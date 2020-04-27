#include <runtime/platform.h>
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
IMPORT NODE *from_uint32(uint32_t val);
IMPORT NODE *from_uchar32(unsigned int chr);
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
static void entry__1_1_std__debug_string(void);
static NODE *func__1_1_std__debug_string;
static NODE *get__std__debug_string(void) {
  return var.std__debug_string;
}
static NODE *func__2_1_std__dump;
static void entry__2_1_std__dump(void);
static FRAME_INFO frame__2_1_std__dump = {2, {"args", "depth"}};
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
static NODE *string__578a5af303e9cdb;
static NODE *get__std__dump(void) {
  return var.std__dump;
}
static NODE *func__3_1_std__edump;
static void entry__3_1_std__edump(void);
static FRAME_INFO frame__3_1_std__edump = {2, {"args", "depth"}};
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
static NODE *get__std__edump(void) {
  return var.std__edump;
}
static void entry__4_1_std__collect_garbage(void);
static NODE *func__4_1_std__collect_garbage;
static NODE *get__std__collect_garbage(void) {
  return var.std__collect_garbage;
}
static void entry__5_1_std__instruction_counter(void);
static NODE *func__5_1_std__instruction_counter;
static NODE *get__std__instruction_counter(void) {
  return var.std__instruction_counter;
}
static void entry__6_1_std__total_garbage_collections(void);
static NODE *func__6_1_std__total_garbage_collections;
static NODE *get__std__total_garbage_collections(void) {
  return var.std__total_garbage_collections;
}
static NODE *func__7_1_std__hexdump;
static void entry__7_1_std__hexdump(void);
static FRAME_INFO frame__7_1_std__hexdump = {3, {"str", "len", "pos"}};
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
static NODE *string__578a5af303e9cd1;
static void cont__7_13(void);
static void cont__7_14(void);
static NODE *func__7_15;
static void entry__7_15(void);
static FRAME_INFO frame__7_15 = {2, {"i", "line"}};
static void cont__7_16(void);
static void cont__7_17(void);
static void cont__7_18(void);
static void cont__7_19(void);
static NODE *string__578a5af303e9cc1;
static void cont__7_21(void);
static void cont__7_22(void);
static NODE *string__fa730415f296bec;
static void cont__7_24(void);
static NODE *string__2d7981f4e6082be5;
static void cont__7_26(void);
static NODE *func__7_27;
static void entry__7_27(void);
static FRAME_INFO frame__7_27 = {3, {"i", "line", "chr"}};
static void cont__7_28(void);
static void cont__7_29(void);
static void cont__7_30(void);
static NODE *func__7_31;
static void entry__7_31(void);
static FRAME_INFO frame__7_31 = {1, {"chr"}};
static void cont__7_32(void);
static void cont__7_33(void);
static NODE *func__7_34;
static void entry__7_34(void);
static FRAME_INFO frame__7_34 = {1, {"chr"}};
static NODE *func__7_35;
static void entry__7_35(void);
static FRAME_INFO frame__7_35 = {0, {}};
static NODE *string__578a5af303e9ccf;
static void cont__7_37(void);
static void cont__7_38(void);
static void cont__7_39(void);
static NODE *get__std__hexdump(void) {
  return var.std__hexdump;
}
void run__basic__debug(void);

static CONTINUATION_INFO continuation_info[] = {
  {run__basic__debug, NULL, },
  {entry__1_1_std__debug_string, NULL, 47, 66, 3, 2},
  {entry__2_4, NULL, 89, 89, 5, 18},
  {cont__2_5, &frame__2_4, 90, 90, 20, 20},
  {cont__2_6, &frame__2_4, 90, 90, 5, 20},
  {cont__2_7, &frame__2_4, 90, 90, 20, 20},
  {entry__2_9, NULL, 91, 91, 69, 69},
  {cont__2_10, &frame__2_9, 91, 91, 50, 76},
  {cont__2_11, &frame__2_9, 91, 91, 35, 76},
  {entry__2_1_std__dump, NULL, 88, 88, 6, 20},
  {cont__2_2, &frame__2_1_std__dump, 88, 88, 6, 27},
  {cont__2_3, &frame__2_1_std__dump, 88, 90, 3, 20},
  {cont__2_8, &frame__2_1_std__dump, 91, 91, 3, 76},
  {entry__3_4, NULL, 114, 114, 5, 18},
  {cont__3_5, &frame__3_4, 115, 115, 20, 20},
  {cont__3_6, &frame__3_4, 115, 115, 5, 20},
  {cont__3_7, &frame__3_4, 115, 115, 20, 20},
  {entry__3_9, NULL, 116, 116, 70, 70},
  {cont__3_10, &frame__3_9, 116, 116, 51, 77},
  {cont__3_11, &frame__3_9, 116, 116, 35, 77},
  {entry__3_1_std__edump, NULL, 113, 113, 6, 20},
  {cont__3_2, &frame__3_1_std__edump, 113, 113, 6, 27},
  {cont__3_3, &frame__3_1_std__edump, 113, 115, 3, 20},
  {cont__3_8, &frame__3_1_std__edump, 116, 116, 3, 77},
  {entry__4_1_std__collect_garbage, NULL, 126, 130, 3, 2},
  {entry__5_1_std__instruction_counter, NULL, 145, 148, 3, 2},
  {entry__6_1_std__total_garbage_collections, NULL, 158, 161, 3, 2},
  {entry__7_15, NULL, 175, 175, 45, 51},
  {cont__7_16, &frame__7_15, 175, 175, 45, 62},
  {cont__7_17, &frame__7_15, 175, 175, 41, 63},
  {cont__7_18, &frame__7_15, 175, 175, 32, 70},
  {cont__7_19, &frame__7_15, 175, 175, 22, 70},
  {entry__7_31, NULL, 180, 180, 23, 35},
  {cont__7_32, &frame__7_31, 180, 180, 23, 35},
  {entry__7_34, NULL, 181, 181, 11, 19},
  {entry__7_35, NULL, 183, 183, 11, 19},
  {entry__7_27, NULL, 178, 178, 7, 18},
  {cont__7_28, &frame__7_27, 180, 180, 9, 18},
  {cont__7_29, &frame__7_27, 180, 180, 9, 18},
  {cont__7_30, &frame__7_27, 180, 180, 9, 35},
  {cont__7_33, &frame__7_27, 179, 183, 7, 20},
  {entry__7_5, NULL, 172, 172, 12, 18},
  {cont__7_6, &frame__7_5, 172, 172, 5, 22},
  {cont__7_7, &frame__7_5, 173, 173, 21, 25},
  {cont__7_8, &frame__7_5, 173, 173, 27, 31},
  {cont__7_9, &frame__7_5, 173, 173, 5, 32},
  {cont__7_10, &frame__7_5, 174, 174, 20, 27},
  {cont__7_11, &frame__7_5, 174, 174, 11, 34},
  {cont__7_13, &frame__7_5, 174, 174, 5, 38},
  {cont__7_14, &frame__7_5, 175, 175, 5, 70},
  {cont__7_21, &frame__7_5, 176, 176, 21, 24},
  {cont__7_22, &frame__7_5, 176, 176, 11, 25},
  {cont__7_24, &frame__7_5, 176, 176, 5, 30},
  {cont__7_26, &frame__7_5, 177, 183, 5, 21},
  {cont__7_37, &frame__7_5, 184, 184, 5, 11},
  {cont__7_38, &frame__7_5, 185, 185, 5, 15},
  {cont__7_39, &frame__7_5, 185, 185, 15, 15},
  {entry__7_3, NULL, 171, 171, 12, 20},
  {cont__7_4, &frame__7_3, 171, 185, 9, 15},
  {entry__7_1_std__hexdump, NULL, 169, 169, 3, 21},
  {cont__7_2, &frame__7_1_std__hexdump, 171, 185, 3, 15}
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
static void entry__1_1_std__debug_string(void) {
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
  // 91: ... 2
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
  // 91: ... debug_string(expr -2 depth)
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
  // 91: ... write name ":" debug_string(expr -2 depth)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = string__578a5af303e9cdb;
  arguments->slots[2] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__2_1_std__dump(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // args: 0
  // depth: 1
  frame->slots[1] /* depth */ = create_cell();
  frame->slots[0] /* args */ = create_cell_with_contents(from_arguments(0, argument_count-0));
  // 87: $$depth 1
  ((CELL *)frame->slots[1])->contents /* depth */ = number__1;
  // 88: ... length_of(args)
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
  // 88: ... length_of(args).is_odd
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
  // 88: ... :
  // 89:   !depth args(1)
  // 90:   range &args 2 -1
  frame->slots[4] /* temp__3 */ = create_closure(entry__2_4, 0);
  // 88: if length_of(args).is_odd:
  // 89:   !depth args(1)
  // 90:   range &args 2 -1
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
  // 89: !depth args(1)
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
  // 90: ... 1
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
  // 90: range &args 2 -1
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
  // 91: ... : (name expr) write name ":" debug_string(expr -2 depth)
  frame->slots[2] /* temp__1 */ = create_closure(entry__2_9, 2);
  // 91: for_each_pair args: (name expr) write name ":" debug_string(expr -2 depth)
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
  // 116: ... 2
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
  // 116: ... debug_string(expr -2 depth)
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
  // 116: ... ewrite name ":" debug_string(expr -2 depth)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = string__578a5af303e9cdb;
  arguments->slots[2] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__ewrite();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__3_1_std__edump(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // args: 0
  // depth: 1
  frame->slots[1] /* depth */ = create_cell();
  frame->slots[0] /* args */ = create_cell_with_contents(from_arguments(0, argument_count-0));
  // 112: $$depth 1
  ((CELL *)frame->slots[1])->contents /* depth */ = number__1;
  // 113: ... length_of(args)
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
  // 113: ... length_of(args).is_odd
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
  // 113: ... :
  // 114:   !depth args(1)
  // 115:   range &args 2 -1
  frame->slots[4] /* temp__3 */ = create_closure(entry__3_4, 0);
  // 113: if length_of(args).is_odd:
  // 114:   !depth args(1)
  // 115:   range &args 2 -1
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
  // 114: !depth args(1)
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
  // 115: ... 1
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
  // 115: range &args 2 -1
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
  // 116: ... : (name expr) ewrite name ":" debug_string(expr -2 depth)
  frame->slots[2] /* temp__1 */ = create_closure(entry__3_9, 2);
  // 116: for_each_pair args: (name expr) ewrite name ":" debug_string(expr -2 depth)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* args */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each_pair();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__4_1_std__collect_garbage(void) {
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
static void entry__5_1_std__instruction_counter(void) {
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
static void entry__6_1_std__total_garbage_collections(void) {
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
  // 172: ... len-pos
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
  // 172: $n min(len-pos 16)
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
  // 173: ... pos+1
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
  // 173: ... pos+n
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
  // 173: $line range(str pos+1 pos+n)
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
  // 174: ... hex(pos)
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
  // 174: ... pad_left(hex(pos) 8 "0")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = number__8;
  arguments->slots[2] = string__578a5af303e9cd1;
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
  // 174: write pad_left(hex(pos) 8 "0") ":"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = string__578a5af303e9cdb;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__7_14;
}
static void cont__7_14(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 175: ... : (i) write " " pad_left(hex(line(i).to_integer) 2 "0")
  frame->slots[5] /* temp__1 */ = create_closure(entry__7_15, 1);
  // 175: from_to 1 n: (i) write " " pad_left(hex(line(i).to_integer) 2 "0")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = number__1;
  arguments->slots[1] = frame->slots[3] /* n */;
  arguments->slots[2] = frame->slots[5] /* temp__1 */;
  result_count = 0;
  myself = get__from_to();
  func = myself->type;
  frame->cont = cont__7_21;
}
static void entry__7_15(void) {
  allocate_initialized_frame_gc(2, 6);
  // slot allocations:
  // i: 0
  // line: 1
  frame->slots[1] = myself->closure.frame->slots[4]; /* line */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 175: ... line(i)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* i */;
  result_count = 1;
  myself = frame->slots[1] /* line */;
  func = myself->type;
  frame->cont = cont__7_16;
}
static void cont__7_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__4 */ = arguments->slots[0];
  // 175: ... line(i).to_integer
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__4 */;
  result_count = 1;
  myself = get__to_integer();
  func = myself->type;
  frame->cont = cont__7_17;
}
static void cont__7_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 175: ... hex(line(i).to_integer)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__hex();
  func = myself->type;
  frame->cont = cont__7_18;
}
static void cont__7_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 175: ... pad_left(hex(line(i).to_integer) 2 "0")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = number__2;
  arguments->slots[2] = string__578a5af303e9cd1;
  result_count = 1;
  myself = get__pad_left();
  func = myself->type;
  frame->cont = cont__7_19;
}
static void cont__7_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 175: ... write " " pad_left(hex(line(i).to_integer) 2 "0")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__578a5af303e9cc1;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_21(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 176: ... 16-n
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__16;
  arguments->slots[1] = frame->slots[3] /* n */;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__7_22;
}
static void cont__7_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 176: ... dup("   " 16-n)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__fa730415f296bec;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = 1;
  myself = get__dup();
  func = myself->type;
  frame->cont = cont__7_24;
}
static void cont__7_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 176: write dup("   " 16-n) "  "
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = string__2d7981f4e6082be5;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__7_26;
}
static void cont__7_26(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 177: ... : (i)
  // 178:   $chr line(i)
  // 179:   if
  // 180:     chr >= ' ' && chr < '@del;':
  // 181:       write chr
  // 182:     :
  // 183:       write "."
  frame->slots[5] /* temp__1 */ = create_closure(entry__7_27, 1);
  // 177: from_to 1 n: (i)
  // 178:   $chr line(i)
  // 179:   if
  // 180:     chr >= ' ' && chr < '@del;':
  // 181:       write chr
  // 182:     :
  // 183:       write "."
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = number__1;
  arguments->slots[1] = frame->slots[3] /* n */;
  arguments->slots[2] = frame->slots[5] /* temp__1 */;
  result_count = 0;
  myself = get__from_to();
  func = myself->type;
  frame->cont = cont__7_37;
}
static void entry__7_34(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 181: write chr
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_35(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 183: write "."
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__578a5af303e9ccf;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__7_27(void) {
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
  // 178: $chr line(i)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* i */;
  result_count = 1;
  myself = frame->slots[1] /* line */;
  func = myself->type;
  frame->cont = cont__7_28;
}
static void cont__7_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* chr */, arguments->slots[0]);
  // 180: chr >= ' '
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* chr */;
  arguments->slots[1] = character__32;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__7_29;
}
static void cont__7_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 180: chr >= ' '
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__7_30;
}
static void cont__7_30(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 180: ... chr < '@del;'
  frame->slots[6] /* temp__4 */ = create_closure(entry__7_31, 0);
  // 180: chr >= ' ' && chr < '@del;'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[6] /* temp__4 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__7_33;
}
static void entry__7_31(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 180: ... chr < '@del;'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  arguments->slots[1] = character__127;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__7_32;
}
static void cont__7_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 180: ... chr < '@del;'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__7_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 180: ... :
  // 181:   write chr
  frame->slots[7] /* temp__5 */ = create_closure(entry__7_34, 0);
  // 179: if
  // 180:   chr >= ' ' && chr < '@del;':
  // 181:     write chr
  // 182:   :
  // 183:     write "."
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__5 */;
  arguments->slots[2] = func__7_35;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__7_37(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 184: writeln
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = get__writeln();
  func = myself->type;
  frame->cont = cont__7_38;
}
static void cont__7_38(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 185: plus &pos n
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* pos */;
  arguments->slots[1] = frame->slots[3] /* n */;
  result_count = 1;
  myself = get__plus();
  func = myself->type;
  frame->cont = cont__7_39;
}
static void cont__7_39(void) {
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
  // 171: ... pos < len
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
  // 171: ... :
  // 172:   $n min(len-pos 16)
  // 173:   $line range(str pos+1 pos+n)
  // 174:   write pad_left(hex(pos) 8 "0") ":"
  // 175:   from_to 1 n: (i) write " " pad_left(hex(line(i).to_integer) 2 "0")
  // 176:   write dup("   " 16-n) "  "
  // 177:   from_to 1 n: (i)
  // 178:     $chr line(i)
  // 179:     if
  // 180:       chr >= ' ' && chr < '@del;':
  // ...
  frame->slots[4] /* temp__2 */ = create_closure(entry__7_5, 0);
  // 171: ... -> pos < len:
  // 172:   $n min(len-pos 16)
  // 173:   $line range(str pos+1 pos+n)
  // 174:   write pad_left(hex(pos) 8 "0") ":"
  // 175:   from_to 1 n: (i) write " " pad_left(hex(line(i).to_integer) 2 "0")
  // 176:   write dup("   " 16-n) "  "
  // 177:   from_to 1 n: (i)
  // 178:     $chr line(i)
  // 179:     if
  // 180:       chr >= ' ' && chr < '@del;':
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__7_1_std__hexdump(void) {
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
  // 169: $len length_of(str)
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
  // 170: $$pos 0
  ((CELL *)frame->slots[2])->contents /* pos */ = number__0;
  // 171: ... -> pos < len:
  // 172:   $n min(len-pos 16)
  // 173:   $line range(str pos+1 pos+n)
  // 174:   write pad_left(hex(pos) 8 "0") ":"
  // 175:   from_to 1 n: (i) write " " pad_left(hex(line(i).to_integer) 2 "0")
  // 176:   write dup("   " 16-n) "  "
  // 177:   from_to 1 n: (i)
  // 178:     $chr line(i)
  // 179:     if
  // 180:       chr >= ' ' && chr < '@del;':
  // ...
  frame->slots[3] /* temp__1 */ = create_closure(entry__7_3, 0);
  // 171: while -> pos < len:
  // 172:   $n min(len-pos 16)
  // 173:   $line range(str pos+1 pos+n)
  // 174:   write pad_left(hex(pos) 8 "0") ":"
  // 175:   from_to 1 n: (i) write " " pad_left(hex(line(i).to_integer) 2 "0")
  // 176:   write dup("   " 16-n) "  "
  // 177:   from_to 1 n: (i)
  // 178:     $chr line(i)
  // 179:     if
  // 180:       chr >= ' ' && chr < '@del;':
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
  var.std__edump = collect_node(var.std__edump);
  var.std__collect_garbage = collect_node(var.std__collect_garbage);
  var.std__instruction_counter = collect_node(var.std__instruction_counter);
  var.std__total_garbage_collections = collect_node(var.std__total_garbage_collections);
  var.std__hexdump = collect_node(var.std__hexdump);
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
  number__0 = from_uint32(0U);
  number__8 = from_uint32(8U);
  number__16 = from_uint32(16U);
  character__32 = from_uchar32(32);
  character__127 = from_uchar32(127);
  number__1 = from_uint32(1U);
  number__2 = from_uint32(2U);
  func__1_1_std__debug_string = create_function(entry__1_1_std__debug_string, -1);
  string__578a5af303e9cdb = from_latin_1_string(":", 1);
  func__2_1_std__dump = create_function(entry__2_1_std__dump, -1);
  func__3_1_std__edump = create_function(entry__3_1_std__edump, -1);
  func__4_1_std__collect_garbage = create_function(entry__4_1_std__collect_garbage, 0);
  func__5_1_std__instruction_counter = create_function(entry__5_1_std__instruction_counter, 0);
  func__6_1_std__total_garbage_collections = create_function(entry__6_1_std__total_garbage_collections, 0);
  string__578a5af303e9cd1 = from_latin_1_string("0", 1);
  string__578a5af303e9cc1 = from_latin_1_string(" ", 1);
  string__fa730415f296bec = from_latin_1_string("   ", 3);
  string__2d7981f4e6082be5 = from_latin_1_string("  ", 2);
  string__578a5af303e9ccf = from_latin_1_string(".", 1);
  func__7_35 = create_function(entry__7_35, 0);
  func__7_1_std__hexdump = create_function(entry__7_1_std__hexdump, 1);
}

static int already_run_phase_3 = false;

EXPORT void phase_3__basic__debug(void) {
  if (already_run_phase_3) return;
  already_run_phase_3 = true;
  set_module("basic__debug");
  set_used_namespaces(used_namespaces);
  define_single_assign_static("std", "debug_string", get__std__debug_string, &var.std__debug_string);
  define_single_assign_static("std", "dump", get__std__dump, &var.std__dump);
  define_single_assign_static("std", "edump", get__std__edump, &var.std__edump);
  define_single_assign_static("std", "collect_garbage", get__std__collect_garbage, &var.std__collect_garbage);
  define_single_assign_static("std", "instruction_counter", get__std__instruction_counter, &var.std__instruction_counter);
  define_single_assign_static("std", "total_garbage_collections", get__std__total_garbage_collections, &var.std__total_garbage_collections);
  define_single_assign_static("std", "hexdump", get__std__hexdump, &var.std__hexdump);
}

static int already_run_phase_4 = false;

EXPORT void phase_4__basic__debug(void) {
  if (already_run_phase_4) return;
  already_run_phase_4 = true;
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

static int already_run_phase_5 = false;

EXPORT void phase_5__basic__debug(void) {
  if (already_run_phase_5) return;
  already_run_phase_5 = true;
  assign_variable(&var.std__debug_string, &func__1_1_std__debug_string);
  assign_variable(&var.std__dump, &func__2_1_std__dump);
  assign_variable(&var.std__edump, &func__3_1_std__edump);
  assign_variable(&var.std__collect_garbage, &func__4_1_std__collect_garbage);
  assign_variable(&var.std__instruction_counter, &func__5_1_std__instruction_counter);
  assign_variable(&var.std__total_garbage_collections, &func__6_1_std__total_garbage_collections);
  assign_variable(&var.std__hexdump, &func__7_1_std__hexdump);
}

static int already_run_phase_6 = false;

EXPORT void phase_6__basic__debug(void) {
  if (already_run_phase_6) return;
  already_run_phase_6 = true;
  register_collector(collect__basic__debug);
}
