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
#if defined(__GNUC__) && !defined(__clang__) && defined(__x86_64)
  #define ASM(x) asm(x)
#else
  #define ASM(x)
#endif
REGISTER FUNC func ASM("r14");
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
REGISTER FRAME *frame ASM("r15");
IMPORT void allocate_initialized_frame_gc(int slot_idx, int slot_count);
IMPORT NODE *create_continuation(void);
REGISTER int argument_count ASM("ebx");
IMPORT void invalid_arguments_error(void);
IMPORT NODE *create_closure(FUNC type, int par_count);
REGISTER FRAME *arguments ASM("r12");
IMPORT void *node_p;
IMPORT int result_count;
REGISTER NODE *myself ASM("r13");
IMPORT void invalid_results_error(void);
IMPORT NODE *create_cell(void);
IMPORT void too_few_arguments_error(void);
IMPORT void too_many_arguments_error(void);
IMPORT NODE *undefined;
typedef struct CELL {
  FUNC type;
  struct ATTRIBUTES *attributes;
  NODE *contents;
} CELL;
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
static NODE_GETTER get__false;
static NODE_GETTER get_value_or_future__false;
static NODE_GETTER get__for_each;
static NODE_GETTER get_value_or_future__for_each;
static NODE_GETTER get__if;
static NODE_GETTER get_value_or_future__if;
static NODE_GETTER get__is_defined;
static NODE_GETTER get_value_or_future__is_defined;
static NODE_GETTER get__parameter_count_of;
static NODE_GETTER get_value_or_future__parameter_count_of;
static NODE_GETTER get__std__equal;
static NODE_GETTER get_value_or_future__std__equal;
static NODE_GETTER get__true;
static NODE_GETTER get_value_or_future__true;
static NODE_GETTER get__undefined;
static NODE_GETTER get_value_or_future__undefined;
static NODE_GETTER get__unless;
static NODE_GETTER get_value_or_future__unless;
static struct {
  NODE *std__any_of;
  NODE *std__all_of;
  NODE *std__fold;
  NODE *std__find_first;
} var;
static const char *var_names[] = {
};
static NODE *func__1_1_std__any_of;
static void entry__1_1_std__any_of(void);
static FRAME_INFO frame__1_1_std__any_of = {3, {"collection", "test", "return"}};
static NODE *func__1_2;
static void entry__1_2(void);
static FRAME_INFO frame__1_2 = {3, {"item", "test", "return"}};
static void cont__1_3(void);
static NODE *func__1_4;
static void entry__1_4(void);
static FRAME_INFO frame__1_4 = {1, {"return"}};
static void cont__1_5(void);
static NODE *get__std__any_of(void) {
  return var.std__any_of;
}
static NODE *func__2_1_std__all_of;
static void entry__2_1_std__all_of(void);
static FRAME_INFO frame__2_1_std__all_of = {3, {"collection", "test", "return"}};
static NODE *func__2_2;
static void entry__2_2(void);
static FRAME_INFO frame__2_2 = {3, {"item", "test", "return"}};
static void cont__2_3(void);
static NODE *func__2_4;
static void entry__2_4(void);
static FRAME_INFO frame__2_4 = {1, {"return"}};
static void cont__2_5(void);
static NODE *get__std__all_of(void) {
  return var.std__all_of;
}
static NODE *func__3_1_std__fold;
static void entry__3_1_std__fold(void);
static FRAME_INFO frame__3_1_std__fold = {4, {"base", "func", "collection", "result"}};
static NODE *func__3_2;
static void entry__3_2(void);
static FRAME_INFO frame__3_2 = {3, {"item", "result", "func"}};
static void cont__3_3(void);
static NODE *func__3_4;
static void entry__3_4(void);
static FRAME_INFO frame__3_4 = {3, {"result", "func", "item"}};
static void cont__3_5(void);
static NODE *func__3_6;
static void entry__3_6(void);
static FRAME_INFO frame__3_6 = {2, {"result", "item"}};
static void cont__3_7(void);
static NODE *get__std__fold(void) {
  return var.std__fold;
}
static NODE *func__4_1_std__find_first;
static void entry__4_1_std__find_first(void);
static FRAME_INFO frame__4_1_std__find_first = {3, {"collection", "test", "return"}};
static void cont__4_2(void);
static void cont__4_3(void);
static NODE *func__4_4;
static void entry__4_4(void);
static FRAME_INFO frame__4_4 = {3, {"collection", "test", "return"}};
static NODE *func__4_5;
static void entry__4_5(void);
static FRAME_INFO frame__4_5 = {4, {"idx", "item", "test", "return"}};
static void cont__4_6(void);
static NODE *func__4_7;
static void entry__4_7(void);
static FRAME_INFO frame__4_7 = {3, {"return", "idx", "item"}};
static void cont__4_8(void);
static NODE *func__4_9;
static void entry__4_9(void);
static FRAME_INFO frame__4_9 = {3, {"collection", "test", "return"}};
static NODE *func__4_10;
static void entry__4_10(void);
static FRAME_INFO frame__4_10 = {3, {"item", "test", "return"}};
static void cont__4_11(void);
static NODE *func__4_12;
static void entry__4_12(void);
static FRAME_INFO frame__4_12 = {2, {"return", "item"}};
static void cont__4_13(void);
static void cont__4_14(void);
static NODE *get__std__find_first(void) {
  return var.std__find_first;
}
void run__basic__functional(void);

static CONTINUATION_INFO continuation_info[] = {
  {run__basic__functional, NULL, },
  {entry__1_4, NULL, 34, 34, 46, 56},
  {entry__1_2, NULL, 34, 34, 34, 43},
  {cont__1_3, &frame__1_2, 34, 34, 31, 56},
  {entry__1_1_std__any_of, NULL, 34, 34, 3, 56},
  {cont__1_5, &frame__1_1_std__any_of, 35, 35, 3, 10},
  {entry__2_4, NULL, 48, 48, 50, 61},
  {entry__2_2, NULL, 48, 48, 38, 47},
  {cont__2_3, &frame__2_2, 48, 48, 31, 61},
  {entry__2_1_std__all_of, NULL, 48, 48, 3, 61},
  {cont__2_5, &frame__2_1_std__all_of, 49, 49, 3, 9},
  {entry__3_4, NULL, 81, 81, 9, 33},
  {cont__3_5, &frame__3_4, 81, 81, 33, 33},
  {entry__3_6, NULL, 83, 83, 20, 20},
  {entry__3_2, NULL, 80, 80, 7, 23},
  {cont__3_3, &frame__3_2, 79, 83, 5, 21},
  {entry__3_1_std__fold, NULL, 78, 83, 3, 22},
  {cont__3_7, &frame__3_1_std__fold, 84, 84, 3, 11},
  {entry__4_7, NULL, 104, 104, 54, 68},
  {entry__4_5, NULL, 104, 104, 42, 51},
  {cont__4_6, &frame__4_5, 104, 104, 39, 68},
  {entry__4_4, NULL, 104, 104, 7, 68},
  {cont__4_8, &frame__4_4, 105, 105, 7, 32},
  {entry__4_12, NULL, 107, 107, 50, 60},
  {entry__4_10, NULL, 107, 107, 38, 47},
  {cont__4_11, &frame__4_10, 107, 107, 35, 60},
  {entry__4_9, NULL, 107, 107, 7, 60},
  {cont__4_13, &frame__4_9, 108, 108, 7, 22},
  {entry__4_1_std__find_first, NULL, 103, 103, 5, 30},
  {cont__4_2, &frame__4_1_std__find_first, 103, 103, 5, 35},
  {cont__4_3, &frame__4_1_std__find_first, 102, 108, 3, 23},
  {cont__4_14, &frame__4_1_std__find_first, 108, 108, 23, 23}
};

union NODE {
  struct {
    FUNC type;
    ATTRIBUTES *attributes;
  };
  CONTINUATION continuation;
  CLOSURE closure;
};
static NODE *number__2;

static const char *used_namespaces[] = {
  "std",
  NULL
};

static MODULE_INFO module_info = {
  NULL,
  "basic__functional",
  continuation_info,
  sizeof(continuation_info)/sizeof(CONTINUATION_INFO),
  (NODE **)&var,
  var_names,
  sizeof(var_names)/sizeof(const char *),
  used_namespaces,
  {DEBUG_FILENAME("basic/functional.sim")}
};

/******
C O D E
******/

static int already_run = false;

EXPORT void run__basic__functional(void) {
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
static void entry__1_1_std__any_of(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // collection: 0
  // test: 1
  // return: 2
  frame->slots[2] /* return */ = create_continuation();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 34: ... : (item) if test(item): return true
  frame->slots[3] /* temp__1 */ = create_closure(entry__1_2, 1);
  // 34: for_each collection: (item) if test(item): return true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* collection */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__1_5;
}
static void entry__1_4(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 34: ... return true
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__true();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__1_2(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // item: 0
  // test: 1
  // return: 2
  frame->slots[1] = myself->closure.frame->slots[1]; /* test */
  frame->slots[2] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 34: ... test(item)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* item */;
  result_count = 1;
  myself = frame->slots[1] /* test */;
  func = myself->type;
  frame->cont = cont__1_3;
}
static void cont__1_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 34: ... : return true
  frame->slots[4] /* temp__2 */ = create_closure(entry__1_4, 0);
  // 34: ... if test(item): return true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__1_5(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 35: -> false
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__false();
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__2_1_std__all_of(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // collection: 0
  // test: 1
  // return: 2
  frame->slots[2] /* return */ = create_continuation();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 48: ... : (item) unless test(item): return false
  frame->slots[3] /* temp__1 */ = create_closure(entry__2_2, 1);
  // 48: for_each collection: (item) unless test(item): return false
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* collection */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__2_5;
}
static void entry__2_4(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 48: ... return false
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__false();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__2_2(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // item: 0
  // test: 1
  // return: 2
  frame->slots[1] = myself->closure.frame->slots[1]; /* test */
  frame->slots[2] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 48: ... test(item)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* item */;
  result_count = 1;
  myself = frame->slots[1] /* test */;
  func = myself->type;
  frame->cont = cont__2_3;
}
static void cont__2_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 48: ... : return false
  frame->slots[4] /* temp__2 */ = create_closure(entry__2_4, 0);
  // 48: ... unless test(item): return false
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__2_5(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 49: -> true
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__true();
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__3_1_std__fold(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // base: 0
  // func: 1
  // collection: 2
  // result: 3
  frame->slots[3] /* result */ = create_cell();
  if (argument_count < 2) {
    too_few_arguments_error();
    return;
  }
  if (argument_count > 3) {
    too_many_arguments_error();
    return;
  }
  frame->slots[2] /* collection */ = arguments->slots[argument_count-1];
  frame->slots[1] /* func */ = arguments->slots[argument_count-2];
  switch(argument_count) {
    default: frame->slots[0] /* base */ = arguments->slots[0];
    case 2:;
  }
  switch(argument_count) {
    case 2: frame->slots[0] /* base */ = undefined;
  }
  // 77: $$result base
  ((CELL *)frame->slots[3])->contents /* result */ = frame->slots[0] /* base */;
  // 78: ... : (item)
  // 79:   if
  // 80:     result.is_defined:
  // 81:       !result func(result item)
  // 82:     :
  // 83:       !result item
  frame->slots[4] /* temp__1 */ = create_closure(entry__3_2, 1);
  // 78: for_each collection: (item)
  // 79:   if
  // 80:     result.is_defined:
  // 81:       !result func(result item)
  // 82:     :
  // 83:       !result item
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* collection */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__3_7;
}
static void entry__3_4(void) {
  allocate_initialized_frame_gc(3, 3);
  // slot allocations:
  // result: 0
  // func: 1
  // item: 2
  frame->slots[0] = myself->closure.frame->slots[1]; /* result */
  frame->slots[1] = myself->closure.frame->slots[2]; /* func */
  frame->slots[2] = myself->closure.frame->slots[0]; /* item */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 81: !result func(result item)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* result */;
  arguments->slots[1] = frame->slots[2] /* item */;
  result_count = 1;
  myself = frame->slots[1] /* func */;
  func = myself->type;
  frame->cont = cont__3_5;
}
static void cont__3_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* result */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__3_6(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // result: 0
  // item: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* result */
  frame->slots[1] = myself->closure.frame->slots[0]; /* item */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 83: !result item
  ((CELL *)frame->slots[0])->contents /* result */ = frame->slots[1] /* item */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__3_2(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // item: 0
  // result: 1
  // func: 2
  frame->slots[1] = myself->closure.frame->slots[3]; /* result */
  frame->slots[2] = myself->closure.frame->slots[1]; /* func */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 80: result.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* result */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__3_3;
}
static void cont__3_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 80: ... :
  // 81:   !result func(result item)
  frame->slots[4] /* temp__2 */ = create_closure(entry__3_4, 0);
  // 82: :
  // 83:   !result item
  frame->slots[5] /* temp__3 */ = create_closure(entry__3_6, 0);
  // 79: if
  // 80:   result.is_defined:
  // 81:     !result func(result item)
  // 82:   :
  // 83:     !result item
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
static void cont__3_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 84: -> result
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* result */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__4_1_std__find_first(void) {
  allocate_initialized_frame_gc(3, 7);
  // slot allocations:
  // collection: 0
  // test: 1
  // return: 2
  frame->slots[2] /* return */ = create_continuation();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 103: parameter_count_of(return)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* return */;
  result_count = 1;
  myself = get__parameter_count_of();
  func = myself->type;
  frame->cont = cont__4_2;
}
static void cont__4_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 103: parameter_count_of(return) == 2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__4_3;
}
static void cont__4_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 103: ... :
  // 104:   for_each collection: (idx item) if test(item): return idx item
  // 105:   return undefined undefined
  frame->slots[5] /* temp__3 */ = create_closure(entry__4_4, 0);
  // 106: :
  // 107:   for_each collection: (item) if test(item): return item
  // 108:   return undefined
  frame->slots[6] /* temp__4 */ = create_closure(entry__4_9, 0);
  // 102: if
  // 103:   parameter_count_of(return) == 2:
  // 104:     for_each collection: (idx item) if test(item): return idx item
  // 105:     return undefined undefined
  // 106:   :
  // 107:     for_each collection: (item) if test(item): return item
  // 108:     return undefined
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  arguments->slots[2] = frame->slots[6] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__4_14;
}
static void entry__4_4(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // collection: 0
  // test: 1
  // return: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* collection */
  frame->slots[1] = myself->closure.frame->slots[1]; /* test */
  frame->slots[2] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 104: ... : (idx item) if test(item): return idx item
  frame->slots[3] /* temp__1 */ = create_closure(entry__4_5, 2);
  // 104: for_each collection: (idx item) if test(item): return idx item
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* collection */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__4_8;
}
static void entry__4_7(void) {
  allocate_initialized_frame_gc(3, 3);
  // slot allocations:
  // return: 0
  // idx: 1
  // item: 2
  frame->slots[0] = myself->closure.frame->slots[3]; /* return */
  frame->slots[1] = myself->closure.frame->slots[0]; /* idx */
  frame->slots[2] = myself->closure.frame->slots[1]; /* item */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 104: ... return idx item
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* idx */;
  arguments->slots[1] = frame->slots[2] /* item */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__4_5(void) {
  allocate_initialized_frame_gc(4, 6);
  // slot allocations:
  // idx: 0
  // item: 1
  // test: 2
  // return: 3
  frame->slots[2] = myself->closure.frame->slots[1]; /* test */
  frame->slots[3] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 104: ... test(item)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* item */;
  result_count = 1;
  myself = frame->slots[2] /* test */;
  func = myself->type;
  frame->cont = cont__4_6;
}
static void cont__4_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 104: ... : return idx item
  frame->slots[5] /* temp__2 */ = create_closure(entry__4_7, 0);
  // 104: ... if test(item): return idx item
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__4_8(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 105: return undefined undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  arguments->slots[1] = get__undefined();
  result_count = frame->caller_result_count;
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__4_9(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // collection: 0
  // test: 1
  // return: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* collection */
  frame->slots[1] = myself->closure.frame->slots[1]; /* test */
  frame->slots[2] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 107: ... : (item) if test(item): return item
  frame->slots[3] /* temp__1 */ = create_closure(entry__4_10, 1);
  // 107: for_each collection: (item) if test(item): return item
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* collection */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__4_13;
}
static void entry__4_12(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // return: 0
  // item: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  frame->slots[1] = myself->closure.frame->slots[0]; /* item */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 107: ... return item
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* item */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__4_10(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // item: 0
  // test: 1
  // return: 2
  frame->slots[1] = myself->closure.frame->slots[1]; /* test */
  frame->slots[2] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 107: ... test(item)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* item */;
  result_count = 1;
  myself = frame->slots[1] /* test */;
  func = myself->type;
  frame->cont = cont__4_11;
}
static void cont__4_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 107: ... : return item
  frame->slots[4] /* temp__2 */ = create_closure(entry__4_12, 0);
  // 107: ... if test(item): return item
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__4_13(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 108: return undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  result_count = frame->caller_result_count;
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__4_14(void) {
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
EXPORT void collect__basic__functional(void) {
  var.std__any_of = collect_node(var.std__any_of);
  var.std__all_of = collect_node(var.std__all_of);
  var.std__fold = collect_node(var.std__fold);
  var.std__find_first = collect_node(var.std__find_first);
}

static int already_run_phase_1 = false;

EXPORT void phase_1__basic__functional(void) {
  if (already_run_phase_1) return;
  already_run_phase_1 = true;
  register_module_info(&module_info);
}

static int already_run_phase_2 = false;

EXPORT void phase_2__basic__functional(void) {
  if (already_run_phase_2) return;
  already_run_phase_2 = true;
  number__2 = from_uint32(2U);
  func__1_1_std__any_of = create_function(entry__1_1_std__any_of, 2);
  func__2_1_std__all_of = create_function(entry__2_1_std__all_of, 2);
  func__3_1_std__fold = create_function(entry__3_1_std__fold, -1);
  func__4_1_std__find_first = create_function(entry__4_1_std__find_first, 2);
}

static int already_run_phase_3 = false;

EXPORT void phase_3__basic__functional(void) {
  if (already_run_phase_3) return;
  already_run_phase_3 = true;
  set_module("basic__functional");
  set_used_namespaces(used_namespaces);
  define_single_assign_static("std", "any_of", get__std__any_of, &var.std__any_of);
  define_single_assign_static("std", "all_of", get__std__all_of, &var.std__all_of);
  define_single_assign_static("std", "fold", get__std__fold, &var.std__fold);
  define_single_assign_static("std", "find_first", get__std__find_first, &var.std__find_first);
}

static int already_run_phase_4 = false;

EXPORT void phase_4__basic__functional(void) {
  if (already_run_phase_4) return;
  already_run_phase_4 = true;
  set_module("basic__functional");
  set_used_namespaces(used_namespaces);
  use_read_only(NULL, "false", &get__false, &get_value_or_future__false);
  use_read_only(NULL, "for_each", &get__for_each, &get_value_or_future__for_each);
  use_read_only(NULL, "if", &get__if, &get_value_or_future__if);
  use_read_only(NULL, "is_defined", &get__is_defined, &get_value_or_future__is_defined);
  use_read_only(NULL, "parameter_count_of", &get__parameter_count_of, &get_value_or_future__parameter_count_of);
  use_read_only("std", "equal", &get__std__equal, &get_value_or_future__std__equal);
  use_read_only(NULL, "true", &get__true, &get_value_or_future__true);
  use_read_only(NULL, "undefined", &get__undefined, &get_value_or_future__undefined);
  use_read_only(NULL, "unless", &get__unless, &get_value_or_future__unless);
}

static int already_run_phase_5 = false;

EXPORT void phase_5__basic__functional(void) {
  if (already_run_phase_5) return;
  already_run_phase_5 = true;
  assign_variable(&var.std__any_of, &func__1_1_std__any_of);
  assign_variable(&var.std__all_of, &func__2_1_std__all_of);
  assign_variable(&var.std__fold, &func__3_1_std__fold);
  assign_variable(&var.std__find_first, &func__4_1_std__find_first);
}

static int already_run_phase_6 = false;

EXPORT void phase_6__basic__functional(void) {
  if (already_run_phase_6) return;
  already_run_phase_6 = true;
  register_collector(collect__basic__functional);
}
