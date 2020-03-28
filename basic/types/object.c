#include <string.h>
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
IMPORT void *collect_simple_node(SIMPLE_NODE *node);
IMPORT void no_such_function(void);
IMPORT OCTREE undefined_attributes_level_1;
IMPORT OCTREE undefined_attributes_level_2;
IMPORT OCTREE undefined_attributes_level_3;
IMPORT OCTREE undefined_attributes_level_4;
IMPORT OCTREE undefined_attributes_level_5;
IMPORT OCTREE undefined_attributes_level_6;
IMPORT OCTREE undefined_attributes_level_7;
IMPORT __attribute__ ((noreturn)) void runtime_error(const char *msg, ...);
REGISTER int argument_count ASM("ebx");
IMPORT void invalid_arguments_error(void);
REGISTER FRAME *arguments ASM("r12");
IMPORT void *node_p;
IMPORT int debug_print(int indent, char *buf, const char *format, ...);
IMPORT int debug_print_head(int *indent_p, char **buf_p, const char *format, ...);
IMPORT const char *indent_to_string(int indent);
IMPORT int polymorphic_function_count;
IMPORT int polymorphic_function_with_setter_count;
IMPORT NODE *get_attribute(NODE *node, int idx);
IMPORT NODE *undefined;
IMPORT const char **polymorphic_function_names;
IMPORT int print(char **buf_p, const char *format, ...);
IMPORT void too_few_arguments_error(void);
IMPORT void too_many_arguments_error(void);
IMPORT int result_count;
REGISTER NODE *myself ASM("r13");
IMPORT void invalid_results_error(void);
IMPORT NODE *from_long(long val);
IMPORT NODE *collect_node(NODE *node);
IMPORT void collect_static_attributes(ATTRIBUTES *attributes);
IMPORT void register_module_info(MODULE_INFO *info);
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
IMPORT void define_attribute(
  const char *namespace, const char *name,
  int id, NODE *attribute
);
IMPORT void define_method(
  const char *namespace, const char *name,
  int id, NODE *method
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
static int poly_idx__default_value;
static NODE_GETTER get__default_value;
static NODE_GETTER get__equal;
static NODE_GETTER get_value_or_future__equal;
static int poly_idx__equal_type_and_value;
static NODE_GETTER get__equal_type_and_value;
static NODE_GETTER get__false;
static NODE_GETTER get_value_or_future__false;
static int poly_idx__is_defined;
static NODE_GETTER get__is_defined;
static int poly_idx__is_undefined;
static NODE_GETTER get__is_undefined;
static int poly_idx__serialize;
static NODE_GETTER get__serialize;
static NODE_GETTER get__std__true;
static NODE_GETTER get_value_or_future__std__true;
static NODE_GETTER get__to_string;
static NODE_GETTER get_value_or_future__to_string;
static NODE_GETTER get__true;
static NODE_GETTER get_value_or_future__true;
static struct {
  NODE *types__object;
  NODE *std__current_address_of;
} var;
static const char *var_names[] = {
};
static NODE *get__types__object(void) {
  return var.types__object;
}
static NODE *create__types__object();
static NODE *func__4_1_types__object_default_value;
static void entry__4_1_types__object_default_value(void);
static FRAME_INFO frame__4_1_types__object_default_value = {2, {"self", "default"}};

int has_prefix(const char *str, const char *prefix)
{
  size_t prefix_len = strlen(prefix);
  size_t str_len = strlen(str);
  return str_len < prefix_len ? false : strncmp(prefix, str, prefix_len) == 0;
}

static long func__types__object___debug_string(NODE *node, int indent, int max_depth, char *buf);
static NODE *func__7_1_types__object_serialize;
static void entry__7_1_types__object_serialize(void);
static FRAME_INFO frame__7_1_types__object_serialize = {2, {"self", "indent"}};
static void cont__7_2(void);
static NODE *func__8_1_types__object_equal_type_and_value;
static void entry__8_1_types__object_equal_type_and_value(void);
static FRAME_INFO frame__8_1_types__object_equal_type_and_value = {2, {"a", "b"}};
static void cont__8_2(void);
static void entry__9_1_std__current_address_of(void);
static NODE *func__9_1_std__current_address_of;
static NODE *get__std__current_address_of(void) {
  return var.std__current_address_of;
}
void run__basic__types__object(void);

static CONTINUATION_INFO continuation_info[] = {
  {run__basic__types__object, NULL, },
  {entry__4_1_types__object_default_value, NULL, 36, 36, 47, 53},
  {entry__7_1_types__object_serialize, NULL, 87, 87, 46, 59},
  {cont__7_2, &frame__7_1_types__object_serialize, 87, 87, 43, 59},
  {entry__8_1_types__object_equal_type_and_value, NULL, 89, 89, 47, 56},
  {cont__8_2, &frame__8_1_types__object_equal_type_and_value, 89, 89, 44, 56},
  {entry__9_1_std__current_address_of, NULL, 100, 103, 3, 2}
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

static const char *used_namespaces[] = {
  "std",
  NULL
};

static MODULE_INFO module_info = {
  NULL,
  "basic__types__object",
  continuation_info,
  sizeof(continuation_info)/sizeof(CONTINUATION_INFO),
  (NODE **)&var,
  var_names,
  sizeof(var_names)/sizeof(const char *),
  used_namespaces,
  {DEBUG_FILENAME("basic/types/object.sim")}
};

/******
C O D E
******/

static int already_run = false;

EXPORT void run__basic__types__object(void) {
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

static VTABLE vtable__types__object = {
  sizeof(SIMPLE_NODE),
  (COLLECTOR *)&collect_simple_node,
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
  &func__types__object___debug_string
};

static ATTRIBUTES attributes__types__object = {
  &vtable__types__object,
  {
    &undefined_attributes_level_1, &undefined_attributes_level_2,
    &undefined_attributes_level_3, &undefined_attributes_level_4,
    &undefined_attributes_level_5, &undefined_attributes_level_6,
    &undefined_attributes_level_7
  }
};

static void type__types__object(void) {
  {
    runtime_error("Attempt to call an object as a function!");
  }
}
SIMPLE_NODE types__object__node =
  {
    type__types__object,
    &attributes__types__object
  };

static NODE *create__types__object() {
  return (NODE *)&types__object__node;
}
static void entry__4_1_types__object_default_value(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // self: 0
  // default: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 36: ... -> self
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}

static long func__types__object___debug_string(NODE *node, int indent, int max_depth, char *buf) {
  if (max_depth == 0) {
    return debug_print(indent, buf, "<object>");
  } else {
    int i, n, len;
    n = debug_print_head(&indent, &buf, "object");
    const char *contents_indent = indent_to_string(indent);
    int count = polymorphic_function_count > polymorphic_function_with_setter_count ? polymorphic_function_count : polymorphic_function_with_setter_count;
    for (i = 0; i < count; ++i) {
      NODE *attr = get_attribute(node, i);
      NODE *attr_addr = (NODE *)((long)attr-1);
      if (
        (long)attr & 1 &&
        (attr_addr)->type != (undefined)->type &&
        strncmp(polymorphic_function_names[i], "std::is_", 8) != 0 &&
        strcmp(polymorphic_function_names[i], "_basic__exceptions::retain_id_of") != 0 &&
        strcmp(polymorphic_function_names[i], "_basic__types__tree::table_of") != 0 &&
        //!has_prefix(polymorphic_function_names[i], "_basic__") &&
        //!has_prefix(polymorphic_function_names[i], "_system__") &&
        (
          attr_addr == get__std__true() ||
          strstr(polymorphic_function_names[i], "::is_") == NULL
        ) &&
        strcmp(polymorphic_function_names[i], "std::parameter_count_of") != 0
      ) {
        n += print(&buf, contents_indent);
        n += print(&buf, "%s:", polymorphic_function_names[i]);
        len = debug_string(attr_addr, -indent-2, max_depth-1, buf);
        if (buf) buf += len;
        n += len;
      }
    }
    return n;
  }
}
static void entry__7_1_types__object_serialize(void) {
  allocate_initialized_frame_gc(2, 3);
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
    case 1: frame->slots[1] /* indent */ = undefined;
  }
  // 87: ... self.to_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__to_string();
  func = myself->type;
  frame->cont = cont__7_2;
}
static void cont__7_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 87: ... -> self.to_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__8_1_types__object_equal_type_and_value(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // a: 0
  // b: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 89: ... equal(a b)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* a */;
  arguments->slots[1] = frame->slots[1] /* b */;
  result_count = 1;
  myself = get__equal();
  func = myself->type;
  frame->cont = cont__8_2;
}
static void cont__8_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 89: ... -> equal(a b)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__9_1_std__current_address_of(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  {
    NODE *result__node = (NODE *)(from_long((long)arguments->slots[0]));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
EXPORT void collect__basic__types__object(void) {
  var.types__object = collect_node(var.types__object);
  collect_static_attributes(&attributes__types__object);
  var.std__current_address_of = collect_node(var.std__current_address_of);
}

static int already_run_phase_1 = false;

EXPORT void phase_1__basic__types__object(void) {
  if (already_run_phase_1) return;
  already_run_phase_1 = true;
  register_module_info(&module_info);
}

static int already_run_phase_2 = false;

EXPORT void phase_2__basic__types__object(void) {
  if (already_run_phase_2) return;
  already_run_phase_2 = true;
  func__4_1_types__object_default_value = create_function(entry__4_1_types__object_default_value, 2);
  func__7_1_types__object_serialize = create_function(entry__7_1_types__object_serialize, -1);
  func__8_1_types__object_equal_type_and_value = create_function(entry__8_1_types__object_equal_type_and_value, 2);
  func__9_1_std__current_address_of = create_function(entry__9_1_std__current_address_of, 1);
}

static int already_run_phase_3 = false;

EXPORT void phase_3__basic__types__object(void) {
  if (already_run_phase_3) return;
  already_run_phase_3 = true;
  set_module("basic__types__object");
  set_used_namespaces(used_namespaces);
  var.types__object = create__types__object();
  define_single_assign_static("types", "object", get__types__object, &var.types__object);
  define_single_assign_static("std", "current_address_of", get__std__current_address_of, &var.std__current_address_of);
}

static int already_run_phase_4 = false;

EXPORT void phase_4__basic__types__object(void) {
  if (already_run_phase_4) return;
  already_run_phase_4 = true;
  set_module("basic__types__object");
  set_used_namespaces(used_namespaces);
  use_polymorphic_function(NULL, "default_value", &get__default_value, &poly_idx__default_value);
  use_read_only(NULL, "equal", &get__equal, &get_value_or_future__equal);
  use_polymorphic_function(NULL, "equal_type_and_value", &get__equal_type_and_value, &poly_idx__equal_type_and_value);
  use_read_only(NULL, "false", &get__false, &get_value_or_future__false);
  use_polymorphic_function(NULL, "is_defined", &get__is_defined, &poly_idx__is_defined);
  use_polymorphic_function(NULL, "is_undefined", &get__is_undefined, &poly_idx__is_undefined);
  use_polymorphic_function(NULL, "serialize", &get__serialize, &poly_idx__serialize);
  use_read_only("std", "true", &get__std__true, &get_value_or_future__std__true);
  use_read_only(NULL, "to_string", &get__to_string, &get_value_or_future__to_string);
  use_read_only(NULL, "true", &get__true, &get_value_or_future__true);
  define_attribute("types", "object", poly_idx__is_defined, get__true());
  define_attribute("types", "object", poly_idx__is_undefined, get__false());
  define_method("types", "object", poly_idx__default_value, func__4_1_types__object_default_value);
  define_method("types", "object", poly_idx__serialize, func__7_1_types__object_serialize);
  define_method("types", "object", poly_idx__equal_type_and_value, func__8_1_types__object_equal_type_and_value);
}

static int already_run_phase_5 = false;

EXPORT void phase_5__basic__types__object(void) {
  if (already_run_phase_5) return;
  already_run_phase_5 = true;
  assign_variable(&var.std__current_address_of, &func__9_1_std__current_address_of);
}

static int already_run_phase_6 = false;

EXPORT void phase_6__basic__types__object(void) {
  if (already_run_phase_6) return;
  already_run_phase_6 = true;
  register_collector(collect__basic__types__object);
}
