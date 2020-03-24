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
REGISTER NODE *myself ASM("r13");
REGISTER int argument_count ASM("ebx");
IMPORT void invalid_arguments_error(void);
REGISTER FRAME *arguments ASM("r12");
IMPORT void *node_p;
IMPORT int result_count;
IMPORT void invalid_results_error(void);
IMPORT NODE *create_closure(FUNC type, int par_count);
IMPORT void too_few_arguments_error(void);
IMPORT void too_many_arguments_error(void);
IMPORT NODE *undefined;
IMPORT NODE *create_future(void);
IMPORT void initialize_future(NODE *var, NODE *val);
IMPORT NODE *collect_node(NODE *node);
IMPORT void register_module_info(MODULE_INFO *info);
IMPORT NODE *from_uint32(uint32_t val);
IMPORT NODE *create_function(FUNC func, int par_count);
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
static NODE_GETTER get__do_until;
static NODE_GETTER get_value_or_future__do_until;
static NODE_GETTER get__do_while;
static NODE_GETTER get_value_or_future__do_while;
static NODE_GETTER get__forever;
static NODE_GETTER get_value_or_future__forever;
static NODE_GETTER get__if;
static NODE_GETTER get_value_or_future__if;
static NODE_GETTER get__is_defined;
static NODE_GETTER get_value_or_future__is_defined;
static NODE_GETTER get__repeat;
static NODE_GETTER get_value_or_future__repeat;
static NODE_GETTER get__std__less;
static NODE_GETTER get_value_or_future__std__less;
static NODE_GETTER get__std__minus;
static NODE_GETTER get_value_or_future__std__minus;
static NODE_GETTER get__std__not;
static NODE_GETTER get_value_or_future__std__not;
static NODE_GETTER get__std__plus;
static NODE_GETTER get_value_or_future__std__plus;
static NODE_GETTER get__unless;
static NODE_GETTER get_value_or_future__unless;
static NODE_GETTER get__while;
static NODE_GETTER get_value_or_future__while;
static struct {
  NODE *_from_to_1;
  NODE *_from_to_2;
  NODE *_from_to_by_1;
  NODE *_from_to_by_2;
  NODE *_from_down_to_1;
  NODE *_from_down_to_2;
  NODE *_from_down_to_by_1;
  NODE *_from_down_to_by_2;
  NODE *std__from_to;
  NODE *std__from_to_by;
  NODE *std__from_down_to;
  NODE *std__from_down_to_by;
  NODE *std__repeat;
  NODE *std__forever;
  NODE *std__while;
  NODE *std__do_while;
  NODE *std__do_until;
} var;
static const char *var_names[] = {
  "from_to_1",
  "from_to_2",
  "from_to_by_1",
  "from_to_by_2",
  "from_down_to_1",
  "from_down_to_2",
  "from_down_to_by_1",
  "from_down_to_by_2"
};
static NODE *func__1_1;
static void entry__1_1(void);
static FRAME_INFO frame__1_1 = {4, {"first", "last", "body", "body2"}};
static void cont__1_2(void);
static NODE *func__1_3;
static void entry__1_3(void);
static FRAME_INFO frame__1_3 = {4, {"last", "first", "body", "body2"}};
static void cont__1_4(void);
static void cont__1_5(void);
static NODE *func__1_6;
static void entry__1_6(void);
static FRAME_INFO frame__1_6 = {2, {"body", "first"}};
static void cont__1_7(void);
static void cont__1_8(void);
static NODE *func__1_9;
static void entry__1_9(void);
static FRAME_INFO frame__1_9 = {3, {"first", "last", "body"}};
static NODE *get__std__from_to(void) {
  return var.std__from_to;
}
static NODE *func__2_1;
static void entry__2_1(void);
static FRAME_INFO frame__2_1 = {3, {"s", "e", "body"}};
static void cont__2_2(void);
static void cont__2_3(void);
static NODE *func__2_4;
static void entry__2_4(void);
static FRAME_INFO frame__2_4 = {3, {"body", "s", "e"}};
static void cont__2_5(void);
static void cont__2_6(void);
static NODE *func__3_1;
static void entry__3_1(void);
static FRAME_INFO frame__3_1 = {4, {"s", "e", "body", "body2"}};
static void cont__3_2(void);
static void cont__3_3(void);
static NODE *func__3_4;
static void entry__3_4(void);
static FRAME_INFO frame__3_4 = {4, {"body2", "body", "s", "e"}};
static void cont__3_5(void);
static void cont__3_6(void);
static void cont__3_7(void);
static NODE *func__4_1;
static void entry__4_1(void);
static FRAME_INFO frame__4_1 = {5, {"first", "last", "step", "body", "body2"}};
static void cont__4_2(void);
static NODE *func__4_3;
static void entry__4_3(void);
static FRAME_INFO frame__4_3 = {5, {"last", "first", "body", "step", "body2"}};
static void cont__4_4(void);
static void cont__4_5(void);
static NODE *func__4_6;
static void entry__4_6(void);
static FRAME_INFO frame__4_6 = {2, {"body", "first"}};
static void cont__4_7(void);
static void cont__4_8(void);
static NODE *func__4_9;
static void entry__4_9(void);
static FRAME_INFO frame__4_9 = {4, {"first", "last", "step", "body"}};
static NODE *get__std__from_to_by(void) {
  return var.std__from_to_by;
}
static NODE *func__5_1;
static void entry__5_1(void);
static FRAME_INFO frame__5_1 = {4, {"s", "e", "step", "body"}};
static void cont__5_2(void);
static void cont__5_3(void);
static NODE *func__5_4;
static void entry__5_4(void);
static FRAME_INFO frame__5_4 = {4, {"body", "s", "step", "e"}};
static void cont__5_5(void);
static void cont__5_6(void);
static NODE *func__6_1;
static void entry__6_1(void);
static FRAME_INFO frame__6_1 = {5, {"s", "e", "step", "body", "body2"}};
static void cont__6_2(void);
static void cont__6_3(void);
static NODE *func__6_4;
static void entry__6_4(void);
static FRAME_INFO frame__6_4 = {5, {"body2", "body", "s", "step", "e"}};
static void cont__6_5(void);
static void cont__6_6(void);
static void cont__6_7(void);
static NODE *func__7_1;
static void entry__7_1(void);
static FRAME_INFO frame__7_1 = {4, {"first", "last", "body", "body2"}};
static void cont__7_2(void);
static NODE *func__7_3;
static void entry__7_3(void);
static FRAME_INFO frame__7_3 = {4, {"first", "last", "body", "body2"}};
static void cont__7_4(void);
static void cont__7_5(void);
static NODE *func__7_6;
static void entry__7_6(void);
static FRAME_INFO frame__7_6 = {2, {"body", "first"}};
static void cont__7_7(void);
static void cont__7_8(void);
static NODE *func__7_9;
static void entry__7_9(void);
static FRAME_INFO frame__7_9 = {3, {"first", "last", "body"}};
static NODE *get__std__from_down_to(void) {
  return var.std__from_down_to;
}
static NODE *func__8_1;
static void entry__8_1(void);
static FRAME_INFO frame__8_1 = {3, {"s", "e", "body"}};
static void cont__8_2(void);
static void cont__8_3(void);
static NODE *func__8_4;
static void entry__8_4(void);
static FRAME_INFO frame__8_4 = {3, {"body", "s", "e"}};
static void cont__8_5(void);
static void cont__8_6(void);
static NODE *func__9_1;
static void entry__9_1(void);
static FRAME_INFO frame__9_1 = {4, {"s", "e", "body", "body2"}};
static void cont__9_2(void);
static void cont__9_3(void);
static NODE *func__9_4;
static void entry__9_4(void);
static FRAME_INFO frame__9_4 = {4, {"body2", "body", "s", "e"}};
static void cont__9_5(void);
static void cont__9_6(void);
static void cont__9_7(void);
static NODE *func__10_1;
static void entry__10_1(void);
static FRAME_INFO frame__10_1 = {5, {"first", "last", "step", "body", "body2"}};
static void cont__10_2(void);
static NODE *func__10_3;
static void entry__10_3(void);
static FRAME_INFO frame__10_3 = {5, {"first", "last", "body", "step", "body2"}};
static void cont__10_4(void);
static void cont__10_5(void);
static NODE *func__10_6;
static void entry__10_6(void);
static FRAME_INFO frame__10_6 = {2, {"body", "first"}};
static void cont__10_7(void);
static void cont__10_8(void);
static NODE *func__10_9;
static void entry__10_9(void);
static FRAME_INFO frame__10_9 = {4, {"first", "last", "step", "body"}};
static NODE *get__std__from_down_to_by(void) {
  return var.std__from_down_to_by;
}
static NODE *func__11_1;
static void entry__11_1(void);
static FRAME_INFO frame__11_1 = {4, {"s", "e", "step", "body"}};
static void cont__11_2(void);
static void cont__11_3(void);
static NODE *func__11_4;
static void entry__11_4(void);
static FRAME_INFO frame__11_4 = {4, {"body", "s", "step", "e"}};
static void cont__11_5(void);
static void cont__11_6(void);
static NODE *func__12_1;
static void entry__12_1(void);
static FRAME_INFO frame__12_1 = {5, {"s", "e", "step", "body", "body2"}};
static void cont__12_2(void);
static void cont__12_3(void);
static NODE *func__12_4;
static void entry__12_4(void);
static FRAME_INFO frame__12_4 = {5, {"body2", "body", "s", "step", "e"}};
static void cont__12_5(void);
static void cont__12_6(void);
static void cont__12_7(void);
static NODE *func__13_1;
static void entry__13_1(void);
static FRAME_INFO frame__13_1 = {2, {"n", "body"}};
static void cont__13_2(void);
static void cont__13_3(void);
static NODE *func__13_4;
static void entry__13_4(void);
static FRAME_INFO frame__13_4 = {2, {"body", "n"}};
static void cont__13_5(void);
static void cont__13_6(void);
static NODE *get__std__repeat(void) {
  return var.std__repeat;
}
static NODE *func__14_1;
static void entry__14_1(void);
static FRAME_INFO frame__14_1 = {1, {"body"}};
static void cont__14_2(void);
static NODE *get__std__forever(void) {
  return var.std__forever;
}
static NODE *func__15_1;
static void entry__15_1(void);
static FRAME_INFO frame__15_1 = {3, {"cond_and_body", "cond", "body"}};
static void cont__15_2(void);
static NODE *func__15_3;
static void entry__15_3(void);
static FRAME_INFO frame__15_3 = {2, {"body", "cond_and_body"}};
static void cont__15_4(void);
static NODE *get__std__while(void) {
  return var.std__while;
}
static NODE *func__16_1;
static void entry__16_1(void);
static FRAME_INFO frame__16_1 = {1, {"body"}};
static void cont__16_2(void);
static NODE *func__16_3;
static void entry__16_3(void);
static FRAME_INFO frame__16_3 = {1, {"body"}};
static NODE *get__std__do_while(void) {
  return var.std__do_while;
}
static NODE *func__17_1;
static void entry__17_1(void);
static FRAME_INFO frame__17_1 = {1, {"body"}};
static void cont__17_2(void);
static NODE *func__17_3;
static void entry__17_3(void);
static FRAME_INFO frame__17_3 = {1, {"body"}};
static NODE *get__std__do_until(void) {
  return var.std__do_until;
}
void run__basic__loops(void);

static CONTINUATION_INFO continuation_info[] = {
  {run__basic__loops, NULL, },
  {entry__1_6, NULL, 87, 87, 25, 34},
  {entry__1_3, NULL, 87, 87, 10, 22},
  {cont__1_4, &frame__1_3, 87, 87, 10, 22},
  {cont__1_5, &frame__1_3, 87, 87, 7, 34},
  {cont__1_7, &frame__1_3, 88, 88, 17, 23},
  {cont__1_8, &frame__1_3, 88, 88, 7, 39},
  {entry__1_9, NULL, 90, 90, 7, 31},
  {entry__1_1, NULL, 86, 86, 5, 20},
  {cont__1_2, &frame__1_1, 85, 90, 3, 32},
  {entry__2_4, NULL, 94, 94, 5, 10},
  {cont__2_5, &frame__2_4, 95, 95, 15, 17},
  {cont__2_6, &frame__2_4, 95, 95, 5, 24},
  {entry__2_1, NULL, 93, 93, 6, 11},
  {cont__2_2, &frame__2_1, 93, 93, 6, 11},
  {cont__2_3, &frame__2_1, 93, 95, 3, 24},
  {entry__3_4, NULL, 99, 99, 5, 9},
  {cont__3_5, &frame__3_4, 100, 100, 5, 10},
  {cont__3_6, &frame__3_4, 101, 101, 15, 17},
  {cont__3_7, &frame__3_4, 101, 101, 5, 30},
  {entry__3_1, NULL, 98, 98, 6, 11},
  {cont__3_2, &frame__3_1, 98, 98, 6, 11},
  {cont__3_3, &frame__3_1, 98, 101, 3, 30},
  {entry__4_6, NULL, 163, 163, 25, 34},
  {entry__4_3, NULL, 163, 163, 10, 22},
  {cont__4_4, &frame__4_3, 163, 163, 10, 22},
  {cont__4_5, &frame__4_3, 163, 163, 7, 34},
  {cont__4_7, &frame__4_3, 164, 164, 20, 29},
  {cont__4_8, &frame__4_3, 164, 164, 7, 50},
  {entry__4_9, NULL, 166, 166, 7, 39},
  {entry__4_1, NULL, 162, 162, 5, 20},
  {cont__4_2, &frame__4_1, 161, 166, 3, 40},
  {entry__5_4, NULL, 170, 170, 5, 10},
  {cont__5_5, &frame__5_4, 171, 171, 18, 23},
  {cont__5_6, &frame__5_4, 171, 171, 5, 35},
  {entry__5_1, NULL, 169, 169, 6, 11},
  {cont__5_2, &frame__5_1, 169, 169, 6, 11},
  {cont__5_3, &frame__5_1, 169, 171, 3, 35},
  {entry__6_4, NULL, 175, 175, 5, 9},
  {cont__6_5, &frame__6_4, 176, 176, 5, 10},
  {cont__6_6, &frame__6_4, 177, 177, 18, 23},
  {cont__6_7, &frame__6_4, 177, 177, 5, 41},
  {entry__6_1, NULL, 174, 174, 6, 11},
  {cont__6_2, &frame__6_1, 174, 174, 6, 11},
  {cont__6_3, &frame__6_1, 174, 177, 3, 41},
  {entry__7_6, NULL, 234, 234, 25, 34},
  {entry__7_3, NULL, 234, 234, 10, 22},
  {cont__7_4, &frame__7_3, 234, 234, 10, 22},
  {cont__7_5, &frame__7_3, 234, 234, 7, 34},
  {cont__7_7, &frame__7_3, 235, 235, 22, 28},
  {cont__7_8, &frame__7_3, 235, 235, 7, 44},
  {entry__7_9, NULL, 237, 237, 7, 36},
  {entry__7_1, NULL, 233, 233, 5, 20},
  {cont__7_2, &frame__7_1, 232, 237, 3, 37},
  {entry__8_4, NULL, 241, 241, 5, 10},
  {cont__8_5, &frame__8_4, 242, 242, 20, 22},
  {cont__8_6, &frame__8_4, 242, 242, 5, 29},
  {entry__8_1, NULL, 240, 240, 6, 11},
  {cont__8_2, &frame__8_1, 240, 240, 6, 11},
  {cont__8_3, &frame__8_1, 240, 242, 3, 29},
  {entry__9_4, NULL, 246, 246, 5, 9},
  {cont__9_5, &frame__9_4, 247, 247, 5, 10},
  {cont__9_6, &frame__9_4, 248, 248, 15, 17},
  {cont__9_7, &frame__9_4, 248, 248, 5, 30},
  {entry__9_1, NULL, 245, 245, 6, 11},
  {cont__9_2, &frame__9_1, 245, 245, 6, 11},
  {cont__9_3, &frame__9_1, 245, 248, 3, 30},
  {entry__10_6, NULL, 304, 304, 25, 34},
  {entry__10_3, NULL, 304, 304, 10, 22},
  {cont__10_4, &frame__10_3, 304, 304, 10, 22},
  {cont__10_5, &frame__10_3, 304, 304, 7, 34},
  {cont__10_7, &frame__10_3, 305, 305, 25, 34},
  {cont__10_8, &frame__10_3, 305, 305, 7, 55},
  {entry__10_9, NULL, 307, 307, 7, 44},
  {entry__10_1, NULL, 303, 303, 5, 20},
  {cont__10_2, &frame__10_1, 302, 307, 3, 45},
  {entry__11_4, NULL, 311, 311, 5, 10},
  {cont__11_5, &frame__11_4, 312, 312, 23, 28},
  {cont__11_6, &frame__11_4, 312, 312, 5, 40},
  {entry__11_1, NULL, 310, 310, 6, 11},
  {cont__11_2, &frame__11_1, 310, 310, 6, 11},
  {cont__11_3, &frame__11_1, 310, 312, 3, 40},
  {entry__12_4, NULL, 316, 316, 5, 9},
  {cont__12_5, &frame__12_4, 317, 317, 5, 10},
  {cont__12_6, &frame__12_4, 318, 318, 23, 28},
  {cont__12_7, &frame__12_4, 318, 318, 5, 46},
  {entry__12_1, NULL, 315, 315, 6, 11},
  {cont__12_2, &frame__12_1, 315, 315, 6, 11},
  {cont__12_3, &frame__12_1, 315, 318, 3, 46},
  {entry__13_4, NULL, 348, 348, 5, 8},
  {cont__13_5, &frame__13_4, 349, 349, 12, 14},
  {cont__13_6, &frame__13_4, 349, 349, 5, 19},
  {entry__13_1, NULL, 347, 347, 6, 11},
  {cont__13_2, &frame__13_1, 347, 347, 6, 11},
  {cont__13_3, &frame__13_1, 347, 349, 3, 19},
  {entry__14_1, NULL, 389, 389, 3, 6},
  {cont__14_2, &frame__14_1, 390, 390, 3, 14},
  {entry__15_3, NULL, 442, 442, 5, 8},
  {cont__15_4, &frame__15_3, 443, 443, 5, 23},
  {entry__15_1, NULL, 440, 440, 3, 27},
  {cont__15_2, &frame__15_1, 441, 443, 3, 23},
  {entry__16_3, NULL, 458, 458, 14, 26},
  {entry__16_1, NULL, 458, 458, 6, 11},
  {cont__16_2, &frame__16_1, 458, 458, 3, 26},
  {entry__17_3, NULL, 473, 473, 18, 30},
  {entry__17_1, NULL, 473, 473, 10, 15},
  {cont__17_2, &frame__17_1, 473, 473, 3, 30}
};

union NODE {
  struct {
    FUNC type;
    ATTRIBUTES *attributes;
  };
  CONTINUATION continuation;
  CLOSURE closure;
};
static NODE *number__1;

static const char *used_namespaces[] = {
  "std",
  NULL
};

static MODULE_INFO module_info = {
  NULL,
  "basic__loops",
  continuation_info,
  sizeof(continuation_info)/sizeof(CONTINUATION_INFO),
  (NODE **)&var,
  var_names,
  sizeof(var_names)/sizeof(const char *),
  used_namespaces,
  {DEBUG_FILENAME("basic/loops.sim")}
};

/******
C O D E
******/

static int already_run = false;

EXPORT void run__basic__loops(void) {
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
static void entry__1_3(void) {
  allocate_initialized_frame_gc(4, 7);
  // slot allocations:
  // last: 0
  // first: 1
  // body: 2
  // body2: 3
  frame->slots[0] = myself->closure.frame->slots[1]; /* last */
  frame->slots[1] = myself->closure.frame->slots[0]; /* first */
  frame->slots[2] = myself->closure.frame->slots[2]; /* body */
  frame->slots[3] = myself->closure.frame->slots[3]; /* body2 */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 87: ... first <= last
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* last */;
  arguments->slots[1] = frame->slots[1] /* first */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__1_4;
}
static void cont__1_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 87: ... first <= last
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__1_5;
}
static void cont__1_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 87: ... : body first
  frame->slots[6] /* temp__3 */ = create_closure(entry__1_6, 0);
  // 87: if first <= last: body first
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__1_7;
}
static void entry__1_6(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // body: 0
  // first: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* body */
  frame->slots[1] = myself->closure.frame->slots[1]; /* first */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 87: ... body first
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* first */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__1_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 88: ... first+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* first */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__1_8;
}
static void cont__1_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 88: from_to_2 first+1 last body body2
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[0] /* last */;
  arguments->slots[2] = frame->slots[2] /* body */;
  arguments->slots[3] = frame->slots[3] /* body2 */;
  result_count = frame->caller_result_count;
  myself = var._from_to_2;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__1_9(void) {
  allocate_initialized_frame_gc(3, 3);
  // slot allocations:
  // first: 0
  // last: 1
  // body: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* first */
  frame->slots[1] = myself->closure.frame->slots[1]; /* last */
  frame->slots[2] = myself->closure.frame->slots[2]; /* body */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 90: from_to_1 first last body
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* first */;
  arguments->slots[1] = frame->slots[1] /* last */;
  arguments->slots[2] = frame->slots[2] /* body */;
  result_count = frame->caller_result_count;
  myself = var._from_to_1;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__1_1(void) {
  allocate_initialized_frame_gc(4, 7);
  // slot allocations:
  // first: 0
  // last: 1
  // body: 2
  // body2: 3
  if (argument_count < 3) {
    too_few_arguments_error();
    return;
  }
  if (argument_count > 4) {
    too_many_arguments_error();
    return;
  }
  switch(argument_count) {
    default: frame->slots[3] /* body2 */ = arguments->slots[3];
    case 3:;
  }
  switch(argument_count) {
    case 3: frame->slots[3] /* body2 */ = undefined;
  }
  // 86: body2.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* body2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__1_2;
}
static void cont__1_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 86: ... :
  // 87:   if first <= last: body first
  // 88:   from_to_2 first+1 last body body2
  frame->slots[5] /* temp__2 */ = create_closure(entry__1_3, 0);
  // 89: :
  // 90:   from_to_1 first last body
  frame->slots[6] /* temp__3 */ = create_closure(entry__1_9, 0);
  // 85: if
  // 86:   body2.is_defined:
  // 87:     if first <= last: body first
  // 88:     from_to_2 first+1 last body body2
  // 89:   :
  // 90:     from_to_1 first last body
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
static void entry__2_4(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // body: 0
  // s: 1
  // e: 2
  frame->slots[0] = myself->closure.frame->slots[2]; /* body */
  frame->slots[1] = myself->closure.frame->slots[0]; /* s */
  frame->slots[2] = myself->closure.frame->slots[1]; /* e */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 94: body s
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* s */;
  result_count = 0;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame->cont = cont__2_5;
}
static void cont__2_5(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 95: ... s+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* s */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__2_6;
}
static void cont__2_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 95: from_to_1 s+1 e body
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* e */;
  arguments->slots[2] = frame->slots[0] /* body */;
  result_count = frame->caller_result_count;
  myself = var._from_to_1;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__2_1(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // s: 0
  // e: 1
  // body: 2
  if (argument_count != 3) {
    invalid_arguments_error();
    return;
  }
  // 93: ... s <= e
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* e */;
  arguments->slots[1] = frame->slots[0] /* s */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__2_2;
}
static void cont__2_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 93: ... s <= e
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__2_3;
}
static void cont__2_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 93: ... :
  // 94:   body s
  // 95:   from_to_1 s+1 e body
  frame->slots[5] /* temp__3 */ = create_closure(entry__2_4, 0);
  // 93: if s <= e:
  // 94:   body s
  // 95:   from_to_1 s+1 e body
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__3_4(void) {
  allocate_initialized_frame_gc(4, 5);
  // slot allocations:
  // body2: 0
  // body: 1
  // s: 2
  // e: 3
  frame->slots[0] = myself->closure.frame->slots[3]; /* body2 */
  frame->slots[1] = myself->closure.frame->slots[2]; /* body */
  frame->slots[2] = myself->closure.frame->slots[0]; /* s */
  frame->slots[3] = myself->closure.frame->slots[1]; /* e */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 99: body2
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = frame->slots[0] /* body2 */;
  func = myself->type;
  frame->cont = cont__3_5;
}
static void cont__3_5(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 100: body s
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* s */;
  result_count = 0;
  myself = frame->slots[1] /* body */;
  func = myself->type;
  frame->cont = cont__3_6;
}
static void cont__3_6(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 101: ... s+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* s */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__3_7;
}
static void cont__3_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 101: from_to_2 s+1 e body body2
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* e */;
  arguments->slots[2] = frame->slots[1] /* body */;
  arguments->slots[3] = frame->slots[0] /* body2 */;
  result_count = frame->caller_result_count;
  myself = var._from_to_2;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__3_1(void) {
  allocate_initialized_frame_gc(4, 7);
  // slot allocations:
  // s: 0
  // e: 1
  // body: 2
  // body2: 3
  if (argument_count != 4) {
    invalid_arguments_error();
    return;
  }
  // 98: ... s <= e
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* e */;
  arguments->slots[1] = frame->slots[0] /* s */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__3_2;
}
static void cont__3_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 98: ... s <= e
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__3_3;
}
static void cont__3_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  //  98: ... :
  //  99:   body2
  // 100:   body s
  // 101:   from_to_2 s+1 e body body2
  frame->slots[6] /* temp__3 */ = create_closure(entry__3_4, 0);
  //  98: if s <= e:
  //  99:   body2
  // 100:   body s
  // 101:   from_to_2 s+1 e body body2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__4_3(void) {
  allocate_initialized_frame_gc(5, 8);
  // slot allocations:
  // last: 0
  // first: 1
  // body: 2
  // step: 3
  // body2: 4
  frame->slots[0] = myself->closure.frame->slots[1]; /* last */
  frame->slots[1] = myself->closure.frame->slots[0]; /* first */
  frame->slots[2] = myself->closure.frame->slots[3]; /* body */
  frame->slots[3] = myself->closure.frame->slots[2]; /* step */
  frame->slots[4] = myself->closure.frame->slots[4]; /* body2 */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 163: ... first <= last
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* last */;
  arguments->slots[1] = frame->slots[1] /* first */;
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
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 163: ... first <= last
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__4_5;
}
static void cont__4_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 163: ... : body first
  frame->slots[7] /* temp__3 */ = create_closure(entry__4_6, 0);
  // 163: if first <= last: body first
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__4_7;
}
static void entry__4_6(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // body: 0
  // first: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* body */
  frame->slots[1] = myself->closure.frame->slots[1]; /* first */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 163: ... body first
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* first */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__4_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 164: ... first+step
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* first */;
  arguments->slots[1] = frame->slots[3] /* step */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__4_8;
}
static void cont__4_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 164: from_to_by_2 first+step last step body body2
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[0] /* last */;
  arguments->slots[2] = frame->slots[3] /* step */;
  arguments->slots[3] = frame->slots[2] /* body */;
  arguments->slots[4] = frame->slots[4] /* body2 */;
  result_count = frame->caller_result_count;
  myself = var._from_to_by_2;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__4_9(void) {
  allocate_initialized_frame_gc(4, 4);
  // slot allocations:
  // first: 0
  // last: 1
  // step: 2
  // body: 3
  frame->slots[0] = myself->closure.frame->slots[0]; /* first */
  frame->slots[1] = myself->closure.frame->slots[1]; /* last */
  frame->slots[2] = myself->closure.frame->slots[2]; /* step */
  frame->slots[3] = myself->closure.frame->slots[3]; /* body */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 166: from_to_by_1 first last step body
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* first */;
  arguments->slots[1] = frame->slots[1] /* last */;
  arguments->slots[2] = frame->slots[2] /* step */;
  arguments->slots[3] = frame->slots[3] /* body */;
  result_count = frame->caller_result_count;
  myself = var._from_to_by_1;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__4_1(void) {
  allocate_initialized_frame_gc(5, 8);
  // slot allocations:
  // first: 0
  // last: 1
  // step: 2
  // body: 3
  // body2: 4
  if (argument_count < 4) {
    too_few_arguments_error();
    return;
  }
  if (argument_count > 5) {
    too_many_arguments_error();
    return;
  }
  switch(argument_count) {
    default: frame->slots[4] /* body2 */ = arguments->slots[4];
    case 4:;
  }
  switch(argument_count) {
    case 4: frame->slots[4] /* body2 */ = undefined;
  }
  // 162: body2.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* body2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__4_2;
}
static void cont__4_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 162: ... :
  // 163:   if first <= last: body first
  // 164:   from_to_by_2 first+step last step body body2
  frame->slots[6] /* temp__2 */ = create_closure(entry__4_3, 0);
  // 165: :
  // 166:   from_to_by_1 first last step body
  frame->slots[7] /* temp__3 */ = create_closure(entry__4_9, 0);
  // 161: if
  // 162:   body2.is_defined:
  // 163:     if first <= last: body first
  // 164:     from_to_by_2 first+step last step body body2
  // 165:   :
  // 166:     from_to_by_1 first last step body
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
static void entry__5_4(void) {
  allocate_initialized_frame_gc(4, 5);
  // slot allocations:
  // body: 0
  // s: 1
  // step: 2
  // e: 3
  frame->slots[0] = myself->closure.frame->slots[3]; /* body */
  frame->slots[1] = myself->closure.frame->slots[0]; /* s */
  frame->slots[2] = myself->closure.frame->slots[2]; /* step */
  frame->slots[3] = myself->closure.frame->slots[1]; /* e */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 170: body s
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* s */;
  result_count = 0;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame->cont = cont__5_5;
}
static void cont__5_5(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 171: ... s+step
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* s */;
  arguments->slots[1] = frame->slots[2] /* step */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__5_6;
}
static void cont__5_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 171: from_to_by_1 s+step e step body
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* e */;
  arguments->slots[2] = frame->slots[2] /* step */;
  arguments->slots[3] = frame->slots[0] /* body */;
  result_count = frame->caller_result_count;
  myself = var._from_to_by_1;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__5_1(void) {
  allocate_initialized_frame_gc(4, 7);
  // slot allocations:
  // s: 0
  // e: 1
  // step: 2
  // body: 3
  if (argument_count != 4) {
    invalid_arguments_error();
    return;
  }
  // 169: ... s <= e
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* e */;
  arguments->slots[1] = frame->slots[0] /* s */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__5_2;
}
static void cont__5_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 169: ... s <= e
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__5_3;
}
static void cont__5_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 169: ... :
  // 170:   body s
  // 171:   from_to_by_1 s+step e step body
  frame->slots[6] /* temp__3 */ = create_closure(entry__5_4, 0);
  // 169: if s <= e:
  // 170:   body s
  // 171:   from_to_by_1 s+step e step body
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__6_4(void) {
  allocate_initialized_frame_gc(5, 6);
  // slot allocations:
  // body2: 0
  // body: 1
  // s: 2
  // step: 3
  // e: 4
  frame->slots[0] = myself->closure.frame->slots[4]; /* body2 */
  frame->slots[1] = myself->closure.frame->slots[3]; /* body */
  frame->slots[2] = myself->closure.frame->slots[0]; /* s */
  frame->slots[3] = myself->closure.frame->slots[2]; /* step */
  frame->slots[4] = myself->closure.frame->slots[1]; /* e */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 175: body2
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = frame->slots[0] /* body2 */;
  func = myself->type;
  frame->cont = cont__6_5;
}
static void cont__6_5(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 176: body s
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* s */;
  result_count = 0;
  myself = frame->slots[1] /* body */;
  func = myself->type;
  frame->cont = cont__6_6;
}
static void cont__6_6(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 177: ... s+step
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* s */;
  arguments->slots[1] = frame->slots[3] /* step */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__6_7;
}
static void cont__6_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 177: from_to_by_2 s+step e step body body2
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* e */;
  arguments->slots[2] = frame->slots[3] /* step */;
  arguments->slots[3] = frame->slots[1] /* body */;
  arguments->slots[4] = frame->slots[0] /* body2 */;
  result_count = frame->caller_result_count;
  myself = var._from_to_by_2;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__6_1(void) {
  allocate_initialized_frame_gc(5, 8);
  // slot allocations:
  // s: 0
  // e: 1
  // step: 2
  // body: 3
  // body2: 4
  if (argument_count != 5) {
    invalid_arguments_error();
    return;
  }
  // 174: ... s <= e
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* e */;
  arguments->slots[1] = frame->slots[0] /* s */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__6_2;
}
static void cont__6_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 174: ... s <= e
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__6_3;
}
static void cont__6_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 174: ... :
  // 175:   body2
  // 176:   body s
  // 177:   from_to_by_2 s+step e step body body2
  frame->slots[7] /* temp__3 */ = create_closure(entry__6_4, 0);
  // 174: if s <= e:
  // 175:   body2
  // 176:   body s
  // 177:   from_to_by_2 s+step e step body body2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_3(void) {
  allocate_initialized_frame_gc(4, 7);
  // slot allocations:
  // first: 0
  // last: 1
  // body: 2
  // body2: 3
  frame->slots[0] = myself->closure.frame->slots[0]; /* first */
  frame->slots[1] = myself->closure.frame->slots[1]; /* last */
  frame->slots[2] = myself->closure.frame->slots[2]; /* body */
  frame->slots[3] = myself->closure.frame->slots[3]; /* body2 */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 234: ... first >= last
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* first */;
  arguments->slots[1] = frame->slots[1] /* last */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__7_4;
}
static void cont__7_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 234: ... first >= last
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__7_5;
}
static void cont__7_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 234: ... : body first
  frame->slots[6] /* temp__3 */ = create_closure(entry__7_6, 0);
  // 234: if first >= last: body first
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__7_7;
}
static void entry__7_6(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // body: 0
  // first: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* body */
  frame->slots[1] = myself->closure.frame->slots[0]; /* first */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 234: ... body first
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* first */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 235: ... first+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* first */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__7_8;
}
static void cont__7_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 235: from_down_to_2 first+1 last body body2
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* last */;
  arguments->slots[2] = frame->slots[2] /* body */;
  arguments->slots[3] = frame->slots[3] /* body2 */;
  result_count = frame->caller_result_count;
  myself = var._from_down_to_2;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_9(void) {
  allocate_initialized_frame_gc(3, 3);
  // slot allocations:
  // first: 0
  // last: 1
  // body: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* first */
  frame->slots[1] = myself->closure.frame->slots[1]; /* last */
  frame->slots[2] = myself->closure.frame->slots[2]; /* body */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 237: from_down_to_1 first last body
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* first */;
  arguments->slots[1] = frame->slots[1] /* last */;
  arguments->slots[2] = frame->slots[2] /* body */;
  result_count = frame->caller_result_count;
  myself = var._from_down_to_1;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_1(void) {
  allocate_initialized_frame_gc(4, 7);
  // slot allocations:
  // first: 0
  // last: 1
  // body: 2
  // body2: 3
  if (argument_count < 3) {
    too_few_arguments_error();
    return;
  }
  if (argument_count > 4) {
    too_many_arguments_error();
    return;
  }
  switch(argument_count) {
    default: frame->slots[3] /* body2 */ = arguments->slots[3];
    case 3:;
  }
  switch(argument_count) {
    case 3: frame->slots[3] /* body2 */ = undefined;
  }
  // 233: body2.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* body2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__7_2;
}
static void cont__7_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 233: ... :
  // 234:   if first >= last: body first
  // 235:   from_down_to_2 first+1 last body body2
  frame->slots[5] /* temp__2 */ = create_closure(entry__7_3, 0);
  // 236: :
  // 237:   from_down_to_1 first last body
  frame->slots[6] /* temp__3 */ = create_closure(entry__7_9, 0);
  // 232: if
  // 233:   body2.is_defined:
  // 234:     if first >= last: body first
  // 235:     from_down_to_2 first+1 last body body2
  // 236:   :
  // 237:     from_down_to_1 first last body
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
static void entry__8_4(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // body: 0
  // s: 1
  // e: 2
  frame->slots[0] = myself->closure.frame->slots[2]; /* body */
  frame->slots[1] = myself->closure.frame->slots[0]; /* s */
  frame->slots[2] = myself->closure.frame->slots[1]; /* e */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 241: body s
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* s */;
  result_count = 0;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame->cont = cont__8_5;
}
static void cont__8_5(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 242: ... s-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* s */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__8_6;
}
static void cont__8_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 242: from_down_to_1 s-1 e body
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* e */;
  arguments->slots[2] = frame->slots[0] /* body */;
  result_count = frame->caller_result_count;
  myself = var._from_down_to_1;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__8_1(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // s: 0
  // e: 1
  // body: 2
  if (argument_count != 3) {
    invalid_arguments_error();
    return;
  }
  // 240: ... s >= e
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* s */;
  arguments->slots[1] = frame->slots[1] /* e */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__8_2;
}
static void cont__8_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 240: ... s >= e
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__8_3;
}
static void cont__8_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 240: ... :
  // 241:   body s
  // 242:   from_down_to_1 s-1 e body
  frame->slots[5] /* temp__3 */ = create_closure(entry__8_4, 0);
  // 240: if s >= e:
  // 241:   body s
  // 242:   from_down_to_1 s-1 e body
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__9_4(void) {
  allocate_initialized_frame_gc(4, 5);
  // slot allocations:
  // body2: 0
  // body: 1
  // s: 2
  // e: 3
  frame->slots[0] = myself->closure.frame->slots[3]; /* body2 */
  frame->slots[1] = myself->closure.frame->slots[2]; /* body */
  frame->slots[2] = myself->closure.frame->slots[0]; /* s */
  frame->slots[3] = myself->closure.frame->slots[1]; /* e */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 246: body2
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = frame->slots[0] /* body2 */;
  func = myself->type;
  frame->cont = cont__9_5;
}
static void cont__9_5(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 247: body s
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* s */;
  result_count = 0;
  myself = frame->slots[1] /* body */;
  func = myself->type;
  frame->cont = cont__9_6;
}
static void cont__9_6(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 248: ... s-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* s */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__9_7;
}
static void cont__9_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 248: from_to_2 s-1 e body body2
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* e */;
  arguments->slots[2] = frame->slots[1] /* body */;
  arguments->slots[3] = frame->slots[0] /* body2 */;
  result_count = frame->caller_result_count;
  myself = var._from_to_2;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__9_1(void) {
  allocate_initialized_frame_gc(4, 7);
  // slot allocations:
  // s: 0
  // e: 1
  // body: 2
  // body2: 3
  if (argument_count != 4) {
    invalid_arguments_error();
    return;
  }
  // 245: ... s >= e
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* s */;
  arguments->slots[1] = frame->slots[1] /* e */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__9_2;
}
static void cont__9_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 245: ... s >= e
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__9_3;
}
static void cont__9_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 245: ... :
  // 246:   body2
  // 247:   body s
  // 248:   from_to_2 s-1 e body body2
  frame->slots[6] /* temp__3 */ = create_closure(entry__9_4, 0);
  // 245: if s >= e:
  // 246:   body2
  // 247:   body s
  // 248:   from_to_2 s-1 e body body2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__10_3(void) {
  allocate_initialized_frame_gc(5, 8);
  // slot allocations:
  // first: 0
  // last: 1
  // body: 2
  // step: 3
  // body2: 4
  frame->slots[0] = myself->closure.frame->slots[0]; /* first */
  frame->slots[1] = myself->closure.frame->slots[1]; /* last */
  frame->slots[2] = myself->closure.frame->slots[3]; /* body */
  frame->slots[3] = myself->closure.frame->slots[2]; /* step */
  frame->slots[4] = myself->closure.frame->slots[4]; /* body2 */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 304: ... first >= last
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* first */;
  arguments->slots[1] = frame->slots[1] /* last */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__10_4;
}
static void cont__10_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 304: ... first >= last
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__10_5;
}
static void cont__10_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 304: ... : body first
  frame->slots[7] /* temp__3 */ = create_closure(entry__10_6, 0);
  // 304: if first >= last: body first
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__10_7;
}
static void entry__10_6(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // body: 0
  // first: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* body */
  frame->slots[1] = myself->closure.frame->slots[0]; /* first */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 304: ... body first
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* first */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__10_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 305: ... first+step
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* first */;
  arguments->slots[1] = frame->slots[3] /* step */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__10_8;
}
static void cont__10_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 305: from_down_to_by_2 first+step last step body body2
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* last */;
  arguments->slots[2] = frame->slots[3] /* step */;
  arguments->slots[3] = frame->slots[2] /* body */;
  arguments->slots[4] = frame->slots[4] /* body2 */;
  result_count = frame->caller_result_count;
  myself = var._from_down_to_by_2;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__10_9(void) {
  allocate_initialized_frame_gc(4, 4);
  // slot allocations:
  // first: 0
  // last: 1
  // step: 2
  // body: 3
  frame->slots[0] = myself->closure.frame->slots[0]; /* first */
  frame->slots[1] = myself->closure.frame->slots[1]; /* last */
  frame->slots[2] = myself->closure.frame->slots[2]; /* step */
  frame->slots[3] = myself->closure.frame->slots[3]; /* body */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 307: from_down_to_by_1 first last step body
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* first */;
  arguments->slots[1] = frame->slots[1] /* last */;
  arguments->slots[2] = frame->slots[2] /* step */;
  arguments->slots[3] = frame->slots[3] /* body */;
  result_count = frame->caller_result_count;
  myself = var._from_down_to_by_1;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__10_1(void) {
  allocate_initialized_frame_gc(5, 8);
  // slot allocations:
  // first: 0
  // last: 1
  // step: 2
  // body: 3
  // body2: 4
  if (argument_count < 4) {
    too_few_arguments_error();
    return;
  }
  if (argument_count > 5) {
    too_many_arguments_error();
    return;
  }
  switch(argument_count) {
    default: frame->slots[4] /* body2 */ = arguments->slots[4];
    case 4:;
  }
  switch(argument_count) {
    case 4: frame->slots[4] /* body2 */ = undefined;
  }
  // 303: body2.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* body2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__10_2;
}
static void cont__10_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 303: ... :
  // 304:   if first >= last: body first
  // 305:   from_down_to_by_2 first+step last step body body2
  frame->slots[6] /* temp__2 */ = create_closure(entry__10_3, 0);
  // 306: :
  // 307:   from_down_to_by_1 first last step body
  frame->slots[7] /* temp__3 */ = create_closure(entry__10_9, 0);
  // 302: if
  // 303:   body2.is_defined:
  // 304:     if first >= last: body first
  // 305:     from_down_to_by_2 first+step last step body body2
  // 306:   :
  // 307:     from_down_to_by_1 first last step body
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
static void entry__11_4(void) {
  allocate_initialized_frame_gc(4, 5);
  // slot allocations:
  // body: 0
  // s: 1
  // step: 2
  // e: 3
  frame->slots[0] = myself->closure.frame->slots[3]; /* body */
  frame->slots[1] = myself->closure.frame->slots[0]; /* s */
  frame->slots[2] = myself->closure.frame->slots[2]; /* step */
  frame->slots[3] = myself->closure.frame->slots[1]; /* e */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 311: body s
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* s */;
  result_count = 0;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame->cont = cont__11_5;
}
static void cont__11_5(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 312: ... s-step
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* s */;
  arguments->slots[1] = frame->slots[2] /* step */;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__11_6;
}
static void cont__11_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 312: from_down_to_by_1 s-step e step body
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* e */;
  arguments->slots[2] = frame->slots[2] /* step */;
  arguments->slots[3] = frame->slots[0] /* body */;
  result_count = frame->caller_result_count;
  myself = var._from_down_to_by_1;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__11_1(void) {
  allocate_initialized_frame_gc(4, 7);
  // slot allocations:
  // s: 0
  // e: 1
  // step: 2
  // body: 3
  if (argument_count != 4) {
    invalid_arguments_error();
    return;
  }
  // 310: ... s >= e
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* s */;
  arguments->slots[1] = frame->slots[1] /* e */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__11_2;
}
static void cont__11_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 310: ... s >= e
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__11_3;
}
static void cont__11_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 310: ... :
  // 311:   body s
  // 312:   from_down_to_by_1 s-step e step body
  frame->slots[6] /* temp__3 */ = create_closure(entry__11_4, 0);
  // 310: if s >= e:
  // 311:   body s
  // 312:   from_down_to_by_1 s-step e step body
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__12_4(void) {
  allocate_initialized_frame_gc(5, 6);
  // slot allocations:
  // body2: 0
  // body: 1
  // s: 2
  // step: 3
  // e: 4
  frame->slots[0] = myself->closure.frame->slots[4]; /* body2 */
  frame->slots[1] = myself->closure.frame->slots[3]; /* body */
  frame->slots[2] = myself->closure.frame->slots[0]; /* s */
  frame->slots[3] = myself->closure.frame->slots[2]; /* step */
  frame->slots[4] = myself->closure.frame->slots[1]; /* e */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 316: body2
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = frame->slots[0] /* body2 */;
  func = myself->type;
  frame->cont = cont__12_5;
}
static void cont__12_5(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 317: body s
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* s */;
  result_count = 0;
  myself = frame->slots[1] /* body */;
  func = myself->type;
  frame->cont = cont__12_6;
}
static void cont__12_6(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 318: ... s-step
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* s */;
  arguments->slots[1] = frame->slots[3] /* step */;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__12_7;
}
static void cont__12_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 318: from_down_to_by_2 s-step e step body body2
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* e */;
  arguments->slots[2] = frame->slots[3] /* step */;
  arguments->slots[3] = frame->slots[1] /* body */;
  arguments->slots[4] = frame->slots[0] /* body2 */;
  result_count = frame->caller_result_count;
  myself = var._from_down_to_by_2;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__12_1(void) {
  allocate_initialized_frame_gc(5, 8);
  // slot allocations:
  // s: 0
  // e: 1
  // step: 2
  // body: 3
  // body2: 4
  if (argument_count != 5) {
    invalid_arguments_error();
    return;
  }
  // 315: ... s >= e
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* s */;
  arguments->slots[1] = frame->slots[1] /* e */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__12_2;
}
static void cont__12_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 315: ... s >= e
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__12_3;
}
static void cont__12_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 315: ... :
  // 316:   body2
  // 317:   body s
  // 318:   from_down_to_by_2 s-step e step body body2
  frame->slots[7] /* temp__3 */ = create_closure(entry__12_4, 0);
  // 315: if s >= e:
  // 316:   body2
  // 317:   body s
  // 318:   from_down_to_by_2 s-step e step body body2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__13_4(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // body: 0
  // n: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* body */
  frame->slots[1] = myself->closure.frame->slots[0]; /* n */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 348: body
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame->cont = cont__13_5;
}
static void cont__13_5(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 349: ... n-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* n */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__13_6;
}
static void cont__13_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 349: repeat n-1 body
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[0] /* body */;
  result_count = frame->caller_result_count;
  myself = get__repeat();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__13_1(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // n: 0
  // body: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 347: ... n >= 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* n */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__13_2;
}
static void cont__13_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 347: ... n >= 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__13_3;
}
static void cont__13_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 347: ... :
  // 348:   body
  // 349:   repeat n-1 body
  frame->slots[4] /* temp__3 */ = create_closure(entry__13_4, 0);
  // 347: if n >= 1:
  // 348:   body
  // 349:   repeat n-1 body
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__14_1(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // body: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 389: body
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame->cont = cont__14_2;
}
static void cont__14_2(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 390: forever body
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* body */;
  result_count = frame->caller_result_count;
  myself = get__forever();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__15_3(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // body: 0
  // cond_and_body: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* body */
  frame->slots[1] = myself->closure.frame->slots[0]; /* cond_and_body */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 442: body
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame->cont = cont__15_4;
}
static void cont__15_4(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 443: while cond_and_body
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* cond_and_body */;
  result_count = frame->caller_result_count;
  myself = get__while();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__15_1(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // cond_and_body: 0
  // cond: 1
  // body: 2
  frame->slots[1] /* cond */ = create_future();
  frame->slots[2] /* body */ = create_future();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 440: cond_and_body $cond $body
  argument_count = 0;
  arguments = node_p;
  result_count = 2;
  myself = frame->slots[0] /* cond_and_body */;
  func = myself->type;
  frame->cont = cont__15_2;
}
static void cont__15_2(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  frame->slots[4] /* temp__2 */ = arguments->slots[1];
  // 440: ... cond
  initialize_future(frame->slots[1] /* cond */, frame->slots[3] /* temp__1 */);
  // 440: ... body
  initialize_future(frame->slots[2] /* body */, frame->slots[4] /* temp__2 */);
  // 441: ... :
  // 442:   body
  // 443:   while cond_and_body
  frame->slots[3] /* temp__1 */ = create_closure(entry__15_3, 0);
  // 441: if cond:
  // 442:   body
  // 443:   while cond_and_body
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* cond */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__16_3(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // body: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* body */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 458: ... do_while body
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* body */;
  result_count = frame->caller_result_count;
  myself = get__do_while();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__16_1(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // body: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 458: ... body()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame->cont = cont__16_2;
}
static void cont__16_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 458: ... : do_while body
  frame->slots[2] /* temp__2 */ = create_closure(entry__16_3, 0);
  // 458: if body(): do_while body
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__17_3(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // body: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* body */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 473: ... do_until body
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* body */;
  result_count = frame->caller_result_count;
  myself = get__do_until();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__17_1(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // body: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 473: ... body()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame->cont = cont__17_2;
}
static void cont__17_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 473: ... : do_until body
  frame->slots[2] /* temp__2 */ = create_closure(entry__17_3, 0);
  // 473: unless body(): do_until body
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
EXPORT void collect__basic__loops(void) {
  var.std__from_to = collect_node(var.std__from_to);
  var._from_to_1 = collect_node(var._from_to_1);
  var._from_to_2 = collect_node(var._from_to_2);
  var.std__from_to_by = collect_node(var.std__from_to_by);
  var._from_to_by_1 = collect_node(var._from_to_by_1);
  var._from_to_by_2 = collect_node(var._from_to_by_2);
  var.std__from_down_to = collect_node(var.std__from_down_to);
  var._from_down_to_1 = collect_node(var._from_down_to_1);
  var._from_down_to_2 = collect_node(var._from_down_to_2);
  var.std__from_down_to_by = collect_node(var.std__from_down_to_by);
  var._from_down_to_by_1 = collect_node(var._from_down_to_by_1);
  var._from_down_to_by_2 = collect_node(var._from_down_to_by_2);
  var.std__repeat = collect_node(var.std__repeat);
  var.std__forever = collect_node(var.std__forever);
  var.std__while = collect_node(var.std__while);
  var.std__do_while = collect_node(var.std__do_while);
  var.std__do_until = collect_node(var.std__do_until);
}

static int already_run_phase_1 = false;

EXPORT void phase_1__basic__loops(void) {
  if (already_run_phase_1) return;
  already_run_phase_1 = true;
  register_module_info(&module_info);
}

static int already_run_phase_2 = false;

EXPORT void phase_2__basic__loops(void) {
  if (already_run_phase_2) return;
  already_run_phase_2 = true;
  number__1 = from_uint32(1U);
  func__1_1 = create_function(entry__1_1, -1);
  func__2_1 = create_function(entry__2_1, 3);
  func__3_1 = create_function(entry__3_1, 4);
  func__4_1 = create_function(entry__4_1, -1);
  func__5_1 = create_function(entry__5_1, 4);
  func__6_1 = create_function(entry__6_1, 5);
  func__7_1 = create_function(entry__7_1, -1);
  func__8_1 = create_function(entry__8_1, 3);
  func__9_1 = create_function(entry__9_1, 4);
  func__10_1 = create_function(entry__10_1, -1);
  func__11_1 = create_function(entry__11_1, 4);
  func__12_1 = create_function(entry__12_1, 5);
  func__13_1 = create_function(entry__13_1, 2);
  func__14_1 = create_function(entry__14_1, 1);
  func__15_1 = create_function(entry__15_1, 1);
  func__16_1 = create_function(entry__16_1, 1);
  func__17_1 = create_function(entry__17_1, 1);
}

static int already_run_phase_3 = false;

EXPORT void phase_3__basic__loops(void) {
  if (already_run_phase_3) return;
  already_run_phase_3 = true;
  set_module("basic__loops");
  set_used_namespaces(used_namespaces);
  define_single_assign_static("std", "from_to", get__std__from_to, &var.std__from_to);
  define_single_assign_static("std", "from_to_by", get__std__from_to_by, &var.std__from_to_by);
  define_single_assign_static("std", "from_down_to", get__std__from_down_to, &var.std__from_down_to);
  define_single_assign_static("std", "from_down_to_by", get__std__from_down_to_by, &var.std__from_down_to_by);
  define_single_assign_static("std", "repeat", get__std__repeat, &var.std__repeat);
  define_single_assign_static("std", "forever", get__std__forever, &var.std__forever);
  define_single_assign_static("std", "while", get__std__while, &var.std__while);
  define_single_assign_static("std", "do_while", get__std__do_while, &var.std__do_while);
  define_single_assign_static("std", "do_until", get__std__do_until, &var.std__do_until);
}

static int already_run_phase_4 = false;

EXPORT void phase_4__basic__loops(void) {
  if (already_run_phase_4) return;
  already_run_phase_4 = true;
  set_module("basic__loops");
  set_used_namespaces(used_namespaces);
  use_read_only(NULL, "do_until", &get__do_until, &get_value_or_future__do_until);
  use_read_only(NULL, "do_while", &get__do_while, &get_value_or_future__do_while);
  use_read_only(NULL, "forever", &get__forever, &get_value_or_future__forever);
  use_read_only(NULL, "if", &get__if, &get_value_or_future__if);
  use_read_only(NULL, "is_defined", &get__is_defined, &get_value_or_future__is_defined);
  use_read_only(NULL, "repeat", &get__repeat, &get_value_or_future__repeat);
  use_read_only("std", "less", &get__std__less, &get_value_or_future__std__less);
  use_read_only("std", "minus", &get__std__minus, &get_value_or_future__std__minus);
  use_read_only("std", "not", &get__std__not, &get_value_or_future__std__not);
  use_read_only("std", "plus", &get__std__plus, &get_value_or_future__std__plus);
  use_read_only(NULL, "unless", &get__unless, &get_value_or_future__unless);
  use_read_only(NULL, "while", &get__while, &get_value_or_future__while);
}

static int already_run_phase_5 = false;

EXPORT void phase_5__basic__loops(void) {
  if (already_run_phase_5) return;
  already_run_phase_5 = true;
  assign_variable(&var.std__from_to, &func__1_1);
  assign_variable(&var._from_to_1, &func__2_1);
  assign_variable(&var._from_to_2, &func__3_1);
  assign_variable(&var.std__from_to_by, &func__4_1);
  assign_variable(&var._from_to_by_1, &func__5_1);
  assign_variable(&var._from_to_by_2, &func__6_1);
  assign_variable(&var.std__from_down_to, &func__7_1);
  assign_variable(&var._from_down_to_1, &func__8_1);
  assign_variable(&var._from_down_to_2, &func__9_1);
  assign_variable(&var.std__from_down_to_by, &func__10_1);
  assign_variable(&var._from_down_to_by_1, &func__11_1);
  assign_variable(&var._from_down_to_by_2, &func__12_1);
  assign_variable(&var.std__repeat, &func__13_1);
  assign_variable(&var.std__forever, &func__14_1);
  assign_variable(&var.std__while, &func__15_1);
  assign_variable(&var.std__do_while, &func__16_1);
  assign_variable(&var.std__do_until, &func__17_1);
}

static int already_run_phase_6 = false;

EXPORT void phase_6__basic__loops(void) {
  if (already_run_phase_6) return;
  already_run_phase_6 = true;
  register_collector(collect__basic__loops);
}
