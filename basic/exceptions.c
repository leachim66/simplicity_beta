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
IMPORT NODE *register_unique_item(const char *name);
IMPORT NODE *create_function(FUNC func, int par_count);
IMPORT NODE *from_latin_1_string(const char *str, long len);
IMPORT void set_module(const char *name);
IMPORT void set_used_namespaces(const char **namespaces);
IMPORT void assign_value(NODE **dest, NODE *val);
IMPORT void define_single_assign_static(
  const char *namespace, const char *name,
  NODE_GETTER getter, NODE **var_p
);
IMPORT void register_dynamic(int *id_p);
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
  NODE *std__CLEANUP;
  NODE *std__ERROR_MESSAGE;
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
static NODE *unique__std__CLEANUP;
static NODE *get__std__CLEANUP(void) {
  return var.std__CLEANUP;
}
static NODE *unique__std__ERROR_MESSAGE;
static NODE *get__std__ERROR_MESSAGE(void) {
  return var.std__ERROR_MESSAGE;
}
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
static NODE *func__9_1_std__register_resource;
static void entry__9_1_std__register_resource(void);
static FRAME_INFO frame__9_1_std__register_resource = {1, {"resource"}};
static void cont__9_2(void);
static void cont__9_3(void);
static NODE *get__std__register_resource(void) {
  return var.std__register_resource;
}
static NODE *func__10_1_std__deregister_resource;
static void entry__10_1_std__deregister_resource(void);
static FRAME_INFO frame__10_1_std__deregister_resource = {4, {"resource", "return", "resource_id", "n"}};
static void cont__10_2(void);
static void cont__10_3(void);
static NODE *func__10_4;
static void entry__10_4(void);
static FRAME_INFO frame__10_4 = {3, {"n", "resource_id", "return"}};
static void cont__10_5(void);
static NODE *func__10_6;
static void entry__10_6(void);
static FRAME_INFO frame__10_6 = {3, {"n", "resource_id", "return"}};
static void cont__10_7(void);
static void cont__10_8(void);
static void cont__10_9(void);
static NODE *func__10_10;
static void entry__10_10(void);
static FRAME_INFO frame__10_10 = {2, {"n", "return"}};
static void cont__10_11(void);
static void cont__10_12(void);
static void cont__10_13(void);
static void cont__10_14(void);
static NODE *get__std__deregister_resource(void) {
  return var.std__deregister_resource;
}
static NODE *func__11_1_cleanup_till;
static void entry__11_1_cleanup_till(void);
static FRAME_INFO frame__11_1_cleanup_till = {1, {"id"}};
static NODE *func__11_2;
static void entry__11_2(void);
static FRAME_INFO frame__11_2 = {3, {"repeat_me", "id", "i"}};
static void cont__11_3(void);
static NODE *func__11_4;
static void entry__11_4(void);
static FRAME_INFO frame__11_4 = {3, {"break", "i", "id"}};
static NODE *func__11_5;
static void entry__11_5(void);
static FRAME_INFO frame__11_5 = {3, {"i", "id", "break"}};
static void cont__11_6(void);
static NODE *func__11_7;
static void entry__11_7(void);
static FRAME_INFO frame__11_7 = {2, {"i", "id"}};
static void cont__11_8(void);
static void cont__11_9(void);
static void cont__11_10(void);
static void cont__11_11(void);
static void cont__11_12(void);
static NODE *func__11_13;
static void entry__11_13(void);
static FRAME_INFO frame__11_13 = {4, {"i", "id", "break", "resource"}};
static void cont__11_14(void);
static void cont__11_15(void);
static void cont__11_16(void);
static NODE *func__11_17;
static void entry__11_17(void);
static FRAME_INFO frame__11_17 = {2, {"id", "resource"}};
static void cont__11_18(void);
static void cont__11_19(void);
static void cont__11_20(void);
static void cont__11_21(void);
static void cont__11_22(void);
static void cont__11_23(void);
static void cont__11_24(void);
static void cont__11_25(void);
static NODE *func__11_26;
static void entry__11_26(void);
static FRAME_INFO frame__11_26 = {3, {"i", "repeat_me", "resource"}};
static void cont__11_27(void);
static void cont__11_28(void);
static void cont__11_29(void);
static NODE *func__12_1_cleanup;
static void entry__12_1_cleanup(void);
static FRAME_INFO frame__12_1_cleanup = {0, {}};
static NODE *func__12_2;
static void entry__12_2(void);
static FRAME_INFO frame__12_2 = {0, {}};
static void cont__12_3(void);
static void cont__12_4(void);
static NODE *func__12_5;
static void entry__12_5(void);
static FRAME_INFO frame__12_5 = {1, {"resource"}};
static void cont__12_6(void);
static void entry__13_1_clib_exit(void);
static NODE *func__13_1_clib_exit;
static NODE *func__15_1_std__at_exit;
static void entry__15_1_std__at_exit(void);
static FRAME_INFO frame__15_1_std__at_exit = {1, {"func"}};
static void cont__15_2(void);
static NODE *get__std__at_exit(void) {
  return var.std__at_exit;
}
static NODE *func__16_1_std__exit;
static void entry__16_1_std__exit(void);
static FRAME_INFO frame__16_1_std__exit = {1, {"status"}};
static NODE *func__16_2;
static void entry__16_2(void);
static FRAME_INFO frame__16_2 = {1, {"func"}};
static void cont__16_3(void);
static void cont__16_4(void);
static NODE *get__std__exit(void) {
  return var.std__exit;
}
static NODE *func__17_1_std__terminate;
static void entry__17_1_std__terminate(void);
static FRAME_INFO frame__17_1_std__terminate = {0, {}};
static NODE *get__std__terminate(void) {
  return var.std__terminate;
}
static NODE *func__18_1_std__ErrorMessage;
static void entry__18_1_std__ErrorMessage(void);
static FRAME_INFO frame__18_1_std__ErrorMessage = {2, {"args", "msg"}};
static void cont__18_2(void);
static void cont__18_3(void);
static NODE *func__18_4;
static void entry__18_4(void);
static FRAME_INFO frame__18_4 = {1, {"msg"}};
static void cont__18_5(void);
static void cont__18_6(void);
static void cont__18_7(void);
static NODE *get__std__ErrorMessage(void) {
  return var.std__ErrorMessage;
}
static NODE *func__19_1_std__Error;
static void entry__19_1_std__Error(void);
static FRAME_INFO frame__19_1_std__Error = {1, {"args"}};
static void cont__19_2(void);
static void cont__19_3(void);
static NODE *get__std__Error(void) {
  return var.std__Error;
}
static void entry__20_1_crash_dump(void);
static NODE *func__20_1_crash_dump;
static NODE *func__21_1_RuntimeError;
static void entry__21_1_RuntimeError(void);
static FRAME_INFO frame__21_1_RuntimeError = {1, {"args"}};
static void cont__21_2(void);
static NODE *func__21_3;
static void entry__21_3(void);
static FRAME_INFO frame__21_3 = {1, {"args"}};
static NODE *string__21_4;
static void cont__21_5(void);
static void cont__21_6(void);
static void cont__21_7(void);
static NODE *func__21_8;
static void entry__21_8(void);
static FRAME_INFO frame__21_8 = {0, {}};
static int dyna_idx__std__raise;
static NODE *get__std__raise(void) {
  return get_dynamic_slot(dyna_idx__std__raise);
}
static void define__std__raise(NODE *node) {
  define_dynamic_slot(dyna_idx__std__raise, node);
}
static NODE *func__23_1_std__try;
static void entry__23_1_std__try(void);
static FRAME_INFO frame__23_1_std__try = {3, {"bodies", "return", "outer_raise"}};
static NODE *func__23_2;
static void entry__23_2(void);
static FRAME_INFO frame__23_2 = {5, {"return__1", "bodies", "outer_raise", "return", "body"}};
static NODE *func__23_3_raise;
static void entry__23_3_raise(void);
static FRAME_INFO frame__23_3_raise = {5, {"args", "bodies", "outer_raise", "return", "handler"}};
static void cont__23_4(void);
static NODE *func__23_5;
static void entry__23_5(void);
static FRAME_INFO frame__23_5 = {1, {"outer_raise"}};
static NODE *func__23_6;
static void entry__23_6(void);
static FRAME_INFO frame__23_6 = {1, {"bodies"}};
static void cont__23_7(void);
static void cont__23_8(void);
static void cont__23_9(void);
static void cont__23_10(void);
static NODE *func__23_11;
static void entry__23_11(void);
static FRAME_INFO frame__23_11 = {2, {"handler", "return"}};
static void cont__23_12(void);
static NODE *func__23_13;
static void entry__23_13(void);
static FRAME_INFO frame__23_13 = {3, {"handler", "args", "return"}};
static void cont__23_14(void);
static void cont__23_15(void);
static void cont__23_16(void);
static NODE *func__23_17;
static void entry__23_17(void);
static FRAME_INFO frame__23_17 = {1, {"bodies"}};
static NODE *func__23_18;
static void entry__23_18(void);
static FRAME_INFO frame__23_18 = {1, {"args"}};
static void cont__23_19(void);
static void cont__23_20(void);
static void cont__23_21(void);
static void cont__23_22(void);
static NODE *get__std__try(void) {
  return var.std__try;
}
static NODE *func__24_1_std__transaction;
static void entry__24_1_std__transaction(void);
static FRAME_INFO frame__24_1_std__transaction = {3, {"body", "return__1", "first_id"}};
static void cont__24_2(void);
static NODE *func__24_3;
static void entry__24_3(void);
static FRAME_INFO frame__24_3 = {2, {"args", "first_id"}};
static void cont__24_4(void);
static void cont__24_5(void);
static NODE *get__std__transaction(void) {
  return var.std__transaction;
}
static NODE *func__25_1_std__retain;
static void entry__25_1_std__retain(void);
static FRAME_INFO frame__25_1_std__retain = {5, {"resource", "id", "s", "e", "retain_id"}};
static void cont__25_2(void);
static NODE *func__25_3;
static void entry__25_3(void);
static FRAME_INFO frame__25_3 = {0, {}};
static NODE *string__25_4;
static void cont__25_5(void);
static void cont__25_6(void);
static void cont__25_7(void);
static NODE *func__25_8;
static void entry__25_8(void);
static FRAME_INFO frame__25_8 = {3, {"s", "e", "id"}};
static void cont__25_9(void);
static NODE *func__25_10;
static void entry__25_10(void);
static FRAME_INFO frame__25_10 = {4, {"s", "e", "id", "i"}};
static void cont__25_11(void);
static void cont__25_12(void);
static void cont__25_13(void);
static void cont__25_14(void);
static void cont__25_15(void);
static void cont__25_16(void);
static void cont__25_17(void);
static NODE *func__25_18;
static void entry__25_18(void);
static FRAME_INFO frame__25_18 = {2, {"s", "i"}};
static NODE *func__25_19;
static void entry__25_19(void);
static FRAME_INFO frame__25_19 = {2, {"e", "i"}};
static void cont__25_20(void);
static void cont__25_21(void);
static void cont__25_22(void);
static NODE *func__25_23;
static void entry__25_23(void);
static FRAME_INFO frame__25_23 = {2, {"s", "id"}};
static void cont__25_24(void);
static void cont__25_25(void);
static void cont__25_26(void);
static void cont__25_27(void);
static void cont__25_28(void);
static NODE *func__25_29;
static void entry__25_29(void);
static FRAME_INFO frame__25_29 = {0, {}};
static NODE *string__25_30;
static void cont__25_31(void);
static void cont__25_32(void);
static void cont__25_33(void);
static void cont__25_34(void);
static NODE *func__25_35;
static void entry__25_35(void);
static FRAME_INFO frame__25_35 = {1, {"retain_id"}};
static void cont__25_36(void);
static void cont__25_37(void);
static NODE *func__25_38;
static void entry__25_38(void);
static FRAME_INFO frame__25_38 = {1, {"s"}};
static void cont__25_39(void);
static void cont__25_40(void);
static NODE *get__std__retain(void) {
  return var.std__retain;
}
void run__basic__exceptions(void);

static CONTINUATION_INFO continuation_info[] = {
  {type__resource_id_of, NULL, 28, 28, 2, 15},
  {type__retain_id_of, NULL, 29, 29, 2, 13},
  {run__basic__exceptions, NULL, 98, 98, 1, 27},
  {entry__9_1_std__register_resource, NULL, 38, 38, 3, 23},
  {cont__9_2, &frame__9_1_std__register_resource, 39, 39, 3, 26},
  {cont__9_3, &frame__9_1_std__register_resource, 39, 39, 26, 26},
  {entry__10_10, NULL, 50, 50, 7, 28},
  {cont__10_11, &frame__10_10, 51, 51, 7, 12},
  {entry__10_6, NULL, 49, 49, 23, 34},
  {cont__10_7, &frame__10_6, 49, 49, 8, 35},
  {cont__10_8, &frame__10_6, 49, 49, 8, 50},
  {cont__10_9, &frame__10_6, 49, 51, 5, 12},
  {cont__10_12, &frame__10_6, 52, 52, 5, 10},
  {cont__10_13, &frame__10_6, 52, 52, 10, 10},
  {entry__10_4, NULL, 48, 48, 12, 16},
  {cont__10_5, &frame__10_4, 48, 52, 9, 10},
  {entry__10_1_std__deregister_resource, NULL, 46, 46, 3, 39},
  {cont__10_2, &frame__10_1_std__deregister_resource, 47, 47, 3, 26},
  {cont__10_3, &frame__10_1_std__deregister_resource, 48, 52, 3, 10},
  {cont__10_14, &frame__10_1_std__deregister_resource, 52, 52, 10, 10},
  {entry__11_7, NULL, 75, 75, 40, 51},
  {cont__11_8, &frame__11_7, 75, 75, 25, 52},
  {cont__11_9, &frame__11_7, 75, 75, 25, 58},
  {cont__11_10, &frame__11_7, 75, 75, 25, 58},
  {cont__11_11, &frame__11_7, 75, 75, 25, 58},
  {entry__11_17, NULL, 78, 78, 50, 71},
  {cont__11_18, &frame__11_17, 78, 78, 50, 76},
  {cont__11_19, &frame__11_17, 78, 78, 50, 76},
  {entry__11_13, NULL, 76, 76, 9, 30},
  {cont__11_14, &frame__11_13, 78, 78, 11, 32},
  {cont__11_15, &frame__11_13, 78, 78, 11, 45},
  {cont__11_16, &frame__11_13, 78, 78, 11, 76},
  {cont__11_20, &frame__11_13, 77, 79, 9, 15},
  {cont__11_21, &frame__11_13, 80, 80, 9, 14},
  {cont__11_22, &frame__11_13, 80, 80, 14, 14},
  {entry__11_5, NULL, 75, 75, 16, 20},
  {cont__11_6, &frame__11_5, 75, 75, 16, 58},
  {cont__11_12, &frame__11_5, 75, 80, 13, 14},
  {entry__11_4, NULL, 75, 80, 7, 14},
  {cont__11_23, &frame__11_4, 80, 80, 14, 14},
  {entry__11_26, NULL, 82, 82, 7, 28},
  {cont__11_27, &frame__11_26, 83, 83, 7, 28},
  {cont__11_28, &frame__11_26, 84, 84, 7, 20},
  {cont__11_29, &frame__11_26, 85, 85, 7, 15},
  {entry__11_2, NULL, 73, 73, 5, 28},
  {cont__11_3, &frame__11_2, 74, 80, 5, 15},
  {cont__11_24, &frame__11_2, 81, 81, 8, 12},
  {cont__11_25, &frame__11_2, 81, 85, 5, 15},
  {entry__11_1_cleanup_till, NULL, 72, 85, 3, 16},
  {entry__12_5, NULL, 89, 89, 5, 28},
  {cont__12_6, &frame__12_5, 90, 90, 5, 18},
  {entry__12_2, NULL, 88, 88, 16, 33},
  {cont__12_3, &frame__12_2, 88, 88, 12, 34},
  {cont__12_4, &frame__12_2, 88, 90, 9, 18},
  {entry__12_1_cleanup, NULL, 88, 90, 3, 18},
  {entry__13_1_clib_exit, NULL, 93, 96, 3, 2},
  {entry__15_1_std__at_exit, NULL, 100, 100, 23, 47},
  {cont__15_2, &frame__15_1_std__at_exit, 100, 100, 47, 47},
  {entry__16_2, NULL, 103, 103, 35, 38},
  {entry__16_1_std__exit, NULL, 103, 103, 3, 38},
  {cont__16_3, &frame__16_1_std__exit, 104, 104, 3, 9},
  {cont__16_4, &frame__16_1_std__exit, 105, 105, 3, 18},
  {entry__17_1_std__terminate, NULL, 107, 107, 18, 23},
  {entry__18_4, NULL, 111, 111, 35, 50},
  {cont__18_5, &frame__18_4, 111, 111, 50, 50},
  {entry__18_1_std__ErrorMessage, NULL, 110, 110, 3, 21},
  {cont__18_2, &frame__18_1_std__ErrorMessage, 111, 111, 10, 32},
  {cont__18_3, &frame__18_1_std__ErrorMessage, 111, 111, 3, 50},
  {cont__18_6, &frame__18_1_std__ErrorMessage, 112, 112, 3, 21},
  {cont__18_7, &frame__18_1_std__ErrorMessage, 113, 113, 3, 12},
  {entry__19_1_std__Error, NULL, 116, 116, 3, 9},
  {cont__19_2, &frame__19_1_std__Error, 117, 117, 3, 20},
  {cont__19_3, &frame__19_1_std__Error, 118, 118, 3, 8},
  {entry__20_1_crash_dump, NULL, 121, 125, 3, 2},
  {entry__21_3, NULL, 131, 131, 7, 30},
  {cont__21_5, &frame__21_3, 132, 132, 7, 24},
  {cont__21_6, &frame__21_3, 133, 133, 7, 16},
  {cont__21_7, &frame__21_3, 134, 134, 7, 12},
  {entry__21_8, NULL, 136, 136, 7, 12},
  {entry__21_1_RuntimeError, NULL, 128, 128, 3, 9},
  {cont__21_2, &frame__21_1_RuntimeError, 129, 136, 3, 13},
  {entry__23_5, NULL, 148, 148, 36, 49},
  {entry__23_6, NULL, 148, 148, 55, 66},
  {cont__23_7, &frame__23_6, 148, 148, 52, 66},
  {entry__23_11, NULL, 151, 151, 11, 17},
  {cont__23_12, &frame__23_11, 152, 152, 11, 16},
  {entry__23_13, NULL, 154, 154, 11, 23},
  {cont__23_14, &frame__23_13, 155, 155, 11, 16},
  {entry__23_3_raise, NULL, 148, 148, 19, 33},
  {cont__23_4, &frame__23_3_raise, 148, 148, 7, 67},
  {cont__23_8, &frame__23_3_raise, 150, 150, 9, 35},
  {cont__23_9, &frame__23_3_raise, 150, 150, 9, 40},
  {cont__23_10, &frame__23_3_raise, 149, 155, 7, 17},
  {entry__23_18, NULL, 158, 158, 48, 51},
  {entry__23_17, NULL, 158, 158, 25, 51},
  {cont__23_19, &frame__23_17, 158, 158, 51, 51},
  {entry__23_2, NULL, 157, 157, 5, 22},
  {cont__23_15, &frame__23_2, 158, 158, 8, 22},
  {cont__23_16, &frame__23_2, 158, 158, 5, 51},
  {cont__23_20, &frame__23_2, 159, 159, 5, 8},
  {cont__23_21, &frame__23_2, 159, 159, 8, 8},
  {entry__23_1_std__try, NULL, 146, 159, 3, 8},
  {cont__23_22, &frame__23_1_std__try, 159, 159, 8, 8},
  {entry__24_3, NULL, 166, 166, 5, 25},
  {cont__24_4, &frame__24_3, 167, 167, 5, 15},
  {entry__24_1_std__transaction, NULL, 162, 162, 3, 72},
  {cont__24_2, &frame__24_1_std__transaction, 165, 167, 3, 15},
  {cont__24_5, &frame__24_1_std__transaction, 167, 167, 15, 15},
  {entry__25_3, NULL, 171, 171, 5, 63},
  {entry__25_18, NULL, 179, 179, 12, 12},
  {entry__25_19, NULL, 181, 181, 9, 14},
  {cont__25_20, &frame__25_19, 181, 181, 14, 14},
  {entry__25_10, NULL, 176, 176, 8, 10},
  {cont__25_11, &frame__25_10, 176, 176, 8, 12},
  {cont__25_12, &frame__25_10, 176, 176, 5, 20},
  {cont__25_13, &frame__25_10, 178, 178, 28, 39},
  {cont__25_14, &frame__25_10, 178, 178, 13, 40},
  {cont__25_15, &frame__25_10, 178, 178, 7, 40},
  {cont__25_16, &frame__25_10, 178, 178, 7, 40},
  {cont__25_17, &frame__25_10, 177, 181, 5, 15},
  {entry__25_8, NULL, 175, 175, 12, 16},
  {cont__25_9, &frame__25_8, 175, 181, 9, 16},
  {entry__25_23, NULL, 182, 182, 31, 42},
  {cont__25_24, &frame__25_23, 182, 182, 16, 43},
  {cont__25_25, &frame__25_23, 182, 182, 16, 49},
  {cont__25_26, &frame__25_23, 182, 182, 16, 49},
  {cont__25_27, &frame__25_23, 182, 182, 16, 49},
  {entry__25_29, NULL, 183, 183, 5, 54},
  {entry__25_35, NULL, 185, 185, 32, 60},
  {cont__25_36, &frame__25_35, 185, 185, 32, 60},
  {entry__25_38, NULL, 186, 186, 6, 17},
  {cont__25_39, &frame__25_38, 186, 186, 5, 17},
  {cont__25_40, &frame__25_38, 186, 186, 48, 48},
  {entry__25_1_std__retain, NULL, 170, 170, 6, 35},
  {cont__25_2, &frame__25_1_std__retain, 170, 171, 3, 63},
  {cont__25_5, &frame__25_1_std__retain, 172, 172, 3, 30},
  {cont__25_6, &frame__25_1_std__retain, 174, 174, 3, 26},
  {cont__25_7, &frame__25_1_std__retain, 175, 181, 3, 16},
  {cont__25_21, &frame__25_1_std__retain, 182, 182, 6, 11},
  {cont__25_22, &frame__25_1_std__retain, 182, 182, 6, 49},
  {cont__25_28, &frame__25_1_std__retain, 182, 183, 3, 54},
  {cont__25_31, &frame__25_1_std__retain, 184, 184, 27, 38},
  {cont__25_32, &frame__25_1_std__retain, 184, 184, 3, 39},
  {cont__25_33, &frame__25_1_std__retain, 185, 185, 6, 27},
  {cont__25_34, &frame__25_1_std__retain, 185, 185, 6, 60},
  {cont__25_37, &frame__25_1_std__retain, 185, 186, 3, 48}
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
  // 32: %first_resource_id undefined
  initialize_maybe_future(get__first_resource_id(), get__undefined());
  // 33: $$next_resource_id 0
  var._next_resource_id = number__0;
  // 34: $$resources empty_list
  var._resources = get__empty_list();
  // 98: $$exit_functions empty_list
  var._exit_functions = get__empty_list();
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__9_1_std__register_resource(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // resource: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* resource */ = create_cell_with_contents(arguments->slots[0]);
  // 37: !resource.resource_id_of next_resource_id
  frame->slots[1] /* temp__1 */ = var._next_resource_id;
  // 37: !resource.resource_id_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* resource */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__resource_id_of, frame->slots[1] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* resource */ = temp;

  }
  // 38: inc &next_resource_id
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._next_resource_id;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__9_2;
}
static void cont__9_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._next_resource_id = arguments->slots[0];
  // 39: push &resources resource
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._resources;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* resource */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__9_3;
}
static void cont__9_3(void) {
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
static void entry__10_1_std__deregister_resource(void) {
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
  // 46: $resource_id resource_id_of(resource)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* resource */;
  result_count = 1;
  myself = var._resource_id_of;
  func = myself->type;
  frame->cont = cont__10_2;
}
static void cont__10_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* resource_id */, arguments->slots[0]);
  // 47: $$n length_of(resources)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._resources;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__10_3;
}
static void cont__10_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* n */ = arguments->slots[0];
  // 48: ... -> n > 0:
  // 49:   if resource_id_of(resources(n)) == resource_id:
  // 50:     delete_at &resources n
  // 51:     return
  // 52:   dec &n
  frame->slots[4] /* temp__1 */ = create_closure(entry__10_4, 0);
  // 48: while -> n > 0:
  // 49:   if resource_id_of(resources(n)) == resource_id:
  // 50:     delete_at &resources n
  // 51:     return
  // 52:   dec &n
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__while();
  func = myself->type;
  frame->cont = cont__10_14;
}
static void entry__10_6(void) {
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
  // 49: ... resources(n)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* n */;
  result_count = 1;
  myself = var._resources;
  func = myself->type;
  frame->cont = cont__10_7;
}
static void cont__10_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 49: ... resource_id_of(resources(n))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = var._resource_id_of;
  func = myself->type;
  frame->cont = cont__10_8;
}
static void cont__10_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 49: ... resource_id_of(resources(n)) == resource_id
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[1] /* resource_id */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__10_9;
}
static void cont__10_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 49: ... :
  // 50:   delete_at &resources n
  // 51:   return
  frame->slots[6] /* temp__4 */ = create_closure(entry__10_10, 0);
  // 49: if resource_id_of(resources(n)) == resource_id:
  // 50:   delete_at &resources n
  // 51:   return
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__10_12;
}
static void entry__10_10(void) {
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
  // 50: delete_at &resources n
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._resources;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* n */;
  result_count = 1;
  myself = get__delete_at();
  func = myself->type;
  frame->cont = cont__10_11;
}
static void cont__10_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._resources = arguments->slots[0];
  // 51: return
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__10_12(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 52: dec &n
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* n */;
  result_count = 1;
  myself = get__dec();
  func = myself->type;
  frame->cont = cont__10_13;
}
static void cont__10_13(void) {
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
static void entry__10_4(void) {
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
  // 48: ... n > 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* n */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__10_5;
}
static void cont__10_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 48: ... :
  // 49:   if resource_id_of(resources(n)) == resource_id:
  // 50:     delete_at &resources n
  // 51:     return
  // 52:   dec &n
  frame->slots[4] /* temp__2 */ = create_closure(entry__10_6, 0);
  // 48: ... -> n > 0:
  // 49:   if resource_id_of(resources(n)) == resource_id:
  // 50:     delete_at &resources n
  // 51:     return
  // 52:   dec &n
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__10_14(void) {
  myself = frame->slots[1] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__11_26(void) {
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
  // 82: $resource resources(i)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* i */;
  result_count = 1;
  myself = var._resources;
  func = myself->type;
  frame->cont = cont__11_27;
}
static void cont__11_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* resource */, arguments->slots[0]);
  // 83: delete_at &resources i
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._resources;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* i */;
  result_count = 1;
  myself = get__delete_at();
  func = myself->type;
  frame->cont = cont__11_28;
}
static void cont__11_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._resources = arguments->slots[0];
  // 84: close resource
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* resource */;
  result_count = 0;
  myself = get__close();
  func = myself->type;
  frame->cont = cont__11_29;
}
static void cont__11_29(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 85: repeat_me
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* repeat_me */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__11_2(void) {
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
  // 73: $$i length_of(resources)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._resources;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__11_3;
}
static void cont__11_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* i */ = arguments->slots[0];
  // 74: ... : (-> break)
  // 75:   while -> i > 0 && resource_id_of(resources(i)) >= id:
  // 76:     $resource resources(i)
  // 77:     if
  // 78:       retain_id_of(resource).is_undefined || retain_id_of(resource) > id
  // 79:       break
  // 80:     dec &i
  frame->slots[3] /* temp__1 */ = create_closure(entry__11_4, 0);
  // 74: do: (-> break)
  // 75:   while -> i > 0 && resource_id_of(resources(i)) >= id:
  // 76:     $resource resources(i)
  // 77:     if
  // 78:       retain_id_of(resource).is_undefined || retain_id_of(resource) > id
  // 79:       break
  // 80:     dec &i
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = 0;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__11_24;
}
static void entry__11_4(void) {
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
  // 75: ... -> i > 0 && resource_id_of(resources(i)) >= id:
  // 76:   $resource resources(i)
  // 77:   if
  // 78:     retain_id_of(resource).is_undefined || retain_id_of(resource) > id
  // 79:     break
  // 80:   dec &i
  frame->slots[3] /* temp__1 */ = create_closure(entry__11_5, 0);
  // 75: while -> i > 0 && resource_id_of(resources(i)) >= id:
  // 76:   $resource resources(i)
  // 77:   if
  // 78:     retain_id_of(resource).is_undefined || retain_id_of(resource) > id
  // 79:     break
  // 80:   dec &i
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__while();
  func = myself->type;
  frame->cont = cont__11_23;
}
static void entry__11_13(void) {
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
  // 76: $resource resources(i)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* i */;
  result_count = 1;
  myself = var._resources;
  func = myself->type;
  frame->cont = cont__11_14;
}
static void cont__11_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* resource */, arguments->slots[0]);
  // 78: retain_id_of(resource)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* resource */;
  result_count = 1;
  myself = var._retain_id_of;
  func = myself->type;
  frame->cont = cont__11_15;
}
static void cont__11_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 78: retain_id_of(resource).is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__3 */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__11_16;
}
static void cont__11_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 78: ... retain_id_of(resource) > id
  frame->slots[7] /* temp__4 */ = create_closure(entry__11_17, 0);
  // 78: retain_id_of(resource).is_undefined || retain_id_of(resource) > id
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__4 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__11_20;
}
static void entry__11_17(void) {
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
  // 78: ... retain_id_of(resource)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* resource */;
  result_count = 1;
  myself = var._retain_id_of;
  func = myself->type;
  frame->cont = cont__11_18;
}
static void cont__11_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 78: ... retain_id_of(resource) > id
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* id */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__11_19;
}
static void cont__11_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 78: ... retain_id_of(resource) > id
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__11_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 77: if
  // 78:   retain_id_of(resource).is_undefined || retain_id_of(resource) > id
  // 79:   break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* break */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__11_21;
}
static void cont__11_21(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 80: dec &i
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* i */;
  result_count = 1;
  myself = get__dec();
  func = myself->type;
  frame->cont = cont__11_22;
}
static void cont__11_22(void) {
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
static void entry__11_5(void) {
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
  // 75: ... i > 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* i */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__11_6;
}
static void cont__11_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 75: ... resource_id_of(resources(i)) >= id
  frame->slots[5] /* temp__3 */ = create_closure(entry__11_7, 0);
  // 75: ... i > 0 && resource_id_of(resources(i)) >= id
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__11_12;
}
static void entry__11_7(void) {
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
  // 75: ... resources(i)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* i */;
  result_count = 1;
  myself = var._resources;
  func = myself->type;
  frame->cont = cont__11_8;
}
static void cont__11_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__4 */ = arguments->slots[0];
  // 75: ... resource_id_of(resources(i))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__4 */;
  result_count = 1;
  myself = var._resource_id_of;
  func = myself->type;
  frame->cont = cont__11_9;
}
static void cont__11_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 75: ... resource_id_of(resources(i)) >= id
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  arguments->slots[1] = frame->slots[1] /* id */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__11_10;
}
static void cont__11_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 75: ... resource_id_of(resources(i)) >= id
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__11_11;
}
static void cont__11_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 75: ... resource_id_of(resources(i)) >= id
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__11_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 75: ... :
  // 76:   $resource resources(i)
  // 77:   if
  // 78:     retain_id_of(resource).is_undefined || retain_id_of(resource) > id
  // 79:     break
  // 80:   dec &i
  frame->slots[6] /* temp__4 */ = create_closure(entry__11_13, 0);
  // 75: ... -> i > 0 && resource_id_of(resources(i)) >= id:
  // 76:   $resource resources(i)
  // 77:   if
  // 78:     retain_id_of(resource).is_undefined || retain_id_of(resource) > id
  // 79:     break
  // 80:   dec &i
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__4 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__11_23(void) {
  myself = frame->slots[0] /* break */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__11_24(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 81: ... i > 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* i */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__11_25;
}
static void cont__11_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 81: ... :
  // 82:   $resource resources(i)
  // 83:   delete_at &resources i
  // 84:   close resource
  // 85:   repeat_me
  frame->slots[4] /* temp__2 */ = create_closure(entry__11_26, 0);
  // 81: if i > 0:
  // 82:   $resource resources(i)
  // 83:   delete_at &resources i
  // 84:   close resource
  // 85:   repeat_me
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__11_1_cleanup_till(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // id: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 72: ... : (repeat_me^)
  // 73:   $$i length_of(resources)
  // 74:   do: (-> break)
  // 75:     while -> i > 0 && resource_id_of(resources(i)) >= id:
  // 76:       $resource resources(i)
  // 77:       if
  // 78:         retain_id_of(resource).is_undefined || retain_id_of(resource) > id
  // 79:         break
  // 80:       dec &i
  // 81:   if i > 0:
  // ...
  frame->slots[1] /* temp__1 */ = create_closure(entry__11_2, 0);
  // 72: do: (repeat_me^)
  // 73:   $$i length_of(resources)
  // 74:   do: (-> break)
  // 75:     while -> i > 0 && resource_id_of(resources(i)) >= id:
  // 76:       $resource resources(i)
  // 77:       if
  // 78:         retain_id_of(resource).is_undefined || retain_id_of(resource) > id
  // 79:         break
  // 80:       dec &i
  // 81:   if i > 0:
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__do();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__12_5(void) {
  allocate_initialized_frame_gc(0, 2);
  // slot allocations:
  // resource: 0
  frame->slots[0] /* resource */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 89: pop &resources $resource
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._resources;
  result_count = 2;
  myself = get__pop();
  func = myself->type;
  frame->cont = cont__12_6;
}
static void cont__12_6(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  var._resources = arguments->slots[0];
  frame->slots[1] /* temp__1 */ = arguments->slots[1];
  // 89: ... resource
  initialize_future(frame->slots[0] /* resource */, frame->slots[1] /* temp__1 */);
  // 90: close resource
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* resource */;
  result_count = frame->caller_result_count;
  myself = get__close();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__12_2(void) {
  allocate_initialized_frame_gc(0, 2);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 88: ... resources.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._resources;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__12_3;
}
static void cont__12_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 88: ... not(resources.is_empty)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = get__not();
  func = myself->type;
  frame->cont = cont__12_4;
}
static void cont__12_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 88: ... -> not(resources.is_empty):
  // 89:   pop &resources $resource
  // 90:   close resource
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = func__12_5;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__12_1_cleanup(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 88: while -> not(resources.is_empty):
  // 89:   pop &resources $resource
  // 90:   close resource
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__12_2;
  result_count = frame->caller_result_count;
  myself = get__while();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__13_1_clib_exit(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  terminate(to_int(arguments->slots[0]));
}
static void entry__15_1_std__at_exit(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // func: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 100: ... push &exit_functions func
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._exit_functions;
  arguments->slots[1] = frame->slots[0] /* func */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__15_2;
}
static void cont__15_2(void) {
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
static void entry__16_1_std__exit(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // status: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 103: for_each exit_functions: (func) func
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._exit_functions;
  arguments->slots[1] = func__16_2;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__16_3;
}
static void entry__16_2(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // func: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 103: ... func
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* func */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__16_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 104: cleanup
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = var._cleanup;
  func = myself->type;
  frame->cont = cont__16_4;
}
static void cont__16_4(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 105: clib_exit status
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* status */;
  result_count = frame->caller_result_count;
  myself = var._clib_exit;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__17_1_std__terminate(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 107: ... exit 0
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__0;
  result_count = frame->caller_result_count;
  myself = get__exit();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__18_1_std__ErrorMessage(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // args: 0
  // msg: 1
  frame->slots[1] /* msg */ = create_cell();
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 110: $$msg string(args*)
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[0] /* args */);
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__18_2;
}
static void cont__18_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* msg */ = arguments->slots[0];
  // 111: ... msg .has_suffix. '@nl;'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* msg */;
  arguments->slots[1] = character__10;
  result_count = 1;
  myself = get__has_suffix();
  func = myself->type;
  frame->cont = cont__18_3;
}
static void cont__18_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 111: ... : push &msg '@nl;'
  frame->slots[3] /* temp__2 */ = create_closure(entry__18_4, 0);
  // 111: unless msg .has_suffix. '@nl;': push &msg '@nl;'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__18_6;
}
static void entry__18_4(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // msg: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* msg */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 111: ... push &msg '@nl;'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* msg */;
  arguments->slots[1] = character__10;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__18_5;
}
static void cont__18_5(void) {
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
static void cont__18_6(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 112: flush STDOUT_FILENO
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__STDOUT_FILENO();
  result_count = 0;
  myself = get__flush();
  func = myself->type;
  frame->cont = cont__18_7;
}
static void cont__18_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 113: ewrite msg
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* msg */;
  result_count = frame->caller_result_count;
  myself = get__ewrite();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__19_1_std__Error(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // args: 0
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 116: cleanup
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = var._cleanup;
  func = myself->type;
  frame->cont = cont__19_2;
}
static void cont__19_2(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 117: ErrorMessage args*
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[0] /* args */);
  result_count = 0;
  myself = get__ErrorMessage();
  func = myself->type;
  frame->cont = cont__19_3;
}
static void cont__19_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 118: exit 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = frame->caller_result_count;
  myself = get__exit();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__20_1_crash_dump(void) {
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
static void entry__21_3(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // args: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* args */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 131: ewrite "RUNTIME ERROR: "
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__21_4;
  result_count = 0;
  myself = get__ewrite();
  func = myself->type;
  frame->cont = cont__21_5;
}
static void cont__21_5(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 132: ErrorMessage args*
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[0] /* args */);
  result_count = 0;
  myself = get__ErrorMessage();
  func = myself->type;
  frame->cont = cont__21_6;
}
static void cont__21_6(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 133: crash_dump
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = var._crash_dump;
  func = myself->type;
  frame->cont = cont__21_7;
}
static void cont__21_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 134: exit 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = frame->caller_result_count;
  myself = get__exit();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__21_8(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 136: exit 2
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = frame->caller_result_count;
  myself = get__exit();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__21_1_RuntimeError(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // args: 0
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 128: cleanup
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = var._cleanup;
  func = myself->type;
  frame->cont = cont__21_2;
}
static void cont__21_2(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 130: :
  // 131:   ewrite "RUNTIME ERROR: "
  // 132:   ErrorMessage args*
  // 133:   crash_dump
  // 134:   exit 1
  frame->slots[1] /* temp__1 */ = create_closure(entry__21_3, 0);
  // 129: try
  // 130:   :
  // 131:     ewrite "RUNTIME ERROR: "
  // 132:     ErrorMessage args*
  // 133:     crash_dump
  // 134:     exit 1
  // 135:   :
  // 136:     exit 2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = func__21_8;
  result_count = frame->caller_result_count;
  myself = get__try();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__23_1_std__try(void) {
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
  // 145: $outer_raise raise
  initialize_maybe_future(frame->slots[2] /* outer_raise */, get__raise());
  // 146: ... :
  // 147:   %raise: (args*)
  // 148:     $handler if(bodies.is_empty (-> outer_raise) -> get(&bodies))
  // 149:     if
  // 150:       parameter_count_of(handler) == 0:
  // 151:         handler
  // 152:         return
  // 153:       :
  // 154:         handler args*
  // 155:         return
  // ...
  frame->slots[3] /* temp__1 */ = create_closure(entry__23_2, 0);
  // 146: do:
  // 147:   %raise: (args*)
  // 148:     $handler if(bodies.is_empty (-> outer_raise) -> get(&bodies))
  // 149:     if
  // 150:       parameter_count_of(handler) == 0:
  // 151:         handler
  // 152:         return
  // 153:       :
  // 154:         handler args*
  // 155:         return
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__23_22;
}
static void entry__23_2(void) {
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
  // 147: ... : (args*)
  // 148:   $handler if(bodies.is_empty (-> outer_raise) -> get(&bodies))
  // 149:   if
  // 150:     parameter_count_of(handler) == 0:
  // 151:       handler
  // 152:       return
  // 153:     :
  // 154:       handler args*
  // 155:       return
  frame->slots[5] /* temp__1 */ = create_closure(entry__23_3_raise, -1);
  // 147: %raise: (args*)
  // 148:   $handler if(bodies.is_empty (-> outer_raise) -> get(&bodies))
  // 149:   if
  // 150:     parameter_count_of(handler) == 0:
  // 151:       handler
  // 152:       return
  // 153:     :
  // 154:       handler args*
  // 155:       return
  initialize_future(get__raise(), frame->slots[5] /* temp__1 */);
  // 157: $body get(&bodies)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* bodies */;
  result_count = 2;
  myself = get__get();
  func = myself->type;
  frame->cont = cont__23_15;
}
static void entry__23_11(void) {
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
  // 151: handler
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = frame->slots[0] /* handler */;
  func = myself->type;
  frame->cont = cont__23_12;
}
static void cont__23_12(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 152: return
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__23_13(void) {
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
  // 154: handler args*
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[1] /* args */);
  result_count = 0;
  myself = frame->slots[0] /* handler */;
  func = myself->type;
  frame->cont = cont__23_14;
}
static void cont__23_14(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 155: return
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__23_3_raise(void) {
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
  // 148: ... bodies.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* bodies */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__23_4;
}
static void cont__23_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 148: ... -> outer_raise
  frame->slots[6] /* temp__2 */ = create_closure(entry__23_5, 0);
  // 148: ... -> get(&bodies)
  frame->slots[7] /* temp__3 */ = create_closure(entry__23_6, 0);
  // 148: $handler if(bodies.is_empty (-> outer_raise) -> get(&bodies))
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  arguments->slots[2] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__23_8;
}
static void entry__23_5(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // outer_raise: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* outer_raise */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 148: ... -> outer_raise
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* outer_raise */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__23_6(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // bodies: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* bodies */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 148: ... get(&bodies)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* bodies */;
  result_count = 2;
  myself = get__get();
  func = myself->type;
  frame->cont = cont__23_7;
}
static void cont__23_7(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* bodies */ = arguments->slots[0];
  frame->slots[1] /* temp__1 */ = arguments->slots[1];
  // 148: ... -> get(&bodies)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__23_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* handler */, arguments->slots[0]);
  // 150: parameter_count_of(handler)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* handler */;
  result_count = 1;
  myself = get__parameter_count_of();
  func = myself->type;
  frame->cont = cont__23_9;
}
static void cont__23_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 150: parameter_count_of(handler) == 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__23_10;
}
static void cont__23_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 150: ... :
  // 151:   handler
  // 152:   return
  frame->slots[7] /* temp__3 */ = create_closure(entry__23_11, 0);
  // 153: :
  // 154:   handler args*
  // 155:   return
  frame->slots[8] /* temp__4 */ = create_closure(entry__23_13, 0);
  // 149: if
  // 150:   parameter_count_of(handler) == 0:
  // 151:     handler
  // 152:     return
  // 153:   :
  // 154:     handler args*
  // 155:     return
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
static void cont__23_15(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* bodies */ = arguments->slots[0];
  frame->slots[5] /* temp__1 */ = arguments->slots[1];
  // 157: ... body
  initialize_future(frame->slots[4] /* body */, frame->slots[5] /* temp__1 */);
  // 158: ... bodies.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* bodies */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__23_16;
}
static void cont__23_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 158: ... : push &bodies: (_args*) pass
  frame->slots[6] /* temp__2 */ = create_closure(entry__23_17, 0);
  // 158: if bodies.is_empty: push &bodies: (_args*) pass
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__23_20;
}
static void entry__23_17(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // bodies: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* bodies */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 158: ... push &bodies: (_args*) pass
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* bodies */;
  arguments->slots[1] = func__23_18;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__23_19;
}
static void entry__23_18(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // args: 0
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 158: ... pass
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = get__pass();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__23_19(void) {
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
static void cont__23_20(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 159: body
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[4] /* body */;
  func = myself->type;
  frame->cont = cont__23_21;
}
static void cont__23_21(void) {
  myself = frame->slots[0] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__23_22(void) {
  myself = frame->slots[1] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__24_1_std__transaction(void) {
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
  // 162: inc &next_resource_id # prevent that two transactions have the same id
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._next_resource_id;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__24_2;
}
static void cont__24_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._next_resource_id = arguments->slots[0];
  // 163: $first_id next_resource_id
  initialize_future(frame->slots[2] /* first_id */, var._next_resource_id);
  // 164: %first_resource_id first_id
  initialize_maybe_future(get__first_resource_id(), frame->slots[2] /* first_id */);
  // 165: ... : (args*)
  // 166:   cleanup_till first_id
  // 167:   raise args*
  frame->slots[3] /* temp__1 */ = create_closure(entry__24_3, -1);
  // 165: try body: (args*)
  // 166:   cleanup_till first_id
  // 167:   raise args*
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* body */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__try();
  func = myself->type;
  frame->cont = cont__24_5;
}
static void entry__24_3(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // args: 0
  // first_id: 1
  frame->slots[1] = myself->closure.frame->slots[2]; /* first_id */
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 166: cleanup_till first_id
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* first_id */;
  result_count = 0;
  myself = var._cleanup_till;
  func = myself->type;
  frame->cont = cont__24_4;
}
static void cont__24_4(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 167: raise args*
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[0] /* args */);
  result_count = frame->caller_result_count;
  myself = get__raise();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__24_5(void) {
  myself = frame->slots[1] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__25_38(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // s: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* s */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 186: !resources(s).retain_id_of first_resource_id
  frame->slots[1] /* temp__1 */ = get__first_resource_id();
  // 186: ... resources(s)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* s */;
  result_count = 1;
  myself = var._resources;
  func = myself->type;
  frame->cont = cont__25_39;
}
static void cont__25_39(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 186: !resources(s).retain_id_of
  {
    NODE *temp = clone_object_and_attributes(frame->slots[2] /* temp__2 */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__retain_id_of, frame->slots[1] /* temp__1 */);
    frame->slots[2] /* temp__2 */ = temp;

  }
  // 186: !resources(s)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* s */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = var._resources;
  func = myself->type;
  frame->cont = cont__25_40;
}
static void cont__25_40(void) {
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
static void entry__25_1_std__retain(void) {
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
  // 170: ... first_resource_id.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__first_resource_id();
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__25_2;
}
static void cont__25_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 170: if first_resource_id.is_undefined:
  // 171:   raise "Attempt to retain a resource outside a transaction!"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = func__25_3;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__25_5;
}
static void entry__25_3(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 171: raise "Attempt to retain a resource outside a transaction!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__25_4;
  result_count = frame->caller_result_count;
  myself = get__raise();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__25_5(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 172: $id resource_id_of(resource)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* resource */;
  result_count = 1;
  myself = var._resource_id_of;
  func = myself->type;
  frame->cont = cont__25_6;
}
static void cont__25_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* id */, arguments->slots[0]);
  // 173: $$s 1
  ((CELL *)frame->slots[2])->contents /* s */ = number__1;
  // 174: $$e length_of(resources)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._resources;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__25_7;
}
static void cont__25_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* e */ = arguments->slots[0];
  // 175: ... -> e > s:
  // 176:   $i s+e+1 .div. 2
  // 177:   if
  // 178:     id >= resource_id_of(resources(i)):
  // 179:       !s i
  // 180:     :
  // 181:       !e i-i
  frame->slots[5] /* temp__1 */ = create_closure(entry__25_8, 0);
  // 175: while -> e > s:
  // 176:   $i s+e+1 .div. 2
  // 177:   if
  // 178:     id >= resource_id_of(resources(i)):
  // 179:       !s i
  // 180:     :
  // 181:       !e i-i
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  result_count = 0;
  myself = get__while();
  func = myself->type;
  frame->cont = cont__25_21;
}
static void entry__25_18(void) {
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
  // 179: !s i
  ((CELL *)frame->slots[0])->contents /* s */ = frame->slots[1] /* i */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__25_19(void) {
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
  // 181: !e i-i
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* i */;
  arguments->slots[1] = frame->slots[1] /* i */;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__25_20;
}
static void cont__25_20(void) {
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
static void entry__25_10(void) {
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
  // 176: ... s+e
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* s */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* e */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__25_11;
}
static void cont__25_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 176: ... s+e+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__25_12;
}
static void cont__25_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 176: $i s+e+1 .div. 2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__div();
  func = myself->type;
  frame->cont = cont__25_13;
}
static void cont__25_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* i */, arguments->slots[0]);
  // 178: ... resources(i)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* i */;
  result_count = 1;
  myself = var._resources;
  func = myself->type;
  frame->cont = cont__25_14;
}
static void cont__25_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__4 */ = arguments->slots[0];
  // 178: ... resource_id_of(resources(i))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__4 */;
  result_count = 1;
  myself = var._resource_id_of;
  func = myself->type;
  frame->cont = cont__25_15;
}
static void cont__25_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 178: id >= resource_id_of(resources(i))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* id */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__25_16;
}
static void cont__25_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 178: id >= resource_id_of(resources(i))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__25_17;
}
static void cont__25_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 178: ... :
  // 179:   !s i
  frame->slots[8] /* temp__5 */ = create_closure(entry__25_18, 0);
  // 180: :
  // 181:   !e i-i
  frame->slots[9] /* temp__6 */ = create_closure(entry__25_19, 0);
  // 177: if
  // 178:   id >= resource_id_of(resources(i)):
  // 179:     !s i
  // 180:   :
  // 181:     !e i-i
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
static void entry__25_8(void) {
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
  // 175: ... e > s
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* s */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* e */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__25_9;
}
static void cont__25_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 175: ... :
  // 176:   $i s+e+1 .div. 2
  // 177:   if
  // 178:     id >= resource_id_of(resources(i)):
  // 179:       !s i
  // 180:     :
  // 181:       !e i-i
  frame->slots[4] /* temp__2 */ = create_closure(entry__25_10, 0);
  // 175: ... -> e > s:
  // 176:   $i s+e+1 .div. 2
  // 177:   if
  // 178:     id >= resource_id_of(resources(i)):
  // 179:       !s i
  // 180:     :
  // 181:       !e i-i
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__25_21(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 182: ... e == 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* e */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__25_22;
}
static void cont__25_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 182: ... resource_id_of(resources(s)) != id
  frame->slots[7] /* temp__3 */ = create_closure(entry__25_23, 0);
  // 182: ... e == 0 || resource_id_of(resources(s)) != id
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__25_28;
}
static void entry__25_23(void) {
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
  // 182: ... resources(s)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* s */;
  result_count = 1;
  myself = var._resources;
  func = myself->type;
  frame->cont = cont__25_24;
}
static void cont__25_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__4 */ = arguments->slots[0];
  // 182: ... resource_id_of(resources(s))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__4 */;
  result_count = 1;
  myself = var._resource_id_of;
  func = myself->type;
  frame->cont = cont__25_25;
}
static void cont__25_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 182: ... resource_id_of(resources(s)) != id
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  arguments->slots[1] = frame->slots[1] /* id */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__25_26;
}
static void cont__25_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 182: ... resource_id_of(resources(s)) != id
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__25_27;
}
static void cont__25_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 182: ... resource_id_of(resources(s)) != id
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__25_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 182: if e == 0 || resource_id_of(resources(s)) != id:
  // 183:   raise "Attempt to retain an nonexistant resource!"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = func__25_29;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__25_31;
}
static void entry__25_29(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 183: raise "Attempt to retain an nonexistant resource!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__25_30;
  result_count = frame->caller_result_count;
  myself = get__raise();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__25_31(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 184: ... resources(s)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* s */;
  result_count = 1;
  myself = var._resources;
  func = myself->type;
  frame->cont = cont__25_32;
}
static void cont__25_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 184: $retain_id retain_id_of(resources(s))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  result_count = 1;
  myself = var._retain_id_of;
  func = myself->type;
  frame->cont = cont__25_33;
}
static void cont__25_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* retain_id */, arguments->slots[0]);
  // 185: ... retain_id.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* retain_id */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__25_34;
}
static void cont__25_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 185: ... first_resource_id < retain_id
  frame->slots[7] /* temp__3 */ = create_closure(entry__25_35, 0);
  // 185: ... retain_id.is_undefined || first_resource_id < retain_id
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__25_37;
}
static void entry__25_35(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // retain_id: 0
  frame->slots[0] = myself->closure.frame->slots[4]; /* retain_id */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 185: ... first_resource_id < retain_id
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__first_resource_id();
  arguments->slots[1] = frame->slots[0] /* retain_id */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__25_36;
}
static void cont__25_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 185: ... first_resource_id < retain_id
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__25_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 185: ... :
  // 186:   !resources(s).retain_id_of first_resource_id
  frame->slots[8] /* temp__4 */ = create_closure(entry__25_38, 0);
  // 185: if retain_id.is_undefined || first_resource_id < retain_id:
  // 186:   !resources(s).retain_id_of first_resource_id
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
  var.std__CLEANUP = collect_node(var.std__CLEANUP);
  var.std__ERROR_MESSAGE = collect_node(var.std__ERROR_MESSAGE);
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
  unique__std__CLEANUP = register_unique_item("std__CLEANUP");
  unique__std__ERROR_MESSAGE = register_unique_item("std__ERROR_MESSAGE");
  func__9_1_std__register_resource = create_function(entry__9_1_std__register_resource, 1);
  func__10_1_std__deregister_resource = create_function(entry__10_1_std__deregister_resource, 1);
  func__11_1_cleanup_till = create_function(entry__11_1_cleanup_till, 1);
  func__12_5 = create_function(entry__12_5, 0);
  func__12_2 = create_function(entry__12_2, 0);
  func__12_1_cleanup = create_function(entry__12_1_cleanup, 0);
  func__13_1_clib_exit = create_function(entry__13_1_clib_exit, 1);
  func__15_1_std__at_exit = create_function(entry__15_1_std__at_exit, 1);
  func__16_2 = create_function(entry__16_2, 1);
  func__16_1_std__exit = create_function(entry__16_1_std__exit, 1);
  func__17_1_std__terminate = create_function(entry__17_1_std__terminate, 0);
  func__18_1_std__ErrorMessage = create_function(entry__18_1_std__ErrorMessage, -1);
  func__19_1_std__Error = create_function(entry__19_1_std__Error, -1);
  func__20_1_crash_dump = create_function(entry__20_1_crash_dump, 0);
  string__21_4 = from_latin_1_string("RUNTIME ERROR: ", 15);
  func__21_8 = create_function(entry__21_8, 0);
  func__21_1_RuntimeError = create_function(entry__21_1_RuntimeError, -1);
  func__23_18 = create_function(entry__23_18, -1);
  func__23_1_std__try = create_function(entry__23_1_std__try, -1);
  func__24_1_std__transaction = create_function(entry__24_1_std__transaction, 1);
  string__25_4 = from_latin_1_string("Attempt to retain a resource outside a transaction!", 51);
  func__25_3 = create_function(entry__25_3, 0);
  string__25_30 = from_latin_1_string("Attempt to retain an nonexistant resource!", 42);
  func__25_29 = create_function(entry__25_29, 0);
  func__25_1_std__retain = create_function(entry__25_1_std__retain, 1);
}

static int already_run_phase_3 = false;

EXPORT void phase_3__basic__exceptions(void) {
  if (already_run_phase_3) return;
  already_run_phase_3 = true;
  set_module("basic__exceptions");
  set_used_namespaces(used_namespaces);
  assign_value(&var.std__CLEANUP, unique__std__CLEANUP);
  define_single_assign_static("std", "CLEANUP", get__std__CLEANUP, &var.std__CLEANUP);
  assign_value(&var.std__ERROR_MESSAGE, unique__std__ERROR_MESSAGE);
  define_single_assign_static("std", "ERROR_MESSAGE", get__std__ERROR_MESSAGE, &var.std__ERROR_MESSAGE);
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
  assign_variable(&var.std__register_resource, &func__9_1_std__register_resource);
  assign_variable(&var.std__deregister_resource, &func__10_1_std__deregister_resource);
  assign_variable(&var._cleanup_till, &func__11_1_cleanup_till);
  assign_variable(&var._cleanup, &func__12_1_cleanup);
  assign_variable(&var._clib_exit, &func__13_1_clib_exit);
  assign_variable(&var.std__at_exit, &func__15_1_std__at_exit);
  assign_variable(&var.std__exit, &func__16_1_std__exit);
  assign_variable(&var.std__terminate, &func__17_1_std__terminate);
  assign_variable(&var.std__ErrorMessage, &func__18_1_std__ErrorMessage);
  assign_variable(&var.std__Error, &func__19_1_std__Error);
  assign_variable(&var._crash_dump, &func__20_1_crash_dump);
  assign_variable(&var._RuntimeError, &func__21_1_RuntimeError);
  initialize_future(get__std__raise(), var._RuntimeError);
  assign_variable(&var.std__try, &func__23_1_std__try);
  assign_variable(&var.std__transaction, &func__24_1_std__transaction);
  assign_variable(&var.std__retain, &func__25_1_std__retain);
}

static int already_run_phase_6 = false;

EXPORT void phase_6__basic__exceptions(void) {
  if (already_run_phase_6) return;
  already_run_phase_6 = true;
  register_collector(collect__basic__exceptions);
}
