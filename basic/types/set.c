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
REGISTER int argument_count ASM("ebx");
IMPORT void too_few_arguments_error(void);
REGISTER NODE *myself ASM("r13");
IMPORT NODE *get_attribute(NODE *node, int idx);
REGISTER FRAME *arguments ASM("r12");
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
IMPORT void initialize_maybe_future(NODE *var, NODE *val);
IMPORT NODE *create_cell_with_contents(NODE *contents);
IMPORT NODE *create_closure(FUNC type, int par_count);
IMPORT int result_count;
typedef struct CELL {
  FUNC type;
  struct ATTRIBUTES *attributes;
  NODE *contents;
} CELL;
IMPORT void invalid_results_error(void);
IMPORT NODE *create_continuation(void);
IMPORT NODE *create_future(void);
IMPORT NODE *create_cell(void);
IMPORT void too_many_arguments_error(void);
IMPORT void initialize_future(NODE *var, NODE *val);
IMPORT void allocate_arguments(void);
IMPORT NODE *from_arguments(int first_idx, int count);
IMPORT NODE *collect_node(NODE *node);
IMPORT void register_module_info(MODULE_INFO *info);
IMPORT void set_module(const char *name);
IMPORT NODE *from_uchar32(unsigned int chr);
IMPORT NODE *from_uint32(uint32_t val);
IMPORT NODE *create_function(FUNC func, int par_count);
IMPORT NODE *from_latin_1_string(const char *str, long len);
IMPORT void define_polymorphic_function(
  const char *namespace, const char *name, NODE_GETTER getter, int *id_p,
  NODE **var_p
);
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
IMPORT void define_method(
  const char *namespace, const char *name,
  int id, NODE *method
);
IMPORT void define_attribute(
  const char *namespace, const char *name,
  int id, NODE *attribute
);
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
static NODE_GETTER get__empty_list;
static NODE_GETTER get_value_or_future__empty_list;
static NODE_GETTER get__false;
static NODE_GETTER get_value_or_future__false;
static NODE_GETTER get__for_each;
static NODE_GETTER get_value_or_future__for_each;
static NODE_GETTER get__if;
static NODE_GETTER get_value_or_future__if;
static int poly_idx__is_a_set;
static NODE_GETTER get__is_a_set;
static int poly_idx__is_empty;
static NODE_GETTER get__is_empty;
static NODE_GETTER get__length_of;
static NODE_GETTER get_value_or_future__length_of;
static NODE_GETTER get__push;
static NODE_GETTER get_value_or_future__push;
static int poly_idx__serialization_tag_of;
static NODE_GETTER get__serialization_tag_of;
static int poly_idx__serialize;
static NODE_GETTER get__serialize;
static NODE_GETTER get__spaces;
static NODE_GETTER get_value_or_future__spaces;
static NODE_GETTER get__std__equal;
static NODE_GETTER get_value_or_future__std__equal;
static NODE_GETTER get__std__plus;
static NODE_GETTER get_value_or_future__std__plus;
static NODE_GETTER get__std__string;
static NODE_GETTER get_value_or_future__std__string;
static int poly_idx__to_list;
static NODE_GETTER get__to_list;
static NODE_GETTER get__true;
static NODE_GETTER get_value_or_future__true;
static NODE_GETTER get__types__object;
static NODE_GETTER get_value_or_future__types__object;
static NODE_GETTER get__types__unordered_set;
static NODE_GETTER get_value_or_future__types__unordered_set;
static int poly_idx__union;
static NODE_GETTER get__union;
static NODE_GETTER get__write_to;
static NODE_GETTER get_value_or_future__write_to;
static struct {
  NODE *types__generic_set;
  NODE *std__is_a_set;
  NODE *types__set;
  NODE *std__empty_set;
  NODE *std__set;
} var;
static const char *var_names[] = {
};
static NODE *get__types__generic_set(void) {
  return var.types__generic_set;
}
static NODE *func__types__generic_set___union;
static void entry__types__generic_set___union(void);
static FRAME_INFO frame__types__generic_set___union = {2, {"left", "right"}};
static NODE *func__types__generic_set__union_2;
static void entry__types__generic_set__union_2(void);
static FRAME_INFO frame__types__generic_set__union_2 = {2, {"key", "left"}};
static void cont__types__generic_set__union_3(void);
static void cont__types__generic_set___union_4(void);
static NODE *func__types__generic_set___serialize;
static void entry__types__generic_set___serialize(void);
static FRAME_INFO frame__types__generic_set___serialize = {5, {"self", "indent", "return", "tag", "buf"}};
static void cont__types__generic_set___serialize_2(void);
static void cont__types__generic_set___serialize_3(void);
static NODE *func__types__generic_set__serialize_4;
static void entry__types__generic_set__serialize_4(void);
static FRAME_INFO frame__types__generic_set__serialize_4 = {2, {"return", "tag"}};
static NODE *string__2d7981f4e6482bec;
static void cont__types__generic_set__serialize_6(void);
static void cont__types__generic_set___serialize_7(void);
static NODE *func__types__generic_set__serialize_8;
static void entry__types__generic_set__serialize_8(void);
static FRAME_INFO frame__types__generic_set__serialize_8 = {3, {"key", "buf", "indent"}};
static void cont__types__generic_set__serialize_9(void);
static void cont__types__generic_set__serialize_10(void);
static void cont__types__generic_set__serialize_11(void);
static void cont__types__generic_set__serialize_12(void);
static void cont__types__generic_set__serialize_13(void);
static void cont__types__generic_set___serialize_14(void);
static NODE *func__types__generic_set___is_empty;
static void entry__types__generic_set___is_empty(void);
static FRAME_INFO frame__types__generic_set___is_empty = {1, {"self"}};
static void cont__types__generic_set___is_empty_2(void);
static void cont__types__generic_set___is_empty_3(void);
static NODE *func__types__generic_set___to_list;
static void entry__types__generic_set___to_list(void);
static FRAME_INFO frame__types__generic_set___to_list = {2, {"self", "items"}};
static NODE *func__types__generic_set__to_list_2;
static void entry__types__generic_set__to_list_2(void);
static FRAME_INFO frame__types__generic_set__to_list_2 = {2, {"item", "items"}};
static void cont__types__generic_set__to_list_3(void);
static void cont__types__generic_set___to_list_4(void);
static int poly_idx__std__is_a_set;
static void type__std__is_a_set(void);
static NODE *get__std__is_a_set(void) {
  return var.std__is_a_set;
}
static NODE *get__types__set(void) {
  return var.types__set;
}
static NODE *string__fa724815d016bb8;
static NODE *get__std__empty_set(void) {
  return var.std__empty_set;
}
static NODE *func__std__set;
static void entry__std__set(void);
static FRAME_INFO frame__std__set = {2, {"args", "tab"}};
static NODE *func__std__set_2;
static void entry__std__set_2(void);
static FRAME_INFO frame__std__set_2 = {2, {"key", "tab"}};
static void cont__std__set_3(void);
static void cont__std__set_4(void);
static NODE *get__std__set(void) {
  return var.std__set;
}
void run__basic__types__set(void);

static CONTINUATION_INFO continuation_info[] = {
  {type__std__is_a_set, NULL, 69, 69, 2, 14},
  {run__basic__types__set, NULL, 76, 78, 1, 48},
  {entry__types__generic_set__union_2, NULL, 34, 34, 25, 34},
  {cont__types__generic_set__union_3, &frame__types__generic_set__union_2, 34, 34, 39, 39},
  {entry__types__generic_set___union, NULL, 34, 34, 3, 39},
  {cont__types__generic_set___union_4, &frame__types__generic_set___union, },
  {entry__types__generic_set__serialize_4, NULL, 45, 45, 28, 37},
  {cont__types__generic_set__serialize_6, &frame__types__generic_set__serialize_4, 45, 45, 21, 37},
  {entry__types__generic_set__serialize_8, NULL, 48, 48, 33, 40},
  {cont__types__generic_set__serialize_9, &frame__types__generic_set__serialize_8, 48, 48, 26, 41},
  {cont__types__generic_set__serialize_10, &frame__types__generic_set__serialize_8, 48, 48, 57, 64},
  {cont__types__generic_set__serialize_11, &frame__types__generic_set__serialize_8, 48, 48, 43, 65},
  {cont__types__generic_set__serialize_12, &frame__types__generic_set__serialize_8, 48, 48, 5, 65},
  {cont__types__generic_set__serialize_13, &frame__types__generic_set__serialize_8, 48, 48, 65, 65},
  {entry__types__generic_set___serialize, NULL, 44, 44, 3, 33},
  {cont__types__generic_set___serialize_2, &frame__types__generic_set___serialize, 45, 45, 6, 18},
  {cont__types__generic_set___serialize_3, &frame__types__generic_set___serialize, 45, 45, 3, 37},
  {cont__types__generic_set___serialize_7, &frame__types__generic_set___serialize, 47, 48, 3, 65},
  {cont__types__generic_set___serialize_14, &frame__types__generic_set___serialize, 49, 49, 3, 8},
  {entry__types__generic_set___is_empty, NULL, 57, 57, 6, 20},
  {cont__types__generic_set___is_empty_2, &frame__types__generic_set___is_empty, 57, 57, 6, 25},
  {cont__types__generic_set___is_empty_3, &frame__types__generic_set___is_empty, 57, 57, 3, 25},
  {entry__types__generic_set__to_list_2, NULL, 66, 66, 25, 40},
  {cont__types__generic_set__to_list_3, &frame__types__generic_set__to_list_2, 66, 66, 40, 40},
  {entry__types__generic_set___to_list, NULL, 66, 66, 3, 40},
  {cont__types__generic_set___to_list_4, &frame__types__generic_set___to_list, 67, 67, 3, 10},
  {entry__std__set_2, NULL, 97, 97, 24, 32},
  {cont__std__set_3, &frame__std__set_2, 97, 97, 37, 37},
  {entry__std__set, NULL, 97, 97, 3, 37},
  {cont__std__set_4, &frame__std__set, 98, 98, 3, 8}
};

union NODE {
  struct {
    FUNC type;
    ATTRIBUTES *attributes;
  };
  CONTINUATION continuation;
  CLOSURE closure;
};
static void type__std__is_a_set(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__std__is_a_set);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__is_a_set, attr);
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
static NODE *character__10;
static NODE *number__0;
static NODE *number__2;

static const char *used_namespaces[] = {
  "std",
  NULL
};

static MODULE_INFO module_info = {
  NULL,
  "basic__types__set",
  continuation_info,
  sizeof(continuation_info)/sizeof(CONTINUATION_INFO),
  (NODE **)&var,
  var_names,
  sizeof(var_names)/sizeof(const char *),
  used_namespaces,
  {DEBUG_FILENAME("basic/types/set.sim")}
};

/******
C O D E
******/

static int already_run = false;

EXPORT void run__basic__types__set(void) {
  if (already_run) {
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  already_run = true;
  allocate_initialized_frame_gc(0, 0);
  // 23: $types::generic_set types::object
  // 24:   #
  // 25:     the prototype object for all kinds of sets
  initialize_maybe_future(var.types__generic_set, get__types__object());
  // 76: $types::set types::unordered_set
  // 77:   #
  // 78:     the prototype object for all unordered sets
  initialize_maybe_future(var.types__set, get__types__unordered_set());
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__generic_set___union(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // left: 0
  // right: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* left */ = create_cell_with_contents(arguments->slots[0]);
  // 34: ... : (key) !left(key) true
  frame->slots[2] /* temp__1 */ = create_closure(entry__types__generic_set__union_2, 1);
  // 34: for_each right: (key) !left(key) true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* right */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count =
    frame->caller_result_count >= 1 ?
    frame->caller_result_count-1 : -1;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__types__generic_set___union_4;
}
static void entry__types__generic_set__union_2(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // key: 0
  // left: 1
  frame->slots[1] = myself->closure.frame->slots[0]; /* left */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 34: ... !left(key)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* key */;
  arguments->slots[1] = get__true();
  result_count = 1;
  myself = ((CELL *)frame->slots[1])->contents /* left */;
  func = myself->type;
  frame->cont = cont__types__generic_set__union_3;
}
static void cont__types__generic_set__union_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* left */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__types__generic_set___union_4(void) {
  int i = argument_count;
  while (--i >= 0) {
    arguments->slots[i+1] = arguments->slots[i];
  }
  argument_count += 1;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* left */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__generic_set___serialize(void) {
  allocate_initialized_frame_gc(3, 7);
  // slot allocations:
  // self: 0
  // indent: 1
  // return: 2
  // tag: 3
  // buf: 4
  frame->slots[2] /* return */ = create_continuation();
  frame->slots[3] /* tag */ = create_future();
  frame->slots[4] /* buf */ = create_cell();
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  if (argument_count > 2) {
    too_many_arguments_error();
    return;
  }
  switch(argument_count) {
    default: frame->slots[1] /* indent */ = arguments->slots[1];
    case 1:;
  }
  switch(argument_count) {
    case 1: frame->slots[1] /* indent */ = number__0;
  }
  // 44: $tag serialization_tag_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__serialization_tag_of();
  func = myself->type;
  frame->cont = cont__types__generic_set___serialize_2;
}
static void cont__types__generic_set___serialize_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* tag */, arguments->slots[0]);
  // 45: ... self.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__types__generic_set___serialize_3;
}
static void cont__types__generic_set___serialize_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 45: ... : return "@(tag)()"
  frame->slots[6] /* temp__2 */ = create_closure(entry__types__generic_set__serialize_4, 0);
  // 45: if self.is_empty: return "@(tag)()"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__generic_set___serialize_7;
}
static void entry__types__generic_set__serialize_4(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // return: 0
  // tag: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  frame->slots[1] = myself->closure.frame->slots[3]; /* tag */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 45: ... "@(tag)()"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* tag */;
  arguments->slots[1] = string__2d7981f4e6482bec;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__types__generic_set__serialize_6;
}
static void cont__types__generic_set__serialize_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 45: ... return "@(tag)()"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__generic_set___serialize_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 46: $$buf tag
  ((CELL *)frame->slots[4])->contents /* buf */ = frame->slots[3] /* tag */;
  // 47: ... : (key)
  // 48:   write_to &buf '@nl;' spaces(indent+2) serialize(key indent+2)
  frame->slots[5] /* temp__1 */ = create_closure(entry__types__generic_set__serialize_8, 1);
  // 47: for_each self: (key)
  // 48:   write_to &buf '@nl;' spaces(indent+2) serialize(key indent+2)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__types__generic_set___serialize_14;
}
static void entry__types__generic_set__serialize_8(void) {
  allocate_initialized_frame_gc(3, 7);
  // slot allocations:
  // key: 0
  // buf: 1
  // indent: 2
  frame->slots[1] = myself->closure.frame->slots[4]; /* buf */
  frame->slots[2] = myself->closure.frame->slots[1]; /* indent */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 48: ... indent+2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* indent */;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__types__generic_set__serialize_9;
}
static void cont__types__generic_set__serialize_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 48: ... spaces(indent+2)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__spaces();
  func = myself->type;
  frame->cont = cont__types__generic_set__serialize_10;
}
static void cont__types__generic_set__serialize_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 48: ... indent+2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* indent */;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__types__generic_set__serialize_11;
}
static void cont__types__generic_set__serialize_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__4 */ = arguments->slots[0];
  // 48: ... serialize(key indent+2)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* key */;
  arguments->slots[1] = frame->slots[6] /* temp__4 */;
  result_count = 1;
  myself = get__serialize();
  func = myself->type;
  frame->cont = cont__types__generic_set__serialize_12;
}
static void cont__types__generic_set__serialize_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 48: write_to &buf '@nl;' spaces(indent+2) serialize(key indent+2)
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* buf */;
  arguments->slots[1] = character__10;
  arguments->slots[2] = frame->slots[3] /* temp__1 */;
  arguments->slots[3] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__write_to();
  func = myself->type;
  frame->cont = cont__types__generic_set__serialize_13;
}
static void cont__types__generic_set__serialize_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* buf */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__types__generic_set___serialize_14(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 49: -> buf
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* buf */;
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__types__generic_set___is_empty(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // self: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 57: ... length_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__types__generic_set___is_empty_2;
}
static void cont__types__generic_set___is_empty_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 57: ... length_of(self) == 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__types__generic_set___is_empty_3;
}
static void cont__types__generic_set___is_empty_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 57: -> length_of(self) == 0
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__generic_set___to_list(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // self: 0
  // items: 1
  frame->slots[1] /* items */ = create_cell();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 65: $$items empty_list
  ((CELL *)frame->slots[1])->contents /* items */ = get__empty_list();
  // 66: ... : (item) push &items item
  frame->slots[2] /* temp__1 */ = create_closure(entry__types__generic_set__to_list_2, 1);
  // 66: for_each self: (item) push &items item
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__types__generic_set___to_list_4;
}
static void entry__types__generic_set__to_list_2(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // item: 0
  // items: 1
  frame->slots[1] = myself->closure.frame->slots[1]; /* items */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 66: ... push &items item
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* items */;
  arguments->slots[1] = frame->slots[0] /* item */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__types__generic_set__to_list_3;
}
static void cont__types__generic_set__to_list_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* items */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__types__generic_set___to_list_4(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 67: -> items
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* items */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__set(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // args: 0
  // tab: 1
  frame->slots[1] /* tab */ = create_cell();
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 96: $$tab types::set
  ((CELL *)frame->slots[1])->contents /* tab */ = var.types__set;
  // 97: ... : (key) !tab(key) true
  frame->slots[2] /* temp__1 */ = create_closure(entry__std__set_2, 1);
  // 97: for_each args: (key) !tab(key) true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* args */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__std__set_4;
}
static void entry__std__set_2(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // key: 0
  // tab: 1
  frame->slots[1] = myself->closure.frame->slots[1]; /* tab */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 97: ... !tab(key)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* key */;
  arguments->slots[1] = get__true();
  result_count = 1;
  myself = ((CELL *)frame->slots[1])->contents /* tab */;
  func = myself->type;
  frame->cont = cont__std__set_3;
}
static void cont__std__set_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* tab */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__std__set_4(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 98: -> tab
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* tab */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
EXPORT void collect__basic__types__set(void) {
  var.types__generic_set = collect_node(var.types__generic_set);
  var.std__is_a_set = collect_node(var.std__is_a_set);
  var.types__set = collect_node(var.types__set);
  var.std__empty_set = collect_node(var.std__empty_set);
  var.std__set = collect_node(var.std__set);
}

static int already_run_phase_1 = false;

EXPORT void phase_1__basic__types__set(void) {
  if (already_run_phase_1) return;
  already_run_phase_1 = true;
  register_module_info(&module_info);
}

static int already_run_phase_2 = false;

EXPORT void phase_2__basic__types__set(void) {
  if (already_run_phase_2) return;
  already_run_phase_2 = true;
  set_module("basic__types__set");
  character__10 = from_uchar32(10);
  number__0 = from_uint32(0U);
  number__2 = from_uint32(2U);
  func__types__generic_set___union = create_function(entry__types__generic_set___union, 2);
  string__2d7981f4e6482bec = from_latin_1_string("()", 2);
  func__types__generic_set___serialize = create_function(entry__types__generic_set___serialize, -1);
  func__types__generic_set___is_empty = create_function(entry__types__generic_set___is_empty, 1);
  func__types__generic_set___to_list = create_function(entry__types__generic_set___to_list, 1);
  define_polymorphic_function("std", "is_a_set", get__std__is_a_set, &poly_idx__std__is_a_set, &var.std__is_a_set);
  string__fa724815d016bb8 = from_latin_1_string("set", 3);
  func__std__set = create_function(entry__std__set, -1);
}

static int already_run_phase_3 = false;

EXPORT void phase_3__basic__types__set(void) {
  if (already_run_phase_3) return;
  already_run_phase_3 = true;
  set_module("basic__types__set");
  set_used_namespaces(used_namespaces);
  var.types__generic_set = create_future();
  define_single_assign_static("types", "generic_set", get__types__generic_set, &var.types__generic_set);
  var.types__set = create_future();
  define_single_assign_static("types", "set", get__types__set, &var.types__set);
  var.std__empty_set = create_future();
  define_single_assign_static("std", "empty_set", get__std__empty_set, &var.std__empty_set);
  var.std__set = create_future();
  define_single_assign_static("std", "set", get__std__set, &var.std__set);
}

static int already_run_phase_4 = false;

EXPORT void phase_4__basic__types__set(void) {
  if (already_run_phase_4) return;
  already_run_phase_4 = true;
  set_module("basic__types__set");
  set_used_namespaces(used_namespaces);
  use_read_only(NULL, "empty_list", &get__empty_list, &get_value_or_future__empty_list);
  use_read_only(NULL, "false", &get__false, &get_value_or_future__false);
  use_read_only(NULL, "for_each", &get__for_each, &get_value_or_future__for_each);
  use_read_only(NULL, "if", &get__if, &get_value_or_future__if);
  use_polymorphic_function(NULL, "is_a_set", &get__is_a_set, &poly_idx__is_a_set);
  use_polymorphic_function(NULL, "is_empty", &get__is_empty, &poly_idx__is_empty);
  use_read_only(NULL, "length_of", &get__length_of, &get_value_or_future__length_of);
  use_read_only(NULL, "push", &get__push, &get_value_or_future__push);
  use_polymorphic_function(NULL, "serialization_tag_of", &get__serialization_tag_of, &poly_idx__serialization_tag_of);
  use_polymorphic_function(NULL, "serialize", &get__serialize, &poly_idx__serialize);
  use_read_only(NULL, "spaces", &get__spaces, &get_value_or_future__spaces);
  use_read_only("std", "equal", &get__std__equal, &get_value_or_future__std__equal);
  use_read_only("std", "plus", &get__std__plus, &get_value_or_future__std__plus);
  use_read_only("std", "string", &get__std__string, &get_value_or_future__std__string);
  use_polymorphic_function(NULL, "to_list", &get__to_list, &poly_idx__to_list);
  use_read_only(NULL, "true", &get__true, &get_value_or_future__true);
  use_read_only("types", "object", &get__types__object, &get_value_or_future__types__object);
  use_read_only("types", "unordered_set", &get__types__unordered_set, &get_value_or_future__types__unordered_set);
  use_polymorphic_function(NULL, "union", &get__union, &poly_idx__union);
  use_read_only(NULL, "write_to", &get__write_to, &get_value_or_future__write_to);
  define_method("types", "generic_set", poly_idx__union, func__types__generic_set___union);
  define_method("types", "generic_set", poly_idx__serialize, func__types__generic_set___serialize);
  define_method("types", "generic_set", poly_idx__is_empty, func__types__generic_set___is_empty);
  define_method("types", "generic_set", poly_idx__to_list, func__types__generic_set___to_list);
  define_attribute("types", "object", poly_idx__is_a_set, get__false());
  define_attribute("types", "generic_set", poly_idx__is_a_set, get__true());
  define_attribute("types", "set", poly_idx__serialization_tag_of, string__fa724815d016bb8);
}

static int already_run_phase_5 = false;

EXPORT void phase_5__basic__types__set(void) {
  if (already_run_phase_5) return;
  already_run_phase_5 = true;
  initialize_future(var.types__generic_set, get__types__object());
  assign_value(&var.std__is_a_set, create_function(type__std__is_a_set, -1));
  initialize_future(var.types__set, get__types__unordered_set());
  initialize_future(var.std__empty_set, var.types__set);
  initialize_future(var.std__set, func__std__set);
}

static int already_run_phase_6 = false;

EXPORT void phase_6__basic__types__set(void) {
  if (already_run_phase_6) return;
  already_run_phase_6 = true;
  register_collector(collect__basic__types__set);
}
