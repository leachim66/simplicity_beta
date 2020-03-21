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
IMPORT void define_polymorphic_function(
  const char *namespace, const char *name, NODE_GETTER getter, int *id_p,
  NODE **var_p
);
IMPORT void set_module(const char *name);
IMPORT void set_used_namespaces(const char **namespaces);
IMPORT NODE *from_uint32(uint32_t val);
IMPORT NODE *from_latin_1_string(const char *str, long len);
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

#define ENCODE_ADDRESS(addr) ((void *)((uintptr_t)addr | 2))
#define DECODE_ADDRESS(addr) ((void *)((uintptr_t)addr & -3))
#define IS_AN_INVALID_ADDRESS(addr) ((uintptr_t)addr & 2)

#define MSB (1L << (8*sizeof(void *)-1))
#define ENCODE_TO_LENGTH(addr) ((void *)(((uintptr_t)addr >> 1) | MSB))
#define DECODE_FROM_LENGTH(addr) ((void *)((uintptr_t)addr << 1))
#define IS_AN_INVALID_LENGTH(addr) ((uintptr_t)addr & MSB)

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
static int poly_idx__arguments_of;
static NODE_GETTER get__arguments_of;
static NODE_GETTER get__body;
static NODE_GETTER get_value_or_future__body;
static NODE_GETTER get__case;
static NODE_GETTER get_value_or_future__case;
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
static int poly_idx__output_arguments_of;
static NODE_GETTER get__output_arguments_of;
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
static NODE_GETTER get__sim2c__attribute_function_pair;
static NODE_GETTER get_value_or_future__sim2c__attribute_function_pair;
static NODE_GETTER get__sim2c__attribute_value_pair;
static NODE_GETTER get_value_or_future__sim2c__attribute_value_pair;
static NODE_GETTER get__sim2c__body;
static NODE_GETTER get_value_or_future__sim2c__body;
static NODE_GETTER get__sim2c__call;
static NODE_GETTER get_value_or_future__sim2c__call;
static NODE_GETTER get__sim2c__function_call;
static NODE_GETTER get_value_or_future__sim2c__function_call;
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
  NODE *sim2c__expand_statement;
  NODE *sim2c__expand_expression;
  NODE *sim2c__expand_operator_call;
} var;
static const char *var_names[] = {
  "expand_arguments"
};
static int poly_idx__sim2c__expand_statement;
static void type__sim2c__expand_statement(void);
static NODE *get__sim2c__expand_statement(void) {
  return var.sim2c__expand_statement;
}
static int poly_idx__sim2c__expand_expression;
static void type__sim2c__expand_expression(void);
static NODE *get__sim2c__expand_expression(void) {
  return var.sim2c__expand_expression;
}
static NODE *func__3_1;
static void entry__3_1(void);
static FRAME_INFO frame__3_1 = {2, {"arguments", "new_arguments"}};
static NODE *func__3_2;
static void entry__3_2(void);
static FRAME_INFO frame__3_2 = {2, {"argument", "new_arguments"}};
static void cont__3_3(void);
static NODE *func__3_4;
static void entry__3_4(void);
static FRAME_INFO frame__3_4 = {2, {"new_arguments", "argument"}};
static void cont__3_5(void);
static void cont__3_6(void);
static void cont__3_7(void);
static void cont__3_8(void);
static void cont__3_9(void);
static NODE *func__3_10;
static void entry__3_10(void);
static FRAME_INFO frame__3_10 = {2, {"new_arguments", "argument"}};
static void cont__3_11(void);
static void cont__3_12(void);
static void cont__3_13(void);
static NODE *func__4_1;
static void entry__4_1(void);
static FRAME_INFO frame__4_1 = {1, {"self"}};
static NODE *string__4_2;
static void cont__4_3(void);
static NODE *func__5_1;
static void entry__5_1(void);
static FRAME_INFO frame__5_1 = {1, {"self"}};
static NODE *string__5_2;
static void cont__5_3(void);
static NODE *func__6_1;
static void entry__6_1(void);
static FRAME_INFO frame__6_1 = {1, {"self"}};
static NODE *string__6_2;
static void cont__6_3(void);
static void cont__6_4(void);
static NODE *func__6_5;
static void entry__6_5(void);
static FRAME_INFO frame__6_5 = {1, {"parameter"}};
static void cont__6_6(void);
static void cont__6_7(void);
static NODE *func__6_8;
static void entry__6_8(void);
static FRAME_INFO frame__6_8 = {1, {"parameter"}};
static void cont__6_9(void);
static void cont__6_10(void);
static void cont__6_11(void);
static void cont__6_12(void);
static void cont__6_13(void);
static NODE *func__6_14;
static void entry__6_14(void);
static FRAME_INFO frame__6_14 = {1, {"stmt"}};
static void cont__6_15(void);
static void cont__6_16(void);
static NODE *func__7_1;
static void entry__7_1(void);
static FRAME_INFO frame__7_1 = {1, {"self"}};
static NODE *string__7_2;
static void cont__7_3(void);
static void cont__7_4(void);
static void cont__7_5(void);
static NODE *func__7_6;
static void entry__7_6(void);
static FRAME_INFO frame__7_6 = {1, {"self"}};
static void cont__7_7(void);
static void cont__7_8(void);
static NODE *func__7_9;
static void entry__7_9(void);
static FRAME_INFO frame__7_9 = {1, {"self"}};
static void cont__7_10(void);
static void cont__7_11(void);
static void cont__7_12(void);
static void cont__7_13(void);
static void cont__7_14(void);
static void cont__7_15(void);
static void cont__7_16(void);
static void cont__7_17(void);
static void cont__7_18(void);
static void cont__7_19(void);
static NODE *func__8_1;
static void entry__8_1(void);
static FRAME_INFO frame__8_1 = {3, {"self", "make_right_argument_lazy", "functor"}};
static NODE *func__8_2;
static void entry__8_2(void);
static FRAME_INFO frame__8_2 = {2, {"self", "right"}};
static void cont__8_3(void);
static void cont__8_4(void);
static void cont__8_5(void);
static void cont__8_6(void);
static void cont__8_7(void);
static void cont__8_8(void);
static void cont__8_9(void);
static void cont__8_10(void);
static void cont__8_11(void);
static void cont__8_12(void);
static void cont__8_13(void);
static void cont__8_14(void);
static void cont__8_15(void);
static void cont__8_16(void);
static NODE *func__8_17;
static void entry__8_17(void);
static FRAME_INFO frame__8_17 = {4, {"functor", "self", "make_right_argument_lazy", "do_insert_not"}};
static void cont__8_18(void);
static NODE *func__8_19;
static void entry__8_19(void);
static FRAME_INFO frame__8_19 = {1, {"functor"}};
static NODE *string__8_20;
static void cont__8_21(void);
static NODE *func__8_22;
static void entry__8_22(void);
static FRAME_INFO frame__8_22 = {1, {"functor"}};
static NODE *string__8_23;
static void cont__8_24(void);
static NODE *func__8_25;
static void entry__8_25(void);
static FRAME_INFO frame__8_25 = {1, {"functor"}};
static NODE *string__8_26;
static void cont__8_27(void);
static NODE *func__8_28;
static void entry__8_28(void);
static FRAME_INFO frame__8_28 = {2, {"self", "functor"}};
static void cont__8_29(void);
static void cont__8_30(void);
static void cont__8_31(void);
static NODE *func__8_32;
static void entry__8_32(void);
static FRAME_INFO frame__8_32 = {1, {"functor"}};
static NODE *string__8_33;
static void cont__8_34(void);
static NODE *func__8_35;
static void entry__8_35(void);
static FRAME_INFO frame__8_35 = {1, {"functor"}};
static NODE *string__8_36;
static void cont__8_37(void);
static NODE *func__8_38;
static void entry__8_38(void);
static FRAME_INFO frame__8_38 = {1, {"functor"}};
static NODE *string__8_39;
static void cont__8_40(void);
static NODE *func__8_41;
static void entry__8_41(void);
static FRAME_INFO frame__8_41 = {1, {"functor"}};
static NODE *string__8_42;
static void cont__8_43(void);
static NODE *func__8_44;
static void entry__8_44(void);
static FRAME_INFO frame__8_44 = {1, {"functor"}};
static NODE *string__8_45;
static void cont__8_46(void);
static NODE *func__8_47;
static void entry__8_47(void);
static FRAME_INFO frame__8_47 = {1, {"functor"}};
static NODE *string__8_48;
static void cont__8_49(void);
static NODE *func__8_50;
static void entry__8_50(void);
static FRAME_INFO frame__8_50 = {1, {"functor"}};
static NODE *string__8_51;
static void cont__8_52(void);
static NODE *func__8_53;
static void entry__8_53(void);
static FRAME_INFO frame__8_53 = {3, {"functor", "self", "do_insert_not"}};
static NODE *string__8_54;
static void cont__8_55(void);
static void cont__8_56(void);
static void cont__8_57(void);
static void cont__8_58(void);
static void cont__8_59(void);
static void cont__8_60(void);
static void cont__8_61(void);
static void cont__8_62(void);
static void cont__8_63(void);
static void cont__8_64(void);
static NODE *func__8_65;
static void entry__8_65(void);
static FRAME_INFO frame__8_65 = {1, {"functor"}};
static NODE *string__8_66;
static void cont__8_67(void);
static NODE *func__8_68;
static void entry__8_68(void);
static FRAME_INFO frame__8_68 = {2, {"functor", "do_insert_not"}};
static NODE *string__8_69;
static void cont__8_70(void);
static NODE *func__8_71;
static void entry__8_71(void);
static FRAME_INFO frame__8_71 = {2, {"functor", "self"}};
static NODE *string__8_72;
static void cont__8_73(void);
static void cont__8_74(void);
static void cont__8_75(void);
static void cont__8_76(void);
static void cont__8_77(void);
static void cont__8_78(void);
static void cont__8_79(void);
static void cont__8_80(void);
static void cont__8_81(void);
static void cont__8_82(void);
static NODE *func__8_83;
static void entry__8_83(void);
static FRAME_INFO frame__8_83 = {1, {"functor"}};
static NODE *string__8_84;
static void cont__8_85(void);
static NODE *func__8_86;
static void entry__8_86(void);
static FRAME_INFO frame__8_86 = {2, {"functor", "do_insert_not"}};
static NODE *string__8_87;
static void cont__8_88(void);
static NODE *func__8_89;
static void entry__8_89(void);
static FRAME_INFO frame__8_89 = {2, {"functor", "make_right_argument_lazy"}};
static NODE *string__8_90;
static void cont__8_91(void);
static NODE *func__8_92;
static void entry__8_92(void);
static FRAME_INFO frame__8_92 = {2, {"functor", "make_right_argument_lazy"}};
static NODE *string__8_93;
static void cont__8_94(void);
static NODE *func__8_95;
static void entry__8_95(void);
static FRAME_INFO frame__8_95 = {1, {"functor"}};
static NODE *string__8_96;
static void cont__8_97(void);
static NODE *func__8_98;
static void entry__8_98(void);
static FRAME_INFO frame__8_98 = {1, {"functor"}};
static NODE *string__8_99;
static void cont__8_100(void);
static NODE *string__8_101;
static NODE *string__8_102;
static NODE *string__8_103;
static NODE *string__8_104;
static NODE *string__8_105;
static NODE *string__8_106;
static NODE *string__8_107;
static NODE *string__8_108;
static NODE *string__8_109;
static NODE *string__8_110;
static NODE *string__8_111;
static NODE *string__8_112;
static NODE *string__8_113;
static NODE *string__8_114;
static NODE *string__8_115;
static NODE *string__8_116;
static NODE *string__8_117;
static NODE *string__8_118;
static NODE *string__8_119;
static void cont__8_120(void);
static NODE *func__8_121;
static void entry__8_121(void);
static FRAME_INFO frame__8_121 = {1, {"self"}};
static NODE *string__8_122;
static void cont__8_123(void);
static void cont__8_124(void);
static void cont__8_125(void);
static void cont__8_126(void);
static void cont__8_127(void);
static void cont__8_128(void);
static NODE *get__sim2c__expand_operator_call(void) {
  return var.sim2c__expand_operator_call;
}
static NODE *func__9_1;
static void entry__9_1(void);
static FRAME_INFO frame__9_1 = {1, {"self"}};
static NODE *string__9_2;
static void cont__9_3(void);
static void cont__9_4(void);
static void cont__9_5(void);
static NODE *func__9_6;
static void entry__9_6(void);
static FRAME_INFO frame__9_6 = {2, {"self", "functor"}};
static void cont__9_7(void);
static void cont__9_8(void);
static void cont__9_9(void);
static void cont__9_10(void);
static NODE *func__9_11;
static void entry__9_11(void);
static FRAME_INFO frame__9_11 = {1, {"functor"}};
static void cont__9_12(void);
static NODE *string__9_13;
static void cont__9_14(void);
static void cont__9_15(void);
static NODE *func__9_16;
static void entry__9_16(void);
static FRAME_INFO frame__9_16 = {3, {"self", "arguments", "right"}};
static void cont__9_17(void);
static void cont__9_18(void);
static void cont__9_19(void);
static void cont__9_20(void);
static void cont__9_21(void);
static NODE *func__9_22;
static void entry__9_22(void);
static FRAME_INFO frame__9_22 = {2, {"right", "arguments"}};
static void cont__9_23(void);
static NODE *func__9_24;
static void entry__9_24(void);
static FRAME_INFO frame__9_24 = {1, {"right"}};
static void cont__9_25(void);
static void cont__9_26(void);
static NODE *string__9_27;
static void cont__9_28(void);
static void cont__9_29(void);
static NODE *func__9_30;
static void entry__9_30(void);
static FRAME_INFO frame__9_30 = {3, {"right", "arguments", "right_arguments"}};
static void cont__9_31(void);
static void cont__9_32(void);
static void cont__9_33(void);
static void cont__9_34(void);
static void cont__9_35(void);
static void cont__9_36(void);
static NODE *string__9_37;
static void cont__9_38(void);
static void cont__9_39(void);
static NODE *func__9_40;
static void entry__9_40(void);
static FRAME_INFO frame__9_40 = {1, {"self"}};
static void cont__9_41(void);
static void cont__9_42(void);
static void cont__9_43(void);
static void cont__9_44(void);
static NODE *func__10_1;
static void entry__10_1(void);
static FRAME_INFO frame__10_1 = {1, {"self"}};
static NODE *string__10_2;
static void cont__10_3(void);
static void cont__10_4(void);
static void cont__10_5(void);
static NODE *func__11_1;
static void entry__11_1(void);
static FRAME_INFO frame__11_1 = {1, {"self"}};
static NODE *string__11_2;
static void cont__11_3(void);
static void cont__11_4(void);
static void cont__11_5(void);
void run__expander(void);

static CONTINUATION_INFO continuation_info[] = {
  {type__sim2c__expand_statement, NULL, 29, 29, 2, 24},
  {type__sim2c__expand_expression, NULL, 30, 30, 2, 25},
  {run__expander, NULL, },
  {entry__3_4, NULL, 39, 39, 41, 63},
  {cont__3_5, &frame__3_4, 37, 39, 9, 64},
  {cont__3_6, &frame__3_4, 40, 40, 47, 69},
  {cont__3_7, &frame__3_4, 40, 40, 29, 70},
  {cont__3_8, &frame__3_4, 40, 40, 9, 70},
  {cont__3_9, &frame__3_4, 40, 40, 70, 70},
  {entry__3_10, NULL, 42, 42, 29, 55},
  {cont__3_11, &frame__3_10, 42, 42, 9, 55},
  {cont__3_12, &frame__3_10, 42, 42, 55, 55},
  {entry__3_2, NULL, 36, 36, 7, 41},
  {cont__3_3, &frame__3_2, 35, 42, 5, 56},
  {entry__3_1, NULL, 34, 42, 3, 57},
  {cont__3_13, &frame__3_1, 43, 43, 3, 18},
  {entry__4_1, NULL, 49, 49, 3, 45},
  {cont__4_3, &frame__4_1, },
  {entry__5_1, NULL, 52, 52, 3, 46},
  {cont__5_3, &frame__5_1, },
  {entry__6_8, NULL, 61, 61, 26, 51},
  {cont__6_9, &frame__6_8, 61, 61, 7, 51},
  {cont__6_10, &frame__6_8, 61, 61, 51, 51},
  {entry__6_5, NULL, 60, 60, 8, 34},
  {cont__6_6, &frame__6_5, 60, 60, 8, 45},
  {cont__6_7, &frame__6_5, 60, 61, 5, 51},
  {cont__6_11, &frame__6_5, },
  {entry__6_14, NULL, 62, 62, 44, 65},
  {cont__6_15, &frame__6_14, 62, 62, 65, 65},
  {entry__6_1, NULL, 58, 58, 3, 40},
  {cont__6_3, &frame__6_1, 59, 59, 16, 33},
  {cont__6_4, &frame__6_1, 59, 61, 3, 52},
  {cont__6_12, &frame__6_1, 62, 62, 16, 33},
  {cont__6_13, &frame__6_1, 62, 62, 3, 65},
  {cont__6_16, &frame__6_1, 62, 62, 65, 65},
  {entry__7_9, NULL, 70, 70, 61, 80},
  {cont__7_10, &frame__7_9, 70, 70, 42, 80},
  {cont__7_11, &frame__7_9, 70, 70, 80, 80},
  {entry__7_6, NULL, 70, 70, 8, 28},
  {cont__7_7, &frame__7_6, 70, 70, 8, 39},
  {cont__7_8, &frame__7_6, 70, 70, 5, 80},
  {cont__7_12, &frame__7_6, 71, 71, 24, 38},
  {cont__7_13, &frame__7_6, 71, 71, 5, 38},
  {cont__7_14, &frame__7_6, 71, 71, 38, 38},
  {entry__7_1, NULL, 68, 68, 3, 45},
  {cont__7_3, &frame__7_1, 69, 69, 6, 21},
  {cont__7_4, &frame__7_1, 69, 69, 6, 32},
  {cont__7_5, &frame__7_1, 69, 71, 3, 38},
  {cont__7_15, &frame__7_1, 72, 72, 21, 37},
  {cont__7_16, &frame__7_1, 72, 72, 3, 37},
  {cont__7_17, &frame__7_1, 73, 73, 21, 44},
  {cont__7_18, &frame__7_1, 73, 73, 3, 44},
  {cont__7_19, &frame__7_1, 73, 73, 44, 44},
  {entry__8_2, NULL, 80, 80, 12, 29},
  {cont__8_3, &frame__8_2, 80, 80, 5, 32},
  {cont__8_4, &frame__8_2, 86, 86, 29, 39},
  {cont__8_5, &frame__8_2, 87, 87, 28, 45},
  {cont__8_6, &frame__8_2, 88, 88, 35, 59},
  {cont__8_7, &frame__8_2, 89, 89, 32, 53},
  {cont__8_8, &frame__8_2, 84, 89, 11, 53},
  {cont__8_9, &frame__8_2, 90, 90, 22, 39},
  {cont__8_10, &frame__8_2, 91, 91, 29, 53},
  {cont__8_11, &frame__8_2, 92, 92, 26, 47},
  {cont__8_12, &frame__8_2, 81, 81, 6, 22},
  {cont__8_13, &frame__8_2, 81, 81, 5, 25},
  {cont__8_14, &frame__8_2, 92, 92, 49, 49},
  {entry__8_19, NULL, 100, 100, 9, 40},
  {cont__8_21, &frame__8_19, 100, 100, 40, 40},
  {entry__8_22, NULL, 102, 102, 9, 39},
  {cont__8_24, &frame__8_22, 102, 102, 39, 39},
  {entry__8_25, NULL, 104, 104, 9, 39},
  {cont__8_27, &frame__8_25, 104, 104, 39, 39},
  {entry__8_32, NULL, 108, 108, 13, 45},
  {cont__8_34, &frame__8_32, 108, 108, 45, 45},
  {entry__8_35, NULL, 110, 110, 13, 44},
  {cont__8_37, &frame__8_35, 110, 110, 44, 44},
  {entry__8_28, NULL, 107, 107, 21, 38},
  {cont__8_29, &frame__8_28, 107, 107, 11, 39},
  {cont__8_30, &frame__8_28, 107, 107, 11, 44},
  {cont__8_31, &frame__8_28, 106, 110, 9, 45},
  {entry__8_38, NULL, 112, 112, 9, 45},
  {cont__8_40, &frame__8_38, 112, 112, 45, 45},
  {entry__8_41, NULL, 114, 114, 9, 46},
  {cont__8_43, &frame__8_41, 114, 114, 46, 46},
  {entry__8_44, NULL, 116, 116, 9, 42},
  {cont__8_46, &frame__8_44, 116, 116, 42, 42},
  {entry__8_47, NULL, 118, 118, 9, 42},
  {cont__8_49, &frame__8_47, 118, 118, 42, 42},
  {entry__8_50, NULL, 120, 120, 9, 41},
  {cont__8_52, &frame__8_50, 120, 120, 41, 41},
  {entry__8_53, NULL, 122, 122, 9, 39},
  {cont__8_55, &frame__8_53, 123, 123, 15, 31},
  {cont__8_56, &frame__8_53, 123, 123, 15, 34},
  {cont__8_57, &frame__8_53, 123, 123, 37, 53},
  {cont__8_58, &frame__8_53, 123, 123, 37, 56},
  {cont__8_59, &frame__8_53, 123, 123, 9, 56},
  {cont__8_60, &frame__8_53, 123, 123, 15, 31},
  {cont__8_61, &frame__8_53, 123, 123, 14, 34},
  {cont__8_62, &frame__8_53, 123, 123, 37, 53},
  {cont__8_63, &frame__8_53, 123, 123, 36, 56},
  {cont__8_64, &frame__8_53, 124, 124, 27, 27},
  {entry__8_65, NULL, 126, 126, 9, 39},
  {cont__8_67, &frame__8_65, 126, 126, 39, 39},
  {entry__8_68, NULL, 128, 128, 9, 39},
  {cont__8_70, &frame__8_68, 129, 129, 27, 27},
  {entry__8_71, NULL, 131, 131, 9, 39},
  {cont__8_73, &frame__8_71, 132, 132, 15, 31},
  {cont__8_74, &frame__8_71, 132, 132, 15, 34},
  {cont__8_75, &frame__8_71, 132, 132, 37, 53},
  {cont__8_76, &frame__8_71, 132, 132, 37, 56},
  {cont__8_77, &frame__8_71, 132, 132, 9, 56},
  {cont__8_78, &frame__8_71, 132, 132, 15, 31},
  {cont__8_79, &frame__8_71, 132, 132, 14, 34},
  {cont__8_80, &frame__8_71, 132, 132, 37, 53},
  {cont__8_81, &frame__8_71, 132, 132, 36, 56},
  {cont__8_82, &frame__8_71, 132, 132, 56, 56},
  {entry__8_83, NULL, 134, 134, 9, 40},
  {cont__8_85, &frame__8_83, 134, 134, 40, 40},
  {entry__8_86, NULL, 136, 136, 9, 40},
  {cont__8_88, &frame__8_86, 137, 137, 27, 27},
  {entry__8_89, NULL, 139, 139, 9, 38},
  {cont__8_91, &frame__8_89, 140, 140, 9, 32},
  {entry__8_92, NULL, 142, 142, 9, 37},
  {cont__8_94, &frame__8_92, 143, 143, 9, 32},
  {entry__8_95, NULL, 145, 145, 9, 46},
  {cont__8_97, &frame__8_95, 145, 145, 46, 46},
  {entry__8_98, NULL, 147, 147, 9, 49},
  {cont__8_100, &frame__8_98, 147, 147, 49, 49},
  {entry__8_121, NULL, 152, 152, 23, 43},
  {cont__8_123, &frame__8_121, 153, 153, 25, 34},
  {cont__8_124, &frame__8_121, 154, 154, 24, 40},
  {cont__8_125, &frame__8_121, 155, 155, 31, 54},
  {cont__8_126, &frame__8_121, 156, 156, 28, 48},
  {cont__8_127, &frame__8_121, 156, 156, 50, 50},
  {entry__8_17, NULL, 98, 98, 7, 22},
  {cont__8_18, &frame__8_17, 97, 147, 5, 50},
  {cont__8_120, &frame__8_17, 149, 156, 5, 50},
  {entry__8_1, NULL, 94, 94, 3, 28},
  {cont__8_15, &frame__8_1, 95, 95, 6, 34},
  {cont__8_16, &frame__8_1, 95, 156, 3, 51},
  {cont__8_128, &frame__8_1, },
  {entry__9_11, NULL, 167, 167, 40, 55},
  {cont__9_12, &frame__9_11, 167, 167, 40, 62},
  {cont__9_14, &frame__9_11, 167, 167, 40, 62},
  {entry__9_24, NULL, 170, 170, 54, 70},
  {cont__9_25, &frame__9_24, 170, 170, 46, 71},
  {cont__9_26, &frame__9_24, 170, 170, 46, 78},
  {cont__9_28, &frame__9_24, 170, 170, 46, 78},
  {entry__9_30, NULL, 171, 171, 11, 46},
  {cont__9_31, &frame__9_30, 172, 172, 27, 44},
  {cont__9_32, &frame__9_30, 172, 172, 11, 44},
  {cont__9_33, &frame__9_30, 173, 173, 11, 35},
  {cont__9_34, &frame__9_30, 173, 173, 35, 35},
  {entry__9_22, NULL, 170, 170, 18, 41},
  {cont__9_23, &frame__9_22, 170, 170, 18, 78},
  {cont__9_29, &frame__9_22, 170, 173, 15, 35},
  {entry__9_16, NULL, 168, 168, 26, 43},
  {cont__9_17, &frame__9_16, 168, 168, 26, 46},
  {cont__9_18, &frame__9_16, 168, 168, 9, 47},
  {cont__9_19, &frame__9_16, 169, 169, 17, 34},
  {cont__9_20, &frame__9_16, 169, 169, 9, 37},
  {cont__9_21, &frame__9_16, 170, 173, 9, 35},
  {cont__9_35, &frame__9_16, 174, 174, 9, 29},
  {cont__9_36, &frame__9_16, 175, 175, 9, 51},
  {cont__9_38, &frame__9_16, 176, 176, 9, 54},
  {cont__9_39, &frame__9_16, 176, 176, 54, 54},
  {entry__9_40, NULL, 178, 178, 27, 43},
  {cont__9_41, &frame__9_40, 178, 178, 9, 43},
  {cont__9_42, &frame__9_40, 179, 179, 9, 34},
  {cont__9_43, &frame__9_40, 179, 179, 34, 34},
  {entry__9_6, NULL, 164, 164, 24, 38},
  {cont__9_7, &frame__9_6, 164, 164, 5, 38},
  {cont__9_8, &frame__9_6, 165, 165, 5, 29},
  {cont__9_9, &frame__9_6, 167, 167, 7, 35},
  {cont__9_10, &frame__9_6, 167, 167, 7, 62},
  {cont__9_15, &frame__9_6, 166, 179, 5, 35},
  {entry__9_1, NULL, 159, 159, 3, 49},
  {cont__9_3, &frame__9_1, 163, 163, 6, 21},
  {cont__9_4, &frame__9_1, 163, 163, 6, 32},
  {cont__9_5, &frame__9_1, 163, 179, 3, 36},
  {cont__9_44, &frame__9_1, },
  {entry__10_1, NULL, 185, 185, 3, 56},
  {cont__10_3, &frame__10_1, 186, 186, 21, 37},
  {cont__10_4, &frame__10_1, 186, 186, 3, 37},
  {cont__10_5, &frame__10_1, 186, 186, 37, 37},
  {entry__11_1, NULL, 192, 192, 3, 59},
  {cont__11_3, &frame__11_1, 193, 193, 21, 37},
  {cont__11_4, &frame__11_1, 193, 193, 3, 37},
  {cont__11_5, &frame__11_1, 193, 193, 37, 37}
};

union NODE {
  struct {
    FUNC type;
    ATTRIBUTES *attributes;
  };
  CONTINUATION continuation;
  CLOSURE closure;
};
static void type__sim2c__expand_statement(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__sim2c__expand_statement);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__sim2c__expand_statement, attr);
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
static void type__sim2c__expand_expression(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__sim2c__expand_expression);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__sim2c__expand_expression, attr);
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
  "sim2c",
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
static void entry__3_1(void) {
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
  frame->slots[2] /* temp__1 */ = create_closure(entry__3_2, 1);
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
  frame->cont = cont__3_13;
}
static void entry__3_4(void) {
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
  frame->cont = cont__3_5;
}
static void cont__3_5(void) {
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
  frame->cont = cont__3_6;
}
static void cont__3_6(void) {
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
  frame->cont = cont__3_7;
}
static void cont__3_7(void) {
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
  frame->cont = cont__3_8;
}
static void cont__3_8(void) {
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
  frame->cont = cont__3_9;
}
static void cont__3_9(void) {
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
static void entry__3_10(void) {
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
  frame->cont = cont__3_11;
}
static void cont__3_11(void) {
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
  frame->cont = cont__3_12;
}
static void cont__3_12(void) {
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
static void entry__3_2(void) {
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
  frame->cont = cont__3_3;
}
static void cont__3_3(void) {
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
  frame->slots[3] /* temp__2 */ = create_closure(entry__3_4, 0);
  // 41: :
  // 42:   push &new_arguments expand_expression(argument)
  frame->slots[4] /* temp__3 */ = create_closure(entry__3_10, 0);
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
static void cont__3_13(void) {
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
static void entry__4_1(void) {
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
  arguments->slots[0] = string__4_2;
  result_count =
    frame->caller_result_count >= 1 ?
    frame->caller_result_count-1 : -1;
  myself = get__show_compiler_debug_info();
  func = myself->type;
  frame->cont = cont__4_3;
}
static void cont__4_3(void) {
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
static void entry__5_1(void) {
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
  arguments->slots[0] = string__5_2;
  result_count =
    frame->caller_result_count >= 1 ?
    frame->caller_result_count-1 : -1;
  myself = get__show_compiler_debug_info();
  func = myself->type;
  frame->cont = cont__5_3;
}
static void cont__5_3(void) {
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
static void entry__6_1(void) {
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
  arguments->slots[0] = string__6_2;
  result_count = 0;
  myself = get__show_compiler_debug_info();
  func = myself->type;
  frame->cont = cont__6_3;
}
static void cont__6_3(void) {
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
  frame->cont = cont__6_4;
}
static void cont__6_4(void) {
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
  arguments->slots[1] = func__6_5;
  result_count = 1;
  myself = get__update_each();
  func = myself->type;
  frame->cont = cont__6_12;
}
static void entry__6_5(void) {
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
  frame->cont = cont__6_6;
}
static void cont__6_6(void) {
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
  frame->cont = cont__6_7;
}
static void cont__6_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 60: ... :
  // 61:   expand_expression &parameter.default_value_of
  frame->slots[3] /* temp__3 */ = create_closure(entry__6_8, 0);
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
  frame->cont = cont__6_11;
}
static void entry__6_8(void) {
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
  frame->cont = cont__6_9;
}
static void cont__6_9(void) {
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
  frame->cont = cont__6_10;
}
static void cont__6_10(void) {
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
static void cont__6_11(void) {
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
static void cont__6_12(void) {
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
  frame->cont = cont__6_13;
}
static void cont__6_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 62: update_each &self.statements_of: (&stmt) expand_statement &stmt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = func__6_14;
  result_count = 1;
  myself = get__update_each();
  func = myself->type;
  frame->cont = cont__6_16;
}
static void entry__6_14(void) {
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
  frame->cont = cont__6_15;
}
static void cont__6_15(void) {
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
static void cont__6_16(void) {
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
static void entry__7_1(void) {
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
  arguments->slots[0] = string__7_2;
  result_count = 0;
  myself = get__show_compiler_debug_info();
  func = myself->type;
  frame->cont = cont__7_3;
}
static void cont__7_3(void) {
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
  frame->cont = cont__7_4;
}
static void cont__7_4(void) {
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
  frame->cont = cont__7_5;
}
static void cont__7_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 69: ... :
  // 70:   if result_count_of(self).is_defined: expand_expression &self.result_count_of
  // 71:   expand_expression &self.functor_of
  frame->slots[3] /* temp__3 */ = create_closure(entry__7_6, 0);
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
  frame->cont = cont__7_15;
}
static void entry__7_6(void) {
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
  frame->cont = cont__7_7;
}
static void cont__7_7(void) {
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
  frame->cont = cont__7_8;
}
static void cont__7_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 70: ... : expand_expression &self.result_count_of
  frame->slots[3] /* temp__3 */ = create_closure(entry__7_9, 0);
  // 70: if result_count_of(self).is_defined: expand_expression &self.result_count_of
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__7_12;
}
static void entry__7_9(void) {
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
  frame->cont = cont__7_10;
}
static void cont__7_10(void) {
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
  frame->cont = cont__7_11;
}
static void cont__7_11(void) {
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
static void cont__7_12(void) {
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
  frame->cont = cont__7_13;
}
static void cont__7_13(void) {
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
  frame->cont = cont__7_14;
}
static void cont__7_14(void) {
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
static void cont__7_15(void) {
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
  frame->cont = cont__7_16;
}
static void cont__7_16(void) {
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
  frame->cont = cont__7_17;
}
static void cont__7_17(void) {
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
  // 73: ... self.output_arguments_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__output_arguments_of();
  func = myself->type;
  frame->cont = cont__7_18;
}
static void cont__7_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 73: expand_arguments &self.output_arguments_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = var._expand_arguments;
  func = myself->type;
  frame->cont = cont__7_19;
}
static void cont__7_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 73: ... &self.output_arguments_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__output_arguments_of, frame->slots[2] /* temp__2 */);
    ((CELL *)frame->slots[0])->contents /* self */ = temp;

  }
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__8_1(void) {
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
  // 79: ... :
  // 80:   $right arguments_of(self)(2)
  // 81:   !self.arguments_of(2)
  // 82:     body
  // 83:       .statements_of
  // 84:         list
  // 85:           return_statement
  // 86:             .arguments_of list(right)
  // 87:             .fragment_of fragment_of(right)
  // 88:             .source_position_of source_position_of(right)
  // ...
  frame->slots[3] /* temp__1 */ = create_closure(entry__8_2, 0);
  // 79: $make_right_argument_lazy:
  // 80:   $right arguments_of(self)(2)
  // 81:   !self.arguments_of(2)
  // 82:     body
  // 83:       .statements_of
  // 84:         list
  // 85:           return_statement
  // 86:             .arguments_of list(right)
  // 87:             .fragment_of fragment_of(right)
  // 88:             .source_position_of source_position_of(right)
  // ...
  initialize_future(frame->slots[1] /* make_right_argument_lazy */, frame->slots[3] /* temp__1 */);
  // 94: $$functor functor_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__functor_of();
  func = myself->type;
  frame->cont = cont__8_15;
}
static void entry__8_2(void) {
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
  // 80: ... arguments_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__8_3;
}
static void cont__8_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 80: $right arguments_of(self)(2)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = frame->slots[2] /* temp__1 */;
  func = myself->type;
  frame->cont = cont__8_4;
}
static void cont__8_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* right */, arguments->slots[0]);
  // 86: ... list(right)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* right */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__8_5;
}
static void cont__8_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 87: ... fragment_of(right)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* right */;
  result_count = 1;
  myself = get__fragment_of();
  func = myself->type;
  frame->cont = cont__8_6;
}
static void cont__8_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__4 */ = arguments->slots[0];
  // 88: ... source_position_of(right)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* right */;
  result_count = 1;
  myself = get__source_position_of();
  func = myself->type;
  frame->cont = cont__8_7;
}
static void cont__8_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__5 */ = arguments->slots[0];
  // 89: ... end_position_of(right)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* right */;
  result_count = 1;
  myself = get__end_position_of();
  func = myself->type;
  frame->cont = cont__8_8;
}
static void cont__8_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__6 */ = arguments->slots[0];
  // 85: return_statement
  // 86:   .arguments_of list(right)
  // 87:   .fragment_of fragment_of(right)
  // 88:   .source_position_of source_position_of(right)
  // 89:   .end_position_of end_position_of(right)
  {
    NODE *temp = clone_object_and_attributes(get__return_statement());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[4] /* temp__3 */);
    set_attribute_value(temp->attributes, poly_idx__fragment_of, frame->slots[5] /* temp__4 */);
    set_attribute_value(temp->attributes, poly_idx__source_position_of, frame->slots[6] /* temp__5 */);
    set_attribute_value(temp->attributes, poly_idx__end_position_of, frame->slots[7] /* temp__6 */);
    frame->slots[3] /* temp__2 */ = temp;

  }
  // 84: list
  // 85:   return_statement
  // 86:     .arguments_of list(right)
  // 87:     .fragment_of fragment_of(right)
  // 88:     .source_position_of source_position_of(right)
  // 89:     .end_position_of end_position_of(right)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__8_9;
}
static void cont__8_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 90: ... fragment_of(right)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* right */;
  result_count = 1;
  myself = get__fragment_of();
  func = myself->type;
  frame->cont = cont__8_10;
}
static void cont__8_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__7 */ = arguments->slots[0];
  // 91: ... source_position_of(right)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* right */;
  result_count = 1;
  myself = get__source_position_of();
  func = myself->type;
  frame->cont = cont__8_11;
}
static void cont__8_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__8 */ = arguments->slots[0];
  // 92: ... end_position_of(right)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* right */;
  result_count = 1;
  myself = get__end_position_of();
  func = myself->type;
  frame->cont = cont__8_12;
}
static void cont__8_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__9 */ = arguments->slots[0];
  // 81: !self.arguments_of(2)
  // 82:   body
  // 83:     .statements_of
  // 84:       list
  // 85:         return_statement
  // 86:           .arguments_of list(right)
  // 87:           .fragment_of fragment_of(right)
  // 88:           .source_position_of source_position_of(right)
  // 89:           .end_position_of end_position_of(right)
  // 90:     .fragment_of fragment_of(right)
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
  // 81: ... self.arguments_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__8_13;
}
static void cont__8_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__11 */ = arguments->slots[0];
  // 81: !self.arguments_of(2)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__2;
  arguments->slots[1] = frame->slots[11] /* temp__10 */;
  result_count = 1;
  myself = frame->slots[12] /* temp__11 */;
  func = myself->type;
  frame->cont = cont__8_14;
}
static void cont__8_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__11 */ = arguments->slots[0];
  // 81: !self.arguments_of
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
static void cont__8_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* functor */ = arguments->slots[0];
  // 95: ... functor.is_an_operator_symbol
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* functor */;
  result_count = 1;
  myself = get__is_an_operator_symbol();
  func = myself->type;
  frame->cont = cont__8_16;
}
static void cont__8_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  //  95: ... :
  //  96:   $$do_insert_not false
  //  97:   case
  //  98:     name_of(functor)
  //  99:     "*":
  // 100:       !functor std_identifier("times")
  // 101:     "/":
  // 102:       !functor std_identifier("over")
  // 103:     "+":
  // 104:       !functor std_identifier("plus")
  // ...
  frame->slots[4] /* temp__2 */ = create_closure(entry__8_17, 0);
  //  95: if functor.is_an_operator_symbol:
  //  96:   $$do_insert_not false
  //  97:   case
  //  98:     name_of(functor)
  //  99:     "*":
  // 100:       !functor std_identifier("times")
  // 101:     "/":
  // 102:       !functor std_identifier("over")
  // 103:     "+":
  // 104:       !functor std_identifier("plus")
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
  frame->cont = cont__8_128;
}
static void entry__8_121(void) {
  allocate_initialized_frame_gc(1, 6);
  // slot allocations:
  // self: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 152: ... std_identifier("not")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__8_122;
  result_count = 1;
  myself = get__std_identifier();
  func = myself->type;
  frame->cont = cont__8_123;
}
static void cont__8_123(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 153: ... list(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__8_124;
}
static void cont__8_124(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 154: ... fragment_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__fragment_of();
  func = myself->type;
  frame->cont = cont__8_125;
}
static void cont__8_125(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 155: ... source_position_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__source_position_of();
  func = myself->type;
  frame->cont = cont__8_126;
}
static void cont__8_126(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__4 */ = arguments->slots[0];
  // 156: ... end_position_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__end_position_of();
  func = myself->type;
  frame->cont = cont__8_127;
}
static void cont__8_127(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__5 */ = arguments->slots[0];
  // 150: !self
  // 151:   function_call
  // 152:     .functor_of std_identifier("not")
  // 153:     .arguments_of list(self)
  // 154:     .fragment_of fragment_of(self)
  // 155:     .source_position_of source_position_of(self)
  // 156:     .end_position_of end_position_of(self)
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
static void entry__8_17(void) {
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
  // 96: $$do_insert_not false
  ((CELL *)frame->slots[3])->contents /* do_insert_not */ = get__false();
  // 98: name_of(functor)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* functor */;
  result_count = 1;
  myself = get__name_of();
  func = myself->type;
  frame->cont = cont__8_18;
}
static void cont__8_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  //  99: ... :
  // 100:   !functor std_identifier("times")
  frame->slots[5] /* temp__2 */ = create_closure(entry__8_19, 0);
  // 101: ... :
  // 102:   !functor std_identifier("over")
  frame->slots[6] /* temp__3 */ = create_closure(entry__8_22, 0);
  // 103: ... :
  // 104:   !functor std_identifier("plus")
  frame->slots[7] /* temp__4 */ = create_closure(entry__8_25, 0);
  // 105: ... :
  // 106:   if
  // 107:     length_of(arguments_of(self)) == 1:
  // 108:       !functor std_identifier("negate")
  // 109:     :
  // 110:       !functor std_identifier("minus")
  frame->slots[8] /* temp__5 */ = create_closure(entry__8_28, 0);
  // 111: ... :
  // 112:   !functor std_identifier("shift_left")
  frame->slots[9] /* temp__6 */ = create_closure(entry__8_38, 0);
  // 113: ... :
  // 114:   !functor std_identifier("shift_right")
  frame->slots[10] /* temp__7 */ = create_closure(entry__8_41, 0);
  // 115: ... :
  // 116:   !functor std_identifier("bit_and")
  frame->slots[11] /* temp__8 */ = create_closure(entry__8_44, 0);
  // 117: ... :
  // 118:   !functor std_identifier("bit_xor")
  frame->slots[12] /* temp__9 */ = create_closure(entry__8_47, 0);
  // 119: ... :
  // 120:   !functor std_identifier("bit_or")
  frame->slots[13] /* temp__10 */ = create_closure(entry__8_50, 0);
  // 121: ... :
  // 122:   !functor std_identifier("less")
  // 123:   swap &self.arguments_of(1) &self.arguments_of(2)
  // 124:   !do_insert_not true
  frame->slots[14] /* temp__11 */ = create_closure(entry__8_53, 0);
  // 125: ... :
  // 126:   !functor std_identifier("less")
  frame->slots[15] /* temp__12 */ = create_closure(entry__8_65, 0);
  // 127: ... :
  // 128:   !functor std_identifier("less")
  // 129:   !do_insert_not true
  frame->slots[16] /* temp__13 */ = create_closure(entry__8_68, 0);
  // 130: ... :
  // 131:   !functor std_identifier("less")
  // 132:   swap &self.arguments_of(1) &self.arguments_of(2)
  frame->slots[17] /* temp__14 */ = create_closure(entry__8_71, 0);
  // 133: ... :
  // 134:   !functor std_identifier("equal")
  frame->slots[18] /* temp__15 */ = create_closure(entry__8_83, 0);
  // 135: ... :
  // 136:   !functor std_identifier("equal")
  // 137:   !do_insert_not true
  frame->slots[19] /* temp__16 */ = create_closure(entry__8_86, 0);
  // 138: ... :
  // 139:   !functor std_identifier("and")
  // 140:   make_right_argument_lazy
  frame->slots[20] /* temp__17 */ = create_closure(entry__8_89, 0);
  // 141: ... :
  // 142:   !functor std_identifier("or")
  // 143:   make_right_argument_lazy
  frame->slots[21] /* temp__18 */ = create_closure(entry__8_92, 0);
  // 144: ... :
  // 145:   !functor std_identifier("value_range")
  frame->slots[22] /* temp__19 */ = create_closure(entry__8_95, 0);
  // 146: ... :
  // 147:   !functor std_identifier("key_value_pair")
  frame->slots[23] /* temp__20 */ = create_closure(entry__8_98, 0);
  //  97: case
  //  98:   name_of(functor)
  //  99:   "*":
  // 100:     !functor std_identifier("times")
  // 101:   "/":
  // 102:     !functor std_identifier("over")
  // 103:   "+":
  // 104:     !functor std_identifier("plus")
  // 105:   "-":
  // 106:     if
  // ...
  argument_count = 39;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = string__8_101;
  arguments->slots[2] = frame->slots[5] /* temp__2 */;
  arguments->slots[3] = string__8_102;
  arguments->slots[4] = frame->slots[6] /* temp__3 */;
  arguments->slots[5] = string__8_103;
  arguments->slots[6] = frame->slots[7] /* temp__4 */;
  arguments->slots[7] = string__8_104;
  arguments->slots[8] = frame->slots[8] /* temp__5 */;
  arguments->slots[9] = string__8_105;
  arguments->slots[10] = frame->slots[9] /* temp__6 */;
  arguments->slots[11] = string__8_106;
  arguments->slots[12] = frame->slots[10] /* temp__7 */;
  arguments->slots[13] = string__8_107;
  arguments->slots[14] = frame->slots[11] /* temp__8 */;
  arguments->slots[15] = string__8_108;
  arguments->slots[16] = frame->slots[12] /* temp__9 */;
  arguments->slots[17] = string__8_109;
  arguments->slots[18] = frame->slots[13] /* temp__10 */;
  arguments->slots[19] = string__8_110;
  arguments->slots[20] = frame->slots[14] /* temp__11 */;
  arguments->slots[21] = string__8_111;
  arguments->slots[22] = frame->slots[15] /* temp__12 */;
  arguments->slots[23] = string__8_112;
  arguments->slots[24] = frame->slots[16] /* temp__13 */;
  arguments->slots[25] = string__8_113;
  arguments->slots[26] = frame->slots[17] /* temp__14 */;
  arguments->slots[27] = string__8_114;
  arguments->slots[28] = frame->slots[18] /* temp__15 */;
  arguments->slots[29] = string__8_115;
  arguments->slots[30] = frame->slots[19] /* temp__16 */;
  arguments->slots[31] = string__8_116;
  arguments->slots[32] = frame->slots[20] /* temp__17 */;
  arguments->slots[33] = string__8_117;
  arguments->slots[34] = frame->slots[21] /* temp__18 */;
  arguments->slots[35] = string__8_118;
  arguments->slots[36] = frame->slots[22] /* temp__19 */;
  arguments->slots[37] = string__8_119;
  arguments->slots[38] = frame->slots[23] /* temp__20 */;
  result_count = 0;
  myself = get__case();
  func = myself->type;
  frame->cont = cont__8_120;
}
static void entry__8_32(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // functor: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* functor */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 108: !functor std_identifier("negate")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__8_33;
  result_count = 1;
  myself = get__std_identifier();
  func = myself->type;
  frame->cont = cont__8_34;
}
static void cont__8_34(void) {
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
static void entry__8_35(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // functor: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* functor */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 110: !functor std_identifier("minus")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__8_36;
  result_count = 1;
  myself = get__std_identifier();
  func = myself->type;
  frame->cont = cont__8_37;
}
static void cont__8_37(void) {
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
static void entry__8_19(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // functor: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* functor */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 100: !functor std_identifier("times")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__8_20;
  result_count = 1;
  myself = get__std_identifier();
  func = myself->type;
  frame->cont = cont__8_21;
}
static void cont__8_21(void) {
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
static void entry__8_22(void) {
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
  arguments->slots[0] = string__8_23;
  result_count = 1;
  myself = get__std_identifier();
  func = myself->type;
  frame->cont = cont__8_24;
}
static void cont__8_24(void) {
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
static void entry__8_25(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // functor: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* functor */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 104: !functor std_identifier("plus")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__8_26;
  result_count = 1;
  myself = get__std_identifier();
  func = myself->type;
  frame->cont = cont__8_27;
}
static void cont__8_27(void) {
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
static void entry__8_28(void) {
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
  // 107: ... arguments_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__8_29;
}
static void cont__8_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 107: length_of(arguments_of(self))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__8_30;
}
static void cont__8_30(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 107: length_of(arguments_of(self)) == 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__8_31;
}
static void cont__8_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 107: ... :
  // 108:   !functor std_identifier("negate")
  frame->slots[5] /* temp__4 */ = create_closure(entry__8_32, 0);
  // 109: :
  // 110:   !functor std_identifier("minus")
  frame->slots[6] /* temp__5 */ = create_closure(entry__8_35, 0);
  // 106: if
  // 107:   length_of(arguments_of(self)) == 1:
  // 108:     !functor std_identifier("negate")
  // 109:   :
  // 110:     !functor std_identifier("minus")
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
static void entry__8_38(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // functor: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* functor */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 112: !functor std_identifier("shift_left")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__8_39;
  result_count = 1;
  myself = get__std_identifier();
  func = myself->type;
  frame->cont = cont__8_40;
}
static void cont__8_40(void) {
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
static void entry__8_41(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // functor: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* functor */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 114: !functor std_identifier("shift_right")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__8_42;
  result_count = 1;
  myself = get__std_identifier();
  func = myself->type;
  frame->cont = cont__8_43;
}
static void cont__8_43(void) {
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
static void entry__8_44(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // functor: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* functor */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 116: !functor std_identifier("bit_and")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__8_45;
  result_count = 1;
  myself = get__std_identifier();
  func = myself->type;
  frame->cont = cont__8_46;
}
static void cont__8_46(void) {
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
static void entry__8_47(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // functor: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* functor */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 118: !functor std_identifier("bit_xor")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__8_48;
  result_count = 1;
  myself = get__std_identifier();
  func = myself->type;
  frame->cont = cont__8_49;
}
static void cont__8_49(void) {
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
static void entry__8_50(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // functor: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* functor */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 120: !functor std_identifier("bit_or")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__8_51;
  result_count = 1;
  myself = get__std_identifier();
  func = myself->type;
  frame->cont = cont__8_52;
}
static void cont__8_52(void) {
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
static void entry__8_53(void) {
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
  // 122: !functor std_identifier("less")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__8_54;
  result_count = 1;
  myself = get__std_identifier();
  func = myself->type;
  frame->cont = cont__8_55;
}
static void cont__8_55(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* functor */ = arguments->slots[0];
  // 123: ... self.arguments_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* self */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__8_56;
}
static void cont__8_56(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 123: ... self.arguments_of(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[4] /* temp__2 */;
  func = myself->type;
  frame->cont = cont__8_57;
}
static void cont__8_57(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 123: ... self.arguments_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* self */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__8_58;
}
static void cont__8_58(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__4 */ = arguments->slots[0];
  // 123: ... self.arguments_of(2)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = frame->slots[6] /* temp__4 */;
  func = myself->type;
  frame->cont = cont__8_59;
}
static void cont__8_59(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 123: swap &self.arguments_of(1) &self.arguments_of(2)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 2;
  myself = get__swap();
  func = myself->type;
  frame->cont = cont__8_60;
}
static void cont__8_60(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__5 */ = arguments->slots[0];
  frame->slots[8] /* temp__6 */ = arguments->slots[1];
  // 123: ... self.arguments_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* self */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__8_61;
}
static void cont__8_61(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__7 */ = arguments->slots[0];
  // 123: ... &self.arguments_of(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__1;
  arguments->slots[1] = frame->slots[7] /* temp__5 */;
  result_count = 1;
  myself = frame->slots[9] /* temp__7 */;
  func = myself->type;
  frame->cont = cont__8_62;
}
static void cont__8_62(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__7 */ = arguments->slots[0];
  // 123: ... &self.arguments_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[1])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[9] /* temp__7 */);
    ((CELL *)frame->slots[1])->contents /* self */ = temp;

  }
  // 123: ... self.arguments_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* self */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__8_63;
}
static void cont__8_63(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__8 */ = arguments->slots[0];
  // 123: ... &self.arguments_of(2)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__2;
  arguments->slots[1] = frame->slots[8] /* temp__6 */;
  result_count = 1;
  myself = frame->slots[10] /* temp__8 */;
  func = myself->type;
  frame->cont = cont__8_64;
}
static void cont__8_64(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__8 */ = arguments->slots[0];
  // 123: ... &self.arguments_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[1])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[10] /* temp__8 */);
    ((CELL *)frame->slots[1])->contents /* self */ = temp;

  }
  // 124: !do_insert_not true
  ((CELL *)frame->slots[2])->contents /* do_insert_not */ = get__true();
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__8_65(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // functor: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* functor */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 126: !functor std_identifier("less")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__8_66;
  result_count = 1;
  myself = get__std_identifier();
  func = myself->type;
  frame->cont = cont__8_67;
}
static void cont__8_67(void) {
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
static void entry__8_68(void) {
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
  // 128: !functor std_identifier("less")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__8_69;
  result_count = 1;
  myself = get__std_identifier();
  func = myself->type;
  frame->cont = cont__8_70;
}
static void cont__8_70(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* functor */ = arguments->slots[0];
  // 129: !do_insert_not true
  ((CELL *)frame->slots[1])->contents /* do_insert_not */ = get__true();
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__8_71(void) {
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
  // 131: !functor std_identifier("less")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__8_72;
  result_count = 1;
  myself = get__std_identifier();
  func = myself->type;
  frame->cont = cont__8_73;
}
static void cont__8_73(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* functor */ = arguments->slots[0];
  // 132: ... self.arguments_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* self */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__8_74;
}
static void cont__8_74(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 132: ... self.arguments_of(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[3] /* temp__2 */;
  func = myself->type;
  frame->cont = cont__8_75;
}
static void cont__8_75(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 132: ... self.arguments_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* self */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__8_76;
}
static void cont__8_76(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__4 */ = arguments->slots[0];
  // 132: ... self.arguments_of(2)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = frame->slots[5] /* temp__4 */;
  func = myself->type;
  frame->cont = cont__8_77;
}
static void cont__8_77(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 132: swap &self.arguments_of(1) &self.arguments_of(2)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 2;
  myself = get__swap();
  func = myself->type;
  frame->cont = cont__8_78;
}
static void cont__8_78(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__5 */ = arguments->slots[0];
  frame->slots[7] /* temp__6 */ = arguments->slots[1];
  // 132: ... self.arguments_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* self */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__8_79;
}
static void cont__8_79(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__7 */ = arguments->slots[0];
  // 132: ... &self.arguments_of(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__1;
  arguments->slots[1] = frame->slots[6] /* temp__5 */;
  result_count = 1;
  myself = frame->slots[8] /* temp__7 */;
  func = myself->type;
  frame->cont = cont__8_80;
}
static void cont__8_80(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__7 */ = arguments->slots[0];
  // 132: ... &self.arguments_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[1])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[8] /* temp__7 */);
    ((CELL *)frame->slots[1])->contents /* self */ = temp;

  }
  // 132: ... self.arguments_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* self */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__8_81;
}
static void cont__8_81(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__8 */ = arguments->slots[0];
  // 132: ... &self.arguments_of(2)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__2;
  arguments->slots[1] = frame->slots[7] /* temp__6 */;
  result_count = 1;
  myself = frame->slots[9] /* temp__8 */;
  func = myself->type;
  frame->cont = cont__8_82;
}
static void cont__8_82(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__8 */ = arguments->slots[0];
  // 132: ... &self.arguments_of
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
static void entry__8_83(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // functor: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* functor */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 134: !functor std_identifier("equal")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__8_84;
  result_count = 1;
  myself = get__std_identifier();
  func = myself->type;
  frame->cont = cont__8_85;
}
static void cont__8_85(void) {
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
static void entry__8_86(void) {
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
  // 136: !functor std_identifier("equal")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__8_87;
  result_count = 1;
  myself = get__std_identifier();
  func = myself->type;
  frame->cont = cont__8_88;
}
static void cont__8_88(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* functor */ = arguments->slots[0];
  // 137: !do_insert_not true
  ((CELL *)frame->slots[1])->contents /* do_insert_not */ = get__true();
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__8_89(void) {
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
  // 139: !functor std_identifier("and")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__8_90;
  result_count = 1;
  myself = get__std_identifier();
  func = myself->type;
  frame->cont = cont__8_91;
}
static void cont__8_91(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* functor */ = arguments->slots[0];
  // 140: make_right_argument_lazy
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* make_right_argument_lazy */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__8_92(void) {
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
  // 142: !functor std_identifier("or")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__8_93;
  result_count = 1;
  myself = get__std_identifier();
  func = myself->type;
  frame->cont = cont__8_94;
}
static void cont__8_94(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* functor */ = arguments->slots[0];
  // 143: make_right_argument_lazy
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* make_right_argument_lazy */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__8_95(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // functor: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* functor */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 145: !functor std_identifier("value_range")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__8_96;
  result_count = 1;
  myself = get__std_identifier();
  func = myself->type;
  frame->cont = cont__8_97;
}
static void cont__8_97(void) {
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
static void entry__8_98(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // functor: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* functor */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 147: !functor std_identifier("key_value_pair")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__8_99;
  result_count = 1;
  myself = get__std_identifier();
  func = myself->type;
  frame->cont = cont__8_100;
}
static void cont__8_100(void) {
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
static void cont__8_120(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 148: !self.functor_of functor
  frame->slots[4] /* temp__1 */ = ((CELL *)frame->slots[0])->contents /* functor */;
  // 148: !self.functor_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[1])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__functor_of, frame->slots[4] /* temp__1 */);
    ((CELL *)frame->slots[1])->contents /* self */ = temp;

  }
  // 149: ... :
  // 150:   !self
  // 151:     function_call
  // 152:       .functor_of std_identifier("not")
  // 153:       .arguments_of list(self)
  // 154:       .fragment_of fragment_of(self)
  // 155:       .source_position_of source_position_of(self)
  // 156:       .end_position_of end_position_of(self)
  frame->slots[4] /* temp__1 */ = create_closure(entry__8_121, 0);
  // 149: if do_insert_not:
  // 150:   !self
  // 151:     function_call
  // 152:       .functor_of std_identifier("not")
  // 153:       .arguments_of list(self)
  // 154:       .fragment_of fragment_of(self)
  // 155:       .source_position_of source_position_of(self)
  // 156:       .end_position_of end_position_of(self)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* do_insert_not */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__8_128(void) {
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
static void entry__9_1(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // self: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* self */ = create_cell_with_contents(arguments->slots[0]);
  // 159: show_compiler_debug_info "expand function call"
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
  // 163: ... functor_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__functor_of();
  func = myself->type;
  frame->cont = cont__9_4;
}
static void cont__9_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 163: ... functor_of(self).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__9_5;
}
static void cont__9_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 163: ... :
  // 164:   expand_expression &self.functor_of
  // 165:   $functor functor_of(self)
  // 166:   if
  // 167:     functor.is_an_operator_symbol && name_of(functor) == ",":
  // 168:       $$arguments list(arguments_of(self)(1))
  // 169:       $$right arguments_of(self)(2)
  // 170:       while -> right.is_a_function_call && name_of(functor_of(right)) == ",":
  // 171:         $right_arguments arguments_of(right)
  // 172:         push &arguments right_arguments(1)
  // ...
  frame->slots[3] /* temp__3 */ = create_closure(entry__9_6, 0);
  // 163: if functor_of(self).is_defined:
  // 164:   expand_expression &self.functor_of
  // 165:   $functor functor_of(self)
  // 166:   if
  // 167:     functor.is_an_operator_symbol && name_of(functor) == ",":
  // 168:       $$arguments list(arguments_of(self)(1))
  // 169:       $$right arguments_of(self)(2)
  // 170:       while -> right.is_a_function_call && name_of(functor_of(right)) == ",":
  // 171:         $right_arguments arguments_of(right)
  // 172:         push &arguments right_arguments(1)
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
  frame->cont = cont__9_44;
}
static void entry__9_16(void) {
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
  // 168: ... arguments_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__9_17;
}
static void cont__9_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 168: ... arguments_of(self)(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[4] /* temp__2 */;
  func = myself->type;
  frame->cont = cont__9_18;
}
static void cont__9_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 168: $$arguments list(arguments_of(self)(1))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__9_19;
}
static void cont__9_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* arguments */ = arguments->slots[0];
  // 169: ... arguments_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__9_20;
}
static void cont__9_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 169: $$right arguments_of(self)(2)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = frame->slots[3] /* temp__1 */;
  func = myself->type;
  frame->cont = cont__9_21;
}
static void cont__9_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* right */ = arguments->slots[0];
  // 170: ... -> right.is_a_function_call && name_of(functor_of(right)) == ",":
  // 171:   $right_arguments arguments_of(right)
  // 172:   push &arguments right_arguments(1)
  // 173:   !right right_arguments(2)
  frame->slots[3] /* temp__1 */ = create_closure(entry__9_22, 0);
  // 170: while -> right.is_a_function_call && name_of(functor_of(right)) == ",":
  // 171:   $right_arguments arguments_of(right)
  // 172:   push &arguments right_arguments(1)
  // 173:   !right right_arguments(2)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = 0;
  myself = get__while();
  func = myself->type;
  frame->cont = cont__9_35;
}
static void entry__9_30(void) {
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
  // 171: $right_arguments arguments_of(right)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* right */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__9_31;
}
static void cont__9_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* right_arguments */, arguments->slots[0]);
  // 172: ... right_arguments(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[2] /* right_arguments */;
  func = myself->type;
  frame->cont = cont__9_32;
}
static void cont__9_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 172: push &arguments right_arguments(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* arguments */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__9_33;
}
static void cont__9_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* arguments */ = arguments->slots[0];
  // 173: !right right_arguments(2)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = frame->slots[2] /* right_arguments */;
  func = myself->type;
  frame->cont = cont__9_34;
}
static void cont__9_34(void) {
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
static void entry__9_22(void) {
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
  // 170: ... right.is_a_function_call
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* right */;
  result_count = 1;
  myself = get__is_a_function_call();
  func = myself->type;
  frame->cont = cont__9_23;
}
static void cont__9_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 170: ... name_of(functor_of(right)) == ","
  frame->slots[4] /* temp__3 */ = create_closure(entry__9_24, 0);
  // 170: ... right.is_a_function_call && name_of(functor_of(right)) == ","
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__9_29;
}
static void entry__9_24(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // right: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* right */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 170: ... functor_of(right)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* right */;
  result_count = 1;
  myself = get__functor_of();
  func = myself->type;
  frame->cont = cont__9_25;
}
static void cont__9_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 170: ... name_of(functor_of(right))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__name_of();
  func = myself->type;
  frame->cont = cont__9_26;
}
static void cont__9_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 170: ... name_of(functor_of(right)) == ","
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = string__9_27;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__9_28;
}
static void cont__9_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 170: ... name_of(functor_of(right)) == ","
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__9_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 170: ... :
  // 171:   $right_arguments arguments_of(right)
  // 172:   push &arguments right_arguments(1)
  // 173:   !right right_arguments(2)
  frame->slots[5] /* temp__4 */ = create_closure(entry__9_30, 0);
  // 170: ... -> right.is_a_function_call && name_of(functor_of(right)) == ",":
  // 171:   $right_arguments arguments_of(right)
  // 172:   push &arguments right_arguments(1)
  // 173:   !right right_arguments(2)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__4 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__9_35(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 174: push &arguments right
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* arguments */;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* right */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__9_36;
}
static void cont__9_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* arguments */ = arguments->slots[0];
  // 175: !self.functor_of std_identifier("sequence")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__9_37;
  result_count = 1;
  myself = get__std_identifier();
  func = myself->type;
  frame->cont = cont__9_38;
}
static void cont__9_38(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 175: !self.functor_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__functor_of, frame->slots[3] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* self */ = temp;

  }
  // 176: !self.arguments_of expand_arguments(arguments)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* arguments */;
  result_count = 1;
  myself = var._expand_arguments;
  func = myself->type;
  frame->cont = cont__9_39;
}
static void cont__9_39(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 176: !self.arguments_of
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
static void entry__9_40(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // self: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 178: ... self.arguments_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__9_41;
}
static void cont__9_41(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 178: expand_arguments &self.arguments_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = var._expand_arguments;
  func = myself->type;
  frame->cont = cont__9_42;
}
static void cont__9_42(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 178: ... &self.arguments_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[2] /* temp__2 */);
    ((CELL *)frame->slots[0])->contents /* self */ = temp;

  }
  // 179: expand_operator_call &self
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__expand_operator_call();
  func = myself->type;
  frame->cont = cont__9_43;
}
static void cont__9_43(void) {
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
static void entry__9_6(void) {
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
  // 164: ... self.functor_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__functor_of();
  func = myself->type;
  frame->cont = cont__9_7;
}
static void cont__9_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 164: expand_expression &self.functor_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__expand_expression();
  func = myself->type;
  frame->cont = cont__9_8;
}
static void cont__9_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 164: ... &self.functor_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__functor_of, frame->slots[3] /* temp__2 */);
    ((CELL *)frame->slots[0])->contents /* self */ = temp;

  }
  // 165: $functor functor_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__functor_of();
  func = myself->type;
  frame->cont = cont__9_9;
}
static void cont__9_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* functor */, arguments->slots[0]);
  // 167: functor.is_an_operator_symbol
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* functor */;
  result_count = 1;
  myself = get__is_an_operator_symbol();
  func = myself->type;
  frame->cont = cont__9_10;
}
static void cont__9_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 167: ... name_of(functor) == ","
  frame->slots[4] /* temp__3 */ = create_closure(entry__9_11, 0);
  // 167: functor.is_an_operator_symbol && name_of(functor) == ","
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__9_15;
}
static void entry__9_11(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // functor: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* functor */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 167: ... name_of(functor)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* functor */;
  result_count = 1;
  myself = get__name_of();
  func = myself->type;
  frame->cont = cont__9_12;
}
static void cont__9_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 167: ... name_of(functor) == ","
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = string__9_13;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__9_14;
}
static void cont__9_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 167: ... name_of(functor) == ","
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__9_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 167: ... :
  // 168:   $$arguments list(arguments_of(self)(1))
  // 169:   $$right arguments_of(self)(2)
  // 170:   while -> right.is_a_function_call && name_of(functor_of(right)) == ",":
  // 171:     $right_arguments arguments_of(right)
  // 172:     push &arguments right_arguments(1)
  // 173:     !right right_arguments(2)
  // 174:   push &arguments right
  // 175:   !self.functor_of std_identifier("sequence")
  // 176:   !self.arguments_of expand_arguments(arguments)
  frame->slots[5] /* temp__4 */ = create_closure(entry__9_16, 0);
  // 177: :
  // 178:   expand_arguments &self.arguments_of
  // 179:   expand_operator_call &self
  frame->slots[6] /* temp__5 */ = create_closure(entry__9_40, 0);
  // 166: if
  // 167:   functor.is_an_operator_symbol && name_of(functor) == ",":
  // 168:     $$arguments list(arguments_of(self)(1))
  // 169:     $$right arguments_of(self)(2)
  // 170:     while -> right.is_a_function_call && name_of(functor_of(right)) == ",":
  // 171:       $right_arguments arguments_of(right)
  // 172:       push &arguments right_arguments(1)
  // 173:       !right right_arguments(2)
  // 174:     push &arguments right
  // 175:     !self.functor_of std_identifier("sequence")
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
static void cont__9_44(void) {
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
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // self: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* self */ = create_cell_with_contents(arguments->slots[0]);
  // 185: show_compiler_debug_info "expand attribute-value pair"
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
  // 186: ... self.arguments_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__10_4;
}
static void cont__10_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 186: expand_arguments &self.arguments_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = var._expand_arguments;
  func = myself->type;
  frame->cont = cont__10_5;
}
static void cont__10_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 186: ... &self.arguments_of
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
static void entry__11_1(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // self: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* self */ = create_cell_with_contents(arguments->slots[0]);
  // 192: show_compiler_debug_info "expand attribute-function pair"
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
  // 193: ... self.arguments_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__11_4;
}
static void cont__11_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 193: expand_arguments &self.arguments_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = var._expand_arguments;
  func = myself->type;
  frame->cont = cont__11_5;
}
static void cont__11_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 193: ... &self.arguments_of
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
  var.sim2c__expand_statement = collect_node(var.sim2c__expand_statement);
  var.sim2c__expand_expression = collect_node(var.sim2c__expand_expression);
  var._expand_arguments = collect_node(var._expand_arguments);
  func__3_1 = collect_node(func__3_1);
  string__4_2 = collect_node(string__4_2);
  func__4_1 = collect_node(func__4_1);
  string__5_2 = collect_node(string__5_2);
  func__5_1 = collect_node(func__5_1);
  string__6_2 = collect_node(string__6_2);
  func__6_5 = collect_node(func__6_5);
  func__6_14 = collect_node(func__6_14);
  func__6_1 = collect_node(func__6_1);
  string__7_2 = collect_node(string__7_2);
  func__7_1 = collect_node(func__7_1);
  var.sim2c__expand_operator_call = collect_node(var.sim2c__expand_operator_call);
  string__8_20 = collect_node(string__8_20);
  string__8_23 = collect_node(string__8_23);
  string__8_26 = collect_node(string__8_26);
  string__8_33 = collect_node(string__8_33);
  string__8_36 = collect_node(string__8_36);
  string__8_39 = collect_node(string__8_39);
  string__8_42 = collect_node(string__8_42);
  string__8_45 = collect_node(string__8_45);
  string__8_48 = collect_node(string__8_48);
  string__8_51 = collect_node(string__8_51);
  string__8_54 = collect_node(string__8_54);
  string__8_66 = collect_node(string__8_66);
  string__8_69 = collect_node(string__8_69);
  string__8_72 = collect_node(string__8_72);
  string__8_84 = collect_node(string__8_84);
  string__8_87 = collect_node(string__8_87);
  string__8_90 = collect_node(string__8_90);
  string__8_93 = collect_node(string__8_93);
  string__8_96 = collect_node(string__8_96);
  string__8_99 = collect_node(string__8_99);
  string__8_101 = collect_node(string__8_101);
  string__8_102 = collect_node(string__8_102);
  string__8_103 = collect_node(string__8_103);
  string__8_104 = collect_node(string__8_104);
  string__8_105 = collect_node(string__8_105);
  string__8_106 = collect_node(string__8_106);
  string__8_107 = collect_node(string__8_107);
  string__8_108 = collect_node(string__8_108);
  string__8_109 = collect_node(string__8_109);
  string__8_110 = collect_node(string__8_110);
  string__8_111 = collect_node(string__8_111);
  string__8_112 = collect_node(string__8_112);
  string__8_113 = collect_node(string__8_113);
  string__8_114 = collect_node(string__8_114);
  string__8_115 = collect_node(string__8_115);
  string__8_116 = collect_node(string__8_116);
  string__8_117 = collect_node(string__8_117);
  string__8_118 = collect_node(string__8_118);
  string__8_119 = collect_node(string__8_119);
  string__8_122 = collect_node(string__8_122);
  func__8_1 = collect_node(func__8_1);
  string__9_2 = collect_node(string__9_2);
  string__9_13 = collect_node(string__9_13);
  string__9_27 = collect_node(string__9_27);
  string__9_37 = collect_node(string__9_37);
  func__9_1 = collect_node(func__9_1);
  string__10_2 = collect_node(string__10_2);
  func__10_1 = collect_node(func__10_1);
  string__11_2 = collect_node(string__11_2);
  func__11_1 = collect_node(func__11_1);
  number__1 = collect_node(number__1);
  number__2 = collect_node(number__2);
}

static int already_run_phase_1 = false;

EXPORT void phase_1__expander(void) {
  if (already_run_phase_1) return;
  already_run_phase_1 = true;
  register_module_info(&module_info);
  define_polymorphic_function("sim2c", "expand_statement", get__sim2c__expand_statement, &poly_idx__sim2c__expand_statement, &var.sim2c__expand_statement);
  define_polymorphic_function("sim2c", "expand_expression", get__sim2c__expand_expression, &poly_idx__sim2c__expand_expression, &var.sim2c__expand_expression);
}

static int already_run_phase_2 = false;

EXPORT void phase_2__expander(void) {
  if (already_run_phase_2) return;
  already_run_phase_2 = true;
  set_module("expander");
  set_used_namespaces(used_namespaces);
  number__1 = from_uint32(1U);
  number__2 = from_uint32(2U);
  func__3_1 = create_future();
  string__4_2 = from_latin_1_string("expand statement", 16);
  func__4_1 = create_future();
  string__5_2 = from_latin_1_string("expand expression", 17);
  func__5_1 = create_future();
  string__6_2 = from_latin_1_string("expand body", 11);
  func__6_5 = create_future();
  func__6_14 = create_future();
  func__6_1 = create_future();
  string__7_2 = from_latin_1_string("expand statement", 16);
  func__7_1 = create_future();
  string__8_20 = from_latin_1_string("times", 5);
  string__8_23 = from_latin_1_string("over", 4);
  string__8_26 = from_latin_1_string("plus", 4);
  string__8_33 = from_latin_1_string("negate", 6);
  string__8_36 = from_latin_1_string("minus", 5);
  string__8_39 = from_latin_1_string("shift_left", 10);
  string__8_42 = from_latin_1_string("shift_right", 11);
  string__8_45 = from_latin_1_string("bit_and", 7);
  string__8_48 = from_latin_1_string("bit_xor", 7);
  string__8_51 = from_latin_1_string("bit_or", 6);
  string__8_54 = from_latin_1_string("less", 4);
  string__8_66 = from_latin_1_string("less", 4);
  string__8_69 = from_latin_1_string("less", 4);
  string__8_72 = from_latin_1_string("less", 4);
  string__8_84 = from_latin_1_string("equal", 5);
  string__8_87 = from_latin_1_string("equal", 5);
  string__8_90 = from_latin_1_string("and", 3);
  string__8_93 = from_latin_1_string("or", 2);
  string__8_96 = from_latin_1_string("value_range", 11);
  string__8_99 = from_latin_1_string("key_value_pair", 14);
  string__8_101 = from_latin_1_string("*", 1);
  string__8_102 = from_latin_1_string("/", 1);
  string__8_103 = from_latin_1_string("+", 1);
  string__8_104 = from_latin_1_string("-", 1);
  string__8_105 = from_latin_1_string("<<", 2);
  string__8_106 = from_latin_1_string(">>", 2);
  string__8_107 = from_latin_1_string("&", 1);
  string__8_108 = from_latin_1_string("^", 1);
  string__8_109 = from_latin_1_string("|", 1);
  string__8_110 = from_latin_1_string("<=", 2);
  string__8_111 = from_latin_1_string("<", 1);
  string__8_112 = from_latin_1_string(">=", 2);
  string__8_113 = from_latin_1_string(">", 1);
  string__8_114 = from_latin_1_string("==", 2);
  string__8_115 = from_latin_1_string("!=", 2);
  string__8_116 = from_latin_1_string("&&", 2);
  string__8_117 = from_latin_1_string("||", 2);
  string__8_118 = from_latin_1_string("..", 2);
  string__8_119 = from_latin_1_string("=", 1);
  string__8_122 = from_latin_1_string("not", 3);
  func__8_1 = create_future();
  define_single_assign_static("sim2c", "expand_operator_call", get__sim2c__expand_operator_call, &var.sim2c__expand_operator_call);
  string__9_2 = from_latin_1_string("expand function call", 20);
  string__9_13 = from_latin_1_string(",", 1);
  string__9_27 = from_latin_1_string(",", 1);
  string__9_37 = from_latin_1_string("sequence", 8);
  func__9_1 = create_future();
  string__10_2 = from_latin_1_string("expand attribute-value pair", 27);
  func__10_1 = create_future();
  string__11_2 = from_latin_1_string("expand attribute-function pair", 30);
  func__11_1 = create_future();
}

static int already_run_phase_3 = false;

EXPORT void phase_3__expander(void) {
  if (already_run_phase_3) return;
  already_run_phase_3 = true;
  set_module("expander");
  set_used_namespaces(used_namespaces);
  use_polymorphic_function(NULL, "arguments_of", &get__arguments_of, &poly_idx__arguments_of);
  use_read_only(NULL, "body", &get__body, &get_value_or_future__body);
  use_read_only(NULL, "case", &get__case, &get_value_or_future__case);
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
  use_polymorphic_function(NULL, "output_arguments_of", &get__output_arguments_of, &poly_idx__output_arguments_of);
  use_polymorphic_function(NULL, "parameters_of", &get__parameters_of, &poly_idx__parameters_of);
  use_read_only(NULL, "push", &get__push, &get_value_or_future__push);
  use_polymorphic_function(NULL, "result_count_of", &get__result_count_of, &poly_idx__result_count_of);
  use_read_only(NULL, "return_statement", &get__return_statement, &get_value_or_future__return_statement);
  use_read_only(NULL, "show_compiler_debug_info", &get__show_compiler_debug_info, &get_value_or_future__show_compiler_debug_info);
  use_read_only("sim2c", "attribute_function_pair", &get__sim2c__attribute_function_pair, &get_value_or_future__sim2c__attribute_function_pair);
  use_read_only("sim2c", "attribute_value_pair", &get__sim2c__attribute_value_pair, &get_value_or_future__sim2c__attribute_value_pair);
  use_read_only("sim2c", "body", &get__sim2c__body, &get_value_or_future__sim2c__body);
  use_read_only("sim2c", "call", &get__sim2c__call, &get_value_or_future__sim2c__call);
  use_read_only("sim2c", "function_call", &get__sim2c__function_call, &get_value_or_future__sim2c__function_call);
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
  define_method("types", "grammar_node", poly_idx__expand_statement, func__4_1);
  define_method("types", "grammar_node", poly_idx__expand_expression, func__5_1);
  define_method("sim2c", "body", poly_idx__expand_expression, func__6_1);
  define_method("sim2c", "call", poly_idx__expand_statement, func__7_1);
  define_method("sim2c", "function_call", poly_idx__expand_expression, func__9_1);
  define_method("sim2c", "attribute_value_pair", poly_idx__expand_expression, func__10_1);
  define_method("sim2c", "attribute_function_pair", poly_idx__expand_expression, func__11_1);
}

static int already_run_phase_4 = false;

EXPORT void phase_4__expander(void) {
  if (already_run_phase_4) return;
  already_run_phase_4 = true;
  assign_value(&var.sim2c__expand_statement, create_function(type__sim2c__expand_statement, -1));
  assign_value(&var.sim2c__expand_expression, create_function(type__sim2c__expand_expression, -1));
  assign_variable(&var._expand_arguments, &func__3_1);
  assign_variable(&var.sim2c__expand_operator_call, &func__8_1);
}

static int already_run_phase_5 = false;

EXPORT void phase_5__expander(void) {
  if (already_run_phase_5) return;
  already_run_phase_5 = true;
  assign_value(&func__3_1, create_function(entry__3_1, 1));
  assign_value(&func__4_1, create_function(entry__4_1, 1));
  assign_value(&func__5_1, create_function(entry__5_1, 1));
  assign_value(&func__6_5, create_function(entry__6_5, 1));
  assign_value(&func__6_14, create_function(entry__6_14, 1));
  assign_value(&func__6_1, create_function(entry__6_1, 1));
  assign_value(&func__7_1, create_function(entry__7_1, 1));
  assign_value(&func__8_1, create_function(entry__8_1, 1));
  assign_value(&func__9_1, create_function(entry__9_1, 1));
  assign_value(&func__10_1, create_function(entry__10_1, 1));
  assign_value(&func__11_1, create_function(entry__11_1, 1));
  register_collector(collect__expander);
}
