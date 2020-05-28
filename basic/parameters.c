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
IMPORT void set_module(const char *name);
IMPORT NODE *from_uchar32(unsigned int chr);
IMPORT NODE *from_uint32(uint32_t val);
IMPORT NODE *register_unique_item(const char *name);
IMPORT NODE *create_function(FUNC func, int par_count);
IMPORT NODE *from_latin_1_string(const char *str, long len);
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
static NODE *func__std__copyright_1;
static void entry__std__copyright_1(void);
static FRAME_INFO frame__std__copyright_1 = {1, {"msg"}};
static NODE *get__std__copyright(void) {
  return var.std__copyright;
}
static NODE *func__std__version_1;
static void entry__std__version_1(void);
static FRAME_INFO frame__std__version_1 = {1, {"no"}};
static NODE *get__std__version(void) {
  return var.std__version;
}
static NODE *func__std__extract_options_1;
static void entry__std__extract_options_1(void);
static FRAME_INFO frame__std__extract_options_1 = {4, {"options", "templates", "results", "parameters"}};
static NODE *func__std__extract_options_2;
static void entry__std__extract_options_2(void);
static FRAME_INFO frame__std__extract_options_2 = {3, {"options", "parameters", "idx"}};
static NODE *func__std__extract_options_3;
static void entry__std__extract_options_3(void);
static FRAME_INFO frame__std__extract_options_3 = {4, {"option", "idx", "parameters", "options"}};
static void cont__std__extract_options_4(void);
static NODE *func__std__extract_options_5;
static void entry__std__extract_options_5(void);
static FRAME_INFO frame__std__extract_options_5 = {1, {"idx"}};
static void cont__std__extract_options_6(void);
static NODE *func__std__extract_options_7;
static void entry__std__extract_options_7(void);
static FRAME_INFO frame__std__extract_options_7 = {4, {"parameters", "option", "options", "idx"}};
static void cont__std__extract_options_8(void);
static void cont__std__extract_options_9(void);
static void cont__std__extract_options_10(void);
static NODE *func__std__extract_options_11;
static void entry__std__extract_options_11(void);
static FRAME_INFO frame__std__extract_options_11 = {5, {"template", "options", "results", "result", "idx"}};
static void cont__std__extract_options_12(void);
static void cont__std__extract_options_13(void);
static NODE *func__std__extract_options_14;
static void entry__std__extract_options_14(void);
static FRAME_INFO frame__std__extract_options_14 = {4, {"result", "options", "template", "idx"}};
static NODE *func__std__extract_options_15;
static void entry__std__extract_options_15(void);
static FRAME_INFO frame__std__extract_options_15 = {5, {"option", "template", "options", "idx", "result"}};
static void cont__std__extract_options_16(void);
static void cont__std__extract_options_17(void);
static void cont__std__extract_options_18(void);
static NODE *func__std__extract_options_19;
static void entry__std__extract_options_19(void);
static FRAME_INFO frame__std__extract_options_19 = {4, {"options", "idx", "result", "option"}};
static void cont__std__extract_options_20(void);
static void cont__std__extract_options_21(void);
static void cont__std__extract_options_22(void);
static NODE *func__std__extract_options_23;
static void entry__std__extract_options_23(void);
static FRAME_INFO frame__std__extract_options_23 = {1, {"idx"}};
static void cont__std__extract_options_24(void);
static NODE *func__std__extract_options_25;
static void entry__std__extract_options_25(void);
static FRAME_INFO frame__std__extract_options_25 = {4, {"options", "template", "idx", "result"}};
static NODE *func__std__extract_options_26;
static void entry__std__extract_options_26(void);
static FRAME_INFO frame__std__extract_options_26 = {5, {"option", "template", "options", "idx", "result"}};
static void cont__std__extract_options_27(void);
static void cont__std__extract_options_28(void);
static void cont__std__extract_options_29(void);
static NODE *func__std__extract_options_30;
static void entry__std__extract_options_30(void);
static FRAME_INFO frame__std__extract_options_30 = {4, {"options", "idx", "result", "option"}};
static void cont__std__extract_options_31(void);
static void cont__std__extract_options_32(void);
static NODE *func__std__extract_options_33;
static void entry__std__extract_options_33(void);
static FRAME_INFO frame__std__extract_options_33 = {1, {"idx"}};
static void cont__std__extract_options_34(void);
static void cont__std__extract_options_35(void);
static void cont__std__extract_options_36(void);
static void cont__std__extract_options_37(void);
static void cont__std__extract_options_38(void);
static NODE *func__std__extract_options_39;
static void entry__std__extract_options_39(void);
static FRAME_INFO frame__std__extract_options_39 = {1, {"options"}};
static void cont__std__extract_options_40(void);
static void cont__std__extract_options_41(void);
static void cont__std__extract_options_42(void);
static void cont__std__extract_options_43(void);
static void cont__std__extract_options_44(void);
static NODE *string__629e8589dc7e42e;
static NODE *string__578a5af303e9cc0;
static void cont__std__extract_options_47(void);
static void cont__std__extract_options_48(void);
static NODE *get__std__extract_options(void) {
  return var.std__extract_options;
}
static NODE *func__std__extract_some_options_1;
static void entry__std__extract_some_options_1(void);
static FRAME_INFO frame__std__extract_some_options_1 = {3, {"options", "templates", "results"}};
static NODE *func__std__extract_some_options_2;
static void entry__std__extract_some_options_2(void);
static FRAME_INFO frame__std__extract_some_options_2 = {5, {"template", "options", "results", "result", "idx"}};
static void cont__std__extract_some_options_3(void);
static void cont__std__extract_some_options_4(void);
static NODE *func__std__extract_some_options_5;
static void entry__std__extract_some_options_5(void);
static FRAME_INFO frame__std__extract_some_options_5 = {4, {"result", "options", "template", "idx"}};
static NODE *func__std__extract_some_options_6;
static void entry__std__extract_some_options_6(void);
static FRAME_INFO frame__std__extract_some_options_6 = {5, {"option", "template", "options", "idx", "result"}};
static void cont__std__extract_some_options_7(void);
static void cont__std__extract_some_options_8(void);
static void cont__std__extract_some_options_9(void);
static NODE *func__std__extract_some_options_10;
static void entry__std__extract_some_options_10(void);
static FRAME_INFO frame__std__extract_some_options_10 = {4, {"options", "idx", "result", "option"}};
static void cont__std__extract_some_options_11(void);
static void cont__std__extract_some_options_12(void);
static void cont__std__extract_some_options_13(void);
static NODE *func__std__extract_some_options_14;
static void entry__std__extract_some_options_14(void);
static FRAME_INFO frame__std__extract_some_options_14 = {1, {"idx"}};
static void cont__std__extract_some_options_15(void);
static NODE *func__std__extract_some_options_16;
static void entry__std__extract_some_options_16(void);
static FRAME_INFO frame__std__extract_some_options_16 = {4, {"options", "template", "idx", "result"}};
static NODE *func__std__extract_some_options_17;
static void entry__std__extract_some_options_17(void);
static FRAME_INFO frame__std__extract_some_options_17 = {5, {"option", "template", "options", "idx", "result"}};
static void cont__std__extract_some_options_18(void);
static NODE *func__std__extract_some_options_19;
static void entry__std__extract_some_options_19(void);
static FRAME_INFO frame__std__extract_some_options_19 = {2, {"option", "template"}};
static void cont__std__extract_some_options_20(void);
static void cont__std__extract_some_options_21(void);
static void cont__std__extract_some_options_22(void);
static void cont__std__extract_some_options_23(void);
static NODE *func__std__extract_some_options_24;
static void entry__std__extract_some_options_24(void);
static FRAME_INFO frame__std__extract_some_options_24 = {4, {"options", "idx", "result", "option"}};
static void cont__std__extract_some_options_25(void);
static void cont__std__extract_some_options_26(void);
static NODE *func__std__extract_some_options_27;
static void entry__std__extract_some_options_27(void);
static FRAME_INFO frame__std__extract_some_options_27 = {1, {"idx"}};
static void cont__std__extract_some_options_28(void);
static void cont__std__extract_some_options_29(void);
static void cont__std__extract_some_options_30(void);
static void cont__std__extract_some_options_31(void);
static NODE *get__std__extract_some_options(void) {
  return var.std__extract_some_options;
}
static NODE *func__display_table_1;
static void entry__display_table_1(void);
static FRAME_INFO frame__display_table_1 = {2, {"tab", "first_column_width"}};
static NODE *func__display_table_2;
static void entry__display_table_2(void);
static FRAME_INFO frame__display_table_2 = {2, {"entry", "first_column_width"}};
static void cont__display_table_3(void);
static void cont__display_table_4(void);
static void cont__display_table_5(void);
static void cont__display_table_6(void);
static void cont__display_table_7(void);
static NODE *func__display_table_8;
static void entry__display_table_8(void);
static FRAME_INFO frame__display_table_8 = {2, {"entry", "first_column_width"}};
static void cont__display_table_9(void);
static void cont__display_table_10(void);
static NODE *string__2d7981f4e6082be5;
static void cont__display_table_12(void);
static void cont__display_table_13(void);
static NODE *func__display_table_14;
static void entry__display_table_14(void);
static FRAME_INFO frame__display_table_14 = {3, {"idx", "line", "first_column_width"}};
static void cont__display_table_15(void);
static void cont__display_table_16(void);
static NODE *func__display_table_17;
static void entry__display_table_17(void);
static FRAME_INFO frame__display_table_17 = {1, {"first_column_width"}};
static void cont__display_table_18(void);
static NODE *string__578a5af303e9cc1;
static void cont__display_table_20(void);
static void cont__display_table_21(void);
static NODE *func__show_version_1;
static void entry__show_version_1(void);
static FRAME_INFO frame__show_version_1 = {1, {"command_name"}};
static NODE *string__2d7981f4e7582bcf;
static void cont__show_version_3(void);
static NODE *func__show_copyright_1;
static void entry__show_copyright_1(void);
static FRAME_INFO frame__show_copyright_1 = {0, {}};
static NODE *func__check_arguments_1;
static void entry__check_arguments_1(void);
static FRAME_INFO frame__check_arguments_1 = {18, {"command", "arguments", "templates", "results", "options", "parameters", "names", "kinds", "possible_values", "default_values", "conversions", "help_messages", "command_name", "help_message", "show_usage", "too_few_arguments_error", "too_many_arguments_error", "last_idx"}};
static NODE *func__check_arguments_2;
static void entry__check_arguments_2(void);
static FRAME_INFO frame__check_arguments_2 = {7, {"idx", "help_messages", "possible_values", "default_values", "message", "possible_value", "default_value"}};
static void cont__check_arguments_3(void);
static void cont__check_arguments_4(void);
static void cont__check_arguments_5(void);
static NODE *func__check_arguments_6;
static void entry__check_arguments_6(void);
static FRAME_INFO frame__check_arguments_6 = {2, {"message", "possible_value"}};
static NODE *string__e8329800b0d69ed2;
static void cont__check_arguments_8(void);
static NODE *func__check_arguments_9;
static void entry__check_arguments_9(void);
static FRAME_INFO frame__check_arguments_9 = {2, {"value", "message"}};
static void cont__check_arguments_10(void);
static void cont__check_arguments_11(void);
static void cont__check_arguments_12(void);
static void cont__check_arguments_13(void);
static void cont__check_arguments_14(void);
static void cont__check_arguments_15(void);
static void cont__check_arguments_16(void);
static NODE *func__check_arguments_17;
static void entry__check_arguments_17(void);
static FRAME_INFO frame__check_arguments_17 = {2, {"message", "default_value"}};
static void cont__check_arguments_18(void);
static void cont__check_arguments_19(void);
static NODE *string__7f5cac89d5ba4088;
static NODE *string__578a5af303e9cc8;
static void cont__check_arguments_22(void);
static void cont__check_arguments_23(void);
static void cont__check_arguments_24(void);
static NODE *func__check_arguments_25;
static void entry__check_arguments_25(void);
static FRAME_INFO frame__check_arguments_25 = {8, {"kinds", "command_name", "command", "parameters", "help_message", "options", "help_messages", "parameter_name"}};
static NODE *func__check_arguments_26;
static void entry__check_arguments_26(void);
static FRAME_INFO frame__check_arguments_26 = {4, {"parameter", "idx", "kinds", "buf"}};
static void cont__check_arguments_27(void);
static void cont__check_arguments_28(void);
static NODE *func__check_arguments_29;
static void entry__check_arguments_29(void);
static FRAME_INFO frame__check_arguments_29 = {1, {"buf"}};
static void cont__check_arguments_30(void);
static NODE *func__check_arguments_31;
static void entry__check_arguments_31(void);
static FRAME_INFO frame__check_arguments_31 = {1, {"buf"}};
static void cont__check_arguments_32(void);
static NODE *func__check_arguments_33;
static void entry__check_arguments_33(void);
static FRAME_INFO frame__check_arguments_33 = {1, {"buf"}};
static void cont__check_arguments_34(void);
static void cont__check_arguments_35(void);
static void cont__check_arguments_36(void);
static NODE *func__check_arguments_37;
static void entry__check_arguments_37(void);
static FRAME_INFO frame__check_arguments_37 = {1, {"command_name"}};
static void cont__check_arguments_38(void);
static void cont__check_arguments_39(void);
static NODE *func__check_arguments_40;
static void entry__check_arguments_40(void);
static FRAME_INFO frame__check_arguments_40 = {2, {"command_name", "command"}};
static void cont__check_arguments_41(void);
static void cont__check_arguments_42(void);
static void cont__check_arguments_43(void);
static void cont__check_arguments_44(void);
static NODE *string__5a1f579a019362ed;
static void cont__check_arguments_46(void);
static void cont__check_arguments_47(void);
static NODE *func__check_arguments_48;
static void entry__check_arguments_48(void);
static FRAME_INFO frame__check_arguments_48 = {1, {"command_name"}};
static void cont__check_arguments_49(void);
static NODE *func__check_arguments_50;
static void entry__check_arguments_50(void);
static FRAME_INFO frame__check_arguments_50 = {1, {"command_name"}};
static NODE *string__d89f1181d9c5276e;
static void cont__check_arguments_52(void);
static NODE *string__a3040cb415de108a;
static void cont__check_arguments_54(void);
static void cont__check_arguments_55(void);
static NODE *func__check_arguments_56;
static void entry__check_arguments_56(void);
static FRAME_INFO frame__check_arguments_56 = {1, {"command"}};
static void cont__check_arguments_57(void);
static NODE *func__check_arguments_58;
static void entry__check_arguments_58(void);
static FRAME_INFO frame__check_arguments_58 = {0, {}};
static void cont__check_arguments_59(void);
static void cont__check_arguments_60(void);
static NODE *func__check_arguments_61;
static void entry__check_arguments_61(void);
static FRAME_INFO frame__check_arguments_61 = {3, {"parameter", "idx", "parameter_name"}};
static void cont__check_arguments_62(void);
static void cont__check_arguments_63(void);
static void cont__check_arguments_64(void);
static NODE *string__a67e424a37fc0741;
static void cont__check_arguments_66(void);
static NODE *func__check_arguments_67;
static void entry__check_arguments_67(void);
static FRAME_INFO frame__check_arguments_67 = {4, {"parameters", "parameter_name", "help_message", "tab"}};
static NODE *func__check_arguments_68;
static void entry__check_arguments_68(void);
static FRAME_INFO frame__check_arguments_68 = {5, {"parameter", "idx", "tab", "parameter_name", "help_message"}};
static void cont__check_arguments_69(void);
static void cont__check_arguments_70(void);
static void cont__check_arguments_71(void);
static void cont__check_arguments_72(void);
static void cont__check_arguments_73(void);
static void cont__check_arguments_74(void);
static void cont__check_arguments_75(void);
static NODE *func__check_arguments_76;
static void entry__check_arguments_76(void);
static FRAME_INFO frame__check_arguments_76 = {3, {"options", "kinds", "help_messages"}};
static NODE *string__293744df0bfb878b;
static void cont__check_arguments_78(void);
static NODE *func__check_arguments_79;
static void entry__check_arguments_79(void);
static FRAME_INFO frame__check_arguments_79 = {4, {"options", "kinds", "help_messages", "tab"}};
static NODE *func__check_arguments_80;
static void entry__check_arguments_80(void);
static FRAME_INFO frame__check_arguments_80 = {6, {"option", "idx", "kinds", "tab", "help_messages", "option_name"}};
static NODE *func__check_arguments_81;
static void entry__check_arguments_81(void);
static FRAME_INFO frame__check_arguments_81 = {4, {"option", "kinds", "idx", "buf"}};
static NODE *string__2d7981f4e6602be8;
static void cont__check_arguments_83(void);
static void cont__check_arguments_84(void);
static NODE *func__check_arguments_85;
static void entry__check_arguments_85(void);
static FRAME_INFO frame__check_arguments_85 = {1, {"buf"}};
static NODE *string__1a1f5d6080113292;
static void cont__check_arguments_87(void);
static NODE *func__check_arguments_88;
static void entry__check_arguments_88(void);
static FRAME_INFO frame__check_arguments_88 = {1, {"buf"}};
static NODE *string__eb0400899490d0a9;
static void cont__check_arguments_90(void);
static void cont__check_arguments_91(void);
static void cont__check_arguments_92(void);
static void cont__check_arguments_93(void);
static void cont__check_arguments_94(void);
static void cont__check_arguments_95(void);
static void cont__check_arguments_96(void);
static NODE *func__check_arguments_97;
static void entry__check_arguments_97(void);
static FRAME_INFO frame__check_arguments_97 = {2, {"command", "show_usage"}};
static void cont__check_arguments_98(void);
static NODE *func__check_arguments_99;
static void entry__check_arguments_99(void);
static FRAME_INFO frame__check_arguments_99 = {1, {"command"}};
static NODE *string__1fe132c840060c77;
static NODE *string__2952791d2723646b;
static void cont__check_arguments_102(void);
static NODE *func__check_arguments_103;
static void entry__check_arguments_103(void);
static FRAME_INFO frame__check_arguments_103 = {0, {}};
static NODE *string__f0948421cb0e2be3;
static void cont__check_arguments_105(void);
static void cont__check_arguments_106(void);
static NODE *func__check_arguments_107;
static void entry__check_arguments_107(void);
static FRAME_INFO frame__check_arguments_107 = {1, {"show_usage"}};
static NODE *string__e3aee165acc437aa;
static void cont__check_arguments_109(void);
static void cont__check_arguments_110(void);
static void cont__check_arguments_111(void);
static void cont__check_arguments_112(void);
static void cont__check_arguments_113(void);
static NODE *func__check_arguments_114;
static void entry__check_arguments_114(void);
static FRAME_INFO frame__check_arguments_114 = {16, {"idx", "template", "possible_values", "names", "kinds", "default_values", "conversions", "help_messages", "results", "options", "parameters", "option", "name", "default_value", "conversion", "help"}};
static void cont__check_arguments_115(void);
static void cont__check_arguments_116(void);
static NODE *func__check_arguments_117;
static void entry__check_arguments_117(void);
static FRAME_INFO frame__check_arguments_117 = {2, {"possible_values", "option"}};
static void cont__check_arguments_118(void);
static void cont__check_arguments_119(void);
static void cont__check_arguments_120(void);
static NODE *func__check_arguments_121;
static void entry__check_arguments_121(void);
static FRAME_INFO frame__check_arguments_121 = {1, {"possible_values"}};
static void cont__check_arguments_122(void);
static void cont__check_arguments_123(void);
static void cont__check_arguments_124(void);
static NODE *func__check_arguments_125;
static void entry__check_arguments_125(void);
static FRAME_INFO frame__check_arguments_125 = {1, {"name"}};
static NODE *func__check_arguments_126;
static void entry__check_arguments_126(void);
static FRAME_INFO frame__check_arguments_126 = {1, {"option"}};
static void cont__check_arguments_127(void);
static void cont__check_arguments_128(void);
static void cont__check_arguments_129(void);
static void cont__check_arguments_130(void);
static void cont__check_arguments_131(void);
static void cont__check_arguments_132(void);
static NODE *func__check_arguments_133;
static void entry__check_arguments_133(void);
static FRAME_INFO frame__check_arguments_133 = {5, {"option", "results", "options", "idx", "kinds"}};
static void cont__check_arguments_134(void);
static NODE *func__check_arguments_135;
static void entry__check_arguments_135(void);
static FRAME_INFO frame__check_arguments_135 = {5, {"results", "options", "option", "idx", "kinds"}};
static void cont__check_arguments_136(void);
static void cont__check_arguments_137(void);
static void cont__check_arguments_138(void);
static NODE *func__check_arguments_139;
static void entry__check_arguments_139(void);
static FRAME_INFO frame__check_arguments_139 = {5, {"option", "results", "options", "name", "idx"}};
static void cont__check_arguments_140(void);
static NODE *func__check_arguments_141;
static void entry__check_arguments_141(void);
static FRAME_INFO frame__check_arguments_141 = {4, {"results", "options", "name", "idx"}};
static void cont__check_arguments_142(void);
static void cont__check_arguments_143(void);
static NODE *func__check_arguments_144;
static void entry__check_arguments_144(void);
static FRAME_INFO frame__check_arguments_144 = {5, {"option", "results", "options", "name", "idx"}};
static void cont__check_arguments_145(void);
static NODE *func__check_arguments_146;
static void entry__check_arguments_146(void);
static FRAME_INFO frame__check_arguments_146 = {4, {"results", "options", "name", "idx"}};
static void cont__check_arguments_147(void);
static void cont__check_arguments_148(void);
static NODE *func__check_arguments_149;
static void entry__check_arguments_149(void);
static FRAME_INFO frame__check_arguments_149 = {5, {"option", "results", "parameters", "name", "idx"}};
static void cont__check_arguments_150(void);
static NODE *func__check_arguments_151;
static void entry__check_arguments_151(void);
static FRAME_INFO frame__check_arguments_151 = {1, {"option"}};
static void cont__check_arguments_152(void);
static void cont__check_arguments_153(void);
static NODE *func__check_arguments_154;
static void entry__check_arguments_154(void);
static FRAME_INFO frame__check_arguments_154 = {4, {"results", "parameters", "name", "idx"}};
static void cont__check_arguments_155(void);
static void cont__check_arguments_156(void);
static NODE *func__check_arguments_157;
static void entry__check_arguments_157(void);
static FRAME_INFO frame__check_arguments_157 = {4, {"results", "parameters", "name", "idx"}};
static void cont__check_arguments_158(void);
static void cont__check_arguments_159(void);
static void cont__check_arguments_160(void);
static void cont__check_arguments_161(void);
static void cont__check_arguments_162(void);
static void cont__check_arguments_163(void);
static NODE *func__check_arguments_164;
static void entry__check_arguments_164(void);
static FRAME_INFO frame__check_arguments_164 = {3, {"arguments", "show_usage", "command_name"}};
static void cont__check_arguments_165(void);
static NODE *string__481f572601de82a7;
static void cont__check_arguments_167(void);
static NODE *func__check_arguments_168;
static void entry__check_arguments_168(void);
static FRAME_INFO frame__check_arguments_168 = {1, {"show_usage"}};
static void cont__check_arguments_169(void);
static void cont__check_arguments_170(void);
static void cont__check_arguments_171(void);
static NODE *func__check_arguments_172;
static void entry__check_arguments_172(void);
static FRAME_INFO frame__check_arguments_172 = {1, {"arguments"}};
static void cont__check_arguments_173(void);
static NODE *string__d29f58972c488aa7;
static void cont__check_arguments_175(void);
static void cont__check_arguments_176(void);
static NODE *func__check_arguments_177;
static void entry__check_arguments_177(void);
static FRAME_INFO frame__check_arguments_177 = {0, {}};
static void cont__check_arguments_178(void);
static void cont__check_arguments_179(void);
static void cont__check_arguments_180(void);
static NODE *func__check_arguments_181;
static void entry__check_arguments_181(void);
static FRAME_INFO frame__check_arguments_181 = {1, {"arguments"}};
static void cont__check_arguments_182(void);
static NODE *string__48e824ee4f7a5d6b;
static void cont__check_arguments_184(void);
static void cont__check_arguments_185(void);
static NODE *func__check_arguments_186;
static void entry__check_arguments_186(void);
static FRAME_INFO frame__check_arguments_186 = {1, {"command_name"}};
static void cont__check_arguments_187(void);
static void cont__check_arguments_188(void);
static NODE *func__check_arguments_189;
static void entry__check_arguments_189(void);
static FRAME_INFO frame__check_arguments_189 = {7, {"arguments", "kinds", "results", "options", "idx", "fetch_option_value", "option_idx"}};
static NODE *func__check_arguments_190;
static void entry__check_arguments_190(void);
static FRAME_INFO frame__check_arguments_190 = {8, {"break", "arguments", "idx", "fetch_option_value", "kinds", "option_idx", "results", "options"}};
static NODE *func__check_arguments_191;
static void entry__check_arguments_191(void);
static FRAME_INFO frame__check_arguments_191 = {9, {"argument", "arguments", "idx", "break", "fetch_option_value", "kinds", "option_idx", "results", "options"}};
static void cont__check_arguments_192(void);
static NODE *func__check_arguments_193;
static void entry__check_arguments_193(void);
static FRAME_INFO frame__check_arguments_193 = {3, {"arguments", "idx", "break"}};
static void cont__check_arguments_194(void);
static void cont__check_arguments_195(void);
static NODE *func__check_arguments_196;
static void entry__check_arguments_196(void);
static FRAME_INFO frame__check_arguments_196 = {7, {"fetch_option_value", "arguments", "idx", "kinds", "option_idx", "results", "argument"}};
static void cont__check_arguments_197(void);
static void cont__check_arguments_198(void);
static NODE *func__check_arguments_199;
static void entry__check_arguments_199(void);
static FRAME_INFO frame__check_arguments_199 = {3, {"results", "option_idx", "argument"}};
static void cont__check_arguments_200(void);
static NODE *func__check_arguments_201;
static void entry__check_arguments_201(void);
static FRAME_INFO frame__check_arguments_201 = {3, {"results", "option_idx", "argument"}};
static void cont__check_arguments_202(void);
static void cont__check_arguments_203(void);
static void cont__check_arguments_204(void);
static NODE *func__check_arguments_205;
static void entry__check_arguments_205(void);
static FRAME_INFO frame__check_arguments_205 = {8, {"argument", "option_idx", "options", "kinds", "results", "fetch_option_value", "arguments", "idx"}};
static void cont__check_arguments_206(void);
static NODE *func__check_arguments_207;
static void entry__check_arguments_207(void);
static FRAME_INFO frame__check_arguments_207 = {8, {"option_idx", "options", "argument", "kinds", "results", "fetch_option_value", "arguments", "idx"}};
static void cont__check_arguments_208(void);
static void cont__check_arguments_209(void);
static void cont__check_arguments_210(void);
static void cont__check_arguments_211(void);
static NODE *func__check_arguments_212;
static void entry__check_arguments_212(void);
static FRAME_INFO frame__check_arguments_212 = {1, {"argument"}};
static NODE *string__42c4ee3f21a0316f;
static void cont__check_arguments_214(void);
static void cont__check_arguments_215(void);
static void cont__check_arguments_216(void);
static void cont__check_arguments_217(void);
static NODE *func__check_arguments_218;
static void entry__check_arguments_218(void);
static FRAME_INFO frame__check_arguments_218 = {2, {"results", "option_idx"}};
static void cont__check_arguments_219(void);
static NODE *func__check_arguments_220;
static void entry__check_arguments_220(void);
static FRAME_INFO frame__check_arguments_220 = {1, {"fetch_option_value"}};
static void cont__check_arguments_221(void);
static void cont__check_arguments_222(void);
static NODE *func__check_arguments_223;
static void entry__check_arguments_223(void);
static FRAME_INFO frame__check_arguments_223 = {1, {"idx"}};
static void cont__check_arguments_224(void);
static void cont__check_arguments_225(void);
static void cont__check_arguments_226(void);
static void cont__check_arguments_227(void);
static NODE *func__check_arguments_228;
static void entry__check_arguments_228(void);
static FRAME_INFO frame__check_arguments_228 = {6, {"break", "templates", "arguments", "too_few_arguments_error", "results", "last_idx"}};
static void cont__check_arguments_229(void);
static NODE *func__check_arguments_230;
static void entry__check_arguments_230(void);
static FRAME_INFO frame__check_arguments_230 = {12, {"idx", "template", "arguments", "too_few_arguments_error", "results", "last_idx", "break", "option", "name", "default_value", "conversion", "help"}};
static void cont__check_arguments_231(void);
static void cont__check_arguments_232(void);
static NODE *func__check_arguments_233;
static void entry__check_arguments_233(void);
static FRAME_INFO frame__check_arguments_233 = {1, {"option"}};
static void cont__check_arguments_234(void);
static void cont__check_arguments_235(void);
static NODE *func__check_arguments_236;
static void entry__check_arguments_236(void);
static FRAME_INFO frame__check_arguments_236 = {5, {"arguments", "too_few_arguments_error", "results", "idx", "last_idx"}};
static void cont__check_arguments_237(void);
static void cont__check_arguments_238(void);
static void cont__check_arguments_239(void);
static void cont__check_arguments_240(void);
static void cont__check_arguments_241(void);
static void cont__check_arguments_242(void);
static NODE *func__check_arguments_243;
static void entry__check_arguments_243(void);
static FRAME_INFO frame__check_arguments_243 = {1, {"break"}};
static void cont__check_arguments_244(void);
static void cont__check_arguments_245(void);
static NODE *func__check_arguments_246;
static void entry__check_arguments_246(void);
static FRAME_INFO frame__check_arguments_246 = {10, {"idx", "template", "arguments", "too_few_arguments_error", "results", "option", "name", "default_value", "conversion", "help"}};
static void cont__check_arguments_247(void);
static void cont__check_arguments_248(void);
static NODE *func__check_arguments_249;
static void entry__check_arguments_249(void);
static FRAME_INFO frame__check_arguments_249 = {1, {"option"}};
static void cont__check_arguments_250(void);
static void cont__check_arguments_251(void);
static NODE *func__check_arguments_252;
static void entry__check_arguments_252(void);
static FRAME_INFO frame__check_arguments_252 = {4, {"arguments", "too_few_arguments_error", "results", "idx"}};
static void cont__check_arguments_253(void);
static void cont__check_arguments_254(void);
static void cont__check_arguments_255(void);
static void cont__check_arguments_256(void);
static void cont__check_arguments_257(void);
static NODE *func__check_arguments_258;
static void entry__check_arguments_258(void);
static FRAME_INFO frame__check_arguments_258 = {3, {"arguments", "results", "idx"}};
static void cont__check_arguments_259(void);
static void cont__check_arguments_260(void);
static NODE *func__check_arguments_261;
static void entry__check_arguments_261(void);
static FRAME_INFO frame__check_arguments_261 = {3, {"arguments", "results", "idx"}};
static void cont__check_arguments_262(void);
static void cont__check_arguments_263(void);
static NODE *func__check_arguments_264;
static void entry__check_arguments_264(void);
static FRAME_INFO frame__check_arguments_264 = {3, {"results", "idx", "arguments"}};
static void cont__check_arguments_265(void);
static NODE *func__check_arguments_266;
static void entry__check_arguments_266(void);
static FRAME_INFO frame__check_arguments_266 = {4, {"arguments", "too_few_arguments_error", "results", "idx"}};
static void cont__check_arguments_267(void);
static void cont__check_arguments_268(void);
static void cont__check_arguments_269(void);
static void cont__check_arguments_270(void);
static void cont__check_arguments_271(void);
static void cont__check_arguments_272(void);
static void cont__check_arguments_273(void);
static NODE *func__check_arguments_274;
static void entry__check_arguments_274(void);
static FRAME_INFO frame__check_arguments_274 = {8, {"idx", "result", "default_values", "results", "possible_values", "names", "show_usage", "conversions"}};
static void cont__check_arguments_275(void);
static NODE *func__check_arguments_276;
static void entry__check_arguments_276(void);
static FRAME_INFO frame__check_arguments_276 = {2, {"default_values", "idx"}};
static void cont__check_arguments_277(void);
static void cont__check_arguments_278(void);
static void cont__check_arguments_279(void);
static NODE *func__check_arguments_280;
static void entry__check_arguments_280(void);
static FRAME_INFO frame__check_arguments_280 = {3, {"results", "idx", "default_values"}};
static void cont__check_arguments_281(void);
static void cont__check_arguments_282(void);
static NODE *func__check_arguments_283;
static void entry__check_arguments_283(void);
static FRAME_INFO frame__check_arguments_283 = {10, {"possible_values", "idx", "names", "show_usage", "result", "conversions", "results", "possible_value", "check", "conversion"}};
static NODE *func__check_arguments_284;
static void entry__check_arguments_284(void);
static FRAME_INFO frame__check_arguments_284 = {5, {"value", "possible_value", "names", "idx", "show_usage"}};
static void cont__check_arguments_285(void);
static NODE *func__check_arguments_286;
static void entry__check_arguments_286(void);
static FRAME_INFO frame__check_arguments_286 = {3, {"names", "idx", "show_usage"}};
static void cont__check_arguments_287(void);
static void cont__check_arguments_288(void);
static NODE *string__143aedf103648031;
static NODE *string__2d7981f4e6002bcf;
static void cont__check_arguments_291(void);
static void cont__check_arguments_292(void);
static void cont__check_arguments_293(void);
static void cont__check_arguments_294(void);
static void cont__check_arguments_295(void);
static NODE *func__check_arguments_296;
static void entry__check_arguments_296(void);
static FRAME_INFO frame__check_arguments_296 = {2, {"result", "check"}};
static void cont__check_arguments_297(void);
static NODE *func__check_arguments_298;
static void entry__check_arguments_298(void);
static FRAME_INFO frame__check_arguments_298 = {2, {"result", "check"}};
static NODE *func__check_arguments_299;
static void entry__check_arguments_299(void);
static FRAME_INFO frame__check_arguments_299 = {2, {"item", "check"}};
static NODE *func__check_arguments_300;
static void entry__check_arguments_300(void);
static FRAME_INFO frame__check_arguments_300 = {2, {"check", "result"}};
static void cont__check_arguments_301(void);
static void cont__check_arguments_302(void);
static void cont__check_arguments_303(void);
static NODE *func__check_arguments_304;
static void entry__check_arguments_304(void);
static FRAME_INFO frame__check_arguments_304 = {4, {"result", "conversion", "results", "idx"}};
static void cont__check_arguments_305(void);
static NODE *func__check_arguments_306;
static void entry__check_arguments_306(void);
static FRAME_INFO frame__check_arguments_306 = {5, {"result", "conversion", "results", "idx", "new_result"}};
static NODE *func__check_arguments_307;
static void entry__check_arguments_307(void);
static FRAME_INFO frame__check_arguments_307 = {3, {"item", "new_result", "conversion"}};
static void cont__check_arguments_308(void);
static void cont__check_arguments_309(void);
static void cont__check_arguments_310(void);
static void cont__check_arguments_311(void);
static NODE *func__check_arguments_312;
static void entry__check_arguments_312(void);
static FRAME_INFO frame__check_arguments_312 = {4, {"results", "idx", "conversion", "result"}};
static void cont__check_arguments_313(void);
static void cont__check_arguments_314(void);
static void cont__check_arguments_315(void);
static NODE *func__std__program_commands_1;
static void entry__std__program_commands_1(void);
static FRAME_INFO frame__std__program_commands_1 = {2, {"commands", "command_ids"}};
static NODE *func__std__program_commands_2;
static void entry__std__program_commands_2(void);
static FRAME_INFO frame__std__program_commands_2 = {4, {"command", "command_ids", "name", "description"}};
static void cont__std__program_commands_3(void);
static void cont__std__program_commands_4(void);
static void cont__std__program_commands_5(void);
static void cont__std__program_commands_6(void);
static void cont__std__program_commands_7(void);
static void cont__std__program_commands_8(void);
static void cont__std__program_commands_9(void);
static NODE *get__std__program_commands(void) {
  return var.std__program_commands;
}
static NODE *func__std__command_parameters_1;
static void entry__std__command_parameters_1(void);
static FRAME_INFO frame__std__command_parameters_1 = {2, {"id", "templates"}};
static void cont__std__command_parameters_2(void);
static NODE *func__std__command_parameters_3;
static void entry__std__command_parameters_3(void);
static FRAME_INFO frame__std__command_parameters_3 = {1, {"templates"}};
static void cont__std__command_parameters_4(void);
static void cont__std__command_parameters_5(void);
static void cont__std__command_parameters_6(void);
static NODE *func__std__command_parameters_7;
static void entry__std__command_parameters_7(void);
static FRAME_INFO frame__std__command_parameters_7 = {3, {"id", "templates", "command"}};
static void cont__std__command_parameters_8(void);
static void cont__std__command_parameters_9(void);
static NODE *func__std__command_parameters_10;
static void entry__std__command_parameters_10(void);
static FRAME_INFO frame__std__command_parameters_10 = {3, {"command", "id", "templates"}};
static NODE *string__120ae80b5d007d49;
static void cont__std__command_parameters_12(void);
static NODE *func__std__command_parameters_13;
static void entry__std__command_parameters_13(void);
static FRAME_INFO frame__std__command_parameters_13 = {1, {"id"}};
static void cont__std__command_parameters_14(void);
static void cont__std__command_parameters_15(void);
static NODE *func__std__command_parameters_16;
static void entry__std__command_parameters_16(void);
static FRAME_INFO frame__std__command_parameters_16 = {1, {"id"}};
static void cont__std__command_parameters_17(void);
static void cont__std__command_parameters_18(void);
static void cont__std__command_parameters_19(void);
static void cont__std__command_parameters_20(void);
static void cont__std__command_parameters_21(void);
static void cont__std__command_parameters_22(void);
static NODE *func__std__command_parameters_23;
static void entry__std__command_parameters_23(void);
static FRAME_INFO frame__std__command_parameters_23 = {2, {"id", "templates"}};
static void cont__std__command_parameters_24(void);
static void cont__std__command_parameters_25(void);
static NODE *func__std__command_parameters_26;
static void entry__std__command_parameters_26(void);
static FRAME_INFO frame__std__command_parameters_26 = {3, {"command", "id", "templates"}};
static void cont__std__command_parameters_27(void);
static void cont__std__command_parameters_28(void);
static NODE *func__std__command_parameters_29;
static void entry__std__command_parameters_29(void);
static FRAME_INFO frame__std__command_parameters_29 = {3, {"id", "command", "templates"}};
static void cont__std__command_parameters_30(void);
static void cont__std__command_parameters_31(void);
static NODE *func__std__command_parameters_32;
static void entry__std__command_parameters_32(void);
static FRAME_INFO frame__std__command_parameters_32 = {1, {"templates"}};
static NODE *func__std__command_parameters_33;
static void entry__std__command_parameters_33(void);
static FRAME_INFO frame__std__command_parameters_33 = {1, {"templates"}};
static void cont__std__command_parameters_34(void);
static void cont__std__command_parameters_35(void);
static void cont__std__command_parameters_36(void);
static NODE *get__std__command_parameters(void) {
  return var.std__command_parameters;
}
static NODE *func__show_commands_1;
static void entry__show_commands_1(void);
static FRAME_INFO frame__show_commands_1 = {1, {"tab"}};
static void cont__show_commands_2(void);
static NODE *func__show_commands_3;
static void entry__show_commands_3(void);
static FRAME_INFO frame__show_commands_3 = {0, {}};
static void cont__show_commands_4(void);
static void cont__show_commands_5(void);
static void cont__show_commands_6(void);
static NODE *string__c69810bce846f05a;
static void cont__show_commands_8(void);
static NODE *string__e65a119686ab55e3;
static void cont__show_commands_10(void);
static void cont__show_commands_11(void);
static NODE *func__show_commands_12;
static void entry__show_commands_12(void);
static FRAME_INFO frame__show_commands_12 = {3, {"idx", "command_name", "tab"}};
static void cont__show_commands_13(void);
static void cont__show_commands_14(void);
static void cont__show_commands_15(void);
static void cont__show_commands_16(void);
static void cont__show_commands_17(void);
static NODE *func__show_commands_18;
static void entry__show_commands_18(void);
static FRAME_INFO frame__show_commands_18 = {1, {"tab"}};
static NODE *string__7cf0276001425531;
static NODE *string__d9b4d5146ecce23;
static void cont__show_commands_21(void);
static void cont__show_commands_22(void);
static void cont__show_commands_23(void);
static void cont__show_commands_24(void);
static NODE *func__show_commands_25;
static void entry__show_commands_25(void);
static FRAME_INFO frame__show_commands_25 = {1, {"tab"}};
static NODE *string__945c0f9015c3e094;
static NODE *string__460a51cfecd67225;
static void cont__show_commands_28(void);
static void cont__show_commands_29(void);
static void cont__show_commands_30(void);
static NODE *func__std__program_parameters_1;
static void entry__std__program_parameters_1(void);
static FRAME_INFO frame__std__program_parameters_1 = {1, {"templates"}};
static void cont__std__program_parameters_2(void);
static NODE *func__std__program_parameters_3;
static void entry__std__program_parameters_3(void);
static FRAME_INFO frame__std__program_parameters_3 = {1, {"templates"}};
static NODE *func__std__program_parameters_4;
static void entry__std__program_parameters_4(void);
static FRAME_INFO frame__std__program_parameters_4 = {0, {}};
static void cont__std__program_parameters_5(void);
static NODE *func__std__program_parameters_6;
static void entry__std__program_parameters_6(void);
static FRAME_INFO frame__std__program_parameters_6 = {0, {}};
static NODE *func__std__program_parameters_7;
static void entry__std__program_parameters_7(void);
static FRAME_INFO frame__std__program_parameters_7 = {0, {}};
static void cont__std__program_parameters_8(void);
static NODE *func__std__program_parameters_9;
static void entry__std__program_parameters_9(void);
static FRAME_INFO frame__std__program_parameters_9 = {0, {}};
static NODE *string__9e1d476192d899b4;
static void cont__std__program_parameters_11(void);
static void cont__std__program_parameters_12(void);
static NODE *func__std__program_parameters_13;
static void entry__std__program_parameters_13(void);
static FRAME_INFO frame__std__program_parameters_13 = {0, {}};
static void cont__std__program_parameters_14(void);
static NODE *func__std__program_parameters_15;
static void entry__std__program_parameters_15(void);
static FRAME_INFO frame__std__program_parameters_15 = {0, {}};
static void cont__std__program_parameters_16(void);
static NODE *func__std__program_parameters_17;
static void entry__std__program_parameters_17(void);
static FRAME_INFO frame__std__program_parameters_17 = {0, {}};
static void cont__std__program_parameters_18(void);
static NODE *func__std__program_parameters_19;
static void entry__std__program_parameters_19(void);
static FRAME_INFO frame__std__program_parameters_19 = {0, {}};
static void cont__std__program_parameters_20(void);
static NODE *func__std__program_parameters_21;
static void entry__std__program_parameters_21(void);
static FRAME_INFO frame__std__program_parameters_21 = {0, {}};
static void cont__std__program_parameters_22(void);
static NODE *func__std__program_parameters_23;
static void entry__std__program_parameters_23(void);
static FRAME_INFO frame__std__program_parameters_23 = {0, {}};
static void cont__std__program_parameters_24(void);
static NODE *func__std__program_parameters_25;
static void entry__std__program_parameters_25(void);
static FRAME_INFO frame__std__program_parameters_25 = {0, {}};
static void cont__std__program_parameters_26(void);
static NODE *func__std__program_parameters_27;
static void entry__std__program_parameters_27(void);
static FRAME_INFO frame__std__program_parameters_27 = {0, {}};
static NODE *string__1dc76095d723d587;
static void cont__std__program_parameters_29(void);
static NODE *func__std__program_parameters_30;
static void entry__std__program_parameters_30(void);
static FRAME_INFO frame__std__program_parameters_30 = {0, {}};
static NODE *string__a15bc662b3bb7e39;
static void cont__std__program_parameters_32(void);
static NODE *func__std__program_parameters_33;
static void entry__std__program_parameters_33(void);
static FRAME_INFO frame__std__program_parameters_33 = {0, {}};
static void cont__std__program_parameters_34(void);
static NODE *func__std__program_parameters_35;
static void entry__std__program_parameters_35(void);
static FRAME_INFO frame__std__program_parameters_35 = {0, {}};
static NODE *string__617a0ed7343fbf40;
static void cont__std__program_parameters_37(void);
static void cont__std__program_parameters_38(void);
static NODE *string__19bd6394b9c09d4b;
static void cont__std__program_parameters_40(void);
static void cont__std__program_parameters_41(void);
static NODE *func__std__program_parameters_42;
static void entry__std__program_parameters_42(void);
static FRAME_INFO frame__std__program_parameters_42 = {0, {}};
static void cont__std__program_parameters_43(void);
static void cont__std__program_parameters_44(void);
static NODE *func__std__program_parameters_45;
static void entry__std__program_parameters_45(void);
static FRAME_INFO frame__std__program_parameters_45 = {0, {}};
static void cont__std__program_parameters_46(void);
static NODE *func__std__program_parameters_47;
static void entry__std__program_parameters_47(void);
static FRAME_INFO frame__std__program_parameters_47 = {1, {"command_name"}};
static void cont__std__program_parameters_48(void);
static void cont__std__program_parameters_49(void);
static void cont__std__program_parameters_50(void);
static void cont__std__program_parameters_51(void);
static NODE *string__f68d8519ec4e03eb;
static void cont__std__program_parameters_53(void);
static void cont__std__program_parameters_54(void);
static NODE *get__std__program_parameters(void) {
  return var.std__program_parameters;
}
void run__basic__parameters(void);

static CONTINUATION_INFO continuation_info[] = {
  {run__basic__parameters, NULL, 215, 215, 1, 33},
  {entry__std__copyright_1, NULL, 74, 74, 24, 24},
  {entry__std__version_1, NULL, 82, 82, 21, 21},
  {entry__std__extract_options_5, NULL, 119, 119, 11, 18},
  {cont__std__extract_options_6, &frame__std__extract_options_5, 119, 119, 18, 18},
  {entry__std__extract_options_7, NULL, 121, 121, 11, 33},
  {cont__std__extract_options_8, &frame__std__extract_options_7, 122, 122, 11, 32},
  {cont__std__extract_options_9, &frame__std__extract_options_7, 122, 122, 32, 32},
  {entry__std__extract_options_3, NULL, 118, 118, 9, 34},
  {cont__std__extract_options_4, &frame__std__extract_options_3, 117, 122, 7, 33},
  {entry__std__extract_options_2, NULL, 116, 122, 5, 34},
  {entry__std__extract_options_19, NULL, 132, 132, 15, 36},
  {cont__std__extract_options_20, &frame__std__extract_options_19, 133, 133, 28, 43},
  {cont__std__extract_options_21, &frame__std__extract_options_19, 133, 133, 15, 43},
  {cont__std__extract_options_22, &frame__std__extract_options_19, 133, 133, 43, 43},
  {entry__std__extract_options_23, NULL, 135, 135, 15, 22},
  {cont__std__extract_options_24, &frame__std__extract_options_23, 135, 135, 22, 22},
  {entry__std__extract_options_15, NULL, 131, 131, 13, 26},
  {cont__std__extract_options_16, &frame__std__extract_options_15, 131, 131, 31, 46},
  {cont__std__extract_options_17, &frame__std__extract_options_15, 131, 131, 13, 46},
  {cont__std__extract_options_18, &frame__std__extract_options_15, 130, 135, 11, 23},
  {entry__std__extract_options_14, NULL, 129, 135, 9, 24},
  {entry__std__extract_options_30, NULL, 140, 140, 15, 36},
  {cont__std__extract_options_31, &frame__std__extract_options_30, 141, 141, 15, 38},
  {cont__std__extract_options_32, &frame__std__extract_options_30, 141, 141, 38, 38},
  {entry__std__extract_options_33, NULL, 143, 143, 15, 22},
  {cont__std__extract_options_34, &frame__std__extract_options_33, 143, 143, 22, 22},
  {entry__std__extract_options_26, NULL, 139, 139, 13, 26},
  {cont__std__extract_options_27, &frame__std__extract_options_26, 139, 139, 31, 46},
  {cont__std__extract_options_28, &frame__std__extract_options_26, 139, 139, 13, 46},
  {cont__std__extract_options_29, &frame__std__extract_options_26, 138, 143, 11, 23},
  {entry__std__extract_options_25, NULL, 137, 143, 9, 24},
  {entry__std__extract_options_11, NULL, 124, 124, 5, 31},
  {cont__std__extract_options_12, &frame__std__extract_options_11, 127, 127, 7, 31},
  {cont__std__extract_options_13, &frame__std__extract_options_11, 126, 143, 5, 26},
  {cont__std__extract_options_35, &frame__std__extract_options_11, 144, 144, 5, 24},
  {cont__std__extract_options_36, &frame__std__extract_options_11, 144, 144, 24, 24},
  {entry__std__extract_options_39, NULL, 146, 146, 55, 64},
  {cont__std__extract_options_40, &frame__std__extract_options_39, 146, 146, 48, 65},
  {cont__std__extract_options_41, &frame__std__extract_options_39, 146, 146, 35, 66},
  {cont__std__extract_options_42, &frame__std__extract_options_39, 146, 146, 71, 71},
  {cont__std__extract_options_43, &frame__std__extract_options_39, 146, 146, 29, 72},
  {cont__std__extract_options_44, &frame__std__extract_options_39, 146, 146, 11, 75},
  {cont__std__extract_options_47, &frame__std__extract_options_39, 146, 146, 5, 75},
  {entry__std__extract_options_1, NULL, 114, 122, 3, 35},
  {cont__std__extract_options_10, &frame__std__extract_options_1, 123, 144, 3, 24},
  {cont__std__extract_options_37, &frame__std__extract_options_1, 145, 145, 10, 25},
  {cont__std__extract_options_38, &frame__std__extract_options_1, 145, 146, 3, 75},
  {cont__std__extract_options_48, &frame__std__extract_options_1, 147, 147, 3, 25},
  {entry__std__extract_some_options_10, NULL, 187, 187, 15, 36},
  {cont__std__extract_some_options_11, &frame__std__extract_some_options_10, 188, 188, 28, 43},
  {cont__std__extract_some_options_12, &frame__std__extract_some_options_10, 188, 188, 15, 43},
  {cont__std__extract_some_options_13, &frame__std__extract_some_options_10, 188, 188, 43, 43},
  {entry__std__extract_some_options_14, NULL, 190, 190, 15, 22},
  {cont__std__extract_some_options_15, &frame__std__extract_some_options_14, 190, 190, 22, 22},
  {entry__std__extract_some_options_6, NULL, 186, 186, 13, 26},
  {cont__std__extract_some_options_7, &frame__std__extract_some_options_6, 186, 186, 31, 46},
  {cont__std__extract_some_options_8, &frame__std__extract_some_options_6, 186, 186, 13, 46},
  {cont__std__extract_some_options_9, &frame__std__extract_some_options_6, 185, 190, 11, 23},
  {entry__std__extract_some_options_5, NULL, 184, 190, 9, 24},
  {entry__std__extract_some_options_19, NULL, 194, 194, 43, 56},
  {cont__std__extract_some_options_20, &frame__std__extract_some_options_19, 194, 194, 61, 76},
  {cont__std__extract_some_options_21, &frame__std__extract_some_options_19, 194, 194, 43, 76},
  {cont__std__extract_some_options_22, &frame__std__extract_some_options_19, 194, 194, 43, 76},
  {entry__std__extract_some_options_24, NULL, 195, 195, 15, 36},
  {cont__std__extract_some_options_25, &frame__std__extract_some_options_24, 196, 196, 15, 38},
  {cont__std__extract_some_options_26, &frame__std__extract_some_options_24, 196, 196, 38, 38},
  {entry__std__extract_some_options_27, NULL, 198, 198, 15, 22},
  {cont__std__extract_some_options_28, &frame__std__extract_some_options_27, 198, 198, 22, 22},
  {entry__std__extract_some_options_17, NULL, 194, 194, 13, 38},
  {cont__std__extract_some_options_18, &frame__std__extract_some_options_17, 194, 194, 13, 76},
  {cont__std__extract_some_options_23, &frame__std__extract_some_options_17, 193, 198, 11, 23},
  {entry__std__extract_some_options_16, NULL, 192, 198, 9, 24},
  {entry__std__extract_some_options_2, NULL, 179, 179, 5, 31},
  {cont__std__extract_some_options_3, &frame__std__extract_some_options_2, 182, 182, 7, 31},
  {cont__std__extract_some_options_4, &frame__std__extract_some_options_2, 181, 198, 5, 26},
  {cont__std__extract_some_options_29, &frame__std__extract_some_options_2, 199, 199, 5, 24},
  {cont__std__extract_some_options_30, &frame__std__extract_some_options_2, 199, 199, 24, 24},
  {entry__std__extract_some_options_1, NULL, 178, 199, 3, 24},
  {cont__std__extract_some_options_31, &frame__std__extract_some_options_1, 200, 200, 3, 13},
  {entry__display_table_2, NULL, 204, 204, 65, 72},
  {cont__display_table_3, &frame__display_table_2, 204, 204, 55, 73},
  {cont__display_table_4, &frame__display_table_2, 204, 204, 25, 73},
  {cont__display_table_5, &frame__display_table_2, 204, 204, 73, 73},
  {entry__display_table_17, NULL, 209, 209, 37, 56},
  {cont__display_table_18, &frame__display_table_17, 209, 209, 27, 56},
  {cont__display_table_20, &frame__display_table_17, 209, 209, 20, 56},
  {entry__display_table_14, NULL, 209, 209, 10, 17},
  {cont__display_table_15, &frame__display_table_14, 209, 209, 10, 17},
  {cont__display_table_16, &frame__display_table_14, 209, 209, 7, 56},
  {cont__display_table_21, &frame__display_table_14, 210, 210, 7, 19},
  {entry__display_table_8, NULL, 207, 207, 27, 34},
  {cont__display_table_9, &frame__display_table_8, 207, 207, 17, 54},
  {cont__display_table_10, &frame__display_table_8, 207, 207, 5, 54},
  {cont__display_table_12, &frame__display_table_8, 208, 208, 19, 26},
  {cont__display_table_13, &frame__display_table_8, 208, 210, 5, 19},
  {entry__display_table_1, NULL, 204, 204, 3, 73},
  {cont__display_table_6, &frame__display_table_1, 205, 205, 3, 28},
  {cont__display_table_7, &frame__display_table_1, 206, 210, 3, 20},
  {entry__show_version_1, NULL, 218, 218, 10, 53},
  {cont__show_version_3, &frame__show_version_1, 218, 218, 3, 53},
  {entry__show_copyright_1, NULL, 220, 220, 18, 41},
  {entry__check_arguments_9, NULL, 240, 240, 40, 70},
  {cont__check_arguments_10, &frame__check_arguments_9, 240, 240, 70, 70},
  {entry__check_arguments_6, NULL, 239, 239, 7, 37},
  {cont__check_arguments_8, &frame__check_arguments_6, 240, 240, 7, 70},
  {cont__check_arguments_11, &frame__check_arguments_6, 241, 241, 17, 17},
  {cont__check_arguments_12, &frame__check_arguments_6, 241, 241, 7, 18},
  {cont__check_arguments_13, &frame__check_arguments_6, 241, 241, 25, 25},
  {entry__check_arguments_17, NULL, 244, 244, 17, 17},
  {cont__check_arguments_18, &frame__check_arguments_17, 244, 244, 7, 18},
  {cont__check_arguments_19, &frame__check_arguments_17, 245, 245, 23, 57},
  {cont__check_arguments_22, &frame__check_arguments_17, 245, 245, 7, 57},
  {cont__check_arguments_23, &frame__check_arguments_17, 245, 245, 57, 57},
  {entry__check_arguments_2, NULL, 236, 236, 5, 32},
  {cont__check_arguments_3, &frame__check_arguments_2, 237, 237, 5, 40},
  {cont__check_arguments_4, &frame__check_arguments_2, 238, 238, 8, 32},
  {cont__check_arguments_5, &frame__check_arguments_2, 238, 241, 5, 25},
  {cont__check_arguments_14, &frame__check_arguments_2, 242, 242, 5, 38},
  {cont__check_arguments_15, &frame__check_arguments_2, 243, 243, 8, 31},
  {cont__check_arguments_16, &frame__check_arguments_2, 243, 245, 5, 57},
  {cont__check_arguments_24, &frame__check_arguments_2, 246, 246, 5, 14},
  {entry__check_arguments_29, NULL, 253, 253, 11, 23},
  {cont__check_arguments_30, &frame__check_arguments_29, 253, 253, 23, 23},
  {entry__check_arguments_31, NULL, 255, 255, 11, 23},
  {cont__check_arguments_32, &frame__check_arguments_31, 255, 255, 23, 23},
  {entry__check_arguments_33, NULL, 257, 257, 11, 23},
  {cont__check_arguments_34, &frame__check_arguments_33, 257, 257, 23, 23},
  {entry__check_arguments_26, NULL, 250, 250, 7, 35},
  {cont__check_arguments_27, &frame__check_arguments_26, 251, 251, 12, 21},
  {cont__check_arguments_28, &frame__check_arguments_26, 251, 257, 7, 24},
  {cont__check_arguments_35, &frame__check_arguments_26, 258, 258, 7, 12},
  {entry__check_arguments_37, NULL, 260, 260, 36, 60},
  {entry__check_arguments_40, NULL, 262, 262, 7, 39},
  {cont__check_arguments_41, &frame__check_arguments_40, 263, 263, 27, 58},
  {cont__check_arguments_42, &frame__check_arguments_40, 263, 263, 16, 59},
  {cont__check_arguments_43, &frame__check_arguments_40, 263, 263, 7, 59},
  {entry__check_arguments_50, NULL, 266, 266, 40, 80},
  {entry__check_arguments_48, NULL, 266, 266, 10, 37},
  {cont__check_arguments_49, &frame__check_arguments_48, 266, 266, 7, 80},
  {cont__check_arguments_52, &frame__check_arguments_48, 267, 267, 7, 42},
  {entry__check_arguments_56, NULL, 273, 273, 12, 30},
  {cont__check_arguments_57, &frame__check_arguments_56, 273, 273, 9, 30},
  {entry__check_arguments_58, NULL, 274, 274, 9, 13},
  {entry__check_arguments_61, NULL, 276, 276, 18, 46},
  {cont__check_arguments_62, &frame__check_arguments_61, 276, 276, 7, 46},
  {entry__check_arguments_68, NULL, 284, 284, 24, 52},
  {cont__check_arguments_69, &frame__check_arguments_68, 284, 284, 54, 70},
  {cont__check_arguments_70, &frame__check_arguments_68, 284, 284, 19, 71},
  {cont__check_arguments_71, &frame__check_arguments_68, 284, 284, 9, 71},
  {cont__check_arguments_72, &frame__check_arguments_68, 284, 284, 71, 71},
  {entry__check_arguments_67, NULL, 283, 284, 7, 71},
  {cont__check_arguments_73, &frame__check_arguments_67, 285, 285, 7, 23},
  {entry__check_arguments_85, NULL, 297, 297, 17, 36},
  {cont__check_arguments_87, &frame__check_arguments_85, 297, 297, 36, 36},
  {entry__check_arguments_88, NULL, 299, 299, 17, 37},
  {cont__check_arguments_90, &frame__check_arguments_88, 299, 299, 37, 37},
  {entry__check_arguments_81, NULL, 294, 294, 13, 37},
  {cont__check_arguments_83, &frame__check_arguments_81, 295, 295, 18, 27},
  {cont__check_arguments_84, &frame__check_arguments_81, 295, 299, 13, 38},
  {cont__check_arguments_91, &frame__check_arguments_81, 300, 300, 13, 18},
  {entry__check_arguments_80, NULL, 302, 302, 26, 38},
  {cont__check_arguments_92, &frame__check_arguments_80, 302, 302, 40, 57},
  {cont__check_arguments_93, &frame__check_arguments_80, 302, 302, 21, 58},
  {cont__check_arguments_94, &frame__check_arguments_80, 302, 302, 11, 58},
  {cont__check_arguments_95, &frame__check_arguments_80, 302, 302, 58, 58},
  {entry__check_arguments_79, NULL, 292, 302, 9, 58},
  {cont__check_arguments_96, &frame__check_arguments_79, 303, 303, 9, 25},
  {entry__check_arguments_76, NULL, 287, 289, 7, 16},
  {cont__check_arguments_78, &frame__check_arguments_76, 290, 303, 7, 25},
  {entry__check_arguments_25, NULL, 260, 260, 8, 33},
  {cont__check_arguments_36, &frame__check_arguments_25, 260, 260, 5, 60},
  {cont__check_arguments_38, &frame__check_arguments_25, 261, 261, 8, 28},
  {cont__check_arguments_39, &frame__check_arguments_25, 261, 263, 5, 59},
  {cont__check_arguments_44, &frame__check_arguments_25, 264, 264, 5, 21},
  {cont__check_arguments_46, &frame__check_arguments_25, 265, 265, 12, 29},
  {cont__check_arguments_47, &frame__check_arguments_25, 265, 267, 5, 42},
  {cont__check_arguments_54, &frame__check_arguments_25, 272, 272, 9, 26},
  {cont__check_arguments_55, &frame__check_arguments_25, 273, 273, 9, 30},
  {cont__check_arguments_59, &frame__check_arguments_25, 268, 274, 5, 14},
  {cont__check_arguments_60, &frame__check_arguments_25, 275, 276, 5, 46},
  {cont__check_arguments_63, &frame__check_arguments_25, 277, 277, 5, 12},
  {cont__check_arguments_64, &frame__check_arguments_25, 278, 280, 5, 17},
  {cont__check_arguments_66, &frame__check_arguments_25, 281, 285, 5, 23},
  {cont__check_arguments_74, &frame__check_arguments_25, 286, 286, 12, 27},
  {cont__check_arguments_75, &frame__check_arguments_25, 286, 303, 5, 26},
  {entry__check_arguments_99, NULL, 308, 309, 18, 51},
  {cont__check_arguments_102, &frame__check_arguments_99, 308, 309, 9, 51},
  {entry__check_arguments_103, NULL, 311, 312, 9, 28},
  {entry__check_arguments_97, NULL, 307, 307, 7, 24},
  {cont__check_arguments_98, &frame__check_arguments_97, 306, 312, 5, 30},
  {cont__check_arguments_105, &frame__check_arguments_97, 313, 313, 5, 14},
  {cont__check_arguments_106, &frame__check_arguments_97, 314, 314, 5, 10},
  {entry__check_arguments_107, NULL, 317, 318, 5, 25},
  {cont__check_arguments_109, &frame__check_arguments_107, 319, 319, 5, 14},
  {cont__check_arguments_110, &frame__check_arguments_107, 320, 320, 5, 10},
  {entry__check_arguments_117, NULL, 326, 326, 31, 46},
  {cont__check_arguments_118, &frame__check_arguments_117, 326, 326, 9, 46},
  {cont__check_arguments_119, &frame__check_arguments_117, 327, 327, 9, 30},
  {cont__check_arguments_120, &frame__check_arguments_117, 327, 327, 30, 30},
  {entry__check_arguments_121, NULL, 329, 329, 9, 39},
  {cont__check_arguments_122, &frame__check_arguments_121, 329, 329, 39, 39},
  {entry__check_arguments_125, NULL, 334, 334, 9, 15},
  {entry__check_arguments_126, NULL, 335, 335, 9, 17},
  {entry__check_arguments_135, NULL, 342, 342, 9, 27},
  {cont__check_arguments_136, &frame__check_arguments_135, 343, 343, 9, 24},
  {cont__check_arguments_137, &frame__check_arguments_135, 344, 344, 9, 19},
  {cont__check_arguments_138, &frame__check_arguments_135, 344, 344, 34, 34},
  {entry__check_arguments_133, NULL, 341, 341, 10, 27},
  {cont__check_arguments_134, &frame__check_arguments_133, 341, 344, 7, 34},
  {entry__check_arguments_141, NULL, 346, 346, 9, 31},
  {cont__check_arguments_142, &frame__check_arguments_141, 347, 347, 9, 22},
  {cont__check_arguments_143, &frame__check_arguments_141, 347, 347, 26, 26},
  {entry__check_arguments_139, NULL, 345, 345, 10, 32},
  {cont__check_arguments_140, &frame__check_arguments_139, 345, 347, 7, 26},
  {entry__check_arguments_146, NULL, 349, 349, 9, 32},
  {cont__check_arguments_147, &frame__check_arguments_146, 350, 350, 9, 22},
  {cont__check_arguments_148, &frame__check_arguments_146, 350, 350, 26, 26},
  {entry__check_arguments_144, NULL, 348, 348, 10, 38},
  {cont__check_arguments_145, &frame__check_arguments_144, 348, 350, 7, 26},
  {entry__check_arguments_151, NULL, 351, 351, 39, 63},
  {cont__check_arguments_152, &frame__check_arguments_151, 351, 351, 39, 63},
  {entry__check_arguments_154, NULL, 352, 352, 9, 32},
  {cont__check_arguments_155, &frame__check_arguments_154, 353, 353, 9, 25},
  {cont__check_arguments_156, &frame__check_arguments_154, 353, 353, 29, 29},
  {entry__check_arguments_149, NULL, 351, 351, 10, 34},
  {cont__check_arguments_150, &frame__check_arguments_149, 351, 351, 10, 63},
  {cont__check_arguments_153, &frame__check_arguments_149, 351, 353, 7, 29},
  {entry__check_arguments_157, NULL, 355, 355, 9, 31},
  {cont__check_arguments_158, &frame__check_arguments_157, 356, 356, 9, 25},
  {cont__check_arguments_159, &frame__check_arguments_157, 356, 356, 29, 29},
  {entry__check_arguments_114, NULL, 323, 323, 5, 63},
  {cont__check_arguments_115, &frame__check_arguments_114, 325, 325, 7, 32},
  {cont__check_arguments_116, &frame__check_arguments_114, 324, 329, 5, 40},
  {cont__check_arguments_123, &frame__check_arguments_114, 333, 333, 9, 23},
  {cont__check_arguments_124, &frame__check_arguments_114, 335, 335, 9, 17},
  {cont__check_arguments_127, &frame__check_arguments_114, 330, 335, 5, 18},
  {cont__check_arguments_128, &frame__check_arguments_114, 336, 336, 5, 22},
  {cont__check_arguments_129, &frame__check_arguments_114, 337, 337, 5, 38},
  {cont__check_arguments_130, &frame__check_arguments_114, 338, 338, 5, 32},
  {cont__check_arguments_131, &frame__check_arguments_114, 339, 339, 5, 28},
  {cont__check_arguments_132, &frame__check_arguments_114, 340, 356, 5, 30},
  {entry__check_arguments_168, NULL, 359, 359, 7, 16},
  {cont__check_arguments_169, &frame__check_arguments_168, 360, 360, 7, 15},
  {entry__check_arguments_172, NULL, 361, 361, 40, 51},
  {cont__check_arguments_173, &frame__check_arguments_172, 361, 361, 40, 68},
  {cont__check_arguments_175, &frame__check_arguments_172, 361, 361, 40, 68},
  {entry__check_arguments_177, NULL, 362, 362, 7, 20},
  {cont__check_arguments_178, &frame__check_arguments_177, 363, 363, 7, 15},
  {entry__check_arguments_181, NULL, 364, 364, 38, 49},
  {cont__check_arguments_182, &frame__check_arguments_181, 364, 364, 38, 64},
  {cont__check_arguments_184, &frame__check_arguments_181, 364, 364, 38, 64},
  {entry__check_arguments_186, NULL, 365, 365, 7, 31},
  {cont__check_arguments_187, &frame__check_arguments_186, 366, 366, 7, 15},
  {entry__check_arguments_164, NULL, 358, 358, 8, 19},
  {cont__check_arguments_165, &frame__check_arguments_164, 358, 358, 8, 31},
  {cont__check_arguments_167, &frame__check_arguments_164, 358, 360, 5, 15},
  {cont__check_arguments_170, &frame__check_arguments_164, 361, 361, 8, 35},
  {cont__check_arguments_171, &frame__check_arguments_164, 361, 361, 8, 68},
  {cont__check_arguments_176, &frame__check_arguments_164, 361, 363, 5, 15},
  {cont__check_arguments_179, &frame__check_arguments_164, 364, 364, 8, 33},
  {cont__check_arguments_180, &frame__check_arguments_164, 364, 364, 8, 64},
  {cont__check_arguments_185, &frame__check_arguments_164, 364, 366, 5, 15},
  {entry__check_arguments_193, NULL, 374, 374, 11, 34},
  {cont__check_arguments_194, &frame__check_arguments_193, 375, 375, 11, 15},
  {entry__check_arguments_199, NULL, 382, 382, 17, 36},
  {cont__check_arguments_200, &frame__check_arguments_199, 382, 382, 45, 45},
  {entry__check_arguments_201, NULL, 384, 384, 23, 41},
  {cont__check_arguments_202, &frame__check_arguments_201, 384, 384, 17, 50},
  {cont__check_arguments_203, &frame__check_arguments_201, 384, 384, 22, 41},
  {cont__check_arguments_204, &frame__check_arguments_201, 384, 384, 50, 50},
  {entry__check_arguments_196, NULL, 379, 379, 13, 36},
  {cont__check_arguments_197, &frame__check_arguments_196, 380, 380, 18, 34},
  {cont__check_arguments_198, &frame__check_arguments_196, 380, 384, 13, 51},
  {entry__check_arguments_212, NULL, 389, 389, 51, 80},
  {cont__check_arguments_214, &frame__check_arguments_212, 389, 389, 45, 80},
  {entry__check_arguments_218, NULL, 392, 392, 21, 40},
  {cont__check_arguments_219, &frame__check_arguments_218, 392, 392, 45, 45},
  {entry__check_arguments_220, NULL, 394, 394, 44, 44},
  {entry__check_arguments_207, NULL, 388, 388, 55, 55},
  {cont__check_arguments_208, &frame__check_arguments_207, 388, 388, 37, 56},
  {cont__check_arguments_209, &frame__check_arguments_207, 388, 388, 17, 57},
  {cont__check_arguments_210, &frame__check_arguments_207, 389, 389, 20, 42},
  {cont__check_arguments_211, &frame__check_arguments_207, 389, 389, 17, 80},
  {cont__check_arguments_215, &frame__check_arguments_207, 391, 391, 19, 35},
  {cont__check_arguments_216, &frame__check_arguments_207, 391, 391, 19, 53},
  {cont__check_arguments_217, &frame__check_arguments_207, 390, 394, 17, 45},
  {cont__check_arguments_221, &frame__check_arguments_207, 395, 395, 17, 40},
  {cont__check_arguments_222, &frame__check_arguments_207, 395, 395, 40, 40},
  {entry__check_arguments_223, NULL, 397, 397, 17, 24},
  {cont__check_arguments_224, &frame__check_arguments_223, 397, 397, 24, 24},
  {entry__check_arguments_205, NULL, 387, 387, 15, 40},
  {cont__check_arguments_206, &frame__check_arguments_205, 386, 397, 13, 25},
  {entry__check_arguments_191, NULL, 373, 373, 12, 27},
  {cont__check_arguments_192, &frame__check_arguments_191, 373, 375, 9, 15},
  {cont__check_arguments_195, &frame__check_arguments_191, 376, 397, 9, 27},
  {entry__check_arguments_190, NULL, 372, 397, 7, 28},
  {cont__check_arguments_225, &frame__check_arguments_190, 397, 397, 28, 28},
  {entry__check_arguments_189, NULL, 371, 397, 5, 29},
  {entry__check_arguments_233, NULL, 402, 402, 38, 59},
  {cont__check_arguments_234, &frame__check_arguments_233, 402, 402, 59, 59},
  {entry__check_arguments_236, NULL, 405, 405, 14, 31},
  {cont__check_arguments_237, &frame__check_arguments_236, 405, 405, 11, 55},
  {cont__check_arguments_238, &frame__check_arguments_236, 406, 406, 11, 38},
  {cont__check_arguments_239, &frame__check_arguments_236, 406, 406, 26, 38},
  {cont__check_arguments_240, &frame__check_arguments_236, 407, 407, 11, 25},
  {cont__check_arguments_241, &frame__check_arguments_236, 407, 407, 25, 25},
  {entry__check_arguments_243, NULL, 409, 409, 11, 15},
  {entry__check_arguments_230, NULL, 401, 401, 7, 69},
  {cont__check_arguments_231, &frame__check_arguments_230, 402, 402, 10, 35},
  {cont__check_arguments_232, &frame__check_arguments_230, 402, 402, 7, 59},
  {cont__check_arguments_235, &frame__check_arguments_230, 408, 408, 9, 60},
  {cont__check_arguments_242, &frame__check_arguments_230, 403, 409, 7, 16},
  {entry__check_arguments_228, NULL, 400, 400, 38, 38},
  {cont__check_arguments_229, &frame__check_arguments_228, 400, 409, 5, 17},
  {cont__check_arguments_244, &frame__check_arguments_228, 409, 409, 17, 17},
  {entry__check_arguments_249, NULL, 412, 412, 36, 57},
  {cont__check_arguments_250, &frame__check_arguments_249, 412, 412, 57, 57},
  {entry__check_arguments_252, NULL, 415, 415, 12, 31},
  {cont__check_arguments_253, &frame__check_arguments_252, 415, 415, 12, 36},
  {cont__check_arguments_254, &frame__check_arguments_252, 415, 415, 9, 60},
  {cont__check_arguments_255, &frame__check_arguments_252, 416, 416, 9, 36},
  {cont__check_arguments_256, &frame__check_arguments_252, 416, 416, 24, 36},
  {cont__check_arguments_257, &frame__check_arguments_252, 416, 416, 36, 36},
  {entry__check_arguments_261, NULL, 418, 418, 38, 65},
  {cont__check_arguments_262, &frame__check_arguments_261, 418, 418, 53, 65},
  {cont__check_arguments_263, &frame__check_arguments_261, 418, 418, 65, 65},
  {entry__check_arguments_258, NULL, 418, 418, 12, 31},
  {cont__check_arguments_259, &frame__check_arguments_258, 418, 418, 12, 35},
  {cont__check_arguments_260, &frame__check_arguments_258, 418, 418, 9, 65},
  {entry__check_arguments_264, NULL, 420, 420, 9, 21},
  {cont__check_arguments_265, &frame__check_arguments_264, 421, 421, 29, 29},
  {entry__check_arguments_266, NULL, 423, 423, 12, 31},
  {cont__check_arguments_267, &frame__check_arguments_266, 423, 423, 12, 36},
  {cont__check_arguments_268, &frame__check_arguments_266, 423, 423, 9, 60},
  {cont__check_arguments_269, &frame__check_arguments_266, 424, 424, 9, 21},
  {cont__check_arguments_270, &frame__check_arguments_266, 425, 425, 29, 29},
  {entry__check_arguments_246, NULL, 411, 411, 5, 67},
  {cont__check_arguments_247, &frame__check_arguments_246, 412, 412, 8, 33},
  {cont__check_arguments_248, &frame__check_arguments_246, 412, 412, 5, 57},
  {cont__check_arguments_251, &frame__check_arguments_246, 413, 425, 5, 30},
  {entry__check_arguments_276, NULL, 429, 429, 30, 48},
  {cont__check_arguments_277, &frame__check_arguments_276, 429, 429, 30, 59},
  {cont__check_arguments_278, &frame__check_arguments_276, 429, 429, 30, 59},
  {entry__check_arguments_280, NULL, 430, 430, 9, 41},
  {cont__check_arguments_281, &frame__check_arguments_280, 430, 430, 9, 21},
  {cont__check_arguments_282, &frame__check_arguments_280, 430, 430, 41, 41},
  {entry__check_arguments_286, NULL, 437, 437, 45, 54},
  {cont__check_arguments_287, &frame__check_arguments_286, 437, 437, 45, 68},
  {cont__check_arguments_288, &frame__check_arguments_286, 437, 437, 15, 75},
  {cont__check_arguments_291, &frame__check_arguments_286, 436, 437, 13, 75},
  {cont__check_arguments_292, &frame__check_arguments_286, 438, 438, 13, 22},
  {cont__check_arguments_293, &frame__check_arguments_286, 439, 439, 13, 18},
  {entry__check_arguments_284, NULL, 435, 435, 18, 38},
  {cont__check_arguments_285, &frame__check_arguments_284, 435, 439, 11, 18},
  {entry__check_arguments_299, NULL, 444, 444, 39, 48},
  {entry__check_arguments_298, NULL, 444, 444, 15, 48},
  {entry__check_arguments_300, NULL, 446, 446, 15, 26},
  {entry__check_arguments_296, NULL, 443, 443, 13, 28},
  {cont__check_arguments_297, &frame__check_arguments_296, 442, 446, 11, 27},
  {entry__check_arguments_307, NULL, 452, 452, 56, 71},
  {cont__check_arguments_308, &frame__check_arguments_307, 452, 452, 39, 71},
  {cont__check_arguments_309, &frame__check_arguments_307, 452, 452, 71, 71},
  {entry__check_arguments_306, NULL, 452, 452, 15, 71},
  {cont__check_arguments_310, &frame__check_arguments_306, 453, 453, 15, 27},
  {cont__check_arguments_311, &frame__check_arguments_306, 453, 453, 38, 38},
  {entry__check_arguments_312, NULL, 455, 455, 15, 46},
  {cont__check_arguments_313, &frame__check_arguments_312, 455, 455, 15, 27},
  {cont__check_arguments_314, &frame__check_arguments_312, 455, 455, 46, 46},
  {entry__check_arguments_304, NULL, 450, 450, 13, 28},
  {cont__check_arguments_305, &frame__check_arguments_304, 449, 455, 11, 47},
  {entry__check_arguments_283, NULL, 432, 432, 9, 44},
  {cont__check_arguments_294, &frame__check_arguments_283, 441, 441, 12, 36},
  {cont__check_arguments_295, &frame__check_arguments_283, 441, 446, 9, 28},
  {cont__check_arguments_301, &frame__check_arguments_283, 447, 447, 9, 36},
  {cont__check_arguments_302, &frame__check_arguments_283, 448, 448, 12, 32},
  {cont__check_arguments_303, &frame__check_arguments_283, 448, 455, 9, 48},
  {entry__check_arguments_274, NULL, 429, 429, 7, 25},
  {cont__check_arguments_275, &frame__check_arguments_274, 429, 429, 7, 59},
  {cont__check_arguments_279, &frame__check_arguments_274, 428, 455, 5, 50},
  {entry__check_arguments_1, NULL, 232, 232, 50, 50},
  {cont__check_arguments_111, &frame__check_arguments_1, 232, 232, 3, 51},
  {cont__check_arguments_112, &frame__check_arguments_1, 233, 233, 3, 26},
  {cont__check_arguments_113, &frame__check_arguments_1, 322, 356, 3, 31},
  {cont__check_arguments_160, &frame__check_arguments_1, 357, 357, 6, 25},
  {cont__check_arguments_161, &frame__check_arguments_1, 357, 357, 6, 30},
  {cont__check_arguments_162, &frame__check_arguments_1, 357, 357, 6, 30},
  {cont__check_arguments_163, &frame__check_arguments_1, 357, 366, 3, 16},
  {cont__check_arguments_188, &frame__check_arguments_1, 367, 397, 3, 30},
  {cont__check_arguments_226, &frame__check_arguments_1, 398, 398, 3, 15},
  {cont__check_arguments_227, &frame__check_arguments_1, 399, 409, 3, 18},
  {cont__check_arguments_245, &frame__check_arguments_1, 410, 425, 3, 31},
  {cont__check_arguments_271, &frame__check_arguments_1, 426, 426, 10, 27},
  {cont__check_arguments_272, &frame__check_arguments_1, 426, 426, 3, 52},
  {cont__check_arguments_273, &frame__check_arguments_1, 427, 455, 3, 51},
  {cont__check_arguments_315, &frame__check_arguments_1, 456, 456, 3, 13},
  {entry__std__program_commands_2, NULL, 468, 468, 5, 25},
  {cont__std__program_commands_3, &frame__std__program_commands_2, 469, 469, 5, 34},
  {cont__std__program_commands_4, &frame__std__program_commands_2, 470, 470, 5, 28},
  {cont__std__program_commands_5, &frame__std__program_commands_2, 471, 471, 5, 42},
  {cont__std__program_commands_6, &frame__std__program_commands_2, 472, 472, 5, 25},
  {cont__std__program_commands_7, &frame__std__program_commands_2, 473, 473, 5, 38},
  {cont__std__program_commands_8, &frame__std__program_commands_2, 473, 473, 38, 38},
  {entry__std__program_commands_1, NULL, 467, 473, 3, 38},
  {cont__std__program_commands_9, &frame__std__program_commands_1, 474, 474, 3, 17},
  {entry__std__command_parameters_3, NULL, 487, 487, 12, 26},
  {cont__std__command_parameters_4, &frame__std__command_parameters_3, 487, 487, 28, 47},
  {cont__std__command_parameters_5, &frame__std__command_parameters_3, 487, 487, 8, 48},
  {cont__std__command_parameters_6, &frame__std__command_parameters_3, 487, 487, 5, 49},
  {entry__std__command_parameters_16, NULL, 495, 495, 13, 37},
  {cont__std__command_parameters_17, &frame__std__command_parameters_16, 495, 495, 13, 47},
  {cont__std__command_parameters_18, &frame__std__command_parameters_16, 495, 495, 52, 68},
  {cont__std__command_parameters_19, &frame__std__command_parameters_16, 495, 495, 13, 68},
  {cont__std__command_parameters_20, &frame__std__command_parameters_16, 495, 495, 13, 68},
  {entry__std__command_parameters_13, NULL, 494, 494, 13, 45},
  {cont__std__command_parameters_14, &frame__std__command_parameters_13, 494, 494, 13, 50},
  {cont__std__command_parameters_15, &frame__std__command_parameters_13, 495, 495, 13, 68},
  {cont__std__command_parameters_21, &frame__std__command_parameters_13, },
  {entry__std__command_parameters_23, NULL, 497, 497, 29, 45},
  {cont__std__command_parameters_24, &frame__std__command_parameters_23, 497, 497, 47, 60},
  {cont__std__command_parameters_25, &frame__std__command_parameters_23, 497, 497, 13, 70},
  {entry__std__command_parameters_10, NULL, 493, 493, 13, 29},
  {cont__std__command_parameters_12, &frame__std__command_parameters_10, },
  {cont__std__command_parameters_22, &frame__std__command_parameters_10, 491, 497, 9, 71},
  {entry__std__command_parameters_29, NULL, 500, 500, 67, 67},
  {cont__std__command_parameters_30, &frame__std__command_parameters_29, 500, 500, 35, 68},
  {cont__std__command_parameters_31, &frame__std__command_parameters_29, 500, 500, 11, 78},
  {entry__std__command_parameters_26, NULL, 498, 498, 23, 39},
  {cont__std__command_parameters_27, &frame__std__command_parameters_26, 498, 498, 12, 39},
  {cont__std__command_parameters_28, &frame__std__command_parameters_26, 498, 500, 9, 78},
  {entry__std__command_parameters_33, NULL, 501, 501, 24, 38},
  {cont__std__command_parameters_34, &frame__std__command_parameters_33, 501, 501, 40, 59},
  {cont__std__command_parameters_35, &frame__std__command_parameters_33, 501, 501, 20, 60},
  {cont__std__command_parameters_36, &frame__std__command_parameters_33, 501, 501, 17, 61},
  {entry__std__command_parameters_32, NULL, 501, 501, 9, 61},
  {entry__std__command_parameters_7, NULL, 489, 489, 16, 40},
  {cont__std__command_parameters_8, &frame__std__command_parameters_7, 489, 489, 7, 50},
  {cont__std__command_parameters_9, &frame__std__command_parameters_7, 490, 501, 7, 61},
  {entry__std__command_parameters_1, NULL, 486, 486, 5, 35},
  {cont__std__command_parameters_2, &frame__std__command_parameters_1, 485, 501, 3, 63},
  {entry__show_commands_3, NULL, 505, 505, 51, 51},
  {cont__show_commands_4, &frame__show_commands_3, 505, 505, 18, 52},
  {cont__show_commands_5, &frame__show_commands_3, 505, 505, 5, 52},
  {entry__show_commands_12, NULL, 509, 509, 33, 57},
  {cont__show_commands_13, &frame__show_commands_12, 509, 509, 15, 58},
  {cont__show_commands_14, &frame__show_commands_12, 509, 509, 5, 58},
  {cont__show_commands_15, &frame__show_commands_12, 509, 509, 58, 58},
  {entry__show_commands_18, NULL, 511, 511, 15, 63},
  {cont__show_commands_21, &frame__show_commands_18, 511, 511, 5, 63},
  {cont__show_commands_22, &frame__show_commands_18, 511, 511, 63, 63},
  {entry__show_commands_25, NULL, 513, 513, 15, 58},
  {cont__show_commands_28, &frame__show_commands_25, 513, 513, 5, 58},
  {cont__show_commands_29, &frame__show_commands_25, 513, 513, 58, 58},
  {entry__show_commands_1, NULL, 504, 504, 6, 31},
  {cont__show_commands_2, &frame__show_commands_1, 504, 505, 3, 52},
  {cont__show_commands_6, &frame__show_commands_1, 506, 506, 3, 32},
  {cont__show_commands_8, &frame__show_commands_1, 507, 507, 14, 66},
  {cont__show_commands_10, &frame__show_commands_1, 507, 507, 3, 67},
  {cont__show_commands_11, &frame__show_commands_1, 508, 509, 3, 58},
  {cont__show_commands_16, &frame__show_commands_1, 510, 510, 6, 33},
  {cont__show_commands_17, &frame__show_commands_1, 510, 511, 3, 63},
  {cont__show_commands_23, &frame__show_commands_1, 512, 512, 6, 31},
  {cont__show_commands_24, &frame__show_commands_1, 512, 513, 3, 58},
  {cont__show_commands_30, &frame__show_commands_1, 514, 514, 3, 19},
  {entry__std__program_parameters_3, NULL, 678, 678, 7, 54},
  {entry__std__program_parameters_6, NULL, 613, 613, 33, 45},
  {entry__std__program_parameters_9, NULL, 616, 617, 13, 35},
  {cont__std__program_parameters_11, &frame__std__program_parameters_9, 618, 618, 13, 25},
  {cont__std__program_parameters_12, &frame__std__program_parameters_9, 619, 619, 13, 18},
  {entry__std__program_parameters_17, NULL, 625, 625, 19, 32},
  {cont__std__program_parameters_18, &frame__std__program_parameters_17, 626, 626, 19, 27},
  {entry__std__program_parameters_15, NULL, 624, 624, 20, 47},
  {cont__std__program_parameters_16, &frame__std__program_parameters_15, 624, 626, 17, 27},
  {entry__std__program_parameters_21, NULL, 631, 631, 21, 33},
  {cont__std__program_parameters_22, &frame__std__program_parameters_21, 632, 632, 21, 29},
  {entry__std__program_parameters_27, NULL, 638, 640, 27, 46},
  {cont__std__program_parameters_29, &frame__std__program_parameters_27, 641, 641, 27, 35},
  {entry__std__program_parameters_25, NULL, 637, 637, 28, 55},
  {cont__std__program_parameters_26, &frame__std__program_parameters_25, 637, 641, 25, 35},
  {entry__std__program_parameters_30, NULL, 644, 649, 25, 77},
  {cont__std__program_parameters_32, &frame__std__program_parameters_30, 650, 650, 25, 33},
  {entry__std__program_parameters_35, NULL, 654, 656, 27, 44},
  {cont__std__program_parameters_37, &frame__std__program_parameters_35, 657, 657, 27, 35},
  {entry__std__program_parameters_33, NULL, 653, 653, 28, 53},
  {cont__std__program_parameters_34, &frame__std__program_parameters_33, 653, 657, 25, 35},
  {entry__std__program_parameters_23, NULL, 634, 634, 26, 50},
  {cont__std__program_parameters_24, &frame__std__program_parameters_23, 634, 657, 21, 37},
  {cont__std__program_parameters_38, &frame__std__program_parameters_23, 658, 659, 21, 43},
  {cont__std__program_parameters_40, &frame__std__program_parameters_23, 660, 660, 21, 33},
  {cont__std__program_parameters_41, &frame__std__program_parameters_23, 661, 661, 21, 26},
  {entry__std__program_parameters_42, NULL, 663, 664, 21, 41},
  {cont__std__program_parameters_43, &frame__std__program_parameters_42, 665, 665, 21, 33},
  {cont__std__program_parameters_44, &frame__std__program_parameters_42, 666, 666, 21, 26},
  {entry__std__program_parameters_19, NULL, 629, 629, 22, 54},
  {cont__std__program_parameters_20, &frame__std__program_parameters_19, 629, 666, 17, 27},
  {entry__std__program_parameters_47, NULL, 670, 670, 66, 66},
  {cont__std__program_parameters_48, &frame__std__program_parameters_47, 670, 670, 19, 67},
  {cont__std__program_parameters_49, &frame__std__program_parameters_47, 671, 671, 19, 43},
  {cont__std__program_parameters_50, &frame__std__program_parameters_47, 672, 672, 19, 27},
  {entry__std__program_parameters_45, NULL, 669, 669, 20, 45},
  {cont__std__program_parameters_46, &frame__std__program_parameters_45, 669, 672, 17, 27},
  {entry__std__program_parameters_13, NULL, 621, 621, 18, 42},
  {cont__std__program_parameters_14, &frame__std__program_parameters_13, 621, 672, 13, 29},
  {cont__std__program_parameters_51, &frame__std__program_parameters_13, 673, 674, 13, 32},
  {cont__std__program_parameters_53, &frame__std__program_parameters_13, 675, 675, 13, 25},
  {cont__std__program_parameters_54, &frame__std__program_parameters_13, 676, 676, 13, 18},
  {entry__std__program_parameters_7, NULL, 615, 615, 11, 41},
  {cont__std__program_parameters_8, &frame__std__program_parameters_7, 614, 676, 9, 19},
  {entry__std__program_parameters_4, NULL, 613, 613, 10, 30},
  {cont__std__program_parameters_5, &frame__std__program_parameters_4, 613, 676, 7, 20},
  {entry__std__program_parameters_1, NULL, 612, 612, 5, 24},
  {cont__std__program_parameters_2, &frame__std__program_parameters_1, 611, 678, 3, 55}
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
  // 65: $$program_version undefined # stores the version of the application
  var._program_version = get__undefined();
  // 66: $$program_copyright undefined # stores the copyright notice the application
  var._program_copyright = get__undefined();
  // 212: $$command_id undefined
  var._command_id = get__undefined();
  // 213: $$command_id_count 0
  var._command_id_count = number__0;
  // 214: $$command_names empty_list
  var._command_names = get__empty_list();
  // 215: $$command_descriptions empty_list
  var._command_descriptions = get__empty_list();
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__copyright_1(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // msg: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 74: !program_copyright msg
  var._program_copyright = frame->slots[0] /* msg */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__version_1(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // no: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 82: !program_version no
  var._program_version = frame->slots[0] /* no */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__extract_options_1(void) {
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
  // 112: $$results empty_list
  ((CELL *)frame->slots[2])->contents /* results */ = get__empty_list();
  // 113: $$parameters empty_list
  ((CELL *)frame->slots[3])->contents /* parameters */ = get__empty_list();
  // 114: ... :
  // 115:   $$idx 1
  // 116:   for_each options: (option)
  // 117:     if
  // 118:       option.is_a_key_value_pair:
  // 119:         inc &idx
  // 120:       :
  // 121:         push &parameters option
  // 122:         delete_at &options idx
  frame->slots[4] /* temp__1 */ = create_closure(entry__std__extract_options_2, 0);
  // 114: do:
  // 115:   $$idx 1
  // 116:   for_each options: (option)
  // 117:     if
  // 118:       option.is_a_key_value_pair:
  // 119:         inc &idx
  // 120:       :
  // 121:         push &parameters option
  // 122:         delete_at &options idx
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__std__extract_options_10;
}
static void entry__std__extract_options_5(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // idx: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* idx */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 119: inc &idx
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* idx */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__std__extract_options_6;
}
static void cont__std__extract_options_6(void) {
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
static void entry__std__extract_options_7(void) {
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
  // 121: push &parameters option
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* parameters */;
  arguments->slots[1] = frame->slots[1] /* option */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__std__extract_options_8;
}
static void cont__std__extract_options_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* parameters */ = arguments->slots[0];
  // 122: delete_at &options idx
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* options */;
  arguments->slots[1] = ((CELL *)frame->slots[3])->contents /* idx */;
  result_count = 1;
  myself = get__delete_at();
  func = myself->type;
  frame->cont = cont__std__extract_options_9;
}
static void cont__std__extract_options_9(void) {
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
static void entry__std__extract_options_3(void) {
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
  // 118: option.is_a_key_value_pair
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* option */;
  result_count = 1;
  myself = get__is_a_key_value_pair();
  func = myself->type;
  frame->cont = cont__std__extract_options_4;
}
static void cont__std__extract_options_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 118: ... :
  // 119:   inc &idx
  frame->slots[5] /* temp__2 */ = create_closure(entry__std__extract_options_5, 0);
  // 120: :
  // 121:   push &parameters option
  // 122:   delete_at &options idx
  frame->slots[6] /* temp__3 */ = create_closure(entry__std__extract_options_7, 0);
  // 117: if
  // 118:   option.is_a_key_value_pair:
  // 119:     inc &idx
  // 120:   :
  // 121:     push &parameters option
  // 122:     delete_at &options idx
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
static void entry__std__extract_options_2(void) {
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
  // 115: $$idx 1
  ((CELL *)frame->slots[2])->contents /* idx */ = number__1;
  // 116: ... : (option)
  // 117:   if
  // 118:     option.is_a_key_value_pair:
  // 119:       inc &idx
  // 120:     :
  // 121:       push &parameters option
  // 122:       delete_at &options idx
  frame->slots[3] /* temp__1 */ = create_closure(entry__std__extract_options_3, 1);
  // 116: for_each options: (option)
  // 117:   if
  // 118:     option.is_a_key_value_pair:
  // 119:       inc &idx
  // 120:     :
  // 121:       push &parameters option
  // 122:       delete_at &options idx
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* options */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__std__extract_options_10(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 123: ... : (template)
  // 124:   $$result value_of(template)
  // 125:   $$idx 1
  // 126:   if
  // 127:     result == SOME_PARAMETERS:
  // 128:       !result empty_list
  // 129:       for_each options: (option)
  // 130:         if
  // 131:           key_of(option) == key_of(template):
  // 132:             delete_at &options idx
  // ...
  frame->slots[4] /* temp__1 */ = create_closure(entry__std__extract_options_11, 1);
  // 123: for_each templates: (template)
  // 124:   $$result value_of(template)
  // 125:   $$idx 1
  // 126:   if
  // 127:     result == SOME_PARAMETERS:
  // 128:       !result empty_list
  // 129:       for_each options: (option)
  // 130:         if
  // 131:           key_of(option) == key_of(template):
  // 132:             delete_at &options idx
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* templates */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__std__extract_options_37;
}
static void entry__std__extract_options_11(void) {
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
  // 124: $$result value_of(template)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* template */;
  result_count = 1;
  myself = get__value_of();
  func = myself->type;
  frame->cont = cont__std__extract_options_12;
}
static void cont__std__extract_options_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* result */ = arguments->slots[0];
  // 125: $$idx 1
  ((CELL *)frame->slots[4])->contents /* idx */ = number__1;
  // 127: result == SOME_PARAMETERS
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* result */;
  arguments->slots[1] = get__SOME_PARAMETERS();
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__std__extract_options_13;
}
static void cont__std__extract_options_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 127: ... :
  // 128:   !result empty_list
  // 129:   for_each options: (option)
  // 130:     if
  // 131:       key_of(option) == key_of(template):
  // 132:         delete_at &options idx
  // 133:         push &result value_of(option)
  // 134:       :
  // 135:         inc &idx
  frame->slots[6] /* temp__2 */ = create_closure(entry__std__extract_options_14, 0);
  // 136: :
  // 137:   for_each options: (option)
  // 138:     if
  // 139:       key_of(option) == key_of(template):
  // 140:         delete_at &options idx
  // 141:         !result value_of(option)
  // 142:       :
  // 143:         inc &idx
  frame->slots[7] /* temp__3 */ = create_closure(entry__std__extract_options_25, 0);
  // 126: if
  // 127:   result == SOME_PARAMETERS:
  // 128:     !result empty_list
  // 129:     for_each options: (option)
  // 130:       if
  // 131:         key_of(option) == key_of(template):
  // 132:           delete_at &options idx
  // 133:           push &result value_of(option)
  // 134:         :
  // 135:           inc &idx
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  arguments->slots[2] = frame->slots[7] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__std__extract_options_35;
}
static void entry__std__extract_options_30(void) {
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
  // 140: delete_at &options idx
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* options */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* idx */;
  result_count = 1;
  myself = get__delete_at();
  func = myself->type;
  frame->cont = cont__std__extract_options_31;
}
static void cont__std__extract_options_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* options */ = arguments->slots[0];
  // 141: !result value_of(option)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* option */;
  result_count = 1;
  myself = get__value_of();
  func = myself->type;
  frame->cont = cont__std__extract_options_32;
}
static void cont__std__extract_options_32(void) {
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
static void entry__std__extract_options_33(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // idx: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* idx */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 143: inc &idx
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* idx */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__std__extract_options_34;
}
static void cont__std__extract_options_34(void) {
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
static void entry__std__extract_options_26(void) {
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
  // 139: key_of(option)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* option */;
  result_count = 1;
  myself = get__key_of();
  func = myself->type;
  frame->cont = cont__std__extract_options_27;
}
static void cont__std__extract_options_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 139: ... key_of(template)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* template */;
  result_count = 1;
  myself = get__key_of();
  func = myself->type;
  frame->cont = cont__std__extract_options_28;
}
static void cont__std__extract_options_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__3 */ = arguments->slots[0];
  // 139: key_of(option) == key_of(template)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__std__extract_options_29;
}
static void cont__std__extract_options_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 139: ... :
  // 140:   delete_at &options idx
  // 141:   !result value_of(option)
  frame->slots[8] /* temp__4 */ = create_closure(entry__std__extract_options_30, 0);
  // 142: :
  // 143:   inc &idx
  frame->slots[9] /* temp__5 */ = create_closure(entry__std__extract_options_33, 0);
  // 138: if
  // 139:   key_of(option) == key_of(template):
  // 140:     delete_at &options idx
  // 141:     !result value_of(option)
  // 142:   :
  // 143:     inc &idx
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
static void entry__std__extract_options_19(void) {
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
  // 132: delete_at &options idx
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* options */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* idx */;
  result_count = 1;
  myself = get__delete_at();
  func = myself->type;
  frame->cont = cont__std__extract_options_20;
}
static void cont__std__extract_options_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* options */ = arguments->slots[0];
  // 133: ... value_of(option)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* option */;
  result_count = 1;
  myself = get__value_of();
  func = myself->type;
  frame->cont = cont__std__extract_options_21;
}
static void cont__std__extract_options_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 133: push &result value_of(option)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* result */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__std__extract_options_22;
}
static void cont__std__extract_options_22(void) {
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
static void entry__std__extract_options_23(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // idx: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* idx */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 135: inc &idx
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* idx */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__std__extract_options_24;
}
static void cont__std__extract_options_24(void) {
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
static void entry__std__extract_options_15(void) {
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
  // 131: key_of(option)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* option */;
  result_count = 1;
  myself = get__key_of();
  func = myself->type;
  frame->cont = cont__std__extract_options_16;
}
static void cont__std__extract_options_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 131: ... key_of(template)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* template */;
  result_count = 1;
  myself = get__key_of();
  func = myself->type;
  frame->cont = cont__std__extract_options_17;
}
static void cont__std__extract_options_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__3 */ = arguments->slots[0];
  // 131: key_of(option) == key_of(template)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__std__extract_options_18;
}
static void cont__std__extract_options_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 131: ... :
  // 132:   delete_at &options idx
  // 133:   push &result value_of(option)
  frame->slots[8] /* temp__4 */ = create_closure(entry__std__extract_options_19, 0);
  // 134: :
  // 135:   inc &idx
  frame->slots[9] /* temp__5 */ = create_closure(entry__std__extract_options_23, 0);
  // 130: if
  // 131:   key_of(option) == key_of(template):
  // 132:     delete_at &options idx
  // 133:     push &result value_of(option)
  // 134:   :
  // 135:     inc &idx
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
static void entry__std__extract_options_14(void) {
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
  // 128: !result empty_list
  ((CELL *)frame->slots[0])->contents /* result */ = get__empty_list();
  // 129: ... : (option)
  // 130:   if
  // 131:     key_of(option) == key_of(template):
  // 132:       delete_at &options idx
  // 133:       push &result value_of(option)
  // 134:     :
  // 135:       inc &idx
  frame->slots[4] /* temp__1 */ = create_closure(entry__std__extract_options_15, 1);
  // 129: for_each options: (option)
  // 130:   if
  // 131:     key_of(option) == key_of(template):
  // 132:       delete_at &options idx
  // 133:       push &result value_of(option)
  // 134:     :
  // 135:       inc &idx
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* options */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__extract_options_25(void) {
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
  // 137: ... : (option)
  // 138:   if
  // 139:     key_of(option) == key_of(template):
  // 140:       delete_at &options idx
  // 141:       !result value_of(option)
  // 142:     :
  // 143:       inc &idx
  frame->slots[4] /* temp__1 */ = create_closure(entry__std__extract_options_26, 1);
  // 137: for_each options: (option)
  // 138:   if
  // 139:     key_of(option) == key_of(template):
  // 140:       delete_at &options idx
  // 141:       !result value_of(option)
  // 142:     :
  // 143:       inc &idx
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* options */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__std__extract_options_35(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 144: push &results result
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* results */;
  arguments->slots[1] = ((CELL *)frame->slots[3])->contents /* result */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__std__extract_options_36;
}
static void cont__std__extract_options_36(void) {
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
static void cont__std__extract_options_37(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 145: ... options.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* options */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__std__extract_options_38;
}
static void cont__std__extract_options_38(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 145: ... :
  // 146:   Error "Invalid option @(range(debug_string(key_of(options(1))) 1 -2))!"
  frame->slots[5] /* temp__2 */ = create_closure(entry__std__extract_options_39, 0);
  // 145: unless options.is_empty:
  // 146:   Error "Invalid option @(range(debug_string(key_of(options(1))) 1 -2))!"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__std__extract_options_48;
}
static void entry__std__extract_options_39(void) {
  allocate_initialized_frame_gc(1, 7);
  // slot allocations:
  // options: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* options */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 146: ... options(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* options */;
  func = myself->type;
  frame->cont = cont__std__extract_options_40;
}
static void cont__std__extract_options_40(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__5 */ = arguments->slots[0];
  // 146: ... key_of(options(1))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__5 */;
  result_count = 1;
  myself = get__key_of();
  func = myself->type;
  frame->cont = cont__std__extract_options_41;
}
static void cont__std__extract_options_41(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__4 */ = arguments->slots[0];
  // 146: ... debug_string(key_of(options(1)))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__4 */;
  result_count = 1;
  myself = get__debug_string();
  func = myself->type;
  frame->cont = cont__std__extract_options_42;
}
static void cont__std__extract_options_42(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 146: ... 2
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__std__extract_options_43;
}
static void cont__std__extract_options_43(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__6 */ = arguments->slots[0];
  // 146: ... range(debug_string(key_of(options(1))) 1 -2)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[6] /* temp__6 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__std__extract_options_44;
}
static void cont__std__extract_options_44(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 146: ... "Invalid option @(range(debug_string(key_of(options(1))) 1 -2))!"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__629e8589dc7e42e;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  arguments->slots[2] = string__578a5af303e9cc0;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__std__extract_options_47;
}
static void cont__std__extract_options_47(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 146: Error "Invalid option @(range(debug_string(key_of(options(1))) 1 -2))!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__std__extract_options_48(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 147: -> results* parameters*
  argument_count = 0;
  arguments = node_p;
  unfold(((CELL *)frame->slots[2])->contents /* results */);
  unfold(((CELL *)frame->slots[3])->contents /* parameters */);
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__extract_some_options_1(void) {
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
  // 177: $$results empty_list
  ((CELL *)frame->slots[2])->contents /* results */ = get__empty_list();
  // 178: ... : (template)
  // 179:   $$result value_of(template)
  // 180:   $$idx 1
  // 181:   if
  // 182:     result == SOME_PARAMETERS:
  // 183:       !result empty_list
  // 184:       for_each options: (option)
  // 185:         if
  // 186:           key_of(option) == key_of(template):
  // 187:             delete_at &options idx
  // ...
  frame->slots[3] /* temp__1 */ = create_closure(entry__std__extract_some_options_2, 1);
  // 178: for_each templates: (template)
  // 179:   $$result value_of(template)
  // 180:   $$idx 1
  // 181:   if
  // 182:     result == SOME_PARAMETERS:
  // 183:       !result empty_list
  // 184:       for_each options: (option)
  // 185:         if
  // 186:           key_of(option) == key_of(template):
  // 187:             delete_at &options idx
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* templates */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__std__extract_some_options_31;
}
static void entry__std__extract_some_options_2(void) {
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
  // 179: $$result value_of(template)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* template */;
  result_count = 1;
  myself = get__value_of();
  func = myself->type;
  frame->cont = cont__std__extract_some_options_3;
}
static void cont__std__extract_some_options_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* result */ = arguments->slots[0];
  // 180: $$idx 1
  ((CELL *)frame->slots[4])->contents /* idx */ = number__1;
  // 182: result == SOME_PARAMETERS
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* result */;
  arguments->slots[1] = get__SOME_PARAMETERS();
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__std__extract_some_options_4;
}
static void cont__std__extract_some_options_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 182: ... :
  // 183:   !result empty_list
  // 184:   for_each options: (option)
  // 185:     if
  // 186:       key_of(option) == key_of(template):
  // 187:         delete_at &options idx
  // 188:         push &result value_of(option)
  // 189:       :
  // 190:         inc &idx
  frame->slots[6] /* temp__2 */ = create_closure(entry__std__extract_some_options_5, 0);
  // 191: :
  // 192:   for_each options: (option)
  // 193:     if
  // 194:       option.is_a_key_value_pair && key_of(option) == key_of(template):
  // 195:         delete_at &options idx
  // 196:         !result value_of(option)
  // 197:       :
  // 198:         inc &idx
  frame->slots[7] /* temp__3 */ = create_closure(entry__std__extract_some_options_16, 0);
  // 181: if
  // 182:   result == SOME_PARAMETERS:
  // 183:     !result empty_list
  // 184:     for_each options: (option)
  // 185:       if
  // 186:         key_of(option) == key_of(template):
  // 187:           delete_at &options idx
  // 188:           push &result value_of(option)
  // 189:         :
  // 190:           inc &idx
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  arguments->slots[2] = frame->slots[7] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__std__extract_some_options_29;
}
static void entry__std__extract_some_options_24(void) {
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
  // 195: delete_at &options idx
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* options */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* idx */;
  result_count = 1;
  myself = get__delete_at();
  func = myself->type;
  frame->cont = cont__std__extract_some_options_25;
}
static void cont__std__extract_some_options_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* options */ = arguments->slots[0];
  // 196: !result value_of(option)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* option */;
  result_count = 1;
  myself = get__value_of();
  func = myself->type;
  frame->cont = cont__std__extract_some_options_26;
}
static void cont__std__extract_some_options_26(void) {
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
static void entry__std__extract_some_options_27(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // idx: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* idx */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 198: inc &idx
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* idx */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__std__extract_some_options_28;
}
static void cont__std__extract_some_options_28(void) {
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
static void entry__std__extract_some_options_17(void) {
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
  // 194: option.is_a_key_value_pair
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* option */;
  result_count = 1;
  myself = get__is_a_key_value_pair();
  func = myself->type;
  frame->cont = cont__std__extract_some_options_18;
}
static void cont__std__extract_some_options_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 194: ... key_of(option) == key_of(template)
  frame->slots[7] /* temp__3 */ = create_closure(entry__std__extract_some_options_19, 0);
  // 194: option.is_a_key_value_pair && key_of(option) == key_of(template)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__std__extract_some_options_23;
}
static void entry__std__extract_some_options_19(void) {
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
  // 194: ... key_of(option)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* option */;
  result_count = 1;
  myself = get__key_of();
  func = myself->type;
  frame->cont = cont__std__extract_some_options_20;
}
static void cont__std__extract_some_options_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 194: ... key_of(template)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* template */;
  result_count = 1;
  myself = get__key_of();
  func = myself->type;
  frame->cont = cont__std__extract_some_options_21;
}
static void cont__std__extract_some_options_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 194: ... key_of(option) == key_of(template)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__std__extract_some_options_22;
}
static void cont__std__extract_some_options_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 194: ... key_of(option) == key_of(template)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__std__extract_some_options_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 194: ... :
  // 195:   delete_at &options idx
  // 196:   !result value_of(option)
  frame->slots[8] /* temp__4 */ = create_closure(entry__std__extract_some_options_24, 0);
  // 197: :
  // 198:   inc &idx
  frame->slots[9] /* temp__5 */ = create_closure(entry__std__extract_some_options_27, 0);
  // 193: if
  // 194:   option.is_a_key_value_pair && key_of(option) == key_of(template):
  // 195:     delete_at &options idx
  // 196:     !result value_of(option)
  // 197:   :
  // 198:     inc &idx
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
static void entry__std__extract_some_options_10(void) {
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
  // 187: delete_at &options idx
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* options */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* idx */;
  result_count = 1;
  myself = get__delete_at();
  func = myself->type;
  frame->cont = cont__std__extract_some_options_11;
}
static void cont__std__extract_some_options_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* options */ = arguments->slots[0];
  // 188: ... value_of(option)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* option */;
  result_count = 1;
  myself = get__value_of();
  func = myself->type;
  frame->cont = cont__std__extract_some_options_12;
}
static void cont__std__extract_some_options_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 188: push &result value_of(option)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* result */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__std__extract_some_options_13;
}
static void cont__std__extract_some_options_13(void) {
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
static void entry__std__extract_some_options_14(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // idx: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* idx */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 190: inc &idx
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* idx */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__std__extract_some_options_15;
}
static void cont__std__extract_some_options_15(void) {
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
static void entry__std__extract_some_options_6(void) {
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
  // 186: key_of(option)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* option */;
  result_count = 1;
  myself = get__key_of();
  func = myself->type;
  frame->cont = cont__std__extract_some_options_7;
}
static void cont__std__extract_some_options_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 186: ... key_of(template)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* template */;
  result_count = 1;
  myself = get__key_of();
  func = myself->type;
  frame->cont = cont__std__extract_some_options_8;
}
static void cont__std__extract_some_options_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__3 */ = arguments->slots[0];
  // 186: key_of(option) == key_of(template)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__std__extract_some_options_9;
}
static void cont__std__extract_some_options_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 186: ... :
  // 187:   delete_at &options idx
  // 188:   push &result value_of(option)
  frame->slots[8] /* temp__4 */ = create_closure(entry__std__extract_some_options_10, 0);
  // 189: :
  // 190:   inc &idx
  frame->slots[9] /* temp__5 */ = create_closure(entry__std__extract_some_options_14, 0);
  // 185: if
  // 186:   key_of(option) == key_of(template):
  // 187:     delete_at &options idx
  // 188:     push &result value_of(option)
  // 189:   :
  // 190:     inc &idx
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
static void entry__std__extract_some_options_5(void) {
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
  // 183: !result empty_list
  ((CELL *)frame->slots[0])->contents /* result */ = get__empty_list();
  // 184: ... : (option)
  // 185:   if
  // 186:     key_of(option) == key_of(template):
  // 187:       delete_at &options idx
  // 188:       push &result value_of(option)
  // 189:     :
  // 190:       inc &idx
  frame->slots[4] /* temp__1 */ = create_closure(entry__std__extract_some_options_6, 1);
  // 184: for_each options: (option)
  // 185:   if
  // 186:     key_of(option) == key_of(template):
  // 187:       delete_at &options idx
  // 188:       push &result value_of(option)
  // 189:     :
  // 190:       inc &idx
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* options */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__extract_some_options_16(void) {
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
  // 192: ... : (option)
  // 193:   if
  // 194:     option.is_a_key_value_pair && key_of(option) == key_of(template):
  // 195:       delete_at &options idx
  // 196:       !result value_of(option)
  // 197:     :
  // 198:       inc &idx
  frame->slots[4] /* temp__1 */ = create_closure(entry__std__extract_some_options_17, 1);
  // 192: for_each options: (option)
  // 193:   if
  // 194:     option.is_a_key_value_pair && key_of(option) == key_of(template):
  // 195:       delete_at &options idx
  // 196:       !result value_of(option)
  // 197:     :
  // 198:       inc &idx
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* options */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__std__extract_some_options_29(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 199: push &results result
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* results */;
  arguments->slots[1] = ((CELL *)frame->slots[3])->contents /* result */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__std__extract_some_options_30;
}
static void cont__std__extract_some_options_30(void) {
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
static void cont__std__extract_some_options_31(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 200: -> results*
  argument_count = 0;
  arguments = node_p;
  arguments->slots[argument_count++] = ((CELL *)frame->slots[0])->contents /* options */;
  unfold(((CELL *)frame->slots[2])->contents /* results */);
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__display_table_14(void) {
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
  // 209: ... idx != 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* idx */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__display_table_15;
}
static void cont__display_table_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 209: ... idx != 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__display_table_16;
}
static void cont__display_table_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 209: ... : ewrite " " .dup. 2+first_column_width
  frame->slots[5] /* temp__3 */ = create_closure(entry__display_table_17, 0);
  // 209: if idx != 1: ewrite " " .dup. 2+first_column_width
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__display_table_21;
}
static void entry__display_table_17(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // first_column_width: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* first_column_width */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 209: ... 2+first_column_width
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__2;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* first_column_width */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__display_table_18;
}
static void cont__display_table_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 209: ... " " .dup. 2+first_column_width
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__578a5af303e9cc1;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__dup();
  func = myself->type;
  frame->cont = cont__display_table_20;
}
static void cont__display_table_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 209: ... ewrite " " .dup. 2+first_column_width
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__ewrite();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__display_table_21(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 210: ewriteln line
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* line */;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__display_table_8(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // entry: 0
  // first_column_width: 1
  frame->slots[1] = myself->closure.frame->slots[1]; /* first_column_width */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 207: ... entry(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* entry */;
  func = myself->type;
  frame->cont = cont__display_table_9;
}
static void cont__display_table_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 207: ... pad_right(entry(1) first_column_width)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* first_column_width */;
  result_count = 1;
  myself = get__pad_right();
  func = myself->type;
  frame->cont = cont__display_table_10;
}
static void cont__display_table_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 207: ewrite "  " pad_right(entry(1) first_column_width)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e6082be5;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__ewrite();
  func = myself->type;
  frame->cont = cont__display_table_12;
}
static void cont__display_table_12(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 208: ... entry(2)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = frame->slots[0] /* entry */;
  func = myself->type;
  frame->cont = cont__display_table_13;
}
static void cont__display_table_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 208: ... : (idx line)
  // 209:   if idx != 1: ewrite " " .dup. 2+first_column_width
  // 210:   ewriteln line
  frame->slots[3] /* temp__2 */ = create_closure(entry__display_table_14, 2);
  // 208: for_each_line entry(2): (idx line)
  // 209:   if idx != 1: ewrite " " .dup. 2+first_column_width
  // 210:   ewriteln line
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__for_each_line();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__display_table_1(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // tab: 0
  // first_column_width: 1
  frame->slots[1] /* first_column_width */ = create_cell();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 203: $$first_column_width 0
  ((CELL *)frame->slots[1])->contents /* first_column_width */ = number__0;
  // 204: ... : (entry) extend_to &first_column_width length_of(entry(1))
  frame->slots[2] /* temp__1 */ = create_closure(entry__display_table_2, 1);
  // 204: for_each tab: (entry) extend_to &first_column_width length_of(entry(1))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* tab */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__display_table_6;
}
static void entry__display_table_2(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // entry: 0
  // first_column_width: 1
  frame->slots[1] = myself->closure.frame->slots[1]; /* first_column_width */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 204: ... entry(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* entry */;
  func = myself->type;
  frame->cont = cont__display_table_3;
}
static void cont__display_table_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 204: ... length_of(entry(1))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__display_table_4;
}
static void cont__display_table_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 204: ... extend_to &first_column_width length_of(entry(1))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* first_column_width */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__extend_to();
  func = myself->type;
  frame->cont = cont__display_table_5;
}
static void cont__display_table_5(void) {
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
static void cont__display_table_6(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 205: plus &first_column_width 2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* first_column_width */;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__plus();
  func = myself->type;
  frame->cont = cont__display_table_7;
}
static void cont__display_table_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* first_column_width */ = arguments->slots[0];
  // 206: ... : (entry)
  // 207:   ewrite "  " pad_right(entry(1) first_column_width)
  // 208:   for_each_line entry(2): (idx line)
  // 209:     if idx != 1: ewrite " " .dup. 2+first_column_width
  // 210:     ewriteln line
  frame->slots[2] /* temp__1 */ = create_closure(entry__display_table_8, 1);
  // 206: for_each tab: (entry)
  // 207:   ewrite "  " pad_right(entry(1) first_column_width)
  // 208:   for_each_line entry(2): (idx line)
  // 209:     if idx != 1: ewrite " " .dup. 2+first_column_width
  // 210:     ewriteln line
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* tab */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__show_version_1(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // command_name: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 218: ... "@(command_name) @(program_version)@nl;@nl;"
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* command_name */;
  arguments->slots[1] = string__578a5af303e9cc1;
  arguments->slots[2] = var._program_version;
  arguments->slots[3] = string__2d7981f4e7582bcf;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__show_version_3;
}
static void cont__show_version_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 218: ewrite "@(command_name) @(program_version)@nl;@nl;"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__ewrite();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__show_copyright_1(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 220: ... ewrite program_copyright
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._program_copyright;
  result_count = frame->caller_result_count;
  myself = get__ewrite();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__check_arguments_1(void) {
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
  // 235: ... : (idx)
  // 236:   $$message help_messages(idx)
  // 237:   $possible_value possible_values(idx)
  // 238:   if possible_value.is_defined:
  // 239:     append &message "valid values:"
  // 240:     for_each possible_value: (value) write_to &message ' ' value ','
  // 241:     !message(-1) '@nl;'
  // 242:   $default_value default_values(idx)
  // 243:   if default_value.is_defined:
  // 244:     !message(-1) ' '
  // ...
  frame->slots[18] /* temp__1 */ = create_closure(entry__check_arguments_2, 1);
  // 235: $help_message: (idx)
  // 236:   $$message help_messages(idx)
  // 237:   $possible_value possible_values(idx)
  // 238:   if possible_value.is_defined:
  // 239:     append &message "valid values:"
  // 240:     for_each possible_value: (value) write_to &message ' ' value ','
  // 241:     !message(-1) '@nl;'
  // 242:   $default_value default_values(idx)
  // 243:   if default_value.is_defined:
  // 244:     !message(-1) ' '
  // ...
  initialize_future(frame->slots[13] /* help_message */, frame->slots[18] /* temp__1 */);
  // 248: ... :
  // 249:   $parameter_name: (parameter idx)
  // 250:     $$buf parameter.to_upper_case
  // 251:     case kinds(idx)
  // 252:       OPTIONAL_PARAMETER:
  // 253:         push &buf '?'
  // 254:       SOME_PARAMETERS:
  // 255:         push &buf '*'
  // 256:       MANY_PARAMETERS:
  // 257:         push &buf '+'
  // ...
  frame->slots[18] /* temp__1 */ = create_closure(entry__check_arguments_25, 0);
  // 248: $show_usage:
  // 249:   $parameter_name: (parameter idx)
  // 250:     $$buf parameter.to_upper_case
  // 251:     case kinds(idx)
  // 252:       OPTIONAL_PARAMETER:
  // 253:         push &buf '?'
  // 254:       SOME_PARAMETERS:
  // 255:         push &buf '*'
  // 256:       MANY_PARAMETERS:
  // 257:         push &buf '+'
  // ...
  initialize_future(frame->slots[14] /* show_usage */, frame->slots[18] /* temp__1 */);
  // 305: ... :
  // 306:   if
  // 307:     command.is_defined:
  // 308:       ewriteln "
  // 309:         Too few arguments for @(command)-command!
  // 310:     :
  // 311:       ewriteln "
  // 312:         Too few arguments!
  // 313:   show_usage
  // 314:   exit 1
  frame->slots[18] /* temp__1 */ = create_closure(entry__check_arguments_97, 0);
  // 305: $too_few_arguments_error:
  // 306:   if
  // 307:     command.is_defined:
  // 308:       ewriteln "
  // 309:         Too few arguments for @(command)-command!
  // 310:     :
  // 311:       ewriteln "
  // 312:         Too few arguments!
  // 313:   show_usage
  // 314:   exit 1
  initialize_future(frame->slots[15] /* too_few_arguments_error */, frame->slots[18] /* temp__1 */);
  // 316: ... :
  // 317:   ewriteln "
  // 318:     Too many arguments!
  // 319:   show_usage
  // 320:   exit 1
  frame->slots[18] /* temp__1 */ = create_closure(entry__check_arguments_107, 0);
  // 316: $too_many_arguments_error:
  // 317:   ewriteln "
  // 318:     Too many arguments!
  // 319:   show_usage
  // 320:   exit 1
  initialize_future(frame->slots[16] /* too_many_arguments_error */, frame->slots[18] /* temp__1 */);
  // 223: $$results empty_list
  ((CELL *)frame->slots[3])->contents /* results */ = get__empty_list();
  // 224: $$options empty_key_order_table
  ((CELL *)frame->slots[4])->contents /* options */ = get__empty_key_order_table();
  // 225: $$parameters empty_insert_order_table
  ((CELL *)frame->slots[5])->contents /* parameters */ = get__empty_insert_order_table();
  // 226: $$names empty_list
  ((CELL *)frame->slots[6])->contents /* names */ = get__empty_list();
  // 227: $$kinds empty_list
  ((CELL *)frame->slots[7])->contents /* kinds */ = get__empty_list();
  // 228: $$possible_values empty_list
  ((CELL *)frame->slots[8])->contents /* possible_values */ = get__empty_list();
  // 229: $$default_values empty_list
  ((CELL *)frame->slots[9])->contents /* default_values */ = get__empty_list();
  // 230: $$conversions empty_list
  ((CELL *)frame->slots[10])->contents /* conversions */ = get__empty_list();
  // 231: $$help_messages empty_list
  ((CELL *)frame->slots[11])->contents /* help_messages */ = get__empty_list();
  // 232: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__check_arguments_111;
}
static void entry__check_arguments_79(void) {
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
  // 291: $$tab empty_list
  ((CELL *)frame->slots[3])->contents /* tab */ = get__empty_list();
  // 292: ... : (option idx)
  // 293:   $option_name:
  // 294:     $$buf string("--" option)
  // 295:     case kinds(idx)
  // 296:       VALUED_OPTION:
  // 297:         append &buf " VALUE"
  // 298:       MULTI_VALUED_OPTION:
  // 299:         append &buf " VALUES"
  // 300:     -> buf
  // 301:   
  // ...
  frame->slots[4] /* temp__1 */ = create_closure(entry__check_arguments_80, 2);
  // 292: for_each options: (option idx)
  // 293:   $option_name:
  // 294:     $$buf string("--" option)
  // 295:     case kinds(idx)
  // 296:       VALUED_OPTION:
  // 297:         append &buf " VALUE"
  // 298:       MULTI_VALUED_OPTION:
  // 299:         append &buf " VALUES"
  // 300:     -> buf
  // 301:   
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* options */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__check_arguments_96;
}
static void entry__check_arguments_80(void) {
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
  // 293: ... :
  // 294:   $$buf string("--" option)
  // 295:   case kinds(idx)
  // 296:     VALUED_OPTION:
  // 297:       append &buf " VALUE"
  // 298:     MULTI_VALUED_OPTION:
  // 299:       append &buf " VALUES"
  // 300:   -> buf
  frame->slots[6] /* temp__1 */ = create_closure(entry__check_arguments_81, 0);
  // 293: $option_name:
  // 294:   $$buf string("--" option)
  // 295:   case kinds(idx)
  // 296:     VALUED_OPTION:
  // 297:       append &buf " VALUE"
  // 298:     MULTI_VALUED_OPTION:
  // 299:       append &buf " VALUES"
  // 300:   -> buf
  initialize_future(frame->slots[5] /* option_name */, frame->slots[6] /* temp__1 */);
  // 302: ... option_name()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = frame->slots[5] /* option_name */;
  func = myself->type;
  frame->cont = cont__check_arguments_92;
}
static void entry__check_arguments_81(void) {
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
  // 294: $$buf string("--" option)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e6602be8;
  arguments->slots[1] = frame->slots[0] /* option */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__check_arguments_83;
}
static void cont__check_arguments_83(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* buf */ = arguments->slots[0];
  // 295: ... kinds(idx)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* idx */;
  result_count = 1;
  myself = ((CELL *)frame->slots[1])->contents /* kinds */;
  func = myself->type;
  frame->cont = cont__check_arguments_84;
}
static void cont__check_arguments_84(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 296: ... :
  // 297:   append &buf " VALUE"
  frame->slots[5] /* temp__2 */ = create_closure(entry__check_arguments_85, 0);
  // 298: ... :
  // 299:   append &buf " VALUES"
  frame->slots[6] /* temp__3 */ = create_closure(entry__check_arguments_88, 0);
  // 295: case kinds(idx)
  // 296:   VALUED_OPTION:
  // 297:     append &buf " VALUE"
  // 298:   MULTI_VALUED_OPTION:
  // 299:     append &buf " VALUES"
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
  frame->cont = cont__check_arguments_91;
}
static void entry__check_arguments_85(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // buf: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* buf */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 297: append &buf " VALUE"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* buf */;
  arguments->slots[1] = string__1a1f5d6080113292;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__check_arguments_87;
}
static void cont__check_arguments_87(void) {
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
static void entry__check_arguments_88(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // buf: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* buf */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 299: append &buf " VALUES"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* buf */;
  arguments->slots[1] = string__eb0400899490d0a9;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__check_arguments_90;
}
static void cont__check_arguments_90(void) {
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
static void cont__check_arguments_91(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 300: -> buf
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* buf */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__check_arguments_92(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 302: ... help_messages(idx)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* idx */;
  result_count = 1;
  myself = ((CELL *)frame->slots[4])->contents /* help_messages */;
  func = myself->type;
  frame->cont = cont__check_arguments_93;
}
static void cont__check_arguments_93(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__3 */ = arguments->slots[0];
  // 302: ... list(option_name() help_messages(idx))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__2 */;
  arguments->slots[1] = frame->slots[8] /* temp__3 */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__check_arguments_94;
}
static void cont__check_arguments_94(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 302: push &tab list(option_name() help_messages(idx))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* tab */;
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__check_arguments_95;
}
static void cont__check_arguments_95(void) {
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
static void cont__check_arguments_96(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 303: display_table tab
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* tab */;
  result_count = frame->caller_result_count;
  myself = var._display_table;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__check_arguments_76(void) {
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
  // 287: ewrite "
  // 288:   
  // 289:   Options:
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__293744df0bfb878b;
  result_count = 0;
  myself = get__ewrite();
  func = myself->type;
  frame->cont = cont__check_arguments_78;
}
static void cont__check_arguments_78(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 290: ... :
  // 291:   $$tab empty_list
  // 292:   for_each options: (option idx)
  // 293:     $option_name:
  // 294:       $$buf string("--" option)
  // 295:       case kinds(idx)
  // 296:         VALUED_OPTION:
  // 297:           append &buf " VALUE"
  // 298:         MULTI_VALUED_OPTION:
  // 299:           append &buf " VALUES"
  // ...
  frame->slots[3] /* temp__1 */ = create_closure(entry__check_arguments_79, 0);
  // 290: do:
  // 291:   $$tab empty_list
  // 292:   for_each options: (option idx)
  // 293:     $option_name:
  // 294:       $$buf string("--" option)
  // 295:       case kinds(idx)
  // 296:         VALUED_OPTION:
  // 297:           append &buf " VALUE"
  // 298:         MULTI_VALUED_OPTION:
  // 299:           append &buf " VALUES"
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__do();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__check_arguments_2(void) {
  allocate_initialized_frame_gc(4, 9);
  // slot allocations:
  // idx: 0
  // help_messages: 1
  // possible_values: 2
  // default_values: 3
  // message: 4
  // possible_value: 5
  // default_value: 6
  frame->slots[1] = myself->closure.frame->slots[11]; /* help_messages */
  frame->slots[2] = myself->closure.frame->slots[8]; /* possible_values */
  frame->slots[3] = myself->closure.frame->slots[9]; /* default_values */
  frame->slots[4] /* message */ = create_cell();
  frame->slots[5] /* possible_value */ = create_future();
  frame->slots[6] /* default_value */ = create_future();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 236: $$message help_messages(idx)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* idx */;
  result_count = 1;
  myself = ((CELL *)frame->slots[1])->contents /* help_messages */;
  func = myself->type;
  frame->cont = cont__check_arguments_3;
}
static void cont__check_arguments_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[4])->contents /* message */ = arguments->slots[0];
  // 237: $possible_value possible_values(idx)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* idx */;
  result_count = 1;
  myself = ((CELL *)frame->slots[2])->contents /* possible_values */;
  func = myself->type;
  frame->cont = cont__check_arguments_4;
}
static void cont__check_arguments_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* possible_value */, arguments->slots[0]);
  // 238: ... possible_value.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* possible_value */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__check_arguments_5;
}
static void cont__check_arguments_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 238: ... :
  // 239:   append &message "valid values:"
  // 240:   for_each possible_value: (value) write_to &message ' ' value ','
  // 241:   !message(-1) '@nl;'
  frame->slots[8] /* temp__2 */ = create_closure(entry__check_arguments_6, 0);
  // 238: if possible_value.is_defined:
  // 239:   append &message "valid values:"
  // 240:   for_each possible_value: (value) write_to &message ' ' value ','
  // 241:   !message(-1) '@nl;'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__check_arguments_14;
}
static void entry__check_arguments_6(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // message: 0
  // possible_value: 1
  frame->slots[0] = myself->closure.frame->slots[4]; /* message */
  frame->slots[1] = myself->closure.frame->slots[5]; /* possible_value */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 239: append &message "valid values:"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* message */;
  arguments->slots[1] = string__e8329800b0d69ed2;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__check_arguments_8;
}
static void cont__check_arguments_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* message */ = arguments->slots[0];
  // 240: ... : (value) write_to &message ' ' value ','
  frame->slots[2] /* temp__1 */ = create_closure(entry__check_arguments_9, 1);
  // 240: for_each possible_value: (value) write_to &message ' ' value ','
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* possible_value */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__check_arguments_11;
}
static void entry__check_arguments_9(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // value: 0
  // message: 1
  frame->slots[1] = myself->closure.frame->slots[0]; /* message */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 240: ... write_to &message ' ' value ','
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* message */;
  arguments->slots[1] = character__32;
  arguments->slots[2] = frame->slots[0] /* value */;
  arguments->slots[3] = character__44;
  result_count = 1;
  myself = get__write_to();
  func = myself->type;
  frame->cont = cont__check_arguments_10;
}
static void cont__check_arguments_10(void) {
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
static void cont__check_arguments_11(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 241: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__check_arguments_12;
}
static void cont__check_arguments_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 241: !message(-1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = character__10;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* message */;
  func = myself->type;
  frame->cont = cont__check_arguments_13;
}
static void cont__check_arguments_13(void) {
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
static void cont__check_arguments_14(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 242: $default_value default_values(idx)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* idx */;
  result_count = 1;
  myself = ((CELL *)frame->slots[3])->contents /* default_values */;
  func = myself->type;
  frame->cont = cont__check_arguments_15;
}
static void cont__check_arguments_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* default_value */, arguments->slots[0]);
  // 243: ... default_value.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* default_value */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__check_arguments_16;
}
static void cont__check_arguments_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 243: ... :
  // 244:   !message(-1) ' '
  // 245:   append &message "(default value: @(default_value))"
  frame->slots[8] /* temp__2 */ = create_closure(entry__check_arguments_17, 0);
  // 243: if default_value.is_defined:
  // 244:   !message(-1) ' '
  // 245:   append &message "(default value: @(default_value))"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__check_arguments_24;
}
static void entry__check_arguments_17(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // message: 0
  // default_value: 1
  frame->slots[0] = myself->closure.frame->slots[4]; /* message */
  frame->slots[1] = myself->closure.frame->slots[6]; /* default_value */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 244: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__check_arguments_18;
}
static void cont__check_arguments_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 244: !message(-1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = character__32;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* message */;
  func = myself->type;
  frame->cont = cont__check_arguments_19;
}
static void cont__check_arguments_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* message */ = arguments->slots[0];
  // 245: ... "(default value: @(default_value))"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__7f5cac89d5ba4088;
  arguments->slots[1] = frame->slots[1] /* default_value */;
  arguments->slots[2] = string__578a5af303e9cc8;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__check_arguments_22;
}
static void cont__check_arguments_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 245: append &message "(default value: @(default_value))"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* message */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__check_arguments_23;
}
static void cont__check_arguments_23(void) {
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
static void cont__check_arguments_24(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 246: -> message
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* message */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__check_arguments_25(void) {
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
  // 251:   case kinds(idx)
  // 252:     OPTIONAL_PARAMETER:
  // 253:       push &buf '?'
  // 254:     SOME_PARAMETERS:
  // 255:       push &buf '*'
  // 256:     MANY_PARAMETERS:
  // 257:       push &buf '+'
  // 258:   -> buf
  frame->slots[8] /* temp__1 */ = create_closure(entry__check_arguments_26, 2);
  // 249: $parameter_name: (parameter idx)
  // 250:   $$buf parameter.to_upper_case
  // 251:   case kinds(idx)
  // 252:     OPTIONAL_PARAMETER:
  // 253:       push &buf '?'
  // 254:     SOME_PARAMETERS:
  // 255:       push &buf '*'
  // 256:     MANY_PARAMETERS:
  // 257:       push &buf '+'
  // 258:   -> buf
  initialize_future(frame->slots[7] /* parameter_name */, frame->slots[8] /* temp__1 */);
  // 260: ... program_version.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._program_version;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__check_arguments_36;
}
static void entry__check_arguments_26(void) {
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
  frame->cont = cont__check_arguments_27;
}
static void cont__check_arguments_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* buf */ = arguments->slots[0];
  // 251: ... kinds(idx)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* idx */;
  result_count = 1;
  myself = ((CELL *)frame->slots[2])->contents /* kinds */;
  func = myself->type;
  frame->cont = cont__check_arguments_28;
}
static void cont__check_arguments_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 252: ... :
  // 253:   push &buf '?'
  frame->slots[5] /* temp__2 */ = create_closure(entry__check_arguments_29, 0);
  // 254: ... :
  // 255:   push &buf '*'
  frame->slots[6] /* temp__3 */ = create_closure(entry__check_arguments_31, 0);
  // 256: ... :
  // 257:   push &buf '+'
  frame->slots[7] /* temp__4 */ = create_closure(entry__check_arguments_33, 0);
  // 251: case kinds(idx)
  // 252:   OPTIONAL_PARAMETER:
  // 253:     push &buf '?'
  // 254:   SOME_PARAMETERS:
  // 255:     push &buf '*'
  // 256:   MANY_PARAMETERS:
  // 257:     push &buf '+'
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
  frame->cont = cont__check_arguments_35;
}
static void entry__check_arguments_29(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // buf: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* buf */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 253: push &buf '?'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* buf */;
  arguments->slots[1] = character__63;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__check_arguments_30;
}
static void cont__check_arguments_30(void) {
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
static void entry__check_arguments_31(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // buf: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* buf */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 255: push &buf '*'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* buf */;
  arguments->slots[1] = character__42;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__check_arguments_32;
}
static void cont__check_arguments_32(void) {
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
static void entry__check_arguments_33(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // buf: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* buf */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 257: push &buf '+'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* buf */;
  arguments->slots[1] = character__43;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__check_arguments_34;
}
static void cont__check_arguments_34(void) {
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
static void cont__check_arguments_35(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 258: -> buf
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* buf */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__check_arguments_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__1 */ = arguments->slots[0];
  // 260: ... : show_version command_name
  frame->slots[9] /* temp__2 */ = create_closure(entry__check_arguments_37, 0);
  // 260: if program_version.is_defined: show_version command_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__1 */;
  arguments->slots[1] = frame->slots[9] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__check_arguments_38;
}
static void entry__check_arguments_37(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // command_name: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* command_name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 260: ... show_version command_name
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* command_name */;
  result_count = frame->caller_result_count;
  myself = var._show_version;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__check_arguments_38(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 261: ... command_id.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._command_id;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__check_arguments_39;
}
static void cont__check_arguments_39(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__1 */ = arguments->slots[0];
  // 261: ... :
  // 262:   ewriteln command_name ' ' command
  // 263:   ewriteln indented(2 command_descriptions(command_id))
  frame->slots[9] /* temp__2 */ = create_closure(entry__check_arguments_40, 0);
  // 261: if command_id.is_defined:
  // 262:   ewriteln command_name ' ' command
  // 263:   ewriteln indented(2 command_descriptions(command_id))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__1 */;
  arguments->slots[1] = frame->slots[9] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__check_arguments_44;
}
static void entry__check_arguments_40(void) {
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
  // 262: ewriteln command_name ' ' command
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* command_name */;
  arguments->slots[1] = character__32;
  arguments->slots[2] = frame->slots[1] /* command */;
  result_count = 0;
  myself = get__ewriteln();
  func = myself->type;
  frame->cont = cont__check_arguments_41;
}
static void cont__check_arguments_41(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 263: ... command_descriptions(command_id)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._command_id;
  result_count = 1;
  myself = var._command_descriptions;
  func = myself->type;
  frame->cont = cont__check_arguments_42;
}
static void cont__check_arguments_42(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 263: ... indented(2 command_descriptions(command_id))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__2;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__indented();
  func = myself->type;
  frame->cont = cont__check_arguments_43;
}
static void cont__check_arguments_43(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 263: ewriteln indented(2 command_descriptions(command_id))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__check_arguments_44(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 264: ewriteln "Usage:"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__5a1f579a019362ed;
  result_count = 0;
  myself = get__ewriteln();
  func = myself->type;
  frame->cont = cont__check_arguments_46;
}
static void cont__check_arguments_46(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 265: ... command.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* command */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__check_arguments_47;
}
static void cont__check_arguments_47(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__1 */ = arguments->slots[0];
  // 265: ... :
  // 266:   if program_copyright.is_defined: ewriteln "  " command_name " --copyright"
  // 267:   ewriteln "  " command_name " --help"
  frame->slots[9] /* temp__2 */ = create_closure(entry__check_arguments_48, 0);
  // 265: unless command.is_defined:
  // 266:   if program_copyright.is_defined: ewriteln "  " command_name " --copyright"
  // 267:   ewriteln "  " command_name " --help"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__1 */;
  arguments->slots[1] = frame->slots[9] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__check_arguments_54;
}
static void entry__check_arguments_48(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // command_name: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* command_name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 266: ... program_copyright.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._program_copyright;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__check_arguments_49;
}
static void cont__check_arguments_49(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 266: ... : ewriteln "  " command_name " --copyright"
  frame->slots[2] /* temp__2 */ = create_closure(entry__check_arguments_50, 0);
  // 266: if program_copyright.is_defined: ewriteln "  " command_name " --copyright"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__check_arguments_52;
}
static void entry__check_arguments_50(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // command_name: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* command_name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 266: ... ewriteln "  " command_name " --copyright"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e6082be5;
  arguments->slots[1] = frame->slots[0] /* command_name */;
  arguments->slots[2] = string__d89f1181d9c5276e;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__check_arguments_52(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 267: ewriteln "  " command_name " --help"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e6082be5;
  arguments->slots[1] = frame->slots[0] /* command_name */;
  arguments->slots[2] = string__a3040cb415de108a;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__check_arguments_54(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 272: command.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* command */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__check_arguments_55;
}
static void cont__check_arguments_55(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__2 */ = arguments->slots[0];
  // 273: -> string(' ' command)
  frame->slots[10] /* temp__3 */ = create_closure(entry__check_arguments_56, 0);
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__2 */;
  arguments->slots[1] = frame->slots[10] /* temp__3 */;
  arguments->slots[2] = func__check_arguments_58;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__check_arguments_59;
}
static void entry__check_arguments_56(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // command: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* command */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 273: ... string(' ' command)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__32;
  arguments->slots[1] = frame->slots[0] /* command */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__check_arguments_57;
}
static void cont__check_arguments_57(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 273: -> string(' ' command)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__check_arguments_58(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 274: -> ""
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = empty_string;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__check_arguments_59(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__1 */ = arguments->slots[0];
  // 268: ewrite
  // 269:   "  "
  // 270:   command_name
  // 271:   if
  // 272:     command.is_defined
  // 273:     -> string(' ' command)
  // 274:     -> ""
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e6082be5;
  arguments->slots[1] = frame->slots[1] /* command_name */;
  arguments->slots[2] = frame->slots[8] /* temp__1 */;
  result_count = 0;
  myself = get__ewrite();
  func = myself->type;
  frame->cont = cont__check_arguments_60;
}
static void cont__check_arguments_60(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 275: ... : (parameter idx)
  // 276:   ewrite " " parameter_name(parameter idx)
  frame->slots[8] /* temp__1 */ = create_closure(entry__check_arguments_61, 2);
  // 275: for_each parameters: (parameter idx)
  // 276:   ewrite " " parameter_name(parameter idx)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* parameters */;
  arguments->slots[1] = frame->slots[8] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__check_arguments_63;
}
static void entry__check_arguments_61(void) {
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
  // 276: ... parameter_name(parameter idx)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* parameter */;
  arguments->slots[1] = frame->slots[1] /* idx */;
  result_count = 1;
  myself = frame->slots[2] /* parameter_name */;
  func = myself->type;
  frame->cont = cont__check_arguments_62;
}
static void cont__check_arguments_62(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 276: ewrite " " parameter_name(parameter idx)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__578a5af303e9cc1;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__ewrite();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__check_arguments_63(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 277: ewriteln
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = get__ewriteln();
  func = myself->type;
  frame->cont = cont__check_arguments_64;
}
static void cont__check_arguments_64(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 278: ewrite "
  // 279:   
  // 280:   Parameters:
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__a67e424a37fc0741;
  result_count = 0;
  myself = get__ewrite();
  func = myself->type;
  frame->cont = cont__check_arguments_66;
}
static void cont__check_arguments_66(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 281: ... :
  // 282:   $$tab empty_list
  // 283:   for_each parameters: (parameter idx)
  // 284:     push &tab list(parameter_name(parameter idx) help_message(idx))
  // 285:   display_table tab
  frame->slots[8] /* temp__1 */ = create_closure(entry__check_arguments_67, 0);
  // 281: do:
  // 282:   $$tab empty_list
  // 283:   for_each parameters: (parameter idx)
  // 284:     push &tab list(parameter_name(parameter idx) help_message(idx))
  // 285:   display_table tab
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__1 */;
  result_count = 0;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__check_arguments_74;
}
static void entry__check_arguments_67(void) {
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
  // 282: $$tab empty_list
  ((CELL *)frame->slots[3])->contents /* tab */ = get__empty_list();
  // 283: ... : (parameter idx)
  // 284:   push &tab list(parameter_name(parameter idx) help_message(idx))
  frame->slots[4] /* temp__1 */ = create_closure(entry__check_arguments_68, 2);
  // 283: for_each parameters: (parameter idx)
  // 284:   push &tab list(parameter_name(parameter idx) help_message(idx))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* parameters */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__check_arguments_73;
}
static void entry__check_arguments_68(void) {
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
  // 284: ... parameter_name(parameter idx)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* parameter */;
  arguments->slots[1] = frame->slots[1] /* idx */;
  result_count = 1;
  myself = frame->slots[3] /* parameter_name */;
  func = myself->type;
  frame->cont = cont__check_arguments_69;
}
static void cont__check_arguments_69(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 284: ... help_message(idx)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* idx */;
  result_count = 1;
  myself = frame->slots[4] /* help_message */;
  func = myself->type;
  frame->cont = cont__check_arguments_70;
}
static void cont__check_arguments_70(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__3 */ = arguments->slots[0];
  // 284: ... list(parameter_name(parameter idx) help_message(idx))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__check_arguments_71;
}
static void cont__check_arguments_71(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 284: push &tab list(parameter_name(parameter idx) help_message(idx))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* tab */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__check_arguments_72;
}
static void cont__check_arguments_72(void) {
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
static void cont__check_arguments_73(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 285: display_table tab
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* tab */;
  result_count = frame->caller_result_count;
  myself = var._display_table;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__check_arguments_74(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 286: ... options.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[5])->contents /* options */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__check_arguments_75;
}
static void cont__check_arguments_75(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__1 */ = arguments->slots[0];
  // 286: ... :
  // 287:   ewrite "
  // 288:     
  // 289:     Options:
  // 290:   do:
  // 291:     $$tab empty_list
  // 292:     for_each options: (option idx)
  // 293:       $option_name:
  // 294:         $$buf string("--" option)
  // 295:         case kinds(idx)
  // ...
  frame->slots[9] /* temp__2 */ = create_closure(entry__check_arguments_76, 0);
  // 286: unless options.is_empty:
  // 287:   ewrite "
  // 288:     
  // 289:     Options:
  // 290:   do:
  // 291:     $$tab empty_list
  // 292:     for_each options: (option idx)
  // 293:       $option_name:
  // 294:         $$buf string("--" option)
  // 295:         case kinds(idx)
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
static void entry__check_arguments_97(void) {
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
  // 307: command.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* command */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__check_arguments_98;
}
static void cont__check_arguments_98(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 307: ... :
  // 308:   ewriteln "
  // 309:     Too few arguments for @(command)-command!
  frame->slots[3] /* temp__2 */ = create_closure(entry__check_arguments_99, 0);
  // 306: if
  // 307:   command.is_defined:
  // 308:     ewriteln "
  // 309:       Too few arguments for @(command)-command!
  // 310:   :
  // 311:     ewriteln "
  // 312:       Too few arguments!
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  arguments->slots[2] = func__check_arguments_103;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__check_arguments_105;
}
static void entry__check_arguments_99(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // command: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* command */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 308: ... "
  // 309:   Too few arguments for @(command)-command!
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__1fe132c840060c77;
  arguments->slots[1] = frame->slots[0] /* command */;
  arguments->slots[2] = string__2952791d2723646b;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__check_arguments_102;
}
static void cont__check_arguments_102(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 308: ewriteln "
  // 309:   Too few arguments for @(command)-command!
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__check_arguments_103(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 311: ewriteln "
  // 312:   Too few arguments!
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__f0948421cb0e2be3;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__check_arguments_105(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 313: show_usage
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = frame->slots[1] /* show_usage */;
  func = myself->type;
  frame->cont = cont__check_arguments_106;
}
static void cont__check_arguments_106(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 314: exit 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = frame->caller_result_count;
  myself = get__exit();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__check_arguments_107(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // show_usage: 0
  frame->slots[0] = myself->closure.frame->slots[14]; /* show_usage */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 317: ewriteln "
  // 318:   Too many arguments!
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__e3aee165acc437aa;
  result_count = 0;
  myself = get__ewriteln();
  func = myself->type;
  frame->cont = cont__check_arguments_109;
}
static void cont__check_arguments_109(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 319: show_usage
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = frame->slots[0] /* show_usage */;
  func = myself->type;
  frame->cont = cont__check_arguments_110;
}
static void cont__check_arguments_110(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 320: exit 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = frame->caller_result_count;
  myself = get__exit();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__check_arguments_111(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[18] /* temp__1 */ = arguments->slots[0];
  // 232: $command_name truncate_until(program_name '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__program_name();
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[18] /* temp__1 */;
  result_count = 1;
  myself = get__truncate_until();
  func = myself->type;
  frame->cont = cont__check_arguments_112;
}
static void cont__check_arguments_112(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[12] /* command_name */, arguments->slots[0]);
  // 233: map &arguments from_utf8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* arguments */;
  arguments->slots[1] = get__from_utf8();
  result_count = 1;
  myself = get__map();
  func = myself->type;
  frame->cont = cont__check_arguments_113;
}
static void cont__check_arguments_113(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* arguments */ = arguments->slots[0];
  // 322: ... : (idx template)
  // 323:   template $$option $name? $default_value? $conversion? $help
  // 324:   if
  // 325:     option.is_a_key_value_pair:
  // 326:       push &possible_values value_of(option)
  // 327:       !option key_of(option)
  // 328:     :
  // 329:       push &possible_values undefined
  // 330:   push
  // 331:     &names
  // ...
  frame->slots[18] /* temp__1 */ = create_closure(entry__check_arguments_114, 2);
  // 322: for_each templates: (idx template)
  // 323:   template $$option $name? $default_value? $conversion? $help
  // 324:   if
  // 325:     option.is_a_key_value_pair:
  // 326:       push &possible_values value_of(option)
  // 327:       !option key_of(option)
  // 328:     :
  // 329:       push &possible_values undefined
  // 330:   push
  // 331:     &names
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* templates */;
  arguments->slots[1] = frame->slots[18] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__check_arguments_160;
}
static void entry__check_arguments_154(void) {
  allocate_initialized_frame_gc(4, 4);
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
  // 352: push &results empty_list
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* results */;
  arguments->slots[1] = get__empty_list();
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__check_arguments_155;
}
static void cont__check_arguments_155(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* results */ = arguments->slots[0];
  // 353: !parameters(name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* name */;
  arguments->slots[1] = frame->slots[3] /* idx */;
  result_count = 1;
  myself = ((CELL *)frame->slots[1])->contents /* parameters */;
  func = myself->type;
  frame->cont = cont__check_arguments_156;
}
static void cont__check_arguments_156(void) {
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
static void entry__check_arguments_146(void) {
  allocate_initialized_frame_gc(4, 4);
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
  // 349: push &results empty_list
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* results */;
  arguments->slots[1] = get__empty_list();
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__check_arguments_147;
}
static void cont__check_arguments_147(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* results */ = arguments->slots[0];
  // 350: !options(name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* name */;
  arguments->slots[1] = frame->slots[3] /* idx */;
  result_count = 1;
  myself = ((CELL *)frame->slots[1])->contents /* options */;
  func = myself->type;
  frame->cont = cont__check_arguments_148;
}
static void cont__check_arguments_148(void) {
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
static void entry__check_arguments_141(void) {
  allocate_initialized_frame_gc(4, 4);
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
  // 346: push &results undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* results */;
  arguments->slots[1] = get__undefined();
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__check_arguments_142;
}
static void cont__check_arguments_142(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* results */ = arguments->slots[0];
  // 347: !options(name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* name */;
  arguments->slots[1] = frame->slots[3] /* idx */;
  result_count = 1;
  myself = ((CELL *)frame->slots[1])->contents /* options */;
  func = myself->type;
  frame->cont = cont__check_arguments_143;
}
static void cont__check_arguments_143(void) {
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
static void entry__check_arguments_135(void) {
  allocate_initialized_frame_gc(5, 5);
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
  // 342: push &results false
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* results */;
  arguments->slots[1] = get__false();
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__check_arguments_136;
}
static void cont__check_arguments_136(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* results */ = arguments->slots[0];
  // 343: !options(option)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* option */;
  arguments->slots[1] = frame->slots[3] /* idx */;
  result_count = 1;
  myself = ((CELL *)frame->slots[1])->contents /* options */;
  func = myself->type;
  frame->cont = cont__check_arguments_137;
}
static void cont__check_arguments_137(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* options */ = arguments->slots[0];
  // 344: !kinds(idx)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* idx */;
  arguments->slots[1] = var._BOOLEAN_OPTION;
  result_count = 1;
  myself = ((CELL *)frame->slots[4])->contents /* kinds */;
  func = myself->type;
  frame->cont = cont__check_arguments_138;
}
static void cont__check_arguments_138(void) {
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
static void entry__check_arguments_133(void) {
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
  // 341: ... option.is_a_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* option */;
  result_count = 1;
  myself = get__is_a_string();
  func = myself->type;
  frame->cont = cont__check_arguments_134;
}
static void cont__check_arguments_134(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 341: ... :
  // 342:   push &results false
  // 343:   !options(option) idx
  // 344:   !kinds(idx) BOOLEAN_OPTION
  frame->slots[6] /* temp__2 */ = create_closure(entry__check_arguments_135, 0);
  // 341: -> option.is_a_string:
  // 342:   push &results false
  // 343:   !options(option) idx
  // 344:   !kinds(idx) BOOLEAN_OPTION
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__check_arguments_139(void) {
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
  // 345: ... option == VALUED_OPTION
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* option */;
  arguments->slots[1] = get__VALUED_OPTION();
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__check_arguments_140;
}
static void cont__check_arguments_140(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 345: ... :
  // 346:   push &results undefined
  // 347:   !options(name) idx
  frame->slots[6] /* temp__2 */ = create_closure(entry__check_arguments_141, 0);
  // 345: -> option == VALUED_OPTION:
  // 346:   push &results undefined
  // 347:   !options(name) idx
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__check_arguments_144(void) {
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
  // 348: ... option == MULTI_VALUED_OPTION
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* option */;
  arguments->slots[1] = get__MULTI_VALUED_OPTION();
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__check_arguments_145;
}
static void cont__check_arguments_145(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 348: ... :
  // 349:   push &results empty_list
  // 350:   !options(name) idx
  frame->slots[6] /* temp__2 */ = create_closure(entry__check_arguments_146, 0);
  // 348: -> option == MULTI_VALUED_OPTION:
  // 349:   push &results empty_list
  // 350:   !options(name) idx
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__check_arguments_149(void) {
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
  // 351: ... option == SOME_PARAMETERS
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* option */;
  arguments->slots[1] = get__SOME_PARAMETERS();
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__check_arguments_150;
}
static void cont__check_arguments_150(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 351: ... option == MANY_PARAMETERS
  frame->slots[7] /* temp__3 */ = create_closure(entry__check_arguments_151, 0);
  // 351: ... option == SOME_PARAMETERS || option == MANY_PARAMETERS
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__check_arguments_153;
}
static void entry__check_arguments_151(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // option: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* option */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 351: ... option == MANY_PARAMETERS
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* option */;
  arguments->slots[1] = get__MANY_PARAMETERS();
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__check_arguments_152;
}
static void cont__check_arguments_152(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 351: ... option == MANY_PARAMETERS
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__check_arguments_153(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 351: ... :
  // 352:   push &results empty_list
  // 353:   !parameters(name) idx
  frame->slots[8] /* temp__4 */ = create_closure(entry__check_arguments_154, 0);
  // 351: -> option == SOME_PARAMETERS || option == MANY_PARAMETERS:
  // 352:   push &results empty_list
  // 353:   !parameters(name) idx
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__4 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__check_arguments_157(void) {
  allocate_initialized_frame_gc(4, 4);
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
  // 355: push &results undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* results */;
  arguments->slots[1] = get__undefined();
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__check_arguments_158;
}
static void cont__check_arguments_158(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* results */ = arguments->slots[0];
  // 356: !parameters(name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* name */;
  arguments->slots[1] = frame->slots[3] /* idx */;
  result_count = 1;
  myself = ((CELL *)frame->slots[1])->contents /* parameters */;
  func = myself->type;
  frame->cont = cont__check_arguments_159;
}
static void cont__check_arguments_159(void) {
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
static void entry__check_arguments_114(void) {
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
  // 323: template $$option $name? $default_value? $conversion? $help
  argument_count = 0;
  arguments = node_p;
  result_count = -1;
  myself = frame->slots[1] /* template */;
  func = myself->type;
  frame->cont = cont__check_arguments_115;
}
static void cont__check_arguments_115(void) {
  if (argument_count < 2) {
    too_few_results_error();
    return;
  }
  if (argument_count > 5) {
    too_many_results_error();
    return;
  }
  ((CELL *)frame->slots[11])->contents /* option */ = arguments->slots[0];
  initialize_future(frame->slots[15] /* help */, arguments->slots[argument_count-1]);
  switch(argument_count) {
    default: initialize_future(frame->slots[14] /* conversion */, arguments->slots[3]);
    case 4: initialize_future(frame->slots[13] /* default_value */, arguments->slots[2]);
    case 3: initialize_future(frame->slots[12] /* name */, arguments->slots[1]);
    case 2:;
  }
  switch(argument_count) {
    case 2: initialize_future(frame->slots[12] /* name */, undefined);
    case 3: initialize_future(frame->slots[13] /* default_value */, undefined);
    case 4: initialize_future(frame->slots[14] /* conversion */, undefined);
  }
  // 325: option.is_a_key_value_pair
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[11])->contents /* option */;
  result_count = 1;
  myself = get__is_a_key_value_pair();
  func = myself->type;
  frame->cont = cont__check_arguments_116;
}
static void cont__check_arguments_116(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[16] /* temp__1 */ = arguments->slots[0];
  // 325: ... :
  // 326:   push &possible_values value_of(option)
  // 327:   !option key_of(option)
  frame->slots[17] /* temp__2 */ = create_closure(entry__check_arguments_117, 0);
  // 328: :
  // 329:   push &possible_values undefined
  frame->slots[18] /* temp__3 */ = create_closure(entry__check_arguments_121, 0);
  // 324: if
  // 325:   option.is_a_key_value_pair:
  // 326:     push &possible_values value_of(option)
  // 327:     !option key_of(option)
  // 328:   :
  // 329:     push &possible_values undefined
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[16] /* temp__1 */;
  arguments->slots[1] = frame->slots[17] /* temp__2 */;
  arguments->slots[2] = frame->slots[18] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__check_arguments_123;
}
static void entry__check_arguments_117(void) {
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
  // 326: ... value_of(option)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* option */;
  result_count = 1;
  myself = get__value_of();
  func = myself->type;
  frame->cont = cont__check_arguments_118;
}
static void cont__check_arguments_118(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 326: push &possible_values value_of(option)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* possible_values */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__check_arguments_119;
}
static void cont__check_arguments_119(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* possible_values */ = arguments->slots[0];
  // 327: !option key_of(option)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* option */;
  result_count = 1;
  myself = get__key_of();
  func = myself->type;
  frame->cont = cont__check_arguments_120;
}
static void cont__check_arguments_120(void) {
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
static void entry__check_arguments_121(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // possible_values: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* possible_values */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 329: push &possible_values undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* possible_values */;
  arguments->slots[1] = get__undefined();
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__check_arguments_122;
}
static void cont__check_arguments_122(void) {
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
static void cont__check_arguments_123(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 333: name.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[12] /* name */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__check_arguments_124;
}
static void cont__check_arguments_124(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[17] /* temp__2 */ = arguments->slots[0];
  // 334: -> name
  frame->slots[18] /* temp__3 */ = create_closure(entry__check_arguments_125, 0);
  // 335: -> option
  frame->slots[19] /* temp__4 */ = create_closure(entry__check_arguments_126, 0);
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[17] /* temp__2 */;
  arguments->slots[1] = frame->slots[18] /* temp__3 */;
  arguments->slots[2] = frame->slots[19] /* temp__4 */;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__check_arguments_127;
}
static void entry__check_arguments_125(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[12]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 334: -> name
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__check_arguments_126(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // option: 0
  frame->slots[0] = myself->closure.frame->slots[11]; /* option */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 335: -> option
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* option */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__check_arguments_127(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[16] /* temp__1 */ = arguments->slots[0];
  // 330: push
  // 331:   &names
  // 332:   if
  // 333:     name.is_defined
  // 334:     -> name
  // 335:     -> option
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* names */;
  arguments->slots[1] = frame->slots[16] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__check_arguments_128;
}
static void cont__check_arguments_128(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* names */ = arguments->slots[0];
  // 336: push &kinds option
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* kinds */;
  arguments->slots[1] = ((CELL *)frame->slots[11])->contents /* option */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__check_arguments_129;
}
static void cont__check_arguments_129(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[4])->contents /* kinds */ = arguments->slots[0];
  // 337: push &default_values default_value
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[5])->contents /* default_values */;
  arguments->slots[1] = frame->slots[13] /* default_value */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__check_arguments_130;
}
static void cont__check_arguments_130(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[5])->contents /* default_values */ = arguments->slots[0];
  // 338: push &conversions conversion
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[6])->contents /* conversions */;
  arguments->slots[1] = frame->slots[14] /* conversion */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__check_arguments_131;
}
static void cont__check_arguments_131(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[6])->contents /* conversions */ = arguments->slots[0];
  // 339: push &help_messages help
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[7])->contents /* help_messages */;
  arguments->slots[1] = frame->slots[15] /* help */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__check_arguments_132;
}
static void cont__check_arguments_132(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[7])->contents /* help_messages */ = arguments->slots[0];
  // 341: -> option.is_a_string:
  // 342:   push &results false
  // 343:   !options(option) idx
  // 344:   !kinds(idx) BOOLEAN_OPTION
  frame->slots[16] /* temp__1 */ = create_closure(entry__check_arguments_133, 0);
  // 345: -> option == VALUED_OPTION:
  // 346:   push &results undefined
  // 347:   !options(name) idx
  frame->slots[17] /* temp__2 */ = create_closure(entry__check_arguments_139, 0);
  // 348: -> option == MULTI_VALUED_OPTION:
  // 349:   push &results empty_list
  // 350:   !options(name) idx
  frame->slots[18] /* temp__3 */ = create_closure(entry__check_arguments_144, 0);
  // 351: -> option == SOME_PARAMETERS || option == MANY_PARAMETERS:
  // 352:   push &results empty_list
  // 353:   !parameters(name) idx
  frame->slots[19] /* temp__4 */ = create_closure(entry__check_arguments_149, 0);
  // 354: :
  // 355:   push &results undefined
  // 356:   !parameters(name) idx
  frame->slots[20] /* temp__5 */ = create_closure(entry__check_arguments_157, 0);
  // 340: cond
  // 341:   -> option.is_a_string:
  // 342:     push &results false
  // 343:     !options(option) idx
  // 344:     !kinds(idx) BOOLEAN_OPTION
  // 345:   -> option == VALUED_OPTION:
  // 346:     push &results undefined
  // 347:     !options(name) idx
  // 348:   -> option == MULTI_VALUED_OPTION:
  // 349:     push &results empty_list
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
static void cont__check_arguments_160(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 357: ... length_of(arguments)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* arguments */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__check_arguments_161;
}
static void cont__check_arguments_161(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[20] /* temp__3 */ = arguments->slots[0];
  // 357: ... length_of(arguments) >= 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[20] /* temp__3 */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__check_arguments_162;
}
static void cont__check_arguments_162(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[19] /* temp__2 */ = arguments->slots[0];
  // 357: ... length_of(arguments) >= 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[19] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__check_arguments_163;
}
static void cont__check_arguments_163(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[18] /* temp__1 */ = arguments->slots[0];
  // 357: ... :
  // 358:   if arguments(1) == "--help":
  // 359:     show_usage
  // 360:     terminate
  // 361:   if program_copyright.is_defined && arguments(1) == "--copyright":
  // 362:     show_copyright
  // 363:     terminate
  // 364:   if program_version.is_defined && arguments(1) == "--version":
  // 365:     show_version command_name
  // 366:     terminate
  frame->slots[21] /* temp__4 */ = create_closure(entry__check_arguments_164, 0);
  // 357: if length_of(arguments) >= 1:
  // 358:   if arguments(1) == "--help":
  // 359:     show_usage
  // 360:     terminate
  // 361:   if program_copyright.is_defined && arguments(1) == "--copyright":
  // 362:     show_copyright
  // 363:     terminate
  // 364:   if program_version.is_defined && arguments(1) == "--version":
  // 365:     show_version command_name
  // 366:     terminate
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[18] /* temp__1 */;
  arguments->slots[1] = frame->slots[21] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__check_arguments_188;
}
static void entry__check_arguments_186(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // command_name: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* command_name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 365: show_version command_name
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* command_name */;
  result_count = 0;
  myself = var._show_version;
  func = myself->type;
  frame->cont = cont__check_arguments_187;
}
static void cont__check_arguments_187(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 366: terminate
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = get__terminate();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__check_arguments_164(void) {
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
  // 358: ... arguments(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* arguments */;
  func = myself->type;
  frame->cont = cont__check_arguments_165;
}
static void cont__check_arguments_165(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 358: ... arguments(1) == "--help"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = string__481f572601de82a7;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__check_arguments_167;
}
static void cont__check_arguments_167(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 358: ... :
  // 359:   show_usage
  // 360:   terminate
  frame->slots[5] /* temp__3 */ = create_closure(entry__check_arguments_168, 0);
  // 358: if arguments(1) == "--help":
  // 359:   show_usage
  // 360:   terminate
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__check_arguments_170;
}
static void entry__check_arguments_168(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // show_usage: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* show_usage */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 359: show_usage
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = frame->slots[0] /* show_usage */;
  func = myself->type;
  frame->cont = cont__check_arguments_169;
}
static void cont__check_arguments_169(void) {
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
static void cont__check_arguments_170(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 361: ... program_copyright.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._program_copyright;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__check_arguments_171;
}
static void cont__check_arguments_171(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 361: ... arguments(1) == "--copyright"
  frame->slots[5] /* temp__3 */ = create_closure(entry__check_arguments_172, 0);
  // 361: ... program_copyright.is_defined && arguments(1) == "--copyright"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__check_arguments_176;
}
static void entry__check_arguments_172(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // arguments: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* arguments */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 361: ... arguments(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* arguments */;
  func = myself->type;
  frame->cont = cont__check_arguments_173;
}
static void cont__check_arguments_173(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 361: ... arguments(1) == "--copyright"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = string__d29f58972c488aa7;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__check_arguments_175;
}
static void cont__check_arguments_175(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 361: ... arguments(1) == "--copyright"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__check_arguments_176(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 361: if program_copyright.is_defined && arguments(1) == "--copyright":
  // 362:   show_copyright
  // 363:   terminate
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = func__check_arguments_177;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__check_arguments_179;
}
static void entry__check_arguments_177(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 362: show_copyright
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = var._show_copyright;
  func = myself->type;
  frame->cont = cont__check_arguments_178;
}
static void cont__check_arguments_178(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 363: terminate
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = get__terminate();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__check_arguments_179(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 364: ... program_version.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._program_version;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__check_arguments_180;
}
static void cont__check_arguments_180(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 364: ... arguments(1) == "--version"
  frame->slots[5] /* temp__3 */ = create_closure(entry__check_arguments_181, 0);
  // 364: ... program_version.is_defined && arguments(1) == "--version"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__check_arguments_185;
}
static void entry__check_arguments_181(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // arguments: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* arguments */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 364: ... arguments(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* arguments */;
  func = myself->type;
  frame->cont = cont__check_arguments_182;
}
static void cont__check_arguments_182(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 364: ... arguments(1) == "--version"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = string__48e824ee4f7a5d6b;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__check_arguments_184;
}
static void cont__check_arguments_184(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 364: ... arguments(1) == "--version"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__check_arguments_185(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 364: ... :
  // 365:   show_version command_name
  // 366:   terminate
  frame->slots[6] /* temp__4 */ = create_closure(entry__check_arguments_186, 0);
  // 364: if program_version.is_defined && arguments(1) == "--version":
  // 365:   show_version command_name
  // 366:   terminate
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__check_arguments_188(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 367: ... :
  // 368:   $$idx 1
  // 369:   $$fetch_option_value false
  // 370:   $$option_idx undefined
  // 371:   do: (-> break)
  // 372:     for_each arguments: (argument)
  // 373:       if argument == "--":
  // 374:         delete_at &arguments idx
  // 375:         break
  // 376:       if
  // ...
  frame->slots[18] /* temp__1 */ = create_closure(entry__check_arguments_189, 0);
  // 367: do:
  // 368:   $$idx 1
  // 369:   $$fetch_option_value false
  // 370:   $$option_idx undefined
  // 371:   do: (-> break)
  // 372:     for_each arguments: (argument)
  // 373:       if argument == "--":
  // 374:         delete_at &arguments idx
  // 375:         break
  // 376:       if
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[18] /* temp__1 */;
  result_count = 0;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__check_arguments_226;
}
static void entry__check_arguments_190(void) {
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
  // 372: ... : (argument)
  // 373:   if argument == "--":
  // 374:     delete_at &arguments idx
  // 375:     break
  // 376:   if
  // 377:     fetch_option_value:
  // 378:       !fetch_option_value false
  // 379:       delete_at &arguments idx
  // 380:       case kinds(option_idx)
  // 381:         VALUED_OPTION:
  // ...
  frame->slots[8] /* temp__1 */ = create_closure(entry__check_arguments_191, 1);
  // 372: for_each arguments: (argument)
  // 373:   if argument == "--":
  // 374:     delete_at &arguments idx
  // 375:     break
  // 376:   if
  // 377:     fetch_option_value:
  // 378:       !fetch_option_value false
  // 379:       delete_at &arguments idx
  // 380:       case kinds(option_idx)
  // 381:         VALUED_OPTION:
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* arguments */;
  arguments->slots[1] = frame->slots[8] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__check_arguments_225;
}
static void entry__check_arguments_207(void) {
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
  // 388: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__check_arguments_208;
}
static void cont__check_arguments_208(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__2 */ = arguments->slots[0];
  // 388: ... range(argument 3 -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* argument */;
  arguments->slots[1] = number__3;
  arguments->slots[2] = frame->slots[9] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__check_arguments_209;
}
static void cont__check_arguments_209(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__1 */ = arguments->slots[0];
  // 388: !option_idx options(range(argument 3 -1))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[1])->contents /* options */;
  func = myself->type;
  frame->cont = cont__check_arguments_210;
}
static void cont__check_arguments_210(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* option_idx */ = arguments->slots[0];
  // 389: ... option_idx.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* option_idx */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__check_arguments_211;
}
static void cont__check_arguments_211(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__1 */ = arguments->slots[0];
  // 389: ... : Error "Invalid option: @(argument)!"
  frame->slots[9] /* temp__2 */ = create_closure(entry__check_arguments_212, 0);
  // 389: if option_idx.is_undefined: Error "Invalid option: @(argument)!"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__1 */;
  arguments->slots[1] = frame->slots[9] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__check_arguments_215;
}
static void entry__check_arguments_212(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // argument: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* argument */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 389: ... "Invalid option: @(argument)!"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__42c4ee3f21a0316f;
  arguments->slots[1] = frame->slots[0] /* argument */;
  arguments->slots[2] = string__578a5af303e9cc0;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__check_arguments_214;
}
static void cont__check_arguments_214(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 389: ... Error "Invalid option: @(argument)!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__check_arguments_215(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 391: kinds(option_idx)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* option_idx */;
  result_count = 1;
  myself = ((CELL *)frame->slots[3])->contents /* kinds */;
  func = myself->type;
  frame->cont = cont__check_arguments_216;
}
static void cont__check_arguments_216(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__2 */ = arguments->slots[0];
  // 391: kinds(option_idx) == BOOLEAN_OPTION
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__2 */;
  arguments->slots[1] = var._BOOLEAN_OPTION;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__check_arguments_217;
}
static void cont__check_arguments_217(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__1 */ = arguments->slots[0];
  // 391: ... :
  // 392:   !results(option_idx) true
  frame->slots[10] /* temp__3 */ = create_closure(entry__check_arguments_218, 0);
  // 393: :
  // 394:   !fetch_option_value true
  frame->slots[11] /* temp__4 */ = create_closure(entry__check_arguments_220, 0);
  // 390: if
  // 391:   kinds(option_idx) == BOOLEAN_OPTION:
  // 392:     !results(option_idx) true
  // 393:   :
  // 394:     !fetch_option_value true
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__1 */;
  arguments->slots[1] = frame->slots[10] /* temp__3 */;
  arguments->slots[2] = frame->slots[11] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__check_arguments_221;
}
static void entry__check_arguments_218(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // results: 0
  // option_idx: 1
  frame->slots[0] = myself->closure.frame->slots[4]; /* results */
  frame->slots[1] = myself->closure.frame->slots[0]; /* option_idx */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 392: !results(option_idx)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* option_idx */;
  arguments->slots[1] = get__true();
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* results */;
  func = myself->type;
  frame->cont = cont__check_arguments_219;
}
static void cont__check_arguments_219(void) {
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
static void entry__check_arguments_220(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // fetch_option_value: 0
  frame->slots[0] = myself->closure.frame->slots[5]; /* fetch_option_value */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 394: !fetch_option_value true
  ((CELL *)frame->slots[0])->contents /* fetch_option_value */ = get__true();
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__check_arguments_221(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 395: delete_at &arguments idx
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[6])->contents /* arguments */;
  arguments->slots[1] = ((CELL *)frame->slots[7])->contents /* idx */;
  result_count = 1;
  myself = get__delete_at();
  func = myself->type;
  frame->cont = cont__check_arguments_222;
}
static void cont__check_arguments_222(void) {
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
static void entry__check_arguments_223(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // idx: 0
  frame->slots[0] = myself->closure.frame->slots[7]; /* idx */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 397: inc &idx
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* idx */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__check_arguments_224;
}
static void cont__check_arguments_224(void) {
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
static void entry__check_arguments_199(void) {
  allocate_initialized_frame_gc(3, 3);
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
  // 382: !results(option_idx)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* option_idx */;
  arguments->slots[1] = frame->slots[2] /* argument */;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* results */;
  func = myself->type;
  frame->cont = cont__check_arguments_200;
}
static void cont__check_arguments_200(void) {
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
static void entry__check_arguments_201(void) {
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
  // 384: ... results(option_idx)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* option_idx */;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* results */;
  func = myself->type;
  frame->cont = cont__check_arguments_202;
}
static void cont__check_arguments_202(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 384: push &results(option_idx) argument
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* argument */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__check_arguments_203;
}
static void cont__check_arguments_203(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 384: ... &results(option_idx)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* option_idx */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* results */;
  func = myself->type;
  frame->cont = cont__check_arguments_204;
}
static void cont__check_arguments_204(void) {
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
static void entry__check_arguments_196(void) {
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
  // 378: !fetch_option_value false
  ((CELL *)frame->slots[0])->contents /* fetch_option_value */ = get__false();
  // 379: delete_at &arguments idx
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* arguments */;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* idx */;
  result_count = 1;
  myself = get__delete_at();
  func = myself->type;
  frame->cont = cont__check_arguments_197;
}
static void cont__check_arguments_197(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* arguments */ = arguments->slots[0];
  // 380: ... kinds(option_idx)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* option_idx */;
  result_count = 1;
  myself = ((CELL *)frame->slots[3])->contents /* kinds */;
  func = myself->type;
  frame->cont = cont__check_arguments_198;
}
static void cont__check_arguments_198(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 381: ... :
  // 382:   !results(option_idx) argument
  frame->slots[8] /* temp__2 */ = create_closure(entry__check_arguments_199, 0);
  // 383: ... :
  // 384:   push &results(option_idx) argument
  frame->slots[9] /* temp__3 */ = create_closure(entry__check_arguments_201, 0);
  // 380: case kinds(option_idx)
  // 381:   VALUED_OPTION:
  // 382:     !results(option_idx) argument
  // 383:   MULTI_VALUED_OPTION:
  // 384:     push &results(option_idx) argument
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
static void entry__check_arguments_205(void) {
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
  // 387: argument .has_prefix. "--"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* argument */;
  arguments->slots[1] = string__2d7981f4e6602be8;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__check_arguments_206;
}
static void cont__check_arguments_206(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__1 */ = arguments->slots[0];
  // 387: ... :
  // 388:   !option_idx options(range(argument 3 -1))
  // 389:   if option_idx.is_undefined: Error "Invalid option: @(argument)!"
  // 390:   if
  // 391:     kinds(option_idx) == BOOLEAN_OPTION:
  // 392:       !results(option_idx) true
  // 393:     :
  // 394:       !fetch_option_value true
  // 395:   delete_at &arguments idx
  frame->slots[9] /* temp__2 */ = create_closure(entry__check_arguments_207, 0);
  // 396: :
  // 397:   inc &idx
  frame->slots[10] /* temp__3 */ = create_closure(entry__check_arguments_223, 0);
  // 386: if
  // 387:   argument .has_prefix. "--":
  // 388:     !option_idx options(range(argument 3 -1))
  // 389:     if option_idx.is_undefined: Error "Invalid option: @(argument)!"
  // 390:     if
  // 391:       kinds(option_idx) == BOOLEAN_OPTION:
  // 392:         !results(option_idx) true
  // 393:       :
  // 394:         !fetch_option_value true
  // 395:     delete_at &arguments idx
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
static void entry__check_arguments_191(void) {
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
  // 373: ... argument == "--"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* argument */;
  arguments->slots[1] = string__2d7981f4e6602be8;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__check_arguments_192;
}
static void cont__check_arguments_192(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  // 373: ... :
  // 374:   delete_at &arguments idx
  // 375:   break
  frame->slots[10] /* temp__2 */ = create_closure(entry__check_arguments_193, 0);
  // 373: if argument == "--":
  // 374:   delete_at &arguments idx
  // 375:   break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  arguments->slots[1] = frame->slots[10] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__check_arguments_195;
}
static void entry__check_arguments_193(void) {
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
  // 374: delete_at &arguments idx
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* arguments */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* idx */;
  result_count = 1;
  myself = get__delete_at();
  func = myself->type;
  frame->cont = cont__check_arguments_194;
}
static void cont__check_arguments_194(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* arguments */ = arguments->slots[0];
  // 375: break
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[2] /* break */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__check_arguments_195(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 377: ... :
  // 378:   !fetch_option_value false
  // 379:   delete_at &arguments idx
  // 380:   case kinds(option_idx)
  // 381:     VALUED_OPTION:
  // 382:       !results(option_idx) argument
  // 383:     MULTI_VALUED_OPTION:
  // 384:       push &results(option_idx) argument
  frame->slots[9] /* temp__1 */ = create_closure(entry__check_arguments_196, 0);
  // 385: :
  // 386:   if
  // 387:     argument .has_prefix. "--":
  // 388:       !option_idx options(range(argument 3 -1))
  // 389:       if option_idx.is_undefined: Error "Invalid option: @(argument)!"
  // 390:       if
  // 391:         kinds(option_idx) == BOOLEAN_OPTION:
  // 392:           !results(option_idx) true
  // 393:         :
  // 394:           !fetch_option_value true
  // ...
  frame->slots[10] /* temp__2 */ = create_closure(entry__check_arguments_205, 0);
  // 376: if
  // 377:   fetch_option_value:
  // 378:     !fetch_option_value false
  // 379:     delete_at &arguments idx
  // 380:     case kinds(option_idx)
  // 381:       VALUED_OPTION:
  // 382:         !results(option_idx) argument
  // 383:       MULTI_VALUED_OPTION:
  // 384:         push &results(option_idx) argument
  // 385:   :
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
static void cont__check_arguments_225(void) {
  myself = frame->slots[0] /* break */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__check_arguments_189(void) {
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
  // 368: $$idx 1
  ((CELL *)frame->slots[4])->contents /* idx */ = number__1;
  // 369: $$fetch_option_value false
  ((CELL *)frame->slots[5])->contents /* fetch_option_value */ = get__false();
  // 370: $$option_idx undefined
  ((CELL *)frame->slots[6])->contents /* option_idx */ = get__undefined();
  // 371: ... : (-> break)
  // 372:   for_each arguments: (argument)
  // 373:     if argument == "--":
  // 374:       delete_at &arguments idx
  // 375:       break
  // 376:     if
  // 377:       fetch_option_value:
  // 378:         !fetch_option_value false
  // 379:         delete_at &arguments idx
  // 380:         case kinds(option_idx)
  // ...
  frame->slots[7] /* temp__1 */ = create_closure(entry__check_arguments_190, 0);
  // 371: do: (-> break)
  // 372:   for_each arguments: (argument)
  // 373:     if argument == "--":
  // 374:       delete_at &arguments idx
  // 375:       break
  // 376:     if
  // 377:       fetch_option_value:
  // 378:         !fetch_option_value false
  // 379:         delete_at &arguments idx
  // 380:         case kinds(option_idx)
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__do();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__check_arguments_226(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 398: $$last_idx -1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__check_arguments_227;
}
static void cont__check_arguments_227(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[17])->contents /* last_idx */ = arguments->slots[0];
  // 399: ... : (-> break)
  // 400:   for_each_from_down_to templates -1 1: (idx template)
  // 401:     template $$option $_name? $_default_value? $_conversion? $_help
  // 402:     if option.is_a_key_value_pair: !option key_of(option)
  // 403:     case option
  // 404:       MANDATORY_PARAMETER:
  // 405:         if arguments.is_empty too_few_arguments_error
  // 406:         pop &arguments !results(idx)
  // 407:         !last_idx idx-1
  // 408:       OPTIONAL_PARAMETER, SOME_PARAMETERS, MANY_PARAMETERS:
  // ...
  frame->slots[18] /* temp__1 */ = create_closure(entry__check_arguments_228, 0);
  // 399: do: (-> break)
  // 400:   for_each_from_down_to templates -1 1: (idx template)
  // 401:     template $$option $_name? $_default_value? $_conversion? $_help
  // 402:     if option.is_a_key_value_pair: !option key_of(option)
  // 403:     case option
  // 404:       MANDATORY_PARAMETER:
  // 405:         if arguments.is_empty too_few_arguments_error
  // 406:         pop &arguments !results(idx)
  // 407:         !last_idx idx-1
  // 408:       OPTIONAL_PARAMETER, SOME_PARAMETERS, MANY_PARAMETERS:
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[18] /* temp__1 */;
  result_count = 0;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__check_arguments_245;
}
static void entry__check_arguments_228(void) {
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
  // 400: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__check_arguments_229;
}
static void cont__check_arguments_229(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 400: ... : (idx template)
  // 401:   template $$option $_name? $_default_value? $_conversion? $_help
  // 402:   if option.is_a_key_value_pair: !option key_of(option)
  // 403:   case option
  // 404:     MANDATORY_PARAMETER:
  // 405:       if arguments.is_empty too_few_arguments_error
  // 406:       pop &arguments !results(idx)
  // 407:       !last_idx idx-1
  // 408:     OPTIONAL_PARAMETER, SOME_PARAMETERS, MANY_PARAMETERS:
  // 409:       break
  frame->slots[7] /* temp__2 */ = create_closure(entry__check_arguments_230, 2);
  // 400: for_each_from_down_to templates -1 1: (idx template)
  // 401:   template $$option $_name? $_default_value? $_conversion? $_help
  // 402:   if option.is_a_key_value_pair: !option key_of(option)
  // 403:   case option
  // 404:     MANDATORY_PARAMETER:
  // 405:       if arguments.is_empty too_few_arguments_error
  // 406:       pop &arguments !results(idx)
  // 407:       !last_idx idx-1
  // 408:     OPTIONAL_PARAMETER, SOME_PARAMETERS, MANY_PARAMETERS:
  // 409:       break
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* templates */;
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  arguments->slots[2] = number__1;
  arguments->slots[3] = frame->slots[7] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__for_each_from_down_to();
  func = myself->type;
  frame->cont = cont__check_arguments_244;
}
static void entry__check_arguments_243(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // break: 0
  frame->slots[0] = myself->closure.frame->slots[6]; /* break */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 409: break
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* break */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__check_arguments_230(void) {
  allocate_initialized_frame_gc(7, 15);
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
  // 401: template $$option $_name? $_default_value? $_conversion? $_help
  argument_count = 0;
  arguments = node_p;
  result_count = -1;
  myself = frame->slots[1] /* template */;
  func = myself->type;
  frame->cont = cont__check_arguments_231;
}
static void cont__check_arguments_231(void) {
  if (argument_count < 2) {
    too_few_results_error();
    return;
  }
  if (argument_count > 5) {
    too_many_results_error();
    return;
  }
  ((CELL *)frame->slots[7])->contents /* option */ = arguments->slots[0];
  initialize_future(frame->slots[11] /* help */, arguments->slots[argument_count-1]);
  switch(argument_count) {
    default: initialize_future(frame->slots[10] /* conversion */, arguments->slots[3]);
    case 4: initialize_future(frame->slots[9] /* default_value */, arguments->slots[2]);
    case 3: initialize_future(frame->slots[8] /* name */, arguments->slots[1]);
    case 2:;
  }
  switch(argument_count) {
    case 2: initialize_future(frame->slots[8] /* name */, undefined);
    case 3: initialize_future(frame->slots[9] /* default_value */, undefined);
    case 4: initialize_future(frame->slots[10] /* conversion */, undefined);
  }
  // 402: ... option.is_a_key_value_pair
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[7])->contents /* option */;
  result_count = 1;
  myself = get__is_a_key_value_pair();
  func = myself->type;
  frame->cont = cont__check_arguments_232;
}
static void cont__check_arguments_232(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__1 */ = arguments->slots[0];
  // 402: ... : !option key_of(option)
  frame->slots[13] /* temp__2 */ = create_closure(entry__check_arguments_233, 0);
  // 402: if option.is_a_key_value_pair: !option key_of(option)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[12] /* temp__1 */;
  arguments->slots[1] = frame->slots[13] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__check_arguments_235;
}
static void entry__check_arguments_233(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // option: 0
  frame->slots[0] = myself->closure.frame->slots[7]; /* option */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 402: ... !option key_of(option)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* option */;
  result_count = 1;
  myself = get__key_of();
  func = myself->type;
  frame->cont = cont__check_arguments_234;
}
static void cont__check_arguments_234(void) {
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
static void cont__check_arguments_235(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 404: ... :
  // 405:   if arguments.is_empty too_few_arguments_error
  // 406:   pop &arguments !results(idx)
  // 407:   !last_idx idx-1
  frame->slots[12] /* temp__1 */ = create_closure(entry__check_arguments_236, 0);
  // 408: OPTIONAL_PARAMETER, SOME_PARAMETERS, MANY_PARAMETERS
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__OPTIONAL_PARAMETER();
  arguments->slots[1] = get__SOME_PARAMETERS();
  arguments->slots[2] = get__MANY_PARAMETERS();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__check_arguments_242;
}
static void entry__check_arguments_236(void) {
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
  // 405: ... arguments.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* arguments */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__check_arguments_237;
}
static void cont__check_arguments_237(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 405: if arguments.is_empty too_few_arguments_error
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* too_few_arguments_error */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__check_arguments_238;
}
static void cont__check_arguments_238(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 406: pop &arguments !results(idx)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* arguments */;
  result_count = 2;
  myself = get__pop();
  func = myself->type;
  frame->cont = cont__check_arguments_239;
}
static void cont__check_arguments_239(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* arguments */ = arguments->slots[0];
  frame->slots[5] /* temp__1 */ = arguments->slots[1];
  // 406: ... !results(idx)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* idx */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[2])->contents /* results */;
  func = myself->type;
  frame->cont = cont__check_arguments_240;
}
static void cont__check_arguments_240(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* results */ = arguments->slots[0];
  // 407: !last_idx idx-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* idx */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__check_arguments_241;
}
static void cont__check_arguments_241(void) {
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
static void cont__check_arguments_242(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__2 */ = arguments->slots[0];
  // 408: ... :
  // 409:   break
  frame->slots[14] /* temp__3 */ = create_closure(entry__check_arguments_243, 0);
  // 403: case option
  // 404:   MANDATORY_PARAMETER:
  // 405:     if arguments.is_empty too_few_arguments_error
  // 406:     pop &arguments !results(idx)
  // 407:     !last_idx idx-1
  // 408:   OPTIONAL_PARAMETER, SOME_PARAMETERS, MANY_PARAMETERS:
  // 409:     break
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
static void cont__check_arguments_244(void) {
  myself = frame->slots[0] /* break */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__check_arguments_245(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 410: ... : (idx template)
  // 411:   template $$option $_name? $_default_value? $_conversion? $_help
  // 412:   if option.is_a_key_value_pair: !option key_of(option)
  // 413:   case option
  // 414:     MANDATORY_PARAMETER:
  // 415:       if length_of(arguments) == 0 too_few_arguments_error
  // 416:       get &arguments !results(idx)
  // 417:     OPTIONAL_PARAMETER:
  // 418:       if length_of(arguments) > 0: get &arguments !results(idx)
  // 419:     SOME_PARAMETERS:
  // ...
  frame->slots[18] /* temp__1 */ = create_closure(entry__check_arguments_246, 2);
  // 410: for_each_from_to templates 1 last_idx: (idx template)
  // 411:   template $$option $_name? $_default_value? $_conversion? $_help
  // 412:   if option.is_a_key_value_pair: !option key_of(option)
  // 413:   case option
  // 414:     MANDATORY_PARAMETER:
  // 415:       if length_of(arguments) == 0 too_few_arguments_error
  // 416:       get &arguments !results(idx)
  // 417:     OPTIONAL_PARAMETER:
  // 418:       if length_of(arguments) > 0: get &arguments !results(idx)
  // 419:     SOME_PARAMETERS:
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
  frame->cont = cont__check_arguments_271;
}
static void entry__check_arguments_261(void) {
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
  // 418: ... get &arguments !results(idx)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* arguments */;
  result_count = 2;
  myself = get__get();
  func = myself->type;
  frame->cont = cont__check_arguments_262;
}
static void cont__check_arguments_262(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* arguments */ = arguments->slots[0];
  frame->slots[3] /* temp__1 */ = arguments->slots[1];
  // 418: ... !results(idx)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* idx */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[1])->contents /* results */;
  func = myself->type;
  frame->cont = cont__check_arguments_263;
}
static void cont__check_arguments_263(void) {
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
static void entry__check_arguments_252(void) {
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
  // 415: ... length_of(arguments)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* arguments */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__check_arguments_253;
}
static void cont__check_arguments_253(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 415: ... length_of(arguments) == 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__check_arguments_254;
}
static void cont__check_arguments_254(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 415: if length_of(arguments) == 0 too_few_arguments_error
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* too_few_arguments_error */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__check_arguments_255;
}
static void cont__check_arguments_255(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 416: get &arguments !results(idx)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* arguments */;
  result_count = 2;
  myself = get__get();
  func = myself->type;
  frame->cont = cont__check_arguments_256;
}
static void cont__check_arguments_256(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* arguments */ = arguments->slots[0];
  frame->slots[4] /* temp__1 */ = arguments->slots[1];
  // 416: ... !results(idx)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* idx */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[2])->contents /* results */;
  func = myself->type;
  frame->cont = cont__check_arguments_257;
}
static void cont__check_arguments_257(void) {
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
static void entry__check_arguments_258(void) {
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
  // 418: ... length_of(arguments)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* arguments */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__check_arguments_259;
}
static void cont__check_arguments_259(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 418: ... length_of(arguments) > 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__check_arguments_260;
}
static void cont__check_arguments_260(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 418: ... : get &arguments !results(idx)
  frame->slots[5] /* temp__3 */ = create_closure(entry__check_arguments_261, 0);
  // 418: if length_of(arguments) > 0: get &arguments !results(idx)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__check_arguments_264(void) {
  allocate_initialized_frame_gc(3, 3);
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
  // 420: !results(idx)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* idx */;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* arguments */;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* results */;
  func = myself->type;
  frame->cont = cont__check_arguments_265;
}
static void cont__check_arguments_265(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* results */ = arguments->slots[0];
  // 421: !arguments empty_list
  ((CELL *)frame->slots[2])->contents /* arguments */ = get__empty_list();
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__check_arguments_266(void) {
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
  // 423: ... length_of(arguments)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* arguments */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__check_arguments_267;
}
static void cont__check_arguments_267(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 423: ... length_of(arguments) == 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__check_arguments_268;
}
static void cont__check_arguments_268(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 423: if length_of(arguments) == 0 too_few_arguments_error
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* too_few_arguments_error */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__check_arguments_269;
}
static void cont__check_arguments_269(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 424: !results(idx)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* idx */;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* arguments */;
  result_count = 1;
  myself = ((CELL *)frame->slots[2])->contents /* results */;
  func = myself->type;
  frame->cont = cont__check_arguments_270;
}
static void cont__check_arguments_270(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* results */ = arguments->slots[0];
  // 425: !arguments empty_list
  ((CELL *)frame->slots[0])->contents /* arguments */ = get__empty_list();
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__check_arguments_246(void) {
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
  // 411: template $$option $_name? $_default_value? $_conversion? $_help
  argument_count = 0;
  arguments = node_p;
  result_count = -1;
  myself = frame->slots[1] /* template */;
  func = myself->type;
  frame->cont = cont__check_arguments_247;
}
static void cont__check_arguments_247(void) {
  if (argument_count < 2) {
    too_few_results_error();
    return;
  }
  if (argument_count > 5) {
    too_many_results_error();
    return;
  }
  ((CELL *)frame->slots[5])->contents /* option */ = arguments->slots[0];
  initialize_future(frame->slots[9] /* help */, arguments->slots[argument_count-1]);
  switch(argument_count) {
    default: initialize_future(frame->slots[8] /* conversion */, arguments->slots[3]);
    case 4: initialize_future(frame->slots[7] /* default_value */, arguments->slots[2]);
    case 3: initialize_future(frame->slots[6] /* name */, arguments->slots[1]);
    case 2:;
  }
  switch(argument_count) {
    case 2: initialize_future(frame->slots[6] /* name */, undefined);
    case 3: initialize_future(frame->slots[7] /* default_value */, undefined);
    case 4: initialize_future(frame->slots[8] /* conversion */, undefined);
  }
  // 412: ... option.is_a_key_value_pair
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[5])->contents /* option */;
  result_count = 1;
  myself = get__is_a_key_value_pair();
  func = myself->type;
  frame->cont = cont__check_arguments_248;
}
static void cont__check_arguments_248(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__1 */ = arguments->slots[0];
  // 412: ... : !option key_of(option)
  frame->slots[11] /* temp__2 */ = create_closure(entry__check_arguments_249, 0);
  // 412: if option.is_a_key_value_pair: !option key_of(option)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__1 */;
  arguments->slots[1] = frame->slots[11] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__check_arguments_251;
}
static void entry__check_arguments_249(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // option: 0
  frame->slots[0] = myself->closure.frame->slots[5]; /* option */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 412: ... !option key_of(option)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* option */;
  result_count = 1;
  myself = get__key_of();
  func = myself->type;
  frame->cont = cont__check_arguments_250;
}
static void cont__check_arguments_250(void) {
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
static void cont__check_arguments_251(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 414: ... :
  // 415:   if length_of(arguments) == 0 too_few_arguments_error
  // 416:   get &arguments !results(idx)
  frame->slots[10] /* temp__1 */ = create_closure(entry__check_arguments_252, 0);
  // 417: ... :
  // 418:   if length_of(arguments) > 0: get &arguments !results(idx)
  frame->slots[11] /* temp__2 */ = create_closure(entry__check_arguments_258, 0);
  // 419: ... :
  // 420:   !results(idx) arguments
  // 421:   !arguments empty_list
  frame->slots[12] /* temp__3 */ = create_closure(entry__check_arguments_264, 0);
  // 422: ... :
  // 423:   if length_of(arguments) == 0 too_few_arguments_error
  // 424:   !results(idx) arguments
  // 425:   !arguments empty_list
  frame->slots[13] /* temp__4 */ = create_closure(entry__check_arguments_266, 0);
  // 413: case option
  // 414:   MANDATORY_PARAMETER:
  // 415:     if length_of(arguments) == 0 too_few_arguments_error
  // 416:     get &arguments !results(idx)
  // 417:   OPTIONAL_PARAMETER:
  // 418:     if length_of(arguments) > 0: get &arguments !results(idx)
  // 419:   SOME_PARAMETERS:
  // 420:     !results(idx) arguments
  // 421:     !arguments empty_list
  // 422:   MANY_PARAMETERS:
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
static void cont__check_arguments_271(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 426: ... arguments.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* arguments */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__check_arguments_272;
}
static void cont__check_arguments_272(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[18] /* temp__1 */ = arguments->slots[0];
  // 426: unless arguments.is_empty too_many_arguments_error
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[18] /* temp__1 */;
  arguments->slots[1] = frame->slots[16] /* too_many_arguments_error */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__check_arguments_273;
}
static void cont__check_arguments_273(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 427: ... : (idx result)
  // 428:   if
  // 429:     result.is_undefined && default_values(idx).is_defined:
  // 430:       !results(idx) default_values(idx)
  // 431:     :
  // 432:       $possible_value possible_values(idx)
  // 433:       
  // 434:       $check: (value)
  // 435:         unless possible_value(value):
  // 436:           ewriteln
  // ...
  frame->slots[18] /* temp__1 */ = create_closure(entry__check_arguments_274, 2);
  // 427: for_each results: (idx result)
  // 428:   if
  // 429:     result.is_undefined && default_values(idx).is_defined:
  // 430:       !results(idx) default_values(idx)
  // 431:     :
  // 432:       $possible_value possible_values(idx)
  // 433:       
  // 434:       $check: (value)
  // 435:         unless possible_value(value):
  // 436:           ewriteln
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* results */;
  arguments->slots[1] = frame->slots[18] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__check_arguments_315;
}
static void entry__check_arguments_306(void) {
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
  // 451: $$new_result empty_list
  ((CELL *)frame->slots[4])->contents /* new_result */ = get__empty_list();
  // 452: ... : (item) push &new_result conversion(item)
  frame->slots[5] /* temp__1 */ = create_closure(entry__check_arguments_307, 1);
  // 452: for_each result: (item) push &new_result conversion(item)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* result */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__check_arguments_310;
}
static void entry__check_arguments_307(void) {
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
  // 452: ... conversion(item)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* item */;
  result_count = 1;
  myself = frame->slots[2] /* conversion */;
  func = myself->type;
  frame->cont = cont__check_arguments_308;
}
static void cont__check_arguments_308(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 452: ... push &new_result conversion(item)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* new_result */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__check_arguments_309;
}
static void cont__check_arguments_309(void) {
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
static void cont__check_arguments_310(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 453: !results(idx)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* idx */;
  arguments->slots[1] = ((CELL *)frame->slots[4])->contents /* new_result */;
  result_count = 1;
  myself = ((CELL *)frame->slots[2])->contents /* results */;
  func = myself->type;
  frame->cont = cont__check_arguments_311;
}
static void cont__check_arguments_311(void) {
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
static void entry__check_arguments_312(void) {
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
  // 455: !results(idx) conversion(result)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* result */;
  result_count = 1;
  myself = frame->slots[2] /* conversion */;
  func = myself->type;
  frame->cont = cont__check_arguments_313;
}
static void cont__check_arguments_313(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 455: !results(idx)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* idx */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* results */;
  func = myself->type;
  frame->cont = cont__check_arguments_314;
}
static void cont__check_arguments_314(void) {
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
static void entry__check_arguments_304(void) {
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
  // 450: result.is_a_list
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* result */;
  result_count = 1;
  myself = get__is_a_list();
  func = myself->type;
  frame->cont = cont__check_arguments_305;
}
static void cont__check_arguments_305(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 450: ... :
  // 451:   $$new_result empty_list
  // 452:   for_each result: (item) push &new_result conversion(item)
  // 453:   !results(idx) new_result
  frame->slots[5] /* temp__2 */ = create_closure(entry__check_arguments_306, 0);
  // 454: :
  // 455:   !results(idx) conversion(result)
  frame->slots[6] /* temp__3 */ = create_closure(entry__check_arguments_312, 0);
  // 449: if
  // 450:   result.is_a_list:
  // 451:     $$new_result empty_list
  // 452:     for_each result: (item) push &new_result conversion(item)
  // 453:     !results(idx) new_result
  // 454:   :
  // 455:     !results(idx) conversion(result)
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
static void entry__check_arguments_280(void) {
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
  // 430: !results(idx) default_values(idx)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* idx */;
  result_count = 1;
  myself = ((CELL *)frame->slots[2])->contents /* default_values */;
  func = myself->type;
  frame->cont = cont__check_arguments_281;
}
static void cont__check_arguments_281(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 430: !results(idx)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* idx */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* results */;
  func = myself->type;
  frame->cont = cont__check_arguments_282;
}
static void cont__check_arguments_282(void) {
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
static void entry__check_arguments_283(void) {
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
  // 434: ... : (value)
  // 435:   unless possible_value(value):
  // 436:     ewriteln
  // 437:       "Invalid argument value for @(names(idx).to_upper_case)!@nl;"
  // 438:     show_usage
  // 439:     exit 1
  frame->slots[10] /* temp__1 */ = create_closure(entry__check_arguments_284, 1);
  // 434: $check: (value)
  // 435:   unless possible_value(value):
  // 436:     ewriteln
  // 437:       "Invalid argument value for @(names(idx).to_upper_case)!@nl;"
  // 438:     show_usage
  // 439:     exit 1
  initialize_future(frame->slots[8] /* check */, frame->slots[10] /* temp__1 */);
  // 432: $possible_value possible_values(idx)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* idx */;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* possible_values */;
  func = myself->type;
  frame->cont = cont__check_arguments_294;
}
static void entry__check_arguments_286(void) {
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
  // 437: ... names(idx)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* idx */;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* names */;
  func = myself->type;
  frame->cont = cont__check_arguments_287;
}
static void cont__check_arguments_287(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 437: ... names(idx).to_upper_case
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__to_upper_case();
  func = myself->type;
  frame->cont = cont__check_arguments_288;
}
static void cont__check_arguments_288(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 437: "Invalid argument value for @(names(idx).to_upper_case)!@nl;"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__143aedf103648031;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  arguments->slots[2] = string__2d7981f4e6002bcf;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__check_arguments_291;
}
static void cont__check_arguments_291(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 436: ewriteln
  // 437:   "Invalid argument value for @(names(idx).to_upper_case)!@nl;"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = 0;
  myself = get__ewriteln();
  func = myself->type;
  frame->cont = cont__check_arguments_292;
}
static void cont__check_arguments_292(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 438: show_usage
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = frame->slots[2] /* show_usage */;
  func = myself->type;
  frame->cont = cont__check_arguments_293;
}
static void cont__check_arguments_293(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 439: exit 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = frame->caller_result_count;
  myself = get__exit();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__check_arguments_284(void) {
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
  // 435: ... possible_value(value)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* value */;
  result_count = 1;
  myself = frame->slots[1] /* possible_value */;
  func = myself->type;
  frame->cont = cont__check_arguments_285;
}
static void cont__check_arguments_285(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 435: ... :
  // 436:   ewriteln
  // 437:     "Invalid argument value for @(names(idx).to_upper_case)!@nl;"
  // 438:   show_usage
  // 439:   exit 1
  frame->slots[6] /* temp__2 */ = create_closure(entry__check_arguments_286, 0);
  // 435: unless possible_value(value):
  // 436:   ewriteln
  // 437:     "Invalid argument value for @(names(idx).to_upper_case)!@nl;"
  // 438:   show_usage
  // 439:   exit 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__check_arguments_294(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[7] /* possible_value */, arguments->slots[0]);
  // 441: ... possible_value.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* possible_value */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__check_arguments_295;
}
static void cont__check_arguments_295(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__1 */ = arguments->slots[0];
  // 441: ... :
  // 442:   if
  // 443:     result.is_a_list:
  // 444:       for_each result: (item) check item
  // 445:     :
  // 446:       check result
  frame->slots[11] /* temp__2 */ = create_closure(entry__check_arguments_296, 0);
  // 441: if possible_value.is_defined:
  // 442:   if
  // 443:     result.is_a_list:
  // 444:       for_each result: (item) check item
  // 445:     :
  // 446:       check result
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__1 */;
  arguments->slots[1] = frame->slots[11] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__check_arguments_301;
}
static void entry__check_arguments_299(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // item: 0
  // check: 1
  frame->slots[1] = myself->closure.frame->slots[1]; /* check */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 444: ... check item
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* item */;
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* check */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__check_arguments_298(void) {
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
  // 444: ... : (item) check item
  frame->slots[2] /* temp__1 */ = create_closure(entry__check_arguments_299, 1);
  // 444: for_each result: (item) check item
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* result */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__check_arguments_300(void) {
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
  // 446: check result
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* result */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* check */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__check_arguments_296(void) {
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
  // 443: result.is_a_list
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* result */;
  result_count = 1;
  myself = get__is_a_list();
  func = myself->type;
  frame->cont = cont__check_arguments_297;
}
static void cont__check_arguments_297(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 443: ... :
  // 444:   for_each result: (item) check item
  frame->slots[3] /* temp__2 */ = create_closure(entry__check_arguments_298, 0);
  // 445: :
  // 446:   check result
  frame->slots[4] /* temp__3 */ = create_closure(entry__check_arguments_300, 0);
  // 442: if
  // 443:   result.is_a_list:
  // 444:     for_each result: (item) check item
  // 445:   :
  // 446:     check result
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
static void cont__check_arguments_301(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 447: $conversion conversions(idx)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* idx */;
  result_count = 1;
  myself = ((CELL *)frame->slots[5])->contents /* conversions */;
  func = myself->type;
  frame->cont = cont__check_arguments_302;
}
static void cont__check_arguments_302(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[9] /* conversion */, arguments->slots[0]);
  // 448: ... conversion.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* conversion */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__check_arguments_303;
}
static void cont__check_arguments_303(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__1 */ = arguments->slots[0];
  // 448: ... :
  // 449:   if
  // 450:     result.is_a_list:
  // 451:       $$new_result empty_list
  // 452:       for_each result: (item) push &new_result conversion(item)
  // 453:       !results(idx) new_result
  // 454:     :
  // 455:       !results(idx) conversion(result)
  frame->slots[11] /* temp__2 */ = create_closure(entry__check_arguments_304, 0);
  // 448: if conversion.is_defined:
  // 449:   if
  // 450:     result.is_a_list:
  // 451:       $$new_result empty_list
  // 452:       for_each result: (item) push &new_result conversion(item)
  // 453:       !results(idx) new_result
  // 454:     :
  // 455:       !results(idx) conversion(result)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__1 */;
  arguments->slots[1] = frame->slots[11] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__check_arguments_274(void) {
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
  // 429: result.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* result */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__check_arguments_275;
}
static void cont__check_arguments_275(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__2 */ = arguments->slots[0];
  // 429: ... default_values(idx).is_defined
  frame->slots[10] /* temp__3 */ = create_closure(entry__check_arguments_276, 0);
  // 429: result.is_undefined && default_values(idx).is_defined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__2 */;
  arguments->slots[1] = frame->slots[10] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__check_arguments_279;
}
static void entry__check_arguments_276(void) {
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
  // 429: ... default_values(idx)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* idx */;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* default_values */;
  func = myself->type;
  frame->cont = cont__check_arguments_277;
}
static void cont__check_arguments_277(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 429: ... default_values(idx).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__check_arguments_278;
}
static void cont__check_arguments_278(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 429: ... default_values(idx).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__check_arguments_279(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__1 */ = arguments->slots[0];
  // 429: ... :
  // 430:   !results(idx) default_values(idx)
  frame->slots[11] /* temp__4 */ = create_closure(entry__check_arguments_280, 0);
  // 431: :
  // 432:   $possible_value possible_values(idx)
  // 433:   
  // 434:   $check: (value)
  // 435:     unless possible_value(value):
  // 436:       ewriteln
  // 437:         "Invalid argument value for @(names(idx).to_upper_case)!@nl;"
  // 438:       show_usage
  // 439:       exit 1
  // 440:   
  // ...
  frame->slots[12] /* temp__5 */ = create_closure(entry__check_arguments_283, 0);
  // 428: if
  // 429:   result.is_undefined && default_values(idx).is_defined:
  // 430:     !results(idx) default_values(idx)
  // 431:   :
  // 432:     $possible_value possible_values(idx)
  // 433:     
  // 434:     $check: (value)
  // 435:       unless possible_value(value):
  // 436:         ewriteln
  // 437:           "Invalid argument value for @(names(idx).to_upper_case)!@nl;"
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
static void cont__check_arguments_315(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 456: -> results*
  argument_count = 0;
  arguments = node_p;
  unfold(((CELL *)frame->slots[3])->contents /* results */);
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__program_commands_1(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // commands: 0
  // command_ids: 1
  frame->slots[1] /* command_ids */ = create_cell();
  frame->slots[0] /* commands */ = from_arguments(0, argument_count-0);
  // 466: $$command_ids empty_list
  ((CELL *)frame->slots[1])->contents /* command_ids */ = get__empty_list();
  // 467: ... : (command)
  // 468:   $name key_of(command)
  // 469:   $description value_of(command)
  // 470:   push &command_names name
  // 471:   push &command_descriptions description
  // 472:   inc &command_id_count
  // 473:   push &command_ids command_id_count
  frame->slots[2] /* temp__1 */ = create_closure(entry__std__program_commands_2, 1);
  // 467: for_each commands: (command)
  // 468:   $name key_of(command)
  // 469:   $description value_of(command)
  // 470:   push &command_names name
  // 471:   push &command_descriptions description
  // 472:   inc &command_id_count
  // 473:   push &command_ids command_id_count
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* commands */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__std__program_commands_9;
}
static void entry__std__program_commands_2(void) {
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
  // 468: $name key_of(command)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* command */;
  result_count = 1;
  myself = get__key_of();
  func = myself->type;
  frame->cont = cont__std__program_commands_3;
}
static void cont__std__program_commands_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* name */, arguments->slots[0]);
  // 469: $description value_of(command)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* command */;
  result_count = 1;
  myself = get__value_of();
  func = myself->type;
  frame->cont = cont__std__program_commands_4;
}
static void cont__std__program_commands_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* description */, arguments->slots[0]);
  // 470: push &command_names name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._command_names;
  arguments->slots[1] = frame->slots[2] /* name */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__std__program_commands_5;
}
static void cont__std__program_commands_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._command_names = arguments->slots[0];
  // 471: push &command_descriptions description
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._command_descriptions;
  arguments->slots[1] = frame->slots[3] /* description */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__std__program_commands_6;
}
static void cont__std__program_commands_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._command_descriptions = arguments->slots[0];
  // 472: inc &command_id_count
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._command_id_count;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__std__program_commands_7;
}
static void cont__std__program_commands_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._command_id_count = arguments->slots[0];
  // 473: push &command_ids command_id_count
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* command_ids */;
  arguments->slots[1] = var._command_id_count;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__std__program_commands_8;
}
static void cont__std__program_commands_8(void) {
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
static void cont__std__program_commands_9(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 474: -> command_ids*
  argument_count = 0;
  arguments = node_p;
  unfold(((CELL *)frame->slots[1])->contents /* command_ids */);
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__command_parameters_33(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // templates: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* templates */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 501: ... list(undefined)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__std__command_parameters_34;
}
static void cont__std__command_parameters_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 501: ... length_of(templates)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* templates */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__std__command_parameters_35;
}
static void cont__std__command_parameters_35(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 501: ... dup(list(undefined) length_of(templates))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__dup();
  func = myself->type;
  frame->cont = cont__std__command_parameters_36;
}
static void cont__std__command_parameters_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 501: ... -> dup(list(undefined) length_of(templates))*
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[1] /* temp__1 */);
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__command_parameters_29(void) {
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
  // 499: !command_id id
  var._command_id = frame->slots[0] /* id */;
  // 500: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__std__command_parameters_30;
}
static void cont__std__command_parameters_30(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 500: ... range(command_line_arguments 2 -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__command_line_arguments();
  arguments->slots[1] = number__2;
  arguments->slots[2] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__std__command_parameters_31;
}
static void cont__std__command_parameters_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 500: check_arguments command range(command_line_arguments 2 -1) templates
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
static void entry__std__command_parameters_23(void) {
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
  // 497: ... command_names(id)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* id */;
  result_count = 1;
  myself = var._command_names;
  func = myself->type;
  frame->cont = cont__std__command_parameters_24;
}
static void cont__std__command_parameters_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 497: ... list("--help")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__481f572601de82a7;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__std__command_parameters_25;
}
static void cont__std__command_parameters_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 497: check_arguments command_names(id) list("--help") templates
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
static void entry__std__command_parameters_10(void) {
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
  // 493: command == "help"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* command */;
  arguments->slots[1] = string__120ae80b5d007d49;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__std__command_parameters_12;
}
static void cont__std__command_parameters_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  frame->slots[5] /* temp__3 */ = create_closure(entry__std__command_parameters_13, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__std__command_parameters_22;
}
static void entry__std__command_parameters_13(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // id: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* id */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 494: length_of(command_line_arguments)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__command_line_arguments();
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__std__command_parameters_14;
}
static void cont__std__command_parameters_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 494: length_of(command_line_arguments) == 2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__std__command_parameters_15;
}
static void cont__std__command_parameters_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 495: command_line_arguments(2).from_utf8 == command_names(id)
  frame->slots[4] /* temp__4 */ = create_closure(entry__std__command_parameters_16, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__4 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__std__command_parameters_21;
}
static void entry__std__command_parameters_16(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // id: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* id */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 495: command_line_arguments(2)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = get__command_line_arguments();
  func = myself->type;
  frame->cont = cont__std__command_parameters_17;
}
static void cont__std__command_parameters_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 495: command_line_arguments(2).from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__from_utf8();
  func = myself->type;
  frame->cont = cont__std__command_parameters_18;
}
static void cont__std__command_parameters_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 495: ... command_names(id)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* id */;
  result_count = 1;
  myself = var._command_names;
  func = myself->type;
  frame->cont = cont__std__command_parameters_19;
}
static void cont__std__command_parameters_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__4 */ = arguments->slots[0];
  // 495: command_line_arguments(2).from_utf8 == command_names(id)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__4 */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__std__command_parameters_20;
}
static void cont__std__command_parameters_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 495: command_line_arguments(2).from_utf8 == command_names(id)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__std__command_parameters_21(void) {
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
static void cont__std__command_parameters_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 496: :
  // 497:   check_arguments command_names(id) list("--help") templates
  frame->slots[6] /* temp__4 */ = create_closure(entry__std__command_parameters_23, 0);
  // 491: ->
  // 492:   &&
  // 493:     command == "help"
  // 494:     length_of(command_line_arguments) == 2
  // 495:     command_line_arguments(2).from_utf8 == command_names(id)
  // 496:   :
  // 497:     check_arguments command_names(id) list("--help") templates
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__4 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__command_parameters_26(void) {
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
  // 498: ... command_names(id)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* id */;
  result_count = 1;
  myself = var._command_names;
  func = myself->type;
  frame->cont = cont__std__command_parameters_27;
}
static void cont__std__command_parameters_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 498: ... command == command_names(id)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* command */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__std__command_parameters_28;
}
static void cont__std__command_parameters_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 498: ... :
  // 499:   !command_id id
  // 500:   check_arguments command range(command_line_arguments 2 -1) templates
  frame->slots[5] /* temp__3 */ = create_closure(entry__std__command_parameters_29, 0);
  // 498: -> command == command_names(id):
  // 499:   !command_id id
  // 500:   check_arguments command range(command_line_arguments 2 -1) templates
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__command_parameters_32(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // templates: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* templates */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 501: ... -> dup(list(undefined) length_of(templates))*
  frame->slots[1] /* temp__1 */ = create_closure(entry__std__command_parameters_33, 0);
  // 501: -> true -> dup(list(undefined) length_of(templates))*
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__true();
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__command_parameters_3(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // templates: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* templates */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 487: ... list(undefined)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__std__command_parameters_4;
}
static void cont__std__command_parameters_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 487: ... length_of(templates)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* templates */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__std__command_parameters_5;
}
static void cont__std__command_parameters_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 487: ... dup(list(undefined) length_of(templates))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__dup();
  func = myself->type;
  frame->cont = cont__std__command_parameters_6;
}
static void cont__std__command_parameters_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 487: -> dup(list(undefined) length_of(templates))*
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[1] /* temp__1 */);
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__command_parameters_7(void) {
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
  // 489: ... command_line_arguments(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__command_line_arguments();
  func = myself->type;
  frame->cont = cont__std__command_parameters_8;
}
static void cont__std__command_parameters_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 489: $command command_line_arguments(1).from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__from_utf8();
  func = myself->type;
  frame->cont = cont__std__command_parameters_9;
}
static void cont__std__command_parameters_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* command */, arguments->slots[0]);
  // 491: ->
  // 492:   &&
  // 493:     command == "help"
  // 494:     length_of(command_line_arguments) == 2
  // 495:     command_line_arguments(2).from_utf8 == command_names(id)
  // 496:   :
  // 497:     check_arguments command_names(id) list("--help") templates
  frame->slots[3] /* temp__1 */ = create_closure(entry__std__command_parameters_10, 0);
  // 498: -> command == command_names(id):
  // 499:   !command_id id
  // 500:   check_arguments command range(command_line_arguments 2 -1) templates
  frame->slots[4] /* temp__2 */ = create_closure(entry__std__command_parameters_26, 0);
  // 501: -> true -> dup(list(undefined) length_of(templates))*
  frame->slots[5] /* temp__3 */ = create_closure(entry__std__command_parameters_32, 0);
  // 490: cond
  // 491:   ->
  // 492:     &&
  // 493:       command == "help"
  // 494:       length_of(command_line_arguments) == 2
  // 495:       command_line_arguments(2).from_utf8 == command_names(id)
  // 496:     :
  // 497:       check_arguments command_names(id) list("--help") templates
  // 498:   -> command == command_names(id):
  // 499:     !command_id id
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
static void entry__std__command_parameters_1(void) {
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
  // 486: command_line_arguments.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__command_line_arguments();
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__std__command_parameters_2;
}
static void cont__std__command_parameters_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 487: -> dup(list(undefined) length_of(templates))*
  frame->slots[3] /* temp__2 */ = create_closure(entry__std__command_parameters_3, 0);
  // 488: :
  // 489:   $command command_line_arguments(1).from_utf8
  // 490:   cond
  // 491:     ->
  // 492:       &&
  // 493:         command == "help"
  // 494:         length_of(command_line_arguments) == 2
  // 495:         command_line_arguments(2).from_utf8 == command_names(id)
  // 496:       :
  // 497:         check_arguments command_names(id) list("--help") templates
  // ...
  frame->slots[4] /* temp__3 */ = create_closure(entry__std__command_parameters_7, 0);
  // 485: if
  // 486:   command_line_arguments.is_empty
  // 487:   -> dup(list(undefined) length_of(templates))*
  // 488:   :
  // 489:     $command command_line_arguments(1).from_utf8
  // 490:     cond
  // 491:       ->
  // 492:         &&
  // 493:           command == "help"
  // 494:           length_of(command_line_arguments) == 2
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
static void entry__show_commands_1(void) {
  allocate_initialized_frame_gc(0, 3);
  // slot allocations:
  // tab: 0
  frame->slots[0] /* tab */ = create_cell();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 504: ... program_version.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._program_version;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__show_commands_2;
}
static void cont__show_commands_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 504: if program_version.is_defined:
  // 505:   show_version truncate_until(program_name '/' -1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = func__show_commands_3;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__show_commands_6;
}
static void entry__show_commands_3(void) {
  allocate_initialized_frame_gc(0, 2);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 505: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__show_commands_4;
}
static void cont__show_commands_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 505: ... truncate_until(program_name '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__program_name();
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = get__truncate_until();
  func = myself->type;
  frame->cont = cont__show_commands_5;
}
static void cont__show_commands_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 505: show_version truncate_until(program_name '/' -1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = var._show_version;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__show_commands_6(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 506: ewriteln "Available commands:"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__c69810bce846f05a;
  result_count = 0;
  myself = get__ewriteln();
  func = myself->type;
  frame->cont = cont__show_commands_8;
}
static void cont__show_commands_8(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 507: ... list("help" "display help for the specified command")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__120ae80b5d007d49;
  arguments->slots[1] = string__e65a119686ab55e3;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__show_commands_10;
}
static void cont__show_commands_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 507: $$tab list(list("help" "display help for the specified command"))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__show_commands_11;
}
static void cont__show_commands_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* tab */ = arguments->slots[0];
  // 508: ... : (idx command_name)
  // 509:   push &tab list(command_name command_descriptions(idx))
  frame->slots[1] /* temp__1 */ = create_closure(entry__show_commands_12, 2);
  // 508: for_each command_names: (idx command_name)
  // 509:   push &tab list(command_name command_descriptions(idx))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._command_names;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__show_commands_16;
}
static void entry__show_commands_12(void) {
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
  // 509: ... command_descriptions(idx)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* idx */;
  result_count = 1;
  myself = var._command_descriptions;
  func = myself->type;
  frame->cont = cont__show_commands_13;
}
static void cont__show_commands_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 509: ... list(command_name command_descriptions(idx))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* command_name */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__show_commands_14;
}
static void cont__show_commands_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 509: push &tab list(command_name command_descriptions(idx))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* tab */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__show_commands_15;
}
static void cont__show_commands_15(void) {
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
static void cont__show_commands_16(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 510: ... program_copyright.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._program_copyright;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__show_commands_17;
}
static void cont__show_commands_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 510: ... :
  // 511:   push &tab list("copyright" "display the copyright message")
  frame->slots[2] /* temp__2 */ = create_closure(entry__show_commands_18, 0);
  // 510: if program_copyright.is_defined:
  // 511:   push &tab list("copyright" "display the copyright message")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__show_commands_23;
}
static void entry__show_commands_18(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // tab: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* tab */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 511: ... list("copyright" "display the copyright message")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__7cf0276001425531;
  arguments->slots[1] = string__d9b4d5146ecce23;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__show_commands_21;
}
static void cont__show_commands_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 511: push &tab list("copyright" "display the copyright message")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* tab */;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__show_commands_22;
}
static void cont__show_commands_22(void) {
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
static void cont__show_commands_23(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 512: ... program_version.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._program_version;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__show_commands_24;
}
static void cont__show_commands_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 512: ... :
  // 513:   push &tab list("version" "display the version number")
  frame->slots[2] /* temp__2 */ = create_closure(entry__show_commands_25, 0);
  // 512: if program_version.is_defined:
  // 513:   push &tab list("version" "display the version number")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__show_commands_30;
}
static void entry__show_commands_25(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // tab: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* tab */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 513: ... list("version" "display the version number")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__945c0f9015c3e094;
  arguments->slots[1] = string__460a51cfecd67225;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__show_commands_28;
}
static void cont__show_commands_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 513: push &tab list("version" "display the version number")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* tab */;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__show_commands_29;
}
static void cont__show_commands_29(void) {
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
static void cont__show_commands_30(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 514: display_table tab
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* tab */;
  result_count = frame->caller_result_count;
  myself = var._display_table;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__program_parameters_9(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 616: ewriteln "
  // 617:   No command specified!
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__9e1d476192d899b4;
  result_count = 0;
  myself = get__ewriteln();
  func = myself->type;
  frame->cont = cont__std__program_parameters_11;
}
static void cont__std__program_parameters_11(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 618: show_commands
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = var._show_commands;
  func = myself->type;
  frame->cont = cont__std__program_parameters_12;
}
static void cont__std__program_parameters_12(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 619: exit 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = frame->caller_result_count;
  myself = get__exit();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__program_parameters_13(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 621: ... command_line_arguments(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__command_line_arguments();
  func = myself->type;
  frame->cont = cont__std__program_parameters_14;
}
static void cont__std__program_parameters_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 621: case command_line_arguments(1)
  // 622:   "copyright"
  // 623:   :
  // 624:     if program_copyright.is_defined:
  // 625:       show_copyright
  // 626:       terminate
  // 627:   "help"
  // 628:   :
  // 629:     case length_of(command_line_arguments)
  // 630:       1:
  // ...
  argument_count = 7;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = string__7cf0276001425531;
  arguments->slots[2] = func__std__program_parameters_15;
  arguments->slots[3] = string__120ae80b5d007d49;
  arguments->slots[4] = func__std__program_parameters_19;
  arguments->slots[5] = string__945c0f9015c3e094;
  arguments->slots[6] = func__std__program_parameters_45;
  result_count = 0;
  myself = get__case();
  func = myself->type;
  frame->cont = cont__std__program_parameters_51;
}
static void entry__std__program_parameters_47(void) {
  allocate_initialized_frame_gc(0, 2);
  // slot allocations:
  // command_name: 0
  frame->slots[0] /* command_name */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 670: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__std__program_parameters_48;
}
static void cont__std__program_parameters_48(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 670: $command_name truncate_until(program_name '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__program_name();
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__truncate_until();
  func = myself->type;
  frame->cont = cont__std__program_parameters_49;
}
static void cont__std__program_parameters_49(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[0] /* command_name */, arguments->slots[0]);
  // 671: show_version command_name
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* command_name */;
  result_count = 0;
  myself = var._show_version;
  func = myself->type;
  frame->cont = cont__std__program_parameters_50;
}
static void cont__std__program_parameters_50(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 672: terminate
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = get__terminate();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__program_parameters_21(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 631: show_commands
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = var._show_commands;
  func = myself->type;
  frame->cont = cont__std__program_parameters_22;
}
static void cont__std__program_parameters_22(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 632: terminate
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = get__terminate();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__program_parameters_23(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 634: ... command_line_arguments(2)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = get__command_line_arguments();
  func = myself->type;
  frame->cont = cont__std__program_parameters_24;
}
static void cont__std__program_parameters_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 634: case command_line_arguments(2)
  // 635:   "copyright"
  // 636:   :
  // 637:     if program_copyright.is_defined:
  // 638:       ewrite "
  // 639:         Usage:
  // 640:           sigi copyright
  // 641:       terminate
  // 642:   "help"
  // 643:   :
  // ...
  argument_count = 7;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = string__7cf0276001425531;
  arguments->slots[2] = func__std__program_parameters_25;
  arguments->slots[3] = string__120ae80b5d007d49;
  arguments->slots[4] = func__std__program_parameters_30;
  arguments->slots[5] = string__945c0f9015c3e094;
  arguments->slots[6] = func__std__program_parameters_33;
  result_count = 0;
  myself = get__case();
  func = myself->type;
  frame->cont = cont__std__program_parameters_38;
}
static void entry__std__program_parameters_35(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 654: ewrite "
  // 655:   Usage:
  // 656:     sigi version
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__617a0ed7343fbf40;
  result_count = 0;
  myself = get__ewrite();
  func = myself->type;
  frame->cont = cont__std__program_parameters_37;
}
static void cont__std__program_parameters_37(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 657: terminate
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = get__terminate();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__program_parameters_27(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 638: ewrite "
  // 639:   Usage:
  // 640:     sigi copyright
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__1dc76095d723d587;
  result_count = 0;
  myself = get__ewrite();
  func = myself->type;
  frame->cont = cont__std__program_parameters_29;
}
static void cont__std__program_parameters_29(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 641: terminate
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = get__terminate();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__program_parameters_25(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 637: ... program_copyright.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._program_copyright;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__std__program_parameters_26;
}
static void cont__std__program_parameters_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 637: if program_copyright.is_defined:
  // 638:   ewrite "
  // 639:     Usage:
  // 640:       sigi copyright
  // 641:   terminate
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = func__std__program_parameters_27;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__program_parameters_30(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 644: ewrite "
  // 645:   Usage:
  // 646:     sigi help COMMAND
  // 647:   
  // 648:   Parameter:
  // 649:     COMMAND  the command for which to retrieve help
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__a15bc662b3bb7e39;
  result_count = 0;
  myself = get__ewrite();
  func = myself->type;
  frame->cont = cont__std__program_parameters_32;
}
static void cont__std__program_parameters_32(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 650: terminate
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = get__terminate();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__program_parameters_33(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 653: ... program_version.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._program_version;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__std__program_parameters_34;
}
static void cont__std__program_parameters_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 653: if program_version.is_defined:
  // 654:   ewrite "
  // 655:     Usage:
  // 656:       sigi version
  // 657:   terminate
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = func__std__program_parameters_35;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__std__program_parameters_38(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 658: ewriteln "
  // 659:   Invalid command name!
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__19bd6394b9c09d4b;
  result_count = 0;
  myself = get__ewriteln();
  func = myself->type;
  frame->cont = cont__std__program_parameters_40;
}
static void cont__std__program_parameters_40(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 660: show_commands
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = var._show_commands;
  func = myself->type;
  frame->cont = cont__std__program_parameters_41;
}
static void cont__std__program_parameters_41(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 661: exit 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = frame->caller_result_count;
  myself = get__exit();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__program_parameters_42(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 663: ewriteln "
  // 664:   Too many arguments!
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__e3aee165acc437aa;
  result_count = 0;
  myself = get__ewriteln();
  func = myself->type;
  frame->cont = cont__std__program_parameters_43;
}
static void cont__std__program_parameters_43(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 665: show_commands
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = var._show_commands;
  func = myself->type;
  frame->cont = cont__std__program_parameters_44;
}
static void cont__std__program_parameters_44(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 666: exit 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = frame->caller_result_count;
  myself = get__exit();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__program_parameters_17(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 625: show_copyright
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = var._show_copyright;
  func = myself->type;
  frame->cont = cont__std__program_parameters_18;
}
static void cont__std__program_parameters_18(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 626: terminate
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = get__terminate();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__program_parameters_15(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 624: ... program_copyright.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._program_copyright;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__std__program_parameters_16;
}
static void cont__std__program_parameters_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 624: if program_copyright.is_defined:
  // 625:   show_copyright
  // 626:   terminate
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = func__std__program_parameters_17;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__program_parameters_19(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 629: ... length_of(command_line_arguments)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__command_line_arguments();
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__std__program_parameters_20;
}
static void cont__std__program_parameters_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 629: case length_of(command_line_arguments)
  // 630:   1:
  // 631:     show_commands
  // 632:     terminate
  // 633:   2:
  // 634:     case command_line_arguments(2)
  // 635:       "copyright"
  // 636:       :
  // 637:         if program_copyright.is_defined:
  // 638:           ewrite "
  // ...
  argument_count = 6;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = func__std__program_parameters_21;
  arguments->slots[3] = number__2;
  arguments->slots[4] = func__std__program_parameters_23;
  arguments->slots[5] = func__std__program_parameters_42;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__program_parameters_45(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 669: ... program_version.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._program_version;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__std__program_parameters_46;
}
static void cont__std__program_parameters_46(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 669: if program_version.is_defined:
  // 670:   $command_name truncate_until(program_name '/' -1)
  // 671:   show_version command_name
  // 672:   terminate
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = func__std__program_parameters_47;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__std__program_parameters_51(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 673: ewriteln "
  // 674:   Invalid arguments!
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__f68d8519ec4e03eb;
  result_count = 0;
  myself = get__ewriteln();
  func = myself->type;
  frame->cont = cont__std__program_parameters_53;
}
static void cont__std__program_parameters_53(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 675: show_commands
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = var._show_commands;
  func = myself->type;
  frame->cont = cont__std__program_parameters_54;
}
static void cont__std__program_parameters_54(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 676: exit 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = frame->caller_result_count;
  myself = get__exit();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__program_parameters_6(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 613: ... -> command_id
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._command_id;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__program_parameters_7(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 615: command_line_arguments.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__command_line_arguments();
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__std__program_parameters_8;
}
static void cont__std__program_parameters_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 614: if
  // 615:   command_line_arguments.is_empty:
  // 616:     ewriteln "
  // 617:       No command specified!
  // 618:     show_commands
  // 619:     exit 1
  // 620:   :
  // 621:     case command_line_arguments(1)
  // 622:       "copyright"
  // 623:       :
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = func__std__program_parameters_9;
  arguments->slots[2] = func__std__program_parameters_13;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__program_parameters_3(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // templates: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* templates */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 678: check_arguments command_line_arguments templates
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__command_line_arguments();
  arguments->slots[1] = frame->slots[0] /* templates */;
  result_count = frame->caller_result_count;
  myself = var._check_arguments;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__program_parameters_4(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 613: ... command_id.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._command_id;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__std__program_parameters_5;
}
static void cont__std__program_parameters_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 613: if command_id.is_defined (-> command_id):
  // 614:   if
  // 615:     command_line_arguments.is_empty:
  // 616:       ewriteln "
  // 617:         No command specified!
  // 618:       show_commands
  // 619:       exit 1
  // 620:     :
  // 621:       case command_line_arguments(1)
  // 622:         "copyright"
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = func__std__program_parameters_6;
  arguments->slots[2] = func__std__program_parameters_7;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__program_parameters_1(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // templates: 0
  frame->slots[0] /* templates */ = from_arguments(0, argument_count-0);
  // 612: command_id_count > 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = var._command_id_count;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__std__program_parameters_2;
}
static void cont__std__program_parameters_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 677: :
  // 678:   check_arguments command_line_arguments templates
  frame->slots[2] /* temp__2 */ = create_closure(entry__std__program_parameters_3, 0);
  // 611: if
  // 612:   command_id_count > 0:
  // 613:     if command_id.is_defined (-> command_id):
  // 614:       if
  // 615:         command_line_arguments.is_empty:
  // 616:           ewriteln "
  // 617:             No command specified!
  // 618:           show_commands
  // 619:           exit 1
  // 620:         :
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = func__std__program_parameters_4;
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
  set_module("basic__parameters");
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
  func__std__copyright_1 = create_function(entry__std__copyright_1, 1);
  func__std__version_1 = create_function(entry__std__version_1, 1);
  string__629e8589dc7e42e = from_latin_1_string("Invalid option ", 15);
  string__578a5af303e9cc0 = from_latin_1_string("!", 1);
  func__std__extract_options_1 = create_function(entry__std__extract_options_1, -1);
  func__std__extract_some_options_1 = create_function(entry__std__extract_some_options_1, -1);
  string__2d7981f4e6082be5 = from_latin_1_string("  ", 2);
  string__578a5af303e9cc1 = from_latin_1_string(" ", 1);
  func__display_table_1 = create_function(entry__display_table_1, 1);
  string__2d7981f4e7582bcf = from_latin_1_string(
    "\n"
    "\n",
    2);
  func__show_version_1 = create_function(entry__show_version_1, 1);
  func__show_copyright_1 = create_function(entry__show_copyright_1, 0);
  string__e8329800b0d69ed2 = from_latin_1_string("valid values:", 13);
  string__7f5cac89d5ba4088 = from_latin_1_string("(default value: ", 16);
  string__578a5af303e9cc8 = from_latin_1_string(")", 1);
  string__5a1f579a019362ed = from_latin_1_string("Usage:", 6);
  string__d89f1181d9c5276e = from_latin_1_string(" --copyright", 12);
  string__a3040cb415de108a = from_latin_1_string(" --help", 7);
  func__check_arguments_58 = create_function(entry__check_arguments_58, 0);
  string__a67e424a37fc0741 = from_latin_1_string(
    "\n"
    "Parameters:\n",
    13);
  string__293744df0bfb878b = from_latin_1_string(
    "\n"
    "Options:\n",
    10);
  string__2d7981f4e6602be8 = from_latin_1_string("--", 2);
  string__1a1f5d6080113292 = from_latin_1_string(" VALUE", 6);
  string__eb0400899490d0a9 = from_latin_1_string(" VALUES", 7);
  string__1fe132c840060c77 = from_latin_1_string("Too few arguments for ", 22);
  string__2952791d2723646b = from_latin_1_string("-command!\012", 10);
  string__f0948421cb0e2be3 = from_latin_1_string("Too few arguments!\012", 19);
  func__check_arguments_103 = create_function(entry__check_arguments_103, 0);
  string__e3aee165acc437aa = from_latin_1_string("Too many arguments!\012", 20);
  string__481f572601de82a7 = from_latin_1_string("--help", 6);
  string__d29f58972c488aa7 = from_latin_1_string("--copyright", 11);
  func__check_arguments_177 = create_function(entry__check_arguments_177, 0);
  string__48e824ee4f7a5d6b = from_latin_1_string("--version", 9);
  string__42c4ee3f21a0316f = from_latin_1_string("Invalid option: ", 16);
  string__143aedf103648031 = from_latin_1_string("Invalid argument value for ", 27);
  string__2d7981f4e6002bcf = from_latin_1_string("!\012", 2);
  func__check_arguments_1 = create_function(entry__check_arguments_1, -1);
  func__std__program_commands_1 = create_function(entry__std__program_commands_1, -1);
  string__120ae80b5d007d49 = from_latin_1_string("help", 4);
  func__std__command_parameters_1 = create_function(entry__std__command_parameters_1, -1);
  func__show_commands_3 = create_function(entry__show_commands_3, 0);
  string__c69810bce846f05a = from_latin_1_string("Available commands:", 19);
  string__e65a119686ab55e3 = from_latin_1_string("display help for the specified command", 38);
  string__7cf0276001425531 = from_latin_1_string("copyright", 9);
  string__d9b4d5146ecce23 = from_latin_1_string("display the copyright message", 29);
  string__945c0f9015c3e094 = from_latin_1_string("version", 7);
  string__460a51cfecd67225 = from_latin_1_string("display the version number", 26);
  func__show_commands_1 = create_function(entry__show_commands_1, 0);
  func__std__program_parameters_6 = create_function(entry__std__program_parameters_6, 0);
  string__9e1d476192d899b4 = from_latin_1_string("No command specified!\012", 22);
  func__std__program_parameters_9 = create_function(entry__std__program_parameters_9, 0);
  func__std__program_parameters_17 = create_function(entry__std__program_parameters_17, 0);
  func__std__program_parameters_15 = create_function(entry__std__program_parameters_15, 0);
  func__std__program_parameters_21 = create_function(entry__std__program_parameters_21, 0);
  string__1dc76095d723d587 = from_latin_1_string(
    "Usage:\n"
    "  sigi copyright\n",
    24);
  func__std__program_parameters_27 = create_function(entry__std__program_parameters_27, 0);
  func__std__program_parameters_25 = create_function(entry__std__program_parameters_25, 0);
  string__a15bc662b3bb7e39 = from_latin_1_string(
    "Usage:\n"
    "  sigi help COMMAND\n"
    "\n"
    "Parameter:\n"
    "  COMMAND  the command for which to retrieve help\n",
    89);
  func__std__program_parameters_30 = create_function(entry__std__program_parameters_30, 0);
  string__617a0ed7343fbf40 = from_latin_1_string(
    "Usage:\n"
    "  sigi version\n",
    22);
  func__std__program_parameters_35 = create_function(entry__std__program_parameters_35, 0);
  func__std__program_parameters_33 = create_function(entry__std__program_parameters_33, 0);
  string__19bd6394b9c09d4b = from_latin_1_string("Invalid command name!\012", 22);
  func__std__program_parameters_23 = create_function(entry__std__program_parameters_23, 0);
  func__std__program_parameters_42 = create_function(entry__std__program_parameters_42, 0);
  func__std__program_parameters_19 = create_function(entry__std__program_parameters_19, 0);
  func__std__program_parameters_47 = create_function(entry__std__program_parameters_47, 0);
  func__std__program_parameters_45 = create_function(entry__std__program_parameters_45, 0);
  string__f68d8519ec4e03eb = from_latin_1_string("Invalid arguments!\012", 19);
  func__std__program_parameters_13 = create_function(entry__std__program_parameters_13, 0);
  func__std__program_parameters_7 = create_function(entry__std__program_parameters_7, 0);
  func__std__program_parameters_4 = create_function(entry__std__program_parameters_4, 0);
  func__std__program_parameters_1 = create_function(entry__std__program_parameters_1, -1);
}

static int already_run_phase_3 = false;

EXPORT void phase_3__basic__parameters(void) {
  if (already_run_phase_3) return;
  already_run_phase_3 = true;
  set_module("basic__parameters");
  set_used_namespaces(used_namespaces);
  assign_value(&var._BOOLEAN_OPTION, unique__BOOLEAN_OPTION);
  var.std__VALUED_OPTION = create_future();
  define_single_assign_static("std", "VALUED_OPTION", get__std__VALUED_OPTION, &var.std__VALUED_OPTION);
  var.std__MULTI_VALUED_OPTION = create_future();
  define_single_assign_static("std", "MULTI_VALUED_OPTION", get__std__MULTI_VALUED_OPTION, &var.std__MULTI_VALUED_OPTION);
  var.std__MANDATORY_PARAMETER = create_future();
  define_single_assign_static("std", "MANDATORY_PARAMETER", get__std__MANDATORY_PARAMETER, &var.std__MANDATORY_PARAMETER);
  var.std__OPTIONAL_PARAMETER = create_future();
  define_single_assign_static("std", "OPTIONAL_PARAMETER", get__std__OPTIONAL_PARAMETER, &var.std__OPTIONAL_PARAMETER);
  var.std__SOME_PARAMETERS = create_future();
  define_single_assign_static("std", "SOME_PARAMETERS", get__std__SOME_PARAMETERS, &var.std__SOME_PARAMETERS);
  var.std__MANY_PARAMETERS = create_future();
  define_single_assign_static("std", "MANY_PARAMETERS", get__std__MANY_PARAMETERS, &var.std__MANY_PARAMETERS);
  var.std__copyright = create_future();
  define_single_assign_static("std", "copyright", get__std__copyright, &var.std__copyright);
  var.std__version = create_future();
  define_single_assign_static("std", "version", get__std__version, &var.std__version);
  var.std__extract_options = create_future();
  define_single_assign_static("std", "extract_options", get__std__extract_options, &var.std__extract_options);
  var.std__extract_some_options = create_future();
  define_single_assign_static("std", "extract_some_options", get__std__extract_some_options, &var.std__extract_some_options);
  var.std__program_commands = create_future();
  define_single_assign_static("std", "program_commands", get__std__program_commands, &var.std__program_commands);
  var.std__command_parameters = create_future();
  define_single_assign_static("std", "command_parameters", get__std__command_parameters, &var.std__command_parameters);
  var.std__program_parameters = create_future();
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
  initialize_future(var.std__VALUED_OPTION, unique__std__VALUED_OPTION);
  initialize_future(var.std__MULTI_VALUED_OPTION, unique__std__MULTI_VALUED_OPTION);
  initialize_future(var.std__MANDATORY_PARAMETER, unique__std__MANDATORY_PARAMETER);
  initialize_future(var.std__OPTIONAL_PARAMETER, unique__std__OPTIONAL_PARAMETER);
  initialize_future(var.std__SOME_PARAMETERS, unique__std__SOME_PARAMETERS);
  initialize_future(var.std__MANY_PARAMETERS, unique__std__MANY_PARAMETERS);
  initialize_future(var.std__copyright, func__std__copyright_1);
  initialize_future(var.std__version, func__std__version_1);
  initialize_future(var.std__extract_options, func__std__extract_options_1);
  initialize_future(var.std__extract_some_options, func__std__extract_some_options_1);
  assign_variable(&var._display_table, &func__display_table_1);
  assign_variable(&var._show_version, &func__show_version_1);
  assign_variable(&var._show_copyright, &func__show_copyright_1);
  assign_variable(&var._check_arguments, &func__check_arguments_1);
  initialize_future(var.std__program_commands, func__std__program_commands_1);
  initialize_future(var.std__command_parameters, func__std__command_parameters_1);
  assign_variable(&var._show_commands, &func__show_commands_1);
  initialize_future(var.std__program_parameters, func__std__program_parameters_1);
}

static int already_run_phase_6 = false;

EXPORT void phase_6__basic__parameters(void) {
  if (already_run_phase_6) return;
  already_run_phase_6 = true;
  register_collector(collect__basic__parameters);
}
