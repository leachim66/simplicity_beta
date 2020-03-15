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
REGISTER FUNC func ASM("r14");
REGISTER FRAME *frame ASM("r15");
IMPORT void allocate_initialized_frame_gc(int slot_idx, int slot_count);
REGISTER int argument_count ASM("ebx");
REGISTER FRAME *arguments ASM("r12");
IMPORT void *node_p;
IMPORT int result_count;
REGISTER NODE *myself ASM("r13");
IMPORT void invalid_results_error(void);
IMPORT void initialize_future(NODE *var, NODE *val);
IMPORT void invalid_arguments_error(void);
IMPORT NODE *create_cell(void);
IMPORT NODE *create_future(void);
IMPORT NODE *create_cell_with_contents(NODE *contents);
typedef struct CELL {
  FUNC type;
  struct ATTRIBUTES *attributes;
  NODE *contents;
} CELL;
IMPORT NODE *create_closure(FUNC type, int par_count);
IMPORT NODE *undefined;
IMPORT NODE *create_continuation(void);
IMPORT void allocate_arguments(void);
IMPORT void too_few_arguments_error(void);
IMPORT NODE *from_arguments(int first_idx, int count);
IMPORT NODE *empty_string;
IMPORT NODE *collect_node(NODE *node);
IMPORT void register_module_info(MODULE_INFO *info);
IMPORT void set_module(const char *name);
IMPORT void set_used_namespaces(const char **namespaces);
IMPORT void define_single_assign_static(
  const char *namespace, const char *name,
  NODE_GETTER getter, NODE **var_p
);
IMPORT NODE *from_latin_1_string(const char *str, long len);
IMPORT void use_read_only(
  const char *namespace, const char *name,
  NODE_GETTER *getter, NODE_GETTER *get_value_or_future
);
IMPORT void assign_value(NODE **dest, NODE *val);
IMPORT NODE *from_uchar32(unsigned int chr);
IMPORT NODE *from_uint32(uint32_t val);
IMPORT void assign_variable(NODE **dest, NODE **var_p);
IMPORT NODE *create_function(FUNC func, int par_count);
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
static NODE_GETTER get__DIGIT;
static NODE_GETTER get_value_or_future__DIGIT;
static NODE_GETTER get__IDENTIFIER;
static NODE_GETTER get_value_or_future__IDENTIFIER;
static NODE_GETTER get__LETTER;
static NODE_GETTER get_value_or_future__LETTER;
static NODE_GETTER get__NAME;
static NODE_GETTER get_value_or_future__NAME;
static NODE_GETTER get__alt;
static NODE_GETTER get_value_or_future__alt;
static NODE_GETTER get__case;
static NODE_GETTER get_value_or_future__case;
static NODE_GETTER get__character;
static NODE_GETTER get_value_or_future__character;
static NODE_GETTER get__deserialize_item;
static NODE_GETTER get_value_or_future__deserialize_item;
static NODE_GETTER get__empty_table;
static NODE_GETTER get_value_or_future__empty_table;
static NODE_GETTER get__for_each_pair;
static NODE_GETTER get_value_or_future__for_each_pair;
static NODE_GETTER get__forever;
static NODE_GETTER get_value_or_future__forever;
static NODE_GETTER get__get_deserialization_indent;
static NODE_GETTER get_value_or_future__get_deserialization_indent;
static NODE_GETTER get__has_prefix;
static NODE_GETTER get_value_or_future__has_prefix;
static NODE_GETTER get__if;
static NODE_GETTER get_value_or_future__if;
static NODE_GETTER get__inc;
static NODE_GETTER get_value_or_future__inc;
static NODE_GETTER get__is_defined;
static NODE_GETTER get_value_or_future__is_defined;
static NODE_GETTER get__is_undefined;
static NODE_GETTER get_value_or_future__is_undefined;
static NODE_GETTER get__length_of;
static NODE_GETTER get_value_or_future__length_of;
static NODE_GETTER get__many;
static NODE_GETTER get_value_or_future__many;
static NODE_GETTER get__match;
static NODE_GETTER get_value_or_future__match;
static NODE_GETTER get__optional;
static NODE_GETTER get_value_or_future__optional;
static NODE_GETTER get__parse_integer;
static NODE_GETTER get_value_or_future__parse_integer;
static NODE_GETTER get__parse_number;
static NODE_GETTER get_value_or_future__parse_number;
static NODE_GETTER get__plus;
static NODE_GETTER get_value_or_future__plus;
static NODE_GETTER get__push;
static NODE_GETTER get_value_or_future__push;
static NODE_GETTER get__raise;
static NODE_GETTER get_value_or_future__raise;
static NODE_GETTER get__range;
static NODE_GETTER get_value_or_future__range;
static NODE_GETTER get__some;
static NODE_GETTER get_value_or_future__some;
static NODE_GETTER get__std__and;
static NODE_GETTER get_value_or_future__std__and;
static NODE_GETTER get__std__equal;
static NODE_GETTER get_value_or_future__std__equal;
static NODE_GETTER get__std__less;
static NODE_GETTER get_value_or_future__std__less;
static NODE_GETTER get__std__minus;
static NODE_GETTER get_value_or_future__std__minus;
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
static NODE_GETTER get__std__value_range;
static NODE_GETTER get_value_or_future__std__value_range;
static NODE_GETTER get__undefined;
static NODE_GETTER get_value_or_future__undefined;
static NODE_GETTER get__while;
static NODE_GETTER get_value_or_future__while;
static struct {
  NODE *_deserializers;
  NODE *_deserialize_stream;
  NODE *std__NAME;
  NODE *std__IDENTIFIER;
  NODE *std__register_deserializer;
  NODE *std__get_deserialization_indent;
  NODE *std__deserialize_item;
  NODE *std__create_deserializer;
  NODE *std__deserialize;
} var;
static const char *var_names[] = {
  "deserializers",
  "deserialize_stream"
};
static NODE *get__std__NAME(void) {
  return var.std__NAME;
}
static NODE *get__std__IDENTIFIER(void) {
  return var.std__IDENTIFIER;
}
static NODE *func__4_1;
static void entry__4_1(void);
static FRAME_INFO frame__4_1 = {2, {"tag", "deserializer"}};
static void cont__4_2(void);
static NODE *get__std__register_deserializer(void) {
  return var.std__register_deserializer;
}
static NODE *func__5_1;
static void entry__5_1(void);
static FRAME_INFO frame__5_1 = {4, {"text", "i", "n", "indent"}};
static void cont__5_2(void);
static NODE *func__5_3;
static void entry__5_3(void);
static FRAME_INFO frame__5_3 = {4, {"n", "i", "text", "indent"}};
static void cont__5_4(void);
static void cont__5_5(void);
static NODE *func__5_6;
static void entry__5_6(void);
static FRAME_INFO frame__5_6 = {2, {"text", "i"}};
static void cont__5_7(void);
static void cont__5_8(void);
static void cont__5_9(void);
static NODE *func__5_10;
static void entry__5_10(void);
static FRAME_INFO frame__5_10 = {2, {"i", "indent"}};
static void cont__5_11(void);
static void cont__5_12(void);
static void cont__5_13(void);
static NODE *func__5_14;
static void entry__5_14(void);
static FRAME_INFO frame__5_14 = {4, {"n", "i", "text", "indent"}};
static void cont__5_15(void);
static void cont__5_16(void);
static NODE *func__5_17;
static void entry__5_17(void);
static FRAME_INFO frame__5_17 = {2, {"text", "i"}};
static void cont__5_18(void);
static void cont__5_19(void);
static void cont__5_20(void);
static NODE *func__5_21;
static void entry__5_21(void);
static FRAME_INFO frame__5_21 = {2, {"i", "indent"}};
static void cont__5_22(void);
static void cont__5_23(void);
static void cont__5_24(void);
static void cont__5_25(void);
static void cont__5_26(void);
static NODE *get__std__get_deserialization_indent(void) {
  return var.std__get_deserialization_indent;
}
static NODE *func__6_1;
static void entry__6_1(void);
static FRAME_INFO frame__6_1 = {2, {"text", "base_indent"}};
static void cont__6_2(void);
static void cont__6_3(void);
static void cont__6_4(void);
static NODE *func__6_5;
static void entry__6_5(void);
static FRAME_INFO frame__6_5 = {1, {"text"}};
static void cont__6_6(void);
static void cont__6_7(void);
static void cont__6_8(void);
static NODE *func__6_9;
static void entry__6_9(void);
static FRAME_INFO frame__6_9 = {3, {"text", "base_indent", "indent"}};
static void cont__6_10(void);
static void cont__6_11(void);
static NODE *func__6_12;
static void entry__6_12(void);
static FRAME_INFO frame__6_12 = {2, {"text", "indent"}};
static NODE *func__6_13;
static void entry__6_13(void);
static FRAME_INFO frame__6_13 = {0, {}};
static NODE *func__6_14;
static void entry__6_14(void);
static FRAME_INFO frame__6_14 = {2, {"text", "base_indent"}};
static NODE *func__6_15;
static void entry__6_15(void);
static FRAME_INFO frame__6_15 = {1, {"text"}};
static void cont__6_16(void);
static void cont__6_17(void);
static NODE *func__6_18;
static void entry__6_18(void);
static FRAME_INFO frame__6_18 = {1, {"text"}};
static void cont__6_19(void);
static void cont__6_20(void);
static void cont__6_21(void);
static NODE *get__std__deserialize_item(void) {
  return var.std__deserialize_item;
}
static NODE *func__7_1;
static void entry__7_1(void);
static FRAME_INFO frame__7_1 = {4, {"name", "prototype", "attributes", "attribute_setters"}};
static NODE *func__7_2;
static void entry__7_2(void);
static FRAME_INFO frame__7_2 = {3, {"attribute_name", "attribute_setter", "attribute_setters"}};
static void cont__7_3(void);
static void cont__7_4(void);
static void cont__7_5(void);
static void cont__7_6(void);
static NODE *func__7_7;
static void entry__7_7(void);
static FRAME_INFO frame__7_7 = {7, {"text", "base_indent", "return", "prototype", "name", "attribute_setters", "obj"}};
static NODE *string__7_8;
static void cont__7_9(void);
static NODE *func__7_10;
static void entry__7_10(void);
static FRAME_INFO frame__7_10 = {3, {"return", "text", "prototype"}};
static void cont__7_11(void);
static void cont__7_12(void);
static void cont__7_13(void);
static void cont__7_14(void);
static void cont__7_15(void);
static void cont__7_16(void);
static NODE *func__7_17;
static void entry__7_17(void);
static FRAME_INFO frame__7_17 = {1, {"name"}};
static NODE *string__7_18;
static NODE *string__7_19;
static void cont__7_20(void);
static void cont__7_21(void);
static NODE *func__7_22;
static void entry__7_22(void);
static FRAME_INFO frame__7_22 = {11, {"text", "return", "obj", "base_indent", "name", "attribute_setters", "remaining_text", "indent", "len", "tag", "attribute_setter"}};
static void cont__7_23(void);
static void cont__7_24(void);
static NODE *func__7_25;
static void entry__7_25(void);
static FRAME_INFO frame__7_25 = {1, {"text"}};
static void cont__7_26(void);
static void cont__7_27(void);
static void cont__7_28(void);
static void cont__7_29(void);
static NODE *func__7_30;
static void entry__7_30(void);
static FRAME_INFO frame__7_30 = {3, {"return", "text", "obj"}};
static void cont__7_31(void);
static void cont__7_32(void);
static void cont__7_33(void);
static void cont__7_34(void);
static NODE *func__7_35;
static void entry__7_35(void);
static FRAME_INFO frame__7_35 = {3, {"return", "text", "obj"}};
static void cont__7_36(void);
static void cont__7_37(void);
static void cont__7_38(void);
static NODE *func__7_39;
static void entry__7_39(void);
static FRAME_INFO frame__7_39 = {2, {"text", "len"}};
static void cont__7_40(void);
static void cont__7_41(void);
static void cont__7_42(void);
static void cont__7_43(void);
static void cont__7_44(void);
static NODE *func__7_45;
static void entry__7_45(void);
static FRAME_INFO frame__7_45 = {1, {"name"}};
static NODE *string__7_46;
static NODE *string__7_47;
static void cont__7_48(void);
static void cont__7_49(void);
static void cont__7_50(void);
static void cont__7_51(void);
static void cont__7_52(void);
static NODE *func__7_53;
static void entry__7_53(void);
static FRAME_INFO frame__7_53 = {1, {"name"}};
static NODE *string__7_54;
static NODE *string__7_55;
static void cont__7_56(void);
static void cont__7_57(void);
static void cont__7_58(void);
static void cont__7_59(void);
static void cont__7_60(void);
static void cont__7_61(void);
static void cont__7_62(void);
static void cont__7_63(void);
static NODE *get__std__create_deserializer(void) {
  return var.std__create_deserializer;
}
static NODE *func__8_1;
static void entry__8_1(void);
static FRAME_INFO frame__8_1 = {3, {"text", "indent", "return"}};
static void cont__8_2(void);
static NODE *func__8_3;
static void entry__8_3(void);
static FRAME_INFO frame__8_3 = {5, {"text", "return", "str", "i", "n"}};
static void cont__8_4(void);
static NODE *func__8_5;
static void entry__8_5(void);
static FRAME_INFO frame__8_5 = {5, {"n", "i", "text", "return", "str"}};
static void cont__8_6(void);
static void cont__8_7(void);
static NODE *func__8_8;
static void entry__8_8(void);
static FRAME_INFO frame__8_8 = {6, {"text", "i", "return", "str", "n", "chr"}};
static void cont__8_9(void);
static NODE *func__8_10;
static void entry__8_10(void);
static FRAME_INFO frame__8_10 = {4, {"return", "text", "i", "str"}};
static void cont__8_11(void);
static void cont__8_12(void);
static void cont__8_13(void);
static NODE *func__8_14;
static void entry__8_14(void);
static FRAME_INFO frame__8_14 = {7, {"text", "i", "n", "str", "escape_text", "rest_text", "value"}};
static void cont__8_15(void);
static void cont__8_16(void);
static void cont__8_17(void);
static void cont__8_18(void);
static void cont__8_19(void);
static void cont__8_20(void);
static void cont__8_21(void);
static void cont__8_22(void);
static void cont__8_23(void);
static void cont__8_24(void);
static NODE *func__8_25;
static void entry__8_25(void);
static FRAME_INFO frame__8_25 = {3, {"n", "i", "text"}};
static void cont__8_26(void);
static NODE *func__8_27;
static void entry__8_27(void);
static FRAME_INFO frame__8_27 = {2, {"text", "i"}};
static void cont__8_28(void);
static void cont__8_29(void);
static void cont__8_30(void);
static void cont__8_31(void);
static void cont__8_32(void);
static NODE *func__8_33;
static void entry__8_33(void);
static FRAME_INFO frame__8_33 = {0, {}};
static NODE *string__8_34;
static void cont__8_35(void);
static void cont__8_36(void);
static void cont__8_37(void);
static NODE *func__8_38;
static void entry__8_38(void);
static FRAME_INFO frame__8_38 = {2, {"str", "chr"}};
static void cont__8_39(void);
static void cont__8_40(void);
static void cont__8_41(void);
static void cont__8_42(void);
static NODE *string__8_43;
static NODE *func__8_44;
static void entry__8_44(void);
static FRAME_INFO frame__8_44 = {4, {"text", "return", "n", "chr"}};
static void cont__8_45(void);
static void cont__8_46(void);
static NODE *func__8_47;
static void entry__8_47(void);
static FRAME_INFO frame__8_47 = {0, {}};
static NODE *string__8_48;
static void cont__8_49(void);
static void cont__8_50(void);
static void cont__8_51(void);
static NODE *func__8_52;
static void entry__8_52(void);
static FRAME_INFO frame__8_52 = {7, {"text", "n", "return", "escape_text", "rest_text", "value", "i"}};
static void cont__8_53(void);
static void cont__8_54(void);
static void cont__8_55(void);
static void cont__8_56(void);
static void cont__8_57(void);
static void cont__8_58(void);
static void cont__8_59(void);
static void cont__8_60(void);
static NODE *func__8_61;
static void entry__8_61(void);
static FRAME_INFO frame__8_61 = {3, {"n", "i", "text"}};
static void cont__8_62(void);
static void cont__8_63(void);
static NODE *func__8_64;
static void entry__8_64(void);
static FRAME_INFO frame__8_64 = {2, {"text", "i"}};
static void cont__8_65(void);
static void cont__8_66(void);
static void cont__8_67(void);
static NODE *func__8_68;
static void entry__8_68(void);
static FRAME_INFO frame__8_68 = {2, {"text", "i"}};
static void cont__8_69(void);
static void cont__8_70(void);
static void cont__8_71(void);
static void cont__8_72(void);
static void cont__8_73(void);
static void cont__8_74(void);
static void cont__8_75(void);
static NODE *func__8_76;
static void entry__8_76(void);
static FRAME_INFO frame__8_76 = {0, {}};
static NODE *string__8_77;
static void cont__8_78(void);
static void cont__8_79(void);
static void cont__8_80(void);
static void cont__8_81(void);
static void cont__8_82(void);
static NODE *func__8_83;
static void entry__8_83(void);
static FRAME_INFO frame__8_83 = {3, {"text", "return", "chr"}};
static void cont__8_84(void);
static void cont__8_85(void);
static void cont__8_86(void);
static NODE *func__8_87;
static void entry__8_87(void);
static FRAME_INFO frame__8_87 = {0, {}};
static NODE *string__8_88;
static void cont__8_89(void);
static void cont__8_90(void);
static void cont__8_91(void);
static void cont__8_92(void);
static NODE *func__8_93;
static void entry__8_93(void);
static FRAME_INFO frame__8_93 = {3, {"text", "return", "val"}};
static void cont__8_94(void);
static void cont__8_95(void);
static NODE *func__8_96;
static void entry__8_96(void);
static FRAME_INFO frame__8_96 = {0, {}};
static NODE *string__8_97;
static void cont__8_98(void);
static NODE *func__8_99;
static void entry__8_99(void);
static FRAME_INFO frame__8_99 = {3, {"text", "indent", "len"}};
static void cont__8_100(void);
static void cont__8_101(void);
static NODE *func__8_102;
static void entry__8_102(void);
static FRAME_INFO frame__8_102 = {5, {"text", "len", "indent", "tag", "deserializer"}};
static void cont__8_103(void);
static void cont__8_104(void);
static void cont__8_105(void);
static NODE *func__8_106;
static void entry__8_106(void);
static FRAME_INFO frame__8_106 = {4, {"text", "len", "deserializer", "indent"}};
static void cont__8_107(void);
static void cont__8_108(void);
static void cont__8_109(void);
static NODE *func__8_110;
static void entry__8_110(void);
static FRAME_INFO frame__8_110 = {1, {"tag"}};
static NODE *string__8_111;
static NODE *string__8_112;
static void cont__8_113(void);
static NODE *func__8_114;
static void entry__8_114(void);
static FRAME_INFO frame__8_114 = {0, {}};
static NODE *string__8_115;
static void cont__8_116(void);
static NODE *func__9_1;
static void entry__9_1(void);
static FRAME_INFO frame__9_1 = {3, {"text", "remaining_text", "obj"}};
static void cont__9_2(void);
static void cont__9_3(void);
static NODE *func__9_4;
static void entry__9_4(void);
static FRAME_INFO frame__9_4 = {1, {"obj"}};
static NODE *func__9_5;
static void entry__9_5(void);
static FRAME_INFO frame__9_5 = {0, {}};
static void cont__9_6(void);
static NODE *get__std__deserialize(void) {
  return var.std__deserialize;
}
static void cont__10_1(void);
static void cont__10_2(void);
static void cont__10_3(void);
static void cont__10_4(void);
static void cont__10_5(void);
static void cont__10_6(void);
static void cont__10_7(void);
static NODE *string__11_1;
static void cont__11_2(void);
static void cont__11_3(void);
static void cont__11_4(void);
void run__basic__deserialize(void);

static CONTINUATION_INFO continuation_info[] = {
  {run__basic__deserialize, NULL, 23, 23, 25, 41},
  {cont__10_1, NULL, 23, 23, 20, 42},
  {cont__10_2, NULL, 23, 23, 60, 76},
  {cont__10_3, NULL, 23, 23, 55, 77},
  {cont__10_4, NULL, 23, 23, 50, 77},
  {cont__10_5, NULL, 23, 23, 45, 78},
  {cont__10_6, NULL, 23, 23, 1, 78},
  {cont__10_7, NULL, 24, 24, 33, 42},
  {cont__11_2, NULL, 24, 24, 24, 43},
  {cont__11_3, NULL, 24, 24, 1, 43},
  {cont__11_4, NULL, 25, 25, 1, 27},
  {entry__4_1, NULL, 27, 27, 49, 67},
  {cont__4_2, &frame__4_1, 27, 27, 80, 80},
  {entry__5_6, NULL, 33, 33, 22, 28},
  {cont__5_7, &frame__5_6, 33, 33, 22, 38},
  {cont__5_8, &frame__5_6, 33, 33, 22, 38},
  {entry__5_10, NULL, 34, 34, 5, 10},
  {cont__5_11, &frame__5_10, 35, 35, 5, 18},
  {cont__5_12, &frame__5_10, 35, 35, 18, 18},
  {entry__5_3, NULL, 33, 33, 12, 17},
  {cont__5_4, &frame__5_3, 33, 33, 12, 17},
  {cont__5_5, &frame__5_3, 33, 33, 12, 38},
  {cont__5_9, &frame__5_3, 33, 35, 9, 18},
  {entry__5_17, NULL, 36, 36, 22, 28},
  {cont__5_18, &frame__5_17, 36, 36, 22, 35},
  {cont__5_19, &frame__5_17, 36, 36, 22, 35},
  {entry__5_21, NULL, 37, 37, 5, 10},
  {cont__5_22, &frame__5_21, 38, 38, 5, 15},
  {cont__5_23, &frame__5_21, 38, 38, 15, 15},
  {entry__5_14, NULL, 36, 36, 12, 17},
  {cont__5_15, &frame__5_14, 36, 36, 12, 17},
  {cont__5_16, &frame__5_14, 36, 36, 12, 35},
  {cont__5_20, &frame__5_14, 36, 38, 9, 15},
  {entry__5_1, NULL, 31, 31, 3, 20},
  {cont__5_2, &frame__5_1, 33, 35, 3, 18},
  {cont__5_13, &frame__5_1, 36, 38, 3, 15},
  {cont__5_24, &frame__5_1, 39, 39, 18, 18},
  {cont__5_25, &frame__5_1, 39, 39, 3, 18},
  {cont__5_26, &frame__5_1, 40, 40, 3, 11},
  {entry__6_5, NULL, 44, 44, 29, 35},
  {cont__6_6, &frame__6_5, 44, 44, 29, 45},
  {cont__6_7, &frame__6_5, 44, 44, 29, 45},
  {entry__6_12, NULL, 48, 48, 11, 40},
  {entry__6_13, NULL, 49, 49, 9, 30},
  {entry__6_9, NULL, 45, 45, 7, 47},
  {cont__6_10, &frame__6_9, 47, 47, 9, 28},
  {cont__6_11, &frame__6_9, 46, 49, 7, 30},
  {entry__6_18, NULL, 51, 51, 47, 47},
  {cont__6_19, &frame__6_18, 51, 51, 32, 47},
  {cont__6_20, &frame__6_18, 51, 51, 47, 47},
  {entry__6_15, NULL, 51, 51, 16, 22},
  {cont__6_16, &frame__6_15, 51, 51, 16, 29},
  {cont__6_17, &frame__6_15, 51, 51, 13, 47},
  {entry__6_14, NULL, 51, 51, 7, 47},
  {cont__6_21, &frame__6_14, 52, 52, 7, 41},
  {entry__6_1, NULL, 44, 44, 5, 19},
  {cont__6_2, &frame__6_1, 44, 44, 5, 24},
  {cont__6_3, &frame__6_1, 44, 44, 5, 24},
  {cont__6_4, &frame__6_1, 44, 44, 5, 45},
  {cont__6_8, &frame__6_1, 43, 52, 3, 42},
  {entry__7_2, NULL, 57, 57, 48, 48},
  {cont__7_3, &frame__7_2, 57, 57, 24, 49},
  {cont__7_4, &frame__7_2, 57, 57, 5, 50},
  {cont__7_5, &frame__7_2, 57, 57, 67, 67},
  {entry__7_10, NULL, 64, 64, 53, 53},
  {cont__7_11, &frame__7_10, 64, 64, 39, 54},
  {cont__7_12, &frame__7_10, 64, 64, 32, 64},
  {entry__7_17, NULL, 66, 66, 13, 72},
  {cont__7_20, &frame__7_17, 66, 66, 7, 72},
  {entry__7_25, NULL, 69, 69, 34, 40},
  {cont__7_26, &frame__7_25, 69, 69, 34, 50},
  {cont__7_27, &frame__7_25, 69, 69, 34, 50},
  {cont__7_28, &frame__7_25, 69, 69, 34, 50},
  {entry__7_30, NULL, 69, 69, 53, 67},
  {entry__7_35, NULL, 71, 71, 33, 47},
  {entry__7_39, NULL, 74, 74, 35, 39},
  {cont__7_40, &frame__7_39, 74, 74, 30, 40},
  {cont__7_41, &frame__7_39, 74, 74, 30, 47},
  {cont__7_42, &frame__7_39, 74, 74, 30, 47},
  {cont__7_43, &frame__7_39, 74, 74, 30, 47},
  {entry__7_45, NULL, 75, 75, 15, 77},
  {cont__7_48, &frame__7_45, 75, 75, 9, 77},
  {entry__7_53, NULL, 79, 79, 15, 77},
  {cont__7_56, &frame__7_53, 79, 79, 9, 77},
  {entry__7_22, NULL, 69, 69, 10, 24},
  {cont__7_23, &frame__7_22, 69, 69, 10, 29},
  {cont__7_24, &frame__7_22, 69, 69, 10, 50},
  {cont__7_29, &frame__7_22, 69, 69, 7, 67},
  {cont__7_31, &frame__7_22, 70, 70, 7, 61},
  {cont__7_32, &frame__7_22, 71, 71, 10, 30},
  {cont__7_33, &frame__7_22, 71, 71, 10, 30},
  {cont__7_34, &frame__7_22, 71, 71, 7, 47},
  {cont__7_36, &frame__7_22, 73, 73, 7, 32},
  {cont__7_37, &frame__7_22, 74, 74, 10, 25},
  {cont__7_38, &frame__7_22, 74, 74, 10, 47},
  {cont__7_44, &frame__7_22, 74, 75, 7, 77},
  {cont__7_49, &frame__7_22, 76, 76, 7, 28},
  {cont__7_50, &frame__7_22, 77, 77, 7, 46},
  {cont__7_51, &frame__7_22, 78, 78, 10, 38},
  {cont__7_52, &frame__7_22, 78, 79, 7, 77},
  {cont__7_57, &frame__7_22, 80, 80, 19, 23},
  {cont__7_58, &frame__7_22, 80, 80, 26, 26},
  {cont__7_59, &frame__7_22, 80, 80, 7, 26},
  {cont__7_60, &frame__7_22, 81, 81, 29, 58},
  {cont__7_61, &frame__7_22, 81, 81, 7, 58},
  {cont__7_62, &frame__7_22, 81, 81, 58, 58},
  {entry__7_7, NULL, 64, 64, 8, 29},
  {cont__7_9, &frame__7_7, 64, 64, 5, 64},
  {cont__7_13, &frame__7_7, 65, 65, 8, 14},
  {cont__7_14, &frame__7_7, 65, 65, 8, 24},
  {cont__7_15, &frame__7_7, 65, 65, 8, 24},
  {cont__7_16, &frame__7_7, 65, 66, 5, 72},
  {cont__7_21, &frame__7_7, 68, 81, 5, 58},
  {cont__7_63, &frame__7_7, 81, 81, 58, 58},
  {entry__7_1, NULL, 56, 57, 3, 67},
  {cont__7_6, &frame__7_1, 58, 81, 3, 59},
  {entry__8_10, NULL, 100, 100, 31, 33},
  {cont__8_11, &frame__8_10, 100, 100, 36, 36},
  {cont__8_12, &frame__8_10, 100, 100, 20, 37},
  {cont__8_13, &frame__8_10, 100, 100, 13, 41},
  {entry__8_27, NULL, 105, 105, 47, 53},
  {cont__8_28, &frame__8_27, 105, 105, 47, 60},
  {cont__8_29, &frame__8_27, 105, 105, 47, 60},
  {cont__8_30, &frame__8_27, 105, 105, 47, 60},
  {entry__8_25, NULL, 105, 105, 38, 42},
  {cont__8_26, &frame__8_25, 105, 105, 38, 60},
  {cont__8_31, &frame__8_25, 105, 105, 38, 60},
  {entry__8_33, NULL, 106, 106, 15, 79},
  {entry__8_14, NULL, 102, 102, 37, 39},
  {cont__8_15, &frame__8_14, 102, 102, 42, 42},
  {cont__8_16, &frame__8_14, 102, 102, 13, 43},
  {cont__8_17, &frame__8_14, 103, 103, 13, 55},
  {cont__8_18, &frame__8_14, 104, 104, 23, 44},
  {cont__8_19, &frame__8_14, 104, 104, 21, 44},
  {cont__8_20, &frame__8_14, 104, 104, 46, 65},
  {cont__8_21, &frame__8_14, 104, 104, 21, 65},
  {cont__8_22, &frame__8_14, 104, 104, 13, 65},
  {cont__8_23, &frame__8_14, 105, 105, 16, 33},
  {cont__8_24, &frame__8_14, 105, 105, 16, 60},
  {cont__8_32, &frame__8_14, 105, 106, 13, 79},
  {cont__8_35, &frame__8_14, 107, 107, 23, 38},
  {cont__8_36, &frame__8_14, 107, 107, 13, 38},
  {cont__8_37, &frame__8_14, 107, 107, 38, 38},
  {entry__8_38, NULL, 109, 109, 13, 25},
  {cont__8_39, &frame__8_38, 109, 109, 25, 25},
  {entry__8_8, NULL, 96, 96, 9, 20},
  {cont__8_9, &frame__8_8, 97, 109, 9, 26},
  {cont__8_40, &frame__8_8, 110, 110, 9, 14},
  {cont__8_41, &frame__8_8, 110, 110, 14, 14},
  {entry__8_5, NULL, 95, 95, 16, 21},
  {cont__8_6, &frame__8_5, 95, 95, 16, 21},
  {cont__8_7, &frame__8_5, 95, 110, 13, 14},
  {entry__8_3, NULL, 94, 94, 7, 24},
  {cont__8_4, &frame__8_3, 95, 110, 7, 14},
  {cont__8_42, &frame__8_3, 111, 111, 7, 69},
  {entry__8_47, NULL, 115, 115, 9, 78},
  {entry__8_68, NULL, 127, 127, 20, 22},
  {cont__8_69, &frame__8_68, 127, 127, 15, 23},
  {cont__8_70, &frame__8_68, 127, 127, 15, 35},
  {cont__8_71, &frame__8_68, 127, 127, 15, 35},
  {cont__8_72, &frame__8_68, 127, 127, 15, 35},
  {entry__8_64, NULL, 126, 126, 15, 21},
  {cont__8_65, &frame__8_64, 126, 126, 15, 28},
  {cont__8_66, &frame__8_64, 126, 126, 15, 28},
  {cont__8_67, &frame__8_64, 127, 127, 15, 35},
  {cont__8_73, &frame__8_64, },
  {entry__8_61, NULL, 125, 125, 15, 17},
  {cont__8_62, &frame__8_61, 125, 125, 15, 21},
  {cont__8_63, &frame__8_61, },
  {cont__8_74, &frame__8_61, },
  {entry__8_76, NULL, 129, 130, 15, 78},
  {entry__8_52, NULL, 119, 119, 38, 38},
  {cont__8_53, &frame__8_52, 119, 119, 11, 39},
  {cont__8_54, &frame__8_52, 120, 120, 11, 53},
  {cont__8_55, &frame__8_52, 121, 121, 16, 37},
  {cont__8_56, &frame__8_52, 121, 121, 14, 37},
  {cont__8_57, &frame__8_52, 121, 121, 39, 58},
  {cont__8_58, &frame__8_52, 121, 121, 11, 58},
  {cont__8_59, &frame__8_52, 124, 124, 15, 32},
  {cont__8_60, &frame__8_52, },
  {cont__8_75, &frame__8_52, 122, 130, 11, 80},
  {cont__8_78, &frame__8_52, 131, 131, 29, 31},
  {cont__8_79, &frame__8_52, 131, 131, 34, 34},
  {cont__8_80, &frame__8_52, 131, 131, 18, 35},
  {cont__8_81, &frame__8_52, 131, 131, 37, 52},
  {cont__8_82, &frame__8_52, 131, 131, 11, 52},
  {entry__8_87, NULL, 134, 135, 13, 78},
  {entry__8_83, NULL, 133, 133, 14, 20},
  {cont__8_84, &frame__8_83, 133, 133, 14, 32},
  {cont__8_85, &frame__8_83, 133, 133, 14, 32},
  {cont__8_86, &frame__8_83, 133, 135, 11, 79},
  {cont__8_89, &frame__8_83, 136, 136, 32, 32},
  {cont__8_90, &frame__8_83, 136, 136, 18, 33},
  {cont__8_91, &frame__8_83, 136, 136, 11, 37},
  {entry__8_44, NULL, 113, 113, 7, 24},
  {cont__8_45, &frame__8_44, 114, 114, 10, 14},
  {cont__8_46, &frame__8_44, 114, 115, 7, 78},
  {cont__8_49, &frame__8_44, 116, 116, 7, 18},
  {cont__8_50, &frame__8_44, 118, 118, 9, 19},
  {cont__8_51, &frame__8_44, 117, 136, 7, 38},
  {entry__8_96, NULL, 140, 140, 9, 76},
  {entry__8_93, NULL, 138, 138, 7, 30},
  {cont__8_94, &frame__8_93, 139, 139, 10, 25},
  {cont__8_95, &frame__8_93, 139, 140, 7, 76},
  {cont__8_98, &frame__8_93, 141, 141, 7, 21},
  {entry__8_106, NULL, 150, 150, 27, 31},
  {cont__8_107, &frame__8_106, 150, 150, 34, 34},
  {cont__8_108, &frame__8_106, 150, 150, 15, 34},
  {cont__8_109, &frame__8_106, 151, 151, 15, 38},
  {entry__8_110, NULL, 153, 154, 21, 59},
  {cont__8_113, &frame__8_110, 153, 154, 15, 59},
  {entry__8_102, NULL, 146, 146, 11, 32},
  {cont__8_103, &frame__8_102, 147, 147, 11, 42},
  {cont__8_104, &frame__8_102, 149, 149, 13, 35},
  {cont__8_105, &frame__8_102, 148, 154, 11, 61},
  {entry__8_114, NULL, 156, 156, 11, 74},
  {entry__8_99, NULL, 143, 143, 7, 32},
  {cont__8_100, &frame__8_99, 145, 145, 9, 22},
  {cont__8_101, &frame__8_99, 144, 156, 7, 75},
  {entry__8_1, NULL, 90, 90, 5, 11},
  {cont__8_2, &frame__8_1, 137, 137, 5, 14},
  {cont__8_92, &frame__8_1, 89, 156, 3, 77},
  {cont__8_116, &frame__8_1, 156, 156, 77, 77},
  {entry__9_4, NULL, 160, 160, 31, 36},
  {entry__9_5, NULL, 160, 160, 39, 50},
  {entry__9_1, NULL, 159, 159, 3, 48},
  {cont__9_2, &frame__9_1, 160, 160, 9, 28},
  {cont__9_3, &frame__9_1, 160, 160, 6, 51},
  {cont__9_6, &frame__9_1, 160, 160, 3, 51}
};

union NODE {
  struct {
    FUNC type;
    ATTRIBUTES *attributes;
  };
  CONTINUATION continuation;
  CLOSURE closure;
};
static NODE *character__9;
static NODE *character__57;
static NODE *character__10;
static NODE *character__58;
static NODE *number__0;
static NODE *character__48;
static NODE *number__3;
static NODE *number__4;
static NODE *character__95;
static NODE *number__8;
static NODE *character__64;
static NODE *character__34;
static NODE *character__39;
static NODE *character__32;
static NODE *character__59;
static NODE *number__1;
static NODE *number__2;

static const char *used_namespaces[] = {
  "std",
  NULL
};

static MODULE_INFO module_info = {
  NULL,
  "basic__deserialize",
  continuation_info,
  sizeof(continuation_info)/sizeof(CONTINUATION_INFO),
  (NODE **)&var,
  var_names,
  sizeof(var_names)/sizeof(const char *),
  used_namespaces,
  {DEBUG_FILENAME("basic/deserialize.sim")}
};

/******
C O D E
******/

static int already_run = false;

EXPORT void run__basic__deserialize(void) {
  if (already_run) {
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  already_run = true;
  allocate_initialized_frame_gc(0, 0);
  // 23: ... alt(LETTER DIGIT)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__LETTER();
  arguments->slots[1] = get__DIGIT();
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__10_1;
}
static void cont__10_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__2 = arguments->slots[0];
  // 23: ... some(alt(LETTER DIGIT))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = temp__2;
  result_count = 1;
  myself = get__some();
  func = myself->type;
  frame->cont = cont__10_2;
}
static void cont__10_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__1 = arguments->slots[0];
  // 23: ... alt(LETTER DIGIT)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__LETTER();
  arguments->slots[1] = get__DIGIT();
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__10_3;
}
static void cont__10_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__6 = arguments->slots[0];
  // 23: ... many(alt(LETTER DIGIT))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = temp__6;
  result_count = 1;
  myself = get__many();
  func = myself->type;
  frame->cont = cont__10_4;
}
static void cont__10_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__5 = arguments->slots[0];
  // 23: ... '_', many(alt(LETTER DIGIT))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__95;
  arguments->slots[1] = temp__5;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__10_5;
}
static void cont__10_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__4 = arguments->slots[0];
  // 23: ... some('_', many(alt(LETTER DIGIT)))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = temp__4;
  result_count = 1;
  myself = get__some();
  func = myself->type;
  frame->cont = cont__10_6;
}
static void cont__10_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__3 = arguments->slots[0];
  // 23: $std::NAME LETTER, some(alt(LETTER DIGIT)), some('_', many(alt(LETTER DIGIT)))
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__LETTER();
  arguments->slots[1] = temp__1;
  arguments->slots[2] = temp__3;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__10_7;
}
static void cont__10_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var.std__NAME, arguments->slots[0]);
  // 24: ... "::", NAME
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__11_1;
  arguments->slots[1] = get__NAME();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__11_2;
}
static void cont__11_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__2 = arguments->slots[0];
  // 24: ... optional("::", NAME)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = temp__2;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__11_3;
}
static void cont__11_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  temp__1 = arguments->slots[0];
  // 24: $std::IDENTIFIER NAME, optional("::", NAME)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__NAME();
  arguments->slots[1] = temp__1;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__11_4;
}
static void cont__11_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var.std__IDENTIFIER, arguments->slots[0]);
  // 25: $$deserializers empty_table
  var._deserializers = get__empty_table();
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__4_1(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // tag: 0
  // deserializer: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 27: ... !deserializers(tag) deserializer
  frame->slots[2] /* temp__1 */ = frame->slots[1] /* deserializer */;
  // 27: ... !deserializers(tag)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* tag */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = var._deserializers;
  func = myself->type;
  frame->cont = cont__4_2;
}
static void cont__4_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._deserializers = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__5_1(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // text: 0
  // i: 1
  // n: 2
  // indent: 3
  frame->slots[1] /* i */ = create_cell();
  frame->slots[2] /* n */ = create_future();
  frame->slots[3] /* indent */ = create_cell();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* text */ = create_cell_with_contents(arguments->slots[0]);
  // 30: $$i 2
  ((CELL *)frame->slots[1])->contents /* i */ = number__2;
  // 31: $n length_of(text)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__5_2;
}
static void cont__5_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* n */, arguments->slots[0]);
  // 32: $$indent 0
  ((CELL *)frame->slots[3])->contents /* indent */ = number__0;
  // 33: ... -> i <= n && text(i) == '@ht;':
  // 34:   inc &i
  // 35:   plus &indent 8
  frame->slots[4] /* temp__1 */ = create_closure(entry__5_3, 0);
  // 33: while -> i <= n && text(i) == '@ht;':
  // 34:   inc &i
  // 35:   plus &indent 8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__while();
  func = myself->type;
  frame->cont = cont__5_13;
}
static void entry__5_10(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // i: 0
  // indent: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* i */
  frame->slots[1] = myself->closure.frame->slots[3]; /* indent */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 34: inc &i
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* i */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__5_11;
}
static void cont__5_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* i */ = arguments->slots[0];
  // 35: plus &indent 8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* indent */;
  arguments->slots[1] = number__8;
  result_count = 1;
  myself = get__plus();
  func = myself->type;
  frame->cont = cont__5_12;
}
static void cont__5_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* indent */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__5_3(void) {
  allocate_initialized_frame_gc(4, 9);
  // slot allocations:
  // n: 0
  // i: 1
  // text: 2
  // indent: 3
  frame->slots[0] = myself->closure.frame->slots[2]; /* n */
  frame->slots[1] = myself->closure.frame->slots[1]; /* i */
  frame->slots[2] = myself->closure.frame->slots[0]; /* text */
  frame->slots[3] = myself->closure.frame->slots[3]; /* indent */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 33: ... i <= n
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* n */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* i */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__5_4;
}
static void cont__5_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 33: ... i <= n
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__3 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__5_5;
}
static void cont__5_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 33: ... text(i) == '@ht;'
  frame->slots[7] /* temp__4 */ = create_closure(entry__5_6, 0);
  // 33: ... i <= n && text(i) == '@ht;'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__4 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__5_9;
}
static void entry__5_6(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // text: 0
  // i: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* text */
  frame->slots[1] = myself->closure.frame->slots[1]; /* i */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 33: ... text(i)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* i */;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* text */;
  func = myself->type;
  frame->cont = cont__5_7;
}
static void cont__5_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 33: ... text(i) == '@ht;'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = character__9;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__5_8;
}
static void cont__5_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 33: ... text(i) == '@ht;'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__5_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 33: ... :
  // 34:   inc &i
  // 35:   plus &indent 8
  frame->slots[8] /* temp__5 */ = create_closure(entry__5_10, 0);
  // 33: ... -> i <= n && text(i) == '@ht;':
  // 34:   inc &i
  // 35:   plus &indent 8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__5 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__5_13(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 36: ... -> i <= n && text(i) == ' ':
  // 37:   inc &i
  // 38:   inc &indent
  frame->slots[4] /* temp__1 */ = create_closure(entry__5_14, 0);
  // 36: while -> i <= n && text(i) == ' ':
  // 37:   inc &i
  // 38:   inc &indent
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__while();
  func = myself->type;
  frame->cont = cont__5_24;
}
static void entry__5_21(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // i: 0
  // indent: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* i */
  frame->slots[1] = myself->closure.frame->slots[3]; /* indent */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 37: inc &i
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* i */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__5_22;
}
static void cont__5_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* i */ = arguments->slots[0];
  // 38: inc &indent
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* indent */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__5_23;
}
static void cont__5_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* indent */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__5_14(void) {
  allocate_initialized_frame_gc(4, 9);
  // slot allocations:
  // n: 0
  // i: 1
  // text: 2
  // indent: 3
  frame->slots[0] = myself->closure.frame->slots[2]; /* n */
  frame->slots[1] = myself->closure.frame->slots[1]; /* i */
  frame->slots[2] = myself->closure.frame->slots[0]; /* text */
  frame->slots[3] = myself->closure.frame->slots[3]; /* indent */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 36: ... i <= n
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* n */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* i */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__5_15;
}
static void cont__5_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 36: ... i <= n
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__3 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__5_16;
}
static void cont__5_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 36: ... text(i) == ' '
  frame->slots[7] /* temp__4 */ = create_closure(entry__5_17, 0);
  // 36: ... i <= n && text(i) == ' '
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__4 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__5_20;
}
static void entry__5_17(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // text: 0
  // i: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* text */
  frame->slots[1] = myself->closure.frame->slots[1]; /* i */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 36: ... text(i)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* i */;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* text */;
  func = myself->type;
  frame->cont = cont__5_18;
}
static void cont__5_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 36: ... text(i) == ' '
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = character__32;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__5_19;
}
static void cont__5_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 36: ... text(i) == ' '
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__5_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 36: ... :
  // 37:   inc &i
  // 38:   inc &indent
  frame->slots[8] /* temp__5 */ = create_closure(entry__5_21, 0);
  // 36: ... -> i <= n && text(i) == ' ':
  // 37:   inc &i
  // 38:   inc &indent
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__5 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__5_24(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 39: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__5_25;
}
static void cont__5_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 39: range &text i -1
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* i */;
  arguments->slots[2] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__5_26;
}
static void cont__5_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* text */ = arguments->slots[0];
  // 40: -> indent
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  arguments->slots[1] = ((CELL *)frame->slots[3])->contents /* indent */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__6_12(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // text: 0
  // indent: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* text */
  frame->slots[1] = myself->closure.frame->slots[2]; /* indent */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 48: deserialize_stream text indent
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  arguments->slots[1] = frame->slots[1] /* indent */;
  result_count = frame->caller_result_count;
  myself = var._deserialize_stream;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__6_13(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 49: -> undefined undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  arguments->slots[1] = get__undefined();
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__6_9(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // text: 0
  // base_indent: 1
  // indent: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* text */
  frame->slots[1] = myself->closure.frame->slots[1]; /* base_indent */
  frame->slots[2] /* indent */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 45: $indent get_deserialization_indent(&text)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  result_count = 2;
  myself = get__get_deserialization_indent();
  func = myself->type;
  frame->cont = cont__6_10;
}
static void cont__6_10(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* text */ = arguments->slots[0];
  frame->slots[3] /* temp__1 */ = arguments->slots[1];
  // 45: ... indent
  initialize_future(frame->slots[2] /* indent */, frame->slots[3] /* temp__1 */);
  // 47: indent > base_indent
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* base_indent */;
  arguments->slots[1] = frame->slots[2] /* indent */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__6_11;
}
static void cont__6_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 47: ... :
  // 48:   deserialize_stream text indent
  frame->slots[4] /* temp__2 */ = create_closure(entry__6_12, 0);
  // 46: if
  // 47:   indent > base_indent:
  // 48:     deserialize_stream text indent
  // 49:   -> undefined undefined
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  arguments->slots[2] = func__6_13;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__6_14(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // text: 0
  // base_indent: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* text */
  frame->slots[1] = myself->closure.frame->slots[1]; /* base_indent */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 51: ... -> text(1) == ' ': range &text 2 -1
  frame->slots[2] /* temp__1 */ = create_closure(entry__6_15, 0);
  // 51: while -> text(1) == ' ': range &text 2 -1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__while();
  func = myself->type;
  frame->cont = cont__6_21;
}
static void entry__6_18(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // text: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* text */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 51: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__6_19;
}
static void cont__6_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 51: ... range &text 2 -1
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  arguments->slots[1] = number__2;
  arguments->slots[2] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__6_20;
}
static void cont__6_20(void) {
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
static void entry__6_15(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // text: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* text */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 51: ... text(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* text */;
  func = myself->type;
  frame->cont = cont__6_16;
}
static void cont__6_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 51: ... text(1) == ' '
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = character__32;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__6_17;
}
static void cont__6_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 51: ... : range &text 2 -1
  frame->slots[3] /* temp__3 */ = create_closure(entry__6_18, 0);
  // 51: ... -> text(1) == ' ': range &text 2 -1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__6_21(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 52: deserialize_stream text base_indent
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  arguments->slots[1] = frame->slots[1] /* base_indent */;
  result_count = frame->caller_result_count;
  myself = var._deserialize_stream;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__6_1(void) {
  allocate_initialized_frame_gc(2, 9);
  // slot allocations:
  // text: 0
  // base_indent: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* text */ = create_cell_with_contents(arguments->slots[0]);
  // 44: length_of(text)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__6_2;
}
static void cont__6_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__4 */ = arguments->slots[0];
  // 44: length_of(text) >= 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__4 */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__6_3;
}
static void cont__6_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 44: length_of(text) >= 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__6_4;
}
static void cont__6_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 44: ... text(1) == '@nl;'
  frame->slots[6] /* temp__5 */ = create_closure(entry__6_5, 0);
  // 44: length_of(text) >= 1 && text(1) == '@nl;'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[6] /* temp__5 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__6_8;
}
static void entry__6_5(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // text: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* text */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 44: ... text(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* text */;
  func = myself->type;
  frame->cont = cont__6_6;
}
static void cont__6_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 44: ... text(1) == '@nl;'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = character__10;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__6_7;
}
static void cont__6_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 44: ... text(1) == '@nl;'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__6_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 44: ... :
  // 45:   $indent get_deserialization_indent(&text)
  // 46:   if
  // 47:     indent > base_indent:
  // 48:       deserialize_stream text indent
  // 49:     -> undefined undefined
  frame->slots[7] /* temp__6 */ = create_closure(entry__6_9, 0);
  // 50: :
  // 51:   while -> text(1) == ' ': range &text 2 -1
  // 52:   deserialize_stream text base_indent
  frame->slots[8] /* temp__7 */ = create_closure(entry__6_14, 0);
  // 43: if
  // 44:   length_of(text) >= 1 && text(1) == '@nl;':
  // 45:     $indent get_deserialization_indent(&text)
  // 46:     if
  // 47:       indent > base_indent:
  // 48:         deserialize_stream text indent
  // 49:       -> undefined undefined
  // 50:   :
  // 51:     while -> text(1) == ' ': range &text 2 -1
  // 52:     deserialize_stream text base_indent
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__6 */;
  arguments->slots[2] = frame->slots[8] /* temp__7 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_7(void) {
  allocate_initialized_frame_gc(6, 11);
  // slot allocations:
  // text: 0
  // base_indent: 1
  // return: 2
  // prototype: 3
  // name: 4
  // attribute_setters: 5
  // obj: 6
  frame->slots[2] /* return */ = create_continuation();
  frame->slots[3] = myself->closure.frame->slots[1]; /* prototype */
  frame->slots[4] = myself->closure.frame->slots[0]; /* name */
  frame->slots[5] = myself->closure.frame->slots[3]; /* attribute_setters */
  frame->slots[6] /* obj */ = create_cell();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* text */ = create_cell_with_contents(arguments->slots[0]);
  // 64: ... text .has_prefix. "()"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  arguments->slots[1] = string__7_8;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__7_9;
}
static void cont__7_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 64: ... : return range(text 3 -1) prototype
  frame->slots[8] /* temp__2 */ = create_closure(entry__7_10, 0);
  // 64: if text .has_prefix. "()": return range(text 3 -1) prototype
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__7_13;
}
static void entry__7_10(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // return: 0
  // text: 1
  // prototype: 2
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  frame->slots[1] = myself->closure.frame->slots[0]; /* text */
  frame->slots[2] = myself->closure.frame->slots[3]; /* prototype */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 64: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__7_11;
}
static void cont__7_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 64: ... range(text 3 -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* text */;
  arguments->slots[1] = number__3;
  arguments->slots[2] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__7_12;
}
static void cont__7_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 64: ... return range(text 3 -1) prototype
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* prototype */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_13(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 65: ... text(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* text */;
  func = myself->type;
  frame->cont = cont__7_14;
}
static void cont__7_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__3 */ = arguments->slots[0];
  // 65: ... text(1) != '@nl;'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__3 */;
  arguments->slots[1] = character__10;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__7_15;
}
static void cont__7_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__2 */ = arguments->slots[0];
  // 65: ... text(1) != '@nl;'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__7_16;
}
static void cont__7_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 65: ... :
  // 66:   raise "Invalid @(name) object encountered during deserialisation!"
  frame->slots[10] /* temp__4 */ = create_closure(entry__7_17, 0);
  // 65: if text(1) != '@nl;':
  // 66:   raise "Invalid @(name) object encountered during deserialisation!"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[10] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__7_21;
}
static void entry__7_17(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[4]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 66: ... "Invalid @(name) object encountered during deserialisation!"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__7_18;
  arguments->slots[1] = frame->slots[0] /* name */;
  arguments->slots[2] = string__7_19;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_20;
}
static void cont__7_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 66: raise "Invalid @(name) object encountered during deserialisation!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__raise();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_21(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 67: $$obj prototype
  ((CELL *)frame->slots[6])->contents /* obj */ = frame->slots[3] /* prototype */;
  // 68: ... :
  // 69:   if length_of(text) == 0 || text(1) != '@nl;': return text obj
  // 70:   get_deserialization_indent $remaining_text $indent text
  // 71:   if indent <= base_indent: return text obj
  // 72:   !text remaining_text
  // 73:   match text IDENTIFIER $len
  // 74:   if len.is_undefined || text(len+1) != ':':
  // 75:     raise "Encountered invalid @(name) component during deserialisation!"
  // 76:   $tag range(text 1 len)
  // 77:   $attribute_setter attribute_setters(tag)
  // ...
  frame->slots[7] /* temp__1 */ = create_closure(entry__7_22, 0);
  // 68: forever:
  // 69:   if length_of(text) == 0 || text(1) != '@nl;': return text obj
  // 70:   get_deserialization_indent $remaining_text $indent text
  // 71:   if indent <= base_indent: return text obj
  // 72:   !text remaining_text
  // 73:   match text IDENTIFIER $len
  // 74:   if len.is_undefined || text(len+1) != ':':
  // 75:     raise "Encountered invalid @(name) component during deserialisation!"
  // 76:   $tag range(text 1 len)
  // 77:   $attribute_setter attribute_setters(tag)
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__forever();
  func = myself->type;
  frame->cont = cont__7_63;
}
static void entry__7_22(void) {
  allocate_initialized_frame_gc(6, 16);
  // slot allocations:
  // text: 0
  // return: 1
  // obj: 2
  // base_indent: 3
  // name: 4
  // attribute_setters: 5
  // remaining_text: 6
  // indent: 7
  // len: 8
  // tag: 9
  // attribute_setter: 10
  frame->slots[0] = myself->closure.frame->slots[0]; /* text */
  frame->slots[1] = myself->closure.frame->slots[2]; /* return */
  frame->slots[2] = myself->closure.frame->slots[6]; /* obj */
  frame->slots[3] = myself->closure.frame->slots[1]; /* base_indent */
  frame->slots[4] = myself->closure.frame->slots[4]; /* name */
  frame->slots[5] = myself->closure.frame->slots[5]; /* attribute_setters */
  frame->slots[6] /* remaining_text */ = create_future();
  frame->slots[7] /* indent */ = create_future();
  frame->slots[8] /* len */ = create_future();
  frame->slots[9] /* tag */ = create_future();
  frame->slots[10] /* attribute_setter */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 69: ... length_of(text)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__7_23;
}
static void cont__7_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__3 */ = arguments->slots[0];
  // 69: ... length_of(text) == 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[13] /* temp__3 */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__7_24;
}
static void cont__7_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__2 */ = arguments->slots[0];
  // 69: ... text(1) != '@nl;'
  frame->slots[14] /* temp__4 */ = create_closure(entry__7_25, 0);
  // 69: ... length_of(text) == 0 || text(1) != '@nl;'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[12] /* temp__2 */;
  arguments->slots[1] = frame->slots[14] /* temp__4 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__7_29;
}
static void entry__7_25(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // text: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* text */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 69: ... text(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* text */;
  func = myself->type;
  frame->cont = cont__7_26;
}
static void cont__7_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 69: ... text(1) != '@nl;'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  arguments->slots[1] = character__10;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__7_27;
}
static void cont__7_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 69: ... text(1) != '@nl;'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__7_28;
}
static void cont__7_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 69: ... text(1) != '@nl;'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__7_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 69: ... : return text obj
  frame->slots[15] /* temp__5 */ = create_closure(entry__7_30, 0);
  // 69: if length_of(text) == 0 || text(1) != '@nl;': return text obj
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__1 */;
  arguments->slots[1] = frame->slots[15] /* temp__5 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__7_31;
}
static void entry__7_30(void) {
  allocate_initialized_frame_gc(3, 3);
  // slot allocations:
  // return: 0
  // text: 1
  // obj: 2
  frame->slots[0] = myself->closure.frame->slots[1]; /* return */
  frame->slots[1] = myself->closure.frame->slots[0]; /* text */
  frame->slots[2] = myself->closure.frame->slots[2]; /* obj */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 69: ... return text obj
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* text */;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* obj */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_31(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 70: get_deserialization_indent $remaining_text $indent text
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  result_count = 2;
  myself = get__get_deserialization_indent();
  func = myself->type;
  frame->cont = cont__7_32;
}
static void cont__7_32(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  frame->slots[12] /* temp__2 */ = arguments->slots[1];
  // 70: ... remaining_text
  initialize_future(frame->slots[6] /* remaining_text */, frame->slots[11] /* temp__1 */);
  // 70: ... indent
  initialize_future(frame->slots[7] /* indent */, frame->slots[12] /* temp__2 */);
  // 71: ... indent <= base_indent
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* base_indent */;
  arguments->slots[1] = frame->slots[7] /* indent */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__7_33;
}
static void cont__7_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__2 */ = arguments->slots[0];
  // 71: ... indent <= base_indent
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[12] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__7_34;
}
static void cont__7_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 71: ... : return text obj
  frame->slots[13] /* temp__3 */ = create_closure(entry__7_35, 0);
  // 71: if indent <= base_indent: return text obj
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__1 */;
  arguments->slots[1] = frame->slots[13] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__7_36;
}
static void entry__7_35(void) {
  allocate_initialized_frame_gc(3, 3);
  // slot allocations:
  // return: 0
  // text: 1
  // obj: 2
  frame->slots[0] = myself->closure.frame->slots[1]; /* return */
  frame->slots[1] = myself->closure.frame->slots[0]; /* text */
  frame->slots[2] = myself->closure.frame->slots[2]; /* obj */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 71: ... return text obj
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* text */;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* obj */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_36(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 72: !text remaining_text
  ((CELL *)frame->slots[0])->contents /* text */ = frame->slots[6] /* remaining_text */;
  // 73: match text IDENTIFIER $len
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  arguments->slots[1] = get__IDENTIFIER();
  result_count = 1;
  myself = get__match();
  func = myself->type;
  frame->cont = cont__7_37;
}
static void cont__7_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[8] /* len */, arguments->slots[0]);
  // 74: ... len.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* len */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__7_38;
}
static void cont__7_38(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__2 */ = arguments->slots[0];
  // 74: ... text(len+1) != ':'
  frame->slots[13] /* temp__3 */ = create_closure(entry__7_39, 0);
  // 74: ... len.is_undefined || text(len+1) != ':'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[12] /* temp__2 */;
  arguments->slots[1] = frame->slots[13] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__7_44;
}
static void entry__7_39(void) {
  allocate_initialized_frame_gc(2, 6);
  // slot allocations:
  // text: 0
  // len: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* text */
  frame->slots[1] = myself->closure.frame->slots[8]; /* len */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 74: ... len+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* len */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__7_40;
}
static void cont__7_40(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__4 */ = arguments->slots[0];
  // 74: ... text(len+1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__4 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* text */;
  func = myself->type;
  frame->cont = cont__7_41;
}
static void cont__7_41(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 74: ... text(len+1) != ':'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  arguments->slots[1] = character__58;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__7_42;
}
static void cont__7_42(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 74: ... text(len+1) != ':'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__7_43;
}
static void cont__7_43(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 74: ... text(len+1) != ':'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__7_44(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 74: ... :
  // 75:   raise "Encountered invalid @(name) component during deserialisation!"
  frame->slots[14] /* temp__4 */ = create_closure(entry__7_45, 0);
  // 74: if len.is_undefined || text(len+1) != ':':
  // 75:   raise "Encountered invalid @(name) component during deserialisation!"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__1 */;
  arguments->slots[1] = frame->slots[14] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__7_49;
}
static void entry__7_45(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[4]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 75: ... "Encountered invalid @(name) component during deserialisation!"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__7_46;
  arguments->slots[1] = frame->slots[0] /* name */;
  arguments->slots[2] = string__7_47;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_48;
}
static void cont__7_48(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 75: raise "Encountered invalid @(name) component during deserialisation!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__raise();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_49(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 76: $tag range(text 1 len)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[8] /* len */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__7_50;
}
static void cont__7_50(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[9] /* tag */, arguments->slots[0]);
  // 77: $attribute_setter attribute_setters(tag)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* tag */;
  result_count = 1;
  myself = ((CELL *)frame->slots[5])->contents /* attribute_setters */;
  func = myself->type;
  frame->cont = cont__7_51;
}
static void cont__7_51(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[10] /* attribute_setter */, arguments->slots[0]);
  // 78: ... attribute_setter.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* attribute_setter */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__7_52;
}
static void cont__7_52(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 78: ... :
  // 79:   raise "Encountered unknown @(name) component during deserialisation!"
  frame->slots[12] /* temp__2 */ = create_closure(entry__7_53, 0);
  // 78: if attribute_setter.is_undefined:
  // 79:   raise "Encountered unknown @(name) component during deserialisation!"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__1 */;
  arguments->slots[1] = frame->slots[12] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__7_57;
}
static void entry__7_53(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[4]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 79: ... "Encountered unknown @(name) component during deserialisation!"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__7_54;
  arguments->slots[1] = frame->slots[0] /* name */;
  arguments->slots[2] = string__7_55;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_56;
}
static void cont__7_56(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 79: raise "Encountered unknown @(name) component during deserialisation!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__raise();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_57(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 80: ... len+2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* len */;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__7_58;
}
static void cont__7_58(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 80: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__7_59;
}
static void cont__7_59(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__2 */ = arguments->slots[0];
  // 80: range &text len+2 -1
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  arguments->slots[1] = frame->slots[11] /* temp__1 */;
  arguments->slots[2] = frame->slots[12] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__7_60;
}
static void cont__7_60(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* text */ = arguments->slots[0];
  // 81: ... deserialize_item(&text indent)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  arguments->slots[1] = frame->slots[7] /* indent */;
  result_count = 2;
  myself = get__deserialize_item();
  func = myself->type;
  frame->cont = cont__7_61;
}
static void cont__7_61(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* text */ = arguments->slots[0];
  frame->slots[11] /* temp__1 */ = arguments->slots[1];
  // 81: attribute_setter &obj deserialize_item(&text indent)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* obj */;
  arguments->slots[1] = frame->slots[11] /* temp__1 */;
  result_count = 1;
  myself = frame->slots[10] /* attribute_setter */;
  func = myself->type;
  frame->cont = cont__7_62;
}
static void cont__7_62(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* obj */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__7_63(void) {
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__7_1(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // name: 0
  // prototype: 1
  // attributes: 2
  // attribute_setters: 3
  frame->slots[3] /* attribute_setters */ = create_cell();
  if (argument_count < 2) {
    too_few_arguments_error();
    return;
  }
  frame->slots[0] /* name */ = arguments->slots[0];
  frame->slots[1] /* prototype */ = arguments->slots[1];
  frame->slots[2] /* attributes */ = from_arguments(2, argument_count-2);
  // 55: $$attribute_setters empty_table
  ((CELL *)frame->slots[3])->contents /* attribute_setters */ = get__empty_table();
  // 56: ... : (attribute_name attribute_setter)
  // 57:   !attribute_setters(range(attribute_name 3 -1)) attribute_setter
  frame->slots[4] /* temp__1 */ = create_closure(entry__7_2, 2);
  // 56: for_each_pair attributes: (attribute_name attribute_setter)
  // 57:   !attribute_setters(range(attribute_name 3 -1)) attribute_setter
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* attributes */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__for_each_pair();
  func = myself->type;
  frame->cont = cont__7_6;
}
static void entry__7_2(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // attribute_name: 0
  // attribute_setter: 1
  // attribute_setters: 2
  frame->slots[2] = myself->closure.frame->slots[3]; /* attribute_setters */
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 57: !attribute_setters(range(attribute_name 3 -1)) attribute_setter
  frame->slots[3] /* temp__1 */ = frame->slots[1] /* attribute_setter */;
  // 57: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__7_3;
}
static void cont__7_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 57: ... range(attribute_name 3 -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* attribute_name */;
  arguments->slots[1] = number__3;
  arguments->slots[2] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__7_4;
}
static void cont__7_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 57: !attribute_setters(range(attribute_name 3 -1))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[2])->contents /* attribute_setters */;
  func = myself->type;
  frame->cont = cont__7_5;
}
static void cont__7_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* attribute_setters */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__7_6(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 58: ... :
  // 59:   (
  // 60:     $text
  // 61:     base_indent
  // 62:     -> return
  // 63:   )
  // 64:   if text .has_prefix. "()": return range(text 3 -1) prototype
  // 65:   if text(1) != '@nl;':
  // 66:     raise "Invalid @(name) object encountered during deserialisation!"
  // 67:   $$obj prototype
  // ...
  frame->slots[4] /* temp__1 */ = create_closure(entry__7_7, 2);
  // 58: -> :
  // 59:   (
  // 60:     $text
  // 61:     base_indent
  // 62:     -> return
  // 63:   )
  // 64:   if text .has_prefix. "()": return range(text 3 -1) prototype
  // 65:   if text(1) != '@nl;':
  // 66:     raise "Invalid @(name) object encountered during deserialisation!"
  // 67:   $$obj prototype
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__8_1(void) {
  allocate_initialized_frame_gc(3, 9);
  // slot allocations:
  // text: 0
  // indent: 1
  // return: 2
  frame->slots[2] /* return */ = create_continuation();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* text */ = create_cell_with_contents(arguments->slots[0]);
  // 90: text(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* text */;
  func = myself->type;
  frame->cont = cont__8_2;
}
static void cont__8_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  //  91: ... :
  //  92:   $$str ""
  //  93:   $$i 2
  //  94:   $n length_of(text)
  //  95:   while -> i <= n:
  //  96:     $chr text(i)
  //  97:     case
  //  98:       chr
  //  99:       '@quot;':
  // 100:         return range(text i+1 -1) str
  // ...
  frame->slots[4] /* temp__2 */ = create_closure(entry__8_3, 0);
  // 112: ... :
  // 113:   $n length_of(text)
  // 114:   if n < 3:
  // 115:     raise "Invalid character constant encountered during deserialization!"
  // 116:   $chr text(2)
  // 117:   if
  // 118:     chr == '@@':
  // 119:       $escape_text range(text 3 -1)
  // 120:       parse_integer escape_text $rest_text $value
  // 121:       $i 3+length_of(escape_text)-length_of(rest_text)
  // ...
  frame->slots[5] /* temp__3 */ = create_closure(entry__8_44, 0);
  // 137: '0' .. '9'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__48;
  arguments->slots[1] = character__57;
  result_count = 1;
  myself = get__std__value_range();
  func = myself->type;
  frame->cont = cont__8_92;
}
static void entry__8_52(void) {
  allocate_initialized_frame_gc(3, 11);
  // slot allocations:
  // text: 0
  // n: 1
  // return: 2
  // escape_text: 3
  // rest_text: 4
  // value: 5
  // i: 6
  frame->slots[0] = myself->closure.frame->slots[0]; /* text */
  frame->slots[1] = myself->closure.frame->slots[2]; /* n */
  frame->slots[2] = myself->closure.frame->slots[1]; /* return */
  frame->slots[3] /* escape_text */ = create_future();
  frame->slots[4] /* rest_text */ = create_future();
  frame->slots[5] /* value */ = create_future();
  frame->slots[6] /* i */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 119: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__8_53;
}
static void cont__8_53(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 119: $escape_text range(text 3 -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  arguments->slots[1] = number__3;
  arguments->slots[2] = frame->slots[7] /* temp__1 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__8_54;
}
static void cont__8_54(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* escape_text */, arguments->slots[0]);
  // 120: parse_integer escape_text $rest_text $value
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* escape_text */;
  result_count = 2;
  myself = get__parse_integer();
  func = myself->type;
  frame->cont = cont__8_55;
}
static void cont__8_55(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  frame->slots[8] /* temp__2 */ = arguments->slots[1];
  // 120: ... rest_text
  initialize_future(frame->slots[4] /* rest_text */, frame->slots[7] /* temp__1 */);
  // 120: ... value
  initialize_future(frame->slots[5] /* value */, frame->slots[8] /* temp__2 */);
  // 121: ... length_of(escape_text)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* escape_text */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__8_56;
}
static void cont__8_56(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__2 */ = arguments->slots[0];
  // 121: ... 3+length_of(escape_text)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__3;
  arguments->slots[1] = frame->slots[8] /* temp__2 */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__8_57;
}
static void cont__8_57(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 121: ... length_of(rest_text)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* rest_text */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__8_58;
}
static void cont__8_58(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__3 */ = arguments->slots[0];
  // 121: $i 3+length_of(escape_text)-length_of(rest_text)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[9] /* temp__3 */;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__8_59;
}
static void cont__8_59(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* i */, arguments->slots[0]);
  // 124: value.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* value */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__8_60;
}
static void cont__8_60(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__2 */ = arguments->slots[0];
  frame->slots[9] /* temp__3 */ = create_closure(entry__8_61, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__2 */;
  arguments->slots[1] = frame->slots[9] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__8_75;
}
static void entry__8_61(void) {
  allocate_initialized_frame_gc(3, 7);
  // slot allocations:
  // n: 0
  // i: 1
  // text: 2
  frame->slots[0] = myself->closure.frame->slots[1]; /* n */
  frame->slots[1] = myself->closure.frame->slots[6]; /* i */
  frame->slots[2] = myself->closure.frame->slots[0]; /* text */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 125: i+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* i */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__8_62;
}
static void cont__8_62(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 125: i+1 > n
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* n */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__8_63;
}
static void cont__8_63(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  frame->slots[6] /* temp__4 */ = create_closure(entry__8_64, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[6] /* temp__4 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__8_74;
}
static void entry__8_64(void) {
  allocate_initialized_frame_gc(2, 7);
  // slot allocations:
  // text: 0
  // i: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* text */
  frame->slots[1] = myself->closure.frame->slots[1]; /* i */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 126: text(i)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* i */;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* text */;
  func = myself->type;
  frame->cont = cont__8_65;
}
static void cont__8_65(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__4 */ = arguments->slots[0];
  // 126: text(i) != ';'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__4 */;
  arguments->slots[1] = character__59;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__8_66;
}
static void cont__8_66(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 126: text(i) != ';'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__8_67;
}
static void cont__8_67(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 127: text(i+1) != '@apos;'
  frame->slots[6] /* temp__5 */ = create_closure(entry__8_68, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[6] /* temp__5 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__8_73;
}
static void entry__8_68(void) {
  allocate_initialized_frame_gc(2, 6);
  // slot allocations:
  // text: 0
  // i: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* text */
  frame->slots[1] = myself->closure.frame->slots[1]; /* i */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 127: ... i+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* i */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__8_69;
}
static void cont__8_69(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__4 */ = arguments->slots[0];
  // 127: text(i+1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__4 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* text */;
  func = myself->type;
  frame->cont = cont__8_70;
}
static void cont__8_70(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 127: text(i+1) != '@apos;'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  arguments->slots[1] = character__39;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__8_71;
}
static void cont__8_71(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 127: text(i+1) != '@apos;'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__8_72;
}
static void cont__8_72(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 127: text(i+1) != '@apos;'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__8_73(void) {
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
static void cont__8_74(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__8_75(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 122: if
  // 123:   ||
  // 124:     value.is_undefined
  // 125:     i+1 > n
  // 126:     text(i) != ';'
  // 127:     text(i+1) != '@apos;'
  // 128:   :
  // 129:     raise
  // 130:       "Invalid character escape encountered during deserialization!"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = func__8_76;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__8_78;
}
static void entry__8_76(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 129: raise
  // 130:   "Invalid character escape encountered during deserialization!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__8_77;
  result_count = frame->caller_result_count;
  myself = get__raise();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__8_78(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 131: ... i+2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* i */;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__8_79;
}
static void cont__8_79(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__2 */ = arguments->slots[0];
  // 131: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__8_80;
}
static void cont__8_80(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__3 */ = arguments->slots[0];
  // 131: ... range(text i+2 -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  arguments->slots[1] = frame->slots[8] /* temp__2 */;
  arguments->slots[2] = frame->slots[9] /* temp__3 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__8_81;
}
static void cont__8_81(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 131: ... character(value)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* value */;
  result_count = 1;
  myself = get__character();
  func = myself->type;
  frame->cont = cont__8_82;
}
static void cont__8_82(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__4 */ = arguments->slots[0];
  // 131: return range(text i+2 -1) character(value)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[10] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__8_83(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // text: 0
  // return: 1
  // chr: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* text */
  frame->slots[1] = myself->closure.frame->slots[1]; /* return */
  frame->slots[2] = myself->closure.frame->slots[3]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 133: ... text(3)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__3;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* text */;
  func = myself->type;
  frame->cont = cont__8_84;
}
static void cont__8_84(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 133: ... text(3) != '@apos;'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__3 */;
  arguments->slots[1] = character__39;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__8_85;
}
static void cont__8_85(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 133: ... text(3) != '@apos;'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__8_86;
}
static void cont__8_86(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 133: if text(3) != '@apos;':
  // 134:   raise
  // 135:     "Invalid character constant encountered during deserialization!"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = func__8_87;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__8_89;
}
static void entry__8_87(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 134: raise
  // 135:   "Invalid character constant encountered during deserialization!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__8_88;
  result_count = frame->caller_result_count;
  myself = get__raise();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__8_89(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 136: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__8_90;
}
static void cont__8_90(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 136: ... range(text 4 -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  arguments->slots[1] = number__4;
  arguments->slots[2] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__8_91;
}
static void cont__8_91(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 136: return range(text 4 -1) chr
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* chr */;
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__8_3(void) {
  allocate_initialized_frame_gc(2, 6);
  // slot allocations:
  // text: 0
  // return: 1
  // str: 2
  // i: 3
  // n: 4
  frame->slots[0] = myself->closure.frame->slots[0]; /* text */
  frame->slots[1] = myself->closure.frame->slots[2]; /* return */
  frame->slots[2] /* str */ = create_cell();
  frame->slots[3] /* i */ = create_cell();
  frame->slots[4] /* n */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 92: $$str ""
  ((CELL *)frame->slots[2])->contents /* str */ = empty_string;
  // 93: $$i 2
  ((CELL *)frame->slots[3])->contents /* i */ = number__2;
  // 94: $n length_of(text)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__8_4;
}
static void cont__8_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* n */, arguments->slots[0]);
  //  95: ... -> i <= n:
  //  96:   $chr text(i)
  //  97:   case
  //  98:     chr
  //  99:     '@quot;':
  // 100:       return range(text i+1 -1) str
  // 101:     '@@':
  // 102:       $escape_text range(text i+1 -1)
  // 103:       parse_integer escape_text $rest_text $value
  // 104:       plus &i 1+length_of(escape_text)-length_of(rest_text)
  // ...
  frame->slots[5] /* temp__1 */ = create_closure(entry__8_5, 0);
  //  95: while -> i <= n:
  //  96:   $chr text(i)
  //  97:   case
  //  98:     chr
  //  99:     '@quot;':
  // 100:       return range(text i+1 -1) str
  // 101:     '@@':
  // 102:       $escape_text range(text i+1 -1)
  // 103:       parse_integer escape_text $rest_text $value
  // 104:       plus &i 1+length_of(escape_text)-length_of(rest_text)
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  result_count = 0;
  myself = get__while();
  func = myself->type;
  frame->cont = cont__8_42;
}
static void entry__8_8(void) {
  allocate_initialized_frame_gc(5, 9);
  // slot allocations:
  // text: 0
  // i: 1
  // return: 2
  // str: 3
  // n: 4
  // chr: 5
  frame->slots[0] = myself->closure.frame->slots[2]; /* text */
  frame->slots[1] = myself->closure.frame->slots[1]; /* i */
  frame->slots[2] = myself->closure.frame->slots[3]; /* return */
  frame->slots[3] = myself->closure.frame->slots[4]; /* str */
  frame->slots[4] = myself->closure.frame->slots[0]; /* n */
  frame->slots[5] /* chr */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 96: $chr text(i)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* i */;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* text */;
  func = myself->type;
  frame->cont = cont__8_9;
}
static void cont__8_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* chr */, arguments->slots[0]);
  //  99: ... :
  // 100:   return range(text i+1 -1) str
  frame->slots[6] /* temp__1 */ = create_closure(entry__8_10, 0);
  // 101: ... :
  // 102:   $escape_text range(text i+1 -1)
  // 103:   parse_integer escape_text $rest_text $value
  // 104:   plus &i 1+length_of(escape_text)-length_of(rest_text)
  // 105:   if value.is_undefined || i > n || text(i) != ';':
  // 106:     raise "Invalid string escape encountered during deserialization!"
  // 107:   push &str character(value)
  frame->slots[7] /* temp__2 */ = create_closure(entry__8_14, 0);
  // 108: :
  // 109:   push &str chr
  frame->slots[8] /* temp__3 */ = create_closure(entry__8_38, 0);
  //  97: case
  //  98:   chr
  //  99:   '@quot;':
  // 100:     return range(text i+1 -1) str
  // 101:   '@@':
  // 102:     $escape_text range(text i+1 -1)
  // 103:     parse_integer escape_text $rest_text $value
  // 104:     plus &i 1+length_of(escape_text)-length_of(rest_text)
  // 105:     if value.is_undefined || i > n || text(i) != ';':
  // 106:       raise "Invalid string escape encountered during deserialization!"
  // ...
  argument_count = 6;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* chr */;
  arguments->slots[1] = character__34;
  arguments->slots[2] = frame->slots[6] /* temp__1 */;
  arguments->slots[3] = character__64;
  arguments->slots[4] = frame->slots[7] /* temp__2 */;
  arguments->slots[5] = frame->slots[8] /* temp__3 */;
  result_count = 0;
  myself = get__case();
  func = myself->type;
  frame->cont = cont__8_40;
}
static void entry__8_10(void) {
  allocate_initialized_frame_gc(4, 7);
  // slot allocations:
  // return: 0
  // text: 1
  // i: 2
  // str: 3
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  frame->slots[1] = myself->closure.frame->slots[0]; /* text */
  frame->slots[2] = myself->closure.frame->slots[1]; /* i */
  frame->slots[3] = myself->closure.frame->slots[3]; /* str */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 100: ... i+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* i */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__8_11;
}
static void cont__8_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 100: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__8_12;
}
static void cont__8_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 100: ... range(text i+1 -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* text */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  arguments->slots[2] = frame->slots[6] /* temp__3 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__8_13;
}
static void cont__8_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 100: return range(text i+1 -1) str
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = ((CELL *)frame->slots[3])->contents /* str */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__8_14(void) {
  allocate_initialized_frame_gc(4, 11);
  // slot allocations:
  // text: 0
  // i: 1
  // n: 2
  // str: 3
  // escape_text: 4
  // rest_text: 5
  // value: 6
  frame->slots[0] = myself->closure.frame->slots[0]; /* text */
  frame->slots[1] = myself->closure.frame->slots[1]; /* i */
  frame->slots[2] = myself->closure.frame->slots[4]; /* n */
  frame->slots[3] = myself->closure.frame->slots[3]; /* str */
  frame->slots[4] /* escape_text */ = create_future();
  frame->slots[5] /* rest_text */ = create_future();
  frame->slots[6] /* value */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 102: ... i+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* i */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__8_15;
}
static void cont__8_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 102: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__8_16;
}
static void cont__8_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__2 */ = arguments->slots[0];
  // 102: $escape_text range(text i+1 -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  arguments->slots[1] = frame->slots[7] /* temp__1 */;
  arguments->slots[2] = frame->slots[8] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__8_17;
}
static void cont__8_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* escape_text */, arguments->slots[0]);
  // 103: parse_integer escape_text $rest_text $value
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* escape_text */;
  result_count = 2;
  myself = get__parse_integer();
  func = myself->type;
  frame->cont = cont__8_18;
}
static void cont__8_18(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  frame->slots[8] /* temp__2 */ = arguments->slots[1];
  // 103: ... rest_text
  initialize_future(frame->slots[5] /* rest_text */, frame->slots[7] /* temp__1 */);
  // 103: ... value
  initialize_future(frame->slots[6] /* value */, frame->slots[8] /* temp__2 */);
  // 104: ... length_of(escape_text)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* escape_text */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__8_19;
}
static void cont__8_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__3 */ = arguments->slots[0];
  // 104: ... 1+length_of(escape_text)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__1;
  arguments->slots[1] = frame->slots[9] /* temp__3 */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__8_20;
}
static void cont__8_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__2 */ = arguments->slots[0];
  // 104: ... length_of(rest_text)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* rest_text */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__8_21;
}
static void cont__8_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__4 */ = arguments->slots[0];
  // 104: ... 1+length_of(escape_text)-length_of(rest_text)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__2 */;
  arguments->slots[1] = frame->slots[10] /* temp__4 */;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__8_22;
}
static void cont__8_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 104: plus &i 1+length_of(escape_text)-length_of(rest_text)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* i */;
  arguments->slots[1] = frame->slots[7] /* temp__1 */;
  result_count = 1;
  myself = get__plus();
  func = myself->type;
  frame->cont = cont__8_23;
}
static void cont__8_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* i */ = arguments->slots[0];
  // 105: ... value.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* value */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__8_24;
}
static void cont__8_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__2 */ = arguments->slots[0];
  // 105: ... i > n || text(i) != ';'
  frame->slots[9] /* temp__3 */ = create_closure(entry__8_25, 0);
  // 105: ... value.is_undefined || i > n || text(i) != ';'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__2 */;
  arguments->slots[1] = frame->slots[9] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__8_32;
}
static void entry__8_25(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // n: 0
  // i: 1
  // text: 2
  frame->slots[0] = myself->closure.frame->slots[2]; /* n */
  frame->slots[1] = myself->closure.frame->slots[1]; /* i */
  frame->slots[2] = myself->closure.frame->slots[0]; /* text */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 105: ... i > n
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* n */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* i */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__8_26;
}
static void cont__8_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 105: ... text(i) != ';'
  frame->slots[5] /* temp__3 */ = create_closure(entry__8_27, 0);
  // 105: ... i > n || text(i) != ';'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__8_31;
}
static void entry__8_27(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // text: 0
  // i: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* text */
  frame->slots[1] = myself->closure.frame->slots[1]; /* i */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 105: ... text(i)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* i */;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* text */;
  func = myself->type;
  frame->cont = cont__8_28;
}
static void cont__8_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 105: ... text(i) != ';'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  arguments->slots[1] = character__59;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__8_29;
}
static void cont__8_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 105: ... text(i) != ';'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__8_30;
}
static void cont__8_30(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 105: ... text(i) != ';'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__8_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 105: ... i > n || text(i) != ';'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__8_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 105: if value.is_undefined || i > n || text(i) != ';':
  // 106:   raise "Invalid string escape encountered during deserialization!"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = func__8_33;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__8_35;
}
static void entry__8_33(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 106: raise "Invalid string escape encountered during deserialization!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__8_34;
  result_count = frame->caller_result_count;
  myself = get__raise();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__8_35(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 107: ... character(value)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* value */;
  result_count = 1;
  myself = get__character();
  func = myself->type;
  frame->cont = cont__8_36;
}
static void cont__8_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 107: push &str character(value)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* str */;
  arguments->slots[1] = frame->slots[7] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__8_37;
}
static void cont__8_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* str */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__8_38(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // str: 0
  // chr: 1
  frame->slots[0] = myself->closure.frame->slots[3]; /* str */
  frame->slots[1] = myself->closure.frame->slots[5]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 109: push &str chr
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* str */;
  arguments->slots[1] = frame->slots[1] /* chr */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__8_39;
}
static void cont__8_39(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* str */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__8_40(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 110: inc &i
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* i */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__8_41;
}
static void cont__8_41(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* i */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__8_5(void) {
  allocate_initialized_frame_gc(5, 8);
  // slot allocations:
  // n: 0
  // i: 1
  // text: 2
  // return: 3
  // str: 4
  frame->slots[0] = myself->closure.frame->slots[4]; /* n */
  frame->slots[1] = myself->closure.frame->slots[3]; /* i */
  frame->slots[2] = myself->closure.frame->slots[0]; /* text */
  frame->slots[3] = myself->closure.frame->slots[1]; /* return */
  frame->slots[4] = myself->closure.frame->slots[2]; /* str */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 95: ... i <= n
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* n */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* i */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__8_6;
}
static void cont__8_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 95: ... i <= n
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__8_7;
}
static void cont__8_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  //  95: ... :
  //  96:   $chr text(i)
  //  97:   case
  //  98:     chr
  //  99:     '@quot;':
  // 100:       return range(text i+1 -1) str
  // 101:     '@@':
  // 102:       $escape_text range(text i+1 -1)
  // 103:       parse_integer escape_text $rest_text $value
  // 104:       plus &i 1+length_of(escape_text)-length_of(rest_text)
  // ...
  frame->slots[7] /* temp__3 */ = create_closure(entry__8_8, 0);
  //  95: ... -> i <= n:
  //  96:   $chr text(i)
  //  97:   case
  //  98:     chr
  //  99:     '@quot;':
  // 100:       return range(text i+1 -1) str
  // 101:     '@@':
  // 102:       $escape_text range(text i+1 -1)
  // 103:       parse_integer escape_text $rest_text $value
  // 104:       plus &i 1+length_of(escape_text)-length_of(rest_text)
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__8_42(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 111: raise "Unterminated string encountered during deserialization!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__8_43;
  result_count = frame->caller_result_count;
  myself = get__raise();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__8_44(void) {
  allocate_initialized_frame_gc(2, 7);
  // slot allocations:
  // text: 0
  // return: 1
  // n: 2
  // chr: 3
  frame->slots[0] = myself->closure.frame->slots[0]; /* text */
  frame->slots[1] = myself->closure.frame->slots[2]; /* return */
  frame->slots[2] /* n */ = create_future();
  frame->slots[3] /* chr */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 113: $n length_of(text)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__8_45;
}
static void cont__8_45(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* n */, arguments->slots[0]);
  // 114: ... n < 3
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* n */;
  arguments->slots[1] = number__3;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__8_46;
}
static void cont__8_46(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 114: if n < 3:
  // 115:   raise "Invalid character constant encountered during deserialization!"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = func__8_47;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__8_49;
}
static void entry__8_47(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 115: raise "Invalid character constant encountered during deserialization!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__8_48;
  result_count = frame->caller_result_count;
  myself = get__raise();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__8_49(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 116: $chr text(2)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* text */;
  func = myself->type;
  frame->cont = cont__8_50;
}
static void cont__8_50(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* chr */, arguments->slots[0]);
  // 118: chr == '@@'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* chr */;
  arguments->slots[1] = character__64;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__8_51;
}
static void cont__8_51(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 118: ... :
  // 119:   $escape_text range(text 3 -1)
  // 120:   parse_integer escape_text $rest_text $value
  // 121:   $i 3+length_of(escape_text)-length_of(rest_text)
  // 122:   if
  // 123:     ||
  // 124:       value.is_undefined
  // 125:       i+1 > n
  // 126:       text(i) != ';'
  // 127:       text(i+1) != '@apos;'
  // ...
  frame->slots[5] /* temp__2 */ = create_closure(entry__8_52, 0);
  // 132: :
  // 133:   if text(3) != '@apos;':
  // 134:     raise
  // 135:       "Invalid character constant encountered during deserialization!"
  // 136:   return range(text 4 -1) chr
  frame->slots[6] /* temp__3 */ = create_closure(entry__8_83, 0);
  // 117: if
  // 118:   chr == '@@':
  // 119:     $escape_text range(text 3 -1)
  // 120:     parse_integer escape_text $rest_text $value
  // 121:     $i 3+length_of(escape_text)-length_of(rest_text)
  // 122:     if
  // 123:       ||
  // 124:         value.is_undefined
  // 125:         i+1 > n
  // 126:         text(i) != ';'
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
static void cont__8_92(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__4 */ = arguments->slots[0];
  // 137: ... :
  // 138:   $val parse_number(&text)
  // 139:   if val.is_undefined:
  // 140:     raise "Invalid numeric constant encountered during deserialization!"
  // 141:   return text val
  frame->slots[7] /* temp__5 */ = create_closure(entry__8_93, 0);
  // 142: :
  // 143:   match text IDENTIFIER $len
  // 144:   if
  // 145:     len.is_defined:
  // 146:       $tag range(text 1 len)
  // 147:       $deserializer deserializers(tag)
  // 148:       if
  // 149:         deserializer.is_defined:
  // 150:           range &text len+1 -1
  // 151:           deserializer text indent
  // ...
  frame->slots[8] /* temp__6 */ = create_closure(entry__8_99, 0);
  // 89: case
  // 90:   text(1)
  // 91:   '@quot;':
  // 92:     $$str ""
  // 93:     $$i 2
  // 94:     $n length_of(text)
  // 95:     while -> i <= n:
  // 96:       $chr text(i)
  // 97:       case
  // 98:         chr
  // ...
  argument_count = 8;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = character__34;
  arguments->slots[2] = frame->slots[4] /* temp__2 */;
  arguments->slots[3] = character__39;
  arguments->slots[4] = frame->slots[5] /* temp__3 */;
  arguments->slots[5] = frame->slots[6] /* temp__4 */;
  arguments->slots[6] = frame->slots[7] /* temp__5 */;
  arguments->slots[7] = frame->slots[8] /* temp__6 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame->cont = cont__8_116;
}
static void entry__8_106(void) {
  allocate_initialized_frame_gc(4, 6);
  // slot allocations:
  // text: 0
  // len: 1
  // deserializer: 2
  // indent: 3
  frame->slots[0] = myself->closure.frame->slots[0]; /* text */
  frame->slots[1] = myself->closure.frame->slots[1]; /* len */
  frame->slots[2] = myself->closure.frame->slots[4]; /* deserializer */
  frame->slots[3] = myself->closure.frame->slots[2]; /* indent */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 150: ... len+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* len */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__8_107;
}
static void cont__8_107(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 150: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__8_108;
}
static void cont__8_108(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 150: range &text len+1 -1
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  arguments->slots[2] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__8_109;
}
static void cont__8_109(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* text */ = arguments->slots[0];
  // 151: deserializer text indent
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  arguments->slots[1] = frame->slots[3] /* indent */;
  result_count = frame->caller_result_count;
  myself = frame->slots[2] /* deserializer */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__8_110(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // tag: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* tag */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 153: ... "
  // 154:   No deserializer defined for "@(tag)@quot;!@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__8_111;
  arguments->slots[1] = frame->slots[0] /* tag */;
  arguments->slots[2] = string__8_112;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__8_113;
}
static void cont__8_113(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 153: raise "
  // 154:   No deserializer defined for "@(tag)@quot;!@
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__raise();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__8_102(void) {
  allocate_initialized_frame_gc(3, 8);
  // slot allocations:
  // text: 0
  // len: 1
  // indent: 2
  // tag: 3
  // deserializer: 4
  frame->slots[0] = myself->closure.frame->slots[0]; /* text */
  frame->slots[1] = myself->closure.frame->slots[2]; /* len */
  frame->slots[2] = myself->closure.frame->slots[1]; /* indent */
  frame->slots[3] /* tag */ = create_future();
  frame->slots[4] /* deserializer */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 146: $tag range(text 1 len)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[1] /* len */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__8_103;
}
static void cont__8_103(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* tag */, arguments->slots[0]);
  // 147: $deserializer deserializers(tag)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* tag */;
  result_count = 1;
  myself = var._deserializers;
  func = myself->type;
  frame->cont = cont__8_104;
}
static void cont__8_104(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* deserializer */, arguments->slots[0]);
  // 149: deserializer.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* deserializer */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__8_105;
}
static void cont__8_105(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 149: ... :
  // 150:   range &text len+1 -1
  // 151:   deserializer text indent
  frame->slots[6] /* temp__2 */ = create_closure(entry__8_106, 0);
  // 152: :
  // 153:   raise "
  // 154:     No deserializer defined for "@(tag)@quot;!@
  frame->slots[7] /* temp__3 */ = create_closure(entry__8_110, 0);
  // 148: if
  // 149:   deserializer.is_defined:
  // 150:     range &text len+1 -1
  // 151:     deserializer text indent
  // 152:   :
  // 153:     raise "
  // 154:       No deserializer defined for "@(tag)@quot;!@
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
static void entry__8_114(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 156: raise "No valid tag found while attempting to deserialize text!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__8_115;
  result_count = frame->caller_result_count;
  myself = get__raise();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__8_93(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // text: 0
  // return: 1
  // val: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* text */
  frame->slots[1] = myself->closure.frame->slots[2]; /* return */
  frame->slots[2] /* val */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 138: $val parse_number(&text)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  result_count = 2;
  myself = get__parse_number();
  func = myself->type;
  frame->cont = cont__8_94;
}
static void cont__8_94(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* text */ = arguments->slots[0];
  frame->slots[3] /* temp__1 */ = arguments->slots[1];
  // 138: ... val
  initialize_future(frame->slots[2] /* val */, frame->slots[3] /* temp__1 */);
  // 139: ... val.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* val */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__8_95;
}
static void cont__8_95(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 139: if val.is_undefined:
  // 140:   raise "Invalid numeric constant encountered during deserialization!"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = func__8_96;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__8_98;
}
static void entry__8_96(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 140: raise "Invalid numeric constant encountered during deserialization!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__8_97;
  result_count = frame->caller_result_count;
  myself = get__raise();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__8_98(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 141: return text val
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  arguments->slots[1] = frame->slots[2] /* val */;
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__8_99(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // text: 0
  // indent: 1
  // len: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* text */
  frame->slots[1] = myself->closure.frame->slots[1]; /* indent */
  frame->slots[2] /* len */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 143: match text IDENTIFIER $len
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  arguments->slots[1] = get__IDENTIFIER();
  result_count = 1;
  myself = get__match();
  func = myself->type;
  frame->cont = cont__8_100;
}
static void cont__8_100(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* len */, arguments->slots[0]);
  // 145: len.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* len */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__8_101;
}
static void cont__8_101(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 145: ... :
  // 146:   $tag range(text 1 len)
  // 147:   $deserializer deserializers(tag)
  // 148:   if
  // 149:     deserializer.is_defined:
  // 150:       range &text len+1 -1
  // 151:       deserializer text indent
  // 152:     :
  // 153:       raise "
  // 154:         No deserializer defined for "@(tag)@quot;!@
  frame->slots[4] /* temp__2 */ = create_closure(entry__8_102, 0);
  // 144: if
  // 145:   len.is_defined:
  // 146:     $tag range(text 1 len)
  // 147:     $deserializer deserializers(tag)
  // 148:     if
  // 149:       deserializer.is_defined:
  // 150:         range &text len+1 -1
  // 151:         deserializer text indent
  // 152:       :
  // 153:         raise "
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  arguments->slots[2] = func__8_114;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__8_116(void) {
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__9_1(void) {
  allocate_initialized_frame_gc(1, 6);
  // slot allocations:
  // text: 0
  // remaining_text: 1
  // obj: 2
  frame->slots[1] /* remaining_text */ = create_future();
  frame->slots[2] /* obj */ = create_future();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 159: deserialize_stream text 0 $remaining_text $obj
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* text */;
  arguments->slots[1] = number__0;
  result_count = 2;
  myself = var._deserialize_stream;
  func = myself->type;
  frame->cont = cont__9_2;
}
static void cont__9_2(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  frame->slots[4] /* temp__2 */ = arguments->slots[1];
  // 159: ... remaining_text
  initialize_future(frame->slots[1] /* remaining_text */, frame->slots[3] /* temp__1 */);
  // 159: ... obj
  initialize_future(frame->slots[2] /* obj */, frame->slots[4] /* temp__2 */);
  // 160: ... remaining_text == ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* remaining_text */;
  arguments->slots[1] = empty_string;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__9_3;
}
static void cont__9_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 160: ... -> obj
  frame->slots[5] /* temp__3 */ = create_closure(entry__9_4, 0);
  // 160: ... if(remaining_text == "" (-> obj) -> undefined)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  arguments->slots[2] = func__9_5;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__9_6;
}
static void entry__9_4(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // obj: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* obj */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 160: ... -> obj
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* obj */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__9_5(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 160: ... -> undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__9_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 160: -> if(remaining_text == "" (-> obj) -> undefined)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
EXPORT void collect__basic__deserialize(void) {
  temp__1 = collect_node(temp__1);
  temp__2 = collect_node(temp__2);
  temp__3 = collect_node(temp__3);
  temp__4 = collect_node(temp__4);
  temp__5 = collect_node(temp__5);
  temp__6 = collect_node(temp__6);
  var.std__NAME = collect_node(var.std__NAME);
  var.std__IDENTIFIER = collect_node(var.std__IDENTIFIER);
  var._deserializers = collect_node(var._deserializers);
  var.std__register_deserializer = collect_node(var.std__register_deserializer);
  func__4_1 = collect_node(func__4_1);
  var.std__get_deserialization_indent = collect_node(var.std__get_deserialization_indent);
  func__5_1 = collect_node(func__5_1);
  var.std__deserialize_item = collect_node(var.std__deserialize_item);
  func__6_13 = collect_node(func__6_13);
  func__6_1 = collect_node(func__6_1);
  var.std__create_deserializer = collect_node(var.std__create_deserializer);
  string__7_8 = collect_node(string__7_8);
  string__7_18 = collect_node(string__7_18);
  string__7_19 = collect_node(string__7_19);
  string__7_46 = collect_node(string__7_46);
  string__7_47 = collect_node(string__7_47);
  string__7_54 = collect_node(string__7_54);
  string__7_55 = collect_node(string__7_55);
  func__7_1 = collect_node(func__7_1);
  var._deserialize_stream = collect_node(var._deserialize_stream);
  string__8_34 = collect_node(string__8_34);
  func__8_33 = collect_node(func__8_33);
  string__8_43 = collect_node(string__8_43);
  string__8_48 = collect_node(string__8_48);
  func__8_47 = collect_node(func__8_47);
  string__8_77 = collect_node(string__8_77);
  func__8_76 = collect_node(func__8_76);
  string__8_88 = collect_node(string__8_88);
  func__8_87 = collect_node(func__8_87);
  string__8_97 = collect_node(string__8_97);
  func__8_96 = collect_node(func__8_96);
  string__8_111 = collect_node(string__8_111);
  string__8_112 = collect_node(string__8_112);
  string__8_115 = collect_node(string__8_115);
  func__8_114 = collect_node(func__8_114);
  func__8_1 = collect_node(func__8_1);
  var.std__deserialize = collect_node(var.std__deserialize);
  func__9_5 = collect_node(func__9_5);
  func__9_1 = collect_node(func__9_1);
  string__11_1 = collect_node(string__11_1);
  character__9 = collect_node(character__9);
  character__57 = collect_node(character__57);
  character__10 = collect_node(character__10);
  character__58 = collect_node(character__58);
  number__0 = collect_node(number__0);
  character__48 = collect_node(character__48);
  number__3 = collect_node(number__3);
  number__4 = collect_node(number__4);
  character__95 = collect_node(character__95);
  number__8 = collect_node(number__8);
  character__64 = collect_node(character__64);
  character__34 = collect_node(character__34);
  character__39 = collect_node(character__39);
  character__32 = collect_node(character__32);
  character__59 = collect_node(character__59);
  number__1 = collect_node(number__1);
  number__2 = collect_node(number__2);
}

static int already_run_phase_1 = false;

EXPORT void phase_1__basic__deserialize(void) {
  if (already_run_phase_1) return;
  already_run_phase_1 = true;
  register_module_info(&module_info);
}

static int already_run_phase_2 = false;

EXPORT void phase_2__basic__deserialize(void) {
  if (already_run_phase_2) return;
  already_run_phase_2 = true;
  set_module("basic__deserialize");
  set_used_namespaces(used_namespaces);
  character__9 = create_future();
  character__57 = create_future();
  character__10 = create_future();
  character__58 = create_future();
  number__0 = create_future();
  character__48 = create_future();
  number__3 = create_future();
  number__4 = create_future();
  character__95 = create_future();
  number__8 = create_future();
  character__64 = create_future();
  character__34 = create_future();
  character__39 = create_future();
  character__32 = create_future();
  character__59 = create_future();
  number__1 = create_future();
  number__2 = create_future();
  define_single_assign_static("std", "NAME", get__std__NAME, &var.std__NAME);
  define_single_assign_static("std", "IDENTIFIER", get__std__IDENTIFIER, &var.std__IDENTIFIER);
  func__4_1 = create_future();
  define_single_assign_static("std", "register_deserializer", get__std__register_deserializer, &var.std__register_deserializer);
  func__5_1 = create_future();
  define_single_assign_static("std", "get_deserialization_indent", get__std__get_deserialization_indent, &var.std__get_deserialization_indent);
  func__6_13 = create_future();
  func__6_1 = create_future();
  define_single_assign_static("std", "deserialize_item", get__std__deserialize_item, &var.std__deserialize_item);
  string__7_8 = from_latin_1_string("()", 2);
  string__7_18 = from_latin_1_string("Invalid ", 8);
  string__7_19 = from_latin_1_string(" object encountered during deserialisation!", 43);
  string__7_46 = from_latin_1_string("Encountered invalid ", 20);
  string__7_47 = from_latin_1_string(" component during deserialisation!", 34);
  string__7_54 = from_latin_1_string("Encountered unknown ", 20);
  string__7_55 = from_latin_1_string(" component during deserialisation!", 34);
  func__7_1 = create_future();
  define_single_assign_static("std", "create_deserializer", get__std__create_deserializer, &var.std__create_deserializer);
  string__8_34 = from_latin_1_string("Invalid string escape encountered during deserialization!", 57);
  func__8_33 = create_future();
  string__8_43 = from_latin_1_string("Unterminated string encountered during deserialization!", 55);
  string__8_48 = from_latin_1_string("Invalid character constant encountered during deserialization!", 62);
  func__8_47 = create_future();
  string__8_77 = from_latin_1_string("Invalid character escape encountered during deserialization!", 60);
  func__8_76 = create_future();
  string__8_88 = from_latin_1_string("Invalid character constant encountered during deserialization!", 62);
  func__8_87 = create_future();
  string__8_97 = from_latin_1_string("Invalid numeric constant encountered during deserialization!", 60);
  func__8_96 = create_future();
  string__8_111 = from_latin_1_string("No deserializer defined for \042", 29);
  string__8_112 = from_latin_1_string("\042!", 2);
  string__8_115 = from_latin_1_string("No valid tag found while attempting to deserialize text!", 56);
  func__8_114 = create_future();
  func__8_1 = create_future();
  func__9_5 = create_future();
  func__9_1 = create_future();
  define_single_assign_static("std", "deserialize", get__std__deserialize, &var.std__deserialize);
  string__11_1 = from_latin_1_string("::", 2);
}

static int already_run_phase_3 = false;

EXPORT void phase_3__basic__deserialize(void) {
  if (already_run_phase_3) return;
  already_run_phase_3 = true;
  set_module("basic__deserialize");
  set_used_namespaces(used_namespaces);
  use_read_only(NULL, "DIGIT", &get__DIGIT, &get_value_or_future__DIGIT);
  use_read_only(NULL, "IDENTIFIER", &get__IDENTIFIER, &get_value_or_future__IDENTIFIER);
  use_read_only(NULL, "LETTER", &get__LETTER, &get_value_or_future__LETTER);
  use_read_only(NULL, "NAME", &get__NAME, &get_value_or_future__NAME);
  use_read_only(NULL, "alt", &get__alt, &get_value_or_future__alt);
  use_read_only(NULL, "case", &get__case, &get_value_or_future__case);
  use_read_only(NULL, "character", &get__character, &get_value_or_future__character);
  use_read_only(NULL, "deserialize_item", &get__deserialize_item, &get_value_or_future__deserialize_item);
  use_read_only(NULL, "empty_table", &get__empty_table, &get_value_or_future__empty_table);
  use_read_only(NULL, "for_each_pair", &get__for_each_pair, &get_value_or_future__for_each_pair);
  use_read_only(NULL, "forever", &get__forever, &get_value_or_future__forever);
  use_read_only(NULL, "get_deserialization_indent", &get__get_deserialization_indent, &get_value_or_future__get_deserialization_indent);
  use_read_only(NULL, "has_prefix", &get__has_prefix, &get_value_or_future__has_prefix);
  use_read_only(NULL, "if", &get__if, &get_value_or_future__if);
  use_read_only(NULL, "inc", &get__inc, &get_value_or_future__inc);
  use_read_only(NULL, "is_defined", &get__is_defined, &get_value_or_future__is_defined);
  use_read_only(NULL, "is_undefined", &get__is_undefined, &get_value_or_future__is_undefined);
  use_read_only(NULL, "length_of", &get__length_of, &get_value_or_future__length_of);
  use_read_only(NULL, "many", &get__many, &get_value_or_future__many);
  use_read_only(NULL, "match", &get__match, &get_value_or_future__match);
  use_read_only(NULL, "optional", &get__optional, &get_value_or_future__optional);
  use_read_only(NULL, "parse_integer", &get__parse_integer, &get_value_or_future__parse_integer);
  use_read_only(NULL, "parse_number", &get__parse_number, &get_value_or_future__parse_number);
  use_read_only(NULL, "plus", &get__plus, &get_value_or_future__plus);
  use_read_only(NULL, "push", &get__push, &get_value_or_future__push);
  use_read_only(NULL, "raise", &get__raise, &get_value_or_future__raise);
  use_read_only(NULL, "range", &get__range, &get_value_or_future__range);
  use_read_only(NULL, "some", &get__some, &get_value_or_future__some);
  use_read_only("std", "and", &get__std__and, &get_value_or_future__std__and);
  use_read_only("std", "equal", &get__std__equal, &get_value_or_future__std__equal);
  use_read_only("std", "less", &get__std__less, &get_value_or_future__std__less);
  use_read_only("std", "minus", &get__std__minus, &get_value_or_future__std__minus);
  use_read_only("std", "negate", &get__std__negate, &get_value_or_future__std__negate);
  use_read_only("std", "not", &get__std__not, &get_value_or_future__std__not);
  use_read_only("std", "or", &get__std__or, &get_value_or_future__std__or);
  use_read_only("std", "plus", &get__std__plus, &get_value_or_future__std__plus);
  use_read_only("std", "sequence", &get__std__sequence, &get_value_or_future__std__sequence);
  use_read_only("std", "string", &get__std__string, &get_value_or_future__std__string);
  use_read_only("std", "value_range", &get__std__value_range, &get_value_or_future__std__value_range);
  use_read_only(NULL, "undefined", &get__undefined, &get_value_or_future__undefined);
  use_read_only(NULL, "while", &get__while, &get_value_or_future__while);
}

static int already_run_phase_4 = false;

EXPORT void phase_4__basic__deserialize(void) {
  if (already_run_phase_4) return;
  already_run_phase_4 = true;
  assign_value(&character__9, from_uchar32(9));
  assign_value(&character__57, from_uchar32(57));
  assign_value(&character__10, from_uchar32(10));
  assign_value(&character__58, from_uchar32(58));
  assign_value(&number__0, from_uint32(0U));
  assign_value(&character__48, from_uchar32(48));
  assign_value(&number__3, from_uint32(3U));
  assign_value(&number__4, from_uint32(4U));
  assign_value(&character__95, from_uchar32(95));
  assign_value(&number__8, from_uint32(8U));
  assign_value(&character__64, from_uchar32(64));
  assign_value(&character__34, from_uchar32(34));
  assign_value(&character__39, from_uchar32(39));
  assign_value(&character__32, from_uchar32(32));
  assign_value(&character__59, from_uchar32(59));
  assign_value(&number__1, from_uint32(1U));
  assign_value(&number__2, from_uint32(2U));
  assign_variable(&var.std__register_deserializer, &func__4_1);
  assign_variable(&var.std__get_deserialization_indent, &func__5_1);
  assign_variable(&var.std__deserialize_item, &func__6_1);
  assign_variable(&var.std__create_deserializer, &func__7_1);
  assign_variable(&var._deserialize_stream, &func__8_1);
  assign_variable(&var.std__deserialize, &func__9_1);
}

static int already_run_phase_5 = false;

EXPORT void phase_5__basic__deserialize(void) {
  if (already_run_phase_5) return;
  already_run_phase_5 = true;
  assign_value(&func__4_1, create_function(entry__4_1, 2));
  assign_value(&func__5_1, create_function(entry__5_1, 1));
  assign_value(&func__6_13, create_function(entry__6_13, 0));
  assign_value(&func__6_1, create_function(entry__6_1, 2));
  assign_value(&func__7_1, create_function(entry__7_1, -1));
  assign_value(&func__8_33, create_function(entry__8_33, 0));
  assign_value(&func__8_47, create_function(entry__8_47, 0));
  assign_value(&func__8_76, create_function(entry__8_76, 0));
  assign_value(&func__8_87, create_function(entry__8_87, 0));
  assign_value(&func__8_96, create_function(entry__8_96, 0));
  assign_value(&func__8_114, create_function(entry__8_114, 0));
  assign_value(&func__8_1, create_function(entry__8_1, 2));
  assign_value(&func__9_5, create_function(entry__9_5, 0));
  assign_value(&func__9_1, create_function(entry__9_1, 1));
  register_collector(collect__basic__deserialize);
}
