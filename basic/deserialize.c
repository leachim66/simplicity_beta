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
IMPORT NODE *from_uchar32(unsigned int chr);
IMPORT NODE *from_uint32(uint32_t val);
IMPORT NODE *create_function(FUNC func, int par_count);
IMPORT NODE *from_latin_1_string(const char *str, long len);
IMPORT void set_module(const char *name);
IMPORT void set_used_namespaces(const char **namespaces);
IMPORT void define_single_assign_static(
  const char *namespace, const char *name,
  NODE_GETTER getter, NODE **var_p
);
IMPORT void use_read_only(
  const char *namespace, const char *name,
  NODE_GETTER *getter, NODE_GETTER *get_value_or_future
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
static NODE *func__4_1_std__register_deserializer;
static void entry__4_1_std__register_deserializer(void);
static FRAME_INFO frame__4_1_std__register_deserializer = {2, {"tag", "deserializer"}};
static void cont__4_2(void);
static NODE *get__std__register_deserializer(void) {
  return var.std__register_deserializer;
}
static NODE *func__5_1_std__get_deserialization_indent;
static void entry__5_1_std__get_deserialization_indent(void);
static FRAME_INFO frame__5_1_std__get_deserialization_indent = {4, {"text", "i", "n", "indent"}};
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
static NODE *func__6_1_std__deserialize_item;
static void entry__6_1_std__deserialize_item(void);
static FRAME_INFO frame__6_1_std__deserialize_item = {2, {"text", "base_indent"}};
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
static NODE *func__7_1_std__create_deserializer;
static void entry__7_1_std__create_deserializer(void);
static FRAME_INFO frame__7_1_std__create_deserializer = {4, {"name", "prototype", "attributes", "attribute_setters"}};
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
static NODE *string__2d7981f4e6482bec;
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
static NODE *string__76acaf9d04f58520;
static NODE *string__770b9b2c5bac96f5;
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
static NODE *string__deed742f6908f861;
static NODE *string__dc7e95992fac4f0d;
static void cont__7_48(void);
static void cont__7_49(void);
static void cont__7_50(void);
static void cont__7_51(void);
static void cont__7_52(void);
static NODE *func__7_53;
static void entry__7_53(void);
static FRAME_INFO frame__7_53 = {1, {"name"}};
static NODE *string__d8ed73a1e9580be1;
static void cont__7_55(void);
static void cont__7_56(void);
static void cont__7_57(void);
static void cont__7_58(void);
static void cont__7_59(void);
static void cont__7_60(void);
static void cont__7_61(void);
static void cont__7_62(void);
static NODE *get__std__create_deserializer(void) {
  return var.std__create_deserializer;
}
static NODE *func__8_1_deserialize_stream;
static void entry__8_1_deserialize_stream(void);
static FRAME_INFO frame__8_1_deserialize_stream = {3, {"text", "indent", "return"}};
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
static NODE *string__8d42cc379b749591;
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
static NODE *string__e4bd1ec7a051e115;
static NODE *func__8_44;
static void entry__8_44(void);
static FRAME_INFO frame__8_44 = {4, {"text", "return", "n", "chr"}};
static void cont__8_45(void);
static void cont__8_46(void);
static NODE *func__8_47;
static void entry__8_47(void);
static FRAME_INFO frame__8_47 = {0, {}};
static NODE *string__6ce496bd70576317;
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
static NODE *string__c08bfa6e27fae532;
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
static void cont__8_88(void);
static void cont__8_89(void);
static void cont__8_90(void);
static void cont__8_91(void);
static NODE *func__8_92;
static void entry__8_92(void);
static FRAME_INFO frame__8_92 = {3, {"text", "return", "val"}};
static void cont__8_93(void);
static void cont__8_94(void);
static NODE *func__8_95;
static void entry__8_95(void);
static FRAME_INFO frame__8_95 = {0, {}};
static NODE *string__a7e8c0fdec6da36f;
static void cont__8_97(void);
static NODE *func__8_98;
static void entry__8_98(void);
static FRAME_INFO frame__8_98 = {3, {"text", "indent", "len"}};
static void cont__8_99(void);
static void cont__8_100(void);
static NODE *func__8_101;
static void entry__8_101(void);
static FRAME_INFO frame__8_101 = {5, {"text", "len", "indent", "tag", "deserializer"}};
static void cont__8_102(void);
static void cont__8_103(void);
static void cont__8_104(void);
static NODE *func__8_105;
static void entry__8_105(void);
static FRAME_INFO frame__8_105 = {4, {"text", "len", "deserializer", "indent"}};
static void cont__8_106(void);
static void cont__8_107(void);
static void cont__8_108(void);
static NODE *func__8_109;
static void entry__8_109(void);
static FRAME_INFO frame__8_109 = {1, {"tag"}};
static NODE *string__8b7292a23e049581;
static NODE *string__2d7981f4e6182be4;
static void cont__8_112(void);
static NODE *func__8_113;
static void entry__8_113(void);
static FRAME_INFO frame__8_113 = {0, {}};
static NODE *string__e89843a7c2547e3c;
static void cont__8_115(void);
static NODE *func__9_1_std__deserialize;
static void entry__9_1_std__deserialize(void);
static FRAME_INFO frame__9_1_std__deserialize = {3, {"text", "remaining_text", "obj"}};
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
static NODE *string__2d7981f4e6d82bff;
static void cont__11_2(void);
static void cont__11_3(void);
static void cont__11_4(void);
void run__basic__deserialize(void);

static CONTINUATION_INFO continuation_info[] = {
  {run__basic__deserialize, NULL, 29, 29, 16, 32},
  {cont__10_1, NULL, 29, 29, 11, 33},
  {cont__10_2, NULL, 29, 29, 51, 67},
  {cont__10_3, NULL, 29, 29, 46, 68},
  {cont__10_4, NULL, 29, 29, 41, 68},
  {cont__10_5, NULL, 29, 29, 36, 69},
  {cont__10_6, NULL, 23, 29, 1, 69},
  {cont__10_7, NULL, 37, 37, 18, 27},
  {cont__11_2, NULL, 37, 37, 9, 28},
  {cont__11_3, NULL, 31, 37, 1, 28},
  {cont__11_4, NULL, 39, 39, 1, 27},
  {entry__4_1_std__register_deserializer, NULL, 52, 52, 3, 21},
  {cont__4_2, &frame__4_1_std__register_deserializer, 52, 52, 34, 34},
  {entry__5_6, NULL, 65, 65, 22, 28},
  {cont__5_7, &frame__5_6, 65, 65, 22, 38},
  {cont__5_8, &frame__5_6, 65, 65, 22, 38},
  {entry__5_10, NULL, 66, 66, 5, 10},
  {cont__5_11, &frame__5_10, 67, 67, 5, 18},
  {cont__5_12, &frame__5_10, 67, 67, 18, 18},
  {entry__5_3, NULL, 65, 65, 12, 17},
  {cont__5_4, &frame__5_3, 65, 65, 12, 17},
  {cont__5_5, &frame__5_3, 65, 65, 12, 38},
  {cont__5_9, &frame__5_3, 65, 67, 9, 18},
  {entry__5_17, NULL, 68, 68, 22, 28},
  {cont__5_18, &frame__5_17, 68, 68, 22, 35},
  {cont__5_19, &frame__5_17, 68, 68, 22, 35},
  {entry__5_21, NULL, 69, 69, 5, 10},
  {cont__5_22, &frame__5_21, 70, 70, 5, 15},
  {cont__5_23, &frame__5_21, 70, 70, 15, 15},
  {entry__5_14, NULL, 68, 68, 12, 17},
  {cont__5_15, &frame__5_14, 68, 68, 12, 17},
  {cont__5_16, &frame__5_14, 68, 68, 12, 35},
  {cont__5_20, &frame__5_14, 68, 70, 9, 15},
  {entry__5_1_std__get_deserialization_indent, NULL, 63, 63, 3, 20},
  {cont__5_2, &frame__5_1_std__get_deserialization_indent, 65, 67, 3, 18},
  {cont__5_13, &frame__5_1_std__get_deserialization_indent, 68, 70, 3, 15},
  {cont__5_24, &frame__5_1_std__get_deserialization_indent, 71, 71, 18, 18},
  {cont__5_25, &frame__5_1_std__get_deserialization_indent, 71, 71, 3, 18},
  {cont__5_26, &frame__5_1_std__get_deserialization_indent, 72, 72, 3, 11},
  {entry__6_5, NULL, 84, 84, 29, 35},
  {cont__6_6, &frame__6_5, 84, 84, 29, 45},
  {cont__6_7, &frame__6_5, 84, 84, 29, 45},
  {entry__6_12, NULL, 88, 88, 11, 40},
  {entry__6_13, NULL, 89, 89, 9, 30},
  {entry__6_9, NULL, 85, 85, 7, 47},
  {cont__6_10, &frame__6_9, 87, 87, 9, 28},
  {cont__6_11, &frame__6_9, 86, 89, 7, 30},
  {entry__6_18, NULL, 91, 91, 47, 47},
  {cont__6_19, &frame__6_18, 91, 91, 32, 47},
  {cont__6_20, &frame__6_18, 91, 91, 47, 47},
  {entry__6_15, NULL, 91, 91, 16, 22},
  {cont__6_16, &frame__6_15, 91, 91, 16, 29},
  {cont__6_17, &frame__6_15, 91, 91, 13, 47},
  {entry__6_14, NULL, 91, 91, 7, 47},
  {cont__6_21, &frame__6_14, 92, 92, 7, 41},
  {entry__6_1_std__deserialize_item, NULL, 84, 84, 5, 19},
  {cont__6_2, &frame__6_1_std__deserialize_item, 84, 84, 5, 24},
  {cont__6_3, &frame__6_1_std__deserialize_item, 84, 84, 5, 24},
  {cont__6_4, &frame__6_1_std__deserialize_item, 84, 84, 5, 45},
  {cont__6_8, &frame__6_1_std__deserialize_item, 83, 92, 3, 42},
  {entry__7_2, NULL, 106, 106, 48, 48},
  {cont__7_3, &frame__7_2, 106, 106, 24, 49},
  {cont__7_4, &frame__7_2, 106, 106, 5, 50},
  {cont__7_5, &frame__7_2, 106, 106, 67, 67},
  {entry__7_10, NULL, 113, 113, 53, 53},
  {cont__7_11, &frame__7_10, 113, 113, 39, 54},
  {cont__7_12, &frame__7_10, 113, 113, 32, 64},
  {entry__7_17, NULL, 115, 115, 13, 72},
  {cont__7_20, &frame__7_17, 115, 115, 7, 72},
  {entry__7_25, NULL, 118, 118, 34, 40},
  {cont__7_26, &frame__7_25, 118, 118, 34, 50},
  {cont__7_27, &frame__7_25, 118, 118, 34, 50},
  {cont__7_28, &frame__7_25, 118, 118, 34, 50},
  {entry__7_30, NULL, 118, 118, 53, 67},
  {entry__7_35, NULL, 120, 120, 33, 47},
  {entry__7_39, NULL, 123, 123, 35, 39},
  {cont__7_40, &frame__7_39, 123, 123, 30, 40},
  {cont__7_41, &frame__7_39, 123, 123, 30, 47},
  {cont__7_42, &frame__7_39, 123, 123, 30, 47},
  {cont__7_43, &frame__7_39, 123, 123, 30, 47},
  {entry__7_45, NULL, 124, 124, 15, 77},
  {cont__7_48, &frame__7_45, 124, 124, 9, 77},
  {entry__7_53, NULL, 128, 128, 15, 77},
  {cont__7_55, &frame__7_53, 128, 128, 9, 77},
  {entry__7_22, NULL, 118, 118, 10, 24},
  {cont__7_23, &frame__7_22, 118, 118, 10, 29},
  {cont__7_24, &frame__7_22, 118, 118, 10, 50},
  {cont__7_29, &frame__7_22, 118, 118, 7, 67},
  {cont__7_31, &frame__7_22, 119, 119, 7, 61},
  {cont__7_32, &frame__7_22, 120, 120, 10, 30},
  {cont__7_33, &frame__7_22, 120, 120, 10, 30},
  {cont__7_34, &frame__7_22, 120, 120, 7, 47},
  {cont__7_36, &frame__7_22, 122, 122, 7, 32},
  {cont__7_37, &frame__7_22, 123, 123, 10, 25},
  {cont__7_38, &frame__7_22, 123, 123, 10, 47},
  {cont__7_44, &frame__7_22, 123, 124, 7, 77},
  {cont__7_49, &frame__7_22, 125, 125, 7, 28},
  {cont__7_50, &frame__7_22, 126, 126, 7, 46},
  {cont__7_51, &frame__7_22, 127, 127, 10, 38},
  {cont__7_52, &frame__7_22, 127, 128, 7, 77},
  {cont__7_56, &frame__7_22, 129, 129, 19, 23},
  {cont__7_57, &frame__7_22, 129, 129, 26, 26},
  {cont__7_58, &frame__7_22, 129, 129, 7, 26},
  {cont__7_59, &frame__7_22, 130, 130, 29, 58},
  {cont__7_60, &frame__7_22, 130, 130, 7, 58},
  {cont__7_61, &frame__7_22, 130, 130, 58, 58},
  {entry__7_7, NULL, 113, 113, 8, 29},
  {cont__7_9, &frame__7_7, 113, 113, 5, 64},
  {cont__7_13, &frame__7_7, 114, 114, 8, 14},
  {cont__7_14, &frame__7_7, 114, 114, 8, 24},
  {cont__7_15, &frame__7_7, 114, 114, 8, 24},
  {cont__7_16, &frame__7_7, 114, 115, 5, 72},
  {cont__7_21, &frame__7_7, 117, 130, 5, 58},
  {cont__7_62, &frame__7_7, 130, 130, 58, 58},
  {entry__7_1_std__create_deserializer, NULL, 105, 106, 3, 67},
  {cont__7_6, &frame__7_1_std__create_deserializer, 107, 130, 3, 59},
  {entry__8_10, NULL, 149, 149, 31, 33},
  {cont__8_11, &frame__8_10, 149, 149, 36, 36},
  {cont__8_12, &frame__8_10, 149, 149, 20, 37},
  {cont__8_13, &frame__8_10, 149, 149, 13, 41},
  {entry__8_27, NULL, 154, 154, 47, 53},
  {cont__8_28, &frame__8_27, 154, 154, 47, 60},
  {cont__8_29, &frame__8_27, 154, 154, 47, 60},
  {cont__8_30, &frame__8_27, 154, 154, 47, 60},
  {entry__8_25, NULL, 154, 154, 38, 42},
  {cont__8_26, &frame__8_25, 154, 154, 38, 60},
  {cont__8_31, &frame__8_25, 154, 154, 38, 60},
  {entry__8_33, NULL, 155, 155, 15, 79},
  {entry__8_14, NULL, 151, 151, 37, 39},
  {cont__8_15, &frame__8_14, 151, 151, 42, 42},
  {cont__8_16, &frame__8_14, 151, 151, 13, 43},
  {cont__8_17, &frame__8_14, 152, 152, 13, 55},
  {cont__8_18, &frame__8_14, 153, 153, 23, 44},
  {cont__8_19, &frame__8_14, 153, 153, 21, 44},
  {cont__8_20, &frame__8_14, 153, 153, 46, 65},
  {cont__8_21, &frame__8_14, 153, 153, 21, 65},
  {cont__8_22, &frame__8_14, 153, 153, 13, 65},
  {cont__8_23, &frame__8_14, 154, 154, 16, 33},
  {cont__8_24, &frame__8_14, 154, 154, 16, 60},
  {cont__8_32, &frame__8_14, 154, 155, 13, 79},
  {cont__8_35, &frame__8_14, 156, 156, 23, 38},
  {cont__8_36, &frame__8_14, 156, 156, 13, 38},
  {cont__8_37, &frame__8_14, 156, 156, 38, 38},
  {entry__8_38, NULL, 158, 158, 13, 25},
  {cont__8_39, &frame__8_38, 158, 158, 25, 25},
  {entry__8_8, NULL, 145, 145, 9, 20},
  {cont__8_9, &frame__8_8, 146, 158, 9, 26},
  {cont__8_40, &frame__8_8, 159, 159, 9, 14},
  {cont__8_41, &frame__8_8, 159, 159, 14, 14},
  {entry__8_5, NULL, 144, 144, 16, 21},
  {cont__8_6, &frame__8_5, 144, 144, 16, 21},
  {cont__8_7, &frame__8_5, 144, 159, 13, 14},
  {entry__8_3, NULL, 143, 143, 7, 24},
  {cont__8_4, &frame__8_3, 144, 159, 7, 14},
  {cont__8_42, &frame__8_3, 160, 160, 7, 69},
  {entry__8_47, NULL, 164, 164, 9, 78},
  {entry__8_68, NULL, 176, 176, 20, 22},
  {cont__8_69, &frame__8_68, 176, 176, 15, 23},
  {cont__8_70, &frame__8_68, 176, 176, 15, 35},
  {cont__8_71, &frame__8_68, 176, 176, 15, 35},
  {cont__8_72, &frame__8_68, 176, 176, 15, 35},
  {entry__8_64, NULL, 175, 175, 15, 21},
  {cont__8_65, &frame__8_64, 175, 175, 15, 28},
  {cont__8_66, &frame__8_64, 175, 175, 15, 28},
  {cont__8_67, &frame__8_64, 176, 176, 15, 35},
  {cont__8_73, &frame__8_64, },
  {entry__8_61, NULL, 174, 174, 15, 17},
  {cont__8_62, &frame__8_61, 174, 174, 15, 21},
  {cont__8_63, &frame__8_61, },
  {cont__8_74, &frame__8_61, },
  {entry__8_76, NULL, 178, 179, 15, 78},
  {entry__8_52, NULL, 168, 168, 38, 38},
  {cont__8_53, &frame__8_52, 168, 168, 11, 39},
  {cont__8_54, &frame__8_52, 169, 169, 11, 53},
  {cont__8_55, &frame__8_52, 170, 170, 16, 37},
  {cont__8_56, &frame__8_52, 170, 170, 14, 37},
  {cont__8_57, &frame__8_52, 170, 170, 39, 58},
  {cont__8_58, &frame__8_52, 170, 170, 11, 58},
  {cont__8_59, &frame__8_52, 173, 173, 15, 32},
  {cont__8_60, &frame__8_52, },
  {cont__8_75, &frame__8_52, 171, 179, 11, 80},
  {cont__8_78, &frame__8_52, 180, 180, 29, 31},
  {cont__8_79, &frame__8_52, 180, 180, 34, 34},
  {cont__8_80, &frame__8_52, 180, 180, 18, 35},
  {cont__8_81, &frame__8_52, 180, 180, 37, 52},
  {cont__8_82, &frame__8_52, 180, 180, 11, 52},
  {entry__8_87, NULL, 183, 184, 13, 78},
  {entry__8_83, NULL, 182, 182, 14, 20},
  {cont__8_84, &frame__8_83, 182, 182, 14, 32},
  {cont__8_85, &frame__8_83, 182, 182, 14, 32},
  {cont__8_86, &frame__8_83, 182, 184, 11, 79},
  {cont__8_88, &frame__8_83, 185, 185, 32, 32},
  {cont__8_89, &frame__8_83, 185, 185, 18, 33},
  {cont__8_90, &frame__8_83, 185, 185, 11, 37},
  {entry__8_44, NULL, 162, 162, 7, 24},
  {cont__8_45, &frame__8_44, 163, 163, 10, 14},
  {cont__8_46, &frame__8_44, 163, 164, 7, 78},
  {cont__8_49, &frame__8_44, 165, 165, 7, 18},
  {cont__8_50, &frame__8_44, 167, 167, 9, 19},
  {cont__8_51, &frame__8_44, 166, 185, 7, 38},
  {entry__8_95, NULL, 189, 189, 9, 76},
  {entry__8_92, NULL, 187, 187, 7, 30},
  {cont__8_93, &frame__8_92, 188, 188, 10, 25},
  {cont__8_94, &frame__8_92, 188, 189, 7, 76},
  {cont__8_97, &frame__8_92, 190, 190, 7, 21},
  {entry__8_105, NULL, 199, 199, 27, 31},
  {cont__8_106, &frame__8_105, 199, 199, 34, 34},
  {cont__8_107, &frame__8_105, 199, 199, 15, 34},
  {cont__8_108, &frame__8_105, 200, 200, 15, 38},
  {entry__8_109, NULL, 202, 203, 21, 59},
  {cont__8_112, &frame__8_109, 202, 203, 15, 59},
  {entry__8_101, NULL, 195, 195, 11, 32},
  {cont__8_102, &frame__8_101, 196, 196, 11, 42},
  {cont__8_103, &frame__8_101, 198, 198, 13, 35},
  {cont__8_104, &frame__8_101, 197, 203, 11, 61},
  {entry__8_113, NULL, 205, 205, 11, 74},
  {entry__8_98, NULL, 192, 192, 7, 32},
  {cont__8_99, &frame__8_98, 194, 194, 9, 22},
  {cont__8_100, &frame__8_98, 193, 205, 7, 75},
  {entry__8_1_deserialize_stream, NULL, 139, 139, 5, 11},
  {cont__8_2, &frame__8_1_deserialize_stream, 186, 186, 5, 14},
  {cont__8_91, &frame__8_1_deserialize_stream, 138, 205, 3, 77},
  {cont__8_115, &frame__8_1_deserialize_stream, 205, 205, 77, 77},
  {entry__9_4, NULL, 218, 218, 31, 36},
  {entry__9_5, NULL, 218, 218, 39, 50},
  {entry__9_1_std__deserialize, NULL, 217, 217, 3, 48},
  {cont__9_2, &frame__9_1_std__deserialize, 218, 218, 9, 28},
  {cont__9_3, &frame__9_1_std__deserialize, 218, 218, 6, 51},
  {cont__9_6, &frame__9_1_std__deserialize, 218, 218, 3, 51}
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
  allocate_initialized_frame_gc(0, 6);
  // 29: ... alt(LETTER DIGIT)
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
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 29: ... some(alt(LETTER DIGIT))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
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
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 29: ... alt(LETTER DIGIT)
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
  frame->slots[5] /* temp__6 */ = arguments->slots[0];
  // 29: ... many(alt(LETTER DIGIT))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__6 */;
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
  frame->slots[4] /* temp__5 */ = arguments->slots[0];
  // 29: ... '_', many(alt(LETTER DIGIT))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__95;
  arguments->slots[1] = frame->slots[4] /* temp__5 */;
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
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 29: ... some('_', many(alt(LETTER DIGIT)))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__4 */;
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
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 23: $std::NAME
  // 24:   #
  // 25:     a grammar expression to match a valid Simplicity name
  // 26:     
  // 27:     See also: IDENTIFIER
  // 28:   
  // 29:   LETTER, some(alt(LETTER DIGIT)), some('_', many(alt(LETTER DIGIT)))
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__LETTER();
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  arguments->slots[2] = frame->slots[2] /* temp__3 */;
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
  // 37: ... "::", NAME
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e6d82bff;
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
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 37: ... optional("::", NAME)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
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
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 31: $std::IDENTIFIER
  // 32:   #
  // 33:     a grammar expression to match a valid Simplicity name (with optional namespace)
  // 34:     
  // 35:     See also: NAME
  // 36:   
  // 37:   NAME, optional("::", NAME)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__NAME();
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
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
  // 39: $$deserializers empty_table
  var._deserializers = get__empty_table();
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__4_1_std__register_deserializer(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // tag: 0
  // deserializer: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 52: !deserializers(tag) deserializer
  frame->slots[2] /* temp__1 */ = frame->slots[1] /* deserializer */;
  // 52: !deserializers(tag)
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
static void entry__5_1_std__get_deserialization_indent(void) {
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
  // 62: $$i 2
  ((CELL *)frame->slots[1])->contents /* i */ = number__2;
  // 63: $n length_of(text)
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
  // 64: $$indent 0
  ((CELL *)frame->slots[3])->contents /* indent */ = number__0;
  // 65: ... -> i <= n && text(i) == '@ht;':
  // 66:   inc &i
  // 67:   plus &indent 8
  frame->slots[4] /* temp__1 */ = create_closure(entry__5_3, 0);
  // 65: while -> i <= n && text(i) == '@ht;':
  // 66:   inc &i
  // 67:   plus &indent 8
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
  // 66: inc &i
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
  // 67: plus &indent 8
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
  // 65: ... i <= n
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
  // 65: ... i <= n
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
  // 65: ... text(i) == '@ht;'
  frame->slots[7] /* temp__4 */ = create_closure(entry__5_6, 0);
  // 65: ... i <= n && text(i) == '@ht;'
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
  // 65: ... text(i)
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
  // 65: ... text(i) == '@ht;'
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
  // 65: ... text(i) == '@ht;'
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
  // 65: ... :
  // 66:   inc &i
  // 67:   plus &indent 8
  frame->slots[8] /* temp__5 */ = create_closure(entry__5_10, 0);
  // 65: ... -> i <= n && text(i) == '@ht;':
  // 66:   inc &i
  // 67:   plus &indent 8
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
  // 68: ... -> i <= n && text(i) == ' ':
  // 69:   inc &i
  // 70:   inc &indent
  frame->slots[4] /* temp__1 */ = create_closure(entry__5_14, 0);
  // 68: while -> i <= n && text(i) == ' ':
  // 69:   inc &i
  // 70:   inc &indent
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
  // 69: inc &i
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
  // 70: inc &indent
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
  // 68: ... i <= n
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
  // 68: ... i <= n
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
  // 68: ... text(i) == ' '
  frame->slots[7] /* temp__4 */ = create_closure(entry__5_17, 0);
  // 68: ... i <= n && text(i) == ' '
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
  // 68: ... text(i)
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
  // 68: ... text(i) == ' '
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
  // 68: ... text(i) == ' '
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
  // 68: ... :
  // 69:   inc &i
  // 70:   inc &indent
  frame->slots[8] /* temp__5 */ = create_closure(entry__5_21, 0);
  // 68: ... -> i <= n && text(i) == ' ':
  // 69:   inc &i
  // 70:   inc &indent
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
  // 71: ... 1
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
  // 71: range &text i -1
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
  // 72: -> indent
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
  // 88: deserialize_stream text indent
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
  // 89: -> undefined undefined
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
  // 85: $indent get_deserialization_indent(&text)
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
  // 85: ... indent
  initialize_future(frame->slots[2] /* indent */, frame->slots[3] /* temp__1 */);
  // 87: indent > base_indent
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
  // 87: ... :
  // 88:   deserialize_stream text indent
  frame->slots[4] /* temp__2 */ = create_closure(entry__6_12, 0);
  // 86: if
  // 87:   indent > base_indent:
  // 88:     deserialize_stream text indent
  // 89:   -> undefined undefined
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
  // 91: ... -> text(1) == ' ': range &text 2 -1
  frame->slots[2] /* temp__1 */ = create_closure(entry__6_15, 0);
  // 91: while -> text(1) == ' ': range &text 2 -1
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
  // 91: ... 1
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
  // 91: ... range &text 2 -1
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
  // 91: ... text(1)
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
  // 91: ... text(1) == ' '
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
  // 91: ... : range &text 2 -1
  frame->slots[3] /* temp__3 */ = create_closure(entry__6_18, 0);
  // 91: ... -> text(1) == ' ': range &text 2 -1
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
  // 92: deserialize_stream text base_indent
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  arguments->slots[1] = frame->slots[1] /* base_indent */;
  result_count = frame->caller_result_count;
  myself = var._deserialize_stream;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__6_1_std__deserialize_item(void) {
  allocate_initialized_frame_gc(2, 9);
  // slot allocations:
  // text: 0
  // base_indent: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* text */ = create_cell_with_contents(arguments->slots[0]);
  // 84: length_of(text)
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
  // 84: length_of(text) >= 1
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
  // 84: length_of(text) >= 1
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
  // 84: ... text(1) == '@nl;'
  frame->slots[6] /* temp__5 */ = create_closure(entry__6_5, 0);
  // 84: length_of(text) >= 1 && text(1) == '@nl;'
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
  // 84: ... text(1)
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
  // 84: ... text(1) == '@nl;'
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
  // 84: ... text(1) == '@nl;'
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
  // 84: ... :
  // 85:   $indent get_deserialization_indent(&text)
  // 86:   if
  // 87:     indent > base_indent:
  // 88:       deserialize_stream text indent
  // 89:     -> undefined undefined
  frame->slots[7] /* temp__6 */ = create_closure(entry__6_9, 0);
  // 90: :
  // 91:   while -> text(1) == ' ': range &text 2 -1
  // 92:   deserialize_stream text base_indent
  frame->slots[8] /* temp__7 */ = create_closure(entry__6_14, 0);
  // 83: if
  // 84:   length_of(text) >= 1 && text(1) == '@nl;':
  // 85:     $indent get_deserialization_indent(&text)
  // 86:     if
  // 87:       indent > base_indent:
  // 88:         deserialize_stream text indent
  // 89:       -> undefined undefined
  // 90:   :
  // 91:     while -> text(1) == ' ': range &text 2 -1
  // 92:     deserialize_stream text base_indent
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
  // 113: ... text .has_prefix. "()"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  arguments->slots[1] = string__2d7981f4e6482bec;
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
  // 113: ... : return range(text 3 -1) prototype
  frame->slots[8] /* temp__2 */ = create_closure(entry__7_10, 0);
  // 113: if text .has_prefix. "()": return range(text 3 -1) prototype
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
  // 113: ... 1
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
  // 113: ... range(text 3 -1)
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
  // 113: ... return range(text 3 -1) prototype
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
  // 114: ... text(1)
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
  // 114: ... text(1) != '@nl;'
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
  // 114: ... text(1) != '@nl;'
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
  // 114: ... :
  // 115:   raise "Invalid @(name) object encountered during deserialisation!"
  frame->slots[10] /* temp__4 */ = create_closure(entry__7_17, 0);
  // 114: if text(1) != '@nl;':
  // 115:   raise "Invalid @(name) object encountered during deserialisation!"
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
  // 115: ... "Invalid @(name) object encountered during deserialisation!"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__76acaf9d04f58520;
  arguments->slots[1] = frame->slots[0] /* name */;
  arguments->slots[2] = string__770b9b2c5bac96f5;
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
  // 115: raise "Invalid @(name) object encountered during deserialisation!"
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
  // 116: $$obj prototype
  ((CELL *)frame->slots[6])->contents /* obj */ = frame->slots[3] /* prototype */;
  // 117: ... :
  // 118:   if length_of(text) == 0 || text(1) != '@nl;': return text obj
  // 119:   get_deserialization_indent $remaining_text $indent text
  // 120:   if indent <= base_indent: return text obj
  // 121:   !text remaining_text
  // 122:   match text IDENTIFIER $len
  // 123:   if len.is_undefined || text(len+1) != ':':
  // 124:     raise "Encountered invalid @(name) component during deserialisation!"
  // 125:   $tag range(text 1 len)
  // 126:   $attribute_setter attribute_setters(tag)
  // ...
  frame->slots[7] /* temp__1 */ = create_closure(entry__7_22, 0);
  // 117: forever:
  // 118:   if length_of(text) == 0 || text(1) != '@nl;': return text obj
  // 119:   get_deserialization_indent $remaining_text $indent text
  // 120:   if indent <= base_indent: return text obj
  // 121:   !text remaining_text
  // 122:   match text IDENTIFIER $len
  // 123:   if len.is_undefined || text(len+1) != ':':
  // 124:     raise "Encountered invalid @(name) component during deserialisation!"
  // 125:   $tag range(text 1 len)
  // 126:   $attribute_setter attribute_setters(tag)
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__forever();
  func = myself->type;
  frame->cont = cont__7_62;
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
  // 118: ... length_of(text)
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
  // 118: ... length_of(text) == 0
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
  // 118: ... text(1) != '@nl;'
  frame->slots[14] /* temp__4 */ = create_closure(entry__7_25, 0);
  // 118: ... length_of(text) == 0 || text(1) != '@nl;'
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
  // 118: ... text(1)
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
  // 118: ... text(1) != '@nl;'
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
  // 118: ... text(1) != '@nl;'
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
  // 118: ... text(1) != '@nl;'
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
  // 118: ... : return text obj
  frame->slots[15] /* temp__5 */ = create_closure(entry__7_30, 0);
  // 118: if length_of(text) == 0 || text(1) != '@nl;': return text obj
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
  // 118: ... return text obj
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
  // 119: get_deserialization_indent $remaining_text $indent text
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
  // 119: ... remaining_text
  initialize_future(frame->slots[6] /* remaining_text */, frame->slots[11] /* temp__1 */);
  // 119: ... indent
  initialize_future(frame->slots[7] /* indent */, frame->slots[12] /* temp__2 */);
  // 120: ... indent <= base_indent
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
  // 120: ... indent <= base_indent
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
  // 120: ... : return text obj
  frame->slots[13] /* temp__3 */ = create_closure(entry__7_35, 0);
  // 120: if indent <= base_indent: return text obj
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
  // 120: ... return text obj
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
  // 121: !text remaining_text
  ((CELL *)frame->slots[0])->contents /* text */ = frame->slots[6] /* remaining_text */;
  // 122: match text IDENTIFIER $len
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
  // 123: ... len.is_undefined
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
  // 123: ... text(len+1) != ':'
  frame->slots[13] /* temp__3 */ = create_closure(entry__7_39, 0);
  // 123: ... len.is_undefined || text(len+1) != ':'
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
  // 123: ... len+1
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
  // 123: ... text(len+1)
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
  // 123: ... text(len+1) != ':'
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
  // 123: ... text(len+1) != ':'
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
  // 123: ... text(len+1) != ':'
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
  // 123: ... :
  // 124:   raise "Encountered invalid @(name) component during deserialisation!"
  frame->slots[14] /* temp__4 */ = create_closure(entry__7_45, 0);
  // 123: if len.is_undefined || text(len+1) != ':':
  // 124:   raise "Encountered invalid @(name) component during deserialisation!"
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
  // 124: ... "Encountered invalid @(name) component during deserialisation!"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__deed742f6908f861;
  arguments->slots[1] = frame->slots[0] /* name */;
  arguments->slots[2] = string__dc7e95992fac4f0d;
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
  // 124: raise "Encountered invalid @(name) component during deserialisation!"
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
  // 125: $tag range(text 1 len)
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
  // 126: $attribute_setter attribute_setters(tag)
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
  // 127: ... attribute_setter.is_undefined
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
  // 127: ... :
  // 128:   raise "Encountered unknown @(name) component during deserialisation!"
  frame->slots[12] /* temp__2 */ = create_closure(entry__7_53, 0);
  // 127: if attribute_setter.is_undefined:
  // 128:   raise "Encountered unknown @(name) component during deserialisation!"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__1 */;
  arguments->slots[1] = frame->slots[12] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__7_56;
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
  // 128: ... "Encountered unknown @(name) component during deserialisation!"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__d8ed73a1e9580be1;
  arguments->slots[1] = frame->slots[0] /* name */;
  arguments->slots[2] = string__dc7e95992fac4f0d;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__7_55;
}
static void cont__7_55(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 128: raise "Encountered unknown @(name) component during deserialisation!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__raise();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_56(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 129: ... len+2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* len */;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__7_57;
}
static void cont__7_57(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 129: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__7_58;
}
static void cont__7_58(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__2 */ = arguments->slots[0];
  // 129: range &text len+2 -1
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  arguments->slots[1] = frame->slots[11] /* temp__1 */;
  arguments->slots[2] = frame->slots[12] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__7_59;
}
static void cont__7_59(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* text */ = arguments->slots[0];
  // 130: ... deserialize_item(&text indent)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  arguments->slots[1] = frame->slots[7] /* indent */;
  result_count = 2;
  myself = get__deserialize_item();
  func = myself->type;
  frame->cont = cont__7_60;
}
static void cont__7_60(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* text */ = arguments->slots[0];
  frame->slots[11] /* temp__1 */ = arguments->slots[1];
  // 130: attribute_setter &obj deserialize_item(&text indent)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* obj */;
  arguments->slots[1] = frame->slots[11] /* temp__1 */;
  result_count = 1;
  myself = frame->slots[10] /* attribute_setter */;
  func = myself->type;
  frame->cont = cont__7_61;
}
static void cont__7_61(void) {
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
static void cont__7_62(void) {
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__7_1_std__create_deserializer(void) {
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
  // 104: $$attribute_setters empty_table
  ((CELL *)frame->slots[3])->contents /* attribute_setters */ = get__empty_table();
  // 105: ... : (attribute_name attribute_setter)
  // 106:   !attribute_setters(range(attribute_name 3 -1)) attribute_setter
  frame->slots[4] /* temp__1 */ = create_closure(entry__7_2, 2);
  // 105: for_each_pair attributes: (attribute_name attribute_setter)
  // 106:   !attribute_setters(range(attribute_name 3 -1)) attribute_setter
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
  // 106: !attribute_setters(range(attribute_name 3 -1)) attribute_setter
  frame->slots[3] /* temp__1 */ = frame->slots[1] /* attribute_setter */;
  // 106: ... 1
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
  // 106: ... range(attribute_name 3 -1)
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
  // 106: !attribute_setters(range(attribute_name 3 -1))
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
  // 107: ... :
  // 108:   (
  // 109:     $text
  // 110:     base_indent
  // 111:     -> return
  // 112:   )
  // 113:   if text .has_prefix. "()": return range(text 3 -1) prototype
  // 114:   if text(1) != '@nl;':
  // 115:     raise "Invalid @(name) object encountered during deserialisation!"
  // 116:   $$obj prototype
  // ...
  frame->slots[4] /* temp__1 */ = create_closure(entry__7_7, 2);
  // 107: -> :
  // 108:   (
  // 109:     $text
  // 110:     base_indent
  // 111:     -> return
  // 112:   )
  // 113:   if text .has_prefix. "()": return range(text 3 -1) prototype
  // 114:   if text(1) != '@nl;':
  // 115:     raise "Invalid @(name) object encountered during deserialisation!"
  // 116:   $$obj prototype
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__8_1_deserialize_stream(void) {
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
  // 139: text(1)
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
  // 140: ... :
  // 141:   $$str ""
  // 142:   $$i 2
  // 143:   $n length_of(text)
  // 144:   while -> i <= n:
  // 145:     $chr text(i)
  // 146:     case
  // 147:       chr
  // 148:       '@quot;':
  // 149:         return range(text i+1 -1) str
  // ...
  frame->slots[4] /* temp__2 */ = create_closure(entry__8_3, 0);
  // 161: ... :
  // 162:   $n length_of(text)
  // 163:   if n < 3:
  // 164:     raise "Invalid character constant encountered during deserialization!"
  // 165:   $chr text(2)
  // 166:   if
  // 167:     chr == '@@':
  // 168:       $escape_text range(text 3 -1)
  // 169:       parse_integer escape_text $rest_text $value
  // 170:       $i 3+length_of(escape_text)-length_of(rest_text)
  // ...
  frame->slots[5] /* temp__3 */ = create_closure(entry__8_44, 0);
  // 186: '0' .. '9'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__48;
  arguments->slots[1] = character__57;
  result_count = 1;
  myself = get__std__value_range();
  func = myself->type;
  frame->cont = cont__8_91;
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
  // 168: ... 1
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
  // 168: $escape_text range(text 3 -1)
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
  // 169: parse_integer escape_text $rest_text $value
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
  // 169: ... rest_text
  initialize_future(frame->slots[4] /* rest_text */, frame->slots[7] /* temp__1 */);
  // 169: ... value
  initialize_future(frame->slots[5] /* value */, frame->slots[8] /* temp__2 */);
  // 170: ... length_of(escape_text)
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
  // 170: ... 3+length_of(escape_text)
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
  // 170: ... length_of(rest_text)
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
  // 170: $i 3+length_of(escape_text)-length_of(rest_text)
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
  // 173: value.is_undefined
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
  // 174: i+1
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
  // 174: i+1 > n
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
  // 175: text(i)
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
  // 175: text(i) != ';'
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
  // 175: text(i) != ';'
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
  // 176: text(i+1) != '@apos;'
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
  // 176: ... i+1
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
  // 176: text(i+1)
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
  // 176: text(i+1) != '@apos;'
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
  // 176: text(i+1) != '@apos;'
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
  // 176: text(i+1) != '@apos;'
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
  // 171: if
  // 172:   ||
  // 173:     value.is_undefined
  // 174:     i+1 > n
  // 175:     text(i) != ';'
  // 176:     text(i+1) != '@apos;'
  // 177:   :
  // 178:     raise
  // 179:       "Invalid character escape encountered during deserialization!"
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
  // 178: raise
  // 179:   "Invalid character escape encountered during deserialization!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__c08bfa6e27fae532;
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
  // 180: ... i+2
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
  // 180: ... 1
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
  // 180: ... range(text i+2 -1)
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
  // 180: ... character(value)
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
  // 180: return range(text i+2 -1) character(value)
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
  // 182: ... text(3)
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
  // 182: ... text(3) != '@apos;'
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
  // 182: ... text(3) != '@apos;'
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
  // 182: if text(3) != '@apos;':
  // 183:   raise
  // 184:     "Invalid character constant encountered during deserialization!"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = func__8_87;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__8_88;
}
static void entry__8_87(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 183: raise
  // 184:   "Invalid character constant encountered during deserialization!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__6ce496bd70576317;
  result_count = frame->caller_result_count;
  myself = get__raise();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__8_88(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 185: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__8_89;
}
static void cont__8_89(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 185: ... range(text 4 -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  arguments->slots[1] = number__4;
  arguments->slots[2] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__8_90;
}
static void cont__8_90(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 185: return range(text 4 -1) chr
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
  // 141: $$str ""
  ((CELL *)frame->slots[2])->contents /* str */ = empty_string;
  // 142: $$i 2
  ((CELL *)frame->slots[3])->contents /* i */ = number__2;
  // 143: $n length_of(text)
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
  // 144: ... -> i <= n:
  // 145:   $chr text(i)
  // 146:   case
  // 147:     chr
  // 148:     '@quot;':
  // 149:       return range(text i+1 -1) str
  // 150:     '@@':
  // 151:       $escape_text range(text i+1 -1)
  // 152:       parse_integer escape_text $rest_text $value
  // 153:       plus &i 1+length_of(escape_text)-length_of(rest_text)
  // ...
  frame->slots[5] /* temp__1 */ = create_closure(entry__8_5, 0);
  // 144: while -> i <= n:
  // 145:   $chr text(i)
  // 146:   case
  // 147:     chr
  // 148:     '@quot;':
  // 149:       return range(text i+1 -1) str
  // 150:     '@@':
  // 151:       $escape_text range(text i+1 -1)
  // 152:       parse_integer escape_text $rest_text $value
  // 153:       plus &i 1+length_of(escape_text)-length_of(rest_text)
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
  // 145: $chr text(i)
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
  // 148: ... :
  // 149:   return range(text i+1 -1) str
  frame->slots[6] /* temp__1 */ = create_closure(entry__8_10, 0);
  // 150: ... :
  // 151:   $escape_text range(text i+1 -1)
  // 152:   parse_integer escape_text $rest_text $value
  // 153:   plus &i 1+length_of(escape_text)-length_of(rest_text)
  // 154:   if value.is_undefined || i > n || text(i) != ';':
  // 155:     raise "Invalid string escape encountered during deserialization!"
  // 156:   push &str character(value)
  frame->slots[7] /* temp__2 */ = create_closure(entry__8_14, 0);
  // 157: :
  // 158:   push &str chr
  frame->slots[8] /* temp__3 */ = create_closure(entry__8_38, 0);
  // 146: case
  // 147:   chr
  // 148:   '@quot;':
  // 149:     return range(text i+1 -1) str
  // 150:   '@@':
  // 151:     $escape_text range(text i+1 -1)
  // 152:     parse_integer escape_text $rest_text $value
  // 153:     plus &i 1+length_of(escape_text)-length_of(rest_text)
  // 154:     if value.is_undefined || i > n || text(i) != ';':
  // 155:       raise "Invalid string escape encountered during deserialization!"
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
  // 149: ... i+1
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
  // 149: ... 1
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
  // 149: ... range(text i+1 -1)
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
  // 149: return range(text i+1 -1) str
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
  // 151: ... i+1
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
  // 151: ... 1
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
  // 151: $escape_text range(text i+1 -1)
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
  // 152: parse_integer escape_text $rest_text $value
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
  // 152: ... rest_text
  initialize_future(frame->slots[5] /* rest_text */, frame->slots[7] /* temp__1 */);
  // 152: ... value
  initialize_future(frame->slots[6] /* value */, frame->slots[8] /* temp__2 */);
  // 153: ... length_of(escape_text)
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
  // 153: ... 1+length_of(escape_text)
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
  // 153: ... length_of(rest_text)
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
  // 153: ... 1+length_of(escape_text)-length_of(rest_text)
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
  // 153: plus &i 1+length_of(escape_text)-length_of(rest_text)
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
  // 154: ... value.is_undefined
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
  // 154: ... i > n || text(i) != ';'
  frame->slots[9] /* temp__3 */ = create_closure(entry__8_25, 0);
  // 154: ... value.is_undefined || i > n || text(i) != ';'
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
  // 154: ... i > n
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
  // 154: ... text(i) != ';'
  frame->slots[5] /* temp__3 */ = create_closure(entry__8_27, 0);
  // 154: ... i > n || text(i) != ';'
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
  // 154: ... text(i)
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
  // 154: ... text(i) != ';'
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
  // 154: ... text(i) != ';'
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
  // 154: ... text(i) != ';'
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
  // 154: ... i > n || text(i) != ';'
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
  // 154: if value.is_undefined || i > n || text(i) != ';':
  // 155:   raise "Invalid string escape encountered during deserialization!"
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
  // 155: raise "Invalid string escape encountered during deserialization!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__8d42cc379b749591;
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
  // 156: ... character(value)
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
  // 156: push &str character(value)
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
  // 158: push &str chr
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
  // 159: inc &i
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
  // 144: ... i <= n
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
  // 144: ... i <= n
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
  // 144: ... :
  // 145:   $chr text(i)
  // 146:   case
  // 147:     chr
  // 148:     '@quot;':
  // 149:       return range(text i+1 -1) str
  // 150:     '@@':
  // 151:       $escape_text range(text i+1 -1)
  // 152:       parse_integer escape_text $rest_text $value
  // 153:       plus &i 1+length_of(escape_text)-length_of(rest_text)
  // ...
  frame->slots[7] /* temp__3 */ = create_closure(entry__8_8, 0);
  // 144: ... -> i <= n:
  // 145:   $chr text(i)
  // 146:   case
  // 147:     chr
  // 148:     '@quot;':
  // 149:       return range(text i+1 -1) str
  // 150:     '@@':
  // 151:       $escape_text range(text i+1 -1)
  // 152:       parse_integer escape_text $rest_text $value
  // 153:       plus &i 1+length_of(escape_text)-length_of(rest_text)
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
  // 160: raise "Unterminated string encountered during deserialization!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__e4bd1ec7a051e115;
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
  // 162: $n length_of(text)
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
  // 163: ... n < 3
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
  // 163: if n < 3:
  // 164:   raise "Invalid character constant encountered during deserialization!"
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
  // 164: raise "Invalid character constant encountered during deserialization!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__6ce496bd70576317;
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
  // 165: $chr text(2)
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
  // 167: chr == '@@'
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
  // 167: ... :
  // 168:   $escape_text range(text 3 -1)
  // 169:   parse_integer escape_text $rest_text $value
  // 170:   $i 3+length_of(escape_text)-length_of(rest_text)
  // 171:   if
  // 172:     ||
  // 173:       value.is_undefined
  // 174:       i+1 > n
  // 175:       text(i) != ';'
  // 176:       text(i+1) != '@apos;'
  // ...
  frame->slots[5] /* temp__2 */ = create_closure(entry__8_52, 0);
  // 181: :
  // 182:   if text(3) != '@apos;':
  // 183:     raise
  // 184:       "Invalid character constant encountered during deserialization!"
  // 185:   return range(text 4 -1) chr
  frame->slots[6] /* temp__3 */ = create_closure(entry__8_83, 0);
  // 166: if
  // 167:   chr == '@@':
  // 168:     $escape_text range(text 3 -1)
  // 169:     parse_integer escape_text $rest_text $value
  // 170:     $i 3+length_of(escape_text)-length_of(rest_text)
  // 171:     if
  // 172:       ||
  // 173:         value.is_undefined
  // 174:         i+1 > n
  // 175:         text(i) != ';'
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
static void cont__8_91(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__4 */ = arguments->slots[0];
  // 186: ... :
  // 187:   $val parse_number(&text)
  // 188:   if val.is_undefined:
  // 189:     raise "Invalid numeric constant encountered during deserialization!"
  // 190:   return text val
  frame->slots[7] /* temp__5 */ = create_closure(entry__8_92, 0);
  // 191: :
  // 192:   match text IDENTIFIER $len
  // 193:   if
  // 194:     len.is_defined:
  // 195:       $tag range(text 1 len)
  // 196:       $deserializer deserializers(tag)
  // 197:       if
  // 198:         deserializer.is_defined:
  // 199:           range &text len+1 -1
  // 200:           deserializer text indent
  // ...
  frame->slots[8] /* temp__6 */ = create_closure(entry__8_98, 0);
  // 138: case
  // 139:   text(1)
  // 140:   '@quot;':
  // 141:     $$str ""
  // 142:     $$i 2
  // 143:     $n length_of(text)
  // 144:     while -> i <= n:
  // 145:       $chr text(i)
  // 146:       case
  // 147:         chr
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
  frame->cont = cont__8_115;
}
static void entry__8_105(void) {
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
  // 199: ... len+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* len */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__8_106;
}
static void cont__8_106(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 199: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__8_107;
}
static void cont__8_107(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 199: range &text len+1 -1
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  arguments->slots[2] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__8_108;
}
static void cont__8_108(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* text */ = arguments->slots[0];
  // 200: deserializer text indent
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  arguments->slots[1] = frame->slots[3] /* indent */;
  result_count = frame->caller_result_count;
  myself = frame->slots[2] /* deserializer */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__8_109(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // tag: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* tag */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 202: ... "
  // 203:   No deserializer defined for "@(tag)@quot;!@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__8b7292a23e049581;
  arguments->slots[1] = frame->slots[0] /* tag */;
  arguments->slots[2] = string__2d7981f4e6182be4;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__8_112;
}
static void cont__8_112(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 202: raise "
  // 203:   No deserializer defined for "@(tag)@quot;!@
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__raise();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__8_101(void) {
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
  // 195: $tag range(text 1 len)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[1] /* len */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__8_102;
}
static void cont__8_102(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* tag */, arguments->slots[0]);
  // 196: $deserializer deserializers(tag)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* tag */;
  result_count = 1;
  myself = var._deserializers;
  func = myself->type;
  frame->cont = cont__8_103;
}
static void cont__8_103(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* deserializer */, arguments->slots[0]);
  // 198: deserializer.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* deserializer */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__8_104;
}
static void cont__8_104(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 198: ... :
  // 199:   range &text len+1 -1
  // 200:   deserializer text indent
  frame->slots[6] /* temp__2 */ = create_closure(entry__8_105, 0);
  // 201: :
  // 202:   raise "
  // 203:     No deserializer defined for "@(tag)@quot;!@
  frame->slots[7] /* temp__3 */ = create_closure(entry__8_109, 0);
  // 197: if
  // 198:   deserializer.is_defined:
  // 199:     range &text len+1 -1
  // 200:     deserializer text indent
  // 201:   :
  // 202:     raise "
  // 203:       No deserializer defined for "@(tag)@quot;!@
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
static void entry__8_113(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 205: raise "No valid tag found while attempting to deserialize text!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__e89843a7c2547e3c;
  result_count = frame->caller_result_count;
  myself = get__raise();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__8_92(void) {
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
  // 187: $val parse_number(&text)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  result_count = 2;
  myself = get__parse_number();
  func = myself->type;
  frame->cont = cont__8_93;
}
static void cont__8_93(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* text */ = arguments->slots[0];
  frame->slots[3] /* temp__1 */ = arguments->slots[1];
  // 187: ... val
  initialize_future(frame->slots[2] /* val */, frame->slots[3] /* temp__1 */);
  // 188: ... val.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* val */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__8_94;
}
static void cont__8_94(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 188: if val.is_undefined:
  // 189:   raise "Invalid numeric constant encountered during deserialization!"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = func__8_95;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__8_97;
}
static void entry__8_95(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 189: raise "Invalid numeric constant encountered during deserialization!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__a7e8c0fdec6da36f;
  result_count = frame->caller_result_count;
  myself = get__raise();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__8_97(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 190: return text val
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  arguments->slots[1] = frame->slots[2] /* val */;
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__8_98(void) {
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
  // 192: match text IDENTIFIER $len
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  arguments->slots[1] = get__IDENTIFIER();
  result_count = 1;
  myself = get__match();
  func = myself->type;
  frame->cont = cont__8_99;
}
static void cont__8_99(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* len */, arguments->slots[0]);
  // 194: len.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* len */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__8_100;
}
static void cont__8_100(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 194: ... :
  // 195:   $tag range(text 1 len)
  // 196:   $deserializer deserializers(tag)
  // 197:   if
  // 198:     deserializer.is_defined:
  // 199:       range &text len+1 -1
  // 200:       deserializer text indent
  // 201:     :
  // 202:       raise "
  // 203:         No deserializer defined for "@(tag)@quot;!@
  frame->slots[4] /* temp__2 */ = create_closure(entry__8_101, 0);
  // 193: if
  // 194:   len.is_defined:
  // 195:     $tag range(text 1 len)
  // 196:     $deserializer deserializers(tag)
  // 197:     if
  // 198:       deserializer.is_defined:
  // 199:         range &text len+1 -1
  // 200:         deserializer text indent
  // 201:       :
  // 202:         raise "
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  arguments->slots[2] = func__8_113;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__8_115(void) {
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__9_1_std__deserialize(void) {
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
  // 217: deserialize_stream text 0 $remaining_text $obj
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
  // 217: ... remaining_text
  initialize_future(frame->slots[1] /* remaining_text */, frame->slots[3] /* temp__1 */);
  // 217: ... obj
  initialize_future(frame->slots[2] /* obj */, frame->slots[4] /* temp__2 */);
  // 218: ... remaining_text == ""
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
  // 218: ... -> obj
  frame->slots[5] /* temp__3 */ = create_closure(entry__9_4, 0);
  // 218: ... if(remaining_text == "" (-> obj) -> undefined)
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
  // 218: ... -> obj
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
  // 218: ... -> undefined
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
  // 218: -> if(remaining_text == "" (-> obj) -> undefined)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
EXPORT void collect__basic__deserialize(void) {
  var.std__NAME = collect_node(var.std__NAME);
  var.std__IDENTIFIER = collect_node(var.std__IDENTIFIER);
  var._deserializers = collect_node(var._deserializers);
  var.std__register_deserializer = collect_node(var.std__register_deserializer);
  var.std__get_deserialization_indent = collect_node(var.std__get_deserialization_indent);
  var.std__deserialize_item = collect_node(var.std__deserialize_item);
  var.std__create_deserializer = collect_node(var.std__create_deserializer);
  var._deserialize_stream = collect_node(var._deserialize_stream);
  var.std__deserialize = collect_node(var.std__deserialize);
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
  character__9 = from_uchar32(9);
  character__57 = from_uchar32(57);
  character__10 = from_uchar32(10);
  character__58 = from_uchar32(58);
  number__0 = from_uint32(0U);
  character__48 = from_uchar32(48);
  number__3 = from_uint32(3U);
  number__4 = from_uint32(4U);
  character__95 = from_uchar32(95);
  number__8 = from_uint32(8U);
  character__64 = from_uchar32(64);
  character__34 = from_uchar32(34);
  character__39 = from_uchar32(39);
  character__32 = from_uchar32(32);
  character__59 = from_uchar32(59);
  number__1 = from_uint32(1U);
  number__2 = from_uint32(2U);
  func__4_1_std__register_deserializer = create_function(entry__4_1_std__register_deserializer, 2);
  func__5_1_std__get_deserialization_indent = create_function(entry__5_1_std__get_deserialization_indent, 1);
  func__6_13 = create_function(entry__6_13, 0);
  func__6_1_std__deserialize_item = create_function(entry__6_1_std__deserialize_item, 2);
  string__2d7981f4e6482bec = from_latin_1_string("()", 2);
  string__76acaf9d04f58520 = from_latin_1_string("Invalid ", 8);
  string__770b9b2c5bac96f5 = from_latin_1_string(" object encountered during deserialisation!", 43);
  string__deed742f6908f861 = from_latin_1_string("Encountered invalid ", 20);
  string__dc7e95992fac4f0d = from_latin_1_string(" component during deserialisation!", 34);
  string__d8ed73a1e9580be1 = from_latin_1_string("Encountered unknown ", 20);
  func__7_1_std__create_deserializer = create_function(entry__7_1_std__create_deserializer, -1);
  string__8d42cc379b749591 = from_latin_1_string("Invalid string escape encountered during deserialization!", 57);
  func__8_33 = create_function(entry__8_33, 0);
  string__e4bd1ec7a051e115 = from_latin_1_string("Unterminated string encountered during deserialization!", 55);
  string__6ce496bd70576317 = from_latin_1_string("Invalid character constant encountered during deserialization!", 62);
  func__8_47 = create_function(entry__8_47, 0);
  string__c08bfa6e27fae532 = from_latin_1_string("Invalid character escape encountered during deserialization!", 60);
  func__8_76 = create_function(entry__8_76, 0);
  func__8_87 = create_function(entry__8_87, 0);
  string__a7e8c0fdec6da36f = from_latin_1_string("Invalid numeric constant encountered during deserialization!", 60);
  func__8_95 = create_function(entry__8_95, 0);
  string__8b7292a23e049581 = from_latin_1_string("No deserializer defined for \042", 29);
  string__2d7981f4e6182be4 = from_latin_1_string("\042!", 2);
  string__e89843a7c2547e3c = from_latin_1_string("No valid tag found while attempting to deserialize text!", 56);
  func__8_113 = create_function(entry__8_113, 0);
  func__8_1_deserialize_stream = create_function(entry__8_1_deserialize_stream, 2);
  func__9_5 = create_function(entry__9_5, 0);
  func__9_1_std__deserialize = create_function(entry__9_1_std__deserialize, 1);
  string__2d7981f4e6d82bff = from_latin_1_string("::", 2);
}

static int already_run_phase_3 = false;

EXPORT void phase_3__basic__deserialize(void) {
  if (already_run_phase_3) return;
  already_run_phase_3 = true;
  set_module("basic__deserialize");
  set_used_namespaces(used_namespaces);
  define_single_assign_static("std", "NAME", get__std__NAME, &var.std__NAME);
  define_single_assign_static("std", "IDENTIFIER", get__std__IDENTIFIER, &var.std__IDENTIFIER);
  define_single_assign_static("std", "register_deserializer", get__std__register_deserializer, &var.std__register_deserializer);
  define_single_assign_static("std", "get_deserialization_indent", get__std__get_deserialization_indent, &var.std__get_deserialization_indent);
  define_single_assign_static("std", "deserialize_item", get__std__deserialize_item, &var.std__deserialize_item);
  define_single_assign_static("std", "create_deserializer", get__std__create_deserializer, &var.std__create_deserializer);
  define_single_assign_static("std", "deserialize", get__std__deserialize, &var.std__deserialize);
}

static int already_run_phase_4 = false;

EXPORT void phase_4__basic__deserialize(void) {
  if (already_run_phase_4) return;
  already_run_phase_4 = true;
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

static int already_run_phase_5 = false;

EXPORT void phase_5__basic__deserialize(void) {
  if (already_run_phase_5) return;
  already_run_phase_5 = true;
  assign_variable(&var.std__register_deserializer, &func__4_1_std__register_deserializer);
  assign_variable(&var.std__get_deserialization_indent, &func__5_1_std__get_deserialization_indent);
  assign_variable(&var.std__deserialize_item, &func__6_1_std__deserialize_item);
  assign_variable(&var.std__create_deserializer, &func__7_1_std__create_deserializer);
  assign_variable(&var._deserialize_stream, &func__8_1_deserialize_stream);
  assign_variable(&var.std__deserialize, &func__9_1_std__deserialize);
}

static int already_run_phase_6 = false;

EXPORT void phase_6__basic__deserialize(void) {
  if (already_run_phase_6) return;
  already_run_phase_6 = true;
  register_collector(collect__basic__deserialize);
}
