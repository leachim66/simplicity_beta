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
IMPORT void allocate_arguments(void);
IMPORT NODE *create_cell(void);
REGISTER int argument_count ASM("ebx");
IMPORT void too_few_arguments_error(void);
REGISTER FRAME *arguments ASM("r12");
IMPORT NODE *from_arguments(int first_idx, int count);
typedef struct CELL {
  FUNC type;
  struct ATTRIBUTES *attributes;
  NODE *contents;
} CELL;
IMPORT NODE *create_closure(FUNC type, int par_count);
IMPORT void *node_p;
IMPORT int result_count;
REGISTER NODE *myself ASM("r13");
IMPORT void invalid_arguments_error(void);
IMPORT void invalid_results_error(void);
IMPORT NODE *create_future(void);
IMPORT void initialize_future(NODE *var, NODE *val);
IMPORT NODE *collect_node(NODE *node);
IMPORT void register_module_info(MODULE_INFO *info);
IMPORT NODE *from_uchar32(unsigned int chr);
IMPORT NODE *from_uint32(uint32_t val);
IMPORT NODE *from_latin_1_string(const char *str, long len);
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
static NODE_GETTER get__append;
static NODE_GETTER get_value_or_future__append;
static NODE_GETTER get__contains;
static NODE_GETTER get_value_or_future__contains;
static NODE_GETTER get__for_each_pair;
static NODE_GETTER get_value_or_future__for_each_pair;
static NODE_GETTER get__if;
static NODE_GETTER get_value_or_future__if;
static NODE_GETTER get__indented;
static NODE_GETTER get_value_or_future__indented;
static NODE_GETTER get__serialize;
static NODE_GETTER get_value_or_future__serialize;
static NODE_GETTER get__std__equal;
static NODE_GETTER get_value_or_future__std__equal;
static NODE_GETTER get__std__not;
static NODE_GETTER get_value_or_future__std__not;
static NODE_GETTER get__write_to;
static NODE_GETTER get_value_or_future__write_to;
static struct {
  NODE *std__serialize_object;
} var;
static const char *var_names[] = {
};
static NODE *func__1_1_std__serialize_object;
static void entry__1_1_std__serialize_object(void);
static FRAME_INFO frame__1_1_std__serialize_object = {5, {"tag", "prototype", "obj", "attributes", "buf"}};
static NODE *func__1_2;
static void entry__1_2(void);
static FRAME_INFO frame__1_2 = {6, {"attribute_name", "attribute_getter", "obj", "prototype", "buf", "attribute"}};
static void cont__1_3(void);
static void cont__1_4(void);
static void cont__1_5(void);
static void cont__1_6(void);
static NODE *func__1_7;
static void entry__1_7(void);
static FRAME_INFO frame__1_7 = {4, {"attribute", "buf", "attribute_name", "text"}};
static void cont__1_8(void);
static NODE *string__fa73ac15f296bec;
static NODE *string__578a5af303e9cdb;
static void cont__1_11(void);
static void cont__1_12(void);
static NODE *func__1_13;
static void entry__1_13(void);
static FRAME_INFO frame__1_13 = {2, {"buf", "text"}};
static void cont__1_14(void);
static void cont__1_15(void);
static NODE *func__1_16;
static void entry__1_16(void);
static FRAME_INFO frame__1_16 = {2, {"buf", "text"}};
static void cont__1_17(void);
static void cont__1_18(void);
static void cont__1_19(void);
static NODE *func__1_20;
static void entry__1_20(void);
static FRAME_INFO frame__1_20 = {1, {"buf"}};
static NODE *string__2d7981f4e6482bec;
static void cont__1_22(void);
static void cont__1_23(void);
static NODE *get__std__serialize_object(void) {
  return var.std__serialize_object;
}
void run__basic__serialize(void);

static CONTINUATION_INFO continuation_info[] = {
  {run__basic__serialize, NULL, },
  {entry__1_13, NULL, 44, 44, 32, 47},
  {cont__1_14, &frame__1_13, 44, 44, 11, 47},
  {cont__1_15, &frame__1_13, 44, 44, 47, 47},
  {entry__1_16, NULL, 46, 46, 11, 32},
  {cont__1_17, &frame__1_16, 46, 46, 32, 32},
  {entry__1_7, NULL, 40, 40, 7, 31},
  {cont__1_8, &frame__1_7, 41, 41, 7, 47},
  {cont__1_11, &frame__1_7, 43, 43, 9, 30},
  {cont__1_12, &frame__1_7, 42, 46, 7, 33},
  {entry__1_2, NULL, 38, 38, 5, 36},
  {cont__1_3, &frame__1_2, 39, 39, 21, 47},
  {cont__1_4, &frame__1_2, 39, 39, 8, 47},
  {cont__1_5, &frame__1_2, 39, 39, 8, 47},
  {cont__1_6, &frame__1_2, 39, 46, 5, 34},
  {entry__1_20, NULL, 47, 47, 18, 33},
  {cont__1_22, &frame__1_20, 47, 47, 33, 33},
  {entry__1_1_std__serialize_object, NULL, 37, 46, 3, 35},
  {cont__1_18, &frame__1_1_std__serialize_object, 47, 47, 6, 15},
  {cont__1_19, &frame__1_1_std__serialize_object, 47, 47, 3, 33},
  {cont__1_23, &frame__1_1_std__serialize_object, 48, 48, 3, 8}
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
static NODE *number__4;
static NODE *character__32;

static const char *used_namespaces[] = {
  "std",
  NULL
};

static MODULE_INFO module_info = {
  NULL,
  "basic__serialize",
  continuation_info,
  sizeof(continuation_info)/sizeof(CONTINUATION_INFO),
  (NODE **)&var,
  var_names,
  sizeof(var_names)/sizeof(const char *),
  used_namespaces,
  {DEBUG_FILENAME("basic/serialize.sim")}
};

/******
C O D E
******/

static int already_run = false;

EXPORT void run__basic__serialize(void) {
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
static void entry__1_1_std__serialize_object(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(4, 7);
  // slot allocations:
  // tag: 0
  // prototype: 1
  // obj: 2
  // attributes: 3
  // buf: 4
  frame->slots[4] /* buf */ = create_cell();
  if (argument_count < 3) {
    too_few_arguments_error();
    return;
  }
  frame->slots[0] /* tag */ = arguments->slots[0];
  frame->slots[1] /* prototype */ = arguments->slots[1];
  frame->slots[2] /* obj */ = arguments->slots[2];
  frame->slots[3] /* attributes */ = from_arguments(3, argument_count-3);
  // 36: $$buf tag
  ((CELL *)frame->slots[4])->contents /* buf */ = frame->slots[0] /* tag */;
  // 37: ... : (attribute_name attribute_getter)
  // 38:   $attribute attribute_getter(obj)
  // 39:   if attribute != attribute_getter(prototype):
  // 40:     $text attribute.serialize
  // 41:     write_to &buf "@nl;  " attribute_name ":"
  // 42:     if
  // 43:       text .contains. '@nl;':
  // 44:         write_to &buf '@nl;' indented(4 text)
  // 45:       :
  // 46:         write_to &buf ' ' text
  frame->slots[5] /* temp__1 */ = create_closure(entry__1_2, 2);
  // 37: for_each_pair attributes: (attribute_name attribute_getter)
  // 38:   $attribute attribute_getter(obj)
  // 39:   if attribute != attribute_getter(prototype):
  // 40:     $text attribute.serialize
  // 41:     write_to &buf "@nl;  " attribute_name ":"
  // 42:     if
  // 43:       text .contains. '@nl;':
  // 44:         write_to &buf '@nl;' indented(4 text)
  // 45:       :
  // 46:         write_to &buf ' ' text
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* attributes */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 0;
  myself = get__for_each_pair();
  func = myself->type;
  frame->cont = cont__1_18;
}
static void entry__1_13(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // buf: 0
  // text: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* buf */
  frame->slots[1] = myself->closure.frame->slots[3]; /* text */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 44: ... indented(4 text)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__4;
  arguments->slots[1] = frame->slots[1] /* text */;
  result_count = 1;
  myself = get__indented();
  func = myself->type;
  frame->cont = cont__1_14;
}
static void cont__1_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 44: write_to &buf '@nl;' indented(4 text)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* buf */;
  arguments->slots[1] = character__10;
  arguments->slots[2] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__write_to();
  func = myself->type;
  frame->cont = cont__1_15;
}
static void cont__1_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* buf */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__1_16(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // buf: 0
  // text: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* buf */
  frame->slots[1] = myself->closure.frame->slots[3]; /* text */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 46: write_to &buf ' ' text
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* buf */;
  arguments->slots[1] = character__32;
  arguments->slots[2] = frame->slots[1] /* text */;
  result_count = 1;
  myself = get__write_to();
  func = myself->type;
  frame->cont = cont__1_17;
}
static void cont__1_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* buf */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__1_7(void) {
  allocate_initialized_frame_gc(3, 7);
  // slot allocations:
  // attribute: 0
  // buf: 1
  // attribute_name: 2
  // text: 3
  frame->slots[0] = myself->closure.frame->slots[5]; /* attribute */
  frame->slots[1] = myself->closure.frame->slots[4]; /* buf */
  frame->slots[2] = myself->closure.frame->slots[0]; /* attribute_name */
  frame->slots[3] /* text */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 40: $text attribute.serialize
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* attribute */;
  result_count = 1;
  myself = get__serialize();
  func = myself->type;
  frame->cont = cont__1_8;
}
static void cont__1_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* text */, arguments->slots[0]);
  // 41: write_to &buf "@nl;  " attribute_name ":"
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* buf */;
  arguments->slots[1] = string__fa73ac15f296bec;
  arguments->slots[2] = frame->slots[2] /* attribute_name */;
  arguments->slots[3] = string__578a5af303e9cdb;
  result_count = 1;
  myself = get__write_to();
  func = myself->type;
  frame->cont = cont__1_11;
}
static void cont__1_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* buf */ = arguments->slots[0];
  // 43: text .contains. '@nl;'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* text */;
  arguments->slots[1] = character__10;
  result_count = 1;
  myself = get__contains();
  func = myself->type;
  frame->cont = cont__1_12;
}
static void cont__1_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 43: ... :
  // 44:   write_to &buf '@nl;' indented(4 text)
  frame->slots[5] /* temp__2 */ = create_closure(entry__1_13, 0);
  // 45: :
  // 46:   write_to &buf ' ' text
  frame->slots[6] /* temp__3 */ = create_closure(entry__1_16, 0);
  // 42: if
  // 43:   text .contains. '@nl;':
  // 44:     write_to &buf '@nl;' indented(4 text)
  // 45:   :
  // 46:     write_to &buf ' ' text
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
static void entry__1_2(void) {
  allocate_initialized_frame_gc(5, 10);
  // slot allocations:
  // attribute_name: 0
  // attribute_getter: 1
  // obj: 2
  // prototype: 3
  // buf: 4
  // attribute: 5
  frame->slots[2] = myself->closure.frame->slots[2]; /* obj */
  frame->slots[3] = myself->closure.frame->slots[1]; /* prototype */
  frame->slots[4] = myself->closure.frame->slots[4]; /* buf */
  frame->slots[5] /* attribute */ = create_future();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 38: $attribute attribute_getter(obj)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* obj */;
  result_count = 1;
  myself = frame->slots[1] /* attribute_getter */;
  func = myself->type;
  frame->cont = cont__1_3;
}
static void cont__1_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* attribute */, arguments->slots[0]);
  // 39: ... attribute_getter(prototype)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* prototype */;
  result_count = 1;
  myself = frame->slots[1] /* attribute_getter */;
  func = myself->type;
  frame->cont = cont__1_4;
}
static void cont__1_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__3 */ = arguments->slots[0];
  // 39: ... attribute != attribute_getter(prototype)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* attribute */;
  arguments->slots[1] = frame->slots[8] /* temp__3 */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__1_5;
}
static void cont__1_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 39: ... attribute != attribute_getter(prototype)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__1_6;
}
static void cont__1_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 39: ... :
  // 40:   $text attribute.serialize
  // 41:   write_to &buf "@nl;  " attribute_name ":"
  // 42:   if
  // 43:     text .contains. '@nl;':
  // 44:       write_to &buf '@nl;' indented(4 text)
  // 45:     :
  // 46:       write_to &buf ' ' text
  frame->slots[9] /* temp__4 */ = create_closure(entry__1_7, 0);
  // 39: if attribute != attribute_getter(prototype):
  // 40:   $text attribute.serialize
  // 41:   write_to &buf "@nl;  " attribute_name ":"
  // 42:   if
  // 43:     text .contains. '@nl;':
  // 44:       write_to &buf '@nl;' indented(4 text)
  // 45:     :
  // 46:       write_to &buf ' ' text
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[9] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__1_18(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 47: ... buf == tag
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* buf */;
  arguments->slots[1] = frame->slots[0] /* tag */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__1_19;
}
static void cont__1_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 47: ... : append &buf "()"
  frame->slots[6] /* temp__2 */ = create_closure(entry__1_20, 0);
  // 47: if buf == tag: append &buf "()"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__1_23;
}
static void entry__1_20(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // buf: 0
  frame->slots[0] = myself->closure.frame->slots[4]; /* buf */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 47: ... append &buf "()"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* buf */;
  arguments->slots[1] = string__2d7981f4e6482bec;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__1_22;
}
static void cont__1_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* buf */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__1_23(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 48: -> buf
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* buf */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
EXPORT void collect__basic__serialize(void) {
  var.std__serialize_object = collect_node(var.std__serialize_object);
}

static int already_run_phase_1 = false;

EXPORT void phase_1__basic__serialize(void) {
  if (already_run_phase_1) return;
  already_run_phase_1 = true;
  register_module_info(&module_info);
}

static int already_run_phase_2 = false;

EXPORT void phase_2__basic__serialize(void) {
  if (already_run_phase_2) return;
  already_run_phase_2 = true;
  character__10 = from_uchar32(10);
  number__4 = from_uint32(4U);
  character__32 = from_uchar32(32);
  string__fa73ac15f296bec = from_latin_1_string(
    "\n"
    "  ",
    3);
  string__578a5af303e9cdb = from_latin_1_string(":", 1);
  string__2d7981f4e6482bec = from_latin_1_string("()", 2);
  func__1_1_std__serialize_object = create_function(entry__1_1_std__serialize_object, -1);
}

static int already_run_phase_3 = false;

EXPORT void phase_3__basic__serialize(void) {
  if (already_run_phase_3) return;
  already_run_phase_3 = true;
  set_module("basic__serialize");
  set_used_namespaces(used_namespaces);
  define_single_assign_static("std", "serialize_object", get__std__serialize_object, &var.std__serialize_object);
}

static int already_run_phase_4 = false;

EXPORT void phase_4__basic__serialize(void) {
  if (already_run_phase_4) return;
  already_run_phase_4 = true;
  set_module("basic__serialize");
  set_used_namespaces(used_namespaces);
  use_read_only(NULL, "append", &get__append, &get_value_or_future__append);
  use_read_only(NULL, "contains", &get__contains, &get_value_or_future__contains);
  use_read_only(NULL, "for_each_pair", &get__for_each_pair, &get_value_or_future__for_each_pair);
  use_read_only(NULL, "if", &get__if, &get_value_or_future__if);
  use_read_only(NULL, "indented", &get__indented, &get_value_or_future__indented);
  use_read_only(NULL, "serialize", &get__serialize, &get_value_or_future__serialize);
  use_read_only("std", "equal", &get__std__equal, &get_value_or_future__std__equal);
  use_read_only("std", "not", &get__std__not, &get_value_or_future__std__not);
  use_read_only(NULL, "write_to", &get__write_to, &get_value_or_future__write_to);
}

static int already_run_phase_5 = false;

EXPORT void phase_5__basic__serialize(void) {
  if (already_run_phase_5) return;
  already_run_phase_5 = true;
  assign_variable(&var.std__serialize_object, &func__1_1_std__serialize_object);
}

static int already_run_phase_6 = false;

EXPORT void phase_6__basic__serialize(void) {
  if (already_run_phase_6) return;
  already_run_phase_6 = true;
  register_collector(collect__basic__serialize);
}
