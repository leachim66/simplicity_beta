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
REGISTER FUNC func ASM("r14");
REGISTER FRAME *frame ASM("r15");
IMPORT void allocate_initialized_frame_gc(int slot_idx, int slot_count);
IMPORT NODE *undefined;
IMPORT int main_argc;
REGISTER int argument_count ASM("ebx");
IMPORT void *node_p;
IMPORT int result_count;
REGISTER NODE *myself ASM("r13");
IMPORT void invalid_results_error(void);
IMPORT char **main_argv;
IMPORT int polymorphic_function_count;
IMPORT int polymorphic_function_with_setter_count;
IMPORT const char **polymorphic_function_names;
IMPORT void invalid_arguments_error(void);
IMPORT void too_few_arguments_error(void);
IMPORT void too_many_arguments_error(void);
IMPORT NODE *create_closure(FUNC type, int par_count);
IMPORT NODE *create_future(void);
IMPORT void initialize_future(NODE *var, NODE *val);
typedef enum {
  EM__NORMAL,
  EM__RECORD,
  EM__REPLAY
} EVENT__MODE;
IMPORT EVENT__MODE event__mode;
IMPORT NODE *empty_string;
IMPORT void record__event(const char *name);
IMPORT void store__integer(int val);
IMPORT void successful__action(const char *name);
IMPORT void failed__action(const char *name);
IMPORT void store__long_integer(long val);
IMPORT void store__pointer(void *ptr);
IMPORT void store__int_array(const int *buf, long len);
IMPORT void store__memory(const uint8_t *buf, long len);
IMPORT void store__c_string(const char *buf);
IMPORT void retrieve__pointer(void **ptr_p);
IMPORT NODE *create_cell(void);
IMPORT void print__pointer(void *ptr);
typedef struct CELL {
  FUNC type;
  struct ATTRIBUTES *attributes;
  NODE *contents;
} CELL;
IMPORT void replay__event(const char *name);
IMPORT int replay__action(const char *name);
IMPORT void report__event(const char *name);
IMPORT void print__int_array(const int *buf, long len);
IMPORT void print__memory(const uint8_t *buf, long len);
IMPORT long retrieve__int_array(int **buf_p);
IMPORT long retrieve__memory(uint8_t **buf_p);
IMPORT NODE *zero;
IMPORT NODE *boolean_true;
IMPORT NODE *boolean_false;
IMPORT NODE *from_bool(int val);
IMPORT __attribute__ ((noreturn)) void unrecoverable_error(const char *msg, ...);
IMPORT __attribute__ ((noreturn)) void out_of_memory_error(void);
IMPORT __attribute__ ((noreturn)) void runtime_error(const char *msg, ...);
IMPORT void too_few_results_error(void);
IMPORT void too_many_results_error(void);
IMPORT void invalid_index_error(void);
IMPORT void divide_by_zero_error(void);
IMPORT void not_yet_implemented_error(void);
IMPORT void resource_error(void);
IMPORT void io_error(void);
IMPORT NODE *create_continuation(void);
IMPORT NODE *create_cell_with_contents(NODE *contents);
IMPORT NODE *collect_node(NODE *node);
IMPORT void register_module_info(MODULE_INFO *info);
IMPORT void set_module(const char *name);
IMPORT NODE *from_uchar32(unsigned int chr);
IMPORT NODE *from_uint32(uint32_t val);
IMPORT NODE *register_unique_item(const char *name);
IMPORT NODE *create_function(FUNC func, int par_count);
IMPORT NODE *from_latin_1_string(const char *str, long len);
IMPORT void set_used_namespaces(const char **namespaces);
IMPORT void assign_value(NODE **dest, NODE *val);
IMPORT void register_dynamic(int *id_p);
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
static NODE_GETTER get__append;
static NODE_GETTER get_value_or_future__append;
static NODE_GETTER get__case;
static NODE_GETTER get_value_or_future__case;
static NODE_GETTER get__cond;
static NODE_GETTER get_value_or_future__cond;
static NODE_GETTER get__contains;
static NODE_GETTER get_value_or_future__contains;
static NODE_GETTER get__converted;
static NODE_GETTER get_value_or_future__converted;
static NODE_GETTER get__dec;
static NODE_GETTER get_value_or_future__dec;
static NODE_GETTER get__do;
static NODE_GETTER get_value_or_future__do;
static NODE_GETTER get__empty_list;
static NODE_GETTER get_value_or_future__empty_list;
static NODE_GETTER get__empty_table;
static NODE_GETTER get_value_or_future__empty_table;
static NODE_GETTER get__false;
static NODE_GETTER get_value_or_future__false;
static NODE_GETTER get__for_each;
static NODE_GETTER get_value_or_future__for_each;
static NODE_GETTER get__global_names;
static NODE_GETTER get_value_or_future__global_names;
static NODE_GETTER get__if;
static NODE_GETTER get_value_or_future__if;
static NODE_GETTER get__inc;
static NODE_GETTER get_value_or_future__inc;
static NODE_GETTER get__is_a_string;
static NODE_GETTER get_value_or_future__is_a_string;
static NODE_GETTER get__is_defined;
static NODE_GETTER get_value_or_future__is_defined;
static NODE_GETTER get__is_empty;
static NODE_GETTER get_value_or_future__is_empty;
static NODE_GETTER get__join;
static NODE_GETTER get_value_or_future__join;
static NODE_GETTER get__length_of;
static NODE_GETTER get_value_or_future__length_of;
static NODE_GETTER get__list;
static NODE_GETTER get_value_or_future__list;
static NODE_GETTER get__pass;
static NODE_GETTER get_value_or_future__pass;
static NODE_GETTER get__push;
static NODE_GETTER get_value_or_future__push;
static NODE_GETTER get__put;
static NODE_GETTER get_value_or_future__put;
static NODE_GETTER get__range;
static NODE_GETTER get_value_or_future__range;
static NODE_GETTER get__replace_all;
static NODE_GETTER get_value_or_future__replace_all;
static NODE_GETTER get__std__and;
static NODE_GETTER get_value_or_future__std__and;
static NODE_GETTER get__std__equal;
static NODE_GETTER get_value_or_future__std__equal;
static NODE_GETTER get__std__key_value_pair;
static NODE_GETTER get_value_or_future__std__key_value_pair;
static NODE_GETTER get__std__less;
static NODE_GETTER get_value_or_future__std__less;
static NODE_GETTER get__std__minus;
static NODE_GETTER get_value_or_future__std__minus;
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
static NODE_GETTER get__std__value_range;
static NODE_GETTER get_value_or_future__std__value_range;
static NODE_GETTER get__trim;
static NODE_GETTER get_value_or_future__trim;
static NODE_GETTER get__true;
static NODE_GETTER get_value_or_future__true;
static NODE_GETTER get__undefined;
static NODE_GETTER get_value_or_future__undefined;
static NODE_GETTER get__unless;
static NODE_GETTER get_value_or_future__unless;
static NODE_GETTER get__use_identifier;
static NODE_GETTER get_value_or_future__use_identifier;
static NODE_GETTER get__while;
static NODE_GETTER get_value_or_future__while;
static NODE_GETTER get__write_to;
static NODE_GETTER get_value_or_future__write_to;
static NODE_GETTER get__writeln_to;
static NODE_GETTER get_value_or_future__writeln_to;
static struct {
  NODE *_EVENT;
  NODE *_ACTION;
  NODE *_INFO;
  NODE *_DATA;
  NODE *_macro_replacements;
  NODE *_define_macro;
  NODE *compiler__converted;
} var;
static const char *var_names[] = {
  "EVENT",
  "ACTION",
  "INFO",
  "DATA",
  "macro_replacements",
  "define_macro"
};
static NODE *unique__EVENT;
static NODE *unique__ACTION;
static NODE *unique__INFO;
static NODE *unique__DATA;
static int dyna_idx__event_name;
static NODE *get__event_name(void) {
  return get_dynamic_cell(dyna_idx__event_name);
}
static void set__event_name(NODE *node) {
  set_dynamic_cell(dyna_idx__event_name, node);
}
static void define__event_name(NODE *node) {
  define_dynamic_cell(dyna_idx__event_name, node);
}
static int dyna_idx__event_kind;
static NODE *get__event_kind(void) {
  return get_dynamic_cell(dyna_idx__event_kind);
}
static void set__event_kind(NODE *node) {
  set_dynamic_cell(dyna_idx__event_kind, node);
}
static void define__event_kind(NODE *node) {
  define_dynamic_cell(dyna_idx__event_kind, node);
}
static int dyna_idx__event_phase;
static NODE *get__event_phase(void) {
  return get_dynamic_cell(dyna_idx__event_phase);
}
static void set__event_phase(NODE *node) {
  set_dynamic_cell(dyna_idx__event_phase, node);
}
static void define__event_phase(NODE *node) {
  define_dynamic_cell(dyna_idx__event_phase, node);
}
static int dyna_idx__data_variables;
static NODE *get__data_variables(void) {
  return get_dynamic_cell(dyna_idx__data_variables);
}
static void set__data_variables(NODE *node) {
  set_dynamic_cell(dyna_idx__data_variables, node);
}
static void define__data_variables(NODE *node) {
  define_dynamic_cell(dyna_idx__data_variables, node);
}
static int dyna_idx__info_variables;
static NODE *get__info_variables(void) {
  return get_dynamic_cell(dyna_idx__info_variables);
}
static void set__info_variables(NODE *node) {
  set_dynamic_cell(dyna_idx__info_variables, node);
}
static void define__info_variables(NODE *node) {
  define_dynamic_cell(dyna_idx__info_variables, node);
}
static NODE *func__define_macro_1;
static void entry__define_macro_1(void);
static FRAME_INFO frame__define_macro_1 = {2, {"name", "replacement"}};
static void cont__define_macro_2(void);
static NODE *func__compiler__converted_1;
static void entry__compiler__converted_1(void);
static FRAME_INFO frame__compiler__converted_1 = {8, {"code", "return__1", "new_code", "start", "within_string", "s", "i", "len"}};
static void cont__compiler__converted_2(void);
static void cont__compiler__converted_3(void);
static NODE *func__compiler__converted_4;
static void entry__compiler__converted_4(void);
static FRAME_INFO frame__compiler__converted_4 = {7, {"len", "i", "within_string", "code", "s", "new_code", "start"}};
static void cont__compiler__converted_5(void);
static void cont__compiler__converted_6(void);
static NODE *func__compiler__converted_7;
static void entry__compiler__converted_7(void);
static FRAME_INFO frame__compiler__converted_7 = {7, {"within_string", "code", "i", "s", "new_code", "start", "len"}};
static NODE *func__compiler__converted_8;
static void entry__compiler__converted_8(void);
static FRAME_INFO frame__compiler__converted_8 = {3, {"code", "i", "within_string"}};
static void cont__compiler__converted_9(void);
static NODE *func__compiler__converted_10;
static void entry__compiler__converted_10(void);
static FRAME_INFO frame__compiler__converted_10 = {3, {"code", "i", "within_string"}};
static void cont__compiler__converted_11(void);
static void cont__compiler__converted_12(void);
static void cont__compiler__converted_13(void);
static void cont__compiler__converted_14(void);
static NODE *func__compiler__converted_15;
static void entry__compiler__converted_15(void);
static FRAME_INFO frame__compiler__converted_15 = {1, {"within_string"}};
static void cont__compiler__converted_16(void);
static void cont__compiler__converted_17(void);
static NODE *func__compiler__converted_18;
static void entry__compiler__converted_18(void);
static FRAME_INFO frame__compiler__converted_18 = {8, {"code", "i", "s", "within_string", "new_code", "start", "len", "chr"}};
static void cont__compiler__converted_19(void);
static void cont__compiler__converted_20(void);
static void cont__compiler__converted_21(void);
static void cont__compiler__converted_22(void);
static NODE *func__compiler__converted_23;
static void entry__compiler__converted_23(void);
static FRAME_INFO frame__compiler__converted_23 = {2, {"s", "i"}};
static void cont__compiler__converted_24(void);
static NODE *func__compiler__converted_25;
static void entry__compiler__converted_25(void);
static FRAME_INFO frame__compiler__converted_25 = {2, {"s", "i"}};
static void cont__compiler__converted_26(void);
static NODE *func__compiler__converted_27;
static void entry__compiler__converted_27(void);
static FRAME_INFO frame__compiler__converted_27 = {4, {"s", "code", "i", "within_string"}};
static void cont__compiler__converted_28(void);
static void cont__compiler__converted_29(void);
static void cont__compiler__converted_30(void);
static void cont__compiler__converted_31(void);
static NODE *func__compiler__converted_32;
static void entry__compiler__converted_32(void);
static FRAME_INFO frame__compiler__converted_32 = {1, {"within_string"}};
static NODE *func__compiler__converted_33;
static void entry__compiler__converted_33(void);
static FRAME_INFO frame__compiler__converted_33 = {7, {"s", "chr", "code", "i", "new_code", "start", "len"}};
static void cont__compiler__converted_34(void);
static NODE *func__compiler__converted_35;
static void entry__compiler__converted_35(void);
static FRAME_INFO frame__compiler__converted_35 = {7, {"chr", "code", "i", "s", "new_code", "start", "len"}};
static void cont__compiler__converted_36(void);
static NODE *func__compiler__converted_37;
static void entry__compiler__converted_37(void);
static FRAME_INFO frame__compiler__converted_37 = {2, {"code", "i"}};
static void cont__compiler__converted_38(void);
static void cont__compiler__converted_39(void);
static void cont__compiler__converted_40(void);
static void cont__compiler__converted_41(void);
static NODE *func__compiler__converted_42;
static void entry__compiler__converted_42(void);
static FRAME_INFO frame__compiler__converted_42 = {1, {"i"}};
static void cont__compiler__converted_43(void);
static NODE *func__compiler__converted_44;
static void entry__compiler__converted_44(void);
static FRAME_INFO frame__compiler__converted_44 = {8, {"code", "s", "i", "new_code", "start", "len", "identifier", "replacement"}};
static void cont__compiler__converted_45(void);
static void cont__compiler__converted_46(void);
static void cont__compiler__converted_47(void);
static void cont__compiler__converted_48(void);
static NODE *func__compiler__converted_49;
static void entry__compiler__converted_49(void);
static FRAME_INFO frame__compiler__converted_49 = {7, {"new_code", "code", "start", "s", "i", "len", "replacement"}};
static void cont__compiler__converted_50(void);
static void cont__compiler__converted_51(void);
static void cont__compiler__converted_52(void);
static void cont__compiler__converted_53(void);
static void cont__compiler__converted_54(void);
static NODE *func__compiler__converted_55;
static void entry__compiler__converted_55(void);
static FRAME_INFO frame__compiler__converted_55 = {7, {"i", "len", "code", "replacement", "arguments", "a", "level"}};
static void cont__compiler__converted_56(void);
static void cont__compiler__converted_57(void);
static NODE *func__compiler__converted_58;
static void entry__compiler__converted_58(void);
static FRAME_INFO frame__compiler__converted_58 = {7, {"break", "len", "i", "code", "level", "arguments", "a"}};
static NODE *func__compiler__converted_59;
static void entry__compiler__converted_59(void);
static FRAME_INFO frame__compiler__converted_59 = {7, {"len", "i", "code", "level", "arguments", "a", "break"}};
static void cont__compiler__converted_60(void);
static void cont__compiler__converted_61(void);
static NODE *func__compiler__converted_62;
static void entry__compiler__converted_62(void);
static FRAME_INFO frame__compiler__converted_62 = {6, {"code", "i", "level", "arguments", "a", "break"}};
static void cont__compiler__converted_63(void);
static NODE *func__compiler__converted_64;
static void entry__compiler__converted_64(void);
static FRAME_INFO frame__compiler__converted_64 = {5, {"level", "arguments", "code", "a", "i"}};
static void cont__compiler__converted_65(void);
static NODE *func__compiler__converted_66;
static void entry__compiler__converted_66(void);
static FRAME_INFO frame__compiler__converted_66 = {4, {"arguments", "code", "a", "i"}};
static void cont__compiler__converted_67(void);
static void cont__compiler__converted_68(void);
static void cont__compiler__converted_69(void);
static void cont__compiler__converted_70(void);
static void cont__compiler__converted_71(void);
static NODE *func__compiler__converted_72;
static void entry__compiler__converted_72(void);
static FRAME_INFO frame__compiler__converted_72 = {1, {"level"}};
static void cont__compiler__converted_73(void);
static NODE *func__compiler__converted_74;
static void entry__compiler__converted_74(void);
static FRAME_INFO frame__compiler__converted_74 = {6, {"level", "arguments", "code", "a", "i", "break"}};
static void cont__compiler__converted_75(void);
static void cont__compiler__converted_76(void);
static NODE *func__compiler__converted_77;
static void entry__compiler__converted_77(void);
static FRAME_INFO frame__compiler__converted_77 = {5, {"arguments", "code", "a", "i", "break"}};
static void cont__compiler__converted_78(void);
static void cont__compiler__converted_79(void);
static void cont__compiler__converted_80(void);
static void cont__compiler__converted_81(void);
static void cont__compiler__converted_82(void);
static void cont__compiler__converted_83(void);
static void cont__compiler__converted_84(void);
static void cont__compiler__converted_85(void);
static void cont__compiler__converted_86(void);
static void cont__compiler__converted_87(void);
static NODE *func__compiler__converted_88;
static void entry__compiler__converted_88(void);
static FRAME_INFO frame__compiler__converted_88 = {6, {"replacement", "arguments", "r", "j", "m", "new_replacement"}};
static void cont__compiler__converted_89(void);
static NODE *func__compiler__converted_90;
static void entry__compiler__converted_90(void);
static FRAME_INFO frame__compiler__converted_90 = {6, {"m", "j", "replacement", "new_replacement", "r", "arguments"}};
static void cont__compiler__converted_91(void);
static void cont__compiler__converted_92(void);
static NODE *func__compiler__converted_93;
static void entry__compiler__converted_93(void);
static FRAME_INFO frame__compiler__converted_93 = {5, {"replacement", "j", "new_replacement", "r", "arguments"}};
static void cont__compiler__converted_94(void);
static void cont__compiler__converted_95(void);
static NODE *func__compiler__converted_96;
static void entry__compiler__converted_96(void);
static FRAME_INFO frame__compiler__converted_96 = {6, {"new_replacement", "replacement", "r", "j", "arguments", "var_no"}};
static void cont__compiler__converted_97(void);
static void cont__compiler__converted_98(void);
static void cont__compiler__converted_99(void);
static void cont__compiler__converted_100(void);
static void cont__compiler__converted_101(void);
static void cont__compiler__converted_102(void);
static NODE *func__compiler__converted_103;
static void entry__compiler__converted_103(void);
static FRAME_INFO frame__compiler__converted_103 = {2, {"new_replacement", "arguments"}};
static NODE *string__2d7981f4e6682be5;
static void cont__compiler__converted_105(void);
static void cont__compiler__converted_106(void);
static NODE *func__compiler__converted_107;
static void entry__compiler__converted_107(void);
static FRAME_INFO frame__compiler__converted_107 = {4, {"var_no", "new_replacement", "arguments", "idx"}};
static void cont__compiler__converted_108(void);
static void cont__compiler__converted_109(void);
static void cont__compiler__converted_110(void);
static void cont__compiler__converted_111(void);
static void cont__compiler__converted_112(void);
static void cont__compiler__converted_113(void);
static void cont__compiler__converted_114(void);
static void cont__compiler__converted_115(void);
static void cont__compiler__converted_116(void);
static void cont__compiler__converted_117(void);
static void cont__compiler__converted_118(void);
static NODE *func__compiler__converted_119;
static void entry__compiler__converted_119(void);
static FRAME_INFO frame__compiler__converted_119 = {2, {"replacement", "arguments"}};
static void cont__compiler__converted_120(void);
static NODE *func__compiler__converted_121;
static void entry__compiler__converted_121(void);
static FRAME_INFO frame__compiler__converted_121 = {1, {"replacement"}};
static void cont__compiler__converted_122(void);
static NODE *func__compiler__converted_123;
static void entry__compiler__converted_123(void);
static FRAME_INFO frame__compiler__converted_123 = {1, {"replacement"}};
static void cont__compiler__converted_124(void);
static void cont__compiler__converted_125(void);
static void cont__compiler__converted_126(void);
static void cont__compiler__converted_127(void);
static NODE *func__compiler__converted_128;
static void entry__compiler__converted_128(void);
static FRAME_INFO frame__compiler__converted_128 = {6, {"identifier", "new_code", "code", "start", "s", "i"}};
static void cont__compiler__converted_129(void);
static NODE *func__compiler__converted_130;
static void entry__compiler__converted_130(void);
static FRAME_INFO frame__compiler__converted_130 = {6, {"identifier", "new_code", "code", "start", "s", "i"}};
static NODE *string__2d7981f4e6d82bff;
static NODE *string__2d7981f4e5f02b9a;
static void cont__compiler__converted_133(void);
static void cont__compiler__converted_134(void);
static void cont__compiler__converted_135(void);
static void cont__compiler__converted_136(void);
static void cont__compiler__converted_137(void);
static void cont__compiler__converted_138(void);
static void cont__compiler__converted_139(void);
static void cont__compiler__converted_140(void);
static NODE *func__compiler__converted_141;
static void entry__compiler__converted_141(void);
static FRAME_INFO frame__compiler__converted_141 = {0, {}};
static void cont__compiler__converted_142(void);
static void cont__compiler__converted_143(void);
static void cont__compiler__converted_144(void);
static void cont__compiler__converted_145(void);
static void cont__compiler__converted_146(void);
static NODE *func__compiler__converted_147;
static void entry__compiler__converted_147(void);
static FRAME_INFO frame__compiler__converted_147 = {3, {"new_code", "code", "start"}};
static void cont__compiler__converted_148(void);
static void cont__compiler__converted_149(void);
static void cont__compiler__converted_150(void);
static NODE *func__compiler__converted_151;
static void entry__compiler__converted_151(void);
static FRAME_INFO frame__compiler__converted_151 = {1, {"code"}};
static void cont__compiler__converted_152(void);
static void cont__compiler__converted_153(void);
static void cont__compiler__converted_154(void);
static NODE *get__compiler__converted(void) {
  return var.compiler__converted;
}
static NODE *string__400ae5cb5c587d7a;
static NODE *string__6c94222b8f3884e6;
static void cont__83_3(void);
static NODE *string__400ae5cb5c587d6f;
static NODE *string__6c94222b8f3884f3;
static void cont__84_3(void);
static NODE *string__1028a78005f60678;
static NODE *string__34f9178f4105813b;
static void cont__85_3(void);
static NODE *string__6b819d4408594055;
static NODE *string__a8d3ab331eb668e7;
static void cont__86_3(void);
static NODE *string__59cab089aecbe8a5;
static NODE *string__77b931a5baaa8bfc;
static void cont__87_3(void);
static NODE *string__77819b4408019052;
static NODE *string__b4d3ad331eeeb8e0;
static void cont__88_3(void);
static NODE *string__48483b12ea44e011;
static NODE *string__a7a3514a924a78fa;
static void cont__89_3(void);
static NODE *string__8f50c41d106226cf;
static NODE *string__dfd1ce1d312022e7;
static void cont__90_3(void);
static NODE *string__440ae28b5c107d6d;
static NODE *string__6c9a2bd2e7c4af5;
static void cont__91_3(void);
static NODE *string__8d88533a39505214;
static NODE *string__1bb6ef61f3edfaf2;
static void cont__92_3(void);
static NODE *string__8f7216a94bc80f3;
static NODE *string__fbe40d362af5bff1;
static void cont__93_3(void);
static NODE *string__88f7216a94ac80f6;
static NODE *string__91ccef706a22d072;
static void cont__94_3(void);
static NODE *string__940ced12ee123334;
static NODE *string__d48de512cf50371c;
static void cont__95_3(void);
static NODE *string__fa72dc15c216b9e;
static NODE *func__96_2;
static void entry__96_2(void);
static FRAME_INFO frame__96_2 = {2, {"arguments", "name"}};
static void cont__96_3(void);
static void cont__96_4(void);
static void cont__96_5(void);
static NODE *func__96_6;
static void entry__96_6(void);
static FRAME_INFO frame__96_6 = {1, {"name"}};
static void cont__96_7(void);
static NODE *func__96_8;
static void entry__96_8(void);
static FRAME_INFO frame__96_8 = {1, {"name"}};
static NODE *string__2e0ae90b5df07d17;
static void cont__96_10(void);
static NODE *func__96_11;
static void entry__96_11(void);
static FRAME_INFO frame__96_11 = {1, {"name"}};
static NODE *string__485aef83e8b97008;
static void cont__96_13(void);
static void cont__96_14(void);
static NODE *func__96_15;
static void entry__96_15(void);
static FRAME_INFO frame__96_15 = {1, {"name"}};
static NODE *string__405aee03eb306008;
static NODE *string__2d7981f4e6482bec;
static void cont__96_18(void);
static void cont__96_19(void);
static NODE *string__265ae243ebba4003;
static NODE *func__97_2;
static void entry__97_2(void);
static FRAME_INFO frame__97_2 = {1, {"arguments"}};
static void cont__97_3(void);
static NODE *string__314a5f4a93a00186;
static void cont__97_5(void);
static NODE *string__301f5c1000c06299;
static NODE *func__98_2;
static void entry__98_2(void);
static FRAME_INFO frame__98_2 = {1, {"arguments"}};
static void cont__98_3(void);
static void cont__98_4(void);
static NODE *string__500ae2cb5c507d76;
static NODE *func__99_2;
static void entry__99_2(void);
static FRAME_INFO frame__99_2 = {0, {}};
static void cont__99_3(void);
static NODE *string__4a0ae10b5cc07d78;
static NODE *func__100_2;
static void entry__100_2(void);
static FRAME_INFO frame__100_2 = {0, {}};
static void cont__100_3(void);
static NODE *func__100_4;
static void entry__100_4(void);
static FRAME_INFO frame__100_4 = {0, {}};
static NODE *string__b0ac9625f04ddbd3;
static NODE *string__fa730c15f616bf7;
static void cont__100_7(void);
static NODE *func__100_8;
static void entry__100_8(void);
static FRAME_INFO frame__100_8 = {0, {}};
static NODE *string__f9bb92aa6d4490dd;
static void cont__100_10(void);
static NODE *string__fa72a015c596b98;
static NODE *func__101_2;
static void entry__101_2(void);
static FRAME_INFO frame__101_2 = {2, {"arguments", "name"}};
static void cont__101_3(void);
static NODE *func__101_4;
static void entry__101_4(void);
static FRAME_INFO frame__101_4 = {2, {"arguments", "name"}};
static NODE *string__b8200c1595938088;
static void cont__101_6(void);
static void cont__101_7(void);
static void cont__101_8(void);
static NODE *func__101_9;
static void entry__101_9(void);
static FRAME_INFO frame__101_9 = {1, {"name"}};
static NODE *string__297be2f6f9dca12f;
static NODE *string__2d7981f4e6402bfe;
static void cont__101_12(void);
static NODE *func__101_13;
static void entry__101_13(void);
static FRAME_INFO frame__101_13 = {2, {"name", "arguments"}};
static void cont__101_14(void);
static NODE *string__4a1f57e083be52ff;
static NODE *string__820afe0b5f887d19;
static NODE *string__fd21e7555dafa46d;
static NODE *string__7ed0587dfc52436;
static NODE *string__c81f08526aea5316;
static NODE *string__eff8bde306d1997d;
static void cont__101_21(void);
static NODE *func__101_22;
static void entry__101_22(void);
static FRAME_INFO frame__101_22 = {1, {"arguments"}};
static void cont__101_23(void);
static void cont__101_24(void);
static void cont__101_25(void);
static NODE *string__5a0ae28b5c107d7e;
static NODE *func__102_2;
static void entry__102_2(void);
static FRAME_INFO frame__102_2 = {2, {"arguments", "name"}};
static void cont__102_3(void);
static NODE *func__102_4;
static void entry__102_4(void);
static FRAME_INFO frame__102_4 = {2, {"arguments", "name"}};
static NODE *string__40f9098a5d354178;
static void cont__102_6(void);
static void cont__102_7(void);
static void cont__102_8(void);
static NODE *func__102_9;
static void entry__102_9(void);
static FRAME_INFO frame__102_9 = {1, {"name"}};
static NODE *string__329e59a9af29a0d5;
static void cont__102_11(void);
static NODE *func__102_12;
static void entry__102_12(void);
static FRAME_INFO frame__102_12 = {2, {"name", "arguments"}};
static void cont__102_13(void);
static NODE *string__7b0520b55f9bd587;
static void cont__102_15(void);
static NODE *func__102_16;
static void entry__102_16(void);
static FRAME_INFO frame__102_16 = {1, {"arguments"}};
static void cont__102_17(void);
static void cont__102_18(void);
static void cont__102_19(void);
static NODE *string__eec400c5149050a8;
static NODE *func__103_2;
static void entry__103_2(void);
static FRAME_INFO frame__103_2 = {2, {"arguments", "name"}};
static void cont__103_3(void);
static NODE *func__103_4;
static void entry__103_4(void);
static FRAME_INFO frame__103_4 = {2, {"arguments", "name"}};
static NODE *string__ae4408d515925088;
static void cont__103_6(void);
static void cont__103_7(void);
static void cont__103_8(void);
static NODE *func__103_9;
static void entry__103_9(void);
static FRAME_INFO frame__103_9 = {1, {"name"}};
static NODE *string__f7fe2f879dc120f;
static void cont__103_11(void);
static NODE *func__103_12;
static void entry__103_12(void);
static FRAME_INFO frame__103_12 = {1, {"name"}};
static NODE *string__820af8cb5f507d19;
static NODE *string__1ee649de6e08afc4;
static NODE *string__ee1b085ceaeae036;
static void cont__103_16(void);
static NODE *func__103_17;
static void entry__103_17(void);
static FRAME_INFO frame__103_17 = {1, {"arguments"}};
static void cont__103_18(void);
static void cont__103_19(void);
static void cont__103_20(void);
static NODE *string__a602a332a09613c;
static NODE *func__104_2;
static void entry__104_2(void);
static FRAME_INFO frame__104_2 = {3, {"arguments", "name", "length"}};
static void cont__104_3(void);
static void cont__104_4(void);
static NODE *func__104_5;
static void entry__104_5(void);
static FRAME_INFO frame__104_5 = {3, {"arguments", "name", "length"}};
static NODE *string__4ae022330b0b651c;
static void cont__104_7(void);
static void cont__104_8(void);
static NODE *string__77c059895d31cd96;
static void cont__104_10(void);
static NODE *func__104_11;
static void entry__104_11(void);
static FRAME_INFO frame__104_11 = {1, {"arguments"}};
static void cont__104_12(void);
static void cont__104_13(void);
static void cont__104_14(void);
static NODE *string__21f5d960028028e;
static NODE *func__105_2;
static void entry__105_2(void);
static FRAME_INFO frame__105_2 = {3, {"arguments", "name", "length"}};
static void cont__105_3(void);
static void cont__105_4(void);
static NODE *func__105_5;
static void entry__105_5(void);
static FRAME_INFO frame__105_5 = {3, {"arguments", "name", "length"}};
static NODE *string__421f5586012a02ae;
static void cont__105_7(void);
static void cont__105_8(void);
static NODE *string__8030e06afcbf4f61;
static void cont__105_10(void);
static NODE *func__105_11;
static void entry__105_11(void);
static FRAME_INFO frame__105_11 = {1, {"arguments"}};
static void cont__105_12(void);
static void cont__105_13(void);
static void cont__105_14(void);
static NODE *string__a68a78f85a6d407;
static NODE *func__106_2;
static void entry__106_2(void);
static FRAME_INFO frame__106_2 = {2, {"arguments", "name"}};
static void cont__106_3(void);
static NODE *func__106_4;
static void entry__106_4(void);
static FRAME_INFO frame__106_4 = {2, {"arguments", "name"}};
static NODE *string__4a68af9f84a4d027;
static void cont__106_6(void);
static void cont__106_7(void);
static NODE *string__fabc9ed81001dd7;
static void cont__106_9(void);
static NODE *func__106_10;
static void entry__106_10(void);
static FRAME_INFO frame__106_10 = {1, {"arguments"}};
static void cont__106_11(void);
static void cont__106_12(void);
static void cont__106_13(void);
static NODE *string__fa729015c596b88;
static NODE *func__107_2;
static void entry__107_2(void);
static FRAME_INFO frame__107_2 = {3, {"retrieve_variables", "print_variables", "buf"}};
static NODE *func__107_3;
static void entry__107_3(void);
static FRAME_INFO frame__107_3 = {2, {"buf", "indent"}};
static void cont__107_4(void);
static NODE *func__107_5;
static void entry__107_5(void);
static FRAME_INFO frame__107_5 = {0, {}};
static NODE *string__d81f466083be52f7;
static NODE *func__107_7;
static void entry__107_7(void);
static FRAME_INFO frame__107_7 = {0, {}};
static NODE *string__2d7981f4e6082be5;
static void cont__107_9(void);
static NODE *func__107_10;
static void entry__107_10(void);
static FRAME_INFO frame__107_10 = {5, {"var", "buf", "indent", "type", "name"}};
static void cont__107_11(void);
static void cont__107_12(void);
static NODE *func__107_13;
static void entry__107_13(void);
static FRAME_INFO frame__107_13 = {3, {"buf", "indent", "name"}};
static NODE *string__3802f8268029fd6c;
static void cont__107_15(void);
static void cont__107_16(void);
static NODE *func__107_17;
static void entry__107_17(void);
static FRAME_INFO frame__107_17 = {4, {"buf", "indent", "var", "name"}};
static void cont__107_18(void);
static NODE *string__30c5044d97434308;
static void cont__107_20(void);
static void cont__107_21(void);
static NODE *func__107_22;
static void entry__107_22(void);
static FRAME_INFO frame__107_22 = {4, {"buf", "indent", "var", "name"}};
static void cont__107_23(void);
static NODE *string__4ff2866267e10016;
static void cont__107_25(void);
static void cont__107_26(void);
static NODE *func__107_27;
static void entry__107_27(void);
static FRAME_INFO frame__107_27 = {4, {"buf", "indent", "type", "name"}};
static NODE *string__192c815f22d3275e;
static NODE *string__2d7981f4e6482be3;
static void cont__107_30(void);
static void cont__107_31(void);
static NODE *func__107_32;
static void entry__107_32(void);
static FRAME_INFO frame__107_32 = {2, {"buf", "indent"}};
static void cont__107_33(void);
static NODE *func__107_34;
static void entry__107_34(void);
static FRAME_INFO frame__107_34 = {0, {}};
static NODE *func__107_35;
static void entry__107_35(void);
static FRAME_INFO frame__107_35 = {0, {}};
static void cont__107_36(void);
static NODE *func__107_37;
static void entry__107_37(void);
static FRAME_INFO frame__107_37 = {5, {"var", "buf", "indent", "type", "name"}};
static void cont__107_38(void);
static void cont__107_39(void);
static NODE *func__107_40;
static void entry__107_40(void);
static FRAME_INFO frame__107_40 = {3, {"buf", "indent", "name"}};
static NODE *string__32285b242638aa20;
static void cont__107_42(void);
static void cont__107_43(void);
static NODE *func__107_44;
static void entry__107_44(void);
static FRAME_INFO frame__107_44 = {4, {"buf", "indent", "name", "var"}};
static void cont__107_45(void);
static NODE *string__8eee524608dfba81;
static void cont__107_47(void);
static void cont__107_48(void);
static NODE *func__107_49;
static void entry__107_49(void);
static FRAME_INFO frame__107_49 = {4, {"buf", "indent", "name", "var"}};
static void cont__107_50(void);
static NODE *string__173507c00b84c49d;
static void cont__107_52(void);
static void cont__107_53(void);
static NODE *func__107_54;
static void entry__107_54(void);
static FRAME_INFO frame__107_54 = {4, {"buf", "indent", "type", "name"}};
static NODE *string__ae4408db944250a5;
static NODE *string__578a5af303e9cc9;
static void cont__107_57(void);
static void cont__107_58(void);
static NODE *func__107_59;
static void entry__107_59(void);
static FRAME_INFO frame__107_59 = {3, {"buf", "retrieve_variables", "print_variables"}};
static void cont__107_60(void);
static NODE *func__107_61;
static void entry__107_61(void);
static FRAME_INFO frame__107_61 = {3, {"buf", "retrieve_variables", "print_variables"}};
static NODE *string__887d942629156ee6;
static void cont__107_63(void);
static NODE *string__33d6d747fb30a3e4;
static NODE *string__860afb0b5fb87d33;
static void cont__107_66(void);
static void cont__107_67(void);
static void cont__107_68(void);
static void cont__107_69(void);
static NODE *func__107_70;
static void entry__107_70(void);
static FRAME_INFO frame__107_70 = {2, {"buf", "print_variables"}};
static NODE *string__f3d6bf47fb36a3e0;
static void cont__107_72(void);
static void cont__107_73(void);
static NODE *func__107_74;
static void entry__107_74(void);
static FRAME_INFO frame__107_74 = {3, {"buf", "retrieve_variables", "print_variables"}};
static void cont__107_75(void);
static void cont__107_76(void);
static NODE *func__107_77;
static void entry__107_77(void);
static FRAME_INFO frame__107_77 = {7, {"buf", "retrieve_variables", "print_variables", "var", "type", "name", "default"}};
static NODE *string__47540a9adb64843c;
static void cont__107_79(void);
static NODE *string__3f8698e0b2f30ecd;
static NODE *string__ca1f46618166c2dd;
static void cont__107_82(void);
static void cont__107_83(void);
static void cont__107_84(void);
static NODE *string__12661159642bb65a;
static void cont__107_86(void);
static void cont__107_87(void);
static void cont__107_88(void);
static void cont__107_89(void);
static void cont__107_90(void);
static NODE *func__107_91;
static void entry__107_91(void);
static FRAME_INFO frame__107_91 = {1, {"var"}};
static void cont__107_92(void);
static NODE *func__107_93;
static void entry__107_93(void);
static FRAME_INFO frame__107_93 = {0, {}};
static NODE *string__c440cd65102e84e8;
static void cont__107_95(void);
static NODE *string__fa730415fc16bec;
static NODE *string__d81f466d0154f2dd;
static void cont__107_98(void);
static void cont__107_99(void);
static void cont__107_100(void);
static NODE *func__107_101;
static void entry__107_101(void);
static FRAME_INFO frame__107_101 = {2, {"buf", "print_variables"}};
static NODE *string__4fbb5986ed8ccf7;
static void cont__107_103(void);
static void cont__107_104(void);
static void cont__107_105(void);
static void cont__107_106(void);
static void cont__107_107(void);
static NODE *string__3c202d3e36291121;
static NODE *string__7ca0252e172b1501;
static void cont__108_3(void);
static NODE *string__760ae00b5cf07d76;
static NODE *string__360ae80b5df07d56;
static void cont__109_3(void);
static NODE *string__6a0ae5cb5cc87d7c;
static NODE *string__62d904ca56abf62f;
static void cont__110_3(void);
static NODE *string__85ae003eb527012;
static NODE *string__52b31fb1ca36ad;
static void cont__111_3(void);
static NODE *string__ae20f214ef3d4185;
static NODE *string__ee21fa04ce7f45ad;
static void cont__112_3(void);
static NODE *string__242c2d3622a1a2b6;
static NODE *string__bdf1fe7d3fa3f48e;
static void cont__113_3(void);
static NODE *string__6a0ae70b5ce07d7c;
static NODE *string__10f0a21e06f5c291;
static void cont__114_3(void);
static NODE *string__381f5f1a80c1c291;
static NODE *string__1c42567d62ae9fc4;
static void cont__115_3(void);
static NODE *string__2c1f5f1900c0c291;
static NODE *string__c207e6e98f96cbad;
static void cont__116_3(void);
static NODE *string__88b83a651b4554fc;
static NODE *string__e713ee46cfe40ca0;
static void cont__117_3(void);
static NODE *string__75924e59eefc3c27;
static NODE *string__c9e5fa593f26b652;
static void cont__118_3(void);
static NODE *string__808839651b3ce4f5;
static NODE *string__76174d28d266419;
static void cont__119_3(void);
static NODE *string__df153d64b7266922;
static NODE *string__a89eeef2e6ec47d6;
static void cont__120_3(void);
static NODE *string__681415cc9aa25dc9;
static NODE *string__62013454820fcbb4;
static void cont__121_3(void);
static NODE *string__8864d352eefa60e5;
static NODE *string__e7e98d9fbc185a2b;
static void cont__122_3(void);
static NODE *string__7414100c9a9a5dc3;
static NODE *string__d0d6524fe2f4619c;
static void cont__123_3(void);
static NODE *string__4388537a39721213;
static NODE *string__85e7f27c75b002fc;
static void cont__124_3(void);
static NODE *string__301f5b1980280299;
static NODE *string__f4e01cf5f7a8d221;
static void cont__125_3(void);
static NODE *string__1a5ae343eb822019;
static NODE *string__ab6aca91eb0633a9;
static void cont__126_3(void);
static NODE *string__690816604df6099f;
static NODE *string__7a5a4cdb9d9e0e09;
static void cont__127_3(void);
static NODE *string__adfe76f306663a82;
static NODE *string__55fab4fde7164944;
static void cont__128_3(void);
static NODE *string__26ff7f9f9c5c0312;
static NODE *string__7317d013e72f1e80;
static void cont__129_3(void);
static NODE *string__fce3f40028924a51;
static NODE *string__64a4d424679d8650;
static void cont__130_3(void);
static NODE *string__aab70cfc8956db67;
static NODE *string__e8cfae9434301166;
static void cont__131_3(void);
static NODE *string__6cf0c8742a12ca30;
static NODE *string__65e49414af94386a;
static void cont__132_3(void);
static NODE *string__1adfaddd8e34edf5;
static NODE *string__e77c83ca19b4e164;
static void cont__133_3(void);
static NODE *string__e858bf99576dbe16;
static NODE *string__26323596c3854c8e;
static void cont__134_3(void);
static NODE *string__cad5afdc0874a104;
static NODE *string__245ca532f1b1e064;
static void cont__135_3(void);
static NODE *string__aa786f40ccc234b9;
static NODE *string__b633324328a52c38;
static void cont__136_3(void);
static NODE *string__37ce8a8da4c412d5;
static NODE *string__b69de9e24cd9d6a2;
static void cont__137_3(void);
static NODE *string__221e44965d54351b;
static NODE *string__13951d152a225118;
static void cont__138_3(void);
static NODE *string__e4ae97e99176a5b2;
static NODE *string__413ff844cdfe78b6;
static void cont__139_3(void);
static NODE *string__3c9404ad0742476f;
static NODE *string__6a3612ac9bfecfbc;
static void cont__140_3(void);
static NODE *string__a28a14985afc552;
static NODE *string__1f25251097233e14;
static void cont__141_3(void);
void run__macros(void);

static CONTINUATION_INFO continuation_info[] = {
  {run__macros, NULL, 43, 43, 1, 31},
  {cont__83_3, NULL, 44, 44, 1, 31},
  {cont__84_3, NULL, 45, 45, 1, 38},
  {cont__85_3, NULL, 46, 46, 1, 54},
  {cont__86_3, NULL, 47, 47, 1, 78},
  {cont__87_3, NULL, 48, 48, 1, 54},
  {cont__88_3, NULL, 49, 49, 1, 47},
  {cont__89_3, NULL, 50, 50, 1, 46},
  {cont__90_3, NULL, 51, 51, 1, 33},
  {cont__91_3, NULL, 52, 56, 1, 4},
  {cont__92_3, NULL, 57, 61, 1, 4},
  {cont__93_3, NULL, 62, 66, 1, 4},
  {cont__94_3, NULL, 67, 67, 1, 42},
  {cont__95_3, NULL, 68, 73, 1, 24},
  {cont__96_19, NULL, 74, 77, 1, 39},
  {cont__97_5, NULL, 78, 81, 1, 39},
  {cont__98_4, NULL, 82, 84, 1, 7},
  {cont__99_3, NULL, 85, 93, 1, 44},
  {cont__100_10, NULL, 94, 110, 1, 13},
  {cont__101_25, NULL, 111, 127, 1, 13},
  {cont__102_19, NULL, 128, 144, 1, 13},
  {cont__103_20, NULL, 145, 155, 1, 13},
  {cont__104_14, NULL, 156, 166, 1, 13},
  {cont__105_14, NULL, 167, 176, 1, 13},
  {cont__106_13, NULL, 177, 255, 1, 8},
  {cont__107_107, NULL, 256, 256, 1, 36},
  {cont__108_3, NULL, 257, 257, 1, 26},
  {cont__109_3, NULL, 258, 258, 1, 34},
  {cont__110_3, NULL, 259, 259, 1, 36},
  {cont__111_3, NULL, 260, 260, 1, 42},
  {cont__112_3, NULL, 261, 261, 1, 47},
  {cont__113_3, NULL, 262, 262, 1, 30},
  {cont__114_3, NULL, 263, 263, 1, 34},
  {cont__115_3, NULL, 264, 264, 1, 54},
  {cont__116_3, NULL, 265, 271, 1, 4},
  {cont__117_3, NULL, 272, 281, 1, 4},
  {cont__118_3, NULL, 282, 282, 1, 67},
  {cont__119_3, NULL, 283, 291, 1, 4},
  {cont__120_3, NULL, 292, 300, 1, 4},
  {cont__121_3, NULL, 301, 309, 1, 4},
  {cont__122_3, NULL, 310, 318, 1, 4},
  {cont__123_3, NULL, 319, 321, 1, 22},
  {cont__124_3, NULL, 322, 327, 1, 4},
  {cont__125_3, NULL, 328, 332, 1, 4},
  {cont__126_3, NULL, 336, 336, 1, 61},
  {cont__127_3, NULL, 337, 337, 1, 59},
  {cont__128_3, NULL, 341, 344, 1, 4},
  {cont__129_3, NULL, 345, 348, 1, 4},
  {cont__130_3, NULL, 349, 352, 1, 4},
  {cont__131_3, NULL, 353, 356, 1, 4},
  {cont__132_3, NULL, 357, 360, 1, 4},
  {cont__133_3, NULL, 361, 364, 1, 4},
  {cont__134_3, NULL, 365, 368, 1, 4},
  {cont__135_3, NULL, 369, 372, 1, 4},
  {cont__136_3, NULL, 373, 376, 1, 4},
  {cont__137_3, NULL, 377, 380, 1, 4},
  {cont__138_3, NULL, 381, 384, 1, 4},
  {cont__139_3, NULL, 385, 388, 1, 4},
  {cont__140_3, NULL, 389, 392, 1, 4},
  {cont__141_3, NULL, },
  {entry__define_macro_1, NULL, 41, 41, 35, 59},
  {cont__define_macro_2, &frame__define_macro_1, 41, 41, 71, 71},
  {entry__compiler__converted_15, NULL, 409, 409, 72, 72},
  {entry__compiler__converted_10, NULL, 409, 409, 40, 42},
  {cont__compiler__converted_11, &frame__compiler__converted_10, 409, 409, 35, 43},
  {cont__compiler__converted_12, &frame__compiler__converted_10, 409, 409, 35, 50},
  {cont__compiler__converted_13, &frame__compiler__converted_10, 409, 409, 35, 50},
  {cont__compiler__converted_14, &frame__compiler__converted_10, 409, 409, 32, 72},
  {entry__compiler__converted_8, NULL, 409, 409, 14, 20},
  {cont__compiler__converted_9, &frame__compiler__converted_8, 409, 409, 9, 72},
  {cont__compiler__converted_16, &frame__compiler__converted_8, 410, 410, 9, 14},
  {cont__compiler__converted_17, &frame__compiler__converted_8, 410, 410, 14, 14},
  {entry__compiler__converted_25, NULL, 416, 416, 37, 37},
  {entry__compiler__converted_23, NULL, 416, 416, 20, 31},
  {cont__compiler__converted_24, &frame__compiler__converted_23, 416, 416, 13, 37},
  {entry__compiler__converted_32, NULL, 421, 421, 52, 52},
  {entry__compiler__converted_27, NULL, 421, 421, 21, 23},
  {cont__compiler__converted_28, &frame__compiler__converted_27, 421, 421, 16, 24},
  {cont__compiler__converted_29, &frame__compiler__converted_27, 421, 421, 16, 31},
  {cont__compiler__converted_30, &frame__compiler__converted_27, 421, 421, 16, 31},
  {cont__compiler__converted_31, &frame__compiler__converted_27, 421, 421, 13, 52},
  {entry__compiler__converted_37, NULL, 425, 425, 36, 38},
  {cont__compiler__converted_38, &frame__compiler__converted_37, 425, 425, 31, 39},
  {cont__compiler__converted_39, &frame__compiler__converted_37, 425, 425, 31, 46},
  {cont__compiler__converted_40, &frame__compiler__converted_37, 425, 425, 31, 46},
  {entry__compiler__converted_42, NULL, 426, 426, 19, 24},
  {cont__compiler__converted_43, &frame__compiler__converted_42, 426, 426, 24, 24},
  {entry__compiler__converted_66, NULL, 445, 445, 71, 73},
  {cont__compiler__converted_67, &frame__compiler__converted_66, 445, 445, 58, 74},
  {cont__compiler__converted_68, &frame__compiler__converted_66, 445, 445, 53, 75},
  {cont__compiler__converted_69, &frame__compiler__converted_66, 445, 445, 37, 75},
  {cont__compiler__converted_70, &frame__compiler__converted_66, 446, 446, 37, 42},
  {cont__compiler__converted_71, &frame__compiler__converted_66, 446, 446, 42, 42},
  {entry__compiler__converted_64, NULL, 444, 444, 38, 47},
  {cont__compiler__converted_65, &frame__compiler__converted_64, 444, 446, 35, 42},
  {entry__compiler__converted_72, NULL, 448, 448, 35, 44},
  {cont__compiler__converted_73, &frame__compiler__converted_72, 448, 448, 44, 44},
  {entry__compiler__converted_77, NULL, 452, 452, 71, 73},
  {cont__compiler__converted_78, &frame__compiler__converted_77, 452, 452, 58, 74},
  {cont__compiler__converted_79, &frame__compiler__converted_77, 452, 452, 53, 75},
  {cont__compiler__converted_80, &frame__compiler__converted_77, 452, 452, 37, 75},
  {cont__compiler__converted_81, &frame__compiler__converted_77, 453, 453, 37, 42},
  {cont__compiler__converted_82, &frame__compiler__converted_77, 454, 454, 37, 41},
  {entry__compiler__converted_74, NULL, 450, 450, 35, 44},
  {cont__compiler__converted_75, &frame__compiler__converted_74, 451, 451, 38, 47},
  {cont__compiler__converted_76, &frame__compiler__converted_74, 451, 454, 35, 41},
  {entry__compiler__converted_62, NULL, 442, 442, 33, 39},
  {cont__compiler__converted_63, &frame__compiler__converted_62, 441, 454, 31, 43},
  {cont__compiler__converted_83, &frame__compiler__converted_62, 455, 455, 31, 36},
  {cont__compiler__converted_84, &frame__compiler__converted_62, 455, 455, 36, 36},
  {entry__compiler__converted_59, NULL, 440, 440, 38, 45},
  {cont__compiler__converted_60, &frame__compiler__converted_59, 440, 440, 38, 45},
  {cont__compiler__converted_61, &frame__compiler__converted_59, 440, 455, 35, 36},
  {entry__compiler__converted_58, NULL, 440, 455, 29, 36},
  {cont__compiler__converted_85, &frame__compiler__converted_58, 455, 455, 36, 36},
  {entry__compiler__converted_103, NULL, 473, 473, 41, 60},
  {cont__compiler__converted_105, &frame__compiler__converted_103, 471, 473, 39, 60},
  {cont__compiler__converted_106, &frame__compiler__converted_103, 473, 473, 61, 61},
  {entry__compiler__converted_107, NULL, 475, 475, 39, 53},
  {cont__compiler__converted_108, &frame__compiler__converted_107, 476, 476, 63, 76},
  {cont__compiler__converted_109, &frame__compiler__converted_107, 476, 476, 39, 76},
  {cont__compiler__converted_110, &frame__compiler__converted_107, 476, 476, 76, 76},
  {entry__compiler__converted_96, NULL, 466, 466, 57, 59},
  {cont__compiler__converted_97, &frame__compiler__converted_96, 466, 466, 37, 60},
  {cont__compiler__converted_98, &frame__compiler__converted_96, 464, 466, 35, 60},
  {cont__compiler__converted_99, &frame__compiler__converted_96, 467, 467, 35, 40},
  {cont__compiler__converted_100, &frame__compiler__converted_96, 468, 468, 35, 56},
  {cont__compiler__converted_101, &frame__compiler__converted_96, 470, 470, 37, 49},
  {cont__compiler__converted_102, &frame__compiler__converted_96, 469, 476, 35, 77},
  {cont__compiler__converted_111, &frame__compiler__converted_96, 477, 477, 35, 40},
  {cont__compiler__converted_112, &frame__compiler__converted_96, 477, 477, 40, 40},
  {entry__compiler__converted_93, NULL, 463, 463, 36, 49},
  {cont__compiler__converted_94, &frame__compiler__converted_93, 463, 463, 36, 56},
  {cont__compiler__converted_95, &frame__compiler__converted_93, 463, 477, 33, 40},
  {cont__compiler__converted_113, &frame__compiler__converted_93, 478, 478, 33, 38},
  {cont__compiler__converted_114, &frame__compiler__converted_93, 478, 478, 38, 38},
  {entry__compiler__converted_90, NULL, 462, 462, 40, 45},
  {cont__compiler__converted_91, &frame__compiler__converted_90, 462, 462, 40, 45},
  {cont__compiler__converted_92, &frame__compiler__converted_90, 462, 478, 37, 38},
  {entry__compiler__converted_88, NULL, 460, 460, 31, 55},
  {cont__compiler__converted_89, &frame__compiler__converted_88, 462, 478, 31, 38},
  {cont__compiler__converted_115, &frame__compiler__converted_88, 480, 480, 77, 77},
  {cont__compiler__converted_116, &frame__compiler__converted_88, 480, 480, 56, 78},
  {cont__compiler__converted_117, &frame__compiler__converted_88, 479, 480, 31, 79},
  {cont__compiler__converted_118, &frame__compiler__converted_88, 480, 480, 80, 80},
  {entry__compiler__converted_119, NULL, 482, 482, 31, 65},
  {cont__compiler__converted_120, &frame__compiler__converted_119, 482, 482, 65, 65},
  {entry__compiler__converted_55, NULL, 435, 435, 27, 44},
  {cont__compiler__converted_56, &frame__compiler__converted_55, 436, 436, 27, 32},
  {cont__compiler__converted_57, &frame__compiler__converted_55, 439, 455, 27, 37},
  {cont__compiler__converted_86, &frame__compiler__converted_55, 457, 457, 29, 51},
  {cont__compiler__converted_87, &frame__compiler__converted_55, 456, 482, 27, 66},
  {entry__compiler__converted_123, NULL, 485, 485, 29, 54},
  {cont__compiler__converted_124, &frame__compiler__converted_123, 485, 485, 54, 54},
  {entry__compiler__converted_121, NULL, 484, 484, 34, 56},
  {cont__compiler__converted_122, &frame__compiler__converted_121, 484, 485, 27, 54},
  {entry__compiler__converted_49, NULL, 432, 432, 57, 59},
  {cont__compiler__converted_50, &frame__compiler__converted_49, 432, 432, 40, 60},
  {cont__compiler__converted_51, &frame__compiler__converted_49, 432, 432, 23, 60},
  {cont__compiler__converted_52, &frame__compiler__converted_49, 434, 434, 25, 31},
  {cont__compiler__converted_53, &frame__compiler__converted_49, 434, 434, 25, 38},
  {cont__compiler__converted_54, &frame__compiler__converted_49, 433, 485, 23, 56},
  {cont__compiler__converted_125, &frame__compiler__converted_49, 486, 486, 40, 60},
  {cont__compiler__converted_126, &frame__compiler__converted_49, 486, 486, 23, 60},
  {cont__compiler__converted_127, &frame__compiler__converted_49, 487, 487, 30, 30},
  {entry__compiler__converted_130, NULL, 490, 490, 49, 59},
  {cont__compiler__converted_133, &frame__compiler__converted_130, 490, 490, 25, 59},
  {cont__compiler__converted_134, &frame__compiler__converted_130, 491, 491, 59, 61},
  {cont__compiler__converted_135, &frame__compiler__converted_130, 491, 491, 42, 62},
  {cont__compiler__converted_136, &frame__compiler__converted_130, 491, 491, 25, 62},
  {cont__compiler__converted_137, &frame__compiler__converted_130, 492, 492, 25, 51},
  {cont__compiler__converted_138, &frame__compiler__converted_130, 493, 493, 32, 32},
  {entry__compiler__converted_128, NULL, 489, 489, 26, 50},
  {cont__compiler__converted_129, &frame__compiler__converted_128, 489, 493, 23, 32},
  {cont__compiler__converted_139, &frame__compiler__converted_128, 494, 494, 23, 47},
  {entry__compiler__converted_44, NULL, 428, 428, 45, 47},
  {cont__compiler__converted_45, &frame__compiler__converted_44, 428, 428, 19, 48},
  {cont__compiler__converted_46, &frame__compiler__converted_44, 429, 429, 19, 62},
  {cont__compiler__converted_47, &frame__compiler__converted_44, 431, 431, 21, 42},
  {cont__compiler__converted_48, &frame__compiler__converted_44, 430, 494, 19, 48},
  {cont__compiler__converted_140, &frame__compiler__converted_44, 495, 495, 30, 30},
  {entry__compiler__converted_35, NULL, 425, 425, 17, 26},
  {cont__compiler__converted_36, &frame__compiler__converted_35, 425, 425, 17, 46},
  {cont__compiler__converted_41, &frame__compiler__converted_35, 424, 495, 15, 31},
  {entry__compiler__converted_33, NULL, 423, 423, 16, 27},
  {cont__compiler__converted_34, &frame__compiler__converted_33, 423, 495, 13, 32},
  {entry__compiler__converted_141, NULL, 418, 418, 13, 16},
  {entry__compiler__converted_18, NULL, 412, 412, 9, 20},
  {cont__compiler__converted_19, &frame__compiler__converted_18, 415, 415, 16, 25},
  {cont__compiler__converted_20, &frame__compiler__converted_18, 415, 415, 28, 37},
  {cont__compiler__converted_21, &frame__compiler__converted_18, 415, 415, 11, 37},
  {cont__compiler__converted_22, &frame__compiler__converted_18, 417, 417, 11, 20},
  {cont__compiler__converted_26, &frame__compiler__converted_18, 413, 495, 9, 34},
  {cont__compiler__converted_142, &frame__compiler__converted_18, 496, 496, 9, 14},
  {cont__compiler__converted_143, &frame__compiler__converted_18, 496, 496, 14, 14},
  {entry__compiler__converted_7, NULL, 407, 496, 5, 15},
  {entry__compiler__converted_4, NULL, 406, 406, 12, 19},
  {cont__compiler__converted_5, &frame__compiler__converted_4, 406, 406, 12, 19},
  {cont__compiler__converted_6, &frame__compiler__converted_4, 406, 496, 9, 16},
  {entry__compiler__converted_147, NULL, 499, 499, 42, 42},
  {cont__compiler__converted_148, &frame__compiler__converted_147, 499, 499, 24, 43},
  {cont__compiler__converted_149, &frame__compiler__converted_147, 499, 499, 8, 44},
  {cont__compiler__converted_150, &frame__compiler__converted_147, 499, 499, 5, 44},
  {entry__compiler__converted_151, NULL, 500, 500, 22, 22},
  {cont__compiler__converted_152, &frame__compiler__converted_151, 500, 500, 8, 23},
  {cont__compiler__converted_153, &frame__compiler__converted_151, 500, 500, 5, 23},
  {entry__compiler__converted_1, NULL, 399, 399, 3, 34},
  {cont__compiler__converted_2, &frame__compiler__converted_1, 405, 405, 3, 22},
  {cont__compiler__converted_3, &frame__compiler__converted_1, 406, 496, 3, 16},
  {cont__compiler__converted_144, &frame__compiler__converted_1, 498, 498, 5, 18},
  {cont__compiler__converted_145, &frame__compiler__converted_1, 498, 498, 5, 18},
  {cont__compiler__converted_146, &frame__compiler__converted_1, 497, 500, 3, 23},
  {cont__compiler__converted_154, &frame__compiler__converted_1, 500, 500, 23, 23},
  {entry__96_8, NULL, 72, 72, 36, 48},
  {cont__96_10, &frame__96_8, 72, 72, 33, 48},
  {entry__96_11, NULL, 72, 72, 54, 67},
  {cont__96_13, &frame__96_11, 72, 72, 51, 67},
  {entry__96_6, NULL, 72, 72, 11, 30},
  {cont__96_7, &frame__96_6, 72, 72, 8, 68},
  {cont__96_14, &frame__96_6, 72, 72, 5, 68},
  {entry__96_15, NULL, 73, 73, 8, 23},
  {cont__96_18, &frame__96_15, 73, 73, 5, 23},
  {entry__96_2, NULL, 69, 69, 3, 20},
  {cont__96_3, &frame__96_2, 71, 71, 5, 22},
  {cont__96_4, &frame__96_2, 71, 71, 5, 33},
  {cont__96_5, &frame__96_2, 70, 73, 3, 23},
  {entry__97_2, NULL, 75, 75, 3, 26},
  {cont__97_3, &frame__97_2, 77, 77, 3, 39},
  {entry__98_2, NULL, 79, 79, 3, 26},
  {cont__98_3, &frame__98_2, 81, 81, 3, 39},
  {entry__99_2, NULL, 84, 84, 3, 7},
  {entry__100_4, NULL, 89, 92, 8, 51},
  {cont__100_7, &frame__100_4, 89, 92, 5, 51},
  {entry__100_8, NULL, 93, 93, 5, 43},
  {entry__100_2, NULL, 88, 88, 5, 23},
  {cont__100_3, &frame__100_2, 87, 93, 3, 43},
  {entry__101_9, NULL, 100, 100, 34, 61},
  {cont__101_12, &frame__101_9, 100, 100, 31, 61},
  {entry__101_13, NULL, 102, 102, 30, 41},
  {cont__101_14, &frame__101_13, 100, 107, 67, 18},
  {cont__101_21, &frame__101_13, 100, 107, 64, 18},
  {entry__101_4, NULL, 99, 99, 28, 51},
  {cont__101_6, &frame__101_4, 99, 99, 7, 51},
  {cont__101_7, &frame__101_4, 100, 100, 10, 28},
  {cont__101_8, &frame__101_4, 100, 107, 7, 18},
  {entry__101_22, NULL, 109, 109, 28, 51},
  {cont__101_23, &frame__101_22, 109, 109, 7, 51},
  {cont__101_24, &frame__101_22, 110, 110, 7, 11},
  {entry__101_2, NULL, 95, 95, 3, 20},
  {cont__101_3, &frame__101_2, 96, 110, 3, 12},
  {entry__102_9, NULL, 117, 117, 34, 66},
  {cont__102_11, &frame__102_9, 117, 117, 31, 66},
  {entry__102_12, NULL, 119, 119, 30, 41},
  {cont__102_13, &frame__102_12, 117, 124, 72, 18},
  {cont__102_15, &frame__102_12, 117, 124, 69, 18},
  {entry__102_4, NULL, 116, 116, 28, 56},
  {cont__102_6, &frame__102_4, 116, 116, 7, 56},
  {cont__102_7, &frame__102_4, 117, 117, 10, 28},
  {cont__102_8, &frame__102_4, 117, 124, 7, 18},
  {entry__102_16, NULL, 126, 126, 28, 56},
  {cont__102_17, &frame__102_16, 126, 126, 7, 56},
  {cont__102_18, &frame__102_16, 127, 127, 7, 11},
  {entry__102_2, NULL, 112, 112, 3, 20},
  {cont__102_3, &frame__102_2, 113, 127, 3, 12},
  {entry__103_9, NULL, 134, 134, 34, 61},
  {cont__103_11, &frame__103_9, 134, 134, 31, 61},
  {entry__103_12, NULL, 134, 141, 67, 18},
  {cont__103_16, &frame__103_12, 134, 141, 64, 18},
  {entry__103_4, NULL, 133, 133, 28, 51},
  {cont__103_6, &frame__103_4, 133, 133, 7, 51},
  {cont__103_7, &frame__103_4, 134, 134, 10, 28},
  {cont__103_8, &frame__103_4, 134, 141, 7, 18},
  {entry__103_17, NULL, 143, 143, 28, 51},
  {cont__103_18, &frame__103_17, 143, 143, 7, 51},
  {cont__103_19, &frame__103_17, 144, 144, 7, 11},
  {entry__103_2, NULL, 129, 129, 3, 20},
  {cont__103_3, &frame__103_2, 130, 144, 3, 12},
  {entry__104_5, NULL, 151, 151, 28, 53},
  {cont__104_7, &frame__104_5, 151, 151, 7, 53},
  {cont__104_8, &frame__104_5, 152, 152, 10, 50},
  {cont__104_10, &frame__104_5, 152, 152, 7, 50},
  {entry__104_11, NULL, 154, 154, 28, 53},
  {cont__104_12, &frame__104_11, 154, 154, 7, 53},
  {cont__104_13, &frame__104_11, 155, 155, 7, 11},
  {entry__104_2, NULL, 146, 146, 3, 20},
  {cont__104_3, &frame__104_2, 147, 147, 3, 22},
  {cont__104_4, &frame__104_2, 148, 155, 3, 12},
  {entry__105_5, NULL, 162, 162, 28, 50},
  {cont__105_7, &frame__105_5, 162, 162, 7, 50},
  {cont__105_8, &frame__105_5, 163, 163, 10, 47},
  {cont__105_10, &frame__105_5, 163, 163, 7, 47},
  {entry__105_11, NULL, 165, 165, 28, 50},
  {cont__105_12, &frame__105_11, 165, 165, 7, 50},
  {cont__105_13, &frame__105_11, 166, 166, 7, 11},
  {entry__105_2, NULL, 157, 157, 3, 20},
  {cont__105_3, &frame__105_2, 158, 158, 3, 22},
  {cont__105_4, &frame__105_2, 159, 166, 3, 12},
  {entry__106_4, NULL, 172, 172, 28, 52},
  {cont__106_6, &frame__106_4, 172, 172, 7, 52},
  {cont__106_7, &frame__106_4, 173, 173, 10, 38},
  {cont__106_9, &frame__106_4, 173, 173, 7, 38},
  {entry__106_10, NULL, 175, 175, 28, 52},
  {cont__106_11, &frame__106_10, 175, 175, 7, 52},
  {cont__106_12, &frame__106_10, 176, 176, 7, 11},
  {entry__106_2, NULL, 168, 168, 3, 20},
  {cont__106_3, &frame__106_2, 169, 176, 3, 12},
  {entry__107_5, NULL, 179, 179, 38, 48},
  {entry__107_7, NULL, 179, 179, 51, 57},
  {entry__107_13, NULL, 186, 186, 34, 72},
  {cont__107_15, &frame__107_13, 186, 186, 11, 72},
  {cont__107_16, &frame__107_13, 186, 186, 72, 72},
  {entry__107_17, NULL, 191, 191, 16, 21},
  {cont__107_18, &frame__107_17, 191, 191, 13, 64},
  {cont__107_20, &frame__107_17, 188, 191, 11, 64},
  {cont__107_21, &frame__107_17, 191, 191, 65, 65},
  {entry__107_22, NULL, 196, 196, 16, 21},
  {cont__107_23, &frame__107_22, 196, 196, 13, 65},
  {cont__107_25, &frame__107_22, 193, 196, 11, 65},
  {cont__107_26, &frame__107_22, 196, 196, 66, 66},
  {entry__107_27, NULL, 198, 198, 34, 63},
  {cont__107_30, &frame__107_27, 198, 198, 11, 63},
  {cont__107_31, &frame__107_27, 198, 198, 63, 63},
  {entry__107_10, NULL, 181, 181, 7, 18},
  {cont__107_11, &frame__107_10, 182, 182, 7, 18},
  {cont__107_12, &frame__107_10, 183, 198, 7, 64},
  {entry__107_3, NULL, 179, 179, 16, 35},
  {cont__107_4, &frame__107_3, 179, 179, 5, 58},
  {cont__107_9, &frame__107_3, 180, 198, 5, 65},
  {entry__107_34, NULL, 201, 201, 38, 48},
  {entry__107_35, NULL, 201, 201, 51, 57},
  {entry__107_40, NULL, 208, 208, 34, 59},
  {cont__107_42, &frame__107_40, 208, 208, 11, 59},
  {cont__107_43, &frame__107_40, 208, 208, 59, 59},
  {entry__107_44, NULL, 210, 210, 63, 68},
  {cont__107_45, &frame__107_44, 210, 210, 34, 72},
  {cont__107_47, &frame__107_44, 210, 210, 11, 72},
  {cont__107_48, &frame__107_44, 210, 210, 72, 72},
  {entry__107_49, NULL, 212, 212, 60, 65},
  {cont__107_50, &frame__107_49, 212, 212, 34, 69},
  {cont__107_52, &frame__107_49, 212, 212, 11, 69},
  {cont__107_53, &frame__107_49, 212, 212, 69, 69},
  {entry__107_54, NULL, 214, 214, 34, 59},
  {cont__107_57, &frame__107_54, 214, 214, 11, 59},
  {cont__107_58, &frame__107_54, 214, 214, 59, 59},
  {entry__107_37, NULL, 203, 203, 7, 18},
  {cont__107_38, &frame__107_37, 204, 204, 7, 18},
  {cont__107_39, &frame__107_37, 205, 214, 7, 60},
  {entry__107_32, NULL, 201, 201, 16, 35},
  {cont__107_33, &frame__107_32, 201, 201, 5, 58},
  {cont__107_36, &frame__107_32, 202, 214, 5, 61},
  {entry__107_70, NULL, 227, 229, 23, 45},
  {cont__107_72, &frame__107_70, 227, 229, 9, 45},
  {cont__107_73, &frame__107_70, 230, 230, 9, 23},
  {entry__107_61, NULL, 219, 221, 7, 16},
  {cont__107_63, &frame__107_61, 222, 224, 21, 43},
  {cont__107_66, &frame__107_61, 222, 224, 7, 43},
  {cont__107_67, &frame__107_61, 225, 225, 7, 24},
  {cont__107_68, &frame__107_61, 226, 226, 14, 36},
  {cont__107_69, &frame__107_61, 226, 230, 7, 23},
  {entry__107_59, NULL, 218, 218, 8, 26},
  {cont__107_60, &frame__107_59, 218, 230, 5, 24},
  {entry__107_91, NULL, 244, 244, 62, 67},
  {cont__107_92, &frame__107_91, 244, 244, 59, 67},
  {entry__107_93, NULL, 244, 244, 38, 56},
  {entry__107_101, NULL, 250, 252, 23, 49},
  {cont__107_103, &frame__107_101, 250, 252, 9, 49},
  {cont__107_104, &frame__107_101, 253, 253, 9, 23},
  {entry__107_77, NULL, 232, 235, 7, 20},
  {cont__107_79, &frame__107_77, 236, 238, 21, 54},
  {cont__107_82, &frame__107_77, 236, 238, 7, 54},
  {cont__107_83, &frame__107_77, 239, 239, 7, 24},
  {cont__107_84, &frame__107_77, 240, 240, 7, 34},
  {cont__107_86, &frame__107_77, 241, 241, 7, 28},
  {cont__107_87, &frame__107_77, 242, 242, 7, 18},
  {cont__107_88, &frame__107_77, 243, 243, 7, 18},
  {cont__107_89, &frame__107_77, 244, 244, 19, 35},
  {cont__107_90, &frame__107_77, 244, 244, 7, 68},
  {cont__107_95, &frame__107_77, 245, 248, 21, 13},
  {cont__107_98, &frame__107_77, 245, 248, 7, 13},
  {cont__107_99, &frame__107_77, 249, 249, 14, 36},
  {cont__107_100, &frame__107_77, 249, 253, 7, 23},
  {entry__107_74, NULL, 231, 231, 8, 32},
  {cont__107_75, &frame__107_74, 231, 231, 8, 36},
  {cont__107_76, &frame__107_74, 231, 253, 5, 24},
  {entry__107_2, NULL, 217, 253, 3, 25},
  {cont__107_105, &frame__107_2, 254, 254, 3, 19},
  {cont__107_106, &frame__107_2, 255, 255, 3, 8}
};

union NODE {
  struct {
    FUNC type;
    ATTRIBUTES *attributes;
  };
  CONTINUATION continuation;
  CLOSURE closure;
};
static NODE *character__92;
static NODE *character__90;
static NODE *character__122;
static NODE *character__57;
static NODE *character__65;
static NODE *character__44;
static NODE *character__10;
static NODE *number__0;
static NODE *character__58;
static NODE *number__3;
static NODE *character__48;
static NODE *character__95;
static NODE *character__40;
static NODE *character__34;
static NODE *character__36;
static NODE *character__125;
static NODE *character__41;
static NODE *character__97;
static NODE *number__1;
static NODE *number__2;
static NODE *character__42;

static const char *used_namespaces[] = {
  "std",
  "compiler",
  "node",
  NULL
};

static MODULE_INFO module_info = {
  NULL,
  "macros",
  continuation_info,
  sizeof(continuation_info)/sizeof(CONTINUATION_INFO),
  (NODE **)&var,
  var_names,
  sizeof(var_names)/sizeof(const char *),
  used_namespaces,
  {DEBUG_FILENAME("macros.sim")}
};

/******
C O D E
******/

static int already_run = false;

EXPORT void run__macros(void) {
  if (already_run) {
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  already_run = true;
  allocate_initialized_frame_gc(0, 0);
  // 34: %%event_name undefined
  set__event_name(get__undefined());
  // 35: %%event_kind undefined
  set__event_kind(get__undefined());
  // 36: %%event_phase undefined
  set__event_phase(get__undefined());
  // 37: %%data_variables undefined
  set__data_variables(get__undefined());
  // 38: %%info_variables undefined
  set__info_variables(get__undefined());
  // 39: $$macro_replacements empty_table
  var._macro_replacements = get__empty_table();
  // 43: define_macro "ARGC" "main_argc"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__400ae5cb5c587d7a;
  arguments->slots[1] = string__6c94222b8f3884e6;
  result_count = 0;
  myself = var._define_macro;
  func = myself->type;
  frame->cont = cont__83_3;
}
static void cont__83_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 44: define_macro "ARGV" "main_argv"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__400ae5cb5c587d6f;
  arguments->slots[1] = string__6c94222b8f3884f3;
  result_count = 0;
  myself = var._define_macro;
  func = myself->type;
  frame->cont = cont__84_3;
}
static void cont__84_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 45: define_macro "POLY_IDX" "poly_idx__$1"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__1028a78005f60678;
  arguments->slots[1] = string__34f9178f4105813b;
  result_count = 0;
  myself = var._define_macro;
  func = myself->type;
  frame->cont = cont__85_3;
}
static void cont__85_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 46: define_macro "POLY_COUNT" "polymorphic_function_count"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__6b819d4408594055;
  arguments->slots[1] = string__a8d3ab331eb668e7;
  result_count = 0;
  myself = var._define_macro;
  func = myself->type;
  frame->cont = cont__86_3;
}
static void cont__86_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 47: define_macro "POLY_WITH_SETTER_COUNT" "polymorphic_function_with_setter_count"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__59cab089aecbe8a5;
  arguments->slots[1] = string__77b931a5baaa8bfc;
  result_count = 0;
  myself = var._define_macro;
  func = myself->type;
  frame->cont = cont__87_3;
}
static void cont__87_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 48: define_macro "POLY_NAMES" "polymorphic_function_names"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__77819b4408019052;
  arguments->slots[1] = string__b4d3ad331eeeb8e0;
  result_count = 0;
  myself = var._define_macro;
  func = myself->type;
  frame->cont = cont__88_3;
}
static void cont__88_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 49: define_macro "UNIQUE_NAMES" "unique_item_names"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__48483b12ea44e011;
  arguments->slots[1] = string__a7a3514a924a78fa;
  result_count = 0;
  myself = var._define_macro;
  func = myself->type;
  frame->cont = cont__89_3;
}
static void cont__89_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 50: define_macro "ARGUMENT_COUNT" "argument_count"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__8f50c41d106226cf;
  arguments->slots[1] = string__dfd1ce1d312022e7;
  result_count = 0;
  myself = var._define_macro;
  func = myself->type;
  frame->cont = cont__90_3;
}
static void cont__90_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 51: define_macro "CONT" "frame->cont"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__440ae28b5c107d6d;
  arguments->slots[1] = string__6c9a2bd2e7c4af5;
  result_count = 0;
  myself = var._define_macro;
  func = myself->type;
  frame->cont = cont__91_3;
}
static void cont__91_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 52: define_macro "CHECK_ARGUMENTS" "
  // 53:   if (argument_count != $1) {
  // 54:     invalid_arguments_error();
  // 55:     return;
  // 56:   }@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__8d88533a39505214;
  arguments->slots[1] = string__1bb6ef61f3edfaf2;
  result_count = 0;
  myself = var._define_macro;
  func = myself->type;
  frame->cont = cont__92_3;
}
static void cont__92_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 57: define_macro "MIN_ARGUMENTS" "
  // 58:   if (argument_count < $1) {
  // 59:     too_few_arguments_error();
  // 60:     return;
  // 61:   }@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__8f7216a94bc80f3;
  arguments->slots[1] = string__fbe40d362af5bff1;
  result_count = 0;
  myself = var._define_macro;
  func = myself->type;
  frame->cont = cont__93_3;
}
static void cont__93_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 62: define_macro "MAX_ARGUMENTS" "
  // 63:   if (argument_count > $1) {
  // 64:     too_many_arguments_error();
  // 65:     return;
  // 66:   }@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__88f7216a94ac80f6;
  arguments->slots[1] = string__91ccef706a22d072;
  result_count = 0;
  myself = var._define_macro;
  func = myself->type;
  frame->cont = cont__94_3;
}
static void cont__94_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 67: define_macro "RESULT_COUNT" "result_count"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__940ced12ee123334;
  arguments->slots[1] = string__d48de512cf50371c;
  result_count = 0;
  myself = var._define_macro;
  func = myself->type;
  frame->cont = cont__95_3;
}
static void cont__95_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 68: define_macro "VAR": (arguments)
  // 69:   $name arguments(1)
  // 70:   if
  // 71:     global_names(name).is_defined
  // 72:     -> if(name .contains. "__" (-> "var.@(name)") -> "var._@(name)")
  // 73:     -> "get__@(name)()"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__fa72dc15c216b9e;
  arguments->slots[1] = func__96_2;
  result_count = 0;
  myself = var._define_macro;
  func = myself->type;
  frame->cont = cont__96_19;
}
static void entry__96_6(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 72: ... name .contains. "__"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = string__2d7981f4e5f02b9a;
  result_count = 1;
  myself = get__contains();
  func = myself->type;
  frame->cont = cont__96_7;
}
static void cont__96_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 72: ... -> "var.@(name)"
  frame->slots[3] /* temp__3 */ = create_closure(entry__96_8, 0);
  // 72: ... -> "var._@(name)"
  frame->slots[4] /* temp__4 */ = create_closure(entry__96_11, 0);
  // 72: ... if(name .contains. "__" (-> "var.@(name)") -> "var._@(name)")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  arguments->slots[2] = frame->slots[4] /* temp__4 */;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__96_14;
}
static void entry__96_8(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 72: ... "var.@(name)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2e0ae90b5df07d17;
  arguments->slots[1] = frame->slots[0] /* name */;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__96_10;
}
static void cont__96_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 72: ... -> "var.@(name)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__96_11(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 72: ... "var._@(name)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__485aef83e8b97008;
  arguments->slots[1] = frame->slots[0] /* name */;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__96_13;
}
static void cont__96_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 72: ... -> "var._@(name)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__96_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 72: -> if(name .contains. "__" (-> "var.@(name)") -> "var._@(name)")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__96_15(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 73: ... "get__@(name)()"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__405aee03eb306008;
  arguments->slots[1] = frame->slots[0] /* name */;
  arguments->slots[2] = string__2d7981f4e6482bec;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__96_18;
}
static void cont__96_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 73: -> "get__@(name)()"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__96_2(void) {
  allocate_initialized_frame_gc(1, 6);
  // slot allocations:
  // arguments: 0
  // name: 1
  frame->slots[1] /* name */ = create_future();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 69: $name arguments(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* arguments */;
  func = myself->type;
  frame->cont = cont__96_3;
}
static void cont__96_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* name */, arguments->slots[0]);
  // 71: global_names(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* name */;
  result_count = 1;
  myself = get__global_names();
  func = myself->type;
  frame->cont = cont__96_4;
}
static void cont__96_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 71: global_names(name).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__96_5;
}
static void cont__96_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 72: -> if(name .contains. "__" (-> "var.@(name)") -> "var._@(name)")
  frame->slots[4] /* temp__3 */ = create_closure(entry__96_6, 0);
  // 73: -> "get__@(name)()"
  frame->slots[5] /* temp__4 */ = create_closure(entry__96_15, 0);
  // 70: if
  // 71:   global_names(name).is_defined
  // 72:   -> if(name .contains. "__" (-> "var.@(name)") -> "var._@(name)")
  // 73:   -> "get__@(name)()"
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
static void cont__96_19(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 74: define_macro "EVENT": (arguments)
  // 75:   !event_name arguments(1)
  // 76:   !event_kind EVENT
  // 77:   -> "if (event__mode != EM__REPLAY) {"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__265ae243ebba4003;
  arguments->slots[1] = func__97_2;
  result_count = 0;
  myself = var._define_macro;
  func = myself->type;
  frame->cont = cont__97_5;
}
static void entry__97_2(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // arguments: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 75: !event_name arguments(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* arguments */;
  func = myself->type;
  frame->cont = cont__97_3;
}
static void cont__97_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__event_name(arguments->slots[0]);
  // 76: !event_kind EVENT
  set__event_kind(var._EVENT);
  // 77: -> "if (event__mode != EM__REPLAY) {"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__314a5f4a93a00186;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__97_5(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 78: define_macro "ACTION": (arguments)
  // 79:   !event_name arguments(1)
  // 80:   !event_kind ACTION
  // 81:   -> "if (event__mode != EM__REPLAY) {"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__301f5c1000c06299;
  arguments->slots[1] = func__98_2;
  result_count = 0;
  myself = var._define_macro;
  func = myself->type;
  frame->cont = cont__98_4;
}
static void entry__98_2(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // arguments: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 79: !event_name arguments(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* arguments */;
  func = myself->type;
  frame->cont = cont__98_3;
}
static void cont__98_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__event_name(arguments->slots[0]);
  // 80: !event_kind ACTION
  set__event_kind(var._ACTION);
  // 81: -> "if (event__mode != EM__REPLAY) {"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__314a5f4a93a00186;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__98_4(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 82: define_macro "INFO":
  // 83:   !event_phase INFO
  // 84:   -> ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__500ae2cb5c507d76;
  arguments->slots[1] = func__99_2;
  result_count = 0;
  myself = var._define_macro;
  func = myself->type;
  frame->cont = cont__99_3;
}
static void entry__99_2(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 83: !event_phase INFO
  set__event_phase(var._INFO);
  // 84: -> ""
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = empty_string;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__99_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 85: define_macro "DATA":
  // 86:   !event_phase DATA
  // 87:   if
  // 88:     event_kind == EVENT
  // 89:     -> "
  // 90:       @
  // 91:         if (event__mode == EM__RECORD) {
  // 92:           record__event("@(event_name)@quot;);@
  // 93:     -> "  if (event__mode == EM__RECORD) {"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__4a0ae10b5cc07d78;
  arguments->slots[1] = func__100_2;
  result_count = 0;
  myself = var._define_macro;
  func = myself->type;
  frame->cont = cont__100_10;
}
static void entry__100_4(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 89: ... "
  // 90:   @
  // 91:     if (event__mode == EM__RECORD) {
  // 92:       record__event("@(event_name)@quot;);@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__b0ac9625f04ddbd3;
  arguments->slots[1] = get__event_name();
  arguments->slots[2] = string__fa730c15f616bf7;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__100_7;
}
static void cont__100_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 89: -> "
  // 90:   @
  // 91:     if (event__mode == EM__RECORD) {
  // 92:       record__event("@(event_name)@quot;);@
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__100_8(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 93: -> "  if (event__mode == EM__RECORD) {"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__f9bb92aa6d4490dd;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__100_2(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 86: !event_phase DATA
  set__event_phase(var._DATA);
  // 88: event_kind == EVENT
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__event_kind();
  arguments->slots[1] = var._EVENT;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__100_3;
}
static void cont__100_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 87: if
  // 88:   event_kind == EVENT
  // 89:   -> "
  // 90:     @
  // 91:       if (event__mode == EM__RECORD) {
  // 92:         record__event("@(event_name)@quot;);@
  // 93:   -> "  if (event__mode == EM__RECORD) {"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = func__100_4;
  arguments->slots[2] = func__100_8;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__100_10(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  //  94: define_macro "INT": (arguments)
  //  95:   $name arguments(1)
  //  96:   case
  //  97:     event_phase
  //  98:     DATA:
  //  99:       push &data_variables put(arguments "integer")
  // 100:       if event_kind == EVENT (-> "  store__integer(@(name));") -> "
  // 101:         @
  // 102:           if (@(name) == @(arguments(2))) {
  // 103:               successful__action("@(event_name)");
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__fa72a015c596b98;
  arguments->slots[1] = func__101_2;
  result_count = 0;
  myself = var._define_macro;
  func = myself->type;
  frame->cont = cont__101_25;
}
static void entry__101_9(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 100: ... "  store__integer(@(name));"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__297be2f6f9dca12f;
  arguments->slots[1] = frame->slots[0] /* name */;
  arguments->slots[2] = string__2d7981f4e6402bfe;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__101_12;
}
static void cont__101_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 100: ... -> "  store__integer(@(name));"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__101_13(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // name: 0
  // arguments: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* name */
  frame->slots[1] = myself->closure.frame->slots[0]; /* arguments */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 102: ... arguments(2)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = frame->slots[1] /* arguments */;
  func = myself->type;
  frame->cont = cont__101_14;
}
static void cont__101_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 100: ... "
  // 101:   @
  // 102:     if (@(name) == @(arguments(2))) {
  // 103:         successful__action("@(event_name)");
  // 104:       } else {
  // 105:         failed__action("@(event_name)");
  // 106:         store__integer(@(name));
  // 107:       }@
  argument_count = 11;
  arguments = node_p;
  arguments->slots[0] = string__4a1f57e083be52ff;
  arguments->slots[1] = frame->slots[0] /* name */;
  arguments->slots[2] = string__820afe0b5f887d19;
  arguments->slots[3] = frame->slots[3] /* temp__2 */;
  arguments->slots[4] = string__fd21e7555dafa46d;
  arguments->slots[5] = get__event_name();
  arguments->slots[6] = string__7ed0587dfc52436;
  arguments->slots[7] = get__event_name();
  arguments->slots[8] = string__c81f08526aea5316;
  arguments->slots[9] = frame->slots[0] /* name */;
  arguments->slots[10] = string__eff8bde306d1997d;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__101_21;
}
static void cont__101_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 100: ... -> "
  // 101:   @
  // 102:     if (@(name) == @(arguments(2))) {
  // 103:         successful__action("@(event_name)");
  // 104:       } else {
  // 105:         failed__action("@(event_name)");
  // 106:         store__integer(@(name));
  // 107:       }@
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__101_4(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // arguments: 0
  // name: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* arguments */
  frame->slots[1] = myself->closure.frame->slots[1]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 99: ... put(arguments "integer")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* arguments */;
  arguments->slots[1] = string__b8200c1595938088;
  result_count = 1;
  myself = get__put();
  func = myself->type;
  frame->cont = cont__101_6;
}
static void cont__101_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 99: push &data_variables put(arguments "integer")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__data_variables();
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__101_7;
}
static void cont__101_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__data_variables(arguments->slots[0]);
  // 100: ... event_kind == EVENT
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__event_kind();
  arguments->slots[1] = var._EVENT;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__101_8;
}
static void cont__101_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 100: ... -> "  store__integer(@(name));"
  frame->slots[3] /* temp__2 */ = create_closure(entry__101_9, 0);
  // 100: ... -> "
  // 101:   @
  // 102:     if (@(name) == @(arguments(2))) {
  // 103:         successful__action("@(event_name)");
  // 104:       } else {
  // 105:         failed__action("@(event_name)");
  // 106:         store__integer(@(name));
  // 107:       }@
  frame->slots[4] /* temp__3 */ = create_closure(entry__101_13, 0);
  // 100: if event_kind == EVENT (-> "  store__integer(@(name));") -> "
  // 101:   @
  // 102:     if (@(name) == @(arguments(2))) {
  // 103:         successful__action("@(event_name)");
  // 104:       } else {
  // 105:         failed__action("@(event_name)");
  // 106:         store__integer(@(name));
  // 107:       }@
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
static void entry__101_22(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // arguments: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* arguments */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 109: ... put(arguments "integer")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* arguments */;
  arguments->slots[1] = string__b8200c1595938088;
  result_count = 1;
  myself = get__put();
  func = myself->type;
  frame->cont = cont__101_23;
}
static void cont__101_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 109: push &info_variables put(arguments "integer")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__info_variables();
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__101_24;
}
static void cont__101_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__info_variables(arguments->slots[0]);
  // 110: -> ""
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = empty_string;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__101_2(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // arguments: 0
  // name: 1
  frame->slots[1] /* name */ = create_future();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 95: $name arguments(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* arguments */;
  func = myself->type;
  frame->cont = cont__101_3;
}
static void cont__101_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* name */, arguments->slots[0]);
  //  98: ... :
  //  99:   push &data_variables put(arguments "integer")
  // 100:   if event_kind == EVENT (-> "  store__integer(@(name));") -> "
  // 101:     @
  // 102:       if (@(name) == @(arguments(2))) {
  // 103:           successful__action("@(event_name)");
  // 104:         } else {
  // 105:           failed__action("@(event_name)");
  // 106:           store__integer(@(name));
  // 107:         }@
  frame->slots[2] /* temp__1 */ = create_closure(entry__101_4, 0);
  // 108: ... :
  // 109:   push &info_variables put(arguments "integer")
  // 110:   -> ""
  frame->slots[3] /* temp__2 */ = create_closure(entry__101_22, 0);
  //  96: case
  //  97:   event_phase
  //  98:   DATA:
  //  99:     push &data_variables put(arguments "integer")
  // 100:     if event_kind == EVENT (-> "  store__integer(@(name));") -> "
  // 101:       @
  // 102:         if (@(name) == @(arguments(2))) {
  // 103:             successful__action("@(event_name)");
  // 104:           } else {
  // 105:             failed__action("@(event_name)");
  // ...
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = get__event_phase();
  arguments->slots[1] = var._DATA;
  arguments->slots[2] = frame->slots[2] /* temp__1 */;
  arguments->slots[3] = var._INFO;
  arguments->slots[4] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__101_25(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 111: define_macro "LONG": (arguments)
  // 112:   $name arguments(1)
  // 113:   case
  // 114:     event_phase
  // 115:     DATA:
  // 116:       push &data_variables put(arguments "long_integer")
  // 117:       if event_kind == EVENT (-> "  store__long_integer(@(name));") -> "
  // 118:         @
  // 119:           if (@(name) == @(arguments(2))) {
  // 120:               successful__action("@(event_name)");
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__5a0ae28b5c107d7e;
  arguments->slots[1] = func__102_2;
  result_count = 0;
  myself = var._define_macro;
  func = myself->type;
  frame->cont = cont__102_19;
}
static void entry__102_9(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 117: ... "  store__long_integer(@(name));"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__329e59a9af29a0d5;
  arguments->slots[1] = frame->slots[0] /* name */;
  arguments->slots[2] = string__2d7981f4e6402bfe;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__102_11;
}
static void cont__102_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 117: ... -> "  store__long_integer(@(name));"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__102_12(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // name: 0
  // arguments: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* name */
  frame->slots[1] = myself->closure.frame->slots[0]; /* arguments */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 119: ... arguments(2)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = frame->slots[1] /* arguments */;
  func = myself->type;
  frame->cont = cont__102_13;
}
static void cont__102_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 117: ... "
  // 118:   @
  // 119:     if (@(name) == @(arguments(2))) {
  // 120:         successful__action("@(event_name)");
  // 121:       } else {
  // 122:         failed__action("@(event_name)");
  // 123:         store__long_integer(@(name));
  // 124:       }@
  argument_count = 11;
  arguments = node_p;
  arguments->slots[0] = string__4a1f57e083be52ff;
  arguments->slots[1] = frame->slots[0] /* name */;
  arguments->slots[2] = string__820afe0b5f887d19;
  arguments->slots[3] = frame->slots[3] /* temp__2 */;
  arguments->slots[4] = string__fd21e7555dafa46d;
  arguments->slots[5] = get__event_name();
  arguments->slots[6] = string__7ed0587dfc52436;
  arguments->slots[7] = get__event_name();
  arguments->slots[8] = string__7b0520b55f9bd587;
  arguments->slots[9] = frame->slots[0] /* name */;
  arguments->slots[10] = string__eff8bde306d1997d;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__102_15;
}
static void cont__102_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 117: ... -> "
  // 118:   @
  // 119:     if (@(name) == @(arguments(2))) {
  // 120:         successful__action("@(event_name)");
  // 121:       } else {
  // 122:         failed__action("@(event_name)");
  // 123:         store__long_integer(@(name));
  // 124:       }@
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__102_4(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // arguments: 0
  // name: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* arguments */
  frame->slots[1] = myself->closure.frame->slots[1]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 116: ... put(arguments "long_integer")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* arguments */;
  arguments->slots[1] = string__40f9098a5d354178;
  result_count = 1;
  myself = get__put();
  func = myself->type;
  frame->cont = cont__102_6;
}
static void cont__102_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 116: push &data_variables put(arguments "long_integer")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__data_variables();
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__102_7;
}
static void cont__102_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__data_variables(arguments->slots[0]);
  // 117: ... event_kind == EVENT
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__event_kind();
  arguments->slots[1] = var._EVENT;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__102_8;
}
static void cont__102_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 117: ... -> "  store__long_integer(@(name));"
  frame->slots[3] /* temp__2 */ = create_closure(entry__102_9, 0);
  // 117: ... -> "
  // 118:   @
  // 119:     if (@(name) == @(arguments(2))) {
  // 120:         successful__action("@(event_name)");
  // 121:       } else {
  // 122:         failed__action("@(event_name)");
  // 123:         store__long_integer(@(name));
  // 124:       }@
  frame->slots[4] /* temp__3 */ = create_closure(entry__102_12, 0);
  // 117: if event_kind == EVENT (-> "  store__long_integer(@(name));") -> "
  // 118:   @
  // 119:     if (@(name) == @(arguments(2))) {
  // 120:         successful__action("@(event_name)");
  // 121:       } else {
  // 122:         failed__action("@(event_name)");
  // 123:         store__long_integer(@(name));
  // 124:       }@
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
static void entry__102_16(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // arguments: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* arguments */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 126: ... put(arguments "long_integer")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* arguments */;
  arguments->slots[1] = string__40f9098a5d354178;
  result_count = 1;
  myself = get__put();
  func = myself->type;
  frame->cont = cont__102_17;
}
static void cont__102_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 126: push &info_variables put(arguments "long_integer")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__info_variables();
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__102_18;
}
static void cont__102_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__info_variables(arguments->slots[0]);
  // 127: -> ""
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = empty_string;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__102_2(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // arguments: 0
  // name: 1
  frame->slots[1] /* name */ = create_future();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 112: $name arguments(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* arguments */;
  func = myself->type;
  frame->cont = cont__102_3;
}
static void cont__102_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* name */, arguments->slots[0]);
  // 115: ... :
  // 116:   push &data_variables put(arguments "long_integer")
  // 117:   if event_kind == EVENT (-> "  store__long_integer(@(name));") -> "
  // 118:     @
  // 119:       if (@(name) == @(arguments(2))) {
  // 120:           successful__action("@(event_name)");
  // 121:         } else {
  // 122:           failed__action("@(event_name)");
  // 123:           store__long_integer(@(name));
  // 124:         }@
  frame->slots[2] /* temp__1 */ = create_closure(entry__102_4, 0);
  // 125: ... :
  // 126:   push &info_variables put(arguments "long_integer")
  // 127:   -> ""
  frame->slots[3] /* temp__2 */ = create_closure(entry__102_16, 0);
  // 113: case
  // 114:   event_phase
  // 115:   DATA:
  // 116:     push &data_variables put(arguments "long_integer")
  // 117:     if event_kind == EVENT (-> "  store__long_integer(@(name));") -> "
  // 118:       @
  // 119:         if (@(name) == @(arguments(2))) {
  // 120:             successful__action("@(event_name)");
  // 121:           } else {
  // 122:             failed__action("@(event_name)");
  // ...
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = get__event_phase();
  arguments->slots[1] = var._DATA;
  arguments->slots[2] = frame->slots[2] /* temp__1 */;
  arguments->slots[3] = var._INFO;
  arguments->slots[4] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__102_19(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 128: define_macro "POINTER": (arguments)
  // 129:   $name arguments(1)
  // 130:   case
  // 131:     event_phase
  // 132:     DATA:
  // 133:       push &data_variables put(arguments "pointer")
  // 134:       if event_kind == EVENT (-> "  store__pointer(@(name));") -> "
  // 135:         @
  // 136:           if (@(name) && @(name) != (void *)FIRST_INVALID_ADDRESS) {
  // 137:               successful__action("@(event_name)");
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__eec400c5149050a8;
  arguments->slots[1] = func__103_2;
  result_count = 0;
  myself = var._define_macro;
  func = myself->type;
  frame->cont = cont__103_20;
}
static void entry__103_9(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 134: ... "  store__pointer(@(name));"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__f7fe2f879dc120f;
  arguments->slots[1] = frame->slots[0] /* name */;
  arguments->slots[2] = string__2d7981f4e6402bfe;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__103_11;
}
static void cont__103_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 134: ... -> "  store__pointer(@(name));"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__103_12(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 134: ... "
  // 135:   @
  // 136:     if (@(name) && @(name) != (void *)FIRST_INVALID_ADDRESS) {
  // 137:         successful__action("@(event_name)");
  // 138:       } else {
  // 139:         failed__action("@(event_name)");
  // 140:         store__pointer(@(name));
  // 141:       }@
  argument_count = 11;
  arguments = node_p;
  arguments->slots[0] = string__4a1f57e083be52ff;
  arguments->slots[1] = frame->slots[0] /* name */;
  arguments->slots[2] = string__820af8cb5f507d19;
  arguments->slots[3] = frame->slots[0] /* name */;
  arguments->slots[4] = string__1ee649de6e08afc4;
  arguments->slots[5] = get__event_name();
  arguments->slots[6] = string__7ed0587dfc52436;
  arguments->slots[7] = get__event_name();
  arguments->slots[8] = string__ee1b085ceaeae036;
  arguments->slots[9] = frame->slots[0] /* name */;
  arguments->slots[10] = string__eff8bde306d1997d;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__103_16;
}
static void cont__103_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 134: ... -> "
  // 135:   @
  // 136:     if (@(name) && @(name) != (void *)FIRST_INVALID_ADDRESS) {
  // 137:         successful__action("@(event_name)");
  // 138:       } else {
  // 139:         failed__action("@(event_name)");
  // 140:         store__pointer(@(name));
  // 141:       }@
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__103_4(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // arguments: 0
  // name: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* arguments */
  frame->slots[1] = myself->closure.frame->slots[1]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 133: ... put(arguments "pointer")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* arguments */;
  arguments->slots[1] = string__ae4408d515925088;
  result_count = 1;
  myself = get__put();
  func = myself->type;
  frame->cont = cont__103_6;
}
static void cont__103_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 133: push &data_variables put(arguments "pointer")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__data_variables();
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__103_7;
}
static void cont__103_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__data_variables(arguments->slots[0]);
  // 134: ... event_kind == EVENT
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__event_kind();
  arguments->slots[1] = var._EVENT;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__103_8;
}
static void cont__103_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 134: ... -> "  store__pointer(@(name));"
  frame->slots[3] /* temp__2 */ = create_closure(entry__103_9, 0);
  // 134: ... -> "
  // 135:   @
  // 136:     if (@(name) && @(name) != (void *)FIRST_INVALID_ADDRESS) {
  // 137:         successful__action("@(event_name)");
  // 138:       } else {
  // 139:         failed__action("@(event_name)");
  // 140:         store__pointer(@(name));
  // 141:       }@
  frame->slots[4] /* temp__3 */ = create_closure(entry__103_12, 0);
  // 134: if event_kind == EVENT (-> "  store__pointer(@(name));") -> "
  // 135:   @
  // 136:     if (@(name) && @(name) != (void *)FIRST_INVALID_ADDRESS) {
  // 137:         successful__action("@(event_name)");
  // 138:       } else {
  // 139:         failed__action("@(event_name)");
  // 140:         store__pointer(@(name));
  // 141:       }@
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
static void entry__103_17(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // arguments: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* arguments */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 143: ... put(arguments "pointer")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* arguments */;
  arguments->slots[1] = string__ae4408d515925088;
  result_count = 1;
  myself = get__put();
  func = myself->type;
  frame->cont = cont__103_18;
}
static void cont__103_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 143: push &info_variables put(arguments "pointer")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__info_variables();
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__103_19;
}
static void cont__103_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__info_variables(arguments->slots[0]);
  // 144: -> ""
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = empty_string;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__103_2(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // arguments: 0
  // name: 1
  frame->slots[1] /* name */ = create_future();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 129: $name arguments(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* arguments */;
  func = myself->type;
  frame->cont = cont__103_3;
}
static void cont__103_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* name */, arguments->slots[0]);
  // 132: ... :
  // 133:   push &data_variables put(arguments "pointer")
  // 134:   if event_kind == EVENT (-> "  store__pointer(@(name));") -> "
  // 135:     @
  // 136:       if (@(name) && @(name) != (void *)FIRST_INVALID_ADDRESS) {
  // 137:           successful__action("@(event_name)");
  // 138:         } else {
  // 139:           failed__action("@(event_name)");
  // 140:           store__pointer(@(name));
  // 141:         }@
  frame->slots[2] /* temp__1 */ = create_closure(entry__103_4, 0);
  // 142: ... :
  // 143:   push &info_variables put(arguments "pointer")
  // 144:   -> ""
  frame->slots[3] /* temp__2 */ = create_closure(entry__103_17, 0);
  // 130: case
  // 131:   event_phase
  // 132:   DATA:
  // 133:     push &data_variables put(arguments "pointer")
  // 134:     if event_kind == EVENT (-> "  store__pointer(@(name));") -> "
  // 135:       @
  // 136:         if (@(name) && @(name) != (void *)FIRST_INVALID_ADDRESS) {
  // 137:             successful__action("@(event_name)");
  // 138:           } else {
  // 139:             failed__action("@(event_name)");
  // ...
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = get__event_phase();
  arguments->slots[1] = var._DATA;
  arguments->slots[2] = frame->slots[2] /* temp__1 */;
  arguments->slots[3] = var._INFO;
  arguments->slots[4] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__103_20(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 145: define_macro "INT_ARRAY": (arguments)
  // 146:   $name arguments(1)
  // 147:   $length arguments(2)
  // 148:   case
  // 149:     event_phase
  // 150:     DATA:
  // 151:       push &data_variables put(arguments "int_array")
  // 152:       -> "  store__int_array(@(name), @(length));"
  // 153:     INFO:
  // 154:       push &info_variables put(arguments "int_array")
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__a602a332a09613c;
  arguments->slots[1] = func__104_2;
  result_count = 0;
  myself = var._define_macro;
  func = myself->type;
  frame->cont = cont__104_14;
}
static void entry__104_5(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // arguments: 0
  // name: 1
  // length: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* arguments */
  frame->slots[1] = myself->closure.frame->slots[1]; /* name */
  frame->slots[2] = myself->closure.frame->slots[2]; /* length */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 151: ... put(arguments "int_array")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* arguments */;
  arguments->slots[1] = string__4ae022330b0b651c;
  result_count = 1;
  myself = get__put();
  func = myself->type;
  frame->cont = cont__104_7;
}
static void cont__104_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 151: push &data_variables put(arguments "int_array")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__data_variables();
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__104_8;
}
static void cont__104_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__data_variables(arguments->slots[0]);
  // 152: ... "  store__int_array(@(name), @(length));"
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = string__77c059895d31cd96;
  arguments->slots[1] = frame->slots[1] /* name */;
  arguments->slots[2] = string__2d7981f4e6682be5;
  arguments->slots[3] = frame->slots[2] /* length */;
  arguments->slots[4] = string__2d7981f4e6402bfe;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__104_10;
}
static void cont__104_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 152: -> "  store__int_array(@(name), @(length));"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__104_11(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // arguments: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* arguments */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 154: ... put(arguments "int_array")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* arguments */;
  arguments->slots[1] = string__4ae022330b0b651c;
  result_count = 1;
  myself = get__put();
  func = myself->type;
  frame->cont = cont__104_12;
}
static void cont__104_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 154: push &info_variables put(arguments "int_array")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__info_variables();
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__104_13;
}
static void cont__104_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__info_variables(arguments->slots[0]);
  // 155: -> ""
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = empty_string;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__104_2(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // arguments: 0
  // name: 1
  // length: 2
  frame->slots[1] /* name */ = create_future();
  frame->slots[2] /* length */ = create_future();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 146: $name arguments(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* arguments */;
  func = myself->type;
  frame->cont = cont__104_3;
}
static void cont__104_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* name */, arguments->slots[0]);
  // 147: $length arguments(2)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = frame->slots[0] /* arguments */;
  func = myself->type;
  frame->cont = cont__104_4;
}
static void cont__104_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* length */, arguments->slots[0]);
  // 150: ... :
  // 151:   push &data_variables put(arguments "int_array")
  // 152:   -> "  store__int_array(@(name), @(length));"
  frame->slots[3] /* temp__1 */ = create_closure(entry__104_5, 0);
  // 153: ... :
  // 154:   push &info_variables put(arguments "int_array")
  // 155:   -> ""
  frame->slots[4] /* temp__2 */ = create_closure(entry__104_11, 0);
  // 148: case
  // 149:   event_phase
  // 150:   DATA:
  // 151:     push &data_variables put(arguments "int_array")
  // 152:     -> "  store__int_array(@(name), @(length));"
  // 153:   INFO:
  // 154:     push &info_variables put(arguments "int_array")
  // 155:     -> ""
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = get__event_phase();
  arguments->slots[1] = var._DATA;
  arguments->slots[2] = frame->slots[3] /* temp__1 */;
  arguments->slots[3] = var._INFO;
  arguments->slots[4] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__104_14(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 156: define_macro "MEMORY": (arguments)
  // 157:   $name arguments(1)
  // 158:   $length arguments(2)
  // 159:   case
  // 160:     event_phase
  // 161:     DATA:
  // 162:       push &data_variables put(arguments "memory")
  // 163:       -> "  store__memory(@(name), @(length));"
  // 164:     INFO:
  // 165:       push &info_variables put(arguments "memory")
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__21f5d960028028e;
  arguments->slots[1] = func__105_2;
  result_count = 0;
  myself = var._define_macro;
  func = myself->type;
  frame->cont = cont__105_14;
}
static void entry__105_5(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // arguments: 0
  // name: 1
  // length: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* arguments */
  frame->slots[1] = myself->closure.frame->slots[1]; /* name */
  frame->slots[2] = myself->closure.frame->slots[2]; /* length */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 162: ... put(arguments "memory")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* arguments */;
  arguments->slots[1] = string__421f5586012a02ae;
  result_count = 1;
  myself = get__put();
  func = myself->type;
  frame->cont = cont__105_7;
}
static void cont__105_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 162: push &data_variables put(arguments "memory")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__data_variables();
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__105_8;
}
static void cont__105_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__data_variables(arguments->slots[0]);
  // 163: ... "  store__memory(@(name), @(length));"
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = string__8030e06afcbf4f61;
  arguments->slots[1] = frame->slots[1] /* name */;
  arguments->slots[2] = string__2d7981f4e6682be5;
  arguments->slots[3] = frame->slots[2] /* length */;
  arguments->slots[4] = string__2d7981f4e6402bfe;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__105_10;
}
static void cont__105_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 163: -> "  store__memory(@(name), @(length));"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__105_11(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // arguments: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* arguments */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 165: ... put(arguments "memory")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* arguments */;
  arguments->slots[1] = string__421f5586012a02ae;
  result_count = 1;
  myself = get__put();
  func = myself->type;
  frame->cont = cont__105_12;
}
static void cont__105_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 165: push &info_variables put(arguments "memory")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__info_variables();
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__105_13;
}
static void cont__105_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__info_variables(arguments->slots[0]);
  // 166: -> ""
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = empty_string;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__105_2(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // arguments: 0
  // name: 1
  // length: 2
  frame->slots[1] /* name */ = create_future();
  frame->slots[2] /* length */ = create_future();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 157: $name arguments(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* arguments */;
  func = myself->type;
  frame->cont = cont__105_3;
}
static void cont__105_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* name */, arguments->slots[0]);
  // 158: $length arguments(2)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = frame->slots[0] /* arguments */;
  func = myself->type;
  frame->cont = cont__105_4;
}
static void cont__105_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* length */, arguments->slots[0]);
  // 161: ... :
  // 162:   push &data_variables put(arguments "memory")
  // 163:   -> "  store__memory(@(name), @(length));"
  frame->slots[3] /* temp__1 */ = create_closure(entry__105_5, 0);
  // 164: ... :
  // 165:   push &info_variables put(arguments "memory")
  // 166:   -> ""
  frame->slots[4] /* temp__2 */ = create_closure(entry__105_11, 0);
  // 159: case
  // 160:   event_phase
  // 161:   DATA:
  // 162:     push &data_variables put(arguments "memory")
  // 163:     -> "  store__memory(@(name), @(length));"
  // 164:   INFO:
  // 165:     push &info_variables put(arguments "memory")
  // 166:     -> ""
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = get__event_phase();
  arguments->slots[1] = var._DATA;
  arguments->slots[2] = frame->slots[3] /* temp__1 */;
  arguments->slots[3] = var._INFO;
  arguments->slots[4] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__105_14(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 167: define_macro "C_STRING": (arguments)
  // 168:   $name arguments(1)
  // 169:   case
  // 170:     event_phase
  // 171:     DATA:
  // 172:       push &data_variables put(arguments "c_string")
  // 173:       -> "  store__c_string(@(name));"
  // 174:     INFO:
  // 175:       push &info_variables put(arguments "c_string")
  // 176:       -> ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__a68a78f85a6d407;
  arguments->slots[1] = func__106_2;
  result_count = 0;
  myself = var._define_macro;
  func = myself->type;
  frame->cont = cont__106_13;
}
static void entry__106_4(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // arguments: 0
  // name: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* arguments */
  frame->slots[1] = myself->closure.frame->slots[1]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 172: ... put(arguments "c_string")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* arguments */;
  arguments->slots[1] = string__4a68af9f84a4d027;
  result_count = 1;
  myself = get__put();
  func = myself->type;
  frame->cont = cont__106_6;
}
static void cont__106_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 172: push &data_variables put(arguments "c_string")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__data_variables();
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__106_7;
}
static void cont__106_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__data_variables(arguments->slots[0]);
  // 173: ... "  store__c_string(@(name));"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__fabc9ed81001dd7;
  arguments->slots[1] = frame->slots[1] /* name */;
  arguments->slots[2] = string__2d7981f4e6402bfe;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__106_9;
}
static void cont__106_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 173: -> "  store__c_string(@(name));"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__106_10(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // arguments: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* arguments */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 175: ... put(arguments "c_string")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* arguments */;
  arguments->slots[1] = string__4a68af9f84a4d027;
  result_count = 1;
  myself = get__put();
  func = myself->type;
  frame->cont = cont__106_11;
}
static void cont__106_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 175: push &info_variables put(arguments "c_string")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__info_variables();
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__106_12;
}
static void cont__106_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__info_variables(arguments->slots[0]);
  // 176: -> ""
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = empty_string;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__106_2(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // arguments: 0
  // name: 1
  frame->slots[1] /* name */ = create_future();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 168: $name arguments(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* arguments */;
  func = myself->type;
  frame->cont = cont__106_3;
}
static void cont__106_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* name */, arguments->slots[0]);
  // 171: ... :
  // 172:   push &data_variables put(arguments "c_string")
  // 173:   -> "  store__c_string(@(name));"
  frame->slots[2] /* temp__1 */ = create_closure(entry__106_4, 0);
  // 174: ... :
  // 175:   push &info_variables put(arguments "c_string")
  // 176:   -> ""
  frame->slots[3] /* temp__2 */ = create_closure(entry__106_10, 0);
  // 169: case
  // 170:   event_phase
  // 171:   DATA:
  // 172:     push &data_variables put(arguments "c_string")
  // 173:     -> "  store__c_string(@(name));"
  // 174:   INFO:
  // 175:     push &info_variables put(arguments "c_string")
  // 176:     -> ""
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = get__event_phase();
  arguments->slots[1] = var._DATA;
  arguments->slots[2] = frame->slots[2] /* temp__1 */;
  arguments->slots[3] = var._INFO;
  arguments->slots[4] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__106_13(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 177: define_macro "END":
  // 178:   $retrieve_variables:
  // 179:     $indent if(event_kind == ACTION (-> "      ") -> "  ")
  // 180:     for_each data_variables: (var)
  // 181:       $type var(1)
  // 182:       $name var(2)
  // 183:       case
  // 184:         type
  // 185:         "pointer":
  // 186:           writeln_to &buf indent "retrieve__pointer((void **)&@(name));"
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__fa729015c596b88;
  arguments->slots[1] = func__107_2;
  result_count = 0;
  myself = var._define_macro;
  func = myself->type;
  frame->cont = cont__107_107;
}
static void entry__107_2(void) {
  allocate_initialized_frame_gc(0, 5);
  // slot allocations:
  // retrieve_variables: 0
  // print_variables: 1
  // buf: 2
  frame->slots[0] /* retrieve_variables */ = create_future();
  frame->slots[1] /* print_variables */ = create_future();
  frame->slots[2] /* buf */ = create_cell();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 178: ... :
  // 179:   $indent if(event_kind == ACTION (-> "      ") -> "  ")
  // 180:   for_each data_variables: (var)
  // 181:     $type var(1)
  // 182:     $name var(2)
  // 183:     case
  // 184:       type
  // 185:       "pointer":
  // 186:         writeln_to &buf indent "retrieve__pointer((void **)&@(name));"
  // 187:       "int_array":
  // ...
  frame->slots[3] /* temp__1 */ = create_closure(entry__107_3, 0);
  // 178: $retrieve_variables:
  // 179:   $indent if(event_kind == ACTION (-> "      ") -> "  ")
  // 180:   for_each data_variables: (var)
  // 181:     $type var(1)
  // 182:     $name var(2)
  // 183:     case
  // 184:       type
  // 185:       "pointer":
  // 186:         writeln_to &buf indent "retrieve__pointer((void **)&@(name));"
  // 187:       "int_array":
  // ...
  initialize_future(frame->slots[0] /* retrieve_variables */, frame->slots[3] /* temp__1 */);
  // 200: ... :
  // 201:   $indent if(event_kind == ACTION (-> "      ") -> "  ")
  // 202:   for_each info_variables: (var)
  // 203:     $type var(1)
  // 204:     $name var(2)
  // 205:     case
  // 206:       type
  // 207:       "pointer":
  // 208:         writeln_to &buf indent "print__pointer(@(name));"
  // 209:       "int_array":
  // ...
  frame->slots[3] /* temp__1 */ = create_closure(entry__107_32, 0);
  // 200: $print_variables:
  // 201:   $indent if(event_kind == ACTION (-> "      ") -> "  ")
  // 202:   for_each info_variables: (var)
  // 203:     $type var(1)
  // 204:     $name var(2)
  // 205:     case
  // 206:       type
  // 207:       "pointer":
  // 208:         writeln_to &buf indent "print__pointer(@(name));"
  // 209:       "int_array":
  // ...
  initialize_future(frame->slots[1] /* print_variables */, frame->slots[3] /* temp__1 */);
  // 216: $$buf ""
  ((CELL *)frame->slots[2])->contents /* buf */ = empty_string;
  // 218: -> event_kind == EVENT:
  // 219:   write_to &buf "
  // 220:       }
  // 221:     } else {
  // 222:   write_to &buf "
  // 223:     @
  // 224:       replay__event("@(event_name)");
  // 225:   retrieve_variables
  // 226:   unless info_variables.is_empty:
  // 227:     write_to &buf "
  // ...
  frame->slots[3] /* temp__1 */ = create_closure(entry__107_59, 0);
  // 231: -> length_of(data_variables) > 0:
  // 232:   write_to &buf "
  // 233:     @
  // 234:         }
  // 235:       } else {
  // 236:   write_to &buf "
  // 237:     @
  // 238:         if (replay__action("@(event_name)")) {
  // 239:   retrieve_variables
  // 240:   writeln_to &buf "  } else {"
  // ...
  frame->slots[4] /* temp__2 */ = create_closure(entry__107_74, 0);
  // 217: cond
  // 218:   -> event_kind == EVENT:
  // 219:     write_to &buf "
  // 220:         }
  // 221:       } else {
  // 222:     write_to &buf "
  // 223:       @
  // 224:         replay__event("@(event_name)");
  // 225:     retrieve_variables
  // 226:     unless info_variables.is_empty:
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__cond();
  func = myself->type;
  frame->cont = cont__107_105;
}
static void entry__107_101(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // buf: 0
  // print_variables: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* buf */
  frame->slots[1] = myself->closure.frame->slots[2]; /* print_variables */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 250: ... "
  // 251:   @
  // 252:       report__event("@(event_name)");
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__4fbb5986ed8ccf7;
  arguments->slots[1] = get__event_name();
  arguments->slots[2] = string__860afb0b5fb87d33;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__107_103;
}
static void cont__107_103(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 250: write_to &buf "
  // 251:   @
  // 252:       report__event("@(event_name)");
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* buf */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__write_to();
  func = myself->type;
  frame->cont = cont__107_104;
}
static void cont__107_104(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* buf */ = arguments->slots[0];
  // 253: print_variables
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* print_variables */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__107_77(void) {
  allocate_initialized_frame_gc(3, 9);
  // slot allocations:
  // buf: 0
  // retrieve_variables: 1
  // print_variables: 2
  // var: 3
  // type: 4
  // name: 5
  // default: 6
  frame->slots[0] = myself->closure.frame->slots[0]; /* buf */
  frame->slots[1] = myself->closure.frame->slots[1]; /* retrieve_variables */
  frame->slots[2] = myself->closure.frame->slots[2]; /* print_variables */
  frame->slots[3] /* var */ = create_future();
  frame->slots[4] /* type */ = create_future();
  frame->slots[5] /* name */ = create_future();
  frame->slots[6] /* default */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 232: write_to &buf "
  // 233:   @
  // 234:       }
  // 235:     } else {
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* buf */;
  arguments->slots[1] = string__47540a9adb64843c;
  result_count = 1;
  myself = get__write_to();
  func = myself->type;
  frame->cont = cont__107_79;
}
static void cont__107_79(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* buf */ = arguments->slots[0];
  // 236: ... "
  // 237:   @
  // 238:       if (replay__action("@(event_name)")) {
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__3f8698e0b2f30ecd;
  arguments->slots[1] = get__event_name();
  arguments->slots[2] = string__ca1f46618166c2dd;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__107_82;
}
static void cont__107_82(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 236: write_to &buf "
  // 237:   @
  // 238:       if (replay__action("@(event_name)")) {
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* buf */;
  arguments->slots[1] = frame->slots[7] /* temp__1 */;
  result_count = 1;
  myself = get__write_to();
  func = myself->type;
  frame->cont = cont__107_83;
}
static void cont__107_83(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* buf */ = arguments->slots[0];
  // 239: retrieve_variables
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = frame->slots[1] /* retrieve_variables */;
  func = myself->type;
  frame->cont = cont__107_84;
}
static void cont__107_84(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 240: writeln_to &buf "  } else {"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* buf */;
  arguments->slots[1] = string__12661159642bb65a;
  result_count = 1;
  myself = get__writeln_to();
  func = myself->type;
  frame->cont = cont__107_86;
}
static void cont__107_86(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* buf */ = arguments->slots[0];
  // 241: $var data_variables(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__data_variables();
  func = myself->type;
  frame->cont = cont__107_87;
}
static void cont__107_87(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* var */, arguments->slots[0]);
  // 242: $type var(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[3] /* var */;
  func = myself->type;
  frame->cont = cont__107_88;
}
static void cont__107_88(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* type */, arguments->slots[0]);
  // 243: $name var(2)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = frame->slots[3] /* var */;
  func = myself->type;
  frame->cont = cont__107_89;
}
static void cont__107_89(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* name */, arguments->slots[0]);
  // 244: ... type == "pointer"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* type */;
  arguments->slots[1] = string__ae4408d515925088;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__107_90;
}
static void cont__107_90(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 244: ... -> var(3)
  frame->slots[8] /* temp__2 */ = create_closure(entry__107_91, 0);
  // 244: $default if(type == "pointer" (-> "SAMPLE_POINTER") -> var(3))
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = func__107_93;
  arguments->slots[2] = frame->slots[8] /* temp__2 */;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__107_95;
}
static void entry__107_91(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // var: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* var */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 244: ... var(3)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__3;
  result_count = 1;
  myself = frame->slots[0] /* var */;
  func = myself->type;
  frame->cont = cont__107_92;
}
static void cont__107_92(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 244: ... -> var(3)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__107_93(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 244: ... -> "SAMPLE_POINTER"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__c440cd65102e84e8;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__107_95(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* default */, arguments->slots[0]);
  // 245: ... "
  // 246:   @
  // 247:         @(name) = @(default);
  // 248:     }
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = string__d81f466083be52f7;
  arguments->slots[1] = frame->slots[5] /* name */;
  arguments->slots[2] = string__fa730415fc16bec;
  arguments->slots[3] = frame->slots[6] /* default */;
  arguments->slots[4] = string__d81f466d0154f2dd;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__107_98;
}
static void cont__107_98(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 245: write_to &buf "
  // 246:   @
  // 247:         @(name) = @(default);
  // 248:     }
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* buf */;
  arguments->slots[1] = frame->slots[7] /* temp__1 */;
  result_count = 1;
  myself = get__write_to();
  func = myself->type;
  frame->cont = cont__107_99;
}
static void cont__107_99(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* buf */ = arguments->slots[0];
  // 249: ... info_variables.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__info_variables();
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__107_100;
}
static void cont__107_100(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 249: ... :
  // 250:   write_to &buf "
  // 251:     @
  // 252:         report__event("@(event_name)");
  // 253:   print_variables
  frame->slots[8] /* temp__2 */ = create_closure(entry__107_101, 0);
  // 249: unless info_variables.is_empty:
  // 250:   write_to &buf "
  // 251:     @
  // 252:         report__event("@(event_name)");
  // 253:   print_variables
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__107_70(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // buf: 0
  // print_variables: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* buf */
  frame->slots[1] = myself->closure.frame->slots[2]; /* print_variables */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 227: ... "
  // 228:   @
  // 229:     report__event("@(event_name)");
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__f3d6bf47fb36a3e0;
  arguments->slots[1] = get__event_name();
  arguments->slots[2] = string__860afb0b5fb87d33;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__107_72;
}
static void cont__107_72(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 227: write_to &buf "
  // 228:   @
  // 229:     report__event("@(event_name)");
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* buf */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__write_to();
  func = myself->type;
  frame->cont = cont__107_73;
}
static void cont__107_73(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* buf */ = arguments->slots[0];
  // 230: print_variables
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* print_variables */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__107_61(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // buf: 0
  // retrieve_variables: 1
  // print_variables: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* buf */
  frame->slots[1] = myself->closure.frame->slots[1]; /* retrieve_variables */
  frame->slots[2] = myself->closure.frame->slots[2]; /* print_variables */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 219: write_to &buf "
  // 220:     }
  // 221:   } else {
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* buf */;
  arguments->slots[1] = string__887d942629156ee6;
  result_count = 1;
  myself = get__write_to();
  func = myself->type;
  frame->cont = cont__107_63;
}
static void cont__107_63(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* buf */ = arguments->slots[0];
  // 222: ... "
  // 223:   @
  // 224:     replay__event("@(event_name)");
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__33d6d747fb30a3e4;
  arguments->slots[1] = get__event_name();
  arguments->slots[2] = string__860afb0b5fb87d33;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__107_66;
}
static void cont__107_66(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 222: write_to &buf "
  // 223:   @
  // 224:     replay__event("@(event_name)");
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* buf */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__write_to();
  func = myself->type;
  frame->cont = cont__107_67;
}
static void cont__107_67(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* buf */ = arguments->slots[0];
  // 225: retrieve_variables
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = frame->slots[1] /* retrieve_variables */;
  func = myself->type;
  frame->cont = cont__107_68;
}
static void cont__107_68(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 226: ... info_variables.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__info_variables();
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__107_69;
}
static void cont__107_69(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 226: ... :
  // 227:   write_to &buf "
  // 228:     @
  // 229:       report__event("@(event_name)");
  // 230:   print_variables
  frame->slots[4] /* temp__2 */ = create_closure(entry__107_70, 0);
  // 226: unless info_variables.is_empty:
  // 227:   write_to &buf "
  // 228:     @
  // 229:       report__event("@(event_name)");
  // 230:   print_variables
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__107_40(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // buf: 0
  // indent: 1
  // name: 2
  frame->slots[0] = myself->closure.frame->slots[1]; /* buf */
  frame->slots[1] = myself->closure.frame->slots[2]; /* indent */
  frame->slots[2] = myself->closure.frame->slots[4]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 208: ... "print__pointer(@(name));"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__32285b242638aa20;
  arguments->slots[1] = frame->slots[2] /* name */;
  arguments->slots[2] = string__2d7981f4e6402bfe;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__107_42;
}
static void cont__107_42(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 208: writeln_to &buf indent "print__pointer(@(name));"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* buf */;
  arguments->slots[1] = frame->slots[1] /* indent */;
  arguments->slots[2] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__writeln_to();
  func = myself->type;
  frame->cont = cont__107_43;
}
static void cont__107_43(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* buf */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__107_44(void) {
  allocate_initialized_frame_gc(4, 6);
  // slot allocations:
  // buf: 0
  // indent: 1
  // name: 2
  // var: 3
  frame->slots[0] = myself->closure.frame->slots[1]; /* buf */
  frame->slots[1] = myself->closure.frame->slots[2]; /* indent */
  frame->slots[2] = myself->closure.frame->slots[4]; /* name */
  frame->slots[3] = myself->closure.frame->slots[0]; /* var */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 210: ... var(3)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__3;
  result_count = 1;
  myself = frame->slots[3] /* var */;
  func = myself->type;
  frame->cont = cont__107_45;
}
static void cont__107_45(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 210: ... "print__int_array(@(name), @(var(3)));"
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = string__8eee524608dfba81;
  arguments->slots[1] = frame->slots[2] /* name */;
  arguments->slots[2] = string__2d7981f4e6682be5;
  arguments->slots[3] = frame->slots[5] /* temp__2 */;
  arguments->slots[4] = string__2d7981f4e6402bfe;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__107_47;
}
static void cont__107_47(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 210: writeln_to &buf indent "print__int_array(@(name), @(var(3)));"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* buf */;
  arguments->slots[1] = frame->slots[1] /* indent */;
  arguments->slots[2] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__writeln_to();
  func = myself->type;
  frame->cont = cont__107_48;
}
static void cont__107_48(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* buf */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__107_49(void) {
  allocate_initialized_frame_gc(4, 6);
  // slot allocations:
  // buf: 0
  // indent: 1
  // name: 2
  // var: 3
  frame->slots[0] = myself->closure.frame->slots[1]; /* buf */
  frame->slots[1] = myself->closure.frame->slots[2]; /* indent */
  frame->slots[2] = myself->closure.frame->slots[4]; /* name */
  frame->slots[3] = myself->closure.frame->slots[0]; /* var */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 212: ... var(3)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__3;
  result_count = 1;
  myself = frame->slots[3] /* var */;
  func = myself->type;
  frame->cont = cont__107_50;
}
static void cont__107_50(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 212: ... "print__memory(@(name), @(var(3)));"
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = string__173507c00b84c49d;
  arguments->slots[1] = frame->slots[2] /* name */;
  arguments->slots[2] = string__2d7981f4e6682be5;
  arguments->slots[3] = frame->slots[5] /* temp__2 */;
  arguments->slots[4] = string__2d7981f4e6402bfe;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__107_52;
}
static void cont__107_52(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 212: writeln_to &buf indent "print__memory(@(name), @(var(3)));"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* buf */;
  arguments->slots[1] = frame->slots[1] /* indent */;
  arguments->slots[2] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__writeln_to();
  func = myself->type;
  frame->cont = cont__107_53;
}
static void cont__107_53(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* buf */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__107_54(void) {
  allocate_initialized_frame_gc(4, 5);
  // slot allocations:
  // buf: 0
  // indent: 1
  // type: 2
  // name: 3
  frame->slots[0] = myself->closure.frame->slots[1]; /* buf */
  frame->slots[1] = myself->closure.frame->slots[2]; /* indent */
  frame->slots[2] = myself->closure.frame->slots[3]; /* type */
  frame->slots[3] = myself->closure.frame->slots[4]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 214: ... "print__@(type)(@(name));"
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = string__ae4408db944250a5;
  arguments->slots[1] = frame->slots[2] /* type */;
  arguments->slots[2] = string__578a5af303e9cc9;
  arguments->slots[3] = frame->slots[3] /* name */;
  arguments->slots[4] = string__2d7981f4e6402bfe;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__107_57;
}
static void cont__107_57(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 214: writeln_to &buf indent "print__@(type)(@(name));"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* buf */;
  arguments->slots[1] = frame->slots[1] /* indent */;
  arguments->slots[2] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__writeln_to();
  func = myself->type;
  frame->cont = cont__107_58;
}
static void cont__107_58(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* buf */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__107_37(void) {
  allocate_initialized_frame_gc(3, 9);
  // slot allocations:
  // var: 0
  // buf: 1
  // indent: 2
  // type: 3
  // name: 4
  frame->slots[1] = myself->closure.frame->slots[0]; /* buf */
  frame->slots[2] = myself->closure.frame->slots[1]; /* indent */
  frame->slots[3] /* type */ = create_future();
  frame->slots[4] /* name */ = create_future();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 203: $type var(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* var */;
  func = myself->type;
  frame->cont = cont__107_38;
}
static void cont__107_38(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* type */, arguments->slots[0]);
  // 204: $name var(2)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = frame->slots[0] /* var */;
  func = myself->type;
  frame->cont = cont__107_39;
}
static void cont__107_39(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* name */, arguments->slots[0]);
  // 207: ... :
  // 208:   writeln_to &buf indent "print__pointer(@(name));"
  frame->slots[5] /* temp__1 */ = create_closure(entry__107_40, 0);
  // 209: ... :
  // 210:   writeln_to &buf indent "print__int_array(@(name), @(var(3)));"
  frame->slots[6] /* temp__2 */ = create_closure(entry__107_44, 0);
  // 211: ... :
  // 212:   writeln_to &buf indent "print__memory(@(name), @(var(3)));"
  frame->slots[7] /* temp__3 */ = create_closure(entry__107_49, 0);
  // 213: :
  // 214:   writeln_to &buf indent "print__@(type)(@(name));"
  frame->slots[8] /* temp__4 */ = create_closure(entry__107_54, 0);
  // 205: case
  // 206:   type
  // 207:   "pointer":
  // 208:     writeln_to &buf indent "print__pointer(@(name));"
  // 209:   "int_array":
  // 210:     writeln_to &buf indent "print__int_array(@(name), @(var(3)));"
  // 211:   "memory":
  // 212:     writeln_to &buf indent "print__memory(@(name), @(var(3)));"
  // 213:   :
  // 214:     writeln_to &buf indent "print__@(type)(@(name));"
  argument_count = 8;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* type */;
  arguments->slots[1] = string__ae4408d515925088;
  arguments->slots[2] = frame->slots[5] /* temp__1 */;
  arguments->slots[3] = string__4ae022330b0b651c;
  arguments->slots[4] = frame->slots[6] /* temp__2 */;
  arguments->slots[5] = string__421f5586012a02ae;
  arguments->slots[6] = frame->slots[7] /* temp__3 */;
  arguments->slots[7] = frame->slots[8] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__107_13(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // buf: 0
  // indent: 1
  // name: 2
  frame->slots[0] = myself->closure.frame->slots[1]; /* buf */
  frame->slots[1] = myself->closure.frame->slots[2]; /* indent */
  frame->slots[2] = myself->closure.frame->slots[4]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 186: ... "retrieve__pointer((void **)&@(name));"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__3802f8268029fd6c;
  arguments->slots[1] = frame->slots[2] /* name */;
  arguments->slots[2] = string__2d7981f4e6402bfe;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__107_15;
}
static void cont__107_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 186: writeln_to &buf indent "retrieve__pointer((void **)&@(name));"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* buf */;
  arguments->slots[1] = frame->slots[1] /* indent */;
  arguments->slots[2] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__writeln_to();
  func = myself->type;
  frame->cont = cont__107_16;
}
static void cont__107_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* buf */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__107_17(void) {
  allocate_initialized_frame_gc(4, 6);
  // slot allocations:
  // buf: 0
  // indent: 1
  // var: 2
  // name: 3
  frame->slots[0] = myself->closure.frame->slots[1]; /* buf */
  frame->slots[1] = myself->closure.frame->slots[2]; /* indent */
  frame->slots[2] = myself->closure.frame->slots[0]; /* var */
  frame->slots[3] = myself->closure.frame->slots[4]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 191: ... var(3)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__3;
  result_count = 1;
  myself = frame->slots[2] /* var */;
  func = myself->type;
  frame->cont = cont__107_18;
}
static void cont__107_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 191: "@(var(3)) = retrieve__int_array((int **)&@(name));"
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  arguments->slots[1] = string__30c5044d97434308;
  arguments->slots[2] = frame->slots[3] /* name */;
  arguments->slots[3] = string__2d7981f4e6402bfe;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__107_20;
}
static void cont__107_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 188: writeln_to
  // 189:   &buf
  // 190:   indent
  // 191:   "@(var(3)) = retrieve__int_array((int **)&@(name));"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* buf */;
  arguments->slots[1] = frame->slots[1] /* indent */;
  arguments->slots[2] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__writeln_to();
  func = myself->type;
  frame->cont = cont__107_21;
}
static void cont__107_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* buf */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__107_22(void) {
  allocate_initialized_frame_gc(4, 6);
  // slot allocations:
  // buf: 0
  // indent: 1
  // var: 2
  // name: 3
  frame->slots[0] = myself->closure.frame->slots[1]; /* buf */
  frame->slots[1] = myself->closure.frame->slots[2]; /* indent */
  frame->slots[2] = myself->closure.frame->slots[0]; /* var */
  frame->slots[3] = myself->closure.frame->slots[4]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 196: ... var(3)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__3;
  result_count = 1;
  myself = frame->slots[2] /* var */;
  func = myself->type;
  frame->cont = cont__107_23;
}
static void cont__107_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 196: "@(var(3)) = retrieve__memory((uint8_t **)&@(name));"
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  arguments->slots[1] = string__4ff2866267e10016;
  arguments->slots[2] = frame->slots[3] /* name */;
  arguments->slots[3] = string__2d7981f4e6402bfe;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__107_25;
}
static void cont__107_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 193: writeln_to
  // 194:   &buf
  // 195:   indent
  // 196:   "@(var(3)) = retrieve__memory((uint8_t **)&@(name));"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* buf */;
  arguments->slots[1] = frame->slots[1] /* indent */;
  arguments->slots[2] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__writeln_to();
  func = myself->type;
  frame->cont = cont__107_26;
}
static void cont__107_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* buf */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__107_27(void) {
  allocate_initialized_frame_gc(4, 5);
  // slot allocations:
  // buf: 0
  // indent: 1
  // type: 2
  // name: 3
  frame->slots[0] = myself->closure.frame->slots[1]; /* buf */
  frame->slots[1] = myself->closure.frame->slots[2]; /* indent */
  frame->slots[2] = myself->closure.frame->slots[3]; /* type */
  frame->slots[3] = myself->closure.frame->slots[4]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 198: ... "retrieve__@(type)(&@(name));"
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = string__192c815f22d3275e;
  arguments->slots[1] = frame->slots[2] /* type */;
  arguments->slots[2] = string__2d7981f4e6482be3;
  arguments->slots[3] = frame->slots[3] /* name */;
  arguments->slots[4] = string__2d7981f4e6402bfe;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__107_30;
}
static void cont__107_30(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 198: writeln_to &buf indent "retrieve__@(type)(&@(name));"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* buf */;
  arguments->slots[1] = frame->slots[1] /* indent */;
  arguments->slots[2] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__writeln_to();
  func = myself->type;
  frame->cont = cont__107_31;
}
static void cont__107_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* buf */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__107_10(void) {
  allocate_initialized_frame_gc(3, 9);
  // slot allocations:
  // var: 0
  // buf: 1
  // indent: 2
  // type: 3
  // name: 4
  frame->slots[1] = myself->closure.frame->slots[0]; /* buf */
  frame->slots[2] = myself->closure.frame->slots[1]; /* indent */
  frame->slots[3] /* type */ = create_future();
  frame->slots[4] /* name */ = create_future();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 181: $type var(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* var */;
  func = myself->type;
  frame->cont = cont__107_11;
}
static void cont__107_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* type */, arguments->slots[0]);
  // 182: $name var(2)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = frame->slots[0] /* var */;
  func = myself->type;
  frame->cont = cont__107_12;
}
static void cont__107_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* name */, arguments->slots[0]);
  // 185: ... :
  // 186:   writeln_to &buf indent "retrieve__pointer((void **)&@(name));"
  frame->slots[5] /* temp__1 */ = create_closure(entry__107_13, 0);
  // 187: ... :
  // 188:   writeln_to
  // 189:     &buf
  // 190:     indent
  // 191:     "@(var(3)) = retrieve__int_array((int **)&@(name));"
  frame->slots[6] /* temp__2 */ = create_closure(entry__107_17, 0);
  // 192: ... :
  // 193:   writeln_to
  // 194:     &buf
  // 195:     indent
  // 196:     "@(var(3)) = retrieve__memory((uint8_t **)&@(name));"
  frame->slots[7] /* temp__3 */ = create_closure(entry__107_22, 0);
  // 197: :
  // 198:   writeln_to &buf indent "retrieve__@(type)(&@(name));"
  frame->slots[8] /* temp__4 */ = create_closure(entry__107_27, 0);
  // 183: case
  // 184:   type
  // 185:   "pointer":
  // 186:     writeln_to &buf indent "retrieve__pointer((void **)&@(name));"
  // 187:   "int_array":
  // 188:     writeln_to
  // 189:       &buf
  // 190:       indent
  // 191:       "@(var(3)) = retrieve__int_array((int **)&@(name));"
  // 192:   "memory":
  // ...
  argument_count = 8;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* type */;
  arguments->slots[1] = string__ae4408d515925088;
  arguments->slots[2] = frame->slots[5] /* temp__1 */;
  arguments->slots[3] = string__4ae022330b0b651c;
  arguments->slots[4] = frame->slots[6] /* temp__2 */;
  arguments->slots[5] = string__421f5586012a02ae;
  arguments->slots[6] = frame->slots[7] /* temp__3 */;
  arguments->slots[7] = frame->slots[8] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__107_3(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // buf: 0
  // indent: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* buf */
  frame->slots[1] /* indent */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 179: ... event_kind == ACTION
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__event_kind();
  arguments->slots[1] = var._ACTION;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__107_4;
}
static void cont__107_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 179: $indent if(event_kind == ACTION (-> "      ") -> "  ")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = func__107_5;
  arguments->slots[2] = func__107_7;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__107_9;
}
static void entry__107_5(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 179: ... -> "      "
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__d81f466083be52f7;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__107_7(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 179: ... -> "  "
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e6082be5;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__107_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* indent */, arguments->slots[0]);
  // 180: ... : (var)
  // 181:   $type var(1)
  // 182:   $name var(2)
  // 183:   case
  // 184:     type
  // 185:     "pointer":
  // 186:       writeln_to &buf indent "retrieve__pointer((void **)&@(name));"
  // 187:     "int_array":
  // 188:       writeln_to
  // 189:         &buf
  // ...
  frame->slots[2] /* temp__1 */ = create_closure(entry__107_10, 1);
  // 180: for_each data_variables: (var)
  // 181:   $type var(1)
  // 182:   $name var(2)
  // 183:   case
  // 184:     type
  // 185:     "pointer":
  // 186:       writeln_to &buf indent "retrieve__pointer((void **)&@(name));"
  // 187:     "int_array":
  // 188:       writeln_to
  // 189:         &buf
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__data_variables();
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__107_32(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // buf: 0
  // indent: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* buf */
  frame->slots[1] /* indent */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 201: ... event_kind == ACTION
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__event_kind();
  arguments->slots[1] = var._ACTION;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__107_33;
}
static void cont__107_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 201: $indent if(event_kind == ACTION (-> "      ") -> "  ")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = func__107_34;
  arguments->slots[2] = func__107_35;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__107_36;
}
static void entry__107_34(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 201: ... -> "      "
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__d81f466083be52f7;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__107_35(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 201: ... -> "  "
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e6082be5;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__107_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* indent */, arguments->slots[0]);
  // 202: ... : (var)
  // 203:   $type var(1)
  // 204:   $name var(2)
  // 205:   case
  // 206:     type
  // 207:     "pointer":
  // 208:       writeln_to &buf indent "print__pointer(@(name));"
  // 209:     "int_array":
  // 210:       writeln_to &buf indent "print__int_array(@(name), @(var(3)));"
  // 211:     "memory":
  // ...
  frame->slots[2] /* temp__1 */ = create_closure(entry__107_37, 1);
  // 202: for_each info_variables: (var)
  // 203:   $type var(1)
  // 204:   $name var(2)
  // 205:   case
  // 206:     type
  // 207:     "pointer":
  // 208:       writeln_to &buf indent "print__pointer(@(name));"
  // 209:     "int_array":
  // 210:       writeln_to &buf indent "print__int_array(@(name), @(var(3)));"
  // 211:     "memory":
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__info_variables();
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__107_59(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // buf: 0
  // retrieve_variables: 1
  // print_variables: 2
  frame->slots[0] = myself->closure.frame->slots[2]; /* buf */
  frame->slots[1] = myself->closure.frame->slots[0]; /* retrieve_variables */
  frame->slots[2] = myself->closure.frame->slots[1]; /* print_variables */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 218: ... event_kind == EVENT
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__event_kind();
  arguments->slots[1] = var._EVENT;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__107_60;
}
static void cont__107_60(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 218: ... :
  // 219:   write_to &buf "
  // 220:       }
  // 221:     } else {
  // 222:   write_to &buf "
  // 223:     @
  // 224:       replay__event("@(event_name)");
  // 225:   retrieve_variables
  // 226:   unless info_variables.is_empty:
  // 227:     write_to &buf "
  // ...
  frame->slots[4] /* temp__2 */ = create_closure(entry__107_61, 0);
  // 218: -> event_kind == EVENT:
  // 219:   write_to &buf "
  // 220:       }
  // 221:     } else {
  // 222:   write_to &buf "
  // 223:     @
  // 224:       replay__event("@(event_name)");
  // 225:   retrieve_variables
  // 226:   unless info_variables.is_empty:
  // 227:     write_to &buf "
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__107_74(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // buf: 0
  // retrieve_variables: 1
  // print_variables: 2
  frame->slots[0] = myself->closure.frame->slots[2]; /* buf */
  frame->slots[1] = myself->closure.frame->slots[0]; /* retrieve_variables */
  frame->slots[2] = myself->closure.frame->slots[1]; /* print_variables */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 231: ... length_of(data_variables)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__data_variables();
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__107_75;
}
static void cont__107_75(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 231: ... length_of(data_variables) > 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__107_76;
}
static void cont__107_76(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 231: ... :
  // 232:   write_to &buf "
  // 233:     @
  // 234:         }
  // 235:       } else {
  // 236:   write_to &buf "
  // 237:     @
  // 238:         if (replay__action("@(event_name)")) {
  // 239:   retrieve_variables
  // 240:   writeln_to &buf "  } else {"
  // ...
  frame->slots[5] /* temp__3 */ = create_closure(entry__107_77, 0);
  // 231: -> length_of(data_variables) > 0:
  // 232:   write_to &buf "
  // 233:     @
  // 234:         }
  // 235:       } else {
  // 236:   write_to &buf "
  // 237:     @
  // 238:         if (replay__action("@(event_name)")) {
  // 239:   retrieve_variables
  // 240:   writeln_to &buf "  } else {"
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__107_105(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 254: write_to &buf '}'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* buf */;
  arguments->slots[1] = character__125;
  result_count = 1;
  myself = get__write_to();
  func = myself->type;
  frame->cont = cont__107_106;
}
static void cont__107_106(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* buf */ = arguments->slots[0];
  // 255: -> buf
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* buf */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__107_107(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 256: define_macro "UNDEFINED" "undefined"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__3c202d3e36291121;
  arguments->slots[1] = string__7ca0252e172b1501;
  result_count = 0;
  myself = var._define_macro;
  func = myself->type;
  frame->cont = cont__108_3;
}
static void cont__108_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 257: define_macro "ZERO" "zero"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__760ae00b5cf07d76;
  arguments->slots[1] = string__360ae80b5df07d56;
  result_count = 0;
  myself = var._define_macro;
  func = myself->type;
  frame->cont = cont__109_3;
}
static void cont__109_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 258: define_macro "TRUE" "boolean_true"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__6a0ae5cb5cc87d7c;
  arguments->slots[1] = string__62d904ca56abf62f;
  result_count = 0;
  myself = var._define_macro;
  func = myself->type;
  frame->cont = cont__110_3;
}
static void cont__110_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 259: define_macro "FALSE" "boolean_false"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__85ae003eb527012;
  arguments->slots[1] = string__52b31fb1ca36ad;
  result_count = 0;
  myself = var._define_macro;
  func = myself->type;
  frame->cont = cont__111_3;
}
static void cont__111_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 260: define_macro "EMPTY_STRING" "empty_string"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__ae20f214ef3d4185;
  arguments->slots[1] = string__ee21fa04ce7f45ad;
  result_count = 0;
  myself = var._define_macro;
  func = myself->type;
  frame->cont = cont__112_3;
}
static void cont__112_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 261: define_macro "ARGUMENTS" "arguments->slots[$1]"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__242c2d3622a1a2b6;
  arguments->slots[1] = string__bdf1fe7d3fa3f48e;
  result_count = 0;
  myself = var._define_macro;
  func = myself->type;
  frame->cont = cont__113_3;
}
static void cont__113_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 262: define_macro "TYPE" "type__$1"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__6a0ae70b5ce07d7c;
  arguments->slots[1] = string__10f0a21e06f5c291;
  result_count = 0;
  myself = var._define_macro;
  func = myself->type;
  frame->cont = cont__114_3;
}
static void cont__114_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 263: define_macro "TYPEOF" "($1)->type"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__381f5f1a80c1c291;
  arguments->slots[1] = string__1c42567d62ae9fc4;
  result_count = 0;
  myself = var._define_macro;
  func = myself->type;
  frame->cont = cont__115_3;
}
static void cont__115_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 264: define_macro "SIZEOF" "($1)->attributes->vtable->size"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2c1f5f1900c0c291;
  arguments->slots[1] = string__c207e6e98f96cbad;
  result_count = 0;
  myself = var._define_macro;
  func = myself->type;
  frame->cont = cont__116_3;
}
static void cont__116_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 265: define_macro "RETURN_NOTHING" "
  // 266:   {
  // 267:     argument_count = 0;
  // 268:     func = frame->cont;
  // 269:     frame->cont = invalid_continuation;
  // 270:     return;
  // 271:   }@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__88b83a651b4554fc;
  arguments->slots[1] = string__e713ee46cfe40ca0;
  result_count = 0;
  myself = var._define_macro;
  func = myself->type;
  frame->cont = cont__117_3;
}
static void cont__117_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 272: define_macro "RETURN_SINGLE_RESULT" "
  // 273:   {
  // 274:     NODE *result__node = (NODE *)($1);
  // 275:     arguments = node_p;
  // 276:     arguments->slots[0] = result__node;
  // 277:     argument_count = 1;
  // 278:     func = frame->cont;
  // 279:     frame->cont = invalid_continuation;
  // 280:     return;
  // 281:   }@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__75924e59eefc3c27;
  arguments->slots[1] = string__c9e5fa593f26b652;
  result_count = 0;
  myself = var._define_macro;
  func = myself->type;
  frame->cont = cont__118_3;
}
static void cont__118_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 282: define_macro "RETURN_BOOLEAN" "RETURN_SINGLE_RESULT(from_bool($1))"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__808839651b3ce4f5;
  arguments->slots[1] = string__76174d28d266419;
  result_count = 0;
  myself = var._define_macro;
  func = myself->type;
  frame->cont = cont__119_3;
}
static void cont__119_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 283: define_macro "RETURN_UNDEFINED" "
  // 284:   {
  // 285:     arguments = node_p;
  // 286:     arguments->slots[0] = undefined;
  // 287:     argument_count = 1;
  // 288:     func = frame->cont;
  // 289:     frame->cont = invalid_continuation;
  // 290:     return;
  // 291:   }@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__df153d64b7266922;
  arguments->slots[1] = string__a89eeef2e6ec47d6;
  result_count = 0;
  myself = var._define_macro;
  func = myself->type;
  frame->cont = cont__120_3;
}
static void cont__120_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 292: define_macro "RETURN_TRUE" "
  // 293:   {
  // 294:     arguments = node_p;
  // 295:     arguments->slots[0] = boolean_true;
  // 296:     argument_count = 1;
  // 297:     func = frame->cont;
  // 298:     frame->cont = invalid_continuation;
  // 299:     return;
  // 300:   }@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__681415cc9aa25dc9;
  arguments->slots[1] = string__62013454820fcbb4;
  result_count = 0;
  myself = var._define_macro;
  func = myself->type;
  frame->cont = cont__121_3;
}
static void cont__121_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 301: define_macro "RETURN_FALSE" "
  // 302:   {
  // 303:     arguments = node_p;
  // 304:     arguments->slots[0] = boolean_false;
  // 305:     argument_count = 1;
  // 306:     func = frame->cont;
  // 307:     frame->cont = invalid_continuation;
  // 308:     return;
  // 309:   }@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__8864d352eefa60e5;
  arguments->slots[1] = string__e7e98d9fbc185a2b;
  result_count = 0;
  myself = var._define_macro;
  func = myself->type;
  frame->cont = cont__122_3;
}
static void cont__122_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 310: define_macro "RETURN_ZERO" "
  // 311:   {
  // 312:     arguments = node_p;
  // 313:     arguments->slots[0] = zero;
  // 314:     argument_count = 1;
  // 315:     func = frame->cont;
  // 316:     frame->cont = invalid_continuation;
  // 317:     return;
  // 318:   }@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__7414100c9a9a5dc3;
  arguments->slots[1] = string__d0d6524fe2f4619c;
  result_count = 0;
  myself = var._define_macro;
  func = myself->type;
  frame->cont = cont__123_3;
}
static void cont__123_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 319: define_macro "START_ARGUMENTS" "
  // 320:   argument_count = $1;
  // 321:   arguments = node_p;@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__4388537a39721213;
  arguments->slots[1] = string__85e7f27c75b002fc;
  result_count = 0;
  myself = var._define_macro;
  func = myself->type;
  frame->cont = cont__124_3;
}
static void cont__124_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 322: define_macro "RETURN" "
  // 323:   {
  // 324:     func = frame->cont;
  // 325:     frame->cont = invalid_continuation;
  // 326:     return;
  // 327:   }@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__301f5b1980280299;
  arguments->slots[1] = string__f4e01cf5f7a8d221;
  result_count = 0;
  myself = var._define_macro;
  func = myself->type;
  frame->cont = cont__125_3;
}
static void cont__125_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 328: define_macro "CHAIN" "
  // 329:   {
  // 330:     func = myself->type;
  // 331:     return;
  // 332:   }@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__1a5ae343eb822019;
  arguments->slots[1] = string__ab6aca91eb0633a9;
  result_count = 0;
  myself = var._define_macro;
  func = myself->type;
  frame->cont = cont__126_3;
}
static void cont__126_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 336: define_macro "UNRECOVERABLE_ERROR" "unrecoverable_error($*);"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__690816604df6099f;
  arguments->slots[1] = string__7a5a4cdb9d9e0e09;
  result_count = 0;
  myself = var._define_macro;
  func = myself->type;
  frame->cont = cont__127_3;
}
static void cont__127_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 337: define_macro "OUT_OF_MEMORY_ERROR" "out_of_memory_error();"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__adfe76f306663a82;
  arguments->slots[1] = string__55fab4fde7164944;
  result_count = 0;
  myself = var._define_macro;
  func = myself->type;
  frame->cont = cont__128_3;
}
static void cont__128_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 341: define_macro "RUNTIME_ERROR" "
  // 342:   {
  // 343:     runtime_error($*);
  // 344:   }@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__26ff7f9f9c5c0312;
  arguments->slots[1] = string__7317d013e72f1e80;
  result_count = 0;
  myself = var._define_macro;
  func = myself->type;
  frame->cont = cont__129_3;
}
static void cont__129_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 345: define_macro "TOO_FEW_ARGUMENTS_ERROR" "
  // 346:   {
  // 347:     too_few_arguments_error();
  // 348:   }@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__fce3f40028924a51;
  arguments->slots[1] = string__64a4d424679d8650;
  result_count = 0;
  myself = var._define_macro;
  func = myself->type;
  frame->cont = cont__130_3;
}
static void cont__130_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 349: define_macro "TOO_MANY_ARGUMENTS_ERROR" "
  // 350:   {
  // 351:     too_many_arguments_error();
  // 352:   }@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__aab70cfc8956db67;
  arguments->slots[1] = string__e8cfae9434301166;
  result_count = 0;
  myself = var._define_macro;
  func = myself->type;
  frame->cont = cont__131_3;
}
static void cont__131_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 353: define_macro "INVALID_ARGUMENTS_ERROR" "
  // 354:   {
  // 355:     invalid_arguments_error();
  // 356:   }@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__6cf0c8742a12ca30;
  arguments->slots[1] = string__65e49414af94386a;
  result_count = 0;
  myself = var._define_macro;
  func = myself->type;
  frame->cont = cont__132_3;
}
static void cont__132_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 357: define_macro "TOO_FEW_RESULTS_ERROR" "
  // 358:   {
  // 359:     too_few_results_error();
  // 360:   }@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__1adfaddd8e34edf5;
  arguments->slots[1] = string__e77c83ca19b4e164;
  result_count = 0;
  myself = var._define_macro;
  func = myself->type;
  frame->cont = cont__133_3;
}
static void cont__133_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 361: define_macro "TOO_MANY_RESULTS_ERROR" "
  // 362:   {
  // 363:     too_many_results_error();
  // 364:   }@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__e858bf99576dbe16;
  arguments->slots[1] = string__26323596c3854c8e;
  result_count = 0;
  myself = var._define_macro;
  func = myself->type;
  frame->cont = cont__134_3;
}
static void cont__134_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 365: define_macro "INVALID_RESULTS_ERROR" "
  // 366:   {
  // 367:     invalid_results_error();
  // 368:   }@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__cad5afdc0874a104;
  arguments->slots[1] = string__245ca532f1b1e064;
  result_count = 0;
  myself = var._define_macro;
  func = myself->type;
  frame->cont = cont__135_3;
}
static void cont__135_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 369: define_macro "INVALID_INDEX_ERROR" "
  // 370:   {
  // 371:     invalid_index_error();
  // 372:   }@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__aa786f40ccc234b9;
  arguments->slots[1] = string__b633324328a52c38;
  result_count = 0;
  myself = var._define_macro;
  func = myself->type;
  frame->cont = cont__136_3;
}
static void cont__136_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 373: define_macro "DIVIDE_BY_ZERO_ERROR" "
  // 374:   {
  // 375:     divide_by_zero_error();
  // 376:   }@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__37ce8a8da4c412d5;
  arguments->slots[1] = string__b69de9e24cd9d6a2;
  result_count = 0;
  myself = var._define_macro;
  func = myself->type;
  frame->cont = cont__137_3;
}
static void cont__137_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 377: define_macro "NOT_YET_IMPLEMENTED_ERROR" "
  // 378:   {
  // 379:     not_yet_implemented_error();
  // 380:   }@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__221e44965d54351b;
  arguments->slots[1] = string__13951d152a225118;
  result_count = 0;
  myself = var._define_macro;
  func = myself->type;
  frame->cont = cont__138_3;
}
static void cont__138_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 381: define_macro "NO_SUCH_FUNCTION_ERROR" "
  // 382:   {
  // 383:     no_such_function_error();
  // 384:   }@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__e4ae97e99176a5b2;
  arguments->slots[1] = string__413ff844cdfe78b6;
  result_count = 0;
  myself = var._define_macro;
  func = myself->type;
  frame->cont = cont__139_3;
}
static void cont__139_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 385: define_macro "RESOURCE_ERROR" "
  // 386:   {
  // 387:     resource_error();
  // 388:   }@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__3c9404ad0742476f;
  arguments->slots[1] = string__6a3612ac9bfecfbc;
  result_count = 0;
  myself = var._define_macro;
  func = myself->type;
  frame->cont = cont__140_3;
}
static void cont__140_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 389: define_macro "IO_ERROR" "
  // 390:   {
  // 391:     io_error();
  // 392:   }@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__a28a14985afc552;
  arguments->slots[1] = string__1f25251097233e14;
  result_count = 0;
  myself = var._define_macro;
  func = myself->type;
  frame->cont = cont__141_3;
}
static void cont__141_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__define_macro_1(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // name: 0
  // replacement: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 41: ... !macro_replacements(name) replacement
  frame->slots[2] /* temp__1 */ = frame->slots[1] /* replacement */;
  // 41: ... !macro_replacements(name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = var._macro_replacements;
  func = myself->type;
  frame->cont = cont__define_macro_2;
}
static void cont__define_macro_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._macro_replacements = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__converted_1(void) {
  allocate_initialized_frame_gc(2, 12);
  // slot allocations:
  // code: 0
  // return__1: 1
  // new_code: 2
  // start: 3
  // within_string: 4
  // s: 5
  // i: 6
  // len: 7
  frame->slots[1] /* return__1 */ = create_continuation();
  define__event_name(undefined);
  define__event_kind(undefined);
  define__data_variables(undefined);
  define__info_variables(undefined);
  frame->slots[2] /* new_code */ = create_cell();
  frame->slots[3] /* start */ = create_cell();
  frame->slots[4] /* within_string */ = create_cell();
  frame->slots[5] /* s */ = create_cell();
  frame->slots[6] /* i */ = create_cell();
  frame->slots[7] /* len */ = create_future();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* code */ = create_cell_with_contents(arguments->slots[0]);
  // 395: %%event_name undefined
  set__event_name(get__undefined());
  // 396: %%event_kind undefined
  set__event_kind(get__undefined());
  // 397: %%data_variables empty_list
  set__data_variables(get__empty_list());
  // 398: %%info_variables empty_list
  set__info_variables(get__empty_list());
  // 399: push &code '@nl;' # add sentinel
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* code */;
  arguments->slots[1] = character__10;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__converted_2;
}
static void cont__compiler__converted_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* code */ = arguments->slots[0];
  // 400: $$new_code ""
  ((CELL *)frame->slots[2])->contents /* new_code */ = empty_string;
  // 401: $$start 1
  ((CELL *)frame->slots[3])->contents /* start */ = number__1;
  // 402: $$within_string false
  ((CELL *)frame->slots[4])->contents /* within_string */ = get__false();
  // 403: $$s undefined
  ((CELL *)frame->slots[5])->contents /* s */ = get__undefined();
  // 404: $$i 1
  ((CELL *)frame->slots[6])->contents /* i */ = number__1;
  // 405: $len length_of(code)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* code */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__compiler__converted_3;
}
static void cont__compiler__converted_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[7] /* len */, arguments->slots[0]);
  // 406: ... -> i <= len:
  // 407:   if
  // 408:     within_string:
  // 409:       case code(i) '@quot;': if code(i-1) != '\': !within_string false
  // 410:       inc &i
  // 411:     :
  // 412:       $chr code(i)
  // 413:       case
  // 414:         chr
  // 415:         '_', 'a' .. 'z', 'A' .. 'Z':
  // ...
  frame->slots[8] /* temp__1 */ = create_closure(entry__compiler__converted_4, 0);
  // 406: while -> i <= len:
  // 407:   if
  // 408:     within_string:
  // 409:       case code(i) '@quot;': if code(i-1) != '\': !within_string false
  // 410:       inc &i
  // 411:     :
  // 412:       $chr code(i)
  // 413:       case
  // 414:         chr
  // 415:         '_', 'a' .. 'z', 'A' .. 'Z':
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__1 */;
  result_count = 0;
  myself = get__while();
  func = myself->type;
  frame->cont = cont__compiler__converted_144;
}
static void entry__compiler__converted_8(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // code: 0
  // i: 1
  // within_string: 2
  frame->slots[0] = myself->closure.frame->slots[1]; /* code */
  frame->slots[1] = myself->closure.frame->slots[2]; /* i */
  frame->slots[2] = myself->closure.frame->slots[0]; /* within_string */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 409: ... code(i)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* i */;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* code */;
  func = myself->type;
  frame->cont = cont__compiler__converted_9;
}
static void cont__compiler__converted_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 409: ... : if code(i-1) != '\': !within_string false
  frame->slots[4] /* temp__2 */ = create_closure(entry__compiler__converted_10, 0);
  // 409: case code(i) '@quot;': if code(i-1) != '\': !within_string false
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = character__34;
  arguments->slots[2] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__case();
  func = myself->type;
  frame->cont = cont__compiler__converted_16;
}
static void entry__compiler__converted_15(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // within_string: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* within_string */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 409: ... !within_string false
  ((CELL *)frame->slots[0])->contents /* within_string */ = get__false();
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__converted_10(void) {
  allocate_initialized_frame_gc(3, 8);
  // slot allocations:
  // code: 0
  // i: 1
  // within_string: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* code */
  frame->slots[1] = myself->closure.frame->slots[1]; /* i */
  frame->slots[2] = myself->closure.frame->slots[2]; /* within_string */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 409: ... i-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* i */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__compiler__converted_11;
}
static void cont__compiler__converted_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__4 */ = arguments->slots[0];
  // 409: ... code(i-1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__4 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* code */;
  func = myself->type;
  frame->cont = cont__compiler__converted_12;
}
static void cont__compiler__converted_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 409: ... code(i-1) != '\'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__3 */;
  arguments->slots[1] = character__92;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__compiler__converted_13;
}
static void cont__compiler__converted_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 409: ... code(i-1) != '\'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__compiler__converted_14;
}
static void cont__compiler__converted_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 409: ... : !within_string false
  frame->slots[7] /* temp__5 */ = create_closure(entry__compiler__converted_15, 0);
  // 409: ... if code(i-1) != '\': !within_string false
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__5 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__converted_16(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 410: inc &i
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* i */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__compiler__converted_17;
}
static void cont__compiler__converted_17(void) {
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
static void entry__compiler__converted_18(void) {
  allocate_initialized_frame_gc(7, 15);
  // slot allocations:
  // code: 0
  // i: 1
  // s: 2
  // within_string: 3
  // new_code: 4
  // start: 5
  // len: 6
  // chr: 7
  frame->slots[0] = myself->closure.frame->slots[1]; /* code */
  frame->slots[1] = myself->closure.frame->slots[2]; /* i */
  frame->slots[2] = myself->closure.frame->slots[3]; /* s */
  frame->slots[3] = myself->closure.frame->slots[0]; /* within_string */
  frame->slots[4] = myself->closure.frame->slots[4]; /* new_code */
  frame->slots[5] = myself->closure.frame->slots[5]; /* start */
  frame->slots[6] = myself->closure.frame->slots[6]; /* len */
  frame->slots[7] /* chr */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 412: $chr code(i)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* i */;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* code */;
  func = myself->type;
  frame->cont = cont__compiler__converted_19;
}
static void cont__compiler__converted_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[7] /* chr */, arguments->slots[0]);
  // 415: ... 'a' .. 'z'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__97;
  arguments->slots[1] = character__122;
  result_count = 1;
  myself = get__std__value_range();
  func = myself->type;
  frame->cont = cont__compiler__converted_20;
}
static void cont__compiler__converted_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__2 */ = arguments->slots[0];
  // 415: ... 'A' .. 'Z'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__65;
  arguments->slots[1] = character__90;
  result_count = 1;
  myself = get__std__value_range();
  func = myself->type;
  frame->cont = cont__compiler__converted_21;
}
static void cont__compiler__converted_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__3 */ = arguments->slots[0];
  // 415: '_', 'a' .. 'z', 'A' .. 'Z'
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = character__95;
  arguments->slots[1] = frame->slots[9] /* temp__2 */;
  arguments->slots[2] = frame->slots[10] /* temp__3 */;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__compiler__converted_22;
}
static void cont__compiler__converted_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__1 */ = arguments->slots[0];
  // 415: ... :
  // 416:   unless s.is_defined: !s i
  frame->slots[11] /* temp__4 */ = create_closure(entry__compiler__converted_23, 0);
  // 417: '0' .. '9'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__48;
  arguments->slots[1] = character__57;
  result_count = 1;
  myself = get__std__value_range();
  func = myself->type;
  frame->cont = cont__compiler__converted_26;
}
static void entry__compiler__converted_25(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // s: 0
  // i: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* s */
  frame->slots[1] = myself->closure.frame->slots[1]; /* i */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 416: ... !s i
  ((CELL *)frame->slots[0])->contents /* s */ = ((CELL *)frame->slots[1])->contents /* i */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__converted_23(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // s: 0
  // i: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* s */
  frame->slots[1] = myself->closure.frame->slots[1]; /* i */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 416: ... s.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* s */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__compiler__converted_24;
}
static void cont__compiler__converted_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 416: ... : !s i
  frame->slots[3] /* temp__2 */ = create_closure(entry__compiler__converted_25, 0);
  // 416: unless s.is_defined: !s i
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__converted_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__5 */ = arguments->slots[0];
  // 419: ... :
  // 420:   !s undefined
  // 421:   if code(i-1) != '\': !within_string true
  frame->slots[13] /* temp__6 */ = create_closure(entry__compiler__converted_27, 0);
  // 422: :
  // 423:   if s.is_defined:
  // 424:     if
  // 425:       chr == ':' && code(i+1) == ':':
  // 426:         inc &i
  // 427:       :
  // 428:         $$identifier range(code s i-1)
  // 429:         $$replacement macro_replacements(identifier)
  // 430:         if
  // 431:           replacement.is_defined:
  // ...
  frame->slots[14] /* temp__7 */ = create_closure(entry__compiler__converted_33, 0);
  // 413: case
  // 414:   chr
  // 415:   '_', 'a' .. 'z', 'A' .. 'Z':
  // 416:     unless s.is_defined: !s i
  // 417:   '0' .. '9':
  // 418:     pass
  // 419:   '@quot;':
  // 420:     !s undefined
  // 421:     if code(i-1) != '\': !within_string true
  // 422:   :
  // ...
  argument_count = 8;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* chr */;
  arguments->slots[1] = frame->slots[8] /* temp__1 */;
  arguments->slots[2] = frame->slots[11] /* temp__4 */;
  arguments->slots[3] = frame->slots[12] /* temp__5 */;
  arguments->slots[4] = func__compiler__converted_141;
  arguments->slots[5] = character__34;
  arguments->slots[6] = frame->slots[13] /* temp__6 */;
  arguments->slots[7] = frame->slots[14] /* temp__7 */;
  result_count = 0;
  myself = get__case();
  func = myself->type;
  frame->cont = cont__compiler__converted_142;
}
static void entry__compiler__converted_42(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // i: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* i */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 426: inc &i
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* i */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__compiler__converted_43;
}
static void cont__compiler__converted_43(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* i */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__converted_44(void) {
  allocate_initialized_frame_gc(6, 11);
  // slot allocations:
  // code: 0
  // s: 1
  // i: 2
  // new_code: 3
  // start: 4
  // len: 5
  // identifier: 6
  // replacement: 7
  frame->slots[0] = myself->closure.frame->slots[1]; /* code */
  frame->slots[1] = myself->closure.frame->slots[3]; /* s */
  frame->slots[2] = myself->closure.frame->slots[2]; /* i */
  frame->slots[3] = myself->closure.frame->slots[4]; /* new_code */
  frame->slots[4] = myself->closure.frame->slots[5]; /* start */
  frame->slots[5] = myself->closure.frame->slots[6]; /* len */
  frame->slots[6] /* identifier */ = create_cell();
  frame->slots[7] /* replacement */ = create_cell();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 428: ... i-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* i */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__compiler__converted_45;
}
static void cont__compiler__converted_45(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__1 */ = arguments->slots[0];
  // 428: $$identifier range(code s i-1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* code */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* s */;
  arguments->slots[2] = frame->slots[8] /* temp__1 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__compiler__converted_46;
}
static void cont__compiler__converted_46(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[6])->contents /* identifier */ = arguments->slots[0];
  // 429: $$replacement macro_replacements(identifier)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[6])->contents /* identifier */;
  result_count = 1;
  myself = var._macro_replacements;
  func = myself->type;
  frame->cont = cont__compiler__converted_47;
}
static void cont__compiler__converted_47(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[7])->contents /* replacement */ = arguments->slots[0];
  // 431: replacement.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[7])->contents /* replacement */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__compiler__converted_48;
}
static void cont__compiler__converted_48(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__1 */ = arguments->slots[0];
  // 431: ... :
  // 432:   append &new_code range(code start s-1)
  // 433:   if
  // 434:     code(i) == '(':
  // 435:       $$arguments list()
  // 436:       inc &i
  // 437:       $$a i
  // 438:       $$level 1
  // 439:       do: (-> break)
  // 440:         while -> i <= len:
  // ...
  frame->slots[9] /* temp__2 */ = create_closure(entry__compiler__converted_49, 0);
  // 488: :
  // 489:   if identifier .contains. ':':
  // 490:     replace_all &identifier "::" = "__"
  // 491:     append &new_code range(code start s-1)
  // 492:     append &new_code identifier
  // 493:     !start i
  // 494:   use_identifier identifier
  frame->slots[10] /* temp__3 */ = create_closure(entry__compiler__converted_128, 0);
  // 430: if
  // 431:   replacement.is_defined:
  // 432:     append &new_code range(code start s-1)
  // 433:     if
  // 434:       code(i) == '(':
  // 435:         $$arguments list()
  // 436:         inc &i
  // 437:         $$a i
  // 438:         $$level 1
  // 439:         do: (-> break)
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__1 */;
  arguments->slots[1] = frame->slots[9] /* temp__2 */;
  arguments->slots[2] = frame->slots[10] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__converted_140;
}
static void entry__compiler__converted_49(void) {
  allocate_initialized_frame_gc(7, 11);
  // slot allocations:
  // new_code: 0
  // code: 1
  // start: 2
  // s: 3
  // i: 4
  // len: 5
  // replacement: 6
  frame->slots[0] = myself->closure.frame->slots[3]; /* new_code */
  frame->slots[1] = myself->closure.frame->slots[0]; /* code */
  frame->slots[2] = myself->closure.frame->slots[4]; /* start */
  frame->slots[3] = myself->closure.frame->slots[1]; /* s */
  frame->slots[4] = myself->closure.frame->slots[2]; /* i */
  frame->slots[5] = myself->closure.frame->slots[5]; /* len */
  frame->slots[6] = myself->closure.frame->slots[7]; /* replacement */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 432: ... s-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* s */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__compiler__converted_50;
}
static void cont__compiler__converted_50(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__2 */ = arguments->slots[0];
  // 432: ... range(code start s-1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* code */;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* start */;
  arguments->slots[2] = frame->slots[8] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__compiler__converted_51;
}
static void cont__compiler__converted_51(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 432: append &new_code range(code start s-1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* new_code */;
  arguments->slots[1] = frame->slots[7] /* temp__1 */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__compiler__converted_52;
}
static void cont__compiler__converted_52(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* new_code */ = arguments->slots[0];
  // 434: code(i)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* i */;
  result_count = 1;
  myself = ((CELL *)frame->slots[1])->contents /* code */;
  func = myself->type;
  frame->cont = cont__compiler__converted_53;
}
static void cont__compiler__converted_53(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__2 */ = arguments->slots[0];
  // 434: code(i) == '('
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__2 */;
  arguments->slots[1] = character__40;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__compiler__converted_54;
}
static void cont__compiler__converted_54(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 434: ... :
  // 435:   $$arguments list()
  // 436:   inc &i
  // 437:   $$a i
  // 438:   $$level 1
  // 439:   do: (-> break)
  // 440:     while -> i <= len:
  // 441:       case
  // 442:         code(i)
  // 443:         ',':
  // ...
  frame->slots[9] /* temp__3 */ = create_closure(entry__compiler__converted_55, 0);
  // 483: :
  // 484:   unless replacement.is_a_string:
  // 485:     !replacement replacement()
  frame->slots[10] /* temp__4 */ = create_closure(entry__compiler__converted_121, 0);
  // 433: if
  // 434:   code(i) == '(':
  // 435:     $$arguments list()
  // 436:     inc &i
  // 437:     $$a i
  // 438:     $$level 1
  // 439:     do: (-> break)
  // 440:       while -> i <= len:
  // 441:         case
  // 442:           code(i)
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[9] /* temp__3 */;
  arguments->slots[2] = frame->slots[10] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__converted_125;
}
static void entry__compiler__converted_123(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // replacement: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* replacement */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 485: !replacement replacement()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* replacement */;
  func = myself->type;
  frame->cont = cont__compiler__converted_124;
}
static void cont__compiler__converted_124(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* replacement */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__converted_88(void) {
  allocate_initialized_frame_gc(2, 8);
  // slot allocations:
  // replacement: 0
  // arguments: 1
  // r: 2
  // j: 3
  // m: 4
  // new_replacement: 5
  frame->slots[0] = myself->closure.frame->slots[3]; /* replacement */
  frame->slots[1] = myself->closure.frame->slots[4]; /* arguments */
  frame->slots[2] /* r */ = create_cell();
  frame->slots[3] /* j */ = create_cell();
  frame->slots[4] /* m */ = create_future();
  frame->slots[5] /* new_replacement */ = create_cell();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 458: $$r 1
  ((CELL *)frame->slots[2])->contents /* r */ = number__1;
  // 459: $$j 1
  ((CELL *)frame->slots[3])->contents /* j */ = number__1;
  // 460: $m length_of(replacement)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* replacement */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__compiler__converted_89;
}
static void cont__compiler__converted_89(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* m */, arguments->slots[0]);
  // 461: $$new_replacement ""
  ((CELL *)frame->slots[5])->contents /* new_replacement */ = empty_string;
  // 462: ... -> j <= m:
  // 463:   if replacement(j) == '$':
  // 464:     append
  // 465:       &new_replacement
  // 466:       range(replacement r j-1)
  // 467:     inc &j
  // 468:     $var_no replacement(j)
  // 469:     if
  // 470:       var_no == '*':
  // 471:         append
  // ...
  frame->slots[6] /* temp__1 */ = create_closure(entry__compiler__converted_90, 0);
  // 462: while -> j <= m:
  // 463:   if replacement(j) == '$':
  // 464:     append
  // 465:       &new_replacement
  // 466:       range(replacement r j-1)
  // 467:     inc &j
  // 468:     $var_no replacement(j)
  // 469:     if
  // 470:       var_no == '*':
  // 471:         append
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  result_count = 0;
  myself = get__while();
  func = myself->type;
  frame->cont = cont__compiler__converted_115;
}
static void entry__compiler__converted_93(void) {
  allocate_initialized_frame_gc(5, 8);
  // slot allocations:
  // replacement: 0
  // j: 1
  // new_replacement: 2
  // r: 3
  // arguments: 4
  frame->slots[0] = myself->closure.frame->slots[2]; /* replacement */
  frame->slots[1] = myself->closure.frame->slots[1]; /* j */
  frame->slots[2] = myself->closure.frame->slots[3]; /* new_replacement */
  frame->slots[3] = myself->closure.frame->slots[4]; /* r */
  frame->slots[4] = myself->closure.frame->slots[5]; /* arguments */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 463: ... replacement(j)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* j */;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* replacement */;
  func = myself->type;
  frame->cont = cont__compiler__converted_94;
}
static void cont__compiler__converted_94(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 463: ... replacement(j) == '$'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = character__36;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__compiler__converted_95;
}
static void cont__compiler__converted_95(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 463: ... :
  // 464:   append
  // 465:     &new_replacement
  // 466:     range(replacement r j-1)
  // 467:   inc &j
  // 468:   $var_no replacement(j)
  // 469:   if
  // 470:     var_no == '*':
  // 471:       append
  // 472:         &new_replacement
  // ...
  frame->slots[7] /* temp__3 */ = create_closure(entry__compiler__converted_96, 0);
  // 463: if replacement(j) == '$':
  // 464:   append
  // 465:     &new_replacement
  // 466:     range(replacement r j-1)
  // 467:   inc &j
  // 468:   $var_no replacement(j)
  // 469:   if
  // 470:     var_no == '*':
  // 471:       append
  // 472:         &new_replacement
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__converted_113;
}
static void entry__compiler__converted_96(void) {
  allocate_initialized_frame_gc(5, 9);
  // slot allocations:
  // new_replacement: 0
  // replacement: 1
  // r: 2
  // j: 3
  // arguments: 4
  // var_no: 5
  frame->slots[0] = myself->closure.frame->slots[2]; /* new_replacement */
  frame->slots[1] = myself->closure.frame->slots[0]; /* replacement */
  frame->slots[2] = myself->closure.frame->slots[3]; /* r */
  frame->slots[3] = myself->closure.frame->slots[1]; /* j */
  frame->slots[4] = myself->closure.frame->slots[4]; /* arguments */
  frame->slots[5] /* var_no */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 466: ... j-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* j */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__compiler__converted_97;
}
static void cont__compiler__converted_97(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 466: range(replacement r j-1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* replacement */;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* r */;
  arguments->slots[2] = frame->slots[7] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__compiler__converted_98;
}
static void cont__compiler__converted_98(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 464: append
  // 465:   &new_replacement
  // 466:   range(replacement r j-1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* new_replacement */;
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__compiler__converted_99;
}
static void cont__compiler__converted_99(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* new_replacement */ = arguments->slots[0];
  // 467: inc &j
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* j */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__compiler__converted_100;
}
static void cont__compiler__converted_100(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* j */ = arguments->slots[0];
  // 468: $var_no replacement(j)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* j */;
  result_count = 1;
  myself = ((CELL *)frame->slots[1])->contents /* replacement */;
  func = myself->type;
  frame->cont = cont__compiler__converted_101;
}
static void cont__compiler__converted_101(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* var_no */, arguments->slots[0]);
  // 470: var_no == '*'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* var_no */;
  arguments->slots[1] = character__42;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__compiler__converted_102;
}
static void cont__compiler__converted_102(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 470: ... :
  // 471:   append
  // 472:     &new_replacement
  // 473:     join(arguments ", ")
  frame->slots[7] /* temp__2 */ = create_closure(entry__compiler__converted_103, 0);
  // 474: :
  // 475:   $idx var_no-'0'
  // 476:   append &new_replacement arguments(idx)
  frame->slots[8] /* temp__3 */ = create_closure(entry__compiler__converted_107, 0);
  // 469: if
  // 470:   var_no == '*':
  // 471:     append
  // 472:       &new_replacement
  // 473:       join(arguments ", ")
  // 474:   :
  // 475:     $idx var_no-'0'
  // 476:     append &new_replacement arguments(idx)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  arguments->slots[2] = frame->slots[8] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__converted_111;
}
static void entry__compiler__converted_103(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // new_replacement: 0
  // arguments: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* new_replacement */
  frame->slots[1] = myself->closure.frame->slots[4]; /* arguments */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 473: join(arguments ", ")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* arguments */;
  arguments->slots[1] = string__2d7981f4e6682be5;
  result_count = 1;
  myself = get__join();
  func = myself->type;
  frame->cont = cont__compiler__converted_105;
}
static void cont__compiler__converted_105(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 471: append
  // 472:   &new_replacement
  // 473:   join(arguments ", ")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* new_replacement */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__compiler__converted_106;
}
static void cont__compiler__converted_106(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* new_replacement */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__converted_107(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // var_no: 0
  // new_replacement: 1
  // arguments: 2
  // idx: 3
  frame->slots[0] = myself->closure.frame->slots[5]; /* var_no */
  frame->slots[1] = myself->closure.frame->slots[0]; /* new_replacement */
  frame->slots[2] = myself->closure.frame->slots[4]; /* arguments */
  frame->slots[3] /* idx */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 475: $idx var_no-'0'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* var_no */;
  arguments->slots[1] = character__48;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__compiler__converted_108;
}
static void cont__compiler__converted_108(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* idx */, arguments->slots[0]);
  // 476: ... arguments(idx)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* idx */;
  result_count = 1;
  myself = ((CELL *)frame->slots[2])->contents /* arguments */;
  func = myself->type;
  frame->cont = cont__compiler__converted_109;
}
static void cont__compiler__converted_109(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 476: append &new_replacement arguments(idx)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* new_replacement */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__compiler__converted_110;
}
static void cont__compiler__converted_110(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* new_replacement */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__converted_111(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 477: !r j+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* j */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__compiler__converted_112;
}
static void cont__compiler__converted_112(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* r */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__converted_113(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 478: inc &j
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* j */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__compiler__converted_114;
}
static void cont__compiler__converted_114(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* j */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__converted_90(void) {
  allocate_initialized_frame_gc(6, 9);
  // slot allocations:
  // m: 0
  // j: 1
  // replacement: 2
  // new_replacement: 3
  // r: 4
  // arguments: 5
  frame->slots[0] = myself->closure.frame->slots[4]; /* m */
  frame->slots[1] = myself->closure.frame->slots[3]; /* j */
  frame->slots[2] = myself->closure.frame->slots[0]; /* replacement */
  frame->slots[3] = myself->closure.frame->slots[5]; /* new_replacement */
  frame->slots[4] = myself->closure.frame->slots[2]; /* r */
  frame->slots[5] = myself->closure.frame->slots[1]; /* arguments */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 462: ... j <= m
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* m */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* j */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__compiler__converted_91;
}
static void cont__compiler__converted_91(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 462: ... j <= m
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__compiler__converted_92;
}
static void cont__compiler__converted_92(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 462: ... :
  // 463:   if replacement(j) == '$':
  // 464:     append
  // 465:       &new_replacement
  // 466:       range(replacement r j-1)
  // 467:     inc &j
  // 468:     $var_no replacement(j)
  // 469:     if
  // 470:       var_no == '*':
  // 471:         append
  // ...
  frame->slots[8] /* temp__3 */ = create_closure(entry__compiler__converted_93, 0);
  // 462: ... -> j <= m:
  // 463:   if replacement(j) == '$':
  // 464:     append
  // 465:       &new_replacement
  // 466:       range(replacement r j-1)
  // 467:     inc &j
  // 468:     $var_no replacement(j)
  // 469:     if
  // 470:       var_no == '*':
  // 471:         append
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__3 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__converted_115(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 480: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__compiler__converted_116;
}
static void cont__compiler__converted_116(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 480: ... range(replacement r -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* replacement */;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* r */;
  arguments->slots[2] = frame->slots[7] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__compiler__converted_117;
}
static void cont__compiler__converted_117(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 479: !replacement
  // 480:   append(new_replacement range(replacement r -1))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[5])->contents /* new_replacement */;
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__compiler__converted_118;
}
static void cont__compiler__converted_118(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* replacement */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__converted_119(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // replacement: 0
  // arguments: 1
  frame->slots[0] = myself->closure.frame->slots[3]; /* replacement */
  frame->slots[1] = myself->closure.frame->slots[4]; /* arguments */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 482: !replacement replacement(arguments)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* arguments */;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* replacement */;
  func = myself->type;
  frame->cont = cont__compiler__converted_120;
}
static void cont__compiler__converted_120(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* replacement */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__converted_55(void) {
  allocate_initialized_frame_gc(4, 10);
  // slot allocations:
  // i: 0
  // len: 1
  // code: 2
  // replacement: 3
  // arguments: 4
  // a: 5
  // level: 6
  frame->slots[0] = myself->closure.frame->slots[4]; /* i */
  frame->slots[1] = myself->closure.frame->slots[5]; /* len */
  frame->slots[2] = myself->closure.frame->slots[1]; /* code */
  frame->slots[3] = myself->closure.frame->slots[6]; /* replacement */
  frame->slots[4] /* arguments */ = create_cell();
  frame->slots[5] /* a */ = create_cell();
  frame->slots[6] /* level */ = create_cell();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 435: $$arguments list()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__compiler__converted_56;
}
static void cont__compiler__converted_56(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[4])->contents /* arguments */ = arguments->slots[0];
  // 436: inc &i
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* i */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__compiler__converted_57;
}
static void cont__compiler__converted_57(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* i */ = arguments->slots[0];
  // 437: $$a i
  ((CELL *)frame->slots[5])->contents /* a */ = ((CELL *)frame->slots[0])->contents /* i */;
  // 438: $$level 1
  ((CELL *)frame->slots[6])->contents /* level */ = number__1;
  // 439: ... : (-> break)
  // 440:   while -> i <= len:
  // 441:     case
  // 442:       code(i)
  // 443:       ',':
  // 444:         if level == 1:
  // 445:           push &arguments trim(range(code a i-1))
  // 446:           !a i+1
  // 447:       '(':
  // 448:         inc &level
  // ...
  frame->slots[7] /* temp__1 */ = create_closure(entry__compiler__converted_58, 0);
  // 439: do: (-> break)
  // 440:   while -> i <= len:
  // 441:     case
  // 442:       code(i)
  // 443:       ',':
  // 444:         if level == 1:
  // 445:           push &arguments trim(range(code a i-1))
  // 446:           !a i+1
  // 447:       '(':
  // 448:         inc &level
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  result_count = 0;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__compiler__converted_86;
}
static void entry__compiler__converted_58(void) {
  allocate_initialized_frame_gc(7, 8);
  // slot allocations:
  // break: 0
  // len: 1
  // i: 2
  // code: 3
  // level: 4
  // arguments: 5
  // a: 6
  frame->slots[0] /* break */ = create_continuation();
  frame->slots[1] = myself->closure.frame->slots[1]; /* len */
  frame->slots[2] = myself->closure.frame->slots[0]; /* i */
  frame->slots[3] = myself->closure.frame->slots[2]; /* code */
  frame->slots[4] = myself->closure.frame->slots[6]; /* level */
  frame->slots[5] = myself->closure.frame->slots[4]; /* arguments */
  frame->slots[6] = myself->closure.frame->slots[5]; /* a */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 440: ... -> i <= len:
  // 441:   case
  // 442:     code(i)
  // 443:     ',':
  // 444:       if level == 1:
  // 445:         push &arguments trim(range(code a i-1))
  // 446:         !a i+1
  // 447:     '(':
  // 448:       inc &level
  // 449:     ')':
  // ...
  frame->slots[7] /* temp__1 */ = create_closure(entry__compiler__converted_59, 0);
  // 440: while -> i <= len:
  // 441:   case
  // 442:     code(i)
  // 443:     ',':
  // 444:       if level == 1:
  // 445:         push &arguments trim(range(code a i-1))
  // 446:         !a i+1
  // 447:     '(':
  // 448:       inc &level
  // 449:     ')':
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__while();
  func = myself->type;
  frame->cont = cont__compiler__converted_85;
}
static void entry__compiler__converted_62(void) {
  allocate_initialized_frame_gc(6, 10);
  // slot allocations:
  // code: 0
  // i: 1
  // level: 2
  // arguments: 3
  // a: 4
  // break: 5
  frame->slots[0] = myself->closure.frame->slots[2]; /* code */
  frame->slots[1] = myself->closure.frame->slots[1]; /* i */
  frame->slots[2] = myself->closure.frame->slots[3]; /* level */
  frame->slots[3] = myself->closure.frame->slots[4]; /* arguments */
  frame->slots[4] = myself->closure.frame->slots[5]; /* a */
  frame->slots[5] = myself->closure.frame->slots[6]; /* break */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 442: code(i)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* i */;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* code */;
  func = myself->type;
  frame->cont = cont__compiler__converted_63;
}
static void cont__compiler__converted_63(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 443: ... :
  // 444:   if level == 1:
  // 445:     push &arguments trim(range(code a i-1))
  // 446:     !a i+1
  frame->slots[7] /* temp__2 */ = create_closure(entry__compiler__converted_64, 0);
  // 447: ... :
  // 448:   inc &level
  frame->slots[8] /* temp__3 */ = create_closure(entry__compiler__converted_72, 0);
  // 449: ... :
  // 450:   dec &level
  // 451:   if level == 0:
  // 452:     push &arguments trim(range(code a i-1))
  // 453:     inc &i
  // 454:     break
  frame->slots[9] /* temp__4 */ = create_closure(entry__compiler__converted_74, 0);
  // 441: case
  // 442:   code(i)
  // 443:   ',':
  // 444:     if level == 1:
  // 445:       push &arguments trim(range(code a i-1))
  // 446:       !a i+1
  // 447:   '(':
  // 448:     inc &level
  // 449:   ')':
  // 450:     dec &level
  // ...
  argument_count = 7;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = character__44;
  arguments->slots[2] = frame->slots[7] /* temp__2 */;
  arguments->slots[3] = character__40;
  arguments->slots[4] = frame->slots[8] /* temp__3 */;
  arguments->slots[5] = character__41;
  arguments->slots[6] = frame->slots[9] /* temp__4 */;
  result_count = 0;
  myself = get__case();
  func = myself->type;
  frame->cont = cont__compiler__converted_83;
}
static void entry__compiler__converted_77(void) {
  allocate_initialized_frame_gc(5, 8);
  // slot allocations:
  // arguments: 0
  // code: 1
  // a: 2
  // i: 3
  // break: 4
  frame->slots[0] = myself->closure.frame->slots[1]; /* arguments */
  frame->slots[1] = myself->closure.frame->slots[2]; /* code */
  frame->slots[2] = myself->closure.frame->slots[3]; /* a */
  frame->slots[3] = myself->closure.frame->slots[4]; /* i */
  frame->slots[4] = myself->closure.frame->slots[5]; /* break */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 452: ... i-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* i */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__compiler__converted_78;
}
static void cont__compiler__converted_78(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__3 */ = arguments->slots[0];
  // 452: ... range(code a i-1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* code */;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* a */;
  arguments->slots[2] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__compiler__converted_79;
}
static void cont__compiler__converted_79(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 452: ... trim(range(code a i-1))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__compiler__converted_80;
}
static void cont__compiler__converted_80(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 452: push &arguments trim(range(code a i-1))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* arguments */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__converted_81;
}
static void cont__compiler__converted_81(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* arguments */ = arguments->slots[0];
  // 453: inc &i
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* i */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__compiler__converted_82;
}
static void cont__compiler__converted_82(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* i */ = arguments->slots[0];
  // 454: break
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[4] /* break */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__converted_66(void) {
  allocate_initialized_frame_gc(4, 7);
  // slot allocations:
  // arguments: 0
  // code: 1
  // a: 2
  // i: 3
  frame->slots[0] = myself->closure.frame->slots[1]; /* arguments */
  frame->slots[1] = myself->closure.frame->slots[2]; /* code */
  frame->slots[2] = myself->closure.frame->slots[3]; /* a */
  frame->slots[3] = myself->closure.frame->slots[4]; /* i */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 445: ... i-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* i */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__compiler__converted_67;
}
static void cont__compiler__converted_67(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 445: ... range(code a i-1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* code */;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* a */;
  arguments->slots[2] = frame->slots[6] /* temp__3 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__compiler__converted_68;
}
static void cont__compiler__converted_68(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 445: ... trim(range(code a i-1))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__compiler__converted_69;
}
static void cont__compiler__converted_69(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 445: push &arguments trim(range(code a i-1))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* arguments */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__converted_70;
}
static void cont__compiler__converted_70(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* arguments */ = arguments->slots[0];
  // 446: !a i+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* i */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__compiler__converted_71;
}
static void cont__compiler__converted_71(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* a */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__converted_64(void) {
  allocate_initialized_frame_gc(5, 7);
  // slot allocations:
  // level: 0
  // arguments: 1
  // code: 2
  // a: 3
  // i: 4
  frame->slots[0] = myself->closure.frame->slots[2]; /* level */
  frame->slots[1] = myself->closure.frame->slots[3]; /* arguments */
  frame->slots[2] = myself->closure.frame->slots[0]; /* code */
  frame->slots[3] = myself->closure.frame->slots[4]; /* a */
  frame->slots[4] = myself->closure.frame->slots[1]; /* i */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 444: ... level == 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* level */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__compiler__converted_65;
}
static void cont__compiler__converted_65(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 444: ... :
  // 445:   push &arguments trim(range(code a i-1))
  // 446:   !a i+1
  frame->slots[6] /* temp__2 */ = create_closure(entry__compiler__converted_66, 0);
  // 444: if level == 1:
  // 445:   push &arguments trim(range(code a i-1))
  // 446:   !a i+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__converted_72(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // level: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* level */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 448: inc &level
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* level */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__compiler__converted_73;
}
static void cont__compiler__converted_73(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* level */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__converted_74(void) {
  allocate_initialized_frame_gc(6, 8);
  // slot allocations:
  // level: 0
  // arguments: 1
  // code: 2
  // a: 3
  // i: 4
  // break: 5
  frame->slots[0] = myself->closure.frame->slots[2]; /* level */
  frame->slots[1] = myself->closure.frame->slots[3]; /* arguments */
  frame->slots[2] = myself->closure.frame->slots[0]; /* code */
  frame->slots[3] = myself->closure.frame->slots[4]; /* a */
  frame->slots[4] = myself->closure.frame->slots[1]; /* i */
  frame->slots[5] = myself->closure.frame->slots[5]; /* break */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 450: dec &level
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* level */;
  result_count = 1;
  myself = get__dec();
  func = myself->type;
  frame->cont = cont__compiler__converted_75;
}
static void cont__compiler__converted_75(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* level */ = arguments->slots[0];
  // 451: ... level == 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* level */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__compiler__converted_76;
}
static void cont__compiler__converted_76(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 451: ... :
  // 452:   push &arguments trim(range(code a i-1))
  // 453:   inc &i
  // 454:   break
  frame->slots[7] /* temp__2 */ = create_closure(entry__compiler__converted_77, 0);
  // 451: if level == 0:
  // 452:   push &arguments trim(range(code a i-1))
  // 453:   inc &i
  // 454:   break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__converted_83(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 455: inc &i
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* i */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__compiler__converted_84;
}
static void cont__compiler__converted_84(void) {
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
static void entry__compiler__converted_59(void) {
  allocate_initialized_frame_gc(7, 10);
  // slot allocations:
  // len: 0
  // i: 1
  // code: 2
  // level: 3
  // arguments: 4
  // a: 5
  // break: 6
  frame->slots[0] = myself->closure.frame->slots[1]; /* len */
  frame->slots[1] = myself->closure.frame->slots[2]; /* i */
  frame->slots[2] = myself->closure.frame->slots[3]; /* code */
  frame->slots[3] = myself->closure.frame->slots[4]; /* level */
  frame->slots[4] = myself->closure.frame->slots[5]; /* arguments */
  frame->slots[5] = myself->closure.frame->slots[6]; /* a */
  frame->slots[6] = myself->closure.frame->slots[0]; /* break */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 440: ... i <= len
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* len */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* i */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__compiler__converted_60;
}
static void cont__compiler__converted_60(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__2 */ = arguments->slots[0];
  // 440: ... i <= len
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__compiler__converted_61;
}
static void cont__compiler__converted_61(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 440: ... :
  // 441:   case
  // 442:     code(i)
  // 443:     ',':
  // 444:       if level == 1:
  // 445:         push &arguments trim(range(code a i-1))
  // 446:         !a i+1
  // 447:     '(':
  // 448:       inc &level
  // 449:     ')':
  // ...
  frame->slots[9] /* temp__3 */ = create_closure(entry__compiler__converted_62, 0);
  // 440: ... -> i <= len:
  // 441:   case
  // 442:     code(i)
  // 443:     ',':
  // 444:       if level == 1:
  // 445:         push &arguments trim(range(code a i-1))
  // 446:         !a i+1
  // 447:     '(':
  // 448:       inc &level
  // 449:     ')':
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[9] /* temp__3 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__converted_85(void) {
  myself = frame->slots[0] /* break */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__compiler__converted_86(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 457: replacement.is_a_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* replacement */;
  result_count = 1;
  myself = get__is_a_string();
  func = myself->type;
  frame->cont = cont__compiler__converted_87;
}
static void cont__compiler__converted_87(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 457: ... :
  // 458:   $$r 1
  // 459:   $$j 1
  // 460:   $m length_of(replacement)
  // 461:   $$new_replacement ""
  // 462:   while -> j <= m:
  // 463:     if replacement(j) == '$':
  // 464:       append
  // 465:         &new_replacement
  // 466:         range(replacement r j-1)
  // ...
  frame->slots[8] /* temp__2 */ = create_closure(entry__compiler__converted_88, 0);
  // 481: :
  // 482:   !replacement replacement(arguments)
  frame->slots[9] /* temp__3 */ = create_closure(entry__compiler__converted_119, 0);
  // 456: if
  // 457:   replacement.is_a_string:
  // 458:     $$r 1
  // 459:     $$j 1
  // 460:     $m length_of(replacement)
  // 461:     $$new_replacement ""
  // 462:     while -> j <= m:
  // 463:       if replacement(j) == '$':
  // 464:         append
  // 465:           &new_replacement
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__2 */;
  arguments->slots[2] = frame->slots[9] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__converted_121(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // replacement: 0
  frame->slots[0] = myself->closure.frame->slots[6]; /* replacement */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 484: ... replacement.is_a_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* replacement */;
  result_count = 1;
  myself = get__is_a_string();
  func = myself->type;
  frame->cont = cont__compiler__converted_122;
}
static void cont__compiler__converted_122(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 484: ... :
  // 485:   !replacement replacement()
  frame->slots[2] /* temp__2 */ = create_closure(entry__compiler__converted_123, 0);
  // 484: unless replacement.is_a_string:
  // 485:   !replacement replacement()
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__converted_125(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 486: ... replacement.converted
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[6])->contents /* replacement */;
  result_count = 1;
  myself = get__converted();
  func = myself->type;
  frame->cont = cont__compiler__converted_126;
}
static void cont__compiler__converted_126(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 486: append &new_code replacement.converted
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* new_code */;
  arguments->slots[1] = frame->slots[7] /* temp__1 */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__compiler__converted_127;
}
static void cont__compiler__converted_127(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* new_code */ = arguments->slots[0];
  // 487: !start i
  ((CELL *)frame->slots[2])->contents /* start */ = ((CELL *)frame->slots[4])->contents /* i */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__converted_128(void) {
  allocate_initialized_frame_gc(6, 8);
  // slot allocations:
  // identifier: 0
  // new_code: 1
  // code: 2
  // start: 3
  // s: 4
  // i: 5
  frame->slots[0] = myself->closure.frame->slots[6]; /* identifier */
  frame->slots[1] = myself->closure.frame->slots[3]; /* new_code */
  frame->slots[2] = myself->closure.frame->slots[0]; /* code */
  frame->slots[3] = myself->closure.frame->slots[4]; /* start */
  frame->slots[4] = myself->closure.frame->slots[1]; /* s */
  frame->slots[5] = myself->closure.frame->slots[2]; /* i */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 489: ... identifier .contains. ':'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* identifier */;
  arguments->slots[1] = character__58;
  result_count = 1;
  myself = get__contains();
  func = myself->type;
  frame->cont = cont__compiler__converted_129;
}
static void cont__compiler__converted_129(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 489: ... :
  // 490:   replace_all &identifier "::" = "__"
  // 491:   append &new_code range(code start s-1)
  // 492:   append &new_code identifier
  // 493:   !start i
  frame->slots[7] /* temp__2 */ = create_closure(entry__compiler__converted_130, 0);
  // 489: if identifier .contains. ':':
  // 490:   replace_all &identifier "::" = "__"
  // 491:   append &new_code range(code start s-1)
  // 492:   append &new_code identifier
  // 493:   !start i
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__converted_139;
}
static void entry__compiler__converted_130(void) {
  allocate_initialized_frame_gc(6, 8);
  // slot allocations:
  // identifier: 0
  // new_code: 1
  // code: 2
  // start: 3
  // s: 4
  // i: 5
  frame->slots[0] = myself->closure.frame->slots[0]; /* identifier */
  frame->slots[1] = myself->closure.frame->slots[1]; /* new_code */
  frame->slots[2] = myself->closure.frame->slots[2]; /* code */
  frame->slots[3] = myself->closure.frame->slots[3]; /* start */
  frame->slots[4] = myself->closure.frame->slots[4]; /* s */
  frame->slots[5] = myself->closure.frame->slots[5]; /* i */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 490: ... "::" = "__"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e6d82bff;
  arguments->slots[1] = string__2d7981f4e5f02b9a;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__compiler__converted_133;
}
static void cont__compiler__converted_133(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 490: replace_all &identifier "::" = "__"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* identifier */;
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  result_count = 1;
  myself = get__replace_all();
  func = myself->type;
  frame->cont = cont__compiler__converted_134;
}
static void cont__compiler__converted_134(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* identifier */ = arguments->slots[0];
  // 491: ... s-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* s */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__compiler__converted_135;
}
static void cont__compiler__converted_135(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 491: ... range(code start s-1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* code */;
  arguments->slots[1] = ((CELL *)frame->slots[3])->contents /* start */;
  arguments->slots[2] = frame->slots[7] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__compiler__converted_136;
}
static void cont__compiler__converted_136(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 491: append &new_code range(code start s-1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* new_code */;
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__compiler__converted_137;
}
static void cont__compiler__converted_137(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* new_code */ = arguments->slots[0];
  // 492: append &new_code identifier
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* new_code */;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* identifier */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__compiler__converted_138;
}
static void cont__compiler__converted_138(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* new_code */ = arguments->slots[0];
  // 493: !start i
  ((CELL *)frame->slots[3])->contents /* start */ = ((CELL *)frame->slots[5])->contents /* i */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__converted_139(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 494: use_identifier identifier
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* identifier */;
  result_count = frame->caller_result_count;
  myself = get__use_identifier();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__converted_140(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 495: !s undefined
  ((CELL *)frame->slots[1])->contents /* s */ = get__undefined();
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__converted_35(void) {
  allocate_initialized_frame_gc(7, 12);
  // slot allocations:
  // chr: 0
  // code: 1
  // i: 2
  // s: 3
  // new_code: 4
  // start: 5
  // len: 6
  frame->slots[0] = myself->closure.frame->slots[1]; /* chr */
  frame->slots[1] = myself->closure.frame->slots[2]; /* code */
  frame->slots[2] = myself->closure.frame->slots[3]; /* i */
  frame->slots[3] = myself->closure.frame->slots[0]; /* s */
  frame->slots[4] = myself->closure.frame->slots[4]; /* new_code */
  frame->slots[5] = myself->closure.frame->slots[5]; /* start */
  frame->slots[6] = myself->closure.frame->slots[6]; /* len */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 425: chr == ':'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  arguments->slots[1] = character__58;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__compiler__converted_36;
}
static void cont__compiler__converted_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__2 */ = arguments->slots[0];
  // 425: ... code(i+1) == ':'
  frame->slots[9] /* temp__3 */ = create_closure(entry__compiler__converted_37, 0);
  // 425: chr == ':' && code(i+1) == ':'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__2 */;
  arguments->slots[1] = frame->slots[9] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__compiler__converted_41;
}
static void entry__compiler__converted_37(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // code: 0
  // i: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* code */
  frame->slots[1] = myself->closure.frame->slots[2]; /* i */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 425: ... i+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* i */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__compiler__converted_38;
}
static void cont__compiler__converted_38(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 425: ... code(i+1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* code */;
  func = myself->type;
  frame->cont = cont__compiler__converted_39;
}
static void cont__compiler__converted_39(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 425: ... code(i+1) == ':'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = character__58;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__compiler__converted_40;
}
static void cont__compiler__converted_40(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 425: ... code(i+1) == ':'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__converted_41(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 425: ... :
  // 426:   inc &i
  frame->slots[10] /* temp__4 */ = create_closure(entry__compiler__converted_42, 0);
  // 427: :
  // 428:   $$identifier range(code s i-1)
  // 429:   $$replacement macro_replacements(identifier)
  // 430:   if
  // 431:     replacement.is_defined:
  // 432:       append &new_code range(code start s-1)
  // 433:       if
  // 434:         code(i) == '(':
  // 435:           $$arguments list()
  // 436:           inc &i
  // ...
  frame->slots[11] /* temp__5 */ = create_closure(entry__compiler__converted_44, 0);
  // 424: if
  // 425:   chr == ':' && code(i+1) == ':':
  // 426:     inc &i
  // 427:   :
  // 428:     $$identifier range(code s i-1)
  // 429:     $$replacement macro_replacements(identifier)
  // 430:     if
  // 431:       replacement.is_defined:
  // 432:         append &new_code range(code start s-1)
  // 433:         if
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[10] /* temp__4 */;
  arguments->slots[2] = frame->slots[11] /* temp__5 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__converted_32(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // within_string: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* within_string */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 421: ... !within_string true
  ((CELL *)frame->slots[0])->contents /* within_string */ = get__true();
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__converted_27(void) {
  allocate_initialized_frame_gc(4, 9);
  // slot allocations:
  // s: 0
  // code: 1
  // i: 2
  // within_string: 3
  frame->slots[0] = myself->closure.frame->slots[2]; /* s */
  frame->slots[1] = myself->closure.frame->slots[0]; /* code */
  frame->slots[2] = myself->closure.frame->slots[1]; /* i */
  frame->slots[3] = myself->closure.frame->slots[3]; /* within_string */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 420: !s undefined
  ((CELL *)frame->slots[0])->contents /* s */ = get__undefined();
  // 421: ... i-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* i */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__compiler__converted_28;
}
static void cont__compiler__converted_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__4 */ = arguments->slots[0];
  // 421: ... code(i-1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__4 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[1])->contents /* code */;
  func = myself->type;
  frame->cont = cont__compiler__converted_29;
}
static void cont__compiler__converted_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 421: ... code(i-1) != '\'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__3 */;
  arguments->slots[1] = character__92;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__compiler__converted_30;
}
static void cont__compiler__converted_30(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 421: ... code(i-1) != '\'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__compiler__converted_31;
}
static void cont__compiler__converted_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 421: ... : !within_string true
  frame->slots[8] /* temp__5 */ = create_closure(entry__compiler__converted_32, 0);
  // 421: if code(i-1) != '\': !within_string true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__5 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__converted_33(void) {
  allocate_initialized_frame_gc(7, 9);
  // slot allocations:
  // s: 0
  // chr: 1
  // code: 2
  // i: 3
  // new_code: 4
  // start: 5
  // len: 6
  frame->slots[0] = myself->closure.frame->slots[2]; /* s */
  frame->slots[1] = myself->closure.frame->slots[7]; /* chr */
  frame->slots[2] = myself->closure.frame->slots[0]; /* code */
  frame->slots[3] = myself->closure.frame->slots[1]; /* i */
  frame->slots[4] = myself->closure.frame->slots[4]; /* new_code */
  frame->slots[5] = myself->closure.frame->slots[5]; /* start */
  frame->slots[6] = myself->closure.frame->slots[6]; /* len */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 423: ... s.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* s */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__compiler__converted_34;
}
static void cont__compiler__converted_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 423: ... :
  // 424:   if
  // 425:     chr == ':' && code(i+1) == ':':
  // 426:       inc &i
  // 427:     :
  // 428:       $$identifier range(code s i-1)
  // 429:       $$replacement macro_replacements(identifier)
  // 430:       if
  // 431:         replacement.is_defined:
  // 432:           append &new_code range(code start s-1)
  // ...
  frame->slots[8] /* temp__2 */ = create_closure(entry__compiler__converted_35, 0);
  // 423: if s.is_defined:
  // 424:   if
  // 425:     chr == ':' && code(i+1) == ':':
  // 426:       inc &i
  // 427:     :
  // 428:       $$identifier range(code s i-1)
  // 429:       $$replacement macro_replacements(identifier)
  // 430:       if
  // 431:         replacement.is_defined:
  // 432:           append &new_code range(code start s-1)
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
static void entry__compiler__converted_141(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 418: pass
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = get__pass();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__converted_142(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 496: inc &i
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* i */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__compiler__converted_143;
}
static void cont__compiler__converted_143(void) {
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
static void entry__compiler__converted_7(void) {
  allocate_initialized_frame_gc(7, 9);
  // slot allocations:
  // within_string: 0
  // code: 1
  // i: 2
  // s: 3
  // new_code: 4
  // start: 5
  // len: 6
  frame->slots[0] = myself->closure.frame->slots[2]; /* within_string */
  frame->slots[1] = myself->closure.frame->slots[3]; /* code */
  frame->slots[2] = myself->closure.frame->slots[1]; /* i */
  frame->slots[3] = myself->closure.frame->slots[4]; /* s */
  frame->slots[4] = myself->closure.frame->slots[5]; /* new_code */
  frame->slots[5] = myself->closure.frame->slots[6]; /* start */
  frame->slots[6] = myself->closure.frame->slots[0]; /* len */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 408: ... :
  // 409:   case code(i) '@quot;': if code(i-1) != '\': !within_string false
  // 410:   inc &i
  frame->slots[7] /* temp__1 */ = create_closure(entry__compiler__converted_8, 0);
  // 411: :
  // 412:   $chr code(i)
  // 413:   case
  // 414:     chr
  // 415:     '_', 'a' .. 'z', 'A' .. 'Z':
  // 416:       unless s.is_defined: !s i
  // 417:     '0' .. '9':
  // 418:       pass
  // 419:     '@quot;':
  // 420:       !s undefined
  // ...
  frame->slots[8] /* temp__2 */ = create_closure(entry__compiler__converted_18, 0);
  // 407: if
  // 408:   within_string:
  // 409:     case code(i) '@quot;': if code(i-1) != '\': !within_string false
  // 410:     inc &i
  // 411:   :
  // 412:     $chr code(i)
  // 413:     case
  // 414:       chr
  // 415:       '_', 'a' .. 'z', 'A' .. 'Z':
  // 416:         unless s.is_defined: !s i
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* within_string */;
  arguments->slots[1] = frame->slots[7] /* temp__1 */;
  arguments->slots[2] = frame->slots[8] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__converted_4(void) {
  allocate_initialized_frame_gc(7, 10);
  // slot allocations:
  // len: 0
  // i: 1
  // within_string: 2
  // code: 3
  // s: 4
  // new_code: 5
  // start: 6
  frame->slots[0] = myself->closure.frame->slots[7]; /* len */
  frame->slots[1] = myself->closure.frame->slots[6]; /* i */
  frame->slots[2] = myself->closure.frame->slots[4]; /* within_string */
  frame->slots[3] = myself->closure.frame->slots[0]; /* code */
  frame->slots[4] = myself->closure.frame->slots[5]; /* s */
  frame->slots[5] = myself->closure.frame->slots[2]; /* new_code */
  frame->slots[6] = myself->closure.frame->slots[3]; /* start */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 406: ... i <= len
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* len */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* i */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__compiler__converted_5;
}
static void cont__compiler__converted_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__2 */ = arguments->slots[0];
  // 406: ... i <= len
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__compiler__converted_6;
}
static void cont__compiler__converted_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 406: ... :
  // 407:   if
  // 408:     within_string:
  // 409:       case code(i) '@quot;': if code(i-1) != '\': !within_string false
  // 410:       inc &i
  // 411:     :
  // 412:       $chr code(i)
  // 413:       case
  // 414:         chr
  // 415:         '_', 'a' .. 'z', 'A' .. 'Z':
  // ...
  frame->slots[9] /* temp__3 */ = create_closure(entry__compiler__converted_7, 0);
  // 406: ... -> i <= len:
  // 407:   if
  // 408:     within_string:
  // 409:       case code(i) '@quot;': if code(i-1) != '\': !within_string false
  // 410:       inc &i
  // 411:     :
  // 412:       $chr code(i)
  // 413:       case
  // 414:         chr
  // 415:         '_', 'a' .. 'z', 'A' .. 'Z':
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[9] /* temp__3 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__converted_144(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 498: new_code != ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* new_code */;
  arguments->slots[1] = empty_string;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__compiler__converted_145;
}
static void cont__compiler__converted_145(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__2 */ = arguments->slots[0];
  // 498: new_code != ""
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__compiler__converted_146;
}
static void cont__compiler__converted_146(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__1 */ = arguments->slots[0];
  // 499: -> append(new_code range(code start -2))
  frame->slots[10] /* temp__3 */ = create_closure(entry__compiler__converted_147, 0);
  // 500: -> range(code 1 -2)
  frame->slots[11] /* temp__4 */ = create_closure(entry__compiler__converted_151, 0);
  // 497: if
  // 498:   new_code != ""
  // 499:   -> append(new_code range(code start -2))
  // 500:   -> range(code 1 -2)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__1 */;
  arguments->slots[1] = frame->slots[10] /* temp__3 */;
  arguments->slots[2] = frame->slots[11] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__converted_154;
}
static void entry__compiler__converted_147(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // new_code: 0
  // code: 1
  // start: 2
  frame->slots[0] = myself->closure.frame->slots[2]; /* new_code */
  frame->slots[1] = myself->closure.frame->slots[0]; /* code */
  frame->slots[2] = myself->closure.frame->slots[3]; /* start */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 499: ... 2
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__compiler__converted_148;
}
static void cont__compiler__converted_148(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 499: ... range(code start -2)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* code */;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* start */;
  arguments->slots[2] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__compiler__converted_149;
}
static void cont__compiler__converted_149(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 499: ... append(new_code range(code start -2))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* new_code */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__compiler__converted_150;
}
static void cont__compiler__converted_150(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 499: -> append(new_code range(code start -2))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__converted_151(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // code: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* code */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 500: ... 2
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__compiler__converted_152;
}
static void cont__compiler__converted_152(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 500: ... range(code 1 -2)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* code */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__compiler__converted_153;
}
static void cont__compiler__converted_153(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 500: -> range(code 1 -2)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__converted_154(void) {
  myself = frame->slots[1] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
EXPORT void collect__macros(void) {
  var._EVENT = collect_node(var._EVENT);
  var._ACTION = collect_node(var._ACTION);
  var._INFO = collect_node(var._INFO);
  var._DATA = collect_node(var._DATA);
  var._macro_replacements = collect_node(var._macro_replacements);
  var._define_macro = collect_node(var._define_macro);
  var.compiler__converted = collect_node(var.compiler__converted);
}

static int already_run_phase_1 = false;

EXPORT void phase_1__macros(void) {
  if (already_run_phase_1) return;
  already_run_phase_1 = true;
  register_module_info(&module_info);
}

static int already_run_phase_2 = false;

EXPORT void phase_2__macros(void) {
  if (already_run_phase_2) return;
  already_run_phase_2 = true;
  set_module("macros");
  character__92 = from_uchar32(92);
  character__90 = from_uchar32(90);
  character__122 = from_uchar32(122);
  character__57 = from_uchar32(57);
  character__65 = from_uchar32(65);
  character__44 = from_uchar32(44);
  character__10 = from_uchar32(10);
  number__0 = from_uint32(0U);
  character__58 = from_uchar32(58);
  number__3 = from_uint32(3U);
  character__48 = from_uchar32(48);
  character__95 = from_uchar32(95);
  character__40 = from_uchar32(40);
  character__34 = from_uchar32(34);
  character__36 = from_uchar32(36);
  character__125 = from_uchar32(125);
  character__41 = from_uchar32(41);
  character__97 = from_uchar32(97);
  number__1 = from_uint32(1U);
  number__2 = from_uint32(2U);
  character__42 = from_uchar32(42);
  unique__EVENT = register_unique_item("EVENT");
  unique__ACTION = register_unique_item("ACTION");
  unique__INFO = register_unique_item("INFO");
  unique__DATA = register_unique_item("DATA");
  func__define_macro_1 = create_function(entry__define_macro_1, 2);
  string__2d7981f4e6682be5 = from_latin_1_string(", ", 2);
  string__2d7981f4e6d82bff = from_latin_1_string("::", 2);
  string__2d7981f4e5f02b9a = from_latin_1_string("__", 2);
  func__compiler__converted_141 = create_function(entry__compiler__converted_141, 0);
  func__compiler__converted_1 = create_function(entry__compiler__converted_1, 1);
  string__400ae5cb5c587d7a = from_latin_1_string("ARGC", 4);
  string__6c94222b8f3884e6 = from_latin_1_string("main_argc", 9);
  string__400ae5cb5c587d6f = from_latin_1_string("ARGV", 4);
  string__6c94222b8f3884f3 = from_latin_1_string("main_argv", 9);
  string__1028a78005f60678 = from_latin_1_string("POLY_IDX", 8);
  string__34f9178f4105813b = from_latin_1_string("poly_idx__$1", 12);
  string__6b819d4408594055 = from_latin_1_string("POLY_COUNT", 10);
  string__a8d3ab331eb668e7 = from_latin_1_string("polymorphic_function_count", 26);
  string__59cab089aecbe8a5 = from_latin_1_string("POLY_WITH_SETTER_COUNT", 22);
  string__77b931a5baaa8bfc = from_latin_1_string("polymorphic_function_with_setter_count", 38);
  string__77819b4408019052 = from_latin_1_string("POLY_NAMES", 10);
  string__b4d3ad331eeeb8e0 = from_latin_1_string("polymorphic_function_names", 26);
  string__48483b12ea44e011 = from_latin_1_string("UNIQUE_NAMES", 12);
  string__a7a3514a924a78fa = from_latin_1_string("unique_item_names", 17);
  string__8f50c41d106226cf = from_latin_1_string("ARGUMENT_COUNT", 14);
  string__dfd1ce1d312022e7 = from_latin_1_string("argument_count", 14);
  string__440ae28b5c107d6d = from_latin_1_string("CONT", 4);
  string__6c9a2bd2e7c4af5 = from_latin_1_string("frame->cont", 11);
  string__8d88533a39505214 = from_latin_1_string("CHECK_ARGUMENTS", 15);
  string__1bb6ef61f3edfaf2 = from_latin_1_string(
    "if (argument_count != $1) {\n"
    "  invalid_arguments_error();\n"
    "  return;\n"
    "}",
    68);
  string__8f7216a94bc80f3 = from_latin_1_string("MIN_ARGUMENTS", 13);
  string__fbe40d362af5bff1 = from_latin_1_string(
    "if (argument_count < $1) {\n"
    "  too_few_arguments_error();\n"
    "  return;\n"
    "}",
    67);
  string__88f7216a94ac80f6 = from_latin_1_string("MAX_ARGUMENTS", 13);
  string__91ccef706a22d072 = from_latin_1_string(
    "if (argument_count > $1) {\n"
    "  too_many_arguments_error();\n"
    "  return;\n"
    "}",
    68);
  string__940ced12ee123334 = from_latin_1_string("RESULT_COUNT", 12);
  string__d48de512cf50371c = from_latin_1_string("result_count", 12);
  string__fa72dc15c216b9e = from_latin_1_string("VAR", 3);
  string__2e0ae90b5df07d17 = from_latin_1_string("var.", 4);
  string__485aef83e8b97008 = from_latin_1_string("var._", 5);
  string__405aee03eb306008 = from_latin_1_string("get__", 5);
  string__2d7981f4e6482bec = from_latin_1_string("()", 2);
  func__96_2 = create_function(entry__96_2, 1);
  string__265ae243ebba4003 = from_latin_1_string("EVENT", 5);
  string__314a5f4a93a00186 = from_latin_1_string("if (event__mode != EM__REPLAY) {", 32);
  func__97_2 = create_function(entry__97_2, 1);
  string__301f5c1000c06299 = from_latin_1_string("ACTION", 6);
  func__98_2 = create_function(entry__98_2, 1);
  string__500ae2cb5c507d76 = from_latin_1_string("INFO", 4);
  func__99_2 = create_function(entry__99_2, 0);
  string__4a0ae10b5cc07d78 = from_latin_1_string("DATA", 4);
  string__b0ac9625f04ddbd3 = from_latin_1_string(
    "  if (event__mode == EM__RECORD) {\n"
    "    record__event(\042",
    54);
  string__fa730c15f616bf7 = from_latin_1_string("\042);", 3);
  func__100_4 = create_function(entry__100_4, 0);
  string__f9bb92aa6d4490dd = from_latin_1_string("  if (event__mode == EM__RECORD) {", 34);
  func__100_8 = create_function(entry__100_8, 0);
  func__100_2 = create_function(entry__100_2, 0);
  string__fa72a015c596b98 = from_latin_1_string("INT", 3);
  string__b8200c1595938088 = from_latin_1_string("integer", 7);
  string__297be2f6f9dca12f = from_latin_1_string("  store__integer(", 17);
  string__2d7981f4e6402bfe = from_latin_1_string(");", 2);
  string__4a1f57e083be52ff = from_latin_1_string("  if (", 6);
  string__820afe0b5f887d19 = from_latin_1_string(" == ", 4);
  string__fd21e7555dafa46d = from_latin_1_string(
    ") {\n"
    "      successful__action(\042",
    30);
  string__7ed0587dfc52436 = from_latin_1_string(
    "\042);\n"
    "    } else {\n"
    "      failed__action(\042",
    39);
  string__c81f08526aea5316 = from_latin_1_string(
    "\042);\n"
    "      store__integer(",
    25);
  string__eff8bde306d1997d = from_latin_1_string(
    ");\n"
    "    }",
    8);
  func__101_2 = create_function(entry__101_2, 1);
  string__5a0ae28b5c107d7e = from_latin_1_string("LONG", 4);
  string__40f9098a5d354178 = from_latin_1_string("long_integer", 12);
  string__329e59a9af29a0d5 = from_latin_1_string("  store__long_integer(", 22);
  string__7b0520b55f9bd587 = from_latin_1_string(
    "\042);\n"
    "      store__long_integer(",
    30);
  func__102_2 = create_function(entry__102_2, 1);
  string__eec400c5149050a8 = from_latin_1_string("POINTER", 7);
  string__ae4408d515925088 = from_latin_1_string("pointer", 7);
  string__f7fe2f879dc120f = from_latin_1_string("  store__pointer(", 17);
  string__820af8cb5f507d19 = from_latin_1_string(" && ", 4);
  string__1ee649de6e08afc4 = from_latin_1_string(
    " != (void *)FIRST_INVALID_ADDRESS) {\n"
    "      successful__action(\042",
    63);
  string__ee1b085ceaeae036 = from_latin_1_string(
    "\042);\n"
    "      store__pointer(",
    25);
  func__103_2 = create_function(entry__103_2, 1);
  string__a602a332a09613c = from_latin_1_string("INT_ARRAY", 9);
  string__4ae022330b0b651c = from_latin_1_string("int_array", 9);
  string__77c059895d31cd96 = from_latin_1_string("  store__int_array(", 19);
  func__104_2 = create_function(entry__104_2, 1);
  string__21f5d960028028e = from_latin_1_string("MEMORY", 6);
  string__421f5586012a02ae = from_latin_1_string("memory", 6);
  string__8030e06afcbf4f61 = from_latin_1_string("  store__memory(", 16);
  func__105_2 = create_function(entry__105_2, 1);
  string__a68a78f85a6d407 = from_latin_1_string("C_STRING", 8);
  string__4a68af9f84a4d027 = from_latin_1_string("c_string", 8);
  string__fabc9ed81001dd7 = from_latin_1_string("  store__c_string(", 18);
  func__106_2 = create_function(entry__106_2, 1);
  string__fa729015c596b88 = from_latin_1_string("END", 3);
  string__d81f466083be52f7 = from_latin_1_string("      ", 6);
  func__107_5 = create_function(entry__107_5, 0);
  string__2d7981f4e6082be5 = from_latin_1_string("  ", 2);
  func__107_7 = create_function(entry__107_7, 0);
  string__3802f8268029fd6c = from_latin_1_string("retrieve__pointer((void **)&", 28);
  string__30c5044d97434308 = from_latin_1_string(" = retrieve__int_array((int **)&", 32);
  string__4ff2866267e10016 = from_latin_1_string(" = retrieve__memory((uint8_t **)&", 33);
  string__192c815f22d3275e = from_latin_1_string("retrieve__", 10);
  string__2d7981f4e6482be3 = from_latin_1_string("(&", 2);
  func__107_34 = create_function(entry__107_34, 0);
  func__107_35 = create_function(entry__107_35, 0);
  string__32285b242638aa20 = from_latin_1_string("print__pointer(", 15);
  string__8eee524608dfba81 = from_latin_1_string("print__int_array(", 17);
  string__173507c00b84c49d = from_latin_1_string("print__memory(", 14);
  string__ae4408db944250a5 = from_latin_1_string("print__", 7);
  string__578a5af303e9cc9 = from_latin_1_string("(", 1);
  string__887d942629156ee6 = from_latin_1_string(
    "  }\n"
    "} else {\n",
    13);
  string__33d6d747fb30a3e4 = from_latin_1_string("  replay__event(\042", 17);
  string__860afb0b5fb87d33 = from_latin_1_string("\042);\012", 4);
  string__f3d6bf47fb36a3e0 = from_latin_1_string("  report__event(\042", 17);
  string__47540a9adb64843c = from_latin_1_string(
    "    }\n"
    "  } else {\n",
    17);
  string__3f8698e0b2f30ecd = from_latin_1_string("    if (replay__action(\042", 24);
  string__ca1f46618166c2dd = from_latin_1_string("\042)) {\012", 6);
  string__12661159642bb65a = from_latin_1_string("  } else {", 10);
  string__c440cd65102e84e8 = from_latin_1_string("SAMPLE_POINTER", 14);
  func__107_93 = create_function(entry__107_93, 0);
  string__fa730415fc16bec = from_latin_1_string(" = ", 3);
  string__d81f466d0154f2dd = from_latin_1_string(
    ";\n"
    "  }\n",
    6);
  string__4fbb5986ed8ccf7 = from_latin_1_string("    report__event(\042", 19);
  func__107_2 = create_function(entry__107_2, 0);
  string__3c202d3e36291121 = from_latin_1_string("UNDEFINED", 9);
  string__7ca0252e172b1501 = from_latin_1_string("undefined", 9);
  string__760ae00b5cf07d76 = from_latin_1_string("ZERO", 4);
  string__360ae80b5df07d56 = from_latin_1_string("zero", 4);
  string__6a0ae5cb5cc87d7c = from_latin_1_string("TRUE", 4);
  string__62d904ca56abf62f = from_latin_1_string("boolean_true", 12);
  string__85ae003eb527012 = from_latin_1_string("FALSE", 5);
  string__52b31fb1ca36ad = from_latin_1_string("boolean_false", 13);
  string__ae20f214ef3d4185 = from_latin_1_string("EMPTY_STRING", 12);
  string__ee21fa04ce7f45ad = from_latin_1_string("empty_string", 12);
  string__242c2d3622a1a2b6 = from_latin_1_string("ARGUMENTS", 9);
  string__bdf1fe7d3fa3f48e = from_latin_1_string("arguments->slots[$1]", 20);
  string__6a0ae70b5ce07d7c = from_latin_1_string("TYPE", 4);
  string__10f0a21e06f5c291 = from_latin_1_string("type__$1", 8);
  string__381f5f1a80c1c291 = from_latin_1_string("TYPEOF", 6);
  string__1c42567d62ae9fc4 = from_latin_1_string("($1)->type", 10);
  string__2c1f5f1900c0c291 = from_latin_1_string("SIZEOF", 6);
  string__c207e6e98f96cbad = from_latin_1_string("($1)->attributes->vtable->size", 30);
  string__88b83a651b4554fc = from_latin_1_string("RETURN_NOTHING", 14);
  string__e713ee46cfe40ca0 = from_latin_1_string(
    "{\n"
    "  argument_count = 0;\n"
    "  func = frame->cont;\n"
    "  frame->cont = invalid_continuation;\n"
    "  return;\n"
    "}",
    95);
  string__75924e59eefc3c27 = from_latin_1_string("RETURN_SINGLE_RESULT", 20);
  string__c9e5fa593f26b652 = from_latin_1_string(
    "{\n"
    "  NODE *result__node = (NODE *)($1);\n"
    "  arguments = node_p;\n"
    "  arguments->slots[0] = result__node;\n"
    "  argument_count = 1;\n"
    "  func = frame->cont;\n"
    "  frame->cont = invalid_continuation;\n"
    "  return;\n"
    "}",
    192);
  string__808839651b3ce4f5 = from_latin_1_string("RETURN_BOOLEAN", 14);
  string__76174d28d266419 = from_latin_1_string("RETURN_SINGLE_RESULT(from_bool($1))", 35);
  string__df153d64b7266922 = from_latin_1_string("RETURN_UNDEFINED", 16);
  string__a89eeef2e6ec47d6 = from_latin_1_string(
    "{\n"
    "  arguments = node_p;\n"
    "  arguments->slots[0] = undefined;\n"
    "  argument_count = 1;\n"
    "  func = frame->cont;\n"
    "  frame->cont = invalid_continuation;\n"
    "  return;\n"
    "}",
    152);
  string__681415cc9aa25dc9 = from_latin_1_string("RETURN_TRUE", 11);
  string__62013454820fcbb4 = from_latin_1_string(
    "{\n"
    "  arguments = node_p;\n"
    "  arguments->slots[0] = boolean_true;\n"
    "  argument_count = 1;\n"
    "  func = frame->cont;\n"
    "  frame->cont = invalid_continuation;\n"
    "  return;\n"
    "}",
    155);
  string__8864d352eefa60e5 = from_latin_1_string("RETURN_FALSE", 12);
  string__e7e98d9fbc185a2b = from_latin_1_string(
    "{\n"
    "  arguments = node_p;\n"
    "  arguments->slots[0] = boolean_false;\n"
    "  argument_count = 1;\n"
    "  func = frame->cont;\n"
    "  frame->cont = invalid_continuation;\n"
    "  return;\n"
    "}",
    156);
  string__7414100c9a9a5dc3 = from_latin_1_string("RETURN_ZERO", 11);
  string__d0d6524fe2f4619c = from_latin_1_string(
    "{\n"
    "  arguments = node_p;\n"
    "  arguments->slots[0] = zero;\n"
    "  argument_count = 1;\n"
    "  func = frame->cont;\n"
    "  frame->cont = invalid_continuation;\n"
    "  return;\n"
    "}",
    147);
  string__4388537a39721213 = from_latin_1_string("START_ARGUMENTS", 15);
  string__85e7f27c75b002fc = from_latin_1_string(
    "argument_count = $1;\n"
    "arguments = node_p;",
    40);
  string__301f5b1980280299 = from_latin_1_string("RETURN", 6);
  string__f4e01cf5f7a8d221 = from_latin_1_string(
    "{\n"
    "  func = frame->cont;\n"
    "  frame->cont = invalid_continuation;\n"
    "  return;\n"
    "}",
    73);
  string__1a5ae343eb822019 = from_latin_1_string("CHAIN", 5);
  string__ab6aca91eb0633a9 = from_latin_1_string(
    "{\n"
    "  func = myself->type;\n"
    "  return;\n"
    "}",
    36);
  string__690816604df6099f = from_latin_1_string("UNRECOVERABLE_ERROR", 19);
  string__7a5a4cdb9d9e0e09 = from_latin_1_string("unrecoverable_error($*);", 24);
  string__adfe76f306663a82 = from_latin_1_string("OUT_OF_MEMORY_ERROR", 19);
  string__55fab4fde7164944 = from_latin_1_string("out_of_memory_error();", 22);
  string__26ff7f9f9c5c0312 = from_latin_1_string("RUNTIME_ERROR", 13);
  string__7317d013e72f1e80 = from_latin_1_string(
    "{\n"
    "  runtime_error($*);\n"
    "}",
    24);
  string__fce3f40028924a51 = from_latin_1_string("TOO_FEW_ARGUMENTS_ERROR", 23);
  string__64a4d424679d8650 = from_latin_1_string(
    "{\n"
    "  too_few_arguments_error();\n"
    "}",
    32);
  string__aab70cfc8956db67 = from_latin_1_string("TOO_MANY_ARGUMENTS_ERROR", 24);
  string__e8cfae9434301166 = from_latin_1_string(
    "{\n"
    "  too_many_arguments_error();\n"
    "}",
    33);
  string__6cf0c8742a12ca30 = from_latin_1_string("INVALID_ARGUMENTS_ERROR", 23);
  string__65e49414af94386a = from_latin_1_string(
    "{\n"
    "  invalid_arguments_error();\n"
    "}",
    32);
  string__1adfaddd8e34edf5 = from_latin_1_string("TOO_FEW_RESULTS_ERROR", 21);
  string__e77c83ca19b4e164 = from_latin_1_string(
    "{\n"
    "  too_few_results_error();\n"
    "}",
    30);
  string__e858bf99576dbe16 = from_latin_1_string("TOO_MANY_RESULTS_ERROR", 22);
  string__26323596c3854c8e = from_latin_1_string(
    "{\n"
    "  too_many_results_error();\n"
    "}",
    31);
  string__cad5afdc0874a104 = from_latin_1_string("INVALID_RESULTS_ERROR", 21);
  string__245ca532f1b1e064 = from_latin_1_string(
    "{\n"
    "  invalid_results_error();\n"
    "}",
    30);
  string__aa786f40ccc234b9 = from_latin_1_string("INVALID_INDEX_ERROR", 19);
  string__b633324328a52c38 = from_latin_1_string(
    "{\n"
    "  invalid_index_error();\n"
    "}",
    28);
  string__37ce8a8da4c412d5 = from_latin_1_string("DIVIDE_BY_ZERO_ERROR", 20);
  string__b69de9e24cd9d6a2 = from_latin_1_string(
    "{\n"
    "  divide_by_zero_error();\n"
    "}",
    29);
  string__221e44965d54351b = from_latin_1_string("NOT_YET_IMPLEMENTED_ERROR", 25);
  string__13951d152a225118 = from_latin_1_string(
    "{\n"
    "  not_yet_implemented_error();\n"
    "}",
    34);
  string__e4ae97e99176a5b2 = from_latin_1_string("NO_SUCH_FUNCTION_ERROR", 22);
  string__413ff844cdfe78b6 = from_latin_1_string(
    "{\n"
    "  no_such_function_error();\n"
    "}",
    31);
  string__3c9404ad0742476f = from_latin_1_string("RESOURCE_ERROR", 14);
  string__6a3612ac9bfecfbc = from_latin_1_string(
    "{\n"
    "  resource_error();\n"
    "}",
    23);
  string__a28a14985afc552 = from_latin_1_string("IO_ERROR", 8);
  string__1f25251097233e14 = from_latin_1_string(
    "{\n"
    "  io_error();\n"
    "}",
    17);
}

static int already_run_phase_3 = false;

EXPORT void phase_3__macros(void) {
  if (already_run_phase_3) return;
  already_run_phase_3 = true;
  set_module("macros");
  set_used_namespaces(used_namespaces);
  assign_value(&var._EVENT, unique__EVENT);
  assign_value(&var._ACTION, unique__ACTION);
  assign_value(&var._INFO, unique__INFO);
  assign_value(&var._DATA, unique__DATA);
  register_dynamic(&dyna_idx__event_name);
  define__event_name(undefined);
  register_dynamic(&dyna_idx__event_kind);
  define__event_kind(undefined);
  register_dynamic(&dyna_idx__event_phase);
  define__event_phase(undefined);
  register_dynamic(&dyna_idx__data_variables);
  define__data_variables(undefined);
  register_dynamic(&dyna_idx__info_variables);
  define__info_variables(undefined);
  define_single_assign_static("compiler", "converted", get__compiler__converted, &var.compiler__converted);
}

static int already_run_phase_4 = false;

EXPORT void phase_4__macros(void) {
  if (already_run_phase_4) return;
  already_run_phase_4 = true;
  set_module("macros");
  set_used_namespaces(used_namespaces);
  use_read_only(NULL, "append", &get__append, &get_value_or_future__append);
  use_read_only(NULL, "case", &get__case, &get_value_or_future__case);
  use_read_only(NULL, "cond", &get__cond, &get_value_or_future__cond);
  use_read_only(NULL, "contains", &get__contains, &get_value_or_future__contains);
  use_read_only(NULL, "converted", &get__converted, &get_value_or_future__converted);
  use_read_only(NULL, "dec", &get__dec, &get_value_or_future__dec);
  use_read_only(NULL, "do", &get__do, &get_value_or_future__do);
  use_read_only(NULL, "empty_list", &get__empty_list, &get_value_or_future__empty_list);
  use_read_only(NULL, "empty_table", &get__empty_table, &get_value_or_future__empty_table);
  use_read_only(NULL, "false", &get__false, &get_value_or_future__false);
  use_read_only(NULL, "for_each", &get__for_each, &get_value_or_future__for_each);
  use_read_only(NULL, "global_names", &get__global_names, &get_value_or_future__global_names);
  use_read_only(NULL, "if", &get__if, &get_value_or_future__if);
  use_read_only(NULL, "inc", &get__inc, &get_value_or_future__inc);
  use_read_only(NULL, "is_a_string", &get__is_a_string, &get_value_or_future__is_a_string);
  use_read_only(NULL, "is_defined", &get__is_defined, &get_value_or_future__is_defined);
  use_read_only(NULL, "is_empty", &get__is_empty, &get_value_or_future__is_empty);
  use_read_only(NULL, "join", &get__join, &get_value_or_future__join);
  use_read_only(NULL, "length_of", &get__length_of, &get_value_or_future__length_of);
  use_read_only(NULL, "list", &get__list, &get_value_or_future__list);
  use_read_only(NULL, "pass", &get__pass, &get_value_or_future__pass);
  use_read_only(NULL, "push", &get__push, &get_value_or_future__push);
  use_read_only(NULL, "put", &get__put, &get_value_or_future__put);
  use_read_only(NULL, "range", &get__range, &get_value_or_future__range);
  use_read_only(NULL, "replace_all", &get__replace_all, &get_value_or_future__replace_all);
  use_read_only("std", "and", &get__std__and, &get_value_or_future__std__and);
  use_read_only("std", "equal", &get__std__equal, &get_value_or_future__std__equal);
  use_read_only("std", "key_value_pair", &get__std__key_value_pair, &get_value_or_future__std__key_value_pair);
  use_read_only("std", "less", &get__std__less, &get_value_or_future__std__less);
  use_read_only("std", "minus", &get__std__minus, &get_value_or_future__std__minus);
  use_read_only("std", "negate", &get__std__negate, &get_value_or_future__std__negate);
  use_read_only("std", "not", &get__std__not, &get_value_or_future__std__not);
  use_read_only("std", "plus", &get__std__plus, &get_value_or_future__std__plus);
  use_read_only("std", "sequence", &get__std__sequence, &get_value_or_future__std__sequence);
  use_read_only("std", "string", &get__std__string, &get_value_or_future__std__string);
  use_read_only("std", "value_range", &get__std__value_range, &get_value_or_future__std__value_range);
  use_read_only(NULL, "trim", &get__trim, &get_value_or_future__trim);
  use_read_only(NULL, "true", &get__true, &get_value_or_future__true);
  use_read_only(NULL, "undefined", &get__undefined, &get_value_or_future__undefined);
  use_read_only(NULL, "unless", &get__unless, &get_value_or_future__unless);
  use_read_only(NULL, "use_identifier", &get__use_identifier, &get_value_or_future__use_identifier);
  use_read_only(NULL, "while", &get__while, &get_value_or_future__while);
  use_read_only(NULL, "write_to", &get__write_to, &get_value_or_future__write_to);
  use_read_only(NULL, "writeln_to", &get__writeln_to, &get_value_or_future__writeln_to);
}

static int already_run_phase_5 = false;

EXPORT void phase_5__macros(void) {
  if (already_run_phase_5) return;
  already_run_phase_5 = true;
  assign_variable(&var._define_macro, &func__define_macro_1);
  assign_variable(&var.compiler__converted, &func__compiler__converted_1);
}

static int already_run_phase_6 = false;

EXPORT void phase_6__macros(void) {
  if (already_run_phase_6) return;
  already_run_phase_6 = true;
  register_collector(collect__macros);
}
