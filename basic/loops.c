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
IMPORT void set_module(const char *name);
IMPORT NODE *from_uint32(uint32_t val);
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
static NODE *func__std__from_to_1;
static void entry__std__from_to_1(void);
static FRAME_INFO frame__std__from_to_1 = {4, {"first", "last", "body", "body2"}};
static void cont__std__from_to_2(void);
static NODE *func__std__from_to_3;
static void entry__std__from_to_3(void);
static FRAME_INFO frame__std__from_to_3 = {4, {"last", "first", "body", "body2"}};
static void cont__std__from_to_4(void);
static void cont__std__from_to_5(void);
static NODE *func__std__from_to_6;
static void entry__std__from_to_6(void);
static FRAME_INFO frame__std__from_to_6 = {2, {"body", "first"}};
static void cont__std__from_to_7(void);
static void cont__std__from_to_8(void);
static NODE *func__std__from_to_9;
static void entry__std__from_to_9(void);
static FRAME_INFO frame__std__from_to_9 = {3, {"first", "last", "body"}};
static NODE *get__std__from_to(void) {
  return var.std__from_to;
}
static NODE *func__from_to_1_1;
static void entry__from_to_1_1(void);
static FRAME_INFO frame__from_to_1_1 = {3, {"s", "e", "body"}};
static void cont__from_to_1_2(void);
static void cont__from_to_1_3(void);
static NODE *func__from_to_1_4;
static void entry__from_to_1_4(void);
static FRAME_INFO frame__from_to_1_4 = {3, {"body", "s", "e"}};
static void cont__from_to_1_5(void);
static void cont__from_to_1_6(void);
static NODE *func__from_to_2_1;
static void entry__from_to_2_1(void);
static FRAME_INFO frame__from_to_2_1 = {4, {"s", "e", "body", "body2"}};
static void cont__from_to_2_2(void);
static void cont__from_to_2_3(void);
static NODE *func__from_to_2_4;
static void entry__from_to_2_4(void);
static FRAME_INFO frame__from_to_2_4 = {4, {"body2", "body", "s", "e"}};
static void cont__from_to_2_5(void);
static void cont__from_to_2_6(void);
static void cont__from_to_2_7(void);
static NODE *func__std__from_to_by_1;
static void entry__std__from_to_by_1(void);
static FRAME_INFO frame__std__from_to_by_1 = {5, {"first", "last", "step", "body", "body2"}};
static void cont__std__from_to_by_2(void);
static NODE *func__std__from_to_by_3;
static void entry__std__from_to_by_3(void);
static FRAME_INFO frame__std__from_to_by_3 = {5, {"last", "first", "body", "step", "body2"}};
static void cont__std__from_to_by_4(void);
static void cont__std__from_to_by_5(void);
static NODE *func__std__from_to_by_6;
static void entry__std__from_to_by_6(void);
static FRAME_INFO frame__std__from_to_by_6 = {2, {"body", "first"}};
static void cont__std__from_to_by_7(void);
static void cont__std__from_to_by_8(void);
static NODE *func__std__from_to_by_9;
static void entry__std__from_to_by_9(void);
static FRAME_INFO frame__std__from_to_by_9 = {4, {"first", "last", "step", "body"}};
static NODE *get__std__from_to_by(void) {
  return var.std__from_to_by;
}
static NODE *func__from_to_by_1_1;
static void entry__from_to_by_1_1(void);
static FRAME_INFO frame__from_to_by_1_1 = {4, {"s", "e", "step", "body"}};
static void cont__from_to_by_1_2(void);
static void cont__from_to_by_1_3(void);
static NODE *func__from_to_by_1_4;
static void entry__from_to_by_1_4(void);
static FRAME_INFO frame__from_to_by_1_4 = {4, {"body", "s", "step", "e"}};
static void cont__from_to_by_1_5(void);
static void cont__from_to_by_1_6(void);
static NODE *func__from_to_by_2_1;
static void entry__from_to_by_2_1(void);
static FRAME_INFO frame__from_to_by_2_1 = {5, {"s", "e", "step", "body", "body2"}};
static void cont__from_to_by_2_2(void);
static void cont__from_to_by_2_3(void);
static NODE *func__from_to_by_2_4;
static void entry__from_to_by_2_4(void);
static FRAME_INFO frame__from_to_by_2_4 = {5, {"body2", "body", "s", "step", "e"}};
static void cont__from_to_by_2_5(void);
static void cont__from_to_by_2_6(void);
static void cont__from_to_by_2_7(void);
static NODE *func__std__from_down_to_1;
static void entry__std__from_down_to_1(void);
static FRAME_INFO frame__std__from_down_to_1 = {4, {"first", "last", "body", "body2"}};
static void cont__std__from_down_to_2(void);
static NODE *func__std__from_down_to_3;
static void entry__std__from_down_to_3(void);
static FRAME_INFO frame__std__from_down_to_3 = {4, {"first", "last", "body", "body2"}};
static void cont__std__from_down_to_4(void);
static void cont__std__from_down_to_5(void);
static NODE *func__std__from_down_to_6;
static void entry__std__from_down_to_6(void);
static FRAME_INFO frame__std__from_down_to_6 = {2, {"body", "first"}};
static void cont__std__from_down_to_7(void);
static void cont__std__from_down_to_8(void);
static NODE *func__std__from_down_to_9;
static void entry__std__from_down_to_9(void);
static FRAME_INFO frame__std__from_down_to_9 = {3, {"first", "last", "body"}};
static NODE *get__std__from_down_to(void) {
  return var.std__from_down_to;
}
static NODE *func__from_down_to_1_1;
static void entry__from_down_to_1_1(void);
static FRAME_INFO frame__from_down_to_1_1 = {3, {"s", "e", "body"}};
static void cont__from_down_to_1_2(void);
static void cont__from_down_to_1_3(void);
static NODE *func__from_down_to_1_4;
static void entry__from_down_to_1_4(void);
static FRAME_INFO frame__from_down_to_1_4 = {3, {"body", "s", "e"}};
static void cont__from_down_to_1_5(void);
static void cont__from_down_to_1_6(void);
static NODE *func__from_down_to_2_1;
static void entry__from_down_to_2_1(void);
static FRAME_INFO frame__from_down_to_2_1 = {4, {"s", "e", "body", "body2"}};
static void cont__from_down_to_2_2(void);
static void cont__from_down_to_2_3(void);
static NODE *func__from_down_to_2_4;
static void entry__from_down_to_2_4(void);
static FRAME_INFO frame__from_down_to_2_4 = {4, {"body2", "body", "s", "e"}};
static void cont__from_down_to_2_5(void);
static void cont__from_down_to_2_6(void);
static void cont__from_down_to_2_7(void);
static NODE *func__std__from_down_to_by_1;
static void entry__std__from_down_to_by_1(void);
static FRAME_INFO frame__std__from_down_to_by_1 = {5, {"first", "last", "step", "body", "body2"}};
static void cont__std__from_down_to_by_2(void);
static NODE *func__std__from_down_to_by_3;
static void entry__std__from_down_to_by_3(void);
static FRAME_INFO frame__std__from_down_to_by_3 = {5, {"first", "last", "body", "step", "body2"}};
static void cont__std__from_down_to_by_4(void);
static void cont__std__from_down_to_by_5(void);
static NODE *func__std__from_down_to_by_6;
static void entry__std__from_down_to_by_6(void);
static FRAME_INFO frame__std__from_down_to_by_6 = {2, {"body", "first"}};
static void cont__std__from_down_to_by_7(void);
static void cont__std__from_down_to_by_8(void);
static NODE *func__std__from_down_to_by_9;
static void entry__std__from_down_to_by_9(void);
static FRAME_INFO frame__std__from_down_to_by_9 = {4, {"first", "last", "step", "body"}};
static NODE *get__std__from_down_to_by(void) {
  return var.std__from_down_to_by;
}
static NODE *func__from_down_to_by_1_1;
static void entry__from_down_to_by_1_1(void);
static FRAME_INFO frame__from_down_to_by_1_1 = {4, {"s", "e", "step", "body"}};
static void cont__from_down_to_by_1_2(void);
static void cont__from_down_to_by_1_3(void);
static NODE *func__from_down_to_by_1_4;
static void entry__from_down_to_by_1_4(void);
static FRAME_INFO frame__from_down_to_by_1_4 = {4, {"body", "s", "step", "e"}};
static void cont__from_down_to_by_1_5(void);
static void cont__from_down_to_by_1_6(void);
static NODE *func__from_down_to_by_2_1;
static void entry__from_down_to_by_2_1(void);
static FRAME_INFO frame__from_down_to_by_2_1 = {5, {"s", "e", "step", "body", "body2"}};
static void cont__from_down_to_by_2_2(void);
static void cont__from_down_to_by_2_3(void);
static NODE *func__from_down_to_by_2_4;
static void entry__from_down_to_by_2_4(void);
static FRAME_INFO frame__from_down_to_by_2_4 = {5, {"body2", "body", "s", "step", "e"}};
static void cont__from_down_to_by_2_5(void);
static void cont__from_down_to_by_2_6(void);
static void cont__from_down_to_by_2_7(void);
static NODE *func__std__repeat_1;
static void entry__std__repeat_1(void);
static FRAME_INFO frame__std__repeat_1 = {2, {"n", "body"}};
static void cont__std__repeat_2(void);
static void cont__std__repeat_3(void);
static NODE *func__std__repeat_4;
static void entry__std__repeat_4(void);
static FRAME_INFO frame__std__repeat_4 = {2, {"body", "n"}};
static void cont__std__repeat_5(void);
static void cont__std__repeat_6(void);
static NODE *get__std__repeat(void) {
  return var.std__repeat;
}
static NODE *func__std__forever_1;
static void entry__std__forever_1(void);
static FRAME_INFO frame__std__forever_1 = {1, {"body"}};
static void cont__std__forever_2(void);
static NODE *get__std__forever(void) {
  return var.std__forever;
}
static NODE *func__std__while_1;
static void entry__std__while_1(void);
static FRAME_INFO frame__std__while_1 = {3, {"cond_and_body", "cond", "body"}};
static void cont__std__while_2(void);
static NODE *func__std__while_3;
static void entry__std__while_3(void);
static FRAME_INFO frame__std__while_3 = {2, {"body", "cond_and_body"}};
static void cont__std__while_4(void);
static NODE *get__std__while(void) {
  return var.std__while;
}
static NODE *func__std__do_while_1;
static void entry__std__do_while_1(void);
static FRAME_INFO frame__std__do_while_1 = {1, {"body"}};
static void cont__std__do_while_2(void);
static NODE *func__std__do_while_3;
static void entry__std__do_while_3(void);
static FRAME_INFO frame__std__do_while_3 = {1, {"body"}};
static NODE *get__std__do_while(void) {
  return var.std__do_while;
}
static NODE *func__std__do_until_1;
static void entry__std__do_until_1(void);
static FRAME_INFO frame__std__do_until_1 = {1, {"body"}};
static void cont__std__do_until_2(void);
static NODE *func__std__do_until_3;
static void entry__std__do_until_3(void);
static FRAME_INFO frame__std__do_until_3 = {1, {"body"}};
static NODE *get__std__do_until(void) {
  return var.std__do_until;
}
void run__basic__loops(void);

static CONTINUATION_INFO continuation_info[] = {
  {run__basic__loops, NULL, },
  {entry__std__from_to_6, NULL, 100, 100, 25, 34},
  {entry__std__from_to_3, NULL, 100, 100, 10, 22},
  {cont__std__from_to_4, &frame__std__from_to_3, 100, 100, 10, 22},
  {cont__std__from_to_5, &frame__std__from_to_3, 100, 100, 7, 34},
  {cont__std__from_to_7, &frame__std__from_to_3, 101, 101, 17, 23},
  {cont__std__from_to_8, &frame__std__from_to_3, 101, 101, 7, 39},
  {entry__std__from_to_9, NULL, 103, 103, 7, 31},
  {entry__std__from_to_1, NULL, 99, 99, 5, 20},
  {cont__std__from_to_2, &frame__std__from_to_1, 98, 103, 3, 32},
  {entry__from_to_1_4, NULL, 107, 107, 5, 10},
  {cont__from_to_1_5, &frame__from_to_1_4, 108, 108, 15, 17},
  {cont__from_to_1_6, &frame__from_to_1_4, 108, 108, 5, 24},
  {entry__from_to_1_1, NULL, 106, 106, 6, 11},
  {cont__from_to_1_2, &frame__from_to_1_1, 106, 106, 6, 11},
  {cont__from_to_1_3, &frame__from_to_1_1, 106, 108, 3, 24},
  {entry__from_to_2_4, NULL, 112, 112, 5, 9},
  {cont__from_to_2_5, &frame__from_to_2_4, 113, 113, 5, 10},
  {cont__from_to_2_6, &frame__from_to_2_4, 114, 114, 15, 17},
  {cont__from_to_2_7, &frame__from_to_2_4, 114, 114, 5, 30},
  {entry__from_to_2_1, NULL, 111, 111, 6, 11},
  {cont__from_to_2_2, &frame__from_to_2_1, 111, 111, 6, 11},
  {cont__from_to_2_3, &frame__from_to_2_1, 111, 114, 3, 30},
  {entry__std__from_to_by_6, NULL, 176, 176, 25, 34},
  {entry__std__from_to_by_3, NULL, 176, 176, 10, 22},
  {cont__std__from_to_by_4, &frame__std__from_to_by_3, 176, 176, 10, 22},
  {cont__std__from_to_by_5, &frame__std__from_to_by_3, 176, 176, 7, 34},
  {cont__std__from_to_by_7, &frame__std__from_to_by_3, 177, 177, 20, 29},
  {cont__std__from_to_by_8, &frame__std__from_to_by_3, 177, 177, 7, 50},
  {entry__std__from_to_by_9, NULL, 179, 179, 7, 39},
  {entry__std__from_to_by_1, NULL, 175, 175, 5, 20},
  {cont__std__from_to_by_2, &frame__std__from_to_by_1, 174, 179, 3, 40},
  {entry__from_to_by_1_4, NULL, 183, 183, 5, 10},
  {cont__from_to_by_1_5, &frame__from_to_by_1_4, 184, 184, 18, 23},
  {cont__from_to_by_1_6, &frame__from_to_by_1_4, 184, 184, 5, 35},
  {entry__from_to_by_1_1, NULL, 182, 182, 6, 11},
  {cont__from_to_by_1_2, &frame__from_to_by_1_1, 182, 182, 6, 11},
  {cont__from_to_by_1_3, &frame__from_to_by_1_1, 182, 184, 3, 35},
  {entry__from_to_by_2_4, NULL, 188, 188, 5, 9},
  {cont__from_to_by_2_5, &frame__from_to_by_2_4, 189, 189, 5, 10},
  {cont__from_to_by_2_6, &frame__from_to_by_2_4, 190, 190, 18, 23},
  {cont__from_to_by_2_7, &frame__from_to_by_2_4, 190, 190, 5, 41},
  {entry__from_to_by_2_1, NULL, 187, 187, 6, 11},
  {cont__from_to_by_2_2, &frame__from_to_by_2_1, 187, 187, 6, 11},
  {cont__from_to_by_2_3, &frame__from_to_by_2_1, 187, 190, 3, 41},
  {entry__std__from_down_to_6, NULL, 247, 247, 25, 34},
  {entry__std__from_down_to_3, NULL, 247, 247, 10, 22},
  {cont__std__from_down_to_4, &frame__std__from_down_to_3, 247, 247, 10, 22},
  {cont__std__from_down_to_5, &frame__std__from_down_to_3, 247, 247, 7, 34},
  {cont__std__from_down_to_7, &frame__std__from_down_to_3, 248, 248, 22, 28},
  {cont__std__from_down_to_8, &frame__std__from_down_to_3, 248, 248, 7, 44},
  {entry__std__from_down_to_9, NULL, 250, 250, 7, 36},
  {entry__std__from_down_to_1, NULL, 246, 246, 5, 20},
  {cont__std__from_down_to_2, &frame__std__from_down_to_1, 245, 250, 3, 37},
  {entry__from_down_to_1_4, NULL, 254, 254, 5, 10},
  {cont__from_down_to_1_5, &frame__from_down_to_1_4, 255, 255, 20, 22},
  {cont__from_down_to_1_6, &frame__from_down_to_1_4, 255, 255, 5, 29},
  {entry__from_down_to_1_1, NULL, 253, 253, 6, 11},
  {cont__from_down_to_1_2, &frame__from_down_to_1_1, 253, 253, 6, 11},
  {cont__from_down_to_1_3, &frame__from_down_to_1_1, 253, 255, 3, 29},
  {entry__from_down_to_2_4, NULL, 259, 259, 5, 9},
  {cont__from_down_to_2_5, &frame__from_down_to_2_4, 260, 260, 5, 10},
  {cont__from_down_to_2_6, &frame__from_down_to_2_4, 261, 261, 15, 17},
  {cont__from_down_to_2_7, &frame__from_down_to_2_4, 261, 261, 5, 30},
  {entry__from_down_to_2_1, NULL, 258, 258, 6, 11},
  {cont__from_down_to_2_2, &frame__from_down_to_2_1, 258, 258, 6, 11},
  {cont__from_down_to_2_3, &frame__from_down_to_2_1, 258, 261, 3, 30},
  {entry__std__from_down_to_by_6, NULL, 317, 317, 25, 34},
  {entry__std__from_down_to_by_3, NULL, 317, 317, 10, 22},
  {cont__std__from_down_to_by_4, &frame__std__from_down_to_by_3, 317, 317, 10, 22},
  {cont__std__from_down_to_by_5, &frame__std__from_down_to_by_3, 317, 317, 7, 34},
  {cont__std__from_down_to_by_7, &frame__std__from_down_to_by_3, 318, 318, 25, 34},
  {cont__std__from_down_to_by_8, &frame__std__from_down_to_by_3, 318, 318, 7, 55},
  {entry__std__from_down_to_by_9, NULL, 320, 320, 7, 44},
  {entry__std__from_down_to_by_1, NULL, 316, 316, 5, 20},
  {cont__std__from_down_to_by_2, &frame__std__from_down_to_by_1, 315, 320, 3, 45},
  {entry__from_down_to_by_1_4, NULL, 324, 324, 5, 10},
  {cont__from_down_to_by_1_5, &frame__from_down_to_by_1_4, 325, 325, 23, 28},
  {cont__from_down_to_by_1_6, &frame__from_down_to_by_1_4, 325, 325, 5, 40},
  {entry__from_down_to_by_1_1, NULL, 323, 323, 6, 11},
  {cont__from_down_to_by_1_2, &frame__from_down_to_by_1_1, 323, 323, 6, 11},
  {cont__from_down_to_by_1_3, &frame__from_down_to_by_1_1, 323, 325, 3, 40},
  {entry__from_down_to_by_2_4, NULL, 329, 329, 5, 9},
  {cont__from_down_to_by_2_5, &frame__from_down_to_by_2_4, 330, 330, 5, 10},
  {cont__from_down_to_by_2_6, &frame__from_down_to_by_2_4, 331, 331, 23, 28},
  {cont__from_down_to_by_2_7, &frame__from_down_to_by_2_4, 331, 331, 5, 46},
  {entry__from_down_to_by_2_1, NULL, 328, 328, 6, 11},
  {cont__from_down_to_by_2_2, &frame__from_down_to_by_2_1, 328, 328, 6, 11},
  {cont__from_down_to_by_2_3, &frame__from_down_to_by_2_1, 328, 331, 3, 46},
  {entry__std__repeat_4, NULL, 361, 361, 5, 8},
  {cont__std__repeat_5, &frame__std__repeat_4, 362, 362, 12, 14},
  {cont__std__repeat_6, &frame__std__repeat_4, 362, 362, 5, 19},
  {entry__std__repeat_1, NULL, 360, 360, 6, 11},
  {cont__std__repeat_2, &frame__std__repeat_1, 360, 360, 6, 11},
  {cont__std__repeat_3, &frame__std__repeat_1, 360, 362, 3, 19},
  {entry__std__forever_1, NULL, 402, 402, 3, 6},
  {cont__std__forever_2, &frame__std__forever_1, 403, 403, 3, 14},
  {entry__std__while_3, NULL, 455, 455, 5, 8},
  {cont__std__while_4, &frame__std__while_3, 456, 456, 5, 23},
  {entry__std__while_1, NULL, 453, 453, 3, 27},
  {cont__std__while_2, &frame__std__while_1, 454, 456, 3, 23},
  {entry__std__do_while_3, NULL, 471, 471, 14, 26},
  {entry__std__do_while_1, NULL, 471, 471, 6, 11},
  {cont__std__do_while_2, &frame__std__do_while_1, 471, 471, 3, 26},
  {entry__std__do_until_3, NULL, 486, 486, 18, 30},
  {entry__std__do_until_1, NULL, 486, 486, 10, 15},
  {cont__std__do_until_2, &frame__std__do_until_1, 486, 486, 3, 30}
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
static void entry__std__from_to_3(void) {
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
  // 100: ... first <= last
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* last */;
  arguments->slots[1] = frame->slots[1] /* first */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__std__from_to_4;
}
static void cont__std__from_to_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 100: ... first <= last
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__std__from_to_5;
}
static void cont__std__from_to_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 100: ... : body first
  frame->slots[6] /* temp__3 */ = create_closure(entry__std__from_to_6, 0);
  // 100: if first <= last: body first
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__std__from_to_7;
}
static void entry__std__from_to_6(void) {
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
  // 100: ... body first
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* first */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__std__from_to_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 101: ... first+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* first */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__std__from_to_8;
}
static void cont__std__from_to_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 101: from_to_2 first+1 last body body2
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
static void entry__std__from_to_9(void) {
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
  // 103: from_to_1 first last body
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
static void entry__std__from_to_1(void) {
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
  // 99: body2.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* body2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__std__from_to_2;
}
static void cont__std__from_to_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  //  99: ... :
  // 100:   if first <= last: body first
  // 101:   from_to_2 first+1 last body body2
  frame->slots[5] /* temp__2 */ = create_closure(entry__std__from_to_3, 0);
  // 102: :
  // 103:   from_to_1 first last body
  frame->slots[6] /* temp__3 */ = create_closure(entry__std__from_to_9, 0);
  //  98: if
  //  99:   body2.is_defined:
  // 100:     if first <= last: body first
  // 101:     from_to_2 first+1 last body body2
  // 102:   :
  // 103:     from_to_1 first last body
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
static void entry__from_to_1_4(void) {
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
  // 107: body s
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* s */;
  result_count = 0;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame->cont = cont__from_to_1_5;
}
static void cont__from_to_1_5(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 108: ... s+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* s */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__from_to_1_6;
}
static void cont__from_to_1_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 108: from_to_1 s+1 e body
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
static void entry__from_to_1_1(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // s: 0
  // e: 1
  // body: 2
  if (argument_count != 3) {
    invalid_arguments_error();
    return;
  }
  // 106: ... s <= e
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* e */;
  arguments->slots[1] = frame->slots[0] /* s */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__from_to_1_2;
}
static void cont__from_to_1_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 106: ... s <= e
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__from_to_1_3;
}
static void cont__from_to_1_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 106: ... :
  // 107:   body s
  // 108:   from_to_1 s+1 e body
  frame->slots[5] /* temp__3 */ = create_closure(entry__from_to_1_4, 0);
  // 106: if s <= e:
  // 107:   body s
  // 108:   from_to_1 s+1 e body
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__from_to_2_4(void) {
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
  // 112: body2
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = frame->slots[0] /* body2 */;
  func = myself->type;
  frame->cont = cont__from_to_2_5;
}
static void cont__from_to_2_5(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 113: body s
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* s */;
  result_count = 0;
  myself = frame->slots[1] /* body */;
  func = myself->type;
  frame->cont = cont__from_to_2_6;
}
static void cont__from_to_2_6(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 114: ... s+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* s */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__from_to_2_7;
}
static void cont__from_to_2_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 114: from_to_2 s+1 e body body2
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
static void entry__from_to_2_1(void) {
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
  // 111: ... s <= e
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* e */;
  arguments->slots[1] = frame->slots[0] /* s */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__from_to_2_2;
}
static void cont__from_to_2_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 111: ... s <= e
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__from_to_2_3;
}
static void cont__from_to_2_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 111: ... :
  // 112:   body2
  // 113:   body s
  // 114:   from_to_2 s+1 e body body2
  frame->slots[6] /* temp__3 */ = create_closure(entry__from_to_2_4, 0);
  // 111: if s <= e:
  // 112:   body2
  // 113:   body s
  // 114:   from_to_2 s+1 e body body2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__from_to_by_3(void) {
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
  // 176: ... first <= last
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* last */;
  arguments->slots[1] = frame->slots[1] /* first */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__std__from_to_by_4;
}
static void cont__std__from_to_by_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 176: ... first <= last
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__std__from_to_by_5;
}
static void cont__std__from_to_by_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 176: ... : body first
  frame->slots[7] /* temp__3 */ = create_closure(entry__std__from_to_by_6, 0);
  // 176: if first <= last: body first
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__std__from_to_by_7;
}
static void entry__std__from_to_by_6(void) {
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
  // 176: ... body first
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* first */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__std__from_to_by_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 177: ... first+step
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* first */;
  arguments->slots[1] = frame->slots[3] /* step */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__std__from_to_by_8;
}
static void cont__std__from_to_by_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 177: from_to_by_2 first+step last step body body2
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
static void entry__std__from_to_by_9(void) {
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
  // 179: from_to_by_1 first last step body
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
static void entry__std__from_to_by_1(void) {
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
  // 175: body2.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* body2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__std__from_to_by_2;
}
static void cont__std__from_to_by_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 175: ... :
  // 176:   if first <= last: body first
  // 177:   from_to_by_2 first+step last step body body2
  frame->slots[6] /* temp__2 */ = create_closure(entry__std__from_to_by_3, 0);
  // 178: :
  // 179:   from_to_by_1 first last step body
  frame->slots[7] /* temp__3 */ = create_closure(entry__std__from_to_by_9, 0);
  // 174: if
  // 175:   body2.is_defined:
  // 176:     if first <= last: body first
  // 177:     from_to_by_2 first+step last step body body2
  // 178:   :
  // 179:     from_to_by_1 first last step body
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
static void entry__from_to_by_1_4(void) {
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
  // 183: body s
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* s */;
  result_count = 0;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame->cont = cont__from_to_by_1_5;
}
static void cont__from_to_by_1_5(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 184: ... s+step
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* s */;
  arguments->slots[1] = frame->slots[2] /* step */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__from_to_by_1_6;
}
static void cont__from_to_by_1_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 184: from_to_by_1 s+step e step body
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
static void entry__from_to_by_1_1(void) {
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
  // 182: ... s <= e
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* e */;
  arguments->slots[1] = frame->slots[0] /* s */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__from_to_by_1_2;
}
static void cont__from_to_by_1_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 182: ... s <= e
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__from_to_by_1_3;
}
static void cont__from_to_by_1_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 182: ... :
  // 183:   body s
  // 184:   from_to_by_1 s+step e step body
  frame->slots[6] /* temp__3 */ = create_closure(entry__from_to_by_1_4, 0);
  // 182: if s <= e:
  // 183:   body s
  // 184:   from_to_by_1 s+step e step body
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__from_to_by_2_4(void) {
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
  // 188: body2
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = frame->slots[0] /* body2 */;
  func = myself->type;
  frame->cont = cont__from_to_by_2_5;
}
static void cont__from_to_by_2_5(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 189: body s
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* s */;
  result_count = 0;
  myself = frame->slots[1] /* body */;
  func = myself->type;
  frame->cont = cont__from_to_by_2_6;
}
static void cont__from_to_by_2_6(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 190: ... s+step
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* s */;
  arguments->slots[1] = frame->slots[3] /* step */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__from_to_by_2_7;
}
static void cont__from_to_by_2_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 190: from_to_by_2 s+step e step body body2
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
static void entry__from_to_by_2_1(void) {
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
  // 187: ... s <= e
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* e */;
  arguments->slots[1] = frame->slots[0] /* s */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__from_to_by_2_2;
}
static void cont__from_to_by_2_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 187: ... s <= e
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__from_to_by_2_3;
}
static void cont__from_to_by_2_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 187: ... :
  // 188:   body2
  // 189:   body s
  // 190:   from_to_by_2 s+step e step body body2
  frame->slots[7] /* temp__3 */ = create_closure(entry__from_to_by_2_4, 0);
  // 187: if s <= e:
  // 188:   body2
  // 189:   body s
  // 190:   from_to_by_2 s+step e step body body2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__from_down_to_3(void) {
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
  // 247: ... first >= last
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* first */;
  arguments->slots[1] = frame->slots[1] /* last */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__std__from_down_to_4;
}
static void cont__std__from_down_to_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 247: ... first >= last
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__std__from_down_to_5;
}
static void cont__std__from_down_to_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 247: ... : body first
  frame->slots[6] /* temp__3 */ = create_closure(entry__std__from_down_to_6, 0);
  // 247: if first >= last: body first
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__std__from_down_to_7;
}
static void entry__std__from_down_to_6(void) {
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
  // 247: ... body first
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* first */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__std__from_down_to_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 248: ... first+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* first */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__std__from_down_to_8;
}
static void cont__std__from_down_to_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 248: from_down_to_2 first+1 last body body2
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
static void entry__std__from_down_to_9(void) {
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
  // 250: from_down_to_1 first last body
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
static void entry__std__from_down_to_1(void) {
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
  // 246: body2.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* body2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__std__from_down_to_2;
}
static void cont__std__from_down_to_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 246: ... :
  // 247:   if first >= last: body first
  // 248:   from_down_to_2 first+1 last body body2
  frame->slots[5] /* temp__2 */ = create_closure(entry__std__from_down_to_3, 0);
  // 249: :
  // 250:   from_down_to_1 first last body
  frame->slots[6] /* temp__3 */ = create_closure(entry__std__from_down_to_9, 0);
  // 245: if
  // 246:   body2.is_defined:
  // 247:     if first >= last: body first
  // 248:     from_down_to_2 first+1 last body body2
  // 249:   :
  // 250:     from_down_to_1 first last body
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
static void entry__from_down_to_1_4(void) {
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
  // 254: body s
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* s */;
  result_count = 0;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame->cont = cont__from_down_to_1_5;
}
static void cont__from_down_to_1_5(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 255: ... s-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* s */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__from_down_to_1_6;
}
static void cont__from_down_to_1_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 255: from_down_to_1 s-1 e body
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
static void entry__from_down_to_1_1(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // s: 0
  // e: 1
  // body: 2
  if (argument_count != 3) {
    invalid_arguments_error();
    return;
  }
  // 253: ... s >= e
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* s */;
  arguments->slots[1] = frame->slots[1] /* e */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__from_down_to_1_2;
}
static void cont__from_down_to_1_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 253: ... s >= e
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__from_down_to_1_3;
}
static void cont__from_down_to_1_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 253: ... :
  // 254:   body s
  // 255:   from_down_to_1 s-1 e body
  frame->slots[5] /* temp__3 */ = create_closure(entry__from_down_to_1_4, 0);
  // 253: if s >= e:
  // 254:   body s
  // 255:   from_down_to_1 s-1 e body
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__from_down_to_2_4(void) {
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
  // 259: body2
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = frame->slots[0] /* body2 */;
  func = myself->type;
  frame->cont = cont__from_down_to_2_5;
}
static void cont__from_down_to_2_5(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 260: body s
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* s */;
  result_count = 0;
  myself = frame->slots[1] /* body */;
  func = myself->type;
  frame->cont = cont__from_down_to_2_6;
}
static void cont__from_down_to_2_6(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 261: ... s-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* s */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__from_down_to_2_7;
}
static void cont__from_down_to_2_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 261: from_to_2 s-1 e body body2
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
static void entry__from_down_to_2_1(void) {
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
  // 258: ... s >= e
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* s */;
  arguments->slots[1] = frame->slots[1] /* e */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__from_down_to_2_2;
}
static void cont__from_down_to_2_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 258: ... s >= e
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__from_down_to_2_3;
}
static void cont__from_down_to_2_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 258: ... :
  // 259:   body2
  // 260:   body s
  // 261:   from_to_2 s-1 e body body2
  frame->slots[6] /* temp__3 */ = create_closure(entry__from_down_to_2_4, 0);
  // 258: if s >= e:
  // 259:   body2
  // 260:   body s
  // 261:   from_to_2 s-1 e body body2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__from_down_to_by_3(void) {
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
  // 317: ... first >= last
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* first */;
  arguments->slots[1] = frame->slots[1] /* last */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__std__from_down_to_by_4;
}
static void cont__std__from_down_to_by_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 317: ... first >= last
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__std__from_down_to_by_5;
}
static void cont__std__from_down_to_by_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 317: ... : body first
  frame->slots[7] /* temp__3 */ = create_closure(entry__std__from_down_to_by_6, 0);
  // 317: if first >= last: body first
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__std__from_down_to_by_7;
}
static void entry__std__from_down_to_by_6(void) {
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
  // 317: ... body first
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* first */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__std__from_down_to_by_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 318: ... first+step
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* first */;
  arguments->slots[1] = frame->slots[3] /* step */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__std__from_down_to_by_8;
}
static void cont__std__from_down_to_by_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 318: from_down_to_by_2 first+step last step body body2
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
static void entry__std__from_down_to_by_9(void) {
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
  // 320: from_down_to_by_1 first last step body
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
static void entry__std__from_down_to_by_1(void) {
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
  // 316: body2.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* body2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__std__from_down_to_by_2;
}
static void cont__std__from_down_to_by_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 316: ... :
  // 317:   if first >= last: body first
  // 318:   from_down_to_by_2 first+step last step body body2
  frame->slots[6] /* temp__2 */ = create_closure(entry__std__from_down_to_by_3, 0);
  // 319: :
  // 320:   from_down_to_by_1 first last step body
  frame->slots[7] /* temp__3 */ = create_closure(entry__std__from_down_to_by_9, 0);
  // 315: if
  // 316:   body2.is_defined:
  // 317:     if first >= last: body first
  // 318:     from_down_to_by_2 first+step last step body body2
  // 319:   :
  // 320:     from_down_to_by_1 first last step body
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
static void entry__from_down_to_by_1_4(void) {
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
  // 324: body s
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* s */;
  result_count = 0;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame->cont = cont__from_down_to_by_1_5;
}
static void cont__from_down_to_by_1_5(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 325: ... s-step
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* s */;
  arguments->slots[1] = frame->slots[2] /* step */;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__from_down_to_by_1_6;
}
static void cont__from_down_to_by_1_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 325: from_down_to_by_1 s-step e step body
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
static void entry__from_down_to_by_1_1(void) {
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
  // 323: ... s >= e
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* s */;
  arguments->slots[1] = frame->slots[1] /* e */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__from_down_to_by_1_2;
}
static void cont__from_down_to_by_1_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 323: ... s >= e
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__from_down_to_by_1_3;
}
static void cont__from_down_to_by_1_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 323: ... :
  // 324:   body s
  // 325:   from_down_to_by_1 s-step e step body
  frame->slots[6] /* temp__3 */ = create_closure(entry__from_down_to_by_1_4, 0);
  // 323: if s >= e:
  // 324:   body s
  // 325:   from_down_to_by_1 s-step e step body
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__from_down_to_by_2_4(void) {
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
  // 329: body2
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = frame->slots[0] /* body2 */;
  func = myself->type;
  frame->cont = cont__from_down_to_by_2_5;
}
static void cont__from_down_to_by_2_5(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 330: body s
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* s */;
  result_count = 0;
  myself = frame->slots[1] /* body */;
  func = myself->type;
  frame->cont = cont__from_down_to_by_2_6;
}
static void cont__from_down_to_by_2_6(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 331: ... s-step
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* s */;
  arguments->slots[1] = frame->slots[3] /* step */;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__from_down_to_by_2_7;
}
static void cont__from_down_to_by_2_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 331: from_down_to_by_2 s-step e step body body2
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
static void entry__from_down_to_by_2_1(void) {
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
  // 328: ... s >= e
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* s */;
  arguments->slots[1] = frame->slots[1] /* e */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__from_down_to_by_2_2;
}
static void cont__from_down_to_by_2_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 328: ... s >= e
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__from_down_to_by_2_3;
}
static void cont__from_down_to_by_2_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 328: ... :
  // 329:   body2
  // 330:   body s
  // 331:   from_down_to_by_2 s-step e step body body2
  frame->slots[7] /* temp__3 */ = create_closure(entry__from_down_to_by_2_4, 0);
  // 328: if s >= e:
  // 329:   body2
  // 330:   body s
  // 331:   from_down_to_by_2 s-step e step body body2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__repeat_4(void) {
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
  // 361: body
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame->cont = cont__std__repeat_5;
}
static void cont__std__repeat_5(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 362: ... n-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* n */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__std__repeat_6;
}
static void cont__std__repeat_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 362: repeat n-1 body
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[0] /* body */;
  result_count = frame->caller_result_count;
  myself = get__repeat();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__repeat_1(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // n: 0
  // body: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 360: ... n >= 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* n */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__std__repeat_2;
}
static void cont__std__repeat_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 360: ... n >= 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__std__repeat_3;
}
static void cont__std__repeat_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 360: ... :
  // 361:   body
  // 362:   repeat n-1 body
  frame->slots[4] /* temp__3 */ = create_closure(entry__std__repeat_4, 0);
  // 360: if n >= 1:
  // 361:   body
  // 362:   repeat n-1 body
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__forever_1(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // body: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 402: body
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame->cont = cont__std__forever_2;
}
static void cont__std__forever_2(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 403: forever body
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* body */;
  result_count = frame->caller_result_count;
  myself = get__forever();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__while_3(void) {
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
  // 455: body
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame->cont = cont__std__while_4;
}
static void cont__std__while_4(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 456: while cond_and_body
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* cond_and_body */;
  result_count = frame->caller_result_count;
  myself = get__while();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__while_1(void) {
  allocate_initialized_frame_gc(1, 4);
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
  // 453: cond_and_body $cond $body
  argument_count = 0;
  arguments = node_p;
  result_count = 2;
  myself = frame->slots[0] /* cond_and_body */;
  func = myself->type;
  frame->cont = cont__std__while_2;
}
static void cont__std__while_2(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* cond */, arguments->slots[0]);
  initialize_future(frame->slots[2] /* body */, arguments->slots[1]);
  // 454: ... :
  // 455:   body
  // 456:   while cond_and_body
  frame->slots[3] /* temp__1 */ = create_closure(entry__std__while_3, 0);
  // 454: if cond:
  // 455:   body
  // 456:   while cond_and_body
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* cond */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__do_while_3(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // body: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* body */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 471: ... do_while body
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* body */;
  result_count = frame->caller_result_count;
  myself = get__do_while();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__do_while_1(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // body: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 471: ... body()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame->cont = cont__std__do_while_2;
}
static void cont__std__do_while_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 471: ... : do_while body
  frame->slots[2] /* temp__2 */ = create_closure(entry__std__do_while_3, 0);
  // 471: if body(): do_while body
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__do_until_3(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // body: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* body */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 486: ... do_until body
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* body */;
  result_count = frame->caller_result_count;
  myself = get__do_until();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__do_until_1(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // body: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 486: ... body()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame->cont = cont__std__do_until_2;
}
static void cont__std__do_until_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 486: ... : do_until body
  frame->slots[2] /* temp__2 */ = create_closure(entry__std__do_until_3, 0);
  // 486: unless body(): do_until body
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
  set_module("basic__loops");
  number__1 = from_uint32(1U);
  func__std__from_to_1 = create_function(entry__std__from_to_1, -1);
  func__from_to_1_1 = create_function(entry__from_to_1_1, 3);
  func__from_to_2_1 = create_function(entry__from_to_2_1, 4);
  func__std__from_to_by_1 = create_function(entry__std__from_to_by_1, -1);
  func__from_to_by_1_1 = create_function(entry__from_to_by_1_1, 4);
  func__from_to_by_2_1 = create_function(entry__from_to_by_2_1, 5);
  func__std__from_down_to_1 = create_function(entry__std__from_down_to_1, -1);
  func__from_down_to_1_1 = create_function(entry__from_down_to_1_1, 3);
  func__from_down_to_2_1 = create_function(entry__from_down_to_2_1, 4);
  func__std__from_down_to_by_1 = create_function(entry__std__from_down_to_by_1, -1);
  func__from_down_to_by_1_1 = create_function(entry__from_down_to_by_1_1, 4);
  func__from_down_to_by_2_1 = create_function(entry__from_down_to_by_2_1, 5);
  func__std__repeat_1 = create_function(entry__std__repeat_1, 2);
  func__std__forever_1 = create_function(entry__std__forever_1, 1);
  func__std__while_1 = create_function(entry__std__while_1, 1);
  func__std__do_while_1 = create_function(entry__std__do_while_1, 1);
  func__std__do_until_1 = create_function(entry__std__do_until_1, 1);
}

static int already_run_phase_3 = false;

EXPORT void phase_3__basic__loops(void) {
  if (already_run_phase_3) return;
  already_run_phase_3 = true;
  set_module("basic__loops");
  set_used_namespaces(used_namespaces);
  var.std__from_to = create_future();
  define_single_assign_static("std", "from_to", get__std__from_to, &var.std__from_to);
  var.std__from_to_by = create_future();
  define_single_assign_static("std", "from_to_by", get__std__from_to_by, &var.std__from_to_by);
  var.std__from_down_to = create_future();
  define_single_assign_static("std", "from_down_to", get__std__from_down_to, &var.std__from_down_to);
  var.std__from_down_to_by = create_future();
  define_single_assign_static("std", "from_down_to_by", get__std__from_down_to_by, &var.std__from_down_to_by);
  var.std__repeat = create_future();
  define_single_assign_static("std", "repeat", get__std__repeat, &var.std__repeat);
  var.std__forever = create_future();
  define_single_assign_static("std", "forever", get__std__forever, &var.std__forever);
  var.std__while = create_future();
  define_single_assign_static("std", "while", get__std__while, &var.std__while);
  var.std__do_while = create_future();
  define_single_assign_static("std", "do_while", get__std__do_while, &var.std__do_while);
  var.std__do_until = create_future();
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
  initialize_future(var.std__from_to, func__std__from_to_1);
  assign_variable(&var._from_to_1, &func__from_to_1_1);
  assign_variable(&var._from_to_2, &func__from_to_2_1);
  initialize_future(var.std__from_to_by, func__std__from_to_by_1);
  assign_variable(&var._from_to_by_1, &func__from_to_by_1_1);
  assign_variable(&var._from_to_by_2, &func__from_to_by_2_1);
  initialize_future(var.std__from_down_to, func__std__from_down_to_1);
  assign_variable(&var._from_down_to_1, &func__from_down_to_1_1);
  assign_variable(&var._from_down_to_2, &func__from_down_to_2_1);
  initialize_future(var.std__from_down_to_by, func__std__from_down_to_by_1);
  assign_variable(&var._from_down_to_by_1, &func__from_down_to_by_1_1);
  assign_variable(&var._from_down_to_by_2, &func__from_down_to_by_2_1);
  initialize_future(var.std__repeat, func__std__repeat_1);
  initialize_future(var.std__forever, func__std__forever_1);
  initialize_future(var.std__while, func__std__while_1);
  initialize_future(var.std__do_while, func__std__do_while_1);
  initialize_future(var.std__do_until, func__std__do_until_1);
}

static int already_run_phase_6 = false;

EXPORT void phase_6__basic__loops(void) {
  if (already_run_phase_6) return;
  already_run_phase_6 = true;
  register_collector(collect__basic__loops);
}
