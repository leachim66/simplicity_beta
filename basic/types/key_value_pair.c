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
IMPORT void *allocate(long size);
IMPORT ATTRIBUTES *collect_attributes(ATTRIBUTES *attributes);
IMPORT NODE *collect_node(NODE *node);
IMPORT void no_such_function(void);
IMPORT OCTREE undefined_attributes_level_1;
IMPORT OCTREE undefined_attributes_level_2;
IMPORT OCTREE undefined_attributes_level_3;
IMPORT OCTREE undefined_attributes_level_4;
IMPORT OCTREE undefined_attributes_level_5;
IMPORT OCTREE undefined_attributes_level_6;
IMPORT OCTREE undefined_attributes_level_7;
IMPORT __attribute__ ((noreturn)) void runtime_error(const char *msg, ...);
IMPORT int debug_print_head(int *indent_p, char **buf_p, const char *format, ...);
IMPORT const char *indent_to_string(int indent);
IMPORT int print(char **buf_p, const char *format, ...);
IMPORT void too_few_arguments_error(void);
IMPORT void too_many_arguments_error(void);
IMPORT int result_count;
IMPORT void invalid_results_error(void);
IMPORT void collect_static_attributes(ATTRIBUTES *attributes);
IMPORT void register_module_info(MODULE_INFO *info);
IMPORT void define_polymorphic_function(
  const char *namespace, const char *name, NODE_GETTER getter, int *id_p,
  NODE **var_p
);
IMPORT void set_module(const char *name);
IMPORT void set_used_namespaces(const char **namespaces);
IMPORT NODE *create_future(void);
IMPORT NODE *create_future_with_prototype(NODE *prototype);
IMPORT void define_single_assign_static(
  const char *namespace, const char *name,
  NODE_GETTER getter, NODE **var_p
);
IMPORT NODE *from_latin_1_string(const char *str, long len);
IMPORT void use_read_only(
  const char *namespace, const char *name,
  NODE_GETTER *getter, NODE_GETTER *get_value_or_future
);
IMPORT void use_polymorphic_function(
  const char *namespace, const char *name, NODE_GETTER *getter, int *id
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
IMPORT NODE *from_uint32(uint32_t val);
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
static NODE_GETTER get__false;
static NODE_GETTER get_value_or_future__false;
static int poly_idx__is_a_key_value_pair;
static NODE_GETTER get__is_a_key_value_pair;
static int poly_idx__key_of;
static NODE_GETTER get__key_of;
static int poly_idx__serialize;
static NODE_GETTER get__serialize;
static NODE_GETTER get__spaces;
static NODE_GETTER get_value_or_future__spaces;
static NODE_GETTER get__std__plus;
static NODE_GETTER get_value_or_future__std__plus;
static NODE_GETTER get__std__string;
static NODE_GETTER get_value_or_future__std__string;
static NODE_GETTER get__true;
static NODE_GETTER get_value_or_future__true;
static NODE_GETTER get__types__object;
static NODE_GETTER get_value_or_future__types__object;
static int poly_idx__value_of;
static NODE_GETTER get__value_of;
static struct {
  NODE *std__is_a_key_value_pair;
  NODE *types__key_value_pair;
  NODE *std__key_value_pair;
} var;
static const char *var_names[] = {
};
static int poly_idx__std__is_a_key_value_pair;
static void type__std__is_a_key_value_pair(void);
static NODE *get__std__is_a_key_value_pair(void) {
  return var.std__is_a_key_value_pair;
}

typedef struct {
  void *type;
  ATTRIBUTES *attributes;
  NODE *key;
  NODE *value;
} KEY_VALUE_PAIR;
static NODE *get__types__key_value_pair(void) {
  return var.types__key_value_pair;
}
static NODE *create__types__key_value_pair(NODE *key, NODE *value);
static void entry__6_1(void);
static NODE *func__6_1;
static NODE *get__std__key_value_pair(void) {
  return var.std__key_value_pair;
}
static void entry__7_1(void);
static NODE *func__7_1;
static void entry__8_1(void);
static NODE *func__8_1;

static long func__types__key_value_pair___debug_string(NODE *node, int indent, int max_depth, char *buf);
static NODE *func__10_1;
static void entry__10_1(void);
static FRAME_INFO frame__10_1 = {2, {"self", "indent"}};
static void cont__10_2(void);
static void cont__10_3(void);
static void cont__10_4(void);
static void cont__10_5(void);
static void cont__10_6(void);
static void cont__10_7(void);
static void cont__10_8(void);
static void cont__10_9(void);
static void cont__10_10(void);
static void cont__10_11(void);
static NODE *string__10_12;
static NODE *string__10_13;
static void cont__10_14(void);
void run__basic__types__key_value_pair(void);

static CONTINUATION_INFO continuation_info[] = {
  {type__std__is_a_key_value_pair, NULL, 23, 23, 2, 25},
  {run__basic__types__key_value_pair, NULL, },
  {entry__6_1, NULL, 48, 51, 3, 2},
  {entry__7_1, NULL, 54, 57, 3, 2},
  {entry__8_1, NULL, 60, 63, 3, 2},
  {entry__10_1, NULL, 91, 91, 14, 21},
  {cont__10_2, &frame__10_1, 91, 91, 7, 22},
  {cont__10_3, &frame__10_1, 91, 91, 36, 47},
  {cont__10_4, &frame__10_1, 91, 91, 49, 56},
  {cont__10_5, &frame__10_1, 91, 91, 26, 57},
  {cont__10_6, &frame__10_1, 92, 92, 18, 25},
  {cont__10_7, &frame__10_1, 92, 92, 11, 26},
  {cont__10_8, &frame__10_1, 92, 92, 40, 53},
  {cont__10_9, &frame__10_1, 92, 92, 55, 62},
  {cont__10_10, &frame__10_1, 92, 92, 30, 63},
  {cont__10_11, &frame__10_1, 89, 92, 6, 65},
  {cont__10_14, &frame__10_1, 89, 92, 3, 65}
};

union NODE {
  struct {
    FUNC type;
    ATTRIBUTES *attributes;
  };
  CONTINUATION continuation;
  CLOSURE closure;
  SIMPLE_NODE simple_node;
  KEY_VALUE_PAIR key_value_pair;
};
static void type__std__is_a_key_value_pair(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__is_a_key_value_pair);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__is_a_key_value_pair, attr);
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
static NODE *number__4;
static NODE *number__2;

static const char *used_namespaces[] = {
  "std",
  NULL
};

static MODULE_INFO module_info = {
  NULL,
  "basic__types__key_value_pair",
  continuation_info,
  sizeof(continuation_info)/sizeof(CONTINUATION_INFO),
  (NODE **)&var,
  var_names,
  sizeof(var_names)/sizeof(const char *),
  used_namespaces,
  {DEBUG_FILENAME("basic/types/key_value_pair.sim")}
};

/******
C O D E
******/

static int already_run = false;

EXPORT void run__basic__types__key_value_pair(void) {
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
static void *collect_key_value_pair(KEY_VALUE_PAIR *node) {
  KEY_VALUE_PAIR *new_node = allocate(sizeof(KEY_VALUE_PAIR));
  new_node->type = node->type;
  *(void **)node = ENCODE_ADDRESS(new_node);
  new_node->attributes = collect_attributes(node->attributes);
  new_node->key = collect_node(node->key);
  new_node->value = collect_node(node->value);
  return new_node;
}

static VTABLE vtable__types__key_value_pair = {
  sizeof(KEY_VALUE_PAIR),
  (COLLECTOR *)&collect_key_value_pair,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  &func__types__key_value_pair___debug_string
};

static ATTRIBUTES attributes__types__key_value_pair = {
  &vtable__types__key_value_pair,
  {
    &undefined_attributes_level_1, &undefined_attributes_level_2,
    &undefined_attributes_level_3, &undefined_attributes_level_4,
    &undefined_attributes_level_5, &undefined_attributes_level_6,
    &undefined_attributes_level_7
  }
};

static void type__types__key_value_pair(void) {
  {
    runtime_error("Attempt to call an option value as a function!");
  }
}
static NODE *create__types__key_value_pair(NODE *key, NODE *value) {
  NODE *node = allocate(sizeof(KEY_VALUE_PAIR));
  node->type = type__types__key_value_pair;
  node->attributes = &attributes__types__key_value_pair;
  node->key_value_pair.key = key;
  node->key_value_pair.value = value;
  return node;
}
static void entry__6_1(void) {
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  {
    NODE *result__node = (NODE *)(create__types__key_value_pair(arguments->slots[0], arguments->slots[1]));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__7_1(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  {
    NODE *result__node = (NODE *)(arguments->slots[0]->key_value_pair.key);
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__8_1(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  {
    NODE *result__node = (NODE *)(arguments->slots[0]->key_value_pair.value);
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}

static long func__types__key_value_pair___debug_string(NODE *node, int indent, int max_depth, char *buf) {
  int i, n, len;
  n = debug_print_head(&indent, &buf, "key_value_pair");
  const char *contents_indent = indent_to_string(indent);
  n += print(&buf, contents_indent);
  len = debug_string(node->key_value_pair.key, indent, max_depth-1, buf);
  if (buf) buf += len;
  n += len;
  n += print(&buf, contents_indent);
  len = debug_string(node->key_value_pair.value, indent, max_depth-1, buf);
  if (buf) buf += len;
  n += len;
  return n;
}
static void entry__10_1(void) {
  allocate_initialized_frame_gc(2, 13);
  // slot allocations:
  // self: 0
  // indent: 1
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
  // 91: ... indent+2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* indent */;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__10_2;
}
static void cont__10_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 91: ... spaces(indent+2)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__spaces();
  func = myself->type;
  frame->cont = cont__10_3;
}
static void cont__10_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 91: ... key_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__key_of();
  func = myself->type;
  frame->cont = cont__10_4;
}
static void cont__10_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__5 */ = arguments->slots[0];
  // 91: ... indent+4
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* indent */;
  arguments->slots[1] = number__4;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__10_5;
}
static void cont__10_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__6 */ = arguments->slots[0];
  // 91: ... serialize(key_of(self) indent+4)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__5 */;
  arguments->slots[1] = frame->slots[7] /* temp__6 */;
  result_count = 1;
  myself = get__serialize();
  func = myself->type;
  frame->cont = cont__10_6;
}
static void cont__10_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__4 */ = arguments->slots[0];
  // 92: ... indent+2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* indent */;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__10_7;
}
static void cont__10_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__8 */ = arguments->slots[0];
  // 92: ... spaces(indent+2)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__8 */;
  result_count = 1;
  myself = get__spaces();
  func = myself->type;
  frame->cont = cont__10_8;
}
static void cont__10_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__7 */ = arguments->slots[0];
  // 92: ... value_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__value_of();
  func = myself->type;
  frame->cont = cont__10_9;
}
static void cont__10_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__10 */ = arguments->slots[0];
  // 92: ... indent+4
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* indent */;
  arguments->slots[1] = number__4;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__10_10;
}
static void cont__10_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__11 */ = arguments->slots[0];
  // 92: ... serialize(value_of(self) indent+4)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__10 */;
  arguments->slots[1] = frame->slots[12] /* temp__11 */;
  result_count = 1;
  myself = get__serialize();
  func = myself->type;
  frame->cont = cont__10_11;
}
static void cont__10_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__9 */ = arguments->slots[0];
  // 89: ... "
  // 90:   key_value_pair
  // 91:   @(spaces(indent+2))@(serialize(key_of(self) indent+4))@
  // 92:   @nl;@(spaces(indent+2))@(serialize(value_of(self) indent+4))@
  argument_count = 6;
  arguments = node_p;
  arguments->slots[0] = string__10_12;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  arguments->slots[2] = frame->slots[5] /* temp__4 */;
  arguments->slots[3] = string__10_13;
  arguments->slots[4] = frame->slots[8] /* temp__7 */;
  arguments->slots[5] = frame->slots[10] /* temp__9 */;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__10_14;
}
static void cont__10_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 89: -> "
  // 90:   key_value_pair
  // 91:   @(spaces(indent+2))@(serialize(key_of(self) indent+4))@
  // 92:   @nl;@(spaces(indent+2))@(serialize(value_of(self) indent+4))@
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
EXPORT void collect__basic__types__key_value_pair(void) {
  var.std__is_a_key_value_pair = collect_node(var.std__is_a_key_value_pair);
  var.types__key_value_pair = collect_node(var.types__key_value_pair);
  collect_static_attributes(&attributes__types__key_value_pair);
  var.std__key_value_pair = collect_node(var.std__key_value_pair);
  string__10_12 = collect_node(string__10_12);
  string__10_13 = collect_node(string__10_13);
  func__10_1 = collect_node(func__10_1);
  number__0 = collect_node(number__0);
  number__4 = collect_node(number__4);
  number__2 = collect_node(number__2);
}

static int already_run_phase_1 = false;

EXPORT void phase_1__basic__types__key_value_pair(void) {
  if (already_run_phase_1) return;
  already_run_phase_1 = true;
  register_module_info(&module_info);
  define_polymorphic_function("std", "is_a_key_value_pair", get__std__is_a_key_value_pair, &poly_idx__std__is_a_key_value_pair, &var.std__is_a_key_value_pair);
}

static int already_run_phase_2 = false;

EXPORT void phase_2__basic__types__key_value_pair(void) {
  if (already_run_phase_2) return;
  already_run_phase_2 = true;
  set_module("basic__types__key_value_pair");
  set_used_namespaces(used_namespaces);
  number__0 = create_future();
  number__4 = create_future();
  number__2 = create_future();
  var.types__key_value_pair = create_future_with_prototype(create__types__key_value_pair(NULL, NULL));
  define_single_assign_static("types", "key_value_pair", get__types__key_value_pair, &var.types__key_value_pair);
  func__6_1 = create_future();
  define_single_assign_static("std", "key_value_pair", get__std__key_value_pair, &var.std__key_value_pair);
  func__7_1 = create_future();
  func__8_1 = create_future();
  string__10_12 = from_latin_1_string("key_value_pair\012", 15);
  string__10_13 = from_latin_1_string("\012", 1);
  func__10_1 = create_future();
}

static int already_run_phase_3 = false;

EXPORT void phase_3__basic__types__key_value_pair(void) {
  if (already_run_phase_3) return;
  already_run_phase_3 = true;
  set_module("basic__types__key_value_pair");
  set_used_namespaces(used_namespaces);
  use_read_only(NULL, "false", &get__false, &get_value_or_future__false);
  use_polymorphic_function(NULL, "is_a_key_value_pair", &get__is_a_key_value_pair, &poly_idx__is_a_key_value_pair);
  use_polymorphic_function(NULL, "key_of", &get__key_of, &poly_idx__key_of);
  use_polymorphic_function(NULL, "serialize", &get__serialize, &poly_idx__serialize);
  use_read_only(NULL, "spaces", &get__spaces, &get_value_or_future__spaces);
  use_read_only("std", "plus", &get__std__plus, &get_value_or_future__std__plus);
  use_read_only("std", "string", &get__std__string, &get_value_or_future__std__string);
  use_read_only(NULL, "true", &get__true, &get_value_or_future__true);
  use_read_only("types", "object", &get__types__object, &get_value_or_future__types__object);
  use_polymorphic_function(NULL, "value_of", &get__value_of, &poly_idx__value_of);
  define_attribute("types", "object", poly_idx__is_a_key_value_pair, get__false());
  define_attribute("types", "key_value_pair", poly_idx__is_a_key_value_pair, get__true());
  define_method("types", "key_value_pair", poly_idx__key_of, func__7_1);
  define_method("types", "key_value_pair", poly_idx__value_of, func__8_1);
  define_method("types", "key_value_pair", poly_idx__serialize, func__10_1);
}

static int already_run_phase_4 = false;

EXPORT void phase_4__basic__types__key_value_pair(void) {
  if (already_run_phase_4) return;
  already_run_phase_4 = true;
  assign_value(&number__0, from_uint32(0U));
  assign_value(&number__4, from_uint32(4U));
  assign_value(&number__2, from_uint32(2U));
  assign_value(&var.std__is_a_key_value_pair, create_function(type__std__is_a_key_value_pair, -1));
  assign_value(&var.types__key_value_pair, get__types__object());
  assign_variable(&var.std__key_value_pair, &func__6_1);
}

static int already_run_phase_5 = false;

EXPORT void phase_5__basic__types__key_value_pair(void) {
  if (already_run_phase_5) return;
  already_run_phase_5 = true;
  assign_value(&func__6_1, create_function(entry__6_1, 2));
  assign_value(&func__7_1, create_function(entry__7_1, 1));
  assign_value(&func__8_1, create_function(entry__8_1, 1));
  assign_value(&func__10_1, create_function(entry__10_1, -1));
  register_collector(collect__basic__types__key_value_pair);
}
