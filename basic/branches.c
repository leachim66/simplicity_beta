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
IMPORT void allocate_arguments(void);
IMPORT NODE *from_arguments(int first_idx, int count);
REGISTER int argument_count ASM("ebx");
REGISTER FRAME *arguments ASM("r12");
IMPORT void *node_p;
IMPORT int result_count;
REGISTER NODE *myself ASM("r13");
IMPORT void invalid_arguments_error(void);
IMPORT void invalid_results_error(void);
IMPORT NODE *create_closure(FUNC type, int par_count);
IMPORT NODE *create_future(void);
IMPORT void too_many_results_error(void);
IMPORT NODE *undefined;
IMPORT void initialize_future(NODE *var, NODE *val);
IMPORT NODE *create_cell(void);
typedef struct CELL {
  FUNC type;
  struct ATTRIBUTES *attributes;
  NODE *contents;
} CELL;
IMPORT NODE *create_continuation(void);
IMPORT void too_few_arguments_error(void);
IMPORT NODE *collect_node(NODE *node);
IMPORT void register_module_info(MODULE_INFO *info);
IMPORT void set_module(const char *name);
IMPORT void set_used_namespaces(const char **namespaces);
IMPORT NODE *from_uint32(uint32_t val);
IMPORT void define_single_assign_static(
  const char *namespace, const char *name,
  NODE_GETTER getter, NODE **var_p
);
IMPORT void use_read_only(
  const char *namespace, const char *name,
  NODE_GETTER *getter, NODE_GETTER *get_value_or_future
);
IMPORT void assign_variable(NODE **dest, NODE **var_p);
IMPORT void assign_value(NODE **dest, NODE *val);
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
static NODE_GETTER get__cond;
static NODE_GETTER get_value_or_future__cond;
static NODE_GETTER get__do;
static NODE_GETTER get_value_or_future__do;
static NODE_GETTER get__false;
static NODE_GETTER get_value_or_future__false;
static NODE_GETTER get__for_each;
static NODE_GETTER get_value_or_future__for_each;
static NODE_GETTER get__if;
static NODE_GETTER get_value_or_future__if;
static NODE_GETTER get__is_a_sequence;
static NODE_GETTER get_value_or_future__is_a_sequence;
static NODE_GETTER get__is_a_value_range;
static NODE_GETTER get_value_or_future__is_a_value_range;
static NODE_GETTER get__is_defined;
static NODE_GETTER get_value_or_future__is_defined;
static NODE_GETTER get__is_empty;
static NODE_GETTER get_value_or_future__is_empty;
static NODE_GETTER get__is_undefined;
static NODE_GETTER get_value_or_future__is_undefined;
static NODE_GETTER get__length_of;
static NODE_GETTER get_value_or_future__length_of;
static NODE_GETTER get__lower_bound_of;
static NODE_GETTER get_value_or_future__lower_bound_of;
static NODE_GETTER get__range;
static NODE_GETTER get_value_or_future__range;
static NODE_GETTER get__std__and;
static NODE_GETTER get_value_or_future__std__and;
static NODE_GETTER get__std__equal;
static NODE_GETTER get_value_or_future__std__equal;
static NODE_GETTER get__std__less;
static NODE_GETTER get_value_or_future__std__less;
static NODE_GETTER get__std__negate;
static NODE_GETTER get_value_or_future__std__negate;
static NODE_GETTER get__std__not;
static NODE_GETTER get_value_or_future__std__not;
static NODE_GETTER get__true;
static NODE_GETTER get_value_or_future__true;
static NODE_GETTER get__unless;
static NODE_GETTER get_value_or_future__unless;
static NODE_GETTER get__upper_bound_of;
static NODE_GETTER get_value_or_future__upper_bound_of;
static struct {
  NODE *_cond_list;
  NODE *std__cond;
  NODE *std__case;
  NODE *std__check_case;
} var;
static const char *var_names[] = {
  "cond_list"
};
static NODE *func__1_1;
static void entry__1_1(void);
static FRAME_INFO frame__1_1 = {1, {"args"}};
static NODE *get__std__cond(void) {
  return var.std__cond;
}
static NODE *func__2_1;
static void entry__2_1(void);
static FRAME_INFO frame__2_1 = {1, {"args"}};
static void cont__2_2(void);
static NODE *func__2_3;
static void entry__2_3(void);
static FRAME_INFO frame__2_3 = {3, {"args", "cond_or_body", "body"}};
static void cont__2_4(void);
static void cont__2_5(void);
static void cont__2_6(void);
static NODE *func__2_7;
static void entry__2_7(void);
static FRAME_INFO frame__2_7 = {3, {"body", "cond_or_body", "args"}};
static void cont__2_8(void);
static NODE *func__2_9;
static void entry__2_9(void);
static FRAME_INFO frame__2_9 = {3, {"cond_or_body", "body", "args"}};
static NODE *func__2_10;
static void entry__2_10(void);
static FRAME_INFO frame__2_10 = {1, {"args"}};
static void cont__2_11(void);
static void cont__2_12(void);
static NODE *func__2_13;
static void entry__2_13(void);
static FRAME_INFO frame__2_13 = {1, {"cond_or_body"}};
static NODE *func__3_1;
static void entry__3_1(void);
static FRAME_INFO frame__3_1 = {3, {"expr", "values_and_bodies", "recursive_case"}};
static NODE *func__3_2;
static void entry__3_2(void);
static FRAME_INFO frame__3_2 = {4, {"args", "expr", "recursive_case", "len"}};
static void cont__3_3(void);
static void cont__3_4(void);
static NODE *func__3_5;
static void entry__3_5(void);
static FRAME_INFO frame__3_5 = {4, {"len", "args", "expr", "recursive_case"}};
static void cont__3_6(void);
static NODE *func__3_7;
static void entry__3_7(void);
static FRAME_INFO frame__3_7 = {2, {"args", "body"}};
static void cont__3_8(void);
static NODE *func__3_9;
static void entry__3_9(void);
static FRAME_INFO frame__3_9 = {6, {"args", "expr", "recursive_case", "value", "body", "success"}};
static void cont__3_10(void);
static void cont__3_11(void);
static void cont__3_12(void);
static NODE *func__3_13;
static void entry__3_13(void);
static FRAME_INFO frame__3_13 = {3, {"value", "expr", "success"}};
static NODE *func__3_14;
static void entry__3_14(void);
static FRAME_INFO frame__3_14 = {3, {"value", "expr", "success"}};
static void cont__3_15(void);
static NODE *func__3_16;
static void entry__3_16(void);
static FRAME_INFO frame__3_16 = {3, {"value", "expr", "success"}};
static NODE *func__3_17;
static void entry__3_17(void);
static FRAME_INFO frame__3_17 = {4, {"break", "value", "expr", "success"}};
static NODE *func__3_18;
static void entry__3_18(void);
static FRAME_INFO frame__3_18 = {4, {"sub_value", "expr", "success", "break"}};
static void cont__3_19(void);
static NODE *func__3_20;
static void entry__3_20(void);
static FRAME_INFO frame__3_20 = {1, {"sub_value"}};
static void cont__3_21(void);
static void cont__3_22(void);
static NODE *func__3_23;
static void entry__3_23(void);
static FRAME_INFO frame__3_23 = {4, {"expr", "sub_value", "success", "break"}};
static void cont__3_24(void);
static void cont__3_25(void);
static void cont__3_26(void);
static NODE *func__3_27;
static void entry__3_27(void);
static FRAME_INFO frame__3_27 = {2, {"sub_value", "expr"}};
static void cont__3_28(void);
static void cont__3_29(void);
static void cont__3_30(void);
static void cont__3_31(void);
static NODE *func__3_32;
static void entry__3_32(void);
static FRAME_INFO frame__3_32 = {2, {"success", "break"}};
static NODE *func__3_33;
static void entry__3_33(void);
static FRAME_INFO frame__3_33 = {4, {"sub_value", "expr", "success", "break"}};
static void cont__3_34(void);
static NODE *func__3_35;
static void entry__3_35(void);
static FRAME_INFO frame__3_35 = {2, {"success", "break"}};
static void cont__3_36(void);
static NODE *func__3_37;
static void entry__3_37(void);
static FRAME_INFO frame__3_37 = {3, {"value", "expr", "success"}};
static void cont__3_38(void);
static NODE *func__3_39;
static void entry__3_39(void);
static FRAME_INFO frame__3_39 = {3, {"expr", "value", "success"}};
static void cont__3_40(void);
static void cont__3_41(void);
static void cont__3_42(void);
static NODE *func__3_43;
static void entry__3_43(void);
static FRAME_INFO frame__3_43 = {2, {"value", "expr"}};
static void cont__3_44(void);
static void cont__3_45(void);
static void cont__3_46(void);
static void cont__3_47(void);
static NODE *func__3_48;
static void entry__3_48(void);
static FRAME_INFO frame__3_48 = {1, {"success"}};
static NODE *func__3_49;
static void entry__3_49(void);
static FRAME_INFO frame__3_49 = {3, {"value", "expr", "success"}};
static void cont__3_50(void);
static NODE *func__3_51;
static void entry__3_51(void);
static FRAME_INFO frame__3_51 = {1, {"success"}};
static NODE *func__3_52;
static void entry__3_52(void);
static FRAME_INFO frame__3_52 = {2, {"expr", "success"}};
static void cont__3_53(void);
static NODE *func__3_54;
static void entry__3_54(void);
static FRAME_INFO frame__3_54 = {1, {"success"}};
static void cont__3_55(void);
static NODE *func__3_56;
static void entry__3_56(void);
static FRAME_INFO frame__3_56 = {2, {"recursive_case", "args"}};
static void cont__3_57(void);
static void cont__3_58(void);
static NODE *get__std__case(void) {
  return var.std__case;
}
static NODE *func__4_1;
static void entry__4_1(void);
static FRAME_INFO frame__4_1 = {4, {"expr", "check", "values_and_bodies", "recursive_check_case"}};
static NODE *func__4_2;
static void entry__4_2(void);
static FRAME_INFO frame__4_2 = {5, {"args", "check", "expr", "recursive_check_case", "len"}};
static void cont__4_3(void);
static void cont__4_4(void);
static NODE *func__4_5;
static void entry__4_5(void);
static FRAME_INFO frame__4_5 = {5, {"len", "args", "check", "expr", "recursive_check_case"}};
static void cont__4_6(void);
static NODE *func__4_7;
static void entry__4_7(void);
static FRAME_INFO frame__4_7 = {2, {"args", "body"}};
static void cont__4_8(void);
static NODE *func__4_9;
static void entry__4_9(void);
static FRAME_INFO frame__4_9 = {7, {"args", "check", "expr", "recursive_check_case", "value", "body", "success"}};
static void cont__4_10(void);
static void cont__4_11(void);
static void cont__4_12(void);
static NODE *func__4_13;
static void entry__4_13(void);
static FRAME_INFO frame__4_13 = {4, {"value", "check", "expr", "success"}};
static NODE *func__4_14;
static void entry__4_14(void);
static FRAME_INFO frame__4_14 = {5, {"break", "value", "check", "expr", "success"}};
static NODE *func__4_15;
static void entry__4_15(void);
static FRAME_INFO frame__4_15 = {5, {"sub_value", "check", "expr", "success", "break"}};
static void cont__4_16(void);
static NODE *func__4_17;
static void entry__4_17(void);
static FRAME_INFO frame__4_17 = {2, {"success", "break"}};
static void cont__4_18(void);
static NODE *func__4_19;
static void entry__4_19(void);
static FRAME_INFO frame__4_19 = {4, {"check", "expr", "value", "success"}};
static void cont__4_20(void);
static NODE *func__4_21;
static void entry__4_21(void);
static FRAME_INFO frame__4_21 = {1, {"success"}};
static void cont__4_22(void);
static NODE *func__4_23;
static void entry__4_23(void);
static FRAME_INFO frame__4_23 = {2, {"recursive_check_case", "args"}};
static void cont__4_24(void);
static void cont__4_25(void);
static NODE *get__std__check_case(void) {
  return var.std__check_case;
}
void run__basic__branches(void);

static CONTINUATION_INFO continuation_info[] = {
  {run__basic__branches, NULL, },
  {entry__1_1, NULL, 53, 53, 3, 16},
  {entry__2_10, NULL, 61, 61, 57, 57},
  {cont__2_11, &frame__2_10, 61, 61, 43, 58},
  {cont__2_12, &frame__2_10, 61, 61, 33, 58},
  {entry__2_9, NULL, 61, 61, 11, 58},
  {entry__2_13, NULL, 63, 63, 11, 22},
  {entry__2_7, NULL, 60, 60, 9, 23},
  {cont__2_8, &frame__2_7, 59, 63, 7, 23},
  {entry__2_3, NULL, 57, 57, 5, 11},
  {cont__2_4, &frame__2_3, 57, 57, 5, 33},
  {cont__2_5, &frame__2_3, 58, 58, 8, 30},
  {cont__2_6, &frame__2_3, 58, 63, 5, 24},
  {entry__2_1, NULL, 56, 56, 10, 22},
  {cont__2_2, &frame__2_1, 56, 63, 3, 25},
  {entry__3_7, NULL, 102, 102, 11, 23},
  {cont__3_8, &frame__3_7, 103, 103, 11, 14},
  {entry__3_20, NULL, 115, 115, 49, 74},
  {cont__3_21, &frame__3_20, 115, 115, 49, 74},
  {entry__3_27, NULL, 119, 119, 39, 63},
  {cont__3_28, &frame__3_27, 119, 119, 31, 63},
  {cont__3_29, &frame__3_27, 119, 119, 31, 63},
  {cont__3_30, &frame__3_27, 119, 119, 31, 63},
  {entry__3_32, NULL, 122, 122, 31, 35},
  {entry__3_23, NULL, 118, 118, 39, 63},
  {cont__3_24, &frame__3_23, 118, 118, 31, 63},
  {cont__3_25, &frame__3_23, 118, 118, 31, 63},
  {cont__3_26, &frame__3_23, 117, 119, 29, 62},
  {cont__3_31, &frame__3_23, 116, 122, 27, 36},
  {entry__3_35, NULL, 126, 126, 29, 33},
  {entry__3_33, NULL, 124, 124, 30, 46},
  {cont__3_34, &frame__3_33, 124, 126, 27, 33},
  {entry__3_18, NULL, 115, 115, 25, 44},
  {cont__3_19, &frame__3_18, 115, 115, 25, 74},
  {cont__3_22, &frame__3_18, 114, 126, 23, 35},
  {entry__3_17, NULL, 113, 126, 21, 36},
  {cont__3_36, &frame__3_17, 126, 126, 36, 36},
  {entry__3_16, NULL, 112, 126, 19, 37},
  {entry__3_14, NULL, 111, 111, 20, 38},
  {cont__3_15, &frame__3_14, 111, 126, 17, 38},
  {entry__3_43, NULL, 131, 131, 31, 51},
  {cont__3_44, &frame__3_43, 131, 131, 23, 51},
  {cont__3_45, &frame__3_43, 131, 131, 23, 51},
  {cont__3_46, &frame__3_43, 131, 131, 23, 51},
  {entry__3_48, NULL, 133, 133, 35, 35},
  {entry__3_39, NULL, 130, 130, 31, 51},
  {cont__3_40, &frame__3_39, 130, 130, 23, 51},
  {cont__3_41, &frame__3_39, 130, 130, 23, 51},
  {cont__3_42, &frame__3_39, 129, 131, 21, 50},
  {cont__3_47, &frame__3_39, 128, 133, 19, 36},
  {entry__3_37, NULL, 127, 127, 20, 41},
  {cont__3_38, &frame__3_37, 127, 133, 17, 37},
  {entry__3_51, NULL, 135, 135, 49, 49},
  {entry__3_49, NULL, 135, 135, 22, 34},
  {cont__3_50, &frame__3_49, 135, 135, 19, 49},
  {entry__3_13, NULL, 110, 135, 15, 50},
  {entry__3_54, NULL, 137, 137, 49, 49},
  {entry__3_52, NULL, 137, 137, 18, 34},
  {cont__3_53, &frame__3_52, 137, 137, 15, 49},
  {entry__3_56, NULL, 138, 138, 57, 57},
  {cont__3_57, &frame__3_56, 138, 138, 43, 58},
  {cont__3_58, &frame__3_56, 138, 138, 28, 58},
  {entry__3_9, NULL, 105, 105, 11, 24},
  {cont__3_10, &frame__3_9, 106, 106, 11, 23},
  {cont__3_11, &frame__3_9, 109, 109, 13, 28},
  {cont__3_12, &frame__3_9, 108, 137, 11, 50},
  {cont__3_55, &frame__3_9, 138, 138, 11, 58},
  {entry__3_5, NULL, 101, 101, 9, 16},
  {cont__3_6, &frame__3_5, 100, 138, 7, 59},
  {entry__3_2, NULL, 98, 98, 5, 24},
  {cont__3_3, &frame__3_2, 99, 99, 8, 14},
  {cont__3_4, &frame__3_2, 99, 138, 5, 60},
  {entry__3_1, NULL, 140, 140, 3, 34},
  {entry__4_7, NULL, 176, 176, 11, 23},
  {cont__4_8, &frame__4_7, 177, 177, 11, 14},
  {entry__4_17, NULL, 188, 188, 21, 25},
  {entry__4_15, NULL, 186, 186, 22, 42},
  {cont__4_16, &frame__4_15, 186, 188, 19, 25},
  {entry__4_14, NULL, 185, 188, 17, 26},
  {cont__4_18, &frame__4_14, 188, 188, 26, 26},
  {entry__4_13, NULL, 184, 188, 15, 27},
  {entry__4_21, NULL, 190, 190, 49, 49},
  {entry__4_19, NULL, 190, 190, 18, 34},
  {cont__4_20, &frame__4_19, 190, 190, 15, 49},
  {entry__4_23, NULL, 191, 191, 63, 63},
  {cont__4_24, &frame__4_23, 191, 191, 49, 64},
  {cont__4_25, &frame__4_23, 191, 191, 28, 64},
  {entry__4_9, NULL, 179, 179, 11, 24},
  {cont__4_10, &frame__4_9, 180, 180, 11, 23},
  {cont__4_11, &frame__4_9, 183, 183, 13, 31},
  {cont__4_12, &frame__4_9, 182, 190, 11, 50},
  {cont__4_22, &frame__4_9, 191, 191, 11, 64},
  {entry__4_5, NULL, 175, 175, 9, 16},
  {cont__4_6, &frame__4_5, 174, 191, 7, 65},
  {entry__4_2, NULL, 172, 172, 5, 24},
  {cont__4_3, &frame__4_2, 173, 173, 8, 14},
  {cont__4_4, &frame__4_2, 173, 191, 5, 66},
  {entry__4_1, NULL, 193, 193, 3, 40}
};

union NODE {
  struct {
    FUNC type;
    ATTRIBUTES *attributes;
  };
  CONTINUATION continuation;
  CLOSURE closure;
};
static NODE *number__0;
static NODE *number__3;
static NODE *number__1;
static NODE *number__2;

static const char *used_namespaces[] = {
  "std",
  NULL
};

static MODULE_INFO module_info = {
  NULL,
  "basic__branches",
  continuation_info,
  sizeof(continuation_info)/sizeof(CONTINUATION_INFO),
  (NODE **)&var,
  var_names,
  sizeof(var_names)/sizeof(const char *),
  used_namespaces,
  {DEBUG_FILENAME("basic/branches.sim")}
};

/******
C O D E
******/

static int already_run = false;

EXPORT void run__basic__branches(void) {
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
static void entry__1_1(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // args: 0
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 53: cond_list args
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* args */;
  result_count = frame->caller_result_count;
  myself = var._cond_list;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__2_10(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // args: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* args */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 61: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__2_11;
}
static void cont__2_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 61: ... range(args 2 -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* args */;
  arguments->slots[1] = number__2;
  arguments->slots[2] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__2_12;
}
static void cont__2_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 61: ... cond_list range(args 2 -1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = var._cond_list;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__2_9(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // cond_or_body: 0
  // body: 1
  // args: 2
  frame->slots[0] = myself->closure.frame->slots[1]; /* cond_or_body */
  frame->slots[1] = myself->closure.frame->slots[0]; /* body */
  frame->slots[2] = myself->closure.frame->slots[2]; /* args */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 61: ... : cond_list range(args 2 -1)
  frame->slots[3] /* temp__1 */ = create_closure(entry__2_10, 0);
  // 61: if cond_or_body body: cond_list range(args 2 -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* cond_or_body */;
  arguments->slots[1] = frame->slots[1] /* body */;
  arguments->slots[2] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__2_13(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // cond_or_body: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* cond_or_body */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 63: cond_or_body
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* cond_or_body */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__2_7(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // body: 0
  // cond_or_body: 1
  // args: 2
  frame->slots[0] = myself->closure.frame->slots[2]; /* body */
  frame->slots[1] = myself->closure.frame->slots[1]; /* cond_or_body */
  frame->slots[2] = myself->closure.frame->slots[0]; /* args */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 60: body.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* body */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__2_8;
}
static void cont__2_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 60: ... :
  // 61:   if cond_or_body body: cond_list range(args 2 -1)
  frame->slots[4] /* temp__2 */ = create_closure(entry__2_9, 0);
  // 62: :
  // 63:   cond_or_body
  frame->slots[5] /* temp__3 */ = create_closure(entry__2_13, 0);
  // 59: if
  // 60:   body.is_defined:
  // 61:     if cond_or_body body: cond_list range(args 2 -1)
  // 62:   :
  // 63:     cond_or_body
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
static void entry__2_3(void) {
  allocate_initialized_frame_gc(1, 6);
  // slot allocations:
  // args: 0
  // cond_or_body: 1
  // body: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* args */
  frame->slots[1] /* cond_or_body */ = create_future();
  frame->slots[2] /* body */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 57: args(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* args */;
  func = myself->type;
  frame->cont = cont__2_4;
}
static void cont__2_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 57: args(1) $cond_or_body? $body?
  argument_count = 0;
  arguments = node_p;
  result_count = -1;
  myself = frame->slots[5] /* temp__3 */;
  func = myself->type;
  frame->cont = cont__2_5;
}
static void cont__2_5(void) {
  if (argument_count > 2) {
    too_many_results_error();
    return;
  }
  switch(argument_count) {
    default: frame->slots[4] /* temp__2 */ = arguments->slots[1];
    case 1: frame->slots[3] /* temp__1 */ = arguments->slots[0];
    case 0:;
  }
  switch(argument_count) {
    case 0: frame->slots[3] /* temp__1 */ = undefined;
    case 1: frame->slots[4] /* temp__2 */ = undefined;
  }
  // 57: ... cond_or_body
  initialize_future(frame->slots[1] /* cond_or_body */, frame->slots[3] /* temp__1 */);
  // 57: ... body
  initialize_future(frame->slots[2] /* body */, frame->slots[4] /* temp__2 */);
  // 58: ... cond_or_body.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* cond_or_body */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__2_6;
}
static void cont__2_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 58: ... : # if not it's the default case
  // 59:   if
  // 60:     body.is_defined:
  // 61:       if cond_or_body body: cond_list range(args 2 -1)
  // 62:     :
  // 63:       cond_or_body
  frame->slots[4] /* temp__2 */ = create_closure(entry__2_7, 0);
  // 58: if cond_or_body.is_defined: # if not it's the default case
  // 59:   if
  // 60:     body.is_defined:
  // 61:       if cond_or_body body: cond_list range(args 2 -1)
  // 62:     :
  // 63:       cond_or_body
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__2_1(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // args: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 56: ... args.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* args */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__2_2;
}
static void cont__2_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 56: ... :
  // 57:   args(1) $cond_or_body? $body?
  // 58:   if cond_or_body.is_defined: # if not it's the default case
  // 59:     if
  // 60:       body.is_defined:
  // 61:         if cond_or_body body: cond_list range(args 2 -1)
  // 62:       :
  // 63:         cond_or_body
  frame->slots[2] /* temp__2 */ = create_closure(entry__2_3, 0);
  // 56: unless args.is_empty:
  // 57:   args(1) $cond_or_body? $body?
  // 58:   if cond_or_body.is_defined: # if not it's the default case
  // 59:     if
  // 60:       body.is_defined:
  // 61:         if cond_or_body body: cond_list range(args 2 -1)
  // 62:       :
  // 63:         cond_or_body
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__3_56(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // recursive_case: 0
  // args: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* recursive_case */
  frame->slots[1] = myself->closure.frame->slots[0]; /* args */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 138: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__3_57;
}
static void cont__3_57(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 138: ... range(args 3 -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* args */;
  arguments->slots[1] = number__3;
  arguments->slots[2] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__3_58;
}
static void cont__3_58(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 138: ... recursive_case range(args 3 -1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* recursive_case */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__3_7(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // args: 0
  // body: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* args */
  frame->slots[1] /* body */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 102: $body args(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* args */;
  func = myself->type;
  frame->cont = cont__3_8;
}
static void cont__3_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* body */, arguments->slots[0]);
  // 103: body
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* body */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__3_9(void) {
  allocate_initialized_frame_gc(3, 9);
  // slot allocations:
  // args: 0
  // expr: 1
  // recursive_case: 2
  // value: 3
  // body: 4
  // success: 5
  frame->slots[0] = myself->closure.frame->slots[1]; /* args */
  frame->slots[1] = myself->closure.frame->slots[2]; /* expr */
  frame->slots[2] = myself->closure.frame->slots[3]; /* recursive_case */
  frame->slots[3] /* value */ = create_future();
  frame->slots[4] /* body */ = create_future();
  frame->slots[5] /* success */ = create_cell();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 105: $value args(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* args */;
  func = myself->type;
  frame->cont = cont__3_10;
}
static void cont__3_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* value */, arguments->slots[0]);
  // 106: $body args(2)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = frame->slots[0] /* args */;
  func = myself->type;
  frame->cont = cont__3_11;
}
static void cont__3_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* body */, arguments->slots[0]);
  // 107: $$success false
  ((CELL *)frame->slots[5])->contents /* success */ = get__false();
  // 109: value.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* value */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__3_12;
}
static void cont__3_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 109: ... :
  // 110:   cond
  // 111:     -> value.is_a_sequence:
  // 112:       do: (-> break)
  // 113:         for_each value: (sub_value)
  // 114:           if
  // 115:             sub_value.is_defined && sub_value.is_a_value_range:
  // 116:               if
  // 117:                 &&
  // 118:                   expr >= lower_bound_of(sub_value)
  // ...
  frame->slots[7] /* temp__2 */ = create_closure(entry__3_13, 0);
  // 136: :
  // 137:   if expr.is_undefined: !success true
  frame->slots[8] /* temp__3 */ = create_closure(entry__3_52, 0);
  // 108: if
  // 109:   value.is_defined:
  // 110:     cond
  // 111:       -> value.is_a_sequence:
  // 112:         do: (-> break)
  // 113:           for_each value: (sub_value)
  // 114:             if
  // 115:               sub_value.is_defined && sub_value.is_a_value_range:
  // 116:                 if
  // 117:                   &&
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  arguments->slots[2] = frame->slots[8] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__3_55;
}
static void entry__3_54(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // success: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* success */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 137: ... !success true
  ((CELL *)frame->slots[0])->contents /* success */ = get__true();
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__3_51(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // success: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* success */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 135: ... !success true
  ((CELL *)frame->slots[0])->contents /* success */ = get__true();
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__3_48(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // success: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* success */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 133: !success true
  ((CELL *)frame->slots[0])->contents /* success */ = get__true();
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__3_39(void) {
  allocate_initialized_frame_gc(3, 9);
  // slot allocations:
  // expr: 0
  // value: 1
  // success: 2
  frame->slots[0] = myself->closure.frame->slots[1]; /* expr */
  frame->slots[1] = myself->closure.frame->slots[0]; /* value */
  frame->slots[2] = myself->closure.frame->slots[2]; /* success */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 130: ... lower_bound_of(value)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* value */;
  result_count = 1;
  myself = get__lower_bound_of();
  func = myself->type;
  frame->cont = cont__3_40;
}
static void cont__3_40(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__4 */ = arguments->slots[0];
  // 130: expr >= lower_bound_of(value)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* expr */;
  arguments->slots[1] = frame->slots[6] /* temp__4 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__3_41;
}
static void cont__3_41(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 130: expr >= lower_bound_of(value)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__3_42;
}
static void cont__3_42(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 131: expr <= upper_bound_of(value)
  frame->slots[7] /* temp__5 */ = create_closure(entry__3_43, 0);
  // 129: &&
  // 130:   expr >= lower_bound_of(value)
  // 131:   expr <= upper_bound_of(value)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__5 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__3_47;
}
static void entry__3_43(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // value: 0
  // expr: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* value */
  frame->slots[1] = myself->closure.frame->slots[0]; /* expr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 131: ... upper_bound_of(value)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* value */;
  result_count = 1;
  myself = get__upper_bound_of();
  func = myself->type;
  frame->cont = cont__3_44;
}
static void cont__3_44(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 131: expr <= upper_bound_of(value)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  arguments->slots[1] = frame->slots[1] /* expr */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__3_45;
}
static void cont__3_45(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 131: expr <= upper_bound_of(value)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__3_46;
}
static void cont__3_46(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 131: expr <= upper_bound_of(value)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__3_47(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 132: :
  // 133:   !success true
  frame->slots[8] /* temp__6 */ = create_closure(entry__3_48, 0);
  // 128: if
  // 129:   &&
  // 130:     expr >= lower_bound_of(value)
  // 131:     expr <= upper_bound_of(value)
  // 132:   :
  // 133:     !success true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__6 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__3_17(void) {
  allocate_initialized_frame_gc(4, 5);
  // slot allocations:
  // break: 0
  // value: 1
  // expr: 2
  // success: 3
  frame->slots[0] /* break */ = create_continuation();
  frame->slots[1] = myself->closure.frame->slots[0]; /* value */
  frame->slots[2] = myself->closure.frame->slots[1]; /* expr */
  frame->slots[3] = myself->closure.frame->slots[2]; /* success */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 113: ... : (sub_value)
  // 114:   if
  // 115:     sub_value.is_defined && sub_value.is_a_value_range:
  // 116:       if
  // 117:         &&
  // 118:           expr >= lower_bound_of(sub_value)
  // 119:           expr <= upper_bound_of(sub_value)
  // 120:         :
  // 121:           !success true
  // 122:           break
  // ...
  frame->slots[4] /* temp__1 */ = create_closure(entry__3_18, 1);
  // 113: for_each value: (sub_value)
  // 114:   if
  // 115:     sub_value.is_defined && sub_value.is_a_value_range:
  // 116:       if
  // 117:         &&
  // 118:           expr >= lower_bound_of(sub_value)
  // 119:           expr <= upper_bound_of(sub_value)
  // 120:         :
  // 121:           !success true
  // 122:           break
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* value */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__3_36;
}
static void entry__3_35(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // success: 0
  // break: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* success */
  frame->slots[1] = myself->closure.frame->slots[3]; /* break */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 125: !success true
  ((CELL *)frame->slots[0])->contents /* success */ = get__true();
  // 126: break
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* break */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__3_32(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // success: 0
  // break: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* success */
  frame->slots[1] = myself->closure.frame->slots[3]; /* break */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 121: !success true
  ((CELL *)frame->slots[0])->contents /* success */ = get__true();
  // 122: break
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* break */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__3_23(void) {
  allocate_initialized_frame_gc(4, 10);
  // slot allocations:
  // expr: 0
  // sub_value: 1
  // success: 2
  // break: 3
  frame->slots[0] = myself->closure.frame->slots[1]; /* expr */
  frame->slots[1] = myself->closure.frame->slots[0]; /* sub_value */
  frame->slots[2] = myself->closure.frame->slots[2]; /* success */
  frame->slots[3] = myself->closure.frame->slots[3]; /* break */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 118: ... lower_bound_of(sub_value)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* sub_value */;
  result_count = 1;
  myself = get__lower_bound_of();
  func = myself->type;
  frame->cont = cont__3_24;
}
static void cont__3_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__4 */ = arguments->slots[0];
  // 118: expr >= lower_bound_of(sub_value)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* expr */;
  arguments->slots[1] = frame->slots[7] /* temp__4 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__3_25;
}
static void cont__3_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 118: expr >= lower_bound_of(sub_value)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__3 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__3_26;
}
static void cont__3_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 119: expr <= upper_bound_of(sub_value)
  frame->slots[8] /* temp__5 */ = create_closure(entry__3_27, 0);
  // 117: &&
  // 118:   expr >= lower_bound_of(sub_value)
  // 119:   expr <= upper_bound_of(sub_value)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  arguments->slots[1] = frame->slots[8] /* temp__5 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__3_31;
}
static void entry__3_27(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // sub_value: 0
  // expr: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* sub_value */
  frame->slots[1] = myself->closure.frame->slots[0]; /* expr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 119: ... upper_bound_of(sub_value)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* sub_value */;
  result_count = 1;
  myself = get__upper_bound_of();
  func = myself->type;
  frame->cont = cont__3_28;
}
static void cont__3_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 119: expr <= upper_bound_of(sub_value)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  arguments->slots[1] = frame->slots[1] /* expr */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__3_29;
}
static void cont__3_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 119: expr <= upper_bound_of(sub_value)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__3_30;
}
static void cont__3_30(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 119: expr <= upper_bound_of(sub_value)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__3_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 120: :
  // 121:   !success true
  // 122:   break
  frame->slots[9] /* temp__6 */ = create_closure(entry__3_32, 0);
  // 116: if
  // 117:   &&
  // 118:     expr >= lower_bound_of(sub_value)
  // 119:     expr <= upper_bound_of(sub_value)
  // 120:   :
  // 121:     !success true
  // 122:     break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[9] /* temp__6 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__3_33(void) {
  allocate_initialized_frame_gc(4, 6);
  // slot allocations:
  // sub_value: 0
  // expr: 1
  // success: 2
  // break: 3
  frame->slots[0] = myself->closure.frame->slots[0]; /* sub_value */
  frame->slots[1] = myself->closure.frame->slots[1]; /* expr */
  frame->slots[2] = myself->closure.frame->slots[2]; /* success */
  frame->slots[3] = myself->closure.frame->slots[3]; /* break */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 124: ... sub_value == expr
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* sub_value */;
  arguments->slots[1] = frame->slots[1] /* expr */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__3_34;
}
static void cont__3_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 124: ... :
  // 125:   !success true
  // 126:   break
  frame->slots[5] /* temp__2 */ = create_closure(entry__3_35, 0);
  // 124: if sub_value == expr:
  // 125:   !success true
  // 126:   break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__3_18(void) {
  allocate_initialized_frame_gc(4, 9);
  // slot allocations:
  // sub_value: 0
  // expr: 1
  // success: 2
  // break: 3
  frame->slots[1] = myself->closure.frame->slots[2]; /* expr */
  frame->slots[2] = myself->closure.frame->slots[3]; /* success */
  frame->slots[3] = myself->closure.frame->slots[0]; /* break */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 115: sub_value.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* sub_value */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__3_19;
}
static void cont__3_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 115: ... sub_value.is_a_value_range
  frame->slots[6] /* temp__3 */ = create_closure(entry__3_20, 0);
  // 115: sub_value.is_defined && sub_value.is_a_value_range
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__3_22;
}
static void entry__3_20(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // sub_value: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* sub_value */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 115: ... sub_value.is_a_value_range
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* sub_value */;
  result_count = 1;
  myself = get__is_a_value_range();
  func = myself->type;
  frame->cont = cont__3_21;
}
static void cont__3_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 115: ... sub_value.is_a_value_range
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__3_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 115: ... :
  // 116:   if
  // 117:     &&
  // 118:       expr >= lower_bound_of(sub_value)
  // 119:       expr <= upper_bound_of(sub_value)
  // 120:     :
  // 121:       !success true
  // 122:       break
  frame->slots[7] /* temp__4 */ = create_closure(entry__3_23, 0);
  // 123: :
  // 124:   if sub_value == expr:
  // 125:     !success true
  // 126:     break
  frame->slots[8] /* temp__5 */ = create_closure(entry__3_33, 0);
  // 114: if
  // 115:   sub_value.is_defined && sub_value.is_a_value_range:
  // 116:     if
  // 117:       &&
  // 118:         expr >= lower_bound_of(sub_value)
  // 119:         expr <= upper_bound_of(sub_value)
  // 120:       :
  // 121:         !success true
  // 122:         break
  // 123:   :
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__4 */;
  arguments->slots[2] = frame->slots[8] /* temp__5 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__3_36(void) {
  myself = frame->slots[0] /* break */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__3_16(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // value: 0
  // expr: 1
  // success: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* value */
  frame->slots[1] = myself->closure.frame->slots[1]; /* expr */
  frame->slots[2] = myself->closure.frame->slots[2]; /* success */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 112: ... : (-> break)
  // 113:   for_each value: (sub_value)
  // 114:     if
  // 115:       sub_value.is_defined && sub_value.is_a_value_range:
  // 116:         if
  // 117:           &&
  // 118:             expr >= lower_bound_of(sub_value)
  // 119:             expr <= upper_bound_of(sub_value)
  // 120:           :
  // 121:             !success true
  // ...
  frame->slots[3] /* temp__1 */ = create_closure(entry__3_17, 0);
  // 112: do: (-> break)
  // 113:   for_each value: (sub_value)
  // 114:     if
  // 115:       sub_value.is_defined && sub_value.is_a_value_range:
  // 116:         if
  // 117:           &&
  // 118:             expr >= lower_bound_of(sub_value)
  // 119:             expr <= upper_bound_of(sub_value)
  // 120:           :
  // 121:             !success true
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__do();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__3_14(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // value: 0
  // expr: 1
  // success: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* value */
  frame->slots[1] = myself->closure.frame->slots[1]; /* expr */
  frame->slots[2] = myself->closure.frame->slots[2]; /* success */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 111: ... value.is_a_sequence
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* value */;
  result_count = 1;
  myself = get__is_a_sequence();
  func = myself->type;
  frame->cont = cont__3_15;
}
static void cont__3_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 111: ... :
  // 112:   do: (-> break)
  // 113:     for_each value: (sub_value)
  // 114:       if
  // 115:         sub_value.is_defined && sub_value.is_a_value_range:
  // 116:           if
  // 117:             &&
  // 118:               expr >= lower_bound_of(sub_value)
  // 119:               expr <= upper_bound_of(sub_value)
  // 120:             :
  // ...
  frame->slots[4] /* temp__2 */ = create_closure(entry__3_16, 0);
  // 111: -> value.is_a_sequence:
  // 112:   do: (-> break)
  // 113:     for_each value: (sub_value)
  // 114:       if
  // 115:         sub_value.is_defined && sub_value.is_a_value_range:
  // 116:           if
  // 117:             &&
  // 118:               expr >= lower_bound_of(sub_value)
  // 119:               expr <= upper_bound_of(sub_value)
  // 120:             :
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__3_37(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // value: 0
  // expr: 1
  // success: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* value */
  frame->slots[1] = myself->closure.frame->slots[1]; /* expr */
  frame->slots[2] = myself->closure.frame->slots[2]; /* success */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 127: ... value.is_a_value_range
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* value */;
  result_count = 1;
  myself = get__is_a_value_range();
  func = myself->type;
  frame->cont = cont__3_38;
}
static void cont__3_38(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 127: ... :
  // 128:   if
  // 129:     &&
  // 130:       expr >= lower_bound_of(value)
  // 131:       expr <= upper_bound_of(value)
  // 132:     :
  // 133:       !success true
  frame->slots[4] /* temp__2 */ = create_closure(entry__3_39, 0);
  // 127: -> value.is_a_value_range:
  // 128:   if
  // 129:     &&
  // 130:       expr >= lower_bound_of(value)
  // 131:       expr <= upper_bound_of(value)
  // 132:     :
  // 133:       !success true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__3_49(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // value: 0
  // expr: 1
  // success: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* value */
  frame->slots[1] = myself->closure.frame->slots[1]; /* expr */
  frame->slots[2] = myself->closure.frame->slots[2]; /* success */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 135: ... value == expr
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* value */;
  arguments->slots[1] = frame->slots[1] /* expr */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__3_50;
}
static void cont__3_50(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 135: ... : !success true
  frame->slots[4] /* temp__2 */ = create_closure(entry__3_51, 0);
  // 135: if value == expr: !success true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__3_13(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // value: 0
  // expr: 1
  // success: 2
  frame->slots[0] = myself->closure.frame->slots[3]; /* value */
  frame->slots[1] = myself->closure.frame->slots[1]; /* expr */
  frame->slots[2] = myself->closure.frame->slots[5]; /* success */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 111: -> value.is_a_sequence:
  // 112:   do: (-> break)
  // 113:     for_each value: (sub_value)
  // 114:       if
  // 115:         sub_value.is_defined && sub_value.is_a_value_range:
  // 116:           if
  // 117:             &&
  // 118:               expr >= lower_bound_of(sub_value)
  // 119:               expr <= upper_bound_of(sub_value)
  // 120:             :
  // ...
  frame->slots[3] /* temp__1 */ = create_closure(entry__3_14, 0);
  // 127: -> value.is_a_value_range:
  // 128:   if
  // 129:     &&
  // 130:       expr >= lower_bound_of(value)
  // 131:       expr <= upper_bound_of(value)
  // 132:     :
  // 133:       !success true
  frame->slots[4] /* temp__2 */ = create_closure(entry__3_37, 0);
  // 134: :
  // 135:   if value == expr: !success true
  frame->slots[5] /* temp__3 */ = create_closure(entry__3_49, 0);
  // 110: cond
  // 111:   -> value.is_a_sequence:
  // 112:     do: (-> break)
  // 113:       for_each value: (sub_value)
  // 114:         if
  // 115:           sub_value.is_defined && sub_value.is_a_value_range:
  // 116:             if
  // 117:               &&
  // 118:                 expr >= lower_bound_of(sub_value)
  // 119:                 expr <= upper_bound_of(sub_value)
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
static void entry__3_52(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // expr: 0
  // success: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* expr */
  frame->slots[1] = myself->closure.frame->slots[5]; /* success */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 137: ... expr.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* expr */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__3_53;
}
static void cont__3_53(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 137: ... : !success true
  frame->slots[3] /* temp__2 */ = create_closure(entry__3_54, 0);
  // 137: if expr.is_undefined: !success true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__3_55(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 138: ... : recursive_case range(args 3 -1)
  frame->slots[6] /* temp__1 */ = create_closure(entry__3_56, 0);
  // 138: if success body: recursive_case range(args 3 -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[5])->contents /* success */;
  arguments->slots[1] = frame->slots[4] /* body */;
  arguments->slots[2] = frame->slots[6] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__3_5(void) {
  allocate_initialized_frame_gc(4, 7);
  // slot allocations:
  // len: 0
  // args: 1
  // expr: 2
  // recursive_case: 3
  frame->slots[0] = myself->closure.frame->slots[3]; /* len */
  frame->slots[1] = myself->closure.frame->slots[0]; /* args */
  frame->slots[2] = myself->closure.frame->slots[1]; /* expr */
  frame->slots[3] = myself->closure.frame->slots[2]; /* recursive_case */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 101: len == 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* len */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__3_6;
}
static void cont__3_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 101: ... :
  // 102:   $body args(1)
  // 103:   body
  frame->slots[5] /* temp__2 */ = create_closure(entry__3_7, 0);
  // 104: :
  // 105:   $value args(1)
  // 106:   $body args(2)
  // 107:   $$success false
  // 108:   if
  // 109:     value.is_defined:
  // 110:       cond
  // 111:         -> value.is_a_sequence:
  // 112:           do: (-> break)
  // 113:             for_each value: (sub_value)
  // ...
  frame->slots[6] /* temp__3 */ = create_closure(entry__3_9, 0);
  // 100: if
  // 101:   len == 1:
  // 102:     $body args(1)
  // 103:     body
  // 104:   :
  // 105:     $value args(1)
  // 106:     $body args(2)
  // 107:     $$success false
  // 108:     if
  // 109:       value.is_defined:
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
static void entry__3_2(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // args: 0
  // expr: 1
  // recursive_case: 2
  // len: 3
  frame->slots[1] = myself->closure.frame->slots[0]; /* expr */
  frame->slots[2] = myself->closure.frame->slots[2]; /* recursive_case */
  frame->slots[3] /* len */ = create_future();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 98: $len length_of(args)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* args */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__3_3;
}
static void cont__3_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* len */, arguments->slots[0]);
  // 99: ... len > 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = frame->slots[3] /* len */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__3_4;
}
static void cont__3_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  //  99: ... :
  // 100:   if
  // 101:     len == 1:
  // 102:       $body args(1)
  // 103:       body
  // 104:     :
  // 105:       $value args(1)
  // 106:       $body args(2)
  // 107:       $$success false
  // 108:       if
  // ...
  frame->slots[5] /* temp__2 */ = create_closure(entry__3_5, 0);
  //  99: if len > 0:
  // 100:   if
  // 101:     len == 1:
  // 102:       $body args(1)
  // 103:       body
  // 104:     :
  // 105:       $value args(1)
  // 106:       $body args(2)
  // 107:       $$success false
  // 108:       if
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__3_1(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // expr: 0
  // values_and_bodies: 1
  // recursive_case: 2
  frame->slots[2] /* recursive_case */ = create_future();
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  frame->slots[0] /* expr */ = arguments->slots[0];
  frame->slots[1] /* values_and_bodies */ = from_arguments(1, argument_count-1);
  //  97: ... : (args)
  //  98:   $len length_of(args)
  //  99:   if len > 0:
  // 100:     if
  // 101:       len == 1:
  // 102:         $body args(1)
  // 103:         body
  // 104:       :
  // 105:         $value args(1)
  // 106:         $body args(2)
  // ...
  frame->slots[3] /* temp__1 */ = create_closure(entry__3_2, 1);
  //  97: $recursive_case: (args)
  //  98:   $len length_of(args)
  //  99:   if len > 0:
  // 100:     if
  // 101:       len == 1:
  // 102:         $body args(1)
  // 103:         body
  // 104:       :
  // 105:         $value args(1)
  // 106:         $body args(2)
  // ...
  initialize_future(frame->slots[2] /* recursive_case */, frame->slots[3] /* temp__1 */);
  // 140: recursive_case values_and_bodies
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* values_and_bodies */;
  result_count = frame->caller_result_count;
  myself = frame->slots[2] /* recursive_case */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__4_23(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // recursive_check_case: 0
  // args: 1
  frame->slots[0] = myself->closure.frame->slots[3]; /* recursive_check_case */
  frame->slots[1] = myself->closure.frame->slots[0]; /* args */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 191: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__4_24;
}
static void cont__4_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 191: ... range(args 3 -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* args */;
  arguments->slots[1] = number__3;
  arguments->slots[2] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__4_25;
}
static void cont__4_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 191: ... recursive_check_case range(args 3 -1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* recursive_check_case */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__4_7(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // args: 0
  // body: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* args */
  frame->slots[1] /* body */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 176: $body args(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* args */;
  func = myself->type;
  frame->cont = cont__4_8;
}
static void cont__4_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* body */, arguments->slots[0]);
  // 177: body
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* body */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__4_9(void) {
  allocate_initialized_frame_gc(4, 10);
  // slot allocations:
  // args: 0
  // check: 1
  // expr: 2
  // recursive_check_case: 3
  // value: 4
  // body: 5
  // success: 6
  frame->slots[0] = myself->closure.frame->slots[1]; /* args */
  frame->slots[1] = myself->closure.frame->slots[2]; /* check */
  frame->slots[2] = myself->closure.frame->slots[3]; /* expr */
  frame->slots[3] = myself->closure.frame->slots[4]; /* recursive_check_case */
  frame->slots[4] /* value */ = create_future();
  frame->slots[5] /* body */ = create_future();
  frame->slots[6] /* success */ = create_cell();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 179: $value args(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* args */;
  func = myself->type;
  frame->cont = cont__4_10;
}
static void cont__4_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* value */, arguments->slots[0]);
  // 180: $body args(2)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = frame->slots[0] /* args */;
  func = myself->type;
  frame->cont = cont__4_11;
}
static void cont__4_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* body */, arguments->slots[0]);
  // 181: $$success false
  ((CELL *)frame->slots[6])->contents /* success */ = get__false();
  // 183: value.is_a_sequence
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* value */;
  result_count = 1;
  myself = get__is_a_sequence();
  func = myself->type;
  frame->cont = cont__4_12;
}
static void cont__4_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 183: ... :
  // 184:   do: (-> break)
  // 185:     for_each value: (sub_value)
  // 186:       if check(expr sub_value):
  // 187:         !success true
  // 188:         break
  frame->slots[8] /* temp__2 */ = create_closure(entry__4_13, 0);
  // 189: :
  // 190:   if check(expr value): !success true
  frame->slots[9] /* temp__3 */ = create_closure(entry__4_19, 0);
  // 182: if
  // 183:   value.is_a_sequence:
  // 184:     do: (-> break)
  // 185:       for_each value: (sub_value)
  // 186:         if check(expr sub_value):
  // 187:           !success true
  // 188:           break
  // 189:   :
  // 190:     if check(expr value): !success true
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__2 */;
  arguments->slots[2] = frame->slots[9] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__4_22;
}
static void entry__4_21(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // success: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* success */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 190: ... !success true
  ((CELL *)frame->slots[0])->contents /* success */ = get__true();
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__4_14(void) {
  allocate_initialized_frame_gc(5, 6);
  // slot allocations:
  // break: 0
  // value: 1
  // check: 2
  // expr: 3
  // success: 4
  frame->slots[0] /* break */ = create_continuation();
  frame->slots[1] = myself->closure.frame->slots[0]; /* value */
  frame->slots[2] = myself->closure.frame->slots[1]; /* check */
  frame->slots[3] = myself->closure.frame->slots[2]; /* expr */
  frame->slots[4] = myself->closure.frame->slots[3]; /* success */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 185: ... : (sub_value)
  // 186:   if check(expr sub_value):
  // 187:     !success true
  // 188:     break
  frame->slots[5] /* temp__1 */ = create_closure(entry__4_15, 1);
  // 185: for_each value: (sub_value)
  // 186:   if check(expr sub_value):
  // 187:     !success true
  // 188:     break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* value */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__4_18;
}
static void entry__4_17(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // success: 0
  // break: 1
  frame->slots[0] = myself->closure.frame->slots[3]; /* success */
  frame->slots[1] = myself->closure.frame->slots[4]; /* break */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 187: !success true
  ((CELL *)frame->slots[0])->contents /* success */ = get__true();
  // 188: break
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* break */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__4_15(void) {
  allocate_initialized_frame_gc(5, 7);
  // slot allocations:
  // sub_value: 0
  // check: 1
  // expr: 2
  // success: 3
  // break: 4
  frame->slots[1] = myself->closure.frame->slots[2]; /* check */
  frame->slots[2] = myself->closure.frame->slots[3]; /* expr */
  frame->slots[3] = myself->closure.frame->slots[4]; /* success */
  frame->slots[4] = myself->closure.frame->slots[0]; /* break */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 186: ... check(expr sub_value)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* expr */;
  arguments->slots[1] = frame->slots[0] /* sub_value */;
  result_count = 1;
  myself = frame->slots[1] /* check */;
  func = myself->type;
  frame->cont = cont__4_16;
}
static void cont__4_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 186: ... :
  // 187:   !success true
  // 188:   break
  frame->slots[6] /* temp__2 */ = create_closure(entry__4_17, 0);
  // 186: if check(expr sub_value):
  // 187:   !success true
  // 188:   break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__4_18(void) {
  myself = frame->slots[0] /* break */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__4_13(void) {
  allocate_initialized_frame_gc(4, 5);
  // slot allocations:
  // value: 0
  // check: 1
  // expr: 2
  // success: 3
  frame->slots[0] = myself->closure.frame->slots[4]; /* value */
  frame->slots[1] = myself->closure.frame->slots[1]; /* check */
  frame->slots[2] = myself->closure.frame->slots[2]; /* expr */
  frame->slots[3] = myself->closure.frame->slots[6]; /* success */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 184: ... : (-> break)
  // 185:   for_each value: (sub_value)
  // 186:     if check(expr sub_value):
  // 187:       !success true
  // 188:       break
  frame->slots[4] /* temp__1 */ = create_closure(entry__4_14, 0);
  // 184: do: (-> break)
  // 185:   for_each value: (sub_value)
  // 186:     if check(expr sub_value):
  // 187:       !success true
  // 188:       break
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__do();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__4_19(void) {
  allocate_initialized_frame_gc(4, 6);
  // slot allocations:
  // check: 0
  // expr: 1
  // value: 2
  // success: 3
  frame->slots[0] = myself->closure.frame->slots[1]; /* check */
  frame->slots[1] = myself->closure.frame->slots[2]; /* expr */
  frame->slots[2] = myself->closure.frame->slots[4]; /* value */
  frame->slots[3] = myself->closure.frame->slots[6]; /* success */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 190: ... check(expr value)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* expr */;
  arguments->slots[1] = frame->slots[2] /* value */;
  result_count = 1;
  myself = frame->slots[0] /* check */;
  func = myself->type;
  frame->cont = cont__4_20;
}
static void cont__4_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 190: ... : !success true
  frame->slots[5] /* temp__2 */ = create_closure(entry__4_21, 0);
  // 190: if check(expr value): !success true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__4_22(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 191: ... : recursive_check_case range(args 3 -1)
  frame->slots[7] /* temp__1 */ = create_closure(entry__4_23, 0);
  // 191: if success body: recursive_check_case range(args 3 -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[6])->contents /* success */;
  arguments->slots[1] = frame->slots[5] /* body */;
  arguments->slots[2] = frame->slots[7] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__4_5(void) {
  allocate_initialized_frame_gc(5, 8);
  // slot allocations:
  // len: 0
  // args: 1
  // check: 2
  // expr: 3
  // recursive_check_case: 4
  frame->slots[0] = myself->closure.frame->slots[4]; /* len */
  frame->slots[1] = myself->closure.frame->slots[0]; /* args */
  frame->slots[2] = myself->closure.frame->slots[1]; /* check */
  frame->slots[3] = myself->closure.frame->slots[2]; /* expr */
  frame->slots[4] = myself->closure.frame->slots[3]; /* recursive_check_case */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 175: len == 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* len */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__4_6;
}
static void cont__4_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 175: ... :
  // 176:   $body args(1)
  // 177:   body
  frame->slots[6] /* temp__2 */ = create_closure(entry__4_7, 0);
  // 178: :
  // 179:   $value args(1)
  // 180:   $body args(2)
  // 181:   $$success false
  // 182:   if
  // 183:     value.is_a_sequence:
  // 184:       do: (-> break)
  // 185:         for_each value: (sub_value)
  // 186:           if check(expr sub_value):
  // 187:             !success true
  // ...
  frame->slots[7] /* temp__3 */ = create_closure(entry__4_9, 0);
  // 174: if
  // 175:   len == 1:
  // 176:     $body args(1)
  // 177:     body
  // 178:   :
  // 179:     $value args(1)
  // 180:     $body args(2)
  // 181:     $$success false
  // 182:     if
  // 183:       value.is_a_sequence:
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
static void entry__4_2(void) {
  allocate_initialized_frame_gc(4, 7);
  // slot allocations:
  // args: 0
  // check: 1
  // expr: 2
  // recursive_check_case: 3
  // len: 4
  frame->slots[1] = myself->closure.frame->slots[1]; /* check */
  frame->slots[2] = myself->closure.frame->slots[0]; /* expr */
  frame->slots[3] = myself->closure.frame->slots[3]; /* recursive_check_case */
  frame->slots[4] /* len */ = create_future();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 172: $len length_of(args)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* args */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__4_3;
}
static void cont__4_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* len */, arguments->slots[0]);
  // 173: ... len > 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = frame->slots[4] /* len */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__4_4;
}
static void cont__4_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 173: ... :
  // 174:   if
  // 175:     len == 1:
  // 176:       $body args(1)
  // 177:       body
  // 178:     :
  // 179:       $value args(1)
  // 180:       $body args(2)
  // 181:       $$success false
  // 182:       if
  // ...
  frame->slots[6] /* temp__2 */ = create_closure(entry__4_5, 0);
  // 173: if len > 0:
  // 174:   if
  // 175:     len == 1:
  // 176:       $body args(1)
  // 177:       body
  // 178:     :
  // 179:       $value args(1)
  // 180:       $body args(2)
  // 181:       $$success false
  // 182:       if
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__4_1(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // expr: 0
  // check: 1
  // values_and_bodies: 2
  // recursive_check_case: 3
  frame->slots[3] /* recursive_check_case */ = create_future();
  if (argument_count < 2) {
    too_few_arguments_error();
    return;
  }
  frame->slots[0] /* expr */ = arguments->slots[0];
  frame->slots[1] /* check */ = arguments->slots[1];
  frame->slots[2] /* values_and_bodies */ = from_arguments(2, argument_count-2);
  // 171: ... : (args)
  // 172:   $len length_of(args)
  // 173:   if len > 0:
  // 174:     if
  // 175:       len == 1:
  // 176:         $body args(1)
  // 177:         body
  // 178:       :
  // 179:         $value args(1)
  // 180:         $body args(2)
  // ...
  frame->slots[4] /* temp__1 */ = create_closure(entry__4_2, 1);
  // 171: $recursive_check_case: (args)
  // 172:   $len length_of(args)
  // 173:   if len > 0:
  // 174:     if
  // 175:       len == 1:
  // 176:         $body args(1)
  // 177:         body
  // 178:       :
  // 179:         $value args(1)
  // 180:         $body args(2)
  // ...
  initialize_future(frame->slots[3] /* recursive_check_case */, frame->slots[4] /* temp__1 */);
  // 193: recursive_check_case values_and_bodies
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* values_and_bodies */;
  result_count = frame->caller_result_count;
  myself = frame->slots[3] /* recursive_check_case */;
  func = myself->type;
  frame = frame->caller_frame;
}
EXPORT void collect__basic__branches(void) {
  var.std__cond = collect_node(var.std__cond);
  func__1_1 = collect_node(func__1_1);
  var._cond_list = collect_node(var._cond_list);
  func__2_1 = collect_node(func__2_1);
  var.std__case = collect_node(var.std__case);
  func__3_1 = collect_node(func__3_1);
  var.std__check_case = collect_node(var.std__check_case);
  func__4_1 = collect_node(func__4_1);
  number__0 = collect_node(number__0);
  number__3 = collect_node(number__3);
  number__1 = collect_node(number__1);
  number__2 = collect_node(number__2);
}

static int already_run_phase_1 = false;

EXPORT void phase_1__basic__branches(void) {
  if (already_run_phase_1) return;
  already_run_phase_1 = true;
  register_module_info(&module_info);
}

static int already_run_phase_2 = false;

EXPORT void phase_2__basic__branches(void) {
  if (already_run_phase_2) return;
  already_run_phase_2 = true;
  set_module("basic__branches");
  set_used_namespaces(used_namespaces);
  number__0 = from_uint32(0U);
  number__3 = from_uint32(3U);
  number__1 = from_uint32(1U);
  number__2 = from_uint32(2U);
  func__1_1 = create_future();
  define_single_assign_static("std", "cond", get__std__cond, &var.std__cond);
  func__2_1 = create_future();
  func__3_1 = create_future();
  define_single_assign_static("std", "case", get__std__case, &var.std__case);
  func__4_1 = create_future();
  define_single_assign_static("std", "check_case", get__std__check_case, &var.std__check_case);
}

static int already_run_phase_3 = false;

EXPORT void phase_3__basic__branches(void) {
  if (already_run_phase_3) return;
  already_run_phase_3 = true;
  set_module("basic__branches");
  set_used_namespaces(used_namespaces);
  use_read_only(NULL, "cond", &get__cond, &get_value_or_future__cond);
  use_read_only(NULL, "do", &get__do, &get_value_or_future__do);
  use_read_only(NULL, "false", &get__false, &get_value_or_future__false);
  use_read_only(NULL, "for_each", &get__for_each, &get_value_or_future__for_each);
  use_read_only(NULL, "if", &get__if, &get_value_or_future__if);
  use_read_only(NULL, "is_a_sequence", &get__is_a_sequence, &get_value_or_future__is_a_sequence);
  use_read_only(NULL, "is_a_value_range", &get__is_a_value_range, &get_value_or_future__is_a_value_range);
  use_read_only(NULL, "is_defined", &get__is_defined, &get_value_or_future__is_defined);
  use_read_only(NULL, "is_empty", &get__is_empty, &get_value_or_future__is_empty);
  use_read_only(NULL, "is_undefined", &get__is_undefined, &get_value_or_future__is_undefined);
  use_read_only(NULL, "length_of", &get__length_of, &get_value_or_future__length_of);
  use_read_only(NULL, "lower_bound_of", &get__lower_bound_of, &get_value_or_future__lower_bound_of);
  use_read_only(NULL, "range", &get__range, &get_value_or_future__range);
  use_read_only("std", "and", &get__std__and, &get_value_or_future__std__and);
  use_read_only("std", "equal", &get__std__equal, &get_value_or_future__std__equal);
  use_read_only("std", "less", &get__std__less, &get_value_or_future__std__less);
  use_read_only("std", "negate", &get__std__negate, &get_value_or_future__std__negate);
  use_read_only("std", "not", &get__std__not, &get_value_or_future__std__not);
  use_read_only(NULL, "true", &get__true, &get_value_or_future__true);
  use_read_only(NULL, "unless", &get__unless, &get_value_or_future__unless);
  use_read_only(NULL, "upper_bound_of", &get__upper_bound_of, &get_value_or_future__upper_bound_of);
}

static int already_run_phase_4 = false;

EXPORT void phase_4__basic__branches(void) {
  if (already_run_phase_4) return;
  already_run_phase_4 = true;
  assign_variable(&var.std__cond, &func__1_1);
  assign_variable(&var._cond_list, &func__2_1);
  assign_variable(&var.std__case, &func__3_1);
  assign_variable(&var.std__check_case, &func__4_1);
}

static int already_run_phase_5 = false;

EXPORT void phase_5__basic__branches(void) {
  if (already_run_phase_5) return;
  already_run_phase_5 = true;
  assign_value(&func__1_1, create_function(entry__1_1, -1));
  assign_value(&func__2_1, create_function(entry__2_1, 1));
  assign_value(&func__3_1, create_function(entry__3_1, -1));
  assign_value(&func__4_1, create_function(entry__4_1, -1));
  register_collector(collect__basic__branches);
}
