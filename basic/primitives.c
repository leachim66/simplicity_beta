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
#if defined(__GNUC__) && !defined(__clang__) && defined(__x86_64)
  #define REGISTER register
#else
  #define REGISTER IMPORT
#endif
typedef struct FRAME {
  FUNC cont;
  struct FRAME *caller_frame;
  long caller_result_count;
  long slot_count;
  NODE *slots[0];
} FRAME;
#if defined(__GNUC__) && !defined(__clang__) && defined(__x86_64)
  #define ASM(x) asm(x)
#else
  #define ASM(x)
#endif
REGISTER FRAME *arguments ASM("r12");
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
REGISTER NODE *myself ASM("r13");
IMPORT NODE *get_attribute(NODE *node, int idx);
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
IMPORT int result_count;
IMPORT void invalid_results_error(void);
IMPORT void allocate_arguments(void);
IMPORT void too_few_arguments_error(void);
IMPORT NODE *from_arguments(int first_idx, int count);
IMPORT NODE *collect_node(NODE *node);
IMPORT void register_module_info(MODULE_INFO *info);
IMPORT void define_polymorphic_function(
  const char *namespace, const char *name, NODE_GETTER getter, int *id_p,
  NODE **var_p
);
IMPORT NODE *from_uchar32(unsigned int chr);
IMPORT NODE *create_function(FUNC func, int par_count);
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
IMPORT void define_method(
  const char *namespace, const char *name,
  int id, NODE *method
);
IMPORT void assign_value(NODE **dest, NODE *val);
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
static int poly_idx__has_minimum_length;
static NODE_GETTER get__has_minimum_length;
static NODE_GETTER get__length_of;
static NODE_GETTER get_value_or_future__length_of;
static NODE_GETTER get__pass;
static NODE_GETTER get_value_or_future__pass;
static NODE_GETTER get__std__less;
static NODE_GETTER get_value_or_future__std__less;
static NODE_GETTER get__std__not;
static NODE_GETTER get_value_or_future__std__not;
static NODE_GETTER get__types__object;
static NODE_GETTER get_value_or_future__types__object;
static NODE_GETTER get__write_to;
static NODE_GETTER get_value_or_future__write_to;
static struct {
  NODE *std__has_minimum_length;
  NODE *std__ignore;
  NODE *std__writeln_to;
  NODE *std__swap;
  NODE *std__pass;
  NODE *std__eval;
  NODE *std__do;
  NODE *std__assign;
  NODE *std__goto;
} var;
static const char *var_names[] = {
};
static int poly_idx__std__has_minimum_length;
static void type__std__has_minimum_length(void);
static NODE *get__std__has_minimum_length(void) {
  return var.std__has_minimum_length;
}
static NODE *func__2_1;
static void entry__2_1(void);
static FRAME_INFO frame__2_1 = {2, {"self", "len"}};
static void cont__2_2(void);
static void cont__2_3(void);
static void cont__2_4(void);
static NODE *func__3_1;
static void entry__3_1(void);
static FRAME_INFO frame__3_1 = {1, {"dummy"}};
static NODE *get__std__ignore(void) {
  return var.std__ignore;
}
static NODE *func__4_1;
static void entry__4_1(void);
static FRAME_INFO frame__4_1 = {2, {"file_handle", "arguments"}};
static NODE *get__std__writeln_to(void) {
  return var.std__writeln_to;
}
static NODE *func__5_1;
static void entry__5_1(void);
static FRAME_INFO frame__5_1 = {2, {"left", "right"}};
static NODE *get__std__swap(void) {
  return var.std__swap;
}
static void entry__6_1(void);
static NODE *func__6_1;
static NODE *get__std__pass(void) {
  return var.std__pass;
}
static NODE *func__7_1;
static void entry__7_1(void);
static FRAME_INFO frame__7_1 = {1, {"body"}};
static NODE *get__std__eval(void) {
  return var.std__eval;
}
static void entry__8_1(void);
static NODE *func__8_1;
static NODE *get__std__do(void) {
  return var.std__do;
}
static void entry__9_1(void);
static NODE *func__9_1;
static NODE *get__std__assign(void) {
  return var.std__assign;
}
static void entry__10_1(void);
static NODE *func__10_1;
static NODE *get__std__goto(void) {
  return var.std__goto;
}
void run__basic__primitives(void);

static CONTINUATION_INFO continuation_info[] = {
  {type__std__has_minimum_length, NULL, 23, 23, 2, 24},
  {run__basic__primitives, NULL, },
  {entry__2_1, NULL, 46, 46, 8, 22},
  {cont__2_2, &frame__2_1, 46, 46, 8, 29},
  {cont__2_3, &frame__2_1, 46, 46, 8, 29},
  {cont__2_4, &frame__2_1, 46, 46, 5, 29},
  {entry__3_1, NULL, 52, 52, 3, 6},
  {entry__4_1, NULL, 67, 67, 3, 40},
  {entry__5_1, NULL, 82, 82, 3, 15},
  {entry__6_1, NULL, 99, 102, 3, 2},
  {entry__7_1, NULL, 105, 119, 3, 47},
  {entry__8_1, NULL, 140, 145, 3, 2},
  {entry__9_1, NULL, 182, 184, 3, 2},
  {entry__10_1, NULL, 197, 212, 3, 2}
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
static void type__std__has_minimum_length(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__has_minimum_length);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__has_minimum_length, attr);
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

static const char *used_namespaces[] = {
  "std",
  NULL
};

static MODULE_INFO module_info = {
  NULL,
  "basic__primitives",
  continuation_info,
  sizeof(continuation_info)/sizeof(CONTINUATION_INFO),
  (NODE **)&var,
  var_names,
  sizeof(var_names)/sizeof(const char *),
  used_namespaces,
  {DEBUG_FILENAME("basic/primitives.sim")}
};

/******
C O D E
******/

static int already_run = false;

EXPORT void run__basic__primitives(void) {
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
static void entry__2_1(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // self: 0
  // len: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 46: ... length_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
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
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 46: ... length_of(self) >= len
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  arguments->slots[1] = frame->slots[1] /* len */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__2_3;
}
static void cont__2_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 46: ... length_of(self) >= len
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__2_4;
}
static void cont__2_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 46: -> length_of(self) >= len
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__3_1(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // dummy: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 52: pass
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = get__pass();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__4_1(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // file_handle: 0
  // arguments: 1
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  frame->slots[0] /* file_handle */ = arguments->slots[0];
  frame->slots[1] /* arguments */ = from_arguments(1, argument_count-1);
  // 67: write_to file_handle arguments* '@nl;'
  argument_count = 0;
  arguments = node_p;
  arguments->slots[argument_count++] = frame->slots[0] /* file_handle */;
  unfold(frame->slots[1] /* arguments */);
  arguments->slots[argument_count++] = character__10;
  result_count = frame->caller_result_count;
  myself = get__write_to();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__5_1(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // left: 0
  // right: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 82: -> right left
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* right */;
  arguments->slots[1] = frame->slots[0] /* left */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__6_1(void) {
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  {
    argument_count = 0;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__7_1(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // body: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 105: body
  // 106:   #
  // 107:     evaluate a function
  // 108:     
  // 109:     Allows the direct evaluation of a lambda-function.
  // 110:     
  // 111:     example:
  // 112:     
  // 113:     # example taken from the compiler's pretty_printer-module
  // 114:     
  // ...
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__8_1(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  myself = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  {
    func = myself->type;
    return;
  }
}
static void entry__9_1(void) {
  {
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__10_1(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = arguments->slots[0];
  FRAME *args = arguments;
  if (argument_count > 0) {
    argument_count = argument_count-1;
  arguments = node_p;
    int i;
    for (i = 0; i < argument_count; ++i) {
      arguments->slots[i] = args->slots[i+1];
    }
  } else {
    argument_count = 0;
  }
  frame->cont = invalid_continuation;
  {
    func = myself->type;
    return;
  }
}
EXPORT void collect__basic__primitives(void) {
  var.std__has_minimum_length = collect_node(var.std__has_minimum_length);
  var.std__ignore = collect_node(var.std__ignore);
  var.std__writeln_to = collect_node(var.std__writeln_to);
  var.std__swap = collect_node(var.std__swap);
  var.std__pass = collect_node(var.std__pass);
  var.std__eval = collect_node(var.std__eval);
  var.std__do = collect_node(var.std__do);
  var.std__assign = collect_node(var.std__assign);
  var.std__goto = collect_node(var.std__goto);
}

static int already_run_phase_1 = false;

EXPORT void phase_1__basic__primitives(void) {
  if (already_run_phase_1) return;
  already_run_phase_1 = true;
  register_module_info(&module_info);
  define_polymorphic_function("std", "has_minimum_length", get__std__has_minimum_length, &poly_idx__std__has_minimum_length, &var.std__has_minimum_length);
}

static int already_run_phase_2 = false;

EXPORT void phase_2__basic__primitives(void) {
  if (already_run_phase_2) return;
  already_run_phase_2 = true;
  character__10 = from_uchar32(10);
  func__2_1 = create_function(entry__2_1, 2);
  func__3_1 = create_function(entry__3_1, 1);
  func__4_1 = create_function(entry__4_1, -1);
  func__5_1 = create_function(entry__5_1, 2);
  func__6_1 = create_function(entry__6_1, 0);
  func__7_1 = create_function(entry__7_1, 1);
  func__8_1 = create_function(entry__8_1, 1);
  func__9_1 = create_function(entry__9_1, -1);
  func__10_1 = create_function(entry__10_1, -1);
}

static int already_run_phase_3 = false;

EXPORT void phase_3__basic__primitives(void) {
  if (already_run_phase_3) return;
  already_run_phase_3 = true;
  set_module("basic__primitives");
  set_used_namespaces(used_namespaces);
  define_single_assign_static("std", "ignore", get__std__ignore, &var.std__ignore);
  define_single_assign_static("std", "writeln_to", get__std__writeln_to, &var.std__writeln_to);
  define_single_assign_static("std", "swap", get__std__swap, &var.std__swap);
  define_single_assign_static("std", "pass", get__std__pass, &var.std__pass);
  define_single_assign_static("std", "eval", get__std__eval, &var.std__eval);
  define_single_assign_static("std", "do", get__std__do, &var.std__do);
  define_single_assign_static("std", "assign", get__std__assign, &var.std__assign);
  define_single_assign_static("std", "goto", get__std__goto, &var.std__goto);
}

static int already_run_phase_4 = false;

EXPORT void phase_4__basic__primitives(void) {
  if (already_run_phase_4) return;
  already_run_phase_4 = true;
  set_module("basic__primitives");
  set_used_namespaces(used_namespaces);
  use_polymorphic_function(NULL, "has_minimum_length", &get__has_minimum_length, &poly_idx__has_minimum_length);
  use_read_only(NULL, "length_of", &get__length_of, &get_value_or_future__length_of);
  use_read_only(NULL, "pass", &get__pass, &get_value_or_future__pass);
  use_read_only("std", "less", &get__std__less, &get_value_or_future__std__less);
  use_read_only("std", "not", &get__std__not, &get_value_or_future__std__not);
  use_read_only("types", "object", &get__types__object, &get_value_or_future__types__object);
  use_read_only(NULL, "write_to", &get__write_to, &get_value_or_future__write_to);
  define_method("types", "object", poly_idx__has_minimum_length, func__2_1);
}

static int already_run_phase_5 = false;

EXPORT void phase_5__basic__primitives(void) {
  if (already_run_phase_5) return;
  already_run_phase_5 = true;
  assign_value(&var.std__has_minimum_length, create_function(type__std__has_minimum_length, -1));
  assign_variable(&var.std__ignore, &func__3_1);
  assign_variable(&var.std__writeln_to, &func__4_1);
  assign_variable(&var.std__swap, &func__5_1);
  assign_variable(&var.std__pass, &func__6_1);
  assign_variable(&var.std__eval, &func__7_1);
  assign_variable(&var.std__do, &func__8_1);
  assign_variable(&var.std__assign, &func__9_1);
  assign_variable(&var.std__goto, &func__10_1);
}

static int already_run_phase_6 = false;

EXPORT void phase_6__basic__primitives(void) {
  if (already_run_phase_6) return;
  already_run_phase_6 = true;
  register_collector(collect__basic__primitives);
}
