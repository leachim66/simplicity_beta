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
IMPORT void set_module(const char *name);
IMPORT void set_used_namespaces(const char **namespaces);
IMPORT NODE *register_unique_item(const char *name);
IMPORT void assign_value(NODE **dest, NODE *val);
IMPORT void define_single_assign_static(
  const char *namespace, const char *name,
  NODE_GETTER getter, NODE **var_p
);
IMPORT NODE *from_latin_1_string(const char *str, long len);
IMPORT void use_read_only(
  const char *namespace, const char *name,
  NODE_GETTER *getter, NODE_GETTER *get_value_or_future
);
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
static NODE *unique__1_1;
static NODE *unique__2_1;
static NODE *get__std__VALUED_OPTION(void) {
  return var.std__VALUED_OPTION;
}
static NODE *unique__3_1;
static NODE *get__std__MULTI_VALUED_OPTION(void) {
  return var.std__MULTI_VALUED_OPTION;
}
static NODE *unique__4_1;
static NODE *get__std__MANDATORY_PARAMETER(void) {
  return var.std__MANDATORY_PARAMETER;
}
static NODE *unique__5_1;
static NODE *get__std__OPTIONAL_PARAMETER(void) {
  return var.std__OPTIONAL_PARAMETER;
}
static NODE *unique__6_1;
static NODE *get__std__SOME_PARAMETERS(void) {
  return var.std__SOME_PARAMETERS;
}
static NODE *unique__7_1;
static NODE *get__std__MANY_PARAMETERS(void) {
  return var.std__MANY_PARAMETERS;
}
static NODE *func__10_1;
static void entry__10_1(void);
static FRAME_INFO frame__10_1 = {1, {"msg"}};
static NODE *get__std__copyright(void) {
  return var.std__copyright;
}
static NODE *func__11_1;
static void entry__11_1(void);
static FRAME_INFO frame__11_1 = {1, {"no"}};
static NODE *get__std__version(void) {
  return var.std__version;
}
static NODE *func__12_1;
static void entry__12_1(void);
static FRAME_INFO frame__12_1 = {4, {"options", "templates", "results", "parameters"}};
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
static NODE *func__13_1;
static void entry__13_1(void);
static FRAME_INFO frame__13_1 = {3, {"options", "templates", "results"}};
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
static NODE *func__14_1;
static void entry__14_1(void);
static FRAME_INFO frame__14_1 = {2, {"tab", "first_column_width"}};
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
static NODE *func__19_1;
static void entry__19_1(void);
static FRAME_INFO frame__19_1 = {1, {"command_name"}};
static NODE *string__19_2;
static NODE *string__19_3;
static void cont__19_4(void);
static NODE *func__20_1;
static void entry__20_1(void);
static FRAME_INFO frame__20_1 = {0, {}};
static NODE *func__21_1;
static void entry__21_1(void);
static FRAME_INFO frame__21_1 = {18, {"command", "arguments", "templates", "results", "options", "parameters", "names", "kinds", "possible_values", "default_values", "conversions", "help_messages", "command_name", "help_message", "show_usage", "too_few_arguments_error", "too_many_arguments_error", "last_idx"}};
static NODE *func__21_2;
static void entry__21_2(void);
static FRAME_INFO frame__21_2 = {5, {"idx", "help_messages", "possible_values", "message", "possible_value"}};
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
static NODE *func__21_15;
static void entry__21_15(void);
static FRAME_INFO frame__21_15 = {8, {"kinds", "command_name", "command", "parameters", "help_message", "options", "help_messages", "parameter_name"}};
static NODE *func__21_16;
static void entry__21_16(void);
static FRAME_INFO frame__21_16 = {4, {"parameter", "idx", "kinds", "buf"}};
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
static NODE *string__21_42;
static void cont__21_43(void);
static NODE *string__21_44;
static NODE *string__21_45;
static void cont__21_46(void);
static void cont__21_47(void);
static NODE *func__21_48;
static void entry__21_48(void);
static FRAME_INFO frame__21_48 = {1, {"command"}};
static void cont__21_49(void);
static NODE *func__21_50;
static void entry__21_50(void);
static FRAME_INFO frame__21_50 = {0, {}};
static void cont__21_51(void);
static NODE *string__21_52;
static void cont__21_53(void);
static NODE *func__21_54;
static void entry__21_54(void);
static FRAME_INFO frame__21_54 = {3, {"parameter", "idx", "parameter_name"}};
static void cont__21_55(void);
static NODE *string__21_56;
static void cont__21_57(void);
static void cont__21_58(void);
static NODE *string__21_59;
static void cont__21_60(void);
static NODE *func__21_61;
static void entry__21_61(void);
static FRAME_INFO frame__21_61 = {4, {"parameters", "parameter_name", "help_message", "tab"}};
static NODE *func__21_62;
static void entry__21_62(void);
static FRAME_INFO frame__21_62 = {5, {"parameter", "idx", "tab", "parameter_name", "help_message"}};
static void cont__21_63(void);
static void cont__21_64(void);
static void cont__21_65(void);
static void cont__21_66(void);
static void cont__21_67(void);
static void cont__21_68(void);
static void cont__21_69(void);
static NODE *func__21_70;
static void entry__21_70(void);
static FRAME_INFO frame__21_70 = {3, {"options", "kinds", "help_messages"}};
static NODE *string__21_71;
static void cont__21_72(void);
static NODE *func__21_73;
static void entry__21_73(void);
static FRAME_INFO frame__21_73 = {4, {"options", "kinds", "help_messages", "tab"}};
static NODE *func__21_74;
static void entry__21_74(void);
static FRAME_INFO frame__21_74 = {6, {"option", "idx", "kinds", "tab", "help_messages", "option_name"}};
static NODE *func__21_75;
static void entry__21_75(void);
static FRAME_INFO frame__21_75 = {4, {"option", "kinds", "idx", "buf"}};
static NODE *string__21_76;
static void cont__21_77(void);
static void cont__21_78(void);
static NODE *func__21_79;
static void entry__21_79(void);
static FRAME_INFO frame__21_79 = {1, {"buf"}};
static NODE *string__21_80;
static void cont__21_81(void);
static NODE *func__21_82;
static void entry__21_82(void);
static FRAME_INFO frame__21_82 = {1, {"buf"}};
static NODE *string__21_83;
static void cont__21_84(void);
static void cont__21_85(void);
static void cont__21_86(void);
static void cont__21_87(void);
static void cont__21_88(void);
static void cont__21_89(void);
static void cont__21_90(void);
static NODE *func__21_91;
static void entry__21_91(void);
static FRAME_INFO frame__21_91 = {2, {"command", "show_usage"}};
static void cont__21_92(void);
static NODE *func__21_93;
static void entry__21_93(void);
static FRAME_INFO frame__21_93 = {1, {"command"}};
static NODE *string__21_94;
static NODE *string__21_95;
static void cont__21_96(void);
static NODE *func__21_97;
static void entry__21_97(void);
static FRAME_INFO frame__21_97 = {0, {}};
static NODE *string__21_98;
static void cont__21_99(void);
static void cont__21_100(void);
static NODE *func__21_101;
static void entry__21_101(void);
static FRAME_INFO frame__21_101 = {1, {"show_usage"}};
static NODE *string__21_102;
static void cont__21_103(void);
static void cont__21_104(void);
static void cont__21_105(void);
static void cont__21_106(void);
static void cont__21_107(void);
static NODE *func__21_108;
static void entry__21_108(void);
static FRAME_INFO frame__21_108 = {16, {"idx", "template", "possible_values", "names", "kinds", "default_values", "conversions", "help_messages", "results", "options", "parameters", "option", "name", "default_value", "conversion", "help"}};
static void cont__21_109(void);
static void cont__21_110(void);
static NODE *func__21_111;
static void entry__21_111(void);
static FRAME_INFO frame__21_111 = {2, {"possible_values", "option"}};
static void cont__21_112(void);
static void cont__21_113(void);
static void cont__21_114(void);
static NODE *func__21_115;
static void entry__21_115(void);
static FRAME_INFO frame__21_115 = {1, {"possible_values"}};
static void cont__21_116(void);
static void cont__21_117(void);
static void cont__21_118(void);
static NODE *func__21_119;
static void entry__21_119(void);
static FRAME_INFO frame__21_119 = {1, {"name"}};
static NODE *func__21_120;
static void entry__21_120(void);
static FRAME_INFO frame__21_120 = {1, {"option"}};
static void cont__21_121(void);
static void cont__21_122(void);
static void cont__21_123(void);
static void cont__21_124(void);
static void cont__21_125(void);
static void cont__21_126(void);
static NODE *func__21_127;
static void entry__21_127(void);
static FRAME_INFO frame__21_127 = {5, {"option", "results", "options", "idx", "kinds"}};
static void cont__21_128(void);
static NODE *func__21_129;
static void entry__21_129(void);
static FRAME_INFO frame__21_129 = {5, {"results", "options", "option", "idx", "kinds"}};
static void cont__21_130(void);
static void cont__21_131(void);
static void cont__21_132(void);
static NODE *func__21_133;
static void entry__21_133(void);
static FRAME_INFO frame__21_133 = {5, {"option", "results", "options", "name", "idx"}};
static void cont__21_134(void);
static NODE *func__21_135;
static void entry__21_135(void);
static FRAME_INFO frame__21_135 = {4, {"results", "options", "name", "idx"}};
static void cont__21_136(void);
static void cont__21_137(void);
static NODE *func__21_138;
static void entry__21_138(void);
static FRAME_INFO frame__21_138 = {5, {"option", "results", "options", "name", "idx"}};
static void cont__21_139(void);
static NODE *func__21_140;
static void entry__21_140(void);
static FRAME_INFO frame__21_140 = {4, {"results", "options", "name", "idx"}};
static void cont__21_141(void);
static void cont__21_142(void);
static NODE *func__21_143;
static void entry__21_143(void);
static FRAME_INFO frame__21_143 = {5, {"option", "results", "parameters", "name", "idx"}};
static void cont__21_144(void);
static NODE *func__21_145;
static void entry__21_145(void);
static FRAME_INFO frame__21_145 = {1, {"option"}};
static void cont__21_146(void);
static void cont__21_147(void);
static NODE *func__21_148;
static void entry__21_148(void);
static FRAME_INFO frame__21_148 = {4, {"results", "parameters", "name", "idx"}};
static void cont__21_149(void);
static void cont__21_150(void);
static NODE *func__21_151;
static void entry__21_151(void);
static FRAME_INFO frame__21_151 = {4, {"results", "parameters", "name", "idx"}};
static void cont__21_152(void);
static void cont__21_153(void);
static void cont__21_154(void);
static void cont__21_155(void);
static void cont__21_156(void);
static void cont__21_157(void);
static NODE *func__21_158;
static void entry__21_158(void);
static FRAME_INFO frame__21_158 = {3, {"arguments", "show_usage", "command_name"}};
static void cont__21_159(void);
static NODE *string__21_160;
static void cont__21_161(void);
static NODE *func__21_162;
static void entry__21_162(void);
static FRAME_INFO frame__21_162 = {1, {"show_usage"}};
static void cont__21_163(void);
static void cont__21_164(void);
static void cont__21_165(void);
static NODE *func__21_166;
static void entry__21_166(void);
static FRAME_INFO frame__21_166 = {1, {"arguments"}};
static void cont__21_167(void);
static NODE *string__21_168;
static void cont__21_169(void);
static void cont__21_170(void);
static NODE *func__21_171;
static void entry__21_171(void);
static FRAME_INFO frame__21_171 = {0, {}};
static void cont__21_172(void);
static void cont__21_173(void);
static void cont__21_174(void);
static NODE *func__21_175;
static void entry__21_175(void);
static FRAME_INFO frame__21_175 = {1, {"arguments"}};
static void cont__21_176(void);
static NODE *string__21_177;
static void cont__21_178(void);
static void cont__21_179(void);
static NODE *func__21_180;
static void entry__21_180(void);
static FRAME_INFO frame__21_180 = {1, {"command_name"}};
static void cont__21_181(void);
static void cont__21_182(void);
static NODE *func__21_183;
static void entry__21_183(void);
static FRAME_INFO frame__21_183 = {7, {"arguments", "kinds", "results", "options", "idx", "fetch_option_value", "option_idx"}};
static NODE *func__21_184;
static void entry__21_184(void);
static FRAME_INFO frame__21_184 = {8, {"break", "arguments", "idx", "fetch_option_value", "kinds", "option_idx", "results", "options"}};
static NODE *func__21_185;
static void entry__21_185(void);
static FRAME_INFO frame__21_185 = {9, {"argument", "arguments", "idx", "break", "fetch_option_value", "kinds", "option_idx", "results", "options"}};
static NODE *string__21_186;
static void cont__21_187(void);
static NODE *func__21_188;
static void entry__21_188(void);
static FRAME_INFO frame__21_188 = {3, {"arguments", "idx", "break"}};
static void cont__21_189(void);
static void cont__21_190(void);
static NODE *func__21_191;
static void entry__21_191(void);
static FRAME_INFO frame__21_191 = {7, {"fetch_option_value", "arguments", "idx", "kinds", "option_idx", "results", "argument"}};
static void cont__21_192(void);
static void cont__21_193(void);
static NODE *func__21_194;
static void entry__21_194(void);
static FRAME_INFO frame__21_194 = {3, {"results", "option_idx", "argument"}};
static void cont__21_195(void);
static NODE *func__21_196;
static void entry__21_196(void);
static FRAME_INFO frame__21_196 = {3, {"results", "option_idx", "argument"}};
static void cont__21_197(void);
static void cont__21_198(void);
static void cont__21_199(void);
static NODE *func__21_200;
static void entry__21_200(void);
static FRAME_INFO frame__21_200 = {8, {"argument", "option_idx", "options", "kinds", "results", "fetch_option_value", "arguments", "idx"}};
static NODE *string__21_201;
static void cont__21_202(void);
static NODE *func__21_203;
static void entry__21_203(void);
static FRAME_INFO frame__21_203 = {8, {"option_idx", "options", "argument", "kinds", "results", "fetch_option_value", "arguments", "idx"}};
static void cont__21_204(void);
static void cont__21_205(void);
static void cont__21_206(void);
static void cont__21_207(void);
static NODE *func__21_208;
static void entry__21_208(void);
static FRAME_INFO frame__21_208 = {1, {"argument"}};
static NODE *string__21_209;
static NODE *string__21_210;
static void cont__21_211(void);
static void cont__21_212(void);
static void cont__21_213(void);
static void cont__21_214(void);
static NODE *func__21_215;
static void entry__21_215(void);
static FRAME_INFO frame__21_215 = {2, {"results", "option_idx"}};
static void cont__21_216(void);
static NODE *func__21_217;
static void entry__21_217(void);
static FRAME_INFO frame__21_217 = {1, {"fetch_option_value"}};
static void cont__21_218(void);
static void cont__21_219(void);
static NODE *func__21_220;
static void entry__21_220(void);
static FRAME_INFO frame__21_220 = {1, {"idx"}};
static void cont__21_221(void);
static void cont__21_222(void);
static void cont__21_223(void);
static void cont__21_224(void);
static NODE *func__21_225;
static void entry__21_225(void);
static FRAME_INFO frame__21_225 = {6, {"break", "templates", "arguments", "too_few_arguments_error", "results", "last_idx"}};
static void cont__21_226(void);
static NODE *func__21_227;
static void entry__21_227(void);
static FRAME_INFO frame__21_227 = {12, {"idx", "template", "arguments", "too_few_arguments_error", "results", "last_idx", "break", "option", "name", "default_value", "conversion", "help"}};
static void cont__21_228(void);
static void cont__21_229(void);
static NODE *func__21_230;
static void entry__21_230(void);
static FRAME_INFO frame__21_230 = {1, {"option"}};
static void cont__21_231(void);
static void cont__21_232(void);
static NODE *func__21_233;
static void entry__21_233(void);
static FRAME_INFO frame__21_233 = {5, {"arguments", "too_few_arguments_error", "results", "idx", "last_idx"}};
static void cont__21_234(void);
static void cont__21_235(void);
static void cont__21_236(void);
static void cont__21_237(void);
static void cont__21_238(void);
static void cont__21_239(void);
static NODE *func__21_240;
static void entry__21_240(void);
static FRAME_INFO frame__21_240 = {1, {"break"}};
static void cont__21_241(void);
static void cont__21_242(void);
static NODE *func__21_243;
static void entry__21_243(void);
static FRAME_INFO frame__21_243 = {10, {"idx", "template", "arguments", "too_few_arguments_error", "results", "option", "name", "default_value", "conversion", "help"}};
static void cont__21_244(void);
static void cont__21_245(void);
static NODE *func__21_246;
static void entry__21_246(void);
static FRAME_INFO frame__21_246 = {1, {"option"}};
static void cont__21_247(void);
static void cont__21_248(void);
static NODE *func__21_249;
static void entry__21_249(void);
static FRAME_INFO frame__21_249 = {4, {"arguments", "too_few_arguments_error", "results", "idx"}};
static void cont__21_250(void);
static void cont__21_251(void);
static void cont__21_252(void);
static void cont__21_253(void);
static void cont__21_254(void);
static NODE *func__21_255;
static void entry__21_255(void);
static FRAME_INFO frame__21_255 = {3, {"arguments", "results", "idx"}};
static void cont__21_256(void);
static void cont__21_257(void);
static NODE *func__21_258;
static void entry__21_258(void);
static FRAME_INFO frame__21_258 = {3, {"arguments", "results", "idx"}};
static void cont__21_259(void);
static void cont__21_260(void);
static NODE *func__21_261;
static void entry__21_261(void);
static FRAME_INFO frame__21_261 = {3, {"results", "idx", "arguments"}};
static void cont__21_262(void);
static NODE *func__21_263;
static void entry__21_263(void);
static FRAME_INFO frame__21_263 = {4, {"arguments", "too_few_arguments_error", "results", "idx"}};
static void cont__21_264(void);
static void cont__21_265(void);
static void cont__21_266(void);
static void cont__21_267(void);
static void cont__21_268(void);
static void cont__21_269(void);
static void cont__21_270(void);
static NODE *func__21_271;
static void entry__21_271(void);
static FRAME_INFO frame__21_271 = {8, {"idx", "result", "default_values", "results", "possible_values", "names", "show_usage", "conversions"}};
static void cont__21_272(void);
static NODE *func__21_273;
static void entry__21_273(void);
static FRAME_INFO frame__21_273 = {2, {"default_values", "idx"}};
static void cont__21_274(void);
static void cont__21_275(void);
static void cont__21_276(void);
static NODE *func__21_277;
static void entry__21_277(void);
static FRAME_INFO frame__21_277 = {3, {"results", "idx", "default_values"}};
static void cont__21_278(void);
static void cont__21_279(void);
static NODE *func__21_280;
static void entry__21_280(void);
static FRAME_INFO frame__21_280 = {10, {"possible_values", "idx", "names", "show_usage", "result", "conversions", "results", "possible_value", "check", "conversion"}};
static NODE *func__21_281;
static void entry__21_281(void);
static FRAME_INFO frame__21_281 = {5, {"value", "possible_value", "names", "idx", "show_usage"}};
static void cont__21_282(void);
static NODE *func__21_283;
static void entry__21_283(void);
static FRAME_INFO frame__21_283 = {3, {"names", "idx", "show_usage"}};
static void cont__21_284(void);
static void cont__21_285(void);
static NODE *string__21_286;
static NODE *string__21_287;
static void cont__21_288(void);
static void cont__21_289(void);
static void cont__21_290(void);
static void cont__21_291(void);
static void cont__21_292(void);
static NODE *func__21_293;
static void entry__21_293(void);
static FRAME_INFO frame__21_293 = {2, {"result", "check"}};
static void cont__21_294(void);
static NODE *func__21_295;
static void entry__21_295(void);
static FRAME_INFO frame__21_295 = {2, {"result", "check"}};
static NODE *func__21_296;
static void entry__21_296(void);
static FRAME_INFO frame__21_296 = {2, {"item", "check"}};
static NODE *func__21_297;
static void entry__21_297(void);
static FRAME_INFO frame__21_297 = {2, {"check", "result"}};
static void cont__21_298(void);
static void cont__21_299(void);
static void cont__21_300(void);
static NODE *func__21_301;
static void entry__21_301(void);
static FRAME_INFO frame__21_301 = {4, {"result", "conversion", "results", "idx"}};
static void cont__21_302(void);
static NODE *func__21_303;
static void entry__21_303(void);
static FRAME_INFO frame__21_303 = {5, {"result", "conversion", "results", "idx", "new_result"}};
static NODE *func__21_304;
static void entry__21_304(void);
static FRAME_INFO frame__21_304 = {3, {"item", "new_result", "conversion"}};
static void cont__21_305(void);
static void cont__21_306(void);
static void cont__21_307(void);
static void cont__21_308(void);
static NODE *func__21_309;
static void entry__21_309(void);
static FRAME_INFO frame__21_309 = {4, {"results", "idx", "conversion", "result"}};
static void cont__21_310(void);
static void cont__21_311(void);
static void cont__21_312(void);
static NODE *func__22_1;
static void entry__22_1(void);
static FRAME_INFO frame__22_1 = {2, {"commands", "command_ids"}};
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
static NODE *func__23_1;
static void entry__23_1(void);
static FRAME_INFO frame__23_1 = {2, {"id", "templates"}};
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
static NODE *string__23_25;
static void cont__23_26(void);
static NODE *func__23_27;
static void entry__23_27(void);
static FRAME_INFO frame__23_27 = {3, {"command", "id", "templates"}};
static void cont__23_28(void);
static void cont__23_29(void);
static NODE *func__23_30;
static void entry__23_30(void);
static FRAME_INFO frame__23_30 = {3, {"id", "command", "templates"}};
static void cont__23_31(void);
static void cont__23_32(void);
static NODE *func__23_33;
static void entry__23_33(void);
static FRAME_INFO frame__23_33 = {1, {"templates"}};
static NODE *func__23_34;
static void entry__23_34(void);
static FRAME_INFO frame__23_34 = {1, {"templates"}};
static void cont__23_35(void);
static void cont__23_36(void);
static void cont__23_37(void);
static NODE *get__std__command_parameters(void) {
  return var.std__command_parameters;
}
static NODE *func__24_1;
static void entry__24_1(void);
static FRAME_INFO frame__24_1 = {1, {"tab"}};
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
static NODE *string__24_10;
static void cont__24_11(void);
static void cont__24_12(void);
static NODE *func__24_13;
static void entry__24_13(void);
static FRAME_INFO frame__24_13 = {3, {"idx", "command_name", "tab"}};
static void cont__24_14(void);
static void cont__24_15(void);
static void cont__24_16(void);
static void cont__24_17(void);
static void cont__24_18(void);
static NODE *func__24_19;
static void entry__24_19(void);
static FRAME_INFO frame__24_19 = {1, {"tab"}};
static NODE *string__24_20;
static NODE *string__24_21;
static void cont__24_22(void);
static void cont__24_23(void);
static void cont__24_24(void);
static void cont__24_25(void);
static NODE *func__24_26;
static void entry__24_26(void);
static FRAME_INFO frame__24_26 = {1, {"tab"}};
static NODE *string__24_27;
static NODE *string__24_28;
static void cont__24_29(void);
static void cont__24_30(void);
static void cont__24_31(void);
static NODE *func__25_1;
static void entry__25_1(void);
static FRAME_INFO frame__25_1 = {1, {"templates"}};
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
static NODE *string__25_15;
static NODE *func__25_16;
static void entry__25_16(void);
static FRAME_INFO frame__25_16 = {0, {}};
static void cont__25_17(void);
static NODE *func__25_18;
static void entry__25_18(void);
static FRAME_INFO frame__25_18 = {0, {}};
static void cont__25_19(void);
static NODE *string__25_20;
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
static NODE *string__25_27;
static NODE *func__25_28;
static void entry__25_28(void);
static FRAME_INFO frame__25_28 = {0, {}};
static void cont__25_29(void);
static NODE *func__25_30;
static void entry__25_30(void);
static FRAME_INFO frame__25_30 = {0, {}};
static NODE *string__25_31;
static void cont__25_32(void);
static NODE *string__25_33;
static NODE *func__25_34;
static void entry__25_34(void);
static FRAME_INFO frame__25_34 = {0, {}};
static NODE *string__25_35;
static void cont__25_36(void);
static NODE *string__25_37;
static NODE *func__25_38;
static void entry__25_38(void);
static FRAME_INFO frame__25_38 = {0, {}};
static void cont__25_39(void);
static NODE *func__25_40;
static void entry__25_40(void);
static FRAME_INFO frame__25_40 = {0, {}};
static NODE *string__25_41;
static void cont__25_42(void);
static void cont__25_43(void);
static NODE *string__25_44;
static void cont__25_45(void);
static void cont__25_46(void);
static NODE *func__25_47;
static void entry__25_47(void);
static FRAME_INFO frame__25_47 = {0, {}};
static NODE *string__25_48;
static void cont__25_49(void);
static void cont__25_50(void);
static NODE *string__25_51;
static NODE *func__25_52;
static void entry__25_52(void);
static FRAME_INFO frame__25_52 = {0, {}};
static void cont__25_53(void);
static NODE *func__25_54;
static void entry__25_54(void);
static FRAME_INFO frame__25_54 = {1, {"command_name"}};
static void cont__25_55(void);
static void cont__25_56(void);
static void cont__25_57(void);
static void cont__25_58(void);
static NODE *string__25_59;
static void cont__25_60(void);
static void cont__25_61(void);
static NODE *get__std__program_parameters(void) {
  return var.std__program_parameters;
}
void run__basic__parameters(void);

static CONTINUATION_INFO continuation_info[] = {
  {run__basic__parameters, NULL, 119, 119, 1, 33},
  {entry__10_1, NULL, 34, 34, 45, 45},
  {entry__11_1, NULL, 36, 36, 39, 39},
  {entry__12_5, NULL, 46, 46, 11, 18},
  {cont__12_6, &frame__12_5, 46, 46, 18, 18},
  {entry__12_7, NULL, 48, 48, 11, 33},
  {cont__12_8, &frame__12_7, 49, 49, 11, 32},
  {cont__12_9, &frame__12_7, 49, 49, 32, 32},
  {entry__12_3, NULL, 45, 45, 9, 34},
  {cont__12_4, &frame__12_3, 44, 49, 7, 33},
  {entry__12_2, NULL, 43, 49, 5, 34},
  {entry__12_19, NULL, 59, 59, 15, 36},
  {cont__12_20, &frame__12_19, 60, 60, 28, 43},
  {cont__12_21, &frame__12_19, 60, 60, 15, 43},
  {cont__12_22, &frame__12_19, 60, 60, 43, 43},
  {entry__12_23, NULL, 62, 62, 15, 22},
  {cont__12_24, &frame__12_23, 62, 62, 22, 22},
  {entry__12_15, NULL, 58, 58, 13, 26},
  {cont__12_16, &frame__12_15, 58, 58, 31, 46},
  {cont__12_17, &frame__12_15, 58, 58, 13, 46},
  {cont__12_18, &frame__12_15, 57, 62, 11, 23},
  {entry__12_14, NULL, 56, 62, 9, 24},
  {entry__12_30, NULL, 67, 67, 15, 36},
  {cont__12_31, &frame__12_30, 68, 68, 15, 38},
  {cont__12_32, &frame__12_30, 68, 68, 38, 38},
  {entry__12_33, NULL, 70, 70, 15, 22},
  {cont__12_34, &frame__12_33, 70, 70, 22, 22},
  {entry__12_26, NULL, 66, 66, 13, 26},
  {cont__12_27, &frame__12_26, 66, 66, 31, 46},
  {cont__12_28, &frame__12_26, 66, 66, 13, 46},
  {cont__12_29, &frame__12_26, 65, 70, 11, 23},
  {entry__12_25, NULL, 64, 70, 9, 24},
  {entry__12_11, NULL, 51, 51, 5, 31},
  {cont__12_12, &frame__12_11, 54, 54, 7, 31},
  {cont__12_13, &frame__12_11, 53, 70, 5, 26},
  {cont__12_35, &frame__12_11, 71, 71, 5, 24},
  {cont__12_36, &frame__12_11, 71, 71, 24, 24},
  {entry__12_39, NULL, 73, 73, 55, 64},
  {cont__12_40, &frame__12_39, 73, 73, 48, 65},
  {cont__12_41, &frame__12_39, 73, 73, 35, 66},
  {cont__12_42, &frame__12_39, 73, 73, 71, 71},
  {cont__12_43, &frame__12_39, 73, 73, 29, 72},
  {cont__12_44, &frame__12_39, 73, 73, 11, 75},
  {cont__12_47, &frame__12_39, 73, 73, 5, 75},
  {entry__12_1, NULL, 41, 49, 3, 35},
  {cont__12_10, &frame__12_1, 50, 71, 3, 24},
  {cont__12_37, &frame__12_1, 72, 72, 10, 25},
  {cont__12_38, &frame__12_1, 72, 73, 3, 75},
  {cont__12_48, &frame__12_1, 74, 74, 3, 25},
  {entry__13_10, NULL, 91, 91, 15, 36},
  {cont__13_11, &frame__13_10, 92, 92, 28, 43},
  {cont__13_12, &frame__13_10, 92, 92, 15, 43},
  {cont__13_13, &frame__13_10, 92, 92, 43, 43},
  {entry__13_14, NULL, 94, 94, 15, 22},
  {cont__13_15, &frame__13_14, 94, 94, 22, 22},
  {entry__13_6, NULL, 90, 90, 13, 26},
  {cont__13_7, &frame__13_6, 90, 90, 31, 46},
  {cont__13_8, &frame__13_6, 90, 90, 13, 46},
  {cont__13_9, &frame__13_6, 89, 94, 11, 23},
  {entry__13_5, NULL, 88, 94, 9, 24},
  {entry__13_19, NULL, 98, 98, 43, 56},
  {cont__13_20, &frame__13_19, 98, 98, 61, 76},
  {cont__13_21, &frame__13_19, 98, 98, 43, 76},
  {cont__13_22, &frame__13_19, 98, 98, 43, 76},
  {entry__13_24, NULL, 99, 99, 15, 36},
  {cont__13_25, &frame__13_24, 100, 100, 15, 38},
  {cont__13_26, &frame__13_24, 100, 100, 38, 38},
  {entry__13_27, NULL, 102, 102, 15, 22},
  {cont__13_28, &frame__13_27, 102, 102, 22, 22},
  {entry__13_17, NULL, 98, 98, 13, 38},
  {cont__13_18, &frame__13_17, 98, 98, 13, 76},
  {cont__13_23, &frame__13_17, 97, 102, 11, 23},
  {entry__13_16, NULL, 96, 102, 9, 24},
  {entry__13_2, NULL, 83, 83, 5, 31},
  {cont__13_3, &frame__13_2, 86, 86, 7, 31},
  {cont__13_4, &frame__13_2, 85, 102, 5, 26},
  {cont__13_29, &frame__13_2, 103, 103, 5, 24},
  {cont__13_30, &frame__13_2, 103, 103, 24, 24},
  {entry__13_1, NULL, 82, 103, 3, 24},
  {cont__13_31, &frame__13_1, 104, 104, 3, 13},
  {entry__14_2, NULL, 108, 108, 65, 72},
  {cont__14_3, &frame__14_2, 108, 108, 55, 73},
  {cont__14_4, &frame__14_2, 108, 108, 25, 73},
  {cont__14_5, &frame__14_2, 108, 108, 73, 73},
  {entry__14_17, NULL, 113, 113, 37, 56},
  {cont__14_18, &frame__14_17, 113, 113, 27, 56},
  {cont__14_20, &frame__14_17, 113, 113, 20, 56},
  {entry__14_14, NULL, 113, 113, 10, 17},
  {cont__14_15, &frame__14_14, 113, 113, 10, 17},
  {cont__14_16, &frame__14_14, 113, 113, 7, 56},
  {cont__14_21, &frame__14_14, 114, 114, 7, 19},
  {entry__14_8, NULL, 111, 111, 27, 34},
  {cont__14_9, &frame__14_8, 111, 111, 17, 54},
  {cont__14_10, &frame__14_8, 111, 111, 5, 54},
  {cont__14_12, &frame__14_8, 112, 112, 19, 26},
  {cont__14_13, &frame__14_8, 112, 114, 5, 19},
  {entry__14_1, NULL, 108, 108, 3, 73},
  {cont__14_6, &frame__14_1, 109, 109, 3, 28},
  {cont__14_7, &frame__14_1, 110, 114, 3, 20},
  {entry__19_1, NULL, 122, 122, 10, 53},
  {cont__19_4, &frame__19_1, 122, 122, 3, 53},
  {entry__20_1, NULL, 124, 124, 18, 41},
  {entry__21_9, NULL, 144, 144, 40, 70},
  {cont__21_10, &frame__21_9, 144, 144, 70, 70},
  {entry__21_6, NULL, 143, 143, 7, 37},
  {cont__21_8, &frame__21_6, 144, 144, 7, 70},
  {cont__21_11, &frame__21_6, 145, 145, 17, 17},
  {cont__21_12, &frame__21_6, 145, 145, 7, 18},
  {cont__21_13, &frame__21_6, 145, 145, 25, 25},
  {entry__21_2, NULL, 140, 140, 5, 32},
  {cont__21_3, &frame__21_2, 141, 141, 5, 40},
  {cont__21_4, &frame__21_2, 142, 142, 8, 32},
  {cont__21_5, &frame__21_2, 142, 145, 5, 25},
  {cont__21_14, &frame__21_2, 146, 146, 5, 14},
  {entry__21_19, NULL, 154, 154, 11, 23},
  {cont__21_20, &frame__21_19, 154, 154, 23, 23},
  {entry__21_21, NULL, 156, 156, 11, 23},
  {cont__21_22, &frame__21_21, 156, 156, 23, 23},
  {entry__21_23, NULL, 158, 158, 11, 23},
  {cont__21_24, &frame__21_23, 158, 158, 23, 23},
  {entry__21_16, NULL, 150, 150, 7, 35},
  {cont__21_17, &frame__21_16, 152, 152, 9, 18},
  {cont__21_18, &frame__21_16, 151, 158, 7, 24},
  {cont__21_25, &frame__21_16, 159, 159, 7, 12},
  {entry__21_27, NULL, 161, 161, 36, 60},
  {entry__21_30, NULL, 163, 163, 7, 39},
  {cont__21_31, &frame__21_30, 164, 164, 27, 58},
  {cont__21_32, &frame__21_30, 164, 164, 16, 59},
  {cont__21_33, &frame__21_30, 164, 164, 7, 59},
  {entry__21_40, NULL, 167, 167, 40, 80},
  {entry__21_38, NULL, 167, 167, 10, 37},
  {cont__21_39, &frame__21_38, 167, 167, 7, 80},
  {cont__21_43, &frame__21_38, 168, 168, 7, 42},
  {entry__21_48, NULL, 172, 172, 33, 51},
  {cont__21_49, &frame__21_48, 172, 172, 30, 51},
  {entry__21_50, NULL, 172, 172, 54, 58},
  {entry__21_54, NULL, 174, 174, 18, 46},
  {cont__21_55, &frame__21_54, 174, 174, 7, 46},
  {entry__21_62, NULL, 182, 182, 24, 52},
  {cont__21_63, &frame__21_62, 182, 182, 54, 70},
  {cont__21_64, &frame__21_62, 182, 182, 19, 71},
  {cont__21_65, &frame__21_62, 182, 182, 9, 71},
  {cont__21_66, &frame__21_62, 182, 182, 71, 71},
  {entry__21_61, NULL, 181, 182, 7, 71},
  {cont__21_67, &frame__21_61, 183, 183, 7, 23},
  {entry__21_79, NULL, 196, 196, 17, 36},
  {cont__21_81, &frame__21_79, 196, 196, 36, 36},
  {entry__21_82, NULL, 198, 198, 17, 37},
  {cont__21_84, &frame__21_82, 198, 198, 37, 37},
  {entry__21_75, NULL, 192, 192, 13, 37},
  {cont__21_77, &frame__21_75, 194, 194, 15, 24},
  {cont__21_78, &frame__21_75, 193, 198, 13, 38},
  {cont__21_85, &frame__21_75, 199, 199, 13, 18},
  {entry__21_74, NULL, 201, 201, 26, 38},
  {cont__21_86, &frame__21_74, 201, 201, 40, 57},
  {cont__21_87, &frame__21_74, 201, 201, 21, 58},
  {cont__21_88, &frame__21_74, 201, 201, 11, 58},
  {cont__21_89, &frame__21_74, 201, 201, 58, 58},
  {entry__21_73, NULL, 190, 201, 9, 58},
  {cont__21_90, &frame__21_73, 202, 202, 9, 25},
  {entry__21_70, NULL, 185, 187, 7, 16},
  {cont__21_72, &frame__21_70, 188, 202, 7, 25},
  {entry__21_15, NULL, 161, 161, 8, 33},
  {cont__21_26, &frame__21_15, 161, 161, 5, 60},
  {cont__21_28, &frame__21_15, 162, 162, 8, 28},
  {cont__21_29, &frame__21_15, 162, 164, 5, 59},
  {cont__21_34, &frame__21_15, 165, 165, 5, 21},
  {cont__21_36, &frame__21_15, 166, 166, 12, 29},
  {cont__21_37, &frame__21_15, 166, 168, 5, 42},
  {cont__21_46, &frame__21_15, 172, 172, 10, 27},
  {cont__21_47, &frame__21_15, 172, 172, 7, 59},
  {cont__21_51, &frame__21_15, 169, 172, 5, 59},
  {cont__21_53, &frame__21_15, 173, 174, 5, 46},
  {cont__21_57, &frame__21_15, 175, 175, 5, 12},
  {cont__21_58, &frame__21_15, 176, 178, 5, 17},
  {cont__21_60, &frame__21_15, 179, 183, 5, 23},
  {cont__21_68, &frame__21_15, 184, 184, 12, 27},
  {cont__21_69, &frame__21_15, 184, 202, 5, 26},
  {entry__21_93, NULL, 207, 208, 18, 51},
  {cont__21_96, &frame__21_93, 207, 208, 9, 51},
  {entry__21_97, NULL, 210, 211, 9, 28},
  {entry__21_91, NULL, 206, 206, 7, 24},
  {cont__21_92, &frame__21_91, 205, 211, 5, 30},
  {cont__21_99, &frame__21_91, 212, 212, 5, 14},
  {cont__21_100, &frame__21_91, 213, 213, 5, 10},
  {entry__21_101, NULL, 216, 217, 5, 25},
  {cont__21_103, &frame__21_101, 218, 218, 5, 14},
  {cont__21_104, &frame__21_101, 219, 219, 5, 10},
  {entry__21_111, NULL, 225, 225, 31, 46},
  {cont__21_112, &frame__21_111, 225, 225, 9, 46},
  {cont__21_113, &frame__21_111, 226, 226, 9, 30},
  {cont__21_114, &frame__21_111, 226, 226, 30, 30},
  {entry__21_115, NULL, 228, 228, 9, 39},
  {cont__21_116, &frame__21_115, 228, 228, 39, 39},
  {entry__21_119, NULL, 229, 229, 37, 43},
  {entry__21_120, NULL, 229, 229, 46, 54},
  {entry__21_129, NULL, 236, 236, 9, 27},
  {cont__21_130, &frame__21_129, 237, 237, 9, 24},
  {cont__21_131, &frame__21_129, 238, 238, 9, 19},
  {cont__21_132, &frame__21_129, 238, 238, 34, 34},
  {entry__21_127, NULL, 235, 235, 10, 27},
  {cont__21_128, &frame__21_127, 235, 238, 7, 34},
  {entry__21_135, NULL, 240, 240, 9, 31},
  {cont__21_136, &frame__21_135, 241, 241, 9, 22},
  {cont__21_137, &frame__21_135, 241, 241, 26, 26},
  {entry__21_133, NULL, 239, 239, 10, 32},
  {cont__21_134, &frame__21_133, 239, 241, 7, 26},
  {entry__21_140, NULL, 243, 243, 9, 32},
  {cont__21_141, &frame__21_140, 244, 244, 9, 22},
  {cont__21_142, &frame__21_140, 244, 244, 26, 26},
  {entry__21_138, NULL, 242, 242, 10, 38},
  {cont__21_139, &frame__21_138, 242, 244, 7, 26},
  {entry__21_145, NULL, 245, 245, 39, 63},
  {cont__21_146, &frame__21_145, 245, 245, 39, 63},
  {entry__21_148, NULL, 246, 246, 9, 32},
  {cont__21_149, &frame__21_148, 247, 247, 9, 25},
  {cont__21_150, &frame__21_148, 247, 247, 29, 29},
  {entry__21_143, NULL, 245, 245, 10, 34},
  {cont__21_144, &frame__21_143, 245, 245, 10, 63},
  {cont__21_147, &frame__21_143, 245, 247, 7, 29},
  {entry__21_151, NULL, 249, 249, 9, 31},
  {cont__21_152, &frame__21_151, 250, 250, 9, 25},
  {cont__21_153, &frame__21_151, 250, 250, 29, 29},
  {entry__21_108, NULL, 222, 222, 5, 63},
  {cont__21_109, &frame__21_108, 224, 224, 7, 32},
  {cont__21_110, &frame__21_108, 223, 228, 5, 40},
  {cont__21_117, &frame__21_108, 229, 229, 20, 34},
  {cont__21_118, &frame__21_108, 229, 229, 17, 55},
  {cont__21_121, &frame__21_108, 229, 229, 5, 55},
  {cont__21_122, &frame__21_108, 230, 230, 5, 22},
  {cont__21_123, &frame__21_108, 231, 231, 5, 38},
  {cont__21_124, &frame__21_108, 232, 232, 5, 32},
  {cont__21_125, &frame__21_108, 233, 233, 5, 28},
  {cont__21_126, &frame__21_108, 234, 250, 5, 30},
  {entry__21_162, NULL, 253, 253, 7, 16},
  {cont__21_163, &frame__21_162, 254, 254, 7, 15},
  {entry__21_166, NULL, 255, 255, 40, 51},
  {cont__21_167, &frame__21_166, 255, 255, 40, 68},
  {cont__21_169, &frame__21_166, 255, 255, 40, 68},
  {entry__21_171, NULL, 256, 256, 7, 20},
  {cont__21_172, &frame__21_171, 257, 257, 7, 15},
  {entry__21_175, NULL, 258, 258, 38, 49},
  {cont__21_176, &frame__21_175, 258, 258, 38, 64},
  {cont__21_178, &frame__21_175, 258, 258, 38, 64},
  {entry__21_180, NULL, 259, 259, 7, 31},
  {cont__21_181, &frame__21_180, 260, 260, 7, 15},
  {entry__21_158, NULL, 252, 252, 8, 19},
  {cont__21_159, &frame__21_158, 252, 252, 8, 31},
  {cont__21_161, &frame__21_158, 252, 254, 5, 15},
  {cont__21_164, &frame__21_158, 255, 255, 8, 35},
  {cont__21_165, &frame__21_158, 255, 255, 8, 68},
  {cont__21_170, &frame__21_158, 255, 257, 5, 15},
  {cont__21_173, &frame__21_158, 258, 258, 8, 33},
  {cont__21_174, &frame__21_158, 258, 258, 8, 64},
  {cont__21_179, &frame__21_158, 258, 260, 5, 15},
  {entry__21_188, NULL, 268, 268, 11, 34},
  {cont__21_189, &frame__21_188, 269, 269, 11, 15},
  {entry__21_194, NULL, 277, 277, 17, 36},
  {cont__21_195, &frame__21_194, 277, 277, 45, 45},
  {entry__21_196, NULL, 279, 279, 23, 41},
  {cont__21_197, &frame__21_196, 279, 279, 17, 50},
  {cont__21_198, &frame__21_196, 279, 279, 22, 41},
  {cont__21_199, &frame__21_196, 279, 279, 50, 50},
  {entry__21_191, NULL, 273, 273, 13, 36},
  {cont__21_192, &frame__21_191, 275, 275, 15, 31},
  {cont__21_193, &frame__21_191, 274, 279, 13, 51},
  {entry__21_208, NULL, 284, 284, 51, 80},
  {cont__21_211, &frame__21_208, 284, 284, 45, 80},
  {entry__21_215, NULL, 287, 287, 21, 40},
  {cont__21_216, &frame__21_215, 287, 287, 45, 45},
  {entry__21_217, NULL, 289, 289, 44, 44},
  {entry__21_203, NULL, 283, 283, 55, 55},
  {cont__21_204, &frame__21_203, 283, 283, 37, 56},
  {cont__21_205, &frame__21_203, 283, 283, 17, 57},
  {cont__21_206, &frame__21_203, 284, 284, 20, 42},
  {cont__21_207, &frame__21_203, 284, 284, 17, 80},
  {cont__21_212, &frame__21_203, 286, 286, 19, 35},
  {cont__21_213, &frame__21_203, 286, 286, 19, 53},
  {cont__21_214, &frame__21_203, 285, 289, 17, 45},
  {cont__21_218, &frame__21_203, 290, 290, 17, 40},
  {cont__21_219, &frame__21_203, 290, 290, 40, 40},
  {entry__21_220, NULL, 292, 292, 17, 24},
  {cont__21_221, &frame__21_220, 292, 292, 24, 24},
  {entry__21_200, NULL, 282, 282, 15, 40},
  {cont__21_202, &frame__21_200, 281, 292, 13, 25},
  {entry__21_185, NULL, 267, 267, 12, 27},
  {cont__21_187, &frame__21_185, 267, 269, 9, 15},
  {cont__21_190, &frame__21_185, 270, 292, 9, 27},
  {entry__21_184, NULL, 266, 292, 7, 28},
  {cont__21_222, &frame__21_184, 292, 292, 28, 28},
  {entry__21_183, NULL, 265, 292, 5, 29},
  {entry__21_230, NULL, 297, 297, 38, 59},
  {cont__21_231, &frame__21_230, 297, 297, 59, 59},
  {entry__21_233, NULL, 301, 301, 14, 31},
  {cont__21_234, &frame__21_233, 301, 301, 11, 55},
  {cont__21_235, &frame__21_233, 302, 302, 11, 38},
  {cont__21_236, &frame__21_233, 302, 302, 26, 38},
  {cont__21_237, &frame__21_233, 303, 303, 11, 25},
  {cont__21_238, &frame__21_233, 303, 303, 25, 25},
  {entry__21_240, NULL, 305, 305, 11, 15},
  {entry__21_227, NULL, 296, 296, 7, 69},
  {cont__21_228, &frame__21_227, 297, 297, 10, 35},
  {cont__21_229, &frame__21_227, 297, 297, 7, 59},
  {cont__21_232, &frame__21_227, 304, 304, 9, 60},
  {cont__21_239, &frame__21_227, 298, 305, 7, 16},
  {entry__21_225, NULL, 295, 295, 38, 38},
  {cont__21_226, &frame__21_225, 295, 305, 5, 17},
  {cont__21_241, &frame__21_225, 305, 305, 17, 17},
  {entry__21_246, NULL, 308, 308, 36, 57},
  {cont__21_247, &frame__21_246, 308, 308, 57, 57},
  {entry__21_249, NULL, 312, 312, 12, 31},
  {cont__21_250, &frame__21_249, 312, 312, 12, 36},
  {cont__21_251, &frame__21_249, 312, 312, 9, 60},
  {cont__21_252, &frame__21_249, 313, 313, 9, 36},
  {cont__21_253, &frame__21_249, 313, 313, 24, 36},
  {cont__21_254, &frame__21_249, 313, 313, 36, 36},
  {entry__21_258, NULL, 315, 315, 38, 65},
  {cont__21_259, &frame__21_258, 315, 315, 53, 65},
  {cont__21_260, &frame__21_258, 315, 315, 65, 65},
  {entry__21_255, NULL, 315, 315, 12, 31},
  {cont__21_256, &frame__21_255, 315, 315, 12, 35},
  {cont__21_257, &frame__21_255, 315, 315, 9, 65},
  {entry__21_261, NULL, 317, 317, 9, 21},
  {cont__21_262, &frame__21_261, 318, 318, 29, 29},
  {entry__21_263, NULL, 320, 320, 12, 31},
  {cont__21_264, &frame__21_263, 320, 320, 12, 36},
  {cont__21_265, &frame__21_263, 320, 320, 9, 60},
  {cont__21_266, &frame__21_263, 321, 321, 9, 21},
  {cont__21_267, &frame__21_263, 322, 322, 29, 29},
  {entry__21_243, NULL, 307, 307, 5, 67},
  {cont__21_244, &frame__21_243, 308, 308, 8, 33},
  {cont__21_245, &frame__21_243, 308, 308, 5, 57},
  {cont__21_248, &frame__21_243, 309, 322, 5, 30},
  {entry__21_273, NULL, 326, 326, 30, 48},
  {cont__21_274, &frame__21_273, 326, 326, 30, 59},
  {cont__21_275, &frame__21_273, 326, 326, 30, 59},
  {entry__21_277, NULL, 327, 327, 9, 41},
  {cont__21_278, &frame__21_277, 327, 327, 9, 21},
  {cont__21_279, &frame__21_277, 327, 327, 41, 41},
  {entry__21_283, NULL, 334, 334, 45, 54},
  {cont__21_284, &frame__21_283, 334, 334, 45, 68},
  {cont__21_285, &frame__21_283, 334, 334, 15, 75},
  {cont__21_288, &frame__21_283, 333, 334, 13, 75},
  {cont__21_289, &frame__21_283, 335, 335, 13, 22},
  {cont__21_290, &frame__21_283, 336, 336, 13, 18},
  {entry__21_281, NULL, 332, 332, 18, 38},
  {cont__21_282, &frame__21_281, 332, 336, 11, 18},
  {entry__21_296, NULL, 341, 341, 39, 48},
  {entry__21_295, NULL, 341, 341, 15, 48},
  {entry__21_297, NULL, 343, 343, 15, 26},
  {entry__21_293, NULL, 340, 340, 13, 28},
  {cont__21_294, &frame__21_293, 339, 343, 11, 27},
  {entry__21_304, NULL, 349, 349, 56, 71},
  {cont__21_305, &frame__21_304, 349, 349, 39, 71},
  {cont__21_306, &frame__21_304, 349, 349, 71, 71},
  {entry__21_303, NULL, 349, 349, 15, 71},
  {cont__21_307, &frame__21_303, 350, 350, 15, 27},
  {cont__21_308, &frame__21_303, 350, 350, 38, 38},
  {entry__21_309, NULL, 352, 352, 15, 46},
  {cont__21_310, &frame__21_309, 352, 352, 15, 27},
  {cont__21_311, &frame__21_309, 352, 352, 46, 46},
  {entry__21_301, NULL, 347, 347, 13, 28},
  {cont__21_302, &frame__21_301, 346, 352, 11, 47},
  {entry__21_280, NULL, 329, 329, 9, 44},
  {cont__21_291, &frame__21_280, 338, 338, 12, 36},
  {cont__21_292, &frame__21_280, 338, 343, 9, 28},
  {cont__21_298, &frame__21_280, 344, 344, 9, 36},
  {cont__21_299, &frame__21_280, 345, 345, 12, 32},
  {cont__21_300, &frame__21_280, 345, 352, 9, 48},
  {entry__21_271, NULL, 326, 326, 7, 25},
  {cont__21_272, &frame__21_271, 326, 326, 7, 59},
  {cont__21_276, &frame__21_271, 325, 352, 5, 50},
  {entry__21_1, NULL, 136, 136, 50, 50},
  {cont__21_105, &frame__21_1, 136, 136, 3, 51},
  {cont__21_106, &frame__21_1, 137, 137, 3, 26},
  {cont__21_107, &frame__21_1, 221, 250, 3, 31},
  {cont__21_154, &frame__21_1, 251, 251, 6, 25},
  {cont__21_155, &frame__21_1, 251, 251, 6, 30},
  {cont__21_156, &frame__21_1, 251, 251, 6, 30},
  {cont__21_157, &frame__21_1, 251, 260, 3, 16},
  {cont__21_182, &frame__21_1, 261, 292, 3, 30},
  {cont__21_223, &frame__21_1, 293, 293, 3, 15},
  {cont__21_224, &frame__21_1, 294, 305, 3, 18},
  {cont__21_242, &frame__21_1, 306, 322, 3, 31},
  {cont__21_268, &frame__21_1, 323, 323, 10, 27},
  {cont__21_269, &frame__21_1, 323, 323, 3, 52},
  {cont__21_270, &frame__21_1, 324, 352, 3, 51},
  {cont__21_312, &frame__21_1, 353, 353, 3, 13},
  {entry__22_2, NULL, 358, 358, 5, 25},
  {cont__22_3, &frame__22_2, 359, 359, 5, 34},
  {cont__22_4, &frame__22_2, 360, 360, 5, 28},
  {cont__22_5, &frame__22_2, 361, 361, 5, 42},
  {cont__22_6, &frame__22_2, 362, 362, 5, 25},
  {cont__22_7, &frame__22_2, 363, 363, 5, 38},
  {cont__22_8, &frame__22_2, 363, 363, 38, 38},
  {entry__22_1, NULL, 357, 363, 3, 38},
  {cont__22_9, &frame__22_1, 364, 364, 3, 17},
  {entry__23_3, NULL, 369, 369, 12, 26},
  {cont__23_4, &frame__23_3, 369, 369, 28, 47},
  {cont__23_5, &frame__23_3, 369, 369, 8, 48},
  {cont__23_6, &frame__23_3, 369, 369, 5, 49},
  {entry__23_16, NULL, 377, 377, 13, 37},
  {cont__23_17, &frame__23_16, 377, 377, 13, 47},
  {cont__23_18, &frame__23_16, 377, 377, 52, 68},
  {cont__23_19, &frame__23_16, 377, 377, 13, 68},
  {cont__23_20, &frame__23_16, 377, 377, 13, 68},
  {entry__23_13, NULL, 376, 376, 13, 45},
  {cont__23_14, &frame__23_13, 376, 376, 13, 50},
  {cont__23_15, &frame__23_13, 377, 377, 13, 68},
  {cont__23_21, &frame__23_13, },
  {entry__23_23, NULL, 379, 379, 29, 45},
  {cont__23_24, &frame__23_23, 379, 379, 47, 60},
  {cont__23_26, &frame__23_23, 379, 379, 13, 70},
  {entry__23_10, NULL, 375, 375, 13, 29},
  {cont__23_12, &frame__23_10, },
  {cont__23_22, &frame__23_10, 373, 379, 9, 71},
  {entry__23_30, NULL, 382, 382, 67, 67},
  {cont__23_31, &frame__23_30, 382, 382, 35, 68},
  {cont__23_32, &frame__23_30, 382, 382, 11, 78},
  {entry__23_27, NULL, 380, 380, 23, 39},
  {cont__23_28, &frame__23_27, 380, 380, 12, 39},
  {cont__23_29, &frame__23_27, 380, 382, 9, 78},
  {entry__23_34, NULL, 383, 383, 24, 38},
  {cont__23_35, &frame__23_34, 383, 383, 40, 59},
  {cont__23_36, &frame__23_34, 383, 383, 20, 60},
  {cont__23_37, &frame__23_34, 383, 383, 17, 61},
  {entry__23_33, NULL, 383, 383, 9, 61},
  {entry__23_7, NULL, 371, 371, 16, 40},
  {cont__23_8, &frame__23_7, 371, 371, 7, 50},
  {cont__23_9, &frame__23_7, 372, 383, 7, 61},
  {entry__23_1, NULL, 368, 368, 5, 35},
  {cont__23_2, &frame__23_1, 367, 383, 3, 63},
  {entry__24_3, NULL, 387, 387, 51, 51},
  {cont__24_4, &frame__24_3, 387, 387, 18, 52},
  {cont__24_5, &frame__24_3, 387, 387, 5, 52},
  {entry__24_13, NULL, 391, 391, 33, 57},
  {cont__24_14, &frame__24_13, 391, 391, 15, 58},
  {cont__24_15, &frame__24_13, 391, 391, 5, 58},
  {cont__24_16, &frame__24_13, 391, 391, 58, 58},
  {entry__24_19, NULL, 393, 393, 15, 63},
  {cont__24_22, &frame__24_19, 393, 393, 5, 63},
  {cont__24_23, &frame__24_19, 393, 393, 63, 63},
  {entry__24_26, NULL, 395, 395, 15, 58},
  {cont__24_29, &frame__24_26, 395, 395, 5, 58},
  {cont__24_30, &frame__24_26, 395, 395, 58, 58},
  {entry__24_1, NULL, 386, 386, 6, 31},
  {cont__24_2, &frame__24_1, 386, 387, 3, 52},
  {cont__24_6, &frame__24_1, 388, 388, 3, 32},
  {cont__24_8, &frame__24_1, 389, 389, 14, 66},
  {cont__24_11, &frame__24_1, 389, 389, 3, 67},
  {cont__24_12, &frame__24_1, 390, 391, 3, 58},
  {cont__24_17, &frame__24_1, 392, 392, 6, 33},
  {cont__24_18, &frame__24_1, 392, 393, 3, 63},
  {cont__24_24, &frame__24_1, 394, 394, 6, 31},
  {cont__24_25, &frame__24_1, 394, 395, 3, 58},
  {cont__24_31, &frame__24_1, 396, 396, 3, 19},
  {entry__25_3, NULL, 463, 463, 7, 54},
  {entry__25_6, NULL, 401, 401, 33, 45},
  {entry__25_9, NULL, 404, 405, 13, 35},
  {cont__25_11, &frame__25_9, 406, 406, 13, 25},
  {cont__25_12, &frame__25_9, 407, 407, 13, 18},
  {entry__25_18, NULL, 413, 413, 19, 32},
  {cont__25_19, &frame__25_18, 414, 414, 19, 27},
  {entry__25_16, NULL, 412, 412, 20, 47},
  {cont__25_17, &frame__25_16, 412, 414, 17, 27},
  {entry__25_23, NULL, 419, 419, 21, 33},
  {cont__25_24, &frame__25_23, 420, 420, 21, 29},
  {entry__25_30, NULL, 426, 428, 27, 46},
  {cont__25_32, &frame__25_30, 429, 429, 27, 35},
  {entry__25_28, NULL, 425, 425, 28, 55},
  {cont__25_29, &frame__25_28, 425, 429, 25, 35},
  {entry__25_34, NULL, 431, 436, 25, 77},
  {cont__25_36, &frame__25_34, 437, 437, 25, 33},
  {entry__25_40, NULL, 440, 442, 27, 44},
  {cont__25_42, &frame__25_40, 443, 443, 27, 35},
  {entry__25_38, NULL, 439, 439, 28, 53},
  {cont__25_39, &frame__25_38, 439, 443, 25, 35},
  {entry__25_25, NULL, 423, 423, 23, 47},
  {cont__25_26, &frame__25_25, 422, 443, 21, 37},
  {cont__25_43, &frame__25_25, 444, 445, 21, 43},
  {cont__25_45, &frame__25_25, 446, 446, 21, 33},
  {cont__25_46, &frame__25_25, 447, 447, 21, 26},
  {entry__25_47, NULL, 449, 450, 21, 41},
  {cont__25_49, &frame__25_47, 451, 451, 21, 33},
  {cont__25_50, &frame__25_47, 452, 452, 21, 26},
  {entry__25_21, NULL, 417, 417, 19, 51},
  {cont__25_22, &frame__25_21, 416, 452, 17, 27},
  {entry__25_54, NULL, 455, 455, 66, 66},
  {cont__25_55, &frame__25_54, 455, 455, 19, 67},
  {cont__25_56, &frame__25_54, 456, 456, 19, 43},
  {cont__25_57, &frame__25_54, 457, 457, 19, 27},
  {entry__25_52, NULL, 454, 454, 20, 45},
  {cont__25_53, &frame__25_52, 454, 457, 17, 27},
  {entry__25_13, NULL, 410, 410, 15, 39},
  {cont__25_14, &frame__25_13, 409, 457, 13, 29},
  {cont__25_58, &frame__25_13, 458, 459, 13, 32},
  {cont__25_60, &frame__25_13, 460, 460, 13, 25},
  {cont__25_61, &frame__25_13, 461, 461, 13, 18},
  {entry__25_7, NULL, 403, 403, 11, 41},
  {cont__25_8, &frame__25_7, 402, 461, 9, 19},
  {entry__25_4, NULL, 401, 401, 10, 30},
  {cont__25_5, &frame__25_4, 401, 461, 7, 20},
  {entry__25_1, NULL, 400, 400, 5, 24},
  {cont__25_2, &frame__25_1, 399, 463, 3, 55}
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
  // 31: $$program_version undefined
  var._program_version = get__undefined();
  // 32: $$program_copyright undefined
  var._program_copyright = get__undefined();
  // 116: $$command_id undefined
  var._command_id = get__undefined();
  // 117: $$command_id_count 0
  var._command_id_count = number__0;
  // 118: $$command_names empty_list
  var._command_names = get__empty_list();
  // 119: $$command_descriptions empty_list
  var._command_descriptions = get__empty_list();
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__10_1(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // msg: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 34: ... !program_copyright msg
  var._program_copyright = frame->slots[0] /* msg */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__11_1(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // no: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 36: ... !program_version no
  var._program_version = frame->slots[0] /* no */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__12_1(void) {
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
  // 39: $$results empty_list
  ((CELL *)frame->slots[2])->contents /* results */ = get__empty_list();
  // 40: $$parameters empty_list
  ((CELL *)frame->slots[3])->contents /* parameters */ = get__empty_list();
  // 41: ... :
  // 42:   $$idx 1
  // 43:   for_each options: (option)
  // 44:     if
  // 45:       option.is_a_key_value_pair:
  // 46:         inc &idx
  // 47:       :
  // 48:         push &parameters option
  // 49:         delete_at &options idx
  frame->slots[4] /* temp__1 */ = create_closure(entry__12_2, 0);
  // 41: do:
  // 42:   $$idx 1
  // 43:   for_each options: (option)
  // 44:     if
  // 45:       option.is_a_key_value_pair:
  // 46:         inc &idx
  // 47:       :
  // 48:         push &parameters option
  // 49:         delete_at &options idx
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
  // 46: inc &idx
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
  // 48: push &parameters option
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
  // 49: delete_at &options idx
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
  // 45: option.is_a_key_value_pair
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
  // 45: ... :
  // 46:   inc &idx
  frame->slots[5] /* temp__2 */ = create_closure(entry__12_5, 0);
  // 47: :
  // 48:   push &parameters option
  // 49:   delete_at &options idx
  frame->slots[6] /* temp__3 */ = create_closure(entry__12_7, 0);
  // 44: if
  // 45:   option.is_a_key_value_pair:
  // 46:     inc &idx
  // 47:   :
  // 48:     push &parameters option
  // 49:     delete_at &options idx
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
  // 42: $$idx 1
  ((CELL *)frame->slots[2])->contents /* idx */ = number__1;
  // 43: ... : (option)
  // 44:   if
  // 45:     option.is_a_key_value_pair:
  // 46:       inc &idx
  // 47:     :
  // 48:       push &parameters option
  // 49:       delete_at &options idx
  frame->slots[3] /* temp__1 */ = create_closure(entry__12_3, 1);
  // 43: for_each options: (option)
  // 44:   if
  // 45:     option.is_a_key_value_pair:
  // 46:       inc &idx
  // 47:     :
  // 48:       push &parameters option
  // 49:       delete_at &options idx
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
  // 50: ... : (template)
  // 51:   $$result value_of(template)
  // 52:   $$idx 1
  // 53:   if
  // 54:     result == SOME_PARAMETERS:
  // 55:       !result empty_list
  // 56:       for_each options: (option)
  // 57:         if
  // 58:           key_of(option) == key_of(template):
  // 59:             delete_at &options idx
  // ...
  frame->slots[4] /* temp__1 */ = create_closure(entry__12_11, 1);
  // 50: for_each templates: (template)
  // 51:   $$result value_of(template)
  // 52:   $$idx 1
  // 53:   if
  // 54:     result == SOME_PARAMETERS:
  // 55:       !result empty_list
  // 56:       for_each options: (option)
  // 57:         if
  // 58:           key_of(option) == key_of(template):
  // 59:             delete_at &options idx
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
  // 51: $$result value_of(template)
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
  // 52: $$idx 1
  ((CELL *)frame->slots[4])->contents /* idx */ = number__1;
  // 54: result == SOME_PARAMETERS
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
  // 54: ... :
  // 55:   !result empty_list
  // 56:   for_each options: (option)
  // 57:     if
  // 58:       key_of(option) == key_of(template):
  // 59:         delete_at &options idx
  // 60:         push &result value_of(option)
  // 61:       :
  // 62:         inc &idx
  frame->slots[6] /* temp__2 */ = create_closure(entry__12_14, 0);
  // 63: :
  // 64:   for_each options: (option)
  // 65:     if
  // 66:       key_of(option) == key_of(template):
  // 67:         delete_at &options idx
  // 68:         !result value_of(option)
  // 69:       :
  // 70:         inc &idx
  frame->slots[7] /* temp__3 */ = create_closure(entry__12_25, 0);
  // 53: if
  // 54:   result == SOME_PARAMETERS:
  // 55:     !result empty_list
  // 56:     for_each options: (option)
  // 57:       if
  // 58:         key_of(option) == key_of(template):
  // 59:           delete_at &options idx
  // 60:           push &result value_of(option)
  // 61:         :
  // 62:           inc &idx
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
  // 67: delete_at &options idx
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
  // 68: !result value_of(option)
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
  // 70: inc &idx
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
  // 66: key_of(option)
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
  // 66: ... key_of(template)
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
  // 66: key_of(option) == key_of(template)
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
  // 66: ... :
  // 67:   delete_at &options idx
  // 68:   !result value_of(option)
  frame->slots[8] /* temp__4 */ = create_closure(entry__12_30, 0);
  // 69: :
  // 70:   inc &idx
  frame->slots[9] /* temp__5 */ = create_closure(entry__12_33, 0);
  // 65: if
  // 66:   key_of(option) == key_of(template):
  // 67:     delete_at &options idx
  // 68:     !result value_of(option)
  // 69:   :
  // 70:     inc &idx
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
  // 59: delete_at &options idx
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
  // 60: ... value_of(option)
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
  // 60: push &result value_of(option)
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
  // 62: inc &idx
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
  // 58: key_of(option)
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
  // 58: ... key_of(template)
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
  // 58: key_of(option) == key_of(template)
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
  // 58: ... :
  // 59:   delete_at &options idx
  // 60:   push &result value_of(option)
  frame->slots[8] /* temp__4 */ = create_closure(entry__12_19, 0);
  // 61: :
  // 62:   inc &idx
  frame->slots[9] /* temp__5 */ = create_closure(entry__12_23, 0);
  // 57: if
  // 58:   key_of(option) == key_of(template):
  // 59:     delete_at &options idx
  // 60:     push &result value_of(option)
  // 61:   :
  // 62:     inc &idx
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
  // 55: !result empty_list
  ((CELL *)frame->slots[0])->contents /* result */ = get__empty_list();
  // 56: ... : (option)
  // 57:   if
  // 58:     key_of(option) == key_of(template):
  // 59:       delete_at &options idx
  // 60:       push &result value_of(option)
  // 61:     :
  // 62:       inc &idx
  frame->slots[4] /* temp__1 */ = create_closure(entry__12_15, 1);
  // 56: for_each options: (option)
  // 57:   if
  // 58:     key_of(option) == key_of(template):
  // 59:       delete_at &options idx
  // 60:       push &result value_of(option)
  // 61:     :
  // 62:       inc &idx
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
  // 64: ... : (option)
  // 65:   if
  // 66:     key_of(option) == key_of(template):
  // 67:       delete_at &options idx
  // 68:       !result value_of(option)
  // 69:     :
  // 70:       inc &idx
  frame->slots[4] /* temp__1 */ = create_closure(entry__12_26, 1);
  // 64: for_each options: (option)
  // 65:   if
  // 66:     key_of(option) == key_of(template):
  // 67:       delete_at &options idx
  // 68:       !result value_of(option)
  // 69:     :
  // 70:       inc &idx
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
  // 71: push &results result
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
  // 72: ... options.is_empty
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
  // 72: ... :
  // 73:   Error "Invalid option @(range(debug_string(key_of(options(1))) 1 -2))!"
  frame->slots[5] /* temp__2 */ = create_closure(entry__12_39, 0);
  // 72: unless options.is_empty:
  // 73:   Error "Invalid option @(range(debug_string(key_of(options(1))) 1 -2))!"
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
  // 73: ... options(1)
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
  // 73: ... key_of(options(1))
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
  // 73: ... debug_string(key_of(options(1)))
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
  // 73: ... 2
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
  // 73: ... range(debug_string(key_of(options(1))) 1 -2)
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
  // 73: ... "Invalid option @(range(debug_string(key_of(options(1))) 1 -2))!"
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
  // 73: Error "Invalid option @(range(debug_string(key_of(options(1))) 1 -2))!"
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
  // 74: -> results* parameters*
  argument_count = 0;
  arguments = node_p;
  unfold(((CELL *)frame->slots[2])->contents /* results */);
  unfold(((CELL *)frame->slots[3])->contents /* parameters */);
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__13_1(void) {
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
  // 81: $$results empty_list
  ((CELL *)frame->slots[2])->contents /* results */ = get__empty_list();
  // 82: ... : (template)
  // 83:   $$result value_of(template)
  // 84:   $$idx 1
  // 85:   if
  // 86:     result == SOME_PARAMETERS:
  // 87:       !result empty_list
  // 88:       for_each options: (option)
  // 89:         if
  // 90:           key_of(option) == key_of(template):
  // 91:             delete_at &options idx
  // ...
  frame->slots[3] /* temp__1 */ = create_closure(entry__13_2, 1);
  // 82: for_each templates: (template)
  // 83:   $$result value_of(template)
  // 84:   $$idx 1
  // 85:   if
  // 86:     result == SOME_PARAMETERS:
  // 87:       !result empty_list
  // 88:       for_each options: (option)
  // 89:         if
  // 90:           key_of(option) == key_of(template):
  // 91:             delete_at &options idx
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
  // 83: $$result value_of(template)
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
  // 84: $$idx 1
  ((CELL *)frame->slots[4])->contents /* idx */ = number__1;
  // 86: result == SOME_PARAMETERS
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
  // 86: ... :
  // 87:   !result empty_list
  // 88:   for_each options: (option)
  // 89:     if
  // 90:       key_of(option) == key_of(template):
  // 91:         delete_at &options idx
  // 92:         push &result value_of(option)
  // 93:       :
  // 94:         inc &idx
  frame->slots[6] /* temp__2 */ = create_closure(entry__13_5, 0);
  //  95: :
  //  96:   for_each options: (option)
  //  97:     if
  //  98:       option.is_a_key_value_pair && key_of(option) == key_of(template):
  //  99:         delete_at &options idx
  // 100:         !result value_of(option)
  // 101:       :
  // 102:         inc &idx
  frame->slots[7] /* temp__3 */ = create_closure(entry__13_16, 0);
  // 85: if
  // 86:   result == SOME_PARAMETERS:
  // 87:     !result empty_list
  // 88:     for_each options: (option)
  // 89:       if
  // 90:         key_of(option) == key_of(template):
  // 91:           delete_at &options idx
  // 92:           push &result value_of(option)
  // 93:         :
  // 94:           inc &idx
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
  // 99: delete_at &options idx
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
  // 100: !result value_of(option)
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
  // 102: inc &idx
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
  // 98: option.is_a_key_value_pair
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
  // 98: ... key_of(option) == key_of(template)
  frame->slots[7] /* temp__3 */ = create_closure(entry__13_19, 0);
  // 98: option.is_a_key_value_pair && key_of(option) == key_of(template)
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
  // 98: ... key_of(option)
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
  // 98: ... key_of(template)
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
  // 98: ... key_of(option) == key_of(template)
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
  // 98: ... key_of(option) == key_of(template)
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
  //  98: ... :
  //  99:   delete_at &options idx
  // 100:   !result value_of(option)
  frame->slots[8] /* temp__4 */ = create_closure(entry__13_24, 0);
  // 101: :
  // 102:   inc &idx
  frame->slots[9] /* temp__5 */ = create_closure(entry__13_27, 0);
  //  97: if
  //  98:   option.is_a_key_value_pair && key_of(option) == key_of(template):
  //  99:     delete_at &options idx
  // 100:     !result value_of(option)
  // 101:   :
  // 102:     inc &idx
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
  // 91: delete_at &options idx
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
  // 92: ... value_of(option)
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
  // 92: push &result value_of(option)
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
  // 94: inc &idx
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
  // 90: key_of(option)
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
  // 90: ... key_of(template)
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
  // 90: key_of(option) == key_of(template)
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
  // 90: ... :
  // 91:   delete_at &options idx
  // 92:   push &result value_of(option)
  frame->slots[8] /* temp__4 */ = create_closure(entry__13_10, 0);
  // 93: :
  // 94:   inc &idx
  frame->slots[9] /* temp__5 */ = create_closure(entry__13_14, 0);
  // 89: if
  // 90:   key_of(option) == key_of(template):
  // 91:     delete_at &options idx
  // 92:     push &result value_of(option)
  // 93:   :
  // 94:     inc &idx
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
  // 87: !result empty_list
  ((CELL *)frame->slots[0])->contents /* result */ = get__empty_list();
  // 88: ... : (option)
  // 89:   if
  // 90:     key_of(option) == key_of(template):
  // 91:       delete_at &options idx
  // 92:       push &result value_of(option)
  // 93:     :
  // 94:       inc &idx
  frame->slots[4] /* temp__1 */ = create_closure(entry__13_6, 1);
  // 88: for_each options: (option)
  // 89:   if
  // 90:     key_of(option) == key_of(template):
  // 91:       delete_at &options idx
  // 92:       push &result value_of(option)
  // 93:     :
  // 94:       inc &idx
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
  //  96: ... : (option)
  //  97:   if
  //  98:     option.is_a_key_value_pair && key_of(option) == key_of(template):
  //  99:       delete_at &options idx
  // 100:       !result value_of(option)
  // 101:     :
  // 102:       inc &idx
  frame->slots[4] /* temp__1 */ = create_closure(entry__13_17, 1);
  //  96: for_each options: (option)
  //  97:   if
  //  98:     option.is_a_key_value_pair && key_of(option) == key_of(template):
  //  99:       delete_at &options idx
  // 100:       !result value_of(option)
  // 101:     :
  // 102:       inc &idx
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
  // 103: push &results result
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
  // 104: -> results*
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
  // 113: ... idx != 1
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
  // 113: ... idx != 1
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
  // 113: ... : ewrite " " .dup. 2+first_column_width
  frame->slots[5] /* temp__3 */ = create_closure(entry__14_17, 0);
  // 113: if idx != 1: ewrite " " .dup. 2+first_column_width
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
  // 113: ... 2+first_column_width
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
  // 113: ... " " .dup. 2+first_column_width
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
  // 113: ... ewrite " " .dup. 2+first_column_width
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
  // 114: ewriteln line
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
  // 111: ... entry(1)
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
  // 111: ... pad_right(entry(1) first_column_width)
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
  // 111: ewrite "  " pad_right(entry(1) first_column_width)
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
  // 112: ... entry(2)
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
  // 112: ... : (idx line)
  // 113:   if idx != 1: ewrite " " .dup. 2+first_column_width
  // 114:   ewriteln line
  frame->slots[3] /* temp__2 */ = create_closure(entry__14_14, 2);
  // 112: for_each_line entry(2): (idx line)
  // 113:   if idx != 1: ewrite " " .dup. 2+first_column_width
  // 114:   ewriteln line
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__for_each_line();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__14_1(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // tab: 0
  // first_column_width: 1
  frame->slots[1] /* first_column_width */ = create_cell();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 107: $$first_column_width 0
  ((CELL *)frame->slots[1])->contents /* first_column_width */ = number__0;
  // 108: ... : (entry) extend_to &first_column_width length_of(entry(1))
  frame->slots[2] /* temp__1 */ = create_closure(entry__14_2, 1);
  // 108: for_each tab: (entry) extend_to &first_column_width length_of(entry(1))
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
  // 108: ... entry(1)
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
  // 108: ... length_of(entry(1))
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
  // 108: ... extend_to &first_column_width length_of(entry(1))
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
  // 109: plus &first_column_width 2
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
  // 110: ... : (entry)
  // 111:   ewrite "  " pad_right(entry(1) first_column_width)
  // 112:   for_each_line entry(2): (idx line)
  // 113:     if idx != 1: ewrite " " .dup. 2+first_column_width
  // 114:     ewriteln line
  frame->slots[2] /* temp__1 */ = create_closure(entry__14_8, 1);
  // 110: for_each tab: (entry)
  // 111:   ewrite "  " pad_right(entry(1) first_column_width)
  // 112:   for_each_line entry(2): (idx line)
  // 113:     if idx != 1: ewrite " " .dup. 2+first_column_width
  // 114:     ewriteln line
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* tab */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__19_1(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // command_name: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 122: ... "@(command_name) @(program_version)@nl;@nl;"
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* command_name */;
  arguments->slots[1] = string__19_2;
  arguments->slots[2] = var._program_version;
  arguments->slots[3] = string__19_3;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__19_4;
}
static void cont__19_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 122: ewrite "@(command_name) @(program_version)@nl;@nl;"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__ewrite();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__20_1(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 124: ... ewrite program_copyright
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._program_copyright;
  result_count = frame->caller_result_count;
  myself = get__ewrite();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__21_1(void) {
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
  // 139: ... : (idx)
  // 140:   $$message help_messages(idx)
  // 141:   $possible_value possible_values(idx)
  // 142:   if possible_value.is_defined:
  // 143:     append &message "valid values:"
  // 144:     for_each possible_value: (value) write_to &message ' ' value ','
  // 145:     !message(-1) '@nl;'
  // 146:   -> message
  frame->slots[18] /* temp__1 */ = create_closure(entry__21_2, 1);
  // 139: $help_message: (idx)
  // 140:   $$message help_messages(idx)
  // 141:   $possible_value possible_values(idx)
  // 142:   if possible_value.is_defined:
  // 143:     append &message "valid values:"
  // 144:     for_each possible_value: (value) write_to &message ' ' value ','
  // 145:     !message(-1) '@nl;'
  // 146:   -> message
  initialize_future(frame->slots[13] /* help_message */, frame->slots[18] /* temp__1 */);
  // 148: ... :
  // 149:   $parameter_name: (parameter idx)
  // 150:     $$buf parameter.to_upper_case
  // 151:     case
  // 152:       kinds(idx)
  // 153:       OPTIONAL_PARAMETER:
  // 154:         push &buf '?'
  // 155:       SOME_PARAMETERS:
  // 156:         push &buf '*'
  // 157:       MANY_PARAMETERS:
  // ...
  frame->slots[18] /* temp__1 */ = create_closure(entry__21_15, 0);
  // 148: $show_usage:
  // 149:   $parameter_name: (parameter idx)
  // 150:     $$buf parameter.to_upper_case
  // 151:     case
  // 152:       kinds(idx)
  // 153:       OPTIONAL_PARAMETER:
  // 154:         push &buf '?'
  // 155:       SOME_PARAMETERS:
  // 156:         push &buf '*'
  // 157:       MANY_PARAMETERS:
  // ...
  initialize_future(frame->slots[14] /* show_usage */, frame->slots[18] /* temp__1 */);
  // 204: ... :
  // 205:   if
  // 206:     command.is_defined:
  // 207:       ewriteln "
  // 208:         Too few arguments for @(command)-command!
  // 209:     :
  // 210:       ewriteln "
  // 211:         Too few arguments!
  // 212:   show_usage
  // 213:   exit 1
  frame->slots[18] /* temp__1 */ = create_closure(entry__21_91, 0);
  // 204: $too_few_arguments_error:
  // 205:   if
  // 206:     command.is_defined:
  // 207:       ewriteln "
  // 208:         Too few arguments for @(command)-command!
  // 209:     :
  // 210:       ewriteln "
  // 211:         Too few arguments!
  // 212:   show_usage
  // 213:   exit 1
  initialize_future(frame->slots[15] /* too_few_arguments_error */, frame->slots[18] /* temp__1 */);
  // 215: ... :
  // 216:   ewriteln "
  // 217:     Too many arguments!
  // 218:   show_usage
  // 219:   exit 1
  frame->slots[18] /* temp__1 */ = create_closure(entry__21_101, 0);
  // 215: $too_many_arguments_error:
  // 216:   ewriteln "
  // 217:     Too many arguments!
  // 218:   show_usage
  // 219:   exit 1
  initialize_future(frame->slots[16] /* too_many_arguments_error */, frame->slots[18] /* temp__1 */);
  // 127: $$results empty_list
  ((CELL *)frame->slots[3])->contents /* results */ = get__empty_list();
  // 128: $$options empty_key_order_table
  ((CELL *)frame->slots[4])->contents /* options */ = get__empty_key_order_table();
  // 129: $$parameters empty_insert_order_table
  ((CELL *)frame->slots[5])->contents /* parameters */ = get__empty_insert_order_table();
  // 130: $$names empty_list
  ((CELL *)frame->slots[6])->contents /* names */ = get__empty_list();
  // 131: $$kinds empty_list
  ((CELL *)frame->slots[7])->contents /* kinds */ = get__empty_list();
  // 132: $$possible_values empty_list
  ((CELL *)frame->slots[8])->contents /* possible_values */ = get__empty_list();
  // 133: $$default_values empty_list
  ((CELL *)frame->slots[9])->contents /* default_values */ = get__empty_list();
  // 134: $$conversions empty_list
  ((CELL *)frame->slots[10])->contents /* conversions */ = get__empty_list();
  // 135: $$help_messages empty_list
  ((CELL *)frame->slots[11])->contents /* help_messages */ = get__empty_list();
  // 136: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__21_105;
}
static void entry__21_73(void) {
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
  // 189: $$tab empty_list
  ((CELL *)frame->slots[3])->contents /* tab */ = get__empty_list();
  // 190: ... : (option idx)
  // 191:   $option_name:
  // 192:     $$buf string("--" option)
  // 193:     case
  // 194:       kinds(idx)
  // 195:       VALUED_OPTION:
  // 196:         append &buf " VALUE"
  // 197:       MULTI_VALUED_OPTION:
  // 198:         append &buf " VALUES"
  // 199:     -> buf
  // ...
  frame->slots[4] /* temp__1 */ = create_closure(entry__21_74, 2);
  // 190: for_each options: (option idx)
  // 191:   $option_name:
  // 192:     $$buf string("--" option)
  // 193:     case
  // 194:       kinds(idx)
  // 195:       VALUED_OPTION:
  // 196:         append &buf " VALUE"
  // 197:       MULTI_VALUED_OPTION:
  // 198:         append &buf " VALUES"
  // 199:     -> buf
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* options */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__21_90;
}
static void entry__21_74(void) {
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
  // 191: ... :
  // 192:   $$buf string("--" option)
  // 193:   case
  // 194:     kinds(idx)
  // 195:     VALUED_OPTION:
  // 196:       append &buf " VALUE"
  // 197:     MULTI_VALUED_OPTION:
  // 198:       append &buf " VALUES"
  // 199:   -> buf
  frame->slots[6] /* temp__1 */ = create_closure(entry__21_75, 0);
  // 191: $option_name:
  // 192:   $$buf string("--" option)
  // 193:   case
  // 194:     kinds(idx)
  // 195:     VALUED_OPTION:
  // 196:       append &buf " VALUE"
  // 197:     MULTI_VALUED_OPTION:
  // 198:       append &buf " VALUES"
  // 199:   -> buf
  initialize_future(frame->slots[5] /* option_name */, frame->slots[6] /* temp__1 */);
  // 201: ... option_name()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = frame->slots[5] /* option_name */;
  func = myself->type;
  frame->cont = cont__21_86;
}
static void entry__21_75(void) {
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
  // 192: $$buf string("--" option)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__21_76;
  arguments->slots[1] = frame->slots[0] /* option */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__21_77;
}
static void cont__21_77(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* buf */ = arguments->slots[0];
  // 194: kinds(idx)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* idx */;
  result_count = 1;
  myself = ((CELL *)frame->slots[1])->contents /* kinds */;
  func = myself->type;
  frame->cont = cont__21_78;
}
static void cont__21_78(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 195: ... :
  // 196:   append &buf " VALUE"
  frame->slots[5] /* temp__2 */ = create_closure(entry__21_79, 0);
  // 197: ... :
  // 198:   append &buf " VALUES"
  frame->slots[6] /* temp__3 */ = create_closure(entry__21_82, 0);
  // 193: case
  // 194:   kinds(idx)
  // 195:   VALUED_OPTION:
  // 196:     append &buf " VALUE"
  // 197:   MULTI_VALUED_OPTION:
  // 198:     append &buf " VALUES"
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
  frame->cont = cont__21_85;
}
static void entry__21_79(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // buf: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* buf */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 196: append &buf " VALUE"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* buf */;
  arguments->slots[1] = string__21_80;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__21_81;
}
static void cont__21_81(void) {
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
static void entry__21_82(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // buf: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* buf */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 198: append &buf " VALUES"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* buf */;
  arguments->slots[1] = string__21_83;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__21_84;
}
static void cont__21_84(void) {
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
static void cont__21_85(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 199: -> buf
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* buf */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__21_86(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 201: ... help_messages(idx)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* idx */;
  result_count = 1;
  myself = ((CELL *)frame->slots[4])->contents /* help_messages */;
  func = myself->type;
  frame->cont = cont__21_87;
}
static void cont__21_87(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__3 */ = arguments->slots[0];
  // 201: ... list(option_name() help_messages(idx))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__2 */;
  arguments->slots[1] = frame->slots[8] /* temp__3 */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__21_88;
}
static void cont__21_88(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 201: push &tab list(option_name() help_messages(idx))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* tab */;
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__21_89;
}
static void cont__21_89(void) {
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
static void cont__21_90(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 202: display_table tab
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* tab */;
  result_count = frame->caller_result_count;
  myself = var._display_table;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__21_70(void) {
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
  // 185: ewrite "
  // 186:   
  // 187:   Options:
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__21_71;
  result_count = 0;
  myself = get__ewrite();
  func = myself->type;
  frame->cont = cont__21_72;
}
static void cont__21_72(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 188: ... :
  // 189:   $$tab empty_list
  // 190:   for_each options: (option idx)
  // 191:     $option_name:
  // 192:       $$buf string("--" option)
  // 193:       case
  // 194:         kinds(idx)
  // 195:         VALUED_OPTION:
  // 196:           append &buf " VALUE"
  // 197:         MULTI_VALUED_OPTION:
  // ...
  frame->slots[3] /* temp__1 */ = create_closure(entry__21_73, 0);
  // 188: do:
  // 189:   $$tab empty_list
  // 190:   for_each options: (option idx)
  // 191:     $option_name:
  // 192:       $$buf string("--" option)
  // 193:       case
  // 194:         kinds(idx)
  // 195:         VALUED_OPTION:
  // 196:           append &buf " VALUE"
  // 197:         MULTI_VALUED_OPTION:
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__do();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__21_2(void) {
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
  // 140: $$message help_messages(idx)
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
  // 141: $possible_value possible_values(idx)
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
  // 142: ... possible_value.is_defined
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
  // 142: ... :
  // 143:   append &message "valid values:"
  // 144:   for_each possible_value: (value) write_to &message ' ' value ','
  // 145:   !message(-1) '@nl;'
  frame->slots[6] /* temp__2 */ = create_closure(entry__21_6, 0);
  // 142: if possible_value.is_defined:
  // 143:   append &message "valid values:"
  // 144:   for_each possible_value: (value) write_to &message ' ' value ','
  // 145:   !message(-1) '@nl;'
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
  // 143: append &message "valid values:"
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
  // 144: ... : (value) write_to &message ' ' value ','
  frame->slots[2] /* temp__1 */ = create_closure(entry__21_9, 1);
  // 144: for_each possible_value: (value) write_to &message ' ' value ','
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
  // 144: ... write_to &message ' ' value ','
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
  // 145: !message(-1) '@nl;'
  frame->slots[2] /* temp__1 */ = character__10;
  // 145: ... 1
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
  // 145: !message(-1)
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
  // 146: -> message
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* message */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__21_15(void) {
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
  // 149: ... : (parameter idx)
  // 150:   $$buf parameter.to_upper_case
  // 151:   case
  // 152:     kinds(idx)
  // 153:     OPTIONAL_PARAMETER:
  // 154:       push &buf '?'
  // 155:     SOME_PARAMETERS:
  // 156:       push &buf '*'
  // 157:     MANY_PARAMETERS:
  // 158:       push &buf '+'
  // ...
  frame->slots[8] /* temp__1 */ = create_closure(entry__21_16, 2);
  // 149: $parameter_name: (parameter idx)
  // 150:   $$buf parameter.to_upper_case
  // 151:   case
  // 152:     kinds(idx)
  // 153:     OPTIONAL_PARAMETER:
  // 154:       push &buf '?'
  // 155:     SOME_PARAMETERS:
  // 156:       push &buf '*'
  // 157:     MANY_PARAMETERS:
  // 158:       push &buf '+'
  // ...
  initialize_future(frame->slots[7] /* parameter_name */, frame->slots[8] /* temp__1 */);
  // 161: ... program_version.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._program_version;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__21_26;
}
static void entry__21_16(void) {
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
  // 150: $$buf parameter.to_upper_case
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
  // 152: kinds(idx)
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
  // 153: ... :
  // 154:   push &buf '?'
  frame->slots[5] /* temp__2 */ = create_closure(entry__21_19, 0);
  // 155: ... :
  // 156:   push &buf '*'
  frame->slots[6] /* temp__3 */ = create_closure(entry__21_21, 0);
  // 157: ... :
  // 158:   push &buf '+'
  frame->slots[7] /* temp__4 */ = create_closure(entry__21_23, 0);
  // 151: case
  // 152:   kinds(idx)
  // 153:   OPTIONAL_PARAMETER:
  // 154:     push &buf '?'
  // 155:   SOME_PARAMETERS:
  // 156:     push &buf '*'
  // 157:   MANY_PARAMETERS:
  // 158:     push &buf '+'
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
  // 154: push &buf '?'
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
  // 156: push &buf '*'
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
  // 158: push &buf '+'
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
  // 159: -> buf
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
  // 161: ... : show_version command_name
  frame->slots[9] /* temp__2 */ = create_closure(entry__21_27, 0);
  // 161: if program_version.is_defined: show_version command_name
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
  // 161: ... show_version command_name
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
  // 162: ... command_id.is_defined
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
  // 162: ... :
  // 163:   ewriteln command_name ' ' command
  // 164:   ewriteln indented(2 command_descriptions(command_id))
  frame->slots[9] /* temp__2 */ = create_closure(entry__21_30, 0);
  // 162: if command_id.is_defined:
  // 163:   ewriteln command_name ' ' command
  // 164:   ewriteln indented(2 command_descriptions(command_id))
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
  // 163: ewriteln command_name ' ' command
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
  // 164: ... command_descriptions(command_id)
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
  // 164: ... indented(2 command_descriptions(command_id))
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
  // 164: ewriteln indented(2 command_descriptions(command_id))
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
  // 165: ewriteln "Usage:"
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
  // 166: ... command.is_defined
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
  // 166: ... :
  // 167:   if program_copyright.is_defined: ewriteln "  " command_name " --copyright"
  // 168:   ewriteln "  " command_name " --help"
  frame->slots[9] /* temp__2 */ = create_closure(entry__21_38, 0);
  // 166: unless command.is_defined:
  // 167:   if program_copyright.is_defined: ewriteln "  " command_name " --copyright"
  // 168:   ewriteln "  " command_name " --help"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__1 */;
  arguments->slots[1] = frame->slots[9] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__21_46;
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
  // 167: ... program_copyright.is_defined
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
  // 167: ... : ewriteln "  " command_name " --copyright"
  frame->slots[2] /* temp__2 */ = create_closure(entry__21_40, 0);
  // 167: if program_copyright.is_defined: ewriteln "  " command_name " --copyright"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__21_43;
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
  // 167: ... ewriteln "  " command_name " --copyright"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__21_41;
  arguments->slots[1] = frame->slots[0] /* command_name */;
  arguments->slots[2] = string__21_42;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__21_43(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 168: ewriteln "  " command_name " --help"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__21_44;
  arguments->slots[1] = frame->slots[0] /* command_name */;
  arguments->slots[2] = string__21_45;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__21_46(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 172: ... command.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* command */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__21_47;
}
static void cont__21_47(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__2 */ = arguments->slots[0];
  // 172: ... -> string(' ' command)
  frame->slots[10] /* temp__3 */ = create_closure(entry__21_48, 0);
  // 172: if(command.is_defined (-> string(' ' command)) -> "")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__2 */;
  arguments->slots[1] = frame->slots[10] /* temp__3 */;
  arguments->slots[2] = func__21_50;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__21_51;
}
static void entry__21_48(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // command: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* command */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 172: ... string(' ' command)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__32;
  arguments->slots[1] = frame->slots[0] /* command */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__21_49;
}
static void cont__21_49(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 172: ... -> string(' ' command)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__21_50(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 172: ... -> ""
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = empty_string;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__21_51(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__1 */ = arguments->slots[0];
  // 169: ewrite
  // 170:   "  "
  // 171:   command_name
  // 172:   if(command.is_defined (-> string(' ' command)) -> "")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__21_52;
  arguments->slots[1] = frame->slots[1] /* command_name */;
  arguments->slots[2] = frame->slots[8] /* temp__1 */;
  result_count = 0;
  myself = get__ewrite();
  func = myself->type;
  frame->cont = cont__21_53;
}
static void cont__21_53(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 173: ... : (parameter idx)
  // 174:   ewrite " " parameter_name(parameter idx)
  frame->slots[8] /* temp__1 */ = create_closure(entry__21_54, 2);
  // 173: for_each parameters: (parameter idx)
  // 174:   ewrite " " parameter_name(parameter idx)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* parameters */;
  arguments->slots[1] = frame->slots[8] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__21_57;
}
static void entry__21_54(void) {
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
  // 174: ... parameter_name(parameter idx)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* parameter */;
  arguments->slots[1] = frame->slots[1] /* idx */;
  result_count = 1;
  myself = frame->slots[2] /* parameter_name */;
  func = myself->type;
  frame->cont = cont__21_55;
}
static void cont__21_55(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 174: ewrite " " parameter_name(parameter idx)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__21_56;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__ewrite();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__21_57(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 175: ewriteln
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = get__ewriteln();
  func = myself->type;
  frame->cont = cont__21_58;
}
static void cont__21_58(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 176: ewrite "
  // 177:   
  // 178:   Parameters:
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__21_59;
  result_count = 0;
  myself = get__ewrite();
  func = myself->type;
  frame->cont = cont__21_60;
}
static void cont__21_60(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 179: ... :
  // 180:   $$tab empty_list
  // 181:   for_each parameters: (parameter idx)
  // 182:     push &tab list(parameter_name(parameter idx) help_message(idx))
  // 183:   display_table tab
  frame->slots[8] /* temp__1 */ = create_closure(entry__21_61, 0);
  // 179: do:
  // 180:   $$tab empty_list
  // 181:   for_each parameters: (parameter idx)
  // 182:     push &tab list(parameter_name(parameter idx) help_message(idx))
  // 183:   display_table tab
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__1 */;
  result_count = 0;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__21_68;
}
static void entry__21_61(void) {
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
  // 180: $$tab empty_list
  ((CELL *)frame->slots[3])->contents /* tab */ = get__empty_list();
  // 181: ... : (parameter idx)
  // 182:   push &tab list(parameter_name(parameter idx) help_message(idx))
  frame->slots[4] /* temp__1 */ = create_closure(entry__21_62, 2);
  // 181: for_each parameters: (parameter idx)
  // 182:   push &tab list(parameter_name(parameter idx) help_message(idx))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* parameters */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__21_67;
}
static void entry__21_62(void) {
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
  // 182: ... parameter_name(parameter idx)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* parameter */;
  arguments->slots[1] = frame->slots[1] /* idx */;
  result_count = 1;
  myself = frame->slots[3] /* parameter_name */;
  func = myself->type;
  frame->cont = cont__21_63;
}
static void cont__21_63(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 182: ... help_message(idx)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* idx */;
  result_count = 1;
  myself = frame->slots[4] /* help_message */;
  func = myself->type;
  frame->cont = cont__21_64;
}
static void cont__21_64(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__3 */ = arguments->slots[0];
  // 182: ... list(parameter_name(parameter idx) help_message(idx))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__21_65;
}
static void cont__21_65(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 182: push &tab list(parameter_name(parameter idx) help_message(idx))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* tab */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__21_66;
}
static void cont__21_66(void) {
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
static void cont__21_67(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 183: display_table tab
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* tab */;
  result_count = frame->caller_result_count;
  myself = var._display_table;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__21_68(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 184: ... options.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[5])->contents /* options */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__21_69;
}
static void cont__21_69(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__1 */ = arguments->slots[0];
  // 184: ... :
  // 185:   ewrite "
  // 186:     
  // 187:     Options:
  // 188:   do:
  // 189:     $$tab empty_list
  // 190:     for_each options: (option idx)
  // 191:       $option_name:
  // 192:         $$buf string("--" option)
  // 193:         case
  // ...
  frame->slots[9] /* temp__2 */ = create_closure(entry__21_70, 0);
  // 184: unless options.is_empty:
  // 185:   ewrite "
  // 186:     
  // 187:     Options:
  // 188:   do:
  // 189:     $$tab empty_list
  // 190:     for_each options: (option idx)
  // 191:       $option_name:
  // 192:         $$buf string("--" option)
  // 193:         case
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
static void entry__21_91(void) {
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
  // 206: command.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* command */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__21_92;
}
static void cont__21_92(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 206: ... :
  // 207:   ewriteln "
  // 208:     Too few arguments for @(command)-command!
  frame->slots[3] /* temp__2 */ = create_closure(entry__21_93, 0);
  // 205: if
  // 206:   command.is_defined:
  // 207:     ewriteln "
  // 208:       Too few arguments for @(command)-command!
  // 209:   :
  // 210:     ewriteln "
  // 211:       Too few arguments!
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  arguments->slots[2] = func__21_97;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__21_99;
}
static void entry__21_93(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // command: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* command */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 207: ... "
  // 208:   Too few arguments for @(command)-command!
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__21_94;
  arguments->slots[1] = frame->slots[0] /* command */;
  arguments->slots[2] = string__21_95;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__21_96;
}
static void cont__21_96(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 207: ewriteln "
  // 208:   Too few arguments for @(command)-command!
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__21_97(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 210: ewriteln "
  // 211:   Too few arguments!
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__21_98;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__21_99(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 212: show_usage
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = frame->slots[1] /* show_usage */;
  func = myself->type;
  frame->cont = cont__21_100;
}
static void cont__21_100(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 213: exit 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = frame->caller_result_count;
  myself = get__exit();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__21_101(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // show_usage: 0
  frame->slots[0] = myself->closure.frame->slots[14]; /* show_usage */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 216: ewriteln "
  // 217:   Too many arguments!
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__21_102;
  result_count = 0;
  myself = get__ewriteln();
  func = myself->type;
  frame->cont = cont__21_103;
}
static void cont__21_103(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 218: show_usage
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = frame->slots[0] /* show_usage */;
  func = myself->type;
  frame->cont = cont__21_104;
}
static void cont__21_104(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 219: exit 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = frame->caller_result_count;
  myself = get__exit();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__21_105(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[18] /* temp__1 */ = arguments->slots[0];
  // 136: $command_name truncate_until(program_name '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__program_name();
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[18] /* temp__1 */;
  result_count = 1;
  myself = get__truncate_until();
  func = myself->type;
  frame->cont = cont__21_106;
}
static void cont__21_106(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[12] /* command_name */, arguments->slots[0]);
  // 137: map &arguments from_utf8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* arguments */;
  arguments->slots[1] = get__from_utf8();
  result_count = 1;
  myself = get__map();
  func = myself->type;
  frame->cont = cont__21_107;
}
static void cont__21_107(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* arguments */ = arguments->slots[0];
  // 221: ... : (idx template)
  // 222:   template $$option $name? $default_value? $conversion? $help
  // 223:   if
  // 224:     option.is_a_key_value_pair:
  // 225:       push &possible_values value_of(option)
  // 226:       !option key_of(option)
  // 227:     :
  // 228:       push &possible_values undefined
  // 229:   push &names if(name.is_defined (-> name) -> option)
  // 230:   push &kinds option
  // ...
  frame->slots[18] /* temp__1 */ = create_closure(entry__21_108, 2);
  // 221: for_each templates: (idx template)
  // 222:   template $$option $name? $default_value? $conversion? $help
  // 223:   if
  // 224:     option.is_a_key_value_pair:
  // 225:       push &possible_values value_of(option)
  // 226:       !option key_of(option)
  // 227:     :
  // 228:       push &possible_values undefined
  // 229:   push &names if(name.is_defined (-> name) -> option)
  // 230:   push &kinds option
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* templates */;
  arguments->slots[1] = frame->slots[18] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__21_154;
}
static void entry__21_148(void) {
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
  // 246: push &results empty_list
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* results */;
  arguments->slots[1] = get__empty_list();
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__21_149;
}
static void cont__21_149(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* results */ = arguments->slots[0];
  // 247: !parameters(name) idx
  frame->slots[4] /* temp__1 */ = frame->slots[3] /* idx */;
  // 247: !parameters(name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* name */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[1])->contents /* parameters */;
  func = myself->type;
  frame->cont = cont__21_150;
}
static void cont__21_150(void) {
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
static void entry__21_140(void) {
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
  // 243: push &results empty_list
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* results */;
  arguments->slots[1] = get__empty_list();
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__21_141;
}
static void cont__21_141(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* results */ = arguments->slots[0];
  // 244: !options(name) idx
  frame->slots[4] /* temp__1 */ = frame->slots[3] /* idx */;
  // 244: !options(name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* name */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[1])->contents /* options */;
  func = myself->type;
  frame->cont = cont__21_142;
}
static void cont__21_142(void) {
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
static void entry__21_135(void) {
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
  // 240: push &results undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* results */;
  arguments->slots[1] = get__undefined();
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__21_136;
}
static void cont__21_136(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* results */ = arguments->slots[0];
  // 241: !options(name) idx
  frame->slots[4] /* temp__1 */ = frame->slots[3] /* idx */;
  // 241: !options(name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* name */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[1])->contents /* options */;
  func = myself->type;
  frame->cont = cont__21_137;
}
static void cont__21_137(void) {
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
static void entry__21_129(void) {
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
  // 236: push &results false
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* results */;
  arguments->slots[1] = get__false();
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__21_130;
}
static void cont__21_130(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* results */ = arguments->slots[0];
  // 237: !options(option) idx
  frame->slots[5] /* temp__1 */ = frame->slots[3] /* idx */;
  // 237: !options(option)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* option */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[1])->contents /* options */;
  func = myself->type;
  frame->cont = cont__21_131;
}
static void cont__21_131(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* options */ = arguments->slots[0];
  // 238: !kinds(idx) BOOLEAN_OPTION
  frame->slots[5] /* temp__1 */ = var._BOOLEAN_OPTION;
  // 238: !kinds(idx)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* idx */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[4])->contents /* kinds */;
  func = myself->type;
  frame->cont = cont__21_132;
}
static void cont__21_132(void) {
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
static void entry__21_127(void) {
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
  // 235: ... option.is_a_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* option */;
  result_count = 1;
  myself = get__is_a_string();
  func = myself->type;
  frame->cont = cont__21_128;
}
static void cont__21_128(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 235: ... :
  // 236:   push &results false
  // 237:   !options(option) idx
  // 238:   !kinds(idx) BOOLEAN_OPTION
  frame->slots[6] /* temp__2 */ = create_closure(entry__21_129, 0);
  // 235: -> option.is_a_string:
  // 236:   push &results false
  // 237:   !options(option) idx
  // 238:   !kinds(idx) BOOLEAN_OPTION
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__21_133(void) {
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
  // 239: ... option == VALUED_OPTION
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* option */;
  arguments->slots[1] = get__VALUED_OPTION();
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__21_134;
}
static void cont__21_134(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 239: ... :
  // 240:   push &results undefined
  // 241:   !options(name) idx
  frame->slots[6] /* temp__2 */ = create_closure(entry__21_135, 0);
  // 239: -> option == VALUED_OPTION:
  // 240:   push &results undefined
  // 241:   !options(name) idx
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__21_138(void) {
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
  // 242: ... option == MULTI_VALUED_OPTION
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* option */;
  arguments->slots[1] = get__MULTI_VALUED_OPTION();
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__21_139;
}
static void cont__21_139(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 242: ... :
  // 243:   push &results empty_list
  // 244:   !options(name) idx
  frame->slots[6] /* temp__2 */ = create_closure(entry__21_140, 0);
  // 242: -> option == MULTI_VALUED_OPTION:
  // 243:   push &results empty_list
  // 244:   !options(name) idx
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__21_143(void) {
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
  // 245: ... option == SOME_PARAMETERS
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* option */;
  arguments->slots[1] = get__SOME_PARAMETERS();
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__21_144;
}
static void cont__21_144(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 245: ... option == MANY_PARAMETERS
  frame->slots[7] /* temp__3 */ = create_closure(entry__21_145, 0);
  // 245: ... option == SOME_PARAMETERS || option == MANY_PARAMETERS
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__21_147;
}
static void entry__21_145(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // option: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* option */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 245: ... option == MANY_PARAMETERS
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* option */;
  arguments->slots[1] = get__MANY_PARAMETERS();
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__21_146;
}
static void cont__21_146(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 245: ... option == MANY_PARAMETERS
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__21_147(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 245: ... :
  // 246:   push &results empty_list
  // 247:   !parameters(name) idx
  frame->slots[8] /* temp__4 */ = create_closure(entry__21_148, 0);
  // 245: -> option == SOME_PARAMETERS || option == MANY_PARAMETERS:
  // 246:   push &results empty_list
  // 247:   !parameters(name) idx
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__4 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__21_151(void) {
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
  // 249: push &results undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* results */;
  arguments->slots[1] = get__undefined();
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__21_152;
}
static void cont__21_152(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* results */ = arguments->slots[0];
  // 250: !parameters(name) idx
  frame->slots[4] /* temp__1 */ = frame->slots[3] /* idx */;
  // 250: !parameters(name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* name */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[1])->contents /* parameters */;
  func = myself->type;
  frame->cont = cont__21_153;
}
static void cont__21_153(void) {
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
static void entry__21_108(void) {
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
  // 222: template $$option $name? $default_value? $conversion? $help
  argument_count = 0;
  arguments = node_p;
  result_count = -1;
  myself = frame->slots[1] /* template */;
  func = myself->type;
  frame->cont = cont__21_109;
}
static void cont__21_109(void) {
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
  // 222: ... name
  initialize_future(frame->slots[12] /* name */, frame->slots[16] /* temp__1 */);
  // 222: ... default_value
  initialize_future(frame->slots[13] /* default_value */, frame->slots[17] /* temp__2 */);
  // 222: ... conversion
  initialize_future(frame->slots[14] /* conversion */, frame->slots[18] /* temp__3 */);
  // 222: ... help
  initialize_future(frame->slots[15] /* help */, frame->slots[19] /* temp__4 */);
  // 224: option.is_a_key_value_pair
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[11])->contents /* option */;
  result_count = 1;
  myself = get__is_a_key_value_pair();
  func = myself->type;
  frame->cont = cont__21_110;
}
static void cont__21_110(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[16] /* temp__1 */ = arguments->slots[0];
  // 224: ... :
  // 225:   push &possible_values value_of(option)
  // 226:   !option key_of(option)
  frame->slots[17] /* temp__2 */ = create_closure(entry__21_111, 0);
  // 227: :
  // 228:   push &possible_values undefined
  frame->slots[18] /* temp__3 */ = create_closure(entry__21_115, 0);
  // 223: if
  // 224:   option.is_a_key_value_pair:
  // 225:     push &possible_values value_of(option)
  // 226:     !option key_of(option)
  // 227:   :
  // 228:     push &possible_values undefined
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[16] /* temp__1 */;
  arguments->slots[1] = frame->slots[17] /* temp__2 */;
  arguments->slots[2] = frame->slots[18] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__21_117;
}
static void entry__21_111(void) {
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
  // 225: ... value_of(option)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* option */;
  result_count = 1;
  myself = get__value_of();
  func = myself->type;
  frame->cont = cont__21_112;
}
static void cont__21_112(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 225: push &possible_values value_of(option)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* possible_values */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__21_113;
}
static void cont__21_113(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* possible_values */ = arguments->slots[0];
  // 226: !option key_of(option)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* option */;
  result_count = 1;
  myself = get__key_of();
  func = myself->type;
  frame->cont = cont__21_114;
}
static void cont__21_114(void) {
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
static void entry__21_115(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // possible_values: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* possible_values */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 228: push &possible_values undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* possible_values */;
  arguments->slots[1] = get__undefined();
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__21_116;
}
static void cont__21_116(void) {
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
static void cont__21_117(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 229: ... name.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[12] /* name */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__21_118;
}
static void cont__21_118(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[17] /* temp__2 */ = arguments->slots[0];
  // 229: ... -> name
  frame->slots[18] /* temp__3 */ = create_closure(entry__21_119, 0);
  // 229: ... -> option
  frame->slots[19] /* temp__4 */ = create_closure(entry__21_120, 0);
  // 229: ... if(name.is_defined (-> name) -> option)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[17] /* temp__2 */;
  arguments->slots[1] = frame->slots[18] /* temp__3 */;
  arguments->slots[2] = frame->slots[19] /* temp__4 */;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__21_121;
}
static void entry__21_119(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[12]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 229: ... -> name
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__21_120(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // option: 0
  frame->slots[0] = myself->closure.frame->slots[11]; /* option */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 229: ... -> option
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* option */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__21_121(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[16] /* temp__1 */ = arguments->slots[0];
  // 229: push &names if(name.is_defined (-> name) -> option)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* names */;
  arguments->slots[1] = frame->slots[16] /* temp__1 */;
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
  ((CELL *)frame->slots[3])->contents /* names */ = arguments->slots[0];
  // 230: push &kinds option
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* kinds */;
  arguments->slots[1] = ((CELL *)frame->slots[11])->contents /* option */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__21_123;
}
static void cont__21_123(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[4])->contents /* kinds */ = arguments->slots[0];
  // 231: push &default_values default_value
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[5])->contents /* default_values */;
  arguments->slots[1] = frame->slots[13] /* default_value */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__21_124;
}
static void cont__21_124(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[5])->contents /* default_values */ = arguments->slots[0];
  // 232: push &conversions conversion
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[6])->contents /* conversions */;
  arguments->slots[1] = frame->slots[14] /* conversion */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__21_125;
}
static void cont__21_125(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[6])->contents /* conversions */ = arguments->slots[0];
  // 233: push &help_messages help
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[7])->contents /* help_messages */;
  arguments->slots[1] = frame->slots[15] /* help */;
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
  ((CELL *)frame->slots[7])->contents /* help_messages */ = arguments->slots[0];
  // 235: -> option.is_a_string:
  // 236:   push &results false
  // 237:   !options(option) idx
  // 238:   !kinds(idx) BOOLEAN_OPTION
  frame->slots[16] /* temp__1 */ = create_closure(entry__21_127, 0);
  // 239: -> option == VALUED_OPTION:
  // 240:   push &results undefined
  // 241:   !options(name) idx
  frame->slots[17] /* temp__2 */ = create_closure(entry__21_133, 0);
  // 242: -> option == MULTI_VALUED_OPTION:
  // 243:   push &results empty_list
  // 244:   !options(name) idx
  frame->slots[18] /* temp__3 */ = create_closure(entry__21_138, 0);
  // 245: -> option == SOME_PARAMETERS || option == MANY_PARAMETERS:
  // 246:   push &results empty_list
  // 247:   !parameters(name) idx
  frame->slots[19] /* temp__4 */ = create_closure(entry__21_143, 0);
  // 248: :
  // 249:   push &results undefined
  // 250:   !parameters(name) idx
  frame->slots[20] /* temp__5 */ = create_closure(entry__21_151, 0);
  // 234: cond
  // 235:   -> option.is_a_string:
  // 236:     push &results false
  // 237:     !options(option) idx
  // 238:     !kinds(idx) BOOLEAN_OPTION
  // 239:   -> option == VALUED_OPTION:
  // 240:     push &results undefined
  // 241:     !options(name) idx
  // 242:   -> option == MULTI_VALUED_OPTION:
  // 243:     push &results empty_list
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
static void cont__21_154(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 251: ... length_of(arguments)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* arguments */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__21_155;
}
static void cont__21_155(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[20] /* temp__3 */ = arguments->slots[0];
  // 251: ... length_of(arguments) >= 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[20] /* temp__3 */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__21_156;
}
static void cont__21_156(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[19] /* temp__2 */ = arguments->slots[0];
  // 251: ... length_of(arguments) >= 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[19] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__21_157;
}
static void cont__21_157(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[18] /* temp__1 */ = arguments->slots[0];
  // 251: ... :
  // 252:   if arguments(1) == "--help":
  // 253:     show_usage
  // 254:     terminate
  // 255:   if program_copyright.is_defined && arguments(1) == "--copyright":
  // 256:     show_copyright
  // 257:     terminate
  // 258:   if program_version.is_defined && arguments(1) == "--version":
  // 259:     show_version command_name
  // 260:     terminate
  frame->slots[21] /* temp__4 */ = create_closure(entry__21_158, 0);
  // 251: if length_of(arguments) >= 1:
  // 252:   if arguments(1) == "--help":
  // 253:     show_usage
  // 254:     terminate
  // 255:   if program_copyright.is_defined && arguments(1) == "--copyright":
  // 256:     show_copyright
  // 257:     terminate
  // 258:   if program_version.is_defined && arguments(1) == "--version":
  // 259:     show_version command_name
  // 260:     terminate
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[18] /* temp__1 */;
  arguments->slots[1] = frame->slots[21] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__21_182;
}
static void entry__21_180(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // command_name: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* command_name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 259: show_version command_name
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* command_name */;
  result_count = 0;
  myself = var._show_version;
  func = myself->type;
  frame->cont = cont__21_181;
}
static void cont__21_181(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 260: terminate
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = get__terminate();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__21_158(void) {
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
  // 252: ... arguments(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* arguments */;
  func = myself->type;
  frame->cont = cont__21_159;
}
static void cont__21_159(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 252: ... arguments(1) == "--help"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = string__21_160;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__21_161;
}
static void cont__21_161(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 252: ... :
  // 253:   show_usage
  // 254:   terminate
  frame->slots[5] /* temp__3 */ = create_closure(entry__21_162, 0);
  // 252: if arguments(1) == "--help":
  // 253:   show_usage
  // 254:   terminate
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__21_164;
}
static void entry__21_162(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // show_usage: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* show_usage */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 253: show_usage
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = frame->slots[0] /* show_usage */;
  func = myself->type;
  frame->cont = cont__21_163;
}
static void cont__21_163(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 254: terminate
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = get__terminate();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__21_164(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 255: ... program_copyright.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._program_copyright;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__21_165;
}
static void cont__21_165(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 255: ... arguments(1) == "--copyright"
  frame->slots[5] /* temp__3 */ = create_closure(entry__21_166, 0);
  // 255: ... program_copyright.is_defined && arguments(1) == "--copyright"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__21_170;
}
static void entry__21_166(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // arguments: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* arguments */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 255: ... arguments(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* arguments */;
  func = myself->type;
  frame->cont = cont__21_167;
}
static void cont__21_167(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 255: ... arguments(1) == "--copyright"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = string__21_168;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__21_169;
}
static void cont__21_169(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 255: ... arguments(1) == "--copyright"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__21_170(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 255: if program_copyright.is_defined && arguments(1) == "--copyright":
  // 256:   show_copyright
  // 257:   terminate
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = func__21_171;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__21_173;
}
static void entry__21_171(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 256: show_copyright
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = var._show_copyright;
  func = myself->type;
  frame->cont = cont__21_172;
}
static void cont__21_172(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 257: terminate
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = get__terminate();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__21_173(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 258: ... program_version.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._program_version;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__21_174;
}
static void cont__21_174(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 258: ... arguments(1) == "--version"
  frame->slots[5] /* temp__3 */ = create_closure(entry__21_175, 0);
  // 258: ... program_version.is_defined && arguments(1) == "--version"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__21_179;
}
static void entry__21_175(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // arguments: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* arguments */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 258: ... arguments(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* arguments */;
  func = myself->type;
  frame->cont = cont__21_176;
}
static void cont__21_176(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 258: ... arguments(1) == "--version"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = string__21_177;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__21_178;
}
static void cont__21_178(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 258: ... arguments(1) == "--version"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__21_179(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 258: ... :
  // 259:   show_version command_name
  // 260:   terminate
  frame->slots[6] /* temp__4 */ = create_closure(entry__21_180, 0);
  // 258: if program_version.is_defined && arguments(1) == "--version":
  // 259:   show_version command_name
  // 260:   terminate
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__21_182(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 261: ... :
  // 262:   $$idx 1
  // 263:   $$fetch_option_value false
  // 264:   $$option_idx undefined
  // 265:   do: (-> break)
  // 266:     for_each arguments: (argument)
  // 267:       if argument == "--":
  // 268:         delete_at &arguments idx
  // 269:         break
  // 270:       if
  // ...
  frame->slots[18] /* temp__1 */ = create_closure(entry__21_183, 0);
  // 261: do:
  // 262:   $$idx 1
  // 263:   $$fetch_option_value false
  // 264:   $$option_idx undefined
  // 265:   do: (-> break)
  // 266:     for_each arguments: (argument)
  // 267:       if argument == "--":
  // 268:         delete_at &arguments idx
  // 269:         break
  // 270:       if
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[18] /* temp__1 */;
  result_count = 0;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__21_223;
}
static void entry__21_184(void) {
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
  // 266: ... : (argument)
  // 267:   if argument == "--":
  // 268:     delete_at &arguments idx
  // 269:     break
  // 270:   if
  // 271:     fetch_option_value:
  // 272:       !fetch_option_value false
  // 273:       delete_at &arguments idx
  // 274:       case
  // 275:         kinds(option_idx)
  // ...
  frame->slots[8] /* temp__1 */ = create_closure(entry__21_185, 1);
  // 266: for_each arguments: (argument)
  // 267:   if argument == "--":
  // 268:     delete_at &arguments idx
  // 269:     break
  // 270:   if
  // 271:     fetch_option_value:
  // 272:       !fetch_option_value false
  // 273:       delete_at &arguments idx
  // 274:       case
  // 275:         kinds(option_idx)
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* arguments */;
  arguments->slots[1] = frame->slots[8] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__21_222;
}
static void entry__21_203(void) {
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
  // 283: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__21_204;
}
static void cont__21_204(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__2 */ = arguments->slots[0];
  // 283: ... range(argument 3 -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* argument */;
  arguments->slots[1] = number__3;
  arguments->slots[2] = frame->slots[9] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__21_205;
}
static void cont__21_205(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__1 */ = arguments->slots[0];
  // 283: !option_idx options(range(argument 3 -1))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[1])->contents /* options */;
  func = myself->type;
  frame->cont = cont__21_206;
}
static void cont__21_206(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* option_idx */ = arguments->slots[0];
  // 284: ... option_idx.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* option_idx */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__21_207;
}
static void cont__21_207(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__1 */ = arguments->slots[0];
  // 284: ... : Error "Invalid option: @(argument)!"
  frame->slots[9] /* temp__2 */ = create_closure(entry__21_208, 0);
  // 284: if option_idx.is_undefined: Error "Invalid option: @(argument)!"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__1 */;
  arguments->slots[1] = frame->slots[9] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__21_212;
}
static void entry__21_208(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // argument: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* argument */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 284: ... "Invalid option: @(argument)!"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__21_209;
  arguments->slots[1] = frame->slots[0] /* argument */;
  arguments->slots[2] = string__21_210;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__21_211;
}
static void cont__21_211(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 284: ... Error "Invalid option: @(argument)!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__21_212(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 286: kinds(option_idx)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* option_idx */;
  result_count = 1;
  myself = ((CELL *)frame->slots[3])->contents /* kinds */;
  func = myself->type;
  frame->cont = cont__21_213;
}
static void cont__21_213(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__2 */ = arguments->slots[0];
  // 286: kinds(option_idx) == BOOLEAN_OPTION
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__2 */;
  arguments->slots[1] = var._BOOLEAN_OPTION;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__21_214;
}
static void cont__21_214(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__1 */ = arguments->slots[0];
  // 286: ... :
  // 287:   !results(option_idx) true
  frame->slots[10] /* temp__3 */ = create_closure(entry__21_215, 0);
  // 288: :
  // 289:   !fetch_option_value true
  frame->slots[11] /* temp__4 */ = create_closure(entry__21_217, 0);
  // 285: if
  // 286:   kinds(option_idx) == BOOLEAN_OPTION:
  // 287:     !results(option_idx) true
  // 288:   :
  // 289:     !fetch_option_value true
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__1 */;
  arguments->slots[1] = frame->slots[10] /* temp__3 */;
  arguments->slots[2] = frame->slots[11] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__21_218;
}
static void entry__21_215(void) {
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
  // 287: !results(option_idx) true
  frame->slots[2] /* temp__1 */ = get__true();
  // 287: !results(option_idx)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* option_idx */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* results */;
  func = myself->type;
  frame->cont = cont__21_216;
}
static void cont__21_216(void) {
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
static void entry__21_217(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // fetch_option_value: 0
  frame->slots[0] = myself->closure.frame->slots[5]; /* fetch_option_value */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 289: !fetch_option_value true
  ((CELL *)frame->slots[0])->contents /* fetch_option_value */ = get__true();
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__21_218(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 290: delete_at &arguments idx
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[6])->contents /* arguments */;
  arguments->slots[1] = ((CELL *)frame->slots[7])->contents /* idx */;
  result_count = 1;
  myself = get__delete_at();
  func = myself->type;
  frame->cont = cont__21_219;
}
static void cont__21_219(void) {
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
static void entry__21_220(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // idx: 0
  frame->slots[0] = myself->closure.frame->slots[7]; /* idx */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 292: inc &idx
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* idx */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__21_221;
}
static void cont__21_221(void) {
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
static void entry__21_194(void) {
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
  // 277: !results(option_idx) argument
  frame->slots[3] /* temp__1 */ = frame->slots[2] /* argument */;
  // 277: !results(option_idx)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* option_idx */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* results */;
  func = myself->type;
  frame->cont = cont__21_195;
}
static void cont__21_195(void) {
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
static void entry__21_196(void) {
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
  // 279: ... results(option_idx)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* option_idx */;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* results */;
  func = myself->type;
  frame->cont = cont__21_197;
}
static void cont__21_197(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 279: push &results(option_idx) argument
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* argument */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__21_198;
}
static void cont__21_198(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 279: ... &results(option_idx)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* option_idx */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* results */;
  func = myself->type;
  frame->cont = cont__21_199;
}
static void cont__21_199(void) {
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
  // 272: !fetch_option_value false
  ((CELL *)frame->slots[0])->contents /* fetch_option_value */ = get__false();
  // 273: delete_at &arguments idx
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* arguments */;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* idx */;
  result_count = 1;
  myself = get__delete_at();
  func = myself->type;
  frame->cont = cont__21_192;
}
static void cont__21_192(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* arguments */ = arguments->slots[0];
  // 275: kinds(option_idx)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* option_idx */;
  result_count = 1;
  myself = ((CELL *)frame->slots[3])->contents /* kinds */;
  func = myself->type;
  frame->cont = cont__21_193;
}
static void cont__21_193(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 276: ... :
  // 277:   !results(option_idx) argument
  frame->slots[8] /* temp__2 */ = create_closure(entry__21_194, 0);
  // 278: ... :
  // 279:   push &results(option_idx) argument
  frame->slots[9] /* temp__3 */ = create_closure(entry__21_196, 0);
  // 274: case
  // 275:   kinds(option_idx)
  // 276:   VALUED_OPTION:
  // 277:     !results(option_idx) argument
  // 278:   MULTI_VALUED_OPTION:
  // 279:     push &results(option_idx) argument
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
static void entry__21_200(void) {
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
  // 282: argument .has_prefix. "--"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* argument */;
  arguments->slots[1] = string__21_201;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__21_202;
}
static void cont__21_202(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__1 */ = arguments->slots[0];
  // 282: ... :
  // 283:   !option_idx options(range(argument 3 -1))
  // 284:   if option_idx.is_undefined: Error "Invalid option: @(argument)!"
  // 285:   if
  // 286:     kinds(option_idx) == BOOLEAN_OPTION:
  // 287:       !results(option_idx) true
  // 288:     :
  // 289:       !fetch_option_value true
  // 290:   delete_at &arguments idx
  frame->slots[9] /* temp__2 */ = create_closure(entry__21_203, 0);
  // 291: :
  // 292:   inc &idx
  frame->slots[10] /* temp__3 */ = create_closure(entry__21_220, 0);
  // 281: if
  // 282:   argument .has_prefix. "--":
  // 283:     !option_idx options(range(argument 3 -1))
  // 284:     if option_idx.is_undefined: Error "Invalid option: @(argument)!"
  // 285:     if
  // 286:       kinds(option_idx) == BOOLEAN_OPTION:
  // 287:         !results(option_idx) true
  // 288:       :
  // 289:         !fetch_option_value true
  // 290:     delete_at &arguments idx
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
static void entry__21_185(void) {
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
  // 267: ... argument == "--"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* argument */;
  arguments->slots[1] = string__21_186;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__21_187;
}
static void cont__21_187(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 267: ... :
  // 268:   delete_at &arguments idx
  // 269:   break
  frame->slots[10] /* temp__2 */ = create_closure(entry__21_188, 0);
  // 267: if argument == "--":
  // 268:   delete_at &arguments idx
  // 269:   break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  arguments->slots[1] = frame->slots[10] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__21_190;
}
static void entry__21_188(void) {
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
  // 268: delete_at &arguments idx
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* arguments */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* idx */;
  result_count = 1;
  myself = get__delete_at();
  func = myself->type;
  frame->cont = cont__21_189;
}
static void cont__21_189(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* arguments */ = arguments->slots[0];
  // 269: break
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[2] /* break */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__21_190(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 271: ... :
  // 272:   !fetch_option_value false
  // 273:   delete_at &arguments idx
  // 274:   case
  // 275:     kinds(option_idx)
  // 276:     VALUED_OPTION:
  // 277:       !results(option_idx) argument
  // 278:     MULTI_VALUED_OPTION:
  // 279:       push &results(option_idx) argument
  frame->slots[9] /* temp__1 */ = create_closure(entry__21_191, 0);
  // 280: :
  // 281:   if
  // 282:     argument .has_prefix. "--":
  // 283:       !option_idx options(range(argument 3 -1))
  // 284:       if option_idx.is_undefined: Error "Invalid option: @(argument)!"
  // 285:       if
  // 286:         kinds(option_idx) == BOOLEAN_OPTION:
  // 287:           !results(option_idx) true
  // 288:         :
  // 289:           !fetch_option_value true
  // ...
  frame->slots[10] /* temp__2 */ = create_closure(entry__21_200, 0);
  // 270: if
  // 271:   fetch_option_value:
  // 272:     !fetch_option_value false
  // 273:     delete_at &arguments idx
  // 274:     case
  // 275:       kinds(option_idx)
  // 276:       VALUED_OPTION:
  // 277:         !results(option_idx) argument
  // 278:       MULTI_VALUED_OPTION:
  // 279:         push &results(option_idx) argument
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
static void cont__21_222(void) {
  myself = frame->slots[0] /* break */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__21_183(void) {
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
  // 262: $$idx 1
  ((CELL *)frame->slots[4])->contents /* idx */ = number__1;
  // 263: $$fetch_option_value false
  ((CELL *)frame->slots[5])->contents /* fetch_option_value */ = get__false();
  // 264: $$option_idx undefined
  ((CELL *)frame->slots[6])->contents /* option_idx */ = get__undefined();
  // 265: ... : (-> break)
  // 266:   for_each arguments: (argument)
  // 267:     if argument == "--":
  // 268:       delete_at &arguments idx
  // 269:       break
  // 270:     if
  // 271:       fetch_option_value:
  // 272:         !fetch_option_value false
  // 273:         delete_at &arguments idx
  // 274:         case
  // ...
  frame->slots[7] /* temp__1 */ = create_closure(entry__21_184, 0);
  // 265: do: (-> break)
  // 266:   for_each arguments: (argument)
  // 267:     if argument == "--":
  // 268:       delete_at &arguments idx
  // 269:       break
  // 270:     if
  // 271:       fetch_option_value:
  // 272:         !fetch_option_value false
  // 273:         delete_at &arguments idx
  // 274:         case
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__do();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__21_223(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 293: $$last_idx -1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__21_224;
}
static void cont__21_224(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[17])->contents /* last_idx */ = arguments->slots[0];
  // 294: ... : (-> break)
  // 295:   for_each_from_down_to templates -1 1: (idx template)
  // 296:     template $$option $_name? $_default_value? $_conversion? $_help
  // 297:     if option.is_a_key_value_pair: !option key_of(option)
  // 298:     case
  // 299:       option
  // 300:       MANDATORY_PARAMETER:
  // 301:         if arguments.is_empty too_few_arguments_error
  // 302:         pop &arguments !results(idx)
  // 303:         !last_idx idx-1
  // ...
  frame->slots[18] /* temp__1 */ = create_closure(entry__21_225, 0);
  // 294: do: (-> break)
  // 295:   for_each_from_down_to templates -1 1: (idx template)
  // 296:     template $$option $_name? $_default_value? $_conversion? $_help
  // 297:     if option.is_a_key_value_pair: !option key_of(option)
  // 298:     case
  // 299:       option
  // 300:       MANDATORY_PARAMETER:
  // 301:         if arguments.is_empty too_few_arguments_error
  // 302:         pop &arguments !results(idx)
  // 303:         !last_idx idx-1
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[18] /* temp__1 */;
  result_count = 0;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__21_242;
}
static void entry__21_225(void) {
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
  // 295: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__21_226;
}
static void cont__21_226(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 295: ... : (idx template)
  // 296:   template $$option $_name? $_default_value? $_conversion? $_help
  // 297:   if option.is_a_key_value_pair: !option key_of(option)
  // 298:   case
  // 299:     option
  // 300:     MANDATORY_PARAMETER:
  // 301:       if arguments.is_empty too_few_arguments_error
  // 302:       pop &arguments !results(idx)
  // 303:       !last_idx idx-1
  // 304:     OPTIONAL_PARAMETER, SOME_PARAMETERS, MANY_PARAMETERS:
  // ...
  frame->slots[7] /* temp__2 */ = create_closure(entry__21_227, 2);
  // 295: for_each_from_down_to templates -1 1: (idx template)
  // 296:   template $$option $_name? $_default_value? $_conversion? $_help
  // 297:   if option.is_a_key_value_pair: !option key_of(option)
  // 298:   case
  // 299:     option
  // 300:     MANDATORY_PARAMETER:
  // 301:       if arguments.is_empty too_few_arguments_error
  // 302:       pop &arguments !results(idx)
  // 303:       !last_idx idx-1
  // 304:     OPTIONAL_PARAMETER, SOME_PARAMETERS, MANY_PARAMETERS:
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
  frame->cont = cont__21_241;
}
static void entry__21_240(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // break: 0
  frame->slots[0] = myself->closure.frame->slots[6]; /* break */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 305: break
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* break */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__21_227(void) {
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
  // 296: template $$option $_name? $_default_value? $_conversion? $_help
  argument_count = 0;
  arguments = node_p;
  result_count = -1;
  myself = frame->slots[1] /* template */;
  func = myself->type;
  frame->cont = cont__21_228;
}
static void cont__21_228(void) {
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
  // 296: ... _name
  initialize_future(frame->slots[8] /* name */, frame->slots[12] /* temp__1 */);
  // 296: ... _default_value
  initialize_future(frame->slots[9] /* default_value */, frame->slots[13] /* temp__2 */);
  // 296: ... _conversion
  initialize_future(frame->slots[10] /* conversion */, frame->slots[14] /* temp__3 */);
  // 296: ... _help
  initialize_future(frame->slots[11] /* help */, frame->slots[15] /* temp__4 */);
  // 297: ... option.is_a_key_value_pair
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[7])->contents /* option */;
  result_count = 1;
  myself = get__is_a_key_value_pair();
  func = myself->type;
  frame->cont = cont__21_229;
}
static void cont__21_229(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__1 */ = arguments->slots[0];
  // 297: ... : !option key_of(option)
  frame->slots[13] /* temp__2 */ = create_closure(entry__21_230, 0);
  // 297: if option.is_a_key_value_pair: !option key_of(option)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[12] /* temp__1 */;
  arguments->slots[1] = frame->slots[13] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__21_232;
}
static void entry__21_230(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // option: 0
  frame->slots[0] = myself->closure.frame->slots[7]; /* option */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 297: ... !option key_of(option)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* option */;
  result_count = 1;
  myself = get__key_of();
  func = myself->type;
  frame->cont = cont__21_231;
}
static void cont__21_231(void) {
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
static void cont__21_232(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 300: ... :
  // 301:   if arguments.is_empty too_few_arguments_error
  // 302:   pop &arguments !results(idx)
  // 303:   !last_idx idx-1
  frame->slots[12] /* temp__1 */ = create_closure(entry__21_233, 0);
  // 304: OPTIONAL_PARAMETER, SOME_PARAMETERS, MANY_PARAMETERS
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__OPTIONAL_PARAMETER();
  arguments->slots[1] = get__SOME_PARAMETERS();
  arguments->slots[2] = get__MANY_PARAMETERS();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__21_239;
}
static void entry__21_233(void) {
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
  // 301: ... arguments.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* arguments */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__21_234;
}
static void cont__21_234(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 301: if arguments.is_empty too_few_arguments_error
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* too_few_arguments_error */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__21_235;
}
static void cont__21_235(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 302: pop &arguments !results(idx)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* arguments */;
  result_count = 2;
  myself = get__pop();
  func = myself->type;
  frame->cont = cont__21_236;
}
static void cont__21_236(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* arguments */ = arguments->slots[0];
  frame->slots[5] /* temp__1 */ = arguments->slots[1];
  // 302: ... !results(idx)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* idx */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[2])->contents /* results */;
  func = myself->type;
  frame->cont = cont__21_237;
}
static void cont__21_237(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* results */ = arguments->slots[0];
  // 303: !last_idx idx-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* idx */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__21_238;
}
static void cont__21_238(void) {
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
static void cont__21_239(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__2 */ = arguments->slots[0];
  // 304: ... :
  // 305:   break
  frame->slots[14] /* temp__3 */ = create_closure(entry__21_240, 0);
  // 298: case
  // 299:   option
  // 300:   MANDATORY_PARAMETER:
  // 301:     if arguments.is_empty too_few_arguments_error
  // 302:     pop &arguments !results(idx)
  // 303:     !last_idx idx-1
  // 304:   OPTIONAL_PARAMETER, SOME_PARAMETERS, MANY_PARAMETERS:
  // 305:     break
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
static void cont__21_241(void) {
  myself = frame->slots[0] /* break */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__21_242(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 306: ... : (idx template)
  // 307:   template $$option $_name? $_default_value? $_conversion? $_help
  // 308:   if option.is_a_key_value_pair: !option key_of(option)
  // 309:   case
  // 310:     option
  // 311:     MANDATORY_PARAMETER:
  // 312:       if length_of(arguments) == 0 too_few_arguments_error
  // 313:       get &arguments !results(idx)
  // 314:     OPTIONAL_PARAMETER:
  // 315:       if length_of(arguments) > 0: get &arguments !results(idx)
  // ...
  frame->slots[18] /* temp__1 */ = create_closure(entry__21_243, 2);
  // 306: for_each_from_to templates 1 last_idx: (idx template)
  // 307:   template $$option $_name? $_default_value? $_conversion? $_help
  // 308:   if option.is_a_key_value_pair: !option key_of(option)
  // 309:   case
  // 310:     option
  // 311:     MANDATORY_PARAMETER:
  // 312:       if length_of(arguments) == 0 too_few_arguments_error
  // 313:       get &arguments !results(idx)
  // 314:     OPTIONAL_PARAMETER:
  // 315:       if length_of(arguments) > 0: get &arguments !results(idx)
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
  frame->cont = cont__21_268;
}
static void entry__21_258(void) {
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
  // 315: ... get &arguments !results(idx)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* arguments */;
  result_count = 2;
  myself = get__get();
  func = myself->type;
  frame->cont = cont__21_259;
}
static void cont__21_259(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* arguments */ = arguments->slots[0];
  frame->slots[3] /* temp__1 */ = arguments->slots[1];
  // 315: ... !results(idx)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* idx */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[1])->contents /* results */;
  func = myself->type;
  frame->cont = cont__21_260;
}
static void cont__21_260(void) {
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
static void entry__21_249(void) {
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
  // 312: ... length_of(arguments)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* arguments */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__21_250;
}
static void cont__21_250(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 312: ... length_of(arguments) == 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__21_251;
}
static void cont__21_251(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 312: if length_of(arguments) == 0 too_few_arguments_error
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* too_few_arguments_error */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__21_252;
}
static void cont__21_252(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 313: get &arguments !results(idx)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* arguments */;
  result_count = 2;
  myself = get__get();
  func = myself->type;
  frame->cont = cont__21_253;
}
static void cont__21_253(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* arguments */ = arguments->slots[0];
  frame->slots[4] /* temp__1 */ = arguments->slots[1];
  // 313: ... !results(idx)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* idx */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[2])->contents /* results */;
  func = myself->type;
  frame->cont = cont__21_254;
}
static void cont__21_254(void) {
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
static void entry__21_255(void) {
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
  // 315: ... length_of(arguments)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* arguments */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__21_256;
}
static void cont__21_256(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 315: ... length_of(arguments) > 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__21_257;
}
static void cont__21_257(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 315: ... : get &arguments !results(idx)
  frame->slots[5] /* temp__3 */ = create_closure(entry__21_258, 0);
  // 315: if length_of(arguments) > 0: get &arguments !results(idx)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__21_261(void) {
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
  // 317: !results(idx) arguments
  frame->slots[3] /* temp__1 */ = ((CELL *)frame->slots[2])->contents /* arguments */;
  // 317: !results(idx)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* idx */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* results */;
  func = myself->type;
  frame->cont = cont__21_262;
}
static void cont__21_262(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* results */ = arguments->slots[0];
  // 318: !arguments empty_list
  ((CELL *)frame->slots[2])->contents /* arguments */ = get__empty_list();
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__21_263(void) {
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
  // 320: ... length_of(arguments)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* arguments */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__21_264;
}
static void cont__21_264(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 320: ... length_of(arguments) == 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__21_265;
}
static void cont__21_265(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 320: if length_of(arguments) == 0 too_few_arguments_error
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* too_few_arguments_error */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__21_266;
}
static void cont__21_266(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 321: !results(idx) arguments
  frame->slots[4] /* temp__1 */ = ((CELL *)frame->slots[0])->contents /* arguments */;
  // 321: !results(idx)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* idx */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[2])->contents /* results */;
  func = myself->type;
  frame->cont = cont__21_267;
}
static void cont__21_267(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* results */ = arguments->slots[0];
  // 322: !arguments empty_list
  ((CELL *)frame->slots[0])->contents /* arguments */ = get__empty_list();
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__21_243(void) {
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
  // 307: template $$option $_name? $_default_value? $_conversion? $_help
  argument_count = 0;
  arguments = node_p;
  result_count = -1;
  myself = frame->slots[1] /* template */;
  func = myself->type;
  frame->cont = cont__21_244;
}
static void cont__21_244(void) {
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
  // 307: ... _name
  initialize_future(frame->slots[6] /* name */, frame->slots[10] /* temp__1 */);
  // 307: ... _default_value
  initialize_future(frame->slots[7] /* default_value */, frame->slots[11] /* temp__2 */);
  // 307: ... _conversion
  initialize_future(frame->slots[8] /* conversion */, frame->slots[12] /* temp__3 */);
  // 307: ... _help
  initialize_future(frame->slots[9] /* help */, frame->slots[13] /* temp__4 */);
  // 308: ... option.is_a_key_value_pair
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[5])->contents /* option */;
  result_count = 1;
  myself = get__is_a_key_value_pair();
  func = myself->type;
  frame->cont = cont__21_245;
}
static void cont__21_245(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__1 */ = arguments->slots[0];
  // 308: ... : !option key_of(option)
  frame->slots[11] /* temp__2 */ = create_closure(entry__21_246, 0);
  // 308: if option.is_a_key_value_pair: !option key_of(option)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__1 */;
  arguments->slots[1] = frame->slots[11] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__21_248;
}
static void entry__21_246(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // option: 0
  frame->slots[0] = myself->closure.frame->slots[5]; /* option */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 308: ... !option key_of(option)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* option */;
  result_count = 1;
  myself = get__key_of();
  func = myself->type;
  frame->cont = cont__21_247;
}
static void cont__21_247(void) {
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
static void cont__21_248(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 311: ... :
  // 312:   if length_of(arguments) == 0 too_few_arguments_error
  // 313:   get &arguments !results(idx)
  frame->slots[10] /* temp__1 */ = create_closure(entry__21_249, 0);
  // 314: ... :
  // 315:   if length_of(arguments) > 0: get &arguments !results(idx)
  frame->slots[11] /* temp__2 */ = create_closure(entry__21_255, 0);
  // 316: ... :
  // 317:   !results(idx) arguments
  // 318:   !arguments empty_list
  frame->slots[12] /* temp__3 */ = create_closure(entry__21_261, 0);
  // 319: ... :
  // 320:   if length_of(arguments) == 0 too_few_arguments_error
  // 321:   !results(idx) arguments
  // 322:   !arguments empty_list
  frame->slots[13] /* temp__4 */ = create_closure(entry__21_263, 0);
  // 309: case
  // 310:   option
  // 311:   MANDATORY_PARAMETER:
  // 312:     if length_of(arguments) == 0 too_few_arguments_error
  // 313:     get &arguments !results(idx)
  // 314:   OPTIONAL_PARAMETER:
  // 315:     if length_of(arguments) > 0: get &arguments !results(idx)
  // 316:   SOME_PARAMETERS:
  // 317:     !results(idx) arguments
  // 318:     !arguments empty_list
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
static void cont__21_268(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 323: ... arguments.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* arguments */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__21_269;
}
static void cont__21_269(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[18] /* temp__1 */ = arguments->slots[0];
  // 323: unless arguments.is_empty too_many_arguments_error
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[18] /* temp__1 */;
  arguments->slots[1] = frame->slots[16] /* too_many_arguments_error */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__21_270;
}
static void cont__21_270(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 324: ... : (idx result)
  // 325:   if
  // 326:     result.is_undefined && default_values(idx).is_defined:
  // 327:       !results(idx) default_values(idx)
  // 328:     :
  // 329:       $possible_value possible_values(idx)
  // 330:       
  // 331:       $check: (value)
  // 332:         unless possible_value(value):
  // 333:           ewriteln
  // ...
  frame->slots[18] /* temp__1 */ = create_closure(entry__21_271, 2);
  // 324: for_each results: (idx result)
  // 325:   if
  // 326:     result.is_undefined && default_values(idx).is_defined:
  // 327:       !results(idx) default_values(idx)
  // 328:     :
  // 329:       $possible_value possible_values(idx)
  // 330:       
  // 331:       $check: (value)
  // 332:         unless possible_value(value):
  // 333:           ewriteln
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* results */;
  arguments->slots[1] = frame->slots[18] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__21_312;
}
static void entry__21_303(void) {
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
  // 348: $$new_result empty_list
  ((CELL *)frame->slots[4])->contents /* new_result */ = get__empty_list();
  // 349: ... : (item) push &new_result conversion(item)
  frame->slots[5] /* temp__1 */ = create_closure(entry__21_304, 1);
  // 349: for_each result: (item) push &new_result conversion(item)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* result */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__21_307;
}
static void entry__21_304(void) {
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
  // 349: ... conversion(item)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* item */;
  result_count = 1;
  myself = frame->slots[2] /* conversion */;
  func = myself->type;
  frame->cont = cont__21_305;
}
static void cont__21_305(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 349: ... push &new_result conversion(item)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* new_result */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__21_306;
}
static void cont__21_306(void) {
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
static void cont__21_307(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 350: !results(idx) new_result
  frame->slots[5] /* temp__1 */ = ((CELL *)frame->slots[4])->contents /* new_result */;
  // 350: !results(idx)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* idx */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[2])->contents /* results */;
  func = myself->type;
  frame->cont = cont__21_308;
}
static void cont__21_308(void) {
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
static void entry__21_309(void) {
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
  // 352: !results(idx) conversion(result)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* result */;
  result_count = 1;
  myself = frame->slots[2] /* conversion */;
  func = myself->type;
  frame->cont = cont__21_310;
}
static void cont__21_310(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 352: !results(idx)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* idx */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* results */;
  func = myself->type;
  frame->cont = cont__21_311;
}
static void cont__21_311(void) {
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
static void entry__21_301(void) {
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
  // 347: result.is_a_list
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* result */;
  result_count = 1;
  myself = get__is_a_list();
  func = myself->type;
  frame->cont = cont__21_302;
}
static void cont__21_302(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 347: ... :
  // 348:   $$new_result empty_list
  // 349:   for_each result: (item) push &new_result conversion(item)
  // 350:   !results(idx) new_result
  frame->slots[5] /* temp__2 */ = create_closure(entry__21_303, 0);
  // 351: :
  // 352:   !results(idx) conversion(result)
  frame->slots[6] /* temp__3 */ = create_closure(entry__21_309, 0);
  // 346: if
  // 347:   result.is_a_list:
  // 348:     $$new_result empty_list
  // 349:     for_each result: (item) push &new_result conversion(item)
  // 350:     !results(idx) new_result
  // 351:   :
  // 352:     !results(idx) conversion(result)
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
static void entry__21_277(void) {
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
  // 327: !results(idx) default_values(idx)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* idx */;
  result_count = 1;
  myself = ((CELL *)frame->slots[2])->contents /* default_values */;
  func = myself->type;
  frame->cont = cont__21_278;
}
static void cont__21_278(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 327: !results(idx)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* idx */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* results */;
  func = myself->type;
  frame->cont = cont__21_279;
}
static void cont__21_279(void) {
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
static void entry__21_280(void) {
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
  // 331: ... : (value)
  // 332:   unless possible_value(value):
  // 333:     ewriteln
  // 334:       "Invalid argument value for @(names(idx).to_upper_case)!@nl;"
  // 335:     show_usage
  // 336:     exit 1
  frame->slots[10] /* temp__1 */ = create_closure(entry__21_281, 1);
  // 331: $check: (value)
  // 332:   unless possible_value(value):
  // 333:     ewriteln
  // 334:       "Invalid argument value for @(names(idx).to_upper_case)!@nl;"
  // 335:     show_usage
  // 336:     exit 1
  initialize_future(frame->slots[8] /* check */, frame->slots[10] /* temp__1 */);
  // 329: $possible_value possible_values(idx)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* idx */;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* possible_values */;
  func = myself->type;
  frame->cont = cont__21_291;
}
static void entry__21_283(void) {
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
  // 334: ... names(idx)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* idx */;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* names */;
  func = myself->type;
  frame->cont = cont__21_284;
}
static void cont__21_284(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 334: ... names(idx).to_upper_case
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__to_upper_case();
  func = myself->type;
  frame->cont = cont__21_285;
}
static void cont__21_285(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 334: "Invalid argument value for @(names(idx).to_upper_case)!@nl;"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__21_286;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  arguments->slots[2] = string__21_287;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__21_288;
}
static void cont__21_288(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 333: ewriteln
  // 334:   "Invalid argument value for @(names(idx).to_upper_case)!@nl;"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = 0;
  myself = get__ewriteln();
  func = myself->type;
  frame->cont = cont__21_289;
}
static void cont__21_289(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 335: show_usage
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = frame->slots[2] /* show_usage */;
  func = myself->type;
  frame->cont = cont__21_290;
}
static void cont__21_290(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 336: exit 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = frame->caller_result_count;
  myself = get__exit();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__21_281(void) {
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
  // 332: ... possible_value(value)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* value */;
  result_count = 1;
  myself = frame->slots[1] /* possible_value */;
  func = myself->type;
  frame->cont = cont__21_282;
}
static void cont__21_282(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 332: ... :
  // 333:   ewriteln
  // 334:     "Invalid argument value for @(names(idx).to_upper_case)!@nl;"
  // 335:   show_usage
  // 336:   exit 1
  frame->slots[6] /* temp__2 */ = create_closure(entry__21_283, 0);
  // 332: unless possible_value(value):
  // 333:   ewriteln
  // 334:     "Invalid argument value for @(names(idx).to_upper_case)!@nl;"
  // 335:   show_usage
  // 336:   exit 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__21_291(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[7] /* possible_value */, arguments->slots[0]);
  // 338: ... possible_value.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* possible_value */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__21_292;
}
static void cont__21_292(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__1 */ = arguments->slots[0];
  // 338: ... :
  // 339:   if
  // 340:     result.is_a_list:
  // 341:       for_each result: (item) check item
  // 342:     :
  // 343:       check result
  frame->slots[11] /* temp__2 */ = create_closure(entry__21_293, 0);
  // 338: if possible_value.is_defined:
  // 339:   if
  // 340:     result.is_a_list:
  // 341:       for_each result: (item) check item
  // 342:     :
  // 343:       check result
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__1 */;
  arguments->slots[1] = frame->slots[11] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__21_298;
}
static void entry__21_296(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // item: 0
  // check: 1
  frame->slots[1] = myself->closure.frame->slots[1]; /* check */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 341: ... check item
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* item */;
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* check */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__21_295(void) {
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
  // 341: ... : (item) check item
  frame->slots[2] /* temp__1 */ = create_closure(entry__21_296, 1);
  // 341: for_each result: (item) check item
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* result */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__21_297(void) {
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
  // 343: check result
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* result */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* check */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__21_293(void) {
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
  // 340: result.is_a_list
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* result */;
  result_count = 1;
  myself = get__is_a_list();
  func = myself->type;
  frame->cont = cont__21_294;
}
static void cont__21_294(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 340: ... :
  // 341:   for_each result: (item) check item
  frame->slots[3] /* temp__2 */ = create_closure(entry__21_295, 0);
  // 342: :
  // 343:   check result
  frame->slots[4] /* temp__3 */ = create_closure(entry__21_297, 0);
  // 339: if
  // 340:   result.is_a_list:
  // 341:     for_each result: (item) check item
  // 342:   :
  // 343:     check result
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
static void cont__21_298(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 344: $conversion conversions(idx)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* idx */;
  result_count = 1;
  myself = ((CELL *)frame->slots[5])->contents /* conversions */;
  func = myself->type;
  frame->cont = cont__21_299;
}
static void cont__21_299(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[9] /* conversion */, arguments->slots[0]);
  // 345: ... conversion.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* conversion */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__21_300;
}
static void cont__21_300(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__1 */ = arguments->slots[0];
  // 345: ... :
  // 346:   if
  // 347:     result.is_a_list:
  // 348:       $$new_result empty_list
  // 349:       for_each result: (item) push &new_result conversion(item)
  // 350:       !results(idx) new_result
  // 351:     :
  // 352:       !results(idx) conversion(result)
  frame->slots[11] /* temp__2 */ = create_closure(entry__21_301, 0);
  // 345: if conversion.is_defined:
  // 346:   if
  // 347:     result.is_a_list:
  // 348:       $$new_result empty_list
  // 349:       for_each result: (item) push &new_result conversion(item)
  // 350:       !results(idx) new_result
  // 351:     :
  // 352:       !results(idx) conversion(result)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__1 */;
  arguments->slots[1] = frame->slots[11] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__21_271(void) {
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
  // 326: result.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* result */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__21_272;
}
static void cont__21_272(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__2 */ = arguments->slots[0];
  // 326: ... default_values(idx).is_defined
  frame->slots[10] /* temp__3 */ = create_closure(entry__21_273, 0);
  // 326: result.is_undefined && default_values(idx).is_defined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__2 */;
  arguments->slots[1] = frame->slots[10] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__21_276;
}
static void entry__21_273(void) {
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
  // 326: ... default_values(idx)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* idx */;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* default_values */;
  func = myself->type;
  frame->cont = cont__21_274;
}
static void cont__21_274(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 326: ... default_values(idx).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__21_275;
}
static void cont__21_275(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 326: ... default_values(idx).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__21_276(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__1 */ = arguments->slots[0];
  // 326: ... :
  // 327:   !results(idx) default_values(idx)
  frame->slots[11] /* temp__4 */ = create_closure(entry__21_277, 0);
  // 328: :
  // 329:   $possible_value possible_values(idx)
  // 330:   
  // 331:   $check: (value)
  // 332:     unless possible_value(value):
  // 333:       ewriteln
  // 334:         "Invalid argument value for @(names(idx).to_upper_case)!@nl;"
  // 335:       show_usage
  // 336:       exit 1
  // 337:   
  // ...
  frame->slots[12] /* temp__5 */ = create_closure(entry__21_280, 0);
  // 325: if
  // 326:   result.is_undefined && default_values(idx).is_defined:
  // 327:     !results(idx) default_values(idx)
  // 328:   :
  // 329:     $possible_value possible_values(idx)
  // 330:     
  // 331:     $check: (value)
  // 332:       unless possible_value(value):
  // 333:         ewriteln
  // 334:           "Invalid argument value for @(names(idx).to_upper_case)!@nl;"
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
static void cont__21_312(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 353: -> results*
  argument_count = 0;
  arguments = node_p;
  unfold(((CELL *)frame->slots[3])->contents /* results */);
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__22_1(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // commands: 0
  // command_ids: 1
  frame->slots[1] /* command_ids */ = create_cell();
  frame->slots[0] /* commands */ = from_arguments(0, argument_count-0);
  // 356: $$command_ids empty_list
  ((CELL *)frame->slots[1])->contents /* command_ids */ = get__empty_list();
  // 357: ... : (command)
  // 358:   $name key_of(command)
  // 359:   $description value_of(command)
  // 360:   push &command_names name
  // 361:   push &command_descriptions description
  // 362:   inc &command_id_count
  // 363:   push &command_ids command_id_count
  frame->slots[2] /* temp__1 */ = create_closure(entry__22_2, 1);
  // 357: for_each commands: (command)
  // 358:   $name key_of(command)
  // 359:   $description value_of(command)
  // 360:   push &command_names name
  // 361:   push &command_descriptions description
  // 362:   inc &command_id_count
  // 363:   push &command_ids command_id_count
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
  // 358: $name key_of(command)
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
  // 359: $description value_of(command)
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
  // 360: push &command_names name
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
  // 361: push &command_descriptions description
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
  // 362: inc &command_id_count
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
  // 363: push &command_ids command_id_count
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
  // 364: -> command_ids*
  argument_count = 0;
  arguments = node_p;
  unfold(((CELL *)frame->slots[1])->contents /* command_ids */);
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__23_34(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // templates: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* templates */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 383: ... list(undefined)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__23_35;
}
static void cont__23_35(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 383: ... length_of(templates)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* templates */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__23_36;
}
static void cont__23_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 383: ... dup(list(undefined) length_of(templates))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__dup();
  func = myself->type;
  frame->cont = cont__23_37;
}
static void cont__23_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 383: ... -> dup(list(undefined) length_of(templates))*
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[1] /* temp__1 */);
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__23_30(void) {
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
  // 381: !command_id id
  var._command_id = frame->slots[0] /* id */;
  // 382: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__23_31;
}
static void cont__23_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 382: ... range(command_line_arguments 2 -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__command_line_arguments();
  arguments->slots[1] = number__2;
  arguments->slots[2] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__23_32;
}
static void cont__23_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 382: check_arguments command range(command_line_arguments 2 -1) templates
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
  // 379: ... command_names(id)
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
  // 379: ... list("--help")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__23_25;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__23_26;
}
static void cont__23_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 379: check_arguments command_names(id) list("--help") templates
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
  // 375: command == "help"
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
  // 376: length_of(command_line_arguments)
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
  // 376: length_of(command_line_arguments) == 2
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
  // 377: command_line_arguments(2).from_utf8 == command_names(id)
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
  // 377: command_line_arguments(2)
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
  // 377: command_line_arguments(2).from_utf8
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
  // 377: ... command_names(id)
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
  // 377: command_line_arguments(2).from_utf8 == command_names(id)
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
  // 377: command_line_arguments(2).from_utf8 == command_names(id)
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
  // 378: :
  // 379:   check_arguments command_names(id) list("--help") templates
  frame->slots[6] /* temp__4 */ = create_closure(entry__23_23, 0);
  // 373: ->
  // 374:   &&
  // 375:     command == "help"
  // 376:     length_of(command_line_arguments) == 2
  // 377:     command_line_arguments(2).from_utf8 == command_names(id)
  // 378:   :
  // 379:     check_arguments command_names(id) list("--help") templates
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__4 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__23_27(void) {
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
  // 380: ... command_names(id)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* id */;
  result_count = 1;
  myself = var._command_names;
  func = myself->type;
  frame->cont = cont__23_28;
}
static void cont__23_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 380: ... command == command_names(id)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* command */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__23_29;
}
static void cont__23_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 380: ... :
  // 381:   !command_id id
  // 382:   check_arguments command range(command_line_arguments 2 -1) templates
  frame->slots[5] /* temp__3 */ = create_closure(entry__23_30, 0);
  // 380: -> command == command_names(id):
  // 381:   !command_id id
  // 382:   check_arguments command range(command_line_arguments 2 -1) templates
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__23_33(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // templates: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* templates */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 383: ... -> dup(list(undefined) length_of(templates))*
  frame->slots[1] /* temp__1 */ = create_closure(entry__23_34, 0);
  // 383: -> true -> dup(list(undefined) length_of(templates))*
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
  // 369: ... list(undefined)
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
  // 369: ... length_of(templates)
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
  // 369: ... dup(list(undefined) length_of(templates))
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
  // 369: -> dup(list(undefined) length_of(templates))*
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
  // 371: ... command_line_arguments(1)
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
  // 371: $command command_line_arguments(1).from_utf8
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
  // 373: ->
  // 374:   &&
  // 375:     command == "help"
  // 376:     length_of(command_line_arguments) == 2
  // 377:     command_line_arguments(2).from_utf8 == command_names(id)
  // 378:   :
  // 379:     check_arguments command_names(id) list("--help") templates
  frame->slots[3] /* temp__1 */ = create_closure(entry__23_10, 0);
  // 380: -> command == command_names(id):
  // 381:   !command_id id
  // 382:   check_arguments command range(command_line_arguments 2 -1) templates
  frame->slots[4] /* temp__2 */ = create_closure(entry__23_27, 0);
  // 383: -> true -> dup(list(undefined) length_of(templates))*
  frame->slots[5] /* temp__3 */ = create_closure(entry__23_33, 0);
  // 372: cond
  // 373:   ->
  // 374:     &&
  // 375:       command == "help"
  // 376:       length_of(command_line_arguments) == 2
  // 377:       command_line_arguments(2).from_utf8 == command_names(id)
  // 378:     :
  // 379:       check_arguments command_names(id) list("--help") templates
  // 380:   -> command == command_names(id):
  // 381:     !command_id id
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
static void entry__23_1(void) {
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
  // 368: command_line_arguments.is_empty
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
  // 369: -> dup(list(undefined) length_of(templates))*
  frame->slots[3] /* temp__2 */ = create_closure(entry__23_3, 0);
  // 370: :
  // 371:   $command command_line_arguments(1).from_utf8
  // 372:   cond
  // 373:     ->
  // 374:       &&
  // 375:         command == "help"
  // 376:         length_of(command_line_arguments) == 2
  // 377:         command_line_arguments(2).from_utf8 == command_names(id)
  // 378:       :
  // 379:         check_arguments command_names(id) list("--help") templates
  // ...
  frame->slots[4] /* temp__3 */ = create_closure(entry__23_7, 0);
  // 367: if
  // 368:   command_line_arguments.is_empty
  // 369:   -> dup(list(undefined) length_of(templates))*
  // 370:   :
  // 371:     $command command_line_arguments(1).from_utf8
  // 372:     cond
  // 373:       ->
  // 374:         &&
  // 375:           command == "help"
  // 376:           length_of(command_line_arguments) == 2
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
static void entry__24_1(void) {
  allocate_initialized_frame_gc(0, 3);
  // slot allocations:
  // tab: 0
  frame->slots[0] /* tab */ = create_cell();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 386: ... program_version.is_defined
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
  // 386: if program_version.is_defined:
  // 387:   show_version truncate_until(program_name '/' -1)
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
  // 387: ... 1
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
  // 387: ... truncate_until(program_name '/' -1)
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
  // 387: show_version truncate_until(program_name '/' -1)
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
  // 388: ewriteln "Available commands:"
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
  // 389: ... list("help" "display help for the specified command")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__24_9;
  arguments->slots[1] = string__24_10;
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
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 389: $$tab list(list("help" "display help for the specified command"))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__24_12;
}
static void cont__24_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* tab */ = arguments->slots[0];
  // 390: ... : (idx command_name)
  // 391:   push &tab list(command_name command_descriptions(idx))
  frame->slots[1] /* temp__1 */ = create_closure(entry__24_13, 2);
  // 390: for_each command_names: (idx command_name)
  // 391:   push &tab list(command_name command_descriptions(idx))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._command_names;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__24_17;
}
static void entry__24_13(void) {
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
  // 391: ... command_descriptions(idx)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* idx */;
  result_count = 1;
  myself = var._command_descriptions;
  func = myself->type;
  frame->cont = cont__24_14;
}
static void cont__24_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 391: ... list(command_name command_descriptions(idx))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* command_name */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__24_15;
}
static void cont__24_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 391: push &tab list(command_name command_descriptions(idx))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* tab */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__24_16;
}
static void cont__24_16(void) {
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
static void cont__24_17(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 392: ... program_copyright.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._program_copyright;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__24_18;
}
static void cont__24_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 392: ... :
  // 393:   push &tab list("copyright" "display the copyright message")
  frame->slots[2] /* temp__2 */ = create_closure(entry__24_19, 0);
  // 392: if program_copyright.is_defined:
  // 393:   push &tab list("copyright" "display the copyright message")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__24_24;
}
static void entry__24_19(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // tab: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* tab */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 393: ... list("copyright" "display the copyright message")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__24_20;
  arguments->slots[1] = string__24_21;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__24_22;
}
static void cont__24_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 393: push &tab list("copyright" "display the copyright message")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* tab */;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__24_23;
}
static void cont__24_23(void) {
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
static void cont__24_24(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 394: ... program_version.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._program_version;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__24_25;
}
static void cont__24_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 394: ... :
  // 395:   push &tab list("version" "display the version number")
  frame->slots[2] /* temp__2 */ = create_closure(entry__24_26, 0);
  // 394: if program_version.is_defined:
  // 395:   push &tab list("version" "display the version number")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__24_31;
}
static void entry__24_26(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // tab: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* tab */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 395: ... list("version" "display the version number")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__24_27;
  arguments->slots[1] = string__24_28;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__24_29;
}
static void cont__24_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 395: push &tab list("version" "display the version number")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* tab */;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__24_30;
}
static void cont__24_30(void) {
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
static void cont__24_31(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 396: display_table tab
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
  // 404: ewriteln "
  // 405:   No command specified!
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
  // 406: show_commands
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
  // 407: exit 1
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
  // 410: command_line_arguments(1)
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
  // 409: case
  // 410:   command_line_arguments(1)
  // 411:   "copyright":
  // 412:     if program_copyright.is_defined:
  // 413:       show_copyright
  // 414:       terminate
  // 415:   "help":
  // 416:     case
  // 417:       length_of(command_line_arguments)
  // 418:       1:
  // ...
  argument_count = 7;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = string__25_15;
  arguments->slots[2] = func__25_16;
  arguments->slots[3] = string__25_20;
  arguments->slots[4] = func__25_21;
  arguments->slots[5] = string__25_51;
  arguments->slots[6] = func__25_52;
  result_count = 0;
  myself = get__case();
  func = myself->type;
  frame->cont = cont__25_58;
}
static void entry__25_54(void) {
  allocate_initialized_frame_gc(0, 2);
  // slot allocations:
  // command_name: 0
  frame->slots[0] /* command_name */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 455: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__25_55;
}
static void cont__25_55(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 455: $command_name truncate_until(program_name '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__program_name();
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__truncate_until();
  func = myself->type;
  frame->cont = cont__25_56;
}
static void cont__25_56(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[0] /* command_name */, arguments->slots[0]);
  // 456: show_version command_name
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* command_name */;
  result_count = 0;
  myself = var._show_version;
  func = myself->type;
  frame->cont = cont__25_57;
}
static void cont__25_57(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 457: terminate
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = get__terminate();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__25_23(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 419: show_commands
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = var._show_commands;
  func = myself->type;
  frame->cont = cont__25_24;
}
static void cont__25_24(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 420: terminate
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
  // 423: command_line_arguments(2)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = get__command_line_arguments();
  func = myself->type;
  frame->cont = cont__25_26;
}
static void cont__25_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 422: case
  // 423:   command_line_arguments(2)
  // 424:   "copyright":
  // 425:     if program_copyright.is_defined:
  // 426:       ewrite "
  // 427:         Usage:
  // 428:           sigi copyright
  // 429:       terminate
  // 430:   "help":
  // 431:     ewrite "
  // ...
  argument_count = 7;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = string__25_27;
  arguments->slots[2] = func__25_28;
  arguments->slots[3] = string__25_33;
  arguments->slots[4] = func__25_34;
  arguments->slots[5] = string__25_37;
  arguments->slots[6] = func__25_38;
  result_count = 0;
  myself = get__case();
  func = myself->type;
  frame->cont = cont__25_43;
}
static void entry__25_40(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 440: ewrite "
  // 441:   Usage:
  // 442:     sigi version
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__25_41;
  result_count = 0;
  myself = get__ewrite();
  func = myself->type;
  frame->cont = cont__25_42;
}
static void cont__25_42(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 443: terminate
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = get__terminate();
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
  // 426: ewrite "
  // 427:   Usage:
  // 428:     sigi copyright
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
  // 429: terminate
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = get__terminate();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__25_28(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 425: ... program_copyright.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._program_copyright;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__25_29;
}
static void cont__25_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 425: if program_copyright.is_defined:
  // 426:   ewrite "
  // 427:     Usage:
  // 428:       sigi copyright
  // 429:   terminate
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = func__25_30;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__25_34(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 431: ewrite "
  // 432:   Usage:
  // 433:     sigi help COMMAND
  // 434:   
  // 435:   Parameter:
  // 436:     COMMAND  the command for which to retrieve help
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__25_35;
  result_count = 0;
  myself = get__ewrite();
  func = myself->type;
  frame->cont = cont__25_36;
}
static void cont__25_36(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 437: terminate
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = get__terminate();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__25_38(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 439: ... program_version.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._program_version;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__25_39;
}
static void cont__25_39(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 439: if program_version.is_defined:
  // 440:   ewrite "
  // 441:     Usage:
  // 442:       sigi version
  // 443:   terminate
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = func__25_40;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__25_43(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 444: ewriteln "
  // 445:   Invalid command name!
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__25_44;
  result_count = 0;
  myself = get__ewriteln();
  func = myself->type;
  frame->cont = cont__25_45;
}
static void cont__25_45(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 446: show_commands
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = var._show_commands;
  func = myself->type;
  frame->cont = cont__25_46;
}
static void cont__25_46(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 447: exit 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = frame->caller_result_count;
  myself = get__exit();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__25_47(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 449: ewriteln "
  // 450:   Too many arguments!
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__25_48;
  result_count = 0;
  myself = get__ewriteln();
  func = myself->type;
  frame->cont = cont__25_49;
}
static void cont__25_49(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 451: show_commands
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = var._show_commands;
  func = myself->type;
  frame->cont = cont__25_50;
}
static void cont__25_50(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 452: exit 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = frame->caller_result_count;
  myself = get__exit();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__25_18(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 413: show_copyright
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = var._show_copyright;
  func = myself->type;
  frame->cont = cont__25_19;
}
static void cont__25_19(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 414: terminate
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = get__terminate();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__25_16(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 412: ... program_copyright.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._program_copyright;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__25_17;
}
static void cont__25_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 412: if program_copyright.is_defined:
  // 413:   show_copyright
  // 414:   terminate
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = func__25_18;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__25_21(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 417: length_of(command_line_arguments)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__command_line_arguments();
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__25_22;
}
static void cont__25_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 416: case
  // 417:   length_of(command_line_arguments)
  // 418:   1:
  // 419:     show_commands
  // 420:     terminate
  // 421:   2:
  // 422:     case
  // 423:       command_line_arguments(2)
  // 424:       "copyright":
  // 425:         if program_copyright.is_defined:
  // ...
  argument_count = 6;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = func__25_23;
  arguments->slots[3] = number__2;
  arguments->slots[4] = func__25_25;
  arguments->slots[5] = func__25_47;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__25_52(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 454: ... program_version.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._program_version;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__25_53;
}
static void cont__25_53(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 454: if program_version.is_defined:
  // 455:   $command_name truncate_until(program_name '/' -1)
  // 456:   show_version command_name
  // 457:   terminate
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = func__25_54;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__25_58(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 458: ewriteln "
  // 459:   Invalid arguments!
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__25_59;
  result_count = 0;
  myself = get__ewriteln();
  func = myself->type;
  frame->cont = cont__25_60;
}
static void cont__25_60(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 460: show_commands
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = var._show_commands;
  func = myself->type;
  frame->cont = cont__25_61;
}
static void cont__25_61(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 461: exit 1
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
  // 401: ... -> command_id
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
  // 403: command_line_arguments.is_empty
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
  // 402: if
  // 403:   command_line_arguments.is_empty:
  // 404:     ewriteln "
  // 405:       No command specified!
  // 406:     show_commands
  // 407:     exit 1
  // 408:   :
  // 409:     case
  // 410:       command_line_arguments(1)
  // 411:       "copyright":
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
  // 463: check_arguments command_line_arguments templates
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
  // 401: ... command_id.is_defined
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
  // 401: if command_id.is_defined (-> command_id):
  // 402:   if
  // 403:     command_line_arguments.is_empty:
  // 404:       ewriteln "
  // 405:         No command specified!
  // 406:       show_commands
  // 407:       exit 1
  // 408:     :
  // 409:       case
  // 410:         command_line_arguments(1)
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
static void entry__25_1(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // templates: 0
  frame->slots[0] /* templates */ = from_arguments(0, argument_count-0);
  // 400: command_id_count > 0
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
  // 462: :
  // 463:   check_arguments command_line_arguments templates
  frame->slots[2] /* temp__2 */ = create_closure(entry__25_3, 0);
  // 399: if
  // 400:   command_id_count > 0:
  // 401:     if command_id.is_defined (-> command_id):
  // 402:       if
  // 403:         command_line_arguments.is_empty:
  // 404:           ewriteln "
  // 405:             No command specified!
  // 406:           show_commands
  // 407:           exit 1
  // 408:         :
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
  unique__1_1 = collect_node(unique__1_1);
  var.std__VALUED_OPTION = collect_node(var.std__VALUED_OPTION);
  unique__2_1 = collect_node(unique__2_1);
  var.std__MULTI_VALUED_OPTION = collect_node(var.std__MULTI_VALUED_OPTION);
  unique__3_1 = collect_node(unique__3_1);
  var.std__MANDATORY_PARAMETER = collect_node(var.std__MANDATORY_PARAMETER);
  unique__4_1 = collect_node(unique__4_1);
  var.std__OPTIONAL_PARAMETER = collect_node(var.std__OPTIONAL_PARAMETER);
  unique__5_1 = collect_node(unique__5_1);
  var.std__SOME_PARAMETERS = collect_node(var.std__SOME_PARAMETERS);
  unique__6_1 = collect_node(unique__6_1);
  var.std__MANY_PARAMETERS = collect_node(var.std__MANY_PARAMETERS);
  unique__7_1 = collect_node(unique__7_1);
  var._program_version = collect_node(var._program_version);
  var._program_copyright = collect_node(var._program_copyright);
  var.std__copyright = collect_node(var.std__copyright);
  func__10_1 = collect_node(func__10_1);
  var.std__version = collect_node(var.std__version);
  func__11_1 = collect_node(func__11_1);
  var.std__extract_options = collect_node(var.std__extract_options);
  string__12_45 = collect_node(string__12_45);
  string__12_46 = collect_node(string__12_46);
  func__12_1 = collect_node(func__12_1);
  var.std__extract_some_options = collect_node(var.std__extract_some_options);
  func__13_1 = collect_node(func__13_1);
  var._display_table = collect_node(var._display_table);
  string__14_11 = collect_node(string__14_11);
  string__14_19 = collect_node(string__14_19);
  func__14_1 = collect_node(func__14_1);
  var._command_id = collect_node(var._command_id);
  var._command_id_count = collect_node(var._command_id_count);
  var._command_names = collect_node(var._command_names);
  var._command_descriptions = collect_node(var._command_descriptions);
  var._show_version = collect_node(var._show_version);
  string__19_2 = collect_node(string__19_2);
  string__19_3 = collect_node(string__19_3);
  func__19_1 = collect_node(func__19_1);
  var._show_copyright = collect_node(var._show_copyright);
  func__20_1 = collect_node(func__20_1);
  var._check_arguments = collect_node(var._check_arguments);
  string__21_7 = collect_node(string__21_7);
  string__21_35 = collect_node(string__21_35);
  string__21_41 = collect_node(string__21_41);
  string__21_42 = collect_node(string__21_42);
  string__21_44 = collect_node(string__21_44);
  string__21_45 = collect_node(string__21_45);
  func__21_50 = collect_node(func__21_50);
  string__21_52 = collect_node(string__21_52);
  string__21_56 = collect_node(string__21_56);
  string__21_59 = collect_node(string__21_59);
  string__21_71 = collect_node(string__21_71);
  string__21_76 = collect_node(string__21_76);
  string__21_80 = collect_node(string__21_80);
  string__21_83 = collect_node(string__21_83);
  string__21_94 = collect_node(string__21_94);
  string__21_95 = collect_node(string__21_95);
  string__21_98 = collect_node(string__21_98);
  func__21_97 = collect_node(func__21_97);
  string__21_102 = collect_node(string__21_102);
  string__21_160 = collect_node(string__21_160);
  string__21_168 = collect_node(string__21_168);
  func__21_171 = collect_node(func__21_171);
  string__21_177 = collect_node(string__21_177);
  string__21_186 = collect_node(string__21_186);
  string__21_201 = collect_node(string__21_201);
  string__21_209 = collect_node(string__21_209);
  string__21_210 = collect_node(string__21_210);
  string__21_286 = collect_node(string__21_286);
  string__21_287 = collect_node(string__21_287);
  func__21_1 = collect_node(func__21_1);
  var.std__program_commands = collect_node(var.std__program_commands);
  func__22_1 = collect_node(func__22_1);
  var.std__command_parameters = collect_node(var.std__command_parameters);
  string__23_11 = collect_node(string__23_11);
  string__23_25 = collect_node(string__23_25);
  func__23_1 = collect_node(func__23_1);
  var._show_commands = collect_node(var._show_commands);
  func__24_3 = collect_node(func__24_3);
  string__24_7 = collect_node(string__24_7);
  string__24_9 = collect_node(string__24_9);
  string__24_10 = collect_node(string__24_10);
  string__24_20 = collect_node(string__24_20);
  string__24_21 = collect_node(string__24_21);
  string__24_27 = collect_node(string__24_27);
  string__24_28 = collect_node(string__24_28);
  func__24_1 = collect_node(func__24_1);
  var.std__program_parameters = collect_node(var.std__program_parameters);
  func__25_6 = collect_node(func__25_6);
  string__25_10 = collect_node(string__25_10);
  func__25_9 = collect_node(func__25_9);
  string__25_15 = collect_node(string__25_15);
  func__25_18 = collect_node(func__25_18);
  func__25_16 = collect_node(func__25_16);
  string__25_20 = collect_node(string__25_20);
  func__25_23 = collect_node(func__25_23);
  string__25_27 = collect_node(string__25_27);
  string__25_31 = collect_node(string__25_31);
  func__25_30 = collect_node(func__25_30);
  func__25_28 = collect_node(func__25_28);
  string__25_33 = collect_node(string__25_33);
  string__25_35 = collect_node(string__25_35);
  func__25_34 = collect_node(func__25_34);
  string__25_37 = collect_node(string__25_37);
  string__25_41 = collect_node(string__25_41);
  func__25_40 = collect_node(func__25_40);
  func__25_38 = collect_node(func__25_38);
  string__25_44 = collect_node(string__25_44);
  func__25_25 = collect_node(func__25_25);
  string__25_48 = collect_node(string__25_48);
  func__25_47 = collect_node(func__25_47);
  func__25_21 = collect_node(func__25_21);
  string__25_51 = collect_node(string__25_51);
  func__25_54 = collect_node(func__25_54);
  func__25_52 = collect_node(func__25_52);
  string__25_59 = collect_node(string__25_59);
  func__25_13 = collect_node(func__25_13);
  func__25_7 = collect_node(func__25_7);
  func__25_4 = collect_node(func__25_4);
  func__25_1 = collect_node(func__25_1);
  character__47 = collect_node(character__47);
  character__63 = collect_node(character__63);
  character__10 = collect_node(character__10);
  character__44 = collect_node(character__44);
  number__0 = collect_node(number__0);
  number__3 = collect_node(number__3);
  character__32 = collect_node(character__32);
  character__43 = collect_node(character__43);
  number__1 = collect_node(number__1);
  number__2 = collect_node(number__2);
  character__42 = collect_node(character__42);
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
  set_module("basic__parameters");
  set_used_namespaces(used_namespaces);
  character__47 = create_future();
  character__63 = create_future();
  character__10 = create_future();
  character__44 = create_future();
  number__0 = create_future();
  number__3 = create_future();
  character__32 = create_future();
  character__43 = create_future();
  number__1 = create_future();
  number__2 = create_future();
  character__42 = create_future();
  unique__1_1 = register_unique_item("BOOLEAN_OPTION");
  assign_value(&var._BOOLEAN_OPTION, unique__1_1);
  unique__2_1 = register_unique_item("std__VALUED_OPTION");
  assign_value(&var.std__VALUED_OPTION, unique__2_1);
  define_single_assign_static("std", "VALUED_OPTION", get__std__VALUED_OPTION, &var.std__VALUED_OPTION);
  unique__3_1 = register_unique_item("std__MULTI_VALUED_OPTION");
  assign_value(&var.std__MULTI_VALUED_OPTION, unique__3_1);
  define_single_assign_static("std", "MULTI_VALUED_OPTION", get__std__MULTI_VALUED_OPTION, &var.std__MULTI_VALUED_OPTION);
  unique__4_1 = register_unique_item("std__MANDATORY_PARAMETER");
  assign_value(&var.std__MANDATORY_PARAMETER, unique__4_1);
  define_single_assign_static("std", "MANDATORY_PARAMETER", get__std__MANDATORY_PARAMETER, &var.std__MANDATORY_PARAMETER);
  unique__5_1 = register_unique_item("std__OPTIONAL_PARAMETER");
  assign_value(&var.std__OPTIONAL_PARAMETER, unique__5_1);
  define_single_assign_static("std", "OPTIONAL_PARAMETER", get__std__OPTIONAL_PARAMETER, &var.std__OPTIONAL_PARAMETER);
  unique__6_1 = register_unique_item("std__SOME_PARAMETERS");
  assign_value(&var.std__SOME_PARAMETERS, unique__6_1);
  define_single_assign_static("std", "SOME_PARAMETERS", get__std__SOME_PARAMETERS, &var.std__SOME_PARAMETERS);
  unique__7_1 = register_unique_item("std__MANY_PARAMETERS");
  assign_value(&var.std__MANY_PARAMETERS, unique__7_1);
  define_single_assign_static("std", "MANY_PARAMETERS", get__std__MANY_PARAMETERS, &var.std__MANY_PARAMETERS);
  func__10_1 = create_future();
  define_single_assign_static("std", "copyright", get__std__copyright, &var.std__copyright);
  func__11_1 = create_future();
  define_single_assign_static("std", "version", get__std__version, &var.std__version);
  string__12_45 = from_latin_1_string("Invalid option ", 15);
  string__12_46 = from_latin_1_string("!", 1);
  func__12_1 = create_future();
  define_single_assign_static("std", "extract_options", get__std__extract_options, &var.std__extract_options);
  func__13_1 = create_future();
  define_single_assign_static("std", "extract_some_options", get__std__extract_some_options, &var.std__extract_some_options);
  string__14_11 = from_latin_1_string("  ", 2);
  string__14_19 = from_latin_1_string(" ", 1);
  func__14_1 = create_future();
  string__19_2 = from_latin_1_string(" ", 1);
  string__19_3 = from_latin_1_string("\012\012", 2);
  func__19_1 = create_future();
  func__20_1 = create_future();
  string__21_7 = from_latin_1_string("valid values:", 13);
  string__21_35 = from_latin_1_string("Usage:", 6);
  string__21_41 = from_latin_1_string("  ", 2);
  string__21_42 = from_latin_1_string(" --copyright", 12);
  string__21_44 = from_latin_1_string("  ", 2);
  string__21_45 = from_latin_1_string(" --help", 7);
  func__21_50 = create_future();
  string__21_52 = from_latin_1_string("  ", 2);
  string__21_56 = from_latin_1_string(" ", 1);
  string__21_59 = from_latin_1_string("\012Parameters:\012", 13);
  string__21_71 = from_latin_1_string("\012Options:\012", 10);
  string__21_76 = from_latin_1_string("--", 2);
  string__21_80 = from_latin_1_string(" VALUE", 6);
  string__21_83 = from_latin_1_string(" VALUES", 7);
  string__21_94 = from_latin_1_string("Too few arguments for ", 22);
  string__21_95 = from_latin_1_string("-command!\012", 10);
  string__21_98 = from_latin_1_string("Too few arguments!\012", 19);
  func__21_97 = create_future();
  string__21_102 = from_latin_1_string("Too many arguments!\012", 20);
  string__21_160 = from_latin_1_string("--help", 6);
  string__21_168 = from_latin_1_string("--copyright", 11);
  func__21_171 = create_future();
  string__21_177 = from_latin_1_string("--version", 9);
  string__21_186 = from_latin_1_string("--", 2);
  string__21_201 = from_latin_1_string("--", 2);
  string__21_209 = from_latin_1_string("Invalid option: ", 16);
  string__21_210 = from_latin_1_string("!", 1);
  string__21_286 = from_latin_1_string("Invalid argument value for ", 27);
  string__21_287 = from_latin_1_string("!\012", 2);
  func__21_1 = create_future();
  func__22_1 = create_future();
  define_single_assign_static("std", "program_commands", get__std__program_commands, &var.std__program_commands);
  string__23_11 = from_latin_1_string("help", 4);
  string__23_25 = from_latin_1_string("--help", 6);
  func__23_1 = create_future();
  define_single_assign_static("std", "command_parameters", get__std__command_parameters, &var.std__command_parameters);
  func__24_3 = create_future();
  string__24_7 = from_latin_1_string("Available commands:", 19);
  string__24_9 = from_latin_1_string("help", 4);
  string__24_10 = from_latin_1_string("display help for the specified command", 38);
  string__24_20 = from_latin_1_string("copyright", 9);
  string__24_21 = from_latin_1_string("display the copyright message", 29);
  string__24_27 = from_latin_1_string("version", 7);
  string__24_28 = from_latin_1_string("display the version number", 26);
  func__24_1 = create_future();
  func__25_6 = create_future();
  string__25_10 = from_latin_1_string("No command specified!\012", 22);
  func__25_9 = create_future();
  string__25_15 = from_latin_1_string("copyright", 9);
  func__25_18 = create_future();
  func__25_16 = create_future();
  string__25_20 = from_latin_1_string("help", 4);
  func__25_23 = create_future();
  string__25_27 = from_latin_1_string("copyright", 9);
  string__25_31 = from_latin_1_string("Usage:\012  sigi copyright\012", 24);
  func__25_30 = create_future();
  func__25_28 = create_future();
  string__25_33 = from_latin_1_string("help", 4);
  string__25_35 = from_latin_1_string("Usage:\012  sigi help COMMAND\012\012Parameter:\012  COMMAND  the command for which to retrieve help\012", 89);
  func__25_34 = create_future();
  string__25_37 = from_latin_1_string("version", 7);
  string__25_41 = from_latin_1_string("Usage:\012  sigi version\012", 22);
  func__25_40 = create_future();
  func__25_38 = create_future();
  string__25_44 = from_latin_1_string("Invalid command name!\012", 22);
  func__25_25 = create_future();
  string__25_48 = from_latin_1_string("Too many arguments!\012", 20);
  func__25_47 = create_future();
  func__25_21 = create_future();
  string__25_51 = from_latin_1_string("version", 7);
  func__25_54 = create_future();
  func__25_52 = create_future();
  string__25_59 = from_latin_1_string("Invalid arguments!\012", 19);
  func__25_13 = create_future();
  func__25_7 = create_future();
  func__25_4 = create_future();
  func__25_1 = create_future();
  define_single_assign_static("std", "program_parameters", get__std__program_parameters, &var.std__program_parameters);
}

static int already_run_phase_3 = false;

EXPORT void phase_3__basic__parameters(void) {
  if (already_run_phase_3) return;
  already_run_phase_3 = true;
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

static int already_run_phase_4 = false;

EXPORT void phase_4__basic__parameters(void) {
  if (already_run_phase_4) return;
  already_run_phase_4 = true;
  assign_value(&character__47, from_uchar32(47));
  assign_value(&character__63, from_uchar32(63));
  assign_value(&character__10, from_uchar32(10));
  assign_value(&character__44, from_uchar32(44));
  assign_value(&number__0, from_uint32(0U));
  assign_value(&number__3, from_uint32(3U));
  assign_value(&character__32, from_uchar32(32));
  assign_value(&character__43, from_uchar32(43));
  assign_value(&number__1, from_uint32(1U));
  assign_value(&number__2, from_uint32(2U));
  assign_value(&character__42, from_uchar32(42));
  assign_variable(&var.std__copyright, &func__10_1);
  assign_variable(&var.std__version, &func__11_1);
  assign_variable(&var.std__extract_options, &func__12_1);
  assign_variable(&var.std__extract_some_options, &func__13_1);
  assign_variable(&var._display_table, &func__14_1);
  assign_variable(&var._show_version, &func__19_1);
  assign_variable(&var._show_copyright, &func__20_1);
  assign_variable(&var._check_arguments, &func__21_1);
  assign_variable(&var.std__program_commands, &func__22_1);
  assign_variable(&var.std__command_parameters, &func__23_1);
  assign_variable(&var._show_commands, &func__24_1);
  assign_variable(&var.std__program_parameters, &func__25_1);
}

static int already_run_phase_5 = false;

EXPORT void phase_5__basic__parameters(void) {
  if (already_run_phase_5) return;
  already_run_phase_5 = true;
  assign_value(&func__10_1, create_function(entry__10_1, 1));
  assign_value(&func__11_1, create_function(entry__11_1, 1));
  assign_value(&func__12_1, create_function(entry__12_1, -1));
  assign_value(&func__13_1, create_function(entry__13_1, -1));
  assign_value(&func__14_1, create_function(entry__14_1, 1));
  assign_value(&func__19_1, create_function(entry__19_1, 1));
  assign_value(&func__20_1, create_function(entry__20_1, 0));
  assign_value(&func__21_50, create_function(entry__21_50, 0));
  assign_value(&func__21_97, create_function(entry__21_97, 0));
  assign_value(&func__21_171, create_function(entry__21_171, 0));
  assign_value(&func__21_1, create_function(entry__21_1, -1));
  assign_value(&func__22_1, create_function(entry__22_1, -1));
  assign_value(&func__23_1, create_function(entry__23_1, -1));
  assign_value(&func__24_3, create_function(entry__24_3, 0));
  assign_value(&func__24_1, create_function(entry__24_1, 0));
  assign_value(&func__25_6, create_function(entry__25_6, 0));
  assign_value(&func__25_9, create_function(entry__25_9, 0));
  assign_value(&func__25_18, create_function(entry__25_18, 0));
  assign_value(&func__25_16, create_function(entry__25_16, 0));
  assign_value(&func__25_23, create_function(entry__25_23, 0));
  assign_value(&func__25_30, create_function(entry__25_30, 0));
  assign_value(&func__25_28, create_function(entry__25_28, 0));
  assign_value(&func__25_34, create_function(entry__25_34, 0));
  assign_value(&func__25_40, create_function(entry__25_40, 0));
  assign_value(&func__25_38, create_function(entry__25_38, 0));
  assign_value(&func__25_25, create_function(entry__25_25, 0));
  assign_value(&func__25_47, create_function(entry__25_47, 0));
  assign_value(&func__25_21, create_function(entry__25_21, 0));
  assign_value(&func__25_54, create_function(entry__25_54, 0));
  assign_value(&func__25_52, create_function(entry__25_52, 0));
  assign_value(&func__25_13, create_function(entry__25_13, 0));
  assign_value(&func__25_7, create_function(entry__25_7, 0));
  assign_value(&func__25_4, create_function(entry__25_4, 0));
  assign_value(&func__25_1, create_function(entry__25_1, -1));
  register_collector(collect__basic__parameters);
}
