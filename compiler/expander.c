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
IMPORT NODE *create_cell(void);
typedef struct CELL {
  FUNC type;
  struct ATTRIBUTES *attributes;
  NODE *contents;
} CELL;
IMPORT NODE *create_closure(FUNC type, int par_count);
IMPORT int result_count;
IMPORT void invalid_results_error(void);
IMPORT NODE *create_cell_with_contents(NODE *contents);
IMPORT NODE *create_future(void);
IMPORT void initialize_future(NODE *var, NODE *val);
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
IMPORT void define_single_assign_static(
  const char *namespace, const char *name,
  NODE_GETTER getter, NODE **var_p
);
IMPORT void use_polymorphic_function(
  const char *namespace, const char *name, NODE_GETTER *getter, int *id
);
IMPORT void use_read_only(
  const char *namespace, const char *name,
  NODE_GETTER *getter, NODE_GETTER *get_value_or_future
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
static int poly_idx__arguments_of;
static NODE_GETTER get__arguments_of;
static NODE_GETTER get__body;
static NODE_GETTER get_value_or_future__body;
static NODE_GETTER get__case;
static NODE_GETTER get_value_or_future__case;
static NODE_GETTER get__compiler__attribute_function_pair;
static NODE_GETTER get_value_or_future__compiler__attribute_function_pair;
static NODE_GETTER get__compiler__attribute_value_pair;
static NODE_GETTER get_value_or_future__compiler__attribute_value_pair;
static NODE_GETTER get__compiler__body;
static NODE_GETTER get_value_or_future__compiler__body;
static NODE_GETTER get__compiler__call;
static NODE_GETTER get_value_or_future__compiler__call;
static NODE_GETTER get__compiler__function_call;
static NODE_GETTER get_value_or_future__compiler__function_call;
static int poly_idx__default_value_of;
static NODE_GETTER get__default_value_of;
static NODE_GETTER get__empty_list;
static NODE_GETTER get_value_or_future__empty_list;
static int poly_idx__end_position_of;
static NODE_GETTER get__end_position_of;
static int poly_idx__expand_expression;
static NODE_GETTER get__expand_expression;
static NODE_GETTER get__expand_operator_call;
static NODE_GETTER get_value_or_future__expand_operator_call;
static int poly_idx__expand_statement;
static NODE_GETTER get__expand_statement;
static NODE_GETTER get__expression_of;
static NODE_GETTER get_value_or_future__expression_of;
static NODE_GETTER get__false;
static NODE_GETTER get_value_or_future__false;
static NODE_GETTER get__for_each;
static NODE_GETTER get_value_or_future__for_each;
static int poly_idx__fragment_of;
static NODE_GETTER get__fragment_of;
static NODE_GETTER get__function_call;
static NODE_GETTER get_value_or_future__function_call;
static int poly_idx__functor_of;
static NODE_GETTER get__functor_of;
static NODE_GETTER get__if;
static NODE_GETTER get_value_or_future__if;
static NODE_GETTER get__is_a_backquoted_expression;
static NODE_GETTER get_value_or_future__is_a_backquoted_expression;
static NODE_GETTER get__is_a_function_call;
static NODE_GETTER get_value_or_future__is_a_function_call;
static NODE_GETTER get__is_an_operator_symbol;
static NODE_GETTER get_value_or_future__is_an_operator_symbol;
static NODE_GETTER get__is_defined;
static NODE_GETTER get_value_or_future__is_defined;
static NODE_GETTER get__length_of;
static NODE_GETTER get_value_or_future__length_of;
static NODE_GETTER get__list;
static NODE_GETTER get_value_or_future__list;
static NODE_GETTER get__name_of;
static NODE_GETTER get_value_or_future__name_of;
static int poly_idx__node__text_of;
static NODE_GETTER get__node__text_of;
static int poly_idx__parameters_of;
static NODE_GETTER get__parameters_of;
static NODE_GETTER get__push;
static NODE_GETTER get_value_or_future__push;
static int poly_idx__result_count_of;
static NODE_GETTER get__result_count_of;
static NODE_GETTER get__return_statement;
static NODE_GETTER get_value_or_future__return_statement;
static NODE_GETTER get__show_compiler_debug_info;
static NODE_GETTER get_value_or_future__show_compiler_debug_info;
static int poly_idx__source_position_of;
static NODE_GETTER get__source_position_of;
static int poly_idx__statements_of;
static NODE_GETTER get__statements_of;
static NODE_GETTER get__std__and;
static NODE_GETTER get_value_or_future__std__and;
static NODE_GETTER get__std__equal;
static NODE_GETTER get_value_or_future__std__equal;
static NODE_GETTER get__std_identifier;
static NODE_GETTER get_value_or_future__std_identifier;
static NODE_GETTER get__string_literal;
static NODE_GETTER get_value_or_future__string_literal;
static NODE_GETTER get__swap;
static NODE_GETTER get_value_or_future__swap;
static NODE_GETTER get__true;
static NODE_GETTER get_value_or_future__true;
static NODE_GETTER get__types__grammar_node;
static NODE_GETTER get_value_or_future__types__grammar_node;
static NODE_GETTER get__update_each;
static NODE_GETTER get_value_or_future__update_each;
static NODE_GETTER get__while;
static NODE_GETTER get_value_or_future__while;
static struct {
  NODE *_expand_arguments;
  NODE *compiler__expand_statement;
  NODE *compiler__expand_expression;
  NODE *compiler__expand_operator_call;
} var;
static const char *var_names[] = {
  "expand_arguments"
};
static int poly_idx__compiler__expand_statement;
static void type__compiler__expand_statement(void);
static NODE *get__compiler__expand_statement(void) {
  return var.compiler__expand_statement;
}
static int poly_idx__compiler__expand_expression;
static void type__compiler__expand_expression(void);
static NODE *get__compiler__expand_expression(void) {
  return var.compiler__expand_expression;
}
static NODE *func__expand_arguments_1;
static void entry__expand_arguments_1(void);
static FRAME_INFO frame__expand_arguments_1 = {2, {"arguments", "new_arguments"}};
static NODE *func__expand_arguments_2;
static void entry__expand_arguments_2(void);
static FRAME_INFO frame__expand_arguments_2 = {2, {"argument", "new_arguments"}};
static void cont__expand_arguments_3(void);
static NODE *func__expand_arguments_4;
static void entry__expand_arguments_4(void);
static FRAME_INFO frame__expand_arguments_4 = {2, {"new_arguments", "argument"}};
static void cont__expand_arguments_5(void);
static void cont__expand_arguments_6(void);
static void cont__expand_arguments_7(void);
static void cont__expand_arguments_8(void);
static void cont__expand_arguments_9(void);
static NODE *func__expand_arguments_10;
static void entry__expand_arguments_10(void);
static FRAME_INFO frame__expand_arguments_10 = {2, {"new_arguments", "argument"}};
static void cont__expand_arguments_11(void);
static void cont__expand_arguments_12(void);
static void cont__expand_arguments_13(void);
static NODE *func__types__grammar_node__expand_statement_1;
static void entry__types__grammar_node__expand_statement_1(void);
static FRAME_INFO frame__types__grammar_node__expand_statement_1 = {1, {"self"}};
static NODE *string__582ccfaf004aa58;
static void cont__types__grammar_node__expand_statement_3(void);
static NODE *func__types__grammar_node__expand_expression_1;
static void entry__types__grammar_node__expand_expression_1(void);
static FRAME_INFO frame__types__grammar_node__expand_expression_1 = {1, {"self"}};
static NODE *string__4bcf31e55e19ce58;
static void cont__types__grammar_node__expand_expression_3(void);
static NODE *func__compiler__body__expand_expression_1;
static void entry__compiler__body__expand_expression_1(void);
static FRAME_INFO frame__compiler__body__expand_expression_1 = {1, {"self"}};
static NODE *string__c4e5f299bf2dab78;
static void cont__compiler__body__expand_expression_3(void);
static void cont__compiler__body__expand_expression_4(void);
static NODE *func__compiler__body__expand_expression_5;
static void entry__compiler__body__expand_expression_5(void);
static FRAME_INFO frame__compiler__body__expand_expression_5 = {1, {"parameter"}};
static void cont__compiler__body__expand_expression_6(void);
static void cont__compiler__body__expand_expression_7(void);
static NODE *func__compiler__body__expand_expression_8;
static void entry__compiler__body__expand_expression_8(void);
static FRAME_INFO frame__compiler__body__expand_expression_8 = {1, {"parameter"}};
static void cont__compiler__body__expand_expression_9(void);
static void cont__compiler__body__expand_expression_10(void);
static void cont__compiler__body__expand_expression_11(void);
static void cont__compiler__body__expand_expression_12(void);
static void cont__compiler__body__expand_expression_13(void);
static NODE *func__compiler__body__expand_expression_14;
static void entry__compiler__body__expand_expression_14(void);
static FRAME_INFO frame__compiler__body__expand_expression_14 = {1, {"stmt"}};
static void cont__compiler__body__expand_expression_15(void);
static void cont__compiler__body__expand_expression_16(void);
static NODE *func__compiler__call__expand_statement_1;
static void entry__compiler__call__expand_statement_1(void);
static FRAME_INFO frame__compiler__call__expand_statement_1 = {1, {"self"}};
static void cont__compiler__call__expand_statement_2(void);
static void cont__compiler__call__expand_statement_3(void);
static void cont__compiler__call__expand_statement_4(void);
static NODE *func__compiler__call__expand_statement_5;
static void entry__compiler__call__expand_statement_5(void);
static FRAME_INFO frame__compiler__call__expand_statement_5 = {1, {"self"}};
static void cont__compiler__call__expand_statement_6(void);
static void cont__compiler__call__expand_statement_7(void);
static NODE *func__compiler__call__expand_statement_8;
static void entry__compiler__call__expand_statement_8(void);
static FRAME_INFO frame__compiler__call__expand_statement_8 = {1, {"self"}};
static void cont__compiler__call__expand_statement_9(void);
static void cont__compiler__call__expand_statement_10(void);
static void cont__compiler__call__expand_statement_11(void);
static void cont__compiler__call__expand_statement_12(void);
static void cont__compiler__call__expand_statement_13(void);
static void cont__compiler__call__expand_statement_14(void);
static void cont__compiler__call__expand_statement_15(void);
static void cont__compiler__call__expand_statement_16(void);
static NODE *func__compiler__expand_operator_call_1;
static void entry__compiler__expand_operator_call_1(void);
static FRAME_INFO frame__compiler__expand_operator_call_1 = {3, {"self", "make_right_argument_lazy", "functor"}};
static NODE *func__compiler__expand_operator_call_2;
static void entry__compiler__expand_operator_call_2(void);
static FRAME_INFO frame__compiler__expand_operator_call_2 = {2, {"self", "right"}};
static void cont__compiler__expand_operator_call_3(void);
static void cont__compiler__expand_operator_call_4(void);
static void cont__compiler__expand_operator_call_5(void);
static void cont__compiler__expand_operator_call_6(void);
static void cont__compiler__expand_operator_call_7(void);
static void cont__compiler__expand_operator_call_8(void);
static void cont__compiler__expand_operator_call_9(void);
static void cont__compiler__expand_operator_call_10(void);
static void cont__compiler__expand_operator_call_11(void);
static void cont__compiler__expand_operator_call_12(void);
static void cont__compiler__expand_operator_call_13(void);
static void cont__compiler__expand_operator_call_14(void);
static void cont__compiler__expand_operator_call_15(void);
static void cont__compiler__expand_operator_call_16(void);
static NODE *func__compiler__expand_operator_call_17;
static void entry__compiler__expand_operator_call_17(void);
static FRAME_INFO frame__compiler__expand_operator_call_17 = {4, {"functor", "self", "make_right_argument_lazy", "do_insert_not"}};
static void cont__compiler__expand_operator_call_18(void);
static NODE *func__compiler__expand_operator_call_19;
static void entry__compiler__expand_operator_call_19(void);
static FRAME_INFO frame__compiler__expand_operator_call_19 = {1, {"functor"}};
static NODE *string__585ae843eae15024;
static void cont__compiler__expand_operator_call_21(void);
static NODE *func__compiler__expand_operator_call_22;
static void entry__compiler__expand_operator_call_22(void);
static FRAME_INFO frame__compiler__expand_operator_call_22 = {1, {"functor"}};
static NODE *string__1c0aeccb5d487d4b;
static void cont__compiler__expand_operator_call_24(void);
static NODE *func__compiler__expand_operator_call_25;
static void entry__compiler__expand_operator_call_25(void);
static FRAME_INFO frame__compiler__expand_operator_call_25 = {1, {"functor"}};
static NODE *string__220aea4b5dc87d4a;
static void cont__compiler__expand_operator_call_27(void);
static NODE *func__compiler__expand_operator_call_28;
static void entry__compiler__expand_operator_call_28(void);
static FRAME_INFO frame__compiler__expand_operator_call_28 = {2, {"self", "functor"}};
static void cont__compiler__expand_operator_call_29(void);
static void cont__compiler__expand_operator_call_30(void);
static void cont__compiler__expand_operator_call_31(void);
static NODE *func__compiler__expand_operator_call_32;
static void entry__compiler__expand_operator_call_32(void);
static FRAME_INFO frame__compiler__expand_operator_call_32 = {1, {"functor"}};
static NODE *string__561f5607811a02b2;
static void cont__compiler__expand_operator_call_34(void);
static NODE *func__compiler__expand_operator_call_35;
static void entry__compiler__expand_operator_call_35(void);
static FRAME_INFO frame__compiler__expand_operator_call_35 = {1, {"functor"}};
static NODE *string__585ae883ea60c024;
static void cont__compiler__expand_operator_call_37(void);
static NODE *func__compiler__expand_operator_call_38;
static void entry__compiler__expand_operator_call_38(void);
static FRAME_INFO frame__compiler__expand_operator_call_38 = {1, {"functor"}};
static NODE *string__2d7c8951ae1884d5;
static void cont__compiler__expand_operator_call_40(void);
static NODE *func__compiler__expand_operator_call_41;
static void entry__compiler__expand_operator_call_41(void);
static FRAME_INFO frame__compiler__expand_operator_call_41 = {1, {"functor"}};
static NODE *string__528d708426488b90;
static void cont__compiler__expand_operator_call_43(void);
static NODE *func__compiler__expand_operator_call_44;
static void entry__compiler__expand_operator_call_44(void);
static FRAME_INFO frame__compiler__expand_operator_call_44 = {1, {"functor"}};
static NODE *string__cc0c0d9615cb809e;
static void cont__compiler__expand_operator_call_46(void);
static NODE *func__compiler__expand_operator_call_47;
static void entry__compiler__expand_operator_call_47(void);
static FRAME_INFO frame__compiler__expand_operator_call_47 = {1, {"functor"}};
static NODE *string__cc0c0bd615c38088;
static void cont__compiler__expand_operator_call_49(void);
static NODE *func__compiler__expand_operator_call_50;
static void entry__compiler__expand_operator_call_50(void);
static FRAME_INFO frame__compiler__expand_operator_call_50 = {1, {"functor"}};
static NODE *string__701f598181c2c2a5;
static void cont__compiler__expand_operator_call_52(void);
static NODE *func__compiler__expand_operator_call_53;
static void entry__compiler__expand_operator_call_53(void);
static FRAME_INFO frame__compiler__expand_operator_call_53 = {3, {"functor", "self", "do_insert_not"}};
static NODE *string__1a0ae80b5df87d4a;
static void cont__compiler__expand_operator_call_55(void);
static void cont__compiler__expand_operator_call_56(void);
static void cont__compiler__expand_operator_call_57(void);
static void cont__compiler__expand_operator_call_58(void);
static void cont__compiler__expand_operator_call_59(void);
static void cont__compiler__expand_operator_call_60(void);
static void cont__compiler__expand_operator_call_61(void);
static void cont__compiler__expand_operator_call_62(void);
static void cont__compiler__expand_operator_call_63(void);
static void cont__compiler__expand_operator_call_64(void);
static NODE *func__compiler__expand_operator_call_65;
static void entry__compiler__expand_operator_call_65(void);
static FRAME_INFO frame__compiler__expand_operator_call_65 = {1, {"functor"}};
static void cont__compiler__expand_operator_call_66(void);
static NODE *func__compiler__expand_operator_call_67;
static void entry__compiler__expand_operator_call_67(void);
static FRAME_INFO frame__compiler__expand_operator_call_67 = {2, {"functor", "do_insert_not"}};
static void cont__compiler__expand_operator_call_68(void);
static NODE *func__compiler__expand_operator_call_69;
static void entry__compiler__expand_operator_call_69(void);
static FRAME_INFO frame__compiler__expand_operator_call_69 = {2, {"functor", "self"}};
static void cont__compiler__expand_operator_call_70(void);
static void cont__compiler__expand_operator_call_71(void);
static void cont__compiler__expand_operator_call_72(void);
static void cont__compiler__expand_operator_call_73(void);
static void cont__compiler__expand_operator_call_74(void);
static void cont__compiler__expand_operator_call_75(void);
static void cont__compiler__expand_operator_call_76(void);
static void cont__compiler__expand_operator_call_77(void);
static void cont__compiler__expand_operator_call_78(void);
static void cont__compiler__expand_operator_call_79(void);
static NODE *func__compiler__expand_operator_call_80;
static void entry__compiler__expand_operator_call_80(void);
static FRAME_INFO frame__compiler__expand_operator_call_80 = {1, {"functor"}};
static NODE *string__685aee43eac0403b;
static void cont__compiler__expand_operator_call_82(void);
static NODE *func__compiler__expand_operator_call_83;
static void entry__compiler__expand_operator_call_83(void);
static FRAME_INFO frame__compiler__expand_operator_call_83 = {2, {"functor", "do_insert_not"}};
static void cont__compiler__expand_operator_call_84(void);
static NODE *func__compiler__expand_operator_call_85;
static void entry__compiler__expand_operator_call_85(void);
static FRAME_INFO frame__compiler__expand_operator_call_85 = {2, {"functor", "make_right_argument_lazy"}};
static NODE *string__fa720015d596ba8;
static void cont__compiler__expand_operator_call_87(void);
static NODE *func__compiler__expand_operator_call_88;
static void entry__compiler__expand_operator_call_88(void);
static FRAME_INFO frame__compiler__expand_operator_call_88 = {2, {"functor", "make_right_argument_lazy"}};
static NODE *string__2d7981f4e4702bb7;
static void cont__compiler__expand_operator_call_90(void);
static NODE *func__compiler__expand_operator_call_91;
static void entry__compiler__expand_operator_call_91(void);
static FRAME_INFO frame__compiler__expand_operator_call_91 = {1, {"functor"}};
static NODE *string__2c93ac4233089e0;
static void cont__compiler__expand_operator_call_93(void);
static NODE *func__compiler__expand_operator_call_94;
static void entry__compiler__expand_operator_call_94(void);
static FRAME_INFO frame__compiler__expand_operator_call_94 = {1, {"functor"}};
static NODE *string__64d512703527e2ab;
static void cont__compiler__expand_operator_call_96(void);
static NODE *string__578a5af303e9ccb;
static NODE *string__578a5af303e9cce;
static NODE *string__578a5af303e9cca;
static NODE *string__578a5af303e9ccc;
static NODE *string__2d7981f4e6e82bf9;
static NODE *string__2d7981f4e6f82bfb;
static NODE *string__578a5af303e9cc7;
static NODE *string__578a5af303e9cbf;
static NODE *string__578a5af303e9c9d;
static NODE *string__2d7981f4e6e82bf8;
static NODE *string__578a5af303e9cdd;
static NODE *string__2d7981f4e6f82bf8;
static NODE *string__578a5af303e9cdf;
static NODE *string__2d7981f4e6e02bf8;
static NODE *string__2d7981f4e6002bf8;
static NODE *string__2d7981f4e6382be3;
static NODE *string__2d7981f4e4e82bb9;
static NODE *string__2d7981f4e6782beb;
static NODE *string__578a5af303e9cdc;
static void cont__compiler__expand_operator_call_116(void);
static NODE *func__compiler__expand_operator_call_117;
static void entry__compiler__expand_operator_call_117(void);
static FRAME_INFO frame__compiler__expand_operator_call_117 = {1, {"self"}};
static NODE *string__fa723c15d516bb8;
static void cont__compiler__expand_operator_call_119(void);
static void cont__compiler__expand_operator_call_120(void);
static void cont__compiler__expand_operator_call_121(void);
static void cont__compiler__expand_operator_call_122(void);
static void cont__compiler__expand_operator_call_123(void);
static void cont__compiler__expand_operator_call_124(void);
static NODE *get__compiler__expand_operator_call(void) {
  return var.compiler__expand_operator_call;
}
static NODE *func__compiler__function_call__expand_expression_1;
static void entry__compiler__function_call__expand_expression_1(void);
static FRAME_INFO frame__compiler__function_call__expand_expression_1 = {1, {"self"}};
static NODE *string__2ae70e1058c2c0b7;
static void cont__compiler__function_call__expand_expression_3(void);
static void cont__compiler__function_call__expand_expression_4(void);
static void cont__compiler__function_call__expand_expression_5(void);
static NODE *func__compiler__function_call__expand_expression_6;
static void entry__compiler__function_call__expand_expression_6(void);
static FRAME_INFO frame__compiler__function_call__expand_expression_6 = {2, {"self", "functor"}};
static void cont__compiler__function_call__expand_expression_7(void);
static void cont__compiler__function_call__expand_expression_8(void);
static void cont__compiler__function_call__expand_expression_9(void);
static void cont__compiler__function_call__expand_expression_10(void);
static NODE *func__compiler__function_call__expand_expression_11;
static void entry__compiler__function_call__expand_expression_11(void);
static FRAME_INFO frame__compiler__function_call__expand_expression_11 = {1, {"functor"}};
static void cont__compiler__function_call__expand_expression_12(void);
static NODE *string__578a5af303e9ccd;
static void cont__compiler__function_call__expand_expression_14(void);
static void cont__compiler__function_call__expand_expression_15(void);
static NODE *func__compiler__function_call__expand_expression_16;
static void entry__compiler__function_call__expand_expression_16(void);
static FRAME_INFO frame__compiler__function_call__expand_expression_16 = {3, {"self", "arguments", "right"}};
static void cont__compiler__function_call__expand_expression_17(void);
static void cont__compiler__function_call__expand_expression_18(void);
static void cont__compiler__function_call__expand_expression_19(void);
static void cont__compiler__function_call__expand_expression_20(void);
static void cont__compiler__function_call__expand_expression_21(void);
static NODE *func__compiler__function_call__expand_expression_22;
static void entry__compiler__function_call__expand_expression_22(void);
static FRAME_INFO frame__compiler__function_call__expand_expression_22 = {2, {"right", "arguments"}};
static void cont__compiler__function_call__expand_expression_23(void);
static NODE *func__compiler__function_call__expand_expression_24;
static void entry__compiler__function_call__expand_expression_24(void);
static FRAME_INFO frame__compiler__function_call__expand_expression_24 = {1, {"right"}};
static void cont__compiler__function_call__expand_expression_25(void);
static void cont__compiler__function_call__expand_expression_26(void);
static void cont__compiler__function_call__expand_expression_27(void);
static void cont__compiler__function_call__expand_expression_28(void);
static NODE *func__compiler__function_call__expand_expression_29;
static void entry__compiler__function_call__expand_expression_29(void);
static FRAME_INFO frame__compiler__function_call__expand_expression_29 = {3, {"right", "arguments", "right_arguments"}};
static void cont__compiler__function_call__expand_expression_30(void);
static void cont__compiler__function_call__expand_expression_31(void);
static void cont__compiler__function_call__expand_expression_32(void);
static void cont__compiler__function_call__expand_expression_33(void);
static void cont__compiler__function_call__expand_expression_34(void);
static void cont__compiler__function_call__expand_expression_35(void);
static NODE *string__6480ae5e84ccc225;
static void cont__compiler__function_call__expand_expression_37(void);
static void cont__compiler__function_call__expand_expression_38(void);
static NODE *func__compiler__function_call__expand_expression_39;
static void entry__compiler__function_call__expand_expression_39(void);
static FRAME_INFO frame__compiler__function_call__expand_expression_39 = {1, {"self"}};
static void cont__compiler__function_call__expand_expression_40(void);
static void cont__compiler__function_call__expand_expression_41(void);
static void cont__compiler__function_call__expand_expression_42(void);
static void cont__compiler__function_call__expand_expression_43(void);
static NODE *func__compiler__attribute_value_pair__expand_expression_1;
static void entry__compiler__attribute_value_pair__expand_expression_1(void);
static FRAME_INFO frame__compiler__attribute_value_pair__expand_expression_1 = {1, {"self"}};
static NODE *string__30246dda36d83a54;
static void cont__compiler__attribute_value_pair__expand_expression_3(void);
static void cont__compiler__attribute_value_pair__expand_expression_4(void);
static void cont__compiler__attribute_value_pair__expand_expression_5(void);
static NODE *func__compiler__attribute_function_pair__expand_expression_1;
static void entry__compiler__attribute_function_pair__expand_expression_1(void);
static FRAME_INFO frame__compiler__attribute_function_pair__expand_expression_1 = {1, {"self"}};
static NODE *string__2c1ce19c26092926;
static void cont__compiler__attribute_function_pair__expand_expression_3(void);
static void cont__compiler__attribute_function_pair__expand_expression_4(void);
static void cont__compiler__attribute_function_pair__expand_expression_5(void);
void run__expander(void);

static CONTINUATION_INFO continuation_info[] = {
  {type__compiler__expand_statement, NULL, 29, 29, 2, 27},
  {type__compiler__expand_expression, NULL, 30, 30, 2, 28},
  {run__expander, NULL, },
  {entry__expand_arguments_4, NULL, 39, 39, 41, 63},
  {cont__expand_arguments_5, &frame__expand_arguments_4, 37, 39, 9, 64},
  {cont__expand_arguments_6, &frame__expand_arguments_4, 40, 40, 47, 69},
  {cont__expand_arguments_7, &frame__expand_arguments_4, 40, 40, 29, 70},
  {cont__expand_arguments_8, &frame__expand_arguments_4, 40, 40, 9, 70},
  {cont__expand_arguments_9, &frame__expand_arguments_4, 40, 40, 70, 70},
  {entry__expand_arguments_10, NULL, 42, 42, 29, 55},
  {cont__expand_arguments_11, &frame__expand_arguments_10, 42, 42, 9, 55},
  {cont__expand_arguments_12, &frame__expand_arguments_10, 42, 42, 55, 55},
  {entry__expand_arguments_2, NULL, 36, 36, 7, 41},
  {cont__expand_arguments_3, &frame__expand_arguments_2, 35, 42, 5, 56},
  {entry__expand_arguments_1, NULL, 34, 42, 3, 57},
  {cont__expand_arguments_13, &frame__expand_arguments_1, 43, 43, 3, 18},
  {entry__types__grammar_node__expand_statement_1, NULL, 49, 49, 3, 45},
  {cont__types__grammar_node__expand_statement_3, &frame__types__grammar_node__expand_statement_1, },
  {entry__types__grammar_node__expand_expression_1, NULL, 52, 52, 3, 46},
  {cont__types__grammar_node__expand_expression_3, &frame__types__grammar_node__expand_expression_1, },
  {entry__compiler__body__expand_expression_8, NULL, 61, 61, 26, 51},
  {cont__compiler__body__expand_expression_9, &frame__compiler__body__expand_expression_8, 61, 61, 7, 51},
  {cont__compiler__body__expand_expression_10, &frame__compiler__body__expand_expression_8, 61, 61, 51, 51},
  {entry__compiler__body__expand_expression_5, NULL, 60, 60, 8, 34},
  {cont__compiler__body__expand_expression_6, &frame__compiler__body__expand_expression_5, 60, 60, 8, 45},
  {cont__compiler__body__expand_expression_7, &frame__compiler__body__expand_expression_5, 60, 61, 5, 51},
  {cont__compiler__body__expand_expression_11, &frame__compiler__body__expand_expression_5, },
  {entry__compiler__body__expand_expression_14, NULL, 62, 62, 44, 65},
  {cont__compiler__body__expand_expression_15, &frame__compiler__body__expand_expression_14, 62, 62, 65, 65},
  {entry__compiler__body__expand_expression_1, NULL, 58, 58, 3, 40},
  {cont__compiler__body__expand_expression_3, &frame__compiler__body__expand_expression_1, 59, 59, 16, 33},
  {cont__compiler__body__expand_expression_4, &frame__compiler__body__expand_expression_1, 59, 61, 3, 52},
  {cont__compiler__body__expand_expression_12, &frame__compiler__body__expand_expression_1, 62, 62, 16, 33},
  {cont__compiler__body__expand_expression_13, &frame__compiler__body__expand_expression_1, 62, 62, 3, 65},
  {cont__compiler__body__expand_expression_16, &frame__compiler__body__expand_expression_1, 62, 62, 65, 65},
  {entry__compiler__call__expand_statement_8, NULL, 70, 70, 61, 80},
  {cont__compiler__call__expand_statement_9, &frame__compiler__call__expand_statement_8, 70, 70, 42, 80},
  {cont__compiler__call__expand_statement_10, &frame__compiler__call__expand_statement_8, 70, 70, 80, 80},
  {entry__compiler__call__expand_statement_5, NULL, 70, 70, 8, 28},
  {cont__compiler__call__expand_statement_6, &frame__compiler__call__expand_statement_5, 70, 70, 8, 39},
  {cont__compiler__call__expand_statement_7, &frame__compiler__call__expand_statement_5, 70, 70, 5, 80},
  {cont__compiler__call__expand_statement_11, &frame__compiler__call__expand_statement_5, 71, 71, 24, 38},
  {cont__compiler__call__expand_statement_12, &frame__compiler__call__expand_statement_5, 71, 71, 5, 38},
  {cont__compiler__call__expand_statement_13, &frame__compiler__call__expand_statement_5, 71, 71, 38, 38},
  {entry__compiler__call__expand_statement_1, NULL, 68, 68, 3, 45},
  {cont__compiler__call__expand_statement_2, &frame__compiler__call__expand_statement_1, 69, 69, 6, 21},
  {cont__compiler__call__expand_statement_3, &frame__compiler__call__expand_statement_1, 69, 69, 6, 32},
  {cont__compiler__call__expand_statement_4, &frame__compiler__call__expand_statement_1, 69, 71, 3, 38},
  {cont__compiler__call__expand_statement_14, &frame__compiler__call__expand_statement_1, 72, 72, 21, 37},
  {cont__compiler__call__expand_statement_15, &frame__compiler__call__expand_statement_1, 72, 72, 3, 37},
  {cont__compiler__call__expand_statement_16, &frame__compiler__call__expand_statement_1, 72, 72, 37, 37},
  {entry__compiler__expand_operator_call_2, NULL, 79, 79, 12, 29},
  {cont__compiler__expand_operator_call_3, &frame__compiler__expand_operator_call_2, 79, 79, 5, 32},
  {cont__compiler__expand_operator_call_4, &frame__compiler__expand_operator_call_2, 85, 85, 29, 39},
  {cont__compiler__expand_operator_call_5, &frame__compiler__expand_operator_call_2, 86, 86, 28, 45},
  {cont__compiler__expand_operator_call_6, &frame__compiler__expand_operator_call_2, 87, 87, 35, 59},
  {cont__compiler__expand_operator_call_7, &frame__compiler__expand_operator_call_2, 88, 88, 32, 53},
  {cont__compiler__expand_operator_call_8, &frame__compiler__expand_operator_call_2, },
  {cont__compiler__expand_operator_call_9, &frame__compiler__expand_operator_call_2, 89, 89, 22, 39},
  {cont__compiler__expand_operator_call_10, &frame__compiler__expand_operator_call_2, 90, 90, 29, 53},
  {cont__compiler__expand_operator_call_11, &frame__compiler__expand_operator_call_2, 91, 91, 26, 47},
  {cont__compiler__expand_operator_call_12, &frame__compiler__expand_operator_call_2, 80, 80, 6, 22},
  {cont__compiler__expand_operator_call_13, &frame__compiler__expand_operator_call_2, 80, 80, 5, 25},
  {cont__compiler__expand_operator_call_14, &frame__compiler__expand_operator_call_2, 91, 91, 49, 49},
  {entry__compiler__expand_operator_call_19, NULL, 99, 99, 9, 40},
  {cont__compiler__expand_operator_call_21, &frame__compiler__expand_operator_call_19, 99, 99, 40, 40},
  {entry__compiler__expand_operator_call_22, NULL, 102, 102, 9, 39},
  {cont__compiler__expand_operator_call_24, &frame__compiler__expand_operator_call_22, 102, 102, 39, 39},
  {entry__compiler__expand_operator_call_25, NULL, 105, 105, 9, 39},
  {cont__compiler__expand_operator_call_27, &frame__compiler__expand_operator_call_25, 105, 105, 39, 39},
  {entry__compiler__expand_operator_call_32, NULL, 110, 110, 13, 45},
  {cont__compiler__expand_operator_call_34, &frame__compiler__expand_operator_call_32, 110, 110, 45, 45},
  {entry__compiler__expand_operator_call_35, NULL, 112, 112, 13, 44},
  {cont__compiler__expand_operator_call_37, &frame__compiler__expand_operator_call_35, 112, 112, 44, 44},
  {entry__compiler__expand_operator_call_28, NULL, 109, 109, 21, 38},
  {cont__compiler__expand_operator_call_29, &frame__compiler__expand_operator_call_28, 109, 109, 11, 39},
  {cont__compiler__expand_operator_call_30, &frame__compiler__expand_operator_call_28, 109, 109, 11, 44},
  {cont__compiler__expand_operator_call_31, &frame__compiler__expand_operator_call_28, 108, 112, 9, 45},
  {entry__compiler__expand_operator_call_38, NULL, 115, 115, 9, 45},
  {cont__compiler__expand_operator_call_40, &frame__compiler__expand_operator_call_38, 115, 115, 45, 45},
  {entry__compiler__expand_operator_call_41, NULL, 118, 118, 9, 46},
  {cont__compiler__expand_operator_call_43, &frame__compiler__expand_operator_call_41, 118, 118, 46, 46},
  {entry__compiler__expand_operator_call_44, NULL, 121, 121, 9, 42},
  {cont__compiler__expand_operator_call_46, &frame__compiler__expand_operator_call_44, 121, 121, 42, 42},
  {entry__compiler__expand_operator_call_47, NULL, 124, 124, 9, 42},
  {cont__compiler__expand_operator_call_49, &frame__compiler__expand_operator_call_47, 124, 124, 42, 42},
  {entry__compiler__expand_operator_call_50, NULL, 127, 127, 9, 41},
  {cont__compiler__expand_operator_call_52, &frame__compiler__expand_operator_call_50, 127, 127, 41, 41},
  {entry__compiler__expand_operator_call_53, NULL, 130, 130, 9, 39},
  {cont__compiler__expand_operator_call_55, &frame__compiler__expand_operator_call_53, 131, 131, 15, 31},
  {cont__compiler__expand_operator_call_56, &frame__compiler__expand_operator_call_53, 131, 131, 15, 34},
  {cont__compiler__expand_operator_call_57, &frame__compiler__expand_operator_call_53, 131, 131, 37, 53},
  {cont__compiler__expand_operator_call_58, &frame__compiler__expand_operator_call_53, 131, 131, 37, 56},
  {cont__compiler__expand_operator_call_59, &frame__compiler__expand_operator_call_53, 131, 131, 9, 56},
  {cont__compiler__expand_operator_call_60, &frame__compiler__expand_operator_call_53, 131, 131, 15, 31},
  {cont__compiler__expand_operator_call_61, &frame__compiler__expand_operator_call_53, 131, 131, 14, 34},
  {cont__compiler__expand_operator_call_62, &frame__compiler__expand_operator_call_53, 131, 131, 37, 53},
  {cont__compiler__expand_operator_call_63, &frame__compiler__expand_operator_call_53, 131, 131, 36, 56},
  {cont__compiler__expand_operator_call_64, &frame__compiler__expand_operator_call_53, 132, 132, 27, 27},
  {entry__compiler__expand_operator_call_65, NULL, 135, 135, 9, 39},
  {cont__compiler__expand_operator_call_66, &frame__compiler__expand_operator_call_65, 135, 135, 39, 39},
  {entry__compiler__expand_operator_call_67, NULL, 138, 138, 9, 39},
  {cont__compiler__expand_operator_call_68, &frame__compiler__expand_operator_call_67, 139, 139, 27, 27},
  {entry__compiler__expand_operator_call_69, NULL, 142, 142, 9, 39},
  {cont__compiler__expand_operator_call_70, &frame__compiler__expand_operator_call_69, 143, 143, 15, 31},
  {cont__compiler__expand_operator_call_71, &frame__compiler__expand_operator_call_69, 143, 143, 15, 34},
  {cont__compiler__expand_operator_call_72, &frame__compiler__expand_operator_call_69, 143, 143, 37, 53},
  {cont__compiler__expand_operator_call_73, &frame__compiler__expand_operator_call_69, 143, 143, 37, 56},
  {cont__compiler__expand_operator_call_74, &frame__compiler__expand_operator_call_69, 143, 143, 9, 56},
  {cont__compiler__expand_operator_call_75, &frame__compiler__expand_operator_call_69, 143, 143, 15, 31},
  {cont__compiler__expand_operator_call_76, &frame__compiler__expand_operator_call_69, 143, 143, 14, 34},
  {cont__compiler__expand_operator_call_77, &frame__compiler__expand_operator_call_69, 143, 143, 37, 53},
  {cont__compiler__expand_operator_call_78, &frame__compiler__expand_operator_call_69, 143, 143, 36, 56},
  {cont__compiler__expand_operator_call_79, &frame__compiler__expand_operator_call_69, 143, 143, 56, 56},
  {entry__compiler__expand_operator_call_80, NULL, 146, 146, 9, 40},
  {cont__compiler__expand_operator_call_82, &frame__compiler__expand_operator_call_80, 146, 146, 40, 40},
  {entry__compiler__expand_operator_call_83, NULL, 149, 149, 9, 40},
  {cont__compiler__expand_operator_call_84, &frame__compiler__expand_operator_call_83, 150, 150, 27, 27},
  {entry__compiler__expand_operator_call_85, NULL, 153, 153, 9, 38},
  {cont__compiler__expand_operator_call_87, &frame__compiler__expand_operator_call_85, 154, 154, 9, 32},
  {entry__compiler__expand_operator_call_88, NULL, 157, 157, 9, 37},
  {cont__compiler__expand_operator_call_90, &frame__compiler__expand_operator_call_88, 158, 158, 9, 32},
  {entry__compiler__expand_operator_call_91, NULL, 161, 161, 9, 46},
  {cont__compiler__expand_operator_call_93, &frame__compiler__expand_operator_call_91, 161, 161, 46, 46},
  {entry__compiler__expand_operator_call_94, NULL, 164, 164, 9, 49},
  {cont__compiler__expand_operator_call_96, &frame__compiler__expand_operator_call_94, 164, 164, 49, 49},
  {entry__compiler__expand_operator_call_117, NULL, 169, 169, 23, 43},
  {cont__compiler__expand_operator_call_119, &frame__compiler__expand_operator_call_117, 170, 170, 25, 34},
  {cont__compiler__expand_operator_call_120, &frame__compiler__expand_operator_call_117, 171, 171, 24, 40},
  {cont__compiler__expand_operator_call_121, &frame__compiler__expand_operator_call_117, 172, 172, 31, 54},
  {cont__compiler__expand_operator_call_122, &frame__compiler__expand_operator_call_117, 173, 173, 28, 48},
  {cont__compiler__expand_operator_call_123, &frame__compiler__expand_operator_call_117, 173, 173, 50, 50},
  {entry__compiler__expand_operator_call_17, NULL, 96, 96, 10, 25},
  {cont__compiler__expand_operator_call_18, &frame__compiler__expand_operator_call_17, 96, 164, 5, 50},
  {cont__compiler__expand_operator_call_116, &frame__compiler__expand_operator_call_17, 166, 173, 5, 50},
  {entry__compiler__expand_operator_call_1, NULL, 93, 93, 3, 28},
  {cont__compiler__expand_operator_call_15, &frame__compiler__expand_operator_call_1, 94, 94, 6, 34},
  {cont__compiler__expand_operator_call_16, &frame__compiler__expand_operator_call_1, 94, 173, 3, 51},
  {cont__compiler__expand_operator_call_124, &frame__compiler__expand_operator_call_1, },
  {entry__compiler__function_call__expand_expression_11, NULL, 184, 184, 40, 55},
  {cont__compiler__function_call__expand_expression_12, &frame__compiler__function_call__expand_expression_11, 184, 184, 40, 62},
  {cont__compiler__function_call__expand_expression_14, &frame__compiler__function_call__expand_expression_11, 184, 184, 40, 62},
  {entry__compiler__function_call__expand_expression_24, NULL, 187, 187, 54, 70},
  {cont__compiler__function_call__expand_expression_25, &frame__compiler__function_call__expand_expression_24, 187, 187, 46, 71},
  {cont__compiler__function_call__expand_expression_26, &frame__compiler__function_call__expand_expression_24, 187, 187, 46, 78},
  {cont__compiler__function_call__expand_expression_27, &frame__compiler__function_call__expand_expression_24, 187, 187, 46, 78},
  {entry__compiler__function_call__expand_expression_29, NULL, 188, 188, 11, 46},
  {cont__compiler__function_call__expand_expression_30, &frame__compiler__function_call__expand_expression_29, 189, 189, 27, 44},
  {cont__compiler__function_call__expand_expression_31, &frame__compiler__function_call__expand_expression_29, 189, 189, 11, 44},
  {cont__compiler__function_call__expand_expression_32, &frame__compiler__function_call__expand_expression_29, 190, 190, 11, 35},
  {cont__compiler__function_call__expand_expression_33, &frame__compiler__function_call__expand_expression_29, 190, 190, 35, 35},
  {entry__compiler__function_call__expand_expression_22, NULL, 187, 187, 18, 41},
  {cont__compiler__function_call__expand_expression_23, &frame__compiler__function_call__expand_expression_22, 187, 187, 18, 78},
  {cont__compiler__function_call__expand_expression_28, &frame__compiler__function_call__expand_expression_22, 187, 190, 15, 35},
  {entry__compiler__function_call__expand_expression_16, NULL, 185, 185, 26, 43},
  {cont__compiler__function_call__expand_expression_17, &frame__compiler__function_call__expand_expression_16, 185, 185, 26, 46},
  {cont__compiler__function_call__expand_expression_18, &frame__compiler__function_call__expand_expression_16, 185, 185, 9, 47},
  {cont__compiler__function_call__expand_expression_19, &frame__compiler__function_call__expand_expression_16, 186, 186, 17, 34},
  {cont__compiler__function_call__expand_expression_20, &frame__compiler__function_call__expand_expression_16, 186, 186, 9, 37},
  {cont__compiler__function_call__expand_expression_21, &frame__compiler__function_call__expand_expression_16, 187, 190, 9, 35},
  {cont__compiler__function_call__expand_expression_34, &frame__compiler__function_call__expand_expression_16, 191, 191, 9, 29},
  {cont__compiler__function_call__expand_expression_35, &frame__compiler__function_call__expand_expression_16, 192, 192, 9, 51},
  {cont__compiler__function_call__expand_expression_37, &frame__compiler__function_call__expand_expression_16, 193, 193, 9, 54},
  {cont__compiler__function_call__expand_expression_38, &frame__compiler__function_call__expand_expression_16, 193, 193, 54, 54},
  {entry__compiler__function_call__expand_expression_39, NULL, 195, 195, 27, 43},
  {cont__compiler__function_call__expand_expression_40, &frame__compiler__function_call__expand_expression_39, 195, 195, 9, 43},
  {cont__compiler__function_call__expand_expression_41, &frame__compiler__function_call__expand_expression_39, 196, 196, 9, 34},
  {cont__compiler__function_call__expand_expression_42, &frame__compiler__function_call__expand_expression_39, 196, 196, 34, 34},
  {entry__compiler__function_call__expand_expression_6, NULL, 181, 181, 24, 38},
  {cont__compiler__function_call__expand_expression_7, &frame__compiler__function_call__expand_expression_6, 181, 181, 5, 38},
  {cont__compiler__function_call__expand_expression_8, &frame__compiler__function_call__expand_expression_6, 182, 182, 5, 29},
  {cont__compiler__function_call__expand_expression_9, &frame__compiler__function_call__expand_expression_6, 184, 184, 7, 35},
  {cont__compiler__function_call__expand_expression_10, &frame__compiler__function_call__expand_expression_6, 184, 184, 7, 62},
  {cont__compiler__function_call__expand_expression_15, &frame__compiler__function_call__expand_expression_6, 183, 196, 5, 35},
  {entry__compiler__function_call__expand_expression_1, NULL, 176, 176, 3, 49},
  {cont__compiler__function_call__expand_expression_3, &frame__compiler__function_call__expand_expression_1, 180, 180, 6, 21},
  {cont__compiler__function_call__expand_expression_4, &frame__compiler__function_call__expand_expression_1, 180, 180, 6, 32},
  {cont__compiler__function_call__expand_expression_5, &frame__compiler__function_call__expand_expression_1, 180, 196, 3, 36},
  {cont__compiler__function_call__expand_expression_43, &frame__compiler__function_call__expand_expression_1, },
  {entry__compiler__attribute_value_pair__expand_expression_1, NULL, 202, 202, 3, 56},
  {cont__compiler__attribute_value_pair__expand_expression_3, &frame__compiler__attribute_value_pair__expand_expression_1, 203, 203, 21, 37},
  {cont__compiler__attribute_value_pair__expand_expression_4, &frame__compiler__attribute_value_pair__expand_expression_1, 203, 203, 3, 37},
  {cont__compiler__attribute_value_pair__expand_expression_5, &frame__compiler__attribute_value_pair__expand_expression_1, 203, 203, 37, 37},
  {entry__compiler__attribute_function_pair__expand_expression_1, NULL, 209, 209, 3, 59},
  {cont__compiler__attribute_function_pair__expand_expression_3, &frame__compiler__attribute_function_pair__expand_expression_1, 210, 210, 21, 37},
  {cont__compiler__attribute_function_pair__expand_expression_4, &frame__compiler__attribute_function_pair__expand_expression_1, 210, 210, 3, 37},
  {cont__compiler__attribute_function_pair__expand_expression_5, &frame__compiler__attribute_function_pair__expand_expression_1, 210, 210, 37, 37}
};

union NODE {
  struct {
    FUNC type;
    ATTRIBUTES *attributes;
  };
  CONTINUATION continuation;
  CLOSURE closure;
};
static void type__compiler__expand_statement(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__compiler__expand_statement);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__compiler__expand_statement, attr);
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
static void type__compiler__expand_expression(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__compiler__expand_expression);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__compiler__expand_expression, attr);
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
  "expander",
  continuation_info,
  sizeof(continuation_info)/sizeof(CONTINUATION_INFO),
  (NODE **)&var,
  var_names,
  sizeof(var_names)/sizeof(const char *),
  used_namespaces,
  {DEBUG_FILENAME("expander.sim")}
};

/******
C O D E
******/

static int already_run = false;

EXPORT void run__expander(void) {
  if (already_run) {
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  already_run = true;
  allocate_initialized_frame_gc(0, 0);
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__expand_arguments_1(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // arguments: 0
  // new_arguments: 1
  frame->slots[1] /* new_arguments */ = create_cell();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 33: $$new_arguments empty_list
  ((CELL *)frame->slots[1])->contents /* new_arguments */ = get__empty_list();
  // 34: ... : (argument)
  // 35:   if
  // 36:     argument.is_a_backquoted_expression:
  // 37:       push
  // 38:         &new_arguments
  // 39:         string_literal(.node::text_of node::text_of(argument))
  // 40:       push &new_arguments expand_expression(expression_of(argument))
  // 41:     :
  // 42:       push &new_arguments expand_expression(argument)
  frame->slots[2] /* temp__1 */ = create_closure(entry__expand_arguments_2, 1);
  // 34: for_each arguments: (argument)
  // 35:   if
  // 36:     argument.is_a_backquoted_expression:
  // 37:       push
  // 38:         &new_arguments
  // 39:         string_literal(.node::text_of node::text_of(argument))
  // 40:       push &new_arguments expand_expression(expression_of(argument))
  // 41:     :
  // 42:       push &new_arguments expand_expression(argument)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* arguments */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__expand_arguments_13;
}
static void entry__expand_arguments_4(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // new_arguments: 0
  // argument: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* new_arguments */
  frame->slots[1] = myself->closure.frame->slots[0]; /* argument */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 39: ... node::text_of(argument)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* argument */;
  result_count = 1;
  myself = get__node__text_of();
  func = myself->type;
  frame->cont = cont__expand_arguments_5;
}
static void cont__expand_arguments_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 39: string_literal(.node::text_of node::text_of(argument))
  {
    NODE *temp = clone_object_and_attributes(get__string_literal());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__node__text_of, frame->slots[3] /* temp__2 */);
    frame->slots[2] /* temp__1 */ = temp;

  }
  // 37: push
  // 38:   &new_arguments
  // 39:   string_literal(.node::text_of node::text_of(argument))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* new_arguments */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__expand_arguments_6;
}
static void cont__expand_arguments_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* new_arguments */ = arguments->slots[0];
  // 40: ... expression_of(argument)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* argument */;
  result_count = 1;
  myself = get__expression_of();
  func = myself->type;
  frame->cont = cont__expand_arguments_7;
}
static void cont__expand_arguments_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 40: ... expand_expression(expression_of(argument))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__expand_expression();
  func = myself->type;
  frame->cont = cont__expand_arguments_8;
}
static void cont__expand_arguments_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 40: push &new_arguments expand_expression(expression_of(argument))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* new_arguments */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__expand_arguments_9;
}
static void cont__expand_arguments_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* new_arguments */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__expand_arguments_10(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // new_arguments: 0
  // argument: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* new_arguments */
  frame->slots[1] = myself->closure.frame->slots[0]; /* argument */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 42: ... expand_expression(argument)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* argument */;
  result_count = 1;
  myself = get__expand_expression();
  func = myself->type;
  frame->cont = cont__expand_arguments_11;
}
static void cont__expand_arguments_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 42: push &new_arguments expand_expression(argument)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* new_arguments */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__expand_arguments_12;
}
static void cont__expand_arguments_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* new_arguments */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__expand_arguments_2(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // argument: 0
  // new_arguments: 1
  frame->slots[1] = myself->closure.frame->slots[1]; /* new_arguments */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 36: argument.is_a_backquoted_expression
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* argument */;
  result_count = 1;
  myself = get__is_a_backquoted_expression();
  func = myself->type;
  frame->cont = cont__expand_arguments_3;
}
static void cont__expand_arguments_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 36: ... :
  // 37:   push
  // 38:     &new_arguments
  // 39:     string_literal(.node::text_of node::text_of(argument))
  // 40:   push &new_arguments expand_expression(expression_of(argument))
  frame->slots[3] /* temp__2 */ = create_closure(entry__expand_arguments_4, 0);
  // 41: :
  // 42:   push &new_arguments expand_expression(argument)
  frame->slots[4] /* temp__3 */ = create_closure(entry__expand_arguments_10, 0);
  // 35: if
  // 36:   argument.is_a_backquoted_expression:
  // 37:     push
  // 38:       &new_arguments
  // 39:       string_literal(.node::text_of node::text_of(argument))
  // 40:     push &new_arguments expand_expression(expression_of(argument))
  // 41:   :
  // 42:     push &new_arguments expand_expression(argument)
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
static void cont__expand_arguments_13(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 43: -> new_arguments
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* new_arguments */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__grammar_node__expand_statement_1(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // self: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* self */ = create_cell_with_contents(arguments->slots[0]);
  // 49: show_compiler_debug_info "expand statement"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__582ccfaf004aa58;
  result_count =
    frame->caller_result_count >= 1 ?
    frame->caller_result_count-1 : -1;
  myself = get__show_compiler_debug_info();
  func = myself->type;
  frame->cont = cont__types__grammar_node__expand_statement_3;
}
static void cont__types__grammar_node__expand_statement_3(void) {
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
static void entry__types__grammar_node__expand_expression_1(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // self: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* self */ = create_cell_with_contents(arguments->slots[0]);
  // 52: show_compiler_debug_info "expand expression"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__4bcf31e55e19ce58;
  result_count =
    frame->caller_result_count >= 1 ?
    frame->caller_result_count-1 : -1;
  myself = get__show_compiler_debug_info();
  func = myself->type;
  frame->cont = cont__types__grammar_node__expand_expression_3;
}
static void cont__types__grammar_node__expand_expression_3(void) {
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
static void entry__compiler__body__expand_expression_1(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // self: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* self */ = create_cell_with_contents(arguments->slots[0]);
  // 58: show_compiler_debug_info "expand body"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__c4e5f299bf2dab78;
  result_count = 0;
  myself = get__show_compiler_debug_info();
  func = myself->type;
  frame->cont = cont__compiler__body__expand_expression_3;
}
static void cont__compiler__body__expand_expression_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 59: ... self.parameters_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__parameters_of();
  func = myself->type;
  frame->cont = cont__compiler__body__expand_expression_4;
}
static void cont__compiler__body__expand_expression_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 59: update_each &self.parameters_of: (&parameter)
  // 60:   if default_value_of(parameter).is_defined:
  // 61:     expand_expression &parameter.default_value_of
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = func__compiler__body__expand_expression_5;
  result_count = 1;
  myself = get__update_each();
  func = myself->type;
  frame->cont = cont__compiler__body__expand_expression_12;
}
static void entry__compiler__body__expand_expression_5(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // parameter: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* parameter */ = create_cell_with_contents(arguments->slots[0]);
  // 60: ... default_value_of(parameter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* parameter */;
  result_count = 1;
  myself = get__default_value_of();
  func = myself->type;
  frame->cont = cont__compiler__body__expand_expression_6;
}
static void cont__compiler__body__expand_expression_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 60: ... default_value_of(parameter).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__compiler__body__expand_expression_7;
}
static void cont__compiler__body__expand_expression_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 60: ... :
  // 61:   expand_expression &parameter.default_value_of
  frame->slots[3] /* temp__3 */ = create_closure(entry__compiler__body__expand_expression_8, 0);
  // 60: if default_value_of(parameter).is_defined:
  // 61:   expand_expression &parameter.default_value_of
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count =
    frame->caller_result_count >= 1 ?
    frame->caller_result_count-1 : -1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__body__expand_expression_11;
}
static void entry__compiler__body__expand_expression_8(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // parameter: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* parameter */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 61: ... parameter.default_value_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* parameter */;
  result_count = 1;
  myself = get__default_value_of();
  func = myself->type;
  frame->cont = cont__compiler__body__expand_expression_9;
}
static void cont__compiler__body__expand_expression_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 61: expand_expression &parameter.default_value_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__expand_expression();
  func = myself->type;
  frame->cont = cont__compiler__body__expand_expression_10;
}
static void cont__compiler__body__expand_expression_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 61: ... &parameter.default_value_of
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
static void cont__compiler__body__expand_expression_11(void) {
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
static void cont__compiler__body__expand_expression_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 59: ... &self.parameters_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__parameters_of, frame->slots[2] /* temp__2 */);
    ((CELL *)frame->slots[0])->contents /* self */ = temp;

  }
  // 62: ... self.statements_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__statements_of();
  func = myself->type;
  frame->cont = cont__compiler__body__expand_expression_13;
}
static void cont__compiler__body__expand_expression_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 62: update_each &self.statements_of: (&stmt) expand_statement &stmt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = func__compiler__body__expand_expression_14;
  result_count = 1;
  myself = get__update_each();
  func = myself->type;
  frame->cont = cont__compiler__body__expand_expression_16;
}
static void entry__compiler__body__expand_expression_14(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // stmt: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* stmt */ = create_cell_with_contents(arguments->slots[0]);
  // 62: ... expand_statement &stmt
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* stmt */;
  result_count = 1;
  myself = get__expand_statement();
  func = myself->type;
  frame->cont = cont__compiler__body__expand_expression_15;
}
static void cont__compiler__body__expand_expression_15(void) {
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
static void cont__compiler__body__expand_expression_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 62: ... &self.statements_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__statements_of, frame->slots[2] /* temp__2 */);
    ((CELL *)frame->slots[0])->contents /* self */ = temp;

  }
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__call__expand_statement_1(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // self: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* self */ = create_cell_with_contents(arguments->slots[0]);
  // 68: show_compiler_debug_info "expand statement"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__582ccfaf004aa58;
  result_count = 0;
  myself = get__show_compiler_debug_info();
  func = myself->type;
  frame->cont = cont__compiler__call__expand_statement_2;
}
static void cont__compiler__call__expand_statement_2(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 69: ... functor_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__functor_of();
  func = myself->type;
  frame->cont = cont__compiler__call__expand_statement_3;
}
static void cont__compiler__call__expand_statement_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 69: ... functor_of(self).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__compiler__call__expand_statement_4;
}
static void cont__compiler__call__expand_statement_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 69: ... :
  // 70:   if result_count_of(self).is_defined: expand_expression &self.result_count_of
  // 71:   expand_expression &self.functor_of
  frame->slots[3] /* temp__3 */ = create_closure(entry__compiler__call__expand_statement_5, 0);
  // 69: if functor_of(self).is_defined:
  // 70:   if result_count_of(self).is_defined: expand_expression &self.result_count_of
  // 71:   expand_expression &self.functor_of
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__call__expand_statement_14;
}
static void entry__compiler__call__expand_statement_5(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // self: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 70: ... result_count_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__result_count_of();
  func = myself->type;
  frame->cont = cont__compiler__call__expand_statement_6;
}
static void cont__compiler__call__expand_statement_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 70: ... result_count_of(self).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__compiler__call__expand_statement_7;
}
static void cont__compiler__call__expand_statement_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 70: ... : expand_expression &self.result_count_of
  frame->slots[3] /* temp__3 */ = create_closure(entry__compiler__call__expand_statement_8, 0);
  // 70: if result_count_of(self).is_defined: expand_expression &self.result_count_of
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__call__expand_statement_11;
}
static void entry__compiler__call__expand_statement_8(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // self: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 70: ... self.result_count_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__result_count_of();
  func = myself->type;
  frame->cont = cont__compiler__call__expand_statement_9;
}
static void cont__compiler__call__expand_statement_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 70: ... expand_expression &self.result_count_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__expand_expression();
  func = myself->type;
  frame->cont = cont__compiler__call__expand_statement_10;
}
static void cont__compiler__call__expand_statement_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 70: ... &self.result_count_of
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
static void cont__compiler__call__expand_statement_11(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 71: ... self.functor_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__functor_of();
  func = myself->type;
  frame->cont = cont__compiler__call__expand_statement_12;
}
static void cont__compiler__call__expand_statement_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 71: expand_expression &self.functor_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__expand_expression();
  func = myself->type;
  frame->cont = cont__compiler__call__expand_statement_13;
}
static void cont__compiler__call__expand_statement_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 71: ... &self.functor_of
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
static void cont__compiler__call__expand_statement_14(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 72: ... self.arguments_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__compiler__call__expand_statement_15;
}
static void cont__compiler__call__expand_statement_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 72: expand_arguments &self.arguments_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = var._expand_arguments;
  func = myself->type;
  frame->cont = cont__compiler__call__expand_statement_16;
}
static void cont__compiler__call__expand_statement_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 72: ... &self.arguments_of
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
static void entry__compiler__expand_operator_call_1(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // self: 0
  // make_right_argument_lazy: 1
  // functor: 2
  frame->slots[1] /* make_right_argument_lazy */ = create_future();
  frame->slots[2] /* functor */ = create_cell();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* self */ = create_cell_with_contents(arguments->slots[0]);
  // 78: ... :
  // 79:   $right arguments_of(self)(2)
  // 80:   !self.arguments_of(2)
  // 81:     body
  // 82:       .statements_of
  // 83:         list
  // 84:           return_statement
  // 85:             .arguments_of list(right)
  // 86:             .fragment_of fragment_of(right)
  // 87:             .source_position_of source_position_of(right)
  // ...
  frame->slots[3] /* temp__1 */ = create_closure(entry__compiler__expand_operator_call_2, 0);
  // 78: $make_right_argument_lazy:
  // 79:   $right arguments_of(self)(2)
  // 80:   !self.arguments_of(2)
  // 81:     body
  // 82:       .statements_of
  // 83:         list
  // 84:           return_statement
  // 85:             .arguments_of list(right)
  // 86:             .fragment_of fragment_of(right)
  // 87:             .source_position_of source_position_of(right)
  // ...
  initialize_future(frame->slots[1] /* make_right_argument_lazy */, frame->slots[3] /* temp__1 */);
  // 93: $$functor functor_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__functor_of();
  func = myself->type;
  frame->cont = cont__compiler__expand_operator_call_15;
}
static void entry__compiler__expand_operator_call_2(void) {
  allocate_initialized_frame_gc(1, 13);
  // slot allocations:
  // self: 0
  // right: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  frame->slots[1] /* right */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 79: ... arguments_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__compiler__expand_operator_call_3;
}
static void cont__compiler__expand_operator_call_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 79: $right arguments_of(self)(2)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = frame->slots[2] /* temp__1 */;
  func = myself->type;
  frame->cont = cont__compiler__expand_operator_call_4;
}
static void cont__compiler__expand_operator_call_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* right */, arguments->slots[0]);
  // 85: ... list(right)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* right */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__compiler__expand_operator_call_5;
}
static void cont__compiler__expand_operator_call_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 86: ... fragment_of(right)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* right */;
  result_count = 1;
  myself = get__fragment_of();
  func = myself->type;
  frame->cont = cont__compiler__expand_operator_call_6;
}
static void cont__compiler__expand_operator_call_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__4 */ = arguments->slots[0];
  // 87: ... source_position_of(right)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* right */;
  result_count = 1;
  myself = get__source_position_of();
  func = myself->type;
  frame->cont = cont__compiler__expand_operator_call_7;
}
static void cont__compiler__expand_operator_call_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__5 */ = arguments->slots[0];
  // 88: ... end_position_of(right)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* right */;
  result_count = 1;
  myself = get__end_position_of();
  func = myself->type;
  frame->cont = cont__compiler__expand_operator_call_8;
}
static void cont__compiler__expand_operator_call_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__6 */ = arguments->slots[0];
  {
    NODE *temp = clone_object_and_attributes(get__return_statement());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[4] /* temp__3 */);
    set_attribute_value(temp->attributes, poly_idx__fragment_of, frame->slots[5] /* temp__4 */);
    set_attribute_value(temp->attributes, poly_idx__source_position_of, frame->slots[6] /* temp__5 */);
    set_attribute_value(temp->attributes, poly_idx__end_position_of, frame->slots[7] /* temp__6 */);
    frame->slots[3] /* temp__2 */ = temp;

  }
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__compiler__expand_operator_call_9;
}
static void cont__compiler__expand_operator_call_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 89: ... fragment_of(right)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* right */;
  result_count = 1;
  myself = get__fragment_of();
  func = myself->type;
  frame->cont = cont__compiler__expand_operator_call_10;
}
static void cont__compiler__expand_operator_call_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__7 */ = arguments->slots[0];
  // 90: ... source_position_of(right)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* right */;
  result_count = 1;
  myself = get__source_position_of();
  func = myself->type;
  frame->cont = cont__compiler__expand_operator_call_11;
}
static void cont__compiler__expand_operator_call_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__8 */ = arguments->slots[0];
  // 91: ... end_position_of(right)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* right */;
  result_count = 1;
  myself = get__end_position_of();
  func = myself->type;
  frame->cont = cont__compiler__expand_operator_call_12;
}
static void cont__compiler__expand_operator_call_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__9 */ = arguments->slots[0];
  // 80: !self.arguments_of(2)
  // 81:   body
  // 82:     .statements_of
  // 83:       list
  // 84:         return_statement
  // 85:           .arguments_of list(right)
  // 86:           .fragment_of fragment_of(right)
  // 87:           .source_position_of source_position_of(right)
  // 88:           .end_position_of end_position_of(right)
  // 89:     .fragment_of fragment_of(right)
  // ...
  {
    NODE *temp = clone_object_and_attributes(get__body());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__statements_of, frame->slots[2] /* temp__1 */);
    set_attribute_value(temp->attributes, poly_idx__fragment_of, frame->slots[8] /* temp__7 */);
    set_attribute_value(temp->attributes, poly_idx__source_position_of, frame->slots[9] /* temp__8 */);
    set_attribute_value(temp->attributes, poly_idx__end_position_of, frame->slots[10] /* temp__9 */);
    frame->slots[11] /* temp__10 */ = temp;

  }
  // 80: ... self.arguments_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__compiler__expand_operator_call_13;
}
static void cont__compiler__expand_operator_call_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__11 */ = arguments->slots[0];
  // 80: !self.arguments_of(2)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__2;
  arguments->slots[1] = frame->slots[11] /* temp__10 */;
  result_count = 1;
  myself = frame->slots[12] /* temp__11 */;
  func = myself->type;
  frame->cont = cont__compiler__expand_operator_call_14;
}
static void cont__compiler__expand_operator_call_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__11 */ = arguments->slots[0];
  // 80: !self.arguments_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[12] /* temp__11 */);
    ((CELL *)frame->slots[0])->contents /* self */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__expand_operator_call_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* functor */ = arguments->slots[0];
  // 94: ... functor.is_an_operator_symbol
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* functor */;
  result_count = 1;
  myself = get__is_an_operator_symbol();
  func = myself->type;
  frame->cont = cont__compiler__expand_operator_call_16;
}
static void cont__compiler__expand_operator_call_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  //  94: ... :
  //  95:   $$do_insert_not false
  //  96:   case name_of(functor)
  //  97:     "*"
  //  98:     :
  //  99:       !functor std_identifier("times")
  // 100:     "/"
  // 101:     :
  // 102:       !functor std_identifier("over")
  // 103:     "+"
  // ...
  frame->slots[4] /* temp__2 */ = create_closure(entry__compiler__expand_operator_call_17, 0);
  //  94: if functor.is_an_operator_symbol:
  //  95:   $$do_insert_not false
  //  96:   case name_of(functor)
  //  97:     "*"
  //  98:     :
  //  99:       !functor std_identifier("times")
  // 100:     "/"
  // 101:     :
  // 102:       !functor std_identifier("over")
  // 103:     "+"
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
  frame->cont = cont__compiler__expand_operator_call_124;
}
static void entry__compiler__expand_operator_call_117(void) {
  allocate_initialized_frame_gc(1, 6);
  // slot allocations:
  // self: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 169: ... std_identifier("not")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__fa723c15d516bb8;
  result_count = 1;
  myself = get__std_identifier();
  func = myself->type;
  frame->cont = cont__compiler__expand_operator_call_119;
}
static void cont__compiler__expand_operator_call_119(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 170: ... list(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__compiler__expand_operator_call_120;
}
static void cont__compiler__expand_operator_call_120(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 171: ... fragment_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__fragment_of();
  func = myself->type;
  frame->cont = cont__compiler__expand_operator_call_121;
}
static void cont__compiler__expand_operator_call_121(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 172: ... source_position_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__source_position_of();
  func = myself->type;
  frame->cont = cont__compiler__expand_operator_call_122;
}
static void cont__compiler__expand_operator_call_122(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__4 */ = arguments->slots[0];
  // 173: ... end_position_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__end_position_of();
  func = myself->type;
  frame->cont = cont__compiler__expand_operator_call_123;
}
static void cont__compiler__expand_operator_call_123(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__5 */ = arguments->slots[0];
  // 167: !self
  // 168:   function_call
  // 169:     .functor_of std_identifier("not")
  // 170:     .arguments_of list(self)
  // 171:     .fragment_of fragment_of(self)
  // 172:     .source_position_of source_position_of(self)
  // 173:     .end_position_of end_position_of(self)
  {
    NODE *temp = clone_object_and_attributes(get__function_call());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__functor_of, frame->slots[1] /* temp__1 */);
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[2] /* temp__2 */);
    set_attribute_value(temp->attributes, poly_idx__fragment_of, frame->slots[3] /* temp__3 */);
    set_attribute_value(temp->attributes, poly_idx__source_position_of, frame->slots[4] /* temp__4 */);
    set_attribute_value(temp->attributes, poly_idx__end_position_of, frame->slots[5] /* temp__5 */);
    ((CELL *)frame->slots[0])->contents /* self */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__expand_operator_call_17(void) {
  allocate_initialized_frame_gc(3, 24);
  // slot allocations:
  // functor: 0
  // self: 1
  // make_right_argument_lazy: 2
  // do_insert_not: 3
  frame->slots[0] = myself->closure.frame->slots[2]; /* functor */
  frame->slots[1] = myself->closure.frame->slots[0]; /* self */
  frame->slots[2] = myself->closure.frame->slots[1]; /* make_right_argument_lazy */
  frame->slots[3] /* do_insert_not */ = create_cell();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 95: $$do_insert_not false
  ((CELL *)frame->slots[3])->contents /* do_insert_not */ = get__false();
  // 96: ... name_of(functor)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* functor */;
  result_count = 1;
  myself = get__name_of();
  func = myself->type;
  frame->cont = cont__compiler__expand_operator_call_18;
}
static void cont__compiler__expand_operator_call_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 98: :
  // 99:   !functor std_identifier("times")
  frame->slots[5] /* temp__2 */ = create_closure(entry__compiler__expand_operator_call_19, 0);
  // 101: :
  // 102:   !functor std_identifier("over")
  frame->slots[6] /* temp__3 */ = create_closure(entry__compiler__expand_operator_call_22, 0);
  // 104: :
  // 105:   !functor std_identifier("plus")
  frame->slots[7] /* temp__4 */ = create_closure(entry__compiler__expand_operator_call_25, 0);
  // 107: :
  // 108:   if
  // 109:     length_of(arguments_of(self)) == 1:
  // 110:       !functor std_identifier("negate")
  // 111:     :
  // 112:       !functor std_identifier("minus")
  frame->slots[8] /* temp__5 */ = create_closure(entry__compiler__expand_operator_call_28, 0);
  // 114: :
  // 115:   !functor std_identifier("shift_left")
  frame->slots[9] /* temp__6 */ = create_closure(entry__compiler__expand_operator_call_38, 0);
  // 117: :
  // 118:   !functor std_identifier("shift_right")
  frame->slots[10] /* temp__7 */ = create_closure(entry__compiler__expand_operator_call_41, 0);
  // 120: :
  // 121:   !functor std_identifier("bit_and")
  frame->slots[11] /* temp__8 */ = create_closure(entry__compiler__expand_operator_call_44, 0);
  // 123: :
  // 124:   !functor std_identifier("bit_xor")
  frame->slots[12] /* temp__9 */ = create_closure(entry__compiler__expand_operator_call_47, 0);
  // 126: :
  // 127:   !functor std_identifier("bit_or")
  frame->slots[13] /* temp__10 */ = create_closure(entry__compiler__expand_operator_call_50, 0);
  // 129: :
  // 130:   !functor std_identifier("less")
  // 131:   swap &self.arguments_of(1) &self.arguments_of(2)
  // 132:   !do_insert_not true
  frame->slots[14] /* temp__11 */ = create_closure(entry__compiler__expand_operator_call_53, 0);
  // 134: :
  // 135:   !functor std_identifier("less")
  frame->slots[15] /* temp__12 */ = create_closure(entry__compiler__expand_operator_call_65, 0);
  // 137: :
  // 138:   !functor std_identifier("less")
  // 139:   !do_insert_not true
  frame->slots[16] /* temp__13 */ = create_closure(entry__compiler__expand_operator_call_67, 0);
  // 141: :
  // 142:   !functor std_identifier("less")
  // 143:   swap &self.arguments_of(1) &self.arguments_of(2)
  frame->slots[17] /* temp__14 */ = create_closure(entry__compiler__expand_operator_call_69, 0);
  // 145: :
  // 146:   !functor std_identifier("equal")
  frame->slots[18] /* temp__15 */ = create_closure(entry__compiler__expand_operator_call_80, 0);
  // 148: :
  // 149:   !functor std_identifier("equal")
  // 150:   !do_insert_not true
  frame->slots[19] /* temp__16 */ = create_closure(entry__compiler__expand_operator_call_83, 0);
  // 152: :
  // 153:   !functor std_identifier("and")
  // 154:   make_right_argument_lazy
  frame->slots[20] /* temp__17 */ = create_closure(entry__compiler__expand_operator_call_85, 0);
  // 156: :
  // 157:   !functor std_identifier("or")
  // 158:   make_right_argument_lazy
  frame->slots[21] /* temp__18 */ = create_closure(entry__compiler__expand_operator_call_88, 0);
  // 160: :
  // 161:   !functor std_identifier("value_range")
  frame->slots[22] /* temp__19 */ = create_closure(entry__compiler__expand_operator_call_91, 0);
  // 163: :
  // 164:   !functor std_identifier("key_value_pair")
  frame->slots[23] /* temp__20 */ = create_closure(entry__compiler__expand_operator_call_94, 0);
  //  96: case name_of(functor)
  //  97:   "*"
  //  98:   :
  //  99:     !functor std_identifier("times")
  // 100:   "/"
  // 101:   :
  // 102:     !functor std_identifier("over")
  // 103:   "+"
  // 104:   :
  // 105:     !functor std_identifier("plus")
  // ...
  argument_count = 39;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = string__578a5af303e9ccb;
  arguments->slots[2] = frame->slots[5] /* temp__2 */;
  arguments->slots[3] = string__578a5af303e9cce;
  arguments->slots[4] = frame->slots[6] /* temp__3 */;
  arguments->slots[5] = string__578a5af303e9cca;
  arguments->slots[6] = frame->slots[7] /* temp__4 */;
  arguments->slots[7] = string__578a5af303e9ccc;
  arguments->slots[8] = frame->slots[8] /* temp__5 */;
  arguments->slots[9] = string__2d7981f4e6e82bf9;
  arguments->slots[10] = frame->slots[9] /* temp__6 */;
  arguments->slots[11] = string__2d7981f4e6f82bfb;
  arguments->slots[12] = frame->slots[10] /* temp__7 */;
  arguments->slots[13] = string__578a5af303e9cc7;
  arguments->slots[14] = frame->slots[11] /* temp__8 */;
  arguments->slots[15] = string__578a5af303e9cbf;
  arguments->slots[16] = frame->slots[12] /* temp__9 */;
  arguments->slots[17] = string__578a5af303e9c9d;
  arguments->slots[18] = frame->slots[13] /* temp__10 */;
  arguments->slots[19] = string__2d7981f4e6e82bf8;
  arguments->slots[20] = frame->slots[14] /* temp__11 */;
  arguments->slots[21] = string__578a5af303e9cdd;
  arguments->slots[22] = frame->slots[15] /* temp__12 */;
  arguments->slots[23] = string__2d7981f4e6f82bf8;
  arguments->slots[24] = frame->slots[16] /* temp__13 */;
  arguments->slots[25] = string__578a5af303e9cdf;
  arguments->slots[26] = frame->slots[17] /* temp__14 */;
  arguments->slots[27] = string__2d7981f4e6e02bf8;
  arguments->slots[28] = frame->slots[18] /* temp__15 */;
  arguments->slots[29] = string__2d7981f4e6002bf8;
  arguments->slots[30] = frame->slots[19] /* temp__16 */;
  arguments->slots[31] = string__2d7981f4e6382be3;
  arguments->slots[32] = frame->slots[20] /* temp__17 */;
  arguments->slots[33] = string__2d7981f4e4e82bb9;
  arguments->slots[34] = frame->slots[21] /* temp__18 */;
  arguments->slots[35] = string__2d7981f4e6782beb;
  arguments->slots[36] = frame->slots[22] /* temp__19 */;
  arguments->slots[37] = string__578a5af303e9cdc;
  arguments->slots[38] = frame->slots[23] /* temp__20 */;
  result_count = 0;
  myself = get__case();
  func = myself->type;
  frame->cont = cont__compiler__expand_operator_call_116;
}
static void entry__compiler__expand_operator_call_32(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // functor: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* functor */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 110: !functor std_identifier("negate")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__561f5607811a02b2;
  result_count = 1;
  myself = get__std_identifier();
  func = myself->type;
  frame->cont = cont__compiler__expand_operator_call_34;
}
static void cont__compiler__expand_operator_call_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* functor */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__expand_operator_call_35(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // functor: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* functor */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 112: !functor std_identifier("minus")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__585ae883ea60c024;
  result_count = 1;
  myself = get__std_identifier();
  func = myself->type;
  frame->cont = cont__compiler__expand_operator_call_37;
}
static void cont__compiler__expand_operator_call_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* functor */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__expand_operator_call_19(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // functor: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* functor */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 99: !functor std_identifier("times")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__585ae843eae15024;
  result_count = 1;
  myself = get__std_identifier();
  func = myself->type;
  frame->cont = cont__compiler__expand_operator_call_21;
}
static void cont__compiler__expand_operator_call_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* functor */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__expand_operator_call_22(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // functor: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* functor */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 102: !functor std_identifier("over")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__1c0aeccb5d487d4b;
  result_count = 1;
  myself = get__std_identifier();
  func = myself->type;
  frame->cont = cont__compiler__expand_operator_call_24;
}
static void cont__compiler__expand_operator_call_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* functor */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__expand_operator_call_25(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // functor: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* functor */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 105: !functor std_identifier("plus")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__220aea4b5dc87d4a;
  result_count = 1;
  myself = get__std_identifier();
  func = myself->type;
  frame->cont = cont__compiler__expand_operator_call_27;
}
static void cont__compiler__expand_operator_call_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* functor */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__expand_operator_call_28(void) {
  allocate_initialized_frame_gc(2, 7);
  // slot allocations:
  // self: 0
  // functor: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* self */
  frame->slots[1] = myself->closure.frame->slots[0]; /* functor */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 109: ... arguments_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__compiler__expand_operator_call_29;
}
static void cont__compiler__expand_operator_call_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 109: length_of(arguments_of(self))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__compiler__expand_operator_call_30;
}
static void cont__compiler__expand_operator_call_30(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 109: length_of(arguments_of(self)) == 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__compiler__expand_operator_call_31;
}
static void cont__compiler__expand_operator_call_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 109: ... :
  // 110:   !functor std_identifier("negate")
  frame->slots[5] /* temp__4 */ = create_closure(entry__compiler__expand_operator_call_32, 0);
  // 111: :
  // 112:   !functor std_identifier("minus")
  frame->slots[6] /* temp__5 */ = create_closure(entry__compiler__expand_operator_call_35, 0);
  // 108: if
  // 109:   length_of(arguments_of(self)) == 1:
  // 110:     !functor std_identifier("negate")
  // 111:   :
  // 112:     !functor std_identifier("minus")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__4 */;
  arguments->slots[2] = frame->slots[6] /* temp__5 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__expand_operator_call_38(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // functor: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* functor */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 115: !functor std_identifier("shift_left")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__2d7c8951ae1884d5;
  result_count = 1;
  myself = get__std_identifier();
  func = myself->type;
  frame->cont = cont__compiler__expand_operator_call_40;
}
static void cont__compiler__expand_operator_call_40(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* functor */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__expand_operator_call_41(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // functor: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* functor */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 118: !functor std_identifier("shift_right")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__528d708426488b90;
  result_count = 1;
  myself = get__std_identifier();
  func = myself->type;
  frame->cont = cont__compiler__expand_operator_call_43;
}
static void cont__compiler__expand_operator_call_43(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* functor */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__expand_operator_call_44(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // functor: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* functor */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 121: !functor std_identifier("bit_and")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__cc0c0d9615cb809e;
  result_count = 1;
  myself = get__std_identifier();
  func = myself->type;
  frame->cont = cont__compiler__expand_operator_call_46;
}
static void cont__compiler__expand_operator_call_46(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* functor */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__expand_operator_call_47(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // functor: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* functor */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 124: !functor std_identifier("bit_xor")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__cc0c0bd615c38088;
  result_count = 1;
  myself = get__std_identifier();
  func = myself->type;
  frame->cont = cont__compiler__expand_operator_call_49;
}
static void cont__compiler__expand_operator_call_49(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* functor */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__expand_operator_call_50(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // functor: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* functor */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 127: !functor std_identifier("bit_or")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__701f598181c2c2a5;
  result_count = 1;
  myself = get__std_identifier();
  func = myself->type;
  frame->cont = cont__compiler__expand_operator_call_52;
}
static void cont__compiler__expand_operator_call_52(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* functor */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__expand_operator_call_53(void) {
  allocate_initialized_frame_gc(3, 11);
  // slot allocations:
  // functor: 0
  // self: 1
  // do_insert_not: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* functor */
  frame->slots[1] = myself->closure.frame->slots[1]; /* self */
  frame->slots[2] = myself->closure.frame->slots[3]; /* do_insert_not */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 130: !functor std_identifier("less")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__1a0ae80b5df87d4a;
  result_count = 1;
  myself = get__std_identifier();
  func = myself->type;
  frame->cont = cont__compiler__expand_operator_call_55;
}
static void cont__compiler__expand_operator_call_55(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* functor */ = arguments->slots[0];
  // 131: ... self.arguments_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* self */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__compiler__expand_operator_call_56;
}
static void cont__compiler__expand_operator_call_56(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 131: ... self.arguments_of(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[4] /* temp__2 */;
  func = myself->type;
  frame->cont = cont__compiler__expand_operator_call_57;
}
static void cont__compiler__expand_operator_call_57(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 131: ... self.arguments_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* self */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__compiler__expand_operator_call_58;
}
static void cont__compiler__expand_operator_call_58(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__4 */ = arguments->slots[0];
  // 131: ... self.arguments_of(2)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = frame->slots[6] /* temp__4 */;
  func = myself->type;
  frame->cont = cont__compiler__expand_operator_call_59;
}
static void cont__compiler__expand_operator_call_59(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 131: swap &self.arguments_of(1) &self.arguments_of(2)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 2;
  myself = get__swap();
  func = myself->type;
  frame->cont = cont__compiler__expand_operator_call_60;
}
static void cont__compiler__expand_operator_call_60(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__5 */ = arguments->slots[0];
  frame->slots[8] /* temp__6 */ = arguments->slots[1];
  // 131: ... self.arguments_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* self */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__compiler__expand_operator_call_61;
}
static void cont__compiler__expand_operator_call_61(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__7 */ = arguments->slots[0];
  // 131: ... &self.arguments_of(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__1;
  arguments->slots[1] = frame->slots[7] /* temp__5 */;
  result_count = 1;
  myself = frame->slots[9] /* temp__7 */;
  func = myself->type;
  frame->cont = cont__compiler__expand_operator_call_62;
}
static void cont__compiler__expand_operator_call_62(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__7 */ = arguments->slots[0];
  // 131: ... &self.arguments_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[1])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[9] /* temp__7 */);
    ((CELL *)frame->slots[1])->contents /* self */ = temp;

  }
  // 131: ... self.arguments_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* self */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__compiler__expand_operator_call_63;
}
static void cont__compiler__expand_operator_call_63(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__8 */ = arguments->slots[0];
  // 131: ... &self.arguments_of(2)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__2;
  arguments->slots[1] = frame->slots[8] /* temp__6 */;
  result_count = 1;
  myself = frame->slots[10] /* temp__8 */;
  func = myself->type;
  frame->cont = cont__compiler__expand_operator_call_64;
}
static void cont__compiler__expand_operator_call_64(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__8 */ = arguments->slots[0];
  // 131: ... &self.arguments_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[1])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[10] /* temp__8 */);
    ((CELL *)frame->slots[1])->contents /* self */ = temp;

  }
  // 132: !do_insert_not true
  ((CELL *)frame->slots[2])->contents /* do_insert_not */ = get__true();
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__expand_operator_call_65(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // functor: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* functor */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 135: !functor std_identifier("less")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__1a0ae80b5df87d4a;
  result_count = 1;
  myself = get__std_identifier();
  func = myself->type;
  frame->cont = cont__compiler__expand_operator_call_66;
}
static void cont__compiler__expand_operator_call_66(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* functor */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__expand_operator_call_67(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // functor: 0
  // do_insert_not: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* functor */
  frame->slots[1] = myself->closure.frame->slots[3]; /* do_insert_not */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 138: !functor std_identifier("less")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__1a0ae80b5df87d4a;
  result_count = 1;
  myself = get__std_identifier();
  func = myself->type;
  frame->cont = cont__compiler__expand_operator_call_68;
}
static void cont__compiler__expand_operator_call_68(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* functor */ = arguments->slots[0];
  // 139: !do_insert_not true
  ((CELL *)frame->slots[1])->contents /* do_insert_not */ = get__true();
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__expand_operator_call_69(void) {
  allocate_initialized_frame_gc(2, 10);
  // slot allocations:
  // functor: 0
  // self: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* functor */
  frame->slots[1] = myself->closure.frame->slots[1]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 142: !functor std_identifier("less")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__1a0ae80b5df87d4a;
  result_count = 1;
  myself = get__std_identifier();
  func = myself->type;
  frame->cont = cont__compiler__expand_operator_call_70;
}
static void cont__compiler__expand_operator_call_70(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* functor */ = arguments->slots[0];
  // 143: ... self.arguments_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* self */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__compiler__expand_operator_call_71;
}
static void cont__compiler__expand_operator_call_71(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 143: ... self.arguments_of(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[3] /* temp__2 */;
  func = myself->type;
  frame->cont = cont__compiler__expand_operator_call_72;
}
static void cont__compiler__expand_operator_call_72(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 143: ... self.arguments_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* self */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__compiler__expand_operator_call_73;
}
static void cont__compiler__expand_operator_call_73(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__4 */ = arguments->slots[0];
  // 143: ... self.arguments_of(2)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = frame->slots[5] /* temp__4 */;
  func = myself->type;
  frame->cont = cont__compiler__expand_operator_call_74;
}
static void cont__compiler__expand_operator_call_74(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 143: swap &self.arguments_of(1) &self.arguments_of(2)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 2;
  myself = get__swap();
  func = myself->type;
  frame->cont = cont__compiler__expand_operator_call_75;
}
static void cont__compiler__expand_operator_call_75(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__5 */ = arguments->slots[0];
  frame->slots[7] /* temp__6 */ = arguments->slots[1];
  // 143: ... self.arguments_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* self */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__compiler__expand_operator_call_76;
}
static void cont__compiler__expand_operator_call_76(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__7 */ = arguments->slots[0];
  // 143: ... &self.arguments_of(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__1;
  arguments->slots[1] = frame->slots[6] /* temp__5 */;
  result_count = 1;
  myself = frame->slots[8] /* temp__7 */;
  func = myself->type;
  frame->cont = cont__compiler__expand_operator_call_77;
}
static void cont__compiler__expand_operator_call_77(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__7 */ = arguments->slots[0];
  // 143: ... &self.arguments_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[1])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[8] /* temp__7 */);
    ((CELL *)frame->slots[1])->contents /* self */ = temp;

  }
  // 143: ... self.arguments_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* self */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__compiler__expand_operator_call_78;
}
static void cont__compiler__expand_operator_call_78(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__8 */ = arguments->slots[0];
  // 143: ... &self.arguments_of(2)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__2;
  arguments->slots[1] = frame->slots[7] /* temp__6 */;
  result_count = 1;
  myself = frame->slots[9] /* temp__8 */;
  func = myself->type;
  frame->cont = cont__compiler__expand_operator_call_79;
}
static void cont__compiler__expand_operator_call_79(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__8 */ = arguments->slots[0];
  // 143: ... &self.arguments_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[1])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[9] /* temp__8 */);
    ((CELL *)frame->slots[1])->contents /* self */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__expand_operator_call_80(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // functor: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* functor */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 146: !functor std_identifier("equal")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__685aee43eac0403b;
  result_count = 1;
  myself = get__std_identifier();
  func = myself->type;
  frame->cont = cont__compiler__expand_operator_call_82;
}
static void cont__compiler__expand_operator_call_82(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* functor */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__expand_operator_call_83(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // functor: 0
  // do_insert_not: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* functor */
  frame->slots[1] = myself->closure.frame->slots[3]; /* do_insert_not */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 149: !functor std_identifier("equal")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__685aee43eac0403b;
  result_count = 1;
  myself = get__std_identifier();
  func = myself->type;
  frame->cont = cont__compiler__expand_operator_call_84;
}
static void cont__compiler__expand_operator_call_84(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* functor */ = arguments->slots[0];
  // 150: !do_insert_not true
  ((CELL *)frame->slots[1])->contents /* do_insert_not */ = get__true();
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__expand_operator_call_85(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // functor: 0
  // make_right_argument_lazy: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* functor */
  frame->slots[1] = myself->closure.frame->slots[2]; /* make_right_argument_lazy */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 153: !functor std_identifier("and")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__fa720015d596ba8;
  result_count = 1;
  myself = get__std_identifier();
  func = myself->type;
  frame->cont = cont__compiler__expand_operator_call_87;
}
static void cont__compiler__expand_operator_call_87(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* functor */ = arguments->slots[0];
  // 154: make_right_argument_lazy
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* make_right_argument_lazy */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__expand_operator_call_88(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // functor: 0
  // make_right_argument_lazy: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* functor */
  frame->slots[1] = myself->closure.frame->slots[2]; /* make_right_argument_lazy */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 157: !functor std_identifier("or")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e4702bb7;
  result_count = 1;
  myself = get__std_identifier();
  func = myself->type;
  frame->cont = cont__compiler__expand_operator_call_90;
}
static void cont__compiler__expand_operator_call_90(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* functor */ = arguments->slots[0];
  // 158: make_right_argument_lazy
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* make_right_argument_lazy */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__expand_operator_call_91(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // functor: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* functor */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 161: !functor std_identifier("value_range")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__2c93ac4233089e0;
  result_count = 1;
  myself = get__std_identifier();
  func = myself->type;
  frame->cont = cont__compiler__expand_operator_call_93;
}
static void cont__compiler__expand_operator_call_93(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* functor */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__expand_operator_call_94(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // functor: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* functor */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 164: !functor std_identifier("key_value_pair")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__64d512703527e2ab;
  result_count = 1;
  myself = get__std_identifier();
  func = myself->type;
  frame->cont = cont__compiler__expand_operator_call_96;
}
static void cont__compiler__expand_operator_call_96(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* functor */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__expand_operator_call_116(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 165: !self.functor_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[1])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__functor_of, ((CELL *)frame->slots[0])->contents /* functor */);
    ((CELL *)frame->slots[1])->contents /* self */ = temp;

  }
  // 166: ... :
  // 167:   !self
  // 168:     function_call
  // 169:       .functor_of std_identifier("not")
  // 170:       .arguments_of list(self)
  // 171:       .fragment_of fragment_of(self)
  // 172:       .source_position_of source_position_of(self)
  // 173:       .end_position_of end_position_of(self)
  frame->slots[4] /* temp__1 */ = create_closure(entry__compiler__expand_operator_call_117, 0);
  // 166: if do_insert_not:
  // 167:   !self
  // 168:     function_call
  // 169:       .functor_of std_identifier("not")
  // 170:       .arguments_of list(self)
  // 171:       .fragment_of fragment_of(self)
  // 172:       .source_position_of source_position_of(self)
  // 173:       .end_position_of end_position_of(self)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* do_insert_not */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__expand_operator_call_124(void) {
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
static void entry__compiler__function_call__expand_expression_1(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // self: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* self */ = create_cell_with_contents(arguments->slots[0]);
  // 176: show_compiler_debug_info "expand function call"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__2ae70e1058c2c0b7;
  result_count = 0;
  myself = get__show_compiler_debug_info();
  func = myself->type;
  frame->cont = cont__compiler__function_call__expand_expression_3;
}
static void cont__compiler__function_call__expand_expression_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 180: ... functor_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__functor_of();
  func = myself->type;
  frame->cont = cont__compiler__function_call__expand_expression_4;
}
static void cont__compiler__function_call__expand_expression_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 180: ... functor_of(self).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__compiler__function_call__expand_expression_5;
}
static void cont__compiler__function_call__expand_expression_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 180: ... :
  // 181:   expand_expression &self.functor_of
  // 182:   $functor functor_of(self)
  // 183:   if
  // 184:     functor.is_an_operator_symbol && name_of(functor) == ",":
  // 185:       $$arguments list(arguments_of(self)(1))
  // 186:       $$right arguments_of(self)(2)
  // 187:       while -> right.is_a_function_call && name_of(functor_of(right)) == ",":
  // 188:         $right_arguments arguments_of(right)
  // 189:         push &arguments right_arguments(1)
  // ...
  frame->slots[3] /* temp__3 */ = create_closure(entry__compiler__function_call__expand_expression_6, 0);
  // 180: if functor_of(self).is_defined:
  // 181:   expand_expression &self.functor_of
  // 182:   $functor functor_of(self)
  // 183:   if
  // 184:     functor.is_an_operator_symbol && name_of(functor) == ",":
  // 185:       $$arguments list(arguments_of(self)(1))
  // 186:       $$right arguments_of(self)(2)
  // 187:       while -> right.is_a_function_call && name_of(functor_of(right)) == ",":
  // 188:         $right_arguments arguments_of(right)
  // 189:         push &arguments right_arguments(1)
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
  frame->cont = cont__compiler__function_call__expand_expression_43;
}
static void entry__compiler__function_call__expand_expression_16(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // self: 0
  // arguments: 1
  // right: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  frame->slots[1] /* arguments */ = create_cell();
  frame->slots[2] /* right */ = create_cell();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 185: ... arguments_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__compiler__function_call__expand_expression_17;
}
static void cont__compiler__function_call__expand_expression_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 185: ... arguments_of(self)(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[4] /* temp__2 */;
  func = myself->type;
  frame->cont = cont__compiler__function_call__expand_expression_18;
}
static void cont__compiler__function_call__expand_expression_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 185: $$arguments list(arguments_of(self)(1))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__compiler__function_call__expand_expression_19;
}
static void cont__compiler__function_call__expand_expression_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* arguments */ = arguments->slots[0];
  // 186: ... arguments_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__compiler__function_call__expand_expression_20;
}
static void cont__compiler__function_call__expand_expression_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 186: $$right arguments_of(self)(2)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = frame->slots[3] /* temp__1 */;
  func = myself->type;
  frame->cont = cont__compiler__function_call__expand_expression_21;
}
static void cont__compiler__function_call__expand_expression_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* right */ = arguments->slots[0];
  // 187: ... -> right.is_a_function_call && name_of(functor_of(right)) == ",":
  // 188:   $right_arguments arguments_of(right)
  // 189:   push &arguments right_arguments(1)
  // 190:   !right right_arguments(2)
  frame->slots[3] /* temp__1 */ = create_closure(entry__compiler__function_call__expand_expression_22, 0);
  // 187: while -> right.is_a_function_call && name_of(functor_of(right)) == ",":
  // 188:   $right_arguments arguments_of(right)
  // 189:   push &arguments right_arguments(1)
  // 190:   !right right_arguments(2)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = 0;
  myself = get__while();
  func = myself->type;
  frame->cont = cont__compiler__function_call__expand_expression_34;
}
static void entry__compiler__function_call__expand_expression_29(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // right: 0
  // arguments: 1
  // right_arguments: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* right */
  frame->slots[1] = myself->closure.frame->slots[1]; /* arguments */
  frame->slots[2] /* right_arguments */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 188: $right_arguments arguments_of(right)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* right */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__compiler__function_call__expand_expression_30;
}
static void cont__compiler__function_call__expand_expression_30(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* right_arguments */, arguments->slots[0]);
  // 189: ... right_arguments(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[2] /* right_arguments */;
  func = myself->type;
  frame->cont = cont__compiler__function_call__expand_expression_31;
}
static void cont__compiler__function_call__expand_expression_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 189: push &arguments right_arguments(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* arguments */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__function_call__expand_expression_32;
}
static void cont__compiler__function_call__expand_expression_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* arguments */ = arguments->slots[0];
  // 190: !right right_arguments(2)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = frame->slots[2] /* right_arguments */;
  func = myself->type;
  frame->cont = cont__compiler__function_call__expand_expression_33;
}
static void cont__compiler__function_call__expand_expression_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* right */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__function_call__expand_expression_22(void) {
  allocate_initialized_frame_gc(2, 6);
  // slot allocations:
  // right: 0
  // arguments: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* right */
  frame->slots[1] = myself->closure.frame->slots[1]; /* arguments */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 187: ... right.is_a_function_call
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* right */;
  result_count = 1;
  myself = get__is_a_function_call();
  func = myself->type;
  frame->cont = cont__compiler__function_call__expand_expression_23;
}
static void cont__compiler__function_call__expand_expression_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 187: ... name_of(functor_of(right)) == ","
  frame->slots[4] /* temp__3 */ = create_closure(entry__compiler__function_call__expand_expression_24, 0);
  // 187: ... right.is_a_function_call && name_of(functor_of(right)) == ","
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__compiler__function_call__expand_expression_28;
}
static void entry__compiler__function_call__expand_expression_24(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // right: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* right */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 187: ... functor_of(right)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* right */;
  result_count = 1;
  myself = get__functor_of();
  func = myself->type;
  frame->cont = cont__compiler__function_call__expand_expression_25;
}
static void cont__compiler__function_call__expand_expression_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 187: ... name_of(functor_of(right))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__name_of();
  func = myself->type;
  frame->cont = cont__compiler__function_call__expand_expression_26;
}
static void cont__compiler__function_call__expand_expression_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 187: ... name_of(functor_of(right)) == ","
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = string__578a5af303e9ccd;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__compiler__function_call__expand_expression_27;
}
static void cont__compiler__function_call__expand_expression_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 187: ... name_of(functor_of(right)) == ","
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__function_call__expand_expression_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 187: ... :
  // 188:   $right_arguments arguments_of(right)
  // 189:   push &arguments right_arguments(1)
  // 190:   !right right_arguments(2)
  frame->slots[5] /* temp__4 */ = create_closure(entry__compiler__function_call__expand_expression_29, 0);
  // 187: ... -> right.is_a_function_call && name_of(functor_of(right)) == ",":
  // 188:   $right_arguments arguments_of(right)
  // 189:   push &arguments right_arguments(1)
  // 190:   !right right_arguments(2)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__4 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__function_call__expand_expression_34(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 191: push &arguments right
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* arguments */;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* right */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__function_call__expand_expression_35;
}
static void cont__compiler__function_call__expand_expression_35(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* arguments */ = arguments->slots[0];
  // 192: !self.functor_of std_identifier("sequence")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__6480ae5e84ccc225;
  result_count = 1;
  myself = get__std_identifier();
  func = myself->type;
  frame->cont = cont__compiler__function_call__expand_expression_37;
}
static void cont__compiler__function_call__expand_expression_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 192: !self.functor_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__functor_of, frame->slots[3] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* self */ = temp;

  }
  // 193: !self.arguments_of expand_arguments(arguments)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* arguments */;
  result_count = 1;
  myself = var._expand_arguments;
  func = myself->type;
  frame->cont = cont__compiler__function_call__expand_expression_38;
}
static void cont__compiler__function_call__expand_expression_38(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 193: !self.arguments_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[3] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* self */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__function_call__expand_expression_39(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // self: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 195: ... self.arguments_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__compiler__function_call__expand_expression_40;
}
static void cont__compiler__function_call__expand_expression_40(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 195: expand_arguments &self.arguments_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = var._expand_arguments;
  func = myself->type;
  frame->cont = cont__compiler__function_call__expand_expression_41;
}
static void cont__compiler__function_call__expand_expression_41(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 195: ... &self.arguments_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[2] /* temp__2 */);
    ((CELL *)frame->slots[0])->contents /* self */ = temp;

  }
  // 196: expand_operator_call &self
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__expand_operator_call();
  func = myself->type;
  frame->cont = cont__compiler__function_call__expand_expression_42;
}
static void cont__compiler__function_call__expand_expression_42(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* self */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__function_call__expand_expression_6(void) {
  allocate_initialized_frame_gc(1, 7);
  // slot allocations:
  // self: 0
  // functor: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  frame->slots[1] /* functor */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 181: ... self.functor_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__functor_of();
  func = myself->type;
  frame->cont = cont__compiler__function_call__expand_expression_7;
}
static void cont__compiler__function_call__expand_expression_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 181: expand_expression &self.functor_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__expand_expression();
  func = myself->type;
  frame->cont = cont__compiler__function_call__expand_expression_8;
}
static void cont__compiler__function_call__expand_expression_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 181: ... &self.functor_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__functor_of, frame->slots[3] /* temp__2 */);
    ((CELL *)frame->slots[0])->contents /* self */ = temp;

  }
  // 182: $functor functor_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__functor_of();
  func = myself->type;
  frame->cont = cont__compiler__function_call__expand_expression_9;
}
static void cont__compiler__function_call__expand_expression_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* functor */, arguments->slots[0]);
  // 184: functor.is_an_operator_symbol
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* functor */;
  result_count = 1;
  myself = get__is_an_operator_symbol();
  func = myself->type;
  frame->cont = cont__compiler__function_call__expand_expression_10;
}
static void cont__compiler__function_call__expand_expression_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 184: ... name_of(functor) == ","
  frame->slots[4] /* temp__3 */ = create_closure(entry__compiler__function_call__expand_expression_11, 0);
  // 184: functor.is_an_operator_symbol && name_of(functor) == ","
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__compiler__function_call__expand_expression_15;
}
static void entry__compiler__function_call__expand_expression_11(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // functor: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* functor */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 184: ... name_of(functor)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* functor */;
  result_count = 1;
  myself = get__name_of();
  func = myself->type;
  frame->cont = cont__compiler__function_call__expand_expression_12;
}
static void cont__compiler__function_call__expand_expression_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 184: ... name_of(functor) == ","
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = string__578a5af303e9ccd;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__compiler__function_call__expand_expression_14;
}
static void cont__compiler__function_call__expand_expression_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 184: ... name_of(functor) == ","
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__function_call__expand_expression_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 184: ... :
  // 185:   $$arguments list(arguments_of(self)(1))
  // 186:   $$right arguments_of(self)(2)
  // 187:   while -> right.is_a_function_call && name_of(functor_of(right)) == ",":
  // 188:     $right_arguments arguments_of(right)
  // 189:     push &arguments right_arguments(1)
  // 190:     !right right_arguments(2)
  // 191:   push &arguments right
  // 192:   !self.functor_of std_identifier("sequence")
  // 193:   !self.arguments_of expand_arguments(arguments)
  frame->slots[5] /* temp__4 */ = create_closure(entry__compiler__function_call__expand_expression_16, 0);
  // 194: :
  // 195:   expand_arguments &self.arguments_of
  // 196:   expand_operator_call &self
  frame->slots[6] /* temp__5 */ = create_closure(entry__compiler__function_call__expand_expression_39, 0);
  // 183: if
  // 184:   functor.is_an_operator_symbol && name_of(functor) == ",":
  // 185:     $$arguments list(arguments_of(self)(1))
  // 186:     $$right arguments_of(self)(2)
  // 187:     while -> right.is_a_function_call && name_of(functor_of(right)) == ",":
  // 188:       $right_arguments arguments_of(right)
  // 189:       push &arguments right_arguments(1)
  // 190:       !right right_arguments(2)
  // 191:     push &arguments right
  // 192:     !self.functor_of std_identifier("sequence")
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__4 */;
  arguments->slots[2] = frame->slots[6] /* temp__5 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__function_call__expand_expression_43(void) {
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
static void entry__compiler__attribute_value_pair__expand_expression_1(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // self: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* self */ = create_cell_with_contents(arguments->slots[0]);
  // 202: show_compiler_debug_info "expand attribute-value pair"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__30246dda36d83a54;
  result_count = 0;
  myself = get__show_compiler_debug_info();
  func = myself->type;
  frame->cont = cont__compiler__attribute_value_pair__expand_expression_3;
}
static void cont__compiler__attribute_value_pair__expand_expression_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 203: ... self.arguments_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__compiler__attribute_value_pair__expand_expression_4;
}
static void cont__compiler__attribute_value_pair__expand_expression_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 203: expand_arguments &self.arguments_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = var._expand_arguments;
  func = myself->type;
  frame->cont = cont__compiler__attribute_value_pair__expand_expression_5;
}
static void cont__compiler__attribute_value_pair__expand_expression_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 203: ... &self.arguments_of
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
static void entry__compiler__attribute_function_pair__expand_expression_1(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // self: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* self */ = create_cell_with_contents(arguments->slots[0]);
  // 209: show_compiler_debug_info "expand attribute-function pair"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__2c1ce19c26092926;
  result_count = 0;
  myself = get__show_compiler_debug_info();
  func = myself->type;
  frame->cont = cont__compiler__attribute_function_pair__expand_expression_3;
}
static void cont__compiler__attribute_function_pair__expand_expression_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 210: ... self.arguments_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__compiler__attribute_function_pair__expand_expression_4;
}
static void cont__compiler__attribute_function_pair__expand_expression_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 210: expand_arguments &self.arguments_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = var._expand_arguments;
  func = myself->type;
  frame->cont = cont__compiler__attribute_function_pair__expand_expression_5;
}
static void cont__compiler__attribute_function_pair__expand_expression_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 210: ... &self.arguments_of
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
EXPORT void collect__expander(void) {
  var.compiler__expand_statement = collect_node(var.compiler__expand_statement);
  var.compiler__expand_expression = collect_node(var.compiler__expand_expression);
  var._expand_arguments = collect_node(var._expand_arguments);
  var.compiler__expand_operator_call = collect_node(var.compiler__expand_operator_call);
}

static int already_run_phase_1 = false;

EXPORT void phase_1__expander(void) {
  if (already_run_phase_1) return;
  already_run_phase_1 = true;
  register_module_info(&module_info);
}

static int already_run_phase_2 = false;

EXPORT void phase_2__expander(void) {
  if (already_run_phase_2) return;
  already_run_phase_2 = true;
  set_module("expander");
  number__1 = from_uint32(1U);
  number__2 = from_uint32(2U);
  define_polymorphic_function("compiler", "expand_statement", get__compiler__expand_statement, &poly_idx__compiler__expand_statement, &var.compiler__expand_statement);
  define_polymorphic_function("compiler", "expand_expression", get__compiler__expand_expression, &poly_idx__compiler__expand_expression, &var.compiler__expand_expression);
  func__expand_arguments_1 = create_function(entry__expand_arguments_1, 1);
  string__582ccfaf004aa58 = from_latin_1_string("expand statement", 16);
  func__types__grammar_node__expand_statement_1 = create_function(entry__types__grammar_node__expand_statement_1, 1);
  string__4bcf31e55e19ce58 = from_latin_1_string("expand expression", 17);
  func__types__grammar_node__expand_expression_1 = create_function(entry__types__grammar_node__expand_expression_1, 1);
  string__c4e5f299bf2dab78 = from_latin_1_string("expand body", 11);
  func__compiler__body__expand_expression_5 = create_function(entry__compiler__body__expand_expression_5, 1);
  func__compiler__body__expand_expression_14 = create_function(entry__compiler__body__expand_expression_14, 1);
  func__compiler__body__expand_expression_1 = create_function(entry__compiler__body__expand_expression_1, 1);
  func__compiler__call__expand_statement_1 = create_function(entry__compiler__call__expand_statement_1, 1);
  string__585ae843eae15024 = from_latin_1_string("times", 5);
  string__1c0aeccb5d487d4b = from_latin_1_string("over", 4);
  string__220aea4b5dc87d4a = from_latin_1_string("plus", 4);
  string__561f5607811a02b2 = from_latin_1_string("negate", 6);
  string__585ae883ea60c024 = from_latin_1_string("minus", 5);
  string__2d7c8951ae1884d5 = from_latin_1_string("shift_left", 10);
  string__528d708426488b90 = from_latin_1_string("shift_right", 11);
  string__cc0c0d9615cb809e = from_latin_1_string("bit_and", 7);
  string__cc0c0bd615c38088 = from_latin_1_string("bit_xor", 7);
  string__701f598181c2c2a5 = from_latin_1_string("bit_or", 6);
  string__1a0ae80b5df87d4a = from_latin_1_string("less", 4);
  string__685aee43eac0403b = from_latin_1_string("equal", 5);
  string__fa720015d596ba8 = from_latin_1_string("and", 3);
  string__2d7981f4e4702bb7 = from_latin_1_string("or", 2);
  string__2c93ac4233089e0 = from_latin_1_string("value_range", 11);
  string__64d512703527e2ab = from_latin_1_string("key_value_pair", 14);
  string__578a5af303e9ccb = from_latin_1_string("*", 1);
  string__578a5af303e9cce = from_latin_1_string("/", 1);
  string__578a5af303e9cca = from_latin_1_string("+", 1);
  string__578a5af303e9ccc = from_latin_1_string("-", 1);
  string__2d7981f4e6e82bf9 = from_latin_1_string("<<", 2);
  string__2d7981f4e6f82bfb = from_latin_1_string(">>", 2);
  string__578a5af303e9cc7 = from_latin_1_string("&", 1);
  string__578a5af303e9cbf = from_latin_1_string("^", 1);
  string__578a5af303e9c9d = from_latin_1_string("|", 1);
  string__2d7981f4e6e82bf8 = from_latin_1_string("<=", 2);
  string__578a5af303e9cdd = from_latin_1_string("<", 1);
  string__2d7981f4e6f82bf8 = from_latin_1_string(">=", 2);
  string__578a5af303e9cdf = from_latin_1_string(">", 1);
  string__2d7981f4e6e02bf8 = from_latin_1_string("==", 2);
  string__2d7981f4e6002bf8 = from_latin_1_string("!=", 2);
  string__2d7981f4e6382be3 = from_latin_1_string("&&", 2);
  string__2d7981f4e4e82bb9 = from_latin_1_string("||", 2);
  string__2d7981f4e6782beb = from_latin_1_string("..", 2);
  string__578a5af303e9cdc = from_latin_1_string("=", 1);
  string__fa723c15d516bb8 = from_latin_1_string("not", 3);
  func__compiler__expand_operator_call_1 = create_function(entry__compiler__expand_operator_call_1, 1);
  string__2ae70e1058c2c0b7 = from_latin_1_string("expand function call", 20);
  string__578a5af303e9ccd = from_latin_1_string(",", 1);
  string__6480ae5e84ccc225 = from_latin_1_string("sequence", 8);
  func__compiler__function_call__expand_expression_1 = create_function(entry__compiler__function_call__expand_expression_1, 1);
  string__30246dda36d83a54 = from_latin_1_string("expand attribute-value pair", 27);
  func__compiler__attribute_value_pair__expand_expression_1 = create_function(entry__compiler__attribute_value_pair__expand_expression_1, 1);
  string__2c1ce19c26092926 = from_latin_1_string("expand attribute-function pair", 30);
  func__compiler__attribute_function_pair__expand_expression_1 = create_function(entry__compiler__attribute_function_pair__expand_expression_1, 1);
}

static int already_run_phase_3 = false;

EXPORT void phase_3__expander(void) {
  if (already_run_phase_3) return;
  already_run_phase_3 = true;
  set_module("expander");
  set_used_namespaces(used_namespaces);
  define_single_assign_static("compiler", "expand_operator_call", get__compiler__expand_operator_call, &var.compiler__expand_operator_call);
}

static int already_run_phase_4 = false;

EXPORT void phase_4__expander(void) {
  if (already_run_phase_4) return;
  already_run_phase_4 = true;
  set_module("expander");
  set_used_namespaces(used_namespaces);
  use_polymorphic_function(NULL, "arguments_of", &get__arguments_of, &poly_idx__arguments_of);
  use_read_only(NULL, "body", &get__body, &get_value_or_future__body);
  use_read_only(NULL, "case", &get__case, &get_value_or_future__case);
  use_read_only("compiler", "attribute_function_pair", &get__compiler__attribute_function_pair, &get_value_or_future__compiler__attribute_function_pair);
  use_read_only("compiler", "attribute_value_pair", &get__compiler__attribute_value_pair, &get_value_or_future__compiler__attribute_value_pair);
  use_read_only("compiler", "body", &get__compiler__body, &get_value_or_future__compiler__body);
  use_read_only("compiler", "call", &get__compiler__call, &get_value_or_future__compiler__call);
  use_read_only("compiler", "function_call", &get__compiler__function_call, &get_value_or_future__compiler__function_call);
  use_polymorphic_function(NULL, "default_value_of", &get__default_value_of, &poly_idx__default_value_of);
  use_read_only(NULL, "empty_list", &get__empty_list, &get_value_or_future__empty_list);
  use_polymorphic_function(NULL, "end_position_of", &get__end_position_of, &poly_idx__end_position_of);
  use_polymorphic_function(NULL, "expand_expression", &get__expand_expression, &poly_idx__expand_expression);
  use_read_only(NULL, "expand_operator_call", &get__expand_operator_call, &get_value_or_future__expand_operator_call);
  use_polymorphic_function(NULL, "expand_statement", &get__expand_statement, &poly_idx__expand_statement);
  use_read_only(NULL, "expression_of", &get__expression_of, &get_value_or_future__expression_of);
  use_read_only(NULL, "false", &get__false, &get_value_or_future__false);
  use_read_only(NULL, "for_each", &get__for_each, &get_value_or_future__for_each);
  use_polymorphic_function(NULL, "fragment_of", &get__fragment_of, &poly_idx__fragment_of);
  use_read_only(NULL, "function_call", &get__function_call, &get_value_or_future__function_call);
  use_polymorphic_function(NULL, "functor_of", &get__functor_of, &poly_idx__functor_of);
  use_read_only(NULL, "if", &get__if, &get_value_or_future__if);
  use_read_only(NULL, "is_a_backquoted_expression", &get__is_a_backquoted_expression, &get_value_or_future__is_a_backquoted_expression);
  use_read_only(NULL, "is_a_function_call", &get__is_a_function_call, &get_value_or_future__is_a_function_call);
  use_read_only(NULL, "is_an_operator_symbol", &get__is_an_operator_symbol, &get_value_or_future__is_an_operator_symbol);
  use_read_only(NULL, "is_defined", &get__is_defined, &get_value_or_future__is_defined);
  use_read_only(NULL, "length_of", &get__length_of, &get_value_or_future__length_of);
  use_read_only(NULL, "list", &get__list, &get_value_or_future__list);
  use_read_only(NULL, "name_of", &get__name_of, &get_value_or_future__name_of);
  use_polymorphic_function("node", "text_of", &get__node__text_of, &poly_idx__node__text_of);
  use_polymorphic_function(NULL, "parameters_of", &get__parameters_of, &poly_idx__parameters_of);
  use_read_only(NULL, "push", &get__push, &get_value_or_future__push);
  use_polymorphic_function(NULL, "result_count_of", &get__result_count_of, &poly_idx__result_count_of);
  use_read_only(NULL, "return_statement", &get__return_statement, &get_value_or_future__return_statement);
  use_read_only(NULL, "show_compiler_debug_info", &get__show_compiler_debug_info, &get_value_or_future__show_compiler_debug_info);
  use_polymorphic_function(NULL, "source_position_of", &get__source_position_of, &poly_idx__source_position_of);
  use_polymorphic_function(NULL, "statements_of", &get__statements_of, &poly_idx__statements_of);
  use_read_only("std", "and", &get__std__and, &get_value_or_future__std__and);
  use_read_only("std", "equal", &get__std__equal, &get_value_or_future__std__equal);
  use_read_only(NULL, "std_identifier", &get__std_identifier, &get_value_or_future__std_identifier);
  use_read_only(NULL, "string_literal", &get__string_literal, &get_value_or_future__string_literal);
  use_read_only(NULL, "swap", &get__swap, &get_value_or_future__swap);
  use_read_only(NULL, "true", &get__true, &get_value_or_future__true);
  use_read_only("types", "grammar_node", &get__types__grammar_node, &get_value_or_future__types__grammar_node);
  use_read_only(NULL, "update_each", &get__update_each, &get_value_or_future__update_each);
  use_read_only(NULL, "while", &get__while, &get_value_or_future__while);
  define_method("types", "grammar_node", poly_idx__expand_statement, func__types__grammar_node__expand_statement_1);
  define_method("types", "grammar_node", poly_idx__expand_expression, func__types__grammar_node__expand_expression_1);
  define_method("compiler", "body", poly_idx__expand_expression, func__compiler__body__expand_expression_1);
  define_method("compiler", "call", poly_idx__expand_statement, func__compiler__call__expand_statement_1);
  define_method("compiler", "function_call", poly_idx__expand_expression, func__compiler__function_call__expand_expression_1);
  define_method("compiler", "attribute_value_pair", poly_idx__expand_expression, func__compiler__attribute_value_pair__expand_expression_1);
  define_method("compiler", "attribute_function_pair", poly_idx__expand_expression, func__compiler__attribute_function_pair__expand_expression_1);
}

static int already_run_phase_5 = false;

EXPORT void phase_5__expander(void) {
  if (already_run_phase_5) return;
  already_run_phase_5 = true;
  assign_value(&var.compiler__expand_statement, create_function(type__compiler__expand_statement, -1));
  assign_value(&var.compiler__expand_expression, create_function(type__compiler__expand_expression, -1));
  assign_variable(&var._expand_arguments, &func__expand_arguments_1);
  assign_variable(&var.compiler__expand_operator_call, &func__compiler__expand_operator_call_1);
}

static int already_run_phase_6 = false;

EXPORT void phase_6__expander(void) {
  if (already_run_phase_6) return;
  already_run_phase_6 = true;
  register_collector(collect__expander);
}
