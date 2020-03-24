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
#if defined(__GNUC__) && !defined(__clang__) && defined(__x86_64)
  #define ASM(x) asm(x)
#else
  #define ASM(x)
#endif
REGISTER NODE *myself ASM("r13");
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
IMPORT NODE *get_attribute(NODE *node, int idx);
REGISTER FRAME *arguments ASM("r12");
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
IMPORT void initialize_maybe_future(NODE *var, NODE *val);
IMPORT NODE *create_continuation_with_exit(FUNC exit_func);
IMPORT NODE *create_cell(void);
IMPORT NODE *create_cell_with_contents(NODE *contents);
typedef struct CELL {
  FUNC type;
  struct ATTRIBUTES *attributes;
  NODE *contents;
} CELL;
IMPORT int result_count;
IMPORT void invalid_results_error(void);
IMPORT NODE *create_closure(FUNC type, int par_count);
IMPORT NODE *create_future(void);
IMPORT void initialize_future(NODE *var, NODE *val);
IMPORT void continuation_type_function(void);
IMPORT NODE *create_continuation(void);
IMPORT void too_few_arguments_error(void);
IMPORT void too_many_arguments_error(void);
IMPORT NODE *collect_node(NODE *node);
IMPORT void register_module_info(MODULE_INFO *info);
IMPORT void register_polymorphic_function_with_setter(const char *name, int *id_p);
IMPORT NODE *from_uint32(uint32_t val);
IMPORT NODE *create_function(FUNC func, int par_count);
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
IMPORT void use_polymorphic_function(
  const char *namespace, const char *name, NODE_GETTER *getter, int *id
);
IMPORT NODE *undefined;
IMPORT void def_attribute(NODE **var_p, int idx, void *attr);
IMPORT void define_type_function(
  const char *namespace, const char *name, FUNC type, int par_cnt
);
IMPORT void define_attribute(
  const char *namespace, const char *name,
  int id, NODE *attribute
);
IMPORT void define_method(
  const char *namespace, const char *name,
  int id, NODE *method
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
#define IS_OLD(addr) false
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
static NODE_GETTER get__case;
static NODE_GETTER get_value_or_future__case;
static NODE_GETTER get__cond;
static NODE_GETTER get_value_or_future__cond;
static NODE_GETTER get__dec;
static NODE_GETTER get_value_or_future__dec;
static NODE_GETTER get__false;
static NODE_GETTER get_value_or_future__false;
static int poly_idx__for_each;
static NODE_GETTER get__for_each;
static NODE_GETTER get__if;
static NODE_GETTER get_value_or_future__if;
static NODE_GETTER get__inc;
static NODE_GETTER get_value_or_future__inc;
static NODE_GETTER get__is_defined;
static NODE_GETTER get_value_or_future__is_defined;
static NODE_GETTER get__is_undefined;
static NODE_GETTER get_value_or_future__is_undefined;
static int poly_idx__key_of;
static NODE_GETTER get__key_of;
static int poly_idx__length_of;
static NODE_GETTER get__length_of;
static int poly_idx__serialization_tag_of;
static NODE_GETTER get__serialization_tag_of;
static NODE_GETTER get__std__equal;
static NODE_GETTER get_value_or_future__std__equal;
static NODE_GETTER get__std__less;
static NODE_GETTER get_value_or_future__std__less;
static NODE_GETTER get__std__not;
static NODE_GETTER get_value_or_future__std__not;
static NODE_GETTER get__true;
static NODE_GETTER get_value_or_future__true;
static NODE_GETTER get__types__generic_set;
static NODE_GETTER get_value_or_future__types__generic_set;
static NODE_GETTER get__types__object;
static NODE_GETTER get_value_or_future__types__object;
static NODE_GETTER get__undefined;
static NODE_GETTER get_value_or_future__undefined;
static struct {
  NODE *_NONE;
  NODE *_tree_of;
  NODE *_left_of;
  NODE *_right_of;
  NODE *_empty_node;
  NODE *_fetch_first;
  NODE *_get_item;
  NODE *_add_item;
  NODE *_remove_item;
  NODE *_for_each_item;
  NODE *types__key_order_set;
  NODE *std__empty_key_order_set;
  NODE *std__key_order_set;
} var;
static const char *var_names[] = {
  "NONE",
  "tree_of",
  "left_of",
  "right_of",
  "empty_node",
  "fetch_first",
  "get_item",
  "add_item",
  "remove_item",
  "for_each_item"
};
static NODE *unique__1_1;
static int poly_idx__tree_of;
static void type__tree_of(void);
static int poly_idx__left_of;
static void type__left_of(void);
static int poly_idx__right_of;
static void type__right_of(void);
static NODE *get__types__key_order_set(void) {
  return var.types__key_order_set;
}
static NODE *func__9_1;
static void entry__9_1(void);
static FRAME_INFO frame__9_1 = {3, {"myself", "return", "left"}};
static void exit__9_1(void);
static void cont__9_2(void);
static void cont__9_3(void);
static NODE *func__9_4;
static void entry__9_4(void);
static FRAME_INFO frame__9_4 = {4, {"left", "myself", "return", "key"}};
static void cont__9_5(void);
static NODE *func__9_6;
static void entry__9_6(void);
static FRAME_INFO frame__9_6 = {3, {"myself", "return", "key"}};
static void cont__9_7(void);
static void cont__9_8(void);
static void cont__9_9(void);
static NODE *func__10_1;
static void entry__10_1(void);
static FRAME_INFO frame__10_1 = {4, {"myself", "key", "return", "my_key"}};
static void cont__10_2(void);
static NODE *func__10_3;
static void entry__10_3(void);
static FRAME_INFO frame__10_3 = {1, {"return"}};
static void cont__10_4(void);
static void cont__10_5(void);
static NODE *func__10_6;
static void entry__10_6(void);
static FRAME_INFO frame__10_6 = {3, {"key", "my_key", "return"}};
static void cont__10_7(void);
static NODE *func__10_8;
static void entry__10_8(void);
static FRAME_INFO frame__10_8 = {1, {"return"}};
static NODE *func__10_9;
static void entry__10_9(void);
static FRAME_INFO frame__10_9 = {4, {"key", "my_key", "return", "myself"}};
static void cont__10_10(void);
static NODE *func__10_11;
static void entry__10_11(void);
static FRAME_INFO frame__10_11 = {3, {"return", "myself", "key"}};
static void cont__10_12(void);
static void cont__10_13(void);
static NODE *func__10_14;
static void entry__10_14(void);
static FRAME_INFO frame__10_14 = {4, {"my_key", "key", "return", "myself"}};
static void cont__10_15(void);
static NODE *func__10_16;
static void entry__10_16(void);
static FRAME_INFO frame__10_16 = {3, {"return", "myself", "key"}};
static void cont__10_17(void);
static void cont__10_18(void);
static void cont__10_19(void);
static NODE *func__11_1;
static void entry__11_1(void);
static FRAME_INFO frame__11_1 = {4, {"myself", "key", "return", "my_key"}};
static void cont__11_2(void);
static NODE *func__11_3;
static void entry__11_3(void);
static FRAME_INFO frame__11_3 = {2, {"return", "key"}};
static void cont__11_4(void);
static void cont__11_5(void);
static NODE *func__11_6;
static void entry__11_6(void);
static FRAME_INFO frame__11_6 = {3, {"key", "my_key", "return"}};
static void cont__11_7(void);
static NODE *func__11_8;
static void entry__11_8(void);
static FRAME_INFO frame__11_8 = {1, {"return"}};
static NODE *func__11_9;
static void entry__11_9(void);
static FRAME_INFO frame__11_9 = {4, {"key", "my_key", "myself", "return"}};
static void cont__11_10(void);
static NODE *func__11_11;
static void entry__11_11(void);
static FRAME_INFO frame__11_11 = {4, {"myself", "key", "return", "left"}};
static void cont__11_12(void);
static void cont__11_13(void);
static void cont__11_14(void);
static NODE *func__11_15;
static void entry__11_15(void);
static FRAME_INFO frame__11_15 = {1, {"return"}};
static void cont__11_16(void);
static NODE *func__11_17;
static void entry__11_17(void);
static FRAME_INFO frame__11_17 = {4, {"my_key", "key", "myself", "return"}};
static void cont__11_18(void);
static NODE *func__11_19;
static void entry__11_19(void);
static FRAME_INFO frame__11_19 = {4, {"myself", "key", "return", "right"}};
static void cont__11_20(void);
static void cont__11_21(void);
static void cont__11_22(void);
static NODE *func__11_23;
static void entry__11_23(void);
static FRAME_INFO frame__11_23 = {1, {"return"}};
static void cont__11_24(void);
static void cont__11_25(void);
static NODE *func__12_1;
static void entry__12_1(void);
static FRAME_INFO frame__12_1 = {4, {"myself", "key", "return", "my_key"}};
static void cont__12_2(void);
static NODE *func__12_3;
static void entry__12_3(void);
static FRAME_INFO frame__12_3 = {1, {"return"}};
static void cont__12_4(void);
static void cont__12_5(void);
static NODE *func__12_6;
static void entry__12_6(void);
static FRAME_INFO frame__12_6 = {4, {"key", "my_key", "myself", "return"}};
static void cont__12_7(void);
static NODE *func__12_8;
static void entry__12_8(void);
static FRAME_INFO frame__12_8 = {4, {"myself", "return", "left", "right"}};
static void cont__12_9(void);
static void cont__12_10(void);
static void cont__12_11(void);
static NODE *func__12_12;
static void entry__12_12(void);
static FRAME_INFO frame__12_12 = {3, {"right", "return", "left"}};
static void cont__12_13(void);
static NODE *func__12_14;
static void entry__12_14(void);
static FRAME_INFO frame__12_14 = {4, {"right", "return", "left", "head"}};
static void cont__12_15(void);
static NODE *func__12_16;
static void entry__12_16(void);
static FRAME_INFO frame__12_16 = {2, {"return", "left"}};
static NODE *func__12_17;
static void entry__12_17(void);
static FRAME_INFO frame__12_17 = {2, {"return", "right"}};
static NODE *func__12_18;
static void entry__12_18(void);
static FRAME_INFO frame__12_18 = {4, {"key", "my_key", "myself", "return"}};
static void cont__12_19(void);
static NODE *func__12_20;
static void entry__12_20(void);
static FRAME_INFO frame__12_20 = {4, {"myself", "key", "return", "left"}};
static void cont__12_21(void);
static void cont__12_22(void);
static void cont__12_23(void);
static NODE *func__12_24;
static void entry__12_24(void);
static FRAME_INFO frame__12_24 = {1, {"return"}};
static void cont__12_25(void);
static NODE *func__12_26;
static void entry__12_26(void);
static FRAME_INFO frame__12_26 = {4, {"my_key", "key", "myself", "return"}};
static void cont__12_27(void);
static NODE *func__12_28;
static void entry__12_28(void);
static FRAME_INFO frame__12_28 = {4, {"myself", "key", "return", "right"}};
static void cont__12_29(void);
static void cont__12_30(void);
static void cont__12_31(void);
static NODE *func__12_32;
static void entry__12_32(void);
static FRAME_INFO frame__12_32 = {1, {"return"}};
static void cont__12_33(void);
static void cont__12_34(void);
static NODE *func__13_1;
static void entry__13_1(void);
static FRAME_INFO frame__13_1 = {4, {"key", "value", "myself", "return"}};
static NODE *func__13_2;
static void entry__13_2(void);
static FRAME_INFO frame__13_2 = {3, {"return", "myself", "key"}};
static void cont__13_3(void);
static void cont__13_4(void);
static NODE *func__13_5;
static void entry__13_5(void);
static FRAME_INFO frame__13_5 = {4, {"myself", "key", "return", "new_tree"}};
static void cont__13_6(void);
static void cont__13_7(void);
static void cont__13_8(void);
static void cont__13_9(void);
static NODE *func__13_10;
static void entry__13_10(void);
static FRAME_INFO frame__13_10 = {2, {"myself", "new_tree"}};
static void cont__13_11(void);
static void cont__13_12(void);
static void cont__13_13(void);
static NODE *func__13_14;
static void entry__13_14(void);
static FRAME_INFO frame__13_14 = {4, {"myself", "key", "return", "new_tree"}};
static void cont__13_15(void);
static void cont__13_16(void);
static void cont__13_17(void);
static void cont__13_18(void);
static NODE *func__13_19;
static void entry__13_19(void);
static FRAME_INFO frame__13_19 = {2, {"myself", "new_tree"}};
static void cont__13_20(void);
static void cont__13_21(void);
static void cont__13_22(void);
static NODE *func__13_23;
static void entry__13_23(void);
static FRAME_INFO frame__13_23 = {0, {}};
static NODE *string__13_24;
static void cont__13_25(void);
static NODE *string__16_1;
static NODE *get__std__empty_key_order_set(void) {
  return var.std__empty_key_order_set;
}
static NODE *func__18_1;
static void entry__18_1(void);
static FRAME_INFO frame__18_1 = {0, {}};
static NODE *get__std__key_order_set(void) {
  return var.std__key_order_set;
}
static NODE *func__19_1;
static void entry__19_1(void);
static FRAME_INFO frame__19_1 = {2, {"myself", "body"}};
static void cont__19_2(void);
static NODE *func__19_3;
static void entry__19_3(void);
static FRAME_INFO frame__19_3 = {2, {"myself", "body"}};
static void cont__19_4(void);
static void cont__19_5(void);
static void cont__19_6(void);
static void cont__19_7(void);
static void cont__19_8(void);
static NODE *func__20_1;
static void entry__20_1(void);
static FRAME_INFO frame__20_1 = {3, {"self", "body", "tree"}};
static void cont__20_2(void);
static void cont__20_3(void);
static NODE *func__20_4;
static void entry__20_4(void);
static FRAME_INFO frame__20_4 = {2, {"tree", "body"}};
void run__basic__types__key_order_set(void);

static CONTINUATION_INFO continuation_info[] = {
  {type__tree_of, NULL, 25, 25, 2, 8},
  {type__left_of, NULL, 26, 26, 2, 8},
  {type__right_of, NULL, 27, 27, 2, 9},
  {run__basic__types__key_order_set, NULL, 39, 39, 1, 25},
  {entry__9_4, NULL, 51, 51, 7, 29},
  {cont__9_5, &frame__9_4, 53, 53, 7, 16},
  {entry__9_6, NULL, 55, 55, 7, 25},
  {cont__9_7, &frame__9_6, 56, 56, 7, 30},
  {cont__9_8, &frame__9_6, 57, 57, 7, 16},
  {entry__9_1, NULL, 48, 48, 3, 24},
  {cont__9_2, &frame__9_1, 50, 50, 5, 19},
  {cont__9_3, &frame__9_1, 49, 57, 3, 17},
  {cont__9_9, &frame__9_1, 57, 57, 17, 17},
  {entry__10_3, NULL, 65, 65, 27, 38},
  {entry__10_8, NULL, 68, 68, 23, 33},
  {entry__10_6, NULL, 68, 68, 8, 20},
  {cont__10_7, &frame__10_6, 68, 68, 5, 33},
  {entry__10_11, NULL, 69, 69, 38, 52},
  {cont__10_12, &frame__10_11, 69, 69, 29, 57},
  {cont__10_13, &frame__10_11, 69, 69, 22, 57},
  {entry__10_9, NULL, 69, 69, 8, 19},
  {cont__10_10, &frame__10_9, 69, 69, 5, 57},
  {entry__10_16, NULL, 70, 70, 38, 53},
  {cont__10_17, &frame__10_16, 70, 70, 29, 58},
  {cont__10_18, &frame__10_16, 70, 70, 22, 58},
  {entry__10_14, NULL, 70, 70, 8, 19},
  {cont__10_15, &frame__10_14, 70, 70, 5, 58},
  {entry__10_1, NULL, 65, 65, 6, 24},
  {cont__10_2, &frame__10_1, 65, 65, 3, 38},
  {cont__10_4, &frame__10_1, 66, 66, 3, 24},
  {cont__10_5, &frame__10_1, 67, 70, 3, 58},
  {cont__10_19, &frame__10_1, 70, 70, 58, 58},
  {entry__11_3, NULL, 78, 78, 27, 56},
  {entry__11_8, NULL, 81, 81, 23, 33},
  {entry__11_6, NULL, 81, 81, 8, 20},
  {cont__11_7, &frame__11_6, 81, 81, 5, 33},
  {entry__11_15, NULL, 84, 84, 24, 50},
  {entry__11_11, NULL, 83, 83, 22, 36},
  {cont__11_12, &frame__11_11, 83, 83, 7, 41},
  {cont__11_13, &frame__11_11, 84, 84, 10, 21},
  {cont__11_14, &frame__11_11, 84, 84, 7, 50},
  {cont__11_16, &frame__11_11, 86, 86, 7, 19},
  {entry__11_9, NULL, 82, 82, 8, 19},
  {cont__11_10, &frame__11_9, 82, 86, 5, 19},
  {entry__11_23, NULL, 89, 89, 25, 51},
  {entry__11_19, NULL, 88, 88, 23, 38},
  {cont__11_20, &frame__11_19, 88, 88, 7, 43},
  {cont__11_21, &frame__11_19, 89, 89, 10, 22},
  {cont__11_22, &frame__11_19, 89, 89, 7, 51},
  {cont__11_24, &frame__11_19, 91, 91, 7, 19},
  {entry__11_17, NULL, 87, 87, 8, 19},
  {cont__11_18, &frame__11_17, 87, 91, 5, 19},
  {entry__11_1, NULL, 78, 78, 6, 24},
  {cont__11_2, &frame__11_1, 78, 78, 3, 56},
  {cont__11_4, &frame__11_1, 79, 79, 3, 24},
  {cont__11_5, &frame__11_1, 80, 91, 3, 20},
  {cont__11_25, &frame__11_1, 91, 91, 20, 20},
  {entry__12_3, NULL, 99, 99, 27, 55},
  {entry__12_14, NULL, 109, 109, 15, 39},
  {cont__12_15, &frame__12_14, 110, 110, 15, 78},
  {entry__12_16, NULL, 112, 112, 15, 25},
  {entry__12_12, NULL, 108, 108, 13, 28},
  {cont__12_13, &frame__12_12, 107, 112, 11, 26},
  {entry__12_17, NULL, 114, 114, 11, 22},
  {entry__12_8, NULL, 103, 103, 7, 27},
  {cont__12_9, &frame__12_8, 104, 104, 7, 30},
  {cont__12_10, &frame__12_8, 106, 106, 9, 23},
  {cont__12_11, &frame__12_8, 105, 114, 7, 23},
  {entry__12_6, NULL, 102, 102, 8, 20},
  {cont__12_7, &frame__12_6, 102, 114, 5, 24},
  {entry__12_24, NULL, 117, 117, 24, 52},
  {entry__12_20, NULL, 116, 116, 25, 39},
  {cont__12_21, &frame__12_20, 116, 116, 7, 44},
  {cont__12_22, &frame__12_20, 117, 117, 10, 21},
  {cont__12_23, &frame__12_20, 117, 117, 7, 52},
  {cont__12_25, &frame__12_20, 119, 119, 7, 19},
  {entry__12_18, NULL, 115, 115, 8, 19},
  {cont__12_19, &frame__12_18, 115, 119, 5, 19},
  {entry__12_32, NULL, 122, 122, 25, 53},
  {entry__12_28, NULL, 121, 121, 26, 41},
  {cont__12_29, &frame__12_28, 121, 121, 7, 46},
  {cont__12_30, &frame__12_28, 122, 122, 10, 22},
  {cont__12_31, &frame__12_28, 122, 122, 7, 53},
  {cont__12_33, &frame__12_28, 124, 124, 7, 19},
  {entry__12_26, NULL, 120, 120, 8, 19},
  {cont__12_27, &frame__12_26, 120, 124, 5, 19},
  {entry__12_1, NULL, 99, 99, 6, 24},
  {cont__12_2, &frame__12_1, 99, 99, 3, 55},
  {cont__12_4, &frame__12_1, 100, 100, 3, 24},
  {cont__12_5, &frame__12_1, 101, 124, 3, 20},
  {cont__12_34, &frame__12_1, 124, 124, 20, 20},
  {entry__13_2, NULL, 136, 136, 23, 37},
  {cont__13_3, &frame__13_2, 136, 136, 14, 42},
  {cont__13_4, &frame__13_2, 136, 136, 7, 42},
  {entry__13_10, NULL, 141, 141, 14, 29},
  {cont__13_11, &frame__13_10, 141, 141, 9, 29},
  {cont__13_12, &frame__13_10, 141, 141, 29, 29},
  {entry__13_5, NULL, 138, 138, 26, 40},
  {cont__13_6, &frame__13_5, 138, 138, 7, 45},
  {cont__13_7, &frame__13_5, 139, 139, 10, 25},
  {cont__13_8, &frame__13_5, 139, 139, 10, 25},
  {cont__13_9, &frame__13_5, 139, 141, 7, 29},
  {cont__13_13, &frame__13_5, 142, 142, 7, 19},
  {entry__13_19, NULL, 147, 147, 14, 29},
  {cont__13_20, &frame__13_19, 147, 147, 9, 29},
  {cont__13_21, &frame__13_19, 147, 147, 29, 29},
  {entry__13_14, NULL, 144, 144, 29, 43},
  {cont__13_15, &frame__13_14, 144, 144, 7, 48},
  {cont__13_16, &frame__13_14, 145, 145, 10, 25},
  {cont__13_17, &frame__13_14, 145, 145, 10, 25},
  {cont__13_18, &frame__13_14, 145, 147, 7, 29},
  {cont__13_22, &frame__13_14, 148, 148, 7, 19},
  {entry__13_23, NULL, 150, 150, 7, 65},
  {entry__13_1, NULL, 133, 150, 3, 66},
  {cont__13_25, &frame__13_1, 150, 150, 66, 66},
  {entry__18_1, NULL, 157, 157, 21, 43},
  {entry__19_3, NULL, 161, 161, 19, 33},
  {cont__19_4, &frame__19_3, 161, 161, 5, 38},
  {cont__19_5, &frame__19_3, 162, 162, 10, 23},
  {cont__19_6, &frame__19_3, 162, 162, 5, 23},
  {cont__19_7, &frame__19_3, 163, 163, 19, 34},
  {cont__19_8, &frame__19_3, 163, 163, 5, 39},
  {entry__19_1, NULL, 160, 160, 6, 22},
  {cont__19_2, &frame__19_1, 160, 163, 3, 39},
  {entry__20_4, NULL, 167, 167, 23, 45},
  {entry__20_1, NULL, 166, 166, 3, 21},
  {cont__20_2, &frame__20_1, 167, 167, 6, 20},
  {cont__20_3, &frame__20_1, 167, 167, 3, 45}
};

union NODE {
  struct {
    FUNC type;
    ATTRIBUTES *attributes;
  };
  CONTINUATION continuation;
  CLOSURE closure;
};
static void type__tree_of(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__tree_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__tree_of, attr);
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
static void type__left_of(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__left_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__left_of, attr);
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
static void type__right_of(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__right_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__right_of, attr);
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
static NODE *number__0;

static const char *used_namespaces[] = {
  "std",
  NULL
};

static MODULE_INFO module_info = {
  NULL,
  "basic__types__key_order_set",
  continuation_info,
  sizeof(continuation_info)/sizeof(CONTINUATION_INFO),
  (NODE **)&var,
  var_names,
  sizeof(var_names)/sizeof(const char *),
  used_namespaces,
  {DEBUG_FILENAME("basic/types/key_order_set.sim")}
};

/******
C O D E
******/

static int already_run = false;

EXPORT void run__basic__types__key_order_set(void) {
  if (already_run) {
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  already_run = true;
  allocate_initialized_frame_gc(0, 0);
  // 29: $types::key_order_set types::generic_set
  initialize_maybe_future(var.types__key_order_set, get__types__generic_set());
  // 39: $empty_node types::object
  initialize_maybe_future(var._empty_node, get__types__object());
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__9_1(void) {
  allocate_initialized_frame_gc(2, 6);
  // slot allocations:
  // myself: 0
  // return: 1
  // left: 2
  frame->slots[1] /* return */ = create_continuation_with_exit(exit__9_1);
  frame->slots[2] /* left */ = create_cell();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* myself */ = create_cell_with_contents(arguments->slots[0]);
  // 48: $$left left_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  result_count = 1;
  myself = var._left_of;
  func = myself->type;
  frame->cont = cont__9_2;
}
static void cont__9_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* left */ = arguments->slots[0];
  // 50: left.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* left */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__9_3;
}
static void cont__9_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 50: ... :
  // 51:   $key fetch_first(&left)
  // 52:   !myself.left_of left
  // 53:   return key
  frame->slots[4] /* temp__2 */ = create_closure(entry__9_4, 0);
  // 54: :
  // 55:   $key key_of(myself)
  // 56:   !myself right_of(myself)
  // 57:   return key
  frame->slots[5] /* temp__3 */ = create_closure(entry__9_6, 0);
  // 49: if
  // 50:   left.is_defined:
  // 51:     $key fetch_first(&left)
  // 52:     !myself.left_of left
  // 53:     return key
  // 54:   :
  // 55:     $key key_of(myself)
  // 56:     !myself right_of(myself)
  // 57:     return key
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  arguments->slots[2] = frame->slots[5] /* temp__3 */;
  result_count =
    frame->caller_result_count >= 1 ?
    frame->caller_result_count-1 : -1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__9_9;
}
static void entry__9_4(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // left: 0
  // myself: 1
  // return: 2
  // key: 3
  frame->slots[0] = myself->closure.frame->slots[2]; /* left */
  frame->slots[1] = myself->closure.frame->slots[0]; /* myself */
  frame->slots[2] = myself->closure.frame->slots[1]; /* return */
  frame->slots[3] /* key */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 51: $key fetch_first(&left)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* left */;
  result_count = 2;
  myself = var._fetch_first;
  func = myself->type;
  frame->cont = cont__9_5;
}
static void cont__9_5(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* left */ = arguments->slots[0];
  frame->slots[4] /* temp__1 */ = arguments->slots[1];
  // 51: ... key
  initialize_future(frame->slots[3] /* key */, frame->slots[4] /* temp__1 */);
  // 52: !myself.left_of left
  frame->slots[4] /* temp__1 */ = ((CELL *)frame->slots[0])->contents /* left */;
  // 52: !myself.left_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[1])->contents /* myself */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__left_of, frame->slots[4] /* temp__1 */);
    ((CELL *)frame->slots[1])->contents /* myself */ = temp;

  }
  // 53: return key
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* key */;
  result_count = frame->caller_result_count;
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__9_6(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // myself: 0
  // return: 1
  // key: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* myself */
  frame->slots[1] = myself->closure.frame->slots[1]; /* return */
  frame->slots[2] /* key */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 55: $key key_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  result_count = 1;
  myself = get__key_of();
  func = myself->type;
  frame->cont = cont__9_7;
}
static void cont__9_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* key */, arguments->slots[0]);
  // 56: !myself right_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  result_count = 1;
  myself = var._right_of;
  func = myself->type;
  frame->cont = cont__9_8;
}
static void cont__9_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* myself */ = arguments->slots[0];
  // 57: return key
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* key */;
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__9_9(void) {
  myself = frame->slots[1] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void exit__9_1(void) {
  frame = ((CONTINUATION *)myself)->exit_frame;
  int i = argument_count;
  while (--i >= 0) {
    arguments->slots[i+1] = arguments->slots[i];
  }
  argument_count += 1;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  func = continuation_type_function;
}
static void entry__10_1(void) {
  allocate_initialized_frame_gc(3, 7);
  // slot allocations:
  // myself: 0
  // key: 1
  // return: 2
  // my_key: 3
  frame->slots[2] /* return */ = create_continuation();
  frame->slots[3] /* my_key */ = create_future();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 65: ... myself.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* myself */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__10_2;
}
static void cont__10_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 65: ... : return false
  frame->slots[5] /* temp__2 */ = create_closure(entry__10_3, 0);
  // 65: if myself.is_undefined: return false
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__10_4;
}
static void entry__10_3(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 65: ... return false
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__false();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__10_4(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 66: $my_key key_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* myself */;
  result_count = 1;
  myself = get__key_of();
  func = myself->type;
  frame->cont = cont__10_5;
}
static void cont__10_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* my_key */, arguments->slots[0]);
  // 68: -> key == my_key: return true
  frame->slots[4] /* temp__1 */ = create_closure(entry__10_6, 0);
  // 69: -> key < my_key: return get_item(left_of(myself) key)
  frame->slots[5] /* temp__2 */ = create_closure(entry__10_9, 0);
  // 70: -> key > my_key: return get_item(right_of(myself) key)
  frame->slots[6] /* temp__3 */ = create_closure(entry__10_14, 0);
  // 67: cond
  // 68:   -> key == my_key: return true
  // 69:   -> key < my_key: return get_item(left_of(myself) key)
  // 70:   -> key > my_key: return get_item(right_of(myself) key)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  arguments->slots[2] = frame->slots[6] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__cond();
  func = myself->type;
  frame->cont = cont__10_19;
}
static void entry__10_16(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // return: 0
  // myself: 1
  // key: 2
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  frame->slots[1] = myself->closure.frame->slots[3]; /* myself */
  frame->slots[2] = myself->closure.frame->slots[1]; /* key */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 70: ... right_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* myself */;
  result_count = 1;
  myself = var._right_of;
  func = myself->type;
  frame->cont = cont__10_17;
}
static void cont__10_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 70: ... get_item(right_of(myself) key)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[2] /* key */;
  result_count = 1;
  myself = var._get_item;
  func = myself->type;
  frame->cont = cont__10_18;
}
static void cont__10_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 70: ... return get_item(right_of(myself) key)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__10_11(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // return: 0
  // myself: 1
  // key: 2
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  frame->slots[1] = myself->closure.frame->slots[3]; /* myself */
  frame->slots[2] = myself->closure.frame->slots[0]; /* key */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 69: ... left_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* myself */;
  result_count = 1;
  myself = var._left_of;
  func = myself->type;
  frame->cont = cont__10_12;
}
static void cont__10_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 69: ... get_item(left_of(myself) key)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[2] /* key */;
  result_count = 1;
  myself = var._get_item;
  func = myself->type;
  frame->cont = cont__10_13;
}
static void cont__10_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 69: ... return get_item(left_of(myself) key)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__10_8(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 68: ... return true
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__true();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__10_6(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // key: 0
  // my_key: 1
  // return: 2
  frame->slots[0] = myself->closure.frame->slots[1]; /* key */
  frame->slots[1] = myself->closure.frame->slots[3]; /* my_key */
  frame->slots[2] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 68: ... key == my_key
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* key */;
  arguments->slots[1] = frame->slots[1] /* my_key */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__10_7;
}
static void cont__10_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 68: ... : return true
  frame->slots[4] /* temp__2 */ = create_closure(entry__10_8, 0);
  // 68: -> key == my_key: return true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__10_9(void) {
  allocate_initialized_frame_gc(4, 6);
  // slot allocations:
  // key: 0
  // my_key: 1
  // return: 2
  // myself: 3
  frame->slots[0] = myself->closure.frame->slots[1]; /* key */
  frame->slots[1] = myself->closure.frame->slots[3]; /* my_key */
  frame->slots[2] = myself->closure.frame->slots[2]; /* return */
  frame->slots[3] = myself->closure.frame->slots[0]; /* myself */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 69: ... key < my_key
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* key */;
  arguments->slots[1] = frame->slots[1] /* my_key */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__10_10;
}
static void cont__10_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 69: ... : return get_item(left_of(myself) key)
  frame->slots[5] /* temp__2 */ = create_closure(entry__10_11, 0);
  // 69: -> key < my_key: return get_item(left_of(myself) key)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__10_14(void) {
  allocate_initialized_frame_gc(4, 6);
  // slot allocations:
  // my_key: 0
  // key: 1
  // return: 2
  // myself: 3
  frame->slots[0] = myself->closure.frame->slots[3]; /* my_key */
  frame->slots[1] = myself->closure.frame->slots[1]; /* key */
  frame->slots[2] = myself->closure.frame->slots[2]; /* return */
  frame->slots[3] = myself->closure.frame->slots[0]; /* myself */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 70: ... key > my_key
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* my_key */;
  arguments->slots[1] = frame->slots[1] /* key */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__10_15;
}
static void cont__10_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 70: ... : return get_item(right_of(myself) key)
  frame->slots[5] /* temp__2 */ = create_closure(entry__10_16, 0);
  // 70: -> key > my_key: return get_item(right_of(myself) key)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__10_19(void) {
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__11_1(void) {
  allocate_initialized_frame_gc(3, 7);
  // slot allocations:
  // myself: 0
  // key: 1
  // return: 2
  // my_key: 3
  frame->slots[2] /* return */ = create_continuation();
  frame->slots[3] /* my_key */ = create_future();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* myself */ = create_cell_with_contents(arguments->slots[0]);
  // 78: ... myself.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__11_2;
}
static void cont__11_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 78: ... : return empty_node(.key_of key)
  frame->slots[5] /* temp__2 */ = create_closure(entry__11_3, 0);
  // 78: if myself.is_undefined: return empty_node(.key_of key)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__11_4;
}
static void entry__11_3(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // return: 0
  // key: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  frame->slots[1] = myself->closure.frame->slots[1]; /* key */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 78: ... empty_node(.key_of key)
  {
    NODE *temp = clone_object_and_attributes(var._empty_node);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__key_of, frame->slots[1] /* key */);
    frame->slots[2] /* temp__1 */ = temp;

  }
  // 78: ... return empty_node(.key_of key)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__11_4(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 79: $my_key key_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  result_count = 1;
  myself = get__key_of();
  func = myself->type;
  frame->cont = cont__11_5;
}
static void cont__11_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* my_key */, arguments->slots[0]);
  // 81: -> key == my_key: return NONE
  frame->slots[4] /* temp__1 */ = create_closure(entry__11_6, 0);
  // 82: -> key < my_key:
  // 83:   $left add_item(left_of(myself) key)
  // 84:   if NONE == left: return NONE # nothing added
  // 85:   !myself.left_of left
  // 86:   return myself
  frame->slots[5] /* temp__2 */ = create_closure(entry__11_9, 0);
  // 87: -> key > my_key:
  // 88:   $right add_item(right_of(myself) key)
  // 89:   if NONE == right: return NONE # nothing added
  // 90:   !myself.right_of right
  // 91:   return myself
  frame->slots[6] /* temp__3 */ = create_closure(entry__11_17, 0);
  // 80: cond
  // 81:   -> key == my_key: return NONE
  // 82:   -> key < my_key:
  // 83:     $left add_item(left_of(myself) key)
  // 84:     if NONE == left: return NONE # nothing added
  // 85:     !myself.left_of left
  // 86:     return myself
  // 87:   -> key > my_key:
  // 88:     $right add_item(right_of(myself) key)
  // 89:     if NONE == right: return NONE # nothing added
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  arguments->slots[2] = frame->slots[6] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__cond();
  func = myself->type;
  frame->cont = cont__11_25;
}
static void entry__11_19(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // myself: 0
  // key: 1
  // return: 2
  // right: 3
  frame->slots[0] = myself->closure.frame->slots[2]; /* myself */
  frame->slots[1] = myself->closure.frame->slots[1]; /* key */
  frame->slots[2] = myself->closure.frame->slots[3]; /* return */
  frame->slots[3] /* right */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 88: ... right_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  result_count = 1;
  myself = var._right_of;
  func = myself->type;
  frame->cont = cont__11_20;
}
static void cont__11_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 88: $right add_item(right_of(myself) key)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* key */;
  result_count = 1;
  myself = var._add_item;
  func = myself->type;
  frame->cont = cont__11_21;
}
static void cont__11_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* right */, arguments->slots[0]);
  // 89: ... NONE == right
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._NONE;
  arguments->slots[1] = frame->slots[3] /* right */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__11_22;
}
static void cont__11_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 89: ... : return NONE # nothing added
  frame->slots[5] /* temp__2 */ = create_closure(entry__11_23, 0);
  // 89: if NONE == right: return NONE # nothing added
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__11_24;
}
static void entry__11_23(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 89: ... return NONE # nothing added
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._NONE;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__11_24(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 90: !myself.right_of right
  frame->slots[4] /* temp__1 */ = frame->slots[3] /* right */;
  // 90: !myself.right_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* myself */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__right_of, frame->slots[4] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* myself */ = temp;

  }
  // 91: return myself
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  result_count = frame->caller_result_count;
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__11_11(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // myself: 0
  // key: 1
  // return: 2
  // left: 3
  frame->slots[0] = myself->closure.frame->slots[2]; /* myself */
  frame->slots[1] = myself->closure.frame->slots[0]; /* key */
  frame->slots[2] = myself->closure.frame->slots[3]; /* return */
  frame->slots[3] /* left */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 83: ... left_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  result_count = 1;
  myself = var._left_of;
  func = myself->type;
  frame->cont = cont__11_12;
}
static void cont__11_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 83: $left add_item(left_of(myself) key)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* key */;
  result_count = 1;
  myself = var._add_item;
  func = myself->type;
  frame->cont = cont__11_13;
}
static void cont__11_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* left */, arguments->slots[0]);
  // 84: ... NONE == left
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._NONE;
  arguments->slots[1] = frame->slots[3] /* left */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__11_14;
}
static void cont__11_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 84: ... : return NONE # nothing added
  frame->slots[5] /* temp__2 */ = create_closure(entry__11_15, 0);
  // 84: if NONE == left: return NONE # nothing added
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__11_16;
}
static void entry__11_15(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 84: ... return NONE # nothing added
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._NONE;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__11_16(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 85: !myself.left_of left
  frame->slots[4] /* temp__1 */ = frame->slots[3] /* left */;
  // 85: !myself.left_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* myself */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__left_of, frame->slots[4] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* myself */ = temp;

  }
  // 86: return myself
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  result_count = frame->caller_result_count;
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__11_8(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 81: ... return NONE
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._NONE;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__11_6(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // key: 0
  // my_key: 1
  // return: 2
  frame->slots[0] = myself->closure.frame->slots[1]; /* key */
  frame->slots[1] = myself->closure.frame->slots[3]; /* my_key */
  frame->slots[2] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 81: ... key == my_key
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* key */;
  arguments->slots[1] = frame->slots[1] /* my_key */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__11_7;
}
static void cont__11_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 81: ... : return NONE
  frame->slots[4] /* temp__2 */ = create_closure(entry__11_8, 0);
  // 81: -> key == my_key: return NONE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__11_9(void) {
  allocate_initialized_frame_gc(4, 6);
  // slot allocations:
  // key: 0
  // my_key: 1
  // myself: 2
  // return: 3
  frame->slots[0] = myself->closure.frame->slots[1]; /* key */
  frame->slots[1] = myself->closure.frame->slots[3]; /* my_key */
  frame->slots[2] = myself->closure.frame->slots[0]; /* myself */
  frame->slots[3] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 82: ... key < my_key
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* key */;
  arguments->slots[1] = frame->slots[1] /* my_key */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__11_10;
}
static void cont__11_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 82: ... :
  // 83:   $left add_item(left_of(myself) key)
  // 84:   if NONE == left: return NONE # nothing added
  // 85:   !myself.left_of left
  // 86:   return myself
  frame->slots[5] /* temp__2 */ = create_closure(entry__11_11, 0);
  // 82: -> key < my_key:
  // 83:   $left add_item(left_of(myself) key)
  // 84:   if NONE == left: return NONE # nothing added
  // 85:   !myself.left_of left
  // 86:   return myself
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__11_17(void) {
  allocate_initialized_frame_gc(4, 6);
  // slot allocations:
  // my_key: 0
  // key: 1
  // myself: 2
  // return: 3
  frame->slots[0] = myself->closure.frame->slots[3]; /* my_key */
  frame->slots[1] = myself->closure.frame->slots[1]; /* key */
  frame->slots[2] = myself->closure.frame->slots[0]; /* myself */
  frame->slots[3] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 87: ... key > my_key
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* my_key */;
  arguments->slots[1] = frame->slots[1] /* key */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__11_18;
}
static void cont__11_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 87: ... :
  // 88:   $right add_item(right_of(myself) key)
  // 89:   if NONE == right: return NONE # nothing added
  // 90:   !myself.right_of right
  // 91:   return myself
  frame->slots[5] /* temp__2 */ = create_closure(entry__11_19, 0);
  // 87: -> key > my_key:
  // 88:   $right add_item(right_of(myself) key)
  // 89:   if NONE == right: return NONE # nothing added
  // 90:   !myself.right_of right
  // 91:   return myself
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__11_25(void) {
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__12_1(void) {
  allocate_initialized_frame_gc(3, 7);
  // slot allocations:
  // myself: 0
  // key: 1
  // return: 2
  // my_key: 3
  frame->slots[2] /* return */ = create_continuation();
  frame->slots[3] /* my_key */ = create_future();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* myself */ = create_cell_with_contents(arguments->slots[0]);
  // 99: ... myself.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__12_2;
}
static void cont__12_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 99: ... : return NONE # nothing removed
  frame->slots[5] /* temp__2 */ = create_closure(entry__12_3, 0);
  // 99: if myself.is_undefined: return NONE # nothing removed
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__12_4;
}
static void entry__12_3(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 99: ... return NONE # nothing removed
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._NONE;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__12_4(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 100: $my_key key_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  result_count = 1;
  myself = get__key_of();
  func = myself->type;
  frame->cont = cont__12_5;
}
static void cont__12_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* my_key */, arguments->slots[0]);
  // 102: -> key == my_key:
  // 103:   $left left_of(myself)
  // 104:   $$right right_of(myself)
  // 105:   if
  // 106:     left.is_defined:
  // 107:       if
  // 108:         right.is_defined:
  // 109:           $head fetch_first(&right)
  // 110:           return types::object(.key_of head .left_of left .right_of right)
  // 111:         :
  // ...
  frame->slots[4] /* temp__1 */ = create_closure(entry__12_6, 0);
  // 115: -> key < my_key:
  // 116:   $left remove_item(left_of(myself) key)
  // 117:   if NONE == left: return NONE # nothing removed
  // 118:   !myself.left_of left
  // 119:   return myself
  frame->slots[5] /* temp__2 */ = create_closure(entry__12_18, 0);
  // 120: -> key > my_key:
  // 121:   $right remove_item(right_of(myself) key)
  // 122:   if NONE == right: return NONE # nothing removed
  // 123:   !myself.right_of right
  // 124:   return myself
  frame->slots[6] /* temp__3 */ = create_closure(entry__12_26, 0);
  // 101: cond
  // 102:   -> key == my_key:
  // 103:     $left left_of(myself)
  // 104:     $$right right_of(myself)
  // 105:     if
  // 106:       left.is_defined:
  // 107:         if
  // 108:           right.is_defined:
  // 109:             $head fetch_first(&right)
  // 110:             return types::object(.key_of head .left_of left .right_of right)
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  arguments->slots[2] = frame->slots[6] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__cond();
  func = myself->type;
  frame->cont = cont__12_34;
}
static void entry__12_28(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // myself: 0
  // key: 1
  // return: 2
  // right: 3
  frame->slots[0] = myself->closure.frame->slots[2]; /* myself */
  frame->slots[1] = myself->closure.frame->slots[1]; /* key */
  frame->slots[2] = myself->closure.frame->slots[3]; /* return */
  frame->slots[3] /* right */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 121: ... right_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  result_count = 1;
  myself = var._right_of;
  func = myself->type;
  frame->cont = cont__12_29;
}
static void cont__12_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 121: $right remove_item(right_of(myself) key)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* key */;
  result_count = 1;
  myself = var._remove_item;
  func = myself->type;
  frame->cont = cont__12_30;
}
static void cont__12_30(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* right */, arguments->slots[0]);
  // 122: ... NONE == right
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._NONE;
  arguments->slots[1] = frame->slots[3] /* right */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__12_31;
}
static void cont__12_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 122: ... : return NONE # nothing removed
  frame->slots[5] /* temp__2 */ = create_closure(entry__12_32, 0);
  // 122: if NONE == right: return NONE # nothing removed
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__12_33;
}
static void entry__12_32(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 122: ... return NONE # nothing removed
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._NONE;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__12_33(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 123: !myself.right_of right
  frame->slots[4] /* temp__1 */ = frame->slots[3] /* right */;
  // 123: !myself.right_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* myself */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__right_of, frame->slots[4] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* myself */ = temp;

  }
  // 124: return myself
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  result_count = frame->caller_result_count;
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__12_20(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // myself: 0
  // key: 1
  // return: 2
  // left: 3
  frame->slots[0] = myself->closure.frame->slots[2]; /* myself */
  frame->slots[1] = myself->closure.frame->slots[0]; /* key */
  frame->slots[2] = myself->closure.frame->slots[3]; /* return */
  frame->slots[3] /* left */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 116: ... left_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  result_count = 1;
  myself = var._left_of;
  func = myself->type;
  frame->cont = cont__12_21;
}
static void cont__12_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 116: $left remove_item(left_of(myself) key)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* key */;
  result_count = 1;
  myself = var._remove_item;
  func = myself->type;
  frame->cont = cont__12_22;
}
static void cont__12_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* left */, arguments->slots[0]);
  // 117: ... NONE == left
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._NONE;
  arguments->slots[1] = frame->slots[3] /* left */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__12_23;
}
static void cont__12_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 117: ... : return NONE # nothing removed
  frame->slots[5] /* temp__2 */ = create_closure(entry__12_24, 0);
  // 117: if NONE == left: return NONE # nothing removed
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__12_25;
}
static void entry__12_24(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 117: ... return NONE # nothing removed
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._NONE;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__12_25(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 118: !myself.left_of left
  frame->slots[4] /* temp__1 */ = frame->slots[3] /* left */;
  // 118: !myself.left_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* myself */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__left_of, frame->slots[4] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* myself */ = temp;

  }
  // 119: return myself
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  result_count = frame->caller_result_count;
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__12_14(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // right: 0
  // return: 1
  // left: 2
  // head: 3
  frame->slots[0] = myself->closure.frame->slots[0]; /* right */
  frame->slots[1] = myself->closure.frame->slots[1]; /* return */
  frame->slots[2] = myself->closure.frame->slots[2]; /* left */
  frame->slots[3] /* head */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 109: $head fetch_first(&right)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* right */;
  result_count = 2;
  myself = var._fetch_first;
  func = myself->type;
  frame->cont = cont__12_15;
}
static void cont__12_15(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* right */ = arguments->slots[0];
  frame->slots[4] /* temp__1 */ = arguments->slots[1];
  // 109: ... head
  initialize_future(frame->slots[3] /* head */, frame->slots[4] /* temp__1 */);
  // 110: ... types::object(.key_of head .left_of left .right_of right)
  {
    NODE *temp = clone_object_and_attributes(get__types__object());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__key_of, frame->slots[3] /* head */);
    set_attribute_value(temp->attributes, poly_idx__left_of, frame->slots[2] /* left */);
    set_attribute_value(temp->attributes, poly_idx__right_of, ((CELL *)frame->slots[0])->contents /* right */);
    frame->slots[4] /* temp__1 */ = temp;

  }
  // 110: return types::object(.key_of head .left_of left .right_of right)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__12_16(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // return: 0
  // left: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* return */
  frame->slots[1] = myself->closure.frame->slots[2]; /* left */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 112: return left
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* left */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__12_12(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // right: 0
  // return: 1
  // left: 2
  frame->slots[0] = myself->closure.frame->slots[3]; /* right */
  frame->slots[1] = myself->closure.frame->slots[1]; /* return */
  frame->slots[2] = myself->closure.frame->slots[2]; /* left */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 108: right.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* right */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__12_13;
}
static void cont__12_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 108: ... :
  // 109:   $head fetch_first(&right)
  // 110:   return types::object(.key_of head .left_of left .right_of right)
  frame->slots[4] /* temp__2 */ = create_closure(entry__12_14, 0);
  // 111: :
  // 112:   return left
  frame->slots[5] /* temp__3 */ = create_closure(entry__12_16, 0);
  // 107: if
  // 108:   right.is_defined:
  // 109:     $head fetch_first(&right)
  // 110:     return types::object(.key_of head .left_of left .right_of right)
  // 111:   :
  // 112:     return left
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
static void entry__12_17(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // return: 0
  // right: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* return */
  frame->slots[1] = myself->closure.frame->slots[3]; /* right */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 114: return right
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* right */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__12_8(void) {
  allocate_initialized_frame_gc(2, 7);
  // slot allocations:
  // myself: 0
  // return: 1
  // left: 2
  // right: 3
  frame->slots[0] = myself->closure.frame->slots[2]; /* myself */
  frame->slots[1] = myself->closure.frame->slots[3]; /* return */
  frame->slots[2] /* left */ = create_future();
  frame->slots[3] /* right */ = create_cell();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 103: $left left_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  result_count = 1;
  myself = var._left_of;
  func = myself->type;
  frame->cont = cont__12_9;
}
static void cont__12_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* left */, arguments->slots[0]);
  // 104: $$right right_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  result_count = 1;
  myself = var._right_of;
  func = myself->type;
  frame->cont = cont__12_10;
}
static void cont__12_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* right */ = arguments->slots[0];
  // 106: left.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* left */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__12_11;
}
static void cont__12_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 106: ... :
  // 107:   if
  // 108:     right.is_defined:
  // 109:       $head fetch_first(&right)
  // 110:       return types::object(.key_of head .left_of left .right_of right)
  // 111:     :
  // 112:       return left
  frame->slots[5] /* temp__2 */ = create_closure(entry__12_12, 0);
  // 113: :
  // 114:   return right
  frame->slots[6] /* temp__3 */ = create_closure(entry__12_17, 0);
  // 105: if
  // 106:   left.is_defined:
  // 107:     if
  // 108:       right.is_defined:
  // 109:         $head fetch_first(&right)
  // 110:         return types::object(.key_of head .left_of left .right_of right)
  // 111:       :
  // 112:         return left
  // 113:   :
  // 114:     return right
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
static void entry__12_6(void) {
  allocate_initialized_frame_gc(4, 6);
  // slot allocations:
  // key: 0
  // my_key: 1
  // myself: 2
  // return: 3
  frame->slots[0] = myself->closure.frame->slots[1]; /* key */
  frame->slots[1] = myself->closure.frame->slots[3]; /* my_key */
  frame->slots[2] = myself->closure.frame->slots[0]; /* myself */
  frame->slots[3] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 102: ... key == my_key
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* key */;
  arguments->slots[1] = frame->slots[1] /* my_key */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__12_7;
}
static void cont__12_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 102: ... :
  // 103:   $left left_of(myself)
  // 104:   $$right right_of(myself)
  // 105:   if
  // 106:     left.is_defined:
  // 107:       if
  // 108:         right.is_defined:
  // 109:           $head fetch_first(&right)
  // 110:           return types::object(.key_of head .left_of left .right_of right)
  // 111:         :
  // ...
  frame->slots[5] /* temp__2 */ = create_closure(entry__12_8, 0);
  // 102: -> key == my_key:
  // 103:   $left left_of(myself)
  // 104:   $$right right_of(myself)
  // 105:   if
  // 106:     left.is_defined:
  // 107:       if
  // 108:         right.is_defined:
  // 109:           $head fetch_first(&right)
  // 110:           return types::object(.key_of head .left_of left .right_of right)
  // 111:         :
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__12_18(void) {
  allocate_initialized_frame_gc(4, 6);
  // slot allocations:
  // key: 0
  // my_key: 1
  // myself: 2
  // return: 3
  frame->slots[0] = myself->closure.frame->slots[1]; /* key */
  frame->slots[1] = myself->closure.frame->slots[3]; /* my_key */
  frame->slots[2] = myself->closure.frame->slots[0]; /* myself */
  frame->slots[3] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 115: ... key < my_key
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* key */;
  arguments->slots[1] = frame->slots[1] /* my_key */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__12_19;
}
static void cont__12_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 115: ... :
  // 116:   $left remove_item(left_of(myself) key)
  // 117:   if NONE == left: return NONE # nothing removed
  // 118:   !myself.left_of left
  // 119:   return myself
  frame->slots[5] /* temp__2 */ = create_closure(entry__12_20, 0);
  // 115: -> key < my_key:
  // 116:   $left remove_item(left_of(myself) key)
  // 117:   if NONE == left: return NONE # nothing removed
  // 118:   !myself.left_of left
  // 119:   return myself
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__12_26(void) {
  allocate_initialized_frame_gc(4, 6);
  // slot allocations:
  // my_key: 0
  // key: 1
  // myself: 2
  // return: 3
  frame->slots[0] = myself->closure.frame->slots[3]; /* my_key */
  frame->slots[1] = myself->closure.frame->slots[1]; /* key */
  frame->slots[2] = myself->closure.frame->slots[0]; /* myself */
  frame->slots[3] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 120: ... key > my_key
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* my_key */;
  arguments->slots[1] = frame->slots[1] /* key */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__12_27;
}
static void cont__12_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 120: ... :
  // 121:   $right remove_item(right_of(myself) key)
  // 122:   if NONE == right: return NONE # nothing removed
  // 123:   !myself.right_of right
  // 124:   return myself
  frame->slots[5] /* temp__2 */ = create_closure(entry__12_28, 0);
  // 120: -> key > my_key:
  // 121:   $right remove_item(right_of(myself) key)
  // 122:   if NONE == right: return NONE # nothing removed
  // 123:   !myself.right_of right
  // 124:   return myself
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__12_34(void) {
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__13_1(void) {
  allocate_initialized_frame_gc(4, 7);
  // slot allocations:
  // key: 0
  // value: 1
  // myself: 2
  // return: 3
  frame->slots[3] /* return */ = create_continuation();
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  if (argument_count > 2) {
    too_many_arguments_error();
    return;
  }
  switch(argument_count) {
    default: frame->slots[1] /* value */ = arguments->slots[1];
    case 1:;
  }
  switch(argument_count) {
    case 1: frame->slots[1] /* value */ = var._NONE;
  }
  frame->slots[2] /* myself */ = create_cell_with_contents(myself);
  // 135: ... :
  // 136:   return get_item(tree_of(myself) key)
  frame->slots[4] /* temp__1 */ = create_closure(entry__13_2, 0);
  // 137: ... :
  // 138:   $new_tree add_item(tree_of(myself) key)
  // 139:   if NONE != new_tree:
  // 140:     !myself.tree_of new_tree
  // 141:     inc &myself.length_of
  // 142:   return myself
  frame->slots[5] /* temp__2 */ = create_closure(entry__13_5, 0);
  // 143: ... :
  // 144:   $new_tree remove_item(tree_of(myself) key)
  // 145:   if NONE != new_tree:
  // 146:     !myself.tree_of new_tree
  // 147:     dec &myself.length_of
  // 148:   return myself
  frame->slots[6] /* temp__3 */ = create_closure(entry__13_14, 0);
  // 133: case
  // 134:   value
  // 135:   NONE:
  // 136:     return get_item(tree_of(myself) key)
  // 137:   true:
  // 138:     $new_tree add_item(tree_of(myself) key)
  // 139:     if NONE != new_tree:
  // 140:       !myself.tree_of new_tree
  // 141:       inc &myself.length_of
  // 142:     return myself
  // ...
  argument_count = 8;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* value */;
  arguments->slots[1] = var._NONE;
  arguments->slots[2] = frame->slots[4] /* temp__1 */;
  arguments->slots[3] = get__true();
  arguments->slots[4] = frame->slots[5] /* temp__2 */;
  arguments->slots[5] = get__false();
  arguments->slots[6] = frame->slots[6] /* temp__3 */;
  arguments->slots[7] = func__13_23;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame->cont = cont__13_25;
}
static void entry__13_2(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // return: 0
  // myself: 1
  // key: 2
  frame->slots[0] = myself->closure.frame->slots[3]; /* return */
  frame->slots[1] = myself->closure.frame->slots[2]; /* myself */
  frame->slots[2] = myself->closure.frame->slots[0]; /* key */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 136: ... tree_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* myself */;
  result_count = 1;
  myself = var._tree_of;
  func = myself->type;
  frame->cont = cont__13_3;
}
static void cont__13_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 136: ... get_item(tree_of(myself) key)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[2] /* key */;
  result_count = 1;
  myself = var._get_item;
  func = myself->type;
  frame->cont = cont__13_4;
}
static void cont__13_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 136: return get_item(tree_of(myself) key)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__13_5(void) {
  allocate_initialized_frame_gc(3, 7);
  // slot allocations:
  // myself: 0
  // key: 1
  // return: 2
  // new_tree: 3
  frame->slots[0] = myself->closure.frame->slots[2]; /* myself */
  frame->slots[1] = myself->closure.frame->slots[0]; /* key */
  frame->slots[2] = myself->closure.frame->slots[3]; /* return */
  frame->slots[3] /* new_tree */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 138: ... tree_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  result_count = 1;
  myself = var._tree_of;
  func = myself->type;
  frame->cont = cont__13_6;
}
static void cont__13_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 138: $new_tree add_item(tree_of(myself) key)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* key */;
  result_count = 1;
  myself = var._add_item;
  func = myself->type;
  frame->cont = cont__13_7;
}
static void cont__13_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* new_tree */, arguments->slots[0]);
  // 139: ... NONE != new_tree
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._NONE;
  arguments->slots[1] = frame->slots[3] /* new_tree */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__13_8;
}
static void cont__13_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 139: ... NONE != new_tree
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__13_9;
}
static void cont__13_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 139: ... :
  // 140:   !myself.tree_of new_tree
  // 141:   inc &myself.length_of
  frame->slots[6] /* temp__3 */ = create_closure(entry__13_10, 0);
  // 139: if NONE != new_tree:
  // 140:   !myself.tree_of new_tree
  // 141:   inc &myself.length_of
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__13_13;
}
static void entry__13_10(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // myself: 0
  // new_tree: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* myself */
  frame->slots[1] = myself->closure.frame->slots[3]; /* new_tree */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 140: !myself.tree_of new_tree
  frame->slots[2] /* temp__1 */ = frame->slots[1] /* new_tree */;
  // 140: !myself.tree_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* myself */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__tree_of, frame->slots[2] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* myself */ = temp;

  }
  // 141: ... myself.length_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__13_11;
}
static void cont__13_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 141: inc &myself.length_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__13_12;
}
static void cont__13_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 141: ... &myself.length_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* myself */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__length_of, frame->slots[3] /* temp__2 */);
    ((CELL *)frame->slots[0])->contents /* myself */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__13_13(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 142: return myself
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  result_count = frame->caller_result_count;
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__13_14(void) {
  allocate_initialized_frame_gc(3, 7);
  // slot allocations:
  // myself: 0
  // key: 1
  // return: 2
  // new_tree: 3
  frame->slots[0] = myself->closure.frame->slots[2]; /* myself */
  frame->slots[1] = myself->closure.frame->slots[0]; /* key */
  frame->slots[2] = myself->closure.frame->slots[3]; /* return */
  frame->slots[3] /* new_tree */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 144: ... tree_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  result_count = 1;
  myself = var._tree_of;
  func = myself->type;
  frame->cont = cont__13_15;
}
static void cont__13_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 144: $new_tree remove_item(tree_of(myself) key)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* key */;
  result_count = 1;
  myself = var._remove_item;
  func = myself->type;
  frame->cont = cont__13_16;
}
static void cont__13_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* new_tree */, arguments->slots[0]);
  // 145: ... NONE != new_tree
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._NONE;
  arguments->slots[1] = frame->slots[3] /* new_tree */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__13_17;
}
static void cont__13_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 145: ... NONE != new_tree
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__13_18;
}
static void cont__13_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 145: ... :
  // 146:   !myself.tree_of new_tree
  // 147:   dec &myself.length_of
  frame->slots[6] /* temp__3 */ = create_closure(entry__13_19, 0);
  // 145: if NONE != new_tree:
  // 146:   !myself.tree_of new_tree
  // 147:   dec &myself.length_of
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__13_22;
}
static void entry__13_19(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // myself: 0
  // new_tree: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* myself */
  frame->slots[1] = myself->closure.frame->slots[3]; /* new_tree */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 146: !myself.tree_of new_tree
  frame->slots[2] /* temp__1 */ = frame->slots[1] /* new_tree */;
  // 146: !myself.tree_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* myself */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__tree_of, frame->slots[2] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* myself */ = temp;

  }
  // 147: ... myself.length_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__13_20;
}
static void cont__13_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 147: dec &myself.length_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__dec();
  func = myself->type;
  frame->cont = cont__13_21;
}
static void cont__13_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 147: ... &myself.length_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* myself */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__length_of, frame->slots[3] /* temp__2 */);
    ((CELL *)frame->slots[0])->contents /* myself */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__13_22(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 148: return myself
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  result_count = frame->caller_result_count;
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__13_23(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 150: Error "Attempt to set a set element to a nonboolean value!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__13_24;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__13_25(void) {
  myself = frame->slots[3] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__18_1(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 157: ... -> types::key_order_set
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var.types__key_order_set;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__19_3(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // myself: 0
  // body: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* myself */
  frame->slots[1] = myself->closure.frame->slots[1]; /* body */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 161: ... left_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* myself */;
  result_count = 1;
  myself = var._left_of;
  func = myself->type;
  frame->cont = cont__19_4;
}
static void cont__19_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 161: for_each_item left_of(myself) body
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* body */;
  result_count = 0;
  myself = var._for_each_item;
  func = myself->type;
  frame->cont = cont__19_5;
}
static void cont__19_5(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 162: ... key_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* myself */;
  result_count = 1;
  myself = get__key_of();
  func = myself->type;
  frame->cont = cont__19_6;
}
static void cont__19_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 162: body key_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = frame->slots[1] /* body */;
  func = myself->type;
  frame->cont = cont__19_7;
}
static void cont__19_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 163: ... right_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* myself */;
  result_count = 1;
  myself = var._right_of;
  func = myself->type;
  frame->cont = cont__19_8;
}
static void cont__19_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 163: for_each_item right_of(myself) body
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* body */;
  result_count = frame->caller_result_count;
  myself = var._for_each_item;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__19_1(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // myself: 0
  // body: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 160: ... myself.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* myself */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__19_2;
}
static void cont__19_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 160: ... :
  // 161:   for_each_item left_of(myself) body
  // 162:   body key_of(myself)
  // 163:   for_each_item right_of(myself) body
  frame->slots[3] /* temp__2 */ = create_closure(entry__19_3, 0);
  // 160: if myself.is_defined:
  // 161:   for_each_item left_of(myself) body
  // 162:   body key_of(myself)
  // 163:   for_each_item right_of(myself) body
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__20_4(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // tree: 0
  // body: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* tree */
  frame->slots[1] = myself->closure.frame->slots[1]; /* body */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 167: ... for_each_item tree body
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* tree */;
  arguments->slots[1] = frame->slots[1] /* body */;
  result_count = frame->caller_result_count;
  myself = var._for_each_item;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__20_1(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // self: 0
  // body: 1
  // tree: 2
  frame->slots[2] /* tree */ = create_future();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 166: $tree tree_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = var._tree_of;
  func = myself->type;
  frame->cont = cont__20_2;
}
static void cont__20_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* tree */, arguments->slots[0]);
  // 167: ... tree.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* tree */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__20_3;
}
static void cont__20_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 167: ... : for_each_item tree body
  frame->slots[4] /* temp__2 */ = create_closure(entry__20_4, 0);
  // 167: if tree.is_defined: for_each_item tree body
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
EXPORT void collect__basic__types__key_order_set(void) {
  var._NONE = collect_node(var._NONE);
  unique__1_1 = collect_node(unique__1_1);
  var._tree_of = collect_node(var._tree_of);
  var._left_of = collect_node(var._left_of);
  var._right_of = collect_node(var._right_of);
  var.types__key_order_set = collect_node(var.types__key_order_set);
  var._empty_node = collect_node(var._empty_node);
  var._fetch_first = collect_node(var._fetch_first);
  var._get_item = collect_node(var._get_item);
  var._add_item = collect_node(var._add_item);
  var._remove_item = collect_node(var._remove_item);
  string__13_24 = collect_node(string__13_24);
  string__16_1 = collect_node(string__16_1);
  var.std__empty_key_order_set = collect_node(var.std__empty_key_order_set);
  var.std__key_order_set = collect_node(var.std__key_order_set);
  var._for_each_item = collect_node(var._for_each_item);
}

static int already_run_phase_1 = false;

EXPORT void phase_1__basic__types__key_order_set(void) {
  if (already_run_phase_1) return;
  already_run_phase_1 = true;
  register_module_info(&module_info);
  register_polymorphic_function_with_setter("_basic__types__key_order_set::tree_of", &poly_idx__tree_of);
  register_polymorphic_function_with_setter("_basic__types__key_order_set::left_of", &poly_idx__left_of);
  register_polymorphic_function_with_setter("_basic__types__key_order_set::right_of", &poly_idx__right_of);
}

static int already_run_phase_2 = false;

EXPORT void phase_2__basic__types__key_order_set(void) {
  if (already_run_phase_2) return;
  already_run_phase_2 = true;
  number__0 = from_uint32(0U);
  func__9_1 = create_function(entry__9_1, 1);
  func__10_1 = create_function(entry__10_1, 2);
  func__11_1 = create_function(entry__11_1, 2);
  func__12_1 = create_function(entry__12_1, 2);
  func__13_23 = create_function(entry__13_23, 0);
  func__18_1 = create_function(entry__18_1, 0);
  func__19_1 = create_function(entry__19_1, 2);
  func__20_1 = create_function(entry__20_1, 2);
}

static int already_run_phase_3 = false;

EXPORT void phase_3__basic__types__key_order_set(void) {
  if (already_run_phase_3) return;
  already_run_phase_3 = true;
  set_module("basic__types__key_order_set");
  set_used_namespaces(used_namespaces);
  unique__1_1 = register_unique_item("NONE");
  assign_value(&var._NONE, unique__1_1);
  define_single_assign_static("types", "key_order_set", get__types__key_order_set, &var.types__key_order_set);
  string__13_24 = from_latin_1_string("Attempt to set a set element to a nonboolean value!", 51);
  string__16_1 = from_latin_1_string("key_order_set", 13);
  define_single_assign_static("std", "empty_key_order_set", get__std__empty_key_order_set, &var.std__empty_key_order_set);
  define_single_assign_static("std", "key_order_set", get__std__key_order_set, &var.std__key_order_set);
}

static int already_run_phase_4 = false;

EXPORT void phase_4__basic__types__key_order_set(void) {
  if (already_run_phase_4) return;
  already_run_phase_4 = true;
  set_module("basic__types__key_order_set");
  set_used_namespaces(used_namespaces);
  use_read_only(NULL, "Error", &get__Error, &get_value_or_future__Error);
  use_read_only(NULL, "case", &get__case, &get_value_or_future__case);
  use_read_only(NULL, "cond", &get__cond, &get_value_or_future__cond);
  use_read_only(NULL, "dec", &get__dec, &get_value_or_future__dec);
  use_read_only(NULL, "false", &get__false, &get_value_or_future__false);
  use_polymorphic_function(NULL, "for_each", &get__for_each, &poly_idx__for_each);
  use_read_only(NULL, "if", &get__if, &get_value_or_future__if);
  use_read_only(NULL, "inc", &get__inc, &get_value_or_future__inc);
  use_read_only(NULL, "is_defined", &get__is_defined, &get_value_or_future__is_defined);
  use_read_only(NULL, "is_undefined", &get__is_undefined, &get_value_or_future__is_undefined);
  use_polymorphic_function(NULL, "key_of", &get__key_of, &poly_idx__key_of);
  use_polymorphic_function(NULL, "length_of", &get__length_of, &poly_idx__length_of);
  use_polymorphic_function(NULL, "serialization_tag_of", &get__serialization_tag_of, &poly_idx__serialization_tag_of);
  use_read_only("std", "equal", &get__std__equal, &get_value_or_future__std__equal);
  use_read_only("std", "less", &get__std__less, &get_value_or_future__std__less);
  use_read_only("std", "not", &get__std__not, &get_value_or_future__std__not);
  use_read_only(NULL, "true", &get__true, &get_value_or_future__true);
  use_read_only("types", "generic_set", &get__types__generic_set, &get_value_or_future__types__generic_set);
  use_read_only("types", "object", &get__types__object, &get_value_or_future__types__object);
  use_read_only(NULL, "undefined", &get__undefined, &get_value_or_future__undefined);
  update_start_p = node_p;
  def_attribute(&var._empty_node, poly_idx__left_of, MAKE_ATTRIBUTE_VALUE(get__undefined()));
  update_start_p = node_p;
  def_attribute(&var._empty_node, poly_idx__right_of, MAKE_ATTRIBUTE_VALUE(get__undefined()));
  define_type_function("types", "key_order_set", entry__13_1, -1);
  define_attribute("types", "key_order_set", poly_idx__tree_of, get__undefined());
  define_attribute("types", "key_order_set", poly_idx__length_of, number__0);
  define_attribute("types", "key_order_set", poly_idx__serialization_tag_of, string__16_1);
  define_method("types", "key_order_set", poly_idx__for_each, func__20_1);
}

static int already_run_phase_5 = false;

EXPORT void phase_5__basic__types__key_order_set(void) {
  if (already_run_phase_5) return;
  already_run_phase_5 = true;
  assign_value(&var._tree_of, create_function(type__tree_of, -1));
  assign_value(&var._left_of, create_function(type__left_of, -1));
  assign_value(&var._right_of, create_function(type__right_of, -1));
  assign_value(&var.types__key_order_set, get__types__generic_set());
  assign_value(&var._empty_node, get__types__object());
  assign_variable(&var._fetch_first, &func__9_1);
  assign_variable(&var._get_item, &func__10_1);
  assign_variable(&var._add_item, &func__11_1);
  assign_variable(&var._remove_item, &func__12_1);
  assign_variable(&var.std__empty_key_order_set, &var.types__key_order_set);
  assign_variable(&var.std__key_order_set, &func__18_1);
  assign_variable(&var._for_each_item, &func__19_1);
}

static int already_run_phase_6 = false;

EXPORT void phase_6__basic__types__key_order_set(void) {
  if (already_run_phase_6) return;
  already_run_phase_6 = true;
  register_collector(collect__basic__types__key_order_set);
}
