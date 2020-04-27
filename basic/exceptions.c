#include <stdlib.h>
#include <runtime/platform.h>
#include <stdint.h>

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
typedef void (*NODE_SETTER)(NODE *);
IMPORT void crash_dump(void);
IMPORT NODE *get_dynamic_slot(int id);
IMPORT void define_dynamic_slot(int id, NODE *node);
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
REGISTER FUNC func ASM("r14");
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
REGISTER NODE *myself ASM("r13");
IMPORT NODE *get_attribute(NODE *node, int idx);
REGISTER FRAME *arguments ASM("r12");
REGISTER int argument_count ASM("ebx");
IMPORT void invalid_arguments_error(void);
IMPORT NODE *clone_object_and_attributes(NODE *node);
IMPORT void *update_start_p;
IMPORT void *node_p;
IMPORT void set_attribute_value(ATTRIBUTES *attributes, int idx, void *attr);
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
IMPORT NODE *undefined;
IMPORT void initialize_maybe_future(NODE *var, NODE *val);
IMPORT NODE *create_cell_with_contents(NODE *contents);
typedef struct CELL {
  FUNC type;
  struct ATTRIBUTES *attributes;
  NODE *contents;
} CELL;
IMPORT int result_count;
IMPORT void invalid_results_error(void);
IMPORT NODE *create_continuation(void);
IMPORT NODE *create_future(void);
IMPORT NODE *create_cell(void);
IMPORT void initialize_future(NODE *var, NODE *val);
IMPORT NODE *create_closure(FUNC type, int par_count);
IMPORT void terminate(int exit_code);
IMPORT void allocate_arguments(void);
IMPORT NODE *from_arguments(int first_idx, int count);
IMPORT NODE *collect_node(NODE *node);
IMPORT void register_module_info(MODULE_INFO *info);
IMPORT void register_polymorphic_function_with_setter(const char *name, int *id_p);
IMPORT NODE *from_uchar32(unsigned int chr);
IMPORT NODE *from_uint32(uint32_t val);
IMPORT NODE *create_function(FUNC func, int par_count);
IMPORT NODE *from_latin_1_string(const char *str, long len);
IMPORT void set_module(const char *name);
IMPORT void set_used_namespaces(const char **namespaces);
IMPORT void register_dynamic(int *id_p);
IMPORT void define_single_assign_static(
  const char *namespace, const char *name,
  NODE_GETTER getter, NODE **var_p
);
IMPORT void define_single_assign_dynamic(
  const char *namespace, const char *name,
  NODE_GETTER getter, NODE_SETTER definer,
  int *id_p
);
IMPORT void use_read_only(
  const char *namespace, const char *name,
  NODE_GETTER *getter, NODE_GETTER *get_value_or_future
);
IMPORT void use_single_assign_dynamic(
  const char *namespace, const char *name,
  NODE_GETTER *getter, NODE_SETTER *definer
);
IMPORT void define_attribute(
  const char *namespace, const char *name,
  int id, NODE *attribute
);
IMPORT void assign_value(NODE **dest, NODE *val);
IMPORT void maybe_initialize_future(NODE *var, NODE *val);
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
static NODE_GETTER get__ErrorMessage;
static NODE_GETTER get_value_or_future__ErrorMessage;
static NODE_GETTER get__STDOUT_FILENO;
static NODE_GETTER get_value_or_future__STDOUT_FILENO;
static NODE_GETTER get__close;
static NODE_GETTER get_value_or_future__close;
static NODE_GETTER get__dec;
static NODE_GETTER get_value_or_future__dec;
static NODE_GETTER get__delete_at;
static NODE_GETTER get_value_or_future__delete_at;
static NODE_GETTER get__div;
static NODE_GETTER get_value_or_future__div;
static NODE_GETTER get__do;
static NODE_GETTER get_value_or_future__do;
static NODE_GETTER get__empty_list;
static NODE_GETTER get_value_or_future__empty_list;
static NODE_GETTER get__ewrite;
static NODE_GETTER get_value_or_future__ewrite;
static NODE_GETTER get__exit;
static NODE_GETTER get_value_or_future__exit;
static NODE_GETTER get__flush;
static NODE_GETTER get_value_or_future__flush;
static NODE_GETTER get__for_each;
static NODE_GETTER get_value_or_future__for_each;
static NODE_GETTER get__get;
static NODE_GETTER get_value_or_future__get;
static NODE_GETTER get__has_suffix;
static NODE_GETTER get_value_or_future__has_suffix;
static NODE_GETTER get__if;
static NODE_GETTER get_value_or_future__if;
static NODE_GETTER get__inc;
static NODE_GETTER get_value_or_future__inc;
static NODE_GETTER get__is_empty;
static NODE_GETTER get_value_or_future__is_empty;
static NODE_GETTER get__is_undefined;
static NODE_GETTER get_value_or_future__is_undefined;
static NODE_GETTER get__length_of;
static NODE_GETTER get_value_or_future__length_of;
static NODE_GETTER get__not;
static NODE_GETTER get_value_or_future__not;
static NODE_GETTER get__parameter_count_of;
static NODE_GETTER get_value_or_future__parameter_count_of;
static NODE_GETTER get__pass;
static NODE_GETTER get_value_or_future__pass;
static NODE_GETTER get__pop;
static NODE_GETTER get_value_or_future__pop;
static NODE_GETTER get__push;
static NODE_GETTER get_value_or_future__push;
static NODE_GETTER get__raise;
static NODE_SETTER define__raise;
static NODE_GETTER get__std__and;
static NODE_GETTER get_value_or_future__std__and;
static NODE_GETTER get__std__equal;
static NODE_GETTER get_value_or_future__std__equal;
static NODE_GETTER get__std__less;
static NODE_GETTER get_value_or_future__std__less;
static NODE_GETTER get__std__minus;
static NODE_GETTER get_value_or_future__std__minus;
static NODE_GETTER get__std__not;
static NODE_GETTER get_value_or_future__std__not;
static NODE_GETTER get__std__or;
static NODE_GETTER get_value_or_future__std__or;
static NODE_GETTER get__std__plus;
static NODE_GETTER get_value_or_future__std__plus;
static NODE_GETTER get__string;
static NODE_GETTER get_value_or_future__string;
static NODE_GETTER get__try;
static NODE_GETTER get_value_or_future__try;
static NODE_GETTER get__types__object;
static NODE_GETTER get_value_or_future__types__object;
static NODE_GETTER get__undefined;
static NODE_GETTER get_value_or_future__undefined;
static NODE_GETTER get__unless;
static NODE_GETTER get_value_or_future__unless;
static NODE_GETTER get__while;
static NODE_GETTER get_value_or_future__while;
static struct {
  NODE *_resource_id_of;
  NODE *_retain_id_of;
  NODE *_next_resource_id;
  NODE *_resources;
  NODE *_cleanup_till;
  NODE *_cleanup;
  NODE *_clib_exit;
  NODE *_exit_functions;
  NODE *_crash_dump;
  NODE *_RuntimeError;
  NODE *std__register_resource;
  NODE *std__deregister_resource;
  NODE *std__at_exit;
  NODE *std__exit;
  NODE *std__terminate;
  NODE *std__ErrorMessage;
  NODE *std__Error;
  NODE *std__try;
  NODE *std__transaction;
  NODE *std__retain;
} var;
static const char *var_names[] = {
  "resource_id_of",
  "retain_id_of",
  "next_resource_id",
  "resources",
  "cleanup_till",
  "cleanup",
  "clib_exit",
  "exit_functions",
  "crash_dump",
  "RuntimeError"
};
static int poly_idx__resource_id_of;
static void type__resource_id_of(void);
static int poly_idx__retain_id_of;
static void type__retain_id_of(void);
static int dyna_idx__first_resource_id;
static NODE *get__first_resource_id(void) {
  return get_dynamic_slot(dyna_idx__first_resource_id);
}
static void define__first_resource_id(NODE *node) {
  define_dynamic_slot(dyna_idx__first_resource_id, node);
}
static NODE *func__std__register_resource_1;
static void entry__std__register_resource_1(void);
static FRAME_INFO frame__std__register_resource_1 = {1, {"resource"}};
static void cont__std__register_resource_2(void);
static void cont__std__register_resource_3(void);
static NODE *get__std__register_resource(void) {
  return var.std__register_resource;
}
static NODE *func__std__deregister_resource_1;
static void entry__std__deregister_resource_1(void);
static FRAME_INFO frame__std__deregister_resource_1 = {4, {"resource", "return", "resource_id", "n"}};
static void cont__std__deregister_resource_2(void);
static void cont__std__deregister_resource_3(void);
static NODE *func__std__deregister_resource_4;
static void entry__std__deregister_resource_4(void);
static FRAME_INFO frame__std__deregister_resource_4 = {3, {"n", "resource_id", "return"}};
static void cont__std__deregister_resource_5(void);
static NODE *func__std__deregister_resource_6;
static void entry__std__deregister_resource_6(void);
static FRAME_INFO frame__std__deregister_resource_6 = {3, {"n", "resource_id", "return"}};
static void cont__std__deregister_resource_7(void);
static void cont__std__deregister_resource_8(void);
static void cont__std__deregister_resource_9(void);
static NODE *func__std__deregister_resource_10;
static void entry__std__deregister_resource_10(void);
static FRAME_INFO frame__std__deregister_resource_10 = {2, {"n", "return"}};
static void cont__std__deregister_resource_11(void);
static void cont__std__deregister_resource_12(void);
static void cont__std__deregister_resource_13(void);
static void cont__std__deregister_resource_14(void);
static NODE *get__std__deregister_resource(void) {
  return var.std__deregister_resource;
}
static NODE *func__cleanup_till_1;
static void entry__cleanup_till_1(void);
static FRAME_INFO frame__cleanup_till_1 = {1, {"id"}};
static NODE *func__cleanup_till_2;
static void entry__cleanup_till_2(void);
static FRAME_INFO frame__cleanup_till_2 = {3, {"repeat_me", "id", "i"}};
static void cont__cleanup_till_3(void);
static NODE *func__cleanup_till_4;
static void entry__cleanup_till_4(void);
static FRAME_INFO frame__cleanup_till_4 = {3, {"break", "i", "id"}};
static NODE *func__cleanup_till_5;
static void entry__cleanup_till_5(void);
static FRAME_INFO frame__cleanup_till_5 = {3, {"i", "id", "break"}};
static void cont__cleanup_till_6(void);
static NODE *func__cleanup_till_7;
static void entry__cleanup_till_7(void);
static FRAME_INFO frame__cleanup_till_7 = {2, {"i", "id"}};
static void cont__cleanup_till_8(void);
static void cont__cleanup_till_9(void);
static void cont__cleanup_till_10(void);
static void cont__cleanup_till_11(void);
static void cont__cleanup_till_12(void);
static NODE *func__cleanup_till_13;
static void entry__cleanup_till_13(void);
static FRAME_INFO frame__cleanup_till_13 = {4, {"i", "id", "break", "resource"}};
static void cont__cleanup_till_14(void);
static void cont__cleanup_till_15(void);
static void cont__cleanup_till_16(void);
static NODE *func__cleanup_till_17;
static void entry__cleanup_till_17(void);
static FRAME_INFO frame__cleanup_till_17 = {2, {"id", "resource"}};
static void cont__cleanup_till_18(void);
static void cont__cleanup_till_19(void);
static void cont__cleanup_till_20(void);
static void cont__cleanup_till_21(void);
static void cont__cleanup_till_22(void);
static void cont__cleanup_till_23(void);
static void cont__cleanup_till_24(void);
static void cont__cleanup_till_25(void);
static NODE *func__cleanup_till_26;
static void entry__cleanup_till_26(void);
static FRAME_INFO frame__cleanup_till_26 = {3, {"i", "repeat_me", "resource"}};
static void cont__cleanup_till_27(void);
static void cont__cleanup_till_28(void);
static void cont__cleanup_till_29(void);
static NODE *func__cleanup_1;
static void entry__cleanup_1(void);
static FRAME_INFO frame__cleanup_1 = {0, {}};
static NODE *func__cleanup_2;
static void entry__cleanup_2(void);
static FRAME_INFO frame__cleanup_2 = {0, {}};
static void cont__cleanup_3(void);
static void cont__cleanup_4(void);
static NODE *func__cleanup_5;
static void entry__cleanup_5(void);
static FRAME_INFO frame__cleanup_5 = {1, {"resource"}};
static void cont__cleanup_6(void);
static void entry__clib_exit_1(void);
static NODE *func__clib_exit_1;
static NODE *func__std__at_exit_1;
static void entry__std__at_exit_1(void);
static FRAME_INFO frame__std__at_exit_1 = {1, {"func"}};
static void cont__std__at_exit_2(void);
static NODE *get__std__at_exit(void) {
  return var.std__at_exit;
}
static NODE *func__std__exit_1;
static void entry__std__exit_1(void);
static FRAME_INFO frame__std__exit_1 = {1, {"status"}};
static NODE *func__std__exit_2;
static void entry__std__exit_2(void);
static FRAME_INFO frame__std__exit_2 = {1, {"func"}};
static void cont__std__exit_3(void);
static void cont__std__exit_4(void);
static NODE *get__std__exit(void) {
  return var.std__exit;
}
static NODE *func__std__terminate_1;
static void entry__std__terminate_1(void);
static FRAME_INFO frame__std__terminate_1 = {0, {}};
static NODE *get__std__terminate(void) {
  return var.std__terminate;
}
static NODE *func__std__ErrorMessage_1;
static void entry__std__ErrorMessage_1(void);
static FRAME_INFO frame__std__ErrorMessage_1 = {2, {"args", "msg"}};
static void cont__std__ErrorMessage_2(void);
static void cont__std__ErrorMessage_3(void);
static NODE *func__std__ErrorMessage_4;
static void entry__std__ErrorMessage_4(void);
static FRAME_INFO frame__std__ErrorMessage_4 = {1, {"msg"}};
static void cont__std__ErrorMessage_5(void);
static void cont__std__ErrorMessage_6(void);
static void cont__std__ErrorMessage_7(void);
static NODE *get__std__ErrorMessage(void) {
  return var.std__ErrorMessage;
}
static NODE *func__std__Error_1;
static void entry__std__Error_1(void);
static FRAME_INFO frame__std__Error_1 = {1, {"args"}};
static void cont__std__Error_2(void);
static void cont__std__Error_3(void);
static NODE *get__std__Error(void) {
  return var.std__Error;
}
static void entry__crash_dump_1(void);
static NODE *func__crash_dump_1;
static NODE *func__RuntimeError_1;
static void entry__RuntimeError_1(void);
static FRAME_INFO frame__RuntimeError_1 = {1, {"args"}};
static void cont__RuntimeError_2(void);
static NODE *func__RuntimeError_3;
static void entry__RuntimeError_3(void);
static FRAME_INFO frame__RuntimeError_3 = {1, {"args"}};
static NODE *string__1700c489be0fe827;
static void cont__RuntimeError_5(void);
static void cont__RuntimeError_6(void);
static void cont__RuntimeError_7(void);
static NODE *func__RuntimeError_8;
static void entry__RuntimeError_8(void);
static FRAME_INFO frame__RuntimeError_8 = {0, {}};
static int dyna_idx__std__raise;
static NODE *get__std__raise(void) {
  return get_dynamic_slot(dyna_idx__std__raise);
}
static void define__std__raise(NODE *node) {
  define_dynamic_slot(dyna_idx__std__raise, node);
}
static NODE *func__std__try_1;
static void entry__std__try_1(void);
static FRAME_INFO frame__std__try_1 = {3, {"bodies", "return", "outer_raise"}};
static NODE *func__std__try_2;
static void entry__std__try_2(void);
static FRAME_INFO frame__std__try_2 = {5, {"return__1", "bodies", "outer_raise", "return", "body"}};
static NODE *func__std__try_3;
static void entry__std__try_3(void);
static FRAME_INFO frame__std__try_3 = {5, {"args", "bodies", "outer_raise", "return", "handler"}};
static void cont__std__try_4(void);
static NODE *func__std__try_5;
static void entry__std__try_5(void);
static FRAME_INFO frame__std__try_5 = {1, {"outer_raise"}};
static NODE *func__std__try_6;
static void entry__std__try_6(void);
static FRAME_INFO frame__std__try_6 = {1, {"bodies"}};
static void cont__std__try_7(void);
static void cont__std__try_8(void);
static void cont__std__try_9(void);
static void cont__std__try_10(void);
static NODE *func__std__try_11;
static void entry__std__try_11(void);
static FRAME_INFO frame__std__try_11 = {2, {"handler", "return"}};
static void cont__std__try_12(void);
static NODE *func__std__try_13;
static void entry__std__try_13(void);
static FRAME_INFO frame__std__try_13 = {3, {"handler", "args", "return"}};
static void cont__std__try_14(void);
static void cont__std__try_15(void);
static void cont__std__try_16(void);
static NODE *func__std__try_17;
static void entry__std__try_17(void);
static FRAME_INFO frame__std__try_17 = {1, {"bodies"}};
static NODE *func__std__try_18;
static void entry__std__try_18(void);
static FRAME_INFO frame__std__try_18 = {1, {"args"}};
static void cont__std__try_19(void);
static void cont__std__try_20(void);
static void cont__std__try_21(void);
static void cont__std__try_22(void);
static NODE *get__std__try(void) {
  return var.std__try;
}
static NODE *func__std__transaction_1;
static void entry__std__transaction_1(void);
static FRAME_INFO frame__std__transaction_1 = {3, {"body", "return__1", "first_id"}};
static void cont__std__transaction_2(void);
static NODE *func__std__transaction_3;
static void entry__std__transaction_3(void);
static FRAME_INFO frame__std__transaction_3 = {2, {"args", "first_id"}};
static void cont__std__transaction_4(void);
static void cont__std__transaction_5(void);
static NODE *get__std__transaction(void) {
  return var.std__transaction;
}
static NODE *func__std__retain_1;
static void entry__std__retain_1(void);
static FRAME_INFO frame__std__retain_1 = {5, {"resource", "id", "s", "e", "retain_id"}};
static void cont__std__retain_2(void);
static NODE *func__std__retain_3;
static void entry__std__retain_3(void);
static FRAME_INFO frame__std__retain_3 = {0, {}};
static NODE *string__5e987c4b4673459c;
static void cont__std__retain_5(void);
static void cont__std__retain_6(void);
static void cont__std__retain_7(void);
static NODE *func__std__retain_8;
static void entry__std__retain_8(void);
static FRAME_INFO frame__std__retain_8 = {3, {"s", "e", "id"}};
static void cont__std__retain_9(void);
static NODE *func__std__retain_10;
static void entry__std__retain_10(void);
static FRAME_INFO frame__std__retain_10 = {4, {"s", "e", "id", "i"}};
static void cont__std__retain_11(void);
static void cont__std__retain_12(void);
static void cont__std__retain_13(void);
static void cont__std__retain_14(void);
static void cont__std__retain_15(void);
static void cont__std__retain_16(void);
static void cont__std__retain_17(void);
static NODE *func__std__retain_18;
static void entry__std__retain_18(void);
static FRAME_INFO frame__std__retain_18 = {2, {"s", "i"}};
static NODE *func__std__retain_19;
static void entry__std__retain_19(void);
static FRAME_INFO frame__std__retain_19 = {2, {"e", "i"}};
static void cont__std__retain_20(void);
static void cont__std__retain_21(void);
static void cont__std__retain_22(void);
static NODE *func__std__retain_23;
static void entry__std__retain_23(void);
static FRAME_INFO frame__std__retain_23 = {2, {"s", "id"}};
static void cont__std__retain_24(void);
static void cont__std__retain_25(void);
static void cont__std__retain_26(void);
static void cont__std__retain_27(void);
static void cont__std__retain_28(void);
static NODE *func__std__retain_29;
static void entry__std__retain_29(void);
static FRAME_INFO frame__std__retain_29 = {0, {}};
static NODE *string__c905c4bfa057bb6c;
static void cont__std__retain_31(void);
static void cont__std__retain_32(void);
static void cont__std__retain_33(void);
static void cont__std__retain_34(void);
static NODE *func__std__retain_35;
static void entry__std__retain_35(void);
static FRAME_INFO frame__std__retain_35 = {1, {"retain_id"}};
static void cont__std__retain_36(void);
static void cont__std__retain_37(void);
static NODE *func__std__retain_38;
static void entry__std__retain_38(void);
static FRAME_INFO frame__std__retain_38 = {1, {"s"}};
static void cont__std__retain_39(void);
static void cont__std__retain_40(void);
static NODE *get__std__retain(void) {
  return var.std__retain;
}
void run__basic__exceptions(void);

static CONTINUATION_INFO continuation_info[] = {
  {type__resource_id_of, NULL, 28, 28, 2, 15},
  {type__retain_id_of, NULL, 30, 30, 2, 13},
  {run__basic__exceptions, NULL, 110, 110, 1, 27},
  {entry__std__register_resource_1, NULL, 45, 45, 3, 23},
  {cont__std__register_resource_2, &frame__std__register_resource_1, 46, 46, 3, 26},
  {cont__std__register_resource_3, &frame__std__register_resource_1, 46, 46, 26, 26},
  {entry__std__deregister_resource_10, NULL, 58, 58, 7, 28},
  {cont__std__deregister_resource_11, &frame__std__deregister_resource_10, 59, 59, 7, 12},
  {entry__std__deregister_resource_6, NULL, 57, 57, 23, 34},
  {cont__std__deregister_resource_7, &frame__std__deregister_resource_6, 57, 57, 8, 35},
  {cont__std__deregister_resource_8, &frame__std__deregister_resource_6, 57, 57, 8, 50},
  {cont__std__deregister_resource_9, &frame__std__deregister_resource_6, 57, 59, 5, 12},
  {cont__std__deregister_resource_12, &frame__std__deregister_resource_6, 60, 60, 5, 10},
  {cont__std__deregister_resource_13, &frame__std__deregister_resource_6, 60, 60, 10, 10},
  {entry__std__deregister_resource_4, NULL, 56, 56, 12, 16},
  {cont__std__deregister_resource_5, &frame__std__deregister_resource_4, 56, 60, 9, 10},
  {entry__std__deregister_resource_1, NULL, 54, 54, 3, 39},
  {cont__std__deregister_resource_2, &frame__std__deregister_resource_1, 55, 55, 3, 26},
  {cont__std__deregister_resource_3, &frame__std__deregister_resource_1, 56, 60, 3, 10},
  {cont__std__deregister_resource_14, &frame__std__deregister_resource_1, 60, 60, 10, 10},
  {entry__cleanup_till_7, NULL, 87, 87, 40, 51},
  {cont__cleanup_till_8, &frame__cleanup_till_7, 87, 87, 25, 52},
  {cont__cleanup_till_9, &frame__cleanup_till_7, 87, 87, 25, 58},
  {cont__cleanup_till_10, &frame__cleanup_till_7, 87, 87, 25, 58},
  {cont__cleanup_till_11, &frame__cleanup_till_7, 87, 87, 25, 58},
  {entry__cleanup_till_17, NULL, 90, 90, 50, 71},
  {cont__cleanup_till_18, &frame__cleanup_till_17, 90, 90, 50, 76},
  {cont__cleanup_till_19, &frame__cleanup_till_17, 90, 90, 50, 76},
  {entry__cleanup_till_13, NULL, 88, 88, 9, 30},
  {cont__cleanup_till_14, &frame__cleanup_till_13, 90, 90, 11, 32},
  {cont__cleanup_till_15, &frame__cleanup_till_13, 90, 90, 11, 45},
  {cont__cleanup_till_16, &frame__cleanup_till_13, 90, 90, 11, 76},
  {cont__cleanup_till_20, &frame__cleanup_till_13, 89, 91, 9, 15},
  {cont__cleanup_till_21, &frame__cleanup_till_13, 92, 92, 9, 14},
  {cont__cleanup_till_22, &frame__cleanup_till_13, 92, 92, 14, 14},
  {entry__cleanup_till_5, NULL, 87, 87, 16, 20},
  {cont__cleanup_till_6, &frame__cleanup_till_5, 87, 87, 16, 58},
  {cont__cleanup_till_12, &frame__cleanup_till_5, 87, 92, 13, 14},
  {entry__cleanup_till_4, NULL, 87, 92, 7, 14},
  {cont__cleanup_till_23, &frame__cleanup_till_4, 92, 92, 14, 14},
  {entry__cleanup_till_26, NULL, 94, 94, 7, 28},
  {cont__cleanup_till_27, &frame__cleanup_till_26, 95, 95, 7, 28},
  {cont__cleanup_till_28, &frame__cleanup_till_26, 96, 96, 7, 20},
  {cont__cleanup_till_29, &frame__cleanup_till_26, 97, 97, 7, 15},
  {entry__cleanup_till_2, NULL, 85, 85, 5, 28},
  {cont__cleanup_till_3, &frame__cleanup_till_2, 86, 92, 5, 15},
  {cont__cleanup_till_24, &frame__cleanup_till_2, 93, 93, 8, 12},
  {cont__cleanup_till_25, &frame__cleanup_till_2, 93, 97, 5, 15},
  {entry__cleanup_till_1, NULL, 84, 97, 3, 16},
  {entry__cleanup_5, NULL, 101, 101, 5, 28},
  {cont__cleanup_6, &frame__cleanup_5, 102, 102, 5, 18},
  {entry__cleanup_2, NULL, 100, 100, 16, 33},
  {cont__cleanup_3, &frame__cleanup_2, 100, 100, 12, 34},
  {cont__cleanup_4, &frame__cleanup_2, 100, 102, 9, 18},
  {entry__cleanup_1, NULL, 100, 102, 3, 18},
  {entry__clib_exit_1, NULL, 105, 108, 3, 2},
  {entry__std__at_exit_1, NULL, 118, 118, 3, 27},
  {cont__std__at_exit_2, &frame__std__at_exit_1, 118, 118, 27, 27},
  {entry__std__exit_2, NULL, 127, 127, 35, 38},
  {entry__std__exit_1, NULL, 127, 127, 3, 38},
  {cont__std__exit_3, &frame__std__exit_1, 128, 128, 3, 9},
  {cont__std__exit_4, &frame__std__exit_1, 129, 129, 3, 18},
  {entry__std__terminate_1, NULL, 135, 135, 5, 10},
  {entry__std__ErrorMessage_4, NULL, 144, 144, 35, 50},
  {cont__std__ErrorMessage_5, &frame__std__ErrorMessage_4, 144, 144, 50, 50},
  {entry__std__ErrorMessage_1, NULL, 143, 143, 3, 21},
  {cont__std__ErrorMessage_2, &frame__std__ErrorMessage_1, 144, 144, 10, 32},
  {cont__std__ErrorMessage_3, &frame__std__ErrorMessage_1, 144, 144, 3, 50},
  {cont__std__ErrorMessage_6, &frame__std__ErrorMessage_1, 145, 145, 3, 21},
  {cont__std__ErrorMessage_7, &frame__std__ErrorMessage_1, 146, 146, 3, 12},
  {entry__std__Error_1, NULL, 154, 154, 3, 9},
  {cont__std__Error_2, &frame__std__Error_1, 155, 155, 3, 20},
  {cont__std__Error_3, &frame__std__Error_1, 156, 156, 3, 8},
  {entry__crash_dump_1, NULL, 159, 163, 3, 2},
  {entry__RuntimeError_3, NULL, 174, 174, 7, 30},
  {cont__RuntimeError_5, &frame__RuntimeError_3, 175, 175, 7, 24},
  {cont__RuntimeError_6, &frame__RuntimeError_3, 176, 176, 7, 16},
  {cont__RuntimeError_7, &frame__RuntimeError_3, 177, 177, 7, 12},
  {entry__RuntimeError_8, NULL, 179, 179, 7, 12},
  {entry__RuntimeError_1, NULL, 171, 171, 3, 9},
  {cont__RuntimeError_2, &frame__RuntimeError_1, 172, 179, 3, 13},
  {entry__std__try_5, NULL, 195, 195, 36, 49},
  {entry__std__try_6, NULL, 195, 195, 55, 66},
  {cont__std__try_7, &frame__std__try_6, 195, 195, 52, 66},
  {entry__std__try_11, NULL, 198, 198, 11, 17},
  {cont__std__try_12, &frame__std__try_11, 199, 199, 11, 16},
  {entry__std__try_13, NULL, 201, 201, 11, 23},
  {cont__std__try_14, &frame__std__try_13, 202, 202, 11, 16},
  {entry__std__try_3, NULL, 195, 195, 19, 33},
  {cont__std__try_4, &frame__std__try_3, 195, 195, 7, 67},
  {cont__std__try_8, &frame__std__try_3, 197, 197, 9, 35},
  {cont__std__try_9, &frame__std__try_3, 197, 197, 9, 40},
  {cont__std__try_10, &frame__std__try_3, 196, 202, 7, 17},
  {entry__std__try_18, NULL, 205, 205, 48, 51},
  {entry__std__try_17, NULL, 205, 205, 25, 51},
  {cont__std__try_19, &frame__std__try_17, 205, 205, 51, 51},
  {entry__std__try_2, NULL, 204, 204, 5, 22},
  {cont__std__try_15, &frame__std__try_2, 205, 205, 8, 22},
  {cont__std__try_16, &frame__std__try_2, 205, 205, 5, 51},
  {cont__std__try_20, &frame__std__try_2, 206, 206, 5, 8},
  {cont__std__try_21, &frame__std__try_2, 206, 206, 8, 8},
  {entry__std__try_1, NULL, 193, 206, 3, 8},
  {cont__std__try_22, &frame__std__try_1, 206, 206, 8, 8},
  {entry__std__transaction_3, NULL, 218, 218, 5, 25},
  {cont__std__transaction_4, &frame__std__transaction_3, 219, 219, 5, 15},
  {entry__std__transaction_1, NULL, 214, 214, 3, 72},
  {cont__std__transaction_2, &frame__std__transaction_1, 217, 219, 3, 15},
  {cont__std__transaction_5, &frame__std__transaction_1, 219, 219, 15, 15},
  {entry__std__retain_3, NULL, 227, 227, 5, 63},
  {entry__std__retain_18, NULL, 235, 235, 12, 12},
  {entry__std__retain_19, NULL, 237, 237, 9, 14},
  {cont__std__retain_20, &frame__std__retain_19, 237, 237, 14, 14},
  {entry__std__retain_10, NULL, 232, 232, 8, 10},
  {cont__std__retain_11, &frame__std__retain_10, 232, 232, 8, 12},
  {cont__std__retain_12, &frame__std__retain_10, 232, 232, 5, 20},
  {cont__std__retain_13, &frame__std__retain_10, 234, 234, 28, 39},
  {cont__std__retain_14, &frame__std__retain_10, 234, 234, 13, 40},
  {cont__std__retain_15, &frame__std__retain_10, 234, 234, 7, 40},
  {cont__std__retain_16, &frame__std__retain_10, 234, 234, 7, 40},
  {cont__std__retain_17, &frame__std__retain_10, 233, 237, 5, 15},
  {entry__std__retain_8, NULL, 231, 231, 12, 16},
  {cont__std__retain_9, &frame__std__retain_8, 231, 237, 9, 16},
  {entry__std__retain_23, NULL, 238, 238, 31, 42},
  {cont__std__retain_24, &frame__std__retain_23, 238, 238, 16, 43},
  {cont__std__retain_25, &frame__std__retain_23, 238, 238, 16, 49},
  {cont__std__retain_26, &frame__std__retain_23, 238, 238, 16, 49},
  {cont__std__retain_27, &frame__std__retain_23, 238, 238, 16, 49},
  {entry__std__retain_29, NULL, 239, 239, 5, 54},
  {entry__std__retain_35, NULL, 241, 241, 32, 60},
  {cont__std__retain_36, &frame__std__retain_35, 241, 241, 32, 60},
  {entry__std__retain_38, NULL, 242, 242, 6, 17},
  {cont__std__retain_39, &frame__std__retain_38, 242, 242, 5, 17},
  {cont__std__retain_40, &frame__std__retain_38, 242, 242, 48, 48},
  {entry__std__retain_1, NULL, 226, 226, 6, 35},
  {cont__std__retain_2, &frame__std__retain_1, 226, 227, 3, 63},
  {cont__std__retain_5, &frame__std__retain_1, 228, 228, 3, 30},
  {cont__std__retain_6, &frame__std__retain_1, 230, 230, 3, 26},
  {cont__std__retain_7, &frame__std__retain_1, 231, 237, 3, 16},
  {cont__std__retain_21, &frame__std__retain_1, 238, 238, 6, 11},
  {cont__std__retain_22, &frame__std__retain_1, 238, 238, 6, 49},
  {cont__std__retain_28, &frame__std__retain_1, 238, 239, 3, 54},
  {cont__std__retain_31, &frame__std__retain_1, 240, 240, 27, 38},
  {cont__std__retain_32, &frame__std__retain_1, 240, 240, 3, 39},
  {cont__std__retain_33, &frame__std__retain_1, 241, 241, 6, 27},
  {cont__std__retain_34, &frame__std__retain_1, 241, 241, 6, 60},
  {cont__std__retain_37, &frame__std__retain_1, 241, 242, 3, 48}
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
static void type__resource_id_of(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__resource_id_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__resource_id_of, attr);
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
static void type__retain_id_of(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__retain_id_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__retain_id_of, attr);
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
static NODE *number__1;
static NODE *number__2;

static const char *used_namespaces[] = {
  "std",
  NULL
};

static MODULE_INFO module_info = {
  NULL,
  "basic__exceptions",
  continuation_info,
  sizeof(continuation_info)/sizeof(CONTINUATION_INFO),
  (NODE **)&var,
  var_names,
  sizeof(var_names)/sizeof(const char *),
  used_namespaces,
  {DEBUG_FILENAME("basic/exceptions.sim")}
};

/******
C O D E
******/

static int already_run = false;

EXPORT void run__basic__exceptions(void) {
  if (already_run) {
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  already_run = true;
  allocate_initialized_frame_gc(0, 0);
  // 35: %first_resource_id undefined
  initialize_maybe_future(get__first_resource_id(), get__undefined());
  // 36: $$next_resource_id 0
  var._next_resource_id = number__0;
  // 37: $$resources empty_list
  var._resources = get__empty_list();
  // 110: $$exit_functions empty_list
  var._exit_functions = get__empty_list();
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__register_resource_1(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // resource: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* resource */ = create_cell_with_contents(arguments->slots[0]);
  // 44: !resource.resource_id_of next_resource_id
  frame->slots[1] /* temp__1 */ = var._next_resource_id;
  // 44: !resource.resource_id_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* resource */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__resource_id_of, frame->slots[1] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* resource */ = temp;

  }
  // 45: inc &next_resource_id
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._next_resource_id;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__std__register_resource_2;
}
static void cont__std__register_resource_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._next_resource_id = arguments->slots[0];
  // 46: push &resources resource
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._resources;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* resource */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__std__register_resource_3;
}
static void cont__std__register_resource_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._resources = arguments->slots[0];
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* resource */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__deregister_resource_1(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // resource: 0
  // return: 1
  // resource_id: 2
  // n: 3
  frame->slots[1] /* return */ = create_continuation();
  frame->slots[2] /* resource_id */ = create_future();
  frame->slots[3] /* n */ = create_cell();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 54: $resource_id resource_id_of(resource)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* resource */;
  result_count = 1;
  myself = var._resource_id_of;
  func = myself->type;
  frame->cont = cont__std__deregister_resource_2;
}
static void cont__std__deregister_resource_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* resource_id */, arguments->slots[0]);
  // 55: $$n length_of(resources)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._resources;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__std__deregister_resource_3;
}
static void cont__std__deregister_resource_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* n */ = arguments->slots[0];
  // 56: ... -> n > 0:
  // 57:   if resource_id_of(resources(n)) == resource_id:
  // 58:     delete_at &resources n
  // 59:     return
  // 60:   dec &n
  frame->slots[4] /* temp__1 */ = create_closure(entry__std__deregister_resource_4, 0);
  // 56: while -> n > 0:
  // 57:   if resource_id_of(resources(n)) == resource_id:
  // 58:     delete_at &resources n
  // 59:     return
  // 60:   dec &n
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__while();
  func = myself->type;
  frame->cont = cont__std__deregister_resource_14;
}
static void entry__std__deregister_resource_6(void) {
  allocate_initialized_frame_gc(3, 7);
  // slot allocations:
  // n: 0
  // resource_id: 1
  // return: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* n */
  frame->slots[1] = myself->closure.frame->slots[1]; /* resource_id */
  frame->slots[2] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 57: ... resources(n)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* n */;
  result_count = 1;
  myself = var._resources;
  func = myself->type;
  frame->cont = cont__std__deregister_resource_7;
}
static void cont__std__deregister_resource_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 57: ... resource_id_of(resources(n))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = var._resource_id_of;
  func = myself->type;
  frame->cont = cont__std__deregister_resource_8;
}
static void cont__std__deregister_resource_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 57: ... resource_id_of(resources(n)) == resource_id
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[1] /* resource_id */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__std__deregister_resource_9;
}
static void cont__std__deregister_resource_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 57: ... :
  // 58:   delete_at &resources n
  // 59:   return
  frame->slots[6] /* temp__4 */ = create_closure(entry__std__deregister_resource_10, 0);
  // 57: if resource_id_of(resources(n)) == resource_id:
  // 58:   delete_at &resources n
  // 59:   return
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__std__deregister_resource_12;
}
static void entry__std__deregister_resource_10(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // n: 0
  // return: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* n */
  frame->slots[1] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 58: delete_at &resources n
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._resources;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* n */;
  result_count = 1;
  myself = get__delete_at();
  func = myself->type;
  frame->cont = cont__std__deregister_resource_11;
}
static void cont__std__deregister_resource_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._resources = arguments->slots[0];
  // 59: return
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__std__deregister_resource_12(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 60: dec &n
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* n */;
  result_count = 1;
  myself = get__dec();
  func = myself->type;
  frame->cont = cont__std__deregister_resource_13;
}
static void cont__std__deregister_resource_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* n */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__deregister_resource_4(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // n: 0
  // resource_id: 1
  // return: 2
  frame->slots[0] = myself->closure.frame->slots[3]; /* n */
  frame->slots[1] = myself->closure.frame->slots[2]; /* resource_id */
  frame->slots[2] = myself->closure.frame->slots[1]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 56: ... n > 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* n */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__std__deregister_resource_5;
}
static void cont__std__deregister_resource_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 56: ... :
  // 57:   if resource_id_of(resources(n)) == resource_id:
  // 58:     delete_at &resources n
  // 59:     return
  // 60:   dec &n
  frame->slots[4] /* temp__2 */ = create_closure(entry__std__deregister_resource_6, 0);
  // 56: ... -> n > 0:
  // 57:   if resource_id_of(resources(n)) == resource_id:
  // 58:     delete_at &resources n
  // 59:     return
  // 60:   dec &n
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__std__deregister_resource_14(void) {
  myself = frame->slots[1] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__cleanup_till_26(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // i: 0
  // repeat_me: 1
  // resource: 2
  frame->slots[0] = myself->closure.frame->slots[2]; /* i */
  frame->slots[1] = myself->closure.frame->slots[0]; /* repeat_me */
  frame->slots[2] /* resource */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 94: $resource resources(i)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* i */;
  result_count = 1;
  myself = var._resources;
  func = myself->type;
  frame->cont = cont__cleanup_till_27;
}
static void cont__cleanup_till_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* resource */, arguments->slots[0]);
  // 95: delete_at &resources i
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._resources;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* i */;
  result_count = 1;
  myself = get__delete_at();
  func = myself->type;
  frame->cont = cont__cleanup_till_28;
}
static void cont__cleanup_till_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._resources = arguments->slots[0];
  // 96: close resource
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* resource */;
  result_count = 0;
  myself = get__close();
  func = myself->type;
  frame->cont = cont__cleanup_till_29;
}
static void cont__cleanup_till_29(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 97: repeat_me
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* repeat_me */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__cleanup_till_2(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // repeat_me: 0
  // id: 1
  // i: 2
  frame->slots[1] = myself->closure.frame->slots[0]; /* id */
  frame->slots[2] /* i */ = create_cell();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* repeat_me */ = myself;
  // 85: $$i length_of(resources)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._resources;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__cleanup_till_3;
}
static void cont__cleanup_till_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* i */ = arguments->slots[0];
  // 86: ... : (-> break)
  // 87:   while -> i > 0 && resource_id_of(resources(i)) >= id:
  // 88:     $resource resources(i)
  // 89:     if
  // 90:       retain_id_of(resource).is_undefined || retain_id_of(resource) > id
  // 91:       break
  // 92:     dec &i
  frame->slots[3] /* temp__1 */ = create_closure(entry__cleanup_till_4, 0);
  // 86: do: (-> break)
  // 87:   while -> i > 0 && resource_id_of(resources(i)) >= id:
  // 88:     $resource resources(i)
  // 89:     if
  // 90:       retain_id_of(resource).is_undefined || retain_id_of(resource) > id
  // 91:       break
  // 92:     dec &i
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = 0;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__cleanup_till_24;
}
static void entry__cleanup_till_4(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // break: 0
  // i: 1
  // id: 2
  frame->slots[0] /* break */ = create_continuation();
  frame->slots[1] = myself->closure.frame->slots[2]; /* i */
  frame->slots[2] = myself->closure.frame->slots[1]; /* id */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 87: ... -> i > 0 && resource_id_of(resources(i)) >= id:
  // 88:   $resource resources(i)
  // 89:   if
  // 90:     retain_id_of(resource).is_undefined || retain_id_of(resource) > id
  // 91:     break
  // 92:   dec &i
  frame->slots[3] /* temp__1 */ = create_closure(entry__cleanup_till_5, 0);
  // 87: while -> i > 0 && resource_id_of(resources(i)) >= id:
  // 88:   $resource resources(i)
  // 89:   if
  // 90:     retain_id_of(resource).is_undefined || retain_id_of(resource) > id
  // 91:     break
  // 92:   dec &i
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__while();
  func = myself->type;
  frame->cont = cont__cleanup_till_23;
}
static void entry__cleanup_till_13(void) {
  allocate_initialized_frame_gc(3, 8);
  // slot allocations:
  // i: 0
  // id: 1
  // break: 2
  // resource: 3
  frame->slots[0] = myself->closure.frame->slots[0]; /* i */
  frame->slots[1] = myself->closure.frame->slots[1]; /* id */
  frame->slots[2] = myself->closure.frame->slots[2]; /* break */
  frame->slots[3] /* resource */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 88: $resource resources(i)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* i */;
  result_count = 1;
  myself = var._resources;
  func = myself->type;
  frame->cont = cont__cleanup_till_14;
}
static void cont__cleanup_till_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* resource */, arguments->slots[0]);
  // 90: retain_id_of(resource)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* resource */;
  result_count = 1;
  myself = var._retain_id_of;
  func = myself->type;
  frame->cont = cont__cleanup_till_15;
}
static void cont__cleanup_till_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 90: retain_id_of(resource).is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__3 */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__cleanup_till_16;
}
static void cont__cleanup_till_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 90: ... retain_id_of(resource) > id
  frame->slots[7] /* temp__4 */ = create_closure(entry__cleanup_till_17, 0);
  // 90: retain_id_of(resource).is_undefined || retain_id_of(resource) > id
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__4 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__cleanup_till_20;
}
static void entry__cleanup_till_17(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // id: 0
  // resource: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* id */
  frame->slots[1] = myself->closure.frame->slots[3]; /* resource */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 90: ... retain_id_of(resource)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* resource */;
  result_count = 1;
  myself = var._retain_id_of;
  func = myself->type;
  frame->cont = cont__cleanup_till_18;
}
static void cont__cleanup_till_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 90: ... retain_id_of(resource) > id
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* id */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__cleanup_till_19;
}
static void cont__cleanup_till_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 90: ... retain_id_of(resource) > id
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__cleanup_till_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 89: if
  // 90:   retain_id_of(resource).is_undefined || retain_id_of(resource) > id
  // 91:   break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* break */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__cleanup_till_21;
}
static void cont__cleanup_till_21(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 92: dec &i
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* i */;
  result_count = 1;
  myself = get__dec();
  func = myself->type;
  frame->cont = cont__cleanup_till_22;
}
static void cont__cleanup_till_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* i */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__cleanup_till_5(void) {
  allocate_initialized_frame_gc(3, 7);
  // slot allocations:
  // i: 0
  // id: 1
  // break: 2
  frame->slots[0] = myself->closure.frame->slots[1]; /* i */
  frame->slots[1] = myself->closure.frame->slots[2]; /* id */
  frame->slots[2] = myself->closure.frame->slots[0]; /* break */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 87: ... i > 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* i */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__cleanup_till_6;
}
static void cont__cleanup_till_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 87: ... resource_id_of(resources(i)) >= id
  frame->slots[5] /* temp__3 */ = create_closure(entry__cleanup_till_7, 0);
  // 87: ... i > 0 && resource_id_of(resources(i)) >= id
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__cleanup_till_12;
}
static void entry__cleanup_till_7(void) {
  allocate_initialized_frame_gc(2, 6);
  // slot allocations:
  // i: 0
  // id: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* i */
  frame->slots[1] = myself->closure.frame->slots[1]; /* id */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 87: ... resources(i)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* i */;
  result_count = 1;
  myself = var._resources;
  func = myself->type;
  frame->cont = cont__cleanup_till_8;
}
static void cont__cleanup_till_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__4 */ = arguments->slots[0];
  // 87: ... resource_id_of(resources(i))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__4 */;
  result_count = 1;
  myself = var._resource_id_of;
  func = myself->type;
  frame->cont = cont__cleanup_till_9;
}
static void cont__cleanup_till_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 87: ... resource_id_of(resources(i)) >= id
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  arguments->slots[1] = frame->slots[1] /* id */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__cleanup_till_10;
}
static void cont__cleanup_till_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 87: ... resource_id_of(resources(i)) >= id
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__cleanup_till_11;
}
static void cont__cleanup_till_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 87: ... resource_id_of(resources(i)) >= id
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__cleanup_till_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 87: ... :
  // 88:   $resource resources(i)
  // 89:   if
  // 90:     retain_id_of(resource).is_undefined || retain_id_of(resource) > id
  // 91:     break
  // 92:   dec &i
  frame->slots[6] /* temp__4 */ = create_closure(entry__cleanup_till_13, 0);
  // 87: ... -> i > 0 && resource_id_of(resources(i)) >= id:
  // 88:   $resource resources(i)
  // 89:   if
  // 90:     retain_id_of(resource).is_undefined || retain_id_of(resource) > id
  // 91:     break
  // 92:   dec &i
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__4 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__cleanup_till_23(void) {
  myself = frame->slots[0] /* break */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__cleanup_till_24(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 93: ... i > 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* i */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__cleanup_till_25;
}
static void cont__cleanup_till_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 93: ... :
  // 94:   $resource resources(i)
  // 95:   delete_at &resources i
  // 96:   close resource
  // 97:   repeat_me
  frame->slots[4] /* temp__2 */ = create_closure(entry__cleanup_till_26, 0);
  // 93: if i > 0:
  // 94:   $resource resources(i)
  // 95:   delete_at &resources i
  // 96:   close resource
  // 97:   repeat_me
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__cleanup_till_1(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // id: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 84: ... : (repeat_me^)
  // 85:   $$i length_of(resources)
  // 86:   do: (-> break)
  // 87:     while -> i > 0 && resource_id_of(resources(i)) >= id:
  // 88:       $resource resources(i)
  // 89:       if
  // 90:         retain_id_of(resource).is_undefined || retain_id_of(resource) > id
  // 91:         break
  // 92:       dec &i
  // 93:   if i > 0:
  // ...
  frame->slots[1] /* temp__1 */ = create_closure(entry__cleanup_till_2, 0);
  // 84: do: (repeat_me^)
  // 85:   $$i length_of(resources)
  // 86:   do: (-> break)
  // 87:     while -> i > 0 && resource_id_of(resources(i)) >= id:
  // 88:       $resource resources(i)
  // 89:       if
  // 90:         retain_id_of(resource).is_undefined || retain_id_of(resource) > id
  // 91:         break
  // 92:       dec &i
  // 93:   if i > 0:
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__do();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__cleanup_5(void) {
  allocate_initialized_frame_gc(0, 2);
  // slot allocations:
  // resource: 0
  frame->slots[0] /* resource */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 101: pop &resources $resource
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._resources;
  result_count = 2;
  myself = get__pop();
  func = myself->type;
  frame->cont = cont__cleanup_6;
}
static void cont__cleanup_6(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  var._resources = arguments->slots[0];
  frame->slots[1] /* temp__1 */ = arguments->slots[1];
  // 101: ... resource
  initialize_future(frame->slots[0] /* resource */, frame->slots[1] /* temp__1 */);
  // 102: close resource
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* resource */;
  result_count = frame->caller_result_count;
  myself = get__close();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__cleanup_2(void) {
  allocate_initialized_frame_gc(0, 2);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 100: ... resources.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._resources;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__cleanup_3;
}
static void cont__cleanup_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 100: ... not(resources.is_empty)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = get__not();
  func = myself->type;
  frame->cont = cont__cleanup_4;
}
static void cont__cleanup_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 100: ... -> not(resources.is_empty):
  // 101:   pop &resources $resource
  // 102:   close resource
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = func__cleanup_5;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__cleanup_1(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 100: while -> not(resources.is_empty):
  // 101:   pop &resources $resource
  // 102:   close resource
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__cleanup_2;
  result_count = frame->caller_result_count;
  myself = get__while();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__clib_exit_1(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  terminate(to_int(arguments->slots[0]));
}
static void entry__std__at_exit_1(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // func: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 118: push &exit_functions func
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._exit_functions;
  arguments->slots[1] = frame->slots[0] /* func */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__std__at_exit_2;
}
static void cont__std__at_exit_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._exit_functions = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__exit_1(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // status: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 127: for_each exit_functions: (func) func
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._exit_functions;
  arguments->slots[1] = func__std__exit_2;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__std__exit_3;
}
static void entry__std__exit_2(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // func: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 127: ... func
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* func */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__std__exit_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 128: cleanup
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = var._cleanup;
  func = myself->type;
  frame->cont = cont__std__exit_4;
}
static void cont__std__exit_4(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 129: clib_exit status
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* status */;
  result_count = frame->caller_result_count;
  myself = var._clib_exit;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__terminate_1(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 135: exit 0
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__0;
  result_count = frame->caller_result_count;
  myself = get__exit();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__ErrorMessage_1(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // args: 0
  // msg: 1
  frame->slots[1] /* msg */ = create_cell();
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 143: $$msg string(args*)
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[0] /* args */);
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__std__ErrorMessage_2;
}
static void cont__std__ErrorMessage_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* msg */ = arguments->slots[0];
  // 144: ... msg .has_suffix. '@nl;'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* msg */;
  arguments->slots[1] = character__10;
  result_count = 1;
  myself = get__has_suffix();
  func = myself->type;
  frame->cont = cont__std__ErrorMessage_3;
}
static void cont__std__ErrorMessage_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 144: ... : push &msg '@nl;'
  frame->slots[3] /* temp__2 */ = create_closure(entry__std__ErrorMessage_4, 0);
  // 144: unless msg .has_suffix. '@nl;': push &msg '@nl;'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__std__ErrorMessage_6;
}
static void entry__std__ErrorMessage_4(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // msg: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* msg */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 144: ... push &msg '@nl;'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* msg */;
  arguments->slots[1] = character__10;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__std__ErrorMessage_5;
}
static void cont__std__ErrorMessage_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* msg */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__std__ErrorMessage_6(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 145: flush STDOUT_FILENO
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__STDOUT_FILENO();
  result_count = 0;
  myself = get__flush();
  func = myself->type;
  frame->cont = cont__std__ErrorMessage_7;
}
static void cont__std__ErrorMessage_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 146: ewrite msg
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* msg */;
  result_count = frame->caller_result_count;
  myself = get__ewrite();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__Error_1(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // args: 0
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 154: cleanup
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = var._cleanup;
  func = myself->type;
  frame->cont = cont__std__Error_2;
}
static void cont__std__Error_2(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 155: ErrorMessage args*
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[0] /* args */);
  result_count = 0;
  myself = get__ErrorMessage();
  func = myself->type;
  frame->cont = cont__std__Error_3;
}
static void cont__std__Error_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 156: exit 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = frame->caller_result_count;
  myself = get__exit();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__crash_dump_1(void) {
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  crash_dump();
  {
    argument_count = 0;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__RuntimeError_3(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // args: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* args */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 174: ewrite "RUNTIME ERROR: "
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__1700c489be0fe827;
  result_count = 0;
  myself = get__ewrite();
  func = myself->type;
  frame->cont = cont__RuntimeError_5;
}
static void cont__RuntimeError_5(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 175: ErrorMessage args*
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[0] /* args */);
  result_count = 0;
  myself = get__ErrorMessage();
  func = myself->type;
  frame->cont = cont__RuntimeError_6;
}
static void cont__RuntimeError_6(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 176: crash_dump
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = var._crash_dump;
  func = myself->type;
  frame->cont = cont__RuntimeError_7;
}
static void cont__RuntimeError_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 177: exit 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = frame->caller_result_count;
  myself = get__exit();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__RuntimeError_8(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 179: exit 2
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = frame->caller_result_count;
  myself = get__exit();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__RuntimeError_1(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // args: 0
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 171: cleanup
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = var._cleanup;
  func = myself->type;
  frame->cont = cont__RuntimeError_2;
}
static void cont__RuntimeError_2(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 173: :
  // 174:   ewrite "RUNTIME ERROR: "
  // 175:   ErrorMessage args*
  // 176:   crash_dump
  // 177:   exit 1
  frame->slots[1] /* temp__1 */ = create_closure(entry__RuntimeError_3, 0);
  // 172: try
  // 173:   :
  // 174:     ewrite "RUNTIME ERROR: "
  // 175:     ErrorMessage args*
  // 176:     crash_dump
  // 177:     exit 1
  // 178:   :
  // 179:     exit 2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = func__RuntimeError_8;
  result_count = frame->caller_result_count;
  myself = get__try();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__try_1(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // bodies: 0
  // return: 1
  // outer_raise: 2
  frame->slots[1] /* return */ = create_continuation();
  // _define $outer_raise raise
  frame->slots[2] /* outer_raise */ = get__raise();
  frame->slots[0] /* bodies */ = create_cell_with_contents(from_arguments(0, argument_count-0));
  // 192: $outer_raise raise
  initialize_maybe_future(frame->slots[2] /* outer_raise */, get__raise());
  // 193: ... :
  // 194:   %raise: (args*)
  // 195:     $handler if(bodies.is_empty (-> outer_raise) -> get(&bodies))
  // 196:     if
  // 197:       parameter_count_of(handler) == 0:
  // 198:         handler
  // 199:         return
  // 200:       :
  // 201:         handler args*
  // 202:         return
  // ...
  frame->slots[3] /* temp__1 */ = create_closure(entry__std__try_2, 0);
  // 193: do:
  // 194:   %raise: (args*)
  // 195:     $handler if(bodies.is_empty (-> outer_raise) -> get(&bodies))
  // 196:     if
  // 197:       parameter_count_of(handler) == 0:
  // 198:         handler
  // 199:         return
  // 200:       :
  // 201:         handler args*
  // 202:         return
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__std__try_22;
}
static void entry__std__try_2(void) {
  allocate_initialized_frame_gc(4, 7);
  // slot allocations:
  // return__1: 0
  // bodies: 1
  // outer_raise: 2
  // return: 3
  // body: 4
  frame->slots[0] /* return__1 */ = create_continuation();
  frame->slots[1] = myself->closure.frame->slots[0]; /* bodies */
  frame->slots[2] = myself->closure.frame->slots[2]; /* outer_raise */
  frame->slots[3] = myself->closure.frame->slots[1]; /* return */
  define__raise(create_future());
  frame->slots[4] /* body */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 194: ... : (args*)
  // 195:   $handler if(bodies.is_empty (-> outer_raise) -> get(&bodies))
  // 196:   if
  // 197:     parameter_count_of(handler) == 0:
  // 198:       handler
  // 199:       return
  // 200:     :
  // 201:       handler args*
  // 202:       return
  frame->slots[5] /* temp__1 */ = create_closure(entry__std__try_3, -1);
  // 194: %raise: (args*)
  // 195:   $handler if(bodies.is_empty (-> outer_raise) -> get(&bodies))
  // 196:   if
  // 197:     parameter_count_of(handler) == 0:
  // 198:       handler
  // 199:       return
  // 200:     :
  // 201:       handler args*
  // 202:       return
  initialize_future(get__raise(), frame->slots[5] /* temp__1 */);
  // 204: $body get(&bodies)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* bodies */;
  result_count = 2;
  myself = get__get();
  func = myself->type;
  frame->cont = cont__std__try_15;
}
static void entry__std__try_11(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // handler: 0
  // return: 1
  frame->slots[0] = myself->closure.frame->slots[4]; /* handler */
  frame->slots[1] = myself->closure.frame->slots[3]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 198: handler
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = frame->slots[0] /* handler */;
  func = myself->type;
  frame->cont = cont__std__try_12;
}
static void cont__std__try_12(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 199: return
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__try_13(void) {
  allocate_initialized_frame_gc(3, 3);
  // slot allocations:
  // handler: 0
  // args: 1
  // return: 2
  frame->slots[0] = myself->closure.frame->slots[4]; /* handler */
  frame->slots[1] = myself->closure.frame->slots[0]; /* args */
  frame->slots[2] = myself->closure.frame->slots[3]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 201: handler args*
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[1] /* args */);
  result_count = 0;
  myself = frame->slots[0] /* handler */;
  func = myself->type;
  frame->cont = cont__std__try_14;
}
static void cont__std__try_14(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 202: return
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__try_3(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(4, 9);
  // slot allocations:
  // args: 0
  // bodies: 1
  // outer_raise: 2
  // return: 3
  // handler: 4
  frame->slots[1] = myself->closure.frame->slots[1]; /* bodies */
  frame->slots[2] = myself->closure.frame->slots[2]; /* outer_raise */
  frame->slots[3] = myself->closure.frame->slots[3]; /* return */
  frame->slots[4] /* handler */ = create_future();
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 195: ... bodies.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* bodies */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__std__try_4;
}
static void cont__std__try_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 195: ... -> outer_raise
  frame->slots[6] /* temp__2 */ = create_closure(entry__std__try_5, 0);
  // 195: ... -> get(&bodies)
  frame->slots[7] /* temp__3 */ = create_closure(entry__std__try_6, 0);
  // 195: $handler if(bodies.is_empty (-> outer_raise) -> get(&bodies))
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  arguments->slots[2] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__std__try_8;
}
static void entry__std__try_5(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // outer_raise: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* outer_raise */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 195: ... -> outer_raise
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* outer_raise */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__try_6(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // bodies: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* bodies */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 195: ... get(&bodies)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* bodies */;
  result_count = 2;
  myself = get__get();
  func = myself->type;
  frame->cont = cont__std__try_7;
}
static void cont__std__try_7(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* bodies */ = arguments->slots[0];
  frame->slots[1] /* temp__1 */ = arguments->slots[1];
  // 195: ... -> get(&bodies)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__std__try_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* handler */, arguments->slots[0]);
  // 197: parameter_count_of(handler)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* handler */;
  result_count = 1;
  myself = get__parameter_count_of();
  func = myself->type;
  frame->cont = cont__std__try_9;
}
static void cont__std__try_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 197: parameter_count_of(handler) == 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__std__try_10;
}
static void cont__std__try_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 197: ... :
  // 198:   handler
  // 199:   return
  frame->slots[7] /* temp__3 */ = create_closure(entry__std__try_11, 0);
  // 200: :
  // 201:   handler args*
  // 202:   return
  frame->slots[8] /* temp__4 */ = create_closure(entry__std__try_13, 0);
  // 196: if
  // 197:   parameter_count_of(handler) == 0:
  // 198:     handler
  // 199:     return
  // 200:   :
  // 201:     handler args*
  // 202:     return
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  arguments->slots[2] = frame->slots[8] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__std__try_15(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* bodies */ = arguments->slots[0];
  frame->slots[5] /* temp__1 */ = arguments->slots[1];
  // 204: ... body
  initialize_future(frame->slots[4] /* body */, frame->slots[5] /* temp__1 */);
  // 205: ... bodies.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* bodies */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__std__try_16;
}
static void cont__std__try_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 205: ... : push &bodies: (_args*) pass
  frame->slots[6] /* temp__2 */ = create_closure(entry__std__try_17, 0);
  // 205: if bodies.is_empty: push &bodies: (_args*) pass
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__std__try_20;
}
static void entry__std__try_17(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // bodies: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* bodies */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 205: ... push &bodies: (_args*) pass
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* bodies */;
  arguments->slots[1] = func__std__try_18;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__std__try_19;
}
static void entry__std__try_18(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // args: 0
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 205: ... pass
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = get__pass();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__std__try_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* bodies */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__std__try_20(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 206: body
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[4] /* body */;
  func = myself->type;
  frame->cont = cont__std__try_21;
}
static void cont__std__try_21(void) {
  myself = frame->slots[0] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__std__try_22(void) {
  myself = frame->slots[1] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__std__transaction_1(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // body: 0
  // return__1: 1
  // first_id: 2
  frame->slots[1] /* return__1 */ = create_continuation();
  frame->slots[2] /* first_id */ = create_future();
  // _define %first_resource_id first_id
  define__first_resource_id(frame->slots[2] /* first_id */);
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 214: inc &next_resource_id # prevent that two transactions have the same id
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._next_resource_id;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__std__transaction_2;
}
static void cont__std__transaction_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._next_resource_id = arguments->slots[0];
  // 215: $first_id next_resource_id
  initialize_future(frame->slots[2] /* first_id */, var._next_resource_id);
  // 216: %first_resource_id first_id
  initialize_maybe_future(get__first_resource_id(), frame->slots[2] /* first_id */);
  // 217: ... : (args*)
  // 218:   cleanup_till first_id
  // 219:   raise args*
  frame->slots[3] /* temp__1 */ = create_closure(entry__std__transaction_3, -1);
  // 217: try body: (args*)
  // 218:   cleanup_till first_id
  // 219:   raise args*
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* body */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__try();
  func = myself->type;
  frame->cont = cont__std__transaction_5;
}
static void entry__std__transaction_3(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // args: 0
  // first_id: 1
  frame->slots[1] = myself->closure.frame->slots[2]; /* first_id */
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 218: cleanup_till first_id
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* first_id */;
  result_count = 0;
  myself = var._cleanup_till;
  func = myself->type;
  frame->cont = cont__std__transaction_4;
}
static void cont__std__transaction_4(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 219: raise args*
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[0] /* args */);
  result_count = frame->caller_result_count;
  myself = get__raise();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__std__transaction_5(void) {
  myself = frame->slots[1] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__std__retain_38(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // s: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* s */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 242: !resources(s).retain_id_of first_resource_id
  frame->slots[1] /* temp__1 */ = get__first_resource_id();
  // 242: ... resources(s)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* s */;
  result_count = 1;
  myself = var._resources;
  func = myself->type;
  frame->cont = cont__std__retain_39;
}
static void cont__std__retain_39(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 242: !resources(s).retain_id_of
  {
    NODE *temp = clone_object_and_attributes(frame->slots[2] /* temp__2 */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__retain_id_of, frame->slots[1] /* temp__1 */);
    frame->slots[2] /* temp__2 */ = temp;

  }
  // 242: !resources(s)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* s */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = var._resources;
  func = myself->type;
  frame->cont = cont__std__retain_40;
}
static void cont__std__retain_40(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._resources = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__retain_1(void) {
  allocate_initialized_frame_gc(1, 9);
  // slot allocations:
  // resource: 0
  // id: 1
  // s: 2
  // e: 3
  // retain_id: 4
  frame->slots[1] /* id */ = create_future();
  frame->slots[2] /* s */ = create_cell();
  frame->slots[3] /* e */ = create_cell();
  frame->slots[4] /* retain_id */ = create_future();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 226: ... first_resource_id.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__first_resource_id();
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__std__retain_2;
}
static void cont__std__retain_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 226: if first_resource_id.is_undefined:
  // 227:   raise "Attempt to retain a resource outside a transaction!"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = func__std__retain_3;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__std__retain_5;
}
static void entry__std__retain_3(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 227: raise "Attempt to retain a resource outside a transaction!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__5e987c4b4673459c;
  result_count = frame->caller_result_count;
  myself = get__raise();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__std__retain_5(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 228: $id resource_id_of(resource)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* resource */;
  result_count = 1;
  myself = var._resource_id_of;
  func = myself->type;
  frame->cont = cont__std__retain_6;
}
static void cont__std__retain_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* id */, arguments->slots[0]);
  // 229: $$s 1
  ((CELL *)frame->slots[2])->contents /* s */ = number__1;
  // 230: $$e length_of(resources)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._resources;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__std__retain_7;
}
static void cont__std__retain_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* e */ = arguments->slots[0];
  // 231: ... -> e > s:
  // 232:   $i s+e+1 .div. 2
  // 233:   if
  // 234:     id >= resource_id_of(resources(i)):
  // 235:       !s i
  // 236:     :
  // 237:       !e i-i
  frame->slots[5] /* temp__1 */ = create_closure(entry__std__retain_8, 0);
  // 231: while -> e > s:
  // 232:   $i s+e+1 .div. 2
  // 233:   if
  // 234:     id >= resource_id_of(resources(i)):
  // 235:       !s i
  // 236:     :
  // 237:       !e i-i
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  result_count = 0;
  myself = get__while();
  func = myself->type;
  frame->cont = cont__std__retain_21;
}
static void entry__std__retain_18(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // s: 0
  // i: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* s */
  frame->slots[1] = myself->closure.frame->slots[3]; /* i */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 235: !s i
  ((CELL *)frame->slots[0])->contents /* s */ = frame->slots[1] /* i */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__retain_19(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // e: 0
  // i: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* e */
  frame->slots[1] = myself->closure.frame->slots[3]; /* i */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 237: !e i-i
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* i */;
  arguments->slots[1] = frame->slots[1] /* i */;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__std__retain_20;
}
static void cont__std__retain_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* e */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__retain_10(void) {
  allocate_initialized_frame_gc(3, 10);
  // slot allocations:
  // s: 0
  // e: 1
  // id: 2
  // i: 3
  frame->slots[0] = myself->closure.frame->slots[0]; /* s */
  frame->slots[1] = myself->closure.frame->slots[1]; /* e */
  frame->slots[2] = myself->closure.frame->slots[2]; /* id */
  frame->slots[3] /* i */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 232: ... s+e
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* s */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* e */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__std__retain_11;
}
static void cont__std__retain_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 232: ... s+e+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__std__retain_12;
}
static void cont__std__retain_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 232: $i s+e+1 .div. 2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__div();
  func = myself->type;
  frame->cont = cont__std__retain_13;
}
static void cont__std__retain_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* i */, arguments->slots[0]);
  // 234: ... resources(i)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* i */;
  result_count = 1;
  myself = var._resources;
  func = myself->type;
  frame->cont = cont__std__retain_14;
}
static void cont__std__retain_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__4 */ = arguments->slots[0];
  // 234: ... resource_id_of(resources(i))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__4 */;
  result_count = 1;
  myself = var._resource_id_of;
  func = myself->type;
  frame->cont = cont__std__retain_15;
}
static void cont__std__retain_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 234: id >= resource_id_of(resources(i))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* id */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__std__retain_16;
}
static void cont__std__retain_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 234: id >= resource_id_of(resources(i))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__std__retain_17;
}
static void cont__std__retain_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 234: ... :
  // 235:   !s i
  frame->slots[8] /* temp__5 */ = create_closure(entry__std__retain_18, 0);
  // 236: :
  // 237:   !e i-i
  frame->slots[9] /* temp__6 */ = create_closure(entry__std__retain_19, 0);
  // 233: if
  // 234:   id >= resource_id_of(resources(i)):
  // 235:     !s i
  // 236:   :
  // 237:     !e i-i
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__5 */;
  arguments->slots[2] = frame->slots[9] /* temp__6 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__retain_8(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // s: 0
  // e: 1
  // id: 2
  frame->slots[0] = myself->closure.frame->slots[2]; /* s */
  frame->slots[1] = myself->closure.frame->slots[3]; /* e */
  frame->slots[2] = myself->closure.frame->slots[1]; /* id */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 231: ... e > s
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* s */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* e */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__std__retain_9;
}
static void cont__std__retain_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 231: ... :
  // 232:   $i s+e+1 .div. 2
  // 233:   if
  // 234:     id >= resource_id_of(resources(i)):
  // 235:       !s i
  // 236:     :
  // 237:       !e i-i
  frame->slots[4] /* temp__2 */ = create_closure(entry__std__retain_10, 0);
  // 231: ... -> e > s:
  // 232:   $i s+e+1 .div. 2
  // 233:   if
  // 234:     id >= resource_id_of(resources(i)):
  // 235:       !s i
  // 236:     :
  // 237:       !e i-i
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__std__retain_21(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 238: ... e == 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* e */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__std__retain_22;
}
static void cont__std__retain_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 238: ... resource_id_of(resources(s)) != id
  frame->slots[7] /* temp__3 */ = create_closure(entry__std__retain_23, 0);
  // 238: ... e == 0 || resource_id_of(resources(s)) != id
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__std__retain_28;
}
static void entry__std__retain_23(void) {
  allocate_initialized_frame_gc(2, 6);
  // slot allocations:
  // s: 0
  // id: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* s */
  frame->slots[1] = myself->closure.frame->slots[1]; /* id */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 238: ... resources(s)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* s */;
  result_count = 1;
  myself = var._resources;
  func = myself->type;
  frame->cont = cont__std__retain_24;
}
static void cont__std__retain_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__4 */ = arguments->slots[0];
  // 238: ... resource_id_of(resources(s))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__4 */;
  result_count = 1;
  myself = var._resource_id_of;
  func = myself->type;
  frame->cont = cont__std__retain_25;
}
static void cont__std__retain_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 238: ... resource_id_of(resources(s)) != id
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  arguments->slots[1] = frame->slots[1] /* id */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__std__retain_26;
}
static void cont__std__retain_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 238: ... resource_id_of(resources(s)) != id
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__std__retain_27;
}
static void cont__std__retain_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 238: ... resource_id_of(resources(s)) != id
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__std__retain_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 238: if e == 0 || resource_id_of(resources(s)) != id:
  // 239:   raise "Attempt to retain an nonexistant resource!"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = func__std__retain_29;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__std__retain_31;
}
static void entry__std__retain_29(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 239: raise "Attempt to retain an nonexistant resource!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__c905c4bfa057bb6c;
  result_count = frame->caller_result_count;
  myself = get__raise();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__std__retain_31(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 240: ... resources(s)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* s */;
  result_count = 1;
  myself = var._resources;
  func = myself->type;
  frame->cont = cont__std__retain_32;
}
static void cont__std__retain_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 240: $retain_id retain_id_of(resources(s))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  result_count = 1;
  myself = var._retain_id_of;
  func = myself->type;
  frame->cont = cont__std__retain_33;
}
static void cont__std__retain_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* retain_id */, arguments->slots[0]);
  // 241: ... retain_id.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* retain_id */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__std__retain_34;
}
static void cont__std__retain_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 241: ... first_resource_id < retain_id
  frame->slots[7] /* temp__3 */ = create_closure(entry__std__retain_35, 0);
  // 241: ... retain_id.is_undefined || first_resource_id < retain_id
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__std__retain_37;
}
static void entry__std__retain_35(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // retain_id: 0
  frame->slots[0] = myself->closure.frame->slots[4]; /* retain_id */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 241: ... first_resource_id < retain_id
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__first_resource_id();
  arguments->slots[1] = frame->slots[0] /* retain_id */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__std__retain_36;
}
static void cont__std__retain_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 241: ... first_resource_id < retain_id
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__std__retain_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 241: ... :
  // 242:   !resources(s).retain_id_of first_resource_id
  frame->slots[8] /* temp__4 */ = create_closure(entry__std__retain_38, 0);
  // 241: if retain_id.is_undefined || first_resource_id < retain_id:
  // 242:   !resources(s).retain_id_of first_resource_id
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
EXPORT void collect__basic__exceptions(void) {
  var._resource_id_of = collect_node(var._resource_id_of);
  var._retain_id_of = collect_node(var._retain_id_of);
  var._next_resource_id = collect_node(var._next_resource_id);
  var._resources = collect_node(var._resources);
  var.std__register_resource = collect_node(var.std__register_resource);
  var.std__deregister_resource = collect_node(var.std__deregister_resource);
  var._cleanup_till = collect_node(var._cleanup_till);
  var._cleanup = collect_node(var._cleanup);
  var._clib_exit = collect_node(var._clib_exit);
  var._exit_functions = collect_node(var._exit_functions);
  var.std__at_exit = collect_node(var.std__at_exit);
  var.std__exit = collect_node(var.std__exit);
  var.std__terminate = collect_node(var.std__terminate);
  var.std__ErrorMessage = collect_node(var.std__ErrorMessage);
  var.std__Error = collect_node(var.std__Error);
  var._crash_dump = collect_node(var._crash_dump);
  var._RuntimeError = collect_node(var._RuntimeError);
  var.std__try = collect_node(var.std__try);
  var.std__transaction = collect_node(var.std__transaction);
  var.std__retain = collect_node(var.std__retain);
}

static int already_run_phase_1 = false;

EXPORT void phase_1__basic__exceptions(void) {
  if (already_run_phase_1) return;
  already_run_phase_1 = true;
  register_module_info(&module_info);
  register_polymorphic_function_with_setter("_basic__exceptions::resource_id_of", &poly_idx__resource_id_of);
  register_polymorphic_function_with_setter("_basic__exceptions::retain_id_of", &poly_idx__retain_id_of);
}

static int already_run_phase_2 = false;

EXPORT void phase_2__basic__exceptions(void) {
  if (already_run_phase_2) return;
  already_run_phase_2 = true;
  character__10 = from_uchar32(10);
  number__0 = from_uint32(0U);
  number__1 = from_uint32(1U);
  number__2 = from_uint32(2U);
  func__std__register_resource_1 = create_function(entry__std__register_resource_1, 1);
  func__std__deregister_resource_1 = create_function(entry__std__deregister_resource_1, 1);
  func__cleanup_till_1 = create_function(entry__cleanup_till_1, 1);
  func__cleanup_5 = create_function(entry__cleanup_5, 0);
  func__cleanup_2 = create_function(entry__cleanup_2, 0);
  func__cleanup_1 = create_function(entry__cleanup_1, 0);
  func__clib_exit_1 = create_function(entry__clib_exit_1, 1);
  func__std__at_exit_1 = create_function(entry__std__at_exit_1, 1);
  func__std__exit_2 = create_function(entry__std__exit_2, 1);
  func__std__exit_1 = create_function(entry__std__exit_1, 1);
  func__std__terminate_1 = create_function(entry__std__terminate_1, 0);
  func__std__ErrorMessage_1 = create_function(entry__std__ErrorMessage_1, -1);
  func__std__Error_1 = create_function(entry__std__Error_1, -1);
  func__crash_dump_1 = create_function(entry__crash_dump_1, 0);
  string__1700c489be0fe827 = from_latin_1_string("RUNTIME ERROR: ", 15);
  func__RuntimeError_8 = create_function(entry__RuntimeError_8, 0);
  func__RuntimeError_1 = create_function(entry__RuntimeError_1, -1);
  func__std__try_18 = create_function(entry__std__try_18, -1);
  func__std__try_1 = create_function(entry__std__try_1, -1);
  func__std__transaction_1 = create_function(entry__std__transaction_1, 1);
  string__5e987c4b4673459c = from_latin_1_string("Attempt to retain a resource outside a transaction!", 51);
  func__std__retain_3 = create_function(entry__std__retain_3, 0);
  string__c905c4bfa057bb6c = from_latin_1_string("Attempt to retain an nonexistant resource!", 42);
  func__std__retain_29 = create_function(entry__std__retain_29, 0);
  func__std__retain_1 = create_function(entry__std__retain_1, 1);
}

static int already_run_phase_3 = false;

EXPORT void phase_3__basic__exceptions(void) {
  if (already_run_phase_3) return;
  already_run_phase_3 = true;
  set_module("basic__exceptions");
  set_used_namespaces(used_namespaces);
  register_dynamic(&dyna_idx__first_resource_id);
  define__first_resource_id(create_future());
  define_single_assign_static("std", "register_resource", get__std__register_resource, &var.std__register_resource);
  define_single_assign_static("std", "deregister_resource", get__std__deregister_resource, &var.std__deregister_resource);
  define_single_assign_static("std", "at_exit", get__std__at_exit, &var.std__at_exit);
  define_single_assign_static("std", "exit", get__std__exit, &var.std__exit);
  define_single_assign_static("std", "terminate", get__std__terminate, &var.std__terminate);
  define_single_assign_static("std", "ErrorMessage", get__std__ErrorMessage, &var.std__ErrorMessage);
  define_single_assign_static("std", "Error", get__std__Error, &var.std__Error);
  define_single_assign_dynamic("std", "raise", get__std__raise, define__std__raise, &dyna_idx__std__raise);
  define__std__raise(create_future());
  define_single_assign_static("std", "try", get__std__try, &var.std__try);
  define_single_assign_static("std", "transaction", get__std__transaction, &var.std__transaction);
  define_single_assign_static("std", "retain", get__std__retain, &var.std__retain);
}

static int already_run_phase_4 = false;

EXPORT void phase_4__basic__exceptions(void) {
  if (already_run_phase_4) return;
  already_run_phase_4 = true;
  set_module("basic__exceptions");
  set_used_namespaces(used_namespaces);
  use_read_only(NULL, "ErrorMessage", &get__ErrorMessage, &get_value_or_future__ErrorMessage);
  use_read_only(NULL, "STDOUT_FILENO", &get__STDOUT_FILENO, &get_value_or_future__STDOUT_FILENO);
  use_read_only(NULL, "close", &get__close, &get_value_or_future__close);
  use_read_only(NULL, "dec", &get__dec, &get_value_or_future__dec);
  use_read_only(NULL, "delete_at", &get__delete_at, &get_value_or_future__delete_at);
  use_read_only(NULL, "div", &get__div, &get_value_or_future__div);
  use_read_only(NULL, "do", &get__do, &get_value_or_future__do);
  use_read_only(NULL, "empty_list", &get__empty_list, &get_value_or_future__empty_list);
  use_read_only(NULL, "ewrite", &get__ewrite, &get_value_or_future__ewrite);
  use_read_only(NULL, "exit", &get__exit, &get_value_or_future__exit);
  use_read_only(NULL, "flush", &get__flush, &get_value_or_future__flush);
  use_read_only(NULL, "for_each", &get__for_each, &get_value_or_future__for_each);
  use_read_only(NULL, "get", &get__get, &get_value_or_future__get);
  use_read_only(NULL, "has_suffix", &get__has_suffix, &get_value_or_future__has_suffix);
  use_read_only(NULL, "if", &get__if, &get_value_or_future__if);
  use_read_only(NULL, "inc", &get__inc, &get_value_or_future__inc);
  use_read_only(NULL, "is_empty", &get__is_empty, &get_value_or_future__is_empty);
  use_read_only(NULL, "is_undefined", &get__is_undefined, &get_value_or_future__is_undefined);
  use_read_only(NULL, "length_of", &get__length_of, &get_value_or_future__length_of);
  use_read_only(NULL, "not", &get__not, &get_value_or_future__not);
  use_read_only(NULL, "parameter_count_of", &get__parameter_count_of, &get_value_or_future__parameter_count_of);
  use_read_only(NULL, "pass", &get__pass, &get_value_or_future__pass);
  use_read_only(NULL, "pop", &get__pop, &get_value_or_future__pop);
  use_read_only(NULL, "push", &get__push, &get_value_or_future__push);
  use_single_assign_dynamic(NULL, "raise", &get__raise, &define__raise);
  use_read_only("std", "and", &get__std__and, &get_value_or_future__std__and);
  use_read_only("std", "equal", &get__std__equal, &get_value_or_future__std__equal);
  use_read_only("std", "less", &get__std__less, &get_value_or_future__std__less);
  use_read_only("std", "minus", &get__std__minus, &get_value_or_future__std__minus);
  use_read_only("std", "not", &get__std__not, &get_value_or_future__std__not);
  use_read_only("std", "or", &get__std__or, &get_value_or_future__std__or);
  use_read_only("std", "plus", &get__std__plus, &get_value_or_future__std__plus);
  use_read_only(NULL, "string", &get__string, &get_value_or_future__string);
  use_read_only(NULL, "try", &get__try, &get_value_or_future__try);
  use_read_only("types", "object", &get__types__object, &get_value_or_future__types__object);
  use_read_only(NULL, "undefined", &get__undefined, &get_value_or_future__undefined);
  use_read_only(NULL, "unless", &get__unless, &get_value_or_future__unless);
  use_read_only(NULL, "while", &get__while, &get_value_or_future__while);
  define_attribute("types", "object", poly_idx__retain_id_of, get__undefined());
}

static int already_run_phase_5 = false;

EXPORT void phase_5__basic__exceptions(void) {
  if (already_run_phase_5) return;
  already_run_phase_5 = true;
  assign_value(&var._resource_id_of, create_function(type__resource_id_of, -1));
  assign_value(&var._retain_id_of, create_function(type__retain_id_of, -1));
  maybe_initialize_future(get__first_resource_id(), get__undefined());
  assign_variable(&var.std__register_resource, &func__std__register_resource_1);
  assign_variable(&var.std__deregister_resource, &func__std__deregister_resource_1);
  assign_variable(&var._cleanup_till, &func__cleanup_till_1);
  assign_variable(&var._cleanup, &func__cleanup_1);
  assign_variable(&var._clib_exit, &func__clib_exit_1);
  assign_variable(&var.std__at_exit, &func__std__at_exit_1);
  assign_variable(&var.std__exit, &func__std__exit_1);
  assign_variable(&var.std__terminate, &func__std__terminate_1);
  assign_variable(&var.std__ErrorMessage, &func__std__ErrorMessage_1);
  assign_variable(&var.std__Error, &func__std__Error_1);
  assign_variable(&var._crash_dump, &func__crash_dump_1);
  assign_variable(&var._RuntimeError, &func__RuntimeError_1);
  initialize_future(get__std__raise(), var._RuntimeError);
  assign_variable(&var.std__try, &func__std__try_1);
  assign_variable(&var.std__transaction, &func__std__transaction_1);
  assign_variable(&var.std__retain, &func__std__retain_1);
}

static int already_run_phase_6 = false;

EXPORT void phase_6__basic__exceptions(void) {
  if (already_run_phase_6) return;
  already_run_phase_6 = true;
  register_collector(collect__basic__exceptions);
}
