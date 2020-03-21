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
IMPORT NODE *create_future(void);
IMPORT NODE *create_cell_with_contents(NODE *contents);
typedef struct CELL {
  FUNC type;
  struct ATTRIBUTES *attributes;
  NODE *contents;
} CELL;
IMPORT int result_count;
IMPORT void invalid_results_error(void);
IMPORT NODE *create_closure(FUNC type, int par_count);
IMPORT void initialize_future(NODE *var, NODE *val);
IMPORT NODE *create_continuation(void);
IMPORT NODE *undefined;
IMPORT void allocate_arguments(void);
IMPORT NODE *from_arguments(int first_idx, int count);
IMPORT NODE *collect_node(NODE *node);
IMPORT void register_module_info(MODULE_INFO *info);
IMPORT void register_polymorphic_function_with_setter(const char *name, int *id_p);
IMPORT NODE *from_uint32(uint32_t val);
IMPORT void set_module(const char *name);
IMPORT void set_used_namespaces(const char **namespaces);
IMPORT void define_single_assign_static(
  const char *namespace, const char *name,
  NODE_GETTER getter, NODE **var_p
);
IMPORT void use_polymorphic_function(
  const char *namespace, const char *name, NODE_GETTER *getter, int *id
);
IMPORT void use_read_only(
  const char *namespace, const char *name,
  NODE_GETTER *getter, NODE_GETTER *get_value_or_future
);
IMPORT void define_attribute(
  const char *namespace, const char *name,
  int id, NODE *attribute
);
IMPORT void define_method(
  const char *namespace, const char *name,
  int id, NODE *method
);
IMPORT void assign_value(NODE **dest, NODE *val);
IMPORT NODE *create_function(FUNC func, int par_count);
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
static int poly_idx__for_each;
static NODE_GETTER get__for_each;
static NODE_GETTER get__if;
static NODE_GETTER get_value_or_future__if;
static NODE_GETTER get__is_defined;
static NODE_GETTER get_value_or_future__is_defined;
static NODE_GETTER get__is_undefined;
static NODE_GETTER get_value_or_future__is_undefined;
static NODE_GETTER get__length_of;
static NODE_GETTER get_value_or_future__length_of;
static NODE_GETTER get__list;
static NODE_GETTER get_value_or_future__list;
static NODE_GETTER get__push;
static NODE_GETTER get_value_or_future__push;
static NODE_GETTER get__range;
static NODE_GETTER get_value_or_future__range;
static NODE_GETTER get__std__less;
static NODE_GETTER get_value_or_future__std__less;
static NODE_GETTER get__std__minus;
static NODE_GETTER get_value_or_future__std__minus;
static NODE_GETTER get__std__negate;
static NODE_GETTER get_value_or_future__std__negate;
static NODE_GETTER get__undefined;
static NODE_GETTER get_value_or_future__undefined;
static NODE_GETTER get__unless;
static NODE_GETTER get_value_or_future__unless;
static struct {
  NODE *_dimensions_of;
  NODE *_table_of;
  NODE *_insert_into;
  NODE *_get_item;
  NODE *_for_each_dimension;
  NODE *types__multi_dimensional_table;
  NODE *std__multi_dimensional_table;
} var;
static const char *var_names[] = {
  "dimensions_of",
  "table_of",
  "insert_into",
  "get_item",
  "for_each_dimension"
};
static int poly_idx__dimensions_of;
static void type__dimensions_of(void);
static int poly_idx__table_of;
static void type__table_of(void);
static NODE *func__3_1;
static void entry__3_1(void);
static FRAME_INFO frame__3_1 = {4, {"table", "dimensions", "args", "idx"}};
static void cont__3_2(void);
static NODE *func__3_3;
static void entry__3_3(void);
static FRAME_INFO frame__3_3 = {2, {"table", "dimensions"}};
static void cont__3_4(void);
static void cont__3_5(void);
static void cont__3_6(void);
static void cont__3_7(void);
static void cont__3_8(void);
static NODE *func__3_9;
static void entry__3_9(void);
static FRAME_INFO frame__3_9 = {4, {"table", "idx", "dimensions", "args"}};
static void cont__3_10(void);
static void cont__3_11(void);
static void cont__3_12(void);
static void cont__3_13(void);
static void cont__3_14(void);
static void cont__3_15(void);
static void cont__3_16(void);
static NODE *func__3_17;
static void entry__3_17(void);
static FRAME_INFO frame__3_17 = {3, {"table", "idx", "args"}};
static void cont__3_18(void);
static void cont__3_19(void);
static void cont__3_20(void);
static NODE *func__4_1;
static void entry__4_1(void);
static FRAME_INFO frame__4_1 = {3, {"table", "indices", "return"}};
static void cont__4_2(void);
static NODE *func__4_3;
static void entry__4_3(void);
static FRAME_INFO frame__4_3 = {1, {"return"}};
static void cont__4_4(void);
static void cont__4_5(void);
static void cont__4_6(void);
static NODE *func__4_7;
static void entry__4_7(void);
static FRAME_INFO frame__4_7 = {2, {"table", "indices"}};
static void cont__4_8(void);
static void cont__4_9(void);
static void cont__4_10(void);
static void cont__4_11(void);
static void cont__4_12(void);
static NODE *func__4_13;
static void entry__4_13(void);
static FRAME_INFO frame__4_13 = {1, {"table"}};
static void cont__4_14(void);
static NODE *func__5_1;
static void entry__5_1(void);
static FRAME_INFO frame__5_1 = {4, {"args", "myself", "dimensions", "n"}};
static void cont__5_2(void);
static void cont__5_3(void);
static void cont__5_4(void);
static void cont__5_5(void);
static NODE *func__5_6;
static void entry__5_6(void);
static FRAME_INFO frame__5_6 = {3, {"myself", "dimensions", "args"}};
static void cont__5_7(void);
static void cont__5_8(void);
static NODE *func__5_9;
static void entry__5_9(void);
static FRAME_INFO frame__5_9 = {2, {"myself", "args"}};
static void cont__5_10(void);
static void cont__5_11(void);
static NODE *get__types__multi_dimensional_table(void) {
  return var.types__multi_dimensional_table;
}
static NODE *func__7_1;
static void entry__7_1(void);
static FRAME_INFO frame__7_1 = {1, {"dimensions"}};
static NODE *get__std__multi_dimensional_table(void) {
  return var.std__multi_dimensional_table;
}
static NODE *func__8_1;
static void entry__8_1(void);
static FRAME_INFO frame__8_1 = {4, {"table", "depth", "indices", "body"}};
static void cont__8_2(void);
static NODE *func__8_3;
static void entry__8_3(void);
static FRAME_INFO frame__8_3 = {4, {"table", "depth", "indices", "body"}};
static NODE *func__8_4;
static void entry__8_4(void);
static FRAME_INFO frame__8_4 = {5, {"idx", "value", "depth", "indices", "body"}};
static void cont__8_5(void);
static NODE *func__8_6;
static void entry__8_6(void);
static FRAME_INFO frame__8_6 = {5, {"value", "depth", "indices", "idx", "body"}};
static void cont__8_7(void);
static void cont__8_8(void);
static NODE *func__8_9;
static void entry__8_9(void);
static FRAME_INFO frame__8_9 = {4, {"body", "indices", "idx", "value"}};
static NODE *func__9_1;
static void entry__9_1(void);
static FRAME_INFO frame__9_1 = {2, {"self", "body"}};
static void cont__9_2(void);
static void cont__9_3(void);
static void cont__9_4(void);
static void cont__9_5(void);
void run__basic__types__multi_dimensional_table(void);

static CONTINUATION_INFO continuation_info[] = {
  {type__dimensions_of, NULL, 23, 23, 2, 14},
  {type__table_of, NULL, 24, 24, 2, 9},
  {run__basic__types__multi_dimensional_table, NULL, },
  {entry__3_3, NULL, 27, 27, 28, 47},
  {cont__3_4, &frame__3_3, 27, 27, 47, 47},
  {entry__3_9, NULL, 32, 32, 21, 30},
  {cont__3_10, &frame__3_9, 32, 32, 52, 52},
  {cont__3_11, &frame__3_9, 32, 32, 32, 53},
  {cont__3_12, &frame__3_9, 32, 32, 69, 69},
  {cont__3_13, &frame__3_9, 32, 32, 55, 70},
  {cont__3_14, &frame__3_9, 31, 32, 7, 71},
  {cont__3_15, &frame__3_9, 31, 31, 7, 17},
  {cont__3_16, &frame__3_9, 32, 32, 72, 72},
  {entry__3_17, NULL, 34, 34, 7, 25},
  {cont__3_18, &frame__3_17, 34, 34, 7, 17},
  {cont__3_19, &frame__3_17, 34, 34, 25, 25},
  {entry__3_1, NULL, 27, 27, 10, 25},
  {cont__3_2, &frame__3_1, 27, 27, 3, 47},
  {cont__3_5, &frame__3_1, 28, 28, 3, 14},
  {cont__3_6, &frame__3_1, 30, 30, 5, 25},
  {cont__3_7, &frame__3_1, 30, 30, 5, 29},
  {cont__3_8, &frame__3_1, 29, 34, 3, 26},
  {cont__3_20, &frame__3_1, 35, 35, 3, 10},
  {entry__4_3, NULL, 43, 43, 26, 41},
  {entry__4_7, NULL, 46, 46, 23, 32},
  {cont__4_8, &frame__4_7, 46, 46, 17, 33},
  {cont__4_9, &frame__4_7, 46, 46, 52, 52},
  {cont__4_10, &frame__4_7, 46, 46, 35, 53},
  {cont__4_11, &frame__4_7, 46, 46, 8, 54},
  {cont__4_12, &frame__4_7, 46, 46, 5, 54},
  {entry__4_13, NULL, 47, 47, 5, 12},
  {entry__4_1, NULL, 43, 43, 6, 23},
  {cont__4_2, &frame__4_1, 43, 43, 3, 41},
  {cont__4_4, &frame__4_1, 45, 45, 5, 22},
  {cont__4_5, &frame__4_1, 45, 45, 5, 26},
  {cont__4_6, &frame__4_1, 44, 47, 3, 12},
  {cont__4_14, &frame__4_1, 47, 47, 12, 12},
  {entry__5_6, NULL, 58, 58, 36, 51},
  {cont__5_7, &frame__5_6, 58, 58, 7, 68},
  {cont__5_8, &frame__5_6, 59, 59, 7, 15},
  {entry__5_9, NULL, 60, 60, 17, 32},
  {cont__5_10, &frame__5_9, 60, 60, 8, 38},
  {cont__5_11, &frame__5_9, 60, 60, 5, 38},
  {entry__5_1, NULL, 54, 54, 3, 35},
  {cont__5_2, &frame__5_1, 55, 55, 3, 26},
  {cont__5_3, &frame__5_1, 57, 57, 5, 19},
  {cont__5_4, &frame__5_1, 57, 57, 5, 23},
  {cont__5_5, &frame__5_1, 56, 60, 3, 38},
  {entry__7_1, NULL, 65, 65, 3, 62},
  {entry__8_6, NULL, 72, 72, 36, 42},
  {cont__8_7, &frame__8_6, 72, 72, 44, 60},
  {cont__8_8, &frame__8_6, 72, 72, 11, 65},
  {entry__8_9, NULL, 74, 74, 11, 33},
  {entry__8_4, NULL, 71, 71, 9, 17},
  {cont__8_5, &frame__8_4, 70, 74, 7, 34},
  {entry__8_3, NULL, 69, 74, 5, 35},
  {entry__8_1, NULL, 68, 68, 6, 21},
  {cont__8_2, &frame__8_1, 68, 74, 3, 36},
  {entry__9_1, NULL, 77, 77, 22, 35},
  {cont__9_2, &frame__9_1, 77, 77, 47, 65},
  {cont__9_3, &frame__9_1, 77, 77, 37, 66},
  {cont__9_4, &frame__9_1, 77, 77, 68, 73},
  {cont__9_5, &frame__9_1, 77, 77, 3, 78}
};

union NODE {
  struct {
    FUNC type;
    ATTRIBUTES *attributes;
  };
  CONTINUATION continuation;
  CLOSURE closure;
};
static void type__dimensions_of(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__dimensions_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__dimensions_of, attr);
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
static void type__table_of(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__table_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__table_of, attr);
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
static NODE *number__1;
static NODE *number__2;

static const char *used_namespaces[] = {
  "std",
  NULL
};

static MODULE_INFO module_info = {
  NULL,
  "basic__types__multi_dimensional_table",
  continuation_info,
  sizeof(continuation_info)/sizeof(CONTINUATION_INFO),
  (NODE **)&var,
  var_names,
  sizeof(var_names)/sizeof(const char *),
  used_namespaces,
  {DEBUG_FILENAME("basic/types/multi_dimensional_table.sim")}
};

/******
C O D E
******/

static int already_run = false;

EXPORT void run__basic__types__multi_dimensional_table(void) {
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
static void entry__3_1(void) {
  allocate_initialized_frame_gc(3, 8);
  // slot allocations:
  // table: 0
  // dimensions: 1
  // args: 2
  // idx: 3
  frame->slots[3] /* idx */ = create_future();
  if (argument_count != 3) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* table */ = create_cell_with_contents(arguments->slots[0]);
  // 27: ... table.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* table */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__3_2;
}
static void cont__3_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 27: ... : !table dimensions(1)
  frame->slots[5] /* temp__2 */ = create_closure(entry__3_3, 0);
  // 27: unless table.is_defined: !table dimensions(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__3_5;
}
static void entry__3_3(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // table: 0
  // dimensions: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* table */
  frame->slots[1] = myself->closure.frame->slots[1]; /* dimensions */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 27: ... !table dimensions(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[1] /* dimensions */;
  func = myself->type;
  frame->cont = cont__3_4;
}
static void cont__3_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* table */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__3_5(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 28: $idx args(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[2] /* args */;
  func = myself->type;
  frame->cont = cont__3_6;
}
static void cont__3_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* idx */, arguments->slots[0]);
  // 30: length_of(dimensions)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* dimensions */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__3_7;
}
static void cont__3_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 30: length_of(dimensions) > 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__1;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__3_8;
}
static void cont__3_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 30: ... :
  // 31:   !table(idx)
  // 32:     insert_into(table(idx) range(dimensions 2 -1) range(args 2 -1))
  frame->slots[6] /* temp__3 */ = create_closure(entry__3_9, 0);
  // 33: :
  // 34:   !table(idx) args(2)
  frame->slots[7] /* temp__4 */ = create_closure(entry__3_17, 0);
  // 29: if
  // 30:   length_of(dimensions) > 1:
  // 31:     !table(idx)
  // 32:       insert_into(table(idx) range(dimensions 2 -1) range(args 2 -1))
  // 33:   :
  // 34:     !table(idx) args(2)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  arguments->slots[2] = frame->slots[7] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__3_20;
}
static void entry__3_9(void) {
  allocate_initialized_frame_gc(4, 10);
  // slot allocations:
  // table: 0
  // idx: 1
  // dimensions: 2
  // args: 3
  frame->slots[0] = myself->closure.frame->slots[0]; /* table */
  frame->slots[1] = myself->closure.frame->slots[3]; /* idx */
  frame->slots[2] = myself->closure.frame->slots[1]; /* dimensions */
  frame->slots[3] = myself->closure.frame->slots[2]; /* args */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 32: ... table(idx)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* idx */;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* table */;
  func = myself->type;
  frame->cont = cont__3_10;
}
static void cont__3_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 32: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__3_11;
}
static void cont__3_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 32: ... range(dimensions 2 -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* dimensions */;
  arguments->slots[1] = number__2;
  arguments->slots[2] = frame->slots[6] /* temp__3 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__3_12;
}
static void cont__3_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 32: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__3_13;
}
static void cont__3_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__5 */ = arguments->slots[0];
  // 32: ... range(args 2 -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* args */;
  arguments->slots[1] = number__2;
  arguments->slots[2] = frame->slots[8] /* temp__5 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__3_14;
}
static void cont__3_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__4 */ = arguments->slots[0];
  // 31: !table(idx)
  // 32:   insert_into(table(idx) range(dimensions 2 -1) range(args 2 -1))
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  arguments->slots[2] = frame->slots[7] /* temp__4 */;
  result_count = 1;
  myself = var._insert_into;
  func = myself->type;
  frame->cont = cont__3_15;
}
static void cont__3_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__6 */ = arguments->slots[0];
  // 31: !table(idx)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* idx */;
  arguments->slots[1] = frame->slots[9] /* temp__6 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* table */;
  func = myself->type;
  frame->cont = cont__3_16;
}
static void cont__3_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* table */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__3_17(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // table: 0
  // idx: 1
  // args: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* table */
  frame->slots[1] = myself->closure.frame->slots[3]; /* idx */
  frame->slots[2] = myself->closure.frame->slots[2]; /* args */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 34: !table(idx) args(2)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = frame->slots[2] /* args */;
  func = myself->type;
  frame->cont = cont__3_18;
}
static void cont__3_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 34: !table(idx)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* idx */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* table */;
  func = myself->type;
  frame->cont = cont__3_19;
}
static void cont__3_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* table */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__3_20(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 35: -> table
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* table */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__4_1(void) {
  allocate_initialized_frame_gc(3, 7);
  // slot allocations:
  // table: 0
  // indices: 1
  // return: 2
  frame->slots[2] /* return */ = create_continuation();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 43: ... table.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* table */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__4_2;
}
static void cont__4_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 43: ... : return undefined
  frame->slots[4] /* temp__2 */ = create_closure(entry__4_3, 0);
  // 43: if table.is_undefined: return undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__4_4;
}
static void entry__4_3(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 43: ... return undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__4_4(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 45: length_of(indices)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* indices */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__4_5;
}
static void cont__4_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 45: length_of(indices) > 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__4_6;
}
static void cont__4_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 46: -> get_item(table(indices(1)) range(indices 2 -1))
  frame->slots[5] /* temp__3 */ = create_closure(entry__4_7, 0);
  // 47: -> table
  frame->slots[6] /* temp__4 */ = create_closure(entry__4_13, 0);
  // 44: if
  // 45:   length_of(indices) > 0
  // 46:   -> get_item(table(indices(1)) range(indices 2 -1))
  // 47:   -> table
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
static void entry__4_7(void) {
  allocate_initialized_frame_gc(2, 7);
  // slot allocations:
  // table: 0
  // indices: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* table */
  frame->slots[1] = myself->closure.frame->slots[1]; /* indices */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 46: ... indices(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[1] /* indices */;
  func = myself->type;
  frame->cont = cont__4_8;
}
static void cont__4_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 46: ... table(indices(1))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = frame->slots[0] /* table */;
  func = myself->type;
  frame->cont = cont__4_9;
}
static void cont__4_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 46: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__4_10;
}
static void cont__4_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__5 */ = arguments->slots[0];
  // 46: ... range(indices 2 -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* indices */;
  arguments->slots[1] = number__2;
  arguments->slots[2] = frame->slots[6] /* temp__5 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__4_11;
}
static void cont__4_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__4 */ = arguments->slots[0];
  // 46: ... get_item(table(indices(1)) range(indices 2 -1))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__4 */;
  result_count = 1;
  myself = var._get_item;
  func = myself->type;
  frame->cont = cont__4_12;
}
static void cont__4_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 46: -> get_item(table(indices(1)) range(indices 2 -1))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__4_13(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // table: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* table */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 47: -> table
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* table */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__4_14(void) {
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__5_6(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // myself: 0
  // dimensions: 1
  // args: 2
  frame->slots[0] = myself->closure.frame->slots[1]; /* myself */
  frame->slots[1] = myself->closure.frame->slots[2]; /* dimensions */
  frame->slots[2] = myself->closure.frame->slots[0]; /* args */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 58: ... table_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  result_count = 1;
  myself = var._table_of;
  func = myself->type;
  frame->cont = cont__5_7;
}
static void cont__5_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 58: !myself.table_of insert_into(table_of(myself) dimensions args)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* dimensions */;
  arguments->slots[2] = frame->slots[2] /* args */;
  result_count = 1;
  myself = var._insert_into;
  func = myself->type;
  frame->cont = cont__5_8;
}
static void cont__5_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 58: !myself.table_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* myself */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__table_of, frame->slots[4] /* temp__2 */);
    ((CELL *)frame->slots[0])->contents /* myself */ = temp;

  }
  // 59: -> myself
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__5_9(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // myself: 0
  // args: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* myself */
  frame->slots[1] = myself->closure.frame->slots[0]; /* args */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 60: ... table_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* myself */;
  result_count = 1;
  myself = var._table_of;
  func = myself->type;
  frame->cont = cont__5_10;
}
static void cont__5_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 60: ... get_item(table_of(myself) args)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[1] /* args */;
  result_count = 1;
  myself = var._get_item;
  func = myself->type;
  frame->cont = cont__5_11;
}
static void cont__5_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 60: -> get_item(table_of(myself) args)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__5_1(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(2, 8);
  // slot allocations:
  // args: 0
  // myself: 1
  // dimensions: 2
  // n: 3
  frame->slots[2] /* dimensions */ = create_future();
  frame->slots[3] /* n */ = create_future();
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  frame->slots[1] /* myself */ = create_cell_with_contents(myself);
  // 54: $dimensions dimensions_of(myself)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* myself */;
  result_count = 1;
  myself = var._dimensions_of;
  func = myself->type;
  frame->cont = cont__5_2;
}
static void cont__5_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* dimensions */, arguments->slots[0]);
  // 55: $n length_of(dimensions)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* dimensions */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__5_3;
}
static void cont__5_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* n */, arguments->slots[0]);
  // 57: length_of(args)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* args */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__5_4;
}
static void cont__5_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 57: length_of(args) > n
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* n */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__5_5;
}
static void cont__5_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 57: ... : # insert
  // 58:   !myself.table_of insert_into(table_of(myself) dimensions args)
  // 59:   -> myself
  frame->slots[6] /* temp__3 */ = create_closure(entry__5_6, 0);
  // 60: -> get_item(table_of(myself) args)
  frame->slots[7] /* temp__4 */ = create_closure(entry__5_9, 0);
  // 56: if
  // 57:   length_of(args) > n: # insert
  // 58:     !myself.table_of insert_into(table_of(myself) dimensions args)
  // 59:     -> myself
  // 60:   -> get_item(table_of(myself) args)
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
static void entry__7_1(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // dimensions: 0
  frame->slots[0] /* dimensions */ = from_arguments(0, argument_count-0);
  // 65: ... types::multi_dimensional_table(.dimensions_of dimensions)
  {
    NODE *temp = clone_object_and_attributes(var.types__multi_dimensional_table);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__dimensions_of, frame->slots[0] /* dimensions */);
    frame->slots[1] /* temp__1 */ = temp;

  }
  // 65: -> types::multi_dimensional_table(.dimensions_of dimensions)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__8_6(void) {
  allocate_initialized_frame_gc(5, 7);
  // slot allocations:
  // value: 0
  // depth: 1
  // indices: 2
  // idx: 3
  // body: 4
  frame->slots[0] = myself->closure.frame->slots[1]; /* value */
  frame->slots[1] = myself->closure.frame->slots[2]; /* depth */
  frame->slots[2] = myself->closure.frame->slots[3]; /* indices */
  frame->slots[3] = myself->closure.frame->slots[0]; /* idx */
  frame->slots[4] = myself->closure.frame->slots[4]; /* body */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 72: ... depth-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* depth */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__8_7;
}
static void cont__8_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 72: ... push(indices idx)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* indices */;
  arguments->slots[1] = frame->slots[3] /* idx */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__8_8;
}
static void cont__8_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 72: for_each_dimension value depth-1 push(indices idx) body
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* value */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  arguments->slots[2] = frame->slots[6] /* temp__2 */;
  arguments->slots[3] = frame->slots[4] /* body */;
  result_count = frame->caller_result_count;
  myself = var._for_each_dimension;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__8_9(void) {
  allocate_initialized_frame_gc(4, 4);
  // slot allocations:
  // body: 0
  // indices: 1
  // idx: 2
  // value: 3
  frame->slots[0] = myself->closure.frame->slots[4]; /* body */
  frame->slots[1] = myself->closure.frame->slots[3]; /* indices */
  frame->slots[2] = myself->closure.frame->slots[0]; /* idx */
  frame->slots[3] = myself->closure.frame->slots[1]; /* value */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 74: body indices* idx value
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[1] /* indices */);
  arguments->slots[argument_count++] = frame->slots[2] /* idx */;
  arguments->slots[argument_count++] = frame->slots[3] /* value */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__8_4(void) {
  allocate_initialized_frame_gc(5, 8);
  // slot allocations:
  // idx: 0
  // value: 1
  // depth: 2
  // indices: 3
  // body: 4
  frame->slots[2] = myself->closure.frame->slots[1]; /* depth */
  frame->slots[3] = myself->closure.frame->slots[2]; /* indices */
  frame->slots[4] = myself->closure.frame->slots[3]; /* body */
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 71: depth > 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__1;
  arguments->slots[1] = frame->slots[2] /* depth */;
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
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 71: ... :
  // 72:   for_each_dimension value depth-1 push(indices idx) body
  frame->slots[6] /* temp__2 */ = create_closure(entry__8_6, 0);
  // 73: :
  // 74:   body indices* idx value
  frame->slots[7] /* temp__3 */ = create_closure(entry__8_9, 0);
  // 70: if
  // 71:   depth > 1:
  // 72:     for_each_dimension value depth-1 push(indices idx) body
  // 73:   :
  // 74:     body indices* idx value
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
static void entry__8_3(void) {
  allocate_initialized_frame_gc(4, 5);
  // slot allocations:
  // table: 0
  // depth: 1
  // indices: 2
  // body: 3
  frame->slots[0] = myself->closure.frame->slots[0]; /* table */
  frame->slots[1] = myself->closure.frame->slots[1]; /* depth */
  frame->slots[2] = myself->closure.frame->slots[2]; /* indices */
  frame->slots[3] = myself->closure.frame->slots[3]; /* body */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 69: ... : (idx value)
  // 70:   if
  // 71:     depth > 1:
  // 72:       for_each_dimension value depth-1 push(indices idx) body
  // 73:     :
  // 74:       body indices* idx value
  frame->slots[4] /* temp__1 */ = create_closure(entry__8_4, 2);
  // 69: for_each table: (idx value)
  // 70:   if
  // 71:     depth > 1:
  // 72:       for_each_dimension value depth-1 push(indices idx) body
  // 73:     :
  // 74:       body indices* idx value
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* table */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__8_1(void) {
  allocate_initialized_frame_gc(4, 6);
  // slot allocations:
  // table: 0
  // depth: 1
  // indices: 2
  // body: 3
  if (argument_count != 4) {
    invalid_arguments_error();
    return;
  }
  // 68: ... table.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* table */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__8_2;
}
static void cont__8_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 68: ... :
  // 69:   for_each table: (idx value)
  // 70:     if
  // 71:       depth > 1:
  // 72:         for_each_dimension value depth-1 push(indices idx) body
  // 73:       :
  // 74:         body indices* idx value
  frame->slots[5] /* temp__2 */ = create_closure(entry__8_3, 0);
  // 68: if table.is_defined:
  // 69:   for_each table: (idx value)
  // 70:     if
  // 71:       depth > 1:
  // 72:         for_each_dimension value depth-1 push(indices idx) body
  // 73:       :
  // 74:         body indices* idx value
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__9_1(void) {
  allocate_initialized_frame_gc(2, 6);
  // slot allocations:
  // self: 0
  // body: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 77: ... table_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = var._table_of;
  func = myself->type;
  frame->cont = cont__9_2;
}
static void cont__9_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 77: ... dimensions_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = var._dimensions_of;
  func = myself->type;
  frame->cont = cont__9_3;
}
static void cont__9_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 77: ... length_of(dimensions_of(self))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__9_4;
}
static void cont__9_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 77: ... list()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__9_5;
}
static void cont__9_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__4 */ = arguments->slots[0];
  // 77: for_each_dimension table_of(self) length_of(dimensions_of(self)) list() body
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  arguments->slots[2] = frame->slots[5] /* temp__4 */;
  arguments->slots[3] = frame->slots[1] /* body */;
  result_count = frame->caller_result_count;
  myself = var._for_each_dimension;
  func = myself->type;
  frame = frame->caller_frame;
}
EXPORT void collect__basic__types__multi_dimensional_table(void) {
  var._dimensions_of = collect_node(var._dimensions_of);
  var._table_of = collect_node(var._table_of);
  var._insert_into = collect_node(var._insert_into);
  func__3_1 = collect_node(func__3_1);
  var._get_item = collect_node(var._get_item);
  func__4_1 = collect_node(func__4_1);
  var.types__multi_dimensional_table = collect_node(var.types__multi_dimensional_table);
  func__5_1 = collect_node(func__5_1);
  var.std__multi_dimensional_table = collect_node(var.std__multi_dimensional_table);
  func__7_1 = collect_node(func__7_1);
  var._for_each_dimension = collect_node(var._for_each_dimension);
  func__8_1 = collect_node(func__8_1);
  func__9_1 = collect_node(func__9_1);
  number__0 = collect_node(number__0);
  number__1 = collect_node(number__1);
  number__2 = collect_node(number__2);
}

static int already_run_phase_1 = false;

EXPORT void phase_1__basic__types__multi_dimensional_table(void) {
  if (already_run_phase_1) return;
  already_run_phase_1 = true;
  register_module_info(&module_info);
  register_polymorphic_function_with_setter("_basic__types__multi_dimensional_table::dimensions_of", &poly_idx__dimensions_of);
  register_polymorphic_function_with_setter("_basic__types__multi_dimensional_table::table_of", &poly_idx__table_of);
}

static int already_run_phase_2 = false;

EXPORT void phase_2__basic__types__multi_dimensional_table(void) {
  if (already_run_phase_2) return;
  already_run_phase_2 = true;
  number__0 = from_uint32(0U);
  number__1 = from_uint32(1U);
  number__2 = from_uint32(2U);
}

static int already_run_phase_3 = false;

EXPORT void phase_3__basic__types__multi_dimensional_table(void) {
  if (already_run_phase_3) return;
  already_run_phase_3 = true;
  set_module("basic__types__multi_dimensional_table");
  set_used_namespaces(used_namespaces);
  func__3_1 = create_future();
  func__4_1 = create_future();
  func__5_1 = create_future();
  define_single_assign_static("types", "multi_dimensional_table", get__types__multi_dimensional_table, &var.types__multi_dimensional_table);
  func__7_1 = create_future();
  define_single_assign_static("std", "multi_dimensional_table", get__std__multi_dimensional_table, &var.std__multi_dimensional_table);
  func__8_1 = create_future();
  func__9_1 = create_future();
}

static int already_run_phase_4 = false;

EXPORT void phase_4__basic__types__multi_dimensional_table(void) {
  if (already_run_phase_4) return;
  already_run_phase_4 = true;
  set_module("basic__types__multi_dimensional_table");
  set_used_namespaces(used_namespaces);
  use_polymorphic_function(NULL, "for_each", &get__for_each, &poly_idx__for_each);
  use_read_only(NULL, "if", &get__if, &get_value_or_future__if);
  use_read_only(NULL, "is_defined", &get__is_defined, &get_value_or_future__is_defined);
  use_read_only(NULL, "is_undefined", &get__is_undefined, &get_value_or_future__is_undefined);
  use_read_only(NULL, "length_of", &get__length_of, &get_value_or_future__length_of);
  use_read_only(NULL, "list", &get__list, &get_value_or_future__list);
  use_read_only(NULL, "push", &get__push, &get_value_or_future__push);
  use_read_only(NULL, "range", &get__range, &get_value_or_future__range);
  use_read_only("std", "less", &get__std__less, &get_value_or_future__std__less);
  use_read_only("std", "minus", &get__std__minus, &get_value_or_future__std__minus);
  use_read_only("std", "negate", &get__std__negate, &get_value_or_future__std__negate);
  use_read_only(NULL, "undefined", &get__undefined, &get_value_or_future__undefined);
  use_read_only(NULL, "unless", &get__unless, &get_value_or_future__unless);
  define_attribute("types", "multi_dimensional_table", poly_idx__table_of, get__undefined());
  define_method("types", "multi_dimensional_table", poly_idx__for_each, func__9_1);
}

static int already_run_phase_5 = false;

EXPORT void phase_5__basic__types__multi_dimensional_table(void) {
  if (already_run_phase_5) return;
  already_run_phase_5 = true;
  assign_value(&var._dimensions_of, create_function(type__dimensions_of, -1));
  assign_value(&var._table_of, create_function(type__table_of, -1));
  assign_variable(&var._insert_into, &func__3_1);
  assign_variable(&var._get_item, &func__4_1);
  assign_variable(&var.types__multi_dimensional_table, &func__5_1);
  assign_variable(&var.std__multi_dimensional_table, &func__7_1);
  assign_variable(&var._for_each_dimension, &func__8_1);
}

static int already_run_phase_6 = false;

EXPORT void phase_6__basic__types__multi_dimensional_table(void) {
  if (already_run_phase_6) return;
  already_run_phase_6 = true;
  assign_value(&func__3_1, create_function(entry__3_1, 3));
  assign_value(&func__4_1, create_function(entry__4_1, 2));
  assign_value(&func__5_1, create_function(entry__5_1, -1));
  assign_value(&func__7_1, create_function(entry__7_1, -1));
  assign_value(&func__8_1, create_function(entry__8_1, 4));
  assign_value(&func__9_1, create_function(entry__9_1, 2));
  register_collector(collect__basic__types__multi_dimensional_table);
}
