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
IMPORT void set_module(const char *name);
IMPORT NODE *from_uint32(uint32_t val);
IMPORT NODE *from_double(double val);
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
static NODE *func__std__inc_1;
static void entry__std__inc_1(void);
static FRAME_INFO frame__std__inc_1 = {1, {"var"}};
static void cont__std__inc_2(void);
static NODE *get__std__inc(void) {
  return var.std__inc;
}
static NODE *func__std__dec_1;
static void entry__std__dec_1(void);
static FRAME_INFO frame__std__dec_1 = {1, {"var"}};
static void cont__std__dec_2(void);
static NODE *get__std__dec(void) {
  return var.std__dec;
}
static NODE *func__std__extend_to_1;
static void entry__std__extend_to_1(void);
static FRAME_INFO frame__std__extend_to_1 = {2, {"var", "val"}};
static void cont__std__extend_to_2(void);
static NODE *func__std__extend_to_3;
static void entry__std__extend_to_3(void);
static FRAME_INFO frame__std__extend_to_3 = {2, {"var", "val"}};
static void cont__std__extend_to_4(void);
static NODE *get__std__extend_to(void) {
  return var.std__extend_to;
}
static NODE *func__std__reduce_to_1;
static void entry__std__reduce_to_1(void);
static FRAME_INFO frame__std__reduce_to_1 = {2, {"var", "val"}};
static void cont__std__reduce_to_2(void);
static NODE *func__std__reduce_to_3;
static void entry__std__reduce_to_3(void);
static FRAME_INFO frame__std__reduce_to_3 = {2, {"var", "val"}};
static void cont__std__reduce_to_4(void);
static NODE *get__std__reduce_to(void) {
  return var.std__reduce_to;
}
static NODE *func__std__abs_1;
static void entry__std__abs_1(void);
static FRAME_INFO frame__std__abs_1 = {1, {"var"}};
static void cont__std__abs_2(void);
static NODE *func__std__abs_3;
static void entry__std__abs_3(void);
static FRAME_INFO frame__std__abs_3 = {1, {"var"}};
static void cont__std__abs_4(void);
static void cont__std__abs_5(void);
static NODE *get__std__abs(void) {
  return var.std__abs;
}
static NODE *func__std__sgn_1;
static void entry__std__sgn_1(void);
static FRAME_INFO frame__std__sgn_1 = {1, {"x"}};
static NODE *func__std__sgn_2;
static void entry__std__sgn_2(void);
static FRAME_INFO frame__std__sgn_2 = {1, {"x"}};
static void cont__std__sgn_3(void);
static NODE *func__std__sgn_4;
static void entry__std__sgn_4(void);
static FRAME_INFO frame__std__sgn_4 = {0, {}};
static NODE *func__std__sgn_5;
static void entry__std__sgn_5(void);
static FRAME_INFO frame__std__sgn_5 = {1, {"x"}};
static void cont__std__sgn_6(void);
static NODE *func__std__sgn_7;
static void entry__std__sgn_7(void);
static FRAME_INFO frame__std__sgn_7 = {0, {}};
static void cont__std__sgn_8(void);
static NODE *func__std__sgn_9;
static void entry__std__sgn_9(void);
static FRAME_INFO frame__std__sgn_9 = {0, {}};
static NODE *func__std__sgn_10;
static void entry__std__sgn_10(void);
static FRAME_INFO frame__std__sgn_10 = {0, {}};
static NODE *get__std__sgn(void) {
  return var.std__sgn;
}
static NODE *func__std__sqr_1;
static void entry__std__sqr_1(void);
static FRAME_INFO frame__std__sqr_1 = {1, {"var"}};
static void cont__std__sqr_2(void);
static NODE *get__std__sqr(void) {
  return var.std__sqr;
}
static NODE *func__std__min_1;
static void entry__std__min_1(void);
static FRAME_INFO frame__std__min_1 = {2, {"args", "result"}};
static void cont__std__min_2(void);
static void cont__std__min_3(void);
static NODE *func__std__min_4;
static void entry__std__min_4(void);
static FRAME_INFO frame__std__min_4 = {2, {"arg", "result"}};
static void cont__std__min_5(void);
static NODE *func__std__min_6;
static void entry__std__min_6(void);
static FRAME_INFO frame__std__min_6 = {2, {"result", "arg"}};
static void cont__std__min_7(void);
static NODE *get__std__min(void) {
  return var.std__min;
}
static NODE *func__std__max_1;
static void entry__std__max_1(void);
static FRAME_INFO frame__std__max_1 = {2, {"args", "result"}};
static void cont__std__max_2(void);
static void cont__std__max_3(void);
static NODE *func__std__max_4;
static void entry__std__max_4(void);
static FRAME_INFO frame__std__max_4 = {2, {"arg", "result"}};
static void cont__std__max_5(void);
static NODE *func__std__max_6;
static void entry__std__max_6(void);
static FRAME_INFO frame__std__max_6 = {2, {"result", "arg"}};
static void cont__std__max_7(void);
static NODE *get__std__max(void) {
  return var.std__max;
}
static NODE *func__std__pow_1;
static void entry__std__pow_1(void);
static FRAME_INFO frame__std__pow_1 = {2, {"x", "n"}};
static NODE *func__std__pow_2;
static void entry__std__pow_2(void);
static FRAME_INFO frame__std__pow_2 = {1, {"n"}};
static void cont__std__pow_3(void);
static NODE *func__std__pow_4;
static void entry__std__pow_4(void);
static FRAME_INFO frame__std__pow_4 = {0, {}};
static NODE *func__std__pow_5;
static void entry__std__pow_5(void);
static FRAME_INFO frame__std__pow_5 = {2, {"n", "x"}};
static void cont__std__pow_6(void);
static NODE *func__std__pow_7;
static void entry__std__pow_7(void);
static FRAME_INFO frame__std__pow_7 = {2, {"x", "n"}};
static void cont__std__pow_8(void);
static void cont__std__pow_9(void);
static void cont__std__pow_10(void);
static void cont__std__pow_11(void);
static NODE *func__std__pow_12;
static void entry__std__pow_12(void);
static FRAME_INFO frame__std__pow_12 = {2, {"x", "n"}};
static NODE *func__std__pow_13;
static void entry__std__pow_13(void);
static FRAME_INFO frame__std__pow_13 = {2, {"x", "n"}};
static void cont__std__pow_14(void);
static void cont__std__pow_15(void);
static void cont__std__pow_16(void);
static NODE *get__std__pow(void) {
  return var.std__pow;
}
static NODE *func__std__sqrt_1;
static void entry__std__sqrt_1(void);
static FRAME_INFO frame__std__sqrt_1 = {3, {"x", "low", "high"}};
static NODE *func__std__sqrt_2;
static void entry__std__sqrt_2(void);
static FRAME_INFO frame__std__sqrt_2 = {4, {"high", "low", "x", "mid"}};
static void cont__std__sqrt_3(void);
static void cont__std__sqrt_4(void);
static void cont__std__sqrt_5(void);
static void cont__std__sqrt_6(void);
static NODE *func__std__sqrt_7;
static void entry__std__sqrt_7(void);
static FRAME_INFO frame__std__sqrt_7 = {2, {"high", "mid"}};
static NODE *func__std__sqrt_8;
static void entry__std__sqrt_8(void);
static FRAME_INFO frame__std__sqrt_8 = {2, {"low", "mid"}};
static void cont__std__sqrt_9(void);
static NODE *get__std__sqrt(void) {
  return var.std__sqrt;
}
static NODE *get__std__PI(void) {
  return var.std__PI;
}
static NODE *func__std__sin_1;
static void entry__std__sin_1(void);
static FRAME_INFO frame__std__sin_1 = {4, {"alpha", "p", "s", "t"}};
static NODE *func__std__sin_2;
static void entry__std__sin_2(void);
static FRAME_INFO frame__std__sin_2 = {4, {"t", "alpha", "p", "s"}};
static void cont__std__sin_3(void);
static void cont__std__sin_4(void);
static void cont__std__sin_5(void);
static void cont__std__sin_6(void);
static void cont__std__sin_7(void);
static void cont__std__sin_8(void);
static void cont__std__sin_9(void);
static void cont__std__sin_10(void);
static void cont__std__sin_11(void);
static void cont__std__sin_12(void);
static void cont__std__sin_13(void);
static NODE *get__std__sin(void) {
  return var.std__sin;
}
static NODE *func__std__cos_1;
static void entry__std__cos_1(void);
static FRAME_INFO frame__std__cos_1 = {4, {"alpha", "p", "s", "t"}};
static NODE *func__std__cos_2;
static void entry__std__cos_2(void);
static FRAME_INFO frame__std__cos_2 = {4, {"p", "t", "alpha", "s"}};
static void cont__std__cos_3(void);
static void cont__std__cos_4(void);
static void cont__std__cos_5(void);
static void cont__std__cos_6(void);
static void cont__std__cos_7(void);
static void cont__std__cos_8(void);
static void cont__std__cos_9(void);
static void cont__std__cos_10(void);
static void cont__std__cos_11(void);
static void cont__std__cos_12(void);
static void cont__std__cos_13(void);
static NODE *get__std__cos(void) {
  return var.std__cos;
}
static NODE *func__std__tan_1;
static void entry__std__tan_1(void);
static FRAME_INFO frame__std__tan_1 = {1, {"alpha"}};
static void cont__std__tan_2(void);
static void cont__std__tan_3(void);
static void cont__std__tan_4(void);
static NODE *get__std__tan(void) {
  return var.std__tan;
}
static NODE *func__std__atan_1;
static void entry__std__atan_1(void);
static FRAME_INFO frame__std__atan_1 = {1, {"x"}};
static void cont__std__atan_2(void);
static NODE *func__std__atan_3;
static void entry__std__atan_3(void);
static FRAME_INFO frame__std__atan_3 = {1, {"x"}};
static void cont__std__atan_4(void);
static NODE *func__std__atan_5;
static void entry__std__atan_5(void);
static FRAME_INFO frame__std__atan_5 = {1, {"x"}};
static void cont__std__atan_6(void);
static void cont__std__atan_7(void);
static void cont__std__atan_8(void);
static NODE *get__std__atan(void) {
  return var.std__atan;
}
static NODE *func__atan2_1;
static void entry__atan2_1(void);
static FRAME_INFO frame__atan2_1 = {1, {"x"}};
static void cont__atan2_2(void);
static NODE *func__atan2_3;
static void entry__atan2_3(void);
static FRAME_INFO frame__atan2_3 = {1, {"x"}};
static void cont__atan2_4(void);
static void cont__atan2_5(void);
static void cont__atan2_6(void);
static void cont__atan2_7(void);
static NODE *func__atan2_8;
static void entry__atan2_8(void);
static FRAME_INFO frame__atan2_8 = {1, {"x"}};
static void cont__atan2_9(void);
static NODE *func__atan3_1;
static void entry__atan3_1(void);
static FRAME_INFO frame__atan3_1 = {1, {"x"}};
static void cont__atan3_2(void);
static void cont__atan3_3(void);
static void cont__atan3_4(void);
static NODE *func__atan3_5;
static void entry__atan3_5(void);
static FRAME_INFO frame__atan3_5 = {1, {"x"}};
static void cont__atan3_6(void);
static void cont__atan3_7(void);
static void cont__atan3_8(void);
static void cont__atan3_9(void);
static void cont__atan3_10(void);
static void cont__atan3_11(void);
static void cont__atan3_12(void);
static void cont__atan3_13(void);
static void cont__atan3_14(void);
static NODE *func__atan3_15;
static void entry__atan3_15(void);
static FRAME_INFO frame__atan3_15 = {1, {"x"}};
static void cont__atan3_16(void);
static NODE *func__atan4_1;
static void entry__atan4_1(void);
static FRAME_INFO frame__atan4_1 = {4, {"x", "sum", "s", "p"}};
static NODE *func__atan4_2;
static void entry__atan4_2(void);
static FRAME_INFO frame__atan4_2 = {5, {"i", "sum", "s", "p", "x"}};
static void cont__atan4_3(void);
static void cont__atan4_4(void);
static void cont__atan4_5(void);
static void cont__atan4_6(void);
static void cont__atan4_7(void);
static void cont__atan4_8(void);
static void cont__atan4_9(void);
void run__basic__math(void);

static CONTINUATION_INFO continuation_info[] = {
  {run__basic__math, NULL, },
  {entry__std__inc_1, NULL, 31, 31, 3, 13},
  {cont__std__inc_2, &frame__std__inc_1, 31, 31, 13, 13},
  {entry__std__dec_1, NULL, 41, 41, 3, 14},
  {cont__std__dec_2, &frame__std__dec_1, 41, 41, 14, 14},
  {entry__std__extend_to_3, NULL, 52, 52, 24, 24},
  {entry__std__extend_to_1, NULL, 52, 52, 6, 14},
  {cont__std__extend_to_2, &frame__std__extend_to_1, 52, 52, 3, 24},
  {cont__std__extend_to_4, &frame__std__extend_to_1, },
  {entry__std__reduce_to_3, NULL, 63, 63, 24, 24},
  {entry__std__reduce_to_1, NULL, 63, 63, 6, 14},
  {cont__std__reduce_to_2, &frame__std__reduce_to_1, 63, 63, 3, 24},
  {cont__std__reduce_to_4, &frame__std__reduce_to_1, },
  {entry__std__abs_3, NULL, 73, 73, 15, 25},
  {cont__std__abs_4, &frame__std__abs_3, 73, 73, 25, 25},
  {entry__std__abs_1, NULL, 73, 73, 6, 12},
  {cont__std__abs_2, &frame__std__abs_1, 73, 73, 3, 25},
  {cont__std__abs_5, &frame__std__abs_1, },
  {entry__std__sgn_4, NULL, 90, 90, 14, 17},
  {entry__std__sgn_2, NULL, 90, 90, 8, 12},
  {cont__std__sgn_3, &frame__std__sgn_2, 90, 90, 5, 17},
  {entry__std__sgn_7, NULL, 91, 91, 18, 18},
  {cont__std__sgn_8, &frame__std__sgn_7, 91, 91, 14, 18},
  {entry__std__sgn_5, NULL, 91, 91, 8, 12},
  {cont__std__sgn_6, &frame__std__sgn_5, 91, 91, 5, 18},
  {entry__std__sgn_10, NULL, 92, 92, 13, 16},
  {entry__std__sgn_9, NULL, 92, 92, 5, 16},
  {entry__std__sgn_1, NULL, 89, 92, 3, 16},
  {entry__std__sqr_1, NULL, 102, 102, 6, 12},
  {cont__std__sqr_2, &frame__std__sqr_1, 102, 102, 3, 12},
  {entry__std__min_6, NULL, 113, 113, 64, 64},
  {entry__std__min_4, NULL, 113, 113, 40, 51},
  {cont__std__min_5, &frame__std__min_4, 113, 113, 37, 64},
  {entry__std__min_1, NULL, 112, 112, 3, 18},
  {cont__std__min_2, &frame__std__min_1, 113, 113, 28, 28},
  {cont__std__min_3, &frame__std__min_1, 113, 113, 3, 64},
  {cont__std__min_7, &frame__std__min_1, 114, 114, 3, 11},
  {entry__std__max_6, NULL, 125, 125, 64, 64},
  {entry__std__max_4, NULL, 125, 125, 40, 51},
  {cont__std__max_5, &frame__std__max_4, 125, 125, 37, 64},
  {entry__std__max_1, NULL, 124, 124, 3, 18},
  {cont__std__max_2, &frame__std__max_1, 125, 125, 28, 28},
  {cont__std__max_3, &frame__std__max_1, 125, 125, 3, 64},
  {cont__std__max_7, &frame__std__max_1, 126, 126, 3, 11},
  {entry__std__pow_4, NULL, 140, 140, 15, 18},
  {entry__std__pow_2, NULL, 140, 140, 8, 13},
  {cont__std__pow_3, &frame__std__pow_2, 140, 140, 5, 18},
  {entry__std__pow_7, NULL, 141, 141, 33, 38},
  {cont__std__pow_8, &frame__std__pow_7, 141, 141, 27, 39},
  {cont__std__pow_9, &frame__std__pow_7, 141, 141, 23, 40},
  {cont__std__pow_10, &frame__std__pow_7, 141, 141, 21, 40},
  {cont__std__pow_11, &frame__std__pow_7, 141, 141, 18, 40},
  {entry__std__pow_5, NULL, 141, 141, 8, 16},
  {cont__std__pow_6, &frame__std__pow_5, 141, 141, 5, 40},
  {entry__std__pow_13, NULL, 142, 142, 26, 31},
  {cont__std__pow_14, &frame__std__pow_13, 142, 142, 20, 32},
  {cont__std__pow_15, &frame__std__pow_13, 142, 142, 16, 33},
  {cont__std__pow_16, &frame__std__pow_13, 142, 142, 13, 33},
  {entry__std__pow_12, NULL, 142, 142, 5, 33},
  {entry__std__pow_1, NULL, 139, 142, 3, 33},
  {entry__std__sqrt_7, NULL, 158, 158, 17, 17},
  {entry__std__sqrt_8, NULL, 160, 160, 16, 16},
  {entry__std__sqrt_2, NULL, 155, 155, 11, 18},
  {cont__std__sqrt_3, &frame__std__sqrt_2, 155, 155, 5, 21},
  {cont__std__sqrt_4, &frame__std__sqrt_2, 157, 157, 7, 14},
  {cont__std__sqrt_5, &frame__std__sqrt_2, 157, 157, 7, 18},
  {cont__std__sqrt_6, &frame__std__sqrt_2, 156, 160, 5, 17},
  {entry__std__sqrt_1, NULL, 154, 160, 3, 18},
  {cont__std__sqrt_9, &frame__std__sqrt_1, 161, 161, 3, 8},
  {entry__std__sin_2, NULL, 179, 179, 9, 9},
  {cont__std__sin_3, &frame__std__sin_2, 179, 179, 9, 15},
  {cont__std__sin_4, &frame__std__sin_2, 179, 179, 9, 21},
  {cont__std__sin_5, &frame__std__sin_2, 179, 179, 24, 26},
  {cont__std__sin_6, &frame__std__sin_2, 179, 179, 29, 31},
  {cont__std__sin_7, &frame__std__sin_2, 179, 179, 29, 33},
  {cont__std__sin_8, &frame__std__sin_2, 179, 179, 24, 33},
  {cont__std__sin_9, &frame__std__sin_2, 179, 179, 5, 35},
  {cont__std__sin_10, &frame__std__sin_2, 180, 180, 5, 13},
  {cont__std__sin_11, &frame__std__sin_2, 181, 181, 5, 10},
  {cont__std__sin_12, &frame__std__sin_2, 181, 181, 10, 10},
  {entry__std__sin_1, NULL, 178, 181, 3, 10},
  {cont__std__sin_13, &frame__std__sin_1, 182, 182, 3, 6},
  {entry__std__cos_2, NULL, 196, 196, 5, 10},
  {cont__std__cos_3, &frame__std__cos_2, 197, 197, 9, 9},
  {cont__std__cos_4, &frame__std__cos_2, 197, 197, 9, 15},
  {cont__std__cos_5, &frame__std__cos_2, 197, 197, 9, 21},
  {cont__std__cos_6, &frame__std__cos_2, 197, 197, 25, 27},
  {cont__std__cos_7, &frame__std__cos_2, 197, 197, 25, 29},
  {cont__std__cos_8, &frame__std__cos_2, 197, 197, 33, 35},
  {cont__std__cos_9, &frame__std__cos_2, 197, 197, 25, 35},
  {cont__std__cos_10, &frame__std__cos_2, 197, 197, 5, 37},
  {cont__std__cos_11, &frame__std__cos_2, 198, 198, 5, 13},
  {cont__std__cos_12, &frame__std__cos_2, 198, 198, 13, 13},
  {entry__std__cos_1, NULL, 195, 198, 3, 13},
  {cont__std__cos_13, &frame__std__cos_1, 199, 199, 3, 6},
  {entry__std__tan_1, NULL, 209, 209, 6, 15},
  {cont__std__tan_2, &frame__std__tan_1, 209, 209, 17, 26},
  {cont__std__tan_3, &frame__std__tan_1, 209, 209, 6, 26},
  {cont__std__tan_4, &frame__std__tan_1, 209, 209, 3, 26},
  {entry__std__atan_3, NULL, 221, 221, 8, 15},
  {cont__std__atan_4, &frame__std__atan_3, 221, 221, 5, 15},
  {entry__std__atan_5, NULL, 222, 222, 16, 16},
  {cont__std__atan_6, &frame__std__atan_5, 222, 222, 9, 17},
  {cont__std__atan_7, &frame__std__atan_5, 222, 222, 9, 17},
  {cont__std__atan_8, &frame__std__atan_5, 222, 222, 5, 17},
  {entry__std__atan_1, NULL, 220, 220, 5, 9},
  {cont__std__atan_2, &frame__std__atan_1, 219, 222, 3, 17},
  {entry__atan2_3, NULL, 227, 227, 8, 11},
  {cont__atan2_4, &frame__atan2_3, 227, 227, 19, 21},
  {cont__atan2_5, &frame__atan2_3, 227, 227, 13, 22},
  {cont__atan2_6, &frame__atan2_3, 227, 227, 8, 22},
  {cont__atan2_7, &frame__atan2_3, 227, 227, 5, 22},
  {entry__atan2_8, NULL, 228, 228, 8, 15},
  {cont__atan2_9, &frame__atan2_8, 228, 228, 5, 15},
  {entry__atan2_1, NULL, 226, 226, 5, 9},
  {cont__atan2_2, &frame__atan2_1, 225, 228, 3, 15},
  {entry__atan3_5, NULL, 233, 233, 8, 11},
  {cont__atan3_6, &frame__atan3_5, 233, 233, 20, 26},
  {cont__atan3_7, &frame__atan3_5, 233, 233, 20, 28},
  {cont__atan3_8, &frame__atan3_5, 233, 233, 20, 30},
  {cont__atan3_9, &frame__atan3_5, 233, 233, 34, 40},
  {cont__atan3_10, &frame__atan3_5, 233, 233, 34, 42},
  {cont__atan3_11, &frame__atan3_5, 233, 233, 20, 42},
  {cont__atan3_12, &frame__atan3_5, 233, 233, 13, 44},
  {cont__atan3_13, &frame__atan3_5, 233, 233, 8, 44},
  {cont__atan3_14, &frame__atan3_5, 233, 233, 5, 44},
  {entry__atan3_15, NULL, 234, 234, 8, 15},
  {cont__atan3_16, &frame__atan3_15, 234, 234, 5, 15},
  {entry__atan3_1, NULL, 232, 232, 11, 17},
  {cont__atan3_2, &frame__atan3_1, 232, 232, 9, 17},
  {cont__atan3_3, &frame__atan3_1, 232, 232, 5, 17},
  {cont__atan3_4, &frame__atan3_1, 231, 234, 3, 15},
  {entry__atan4_2, NULL, 241, 241, 15, 17},
  {cont__atan4_3, &frame__atan4_2, 241, 241, 15, 19},
  {cont__atan4_4, &frame__atan4_2, 241, 241, 5, 19},
  {cont__atan4_5, &frame__atan4_2, 242, 242, 8, 10},
  {cont__atan4_6, &frame__atan4_2, 242, 242, 5, 12},
  {cont__atan4_7, &frame__atan4_2, 243, 243, 5, 9},
  {cont__atan4_8, &frame__atan4_2, 243, 243, 9, 9},
  {entry__atan4_1, NULL, 240, 243, 3, 9},
  {cont__atan4_9, &frame__atan4_1, 244, 244, 3, 8}
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
static void entry__std__inc_1(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // var: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* var */ = create_cell_with_contents(arguments->slots[0]);
  // 31: plus &var 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* var */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__plus();
  func = myself->type;
  frame->cont = cont__std__inc_2;
}
static void cont__std__inc_2(void) {
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
static void entry__std__dec_1(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // var: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* var */ = create_cell_with_contents(arguments->slots[0]);
  // 41: minus &var 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* var */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__minus();
  func = myself->type;
  frame->cont = cont__std__dec_2;
}
static void cont__std__dec_2(void) {
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
static void entry__std__extend_to_1(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // var: 0
  // val: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* var */ = create_cell_with_contents(arguments->slots[0]);
  // 52: ... val > var
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* var */;
  arguments->slots[1] = frame->slots[1] /* val */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__std__extend_to_2;
}
static void cont__std__extend_to_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 52: ... : !var val
  frame->slots[3] /* temp__2 */ = create_closure(entry__std__extend_to_3, 0);
  // 52: if val > var: !var val
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count =
    frame->caller_result_count >= 1 ?
    frame->caller_result_count-1 : -1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__std__extend_to_4;
}
static void entry__std__extend_to_3(void) {
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
  // 52: ... !var val
  ((CELL *)frame->slots[0])->contents /* var */ = frame->slots[1] /* val */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__std__extend_to_4(void) {
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
static void entry__std__reduce_to_1(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // var: 0
  // val: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* var */ = create_cell_with_contents(arguments->slots[0]);
  // 63: ... val < var
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* val */;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* var */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__std__reduce_to_2;
}
static void cont__std__reduce_to_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 63: ... : !var val
  frame->slots[3] /* temp__2 */ = create_closure(entry__std__reduce_to_3, 0);
  // 63: if val < var: !var val
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count =
    frame->caller_result_count >= 1 ?
    frame->caller_result_count-1 : -1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__std__reduce_to_4;
}
static void entry__std__reduce_to_3(void) {
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
  // 63: ... !var val
  ((CELL *)frame->slots[0])->contents /* var */ = frame->slots[1] /* val */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__std__reduce_to_4(void) {
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
static void entry__std__abs_1(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // var: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* var */ = create_cell_with_contents(arguments->slots[0]);
  // 73: ... var < 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* var */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__std__abs_2;
}
static void cont__std__abs_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 73: ... : negate &var
  frame->slots[2] /* temp__2 */ = create_closure(entry__std__abs_3, 0);
  // 73: if var < 0: negate &var
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count =
    frame->caller_result_count >= 1 ?
    frame->caller_result_count-1 : -1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__std__abs_5;
}
static void entry__std__abs_3(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // var: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* var */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 73: ... negate &var
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* var */;
  result_count = 1;
  myself = get__negate();
  func = myself->type;
  frame->cont = cont__std__abs_4;
}
static void cont__std__abs_4(void) {
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
static void cont__std__abs_5(void) {
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
static void entry__std__sgn_10(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 92: ... -> 0
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__0;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__sgn_7(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
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
  frame->cont = cont__std__sgn_8;
}
static void cont__std__sgn_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 91: ... -> -1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__sgn_4(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 90: ... -> 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__sgn_2(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // x: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* x */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 90: ... x > 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = frame->slots[0] /* x */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__std__sgn_3;
}
static void cont__std__sgn_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 90: -> x > 0 -> 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = func__std__sgn_4;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__sgn_5(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // x: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* x */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 91: ... x < 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* x */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__std__sgn_6;
}
static void cont__std__sgn_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 91: -> x < 0 -> -1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = func__std__sgn_7;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__sgn_9(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 92: -> true -> 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__true();
  arguments->slots[1] = func__std__sgn_10;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__sgn_1(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // x: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 90: -> x > 0 -> 1
  frame->slots[1] /* temp__1 */ = create_closure(entry__std__sgn_2, 0);
  // 91: -> x < 0 -> -1
  frame->slots[2] /* temp__2 */ = create_closure(entry__std__sgn_5, 0);
  // 89: cond
  // 90:   -> x > 0 -> 1
  // 91:   -> x < 0 -> -1
  // 92:   -> true -> 0
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  arguments->slots[2] = func__std__sgn_9;
  result_count = frame->caller_result_count;
  myself = get__cond();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__sqr_1(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // var: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 102: ... var*var
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* var */;
  arguments->slots[1] = frame->slots[0] /* var */;
  result_count = 1;
  myself = get__std__times();
  func = myself->type;
  frame->cont = cont__std__sqr_2;
}
static void cont__std__sqr_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 102: -> var*var
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__min_1(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // args: 0
  // result: 1
  frame->slots[1] /* result */ = create_cell();
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 112: $$result args(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* args */;
  func = myself->type;
  frame->cont = cont__std__min_2;
}
static void cont__std__min_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* result */ = arguments->slots[0];
  // 113: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__std__min_3;
}
static void cont__std__min_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 113: ... : (arg) if arg < result: !result arg
  frame->slots[3] /* temp__2 */ = create_closure(entry__std__min_4, 1);
  // 113: for_each_from_to args 2 -1: (arg) if arg < result: !result arg
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* args */;
  arguments->slots[1] = number__2;
  arguments->slots[2] = frame->slots[2] /* temp__1 */;
  arguments->slots[3] = frame->slots[3] /* temp__2 */;
  result_count = 0;
  myself = get__for_each_from_to();
  func = myself->type;
  frame->cont = cont__std__min_7;
}
static void entry__std__min_6(void) {
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
  // 113: ... !result arg
  ((CELL *)frame->slots[0])->contents /* result */ = frame->slots[1] /* arg */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__min_4(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // arg: 0
  // result: 1
  frame->slots[1] = myself->closure.frame->slots[1]; /* result */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 113: ... arg < result
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* arg */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* result */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__std__min_5;
}
static void cont__std__min_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 113: ... : !result arg
  frame->slots[3] /* temp__2 */ = create_closure(entry__std__min_6, 0);
  // 113: ... if arg < result: !result arg
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__std__min_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 114: -> result
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* result */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__max_1(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // args: 0
  // result: 1
  frame->slots[1] /* result */ = create_cell();
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 124: $$result args(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* args */;
  func = myself->type;
  frame->cont = cont__std__max_2;
}
static void cont__std__max_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* result */ = arguments->slots[0];
  // 125: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__std__max_3;
}
static void cont__std__max_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 125: ... : (arg) if arg > result: !result arg
  frame->slots[3] /* temp__2 */ = create_closure(entry__std__max_4, 1);
  // 125: for_each_from_to args 2 -1: (arg) if arg > result: !result arg
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* args */;
  arguments->slots[1] = number__2;
  arguments->slots[2] = frame->slots[2] /* temp__1 */;
  arguments->slots[3] = frame->slots[3] /* temp__2 */;
  result_count = 0;
  myself = get__for_each_from_to();
  func = myself->type;
  frame->cont = cont__std__max_7;
}
static void entry__std__max_6(void) {
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
  // 125: ... !result arg
  ((CELL *)frame->slots[0])->contents /* result */ = frame->slots[1] /* arg */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__max_4(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // arg: 0
  // result: 1
  frame->slots[1] = myself->closure.frame->slots[1]; /* result */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 125: ... arg > result
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* result */;
  arguments->slots[1] = frame->slots[0] /* arg */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__std__max_5;
}
static void cont__std__max_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 125: ... : !result arg
  frame->slots[3] /* temp__2 */ = create_closure(entry__std__max_6, 0);
  // 125: ... if arg > result: !result arg
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__std__max_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 126: -> result
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* result */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__pow_13(void) {
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
  // 142: ... n >> 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* n */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__shift_right();
  func = myself->type;
  frame->cont = cont__std__pow_14;
}
static void cont__std__pow_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 142: ... pow(x n >> 1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* x */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__pow();
  func = myself->type;
  frame->cont = cont__std__pow_15;
}
static void cont__std__pow_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 142: ... sqr(pow(x n >> 1))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__sqr();
  func = myself->type;
  frame->cont = cont__std__pow_16;
}
static void cont__std__pow_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 142: ... -> sqr(pow(x n >> 1))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__pow_7(void) {
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
  // 141: ... n >> 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* n */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__shift_right();
  func = myself->type;
  frame->cont = cont__std__pow_8;
}
static void cont__std__pow_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__4 */ = arguments->slots[0];
  // 141: ... pow(x n >> 1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* x */;
  arguments->slots[1] = frame->slots[5] /* temp__4 */;
  result_count = 1;
  myself = get__pow();
  func = myself->type;
  frame->cont = cont__std__pow_9;
}
static void cont__std__pow_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 141: ... sqr(pow(x n >> 1))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__sqr();
  func = myself->type;
  frame->cont = cont__std__pow_10;
}
static void cont__std__pow_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 141: ... x*sqr(pow(x n >> 1))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* x */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__times();
  func = myself->type;
  frame->cont = cont__std__pow_11;
}
static void cont__std__pow_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 141: ... -> x*sqr(pow(x n >> 1))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__pow_4(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 140: ... -> 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__pow_2(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // n: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* n */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 140: ... n == 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* n */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__std__pow_3;
}
static void cont__std__pow_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 140: -> n == 0 -> 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = func__std__pow_4;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__pow_5(void) {
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
  // 141: ... is_odd(n)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* n */;
  result_count = 1;
  myself = get__is_odd();
  func = myself->type;
  frame->cont = cont__std__pow_6;
}
static void cont__std__pow_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 141: ... -> x*sqr(pow(x n >> 1))
  frame->slots[3] /* temp__2 */ = create_closure(entry__std__pow_7, 0);
  // 141: -> is_odd(n) -> x*sqr(pow(x n >> 1))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__pow_12(void) {
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
  // 142: ... -> sqr(pow(x n >> 1))
  frame->slots[2] /* temp__1 */ = create_closure(entry__std__pow_13, 0);
  // 142: -> true -> sqr(pow(x n >> 1))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__true();
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__pow_1(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // x: 0
  // n: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 140: -> n == 0 -> 1
  frame->slots[2] /* temp__1 */ = create_closure(entry__std__pow_2, 0);
  // 141: -> is_odd(n) -> x*sqr(pow(x n >> 1))
  frame->slots[3] /* temp__2 */ = create_closure(entry__std__pow_5, 0);
  // 142: -> true -> sqr(pow(x n >> 1))
  frame->slots[4] /* temp__3 */ = create_closure(entry__std__pow_12, 0);
  // 139: cond
  // 140:   -> n == 0 -> 1
  // 141:   -> is_odd(n) -> x*sqr(pow(x n >> 1))
  // 142:   -> true -> sqr(pow(x n >> 1))
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
static void entry__std__sqrt_1(void) {
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
  // 152: $$low 0
  ((CELL *)frame->slots[1])->contents /* low */ = number__0;
  // 153: $$high x
  ((CELL *)frame->slots[2])->contents /* high */ = frame->slots[0] /* x */;
  // 154: ... :
  // 155:   $mid (high+low)/2
  // 156:   if
  // 157:     sqr(mid) > x:
  // 158:       !high mid
  // 159:     :
  // 160:       !low mid
  frame->slots[3] /* temp__1 */ = create_closure(entry__std__sqrt_2, 0);
  // 154: repeat 50:
  // 155:   $mid (high+low)/2
  // 156:   if
  // 157:     sqr(mid) > x:
  // 158:       !high mid
  // 159:     :
  // 160:       !low mid
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__50;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 0;
  myself = get__repeat();
  func = myself->type;
  frame->cont = cont__std__sqrt_9;
}
static void entry__std__sqrt_7(void) {
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
  // 158: !high mid
  ((CELL *)frame->slots[0])->contents /* high */ = frame->slots[1] /* mid */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__sqrt_8(void) {
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
  // 160: !low mid
  ((CELL *)frame->slots[0])->contents /* low */ = frame->slots[1] /* mid */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__sqrt_2(void) {
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
  // 155: ... high+low
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* high */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* low */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__std__sqrt_3;
}
static void cont__std__sqrt_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 155: $mid (high+low)/2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__std__over();
  func = myself->type;
  frame->cont = cont__std__sqrt_4;
}
static void cont__std__sqrt_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* mid */, arguments->slots[0]);
  // 157: sqr(mid)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* mid */;
  result_count = 1;
  myself = get__sqr();
  func = myself->type;
  frame->cont = cont__std__sqrt_5;
}
static void cont__std__sqrt_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 157: sqr(mid) > x
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* x */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__std__sqrt_6;
}
static void cont__std__sqrt_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 157: ... :
  // 158:   !high mid
  frame->slots[6] /* temp__3 */ = create_closure(entry__std__sqrt_7, 0);
  // 159: :
  // 160:   !low mid
  frame->slots[7] /* temp__4 */ = create_closure(entry__std__sqrt_8, 0);
  // 156: if
  // 157:   sqr(mid) > x:
  // 158:     !high mid
  // 159:   :
  // 160:     !low mid
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
static void cont__std__sqrt_9(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 161: -> low
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* low */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__sin_1(void) {
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
  // 175: $$p 1
  ((CELL *)frame->slots[1])->contents /* p */ = number__1;
  // 176: $$s alpha
  ((CELL *)frame->slots[2])->contents /* s */ = frame->slots[0] /* alpha */;
  // 177: $$t alpha
  ((CELL *)frame->slots[3])->contents /* t */ = frame->slots[0] /* alpha */;
  // 178: ... :
  // 179:   !t -t*alpha*alpha/(2*p*(2*p+1))
  // 180:   plus &s t
  // 181:   inc &p
  frame->slots[4] /* temp__1 */ = create_closure(entry__std__sin_2, 0);
  // 178: repeat 13:
  // 179:   !t -t*alpha*alpha/(2*p*(2*p+1))
  // 180:   plus &s t
  // 181:   inc &p
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__13;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__repeat();
  func = myself->type;
  frame->cont = cont__std__sin_13;
}
static void entry__std__sin_2(void) {
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
  // 179: ... t
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* t */;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__std__sin_3;
}
static void cont__std__sin_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 179: ... t*alpha
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__3 */;
  arguments->slots[1] = frame->slots[1] /* alpha */;
  result_count = 1;
  myself = get__std__times();
  func = myself->type;
  frame->cont = cont__std__sin_4;
}
static void cont__std__sin_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 179: ... t*alpha*alpha
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  arguments->slots[1] = frame->slots[1] /* alpha */;
  result_count = 1;
  myself = get__std__times();
  func = myself->type;
  frame->cont = cont__std__sin_5;
}
static void cont__std__sin_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 179: ... 2*p
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__2;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* p */;
  result_count = 1;
  myself = get__std__times();
  func = myself->type;
  frame->cont = cont__std__sin_6;
}
static void cont__std__sin_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__5 */ = arguments->slots[0];
  // 179: ... 2*p
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__2;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* p */;
  result_count = 1;
  myself = get__std__times();
  func = myself->type;
  frame->cont = cont__std__sin_7;
}
static void cont__std__sin_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__7 */ = arguments->slots[0];
  // 179: ... 2*p+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__7 */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__std__sin_8;
}
static void cont__std__sin_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__6 */ = arguments->slots[0];
  // 179: ... 2*p*(2*p+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__5 */;
  arguments->slots[1] = frame->slots[9] /* temp__6 */;
  result_count = 1;
  myself = get__std__times();
  func = myself->type;
  frame->cont = cont__std__sin_9;
}
static void cont__std__sin_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__4 */ = arguments->slots[0];
  // 179: !t -t*alpha*alpha/(2*p*(2*p+1))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__4 */;
  result_count = 1;
  myself = get__std__over();
  func = myself->type;
  frame->cont = cont__std__sin_10;
}
static void cont__std__sin_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* t */ = arguments->slots[0];
  // 180: plus &s t
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* s */;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* t */;
  result_count = 1;
  myself = get__plus();
  func = myself->type;
  frame->cont = cont__std__sin_11;
}
static void cont__std__sin_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* s */ = arguments->slots[0];
  // 181: inc &p
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* p */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__std__sin_12;
}
static void cont__std__sin_12(void) {
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
static void cont__std__sin_13(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 182: -> s
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* s */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__cos_1(void) {
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
  // 192: $$p 0
  ((CELL *)frame->slots[1])->contents /* p */ = number__0;
  // 193: $$s 1
  ((CELL *)frame->slots[2])->contents /* s */ = number__1;
  // 194: $$t 1
  ((CELL *)frame->slots[3])->contents /* t */ = number__1;
  // 195: ... :
  // 196:   inc &p
  // 197:   !t -t*alpha*alpha/((2*p-1)*(2*p))
  // 198:   plus &s t
  frame->slots[4] /* temp__1 */ = create_closure(entry__std__cos_2, 0);
  // 195: repeat 13:
  // 196:   inc &p
  // 197:   !t -t*alpha*alpha/((2*p-1)*(2*p))
  // 198:   plus &s t
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__13;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__repeat();
  func = myself->type;
  frame->cont = cont__std__cos_13;
}
static void entry__std__cos_2(void) {
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
  // 196: inc &p
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* p */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__std__cos_3;
}
static void cont__std__cos_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* p */ = arguments->slots[0];
  // 197: ... t
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* t */;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__std__cos_4;
}
static void cont__std__cos_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 197: ... t*alpha
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__3 */;
  arguments->slots[1] = frame->slots[2] /* alpha */;
  result_count = 1;
  myself = get__std__times();
  func = myself->type;
  frame->cont = cont__std__cos_5;
}
static void cont__std__cos_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 197: ... t*alpha*alpha
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  arguments->slots[1] = frame->slots[2] /* alpha */;
  result_count = 1;
  myself = get__std__times();
  func = myself->type;
  frame->cont = cont__std__cos_6;
}
static void cont__std__cos_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 197: ... 2*p
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__2;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* p */;
  result_count = 1;
  myself = get__std__times();
  func = myself->type;
  frame->cont = cont__std__cos_7;
}
static void cont__std__cos_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__6 */ = arguments->slots[0];
  // 197: ... 2*p-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__6 */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__std__cos_8;
}
static void cont__std__cos_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__5 */ = arguments->slots[0];
  // 197: ... 2*p
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__2;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* p */;
  result_count = 1;
  myself = get__std__times();
  func = myself->type;
  frame->cont = cont__std__cos_9;
}
static void cont__std__cos_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__7 */ = arguments->slots[0];
  // 197: ... 2*p-1)*(2*p
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__5 */;
  arguments->slots[1] = frame->slots[10] /* temp__7 */;
  result_count = 1;
  myself = get__std__times();
  func = myself->type;
  frame->cont = cont__std__cos_10;
}
static void cont__std__cos_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__4 */ = arguments->slots[0];
  // 197: !t -t*alpha*alpha/((2*p-1)*(2*p))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__4 */;
  result_count = 1;
  myself = get__std__over();
  func = myself->type;
  frame->cont = cont__std__cos_11;
}
static void cont__std__cos_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* t */ = arguments->slots[0];
  // 198: plus &s t
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* s */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* t */;
  result_count = 1;
  myself = get__plus();
  func = myself->type;
  frame->cont = cont__std__cos_12;
}
static void cont__std__cos_12(void) {
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
static void cont__std__cos_13(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 199: -> s
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* s */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__tan_1(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // alpha: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 209: ... sin(alpha)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* alpha */;
  result_count = 1;
  myself = get__sin();
  func = myself->type;
  frame->cont = cont__std__tan_2;
}
static void cont__std__tan_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 209: ... cos(alpha)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* alpha */;
  result_count = 1;
  myself = get__cos();
  func = myself->type;
  frame->cont = cont__std__tan_3;
}
static void cont__std__tan_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 209: ... sin(alpha)/cos(alpha)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__over();
  func = myself->type;
  frame->cont = cont__std__tan_4;
}
static void cont__std__tan_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 209: -> sin(alpha)/cos(alpha)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__atan_3(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // x: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* x */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 221: ... atan2(x)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* x */;
  result_count = 1;
  myself = var._atan2;
  func = myself->type;
  frame->cont = cont__std__atan_4;
}
static void cont__std__atan_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 221: -> atan2(x)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__atan_5(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // x: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* x */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 222: ... x
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* x */;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__std__atan_6;
}
static void cont__std__atan_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 222: ... atan2(-x)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = var._atan2;
  func = myself->type;
  frame->cont = cont__std__atan_7;
}
static void cont__std__atan_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 222: ... atan2(-x)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__std__atan_8;
}
static void cont__std__atan_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 222: -> -atan2(-x)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__atan_1(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // x: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 220: x > 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = frame->slots[0] /* x */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__std__atan_2;
}
static void cont__std__atan_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 221: -> atan2(x)
  frame->slots[2] /* temp__2 */ = create_closure(entry__std__atan_3, 0);
  // 222: -> -atan2(-x)
  frame->slots[3] /* temp__3 */ = create_closure(entry__std__atan_5, 0);
  // 219: if
  // 220:   x > 0
  // 221:   -> atan2(x)
  // 222:   -> -atan2(-x)
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
static void entry__atan2_3(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // x: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* x */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 227: ... PI/2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__PI();
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__std__over();
  func = myself->type;
  frame->cont = cont__atan2_4;
}
static void cont__atan2_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 227: ... 1/x
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__1;
  arguments->slots[1] = frame->slots[0] /* x */;
  result_count = 1;
  myself = get__std__over();
  func = myself->type;
  frame->cont = cont__atan2_5;
}
static void cont__atan2_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__4 */ = arguments->slots[0];
  // 227: ... atan3(1/x)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__4 */;
  result_count = 1;
  myself = var._atan3;
  func = myself->type;
  frame->cont = cont__atan2_6;
}
static void cont__atan2_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 227: ... PI/2-atan3(1/x)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__atan2_7;
}
static void cont__atan2_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 227: -> PI/2-atan3(1/x)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__atan2_8(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // x: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* x */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 228: ... atan3(x)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* x */;
  result_count = 1;
  myself = var._atan3;
  func = myself->type;
  frame->cont = cont__atan2_9;
}
static void cont__atan2_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 228: -> atan3(x)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__atan2_1(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // x: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 226: x > 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__1;
  arguments->slots[1] = frame->slots[0] /* x */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__atan2_2;
}
static void cont__atan2_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 227: -> PI/2-atan3(1/x)
  frame->slots[2] /* temp__2 */ = create_closure(entry__atan2_3, 0);
  // 228: -> atan3(x)
  frame->slots[3] /* temp__3 */ = create_closure(entry__atan2_8, 0);
  // 225: if
  // 226:   x > 1
  // 227:   -> PI/2-atan3(1/x)
  // 228:   -> atan3(x)
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
static void entry__atan3_5(void) {
  allocate_initialized_frame_gc(1, 10);
  // slot allocations:
  // x: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* x */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 233: ... PI/6
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__PI();
  arguments->slots[1] = number__6;
  result_count = 1;
  myself = get__std__over();
  func = myself->type;
  frame->cont = cont__atan3_6;
}
static void cont__atan3_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 233: ... sqrt(3)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__3;
  result_count = 1;
  myself = get__sqrt();
  func = myself->type;
  frame->cont = cont__atan3_7;
}
static void cont__atan3_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__7 */ = arguments->slots[0];
  // 233: ... sqrt(3)*x
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__7 */;
  arguments->slots[1] = frame->slots[0] /* x */;
  result_count = 1;
  myself = get__std__times();
  func = myself->type;
  frame->cont = cont__atan3_8;
}
static void cont__atan3_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__6 */ = arguments->slots[0];
  // 233: ... sqrt(3)*x-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__6 */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__atan3_9;
}
static void cont__atan3_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__5 */ = arguments->slots[0];
  // 233: ... sqrt(3)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__3;
  result_count = 1;
  myself = get__sqrt();
  func = myself->type;
  frame->cont = cont__atan3_10;
}
static void cont__atan3_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__9 */ = arguments->slots[0];
  // 233: ... sqrt(3)+x
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__9 */;
  arguments->slots[1] = frame->slots[0] /* x */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__atan3_11;
}
static void cont__atan3_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__8 */ = arguments->slots[0];
  // 233: ... sqrt(3)*x-1)/(sqrt(3)+x
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__5 */;
  arguments->slots[1] = frame->slots[8] /* temp__8 */;
  result_count = 1;
  myself = get__std__over();
  func = myself->type;
  frame->cont = cont__atan3_12;
}
static void cont__atan3_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__4 */ = arguments->slots[0];
  // 233: ... atan4((sqrt(3)*x-1)/(sqrt(3)+x))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__4 */;
  result_count = 1;
  myself = var._atan4;
  func = myself->type;
  frame->cont = cont__atan3_13;
}
static void cont__atan3_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 233: ... PI/6+atan4((sqrt(3)*x-1)/(sqrt(3)+x))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__atan3_14;
}
static void cont__atan3_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 233: -> PI/6+atan4((sqrt(3)*x-1)/(sqrt(3)+x))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__atan3_15(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // x: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* x */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 234: ... atan4(x)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* x */;
  result_count = 1;
  myself = var._atan4;
  func = myself->type;
  frame->cont = cont__atan3_16;
}
static void cont__atan3_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 234: -> atan4(x)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__atan3_1(void) {
  allocate_initialized_frame_gc(1, 6);
  // slot allocations:
  // x: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 232: ... sqrt(3)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__3;
  result_count = 1;
  myself = get__sqrt();
  func = myself->type;
  frame->cont = cont__atan3_2;
}
static void cont__atan3_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 232: ... 2-sqrt(3)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__2;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__atan3_3;
}
static void cont__atan3_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 232: x > 2-sqrt(3)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[0] /* x */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__atan3_4;
}
static void cont__atan3_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 233: -> PI/6+atan4((sqrt(3)*x-1)/(sqrt(3)+x))
  frame->slots[4] /* temp__4 */ = create_closure(entry__atan3_5, 0);
  // 234: -> atan4(x)
  frame->slots[5] /* temp__5 */ = create_closure(entry__atan3_15, 0);
  // 231: if
  // 232:   x > 2-sqrt(3)
  // 233:   -> PI/6+atan4((sqrt(3)*x-1)/(sqrt(3)+x))
  // 234:   -> atan4(x)
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
static void entry__atan4_1(void) {
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
  // 237: $$sum 0
  ((CELL *)frame->slots[1])->contents /* sum */ = number__0;
  // 238: $$s 1
  ((CELL *)frame->slots[2])->contents /* s */ = number__1;
  // 239: $$p x
  ((CELL *)frame->slots[3])->contents /* p */ = frame->slots[0] /* x */;
  // 240: ... : (i)
  // 241:   plus &sum s*p/i
  // 242:   !p p*x*x
  // 243:   !s -s
  frame->slots[4] /* temp__1 */ = create_closure(entry__atan4_2, 1);
  // 240: from_to_by 1 23 2: (i)
  // 241:   plus &sum s*p/i
  // 242:   !p p*x*x
  // 243:   !s -s
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = number__1;
  arguments->slots[1] = number__23;
  arguments->slots[2] = number__2;
  arguments->slots[3] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__from_to_by();
  func = myself->type;
  frame->cont = cont__atan4_9;
}
static void entry__atan4_2(void) {
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
  // 241: ... s*p
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* s */;
  arguments->slots[1] = ((CELL *)frame->slots[3])->contents /* p */;
  result_count = 1;
  myself = get__std__times();
  func = myself->type;
  frame->cont = cont__atan4_3;
}
static void cont__atan4_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 241: ... s*p/i
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[0] /* i */;
  result_count = 1;
  myself = get__std__over();
  func = myself->type;
  frame->cont = cont__atan4_4;
}
static void cont__atan4_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 241: plus &sum s*p/i
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* sum */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 1;
  myself = get__plus();
  func = myself->type;
  frame->cont = cont__atan4_5;
}
static void cont__atan4_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* sum */ = arguments->slots[0];
  // 242: ... p*x
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* p */;
  arguments->slots[1] = frame->slots[4] /* x */;
  result_count = 1;
  myself = get__std__times();
  func = myself->type;
  frame->cont = cont__atan4_6;
}
static void cont__atan4_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 242: !p p*x*x
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* x */;
  result_count = 1;
  myself = get__std__times();
  func = myself->type;
  frame->cont = cont__atan4_7;
}
static void cont__atan4_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* p */ = arguments->slots[0];
  // 243: !s -s
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* s */;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__atan4_8;
}
static void cont__atan4_8(void) {
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
static void cont__atan4_9(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 244: -> sum
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
  set_module("basic__math");
  number__50 = from_uint32(50U);
  number__6 = from_uint32(6U);
  number__3_1415926535897932 = from_double(3.1415926535897932);
  number__0 = from_uint32(0U);
  number__3 = from_uint32(3U);
  number__13 = from_uint32(13U);
  number__23 = from_uint32(23U);
  number__1 = from_uint32(1U);
  number__2 = from_uint32(2U);
  func__std__inc_1 = create_function(entry__std__inc_1, 1);
  func__std__dec_1 = create_function(entry__std__dec_1, 1);
  func__std__extend_to_1 = create_function(entry__std__extend_to_1, 2);
  func__std__reduce_to_1 = create_function(entry__std__reduce_to_1, 2);
  func__std__abs_1 = create_function(entry__std__abs_1, 1);
  func__std__sgn_4 = create_function(entry__std__sgn_4, 0);
  func__std__sgn_7 = create_function(entry__std__sgn_7, 0);
  func__std__sgn_10 = create_function(entry__std__sgn_10, 0);
  func__std__sgn_9 = create_function(entry__std__sgn_9, 0);
  func__std__sgn_1 = create_function(entry__std__sgn_1, 1);
  func__std__sqr_1 = create_function(entry__std__sqr_1, 1);
  func__std__min_1 = create_function(entry__std__min_1, -1);
  func__std__max_1 = create_function(entry__std__max_1, -1);
  func__std__pow_4 = create_function(entry__std__pow_4, 0);
  func__std__pow_1 = create_function(entry__std__pow_1, 2);
  func__std__sqrt_1 = create_function(entry__std__sqrt_1, 1);
  func__std__sin_1 = create_function(entry__std__sin_1, 1);
  func__std__cos_1 = create_function(entry__std__cos_1, 1);
  func__std__tan_1 = create_function(entry__std__tan_1, 1);
  func__std__atan_1 = create_function(entry__std__atan_1, 1);
  func__atan2_1 = create_function(entry__atan2_1, 1);
  func__atan3_1 = create_function(entry__atan3_1, 1);
  func__atan4_1 = create_function(entry__atan4_1, 1);
}

static int already_run_phase_3 = false;

EXPORT void phase_3__basic__math(void) {
  if (already_run_phase_3) return;
  already_run_phase_3 = true;
  set_module("basic__math");
  set_used_namespaces(used_namespaces);
  var.std__inc = create_future();
  define_single_assign_static("std", "inc", get__std__inc, &var.std__inc);
  var.std__dec = create_future();
  define_single_assign_static("std", "dec", get__std__dec, &var.std__dec);
  var.std__extend_to = create_future();
  define_single_assign_static("std", "extend_to", get__std__extend_to, &var.std__extend_to);
  var.std__reduce_to = create_future();
  define_single_assign_static("std", "reduce_to", get__std__reduce_to, &var.std__reduce_to);
  var.std__abs = create_future();
  define_single_assign_static("std", "abs", get__std__abs, &var.std__abs);
  var.std__sgn = create_future();
  define_single_assign_static("std", "sgn", get__std__sgn, &var.std__sgn);
  var.std__sqr = create_future();
  define_single_assign_static("std", "sqr", get__std__sqr, &var.std__sqr);
  var.std__min = create_future();
  define_single_assign_static("std", "min", get__std__min, &var.std__min);
  var.std__max = create_future();
  define_single_assign_static("std", "max", get__std__max, &var.std__max);
  var.std__pow = create_future();
  define_single_assign_static("std", "pow", get__std__pow, &var.std__pow);
  var.std__sqrt = create_future();
  define_single_assign_static("std", "sqrt", get__std__sqrt, &var.std__sqrt);
  var.std__PI = create_future();
  define_single_assign_static("std", "PI", get__std__PI, &var.std__PI);
  var.std__sin = create_future();
  define_single_assign_static("std", "sin", get__std__sin, &var.std__sin);
  var.std__cos = create_future();
  define_single_assign_static("std", "cos", get__std__cos, &var.std__cos);
  var.std__tan = create_future();
  define_single_assign_static("std", "tan", get__std__tan, &var.std__tan);
  var.std__atan = create_future();
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
  initialize_future(var.std__inc, func__std__inc_1);
  initialize_future(var.std__dec, func__std__dec_1);
  initialize_future(var.std__extend_to, func__std__extend_to_1);
  initialize_future(var.std__reduce_to, func__std__reduce_to_1);
  initialize_future(var.std__abs, func__std__abs_1);
  initialize_future(var.std__sgn, func__std__sgn_1);
  initialize_future(var.std__sqr, func__std__sqr_1);
  initialize_future(var.std__min, func__std__min_1);
  initialize_future(var.std__max, func__std__max_1);
  initialize_future(var.std__pow, func__std__pow_1);
  initialize_future(var.std__sqrt, func__std__sqrt_1);
  initialize_future(var.std__PI, number__3_1415926535897932);
  initialize_future(var.std__sin, func__std__sin_1);
  initialize_future(var.std__cos, func__std__cos_1);
  initialize_future(var.std__tan, func__std__tan_1);
  initialize_future(var.std__atan, func__std__atan_1);
  assign_variable(&var._atan2, &func__atan2_1);
  assign_variable(&var._atan3, &func__atan3_1);
  assign_variable(&var._atan4, &func__atan4_1);
}

static int already_run_phase_6 = false;

EXPORT void phase_6__basic__math(void) {
  if (already_run_phase_6) return;
  already_run_phase_6 = true;
  register_collector(collect__basic__math);
}
