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
IMPORT void too_few_arguments_error(void);
IMPORT void too_many_arguments_error(void);
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
REGISTER int argument_count ASM("ebx");
IMPORT void invalid_arguments_error(void);
IMPORT void *node_p;
IMPORT void allocate_arguments(void);
IMPORT NODE *create_cell(void);
IMPORT NODE *create_cell_with_contents(NODE *contents);
IMPORT NODE *from_arguments(int first_idx, int count);
typedef struct CELL {
  FUNC type;
  struct ATTRIBUTES *attributes;
  NODE *contents;
} CELL;
IMPORT NODE *create_closure(FUNC type, int par_count);
IMPORT int result_count;
REGISTER NODE *myself ASM("r13");
IMPORT void invalid_results_error(void);
IMPORT NODE *create_future(void);
IMPORT void initialize_future(NODE *var, NODE *val);
IMPORT NODE *empty_string;
IMPORT void too_few_results_error(void);
IMPORT void too_many_results_error(void);
IMPORT void terminate(int exit_code);
IMPORT NODE *create_continuation(void);
IMPORT NODE *collect_node(NODE *node);
IMPORT void register_module_info(MODULE_INFO *info);
IMPORT NODE *from_uchar32(unsigned int chr);
IMPORT NODE *from_uint32(uint32_t val);
IMPORT NODE *register_unique_item(const char *name);
IMPORT NODE *create_function(FUNC func, int par_count);
IMPORT NODE *from_latin_1_string(const char *str, long len);
IMPORT void set_module(const char *name);
IMPORT void set_used_namespaces(const char **namespaces);
IMPORT void assign_value(NODE **dest, NODE *val);
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
static NODE_GETTER get__Error;
static NODE_GETTER get_value_or_future__Error;
static NODE_GETTER get__MANDATORY_PARAMETER;
static NODE_GETTER get_value_or_future__MANDATORY_PARAMETER;
static NODE_GETTER get__MANY_PARAMETERS;
static NODE_GETTER get_value_or_future__MANY_PARAMETERS;
static NODE_GETTER get__MULTI_VALUED_OPTION;
static NODE_GETTER get_value_or_future__MULTI_VALUED_OPTION;
static NODE_GETTER get__OPTIONAL_PARAMETER;
static NODE_GETTER get_value_or_future__OPTIONAL_PARAMETER;
static NODE_GETTER get__SOME_PARAMETERS;
static NODE_GETTER get_value_or_future__SOME_PARAMETERS;
static NODE_GETTER get__VALUED_OPTION;
static NODE_GETTER get_value_or_future__VALUED_OPTION;
static NODE_GETTER get__append;
static NODE_GETTER get_value_or_future__append;
static NODE_GETTER get__case;
static NODE_GETTER get_value_or_future__case;
static NODE_GETTER get__command_line_arguments;
static NODE_GETTER get_value_or_future__command_line_arguments;
static NODE_GETTER get__cond;
static NODE_GETTER get_value_or_future__cond;
static NODE_GETTER get__debug_string;
static NODE_GETTER get_value_or_future__debug_string;
static NODE_GETTER get__delete_at;
static NODE_GETTER get_value_or_future__delete_at;
static NODE_GETTER get__do;
static NODE_GETTER get_value_or_future__do;
static NODE_GETTER get__dup;
static NODE_GETTER get_value_or_future__dup;
static NODE_GETTER get__empty_insert_order_table;
static NODE_GETTER get_value_or_future__empty_insert_order_table;
static NODE_GETTER get__empty_key_order_table;
static NODE_GETTER get_value_or_future__empty_key_order_table;
static NODE_GETTER get__empty_list;
static NODE_GETTER get_value_or_future__empty_list;
static NODE_GETTER get__ewrite;
static NODE_GETTER get_value_or_future__ewrite;
static NODE_GETTER get__ewriteln;
static NODE_GETTER get_value_or_future__ewriteln;
static NODE_GETTER get__exit;
static NODE_GETTER get_value_or_future__exit;
static NODE_GETTER get__extend_to;
static NODE_GETTER get_value_or_future__extend_to;
static NODE_GETTER get__false;
static NODE_GETTER get_value_or_future__false;
static NODE_GETTER get__for_each;
static NODE_GETTER get_value_or_future__for_each;
static NODE_GETTER get__for_each_from_down_to;
static NODE_GETTER get_value_or_future__for_each_from_down_to;
static NODE_GETTER get__for_each_from_to;
static NODE_GETTER get_value_or_future__for_each_from_to;
static NODE_GETTER get__for_each_line;
static NODE_GETTER get_value_or_future__for_each_line;
static NODE_GETTER get__from_utf8;
static NODE_GETTER get_value_or_future__from_utf8;
static NODE_GETTER get__get;
static NODE_GETTER get_value_or_future__get;
static NODE_GETTER get__has_prefix;
static NODE_GETTER get_value_or_future__has_prefix;
static NODE_GETTER get__if;
static NODE_GETTER get_value_or_future__if;
static NODE_GETTER get__inc;
static NODE_GETTER get_value_or_future__inc;
static NODE_GETTER get__indented;
static NODE_GETTER get_value_or_future__indented;
static NODE_GETTER get__is_a_key_value_pair;
static NODE_GETTER get_value_or_future__is_a_key_value_pair;
static NODE_GETTER get__is_a_list;
static NODE_GETTER get_value_or_future__is_a_list;
static NODE_GETTER get__is_a_string;
static NODE_GETTER get_value_or_future__is_a_string;
static NODE_GETTER get__is_defined;
static NODE_GETTER get_value_or_future__is_defined;
static NODE_GETTER get__is_empty;
static NODE_GETTER get_value_or_future__is_empty;
static NODE_GETTER get__is_undefined;
static NODE_GETTER get_value_or_future__is_undefined;
static NODE_GETTER get__key_of;
static NODE_GETTER get_value_or_future__key_of;
static NODE_GETTER get__length_of;
static NODE_GETTER get_value_or_future__length_of;
static NODE_GETTER get__list;
static NODE_GETTER get_value_or_future__list;
static NODE_GETTER get__map;
static NODE_GETTER get_value_or_future__map;
static NODE_GETTER get__pad_right;
static NODE_GETTER get_value_or_future__pad_right;
static NODE_GETTER get__plus;
static NODE_GETTER get_value_or_future__plus;
static NODE_GETTER get__pop;
static NODE_GETTER get_value_or_future__pop;
static NODE_GETTER get__program_name;
static NODE_GETTER get_value_or_future__program_name;
static NODE_GETTER get__push;
static NODE_GETTER get_value_or_future__push;
static NODE_GETTER get__range;
static NODE_GETTER get_value_or_future__range;
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
static NODE_GETTER get__string;
static NODE_GETTER get_value_or_future__string;
static NODE_GETTER get__terminate;
static NODE_GETTER get_value_or_future__terminate;
static NODE_GETTER get__to_upper_case;
static NODE_GETTER get_value_or_future__to_upper_case;
static NODE_GETTER get__true;
static NODE_GETTER get_value_or_future__true;
static NODE_GETTER get__truncate_until;
static NODE_GETTER get_value_or_future__truncate_until;
static NODE_GETTER get__undefined;
static NODE_GETTER get_value_or_future__undefined;
static NODE_GETTER get__unless;
static NODE_GETTER get_value_or_future__unless;
static NODE_GETTER get__value_of;
static NODE_GETTER get_value_or_future__value_of;
static NODE_GETTER get__write_to;
static NODE_GETTER get_value_or_future__write_to;
static struct {
  NODE *_BOOLEAN_OPTION;
  NODE *_program_version;
  NODE *_program_copyright;
  NODE *_display_table;
  NODE *_command_id;
  NODE *_command_id_count;
  NODE *_command_names;
  NODE *_command_descriptions;
  NODE *_show_version;
  NODE *_show_copyright;
  NODE *_check_arguments;
  NODE *_show_commands;
  NODE *std__VALUED_OPTION;
  NODE *std__MULTI_VALUED_OPTION;
  NODE *std__MANDATORY_PARAMETER;
  NODE *std__OPTIONAL_PARAMETER;
  NODE *std__SOME_PARAMETERS;
  NODE *std__MANY_PARAMETERS;
  NODE *std__copyright;
  NODE *std__version;
  NODE *std__extract_options;
  NODE *std__extract_some_options;
  NODE *std__program_commands;
  NODE *std__command_parameters;
  NODE *std__program_parameters;
} var;
static const char *var_names[] = {
  "BOOLEAN_OPTION",
  "program_version",
  "program_copyright",
  "display_table",
  "command_id",
  "command_id_count",
  "command_names",
  "command_descriptions",
  "show_version",
  "show_copyright",
  "check_arguments",
  "show_commands"
};
static NODE *unique__BOOLEAN_OPTION;
static NODE *unique__std__VALUED_OPTION;
static NODE *get__std__VALUED_OPTION(void) {
  return var.std__VALUED_OPTION;
}
static NODE *unique__std__MULTI_VALUED_OPTION;
static NODE *get__std__MULTI_VALUED_OPTION(void) {
  return var.std__MULTI_VALUED_OPTION;
}
static NODE *unique__std__MANDATORY_PARAMETER;
static NODE *get__std__MANDATORY_PARAMETER(void) {
  return var.std__MANDATORY_PARAMETER;
}
static NODE *unique__std__OPTIONAL_PARAMETER;
static NODE *get__std__OPTIONAL_PARAMETER(void) {
  return var.std__OPTIONAL_PARAMETER;
}
static NODE *unique__std__SOME_PARAMETERS;
static NODE *get__std__SOME_PARAMETERS(void) {
  return var.std__SOME_PARAMETERS;
}
static NODE *unique__std__MANY_PARAMETERS;
static NODE *get__std__MANY_PARAMETERS(void) {
  return var.std__MANY_PARAMETERS;
}
static NODE *func__10_1_std__copyright;
static void entry__10_1_std__copyright(void);
static FRAME_INFO frame__10_1_std__copyright = {1, {"msg"}};
static NODE *get__std__copyright(void) {
  return var.std__copyright;
}
static NODE *func__11_1_std__version;
static void entry__11_1_std__version(void);
static FRAME_INFO frame__11_1_std__version = {1, {"no"}};
static NODE *get__std__version(void) {
  return var.std__version;
}
static NODE *func__12_1_std__extract_options;
static void entry__12_1_std__extract_options(void);
static FRAME_INFO frame__12_1_std__extract_options = {4, {"options", "templates", "results", "parameters"}};
static NODE *func__12_2;
static void entry__12_2(void);
static FRAME_INFO frame__12_2 = {3, {"options", "parameters", "idx"}};
static NODE *func__12_3;
static void entry__12_3(void);
static FRAME_INFO frame__12_3 = {4, {"option", "idx", "parameters", "options"}};
static void cont__12_4(void);
static NODE *func__12_5;
static void entry__12_5(void);
static FRAME_INFO frame__12_5 = {1, {"idx"}};
static void cont__12_6(void);
static NODE *func__12_7;
static void entry__12_7(void);
static FRAME_INFO frame__12_7 = {4, {"parameters", "option", "options", "idx"}};
static void cont__12_8(void);
static void cont__12_9(void);
static void cont__12_10(void);
static NODE *func__12_11;
static void entry__12_11(void);
static FRAME_INFO frame__12_11 = {5, {"template", "options", "results", "result", "idx"}};
static void cont__12_12(void);
static void cont__12_13(void);
static NODE *func__12_14;
static void entry__12_14(void);
static FRAME_INFO frame__12_14 = {4, {"result", "options", "template", "idx"}};
static NODE *func__12_15;
static void entry__12_15(void);
static FRAME_INFO frame__12_15 = {5, {"option", "template", "options", "idx", "result"}};
static void cont__12_16(void);
static void cont__12_17(void);
static void cont__12_18(void);
static NODE *func__12_19;
static void entry__12_19(void);
static FRAME_INFO frame__12_19 = {4, {"options", "idx", "result", "option"}};
static void cont__12_20(void);
static void cont__12_21(void);
static void cont__12_22(void);
static NODE *func__12_23;
static void entry__12_23(void);
static FRAME_INFO frame__12_23 = {1, {"idx"}};
static void cont__12_24(void);
static NODE *func__12_25;
static void entry__12_25(void);
static FRAME_INFO frame__12_25 = {4, {"options", "template", "idx", "result"}};
static NODE *func__12_26;
static void entry__12_26(void);
static FRAME_INFO frame__12_26 = {5, {"option", "template", "options", "idx", "result"}};
static void cont__12_27(void);
static void cont__12_28(void);
static void cont__12_29(void);
static NODE *func__12_30;
static void entry__12_30(void);
static FRAME_INFO frame__12_30 = {4, {"options", "idx", "result", "option"}};
static void cont__12_31(void);
static void cont__12_32(void);
static NODE *func__12_33;
static void entry__12_33(void);
static FRAME_INFO frame__12_33 = {1, {"idx"}};
static void cont__12_34(void);
static void cont__12_35(void);
static void cont__12_36(void);
static void cont__12_37(void);
static void cont__12_38(void);
static NODE *func__12_39;
static void entry__12_39(void);
static FRAME_INFO frame__12_39 = {1, {"options"}};
static void cont__12_40(void);
static void cont__12_41(void);
static void cont__12_42(void);
static void cont__12_43(void);
static void cont__12_44(void);
static NODE *string__12_45;
static NODE *string__12_46;
static void cont__12_47(void);
static void cont__12_48(void);
static NODE *get__std__extract_options(void) {
  return var.std__extract_options;
}
static NODE *func__13_1_std__extract_some_options;
static void entry__13_1_std__extract_some_options(void);
static FRAME_INFO frame__13_1_std__extract_some_options = {3, {"options", "templates", "results"}};
static NODE *func__13_2;
static void entry__13_2(void);
static FRAME_INFO frame__13_2 = {5, {"template", "options", "results", "result", "idx"}};
static void cont__13_3(void);
static void cont__13_4(void);
static NODE *func__13_5;
static void entry__13_5(void);
static FRAME_INFO frame__13_5 = {4, {"result", "options", "template", "idx"}};
static NODE *func__13_6;
static void entry__13_6(void);
static FRAME_INFO frame__13_6 = {5, {"option", "template", "options", "idx", "result"}};
static void cont__13_7(void);
static void cont__13_8(void);
static void cont__13_9(void);
static NODE *func__13_10;
static void entry__13_10(void);
static FRAME_INFO frame__13_10 = {4, {"options", "idx", "result", "option"}};
static void cont__13_11(void);
static void cont__13_12(void);
static void cont__13_13(void);
static NODE *func__13_14;
static void entry__13_14(void);
static FRAME_INFO frame__13_14 = {1, {"idx"}};
static void cont__13_15(void);
static NODE *func__13_16;
static void entry__13_16(void);
static FRAME_INFO frame__13_16 = {4, {"options", "template", "idx", "result"}};
static NODE *func__13_17;
static void entry__13_17(void);
static FRAME_INFO frame__13_17 = {5, {"option", "template", "options", "idx", "result"}};
static void cont__13_18(void);
static NODE *func__13_19;
static void entry__13_19(void);
static FRAME_INFO frame__13_19 = {2, {"option", "template"}};
static void cont__13_20(void);
static void cont__13_21(void);
static void cont__13_22(void);
static void cont__13_23(void);
static NODE *func__13_24;
static void entry__13_24(void);
static FRAME_INFO frame__13_24 = {4, {"options", "idx", "result", "option"}};
static void cont__13_25(void);
static void cont__13_26(void);
static NODE *func__13_27;
static void entry__13_27(void);
static FRAME_INFO frame__13_27 = {1, {"idx"}};
static void cont__13_28(void);
static void cont__13_29(void);
static void cont__13_30(void);
static void cont__13_31(void);
static NODE *get__std__extract_some_options(void) {
  return var.std__extract_some_options;
}
static NODE *func__14_1_display_table;
static void entry__14_1_display_table(void);
static FRAME_INFO frame__14_1_display_table = {2, {"tab", "first_column_width"}};
static NODE *func__14_2;
static void entry__14_2(void);
static FRAME_INFO frame__14_2 = {2, {"entry", "first_column_width"}};
static void cont__14_3(void);
static void cont__14_4(void);
static void cont__14_5(void);
static void cont__14_6(void);
static void cont__14_7(void);
static NODE *func__14_8;
static void entry__14_8(void);
static FRAME_INFO frame__14_8 = {2, {"entry", "first_column_width"}};
static void cont__14_9(void);
static void cont__14_10(void);
static NODE *string__14_11;
static void cont__14_12(void);
static void cont__14_13(void);
static NODE *func__14_14;
static void entry__14_14(void);
static FRAME_INFO frame__14_14 = {3, {"idx", "line", "first_column_width"}};
static void cont__14_15(void);
static void cont__14_16(void);
static NODE *func__14_17;
static void entry__14_17(void);
static FRAME_INFO frame__14_17 = {1, {"first_column_width"}};
static void cont__14_18(void);
static NODE *string__14_19;
static void cont__14_20(void);
static void cont__14_21(void);
static NODE *func__19_1_show_version;
static void entry__19_1_show_version(void);
static FRAME_INFO frame__19_1_show_version = {1, {"command_name"}};
static NODE *string__19_2;
static void cont__19_3(void);
static NODE *func__20_1_show_copyright;
static void entry__20_1_show_copyright(void);
static FRAME_INFO frame__20_1_show_copyright = {0, {}};
static NODE *func__21_1_check_arguments;
static void entry__21_1_check_arguments(void);
static FRAME_INFO frame__21_1_check_arguments = {18, {"command", "arguments", "templates", "results", "options", "parameters", "names", "kinds", "possible_values", "default_values", "conversions", "help_messages", "command_name", "help_message", "show_usage", "too_few_arguments_error", "too_many_arguments_error", "last_idx"}};
static NODE *func__21_2_help_message;
static void entry__21_2_help_message(void);
static FRAME_INFO frame__21_2_help_message = {5, {"idx", "help_messages", "possible_values", "message", "possible_value"}};
static void cont__21_3(void);
static void cont__21_4(void);
static void cont__21_5(void);
static NODE *func__21_6;
static void entry__21_6(void);
static FRAME_INFO frame__21_6 = {2, {"message", "possible_value"}};
static NODE *string__21_7;
static void cont__21_8(void);
static NODE *func__21_9;
static void entry__21_9(void);
static FRAME_INFO frame__21_9 = {2, {"value", "message"}};
static void cont__21_10(void);
static void cont__21_11(void);
static void cont__21_12(void);
static void cont__21_13(void);
static void cont__21_14(void);
static NODE *func__21_15_show_usage;
static void entry__21_15_show_usage(void);
static FRAME_INFO frame__21_15_show_usage = {8, {"kinds", "command_name", "command", "parameters", "help_message", "options", "help_messages", "parameter_name"}};
static NODE *func__21_16_parameter_name;
static void entry__21_16_parameter_name(void);
static FRAME_INFO frame__21_16_parameter_name = {4, {"parameter", "idx", "kinds", "buf"}};
static void cont__21_17(void);
static void cont__21_18(void);
static NODE *func__21_19;
static void entry__21_19(void);
static FRAME_INFO frame__21_19 = {1, {"buf"}};
static void cont__21_20(void);
static NODE *func__21_21;
static void entry__21_21(void);
static FRAME_INFO frame__21_21 = {1, {"buf"}};
static void cont__21_22(void);
static NODE *func__21_23;
static void entry__21_23(void);
static FRAME_INFO frame__21_23 = {1, {"buf"}};
static void cont__21_24(void);
static void cont__21_25(void);
static void cont__21_26(void);
static NODE *func__21_27;
static void entry__21_27(void);
static FRAME_INFO frame__21_27 = {1, {"command_name"}};
static void cont__21_28(void);
static void cont__21_29(void);
static NODE *func__21_30;
static void entry__21_30(void);
static FRAME_INFO frame__21_30 = {2, {"command_name", "command"}};
static void cont__21_31(void);
static void cont__21_32(void);
static void cont__21_33(void);
static void cont__21_34(void);
static NODE *string__21_35;
static void cont__21_36(void);
static void cont__21_37(void);
static NODE *func__21_38;
static void entry__21_38(void);
static FRAME_INFO frame__21_38 = {1, {"command_name"}};
static void cont__21_39(void);
static NODE *func__21_40;
static void entry__21_40(void);
static FRAME_INFO frame__21_40 = {1, {"command_name"}};
static NODE *string__21_41;
static void cont__21_42(void);
static NODE *string__21_43;
static void cont__21_44(void);
static void cont__21_45(void);
static NODE *func__21_46;
static void entry__21_46(void);
static FRAME_INFO frame__21_46 = {1, {"command"}};
static void cont__21_47(void);
static NODE *func__21_48;
static void entry__21_48(void);
static FRAME_INFO frame__21_48 = {0, {}};
static void cont__21_49(void);
static void cont__21_50(void);
static NODE *func__21_51;
static void entry__21_51(void);
static FRAME_INFO frame__21_51 = {3, {"parameter", "idx", "parameter_name"}};
static void cont__21_52(void);
static void cont__21_53(void);
static void cont__21_54(void);
static NODE *string__21_55;
static void cont__21_56(void);
static NODE *func__21_57;
static void entry__21_57(void);
static FRAME_INFO frame__21_57 = {4, {"parameters", "parameter_name", "help_message", "tab"}};
static NODE *func__21_58;
static void entry__21_58(void);
static FRAME_INFO frame__21_58 = {5, {"parameter", "idx", "tab", "parameter_name", "help_message"}};
static void cont__21_59(void);
static void cont__21_60(void);
static void cont__21_61(void);
static void cont__21_62(void);
static void cont__21_63(void);
static void cont__21_64(void);
static void cont__21_65(void);
static NODE *func__21_66;
static void entry__21_66(void);
static FRAME_INFO frame__21_66 = {3, {"options", "kinds", "help_messages"}};
static NODE *string__21_67;
static void cont__21_68(void);
static NODE *func__21_69;
static void entry__21_69(void);
static FRAME_INFO frame__21_69 = {4, {"options", "kinds", "help_messages", "tab"}};
static NODE *func__21_70;
static void entry__21_70(void);
static FRAME_INFO frame__21_70 = {6, {"option", "idx", "kinds", "tab", "help_messages", "option_name"}};
static NODE *func__21_71_option_name;
static void entry__21_71_option_name(void);
static FRAME_INFO frame__21_71_option_name = {4, {"option", "kinds", "idx", "buf"}};
static NODE *string__21_72;
static void cont__21_73(void);
static void cont__21_74(void);
static NODE *func__21_75;
static void entry__21_75(void);
static FRAME_INFO frame__21_75 = {1, {"buf"}};
static NODE *string__21_76;
static void cont__21_77(void);
static NODE *func__21_78;
static void entry__21_78(void);
static FRAME_INFO frame__21_78 = {1, {"buf"}};
static NODE *string__21_79;
static void cont__21_80(void);
static void cont__21_81(void);
static void cont__21_82(void);
static void cont__21_83(void);
static void cont__21_84(void);
static void cont__21_85(void);
static void cont__21_86(void);
static NODE *func__21_87_too_few_arguments_error;
static void entry__21_87_too_few_arguments_error(void);
static FRAME_INFO frame__21_87_too_few_arguments_error = {2, {"command", "show_usage"}};
static void cont__21_88(void);
static NODE *func__21_89;
static void entry__21_89(void);
static FRAME_INFO frame__21_89 = {1, {"command"}};
static NODE *string__21_90;
static NODE *string__21_91;
static void cont__21_92(void);
static NODE *func__21_93;
static void entry__21_93(void);
static FRAME_INFO frame__21_93 = {0, {}};
static NODE *string__21_94;
static void cont__21_95(void);
static void cont__21_96(void);
static NODE *func__21_97_too_many_arguments_error;
static void entry__21_97_too_many_arguments_error(void);
static FRAME_INFO frame__21_97_too_many_arguments_error = {1, {"show_usage"}};
static NODE *string__21_98;
static void cont__21_99(void);
static void cont__21_100(void);
static void cont__21_101(void);
static void cont__21_102(void);
static void cont__21_103(void);
static NODE *func__21_104;
static void entry__21_104(void);
static FRAME_INFO frame__21_104 = {16, {"idx", "template", "possible_values", "names", "kinds", "default_values", "conversions", "help_messages", "results", "options", "parameters", "option", "name", "default_value", "conversion", "help"}};
static void cont__21_105(void);
static void cont__21_106(void);
static NODE *func__21_107;
static void entry__21_107(void);
static FRAME_INFO frame__21_107 = {2, {"possible_values", "option"}};
static void cont__21_108(void);
static void cont__21_109(void);
static void cont__21_110(void);
static NODE *func__21_111;
static void entry__21_111(void);
static FRAME_INFO frame__21_111 = {1, {"possible_values"}};
static void cont__21_112(void);
static void cont__21_113(void);
static void cont__21_114(void);
static NODE *func__21_115;
static void entry__21_115(void);
static FRAME_INFO frame__21_115 = {1, {"name"}};
static NODE *func__21_116;
static void entry__21_116(void);
static FRAME_INFO frame__21_116 = {1, {"option"}};
static void cont__21_117(void);
static void cont__21_118(void);
static void cont__21_119(void);
static void cont__21_120(void);
static void cont__21_121(void);
static void cont__21_122(void);
static NODE *func__21_123;
static void entry__21_123(void);
static FRAME_INFO frame__21_123 = {5, {"option", "results", "options", "idx", "kinds"}};
static void cont__21_124(void);
static NODE *func__21_125;
static void entry__21_125(void);
static FRAME_INFO frame__21_125 = {5, {"results", "options", "option", "idx", "kinds"}};
static void cont__21_126(void);
static void cont__21_127(void);
static void cont__21_128(void);
static NODE *func__21_129;
static void entry__21_129(void);
static FRAME_INFO frame__21_129 = {5, {"option", "results", "options", "name", "idx"}};
static void cont__21_130(void);
static NODE *func__21_131;
static void entry__21_131(void);
static FRAME_INFO frame__21_131 = {4, {"results", "options", "name", "idx"}};
static void cont__21_132(void);
static void cont__21_133(void);
static NODE *func__21_134;
static void entry__21_134(void);
static FRAME_INFO frame__21_134 = {5, {"option", "results", "options", "name", "idx"}};
static void cont__21_135(void);
static NODE *func__21_136;
static void entry__21_136(void);
static FRAME_INFO frame__21_136 = {4, {"results", "options", "name", "idx"}};
static void cont__21_137(void);
static void cont__21_138(void);
static NODE *func__21_139;
static void entry__21_139(void);
static FRAME_INFO frame__21_139 = {5, {"option", "results", "parameters", "name", "idx"}};
static void cont__21_140(void);
static NODE *func__21_141;
static void entry__21_141(void);
static FRAME_INFO frame__21_141 = {1, {"option"}};
static void cont__21_142(void);
static void cont__21_143(void);
static NODE *func__21_144;
static void entry__21_144(void);
static FRAME_INFO frame__21_144 = {4, {"results", "parameters", "name", "idx"}};
static void cont__21_145(void);
static void cont__21_146(void);
static NODE *func__21_147;
static void entry__21_147(void);
static FRAME_INFO frame__21_147 = {4, {"results", "parameters", "name", "idx"}};
static void cont__21_148(void);
static void cont__21_149(void);
static void cont__21_150(void);
static void cont__21_151(void);
static void cont__21_152(void);
static void cont__21_153(void);
static NODE *func__21_154;
static void entry__21_154(void);
static FRAME_INFO frame__21_154 = {3, {"arguments", "show_usage", "command_name"}};
static void cont__21_155(void);
static NODE *string__21_156;
static void cont__21_157(void);
static NODE *func__21_158;
static void entry__21_158(void);
static FRAME_INFO frame__21_158 = {1, {"show_usage"}};
static void cont__21_159(void);
static void cont__21_160(void);
static void cont__21_161(void);
static NODE *func__21_162;
static void entry__21_162(void);
static FRAME_INFO frame__21_162 = {1, {"arguments"}};
static void cont__21_163(void);
static NODE *string__21_164;
static void cont__21_165(void);
static void cont__21_166(void);
static NODE *func__21_167;
static void entry__21_167(void);
static FRAME_INFO frame__21_167 = {0, {}};
static void cont__21_168(void);
static void cont__21_169(void);
static void cont__21_170(void);
static NODE *func__21_171;
static void entry__21_171(void);
static FRAME_INFO frame__21_171 = {1, {"arguments"}};
static void cont__21_172(void);
static NODE *string__21_173;
static void cont__21_174(void);
static void cont__21_175(void);
static NODE *func__21_176;
static void entry__21_176(void);
static FRAME_INFO frame__21_176 = {1, {"command_name"}};
static void cont__21_177(void);
static void cont__21_178(void);
static NODE *func__21_179;
static void entry__21_179(void);
static FRAME_INFO frame__21_179 = {7, {"arguments", "kinds", "results", "options", "idx", "fetch_option_value", "option_idx"}};
static NODE *func__21_180;
static void entry__21_180(void);
static FRAME_INFO frame__21_180 = {8, {"break", "arguments", "idx", "fetch_option_value", "kinds", "option_idx", "results", "options"}};
static NODE *func__21_181;
static void entry__21_181(void);
static FRAME_INFO frame__21_181 = {9, {"argument", "arguments", "idx", "break", "fetch_option_value", "kinds", "option_idx", "results", "options"}};
static void cont__21_182(void);
static NODE *func__21_183;
static void entry__21_183(void);
static FRAME_INFO frame__21_183 = {3, {"arguments", "idx", "break"}};
static void cont__21_184(void);
static void cont__21_185(void);
static NODE *func__21_186;
static void entry__21_186(void);
static FRAME_INFO frame__21_186 = {7, {"fetch_option_value", "arguments", "idx", "kinds", "option_idx", "results", "argument"}};
static void cont__21_187(void);
static void cont__21_188(void);
static NODE *func__21_189;
static void entry__21_189(void);
static FRAME_INFO frame__21_189 = {3, {"results", "option_idx", "argument"}};
static void cont__21_190(void);
static NODE *func__21_191;
static void entry__21_191(void);
static FRAME_INFO frame__21_191 = {3, {"results", "option_idx", "argument"}};
static void cont__21_192(void);
static void cont__21_193(void);
static void cont__21_194(void);
static NODE *func__21_195;
static void entry__21_195(void);
static FRAME_INFO frame__21_195 = {8, {"argument", "option_idx", "options", "kinds", "results", "fetch_option_value", "arguments", "idx"}};
static void cont__21_196(void);
static NODE *func__21_197;
static void entry__21_197(void);
static FRAME_INFO frame__21_197 = {8, {"option_idx", "options", "argument", "kinds", "results", "fetch_option_value", "arguments", "idx"}};
static void cont__21_198(void);
static void cont__21_199(void);
static void cont__21_200(void);
static void cont__21_201(void);
static NODE *func__21_202;
static void entry__21_202(void);
static FRAME_INFO frame__21_202 = {1, {"argument"}};
static NODE *string__21_203;
static void cont__21_204(void);
static void cont__21_205(void);
static void cont__21_206(void);
static void cont__21_207(void);
static NODE *func__21_208;
static void entry__21_208(void);
static FRAME_INFO frame__21_208 = {2, {"results", "option_idx"}};
static void cont__21_209(void);
static NODE *func__21_210;
static void entry__21_210(void);
static FRAME_INFO frame__21_210 = {1, {"fetch_option_value"}};
static void cont__21_211(void);
static void cont__21_212(void);
static NODE *func__21_213;
static void entry__21_213(void);
static FRAME_INFO frame__21_213 = {1, {"idx"}};
static void cont__21_214(void);
static void cont__21_215(void);
static void cont__21_216(void);
static void cont__21_217(void);
static NODE *func__21_218;
static void entry__21_218(void);
static FRAME_INFO frame__21_218 = {6, {"break", "templates", "arguments", "too_few_arguments_error", "results", "last_idx"}};
static void cont__21_219(void);
static NODE *func__21_220;
static void entry__21_220(void);
static FRAME_INFO frame__21_220 = {12, {"idx", "template", "arguments", "too_few_arguments_error", "results", "last_idx", "break", "option", "name", "default_value", "conversion", "help"}};
static void cont__21_221(void);
static void cont__21_222(void);
static NODE *func__21_223;
static void entry__21_223(void);
static FRAME_INFO frame__21_223 = {1, {"option"}};
static void cont__21_224(void);
static void cont__21_225(void);
static NODE *func__21_226;
static void entry__21_226(void);
static FRAME_INFO frame__21_226 = {5, {"arguments", "too_few_arguments_error", "results", "idx", "last_idx"}};
static void cont__21_227(void);
static void cont__21_228(void);
static void cont__21_229(void);
static void cont__21_230(void);
static void cont__21_231(void);
static void cont__21_232(void);
static NODE *func__21_233;
static void entry__21_233(void);
static FRAME_INFO frame__21_233 = {1, {"break"}};
static void cont__21_234(void);
static void cont__21_235(void);
static NODE *func__21_236;
static void entry__21_236(void);
static FRAME_INFO frame__21_236 = {10, {"idx", "template", "arguments", "too_few_arguments_error", "results", "option", "name", "default_value", "conversion", "help"}};
static void cont__21_237(void);
static void cont__21_238(void);
static NODE *func__21_239;
static void entry__21_239(void);
static FRAME_INFO frame__21_239 = {1, {"option"}};
static void cont__21_240(void);
static void cont__21_241(void);
static NODE *func__21_242;
static void entry__21_242(void);
static FRAME_INFO frame__21_242 = {4, {"arguments", "too_few_arguments_error", "results", "idx"}};
static void cont__21_243(void);
static void cont__21_244(void);
static void cont__21_245(void);
static void cont__21_246(void);
static void cont__21_247(void);
static NODE *func__21_248;
static void entry__21_248(void);
static FRAME_INFO frame__21_248 = {3, {"arguments", "results", "idx"}};
static void cont__21_249(void);
static void cont__21_250(void);
static NODE *func__21_251;
static void entry__21_251(void);
static FRAME_INFO frame__21_251 = {3, {"arguments", "results", "idx"}};
static void cont__21_252(void);
static void cont__21_253(void);
static NODE *func__21_254;
static void entry__21_254(void);
static FRAME_INFO frame__21_254 = {3, {"results", "idx", "arguments"}};
static void cont__21_255(void);
static NODE *func__21_256;
static void entry__21_256(void);
static FRAME_INFO frame__21_256 = {4, {"arguments", "too_few_arguments_error", "results", "idx"}};
static void cont__21_257(void);
static void cont__21_258(void);
static void cont__21_259(void);
static void cont__21_260(void);
static void cont__21_261(void);
static void cont__21_262(void);
static void cont__21_263(void);
static NODE *func__21_264;
static void entry__21_264(void);
static FRAME_INFO frame__21_264 = {8, {"idx", "result", "default_values", "results", "possible_values", "names", "show_usage", "conversions"}};
static void cont__21_265(void);
static NODE *func__21_266;
static void entry__21_266(void);
static FRAME_INFO frame__21_266 = {2, {"default_values", "idx"}};
static void cont__21_267(void);
static void cont__21_268(void);
static void cont__21_269(void);
static NODE *func__21_270;
static void entry__21_270(void);
static FRAME_INFO frame__21_270 = {3, {"results", "idx", "default_values"}};
static void cont__21_271(void);
static void cont__21_272(void);
static NODE *func__21_273;
static void entry__21_273(void);
static FRAME_INFO frame__21_273 = {10, {"possible_values", "idx", "names", "show_usage", "result", "conversions", "results", "possible_value", "check", "conversion"}};
static NODE *func__21_274_check;
static void entry__21_274_check(void);
static FRAME_INFO frame__21_274_check = {5, {"value", "possible_value", "names", "idx", "show_usage"}};
static void cont__21_275(void);
static NODE *func__21_276;
static void entry__21_276(void);
static FRAME_INFO frame__21_276 = {3, {"names", "idx", "show_usage"}};
static void cont__21_277(void);
static void cont__21_278(void);
static NODE *string__21_279;
static NODE *string__21_280;
static void cont__21_281(void);
static void cont__21_282(void);
static void cont__21_283(void);
static void cont__21_284(void);
static void cont__21_285(void);
static NODE *func__21_286;
static void entry__21_286(void);
static FRAME_INFO frame__21_286 = {2, {"result", "check"}};
static void cont__21_287(void);
static NODE *func__21_288;
static void entry__21_288(void);
static FRAME_INFO frame__21_288 = {2, {"result", "check"}};
static NODE *func__21_289;
static void entry__21_289(void);
static FRAME_INFO frame__21_289 = {2, {"item", "check"}};
static NODE *func__21_290;
static void entry__21_290(void);
static FRAME_INFO frame__21_290 = {2, {"check", "result"}};
static void cont__21_291(void);
static void cont__21_292(void);
static void cont__21_293(void);
static NODE *func__21_294;
static void entry__21_294(void);
static FRAME_INFO frame__21_294 = {4, {"result", "conversion", "results", "idx"}};
static void cont__21_295(void);
static NODE *func__21_296;
static void entry__21_296(void);
static FRAME_INFO frame__21_296 = {5, {"result", "conversion", "results", "idx", "new_result"}};
static NODE *func__21_297;
static void entry__21_297(void);
static FRAME_INFO frame__21_297 = {3, {"item", "new_result", "conversion"}};
static void cont__21_298(void);
static void cont__21_299(void);
static void cont__21_300(void);
static void cont__21_301(void);
static NODE *func__21_302;
static void entry__21_302(void);
static FRAME_INFO frame__21_302 = {4, {"results", "idx", "conversion", "result"}};
static void cont__21_303(void);
static void cont__21_304(void);
static void cont__21_305(void);
static NODE *func__22_1_std__program_commands;
static void entry__22_1_std__program_commands(void);
static FRAME_INFO frame__22_1_std__program_commands = {2, {"commands", "command_ids"}};
static NODE *func__22_2;
static void entry__22_2(void);
static FRAME_INFO frame__22_2 = {4, {"command", "command_ids", "name", "description"}};
static void cont__22_3(void);
static void cont__22_4(void);
static void cont__22_5(void);
static void cont__22_6(void);
static void cont__22_7(void);
static void cont__22_8(void);
static void cont__22_9(void);
static NODE *get__std__program_commands(void) {
  return var.std__program_commands;
}
static NODE *func__23_1_std__command_parameters;
static void entry__23_1_std__command_parameters(void);
static FRAME_INFO frame__23_1_std__command_parameters = {2, {"id", "templates"}};
static void cont__23_2(void);
static NODE *func__23_3;
static void entry__23_3(void);
static FRAME_INFO frame__23_3 = {1, {"templates"}};
static void cont__23_4(void);
static void cont__23_5(void);
static void cont__23_6(void);
static NODE *func__23_7;
static void entry__23_7(void);
static FRAME_INFO frame__23_7 = {3, {"id", "templates", "command"}};
static void cont__23_8(void);
static void cont__23_9(void);
static NODE *func__23_10;
static void entry__23_10(void);
static FRAME_INFO frame__23_10 = {3, {"command", "id", "templates"}};
static NODE *string__23_11;
static void cont__23_12(void);
static NODE *func__23_13;
static void entry__23_13(void);
static FRAME_INFO frame__23_13 = {1, {"id"}};
static void cont__23_14(void);
static void cont__23_15(void);
static NODE *func__23_16;
static void entry__23_16(void);
static FRAME_INFO frame__23_16 = {1, {"id"}};
static void cont__23_17(void);
static void cont__23_18(void);
static void cont__23_19(void);
static void cont__23_20(void);
static void cont__23_21(void);
static void cont__23_22(void);
static NODE *func__23_23;
static void entry__23_23(void);
static FRAME_INFO frame__23_23 = {2, {"id", "templates"}};
static void cont__23_24(void);
static void cont__23_25(void);
static NODE *func__23_26;
static void entry__23_26(void);
static FRAME_INFO frame__23_26 = {3, {"command", "id", "templates"}};
static void cont__23_27(void);
static void cont__23_28(void);
static NODE *func__23_29;
static void entry__23_29(void);
static FRAME_INFO frame__23_29 = {3, {"id", "command", "templates"}};
static void cont__23_30(void);
static void cont__23_31(void);
static NODE *func__23_32;
static void entry__23_32(void);
static FRAME_INFO frame__23_32 = {1, {"templates"}};
static NODE *func__23_33;
static void entry__23_33(void);
static FRAME_INFO frame__23_33 = {1, {"templates"}};
static void cont__23_34(void);
static void cont__23_35(void);
static void cont__23_36(void);
static NODE *get__std__command_parameters(void) {
  return var.std__command_parameters;
}
static NODE *func__24_1_show_commands;
static void entry__24_1_show_commands(void);
static FRAME_INFO frame__24_1_show_commands = {1, {"tab"}};
static void cont__24_2(void);
static NODE *func__24_3;
static void entry__24_3(void);
static FRAME_INFO frame__24_3 = {0, {}};
static void cont__24_4(void);
static void cont__24_5(void);
static void cont__24_6(void);
static NODE *string__24_7;
static void cont__24_8(void);
static NODE *string__24_9;
static void cont__24_10(void);
static void cont__24_11(void);
static NODE *func__24_12;
static void entry__24_12(void);
static FRAME_INFO frame__24_12 = {3, {"idx", "command_name", "tab"}};
static void cont__24_13(void);
static void cont__24_14(void);
static void cont__24_15(void);
static void cont__24_16(void);
static void cont__24_17(void);
static NODE *func__24_18;
static void entry__24_18(void);
static FRAME_INFO frame__24_18 = {1, {"tab"}};
static NODE *string__24_19;
static NODE *string__24_20;
static void cont__24_21(void);
static void cont__24_22(void);
static void cont__24_23(void);
static void cont__24_24(void);
static NODE *func__24_25;
static void entry__24_25(void);
static FRAME_INFO frame__24_25 = {1, {"tab"}};
static NODE *string__24_26;
static NODE *string__24_27;
static void cont__24_28(void);
static void cont__24_29(void);
static void cont__24_30(void);
static NODE *func__25_1_std__program_parameters;
static void entry__25_1_std__program_parameters(void);
static FRAME_INFO frame__25_1_std__program_parameters = {1, {"templates"}};
static void cont__25_2(void);
static NODE *func__25_3;
static void entry__25_3(void);
static FRAME_INFO frame__25_3 = {1, {"templates"}};
static NODE *func__25_4;
static void entry__25_4(void);
static FRAME_INFO frame__25_4 = {0, {}};
static void cont__25_5(void);
static NODE *func__25_6;
static void entry__25_6(void);
static FRAME_INFO frame__25_6 = {0, {}};
static NODE *func__25_7;
static void entry__25_7(void);
static FRAME_INFO frame__25_7 = {0, {}};
static void cont__25_8(void);
static NODE *func__25_9;
static void entry__25_9(void);
static FRAME_INFO frame__25_9 = {0, {}};
static NODE *string__25_10;
static void cont__25_11(void);
static void cont__25_12(void);
static NODE *func__25_13;
static void entry__25_13(void);
static FRAME_INFO frame__25_13 = {0, {}};
static void cont__25_14(void);
static NODE *func__25_15;
static void entry__25_15(void);
static FRAME_INFO frame__25_15 = {0, {}};
static void cont__25_16(void);
static NODE *func__25_17;
static void entry__25_17(void);
static FRAME_INFO frame__25_17 = {0, {}};
static void cont__25_18(void);
static NODE *func__25_19;
static void entry__25_19(void);
static FRAME_INFO frame__25_19 = {0, {}};
static void cont__25_20(void);
static NODE *func__25_21;
static void entry__25_21(void);
static FRAME_INFO frame__25_21 = {0, {}};
static void cont__25_22(void);
static NODE *func__25_23;
static void entry__25_23(void);
static FRAME_INFO frame__25_23 = {0, {}};
static void cont__25_24(void);
static NODE *func__25_25;
static void entry__25_25(void);
static FRAME_INFO frame__25_25 = {0, {}};
static void cont__25_26(void);
static NODE *func__25_27;
static void entry__25_27(void);
static FRAME_INFO frame__25_27 = {0, {}};
static NODE *string__25_28;
static void cont__25_29(void);
static NODE *func__25_30;
static void entry__25_30(void);
static FRAME_INFO frame__25_30 = {0, {}};
static NODE *string__25_31;
static void cont__25_32(void);
static NODE *func__25_33;
static void entry__25_33(void);
static FRAME_INFO frame__25_33 = {0, {}};
static void cont__25_34(void);
static NODE *func__25_35;
static void entry__25_35(void);
static FRAME_INFO frame__25_35 = {0, {}};
static NODE *string__25_36;
static void cont__25_37(void);
static void cont__25_38(void);
static NODE *string__25_39;
static void cont__25_40(void);
static void cont__25_41(void);
static NODE *func__25_42;
static void entry__25_42(void);
static FRAME_INFO frame__25_42 = {0, {}};
static void cont__25_43(void);
static void cont__25_44(void);
static NODE *func__25_45;
static void entry__25_45(void);
static FRAME_INFO frame__25_45 = {0, {}};
static void cont__25_46(void);
static NODE *func__25_47;
static void entry__25_47(void);
static FRAME_INFO frame__25_47 = {1, {"command_name"}};
static void cont__25_48(void);
static void cont__25_49(void);
static void cont__25_50(void);
static void cont__25_51(void);
static NODE *string__25_52;
static void cont__25_53(void);
static void cont__25_54(void);
static NODE *get__std__program_parameters(void) {
  return var.std__program_parameters;
}
void run__basic__parameters(void);

static CONTINUATION_INFO continuation_info[] = {
  {run__basic__parameters, NULL, 219, 219, 1, 33},
  {entry__10_1_std__copyright, NULL, 78, 78, 24, 24},
  {entry__11_1_std__version, NULL, 86, 86, 21, 21},
  {entry__12_5, NULL, 123, 123, 11, 18},
  {cont__12_6, &frame__12_5, 123, 123, 18, 18},
  {entry__12_7, NULL, 125, 125, 11, 33},
  {cont__12_8, &frame__12_7, 126, 126, 11, 32},
  {cont__12_9, &frame__12_7, 126, 126, 32, 32},
  {entry__12_3, NULL, 122, 122, 9, 34},
  {cont__12_4, &frame__12_3, 121, 126, 7, 33},
  {entry__12_2, NULL, 120, 126, 5, 34},
  {entry__12_19, NULL, 136, 136, 15, 36},
  {cont__12_20, &frame__12_19, 137, 137, 28, 43},
  {cont__12_21, &frame__12_19, 137, 137, 15, 43},
  {cont__12_22, &frame__12_19, 137, 137, 43, 43},
  {entry__12_23, NULL, 139, 139, 15, 22},
  {cont__12_24, &frame__12_23, 139, 139, 22, 22},
  {entry__12_15, NULL, 135, 135, 13, 26},
  {cont__12_16, &frame__12_15, 135, 135, 31, 46},
  {cont__12_17, &frame__12_15, 135, 135, 13, 46},
  {cont__12_18, &frame__12_15, 134, 139, 11, 23},
  {entry__12_14, NULL, 133, 139, 9, 24},
  {entry__12_30, NULL, 144, 144, 15, 36},
  {cont__12_31, &frame__12_30, 145, 145, 15, 38},
  {cont__12_32, &frame__12_30, 145, 145, 38, 38},
  {entry__12_33, NULL, 147, 147, 15, 22},
  {cont__12_34, &frame__12_33, 147, 147, 22, 22},
  {entry__12_26, NULL, 143, 143, 13, 26},
  {cont__12_27, &frame__12_26, 143, 143, 31, 46},
  {cont__12_28, &frame__12_26, 143, 143, 13, 46},
  {cont__12_29, &frame__12_26, 142, 147, 11, 23},
  {entry__12_25, NULL, 141, 147, 9, 24},
  {entry__12_11, NULL, 128, 128, 5, 31},
  {cont__12_12, &frame__12_11, 131, 131, 7, 31},
  {cont__12_13, &frame__12_11, 130, 147, 5, 26},
  {cont__12_35, &frame__12_11, 148, 148, 5, 24},
  {cont__12_36, &frame__12_11, 148, 148, 24, 24},
  {entry__12_39, NULL, 150, 150, 55, 64},
  {cont__12_40, &frame__12_39, 150, 150, 48, 65},
  {cont__12_41, &frame__12_39, 150, 150, 35, 66},
  {cont__12_42, &frame__12_39, 150, 150, 71, 71},
  {cont__12_43, &frame__12_39, 150, 150, 29, 72},
  {cont__12_44, &frame__12_39, 150, 150, 11, 75},
  {cont__12_47, &frame__12_39, 150, 150, 5, 75},
  {entry__12_1_std__extract_options, NULL, 118, 126, 3, 35},
  {cont__12_10, &frame__12_1_std__extract_options, 127, 148, 3, 24},
  {cont__12_37, &frame__12_1_std__extract_options, 149, 149, 10, 25},
  {cont__12_38, &frame__12_1_std__extract_options, 149, 150, 3, 75},
  {cont__12_48, &frame__12_1_std__extract_options, 151, 151, 3, 25},
  {entry__13_10, NULL, 191, 191, 15, 36},
  {cont__13_11, &frame__13_10, 192, 192, 28, 43},
  {cont__13_12, &frame__13_10, 192, 192, 15, 43},
  {cont__13_13, &frame__13_10, 192, 192, 43, 43},
  {entry__13_14, NULL, 194, 194, 15, 22},
  {cont__13_15, &frame__13_14, 194, 194, 22, 22},
  {entry__13_6, NULL, 190, 190, 13, 26},
  {cont__13_7, &frame__13_6, 190, 190, 31, 46},
  {cont__13_8, &frame__13_6, 190, 190, 13, 46},
  {cont__13_9, &frame__13_6, 189, 194, 11, 23},
  {entry__13_5, NULL, 188, 194, 9, 24},
  {entry__13_19, NULL, 198, 198, 43, 56},
  {cont__13_20, &frame__13_19, 198, 198, 61, 76},
  {cont__13_21, &frame__13_19, 198, 198, 43, 76},
  {cont__13_22, &frame__13_19, 198, 198, 43, 76},
  {entry__13_24, NULL, 199, 199, 15, 36},
  {cont__13_25, &frame__13_24, 200, 200, 15, 38},
  {cont__13_26, &frame__13_24, 200, 200, 38, 38},
  {entry__13_27, NULL, 202, 202, 15, 22},
  {cont__13_28, &frame__13_27, 202, 202, 22, 22},
  {entry__13_17, NULL, 198, 198, 13, 38},
  {cont__13_18, &frame__13_17, 198, 198, 13, 76},
  {cont__13_23, &frame__13_17, 197, 202, 11, 23},
  {entry__13_16, NULL, 196, 202, 9, 24},
  {entry__13_2, NULL, 183, 183, 5, 31},
  {cont__13_3, &frame__13_2, 186, 186, 7, 31},
  {cont__13_4, &frame__13_2, 185, 202, 5, 26},
  {cont__13_29, &frame__13_2, 203, 203, 5, 24},
  {cont__13_30, &frame__13_2, 203, 203, 24, 24},
  {entry__13_1_std__extract_some_options, NULL, 182, 203, 3, 24},
  {cont__13_31, &frame__13_1_std__extract_some_options, 204, 204, 3, 13},
  {entry__14_2, NULL, 208, 208, 65, 72},
  {cont__14_3, &frame__14_2, 208, 208, 55, 73},
  {cont__14_4, &frame__14_2, 208, 208, 25, 73},
  {cont__14_5, &frame__14_2, 208, 208, 73, 73},
  {entry__14_17, NULL, 213, 213, 37, 56},
  {cont__14_18, &frame__14_17, 213, 213, 27, 56},
  {cont__14_20, &frame__14_17, 213, 213, 20, 56},
  {entry__14_14, NULL, 213, 213, 10, 17},
  {cont__14_15, &frame__14_14, 213, 213, 10, 17},
  {cont__14_16, &frame__14_14, 213, 213, 7, 56},
  {cont__14_21, &frame__14_14, 214, 214, 7, 19},
  {entry__14_8, NULL, 211, 211, 27, 34},
  {cont__14_9, &frame__14_8, 211, 211, 17, 54},
  {cont__14_10, &frame__14_8, 211, 211, 5, 54},
  {cont__14_12, &frame__14_8, 212, 212, 19, 26},
  {cont__14_13, &frame__14_8, 212, 214, 5, 19},
  {entry__14_1_display_table, NULL, 208, 208, 3, 73},
  {cont__14_6, &frame__14_1_display_table, 209, 209, 3, 28},
  {cont__14_7, &frame__14_1_display_table, 210, 214, 3, 20},
  {entry__19_1_show_version, NULL, 222, 222, 10, 53},
  {cont__19_3, &frame__19_1_show_version, 222, 222, 3, 53},
  {entry__20_1_show_copyright, NULL, 224, 224, 18, 41},
  {entry__21_9, NULL, 244, 244, 40, 70},
  {cont__21_10, &frame__21_9, 244, 244, 70, 70},
  {entry__21_6, NULL, 243, 243, 7, 37},
  {cont__21_8, &frame__21_6, 244, 244, 7, 70},
  {cont__21_11, &frame__21_6, 245, 245, 17, 17},
  {cont__21_12, &frame__21_6, 245, 245, 7, 18},
  {cont__21_13, &frame__21_6, 245, 245, 25, 25},
  {entry__21_2_help_message, NULL, 240, 240, 5, 32},
  {cont__21_3, &frame__21_2_help_message, 241, 241, 5, 40},
  {cont__21_4, &frame__21_2_help_message, 242, 242, 8, 32},
  {cont__21_5, &frame__21_2_help_message, 242, 245, 5, 25},
  {cont__21_14, &frame__21_2_help_message, 246, 246, 5, 14},
  {entry__21_19, NULL, 254, 254, 11, 23},
  {cont__21_20, &frame__21_19, 254, 254, 23, 23},
  {entry__21_21, NULL, 256, 256, 11, 23},
  {cont__21_22, &frame__21_21, 256, 256, 23, 23},
  {entry__21_23, NULL, 258, 258, 11, 23},
  {cont__21_24, &frame__21_23, 258, 258, 23, 23},
  {entry__21_16_parameter_name, NULL, 250, 250, 7, 35},
  {cont__21_17, &frame__21_16_parameter_name, 252, 252, 9, 18},
  {cont__21_18, &frame__21_16_parameter_name, 251, 258, 7, 24},
  {cont__21_25, &frame__21_16_parameter_name, 259, 259, 7, 12},
  {entry__21_27, NULL, 261, 261, 36, 60},
  {entry__21_30, NULL, 263, 263, 7, 39},
  {cont__21_31, &frame__21_30, 264, 264, 27, 58},
  {cont__21_32, &frame__21_30, 264, 264, 16, 59},
  {cont__21_33, &frame__21_30, 264, 264, 7, 59},
  {entry__21_40, NULL, 267, 267, 40, 80},
  {entry__21_38, NULL, 267, 267, 10, 37},
  {cont__21_39, &frame__21_38, 267, 267, 7, 80},
  {cont__21_42, &frame__21_38, 268, 268, 7, 42},
  {entry__21_46, NULL, 272, 272, 33, 51},
  {cont__21_47, &frame__21_46, 272, 272, 30, 51},
  {entry__21_48, NULL, 272, 272, 54, 58},
  {entry__21_51, NULL, 274, 274, 18, 46},
  {cont__21_52, &frame__21_51, 274, 274, 7, 46},
  {entry__21_58, NULL, 282, 282, 24, 52},
  {cont__21_59, &frame__21_58, 282, 282, 54, 70},
  {cont__21_60, &frame__21_58, 282, 282, 19, 71},
  {cont__21_61, &frame__21_58, 282, 282, 9, 71},
  {cont__21_62, &frame__21_58, 282, 282, 71, 71},
  {entry__21_57, NULL, 281, 282, 7, 71},
  {cont__21_63, &frame__21_57, 283, 283, 7, 23},
  {entry__21_75, NULL, 296, 296, 17, 36},
  {cont__21_77, &frame__21_75, 296, 296, 36, 36},
  {entry__21_78, NULL, 298, 298, 17, 37},
  {cont__21_80, &frame__21_78, 298, 298, 37, 37},
  {entry__21_71_option_name, NULL, 292, 292, 13, 37},
  {cont__21_73, &frame__21_71_option_name, 294, 294, 15, 24},
  {cont__21_74, &frame__21_71_option_name, 293, 298, 13, 38},
  {cont__21_81, &frame__21_71_option_name, 299, 299, 13, 18},
  {entry__21_70, NULL, 301, 301, 26, 38},
  {cont__21_82, &frame__21_70, 301, 301, 40, 57},
  {cont__21_83, &frame__21_70, 301, 301, 21, 58},
  {cont__21_84, &frame__21_70, 301, 301, 11, 58},
  {cont__21_85, &frame__21_70, 301, 301, 58, 58},
  {entry__21_69, NULL, 290, 301, 9, 58},
  {cont__21_86, &frame__21_69, 302, 302, 9, 25},
  {entry__21_66, NULL, 285, 287, 7, 16},
  {cont__21_68, &frame__21_66, 288, 302, 7, 25},
  {entry__21_15_show_usage, NULL, 261, 261, 8, 33},
  {cont__21_26, &frame__21_15_show_usage, 261, 261, 5, 60},
  {cont__21_28, &frame__21_15_show_usage, 262, 262, 8, 28},
  {cont__21_29, &frame__21_15_show_usage, 262, 264, 5, 59},
  {cont__21_34, &frame__21_15_show_usage, 265, 265, 5, 21},
  {cont__21_36, &frame__21_15_show_usage, 266, 266, 12, 29},
  {cont__21_37, &frame__21_15_show_usage, 266, 268, 5, 42},
  {cont__21_44, &frame__21_15_show_usage, 272, 272, 10, 27},
  {cont__21_45, &frame__21_15_show_usage, 272, 272, 7, 59},
  {cont__21_49, &frame__21_15_show_usage, 269, 272, 5, 59},
  {cont__21_50, &frame__21_15_show_usage, 273, 274, 5, 46},
  {cont__21_53, &frame__21_15_show_usage, 275, 275, 5, 12},
  {cont__21_54, &frame__21_15_show_usage, 276, 278, 5, 17},
  {cont__21_56, &frame__21_15_show_usage, 279, 283, 5, 23},
  {cont__21_64, &frame__21_15_show_usage, 284, 284, 12, 27},
  {cont__21_65, &frame__21_15_show_usage, 284, 302, 5, 26},
  {entry__21_89, NULL, 307, 308, 18, 51},
  {cont__21_92, &frame__21_89, 307, 308, 9, 51},
  {entry__21_93, NULL, 310, 311, 9, 28},
  {entry__21_87_too_few_arguments_error, NULL, 306, 306, 7, 24},
  {cont__21_88, &frame__21_87_too_few_arguments_error, 305, 311, 5, 30},
  {cont__21_95, &frame__21_87_too_few_arguments_error, 312, 312, 5, 14},
  {cont__21_96, &frame__21_87_too_few_arguments_error, 313, 313, 5, 10},
  {entry__21_97_too_many_arguments_error, NULL, 316, 317, 5, 25},
  {cont__21_99, &frame__21_97_too_many_arguments_error, 318, 318, 5, 14},
  {cont__21_100, &frame__21_97_too_many_arguments_error, 319, 319, 5, 10},
  {entry__21_107, NULL, 325, 325, 31, 46},
  {cont__21_108, &frame__21_107, 325, 325, 9, 46},
  {cont__21_109, &frame__21_107, 326, 326, 9, 30},
  {cont__21_110, &frame__21_107, 326, 326, 30, 30},
  {entry__21_111, NULL, 328, 328, 9, 39},
  {cont__21_112, &frame__21_111, 328, 328, 39, 39},
  {entry__21_115, NULL, 329, 329, 37, 43},
  {entry__21_116, NULL, 329, 329, 46, 54},
  {entry__21_125, NULL, 336, 336, 9, 27},
  {cont__21_126, &frame__21_125, 337, 337, 9, 24},
  {cont__21_127, &frame__21_125, 338, 338, 9, 19},
  {cont__21_128, &frame__21_125, 338, 338, 34, 34},
  {entry__21_123, NULL, 335, 335, 10, 27},
  {cont__21_124, &frame__21_123, 335, 338, 7, 34},
  {entry__21_131, NULL, 340, 340, 9, 31},
  {cont__21_132, &frame__21_131, 341, 341, 9, 22},
  {cont__21_133, &frame__21_131, 341, 341, 26, 26},
  {entry__21_129, NULL, 339, 339, 10, 32},
  {cont__21_130, &frame__21_129, 339, 341, 7, 26},
  {entry__21_136, NULL, 343, 343, 9, 32},
  {cont__21_137, &frame__21_136, 344, 344, 9, 22},
  {cont__21_138, &frame__21_136, 344, 344, 26, 26},
  {entry__21_134, NULL, 342, 342, 10, 38},
  {cont__21_135, &frame__21_134, 342, 344, 7, 26},
  {entry__21_141, NULL, 345, 345, 39, 63},
  {cont__21_142, &frame__21_141, 345, 345, 39, 63},
  {entry__21_144, NULL, 346, 346, 9, 32},
  {cont__21_145, &frame__21_144, 347, 347, 9, 25},
  {cont__21_146, &frame__21_144, 347, 347, 29, 29},
  {entry__21_139, NULL, 345, 345, 10, 34},
  {cont__21_140, &frame__21_139, 345, 345, 10, 63},
  {cont__21_143, &frame__21_139, 345, 347, 7, 29},
  {entry__21_147, NULL, 349, 349, 9, 31},
  {cont__21_148, &frame__21_147, 350, 350, 9, 25},
  {cont__21_149, &frame__21_147, 350, 350, 29, 29},
  {entry__21_104, NULL, 322, 322, 5, 63},
  {cont__21_105, &frame__21_104, 324, 324, 7, 32},
  {cont__21_106, &frame__21_104, 323, 328, 5, 40},
  {cont__21_113, &frame__21_104, 329, 329, 20, 34},
  {cont__21_114, &frame__21_104, 329, 329, 17, 55},
  {cont__21_117, &frame__21_104, 329, 329, 5, 55},
  {cont__21_118, &frame__21_104, 330, 330, 5, 22},
  {cont__21_119, &frame__21_104, 331, 331, 5, 38},
  {cont__21_120, &frame__21_104, 332, 332, 5, 32},
  {cont__21_121, &frame__21_104, 333, 333, 5, 28},
  {cont__21_122, &frame__21_104, 334, 350, 5, 30},
  {entry__21_158, NULL, 353, 353, 7, 16},
  {cont__21_159, &frame__21_158, 354, 354, 7, 15},
  {entry__21_162, NULL, 355, 355, 40, 51},
  {cont__21_163, &frame__21_162, 355, 355, 40, 68},
  {cont__21_165, &frame__21_162, 355, 355, 40, 68},
  {entry__21_167, NULL, 356, 356, 7, 20},
  {cont__21_168, &frame__21_167, 357, 357, 7, 15},
  {entry__21_171, NULL, 358, 358, 38, 49},
  {cont__21_172, &frame__21_171, 358, 358, 38, 64},
  {cont__21_174, &frame__21_171, 358, 358, 38, 64},
  {entry__21_176, NULL, 359, 359, 7, 31},
  {cont__21_177, &frame__21_176, 360, 360, 7, 15},
  {entry__21_154, NULL, 352, 352, 8, 19},
  {cont__21_155, &frame__21_154, 352, 352, 8, 31},
  {cont__21_157, &frame__21_154, 352, 354, 5, 15},
  {cont__21_160, &frame__21_154, 355, 355, 8, 35},
  {cont__21_161, &frame__21_154, 355, 355, 8, 68},
  {cont__21_166, &frame__21_154, 355, 357, 5, 15},
  {cont__21_169, &frame__21_154, 358, 358, 8, 33},
  {cont__21_170, &frame__21_154, 358, 358, 8, 64},
  {cont__21_175, &frame__21_154, 358, 360, 5, 15},
  {entry__21_183, NULL, 368, 368, 11, 34},
  {cont__21_184, &frame__21_183, 369, 369, 11, 15},
  {entry__21_189, NULL, 377, 377, 17, 36},
  {cont__21_190, &frame__21_189, 377, 377, 45, 45},
  {entry__21_191, NULL, 379, 379, 23, 41},
  {cont__21_192, &frame__21_191, 379, 379, 17, 50},
  {cont__21_193, &frame__21_191, 379, 379, 22, 41},
  {cont__21_194, &frame__21_191, 379, 379, 50, 50},
  {entry__21_186, NULL, 373, 373, 13, 36},
  {cont__21_187, &frame__21_186, 375, 375, 15, 31},
  {cont__21_188, &frame__21_186, 374, 379, 13, 51},
  {entry__21_202, NULL, 384, 384, 51, 80},
  {cont__21_204, &frame__21_202, 384, 384, 45, 80},
  {entry__21_208, NULL, 387, 387, 21, 40},
  {cont__21_209, &frame__21_208, 387, 387, 45, 45},
  {entry__21_210, NULL, 389, 389, 44, 44},
  {entry__21_197, NULL, 383, 383, 55, 55},
  {cont__21_198, &frame__21_197, 383, 383, 37, 56},
  {cont__21_199, &frame__21_197, 383, 383, 17, 57},
  {cont__21_200, &frame__21_197, 384, 384, 20, 42},
  {cont__21_201, &frame__21_197, 384, 384, 17, 80},
  {cont__21_205, &frame__21_197, 386, 386, 19, 35},
  {cont__21_206, &frame__21_197, 386, 386, 19, 53},
  {cont__21_207, &frame__21_197, 385, 389, 17, 45},
  {cont__21_211, &frame__21_197, 390, 390, 17, 40},
  {cont__21_212, &frame__21_197, 390, 390, 40, 40},
  {entry__21_213, NULL, 392, 392, 17, 24},
  {cont__21_214, &frame__21_213, 392, 392, 24, 24},
  {entry__21_195, NULL, 382, 382, 15, 40},
  {cont__21_196, &frame__21_195, 381, 392, 13, 25},
  {entry__21_181, NULL, 367, 367, 12, 27},
  {cont__21_182, &frame__21_181, 367, 369, 9, 15},
  {cont__21_185, &frame__21_181, 370, 392, 9, 27},
  {entry__21_180, NULL, 366, 392, 7, 28},
  {cont__21_215, &frame__21_180, 392, 392, 28, 28},
  {entry__21_179, NULL, 365, 392, 5, 29},
  {entry__21_223, NULL, 397, 397, 38, 59},
  {cont__21_224, &frame__21_223, 397, 397, 59, 59},
  {entry__21_226, NULL, 401, 401, 14, 31},
  {cont__21_227, &frame__21_226, 401, 401, 11, 55},
  {cont__21_228, &frame__21_226, 402, 402, 11, 38},
  {cont__21_229, &frame__21_226, 402, 402, 26, 38},
  {cont__21_230, &frame__21_226, 403, 403, 11, 25},
  {cont__21_231, &frame__21_226, 403, 403, 25, 25},
  {entry__21_233, NULL, 405, 405, 11, 15},
  {entry__21_220, NULL, 396, 396, 7, 69},
  {cont__21_221, &frame__21_220, 397, 397, 10, 35},
  {cont__21_222, &frame__21_220, 397, 397, 7, 59},
  {cont__21_225, &frame__21_220, 404, 404, 9, 60},
  {cont__21_232, &frame__21_220, 398, 405, 7, 16},
  {entry__21_218, NULL, 395, 395, 38, 38},
  {cont__21_219, &frame__21_218, 395, 405, 5, 17},
  {cont__21_234, &frame__21_218, 405, 405, 17, 17},
  {entry__21_239, NULL, 408, 408, 36, 57},
  {cont__21_240, &frame__21_239, 408, 408, 57, 57},
  {entry__21_242, NULL, 412, 412, 12, 31},
  {cont__21_243, &frame__21_242, 412, 412, 12, 36},
  {cont__21_244, &frame__21_242, 412, 412, 9, 60},
  {cont__21_245, &frame__21_242, 413, 413, 9, 36},
  {cont__21_246, &frame__21_242, 413, 413, 24, 36},
  {cont__21_247, &frame__21_242, 413, 413, 36, 36},
  {entry__21_251, NULL, 415, 415, 38, 65},
  {cont__21_252, &frame__21_251, 415, 415, 53, 65},
  {cont__21_253, &frame__21_251, 415, 415, 65, 65},
  {entry__21_248, NULL, 415, 415, 12, 31},
  {cont__21_249, &frame__21_248, 415, 415, 12, 35},
  {cont__21_250, &frame__21_248, 415, 415, 9, 65},
  {entry__21_254, NULL, 417, 417, 9, 21},
  {cont__21_255, &frame__21_254, 418, 418, 29, 29},
  {entry__21_256, NULL, 420, 420, 12, 31},
  {cont__21_257, &frame__21_256, 420, 420, 12, 36},
  {cont__21_258, &frame__21_256, 420, 420, 9, 60},
  {cont__21_259, &frame__21_256, 421, 421, 9, 21},
  {cont__21_260, &frame__21_256, 422, 422, 29, 29},
  {entry__21_236, NULL, 407, 407, 5, 67},
  {cont__21_237, &frame__21_236, 408, 408, 8, 33},
  {cont__21_238, &frame__21_236, 408, 408, 5, 57},
  {cont__21_241, &frame__21_236, 409, 422, 5, 30},
  {entry__21_266, NULL, 426, 426, 30, 48},
  {cont__21_267, &frame__21_266, 426, 426, 30, 59},
  {cont__21_268, &frame__21_266, 426, 426, 30, 59},
  {entry__21_270, NULL, 427, 427, 9, 41},
  {cont__21_271, &frame__21_270, 427, 427, 9, 21},
  {cont__21_272, &frame__21_270, 427, 427, 41, 41},
  {entry__21_276, NULL, 434, 434, 45, 54},
  {cont__21_277, &frame__21_276, 434, 434, 45, 68},
  {cont__21_278, &frame__21_276, 434, 434, 15, 75},
  {cont__21_281, &frame__21_276, 433, 434, 13, 75},
  {cont__21_282, &frame__21_276, 435, 435, 13, 22},
  {cont__21_283, &frame__21_276, 436, 436, 13, 18},
  {entry__21_274_check, NULL, 432, 432, 18, 38},
  {cont__21_275, &frame__21_274_check, 432, 436, 11, 18},
  {entry__21_289, NULL, 441, 441, 39, 48},
  {entry__21_288, NULL, 441, 441, 15, 48},
  {entry__21_290, NULL, 443, 443, 15, 26},
  {entry__21_286, NULL, 440, 440, 13, 28},
  {cont__21_287, &frame__21_286, 439, 443, 11, 27},
  {entry__21_297, NULL, 449, 449, 56, 71},
  {cont__21_298, &frame__21_297, 449, 449, 39, 71},
  {cont__21_299, &frame__21_297, 449, 449, 71, 71},
  {entry__21_296, NULL, 449, 449, 15, 71},
  {cont__21_300, &frame__21_296, 450, 450, 15, 27},
  {cont__21_301, &frame__21_296, 450, 450, 38, 38},
  {entry__21_302, NULL, 452, 452, 15, 46},
  {cont__21_303, &frame__21_302, 452, 452, 15, 27},
  {cont__21_304, &frame__21_302, 452, 452, 46, 46},
  {entry__21_294, NULL, 447, 447, 13, 28},
  {cont__21_295, &frame__21_294, 446, 452, 11, 47},
  {entry__21_273, NULL, 429, 429, 9, 44},
  {cont__21_284, &frame__21_273, 438, 438, 12, 36},
  {cont__21_285, &frame__21_273, 438, 443, 9, 28},
  {cont__21_291, &frame__21_273, 444, 444, 9, 36},
  {cont__21_292, &frame__21_273, 445, 445, 12, 32},
  {cont__21_293, &frame__21_273, 445, 452, 9, 48},
  {entry__21_264, NULL, 426, 426, 7, 25},
  {cont__21_265, &frame__21_264, 426, 426, 7, 59},
  {cont__21_269, &frame__21_264, 425, 452, 5, 50},
  {entry__21_1_check_arguments, NULL, 236, 236, 50, 50},
  {cont__21_101, &frame__21_1_check_arguments, 236, 236, 3, 51},
  {cont__21_102, &frame__21_1_check_arguments, 237, 237, 3, 26},
  {cont__21_103, &frame__21_1_check_arguments, 321, 350, 3, 31},
  {cont__21_150, &frame__21_1_check_arguments, 351, 351, 6, 25},
  {cont__21_151, &frame__21_1_check_arguments, 351, 351, 6, 30},
  {cont__21_152, &frame__21_1_check_arguments, 351, 351, 6, 30},
  {cont__21_153, &frame__21_1_check_arguments, 351, 360, 3, 16},
  {cont__21_178, &frame__21_1_check_arguments, 361, 392, 3, 30},
  {cont__21_216, &frame__21_1_check_arguments, 393, 393, 3, 15},
  {cont__21_217, &frame__21_1_check_arguments, 394, 405, 3, 18},
  {cont__21_235, &frame__21_1_check_arguments, 406, 422, 3, 31},
  {cont__21_261, &frame__21_1_check_arguments, 423, 423, 10, 27},
  {cont__21_262, &frame__21_1_check_arguments, 423, 423, 3, 52},
  {cont__21_263, &frame__21_1_check_arguments, 424, 452, 3, 51},
  {cont__21_305, &frame__21_1_check_arguments, 453, 453, 3, 13},
  {entry__22_2, NULL, 458, 458, 5, 25},
  {cont__22_3, &frame__22_2, 459, 459, 5, 34},
  {cont__22_4, &frame__22_2, 460, 460, 5, 28},
  {cont__22_5, &frame__22_2, 461, 461, 5, 42},
  {cont__22_6, &frame__22_2, 462, 462, 5, 25},
  {cont__22_7, &frame__22_2, 463, 463, 5, 38},
  {cont__22_8, &frame__22_2, 463, 463, 38, 38},
  {entry__22_1_std__program_commands, NULL, 457, 463, 3, 38},
  {cont__22_9, &frame__22_1_std__program_commands, 464, 464, 3, 17},
  {entry__23_3, NULL, 469, 469, 12, 26},
  {cont__23_4, &frame__23_3, 469, 469, 28, 47},
  {cont__23_5, &frame__23_3, 469, 469, 8, 48},
  {cont__23_6, &frame__23_3, 469, 469, 5, 49},
  {entry__23_16, NULL, 477, 477, 13, 37},
  {cont__23_17, &frame__23_16, 477, 477, 13, 47},
  {cont__23_18, &frame__23_16, 477, 477, 52, 68},
  {cont__23_19, &frame__23_16, 477, 477, 13, 68},
  {cont__23_20, &frame__23_16, 477, 477, 13, 68},
  {entry__23_13, NULL, 476, 476, 13, 45},
  {cont__23_14, &frame__23_13, 476, 476, 13, 50},
  {cont__23_15, &frame__23_13, 477, 477, 13, 68},
  {cont__23_21, &frame__23_13, },
  {entry__23_23, NULL, 479, 479, 29, 45},
  {cont__23_24, &frame__23_23, 479, 479, 47, 60},
  {cont__23_25, &frame__23_23, 479, 479, 13, 70},
  {entry__23_10, NULL, 475, 475, 13, 29},
  {cont__23_12, &frame__23_10, },
  {cont__23_22, &frame__23_10, 473, 479, 9, 71},
  {entry__23_29, NULL, 482, 482, 67, 67},
  {cont__23_30, &frame__23_29, 482, 482, 35, 68},
  {cont__23_31, &frame__23_29, 482, 482, 11, 78},
  {entry__23_26, NULL, 480, 480, 23, 39},
  {cont__23_27, &frame__23_26, 480, 480, 12, 39},
  {cont__23_28, &frame__23_26, 480, 482, 9, 78},
  {entry__23_33, NULL, 483, 483, 24, 38},
  {cont__23_34, &frame__23_33, 483, 483, 40, 59},
  {cont__23_35, &frame__23_33, 483, 483, 20, 60},
  {cont__23_36, &frame__23_33, 483, 483, 17, 61},
  {entry__23_32, NULL, 483, 483, 9, 61},
  {entry__23_7, NULL, 471, 471, 16, 40},
  {cont__23_8, &frame__23_7, 471, 471, 7, 50},
  {cont__23_9, &frame__23_7, 472, 483, 7, 61},
  {entry__23_1_std__command_parameters, NULL, 468, 468, 5, 35},
  {cont__23_2, &frame__23_1_std__command_parameters, 467, 483, 3, 63},
  {entry__24_3, NULL, 487, 487, 51, 51},
  {cont__24_4, &frame__24_3, 487, 487, 18, 52},
  {cont__24_5, &frame__24_3, 487, 487, 5, 52},
  {entry__24_12, NULL, 491, 491, 33, 57},
  {cont__24_13, &frame__24_12, 491, 491, 15, 58},
  {cont__24_14, &frame__24_12, 491, 491, 5, 58},
  {cont__24_15, &frame__24_12, 491, 491, 58, 58},
  {entry__24_18, NULL, 493, 493, 15, 63},
  {cont__24_21, &frame__24_18, 493, 493, 5, 63},
  {cont__24_22, &frame__24_18, 493, 493, 63, 63},
  {entry__24_25, NULL, 495, 495, 15, 58},
  {cont__24_28, &frame__24_25, 495, 495, 5, 58},
  {cont__24_29, &frame__24_25, 495, 495, 58, 58},
  {entry__24_1_show_commands, NULL, 486, 486, 6, 31},
  {cont__24_2, &frame__24_1_show_commands, 486, 487, 3, 52},
  {cont__24_6, &frame__24_1_show_commands, 488, 488, 3, 32},
  {cont__24_8, &frame__24_1_show_commands, 489, 489, 14, 66},
  {cont__24_10, &frame__24_1_show_commands, 489, 489, 3, 67},
  {cont__24_11, &frame__24_1_show_commands, 490, 491, 3, 58},
  {cont__24_16, &frame__24_1_show_commands, 492, 492, 6, 33},
  {cont__24_17, &frame__24_1_show_commands, 492, 493, 3, 63},
  {cont__24_23, &frame__24_1_show_commands, 494, 494, 6, 31},
  {cont__24_24, &frame__24_1_show_commands, 494, 495, 3, 58},
  {cont__24_30, &frame__24_1_show_commands, 496, 496, 3, 19},
  {entry__25_3, NULL, 655, 655, 7, 54},
  {entry__25_6, NULL, 593, 593, 33, 45},
  {entry__25_9, NULL, 596, 597, 13, 35},
  {cont__25_11, &frame__25_9, 598, 598, 13, 25},
  {cont__25_12, &frame__25_9, 599, 599, 13, 18},
  {entry__25_17, NULL, 605, 605, 19, 32},
  {cont__25_18, &frame__25_17, 606, 606, 19, 27},
  {entry__25_15, NULL, 604, 604, 20, 47},
  {cont__25_16, &frame__25_15, 604, 606, 17, 27},
  {entry__25_21, NULL, 611, 611, 21, 33},
  {cont__25_22, &frame__25_21, 612, 612, 21, 29},
  {entry__25_27, NULL, 618, 620, 27, 46},
  {cont__25_29, &frame__25_27, 621, 621, 27, 35},
  {entry__25_25, NULL, 617, 617, 28, 55},
  {cont__25_26, &frame__25_25, 617, 621, 25, 35},
  {entry__25_30, NULL, 623, 628, 25, 77},
  {cont__25_32, &frame__25_30, 629, 629, 25, 33},
  {entry__25_35, NULL, 632, 634, 27, 44},
  {cont__25_37, &frame__25_35, 635, 635, 27, 35},
  {entry__25_33, NULL, 631, 631, 28, 53},
  {cont__25_34, &frame__25_33, 631, 635, 25, 35},
  {entry__25_23, NULL, 615, 615, 23, 47},
  {cont__25_24, &frame__25_23, 614, 635, 21, 37},
  {cont__25_38, &frame__25_23, 636, 637, 21, 43},
  {cont__25_40, &frame__25_23, 638, 638, 21, 33},
  {cont__25_41, &frame__25_23, 639, 639, 21, 26},
  {entry__25_42, NULL, 641, 642, 21, 41},
  {cont__25_43, &frame__25_42, 643, 643, 21, 33},
  {cont__25_44, &frame__25_42, 644, 644, 21, 26},
  {entry__25_19, NULL, 609, 609, 19, 51},
  {cont__25_20, &frame__25_19, 608, 644, 17, 27},
  {entry__25_47, NULL, 647, 647, 66, 66},
  {cont__25_48, &frame__25_47, 647, 647, 19, 67},
  {cont__25_49, &frame__25_47, 648, 648, 19, 43},
  {cont__25_50, &frame__25_47, 649, 649, 19, 27},
  {entry__25_45, NULL, 646, 646, 20, 45},
  {cont__25_46, &frame__25_45, 646, 649, 17, 27},
  {entry__25_13, NULL, 602, 602, 15, 39},
  {cont__25_14, &frame__25_13, 601, 649, 13, 29},
  {cont__25_51, &frame__25_13, 650, 651, 13, 32},
  {cont__25_53, &frame__25_13, 652, 652, 13, 25},
  {cont__25_54, &frame__25_13, 653, 653, 13, 18},
  {entry__25_7, NULL, 595, 595, 11, 41},
  {cont__25_8, &frame__25_7, 594, 653, 9, 19},
  {entry__25_4, NULL, 593, 593, 10, 30},
  {cont__25_5, &frame__25_4, 593, 653, 7, 20},
  {entry__25_1_std__program_parameters, NULL, 592, 592, 5, 24},
  {cont__25_2, &frame__25_1_std__program_parameters, 591, 655, 3, 55}
};

union NODE {
  struct {
    FUNC type;
    ATTRIBUTES *attributes;
  };
  CONTINUATION continuation;
  CLOSURE closure;
};
static NODE *character__47;
static NODE *character__63;
static NODE *character__10;
static NODE *character__44;
static NODE *number__0;
static NODE *number__3;
static NODE *character__32;
static NODE *character__43;
static NODE *number__1;
static NODE *number__2;
static NODE *character__42;

static const char *used_namespaces[] = {
  "std",
  NULL
};

static MODULE_INFO module_info = {
  NULL,
  "basic__parameters",
  continuation_info,
  sizeof(continuation_info)/sizeof(CONTINUATION_INFO),
  (NODE **)&var,
  var_names,
  sizeof(var_names)/sizeof(const char *),
  used_namespaces,
  {DEBUG_FILENAME("basic/parameters.sim")}
};

/******
C O D E
******/

static int already_run = false;

EXPORT void run__basic__parameters(void) {
  if (already_run) {
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  already_run = true;
  allocate_initialized_frame_gc(0, 0);
  // 66: $$program_version undefined
  var._program_version = get__undefined();
  // 69: $$program_copyright undefined
  var._program_copyright = get__undefined();
  // 216: $$command_id undefined
  var._command_id = get__undefined();
  // 217: $$command_id_count 0
  var._command_id_count = number__0;
  // 218: $$command_names empty_list
  var._command_names = get__empty_list();
  // 219: $$command_descriptions empty_list
  var._command_descriptions = get__empty_list();
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__10_1_std__copyright(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // msg: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 78: !program_copyright msg
  var._program_copyright = frame->slots[0] /* msg */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__11_1_std__version(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // no: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 86: !program_version no
  var._program_version = frame->slots[0] /* no */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__12_1_std__extract_options(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(2, 6);
  // slot allocations:
  // options: 0
  // templates: 1
  // results: 2
  // parameters: 3
  frame->slots[2] /* results */ = create_cell();
  frame->slots[3] /* parameters */ = create_cell();
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  frame->slots[0] /* options */ = create_cell_with_contents(arguments->slots[0]);
  frame->slots[1] /* templates */ = from_arguments(1, argument_count-1);
  // 116: $$results empty_list
  ((CELL *)frame->slots[2])->contents /* results */ = get__empty_list();
  // 117: $$parameters empty_list
  ((CELL *)frame->slots[3])->contents /* parameters */ = get__empty_list();
  // 118: ... :
  // 119:   $$idx 1
  // 120:   for_each options: (option)
  // 121:     if
  // 122:       option.is_a_key_value_pair:
  // 123:         inc &idx
  // 124:       :
  // 125:         push &parameters option
  // 126:         delete_at &options idx
  frame->slots[4] /* temp__1 */ = create_closure(entry__12_2, 0);
  // 118: do:
  // 119:   $$idx 1
  // 120:   for_each options: (option)
  // 121:     if
  // 122:       option.is_a_key_value_pair:
  // 123:         inc &idx
  // 124:       :
  // 125:         push &parameters option
  // 126:         delete_at &options idx
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__12_10;
}
static void entry__12_5(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // idx: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* idx */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 123: inc &idx
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* idx */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__12_6;
}
static void cont__12_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* idx */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__12_7(void) {
  allocate_initialized_frame_gc(4, 4);
  // slot allocations:
  // parameters: 0
  // option: 1
  // options: 2
  // idx: 3
  frame->slots[0] = myself->closure.frame->slots[2]; /* parameters */
  frame->slots[1] = myself->closure.frame->slots[0]; /* option */
  frame->slots[2] = myself->closure.frame->slots[3]; /* options */
  frame->slots[3] = myself->closure.frame->slots[1]; /* idx */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 125: push &parameters option
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* parameters */;
  arguments->slots[1] = frame->slots[1] /* option */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__12_8;
}
static void cont__12_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* parameters */ = arguments->slots[0];
  // 126: delete_at &options idx
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* options */;
  arguments->slots[1] = ((CELL *)frame->slots[3])->contents /* idx */;
  result_count = 1;
  myself = get__delete_at();
  func = myself->type;
  frame->cont = cont__12_9;
}
static void cont__12_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* options */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__12_3(void) {
  allocate_initialized_frame_gc(4, 7);
  // slot allocations:
  // option: 0
  // idx: 1
  // parameters: 2
  // options: 3
  frame->slots[1] = myself->closure.frame->slots[2]; /* idx */
  frame->slots[2] = myself->closure.frame->slots[1]; /* parameters */
  frame->slots[3] = myself->closure.frame->slots[0]; /* options */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 122: option.is_a_key_value_pair
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* option */;
  result_count = 1;
  myself = get__is_a_key_value_pair();
  func = myself->type;
  frame->cont = cont__12_4;
}
static void cont__12_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 122: ... :
  // 123:   inc &idx
  frame->slots[5] /* temp__2 */ = create_closure(entry__12_5, 0);
  // 124: :
  // 125:   push &parameters option
  // 126:   delete_at &options idx
  frame->slots[6] /* temp__3 */ = create_closure(entry__12_7, 0);
  // 121: if
  // 122:   option.is_a_key_value_pair:
  // 123:     inc &idx
  // 124:   :
  // 125:     push &parameters option
  // 126:     delete_at &options idx
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
static void entry__12_2(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // options: 0
  // parameters: 1
  // idx: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* options */
  frame->slots[1] = myself->closure.frame->slots[3]; /* parameters */
  frame->slots[2] /* idx */ = create_cell();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 119: $$idx 1
  ((CELL *)frame->slots[2])->contents /* idx */ = number__1;
  // 120: ... : (option)
  // 121:   if
  // 122:     option.is_a_key_value_pair:
  // 123:       inc &idx
  // 124:     :
  // 125:       push &parameters option
  // 126:       delete_at &options idx
  frame->slots[3] /* temp__1 */ = create_closure(entry__12_3, 1);
  // 120: for_each options: (option)
  // 121:   if
  // 122:     option.is_a_key_value_pair:
  // 123:       inc &idx
  // 124:     :
  // 125:       push &parameters option
  // 126:       delete_at &options idx
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* options */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__12_10(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 127: ... : (template)
  // 128:   $$result value_of(template)
  // 129:   $$idx 1
  // 130:   if
  // 131:     result == SOME_PARAMETERS:
  // 132:       !result empty_list
  // 133:       for_each options: (option)
  // 134:         if
  // 135:           key_of(option) == key_of(template):
  // 136:             delete_at &options idx
  // ...
  frame->slots[4] /* temp__1 */ = create_closure(entry__12_11, 1);
  // 127: for_each templates: (template)
  // 128:   $$result value_of(template)
  // 129:   $$idx 1
  // 130:   if
  // 131:     result == SOME_PARAMETERS:
  // 132:       !result empty_list
  // 133:       for_each options: (option)
  // 134:         if
  // 135:           key_of(option) == key_of(template):
  // 136:             delete_at &options idx
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* templates */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__12_37;
}
static void entry__12_11(void) {
  allocate_initialized_frame_gc(3, 8);
  // slot allocations:
  // template: 0
  // options: 1
  // results: 2
  // result: 3
  // idx: 4
  frame->slots[1] = myself->closure.frame->slots[0]; /* options */
  frame->slots[2] = myself->closure.frame->slots[2]; /* results */
  frame->slots[3] /* result */ = create_cell();
  frame->slots[4] /* idx */ = create_cell();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 128: $$result value_of(template)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* template */;
  result_count = 1;
  myself = get__value_of();
  func = myself->type;
  frame->cont = cont__12_12;
}
static void cont__12_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* result */ = arguments->slots[0];
  // 129: $$idx 1
  ((CELL *)frame->slots[4])->contents /* idx */ = number__1;
  // 131: result == SOME_PARAMETERS
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* result */;
  arguments->slots[1] = get__SOME_PARAMETERS();
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__12_13;
}
static void cont__12_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 131: ... :
  // 132:   !result empty_list
  // 133:   for_each options: (option)
  // 134:     if
  // 135:       key_of(option) == key_of(template):
  // 136:         delete_at &options idx
  // 137:         push &result value_of(option)
  // 138:       :
  // 139:         inc &idx
  frame->slots[6] /* temp__2 */ = create_closure(entry__12_14, 0);
  // 140: :
  // 141:   for_each options: (option)
  // 142:     if
  // 143:       key_of(option) == key_of(template):
  // 144:         delete_at &options idx
  // 145:         !result value_of(option)
  // 146:       :
  // 147:         inc &idx
  frame->slots[7] /* temp__3 */ = create_closure(entry__12_25, 0);
  // 130: if
  // 131:   result == SOME_PARAMETERS:
  // 132:     !result empty_list
  // 133:     for_each options: (option)
  // 134:       if
  // 135:         key_of(option) == key_of(template):
  // 136:           delete_at &options idx
  // 137:           push &result value_of(option)
  // 138:         :
  // 139:           inc &idx
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  arguments->slots[2] = frame->slots[7] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__12_35;
}
static void entry__12_30(void) {
  allocate_initialized_frame_gc(4, 4);
  // slot allocations:
  // options: 0
  // idx: 1
  // result: 2
  // option: 3
  frame->slots[0] = myself->closure.frame->slots[2]; /* options */
  frame->slots[1] = myself->closure.frame->slots[3]; /* idx */
  frame->slots[2] = myself->closure.frame->slots[4]; /* result */
  frame->slots[3] = myself->closure.frame->slots[0]; /* option */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 144: delete_at &options idx
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* options */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* idx */;
  result_count = 1;
  myself = get__delete_at();
  func = myself->type;
  frame->cont = cont__12_31;
}
static void cont__12_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* options */ = arguments->slots[0];
  // 145: !result value_of(option)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* option */;
  result_count = 1;
  myself = get__value_of();
  func = myself->type;
  frame->cont = cont__12_32;
}
static void cont__12_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* result */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__12_33(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // idx: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* idx */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 147: inc &idx
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* idx */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__12_34;
}
static void cont__12_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* idx */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__12_26(void) {
  allocate_initialized_frame_gc(5, 10);
  // slot allocations:
  // option: 0
  // template: 1
  // options: 2
  // idx: 3
  // result: 4
  frame->slots[1] = myself->closure.frame->slots[1]; /* template */
  frame->slots[2] = myself->closure.frame->slots[0]; /* options */
  frame->slots[3] = myself->closure.frame->slots[2]; /* idx */
  frame->slots[4] = myself->closure.frame->slots[3]; /* result */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 143: key_of(option)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* option */;
  result_count = 1;
  myself = get__key_of();
  func = myself->type;
  frame->cont = cont__12_27;
}
static void cont__12_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 143: ... key_of(template)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* template */;
  result_count = 1;
  myself = get__key_of();
  func = myself->type;
  frame->cont = cont__12_28;
}
static void cont__12_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__3 */ = arguments->slots[0];
  // 143: key_of(option) == key_of(template)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__12_29;
}
static void cont__12_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 143: ... :
  // 144:   delete_at &options idx
  // 145:   !result value_of(option)
  frame->slots[8] /* temp__4 */ = create_closure(entry__12_30, 0);
  // 146: :
  // 147:   inc &idx
  frame->slots[9] /* temp__5 */ = create_closure(entry__12_33, 0);
  // 142: if
  // 143:   key_of(option) == key_of(template):
  // 144:     delete_at &options idx
  // 145:     !result value_of(option)
  // 146:   :
  // 147:     inc &idx
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__4 */;
  arguments->slots[2] = frame->slots[9] /* temp__5 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__12_19(void) {
  allocate_initialized_frame_gc(4, 5);
  // slot allocations:
  // options: 0
  // idx: 1
  // result: 2
  // option: 3
  frame->slots[0] = myself->closure.frame->slots[2]; /* options */
  frame->slots[1] = myself->closure.frame->slots[3]; /* idx */
  frame->slots[2] = myself->closure.frame->slots[4]; /* result */
  frame->slots[3] = myself->closure.frame->slots[0]; /* option */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 136: delete_at &options idx
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* options */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* idx */;
  result_count = 1;
  myself = get__delete_at();
  func = myself->type;
  frame->cont = cont__12_20;
}
static void cont__12_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* options */ = arguments->slots[0];
  // 137: ... value_of(option)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* option */;
  result_count = 1;
  myself = get__value_of();
  func = myself->type;
  frame->cont = cont__12_21;
}
static void cont__12_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 137: push &result value_of(option)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* result */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__12_22;
}
static void cont__12_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* result */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__12_23(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // idx: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* idx */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 139: inc &idx
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* idx */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__12_24;
}
static void cont__12_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* idx */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__12_15(void) {
  allocate_initialized_frame_gc(5, 10);
  // slot allocations:
  // option: 0
  // template: 1
  // options: 2
  // idx: 3
  // result: 4
  frame->slots[1] = myself->closure.frame->slots[2]; /* template */
  frame->slots[2] = myself->closure.frame->slots[1]; /* options */
  frame->slots[3] = myself->closure.frame->slots[3]; /* idx */
  frame->slots[4] = myself->closure.frame->slots[0]; /* result */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 135: key_of(option)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* option */;
  result_count = 1;
  myself = get__key_of();
  func = myself->type;
  frame->cont = cont__12_16;
}
static void cont__12_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 135: ... key_of(template)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* template */;
  result_count = 1;
  myself = get__key_of();
  func = myself->type;
  frame->cont = cont__12_17;
}
static void cont__12_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__3 */ = arguments->slots[0];
  // 135: key_of(option) == key_of(template)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__12_18;
}
static void cont__12_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 135: ... :
  // 136:   delete_at &options idx
  // 137:   push &result value_of(option)
  frame->slots[8] /* temp__4 */ = create_closure(entry__12_19, 0);
  // 138: :
  // 139:   inc &idx
  frame->slots[9] /* temp__5 */ = create_closure(entry__12_23, 0);
  // 134: if
  // 135:   key_of(option) == key_of(template):
  // 136:     delete_at &options idx
  // 137:     push &result value_of(option)
  // 138:   :
  // 139:     inc &idx
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__4 */;
  arguments->slots[2] = frame->slots[9] /* temp__5 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__12_14(void) {
  allocate_initialized_frame_gc(4, 5);
  // slot allocations:
  // result: 0
  // options: 1
  // template: 2
  // idx: 3
  frame->slots[0] = myself->closure.frame->slots[3]; /* result */
  frame->slots[1] = myself->closure.frame->slots[1]; /* options */
  frame->slots[2] = myself->closure.frame->slots[0]; /* template */
  frame->slots[3] = myself->closure.frame->slots[4]; /* idx */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 132: !result empty_list
  ((CELL *)frame->slots[0])->contents /* result */ = get__empty_list();
  // 133: ... : (option)
  // 134:   if
  // 135:     key_of(option) == key_of(template):
  // 136:       delete_at &options idx
  // 137:       push &result value_of(option)
  // 138:     :
  // 139:       inc &idx
  frame->slots[4] /* temp__1 */ = create_closure(entry__12_15, 1);
  // 133: for_each options: (option)
  // 134:   if
  // 135:     key_of(option) == key_of(template):
  // 136:       delete_at &options idx
  // 137:       push &result value_of(option)
  // 138:     :
  // 139:       inc &idx
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* options */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__12_25(void) {
  allocate_initialized_frame_gc(4, 5);
  // slot allocations:
  // options: 0
  // template: 1
  // idx: 2
  // result: 3
  frame->slots[0] = myself->closure.frame->slots[1]; /* options */
  frame->slots[1] = myself->closure.frame->slots[0]; /* template */
  frame->slots[2] = myself->closure.frame->slots[4]; /* idx */
  frame->slots[3] = myself->closure.frame->slots[3]; /* result */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 141: ... : (option)
  // 142:   if
  // 143:     key_of(option) == key_of(template):
  // 144:       delete_at &options idx
  // 145:       !result value_of(option)
  // 146:     :
  // 147:       inc &idx
  frame->slots[4] /* temp__1 */ = create_closure(entry__12_26, 1);
  // 141: for_each options: (option)
  // 142:   if
  // 143:     key_of(option) == key_of(template):
  // 144:       delete_at &options idx
  // 145:       !result value_of(option)
  // 146:     :
  // 147:       inc &idx
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* options */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__12_35(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 148: push &results result
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* results */;
  arguments->slots[1] = ((CELL *)frame->slots[3])->contents /* result */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__12_36;
}
static void cont__12_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* results */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__12_37(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 149: ... options.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* options */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__12_38;
}
static void cont__12_38(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 149: ... :
  // 150:   Error "Invalid option @(range(debug_string(key_of(options(1))) 1 -2))!"
  frame->slots[5] /* temp__2 */ = create_closure(entry__12_39, 0);
  // 149: unless options.is_empty:
  // 150:   Error "Invalid option @(range(debug_string(key_of(options(1))) 1 -2))!"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__12_48;
}
static void entry__12_39(void) {
  allocate_initialized_frame_gc(1, 7);
  // slot allocations:
  // options: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* options */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 150: ... options(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* options */;
  func = myself->type;
  frame->cont = cont__12_40;
}
static void cont__12_40(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__5 */ = arguments->slots[0];
  // 150: ... key_of(options(1))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__5 */;
  result_count = 1;
  myself = get__key_of();
  func = myself->type;
  frame->cont = cont__12_41;
}
static void cont__12_41(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__4 */ = arguments->slots[0];
  // 150: ... debug_string(key_of(options(1)))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__4 */;
  result_count = 1;
  myself = get__debug_string();
  func = myself->type;
  frame->cont = cont__12_42;
}
static void cont__12_42(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 150: ... 2
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__12_43;
}
static void cont__12_43(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__6 */ = arguments->slots[0];
  // 150: ... range(debug_string(key_of(options(1))) 1 -2)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[6] /* temp__6 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__12_44;
}
static void cont__12_44(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 150: ... "Invalid option @(range(debug_string(key_of(options(1))) 1 -2))!"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__12_45;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  arguments->slots[2] = string__12_46;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__12_47;
}
static void cont__12_47(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 150: Error "Invalid option @(range(debug_string(key_of(options(1))) 1 -2))!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__12_48(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 151: -> results* parameters*
  argument_count = 0;
  arguments = node_p;
  unfold(((CELL *)frame->slots[2])->contents /* results */);
  unfold(((CELL *)frame->slots[3])->contents /* parameters */);
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__13_1_std__extract_some_options(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // options: 0
  // templates: 1
  // results: 2
  frame->slots[2] /* results */ = create_cell();
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  frame->slots[0] /* options */ = create_cell_with_contents(arguments->slots[0]);
  frame->slots[1] /* templates */ = from_arguments(1, argument_count-1);
  // 181: $$results empty_list
  ((CELL *)frame->slots[2])->contents /* results */ = get__empty_list();
  // 182: ... : (template)
  // 183:   $$result value_of(template)
  // 184:   $$idx 1
  // 185:   if
  // 186:     result == SOME_PARAMETERS:
  // 187:       !result empty_list
  // 188:       for_each options: (option)
  // 189:         if
  // 190:           key_of(option) == key_of(template):
  // 191:             delete_at &options idx
  // ...
  frame->slots[3] /* temp__1 */ = create_closure(entry__13_2, 1);
  // 182: for_each templates: (template)
  // 183:   $$result value_of(template)
  // 184:   $$idx 1
  // 185:   if
  // 186:     result == SOME_PARAMETERS:
  // 187:       !result empty_list
  // 188:       for_each options: (option)
  // 189:         if
  // 190:           key_of(option) == key_of(template):
  // 191:             delete_at &options idx
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* templates */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__13_31;
}
static void entry__13_2(void) {
  allocate_initialized_frame_gc(3, 8);
  // slot allocations:
  // template: 0
  // options: 1
  // results: 2
  // result: 3
  // idx: 4
  frame->slots[1] = myself->closure.frame->slots[0]; /* options */
  frame->slots[2] = myself->closure.frame->slots[2]; /* results */
  frame->slots[3] /* result */ = create_cell();
  frame->slots[4] /* idx */ = create_cell();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 183: $$result value_of(template)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* template */;
  result_count = 1;
  myself = get__value_of();
  func = myself->type;
  frame->cont = cont__13_3;
}
static void cont__13_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* result */ = arguments->slots[0];
  // 184: $$idx 1
  ((CELL *)frame->slots[4])->contents /* idx */ = number__1;
  // 186: result == SOME_PARAMETERS
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* result */;
  arguments->slots[1] = get__SOME_PARAMETERS();
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__13_4;
}
static void cont__13_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 186: ... :
  // 187:   !result empty_list
  // 188:   for_each options: (option)
  // 189:     if
  // 190:       key_of(option) == key_of(template):
  // 191:         delete_at &options idx
  // 192:         push &result value_of(option)
  // 193:       :
  // 194:         inc &idx
  frame->slots[6] /* temp__2 */ = create_closure(entry__13_5, 0);
  // 195: :
  // 196:   for_each options: (option)
  // 197:     if
  // 198:       option.is_a_key_value_pair && key_of(option) == key_of(template):
  // 199:         delete_at &options idx
  // 200:         !result value_of(option)
  // 201:       :
  // 202:         inc &idx
  frame->slots[7] /* temp__3 */ = create_closure(entry__13_16, 0);
  // 185: if
  // 186:   result == SOME_PARAMETERS:
  // 187:     !result empty_list
  // 188:     for_each options: (option)
  // 189:       if
  // 190:         key_of(option) == key_of(template):
  // 191:           delete_at &options idx
  // 192:           push &result value_of(option)
  // 193:         :
  // 194:           inc &idx
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  arguments->slots[2] = frame->slots[7] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__13_29;
}
static void entry__13_24(void) {
  allocate_initialized_frame_gc(4, 4);
  // slot allocations:
  // options: 0
  // idx: 1
  // result: 2
  // option: 3
  frame->slots[0] = myself->closure.frame->slots[2]; /* options */
  frame->slots[1] = myself->closure.frame->slots[3]; /* idx */
  frame->slots[2] = myself->closure.frame->slots[4]; /* result */
  frame->slots[3] = myself->closure.frame->slots[0]; /* option */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 199: delete_at &options idx
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* options */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* idx */;
  result_count = 1;
  myself = get__delete_at();
  func = myself->type;
  frame->cont = cont__13_25;
}
static void cont__13_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* options */ = arguments->slots[0];
  // 200: !result value_of(option)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* option */;
  result_count = 1;
  myself = get__value_of();
  func = myself->type;
  frame->cont = cont__13_26;
}
static void cont__13_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* result */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__13_27(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // idx: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* idx */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 202: inc &idx
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* idx */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__13_28;
}
static void cont__13_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* idx */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__13_17(void) {
  allocate_initialized_frame_gc(5, 10);
  // slot allocations:
  // option: 0
  // template: 1
  // options: 2
  // idx: 3
  // result: 4
  frame->slots[1] = myself->closure.frame->slots[1]; /* template */
  frame->slots[2] = myself->closure.frame->slots[0]; /* options */
  frame->slots[3] = myself->closure.frame->slots[2]; /* idx */
  frame->slots[4] = myself->closure.frame->slots[3]; /* result */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 198: option.is_a_key_value_pair
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* option */;
  result_count = 1;
  myself = get__is_a_key_value_pair();
  func = myself->type;
  frame->cont = cont__13_18;
}
static void cont__13_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 198: ... key_of(option) == key_of(template)
  frame->slots[7] /* temp__3 */ = create_closure(entry__13_19, 0);
  // 198: option.is_a_key_value_pair && key_of(option) == key_of(template)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__13_23;
}
static void entry__13_19(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // option: 0
  // template: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* option */
  frame->slots[1] = myself->closure.frame->slots[1]; /* template */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 198: ... key_of(option)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* option */;
  result_count = 1;
  myself = get__key_of();
  func = myself->type;
  frame->cont = cont__13_20;
}
static void cont__13_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 198: ... key_of(template)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* template */;
  result_count = 1;
  myself = get__key_of();
  func = myself->type;
  frame->cont = cont__13_21;
}
static void cont__13_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 198: ... key_of(option) == key_of(template)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__13_22;
}
static void cont__13_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 198: ... key_of(option) == key_of(template)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__13_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 198: ... :
  // 199:   delete_at &options idx
  // 200:   !result value_of(option)
  frame->slots[8] /* temp__4 */ = create_closure(entry__13_24, 0);
  // 201: :
  // 202:   inc &idx
  frame->slots[9] /* temp__5 */ = create_closure(entry__13_27, 0);
  // 197: if
  // 198:   option.is_a_key_value_pair && key_of(option) == key_of(template):
  // 199:     delete_at &options idx
  // 200:     !result value_of(option)
  // 201:   :
  // 202:     inc &idx
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__4 */;
  arguments->slots[2] = frame->slots[9] /* temp__5 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__13_10(void) {
  allocate_initialized_frame_gc(4, 5);
  // slot allocations:
  // options: 0
  // idx: 1
  // result: 2
  // option: 3
  frame->slots[0] = myself->closure.frame->slots[2]; /* options */
  frame->slots[1] = myself->closure.frame->slots[3]; /* idx */
  frame->slots[2] = myself->closure.frame->slots[4]; /* result */
  frame->slots[3] = myself->closure.frame->slots[0]; /* option */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 191: delete_at &options idx
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* options */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* idx */;
  result_count = 1;
  myself = get__delete_at();
  func = myself->type;
  frame->cont = cont__13_11;
}
static void cont__13_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* options */ = arguments->slots[0];
  // 192: ... value_of(option)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* option */;
  result_count = 1;
  myself = get__value_of();
  func = myself->type;
  frame->cont = cont__13_12;
}
static void cont__13_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 192: push &result value_of(option)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* result */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__13_13;
}
static void cont__13_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* result */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__13_14(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // idx: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* idx */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 194: inc &idx
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* idx */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__13_15;
}
static void cont__13_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* idx */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__13_6(void) {
  allocate_initialized_frame_gc(5, 10);
  // slot allocations:
  // option: 0
  // template: 1
  // options: 2
  // idx: 3
  // result: 4
  frame->slots[1] = myself->closure.frame->slots[2]; /* template */
  frame->slots[2] = myself->closure.frame->slots[1]; /* options */
  frame->slots[3] = myself->closure.frame->slots[3]; /* idx */
  frame->slots[4] = myself->closure.frame->slots[0]; /* result */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 190: key_of(option)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* option */;
  result_count = 1;
  myself = get__key_of();
  func = myself->type;
  frame->cont = cont__13_7;
}
static void cont__13_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 190: ... key_of(template)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* template */;
  result_count = 1;
  myself = get__key_of();
  func = myself->type;
  frame->cont = cont__13_8;
}
static void cont__13_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__3 */ = arguments->slots[0];
  // 190: key_of(option) == key_of(template)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__13_9;
}
static void cont__13_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 190: ... :
  // 191:   delete_at &options idx
  // 192:   push &result value_of(option)
  frame->slots[8] /* temp__4 */ = create_closure(entry__13_10, 0);
  // 193: :
  // 194:   inc &idx
  frame->slots[9] /* temp__5 */ = create_closure(entry__13_14, 0);
  // 189: if
  // 190:   key_of(option) == key_of(template):
  // 191:     delete_at &options idx
  // 192:     push &result value_of(option)
  // 193:   :
  // 194:     inc &idx
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__4 */;
  arguments->slots[2] = frame->slots[9] /* temp__5 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__13_5(void) {
  allocate_initialized_frame_gc(4, 5);
  // slot allocations:
  // result: 0
  // options: 1
  // template: 2
  // idx: 3
  frame->slots[0] = myself->closure.frame->slots[3]; /* result */
  frame->slots[1] = myself->closure.frame->slots[1]; /* options */
  frame->slots[2] = myself->closure.frame->slots[0]; /* template */
  frame->slots[3] = myself->closure.frame->slots[4]; /* idx */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 187: !result empty_list
  ((CELL *)frame->slots[0])->contents /* result */ = get__empty_list();
  // 188: ... : (option)
  // 189:   if
  // 190:     key_of(option) == key_of(template):
  // 191:       delete_at &options idx
  // 192:       push &result value_of(option)
  // 193:     :
  // 194:       inc &idx
  frame->slots[4] /* temp__1 */ = create_closure(entry__13_6, 1);
  // 188: for_each options: (option)
  // 189:   if
  // 190:     key_of(option) == key_of(template):
  // 191:       delete_at &options idx
  // 192:       push &result value_of(option)
  // 193:     :
  // 194:       inc &idx
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* options */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__13_16(void) {
  allocate_initialized_frame_gc(4, 5);
  // slot allocations:
  // options: 0
  // template: 1
  // idx: 2
  // result: 3
  frame->slots[0] = myself->closure.frame->slots[1]; /* options */
  frame->slots[1] = myself->closure.frame->slots[0]; /* template */
  frame->slots[2] = myself->closure.frame->slots[4]; /* idx */
  frame->slots[3] = myself->closure.frame->slots[3]; /* result */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 196: ... : (option)
  // 197:   if
  // 198:     option.is_a_key_value_pair && key_of(option) == key_of(template):
  // 199:       delete_at &options idx
  // 200:       !result value_of(option)
  // 201:     :
  // 202:       inc &idx
  frame->slots[4] /* temp__1 */ = create_closure(entry__13_17, 1);
  // 196: for_each options: (option)
  // 197:   if
  // 198:     option.is_a_key_value_pair && key_of(option) == key_of(template):
  // 199:       delete_at &options idx
  // 200:       !result value_of(option)
  // 201:     :
  // 202:       inc &idx
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* options */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__13_29(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 203: push &results result
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* results */;
  arguments->slots[1] = ((CELL *)frame->slots[3])->contents /* result */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__13_30;
}
static void cont__13_30(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* results */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__13_31(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 204: -> results*
  argument_count = 0;
  arguments = node_p;
  arguments->slots[argument_count++] = ((CELL *)frame->slots[0])->contents /* options */;
  unfold(((CELL *)frame->slots[2])->contents /* results */);
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__14_14(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // idx: 0
  // line: 1
  // first_column_width: 2
  frame->slots[2] = myself->closure.frame->slots[1]; /* first_column_width */
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 213: ... idx != 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* idx */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__14_15;
}
static void cont__14_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 213: ... idx != 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__14_16;
}
static void cont__14_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 213: ... : ewrite " " .dup. 2+first_column_width
  frame->slots[5] /* temp__3 */ = create_closure(entry__14_17, 0);
  // 213: if idx != 1: ewrite " " .dup. 2+first_column_width
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__14_21;
}
static void entry__14_17(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // first_column_width: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* first_column_width */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 213: ... 2+first_column_width
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__2;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* first_column_width */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__14_18;
}
static void cont__14_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 213: ... " " .dup. 2+first_column_width
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__14_19;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__dup();
  func = myself->type;
  frame->cont = cont__14_20;
}
static void cont__14_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 213: ... ewrite " " .dup. 2+first_column_width
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__ewrite();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__14_21(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 214: ewriteln line
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* line */;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__14_8(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // entry: 0
  // first_column_width: 1
  frame->slots[1] = myself->closure.frame->slots[1]; /* first_column_width */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 211: ... entry(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* entry */;
  func = myself->type;
  frame->cont = cont__14_9;
}
static void cont__14_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 211: ... pad_right(entry(1) first_column_width)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* first_column_width */;
  result_count = 1;
  myself = get__pad_right();
  func = myself->type;
  frame->cont = cont__14_10;
}
static void cont__14_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 211: ewrite "  " pad_right(entry(1) first_column_width)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__14_11;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__ewrite();
  func = myself->type;
  frame->cont = cont__14_12;
}
static void cont__14_12(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 212: ... entry(2)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = frame->slots[0] /* entry */;
  func = myself->type;
  frame->cont = cont__14_13;
}
static void cont__14_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 212: ... : (idx line)
  // 213:   if idx != 1: ewrite " " .dup. 2+first_column_width
  // 214:   ewriteln line
  frame->slots[3] /* temp__2 */ = create_closure(entry__14_14, 2);
  // 212: for_each_line entry(2): (idx line)
  // 213:   if idx != 1: ewrite " " .dup. 2+first_column_width
  // 214:   ewriteln line
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__for_each_line();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__14_1_display_table(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // tab: 0
  // first_column_width: 1
  frame->slots[1] /* first_column_width */ = create_cell();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 207: $$first_column_width 0
  ((CELL *)frame->slots[1])->contents /* first_column_width */ = number__0;
  // 208: ... : (entry) extend_to &first_column_width length_of(entry(1))
  frame->slots[2] /* temp__1 */ = create_closure(entry__14_2, 1);
  // 208: for_each tab: (entry) extend_to &first_column_width length_of(entry(1))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* tab */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__14_6;
}
static void entry__14_2(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // entry: 0
  // first_column_width: 1
  frame->slots[1] = myself->closure.frame->slots[1]; /* first_column_width */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 208: ... entry(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* entry */;
  func = myself->type;
  frame->cont = cont__14_3;
}
static void cont__14_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 208: ... length_of(entry(1))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__14_4;
}
static void cont__14_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 208: ... extend_to &first_column_width length_of(entry(1))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* first_column_width */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__extend_to();
  func = myself->type;
  frame->cont = cont__14_5;
}
static void cont__14_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* first_column_width */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__14_6(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 209: plus &first_column_width 2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* first_column_width */;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__plus();
  func = myself->type;
  frame->cont = cont__14_7;
}
static void cont__14_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* first_column_width */ = arguments->slots[0];
  // 210: ... : (entry)
  // 211:   ewrite "  " pad_right(entry(1) first_column_width)
  // 212:   for_each_line entry(2): (idx line)
  // 213:     if idx != 1: ewrite " " .dup. 2+first_column_width
  // 214:     ewriteln line
  frame->slots[2] /* temp__1 */ = create_closure(entry__14_8, 1);
  // 210: for_each tab: (entry)
  // 211:   ewrite "  " pad_right(entry(1) first_column_width)
  // 212:   for_each_line entry(2): (idx line)
  // 213:     if idx != 1: ewrite " " .dup. 2+first_column_width
  // 214:     ewriteln line
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* tab */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__19_1_show_version(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // command_name: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 222: ... "@(command_name) @(program_version)@nl;@nl;"
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* command_name */;
  arguments->slots[1] = string__14_19;
  arguments->slots[2] = var._program_version;
  arguments->slots[3] = string__19_2;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__19_3;
}
static void cont__19_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 222: ewrite "@(command_name) @(program_version)@nl;@nl;"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__ewrite();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__20_1_show_copyright(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 224: ... ewrite program_copyright
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._program_copyright;
  result_count = frame->caller_result_count;
  myself = get__ewrite();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__21_1_check_arguments(void) {
  allocate_initialized_frame_gc(3, 22);
  // slot allocations:
  // command: 0
  // arguments: 1
  // templates: 2
  // results: 3
  // options: 4
  // parameters: 5
  // names: 6
  // kinds: 7
  // possible_values: 8
  // default_values: 9
  // conversions: 10
  // help_messages: 11
  // command_name: 12
  // help_message: 13
  // show_usage: 14
  // too_few_arguments_error: 15
  // too_many_arguments_error: 16
  // last_idx: 17
  frame->slots[13] /* help_message */ = create_future();
  frame->slots[14] /* show_usage */ = create_future();
  frame->slots[15] /* too_few_arguments_error */ = create_future();
  frame->slots[16] /* too_many_arguments_error */ = create_future();
  frame->slots[3] /* results */ = create_cell();
  frame->slots[4] /* options */ = create_cell();
  frame->slots[5] /* parameters */ = create_cell();
  frame->slots[6] /* names */ = create_cell();
  frame->slots[7] /* kinds */ = create_cell();
  frame->slots[8] /* possible_values */ = create_cell();
  frame->slots[9] /* default_values */ = create_cell();
  frame->slots[10] /* conversions */ = create_cell();
  frame->slots[11] /* help_messages */ = create_cell();
  frame->slots[12] /* command_name */ = create_future();
  frame->slots[17] /* last_idx */ = create_cell();
  if (argument_count < 2) {
    too_few_arguments_error();
    return;
  }
  if (argument_count > 3) {
    too_many_arguments_error();
    return;
  }
  frame->slots[2] /* templates */ = arguments->slots[argument_count-1];
  frame->slots[1] /* arguments */ = create_cell_with_contents(arguments->slots[argument_count-2]);
  switch(argument_count) {
    default: frame->slots[0] /* command */ = arguments->slots[0];
    case 2:;
  }
  switch(argument_count) {
    case 2: frame->slots[0] /* command */ = undefined;
  }
  // 239: ... : (idx)
  // 240:   $$message help_messages(idx)
  // 241:   $possible_value possible_values(idx)
  // 242:   if possible_value.is_defined:
  // 243:     append &message "valid values:"
  // 244:     for_each possible_value: (value) write_to &message ' ' value ','
  // 245:     !message(-1) '@nl;'
  // 246:   -> message
  frame->slots[18] /* temp__1 */ = create_closure(entry__21_2_help_message, 1);
  // 239: $help_message: (idx)
  // 240:   $$message help_messages(idx)
  // 241:   $possible_value possible_values(idx)
  // 242:   if possible_value.is_defined:
  // 243:     append &message "valid values:"
  // 244:     for_each possible_value: (value) write_to &message ' ' value ','
  // 245:     !message(-1) '@nl;'
  // 246:   -> message
  initialize_future(frame->slots[13] /* help_message */, frame->slots[18] /* temp__1 */);
  // 248: ... :
  // 249:   $parameter_name: (parameter idx)
  // 250:     $$buf parameter.to_upper_case
  // 251:     case
  // 252:       kinds(idx)
  // 253:       OPTIONAL_PARAMETER:
  // 254:         push &buf '?'
  // 255:       SOME_PARAMETERS:
  // 256:         push &buf '*'
  // 257:       MANY_PARAMETERS:
  // ...
  frame->slots[18] /* temp__1 */ = create_closure(entry__21_15_show_usage, 0);
  // 248: $show_usage:
  // 249:   $parameter_name: (parameter idx)
  // 250:     $$buf parameter.to_upper_case
  // 251:     case
  // 252:       kinds(idx)
  // 253:       OPTIONAL_PARAMETER:
  // 254:         push &buf '?'
  // 255:       SOME_PARAMETERS:
  // 256:         push &buf '*'
  // 257:       MANY_PARAMETERS:
  // ...
  initialize_future(frame->slots[14] /* show_usage */, frame->slots[18] /* temp__1 */);
  // 304: ... :
  // 305:   if
  // 306:     command.is_defined:
  // 307:       ewriteln "
  // 308:         Too few arguments for @(command)-command!
  // 309:     :
  // 310:       ewriteln "
  // 311:         Too few arguments!
  // 312:   show_usage
  // 313:   exit 1
  frame->slots[18] /* temp__1 */ = create_closure(entry__21_87_too_few_arguments_error, 0);
  // 304: $too_few_arguments_error:
  // 305:   if
  // 306:     command.is_defined:
  // 307:       ewriteln "
  // 308:         Too few arguments for @(command)-command!
  // 309:     :
  // 310:       ewriteln "
  // 311:         Too few arguments!
  // 312:   show_usage
  // 313:   exit 1
  initialize_future(frame->slots[15] /* too_few_arguments_error */, frame->slots[18] /* temp__1 */);
  // 315: ... :
  // 316:   ewriteln "
  // 317:     Too many arguments!
  // 318:   show_usage
  // 319:   exit 1
  frame->slots[18] /* temp__1 */ = create_closure(entry__21_97_too_many_arguments_error, 0);
  // 315: $too_many_arguments_error:
  // 316:   ewriteln "
  // 317:     Too many arguments!
  // 318:   show_usage
  // 319:   exit 1
  initialize_future(frame->slots[16] /* too_many_arguments_error */, frame->slots[18] /* temp__1 */);
  // 227: $$results empty_list
  ((CELL *)frame->slots[3])->contents /* results */ = get__empty_list();
  // 228: $$options empty_key_order_table
  ((CELL *)frame->slots[4])->contents /* options */ = get__empty_key_order_table();
  // 229: $$parameters empty_insert_order_table
  ((CELL *)frame->slots[5])->contents /* parameters */ = get__empty_insert_order_table();
  // 230: $$names empty_list
  ((CELL *)frame->slots[6])->contents /* names */ = get__empty_list();
  // 231: $$kinds empty_list
  ((CELL *)frame->slots[7])->contents /* kinds */ = get__empty_list();
  // 232: $$possible_values empty_list
  ((CELL *)frame->slots[8])->contents /* possible_values */ = get__empty_list();
  // 233: $$default_values empty_list
  ((CELL *)frame->slots[9])->contents /* default_values */ = get__empty_list();
  // 234: $$conversions empty_list
  ((CELL *)frame->slots[10])->contents /* conversions */ = get__empty_list();
  // 235: $$help_messages empty_list
  ((CELL *)frame->slots[11])->contents /* help_messages */ = get__empty_list();
  // 236: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__21_101;
}
static void entry__21_69(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // options: 0
  // kinds: 1
  // help_messages: 2
  // tab: 3
  frame->slots[0] = myself->closure.frame->slots[0]; /* options */
  frame->slots[1] = myself->closure.frame->slots[1]; /* kinds */
  frame->slots[2] = myself->closure.frame->slots[2]; /* help_messages */
  frame->slots[3] /* tab */ = create_cell();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 289: $$tab empty_list
  ((CELL *)frame->slots[3])->contents /* tab */ = get__empty_list();
  // 290: ... : (option idx)
  // 291:   $option_name:
  // 292:     $$buf string("--" option)
  // 293:     case
  // 294:       kinds(idx)
  // 295:       VALUED_OPTION:
  // 296:         append &buf " VALUE"
  // 297:       MULTI_VALUED_OPTION:
  // 298:         append &buf " VALUES"
  // 299:     -> buf
  // ...
  frame->slots[4] /* temp__1 */ = create_closure(entry__21_70, 2);
  // 290: for_each options: (option idx)
  // 291:   $option_name:
  // 292:     $$buf string("--" option)
  // 293:     case
  // 294:       kinds(idx)
  // 295:       VALUED_OPTION:
  // 296:         append &buf " VALUE"
  // 297:       MULTI_VALUED_OPTION:
  // 298:         append &buf " VALUES"
  // 299:     -> buf
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* options */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__21_86;
}
static void entry__21_70(void) {
  allocate_initialized_frame_gc(5, 9);
  // slot allocations:
  // option: 0
  // idx: 1
  // kinds: 2
  // tab: 3
  // help_messages: 4
  // option_name: 5
  frame->slots[2] = myself->closure.frame->slots[1]; /* kinds */
  frame->slots[3] = myself->closure.frame->slots[3]; /* tab */
  frame->slots[4] = myself->closure.frame->slots[2]; /* help_messages */
  frame->slots[5] /* option_name */ = create_future();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 291: ... :
  // 292:   $$buf string("--" option)
  // 293:   case
  // 294:     kinds(idx)
  // 295:     VALUED_OPTION:
  // 296:       append &buf " VALUE"
  // 297:     MULTI_VALUED_OPTION:
  // 298:       append &buf " VALUES"
  // 299:   -> buf
  frame->slots[6] /* temp__1 */ = create_closure(entry__21_71_option_name, 0);
  // 291: $option_name:
  // 292:   $$buf string("--" option)
  // 293:   case
  // 294:     kinds(idx)
  // 295:     VALUED_OPTION:
  // 296:       append &buf " VALUE"
  // 297:     MULTI_VALUED_OPTION:
  // 298:       append &buf " VALUES"
  // 299:   -> buf
  initialize_future(frame->slots[5] /* option_name */, frame->slots[6] /* temp__1 */);
  // 301: ... option_name()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = frame->slots[5] /* option_name */;
  func = myself->type;
  frame->cont = cont__21_82;
}
static void entry__21_71_option_name(void) {
  allocate_initialized_frame_gc(3, 7);
  // slot allocations:
  // option: 0
  // kinds: 1
  // idx: 2
  // buf: 3
  frame->slots[0] = myself->closure.frame->slots[0]; /* option */
  frame->slots[1] = myself->closure.frame->slots[2]; /* kinds */
  frame->slots[2] = myself->closure.frame->slots[1]; /* idx */
  frame->slots[3] /* buf */ = create_cell();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 292: $$buf string("--" option)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__21_72;
  arguments->slots[1] = frame->slots[0] /* option */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__21_73;
}
static void cont__21_73(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* buf */ = arguments->slots[0];
  // 294: kinds(idx)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* idx */;
  result_count = 1;
  myself = ((CELL *)frame->slots[1])->contents /* kinds */;
  func = myself->type;
  frame->cont = cont__21_74;
}
static void cont__21_74(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 295: ... :
  // 296:   append &buf " VALUE"
  frame->slots[5] /* temp__2 */ = create_closure(entry__21_75, 0);
  // 297: ... :
  // 298:   append &buf " VALUES"
  frame->slots[6] /* temp__3 */ = create_closure(entry__21_78, 0);
  // 293: case
  // 294:   kinds(idx)
  // 295:   VALUED_OPTION:
  // 296:     append &buf " VALUE"
  // 297:   MULTI_VALUED_OPTION:
  // 298:     append &buf " VALUES"
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = get__VALUED_OPTION();
  arguments->slots[2] = frame->slots[5] /* temp__2 */;
  arguments->slots[3] = get__MULTI_VALUED_OPTION();
  arguments->slots[4] = frame->slots[6] /* temp__3 */;
  result_count = 0;
  myself = get__case();
  func = myself->type;
  frame->cont = cont__21_81;
}
static void entry__21_75(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // buf: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* buf */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 296: append &buf " VALUE"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* buf */;
  arguments->slots[1] = string__21_76;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__21_77;
}
static void cont__21_77(void) {
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
static void entry__21_78(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // buf: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* buf */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 298: append &buf " VALUES"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* buf */;
  arguments->slots[1] = string__21_79;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__21_80;
}
static void cont__21_80(void) {
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
static void cont__21_81(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 299: -> buf
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* buf */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__21_82(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 301: ... help_messages(idx)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* idx */;
  result_count = 1;
  myself = ((CELL *)frame->slots[4])->contents /* help_messages */;
  func = myself->type;
  frame->cont = cont__21_83;
}
static void cont__21_83(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__3 */ = arguments->slots[0];
  // 301: ... list(option_name() help_messages(idx))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__2 */;
  arguments->slots[1] = frame->slots[8] /* temp__3 */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__21_84;
}
static void cont__21_84(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 301: push &tab list(option_name() help_messages(idx))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* tab */;
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__21_85;
}
static void cont__21_85(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* tab */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__21_86(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 302: display_table tab
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* tab */;
  result_count = frame->caller_result_count;
  myself = var._display_table;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__21_66(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // options: 0
  // kinds: 1
  // help_messages: 2
  frame->slots[0] = myself->closure.frame->slots[5]; /* options */
  frame->slots[1] = myself->closure.frame->slots[0]; /* kinds */
  frame->slots[2] = myself->closure.frame->slots[6]; /* help_messages */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 285: ewrite "
  // 286:   
  // 287:   Options:
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__21_67;
  result_count = 0;
  myself = get__ewrite();
  func = myself->type;
  frame->cont = cont__21_68;
}
static void cont__21_68(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 288: ... :
  // 289:   $$tab empty_list
  // 290:   for_each options: (option idx)
  // 291:     $option_name:
  // 292:       $$buf string("--" option)
  // 293:       case
  // 294:         kinds(idx)
  // 295:         VALUED_OPTION:
  // 296:           append &buf " VALUE"
  // 297:         MULTI_VALUED_OPTION:
  // ...
  frame->slots[3] /* temp__1 */ = create_closure(entry__21_69, 0);
  // 288: do:
  // 289:   $$tab empty_list
  // 290:   for_each options: (option idx)
  // 291:     $option_name:
  // 292:       $$buf string("--" option)
  // 293:       case
  // 294:         kinds(idx)
  // 295:         VALUED_OPTION:
  // 296:           append &buf " VALUE"
  // 297:         MULTI_VALUED_OPTION:
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__do();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__21_2_help_message(void) {
  allocate_initialized_frame_gc(3, 7);
  // slot allocations:
  // idx: 0
  // help_messages: 1
  // possible_values: 2
  // message: 3
  // possible_value: 4
  frame->slots[1] = myself->closure.frame->slots[11]; /* help_messages */
  frame->slots[2] = myself->closure.frame->slots[8]; /* possible_values */
  frame->slots[3] /* message */ = create_cell();
  frame->slots[4] /* possible_value */ = create_future();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 240: $$message help_messages(idx)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* idx */;
  result_count = 1;
  myself = ((CELL *)frame->slots[1])->contents /* help_messages */;
  func = myself->type;
  frame->cont = cont__21_3;
}
static void cont__21_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* message */ = arguments->slots[0];
  // 241: $possible_value possible_values(idx)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* idx */;
  result_count = 1;
  myself = ((CELL *)frame->slots[2])->contents /* possible_values */;
  func = myself->type;
  frame->cont = cont__21_4;
}
static void cont__21_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* possible_value */, arguments->slots[0]);
  // 242: ... possible_value.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* possible_value */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__21_5;
}
static void cont__21_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 242: ... :
  // 243:   append &message "valid values:"
  // 244:   for_each possible_value: (value) write_to &message ' ' value ','
  // 245:   !message(-1) '@nl;'
  frame->slots[6] /* temp__2 */ = create_closure(entry__21_6, 0);
  // 242: if possible_value.is_defined:
  // 243:   append &message "valid values:"
  // 244:   for_each possible_value: (value) write_to &message ' ' value ','
  // 245:   !message(-1) '@nl;'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__21_14;
}
static void entry__21_6(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // message: 0
  // possible_value: 1
  frame->slots[0] = myself->closure.frame->slots[3]; /* message */
  frame->slots[1] = myself->closure.frame->slots[4]; /* possible_value */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 243: append &message "valid values:"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* message */;
  arguments->slots[1] = string__21_7;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__21_8;
}
static void cont__21_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* message */ = arguments->slots[0];
  // 244: ... : (value) write_to &message ' ' value ','
  frame->slots[2] /* temp__1 */ = create_closure(entry__21_9, 1);
  // 244: for_each possible_value: (value) write_to &message ' ' value ','
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* possible_value */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__21_11;
}
static void entry__21_9(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // value: 0
  // message: 1
  frame->slots[1] = myself->closure.frame->slots[0]; /* message */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 244: ... write_to &message ' ' value ','
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* message */;
  arguments->slots[1] = character__32;
  arguments->slots[2] = frame->slots[0] /* value */;
  arguments->slots[3] = character__44;
  result_count = 1;
  myself = get__write_to();
  func = myself->type;
  frame->cont = cont__21_10;
}
static void cont__21_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* message */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__21_11(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 245: !message(-1) '@nl;'
  frame->slots[2] /* temp__1 */ = character__10;
  // 245: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__21_12;
}
static void cont__21_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 245: !message(-1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* message */;
  func = myself->type;
  frame->cont = cont__21_13;
}
static void cont__21_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* message */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__21_14(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 246: -> message
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* message */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__21_15_show_usage(void) {
  allocate_initialized_frame_gc(7, 11);
  // slot allocations:
  // kinds: 0
  // command_name: 1
  // command: 2
  // parameters: 3
  // help_message: 4
  // options: 5
  // help_messages: 6
  // parameter_name: 7
  frame->slots[0] = myself->closure.frame->slots[7]; /* kinds */
  frame->slots[1] = myself->closure.frame->slots[12]; /* command_name */
  frame->slots[2] = myself->closure.frame->slots[0]; /* command */
  frame->slots[3] = myself->closure.frame->slots[5]; /* parameters */
  frame->slots[4] = myself->closure.frame->slots[13]; /* help_message */
  frame->slots[5] = myself->closure.frame->slots[4]; /* options */
  frame->slots[6] = myself->closure.frame->slots[11]; /* help_messages */
  frame->slots[7] /* parameter_name */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 249: ... : (parameter idx)
  // 250:   $$buf parameter.to_upper_case
  // 251:   case
  // 252:     kinds(idx)
  // 253:     OPTIONAL_PARAMETER:
  // 254:       push &buf '?'
  // 255:     SOME_PARAMETERS:
  // 256:       push &buf '*'
  // 257:     MANY_PARAMETERS:
  // 258:       push &buf '+'
  // ...
  frame->slots[8] /* temp__1 */ = create_closure(entry__21_16_parameter_name, 2);
  // 249: $parameter_name: (parameter idx)
  // 250:   $$buf parameter.to_upper_case
  // 251:   case
  // 252:     kinds(idx)
  // 253:     OPTIONAL_PARAMETER:
  // 254:       push &buf '?'
  // 255:     SOME_PARAMETERS:
  // 256:       push &buf '*'
  // 257:     MANY_PARAMETERS:
  // 258:       push &buf '+'
  // ...
  initialize_future(frame->slots[7] /* parameter_name */, frame->slots[8] /* temp__1 */);
  // 261: ... program_version.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._program_version;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__21_26;
}
static void entry__21_16_parameter_name(void) {
  allocate_initialized_frame_gc(3, 8);
  // slot allocations:
  // parameter: 0
  // idx: 1
  // kinds: 2
  // buf: 3
  frame->slots[2] = myself->closure.frame->slots[0]; /* kinds */
  frame->slots[3] /* buf */ = create_cell();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 250: $$buf parameter.to_upper_case
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* parameter */;
  result_count = 1;
  myself = get__to_upper_case();
  func = myself->type;
  frame->cont = cont__21_17;
}
static void cont__21_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* buf */ = arguments->slots[0];
  // 252: kinds(idx)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* idx */;
  result_count = 1;
  myself = ((CELL *)frame->slots[2])->contents /* kinds */;
  func = myself->type;
  frame->cont = cont__21_18;
}
static void cont__21_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 253: ... :
  // 254:   push &buf '?'
  frame->slots[5] /* temp__2 */ = create_closure(entry__21_19, 0);
  // 255: ... :
  // 256:   push &buf '*'
  frame->slots[6] /* temp__3 */ = create_closure(entry__21_21, 0);
  // 257: ... :
  // 258:   push &buf '+'
  frame->slots[7] /* temp__4 */ = create_closure(entry__21_23, 0);
  // 251: case
  // 252:   kinds(idx)
  // 253:   OPTIONAL_PARAMETER:
  // 254:     push &buf '?'
  // 255:   SOME_PARAMETERS:
  // 256:     push &buf '*'
  // 257:   MANY_PARAMETERS:
  // 258:     push &buf '+'
  argument_count = 7;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = get__OPTIONAL_PARAMETER();
  arguments->slots[2] = frame->slots[5] /* temp__2 */;
  arguments->slots[3] = get__SOME_PARAMETERS();
  arguments->slots[4] = frame->slots[6] /* temp__3 */;
  arguments->slots[5] = get__MANY_PARAMETERS();
  arguments->slots[6] = frame->slots[7] /* temp__4 */;
  result_count = 0;
  myself = get__case();
  func = myself->type;
  frame->cont = cont__21_25;
}
static void entry__21_19(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // buf: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* buf */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 254: push &buf '?'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* buf */;
  arguments->slots[1] = character__63;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__21_20;
}
static void cont__21_20(void) {
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
static void entry__21_21(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // buf: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* buf */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 256: push &buf '*'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* buf */;
  arguments->slots[1] = character__42;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__21_22;
}
static void cont__21_22(void) {
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
static void entry__21_23(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // buf: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* buf */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 258: push &buf '+'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* buf */;
  arguments->slots[1] = character__43;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__21_24;
}
static void cont__21_24(void) {
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
static void cont__21_25(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 259: -> buf
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* buf */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__21_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__1 */ = arguments->slots[0];
  // 261: ... : show_version command_name
  frame->slots[9] /* temp__2 */ = create_closure(entry__21_27, 0);
  // 261: if program_version.is_defined: show_version command_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__1 */;
  arguments->slots[1] = frame->slots[9] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__21_28;
}
static void entry__21_27(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // command_name: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* command_name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 261: ... show_version command_name
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* command_name */;
  result_count = frame->caller_result_count;
  myself = var._show_version;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__21_28(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 262: ... command_id.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._command_id;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__21_29;
}
static void cont__21_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__1 */ = arguments->slots[0];
  // 262: ... :
  // 263:   ewriteln command_name ' ' command
  // 264:   ewriteln indented(2 command_descriptions(command_id))
  frame->slots[9] /* temp__2 */ = create_closure(entry__21_30, 0);
  // 262: if command_id.is_defined:
  // 263:   ewriteln command_name ' ' command
  // 264:   ewriteln indented(2 command_descriptions(command_id))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__1 */;
  arguments->slots[1] = frame->slots[9] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__21_34;
}
static void entry__21_30(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // command_name: 0
  // command: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* command_name */
  frame->slots[1] = myself->closure.frame->slots[2]; /* command */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 263: ewriteln command_name ' ' command
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* command_name */;
  arguments->slots[1] = character__32;
  arguments->slots[2] = frame->slots[1] /* command */;
  result_count = 0;
  myself = get__ewriteln();
  func = myself->type;
  frame->cont = cont__21_31;
}
static void cont__21_31(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 264: ... command_descriptions(command_id)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._command_id;
  result_count = 1;
  myself = var._command_descriptions;
  func = myself->type;
  frame->cont = cont__21_32;
}
static void cont__21_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 264: ... indented(2 command_descriptions(command_id))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__2;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__indented();
  func = myself->type;
  frame->cont = cont__21_33;
}
static void cont__21_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 264: ewriteln indented(2 command_descriptions(command_id))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__21_34(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 265: ewriteln "Usage:"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__21_35;
  result_count = 0;
  myself = get__ewriteln();
  func = myself->type;
  frame->cont = cont__21_36;
}
static void cont__21_36(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 266: ... command.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* command */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__21_37;
}
static void cont__21_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__1 */ = arguments->slots[0];
  // 266: ... :
  // 267:   if program_copyright.is_defined: ewriteln "  " command_name " --copyright"
  // 268:   ewriteln "  " command_name " --help"
  frame->slots[9] /* temp__2 */ = create_closure(entry__21_38, 0);
  // 266: unless command.is_defined:
  // 267:   if program_copyright.is_defined: ewriteln "  " command_name " --copyright"
  // 268:   ewriteln "  " command_name " --help"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__1 */;
  arguments->slots[1] = frame->slots[9] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__21_44;
}
static void entry__21_38(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // command_name: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* command_name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 267: ... program_copyright.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._program_copyright;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__21_39;
}
static void cont__21_39(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 267: ... : ewriteln "  " command_name " --copyright"
  frame->slots[2] /* temp__2 */ = create_closure(entry__21_40, 0);
  // 267: if program_copyright.is_defined: ewriteln "  " command_name " --copyright"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__21_42;
}
static void entry__21_40(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // command_name: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* command_name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 267: ... ewriteln "  " command_name " --copyright"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__14_11;
  arguments->slots[1] = frame->slots[0] /* command_name */;
  arguments->slots[2] = string__21_41;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__21_42(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 268: ewriteln "  " command_name " --help"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__14_11;
  arguments->slots[1] = frame->slots[0] /* command_name */;
  arguments->slots[2] = string__21_43;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__21_44(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 272: ... command.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* command */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__21_45;
}
static void cont__21_45(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__2 */ = arguments->slots[0];
  // 272: ... -> string(' ' command)
  frame->slots[10] /* temp__3 */ = create_closure(entry__21_46, 0);
  // 272: if(command.is_defined (-> string(' ' command)) -> "")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__2 */;
  arguments->slots[1] = frame->slots[10] /* temp__3 */;
  arguments->slots[2] = func__21_48;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__21_49;
}
static void entry__21_46(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // command: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* command */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 272: ... string(' ' command)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__32;
  arguments->slots[1] = frame->slots[0] /* command */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__21_47;
}
static void cont__21_47(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 272: ... -> string(' ' command)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__21_48(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 272: ... -> ""
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = empty_string;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__21_49(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__1 */ = arguments->slots[0];
  // 269: ewrite
  // 270:   "  "
  // 271:   command_name
  // 272:   if(command.is_defined (-> string(' ' command)) -> "")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__14_11;
  arguments->slots[1] = frame->slots[1] /* command_name */;
  arguments->slots[2] = frame->slots[8] /* temp__1 */;
  result_count = 0;
  myself = get__ewrite();
  func = myself->type;
  frame->cont = cont__21_50;
}
static void cont__21_50(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 273: ... : (parameter idx)
  // 274:   ewrite " " parameter_name(parameter idx)
  frame->slots[8] /* temp__1 */ = create_closure(entry__21_51, 2);
  // 273: for_each parameters: (parameter idx)
  // 274:   ewrite " " parameter_name(parameter idx)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* parameters */;
  arguments->slots[1] = frame->slots[8] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__21_53;
}
static void entry__21_51(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // parameter: 0
  // idx: 1
  // parameter_name: 2
  frame->slots[2] = myself->closure.frame->slots[7]; /* parameter_name */
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 274: ... parameter_name(parameter idx)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* parameter */;
  arguments->slots[1] = frame->slots[1] /* idx */;
  result_count = 1;
  myself = frame->slots[2] /* parameter_name */;
  func = myself->type;
  frame->cont = cont__21_52;
}
static void cont__21_52(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 274: ewrite " " parameter_name(parameter idx)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__14_19;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__ewrite();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__21_53(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 275: ewriteln
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = get__ewriteln();
  func = myself->type;
  frame->cont = cont__21_54;
}
static void cont__21_54(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 276: ewrite "
  // 277:   
  // 278:   Parameters:
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__21_55;
  result_count = 0;
  myself = get__ewrite();
  func = myself->type;
  frame->cont = cont__21_56;
}
static void cont__21_56(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 279: ... :
  // 280:   $$tab empty_list
  // 281:   for_each parameters: (parameter idx)
  // 282:     push &tab list(parameter_name(parameter idx) help_message(idx))
  // 283:   display_table tab
  frame->slots[8] /* temp__1 */ = create_closure(entry__21_57, 0);
  // 279: do:
  // 280:   $$tab empty_list
  // 281:   for_each parameters: (parameter idx)
  // 282:     push &tab list(parameter_name(parameter idx) help_message(idx))
  // 283:   display_table tab
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__1 */;
  result_count = 0;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__21_64;
}
static void entry__21_57(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // parameters: 0
  // parameter_name: 1
  // help_message: 2
  // tab: 3
  frame->slots[0] = myself->closure.frame->slots[3]; /* parameters */
  frame->slots[1] = myself->closure.frame->slots[7]; /* parameter_name */
  frame->slots[2] = myself->closure.frame->slots[4]; /* help_message */
  frame->slots[3] /* tab */ = create_cell();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 280: $$tab empty_list
  ((CELL *)frame->slots[3])->contents /* tab */ = get__empty_list();
  // 281: ... : (parameter idx)
  // 282:   push &tab list(parameter_name(parameter idx) help_message(idx))
  frame->slots[4] /* temp__1 */ = create_closure(entry__21_58, 2);
  // 281: for_each parameters: (parameter idx)
  // 282:   push &tab list(parameter_name(parameter idx) help_message(idx))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* parameters */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__21_63;
}
static void entry__21_58(void) {
  allocate_initialized_frame_gc(5, 8);
  // slot allocations:
  // parameter: 0
  // idx: 1
  // tab: 2
  // parameter_name: 3
  // help_message: 4
  frame->slots[2] = myself->closure.frame->slots[3]; /* tab */
  frame->slots[3] = myself->closure.frame->slots[1]; /* parameter_name */
  frame->slots[4] = myself->closure.frame->slots[2]; /* help_message */
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 282: ... parameter_name(parameter idx)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* parameter */;
  arguments->slots[1] = frame->slots[1] /* idx */;
  result_count = 1;
  myself = frame->slots[3] /* parameter_name */;
  func = myself->type;
  frame->cont = cont__21_59;
}
static void cont__21_59(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 282: ... help_message(idx)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* idx */;
  result_count = 1;
  myself = frame->slots[4] /* help_message */;
  func = myself->type;
  frame->cont = cont__21_60;
}
static void cont__21_60(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__3 */ = arguments->slots[0];
  // 282: ... list(parameter_name(parameter idx) help_message(idx))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__21_61;
}
static void cont__21_61(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 282: push &tab list(parameter_name(parameter idx) help_message(idx))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* tab */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__21_62;
}
static void cont__21_62(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* tab */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__21_63(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 283: display_table tab
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* tab */;
  result_count = frame->caller_result_count;
  myself = var._display_table;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__21_64(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 284: ... options.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[5])->contents /* options */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__21_65;
}
static void cont__21_65(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__1 */ = arguments->slots[0];
  // 284: ... :
  // 285:   ewrite "
  // 286:     
  // 287:     Options:
  // 288:   do:
  // 289:     $$tab empty_list
  // 290:     for_each options: (option idx)
  // 291:       $option_name:
  // 292:         $$buf string("--" option)
  // 293:         case
  // ...
  frame->slots[9] /* temp__2 */ = create_closure(entry__21_66, 0);
  // 284: unless options.is_empty:
  // 285:   ewrite "
  // 286:     
  // 287:     Options:
  // 288:   do:
  // 289:     $$tab empty_list
  // 290:     for_each options: (option idx)
  // 291:       $option_name:
  // 292:         $$buf string("--" option)
  // 293:         case
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__1 */;
  arguments->slots[1] = frame->slots[9] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__21_87_too_few_arguments_error(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // command: 0
  // show_usage: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* command */
  frame->slots[1] = myself->closure.frame->slots[14]; /* show_usage */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 306: command.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* command */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__21_88;
}
static void cont__21_88(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 306: ... :
  // 307:   ewriteln "
  // 308:     Too few arguments for @(command)-command!
  frame->slots[3] /* temp__2 */ = create_closure(entry__21_89, 0);
  // 305: if
  // 306:   command.is_defined:
  // 307:     ewriteln "
  // 308:       Too few arguments for @(command)-command!
  // 309:   :
  // 310:     ewriteln "
  // 311:       Too few arguments!
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  arguments->slots[2] = func__21_93;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__21_95;
}
static void entry__21_89(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // command: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* command */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 307: ... "
  // 308:   Too few arguments for @(command)-command!
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__21_90;
  arguments->slots[1] = frame->slots[0] /* command */;
  arguments->slots[2] = string__21_91;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__21_92;
}
static void cont__21_92(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 307: ewriteln "
  // 308:   Too few arguments for @(command)-command!
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__21_93(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 310: ewriteln "
  // 311:   Too few arguments!
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__21_94;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__21_95(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 312: show_usage
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = frame->slots[1] /* show_usage */;
  func = myself->type;
  frame->cont = cont__21_96;
}
static void cont__21_96(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 313: exit 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = frame->caller_result_count;
  myself = get__exit();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__21_97_too_many_arguments_error(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // show_usage: 0
  frame->slots[0] = myself->closure.frame->slots[14]; /* show_usage */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 316: ewriteln "
  // 317:   Too many arguments!
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__21_98;
  result_count = 0;
  myself = get__ewriteln();
  func = myself->type;
  frame->cont = cont__21_99;
}
static void cont__21_99(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 318: show_usage
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = frame->slots[0] /* show_usage */;
  func = myself->type;
  frame->cont = cont__21_100;
}
static void cont__21_100(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 319: exit 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = frame->caller_result_count;
  myself = get__exit();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__21_101(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[18] /* temp__1 */ = arguments->slots[0];
  // 236: $command_name truncate_until(program_name '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__program_name();
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[18] /* temp__1 */;
  result_count = 1;
  myself = get__truncate_until();
  func = myself->type;
  frame->cont = cont__21_102;
}
static void cont__21_102(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[12] /* command_name */, arguments->slots[0]);
  // 237: map &arguments from_utf8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* arguments */;
  arguments->slots[1] = get__from_utf8();
  result_count = 1;
  myself = get__map();
  func = myself->type;
  frame->cont = cont__21_103;
}
static void cont__21_103(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* arguments */ = arguments->slots[0];
  // 321: ... : (idx template)
  // 322:   template $$option $name? $default_value? $conversion? $help
  // 323:   if
  // 324:     option.is_a_key_value_pair:
  // 325:       push &possible_values value_of(option)
  // 326:       !option key_of(option)
  // 327:     :
  // 328:       push &possible_values undefined
  // 329:   push &names if(name.is_defined (-> name) -> option)
  // 330:   push &kinds option
  // ...
  frame->slots[18] /* temp__1 */ = create_closure(entry__21_104, 2);
  // 321: for_each templates: (idx template)
  // 322:   template $$option $name? $default_value? $conversion? $help
  // 323:   if
  // 324:     option.is_a_key_value_pair:
  // 325:       push &possible_values value_of(option)
  // 326:       !option key_of(option)
  // 327:     :
  // 328:       push &possible_values undefined
  // 329:   push &names if(name.is_defined (-> name) -> option)
  // 330:   push &kinds option
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* templates */;
  arguments->slots[1] = frame->slots[18] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__21_150;
}
static void entry__21_144(void) {
  allocate_initialized_frame_gc(4, 5);
  // slot allocations:
  // results: 0
  // parameters: 1
  // name: 2
  // idx: 3
  frame->slots[0] = myself->closure.frame->slots[1]; /* results */
  frame->slots[1] = myself->closure.frame->slots[2]; /* parameters */
  frame->slots[2] = myself->closure.frame->slots[3]; /* name */
  frame->slots[3] = myself->closure.frame->slots[4]; /* idx */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 346: push &results empty_list
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* results */;
  arguments->slots[1] = get__empty_list();
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__21_145;
}
static void cont__21_145(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* results */ = arguments->slots[0];
  // 347: !parameters(name) idx
  frame->slots[4] /* temp__1 */ = frame->slots[3] /* idx */;
  // 347: !parameters(name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* name */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[1])->contents /* parameters */;
  func = myself->type;
  frame->cont = cont__21_146;
}
static void cont__21_146(void) {
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
static void entry__21_136(void) {
  allocate_initialized_frame_gc(4, 5);
  // slot allocations:
  // results: 0
  // options: 1
  // name: 2
  // idx: 3
  frame->slots[0] = myself->closure.frame->slots[1]; /* results */
  frame->slots[1] = myself->closure.frame->slots[2]; /* options */
  frame->slots[2] = myself->closure.frame->slots[3]; /* name */
  frame->slots[3] = myself->closure.frame->slots[4]; /* idx */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 343: push &results empty_list
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* results */;
  arguments->slots[1] = get__empty_list();
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__21_137;
}
static void cont__21_137(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* results */ = arguments->slots[0];
  // 344: !options(name) idx
  frame->slots[4] /* temp__1 */ = frame->slots[3] /* idx */;
  // 344: !options(name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* name */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[1])->contents /* options */;
  func = myself->type;
  frame->cont = cont__21_138;
}
static void cont__21_138(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* options */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__21_131(void) {
  allocate_initialized_frame_gc(4, 5);
  // slot allocations:
  // results: 0
  // options: 1
  // name: 2
  // idx: 3
  frame->slots[0] = myself->closure.frame->slots[1]; /* results */
  frame->slots[1] = myself->closure.frame->slots[2]; /* options */
  frame->slots[2] = myself->closure.frame->slots[3]; /* name */
  frame->slots[3] = myself->closure.frame->slots[4]; /* idx */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 340: push &results undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* results */;
  arguments->slots[1] = get__undefined();
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__21_132;
}
static void cont__21_132(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* results */ = arguments->slots[0];
  // 341: !options(name) idx
  frame->slots[4] /* temp__1 */ = frame->slots[3] /* idx */;
  // 341: !options(name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* name */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[1])->contents /* options */;
  func = myself->type;
  frame->cont = cont__21_133;
}
static void cont__21_133(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* options */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__21_125(void) {
  allocate_initialized_frame_gc(5, 6);
  // slot allocations:
  // results: 0
  // options: 1
  // option: 2
  // idx: 3
  // kinds: 4
  frame->slots[0] = myself->closure.frame->slots[1]; /* results */
  frame->slots[1] = myself->closure.frame->slots[2]; /* options */
  frame->slots[2] = myself->closure.frame->slots[0]; /* option */
  frame->slots[3] = myself->closure.frame->slots[3]; /* idx */
  frame->slots[4] = myself->closure.frame->slots[4]; /* kinds */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 336: push &results false
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* results */;
  arguments->slots[1] = get__false();
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__21_126;
}
static void cont__21_126(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* results */ = arguments->slots[0];
  // 337: !options(option) idx
  frame->slots[5] /* temp__1 */ = frame->slots[3] /* idx */;
  // 337: !options(option)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* option */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[1])->contents /* options */;
  func = myself->type;
  frame->cont = cont__21_127;
}
static void cont__21_127(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* options */ = arguments->slots[0];
  // 338: !kinds(idx) BOOLEAN_OPTION
  frame->slots[5] /* temp__1 */ = var._BOOLEAN_OPTION;
  // 338: !kinds(idx)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* idx */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[4])->contents /* kinds */;
  func = myself->type;
  frame->cont = cont__21_128;
}
static void cont__21_128(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[4])->contents /* kinds */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__21_123(void) {
  allocate_initialized_frame_gc(5, 7);
  // slot allocations:
  // option: 0
  // results: 1
  // options: 2
  // idx: 3
  // kinds: 4
  frame->slots[0] = myself->closure.frame->slots[11]; /* option */
  frame->slots[1] = myself->closure.frame->slots[8]; /* results */
  frame->slots[2] = myself->closure.frame->slots[9]; /* options */
  frame->slots[3] = myself->closure.frame->slots[0]; /* idx */
  frame->slots[4] = myself->closure.frame->slots[4]; /* kinds */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 335: ... option.is_a_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* option */;
  result_count = 1;
  myself = get__is_a_string();
  func = myself->type;
  frame->cont = cont__21_124;
}
static void cont__21_124(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 335: ... :
  // 336:   push &results false
  // 337:   !options(option) idx
  // 338:   !kinds(idx) BOOLEAN_OPTION
  frame->slots[6] /* temp__2 */ = create_closure(entry__21_125, 0);
  // 335: -> option.is_a_string:
  // 336:   push &results false
  // 337:   !options(option) idx
  // 338:   !kinds(idx) BOOLEAN_OPTION
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__21_129(void) {
  allocate_initialized_frame_gc(5, 7);
  // slot allocations:
  // option: 0
  // results: 1
  // options: 2
  // name: 3
  // idx: 4
  frame->slots[0] = myself->closure.frame->slots[11]; /* option */
  frame->slots[1] = myself->closure.frame->slots[8]; /* results */
  frame->slots[2] = myself->closure.frame->slots[9]; /* options */
  frame->slots[3] = myself->closure.frame->slots[12]; /* name */
  frame->slots[4] = myself->closure.frame->slots[0]; /* idx */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 339: ... option == VALUED_OPTION
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* option */;
  arguments->slots[1] = get__VALUED_OPTION();
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__21_130;
}
static void cont__21_130(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 339: ... :
  // 340:   push &results undefined
  // 341:   !options(name) idx
  frame->slots[6] /* temp__2 */ = create_closure(entry__21_131, 0);
  // 339: -> option == VALUED_OPTION:
  // 340:   push &results undefined
  // 341:   !options(name) idx
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__21_134(void) {
  allocate_initialized_frame_gc(5, 7);
  // slot allocations:
  // option: 0
  // results: 1
  // options: 2
  // name: 3
  // idx: 4
  frame->slots[0] = myself->closure.frame->slots[11]; /* option */
  frame->slots[1] = myself->closure.frame->slots[8]; /* results */
  frame->slots[2] = myself->closure.frame->slots[9]; /* options */
  frame->slots[3] = myself->closure.frame->slots[12]; /* name */
  frame->slots[4] = myself->closure.frame->slots[0]; /* idx */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 342: ... option == MULTI_VALUED_OPTION
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* option */;
  arguments->slots[1] = get__MULTI_VALUED_OPTION();
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__21_135;
}
static void cont__21_135(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 342: ... :
  // 343:   push &results empty_list
  // 344:   !options(name) idx
  frame->slots[6] /* temp__2 */ = create_closure(entry__21_136, 0);
  // 342: -> option == MULTI_VALUED_OPTION:
  // 343:   push &results empty_list
  // 344:   !options(name) idx
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__21_139(void) {
  allocate_initialized_frame_gc(5, 9);
  // slot allocations:
  // option: 0
  // results: 1
  // parameters: 2
  // name: 3
  // idx: 4
  frame->slots[0] = myself->closure.frame->slots[11]; /* option */
  frame->slots[1] = myself->closure.frame->slots[8]; /* results */
  frame->slots[2] = myself->closure.frame->slots[10]; /* parameters */
  frame->slots[3] = myself->closure.frame->slots[12]; /* name */
  frame->slots[4] = myself->closure.frame->slots[0]; /* idx */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 345: ... option == SOME_PARAMETERS
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* option */;
  arguments->slots[1] = get__SOME_PARAMETERS();
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__21_140;
}
static void cont__21_140(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 345: ... option == MANY_PARAMETERS
  frame->slots[7] /* temp__3 */ = create_closure(entry__21_141, 0);
  // 345: ... option == SOME_PARAMETERS || option == MANY_PARAMETERS
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__21_143;
}
static void entry__21_141(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // option: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* option */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 345: ... option == MANY_PARAMETERS
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* option */;
  arguments->slots[1] = get__MANY_PARAMETERS();
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__21_142;
}
static void cont__21_142(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 345: ... option == MANY_PARAMETERS
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__21_143(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 345: ... :
  // 346:   push &results empty_list
  // 347:   !parameters(name) idx
  frame->slots[8] /* temp__4 */ = create_closure(entry__21_144, 0);
  // 345: -> option == SOME_PARAMETERS || option == MANY_PARAMETERS:
  // 346:   push &results empty_list
  // 347:   !parameters(name) idx
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__4 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__21_147(void) {
  allocate_initialized_frame_gc(4, 5);
  // slot allocations:
  // results: 0
  // parameters: 1
  // name: 2
  // idx: 3
  frame->slots[0] = myself->closure.frame->slots[8]; /* results */
  frame->slots[1] = myself->closure.frame->slots[10]; /* parameters */
  frame->slots[2] = myself->closure.frame->slots[12]; /* name */
  frame->slots[3] = myself->closure.frame->slots[0]; /* idx */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 349: push &results undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* results */;
  arguments->slots[1] = get__undefined();
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__21_148;
}
static void cont__21_148(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* results */ = arguments->slots[0];
  // 350: !parameters(name) idx
  frame->slots[4] /* temp__1 */ = frame->slots[3] /* idx */;
  // 350: !parameters(name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* name */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[1])->contents /* parameters */;
  func = myself->type;
  frame->cont = cont__21_149;
}
static void cont__21_149(void) {
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
static void entry__21_104(void) {
  allocate_initialized_frame_gc(11, 21);
  // slot allocations:
  // idx: 0
  // template: 1
  // possible_values: 2
  // names: 3
  // kinds: 4
  // default_values: 5
  // conversions: 6
  // help_messages: 7
  // results: 8
  // options: 9
  // parameters: 10
  // option: 11
  // name: 12
  // default_value: 13
  // conversion: 14
  // help: 15
  frame->slots[2] = myself->closure.frame->slots[8]; /* possible_values */
  frame->slots[3] = myself->closure.frame->slots[6]; /* names */
  frame->slots[4] = myself->closure.frame->slots[7]; /* kinds */
  frame->slots[5] = myself->closure.frame->slots[9]; /* default_values */
  frame->slots[6] = myself->closure.frame->slots[10]; /* conversions */
  frame->slots[7] = myself->closure.frame->slots[11]; /* help_messages */
  frame->slots[8] = myself->closure.frame->slots[3]; /* results */
  frame->slots[9] = myself->closure.frame->slots[4]; /* options */
  frame->slots[10] = myself->closure.frame->slots[5]; /* parameters */
  frame->slots[11] /* option */ = create_cell();
  frame->slots[12] /* name */ = create_future();
  frame->slots[13] /* default_value */ = create_future();
  frame->slots[14] /* conversion */ = create_future();
  frame->slots[15] /* help */ = create_future();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 322: template $$option $name? $default_value? $conversion? $help
  argument_count = 0;
  arguments = node_p;
  result_count = -1;
  myself = frame->slots[1] /* template */;
  func = myself->type;
  frame->cont = cont__21_105;
}
static void cont__21_105(void) {
  if (argument_count < 2) {
    too_few_results_error();
    return;
  }
  if (argument_count > 5) {
    too_many_results_error();
    return;
  }
  ((CELL *)frame->slots[11])->contents /* option */ = arguments->slots[0];
  frame->slots[19] /* temp__4 */ = arguments->slots[argument_count-1];
  switch(argument_count) {
    default: frame->slots[18] /* temp__3 */ = arguments->slots[3];
    case 4: frame->slots[17] /* temp__2 */ = arguments->slots[2];
    case 3: frame->slots[16] /* temp__1 */ = arguments->slots[1];
    case 2:;
  }
  switch(argument_count) {
    case 2: frame->slots[16] /* temp__1 */ = undefined;
    case 3: frame->slots[17] /* temp__2 */ = undefined;
    case 4: frame->slots[18] /* temp__3 */ = undefined;
  }
  // 322: ... name
  initialize_future(frame->slots[12] /* name */, frame->slots[16] /* temp__1 */);
  // 322: ... default_value
  initialize_future(frame->slots[13] /* default_value */, frame->slots[17] /* temp__2 */);
  // 322: ... conversion
  initialize_future(frame->slots[14] /* conversion */, frame->slots[18] /* temp__3 */);
  // 322: ... help
  initialize_future(frame->slots[15] /* help */, frame->slots[19] /* temp__4 */);
  // 324: option.is_a_key_value_pair
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[11])->contents /* option */;
  result_count = 1;
  myself = get__is_a_key_value_pair();
  func = myself->type;
  frame->cont = cont__21_106;
}
static void cont__21_106(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[16] /* temp__1 */ = arguments->slots[0];
  // 324: ... :
  // 325:   push &possible_values value_of(option)
  // 326:   !option key_of(option)
  frame->slots[17] /* temp__2 */ = create_closure(entry__21_107, 0);
  // 327: :
  // 328:   push &possible_values undefined
  frame->slots[18] /* temp__3 */ = create_closure(entry__21_111, 0);
  // 323: if
  // 324:   option.is_a_key_value_pair:
  // 325:     push &possible_values value_of(option)
  // 326:     !option key_of(option)
  // 327:   :
  // 328:     push &possible_values undefined
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[16] /* temp__1 */;
  arguments->slots[1] = frame->slots[17] /* temp__2 */;
  arguments->slots[2] = frame->slots[18] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__21_113;
}
static void entry__21_107(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // possible_values: 0
  // option: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* possible_values */
  frame->slots[1] = myself->closure.frame->slots[11]; /* option */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 325: ... value_of(option)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* option */;
  result_count = 1;
  myself = get__value_of();
  func = myself->type;
  frame->cont = cont__21_108;
}
static void cont__21_108(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 325: push &possible_values value_of(option)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* possible_values */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__21_109;
}
static void cont__21_109(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* possible_values */ = arguments->slots[0];
  // 326: !option key_of(option)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* option */;
  result_count = 1;
  myself = get__key_of();
  func = myself->type;
  frame->cont = cont__21_110;
}
static void cont__21_110(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* option */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__21_111(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // possible_values: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* possible_values */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 328: push &possible_values undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* possible_values */;
  arguments->slots[1] = get__undefined();
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__21_112;
}
static void cont__21_112(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* possible_values */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__21_113(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 329: ... name.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[12] /* name */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__21_114;
}
static void cont__21_114(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[17] /* temp__2 */ = arguments->slots[0];
  // 329: ... -> name
  frame->slots[18] /* temp__3 */ = create_closure(entry__21_115, 0);
  // 329: ... -> option
  frame->slots[19] /* temp__4 */ = create_closure(entry__21_116, 0);
  // 329: ... if(name.is_defined (-> name) -> option)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[17] /* temp__2 */;
  arguments->slots[1] = frame->slots[18] /* temp__3 */;
  arguments->slots[2] = frame->slots[19] /* temp__4 */;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__21_117;
}
static void entry__21_115(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[12]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 329: ... -> name
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__21_116(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // option: 0
  frame->slots[0] = myself->closure.frame->slots[11]; /* option */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 329: ... -> option
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* option */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__21_117(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[16] /* temp__1 */ = arguments->slots[0];
  // 329: push &names if(name.is_defined (-> name) -> option)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* names */;
  arguments->slots[1] = frame->slots[16] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__21_118;
}
static void cont__21_118(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* names */ = arguments->slots[0];
  // 330: push &kinds option
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* kinds */;
  arguments->slots[1] = ((CELL *)frame->slots[11])->contents /* option */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__21_119;
}
static void cont__21_119(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[4])->contents /* kinds */ = arguments->slots[0];
  // 331: push &default_values default_value
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[5])->contents /* default_values */;
  arguments->slots[1] = frame->slots[13] /* default_value */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__21_120;
}
static void cont__21_120(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[5])->contents /* default_values */ = arguments->slots[0];
  // 332: push &conversions conversion
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[6])->contents /* conversions */;
  arguments->slots[1] = frame->slots[14] /* conversion */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__21_121;
}
static void cont__21_121(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[6])->contents /* conversions */ = arguments->slots[0];
  // 333: push &help_messages help
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[7])->contents /* help_messages */;
  arguments->slots[1] = frame->slots[15] /* help */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__21_122;
}
static void cont__21_122(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[7])->contents /* help_messages */ = arguments->slots[0];
  // 335: -> option.is_a_string:
  // 336:   push &results false
  // 337:   !options(option) idx
  // 338:   !kinds(idx) BOOLEAN_OPTION
  frame->slots[16] /* temp__1 */ = create_closure(entry__21_123, 0);
  // 339: -> option == VALUED_OPTION:
  // 340:   push &results undefined
  // 341:   !options(name) idx
  frame->slots[17] /* temp__2 */ = create_closure(entry__21_129, 0);
  // 342: -> option == MULTI_VALUED_OPTION:
  // 343:   push &results empty_list
  // 344:   !options(name) idx
  frame->slots[18] /* temp__3 */ = create_closure(entry__21_134, 0);
  // 345: -> option == SOME_PARAMETERS || option == MANY_PARAMETERS:
  // 346:   push &results empty_list
  // 347:   !parameters(name) idx
  frame->slots[19] /* temp__4 */ = create_closure(entry__21_139, 0);
  // 348: :
  // 349:   push &results undefined
  // 350:   !parameters(name) idx
  frame->slots[20] /* temp__5 */ = create_closure(entry__21_147, 0);
  // 334: cond
  // 335:   -> option.is_a_string:
  // 336:     push &results false
  // 337:     !options(option) idx
  // 338:     !kinds(idx) BOOLEAN_OPTION
  // 339:   -> option == VALUED_OPTION:
  // 340:     push &results undefined
  // 341:     !options(name) idx
  // 342:   -> option == MULTI_VALUED_OPTION:
  // 343:     push &results empty_list
  // ...
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = frame->slots[16] /* temp__1 */;
  arguments->slots[1] = frame->slots[17] /* temp__2 */;
  arguments->slots[2] = frame->slots[18] /* temp__3 */;
  arguments->slots[3] = frame->slots[19] /* temp__4 */;
  arguments->slots[4] = frame->slots[20] /* temp__5 */;
  result_count = frame->caller_result_count;
  myself = get__cond();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__21_150(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 351: ... length_of(arguments)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* arguments */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__21_151;
}
static void cont__21_151(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[20] /* temp__3 */ = arguments->slots[0];
  // 351: ... length_of(arguments) >= 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[20] /* temp__3 */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__21_152;
}
static void cont__21_152(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[19] /* temp__2 */ = arguments->slots[0];
  // 351: ... length_of(arguments) >= 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[19] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__21_153;
}
static void cont__21_153(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[18] /* temp__1 */ = arguments->slots[0];
  // 351: ... :
  // 352:   if arguments(1) == "--help":
  // 353:     show_usage
  // 354:     terminate
  // 355:   if program_copyright.is_defined && arguments(1) == "--copyright":
  // 356:     show_copyright
  // 357:     terminate
  // 358:   if program_version.is_defined && arguments(1) == "--version":
  // 359:     show_version command_name
  // 360:     terminate
  frame->slots[21] /* temp__4 */ = create_closure(entry__21_154, 0);
  // 351: if length_of(arguments) >= 1:
  // 352:   if arguments(1) == "--help":
  // 353:     show_usage
  // 354:     terminate
  // 355:   if program_copyright.is_defined && arguments(1) == "--copyright":
  // 356:     show_copyright
  // 357:     terminate
  // 358:   if program_version.is_defined && arguments(1) == "--version":
  // 359:     show_version command_name
  // 360:     terminate
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[18] /* temp__1 */;
  arguments->slots[1] = frame->slots[21] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__21_178;
}
static void entry__21_176(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // command_name: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* command_name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 359: show_version command_name
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* command_name */;
  result_count = 0;
  myself = var._show_version;
  func = myself->type;
  frame->cont = cont__21_177;
}
static void cont__21_177(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 360: terminate
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = get__terminate();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__21_154(void) {
  allocate_initialized_frame_gc(3, 7);
  // slot allocations:
  // arguments: 0
  // show_usage: 1
  // command_name: 2
  frame->slots[0] = myself->closure.frame->slots[1]; /* arguments */
  frame->slots[1] = myself->closure.frame->slots[14]; /* show_usage */
  frame->slots[2] = myself->closure.frame->slots[12]; /* command_name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 352: ... arguments(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* arguments */;
  func = myself->type;
  frame->cont = cont__21_155;
}
static void cont__21_155(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 352: ... arguments(1) == "--help"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = string__21_156;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__21_157;
}
static void cont__21_157(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 352: ... :
  // 353:   show_usage
  // 354:   terminate
  frame->slots[5] /* temp__3 */ = create_closure(entry__21_158, 0);
  // 352: if arguments(1) == "--help":
  // 353:   show_usage
  // 354:   terminate
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__21_160;
}
static void entry__21_158(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // show_usage: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* show_usage */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 353: show_usage
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = frame->slots[0] /* show_usage */;
  func = myself->type;
  frame->cont = cont__21_159;
}
static void cont__21_159(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 354: terminate
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = get__terminate();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__21_160(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 355: ... program_copyright.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._program_copyright;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__21_161;
}
static void cont__21_161(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 355: ... arguments(1) == "--copyright"
  frame->slots[5] /* temp__3 */ = create_closure(entry__21_162, 0);
  // 355: ... program_copyright.is_defined && arguments(1) == "--copyright"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__21_166;
}
static void entry__21_162(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // arguments: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* arguments */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 355: ... arguments(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* arguments */;
  func = myself->type;
  frame->cont = cont__21_163;
}
static void cont__21_163(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 355: ... arguments(1) == "--copyright"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = string__21_164;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__21_165;
}
static void cont__21_165(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 355: ... arguments(1) == "--copyright"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__21_166(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 355: if program_copyright.is_defined && arguments(1) == "--copyright":
  // 356:   show_copyright
  // 357:   terminate
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = func__21_167;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__21_169;
}
static void entry__21_167(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 356: show_copyright
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = var._show_copyright;
  func = myself->type;
  frame->cont = cont__21_168;
}
static void cont__21_168(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 357: terminate
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = get__terminate();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__21_169(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 358: ... program_version.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._program_version;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__21_170;
}
static void cont__21_170(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 358: ... arguments(1) == "--version"
  frame->slots[5] /* temp__3 */ = create_closure(entry__21_171, 0);
  // 358: ... program_version.is_defined && arguments(1) == "--version"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__21_175;
}
static void entry__21_171(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // arguments: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* arguments */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 358: ... arguments(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* arguments */;
  func = myself->type;
  frame->cont = cont__21_172;
}
static void cont__21_172(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 358: ... arguments(1) == "--version"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = string__21_173;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__21_174;
}
static void cont__21_174(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 358: ... arguments(1) == "--version"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__21_175(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 358: ... :
  // 359:   show_version command_name
  // 360:   terminate
  frame->slots[6] /* temp__4 */ = create_closure(entry__21_176, 0);
  // 358: if program_version.is_defined && arguments(1) == "--version":
  // 359:   show_version command_name
  // 360:   terminate
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__21_178(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 361: ... :
  // 362:   $$idx 1
  // 363:   $$fetch_option_value false
  // 364:   $$option_idx undefined
  // 365:   do: (-> break)
  // 366:     for_each arguments: (argument)
  // 367:       if argument == "--":
  // 368:         delete_at &arguments idx
  // 369:         break
  // 370:       if
  // ...
  frame->slots[18] /* temp__1 */ = create_closure(entry__21_179, 0);
  // 361: do:
  // 362:   $$idx 1
  // 363:   $$fetch_option_value false
  // 364:   $$option_idx undefined
  // 365:   do: (-> break)
  // 366:     for_each arguments: (argument)
  // 367:       if argument == "--":
  // 368:         delete_at &arguments idx
  // 369:         break
  // 370:       if
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[18] /* temp__1 */;
  result_count = 0;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__21_216;
}
static void entry__21_180(void) {
  allocate_initialized_frame_gc(8, 9);
  // slot allocations:
  // break: 0
  // arguments: 1
  // idx: 2
  // fetch_option_value: 3
  // kinds: 4
  // option_idx: 5
  // results: 6
  // options: 7
  frame->slots[0] /* break */ = create_continuation();
  frame->slots[1] = myself->closure.frame->slots[0]; /* arguments */
  frame->slots[2] = myself->closure.frame->slots[4]; /* idx */
  frame->slots[3] = myself->closure.frame->slots[5]; /* fetch_option_value */
  frame->slots[4] = myself->closure.frame->slots[1]; /* kinds */
  frame->slots[5] = myself->closure.frame->slots[6]; /* option_idx */
  frame->slots[6] = myself->closure.frame->slots[2]; /* results */
  frame->slots[7] = myself->closure.frame->slots[3]; /* options */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 366: ... : (argument)
  // 367:   if argument == "--":
  // 368:     delete_at &arguments idx
  // 369:     break
  // 370:   if
  // 371:     fetch_option_value:
  // 372:       !fetch_option_value false
  // 373:       delete_at &arguments idx
  // 374:       case
  // 375:         kinds(option_idx)
  // ...
  frame->slots[8] /* temp__1 */ = create_closure(entry__21_181, 1);
  // 366: for_each arguments: (argument)
  // 367:   if argument == "--":
  // 368:     delete_at &arguments idx
  // 369:     break
  // 370:   if
  // 371:     fetch_option_value:
  // 372:       !fetch_option_value false
  // 373:       delete_at &arguments idx
  // 374:       case
  // 375:         kinds(option_idx)
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* arguments */;
  arguments->slots[1] = frame->slots[8] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__21_215;
}
static void entry__21_197(void) {
  allocate_initialized_frame_gc(8, 12);
  // slot allocations:
  // option_idx: 0
  // options: 1
  // argument: 2
  // kinds: 3
  // results: 4
  // fetch_option_value: 5
  // arguments: 6
  // idx: 7
  frame->slots[0] = myself->closure.frame->slots[1]; /* option_idx */
  frame->slots[1] = myself->closure.frame->slots[2]; /* options */
  frame->slots[2] = myself->closure.frame->slots[0]; /* argument */
  frame->slots[3] = myself->closure.frame->slots[3]; /* kinds */
  frame->slots[4] = myself->closure.frame->slots[4]; /* results */
  frame->slots[5] = myself->closure.frame->slots[5]; /* fetch_option_value */
  frame->slots[6] = myself->closure.frame->slots[6]; /* arguments */
  frame->slots[7] = myself->closure.frame->slots[7]; /* idx */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 383: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__21_198;
}
static void cont__21_198(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__2 */ = arguments->slots[0];
  // 383: ... range(argument 3 -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* argument */;
  arguments->slots[1] = number__3;
  arguments->slots[2] = frame->slots[9] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__21_199;
}
static void cont__21_199(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__1 */ = arguments->slots[0];
  // 383: !option_idx options(range(argument 3 -1))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[1])->contents /* options */;
  func = myself->type;
  frame->cont = cont__21_200;
}
static void cont__21_200(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* option_idx */ = arguments->slots[0];
  // 384: ... option_idx.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* option_idx */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__21_201;
}
static void cont__21_201(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__1 */ = arguments->slots[0];
  // 384: ... : Error "Invalid option: @(argument)!"
  frame->slots[9] /* temp__2 */ = create_closure(entry__21_202, 0);
  // 384: if option_idx.is_undefined: Error "Invalid option: @(argument)!"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__1 */;
  arguments->slots[1] = frame->slots[9] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__21_205;
}
static void entry__21_202(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // argument: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* argument */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 384: ... "Invalid option: @(argument)!"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__21_203;
  arguments->slots[1] = frame->slots[0] /* argument */;
  arguments->slots[2] = string__12_46;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__21_204;
}
static void cont__21_204(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 384: ... Error "Invalid option: @(argument)!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__21_205(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 386: kinds(option_idx)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* option_idx */;
  result_count = 1;
  myself = ((CELL *)frame->slots[3])->contents /* kinds */;
  func = myself->type;
  frame->cont = cont__21_206;
}
static void cont__21_206(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__2 */ = arguments->slots[0];
  // 386: kinds(option_idx) == BOOLEAN_OPTION
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__2 */;
  arguments->slots[1] = var._BOOLEAN_OPTION;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__21_207;
}
static void cont__21_207(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__1 */ = arguments->slots[0];
  // 386: ... :
  // 387:   !results(option_idx) true
  frame->slots[10] /* temp__3 */ = create_closure(entry__21_208, 0);
  // 388: :
  // 389:   !fetch_option_value true
  frame->slots[11] /* temp__4 */ = create_closure(entry__21_210, 0);
  // 385: if
  // 386:   kinds(option_idx) == BOOLEAN_OPTION:
  // 387:     !results(option_idx) true
  // 388:   :
  // 389:     !fetch_option_value true
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__1 */;
  arguments->slots[1] = frame->slots[10] /* temp__3 */;
  arguments->slots[2] = frame->slots[11] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__21_211;
}
static void entry__21_208(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // results: 0
  // option_idx: 1
  frame->slots[0] = myself->closure.frame->slots[4]; /* results */
  frame->slots[1] = myself->closure.frame->slots[0]; /* option_idx */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 387: !results(option_idx) true
  frame->slots[2] /* temp__1 */ = get__true();
  // 387: !results(option_idx)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* option_idx */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* results */;
  func = myself->type;
  frame->cont = cont__21_209;
}
static void cont__21_209(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* results */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__21_210(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // fetch_option_value: 0
  frame->slots[0] = myself->closure.frame->slots[5]; /* fetch_option_value */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 389: !fetch_option_value true
  ((CELL *)frame->slots[0])->contents /* fetch_option_value */ = get__true();
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__21_211(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 390: delete_at &arguments idx
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[6])->contents /* arguments */;
  arguments->slots[1] = ((CELL *)frame->slots[7])->contents /* idx */;
  result_count = 1;
  myself = get__delete_at();
  func = myself->type;
  frame->cont = cont__21_212;
}
static void cont__21_212(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[6])->contents /* arguments */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__21_213(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // idx: 0
  frame->slots[0] = myself->closure.frame->slots[7]; /* idx */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 392: inc &idx
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* idx */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__21_214;
}
static void cont__21_214(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* idx */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__21_189(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // results: 0
  // option_idx: 1
  // argument: 2
  frame->slots[0] = myself->closure.frame->slots[5]; /* results */
  frame->slots[1] = myself->closure.frame->slots[4]; /* option_idx */
  frame->slots[2] = myself->closure.frame->slots[6]; /* argument */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 377: !results(option_idx) argument
  frame->slots[3] /* temp__1 */ = frame->slots[2] /* argument */;
  // 377: !results(option_idx)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* option_idx */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* results */;
  func = myself->type;
  frame->cont = cont__21_190;
}
static void cont__21_190(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* results */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__21_191(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // results: 0
  // option_idx: 1
  // argument: 2
  frame->slots[0] = myself->closure.frame->slots[5]; /* results */
  frame->slots[1] = myself->closure.frame->slots[4]; /* option_idx */
  frame->slots[2] = myself->closure.frame->slots[6]; /* argument */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 379: ... results(option_idx)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* option_idx */;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* results */;
  func = myself->type;
  frame->cont = cont__21_192;
}
static void cont__21_192(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 379: push &results(option_idx) argument
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* argument */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__21_193;
}
static void cont__21_193(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 379: ... &results(option_idx)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* option_idx */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* results */;
  func = myself->type;
  frame->cont = cont__21_194;
}
static void cont__21_194(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* results */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__21_186(void) {
  allocate_initialized_frame_gc(7, 10);
  // slot allocations:
  // fetch_option_value: 0
  // arguments: 1
  // idx: 2
  // kinds: 3
  // option_idx: 4
  // results: 5
  // argument: 6
  frame->slots[0] = myself->closure.frame->slots[4]; /* fetch_option_value */
  frame->slots[1] = myself->closure.frame->slots[1]; /* arguments */
  frame->slots[2] = myself->closure.frame->slots[2]; /* idx */
  frame->slots[3] = myself->closure.frame->slots[5]; /* kinds */
  frame->slots[4] = myself->closure.frame->slots[6]; /* option_idx */
  frame->slots[5] = myself->closure.frame->slots[7]; /* results */
  frame->slots[6] = myself->closure.frame->slots[0]; /* argument */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 372: !fetch_option_value false
  ((CELL *)frame->slots[0])->contents /* fetch_option_value */ = get__false();
  // 373: delete_at &arguments idx
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* arguments */;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* idx */;
  result_count = 1;
  myself = get__delete_at();
  func = myself->type;
  frame->cont = cont__21_187;
}
static void cont__21_187(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* arguments */ = arguments->slots[0];
  // 375: kinds(option_idx)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* option_idx */;
  result_count = 1;
  myself = ((CELL *)frame->slots[3])->contents /* kinds */;
  func = myself->type;
  frame->cont = cont__21_188;
}
static void cont__21_188(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 376: ... :
  // 377:   !results(option_idx) argument
  frame->slots[8] /* temp__2 */ = create_closure(entry__21_189, 0);
  // 378: ... :
  // 379:   push &results(option_idx) argument
  frame->slots[9] /* temp__3 */ = create_closure(entry__21_191, 0);
  // 374: case
  // 375:   kinds(option_idx)
  // 376:   VALUED_OPTION:
  // 377:     !results(option_idx) argument
  // 378:   MULTI_VALUED_OPTION:
  // 379:     push &results(option_idx) argument
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = get__VALUED_OPTION();
  arguments->slots[2] = frame->slots[8] /* temp__2 */;
  arguments->slots[3] = get__MULTI_VALUED_OPTION();
  arguments->slots[4] = frame->slots[9] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__21_195(void) {
  allocate_initialized_frame_gc(8, 11);
  // slot allocations:
  // argument: 0
  // option_idx: 1
  // options: 2
  // kinds: 3
  // results: 4
  // fetch_option_value: 5
  // arguments: 6
  // idx: 7
  frame->slots[0] = myself->closure.frame->slots[0]; /* argument */
  frame->slots[1] = myself->closure.frame->slots[6]; /* option_idx */
  frame->slots[2] = myself->closure.frame->slots[8]; /* options */
  frame->slots[3] = myself->closure.frame->slots[5]; /* kinds */
  frame->slots[4] = myself->closure.frame->slots[7]; /* results */
  frame->slots[5] = myself->closure.frame->slots[4]; /* fetch_option_value */
  frame->slots[6] = myself->closure.frame->slots[1]; /* arguments */
  frame->slots[7] = myself->closure.frame->slots[2]; /* idx */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 382: argument .has_prefix. "--"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* argument */;
  arguments->slots[1] = string__21_72;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__21_196;
}
static void cont__21_196(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__1 */ = arguments->slots[0];
  // 382: ... :
  // 383:   !option_idx options(range(argument 3 -1))
  // 384:   if option_idx.is_undefined: Error "Invalid option: @(argument)!"
  // 385:   if
  // 386:     kinds(option_idx) == BOOLEAN_OPTION:
  // 387:       !results(option_idx) true
  // 388:     :
  // 389:       !fetch_option_value true
  // 390:   delete_at &arguments idx
  frame->slots[9] /* temp__2 */ = create_closure(entry__21_197, 0);
  // 391: :
  // 392:   inc &idx
  frame->slots[10] /* temp__3 */ = create_closure(entry__21_213, 0);
  // 381: if
  // 382:   argument .has_prefix. "--":
  // 383:     !option_idx options(range(argument 3 -1))
  // 384:     if option_idx.is_undefined: Error "Invalid option: @(argument)!"
  // 385:     if
  // 386:       kinds(option_idx) == BOOLEAN_OPTION:
  // 387:         !results(option_idx) true
  // 388:       :
  // 389:         !fetch_option_value true
  // 390:     delete_at &arguments idx
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__1 */;
  arguments->slots[1] = frame->slots[9] /* temp__2 */;
  arguments->slots[2] = frame->slots[10] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__21_181(void) {
  allocate_initialized_frame_gc(9, 11);
  // slot allocations:
  // argument: 0
  // arguments: 1
  // idx: 2
  // break: 3
  // fetch_option_value: 4
  // kinds: 5
  // option_idx: 6
  // results: 7
  // options: 8
  frame->slots[1] = myself->closure.frame->slots[1]; /* arguments */
  frame->slots[2] = myself->closure.frame->slots[2]; /* idx */
  frame->slots[3] = myself->closure.frame->slots[0]; /* break */
  frame->slots[4] = myself->closure.frame->slots[3]; /* fetch_option_value */
  frame->slots[5] = myself->closure.frame->slots[4]; /* kinds */
  frame->slots[6] = myself->closure.frame->slots[5]; /* option_idx */
  frame->slots[7] = myself->closure.frame->slots[6]; /* results */
  frame->slots[8] = myself->closure.frame->slots[7]; /* options */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 367: ... argument == "--"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* argument */;
  arguments->slots[1] = string__21_72;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__21_182;
}
static void cont__21_182(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 367: ... :
  // 368:   delete_at &arguments idx
  // 369:   break
  frame->slots[10] /* temp__2 */ = create_closure(entry__21_183, 0);
  // 367: if argument == "--":
  // 368:   delete_at &arguments idx
  // 369:   break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  arguments->slots[1] = frame->slots[10] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__21_185;
}
static void entry__21_183(void) {
  allocate_initialized_frame_gc(3, 3);
  // slot allocations:
  // arguments: 0
  // idx: 1
  // break: 2
  frame->slots[0] = myself->closure.frame->slots[1]; /* arguments */
  frame->slots[1] = myself->closure.frame->slots[2]; /* idx */
  frame->slots[2] = myself->closure.frame->slots[3]; /* break */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 368: delete_at &arguments idx
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* arguments */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* idx */;
  result_count = 1;
  myself = get__delete_at();
  func = myself->type;
  frame->cont = cont__21_184;
}
static void cont__21_184(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* arguments */ = arguments->slots[0];
  // 369: break
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[2] /* break */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__21_185(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 371: ... :
  // 372:   !fetch_option_value false
  // 373:   delete_at &arguments idx
  // 374:   case
  // 375:     kinds(option_idx)
  // 376:     VALUED_OPTION:
  // 377:       !results(option_idx) argument
  // 378:     MULTI_VALUED_OPTION:
  // 379:       push &results(option_idx) argument
  frame->slots[9] /* temp__1 */ = create_closure(entry__21_186, 0);
  // 380: :
  // 381:   if
  // 382:     argument .has_prefix. "--":
  // 383:       !option_idx options(range(argument 3 -1))
  // 384:       if option_idx.is_undefined: Error "Invalid option: @(argument)!"
  // 385:       if
  // 386:         kinds(option_idx) == BOOLEAN_OPTION:
  // 387:           !results(option_idx) true
  // 388:         :
  // 389:           !fetch_option_value true
  // ...
  frame->slots[10] /* temp__2 */ = create_closure(entry__21_195, 0);
  // 370: if
  // 371:   fetch_option_value:
  // 372:     !fetch_option_value false
  // 373:     delete_at &arguments idx
  // 374:     case
  // 375:       kinds(option_idx)
  // 376:       VALUED_OPTION:
  // 377:         !results(option_idx) argument
  // 378:       MULTI_VALUED_OPTION:
  // 379:         push &results(option_idx) argument
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* fetch_option_value */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  arguments->slots[2] = frame->slots[10] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__21_215(void) {
  myself = frame->slots[0] /* break */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__21_179(void) {
  allocate_initialized_frame_gc(4, 8);
  // slot allocations:
  // arguments: 0
  // kinds: 1
  // results: 2
  // options: 3
  // idx: 4
  // fetch_option_value: 5
  // option_idx: 6
  frame->slots[0] = myself->closure.frame->slots[1]; /* arguments */
  frame->slots[1] = myself->closure.frame->slots[7]; /* kinds */
  frame->slots[2] = myself->closure.frame->slots[3]; /* results */
  frame->slots[3] = myself->closure.frame->slots[4]; /* options */
  frame->slots[4] /* idx */ = create_cell();
  frame->slots[5] /* fetch_option_value */ = create_cell();
  frame->slots[6] /* option_idx */ = create_cell();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 362: $$idx 1
  ((CELL *)frame->slots[4])->contents /* idx */ = number__1;
  // 363: $$fetch_option_value false
  ((CELL *)frame->slots[5])->contents /* fetch_option_value */ = get__false();
  // 364: $$option_idx undefined
  ((CELL *)frame->slots[6])->contents /* option_idx */ = get__undefined();
  // 365: ... : (-> break)
  // 366:   for_each arguments: (argument)
  // 367:     if argument == "--":
  // 368:       delete_at &arguments idx
  // 369:       break
  // 370:     if
  // 371:       fetch_option_value:
  // 372:         !fetch_option_value false
  // 373:         delete_at &arguments idx
  // 374:         case
  // ...
  frame->slots[7] /* temp__1 */ = create_closure(entry__21_180, 0);
  // 365: do: (-> break)
  // 366:   for_each arguments: (argument)
  // 367:     if argument == "--":
  // 368:       delete_at &arguments idx
  // 369:       break
  // 370:     if
  // 371:       fetch_option_value:
  // 372:         !fetch_option_value false
  // 373:         delete_at &arguments idx
  // 374:         case
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__do();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__21_216(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 393: $$last_idx -1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__21_217;
}
static void cont__21_217(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[17])->contents /* last_idx */ = arguments->slots[0];
  // 394: ... : (-> break)
  // 395:   for_each_from_down_to templates -1 1: (idx template)
  // 396:     template $$option $_name? $_default_value? $_conversion? $_help
  // 397:     if option.is_a_key_value_pair: !option key_of(option)
  // 398:     case
  // 399:       option
  // 400:       MANDATORY_PARAMETER:
  // 401:         if arguments.is_empty too_few_arguments_error
  // 402:         pop &arguments !results(idx)
  // 403:         !last_idx idx-1
  // ...
  frame->slots[18] /* temp__1 */ = create_closure(entry__21_218, 0);
  // 394: do: (-> break)
  // 395:   for_each_from_down_to templates -1 1: (idx template)
  // 396:     template $$option $_name? $_default_value? $_conversion? $_help
  // 397:     if option.is_a_key_value_pair: !option key_of(option)
  // 398:     case
  // 399:       option
  // 400:       MANDATORY_PARAMETER:
  // 401:         if arguments.is_empty too_few_arguments_error
  // 402:         pop &arguments !results(idx)
  // 403:         !last_idx idx-1
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[18] /* temp__1 */;
  result_count = 0;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__21_235;
}
static void entry__21_218(void) {
  allocate_initialized_frame_gc(6, 8);
  // slot allocations:
  // break: 0
  // templates: 1
  // arguments: 2
  // too_few_arguments_error: 3
  // results: 4
  // last_idx: 5
  frame->slots[0] /* break */ = create_continuation();
  frame->slots[1] = myself->closure.frame->slots[2]; /* templates */
  frame->slots[2] = myself->closure.frame->slots[1]; /* arguments */
  frame->slots[3] = myself->closure.frame->slots[15]; /* too_few_arguments_error */
  frame->slots[4] = myself->closure.frame->slots[3]; /* results */
  frame->slots[5] = myself->closure.frame->slots[17]; /* last_idx */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 395: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__21_219;
}
static void cont__21_219(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 395: ... : (idx template)
  // 396:   template $$option $_name? $_default_value? $_conversion? $_help
  // 397:   if option.is_a_key_value_pair: !option key_of(option)
  // 398:   case
  // 399:     option
  // 400:     MANDATORY_PARAMETER:
  // 401:       if arguments.is_empty too_few_arguments_error
  // 402:       pop &arguments !results(idx)
  // 403:       !last_idx idx-1
  // 404:     OPTIONAL_PARAMETER, SOME_PARAMETERS, MANY_PARAMETERS:
  // ...
  frame->slots[7] /* temp__2 */ = create_closure(entry__21_220, 2);
  // 395: for_each_from_down_to templates -1 1: (idx template)
  // 396:   template $$option $_name? $_default_value? $_conversion? $_help
  // 397:   if option.is_a_key_value_pair: !option key_of(option)
  // 398:   case
  // 399:     option
  // 400:     MANDATORY_PARAMETER:
  // 401:       if arguments.is_empty too_few_arguments_error
  // 402:       pop &arguments !results(idx)
  // 403:       !last_idx idx-1
  // 404:     OPTIONAL_PARAMETER, SOME_PARAMETERS, MANY_PARAMETERS:
  // ...
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* templates */;
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  arguments->slots[2] = number__1;
  arguments->slots[3] = frame->slots[7] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__for_each_from_down_to();
  func = myself->type;
  frame->cont = cont__21_234;
}
static void entry__21_233(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // break: 0
  frame->slots[0] = myself->closure.frame->slots[6]; /* break */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 405: break
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* break */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__21_220(void) {
  allocate_initialized_frame_gc(7, 16);
  // slot allocations:
  // idx: 0
  // template: 1
  // arguments: 2
  // too_few_arguments_error: 3
  // results: 4
  // last_idx: 5
  // break: 6
  // option: 7
  // name: 8
  // default_value: 9
  // conversion: 10
  // help: 11
  frame->slots[2] = myself->closure.frame->slots[2]; /* arguments */
  frame->slots[3] = myself->closure.frame->slots[3]; /* too_few_arguments_error */
  frame->slots[4] = myself->closure.frame->slots[4]; /* results */
  frame->slots[5] = myself->closure.frame->slots[5]; /* last_idx */
  frame->slots[6] = myself->closure.frame->slots[0]; /* break */
  frame->slots[7] /* option */ = create_cell();
  frame->slots[8] /* name */ = create_future();
  frame->slots[9] /* default_value */ = create_future();
  frame->slots[10] /* conversion */ = create_future();
  frame->slots[11] /* help */ = create_future();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 396: template $$option $_name? $_default_value? $_conversion? $_help
  argument_count = 0;
  arguments = node_p;
  result_count = -1;
  myself = frame->slots[1] /* template */;
  func = myself->type;
  frame->cont = cont__21_221;
}
static void cont__21_221(void) {
  if (argument_count < 2) {
    too_few_results_error();
    return;
  }
  if (argument_count > 5) {
    too_many_results_error();
    return;
  }
  ((CELL *)frame->slots[7])->contents /* option */ = arguments->slots[0];
  frame->slots[15] /* temp__4 */ = arguments->slots[argument_count-1];
  switch(argument_count) {
    default: frame->slots[14] /* temp__3 */ = arguments->slots[3];
    case 4: frame->slots[13] /* temp__2 */ = arguments->slots[2];
    case 3: frame->slots[12] /* temp__1 */ = arguments->slots[1];
    case 2:;
  }
  switch(argument_count) {
    case 2: frame->slots[12] /* temp__1 */ = undefined;
    case 3: frame->slots[13] /* temp__2 */ = undefined;
    case 4: frame->slots[14] /* temp__3 */ = undefined;
  }
  // 396: ... _name
  initialize_future(frame->slots[8] /* name */, frame->slots[12] /* temp__1 */);
  // 396: ... _default_value
  initialize_future(frame->slots[9] /* default_value */, frame->slots[13] /* temp__2 */);
  // 396: ... _conversion
  initialize_future(frame->slots[10] /* conversion */, frame->slots[14] /* temp__3 */);
  // 396: ... _help
  initialize_future(frame->slots[11] /* help */, frame->slots[15] /* temp__4 */);
  // 397: ... option.is_a_key_value_pair
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[7])->contents /* option */;
  result_count = 1;
  myself = get__is_a_key_value_pair();
  func = myself->type;
  frame->cont = cont__21_222;
}
static void cont__21_222(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__1 */ = arguments->slots[0];
  // 397: ... : !option key_of(option)
  frame->slots[13] /* temp__2 */ = create_closure(entry__21_223, 0);
  // 397: if option.is_a_key_value_pair: !option key_of(option)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[12] /* temp__1 */;
  arguments->slots[1] = frame->slots[13] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__21_225;
}
static void entry__21_223(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // option: 0
  frame->slots[0] = myself->closure.frame->slots[7]; /* option */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 397: ... !option key_of(option)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* option */;
  result_count = 1;
  myself = get__key_of();
  func = myself->type;
  frame->cont = cont__21_224;
}
static void cont__21_224(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* option */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__21_225(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 400: ... :
  // 401:   if arguments.is_empty too_few_arguments_error
  // 402:   pop &arguments !results(idx)
  // 403:   !last_idx idx-1
  frame->slots[12] /* temp__1 */ = create_closure(entry__21_226, 0);
  // 404: OPTIONAL_PARAMETER, SOME_PARAMETERS, MANY_PARAMETERS
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__OPTIONAL_PARAMETER();
  arguments->slots[1] = get__SOME_PARAMETERS();
  arguments->slots[2] = get__MANY_PARAMETERS();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__21_232;
}
static void entry__21_226(void) {
  allocate_initialized_frame_gc(5, 6);
  // slot allocations:
  // arguments: 0
  // too_few_arguments_error: 1
  // results: 2
  // idx: 3
  // last_idx: 4
  frame->slots[0] = myself->closure.frame->slots[2]; /* arguments */
  frame->slots[1] = myself->closure.frame->slots[3]; /* too_few_arguments_error */
  frame->slots[2] = myself->closure.frame->slots[4]; /* results */
  frame->slots[3] = myself->closure.frame->slots[0]; /* idx */
  frame->slots[4] = myself->closure.frame->slots[5]; /* last_idx */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 401: ... arguments.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* arguments */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__21_227;
}
static void cont__21_227(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 401: if arguments.is_empty too_few_arguments_error
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* too_few_arguments_error */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__21_228;
}
static void cont__21_228(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 402: pop &arguments !results(idx)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* arguments */;
  result_count = 2;
  myself = get__pop();
  func = myself->type;
  frame->cont = cont__21_229;
}
static void cont__21_229(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* arguments */ = arguments->slots[0];
  frame->slots[5] /* temp__1 */ = arguments->slots[1];
  // 402: ... !results(idx)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* idx */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[2])->contents /* results */;
  func = myself->type;
  frame->cont = cont__21_230;
}
static void cont__21_230(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* results */ = arguments->slots[0];
  // 403: !last_idx idx-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* idx */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__21_231;
}
static void cont__21_231(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[4])->contents /* last_idx */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__21_232(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__2 */ = arguments->slots[0];
  // 404: ... :
  // 405:   break
  frame->slots[14] /* temp__3 */ = create_closure(entry__21_233, 0);
  // 398: case
  // 399:   option
  // 400:   MANDATORY_PARAMETER:
  // 401:     if arguments.is_empty too_few_arguments_error
  // 402:     pop &arguments !results(idx)
  // 403:     !last_idx idx-1
  // 404:   OPTIONAL_PARAMETER, SOME_PARAMETERS, MANY_PARAMETERS:
  // 405:     break
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[7])->contents /* option */;
  arguments->slots[1] = get__MANDATORY_PARAMETER();
  arguments->slots[2] = frame->slots[12] /* temp__1 */;
  arguments->slots[3] = frame->slots[13] /* temp__2 */;
  arguments->slots[4] = frame->slots[14] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__21_234(void) {
  myself = frame->slots[0] /* break */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__21_235(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 406: ... : (idx template)
  // 407:   template $$option $_name? $_default_value? $_conversion? $_help
  // 408:   if option.is_a_key_value_pair: !option key_of(option)
  // 409:   case
  // 410:     option
  // 411:     MANDATORY_PARAMETER:
  // 412:       if length_of(arguments) == 0 too_few_arguments_error
  // 413:       get &arguments !results(idx)
  // 414:     OPTIONAL_PARAMETER:
  // 415:       if length_of(arguments) > 0: get &arguments !results(idx)
  // ...
  frame->slots[18] /* temp__1 */ = create_closure(entry__21_236, 2);
  // 406: for_each_from_to templates 1 last_idx: (idx template)
  // 407:   template $$option $_name? $_default_value? $_conversion? $_help
  // 408:   if option.is_a_key_value_pair: !option key_of(option)
  // 409:   case
  // 410:     option
  // 411:     MANDATORY_PARAMETER:
  // 412:       if length_of(arguments) == 0 too_few_arguments_error
  // 413:       get &arguments !results(idx)
  // 414:     OPTIONAL_PARAMETER:
  // 415:       if length_of(arguments) > 0: get &arguments !results(idx)
  // ...
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* templates */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = ((CELL *)frame->slots[17])->contents /* last_idx */;
  arguments->slots[3] = frame->slots[18] /* temp__1 */;
  result_count = 0;
  myself = get__for_each_from_to();
  func = myself->type;
  frame->cont = cont__21_261;
}
static void entry__21_251(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // arguments: 0
  // results: 1
  // idx: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* arguments */
  frame->slots[1] = myself->closure.frame->slots[1]; /* results */
  frame->slots[2] = myself->closure.frame->slots[2]; /* idx */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 415: ... get &arguments !results(idx)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* arguments */;
  result_count = 2;
  myself = get__get();
  func = myself->type;
  frame->cont = cont__21_252;
}
static void cont__21_252(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* arguments */ = arguments->slots[0];
  frame->slots[3] /* temp__1 */ = arguments->slots[1];
  // 415: ... !results(idx)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* idx */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[1])->contents /* results */;
  func = myself->type;
  frame->cont = cont__21_253;
}
static void cont__21_253(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* results */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__21_242(void) {
  allocate_initialized_frame_gc(4, 6);
  // slot allocations:
  // arguments: 0
  // too_few_arguments_error: 1
  // results: 2
  // idx: 3
  frame->slots[0] = myself->closure.frame->slots[2]; /* arguments */
  frame->slots[1] = myself->closure.frame->slots[3]; /* too_few_arguments_error */
  frame->slots[2] = myself->closure.frame->slots[4]; /* results */
  frame->slots[3] = myself->closure.frame->slots[0]; /* idx */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 412: ... length_of(arguments)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* arguments */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__21_243;
}
static void cont__21_243(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 412: ... length_of(arguments) == 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__21_244;
}
static void cont__21_244(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 412: if length_of(arguments) == 0 too_few_arguments_error
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* too_few_arguments_error */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__21_245;
}
static void cont__21_245(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 413: get &arguments !results(idx)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* arguments */;
  result_count = 2;
  myself = get__get();
  func = myself->type;
  frame->cont = cont__21_246;
}
static void cont__21_246(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* arguments */ = arguments->slots[0];
  frame->slots[4] /* temp__1 */ = arguments->slots[1];
  // 413: ... !results(idx)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* idx */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[2])->contents /* results */;
  func = myself->type;
  frame->cont = cont__21_247;
}
static void cont__21_247(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* results */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__21_248(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // arguments: 0
  // results: 1
  // idx: 2
  frame->slots[0] = myself->closure.frame->slots[2]; /* arguments */
  frame->slots[1] = myself->closure.frame->slots[4]; /* results */
  frame->slots[2] = myself->closure.frame->slots[0]; /* idx */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 415: ... length_of(arguments)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* arguments */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__21_249;
}
static void cont__21_249(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 415: ... length_of(arguments) > 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__21_250;
}
static void cont__21_250(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 415: ... : get &arguments !results(idx)
  frame->slots[5] /* temp__3 */ = create_closure(entry__21_251, 0);
  // 415: if length_of(arguments) > 0: get &arguments !results(idx)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__21_254(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // results: 0
  // idx: 1
  // arguments: 2
  frame->slots[0] = myself->closure.frame->slots[4]; /* results */
  frame->slots[1] = myself->closure.frame->slots[0]; /* idx */
  frame->slots[2] = myself->closure.frame->slots[2]; /* arguments */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 417: !results(idx) arguments
  frame->slots[3] /* temp__1 */ = ((CELL *)frame->slots[2])->contents /* arguments */;
  // 417: !results(idx)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* idx */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* results */;
  func = myself->type;
  frame->cont = cont__21_255;
}
static void cont__21_255(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* results */ = arguments->slots[0];
  // 418: !arguments empty_list
  ((CELL *)frame->slots[2])->contents /* arguments */ = get__empty_list();
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__21_256(void) {
  allocate_initialized_frame_gc(4, 6);
  // slot allocations:
  // arguments: 0
  // too_few_arguments_error: 1
  // results: 2
  // idx: 3
  frame->slots[0] = myself->closure.frame->slots[2]; /* arguments */
  frame->slots[1] = myself->closure.frame->slots[3]; /* too_few_arguments_error */
  frame->slots[2] = myself->closure.frame->slots[4]; /* results */
  frame->slots[3] = myself->closure.frame->slots[0]; /* idx */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 420: ... length_of(arguments)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* arguments */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__21_257;
}
static void cont__21_257(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 420: ... length_of(arguments) == 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__21_258;
}
static void cont__21_258(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 420: if length_of(arguments) == 0 too_few_arguments_error
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* too_few_arguments_error */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__21_259;
}
static void cont__21_259(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 421: !results(idx) arguments
  frame->slots[4] /* temp__1 */ = ((CELL *)frame->slots[0])->contents /* arguments */;
  // 421: !results(idx)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* idx */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[2])->contents /* results */;
  func = myself->type;
  frame->cont = cont__21_260;
}
static void cont__21_260(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* results */ = arguments->slots[0];
  // 422: !arguments empty_list
  ((CELL *)frame->slots[0])->contents /* arguments */ = get__empty_list();
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__21_236(void) {
  allocate_initialized_frame_gc(5, 14);
  // slot allocations:
  // idx: 0
  // template: 1
  // arguments: 2
  // too_few_arguments_error: 3
  // results: 4
  // option: 5
  // name: 6
  // default_value: 7
  // conversion: 8
  // help: 9
  frame->slots[2] = myself->closure.frame->slots[1]; /* arguments */
  frame->slots[3] = myself->closure.frame->slots[15]; /* too_few_arguments_error */
  frame->slots[4] = myself->closure.frame->slots[3]; /* results */
  frame->slots[5] /* option */ = create_cell();
  frame->slots[6] /* name */ = create_future();
  frame->slots[7] /* default_value */ = create_future();
  frame->slots[8] /* conversion */ = create_future();
  frame->slots[9] /* help */ = create_future();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 407: template $$option $_name? $_default_value? $_conversion? $_help
  argument_count = 0;
  arguments = node_p;
  result_count = -1;
  myself = frame->slots[1] /* template */;
  func = myself->type;
  frame->cont = cont__21_237;
}
static void cont__21_237(void) {
  if (argument_count < 2) {
    too_few_results_error();
    return;
  }
  if (argument_count > 5) {
    too_many_results_error();
    return;
  }
  ((CELL *)frame->slots[5])->contents /* option */ = arguments->slots[0];
  frame->slots[13] /* temp__4 */ = arguments->slots[argument_count-1];
  switch(argument_count) {
    default: frame->slots[12] /* temp__3 */ = arguments->slots[3];
    case 4: frame->slots[11] /* temp__2 */ = arguments->slots[2];
    case 3: frame->slots[10] /* temp__1 */ = arguments->slots[1];
    case 2:;
  }
  switch(argument_count) {
    case 2: frame->slots[10] /* temp__1 */ = undefined;
    case 3: frame->slots[11] /* temp__2 */ = undefined;
    case 4: frame->slots[12] /* temp__3 */ = undefined;
  }
  // 407: ... _name
  initialize_future(frame->slots[6] /* name */, frame->slots[10] /* temp__1 */);
  // 407: ... _default_value
  initialize_future(frame->slots[7] /* default_value */, frame->slots[11] /* temp__2 */);
  // 407: ... _conversion
  initialize_future(frame->slots[8] /* conversion */, frame->slots[12] /* temp__3 */);
  // 407: ... _help
  initialize_future(frame->slots[9] /* help */, frame->slots[13] /* temp__4 */);
  // 408: ... option.is_a_key_value_pair
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[5])->contents /* option */;
  result_count = 1;
  myself = get__is_a_key_value_pair();
  func = myself->type;
  frame->cont = cont__21_238;
}
static void cont__21_238(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__1 */ = arguments->slots[0];
  // 408: ... : !option key_of(option)
  frame->slots[11] /* temp__2 */ = create_closure(entry__21_239, 0);
  // 408: if option.is_a_key_value_pair: !option key_of(option)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__1 */;
  arguments->slots[1] = frame->slots[11] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__21_241;
}
static void entry__21_239(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // option: 0
  frame->slots[0] = myself->closure.frame->slots[5]; /* option */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 408: ... !option key_of(option)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* option */;
  result_count = 1;
  myself = get__key_of();
  func = myself->type;
  frame->cont = cont__21_240;
}
static void cont__21_240(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* option */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__21_241(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 411: ... :
  // 412:   if length_of(arguments) == 0 too_few_arguments_error
  // 413:   get &arguments !results(idx)
  frame->slots[10] /* temp__1 */ = create_closure(entry__21_242, 0);
  // 414: ... :
  // 415:   if length_of(arguments) > 0: get &arguments !results(idx)
  frame->slots[11] /* temp__2 */ = create_closure(entry__21_248, 0);
  // 416: ... :
  // 417:   !results(idx) arguments
  // 418:   !arguments empty_list
  frame->slots[12] /* temp__3 */ = create_closure(entry__21_254, 0);
  // 419: ... :
  // 420:   if length_of(arguments) == 0 too_few_arguments_error
  // 421:   !results(idx) arguments
  // 422:   !arguments empty_list
  frame->slots[13] /* temp__4 */ = create_closure(entry__21_256, 0);
  // 409: case
  // 410:   option
  // 411:   MANDATORY_PARAMETER:
  // 412:     if length_of(arguments) == 0 too_few_arguments_error
  // 413:     get &arguments !results(idx)
  // 414:   OPTIONAL_PARAMETER:
  // 415:     if length_of(arguments) > 0: get &arguments !results(idx)
  // 416:   SOME_PARAMETERS:
  // 417:     !results(idx) arguments
  // 418:     !arguments empty_list
  // ...
  argument_count = 9;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[5])->contents /* option */;
  arguments->slots[1] = get__MANDATORY_PARAMETER();
  arguments->slots[2] = frame->slots[10] /* temp__1 */;
  arguments->slots[3] = get__OPTIONAL_PARAMETER();
  arguments->slots[4] = frame->slots[11] /* temp__2 */;
  arguments->slots[5] = get__SOME_PARAMETERS();
  arguments->slots[6] = frame->slots[12] /* temp__3 */;
  arguments->slots[7] = get__MANY_PARAMETERS();
  arguments->slots[8] = frame->slots[13] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__21_261(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 423: ... arguments.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* arguments */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__21_262;
}
static void cont__21_262(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[18] /* temp__1 */ = arguments->slots[0];
  // 423: unless arguments.is_empty too_many_arguments_error
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[18] /* temp__1 */;
  arguments->slots[1] = frame->slots[16] /* too_many_arguments_error */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__21_263;
}
static void cont__21_263(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 424: ... : (idx result)
  // 425:   if
  // 426:     result.is_undefined && default_values(idx).is_defined:
  // 427:       !results(idx) default_values(idx)
  // 428:     :
  // 429:       $possible_value possible_values(idx)
  // 430:       
  // 431:       $check: (value)
  // 432:         unless possible_value(value):
  // 433:           ewriteln
  // ...
  frame->slots[18] /* temp__1 */ = create_closure(entry__21_264, 2);
  // 424: for_each results: (idx result)
  // 425:   if
  // 426:     result.is_undefined && default_values(idx).is_defined:
  // 427:       !results(idx) default_values(idx)
  // 428:     :
  // 429:       $possible_value possible_values(idx)
  // 430:       
  // 431:       $check: (value)
  // 432:         unless possible_value(value):
  // 433:           ewriteln
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* results */;
  arguments->slots[1] = frame->slots[18] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__21_305;
}
static void entry__21_296(void) {
  allocate_initialized_frame_gc(4, 6);
  // slot allocations:
  // result: 0
  // conversion: 1
  // results: 2
  // idx: 3
  // new_result: 4
  frame->slots[0] = myself->closure.frame->slots[0]; /* result */
  frame->slots[1] = myself->closure.frame->slots[1]; /* conversion */
  frame->slots[2] = myself->closure.frame->slots[2]; /* results */
  frame->slots[3] = myself->closure.frame->slots[3]; /* idx */
  frame->slots[4] /* new_result */ = create_cell();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 448: $$new_result empty_list
  ((CELL *)frame->slots[4])->contents /* new_result */ = get__empty_list();
  // 449: ... : (item) push &new_result conversion(item)
  frame->slots[5] /* temp__1 */ = create_closure(entry__21_297, 1);
  // 449: for_each result: (item) push &new_result conversion(item)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* result */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__21_300;
}
static void entry__21_297(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // item: 0
  // new_result: 1
  // conversion: 2
  frame->slots[1] = myself->closure.frame->slots[4]; /* new_result */
  frame->slots[2] = myself->closure.frame->slots[1]; /* conversion */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 449: ... conversion(item)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* item */;
  result_count = 1;
  myself = frame->slots[2] /* conversion */;
  func = myself->type;
  frame->cont = cont__21_298;
}
static void cont__21_298(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 449: ... push &new_result conversion(item)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* new_result */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__21_299;
}
static void cont__21_299(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* new_result */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__21_300(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 450: !results(idx) new_result
  frame->slots[5] /* temp__1 */ = ((CELL *)frame->slots[4])->contents /* new_result */;
  // 450: !results(idx)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* idx */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[2])->contents /* results */;
  func = myself->type;
  frame->cont = cont__21_301;
}
static void cont__21_301(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* results */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__21_302(void) {
  allocate_initialized_frame_gc(4, 5);
  // slot allocations:
  // results: 0
  // idx: 1
  // conversion: 2
  // result: 3
  frame->slots[0] = myself->closure.frame->slots[2]; /* results */
  frame->slots[1] = myself->closure.frame->slots[3]; /* idx */
  frame->slots[2] = myself->closure.frame->slots[1]; /* conversion */
  frame->slots[3] = myself->closure.frame->slots[0]; /* result */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 452: !results(idx) conversion(result)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* result */;
  result_count = 1;
  myself = frame->slots[2] /* conversion */;
  func = myself->type;
  frame->cont = cont__21_303;
}
static void cont__21_303(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 452: !results(idx)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* idx */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* results */;
  func = myself->type;
  frame->cont = cont__21_304;
}
static void cont__21_304(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* results */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__21_294(void) {
  allocate_initialized_frame_gc(4, 7);
  // slot allocations:
  // result: 0
  // conversion: 1
  // results: 2
  // idx: 3
  frame->slots[0] = myself->closure.frame->slots[4]; /* result */
  frame->slots[1] = myself->closure.frame->slots[9]; /* conversion */
  frame->slots[2] = myself->closure.frame->slots[6]; /* results */
  frame->slots[3] = myself->closure.frame->slots[1]; /* idx */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 447: result.is_a_list
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* result */;
  result_count = 1;
  myself = get__is_a_list();
  func = myself->type;
  frame->cont = cont__21_295;
}
static void cont__21_295(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 447: ... :
  // 448:   $$new_result empty_list
  // 449:   for_each result: (item) push &new_result conversion(item)
  // 450:   !results(idx) new_result
  frame->slots[5] /* temp__2 */ = create_closure(entry__21_296, 0);
  // 451: :
  // 452:   !results(idx) conversion(result)
  frame->slots[6] /* temp__3 */ = create_closure(entry__21_302, 0);
  // 446: if
  // 447:   result.is_a_list:
  // 448:     $$new_result empty_list
  // 449:     for_each result: (item) push &new_result conversion(item)
  // 450:     !results(idx) new_result
  // 451:   :
  // 452:     !results(idx) conversion(result)
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
static void entry__21_270(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // results: 0
  // idx: 1
  // default_values: 2
  frame->slots[0] = myself->closure.frame->slots[3]; /* results */
  frame->slots[1] = myself->closure.frame->slots[0]; /* idx */
  frame->slots[2] = myself->closure.frame->slots[2]; /* default_values */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 427: !results(idx) default_values(idx)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* idx */;
  result_count = 1;
  myself = ((CELL *)frame->slots[2])->contents /* default_values */;
  func = myself->type;
  frame->cont = cont__21_271;
}
static void cont__21_271(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 427: !results(idx)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* idx */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* results */;
  func = myself->type;
  frame->cont = cont__21_272;
}
static void cont__21_272(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* results */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__21_273(void) {
  allocate_initialized_frame_gc(7, 12);
  // slot allocations:
  // possible_values: 0
  // idx: 1
  // names: 2
  // show_usage: 3
  // result: 4
  // conversions: 5
  // results: 6
  // possible_value: 7
  // check: 8
  // conversion: 9
  frame->slots[0] = myself->closure.frame->slots[4]; /* possible_values */
  frame->slots[1] = myself->closure.frame->slots[0]; /* idx */
  frame->slots[2] = myself->closure.frame->slots[5]; /* names */
  frame->slots[3] = myself->closure.frame->slots[6]; /* show_usage */
  frame->slots[4] = myself->closure.frame->slots[1]; /* result */
  frame->slots[5] = myself->closure.frame->slots[7]; /* conversions */
  frame->slots[6] = myself->closure.frame->slots[3]; /* results */
  frame->slots[8] /* check */ = create_future();
  frame->slots[7] /* possible_value */ = create_future();
  frame->slots[9] /* conversion */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 431: ... : (value)
  // 432:   unless possible_value(value):
  // 433:     ewriteln
  // 434:       "Invalid argument value for @(names(idx).to_upper_case)!@nl;"
  // 435:     show_usage
  // 436:     exit 1
  frame->slots[10] /* temp__1 */ = create_closure(entry__21_274_check, 1);
  // 431: $check: (value)
  // 432:   unless possible_value(value):
  // 433:     ewriteln
  // 434:       "Invalid argument value for @(names(idx).to_upper_case)!@nl;"
  // 435:     show_usage
  // 436:     exit 1
  initialize_future(frame->slots[8] /* check */, frame->slots[10] /* temp__1 */);
  // 429: $possible_value possible_values(idx)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* idx */;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* possible_values */;
  func = myself->type;
  frame->cont = cont__21_284;
}
static void entry__21_276(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // names: 0
  // idx: 1
  // show_usage: 2
  frame->slots[0] = myself->closure.frame->slots[2]; /* names */
  frame->slots[1] = myself->closure.frame->slots[3]; /* idx */
  frame->slots[2] = myself->closure.frame->slots[4]; /* show_usage */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 434: ... names(idx)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* idx */;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* names */;
  func = myself->type;
  frame->cont = cont__21_277;
}
static void cont__21_277(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 434: ... names(idx).to_upper_case
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__to_upper_case();
  func = myself->type;
  frame->cont = cont__21_278;
}
static void cont__21_278(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 434: "Invalid argument value for @(names(idx).to_upper_case)!@nl;"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__21_279;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  arguments->slots[2] = string__21_280;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__21_281;
}
static void cont__21_281(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 433: ewriteln
  // 434:   "Invalid argument value for @(names(idx).to_upper_case)!@nl;"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = 0;
  myself = get__ewriteln();
  func = myself->type;
  frame->cont = cont__21_282;
}
static void cont__21_282(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 435: show_usage
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = frame->slots[2] /* show_usage */;
  func = myself->type;
  frame->cont = cont__21_283;
}
static void cont__21_283(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 436: exit 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = frame->caller_result_count;
  myself = get__exit();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__21_274_check(void) {
  allocate_initialized_frame_gc(5, 7);
  // slot allocations:
  // value: 0
  // possible_value: 1
  // names: 2
  // idx: 3
  // show_usage: 4
  frame->slots[1] = myself->closure.frame->slots[7]; /* possible_value */
  frame->slots[2] = myself->closure.frame->slots[2]; /* names */
  frame->slots[3] = myself->closure.frame->slots[1]; /* idx */
  frame->slots[4] = myself->closure.frame->slots[3]; /* show_usage */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 432: ... possible_value(value)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* value */;
  result_count = 1;
  myself = frame->slots[1] /* possible_value */;
  func = myself->type;
  frame->cont = cont__21_275;
}
static void cont__21_275(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 432: ... :
  // 433:   ewriteln
  // 434:     "Invalid argument value for @(names(idx).to_upper_case)!@nl;"
  // 435:   show_usage
  // 436:   exit 1
  frame->slots[6] /* temp__2 */ = create_closure(entry__21_276, 0);
  // 432: unless possible_value(value):
  // 433:   ewriteln
  // 434:     "Invalid argument value for @(names(idx).to_upper_case)!@nl;"
  // 435:   show_usage
  // 436:   exit 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__21_284(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[7] /* possible_value */, arguments->slots[0]);
  // 438: ... possible_value.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* possible_value */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__21_285;
}
static void cont__21_285(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__1 */ = arguments->slots[0];
  // 438: ... :
  // 439:   if
  // 440:     result.is_a_list:
  // 441:       for_each result: (item) check item
  // 442:     :
  // 443:       check result
  frame->slots[11] /* temp__2 */ = create_closure(entry__21_286, 0);
  // 438: if possible_value.is_defined:
  // 439:   if
  // 440:     result.is_a_list:
  // 441:       for_each result: (item) check item
  // 442:     :
  // 443:       check result
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__1 */;
  arguments->slots[1] = frame->slots[11] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__21_291;
}
static void entry__21_289(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // item: 0
  // check: 1
  frame->slots[1] = myself->closure.frame->slots[1]; /* check */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 441: ... check item
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* item */;
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* check */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__21_288(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // result: 0
  // check: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* result */
  frame->slots[1] = myself->closure.frame->slots[1]; /* check */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 441: ... : (item) check item
  frame->slots[2] /* temp__1 */ = create_closure(entry__21_289, 1);
  // 441: for_each result: (item) check item
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* result */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__21_290(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // check: 0
  // result: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* check */
  frame->slots[1] = myself->closure.frame->slots[0]; /* result */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 443: check result
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* result */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* check */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__21_286(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // result: 0
  // check: 1
  frame->slots[0] = myself->closure.frame->slots[4]; /* result */
  frame->slots[1] = myself->closure.frame->slots[8]; /* check */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 440: result.is_a_list
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* result */;
  result_count = 1;
  myself = get__is_a_list();
  func = myself->type;
  frame->cont = cont__21_287;
}
static void cont__21_287(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 440: ... :
  // 441:   for_each result: (item) check item
  frame->slots[3] /* temp__2 */ = create_closure(entry__21_288, 0);
  // 442: :
  // 443:   check result
  frame->slots[4] /* temp__3 */ = create_closure(entry__21_290, 0);
  // 439: if
  // 440:   result.is_a_list:
  // 441:     for_each result: (item) check item
  // 442:   :
  // 443:     check result
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
static void cont__21_291(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 444: $conversion conversions(idx)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* idx */;
  result_count = 1;
  myself = ((CELL *)frame->slots[5])->contents /* conversions */;
  func = myself->type;
  frame->cont = cont__21_292;
}
static void cont__21_292(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[9] /* conversion */, arguments->slots[0]);
  // 445: ... conversion.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* conversion */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__21_293;
}
static void cont__21_293(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__1 */ = arguments->slots[0];
  // 445: ... :
  // 446:   if
  // 447:     result.is_a_list:
  // 448:       $$new_result empty_list
  // 449:       for_each result: (item) push &new_result conversion(item)
  // 450:       !results(idx) new_result
  // 451:     :
  // 452:       !results(idx) conversion(result)
  frame->slots[11] /* temp__2 */ = create_closure(entry__21_294, 0);
  // 445: if conversion.is_defined:
  // 446:   if
  // 447:     result.is_a_list:
  // 448:       $$new_result empty_list
  // 449:       for_each result: (item) push &new_result conversion(item)
  // 450:       !results(idx) new_result
  // 451:     :
  // 452:       !results(idx) conversion(result)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__1 */;
  arguments->slots[1] = frame->slots[11] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__21_264(void) {
  allocate_initialized_frame_gc(8, 13);
  // slot allocations:
  // idx: 0
  // result: 1
  // default_values: 2
  // results: 3
  // possible_values: 4
  // names: 5
  // show_usage: 6
  // conversions: 7
  frame->slots[2] = myself->closure.frame->slots[9]; /* default_values */
  frame->slots[3] = myself->closure.frame->slots[3]; /* results */
  frame->slots[4] = myself->closure.frame->slots[8]; /* possible_values */
  frame->slots[5] = myself->closure.frame->slots[6]; /* names */
  frame->slots[6] = myself->closure.frame->slots[14]; /* show_usage */
  frame->slots[7] = myself->closure.frame->slots[10]; /* conversions */
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 426: result.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* result */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__21_265;
}
static void cont__21_265(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__2 */ = arguments->slots[0];
  // 426: ... default_values(idx).is_defined
  frame->slots[10] /* temp__3 */ = create_closure(entry__21_266, 0);
  // 426: result.is_undefined && default_values(idx).is_defined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__2 */;
  arguments->slots[1] = frame->slots[10] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__21_269;
}
static void entry__21_266(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // default_values: 0
  // idx: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* default_values */
  frame->slots[1] = myself->closure.frame->slots[0]; /* idx */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 426: ... default_values(idx)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* idx */;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* default_values */;
  func = myself->type;
  frame->cont = cont__21_267;
}
static void cont__21_267(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 426: ... default_values(idx).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__21_268;
}
static void cont__21_268(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 426: ... default_values(idx).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__21_269(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__1 */ = arguments->slots[0];
  // 426: ... :
  // 427:   !results(idx) default_values(idx)
  frame->slots[11] /* temp__4 */ = create_closure(entry__21_270, 0);
  // 428: :
  // 429:   $possible_value possible_values(idx)
  // 430:   
  // 431:   $check: (value)
  // 432:     unless possible_value(value):
  // 433:       ewriteln
  // 434:         "Invalid argument value for @(names(idx).to_upper_case)!@nl;"
  // 435:       show_usage
  // 436:       exit 1
  // 437:   
  // ...
  frame->slots[12] /* temp__5 */ = create_closure(entry__21_273, 0);
  // 425: if
  // 426:   result.is_undefined && default_values(idx).is_defined:
  // 427:     !results(idx) default_values(idx)
  // 428:   :
  // 429:     $possible_value possible_values(idx)
  // 430:     
  // 431:     $check: (value)
  // 432:       unless possible_value(value):
  // 433:         ewriteln
  // 434:           "Invalid argument value for @(names(idx).to_upper_case)!@nl;"
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__1 */;
  arguments->slots[1] = frame->slots[11] /* temp__4 */;
  arguments->slots[2] = frame->slots[12] /* temp__5 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__21_305(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 453: -> results*
  argument_count = 0;
  arguments = node_p;
  unfold(((CELL *)frame->slots[3])->contents /* results */);
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__22_1_std__program_commands(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // commands: 0
  // command_ids: 1
  frame->slots[1] /* command_ids */ = create_cell();
  frame->slots[0] /* commands */ = from_arguments(0, argument_count-0);
  // 456: $$command_ids empty_list
  ((CELL *)frame->slots[1])->contents /* command_ids */ = get__empty_list();
  // 457: ... : (command)
  // 458:   $name key_of(command)
  // 459:   $description value_of(command)
  // 460:   push &command_names name
  // 461:   push &command_descriptions description
  // 462:   inc &command_id_count
  // 463:   push &command_ids command_id_count
  frame->slots[2] /* temp__1 */ = create_closure(entry__22_2, 1);
  // 457: for_each commands: (command)
  // 458:   $name key_of(command)
  // 459:   $description value_of(command)
  // 460:   push &command_names name
  // 461:   push &command_descriptions description
  // 462:   inc &command_id_count
  // 463:   push &command_ids command_id_count
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* commands */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__22_9;
}
static void entry__22_2(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // command: 0
  // command_ids: 1
  // name: 2
  // description: 3
  frame->slots[1] = myself->closure.frame->slots[1]; /* command_ids */
  frame->slots[2] /* name */ = create_future();
  frame->slots[3] /* description */ = create_future();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 458: $name key_of(command)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* command */;
  result_count = 1;
  myself = get__key_of();
  func = myself->type;
  frame->cont = cont__22_3;
}
static void cont__22_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* name */, arguments->slots[0]);
  // 459: $description value_of(command)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* command */;
  result_count = 1;
  myself = get__value_of();
  func = myself->type;
  frame->cont = cont__22_4;
}
static void cont__22_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* description */, arguments->slots[0]);
  // 460: push &command_names name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._command_names;
  arguments->slots[1] = frame->slots[2] /* name */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__22_5;
}
static void cont__22_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._command_names = arguments->slots[0];
  // 461: push &command_descriptions description
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._command_descriptions;
  arguments->slots[1] = frame->slots[3] /* description */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__22_6;
}
static void cont__22_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._command_descriptions = arguments->slots[0];
  // 462: inc &command_id_count
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._command_id_count;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__22_7;
}
static void cont__22_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._command_id_count = arguments->slots[0];
  // 463: push &command_ids command_id_count
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* command_ids */;
  arguments->slots[1] = var._command_id_count;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__22_8;
}
static void cont__22_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* command_ids */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__22_9(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 464: -> command_ids*
  argument_count = 0;
  arguments = node_p;
  unfold(((CELL *)frame->slots[1])->contents /* command_ids */);
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__23_33(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // templates: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* templates */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 483: ... list(undefined)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__23_34;
}
static void cont__23_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 483: ... length_of(templates)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* templates */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__23_35;
}
static void cont__23_35(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 483: ... dup(list(undefined) length_of(templates))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__dup();
  func = myself->type;
  frame->cont = cont__23_36;
}
static void cont__23_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 483: ... -> dup(list(undefined) length_of(templates))*
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[1] /* temp__1 */);
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__23_29(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // id: 0
  // command: 1
  // templates: 2
  frame->slots[0] = myself->closure.frame->slots[1]; /* id */
  frame->slots[1] = myself->closure.frame->slots[0]; /* command */
  frame->slots[2] = myself->closure.frame->slots[2]; /* templates */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 481: !command_id id
  var._command_id = frame->slots[0] /* id */;
  // 482: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__23_30;
}
static void cont__23_30(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 482: ... range(command_line_arguments 2 -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__command_line_arguments();
  arguments->slots[1] = number__2;
  arguments->slots[2] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__23_31;
}
static void cont__23_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 482: check_arguments command range(command_line_arguments 2 -1) templates
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* command */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  arguments->slots[2] = frame->slots[2] /* templates */;
  result_count = frame->caller_result_count;
  myself = var._check_arguments;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__23_23(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // id: 0
  // templates: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* id */
  frame->slots[1] = myself->closure.frame->slots[2]; /* templates */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 479: ... command_names(id)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* id */;
  result_count = 1;
  myself = var._command_names;
  func = myself->type;
  frame->cont = cont__23_24;
}
static void cont__23_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 479: ... list("--help")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__21_156;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__23_25;
}
static void cont__23_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 479: check_arguments command_names(id) list("--help") templates
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  arguments->slots[2] = frame->slots[1] /* templates */;
  result_count = frame->caller_result_count;
  myself = var._check_arguments;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__23_10(void) {
  allocate_initialized_frame_gc(3, 7);
  // slot allocations:
  // command: 0
  // id: 1
  // templates: 2
  frame->slots[0] = myself->closure.frame->slots[2]; /* command */
  frame->slots[1] = myself->closure.frame->slots[0]; /* id */
  frame->slots[2] = myself->closure.frame->slots[1]; /* templates */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 475: command == "help"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* command */;
  arguments->slots[1] = string__23_11;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__23_12;
}
static void cont__23_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  frame->slots[5] /* temp__3 */ = create_closure(entry__23_13, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__23_22;
}
static void entry__23_13(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // id: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* id */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 476: length_of(command_line_arguments)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__command_line_arguments();
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__23_14;
}
static void cont__23_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 476: length_of(command_line_arguments) == 2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__23_15;
}
static void cont__23_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 477: command_line_arguments(2).from_utf8 == command_names(id)
  frame->slots[4] /* temp__4 */ = create_closure(entry__23_16, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__4 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__23_21;
}
static void entry__23_16(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // id: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* id */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 477: command_line_arguments(2)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = get__command_line_arguments();
  func = myself->type;
  frame->cont = cont__23_17;
}
static void cont__23_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 477: command_line_arguments(2).from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__from_utf8();
  func = myself->type;
  frame->cont = cont__23_18;
}
static void cont__23_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 477: ... command_names(id)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* id */;
  result_count = 1;
  myself = var._command_names;
  func = myself->type;
  frame->cont = cont__23_19;
}
static void cont__23_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__4 */ = arguments->slots[0];
  // 477: command_line_arguments(2).from_utf8 == command_names(id)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__4 */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__23_20;
}
static void cont__23_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 477: command_line_arguments(2).from_utf8 == command_names(id)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__23_21(void) {
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
static void cont__23_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 478: :
  // 479:   check_arguments command_names(id) list("--help") templates
  frame->slots[6] /* temp__4 */ = create_closure(entry__23_23, 0);
  // 473: ->
  // 474:   &&
  // 475:     command == "help"
  // 476:     length_of(command_line_arguments) == 2
  // 477:     command_line_arguments(2).from_utf8 == command_names(id)
  // 478:   :
  // 479:     check_arguments command_names(id) list("--help") templates
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__4 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__23_26(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // command: 0
  // id: 1
  // templates: 2
  frame->slots[0] = myself->closure.frame->slots[2]; /* command */
  frame->slots[1] = myself->closure.frame->slots[0]; /* id */
  frame->slots[2] = myself->closure.frame->slots[1]; /* templates */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 480: ... command_names(id)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* id */;
  result_count = 1;
  myself = var._command_names;
  func = myself->type;
  frame->cont = cont__23_27;
}
static void cont__23_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 480: ... command == command_names(id)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* command */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__23_28;
}
static void cont__23_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 480: ... :
  // 481:   !command_id id
  // 482:   check_arguments command range(command_line_arguments 2 -1) templates
  frame->slots[5] /* temp__3 */ = create_closure(entry__23_29, 0);
  // 480: -> command == command_names(id):
  // 481:   !command_id id
  // 482:   check_arguments command range(command_line_arguments 2 -1) templates
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__23_32(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // templates: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* templates */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 483: ... -> dup(list(undefined) length_of(templates))*
  frame->slots[1] /* temp__1 */ = create_closure(entry__23_33, 0);
  // 483: -> true -> dup(list(undefined) length_of(templates))*
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__true();
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__23_3(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // templates: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* templates */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 469: ... list(undefined)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__23_4;
}
static void cont__23_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 469: ... length_of(templates)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* templates */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__23_5;
}
static void cont__23_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 469: ... dup(list(undefined) length_of(templates))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__dup();
  func = myself->type;
  frame->cont = cont__23_6;
}
static void cont__23_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 469: -> dup(list(undefined) length_of(templates))*
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[1] /* temp__1 */);
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__23_7(void) {
  allocate_initialized_frame_gc(2, 6);
  // slot allocations:
  // id: 0
  // templates: 1
  // command: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* id */
  frame->slots[1] = myself->closure.frame->slots[1]; /* templates */
  frame->slots[2] /* command */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 471: ... command_line_arguments(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__command_line_arguments();
  func = myself->type;
  frame->cont = cont__23_8;
}
static void cont__23_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 471: $command command_line_arguments(1).from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__from_utf8();
  func = myself->type;
  frame->cont = cont__23_9;
}
static void cont__23_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* command */, arguments->slots[0]);
  // 473: ->
  // 474:   &&
  // 475:     command == "help"
  // 476:     length_of(command_line_arguments) == 2
  // 477:     command_line_arguments(2).from_utf8 == command_names(id)
  // 478:   :
  // 479:     check_arguments command_names(id) list("--help") templates
  frame->slots[3] /* temp__1 */ = create_closure(entry__23_10, 0);
  // 480: -> command == command_names(id):
  // 481:   !command_id id
  // 482:   check_arguments command range(command_line_arguments 2 -1) templates
  frame->slots[4] /* temp__2 */ = create_closure(entry__23_26, 0);
  // 483: -> true -> dup(list(undefined) length_of(templates))*
  frame->slots[5] /* temp__3 */ = create_closure(entry__23_32, 0);
  // 472: cond
  // 473:   ->
  // 474:     &&
  // 475:       command == "help"
  // 476:       length_of(command_line_arguments) == 2
  // 477:       command_line_arguments(2).from_utf8 == command_names(id)
  // 478:     :
  // 479:       check_arguments command_names(id) list("--help") templates
  // 480:   -> command == command_names(id):
  // 481:     !command_id id
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  arguments->slots[2] = frame->slots[5] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__cond();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__23_1_std__command_parameters(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // id: 0
  // templates: 1
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  frame->slots[0] /* id */ = arguments->slots[0];
  frame->slots[1] /* templates */ = from_arguments(1, argument_count-1);
  // 468: command_line_arguments.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__command_line_arguments();
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__23_2;
}
static void cont__23_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 469: -> dup(list(undefined) length_of(templates))*
  frame->slots[3] /* temp__2 */ = create_closure(entry__23_3, 0);
  // 470: :
  // 471:   $command command_line_arguments(1).from_utf8
  // 472:   cond
  // 473:     ->
  // 474:       &&
  // 475:         command == "help"
  // 476:         length_of(command_line_arguments) == 2
  // 477:         command_line_arguments(2).from_utf8 == command_names(id)
  // 478:       :
  // 479:         check_arguments command_names(id) list("--help") templates
  // ...
  frame->slots[4] /* temp__3 */ = create_closure(entry__23_7, 0);
  // 467: if
  // 468:   command_line_arguments.is_empty
  // 469:   -> dup(list(undefined) length_of(templates))*
  // 470:   :
  // 471:     $command command_line_arguments(1).from_utf8
  // 472:     cond
  // 473:       ->
  // 474:         &&
  // 475:           command == "help"
  // 476:           length_of(command_line_arguments) == 2
  // ...
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
static void entry__24_1_show_commands(void) {
  allocate_initialized_frame_gc(0, 3);
  // slot allocations:
  // tab: 0
  frame->slots[0] /* tab */ = create_cell();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 486: ... program_version.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._program_version;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__24_2;
}
static void cont__24_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 486: if program_version.is_defined:
  // 487:   show_version truncate_until(program_name '/' -1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = func__24_3;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__24_6;
}
static void entry__24_3(void) {
  allocate_initialized_frame_gc(0, 2);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 487: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__24_4;
}
static void cont__24_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 487: ... truncate_until(program_name '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__program_name();
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = get__truncate_until();
  func = myself->type;
  frame->cont = cont__24_5;
}
static void cont__24_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 487: show_version truncate_until(program_name '/' -1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = var._show_version;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__24_6(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 488: ewriteln "Available commands:"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__24_7;
  result_count = 0;
  myself = get__ewriteln();
  func = myself->type;
  frame->cont = cont__24_8;
}
static void cont__24_8(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 489: ... list("help" "display help for the specified command")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__23_11;
  arguments->slots[1] = string__24_9;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__24_10;
}
static void cont__24_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 489: $$tab list(list("help" "display help for the specified command"))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__24_11;
}
static void cont__24_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* tab */ = arguments->slots[0];
  // 490: ... : (idx command_name)
  // 491:   push &tab list(command_name command_descriptions(idx))
  frame->slots[1] /* temp__1 */ = create_closure(entry__24_12, 2);
  // 490: for_each command_names: (idx command_name)
  // 491:   push &tab list(command_name command_descriptions(idx))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._command_names;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__24_16;
}
static void entry__24_12(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // idx: 0
  // command_name: 1
  // tab: 2
  frame->slots[2] = myself->closure.frame->slots[0]; /* tab */
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 491: ... command_descriptions(idx)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* idx */;
  result_count = 1;
  myself = var._command_descriptions;
  func = myself->type;
  frame->cont = cont__24_13;
}
static void cont__24_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 491: ... list(command_name command_descriptions(idx))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* command_name */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__24_14;
}
static void cont__24_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 491: push &tab list(command_name command_descriptions(idx))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* tab */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__24_15;
}
static void cont__24_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* tab */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__24_16(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 492: ... program_copyright.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._program_copyright;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__24_17;
}
static void cont__24_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 492: ... :
  // 493:   push &tab list("copyright" "display the copyright message")
  frame->slots[2] /* temp__2 */ = create_closure(entry__24_18, 0);
  // 492: if program_copyright.is_defined:
  // 493:   push &tab list("copyright" "display the copyright message")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__24_23;
}
static void entry__24_18(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // tab: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* tab */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 493: ... list("copyright" "display the copyright message")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__24_19;
  arguments->slots[1] = string__24_20;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__24_21;
}
static void cont__24_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 493: push &tab list("copyright" "display the copyright message")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* tab */;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__24_22;
}
static void cont__24_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* tab */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__24_23(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 494: ... program_version.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._program_version;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__24_24;
}
static void cont__24_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 494: ... :
  // 495:   push &tab list("version" "display the version number")
  frame->slots[2] /* temp__2 */ = create_closure(entry__24_25, 0);
  // 494: if program_version.is_defined:
  // 495:   push &tab list("version" "display the version number")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__24_30;
}
static void entry__24_25(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // tab: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* tab */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 495: ... list("version" "display the version number")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__24_26;
  arguments->slots[1] = string__24_27;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__24_28;
}
static void cont__24_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 495: push &tab list("version" "display the version number")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* tab */;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__24_29;
}
static void cont__24_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* tab */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__24_30(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 496: display_table tab
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* tab */;
  result_count = frame->caller_result_count;
  myself = var._display_table;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__25_9(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 596: ewriteln "
  // 597:   No command specified!
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__25_10;
  result_count = 0;
  myself = get__ewriteln();
  func = myself->type;
  frame->cont = cont__25_11;
}
static void cont__25_11(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 598: show_commands
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = var._show_commands;
  func = myself->type;
  frame->cont = cont__25_12;
}
static void cont__25_12(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 599: exit 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = frame->caller_result_count;
  myself = get__exit();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__25_13(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 602: command_line_arguments(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__command_line_arguments();
  func = myself->type;
  frame->cont = cont__25_14;
}
static void cont__25_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 601: case
  // 602:   command_line_arguments(1)
  // 603:   "copyright":
  // 604:     if program_copyright.is_defined:
  // 605:       show_copyright
  // 606:       terminate
  // 607:   "help":
  // 608:     case
  // 609:       length_of(command_line_arguments)
  // 610:       1:
  // ...
  argument_count = 7;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = string__24_19;
  arguments->slots[2] = func__25_15;
  arguments->slots[3] = string__23_11;
  arguments->slots[4] = func__25_19;
  arguments->slots[5] = string__24_26;
  arguments->slots[6] = func__25_45;
  result_count = 0;
  myself = get__case();
  func = myself->type;
  frame->cont = cont__25_51;
}
static void entry__25_47(void) {
  allocate_initialized_frame_gc(0, 2);
  // slot allocations:
  // command_name: 0
  frame->slots[0] /* command_name */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 647: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__25_48;
}
static void cont__25_48(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 647: $command_name truncate_until(program_name '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__program_name();
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__truncate_until();
  func = myself->type;
  frame->cont = cont__25_49;
}
static void cont__25_49(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[0] /* command_name */, arguments->slots[0]);
  // 648: show_version command_name
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* command_name */;
  result_count = 0;
  myself = var._show_version;
  func = myself->type;
  frame->cont = cont__25_50;
}
static void cont__25_50(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 649: terminate
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = get__terminate();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__25_21(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 611: show_commands
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = var._show_commands;
  func = myself->type;
  frame->cont = cont__25_22;
}
static void cont__25_22(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 612: terminate
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = get__terminate();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__25_23(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 615: command_line_arguments(2)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = get__command_line_arguments();
  func = myself->type;
  frame->cont = cont__25_24;
}
static void cont__25_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 614: case
  // 615:   command_line_arguments(2)
  // 616:   "copyright":
  // 617:     if program_copyright.is_defined:
  // 618:       ewrite "
  // 619:         Usage:
  // 620:           sigi copyright
  // 621:       terminate
  // 622:   "help":
  // 623:     ewrite "
  // ...
  argument_count = 7;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = string__24_19;
  arguments->slots[2] = func__25_25;
  arguments->slots[3] = string__23_11;
  arguments->slots[4] = func__25_30;
  arguments->slots[5] = string__24_26;
  arguments->slots[6] = func__25_33;
  result_count = 0;
  myself = get__case();
  func = myself->type;
  frame->cont = cont__25_38;
}
static void entry__25_35(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 632: ewrite "
  // 633:   Usage:
  // 634:     sigi version
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__25_36;
  result_count = 0;
  myself = get__ewrite();
  func = myself->type;
  frame->cont = cont__25_37;
}
static void cont__25_37(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 635: terminate
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = get__terminate();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__25_27(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 618: ewrite "
  // 619:   Usage:
  // 620:     sigi copyright
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__25_28;
  result_count = 0;
  myself = get__ewrite();
  func = myself->type;
  frame->cont = cont__25_29;
}
static void cont__25_29(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 621: terminate
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = get__terminate();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__25_25(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 617: ... program_copyright.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._program_copyright;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__25_26;
}
static void cont__25_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 617: if program_copyright.is_defined:
  // 618:   ewrite "
  // 619:     Usage:
  // 620:       sigi copyright
  // 621:   terminate
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = func__25_27;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__25_30(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 623: ewrite "
  // 624:   Usage:
  // 625:     sigi help COMMAND
  // 626:   
  // 627:   Parameter:
  // 628:     COMMAND  the command for which to retrieve help
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__25_31;
  result_count = 0;
  myself = get__ewrite();
  func = myself->type;
  frame->cont = cont__25_32;
}
static void cont__25_32(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 629: terminate
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = get__terminate();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__25_33(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 631: ... program_version.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._program_version;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__25_34;
}
static void cont__25_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 631: if program_version.is_defined:
  // 632:   ewrite "
  // 633:     Usage:
  // 634:       sigi version
  // 635:   terminate
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = func__25_35;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__25_38(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 636: ewriteln "
  // 637:   Invalid command name!
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__25_39;
  result_count = 0;
  myself = get__ewriteln();
  func = myself->type;
  frame->cont = cont__25_40;
}
static void cont__25_40(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 638: show_commands
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = var._show_commands;
  func = myself->type;
  frame->cont = cont__25_41;
}
static void cont__25_41(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 639: exit 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = frame->caller_result_count;
  myself = get__exit();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__25_42(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 641: ewriteln "
  // 642:   Too many arguments!
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__21_98;
  result_count = 0;
  myself = get__ewriteln();
  func = myself->type;
  frame->cont = cont__25_43;
}
static void cont__25_43(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 643: show_commands
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = var._show_commands;
  func = myself->type;
  frame->cont = cont__25_44;
}
static void cont__25_44(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 644: exit 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = frame->caller_result_count;
  myself = get__exit();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__25_17(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 605: show_copyright
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = var._show_copyright;
  func = myself->type;
  frame->cont = cont__25_18;
}
static void cont__25_18(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 606: terminate
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = get__terminate();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__25_15(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 604: ... program_copyright.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._program_copyright;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__25_16;
}
static void cont__25_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 604: if program_copyright.is_defined:
  // 605:   show_copyright
  // 606:   terminate
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = func__25_17;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__25_19(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 609: length_of(command_line_arguments)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__command_line_arguments();
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__25_20;
}
static void cont__25_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 608: case
  // 609:   length_of(command_line_arguments)
  // 610:   1:
  // 611:     show_commands
  // 612:     terminate
  // 613:   2:
  // 614:     case
  // 615:       command_line_arguments(2)
  // 616:       "copyright":
  // 617:         if program_copyright.is_defined:
  // ...
  argument_count = 6;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = func__25_21;
  arguments->slots[3] = number__2;
  arguments->slots[4] = func__25_23;
  arguments->slots[5] = func__25_42;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__25_45(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 646: ... program_version.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._program_version;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__25_46;
}
static void cont__25_46(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 646: if program_version.is_defined:
  // 647:   $command_name truncate_until(program_name '/' -1)
  // 648:   show_version command_name
  // 649:   terminate
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = func__25_47;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__25_51(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 650: ewriteln "
  // 651:   Invalid arguments!
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__25_52;
  result_count = 0;
  myself = get__ewriteln();
  func = myself->type;
  frame->cont = cont__25_53;
}
static void cont__25_53(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 652: show_commands
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = var._show_commands;
  func = myself->type;
  frame->cont = cont__25_54;
}
static void cont__25_54(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 653: exit 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = frame->caller_result_count;
  myself = get__exit();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__25_6(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 593: ... -> command_id
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._command_id;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__25_7(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 595: command_line_arguments.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__command_line_arguments();
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__25_8;
}
static void cont__25_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 594: if
  // 595:   command_line_arguments.is_empty:
  // 596:     ewriteln "
  // 597:       No command specified!
  // 598:     show_commands
  // 599:     exit 1
  // 600:   :
  // 601:     case
  // 602:       command_line_arguments(1)
  // 603:       "copyright":
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = func__25_9;
  arguments->slots[2] = func__25_13;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__25_3(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // templates: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* templates */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 655: check_arguments command_line_arguments templates
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__command_line_arguments();
  arguments->slots[1] = frame->slots[0] /* templates */;
  result_count = frame->caller_result_count;
  myself = var._check_arguments;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__25_4(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 593: ... command_id.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._command_id;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__25_5;
}
static void cont__25_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 593: if command_id.is_defined (-> command_id):
  // 594:   if
  // 595:     command_line_arguments.is_empty:
  // 596:       ewriteln "
  // 597:         No command specified!
  // 598:       show_commands
  // 599:       exit 1
  // 600:     :
  // 601:       case
  // 602:         command_line_arguments(1)
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = func__25_6;
  arguments->slots[2] = func__25_7;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__25_1_std__program_parameters(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // templates: 0
  frame->slots[0] /* templates */ = from_arguments(0, argument_count-0);
  // 592: command_id_count > 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = var._command_id_count;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__25_2;
}
static void cont__25_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 654: :
  // 655:   check_arguments command_line_arguments templates
  frame->slots[2] /* temp__2 */ = create_closure(entry__25_3, 0);
  // 591: if
  // 592:   command_id_count > 0:
  // 593:     if command_id.is_defined (-> command_id):
  // 594:       if
  // 595:         command_line_arguments.is_empty:
  // 596:           ewriteln "
  // 597:             No command specified!
  // 598:           show_commands
  // 599:           exit 1
  // 600:         :
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = func__25_4;
  arguments->slots[2] = frame->slots[2] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
EXPORT void collect__basic__parameters(void) {
  var._BOOLEAN_OPTION = collect_node(var._BOOLEAN_OPTION);
  var.std__VALUED_OPTION = collect_node(var.std__VALUED_OPTION);
  var.std__MULTI_VALUED_OPTION = collect_node(var.std__MULTI_VALUED_OPTION);
  var.std__MANDATORY_PARAMETER = collect_node(var.std__MANDATORY_PARAMETER);
  var.std__OPTIONAL_PARAMETER = collect_node(var.std__OPTIONAL_PARAMETER);
  var.std__SOME_PARAMETERS = collect_node(var.std__SOME_PARAMETERS);
  var.std__MANY_PARAMETERS = collect_node(var.std__MANY_PARAMETERS);
  var._program_version = collect_node(var._program_version);
  var._program_copyright = collect_node(var._program_copyright);
  var.std__copyright = collect_node(var.std__copyright);
  var.std__version = collect_node(var.std__version);
  var.std__extract_options = collect_node(var.std__extract_options);
  var.std__extract_some_options = collect_node(var.std__extract_some_options);
  var._display_table = collect_node(var._display_table);
  var._command_id = collect_node(var._command_id);
  var._command_id_count = collect_node(var._command_id_count);
  var._command_names = collect_node(var._command_names);
  var._command_descriptions = collect_node(var._command_descriptions);
  var._show_version = collect_node(var._show_version);
  var._show_copyright = collect_node(var._show_copyright);
  var._check_arguments = collect_node(var._check_arguments);
  var.std__program_commands = collect_node(var.std__program_commands);
  var.std__command_parameters = collect_node(var.std__command_parameters);
  var._show_commands = collect_node(var._show_commands);
  var.std__program_parameters = collect_node(var.std__program_parameters);
}

static int already_run_phase_1 = false;

EXPORT void phase_1__basic__parameters(void) {
  if (already_run_phase_1) return;
  already_run_phase_1 = true;
  register_module_info(&module_info);
}

static int already_run_phase_2 = false;

EXPORT void phase_2__basic__parameters(void) {
  if (already_run_phase_2) return;
  already_run_phase_2 = true;
  character__47 = from_uchar32(47);
  character__63 = from_uchar32(63);
  character__10 = from_uchar32(10);
  character__44 = from_uchar32(44);
  number__0 = from_uint32(0U);
  number__3 = from_uint32(3U);
  character__32 = from_uchar32(32);
  character__43 = from_uchar32(43);
  number__1 = from_uint32(1U);
  number__2 = from_uint32(2U);
  character__42 = from_uchar32(42);
  unique__BOOLEAN_OPTION = register_unique_item("BOOLEAN_OPTION");
  unique__std__VALUED_OPTION = register_unique_item("std__VALUED_OPTION");
  unique__std__MULTI_VALUED_OPTION = register_unique_item("std__MULTI_VALUED_OPTION");
  unique__std__MANDATORY_PARAMETER = register_unique_item("std__MANDATORY_PARAMETER");
  unique__std__OPTIONAL_PARAMETER = register_unique_item("std__OPTIONAL_PARAMETER");
  unique__std__SOME_PARAMETERS = register_unique_item("std__SOME_PARAMETERS");
  unique__std__MANY_PARAMETERS = register_unique_item("std__MANY_PARAMETERS");
  func__10_1_std__copyright = create_function(entry__10_1_std__copyright, 1);
  func__11_1_std__version = create_function(entry__11_1_std__version, 1);
  string__12_45 = from_latin_1_string("Invalid option ", 15);
  string__12_46 = from_latin_1_string("!", 1);
  func__12_1_std__extract_options = create_function(entry__12_1_std__extract_options, -1);
  func__13_1_std__extract_some_options = create_function(entry__13_1_std__extract_some_options, -1);
  string__14_11 = from_latin_1_string("  ", 2);
  string__14_19 = from_latin_1_string(" ", 1);
  func__14_1_display_table = create_function(entry__14_1_display_table, 1);
  string__19_2 = from_latin_1_string("\012\012", 2);
  func__19_1_show_version = create_function(entry__19_1_show_version, 1);
  func__20_1_show_copyright = create_function(entry__20_1_show_copyright, 0);
  string__21_7 = from_latin_1_string("valid values:", 13);
  string__21_35 = from_latin_1_string("Usage:", 6);
  string__21_41 = from_latin_1_string(" --copyright", 12);
  string__21_43 = from_latin_1_string(" --help", 7);
  func__21_48 = create_function(entry__21_48, 0);
  string__21_55 = from_latin_1_string("\012Parameters:\012", 13);
  string__21_67 = from_latin_1_string("\012Options:\012", 10);
  string__21_72 = from_latin_1_string("--", 2);
  string__21_76 = from_latin_1_string(" VALUE", 6);
  string__21_79 = from_latin_1_string(" VALUES", 7);
  string__21_90 = from_latin_1_string("Too few arguments for ", 22);
  string__21_91 = from_latin_1_string("-command!\012", 10);
  string__21_94 = from_latin_1_string("Too few arguments!\012", 19);
  func__21_93 = create_function(entry__21_93, 0);
  string__21_98 = from_latin_1_string("Too many arguments!\012", 20);
  string__21_156 = from_latin_1_string("--help", 6);
  string__21_164 = from_latin_1_string("--copyright", 11);
  func__21_167 = create_function(entry__21_167, 0);
  string__21_173 = from_latin_1_string("--version", 9);
  string__21_203 = from_latin_1_string("Invalid option: ", 16);
  string__21_279 = from_latin_1_string("Invalid argument value for ", 27);
  string__21_280 = from_latin_1_string("!\012", 2);
  func__21_1_check_arguments = create_function(entry__21_1_check_arguments, -1);
  func__22_1_std__program_commands = create_function(entry__22_1_std__program_commands, -1);
  string__23_11 = from_latin_1_string("help", 4);
  func__23_1_std__command_parameters = create_function(entry__23_1_std__command_parameters, -1);
  func__24_3 = create_function(entry__24_3, 0);
  string__24_7 = from_latin_1_string("Available commands:", 19);
  string__24_9 = from_latin_1_string("display help for the specified command", 38);
  string__24_19 = from_latin_1_string("copyright", 9);
  string__24_20 = from_latin_1_string("display the copyright message", 29);
  string__24_26 = from_latin_1_string("version", 7);
  string__24_27 = from_latin_1_string("display the version number", 26);
  func__24_1_show_commands = create_function(entry__24_1_show_commands, 0);
  func__25_6 = create_function(entry__25_6, 0);
  string__25_10 = from_latin_1_string("No command specified!\012", 22);
  func__25_9 = create_function(entry__25_9, 0);
  func__25_17 = create_function(entry__25_17, 0);
  func__25_15 = create_function(entry__25_15, 0);
  func__25_21 = create_function(entry__25_21, 0);
  string__25_28 = from_latin_1_string("Usage:\012  sigi copyright\012", 24);
  func__25_27 = create_function(entry__25_27, 0);
  func__25_25 = create_function(entry__25_25, 0);
  string__25_31 = from_latin_1_string("Usage:\012  sigi help COMMAND\012\012Parameter:\012  COMMAND  the command for which to retrieve help\012", 89);
  func__25_30 = create_function(entry__25_30, 0);
  string__25_36 = from_latin_1_string("Usage:\012  sigi version\012", 22);
  func__25_35 = create_function(entry__25_35, 0);
  func__25_33 = create_function(entry__25_33, 0);
  string__25_39 = from_latin_1_string("Invalid command name!\012", 22);
  func__25_23 = create_function(entry__25_23, 0);
  func__25_42 = create_function(entry__25_42, 0);
  func__25_19 = create_function(entry__25_19, 0);
  func__25_47 = create_function(entry__25_47, 0);
  func__25_45 = create_function(entry__25_45, 0);
  string__25_52 = from_latin_1_string("Invalid arguments!\012", 19);
  func__25_13 = create_function(entry__25_13, 0);
  func__25_7 = create_function(entry__25_7, 0);
  func__25_4 = create_function(entry__25_4, 0);
  func__25_1_std__program_parameters = create_function(entry__25_1_std__program_parameters, -1);
}

static int already_run_phase_3 = false;

EXPORT void phase_3__basic__parameters(void) {
  if (already_run_phase_3) return;
  already_run_phase_3 = true;
  set_module("basic__parameters");
  set_used_namespaces(used_namespaces);
  assign_value(&var._BOOLEAN_OPTION, unique__BOOLEAN_OPTION);
  assign_value(&var.std__VALUED_OPTION, unique__std__VALUED_OPTION);
  define_single_assign_static("std", "VALUED_OPTION", get__std__VALUED_OPTION, &var.std__VALUED_OPTION);
  assign_value(&var.std__MULTI_VALUED_OPTION, unique__std__MULTI_VALUED_OPTION);
  define_single_assign_static("std", "MULTI_VALUED_OPTION", get__std__MULTI_VALUED_OPTION, &var.std__MULTI_VALUED_OPTION);
  assign_value(&var.std__MANDATORY_PARAMETER, unique__std__MANDATORY_PARAMETER);
  define_single_assign_static("std", "MANDATORY_PARAMETER", get__std__MANDATORY_PARAMETER, &var.std__MANDATORY_PARAMETER);
  assign_value(&var.std__OPTIONAL_PARAMETER, unique__std__OPTIONAL_PARAMETER);
  define_single_assign_static("std", "OPTIONAL_PARAMETER", get__std__OPTIONAL_PARAMETER, &var.std__OPTIONAL_PARAMETER);
  assign_value(&var.std__SOME_PARAMETERS, unique__std__SOME_PARAMETERS);
  define_single_assign_static("std", "SOME_PARAMETERS", get__std__SOME_PARAMETERS, &var.std__SOME_PARAMETERS);
  assign_value(&var.std__MANY_PARAMETERS, unique__std__MANY_PARAMETERS);
  define_single_assign_static("std", "MANY_PARAMETERS", get__std__MANY_PARAMETERS, &var.std__MANY_PARAMETERS);
  define_single_assign_static("std", "copyright", get__std__copyright, &var.std__copyright);
  define_single_assign_static("std", "version", get__std__version, &var.std__version);
  define_single_assign_static("std", "extract_options", get__std__extract_options, &var.std__extract_options);
  define_single_assign_static("std", "extract_some_options", get__std__extract_some_options, &var.std__extract_some_options);
  define_single_assign_static("std", "program_commands", get__std__program_commands, &var.std__program_commands);
  define_single_assign_static("std", "command_parameters", get__std__command_parameters, &var.std__command_parameters);
  define_single_assign_static("std", "program_parameters", get__std__program_parameters, &var.std__program_parameters);
}

static int already_run_phase_4 = false;

EXPORT void phase_4__basic__parameters(void) {
  if (already_run_phase_4) return;
  already_run_phase_4 = true;
  set_module("basic__parameters");
  set_used_namespaces(used_namespaces);
  use_read_only(NULL, "Error", &get__Error, &get_value_or_future__Error);
  use_read_only(NULL, "MANDATORY_PARAMETER", &get__MANDATORY_PARAMETER, &get_value_or_future__MANDATORY_PARAMETER);
  use_read_only(NULL, "MANY_PARAMETERS", &get__MANY_PARAMETERS, &get_value_or_future__MANY_PARAMETERS);
  use_read_only(NULL, "MULTI_VALUED_OPTION", &get__MULTI_VALUED_OPTION, &get_value_or_future__MULTI_VALUED_OPTION);
  use_read_only(NULL, "OPTIONAL_PARAMETER", &get__OPTIONAL_PARAMETER, &get_value_or_future__OPTIONAL_PARAMETER);
  use_read_only(NULL, "SOME_PARAMETERS", &get__SOME_PARAMETERS, &get_value_or_future__SOME_PARAMETERS);
  use_read_only(NULL, "VALUED_OPTION", &get__VALUED_OPTION, &get_value_or_future__VALUED_OPTION);
  use_read_only(NULL, "append", &get__append, &get_value_or_future__append);
  use_read_only(NULL, "case", &get__case, &get_value_or_future__case);
  use_read_only(NULL, "command_line_arguments", &get__command_line_arguments, &get_value_or_future__command_line_arguments);
  use_read_only(NULL, "cond", &get__cond, &get_value_or_future__cond);
  use_read_only(NULL, "debug_string", &get__debug_string, &get_value_or_future__debug_string);
  use_read_only(NULL, "delete_at", &get__delete_at, &get_value_or_future__delete_at);
  use_read_only(NULL, "do", &get__do, &get_value_or_future__do);
  use_read_only(NULL, "dup", &get__dup, &get_value_or_future__dup);
  use_read_only(NULL, "empty_insert_order_table", &get__empty_insert_order_table, &get_value_or_future__empty_insert_order_table);
  use_read_only(NULL, "empty_key_order_table", &get__empty_key_order_table, &get_value_or_future__empty_key_order_table);
  use_read_only(NULL, "empty_list", &get__empty_list, &get_value_or_future__empty_list);
  use_read_only(NULL, "ewrite", &get__ewrite, &get_value_or_future__ewrite);
  use_read_only(NULL, "ewriteln", &get__ewriteln, &get_value_or_future__ewriteln);
  use_read_only(NULL, "exit", &get__exit, &get_value_or_future__exit);
  use_read_only(NULL, "extend_to", &get__extend_to, &get_value_or_future__extend_to);
  use_read_only(NULL, "false", &get__false, &get_value_or_future__false);
  use_read_only(NULL, "for_each", &get__for_each, &get_value_or_future__for_each);
  use_read_only(NULL, "for_each_from_down_to", &get__for_each_from_down_to, &get_value_or_future__for_each_from_down_to);
  use_read_only(NULL, "for_each_from_to", &get__for_each_from_to, &get_value_or_future__for_each_from_to);
  use_read_only(NULL, "for_each_line", &get__for_each_line, &get_value_or_future__for_each_line);
  use_read_only(NULL, "from_utf8", &get__from_utf8, &get_value_or_future__from_utf8);
  use_read_only(NULL, "get", &get__get, &get_value_or_future__get);
  use_read_only(NULL, "has_prefix", &get__has_prefix, &get_value_or_future__has_prefix);
  use_read_only(NULL, "if", &get__if, &get_value_or_future__if);
  use_read_only(NULL, "inc", &get__inc, &get_value_or_future__inc);
  use_read_only(NULL, "indented", &get__indented, &get_value_or_future__indented);
  use_read_only(NULL, "is_a_key_value_pair", &get__is_a_key_value_pair, &get_value_or_future__is_a_key_value_pair);
  use_read_only(NULL, "is_a_list", &get__is_a_list, &get_value_or_future__is_a_list);
  use_read_only(NULL, "is_a_string", &get__is_a_string, &get_value_or_future__is_a_string);
  use_read_only(NULL, "is_defined", &get__is_defined, &get_value_or_future__is_defined);
  use_read_only(NULL, "is_empty", &get__is_empty, &get_value_or_future__is_empty);
  use_read_only(NULL, "is_undefined", &get__is_undefined, &get_value_or_future__is_undefined);
  use_read_only(NULL, "key_of", &get__key_of, &get_value_or_future__key_of);
  use_read_only(NULL, "length_of", &get__length_of, &get_value_or_future__length_of);
  use_read_only(NULL, "list", &get__list, &get_value_or_future__list);
  use_read_only(NULL, "map", &get__map, &get_value_or_future__map);
  use_read_only(NULL, "pad_right", &get__pad_right, &get_value_or_future__pad_right);
  use_read_only(NULL, "plus", &get__plus, &get_value_or_future__plus);
  use_read_only(NULL, "pop", &get__pop, &get_value_or_future__pop);
  use_read_only(NULL, "program_name", &get__program_name, &get_value_or_future__program_name);
  use_read_only(NULL, "push", &get__push, &get_value_or_future__push);
  use_read_only(NULL, "range", &get__range, &get_value_or_future__range);
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
  use_read_only(NULL, "string", &get__string, &get_value_or_future__string);
  use_read_only(NULL, "terminate", &get__terminate, &get_value_or_future__terminate);
  use_read_only(NULL, "to_upper_case", &get__to_upper_case, &get_value_or_future__to_upper_case);
  use_read_only(NULL, "true", &get__true, &get_value_or_future__true);
  use_read_only(NULL, "truncate_until", &get__truncate_until, &get_value_or_future__truncate_until);
  use_read_only(NULL, "undefined", &get__undefined, &get_value_or_future__undefined);
  use_read_only(NULL, "unless", &get__unless, &get_value_or_future__unless);
  use_read_only(NULL, "value_of", &get__value_of, &get_value_or_future__value_of);
  use_read_only(NULL, "write_to", &get__write_to, &get_value_or_future__write_to);
}

static int already_run_phase_5 = false;

EXPORT void phase_5__basic__parameters(void) {
  if (already_run_phase_5) return;
  already_run_phase_5 = true;
  assign_variable(&var.std__copyright, &func__10_1_std__copyright);
  assign_variable(&var.std__version, &func__11_1_std__version);
  assign_variable(&var.std__extract_options, &func__12_1_std__extract_options);
  assign_variable(&var.std__extract_some_options, &func__13_1_std__extract_some_options);
  assign_variable(&var._display_table, &func__14_1_display_table);
  assign_variable(&var._show_version, &func__19_1_show_version);
  assign_variable(&var._show_copyright, &func__20_1_show_copyright);
  assign_variable(&var._check_arguments, &func__21_1_check_arguments);
  assign_variable(&var.std__program_commands, &func__22_1_std__program_commands);
  assign_variable(&var.std__command_parameters, &func__23_1_std__command_parameters);
  assign_variable(&var._show_commands, &func__24_1_show_commands);
  assign_variable(&var.std__program_parameters, &func__25_1_std__program_parameters);
}

static int already_run_phase_6 = false;

EXPORT void phase_6__basic__parameters(void) {
  if (already_run_phase_6) return;
  already_run_phase_6 = true;
  register_collector(collect__basic__parameters);
}
