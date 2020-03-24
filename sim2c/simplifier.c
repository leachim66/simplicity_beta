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
IMPORT void initialize_maybe_future(NODE *var, NODE *val);
IMPORT NODE *create_future(void);
IMPORT int result_count;
IMPORT void invalid_results_error(void);
IMPORT void initialize_future(NODE *var, NODE *val);
IMPORT NODE *create_cell(void);
IMPORT NODE *create_cell_with_contents(NODE *contents);
typedef struct CELL {
  FUNC type;
  struct ATTRIBUTES *attributes;
  NODE *contents;
} CELL;
IMPORT NODE *create_closure(FUNC type, int par_count);
IMPORT NODE *undefined;
IMPORT NODE *create_continuation(void);
IMPORT void too_few_arguments_error(void);
IMPORT void too_many_arguments_error(void);
IMPORT NODE *collect_node(NODE *node);
IMPORT void register_module_info(MODULE_INFO *info);
IMPORT void define_polymorphic_function(
  const char *namespace, const char *name, NODE_GETTER getter, int *id_p,
  NODE **var_p
);
IMPORT NODE *from_uint32(uint32_t val);
IMPORT NODE *from_uchar32(unsigned int chr);
IMPORT NODE *create_function(FUNC func, int par_count);
IMPORT void set_module(const char *name);
IMPORT void set_used_namespaces(const char **namespaces);
IMPORT void register_dynamic(int *id_p);
IMPORT NODE *from_latin_1_string(const char *str, long len);
IMPORT void define_single_assign_static(
  const char *namespace, const char *name,
  NODE_GETTER getter, NODE **var_p
);
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
IMPORT void use_polymorphic_function(
  const char *namespace, const char *name, NODE_GETTER *getter, int *id
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
IMPORT void maybe_initialize_future(NODE *var, NODE *val);
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
#define IS_OLD(addr) false
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
static NODE_GETTER get__DYNAMIC_MULTI;
static NODE_GETTER get_value_or_future__DYNAMIC_MULTI;
static NODE_GETTER get__DYNAMIC_SINGLE;
static NODE_GETTER get_value_or_future__DYNAMIC_SINGLE;
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
static NODE_GETTER get__actions;
static NODE_SETTER set__actions;
static NODE_GETTER get__already_defined_names;
static NODE_SETTER define__already_defined_names;
static NODE_GETTER get__alt;
static NODE_GETTER get_value_or_future__alt;
static int poly_idx__arguments_of;
static NODE_GETTER get__arguments_of;
static NODE_GETTER get__assignment;
static NODE_GETTER get_value_or_future__assignment;
static NODE_GETTER get__attribute_function_pair;
static NODE_GETTER get_value_or_future__attribute_function_pair;
static NODE_GETTER get__attribute_kind_of;
static NODE_GETTER get_value_or_future__attribute_kind_of;
static NODE_GETTER get__attribute_value_pair;
static NODE_GETTER get_value_or_future__attribute_value_pair;
static NODE_GETTER get__before;
static NODE_GETTER get_value_or_future__before;
static NODE_GETTER get__behind;
static NODE_GETTER get_value_or_future__behind;
static NODE_GETTER get__case;
static NODE_GETTER get_value_or_future__case;
static NODE_GETTER get__check_usage;
static NODE_GETTER get_value_or_future__check_usage;
static NODE_GETTER get__cond;
static NODE_GETTER get_value_or_future__cond;
static int poly_idx__continuation_of;
static NODE_GETTER get__continuation_of;
static int poly_idx__default_value_of;
static NODE_GETTER get__default_value_of;
static NODE_GETTER get__defined_functions;
static NODE_SETTER set__defined_functions;
static NODE_GETTER get__defined_names_of;
static NODE_GETTER get_value_or_future__defined_names_of;
static NODE_GETTER get__defined_nodes;
static NODE_SETTER set__defined_nodes;
static NODE_GETTER get__defined_structs;
static NODE_SETTER set__defined_structs;
static NODE_GETTER get__definitions;
static NODE_SETTER set__definitions;
static NODE_SETTER define__definitions;
static int poly_idx__definitions_of;
static NODE_GETTER get__definitions_of;
static NODE_GETTER get__do;
static NODE_GETTER get_value_or_future__do;
static NODE_GETTER get__drop;
static NODE_GETTER get_value_or_future__drop;
static NODE_GETTER get__empty_list;
static NODE_GETTER get_value_or_future__empty_list;
static NODE_GETTER get__empty_table;
static NODE_GETTER get_value_or_future__empty_table;
static int poly_idx__end_position_of;
static NODE_GETTER get__end_position_of;
static NODE_GETTER get__extend_to;
static NODE_GETTER get_value_or_future__extend_to;
static NODE_GETTER get__false;
static NODE_GETTER get_value_or_future__false;
static NODE_GETTER get__for_each;
static NODE_GETTER get_value_or_future__for_each;
static int poly_idx__fragment_of;
static NODE_GETTER get__fragment_of;
static int poly_idx__functor_of;
static NODE_GETTER get__functor_of;
static int poly_idx__identifier_of;
static NODE_GETTER get__identifier_of;
static NODE_GETTER get__if;
static NODE_GETTER get_value_or_future__if;
static NODE_GETTER get__inc;
static NODE_GETTER get_value_or_future__inc;
static int poly_idx__inherited_names_of;
static NODE_GETTER get__inherited_names_of;
static NODE_GETTER get__is_a_constant;
static NODE_GETTER get_value_or_future__is_a_constant;
static NODE_GETTER get__is_a_definition;
static NODE_GETTER get_value_or_future__is_a_definition;
static NODE_GETTER get__is_a_function_call;
static NODE_GETTER get_value_or_future__is_a_function_call;
static NODE_GETTER get__is_a_list;
static NODE_GETTER get_value_or_future__is_a_list;
static NODE_GETTER get__is_a_method_definition;
static NODE_GETTER get_value_or_future__is_a_method_definition;
static NODE_GETTER get__is_a_multi_assign_definition;
static NODE_GETTER get_value_or_future__is_a_multi_assign_definition;
static NODE_GETTER get__is_a_remark;
static NODE_GETTER get_value_or_future__is_a_remark;
static NODE_GETTER get__is_a_single_assign_definition;
static NODE_GETTER get_value_or_future__is_a_single_assign_definition;
static NODE_GETTER get__is_a_static_single_definition;
static NODE_GETTER get_value_or_future__is_a_static_single_definition;
static NODE_GETTER get__is_a_temporary;
static NODE_GETTER get_value_or_future__is_a_temporary;
static NODE_GETTER get__is_an_assignment;
static NODE_GETTER get_value_or_future__is_an_assignment;
static NODE_GETTER get__is_an_attribute_access;
static NODE_GETTER get_value_or_future__is_an_attribute_access;
static int poly_idx__is_an_expanded_item;
static NODE_GETTER get__is_an_expanded_item;
static NODE_GETTER get__is_an_identifier;
static NODE_GETTER get_value_or_future__is_an_identifier;
static int poly_idx__is_an_initialization;
static NODE_GETTER get__is_an_initialization;
static int poly_idx__is_an_optional_item;
static NODE_GETTER get__is_an_optional_item;
static NODE_GETTER get__is_defined;
static NODE_GETTER get_value_or_future__is_defined;
static NODE_GETTER get__is_empty;
static NODE_GETTER get_value_or_future__is_empty;
static NODE_GETTER get__is_single_assign;
static NODE_GETTER get_value_or_future__is_single_assign;
static NODE_GETTER get__kind_of;
static NODE_GETTER get_value_or_future__kind_of;
static NODE_GETTER get__length_of;
static NODE_GETTER get_value_or_future__length_of;
static NODE_GETTER get__list;
static NODE_GETTER get_value_or_future__list;
static NODE_GETTER get__might_be_constant;
static NODE_GETTER get_value_or_future__might_be_constant;
static int poly_idx__name_of;
static NODE_GETTER get__name_of;
static int poly_idx__output_arguments_of;
static NODE_GETTER get__output_arguments_of;
static int poly_idx__parameters_of;
static NODE_GETTER get__parameters_of;
static NODE_GETTER get__peek;
static NODE_GETTER get_value_or_future__peek;
static NODE_GETTER get__pop;
static NODE_GETTER get_value_or_future__pop;
static NODE_GETTER get__procedure_call;
static NODE_GETTER get_value_or_future__procedure_call;
static NODE_GETTER get__push;
static NODE_GETTER get_value_or_future__push;
static int poly_idx__result_count_of;
static NODE_GETTER get__result_count_of;
static NODE_GETTER get__show_compiler_debug_info;
static NODE_GETTER get_value_or_future__show_compiler_debug_info;
static NODE_GETTER get__sim2c__attribute_function_pair;
static NODE_GETTER get_value_or_future__sim2c__attribute_function_pair;
static NODE_GETTER get__sim2c__attribute_value_pair;
static NODE_GETTER get_value_or_future__sim2c__attribute_value_pair;
static NODE_GETTER get__sim2c__body;
static NODE_GETTER get_value_or_future__sim2c__body;
static NODE_GETTER get__sim2c__c_body;
static NODE_GETTER get_value_or_future__sim2c__c_body;
static NODE_GETTER get__sim2c__c_code;
static NODE_GETTER get_value_or_future__sim2c__c_code;
static NODE_GETTER get__sim2c__call;
static NODE_GETTER get_value_or_future__sim2c__call;
static NODE_GETTER get__sim2c__function_call;
static NODE_GETTER get_value_or_future__sim2c__function_call;
static NODE_GETTER get__sim2c__temp_idx;
static NODE_SETTER set__sim2c__temp_idx;
static NODE_SETTER define__sim2c__temp_idx;
static int poly_idx__simplify_expression;
static NODE_GETTER get__simplify_expression;
static int poly_idx__simplify_statement;
static NODE_GETTER get__simplify_statement;
static NODE_GETTER get__source_of;
static NODE_GETTER get_value_or_future__source_of;
static int poly_idx__source_position_of;
static NODE_GETTER get__source_position_of;
static NODE_GETTER get__statements;
static NODE_SETTER set__statements;
static NODE_SETTER define__statements;
static int poly_idx__statements_of;
static NODE_GETTER get__statements_of;
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
static NODE_GETTER get__temp_idx;
static NODE_SETTER set__temp_idx;
static NODE_GETTER get__temporary;
static NODE_GETTER get_value_or_future__temporary;
static int poly_idx__temporary_count_of;
static NODE_GETTER get__temporary_count_of;
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
static NODE_GETTER get__use_inline_c;
static NODE_SETTER set__use_inline_c;
static NODE_GETTER get__used_names_of;
static NODE_GETTER get_value_or_future__used_names_of;
static NODE_GETTER get__variable_kind_of;
static NODE_GETTER get_value_or_future__variable_kind_of;
static struct {
  NODE *_temporary_identifier;
  NODE *_simplify_arguments;
  NODE *_do_store;
  NODE *_store_result;
  NODE *sim2c__simplify_statement;
  NODE *sim2c__simplify_expression;
  NODE *sim2c__check_usage;
} var;
static const char *var_names[] = {
  "temporary_identifier",
  "simplify_arguments",
  "do_store",
  "store_result"
};
static int poly_idx__sim2c__simplify_statement;
static void type__sim2c__simplify_statement(void);
static NODE *get__sim2c__simplify_statement(void) {
  return var.sim2c__simplify_statement;
}
static int poly_idx__sim2c__simplify_expression;
static void type__sim2c__simplify_expression(void);
static NODE *get__sim2c__simplify_expression(void) {
  return var.sim2c__simplify_expression;
}
static int dyna_idx__defined_names;
static NODE *get__defined_names(void) {
  return get_dynamic_slot(dyna_idx__defined_names);
}
static void define__defined_names(NODE *node) {
  define_dynamic_slot(dyna_idx__defined_names, node);
}
static int dyna_idx__inherited_names;
static NODE *get__inherited_names(void) {
  return get_dynamic_slot(dyna_idx__inherited_names);
}
static void define__inherited_names(NODE *node) {
  define_dynamic_slot(dyna_idx__inherited_names, node);
}
static NODE *func__5_1;
static void entry__5_1(void);
static FRAME_INFO frame__5_1 = {1, {"id"}};
static void cont__5_2(void);
static NODE *string__5_3;
static void cont__5_4(void);
static NODE *func__6_1;
static void entry__6_1(void);
static FRAME_INFO frame__6_1 = {4, {"self", "arguments", "final_destinations", "output_arguments"}};
static void cont__6_2(void);
static NODE *func__6_3;
static void entry__6_3(void);
static FRAME_INFO frame__6_3 = {1, {"argument"}};
static NODE *func__6_4;
static void entry__6_4(void);
static FRAME_INFO frame__6_4 = {1, {"argument"}};
static void cont__6_5(void);
static NODE *func__6_6;
static void entry__6_6(void);
static FRAME_INFO frame__6_6 = {1, {"argument"}};
static void cont__6_7(void);
static NODE *func__6_8;
static void entry__6_8(void);
static FRAME_INFO frame__6_8 = {1, {"argument"}};
static void cont__6_9(void);
static NODE *func__6_10;
static void entry__6_10(void);
static FRAME_INFO frame__6_10 = {1, {"argument"}};
static void cont__6_11(void);
static NODE *func__6_12;
static void entry__6_12(void);
static FRAME_INFO frame__6_12 = {1, {"argument"}};
static void cont__6_13(void);
static void cont__6_14(void);
static void cont__6_15(void);
static void cont__6_16(void);
static void cont__6_17(void);
static NODE *func__6_18;
static void entry__6_18(void);
static FRAME_INFO frame__6_18 = {4, {"output_arguments", "final_destinations", "self", "first_temporary_index"}};
static NODE *func__6_19;
static void entry__6_19(void);
static FRAME_INFO frame__6_19 = {3, {"break", "output_arguments", "first_temporary_index"}};
static NODE *func__6_20;
static void entry__6_20(void);
static FRAME_INFO frame__6_20 = {5, {"idx", "argument", "output_arguments", "first_temporary_index", "break"}};
static void cont__6_21(void);
static NODE *func__6_22;
static void entry__6_22(void);
static FRAME_INFO frame__6_22 = {2, {"argument", "output_arguments"}};
static void cont__6_23(void);
static NODE *func__6_24;
static void entry__6_24(void);
static FRAME_INFO frame__6_24 = {1, {"output_arguments"}};
static void cont__6_25(void);
static void cont__6_26(void);
static void cont__6_27(void);
static NODE *func__6_28;
static void entry__6_28(void);
static FRAME_INFO frame__6_28 = {1, {"argument"}};
static void cont__6_29(void);
static void cont__6_30(void);
static void cont__6_31(void);
static NODE *func__6_32;
static void entry__6_32(void);
static FRAME_INFO frame__6_32 = {3, {"first_temporary_index", "idx", "break"}};
static void cont__6_33(void);
static void cont__6_34(void);
static void cont__6_35(void);
static NODE *func__6_36;
static void entry__6_36(void);
static FRAME_INFO frame__6_36 = {3, {"final_destinations", "output_arguments", "first_temporary_index"}};
static NODE *func__6_37;
static void entry__6_37(void);
static FRAME_INFO frame__6_37 = {4, {"idx", "argument", "first_temporary_index", "final_destinations"}};
static void cont__6_38(void);
static NODE *func__6_39;
static void entry__6_39(void);
static FRAME_INFO frame__6_39 = {1, {"argument"}};
static void cont__6_40(void);
static void cont__6_41(void);
static NODE *func__6_42;
static void entry__6_42(void);
static FRAME_INFO frame__6_42 = {1, {"final_destinations"}};
static void cont__6_43(void);
static NODE *func__6_44;
static void entry__6_44(void);
static FRAME_INFO frame__6_44 = {3, {"argument", "final_destinations", "temp"}};
static void cont__6_45(void);
static NODE *func__6_46;
static void entry__6_46(void);
static FRAME_INFO frame__6_46 = {2, {"argument", "temp"}};
static void cont__6_47(void);
static NODE *func__6_48;
static void entry__6_48(void);
static FRAME_INFO frame__6_48 = {2, {"argument", "temp"}};
static NODE *func__6_49;
static void entry__6_49(void);
static FRAME_INFO frame__6_49 = {2, {"argument", "temp"}};
static void cont__6_50(void);
static NODE *func__6_51;
static void entry__6_51(void);
static FRAME_INFO frame__6_51 = {2, {"argument", "temp"}};
static void cont__6_52(void);
static void cont__6_53(void);
static void cont__6_54(void);
static void cont__6_55(void);
static void cont__6_56(void);
static void cont__6_57(void);
static NODE *func__7_1;
static void entry__7_1(void);
static FRAME_INFO frame__7_1 = {3, {"name", "definition", "info"}};
static void cont__7_2(void);
static void cont__7_3(void);
static NODE *func__7_4;
static void entry__7_4(void);
static FRAME_INFO frame__7_4 = {2, {"info", "name"}};
static void cont__7_5(void);
static void cont__7_6(void);
static NODE *func__7_7;
static void entry__7_7(void);
static FRAME_INFO frame__7_7 = {2, {"info", "name"}};
static void cont__7_8(void);
static NODE *string__7_9;
static NODE *string__7_10;
static void cont__7_11(void);
static NODE *func__7_12;
static void entry__7_12(void);
static FRAME_INFO frame__7_12 = {2, {"info", "name"}};
static void cont__7_13(void);
static void cont__7_14(void);
static NODE *func__7_15;
static void entry__7_15(void);
static FRAME_INFO frame__7_15 = {2, {"info", "name"}};
static void cont__7_16(void);
static NODE *string__7_17;
static NODE *string__7_18;
static void cont__7_19(void);
static NODE *func__7_20;
static void entry__7_20(void);
static FRAME_INFO frame__7_20 = {2, {"info", "name"}};
static void cont__7_21(void);
static void cont__7_22(void);
static NODE *func__7_23;
static void entry__7_23(void);
static FRAME_INFO frame__7_23 = {2, {"info", "name"}};
static void cont__7_24(void);
static NODE *string__7_25;
static NODE *string__7_26;
static void cont__7_27(void);
static NODE *func__7_28;
static void entry__7_28(void);
static FRAME_INFO frame__7_28 = {2, {"info", "name"}};
static void cont__7_29(void);
static void cont__7_30(void);
static NODE *func__7_31;
static void entry__7_31(void);
static FRAME_INFO frame__7_31 = {2, {"info", "name"}};
static void cont__7_32(void);
static NODE *string__7_33;
static NODE *string__7_34;
static void cont__7_35(void);
static NODE *get__sim2c__check_usage(void) {
  return var.sim2c__check_usage;
}
static NODE *func__8_1;
static void entry__8_1(void);
static FRAME_INFO frame__8_1 = {1, {"self"}};
static NODE *string__8_2;
static void cont__8_3(void);
static void cont__8_4(void);
static NODE *func__9_1;
static void entry__9_1(void);
static FRAME_INFO frame__9_1 = {1, {"self"}};
static NODE *string__9_2;
static void cont__9_3(void);
static NODE *func__10_1;
static void entry__10_1(void);
static FRAME_INFO frame__10_1 = {2, {"self", "all_defined_names"}};
static NODE *string__10_2;
static void cont__10_3(void);
static void cont__10_4(void);
static NODE *func__10_5;
static void entry__10_5(void);
static FRAME_INFO frame__10_5 = {4, {"name", "info", "all_defined_names", "outer_info"}};
static void cont__10_6(void);
static void cont__10_7(void);
static NODE *func__10_8;
static void entry__10_8(void);
static FRAME_INFO frame__10_8 = {2, {"info", "name"}};
static void cont__10_9(void);
static NODE *string__10_10;
static NODE *string__10_11;
static void cont__10_12(void);
static NODE *func__10_13;
static void entry__10_13(void);
static FRAME_INFO frame__10_13 = {3, {"all_defined_names", "name", "info"}};
static void cont__10_14(void);
static void cont__10_15(void);
static void cont__10_16(void);
static NODE *func__10_17;
static void entry__10_17(void);
static FRAME_INFO frame__10_17 = {5, {"name", "info", "all_defined_names", "self", "definition"}};
static void cont__10_18(void);
static void cont__10_19(void);
static NODE *func__10_20;
static void entry__10_20(void);
static FRAME_INFO frame__10_20 = {4, {"name", "definition", "info", "self"}};
static void cont__10_21(void);
static void cont__10_22(void);
static void cont__10_23(void);
static NODE *func__10_24;
static void entry__10_24(void);
static FRAME_INFO frame__10_24 = {1, {"name"}};
static void cont__10_25(void);
static void cont__10_26(void);
static void cont__10_27(void);
static NODE *func__10_28;
static void entry__10_28(void);
static FRAME_INFO frame__10_28 = {3, {"self", "name", "info"}};
static void cont__10_29(void);
static void cont__10_30(void);
static void cont__10_31(void);
static NODE *func__10_32;
static void entry__10_32(void);
static FRAME_INFO frame__10_32 = {4, {"return__4", "self", "all_defined_names", "max_temp_idx"}};
static void cont__10_33(void);
static void cont__10_34(void);
static void cont__10_35(void);
static NODE *func__10_36;
static void entry__10_36(void);
static FRAME_INFO frame__10_36 = {3, {"parameter", "max_temp_idx", "default_value"}};
static void cont__10_37(void);
static void cont__10_38(void);
static NODE *func__10_39;
static void entry__10_39(void);
static FRAME_INFO frame__10_39 = {3, {"default_value", "parameter", "max_temp_idx"}};
static void cont__10_40(void);
static NODE *func__10_41;
static void entry__10_41(void);
static FRAME_INFO frame__10_41 = {5, {"return__1", "parameter", "default_value", "max_temp_idx", "identifier"}};
static void cont__10_42(void);
static void cont__10_43(void);
static void cont__10_44(void);
static void cont__10_45(void);
static void cont__10_46(void);
static void cont__10_47(void);
static void cont__10_48(void);
static void cont__10_49(void);
static NODE *func__10_50;
static void entry__10_50(void);
static FRAME_INFO frame__10_50 = {2, {"default_value", "parameter"}};
static void cont__10_51(void);
static void cont__10_52(void);
static void cont__10_53(void);
static void cont__10_54(void);
static NODE *func__10_55;
static void entry__10_55(void);
static FRAME_INFO frame__10_55 = {2, {"statement", "max_temp_idx"}};
static void cont__10_56(void);
static NODE *func__10_57;
static void entry__10_57(void);
static FRAME_INFO frame__10_57 = {2, {"statement", "max_temp_idx"}};
static void cont__10_58(void);
static NODE *func__10_59;
static void entry__10_59(void);
static FRAME_INFO frame__10_59 = {1, {"statement"}};
static void cont__10_60(void);
static void cont__10_61(void);
static void cont__10_62(void);
static NODE *func__10_63;
static void entry__10_63(void);
static FRAME_INFO frame__10_63 = {1, {"statement"}};
static void cont__10_64(void);
static void cont__10_65(void);
static void cont__10_66(void);
static void cont__10_67(void);
static void cont__10_68(void);
static NODE *func__10_69;
static void entry__10_69(void);
static FRAME_INFO frame__10_69 = {3, {"return__2", "statement", "max_temp_idx"}};
static void cont__10_70(void);
static void cont__10_71(void);
static void cont__10_72(void);
static void cont__10_73(void);
static NODE *func__10_74;
static void entry__10_74(void);
static FRAME_INFO frame__10_74 = {2, {"statement", "max_temp_idx"}};
static void cont__10_75(void);
static NODE *func__10_76;
static void entry__10_76(void);
static FRAME_INFO frame__10_76 = {2, {"statement", "max_temp_idx"}};
static void cont__10_77(void);
static NODE *func__10_78;
static void entry__10_78(void);
static FRAME_INFO frame__10_78 = {1, {"statement"}};
static void cont__10_79(void);
static void cont__10_80(void);
static void cont__10_81(void);
static NODE *func__10_82;
static void entry__10_82(void);
static FRAME_INFO frame__10_82 = {1, {"statement"}};
static void cont__10_83(void);
static void cont__10_84(void);
static void cont__10_85(void);
static void cont__10_86(void);
static void cont__10_87(void);
static NODE *func__10_88;
static void entry__10_88(void);
static FRAME_INFO frame__10_88 = {3, {"return__3", "statement", "max_temp_idx"}};
static void cont__10_89(void);
static void cont__10_90(void);
static void cont__10_91(void);
static void cont__10_92(void);
static void cont__10_93(void);
static void cont__10_94(void);
static NODE *func__10_95;
static void entry__10_95(void);
static FRAME_INFO frame__10_95 = {2, {"self", "temp"}};
static void cont__10_96(void);
static void cont__10_97(void);
static void cont__10_98(void);
static void cont__10_99(void);
static void cont__10_100(void);
static void cont__10_101(void);
static void cont__10_102(void);
static void cont__10_103(void);
static NODE *func__11_1;
static void entry__11_1(void);
static FRAME_INFO frame__11_1 = {6, {"functor", "arguments", "result", "rest", "infos", "info"}};
static void cont__11_2(void);
static void cont__11_3(void);
static NODE *func__11_4;
static void entry__11_4(void);
static FRAME_INFO frame__11_4 = {6, {"arguments", "rest", "functor", "info", "result", "infos"}};
static NODE *func__11_5;
static void entry__11_5(void);
static FRAME_INFO frame__11_5 = {1, {"argument"}};
static void cont__11_6(void);
static void cont__11_7(void);
static void cont__11_8(void);
static void cont__11_9(void);
static NODE *func__11_10;
static void entry__11_10(void);
static FRAME_INFO frame__11_10 = {7, {"functor", "arguments", "info", "rest", "result", "infos", "temp"}};
static void cont__11_11(void);
static void cont__11_12(void);
static void cont__11_13(void);
static void cont__11_14(void);
static void cont__11_15(void);
static void cont__11_16(void);
static void cont__11_17(void);
static void cont__11_18(void);
static void cont__11_19(void);
static void cont__11_20(void);
static void cont__11_21(void);
static void cont__11_22(void);
static void cont__11_23(void);
static void cont__11_24(void);
static void cont__11_25(void);
static void cont__11_26(void);
static void cont__11_27(void);
static NODE *func__11_28;
static void entry__11_28(void);
static FRAME_INFO frame__11_28 = {7, {"rest", "arguments", "functor", "info", "result", "infos", "attribute_pair"}};
static void cont__11_29(void);
static void cont__11_30(void);
static NODE *func__11_31;
static void entry__11_31(void);
static FRAME_INFO frame__11_31 = {7, {"arguments", "functor", "info", "rest", "result", "infos", "temp"}};
static void cont__11_32(void);
static void cont__11_33(void);
static void cont__11_34(void);
static void cont__11_35(void);
static void cont__11_36(void);
static void cont__11_37(void);
static void cont__11_38(void);
static void cont__11_39(void);
static void cont__11_40(void);
static void cont__11_41(void);
static void cont__11_42(void);
static void cont__11_43(void);
static void cont__11_44(void);
static NODE *func__11_45;
static void entry__11_45(void);
static FRAME_INFO frame__11_45 = {0, {}};
static NODE *func__11_46;
static void entry__11_46(void);
static FRAME_INFO frame__11_46 = {0, {}};
static void cont__11_47(void);
static void cont__11_48(void);
static void cont__11_49(void);
static void cont__11_50(void);
static void cont__11_51(void);
static void cont__11_52(void);
static void cont__11_53(void);
static void cont__11_54(void);
static void cont__11_55(void);
static void cont__11_56(void);
static NODE *func__12_1;
static void entry__12_1(void);
static FRAME_INFO frame__12_1 = {5, {"destination", "result", "rest", "infos", "arguments"}};
static void cont__12_2(void);
static void cont__12_3(void);
static void cont__12_4(void);
static NODE *func__12_5;
static void entry__12_5(void);
static FRAME_INFO frame__12_5 = {5, {"arguments", "destination", "result", "rest", "infos"}};
static void cont__12_6(void);
static void cont__12_7(void);
static NODE *func__12_8;
static void entry__12_8(void);
static FRAME_INFO frame__12_8 = {5, {"arguments", "destination", "result", "rest", "infos"}};
static void cont__12_9(void);
static NODE *func__12_10;
static void entry__12_10(void);
static FRAME_INFO frame__12_10 = {5, {"arguments", "result", "rest", "destination", "infos"}};
static void cont__12_11(void);
static void cont__12_12(void);
static NODE *func__12_13;
static void entry__12_13(void);
static FRAME_INFO frame__12_13 = {6, {"destination", "arguments", "result", "rest", "infos", "functor"}};
static void cont__12_14(void);
static void cont__12_15(void);
static NODE *func__12_16;
static void entry__12_16(void);
static FRAME_INFO frame__12_16 = {5, {"functor", "arguments", "result", "rest", "infos"}};
static NODE *func__12_17;
static void entry__12_17(void);
static FRAME_INFO frame__12_17 = {5, {"functor", "result", "rest", "arguments", "infos"}};
static void cont__12_18(void);
static NODE *func__13_1;
static void entry__13_1(void);
static FRAME_INFO frame__13_1 = {3, {"self", "return", "final_destinations"}};
static NODE *string__13_2;
static void cont__13_3(void);
static void cont__13_4(void);
static NODE *func__13_5;
static void entry__13_5(void);
static FRAME_INFO frame__13_5 = {1, {"self"}};
static void cont__13_6(void);
static void cont__13_7(void);
static void cont__13_8(void);
static void cont__13_9(void);
static NODE *func__13_10;
static void entry__13_10(void);
static FRAME_INFO frame__13_10 = {2, {"self", "source"}};
static void cont__13_11(void);
static void cont__13_12(void);
static void cont__13_13(void);
static NODE *func__13_14;
static void entry__13_14(void);
static FRAME_INFO frame__13_14 = {2, {"self", "source"}};
static void cont__13_15(void);
static void cont__13_16(void);
static void cont__13_17(void);
static void cont__13_18(void);
static void cont__13_19(void);
static void cont__13_20(void);
static void cont__13_21(void);
static void cont__13_22(void);
static void cont__13_23(void);
static void cont__13_24(void);
static void cont__13_25(void);
static void cont__13_26(void);
static void cont__13_27(void);
static NODE *func__13_28;
static void entry__13_28(void);
static FRAME_INFO frame__13_28 = {1, {"self"}};
static void cont__13_29(void);
static void cont__13_30(void);
static NODE *func__13_31;
static void entry__13_31(void);
static FRAME_INFO frame__13_31 = {1, {"self"}};
static void cont__13_32(void);
static void cont__13_33(void);
static void cont__13_34(void);
static void cont__13_35(void);
static void cont__13_36(void);
static NODE *func__13_37;
static void entry__13_37(void);
static FRAME_INFO frame__13_37 = {1, {"self"}};
static void cont__13_38(void);
static void cont__13_39(void);
static void cont__13_40(void);
static void cont__13_41(void);
static void cont__13_42(void);
static void cont__13_43(void);
static void cont__13_44(void);
static NODE *func__13_45;
static void entry__13_45(void);
static FRAME_INFO frame__13_45 = {3, {"self", "return", "destination"}};
static void cont__13_46(void);
static void cont__13_47(void);
static void cont__13_48(void);
static NODE *func__13_49;
static void entry__13_49(void);
static FRAME_INFO frame__13_49 = {3, {"destination", "self", "return"}};
static void cont__13_50(void);
static NODE *func__13_51;
static void entry__13_51(void);
static FRAME_INFO frame__13_51 = {4, {"self", "destination", "return", "source"}};
static void cont__13_52(void);
static void cont__13_53(void);
static void cont__13_54(void);
static void cont__13_55(void);
static void cont__13_56(void);
static NODE *func__13_57;
static void entry__13_57(void);
static FRAME_INFO frame__13_57 = {3, {"destination", "source", "return"}};
static void cont__13_58(void);
static void cont__13_59(void);
static void cont__13_60(void);
static NODE *func__13_61;
static void entry__13_61(void);
static FRAME_INFO frame__13_61 = {3, {"source", "destination", "return"}};
static void cont__13_62(void);
static NODE *func__13_63;
static void entry__13_63(void);
static FRAME_INFO frame__13_63 = {1, {"source"}};
static void cont__13_64(void);
static void cont__13_65(void);
static NODE *func__13_66;
static void entry__13_66(void);
static FRAME_INFO frame__13_66 = {3, {"destination", "source", "return"}};
static void cont__13_67(void);
static void cont__13_68(void);
static NODE *func__13_69;
static void entry__13_69(void);
static FRAME_INFO frame__13_69 = {3, {"source", "destination", "self"}};
static void cont__13_70(void);
static NODE *func__13_71;
static void entry__13_71(void);
static FRAME_INFO frame__13_71 = {3, {"destination", "source", "self"}};
static void cont__13_72(void);
static void cont__13_73(void);
static void cont__13_74(void);
static void cont__13_75(void);
static void cont__13_76(void);
static NODE *func__13_77;
static void entry__13_77(void);
static FRAME_INFO frame__13_77 = {2, {"destination", "self"}};
static void cont__13_78(void);
static void cont__13_79(void);
static void cont__13_80(void);
static void cont__13_81(void);
static NODE *func__13_82;
static void entry__13_82(void);
static FRAME_INFO frame__13_82 = {2, {"destination", "self"}};
static void cont__13_83(void);
static void cont__13_84(void);
static void cont__13_85(void);
static void cont__13_86(void);
static NODE *func__13_87;
static void entry__13_87(void);
static FRAME_INFO frame__13_87 = {1, {"self"}};
static void cont__13_88(void);
static NODE *func__13_89;
static void entry__13_89(void);
static FRAME_INFO frame__13_89 = {1, {"argument"}};
static void cont__13_90(void);
static NODE *func__13_91;
static void entry__13_91(void);
static FRAME_INFO frame__13_91 = {1, {"argument"}};
static void cont__13_92(void);
static void cont__13_93(void);
static void cont__13_94(void);
static void cont__13_95(void);
static void cont__13_96(void);
static void cont__13_97(void);
static NODE *func__13_98;
static void entry__13_98(void);
static FRAME_INFO frame__13_98 = {2, {"final_destinations", "self"}};
static NODE *func__13_99;
static void entry__13_99(void);
static FRAME_INFO frame__13_99 = {3, {"idx", "destination", "self"}};
static void cont__13_100(void);
static NODE *func__13_101;
static void entry__13_101(void);
static FRAME_INFO frame__13_101 = {4, {"self", "idx", "destination", "result"}};
static void cont__13_102(void);
static void cont__13_103(void);
static void cont__13_104(void);
static NODE *func__13_105;
static void entry__13_105(void);
static FRAME_INFO frame__13_105 = {2, {"destination", "result"}};
static NODE *func__13_106;
static void entry__13_106(void);
static FRAME_INFO frame__13_106 = {3, {"destination", "result", "identifier"}};
static void cont__13_107(void);
static NODE *func__13_108;
static void entry__13_108(void);
static FRAME_INFO frame__13_108 = {1, {"destination"}};
static NODE *func__13_109;
static void entry__13_109(void);
static FRAME_INFO frame__13_109 = {1, {"destination"}};
static void cont__13_110(void);
static void cont__13_111(void);
static void cont__13_112(void);
static void cont__13_113(void);
static void cont__13_114(void);
static void cont__13_115(void);
static void cont__13_116(void);
static void cont__13_117(void);
static NODE *func__14_1;
static void entry__14_1(void);
static FRAME_INFO frame__14_1 = {2, {"self", "temp"}};
static NODE *string__14_2;
static void cont__14_3(void);
static void cont__14_4(void);
static void cont__14_5(void);
static void cont__14_6(void);
static void cont__14_7(void);
static void cont__14_8(void);
static void cont__14_9(void);
static void cont__14_10(void);
static void cont__14_11(void);
static void cont__14_12(void);
static NODE *func__15_1;
static void entry__15_1(void);
static FRAME_INFO frame__15_1 = {2, {"self", "dummy_destinations"}};
static NODE *string__15_2;
static void cont__15_3(void);
static void cont__15_4(void);
static NODE *func__16_1;
static void entry__16_1(void);
static FRAME_INFO frame__16_1 = {2, {"self", "dummy_destinations"}};
static NODE *string__16_2;
static void cont__16_3(void);
static void cont__16_4(void);
static NODE *func__17_1;
static void entry__17_1(void);
static FRAME_INFO frame__17_1 = {1, {"self"}};
static NODE *string__17_2;
static void cont__17_3(void);
static NODE *func__17_4;
static void entry__17_4(void);
static FRAME_INFO frame__17_4 = {0, {}};
static void cont__17_5(void);
static void cont__17_6(void);
static NODE *func__17_7;
static void entry__17_7(void);
static FRAME_INFO frame__17_7 = {2, {"self", "name"}};
static void cont__17_8(void);
static void cont__17_9(void);
static NODE *func__17_10;
static void entry__17_10(void);
static FRAME_INFO frame__17_10 = {1, {"name"}};
static void cont__17_11(void);
static void cont__17_12(void);
static NODE *func__17_13;
static void entry__17_13(void);
static FRAME_INFO frame__17_13 = {2, {"self", "name"}};
static void cont__17_14(void);
static void cont__17_15(void);
static NODE *func__17_16;
static void entry__17_16(void);
static FRAME_INFO frame__17_16 = {2, {"name", "self"}};
static void cont__17_17(void);
static void cont__17_18(void);
static NODE *func__17_19;
static void entry__17_19(void);
static FRAME_INFO frame__17_19 = {2, {"self", "name"}};
static void cont__17_20(void);
static void cont__17_21(void);
static void cont__17_22(void);
static void cont__17_23(void);
static void cont__17_24(void);
static NODE *func__17_25;
static void entry__17_25(void);
static FRAME_INFO frame__17_25 = {1, {"name"}};
static void cont__17_26(void);
static void cont__17_27(void);
static NODE *string__17_28;
static NODE *string__17_29;
static NODE *string__17_30;
static void cont__17_31(void);
static void cont__17_32(void);
static NODE *func__18_1;
static void entry__18_1(void);
static FRAME_INFO frame__18_1 = {1, {"self"}};
static NODE *string__18_2;
static void cont__18_3(void);
static NODE *func__18_4;
static void entry__18_4(void);
static FRAME_INFO frame__18_4 = {0, {}};
static void cont__18_5(void);
void run__simplifier(void);

static CONTINUATION_INFO continuation_info[] = {
  {type__sim2c__simplify_statement, NULL, 30, 30, 2, 26},
  {type__sim2c__simplify_expression, NULL, 31, 31, 2, 27},
  {run__simplifier, NULL, 34, 34, 1, 28},
  {entry__5_1, NULL, 37, 37, 3, 15},
  {cont__5_2, &frame__5_1, 38, 38, 26, 44},
  {cont__5_4, &frame__5_1, 39, 39, 3, 7},
  {entry__6_6, NULL, 47, 47, 9, 37},
  {cont__6_7, &frame__6_6, 48, 48, 42, 42},
  {entry__6_4, NULL, 45, 45, 10, 37},
  {cont__6_5, &frame__6_4, 45, 48, 7, 42},
  {entry__6_10, NULL, 51, 51, 9, 37},
  {cont__6_11, &frame__6_10, 52, 52, 42, 42},
  {entry__6_8, NULL, 49, 49, 10, 37},
  {cont__6_9, &frame__6_8, 49, 52, 7, 42},
  {entry__6_12, NULL, 54, 54, 9, 37},
  {cont__6_13, &frame__6_12, 54, 54, 37, 37},
  {entry__6_3, NULL, 44, 54, 5, 38},
  {cont__6_14, &frame__6_3, },
  {entry__6_24, NULL, 71, 71, 15, 41},
  {cont__6_25, &frame__6_24, 71, 71, 15, 46},
  {cont__6_26, &frame__6_24, 71, 71, 15, 46},
  {entry__6_28, NULL, 72, 72, 13, 49},
  {cont__6_29, &frame__6_28, 72, 72, 13, 49},
  {entry__6_22, NULL, 70, 70, 15, 52},
  {cont__6_23, &frame__6_22, 69, 71, 13, 45},
  {cont__6_27, &frame__6_22, 72, 72, 13, 49},
  {cont__6_30, &frame__6_22, },
  {entry__6_32, NULL, 75, 75, 13, 17},
  {entry__6_20, NULL, 68, 68, 13, 37},
  {cont__6_21, &frame__6_20, },
  {cont__6_31, &frame__6_20, 66, 75, 9, 18},
  {entry__6_19, NULL, 65, 75, 7, 19},
  {cont__6_33, &frame__6_19, 75, 75, 19, 19},
  {entry__6_39, NULL, 84, 84, 42, 64},
  {cont__6_40, &frame__6_39, 84, 84, 42, 64},
  {entry__6_42, NULL, 85, 85, 13, 46},
  {cont__6_43, &frame__6_42, 85, 85, 46, 46},
  {entry__6_48, NULL, 91, 91, 46, 46},
  {entry__6_46, NULL, 89, 89, 18, 45},
  {cont__6_47, &frame__6_46, 89, 91, 15, 46},
  {entry__6_51, NULL, 94, 94, 46, 46},
  {entry__6_49, NULL, 92, 92, 18, 45},
  {cont__6_50, &frame__6_49, 92, 94, 15, 46},
  {entry__6_44, NULL, 87, 87, 13, 41},
  {cont__6_45, &frame__6_44, 88, 94, 13, 47},
  {cont__6_52, &frame__6_44, 95, 95, 13, 45},
  {cont__6_53, &frame__6_44, 96, 96, 26, 26},
  {entry__6_37, NULL, 84, 84, 11, 37},
  {cont__6_38, &frame__6_37, 84, 84, 11, 64},
  {cont__6_41, &frame__6_37, 83, 96, 9, 27},
  {cont__6_54, &frame__6_37, },
  {entry__6_36, NULL, 78, 96, 7, 28},
  {cont__6_55, &frame__6_36, 96, 96, 29, 29},
  {entry__6_18, NULL, 64, 75, 5, 20},
  {cont__6_34, &frame__6_18, 76, 76, 8, 39},
  {cont__6_35, &frame__6_18, 76, 96, 5, 29},
  {cont__6_56, &frame__6_18, 97, 97, 46, 46},
  {entry__6_1, NULL, 42, 42, 3, 32},
  {cont__6_2, &frame__6_1, 43, 54, 3, 39},
  {cont__6_15, &frame__6_1, 61, 61, 3, 46},
  {cont__6_16, &frame__6_1, 62, 62, 6, 32},
  {cont__6_17, &frame__6_1, 62, 97, 3, 46},
  {cont__6_57, &frame__6_1, 98, 98, 3, 23},
  {entry__7_7, NULL, 105, 105, 21, 39},
  {cont__7_8, &frame__7_7, 105, 106, 41, 62},
  {cont__7_11, &frame__7_7, 105, 106, 9, 62},
  {entry__7_4, NULL, 104, 104, 12, 33},
  {cont__7_5, &frame__7_4, 104, 104, 35, 77},
  {cont__7_6, &frame__7_4, 104, 106, 7, 63},
  {entry__7_15, NULL, 109, 109, 21, 39},
  {cont__7_16, &frame__7_15, 109, 110, 41, 70},
  {cont__7_19, &frame__7_15, 109, 110, 9, 70},
  {entry__7_12, NULL, 108, 108, 12, 33},
  {cont__7_13, &frame__7_12, 108, 108, 35, 63},
  {cont__7_14, &frame__7_12, 108, 110, 7, 71},
  {entry__7_23, NULL, 113, 113, 21, 39},
  {cont__7_24, &frame__7_23, 113, 114, 41, 70},
  {cont__7_27, &frame__7_23, 113, 114, 9, 70},
  {entry__7_20, NULL, 112, 112, 12, 33},
  {cont__7_21, &frame__7_20, 112, 112, 35, 74},
  {cont__7_22, &frame__7_20, 112, 114, 7, 71},
  {entry__7_31, NULL, 117, 117, 21, 39},
  {cont__7_32, &frame__7_31, 117, 118, 41, 71},
  {cont__7_35, &frame__7_31, 117, 118, 9, 71},
  {entry__7_28, NULL, 116, 116, 12, 33},
  {cont__7_29, &frame__7_28, 116, 116, 35, 61},
  {cont__7_30, &frame__7_28, 116, 118, 7, 72},
  {entry__7_1, NULL, 102, 102, 5, 32},
  {cont__7_2, &frame__7_1, 103, 103, 5, 30},
  {cont__7_3, &frame__7_1, 101, 118, 3, 74},
  {entry__8_1, NULL, 124, 124, 3, 57},
  {cont__8_3, &frame__8_1, 125, 125, 3, 23},
  {cont__8_4, &frame__8_1, 125, 125, 23, 23},
  {entry__9_1, NULL, 128, 128, 3, 58},
  {cont__9_3, &frame__9_1, },
  {entry__10_8, NULL, 140, 140, 21, 39},
  {cont__10_9, &frame__10_8, 140, 142, 41, 33},
  {cont__10_12, &frame__10_8, 140, 142, 9, 33},
  {entry__10_13, NULL, 144, 144, 9, 32},
  {cont__10_14, &frame__10_13, 144, 144, 37, 37},
  {entry__10_5, NULL, 137, 137, 5, 43},
  {cont__10_6, &frame__10_5, 139, 139, 7, 27},
  {cont__10_7, &frame__10_5, 138, 144, 5, 38},
  {entry__10_24, NULL, 149, 149, 44, 64},
  {cont__10_25, &frame__10_24, 149, 149, 44, 75},
  {cont__10_26, &frame__10_24, 149, 149, 44, 75},
  {entry__10_28, NULL, 150, 150, 10, 32},
  {cont__10_29, &frame__10_28, 150, 150, 9, 38},
  {cont__10_30, &frame__10_28, 150, 150, 43, 43},
  {entry__10_20, NULL, 148, 148, 7, 38},
  {cont__10_21, &frame__10_20, 149, 149, 10, 28},
  {cont__10_22, &frame__10_20, 149, 149, 10, 39},
  {cont__10_23, &frame__10_20, 149, 149, 10, 75},
  {cont__10_27, &frame__10_20, 149, 150, 7, 43},
  {entry__10_17, NULL, 146, 146, 5, 39},
  {cont__10_18, &frame__10_17, 147, 147, 8, 28},
  {cont__10_19, &frame__10_17, 147, 150, 5, 44},
  {entry__10_41, NULL, 165, 165, 13, 48},
  {cont__10_42, &frame__10_41, 168, 168, 38, 80},
  {cont__10_43, &frame__10_41, 169, 169, 31, 49},
  {cont__10_44, &frame__10_41, 170, 170, 30, 52},
  {cont__10_45, &frame__10_41, 171, 171, 37, 66},
  {cont__10_46, &frame__10_41, 172, 172, 34, 60},
  {cont__10_47, &frame__10_41, 166, 172, 13, 61},
  {cont__10_48, &frame__10_41, 173, 173, 13, 44},
  {cont__10_49, &frame__10_41, 174, 174, 13, 36},
  {entry__10_50, NULL, 176, 176, 13, 46},
  {cont__10_51, &frame__10_50, 177, 177, 53, 53},
  {entry__10_39, NULL, 162, 162, 11, 42},
  {cont__10_40, &frame__10_39, 161, 177, 9, 54},
  {entry__10_36, NULL, 159, 159, 7, 49},
  {cont__10_37, &frame__10_36, 160, 160, 10, 33},
  {cont__10_38, &frame__10_36, 160, 177, 7, 55},
  {cont__10_52, &frame__10_36, },
  {entry__10_63, NULL, 187, 187, 13, 35},
  {cont__10_64, &frame__10_63, 187, 187, 13, 38},
  {cont__10_65, &frame__10_63, 187, 187, 13, 52},
  {cont__10_66, &frame__10_63, 187, 187, 13, 52},
  {entry__10_59, NULL, 186, 186, 13, 42},
  {cont__10_60, &frame__10_59, 186, 186, 13, 45},
  {cont__10_61, &frame__10_59, 186, 186, 13, 75},
  {cont__10_62, &frame__10_59, 187, 187, 13, 52},
  {cont__10_67, &frame__10_59, },
  {entry__10_69, NULL, 190, 190, 13, 40},
  {cont__10_70, &frame__10_69, 191, 191, 13, 44},
  {cont__10_71, &frame__10_69, },
  {entry__10_57, NULL, 185, 185, 13, 38},
  {cont__10_58, &frame__10_57, },
  {cont__10_68, &frame__10_57, 183, 191, 9, 45},
  {entry__10_55, NULL, 182, 182, 14, 34},
  {cont__10_56, &frame__10_55, 182, 191, 7, 46},
  {entry__10_82, NULL, 201, 201, 13, 35},
  {cont__10_83, &frame__10_82, 201, 201, 13, 38},
  {cont__10_84, &frame__10_82, 201, 201, 13, 52},
  {cont__10_85, &frame__10_82, 201, 201, 13, 52},
  {entry__10_78, NULL, 200, 200, 13, 42},
  {cont__10_79, &frame__10_78, 200, 200, 13, 45},
  {cont__10_80, &frame__10_78, 200, 200, 13, 75},
  {cont__10_81, &frame__10_78, 201, 201, 13, 52},
  {cont__10_86, &frame__10_78, },
  {entry__10_88, NULL, 204, 204, 13, 40},
  {cont__10_89, &frame__10_88, 205, 205, 13, 44},
  {cont__10_90, &frame__10_88, },
  {entry__10_76, NULL, 199, 199, 13, 38},
  {cont__10_77, &frame__10_76, },
  {cont__10_87, &frame__10_76, 197, 205, 9, 45},
  {entry__10_74, NULL, 196, 196, 14, 34},
  {cont__10_75, &frame__10_74, 196, 205, 7, 46},
  {entry__10_32, NULL, 152, 152, 5, 41},
  {cont__10_33, &frame__10_32, 153, 153, 5, 45},
  {cont__10_34, &frame__10_32, 158, 158, 18, 35},
  {cont__10_35, &frame__10_32, 158, 177, 5, 56},
  {cont__10_53, &frame__10_32, 181, 181, 14, 32},
  {cont__10_54, &frame__10_32, 181, 191, 5, 47},
  {cont__10_72, &frame__10_32, 195, 195, 14, 32},
  {cont__10_73, &frame__10_32, 195, 205, 5, 47},
  {cont__10_91, &frame__10_32, 208, 208, 5, 28},
  {entry__10_95, NULL, 214, 214, 5, 32},
  {cont__10_96, &frame__10_95, 218, 218, 30, 39},
  {cont__10_97, &frame__10_95, 219, 219, 23, 32},
  {cont__10_98, &frame__10_95, 220, 220, 22, 38},
  {cont__10_99, &frame__10_95, 221, 221, 29, 52},
  {cont__10_100, &frame__10_95, 222, 222, 26, 46},
  {cont__10_101, &frame__10_95, 215, 222, 5, 47},
  {cont__10_102, &frame__10_95, 223, 223, 14, 14},
  {entry__10_1, NULL, 134, 134, 3, 42},
  {cont__10_3, &frame__10_1, 136, 136, 12, 33},
  {cont__10_4, &frame__10_1, 136, 144, 3, 39},
  {cont__10_15, &frame__10_1, 145, 145, 12, 30},
  {cont__10_16, &frame__10_1, 145, 150, 3, 45},
  {cont__10_31, &frame__10_1, 151, 208, 3, 41},
  {cont__10_92, &frame__10_1, 209, 209, 10, 33},
  {cont__10_93, &frame__10_1, 209, 209, 10, 42},
  {cont__10_94, &frame__10_1, 209, 223, 3, 14},
  {cont__10_103, &frame__10_1, },
  {entry__11_5, NULL, 232, 232, 43, 71},
  {cont__11_6, &frame__11_5, 232, 232, 71, 71},
  {entry__11_10, NULL, 234, 234, 9, 36},
  {cont__11_11, &frame__11_10, 240, 240, 34, 43},
  {cont__11_12, &frame__11_10, 241, 241, 26, 42},
  {cont__11_13, &frame__11_10, 242, 242, 33, 56},
  {cont__11_14, &frame__11_10, 243, 243, 30, 50},
  {cont__11_15, &frame__11_10, 235, 243, 9, 51},
  {cont__11_16, &frame__11_10, 244, 244, 23, 31},
  {cont__11_17, &frame__11_10, 244, 244, 40, 48},
  {cont__11_18, &frame__11_10, 244, 244, 9, 54},
  {cont__11_19, &frame__11_10, 245, 245, 20, 20},
  {entry__11_4, NULL, 232, 232, 7, 71},
  {cont__11_7, &frame__11_4, 233, 233, 10, 24},
  {cont__11_8, &frame__11_4, 233, 233, 10, 28},
  {cont__11_9, &frame__11_4, 233, 245, 7, 20},
  {cont__11_20, &frame__11_4, 250, 250, 25, 46},
  {cont__11_21, &frame__11_4, 251, 251, 32, 44},
  {cont__11_22, &frame__11_4, 252, 252, 24, 40},
  {cont__11_23, &frame__11_4, 253, 253, 31, 54},
  {cont__11_24, &frame__11_4, 253, 253, 31, 56},
  {cont__11_25, &frame__11_4, 254, 254, 28, 48},
  {cont__11_26, &frame__11_4, 246, 254, 7, 49},
  {cont__11_27, &frame__11_4, 254, 254, 50, 50},
  {entry__11_31, NULL, 257, 257, 9, 36},
  {cont__11_32, &frame__11_31, 261, 261, 25, 45},
  {cont__11_33, &frame__11_31, 262, 262, 27, 39},
  {cont__11_34, &frame__11_31, 263, 263, 34, 43},
  {cont__11_35, &frame__11_31, 264, 264, 26, 42},
  {cont__11_36, &frame__11_31, 265, 265, 33, 56},
  {cont__11_37, &frame__11_31, 266, 266, 30, 50},
  {cont__11_38, &frame__11_31, 258, 266, 9, 51},
  {cont__11_39, &frame__11_31, 267, 267, 23, 31},
  {cont__11_40, &frame__11_31, 267, 267, 40, 48},
  {cont__11_41, &frame__11_31, 267, 267, 9, 54},
  {cont__11_42, &frame__11_31, 268, 268, 20, 20},
  {entry__11_45, NULL, 273, 273, 11, 36},
  {entry__11_46, NULL, 274, 274, 11, 33},
  {entry__11_28, NULL, 256, 256, 10, 24},
  {cont__11_29, &frame__11_28, 256, 256, 10, 28},
  {cont__11_30, &frame__11_28, 256, 268, 7, 20},
  {cont__11_43, &frame__11_28, 272, 272, 11, 42},
  {cont__11_44, &frame__11_28, 270, 274, 7, 34},
  {cont__11_47, &frame__11_28, 279, 279, 32, 44},
  {cont__11_48, &frame__11_28, 283, 283, 32, 52},
  {cont__11_49, &frame__11_28, 284, 284, 31, 42},
  {cont__11_50, &frame__11_28, 281, 284, 13, 42},
  {cont__11_51, &frame__11_28, 285, 285, 24, 40},
  {cont__11_52, &frame__11_28, 286, 286, 31, 54},
  {cont__11_53, &frame__11_28, 286, 286, 31, 56},
  {cont__11_54, &frame__11_28, 287, 287, 28, 48},
  {cont__11_55, &frame__11_28, 276, 287, 7, 49},
  {cont__11_56, &frame__11_28, 287, 287, 50, 50},
  {entry__11_1, NULL, 229, 229, 3, 18},
  {cont__11_2, &frame__11_1, 231, 231, 5, 23},
  {cont__11_3, &frame__11_1, 230, 287, 3, 51},
  {entry__12_8, NULL, 302, 302, 20, 31},
  {cont__12_9, &frame__12_8, 302, 302, 11, 61},
  {entry__12_10, NULL, 304, 304, 24, 35},
  {cont__12_11, &frame__12_10, 304, 304, 44, 65},
  {cont__12_12, &frame__12_10, 304, 304, 11, 71},
  {entry__12_5, NULL, 301, 301, 9, 20},
  {cont__12_6, &frame__12_5, 301, 301, 9, 37},
  {cont__12_7, &frame__12_5, 300, 304, 7, 72},
  {entry__12_16, NULL, 309, 309, 11, 54},
  {entry__12_17, NULL, 311, 311, 39, 58},
  {cont__12_18, &frame__12_17, 311, 311, 11, 64},
  {entry__12_13, NULL, 306, 306, 7, 38},
  {cont__12_14, &frame__12_13, 308, 308, 9, 32},
  {cont__12_15, &frame__12_13, 307, 311, 7, 65},
  {entry__12_1, NULL, 296, 296, 3, 25},
  {cont__12_2, &frame__12_1, 297, 297, 3, 38},
  {cont__12_3, &frame__12_1, 299, 299, 5, 38},
  {cont__12_4, &frame__12_1, 298, 311, 3, 67},
  {entry__13_5, NULL, 319, 319, 41, 58},
  {cont__13_6, &frame__13_5, 319, 319, 31, 59},
  {cont__13_7, &frame__13_5, 319, 319, 31, 64},
  {cont__13_8, &frame__13_5, 319, 319, 31, 64},
  {entry__13_14, NULL, 324, 324, 23, 40},
  {cont__13_15, &frame__13_14, 326, 326, 18, 44},
  {cont__13_16, &frame__13_14, 326, 326, 46, 70},
  {cont__13_17, &frame__13_14, 326, 326, 46, 73},
  {cont__13_18, &frame__13_14, 326, 326, 13, 74},
  {cont__13_19, &frame__13_14, 327, 327, 25, 44},
  {cont__13_20, &frame__13_14, 328, 328, 24, 40},
  {cont__13_21, &frame__13_14, 329, 329, 31, 54},
  {cont__13_22, &frame__13_14, 330, 330, 28, 48},
  {cont__13_23, &frame__13_14, 330, 330, 50, 50},
  {entry__13_10, NULL, 320, 320, 13, 30},
  {cont__13_11, &frame__13_10, 320, 320, 5, 33},
  {cont__13_12, &frame__13_10, 321, 321, 8, 32},
  {cont__13_13, &frame__13_10, 321, 330, 5, 50},
  {entry__13_31, NULL, 334, 334, 28, 47},
  {cont__13_32, &frame__13_31, 334, 334, 7, 47},
  {cont__13_33, &frame__13_31, 334, 334, 47, 47},
  {entry__13_37, NULL, 336, 336, 28, 47},
  {cont__13_38, &frame__13_37, 336, 336, 7, 47},
  {cont__13_39, &frame__13_37, 336, 336, 47, 47},
  {entry__13_28, NULL, 333, 333, 8, 28},
  {cont__13_29, &frame__13_28, 333, 333, 8, 39},
  {cont__13_30, &frame__13_28, 333, 334, 5, 47},
  {cont__13_34, &frame__13_28, 335, 335, 8, 28},
  {cont__13_35, &frame__13_28, 335, 335, 8, 39},
  {cont__13_36, &frame__13_28, 335, 336, 5, 47},
  {cont__13_40, &frame__13_28, 337, 337, 26, 40},
  {cont__13_41, &frame__13_28, 337, 337, 5, 40},
  {cont__13_42, &frame__13_28, 337, 337, 40, 40},
  {entry__13_57, NULL, 346, 346, 33, 52},
  {cont__13_58, &frame__13_57, 346, 346, 15, 52},
  {cont__13_59, &frame__13_57, 347, 347, 15, 20},
  {entry__13_63, NULL, 349, 349, 42, 64},
  {cont__13_64, &frame__13_63, 349, 349, 42, 64},
  {entry__13_66, NULL, 350, 350, 35, 54},
  {cont__13_67, &frame__13_66, 350, 350, 17, 54},
  {cont__13_68, &frame__13_66, 351, 351, 17, 22},
  {entry__13_61, NULL, 349, 349, 18, 37},
  {cont__13_62, &frame__13_61, 349, 349, 18, 64},
  {cont__13_65, &frame__13_61, 349, 351, 15, 22},
  {entry__13_71, NULL, 353, 353, 35, 54},
  {cont__13_72, &frame__13_71, 353, 353, 17, 54},
  {cont__13_73, &frame__13_71, 354, 354, 18, 41},
  {cont__13_74, &frame__13_71, 354, 354, 18, 44},
  {cont__13_75, &frame__13_71, 354, 354, 17, 44},
  {cont__13_76, &frame__13_71, 354, 354, 70, 70},
  {entry__13_69, NULL, 352, 352, 18, 41},
  {cont__13_70, &frame__13_69, 352, 354, 15, 70},
  {entry__13_77, NULL, 356, 356, 17, 45},
  {cont__13_78, &frame__13_77, 357, 357, 18, 41},
  {cont__13_79, &frame__13_77, 357, 357, 18, 44},
  {cont__13_80, &frame__13_77, 357, 357, 17, 44},
  {cont__13_81, &frame__13_77, 357, 357, 70, 70},
  {entry__13_51, NULL, 344, 344, 21, 38},
  {cont__13_52, &frame__13_51, 344, 344, 13, 41},
  {cont__13_53, &frame__13_51, 345, 345, 16, 45},
  {cont__13_54, &frame__13_51, 345, 345, 16, 53},
  {cont__13_55, &frame__13_51, 345, 345, 16, 53},
  {cont__13_56, &frame__13_51, 345, 347, 13, 20},
  {cont__13_60, &frame__13_51, 348, 357, 13, 71},
  {entry__13_82, NULL, 359, 359, 13, 41},
  {cont__13_83, &frame__13_82, 360, 360, 14, 37},
  {cont__13_84, &frame__13_82, 360, 360, 14, 40},
  {cont__13_85, &frame__13_82, 360, 360, 13, 40},
  {cont__13_86, &frame__13_82, 360, 360, 66, 66},
  {entry__13_49, NULL, 343, 343, 11, 51},
  {cont__13_50, &frame__13_49, 342, 360, 9, 67},
  {entry__13_45, NULL, 340, 340, 20, 44},
  {cont__13_46, &frame__13_45, 340, 340, 7, 47},
  {cont__13_47, &frame__13_45, 341, 341, 10, 36},
  {cont__13_48, &frame__13_45, 341, 360, 7, 68},
  {entry__13_91, NULL, 364, 364, 11, 36},
  {cont__13_92, &frame__13_91, 365, 365, 45, 45},
  {entry__13_89, NULL, 363, 363, 12, 35},
  {cont__13_90, &frame__13_89, 363, 365, 9, 45},
  {cont__13_93, &frame__13_89, },
  {entry__13_87, NULL, 362, 362, 20, 43},
  {cont__13_88, &frame__13_87, 362, 365, 7, 46},
  {cont__13_94, &frame__13_87, 365, 365, 47, 47},
  {entry__13_105, NULL, 377, 377, 13, 43},
  {entry__13_108, NULL, 386, 386, 17, 30},
  {entry__13_109, NULL, 387, 387, 20, 45},
  {cont__13_110, &frame__13_109, 387, 387, 17, 45},
  {entry__13_106, NULL, 385, 385, 17, 44},
  {cont__13_107, &frame__13_106, 383, 387, 13, 46},
  {cont__13_111, &frame__13_106, 391, 391, 38, 54},
  {cont__13_112, &frame__13_106, 392, 392, 31, 42},
  {cont__13_113, &frame__13_106, 393, 393, 30, 52},
  {cont__13_114, &frame__13_106, 394, 394, 37, 66},
  {cont__13_115, &frame__13_106, 395, 395, 34, 60},
  {cont__13_116, &frame__13_106, 389, 395, 13, 61},
  {entry__13_101, NULL, 371, 371, 11, 35},
  {cont__13_102, &frame__13_101, 371, 371, 11, 40},
  {cont__13_103, &frame__13_101, 376, 376, 11, 40},
  {cont__13_104, &frame__13_101, 375, 395, 9, 63},
  {entry__13_99, NULL, 369, 369, 10, 31},
  {cont__13_100, &frame__13_99, 369, 395, 7, 64},
  {entry__13_98, NULL, 368, 395, 5, 65},
  {entry__13_1, NULL, 318, 318, 3, 47},
  {cont__13_3, &frame__13_1, 319, 319, 6, 26},
  {cont__13_4, &frame__13_1, 319, 319, 6, 64},
  {cont__13_9, &frame__13_1, 319, 330, 3, 51},
  {cont__13_24, &frame__13_1, 331, 331, 3, 47},
  {cont__13_25, &frame__13_1, 332, 332, 6, 21},
  {cont__13_26, &frame__13_1, 332, 332, 6, 32},
  {cont__13_27, &frame__13_1, 332, 337, 3, 40},
  {cont__13_43, &frame__13_1, 339, 339, 5, 25},
  {cont__13_44, &frame__13_1, 338, 365, 3, 48},
  {cont__13_95, &frame__13_1, 366, 366, 3, 23},
  {cont__13_96, &frame__13_1, 367, 367, 6, 34},
  {cont__13_97, &frame__13_1, 367, 395, 3, 66},
  {cont__13_117, &frame__13_1, 395, 395, 66, 66},
  {entry__14_1, NULL, 401, 401, 3, 51},
  {cont__14_3, &frame__14_1, 402, 402, 3, 30},
  {cont__14_4, &frame__14_1, 405, 405, 19, 34},
  {cont__14_5, &frame__14_1, 406, 406, 33, 57},
  {cont__14_6, &frame__14_1, 406, 406, 28, 63},
  {cont__14_7, &frame__14_1, 407, 407, 21, 38},
  {cont__14_8, &frame__14_1, 408, 408, 20, 36},
  {cont__14_9, &frame__14_1, 409, 409, 27, 50},
  {cont__14_10, &frame__14_1, 410, 410, 24, 44},
  {cont__14_11, &frame__14_1, 403, 410, 3, 45},
  {cont__14_12, &frame__14_1, 411, 411, 3, 9},
  {entry__15_1, NULL, 417, 417, 3, 58},
  {cont__15_3, &frame__15_1, 418, 419, 3, 47},
  {cont__15_4, &frame__15_1, 419, 419, 48, 48},
  {entry__16_1, NULL, 425, 425, 3, 61},
  {cont__16_3, &frame__16_1, 426, 427, 3, 47},
  {cont__16_4, &frame__16_1, 427, 427, 48, 48},
  {entry__17_4, NULL, 434, 434, 35, 35},
  {entry__17_10, NULL, 439, 439, 22, 43},
  {cont__17_11, &frame__17_10, 439, 439, 48, 48},
  {entry__17_7, NULL, 438, 438, 21, 39},
  {cont__17_8, &frame__17_7, 438, 438, 7, 40},
  {cont__17_9, &frame__17_7, 439, 439, 7, 48},
  {cont__17_12, &frame__17_7, 439, 439, 48, 48},
  {entry__17_16, NULL, 442, 442, 22, 41},
  {cont__17_17, &frame__17_16, 442, 442, 46, 46},
  {entry__17_13, NULL, 441, 441, 21, 39},
  {cont__17_14, &frame__17_13, 441, 441, 7, 40},
  {cont__17_15, &frame__17_13, 442, 442, 7, 46},
  {cont__17_18, &frame__17_13, 442, 442, 46, 46},
  {entry__17_25, NULL, 445, 445, 22, 45},
  {cont__17_26, &frame__17_25, 445, 445, 50, 50},
  {entry__17_19, NULL, 444, 444, 20, 34},
  {cont__17_20, &frame__17_19, 444, 444, 20, 47},
  {cont__17_21, &frame__17_19, 444, 444, 49, 60},
  {cont__17_22, &frame__17_19, 444, 444, 63, 63},
  {cont__17_23, &frame__17_19, 444, 444, 7, 64},
  {cont__17_24, &frame__17_19, 445, 445, 7, 50},
  {cont__17_27, &frame__17_19, 445, 445, 50, 50},
  {entry__17_1, NULL, 433, 433, 3, 44},
  {cont__17_3, &frame__17_1, 434, 434, 3, 35},
  {cont__17_5, &frame__17_1, 436, 436, 5, 17},
  {cont__17_6, &frame__17_1, 435, 445, 3, 51},
  {cont__17_31, &frame__17_1, 446, 446, 3, 24},
  {cont__17_32, &frame__17_1, 446, 446, 24, 24},
  {entry__18_4, NULL, 453, 453, 35, 35},
  {entry__18_1, NULL, 452, 452, 3, 44},
  {cont__18_3, &frame__18_1, 453, 453, 3, 35},
  {cont__18_5, &frame__18_1, 453, 453, 35, 35}
};

union NODE {
  struct {
    FUNC type;
    ATTRIBUTES *attributes;
  };
  CONTINUATION continuation;
  CLOSURE closure;
};
static void type__sim2c__simplify_statement(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__sim2c__simplify_statement);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__sim2c__simplify_statement, attr);
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
static void type__sim2c__simplify_expression(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__sim2c__simplify_expression);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__sim2c__simplify_expression, attr);
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
static NODE *number__0;
static NODE *character__40;
static NODE *character__32;
static NODE *number__1;
static NODE *character__42;

static const char *used_namespaces[] = {
  "std",
  "sim2c",
  "node",
  NULL
};

static MODULE_INFO module_info = {
  NULL,
  "simplifier",
  continuation_info,
  sizeof(continuation_info)/sizeof(CONTINUATION_INFO),
  (NODE **)&var,
  var_names,
  sizeof(var_names)/sizeof(const char *),
  used_namespaces,
  {DEBUG_FILENAME("simplifier.sim")}
};

/******
C O D E
******/

static int already_run = false;

EXPORT void run__simplifier(void) {
  if (already_run) {
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  already_run = true;
  allocate_initialized_frame_gc(0, 0);
  // 33: %defined_names empty_table
  initialize_maybe_future(get__defined_names(), get__empty_table());
  // 34: %inherited_names empty_table
  initialize_maybe_future(get__inherited_names(), get__empty_table());
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__5_1(void) {
  allocate_initialized_frame_gc(0, 2);
  // slot allocations:
  // id: 0
  frame->slots[0] /* id */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 37: inc &temp_idx
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__temp_idx();
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__5_2;
}
static void cont__5_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__temp_idx(arguments->slots[0]);
  // 38: ... "temp__@(temp_idx)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__5_3;
  arguments->slots[1] = get__temp_idx();
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__5_4;
}
static void cont__5_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 38: $id temporary(.name_of "temp__@(temp_idx)")
  {
    NODE *temp = clone_object_and_attributes(get__temporary());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__name_of, frame->slots[1] /* temp__1 */);
    initialize_future(frame->slots[0] /* id */, temp);

  }
  // 39: -> id
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* id */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__6_1(void) {
  allocate_initialized_frame_gc(1, 6);
  // slot allocations:
  // self: 0
  // arguments: 1
  // final_destinations: 2
  // output_arguments: 3
  frame->slots[1] /* arguments */ = create_cell();
  frame->slots[2] /* final_destinations */ = create_cell();
  frame->slots[3] /* output_arguments */ = create_cell();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* self */ = create_cell_with_contents(arguments->slots[0]);
  // 42: $$arguments arguments_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__6_2;
}
static void cont__6_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* arguments */ = arguments->slots[0];
  // 43: update_each &arguments: (&argument)
  // 44:   cond
  // 45:     -> argument.is_an_optional_item:
  // 46:       !argument.is_an_optional_item false
  // 47:       simplify_expression &argument
  // 48:       !argument.is_an_optional_item true
  // 49:     -> argument.is_an_expanded_item:
  // 50:       !argument.is_an_expanded_item false
  // 51:       simplify_expression &argument
  // 52:       !argument.is_an_expanded_item true
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* arguments */;
  arguments->slots[1] = func__6_3;
  result_count = 1;
  myself = get__update_each();
  func = myself->type;
  frame->cont = cont__6_15;
}
static void entry__6_3(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // argument: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* argument */ = create_cell_with_contents(arguments->slots[0]);
  // 45: -> argument.is_an_optional_item:
  // 46:   !argument.is_an_optional_item false
  // 47:   simplify_expression &argument
  // 48:   !argument.is_an_optional_item true
  frame->slots[1] /* temp__1 */ = create_closure(entry__6_4, 0);
  // 49: -> argument.is_an_expanded_item:
  // 50:   !argument.is_an_expanded_item false
  // 51:   simplify_expression &argument
  // 52:   !argument.is_an_expanded_item true
  frame->slots[2] /* temp__2 */ = create_closure(entry__6_8, 0);
  // 53: :
  // 54:   simplify_expression &argument
  frame->slots[3] /* temp__3 */ = create_closure(entry__6_12, 0);
  // 44: cond
  // 45:   -> argument.is_an_optional_item:
  // 46:     !argument.is_an_optional_item false
  // 47:     simplify_expression &argument
  // 48:     !argument.is_an_optional_item true
  // 49:   -> argument.is_an_expanded_item:
  // 50:     !argument.is_an_expanded_item false
  // 51:     simplify_expression &argument
  // 52:     !argument.is_an_expanded_item true
  // 53:   :
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  arguments->slots[2] = frame->slots[3] /* temp__3 */;
  result_count =
    frame->caller_result_count >= 1 ?
    frame->caller_result_count-1 : -1;
  myself = get__cond();
  func = myself->type;
  frame->cont = cont__6_14;
}
static void entry__6_10(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // argument: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* argument */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 50: !argument.is_an_expanded_item false
  frame->slots[1] /* temp__1 */ = get__false();
  // 50: !argument.is_an_expanded_item
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* argument */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__is_an_expanded_item, frame->slots[1] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* argument */ = temp;

  }
  // 51: simplify_expression &argument
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* argument */;
  result_count = 1;
  myself = get__simplify_expression();
  func = myself->type;
  frame->cont = cont__6_11;
}
static void cont__6_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* argument */ = arguments->slots[0];
  // 52: !argument.is_an_expanded_item true
  frame->slots[1] /* temp__1 */ = get__true();
  // 52: !argument.is_an_expanded_item
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* argument */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__is_an_expanded_item, frame->slots[1] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* argument */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__6_6(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // argument: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* argument */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 46: !argument.is_an_optional_item false
  frame->slots[1] /* temp__1 */ = get__false();
  // 46: !argument.is_an_optional_item
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* argument */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__is_an_optional_item, frame->slots[1] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* argument */ = temp;

  }
  // 47: simplify_expression &argument
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* argument */;
  result_count = 1;
  myself = get__simplify_expression();
  func = myself->type;
  frame->cont = cont__6_7;
}
static void cont__6_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* argument */ = arguments->slots[0];
  // 48: !argument.is_an_optional_item true
  frame->slots[1] /* temp__1 */ = get__true();
  // 48: !argument.is_an_optional_item
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* argument */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__is_an_optional_item, frame->slots[1] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* argument */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__6_4(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // argument: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* argument */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 45: ... argument.is_an_optional_item
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* argument */;
  result_count = 1;
  myself = get__is_an_optional_item();
  func = myself->type;
  frame->cont = cont__6_5;
}
static void cont__6_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 45: ... :
  // 46:   !argument.is_an_optional_item false
  // 47:   simplify_expression &argument
  // 48:   !argument.is_an_optional_item true
  frame->slots[2] /* temp__2 */ = create_closure(entry__6_6, 0);
  // 45: -> argument.is_an_optional_item:
  // 46:   !argument.is_an_optional_item false
  // 47:   simplify_expression &argument
  // 48:   !argument.is_an_optional_item true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__6_8(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // argument: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* argument */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 49: ... argument.is_an_expanded_item
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* argument */;
  result_count = 1;
  myself = get__is_an_expanded_item();
  func = myself->type;
  frame->cont = cont__6_9;
}
static void cont__6_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 49: ... :
  // 50:   !argument.is_an_expanded_item false
  // 51:   simplify_expression &argument
  // 52:   !argument.is_an_expanded_item true
  frame->slots[2] /* temp__2 */ = create_closure(entry__6_10, 0);
  // 49: -> argument.is_an_expanded_item:
  // 50:   !argument.is_an_expanded_item false
  // 51:   simplify_expression &argument
  // 52:   !argument.is_an_expanded_item true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__6_12(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // argument: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* argument */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 54: simplify_expression &argument
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* argument */;
  result_count = 1;
  myself = get__simplify_expression();
  func = myself->type;
  frame->cont = cont__6_13;
}
static void cont__6_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* argument */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__6_14(void) {
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
static void cont__6_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* arguments */ = arguments->slots[0];
  // 55: !self.arguments_of arguments
  frame->slots[4] /* temp__1 */ = ((CELL *)frame->slots[1])->contents /* arguments */;
  // 55: !self.arguments_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[4] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* self */ = temp;

  }
  // 60: $$final_destinations undefined
  ((CELL *)frame->slots[2])->contents /* final_destinations */ = get__undefined();
  // 61: $$output_arguments output_arguments_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__output_arguments_of();
  func = myself->type;
  frame->cont = cont__6_16;
}
static void cont__6_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* output_arguments */ = arguments->slots[0];
  // 62: ... output_arguments.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* output_arguments */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__6_17;
}
static void cont__6_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 62: ... :
  // 63:   $$first_temporary_index undefined
  // 64:   do: (-> break)
  // 65:     for_each output_arguments: (idx argument)
  // 66:       unless
  // 67:         ||
  // 68:           argument.is_an_identifier
  // 69:           &&
  // 70:             argument.is_a_single_assign_definition
  // 71:             length_of(output_arguments) == 1
  // ...
  frame->slots[5] /* temp__2 */ = create_closure(entry__6_18, 0);
  // 62: if output_arguments.is_defined:
  // 63:   $$first_temporary_index undefined
  // 64:   do: (-> break)
  // 65:     for_each output_arguments: (idx argument)
  // 66:       unless
  // 67:         ||
  // 68:           argument.is_an_identifier
  // 69:           &&
  // 70:             argument.is_a_single_assign_definition
  // 71:             length_of(output_arguments) == 1
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__6_57;
}
static void entry__6_18(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // output_arguments: 0
  // final_destinations: 1
  // self: 2
  // first_temporary_index: 3
  frame->slots[0] = myself->closure.frame->slots[3]; /* output_arguments */
  frame->slots[1] = myself->closure.frame->slots[2]; /* final_destinations */
  frame->slots[2] = myself->closure.frame->slots[0]; /* self */
  frame->slots[3] /* first_temporary_index */ = create_cell();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 63: $$first_temporary_index undefined
  ((CELL *)frame->slots[3])->contents /* first_temporary_index */ = get__undefined();
  // 64: ... : (-> break)
  // 65:   for_each output_arguments: (idx argument)
  // 66:     unless
  // 67:       ||
  // 68:         argument.is_an_identifier
  // 69:         &&
  // 70:           argument.is_a_single_assign_definition
  // 71:           length_of(output_arguments) == 1
  // 72:         argument.is_a_multi_assign_definition
  // 73:       :
  // ...
  frame->slots[4] /* temp__1 */ = create_closure(entry__6_19, 0);
  // 64: do: (-> break)
  // 65:   for_each output_arguments: (idx argument)
  // 66:     unless
  // 67:       ||
  // 68:         argument.is_an_identifier
  // 69:         &&
  // 70:           argument.is_a_single_assign_definition
  // 71:           length_of(output_arguments) == 1
  // 72:         argument.is_a_multi_assign_definition
  // 73:       :
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__6_34;
}
static void entry__6_19(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // break: 0
  // output_arguments: 1
  // first_temporary_index: 2
  frame->slots[0] /* break */ = create_continuation();
  frame->slots[1] = myself->closure.frame->slots[0]; /* output_arguments */
  frame->slots[2] = myself->closure.frame->slots[3]; /* first_temporary_index */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 65: ... : (idx argument)
  // 66:   unless
  // 67:     ||
  // 68:       argument.is_an_identifier
  // 69:       &&
  // 70:         argument.is_a_single_assign_definition
  // 71:         length_of(output_arguments) == 1
  // 72:       argument.is_a_multi_assign_definition
  // 73:     :
  // 74:       !first_temporary_index idx
  // ...
  frame->slots[3] /* temp__1 */ = create_closure(entry__6_20, 2);
  // 65: for_each output_arguments: (idx argument)
  // 66:   unless
  // 67:     ||
  // 68:       argument.is_an_identifier
  // 69:       &&
  // 70:         argument.is_a_single_assign_definition
  // 71:         length_of(output_arguments) == 1
  // 72:       argument.is_a_multi_assign_definition
  // 73:     :
  // 74:       !first_temporary_index idx
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* output_arguments */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__6_33;
}
static void entry__6_32(void) {
  allocate_initialized_frame_gc(3, 3);
  // slot allocations:
  // first_temporary_index: 0
  // idx: 1
  // break: 2
  frame->slots[0] = myself->closure.frame->slots[3]; /* first_temporary_index */
  frame->slots[1] = myself->closure.frame->slots[0]; /* idx */
  frame->slots[2] = myself->closure.frame->slots[4]; /* break */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 74: !first_temporary_index idx
  ((CELL *)frame->slots[0])->contents /* first_temporary_index */ = frame->slots[1] /* idx */;
  // 75: break
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[2] /* break */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__6_20(void) {
  allocate_initialized_frame_gc(5, 9);
  // slot allocations:
  // idx: 0
  // argument: 1
  // output_arguments: 2
  // first_temporary_index: 3
  // break: 4
  frame->slots[2] = myself->closure.frame->slots[1]; /* output_arguments */
  frame->slots[3] = myself->closure.frame->slots[2]; /* first_temporary_index */
  frame->slots[4] = myself->closure.frame->slots[0]; /* break */
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 68: argument.is_an_identifier
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* argument */;
  result_count = 1;
  myself = get__is_an_identifier();
  func = myself->type;
  frame->cont = cont__6_21;
}
static void cont__6_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  frame->slots[7] /* temp__3 */ = create_closure(entry__6_22, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__6_31;
}
static void entry__6_22(void) {
  allocate_initialized_frame_gc(2, 7);
  // slot allocations:
  // argument: 0
  // output_arguments: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* argument */
  frame->slots[1] = myself->closure.frame->slots[2]; /* output_arguments */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 70: argument.is_a_single_assign_definition
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* argument */;
  result_count = 1;
  myself = get__is_a_single_assign_definition();
  func = myself->type;
  frame->cont = cont__6_23;
}
static void cont__6_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 71: length_of(output_arguments) == 1
  frame->slots[5] /* temp__4 */ = create_closure(entry__6_24, 0);
  // 69: &&
  // 70:   argument.is_a_single_assign_definition
  // 71:   length_of(output_arguments) == 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  arguments->slots[1] = frame->slots[5] /* temp__4 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__6_27;
}
static void entry__6_24(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // output_arguments: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* output_arguments */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 71: length_of(output_arguments)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* output_arguments */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__6_25;
}
static void cont__6_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 71: length_of(output_arguments) == 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__6_26;
}
static void cont__6_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 71: length_of(output_arguments) == 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__6_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 72: argument.is_a_multi_assign_definition
  frame->slots[6] /* temp__5 */ = create_closure(entry__6_28, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[6] /* temp__5 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__6_30;
}
static void entry__6_28(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // argument: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* argument */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 72: argument.is_a_multi_assign_definition
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* argument */;
  result_count = 1;
  myself = get__is_a_multi_assign_definition();
  func = myself->type;
  frame->cont = cont__6_29;
}
static void cont__6_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 72: argument.is_a_multi_assign_definition
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__6_30(void) {
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
static void cont__6_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 73: :
  // 74:   !first_temporary_index idx
  // 75:   break
  frame->slots[8] /* temp__4 */ = create_closure(entry__6_32, 0);
  // 66: unless
  // 67:   ||
  // 68:     argument.is_an_identifier
  // 69:     &&
  // 70:       argument.is_a_single_assign_definition
  // 71:       length_of(output_arguments) == 1
  // 72:     argument.is_a_multi_assign_definition
  // 73:   :
  // 74:     !first_temporary_index idx
  // 75:     break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__6_33(void) {
  myself = frame->slots[0] /* break */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__6_34(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 76: ... first_temporary_index.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* first_temporary_index */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__6_35;
}
static void cont__6_35(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 76: ... :
  // 77:   !final_destinations empty_list
  // 78:   update_each &output_arguments:
  // 79:     (
  // 80:       idx
  // 81:       &argument
  // 82:     )
  // 83:     if
  // 84:       idx < first_temporary_index || argument.is_a_temporary:
  // 85:         push &final_destinations undefined
  // ...
  frame->slots[5] /* temp__2 */ = create_closure(entry__6_36, 0);
  // 76: if first_temporary_index.is_defined:
  // 77:   !final_destinations empty_list
  // 78:   update_each &output_arguments:
  // 79:     (
  // 80:       idx
  // 81:       &argument
  // 82:     )
  // 83:     if
  // 84:       idx < first_temporary_index || argument.is_a_temporary:
  // 85:         push &final_destinations undefined
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__6_56;
}
static void entry__6_36(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // final_destinations: 0
  // output_arguments: 1
  // first_temporary_index: 2
  frame->slots[0] = myself->closure.frame->slots[1]; /* final_destinations */
  frame->slots[1] = myself->closure.frame->slots[0]; /* output_arguments */
  frame->slots[2] = myself->closure.frame->slots[3]; /* first_temporary_index */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 77: !final_destinations empty_list
  ((CELL *)frame->slots[0])->contents /* final_destinations */ = get__empty_list();
  // 78: ... :
  // 79:   (
  // 80:     idx
  // 81:     &argument
  // 82:   )
  // 83:   if
  // 84:     idx < first_temporary_index || argument.is_a_temporary:
  // 85:       push &final_destinations undefined
  // 86:     :
  // 87:       $$temp temporary_identifier()
  // ...
  frame->slots[3] /* temp__1 */ = create_closure(entry__6_37, 2);
  // 78: update_each &output_arguments:
  // 79:   (
  // 80:     idx
  // 81:     &argument
  // 82:   )
  // 83:   if
  // 84:     idx < first_temporary_index || argument.is_a_temporary:
  // 85:       push &final_destinations undefined
  // 86:     :
  // 87:       $$temp temporary_identifier()
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* output_arguments */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__update_each();
  func = myself->type;
  frame->cont = cont__6_55;
}
static void entry__6_37(void) {
  allocate_initialized_frame_gc(4, 9);
  // slot allocations:
  // idx: 0
  // argument: 1
  // first_temporary_index: 2
  // final_destinations: 3
  frame->slots[2] = myself->closure.frame->slots[2]; /* first_temporary_index */
  frame->slots[3] = myself->closure.frame->slots[0]; /* final_destinations */
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  frame->slots[1] /* argument */ = create_cell_with_contents(arguments->slots[1]);
  // 84: idx < first_temporary_index
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* idx */;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* first_temporary_index */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__6_38;
}
static void cont__6_38(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 84: ... argument.is_a_temporary
  frame->slots[6] /* temp__3 */ = create_closure(entry__6_39, 0);
  // 84: idx < first_temporary_index || argument.is_a_temporary
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__6_41;
}
static void entry__6_39(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // argument: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* argument */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 84: ... argument.is_a_temporary
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* argument */;
  result_count = 1;
  myself = get__is_a_temporary();
  func = myself->type;
  frame->cont = cont__6_40;
}
static void cont__6_40(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 84: ... argument.is_a_temporary
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__6_41(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 84: ... :
  // 85:   push &final_destinations undefined
  frame->slots[7] /* temp__4 */ = create_closure(entry__6_42, 0);
  // 86: :
  // 87:   $$temp temporary_identifier()
  // 88:   cond
  // 89:     -> argument.is_an_optional_item:
  // 90:       !argument.is_an_optional_item false
  // 91:       !temp.is_an_optional_item true
  // 92:     -> argument.is_an_expanded_item:
  // 93:       !argument.is_an_expanded_item false
  // 94:       !temp.is_an_expanded_item true
  // 95:   push &final_destinations argument
  // ...
  frame->slots[8] /* temp__5 */ = create_closure(entry__6_44, 0);
  // 83: if
  // 84:   idx < first_temporary_index || argument.is_a_temporary:
  // 85:     push &final_destinations undefined
  // 86:   :
  // 87:     $$temp temporary_identifier()
  // 88:     cond
  // 89:       -> argument.is_an_optional_item:
  // 90:         !argument.is_an_optional_item false
  // 91:         !temp.is_an_optional_item true
  // 92:       -> argument.is_an_expanded_item:
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__4 */;
  arguments->slots[2] = frame->slots[8] /* temp__5 */;
  result_count =
    frame->caller_result_count >= 1 ?
    frame->caller_result_count-1 : -1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__6_54;
}
static void entry__6_42(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // final_destinations: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* final_destinations */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 85: push &final_destinations undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* final_destinations */;
  arguments->slots[1] = get__undefined();
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__6_43;
}
static void cont__6_43(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* final_destinations */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__6_44(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // argument: 0
  // final_destinations: 1
  // temp: 2
  frame->slots[0] = myself->closure.frame->slots[1]; /* argument */
  frame->slots[1] = myself->closure.frame->slots[3]; /* final_destinations */
  frame->slots[2] /* temp */ = create_cell();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 87: $$temp temporary_identifier()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = var._temporary_identifier;
  func = myself->type;
  frame->cont = cont__6_45;
}
static void cont__6_45(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* temp */ = arguments->slots[0];
  // 89: -> argument.is_an_optional_item:
  // 90:   !argument.is_an_optional_item false
  // 91:   !temp.is_an_optional_item true
  frame->slots[3] /* temp__1 */ = create_closure(entry__6_46, 0);
  // 92: -> argument.is_an_expanded_item:
  // 93:   !argument.is_an_expanded_item false
  // 94:   !temp.is_an_expanded_item true
  frame->slots[4] /* temp__2 */ = create_closure(entry__6_49, 0);
  // 88: cond
  // 89:   -> argument.is_an_optional_item:
  // 90:     !argument.is_an_optional_item false
  // 91:     !temp.is_an_optional_item true
  // 92:   -> argument.is_an_expanded_item:
  // 93:     !argument.is_an_expanded_item false
  // 94:     !temp.is_an_expanded_item true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__cond();
  func = myself->type;
  frame->cont = cont__6_52;
}
static void entry__6_51(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // argument: 0
  // temp: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* argument */
  frame->slots[1] = myself->closure.frame->slots[1]; /* temp */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 93: !argument.is_an_expanded_item false
  frame->slots[2] /* temp__1 */ = get__false();
  // 93: !argument.is_an_expanded_item
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* argument */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__is_an_expanded_item, frame->slots[2] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* argument */ = temp;

  }
  // 94: !temp.is_an_expanded_item true
  frame->slots[2] /* temp__1 */ = get__true();
  // 94: !temp.is_an_expanded_item
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[1])->contents /* temp */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__is_an_expanded_item, frame->slots[2] /* temp__1 */);
    ((CELL *)frame->slots[1])->contents /* temp */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__6_48(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // argument: 0
  // temp: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* argument */
  frame->slots[1] = myself->closure.frame->slots[1]; /* temp */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 90: !argument.is_an_optional_item false
  frame->slots[2] /* temp__1 */ = get__false();
  // 90: !argument.is_an_optional_item
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* argument */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__is_an_optional_item, frame->slots[2] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* argument */ = temp;

  }
  // 91: !temp.is_an_optional_item true
  frame->slots[2] /* temp__1 */ = get__true();
  // 91: !temp.is_an_optional_item
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[1])->contents /* temp */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__is_an_optional_item, frame->slots[2] /* temp__1 */);
    ((CELL *)frame->slots[1])->contents /* temp */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__6_46(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // argument: 0
  // temp: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* argument */
  frame->slots[1] = myself->closure.frame->slots[2]; /* temp */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 89: ... argument.is_an_optional_item
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* argument */;
  result_count = 1;
  myself = get__is_an_optional_item();
  func = myself->type;
  frame->cont = cont__6_47;
}
static void cont__6_47(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 89: ... :
  // 90:   !argument.is_an_optional_item false
  // 91:   !temp.is_an_optional_item true
  frame->slots[3] /* temp__2 */ = create_closure(entry__6_48, 0);
  // 89: -> argument.is_an_optional_item:
  // 90:   !argument.is_an_optional_item false
  // 91:   !temp.is_an_optional_item true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__6_49(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // argument: 0
  // temp: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* argument */
  frame->slots[1] = myself->closure.frame->slots[2]; /* temp */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 92: ... argument.is_an_expanded_item
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* argument */;
  result_count = 1;
  myself = get__is_an_expanded_item();
  func = myself->type;
  frame->cont = cont__6_50;
}
static void cont__6_50(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 92: ... :
  // 93:   !argument.is_an_expanded_item false
  // 94:   !temp.is_an_expanded_item true
  frame->slots[3] /* temp__2 */ = create_closure(entry__6_51, 0);
  // 92: -> argument.is_an_expanded_item:
  // 93:   !argument.is_an_expanded_item false
  // 94:   !temp.is_an_expanded_item true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__6_52(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 95: push &final_destinations argument
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* final_destinations */;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* argument */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__6_53;
}
static void cont__6_53(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* final_destinations */ = arguments->slots[0];
  // 96: !argument temp
  ((CELL *)frame->slots[0])->contents /* argument */ = ((CELL *)frame->slots[2])->contents /* temp */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__6_54(void) {
  int i = argument_count;
  while (--i >= 0) {
    arguments->slots[i+1] = arguments->slots[i];
  }
  argument_count += 1;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* argument */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__6_55(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* output_arguments */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__6_56(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 97: !self.output_arguments_of output_arguments
  frame->slots[4] /* temp__1 */ = ((CELL *)frame->slots[0])->contents /* output_arguments */;
  // 97: !self.output_arguments_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[2])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__output_arguments_of, frame->slots[4] /* temp__1 */);
    ((CELL *)frame->slots[2])->contents /* self */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__6_57(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 98: -> final_destinations
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* final_destinations */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__7_31(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // info: 0
  // name: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* info */
  frame->slots[1] = myself->closure.frame->slots[1]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 117: ... identifier_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__7_32;
}
static void cont__7_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 117: ... "
  // 118:   Invalid access to dynamic read-write variable "@(name)@quot;@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__7_33;
  arguments->slots[1] = frame->slots[1] /* name */;
  arguments->slots[2] = string__7_34;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_35;
}
static void cont__7_35(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 117: SyntaxError identifier_of(info) "
  // 118:   Invalid access to dynamic read-write variable "@(name)@quot;@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__SyntaxError();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_23(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // info: 0
  // name: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* info */
  frame->slots[1] = myself->closure.frame->slots[1]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 113: ... identifier_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__7_24;
}
static void cont__7_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 113: ... "
  // 114:   Invalid access to dynamic read-only variable "@(name)@quot;@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__7_25;
  arguments->slots[1] = frame->slots[1] /* name */;
  arguments->slots[2] = string__7_26;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_27;
}
static void cont__7_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 113: SyntaxError identifier_of(info) "
  // 114:   Invalid access to dynamic read-only variable "@(name)@quot;@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__SyntaxError();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_15(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // info: 0
  // name: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* info */
  frame->slots[1] = myself->closure.frame->slots[1]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 109: ... identifier_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__7_16;
}
static void cont__7_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 109: ... "
  // 110:   Invalid access to static read-write variable "@(name)@quot;@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__7_17;
  arguments->slots[1] = frame->slots[1] /* name */;
  arguments->slots[2] = string__7_18;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_19;
}
static void cont__7_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 109: SyntaxError identifier_of(info) "
  // 110:   Invalid access to static read-write variable "@(name)@quot;@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__SyntaxError();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_7(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // info: 0
  // name: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* info */
  frame->slots[1] = myself->closure.frame->slots[1]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 105: ... identifier_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__7_8;
}
static void cont__7_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 105: ... "
  // 106:   Invalid access to read-only variable "@(name)@quot;@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__7_9;
  arguments->slots[1] = frame->slots[1] /* name */;
  arguments->slots[2] = string__7_10;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_11;
}
static void cont__7_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 105: SyntaxError identifier_of(info) "
  // 106:   Invalid access to read-only variable "@(name)@quot;@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__SyntaxError();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_4(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // info: 0
  // name: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* info */
  frame->slots[1] = myself->closure.frame->slots[0]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 104: ... variable_kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__variable_kind_of();
  func = myself->type;
  frame->cont = cont__7_5;
}
static void cont__7_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 104: ... STATIC_MULTI, DYNAMIC_SINGLE, DYNAMIC_MULTI
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__STATIC_MULTI();
  arguments->slots[1] = get__DYNAMIC_SINGLE();
  arguments->slots[2] = get__DYNAMIC_MULTI();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__7_6;
}
static void cont__7_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 104: ... :
  // 105:   SyntaxError identifier_of(info) "
  // 106:     Invalid access to read-only variable "@(name)@quot;@
  frame->slots[4] /* temp__3 */ = create_closure(entry__7_7, 0);
  // 104: case variable_kind_of(info) STATIC_MULTI, DYNAMIC_SINGLE, DYNAMIC_MULTI:
  // 105:   SyntaxError identifier_of(info) "
  // 106:     Invalid access to read-only variable "@(name)@quot;@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  arguments->slots[2] = frame->slots[4] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_12(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // info: 0
  // name: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* info */
  frame->slots[1] = myself->closure.frame->slots[0]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 108: ... variable_kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__variable_kind_of();
  func = myself->type;
  frame->cont = cont__7_13;
}
static void cont__7_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 108: ... DYNAMIC_SINGLE, DYNAMIC_MULTI
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__DYNAMIC_SINGLE();
  arguments->slots[1] = get__DYNAMIC_MULTI();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__7_14;
}
static void cont__7_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 108: ... :
  // 109:   SyntaxError identifier_of(info) "
  // 110:     Invalid access to static read-write variable "@(name)@quot;@
  frame->slots[4] /* temp__3 */ = create_closure(entry__7_15, 0);
  // 108: case variable_kind_of(info) DYNAMIC_SINGLE, DYNAMIC_MULTI:
  // 109:   SyntaxError identifier_of(info) "
  // 110:     Invalid access to static read-write variable "@(name)@quot;@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  arguments->slots[2] = frame->slots[4] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_20(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // info: 0
  // name: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* info */
  frame->slots[1] = myself->closure.frame->slots[0]; /* name */
  if (argument_count != 0) {
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
  frame->cont = cont__7_21;
}
static void cont__7_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 112: ... POLYMORPHIC, STATIC_MULTI, DYNAMIC_MULTI
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__POLYMORPHIC();
  arguments->slots[1] = get__STATIC_MULTI();
  arguments->slots[2] = get__DYNAMIC_MULTI();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__7_22;
}
static void cont__7_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 112: ... :
  // 113:   SyntaxError identifier_of(info) "
  // 114:     Invalid access to dynamic read-only variable "@(name)@quot;@
  frame->slots[4] /* temp__3 */ = create_closure(entry__7_23, 0);
  // 112: case variable_kind_of(info) POLYMORPHIC, STATIC_MULTI, DYNAMIC_MULTI:
  // 113:   SyntaxError identifier_of(info) "
  // 114:     Invalid access to dynamic read-only variable "@(name)@quot;@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  arguments->slots[2] = frame->slots[4] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_28(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // info: 0
  // name: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* info */
  frame->slots[1] = myself->closure.frame->slots[0]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 116: ... variable_kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__variable_kind_of();
  func = myself->type;
  frame->cont = cont__7_29;
}
static void cont__7_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 116: ... POLYMORPHIC, DYNAMIC_SINGLE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__POLYMORPHIC();
  arguments->slots[1] = get__DYNAMIC_SINGLE();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__7_30;
}
static void cont__7_30(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 116: ... :
  // 117:   SyntaxError identifier_of(info) "
  // 118:     Invalid access to dynamic read-write variable "@(name)@quot;@
  frame->slots[4] /* temp__3 */ = create_closure(entry__7_31, 0);
  // 116: case variable_kind_of(info) POLYMORPHIC, DYNAMIC_SINGLE:
  // 117:   SyntaxError identifier_of(info) "
  // 118:     Invalid access to dynamic read-write variable "@(name)@quot;@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  arguments->slots[2] = frame->slots[4] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_1(void) {
  allocate_initialized_frame_gc(3, 9);
  // slot allocations:
  // name: 0
  // definition: 1
  // info: 2
  if (argument_count != 3) {
    invalid_arguments_error();
    return;
  }
  // 102: variable_kind_of(definition)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* definition */;
  result_count = 1;
  myself = get__variable_kind_of();
  func = myself->type;
  frame->cont = cont__7_2;
}
static void cont__7_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 103: STATIC_SINGLE, POLYMORPHIC
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__STATIC_SINGLE();
  arguments->slots[1] = get__POLYMORPHIC();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__7_3;
}
static void cont__7_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 103: ... :
  // 104:   case variable_kind_of(info) STATIC_MULTI, DYNAMIC_SINGLE, DYNAMIC_MULTI:
  // 105:     SyntaxError identifier_of(info) "
  // 106:       Invalid access to read-only variable "@(name)@quot;@
  frame->slots[5] /* temp__3 */ = create_closure(entry__7_4, 0);
  // 107: ... :
  // 108:   case variable_kind_of(info) DYNAMIC_SINGLE, DYNAMIC_MULTI:
  // 109:     SyntaxError identifier_of(info) "
  // 110:       Invalid access to static read-write variable "@(name)@quot;@
  frame->slots[6] /* temp__4 */ = create_closure(entry__7_12, 0);
  // 111: ... :
  // 112:   case variable_kind_of(info) POLYMORPHIC, STATIC_MULTI, DYNAMIC_MULTI:
  // 113:     SyntaxError identifier_of(info) "
  // 114:       Invalid access to dynamic read-only variable "@(name)@quot;@
  frame->slots[7] /* temp__5 */ = create_closure(entry__7_20, 0);
  // 115: ... :
  // 116:   case variable_kind_of(info) POLYMORPHIC, DYNAMIC_SINGLE:
  // 117:     SyntaxError identifier_of(info) "
  // 118:       Invalid access to dynamic read-write variable "@(name)@quot;@
  frame->slots[8] /* temp__6 */ = create_closure(entry__7_28, 0);
  // 101: case
  // 102:   variable_kind_of(definition)
  // 103:   STATIC_SINGLE, POLYMORPHIC:
  // 104:     case variable_kind_of(info) STATIC_MULTI, DYNAMIC_SINGLE, DYNAMIC_MULTI:
  // 105:       SyntaxError identifier_of(info) "
  // 106:         Invalid access to read-only variable "@(name)@quot;@
  // 107:   STATIC_MULTI:
  // 108:     case variable_kind_of(info) DYNAMIC_SINGLE, DYNAMIC_MULTI:
  // 109:       SyntaxError identifier_of(info) "
  // 110:         Invalid access to static read-write variable "@(name)@quot;@
  // ...
  argument_count = 9;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  arguments->slots[2] = frame->slots[5] /* temp__3 */;
  arguments->slots[3] = get__STATIC_MULTI();
  arguments->slots[4] = frame->slots[6] /* temp__4 */;
  arguments->slots[5] = get__DYNAMIC_SINGLE();
  arguments->slots[6] = frame->slots[7] /* temp__5 */;
  arguments->slots[7] = get__DYNAMIC_MULTI();
  arguments->slots[8] = frame->slots[8] /* temp__6 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__8_1(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // self: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 124: show_compiler_debug_info "simplify statement (default)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__8_2;
  result_count = 0;
  myself = get__show_compiler_debug_info();
  func = myself->type;
  frame->cont = cont__8_3;
}
static void cont__8_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 125: push &statements self
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__statements();
  arguments->slots[1] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__8_4;
}
static void cont__8_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__statements(arguments->slots[0]);
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__9_1(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // self: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* self */ = create_cell_with_contents(arguments->slots[0]);
  // 128: show_compiler_debug_info "simplify expression (default)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__9_2;
  result_count =
    frame->caller_result_count >= 1 ?
    frame->caller_result_count-1 : -1;
  myself = get__show_compiler_debug_info();
  func = myself->type;
  frame->cont = cont__9_3;
}
static void cont__9_3(void) {
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
static void entry__10_1(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // self: 0
  // all_defined_names: 1
  frame->slots[1] /* all_defined_names */ = create_cell();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* self */ = create_cell_with_contents(arguments->slots[0]);
  // 134: show_compiler_debug_info "simplify body"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__10_2;
  result_count = 0;
  myself = get__show_compiler_debug_info();
  func = myself->type;
  frame->cont = cont__10_3;
}
static void cont__10_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 135: $$all_defined_names already_defined_names
  ((CELL *)frame->slots[1])->contents /* all_defined_names */ = get__already_defined_names();
  // 136: ... defined_names_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__defined_names_of();
  func = myself->type;
  frame->cont = cont__10_4;
}
static void cont__10_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 136: ... : (name info)
  // 137:   $outer_info already_defined_names(name)
  // 138:   if
  // 139:     outer_info.is_defined:
  // 140:       SyntaxError identifier_of(info) "
  // 141:         An identifier named "@(name)" was already defined in an outer scope @
  // 142:         or in a used namespace@
  // 143:     :
  // 144:       !all_defined_names(name) info
  frame->slots[3] /* temp__2 */ = create_closure(entry__10_5, 2);
  // 136: for_each defined_names_of(self): (name info)
  // 137:   $outer_info already_defined_names(name)
  // 138:   if
  // 139:     outer_info.is_defined:
  // 140:       SyntaxError identifier_of(info) "
  // 141:         An identifier named "@(name)" was already defined in an outer scope @
  // 142:         or in a used namespace@
  // 143:     :
  // 144:       !all_defined_names(name) info
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__10_15;
}
static void entry__10_8(void) {
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
  // 140: ... identifier_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__10_9;
}
static void cont__10_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 140: ... "
  // 141:   An identifier named "@(name)" was already defined in an outer scope @
  // 142:   or in a used namespace@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__10_10;
  arguments->slots[1] = frame->slots[1] /* name */;
  arguments->slots[2] = string__10_11;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__10_12;
}
static void cont__10_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 140: SyntaxError identifier_of(info) "
  // 141:   An identifier named "@(name)" was already defined in an outer scope @
  // 142:   or in a used namespace@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__SyntaxError();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__10_13(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // all_defined_names: 0
  // name: 1
  // info: 2
  frame->slots[0] = myself->closure.frame->slots[2]; /* all_defined_names */
  frame->slots[1] = myself->closure.frame->slots[0]; /* name */
  frame->slots[2] = myself->closure.frame->slots[1]; /* info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 144: !all_defined_names(name) info
  frame->slots[3] /* temp__1 */ = frame->slots[2] /* info */;
  // 144: !all_defined_names(name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* name */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* all_defined_names */;
  func = myself->type;
  frame->cont = cont__10_14;
}
static void cont__10_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* all_defined_names */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__10_5(void) {
  allocate_initialized_frame_gc(3, 7);
  // slot allocations:
  // name: 0
  // info: 1
  // all_defined_names: 2
  // outer_info: 3
  frame->slots[2] = myself->closure.frame->slots[1]; /* all_defined_names */
  frame->slots[3] /* outer_info */ = create_future();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 137: $outer_info already_defined_names(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = get__already_defined_names();
  func = myself->type;
  frame->cont = cont__10_6;
}
static void cont__10_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* outer_info */, arguments->slots[0]);
  // 139: outer_info.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* outer_info */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__10_7;
}
static void cont__10_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 139: ... :
  // 140:   SyntaxError identifier_of(info) "
  // 141:     An identifier named "@(name)" was already defined in an outer scope @
  // 142:     or in a used namespace@
  frame->slots[5] /* temp__2 */ = create_closure(entry__10_8, 0);
  // 143: :
  // 144:   !all_defined_names(name) info
  frame->slots[6] /* temp__3 */ = create_closure(entry__10_13, 0);
  // 138: if
  // 139:   outer_info.is_defined:
  // 140:     SyntaxError identifier_of(info) "
  // 141:       An identifier named "@(name)" was already defined in an outer scope @
  // 142:       or in a used namespace@
  // 143:   :
  // 144:     !all_defined_names(name) info
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
static void cont__10_15(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 145: ... used_names_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__used_names_of();
  func = myself->type;
  frame->cont = cont__10_16;
}
static void cont__10_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 145: ... : (name info)
  // 146:   $definition all_defined_names(name)
  // 147:   if definition.is_defined:
  // 148:     check_usage name definition info
  // 149:     if defined_names(name).is_defined || inherited_names(name).is_defined:
  // 150:       !self.inherited_names_of(name) info
  frame->slots[3] /* temp__2 */ = create_closure(entry__10_17, 2);
  // 145: for_each used_names_of(self): (name info)
  // 146:   $definition all_defined_names(name)
  // 147:   if definition.is_defined:
  // 148:     check_usage name definition info
  // 149:     if defined_names(name).is_defined || inherited_names(name).is_defined:
  // 150:       !self.inherited_names_of(name) info
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__10_31;
}
static void entry__10_28(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // self: 0
  // name: 1
  // info: 2
  frame->slots[0] = myself->closure.frame->slots[3]; /* self */
  frame->slots[1] = myself->closure.frame->slots[0]; /* name */
  frame->slots[2] = myself->closure.frame->slots[2]; /* info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 150: !self.inherited_names_of(name) info
  frame->slots[3] /* temp__1 */ = frame->slots[2] /* info */;
  // 150: ... self.inherited_names_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__inherited_names_of();
  func = myself->type;
  frame->cont = cont__10_29;
}
static void cont__10_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 150: !self.inherited_names_of(name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* name */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = frame->slots[4] /* temp__2 */;
  func = myself->type;
  frame->cont = cont__10_30;
}
static void cont__10_30(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 150: !self.inherited_names_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__inherited_names_of, frame->slots[4] /* temp__2 */);
    ((CELL *)frame->slots[0])->contents /* self */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__10_20(void) {
  allocate_initialized_frame_gc(4, 9);
  // slot allocations:
  // name: 0
  // definition: 1
  // info: 2
  // self: 3
  frame->slots[0] = myself->closure.frame->slots[0]; /* name */
  frame->slots[1] = myself->closure.frame->slots[4]; /* definition */
  frame->slots[2] = myself->closure.frame->slots[1]; /* info */
  frame->slots[3] = myself->closure.frame->slots[3]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 148: check_usage name definition info
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = frame->slots[1] /* definition */;
  arguments->slots[2] = frame->slots[2] /* info */;
  result_count = 0;
  myself = get__check_usage();
  func = myself->type;
  frame->cont = cont__10_21;
}
static void cont__10_21(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 149: ... defined_names(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = get__defined_names();
  func = myself->type;
  frame->cont = cont__10_22;
}
static void cont__10_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 149: ... defined_names(name).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__3 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__10_23;
}
static void cont__10_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 149: ... inherited_names(name).is_defined
  frame->slots[7] /* temp__4 */ = create_closure(entry__10_24, 0);
  // 149: ... defined_names(name).is_defined || inherited_names(name).is_defined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__4 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__10_27;
}
static void entry__10_24(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 149: ... inherited_names(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = get__inherited_names();
  func = myself->type;
  frame->cont = cont__10_25;
}
static void cont__10_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 149: ... inherited_names(name).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__10_26;
}
static void cont__10_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 149: ... inherited_names(name).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__10_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 149: ... :
  // 150:   !self.inherited_names_of(name) info
  frame->slots[8] /* temp__5 */ = create_closure(entry__10_28, 0);
  // 149: if defined_names(name).is_defined || inherited_names(name).is_defined:
  // 150:   !self.inherited_names_of(name) info
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__5 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__10_17(void) {
  allocate_initialized_frame_gc(4, 7);
  // slot allocations:
  // name: 0
  // info: 1
  // all_defined_names: 2
  // self: 3
  // definition: 4
  frame->slots[2] = myself->closure.frame->slots[1]; /* all_defined_names */
  frame->slots[3] = myself->closure.frame->slots[0]; /* self */
  frame->slots[4] /* definition */ = create_future();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 146: $definition all_defined_names(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = ((CELL *)frame->slots[2])->contents /* all_defined_names */;
  func = myself->type;
  frame->cont = cont__10_18;
}
static void cont__10_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* definition */, arguments->slots[0]);
  // 147: ... definition.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* definition */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__10_19;
}
static void cont__10_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 147: ... :
  // 148:   check_usage name definition info
  // 149:   if defined_names(name).is_defined || inherited_names(name).is_defined:
  // 150:     !self.inherited_names_of(name) info
  frame->slots[6] /* temp__2 */ = create_closure(entry__10_20, 0);
  // 147: if definition.is_defined:
  // 148:   check_usage name definition info
  // 149:   if defined_names(name).is_defined || inherited_names(name).is_defined:
  // 150:     !self.inherited_names_of(name) info
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__10_31(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 151: ... :
  // 152:   %defined_names defined_names_of(self)
  // 153:   %inherited_names inherited_names_of(self)
  // 154:   %already_defined_names all_defined_names
  // 155:   %%definitions empty_list
  // 156:   %%statements empty_list
  // 157:   $$max_temp_idx 0
  // 158:   update_each &self.parameters_of: (&parameter)
  // 159:     $$default_value default_value_of(parameter)
  // 160:     if default_value.is_defined:
  // ...
  frame->slots[2] /* temp__1 */ = create_closure(entry__10_32, 0);
  // 151: do:
  // 152:   %defined_names defined_names_of(self)
  // 153:   %inherited_names inherited_names_of(self)
  // 154:   %already_defined_names all_defined_names
  // 155:   %%definitions empty_list
  // 156:   %%statements empty_list
  // 157:   $$max_temp_idx 0
  // 158:   update_each &self.parameters_of: (&parameter)
  // 159:     $$default_value default_value_of(parameter)
  // 160:     if default_value.is_defined:
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__10_92;
}
static void entry__10_32(void) {
  allocate_initialized_frame_gc(3, 7);
  // slot allocations:
  // return__4: 0
  // self: 1
  // all_defined_names: 2
  // max_temp_idx: 3
  frame->slots[0] /* return__4 */ = create_continuation();
  frame->slots[1] = myself->closure.frame->slots[0]; /* self */
  frame->slots[2] = myself->closure.frame->slots[1]; /* all_defined_names */
  define__defined_names(create_future());
  define__inherited_names(create_future());
  // _define %already_defined_names all_defined_names
  define__already_defined_names(create_future());
  define__definitions(undefined);
  define__statements(undefined);
  frame->slots[3] /* max_temp_idx */ = create_cell();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 152: %defined_names defined_names_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* self */;
  result_count = 1;
  myself = get__defined_names_of();
  func = myself->type;
  frame->cont = cont__10_33;
}
static void cont__10_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(get__defined_names(), arguments->slots[0]);
  // 153: %inherited_names inherited_names_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* self */;
  result_count = 1;
  myself = get__inherited_names_of();
  func = myself->type;
  frame->cont = cont__10_34;
}
static void cont__10_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(get__inherited_names(), arguments->slots[0]);
  // 154: %already_defined_names all_defined_names
  initialize_maybe_future(get__already_defined_names(), ((CELL *)frame->slots[2])->contents /* all_defined_names */);
  // 155: %%definitions empty_list
  set__definitions(get__empty_list());
  // 156: %%statements empty_list
  set__statements(get__empty_list());
  // 157: $$max_temp_idx 0
  ((CELL *)frame->slots[3])->contents /* max_temp_idx */ = number__0;
  // 158: ... self.parameters_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* self */;
  result_count = 1;
  myself = get__parameters_of();
  func = myself->type;
  frame->cont = cont__10_35;
}
static void cont__10_35(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 158: ... : (&parameter)
  // 159:   $$default_value default_value_of(parameter)
  // 160:   if default_value.is_defined:
  // 161:     if
  // 162:       default_value.is_a_function_call:
  // 163:         %%statements empty_list
  // 164:         %%sim2c::temp_idx 0
  // 165:         $identifier identifier_of(parameter)
  // 166:         simplify_statement
  // 167:           assignment
  // ...
  frame->slots[5] /* temp__2 */ = create_closure(entry__10_36, 1);
  // 158: update_each &self.parameters_of: (&parameter)
  // 159:   $$default_value default_value_of(parameter)
  // 160:   if default_value.is_defined:
  // 161:     if
  // 162:       default_value.is_a_function_call:
  // 163:         %%statements empty_list
  // 164:         %%sim2c::temp_idx 0
  // 165:         $identifier identifier_of(parameter)
  // 166:         simplify_statement
  // 167:           assignment
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__update_each();
  func = myself->type;
  frame->cont = cont__10_53;
}
static void entry__10_36(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // parameter: 0
  // max_temp_idx: 1
  // default_value: 2
  frame->slots[1] = myself->closure.frame->slots[3]; /* max_temp_idx */
  frame->slots[2] /* default_value */ = create_cell();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* parameter */ = create_cell_with_contents(arguments->slots[0]);
  // 159: $$default_value default_value_of(parameter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* parameter */;
  result_count = 1;
  myself = get__default_value_of();
  func = myself->type;
  frame->cont = cont__10_37;
}
static void cont__10_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* default_value */ = arguments->slots[0];
  // 160: ... default_value.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* default_value */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__10_38;
}
static void cont__10_38(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 160: ... :
  // 161:   if
  // 162:     default_value.is_a_function_call:
  // 163:       %%statements empty_list
  // 164:       %%sim2c::temp_idx 0
  // 165:       $identifier identifier_of(parameter)
  // 166:       simplify_statement
  // 167:         assignment
  // 168:           .output_arguments_of list(parameter(.is_an_optional_item false))
  // 169:           .arguments_of list(default_value)
  // ...
  frame->slots[4] /* temp__2 */ = create_closure(entry__10_39, 0);
  // 160: if default_value.is_defined:
  // 161:   if
  // 162:     default_value.is_a_function_call:
  // 163:       %%statements empty_list
  // 164:       %%sim2c::temp_idx 0
  // 165:       $identifier identifier_of(parameter)
  // 166:       simplify_statement
  // 167:         assignment
  // 168:           .output_arguments_of list(parameter(.is_an_optional_item false))
  // 169:           .arguments_of list(default_value)
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count =
    frame->caller_result_count >= 1 ?
    frame->caller_result_count-1 : -1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__10_52;
}
static void entry__10_41(void) {
  allocate_initialized_frame_gc(4, 12);
  // slot allocations:
  // return__1: 0
  // parameter: 1
  // default_value: 2
  // max_temp_idx: 3
  // identifier: 4
  frame->slots[0] /* return__1 */ = create_continuation();
  frame->slots[1] = myself->closure.frame->slots[1]; /* parameter */
  frame->slots[2] = myself->closure.frame->slots[0]; /* default_value */
  frame->slots[3] = myself->closure.frame->slots[2]; /* max_temp_idx */
  define__statements(undefined);
  define__sim2c__temp_idx(undefined);
  frame->slots[4] /* identifier */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 163: %%statements empty_list
  set__statements(get__empty_list());
  // 164: %%sim2c::temp_idx 0
  set__sim2c__temp_idx(number__0);
  // 165: $identifier identifier_of(parameter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* parameter */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__10_42;
}
static void cont__10_42(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* identifier */, arguments->slots[0]);
  // 168: ... parameter(.is_an_optional_item false)
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[1])->contents /* parameter */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__is_an_optional_item, get__false());
    frame->slots[7] /* temp__3 */ = temp;

  }
  // 168: ... list(parameter(.is_an_optional_item false))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__10_43;
}
static void cont__10_43(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 169: ... list(default_value)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* default_value */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__10_44;
}
static void cont__10_44(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__4 */ = arguments->slots[0];
  // 170: ... fragment_of(identifier)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* identifier */;
  result_count = 1;
  myself = get__fragment_of();
  func = myself->type;
  frame->cont = cont__10_45;
}
static void cont__10_45(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__5 */ = arguments->slots[0];
  // 171: ... source_position_of(identifier)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* identifier */;
  result_count = 1;
  myself = get__source_position_of();
  func = myself->type;
  frame->cont = cont__10_46;
}
static void cont__10_46(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__6 */ = arguments->slots[0];
  // 172: ... end_position_of(identifier)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* identifier */;
  result_count = 1;
  myself = get__end_position_of();
  func = myself->type;
  frame->cont = cont__10_47;
}
static void cont__10_47(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__7 */ = arguments->slots[0];
  // 167: assignment
  // 168:   .output_arguments_of list(parameter(.is_an_optional_item false))
  // 169:   .arguments_of list(default_value)
  // 170:   .fragment_of fragment_of(identifier)
  // 171:   .source_position_of source_position_of(identifier)
  // 172:   .end_position_of end_position_of(identifier)
  {
    NODE *temp = clone_object_and_attributes(get__assignment());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__output_arguments_of, frame->slots[6] /* temp__2 */);
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[8] /* temp__4 */);
    set_attribute_value(temp->attributes, poly_idx__fragment_of, frame->slots[9] /* temp__5 */);
    set_attribute_value(temp->attributes, poly_idx__source_position_of, frame->slots[10] /* temp__6 */);
    set_attribute_value(temp->attributes, poly_idx__end_position_of, frame->slots[11] /* temp__7 */);
    frame->slots[5] /* temp__1 */ = temp;

  }
  // 166: simplify_statement
  // 167:   assignment
  // 168:     .output_arguments_of list(parameter(.is_an_optional_item false))
  // 169:     .arguments_of list(default_value)
  // 170:     .fragment_of fragment_of(identifier)
  // 171:     .source_position_of source_position_of(identifier)
  // 172:     .end_position_of end_position_of(identifier)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  result_count = 0;
  myself = get__simplify_statement();
  func = myself->type;
  frame->cont = cont__10_48;
}
static void cont__10_48(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 173: extend_to &max_temp_idx temp_idx
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* max_temp_idx */;
  arguments->slots[1] = get__temp_idx();
  result_count = 1;
  myself = get__extend_to();
  func = myself->type;
  frame->cont = cont__10_49;
}
static void cont__10_49(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* max_temp_idx */ = arguments->slots[0];
  // 174: !parameter.statements_of statements
  frame->slots[5] /* temp__1 */ = get__statements();
  // 174: !parameter.statements_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[1])->contents /* parameter */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__statements_of, frame->slots[5] /* temp__1 */);
    ((CELL *)frame->slots[1])->contents /* parameter */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  myself = frame->slots[0] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__10_50(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // default_value: 0
  // parameter: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* default_value */
  frame->slots[1] = myself->closure.frame->slots[1]; /* parameter */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 176: simplify_expression &default_value
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* default_value */;
  result_count = 1;
  myself = get__simplify_expression();
  func = myself->type;
  frame->cont = cont__10_51;
}
static void cont__10_51(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* default_value */ = arguments->slots[0];
  // 177: !parameter.default_value_of default_value
  frame->slots[2] /* temp__1 */ = ((CELL *)frame->slots[0])->contents /* default_value */;
  // 177: !parameter.default_value_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[1])->contents /* parameter */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__default_value_of, frame->slots[2] /* temp__1 */);
    ((CELL *)frame->slots[1])->contents /* parameter */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__10_39(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // default_value: 0
  // parameter: 1
  // max_temp_idx: 2
  frame->slots[0] = myself->closure.frame->slots[2]; /* default_value */
  frame->slots[1] = myself->closure.frame->slots[0]; /* parameter */
  frame->slots[2] = myself->closure.frame->slots[1]; /* max_temp_idx */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 162: default_value.is_a_function_call
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* default_value */;
  result_count = 1;
  myself = get__is_a_function_call();
  func = myself->type;
  frame->cont = cont__10_40;
}
static void cont__10_40(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 162: ... :
  // 163:   %%statements empty_list
  // 164:   %%sim2c::temp_idx 0
  // 165:   $identifier identifier_of(parameter)
  // 166:   simplify_statement
  // 167:     assignment
  // 168:       .output_arguments_of list(parameter(.is_an_optional_item false))
  // 169:       .arguments_of list(default_value)
  // 170:       .fragment_of fragment_of(identifier)
  // 171:       .source_position_of source_position_of(identifier)
  // ...
  frame->slots[4] /* temp__2 */ = create_closure(entry__10_41, 0);
  // 175: :
  // 176:   simplify_expression &default_value
  // 177:   !parameter.default_value_of default_value
  frame->slots[5] /* temp__3 */ = create_closure(entry__10_50, 0);
  // 161: if
  // 162:   default_value.is_a_function_call:
  // 163:     %%statements empty_list
  // 164:     %%sim2c::temp_idx 0
  // 165:     $identifier identifier_of(parameter)
  // 166:     simplify_statement
  // 167:       assignment
  // 168:         .output_arguments_of list(parameter(.is_an_optional_item false))
  // 169:         .arguments_of list(default_value)
  // 170:         .fragment_of fragment_of(identifier)
  // ...
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
static void cont__10_52(void) {
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
static void cont__10_53(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 158: ... &self.parameters_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[1])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__parameters_of, frame->slots[6] /* temp__3 */);
    ((CELL *)frame->slots[1])->contents /* self */ = temp;

  }
  // 181: ... statements_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* self */;
  result_count = 1;
  myself = get__statements_of();
  func = myself->type;
  frame->cont = cont__10_54;
}
static void cont__10_54(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 181: ... : (statement)
  // 182:   unless statement.is_a_remark:
  // 183:     if
  // 184:       &&
  // 185:         statement.is_an_assignment
  // 186:         output_arguments_of(statement)(1).is_a_static_single_definition
  // 187:         arguments_of(statement)(1).is_a_constant
  // 188:       :
  // 189:         %%sim2c::temp_idx 0
  // 190:         simplify_statement statement
  // ...
  frame->slots[5] /* temp__2 */ = create_closure(entry__10_55, 1);
  // 181: for_each statements_of(self): (statement)
  // 182:   unless statement.is_a_remark:
  // 183:     if
  // 184:       &&
  // 185:         statement.is_an_assignment
  // 186:         output_arguments_of(statement)(1).is_a_static_single_definition
  // 187:         arguments_of(statement)(1).is_a_constant
  // 188:       :
  // 189:         %%sim2c::temp_idx 0
  // 190:         simplify_statement statement
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__10_72;
}
static void entry__10_69(void) {
  allocate_initialized_frame_gc(3, 3);
  // slot allocations:
  // return__2: 0
  // statement: 1
  // max_temp_idx: 2
  frame->slots[0] /* return__2 */ = create_continuation();
  frame->slots[1] = myself->closure.frame->slots[0]; /* statement */
  frame->slots[2] = myself->closure.frame->slots[1]; /* max_temp_idx */
  define__sim2c__temp_idx(undefined);
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 189: %%sim2c::temp_idx 0
  set__sim2c__temp_idx(number__0);
  // 190: simplify_statement statement
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* statement */;
  result_count = 0;
  myself = get__simplify_statement();
  func = myself->type;
  frame->cont = cont__10_70;
}
static void cont__10_70(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 191: extend_to &max_temp_idx temp_idx
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* max_temp_idx */;
  arguments->slots[1] = get__temp_idx();
  result_count = 1;
  myself = get__extend_to();
  func = myself->type;
  frame->cont = cont__10_71;
}
static void cont__10_71(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* max_temp_idx */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  myself = frame->slots[0] /* return__2 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__10_57(void) {
  allocate_initialized_frame_gc(2, 6);
  // slot allocations:
  // statement: 0
  // max_temp_idx: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* statement */
  frame->slots[1] = myself->closure.frame->slots[1]; /* max_temp_idx */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 185: statement.is_an_assignment
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* statement */;
  result_count = 1;
  myself = get__is_an_assignment();
  func = myself->type;
  frame->cont = cont__10_58;
}
static void cont__10_58(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  frame->slots[4] /* temp__3 */ = create_closure(entry__10_59, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__10_68;
}
static void entry__10_59(void) {
  allocate_initialized_frame_gc(1, 6);
  // slot allocations:
  // statement: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* statement */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 186: output_arguments_of(statement)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* statement */;
  result_count = 1;
  myself = get__output_arguments_of();
  func = myself->type;
  frame->cont = cont__10_60;
}
static void cont__10_60(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__4 */ = arguments->slots[0];
  // 186: output_arguments_of(statement)(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[4] /* temp__4 */;
  func = myself->type;
  frame->cont = cont__10_61;
}
static void cont__10_61(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 186: output_arguments_of(statement)(1).is_a_static_single_definition
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__is_a_static_single_definition();
  func = myself->type;
  frame->cont = cont__10_62;
}
static void cont__10_62(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 187: arguments_of(statement)(1).is_a_constant
  frame->slots[5] /* temp__5 */ = create_closure(entry__10_63, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__5 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__10_67;
}
static void entry__10_63(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // statement: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* statement */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 187: arguments_of(statement)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* statement */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__10_64;
}
static void cont__10_64(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 187: arguments_of(statement)(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[3] /* temp__3 */;
  func = myself->type;
  frame->cont = cont__10_65;
}
static void cont__10_65(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 187: arguments_of(statement)(1).is_a_constant
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__is_a_constant();
  func = myself->type;
  frame->cont = cont__10_66;
}
static void cont__10_66(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 187: arguments_of(statement)(1).is_a_constant
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__10_67(void) {
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
static void cont__10_68(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 188: :
  // 189:   %%sim2c::temp_idx 0
  // 190:   simplify_statement statement
  // 191:   extend_to &max_temp_idx temp_idx
  frame->slots[5] /* temp__4 */ = create_closure(entry__10_69, 0);
  // 183: if
  // 184:   &&
  // 185:     statement.is_an_assignment
  // 186:     output_arguments_of(statement)(1).is_a_static_single_definition
  // 187:     arguments_of(statement)(1).is_a_constant
  // 188:   :
  // 189:     %%sim2c::temp_idx 0
  // 190:     simplify_statement statement
  // 191:     extend_to &max_temp_idx temp_idx
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__10_55(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // statement: 0
  // max_temp_idx: 1
  frame->slots[1] = myself->closure.frame->slots[3]; /* max_temp_idx */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 182: ... statement.is_a_remark
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* statement */;
  result_count = 1;
  myself = get__is_a_remark();
  func = myself->type;
  frame->cont = cont__10_56;
}
static void cont__10_56(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 182: ... :
  // 183:   if
  // 184:     &&
  // 185:       statement.is_an_assignment
  // 186:       output_arguments_of(statement)(1).is_a_static_single_definition
  // 187:       arguments_of(statement)(1).is_a_constant
  // 188:     :
  // 189:       %%sim2c::temp_idx 0
  // 190:       simplify_statement statement
  // 191:       extend_to &max_temp_idx temp_idx
  frame->slots[3] /* temp__2 */ = create_closure(entry__10_57, 0);
  // 182: unless statement.is_a_remark:
  // 183:   if
  // 184:     &&
  // 185:       statement.is_an_assignment
  // 186:       output_arguments_of(statement)(1).is_a_static_single_definition
  // 187:       arguments_of(statement)(1).is_a_constant
  // 188:     :
  // 189:       %%sim2c::temp_idx 0
  // 190:       simplify_statement statement
  // 191:       extend_to &max_temp_idx temp_idx
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__10_72(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 195: ... statements_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* self */;
  result_count = 1;
  myself = get__statements_of();
  func = myself->type;
  frame->cont = cont__10_73;
}
static void cont__10_73(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 195: ... : (statement)
  // 196:   unless statement.is_a_remark:
  // 197:     unless
  // 198:       &&
  // 199:         statement.is_an_assignment
  // 200:         output_arguments_of(statement)(1).is_a_static_single_definition
  // 201:         arguments_of(statement)(1).is_a_constant
  // 202:       :
  // 203:         %%sim2c::temp_idx 0
  // 204:         simplify_statement statement
  // ...
  frame->slots[5] /* temp__2 */ = create_closure(entry__10_74, 1);
  // 195: for_each statements_of(self): (statement)
  // 196:   unless statement.is_a_remark:
  // 197:     unless
  // 198:       &&
  // 199:         statement.is_an_assignment
  // 200:         output_arguments_of(statement)(1).is_a_static_single_definition
  // 201:         arguments_of(statement)(1).is_a_constant
  // 202:       :
  // 203:         %%sim2c::temp_idx 0
  // 204:         simplify_statement statement
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__10_91;
}
static void entry__10_88(void) {
  allocate_initialized_frame_gc(3, 3);
  // slot allocations:
  // return__3: 0
  // statement: 1
  // max_temp_idx: 2
  frame->slots[0] /* return__3 */ = create_continuation();
  frame->slots[1] = myself->closure.frame->slots[0]; /* statement */
  frame->slots[2] = myself->closure.frame->slots[1]; /* max_temp_idx */
  define__sim2c__temp_idx(undefined);
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 203: %%sim2c::temp_idx 0
  set__sim2c__temp_idx(number__0);
  // 204: simplify_statement statement
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* statement */;
  result_count = 0;
  myself = get__simplify_statement();
  func = myself->type;
  frame->cont = cont__10_89;
}
static void cont__10_89(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 205: extend_to &max_temp_idx temp_idx
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* max_temp_idx */;
  arguments->slots[1] = get__temp_idx();
  result_count = 1;
  myself = get__extend_to();
  func = myself->type;
  frame->cont = cont__10_90;
}
static void cont__10_90(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* max_temp_idx */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  myself = frame->slots[0] /* return__3 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__10_76(void) {
  allocate_initialized_frame_gc(2, 6);
  // slot allocations:
  // statement: 0
  // max_temp_idx: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* statement */
  frame->slots[1] = myself->closure.frame->slots[1]; /* max_temp_idx */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 199: statement.is_an_assignment
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* statement */;
  result_count = 1;
  myself = get__is_an_assignment();
  func = myself->type;
  frame->cont = cont__10_77;
}
static void cont__10_77(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  frame->slots[4] /* temp__3 */ = create_closure(entry__10_78, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__10_87;
}
static void entry__10_78(void) {
  allocate_initialized_frame_gc(1, 6);
  // slot allocations:
  // statement: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* statement */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 200: output_arguments_of(statement)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* statement */;
  result_count = 1;
  myself = get__output_arguments_of();
  func = myself->type;
  frame->cont = cont__10_79;
}
static void cont__10_79(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__4 */ = arguments->slots[0];
  // 200: output_arguments_of(statement)(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[4] /* temp__4 */;
  func = myself->type;
  frame->cont = cont__10_80;
}
static void cont__10_80(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 200: output_arguments_of(statement)(1).is_a_static_single_definition
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__is_a_static_single_definition();
  func = myself->type;
  frame->cont = cont__10_81;
}
static void cont__10_81(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 201: arguments_of(statement)(1).is_a_constant
  frame->slots[5] /* temp__5 */ = create_closure(entry__10_82, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__5 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__10_86;
}
static void entry__10_82(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // statement: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* statement */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 201: arguments_of(statement)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* statement */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__10_83;
}
static void cont__10_83(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 201: arguments_of(statement)(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[3] /* temp__3 */;
  func = myself->type;
  frame->cont = cont__10_84;
}
static void cont__10_84(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 201: arguments_of(statement)(1).is_a_constant
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__is_a_constant();
  func = myself->type;
  frame->cont = cont__10_85;
}
static void cont__10_85(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 201: arguments_of(statement)(1).is_a_constant
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__10_86(void) {
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
static void cont__10_87(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 202: :
  // 203:   %%sim2c::temp_idx 0
  // 204:   simplify_statement statement
  // 205:   extend_to &max_temp_idx temp_idx
  frame->slots[5] /* temp__4 */ = create_closure(entry__10_88, 0);
  // 197: unless
  // 198:   &&
  // 199:     statement.is_an_assignment
  // 200:     output_arguments_of(statement)(1).is_a_static_single_definition
  // 201:     arguments_of(statement)(1).is_a_constant
  // 202:   :
  // 203:     %%sim2c::temp_idx 0
  // 204:     simplify_statement statement
  // 205:     extend_to &max_temp_idx temp_idx
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__10_74(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // statement: 0
  // max_temp_idx: 1
  frame->slots[1] = myself->closure.frame->slots[3]; /* max_temp_idx */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 196: ... statement.is_a_remark
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* statement */;
  result_count = 1;
  myself = get__is_a_remark();
  func = myself->type;
  frame->cont = cont__10_75;
}
static void cont__10_75(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 196: ... :
  // 197:   unless
  // 198:     &&
  // 199:       statement.is_an_assignment
  // 200:       output_arguments_of(statement)(1).is_a_static_single_definition
  // 201:       arguments_of(statement)(1).is_a_constant
  // 202:     :
  // 203:       %%sim2c::temp_idx 0
  // 204:       simplify_statement statement
  // 205:       extend_to &max_temp_idx temp_idx
  frame->slots[3] /* temp__2 */ = create_closure(entry__10_76, 0);
  // 196: unless statement.is_a_remark:
  // 197:   unless
  // 198:     &&
  // 199:       statement.is_an_assignment
  // 200:       output_arguments_of(statement)(1).is_a_static_single_definition
  // 201:       arguments_of(statement)(1).is_a_constant
  // 202:     :
  // 203:       %%sim2c::temp_idx 0
  // 204:       simplify_statement statement
  // 205:       extend_to &max_temp_idx temp_idx
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__10_91(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 206: !self.definitions_of definitions
  frame->slots[4] /* temp__1 */ = get__definitions();
  // 206: !self.definitions_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[1])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__definitions_of, frame->slots[4] /* temp__1 */);
    ((CELL *)frame->slots[1])->contents /* self */ = temp;

  }
  // 207: !self.statements_of statements
  frame->slots[4] /* temp__1 */ = get__statements();
  // 207: !self.statements_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[1])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__statements_of, frame->slots[4] /* temp__1 */);
    ((CELL *)frame->slots[1])->contents /* self */ = temp;

  }
  // 208: !self.temporary_count_of max_temp_idx
  frame->slots[4] /* temp__1 */ = ((CELL *)frame->slots[3])->contents /* max_temp_idx */;
  // 208: !self.temporary_count_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[1])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__temporary_count_of, frame->slots[4] /* temp__1 */);
    ((CELL *)frame->slots[1])->contents /* self */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  myself = frame->slots[0] /* return__4 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__10_92(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 209: ... inherited_names_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__inherited_names_of();
  func = myself->type;
  frame->cont = cont__10_93;
}
static void cont__10_93(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 209: ... inherited_names_of(self).is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__10_94;
}
static void cont__10_94(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 209: ... :
  // 210:   #
  // 211:     a closure must be created in a separate step because it is not really
  // 212:     a constant
  // 213:   
  // 214:   $temp temporary_identifier()
  // 215:   push
  // 216:     &statements
  // 217:     assignment
  // 218:       .output_arguments_of list(temp)
  // ...
  frame->slots[4] /* temp__3 */ = create_closure(entry__10_95, 0);
  // 209: unless inherited_names_of(self).is_empty:
  // 210:   #
  // 211:     a closure must be created in a separate step because it is not really
  // 212:     a constant
  // 213:   
  // 214:   $temp temporary_identifier()
  // 215:   push
  // 216:     &statements
  // 217:     assignment
  // 218:       .output_arguments_of list(temp)
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count =
    frame->caller_result_count >= 1 ?
    frame->caller_result_count-1 : -1;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__10_103;
}
static void entry__10_95(void) {
  allocate_initialized_frame_gc(1, 8);
  // slot allocations:
  // self: 0
  // temp: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  frame->slots[1] /* temp */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 214: $temp temporary_identifier()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = var._temporary_identifier;
  func = myself->type;
  frame->cont = cont__10_96;
}
static void cont__10_96(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* temp */, arguments->slots[0]);
  // 218: ... list(temp)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__10_97;
}
static void cont__10_97(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 219: ... list(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__10_98;
}
static void cont__10_98(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 220: ... fragment_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__fragment_of();
  func = myself->type;
  frame->cont = cont__10_99;
}
static void cont__10_99(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__4 */ = arguments->slots[0];
  // 221: ... source_position_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__source_position_of();
  func = myself->type;
  frame->cont = cont__10_100;
}
static void cont__10_100(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__5 */ = arguments->slots[0];
  // 222: ... end_position_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__end_position_of();
  func = myself->type;
  frame->cont = cont__10_101;
}
static void cont__10_101(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__6 */ = arguments->slots[0];
  // 217: assignment
  // 218:   .output_arguments_of list(temp)
  // 219:   .arguments_of list(self)
  // 220:   .fragment_of fragment_of(self)
  // 221:   .source_position_of source_position_of(self)
  // 222:   .end_position_of end_position_of(self)
  {
    NODE *temp = clone_object_and_attributes(get__assignment());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__output_arguments_of, frame->slots[3] /* temp__2 */);
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[4] /* temp__3 */);
    set_attribute_value(temp->attributes, poly_idx__fragment_of, frame->slots[5] /* temp__4 */);
    set_attribute_value(temp->attributes, poly_idx__source_position_of, frame->slots[6] /* temp__5 */);
    set_attribute_value(temp->attributes, poly_idx__end_position_of, frame->slots[7] /* temp__6 */);
    frame->slots[2] /* temp__1 */ = temp;

  }
  // 215: push
  // 216:   &statements
  // 217:   assignment
  // 218:     .output_arguments_of list(temp)
  // 219:     .arguments_of list(self)
  // 220:     .fragment_of fragment_of(self)
  // 221:     .source_position_of source_position_of(self)
  // 222:     .end_position_of end_position_of(self)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__statements();
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__10_102;
}
static void cont__10_102(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__statements(arguments->slots[0]);
  // 223: !self temp
  ((CELL *)frame->slots[0])->contents /* self */ = frame->slots[1] /* temp */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__10_103(void) {
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
static void entry__11_4(void) {
  allocate_initialized_frame_gc(6, 13);
  // slot allocations:
  // arguments: 0
  // rest: 1
  // functor: 2
  // info: 3
  // result: 4
  // infos: 5
  frame->slots[0] = myself->closure.frame->slots[1]; /* arguments */
  frame->slots[1] = myself->closure.frame->slots[3]; /* rest */
  frame->slots[2] = myself->closure.frame->slots[0]; /* functor */
  frame->slots[3] = myself->closure.frame->slots[5]; /* info */
  frame->slots[4] = myself->closure.frame->slots[2]; /* result */
  frame->slots[5] = myself->closure.frame->slots[4]; /* infos */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 232: update_each &arguments: (&argument) simplify_expression &argument
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* arguments */;
  arguments->slots[1] = func__11_5;
  result_count = 1;
  myself = get__update_each();
  func = myself->type;
  frame->cont = cont__11_7;
}
static void entry__11_5(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // argument: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* argument */ = create_cell_with_contents(arguments->slots[0]);
  // 232: ... simplify_expression &argument
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* argument */;
  result_count = 1;
  myself = get__simplify_expression();
  func = myself->type;
  frame->cont = cont__11_6;
}
static void cont__11_6(void) {
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
static void cont__11_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* arguments */ = arguments->slots[0];
  // 233: ... length_of(rest)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* rest */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__11_8;
}
static void cont__11_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 233: ... length_of(rest) > 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__11_9;
}
static void cont__11_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 233: ... :
  // 234:   $temp temporary_identifier()
  // 235:   push
  // 236:     &statements
  // 237:     procedure_call
  // 238:       .functor_of functor
  // 239:       .arguments_of arguments
  // 240:       .output_arguments_of list(temp)
  // 241:       .fragment_of fragment_of(info)
  // 242:       .source_position_of source_position_of(info)
  // ...
  frame->slots[8] /* temp__3 */ = create_closure(entry__11_10, 0);
  // 233: if length_of(rest) > 0:
  // 234:   $temp temporary_identifier()
  // 235:   push
  // 236:     &statements
  // 237:     procedure_call
  // 238:       .functor_of functor
  // 239:       .arguments_of arguments
  // 240:       .output_arguments_of list(temp)
  // 241:       .fragment_of fragment_of(info)
  // 242:       .source_position_of source_position_of(info)
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__11_20;
}
static void entry__11_10(void) {
  allocate_initialized_frame_gc(6, 12);
  // slot allocations:
  // functor: 0
  // arguments: 1
  // info: 2
  // rest: 3
  // result: 4
  // infos: 5
  // temp: 6
  frame->slots[0] = myself->closure.frame->slots[2]; /* functor */
  frame->slots[1] = myself->closure.frame->slots[0]; /* arguments */
  frame->slots[2] = myself->closure.frame->slots[3]; /* info */
  frame->slots[3] = myself->closure.frame->slots[1]; /* rest */
  frame->slots[4] = myself->closure.frame->slots[4]; /* result */
  frame->slots[5] = myself->closure.frame->slots[5]; /* infos */
  frame->slots[6] /* temp */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 234: $temp temporary_identifier()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = var._temporary_identifier;
  func = myself->type;
  frame->cont = cont__11_11;
}
static void cont__11_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* temp */, arguments->slots[0]);
  // 240: ... list(temp)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__11_12;
}
static void cont__11_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__2 */ = arguments->slots[0];
  // 241: ... fragment_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* info */;
  result_count = 1;
  myself = get__fragment_of();
  func = myself->type;
  frame->cont = cont__11_13;
}
static void cont__11_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__3 */ = arguments->slots[0];
  // 242: ... source_position_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* info */;
  result_count = 1;
  myself = get__source_position_of();
  func = myself->type;
  frame->cont = cont__11_14;
}
static void cont__11_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__4 */ = arguments->slots[0];
  // 243: ... end_position_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* info */;
  result_count = 1;
  myself = get__end_position_of();
  func = myself->type;
  frame->cont = cont__11_15;
}
static void cont__11_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__5 */ = arguments->slots[0];
  // 237: procedure_call
  // 238:   .functor_of functor
  // 239:   .arguments_of arguments
  // 240:   .output_arguments_of list(temp)
  // 241:   .fragment_of fragment_of(info)
  // 242:   .source_position_of source_position_of(info)
  // 243:   .end_position_of end_position_of(info)
  {
    NODE *temp = clone_object_and_attributes(get__procedure_call());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__functor_of, frame->slots[0] /* functor */);
    set_attribute_value(temp->attributes, poly_idx__arguments_of, ((CELL *)frame->slots[1])->contents /* arguments */);
    set_attribute_value(temp->attributes, poly_idx__output_arguments_of, frame->slots[8] /* temp__2 */);
    set_attribute_value(temp->attributes, poly_idx__fragment_of, frame->slots[9] /* temp__3 */);
    set_attribute_value(temp->attributes, poly_idx__source_position_of, frame->slots[10] /* temp__4 */);
    set_attribute_value(temp->attributes, poly_idx__end_position_of, frame->slots[11] /* temp__5 */);
    frame->slots[7] /* temp__1 */ = temp;

  }
  // 235: push
  // 236:   &statements
  // 237:   procedure_call
  // 238:     .functor_of functor
  // 239:     .arguments_of arguments
  // 240:     .output_arguments_of list(temp)
  // 241:     .fragment_of fragment_of(info)
  // 242:     .source_position_of source_position_of(info)
  // 243:     .end_position_of end_position_of(info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__statements();
  arguments->slots[1] = frame->slots[7] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__11_16;
}
static void cont__11_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__statements(arguments->slots[0]);
  // 244: ... rest.peek
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* rest */;
  result_count = 1;
  myself = get__peek();
  func = myself->type;
  frame->cont = cont__11_17;
}
static void cont__11_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 244: ... rest.drop
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* rest */;
  result_count = 1;
  myself = get__drop();
  func = myself->type;
  frame->cont = cont__11_18;
}
static void cont__11_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__2 */ = arguments->slots[0];
  // 244: do_store temp rest.peek result rest.drop infos
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp */;
  arguments->slots[1] = frame->slots[7] /* temp__1 */;
  arguments->slots[2] = ((CELL *)frame->slots[4])->contents /* result */;
  arguments->slots[3] = frame->slots[8] /* temp__2 */;
  arguments->slots[4] = ((CELL *)frame->slots[5])->contents /* infos */;
  result_count = 0;
  myself = var._do_store;
  func = myself->type;
  frame->cont = cont__11_19;
}
static void cont__11_19(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 245: !result temp
  ((CELL *)frame->slots[4])->contents /* result */ = frame->slots[6] /* temp */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__11_20(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 250: ... push(arguments result)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* arguments */;
  arguments->slots[1] = ((CELL *)frame->slots[4])->contents /* result */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__11_21;
}
static void cont__11_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 251: ... list(functor)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* functor */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__11_22;
}
static void cont__11_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__3 */ = arguments->slots[0];
  // 252: ... fragment_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* info */;
  result_count = 1;
  myself = get__fragment_of();
  func = myself->type;
  frame->cont = cont__11_23;
}
static void cont__11_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__4 */ = arguments->slots[0];
  // 253: ... source_position_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* info */;
  result_count = 1;
  myself = get__source_position_of();
  func = myself->type;
  frame->cont = cont__11_24;
}
static void cont__11_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__6 */ = arguments->slots[0];
  // 253: ... source_position_of(info)+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__6 */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__11_25;
}
static void cont__11_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__5 */ = arguments->slots[0];
  // 254: ... end_position_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* info */;
  result_count = 1;
  myself = get__end_position_of();
  func = myself->type;
  frame->cont = cont__11_26;
}
static void cont__11_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__7 */ = arguments->slots[0];
  // 248: procedure_call
  // 249:   .functor_of functor
  // 250:   .arguments_of push(arguments result)
  // 251:   .output_arguments_of list(functor)
  // 252:   .fragment_of fragment_of(info)
  // 253:   .source_position_of source_position_of(info)+1
  // 254:   .end_position_of end_position_of(info)
  {
    NODE *temp = clone_object_and_attributes(get__procedure_call());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__functor_of, frame->slots[2] /* functor */);
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[7] /* temp__2 */);
    set_attribute_value(temp->attributes, poly_idx__output_arguments_of, frame->slots[8] /* temp__3 */);
    set_attribute_value(temp->attributes, poly_idx__fragment_of, frame->slots[9] /* temp__4 */);
    set_attribute_value(temp->attributes, poly_idx__source_position_of, frame->slots[10] /* temp__5 */);
    set_attribute_value(temp->attributes, poly_idx__end_position_of, frame->slots[12] /* temp__7 */);
    frame->slots[6] /* temp__1 */ = temp;

  }
  // 246: push
  // 247:   &statements
  // 248:   procedure_call
  // 249:     .functor_of functor
  // 250:     .arguments_of push(arguments result)
  // 251:     .output_arguments_of list(functor)
  // 252:     .fragment_of fragment_of(info)
  // 253:     .source_position_of source_position_of(info)+1
  // 254:     .end_position_of end_position_of(info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__statements();
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__11_27;
}
static void cont__11_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__statements(arguments->slots[0]);
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__11_28(void) {
  allocate_initialized_frame_gc(6, 17);
  // slot allocations:
  // rest: 0
  // arguments: 1
  // functor: 2
  // info: 3
  // result: 4
  // infos: 5
  // attribute_pair: 6
  frame->slots[0] = myself->closure.frame->slots[3]; /* rest */
  frame->slots[1] = myself->closure.frame->slots[1]; /* arguments */
  frame->slots[2] = myself->closure.frame->slots[0]; /* functor */
  frame->slots[3] = myself->closure.frame->slots[5]; /* info */
  frame->slots[4] = myself->closure.frame->slots[2]; /* result */
  frame->slots[5] = myself->closure.frame->slots[4]; /* infos */
  frame->slots[6] /* attribute_pair */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 256: ... length_of(rest)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* rest */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__11_29;
}
static void cont__11_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__2 */ = arguments->slots[0];
  // 256: ... length_of(rest) > 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = frame->slots[8] /* temp__2 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__11_30;
}
static void cont__11_30(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 256: ... :
  // 257:   $temp temporary_identifier()
  // 258:   push
  // 259:     &statements
  // 260:     procedure_call
  // 261:       .functor_of functor_of(arguments)
  // 262:       .arguments_of list(functor)
  // 263:       .output_arguments_of list(temp)
  // 264:       .fragment_of fragment_of(info)
  // 265:       .source_position_of source_position_of(info)
  // ...
  frame->slots[9] /* temp__3 */ = create_closure(entry__11_31, 0);
  // 256: if length_of(rest) > 0:
  // 257:   $temp temporary_identifier()
  // 258:   push
  // 259:     &statements
  // 260:     procedure_call
  // 261:       .functor_of functor_of(arguments)
  // 262:       .arguments_of list(functor)
  // 263:       .output_arguments_of list(temp)
  // 264:       .fragment_of fragment_of(info)
  // 265:       .source_position_of source_position_of(info)
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[9] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__11_43;
}
static void entry__11_31(void) {
  allocate_initialized_frame_gc(6, 14);
  // slot allocations:
  // arguments: 0
  // functor: 1
  // info: 2
  // rest: 3
  // result: 4
  // infos: 5
  // temp: 6
  frame->slots[0] = myself->closure.frame->slots[1]; /* arguments */
  frame->slots[1] = myself->closure.frame->slots[2]; /* functor */
  frame->slots[2] = myself->closure.frame->slots[3]; /* info */
  frame->slots[3] = myself->closure.frame->slots[0]; /* rest */
  frame->slots[4] = myself->closure.frame->slots[4]; /* result */
  frame->slots[5] = myself->closure.frame->slots[5]; /* infos */
  frame->slots[6] /* temp */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 257: $temp temporary_identifier()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = var._temporary_identifier;
  func = myself->type;
  frame->cont = cont__11_32;
}
static void cont__11_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* temp */, arguments->slots[0]);
  // 261: ... functor_of(arguments)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* arguments */;
  result_count = 1;
  myself = get__functor_of();
  func = myself->type;
  frame->cont = cont__11_33;
}
static void cont__11_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__2 */ = arguments->slots[0];
  // 262: ... list(functor)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* functor */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__11_34;
}
static void cont__11_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__3 */ = arguments->slots[0];
  // 263: ... list(temp)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__11_35;
}
static void cont__11_35(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__4 */ = arguments->slots[0];
  // 264: ... fragment_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* info */;
  result_count = 1;
  myself = get__fragment_of();
  func = myself->type;
  frame->cont = cont__11_36;
}
static void cont__11_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__5 */ = arguments->slots[0];
  // 265: ... source_position_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* info */;
  result_count = 1;
  myself = get__source_position_of();
  func = myself->type;
  frame->cont = cont__11_37;
}
static void cont__11_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__6 */ = arguments->slots[0];
  // 266: ... end_position_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* info */;
  result_count = 1;
  myself = get__end_position_of();
  func = myself->type;
  frame->cont = cont__11_38;
}
static void cont__11_38(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__7 */ = arguments->slots[0];
  // 260: procedure_call
  // 261:   .functor_of functor_of(arguments)
  // 262:   .arguments_of list(functor)
  // 263:   .output_arguments_of list(temp)
  // 264:   .fragment_of fragment_of(info)
  // 265:   .source_position_of source_position_of(info)
  // 266:   .end_position_of end_position_of(info)
  {
    NODE *temp = clone_object_and_attributes(get__procedure_call());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__functor_of, frame->slots[8] /* temp__2 */);
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[9] /* temp__3 */);
    set_attribute_value(temp->attributes, poly_idx__output_arguments_of, frame->slots[10] /* temp__4 */);
    set_attribute_value(temp->attributes, poly_idx__fragment_of, frame->slots[11] /* temp__5 */);
    set_attribute_value(temp->attributes, poly_idx__source_position_of, frame->slots[12] /* temp__6 */);
    set_attribute_value(temp->attributes, poly_idx__end_position_of, frame->slots[13] /* temp__7 */);
    frame->slots[7] /* temp__1 */ = temp;

  }
  // 258: push
  // 259:   &statements
  // 260:   procedure_call
  // 261:     .functor_of functor_of(arguments)
  // 262:     .arguments_of list(functor)
  // 263:     .output_arguments_of list(temp)
  // 264:     .fragment_of fragment_of(info)
  // 265:     .source_position_of source_position_of(info)
  // 266:     .end_position_of end_position_of(info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__statements();
  arguments->slots[1] = frame->slots[7] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__11_39;
}
static void cont__11_39(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__statements(arguments->slots[0]);
  // 267: ... rest.peek
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* rest */;
  result_count = 1;
  myself = get__peek();
  func = myself->type;
  frame->cont = cont__11_40;
}
static void cont__11_40(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 267: ... rest.drop
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* rest */;
  result_count = 1;
  myself = get__drop();
  func = myself->type;
  frame->cont = cont__11_41;
}
static void cont__11_41(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__2 */ = arguments->slots[0];
  // 267: do_store temp rest.peek result rest.drop infos
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp */;
  arguments->slots[1] = frame->slots[7] /* temp__1 */;
  arguments->slots[2] = ((CELL *)frame->slots[4])->contents /* result */;
  arguments->slots[3] = frame->slots[8] /* temp__2 */;
  arguments->slots[4] = ((CELL *)frame->slots[5])->contents /* infos */;
  result_count = 0;
  myself = var._do_store;
  func = myself->type;
  frame->cont = cont__11_42;
}
static void cont__11_42(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 268: !result temp
  ((CELL *)frame->slots[4])->contents /* result */ = frame->slots[6] /* temp */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__11_43(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 272: arguments.is_a_method_definition
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* arguments */;
  result_count = 1;
  myself = get__is_a_method_definition();
  func = myself->type;
  frame->cont = cont__11_44;
}
static void cont__11_44(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 270: $attribute_pair
  // 271:   if
  // 272:     arguments.is_a_method_definition
  // 273:     -> attribute_function_pair
  // 274:     -> attribute_value_pair
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = func__11_45;
  arguments->slots[2] = func__11_46;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__11_47;
}
static void entry__11_45(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 273: -> attribute_function_pair
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__attribute_function_pair();
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__11_46(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 274: -> attribute_value_pair
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__attribute_value_pair();
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__11_47(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* attribute_pair */, arguments->slots[0]);
  // 279: ... list(functor)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* functor */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__11_48;
}
static void cont__11_48(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__2 */ = arguments->slots[0];
  // 283: ... functor_of(arguments)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* arguments */;
  result_count = 1;
  myself = get__functor_of();
  func = myself->type;
  frame->cont = cont__11_49;
}
static void cont__11_49(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__5 */ = arguments->slots[0];
  // 284: ... list(result)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* result */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__11_50;
}
static void cont__11_50(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__6 */ = arguments->slots[0];
  // 282: attribute_pair
  // 283:   .identifier_of functor_of(arguments)
  // 284:   .arguments_of list(result)
  {
    NODE *temp = clone_object_and_attributes(frame->slots[6] /* attribute_pair */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__identifier_of, frame->slots[11] /* temp__5 */);
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[12] /* temp__6 */);
    frame->slots[10] /* temp__4 */ = temp;

  }
  // 281: list
  // 282:   attribute_pair
  // 283:     .identifier_of functor_of(arguments)
  // 284:     .arguments_of list(result)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__4 */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__11_51;
}
static void cont__11_51(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__3 */ = arguments->slots[0];
  // 285: ... fragment_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* info */;
  result_count = 1;
  myself = get__fragment_of();
  func = myself->type;
  frame->cont = cont__11_52;
}
static void cont__11_52(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__7 */ = arguments->slots[0];
  // 286: ... source_position_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* info */;
  result_count = 1;
  myself = get__source_position_of();
  func = myself->type;
  frame->cont = cont__11_53;
}
static void cont__11_53(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[15] /* temp__9 */ = arguments->slots[0];
  // 286: ... source_position_of(info)+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[15] /* temp__9 */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__11_54;
}
static void cont__11_54(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[14] /* temp__8 */ = arguments->slots[0];
  // 287: ... end_position_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* info */;
  result_count = 1;
  myself = get__end_position_of();
  func = myself->type;
  frame->cont = cont__11_55;
}
static void cont__11_55(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[16] /* temp__10 */ = arguments->slots[0];
  // 278: assignment
  // 279:   .output_arguments_of list(functor)
  // 280:   .arguments_of
  // 281:     list
  // 282:       attribute_pair
  // 283:         .identifier_of functor_of(arguments)
  // 284:         .arguments_of list(result)
  // 285:   .fragment_of fragment_of(info)
  // 286:   .source_position_of source_position_of(info)+1
  // 287:   .end_position_of end_position_of(info)
  {
    NODE *temp = clone_object_and_attributes(get__assignment());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__output_arguments_of, frame->slots[8] /* temp__2 */);
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[9] /* temp__3 */);
    set_attribute_value(temp->attributes, poly_idx__fragment_of, frame->slots[13] /* temp__7 */);
    set_attribute_value(temp->attributes, poly_idx__source_position_of, frame->slots[14] /* temp__8 */);
    set_attribute_value(temp->attributes, poly_idx__end_position_of, frame->slots[16] /* temp__10 */);
    frame->slots[7] /* temp__1 */ = temp;

  }
  // 276: push
  // 277:   &statements
  // 278:   assignment
  // 279:     .output_arguments_of list(functor)
  // 280:     .arguments_of
  // 281:       list
  // 282:         attribute_pair
  // 283:           .identifier_of functor_of(arguments)
  // 284:           .arguments_of list(result)
  // 285:     .fragment_of fragment_of(info)
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__statements();
  arguments->slots[1] = frame->slots[7] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__11_56;
}
static void cont__11_56(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__statements(arguments->slots[0]);
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__11_1(void) {
  allocate_initialized_frame_gc(5, 9);
  // slot allocations:
  // functor: 0
  // arguments: 1
  // result: 2
  // rest: 3
  // infos: 4
  // info: 5
  frame->slots[5] /* info */ = create_future();
  if (argument_count != 5) {
    invalid_arguments_error();
    return;
  }
  frame->slots[1] /* arguments */ = create_cell_with_contents(arguments->slots[1]);
  frame->slots[2] /* result */ = create_cell_with_contents(arguments->slots[2]);
  frame->slots[4] /* infos */ = create_cell_with_contents(arguments->slots[4]);
  // 229: pop &infos $info
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* infos */;
  result_count = 2;
  myself = get__pop();
  func = myself->type;
  frame->cont = cont__11_2;
}
static void cont__11_2(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[4])->contents /* infos */ = arguments->slots[0];
  frame->slots[6] /* temp__1 */ = arguments->slots[1];
  // 229: ... info
  initialize_future(frame->slots[5] /* info */, frame->slots[6] /* temp__1 */);
  // 231: arguments.is_a_list
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* arguments */;
  result_count = 1;
  myself = get__is_a_list();
  func = myself->type;
  frame->cont = cont__11_3;
}
static void cont__11_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 231: ... : # container access
  // 232:   update_each &arguments: (&argument) simplify_expression &argument
  // 233:   if length_of(rest) > 0:
  // 234:     $temp temporary_identifier()
  // 235:     push
  // 236:       &statements
  // 237:       procedure_call
  // 238:         .functor_of functor
  // 239:         .arguments_of arguments
  // 240:         .output_arguments_of list(temp)
  // ...
  frame->slots[7] /* temp__2 */ = create_closure(entry__11_4, 0);
  // 255: : # attribute value or attribute function definition
  // 256:   if length_of(rest) > 0:
  // 257:     $temp temporary_identifier()
  // 258:     push
  // 259:       &statements
  // 260:       procedure_call
  // 261:         .functor_of functor_of(arguments)
  // 262:         .arguments_of list(functor)
  // 263:         .output_arguments_of list(temp)
  // 264:         .fragment_of fragment_of(info)
  // ...
  frame->slots[8] /* temp__3 */ = create_closure(entry__11_28, 0);
  // 230: if
  // 231:   arguments.is_a_list: # container access
  // 232:     update_each &arguments: (&argument) simplify_expression &argument
  // 233:     if length_of(rest) > 0:
  // 234:       $temp temporary_identifier()
  // 235:       push
  // 236:         &statements
  // 237:         procedure_call
  // 238:           .functor_of functor
  // 239:           .arguments_of arguments
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
static void entry__12_16(void) {
  allocate_initialized_frame_gc(5, 5);
  // slot allocations:
  // functor: 0
  // arguments: 1
  // result: 2
  // rest: 3
  // infos: 4
  frame->slots[0] = myself->closure.frame->slots[5]; /* functor */
  frame->slots[1] = myself->closure.frame->slots[1]; /* arguments */
  frame->slots[2] = myself->closure.frame->slots[2]; /* result */
  frame->slots[3] = myself->closure.frame->slots[3]; /* rest */
  frame->slots[4] = myself->closure.frame->slots[4]; /* infos */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 309: do_store functor arguments result rest infos
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* functor */;
  arguments->slots[1] = frame->slots[1] /* arguments */;
  arguments->slots[2] = frame->slots[2] /* result */;
  arguments->slots[3] = frame->slots[3] /* rest */;
  arguments->slots[4] = ((CELL *)frame->slots[4])->contents /* infos */;
  result_count = frame->caller_result_count;
  myself = var._do_store;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__12_17(void) {
  allocate_initialized_frame_gc(5, 6);
  // slot allocations:
  // functor: 0
  // result: 1
  // rest: 2
  // arguments: 3
  // infos: 4
  frame->slots[0] = myself->closure.frame->slots[5]; /* functor */
  frame->slots[1] = myself->closure.frame->slots[2]; /* result */
  frame->slots[2] = myself->closure.frame->slots[3]; /* rest */
  frame->slots[3] = myself->closure.frame->slots[1]; /* arguments */
  frame->slots[4] = myself->closure.frame->slots[4]; /* infos */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 311: ... push(rest arguments)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* rest */;
  arguments->slots[1] = frame->slots[3] /* arguments */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__12_18;
}
static void cont__12_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 311: store_result functor result push(rest arguments) infos
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* functor */;
  arguments->slots[1] = frame->slots[1] /* result */;
  arguments->slots[2] = frame->slots[5] /* temp__1 */;
  arguments->slots[3] = ((CELL *)frame->slots[4])->contents /* infos */;
  result_count = frame->caller_result_count;
  myself = var._store_result;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__12_8(void) {
  allocate_initialized_frame_gc(5, 6);
  // slot allocations:
  // arguments: 0
  // destination: 1
  // result: 2
  // rest: 3
  // infos: 4
  frame->slots[0] = myself->closure.frame->slots[0]; /* arguments */
  frame->slots[1] = myself->closure.frame->slots[1]; /* destination */
  frame->slots[2] = myself->closure.frame->slots[2]; /* result */
  frame->slots[3] = myself->closure.frame->slots[3]; /* rest */
  frame->slots[4] = myself->closure.frame->slots[4]; /* infos */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 302: ... arguments(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* arguments */;
  func = myself->type;
  frame->cont = cont__12_9;
}
static void cont__12_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 302: do_store arguments(1) destination result rest infos
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* destination */;
  arguments->slots[2] = frame->slots[2] /* result */;
  arguments->slots[3] = frame->slots[3] /* rest */;
  arguments->slots[4] = ((CELL *)frame->slots[4])->contents /* infos */;
  result_count = frame->caller_result_count;
  myself = var._do_store;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__12_10(void) {
  allocate_initialized_frame_gc(5, 7);
  // slot allocations:
  // arguments: 0
  // result: 1
  // rest: 2
  // destination: 3
  // infos: 4
  frame->slots[0] = myself->closure.frame->slots[0]; /* arguments */
  frame->slots[1] = myself->closure.frame->slots[2]; /* result */
  frame->slots[2] = myself->closure.frame->slots[3]; /* rest */
  frame->slots[3] = myself->closure.frame->slots[1]; /* destination */
  frame->slots[4] = myself->closure.frame->slots[4]; /* infos */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 304: ... arguments(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* arguments */;
  func = myself->type;
  frame->cont = cont__12_11;
}
static void cont__12_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 304: ... push(rest destination)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* rest */;
  arguments->slots[1] = frame->slots[3] /* destination */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__12_12;
}
static void cont__12_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 304: store_result arguments(1) result push(rest destination) infos
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* result */;
  arguments->slots[2] = frame->slots[6] /* temp__2 */;
  arguments->slots[3] = ((CELL *)frame->slots[4])->contents /* infos */;
  result_count = frame->caller_result_count;
  myself = var._store_result;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__12_5(void) {
  allocate_initialized_frame_gc(5, 9);
  // slot allocations:
  // arguments: 0
  // destination: 1
  // result: 2
  // rest: 3
  // infos: 4
  frame->slots[0] = myself->closure.frame->slots[4]; /* arguments */
  frame->slots[1] = myself->closure.frame->slots[0]; /* destination */
  frame->slots[2] = myself->closure.frame->slots[1]; /* result */
  frame->slots[3] = myself->closure.frame->slots[2]; /* rest */
  frame->slots[4] = myself->closure.frame->slots[3]; /* infos */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 301: arguments(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* arguments */;
  func = myself->type;
  frame->cont = cont__12_6;
}
static void cont__12_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 301: arguments(1).is_an_identifier
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  result_count = 1;
  myself = get__is_an_identifier();
  func = myself->type;
  frame->cont = cont__12_7;
}
static void cont__12_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 301: ... :
  // 302:   do_store arguments(1) destination result rest infos
  frame->slots[7] /* temp__3 */ = create_closure(entry__12_8, 0);
  // 303: :
  // 304:   store_result arguments(1) result push(rest destination) infos
  frame->slots[8] /* temp__4 */ = create_closure(entry__12_10, 0);
  // 300: if
  // 301:   arguments(1).is_an_identifier:
  // 302:     do_store arguments(1) destination result rest infos
  // 303:   :
  // 304:     store_result arguments(1) result push(rest destination) infos
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  arguments->slots[2] = frame->slots[8] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__12_13(void) {
  allocate_initialized_frame_gc(5, 9);
  // slot allocations:
  // destination: 0
  // arguments: 1
  // result: 2
  // rest: 3
  // infos: 4
  // functor: 5
  frame->slots[0] = myself->closure.frame->slots[0]; /* destination */
  frame->slots[1] = myself->closure.frame->slots[4]; /* arguments */
  frame->slots[2] = myself->closure.frame->slots[1]; /* result */
  frame->slots[3] = myself->closure.frame->slots[2]; /* rest */
  frame->slots[4] = myself->closure.frame->slots[3]; /* infos */
  frame->slots[5] /* functor */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 306: $functor functor_of(destination)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* destination */;
  result_count = 1;
  myself = get__functor_of();
  func = myself->type;
  frame->cont = cont__12_14;
}
static void cont__12_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* functor */, arguments->slots[0]);
  // 308: functor.is_an_identifier
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* functor */;
  result_count = 1;
  myself = get__is_an_identifier();
  func = myself->type;
  frame->cont = cont__12_15;
}
static void cont__12_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 308: ... :
  // 309:   do_store functor arguments result rest infos
  frame->slots[7] /* temp__2 */ = create_closure(entry__12_16, 0);
  // 310: :
  // 311:   store_result functor result push(rest arguments) infos
  frame->slots[8] /* temp__3 */ = create_closure(entry__12_17, 0);
  // 307: if
  // 308:   functor.is_an_identifier:
  // 309:     do_store functor arguments result rest infos
  // 310:   :
  // 311:     store_result functor result push(rest arguments) infos
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
static void entry__12_1(void) {
  allocate_initialized_frame_gc(4, 8);
  // slot allocations:
  // destination: 0
  // result: 1
  // rest: 2
  // infos: 3
  // arguments: 4
  frame->slots[4] /* arguments */ = create_future();
  if (argument_count < 2) {
    too_few_arguments_error();
    return;
  }
  if (argument_count > 4) {
    too_many_arguments_error();
    return;
  }
  switch(argument_count) {
    default: frame->slots[3] /* infos */ = create_cell_with_contents(arguments->slots[3]);
    case 3: frame->slots[2] /* rest */ = arguments->slots[2];
    case 2:;
  }
  switch(argument_count) {
    case 2: frame->slots[2] /* rest */ = get__empty_list();
    case 3: frame->slots[3] /* infos */ = create_cell_with_contents(get__empty_list());
  }
  // 296: push &infos destination
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* infos */;
  arguments->slots[1] = frame->slots[0] /* destination */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__12_2;
}
static void cont__12_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* infos */ = arguments->slots[0];
  // 297: $arguments arguments_of(destination)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* destination */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__12_3;
}
static void cont__12_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* arguments */, arguments->slots[0]);
  // 299: destination.is_an_attribute_access
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* destination */;
  result_count = 1;
  myself = get__is_an_attribute_access();
  func = myself->type;
  frame->cont = cont__12_4;
}
static void cont__12_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 299: ... :
  // 300:   if
  // 301:     arguments(1).is_an_identifier:
  // 302:       do_store arguments(1) destination result rest infos
  // 303:     :
  // 304:       store_result arguments(1) result push(rest destination) infos
  frame->slots[6] /* temp__2 */ = create_closure(entry__12_5, 0);
  // 305: :
  // 306:   $functor functor_of(destination)
  // 307:   if
  // 308:     functor.is_an_identifier:
  // 309:       do_store functor arguments result rest infos
  // 310:     :
  // 311:       store_result functor result push(rest arguments) infos
  frame->slots[7] /* temp__3 */ = create_closure(entry__12_13, 0);
  // 298: if
  // 299:   destination.is_an_attribute_access:
  // 300:     if
  // 301:       arguments(1).is_an_identifier:
  // 302:         do_store arguments(1) destination result rest infos
  // 303:       :
  // 304:         store_result arguments(1) result push(rest destination) infos
  // 305:   :
  // 306:     $functor functor_of(destination)
  // 307:     if
  // ...
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
static void entry__13_1(void) {
  allocate_initialized_frame_gc(2, 7);
  // slot allocations:
  // self: 0
  // return: 1
  // final_destinations: 2
  frame->slots[1] /* return */ = create_continuation();
  frame->slots[2] /* final_destinations */ = create_future();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* self */ = create_cell_with_contents(arguments->slots[0]);
  // 318: show_compiler_debug_info "simplify statement"
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
  // 319: ... self.is_an_assignment
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__is_an_assignment();
  func = myself->type;
  frame->cont = cont__13_4;
}
static void cont__13_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 319: ... length_of(arguments_of(self)) == 1
  frame->slots[5] /* temp__3 */ = create_closure(entry__13_5, 0);
  // 319: ... self.is_an_assignment && length_of(arguments_of(self)) == 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__13_9;
}
static void entry__13_5(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // self: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 319: ... arguments_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__13_6;
}
static void cont__13_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 319: ... length_of(arguments_of(self))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__13_7;
}
static void cont__13_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 319: ... length_of(arguments_of(self)) == 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__13_8;
}
static void cont__13_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 319: ... length_of(arguments_of(self)) == 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__13_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 319: ... :
  // 320:   $source arguments_of(self)(1)
  // 321:   if source.is_a_function_call:
  // 322:     !self
  // 323:       procedure_call
  // 324:         .functor_of functor_of(source)
  // 325:         .output_arguments_of
  // 326:           push(output_arguments_of(source) output_arguments_of(self)(1))
  // 327:         .arguments_of arguments_of(source)
  // 328:         .fragment_of fragment_of(self)
  // ...
  frame->slots[6] /* temp__4 */ = create_closure(entry__13_10, 0);
  // 319: if self.is_an_assignment && length_of(arguments_of(self)) == 1:
  // 320:   $source arguments_of(self)(1)
  // 321:   if source.is_a_function_call:
  // 322:     !self
  // 323:       procedure_call
  // 324:         .functor_of functor_of(source)
  // 325:         .output_arguments_of
  // 326:           push(output_arguments_of(source) output_arguments_of(self)(1))
  // 327:         .arguments_of arguments_of(source)
  // 328:         .fragment_of fragment_of(self)
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__13_24;
}
static void entry__13_14(void) {
  allocate_initialized_frame_gc(2, 11);
  // slot allocations:
  // self: 0
  // source: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  frame->slots[1] = myself->closure.frame->slots[1]; /* source */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 324: ... functor_of(source)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* source */;
  result_count = 1;
  myself = get__functor_of();
  func = myself->type;
  frame->cont = cont__13_15;
}
static void cont__13_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 326: ... output_arguments_of(source)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* source */;
  result_count = 1;
  myself = get__output_arguments_of();
  func = myself->type;
  frame->cont = cont__13_16;
}
static void cont__13_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 326: ... output_arguments_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__output_arguments_of();
  func = myself->type;
  frame->cont = cont__13_17;
}
static void cont__13_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__5 */ = arguments->slots[0];
  // 326: ... output_arguments_of(self)(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[6] /* temp__5 */;
  func = myself->type;
  frame->cont = cont__13_18;
}
static void cont__13_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__4 */ = arguments->slots[0];
  // 326: push(output_arguments_of(source) output_arguments_of(self)(1))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  arguments->slots[1] = frame->slots[5] /* temp__4 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__13_19;
}
static void cont__13_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 327: ... arguments_of(source)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* source */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__13_20;
}
static void cont__13_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__6 */ = arguments->slots[0];
  // 328: ... fragment_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__fragment_of();
  func = myself->type;
  frame->cont = cont__13_21;
}
static void cont__13_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__7 */ = arguments->slots[0];
  // 329: ... source_position_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__source_position_of();
  func = myself->type;
  frame->cont = cont__13_22;
}
static void cont__13_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__8 */ = arguments->slots[0];
  // 330: ... end_position_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__end_position_of();
  func = myself->type;
  frame->cont = cont__13_23;
}
static void cont__13_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__9 */ = arguments->slots[0];
  // 322: !self
  // 323:   procedure_call
  // 324:     .functor_of functor_of(source)
  // 325:     .output_arguments_of
  // 326:       push(output_arguments_of(source) output_arguments_of(self)(1))
  // 327:     .arguments_of arguments_of(source)
  // 328:     .fragment_of fragment_of(self)
  // 329:     .source_position_of source_position_of(self)
  // 330:     .end_position_of end_position_of(self)
  {
    NODE *temp = clone_object_and_attributes(get__procedure_call());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__functor_of, frame->slots[2] /* temp__1 */);
    set_attribute_value(temp->attributes, poly_idx__output_arguments_of, frame->slots[3] /* temp__2 */);
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[7] /* temp__6 */);
    set_attribute_value(temp->attributes, poly_idx__fragment_of, frame->slots[8] /* temp__7 */);
    set_attribute_value(temp->attributes, poly_idx__source_position_of, frame->slots[9] /* temp__8 */);
    set_attribute_value(temp->attributes, poly_idx__end_position_of, frame->slots[10] /* temp__9 */);
    ((CELL *)frame->slots[0])->contents /* self */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__13_10(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // self: 0
  // source: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  frame->slots[1] /* source */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 320: ... arguments_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__13_11;
}
static void cont__13_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 320: $source arguments_of(self)(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[2] /* temp__1 */;
  func = myself->type;
  frame->cont = cont__13_12;
}
static void cont__13_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* source */, arguments->slots[0]);
  // 321: ... source.is_a_function_call
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* source */;
  result_count = 1;
  myself = get__is_a_function_call();
  func = myself->type;
  frame->cont = cont__13_13;
}
static void cont__13_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 321: ... :
  // 322:   !self
  // 323:     procedure_call
  // 324:       .functor_of functor_of(source)
  // 325:       .output_arguments_of
  // 326:         push(output_arguments_of(source) output_arguments_of(self)(1))
  // 327:       .arguments_of arguments_of(source)
  // 328:       .fragment_of fragment_of(self)
  // 329:       .source_position_of source_position_of(self)
  // 330:       .end_position_of end_position_of(self)
  frame->slots[3] /* temp__2 */ = create_closure(entry__13_14, 0);
  // 321: if source.is_a_function_call:
  // 322:   !self
  // 323:     procedure_call
  // 324:       .functor_of functor_of(source)
  // 325:       .output_arguments_of
  // 326:         push(output_arguments_of(source) output_arguments_of(self)(1))
  // 327:       .arguments_of arguments_of(source)
  // 328:       .fragment_of fragment_of(self)
  // 329:       .source_position_of source_position_of(self)
  // 330:       .end_position_of end_position_of(self)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__13_24(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 331: $final_destinations simplify_arguments(&self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 2;
  myself = var._simplify_arguments;
  func = myself->type;
  frame->cont = cont__13_25;
}
static void cont__13_25(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* self */ = arguments->slots[0];
  frame->slots[3] /* temp__1 */ = arguments->slots[1];
  // 331: ... final_destinations
  initialize_future(frame->slots[2] /* final_destinations */, frame->slots[3] /* temp__1 */);
  // 332: ... functor_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__functor_of();
  func = myself->type;
  frame->cont = cont__13_26;
}
static void cont__13_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 332: ... functor_of(self).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__13_27;
}
static void cont__13_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 332: ... :
  // 333:   if result_count_of(self).is_defined:
  // 334:     simplify_expression &self.result_count_of
  // 335:   if continuation_of(self).is_defined:
  // 336:     simplify_expression &self.continuation_of
  // 337:   simplify_expression &self.functor_of
  frame->slots[5] /* temp__3 */ = create_closure(entry__13_28, 0);
  // 332: if functor_of(self).is_defined:
  // 333:   if result_count_of(self).is_defined:
  // 334:     simplify_expression &self.result_count_of
  // 335:   if continuation_of(self).is_defined:
  // 336:     simplify_expression &self.continuation_of
  // 337:   simplify_expression &self.functor_of
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__13_43;
}
static void entry__13_28(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // self: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 333: ... result_count_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__result_count_of();
  func = myself->type;
  frame->cont = cont__13_29;
}
static void cont__13_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 333: ... result_count_of(self).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__13_30;
}
static void cont__13_30(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 333: ... :
  // 334:   simplify_expression &self.result_count_of
  frame->slots[3] /* temp__3 */ = create_closure(entry__13_31, 0);
  // 333: if result_count_of(self).is_defined:
  // 334:   simplify_expression &self.result_count_of
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__13_34;
}
static void entry__13_31(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // self: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 334: ... self.result_count_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__result_count_of();
  func = myself->type;
  frame->cont = cont__13_32;
}
static void cont__13_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 334: simplify_expression &self.result_count_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__simplify_expression();
  func = myself->type;
  frame->cont = cont__13_33;
}
static void cont__13_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 334: ... &self.result_count_of
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
static void cont__13_34(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 335: ... continuation_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__continuation_of();
  func = myself->type;
  frame->cont = cont__13_35;
}
static void cont__13_35(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 335: ... continuation_of(self).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__13_36;
}
static void cont__13_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 335: ... :
  // 336:   simplify_expression &self.continuation_of
  frame->slots[3] /* temp__3 */ = create_closure(entry__13_37, 0);
  // 335: if continuation_of(self).is_defined:
  // 336:   simplify_expression &self.continuation_of
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__13_40;
}
static void entry__13_37(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // self: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 336: ... self.continuation_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__continuation_of();
  func = myself->type;
  frame->cont = cont__13_38;
}
static void cont__13_38(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 336: simplify_expression &self.continuation_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__simplify_expression();
  func = myself->type;
  frame->cont = cont__13_39;
}
static void cont__13_39(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 336: ... &self.continuation_of
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
static void cont__13_40(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 337: ... self.functor_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__functor_of();
  func = myself->type;
  frame->cont = cont__13_41;
}
static void cont__13_41(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 337: simplify_expression &self.functor_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__simplify_expression();
  func = myself->type;
  frame->cont = cont__13_42;
}
static void cont__13_42(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 337: ... &self.functor_of
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
static void cont__13_43(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 339: self.is_an_assignment
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__is_an_assignment();
  func = myself->type;
  frame->cont = cont__13_44;
}
static void cont__13_44(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 339: ... :
  // 340:   $destination output_arguments_of(self)(1)
  // 341:   if destination.is_a_definition:
  // 342:     if
  // 343:       destination.is_a_single_assign_definition:
  // 344:         $source arguments_of(self)(1)
  // 345:         if attribute_kind_of(destination) != NONE:
  // 346:           push &definitions destination = source
  // 347:           return
  // 348:         cond
  // ...
  frame->slots[4] /* temp__2 */ = create_closure(entry__13_45, 0);
  // 361: :
  // 362:   update_each &self.output_arguments_of: (&argument)
  // 363:     if argument.is_a_definition:
  // 364:       push &definitions argument
  // 365:       !argument.is_an_initialization true
  frame->slots[5] /* temp__3 */ = create_closure(entry__13_87, 0);
  // 338: if
  // 339:   self.is_an_assignment:
  // 340:     $destination output_arguments_of(self)(1)
  // 341:     if destination.is_a_definition:
  // 342:       if
  // 343:         destination.is_a_single_assign_definition:
  // 344:           $source arguments_of(self)(1)
  // 345:           if attribute_kind_of(destination) != NONE:
  // 346:             push &definitions destination = source
  // 347:             return
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  arguments->slots[2] = frame->slots[5] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__13_95;
}
static void entry__13_71(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // destination: 0
  // source: 1
  // self: 2
  frame->slots[0] = myself->closure.frame->slots[1]; /* destination */
  frame->slots[1] = myself->closure.frame->slots[0]; /* source */
  frame->slots[2] = myself->closure.frame->slots[2]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 353: ... destination = source
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* destination */;
  arguments->slots[1] = frame->slots[1] /* source */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__13_72;
}
static void cont__13_72(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 353: push &definitions destination = source
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__definitions();
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__13_73;
}
static void cont__13_73(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__definitions(arguments->slots[0]);
  // 354: !self.output_arguments_of(1).is_an_initialization true
  frame->slots[3] /* temp__1 */ = get__true();
  // 354: ... self.output_arguments_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* self */;
  result_count = 1;
  myself = get__output_arguments_of();
  func = myself->type;
  frame->cont = cont__13_74;
}
static void cont__13_74(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 354: ... self.output_arguments_of(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[4] /* temp__2 */;
  func = myself->type;
  frame->cont = cont__13_75;
}
static void cont__13_75(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 354: !self.output_arguments_of(1).is_an_initialization
  {
    NODE *temp = clone_object_and_attributes(frame->slots[5] /* temp__3 */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__is_an_initialization, frame->slots[3] /* temp__1 */);
    frame->slots[5] /* temp__3 */ = temp;

  }
  // 354: !self.output_arguments_of(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__1;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = frame->slots[4] /* temp__2 */;
  func = myself->type;
  frame->cont = cont__13_76;
}
static void cont__13_76(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 354: !self.output_arguments_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[2])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__output_arguments_of, frame->slots[4] /* temp__2 */);
    ((CELL *)frame->slots[2])->contents /* self */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__13_66(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // destination: 0
  // source: 1
  // return: 2
  frame->slots[0] = myself->closure.frame->slots[1]; /* destination */
  frame->slots[1] = myself->closure.frame->slots[0]; /* source */
  frame->slots[2] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 350: ... destination = source
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* destination */;
  arguments->slots[1] = frame->slots[1] /* source */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__13_67;
}
static void cont__13_67(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 350: push &definitions destination = source
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__definitions();
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__13_68;
}
static void cont__13_68(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__definitions(arguments->slots[0]);
  // 351: return
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__13_61(void) {
  allocate_initialized_frame_gc(3, 7);
  // slot allocations:
  // source: 0
  // destination: 1
  // return: 2
  frame->slots[0] = myself->closure.frame->slots[3]; /* source */
  frame->slots[1] = myself->closure.frame->slots[1]; /* destination */
  frame->slots[2] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 349: ... source.is_a_constant
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* source */;
  result_count = 1;
  myself = get__is_a_constant();
  func = myself->type;
  frame->cont = cont__13_62;
}
static void cont__13_62(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 349: ... source.is_single_assign
  frame->slots[5] /* temp__3 */ = create_closure(entry__13_63, 0);
  // 349: ... source.is_a_constant || source.is_single_assign
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__13_65;
}
static void entry__13_63(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // source: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* source */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 349: ... source.is_single_assign
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* source */;
  result_count = 1;
  myself = get__is_single_assign();
  func = myself->type;
  frame->cont = cont__13_64;
}
static void cont__13_64(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 349: ... source.is_single_assign
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__13_65(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 349: ... :
  // 350:   push &definitions destination = source
  // 351:   return
  frame->slots[6] /* temp__4 */ = create_closure(entry__13_66, 0);
  // 349: -> source.is_a_constant || source.is_single_assign:
  // 350:   push &definitions destination = source
  // 351:   return
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__4 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__13_69(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // source: 0
  // destination: 1
  // self: 2
  frame->slots[0] = myself->closure.frame->slots[3]; /* source */
  frame->slots[1] = myself->closure.frame->slots[1]; /* destination */
  frame->slots[2] = myself->closure.frame->slots[0]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 352: ... source.might_be_constant
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* source */;
  result_count = 1;
  myself = get__might_be_constant();
  func = myself->type;
  frame->cont = cont__13_70;
}
static void cont__13_70(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 352: ... :
  // 353:   push &definitions destination = source
  // 354:   !self.output_arguments_of(1).is_an_initialization true
  frame->slots[4] /* temp__2 */ = create_closure(entry__13_71, 0);
  // 352: -> source.might_be_constant:
  // 353:   push &definitions destination = source
  // 354:   !self.output_arguments_of(1).is_an_initialization true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__13_77(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // destination: 0
  // self: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* destination */
  frame->slots[1] = myself->closure.frame->slots[0]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 356: push &definitions destination
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__definitions();
  arguments->slots[1] = frame->slots[0] /* destination */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__13_78;
}
static void cont__13_78(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__definitions(arguments->slots[0]);
  // 357: !self.output_arguments_of(1).is_an_initialization true
  frame->slots[2] /* temp__1 */ = get__true();
  // 357: ... self.output_arguments_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* self */;
  result_count = 1;
  myself = get__output_arguments_of();
  func = myself->type;
  frame->cont = cont__13_79;
}
static void cont__13_79(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 357: ... self.output_arguments_of(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[3] /* temp__2 */;
  func = myself->type;
  frame->cont = cont__13_80;
}
static void cont__13_80(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 357: !self.output_arguments_of(1).is_an_initialization
  {
    NODE *temp = clone_object_and_attributes(frame->slots[4] /* temp__3 */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__is_an_initialization, frame->slots[2] /* temp__1 */);
    frame->slots[4] /* temp__3 */ = temp;

  }
  // 357: !self.output_arguments_of(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__1;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = frame->slots[3] /* temp__2 */;
  func = myself->type;
  frame->cont = cont__13_81;
}
static void cont__13_81(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 357: !self.output_arguments_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[1])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__output_arguments_of, frame->slots[3] /* temp__2 */);
    ((CELL *)frame->slots[1])->contents /* self */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__13_51(void) {
  allocate_initialized_frame_gc(3, 8);
  // slot allocations:
  // self: 0
  // destination: 1
  // return: 2
  // source: 3
  frame->slots[0] = myself->closure.frame->slots[1]; /* self */
  frame->slots[1] = myself->closure.frame->slots[0]; /* destination */
  frame->slots[2] = myself->closure.frame->slots[2]; /* return */
  frame->slots[3] /* source */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 344: ... arguments_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__13_52;
}
static void cont__13_52(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 344: $source arguments_of(self)(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[4] /* temp__1 */;
  func = myself->type;
  frame->cont = cont__13_53;
}
static void cont__13_53(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* source */, arguments->slots[0]);
  // 345: ... attribute_kind_of(destination)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* destination */;
  result_count = 1;
  myself = get__attribute_kind_of();
  func = myself->type;
  frame->cont = cont__13_54;
}
static void cont__13_54(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 345: ... attribute_kind_of(destination) != NONE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__3 */;
  arguments->slots[1] = get__NONE();
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__13_55;
}
static void cont__13_55(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 345: ... attribute_kind_of(destination) != NONE
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__13_56;
}
static void cont__13_56(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 345: ... :
  // 346:   push &definitions destination = source
  // 347:   return
  frame->slots[7] /* temp__4 */ = create_closure(entry__13_57, 0);
  // 345: if attribute_kind_of(destination) != NONE:
  // 346:   push &definitions destination = source
  // 347:   return
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__13_60;
}
static void entry__13_57(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // destination: 0
  // source: 1
  // return: 2
  frame->slots[0] = myself->closure.frame->slots[1]; /* destination */
  frame->slots[1] = myself->closure.frame->slots[3]; /* source */
  frame->slots[2] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 346: ... destination = source
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* destination */;
  arguments->slots[1] = frame->slots[1] /* source */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__13_58;
}
static void cont__13_58(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 346: push &definitions destination = source
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__definitions();
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__13_59;
}
static void cont__13_59(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__definitions(arguments->slots[0]);
  // 347: return
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__13_60(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 349: -> source.is_a_constant || source.is_single_assign:
  // 350:   push &definitions destination = source
  // 351:   return
  frame->slots[4] /* temp__1 */ = create_closure(entry__13_61, 0);
  // 352: -> source.might_be_constant:
  // 353:   push &definitions destination = source
  // 354:   !self.output_arguments_of(1).is_an_initialization true
  frame->slots[5] /* temp__2 */ = create_closure(entry__13_69, 0);
  // 355: :
  // 356:   push &definitions destination
  // 357:   !self.output_arguments_of(1).is_an_initialization true
  frame->slots[6] /* temp__3 */ = create_closure(entry__13_77, 0);
  // 348: cond
  // 349:   -> source.is_a_constant || source.is_single_assign:
  // 350:     push &definitions destination = source
  // 351:     return
  // 352:   -> source.might_be_constant:
  // 353:     push &definitions destination = source
  // 354:     !self.output_arguments_of(1).is_an_initialization true
  // 355:   :
  // 356:     push &definitions destination
  // 357:     !self.output_arguments_of(1).is_an_initialization true
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
static void entry__13_82(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // destination: 0
  // self: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* destination */
  frame->slots[1] = myself->closure.frame->slots[1]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 359: push &definitions destination
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__definitions();
  arguments->slots[1] = frame->slots[0] /* destination */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__13_83;
}
static void cont__13_83(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__definitions(arguments->slots[0]);
  // 360: !self.output_arguments_of(1).is_an_initialization true
  frame->slots[2] /* temp__1 */ = get__true();
  // 360: ... self.output_arguments_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* self */;
  result_count = 1;
  myself = get__output_arguments_of();
  func = myself->type;
  frame->cont = cont__13_84;
}
static void cont__13_84(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 360: ... self.output_arguments_of(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[3] /* temp__2 */;
  func = myself->type;
  frame->cont = cont__13_85;
}
static void cont__13_85(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 360: !self.output_arguments_of(1).is_an_initialization
  {
    NODE *temp = clone_object_and_attributes(frame->slots[4] /* temp__3 */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__is_an_initialization, frame->slots[2] /* temp__1 */);
    frame->slots[4] /* temp__3 */ = temp;

  }
  // 360: !self.output_arguments_of(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__1;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = frame->slots[3] /* temp__2 */;
  func = myself->type;
  frame->cont = cont__13_86;
}
static void cont__13_86(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 360: !self.output_arguments_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[1])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__output_arguments_of, frame->slots[3] /* temp__2 */);
    ((CELL *)frame->slots[1])->contents /* self */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__13_49(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // destination: 0
  // self: 1
  // return: 2
  frame->slots[0] = myself->closure.frame->slots[2]; /* destination */
  frame->slots[1] = myself->closure.frame->slots[0]; /* self */
  frame->slots[2] = myself->closure.frame->slots[1]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 343: destination.is_a_single_assign_definition
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* destination */;
  result_count = 1;
  myself = get__is_a_single_assign_definition();
  func = myself->type;
  frame->cont = cont__13_50;
}
static void cont__13_50(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 343: ... :
  // 344:   $source arguments_of(self)(1)
  // 345:   if attribute_kind_of(destination) != NONE:
  // 346:     push &definitions destination = source
  // 347:     return
  // 348:   cond
  // 349:     -> source.is_a_constant || source.is_single_assign:
  // 350:       push &definitions destination = source
  // 351:       return
  // 352:     -> source.might_be_constant:
  // ...
  frame->slots[4] /* temp__2 */ = create_closure(entry__13_51, 0);
  // 358: :
  // 359:   push &definitions destination
  // 360:   !self.output_arguments_of(1).is_an_initialization true
  frame->slots[5] /* temp__3 */ = create_closure(entry__13_82, 0);
  // 342: if
  // 343:   destination.is_a_single_assign_definition:
  // 344:     $source arguments_of(self)(1)
  // 345:     if attribute_kind_of(destination) != NONE:
  // 346:       push &definitions destination = source
  // 347:       return
  // 348:     cond
  // 349:       -> source.is_a_constant || source.is_single_assign:
  // 350:         push &definitions destination = source
  // 351:         return
  // ...
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
static void entry__13_45(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // self: 0
  // return: 1
  // destination: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  frame->slots[1] = myself->closure.frame->slots[1]; /* return */
  frame->slots[2] /* destination */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 340: ... output_arguments_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__output_arguments_of();
  func = myself->type;
  frame->cont = cont__13_46;
}
static void cont__13_46(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 340: $destination output_arguments_of(self)(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[3] /* temp__1 */;
  func = myself->type;
  frame->cont = cont__13_47;
}
static void cont__13_47(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* destination */, arguments->slots[0]);
  // 341: ... destination.is_a_definition
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* destination */;
  result_count = 1;
  myself = get__is_a_definition();
  func = myself->type;
  frame->cont = cont__13_48;
}
static void cont__13_48(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 341: ... :
  // 342:   if
  // 343:     destination.is_a_single_assign_definition:
  // 344:       $source arguments_of(self)(1)
  // 345:       if attribute_kind_of(destination) != NONE:
  // 346:         push &definitions destination = source
  // 347:         return
  // 348:       cond
  // 349:         -> source.is_a_constant || source.is_single_assign:
  // 350:           push &definitions destination = source
  // ...
  frame->slots[4] /* temp__2 */ = create_closure(entry__13_49, 0);
  // 341: if destination.is_a_definition:
  // 342:   if
  // 343:     destination.is_a_single_assign_definition:
  // 344:       $source arguments_of(self)(1)
  // 345:       if attribute_kind_of(destination) != NONE:
  // 346:         push &definitions destination = source
  // 347:         return
  // 348:       cond
  // 349:         -> source.is_a_constant || source.is_single_assign:
  // 350:           push &definitions destination = source
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
static void entry__13_87(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // self: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 362: ... self.output_arguments_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__output_arguments_of();
  func = myself->type;
  frame->cont = cont__13_88;
}
static void cont__13_88(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 362: update_each &self.output_arguments_of: (&argument)
  // 363:   if argument.is_a_definition:
  // 364:     push &definitions argument
  // 365:     !argument.is_an_initialization true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = func__13_89;
  result_count = 1;
  myself = get__update_each();
  func = myself->type;
  frame->cont = cont__13_94;
}
static void entry__13_89(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // argument: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* argument */ = create_cell_with_contents(arguments->slots[0]);
  // 363: ... argument.is_a_definition
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* argument */;
  result_count = 1;
  myself = get__is_a_definition();
  func = myself->type;
  frame->cont = cont__13_90;
}
static void cont__13_90(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 363: ... :
  // 364:   push &definitions argument
  // 365:   !argument.is_an_initialization true
  frame->slots[2] /* temp__2 */ = create_closure(entry__13_91, 0);
  // 363: if argument.is_a_definition:
  // 364:   push &definitions argument
  // 365:   !argument.is_an_initialization true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count =
    frame->caller_result_count >= 1 ?
    frame->caller_result_count-1 : -1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__13_93;
}
static void entry__13_91(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // argument: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* argument */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 364: push &definitions argument
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__definitions();
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* argument */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__13_92;
}
static void cont__13_92(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__definitions(arguments->slots[0]);
  // 365: !argument.is_an_initialization true
  frame->slots[1] /* temp__1 */ = get__true();
  // 365: !argument.is_an_initialization
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* argument */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__is_an_initialization, frame->slots[1] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* argument */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__13_93(void) {
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
static void cont__13_94(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 362: ... &self.output_arguments_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__output_arguments_of, frame->slots[2] /* temp__2 */);
    ((CELL *)frame->slots[0])->contents /* self */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__13_95(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 366: push &statements self
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__statements();
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__13_96;
}
static void cont__13_96(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__statements(arguments->slots[0]);
  // 367: ... final_destinations.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* final_destinations */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__13_97;
}
static void cont__13_97(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 367: ... :
  // 368:   for_each final_destinations: (idx destination)
  // 369:     if destination.is_defined:
  // 370:       $result
  // 371:         output_arguments_of(self)(idx)
  // 372:           .is_an_optional_item false
  // 373:           .is_an_expanded_item false
  // 374:       
  // 375:       if
  // 376:         destination.is_a_function_call:
  // ...
  frame->slots[4] /* temp__2 */ = create_closure(entry__13_98, 0);
  // 367: if final_destinations.is_defined:
  // 368:   for_each final_destinations: (idx destination)
  // 369:     if destination.is_defined:
  // 370:       $result
  // 371:         output_arguments_of(self)(idx)
  // 372:           .is_an_optional_item false
  // 373:           .is_an_expanded_item false
  // 374:       
  // 375:       if
  // 376:         destination.is_a_function_call:
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__13_117;
}
static void entry__13_105(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // destination: 0
  // result: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* destination */
  frame->slots[1] = myself->closure.frame->slots[3]; /* result */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 377: store_result destination result
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* destination */;
  arguments->slots[1] = frame->slots[1] /* result */;
  result_count = frame->caller_result_count;
  myself = var._store_result;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__13_106(void) {
  allocate_initialized_frame_gc(2, 9);
  // slot allocations:
  // destination: 0
  // result: 1
  // identifier: 2
  frame->slots[0] = myself->closure.frame->slots[2]; /* destination */
  frame->slots[1] = myself->closure.frame->slots[3]; /* result */
  frame->slots[2] /* identifier */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 385: destination.is_an_identifier
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* destination */;
  result_count = 1;
  myself = get__is_an_identifier();
  func = myself->type;
  frame->cont = cont__13_107;
}
static void cont__13_107(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 386: -> destination
  frame->slots[4] /* temp__2 */ = create_closure(entry__13_108, 0);
  // 387: -> identifier_of(destination)
  frame->slots[5] /* temp__3 */ = create_closure(entry__13_109, 0);
  // 383: $identifier
  // 384:   if
  // 385:     destination.is_an_identifier
  // 386:     -> destination
  // 387:     -> identifier_of(destination)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  arguments->slots[2] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__13_111;
}
static void entry__13_108(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // destination: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* destination */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 386: -> destination
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* destination */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__13_109(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // destination: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* destination */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 387: ... identifier_of(destination)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* destination */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__13_110;
}
static void cont__13_110(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 387: -> identifier_of(destination)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__13_111(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* identifier */, arguments->slots[0]);
  // 391: ... list(destination)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* destination */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__13_112;
}
static void cont__13_112(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 392: ... list(result)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* result */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__13_113;
}
static void cont__13_113(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 393: ... fragment_of(identifier)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* identifier */;
  result_count = 1;
  myself = get__fragment_of();
  func = myself->type;
  frame->cont = cont__13_114;
}
static void cont__13_114(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__4 */ = arguments->slots[0];
  // 394: ... source_position_of(identifier)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* identifier */;
  result_count = 1;
  myself = get__source_position_of();
  func = myself->type;
  frame->cont = cont__13_115;
}
static void cont__13_115(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__5 */ = arguments->slots[0];
  // 395: ... end_position_of(identifier)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* identifier */;
  result_count = 1;
  myself = get__end_position_of();
  func = myself->type;
  frame->cont = cont__13_116;
}
static void cont__13_116(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__6 */ = arguments->slots[0];
  // 390: assignment
  // 391:   .output_arguments_of list(destination)
  // 392:   .arguments_of list(result)
  // 393:   .fragment_of fragment_of(identifier)
  // 394:   .source_position_of source_position_of(identifier)
  // 395:   .end_position_of end_position_of(identifier)
  {
    NODE *temp = clone_object_and_attributes(get__assignment());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__output_arguments_of, frame->slots[4] /* temp__2 */);
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[5] /* temp__3 */);
    set_attribute_value(temp->attributes, poly_idx__fragment_of, frame->slots[6] /* temp__4 */);
    set_attribute_value(temp->attributes, poly_idx__source_position_of, frame->slots[7] /* temp__5 */);
    set_attribute_value(temp->attributes, poly_idx__end_position_of, frame->slots[8] /* temp__6 */);
    frame->slots[3] /* temp__1 */ = temp;

  }
  // 389: simplify_statement
  // 390:   assignment
  // 391:     .output_arguments_of list(destination)
  // 392:     .arguments_of list(result)
  // 393:     .fragment_of fragment_of(identifier)
  // 394:     .source_position_of source_position_of(identifier)
  // 395:     .end_position_of end_position_of(identifier)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__simplify_statement();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__13_101(void) {
  allocate_initialized_frame_gc(3, 7);
  // slot allocations:
  // self: 0
  // idx: 1
  // destination: 2
  // result: 3
  frame->slots[0] = myself->closure.frame->slots[2]; /* self */
  frame->slots[1] = myself->closure.frame->slots[0]; /* idx */
  frame->slots[2] = myself->closure.frame->slots[1]; /* destination */
  frame->slots[3] /* result */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 371: output_arguments_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__output_arguments_of();
  func = myself->type;
  frame->cont = cont__13_102;
}
static void cont__13_102(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 371: output_arguments_of(self)(idx)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* idx */;
  result_count = 1;
  myself = frame->slots[5] /* temp__2 */;
  func = myself->type;
  frame->cont = cont__13_103;
}
static void cont__13_103(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 370: $result
  // 371:   output_arguments_of(self)(idx)
  // 372:     .is_an_optional_item false
  // 373:     .is_an_expanded_item false
  {
    NODE *temp = clone_object_and_attributes(frame->slots[4] /* temp__1 */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__is_an_optional_item, get__false());
    set_attribute_value(temp->attributes, poly_idx__is_an_expanded_item, get__false());
    initialize_future(frame->slots[3] /* result */, temp);

  }
  // 376: destination.is_a_function_call
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* destination */;
  result_count = 1;
  myself = get__is_a_function_call();
  func = myself->type;
  frame->cont = cont__13_104;
}
static void cont__13_104(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 376: ... :
  // 377:   store_result destination result
  frame->slots[5] /* temp__2 */ = create_closure(entry__13_105, 0);
  // 378: :
  // 379:   #
  // 380:     ATTENTION: strange - only two source code files have destinations
  // 381:     that actually are identifier nodes - maybe an error in the AST?
  // 382:   
  // 383:   $identifier
  // 384:     if
  // 385:       destination.is_an_identifier
  // 386:       -> destination
  // 387:       -> identifier_of(destination)
  // ...
  frame->slots[6] /* temp__3 */ = create_closure(entry__13_106, 0);
  // 375: if
  // 376:   destination.is_a_function_call:
  // 377:     store_result destination result
  // 378:   :
  // 379:     #
  // 380:       ATTENTION: strange - only two source code files have destinations
  // 381:       that actually are identifier nodes - maybe an error in the AST?
  // 382:     
  // 383:     $identifier
  // 384:       if
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
static void entry__13_99(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // idx: 0
  // destination: 1
  // self: 2
  frame->slots[2] = myself->closure.frame->slots[1]; /* self */
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 369: ... destination.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* destination */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__13_100;
}
static void cont__13_100(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 369: ... :
  // 370:   $result
  // 371:     output_arguments_of(self)(idx)
  // 372:       .is_an_optional_item false
  // 373:       .is_an_expanded_item false
  // 374:   
  // 375:   if
  // 376:     destination.is_a_function_call:
  // 377:       store_result destination result
  // 378:     :
  // ...
  frame->slots[4] /* temp__2 */ = create_closure(entry__13_101, 0);
  // 369: if destination.is_defined:
  // 370:   $result
  // 371:     output_arguments_of(self)(idx)
  // 372:       .is_an_optional_item false
  // 373:       .is_an_expanded_item false
  // 374:   
  // 375:   if
  // 376:     destination.is_a_function_call:
  // 377:       store_result destination result
  // 378:     :
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
static void entry__13_98(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // final_destinations: 0
  // self: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* final_destinations */
  frame->slots[1] = myself->closure.frame->slots[0]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 368: ... : (idx destination)
  // 369:   if destination.is_defined:
  // 370:     $result
  // 371:       output_arguments_of(self)(idx)
  // 372:         .is_an_optional_item false
  // 373:         .is_an_expanded_item false
  // 374:     
  // 375:     if
  // 376:       destination.is_a_function_call:
  // 377:         store_result destination result
  // ...
  frame->slots[2] /* temp__1 */ = create_closure(entry__13_99, 2);
  // 368: for_each final_destinations: (idx destination)
  // 369:   if destination.is_defined:
  // 370:     $result
  // 371:       output_arguments_of(self)(idx)
  // 372:         .is_an_optional_item false
  // 373:         .is_an_expanded_item false
  // 374:     
  // 375:     if
  // 376:       destination.is_a_function_call:
  // 377:         store_result destination result
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* final_destinations */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__13_117(void) {
  myself = frame->slots[1] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__14_1(void) {
  allocate_initialized_frame_gc(1, 10);
  // slot allocations:
  // self: 0
  // temp: 1
  frame->slots[1] /* temp */ = create_future();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 401: show_compiler_debug_info "simplify function call"
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
  // 402: $temp temporary_identifier()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = var._temporary_identifier;
  func = myself->type;
  frame->cont = cont__14_4;
}
static void cont__14_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* temp */, arguments->slots[0]);
  // 405: ... functor_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__functor_of();
  func = myself->type;
  frame->cont = cont__14_5;
}
static void cont__14_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 406: ... output_arguments_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__output_arguments_of();
  func = myself->type;
  frame->cont = cont__14_6;
}
static void cont__14_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__4 */ = arguments->slots[0];
  // 406: ... push(output_arguments_of(self) temp)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__4 */;
  arguments->slots[1] = frame->slots[1] /* temp */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__14_7;
}
static void cont__14_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 407: ... arguments_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__14_8;
}
static void cont__14_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__5 */ = arguments->slots[0];
  // 408: ... fragment_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__fragment_of();
  func = myself->type;
  frame->cont = cont__14_9;
}
static void cont__14_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__6 */ = arguments->slots[0];
  // 409: ... source_position_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__source_position_of();
  func = myself->type;
  frame->cont = cont__14_10;
}
static void cont__14_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__7 */ = arguments->slots[0];
  // 410: ... end_position_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__end_position_of();
  func = myself->type;
  frame->cont = cont__14_11;
}
static void cont__14_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__8 */ = arguments->slots[0];
  // 404: procedure_call
  // 405:   .functor_of functor_of(self)
  // 406:   .output_arguments_of push(output_arguments_of(self) temp)
  // 407:   .arguments_of arguments_of(self)
  // 408:   .fragment_of fragment_of(self)
  // 409:   .source_position_of source_position_of(self)
  // 410:   .end_position_of end_position_of(self)
  {
    NODE *temp = clone_object_and_attributes(get__procedure_call());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__functor_of, frame->slots[3] /* temp__2 */);
    set_attribute_value(temp->attributes, poly_idx__output_arguments_of, frame->slots[4] /* temp__3 */);
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[6] /* temp__5 */);
    set_attribute_value(temp->attributes, poly_idx__fragment_of, frame->slots[7] /* temp__6 */);
    set_attribute_value(temp->attributes, poly_idx__source_position_of, frame->slots[8] /* temp__7 */);
    set_attribute_value(temp->attributes, poly_idx__end_position_of, frame->slots[9] /* temp__8 */);
    frame->slots[2] /* temp__1 */ = temp;

  }
  // 403: simplify_statement
  // 404:   procedure_call
  // 405:     .functor_of functor_of(self)
  // 406:     .output_arguments_of push(output_arguments_of(self) temp)
  // 407:     .arguments_of arguments_of(self)
  // 408:     .fragment_of fragment_of(self)
  // 409:     .source_position_of source_position_of(self)
  // 410:     .end_position_of end_position_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__simplify_statement();
  func = myself->type;
  frame->cont = cont__14_12;
}
static void cont__14_12(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 411: -> temp
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__15_1(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // self: 0
  // dummy_destinations: 1
  frame->slots[1] /* dummy_destinations */ = create_future();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* self */ = create_cell_with_contents(arguments->slots[0]);
  // 417: show_compiler_debug_info "simplify attribute-value pair"
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
  // 418: simplify_arguments &self $_dummy_destinations
  // 419:   # There must not be any output arguments!!!
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 2;
  myself = var._simplify_arguments;
  func = myself->type;
  frame->cont = cont__15_4;
}
static void cont__15_4(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* self */ = arguments->slots[0];
  frame->slots[2] /* temp__1 */ = arguments->slots[1];
  // 418: ... _dummy_destinations
  initialize_future(frame->slots[1] /* dummy_destinations */, frame->slots[2] /* temp__1 */);
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__16_1(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // self: 0
  // dummy_destinations: 1
  frame->slots[1] /* dummy_destinations */ = create_future();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* self */ = create_cell_with_contents(arguments->slots[0]);
  // 425: show_compiler_debug_info "simplify attribute-function pair"
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
  // 426: simplify_arguments &self $_dummy_destinations
  // 427:   # There must not be any output arguments!!!
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 2;
  myself = var._simplify_arguments;
  func = myself->type;
  frame->cont = cont__16_4;
}
static void cont__16_4(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* self */ = arguments->slots[0];
  frame->slots[2] /* temp__1 */ = arguments->slots[1];
  // 426: ... _dummy_destinations
  initialize_future(frame->slots[1] /* dummy_destinations */, frame->slots[2] /* temp__1 */);
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__17_1(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // self: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 433: show_compiler_debug_info "simplify C-code"
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
  // 434: push &actions: !use_inline_c true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__actions();
  arguments->slots[1] = func__17_4;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__17_5;
}
static void entry__17_4(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 434: ... !use_inline_c true
  set__use_inline_c(get__true());
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__17_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__actions(arguments->slots[0]);
  // 436: kind_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__kind_of();
  func = myself->type;
  frame->cont = cont__17_6;
}
static void cont__17_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 437: ... :
  // 438:   $name name_of(identifier_of(self))
  // 439:   push &actions: !defined_structs(name) true
  frame->slots[2] /* temp__2 */ = create_closure(entry__17_7, 0);
  // 440: ... :
  // 441:   $name name_of(identifier_of(self))
  // 442:   push &actions: !defined_nodes(name) self
  frame->slots[3] /* temp__3 */ = create_closure(entry__17_13, 0);
  // 443: ... :
  // 444:   $name behind(source_of(self) .before. '(' alt(' ' '*') -1)
  // 445:   push &actions: !defined_functions(name) true
  frame->slots[4] /* temp__4 */ = create_closure(entry__17_19, 0);
  // 435: case
  // 436:   kind_of(self)
  // 437:   "struct":
  // 438:     $name name_of(identifier_of(self))
  // 439:     push &actions: !defined_structs(name) true
  // 440:   "node":
  // 441:     $name name_of(identifier_of(self))
  // 442:     push &actions: !defined_nodes(name) self
  // 443:   "function":
  // 444:     $name behind(source_of(self) .before. '(' alt(' ' '*') -1)
  // ...
  argument_count = 7;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = string__17_28;
  arguments->slots[2] = frame->slots[2] /* temp__2 */;
  arguments->slots[3] = string__17_29;
  arguments->slots[4] = frame->slots[3] /* temp__3 */;
  arguments->slots[5] = string__17_30;
  arguments->slots[6] = frame->slots[4] /* temp__4 */;
  result_count = 0;
  myself = get__case();
  func = myself->type;
  frame->cont = cont__17_31;
}
static void entry__17_7(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // self: 0
  // name: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  frame->slots[1] /* name */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 438: ... identifier_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__17_8;
}
static void cont__17_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 438: $name name_of(identifier_of(self))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__name_of();
  func = myself->type;
  frame->cont = cont__17_9;
}
static void cont__17_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* name */, arguments->slots[0]);
  // 439: ... : !defined_structs(name) true
  frame->slots[2] /* temp__1 */ = create_closure(entry__17_10, 0);
  // 439: push &actions: !defined_structs(name) true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__actions();
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__17_12;
}
static void entry__17_10(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 439: ... !defined_structs(name) true
  frame->slots[1] /* temp__1 */ = get__true();
  // 439: ... !defined_structs(name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__defined_structs();
  func = myself->type;
  frame->cont = cont__17_11;
}
static void cont__17_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__defined_structs(arguments->slots[0]);
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__17_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__actions(arguments->slots[0]);
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__17_13(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // self: 0
  // name: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  frame->slots[1] /* name */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 441: ... identifier_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__17_14;
}
static void cont__17_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 441: $name name_of(identifier_of(self))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__name_of();
  func = myself->type;
  frame->cont = cont__17_15;
}
static void cont__17_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* name */, arguments->slots[0]);
  // 442: ... : !defined_nodes(name) self
  frame->slots[2] /* temp__1 */ = create_closure(entry__17_16, 0);
  // 442: push &actions: !defined_nodes(name) self
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__actions();
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__17_18;
}
static void entry__17_16(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // name: 0
  // self: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* name */
  frame->slots[1] = myself->closure.frame->slots[0]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 442: ... !defined_nodes(name) self
  frame->slots[2] /* temp__1 */ = frame->slots[1] /* self */;
  // 442: ... !defined_nodes(name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__defined_nodes();
  func = myself->type;
  frame->cont = cont__17_17;
}
static void cont__17_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__defined_nodes(arguments->slots[0]);
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__17_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__actions(arguments->slots[0]);
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__17_19(void) {
  allocate_initialized_frame_gc(1, 6);
  // slot allocations:
  // self: 0
  // name: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  frame->slots[1] /* name */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 444: ... source_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__source_of();
  func = myself->type;
  frame->cont = cont__17_20;
}
static void cont__17_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 444: ... source_of(self) .before. '('
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = character__40;
  result_count = 1;
  myself = get__before();
  func = myself->type;
  frame->cont = cont__17_21;
}
static void cont__17_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 444: ... alt(' ' '*')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__32;
  arguments->slots[1] = character__42;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__17_22;
}
static void cont__17_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 444: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__17_23;
}
static void cont__17_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__4 */ = arguments->slots[0];
  // 444: $name behind(source_of(self) .before. '(' alt(' ' '*') -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  arguments->slots[2] = frame->slots[5] /* temp__4 */;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__17_24;
}
static void cont__17_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* name */, arguments->slots[0]);
  // 445: ... : !defined_functions(name) true
  frame->slots[2] /* temp__1 */ = create_closure(entry__17_25, 0);
  // 445: push &actions: !defined_functions(name) true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__actions();
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__17_27;
}
static void entry__17_25(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 445: ... !defined_functions(name) true
  frame->slots[1] /* temp__1 */ = get__true();
  // 445: ... !defined_functions(name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__defined_functions();
  func = myself->type;
  frame->cont = cont__17_26;
}
static void cont__17_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__defined_functions(arguments->slots[0]);
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__17_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__actions(arguments->slots[0]);
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__17_31(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 446: push &definitions self
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__definitions();
  arguments->slots[1] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__17_32;
}
static void cont__17_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__definitions(arguments->slots[0]);
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__18_1(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // self: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* self */ = create_cell_with_contents(arguments->slots[0]);
  // 452: show_compiler_debug_info "simplify C-body"
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
  // 453: push &actions: !use_inline_c true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__actions();
  arguments->slots[1] = func__18_4;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__18_5;
}
static void entry__18_4(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 453: ... !use_inline_c true
  set__use_inline_c(get__true());
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__18_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__actions(arguments->slots[0]);
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
EXPORT void collect__simplifier(void) {
  var.sim2c__simplify_statement = collect_node(var.sim2c__simplify_statement);
  var.sim2c__simplify_expression = collect_node(var.sim2c__simplify_expression);
  var._temporary_identifier = collect_node(var._temporary_identifier);
  string__5_3 = collect_node(string__5_3);
  var._simplify_arguments = collect_node(var._simplify_arguments);
  var.sim2c__check_usage = collect_node(var.sim2c__check_usage);
  string__7_9 = collect_node(string__7_9);
  string__7_10 = collect_node(string__7_10);
  string__7_17 = collect_node(string__7_17);
  string__7_18 = collect_node(string__7_18);
  string__7_25 = collect_node(string__7_25);
  string__7_26 = collect_node(string__7_26);
  string__7_33 = collect_node(string__7_33);
  string__7_34 = collect_node(string__7_34);
  string__8_2 = collect_node(string__8_2);
  string__9_2 = collect_node(string__9_2);
  string__10_2 = collect_node(string__10_2);
  string__10_10 = collect_node(string__10_10);
  string__10_11 = collect_node(string__10_11);
  var._do_store = collect_node(var._do_store);
  var._store_result = collect_node(var._store_result);
  string__13_2 = collect_node(string__13_2);
  string__14_2 = collect_node(string__14_2);
  string__15_2 = collect_node(string__15_2);
  string__16_2 = collect_node(string__16_2);
  string__17_2 = collect_node(string__17_2);
  string__17_28 = collect_node(string__17_28);
  string__17_29 = collect_node(string__17_29);
  string__17_30 = collect_node(string__17_30);
  string__18_2 = collect_node(string__18_2);
}

static int already_run_phase_1 = false;

EXPORT void phase_1__simplifier(void) {
  if (already_run_phase_1) return;
  already_run_phase_1 = true;
  register_module_info(&module_info);
  define_polymorphic_function("sim2c", "simplify_statement", get__sim2c__simplify_statement, &poly_idx__sim2c__simplify_statement, &var.sim2c__simplify_statement);
  define_polymorphic_function("sim2c", "simplify_expression", get__sim2c__simplify_expression, &poly_idx__sim2c__simplify_expression, &var.sim2c__simplify_expression);
}

static int already_run_phase_2 = false;

EXPORT void phase_2__simplifier(void) {
  if (already_run_phase_2) return;
  already_run_phase_2 = true;
  number__0 = from_uint32(0U);
  character__40 = from_uchar32(40);
  character__32 = from_uchar32(32);
  number__1 = from_uint32(1U);
  character__42 = from_uchar32(42);
  func__5_1 = create_function(entry__5_1, 0);
  func__6_3 = create_function(entry__6_3, 1);
  func__6_1 = create_function(entry__6_1, 1);
  func__7_1 = create_function(entry__7_1, 3);
  func__8_1 = create_function(entry__8_1, 1);
  func__9_1 = create_function(entry__9_1, 1);
  func__10_1 = create_function(entry__10_1, 1);
  func__11_5 = create_function(entry__11_5, 1);
  func__11_45 = create_function(entry__11_45, 0);
  func__11_46 = create_function(entry__11_46, 0);
  func__11_1 = create_function(entry__11_1, 5);
  func__12_1 = create_function(entry__12_1, -1);
  func__13_89 = create_function(entry__13_89, 1);
  func__13_1 = create_function(entry__13_1, 1);
  func__14_1 = create_function(entry__14_1, 1);
  func__15_1 = create_function(entry__15_1, 1);
  func__16_1 = create_function(entry__16_1, 1);
  func__17_4 = create_function(entry__17_4, 0);
  func__17_1 = create_function(entry__17_1, 1);
  func__18_4 = create_function(entry__18_4, 0);
  func__18_1 = create_function(entry__18_1, 1);
}

static int already_run_phase_3 = false;

EXPORT void phase_3__simplifier(void) {
  if (already_run_phase_3) return;
  already_run_phase_3 = true;
  set_module("simplifier");
  set_used_namespaces(used_namespaces);
  register_dynamic(&dyna_idx__defined_names);
  define__defined_names(create_future());
  register_dynamic(&dyna_idx__inherited_names);
  define__inherited_names(create_future());
  string__5_3 = from_latin_1_string("temp__", 6);
  string__7_9 = from_latin_1_string("Invalid access to read-only variable \042", 38);
  string__7_10 = from_latin_1_string("\042", 1);
  string__7_17 = from_latin_1_string("Invalid access to static read-write variable \042", 46);
  string__7_18 = from_latin_1_string("\042", 1);
  string__7_25 = from_latin_1_string("Invalid access to dynamic read-only variable \042", 46);
  string__7_26 = from_latin_1_string("\042", 1);
  string__7_33 = from_latin_1_string("Invalid access to dynamic read-write variable \042", 47);
  string__7_34 = from_latin_1_string("\042", 1);
  define_single_assign_static("sim2c", "check_usage", get__sim2c__check_usage, &var.sim2c__check_usage);
  string__8_2 = from_latin_1_string("simplify statement (default)", 28);
  string__9_2 = from_latin_1_string("simplify expression (default)", 29);
  string__10_2 = from_latin_1_string("simplify body", 13);
  string__10_10 = from_latin_1_string("An identifier named \042", 21);
  string__10_11 = from_latin_1_string("\042 was already defined in an outer scope or in a used namespace", 62);
  string__13_2 = from_latin_1_string("simplify statement", 18);
  string__14_2 = from_latin_1_string("simplify function call", 22);
  string__15_2 = from_latin_1_string("simplify attribute-value pair", 29);
  string__16_2 = from_latin_1_string("simplify attribute-function pair", 32);
  string__17_2 = from_latin_1_string("simplify C-code", 15);
  string__17_28 = from_latin_1_string("struct", 6);
  string__17_29 = from_latin_1_string("node", 4);
  string__17_30 = from_latin_1_string("function", 8);
  string__18_2 = from_latin_1_string("simplify C-body", 15);
}

static int already_run_phase_4 = false;

EXPORT void phase_4__simplifier(void) {
  if (already_run_phase_4) return;
  already_run_phase_4 = true;
  set_module("simplifier");
  set_used_namespaces(used_namespaces);
  use_read_only(NULL, "DYNAMIC_MULTI", &get__DYNAMIC_MULTI, &get_value_or_future__DYNAMIC_MULTI);
  use_read_only(NULL, "DYNAMIC_SINGLE", &get__DYNAMIC_SINGLE, &get_value_or_future__DYNAMIC_SINGLE);
  use_read_only(NULL, "NONE", &get__NONE, &get_value_or_future__NONE);
  use_read_only(NULL, "POLYMORPHIC", &get__POLYMORPHIC, &get_value_or_future__POLYMORPHIC);
  use_read_only(NULL, "STATIC_MULTI", &get__STATIC_MULTI, &get_value_or_future__STATIC_MULTI);
  use_read_only(NULL, "STATIC_SINGLE", &get__STATIC_SINGLE, &get_value_or_future__STATIC_SINGLE);
  use_read_only(NULL, "SyntaxError", &get__SyntaxError, &get_value_or_future__SyntaxError);
  use_read_write(NULL, "actions", &get__actions, &set__actions);
  use_single_assign_dynamic(NULL, "already_defined_names", &get__already_defined_names, &define__already_defined_names);
  use_read_only(NULL, "alt", &get__alt, &get_value_or_future__alt);
  use_polymorphic_function(NULL, "arguments_of", &get__arguments_of, &poly_idx__arguments_of);
  use_read_only(NULL, "assignment", &get__assignment, &get_value_or_future__assignment);
  use_read_only(NULL, "attribute_function_pair", &get__attribute_function_pair, &get_value_or_future__attribute_function_pair);
  use_read_only(NULL, "attribute_kind_of", &get__attribute_kind_of, &get_value_or_future__attribute_kind_of);
  use_read_only(NULL, "attribute_value_pair", &get__attribute_value_pair, &get_value_or_future__attribute_value_pair);
  use_read_only(NULL, "before", &get__before, &get_value_or_future__before);
  use_read_only(NULL, "behind", &get__behind, &get_value_or_future__behind);
  use_read_only(NULL, "case", &get__case, &get_value_or_future__case);
  use_read_only(NULL, "check_usage", &get__check_usage, &get_value_or_future__check_usage);
  use_read_only(NULL, "cond", &get__cond, &get_value_or_future__cond);
  use_polymorphic_function(NULL, "continuation_of", &get__continuation_of, &poly_idx__continuation_of);
  use_polymorphic_function(NULL, "default_value_of", &get__default_value_of, &poly_idx__default_value_of);
  use_read_write(NULL, "defined_functions", &get__defined_functions, &set__defined_functions);
  use_read_only(NULL, "defined_names_of", &get__defined_names_of, &get_value_or_future__defined_names_of);
  use_read_write(NULL, "defined_nodes", &get__defined_nodes, &set__defined_nodes);
  use_read_write(NULL, "defined_structs", &get__defined_structs, &set__defined_structs);
  use_multi_assign_dynamic(NULL, "definitions", &get__definitions, &set__definitions, &define__definitions);
  use_polymorphic_function(NULL, "definitions_of", &get__definitions_of, &poly_idx__definitions_of);
  use_read_only(NULL, "do", &get__do, &get_value_or_future__do);
  use_read_only(NULL, "drop", &get__drop, &get_value_or_future__drop);
  use_read_only(NULL, "empty_list", &get__empty_list, &get_value_or_future__empty_list);
  use_read_only(NULL, "empty_table", &get__empty_table, &get_value_or_future__empty_table);
  use_polymorphic_function(NULL, "end_position_of", &get__end_position_of, &poly_idx__end_position_of);
  use_read_only(NULL, "extend_to", &get__extend_to, &get_value_or_future__extend_to);
  use_read_only(NULL, "false", &get__false, &get_value_or_future__false);
  use_read_only(NULL, "for_each", &get__for_each, &get_value_or_future__for_each);
  use_polymorphic_function(NULL, "fragment_of", &get__fragment_of, &poly_idx__fragment_of);
  use_polymorphic_function(NULL, "functor_of", &get__functor_of, &poly_idx__functor_of);
  use_polymorphic_function(NULL, "identifier_of", &get__identifier_of, &poly_idx__identifier_of);
  use_read_only(NULL, "if", &get__if, &get_value_or_future__if);
  use_read_only(NULL, "inc", &get__inc, &get_value_or_future__inc);
  use_polymorphic_function(NULL, "inherited_names_of", &get__inherited_names_of, &poly_idx__inherited_names_of);
  use_read_only(NULL, "is_a_constant", &get__is_a_constant, &get_value_or_future__is_a_constant);
  use_read_only(NULL, "is_a_definition", &get__is_a_definition, &get_value_or_future__is_a_definition);
  use_read_only(NULL, "is_a_function_call", &get__is_a_function_call, &get_value_or_future__is_a_function_call);
  use_read_only(NULL, "is_a_list", &get__is_a_list, &get_value_or_future__is_a_list);
  use_read_only(NULL, "is_a_method_definition", &get__is_a_method_definition, &get_value_or_future__is_a_method_definition);
  use_read_only(NULL, "is_a_multi_assign_definition", &get__is_a_multi_assign_definition, &get_value_or_future__is_a_multi_assign_definition);
  use_read_only(NULL, "is_a_remark", &get__is_a_remark, &get_value_or_future__is_a_remark);
  use_read_only(NULL, "is_a_single_assign_definition", &get__is_a_single_assign_definition, &get_value_or_future__is_a_single_assign_definition);
  use_read_only(NULL, "is_a_static_single_definition", &get__is_a_static_single_definition, &get_value_or_future__is_a_static_single_definition);
  use_read_only(NULL, "is_a_temporary", &get__is_a_temporary, &get_value_or_future__is_a_temporary);
  use_read_only(NULL, "is_an_assignment", &get__is_an_assignment, &get_value_or_future__is_an_assignment);
  use_read_only(NULL, "is_an_attribute_access", &get__is_an_attribute_access, &get_value_or_future__is_an_attribute_access);
  use_polymorphic_function(NULL, "is_an_expanded_item", &get__is_an_expanded_item, &poly_idx__is_an_expanded_item);
  use_read_only(NULL, "is_an_identifier", &get__is_an_identifier, &get_value_or_future__is_an_identifier);
  use_polymorphic_function(NULL, "is_an_initialization", &get__is_an_initialization, &poly_idx__is_an_initialization);
  use_polymorphic_function(NULL, "is_an_optional_item", &get__is_an_optional_item, &poly_idx__is_an_optional_item);
  use_read_only(NULL, "is_defined", &get__is_defined, &get_value_or_future__is_defined);
  use_read_only(NULL, "is_empty", &get__is_empty, &get_value_or_future__is_empty);
  use_read_only(NULL, "is_single_assign", &get__is_single_assign, &get_value_or_future__is_single_assign);
  use_read_only(NULL, "kind_of", &get__kind_of, &get_value_or_future__kind_of);
  use_read_only(NULL, "length_of", &get__length_of, &get_value_or_future__length_of);
  use_read_only(NULL, "list", &get__list, &get_value_or_future__list);
  use_read_only(NULL, "might_be_constant", &get__might_be_constant, &get_value_or_future__might_be_constant);
  use_polymorphic_function(NULL, "name_of", &get__name_of, &poly_idx__name_of);
  use_polymorphic_function(NULL, "output_arguments_of", &get__output_arguments_of, &poly_idx__output_arguments_of);
  use_polymorphic_function(NULL, "parameters_of", &get__parameters_of, &poly_idx__parameters_of);
  use_read_only(NULL, "peek", &get__peek, &get_value_or_future__peek);
  use_read_only(NULL, "pop", &get__pop, &get_value_or_future__pop);
  use_read_only(NULL, "procedure_call", &get__procedure_call, &get_value_or_future__procedure_call);
  use_read_only(NULL, "push", &get__push, &get_value_or_future__push);
  use_polymorphic_function(NULL, "result_count_of", &get__result_count_of, &poly_idx__result_count_of);
  use_read_only(NULL, "show_compiler_debug_info", &get__show_compiler_debug_info, &get_value_or_future__show_compiler_debug_info);
  use_read_only("sim2c", "attribute_function_pair", &get__sim2c__attribute_function_pair, &get_value_or_future__sim2c__attribute_function_pair);
  use_read_only("sim2c", "attribute_value_pair", &get__sim2c__attribute_value_pair, &get_value_or_future__sim2c__attribute_value_pair);
  use_read_only("sim2c", "body", &get__sim2c__body, &get_value_or_future__sim2c__body);
  use_read_only("sim2c", "c_body", &get__sim2c__c_body, &get_value_or_future__sim2c__c_body);
  use_read_only("sim2c", "c_code", &get__sim2c__c_code, &get_value_or_future__sim2c__c_code);
  use_read_only("sim2c", "call", &get__sim2c__call, &get_value_or_future__sim2c__call);
  use_read_only("sim2c", "function_call", &get__sim2c__function_call, &get_value_or_future__sim2c__function_call);
  use_multi_assign_dynamic("sim2c", "temp_idx", &get__sim2c__temp_idx, &set__sim2c__temp_idx, &define__sim2c__temp_idx);
  use_polymorphic_function(NULL, "simplify_expression", &get__simplify_expression, &poly_idx__simplify_expression);
  use_polymorphic_function(NULL, "simplify_statement", &get__simplify_statement, &poly_idx__simplify_statement);
  use_read_only(NULL, "source_of", &get__source_of, &get_value_or_future__source_of);
  use_polymorphic_function(NULL, "source_position_of", &get__source_position_of, &poly_idx__source_position_of);
  use_multi_assign_dynamic(NULL, "statements", &get__statements, &set__statements, &define__statements);
  use_polymorphic_function(NULL, "statements_of", &get__statements_of, &poly_idx__statements_of);
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
  use_read_write(NULL, "temp_idx", &get__temp_idx, &set__temp_idx);
  use_read_only(NULL, "temporary", &get__temporary, &get_value_or_future__temporary);
  use_polymorphic_function(NULL, "temporary_count_of", &get__temporary_count_of, &poly_idx__temporary_count_of);
  use_read_only(NULL, "true", &get__true, &get_value_or_future__true);
  use_read_only("types", "grammar_node", &get__types__grammar_node, &get_value_or_future__types__grammar_node);
  use_read_only(NULL, "undefined", &get__undefined, &get_value_or_future__undefined);
  use_read_only(NULL, "unless", &get__unless, &get_value_or_future__unless);
  use_read_only(NULL, "update_each", &get__update_each, &get_value_or_future__update_each);
  use_read_write(NULL, "use_inline_c", &get__use_inline_c, &set__use_inline_c);
  use_read_only(NULL, "used_names_of", &get__used_names_of, &get_value_or_future__used_names_of);
  use_read_only(NULL, "variable_kind_of", &get__variable_kind_of, &get_value_or_future__variable_kind_of);
  define_method("types", "grammar_node", poly_idx__simplify_statement, func__8_1);
  define_method("types", "grammar_node", poly_idx__simplify_expression, func__9_1);
  define_method("sim2c", "body", poly_idx__simplify_expression, func__10_1);
  define_method("sim2c", "call", poly_idx__simplify_statement, func__13_1);
  define_method("sim2c", "function_call", poly_idx__simplify_expression, func__14_1);
  define_method("sim2c", "attribute_value_pair", poly_idx__simplify_expression, func__15_1);
  define_method("sim2c", "attribute_function_pair", poly_idx__simplify_expression, func__16_1);
  define_method("sim2c", "c_code", poly_idx__simplify_statement, func__17_1);
  define_method("sim2c", "c_body", poly_idx__simplify_expression, func__18_1);
}

static int already_run_phase_5 = false;

EXPORT void phase_5__simplifier(void) {
  if (already_run_phase_5) return;
  already_run_phase_5 = true;
  assign_value(&var.sim2c__simplify_statement, create_function(type__sim2c__simplify_statement, -1));
  assign_value(&var.sim2c__simplify_expression, create_function(type__sim2c__simplify_expression, -1));
  maybe_initialize_future(get__defined_names(), get__empty_table());
  maybe_initialize_future(get__inherited_names(), get__empty_table());
  assign_variable(&var._temporary_identifier, &func__5_1);
  assign_variable(&var._simplify_arguments, &func__6_1);
  assign_variable(&var.sim2c__check_usage, &func__7_1);
  assign_variable(&var._do_store, &func__11_1);
  assign_variable(&var._store_result, &func__12_1);
}

static int already_run_phase_6 = false;

EXPORT void phase_6__simplifier(void) {
  if (already_run_phase_6) return;
  already_run_phase_6 = true;
  register_collector(collect__simplifier);
}
