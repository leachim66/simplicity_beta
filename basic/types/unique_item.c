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
IMPORT void no_such_function(void);
IMPORT OCTREE undefined_attributes_level_1;
IMPORT OCTREE undefined_attributes_level_2;
IMPORT OCTREE undefined_attributes_level_3;
IMPORT OCTREE undefined_attributes_level_4;
IMPORT OCTREE undefined_attributes_level_5;
IMPORT OCTREE undefined_attributes_level_6;
IMPORT OCTREE undefined_attributes_level_7;
IMPORT __attribute__ ((noreturn)) void runtime_error(const char *msg, ...);
IMPORT void *allocate_memory(size_t size);
IMPORT void *reallocate_memory(void * buf, size_t size);
IMPORT NODE *boolean_false;
IMPORT NODE *from_bool(int val);
IMPORT NODE *from_uint32(uint32_t val);
IMPORT int debug_print(int indent, char *buf, const char *format, ...);
IMPORT NODE *collect_node(NODE *node);
IMPORT void collect_static_attributes(ATTRIBUTES *attributes);
IMPORT void register_module_info(MODULE_INFO *info);
IMPORT void define_polymorphic_function(
  const char *namespace, const char *name, NODE_GETTER getter, int *id_p,
  NODE **var_p
);
IMPORT void define_c_function(const char *name, void *func);
IMPORT NODE *register_unique_item(const char *name);
IMPORT void set_module(const char *name);
IMPORT void set_used_namespaces(const char **namespaces);
IMPORT NODE *create_future_with_prototype(NODE *prototype);
IMPORT void define_single_assign_static(
  const char *namespace, const char *name,
  NODE_GETTER getter, NODE **var_p
);
IMPORT NODE *create_future(void);
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
static int poly_idx__equal;
static NODE_GETTER get__equal;
static NODE_GETTER get__false;
static NODE_GETTER get_value_or_future__false;
static int poly_idx__hash;
static NODE_GETTER get__hash;
static int poly_idx__is_a_unique_item;
static NODE_GETTER get__is_a_unique_item;
static NODE_GETTER get__true;
static NODE_GETTER get_value_or_future__true;
static NODE_GETTER get__types__object;
static NODE_GETTER get_value_or_future__types__object;
static struct {
  NODE *std__is_a_unique_item;
  NODE *types__unique_item;
} var;
static const char *var_names[] = {
};
static int poly_idx__std__is_a_unique_item;
static void type__std__is_a_unique_item(void);
static NODE *get__std__is_a_unique_item(void) {
  return var.std__is_a_unique_item;
}

static long unique_idx = 1;
static const char **my_unique_item_names;

typedef struct {
  void *type;
  ATTRIBUTES *attributes;
  long id;
} UNIQUE_ITEM;

static int is_a_power_of_two(int n);
static NODE *get__types__unique_item(void) {
  return var.types__unique_item;
}
static NODE *create__types__unique_item(long id);
static void entry__9_1(void);
static NODE *func__9_1;
static void entry__10_1(void);
static NODE *func__10_1;

static long func__types__unique_item___debug_string(NODE *node, int indent, int max_depth, char *buf);
void run__basic__types__unique_item(void);

static CONTINUATION_INFO continuation_info[] = {
  {type__std__is_a_unique_item, NULL, 23, 23, 2, 22},
  {run__basic__types__unique_item, NULL, },
  {entry__9_1, NULL, 77, 83, 3, 2},
  {entry__10_1, NULL, 86, 92, 3, 2}
};

union NODE {
  struct {
    FUNC type;
    ATTRIBUTES *attributes;
  };
  CONTINUATION continuation;
  CLOSURE closure;
  SIMPLE_NODE simple_node;
  UNIQUE_ITEM unique_item;
};
static void type__std__is_a_unique_item(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__is_a_unique_item);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__is_a_unique_item, attr);
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

static const char *used_namespaces[] = {
  "std",
  NULL
};

static MODULE_INFO module_info = {
  NULL,
  "basic__types__unique_item",
  continuation_info,
  sizeof(continuation_info)/sizeof(CONTINUATION_INFO),
  (NODE **)&var,
  var_names,
  sizeof(var_names)/sizeof(const char *),
  used_namespaces,
  {DEBUG_FILENAME("basic/types/unique_item.sim")}
};

/******
C O D E
******/

static int already_run = false;

EXPORT void run__basic__types__unique_item(void) {
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
static void *collect_unique_item(UNIQUE_ITEM *node) {
  UNIQUE_ITEM *new_node = allocate(sizeof(UNIQUE_ITEM));
  new_node->type = node->type;
  *(void **)node = ENCODE_ADDRESS(new_node);
  new_node->attributes = collect_attributes(node->attributes);
  new_node->id = node->id;
  return new_node;
}

static int is_a_power_of_two(int n) {
  return ((n != 0) && !(n & (n - 1)));
}

static VTABLE vtable__types__unique_item = {
  sizeof(UNIQUE_ITEM),
  (COLLECTOR *)&collect_unique_item,
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
  &func__types__unique_item___debug_string
};

static ATTRIBUTES attributes__types__unique_item = {
  &vtable__types__unique_item,
  {
    &undefined_attributes_level_1, &undefined_attributes_level_2,
    &undefined_attributes_level_3, &undefined_attributes_level_4,
    &undefined_attributes_level_5, &undefined_attributes_level_6,
    &undefined_attributes_level_7
  }
};

static void type__types__unique_item(void) {
  {
    runtime_error("Attempt to call a unique item as a function!");
  }
}
static NODE *create__types__unique_item(long id) {
  NODE *node = allocate(sizeof(UNIQUE_ITEM));
  node->type = type__types__unique_item;
  node->attributes = &attributes__types__unique_item;
  node->unique_item.id = id;
  return node;
}

NODE *runtime__register_unique_item(const char *name) {
  if (unique_idx == 0) {
    my_unique_item_names = allocate_memory(sizeof(const char *));
  } else if (is_a_power_of_two(unique_idx)) {
    my_unique_item_names =
      reallocate_memory(
        my_unique_item_names,
        2*unique_idx*sizeof(const char *));
  }
  my_unique_item_names[unique_idx] = name;
  return create__types__unique_item(unique_idx++);
}
static void entry__9_1(void) {
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  NODE *right = arguments->slots[1];
  if ((right)->type != type__types__unique_item) {
    arguments = node_p;
    arguments->slots[0] = boolean_false;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  {
    NODE *result__node = (NODE *)(from_bool(arguments->slots[0]->unique_item.id == right->unique_item.id));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__10_1(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  uint32_t hash = arguments->slots[0]->unique_item.id;
  hash *= 1893456841;
  hash ^= hash >> 25 | hash << 7;
  {
    NODE *result__node = (NODE *)(from_uint32(hash));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  };
}

static long func__types__unique_item___debug_string(NODE *node, int indent, int max_depth, char *buf) {
  return debug_print(
    indent, buf, my_unique_item_names[node->unique_item.id]);
}
EXPORT void collect__basic__types__unique_item(void) {
  var.std__is_a_unique_item = collect_node(var.std__is_a_unique_item);
  var.types__unique_item = collect_node(var.types__unique_item);
  collect_static_attributes(&attributes__types__unique_item);
}

static int already_run_phase_1 = false;

EXPORT void phase_1__basic__types__unique_item(void) {
  if (already_run_phase_1) return;
  already_run_phase_1 = true;
  register_module_info(&module_info);
  define_polymorphic_function("std", "is_a_unique_item", get__std__is_a_unique_item, &poly_idx__std__is_a_unique_item, &var.std__is_a_unique_item);
  define_c_function("register_unique_item", runtime__register_unique_item);
}

static int already_run_phase_2 = false;

EXPORT void phase_2__basic__types__unique_item(void) {
  if (already_run_phase_2) return;
  already_run_phase_2 = true;
}

static int already_run_phase_3 = false;

EXPORT void phase_3__basic__types__unique_item(void) {
  if (already_run_phase_3) return;
  already_run_phase_3 = true;
  set_module("basic__types__unique_item");
  set_used_namespaces(used_namespaces);
  var.types__unique_item = create_future_with_prototype(create__types__unique_item(0));
  define_single_assign_static("types", "unique_item", get__types__unique_item, &var.types__unique_item);
  func__9_1 = create_future();
  func__10_1 = create_future();
}

static int already_run_phase_4 = false;

EXPORT void phase_4__basic__types__unique_item(void) {
  if (already_run_phase_4) return;
  already_run_phase_4 = true;
  set_module("basic__types__unique_item");
  set_used_namespaces(used_namespaces);
  use_polymorphic_function(NULL, "equal", &get__equal, &poly_idx__equal);
  use_read_only(NULL, "false", &get__false, &get_value_or_future__false);
  use_polymorphic_function(NULL, "hash", &get__hash, &poly_idx__hash);
  use_polymorphic_function(NULL, "is_a_unique_item", &get__is_a_unique_item, &poly_idx__is_a_unique_item);
  use_read_only(NULL, "true", &get__true, &get_value_or_future__true);
  use_read_only("types", "object", &get__types__object, &get_value_or_future__types__object);
  define_attribute("types", "object", poly_idx__is_a_unique_item, get__false());
  define_attribute("types", "unique_item", poly_idx__is_a_unique_item, get__true());
  define_method("types", "unique_item", poly_idx__equal, func__9_1);
  define_method("types", "unique_item", poly_idx__hash, func__10_1);
}

static int already_run_phase_5 = false;

EXPORT void phase_5__basic__types__unique_item(void) {
  if (already_run_phase_5) return;
  already_run_phase_5 = true;
  assign_value(&var.std__is_a_unique_item, create_function(type__std__is_a_unique_item, -1));
  assign_value(&var.types__unique_item, get__types__object());
}

static int already_run_phase_6 = false;

EXPORT void phase_6__basic__types__unique_item(void) {
  if (already_run_phase_6) return;
  already_run_phase_6 = true;
  assign_value(&func__9_1, create_function(entry__9_1, 2));
  assign_value(&func__10_1, create_function(entry__10_1, 1));
  register_collector(collect__basic__types__unique_item);
}
