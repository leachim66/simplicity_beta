#include <stdint.h>
#include <stdlib.h>
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
typedef struct SIMPLE_NODE {
  FUNC type;
  struct ATTRIBUTES *attributes;
} SIMPLE_NODE;
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
IMPORT void too_few_arguments_error(void);
IMPORT void too_many_arguments_error(void);
REGISTER FRAME *arguments ASM("r12");
IMPORT void *allocate_memory(size_t size);
IMPORT NODE *from_latin_1_string(const char *str, long len);
IMPORT void deallocate_memory(void *buf);
IMPORT void *node_p;
REGISTER NODE *myself ASM("r13");
IMPORT void invalid_arguments_error(void);
IMPORT int result_count;
IMPORT void invalid_results_error(void);
typedef struct CELL {
  FUNC type;
  struct ATTRIBUTES *attributes;
  NODE *contents;
} CELL;
IMPORT void allocate_arguments(void);
IMPORT NODE *create_cell(void);
IMPORT NODE *create_cell_with_contents(NODE *contents);
IMPORT NODE *from_arguments(int first_idx, int count);
IMPORT NODE *create_closure(FUNC type, int par_count);
IMPORT void collect_garbage();
IMPORT NODE *from_uint64(uint64_t val);
IMPORT uint64_t instruction_counter;
IMPORT NODE *from_int(int val);
IMPORT int total_garbage_collections;
IMPORT NODE *create_future(void);
IMPORT void initialize_future(NODE *var, NODE *val);
IMPORT NODE *collect_node(NODE *node);
IMPORT void register_module_info(MODULE_INFO *info);
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
IMPORT void assign_value(NODE **dest, NODE *val);
IMPORT NODE *from_uint32(uint32_t val);
IMPORT NODE *from_uchar32(unsigned int chr);
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
static NODE_GETTER get__debug_string;
static NODE_GETTER get_value_or_future__debug_string;
static NODE_GETTER get__dup;
static NODE_GETTER get_value_or_future__dup;
static NODE_GETTER get__ewrite;
static NODE_GETTER get_value_or_future__ewrite;
static NODE_GETTER get__for_each_pair;
static NODE_GETTER get_value_or_future__for_each_pair;
static NODE_GETTER get__from_to;
static NODE_GETTER get_value_or_future__from_to;
static NODE_GETTER get__hex;
static NODE_GETTER get_value_or_future__hex;
static NODE_GETTER get__if;
static NODE_GETTER get_value_or_future__if;
static NODE_GETTER get__is_odd;
static NODE_GETTER get_value_or_future__is_odd;
static NODE_GETTER get__length_of;
static NODE_GETTER get_value_or_future__length_of;
static NODE_GETTER get__min;
static NODE_GETTER get_value_or_future__min;
static NODE_GETTER get__pad_left;
static NODE_GETTER get_value_or_future__pad_left;
static NODE_GETTER get__plus;
static NODE_GETTER get_value_or_future__plus;
static NODE_GETTER get__range;
static NODE_GETTER get_value_or_future__range;
static NODE_GETTER get__std__and;
static NODE_GETTER get_value_or_future__std__and;
static NODE_GETTER get__std__less;
static NODE_GETTER get_value_or_future__std__less;
static NODE_GETTER get__std__minus;
static NODE_GETTER get_value_or_future__std__minus;
static NODE_GETTER get__std__negate;
static NODE_GETTER get_value_or_future__std__negate;
static NODE_GETTER get__std__not;
static NODE_GETTER get_value_or_future__std__not;
static NODE_GETTER get__std__plus;
static NODE_GETTER get_value_or_future__std__plus;
static NODE_GETTER get__to_integer;
static NODE_GETTER get_value_or_future__to_integer;
static NODE_GETTER get__while;
static NODE_GETTER get_value_or_future__while;
static NODE_GETTER get__write;
static NODE_GETTER get_value_or_future__write;
static NODE_GETTER get__writeln;
static NODE_GETTER get_value_or_future__writeln;
static struct {
  NODE *std__debug_string;
  NODE *std__dump;
  NODE *std__edump;
  NODE *std__collect_garbage;
  NODE *std__instruction_counter;
  NODE *std__total_garbage_collections;
  NODE *std__hexdump;
} var;
static const char *var_names[] = {
};
static void entry__1_1(void);
static NODE *func__1_1;
static NODE *get__std__debug_string(void) {
  return var.std__debug_string;
}
static NODE *func__2_1;
static void entry__2_1(void);
static FRAME_INFO frame__2_1 = {2, {"args", "depth"}};
static void cont__2_2(void);
static void cont__2_3(void);
static NODE *func__2_4;
static void entry__2_4(void);
static FRAME_INFO frame__2_4 = {2, {"depth", "args"}};
static void cont__2_5(void);
static void cont__2_6(void);
static void cont__2_7(void);
static void cont__2_8(void);
static NODE *func__2_9;
static void entry__2_9(void);
static FRAME_INFO frame__2_9 = {3, {"name", "expr", "depth"}};
static void cont__2_10(void);
static void cont__2_11(void);
static NODE *string__2_12;
static NODE *get__std__dump(void) {
  return var.std__dump;
}
static NODE *func__3_1;
static void entry__3_1(void);
static FRAME_INFO frame__3_1 = {2, {"args", "depth"}};
static void cont__3_2(void);
static void cont__3_3(void);
static NODE *func__3_4;
static void entry__3_4(void);
static FRAME_INFO frame__3_4 = {2, {"depth", "args"}};
static void cont__3_5(void);
static void cont__3_6(void);
static void cont__3_7(void);
static void cont__3_8(void);
static NODE *func__3_9;
static void entry__3_9(void);
static FRAME_INFO frame__3_9 = {3, {"name", "expr", "depth"}};
static void cont__3_10(void);
static void cont__3_11(void);
static NODE *string__3_12;
static NODE *get__std__edump(void) {
  return var.std__edump;
}
static void entry__4_1(void);
static NODE *func__4_1;
static NODE *get__std__collect_garbage(void) {
  return var.std__collect_garbage;
}
static void entry__5_1(void);
static NODE *func__5_1;
static NODE *get__std__instruction_counter(void) {
  return var.std__instruction_counter;
}
static void entry__6_1(void);
static NODE *func__6_1;
static NODE *get__std__total_garbage_collections(void) {
  return var.std__total_garbage_collections;
}
static NODE *func__7_1;
static void entry__7_1(void);
static FRAME_INFO frame__7_1 = {3, {"str", "len", "pos"}};
static void cont__7_2(void);
static NODE *func__7_3;
static void entry__7_3(void);
static FRAME_INFO frame__7_3 = {3, {"pos", "len", "str"}};
static void cont__7_4(void);
static NODE *func__7_5;
static void entry__7_5(void);
static FRAME_INFO frame__7_5 = {5, {"len", "pos", "str", "n", "line"}};
static void cont__7_6(void);
static void cont__7_7(void);
static void cont__7_8(void);
static void cont__7_9(void);
static void cont__7_10(void);
static void cont__7_11(void);
static NODE *string__7_12;
static void cont__7_13(void);
static NODE *string__7_14;
static void cont__7_15(void);
static NODE *func__7_16;
static void entry__7_16(void);
static FRAME_INFO frame__7_16 = {2, {"i", "line"}};
static void cont__7_17(void);
static void cont__7_18(void);
static void cont__7_19(void);
static NODE *string__7_20;
static void cont__7_21(void);
static NODE *string__7_22;
static void cont__7_23(void);
static void cont__7_24(void);
static NODE *string__7_25;
static void cont__7_26(void);
static NODE *string__7_27;
static void cont__7_28(void);
static NODE *func__7_29;
static void entry__7_29(void);
static FRAME_INFO frame__7_29 = {3, {"i", "line", "chr"}};
static void cont__7_30(void);
static void cont__7_31(void);
static void cont__7_32(void);
static NODE *func__7_33;
static void entry__7_33(void);
static FRAME_INFO frame__7_33 = {1, {"chr"}};
static void cont__7_34(void);
static void cont__7_35(void);
static NODE *func__7_36;
static void entry__7_36(void);
static FRAME_INFO frame__7_36 = {1, {"chr"}};
static NODE *func__7_37;
static void entry__7_37(void);
static FRAME_INFO frame__7_37 = {0, {}};
static NODE *string__7_38;
static void cont__7_39(void);
static void cont__7_40(void);
static void cont__7_41(void);
static NODE *get__std__hexdump(void) {
  return var.std__hexdump;
}
void run__basic__debug(void);

static CONTINUATION_INFO continuation_info[] = {
  {run__basic__debug, NULL, },
  {entry__1_1, NULL, 45, 64, 3, 2},
  {entry__2_4, NULL, 85, 85, 5, 18},
  {cont__2_5, &frame__2_4, 86, 86, 20, 20},
  {cont__2_6, &frame__2_4, 86, 86, 5, 20},
  {cont__2_7, &frame__2_4, 86, 86, 20, 20},
  {entry__2_9, NULL, 87, 87, 69, 69},
  {cont__2_10, &frame__2_9, 87, 87, 50, 76},
  {cont__2_11, &frame__2_9, 87, 87, 35, 76},
  {entry__2_1, NULL, 84, 84, 6, 20},
  {cont__2_2, &frame__2_1, 84, 84, 6, 27},
  {cont__2_3, &frame__2_1, 84, 86, 3, 20},
  {cont__2_8, &frame__2_1, 87, 87, 3, 76},
  {entry__3_4, NULL, 108, 108, 5, 18},
  {cont__3_5, &frame__3_4, 109, 109, 20, 20},
  {cont__3_6, &frame__3_4, 109, 109, 5, 20},
  {cont__3_7, &frame__3_4, 109, 109, 20, 20},
  {entry__3_9, NULL, 110, 110, 70, 70},
  {cont__3_10, &frame__3_9, 110, 110, 51, 77},
  {cont__3_11, &frame__3_9, 110, 110, 35, 77},
  {entry__3_1, NULL, 107, 107, 6, 20},
  {cont__3_2, &frame__3_1, 107, 107, 6, 27},
  {cont__3_3, &frame__3_1, 107, 109, 3, 20},
  {cont__3_8, &frame__3_1, 110, 110, 3, 77},
  {entry__4_1, NULL, 113, 117, 3, 2},
  {entry__5_1, NULL, 125, 128, 3, 2},
  {entry__6_1, NULL, 131, 134, 3, 2},
  {entry__7_16, NULL, 143, 143, 45, 51},
  {cont__7_17, &frame__7_16, 143, 143, 45, 62},
  {cont__7_18, &frame__7_16, 143, 143, 41, 63},
  {cont__7_19, &frame__7_16, 143, 143, 32, 70},
  {cont__7_21, &frame__7_16, 143, 143, 22, 70},
  {entry__7_33, NULL, 148, 148, 23, 35},
  {cont__7_34, &frame__7_33, 148, 148, 23, 35},
  {entry__7_36, NULL, 149, 149, 11, 19},
  {entry__7_37, NULL, 151, 151, 11, 19},
  {entry__7_29, NULL, 146, 146, 7, 18},
  {cont__7_30, &frame__7_29, 148, 148, 9, 18},
  {cont__7_31, &frame__7_29, 148, 148, 9, 18},
  {cont__7_32, &frame__7_29, 148, 148, 9, 35},
  {cont__7_35, &frame__7_29, 147, 151, 7, 20},
  {entry__7_5, NULL, 140, 140, 12, 18},
  {cont__7_6, &frame__7_5, 140, 140, 5, 22},
  {cont__7_7, &frame__7_5, 141, 141, 21, 25},
  {cont__7_8, &frame__7_5, 141, 141, 27, 31},
  {cont__7_9, &frame__7_5, 141, 141, 5, 32},
  {cont__7_10, &frame__7_5, 142, 142, 20, 27},
  {cont__7_11, &frame__7_5, 142, 142, 11, 34},
  {cont__7_13, &frame__7_5, 142, 142, 5, 38},
  {cont__7_15, &frame__7_5, 143, 143, 5, 70},
  {cont__7_23, &frame__7_5, 144, 144, 21, 24},
  {cont__7_24, &frame__7_5, 144, 144, 11, 25},
  {cont__7_26, &frame__7_5, 144, 144, 5, 30},
  {cont__7_28, &frame__7_5, 145, 151, 5, 21},
  {cont__7_39, &frame__7_5, 152, 152, 5, 11},
  {cont__7_40, &frame__7_5, 153, 153, 5, 15},
  {cont__7_41, &frame__7_5, 153, 153, 15, 15},
  {entry__7_3, NULL, 139, 139, 12, 20},
  {cont__7_4, &frame__7_3, 139, 153, 9, 15},
  {entry__7_1, NULL, 137, 137, 3, 21},
  {cont__7_2, &frame__7_1, 139, 153, 3, 15}
};

union NODE {
  struct {
    FUNC type;
    ATTRIBUTES *attributes;
  };
  CONTINUATION continuation;
  CLOSURE closure;
  SIMPLE_NODE simple_node;
};
static NODE *number__0;
static NODE *number__8;
static NODE *number__16;
static NODE *character__32;
static NODE *character__127;
static NODE *number__1;
static NODE *number__2;

static const char *used_namespaces[] = {
  "std",
  NULL
};

static MODULE_INFO module_info = {
  NULL,
  "basic__debug",
  continuation_info,
  sizeof(continuation_info)/sizeof(CONTINUATION_INFO),
  (NODE **)&var,
  var_names,
  sizeof(var_names)/sizeof(const char *),
  used_namespaces,
  {DEBUG_FILENAME("basic/debug.sim")}
};

/******
C O D E
******/

static int already_run = false;

EXPORT void run__basic__debug(void) {
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
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  if (argument_count > 3) {
    too_many_arguments_error();
    return;
  }

  NODE *node = arguments->slots[0];
  int indent = 0;
  int depth = 1;
  if (argument_count >= 2) {
    indent = to_int(arguments->slots[1]);
  }
  if (argument_count >= 3) {
    depth = to_int(arguments->slots[2]);
  }
  long len = debug_string(node, indent, depth, NULL);
  char *buf = allocate_memory(len+1); // obey terminating null-byte
  len = debug_string(node, indent, depth, buf);
  NODE *result = from_latin_1_string(buf, len);
  deallocate_memory(buf);
  {
    NODE *result__node = (NODE *)(result);
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  };
}
static void entry__2_9(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // name: 0
  // expr: 1
  // depth: 2
  frame->slots[2] = myself->closure.frame->slots[1]; /* depth */
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 87: ... 2
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__2_10;
}
static void cont__2_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 87: ... debug_string(expr -2 depth)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* expr */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  arguments->slots[2] = ((CELL *)frame->slots[2])->contents /* depth */;
  result_count = 1;
  myself = get__debug_string();
  func = myself->type;
  frame->cont = cont__2_11;
}
static void cont__2_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 87: ... write name ":" debug_string(expr -2 depth)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = string__2_12;
  arguments->slots[2] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__2_1(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // args: 0
  // depth: 1
  frame->slots[1] /* depth */ = create_cell();
  frame->slots[0] /* args */ = create_cell_with_contents(from_arguments(0, argument_count-0));
  // 83: $$depth 1
  ((CELL *)frame->slots[1])->contents /* depth */ = number__1;
  // 84: ... length_of(args)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* args */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__2_2;
}
static void cont__2_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 84: ... length_of(args).is_odd
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__is_odd();
  func = myself->type;
  frame->cont = cont__2_3;
}
static void cont__2_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 84: ... :
  // 85:   !depth args(1)
  // 86:   range &args 2 -1
  frame->slots[4] /* temp__3 */ = create_closure(entry__2_4, 0);
  // 84: if length_of(args).is_odd:
  // 85:   !depth args(1)
  // 86:   range &args 2 -1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__2_8;
}
static void entry__2_4(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // depth: 0
  // args: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* depth */
  frame->slots[1] = myself->closure.frame->slots[0]; /* args */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 85: !depth args(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = ((CELL *)frame->slots[1])->contents /* args */;
  func = myself->type;
  frame->cont = cont__2_5;
}
static void cont__2_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* depth */ = arguments->slots[0];
  // 86: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__2_6;
}
static void cont__2_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 86: range &args 2 -1
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* args */;
  arguments->slots[1] = number__2;
  arguments->slots[2] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__2_7;
}
static void cont__2_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* args */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__2_8(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 87: ... : (name expr) write name ":" debug_string(expr -2 depth)
  frame->slots[2] /* temp__1 */ = create_closure(entry__2_9, 2);
  // 87: for_each_pair args: (name expr) write name ":" debug_string(expr -2 depth)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* args */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each_pair();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__3_9(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // name: 0
  // expr: 1
  // depth: 2
  frame->slots[2] = myself->closure.frame->slots[1]; /* depth */
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 110: ... 2
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__3_10;
}
static void cont__3_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 110: ... debug_string(expr -2 depth)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* expr */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  arguments->slots[2] = ((CELL *)frame->slots[2])->contents /* depth */;
  result_count = 1;
  myself = get__debug_string();
  func = myself->type;
  frame->cont = cont__3_11;
}
static void cont__3_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 110: ... ewrite name ":" debug_string(expr -2 depth)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = string__3_12;
  arguments->slots[2] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__ewrite();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__3_1(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // args: 0
  // depth: 1
  frame->slots[1] /* depth */ = create_cell();
  frame->slots[0] /* args */ = create_cell_with_contents(from_arguments(0, argument_count-0));
  // 106: $$depth 1
  ((CELL *)frame->slots[1])->contents /* depth */ = number__1;
  // 107: ... length_of(args)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* args */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__3_2;
}
static void cont__3_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 107: ... length_of(args).is_odd
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__is_odd();
  func = myself->type;
  frame->cont = cont__3_3;
}
static void cont__3_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 107: ... :
  // 108:   !depth args(1)
  // 109:   range &args 2 -1
  frame->slots[4] /* temp__3 */ = create_closure(entry__3_4, 0);
  // 107: if length_of(args).is_odd:
  // 108:   !depth args(1)
  // 109:   range &args 2 -1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__3_8;
}
static void entry__3_4(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // depth: 0
  // args: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* depth */
  frame->slots[1] = myself->closure.frame->slots[0]; /* args */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 108: !depth args(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = ((CELL *)frame->slots[1])->contents /* args */;
  func = myself->type;
  frame->cont = cont__3_5;
}
static void cont__3_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* depth */ = arguments->slots[0];
  // 109: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__3_6;
}
static void cont__3_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 109: range &args 2 -1
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* args */;
  arguments->slots[1] = number__2;
  arguments->slots[2] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__3_7;
}
static void cont__3_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* args */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__3_8(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 110: ... : (name expr) ewrite name ":" debug_string(expr -2 depth)
  frame->slots[2] /* temp__1 */ = create_closure(entry__3_9, 2);
  // 110: for_each_pair args: (name expr) ewrite name ":" debug_string(expr -2 depth)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* args */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each_pair();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__4_1(void) {
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  collect_garbage();
  {
    argument_count = 0;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__5_1(void) {
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  {
    NODE *result__node = (NODE *)(from_uint64(instruction_counter));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__6_1(void) {
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  {
    NODE *result__node = (NODE *)(from_int(total_garbage_collections));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__7_5(void) {
  allocate_initialized_frame_gc(3, 7);
  // slot allocations:
  // len: 0
  // pos: 1
  // str: 2
  // n: 3
  // line: 4
  frame->slots[0] = myself->closure.frame->slots[1]; /* len */
  frame->slots[1] = myself->closure.frame->slots[0]; /* pos */
  frame->slots[2] = myself->closure.frame->slots[2]; /* str */
  frame->slots[3] /* n */ = create_future();
  frame->slots[4] /* line */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 140: ... len-pos
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* len */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* pos */;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__7_6;
}
static void cont__7_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 140: $n min(len-pos 16)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = number__16;
  result_count = 1;
  myself = get__min();
  func = myself->type;
  frame->cont = cont__7_7;
}
static void cont__7_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* n */, arguments->slots[0]);
  // 141: ... pos+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* pos */;
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
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 141: ... pos+n
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* pos */;
  arguments->slots[1] = frame->slots[3] /* n */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__7_9;
}
static void cont__7_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 141: $line range(str pos+1 pos+n)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* str */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  arguments->slots[2] = frame->slots[6] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__7_10;
}
static void cont__7_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* line */, arguments->slots[0]);
  // 142: ... hex(pos)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* pos */;
  result_count = 1;
  myself = get__hex();
  func = myself->type;
  frame->cont = cont__7_11;
}
static void cont__7_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 142: ... pad_left(hex(pos) 8 "0")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = number__8;
  arguments->slots[2] = string__7_12;
  result_count = 1;
  myself = get__pad_left();
  func = myself->type;
  frame->cont = cont__7_13;
}
static void cont__7_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 142: write pad_left(hex(pos) 8 "0") ":"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = string__7_14;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__7_15;
}
static void cont__7_15(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 143: ... : (i) write " " pad_left(hex(line(i).to_integer) 2 "0")
  frame->slots[5] /* temp__1 */ = create_closure(entry__7_16, 1);
  // 143: from_to 1 n: (i) write " " pad_left(hex(line(i).to_integer) 2 "0")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = number__1;
  arguments->slots[1] = frame->slots[3] /* n */;
  arguments->slots[2] = frame->slots[5] /* temp__1 */;
  result_count = 0;
  myself = get__from_to();
  func = myself->type;
  frame->cont = cont__7_23;
}
static void entry__7_16(void) {
  allocate_initialized_frame_gc(2, 6);
  // slot allocations:
  // i: 0
  // line: 1
  frame->slots[1] = myself->closure.frame->slots[4]; /* line */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 143: ... line(i)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* i */;
  result_count = 1;
  myself = frame->slots[1] /* line */;
  func = myself->type;
  frame->cont = cont__7_17;
}
static void cont__7_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__4 */ = arguments->slots[0];
  // 143: ... line(i).to_integer
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__4 */;
  result_count = 1;
  myself = get__to_integer();
  func = myself->type;
  frame->cont = cont__7_18;
}
static void cont__7_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 143: ... hex(line(i).to_integer)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__hex();
  func = myself->type;
  frame->cont = cont__7_19;
}
static void cont__7_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 143: ... pad_left(hex(line(i).to_integer) 2 "0")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = number__2;
  arguments->slots[2] = string__7_20;
  result_count = 1;
  myself = get__pad_left();
  func = myself->type;
  frame->cont = cont__7_21;
}
static void cont__7_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 143: ... write " " pad_left(hex(line(i).to_integer) 2 "0")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__7_22;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_23(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 144: ... 16-n
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__16;
  arguments->slots[1] = frame->slots[3] /* n */;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__7_24;
}
static void cont__7_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 144: ... dup("   " 16-n)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__7_25;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = 1;
  myself = get__dup();
  func = myself->type;
  frame->cont = cont__7_26;
}
static void cont__7_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 144: write dup("   " 16-n) "  "
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = string__7_27;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__7_28;
}
static void cont__7_28(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 145: ... : (i)
  // 146:   $chr line(i)
  // 147:   if
  // 148:     chr >= ' ' && chr < '@del;':
  // 149:       write chr
  // 150:     :
  // 151:       write "."
  frame->slots[5] /* temp__1 */ = create_closure(entry__7_29, 1);
  // 145: from_to 1 n: (i)
  // 146:   $chr line(i)
  // 147:   if
  // 148:     chr >= ' ' && chr < '@del;':
  // 149:       write chr
  // 150:     :
  // 151:       write "."
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = number__1;
  arguments->slots[1] = frame->slots[3] /* n */;
  arguments->slots[2] = frame->slots[5] /* temp__1 */;
  result_count = 0;
  myself = get__from_to();
  func = myself->type;
  frame->cont = cont__7_39;
}
static void entry__7_36(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 149: write chr
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_37(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 151: write "."
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__7_38;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_29(void) {
  allocate_initialized_frame_gc(2, 8);
  // slot allocations:
  // i: 0
  // line: 1
  // chr: 2
  frame->slots[1] = myself->closure.frame->slots[4]; /* line */
  frame->slots[2] /* chr */ = create_future();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 146: $chr line(i)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* i */;
  result_count = 1;
  myself = frame->slots[1] /* line */;
  func = myself->type;
  frame->cont = cont__7_30;
}
static void cont__7_30(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* chr */, arguments->slots[0]);
  // 148: chr >= ' '
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* chr */;
  arguments->slots[1] = character__32;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__7_31;
}
static void cont__7_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 148: chr >= ' '
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__7_32;
}
static void cont__7_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 148: ... chr < '@del;'
  frame->slots[6] /* temp__4 */ = create_closure(entry__7_33, 0);
  // 148: chr >= ' ' && chr < '@del;'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[6] /* temp__4 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__7_35;
}
static void entry__7_33(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 148: ... chr < '@del;'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  arguments->slots[1] = character__127;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__7_34;
}
static void cont__7_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 148: ... chr < '@del;'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__7_35(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 148: ... :
  // 149:   write chr
  frame->slots[7] /* temp__5 */ = create_closure(entry__7_36, 0);
  // 147: if
  // 148:   chr >= ' ' && chr < '@del;':
  // 149:     write chr
  // 150:   :
  // 151:     write "."
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__5 */;
  arguments->slots[2] = func__7_37;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_39(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 152: writeln
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = get__writeln();
  func = myself->type;
  frame->cont = cont__7_40;
}
static void cont__7_40(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 153: plus &pos n
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* pos */;
  arguments->slots[1] = frame->slots[3] /* n */;
  result_count = 1;
  myself = get__plus();
  func = myself->type;
  frame->cont = cont__7_41;
}
static void cont__7_41(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* pos */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__7_3(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // pos: 0
  // len: 1
  // str: 2
  frame->slots[0] = myself->closure.frame->slots[2]; /* pos */
  frame->slots[1] = myself->closure.frame->slots[1]; /* len */
  frame->slots[2] = myself->closure.frame->slots[0]; /* str */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 139: ... pos < len
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* pos */;
  arguments->slots[1] = frame->slots[1] /* len */;
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
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 139: ... :
  // 140:   $n min(len-pos 16)
  // 141:   $line range(str pos+1 pos+n)
  // 142:   write pad_left(hex(pos) 8 "0") ":"
  // 143:   from_to 1 n: (i) write " " pad_left(hex(line(i).to_integer) 2 "0")
  // 144:   write dup("   " 16-n) "  "
  // 145:   from_to 1 n: (i)
  // 146:     $chr line(i)
  // 147:     if
  // 148:       chr >= ' ' && chr < '@del;':
  // ...
  frame->slots[4] /* temp__2 */ = create_closure(entry__7_5, 0);
  // 139: ... -> pos < len:
  // 140:   $n min(len-pos 16)
  // 141:   $line range(str pos+1 pos+n)
  // 142:   write pad_left(hex(pos) 8 "0") ":"
  // 143:   from_to 1 n: (i) write " " pad_left(hex(line(i).to_integer) 2 "0")
  // 144:   write dup("   " 16-n) "  "
  // 145:   from_to 1 n: (i)
  // 146:     $chr line(i)
  // 147:     if
  // 148:       chr >= ' ' && chr < '@del;':
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__7_1(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // str: 0
  // len: 1
  // pos: 2
  frame->slots[1] /* len */ = create_future();
  frame->slots[2] /* pos */ = create_cell();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 137: $len length_of(str)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* str */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__7_2;
}
static void cont__7_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* len */, arguments->slots[0]);
  // 138: $$pos 0
  ((CELL *)frame->slots[2])->contents /* pos */ = number__0;
  // 139: ... -> pos < len:
  // 140:   $n min(len-pos 16)
  // 141:   $line range(str pos+1 pos+n)
  // 142:   write pad_left(hex(pos) 8 "0") ":"
  // 143:   from_to 1 n: (i) write " " pad_left(hex(line(i).to_integer) 2 "0")
  // 144:   write dup("   " 16-n) "  "
  // 145:   from_to 1 n: (i)
  // 146:     $chr line(i)
  // 147:     if
  // 148:       chr >= ' ' && chr < '@del;':
  // ...
  frame->slots[3] /* temp__1 */ = create_closure(entry__7_3, 0);
  // 139: while -> pos < len:
  // 140:   $n min(len-pos 16)
  // 141:   $line range(str pos+1 pos+n)
  // 142:   write pad_left(hex(pos) 8 "0") ":"
  // 143:   from_to 1 n: (i) write " " pad_left(hex(line(i).to_integer) 2 "0")
  // 144:   write dup("   " 16-n) "  "
  // 145:   from_to 1 n: (i)
  // 146:     $chr line(i)
  // 147:     if
  // 148:       chr >= ' ' && chr < '@del;':
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__while();
  func = myself->type;
  frame = frame->caller_frame;
}
EXPORT void collect__basic__debug(void) {
  var.std__debug_string = collect_node(var.std__debug_string);
  var.std__dump = collect_node(var.std__dump);
  string__2_12 = collect_node(string__2_12);
  func__2_1 = collect_node(func__2_1);
  var.std__edump = collect_node(var.std__edump);
  string__3_12 = collect_node(string__3_12);
  func__3_1 = collect_node(func__3_1);
  var.std__collect_garbage = collect_node(var.std__collect_garbage);
  var.std__instruction_counter = collect_node(var.std__instruction_counter);
  var.std__total_garbage_collections = collect_node(var.std__total_garbage_collections);
  var.std__hexdump = collect_node(var.std__hexdump);
  string__7_12 = collect_node(string__7_12);
  string__7_14 = collect_node(string__7_14);
  string__7_20 = collect_node(string__7_20);
  string__7_22 = collect_node(string__7_22);
  string__7_25 = collect_node(string__7_25);
  string__7_27 = collect_node(string__7_27);
  string__7_38 = collect_node(string__7_38);
  func__7_37 = collect_node(func__7_37);
  func__7_1 = collect_node(func__7_1);
  number__0 = collect_node(number__0);
  number__8 = collect_node(number__8);
  number__16 = collect_node(number__16);
  character__32 = collect_node(character__32);
  character__127 = collect_node(character__127);
  number__1 = collect_node(number__1);
  number__2 = collect_node(number__2);
}

static int already_run_phase_1 = false;

EXPORT void phase_1__basic__debug(void) {
  if (already_run_phase_1) return;
  already_run_phase_1 = true;
  register_module_info(&module_info);
}

static int already_run_phase_2 = false;

EXPORT void phase_2__basic__debug(void) {
  if (already_run_phase_2) return;
  already_run_phase_2 = true;
  set_module("basic__debug");
  set_used_namespaces(used_namespaces);
  number__0 = create_future();
  number__8 = create_future();
  number__16 = create_future();
  character__32 = create_future();
  character__127 = create_future();
  number__1 = create_future();
  number__2 = create_future();
  func__1_1 = create_future();
  define_single_assign_static("std", "debug_string", get__std__debug_string, &var.std__debug_string);
  string__2_12 = from_latin_1_string(":", 1);
  func__2_1 = create_future();
  define_single_assign_static("std", "dump", get__std__dump, &var.std__dump);
  string__3_12 = from_latin_1_string(":", 1);
  func__3_1 = create_future();
  define_single_assign_static("std", "edump", get__std__edump, &var.std__edump);
  func__4_1 = create_future();
  define_single_assign_static("std", "collect_garbage", get__std__collect_garbage, &var.std__collect_garbage);
  func__5_1 = create_future();
  define_single_assign_static("std", "instruction_counter", get__std__instruction_counter, &var.std__instruction_counter);
  func__6_1 = create_future();
  define_single_assign_static("std", "total_garbage_collections", get__std__total_garbage_collections, &var.std__total_garbage_collections);
  string__7_12 = from_latin_1_string("0", 1);
  string__7_14 = from_latin_1_string(":", 1);
  string__7_20 = from_latin_1_string("0", 1);
  string__7_22 = from_latin_1_string(" ", 1);
  string__7_25 = from_latin_1_string("   ", 3);
  string__7_27 = from_latin_1_string("  ", 2);
  string__7_38 = from_latin_1_string(".", 1);
  func__7_37 = create_future();
  func__7_1 = create_future();
  define_single_assign_static("std", "hexdump", get__std__hexdump, &var.std__hexdump);
}

static int already_run_phase_3 = false;

EXPORT void phase_3__basic__debug(void) {
  if (already_run_phase_3) return;
  already_run_phase_3 = true;
  set_module("basic__debug");
  set_used_namespaces(used_namespaces);
  use_read_only(NULL, "debug_string", &get__debug_string, &get_value_or_future__debug_string);
  use_read_only(NULL, "dup", &get__dup, &get_value_or_future__dup);
  use_read_only(NULL, "ewrite", &get__ewrite, &get_value_or_future__ewrite);
  use_read_only(NULL, "for_each_pair", &get__for_each_pair, &get_value_or_future__for_each_pair);
  use_read_only(NULL, "from_to", &get__from_to, &get_value_or_future__from_to);
  use_read_only(NULL, "hex", &get__hex, &get_value_or_future__hex);
  use_read_only(NULL, "if", &get__if, &get_value_or_future__if);
  use_read_only(NULL, "is_odd", &get__is_odd, &get_value_or_future__is_odd);
  use_read_only(NULL, "length_of", &get__length_of, &get_value_or_future__length_of);
  use_read_only(NULL, "min", &get__min, &get_value_or_future__min);
  use_read_only(NULL, "pad_left", &get__pad_left, &get_value_or_future__pad_left);
  use_read_only(NULL, "plus", &get__plus, &get_value_or_future__plus);
  use_read_only(NULL, "range", &get__range, &get_value_or_future__range);
  use_read_only("std", "and", &get__std__and, &get_value_or_future__std__and);
  use_read_only("std", "less", &get__std__less, &get_value_or_future__std__less);
  use_read_only("std", "minus", &get__std__minus, &get_value_or_future__std__minus);
  use_read_only("std", "negate", &get__std__negate, &get_value_or_future__std__negate);
  use_read_only("std", "not", &get__std__not, &get_value_or_future__std__not);
  use_read_only("std", "plus", &get__std__plus, &get_value_or_future__std__plus);
  use_read_only(NULL, "to_integer", &get__to_integer, &get_value_or_future__to_integer);
  use_read_only(NULL, "while", &get__while, &get_value_or_future__while);
  use_read_only(NULL, "write", &get__write, &get_value_or_future__write);
  use_read_only(NULL, "writeln", &get__writeln, &get_value_or_future__writeln);
}

static int already_run_phase_4 = false;

EXPORT void phase_4__basic__debug(void) {
  if (already_run_phase_4) return;
  already_run_phase_4 = true;
  assign_value(&number__0, from_uint32(0U));
  assign_value(&number__8, from_uint32(8U));
  assign_value(&number__16, from_uint32(16U));
  assign_value(&character__32, from_uchar32(32));
  assign_value(&character__127, from_uchar32(127));
  assign_value(&number__1, from_uint32(1U));
  assign_value(&number__2, from_uint32(2U));
  assign_variable(&var.std__debug_string, &func__1_1);
  assign_variable(&var.std__dump, &func__2_1);
  assign_variable(&var.std__edump, &func__3_1);
  assign_variable(&var.std__collect_garbage, &func__4_1);
  assign_variable(&var.std__instruction_counter, &func__5_1);
  assign_variable(&var.std__total_garbage_collections, &func__6_1);
  assign_variable(&var.std__hexdump, &func__7_1);
}

static int already_run_phase_5 = false;

EXPORT void phase_5__basic__debug(void) {
  if (already_run_phase_5) return;
  already_run_phase_5 = true;
  assign_value(&func__1_1, create_function(entry__1_1, -1));
  assign_value(&func__2_1, create_function(entry__2_1, -1));
  assign_value(&func__3_1, create_function(entry__3_1, -1));
  assign_value(&func__4_1, create_function(entry__4_1, 0));
  assign_value(&func__5_1, create_function(entry__5_1, 0));
  assign_value(&func__6_1, create_function(entry__6_1, 0));
  assign_value(&func__7_37, create_function(entry__7_37, 0));
  assign_value(&func__7_1, create_function(entry__7_1, 1));
  register_collector(collect__basic__debug);
}
