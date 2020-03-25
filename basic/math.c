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
IMPORT void invalid_arguments_error(void);
IMPORT NODE *create_cell_with_contents(NODE *contents);
REGISTER FRAME *arguments ASM("r12");
IMPORT void *node_p;
typedef struct CELL {
  FUNC type;
  struct ATTRIBUTES *attributes;
  NODE *contents;
} CELL;
IMPORT int result_count;
REGISTER NODE *myself ASM("r13");
IMPORT void invalid_results_error(void);
IMPORT NODE *create_closure(FUNC type, int par_count);
IMPORT void allocate_arguments(void);
IMPORT NODE *create_cell(void);
IMPORT NODE *from_arguments(int first_idx, int count);
IMPORT NODE *create_future(void);
IMPORT void initialize_future(NODE *var, NODE *val);
IMPORT NODE *collect_node(NODE *node);
IMPORT void register_module_info(MODULE_INFO *info);
IMPORT NODE *from_uint32(uint32_t val);
IMPORT NODE *from_double(double val);
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
IMPORT void assign_value(NODE **dest, NODE *val);
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
static NODE_GETTER get__PI;
static NODE_GETTER get_value_or_future__PI;
static NODE_GETTER get__cond;
static NODE_GETTER get_value_or_future__cond;
static NODE_GETTER get__cos;
static NODE_GETTER get_value_or_future__cos;
static NODE_GETTER get__for_each_from_to;
static NODE_GETTER get_value_or_future__for_each_from_to;
static NODE_GETTER get__from_to_by;
static NODE_GETTER get_value_or_future__from_to_by;
static NODE_GETTER get__if;
static NODE_GETTER get_value_or_future__if;
static NODE_GETTER get__inc;
static NODE_GETTER get_value_or_future__inc;
static NODE_GETTER get__is_odd;
static NODE_GETTER get_value_or_future__is_odd;
static NODE_GETTER get__minus;
static NODE_GETTER get_value_or_future__minus;
static NODE_GETTER get__negate;
static NODE_GETTER get_value_or_future__negate;
static NODE_GETTER get__plus;
static NODE_GETTER get_value_or_future__plus;
static NODE_GETTER get__pow;
static NODE_GETTER get_value_or_future__pow;
static NODE_GETTER get__repeat;
static NODE_GETTER get_value_or_future__repeat;
static NODE_GETTER get__sin;
static NODE_GETTER get_value_or_future__sin;
static NODE_GETTER get__sqr;
static NODE_GETTER get_value_or_future__sqr;
static NODE_GETTER get__sqrt;
static NODE_GETTER get_value_or_future__sqrt;
static NODE_GETTER get__std__equal;
static NODE_GETTER get_value_or_future__std__equal;
static NODE_GETTER get__std__less;
static NODE_GETTER get_value_or_future__std__less;
static NODE_GETTER get__std__minus;
static NODE_GETTER get_value_or_future__std__minus;
static NODE_GETTER get__std__negate;
static NODE_GETTER get_value_or_future__std__negate;
static NODE_GETTER get__std__over;
static NODE_GETTER get_value_or_future__std__over;
static NODE_GETTER get__std__plus;
static NODE_GETTER get_value_or_future__std__plus;
static NODE_GETTER get__std__shift_right;
static NODE_GETTER get_value_or_future__std__shift_right;
static NODE_GETTER get__std__times;
static NODE_GETTER get_value_or_future__std__times;
static NODE_GETTER get__true;
static NODE_GETTER get_value_or_future__true;
static struct {
  NODE *_atan2;
  NODE *_atan3;
  NODE *_atan4;
  NODE *std__inc;
  NODE *std__dec;
  NODE *std__extend_to;
  NODE *std__reduce_to;
  NODE *std__abs;
  NODE *std__sgn;
  NODE *std__sqr;
  NODE *std__min;
  NODE *std__max;
  NODE *std__pow;
  NODE *std__sqrt;
  NODE *std__PI;
  NODE *std__sin;
  NODE *std__cos;
  NODE *std__tan;
  NODE *std__atan;
} var;
static const char *var_names[] = {
  "atan2",
  "atan3",
  "atan4"
};
static NODE *func__1_1_std__inc;
static void entry__1_1_std__inc(void);
static FRAME_INFO frame__1_1_std__inc = {1, {"var"}};
static void cont__1_2(void);
static NODE *get__std__inc(void) {
  return var.std__inc;
}
static NODE *func__2_1_std__dec;
static void entry__2_1_std__dec(void);
static FRAME_INFO frame__2_1_std__dec = {1, {"var"}};
static void cont__2_2(void);
static NODE *get__std__dec(void) {
  return var.std__dec;
}
static NODE *func__3_1_std__extend_to;
static void entry__3_1_std__extend_to(void);
static FRAME_INFO frame__3_1_std__extend_to = {2, {"var", "val"}};
static void cont__3_2(void);
static NODE *func__3_3;
static void entry__3_3(void);
static FRAME_INFO frame__3_3 = {2, {"var", "val"}};
static void cont__3_4(void);
static NODE *get__std__extend_to(void) {
  return var.std__extend_to;
}
static NODE *func__4_1_std__reduce_to;
static void entry__4_1_std__reduce_to(void);
static FRAME_INFO frame__4_1_std__reduce_to = {2, {"var", "val"}};
static void cont__4_2(void);
static NODE *func__4_3;
static void entry__4_3(void);
static FRAME_INFO frame__4_3 = {2, {"var", "val"}};
static void cont__4_4(void);
static NODE *get__std__reduce_to(void) {
  return var.std__reduce_to;
}
static NODE *func__5_1_std__abs;
static void entry__5_1_std__abs(void);
static FRAME_INFO frame__5_1_std__abs = {1, {"var"}};
static void cont__5_2(void);
static NODE *func__5_3;
static void entry__5_3(void);
static FRAME_INFO frame__5_3 = {1, {"var"}};
static void cont__5_4(void);
static void cont__5_5(void);
static NODE *get__std__abs(void) {
  return var.std__abs;
}
static NODE *func__6_1_std__sgn;
static void entry__6_1_std__sgn(void);
static FRAME_INFO frame__6_1_std__sgn = {1, {"x"}};
static NODE *func__6_2;
static void entry__6_2(void);
static FRAME_INFO frame__6_2 = {1, {"x"}};
static void cont__6_3(void);
static NODE *func__6_4;
static void entry__6_4(void);
static FRAME_INFO frame__6_4 = {0, {}};
static NODE *func__6_5;
static void entry__6_5(void);
static FRAME_INFO frame__6_5 = {1, {"x"}};
static void cont__6_6(void);
static NODE *func__6_7;
static void entry__6_7(void);
static FRAME_INFO frame__6_7 = {0, {}};
static void cont__6_8(void);
static NODE *func__6_9;
static void entry__6_9(void);
static FRAME_INFO frame__6_9 = {0, {}};
static NODE *func__6_10;
static void entry__6_10(void);
static FRAME_INFO frame__6_10 = {0, {}};
static NODE *get__std__sgn(void) {
  return var.std__sgn;
}
static NODE *func__7_1_std__sqr;
static void entry__7_1_std__sqr(void);
static FRAME_INFO frame__7_1_std__sqr = {1, {"var"}};
static void cont__7_2(void);
static NODE *get__std__sqr(void) {
  return var.std__sqr;
}
static NODE *func__8_1_std__min;
static void entry__8_1_std__min(void);
static FRAME_INFO frame__8_1_std__min = {2, {"args", "result"}};
static void cont__8_2(void);
static void cont__8_3(void);
static NODE *func__8_4;
static void entry__8_4(void);
static FRAME_INFO frame__8_4 = {2, {"arg", "result"}};
static void cont__8_5(void);
static NODE *func__8_6;
static void entry__8_6(void);
static FRAME_INFO frame__8_6 = {2, {"result", "arg"}};
static void cont__8_7(void);
static NODE *get__std__min(void) {
  return var.std__min;
}
static NODE *func__9_1_std__max;
static void entry__9_1_std__max(void);
static FRAME_INFO frame__9_1_std__max = {2, {"args", "result"}};
static void cont__9_2(void);
static void cont__9_3(void);
static NODE *func__9_4;
static void entry__9_4(void);
static FRAME_INFO frame__9_4 = {2, {"arg", "result"}};
static void cont__9_5(void);
static NODE *func__9_6;
static void entry__9_6(void);
static FRAME_INFO frame__9_6 = {2, {"result", "arg"}};
static void cont__9_7(void);
static NODE *get__std__max(void) {
  return var.std__max;
}
static NODE *func__10_1_std__pow;
static void entry__10_1_std__pow(void);
static FRAME_INFO frame__10_1_std__pow = {2, {"x", "n"}};
static NODE *func__10_2;
static void entry__10_2(void);
static FRAME_INFO frame__10_2 = {1, {"n"}};
static void cont__10_3(void);
static NODE *func__10_4;
static void entry__10_4(void);
static FRAME_INFO frame__10_4 = {0, {}};
static NODE *func__10_5;
static void entry__10_5(void);
static FRAME_INFO frame__10_5 = {2, {"n", "x"}};
static void cont__10_6(void);
static NODE *func__10_7;
static void entry__10_7(void);
static FRAME_INFO frame__10_7 = {2, {"x", "n"}};
static void cont__10_8(void);
static void cont__10_9(void);
static void cont__10_10(void);
static void cont__10_11(void);
static NODE *func__10_12;
static void entry__10_12(void);
static FRAME_INFO frame__10_12 = {2, {"x", "n"}};
static NODE *func__10_13;
static void entry__10_13(void);
static FRAME_INFO frame__10_13 = {2, {"x", "n"}};
static void cont__10_14(void);
static void cont__10_15(void);
static void cont__10_16(void);
static NODE *get__std__pow(void) {
  return var.std__pow;
}
static NODE *func__11_1_std__sqrt;
static void entry__11_1_std__sqrt(void);
static FRAME_INFO frame__11_1_std__sqrt = {3, {"x", "low", "high"}};
static NODE *func__11_2;
static void entry__11_2(void);
static FRAME_INFO frame__11_2 = {4, {"high", "low", "x", "mid"}};
static void cont__11_3(void);
static void cont__11_4(void);
static void cont__11_5(void);
static void cont__11_6(void);
static NODE *func__11_7;
static void entry__11_7(void);
static FRAME_INFO frame__11_7 = {2, {"high", "mid"}};
static NODE *func__11_8;
static void entry__11_8(void);
static FRAME_INFO frame__11_8 = {2, {"low", "mid"}};
static void cont__11_9(void);
static NODE *get__std__sqrt(void) {
  return var.std__sqrt;
}
static NODE *get__std__PI(void) {
  return var.std__PI;
}
static NODE *func__13_1_std__sin;
static void entry__13_1_std__sin(void);
static FRAME_INFO frame__13_1_std__sin = {4, {"alpha", "p", "s", "t"}};
static NODE *func__13_2;
static void entry__13_2(void);
static FRAME_INFO frame__13_2 = {4, {"t", "alpha", "p", "s"}};
static void cont__13_3(void);
static void cont__13_4(void);
static void cont__13_5(void);
static void cont__13_6(void);
static void cont__13_7(void);
static void cont__13_8(void);
static void cont__13_9(void);
static void cont__13_10(void);
static void cont__13_11(void);
static void cont__13_12(void);
static void cont__13_13(void);
static NODE *get__std__sin(void) {
  return var.std__sin;
}
static NODE *func__14_1_std__cos;
static void entry__14_1_std__cos(void);
static FRAME_INFO frame__14_1_std__cos = {4, {"alpha", "p", "s", "t"}};
static NODE *func__14_2;
static void entry__14_2(void);
static FRAME_INFO frame__14_2 = {4, {"p", "t", "alpha", "s"}};
static void cont__14_3(void);
static void cont__14_4(void);
static void cont__14_5(void);
static void cont__14_6(void);
static void cont__14_7(void);
static void cont__14_8(void);
static void cont__14_9(void);
static void cont__14_10(void);
static void cont__14_11(void);
static void cont__14_12(void);
static void cont__14_13(void);
static NODE *get__std__cos(void) {
  return var.std__cos;
}
static NODE *func__15_1_std__tan;
static void entry__15_1_std__tan(void);
static FRAME_INFO frame__15_1_std__tan = {1, {"alpha"}};
static void cont__15_2(void);
static void cont__15_3(void);
static void cont__15_4(void);
static NODE *get__std__tan(void) {
  return var.std__tan;
}
static NODE *func__16_1_std__atan;
static void entry__16_1_std__atan(void);
static FRAME_INFO frame__16_1_std__atan = {1, {"x"}};
static void cont__16_2(void);
static NODE *func__16_3;
static void entry__16_3(void);
static FRAME_INFO frame__16_3 = {1, {"x"}};
static void cont__16_4(void);
static NODE *func__16_5;
static void entry__16_5(void);
static FRAME_INFO frame__16_5 = {1, {"x"}};
static void cont__16_6(void);
static void cont__16_7(void);
static void cont__16_8(void);
static NODE *get__std__atan(void) {
  return var.std__atan;
}
static NODE *func__17_1_atan2;
static void entry__17_1_atan2(void);
static FRAME_INFO frame__17_1_atan2 = {1, {"x"}};
static void cont__17_2(void);
static NODE *func__17_3;
static void entry__17_3(void);
static FRAME_INFO frame__17_3 = {1, {"x"}};
static void cont__17_4(void);
static void cont__17_5(void);
static void cont__17_6(void);
static void cont__17_7(void);
static NODE *func__17_8;
static void entry__17_8(void);
static FRAME_INFO frame__17_8 = {1, {"x"}};
static void cont__17_9(void);
static NODE *func__18_1_atan3;
static void entry__18_1_atan3(void);
static FRAME_INFO frame__18_1_atan3 = {1, {"x"}};
static void cont__18_2(void);
static void cont__18_3(void);
static void cont__18_4(void);
static NODE *func__18_5;
static void entry__18_5(void);
static FRAME_INFO frame__18_5 = {1, {"x"}};
static void cont__18_6(void);
static void cont__18_7(void);
static void cont__18_8(void);
static void cont__18_9(void);
static void cont__18_10(void);
static void cont__18_11(void);
static void cont__18_12(void);
static void cont__18_13(void);
static void cont__18_14(void);
static NODE *func__18_15;
static void entry__18_15(void);
static FRAME_INFO frame__18_15 = {1, {"x"}};
static void cont__18_16(void);
static NODE *func__19_1_atan4;
static void entry__19_1_atan4(void);
static FRAME_INFO frame__19_1_atan4 = {4, {"x", "sum", "s", "p"}};
static NODE *func__19_2;
static void entry__19_2(void);
static FRAME_INFO frame__19_2 = {5, {"i", "sum", "s", "p", "x"}};
static void cont__19_3(void);
static void cont__19_4(void);
static void cont__19_5(void);
static void cont__19_6(void);
static void cont__19_7(void);
static void cont__19_8(void);
static void cont__19_9(void);
void run__basic__math(void);

static CONTINUATION_INFO continuation_info[] = {
  {run__basic__math, NULL, },
  {entry__1_1_std__inc, NULL, 23, 23, 19, 29},
  {cont__1_2, &frame__1_1_std__inc, 23, 23, 29, 29},
  {entry__2_1_std__dec, NULL, 25, 25, 19, 30},
  {cont__2_2, &frame__2_1_std__dec, 25, 25, 30, 30},
  {entry__3_3, NULL, 32, 32, 24, 24},
  {entry__3_1_std__extend_to, NULL, 32, 32, 6, 14},
  {cont__3_2, &frame__3_1_std__extend_to, 32, 32, 3, 24},
  {cont__3_4, &frame__3_1_std__extend_to, },
  {entry__4_3, NULL, 39, 39, 24, 24},
  {entry__4_1_std__reduce_to, NULL, 39, 39, 6, 14},
  {cont__4_2, &frame__4_1_std__reduce_to, 39, 39, 3, 24},
  {cont__4_4, &frame__4_1_std__reduce_to, },
  {entry__5_3, NULL, 41, 41, 31, 41},
  {cont__5_4, &frame__5_3, 41, 41, 41, 41},
  {entry__5_1_std__abs, NULL, 41, 41, 22, 28},
  {cont__5_2, &frame__5_1_std__abs, 41, 41, 19, 41},
  {cont__5_5, &frame__5_1_std__abs, },
  {entry__6_4, NULL, 43, 43, 31, 34},
  {entry__6_2, NULL, 43, 43, 25, 29},
  {cont__6_3, &frame__6_2, 43, 43, 22, 34},
  {entry__6_7, NULL, 43, 43, 51, 51},
  {cont__6_8, &frame__6_7, 43, 43, 47, 51},
  {entry__6_5, NULL, 43, 43, 41, 45},
  {cont__6_6, &frame__6_5, 43, 43, 38, 51},
  {entry__6_10, NULL, 43, 43, 62, 65},
  {entry__6_9, NULL, 43, 43, 54, 65},
  {entry__6_1_std__sgn, NULL, 43, 43, 16, 65},
  {entry__7_1_std__sqr, NULL, 45, 45, 21, 27},
  {cont__7_2, &frame__7_1_std__sqr, 45, 45, 18, 27},
  {entry__8_6, NULL, 49, 49, 64, 64},
  {entry__8_4, NULL, 49, 49, 40, 51},
  {cont__8_5, &frame__8_4, 49, 49, 37, 64},
  {entry__8_1_std__min, NULL, 48, 48, 3, 18},
  {cont__8_2, &frame__8_1_std__min, 49, 49, 28, 28},
  {cont__8_3, &frame__8_1_std__min, 49, 49, 3, 64},
  {cont__8_7, &frame__8_1_std__min, 50, 50, 3, 11},
  {entry__9_6, NULL, 54, 54, 64, 64},
  {entry__9_4, NULL, 54, 54, 40, 51},
  {cont__9_5, &frame__9_4, 54, 54, 37, 64},
  {entry__9_1_std__max, NULL, 53, 53, 3, 18},
  {cont__9_2, &frame__9_1_std__max, 54, 54, 28, 28},
  {cont__9_3, &frame__9_1_std__max, 54, 54, 3, 64},
  {cont__9_7, &frame__9_1_std__max, 55, 55, 3, 11},
  {entry__10_4, NULL, 59, 59, 15, 18},
  {entry__10_2, NULL, 59, 59, 8, 13},
  {cont__10_3, &frame__10_2, 59, 59, 5, 18},
  {entry__10_7, NULL, 60, 60, 33, 38},
  {cont__10_8, &frame__10_7, 60, 60, 27, 39},
  {cont__10_9, &frame__10_7, 60, 60, 23, 40},
  {cont__10_10, &frame__10_7, 60, 60, 21, 40},
  {cont__10_11, &frame__10_7, 60, 60, 18, 40},
  {entry__10_5, NULL, 60, 60, 8, 16},
  {cont__10_6, &frame__10_5, 60, 60, 5, 40},
  {entry__10_13, NULL, 61, 61, 26, 31},
  {cont__10_14, &frame__10_13, 61, 61, 20, 32},
  {cont__10_15, &frame__10_13, 61, 61, 16, 33},
  {cont__10_16, &frame__10_13, 61, 61, 13, 33},
  {entry__10_12, NULL, 61, 61, 5, 33},
  {entry__10_1_std__pow, NULL, 58, 61, 3, 33},
  {entry__11_7, NULL, 70, 70, 17, 17},
  {entry__11_8, NULL, 72, 72, 16, 16},
  {entry__11_2, NULL, 67, 67, 11, 18},
  {cont__11_3, &frame__11_2, 67, 67, 5, 21},
  {cont__11_4, &frame__11_2, 69, 69, 7, 14},
  {cont__11_5, &frame__11_2, 69, 69, 7, 18},
  {cont__11_6, &frame__11_2, 68, 72, 5, 17},
  {entry__11_1_std__sqrt, NULL, 66, 72, 3, 18},
  {cont__11_9, &frame__11_1_std__sqrt, 73, 73, 3, 8},
  {entry__13_2, NULL, 82, 82, 9, 9},
  {cont__13_3, &frame__13_2, 82, 82, 9, 15},
  {cont__13_4, &frame__13_2, 82, 82, 9, 21},
  {cont__13_5, &frame__13_2, 82, 82, 24, 26},
  {cont__13_6, &frame__13_2, 82, 82, 29, 31},
  {cont__13_7, &frame__13_2, 82, 82, 29, 33},
  {cont__13_8, &frame__13_2, 82, 82, 24, 33},
  {cont__13_9, &frame__13_2, 82, 82, 5, 35},
  {cont__13_10, &frame__13_2, 83, 83, 5, 13},
  {cont__13_11, &frame__13_2, 84, 84, 5, 10},
  {cont__13_12, &frame__13_2, 84, 84, 10, 10},
  {entry__13_1_std__sin, NULL, 81, 84, 3, 10},
  {cont__13_13, &frame__13_1_std__sin, 85, 85, 3, 6},
  {entry__14_2, NULL, 92, 92, 5, 10},
  {cont__14_3, &frame__14_2, 93, 93, 9, 9},
  {cont__14_4, &frame__14_2, 93, 93, 9, 15},
  {cont__14_5, &frame__14_2, 93, 93, 9, 21},
  {cont__14_6, &frame__14_2, 93, 93, 25, 27},
  {cont__14_7, &frame__14_2, 93, 93, 25, 29},
  {cont__14_8, &frame__14_2, 93, 93, 33, 35},
  {cont__14_9, &frame__14_2, 93, 93, 25, 35},
  {cont__14_10, &frame__14_2, 93, 93, 5, 37},
  {cont__14_11, &frame__14_2, 94, 94, 5, 13},
  {cont__14_12, &frame__14_2, 94, 94, 13, 13},
  {entry__14_1_std__cos, NULL, 91, 94, 3, 13},
  {cont__14_13, &frame__14_1_std__cos, 95, 95, 3, 6},
  {entry__15_1_std__tan, NULL, 97, 97, 23, 32},
  {cont__15_2, &frame__15_1_std__tan, 97, 97, 34, 43},
  {cont__15_3, &frame__15_1_std__tan, 97, 97, 23, 43},
  {cont__15_4, &frame__15_1_std__tan, 97, 97, 20, 43},
  {entry__16_3, NULL, 99, 99, 30, 37},
  {cont__16_4, &frame__16_3, 99, 99, 27, 37},
  {entry__16_5, NULL, 99, 99, 51, 51},
  {cont__16_6, &frame__16_5, 99, 99, 44, 52},
  {cont__16_7, &frame__16_5, 99, 99, 44, 52},
  {cont__16_8, &frame__16_5, 99, 99, 40, 52},
  {entry__16_1_std__atan, NULL, 99, 99, 20, 24},
  {cont__16_2, &frame__16_1_std__atan, 99, 99, 17, 52},
  {entry__17_3, NULL, 101, 101, 26, 29},
  {cont__17_4, &frame__17_3, 101, 101, 37, 39},
  {cont__17_5, &frame__17_3, 101, 101, 31, 40},
  {cont__17_6, &frame__17_3, 101, 101, 26, 40},
  {cont__17_7, &frame__17_3, 101, 101, 23, 40},
  {entry__17_8, NULL, 101, 101, 46, 53},
  {cont__17_9, &frame__17_8, 101, 101, 43, 53},
  {entry__17_1_atan2, NULL, 101, 101, 16, 20},
  {cont__17_2, &frame__17_1_atan2, 101, 101, 13, 53},
  {entry__18_5, NULL, 104, 104, 24, 27},
  {cont__18_6, &frame__18_5, 104, 104, 36, 42},
  {cont__18_7, &frame__18_5, 104, 104, 36, 44},
  {cont__18_8, &frame__18_5, 104, 104, 36, 46},
  {cont__18_9, &frame__18_5, 104, 104, 50, 56},
  {cont__18_10, &frame__18_5, 104, 104, 50, 58},
  {cont__18_11, &frame__18_5, 104, 104, 36, 58},
  {cont__18_12, &frame__18_5, 104, 104, 29, 60},
  {cont__18_13, &frame__18_5, 104, 104, 24, 60},
  {cont__18_14, &frame__18_5, 104, 104, 21, 60},
  {entry__18_15, NULL, 104, 104, 66, 73},
  {cont__18_16, &frame__18_15, 104, 104, 63, 73},
  {entry__18_1_atan3, NULL, 104, 104, 12, 18},
  {cont__18_2, &frame__18_1_atan3, 104, 104, 10, 18},
  {cont__18_3, &frame__18_1_atan3, 104, 104, 6, 18},
  {cont__18_4, &frame__18_1_atan3, 104, 104, 3, 73},
  {entry__19_2, NULL, 111, 111, 15, 17},
  {cont__19_3, &frame__19_2, 111, 111, 15, 19},
  {cont__19_4, &frame__19_2, 111, 111, 5, 19},
  {cont__19_5, &frame__19_2, 112, 112, 8, 10},
  {cont__19_6, &frame__19_2, 112, 112, 5, 12},
  {cont__19_7, &frame__19_2, 113, 113, 5, 9},
  {cont__19_8, &frame__19_2, 113, 113, 9, 9},
  {entry__19_1_atan4, NULL, 110, 113, 3, 9},
  {cont__19_9, &frame__19_1_atan4, 114, 114, 3, 8}
};

union NODE {
  struct {
    FUNC type;
    ATTRIBUTES *attributes;
  };
  CONTINUATION continuation;
  CLOSURE closure;
};
static NODE *number__50;
static NODE *number__6;
static NODE *number__3_1415926535897932;
static NODE *number__0;
static NODE *number__3;
static NODE *number__13;
static NODE *number__23;
static NODE *number__1;
static NODE *number__2;

static const char *used_namespaces[] = {
  "std",
  NULL
};

static MODULE_INFO module_info = {
  NULL,
  "basic__math",
  continuation_info,
  sizeof(continuation_info)/sizeof(CONTINUATION_INFO),
  (NODE **)&var,
  var_names,
  sizeof(var_names)/sizeof(const char *),
  used_namespaces,
  {DEBUG_FILENAME("basic/math.sim")}
};

/******
C O D E
******/

static int already_run = false;

EXPORT void run__basic__math(void) {
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
static void entry__1_1_std__inc(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // var: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* var */ = create_cell_with_contents(arguments->slots[0]);
  // 23: ... plus &var 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* var */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__plus();
  func = myself->type;
  frame->cont = cont__1_2;
}
static void cont__1_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* var */ = arguments->slots[0];
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* var */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__2_1_std__dec(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // var: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* var */ = create_cell_with_contents(arguments->slots[0]);
  // 25: ... minus &var 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* var */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__minus();
  func = myself->type;
  frame->cont = cont__2_2;
}
static void cont__2_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* var */ = arguments->slots[0];
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* var */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__3_1_std__extend_to(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // var: 0
  // val: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* var */ = create_cell_with_contents(arguments->slots[0]);
  // 32: ... val > var
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* var */;
  arguments->slots[1] = frame->slots[1] /* val */;
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
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 32: ... : !var val
  frame->slots[3] /* temp__2 */ = create_closure(entry__3_3, 0);
  // 32: if val > var: !var val
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count =
    frame->caller_result_count >= 1 ?
    frame->caller_result_count-1 : -1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__3_4;
}
static void entry__3_3(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // var: 0
  // val: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* var */
  frame->slots[1] = myself->closure.frame->slots[1]; /* val */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 32: ... !var val
  ((CELL *)frame->slots[0])->contents /* var */ = frame->slots[1] /* val */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__3_4(void) {
  int i = argument_count;
  while (--i >= 0) {
    arguments->slots[i+1] = arguments->slots[i];
  }
  argument_count += 1;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* var */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__4_1_std__reduce_to(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // var: 0
  // val: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* var */ = create_cell_with_contents(arguments->slots[0]);
  // 39: ... val < var
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* val */;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* var */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__4_2;
}
static void cont__4_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 39: ... : !var val
  frame->slots[3] /* temp__2 */ = create_closure(entry__4_3, 0);
  // 39: if val < var: !var val
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count =
    frame->caller_result_count >= 1 ?
    frame->caller_result_count-1 : -1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__4_4;
}
static void entry__4_3(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // var: 0
  // val: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* var */
  frame->slots[1] = myself->closure.frame->slots[1]; /* val */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 39: ... !var val
  ((CELL *)frame->slots[0])->contents /* var */ = frame->slots[1] /* val */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__4_4(void) {
  int i = argument_count;
  while (--i >= 0) {
    arguments->slots[i+1] = arguments->slots[i];
  }
  argument_count += 1;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* var */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__5_1_std__abs(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // var: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* var */ = create_cell_with_contents(arguments->slots[0]);
  // 41: ... var < 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* var */;
  arguments->slots[1] = number__0;
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
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 41: ... : negate &var
  frame->slots[2] /* temp__2 */ = create_closure(entry__5_3, 0);
  // 41: ... if var < 0: negate &var
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count =
    frame->caller_result_count >= 1 ?
    frame->caller_result_count-1 : -1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__5_5;
}
static void entry__5_3(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // var: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* var */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 41: ... negate &var
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* var */;
  result_count = 1;
  myself = get__negate();
  func = myself->type;
  frame->cont = cont__5_4;
}
static void cont__5_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* var */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__5_5(void) {
  int i = argument_count;
  while (--i >= 0) {
    arguments->slots[i+1] = arguments->slots[i];
  }
  argument_count += 1;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* var */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__6_10(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 43: ... -> 0
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__0;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__6_7(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 43: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__6_8;
}
static void cont__6_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 43: ... -> -1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__6_4(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 43: ... -> 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__6_2(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // x: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* x */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 43: ... x > 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = frame->slots[0] /* x */;
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
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 43: ... -> x > 0 -> 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = func__6_4;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__6_5(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // x: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* x */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 43: ... x < 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* x */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__6_6;
}
static void cont__6_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 43: ... -> x < 0 -> -1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = func__6_7;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__6_9(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 43: ... -> true -> 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__true();
  arguments->slots[1] = func__6_10;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__6_1_std__sgn(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // x: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 43: ... -> x > 0 -> 1
  frame->slots[1] /* temp__1 */ = create_closure(entry__6_2, 0);
  // 43: ... -> x < 0 -> -1
  frame->slots[2] /* temp__2 */ = create_closure(entry__6_5, 0);
  // 43: ... cond (-> x > 0 -> 1) (-> x < 0 -> -1) -> true -> 0
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  arguments->slots[2] = func__6_9;
  result_count = frame->caller_result_count;
  myself = get__cond();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_1_std__sqr(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // var: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 45: ... var*var
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* var */;
  arguments->slots[1] = frame->slots[0] /* var */;
  result_count = 1;
  myself = get__std__times();
  func = myself->type;
  frame->cont = cont__7_2;
}
static void cont__7_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 45: ... -> var*var
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__8_1_std__min(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // args: 0
  // result: 1
  frame->slots[1] /* result */ = create_cell();
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 48: $$result args(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* args */;
  func = myself->type;
  frame->cont = cont__8_2;
}
static void cont__8_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* result */ = arguments->slots[0];
  // 49: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__8_3;
}
static void cont__8_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 49: ... : (arg) if arg < result: !result arg
  frame->slots[3] /* temp__2 */ = create_closure(entry__8_4, 1);
  // 49: for_each_from_to args 2 -1: (arg) if arg < result: !result arg
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* args */;
  arguments->slots[1] = number__2;
  arguments->slots[2] = frame->slots[2] /* temp__1 */;
  arguments->slots[3] = frame->slots[3] /* temp__2 */;
  result_count = 0;
  myself = get__for_each_from_to();
  func = myself->type;
  frame->cont = cont__8_7;
}
static void entry__8_6(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // result: 0
  // arg: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* result */
  frame->slots[1] = myself->closure.frame->slots[0]; /* arg */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 49: ... !result arg
  ((CELL *)frame->slots[0])->contents /* result */ = frame->slots[1] /* arg */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__8_4(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // arg: 0
  // result: 1
  frame->slots[1] = myself->closure.frame->slots[1]; /* result */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 49: ... arg < result
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* arg */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* result */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__8_5;
}
static void cont__8_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 49: ... : !result arg
  frame->slots[3] /* temp__2 */ = create_closure(entry__8_6, 0);
  // 49: ... if arg < result: !result arg
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__8_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 50: -> result
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* result */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__9_1_std__max(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // args: 0
  // result: 1
  frame->slots[1] /* result */ = create_cell();
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 53: $$result args(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* args */;
  func = myself->type;
  frame->cont = cont__9_2;
}
static void cont__9_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* result */ = arguments->slots[0];
  // 54: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__9_3;
}
static void cont__9_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 54: ... : (arg) if arg > result: !result arg
  frame->slots[3] /* temp__2 */ = create_closure(entry__9_4, 1);
  // 54: for_each_from_to args 2 -1: (arg) if arg > result: !result arg
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* args */;
  arguments->slots[1] = number__2;
  arguments->slots[2] = frame->slots[2] /* temp__1 */;
  arguments->slots[3] = frame->slots[3] /* temp__2 */;
  result_count = 0;
  myself = get__for_each_from_to();
  func = myself->type;
  frame->cont = cont__9_7;
}
static void entry__9_6(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // result: 0
  // arg: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* result */
  frame->slots[1] = myself->closure.frame->slots[0]; /* arg */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 54: ... !result arg
  ((CELL *)frame->slots[0])->contents /* result */ = frame->slots[1] /* arg */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__9_4(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // arg: 0
  // result: 1
  frame->slots[1] = myself->closure.frame->slots[1]; /* result */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 54: ... arg > result
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* result */;
  arguments->slots[1] = frame->slots[0] /* arg */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__9_5;
}
static void cont__9_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 54: ... : !result arg
  frame->slots[3] /* temp__2 */ = create_closure(entry__9_6, 0);
  // 54: ... if arg > result: !result arg
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__9_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 55: -> result
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* result */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__10_13(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // x: 0
  // n: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* x */
  frame->slots[1] = myself->closure.frame->slots[1]; /* n */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 61: ... n >> 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* n */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__shift_right();
  func = myself->type;
  frame->cont = cont__10_14;
}
static void cont__10_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 61: ... pow(x n >> 1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* x */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__pow();
  func = myself->type;
  frame->cont = cont__10_15;
}
static void cont__10_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 61: ... sqr(pow(x n >> 1))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__sqr();
  func = myself->type;
  frame->cont = cont__10_16;
}
static void cont__10_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 61: ... -> sqr(pow(x n >> 1))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__10_7(void) {
  allocate_initialized_frame_gc(2, 6);
  // slot allocations:
  // x: 0
  // n: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* x */
  frame->slots[1] = myself->closure.frame->slots[0]; /* n */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 60: ... n >> 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* n */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__shift_right();
  func = myself->type;
  frame->cont = cont__10_8;
}
static void cont__10_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__4 */ = arguments->slots[0];
  // 60: ... pow(x n >> 1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* x */;
  arguments->slots[1] = frame->slots[5] /* temp__4 */;
  result_count = 1;
  myself = get__pow();
  func = myself->type;
  frame->cont = cont__10_9;
}
static void cont__10_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 60: ... sqr(pow(x n >> 1))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__sqr();
  func = myself->type;
  frame->cont = cont__10_10;
}
static void cont__10_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 60: ... x*sqr(pow(x n >> 1))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* x */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__times();
  func = myself->type;
  frame->cont = cont__10_11;
}
static void cont__10_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 60: ... -> x*sqr(pow(x n >> 1))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__10_4(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 59: ... -> 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__10_2(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // n: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* n */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 59: ... n == 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* n */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__10_3;
}
static void cont__10_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 59: -> n == 0 -> 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = func__10_4;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__10_5(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // n: 0
  // x: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* n */
  frame->slots[1] = myself->closure.frame->slots[0]; /* x */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 60: ... is_odd(n)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* n */;
  result_count = 1;
  myself = get__is_odd();
  func = myself->type;
  frame->cont = cont__10_6;
}
static void cont__10_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 60: ... -> x*sqr(pow(x n >> 1))
  frame->slots[3] /* temp__2 */ = create_closure(entry__10_7, 0);
  // 60: -> is_odd(n) -> x*sqr(pow(x n >> 1))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__10_12(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // x: 0
  // n: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* x */
  frame->slots[1] = myself->closure.frame->slots[1]; /* n */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 61: ... -> sqr(pow(x n >> 1))
  frame->slots[2] /* temp__1 */ = create_closure(entry__10_13, 0);
  // 61: -> true -> sqr(pow(x n >> 1))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__true();
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__10_1_std__pow(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // x: 0
  // n: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 59: -> n == 0 -> 1
  frame->slots[2] /* temp__1 */ = create_closure(entry__10_2, 0);
  // 60: -> is_odd(n) -> x*sqr(pow(x n >> 1))
  frame->slots[3] /* temp__2 */ = create_closure(entry__10_5, 0);
  // 61: -> true -> sqr(pow(x n >> 1))
  frame->slots[4] /* temp__3 */ = create_closure(entry__10_12, 0);
  // 58: cond
  // 59:   -> n == 0 -> 1
  // 60:   -> is_odd(n) -> x*sqr(pow(x n >> 1))
  // 61:   -> true -> sqr(pow(x n >> 1))
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  arguments->slots[2] = frame->slots[4] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__cond();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__11_1_std__sqrt(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // x: 0
  // low: 1
  // high: 2
  frame->slots[1] /* low */ = create_cell();
  frame->slots[2] /* high */ = create_cell();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 64: $$low 0
  ((CELL *)frame->slots[1])->contents /* low */ = number__0;
  // 65: $$high x
  ((CELL *)frame->slots[2])->contents /* high */ = frame->slots[0] /* x */;
  // 66: ... :
  // 67:   $mid (high+low)/2
  // 68:   if
  // 69:     sqr(mid) > x:
  // 70:       !high mid
  // 71:     :
  // 72:       !low mid
  frame->slots[3] /* temp__1 */ = create_closure(entry__11_2, 0);
  // 66: repeat 50:
  // 67:   $mid (high+low)/2
  // 68:   if
  // 69:     sqr(mid) > x:
  // 70:       !high mid
  // 71:     :
  // 72:       !low mid
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__50;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 0;
  myself = get__repeat();
  func = myself->type;
  frame->cont = cont__11_9;
}
static void entry__11_7(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // high: 0
  // mid: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* high */
  frame->slots[1] = myself->closure.frame->slots[3]; /* mid */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 70: !high mid
  ((CELL *)frame->slots[0])->contents /* high */ = frame->slots[1] /* mid */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__11_8(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // low: 0
  // mid: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* low */
  frame->slots[1] = myself->closure.frame->slots[3]; /* mid */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 72: !low mid
  ((CELL *)frame->slots[0])->contents /* low */ = frame->slots[1] /* mid */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__11_2(void) {
  allocate_initialized_frame_gc(3, 8);
  // slot allocations:
  // high: 0
  // low: 1
  // x: 2
  // mid: 3
  frame->slots[0] = myself->closure.frame->slots[2]; /* high */
  frame->slots[1] = myself->closure.frame->slots[1]; /* low */
  frame->slots[2] = myself->closure.frame->slots[0]; /* x */
  frame->slots[3] /* mid */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 67: ... high+low
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* high */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* low */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__11_3;
}
static void cont__11_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 67: $mid (high+low)/2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__std__over();
  func = myself->type;
  frame->cont = cont__11_4;
}
static void cont__11_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* mid */, arguments->slots[0]);
  // 69: sqr(mid)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* mid */;
  result_count = 1;
  myself = get__sqr();
  func = myself->type;
  frame->cont = cont__11_5;
}
static void cont__11_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 69: sqr(mid) > x
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* x */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__11_6;
}
static void cont__11_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 69: ... :
  // 70:   !high mid
  frame->slots[6] /* temp__3 */ = create_closure(entry__11_7, 0);
  // 71: :
  // 72:   !low mid
  frame->slots[7] /* temp__4 */ = create_closure(entry__11_8, 0);
  // 68: if
  // 69:   sqr(mid) > x:
  // 70:     !high mid
  // 71:   :
  // 72:     !low mid
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  arguments->slots[2] = frame->slots[7] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__11_9(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 73: -> low
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* low */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__13_1_std__sin(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // alpha: 0
  // p: 1
  // s: 2
  // t: 3
  frame->slots[1] /* p */ = create_cell();
  frame->slots[2] /* s */ = create_cell();
  frame->slots[3] /* t */ = create_cell();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 78: $$p 1
  ((CELL *)frame->slots[1])->contents /* p */ = number__1;
  // 79: $$s alpha
  ((CELL *)frame->slots[2])->contents /* s */ = frame->slots[0] /* alpha */;
  // 80: $$t alpha
  ((CELL *)frame->slots[3])->contents /* t */ = frame->slots[0] /* alpha */;
  // 81: ... :
  // 82:   !t -t*alpha*alpha/(2*p*(2*p+1))
  // 83:   plus &s t
  // 84:   inc &p
  frame->slots[4] /* temp__1 */ = create_closure(entry__13_2, 0);
  // 81: repeat 13:
  // 82:   !t -t*alpha*alpha/(2*p*(2*p+1))
  // 83:   plus &s t
  // 84:   inc &p
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__13;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__repeat();
  func = myself->type;
  frame->cont = cont__13_13;
}
static void entry__13_2(void) {
  allocate_initialized_frame_gc(4, 11);
  // slot allocations:
  // t: 0
  // alpha: 1
  // p: 2
  // s: 3
  frame->slots[0] = myself->closure.frame->slots[3]; /* t */
  frame->slots[1] = myself->closure.frame->slots[0]; /* alpha */
  frame->slots[2] = myself->closure.frame->slots[1]; /* p */
  frame->slots[3] = myself->closure.frame->slots[2]; /* s */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 82: ... t
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* t */;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__13_3;
}
static void cont__13_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 82: ... t*alpha
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__3 */;
  arguments->slots[1] = frame->slots[1] /* alpha */;
  result_count = 1;
  myself = get__std__times();
  func = myself->type;
  frame->cont = cont__13_4;
}
static void cont__13_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 82: ... t*alpha*alpha
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  arguments->slots[1] = frame->slots[1] /* alpha */;
  result_count = 1;
  myself = get__std__times();
  func = myself->type;
  frame->cont = cont__13_5;
}
static void cont__13_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 82: ... 2*p
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__2;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* p */;
  result_count = 1;
  myself = get__std__times();
  func = myself->type;
  frame->cont = cont__13_6;
}
static void cont__13_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__5 */ = arguments->slots[0];
  // 82: ... 2*p
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__2;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* p */;
  result_count = 1;
  myself = get__std__times();
  func = myself->type;
  frame->cont = cont__13_7;
}
static void cont__13_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__7 */ = arguments->slots[0];
  // 82: ... 2*p+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__7 */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__13_8;
}
static void cont__13_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__6 */ = arguments->slots[0];
  // 82: ... 2*p*(2*p+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__5 */;
  arguments->slots[1] = frame->slots[9] /* temp__6 */;
  result_count = 1;
  myself = get__std__times();
  func = myself->type;
  frame->cont = cont__13_9;
}
static void cont__13_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__4 */ = arguments->slots[0];
  // 82: !t -t*alpha*alpha/(2*p*(2*p+1))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__4 */;
  result_count = 1;
  myself = get__std__over();
  func = myself->type;
  frame->cont = cont__13_10;
}
static void cont__13_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* t */ = arguments->slots[0];
  // 83: plus &s t
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* s */;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* t */;
  result_count = 1;
  myself = get__plus();
  func = myself->type;
  frame->cont = cont__13_11;
}
static void cont__13_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* s */ = arguments->slots[0];
  // 84: inc &p
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* p */;
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
  ((CELL *)frame->slots[2])->contents /* p */ = arguments->slots[0];
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
  // 85: -> s
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* s */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__14_1_std__cos(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // alpha: 0
  // p: 1
  // s: 2
  // t: 3
  frame->slots[1] /* p */ = create_cell();
  frame->slots[2] /* s */ = create_cell();
  frame->slots[3] /* t */ = create_cell();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 88: $$p 0
  ((CELL *)frame->slots[1])->contents /* p */ = number__0;
  // 89: $$s 1
  ((CELL *)frame->slots[2])->contents /* s */ = number__1;
  // 90: $$t 1
  ((CELL *)frame->slots[3])->contents /* t */ = number__1;
  // 91: ... :
  // 92:   inc &p
  // 93:   !t -t*alpha*alpha/((2*p-1)*(2*p))
  // 94:   plus &s t
  frame->slots[4] /* temp__1 */ = create_closure(entry__14_2, 0);
  // 91: repeat 13:
  // 92:   inc &p
  // 93:   !t -t*alpha*alpha/((2*p-1)*(2*p))
  // 94:   plus &s t
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__13;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__repeat();
  func = myself->type;
  frame->cont = cont__14_13;
}
static void entry__14_2(void) {
  allocate_initialized_frame_gc(4, 11);
  // slot allocations:
  // p: 0
  // t: 1
  // alpha: 2
  // s: 3
  frame->slots[0] = myself->closure.frame->slots[1]; /* p */
  frame->slots[1] = myself->closure.frame->slots[3]; /* t */
  frame->slots[2] = myself->closure.frame->slots[0]; /* alpha */
  frame->slots[3] = myself->closure.frame->slots[2]; /* s */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 92: inc &p
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* p */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__14_3;
}
static void cont__14_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* p */ = arguments->slots[0];
  // 93: ... t
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* t */;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__14_4;
}
static void cont__14_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 93: ... t*alpha
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__3 */;
  arguments->slots[1] = frame->slots[2] /* alpha */;
  result_count = 1;
  myself = get__std__times();
  func = myself->type;
  frame->cont = cont__14_5;
}
static void cont__14_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 93: ... t*alpha*alpha
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  arguments->slots[1] = frame->slots[2] /* alpha */;
  result_count = 1;
  myself = get__std__times();
  func = myself->type;
  frame->cont = cont__14_6;
}
static void cont__14_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 93: ... 2*p
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__2;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* p */;
  result_count = 1;
  myself = get__std__times();
  func = myself->type;
  frame->cont = cont__14_7;
}
static void cont__14_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__6 */ = arguments->slots[0];
  // 93: ... 2*p-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__6 */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__14_8;
}
static void cont__14_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__5 */ = arguments->slots[0];
  // 93: ... 2*p
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__2;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* p */;
  result_count = 1;
  myself = get__std__times();
  func = myself->type;
  frame->cont = cont__14_9;
}
static void cont__14_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__7 */ = arguments->slots[0];
  // 93: ... 2*p-1)*(2*p
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__5 */;
  arguments->slots[1] = frame->slots[10] /* temp__7 */;
  result_count = 1;
  myself = get__std__times();
  func = myself->type;
  frame->cont = cont__14_10;
}
static void cont__14_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__4 */ = arguments->slots[0];
  // 93: !t -t*alpha*alpha/((2*p-1)*(2*p))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__4 */;
  result_count = 1;
  myself = get__std__over();
  func = myself->type;
  frame->cont = cont__14_11;
}
static void cont__14_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* t */ = arguments->slots[0];
  // 94: plus &s t
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* s */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* t */;
  result_count = 1;
  myself = get__plus();
  func = myself->type;
  frame->cont = cont__14_12;
}
static void cont__14_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* s */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__14_13(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 95: -> s
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* s */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__15_1_std__tan(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // alpha: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 97: ... sin(alpha)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* alpha */;
  result_count = 1;
  myself = get__sin();
  func = myself->type;
  frame->cont = cont__15_2;
}
static void cont__15_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 97: ... cos(alpha)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* alpha */;
  result_count = 1;
  myself = get__cos();
  func = myself->type;
  frame->cont = cont__15_3;
}
static void cont__15_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 97: ... sin(alpha)/cos(alpha)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__over();
  func = myself->type;
  frame->cont = cont__15_4;
}
static void cont__15_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 97: ... -> sin(alpha)/cos(alpha)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__16_3(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // x: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* x */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 99: ... atan2(x)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* x */;
  result_count = 1;
  myself = var._atan2;
  func = myself->type;
  frame->cont = cont__16_4;
}
static void cont__16_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 99: ... -> atan2(x)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__16_5(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // x: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* x */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 99: ... x
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* x */;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__16_6;
}
static void cont__16_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 99: ... atan2(-x)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = var._atan2;
  func = myself->type;
  frame->cont = cont__16_7;
}
static void cont__16_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 99: ... atan2(-x)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__16_8;
}
static void cont__16_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 99: ... -> -atan2(-x)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__16_1_std__atan(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // x: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 99: ... x > 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = frame->slots[0] /* x */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__16_2;
}
static void cont__16_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 99: ... -> atan2(x)
  frame->slots[2] /* temp__2 */ = create_closure(entry__16_3, 0);
  // 99: ... -> -atan2(-x)
  frame->slots[3] /* temp__3 */ = create_closure(entry__16_5, 0);
  // 99: ... if x > 0 (-> atan2(x)) -> -atan2(-x)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  arguments->slots[2] = frame->slots[3] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__17_3(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // x: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* x */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 101: ... PI/2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__PI();
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__std__over();
  func = myself->type;
  frame->cont = cont__17_4;
}
static void cont__17_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 101: ... 1/x
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__1;
  arguments->slots[1] = frame->slots[0] /* x */;
  result_count = 1;
  myself = get__std__over();
  func = myself->type;
  frame->cont = cont__17_5;
}
static void cont__17_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__4 */ = arguments->slots[0];
  // 101: ... atan3(1/x)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__4 */;
  result_count = 1;
  myself = var._atan3;
  func = myself->type;
  frame->cont = cont__17_6;
}
static void cont__17_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 101: ... PI/2-atan3(1/x)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__17_7;
}
static void cont__17_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 101: ... -> PI/2-atan3(1/x)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__17_8(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // x: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* x */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 101: ... atan3(x)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* x */;
  result_count = 1;
  myself = var._atan3;
  func = myself->type;
  frame->cont = cont__17_9;
}
static void cont__17_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 101: ... -> atan3(x)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__17_1_atan2(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // x: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 101: ... x > 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__1;
  arguments->slots[1] = frame->slots[0] /* x */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__17_2;
}
static void cont__17_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 101: ... -> PI/2-atan3(1/x)
  frame->slots[2] /* temp__2 */ = create_closure(entry__17_3, 0);
  // 101: ... -> atan3(x)
  frame->slots[3] /* temp__3 */ = create_closure(entry__17_8, 0);
  // 101: ... if x > 1 (-> PI/2-atan3(1/x)) -> atan3(x)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  arguments->slots[2] = frame->slots[3] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__18_5(void) {
  allocate_initialized_frame_gc(1, 10);
  // slot allocations:
  // x: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* x */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 104: ... PI/6
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__PI();
  arguments->slots[1] = number__6;
  result_count = 1;
  myself = get__std__over();
  func = myself->type;
  frame->cont = cont__18_6;
}
static void cont__18_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 104: ... sqrt(3)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__3;
  result_count = 1;
  myself = get__sqrt();
  func = myself->type;
  frame->cont = cont__18_7;
}
static void cont__18_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__7 */ = arguments->slots[0];
  // 104: ... sqrt(3)*x
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__7 */;
  arguments->slots[1] = frame->slots[0] /* x */;
  result_count = 1;
  myself = get__std__times();
  func = myself->type;
  frame->cont = cont__18_8;
}
static void cont__18_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__6 */ = arguments->slots[0];
  // 104: ... sqrt(3)*x-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__6 */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__18_9;
}
static void cont__18_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__5 */ = arguments->slots[0];
  // 104: ... sqrt(3)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__3;
  result_count = 1;
  myself = get__sqrt();
  func = myself->type;
  frame->cont = cont__18_10;
}
static void cont__18_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__9 */ = arguments->slots[0];
  // 104: ... sqrt(3)+x
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__9 */;
  arguments->slots[1] = frame->slots[0] /* x */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__18_11;
}
static void cont__18_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__8 */ = arguments->slots[0];
  // 104: ... sqrt(3)*x-1)/(sqrt(3)+x
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__5 */;
  arguments->slots[1] = frame->slots[8] /* temp__8 */;
  result_count = 1;
  myself = get__std__over();
  func = myself->type;
  frame->cont = cont__18_12;
}
static void cont__18_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__4 */ = arguments->slots[0];
  // 104: ... atan4((sqrt(3)*x-1)/(sqrt(3)+x))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__4 */;
  result_count = 1;
  myself = var._atan4;
  func = myself->type;
  frame->cont = cont__18_13;
}
static void cont__18_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 104: ... PI/6+atan4((sqrt(3)*x-1)/(sqrt(3)+x))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__18_14;
}
static void cont__18_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 104: ... -> PI/6+atan4((sqrt(3)*x-1)/(sqrt(3)+x))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__18_15(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // x: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* x */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 104: ... atan4(x)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* x */;
  result_count = 1;
  myself = var._atan4;
  func = myself->type;
  frame->cont = cont__18_16;
}
static void cont__18_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 104: ... -> atan4(x)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__18_1_atan3(void) {
  allocate_initialized_frame_gc(1, 6);
  // slot allocations:
  // x: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 104: ... sqrt(3)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__3;
  result_count = 1;
  myself = get__sqrt();
  func = myself->type;
  frame->cont = cont__18_2;
}
static void cont__18_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 104: ... 2-sqrt(3)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__2;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__18_3;
}
static void cont__18_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 104: ... x > 2-sqrt(3)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[0] /* x */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__18_4;
}
static void cont__18_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 104: ... -> PI/6+atan4((sqrt(3)*x-1)/(sqrt(3)+x))
  frame->slots[4] /* temp__4 */ = create_closure(entry__18_5, 0);
  // 104: ... -> atan4(x)
  frame->slots[5] /* temp__5 */ = create_closure(entry__18_15, 0);
  // 104: if x > 2-sqrt(3) (-> PI/6+atan4((sqrt(3)*x-1)/(sqrt(3)+x))) -> atan4(x)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__4 */;
  arguments->slots[2] = frame->slots[5] /* temp__5 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__19_1_atan4(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // x: 0
  // sum: 1
  // s: 2
  // p: 3
  frame->slots[1] /* sum */ = create_cell();
  frame->slots[2] /* s */ = create_cell();
  frame->slots[3] /* p */ = create_cell();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 107: $$sum 0
  ((CELL *)frame->slots[1])->contents /* sum */ = number__0;
  // 108: $$s 1
  ((CELL *)frame->slots[2])->contents /* s */ = number__1;
  // 109: $$p x
  ((CELL *)frame->slots[3])->contents /* p */ = frame->slots[0] /* x */;
  // 110: ... : (i)
  // 111:   plus &sum s*p/i
  // 112:   !p p*x*x
  // 113:   !s -s
  frame->slots[4] /* temp__1 */ = create_closure(entry__19_2, 1);
  // 110: from_to_by 1 23 2: (i)
  // 111:   plus &sum s*p/i
  // 112:   !p p*x*x
  // 113:   !s -s
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = number__1;
  arguments->slots[1] = number__23;
  arguments->slots[2] = number__2;
  arguments->slots[3] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__from_to_by();
  func = myself->type;
  frame->cont = cont__19_9;
}
static void entry__19_2(void) {
  allocate_initialized_frame_gc(5, 7);
  // slot allocations:
  // i: 0
  // sum: 1
  // s: 2
  // p: 3
  // x: 4
  frame->slots[1] = myself->closure.frame->slots[1]; /* sum */
  frame->slots[2] = myself->closure.frame->slots[2]; /* s */
  frame->slots[3] = myself->closure.frame->slots[3]; /* p */
  frame->slots[4] = myself->closure.frame->slots[0]; /* x */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 111: ... s*p
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* s */;
  arguments->slots[1] = ((CELL *)frame->slots[3])->contents /* p */;
  result_count = 1;
  myself = get__std__times();
  func = myself->type;
  frame->cont = cont__19_3;
}
static void cont__19_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 111: ... s*p/i
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[0] /* i */;
  result_count = 1;
  myself = get__std__over();
  func = myself->type;
  frame->cont = cont__19_4;
}
static void cont__19_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 111: plus &sum s*p/i
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* sum */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 1;
  myself = get__plus();
  func = myself->type;
  frame->cont = cont__19_5;
}
static void cont__19_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* sum */ = arguments->slots[0];
  // 112: ... p*x
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* p */;
  arguments->slots[1] = frame->slots[4] /* x */;
  result_count = 1;
  myself = get__std__times();
  func = myself->type;
  frame->cont = cont__19_6;
}
static void cont__19_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 112: !p p*x*x
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* x */;
  result_count = 1;
  myself = get__std__times();
  func = myself->type;
  frame->cont = cont__19_7;
}
static void cont__19_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* p */ = arguments->slots[0];
  // 113: !s -s
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* s */;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__19_8;
}
static void cont__19_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* s */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__19_9(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 114: -> sum
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* sum */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
EXPORT void collect__basic__math(void) {
  var.std__inc = collect_node(var.std__inc);
  var.std__dec = collect_node(var.std__dec);
  var.std__extend_to = collect_node(var.std__extend_to);
  var.std__reduce_to = collect_node(var.std__reduce_to);
  var.std__abs = collect_node(var.std__abs);
  var.std__sgn = collect_node(var.std__sgn);
  var.std__sqr = collect_node(var.std__sqr);
  var.std__min = collect_node(var.std__min);
  var.std__max = collect_node(var.std__max);
  var.std__pow = collect_node(var.std__pow);
  var.std__sqrt = collect_node(var.std__sqrt);
  var.std__PI = collect_node(var.std__PI);
  var.std__sin = collect_node(var.std__sin);
  var.std__cos = collect_node(var.std__cos);
  var.std__tan = collect_node(var.std__tan);
  var.std__atan = collect_node(var.std__atan);
  var._atan2 = collect_node(var._atan2);
  var._atan3 = collect_node(var._atan3);
  var._atan4 = collect_node(var._atan4);
}

static int already_run_phase_1 = false;

EXPORT void phase_1__basic__math(void) {
  if (already_run_phase_1) return;
  already_run_phase_1 = true;
  register_module_info(&module_info);
}

static int already_run_phase_2 = false;

EXPORT void phase_2__basic__math(void) {
  if (already_run_phase_2) return;
  already_run_phase_2 = true;
  number__50 = from_uint32(50U);
  number__6 = from_uint32(6U);
  number__3_1415926535897932 = from_double(3.1415926535897932);
  number__0 = from_uint32(0U);
  number__3 = from_uint32(3U);
  number__13 = from_uint32(13U);
  number__23 = from_uint32(23U);
  number__1 = from_uint32(1U);
  number__2 = from_uint32(2U);
  func__1_1_std__inc = create_function(entry__1_1_std__inc, 1);
  func__2_1_std__dec = create_function(entry__2_1_std__dec, 1);
  func__3_1_std__extend_to = create_function(entry__3_1_std__extend_to, 2);
  func__4_1_std__reduce_to = create_function(entry__4_1_std__reduce_to, 2);
  func__5_1_std__abs = create_function(entry__5_1_std__abs, 1);
  func__6_4 = create_function(entry__6_4, 0);
  func__6_7 = create_function(entry__6_7, 0);
  func__6_10 = create_function(entry__6_10, 0);
  func__6_9 = create_function(entry__6_9, 0);
  func__6_1_std__sgn = create_function(entry__6_1_std__sgn, 1);
  func__7_1_std__sqr = create_function(entry__7_1_std__sqr, 1);
  func__8_1_std__min = create_function(entry__8_1_std__min, -1);
  func__9_1_std__max = create_function(entry__9_1_std__max, -1);
  func__10_4 = create_function(entry__10_4, 0);
  func__10_1_std__pow = create_function(entry__10_1_std__pow, 2);
  func__11_1_std__sqrt = create_function(entry__11_1_std__sqrt, 1);
  func__13_1_std__sin = create_function(entry__13_1_std__sin, 1);
  func__14_1_std__cos = create_function(entry__14_1_std__cos, 1);
  func__15_1_std__tan = create_function(entry__15_1_std__tan, 1);
  func__16_1_std__atan = create_function(entry__16_1_std__atan, 1);
  func__17_1_atan2 = create_function(entry__17_1_atan2, 1);
  func__18_1_atan3 = create_function(entry__18_1_atan3, 1);
  func__19_1_atan4 = create_function(entry__19_1_atan4, 1);
}

static int already_run_phase_3 = false;

EXPORT void phase_3__basic__math(void) {
  if (already_run_phase_3) return;
  already_run_phase_3 = true;
  set_module("basic__math");
  set_used_namespaces(used_namespaces);
  define_single_assign_static("std", "inc", get__std__inc, &var.std__inc);
  define_single_assign_static("std", "dec", get__std__dec, &var.std__dec);
  define_single_assign_static("std", "extend_to", get__std__extend_to, &var.std__extend_to);
  define_single_assign_static("std", "reduce_to", get__std__reduce_to, &var.std__reduce_to);
  define_single_assign_static("std", "abs", get__std__abs, &var.std__abs);
  define_single_assign_static("std", "sgn", get__std__sgn, &var.std__sgn);
  define_single_assign_static("std", "sqr", get__std__sqr, &var.std__sqr);
  define_single_assign_static("std", "min", get__std__min, &var.std__min);
  define_single_assign_static("std", "max", get__std__max, &var.std__max);
  define_single_assign_static("std", "pow", get__std__pow, &var.std__pow);
  define_single_assign_static("std", "sqrt", get__std__sqrt, &var.std__sqrt);
  define_single_assign_static("std", "PI", get__std__PI, &var.std__PI);
  define_single_assign_static("std", "sin", get__std__sin, &var.std__sin);
  define_single_assign_static("std", "cos", get__std__cos, &var.std__cos);
  define_single_assign_static("std", "tan", get__std__tan, &var.std__tan);
  define_single_assign_static("std", "atan", get__std__atan, &var.std__atan);
}

static int already_run_phase_4 = false;

EXPORT void phase_4__basic__math(void) {
  if (already_run_phase_4) return;
  already_run_phase_4 = true;
  set_module("basic__math");
  set_used_namespaces(used_namespaces);
  use_read_only(NULL, "PI", &get__PI, &get_value_or_future__PI);
  use_read_only(NULL, "cond", &get__cond, &get_value_or_future__cond);
  use_read_only(NULL, "cos", &get__cos, &get_value_or_future__cos);
  use_read_only(NULL, "for_each_from_to", &get__for_each_from_to, &get_value_or_future__for_each_from_to);
  use_read_only(NULL, "from_to_by", &get__from_to_by, &get_value_or_future__from_to_by);
  use_read_only(NULL, "if", &get__if, &get_value_or_future__if);
  use_read_only(NULL, "inc", &get__inc, &get_value_or_future__inc);
  use_read_only(NULL, "is_odd", &get__is_odd, &get_value_or_future__is_odd);
  use_read_only(NULL, "minus", &get__minus, &get_value_or_future__minus);
  use_read_only(NULL, "negate", &get__negate, &get_value_or_future__negate);
  use_read_only(NULL, "plus", &get__plus, &get_value_or_future__plus);
  use_read_only(NULL, "pow", &get__pow, &get_value_or_future__pow);
  use_read_only(NULL, "repeat", &get__repeat, &get_value_or_future__repeat);
  use_read_only(NULL, "sin", &get__sin, &get_value_or_future__sin);
  use_read_only(NULL, "sqr", &get__sqr, &get_value_or_future__sqr);
  use_read_only(NULL, "sqrt", &get__sqrt, &get_value_or_future__sqrt);
  use_read_only("std", "equal", &get__std__equal, &get_value_or_future__std__equal);
  use_read_only("std", "less", &get__std__less, &get_value_or_future__std__less);
  use_read_only("std", "minus", &get__std__minus, &get_value_or_future__std__minus);
  use_read_only("std", "negate", &get__std__negate, &get_value_or_future__std__negate);
  use_read_only("std", "over", &get__std__over, &get_value_or_future__std__over);
  use_read_only("std", "plus", &get__std__plus, &get_value_or_future__std__plus);
  use_read_only("std", "shift_right", &get__std__shift_right, &get_value_or_future__std__shift_right);
  use_read_only("std", "times", &get__std__times, &get_value_or_future__std__times);
  use_read_only(NULL, "true", &get__true, &get_value_or_future__true);
}

static int already_run_phase_5 = false;

EXPORT void phase_5__basic__math(void) {
  if (already_run_phase_5) return;
  already_run_phase_5 = true;
  assign_variable(&var.std__inc, &func__1_1_std__inc);
  assign_variable(&var.std__dec, &func__2_1_std__dec);
  assign_variable(&var.std__extend_to, &func__3_1_std__extend_to);
  assign_variable(&var.std__reduce_to, &func__4_1_std__reduce_to);
  assign_variable(&var.std__abs, &func__5_1_std__abs);
  assign_variable(&var.std__sgn, &func__6_1_std__sgn);
  assign_variable(&var.std__sqr, &func__7_1_std__sqr);
  assign_variable(&var.std__min, &func__8_1_std__min);
  assign_variable(&var.std__max, &func__9_1_std__max);
  assign_variable(&var.std__pow, &func__10_1_std__pow);
  assign_variable(&var.std__sqrt, &func__11_1_std__sqrt);
  assign_value(&var.std__PI, number__3_1415926535897932);
  assign_variable(&var.std__sin, &func__13_1_std__sin);
  assign_variable(&var.std__cos, &func__14_1_std__cos);
  assign_variable(&var.std__tan, &func__15_1_std__tan);
  assign_variable(&var.std__atan, &func__16_1_std__atan);
  assign_variable(&var._atan2, &func__17_1_atan2);
  assign_variable(&var._atan3, &func__18_1_atan3);
  assign_variable(&var._atan4, &func__19_1_atan4);
}

static int already_run_phase_6 = false;

EXPORT void phase_6__basic__math(void) {
  if (already_run_phase_6) return;
  already_run_phase_6 = true;
  register_collector(collect__basic__math);
}
