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
IMPORT NODE *create_cell(void);
REGISTER int argument_count ASM("ebx");
IMPORT void invalid_arguments_error(void);
REGISTER FRAME *arguments ASM("r12");
IMPORT void *node_p;
IMPORT int result_count;
REGISTER NODE *myself ASM("r13");
IMPORT void invalid_results_error(void);
typedef struct CELL {
  FUNC type;
  struct ATTRIBUTES *attributes;
  NODE *contents;
} CELL;
IMPORT NODE *create_closure(FUNC type, int par_count);
IMPORT NODE *clone_object_and_attributes(NODE *node);
IMPORT void *update_start_p;
IMPORT void set_attribute_value(ATTRIBUTES *attributes, int idx, void *attr);
IMPORT NODE *collect_node(NODE *node);
IMPORT void register_module_info(MODULE_INFO *info);
IMPORT NODE *from_uchar32(unsigned int chr);
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
IMPORT void use_polymorphic_function(
  const char *namespace, const char *name, NODE_GETTER *getter, int *id
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
static NODE_GETTER get__for_each;
static NODE_GETTER get_value_or_future__for_each;
static NODE_GETTER get__if;
static NODE_GETTER get_value_or_future__if;
static NODE_GETTER get__inc;
static NODE_GETTER get_value_or_future__inc;
static NODE_GETTER get__length_of;
static NODE_GETTER get_value_or_future__length_of;
static int poly_idx__line_no_of;
static NODE_GETTER get__line_no_of;
static NODE_GETTER get__list;
static NODE_GETTER get_value_or_future__list;
static NODE_GETTER get__push;
static NODE_GETTER get_value_or_future__push;
static NODE_GETTER get__range;
static NODE_GETTER get_value_or_future__range;
static int poly_idx__sim2c__text_of;
static NODE_GETTER get__sim2c__text_of;
static NODE_GETTER get__std__and;
static NODE_GETTER get_value_or_future__std__and;
static NODE_GETTER get__std__equal;
static NODE_GETTER get_value_or_future__std__equal;
static NODE_GETTER get__std__less;
static NODE_GETTER get_value_or_future__std__less;
static NODE_GETTER get__std__not;
static NODE_GETTER get_value_or_future__std__not;
static NODE_GETTER get__std__or;
static NODE_GETTER get_value_or_future__std__or;
static NODE_GETTER get__std__plus;
static NODE_GETTER get_value_or_future__std__plus;
static NODE_GETTER get__submodule_no;
static NODE_GETTER get_value_or_future__submodule_no;
static int poly_idx__submodule_no_of;
static NODE_GETTER get__submodule_no_of;
static NODE_GETTER get__types__object;
static NODE_GETTER get_value_or_future__types__object;
static struct {
  NODE *sim2c__cut_into_fragments;
} var;
static const char *var_names[] = {
};
static NODE *func__1_1;
static void entry__1_1(void);
static FRAME_INFO frame__1_1 = {5, {"buf", "fragments", "start_idx", "start_no", "no"}};
static void cont__1_2(void);
static NODE *func__1_3;
static void entry__1_3(void);
static FRAME_INFO frame__1_3 = {7, {"idx", "chr", "no", "buf", "fragments", "start_no", "start_idx"}};
static void cont__1_4(void);
static NODE *func__1_5;
static void entry__1_5(void);
static FRAME_INFO frame__1_5 = {6, {"no", "idx", "buf", "fragments", "start_no", "start_idx"}};
static void cont__1_6(void);
static void cont__1_7(void);
static void cont__1_8(void);
static NODE *func__1_9;
static void entry__1_9(void);
static FRAME_INFO frame__1_9 = {2, {"buf", "idx"}};
static void cont__1_10(void);
static void cont__1_11(void);
static void cont__1_12(void);
static NODE *func__1_13;
static void entry__1_13(void);
static FRAME_INFO frame__1_13 = {2, {"buf", "idx"}};
static void cont__1_14(void);
static void cont__1_15(void);
static void cont__1_16(void);
static void cont__1_17(void);
static void cont__1_18(void);
static void cont__1_19(void);
static NODE *func__1_20;
static void entry__1_20(void);
static FRAME_INFO frame__1_20 = {6, {"fragments", "start_no", "buf", "start_idx", "idx", "no"}};
static void cont__1_21(void);
static void cont__1_22(void);
static void cont__1_23(void);
static void cont__1_24(void);
static NODE *get__sim2c__cut_into_fragments(void) {
  return var.sim2c__cut_into_fragments;
}
void run__fragments(void);

static CONTINUATION_INFO continuation_info[] = {
  {run__fragments, NULL, },
  {entry__1_13, NULL, 39, 39, 59, 63},
  {cont__1_14, &frame__1_13, 39, 39, 55, 64},
  {cont__1_15, &frame__1_13, 39, 39, 55, 71},
  {cont__1_16, &frame__1_13, 39, 39, 55, 71},
  {cont__1_17, &frame__1_13, 39, 39, 55, 71},
  {entry__1_9, NULL, 39, 39, 39, 43},
  {cont__1_10, &frame__1_9, 39, 39, 35, 44},
  {cont__1_11, &frame__1_9, 39, 39, 35, 50},
  {cont__1_12, &frame__1_9, 39, 39, 35, 71},
  {cont__1_18, &frame__1_9, 39, 39, 35, 71},
  {entry__1_20, NULL, 45, 45, 29, 52},
  {cont__1_21, &frame__1_20, 40, 45, 9, 53},
  {cont__1_22, &frame__1_20, 47, 47, 9, 24},
  {cont__1_23, &frame__1_20, 47, 47, 24, 24},
  {entry__1_5, NULL, 38, 38, 7, 13},
  {cont__1_6, &frame__1_5, 39, 39, 17, 30},
  {cont__1_7, &frame__1_5, 39, 39, 10, 30},
  {cont__1_8, &frame__1_5, 39, 39, 10, 71},
  {cont__1_19, &frame__1_5, 39, 47, 7, 24},
  {entry__1_3, NULL, 37, 37, 8, 20},
  {cont__1_4, &frame__1_3, 37, 47, 5, 25},
  {entry__1_1, NULL, 32, 32, 3, 20},
  {cont__1_2, &frame__1_1, 36, 47, 3, 26},
  {cont__1_24, &frame__1_1, 48, 48, 3, 14}
};

union NODE {
  struct {
    FUNC type;
    ATTRIBUTES *attributes;
  };
  CONTINUATION continuation;
  CLOSURE closure;
};
static NODE *character__10;
static NODE *character__32;
static NODE *character__125;
static NODE *number__1;

static const char *used_namespaces[] = {
  "std",
  "sim2c",
  "node",
  NULL
};

static MODULE_INFO module_info = {
  NULL,
  "fragments",
  continuation_info,
  sizeof(continuation_info)/sizeof(CONTINUATION_INFO),
  (NODE **)&var,
  var_names,
  sizeof(var_names)/sizeof(const char *),
  used_namespaces,
  {DEBUG_FILENAME("fragments.sim")}
};

/******
C O D E
******/

static int already_run = false;

EXPORT void run__fragments(void) {
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
  allocate_initialized_frame_gc(1, 6);
  // slot allocations:
  // buf: 0
  // fragments: 1
  // start_idx: 2
  // start_no: 3
  // no: 4
  frame->slots[1] /* fragments */ = create_cell();
  frame->slots[2] /* start_idx */ = create_cell();
  frame->slots[3] /* start_no */ = create_cell();
  frame->slots[4] /* no */ = create_cell();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 32: $$fragments list()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__1_2;
}
static void cont__1_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* fragments */ = arguments->slots[0];
  // 33: $$start_idx 1
  ((CELL *)frame->slots[2])->contents /* start_idx */ = number__1;
  // 34: $$start_no 1
  ((CELL *)frame->slots[3])->contents /* start_no */ = number__1;
  // 35: $$no 1
  ((CELL *)frame->slots[4])->contents /* no */ = number__1;
  // 36: ... : (idx chr)
  // 37:   if chr == '@nl;':
  // 38:     inc &no
  // 39:     if idx == length_of(buf) || buf(idx+1) > ' ' && buf(idx+1) != '}':
  // 40:       push
  // 41:         &fragments
  // 42:         types::object
  // 43:           .submodule_no_of submodule_no
  // 44:           .line_no_of start_no
  // 45:           .sim2c::text_of range(buf start_idx idx)
  // ...
  frame->slots[5] /* temp__1 */ = create_closure(entry__1_3, 2);
  // 36: for_each buf: (idx chr)
  // 37:   if chr == '@nl;':
  // 38:     inc &no
  // 39:     if idx == length_of(buf) || buf(idx+1) > ' ' && buf(idx+1) != '}':
  // 40:       push
  // 41:         &fragments
  // 42:         types::object
  // 43:           .submodule_no_of submodule_no
  // 44:           .line_no_of start_no
  // 45:           .sim2c::text_of range(buf start_idx idx)
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* buf */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__1_24;
}
static void entry__1_20(void) {
  allocate_initialized_frame_gc(6, 8);
  // slot allocations:
  // fragments: 0
  // start_no: 1
  // buf: 2
  // start_idx: 3
  // idx: 4
  // no: 5
  frame->slots[0] = myself->closure.frame->slots[3]; /* fragments */
  frame->slots[1] = myself->closure.frame->slots[4]; /* start_no */
  frame->slots[2] = myself->closure.frame->slots[2]; /* buf */
  frame->slots[3] = myself->closure.frame->slots[5]; /* start_idx */
  frame->slots[4] = myself->closure.frame->slots[1]; /* idx */
  frame->slots[5] = myself->closure.frame->slots[0]; /* no */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 45: ... range(buf start_idx idx)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* buf */;
  arguments->slots[1] = ((CELL *)frame->slots[3])->contents /* start_idx */;
  arguments->slots[2] = frame->slots[4] /* idx */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__1_21;
}
static void cont__1_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 42: types::object
  // 43:   .submodule_no_of submodule_no
  // 44:   .line_no_of start_no
  // 45:   .sim2c::text_of range(buf start_idx idx)
  {
    NODE *temp = clone_object_and_attributes(get__types__object());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__submodule_no_of, get__submodule_no());
    set_attribute_value(temp->attributes, poly_idx__line_no_of, ((CELL *)frame->slots[1])->contents /* start_no */);
    set_attribute_value(temp->attributes, poly_idx__sim2c__text_of, frame->slots[7] /* temp__2 */);
    frame->slots[6] /* temp__1 */ = temp;

  }
  // 40: push
  // 41:   &fragments
  // 42:   types::object
  // 43:     .submodule_no_of submodule_no
  // 44:     .line_no_of start_no
  // 45:     .sim2c::text_of range(buf start_idx idx)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* fragments */;
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__1_22;
}
static void cont__1_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* fragments */ = arguments->slots[0];
  // 46: !start_no no
  ((CELL *)frame->slots[1])->contents /* start_no */ = ((CELL *)frame->slots[5])->contents /* no */;
  // 47: !start_idx idx+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* idx */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__1_23;
}
static void cont__1_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* start_idx */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__1_5(void) {
  allocate_initialized_frame_gc(6, 11);
  // slot allocations:
  // no: 0
  // idx: 1
  // buf: 2
  // fragments: 3
  // start_no: 4
  // start_idx: 5
  frame->slots[0] = myself->closure.frame->slots[2]; /* no */
  frame->slots[1] = myself->closure.frame->slots[0]; /* idx */
  frame->slots[2] = myself->closure.frame->slots[3]; /* buf */
  frame->slots[3] = myself->closure.frame->slots[4]; /* fragments */
  frame->slots[4] = myself->closure.frame->slots[5]; /* start_no */
  frame->slots[5] = myself->closure.frame->slots[6]; /* start_idx */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 38: inc &no
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* no */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__1_6;
}
static void cont__1_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* no */ = arguments->slots[0];
  // 39: ... length_of(buf)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* buf */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__1_7;
}
static void cont__1_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__3 */ = arguments->slots[0];
  // 39: ... idx == length_of(buf)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* idx */;
  arguments->slots[1] = frame->slots[8] /* temp__3 */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__1_8;
}
static void cont__1_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 39: ... buf(idx+1) > ' ' && buf(idx+1) != '}'
  frame->slots[9] /* temp__4 */ = create_closure(entry__1_9, 0);
  // 39: ... idx == length_of(buf) || buf(idx+1) > ' ' && buf(idx+1) != '}'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__2 */;
  arguments->slots[1] = frame->slots[9] /* temp__4 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__1_19;
}
static void entry__1_9(void) {
  allocate_initialized_frame_gc(2, 7);
  // slot allocations:
  // buf: 0
  // idx: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* buf */
  frame->slots[1] = myself->closure.frame->slots[1]; /* idx */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 39: ... idx+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* idx */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__1_10;
}
static void cont__1_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__4 */ = arguments->slots[0];
  // 39: ... buf(idx+1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__4 */;
  result_count = 1;
  myself = frame->slots[0] /* buf */;
  func = myself->type;
  frame->cont = cont__1_11;
}
static void cont__1_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 39: ... buf(idx+1) > ' '
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__32;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__1_12;
}
static void cont__1_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 39: ... buf(idx+1) != '}'
  frame->slots[6] /* temp__5 */ = create_closure(entry__1_13, 0);
  // 39: ... buf(idx+1) > ' ' && buf(idx+1) != '}'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[6] /* temp__5 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__1_18;
}
static void entry__1_13(void) {
  allocate_initialized_frame_gc(2, 6);
  // slot allocations:
  // buf: 0
  // idx: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* buf */
  frame->slots[1] = myself->closure.frame->slots[1]; /* idx */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 39: ... idx+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* idx */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__1_14;
}
static void cont__1_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__4 */ = arguments->slots[0];
  // 39: ... buf(idx+1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__4 */;
  result_count = 1;
  myself = frame->slots[0] /* buf */;
  func = myself->type;
  frame->cont = cont__1_15;
}
static void cont__1_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 39: ... buf(idx+1) != '}'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  arguments->slots[1] = character__125;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__1_16;
}
static void cont__1_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 39: ... buf(idx+1) != '}'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__1_17;
}
static void cont__1_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 39: ... buf(idx+1) != '}'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__1_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 39: ... buf(idx+1) > ' ' && buf(idx+1) != '}'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__1_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 39: ... :
  // 40:   push
  // 41:     &fragments
  // 42:     types::object
  // 43:       .submodule_no_of submodule_no
  // 44:       .line_no_of start_no
  // 45:       .sim2c::text_of range(buf start_idx idx)
  // 46:   !start_no no
  // 47:   !start_idx idx+1
  frame->slots[10] /* temp__5 */ = create_closure(entry__1_20, 0);
  // 39: if idx == length_of(buf) || buf(idx+1) > ' ' && buf(idx+1) != '}':
  // 40:   push
  // 41:     &fragments
  // 42:     types::object
  // 43:       .submodule_no_of submodule_no
  // 44:       .line_no_of start_no
  // 45:       .sim2c::text_of range(buf start_idx idx)
  // 46:   !start_no no
  // 47:   !start_idx idx+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[10] /* temp__5 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__1_3(void) {
  allocate_initialized_frame_gc(7, 9);
  // slot allocations:
  // idx: 0
  // chr: 1
  // no: 2
  // buf: 3
  // fragments: 4
  // start_no: 5
  // start_idx: 6
  frame->slots[2] = myself->closure.frame->slots[4]; /* no */
  frame->slots[3] = myself->closure.frame->slots[0]; /* buf */
  frame->slots[4] = myself->closure.frame->slots[1]; /* fragments */
  frame->slots[5] = myself->closure.frame->slots[3]; /* start_no */
  frame->slots[6] = myself->closure.frame->slots[2]; /* start_idx */
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 37: ... chr == '@nl;'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* chr */;
  arguments->slots[1] = character__10;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__1_4;
}
static void cont__1_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 37: ... :
  // 38:   inc &no
  // 39:   if idx == length_of(buf) || buf(idx+1) > ' ' && buf(idx+1) != '}':
  // 40:     push
  // 41:       &fragments
  // 42:       types::object
  // 43:         .submodule_no_of submodule_no
  // 44:         .line_no_of start_no
  // 45:         .sim2c::text_of range(buf start_idx idx)
  // 46:     !start_no no
  // ...
  frame->slots[8] /* temp__2 */ = create_closure(entry__1_5, 0);
  // 37: if chr == '@nl;':
  // 38:   inc &no
  // 39:   if idx == length_of(buf) || buf(idx+1) > ' ' && buf(idx+1) != '}':
  // 40:     push
  // 41:       &fragments
  // 42:       types::object
  // 43:         .submodule_no_of submodule_no
  // 44:         .line_no_of start_no
  // 45:         .sim2c::text_of range(buf start_idx idx)
  // 46:     !start_no no
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__1_24(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 48: -> fragments
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* fragments */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
EXPORT void collect__fragments(void) {
  var.sim2c__cut_into_fragments = collect_node(var.sim2c__cut_into_fragments);
}

static int already_run_phase_1 = false;

EXPORT void phase_1__fragments(void) {
  if (already_run_phase_1) return;
  already_run_phase_1 = true;
  register_module_info(&module_info);
}

static int already_run_phase_2 = false;

EXPORT void phase_2__fragments(void) {
  if (already_run_phase_2) return;
  already_run_phase_2 = true;
  character__10 = from_uchar32(10);
  character__32 = from_uchar32(32);
  character__125 = from_uchar32(125);
  number__1 = from_uint32(1U);
  func__1_1 = create_function(entry__1_1, 1);
}

static int already_run_phase_3 = false;

EXPORT void phase_3__fragments(void) {
  if (already_run_phase_3) return;
  already_run_phase_3 = true;
  set_module("fragments");
  set_used_namespaces(used_namespaces);
  define_single_assign_static("sim2c", "cut_into_fragments", get__sim2c__cut_into_fragments, &var.sim2c__cut_into_fragments);
}

static int already_run_phase_4 = false;

EXPORT void phase_4__fragments(void) {
  if (already_run_phase_4) return;
  already_run_phase_4 = true;
  set_module("fragments");
  set_used_namespaces(used_namespaces);
  use_read_only(NULL, "for_each", &get__for_each, &get_value_or_future__for_each);
  use_read_only(NULL, "if", &get__if, &get_value_or_future__if);
  use_read_only(NULL, "inc", &get__inc, &get_value_or_future__inc);
  use_read_only(NULL, "length_of", &get__length_of, &get_value_or_future__length_of);
  use_polymorphic_function(NULL, "line_no_of", &get__line_no_of, &poly_idx__line_no_of);
  use_read_only(NULL, "list", &get__list, &get_value_or_future__list);
  use_read_only(NULL, "push", &get__push, &get_value_or_future__push);
  use_read_only(NULL, "range", &get__range, &get_value_or_future__range);
  use_polymorphic_function("sim2c", "text_of", &get__sim2c__text_of, &poly_idx__sim2c__text_of);
  use_read_only("std", "and", &get__std__and, &get_value_or_future__std__and);
  use_read_only("std", "equal", &get__std__equal, &get_value_or_future__std__equal);
  use_read_only("std", "less", &get__std__less, &get_value_or_future__std__less);
  use_read_only("std", "not", &get__std__not, &get_value_or_future__std__not);
  use_read_only("std", "or", &get__std__or, &get_value_or_future__std__or);
  use_read_only("std", "plus", &get__std__plus, &get_value_or_future__std__plus);
  use_read_only(NULL, "submodule_no", &get__submodule_no, &get_value_or_future__submodule_no);
  use_polymorphic_function(NULL, "submodule_no_of", &get__submodule_no_of, &poly_idx__submodule_no_of);
  use_read_only("types", "object", &get__types__object, &get_value_or_future__types__object);
}

static int already_run_phase_5 = false;

EXPORT void phase_5__fragments(void) {
  if (already_run_phase_5) return;
  already_run_phase_5 = true;
  assign_variable(&var.sim2c__cut_into_fragments, &func__1_1);
}

static int already_run_phase_6 = false;

EXPORT void phase_6__fragments(void) {
  if (already_run_phase_6) return;
  already_run_phase_6 = true;
  register_collector(collect__fragments);
}
