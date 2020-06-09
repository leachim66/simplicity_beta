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
IMPORT NODE *create_future(void);
IMPORT NODE *create_cell(void);
REGISTER int argument_count ASM("ebx");
IMPORT void invalid_arguments_error(void);
IMPORT NODE *create_cell_with_contents(NODE *contents);
REGISTER FRAME *arguments ASM("r12");
IMPORT NODE *create_closure(FUNC type, int par_count);
IMPORT void initialize_future(NODE *var, NODE *val);
IMPORT NODE *clone_object_and_attributes(NODE *node);
typedef struct CELL {
  FUNC type;
  struct ATTRIBUTES *attributes;
  NODE *contents;
} CELL;
IMPORT void *update_start_p;
IMPORT void *node_p;
IMPORT void set_attribute_value(ATTRIBUTES *attributes, int idx, void *attr);
IMPORT int result_count;
REGISTER NODE *myself ASM("r13");
IMPORT void invalid_results_error(void);
IMPORT NODE *create_continuation(void);
IMPORT void initialize_maybe_future(NODE *var, NODE *val);
IMPORT NODE *empty_string;
IMPORT NODE *undefined;
IMPORT NODE *collect_node(NODE *node);
IMPORT void register_module_info(MODULE_INFO *info);
IMPORT void set_module(const char *name);
IMPORT NODE *from_uchar32(unsigned int chr);
IMPORT NODE *from_uint32(uint32_t val);
IMPORT NODE *from_latin_1_string(const char *str, long len);
IMPORT NODE *create_function(FUNC func, int par_count);
IMPORT void set_used_namespaces(const char **namespaces);
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
static NODE_GETTER get__append;
static NODE_GETTER get_value_or_future__append;
static NODE_GETTER get__case;
static NODE_GETTER get_value_or_future__case;
static NODE_GETTER get__count_occurrences;
static NODE_GETTER get_value_or_future__count_occurrences;
static NODE_GETTER get__dec;
static NODE_GETTER get_value_or_future__dec;
static NODE_GETTER get__do;
static NODE_GETTER get_value_or_future__do;
static NODE_GETTER get__empty_list;
static NODE_GETTER get_value_or_future__empty_list;
static NODE_GETTER get__ewrite;
static NODE_GETTER get_value_or_future__ewrite;
static NODE_GETTER get__exit;
static NODE_GETTER get_value_or_future__exit;
static NODE_GETTER get__forever;
static NODE_GETTER get_value_or_future__forever;
static NODE_GETTER get__if;
static NODE_GETTER get_value_or_future__if;
static NODE_GETTER get__ignore;
static NODE_GETTER get_value_or_future__ignore;
static NODE_GETTER get__inc;
static NODE_GETTER get_value_or_future__inc;
static NODE_GETTER get__indent_marker;
static NODE_GETTER get_value_or_future__indent_marker;
static int poly_idx__indents_of;
static NODE_GETTER get__indents_of;
static NODE_GETTER get__is_odd;
static NODE_GETTER get_value_or_future__is_odd;
static NODE_GETTER get__length_of;
static NODE_GETTER get_value_or_future__length_of;
static NODE_GETTER get__line_no_of;
static NODE_GETTER get_value_or_future__line_no_of;
static NODE_GETTER get__module_name;
static NODE_GETTER get_value_or_future__module_name;
static NODE_GETTER get__newline;
static NODE_GETTER get_value_or_future__newline;
static NODE_GETTER get__outdent_marker;
static NODE_GETTER get_value_or_future__outdent_marker;
static NODE_GETTER get__plus;
static NODE_GETTER get_value_or_future__plus;
static NODE_GETTER get__push;
static NODE_GETTER get_value_or_future__push;
static NODE_GETTER get__range;
static NODE_GETTER get_value_or_future__range;
static NODE_GETTER get__reduce_to;
static NODE_GETTER get_value_or_future__reduce_to;
static NODE_GETTER get__repeat;
static NODE_GETTER get_value_or_future__repeat;
static int poly_idx__source_of;
static NODE_GETTER get__source_of;
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
static NODE_GETTER get__std__string;
static NODE_GETTER get_value_or_future__std__string;
static NODE_GETTER get__text_of;
static NODE_GETTER get_value_or_future__text_of;
static NODE_GETTER get__to_upper_case;
static NODE_GETTER get_value_or_future__to_upper_case;
static NODE_GETTER get__undefined;
static NODE_GETTER get_value_or_future__undefined;
static NODE_GETTER get__while;
static NODE_GETTER get_value_or_future__while;
static struct {
  NODE *compiler__indent_marker;
  NODE *compiler__outdent_marker;
  NODE *compiler__newline;
  NODE *compiler__tokenize;
} var;
static const char *var_names[] = {
};
static NODE *get__compiler__indent_marker(void) {
  return var.compiler__indent_marker;
}
static NODE *get__compiler__outdent_marker(void) {
  return var.compiler__outdent_marker;
}
static NODE *get__compiler__newline(void) {
  return var.compiler__newline;
}
static NODE *func__compiler__tokenize;
static void entry__compiler__tokenize(void);
static FRAME_INFO frame__compiler__tokenize = {11, {"fragment", "text", "i", "s", "new_text", "pending_newlines", "quote_count", "TokenizationError", "skip_line", "get_indent", "convert"}};
static NODE *func__compiler__tokenize_2;
static void entry__compiler__tokenize_2(void);
static FRAME_INFO frame__compiler__tokenize_2 = {5, {"msg", "fragment", "text", "i", "line_no"}};
static void cont__compiler__tokenize_3(void);
static void cont__compiler__tokenize_4(void);
static void cont__compiler__tokenize_5(void);
static void cont__compiler__tokenize_6(void);
static void cont__compiler__tokenize_7(void);
static void cont__compiler__tokenize_8(void);
static void cont__compiler__tokenize_9(void);
static void cont__compiler__tokenize_10(void);
static NODE *string__a18ab04649b43ca6;
static NODE *string__6c6619488b29e163;
static NODE *string__fa730c15ff96bc6;
static NODE *string__2d7981f4e6002bcf;
static void cont__compiler__tokenize_15(void);
static void cont__compiler__tokenize_16(void);
static NODE *func__compiler__tokenize_17;
static void entry__compiler__tokenize_17(void);
static FRAME_INFO frame__compiler__tokenize_17 = {4, {"quote_count", "text", "i", "TokenizationError"}};
static NODE *func__compiler__tokenize_18;
static void entry__compiler__tokenize_18(void);
static FRAME_INFO frame__compiler__tokenize_18 = {4, {"text", "i", "quote_count", "TokenizationError"}};
static void cont__compiler__tokenize_19(void);
static void cont__compiler__tokenize_20(void);
static void cont__compiler__tokenize_21(void);
static NODE *func__compiler__tokenize_22;
static void entry__compiler__tokenize_22(void);
static FRAME_INFO frame__compiler__tokenize_22 = {4, {"text", "i", "quote_count", "TokenizationError"}};
static void cont__compiler__tokenize_23(void);
static NODE *func__compiler__tokenize_24;
static void entry__compiler__tokenize_24(void);
static FRAME_INFO frame__compiler__tokenize_24 = {1, {"quote_count"}};
static void cont__compiler__tokenize_25(void);
static NODE *func__compiler__tokenize_26;
static void entry__compiler__tokenize_26(void);
static FRAME_INFO frame__compiler__tokenize_26 = {1, {"TokenizationError"}};
static NODE *string__dd17af2f619a6908;
static void cont__compiler__tokenize_28(void);
static void cont__compiler__tokenize_29(void);
static NODE *func__compiler__tokenize_30;
static void entry__compiler__tokenize_30(void);
static FRAME_INFO frame__compiler__tokenize_30 = {6, {"return", "pending_newlines", "i", "text", "TokenizationError", "indent"}};
static NODE *func__compiler__tokenize_31;
static void entry__compiler__tokenize_31(void);
static FRAME_INFO frame__compiler__tokenize_31 = {5, {"break", "i", "text", "return", "pending_newlines"}};
static NODE *func__compiler__tokenize_32;
static void entry__compiler__tokenize_32(void);
static FRAME_INFO frame__compiler__tokenize_32 = {5, {"i", "text", "return", "break", "pending_newlines"}};
static void cont__compiler__tokenize_33(void);
static void cont__compiler__tokenize_34(void);
static NODE *func__compiler__tokenize_35;
static void entry__compiler__tokenize_35(void);
static FRAME_INFO frame__compiler__tokenize_35 = {1, {"return"}};
static void cont__compiler__tokenize_36(void);
static void cont__compiler__tokenize_37(void);
static void cont__compiler__tokenize_38(void);
static void cont__compiler__tokenize_39(void);
static void cont__compiler__tokenize_40(void);
static void cont__compiler__tokenize_41(void);
static void cont__compiler__tokenize_42(void);
static void cont__compiler__tokenize_43(void);
static void cont__compiler__tokenize_44(void);
static void cont__compiler__tokenize_45(void);
static NODE *func__compiler__tokenize_46;
static void entry__compiler__tokenize_46(void);
static FRAME_INFO frame__compiler__tokenize_46 = {3, {"text", "i", "indent"}};
static void cont__compiler__tokenize_47(void);
static void cont__compiler__tokenize_48(void);
static NODE *func__compiler__tokenize_49;
static void entry__compiler__tokenize_49(void);
static FRAME_INFO frame__compiler__tokenize_49 = {2, {"i", "indent"}};
static void cont__compiler__tokenize_50(void);
static void cont__compiler__tokenize_51(void);
static void cont__compiler__tokenize_52(void);
static NODE *func__compiler__tokenize_53;
static void entry__compiler__tokenize_53(void);
static FRAME_INFO frame__compiler__tokenize_53 = {3, {"text", "i", "indent"}};
static void cont__compiler__tokenize_54(void);
static void cont__compiler__tokenize_55(void);
static NODE *func__compiler__tokenize_56;
static void entry__compiler__tokenize_56(void);
static FRAME_INFO frame__compiler__tokenize_56 = {2, {"i", "indent"}};
static void cont__compiler__tokenize_57(void);
static void cont__compiler__tokenize_58(void);
static void cont__compiler__tokenize_59(void);
static void cont__compiler__tokenize_60(void);
static NODE *func__compiler__tokenize_61;
static void entry__compiler__tokenize_61(void);
static FRAME_INFO frame__compiler__tokenize_61 = {2, {"text", "i"}};
static void cont__compiler__tokenize_62(void);
static void cont__compiler__tokenize_63(void);
static void cont__compiler__tokenize_64(void);
static NODE *func__compiler__tokenize_65;
static void entry__compiler__tokenize_65(void);
static FRAME_INFO frame__compiler__tokenize_65 = {1, {"TokenizationError"}};
static NODE *string__97eea539018d4d4b;
static void cont__compiler__tokenize_67(void);
static NODE *func__compiler__tokenize_68;
static void entry__compiler__tokenize_68(void);
static FRAME_INFO frame__compiler__tokenize_68 = {13, {"current_indent", "return", "pending_newlines", "new_text", "fragment", "text", "i", "skip_line", "quote_count", "s", "get_indent", "convert", "TokenizationError"}};
static NODE *func__compiler__tokenize_69;
static void entry__compiler__tokenize_69(void);
static FRAME_INFO frame__compiler__tokenize_69 = {19, {"pending_newlines", "new_text", "fragment", "text", "i", "skip_line", "quote_count", "s", "get_indent", "current_indent", "convert", "TokenizationError", "return", "add_newline", "add_indent", "is_a_remark", "is_a_multi_line_string", "is_inline_C", "indent"}};
static NODE *func__compiler__tokenize_70;
static void entry__compiler__tokenize_70(void);
static FRAME_INFO frame__compiler__tokenize_70 = {4, {"pending_newlines", "new_text", "fragment", "indent"}};
static NODE *func__compiler__tokenize_71;
static void entry__compiler__tokenize_71(void);
static FRAME_INFO frame__compiler__tokenize_71 = {3, {"new_text", "fragment", "indent"}};
static void cont__compiler__tokenize_72(void);
static void cont__compiler__tokenize_73(void);
static void cont__compiler__tokenize_74(void);
static NODE *func__compiler__tokenize_75;
static void entry__compiler__tokenize_75(void);
static FRAME_INFO frame__compiler__tokenize_75 = {5, {"new_text", "fragment", "indent", "pending_newlines", "add_newline"}};
static void cont__compiler__tokenize_76(void);
static void cont__compiler__tokenize_77(void);
static void cont__compiler__tokenize_78(void);
static void cont__compiler__tokenize_79(void);
static void cont__compiler__tokenize_80(void);
static void cont__compiler__tokenize_81(void);
static void cont__compiler__tokenize_82(void);
static void cont__compiler__tokenize_83(void);
static void cont__compiler__tokenize_84(void);
static NODE *func__compiler__tokenize_85;
static void entry__compiler__tokenize_85(void);
static FRAME_INFO frame__compiler__tokenize_85 = {2, {"text", "i"}};
static void cont__compiler__tokenize_86(void);
static void cont__compiler__tokenize_87(void);
static void cont__compiler__tokenize_88(void);
static void cont__compiler__tokenize_89(void);
static void cont__compiler__tokenize_90(void);
static void cont__compiler__tokenize_91(void);
static void cont__compiler__tokenize_92(void);
static void cont__compiler__tokenize_93(void);
static void cont__compiler__tokenize_94(void);
static NODE *func__compiler__tokenize_95;
static void entry__compiler__tokenize_95(void);
static FRAME_INFO frame__compiler__tokenize_95 = {15, {"add_indent", "is_a_remark", "is_a_multi_line_string", "is_inline_C", "i", "indent", "skip_line", "get_indent", "current_indent", "new_text", "text", "s", "add_newline", "convert", "TokenizationError"}};
static void cont__compiler__tokenize_96(void);
static NODE *func__compiler__tokenize_97;
static void entry__compiler__tokenize_97(void);
static FRAME_INFO frame__compiler__tokenize_97 = {2, {"is_a_multi_line_string", "is_inline_C"}};
static NODE *func__compiler__tokenize_98;
static void entry__compiler__tokenize_98(void);
static FRAME_INFO frame__compiler__tokenize_98 = {1, {"is_inline_C"}};
static void cont__compiler__tokenize_99(void);
static void cont__compiler__tokenize_100(void);
static NODE *func__compiler__tokenize_101;
static void entry__compiler__tokenize_101(void);
static FRAME_INFO frame__compiler__tokenize_101 = {11, {"i", "indent", "skip_line", "get_indent", "current_indent", "new_text", "text", "s", "add_newline", "rs", "least_indent"}};
static NODE *func__compiler__tokenize_102;
static void entry__compiler__tokenize_102(void);
static FRAME_INFO frame__compiler__tokenize_102 = {5, {"break", "skip_line", "get_indent", "current_indent", "least_indent"}};
static NODE *func__compiler__tokenize_103;
static void entry__compiler__tokenize_103(void);
static FRAME_INFO frame__compiler__tokenize_103 = {6, {"skip_line", "get_indent", "current_indent", "break", "least_indent", "next_indent"}};
static void cont__compiler__tokenize_104(void);
static void cont__compiler__tokenize_105(void);
static void cont__compiler__tokenize_106(void);
static void cont__compiler__tokenize_107(void);
static void cont__compiler__tokenize_108(void);
static void cont__compiler__tokenize_109(void);
static void cont__compiler__tokenize_110(void);
static void cont__compiler__tokenize_111(void);
static NODE *func__compiler__tokenize_112;
static void entry__compiler__tokenize_112(void);
static FRAME_INFO frame__compiler__tokenize_112 = {11, {"break", "skip_line", "indent", "least_indent", "new_text", "text", "s", "i", "get_indent", "current_indent", "add_newline"}};
static NODE *func__compiler__tokenize_113;
static void entry__compiler__tokenize_113(void);
static FRAME_INFO frame__compiler__tokenize_113 = {11, {"skip_line", "indent", "least_indent", "new_text", "text", "s", "i", "get_indent", "current_indent", "break", "add_newline"}};
static void cont__compiler__tokenize_114(void);
static void cont__compiler__tokenize_115(void);
static NODE *func__compiler__tokenize_116;
static void entry__compiler__tokenize_116(void);
static FRAME_INFO frame__compiler__tokenize_116 = {1, {"new_text"}};
static void cont__compiler__tokenize_117(void);
static void cont__compiler__tokenize_118(void);
static void cont__compiler__tokenize_119(void);
static void cont__compiler__tokenize_120(void);
static void cont__compiler__tokenize_121(void);
static void cont__compiler__tokenize_122(void);
static void cont__compiler__tokenize_123(void);
static void cont__compiler__tokenize_124(void);
static void cont__compiler__tokenize_125(void);
static void cont__compiler__tokenize_126(void);
static void cont__compiler__tokenize_127(void);
static void cont__compiler__tokenize_128(void);
static NODE *func__compiler__tokenize_129;
static void entry__compiler__tokenize_129(void);
static FRAME_INFO frame__compiler__tokenize_129 = {5, {"indent", "convert", "current_indent", "TokenizationError", "new_text"}};
static void cont__compiler__tokenize_130(void);
static void cont__compiler__tokenize_131(void);
static NODE *func__compiler__tokenize_132;
static void entry__compiler__tokenize_132(void);
static FRAME_INFO frame__compiler__tokenize_132 = {1, {"TokenizationError"}};
static NODE *string__f6816391653ef18d;
static void cont__compiler__tokenize_134(void);
static void cont__compiler__tokenize_135(void);
static void cont__compiler__tokenize_136(void);
static void cont__compiler__tokenize_137(void);
static NODE *func__compiler__tokenize_138;
static void entry__compiler__tokenize_138(void);
static FRAME_INFO frame__compiler__tokenize_138 = {2, {"return", "indent"}};
static void cont__compiler__tokenize_139(void);
static void cont__compiler__tokenize_140(void);
static void cont__compiler__tokenize_141(void);
static void cont__compiler__tokenize_142(void);
static void cont__compiler__tokenize_143(void);
static void cont__compiler__tokenize_144(void);
static NODE *get__compiler__tokenize(void) {
  return var.compiler__tokenize;
}
void run__tokenizer(void);

static CONTINUATION_INFO continuation_info[] = {
  {run__tokenizer, NULL, },
  {entry__compiler__tokenize_2, NULL, 45, 45, 5, 34},
  {cont__compiler__tokenize_3, &frame__compiler__tokenize_2, 46, 46, 50, 52},
  {cont__compiler__tokenize_4, &frame__compiler__tokenize_2, 46, 46, 37, 53},
  {cont__compiler__tokenize_5, &frame__compiler__tokenize_2, 46, 46, 19, 62},
  {cont__compiler__tokenize_6, &frame__compiler__tokenize_2, 46, 46, 5, 62},
  {cont__compiler__tokenize_7, &frame__compiler__tokenize_2, 47, 47, 20, 25},
  {cont__compiler__tokenize_8, &frame__compiler__tokenize_2, 47, 47, 5, 25},
  {cont__compiler__tokenize_9, &frame__compiler__tokenize_2, 47, 47, 19, 25},
  {cont__compiler__tokenize_10, &frame__compiler__tokenize_2, 48, 51, 12, 24},
  {cont__compiler__tokenize_15, &frame__compiler__tokenize_2, 48, 51, 5, 24},
  {cont__compiler__tokenize_16, &frame__compiler__tokenize_2, 52, 52, 5, 10},
  {entry__compiler__tokenize_24, NULL, 59, 59, 11, 26},
  {cont__compiler__tokenize_25, &frame__compiler__tokenize_24, 59, 59, 26, 26},
  {entry__compiler__tokenize_26, NULL, 61, 61, 11, 70},
  {entry__compiler__tokenize_22, NULL, 57, 57, 12, 18},
  {cont__compiler__tokenize_23, &frame__compiler__tokenize_22, 57, 61, 7, 71},
  {cont__compiler__tokenize_28, &frame__compiler__tokenize_22, 62, 62, 7, 12},
  {cont__compiler__tokenize_29, &frame__compiler__tokenize_22, 62, 62, 12, 12},
  {entry__compiler__tokenize_18, NULL, 56, 56, 14, 20},
  {cont__compiler__tokenize_19, &frame__compiler__tokenize_18, 56, 56, 14, 31},
  {cont__compiler__tokenize_20, &frame__compiler__tokenize_18, 56, 56, 14, 31},
  {cont__compiler__tokenize_21, &frame__compiler__tokenize_18, 56, 62, 11, 12},
  {entry__compiler__tokenize_17, NULL, 56, 62, 5, 12},
  {entry__compiler__tokenize_35, NULL, 68, 68, 42, 42},
  {cont__compiler__tokenize_36, &frame__compiler__tokenize_35, 68, 68, 34, 42},
  {entry__compiler__tokenize_32, NULL, 68, 68, 17, 31},
  {cont__compiler__tokenize_33, &frame__compiler__tokenize_32, 68, 68, 12, 31},
  {cont__compiler__tokenize_34, &frame__compiler__tokenize_32, 68, 68, 9, 42},
  {cont__compiler__tokenize_37, &frame__compiler__tokenize_32, 69, 69, 12, 18},
  {cont__compiler__tokenize_38, &frame__compiler__tokenize_32, 69, 69, 12, 29},
  {cont__compiler__tokenize_39, &frame__compiler__tokenize_32, 69, 69, 12, 29},
  {cont__compiler__tokenize_40, &frame__compiler__tokenize_32, 69, 69, 9, 35},
  {cont__compiler__tokenize_41, &frame__compiler__tokenize_32, 70, 70, 9, 14},
  {cont__compiler__tokenize_42, &frame__compiler__tokenize_32, 71, 71, 9, 29},
  {cont__compiler__tokenize_43, &frame__compiler__tokenize_32, 71, 71, 29, 29},
  {entry__compiler__tokenize_31, NULL, 67, 71, 7, 29},
  {cont__compiler__tokenize_44, &frame__compiler__tokenize_31, 71, 71, 29, 29},
  {entry__compiler__tokenize_49, NULL, 74, 74, 7, 12},
  {cont__compiler__tokenize_50, &frame__compiler__tokenize_49, 75, 75, 7, 20},
  {cont__compiler__tokenize_51, &frame__compiler__tokenize_49, 75, 75, 20, 20},
  {entry__compiler__tokenize_46, NULL, 73, 73, 14, 20},
  {cont__compiler__tokenize_47, &frame__compiler__tokenize_46, 73, 73, 14, 30},
  {cont__compiler__tokenize_48, &frame__compiler__tokenize_46, 73, 75, 11, 20},
  {entry__compiler__tokenize_56, NULL, 77, 77, 7, 12},
  {cont__compiler__tokenize_57, &frame__compiler__tokenize_56, 78, 78, 7, 17},
  {cont__compiler__tokenize_58, &frame__compiler__tokenize_56, 78, 78, 17, 17},
  {entry__compiler__tokenize_53, NULL, 76, 76, 14, 20},
  {cont__compiler__tokenize_54, &frame__compiler__tokenize_53, 76, 76, 14, 27},
  {cont__compiler__tokenize_55, &frame__compiler__tokenize_53, 76, 78, 11, 17},
  {entry__compiler__tokenize_61, NULL, 79, 79, 22, 28},
  {cont__compiler__tokenize_62, &frame__compiler__tokenize_61, 79, 79, 22, 39},
  {cont__compiler__tokenize_63, &frame__compiler__tokenize_61, 79, 79, 22, 39},
  {entry__compiler__tokenize_65, NULL, 80, 80, 7, 56},
  {entry__compiler__tokenize_30, NULL, 66, 71, 5, 30},
  {cont__compiler__tokenize_45, &frame__compiler__tokenize_30, 73, 75, 5, 20},
  {cont__compiler__tokenize_52, &frame__compiler__tokenize_30, 76, 78, 5, 17},
  {cont__compiler__tokenize_59, &frame__compiler__tokenize_30, 79, 79, 8, 17},
  {cont__compiler__tokenize_60, &frame__compiler__tokenize_30, 79, 79, 8, 39},
  {cont__compiler__tokenize_64, &frame__compiler__tokenize_30, 79, 80, 5, 56},
  {cont__compiler__tokenize_67, &frame__compiler__tokenize_30, 81, 81, 5, 13},
  {entry__compiler__tokenize_71, NULL, 91, 91, 11, 32},
  {cont__compiler__tokenize_72, &frame__compiler__tokenize_71, 92, 92, 17, 35},
  {cont__compiler__tokenize_73, &frame__compiler__tokenize_71, 92, 92, 11, 42},
  {cont__compiler__tokenize_74, &frame__compiler__tokenize_71, 92, 92, 42, 42},
  {entry__compiler__tokenize_70, NULL, 90, 92, 9, 42},
  {entry__compiler__tokenize_75, NULL, 95, 95, 9, 36},
  {cont__compiler__tokenize_76, &frame__compiler__tokenize_75, 96, 96, 15, 33},
  {cont__compiler__tokenize_77, &frame__compiler__tokenize_75, 96, 96, 9, 40},
  {cont__compiler__tokenize_78, &frame__compiler__tokenize_75, 97, 97, 9, 29},
  {cont__compiler__tokenize_79, &frame__compiler__tokenize_75, 98, 98, 9, 19},
  {entry__compiler__tokenize_85, NULL, 103, 103, 34, 36},
  {cont__compiler__tokenize_86, &frame__compiler__tokenize_85, 103, 103, 29, 37},
  {cont__compiler__tokenize_87, &frame__compiler__tokenize_85, 103, 103, 29, 44},
  {cont__compiler__tokenize_88, &frame__compiler__tokenize_85, 103, 103, 29, 44},
  {entry__compiler__tokenize_98, NULL, 110, 110, 52, 62},
  {entry__compiler__tokenize_97, NULL, 110, 110, 26, 62},
  {cont__compiler__tokenize_99, &frame__compiler__tokenize_97, 110, 110, 26, 62},
  {entry__compiler__tokenize_103, NULL, 117, 117, 17, 25},
  {cont__compiler__tokenize_104, &frame__compiler__tokenize_103, 118, 118, 17, 39},
  {cont__compiler__tokenize_105, &frame__compiler__tokenize_103, 119, 119, 20, 48},
  {cont__compiler__tokenize_106, &frame__compiler__tokenize_103, 119, 119, 20, 48},
  {cont__compiler__tokenize_107, &frame__compiler__tokenize_103, 119, 119, 17, 54},
  {cont__compiler__tokenize_108, &frame__compiler__tokenize_103, 120, 120, 17, 51},
  {cont__compiler__tokenize_109, &frame__compiler__tokenize_103, 120, 120, 51, 51},
  {entry__compiler__tokenize_102, NULL, 116, 120, 15, 51},
  {cont__compiler__tokenize_110, &frame__compiler__tokenize_102, 120, 120, 51, 51},
  {entry__compiler__tokenize_116, NULL, 125, 125, 45, 62},
  {cont__compiler__tokenize_117, &frame__compiler__tokenize_116, 125, 125, 62, 62},
  {entry__compiler__tokenize_113, NULL, 124, 124, 17, 25},
  {cont__compiler__tokenize_114, &frame__compiler__tokenize_113, 125, 125, 24, 42},
  {cont__compiler__tokenize_115, &frame__compiler__tokenize_113, 125, 125, 17, 62},
  {cont__compiler__tokenize_118, &frame__compiler__tokenize_113, 126, 126, 47, 49},
  {cont__compiler__tokenize_119, &frame__compiler__tokenize_113, 126, 126, 34, 50},
  {cont__compiler__tokenize_120, &frame__compiler__tokenize_113, 126, 126, 17, 50},
  {cont__compiler__tokenize_121, &frame__compiler__tokenize_113, 127, 127, 17, 34},
  {cont__compiler__tokenize_122, &frame__compiler__tokenize_113, 129, 129, 20, 43},
  {cont__compiler__tokenize_123, &frame__compiler__tokenize_113, 129, 129, 20, 43},
  {cont__compiler__tokenize_124, &frame__compiler__tokenize_113, 129, 129, 17, 49},
  {cont__compiler__tokenize_125, &frame__compiler__tokenize_113, 130, 130, 17, 27},
  {entry__compiler__tokenize_112, NULL, 123, 130, 15, 27},
  {cont__compiler__tokenize_126, &frame__compiler__tokenize_112, 130, 130, 27, 27},
  {entry__compiler__tokenize_101, NULL, 115, 120, 13, 52},
  {cont__compiler__tokenize_111, &frame__compiler__tokenize_101, 122, 130, 13, 28},
  {cont__compiler__tokenize_127, &frame__compiler__tokenize_101, 131, 131, 13, 41},
  {cont__compiler__tokenize_128, &frame__compiler__tokenize_101, 131, 131, 41, 41},
  {entry__compiler__tokenize_132, NULL, 134, 134, 41, 79},
  {entry__compiler__tokenize_129, NULL, 133, 133, 13, 35},
  {cont__compiler__tokenize_130, &frame__compiler__tokenize_129, 134, 134, 16, 38},
  {cont__compiler__tokenize_131, &frame__compiler__tokenize_129, 134, 134, 13, 79},
  {cont__compiler__tokenize_134, &frame__compiler__tokenize_129, 135, 135, 13, 41},
  {cont__compiler__tokenize_135, &frame__compiler__tokenize_129, 135, 135, 41, 41},
  {entry__compiler__tokenize_95, NULL, 108, 108, 9, 18},
  {cont__compiler__tokenize_96, &frame__compiler__tokenize_95, 110, 110, 11, 62},
  {cont__compiler__tokenize_100, &frame__compiler__tokenize_95, 109, 135, 9, 42},
  {entry__compiler__tokenize_138, NULL, 136, 136, 35, 47},
  {entry__compiler__tokenize_69, NULL, 100, 100, 20, 26},
  {cont__compiler__tokenize_80, &frame__compiler__tokenize_69, 100, 100, 7, 33},
  {cont__compiler__tokenize_81, &frame__compiler__tokenize_69, 101, 101, 7, 15},
  {cont__compiler__tokenize_82, &frame__compiler__tokenize_69, 102, 102, 7, 48},
  {cont__compiler__tokenize_83, &frame__compiler__tokenize_69, 103, 103, 20, 24},
  {cont__compiler__tokenize_84, &frame__compiler__tokenize_69, 103, 103, 7, 44},
  {cont__compiler__tokenize_89, &frame__compiler__tokenize_69, 104, 104, 37, 39},
  {cont__compiler__tokenize_90, &frame__compiler__tokenize_69, 104, 104, 24, 40},
  {cont__compiler__tokenize_91, &frame__compiler__tokenize_69, 104, 104, 7, 40},
  {cont__compiler__tokenize_92, &frame__compiler__tokenize_69, 105, 105, 7, 25},
  {cont__compiler__tokenize_93, &frame__compiler__tokenize_69, 107, 107, 10, 32},
  {cont__compiler__tokenize_94, &frame__compiler__tokenize_69, 107, 135, 7, 43},
  {cont__compiler__tokenize_136, &frame__compiler__tokenize_69, 136, 136, 10, 32},
  {cont__compiler__tokenize_137, &frame__compiler__tokenize_69, 136, 136, 7, 47},
  {cont__compiler__tokenize_139, &frame__compiler__tokenize_69, 137, 137, 7, 17},
  {entry__compiler__tokenize_68, NULL, 88, 137, 5, 17},
  {cont__compiler__tokenize_140, &frame__compiler__tokenize_68, 137, 137, 17, 17},
  {entry__compiler__tokenize, NULL, 37, 37, 3, 25},
  {cont__compiler__tokenize_141, &frame__compiler__tokenize, 139, 139, 10, 19},
  {cont__compiler__tokenize_142, &frame__compiler__tokenize, 139, 139, 3, 19},
  {cont__compiler__tokenize_143, &frame__compiler__tokenize, 140, 140, 3, 24},
  {cont__compiler__tokenize_144, &frame__compiler__tokenize, 141, 141, 30, 30}
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
static NODE *character__35;
static NODE *character__10;
static NODE *number__0;
static NODE *number__8;
static NODE *character__2;
static NODE *character__34;
static NODE *character__123;
static NODE *character__32;
static NODE *character__1;
static NODE *number__1;

static const char *used_namespaces[] = {
  "std",
  "compiler",
  NULL
};

static MODULE_INFO module_info = {
  NULL,
  "tokenizer",
  continuation_info,
  sizeof(continuation_info)/sizeof(CONTINUATION_INFO),
  (NODE **)&var,
  var_names,
  sizeof(var_names)/sizeof(const char *),
  used_namespaces,
  {DEBUG_FILENAME("tokenizer.sim")}
};

/******
C O D E
******/

static int already_run = false;

EXPORT void run__tokenizer(void) {
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
static void entry__compiler__tokenize(void) {
  allocate_initialized_frame_gc(1, 12);
  // slot allocations:
  // fragment: 0
  // text: 1
  // i: 2
  // s: 3
  // new_text: 4
  // pending_newlines: 5
  // quote_count: 6
  // TokenizationError: 7
  // skip_line: 8
  // get_indent: 9
  // convert: 10
  frame->slots[7] /* TokenizationError */ = create_future();
  frame->slots[8] /* skip_line */ = create_future();
  frame->slots[9] /* get_indent */ = create_future();
  frame->slots[10] /* convert */ = create_future();
  frame->slots[1] /* text */ = create_future();
  frame->slots[2] /* i */ = create_cell();
  frame->slots[3] /* s */ = create_cell();
  frame->slots[4] /* new_text */ = create_cell();
  frame->slots[5] /* pending_newlines */ = create_cell();
  frame->slots[6] /* quote_count */ = create_cell();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* fragment */ = create_cell_with_contents(arguments->slots[0]);
  // 44: ... : ($msg)
  // 45:   $$line_no line_no_of(fragment)
  // 46:   plus &line_no count_occurrences(range(text 1 i-1) newline)
  // 47:   to_upper_case &msg(1)
  // 48:   ewrite "
  // 49:     ____________________________________
  // 50:     TOKENIZATION ERROR IN LINE @(line_no) OF FILE "@(module_name)@
  // 51:     @quot;:@nl;@(msg)!
  // 52:   exit 1
  frame->slots[11] /* temp__1 */ = create_closure(entry__compiler__tokenize_2, 1);
  // 44: $TokenizationError: ($msg)
  // 45:   $$line_no line_no_of(fragment)
  // 46:   plus &line_no count_occurrences(range(text 1 i-1) newline)
  // 47:   to_upper_case &msg(1)
  // 48:   ewrite "
  // 49:     ____________________________________
  // 50:     TOKENIZATION ERROR IN LINE @(line_no) OF FILE "@(module_name)@
  // 51:     @quot;:@nl;@(msg)!
  // 52:   exit 1
  initialize_future(frame->slots[7] /* TokenizationError */, frame->slots[11] /* temp__1 */);
  // 54: ... :
  // 55:   !quote_count 0
  // 56:   while -> text(i) != newline:
  // 57:     case text(i)
  // 58:       '@quot;':
  // 59:         inc &quote_count
  // 60:       '@ht;':
  // 61:         TokenizationError "tabulator character within line detected"
  // 62:     inc &i
  frame->slots[11] /* temp__1 */ = create_closure(entry__compiler__tokenize_17, 0);
  // 54: $skip_line:
  // 55:   !quote_count 0
  // 56:   while -> text(i) != newline:
  // 57:     case text(i)
  // 58:       '@quot;':
  // 59:         inc &quote_count
  // 60:       '@ht;':
  // 61:         TokenizationError "tabulator character within line detected"
  // 62:     inc &i
  initialize_future(frame->slots[8] /* skip_line */, frame->slots[11] /* temp__1 */);
  // 64: ... : (-> return)
  // 65:   !pending_newlines 0
  // 66:   do: (-> break)
  // 67:     forever:
  // 68:       if i == length_of(text): return -1
  // 69:       if text(i) != newline break
  // 70:       inc &i
  // 71:       inc &pending_newlines
  // 72:   $$indent 0
  // 73:   while -> text(i) == '@ht;':
  // ...
  frame->slots[11] /* temp__1 */ = create_closure(entry__compiler__tokenize_30, 0);
  // 64: $get_indent: (-> return)
  // 65:   !pending_newlines 0
  // 66:   do: (-> break)
  // 67:     forever:
  // 68:       if i == length_of(text): return -1
  // 69:       if text(i) != newline break
  // 70:       inc &i
  // 71:       inc &pending_newlines
  // 72:   $$indent 0
  // 73:   while -> text(i) == '@ht;':
  // ...
  initialize_future(frame->slots[9] /* get_indent */, frame->slots[11] /* temp__1 */);
  // 83: ... :
  // 84:   (
  // 85:     current_indent
  // 86:     -> return
  // 87:   )
  // 88:   forever:
  // 89:     $add_newline:
  // 90:       repeat pending_newlines:
  // 91:         push &new_text newline
  // 92:         push &fragment.indents_of indent
  // ...
  frame->slots[11] /* temp__1 */ = create_closure(entry__compiler__tokenize_68, 1);
  // 83: $convert:
  // 84:   (
  // 85:     current_indent
  // 86:     -> return
  // 87:   )
  // 88:   forever:
  // 89:     $add_newline:
  // 90:       repeat pending_newlines:
  // 91:         push &new_text newline
  // 92:         push &fragment.indents_of indent
  // ...
  initialize_future(frame->slots[10] /* convert */, frame->slots[11] /* temp__1 */);
  // 36: !fragment.indents_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* fragment */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__indents_of, get__empty_list());
    ((CELL *)frame->slots[0])->contents /* fragment */ = temp;

  }
  // 37: $text text_of(fragment)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* fragment */;
  result_count = 1;
  myself = get__text_of();
  func = myself->type;
  frame->cont = cont__compiler__tokenize_141;
}
static void entry__compiler__tokenize_22(void) {
  allocate_initialized_frame_gc(4, 7);
  // slot allocations:
  // text: 0
  // i: 1
  // quote_count: 2
  // TokenizationError: 3
  frame->slots[0] = myself->closure.frame->slots[0]; /* text */
  frame->slots[1] = myself->closure.frame->slots[1]; /* i */
  frame->slots[2] = myself->closure.frame->slots[2]; /* quote_count */
  frame->slots[3] = myself->closure.frame->slots[3]; /* TokenizationError */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 57: ... text(i)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* i */;
  result_count = 1;
  myself = frame->slots[0] /* text */;
  func = myself->type;
  frame->cont = cont__compiler__tokenize_23;
}
static void cont__compiler__tokenize_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 58: ... :
  // 59:   inc &quote_count
  frame->slots[5] /* temp__2 */ = create_closure(entry__compiler__tokenize_24, 0);
  // 60: ... :
  // 61:   TokenizationError "tabulator character within line detected"
  frame->slots[6] /* temp__3 */ = create_closure(entry__compiler__tokenize_26, 0);
  // 57: case text(i)
  // 58:   '@quot;':
  // 59:     inc &quote_count
  // 60:   '@ht;':
  // 61:     TokenizationError "tabulator character within line detected"
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = character__34;
  arguments->slots[2] = frame->slots[5] /* temp__2 */;
  arguments->slots[3] = character__9;
  arguments->slots[4] = frame->slots[6] /* temp__3 */;
  result_count = 0;
  myself = get__case();
  func = myself->type;
  frame->cont = cont__compiler__tokenize_28;
}
static void entry__compiler__tokenize_24(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // quote_count: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* quote_count */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 59: inc &quote_count
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* quote_count */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__compiler__tokenize_25;
}
static void cont__compiler__tokenize_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* quote_count */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__tokenize_26(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // TokenizationError: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* TokenizationError */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 61: TokenizationError "tabulator character within line detected"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__dd17af2f619a6908;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* TokenizationError */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__tokenize_28(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 62: inc &i
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* i */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__compiler__tokenize_29;
}
static void cont__compiler__tokenize_29(void) {
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
static void entry__compiler__tokenize_18(void) {
  allocate_initialized_frame_gc(4, 8);
  // slot allocations:
  // text: 0
  // i: 1
  // quote_count: 2
  // TokenizationError: 3
  frame->slots[0] = myself->closure.frame->slots[1]; /* text */
  frame->slots[1] = myself->closure.frame->slots[2]; /* i */
  frame->slots[2] = myself->closure.frame->slots[0]; /* quote_count */
  frame->slots[3] = myself->closure.frame->slots[3]; /* TokenizationError */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 56: ... text(i)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* i */;
  result_count = 1;
  myself = frame->slots[0] /* text */;
  func = myself->type;
  frame->cont = cont__compiler__tokenize_19;
}
static void cont__compiler__tokenize_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 56: ... text(i) != newline
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__3 */;
  arguments->slots[1] = get__newline();
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__compiler__tokenize_20;
}
static void cont__compiler__tokenize_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 56: ... text(i) != newline
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__compiler__tokenize_21;
}
static void cont__compiler__tokenize_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 56: ... :
  // 57:   case text(i)
  // 58:     '@quot;':
  // 59:       inc &quote_count
  // 60:     '@ht;':
  // 61:       TokenizationError "tabulator character within line detected"
  // 62:   inc &i
  frame->slots[7] /* temp__4 */ = create_closure(entry__compiler__tokenize_22, 0);
  // 56: ... -> text(i) != newline:
  // 57:   case text(i)
  // 58:     '@quot;':
  // 59:       inc &quote_count
  // 60:     '@ht;':
  // 61:       TokenizationError "tabulator character within line detected"
  // 62:   inc &i
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__4 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__tokenize_2(void) {
  allocate_initialized_frame_gc(4, 8);
  // slot allocations:
  // msg: 0
  // fragment: 1
  // text: 2
  // i: 3
  // line_no: 4
  frame->slots[1] = myself->closure.frame->slots[0]; /* fragment */
  frame->slots[2] = myself->closure.frame->slots[1]; /* text */
  frame->slots[3] = myself->closure.frame->slots[2]; /* i */
  frame->slots[4] /* line_no */ = create_cell();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* msg */ = create_cell_with_contents(arguments->slots[0]);
  // 45: $$line_no line_no_of(fragment)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* fragment */;
  result_count = 1;
  myself = get__line_no_of();
  func = myself->type;
  frame->cont = cont__compiler__tokenize_3;
}
static void cont__compiler__tokenize_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[4])->contents /* line_no */ = arguments->slots[0];
  // 46: ... i-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* i */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__compiler__tokenize_4;
}
static void cont__compiler__tokenize_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__3 */ = arguments->slots[0];
  // 46: ... range(text 1 i-1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* text */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__compiler__tokenize_5;
}
static void cont__compiler__tokenize_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 46: ... count_occurrences(range(text 1 i-1) newline)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = get__newline();
  result_count = 1;
  myself = get__count_occurrences();
  func = myself->type;
  frame->cont = cont__compiler__tokenize_6;
}
static void cont__compiler__tokenize_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 46: plus &line_no count_occurrences(range(text 1 i-1) newline)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* line_no */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 1;
  myself = get__plus();
  func = myself->type;
  frame->cont = cont__compiler__tokenize_7;
}
static void cont__compiler__tokenize_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[4])->contents /* line_no */ = arguments->slots[0];
  // 47: ... msg(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* msg */;
  func = myself->type;
  frame->cont = cont__compiler__tokenize_8;
}
static void cont__compiler__tokenize_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 47: to_upper_case &msg(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  result_count = 1;
  myself = get__to_upper_case();
  func = myself->type;
  frame->cont = cont__compiler__tokenize_9;
}
static void cont__compiler__tokenize_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 47: ... &msg(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__1;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* msg */;
  func = myself->type;
  frame->cont = cont__compiler__tokenize_10;
}
static void cont__compiler__tokenize_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* msg */ = arguments->slots[0];
  // 48: ... "
  // 49:   ____________________________________
  // 50:   TOKENIZATION ERROR IN LINE @(line_no) OF FILE "@(module_name)@
  // 51:   @quot;:@nl;@(msg)!
  argument_count = 7;
  arguments = node_p;
  arguments->slots[0] = string__a18ab04649b43ca6;
  arguments->slots[1] = ((CELL *)frame->slots[4])->contents /* line_no */;
  arguments->slots[2] = string__6c6619488b29e163;
  arguments->slots[3] = get__module_name();
  arguments->slots[4] = string__fa730c15ff96bc6;
  arguments->slots[5] = ((CELL *)frame->slots[0])->contents /* msg */;
  arguments->slots[6] = string__2d7981f4e6002bcf;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__tokenize_15;
}
static void cont__compiler__tokenize_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 48: ewrite "
  // 49:   ____________________________________
  // 50:   TOKENIZATION ERROR IN LINE @(line_no) OF FILE "@(module_name)@
  // 51:   @quot;:@nl;@(msg)!
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  result_count = 0;
  myself = get__ewrite();
  func = myself->type;
  frame->cont = cont__compiler__tokenize_16;
}
static void cont__compiler__tokenize_16(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 52: exit 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = frame->caller_result_count;
  myself = get__exit();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__tokenize_17(void) {
  allocate_initialized_frame_gc(4, 5);
  // slot allocations:
  // quote_count: 0
  // text: 1
  // i: 2
  // TokenizationError: 3
  frame->slots[0] = myself->closure.frame->slots[6]; /* quote_count */
  frame->slots[1] = myself->closure.frame->slots[1]; /* text */
  frame->slots[2] = myself->closure.frame->slots[2]; /* i */
  frame->slots[3] = myself->closure.frame->slots[7]; /* TokenizationError */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 55: !quote_count 0
  ((CELL *)frame->slots[0])->contents /* quote_count */ = number__0;
  // 56: ... -> text(i) != newline:
  // 57:   case text(i)
  // 58:     '@quot;':
  // 59:       inc &quote_count
  // 60:     '@ht;':
  // 61:       TokenizationError "tabulator character within line detected"
  // 62:   inc &i
  frame->slots[4] /* temp__1 */ = create_closure(entry__compiler__tokenize_18, 0);
  // 56: while -> text(i) != newline:
  // 57:   case text(i)
  // 58:     '@quot;':
  // 59:       inc &quote_count
  // 60:     '@ht;':
  // 61:       TokenizationError "tabulator character within line detected"
  // 62:   inc &i
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__while();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__tokenize_30(void) {
  allocate_initialized_frame_gc(5, 10);
  // slot allocations:
  // return: 0
  // pending_newlines: 1
  // i: 2
  // text: 3
  // TokenizationError: 4
  // indent: 5
  frame->slots[0] /* return */ = create_continuation();
  frame->slots[1] = myself->closure.frame->slots[5]; /* pending_newlines */
  frame->slots[2] = myself->closure.frame->slots[2]; /* i */
  frame->slots[3] = myself->closure.frame->slots[1]; /* text */
  frame->slots[4] = myself->closure.frame->slots[7]; /* TokenizationError */
  frame->slots[5] /* indent */ = create_cell();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 65: !pending_newlines 0
  ((CELL *)frame->slots[1])->contents /* pending_newlines */ = number__0;
  // 66: ... : (-> break)
  // 67:   forever:
  // 68:     if i == length_of(text): return -1
  // 69:     if text(i) != newline break
  // 70:     inc &i
  // 71:     inc &pending_newlines
  frame->slots[6] /* temp__1 */ = create_closure(entry__compiler__tokenize_31, 0);
  // 66: do: (-> break)
  // 67:   forever:
  // 68:     if i == length_of(text): return -1
  // 69:     if text(i) != newline break
  // 70:     inc &i
  // 71:     inc &pending_newlines
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  result_count = 0;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__compiler__tokenize_45;
}
static void entry__compiler__tokenize_31(void) {
  allocate_initialized_frame_gc(5, 6);
  // slot allocations:
  // break: 0
  // i: 1
  // text: 2
  // return: 3
  // pending_newlines: 4
  frame->slots[0] /* break */ = create_continuation();
  frame->slots[1] = myself->closure.frame->slots[2]; /* i */
  frame->slots[2] = myself->closure.frame->slots[3]; /* text */
  frame->slots[3] = myself->closure.frame->slots[0]; /* return */
  frame->slots[4] = myself->closure.frame->slots[1]; /* pending_newlines */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 67: ... :
  // 68:   if i == length_of(text): return -1
  // 69:   if text(i) != newline break
  // 70:   inc &i
  // 71:   inc &pending_newlines
  frame->slots[5] /* temp__1 */ = create_closure(entry__compiler__tokenize_32, 0);
  // 67: forever:
  // 68:   if i == length_of(text): return -1
  // 69:   if text(i) != newline break
  // 70:   inc &i
  // 71:   inc &pending_newlines
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__forever();
  func = myself->type;
  frame->cont = cont__compiler__tokenize_44;
}
static void entry__compiler__tokenize_32(void) {
  allocate_initialized_frame_gc(5, 8);
  // slot allocations:
  // i: 0
  // text: 1
  // return: 2
  // break: 3
  // pending_newlines: 4
  frame->slots[0] = myself->closure.frame->slots[1]; /* i */
  frame->slots[1] = myself->closure.frame->slots[2]; /* text */
  frame->slots[2] = myself->closure.frame->slots[3]; /* return */
  frame->slots[3] = myself->closure.frame->slots[0]; /* break */
  frame->slots[4] = myself->closure.frame->slots[4]; /* pending_newlines */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 68: ... length_of(text)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* text */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__compiler__tokenize_33;
}
static void cont__compiler__tokenize_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 68: ... i == length_of(text)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* i */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__compiler__tokenize_34;
}
static void cont__compiler__tokenize_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 68: ... : return -1
  frame->slots[7] /* temp__3 */ = create_closure(entry__compiler__tokenize_35, 0);
  // 68: if i == length_of(text): return -1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__tokenize_37;
}
static void entry__compiler__tokenize_35(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 68: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__compiler__tokenize_36;
}
static void cont__compiler__tokenize_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 68: ... return -1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__tokenize_37(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 69: ... text(i)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* i */;
  result_count = 1;
  myself = frame->slots[1] /* text */;
  func = myself->type;
  frame->cont = cont__compiler__tokenize_38;
}
static void cont__compiler__tokenize_38(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__3 */ = arguments->slots[0];
  // 69: ... text(i) != newline
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__3 */;
  arguments->slots[1] = get__newline();
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__compiler__tokenize_39;
}
static void cont__compiler__tokenize_39(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 69: ... text(i) != newline
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__compiler__tokenize_40;
}
static void cont__compiler__tokenize_40(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 69: if text(i) != newline break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* break */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__tokenize_41;
}
static void cont__compiler__tokenize_41(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 70: inc &i
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* i */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__compiler__tokenize_42;
}
static void cont__compiler__tokenize_42(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* i */ = arguments->slots[0];
  // 71: inc &pending_newlines
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* pending_newlines */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__compiler__tokenize_43;
}
static void cont__compiler__tokenize_43(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[4])->contents /* pending_newlines */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__tokenize_44(void) {
  myself = frame->slots[0] /* break */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__compiler__tokenize_45(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 72: $$indent 0
  ((CELL *)frame->slots[5])->contents /* indent */ = number__0;
  // 73: ... -> text(i) == '@ht;':
  // 74:   inc &i
  // 75:   plus &indent 8
  frame->slots[6] /* temp__1 */ = create_closure(entry__compiler__tokenize_46, 0);
  // 73: while -> text(i) == '@ht;':
  // 74:   inc &i
  // 75:   plus &indent 8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  result_count = 0;
  myself = get__while();
  func = myself->type;
  frame->cont = cont__compiler__tokenize_52;
}
static void entry__compiler__tokenize_49(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // i: 0
  // indent: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* i */
  frame->slots[1] = myself->closure.frame->slots[2]; /* indent */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 74: inc &i
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* i */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__compiler__tokenize_50;
}
static void cont__compiler__tokenize_50(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* i */ = arguments->slots[0];
  // 75: plus &indent 8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* indent */;
  arguments->slots[1] = number__8;
  result_count = 1;
  myself = get__plus();
  func = myself->type;
  frame->cont = cont__compiler__tokenize_51;
}
static void cont__compiler__tokenize_51(void) {
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
static void entry__compiler__tokenize_46(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // text: 0
  // i: 1
  // indent: 2
  frame->slots[0] = myself->closure.frame->slots[3]; /* text */
  frame->slots[1] = myself->closure.frame->slots[2]; /* i */
  frame->slots[2] = myself->closure.frame->slots[5]; /* indent */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 73: ... text(i)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* i */;
  result_count = 1;
  myself = frame->slots[0] /* text */;
  func = myself->type;
  frame->cont = cont__compiler__tokenize_47;
}
static void cont__compiler__tokenize_47(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 73: ... text(i) == '@ht;'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = character__9;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__compiler__tokenize_48;
}
static void cont__compiler__tokenize_48(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 73: ... :
  // 74:   inc &i
  // 75:   plus &indent 8
  frame->slots[5] /* temp__3 */ = create_closure(entry__compiler__tokenize_49, 0);
  // 73: ... -> text(i) == '@ht;':
  // 74:   inc &i
  // 75:   plus &indent 8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__tokenize_52(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 76: ... -> text(i) == ' ':
  // 77:   inc &i
  // 78:   inc &indent
  frame->slots[6] /* temp__1 */ = create_closure(entry__compiler__tokenize_53, 0);
  // 76: while -> text(i) == ' ':
  // 77:   inc &i
  // 78:   inc &indent
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  result_count = 0;
  myself = get__while();
  func = myself->type;
  frame->cont = cont__compiler__tokenize_59;
}
static void entry__compiler__tokenize_56(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // i: 0
  // indent: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* i */
  frame->slots[1] = myself->closure.frame->slots[2]; /* indent */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 77: inc &i
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* i */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__compiler__tokenize_57;
}
static void cont__compiler__tokenize_57(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* i */ = arguments->slots[0];
  // 78: inc &indent
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* indent */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__compiler__tokenize_58;
}
static void cont__compiler__tokenize_58(void) {
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
static void entry__compiler__tokenize_53(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // text: 0
  // i: 1
  // indent: 2
  frame->slots[0] = myself->closure.frame->slots[3]; /* text */
  frame->slots[1] = myself->closure.frame->slots[2]; /* i */
  frame->slots[2] = myself->closure.frame->slots[5]; /* indent */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 76: ... text(i)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* i */;
  result_count = 1;
  myself = frame->slots[0] /* text */;
  func = myself->type;
  frame->cont = cont__compiler__tokenize_54;
}
static void cont__compiler__tokenize_54(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 76: ... text(i) == ' '
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = character__32;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__compiler__tokenize_55;
}
static void cont__compiler__tokenize_55(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 76: ... :
  // 77:   inc &i
  // 78:   inc &indent
  frame->slots[5] /* temp__3 */ = create_closure(entry__compiler__tokenize_56, 0);
  // 76: ... -> text(i) == ' ':
  // 77:   inc &i
  // 78:   inc &indent
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__tokenize_59(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 79: ... indent > 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = ((CELL *)frame->slots[5])->contents /* indent */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__compiler__tokenize_60;
}
static void cont__compiler__tokenize_60(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 79: ... text(i) == newline
  frame->slots[8] /* temp__3 */ = create_closure(entry__compiler__tokenize_61, 0);
  // 79: ... indent > 0 && text(i) == newline
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__2 */;
  arguments->slots[1] = frame->slots[8] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__compiler__tokenize_64;
}
static void entry__compiler__tokenize_61(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // text: 0
  // i: 1
  frame->slots[0] = myself->closure.frame->slots[3]; /* text */
  frame->slots[1] = myself->closure.frame->slots[2]; /* i */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 79: ... text(i)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* i */;
  result_count = 1;
  myself = frame->slots[0] /* text */;
  func = myself->type;
  frame->cont = cont__compiler__tokenize_62;
}
static void cont__compiler__tokenize_62(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 79: ... text(i) == newline
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = get__newline();
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__compiler__tokenize_63;
}
static void cont__compiler__tokenize_63(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 79: ... text(i) == newline
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__tokenize_64(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 79: ... :
  // 80:   TokenizationError "empty line contains whitespace"
  frame->slots[9] /* temp__4 */ = create_closure(entry__compiler__tokenize_65, 0);
  // 79: if indent > 0 && text(i) == newline:
  // 80:   TokenizationError "empty line contains whitespace"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[9] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__tokenize_67;
}
static void entry__compiler__tokenize_65(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // TokenizationError: 0
  frame->slots[0] = myself->closure.frame->slots[4]; /* TokenizationError */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 80: TokenizationError "empty line contains whitespace"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__97eea539018d4d4b;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* TokenizationError */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__tokenize_67(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 81: -> indent
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[5])->contents /* indent */;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__compiler__tokenize_68(void) {
  allocate_initialized_frame_gc(13, 14);
  // slot allocations:
  // current_indent: 0
  // return: 1
  // pending_newlines: 2
  // new_text: 3
  // fragment: 4
  // text: 5
  // i: 6
  // skip_line: 7
  // quote_count: 8
  // s: 9
  // get_indent: 10
  // convert: 11
  // TokenizationError: 12
  frame->slots[1] /* return */ = create_continuation();
  frame->slots[2] = myself->closure.frame->slots[5]; /* pending_newlines */
  frame->slots[3] = myself->closure.frame->slots[4]; /* new_text */
  frame->slots[4] = myself->closure.frame->slots[0]; /* fragment */
  frame->slots[5] = myself->closure.frame->slots[1]; /* text */
  frame->slots[6] = myself->closure.frame->slots[2]; /* i */
  frame->slots[7] = myself->closure.frame->slots[8]; /* skip_line */
  frame->slots[8] = myself->closure.frame->slots[6]; /* quote_count */
  frame->slots[9] = myself->closure.frame->slots[3]; /* s */
  frame->slots[10] = myself->closure.frame->slots[9]; /* get_indent */
  frame->slots[11] = myself->closure.frame->slots[10]; /* convert */
  frame->slots[12] = myself->closure.frame->slots[7]; /* TokenizationError */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 88: ... :
  // 89:   $add_newline:
  // 90:     repeat pending_newlines:
  // 91:       push &new_text newline
  // 92:       push &fragment.indents_of indent
  // 93:   
  // 94:   $add_indent:
  // 95:     push &new_text indent_marker
  // 96:     push &fragment.indents_of indent
  // 97:     dec &pending_newlines
  // ...
  frame->slots[13] /* temp__1 */ = create_closure(entry__compiler__tokenize_69, 0);
  // 88: forever:
  // 89:   $add_newline:
  // 90:     repeat pending_newlines:
  // 91:       push &new_text newline
  // 92:       push &fragment.indents_of indent
  // 93:   
  // 94:   $add_indent:
  // 95:     push &new_text indent_marker
  // 96:     push &fragment.indents_of indent
  // 97:     dec &pending_newlines
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[13] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__forever();
  func = myself->type;
  frame->cont = cont__compiler__tokenize_140;
}
static void entry__compiler__tokenize_69(void) {
  allocate_initialized_frame_gc(13, 21);
  // slot allocations:
  // pending_newlines: 0
  // new_text: 1
  // fragment: 2
  // text: 3
  // i: 4
  // skip_line: 5
  // quote_count: 6
  // s: 7
  // get_indent: 8
  // current_indent: 9
  // convert: 10
  // TokenizationError: 11
  // return: 12
  // add_newline: 13
  // add_indent: 14
  // is_a_remark: 15
  // is_a_multi_line_string: 16
  // is_inline_C: 17
  // indent: 18
  frame->slots[0] = myself->closure.frame->slots[2]; /* pending_newlines */
  frame->slots[1] = myself->closure.frame->slots[3]; /* new_text */
  frame->slots[2] = myself->closure.frame->slots[4]; /* fragment */
  frame->slots[3] = myself->closure.frame->slots[5]; /* text */
  frame->slots[4] = myself->closure.frame->slots[6]; /* i */
  frame->slots[5] = myself->closure.frame->slots[7]; /* skip_line */
  frame->slots[6] = myself->closure.frame->slots[8]; /* quote_count */
  frame->slots[7] = myself->closure.frame->slots[9]; /* s */
  frame->slots[8] = myself->closure.frame->slots[10]; /* get_indent */
  frame->slots[9] = myself->closure.frame->slots[0]; /* current_indent */
  frame->slots[10] = myself->closure.frame->slots[11]; /* convert */
  frame->slots[11] = myself->closure.frame->slots[12]; /* TokenizationError */
  frame->slots[12] = myself->closure.frame->slots[1]; /* return */
  frame->slots[13] /* add_newline */ = create_future();
  frame->slots[14] /* add_indent */ = create_future();
  frame->slots[15] /* is_a_remark */ = create_future();
  frame->slots[16] /* is_a_multi_line_string */ = create_future();
  frame->slots[17] /* is_inline_C */ = create_future();
  frame->slots[18] /* indent */ = create_cell();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 89: ... :
  // 90:   repeat pending_newlines:
  // 91:     push &new_text newline
  // 92:     push &fragment.indents_of indent
  frame->slots[19] /* temp__1 */ = create_closure(entry__compiler__tokenize_70, 0);
  // 89: $add_newline:
  // 90:   repeat pending_newlines:
  // 91:     push &new_text newline
  // 92:     push &fragment.indents_of indent
  initialize_future(frame->slots[13] /* add_newline */, frame->slots[19] /* temp__1 */);
  // 94: ... :
  // 95:   push &new_text indent_marker
  // 96:   push &fragment.indents_of indent
  // 97:   dec &pending_newlines
  // 98:   add_newline
  frame->slots[19] /* temp__1 */ = create_closure(entry__compiler__tokenize_75, 0);
  // 94: $add_indent:
  // 95:   push &new_text indent_marker
  // 96:   push &fragment.indents_of indent
  // 97:   dec &pending_newlines
  // 98:   add_newline
  initialize_future(frame->slots[14] /* add_indent */, frame->slots[19] /* temp__1 */);
  // 100: ... text(i)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* i */;
  result_count = 1;
  myself = frame->slots[3] /* text */;
  func = myself->type;
  frame->cont = cont__compiler__tokenize_80;
}
static void entry__compiler__tokenize_71(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // new_text: 0
  // fragment: 1
  // indent: 2
  frame->slots[0] = myself->closure.frame->slots[1]; /* new_text */
  frame->slots[1] = myself->closure.frame->slots[2]; /* fragment */
  frame->slots[2] = myself->closure.frame->slots[3]; /* indent */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 91: push &new_text newline
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* new_text */;
  arguments->slots[1] = get__newline();
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__tokenize_72;
}
static void cont__compiler__tokenize_72(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* new_text */ = arguments->slots[0];
  // 92: ... fragment.indents_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* fragment */;
  result_count = 1;
  myself = get__indents_of();
  func = myself->type;
  frame->cont = cont__compiler__tokenize_73;
}
static void cont__compiler__tokenize_73(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 92: push &fragment.indents_of indent
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* indent */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__tokenize_74;
}
static void cont__compiler__tokenize_74(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 92: ... &fragment.indents_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[1])->contents /* fragment */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__indents_of, frame->slots[4] /* temp__2 */);
    ((CELL *)frame->slots[1])->contents /* fragment */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__tokenize_70(void) {
  allocate_initialized_frame_gc(4, 5);
  // slot allocations:
  // pending_newlines: 0
  // new_text: 1
  // fragment: 2
  // indent: 3
  frame->slots[0] = myself->closure.frame->slots[0]; /* pending_newlines */
  frame->slots[1] = myself->closure.frame->slots[1]; /* new_text */
  frame->slots[2] = myself->closure.frame->slots[2]; /* fragment */
  frame->slots[3] = myself->closure.frame->slots[18]; /* indent */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 90: ... :
  // 91:   push &new_text newline
  // 92:   push &fragment.indents_of indent
  frame->slots[4] /* temp__1 */ = create_closure(entry__compiler__tokenize_71, 0);
  // 90: repeat pending_newlines:
  // 91:   push &new_text newline
  // 92:   push &fragment.indents_of indent
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* pending_newlines */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__repeat();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__tokenize_75(void) {
  allocate_initialized_frame_gc(5, 7);
  // slot allocations:
  // new_text: 0
  // fragment: 1
  // indent: 2
  // pending_newlines: 3
  // add_newline: 4
  frame->slots[0] = myself->closure.frame->slots[1]; /* new_text */
  frame->slots[1] = myself->closure.frame->slots[2]; /* fragment */
  frame->slots[2] = myself->closure.frame->slots[18]; /* indent */
  frame->slots[3] = myself->closure.frame->slots[0]; /* pending_newlines */
  frame->slots[4] = myself->closure.frame->slots[13]; /* add_newline */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 95: push &new_text indent_marker
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* new_text */;
  arguments->slots[1] = get__indent_marker();
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__tokenize_76;
}
static void cont__compiler__tokenize_76(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* new_text */ = arguments->slots[0];
  // 96: ... fragment.indents_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* fragment */;
  result_count = 1;
  myself = get__indents_of();
  func = myself->type;
  frame->cont = cont__compiler__tokenize_77;
}
static void cont__compiler__tokenize_77(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 96: push &fragment.indents_of indent
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* indent */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__tokenize_78;
}
static void cont__compiler__tokenize_78(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 96: ... &fragment.indents_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[1])->contents /* fragment */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__indents_of, frame->slots[6] /* temp__2 */);
    ((CELL *)frame->slots[1])->contents /* fragment */ = temp;

  }
  // 97: dec &pending_newlines
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* pending_newlines */;
  result_count = 1;
  myself = get__dec();
  func = myself->type;
  frame->cont = cont__compiler__tokenize_79;
}
static void cont__compiler__tokenize_79(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* pending_newlines */ = arguments->slots[0];
  // 98: add_newline
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[4] /* add_newline */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__tokenize_80(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[19] /* temp__1 */ = arguments->slots[0];
  // 100: $is_a_remark text(i) == '#'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[19] /* temp__1 */;
  arguments->slots[1] = character__35;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__compiler__tokenize_81;
}
static void cont__compiler__tokenize_81(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[15] /* is_a_remark */, arguments->slots[0]);
  // 101: skip_line
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = frame->slots[5] /* skip_line */;
  func = myself->type;
  frame->cont = cont__compiler__tokenize_82;
}
static void cont__compiler__tokenize_82(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 102: $is_a_multi_line_string quote_count.is_odd
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[6])->contents /* quote_count */;
  result_count = 1;
  myself = get__is_odd();
  func = myself->type;
  frame->cont = cont__compiler__tokenize_83;
}
static void cont__compiler__tokenize_83(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[16] /* is_a_multi_line_string */, arguments->slots[0]);
  // 103: ... i > 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__1;
  arguments->slots[1] = ((CELL *)frame->slots[4])->contents /* i */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__compiler__tokenize_84;
}
static void cont__compiler__tokenize_84(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[19] /* temp__1 */ = arguments->slots[0];
  // 103: ... text(i-1) == '{'
  frame->slots[20] /* temp__2 */ = create_closure(entry__compiler__tokenize_85, 0);
  // 103: $is_inline_C i > 1 && text(i-1) == '{'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[19] /* temp__1 */;
  arguments->slots[1] = frame->slots[20] /* temp__2 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__compiler__tokenize_89;
}
static void entry__compiler__tokenize_85(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // text: 0
  // i: 1
  frame->slots[0] = myself->closure.frame->slots[3]; /* text */
  frame->slots[1] = myself->closure.frame->slots[4]; /* i */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 103: ... i-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* i */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__compiler__tokenize_86;
}
static void cont__compiler__tokenize_86(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 103: ... text(i-1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = frame->slots[0] /* text */;
  func = myself->type;
  frame->cont = cont__compiler__tokenize_87;
}
static void cont__compiler__tokenize_87(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 103: ... text(i-1) == '{'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = character__123;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__compiler__tokenize_88;
}
static void cont__compiler__tokenize_88(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 103: ... text(i-1) == '{'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__tokenize_89(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[17] /* is_inline_C */, arguments->slots[0]);
  // 104: ... i-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* i */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__compiler__tokenize_90;
}
static void cont__compiler__tokenize_90(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[20] /* temp__2 */ = arguments->slots[0];
  // 104: ... range(text s i-1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* text */;
  arguments->slots[1] = ((CELL *)frame->slots[7])->contents /* s */;
  arguments->slots[2] = frame->slots[20] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__compiler__tokenize_91;
}
static void cont__compiler__tokenize_91(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[19] /* temp__1 */ = arguments->slots[0];
  // 104: append &new_text range(text s i-1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* new_text */;
  arguments->slots[1] = frame->slots[19] /* temp__1 */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__compiler__tokenize_92;
}
static void cont__compiler__tokenize_92(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* new_text */ = arguments->slots[0];
  // 105: get_indent $$indent
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = frame->slots[8] /* get_indent */;
  func = myself->type;
  frame->cont = cont__compiler__tokenize_93;
}
static void cont__compiler__tokenize_93(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[18])->contents /* indent */ = arguments->slots[0];
  // 106: !s i
  ((CELL *)frame->slots[7])->contents /* s */ = ((CELL *)frame->slots[4])->contents /* i */;
  // 107: ... indent > current_indent
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* current_indent */;
  arguments->slots[1] = ((CELL *)frame->slots[18])->contents /* indent */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__compiler__tokenize_94;
}
static void cont__compiler__tokenize_94(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[19] /* temp__1 */ = arguments->slots[0];
  // 107: ... :
  // 108:   add_indent
  // 109:   if
  // 110:     is_a_remark || is_a_multi_line_string || is_inline_C:
  // 111:       # maybe irregular indentations
  // 112:       
  // 113:       $rs i
  // 114:       $$least_indent indent
  // 115:       do: (-> break)
  // 116:         forever:
  // ...
  frame->slots[20] /* temp__2 */ = create_closure(entry__compiler__tokenize_95, 0);
  // 107: if indent > current_indent:
  // 108:   add_indent
  // 109:   if
  // 110:     is_a_remark || is_a_multi_line_string || is_inline_C:
  // 111:       # maybe irregular indentations
  // 112:       
  // 113:       $rs i
  // 114:       $$least_indent indent
  // 115:       do: (-> break)
  // 116:         forever:
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[19] /* temp__1 */;
  arguments->slots[1] = frame->slots[20] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__tokenize_136;
}
static void entry__compiler__tokenize_101(void) {
  allocate_initialized_frame_gc(9, 12);
  // slot allocations:
  // i: 0
  // indent: 1
  // skip_line: 2
  // get_indent: 3
  // current_indent: 4
  // new_text: 5
  // text: 6
  // s: 7
  // add_newline: 8
  // rs: 9
  // least_indent: 10
  frame->slots[0] = myself->closure.frame->slots[4]; /* i */
  frame->slots[1] = myself->closure.frame->slots[5]; /* indent */
  frame->slots[2] = myself->closure.frame->slots[6]; /* skip_line */
  frame->slots[3] = myself->closure.frame->slots[7]; /* get_indent */
  frame->slots[4] = myself->closure.frame->slots[8]; /* current_indent */
  frame->slots[5] = myself->closure.frame->slots[9]; /* new_text */
  frame->slots[6] = myself->closure.frame->slots[10]; /* text */
  frame->slots[7] = myself->closure.frame->slots[11]; /* s */
  frame->slots[8] = myself->closure.frame->slots[12]; /* add_newline */
  // _define $rs i
  frame->slots[9] /* rs */ = create_future();
  frame->slots[10] /* least_indent */ = create_cell();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 113: $rs i
  initialize_maybe_future(frame->slots[9] /* rs */, ((CELL *)frame->slots[0])->contents /* i */);
  // 114: $$least_indent indent
  ((CELL *)frame->slots[10])->contents /* least_indent */ = ((CELL *)frame->slots[1])->contents /* indent */;
  // 115: ... : (-> break)
  // 116:   forever:
  // 117:     skip_line
  // 118:     get_indent $next_indent
  // 119:     if next_indent <= current_indent break
  // 120:     reduce_to &least_indent next_indent
  frame->slots[11] /* temp__1 */ = create_closure(entry__compiler__tokenize_102, 0);
  // 115: do: (-> break)
  // 116:   forever:
  // 117:     skip_line
  // 118:     get_indent $next_indent
  // 119:     if next_indent <= current_indent break
  // 120:     reduce_to &least_indent next_indent
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__1 */;
  result_count = 0;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__compiler__tokenize_111;
}
static void entry__compiler__tokenize_102(void) {
  allocate_initialized_frame_gc(5, 6);
  // slot allocations:
  // break: 0
  // skip_line: 1
  // get_indent: 2
  // current_indent: 3
  // least_indent: 4
  frame->slots[0] /* break */ = create_continuation();
  frame->slots[1] = myself->closure.frame->slots[2]; /* skip_line */
  frame->slots[2] = myself->closure.frame->slots[3]; /* get_indent */
  frame->slots[3] = myself->closure.frame->slots[4]; /* current_indent */
  frame->slots[4] = myself->closure.frame->slots[10]; /* least_indent */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 116: ... :
  // 117:   skip_line
  // 118:   get_indent $next_indent
  // 119:   if next_indent <= current_indent break
  // 120:   reduce_to &least_indent next_indent
  frame->slots[5] /* temp__1 */ = create_closure(entry__compiler__tokenize_103, 0);
  // 116: forever:
  // 117:   skip_line
  // 118:   get_indent $next_indent
  // 119:   if next_indent <= current_indent break
  // 120:   reduce_to &least_indent next_indent
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__forever();
  func = myself->type;
  frame->cont = cont__compiler__tokenize_110;
}
static void entry__compiler__tokenize_103(void) {
  allocate_initialized_frame_gc(5, 8);
  // slot allocations:
  // skip_line: 0
  // get_indent: 1
  // current_indent: 2
  // break: 3
  // least_indent: 4
  // next_indent: 5
  frame->slots[0] = myself->closure.frame->slots[1]; /* skip_line */
  frame->slots[1] = myself->closure.frame->slots[2]; /* get_indent */
  frame->slots[2] = myself->closure.frame->slots[3]; /* current_indent */
  frame->slots[3] = myself->closure.frame->slots[0]; /* break */
  frame->slots[4] = myself->closure.frame->slots[4]; /* least_indent */
  frame->slots[5] /* next_indent */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 117: skip_line
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = frame->slots[0] /* skip_line */;
  func = myself->type;
  frame->cont = cont__compiler__tokenize_104;
}
static void cont__compiler__tokenize_104(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 118: get_indent $next_indent
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = frame->slots[1] /* get_indent */;
  func = myself->type;
  frame->cont = cont__compiler__tokenize_105;
}
static void cont__compiler__tokenize_105(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* next_indent */, arguments->slots[0]);
  // 119: ... next_indent <= current_indent
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* current_indent */;
  arguments->slots[1] = frame->slots[5] /* next_indent */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__compiler__tokenize_106;
}
static void cont__compiler__tokenize_106(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 119: ... next_indent <= current_indent
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__compiler__tokenize_107;
}
static void cont__compiler__tokenize_107(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 119: if next_indent <= current_indent break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* break */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__tokenize_108;
}
static void cont__compiler__tokenize_108(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 120: reduce_to &least_indent next_indent
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* least_indent */;
  arguments->slots[1] = frame->slots[5] /* next_indent */;
  result_count = 1;
  myself = get__reduce_to();
  func = myself->type;
  frame->cont = cont__compiler__tokenize_109;
}
static void cont__compiler__tokenize_109(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[4])->contents /* least_indent */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__tokenize_110(void) {
  myself = frame->slots[0] /* break */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__compiler__tokenize_111(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 121: !i rs
  ((CELL *)frame->slots[0])->contents /* i */ = frame->slots[9] /* rs */;
  // 122: ... : (-> break)
  // 123:   forever:
  // 124:     skip_line
  // 125:     repeat indent-least_indent: push &new_text ' '
  // 126:     append &new_text range(text s i-1)
  // 127:     get_indent !indent
  // 128:     !s i
  // 129:     if indent <= current_indent break
  // 130:     add_newline
  frame->slots[11] /* temp__1 */ = create_closure(entry__compiler__tokenize_112, 0);
  // 122: do: (-> break)
  // 123:   forever:
  // 124:     skip_line
  // 125:     repeat indent-least_indent: push &new_text ' '
  // 126:     append &new_text range(text s i-1)
  // 127:     get_indent !indent
  // 128:     !s i
  // 129:     if indent <= current_indent break
  // 130:     add_newline
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__1 */;
  result_count = 0;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__compiler__tokenize_127;
}
static void entry__compiler__tokenize_112(void) {
  allocate_initialized_frame_gc(11, 12);
  // slot allocations:
  // break: 0
  // skip_line: 1
  // indent: 2
  // least_indent: 3
  // new_text: 4
  // text: 5
  // s: 6
  // i: 7
  // get_indent: 8
  // current_indent: 9
  // add_newline: 10
  frame->slots[0] /* break */ = create_continuation();
  frame->slots[1] = myself->closure.frame->slots[2]; /* skip_line */
  frame->slots[2] = myself->closure.frame->slots[1]; /* indent */
  frame->slots[3] = myself->closure.frame->slots[10]; /* least_indent */
  frame->slots[4] = myself->closure.frame->slots[5]; /* new_text */
  frame->slots[5] = myself->closure.frame->slots[6]; /* text */
  frame->slots[6] = myself->closure.frame->slots[7]; /* s */
  frame->slots[7] = myself->closure.frame->slots[0]; /* i */
  frame->slots[8] = myself->closure.frame->slots[3]; /* get_indent */
  frame->slots[9] = myself->closure.frame->slots[4]; /* current_indent */
  frame->slots[10] = myself->closure.frame->slots[8]; /* add_newline */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 123: ... :
  // 124:   skip_line
  // 125:   repeat indent-least_indent: push &new_text ' '
  // 126:   append &new_text range(text s i-1)
  // 127:   get_indent !indent
  // 128:   !s i
  // 129:   if indent <= current_indent break
  // 130:   add_newline
  frame->slots[11] /* temp__1 */ = create_closure(entry__compiler__tokenize_113, 0);
  // 123: forever:
  // 124:   skip_line
  // 125:   repeat indent-least_indent: push &new_text ' '
  // 126:   append &new_text range(text s i-1)
  // 127:   get_indent !indent
  // 128:   !s i
  // 129:   if indent <= current_indent break
  // 130:   add_newline
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__forever();
  func = myself->type;
  frame->cont = cont__compiler__tokenize_126;
}
static void entry__compiler__tokenize_113(void) {
  allocate_initialized_frame_gc(11, 13);
  // slot allocations:
  // skip_line: 0
  // indent: 1
  // least_indent: 2
  // new_text: 3
  // text: 4
  // s: 5
  // i: 6
  // get_indent: 7
  // current_indent: 8
  // break: 9
  // add_newline: 10
  frame->slots[0] = myself->closure.frame->slots[1]; /* skip_line */
  frame->slots[1] = myself->closure.frame->slots[2]; /* indent */
  frame->slots[2] = myself->closure.frame->slots[3]; /* least_indent */
  frame->slots[3] = myself->closure.frame->slots[4]; /* new_text */
  frame->slots[4] = myself->closure.frame->slots[5]; /* text */
  frame->slots[5] = myself->closure.frame->slots[6]; /* s */
  frame->slots[6] = myself->closure.frame->slots[7]; /* i */
  frame->slots[7] = myself->closure.frame->slots[8]; /* get_indent */
  frame->slots[8] = myself->closure.frame->slots[9]; /* current_indent */
  frame->slots[9] = myself->closure.frame->slots[0]; /* break */
  frame->slots[10] = myself->closure.frame->slots[10]; /* add_newline */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 124: skip_line
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = frame->slots[0] /* skip_line */;
  func = myself->type;
  frame->cont = cont__compiler__tokenize_114;
}
static void cont__compiler__tokenize_114(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 125: ... indent-least_indent
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* indent */;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* least_indent */;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__compiler__tokenize_115;
}
static void cont__compiler__tokenize_115(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 125: ... : push &new_text ' '
  frame->slots[12] /* temp__2 */ = create_closure(entry__compiler__tokenize_116, 0);
  // 125: repeat indent-least_indent: push &new_text ' '
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__1 */;
  arguments->slots[1] = frame->slots[12] /* temp__2 */;
  result_count = 0;
  myself = get__repeat();
  func = myself->type;
  frame->cont = cont__compiler__tokenize_118;
}
static void entry__compiler__tokenize_116(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // new_text: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* new_text */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 125: ... push &new_text ' '
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* new_text */;
  arguments->slots[1] = character__32;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__tokenize_117;
}
static void cont__compiler__tokenize_117(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* new_text */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__tokenize_118(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 126: ... i-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[6])->contents /* i */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__compiler__tokenize_119;
}
static void cont__compiler__tokenize_119(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__2 */ = arguments->slots[0];
  // 126: ... range(text s i-1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* text */;
  arguments->slots[1] = ((CELL *)frame->slots[5])->contents /* s */;
  arguments->slots[2] = frame->slots[12] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__compiler__tokenize_120;
}
static void cont__compiler__tokenize_120(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 126: append &new_text range(text s i-1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* new_text */;
  arguments->slots[1] = frame->slots[11] /* temp__1 */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__compiler__tokenize_121;
}
static void cont__compiler__tokenize_121(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* new_text */ = arguments->slots[0];
  // 127: get_indent !indent
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = frame->slots[7] /* get_indent */;
  func = myself->type;
  frame->cont = cont__compiler__tokenize_122;
}
static void cont__compiler__tokenize_122(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* indent */ = arguments->slots[0];
  // 128: !s i
  ((CELL *)frame->slots[5])->contents /* s */ = ((CELL *)frame->slots[6])->contents /* i */;
  // 129: ... indent <= current_indent
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* current_indent */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* indent */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__compiler__tokenize_123;
}
static void cont__compiler__tokenize_123(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__2 */ = arguments->slots[0];
  // 129: ... indent <= current_indent
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[12] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__compiler__tokenize_124;
}
static void cont__compiler__tokenize_124(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 129: if indent <= current_indent break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__1 */;
  arguments->slots[1] = frame->slots[9] /* break */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__tokenize_125;
}
static void cont__compiler__tokenize_125(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 130: add_newline
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[10] /* add_newline */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__tokenize_126(void) {
  myself = frame->slots[0] /* break */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__compiler__tokenize_127(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 131: push &new_text outdent_marker
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[5])->contents /* new_text */;
  arguments->slots[1] = get__outdent_marker();
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__tokenize_128;
}
static void cont__compiler__tokenize_128(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[5])->contents /* new_text */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__tokenize_129(void) {
  allocate_initialized_frame_gc(5, 7);
  // slot allocations:
  // indent: 0
  // convert: 1
  // current_indent: 2
  // TokenizationError: 3
  // new_text: 4
  frame->slots[0] = myself->closure.frame->slots[5]; /* indent */
  frame->slots[1] = myself->closure.frame->slots[13]; /* convert */
  frame->slots[2] = myself->closure.frame->slots[8]; /* current_indent */
  frame->slots[3] = myself->closure.frame->slots[14]; /* TokenizationError */
  frame->slots[4] = myself->closure.frame->slots[9]; /* new_text */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 133: !indent convert(indent)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* indent */;
  result_count = 1;
  myself = frame->slots[1] /* convert */;
  func = myself->type;
  frame->cont = cont__compiler__tokenize_130;
}
static void cont__compiler__tokenize_130(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* indent */ = arguments->slots[0];
  // 134: ... indent > current_indent
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* current_indent */;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* indent */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__compiler__tokenize_131;
}
static void cont__compiler__tokenize_131(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 134: ... : TokenizationError "invalid indentation"
  frame->slots[6] /* temp__2 */ = create_closure(entry__compiler__tokenize_132, 0);
  // 134: if indent > current_indent: TokenizationError "invalid indentation"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__tokenize_134;
}
static void entry__compiler__tokenize_132(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // TokenizationError: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* TokenizationError */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 134: ... TokenizationError "invalid indentation"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__f6816391653ef18d;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* TokenizationError */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__tokenize_134(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 135: push &new_text outdent_marker
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* new_text */;
  arguments->slots[1] = get__outdent_marker();
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__tokenize_135;
}
static void cont__compiler__tokenize_135(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[4])->contents /* new_text */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__tokenize_95(void) {
  allocate_initialized_frame_gc(15, 19);
  // slot allocations:
  // add_indent: 0
  // is_a_remark: 1
  // is_a_multi_line_string: 2
  // is_inline_C: 3
  // i: 4
  // indent: 5
  // skip_line: 6
  // get_indent: 7
  // current_indent: 8
  // new_text: 9
  // text: 10
  // s: 11
  // add_newline: 12
  // convert: 13
  // TokenizationError: 14
  frame->slots[0] = myself->closure.frame->slots[14]; /* add_indent */
  frame->slots[1] = myself->closure.frame->slots[15]; /* is_a_remark */
  frame->slots[2] = myself->closure.frame->slots[16]; /* is_a_multi_line_string */
  frame->slots[3] = myself->closure.frame->slots[17]; /* is_inline_C */
  frame->slots[4] = myself->closure.frame->slots[4]; /* i */
  frame->slots[5] = myself->closure.frame->slots[18]; /* indent */
  frame->slots[6] = myself->closure.frame->slots[5]; /* skip_line */
  frame->slots[7] = myself->closure.frame->slots[8]; /* get_indent */
  frame->slots[8] = myself->closure.frame->slots[9]; /* current_indent */
  frame->slots[9] = myself->closure.frame->slots[1]; /* new_text */
  frame->slots[10] = myself->closure.frame->slots[3]; /* text */
  frame->slots[11] = myself->closure.frame->slots[7]; /* s */
  frame->slots[12] = myself->closure.frame->slots[13]; /* add_newline */
  frame->slots[13] = myself->closure.frame->slots[10]; /* convert */
  frame->slots[14] = myself->closure.frame->slots[11]; /* TokenizationError */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 108: add_indent
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = frame->slots[0] /* add_indent */;
  func = myself->type;
  frame->cont = cont__compiler__tokenize_96;
}
static void cont__compiler__tokenize_96(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 110: ... is_a_multi_line_string || is_inline_C
  frame->slots[16] /* temp__2 */ = create_closure(entry__compiler__tokenize_97, 0);
  // 110: is_a_remark || is_a_multi_line_string || is_inline_C
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* is_a_remark */;
  arguments->slots[1] = frame->slots[16] /* temp__2 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__compiler__tokenize_100;
}
static void entry__compiler__tokenize_97(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // is_a_multi_line_string: 0
  // is_inline_C: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* is_a_multi_line_string */
  frame->slots[1] = myself->closure.frame->slots[3]; /* is_inline_C */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 110: ... is_inline_C
  frame->slots[3] /* temp__2 */ = create_closure(entry__compiler__tokenize_98, 0);
  // 110: ... is_a_multi_line_string || is_inline_C
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* is_a_multi_line_string */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__compiler__tokenize_99;
}
static void entry__compiler__tokenize_98(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // is_inline_C: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* is_inline_C */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 110: ... is_inline_C
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* is_inline_C */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__tokenize_99(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 110: ... is_a_multi_line_string || is_inline_C
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__tokenize_100(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[15] /* temp__1 */ = arguments->slots[0];
  // 110: ... :
  // 111:   # maybe irregular indentations
  // 112:   
  // 113:   $rs i
  // 114:   $$least_indent indent
  // 115:   do: (-> break)
  // 116:     forever:
  // 117:       skip_line
  // 118:       get_indent $next_indent
  // 119:       if next_indent <= current_indent break
  // ...
  frame->slots[17] /* temp__3 */ = create_closure(entry__compiler__tokenize_101, 0);
  // 132: :
  // 133:   !indent convert(indent)
  // 134:   if indent > current_indent: TokenizationError "invalid indentation"
  // 135:   push &new_text outdent_marker
  frame->slots[18] /* temp__4 */ = create_closure(entry__compiler__tokenize_129, 0);
  // 109: if
  // 110:   is_a_remark || is_a_multi_line_string || is_inline_C:
  // 111:     # maybe irregular indentations
  // 112:     
  // 113:     $rs i
  // 114:     $$least_indent indent
  // 115:     do: (-> break)
  // 116:       forever:
  // 117:         skip_line
  // 118:         get_indent $next_indent
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[15] /* temp__1 */;
  arguments->slots[1] = frame->slots[17] /* temp__3 */;
  arguments->slots[2] = frame->slots[18] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__tokenize_136(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 136: ... indent < current_indent
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[18])->contents /* indent */;
  arguments->slots[1] = frame->slots[9] /* current_indent */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__compiler__tokenize_137;
}
static void cont__compiler__tokenize_137(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[19] /* temp__1 */ = arguments->slots[0];
  // 136: ... : return indent
  frame->slots[20] /* temp__2 */ = create_closure(entry__compiler__tokenize_138, 0);
  // 136: if indent < current_indent: return indent
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[19] /* temp__1 */;
  arguments->slots[1] = frame->slots[20] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__tokenize_139;
}
static void entry__compiler__tokenize_138(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // return: 0
  // indent: 1
  frame->slots[0] = myself->closure.frame->slots[12]; /* return */
  frame->slots[1] = myself->closure.frame->slots[18]; /* indent */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 136: ... return indent
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* indent */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__tokenize_139(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 137: add_newline
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[13] /* add_newline */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__tokenize_140(void) {
  myself = frame->slots[1] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__compiler__tokenize_141(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* text */, arguments->slots[0]);
  // 38: $$i 1
  ((CELL *)frame->slots[2])->contents /* i */ = number__1;
  // 39: $$s 1
  ((CELL *)frame->slots[3])->contents /* s */ = number__1;
  // 40: $$new_text ""
  ((CELL *)frame->slots[4])->contents /* new_text */ = empty_string;
  // 41: $$pending_newlines 0
  ((CELL *)frame->slots[5])->contents /* pending_newlines */ = number__0;
  // 42: $$quote_count undefined
  ((CELL *)frame->slots[6])->contents /* quote_count */ = get__undefined();
  // 139: ... convert(0)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__0;
  result_count = 1;
  myself = frame->slots[10] /* convert */;
  func = myself->type;
  frame->cont = cont__compiler__tokenize_142;
}
static void cont__compiler__tokenize_142(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 139: ignore convert(0)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__1 */;
  result_count = 0;
  myself = get__ignore();
  func = myself->type;
  frame->cont = cont__compiler__tokenize_143;
}
static void cont__compiler__tokenize_143(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 140: push &new_text newline
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* new_text */;
  arguments->slots[1] = get__newline();
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__tokenize_144;
}
static void cont__compiler__tokenize_144(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[4])->contents /* new_text */ = arguments->slots[0];
  // 141: !fragment.source_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* fragment */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__source_of, ((CELL *)frame->slots[4])->contents /* new_text */);
    ((CELL *)frame->slots[0])->contents /* fragment */ = temp;

  }
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* fragment */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
EXPORT void collect__tokenizer(void) {
  var.compiler__indent_marker = collect_node(var.compiler__indent_marker);
  var.compiler__outdent_marker = collect_node(var.compiler__outdent_marker);
  var.compiler__newline = collect_node(var.compiler__newline);
  var.compiler__tokenize = collect_node(var.compiler__tokenize);
}

static int already_run_phase_1 = false;

EXPORT void phase_1__tokenizer(void) {
  if (already_run_phase_1) return;
  already_run_phase_1 = true;
  register_module_info(&module_info);
}

static int already_run_phase_2 = false;

EXPORT void phase_2__tokenizer(void) {
  if (already_run_phase_2) return;
  already_run_phase_2 = true;
  set_module("tokenizer");
  character__9 = from_uchar32(9);
  character__35 = from_uchar32(35);
  character__10 = from_uchar32(10);
  number__0 = from_uint32(0U);
  number__8 = from_uint32(8U);
  character__2 = from_uchar32(2);
  character__34 = from_uchar32(34);
  character__123 = from_uchar32(123);
  character__32 = from_uchar32(32);
  character__1 = from_uchar32(1);
  number__1 = from_uint32(1U);
  string__a18ab04649b43ca6 = from_latin_1_string(
    "____________________________________\n"
    "TOKENIZATION ERROR IN LINE ",
    64);
  string__6c6619488b29e163 = from_latin_1_string(" OF FILE \042", 10);
  string__fa730c15ff96bc6 = from_latin_1_string("\042:\012", 3);
  string__2d7981f4e6002bcf = from_latin_1_string("!\012", 2);
  string__dd17af2f619a6908 = from_latin_1_string("tabulator character within line detected", 40);
  string__97eea539018d4d4b = from_latin_1_string("empty line contains whitespace", 30);
  string__f6816391653ef18d = from_latin_1_string("invalid indentation", 19);
  func__compiler__tokenize = create_function(entry__compiler__tokenize, 1);
}

static int already_run_phase_3 = false;

EXPORT void phase_3__tokenizer(void) {
  if (already_run_phase_3) return;
  already_run_phase_3 = true;
  set_module("tokenizer");
  set_used_namespaces(used_namespaces);
  var.compiler__indent_marker = create_future();
  define_single_assign_static("compiler", "indent_marker", get__compiler__indent_marker, &var.compiler__indent_marker);
  var.compiler__outdent_marker = create_future();
  define_single_assign_static("compiler", "outdent_marker", get__compiler__outdent_marker, &var.compiler__outdent_marker);
  var.compiler__newline = create_future();
  define_single_assign_static("compiler", "newline", get__compiler__newline, &var.compiler__newline);
  var.compiler__tokenize = create_future();
  define_single_assign_static("compiler", "tokenize", get__compiler__tokenize, &var.compiler__tokenize);
}

static int already_run_phase_4 = false;

EXPORT void phase_4__tokenizer(void) {
  if (already_run_phase_4) return;
  already_run_phase_4 = true;
  set_module("tokenizer");
  set_used_namespaces(used_namespaces);
  use_read_only(NULL, "append", &get__append, &get_value_or_future__append);
  use_read_only(NULL, "case", &get__case, &get_value_or_future__case);
  use_read_only(NULL, "count_occurrences", &get__count_occurrences, &get_value_or_future__count_occurrences);
  use_read_only(NULL, "dec", &get__dec, &get_value_or_future__dec);
  use_read_only(NULL, "do", &get__do, &get_value_or_future__do);
  use_read_only(NULL, "empty_list", &get__empty_list, &get_value_or_future__empty_list);
  use_read_only(NULL, "ewrite", &get__ewrite, &get_value_or_future__ewrite);
  use_read_only(NULL, "exit", &get__exit, &get_value_or_future__exit);
  use_read_only(NULL, "forever", &get__forever, &get_value_or_future__forever);
  use_read_only(NULL, "if", &get__if, &get_value_or_future__if);
  use_read_only(NULL, "ignore", &get__ignore, &get_value_or_future__ignore);
  use_read_only(NULL, "inc", &get__inc, &get_value_or_future__inc);
  use_read_only(NULL, "indent_marker", &get__indent_marker, &get_value_or_future__indent_marker);
  use_polymorphic_function(NULL, "indents_of", &get__indents_of, &poly_idx__indents_of);
  use_read_only(NULL, "is_odd", &get__is_odd, &get_value_or_future__is_odd);
  use_read_only(NULL, "length_of", &get__length_of, &get_value_or_future__length_of);
  use_read_only(NULL, "line_no_of", &get__line_no_of, &get_value_or_future__line_no_of);
  use_read_only(NULL, "module_name", &get__module_name, &get_value_or_future__module_name);
  use_read_only(NULL, "newline", &get__newline, &get_value_or_future__newline);
  use_read_only(NULL, "outdent_marker", &get__outdent_marker, &get_value_or_future__outdent_marker);
  use_read_only(NULL, "plus", &get__plus, &get_value_or_future__plus);
  use_read_only(NULL, "push", &get__push, &get_value_or_future__push);
  use_read_only(NULL, "range", &get__range, &get_value_or_future__range);
  use_read_only(NULL, "reduce_to", &get__reduce_to, &get_value_or_future__reduce_to);
  use_read_only(NULL, "repeat", &get__repeat, &get_value_or_future__repeat);
  use_polymorphic_function(NULL, "source_of", &get__source_of, &poly_idx__source_of);
  use_read_only("std", "and", &get__std__and, &get_value_or_future__std__and);
  use_read_only("std", "equal", &get__std__equal, &get_value_or_future__std__equal);
  use_read_only("std", "less", &get__std__less, &get_value_or_future__std__less);
  use_read_only("std", "minus", &get__std__minus, &get_value_or_future__std__minus);
  use_read_only("std", "negate", &get__std__negate, &get_value_or_future__std__negate);
  use_read_only("std", "not", &get__std__not, &get_value_or_future__std__not);
  use_read_only("std", "or", &get__std__or, &get_value_or_future__std__or);
  use_read_only("std", "string", &get__std__string, &get_value_or_future__std__string);
  use_read_only(NULL, "text_of", &get__text_of, &get_value_or_future__text_of);
  use_read_only(NULL, "to_upper_case", &get__to_upper_case, &get_value_or_future__to_upper_case);
  use_read_only(NULL, "undefined", &get__undefined, &get_value_or_future__undefined);
  use_read_only(NULL, "while", &get__while, &get_value_or_future__while);
}

static int already_run_phase_5 = false;

EXPORT void phase_5__tokenizer(void) {
  if (already_run_phase_5) return;
  already_run_phase_5 = true;
  initialize_future(var.compiler__indent_marker, character__1);
  initialize_future(var.compiler__outdent_marker, character__2);
  initialize_future(var.compiler__newline, character__10);
  initialize_future(var.compiler__tokenize, func__compiler__tokenize);
}

static int already_run_phase_6 = false;

EXPORT void phase_6__tokenizer(void) {
  if (already_run_phase_6) return;
  already_run_phase_6 = true;
  register_collector(collect__tokenizer);
}
