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
typedef void (*NODE_SETTER)(NODE *);
typedef struct FRAME_INFO {
  int var_count;
  const char *var_names[];
} FRAME_INFO;
IMPORT int child_changed_state;
IMPORT int window_changed_size;
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
IMPORT void initialize_maybe_future(NODE *var, NODE *val);
IMPORT NODE *undefined;
IMPORT int result_count;
IMPORT void invalid_results_error(void);
IMPORT NODE *create_closure(FUNC type, int par_count);
IMPORT NODE *create_continuation(void);
typedef struct CELL {
  FUNC type;
  struct ATTRIBUTES *attributes;
  NODE *contents;
} CELL;
IMPORT NODE *create_cell(void);
IMPORT NODE *create_future(void);
IMPORT void initialize_future(NODE *var, NODE *val);
IMPORT void terminate(int exit_code);
IMPORT void allocate_arguments(void);
IMPORT NODE *from_arguments(int first_idx, int count);
IMPORT NODE *collect_node(NODE *node);
IMPORT void register_module_info(MODULE_INFO *info);
IMPORT void define_polymorphic_function_with_setter(
  const char *namespace, const char *name, NODE_GETTER getter, int *id_p,
  NODE **var_p
);
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
IMPORT void define_multi_assign_static(
  const char *namespace, const char *name,
  NODE_GETTER getter, NODE_SETTER setter
);
IMPORT void use_read_only(
  const char *namespace, const char *name,
  NODE_GETTER *getter, NODE_GETTER *get_value_or_future
);
IMPORT void use_read_write(
  const char *namespace, const char *name,
  NODE_GETTER *getter, NODE_SETTER *setter
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
static NODE_GETTER get__READ_FROM;
static NODE_GETTER get_value_or_future__READ_FROM;
static NODE_GETTER get__SCREEN_SIZE_CHANGE;
static NODE_GETTER get_value_or_future__SCREEN_SIZE_CHANGE;
static NODE_GETTER get__STDIN_FILENO;
static NODE_GETTER get_value_or_future__STDIN_FILENO;
static NODE_GETTER get__TERMINATED;
static NODE_GETTER get_value_or_future__TERMINATED;
static NODE_GETTER get__TIMEOUT;
static NODE_GETTER get_value_or_future__TIMEOUT;
static NODE_GETTER get__WRITE_TO;
static NODE_GETTER get_value_or_future__WRITE_TO;
static NODE_GETTER get__append;
static NODE_GETTER get_value_or_future__append;
static NODE_GETTER get__case;
static NODE_GETTER get_value_or_future__case;
static NODE_GETTER get__close;
static NODE_GETTER get_value_or_future__close;
static NODE_GETTER get__create_event;
static NODE_GETTER get_value_or_future__create_event;
static NODE_GETTER get__delete_at;
static NODE_GETTER get_value_or_future__delete_at;
static NODE_GETTER get__do;
static NODE_GETTER get_value_or_future__do;
static NODE_GETTER get__empty_key_order_table;
static NODE_GETTER get_value_or_future__empty_key_order_table;
static NODE_GETTER get__empty_list;
static NODE_GETTER get_value_or_future__empty_list;
static NODE_GETTER get__empty_set;
static NODE_GETTER get_value_or_future__empty_set;
static NODE_GETTER get__events;
static NODE_SETTER set__events;
static NODE_GETTER get__false;
static NODE_GETTER get_value_or_future__false;
static int poly_idx__file_descriptor_of;
static NODE_GETTER get__file_descriptor_of;
static NODE_GETTER get__for_each;
static NODE_GETTER get_value_or_future__for_each;
static NODE_GETTER get__forever;
static NODE_GETTER get_value_or_future__forever;
static NODE_GETTER get__get;
static NODE_GETTER get_value_or_future__get;
static NODE_GETTER get__get_terminal_size;
static NODE_GETTER get_value_or_future__get_terminal_size;
static int poly_idx__height_of;
static NODE_GETTER get__height_of;
static NODE_GETTER get__if;
static NODE_GETTER get_value_or_future__if;
static NODE_GETTER get__inc;
static NODE_GETTER get_value_or_future__inc;
static NODE_GETTER get__is_defined;
static NODE_GETTER get_value_or_future__is_defined;
static NODE_GETTER get__is_empty;
static NODE_GETTER get_value_or_future__is_empty;
static NODE_GETTER get__key_of;
static NODE_GETTER get_value_or_future__key_of;
static NODE_GETTER get__length_of;
static NODE_GETTER get_value_or_future__length_of;
static NODE_GETTER get__no_longer_want_to_read_from;
static NODE_GETTER get_value_or_future__no_longer_want_to_read_from;
static NODE_GETTER get__no_longer_want_to_write_to;
static NODE_GETTER get_value_or_future__no_longer_want_to_write_to;
static NODE_GETTER get__parameter_count_of;
static NODE_GETTER get_value_or_future__parameter_count_of;
static int poly_idx__pid_of;
static NODE_GETTER get__pid_of;
static NODE_GETTER get__process_events;
static NODE_GETTER get_value_or_future__process_events;
static NODE_GETTER get__push;
static NODE_GETTER get_value_or_future__push;
static NODE_GETTER get__put;
static NODE_GETTER get_value_or_future__put;
static NODE_GETTER get__raise;
static NODE_GETTER get_value_or_future__raise;
static NODE_GETTER get__range;
static NODE_GETTER get_value_or_future__range;
static int poly_idx__status_of;
static NODE_GETTER get__status_of;
static NODE_GETTER get__std__and;
static NODE_GETTER get_value_or_future__std__and;
static NODE_GETTER get__std__equal;
static NODE_GETTER get_value_or_future__std__equal;
static NODE_GETTER get__std__less;
static NODE_GETTER get_value_or_future__std__less;
static NODE_GETTER get__std__minus;
static NODE_GETTER get_value_or_future__std__minus;
static NODE_GETTER get__std__negate;
static NODE_GETTER get_value_or_future__std__negate;
static NODE_GETTER get__std__not;
static NODE_GETTER get_value_or_future__std__not;
static NODE_GETTER get__std__plus;
static NODE_GETTER get_value_or_future__std__plus;
static NODE_GETTER get__std__sequence;
static NODE_GETTER get_value_or_future__std__sequence;
static NODE_GETTER get__terminate;
static NODE_GETTER get_value_or_future__terminate;
static NODE_GETTER get__true;
static NODE_GETTER get_value_or_future__true;
static int poly_idx__type_of;
static NODE_GETTER get__type_of;
static NODE_GETTER get__types__object;
static NODE_GETTER get_value_or_future__types__object;
static NODE_GETTER get__undefined;
static NODE_GETTER get_value_or_future__undefined;
static NODE_GETTER get__value_of;
static NODE_GETTER get_value_or_future__value_of;
static NODE_GETTER get__wait_for_io;
static NODE_GETTER get_value_or_future__wait_for_io;
static NODE_GETTER get__wait_pid;
static NODE_GETTER get_value_or_future__wait_pid;
static NODE_GETTER get__want_to_read_from;
static NODE_GETTER get_value_or_future__want_to_read_from;
static NODE_GETTER get__want_to_write_to;
static NODE_GETTER get_value_or_future__want_to_write_to;
static NODE_GETTER get__while;
static NODE_GETTER get_value_or_future__while;
static int poly_idx__width_of;
static NODE_GETTER get__width_of;
static struct {
  NODE *_wanted_output_fds;
  NODE *_wanted_input_fds;
  NODE *_readers;
  NODE *_writers;
  NODE *_terminators;
  NODE *_timeout;
  NODE *_timeout_exceeded;
  NODE *_get_low_level_events;
  NODE *_get_event_handler;
  NODE *_waiting_tasks;
  NODE *std__WRITE_TO;
  NODE *std__READ_FROM;
  NODE *std__file_descriptor_of;
  NODE *std__TERMINATED;
  NODE *std__pid_of;
  NODE *std__status_of;
  NODE *std__TIMEOUT;
  NODE *std__timeout_of;
  NODE *std__SCREEN_SIZE_CHANGE;
  NODE *std__width_of;
  NODE *std__height_of;
  NODE *std__KEY_PRESS;
  NODE *std__key_code_of;
  NODE *std__MOUSE_CLICK;
  NODE *std__target_of;
  NODE *std__PASTE;
  NODE *std__MESSAGE;
  NODE *types__event;
  NODE *std__events;
  NODE *std__want_to_write_to;
  NODE *std__no_longer_want_to_write_to;
  NODE *std__want_to_read_from;
  NODE *std__no_longer_want_to_read_from;
  NODE *std__wanting_to_write_to;
  NODE *std__wanting_to_read_from;
  NODE *std__wait_to_read_from;
  NODE *std__wait_to_write_to;
  NODE *std__wait_for_termination;
  NODE *std__discard;
  NODE *std__create_event;
  NODE *std__get_event;
  NODE *std__process_events;
  NODE *std__wait_to;
  NODE *std__par;
} var;
static const char *var_names[] = {
  "wanted_output_fds",
  "wanted_input_fds",
  "readers",
  "writers",
  "terminators",
  "timeout",
  "timeout_exceeded",
  "get_low_level_events",
  "get_event_handler",
  "waiting_tasks"
};
static NODE *unique__std__WRITE_TO;
static NODE *get__std__WRITE_TO(void) {
  return var.std__WRITE_TO;
}
static NODE *unique__std__READ_FROM;
static NODE *get__std__READ_FROM(void) {
  return var.std__READ_FROM;
}
static int poly_idx__std__file_descriptor_of;
static void type__std__file_descriptor_of(void);
static NODE *get__std__file_descriptor_of(void) {
  return var.std__file_descriptor_of;
}
static NODE *unique__std__TERMINATED;
static NODE *get__std__TERMINATED(void) {
  return var.std__TERMINATED;
}
static int poly_idx__std__pid_of;
static void type__std__pid_of(void);
static NODE *get__std__pid_of(void) {
  return var.std__pid_of;
}
static int poly_idx__std__status_of;
static void type__std__status_of(void);
static NODE *get__std__status_of(void) {
  return var.std__status_of;
}
static NODE *unique__std__TIMEOUT;
static NODE *get__std__TIMEOUT(void) {
  return var.std__TIMEOUT;
}
static int poly_idx__std__timeout_of;
static void type__std__timeout_of(void);
static NODE *get__std__timeout_of(void) {
  return var.std__timeout_of;
}
static NODE *unique__std__SCREEN_SIZE_CHANGE;
static NODE *get__std__SCREEN_SIZE_CHANGE(void) {
  return var.std__SCREEN_SIZE_CHANGE;
}
static int poly_idx__std__width_of;
static void type__std__width_of(void);
static NODE *get__std__width_of(void) {
  return var.std__width_of;
}
static int poly_idx__std__height_of;
static void type__std__height_of(void);
static NODE *get__std__height_of(void) {
  return var.std__height_of;
}
static NODE *unique__std__KEY_PRESS;
static NODE *get__std__KEY_PRESS(void) {
  return var.std__KEY_PRESS;
}
static int poly_idx__std__key_code_of;
static void type__std__key_code_of(void);
static NODE *get__std__key_code_of(void) {
  return var.std__key_code_of;
}
static NODE *unique__std__MOUSE_CLICK;
static NODE *get__std__MOUSE_CLICK(void) {
  return var.std__MOUSE_CLICK;
}
static int poly_idx__std__target_of;
static void type__std__target_of(void);
static NODE *get__std__target_of(void) {
  return var.std__target_of;
}
static NODE *unique__std__PASTE;
static NODE *get__std__PASTE(void) {
  return var.std__PASTE;
}
static NODE *unique__std__MESSAGE;
static NODE *get__std__MESSAGE(void) {
  return var.std__MESSAGE;
}
static NODE *get__types__event(void) {
  return var.types__event;
}
static NODE *get__std__events(void) {
  return var.std__events;
}
static void set__std__events(NODE *val) {
  var.std__events = val;
}
static NODE *func__22_1_std__want_to_write_to;
static void entry__22_1_std__want_to_write_to(void);
static FRAME_INFO frame__22_1_std__want_to_write_to = {1, {"fd"}};
static void cont__22_2(void);
static NODE *get__std__want_to_write_to(void) {
  return var.std__want_to_write_to;
}
static NODE *func__23_1_std__no_longer_want_to_write_to;
static void entry__23_1_std__no_longer_want_to_write_to(void);
static FRAME_INFO frame__23_1_std__no_longer_want_to_write_to = {1, {"fd"}};
static void cont__23_2(void);
static NODE *get__std__no_longer_want_to_write_to(void) {
  return var.std__no_longer_want_to_write_to;
}
static NODE *func__24_1_std__want_to_read_from;
static void entry__24_1_std__want_to_read_from(void);
static FRAME_INFO frame__24_1_std__want_to_read_from = {1, {"fd"}};
static void cont__24_2(void);
static NODE *get__std__want_to_read_from(void) {
  return var.std__want_to_read_from;
}
static NODE *func__25_1_std__no_longer_want_to_read_from;
static void entry__25_1_std__no_longer_want_to_read_from(void);
static FRAME_INFO frame__25_1_std__no_longer_want_to_read_from = {1, {"fd"}};
static void cont__25_2(void);
static NODE *get__std__no_longer_want_to_read_from(void) {
  return var.std__no_longer_want_to_read_from;
}
static NODE *func__26_1_std__wanting_to_write_to;
static void entry__26_1_std__wanting_to_write_to(void);
static FRAME_INFO frame__26_1_std__wanting_to_write_to = {1, {"fd"}};
static void cont__26_2(void);
static NODE *func__26_3;
static void entry__26_3(void);
static FRAME_INFO frame__26_3 = {1, {"fd"}};
static void cont__26_4(void);
static void cont__26_5(void);
static NODE *get__std__wanting_to_write_to(void) {
  return var.std__wanting_to_write_to;
}
static NODE *func__27_1_std__wanting_to_read_from;
static void entry__27_1_std__wanting_to_read_from(void);
static FRAME_INFO frame__27_1_std__wanting_to_read_from = {1, {"fd"}};
static void cont__27_2(void);
static NODE *func__27_3;
static void entry__27_3(void);
static FRAME_INFO frame__27_3 = {1, {"fd"}};
static void cont__27_4(void);
static void cont__27_5(void);
static NODE *get__std__wanting_to_read_from(void) {
  return var.std__wanting_to_read_from;
}
static NODE *func__29_1_std__wait_to_read_from;
static void entry__29_1_std__wait_to_read_from(void);
static FRAME_INFO frame__29_1_std__wait_to_read_from = {2, {"fd", "continuation"}};
static void cont__29_2(void);
static void cont__29_3(void);
static void cont__29_4(void);
static NODE *get__std__wait_to_read_from(void) {
  return var.std__wait_to_read_from;
}
static NODE *func__31_1_std__wait_to_write_to;
static void entry__31_1_std__wait_to_write_to(void);
static FRAME_INFO frame__31_1_std__wait_to_write_to = {2, {"fd", "continuation"}};
static void cont__31_2(void);
static void cont__31_3(void);
static void cont__31_4(void);
static NODE *get__std__wait_to_write_to(void) {
  return var.std__wait_to_write_to;
}
static NODE *func__33_1_std__wait_for_termination;
static void entry__33_1_std__wait_for_termination(void);
static FRAME_INFO frame__33_1_std__wait_for_termination = {2, {"pid", "continuation"}};
static void cont__33_2(void);
static void cont__33_3(void);
static NODE *get__std__wait_for_termination(void) {
  return var.std__wait_for_termination;
}
static NODE *func__36_1_std__discard;
static void entry__36_1_std__discard(void);
static FRAME_INFO frame__36_1_std__discard = {2, {"fd", "return"}};
static void cont__36_2(void);
static NODE *func__36_3;
static void entry__36_3(void);
static FRAME_INFO frame__36_3 = {3, {"fd", "new_events", "s"}};
static void cont__36_4(void);
static void cont__36_5(void);
static void cont__36_6(void);
static NODE *func__36_7;
static void entry__36_7(void);
static FRAME_INFO frame__36_7 = {5, {"idx", "event", "fd", "new_events", "s"}};
static void cont__36_8(void);
static void cont__36_9(void);
static NODE *func__36_10;
static void entry__36_10(void);
static FRAME_INFO frame__36_10 = {5, {"event", "fd", "new_events", "s", "idx"}};
static void cont__36_11(void);
static void cont__36_12(void);
static NODE *func__36_13;
static void entry__36_13(void);
static FRAME_INFO frame__36_13 = {3, {"new_events", "s", "idx"}};
static void cont__36_14(void);
static void cont__36_15(void);
static void cont__36_16(void);
static void cont__36_17(void);
static void cont__36_18(void);
static void cont__36_19(void);
static NODE *func__36_20;
static void entry__36_20(void);
static FRAME_INFO frame__36_20 = {2, {"new_events", "s"}};
static void cont__36_21(void);
static void cont__36_22(void);
static void cont__36_23(void);
static void cont__36_24(void);
static void cont__36_25(void);
static void cont__36_26(void);
static NODE *func__36_27;
static void entry__36_27(void);
static FRAME_INFO frame__36_27 = {1, {"return"}};
static void cont__36_28(void);
static NODE *get__std__discard(void) {
  return var.std__discard;
}
static NODE *func__37_1_std__create_event;
static void entry__37_1_std__create_event(void);
static FRAME_INFO frame__37_1_std__create_event = {1, {"event"}};
static void cont__37_2(void);
static NODE *get__std__create_event(void) {
  return var.std__create_event;
}
static NODE *func__38_1_get_low_level_events;
static void entry__38_1_get_low_level_events(void);
static FRAME_INFO frame__38_1_get_low_level_events = {9, {"for_readers_and_writers_only", "output_fds_list", "input_fds_list", "exception_fds_list", "child_changed_state", "window_changed_size", "ready_input_fds_list", "ready_output_fds_list", "ready_exception_fds_list"}};
static NODE *func__38_2;
static void entry__38_2(void);
static FRAME_INFO frame__38_2 = {2, {"output_fds_list", "input_fds_list"}};
static NODE *func__38_3;
static void entry__38_3(void);
static FRAME_INFO frame__38_3 = {3, {"output_fd", "continuation", "output_fds_list"}};
static void cont__38_4(void);
static void cont__38_5(void);
static NODE *func__38_6;
static void entry__38_6(void);
static FRAME_INFO frame__38_6 = {3, {"input_fd", "continuation", "input_fds_list"}};
static void cont__38_7(void);
static NODE *func__38_8;
static void entry__38_8(void);
static FRAME_INFO frame__38_8 = {2, {"output_fds_list", "input_fds_list"}};
static NODE *func__38_9;
static void entry__38_9(void);
static FRAME_INFO frame__38_9 = {2, {"output_fd", "output_fds_list"}};
static void cont__38_10(void);
static void cont__38_11(void);
static NODE *func__38_12;
static void entry__38_12(void);
static FRAME_INFO frame__38_12 = {2, {"input_fd", "input_fds_list"}};
static void cont__38_13(void);
static void cont__38_14(void);
static void cont__38_15(void);
static NODE *func__38_16;
static void entry__38_16(void);
static FRAME_INFO frame__38_16 = {8, {"child_changed_state", "window_changed_size", "ready_input_fds_list", "ready_output_fds_list", "ready_exception_fds_list", "ready_input_fds_set", "ready_output_fds_set", "ready_exception_fds_set"}};
static NODE *func__38_17;
static void entry__38_17(void);
static FRAME_INFO frame__38_17 = {0, {}};
static NODE *func__38_18;
static void entry__38_18(void);
static FRAME_INFO frame__38_18 = {1, {"break"}};
static NODE *func__38_19;
static void entry__38_19(void);
static FRAME_INFO frame__38_19 = {3, {"break", "status", "pid"}};
static void cont__38_20(void);
static void cont__38_21(void);
static void cont__38_22(void);
static void cont__38_23(void);
static void cont__38_24(void);
static void cont__38_25(void);
static void cont__38_26(void);
static NODE *func__38_27;
static void entry__38_27(void);
static FRAME_INFO frame__38_27 = {2, {"width", "height"}};
static void cont__38_28(void);
static void cont__38_29(void);
static NODE *func__38_30;
static void entry__38_30(void);
static FRAME_INFO frame__38_30 = {2, {"ready_input_fd", "ready_input_fds_set"}};
static void cont__38_31(void);
static void cont__38_32(void);
static NODE *func__38_33;
static void entry__38_33(void);
static FRAME_INFO frame__38_33 = {2, {"ready_output_fd", "ready_output_fds_set"}};
static void cont__38_34(void);
static void cont__38_35(void);
static NODE *func__38_36;
static void entry__38_36(void);
static FRAME_INFO frame__38_36 = {2, {"ready_exception_fd", "ready_exception_fds_set"}};
static void cont__38_37(void);
static void cont__38_38(void);
static NODE *func__38_39;
static void entry__38_39(void);
static FRAME_INFO frame__38_39 = {1, {"input_fd"}};
static void cont__38_40(void);
static NODE *func__38_41;
static void entry__38_41(void);
static FRAME_INFO frame__38_41 = {1, {"input_fd"}};
static void cont__38_42(void);
static NODE *func__38_43;
static void entry__38_43(void);
static FRAME_INFO frame__38_43 = {1, {"output_fd"}};
static void cont__38_44(void);
static NODE *func__38_45;
static void entry__38_45(void);
static FRAME_INFO frame__38_45 = {1, {"output_fd"}};
static NODE *func__38_46;
static void entry__38_46(void);
static FRAME_INFO frame__38_46 = {0, {}};
static NODE *func__39_1_get_event_handler;
static void entry__39_1_get_event_handler(void);
static FRAME_INFO frame__39_1_get_event_handler = {2, {"event", "return"}};
static void cont__39_2(void);
static NODE *func__39_3;
static void entry__39_3(void);
static FRAME_INFO frame__39_3 = {4, {"event", "return", "fd", "reader"}};
static void cont__39_4(void);
static void cont__39_5(void);
static void cont__39_6(void);
static NODE *func__39_7;
static void entry__39_7(void);
static FRAME_INFO frame__39_7 = {3, {"fd", "return", "reader"}};
static void cont__39_8(void);
static void cont__39_9(void);
static NODE *func__39_10;
static void entry__39_10(void);
static FRAME_INFO frame__39_10 = {4, {"event", "return", "fd", "writer"}};
static void cont__39_11(void);
static void cont__39_12(void);
static void cont__39_13(void);
static NODE *func__39_14;
static void entry__39_14(void);
static FRAME_INFO frame__39_14 = {3, {"fd", "return", "writer"}};
static void cont__39_15(void);
static void cont__39_16(void);
static NODE *func__39_17;
static void entry__39_17(void);
static FRAME_INFO frame__39_17 = {4, {"event", "return", "pid", "terminator"}};
static void cont__39_18(void);
static void cont__39_19(void);
static void cont__39_20(void);
static NODE *func__39_21;
static void entry__39_21(void);
static FRAME_INFO frame__39_21 = {3, {"pid", "return", "terminator"}};
static void cont__39_22(void);
static NODE *func__39_23;
static void entry__39_23(void);
static FRAME_INFO frame__39_23 = {1, {"return"}};
static void cont__39_24(void);
static NODE *func__40_1_std__get_event;
static void entry__40_1_std__get_event(void);
static FRAME_INFO frame__40_1_std__get_event = {1, {"return"}};
static NODE *func__40_2;
static void entry__40_2(void);
static FRAME_INFO frame__40_2 = {2, {"myself", "return"}};
static void cont__40_3(void);
static void cont__40_4(void);
static NODE *func__40_5;
static void entry__40_5(void);
static FRAME_INFO frame__40_5 = {4, {"myself", "return", "event", "handler"}};
static void cont__40_6(void);
static void cont__40_7(void);
static void cont__40_8(void);
static NODE *func__40_9;
static void entry__40_9(void);
static FRAME_INFO frame__40_9 = {3, {"myself", "handler", "event"}};
static void cont__40_10(void);
static void cont__40_11(void);
static void cont__40_12(void);
static NODE *func__40_13;
static void entry__40_13(void);
static FRAME_INFO frame__40_13 = {2, {"handler", "event"}};
static NODE *func__40_14;
static void entry__40_14(void);
static FRAME_INFO frame__40_14 = {1, {"handler"}};
static void cont__40_15(void);
static NODE *string__40_16;
static void cont__40_17(void);
static NODE *func__40_18;
static void entry__40_18(void);
static FRAME_INFO frame__40_18 = {0, {}};
static void cont__40_19(void);
static NODE *get__std__get_event(void) {
  return var.std__get_event;
}
static NODE *func__42_1_std__process_events;
static void entry__42_1_std__process_events(void);
static FRAME_INFO frame__42_1_std__process_events = {1, {"i"}};
static NODE *func__42_2;
static void entry__42_2(void);
static FRAME_INFO frame__42_2 = {0, {}};
static void cont__42_3(void);
static void cont__42_4(void);
static NODE *func__42_5;
static void entry__42_5(void);
static FRAME_INFO frame__42_5 = {0, {}};
static void cont__42_6(void);
static void cont__42_7(void);
static void cont__42_8(void);
static NODE *func__42_9;
static void entry__42_9(void);
static FRAME_INFO frame__42_9 = {0, {}};
static void cont__42_10(void);
static void cont__42_11(void);
static void cont__42_12(void);
static NODE *func__42_13;
static void entry__42_13(void);
static FRAME_INFO frame__42_13 = {2, {"i", "n"}};
static void cont__42_14(void);
static NODE *func__42_15;
static void entry__42_15(void);
static FRAME_INFO frame__42_15 = {2, {"n", "i"}};
static void cont__42_16(void);
static void cont__42_17(void);
static NODE *func__42_18;
static void entry__42_18(void);
static FRAME_INFO frame__42_18 = {3, {"i", "event", "handler"}};
static void cont__42_19(void);
static void cont__42_20(void);
static void cont__42_21(void);
static NODE *func__42_22;
static void entry__42_22(void);
static FRAME_INFO frame__42_22 = {3, {"i", "handler", "event"}};
static void cont__42_23(void);
static void cont__42_24(void);
static void cont__42_25(void);
static NODE *func__42_26;
static void entry__42_26(void);
static FRAME_INFO frame__42_26 = {2, {"handler", "event"}};
static NODE *func__42_27;
static void entry__42_27(void);
static FRAME_INFO frame__42_27 = {1, {"handler"}};
static void cont__42_28(void);
static void cont__42_29(void);
static void cont__42_30(void);
static void cont__42_31(void);
static NODE *get__std__process_events(void) {
  return var.std__process_events;
}
static NODE *func__43_1_std__wait_to;
static void entry__43_1_std__wait_to(void);
static FRAME_INFO frame__43_1_std__wait_to = {2, {"args", "event"}};
static NODE *func__43_2;
static void entry__43_2(void);
static FRAME_INFO frame__43_2 = {2, {"continuation", "args"}};
static NODE *func__43_3;
static void entry__43_3(void);
static FRAME_INFO frame__43_3 = {4, {"arg", "continuation", "type", "value"}};
static void cont__43_4(void);
static void cont__43_5(void);
static NODE *func__43_6;
static void entry__43_6(void);
static FRAME_INFO frame__43_6 = {2, {"value", "continuation"}};
static void cont__43_7(void);
static void cont__43_8(void);
static NODE *func__43_9;
static void entry__43_9(void);
static FRAME_INFO frame__43_9 = {2, {"value", "continuation"}};
static void cont__43_10(void);
static void cont__43_11(void);
static NODE *func__43_12;
static void entry__43_12(void);
static FRAME_INFO frame__43_12 = {2, {"value", "continuation"}};
static void cont__43_13(void);
static NODE *func__43_14;
static void entry__43_14(void);
static FRAME_INFO frame__43_14 = {2, {"value", "continuation"}};
static void cont__43_15(void);
static void cont__43_16(void);
static void cont__43_17(void);
static NODE *func__43_18;
static void entry__43_18(void);
static FRAME_INFO frame__43_18 = {3, {"arg", "type", "value"}};
static void cont__43_19(void);
static void cont__43_20(void);
static NODE *func__43_21;
static void entry__43_21(void);
static FRAME_INFO frame__43_21 = {1, {"value"}};
static void cont__43_22(void);
static void cont__43_23(void);
static NODE *func__43_24;
static void entry__43_24(void);
static FRAME_INFO frame__43_24 = {1, {"value"}};
static void cont__43_25(void);
static void cont__43_26(void);
static NODE *func__43_27;
static void entry__43_27(void);
static FRAME_INFO frame__43_27 = {1, {"value"}};
static void cont__43_28(void);
static void cont__43_29(void);
static NODE *get__std__wait_to(void) {
  return var.std__wait_to;
}
static NODE *func__44_1_std__par;
static void entry__44_1_std__par(void);
static FRAME_INFO frame__44_1_std__par = {1, {"tasks"}};
static void cont__44_2(void);
static NODE *get__std__par(void) {
  return var.std__par;
}
void run__basic__event(void);

static CONTINUATION_INFO continuation_info[] = {
  {type__std__file_descriptor_of, NULL, 26, 26, 2, 24},
  {type__std__pid_of, NULL, 30, 30, 2, 12},
  {type__std__status_of, NULL, 31, 31, 2, 15},
  {type__std__timeout_of, NULL, 35, 35, 2, 16},
  {type__std__width_of, NULL, 39, 39, 2, 14},
  {type__std__height_of, NULL, 40, 40, 2, 15},
  {type__std__key_code_of, NULL, 44, 44, 2, 17},
  {type__std__target_of, NULL, 48, 48, 2, 15},
  {run__basic__event, NULL, 331, 331, 1, 26},
  {entry__22_1_std__want_to_write_to, NULL, 69, 69, 3, 24},
  {cont__22_2, &frame__22_1_std__want_to_write_to, 69, 69, 29, 29},
  {entry__23_1_std__no_longer_want_to_write_to, NULL, 82, 82, 3, 24},
  {cont__23_2, &frame__23_1_std__no_longer_want_to_write_to, 82, 82, 30, 30},
  {entry__24_1_std__want_to_read_from, NULL, 95, 95, 3, 23},
  {cont__24_2, &frame__24_1_std__want_to_read_from, 95, 95, 28, 28},
  {entry__25_1_std__no_longer_want_to_read_from, NULL, 108, 108, 3, 23},
  {cont__25_2, &frame__25_1_std__no_longer_want_to_read_from, 108, 108, 29, 29},
  {entry__26_3, NULL, 119, 119, 23, 43},
  {cont__26_4, &frame__26_3, 119, 119, 23, 43},
  {entry__26_1_std__wanting_to_write_to, NULL, 119, 119, 6, 18},
  {cont__26_2, &frame__26_1_std__wanting_to_write_to, 119, 119, 6, 43},
  {cont__26_5, &frame__26_1_std__wanting_to_write_to, 119, 119, 3, 43},
  {entry__27_3, NULL, 130, 130, 23, 42},
  {cont__27_4, &frame__27_3, 130, 130, 23, 42},
  {entry__27_1_std__wanting_to_read_from, NULL, 130, 130, 6, 18},
  {cont__27_2, &frame__27_1_std__wanting_to_read_from, 130, 130, 6, 42},
  {cont__27_5, &frame__27_1_std__wanting_to_read_from, 130, 130, 3, 42},
  {entry__29_1_std__wait_to_read_from, NULL, 143, 143, 3, 22},
  {cont__29_2, &frame__29_1_std__wait_to_read_from, 144, 144, 3, 14},
  {cont__29_3, &frame__29_1_std__wait_to_read_from, 145, 145, 3, 45},
  {cont__29_4, &frame__29_1_std__wait_to_read_from, 145, 145, 45, 45},
  {entry__31_1_std__wait_to_write_to, NULL, 158, 158, 3, 21},
  {cont__31_2, &frame__31_1_std__wait_to_write_to, 159, 159, 3, 14},
  {cont__31_3, &frame__31_1_std__wait_to_write_to, 160, 160, 3, 45},
  {cont__31_4, &frame__31_1_std__wait_to_write_to, 160, 160, 45, 45},
  {entry__33_1_std__wait_for_termination, NULL, 173, 173, 3, 19},
  {cont__33_2, &frame__33_1_std__wait_for_termination, 174, 174, 3, 45},
  {cont__33_3, &frame__33_1_std__wait_for_termination, 174, 174, 45, 45},
  {entry__36_13, NULL, 196, 196, 45, 49},
  {cont__36_14, &frame__36_13, 196, 196, 30, 50},
  {cont__36_15, &frame__36_13, 196, 196, 11, 50},
  {cont__36_16, &frame__36_13, 197, 197, 11, 18},
  {cont__36_17, &frame__36_13, 197, 197, 18, 18},
  {entry__36_10, NULL, 195, 195, 12, 36},
  {cont__36_11, &frame__36_10, 195, 195, 12, 42},
  {cont__36_12, &frame__36_10, 195, 197, 9, 18},
  {entry__36_7, NULL, 194, 194, 12, 25},
  {cont__36_8, &frame__36_7, 194, 194, 27, 45},
  {cont__36_9, &frame__36_7, 194, 197, 7, 19},
  {entry__36_20, NULL, 199, 199, 42, 42},
  {cont__36_21, &frame__36_20, 199, 199, 26, 43},
  {cont__36_22, &frame__36_20, 199, 199, 7, 43},
  {cont__36_23, &frame__36_20, 200, 200, 24, 24},
  {entry__36_3, NULL, 185, 185, 5, 34},
  {cont__36_4, &frame__36_3, 186, 186, 5, 33},
  {cont__36_5, &frame__36_3, 187, 187, 5, 12},
  {cont__36_6, &frame__36_3, 193, 197, 5, 20},
  {cont__36_18, &frame__36_3, 198, 198, 8, 12},
  {cont__36_19, &frame__36_3, 198, 200, 5, 24},
  {entry__36_27, NULL, 201, 201, 39, 54},
  {entry__36_1_std__discard, NULL, 184, 184, 6, 18},
  {cont__36_2, &frame__36_1_std__discard, 184, 200, 3, 25},
  {cont__36_24, &frame__36_1_std__discard, 201, 201, 6, 31},
  {cont__36_25, &frame__36_1_std__discard, 201, 201, 6, 36},
  {cont__36_26, &frame__36_1_std__discard, 201, 201, 3, 54},
  {cont__36_28, &frame__36_1_std__discard, 201, 201, 54, 54},
  {entry__37_1_std__create_event, NULL, 209, 209, 3, 20},
  {cont__37_2, &frame__37_1_std__create_event, 209, 209, 20, 20},
  {entry__38_3, NULL, 218, 218, 9, 39},
  {cont__38_4, &frame__38_3, 218, 218, 39, 39},
  {entry__38_6, NULL, 219, 219, 50, 78},
  {cont__38_7, &frame__38_6, 219, 219, 78, 78},
  {entry__38_2, NULL, 217, 218, 7, 39},
  {cont__38_5, &frame__38_2, 219, 219, 7, 78},
  {entry__38_9, NULL, 221, 221, 47, 77},
  {cont__38_10, &frame__38_9, 221, 221, 77, 77},
  {entry__38_12, NULL, 222, 222, 45, 73},
  {cont__38_13, &frame__38_12, 222, 222, 73, 73},
  {entry__38_8, NULL, 221, 221, 7, 77},
  {cont__38_11, &frame__38_8, 222, 222, 7, 73},
  {entry__38_19, NULL, 238, 238, 36, 36},
  {cont__38_20, &frame__38_19, 238, 238, 13, 41},
  {cont__38_21, &frame__38_19, 239, 239, 16, 23},
  {cont__38_22, &frame__38_19, 239, 239, 16, 23},
  {cont__38_23, &frame__38_19, 239, 239, 13, 29},
  {cont__38_24, &frame__38_19, 240, 241, 13, 77},
  {entry__38_18, NULL, 237, 241, 11, 78},
  {cont__38_25, &frame__38_18, 241, 241, 78, 78},
  {entry__38_17, NULL, 236, 241, 9, 79},
  {entry__38_27, NULL, 243, 243, 9, 53},
  {cont__38_28, &frame__38_27, 244, 248, 9, 30},
  {entry__38_30, NULL, 253, 253, 9, 44},
  {cont__38_31, &frame__38_30, 253, 253, 49, 49},
  {entry__38_33, NULL, 255, 255, 9, 46},
  {cont__38_34, &frame__38_33, 255, 255, 51, 51},
  {entry__38_36, NULL, 257, 257, 9, 52},
  {cont__38_37, &frame__38_36, 257, 257, 57, 57},
  {entry__38_41, NULL, 260, 261, 11, 73},
  {entry__38_39, NULL, 259, 259, 12, 37},
  {cont__38_40, &frame__38_39, 259, 261, 9, 74},
  {entry__38_45, NULL, 264, 265, 11, 73},
  {entry__38_43, NULL, 263, 263, 12, 39},
  {cont__38_44, &frame__38_43, 263, 265, 9, 74},
  {entry__38_16, NULL, 235, 241, 7, 80},
  {cont__38_26, &frame__38_16, 242, 248, 7, 31},
  {cont__38_29, &frame__38_16, 252, 253, 7, 49},
  {cont__38_32, &frame__38_16, 254, 255, 7, 51},
  {cont__38_35, &frame__38_16, 256, 257, 7, 57},
  {cont__38_38, &frame__38_16, 258, 261, 7, 75},
  {cont__38_42, &frame__38_16, 262, 265, 7, 75},
  {entry__38_46, NULL, 267, 267, 7, 49},
  {entry__38_1_get_low_level_events, NULL, 215, 222, 3, 74},
  {cont__38_14, &frame__38_1_get_low_level_events, 224, 233, 5, 12},
  {cont__38_15, &frame__38_1_get_low_level_events, 223, 267, 3, 50},
  {entry__39_7, NULL, 280, 280, 9, 38},
  {cont__39_8, &frame__39_7, 281, 281, 9, 20},
  {cont__39_9, &frame__39_7, 282, 282, 9, 21},
  {entry__39_3, NULL, 277, 277, 7, 35},
  {cont__39_4, &frame__39_3, 278, 278, 7, 25},
  {cont__39_5, &frame__39_3, 279, 279, 10, 26},
  {cont__39_6, &frame__39_3, 279, 282, 7, 21},
  {entry__39_14, NULL, 287, 287, 9, 37},
  {cont__39_15, &frame__39_14, 288, 288, 9, 20},
  {cont__39_16, &frame__39_14, 289, 289, 9, 21},
  {entry__39_10, NULL, 284, 284, 7, 35},
  {cont__39_11, &frame__39_10, 285, 285, 7, 25},
  {cont__39_12, &frame__39_10, 286, 286, 10, 26},
  {cont__39_13, &frame__39_10, 286, 289, 7, 21},
  {entry__39_21, NULL, 294, 294, 9, 25},
  {cont__39_22, &frame__39_21, 295, 295, 9, 25},
  {entry__39_17, NULL, 291, 291, 7, 24},
  {cont__39_18, &frame__39_17, 292, 292, 7, 34},
  {cont__39_19, &frame__39_17, 293, 293, 10, 30},
  {cont__39_20, &frame__39_17, 293, 295, 7, 25},
  {entry__39_23, NULL, 297, 297, 7, 29},
  {entry__39_1_get_event_handler, NULL, 275, 275, 5, 18},
  {cont__39_2, &frame__39_1_get_event_handler, 274, 297, 3, 30},
  {cont__39_24, &frame__39_1_get_event_handler, 298, 298, 3, 14},
  {entry__40_13, NULL, 323, 323, 15, 27},
  {entry__40_14, NULL, 325, 325, 15, 21},
  {entry__40_9, NULL, 320, 320, 11, 35},
  {cont__40_10, &frame__40_9, 322, 322, 13, 39},
  {cont__40_11, &frame__40_9, 322, 322, 13, 44},
  {cont__40_12, &frame__40_9, 321, 325, 11, 22},
  {cont__40_15, &frame__40_9, 326, 326, 11, 38},
  {entry__40_5, NULL, 317, 317, 9, 27},
  {cont__40_6, &frame__40_5, 318, 318, 9, 41},
  {cont__40_7, &frame__40_5, 319, 319, 12, 29},
  {cont__40_8, &frame__40_5, 319, 326, 9, 38},
  {cont__40_17, &frame__40_5, 327, 327, 9, 20},
  {entry__40_18, NULL, 329, 329, 9, 34},
  {entry__40_2, NULL, 316, 316, 7, 23},
  {cont__40_3, &frame__40_2, 316, 316, 7, 27},
  {cont__40_4, &frame__40_2, 315, 329, 5, 35},
  {entry__40_1_std__get_event, NULL, 314, 329, 3, 36},
  {cont__40_19, &frame__40_1_std__get_event, 329, 329, 36, 36},
  {entry__42_5, NULL, 338, 338, 42, 60},
  {cont__42_6, &frame__42_5, 338, 338, 42, 60},
  {entry__42_2, NULL, 338, 338, 12, 35},
  {cont__42_3, &frame__42_2, 338, 338, 12, 39},
  {cont__42_4, &frame__42_2, 338, 338, 9, 60},
  {entry__42_9, NULL, 339, 339, 26, 41},
  {cont__42_10, &frame__42_9, 339, 339, 26, 41},
  {entry__42_26, NULL, 350, 350, 13, 25},
  {entry__42_27, NULL, 352, 352, 13, 19},
  {entry__42_22, NULL, 347, 347, 9, 27},
  {cont__42_23, &frame__42_22, 349, 349, 11, 37},
  {cont__42_24, &frame__42_22, 349, 349, 11, 42},
  {cont__42_25, &frame__42_22, 348, 352, 9, 20},
  {cont__42_28, &frame__42_22, 353, 353, 9, 36},
  {entry__42_18, NULL, 344, 344, 7, 22},
  {cont__42_19, &frame__42_18, 345, 345, 7, 39},
  {cont__42_20, &frame__42_18, 346, 346, 10, 27},
  {cont__42_21, &frame__42_18, 346, 353, 7, 36},
  {cont__42_29, &frame__42_18, 354, 354, 7, 12},
  {cont__42_30, &frame__42_18, 354, 354, 12, 12},
  {entry__42_15, NULL, 343, 343, 14, 19},
  {cont__42_16, &frame__42_15, 343, 343, 14, 19},
  {cont__42_17, &frame__42_15, 343, 354, 11, 12},
  {entry__42_13, NULL, 342, 342, 5, 24},
  {cont__42_14, &frame__42_13, 343, 354, 5, 12},
  {cont__42_31, &frame__42_13, 355, 355, 5, 29},
  {entry__42_1_std__process_events, NULL, 338, 338, 3, 60},
  {cont__42_7, &frame__42_1_std__process_events, 339, 339, 6, 21},
  {cont__42_8, &frame__42_1_std__process_events, 339, 339, 6, 41},
  {cont__42_11, &frame__42_1_std__process_events, 339, 339, 3, 51},
  {cont__42_12, &frame__42_1_std__process_events, 341, 355, 3, 29},
  {entry__43_6, NULL, 375, 375, 11, 33},
  {cont__43_7, &frame__43_6, 376, 376, 11, 25},
  {cont__43_8, &frame__43_6, 376, 376, 38, 38},
  {entry__43_9, NULL, 378, 378, 11, 32},
  {cont__43_10, &frame__43_9, 379, 379, 11, 25},
  {cont__43_11, &frame__43_9, 379, 379, 38, 38},
  {entry__43_12, NULL, 381, 381, 11, 29},
  {cont__43_13, &frame__43_12, 381, 381, 42, 42},
  {entry__43_14, NULL, 384, 384, 40, 40},
  {entry__43_3, NULL, 370, 370, 7, 23},
  {cont__43_4, &frame__43_3, 371, 371, 7, 26},
  {cont__43_5, &frame__43_3, 372, 384, 7, 41},
  {entry__43_2, NULL, 369, 384, 5, 42},
  {cont__43_15, &frame__43_2, 385, 385, 5, 47},
  {cont__43_16, &frame__43_2, 385, 385, 47, 47},
  {entry__43_21, NULL, 392, 392, 9, 41},
  {cont__43_22, &frame__43_21, 393, 393, 9, 23},
  {cont__43_23, &frame__43_21, 393, 393, 33, 33},
  {entry__43_24, NULL, 395, 395, 9, 40},
  {cont__43_25, &frame__43_24, 396, 396, 9, 23},
  {cont__43_26, &frame__43_24, 396, 396, 33, 33},
  {entry__43_27, NULL, 398, 398, 9, 27},
  {cont__43_28, &frame__43_27, 398, 398, 37, 37},
  {entry__43_18, NULL, 387, 387, 5, 21},
  {cont__43_19, &frame__43_18, 388, 388, 5, 24},
  {cont__43_20, &frame__43_18, 389, 398, 5, 38},
  {entry__43_1_std__wait_to, NULL, 368, 385, 3, 47},
  {cont__43_17, &frame__43_1_std__wait_to, 386, 398, 3, 39},
  {cont__43_29, &frame__43_1_std__wait_to, 401, 401, 3, 10},
  {entry__44_1_std__par, NULL, 404, 404, 3, 29},
  {cont__44_2, &frame__44_1_std__par, 405, 405, 3, 16}
};

union NODE {
  struct {
    FUNC type;
    ATTRIBUTES *attributes;
  };
  CONTINUATION continuation;
  CLOSURE closure;
};
static void type__std__file_descriptor_of(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__file_descriptor_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__file_descriptor_of, attr);
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
static void type__std__pid_of(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__pid_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__pid_of, attr);
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
static void type__std__status_of(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__status_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__status_of, attr);
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
static void type__std__timeout_of(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__timeout_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__timeout_of, attr);
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
static void type__std__width_of(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__width_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__width_of, attr);
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
static void type__std__height_of(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__height_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__height_of, attr);
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
static void type__std__key_code_of(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__key_code_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__key_code_of, attr);
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
static void type__std__target_of(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__target_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__target_of, attr);
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

static const char *used_namespaces[] = {
  "std",
  NULL
};

static MODULE_INFO module_info = {
  NULL,
  "basic__event",
  continuation_info,
  sizeof(continuation_info)/sizeof(CONTINUATION_INFO),
  (NODE **)&var,
  var_names,
  sizeof(var_names)/sizeof(const char *),
  used_namespaces,
  {DEBUG_FILENAME("basic/event.sim")}
};

/******
C O D E
******/

static int already_run = false;

EXPORT void run__basic__event(void) {
  if (already_run) {
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  already_run = true;
  allocate_initialized_frame_gc(0, 0);
  // 53: $types::event types::object
  initialize_maybe_future(var.types__event, get__types__object());
  // 54: $$std::events empty_list
  var.std__events = get__empty_list();
  // 55: $$wanted_output_fds empty_set
  var._wanted_output_fds = get__empty_set();
  // 56: $$wanted_input_fds empty_set
  var._wanted_input_fds = get__empty_set();
  // 132: $$readers empty_key_order_table
  var._readers = get__empty_key_order_table();
  // 147: $$writers empty_key_order_table
  var._writers = get__empty_key_order_table();
  // 162: $$terminators empty_key_order_table
  var._terminators = get__empty_key_order_table();
  // 176: $$timeout undefined # there should be separate timeouts for each caller
  var._timeout = get__undefined();
  // 177: $$timeout_exceeded undefined
  var._timeout_exceeded = get__undefined();
  // 331: $$waiting_tasks empty_list
  var._waiting_tasks = get__empty_list();
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__22_1_std__want_to_write_to(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // fd: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 69: !wanted_output_fds(fd) true
  frame->slots[1] /* temp__1 */ = get__true();
  // 69: !wanted_output_fds(fd)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd */;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = var._wanted_output_fds;
  func = myself->type;
  frame->cont = cont__22_2;
}
static void cont__22_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._wanted_output_fds = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__23_1_std__no_longer_want_to_write_to(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // fd: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 82: !wanted_output_fds(fd) false
  frame->slots[1] /* temp__1 */ = get__false();
  // 82: !wanted_output_fds(fd)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd */;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = var._wanted_output_fds;
  func = myself->type;
  frame->cont = cont__23_2;
}
static void cont__23_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._wanted_output_fds = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__24_1_std__want_to_read_from(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // fd: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 95: !wanted_input_fds(fd) true
  frame->slots[1] /* temp__1 */ = get__true();
  // 95: !wanted_input_fds(fd)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd */;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = var._wanted_input_fds;
  func = myself->type;
  frame->cont = cont__24_2;
}
static void cont__24_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._wanted_input_fds = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__25_1_std__no_longer_want_to_read_from(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // fd: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 108: !wanted_input_fds(fd) false
  frame->slots[1] /* temp__1 */ = get__false();
  // 108: !wanted_input_fds(fd)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd */;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = var._wanted_input_fds;
  func = myself->type;
  frame->cont = cont__25_2;
}
static void cont__25_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._wanted_input_fds = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__26_1_std__wanting_to_write_to(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // fd: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 119: ... fd.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__26_2;
}
static void cont__26_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 119: ... wanted_output_fds(fd)
  frame->slots[3] /* temp__3 */ = create_closure(entry__26_3, 0);
  // 119: ... fd.is_defined && wanted_output_fds(fd)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__26_5;
}
static void entry__26_3(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // fd: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* fd */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 119: ... wanted_output_fds(fd)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd */;
  result_count = 1;
  myself = var._wanted_output_fds;
  func = myself->type;
  frame->cont = cont__26_4;
}
static void cont__26_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 119: ... wanted_output_fds(fd)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__26_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 119: -> fd.is_defined && wanted_output_fds(fd)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__27_1_std__wanting_to_read_from(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // fd: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 130: ... fd.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__27_2;
}
static void cont__27_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 130: ... wanted_input_fds(fd)
  frame->slots[3] /* temp__3 */ = create_closure(entry__27_3, 0);
  // 130: ... fd.is_defined && wanted_input_fds(fd)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__27_5;
}
static void entry__27_3(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // fd: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* fd */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 130: ... wanted_input_fds(fd)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd */;
  result_count = 1;
  myself = var._wanted_input_fds;
  func = myself->type;
  frame->cont = cont__27_4;
}
static void cont__27_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 130: ... wanted_input_fds(fd)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__27_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 130: -> fd.is_defined && wanted_input_fds(fd)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__29_1_std__wait_to_read_from(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // fd: 0
  // continuation: 1
  frame->slots[1] /* continuation */ = create_continuation();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 143: want_to_read_from fd
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd */;
  result_count = 0;
  myself = get__want_to_read_from();
  func = myself->type;
  frame->cont = cont__29_2;
}
static void cont__29_2(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 144: !readers(fd) continuation
  frame->slots[2] /* temp__1 */ = frame->slots[1] /* continuation */;
  // 144: !readers(fd)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = var._readers;
  func = myself->type;
  frame->cont = cont__29_3;
}
static void cont__29_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._readers = arguments->slots[0];
  // 145: process_events # will never return directly
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = get__process_events();
  func = myself->type;
  frame->cont = cont__29_4;
}
static void cont__29_4(void) {
  myself = frame->slots[1] /* continuation */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__31_1_std__wait_to_write_to(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // fd: 0
  // continuation: 1
  frame->slots[1] /* continuation */ = create_continuation();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 158: want_to_write_to fd
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd */;
  result_count = 0;
  myself = get__want_to_write_to();
  func = myself->type;
  frame->cont = cont__31_2;
}
static void cont__31_2(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 159: !writers(fd) continuation
  frame->slots[2] /* temp__1 */ = frame->slots[1] /* continuation */;
  // 159: !writers(fd)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = var._writers;
  func = myself->type;
  frame->cont = cont__31_3;
}
static void cont__31_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._writers = arguments->slots[0];
  // 160: process_events # will never return directly
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = get__process_events();
  func = myself->type;
  frame->cont = cont__31_4;
}
static void cont__31_4(void) {
  myself = frame->slots[1] /* continuation */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__33_1_std__wait_for_termination(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // pid: 0
  // continuation: 1
  frame->slots[1] /* continuation */ = create_continuation();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 173: !terminators(pid) continuation
  frame->slots[2] /* temp__1 */ = frame->slots[1] /* continuation */;
  // 173: !terminators(pid)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* pid */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = var._terminators;
  func = myself->type;
  frame->cont = cont__33_2;
}
static void cont__33_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._terminators = arguments->slots[0];
  // 174: process_events # will never return directly
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = get__process_events();
  func = myself->type;
  frame->cont = cont__33_3;
}
static void cont__33_3(void) {
  myself = frame->slots[1] /* continuation */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__36_1_std__discard(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // fd: 0
  // return: 1
  frame->slots[1] /* return */ = create_continuation();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 184: ... fd.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__36_2;
}
static void cont__36_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 184: ... :
  // 185:   no_longer_want_to_read_from fd
  // 186:   no_longer_want_to_write_to fd
  // 187:   close fd
  // 188:   
  // 189:   # remove all associated events
  // 190:   
  // 191:   $$new_events empty_list
  // 192:   $$s 1
  // 193:   for_each events: (idx event)
  // ...
  frame->slots[3] /* temp__2 */ = create_closure(entry__36_3, 0);
  // 184: if fd.is_defined:
  // 185:   no_longer_want_to_read_from fd
  // 186:   no_longer_want_to_write_to fd
  // 187:   close fd
  // 188:   
  // 189:   # remove all associated events
  // 190:   
  // 191:   $$new_events empty_list
  // 192:   $$s 1
  // 193:   for_each events: (idx event)
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__36_24;
}
static void entry__36_20(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // new_events: 0
  // s: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* new_events */
  frame->slots[1] = myself->closure.frame->slots[2]; /* s */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 199: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__36_21;
}
static void cont__36_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 199: ... range(events s -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__events();
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* s */;
  arguments->slots[2] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__36_22;
}
static void cont__36_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 199: append &new_events range(events s -1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* new_events */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__36_23;
}
static void cont__36_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* new_events */ = arguments->slots[0];
  // 200: !events new_events
  set__events(((CELL *)frame->slots[0])->contents /* new_events */);
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__36_3(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // fd: 0
  // new_events: 1
  // s: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* fd */
  frame->slots[1] /* new_events */ = create_cell();
  frame->slots[2] /* s */ = create_cell();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 185: no_longer_want_to_read_from fd
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd */;
  result_count = 0;
  myself = get__no_longer_want_to_read_from();
  func = myself->type;
  frame->cont = cont__36_4;
}
static void cont__36_4(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 186: no_longer_want_to_write_to fd
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd */;
  result_count = 0;
  myself = get__no_longer_want_to_write_to();
  func = myself->type;
  frame->cont = cont__36_5;
}
static void cont__36_5(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 187: close fd
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd */;
  result_count = 0;
  myself = get__close();
  func = myself->type;
  frame->cont = cont__36_6;
}
static void cont__36_6(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 191: $$new_events empty_list
  ((CELL *)frame->slots[1])->contents /* new_events */ = get__empty_list();
  // 192: $$s 1
  ((CELL *)frame->slots[2])->contents /* s */ = number__1;
  // 193: ... : (idx event)
  // 194:   case type_of(event) WRITE_TO, READ_FROM:
  // 195:     if file_descriptor_of(event) == fd:
  // 196:       append &new_events range(events s idx-1)
  // 197:       !s idx+1
  frame->slots[3] /* temp__1 */ = create_closure(entry__36_7, 2);
  // 193: for_each events: (idx event)
  // 194:   case type_of(event) WRITE_TO, READ_FROM:
  // 195:     if file_descriptor_of(event) == fd:
  // 196:       append &new_events range(events s idx-1)
  // 197:       !s idx+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__events();
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__36_18;
}
static void entry__36_13(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // new_events: 0
  // s: 1
  // idx: 2
  frame->slots[0] = myself->closure.frame->slots[2]; /* new_events */
  frame->slots[1] = myself->closure.frame->slots[3]; /* s */
  frame->slots[2] = myself->closure.frame->slots[4]; /* idx */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 196: ... idx-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* idx */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__36_14;
}
static void cont__36_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 196: ... range(events s idx-1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__events();
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* s */;
  arguments->slots[2] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__36_15;
}
static void cont__36_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 196: append &new_events range(events s idx-1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* new_events */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__36_16;
}
static void cont__36_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* new_events */ = arguments->slots[0];
  // 197: !s idx+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* idx */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__36_17;
}
static void cont__36_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* s */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__36_10(void) {
  allocate_initialized_frame_gc(5, 8);
  // slot allocations:
  // event: 0
  // fd: 1
  // new_events: 2
  // s: 3
  // idx: 4
  frame->slots[0] = myself->closure.frame->slots[1]; /* event */
  frame->slots[1] = myself->closure.frame->slots[2]; /* fd */
  frame->slots[2] = myself->closure.frame->slots[3]; /* new_events */
  frame->slots[3] = myself->closure.frame->slots[4]; /* s */
  frame->slots[4] = myself->closure.frame->slots[0]; /* idx */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 195: ... file_descriptor_of(event)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* event */;
  result_count = 1;
  myself = get__file_descriptor_of();
  func = myself->type;
  frame->cont = cont__36_11;
}
static void cont__36_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 195: ... file_descriptor_of(event) == fd
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[1] /* fd */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__36_12;
}
static void cont__36_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 195: ... :
  // 196:   append &new_events range(events s idx-1)
  // 197:   !s idx+1
  frame->slots[7] /* temp__3 */ = create_closure(entry__36_13, 0);
  // 195: if file_descriptor_of(event) == fd:
  // 196:   append &new_events range(events s idx-1)
  // 197:   !s idx+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__36_7(void) {
  allocate_initialized_frame_gc(5, 8);
  // slot allocations:
  // idx: 0
  // event: 1
  // fd: 2
  // new_events: 3
  // s: 4
  frame->slots[2] = myself->closure.frame->slots[0]; /* fd */
  frame->slots[3] = myself->closure.frame->slots[1]; /* new_events */
  frame->slots[4] = myself->closure.frame->slots[2]; /* s */
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 194: ... type_of(event)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* event */;
  result_count = 1;
  myself = get__type_of();
  func = myself->type;
  frame->cont = cont__36_8;
}
static void cont__36_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 194: ... WRITE_TO, READ_FROM
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__WRITE_TO();
  arguments->slots[1] = get__READ_FROM();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__36_9;
}
static void cont__36_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 194: ... :
  // 195:   if file_descriptor_of(event) == fd:
  // 196:     append &new_events range(events s idx-1)
  // 197:     !s idx+1
  frame->slots[7] /* temp__3 */ = create_closure(entry__36_10, 0);
  // 194: case type_of(event) WRITE_TO, READ_FROM:
  // 195:   if file_descriptor_of(event) == fd:
  // 196:     append &new_events range(events s idx-1)
  // 197:     !s idx+1
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  arguments->slots[2] = frame->slots[7] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__36_18(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 198: ... s > 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__1;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* s */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__36_19;
}
static void cont__36_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 198: ... :
  // 199:   append &new_events range(events s -1)
  // 200:   !events new_events
  frame->slots[4] /* temp__2 */ = create_closure(entry__36_20, 0);
  // 198: if s > 1:
  // 199:   append &new_events range(events s -1)
  // 200:   !events new_events
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__36_24(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 201: ... parameter_count_of(return)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* return */;
  result_count = 1;
  myself = get__parameter_count_of();
  func = myself->type;
  frame->cont = cont__36_25;
}
static void cont__36_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 201: ... parameter_count_of(return) == 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__36_26;
}
static void cont__36_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 201: ... : return undefined
  frame->slots[4] /* temp__3 */ = create_closure(entry__36_27, 0);
  // 201: if parameter_count_of(return) == 1: return undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__36_28;
}
static void entry__36_27(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 201: ... return undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__36_28(void) {
  myself = frame->slots[1] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__37_1_std__create_event(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // event: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 209: push &events event
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__events();
  arguments->slots[1] = frame->slots[0] /* event */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__37_2;
}
static void cont__37_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__events(arguments->slots[0]);
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__38_45(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // output_fd: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* output_fd */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 265: types::event(.type_of WRITE_TO .file_descriptor_of output_fd)
  {
    NODE *temp = clone_object_and_attributes(var.types__event);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__type_of, get__WRITE_TO());
    set_attribute_value(temp->attributes, poly_idx__file_descriptor_of, frame->slots[0] /* output_fd */);
    frame->slots[1] /* temp__1 */ = temp;

  }
  // 264: create_event
  // 265:   types::event(.type_of WRITE_TO .file_descriptor_of output_fd)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__create_event();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__38_43(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // output_fd: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 263: ... wanted_output_fds(output_fd)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* output_fd */;
  result_count = 1;
  myself = var._wanted_output_fds;
  func = myself->type;
  frame->cont = cont__38_44;
}
static void cont__38_44(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 263: ... :
  // 264:   create_event
  // 265:     types::event(.type_of WRITE_TO .file_descriptor_of output_fd)
  frame->slots[2] /* temp__2 */ = create_closure(entry__38_45, 0);
  // 263: if wanted_output_fds(output_fd):
  // 264:   create_event
  // 265:     types::event(.type_of WRITE_TO .file_descriptor_of output_fd)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__38_16(void) {
  allocate_initialized_frame_gc(5, 9);
  // slot allocations:
  // child_changed_state: 0
  // window_changed_size: 1
  // ready_input_fds_list: 2
  // ready_output_fds_list: 3
  // ready_exception_fds_list: 4
  // ready_input_fds_set: 5
  // ready_output_fds_set: 6
  // ready_exception_fds_set: 7
  frame->slots[0] = myself->closure.frame->slots[4]; /* child_changed_state */
  frame->slots[1] = myself->closure.frame->slots[5]; /* window_changed_size */
  frame->slots[2] = myself->closure.frame->slots[6]; /* ready_input_fds_list */
  frame->slots[3] = myself->closure.frame->slots[7]; /* ready_output_fds_list */
  frame->slots[4] = myself->closure.frame->slots[8]; /* ready_exception_fds_list */
  frame->slots[5] /* ready_input_fds_set */ = create_cell();
  frame->slots[6] /* ready_output_fds_set */ = create_cell();
  frame->slots[7] /* ready_exception_fds_set */ = create_cell();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 235: if child_changed_state:
  // 236:   do: (-> break)
  // 237:     forever:
  // 238:       wait_pid $status $pid -1 true
  // 239:       if pid <= 0 break
  // 240:       create_event
  // 241:         types::event(.type_of TERMINATED .pid_of pid .status_of status)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* child_changed_state */;
  arguments->slots[1] = func__38_17;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__38_26;
}
static void entry__38_18(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // break: 0
  frame->slots[0] /* break */ = create_continuation();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 237: ... :
  // 238:   wait_pid $status $pid -1 true
  // 239:   if pid <= 0 break
  // 240:   create_event
  // 241:     types::event(.type_of TERMINATED .pid_of pid .status_of status)
  frame->slots[1] /* temp__1 */ = create_closure(entry__38_19, 0);
  // 237: forever:
  // 238:   wait_pid $status $pid -1 true
  // 239:   if pid <= 0 break
  // 240:   create_event
  // 241:     types::event(.type_of TERMINATED .pid_of pid .status_of status)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__forever();
  func = myself->type;
  frame->cont = cont__38_25;
}
static void entry__38_19(void) {
  allocate_initialized_frame_gc(1, 6);
  // slot allocations:
  // break: 0
  // status: 1
  // pid: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* break */
  frame->slots[1] /* status */ = create_future();
  frame->slots[2] /* pid */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 238: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__38_20;
}
static void cont__38_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 238: wait_pid $status $pid -1 true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = get__true();
  result_count = 2;
  myself = get__wait_pid();
  func = myself->type;
  frame->cont = cont__38_21;
}
static void cont__38_21(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  frame->slots[5] /* temp__3 */ = arguments->slots[1];
  // 238: ... status
  initialize_future(frame->slots[1] /* status */, frame->slots[4] /* temp__2 */);
  // 238: ... pid
  initialize_future(frame->slots[2] /* pid */, frame->slots[5] /* temp__3 */);
  // 239: ... pid <= 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = frame->slots[2] /* pid */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__38_22;
}
static void cont__38_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 239: ... pid <= 0
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__38_23;
}
static void cont__38_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 239: if pid <= 0 break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[0] /* break */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__38_24;
}
static void cont__38_24(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 241: types::event(.type_of TERMINATED .pid_of pid .status_of status)
  {
    NODE *temp = clone_object_and_attributes(var.types__event);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__type_of, get__TERMINATED());
    set_attribute_value(temp->attributes, poly_idx__pid_of, frame->slots[2] /* pid */);
    set_attribute_value(temp->attributes, poly_idx__status_of, frame->slots[1] /* status */);
    frame->slots[3] /* temp__1 */ = temp;

  }
  // 240: create_event
  // 241:   types::event(.type_of TERMINATED .pid_of pid .status_of status)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__create_event();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__38_25(void) {
  myself = frame->slots[0] /* break */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__38_17(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 236: do: (-> break)
  // 237:   forever:
  // 238:     wait_pid $status $pid -1 true
  // 239:     if pid <= 0 break
  // 240:     create_event
  // 241:       types::event(.type_of TERMINATED .pid_of pid .status_of status)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__38_18;
  result_count = frame->caller_result_count;
  myself = get__do();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__38_26(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 242: if window_changed_size:
  // 243:   get_terminal_size STDIN_FILENO $width $height
  // 244:   create_event
  // 245:     types::event
  // 246:       .type_of SCREEN_SIZE_CHANGE
  // 247:       .width_of width
  // 248:       .height_of height
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* window_changed_size */;
  arguments->slots[1] = func__38_27;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__38_29;
}
static void entry__38_27(void) {
  allocate_initialized_frame_gc(0, 4);
  // slot allocations:
  // width: 0
  // height: 1
  frame->slots[0] /* width */ = create_future();
  frame->slots[1] /* height */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 243: get_terminal_size STDIN_FILENO $width $height
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__STDIN_FILENO();
  result_count = 2;
  myself = get__get_terminal_size();
  func = myself->type;
  frame->cont = cont__38_28;
}
static void cont__38_28(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  frame->slots[3] /* temp__2 */ = arguments->slots[1];
  // 243: ... width
  initialize_future(frame->slots[0] /* width */, frame->slots[2] /* temp__1 */);
  // 243: ... height
  initialize_future(frame->slots[1] /* height */, frame->slots[3] /* temp__2 */);
  // 245: types::event
  // 246:   .type_of SCREEN_SIZE_CHANGE
  // 247:   .width_of width
  // 248:   .height_of height
  {
    NODE *temp = clone_object_and_attributes(var.types__event);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__type_of, get__SCREEN_SIZE_CHANGE());
    set_attribute_value(temp->attributes, poly_idx__width_of, frame->slots[0] /* width */);
    set_attribute_value(temp->attributes, poly_idx__height_of, frame->slots[1] /* height */);
    frame->slots[2] /* temp__1 */ = temp;

  }
  // 244: create_event
  // 245:   types::event
  // 246:     .type_of SCREEN_SIZE_CHANGE
  // 247:     .width_of width
  // 248:     .height_of height
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__create_event();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__38_29(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 249: $$ready_input_fds_set empty_set
  ((CELL *)frame->slots[5])->contents /* ready_input_fds_set */ = get__empty_set();
  // 250: $$ready_output_fds_set empty_set
  ((CELL *)frame->slots[6])->contents /* ready_output_fds_set */ = get__empty_set();
  // 251: $$ready_exception_fds_set empty_set
  ((CELL *)frame->slots[7])->contents /* ready_exception_fds_set */ = get__empty_set();
  // 252: ... : (ready_input_fd)
  // 253:   !ready_input_fds_set(ready_input_fd) true
  frame->slots[8] /* temp__1 */ = create_closure(entry__38_30, 1);
  // 252: for_each ready_input_fds_list: (ready_input_fd)
  // 253:   !ready_input_fds_set(ready_input_fd) true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* ready_input_fds_list */;
  arguments->slots[1] = frame->slots[8] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__38_32;
}
static void entry__38_30(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // ready_input_fd: 0
  // ready_input_fds_set: 1
  frame->slots[1] = myself->closure.frame->slots[5]; /* ready_input_fds_set */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 253: !ready_input_fds_set(ready_input_fd) true
  frame->slots[2] /* temp__1 */ = get__true();
  // 253: !ready_input_fds_set(ready_input_fd)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* ready_input_fd */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[1])->contents /* ready_input_fds_set */;
  func = myself->type;
  frame->cont = cont__38_31;
}
static void cont__38_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* ready_input_fds_set */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__38_32(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 254: ... : (ready_output_fd)
  // 255:   !ready_output_fds_set(ready_output_fd) true
  frame->slots[8] /* temp__1 */ = create_closure(entry__38_33, 1);
  // 254: for_each ready_output_fds_list: (ready_output_fd)
  // 255:   !ready_output_fds_set(ready_output_fd) true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* ready_output_fds_list */;
  arguments->slots[1] = frame->slots[8] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__38_35;
}
static void entry__38_33(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // ready_output_fd: 0
  // ready_output_fds_set: 1
  frame->slots[1] = myself->closure.frame->slots[6]; /* ready_output_fds_set */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 255: !ready_output_fds_set(ready_output_fd) true
  frame->slots[2] /* temp__1 */ = get__true();
  // 255: !ready_output_fds_set(ready_output_fd)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* ready_output_fd */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[1])->contents /* ready_output_fds_set */;
  func = myself->type;
  frame->cont = cont__38_34;
}
static void cont__38_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* ready_output_fds_set */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__38_35(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 256: ... : (ready_exception_fd)
  // 257:   !ready_exception_fds_set(ready_exception_fd) true
  frame->slots[8] /* temp__1 */ = create_closure(entry__38_36, 1);
  // 256: for_each ready_exception_fds_list: (ready_exception_fd)
  // 257:   !ready_exception_fds_set(ready_exception_fd) true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* ready_exception_fds_list */;
  arguments->slots[1] = frame->slots[8] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__38_38;
}
static void entry__38_36(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // ready_exception_fd: 0
  // ready_exception_fds_set: 1
  frame->slots[1] = myself->closure.frame->slots[7]; /* ready_exception_fds_set */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 257: !ready_exception_fds_set(ready_exception_fd) true
  frame->slots[2] /* temp__1 */ = get__true();
  // 257: !ready_exception_fds_set(ready_exception_fd)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* ready_exception_fd */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[1])->contents /* ready_exception_fds_set */;
  func = myself->type;
  frame->cont = cont__38_37;
}
static void cont__38_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* ready_exception_fds_set */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__38_38(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 258: for_each ready_input_fds_set: (input_fd)
  // 259:   if wanted_input_fds(input_fd):
  // 260:     create_event
  // 261:       types::event(.type_of READ_FROM .file_descriptor_of input_fd)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[5])->contents /* ready_input_fds_set */;
  arguments->slots[1] = func__38_39;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__38_42;
}
static void entry__38_41(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // input_fd: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* input_fd */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 261: types::event(.type_of READ_FROM .file_descriptor_of input_fd)
  {
    NODE *temp = clone_object_and_attributes(var.types__event);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__type_of, get__READ_FROM());
    set_attribute_value(temp->attributes, poly_idx__file_descriptor_of, frame->slots[0] /* input_fd */);
    frame->slots[1] /* temp__1 */ = temp;

  }
  // 260: create_event
  // 261:   types::event(.type_of READ_FROM .file_descriptor_of input_fd)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__create_event();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__38_39(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // input_fd: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 259: ... wanted_input_fds(input_fd)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* input_fd */;
  result_count = 1;
  myself = var._wanted_input_fds;
  func = myself->type;
  frame->cont = cont__38_40;
}
static void cont__38_40(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 259: ... :
  // 260:   create_event
  // 261:     types::event(.type_of READ_FROM .file_descriptor_of input_fd)
  frame->slots[2] /* temp__2 */ = create_closure(entry__38_41, 0);
  // 259: if wanted_input_fds(input_fd):
  // 260:   create_event
  // 261:     types::event(.type_of READ_FROM .file_descriptor_of input_fd)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__38_42(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 262: for_each ready_output_fds_set: (output_fd)
  // 263:   if wanted_output_fds(output_fd):
  // 264:     create_event
  // 265:       types::event(.type_of WRITE_TO .file_descriptor_of output_fd)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[6])->contents /* ready_output_fds_set */;
  arguments->slots[1] = func__38_43;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__38_46(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 267: ... types::event(.type_of TIMEOUT)
  {
    NODE *temp = clone_object_and_attributes(var.types__event);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__type_of, get__TIMEOUT());
    frame->slots[0] /* temp__1 */ = temp;

  }
  // 267: create_event types::event(.type_of TIMEOUT)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__create_event();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__38_1_get_low_level_events(void) {
  allocate_initialized_frame_gc(1, 16);
  // slot allocations:
  // for_readers_and_writers_only: 0
  // output_fds_list: 1
  // input_fds_list: 2
  // exception_fds_list: 3
  // child_changed_state: 4
  // window_changed_size: 5
  // ready_input_fds_list: 6
  // ready_output_fds_list: 7
  // ready_exception_fds_list: 8
  frame->slots[1] /* output_fds_list */ = create_cell();
  frame->slots[2] /* input_fds_list */ = create_cell();
  // _define $exception_fds_list empty_list
  frame->slots[3] /* exception_fds_list */ = get_value_or_future__empty_list();
  frame->slots[4] /* child_changed_state */ = create_future();
  frame->slots[5] /* window_changed_size */ = create_future();
  frame->slots[6] /* ready_input_fds_list */ = create_future();
  frame->slots[7] /* ready_output_fds_list */ = create_future();
  frame->slots[8] /* ready_exception_fds_list */ = create_future();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 212: $$output_fds_list empty_list
  ((CELL *)frame->slots[1])->contents /* output_fds_list */ = get__empty_list();
  // 213: $$input_fds_list empty_list
  ((CELL *)frame->slots[2])->contents /* input_fds_list */ = get__empty_list();
  // 214: $exception_fds_list empty_list
  initialize_maybe_future(frame->slots[3] /* exception_fds_list */, get__empty_list());
  // 216: ... :
  // 217:   for_each writers: (output_fd _continuation)
  // 218:     push &output_fds_list output_fd
  // 219:   for_each readers: (input_fd _continuation) push &input_fds_list input_fd
  frame->slots[9] /* temp__1 */ = create_closure(entry__38_2, 0);
  // 220: :
  // 221:   for_each wanted_output_fds: (output_fd) push &output_fds_list output_fd
  // 222:   for_each wanted_input_fds: (input_fd) push &input_fds_list input_fd
  frame->slots[10] /* temp__2 */ = create_closure(entry__38_8, 0);
  // 215: if
  // 216:   for_readers_and_writers_only:
  // 217:     for_each writers: (output_fd _continuation)
  // 218:       push &output_fds_list output_fd
  // 219:     for_each readers: (input_fd _continuation) push &input_fds_list input_fd
  // 220:   :
  // 221:     for_each wanted_output_fds: (output_fd) push &output_fds_list output_fd
  // 222:     for_each wanted_input_fds: (input_fd) push &input_fds_list input_fd
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* for_readers_and_writers_only */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  arguments->slots[2] = frame->slots[10] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__38_14;
}
static void entry__38_12(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // input_fd: 0
  // input_fds_list: 1
  frame->slots[1] = myself->closure.frame->slots[1]; /* input_fds_list */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 222: ... push &input_fds_list input_fd
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* input_fds_list */;
  arguments->slots[1] = frame->slots[0] /* input_fd */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__38_13;
}
static void cont__38_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* input_fds_list */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__38_6(void) {
  allocate_initialized_frame_gc(3, 3);
  // slot allocations:
  // input_fd: 0
  // continuation: 1
  // input_fds_list: 2
  frame->slots[2] = myself->closure.frame->slots[1]; /* input_fds_list */
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 219: ... push &input_fds_list input_fd
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* input_fds_list */;
  arguments->slots[1] = frame->slots[0] /* input_fd */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__38_7;
}
static void cont__38_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* input_fds_list */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__38_2(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // output_fds_list: 0
  // input_fds_list: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* output_fds_list */
  frame->slots[1] = myself->closure.frame->slots[2]; /* input_fds_list */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 217: ... : (output_fd _continuation)
  // 218:   push &output_fds_list output_fd
  frame->slots[2] /* temp__1 */ = create_closure(entry__38_3, 2);
  // 217: for_each writers: (output_fd _continuation)
  // 218:   push &output_fds_list output_fd
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._writers;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__38_5;
}
static void entry__38_3(void) {
  allocate_initialized_frame_gc(3, 3);
  // slot allocations:
  // output_fd: 0
  // continuation: 1
  // output_fds_list: 2
  frame->slots[2] = myself->closure.frame->slots[0]; /* output_fds_list */
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 218: push &output_fds_list output_fd
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* output_fds_list */;
  arguments->slots[1] = frame->slots[0] /* output_fd */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__38_4;
}
static void cont__38_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* output_fds_list */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__38_5(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 219: ... : (input_fd _continuation) push &input_fds_list input_fd
  frame->slots[2] /* temp__1 */ = create_closure(entry__38_6, 2);
  // 219: for_each readers: (input_fd _continuation) push &input_fds_list input_fd
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._readers;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__38_8(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // output_fds_list: 0
  // input_fds_list: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* output_fds_list */
  frame->slots[1] = myself->closure.frame->slots[2]; /* input_fds_list */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 221: ... : (output_fd) push &output_fds_list output_fd
  frame->slots[2] /* temp__1 */ = create_closure(entry__38_9, 1);
  // 221: for_each wanted_output_fds: (output_fd) push &output_fds_list output_fd
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._wanted_output_fds;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__38_11;
}
static void entry__38_9(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // output_fd: 0
  // output_fds_list: 1
  frame->slots[1] = myself->closure.frame->slots[0]; /* output_fds_list */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 221: ... push &output_fds_list output_fd
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* output_fds_list */;
  arguments->slots[1] = frame->slots[0] /* output_fd */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__38_10;
}
static void cont__38_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* output_fds_list */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__38_11(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 222: ... : (input_fd) push &input_fds_list input_fd
  frame->slots[2] /* temp__1 */ = create_closure(entry__38_12, 1);
  // 222: for_each wanted_input_fds: (input_fd) push &input_fds_list input_fd
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._wanted_input_fds;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__38_14(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 224: wait_for_io
  // 225:   $child_changed_state
  // 226:   $window_changed_size
  // 227:   $ready_input_fds_list
  // 228:   input_fds_list
  // 229:   $ready_output_fds_list
  // 230:   output_fds_list
  // 231:   $ready_exception_fds_list
  // 232:   exception_fds_list
  // 233:   timeout
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* input_fds_list */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* output_fds_list */;
  arguments->slots[2] = frame->slots[3] /* exception_fds_list */;
  arguments->slots[3] = var._timeout;
  result_count = 6;
  myself = get__wait_for_io();
  func = myself->type;
  frame->cont = cont__38_15;
}
static void cont__38_15(void) {
  if (argument_count != 6) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__2 */ = arguments->slots[0];
  frame->slots[11] /* temp__3 */ = arguments->slots[1];
  frame->slots[12] /* temp__4 */ = arguments->slots[2];
  frame->slots[13] /* temp__5 */ = arguments->slots[3];
  frame->slots[14] /* temp__6 */ = arguments->slots[4];
  frame->slots[9] /* temp__1 */ = arguments->slots[5];
  // 225: ... child_changed_state
  initialize_future(frame->slots[4] /* child_changed_state */, frame->slots[10] /* temp__2 */);
  // 226: ... window_changed_size
  initialize_future(frame->slots[5] /* window_changed_size */, frame->slots[11] /* temp__3 */);
  // 227: ... ready_input_fds_list
  initialize_future(frame->slots[6] /* ready_input_fds_list */, frame->slots[12] /* temp__4 */);
  // 229: ... ready_output_fds_list
  initialize_future(frame->slots[7] /* ready_output_fds_list */, frame->slots[13] /* temp__5 */);
  // 231: ... ready_exception_fds_list
  initialize_future(frame->slots[8] /* ready_exception_fds_list */, frame->slots[14] /* temp__6 */);
  // 234: :
  // 235:   if child_changed_state:
  // 236:     do: (-> break)
  // 237:       forever:
  // 238:         wait_pid $status $pid -1 true
  // 239:         if pid <= 0 break
  // 240:         create_event
  // 241:           types::event(.type_of TERMINATED .pid_of pid .status_of status)
  // 242:   if window_changed_size:
  // 243:     get_terminal_size STDIN_FILENO $width $height
  // ...
  frame->slots[15] /* temp__7 */ = create_closure(entry__38_16, 0);
  // 223: if
  // 224:   wait_for_io
  // 225:     $child_changed_state
  // 226:     $window_changed_size
  // 227:     $ready_input_fds_list
  // 228:     input_fds_list
  // 229:     $ready_output_fds_list
  // 230:     output_fds_list
  // 231:     $ready_exception_fds_list
  // 232:     exception_fds_list
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  arguments->slots[1] = frame->slots[15] /* temp__7 */;
  arguments->slots[2] = func__38_46;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__39_1_get_event_handler(void) {
  allocate_initialized_frame_gc(2, 7);
  // slot allocations:
  // event: 0
  // return: 1
  frame->slots[1] /* return */ = create_continuation();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 275: type_of(event)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* event */;
  result_count = 1;
  myself = get__type_of();
  func = myself->type;
  frame->cont = cont__39_2;
}
static void cont__39_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 276: ... :
  // 277:   $fd file_descriptor_of(event)
  // 278:   $reader readers(fd)
  // 279:   if reader.is_defined:
  // 280:     no_longer_want_to_read_from fd
  // 281:     !readers(fd) undefined
  // 282:     return reader
  frame->slots[3] /* temp__2 */ = create_closure(entry__39_3, 0);
  // 283: ... :
  // 284:   $fd file_descriptor_of(event)
  // 285:   $writer writers(fd)
  // 286:   if writer.is_defined:
  // 287:     no_longer_want_to_write_to fd
  // 288:     !writers(fd) undefined
  // 289:     return writer
  frame->slots[4] /* temp__3 */ = create_closure(entry__39_10, 0);
  // 290: ... :
  // 291:   $pid pid_of(event)
  // 292:   $terminator terminators(pid)
  // 293:   if terminator.is_defined:
  // 294:     !terminators(pid) undefined
  // 295:     return terminator
  frame->slots[5] /* temp__4 */ = create_closure(entry__39_17, 0);
  // 296: ... :
  // 297:   return timeout_exceeded
  frame->slots[6] /* temp__5 */ = create_closure(entry__39_23, 0);
  // 274: case
  // 275:   type_of(event)
  // 276:   READ_FROM:
  // 277:     $fd file_descriptor_of(event)
  // 278:     $reader readers(fd)
  // 279:     if reader.is_defined:
  // 280:       no_longer_want_to_read_from fd
  // 281:       !readers(fd) undefined
  // 282:       return reader
  // 283:   WRITE_TO:
  // ...
  argument_count = 9;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = get__READ_FROM();
  arguments->slots[2] = frame->slots[3] /* temp__2 */;
  arguments->slots[3] = get__WRITE_TO();
  arguments->slots[4] = frame->slots[4] /* temp__3 */;
  arguments->slots[5] = get__TERMINATED();
  arguments->slots[6] = frame->slots[5] /* temp__4 */;
  arguments->slots[7] = get__TIMEOUT();
  arguments->slots[8] = frame->slots[6] /* temp__5 */;
  result_count = 0;
  myself = get__case();
  func = myself->type;
  frame->cont = cont__39_24;
}
static void entry__39_21(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // pid: 0
  // return: 1
  // terminator: 2
  frame->slots[0] = myself->closure.frame->slots[2]; /* pid */
  frame->slots[1] = myself->closure.frame->slots[1]; /* return */
  frame->slots[2] = myself->closure.frame->slots[3]; /* terminator */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 294: !terminators(pid) undefined
  frame->slots[3] /* temp__1 */ = get__undefined();
  // 294: !terminators(pid)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* pid */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = var._terminators;
  func = myself->type;
  frame->cont = cont__39_22;
}
static void cont__39_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._terminators = arguments->slots[0];
  // 295: return terminator
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* terminator */;
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__39_14(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // fd: 0
  // return: 1
  // writer: 2
  frame->slots[0] = myself->closure.frame->slots[2]; /* fd */
  frame->slots[1] = myself->closure.frame->slots[1]; /* return */
  frame->slots[2] = myself->closure.frame->slots[3]; /* writer */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 287: no_longer_want_to_write_to fd
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd */;
  result_count = 0;
  myself = get__no_longer_want_to_write_to();
  func = myself->type;
  frame->cont = cont__39_15;
}
static void cont__39_15(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 288: !writers(fd) undefined
  frame->slots[3] /* temp__1 */ = get__undefined();
  // 288: !writers(fd)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = var._writers;
  func = myself->type;
  frame->cont = cont__39_16;
}
static void cont__39_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._writers = arguments->slots[0];
  // 289: return writer
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* writer */;
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__39_7(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // fd: 0
  // return: 1
  // reader: 2
  frame->slots[0] = myself->closure.frame->slots[2]; /* fd */
  frame->slots[1] = myself->closure.frame->slots[1]; /* return */
  frame->slots[2] = myself->closure.frame->slots[3]; /* reader */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 280: no_longer_want_to_read_from fd
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd */;
  result_count = 0;
  myself = get__no_longer_want_to_read_from();
  func = myself->type;
  frame->cont = cont__39_8;
}
static void cont__39_8(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 281: !readers(fd) undefined
  frame->slots[3] /* temp__1 */ = get__undefined();
  // 281: !readers(fd)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = var._readers;
  func = myself->type;
  frame->cont = cont__39_9;
}
static void cont__39_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._readers = arguments->slots[0];
  // 282: return reader
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* reader */;
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__39_3(void) {
  allocate_initialized_frame_gc(2, 6);
  // slot allocations:
  // event: 0
  // return: 1
  // fd: 2
  // reader: 3
  frame->slots[0] = myself->closure.frame->slots[0]; /* event */
  frame->slots[1] = myself->closure.frame->slots[1]; /* return */
  frame->slots[2] /* fd */ = create_future();
  frame->slots[3] /* reader */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 277: $fd file_descriptor_of(event)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* event */;
  result_count = 1;
  myself = get__file_descriptor_of();
  func = myself->type;
  frame->cont = cont__39_4;
}
static void cont__39_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* fd */, arguments->slots[0]);
  // 278: $reader readers(fd)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* fd */;
  result_count = 1;
  myself = var._readers;
  func = myself->type;
  frame->cont = cont__39_5;
}
static void cont__39_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* reader */, arguments->slots[0]);
  // 279: ... reader.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* reader */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__39_6;
}
static void cont__39_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 279: ... :
  // 280:   no_longer_want_to_read_from fd
  // 281:   !readers(fd) undefined
  // 282:   return reader
  frame->slots[5] /* temp__2 */ = create_closure(entry__39_7, 0);
  // 279: if reader.is_defined:
  // 280:   no_longer_want_to_read_from fd
  // 281:   !readers(fd) undefined
  // 282:   return reader
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__39_10(void) {
  allocate_initialized_frame_gc(2, 6);
  // slot allocations:
  // event: 0
  // return: 1
  // fd: 2
  // writer: 3
  frame->slots[0] = myself->closure.frame->slots[0]; /* event */
  frame->slots[1] = myself->closure.frame->slots[1]; /* return */
  frame->slots[2] /* fd */ = create_future();
  frame->slots[3] /* writer */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 284: $fd file_descriptor_of(event)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* event */;
  result_count = 1;
  myself = get__file_descriptor_of();
  func = myself->type;
  frame->cont = cont__39_11;
}
static void cont__39_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* fd */, arguments->slots[0]);
  // 285: $writer writers(fd)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* fd */;
  result_count = 1;
  myself = var._writers;
  func = myself->type;
  frame->cont = cont__39_12;
}
static void cont__39_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* writer */, arguments->slots[0]);
  // 286: ... writer.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* writer */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__39_13;
}
static void cont__39_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 286: ... :
  // 287:   no_longer_want_to_write_to fd
  // 288:   !writers(fd) undefined
  // 289:   return writer
  frame->slots[5] /* temp__2 */ = create_closure(entry__39_14, 0);
  // 286: if writer.is_defined:
  // 287:   no_longer_want_to_write_to fd
  // 288:   !writers(fd) undefined
  // 289:   return writer
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__39_17(void) {
  allocate_initialized_frame_gc(2, 6);
  // slot allocations:
  // event: 0
  // return: 1
  // pid: 2
  // terminator: 3
  frame->slots[0] = myself->closure.frame->slots[0]; /* event */
  frame->slots[1] = myself->closure.frame->slots[1]; /* return */
  frame->slots[2] /* pid */ = create_future();
  frame->slots[3] /* terminator */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 291: $pid pid_of(event)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* event */;
  result_count = 1;
  myself = get__pid_of();
  func = myself->type;
  frame->cont = cont__39_18;
}
static void cont__39_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* pid */, arguments->slots[0]);
  // 292: $terminator terminators(pid)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* pid */;
  result_count = 1;
  myself = var._terminators;
  func = myself->type;
  frame->cont = cont__39_19;
}
static void cont__39_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* terminator */, arguments->slots[0]);
  // 293: ... terminator.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* terminator */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__39_20;
}
static void cont__39_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 293: ... :
  // 294:   !terminators(pid) undefined
  // 295:   return terminator
  frame->slots[5] /* temp__2 */ = create_closure(entry__39_21, 0);
  // 293: if terminator.is_defined:
  // 294:   !terminators(pid) undefined
  // 295:   return terminator
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__39_23(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 297: return timeout_exceeded
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._timeout_exceeded;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__39_24(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 298: -> undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  myself = frame->slots[1] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__40_1_std__get_event(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // return: 0
  frame->slots[0] /* return */ = create_continuation();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 314: ... : (myself^)
  // 315:   if
  // 316:     length_of(events) > 0:
  // 317:       $event get(&events)
  // 318:       $handler get_event_handler(event)
  // 319:       if handler.is_defined:
  // 320:         put &waiting_tasks myself
  // 321:         if
  // 322:           parameter_count_of(handler) == 1:
  // 323:             handler event
  // ...
  frame->slots[1] /* temp__1 */ = create_closure(entry__40_2, 0);
  // 314: forever: (myself^)
  // 315:   if
  // 316:     length_of(events) > 0:
  // 317:       $event get(&events)
  // 318:       $handler get_event_handler(event)
  // 319:       if handler.is_defined:
  // 320:         put &waiting_tasks myself
  // 321:         if
  // 322:           parameter_count_of(handler) == 1:
  // 323:             handler event
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__forever();
  func = myself->type;
  frame->cont = cont__40_19;
}
static void entry__40_5(void) {
  allocate_initialized_frame_gc(2, 6);
  // slot allocations:
  // myself: 0
  // return: 1
  // event: 2
  // handler: 3
  frame->slots[0] = myself->closure.frame->slots[0]; /* myself */
  frame->slots[1] = myself->closure.frame->slots[1]; /* return */
  frame->slots[2] /* event */ = create_future();
  frame->slots[3] /* handler */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 317: $event get(&events)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__events();
  result_count = 2;
  myself = get__get();
  func = myself->type;
  frame->cont = cont__40_6;
}
static void cont__40_6(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  set__events(arguments->slots[0]);
  frame->slots[4] /* temp__1 */ = arguments->slots[1];
  // 317: ... event
  initialize_future(frame->slots[2] /* event */, frame->slots[4] /* temp__1 */);
  // 318: $handler get_event_handler(event)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* event */;
  result_count = 1;
  myself = var._get_event_handler;
  func = myself->type;
  frame->cont = cont__40_7;
}
static void cont__40_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* handler */, arguments->slots[0]);
  // 319: ... handler.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* handler */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__40_8;
}
static void cont__40_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 319: ... :
  // 320:   put &waiting_tasks myself
  // 321:   if
  // 322:     parameter_count_of(handler) == 1:
  // 323:       handler event
  // 324:     :
  // 325:       handler
  // 326:   raise "invalid continuation"
  frame->slots[5] /* temp__2 */ = create_closure(entry__40_9, 0);
  // 319: if handler.is_defined:
  // 320:   put &waiting_tasks myself
  // 321:   if
  // 322:     parameter_count_of(handler) == 1:
  // 323:       handler event
  // 324:     :
  // 325:       handler
  // 326:   raise "invalid continuation"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__40_17;
}
static void entry__40_9(void) {
  allocate_initialized_frame_gc(3, 7);
  // slot allocations:
  // myself: 0
  // handler: 1
  // event: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* myself */
  frame->slots[1] = myself->closure.frame->slots[3]; /* handler */
  frame->slots[2] = myself->closure.frame->slots[2]; /* event */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 320: put &waiting_tasks myself
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._waiting_tasks;
  arguments->slots[1] = frame->slots[0] /* myself */;
  result_count = 1;
  myself = get__put();
  func = myself->type;
  frame->cont = cont__40_10;
}
static void cont__40_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._waiting_tasks = arguments->slots[0];
  // 322: parameter_count_of(handler)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* handler */;
  result_count = 1;
  myself = get__parameter_count_of();
  func = myself->type;
  frame->cont = cont__40_11;
}
static void cont__40_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 322: parameter_count_of(handler) == 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__40_12;
}
static void cont__40_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 322: ... :
  // 323:   handler event
  frame->slots[5] /* temp__3 */ = create_closure(entry__40_13, 0);
  // 324: :
  // 325:   handler
  frame->slots[6] /* temp__4 */ = create_closure(entry__40_14, 0);
  // 321: if
  // 322:   parameter_count_of(handler) == 1:
  // 323:     handler event
  // 324:   :
  // 325:     handler
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  arguments->slots[2] = frame->slots[6] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__40_15;
}
static void entry__40_13(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // handler: 0
  // event: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* handler */
  frame->slots[1] = myself->closure.frame->slots[2]; /* event */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 323: handler event
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* event */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* handler */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__40_14(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // handler: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* handler */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 325: handler
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* handler */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__40_15(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 326: raise "invalid continuation"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__40_16;
  result_count = frame->caller_result_count;
  myself = get__raise();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__40_17(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 327: return event
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* event */;
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__40_18(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 329: get_low_level_events false
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__false();
  result_count = frame->caller_result_count;
  myself = var._get_low_level_events;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__40_2(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // myself: 0
  // return: 1
  frame->slots[1] = myself->closure.frame->slots[0]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* myself */ = myself;
  // 316: length_of(events)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__events();
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__40_3;
}
static void cont__40_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 316: length_of(events) > 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__40_4;
}
static void cont__40_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 316: ... :
  // 317:   $event get(&events)
  // 318:   $handler get_event_handler(event)
  // 319:   if handler.is_defined:
  // 320:     put &waiting_tasks myself
  // 321:     if
  // 322:       parameter_count_of(handler) == 1:
  // 323:         handler event
  // 324:       :
  // 325:         handler
  // ...
  frame->slots[4] /* temp__3 */ = create_closure(entry__40_5, 0);
  // 315: if
  // 316:   length_of(events) > 0:
  // 317:     $event get(&events)
  // 318:     $handler get_event_handler(event)
  // 319:     if handler.is_defined:
  // 320:       put &waiting_tasks myself
  // 321:       if
  // 322:         parameter_count_of(handler) == 1:
  // 323:           handler event
  // 324:         :
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  arguments->slots[2] = func__40_18;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__40_19(void) {
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__42_13(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // i: 0
  // n: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* i */
  frame->slots[1] /* n */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 342: $n length_of(events)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__events();
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__42_14;
}
static void cont__42_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* n */, arguments->slots[0]);
  // 343: ... -> i <= n:
  // 344:   $event events(i)
  // 345:   $handler get_event_handler(event)
  // 346:   if handler.is_defined:
  // 347:     delete_at &events i
  // 348:     if
  // 349:       parameter_count_of(handler) == 1:
  // 350:         handler event
  // 351:       :
  // 352:         handler
  // ...
  frame->slots[2] /* temp__1 */ = create_closure(entry__42_15, 0);
  // 343: while -> i <= n:
  // 344:   $event events(i)
  // 345:   $handler get_event_handler(event)
  // 346:   if handler.is_defined:
  // 347:     delete_at &events i
  // 348:     if
  // 349:       parameter_count_of(handler) == 1:
  // 350:         handler event
  // 351:       :
  // 352:         handler
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__while();
  func = myself->type;
  frame->cont = cont__42_31;
}
static void entry__42_18(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // i: 0
  // event: 1
  // handler: 2
  frame->slots[0] = myself->closure.frame->slots[1]; /* i */
  frame->slots[1] /* event */ = create_future();
  frame->slots[2] /* handler */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 344: $event events(i)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* i */;
  result_count = 1;
  myself = get__events();
  func = myself->type;
  frame->cont = cont__42_19;
}
static void cont__42_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* event */, arguments->slots[0]);
  // 345: $handler get_event_handler(event)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* event */;
  result_count = 1;
  myself = var._get_event_handler;
  func = myself->type;
  frame->cont = cont__42_20;
}
static void cont__42_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* handler */, arguments->slots[0]);
  // 346: ... handler.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* handler */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__42_21;
}
static void cont__42_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 346: ... :
  // 347:   delete_at &events i
  // 348:   if
  // 349:     parameter_count_of(handler) == 1:
  // 350:       handler event
  // 351:     :
  // 352:       handler
  // 353:   raise "invalid continuation"
  frame->slots[4] /* temp__2 */ = create_closure(entry__42_22, 0);
  // 346: if handler.is_defined:
  // 347:   delete_at &events i
  // 348:   if
  // 349:     parameter_count_of(handler) == 1:
  // 350:       handler event
  // 351:     :
  // 352:       handler
  // 353:   raise "invalid continuation"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__42_29;
}
static void entry__42_22(void) {
  allocate_initialized_frame_gc(3, 7);
  // slot allocations:
  // i: 0
  // handler: 1
  // event: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* i */
  frame->slots[1] = myself->closure.frame->slots[2]; /* handler */
  frame->slots[2] = myself->closure.frame->slots[1]; /* event */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 347: delete_at &events i
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__events();
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* i */;
  result_count = 1;
  myself = get__delete_at();
  func = myself->type;
  frame->cont = cont__42_23;
}
static void cont__42_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__events(arguments->slots[0]);
  // 349: parameter_count_of(handler)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* handler */;
  result_count = 1;
  myself = get__parameter_count_of();
  func = myself->type;
  frame->cont = cont__42_24;
}
static void cont__42_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 349: parameter_count_of(handler) == 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__42_25;
}
static void cont__42_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 349: ... :
  // 350:   handler event
  frame->slots[5] /* temp__3 */ = create_closure(entry__42_26, 0);
  // 351: :
  // 352:   handler
  frame->slots[6] /* temp__4 */ = create_closure(entry__42_27, 0);
  // 348: if
  // 349:   parameter_count_of(handler) == 1:
  // 350:     handler event
  // 351:   :
  // 352:     handler
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  arguments->slots[2] = frame->slots[6] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__42_28;
}
static void entry__42_26(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // handler: 0
  // event: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* handler */
  frame->slots[1] = myself->closure.frame->slots[2]; /* event */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 350: handler event
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* event */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* handler */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__42_27(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // handler: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* handler */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 352: handler
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* handler */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__42_28(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 353: raise "invalid continuation"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__40_16;
  result_count = frame->caller_result_count;
  myself = get__raise();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__42_29(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 354: inc &i
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* i */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__42_30;
}
static void cont__42_30(void) {
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
static void entry__42_15(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // n: 0
  // i: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* n */
  frame->slots[1] = myself->closure.frame->slots[0]; /* i */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 343: ... i <= n
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* n */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* i */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__42_16;
}
static void cont__42_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 343: ... i <= n
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__42_17;
}
static void cont__42_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 343: ... :
  // 344:   $event events(i)
  // 345:   $handler get_event_handler(event)
  // 346:   if handler.is_defined:
  // 347:     delete_at &events i
  // 348:     if
  // 349:       parameter_count_of(handler) == 1:
  // 350:         handler event
  // 351:       :
  // 352:         handler
  // ...
  frame->slots[4] /* temp__3 */ = create_closure(entry__42_18, 0);
  // 343: ... -> i <= n:
  // 344:   $event events(i)
  // 345:   $handler get_event_handler(event)
  // 346:   if handler.is_defined:
  // 347:     delete_at &events i
  // 348:     if
  // 349:       parameter_count_of(handler) == 1:
  // 350:         handler event
  // 351:       :
  // 352:         handler
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__42_31(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 355: get_low_level_events true
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__true();
  result_count = frame->caller_result_count;
  myself = var._get_low_level_events;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__42_1_std__process_events(void) {
  allocate_initialized_frame_gc(0, 3);
  // slot allocations:
  // i: 0
  frame->slots[0] /* i */ = create_cell();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 338: while -> length_of(waiting_tasks) > 0: get(&waiting_tasks)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__42_2;
  result_count = 0;
  myself = get__while();
  func = myself->type;
  frame->cont = cont__42_7;
}
static void entry__42_5(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 338: ... get(&waiting_tasks)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._waiting_tasks;
  result_count = 2;
  myself = get__get();
  func = myself->type;
  frame->cont = cont__42_6;
}
static void cont__42_6(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  var._waiting_tasks = arguments->slots[0];
  frame->slots[0] /* temp__1 */ = arguments->slots[1];
  // 338: ... get(&waiting_tasks)
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* temp__1 */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__42_2(void) {
  allocate_initialized_frame_gc(0, 2);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 338: ... length_of(waiting_tasks)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._waiting_tasks;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__42_3;
}
static void cont__42_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 338: ... length_of(waiting_tasks) > 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__42_4;
}
static void cont__42_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 338: ... -> length_of(waiting_tasks) > 0: get(&waiting_tasks)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = func__42_5;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__42_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 339: ... readers.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._readers;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__42_8;
}
static void cont__42_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 339: ... readers.is_empty && writers.is_empty
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = func__42_9;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__42_11;
}
static void entry__42_9(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 339: ... writers.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._writers;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__42_10;
}
static void cont__42_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 339: ... writers.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__42_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 339: if readers.is_empty && writers.is_empty terminate
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = get__terminate();
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__42_12;
}
static void cont__42_12(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 340: $$i 1
  ((CELL *)frame->slots[0])->contents /* i */ = number__1;
  // 341: ... :
  // 342:   $n length_of(events)
  // 343:   while -> i <= n:
  // 344:     $event events(i)
  // 345:     $handler get_event_handler(event)
  // 346:     if handler.is_defined:
  // 347:       delete_at &events i
  // 348:       if
  // 349:         parameter_count_of(handler) == 1:
  // 350:           handler event
  // ...
  frame->slots[1] /* temp__1 */ = create_closure(entry__42_13, 0);
  // 341: forever:
  // 342:   $n length_of(events)
  // 343:   while -> i <= n:
  // 344:     $event events(i)
  // 345:     $handler get_event_handler(event)
  // 346:     if handler.is_defined:
  // 347:       delete_at &events i
  // 348:       if
  // 349:         parameter_count_of(handler) == 1:
  // 350:           handler event
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__forever();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__43_1_std__wait_to(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // args: 0
  // event: 1
  frame->slots[1] /* event */ = create_future();
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 368: ... : (-> continuation)
  // 369:   for_each args: (arg)
  // 370:     $type key_of(arg)
  // 371:     $value value_of(arg)
  // 372:     case
  // 373:       type
  // 374:       READ_FROM:
  // 375:         want_to_read_from value
  // 376:         !readers(value) continuation
  // 377:       WRITE_TO:
  // ...
  frame->slots[2] /* temp__1 */ = create_closure(entry__43_2, 0);
  // 368: do $event: (-> continuation)
  // 369:   for_each args: (arg)
  // 370:     $type key_of(arg)
  // 371:     $value value_of(arg)
  // 372:     case
  // 373:       type
  // 374:       READ_FROM:
  // 375:         want_to_read_from value
  // 376:         !readers(value) continuation
  // 377:       WRITE_TO:
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__43_17;
}
static void entry__43_2(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // continuation: 0
  // args: 1
  frame->slots[0] /* continuation */ = create_continuation();
  frame->slots[1] = myself->closure.frame->slots[0]; /* args */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 369: ... : (arg)
  // 370:   $type key_of(arg)
  // 371:   $value value_of(arg)
  // 372:   case
  // 373:     type
  // 374:     READ_FROM:
  // 375:       want_to_read_from value
  // 376:       !readers(value) continuation
  // 377:     WRITE_TO:
  // 378:       want_to_write_to value
  // ...
  frame->slots[2] /* temp__1 */ = create_closure(entry__43_3, 1);
  // 369: for_each args: (arg)
  // 370:   $type key_of(arg)
  // 371:   $value value_of(arg)
  // 372:   case
  // 373:     type
  // 374:     READ_FROM:
  // 375:       want_to_read_from value
  // 376:       !readers(value) continuation
  // 377:     WRITE_TO:
  // 378:       want_to_write_to value
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* args */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__43_15;
}
static void entry__43_6(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // value: 0
  // continuation: 1
  frame->slots[0] = myself->closure.frame->slots[3]; /* value */
  frame->slots[1] = myself->closure.frame->slots[1]; /* continuation */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 375: want_to_read_from value
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* value */;
  result_count = 0;
  myself = get__want_to_read_from();
  func = myself->type;
  frame->cont = cont__43_7;
}
static void cont__43_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 376: !readers(value) continuation
  frame->slots[2] /* temp__1 */ = frame->slots[1] /* continuation */;
  // 376: !readers(value)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* value */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = var._readers;
  func = myself->type;
  frame->cont = cont__43_8;
}
static void cont__43_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._readers = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__43_9(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // value: 0
  // continuation: 1
  frame->slots[0] = myself->closure.frame->slots[3]; /* value */
  frame->slots[1] = myself->closure.frame->slots[1]; /* continuation */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 378: want_to_write_to value
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* value */;
  result_count = 0;
  myself = get__want_to_write_to();
  func = myself->type;
  frame->cont = cont__43_10;
}
static void cont__43_10(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 379: !writers(value) continuation
  frame->slots[2] /* temp__1 */ = frame->slots[1] /* continuation */;
  // 379: !writers(value)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* value */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = var._writers;
  func = myself->type;
  frame->cont = cont__43_11;
}
static void cont__43_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._writers = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__43_12(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // value: 0
  // continuation: 1
  frame->slots[0] = myself->closure.frame->slots[3]; /* value */
  frame->slots[1] = myself->closure.frame->slots[1]; /* continuation */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 381: !terminators(value) continuation
  frame->slots[2] /* temp__1 */ = frame->slots[1] /* continuation */;
  // 381: !terminators(value)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* value */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = var._terminators;
  func = myself->type;
  frame->cont = cont__43_13;
}
static void cont__43_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._terminators = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__43_14(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // value: 0
  // continuation: 1
  frame->slots[0] = myself->closure.frame->slots[3]; /* value */
  frame->slots[1] = myself->closure.frame->slots[1]; /* continuation */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 383: !timeout value
  var._timeout = frame->slots[0] /* value */;
  // 384: !timeout_exceeded continuation
  var._timeout_exceeded = frame->slots[1] /* continuation */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__43_3(void) {
  allocate_initialized_frame_gc(2, 8);
  // slot allocations:
  // arg: 0
  // continuation: 1
  // type: 2
  // value: 3
  frame->slots[1] = myself->closure.frame->slots[0]; /* continuation */
  frame->slots[2] /* type */ = create_future();
  frame->slots[3] /* value */ = create_future();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 370: $type key_of(arg)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* arg */;
  result_count = 1;
  myself = get__key_of();
  func = myself->type;
  frame->cont = cont__43_4;
}
static void cont__43_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* type */, arguments->slots[0]);
  // 371: $value value_of(arg)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* arg */;
  result_count = 1;
  myself = get__value_of();
  func = myself->type;
  frame->cont = cont__43_5;
}
static void cont__43_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* value */, arguments->slots[0]);
  // 374: ... :
  // 375:   want_to_read_from value
  // 376:   !readers(value) continuation
  frame->slots[4] /* temp__1 */ = create_closure(entry__43_6, 0);
  // 377: ... :
  // 378:   want_to_write_to value
  // 379:   !writers(value) continuation
  frame->slots[5] /* temp__2 */ = create_closure(entry__43_9, 0);
  // 380: ... :
  // 381:   !terminators(value) continuation
  frame->slots[6] /* temp__3 */ = create_closure(entry__43_12, 0);
  // 382: ... :
  // 383:   !timeout value
  // 384:   !timeout_exceeded continuation
  frame->slots[7] /* temp__4 */ = create_closure(entry__43_14, 0);
  // 372: case
  // 373:   type
  // 374:   READ_FROM:
  // 375:     want_to_read_from value
  // 376:     !readers(value) continuation
  // 377:   WRITE_TO:
  // 378:     want_to_write_to value
  // 379:     !writers(value) continuation
  // 380:   TERMINATED:
  // 381:     !terminators(value) continuation
  // ...
  argument_count = 9;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* type */;
  arguments->slots[1] = get__READ_FROM();
  arguments->slots[2] = frame->slots[4] /* temp__1 */;
  arguments->slots[3] = get__WRITE_TO();
  arguments->slots[4] = frame->slots[5] /* temp__2 */;
  arguments->slots[5] = get__TERMINATED();
  arguments->slots[6] = frame->slots[6] /* temp__3 */;
  arguments->slots[7] = get__TIMEOUT();
  arguments->slots[8] = frame->slots[7] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__43_15(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 385: process_events # will never return directly
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = get__process_events();
  func = myself->type;
  frame->cont = cont__43_16;
}
static void cont__43_16(void) {
  myself = frame->slots[0] /* continuation */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__43_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* event */, arguments->slots[0]);
  // 386: for_each args: (arg)
  // 387:   $type key_of(arg)
  // 388:   $value value_of(arg)
  // 389:   case
  // 390:     type
  // 391:     READ_FROM:
  // 392:       no_longer_want_to_read_from value
  // 393:       !readers(value) undefined
  // 394:     WRITE_TO:
  // 395:       no_longer_want_to_write_to value
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* args */;
  arguments->slots[1] = func__43_18;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__43_29;
}
static void entry__43_21(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // value: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* value */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 392: no_longer_want_to_read_from value
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* value */;
  result_count = 0;
  myself = get__no_longer_want_to_read_from();
  func = myself->type;
  frame->cont = cont__43_22;
}
static void cont__43_22(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 393: !readers(value) undefined
  frame->slots[1] /* temp__1 */ = get__undefined();
  // 393: !readers(value)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* value */;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = var._readers;
  func = myself->type;
  frame->cont = cont__43_23;
}
static void cont__43_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._readers = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__43_24(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // value: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* value */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 395: no_longer_want_to_write_to value
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* value */;
  result_count = 0;
  myself = get__no_longer_want_to_write_to();
  func = myself->type;
  frame->cont = cont__43_25;
}
static void cont__43_25(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 396: !writers(value) undefined
  frame->slots[1] /* temp__1 */ = get__undefined();
  // 396: !writers(value)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* value */;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = var._writers;
  func = myself->type;
  frame->cont = cont__43_26;
}
static void cont__43_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._writers = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__43_27(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // value: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* value */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 398: !terminators(value) undefined
  frame->slots[1] /* temp__1 */ = get__undefined();
  // 398: !terminators(value)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* value */;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = var._terminators;
  func = myself->type;
  frame->cont = cont__43_28;
}
static void cont__43_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._terminators = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__43_18(void) {
  allocate_initialized_frame_gc(1, 6);
  // slot allocations:
  // arg: 0
  // type: 1
  // value: 2
  frame->slots[1] /* type */ = create_future();
  frame->slots[2] /* value */ = create_future();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 387: $type key_of(arg)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* arg */;
  result_count = 1;
  myself = get__key_of();
  func = myself->type;
  frame->cont = cont__43_19;
}
static void cont__43_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* type */, arguments->slots[0]);
  // 388: $value value_of(arg)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* arg */;
  result_count = 1;
  myself = get__value_of();
  func = myself->type;
  frame->cont = cont__43_20;
}
static void cont__43_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* value */, arguments->slots[0]);
  // 391: ... :
  // 392:   no_longer_want_to_read_from value
  // 393:   !readers(value) undefined
  frame->slots[3] /* temp__1 */ = create_closure(entry__43_21, 0);
  // 394: ... :
  // 395:   no_longer_want_to_write_to value
  // 396:   !writers(value) undefined
  frame->slots[4] /* temp__2 */ = create_closure(entry__43_24, 0);
  // 397: ... :
  // 398:   !terminators(value) undefined
  frame->slots[5] /* temp__3 */ = create_closure(entry__43_27, 0);
  // 389: case
  // 390:   type
  // 391:   READ_FROM:
  // 392:     no_longer_want_to_read_from value
  // 393:     !readers(value) undefined
  // 394:   WRITE_TO:
  // 395:     no_longer_want_to_write_to value
  // 396:     !writers(value) undefined
  // 397:   TERMINATED:
  // 398:     !terminators(value) undefined
  argument_count = 7;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* type */;
  arguments->slots[1] = get__READ_FROM();
  arguments->slots[2] = frame->slots[3] /* temp__1 */;
  arguments->slots[3] = get__WRITE_TO();
  arguments->slots[4] = frame->slots[4] /* temp__2 */;
  arguments->slots[5] = get__TERMINATED();
  arguments->slots[6] = frame->slots[5] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__43_29(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 399: !timeout undefined
  var._timeout = get__undefined();
  // 400: !timeout_exceeded undefined
  var._timeout_exceeded = get__undefined();
  // 401: -> event
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* event */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__44_1_std__par(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // tasks: 0
  frame->slots[0] /* tasks */ = from_arguments(0, argument_count-0);
  // 404: append &waiting_tasks tasks
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._waiting_tasks;
  arguments->slots[1] = frame->slots[0] /* tasks */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__44_2;
}
static void cont__44_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._waiting_tasks = arguments->slots[0];
  // 405: process_events
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = get__process_events();
  func = myself->type;
  frame = frame->caller_frame;
}
EXPORT void collect__basic__event(void) {
  var.std__WRITE_TO = collect_node(var.std__WRITE_TO);
  var.std__READ_FROM = collect_node(var.std__READ_FROM);
  var.std__file_descriptor_of = collect_node(var.std__file_descriptor_of);
  var.std__TERMINATED = collect_node(var.std__TERMINATED);
  var.std__pid_of = collect_node(var.std__pid_of);
  var.std__status_of = collect_node(var.std__status_of);
  var.std__TIMEOUT = collect_node(var.std__TIMEOUT);
  var.std__timeout_of = collect_node(var.std__timeout_of);
  var.std__SCREEN_SIZE_CHANGE = collect_node(var.std__SCREEN_SIZE_CHANGE);
  var.std__width_of = collect_node(var.std__width_of);
  var.std__height_of = collect_node(var.std__height_of);
  var.std__KEY_PRESS = collect_node(var.std__KEY_PRESS);
  var.std__key_code_of = collect_node(var.std__key_code_of);
  var.std__MOUSE_CLICK = collect_node(var.std__MOUSE_CLICK);
  var.std__target_of = collect_node(var.std__target_of);
  var.std__PASTE = collect_node(var.std__PASTE);
  var.std__MESSAGE = collect_node(var.std__MESSAGE);
  var.types__event = collect_node(var.types__event);
  var.std__events = collect_node(var.std__events);
  var._wanted_output_fds = collect_node(var._wanted_output_fds);
  var._wanted_input_fds = collect_node(var._wanted_input_fds);
  var.std__want_to_write_to = collect_node(var.std__want_to_write_to);
  var.std__no_longer_want_to_write_to = collect_node(var.std__no_longer_want_to_write_to);
  var.std__want_to_read_from = collect_node(var.std__want_to_read_from);
  var.std__no_longer_want_to_read_from = collect_node(var.std__no_longer_want_to_read_from);
  var.std__wanting_to_write_to = collect_node(var.std__wanting_to_write_to);
  var.std__wanting_to_read_from = collect_node(var.std__wanting_to_read_from);
  var._readers = collect_node(var._readers);
  var.std__wait_to_read_from = collect_node(var.std__wait_to_read_from);
  var._writers = collect_node(var._writers);
  var.std__wait_to_write_to = collect_node(var.std__wait_to_write_to);
  var._terminators = collect_node(var._terminators);
  var.std__wait_for_termination = collect_node(var.std__wait_for_termination);
  var._timeout = collect_node(var._timeout);
  var._timeout_exceeded = collect_node(var._timeout_exceeded);
  var.std__discard = collect_node(var.std__discard);
  var.std__create_event = collect_node(var.std__create_event);
  var._get_low_level_events = collect_node(var._get_low_level_events);
  var._get_event_handler = collect_node(var._get_event_handler);
  var.std__get_event = collect_node(var.std__get_event);
  var._waiting_tasks = collect_node(var._waiting_tasks);
  var.std__process_events = collect_node(var.std__process_events);
  var.std__wait_to = collect_node(var.std__wait_to);
  var.std__par = collect_node(var.std__par);
}

static int already_run_phase_1 = false;

EXPORT void phase_1__basic__event(void) {
  if (already_run_phase_1) return;
  already_run_phase_1 = true;
  register_module_info(&module_info);
  define_polymorphic_function_with_setter("std", "file_descriptor_of", get__std__file_descriptor_of, &poly_idx__std__file_descriptor_of, &var.std__file_descriptor_of);
  define_polymorphic_function_with_setter("std", "pid_of", get__std__pid_of, &poly_idx__std__pid_of, &var.std__pid_of);
  define_polymorphic_function_with_setter("std", "status_of", get__std__status_of, &poly_idx__std__status_of, &var.std__status_of);
  define_polymorphic_function_with_setter("std", "timeout_of", get__std__timeout_of, &poly_idx__std__timeout_of, &var.std__timeout_of);
  define_polymorphic_function_with_setter("std", "width_of", get__std__width_of, &poly_idx__std__width_of, &var.std__width_of);
  define_polymorphic_function_with_setter("std", "height_of", get__std__height_of, &poly_idx__std__height_of, &var.std__height_of);
  define_polymorphic_function_with_setter("std", "key_code_of", get__std__key_code_of, &poly_idx__std__key_code_of, &var.std__key_code_of);
  define_polymorphic_function_with_setter("std", "target_of", get__std__target_of, &poly_idx__std__target_of, &var.std__target_of);
}

static int already_run_phase_2 = false;

EXPORT void phase_2__basic__event(void) {
  if (already_run_phase_2) return;
  already_run_phase_2 = true;
  number__0 = from_uint32(0U);
  number__1 = from_uint32(1U);
  unique__std__WRITE_TO = register_unique_item("std__WRITE_TO");
  unique__std__READ_FROM = register_unique_item("std__READ_FROM");
  unique__std__TERMINATED = register_unique_item("std__TERMINATED");
  unique__std__TIMEOUT = register_unique_item("std__TIMEOUT");
  unique__std__SCREEN_SIZE_CHANGE = register_unique_item("std__SCREEN_SIZE_CHANGE");
  unique__std__KEY_PRESS = register_unique_item("std__KEY_PRESS");
  unique__std__MOUSE_CLICK = register_unique_item("std__MOUSE_CLICK");
  unique__std__PASTE = register_unique_item("std__PASTE");
  unique__std__MESSAGE = register_unique_item("std__MESSAGE");
  func__22_1_std__want_to_write_to = create_function(entry__22_1_std__want_to_write_to, 1);
  func__23_1_std__no_longer_want_to_write_to = create_function(entry__23_1_std__no_longer_want_to_write_to, 1);
  func__24_1_std__want_to_read_from = create_function(entry__24_1_std__want_to_read_from, 1);
  func__25_1_std__no_longer_want_to_read_from = create_function(entry__25_1_std__no_longer_want_to_read_from, 1);
  func__26_1_std__wanting_to_write_to = create_function(entry__26_1_std__wanting_to_write_to, 1);
  func__27_1_std__wanting_to_read_from = create_function(entry__27_1_std__wanting_to_read_from, 1);
  func__29_1_std__wait_to_read_from = create_function(entry__29_1_std__wait_to_read_from, 1);
  func__31_1_std__wait_to_write_to = create_function(entry__31_1_std__wait_to_write_to, 1);
  func__33_1_std__wait_for_termination = create_function(entry__33_1_std__wait_for_termination, 1);
  func__36_1_std__discard = create_function(entry__36_1_std__discard, 1);
  func__37_1_std__create_event = create_function(entry__37_1_std__create_event, 1);
  func__38_18 = create_function(entry__38_18, 0);
  func__38_17 = create_function(entry__38_17, 0);
  func__38_27 = create_function(entry__38_27, 0);
  func__38_39 = create_function(entry__38_39, 1);
  func__38_43 = create_function(entry__38_43, 1);
  func__38_46 = create_function(entry__38_46, 0);
  func__38_1_get_low_level_events = create_function(entry__38_1_get_low_level_events, 1);
  func__39_1_get_event_handler = create_function(entry__39_1_get_event_handler, 1);
  string__40_16 = from_latin_1_string("invalid continuation", 20);
  func__40_18 = create_function(entry__40_18, 0);
  func__40_1_std__get_event = create_function(entry__40_1_std__get_event, 0);
  func__42_5 = create_function(entry__42_5, 0);
  func__42_2 = create_function(entry__42_2, 0);
  func__42_9 = create_function(entry__42_9, 0);
  func__42_1_std__process_events = create_function(entry__42_1_std__process_events, 0);
  func__43_18 = create_function(entry__43_18, 1);
  func__43_1_std__wait_to = create_function(entry__43_1_std__wait_to, -1);
  func__44_1_std__par = create_function(entry__44_1_std__par, -1);
}

static int already_run_phase_3 = false;

EXPORT void phase_3__basic__event(void) {
  if (already_run_phase_3) return;
  already_run_phase_3 = true;
  set_module("basic__event");
  set_used_namespaces(used_namespaces);
  assign_value(&var.std__WRITE_TO, unique__std__WRITE_TO);
  define_single_assign_static("std", "WRITE_TO", get__std__WRITE_TO, &var.std__WRITE_TO);
  assign_value(&var.std__READ_FROM, unique__std__READ_FROM);
  define_single_assign_static("std", "READ_FROM", get__std__READ_FROM, &var.std__READ_FROM);
  assign_value(&var.std__TERMINATED, unique__std__TERMINATED);
  define_single_assign_static("std", "TERMINATED", get__std__TERMINATED, &var.std__TERMINATED);
  assign_value(&var.std__TIMEOUT, unique__std__TIMEOUT);
  define_single_assign_static("std", "TIMEOUT", get__std__TIMEOUT, &var.std__TIMEOUT);
  assign_value(&var.std__SCREEN_SIZE_CHANGE, unique__std__SCREEN_SIZE_CHANGE);
  define_single_assign_static("std", "SCREEN_SIZE_CHANGE", get__std__SCREEN_SIZE_CHANGE, &var.std__SCREEN_SIZE_CHANGE);
  assign_value(&var.std__KEY_PRESS, unique__std__KEY_PRESS);
  define_single_assign_static("std", "KEY_PRESS", get__std__KEY_PRESS, &var.std__KEY_PRESS);
  assign_value(&var.std__MOUSE_CLICK, unique__std__MOUSE_CLICK);
  define_single_assign_static("std", "MOUSE_CLICK", get__std__MOUSE_CLICK, &var.std__MOUSE_CLICK);
  assign_value(&var.std__PASTE, unique__std__PASTE);
  define_single_assign_static("std", "PASTE", get__std__PASTE, &var.std__PASTE);
  assign_value(&var.std__MESSAGE, unique__std__MESSAGE);
  define_single_assign_static("std", "MESSAGE", get__std__MESSAGE, &var.std__MESSAGE);
  define_single_assign_static("types", "event", get__types__event, &var.types__event);
  define_multi_assign_static("std", "events", get__std__events, set__std__events);
  define_single_assign_static("std", "want_to_write_to", get__std__want_to_write_to, &var.std__want_to_write_to);
  define_single_assign_static("std", "no_longer_want_to_write_to", get__std__no_longer_want_to_write_to, &var.std__no_longer_want_to_write_to);
  define_single_assign_static("std", "want_to_read_from", get__std__want_to_read_from, &var.std__want_to_read_from);
  define_single_assign_static("std", "no_longer_want_to_read_from", get__std__no_longer_want_to_read_from, &var.std__no_longer_want_to_read_from);
  define_single_assign_static("std", "wanting_to_write_to", get__std__wanting_to_write_to, &var.std__wanting_to_write_to);
  define_single_assign_static("std", "wanting_to_read_from", get__std__wanting_to_read_from, &var.std__wanting_to_read_from);
  define_single_assign_static("std", "wait_to_read_from", get__std__wait_to_read_from, &var.std__wait_to_read_from);
  define_single_assign_static("std", "wait_to_write_to", get__std__wait_to_write_to, &var.std__wait_to_write_to);
  define_single_assign_static("std", "wait_for_termination", get__std__wait_for_termination, &var.std__wait_for_termination);
  define_single_assign_static("std", "discard", get__std__discard, &var.std__discard);
  define_single_assign_static("std", "create_event", get__std__create_event, &var.std__create_event);
  define_single_assign_static("std", "get_event", get__std__get_event, &var.std__get_event);
  define_single_assign_static("std", "process_events", get__std__process_events, &var.std__process_events);
  define_single_assign_static("std", "wait_to", get__std__wait_to, &var.std__wait_to);
  define_single_assign_static("std", "par", get__std__par, &var.std__par);
}

static int already_run_phase_4 = false;

EXPORT void phase_4__basic__event(void) {
  if (already_run_phase_4) return;
  already_run_phase_4 = true;
  set_module("basic__event");
  set_used_namespaces(used_namespaces);
  use_read_only(NULL, "READ_FROM", &get__READ_FROM, &get_value_or_future__READ_FROM);
  use_read_only(NULL, "SCREEN_SIZE_CHANGE", &get__SCREEN_SIZE_CHANGE, &get_value_or_future__SCREEN_SIZE_CHANGE);
  use_read_only(NULL, "STDIN_FILENO", &get__STDIN_FILENO, &get_value_or_future__STDIN_FILENO);
  use_read_only(NULL, "TERMINATED", &get__TERMINATED, &get_value_or_future__TERMINATED);
  use_read_only(NULL, "TIMEOUT", &get__TIMEOUT, &get_value_or_future__TIMEOUT);
  use_read_only(NULL, "WRITE_TO", &get__WRITE_TO, &get_value_or_future__WRITE_TO);
  use_read_only(NULL, "append", &get__append, &get_value_or_future__append);
  use_read_only(NULL, "case", &get__case, &get_value_or_future__case);
  use_read_only(NULL, "close", &get__close, &get_value_or_future__close);
  use_read_only(NULL, "create_event", &get__create_event, &get_value_or_future__create_event);
  use_read_only(NULL, "delete_at", &get__delete_at, &get_value_or_future__delete_at);
  use_read_only(NULL, "do", &get__do, &get_value_or_future__do);
  use_read_only(NULL, "empty_key_order_table", &get__empty_key_order_table, &get_value_or_future__empty_key_order_table);
  use_read_only(NULL, "empty_list", &get__empty_list, &get_value_or_future__empty_list);
  use_read_only(NULL, "empty_set", &get__empty_set, &get_value_or_future__empty_set);
  use_read_write(NULL, "events", &get__events, &set__events);
  use_read_only(NULL, "false", &get__false, &get_value_or_future__false);
  use_polymorphic_function(NULL, "file_descriptor_of", &get__file_descriptor_of, &poly_idx__file_descriptor_of);
  use_read_only(NULL, "for_each", &get__for_each, &get_value_or_future__for_each);
  use_read_only(NULL, "forever", &get__forever, &get_value_or_future__forever);
  use_read_only(NULL, "get", &get__get, &get_value_or_future__get);
  use_read_only(NULL, "get_terminal_size", &get__get_terminal_size, &get_value_or_future__get_terminal_size);
  use_polymorphic_function(NULL, "height_of", &get__height_of, &poly_idx__height_of);
  use_read_only(NULL, "if", &get__if, &get_value_or_future__if);
  use_read_only(NULL, "inc", &get__inc, &get_value_or_future__inc);
  use_read_only(NULL, "is_defined", &get__is_defined, &get_value_or_future__is_defined);
  use_read_only(NULL, "is_empty", &get__is_empty, &get_value_or_future__is_empty);
  use_read_only(NULL, "key_of", &get__key_of, &get_value_or_future__key_of);
  use_read_only(NULL, "length_of", &get__length_of, &get_value_or_future__length_of);
  use_read_only(NULL, "no_longer_want_to_read_from", &get__no_longer_want_to_read_from, &get_value_or_future__no_longer_want_to_read_from);
  use_read_only(NULL, "no_longer_want_to_write_to", &get__no_longer_want_to_write_to, &get_value_or_future__no_longer_want_to_write_to);
  use_read_only(NULL, "parameter_count_of", &get__parameter_count_of, &get_value_or_future__parameter_count_of);
  use_polymorphic_function(NULL, "pid_of", &get__pid_of, &poly_idx__pid_of);
  use_read_only(NULL, "process_events", &get__process_events, &get_value_or_future__process_events);
  use_read_only(NULL, "push", &get__push, &get_value_or_future__push);
  use_read_only(NULL, "put", &get__put, &get_value_or_future__put);
  use_read_only(NULL, "raise", &get__raise, &get_value_or_future__raise);
  use_read_only(NULL, "range", &get__range, &get_value_or_future__range);
  use_polymorphic_function(NULL, "status_of", &get__status_of, &poly_idx__status_of);
  use_read_only("std", "and", &get__std__and, &get_value_or_future__std__and);
  use_read_only("std", "equal", &get__std__equal, &get_value_or_future__std__equal);
  use_read_only("std", "less", &get__std__less, &get_value_or_future__std__less);
  use_read_only("std", "minus", &get__std__minus, &get_value_or_future__std__minus);
  use_read_only("std", "negate", &get__std__negate, &get_value_or_future__std__negate);
  use_read_only("std", "not", &get__std__not, &get_value_or_future__std__not);
  use_read_only("std", "plus", &get__std__plus, &get_value_or_future__std__plus);
  use_read_only("std", "sequence", &get__std__sequence, &get_value_or_future__std__sequence);
  use_read_only(NULL, "terminate", &get__terminate, &get_value_or_future__terminate);
  use_read_only(NULL, "true", &get__true, &get_value_or_future__true);
  use_polymorphic_function(NULL, "type_of", &get__type_of, &poly_idx__type_of);
  use_read_only("types", "object", &get__types__object, &get_value_or_future__types__object);
  use_read_only(NULL, "undefined", &get__undefined, &get_value_or_future__undefined);
  use_read_only(NULL, "value_of", &get__value_of, &get_value_or_future__value_of);
  use_read_only(NULL, "wait_for_io", &get__wait_for_io, &get_value_or_future__wait_for_io);
  use_read_only(NULL, "wait_pid", &get__wait_pid, &get_value_or_future__wait_pid);
  use_read_only(NULL, "want_to_read_from", &get__want_to_read_from, &get_value_or_future__want_to_read_from);
  use_read_only(NULL, "want_to_write_to", &get__want_to_write_to, &get_value_or_future__want_to_write_to);
  use_read_only(NULL, "while", &get__while, &get_value_or_future__while);
  use_polymorphic_function(NULL, "width_of", &get__width_of, &poly_idx__width_of);
}

static int already_run_phase_5 = false;

EXPORT void phase_5__basic__event(void) {
  if (already_run_phase_5) return;
  already_run_phase_5 = true;
  assign_value(&var.std__file_descriptor_of, create_function(type__std__file_descriptor_of, -1));
  assign_value(&var.std__pid_of, create_function(type__std__pid_of, -1));
  assign_value(&var.std__status_of, create_function(type__std__status_of, -1));
  assign_value(&var.std__timeout_of, create_function(type__std__timeout_of, -1));
  assign_value(&var.std__width_of, create_function(type__std__width_of, -1));
  assign_value(&var.std__height_of, create_function(type__std__height_of, -1));
  assign_value(&var.std__key_code_of, create_function(type__std__key_code_of, -1));
  assign_value(&var.std__target_of, create_function(type__std__target_of, -1));
  assign_value(&var.types__event, get__types__object());
  assign_variable(&var.std__want_to_write_to, &func__22_1_std__want_to_write_to);
  assign_variable(&var.std__no_longer_want_to_write_to, &func__23_1_std__no_longer_want_to_write_to);
  assign_variable(&var.std__want_to_read_from, &func__24_1_std__want_to_read_from);
  assign_variable(&var.std__no_longer_want_to_read_from, &func__25_1_std__no_longer_want_to_read_from);
  assign_variable(&var.std__wanting_to_write_to, &func__26_1_std__wanting_to_write_to);
  assign_variable(&var.std__wanting_to_read_from, &func__27_1_std__wanting_to_read_from);
  assign_variable(&var.std__wait_to_read_from, &func__29_1_std__wait_to_read_from);
  assign_variable(&var.std__wait_to_write_to, &func__31_1_std__wait_to_write_to);
  assign_variable(&var.std__wait_for_termination, &func__33_1_std__wait_for_termination);
  assign_variable(&var.std__discard, &func__36_1_std__discard);
  assign_variable(&var.std__create_event, &func__37_1_std__create_event);
  assign_variable(&var._get_low_level_events, &func__38_1_get_low_level_events);
  assign_variable(&var._get_event_handler, &func__39_1_get_event_handler);
  assign_variable(&var.std__get_event, &func__40_1_std__get_event);
  assign_variable(&var.std__process_events, &func__42_1_std__process_events);
  assign_variable(&var.std__wait_to, &func__43_1_std__wait_to);
  assign_variable(&var.std__par, &func__44_1_std__par);
}

static int already_run_phase_6 = false;

EXPORT void phase_6__basic__event(void) {
  if (already_run_phase_6) return;
  already_run_phase_6 = true;
  register_collector(collect__basic__event);
}
