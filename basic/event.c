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
REGISTER int argument_count ASM("ebx");
IMPORT void too_few_arguments_error(void);
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
IMPORT void set_module(const char *name);
IMPORT NODE *from_uint32(uint32_t val);
IMPORT NODE *register_unique_item(const char *name);
IMPORT void define_polymorphic_function_with_setter(
  const char *namespace, const char *name, NODE_GETTER getter, int *id_p,
  NODE **var_p
);
IMPORT NODE *create_function(FUNC func, int par_count);
IMPORT NODE *from_latin_1_string(const char *str, long len);
IMPORT void set_used_namespaces(const char **namespaces);
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
static NODE *func__std__want_to_write_to_1;
static void entry__std__want_to_write_to_1(void);
static FRAME_INFO frame__std__want_to_write_to_1 = {1, {"fd"}};
static void cont__std__want_to_write_to_2(void);
static NODE *get__std__want_to_write_to(void) {
  return var.std__want_to_write_to;
}
static NODE *func__std__no_longer_want_to_write_to_1;
static void entry__std__no_longer_want_to_write_to_1(void);
static FRAME_INFO frame__std__no_longer_want_to_write_to_1 = {1, {"fd"}};
static void cont__std__no_longer_want_to_write_to_2(void);
static NODE *get__std__no_longer_want_to_write_to(void) {
  return var.std__no_longer_want_to_write_to;
}
static NODE *func__std__want_to_read_from_1;
static void entry__std__want_to_read_from_1(void);
static FRAME_INFO frame__std__want_to_read_from_1 = {1, {"fd"}};
static void cont__std__want_to_read_from_2(void);
static NODE *get__std__want_to_read_from(void) {
  return var.std__want_to_read_from;
}
static NODE *func__std__no_longer_want_to_read_from_1;
static void entry__std__no_longer_want_to_read_from_1(void);
static FRAME_INFO frame__std__no_longer_want_to_read_from_1 = {1, {"fd"}};
static void cont__std__no_longer_want_to_read_from_2(void);
static NODE *get__std__no_longer_want_to_read_from(void) {
  return var.std__no_longer_want_to_read_from;
}
static NODE *func__std__wanting_to_write_to_1;
static void entry__std__wanting_to_write_to_1(void);
static FRAME_INFO frame__std__wanting_to_write_to_1 = {1, {"fd"}};
static void cont__std__wanting_to_write_to_2(void);
static NODE *func__std__wanting_to_write_to_3;
static void entry__std__wanting_to_write_to_3(void);
static FRAME_INFO frame__std__wanting_to_write_to_3 = {1, {"fd"}};
static void cont__std__wanting_to_write_to_4(void);
static void cont__std__wanting_to_write_to_5(void);
static NODE *get__std__wanting_to_write_to(void) {
  return var.std__wanting_to_write_to;
}
static NODE *func__std__wanting_to_read_from_1;
static void entry__std__wanting_to_read_from_1(void);
static FRAME_INFO frame__std__wanting_to_read_from_1 = {1, {"fd"}};
static void cont__std__wanting_to_read_from_2(void);
static NODE *func__std__wanting_to_read_from_3;
static void entry__std__wanting_to_read_from_3(void);
static FRAME_INFO frame__std__wanting_to_read_from_3 = {1, {"fd"}};
static void cont__std__wanting_to_read_from_4(void);
static void cont__std__wanting_to_read_from_5(void);
static NODE *get__std__wanting_to_read_from(void) {
  return var.std__wanting_to_read_from;
}
static NODE *func__std__wait_to_read_from_1;
static void entry__std__wait_to_read_from_1(void);
static FRAME_INFO frame__std__wait_to_read_from_1 = {2, {"fd", "continuation"}};
static void cont__std__wait_to_read_from_2(void);
static void cont__std__wait_to_read_from_3(void);
static void cont__std__wait_to_read_from_4(void);
static NODE *get__std__wait_to_read_from(void) {
  return var.std__wait_to_read_from;
}
static NODE *func__std__wait_to_write_to_1;
static void entry__std__wait_to_write_to_1(void);
static FRAME_INFO frame__std__wait_to_write_to_1 = {2, {"fd", "continuation"}};
static void cont__std__wait_to_write_to_2(void);
static void cont__std__wait_to_write_to_3(void);
static void cont__std__wait_to_write_to_4(void);
static NODE *get__std__wait_to_write_to(void) {
  return var.std__wait_to_write_to;
}
static NODE *func__std__wait_for_termination_1;
static void entry__std__wait_for_termination_1(void);
static FRAME_INFO frame__std__wait_for_termination_1 = {2, {"pid", "continuation"}};
static void cont__std__wait_for_termination_2(void);
static void cont__std__wait_for_termination_3(void);
static NODE *get__std__wait_for_termination(void) {
  return var.std__wait_for_termination;
}
static NODE *func__std__discard_1;
static void entry__std__discard_1(void);
static FRAME_INFO frame__std__discard_1 = {2, {"fd", "return"}};
static void cont__std__discard_2(void);
static NODE *func__std__discard_3;
static void entry__std__discard_3(void);
static FRAME_INFO frame__std__discard_3 = {3, {"fd", "new_events", "s"}};
static void cont__std__discard_4(void);
static void cont__std__discard_5(void);
static void cont__std__discard_6(void);
static NODE *func__std__discard_7;
static void entry__std__discard_7(void);
static FRAME_INFO frame__std__discard_7 = {5, {"idx", "event", "fd", "new_events", "s"}};
static void cont__std__discard_8(void);
static void cont__std__discard_9(void);
static NODE *func__std__discard_10;
static void entry__std__discard_10(void);
static FRAME_INFO frame__std__discard_10 = {5, {"event", "fd", "new_events", "s", "idx"}};
static void cont__std__discard_11(void);
static void cont__std__discard_12(void);
static NODE *func__std__discard_13;
static void entry__std__discard_13(void);
static FRAME_INFO frame__std__discard_13 = {3, {"new_events", "s", "idx"}};
static void cont__std__discard_14(void);
static void cont__std__discard_15(void);
static void cont__std__discard_16(void);
static void cont__std__discard_17(void);
static void cont__std__discard_18(void);
static void cont__std__discard_19(void);
static NODE *func__std__discard_20;
static void entry__std__discard_20(void);
static FRAME_INFO frame__std__discard_20 = {2, {"new_events", "s"}};
static void cont__std__discard_21(void);
static void cont__std__discard_22(void);
static void cont__std__discard_23(void);
static void cont__std__discard_24(void);
static void cont__std__discard_25(void);
static void cont__std__discard_26(void);
static NODE *func__std__discard_27;
static void entry__std__discard_27(void);
static FRAME_INFO frame__std__discard_27 = {1, {"return"}};
static void cont__std__discard_28(void);
static NODE *get__std__discard(void) {
  return var.std__discard;
}
static NODE *func__std__create_event_1;
static void entry__std__create_event_1(void);
static FRAME_INFO frame__std__create_event_1 = {1, {"event"}};
static void cont__std__create_event_2(void);
static NODE *get__std__create_event(void) {
  return var.std__create_event;
}
static NODE *func__get_low_level_events_1;
static void entry__get_low_level_events_1(void);
static FRAME_INFO frame__get_low_level_events_1 = {9, {"for_readers_and_writers_only", "output_fds_list", "input_fds_list", "exception_fds_list", "child_changed_state", "window_changed_size", "ready_input_fds_list", "ready_output_fds_list", "ready_exception_fds_list"}};
static NODE *func__get_low_level_events_2;
static void entry__get_low_level_events_2(void);
static FRAME_INFO frame__get_low_level_events_2 = {2, {"output_fds_list", "input_fds_list"}};
static NODE *func__get_low_level_events_3;
static void entry__get_low_level_events_3(void);
static FRAME_INFO frame__get_low_level_events_3 = {3, {"output_fd", "continuation", "output_fds_list"}};
static void cont__get_low_level_events_4(void);
static void cont__get_low_level_events_5(void);
static NODE *func__get_low_level_events_6;
static void entry__get_low_level_events_6(void);
static FRAME_INFO frame__get_low_level_events_6 = {3, {"input_fd", "continuation", "input_fds_list"}};
static void cont__get_low_level_events_7(void);
static NODE *func__get_low_level_events_8;
static void entry__get_low_level_events_8(void);
static FRAME_INFO frame__get_low_level_events_8 = {2, {"output_fds_list", "input_fds_list"}};
static NODE *func__get_low_level_events_9;
static void entry__get_low_level_events_9(void);
static FRAME_INFO frame__get_low_level_events_9 = {2, {"output_fd", "output_fds_list"}};
static void cont__get_low_level_events_10(void);
static void cont__get_low_level_events_11(void);
static NODE *func__get_low_level_events_12;
static void entry__get_low_level_events_12(void);
static FRAME_INFO frame__get_low_level_events_12 = {2, {"input_fd", "input_fds_list"}};
static void cont__get_low_level_events_13(void);
static void cont__get_low_level_events_14(void);
static void cont__get_low_level_events_15(void);
static NODE *func__get_low_level_events_16;
static void entry__get_low_level_events_16(void);
static FRAME_INFO frame__get_low_level_events_16 = {8, {"child_changed_state", "window_changed_size", "ready_input_fds_list", "ready_output_fds_list", "ready_exception_fds_list", "ready_input_fds_set", "ready_output_fds_set", "ready_exception_fds_set"}};
static NODE *func__get_low_level_events_17;
static void entry__get_low_level_events_17(void);
static FRAME_INFO frame__get_low_level_events_17 = {0, {}};
static NODE *func__get_low_level_events_18;
static void entry__get_low_level_events_18(void);
static FRAME_INFO frame__get_low_level_events_18 = {1, {"break"}};
static NODE *func__get_low_level_events_19;
static void entry__get_low_level_events_19(void);
static FRAME_INFO frame__get_low_level_events_19 = {3, {"break", "status", "pid"}};
static void cont__get_low_level_events_20(void);
static void cont__get_low_level_events_21(void);
static void cont__get_low_level_events_22(void);
static void cont__get_low_level_events_23(void);
static void cont__get_low_level_events_24(void);
static void cont__get_low_level_events_25(void);
static void cont__get_low_level_events_26(void);
static NODE *func__get_low_level_events_27;
static void entry__get_low_level_events_27(void);
static FRAME_INFO frame__get_low_level_events_27 = {2, {"width", "height"}};
static void cont__get_low_level_events_28(void);
static void cont__get_low_level_events_29(void);
static NODE *func__get_low_level_events_30;
static void entry__get_low_level_events_30(void);
static FRAME_INFO frame__get_low_level_events_30 = {2, {"ready_input_fd", "ready_input_fds_set"}};
static void cont__get_low_level_events_31(void);
static void cont__get_low_level_events_32(void);
static NODE *func__get_low_level_events_33;
static void entry__get_low_level_events_33(void);
static FRAME_INFO frame__get_low_level_events_33 = {2, {"ready_output_fd", "ready_output_fds_set"}};
static void cont__get_low_level_events_34(void);
static void cont__get_low_level_events_35(void);
static NODE *func__get_low_level_events_36;
static void entry__get_low_level_events_36(void);
static FRAME_INFO frame__get_low_level_events_36 = {2, {"ready_exception_fd", "ready_exception_fds_set"}};
static void cont__get_low_level_events_37(void);
static void cont__get_low_level_events_38(void);
static NODE *func__get_low_level_events_39;
static void entry__get_low_level_events_39(void);
static FRAME_INFO frame__get_low_level_events_39 = {1, {"input_fd"}};
static void cont__get_low_level_events_40(void);
static NODE *func__get_low_level_events_41;
static void entry__get_low_level_events_41(void);
static FRAME_INFO frame__get_low_level_events_41 = {1, {"input_fd"}};
static void cont__get_low_level_events_42(void);
static NODE *func__get_low_level_events_43;
static void entry__get_low_level_events_43(void);
static FRAME_INFO frame__get_low_level_events_43 = {1, {"output_fd"}};
static void cont__get_low_level_events_44(void);
static NODE *func__get_low_level_events_45;
static void entry__get_low_level_events_45(void);
static FRAME_INFO frame__get_low_level_events_45 = {1, {"output_fd"}};
static NODE *func__get_low_level_events_46;
static void entry__get_low_level_events_46(void);
static FRAME_INFO frame__get_low_level_events_46 = {0, {}};
static NODE *func__get_event_handler_1;
static void entry__get_event_handler_1(void);
static FRAME_INFO frame__get_event_handler_1 = {2, {"event", "return"}};
static void cont__get_event_handler_2(void);
static NODE *func__get_event_handler_3;
static void entry__get_event_handler_3(void);
static FRAME_INFO frame__get_event_handler_3 = {4, {"event", "return", "fd", "reader"}};
static void cont__get_event_handler_4(void);
static void cont__get_event_handler_5(void);
static void cont__get_event_handler_6(void);
static NODE *func__get_event_handler_7;
static void entry__get_event_handler_7(void);
static FRAME_INFO frame__get_event_handler_7 = {3, {"fd", "return", "reader"}};
static void cont__get_event_handler_8(void);
static void cont__get_event_handler_9(void);
static NODE *func__get_event_handler_10;
static void entry__get_event_handler_10(void);
static FRAME_INFO frame__get_event_handler_10 = {4, {"event", "return", "fd", "writer"}};
static void cont__get_event_handler_11(void);
static void cont__get_event_handler_12(void);
static void cont__get_event_handler_13(void);
static NODE *func__get_event_handler_14;
static void entry__get_event_handler_14(void);
static FRAME_INFO frame__get_event_handler_14 = {3, {"fd", "return", "writer"}};
static void cont__get_event_handler_15(void);
static void cont__get_event_handler_16(void);
static NODE *func__get_event_handler_17;
static void entry__get_event_handler_17(void);
static FRAME_INFO frame__get_event_handler_17 = {4, {"event", "return", "pid", "terminator"}};
static void cont__get_event_handler_18(void);
static void cont__get_event_handler_19(void);
static void cont__get_event_handler_20(void);
static NODE *func__get_event_handler_21;
static void entry__get_event_handler_21(void);
static FRAME_INFO frame__get_event_handler_21 = {3, {"pid", "return", "terminator"}};
static void cont__get_event_handler_22(void);
static NODE *func__get_event_handler_23;
static void entry__get_event_handler_23(void);
static FRAME_INFO frame__get_event_handler_23 = {1, {"return"}};
static void cont__get_event_handler_24(void);
static NODE *func__std__get_event_1;
static void entry__std__get_event_1(void);
static FRAME_INFO frame__std__get_event_1 = {1, {"return"}};
static NODE *func__std__get_event_2;
static void entry__std__get_event_2(void);
static FRAME_INFO frame__std__get_event_2 = {2, {"myself", "return"}};
static void cont__std__get_event_3(void);
static void cont__std__get_event_4(void);
static NODE *func__std__get_event_5;
static void entry__std__get_event_5(void);
static FRAME_INFO frame__std__get_event_5 = {4, {"myself", "return", "event", "handler"}};
static void cont__std__get_event_6(void);
static void cont__std__get_event_7(void);
static void cont__std__get_event_8(void);
static NODE *func__std__get_event_9;
static void entry__std__get_event_9(void);
static FRAME_INFO frame__std__get_event_9 = {3, {"myself", "handler", "event"}};
static void cont__std__get_event_10(void);
static void cont__std__get_event_11(void);
static void cont__std__get_event_12(void);
static NODE *func__std__get_event_13;
static void entry__std__get_event_13(void);
static FRAME_INFO frame__std__get_event_13 = {2, {"handler", "event"}};
static NODE *func__std__get_event_14;
static void entry__std__get_event_14(void);
static FRAME_INFO frame__std__get_event_14 = {1, {"handler"}};
static void cont__std__get_event_15(void);
static NODE *string__66e3787d9d72e485;
static void cont__std__get_event_17(void);
static NODE *func__std__get_event_18;
static void entry__std__get_event_18(void);
static FRAME_INFO frame__std__get_event_18 = {0, {}};
static void cont__std__get_event_19(void);
static NODE *get__std__get_event(void) {
  return var.std__get_event;
}
static NODE *func__std__process_events_1;
static void entry__std__process_events_1(void);
static FRAME_INFO frame__std__process_events_1 = {1, {"i"}};
static NODE *func__std__process_events_2;
static void entry__std__process_events_2(void);
static FRAME_INFO frame__std__process_events_2 = {0, {}};
static void cont__std__process_events_3(void);
static void cont__std__process_events_4(void);
static NODE *func__std__process_events_5;
static void entry__std__process_events_5(void);
static FRAME_INFO frame__std__process_events_5 = {0, {}};
static void cont__std__process_events_6(void);
static void cont__std__process_events_7(void);
static void cont__std__process_events_8(void);
static NODE *func__std__process_events_9;
static void entry__std__process_events_9(void);
static FRAME_INFO frame__std__process_events_9 = {0, {}};
static void cont__std__process_events_10(void);
static void cont__std__process_events_11(void);
static void cont__std__process_events_12(void);
static NODE *func__std__process_events_13;
static void entry__std__process_events_13(void);
static FRAME_INFO frame__std__process_events_13 = {2, {"i", "n"}};
static void cont__std__process_events_14(void);
static NODE *func__std__process_events_15;
static void entry__std__process_events_15(void);
static FRAME_INFO frame__std__process_events_15 = {2, {"n", "i"}};
static void cont__std__process_events_16(void);
static void cont__std__process_events_17(void);
static NODE *func__std__process_events_18;
static void entry__std__process_events_18(void);
static FRAME_INFO frame__std__process_events_18 = {3, {"i", "event", "handler"}};
static void cont__std__process_events_19(void);
static void cont__std__process_events_20(void);
static void cont__std__process_events_21(void);
static NODE *func__std__process_events_22;
static void entry__std__process_events_22(void);
static FRAME_INFO frame__std__process_events_22 = {3, {"i", "handler", "event"}};
static void cont__std__process_events_23(void);
static void cont__std__process_events_24(void);
static void cont__std__process_events_25(void);
static NODE *func__std__process_events_26;
static void entry__std__process_events_26(void);
static FRAME_INFO frame__std__process_events_26 = {2, {"handler", "event"}};
static NODE *func__std__process_events_27;
static void entry__std__process_events_27(void);
static FRAME_INFO frame__std__process_events_27 = {1, {"handler"}};
static void cont__std__process_events_28(void);
static void cont__std__process_events_29(void);
static void cont__std__process_events_30(void);
static void cont__std__process_events_31(void);
static NODE *get__std__process_events(void) {
  return var.std__process_events;
}
static NODE *func__std__wait_to_1;
static void entry__std__wait_to_1(void);
static FRAME_INFO frame__std__wait_to_1 = {2, {"args", "event"}};
static NODE *func__std__wait_to_2;
static void entry__std__wait_to_2(void);
static FRAME_INFO frame__std__wait_to_2 = {2, {"continuation", "args"}};
static NODE *func__std__wait_to_3;
static void entry__std__wait_to_3(void);
static FRAME_INFO frame__std__wait_to_3 = {4, {"arg", "continuation", "type", "value"}};
static void cont__std__wait_to_4(void);
static void cont__std__wait_to_5(void);
static NODE *func__std__wait_to_6;
static void entry__std__wait_to_6(void);
static FRAME_INFO frame__std__wait_to_6 = {2, {"value", "continuation"}};
static void cont__std__wait_to_7(void);
static void cont__std__wait_to_8(void);
static NODE *func__std__wait_to_9;
static void entry__std__wait_to_9(void);
static FRAME_INFO frame__std__wait_to_9 = {2, {"value", "continuation"}};
static void cont__std__wait_to_10(void);
static void cont__std__wait_to_11(void);
static NODE *func__std__wait_to_12;
static void entry__std__wait_to_12(void);
static FRAME_INFO frame__std__wait_to_12 = {2, {"value", "continuation"}};
static void cont__std__wait_to_13(void);
static NODE *func__std__wait_to_14;
static void entry__std__wait_to_14(void);
static FRAME_INFO frame__std__wait_to_14 = {2, {"value", "continuation"}};
static void cont__std__wait_to_15(void);
static void cont__std__wait_to_16(void);
static void cont__std__wait_to_17(void);
static NODE *func__std__wait_to_18;
static void entry__std__wait_to_18(void);
static FRAME_INFO frame__std__wait_to_18 = {3, {"arg", "type", "value"}};
static void cont__std__wait_to_19(void);
static void cont__std__wait_to_20(void);
static NODE *func__std__wait_to_21;
static void entry__std__wait_to_21(void);
static FRAME_INFO frame__std__wait_to_21 = {1, {"value"}};
static void cont__std__wait_to_22(void);
static void cont__std__wait_to_23(void);
static NODE *func__std__wait_to_24;
static void entry__std__wait_to_24(void);
static FRAME_INFO frame__std__wait_to_24 = {1, {"value"}};
static void cont__std__wait_to_25(void);
static void cont__std__wait_to_26(void);
static NODE *func__std__wait_to_27;
static void entry__std__wait_to_27(void);
static FRAME_INFO frame__std__wait_to_27 = {1, {"value"}};
static void cont__std__wait_to_28(void);
static void cont__std__wait_to_29(void);
static NODE *get__std__wait_to(void) {
  return var.std__wait_to;
}
static NODE *func__std__par_1;
static void entry__std__par_1(void);
static FRAME_INFO frame__std__par_1 = {1, {"tasks"}};
static void cont__std__par_2(void);
static NODE *get__std__par(void) {
  return var.std__par;
}
void run__basic__event(void);

static CONTINUATION_INFO continuation_info[] = {
  {type__std__file_descriptor_of, NULL, 35, 35, 2, 24},
  {type__std__pid_of, NULL, 45, 45, 2, 12},
  {type__std__status_of, NULL, 51, 51, 2, 15},
  {type__std__width_of, NULL, 69, 69, 2, 14},
  {type__std__height_of, NULL, 75, 75, 2, 15},
  {type__std__key_code_of, NULL, 87, 87, 2, 17},
  {type__std__target_of, NULL, 99, 99, 2, 15},
  {run__basic__event, NULL, 428, 428, 1, 26},
  {entry__std__want_to_write_to_1, NULL, 144, 144, 3, 24},
  {cont__std__want_to_write_to_2, &frame__std__want_to_write_to_1, 144, 144, 29, 29},
  {entry__std__no_longer_want_to_write_to_1, NULL, 159, 159, 3, 24},
  {cont__std__no_longer_want_to_write_to_2, &frame__std__no_longer_want_to_write_to_1, 159, 159, 30, 30},
  {entry__std__want_to_read_from_1, NULL, 174, 174, 3, 23},
  {cont__std__want_to_read_from_2, &frame__std__want_to_read_from_1, 174, 174, 28, 28},
  {entry__std__no_longer_want_to_read_from_1, NULL, 189, 189, 3, 23},
  {cont__std__no_longer_want_to_read_from_2, &frame__std__no_longer_want_to_read_from_1, 189, 189, 29, 29},
  {entry__std__wanting_to_write_to_3, NULL, 202, 202, 23, 43},
  {cont__std__wanting_to_write_to_4, &frame__std__wanting_to_write_to_3, 202, 202, 23, 43},
  {entry__std__wanting_to_write_to_1, NULL, 202, 202, 6, 18},
  {cont__std__wanting_to_write_to_2, &frame__std__wanting_to_write_to_1, 202, 202, 6, 43},
  {cont__std__wanting_to_write_to_5, &frame__std__wanting_to_write_to_1, 202, 202, 3, 43},
  {entry__std__wanting_to_read_from_3, NULL, 215, 215, 23, 42},
  {cont__std__wanting_to_read_from_4, &frame__std__wanting_to_read_from_3, 215, 215, 23, 42},
  {entry__std__wanting_to_read_from_1, NULL, 215, 215, 6, 18},
  {cont__std__wanting_to_read_from_2, &frame__std__wanting_to_read_from_1, 215, 215, 6, 42},
  {cont__std__wanting_to_read_from_5, &frame__std__wanting_to_read_from_1, 215, 215, 3, 42},
  {entry__std__wait_to_read_from_1, NULL, 230, 230, 3, 22},
  {cont__std__wait_to_read_from_2, &frame__std__wait_to_read_from_1, 231, 231, 3, 14},
  {cont__std__wait_to_read_from_3, &frame__std__wait_to_read_from_1, 232, 232, 3, 45},
  {cont__std__wait_to_read_from_4, &frame__std__wait_to_read_from_1, 232, 232, 45, 45},
  {entry__std__wait_to_write_to_1, NULL, 247, 247, 3, 21},
  {cont__std__wait_to_write_to_2, &frame__std__wait_to_write_to_1, 248, 248, 3, 14},
  {cont__std__wait_to_write_to_3, &frame__std__wait_to_write_to_1, 249, 249, 3, 45},
  {cont__std__wait_to_write_to_4, &frame__std__wait_to_write_to_1, 249, 249, 45, 45},
  {entry__std__wait_for_termination_1, NULL, 264, 264, 3, 19},
  {cont__std__wait_for_termination_2, &frame__std__wait_for_termination_1, 265, 265, 3, 45},
  {cont__std__wait_for_termination_3, &frame__std__wait_for_termination_1, 265, 265, 45, 45},
  {entry__std__discard_13, NULL, 294, 294, 45, 49},
  {cont__std__discard_14, &frame__std__discard_13, 294, 294, 30, 50},
  {cont__std__discard_15, &frame__std__discard_13, 294, 294, 11, 50},
  {cont__std__discard_16, &frame__std__discard_13, 295, 295, 11, 18},
  {cont__std__discard_17, &frame__std__discard_13, 295, 295, 18, 18},
  {entry__std__discard_10, NULL, 293, 293, 12, 36},
  {cont__std__discard_11, &frame__std__discard_10, 293, 293, 12, 42},
  {cont__std__discard_12, &frame__std__discard_10, 293, 295, 9, 18},
  {entry__std__discard_7, NULL, 292, 292, 12, 25},
  {cont__std__discard_8, &frame__std__discard_7, 292, 292, 27, 45},
  {cont__std__discard_9, &frame__std__discard_7, 292, 295, 7, 19},
  {entry__std__discard_20, NULL, 297, 297, 42, 42},
  {cont__std__discard_21, &frame__std__discard_20, 297, 297, 26, 43},
  {cont__std__discard_22, &frame__std__discard_20, 297, 297, 7, 43},
  {cont__std__discard_23, &frame__std__discard_20, 298, 298, 24, 24},
  {entry__std__discard_3, NULL, 283, 283, 5, 34},
  {cont__std__discard_4, &frame__std__discard_3, 284, 284, 5, 33},
  {cont__std__discard_5, &frame__std__discard_3, 285, 285, 5, 12},
  {cont__std__discard_6, &frame__std__discard_3, 291, 295, 5, 20},
  {cont__std__discard_18, &frame__std__discard_3, 296, 296, 8, 12},
  {cont__std__discard_19, &frame__std__discard_3, 296, 298, 5, 24},
  {entry__std__discard_27, NULL, 299, 299, 39, 54},
  {entry__std__discard_1, NULL, 282, 282, 6, 18},
  {cont__std__discard_2, &frame__std__discard_1, 282, 298, 3, 25},
  {cont__std__discard_24, &frame__std__discard_1, 299, 299, 6, 31},
  {cont__std__discard_25, &frame__std__discard_1, 299, 299, 6, 36},
  {cont__std__discard_26, &frame__std__discard_1, 299, 299, 3, 54},
  {cont__std__discard_28, &frame__std__discard_1, 299, 299, 54, 54},
  {entry__std__create_event_1, NULL, 309, 309, 3, 20},
  {cont__std__create_event_2, &frame__std__create_event_1, 309, 309, 20, 20},
  {entry__get_low_level_events_3, NULL, 318, 318, 9, 39},
  {cont__get_low_level_events_4, &frame__get_low_level_events_3, 318, 318, 39, 39},
  {entry__get_low_level_events_6, NULL, 319, 319, 50, 78},
  {cont__get_low_level_events_7, &frame__get_low_level_events_6, 319, 319, 78, 78},
  {entry__get_low_level_events_2, NULL, 317, 318, 7, 39},
  {cont__get_low_level_events_5, &frame__get_low_level_events_2, 319, 319, 7, 78},
  {entry__get_low_level_events_9, NULL, 321, 321, 47, 77},
  {cont__get_low_level_events_10, &frame__get_low_level_events_9, 321, 321, 77, 77},
  {entry__get_low_level_events_12, NULL, 322, 322, 45, 73},
  {cont__get_low_level_events_13, &frame__get_low_level_events_12, 322, 322, 73, 73},
  {entry__get_low_level_events_8, NULL, 321, 321, 7, 77},
  {cont__get_low_level_events_11, &frame__get_low_level_events_8, 322, 322, 7, 73},
  {entry__get_low_level_events_19, NULL, 338, 338, 36, 36},
  {cont__get_low_level_events_20, &frame__get_low_level_events_19, 338, 338, 13, 41},
  {cont__get_low_level_events_21, &frame__get_low_level_events_19, 339, 339, 16, 23},
  {cont__get_low_level_events_22, &frame__get_low_level_events_19, 339, 339, 16, 23},
  {cont__get_low_level_events_23, &frame__get_low_level_events_19, 339, 339, 13, 29},
  {cont__get_low_level_events_24, &frame__get_low_level_events_19, 340, 341, 13, 77},
  {entry__get_low_level_events_18, NULL, 337, 341, 11, 78},
  {cont__get_low_level_events_25, &frame__get_low_level_events_18, 341, 341, 78, 78},
  {entry__get_low_level_events_17, NULL, 336, 341, 9, 79},
  {entry__get_low_level_events_27, NULL, 343, 343, 9, 53},
  {cont__get_low_level_events_28, &frame__get_low_level_events_27, 344, 348, 9, 30},
  {entry__get_low_level_events_30, NULL, 353, 353, 9, 44},
  {cont__get_low_level_events_31, &frame__get_low_level_events_30, 353, 353, 49, 49},
  {entry__get_low_level_events_33, NULL, 355, 355, 9, 46},
  {cont__get_low_level_events_34, &frame__get_low_level_events_33, 355, 355, 51, 51},
  {entry__get_low_level_events_36, NULL, 357, 357, 9, 52},
  {cont__get_low_level_events_37, &frame__get_low_level_events_36, 357, 357, 57, 57},
  {entry__get_low_level_events_41, NULL, 360, 361, 11, 73},
  {entry__get_low_level_events_39, NULL, 359, 359, 12, 37},
  {cont__get_low_level_events_40, &frame__get_low_level_events_39, 359, 361, 9, 74},
  {entry__get_low_level_events_45, NULL, 364, 365, 11, 73},
  {entry__get_low_level_events_43, NULL, 363, 363, 12, 39},
  {cont__get_low_level_events_44, &frame__get_low_level_events_43, 363, 365, 9, 74},
  {entry__get_low_level_events_16, NULL, 335, 341, 7, 80},
  {cont__get_low_level_events_26, &frame__get_low_level_events_16, 342, 348, 7, 31},
  {cont__get_low_level_events_29, &frame__get_low_level_events_16, 352, 353, 7, 49},
  {cont__get_low_level_events_32, &frame__get_low_level_events_16, 354, 355, 7, 51},
  {cont__get_low_level_events_35, &frame__get_low_level_events_16, 356, 357, 7, 57},
  {cont__get_low_level_events_38, &frame__get_low_level_events_16, 358, 361, 7, 75},
  {cont__get_low_level_events_42, &frame__get_low_level_events_16, 362, 365, 7, 75},
  {entry__get_low_level_events_46, NULL, 367, 367, 7, 49},
  {entry__get_low_level_events_1, NULL, 315, 322, 3, 74},
  {cont__get_low_level_events_14, &frame__get_low_level_events_1, },
  {cont__get_low_level_events_15, &frame__get_low_level_events_1, 323, 367, 3, 50},
  {entry__get_event_handler_7, NULL, 379, 379, 9, 38},
  {cont__get_event_handler_8, &frame__get_event_handler_7, 380, 380, 9, 20},
  {cont__get_event_handler_9, &frame__get_event_handler_7, 381, 381, 9, 21},
  {entry__get_event_handler_3, NULL, 376, 376, 7, 35},
  {cont__get_event_handler_4, &frame__get_event_handler_3, 377, 377, 7, 25},
  {cont__get_event_handler_5, &frame__get_event_handler_3, 378, 378, 10, 26},
  {cont__get_event_handler_6, &frame__get_event_handler_3, 378, 381, 7, 21},
  {entry__get_event_handler_14, NULL, 386, 386, 9, 37},
  {cont__get_event_handler_15, &frame__get_event_handler_14, 387, 387, 9, 20},
  {cont__get_event_handler_16, &frame__get_event_handler_14, 388, 388, 9, 21},
  {entry__get_event_handler_10, NULL, 383, 383, 7, 35},
  {cont__get_event_handler_11, &frame__get_event_handler_10, 384, 384, 7, 25},
  {cont__get_event_handler_12, &frame__get_event_handler_10, 385, 385, 10, 26},
  {cont__get_event_handler_13, &frame__get_event_handler_10, 385, 388, 7, 21},
  {entry__get_event_handler_21, NULL, 393, 393, 9, 25},
  {cont__get_event_handler_22, &frame__get_event_handler_21, 394, 394, 9, 25},
  {entry__get_event_handler_17, NULL, 390, 390, 7, 24},
  {cont__get_event_handler_18, &frame__get_event_handler_17, 391, 391, 7, 34},
  {cont__get_event_handler_19, &frame__get_event_handler_17, 392, 392, 10, 30},
  {cont__get_event_handler_20, &frame__get_event_handler_17, 392, 394, 7, 25},
  {entry__get_event_handler_23, NULL, 396, 396, 7, 29},
  {entry__get_event_handler_1, NULL, 374, 374, 8, 21},
  {cont__get_event_handler_2, &frame__get_event_handler_1, 374, 396, 3, 30},
  {cont__get_event_handler_24, &frame__get_event_handler_1, 397, 397, 3, 14},
  {entry__std__get_event_13, NULL, 420, 420, 15, 27},
  {entry__std__get_event_14, NULL, 422, 422, 15, 21},
  {entry__std__get_event_9, NULL, 417, 417, 11, 35},
  {cont__std__get_event_10, &frame__std__get_event_9, 419, 419, 13, 39},
  {cont__std__get_event_11, &frame__std__get_event_9, 419, 419, 13, 44},
  {cont__std__get_event_12, &frame__std__get_event_9, 418, 422, 11, 22},
  {cont__std__get_event_15, &frame__std__get_event_9, 423, 423, 11, 38},
  {entry__std__get_event_5, NULL, 414, 414, 9, 27},
  {cont__std__get_event_6, &frame__std__get_event_5, 415, 415, 9, 41},
  {cont__std__get_event_7, &frame__std__get_event_5, 416, 416, 12, 29},
  {cont__std__get_event_8, &frame__std__get_event_5, 416, 423, 9, 38},
  {cont__std__get_event_17, &frame__std__get_event_5, 424, 424, 9, 20},
  {entry__std__get_event_18, NULL, 426, 426, 9, 34},
  {entry__std__get_event_2, NULL, 413, 413, 7, 23},
  {cont__std__get_event_3, &frame__std__get_event_2, 413, 413, 7, 27},
  {cont__std__get_event_4, &frame__std__get_event_2, 412, 426, 5, 35},
  {entry__std__get_event_1, NULL, 411, 426, 3, 36},
  {cont__std__get_event_19, &frame__std__get_event_1, 426, 426, 36, 36},
  {entry__std__process_events_5, NULL, 436, 436, 44, 62},
  {cont__std__process_events_6, &frame__std__process_events_5, 436, 436, 44, 62},
  {entry__std__process_events_2, NULL, 436, 436, 14, 37},
  {cont__std__process_events_3, &frame__std__process_events_2, 436, 436, 14, 41},
  {cont__std__process_events_4, &frame__std__process_events_2, 436, 436, 11, 62},
  {entry__std__process_events_9, NULL, 437, 437, 28, 43},
  {cont__std__process_events_10, &frame__std__process_events_9, 437, 437, 28, 43},
  {entry__std__process_events_26, NULL, 448, 448, 15, 27},
  {entry__std__process_events_27, NULL, 450, 450, 15, 21},
  {entry__std__process_events_22, NULL, 445, 445, 11, 29},
  {cont__std__process_events_23, &frame__std__process_events_22, 447, 447, 13, 39},
  {cont__std__process_events_24, &frame__std__process_events_22, 447, 447, 13, 44},
  {cont__std__process_events_25, &frame__std__process_events_22, 446, 450, 11, 22},
  {cont__std__process_events_28, &frame__std__process_events_22, 451, 451, 11, 38},
  {entry__std__process_events_18, NULL, 442, 442, 9, 24},
  {cont__std__process_events_19, &frame__std__process_events_18, 443, 443, 9, 41},
  {cont__std__process_events_20, &frame__std__process_events_18, 444, 444, 12, 29},
  {cont__std__process_events_21, &frame__std__process_events_18, 444, 451, 9, 38},
  {cont__std__process_events_29, &frame__std__process_events_18, 452, 452, 9, 14},
  {cont__std__process_events_30, &frame__std__process_events_18, 452, 452, 14, 14},
  {entry__std__process_events_15, NULL, 441, 441, 16, 21},
  {cont__std__process_events_16, &frame__std__process_events_15, 441, 441, 16, 21},
  {cont__std__process_events_17, &frame__std__process_events_15, 441, 452, 13, 14},
  {entry__std__process_events_13, NULL, 440, 440, 7, 26},
  {cont__std__process_events_14, &frame__std__process_events_13, 441, 452, 7, 14},
  {cont__std__process_events_31, &frame__std__process_events_13, 453, 453, 7, 31},
  {entry__std__process_events_1, NULL, 436, 436, 5, 62},
  {cont__std__process_events_7, &frame__std__process_events_1, 437, 437, 8, 23},
  {cont__std__process_events_8, &frame__std__process_events_1, 437, 437, 8, 43},
  {cont__std__process_events_11, &frame__std__process_events_1, 437, 437, 5, 53},
  {cont__std__process_events_12, &frame__std__process_events_1, 439, 453, 5, 31},
  {entry__std__wait_to_6, NULL, 474, 474, 11, 33},
  {cont__std__wait_to_7, &frame__std__wait_to_6, 475, 475, 11, 25},
  {cont__std__wait_to_8, &frame__std__wait_to_6, 475, 475, 38, 38},
  {entry__std__wait_to_9, NULL, 477, 477, 11, 32},
  {cont__std__wait_to_10, &frame__std__wait_to_9, 478, 478, 11, 25},
  {cont__std__wait_to_11, &frame__std__wait_to_9, 478, 478, 38, 38},
  {entry__std__wait_to_12, NULL, 480, 480, 11, 29},
  {cont__std__wait_to_13, &frame__std__wait_to_12, 480, 480, 42, 42},
  {entry__std__wait_to_14, NULL, 483, 483, 40, 40},
  {entry__std__wait_to_3, NULL, 470, 470, 7, 23},
  {cont__std__wait_to_4, &frame__std__wait_to_3, 471, 471, 7, 26},
  {cont__std__wait_to_5, &frame__std__wait_to_3, 472, 483, 7, 41},
  {entry__std__wait_to_2, NULL, 469, 483, 5, 42},
  {cont__std__wait_to_15, &frame__std__wait_to_2, 484, 484, 5, 47},
  {cont__std__wait_to_16, &frame__std__wait_to_2, 484, 484, 47, 47},
  {entry__std__wait_to_21, NULL, 490, 490, 9, 41},
  {cont__std__wait_to_22, &frame__std__wait_to_21, 491, 491, 9, 23},
  {cont__std__wait_to_23, &frame__std__wait_to_21, 491, 491, 33, 33},
  {entry__std__wait_to_24, NULL, 493, 493, 9, 40},
  {cont__std__wait_to_25, &frame__std__wait_to_24, 494, 494, 9, 23},
  {cont__std__wait_to_26, &frame__std__wait_to_24, 494, 494, 33, 33},
  {entry__std__wait_to_27, NULL, 496, 496, 9, 27},
  {cont__std__wait_to_28, &frame__std__wait_to_27, 496, 496, 37, 37},
  {entry__std__wait_to_18, NULL, 486, 486, 5, 21},
  {cont__std__wait_to_19, &frame__std__wait_to_18, 487, 487, 5, 24},
  {cont__std__wait_to_20, &frame__std__wait_to_18, 488, 496, 5, 38},
  {entry__std__wait_to_1, NULL, 468, 484, 3, 47},
  {cont__std__wait_to_17, &frame__std__wait_to_1, 485, 496, 3, 39},
  {cont__std__wait_to_29, &frame__std__wait_to_1, 499, 499, 3, 10},
  {entry__std__par_1, NULL, 507, 507, 3, 29},
  {cont__std__par_2, &frame__std__par_1, 508, 508, 3, 16}
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
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
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
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
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
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
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
static void type__std__width_of(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
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
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
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
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
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
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
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
  // 115: $types::event types::object
  // 116:   #
  // 117:     an event object
  initialize_maybe_future(var.types__event, get__types__object());
  // 119: $$std::events empty_list
  // 120:   #
  // 121:     the list of unhandled events
  var.std__events = get__empty_list();
  // 123: $$wanted_output_fds empty_set
  // 124:   #
  // 125:     the set of file descriptors that shall be written to
  var._wanted_output_fds = get__empty_set();
  // 127: $$wanted_input_fds empty_set
  // 128:   #
  // 129:     the set of file descriptors that shall be read from
  var._wanted_input_fds = get__empty_set();
  // 217: $$readers empty_key_order_table
  var._readers = get__empty_key_order_table();
  // 234: $$writers empty_key_order_table
  var._writers = get__empty_key_order_table();
  // 251: $$terminators empty_key_order_table
  var._terminators = get__empty_key_order_table();
  // 267: $$timeout undefined # there should be separate timeouts for each caller
  var._timeout = get__undefined();
  // 268: $$timeout_exceeded undefined
  var._timeout_exceeded = get__undefined();
  // 428: $$waiting_tasks empty_list
  var._waiting_tasks = get__empty_list();
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__want_to_write_to_1(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // fd: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 144: !wanted_output_fds(fd)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd */;
  arguments->slots[1] = get__true();
  result_count = 1;
  myself = var._wanted_output_fds;
  func = myself->type;
  frame->cont = cont__std__want_to_write_to_2;
}
static void cont__std__want_to_write_to_2(void) {
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
static void entry__std__no_longer_want_to_write_to_1(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // fd: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 159: !wanted_output_fds(fd)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd */;
  arguments->slots[1] = get__false();
  result_count = 1;
  myself = var._wanted_output_fds;
  func = myself->type;
  frame->cont = cont__std__no_longer_want_to_write_to_2;
}
static void cont__std__no_longer_want_to_write_to_2(void) {
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
static void entry__std__want_to_read_from_1(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // fd: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 174: !wanted_input_fds(fd)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd */;
  arguments->slots[1] = get__true();
  result_count = 1;
  myself = var._wanted_input_fds;
  func = myself->type;
  frame->cont = cont__std__want_to_read_from_2;
}
static void cont__std__want_to_read_from_2(void) {
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
static void entry__std__no_longer_want_to_read_from_1(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // fd: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 189: !wanted_input_fds(fd)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd */;
  arguments->slots[1] = get__false();
  result_count = 1;
  myself = var._wanted_input_fds;
  func = myself->type;
  frame->cont = cont__std__no_longer_want_to_read_from_2;
}
static void cont__std__no_longer_want_to_read_from_2(void) {
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
static void entry__std__wanting_to_write_to_1(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // fd: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 202: ... fd.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__std__wanting_to_write_to_2;
}
static void cont__std__wanting_to_write_to_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 202: ... wanted_output_fds(fd)
  frame->slots[3] /* temp__3 */ = create_closure(entry__std__wanting_to_write_to_3, 0);
  // 202: ... fd.is_defined && wanted_output_fds(fd)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__std__wanting_to_write_to_5;
}
static void entry__std__wanting_to_write_to_3(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // fd: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* fd */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 202: ... wanted_output_fds(fd)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd */;
  result_count = 1;
  myself = var._wanted_output_fds;
  func = myself->type;
  frame->cont = cont__std__wanting_to_write_to_4;
}
static void cont__std__wanting_to_write_to_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 202: ... wanted_output_fds(fd)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__std__wanting_to_write_to_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 202: -> fd.is_defined && wanted_output_fds(fd)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__wanting_to_read_from_1(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // fd: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 215: ... fd.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__std__wanting_to_read_from_2;
}
static void cont__std__wanting_to_read_from_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 215: ... wanted_input_fds(fd)
  frame->slots[3] /* temp__3 */ = create_closure(entry__std__wanting_to_read_from_3, 0);
  // 215: ... fd.is_defined && wanted_input_fds(fd)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__std__wanting_to_read_from_5;
}
static void entry__std__wanting_to_read_from_3(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // fd: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* fd */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 215: ... wanted_input_fds(fd)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd */;
  result_count = 1;
  myself = var._wanted_input_fds;
  func = myself->type;
  frame->cont = cont__std__wanting_to_read_from_4;
}
static void cont__std__wanting_to_read_from_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 215: ... wanted_input_fds(fd)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__std__wanting_to_read_from_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 215: -> fd.is_defined && wanted_input_fds(fd)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__wait_to_read_from_1(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // fd: 0
  // continuation: 1
  frame->slots[1] /* continuation */ = create_continuation();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 230: want_to_read_from fd
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd */;
  result_count = 0;
  myself = get__want_to_read_from();
  func = myself->type;
  frame->cont = cont__std__wait_to_read_from_2;
}
static void cont__std__wait_to_read_from_2(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 231: !readers(fd)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd */;
  arguments->slots[1] = frame->slots[1] /* continuation */;
  result_count = 1;
  myself = var._readers;
  func = myself->type;
  frame->cont = cont__std__wait_to_read_from_3;
}
static void cont__std__wait_to_read_from_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._readers = arguments->slots[0];
  // 232: process_events # will never return directly
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = get__process_events();
  func = myself->type;
  frame->cont = cont__std__wait_to_read_from_4;
}
static void cont__std__wait_to_read_from_4(void) {
  myself = frame->slots[1] /* continuation */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__std__wait_to_write_to_1(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // fd: 0
  // continuation: 1
  frame->slots[1] /* continuation */ = create_continuation();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 247: want_to_write_to fd
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd */;
  result_count = 0;
  myself = get__want_to_write_to();
  func = myself->type;
  frame->cont = cont__std__wait_to_write_to_2;
}
static void cont__std__wait_to_write_to_2(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 248: !writers(fd)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd */;
  arguments->slots[1] = frame->slots[1] /* continuation */;
  result_count = 1;
  myself = var._writers;
  func = myself->type;
  frame->cont = cont__std__wait_to_write_to_3;
}
static void cont__std__wait_to_write_to_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._writers = arguments->slots[0];
  // 249: process_events # will never return directly
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = get__process_events();
  func = myself->type;
  frame->cont = cont__std__wait_to_write_to_4;
}
static void cont__std__wait_to_write_to_4(void) {
  myself = frame->slots[1] /* continuation */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__std__wait_for_termination_1(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // pid: 0
  // continuation: 1
  frame->slots[1] /* continuation */ = create_continuation();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 264: !terminators(pid)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* pid */;
  arguments->slots[1] = frame->slots[1] /* continuation */;
  result_count = 1;
  myself = var._terminators;
  func = myself->type;
  frame->cont = cont__std__wait_for_termination_2;
}
static void cont__std__wait_for_termination_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._terminators = arguments->slots[0];
  // 265: process_events # will never return directly
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = get__process_events();
  func = myself->type;
  frame->cont = cont__std__wait_for_termination_3;
}
static void cont__std__wait_for_termination_3(void) {
  myself = frame->slots[1] /* continuation */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__std__discard_1(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // fd: 0
  // return: 1
  frame->slots[1] /* return */ = create_continuation();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 282: ... fd.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__std__discard_2;
}
static void cont__std__discard_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 282: ... :
  // 283:   no_longer_want_to_read_from fd
  // 284:   no_longer_want_to_write_to fd
  // 285:   close fd
  // 286:   
  // 287:   # remove all associated events
  // 288:   
  // 289:   $$new_events empty_list
  // 290:   $$s 1
  // 291:   for_each events: (idx event)
  // ...
  frame->slots[3] /* temp__2 */ = create_closure(entry__std__discard_3, 0);
  // 282: if fd.is_defined:
  // 283:   no_longer_want_to_read_from fd
  // 284:   no_longer_want_to_write_to fd
  // 285:   close fd
  // 286:   
  // 287:   # remove all associated events
  // 288:   
  // 289:   $$new_events empty_list
  // 290:   $$s 1
  // 291:   for_each events: (idx event)
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__std__discard_24;
}
static void entry__std__discard_20(void) {
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
  // 297: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__std__discard_21;
}
static void cont__std__discard_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 297: ... range(events s -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__events();
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* s */;
  arguments->slots[2] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__std__discard_22;
}
static void cont__std__discard_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 297: append &new_events range(events s -1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* new_events */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__std__discard_23;
}
static void cont__std__discard_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* new_events */ = arguments->slots[0];
  // 298: !events new_events
  set__events(((CELL *)frame->slots[0])->contents /* new_events */);
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__discard_3(void) {
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
  // 283: no_longer_want_to_read_from fd
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd */;
  result_count = 0;
  myself = get__no_longer_want_to_read_from();
  func = myself->type;
  frame->cont = cont__std__discard_4;
}
static void cont__std__discard_4(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 284: no_longer_want_to_write_to fd
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd */;
  result_count = 0;
  myself = get__no_longer_want_to_write_to();
  func = myself->type;
  frame->cont = cont__std__discard_5;
}
static void cont__std__discard_5(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 285: close fd
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd */;
  result_count = 0;
  myself = get__close();
  func = myself->type;
  frame->cont = cont__std__discard_6;
}
static void cont__std__discard_6(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 289: $$new_events empty_list
  ((CELL *)frame->slots[1])->contents /* new_events */ = get__empty_list();
  // 290: $$s 1
  ((CELL *)frame->slots[2])->contents /* s */ = number__1;
  // 291: ... : (idx event)
  // 292:   case type_of(event) WRITE_TO, READ_FROM:
  // 293:     if file_descriptor_of(event) == fd:
  // 294:       append &new_events range(events s idx-1)
  // 295:       !s idx+1
  frame->slots[3] /* temp__1 */ = create_closure(entry__std__discard_7, 2);
  // 291: for_each events: (idx event)
  // 292:   case type_of(event) WRITE_TO, READ_FROM:
  // 293:     if file_descriptor_of(event) == fd:
  // 294:       append &new_events range(events s idx-1)
  // 295:       !s idx+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__events();
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__std__discard_18;
}
static void entry__std__discard_13(void) {
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
  // 294: ... idx-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* idx */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__std__discard_14;
}
static void cont__std__discard_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 294: ... range(events s idx-1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__events();
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* s */;
  arguments->slots[2] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__std__discard_15;
}
static void cont__std__discard_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 294: append &new_events range(events s idx-1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* new_events */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__std__discard_16;
}
static void cont__std__discard_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* new_events */ = arguments->slots[0];
  // 295: !s idx+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* idx */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__std__discard_17;
}
static void cont__std__discard_17(void) {
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
static void entry__std__discard_10(void) {
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
  // 293: ... file_descriptor_of(event)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* event */;
  result_count = 1;
  myself = get__file_descriptor_of();
  func = myself->type;
  frame->cont = cont__std__discard_11;
}
static void cont__std__discard_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 293: ... file_descriptor_of(event) == fd
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[1] /* fd */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__std__discard_12;
}
static void cont__std__discard_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 293: ... :
  // 294:   append &new_events range(events s idx-1)
  // 295:   !s idx+1
  frame->slots[7] /* temp__3 */ = create_closure(entry__std__discard_13, 0);
  // 293: if file_descriptor_of(event) == fd:
  // 294:   append &new_events range(events s idx-1)
  // 295:   !s idx+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__discard_7(void) {
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
  // 292: ... type_of(event)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* event */;
  result_count = 1;
  myself = get__type_of();
  func = myself->type;
  frame->cont = cont__std__discard_8;
}
static void cont__std__discard_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 292: ... WRITE_TO, READ_FROM
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__WRITE_TO();
  arguments->slots[1] = get__READ_FROM();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__std__discard_9;
}
static void cont__std__discard_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 292: ... :
  // 293:   if file_descriptor_of(event) == fd:
  // 294:     append &new_events range(events s idx-1)
  // 295:     !s idx+1
  frame->slots[7] /* temp__3 */ = create_closure(entry__std__discard_10, 0);
  // 292: case type_of(event) WRITE_TO, READ_FROM:
  // 293:   if file_descriptor_of(event) == fd:
  // 294:     append &new_events range(events s idx-1)
  // 295:     !s idx+1
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
static void cont__std__discard_18(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 296: ... s > 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__1;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* s */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__std__discard_19;
}
static void cont__std__discard_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 296: ... :
  // 297:   append &new_events range(events s -1)
  // 298:   !events new_events
  frame->slots[4] /* temp__2 */ = create_closure(entry__std__discard_20, 0);
  // 296: if s > 1:
  // 297:   append &new_events range(events s -1)
  // 298:   !events new_events
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__std__discard_24(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 299: ... parameter_count_of(return)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* return */;
  result_count = 1;
  myself = get__parameter_count_of();
  func = myself->type;
  frame->cont = cont__std__discard_25;
}
static void cont__std__discard_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 299: ... parameter_count_of(return) == 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__std__discard_26;
}
static void cont__std__discard_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 299: ... : return undefined
  frame->slots[4] /* temp__3 */ = create_closure(entry__std__discard_27, 0);
  // 299: if parameter_count_of(return) == 1: return undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__std__discard_28;
}
static void entry__std__discard_27(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 299: ... return undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__std__discard_28(void) {
  myself = frame->slots[1] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__std__create_event_1(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // event: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 309: push &events event
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__events();
  arguments->slots[1] = frame->slots[0] /* event */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__std__create_event_2;
}
static void cont__std__create_event_2(void) {
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
static void entry__get_low_level_events_45(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // output_fd: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* output_fd */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 365: types::event(.type_of WRITE_TO .file_descriptor_of output_fd)
  {
    NODE *temp = clone_object_and_attributes(var.types__event);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__type_of, get__WRITE_TO());
    set_attribute_value(temp->attributes, poly_idx__file_descriptor_of, frame->slots[0] /* output_fd */);
    frame->slots[1] /* temp__1 */ = temp;

  }
  // 364: create_event
  // 365:   types::event(.type_of WRITE_TO .file_descriptor_of output_fd)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__create_event();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__get_low_level_events_43(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // output_fd: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 363: ... wanted_output_fds(output_fd)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* output_fd */;
  result_count = 1;
  myself = var._wanted_output_fds;
  func = myself->type;
  frame->cont = cont__get_low_level_events_44;
}
static void cont__get_low_level_events_44(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 363: ... :
  // 364:   create_event
  // 365:     types::event(.type_of WRITE_TO .file_descriptor_of output_fd)
  frame->slots[2] /* temp__2 */ = create_closure(entry__get_low_level_events_45, 0);
  // 363: if wanted_output_fds(output_fd):
  // 364:   create_event
  // 365:     types::event(.type_of WRITE_TO .file_descriptor_of output_fd)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__get_low_level_events_16(void) {
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
  // 335: if child_changed_state:
  // 336:   do: (-> break)
  // 337:     forever:
  // 338:       wait_pid $status $pid -1 true
  // 339:       if pid <= 0 break
  // 340:       create_event
  // 341:         types::event(.type_of TERMINATED .pid_of pid .status_of status)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* child_changed_state */;
  arguments->slots[1] = func__get_low_level_events_17;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__get_low_level_events_26;
}
static void entry__get_low_level_events_18(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // break: 0
  frame->slots[0] /* break */ = create_continuation();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 337: ... :
  // 338:   wait_pid $status $pid -1 true
  // 339:   if pid <= 0 break
  // 340:   create_event
  // 341:     types::event(.type_of TERMINATED .pid_of pid .status_of status)
  frame->slots[1] /* temp__1 */ = create_closure(entry__get_low_level_events_19, 0);
  // 337: forever:
  // 338:   wait_pid $status $pid -1 true
  // 339:   if pid <= 0 break
  // 340:   create_event
  // 341:     types::event(.type_of TERMINATED .pid_of pid .status_of status)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__forever();
  func = myself->type;
  frame->cont = cont__get_low_level_events_25;
}
static void entry__get_low_level_events_19(void) {
  allocate_initialized_frame_gc(1, 5);
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
  // 338: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__get_low_level_events_20;
}
static void cont__get_low_level_events_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 338: wait_pid $status $pid -1 true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = get__true();
  result_count = 2;
  myself = get__wait_pid();
  func = myself->type;
  frame->cont = cont__get_low_level_events_21;
}
static void cont__get_low_level_events_21(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* status */, arguments->slots[0]);
  initialize_future(frame->slots[2] /* pid */, arguments->slots[1]);
  // 339: ... pid <= 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = frame->slots[2] /* pid */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__get_low_level_events_22;
}
static void cont__get_low_level_events_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 339: ... pid <= 0
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__get_low_level_events_23;
}
static void cont__get_low_level_events_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 339: if pid <= 0 break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[0] /* break */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__get_low_level_events_24;
}
static void cont__get_low_level_events_24(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 341: types::event(.type_of TERMINATED .pid_of pid .status_of status)
  {
    NODE *temp = clone_object_and_attributes(var.types__event);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__type_of, get__TERMINATED());
    set_attribute_value(temp->attributes, poly_idx__pid_of, frame->slots[2] /* pid */);
    set_attribute_value(temp->attributes, poly_idx__status_of, frame->slots[1] /* status */);
    frame->slots[3] /* temp__1 */ = temp;

  }
  // 340: create_event
  // 341:   types::event(.type_of TERMINATED .pid_of pid .status_of status)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__create_event();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__get_low_level_events_25(void) {
  myself = frame->slots[0] /* break */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__get_low_level_events_17(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 336: do: (-> break)
  // 337:   forever:
  // 338:     wait_pid $status $pid -1 true
  // 339:     if pid <= 0 break
  // 340:     create_event
  // 341:       types::event(.type_of TERMINATED .pid_of pid .status_of status)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__get_low_level_events_18;
  result_count = frame->caller_result_count;
  myself = get__do();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__get_low_level_events_26(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 342: if window_changed_size:
  // 343:   get_terminal_size STDIN_FILENO $width $height
  // 344:   create_event
  // 345:     types::event
  // 346:       .type_of SCREEN_SIZE_CHANGE
  // 347:       .width_of width
  // 348:       .height_of height
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* window_changed_size */;
  arguments->slots[1] = func__get_low_level_events_27;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__get_low_level_events_29;
}
static void entry__get_low_level_events_27(void) {
  allocate_initialized_frame_gc(0, 3);
  // slot allocations:
  // width: 0
  // height: 1
  frame->slots[0] /* width */ = create_future();
  frame->slots[1] /* height */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 343: get_terminal_size STDIN_FILENO $width $height
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__STDIN_FILENO();
  result_count = 2;
  myself = get__get_terminal_size();
  func = myself->type;
  frame->cont = cont__get_low_level_events_28;
}
static void cont__get_low_level_events_28(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[0] /* width */, arguments->slots[0]);
  initialize_future(frame->slots[1] /* height */, arguments->slots[1]);
  {
    NODE *temp = clone_object_and_attributes(var.types__event);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__type_of, get__SCREEN_SIZE_CHANGE());
    set_attribute_value(temp->attributes, poly_idx__width_of, frame->slots[0] /* width */);
    set_attribute_value(temp->attributes, poly_idx__height_of, frame->slots[1] /* height */);
    frame->slots[2] /* temp__1 */ = temp;

  }
  // 344: create_event
  // 345:   types::event
  // 346:     .type_of SCREEN_SIZE_CHANGE
  // 347:     .width_of width
  // 348:     .height_of height
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__create_event();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__get_low_level_events_29(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 349: $$ready_input_fds_set empty_set
  ((CELL *)frame->slots[5])->contents /* ready_input_fds_set */ = get__empty_set();
  // 350: $$ready_output_fds_set empty_set
  ((CELL *)frame->slots[6])->contents /* ready_output_fds_set */ = get__empty_set();
  // 351: $$ready_exception_fds_set empty_set
  ((CELL *)frame->slots[7])->contents /* ready_exception_fds_set */ = get__empty_set();
  // 352: ... : (ready_input_fd)
  // 353:   !ready_input_fds_set(ready_input_fd) true
  frame->slots[8] /* temp__1 */ = create_closure(entry__get_low_level_events_30, 1);
  // 352: for_each ready_input_fds_list: (ready_input_fd)
  // 353:   !ready_input_fds_set(ready_input_fd) true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* ready_input_fds_list */;
  arguments->slots[1] = frame->slots[8] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__get_low_level_events_32;
}
static void entry__get_low_level_events_30(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // ready_input_fd: 0
  // ready_input_fds_set: 1
  frame->slots[1] = myself->closure.frame->slots[5]; /* ready_input_fds_set */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 353: !ready_input_fds_set(ready_input_fd)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* ready_input_fd */;
  arguments->slots[1] = get__true();
  result_count = 1;
  myself = ((CELL *)frame->slots[1])->contents /* ready_input_fds_set */;
  func = myself->type;
  frame->cont = cont__get_low_level_events_31;
}
static void cont__get_low_level_events_31(void) {
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
static void cont__get_low_level_events_32(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 354: ... : (ready_output_fd)
  // 355:   !ready_output_fds_set(ready_output_fd) true
  frame->slots[8] /* temp__1 */ = create_closure(entry__get_low_level_events_33, 1);
  // 354: for_each ready_output_fds_list: (ready_output_fd)
  // 355:   !ready_output_fds_set(ready_output_fd) true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* ready_output_fds_list */;
  arguments->slots[1] = frame->slots[8] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__get_low_level_events_35;
}
static void entry__get_low_level_events_33(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // ready_output_fd: 0
  // ready_output_fds_set: 1
  frame->slots[1] = myself->closure.frame->slots[6]; /* ready_output_fds_set */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 355: !ready_output_fds_set(ready_output_fd)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* ready_output_fd */;
  arguments->slots[1] = get__true();
  result_count = 1;
  myself = ((CELL *)frame->slots[1])->contents /* ready_output_fds_set */;
  func = myself->type;
  frame->cont = cont__get_low_level_events_34;
}
static void cont__get_low_level_events_34(void) {
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
static void cont__get_low_level_events_35(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 356: ... : (ready_exception_fd)
  // 357:   !ready_exception_fds_set(ready_exception_fd) true
  frame->slots[8] /* temp__1 */ = create_closure(entry__get_low_level_events_36, 1);
  // 356: for_each ready_exception_fds_list: (ready_exception_fd)
  // 357:   !ready_exception_fds_set(ready_exception_fd) true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* ready_exception_fds_list */;
  arguments->slots[1] = frame->slots[8] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__get_low_level_events_38;
}
static void entry__get_low_level_events_36(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // ready_exception_fd: 0
  // ready_exception_fds_set: 1
  frame->slots[1] = myself->closure.frame->slots[7]; /* ready_exception_fds_set */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 357: !ready_exception_fds_set(ready_exception_fd)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* ready_exception_fd */;
  arguments->slots[1] = get__true();
  result_count = 1;
  myself = ((CELL *)frame->slots[1])->contents /* ready_exception_fds_set */;
  func = myself->type;
  frame->cont = cont__get_low_level_events_37;
}
static void cont__get_low_level_events_37(void) {
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
static void cont__get_low_level_events_38(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 358: for_each ready_input_fds_set: (input_fd)
  // 359:   if wanted_input_fds(input_fd):
  // 360:     create_event
  // 361:       types::event(.type_of READ_FROM .file_descriptor_of input_fd)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[5])->contents /* ready_input_fds_set */;
  arguments->slots[1] = func__get_low_level_events_39;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__get_low_level_events_42;
}
static void entry__get_low_level_events_41(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // input_fd: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* input_fd */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 361: types::event(.type_of READ_FROM .file_descriptor_of input_fd)
  {
    NODE *temp = clone_object_and_attributes(var.types__event);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__type_of, get__READ_FROM());
    set_attribute_value(temp->attributes, poly_idx__file_descriptor_of, frame->slots[0] /* input_fd */);
    frame->slots[1] /* temp__1 */ = temp;

  }
  // 360: create_event
  // 361:   types::event(.type_of READ_FROM .file_descriptor_of input_fd)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__create_event();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__get_low_level_events_39(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // input_fd: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 359: ... wanted_input_fds(input_fd)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* input_fd */;
  result_count = 1;
  myself = var._wanted_input_fds;
  func = myself->type;
  frame->cont = cont__get_low_level_events_40;
}
static void cont__get_low_level_events_40(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 359: ... :
  // 360:   create_event
  // 361:     types::event(.type_of READ_FROM .file_descriptor_of input_fd)
  frame->slots[2] /* temp__2 */ = create_closure(entry__get_low_level_events_41, 0);
  // 359: if wanted_input_fds(input_fd):
  // 360:   create_event
  // 361:     types::event(.type_of READ_FROM .file_descriptor_of input_fd)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__get_low_level_events_42(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 362: for_each ready_output_fds_set: (output_fd)
  // 363:   if wanted_output_fds(output_fd):
  // 364:     create_event
  // 365:       types::event(.type_of WRITE_TO .file_descriptor_of output_fd)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[6])->contents /* ready_output_fds_set */;
  arguments->slots[1] = func__get_low_level_events_43;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__get_low_level_events_46(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 367: ... types::event(.type_of TIMEOUT)
  {
    NODE *temp = clone_object_and_attributes(var.types__event);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__type_of, get__TIMEOUT());
    frame->slots[0] /* temp__1 */ = temp;

  }
  // 367: create_event types::event(.type_of TIMEOUT)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__create_event();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__get_low_level_events_1(void) {
  allocate_initialized_frame_gc(1, 11);
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
  // 312: $$output_fds_list empty_list
  ((CELL *)frame->slots[1])->contents /* output_fds_list */ = get__empty_list();
  // 313: $$input_fds_list empty_list
  ((CELL *)frame->slots[2])->contents /* input_fds_list */ = get__empty_list();
  // 314: $exception_fds_list empty_list
  initialize_maybe_future(frame->slots[3] /* exception_fds_list */, get__empty_list());
  // 316: ... :
  // 317:   for_each writers: (output_fd _continuation)
  // 318:     push &output_fds_list output_fd
  // 319:   for_each readers: (input_fd _continuation) push &input_fds_list input_fd
  frame->slots[9] /* temp__1 */ = create_closure(entry__get_low_level_events_2, 0);
  // 320: :
  // 321:   for_each wanted_output_fds: (output_fd) push &output_fds_list output_fd
  // 322:   for_each wanted_input_fds: (input_fd) push &input_fds_list input_fd
  frame->slots[10] /* temp__2 */ = create_closure(entry__get_low_level_events_8, 0);
  // 315: if
  // 316:   for_readers_and_writers_only:
  // 317:     for_each writers: (output_fd _continuation)
  // 318:       push &output_fds_list output_fd
  // 319:     for_each readers: (input_fd _continuation) push &input_fds_list input_fd
  // 320:   :
  // 321:     for_each wanted_output_fds: (output_fd) push &output_fds_list output_fd
  // 322:     for_each wanted_input_fds: (input_fd) push &input_fds_list input_fd
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* for_readers_and_writers_only */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  arguments->slots[2] = frame->slots[10] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__get_low_level_events_14;
}
static void entry__get_low_level_events_12(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // input_fd: 0
  // input_fds_list: 1
  frame->slots[1] = myself->closure.frame->slots[1]; /* input_fds_list */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 322: ... push &input_fds_list input_fd
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* input_fds_list */;
  arguments->slots[1] = frame->slots[0] /* input_fd */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__get_low_level_events_13;
}
static void cont__get_low_level_events_13(void) {
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
static void entry__get_low_level_events_6(void) {
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
  // 319: ... push &input_fds_list input_fd
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* input_fds_list */;
  arguments->slots[1] = frame->slots[0] /* input_fd */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__get_low_level_events_7;
}
static void cont__get_low_level_events_7(void) {
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
static void entry__get_low_level_events_2(void) {
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
  // 317: ... : (output_fd _continuation)
  // 318:   push &output_fds_list output_fd
  frame->slots[2] /* temp__1 */ = create_closure(entry__get_low_level_events_3, 2);
  // 317: for_each writers: (output_fd _continuation)
  // 318:   push &output_fds_list output_fd
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._writers;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__get_low_level_events_5;
}
static void entry__get_low_level_events_3(void) {
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
  // 318: push &output_fds_list output_fd
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* output_fds_list */;
  arguments->slots[1] = frame->slots[0] /* output_fd */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__get_low_level_events_4;
}
static void cont__get_low_level_events_4(void) {
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
static void cont__get_low_level_events_5(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 319: ... : (input_fd _continuation) push &input_fds_list input_fd
  frame->slots[2] /* temp__1 */ = create_closure(entry__get_low_level_events_6, 2);
  // 319: for_each readers: (input_fd _continuation) push &input_fds_list input_fd
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._readers;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__get_low_level_events_8(void) {
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
  // 321: ... : (output_fd) push &output_fds_list output_fd
  frame->slots[2] /* temp__1 */ = create_closure(entry__get_low_level_events_9, 1);
  // 321: for_each wanted_output_fds: (output_fd) push &output_fds_list output_fd
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._wanted_output_fds;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__get_low_level_events_11;
}
static void entry__get_low_level_events_9(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // output_fd: 0
  // output_fds_list: 1
  frame->slots[1] = myself->closure.frame->slots[0]; /* output_fds_list */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 321: ... push &output_fds_list output_fd
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* output_fds_list */;
  arguments->slots[1] = frame->slots[0] /* output_fd */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__get_low_level_events_10;
}
static void cont__get_low_level_events_10(void) {
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
static void cont__get_low_level_events_11(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 322: ... : (input_fd) push &input_fds_list input_fd
  frame->slots[2] /* temp__1 */ = create_closure(entry__get_low_level_events_12, 1);
  // 322: for_each wanted_input_fds: (input_fd) push &input_fds_list input_fd
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._wanted_input_fds;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__get_low_level_events_14(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* input_fds_list */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* output_fds_list */;
  arguments->slots[2] = frame->slots[3] /* exception_fds_list */;
  arguments->slots[3] = var._timeout;
  result_count = 6;
  myself = get__wait_for_io();
  func = myself->type;
  frame->cont = cont__get_low_level_events_15;
}
static void cont__get_low_level_events_15(void) {
  if (argument_count != 6) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* child_changed_state */, arguments->slots[0]);
  initialize_future(frame->slots[5] /* window_changed_size */, arguments->slots[1]);
  initialize_future(frame->slots[6] /* ready_input_fds_list */, arguments->slots[2]);
  initialize_future(frame->slots[7] /* ready_output_fds_list */, arguments->slots[3]);
  initialize_future(frame->slots[8] /* ready_exception_fds_list */, arguments->slots[4]);
  frame->slots[9] /* temp__1 */ = arguments->slots[5];
  // 334: :
  // 335:   if child_changed_state:
  // 336:     do: (-> break)
  // 337:       forever:
  // 338:         wait_pid $status $pid -1 true
  // 339:         if pid <= 0 break
  // 340:         create_event
  // 341:           types::event(.type_of TERMINATED .pid_of pid .status_of status)
  // 342:   if window_changed_size:
  // 343:     get_terminal_size STDIN_FILENO $width $height
  // ...
  frame->slots[10] /* temp__2 */ = create_closure(entry__get_low_level_events_16, 0);
  // 323: if
  // 324:   wait_for_io
  // 325:     $child_changed_state
  // 326:     $window_changed_size
  // 327:     $ready_input_fds_list
  // 328:     input_fds_list
  // 329:     $ready_output_fds_list
  // 330:     output_fds_list
  // 331:     $ready_exception_fds_list
  // 332:     exception_fds_list
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  arguments->slots[1] = frame->slots[10] /* temp__2 */;
  arguments->slots[2] = func__get_low_level_events_46;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__get_event_handler_1(void) {
  allocate_initialized_frame_gc(2, 7);
  // slot allocations:
  // event: 0
  // return: 1
  frame->slots[1] /* return */ = create_continuation();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 374: ... type_of(event)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* event */;
  result_count = 1;
  myself = get__type_of();
  func = myself->type;
  frame->cont = cont__get_event_handler_2;
}
static void cont__get_event_handler_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 375: ... :
  // 376:   $fd file_descriptor_of(event)
  // 377:   $reader readers(fd)
  // 378:   if reader.is_defined:
  // 379:     no_longer_want_to_read_from fd
  // 380:     !readers(fd) undefined
  // 381:     return reader
  frame->slots[3] /* temp__2 */ = create_closure(entry__get_event_handler_3, 0);
  // 382: ... :
  // 383:   $fd file_descriptor_of(event)
  // 384:   $writer writers(fd)
  // 385:   if writer.is_defined:
  // 386:     no_longer_want_to_write_to fd
  // 387:     !writers(fd) undefined
  // 388:     return writer
  frame->slots[4] /* temp__3 */ = create_closure(entry__get_event_handler_10, 0);
  // 389: ... :
  // 390:   $pid pid_of(event)
  // 391:   $terminator terminators(pid)
  // 392:   if terminator.is_defined:
  // 393:     !terminators(pid) undefined
  // 394:     return terminator
  frame->slots[5] /* temp__4 */ = create_closure(entry__get_event_handler_17, 0);
  // 395: ... :
  // 396:   return timeout_exceeded
  frame->slots[6] /* temp__5 */ = create_closure(entry__get_event_handler_23, 0);
  // 374: case type_of(event)
  // 375:   READ_FROM:
  // 376:     $fd file_descriptor_of(event)
  // 377:     $reader readers(fd)
  // 378:     if reader.is_defined:
  // 379:       no_longer_want_to_read_from fd
  // 380:       !readers(fd) undefined
  // 381:       return reader
  // 382:   WRITE_TO:
  // 383:     $fd file_descriptor_of(event)
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
  frame->cont = cont__get_event_handler_24;
}
static void entry__get_event_handler_21(void) {
  allocate_initialized_frame_gc(3, 3);
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
  // 393: !terminators(pid)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* pid */;
  arguments->slots[1] = get__undefined();
  result_count = 1;
  myself = var._terminators;
  func = myself->type;
  frame->cont = cont__get_event_handler_22;
}
static void cont__get_event_handler_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._terminators = arguments->slots[0];
  // 394: return terminator
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* terminator */;
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__get_event_handler_14(void) {
  allocate_initialized_frame_gc(3, 3);
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
  // 386: no_longer_want_to_write_to fd
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd */;
  result_count = 0;
  myself = get__no_longer_want_to_write_to();
  func = myself->type;
  frame->cont = cont__get_event_handler_15;
}
static void cont__get_event_handler_15(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 387: !writers(fd)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd */;
  arguments->slots[1] = get__undefined();
  result_count = 1;
  myself = var._writers;
  func = myself->type;
  frame->cont = cont__get_event_handler_16;
}
static void cont__get_event_handler_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._writers = arguments->slots[0];
  // 388: return writer
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* writer */;
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__get_event_handler_7(void) {
  allocate_initialized_frame_gc(3, 3);
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
  // 379: no_longer_want_to_read_from fd
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd */;
  result_count = 0;
  myself = get__no_longer_want_to_read_from();
  func = myself->type;
  frame->cont = cont__get_event_handler_8;
}
static void cont__get_event_handler_8(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 380: !readers(fd)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd */;
  arguments->slots[1] = get__undefined();
  result_count = 1;
  myself = var._readers;
  func = myself->type;
  frame->cont = cont__get_event_handler_9;
}
static void cont__get_event_handler_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._readers = arguments->slots[0];
  // 381: return reader
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* reader */;
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__get_event_handler_3(void) {
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
  // 376: $fd file_descriptor_of(event)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* event */;
  result_count = 1;
  myself = get__file_descriptor_of();
  func = myself->type;
  frame->cont = cont__get_event_handler_4;
}
static void cont__get_event_handler_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* fd */, arguments->slots[0]);
  // 377: $reader readers(fd)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* fd */;
  result_count = 1;
  myself = var._readers;
  func = myself->type;
  frame->cont = cont__get_event_handler_5;
}
static void cont__get_event_handler_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* reader */, arguments->slots[0]);
  // 378: ... reader.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* reader */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__get_event_handler_6;
}
static void cont__get_event_handler_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 378: ... :
  // 379:   no_longer_want_to_read_from fd
  // 380:   !readers(fd) undefined
  // 381:   return reader
  frame->slots[5] /* temp__2 */ = create_closure(entry__get_event_handler_7, 0);
  // 378: if reader.is_defined:
  // 379:   no_longer_want_to_read_from fd
  // 380:   !readers(fd) undefined
  // 381:   return reader
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__get_event_handler_10(void) {
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
  // 383: $fd file_descriptor_of(event)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* event */;
  result_count = 1;
  myself = get__file_descriptor_of();
  func = myself->type;
  frame->cont = cont__get_event_handler_11;
}
static void cont__get_event_handler_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* fd */, arguments->slots[0]);
  // 384: $writer writers(fd)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* fd */;
  result_count = 1;
  myself = var._writers;
  func = myself->type;
  frame->cont = cont__get_event_handler_12;
}
static void cont__get_event_handler_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* writer */, arguments->slots[0]);
  // 385: ... writer.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* writer */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__get_event_handler_13;
}
static void cont__get_event_handler_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 385: ... :
  // 386:   no_longer_want_to_write_to fd
  // 387:   !writers(fd) undefined
  // 388:   return writer
  frame->slots[5] /* temp__2 */ = create_closure(entry__get_event_handler_14, 0);
  // 385: if writer.is_defined:
  // 386:   no_longer_want_to_write_to fd
  // 387:   !writers(fd) undefined
  // 388:   return writer
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__get_event_handler_17(void) {
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
  // 390: $pid pid_of(event)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* event */;
  result_count = 1;
  myself = get__pid_of();
  func = myself->type;
  frame->cont = cont__get_event_handler_18;
}
static void cont__get_event_handler_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* pid */, arguments->slots[0]);
  // 391: $terminator terminators(pid)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* pid */;
  result_count = 1;
  myself = var._terminators;
  func = myself->type;
  frame->cont = cont__get_event_handler_19;
}
static void cont__get_event_handler_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* terminator */, arguments->slots[0]);
  // 392: ... terminator.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* terminator */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__get_event_handler_20;
}
static void cont__get_event_handler_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 392: ... :
  // 393:   !terminators(pid) undefined
  // 394:   return terminator
  frame->slots[5] /* temp__2 */ = create_closure(entry__get_event_handler_21, 0);
  // 392: if terminator.is_defined:
  // 393:   !terminators(pid) undefined
  // 394:   return terminator
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__get_event_handler_23(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 396: return timeout_exceeded
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._timeout_exceeded;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__get_event_handler_24(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 397: -> undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  myself = frame->slots[1] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__std__get_event_1(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // return: 0
  frame->slots[0] /* return */ = create_continuation();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 411: ... : (myself^)
  // 412:   if
  // 413:     length_of(events) > 0:
  // 414:       $event get(&events)
  // 415:       $handler get_event_handler(event)
  // 416:       if handler.is_defined:
  // 417:         put &waiting_tasks myself
  // 418:         if
  // 419:           parameter_count_of(handler) == 1:
  // 420:             handler event
  // ...
  frame->slots[1] /* temp__1 */ = create_closure(entry__std__get_event_2, 0);
  // 411: forever: (myself^)
  // 412:   if
  // 413:     length_of(events) > 0:
  // 414:       $event get(&events)
  // 415:       $handler get_event_handler(event)
  // 416:       if handler.is_defined:
  // 417:         put &waiting_tasks myself
  // 418:         if
  // 419:           parameter_count_of(handler) == 1:
  // 420:             handler event
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__forever();
  func = myself->type;
  frame->cont = cont__std__get_event_19;
}
static void entry__std__get_event_5(void) {
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
  // 414: $event get(&events)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__events();
  result_count = 2;
  myself = get__get();
  func = myself->type;
  frame->cont = cont__std__get_event_6;
}
static void cont__std__get_event_6(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  set__events(arguments->slots[0]);
  initialize_future(frame->slots[2] /* event */, arguments->slots[1]);
  // 415: $handler get_event_handler(event)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* event */;
  result_count = 1;
  myself = var._get_event_handler;
  func = myself->type;
  frame->cont = cont__std__get_event_7;
}
static void cont__std__get_event_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* handler */, arguments->slots[0]);
  // 416: ... handler.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* handler */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__std__get_event_8;
}
static void cont__std__get_event_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 416: ... :
  // 417:   put &waiting_tasks myself
  // 418:   if
  // 419:     parameter_count_of(handler) == 1:
  // 420:       handler event
  // 421:     :
  // 422:       handler
  // 423:   raise "invalid continuation"
  frame->slots[5] /* temp__2 */ = create_closure(entry__std__get_event_9, 0);
  // 416: if handler.is_defined:
  // 417:   put &waiting_tasks myself
  // 418:   if
  // 419:     parameter_count_of(handler) == 1:
  // 420:       handler event
  // 421:     :
  // 422:       handler
  // 423:   raise "invalid continuation"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__std__get_event_17;
}
static void entry__std__get_event_9(void) {
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
  // 417: put &waiting_tasks myself
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._waiting_tasks;
  arguments->slots[1] = frame->slots[0] /* myself */;
  result_count = 1;
  myself = get__put();
  func = myself->type;
  frame->cont = cont__std__get_event_10;
}
static void cont__std__get_event_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._waiting_tasks = arguments->slots[0];
  // 419: parameter_count_of(handler)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* handler */;
  result_count = 1;
  myself = get__parameter_count_of();
  func = myself->type;
  frame->cont = cont__std__get_event_11;
}
static void cont__std__get_event_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 419: parameter_count_of(handler) == 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__std__get_event_12;
}
static void cont__std__get_event_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 419: ... :
  // 420:   handler event
  frame->slots[5] /* temp__3 */ = create_closure(entry__std__get_event_13, 0);
  // 421: :
  // 422:   handler
  frame->slots[6] /* temp__4 */ = create_closure(entry__std__get_event_14, 0);
  // 418: if
  // 419:   parameter_count_of(handler) == 1:
  // 420:     handler event
  // 421:   :
  // 422:     handler
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  arguments->slots[2] = frame->slots[6] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__std__get_event_15;
}
static void entry__std__get_event_13(void) {
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
  // 420: handler event
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* event */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* handler */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__get_event_14(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // handler: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* handler */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 422: handler
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* handler */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__std__get_event_15(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 423: raise "invalid continuation"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__66e3787d9d72e485;
  result_count = frame->caller_result_count;
  myself = get__raise();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__std__get_event_17(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 424: return event
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* event */;
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__get_event_18(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 426: get_low_level_events false
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__false();
  result_count = frame->caller_result_count;
  myself = var._get_low_level_events;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__get_event_2(void) {
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
  // 413: length_of(events)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__events();
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__std__get_event_3;
}
static void cont__std__get_event_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 413: length_of(events) > 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__std__get_event_4;
}
static void cont__std__get_event_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 413: ... :
  // 414:   $event get(&events)
  // 415:   $handler get_event_handler(event)
  // 416:   if handler.is_defined:
  // 417:     put &waiting_tasks myself
  // 418:     if
  // 419:       parameter_count_of(handler) == 1:
  // 420:         handler event
  // 421:       :
  // 422:         handler
  // ...
  frame->slots[4] /* temp__3 */ = create_closure(entry__std__get_event_5, 0);
  // 412: if
  // 413:   length_of(events) > 0:
  // 414:     $event get(&events)
  // 415:     $handler get_event_handler(event)
  // 416:     if handler.is_defined:
  // 417:       put &waiting_tasks myself
  // 418:       if
  // 419:         parameter_count_of(handler) == 1:
  // 420:           handler event
  // 421:         :
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  arguments->slots[2] = func__std__get_event_18;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__std__get_event_19(void) {
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__std__process_events_13(void) {
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
  // 440: $n length_of(events)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__events();
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__std__process_events_14;
}
static void cont__std__process_events_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* n */, arguments->slots[0]);
  // 441: ... -> i <= n:
  // 442:   $event events(i)
  // 443:   $handler get_event_handler(event)
  // 444:   if handler.is_defined:
  // 445:     delete_at &events i
  // 446:     if
  // 447:       parameter_count_of(handler) == 1:
  // 448:         handler event
  // 449:       :
  // 450:         handler
  // ...
  frame->slots[2] /* temp__1 */ = create_closure(entry__std__process_events_15, 0);
  // 441: while -> i <= n:
  // 442:   $event events(i)
  // 443:   $handler get_event_handler(event)
  // 444:   if handler.is_defined:
  // 445:     delete_at &events i
  // 446:     if
  // 447:       parameter_count_of(handler) == 1:
  // 448:         handler event
  // 449:       :
  // 450:         handler
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__while();
  func = myself->type;
  frame->cont = cont__std__process_events_31;
}
static void entry__std__process_events_18(void) {
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
  // 442: $event events(i)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* i */;
  result_count = 1;
  myself = get__events();
  func = myself->type;
  frame->cont = cont__std__process_events_19;
}
static void cont__std__process_events_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* event */, arguments->slots[0]);
  // 443: $handler get_event_handler(event)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* event */;
  result_count = 1;
  myself = var._get_event_handler;
  func = myself->type;
  frame->cont = cont__std__process_events_20;
}
static void cont__std__process_events_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* handler */, arguments->slots[0]);
  // 444: ... handler.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* handler */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__std__process_events_21;
}
static void cont__std__process_events_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 444: ... :
  // 445:   delete_at &events i
  // 446:   if
  // 447:     parameter_count_of(handler) == 1:
  // 448:       handler event
  // 449:     :
  // 450:       handler
  // 451:   raise "invalid continuation"
  frame->slots[4] /* temp__2 */ = create_closure(entry__std__process_events_22, 0);
  // 444: if handler.is_defined:
  // 445:   delete_at &events i
  // 446:   if
  // 447:     parameter_count_of(handler) == 1:
  // 448:       handler event
  // 449:     :
  // 450:       handler
  // 451:   raise "invalid continuation"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__std__process_events_29;
}
static void entry__std__process_events_22(void) {
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
  // 445: delete_at &events i
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__events();
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* i */;
  result_count = 1;
  myself = get__delete_at();
  func = myself->type;
  frame->cont = cont__std__process_events_23;
}
static void cont__std__process_events_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__events(arguments->slots[0]);
  // 447: parameter_count_of(handler)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* handler */;
  result_count = 1;
  myself = get__parameter_count_of();
  func = myself->type;
  frame->cont = cont__std__process_events_24;
}
static void cont__std__process_events_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 447: parameter_count_of(handler) == 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__std__process_events_25;
}
static void cont__std__process_events_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 447: ... :
  // 448:   handler event
  frame->slots[5] /* temp__3 */ = create_closure(entry__std__process_events_26, 0);
  // 449: :
  // 450:   handler
  frame->slots[6] /* temp__4 */ = create_closure(entry__std__process_events_27, 0);
  // 446: if
  // 447:   parameter_count_of(handler) == 1:
  // 448:     handler event
  // 449:   :
  // 450:     handler
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  arguments->slots[2] = frame->slots[6] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__std__process_events_28;
}
static void entry__std__process_events_26(void) {
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
  // 448: handler event
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* event */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* handler */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__process_events_27(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // handler: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* handler */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 450: handler
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* handler */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__std__process_events_28(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 451: raise "invalid continuation"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__66e3787d9d72e485;
  result_count = frame->caller_result_count;
  myself = get__raise();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__std__process_events_29(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 452: inc &i
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* i */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__std__process_events_30;
}
static void cont__std__process_events_30(void) {
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
static void entry__std__process_events_15(void) {
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
  // 441: ... i <= n
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* n */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* i */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__std__process_events_16;
}
static void cont__std__process_events_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 441: ... i <= n
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__std__process_events_17;
}
static void cont__std__process_events_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 441: ... :
  // 442:   $event events(i)
  // 443:   $handler get_event_handler(event)
  // 444:   if handler.is_defined:
  // 445:     delete_at &events i
  // 446:     if
  // 447:       parameter_count_of(handler) == 1:
  // 448:         handler event
  // 449:       :
  // 450:         handler
  // ...
  frame->slots[4] /* temp__3 */ = create_closure(entry__std__process_events_18, 0);
  // 441: ... -> i <= n:
  // 442:   $event events(i)
  // 443:   $handler get_event_handler(event)
  // 444:   if handler.is_defined:
  // 445:     delete_at &events i
  // 446:     if
  // 447:       parameter_count_of(handler) == 1:
  // 448:         handler event
  // 449:       :
  // 450:         handler
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__std__process_events_31(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 453: get_low_level_events true
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__true();
  result_count = frame->caller_result_count;
  myself = var._get_low_level_events;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__process_events_1(void) {
  allocate_initialized_frame_gc(0, 3);
  // slot allocations:
  // i: 0
  frame->slots[0] /* i */ = create_cell();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 436: while -> length_of(waiting_tasks) > 0: get(&waiting_tasks)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__std__process_events_2;
  result_count = 0;
  myself = get__while();
  func = myself->type;
  frame->cont = cont__std__process_events_7;
}
static void entry__std__process_events_5(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 436: ... get(&waiting_tasks)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._waiting_tasks;
  result_count = 2;
  myself = get__get();
  func = myself->type;
  frame->cont = cont__std__process_events_6;
}
static void cont__std__process_events_6(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  var._waiting_tasks = arguments->slots[0];
  frame->slots[0] /* temp__1 */ = arguments->slots[1];
  // 436: ... get(&waiting_tasks)
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* temp__1 */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__process_events_2(void) {
  allocate_initialized_frame_gc(0, 2);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 436: ... length_of(waiting_tasks)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._waiting_tasks;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__std__process_events_3;
}
static void cont__std__process_events_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 436: ... length_of(waiting_tasks) > 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__std__process_events_4;
}
static void cont__std__process_events_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 436: ... -> length_of(waiting_tasks) > 0: get(&waiting_tasks)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = func__std__process_events_5;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__std__process_events_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 437: ... readers.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._readers;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__std__process_events_8;
}
static void cont__std__process_events_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 437: ... readers.is_empty && writers.is_empty
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = func__std__process_events_9;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__std__process_events_11;
}
static void entry__std__process_events_9(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 437: ... writers.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._writers;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__std__process_events_10;
}
static void cont__std__process_events_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 437: ... writers.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__std__process_events_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 437: if readers.is_empty && writers.is_empty terminate
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = get__terminate();
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__std__process_events_12;
}
static void cont__std__process_events_12(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 438: $$i 1
  ((CELL *)frame->slots[0])->contents /* i */ = number__1;
  // 439: ... :
  // 440:   $n length_of(events)
  // 441:   while -> i <= n:
  // 442:     $event events(i)
  // 443:     $handler get_event_handler(event)
  // 444:     if handler.is_defined:
  // 445:       delete_at &events i
  // 446:       if
  // 447:         parameter_count_of(handler) == 1:
  // 448:           handler event
  // ...
  frame->slots[1] /* temp__1 */ = create_closure(entry__std__process_events_13, 0);
  // 439: forever:
  // 440:   $n length_of(events)
  // 441:   while -> i <= n:
  // 442:     $event events(i)
  // 443:     $handler get_event_handler(event)
  // 444:     if handler.is_defined:
  // 445:       delete_at &events i
  // 446:       if
  // 447:         parameter_count_of(handler) == 1:
  // 448:           handler event
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__forever();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__wait_to_1(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // args: 0
  // event: 1
  frame->slots[1] /* event */ = create_future();
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 468: ... : (-> continuation)
  // 469:   for_each args: (arg)
  // 470:     $type key_of(arg)
  // 471:     $value value_of(arg)
  // 472:     case type
  // 473:       READ_FROM:
  // 474:         want_to_read_from value
  // 475:         !readers(value) continuation
  // 476:       WRITE_TO:
  // 477:         want_to_write_to value
  // ...
  frame->slots[2] /* temp__1 */ = create_closure(entry__std__wait_to_2, 0);
  // 468: do $event: (-> continuation)
  // 469:   for_each args: (arg)
  // 470:     $type key_of(arg)
  // 471:     $value value_of(arg)
  // 472:     case type
  // 473:       READ_FROM:
  // 474:         want_to_read_from value
  // 475:         !readers(value) continuation
  // 476:       WRITE_TO:
  // 477:         want_to_write_to value
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__std__wait_to_17;
}
static void entry__std__wait_to_2(void) {
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
  // 469: ... : (arg)
  // 470:   $type key_of(arg)
  // 471:   $value value_of(arg)
  // 472:   case type
  // 473:     READ_FROM:
  // 474:       want_to_read_from value
  // 475:       !readers(value) continuation
  // 476:     WRITE_TO:
  // 477:       want_to_write_to value
  // 478:       !writers(value) continuation
  // ...
  frame->slots[2] /* temp__1 */ = create_closure(entry__std__wait_to_3, 1);
  // 469: for_each args: (arg)
  // 470:   $type key_of(arg)
  // 471:   $value value_of(arg)
  // 472:   case type
  // 473:     READ_FROM:
  // 474:       want_to_read_from value
  // 475:       !readers(value) continuation
  // 476:     WRITE_TO:
  // 477:       want_to_write_to value
  // 478:       !writers(value) continuation
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* args */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__std__wait_to_15;
}
static void entry__std__wait_to_6(void) {
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
  // 474: want_to_read_from value
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* value */;
  result_count = 0;
  myself = get__want_to_read_from();
  func = myself->type;
  frame->cont = cont__std__wait_to_7;
}
static void cont__std__wait_to_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 475: !readers(value)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* value */;
  arguments->slots[1] = frame->slots[1] /* continuation */;
  result_count = 1;
  myself = var._readers;
  func = myself->type;
  frame->cont = cont__std__wait_to_8;
}
static void cont__std__wait_to_8(void) {
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
static void entry__std__wait_to_9(void) {
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
  // 477: want_to_write_to value
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* value */;
  result_count = 0;
  myself = get__want_to_write_to();
  func = myself->type;
  frame->cont = cont__std__wait_to_10;
}
static void cont__std__wait_to_10(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 478: !writers(value)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* value */;
  arguments->slots[1] = frame->slots[1] /* continuation */;
  result_count = 1;
  myself = var._writers;
  func = myself->type;
  frame->cont = cont__std__wait_to_11;
}
static void cont__std__wait_to_11(void) {
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
static void entry__std__wait_to_12(void) {
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
  // 480: !terminators(value)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* value */;
  arguments->slots[1] = frame->slots[1] /* continuation */;
  result_count = 1;
  myself = var._terminators;
  func = myself->type;
  frame->cont = cont__std__wait_to_13;
}
static void cont__std__wait_to_13(void) {
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
static void entry__std__wait_to_14(void) {
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
  // 482: !timeout value
  var._timeout = frame->slots[0] /* value */;
  // 483: !timeout_exceeded continuation
  var._timeout_exceeded = frame->slots[1] /* continuation */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__wait_to_3(void) {
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
  // 470: $type key_of(arg)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* arg */;
  result_count = 1;
  myself = get__key_of();
  func = myself->type;
  frame->cont = cont__std__wait_to_4;
}
static void cont__std__wait_to_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* type */, arguments->slots[0]);
  // 471: $value value_of(arg)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* arg */;
  result_count = 1;
  myself = get__value_of();
  func = myself->type;
  frame->cont = cont__std__wait_to_5;
}
static void cont__std__wait_to_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* value */, arguments->slots[0]);
  // 473: ... :
  // 474:   want_to_read_from value
  // 475:   !readers(value) continuation
  frame->slots[4] /* temp__1 */ = create_closure(entry__std__wait_to_6, 0);
  // 476: ... :
  // 477:   want_to_write_to value
  // 478:   !writers(value) continuation
  frame->slots[5] /* temp__2 */ = create_closure(entry__std__wait_to_9, 0);
  // 479: ... :
  // 480:   !terminators(value) continuation
  frame->slots[6] /* temp__3 */ = create_closure(entry__std__wait_to_12, 0);
  // 481: ... :
  // 482:   !timeout value
  // 483:   !timeout_exceeded continuation
  frame->slots[7] /* temp__4 */ = create_closure(entry__std__wait_to_14, 0);
  // 472: case type
  // 473:   READ_FROM:
  // 474:     want_to_read_from value
  // 475:     !readers(value) continuation
  // 476:   WRITE_TO:
  // 477:     want_to_write_to value
  // 478:     !writers(value) continuation
  // 479:   TERMINATED:
  // 480:     !terminators(value) continuation
  // 481:   TIMEOUT:
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
static void cont__std__wait_to_15(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 484: process_events # will never return directly
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = get__process_events();
  func = myself->type;
  frame->cont = cont__std__wait_to_16;
}
static void cont__std__wait_to_16(void) {
  myself = frame->slots[0] /* continuation */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__std__wait_to_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* event */, arguments->slots[0]);
  // 485: for_each args: (arg)
  // 486:   $type key_of(arg)
  // 487:   $value value_of(arg)
  // 488:   case type
  // 489:     READ_FROM:
  // 490:       no_longer_want_to_read_from value
  // 491:       !readers(value) undefined
  // 492:     WRITE_TO:
  // 493:       no_longer_want_to_write_to value
  // 494:       !writers(value) undefined
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* args */;
  arguments->slots[1] = func__std__wait_to_18;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__std__wait_to_29;
}
static void entry__std__wait_to_21(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // value: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* value */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 490: no_longer_want_to_read_from value
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* value */;
  result_count = 0;
  myself = get__no_longer_want_to_read_from();
  func = myself->type;
  frame->cont = cont__std__wait_to_22;
}
static void cont__std__wait_to_22(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 491: !readers(value)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* value */;
  arguments->slots[1] = get__undefined();
  result_count = 1;
  myself = var._readers;
  func = myself->type;
  frame->cont = cont__std__wait_to_23;
}
static void cont__std__wait_to_23(void) {
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
static void entry__std__wait_to_24(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // value: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* value */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 493: no_longer_want_to_write_to value
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* value */;
  result_count = 0;
  myself = get__no_longer_want_to_write_to();
  func = myself->type;
  frame->cont = cont__std__wait_to_25;
}
static void cont__std__wait_to_25(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 494: !writers(value)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* value */;
  arguments->slots[1] = get__undefined();
  result_count = 1;
  myself = var._writers;
  func = myself->type;
  frame->cont = cont__std__wait_to_26;
}
static void cont__std__wait_to_26(void) {
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
static void entry__std__wait_to_27(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // value: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* value */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 496: !terminators(value)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* value */;
  arguments->slots[1] = get__undefined();
  result_count = 1;
  myself = var._terminators;
  func = myself->type;
  frame->cont = cont__std__wait_to_28;
}
static void cont__std__wait_to_28(void) {
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
static void entry__std__wait_to_18(void) {
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
  // 486: $type key_of(arg)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* arg */;
  result_count = 1;
  myself = get__key_of();
  func = myself->type;
  frame->cont = cont__std__wait_to_19;
}
static void cont__std__wait_to_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* type */, arguments->slots[0]);
  // 487: $value value_of(arg)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* arg */;
  result_count = 1;
  myself = get__value_of();
  func = myself->type;
  frame->cont = cont__std__wait_to_20;
}
static void cont__std__wait_to_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* value */, arguments->slots[0]);
  // 489: ... :
  // 490:   no_longer_want_to_read_from value
  // 491:   !readers(value) undefined
  frame->slots[3] /* temp__1 */ = create_closure(entry__std__wait_to_21, 0);
  // 492: ... :
  // 493:   no_longer_want_to_write_to value
  // 494:   !writers(value) undefined
  frame->slots[4] /* temp__2 */ = create_closure(entry__std__wait_to_24, 0);
  // 495: ... :
  // 496:   !terminators(value) undefined
  frame->slots[5] /* temp__3 */ = create_closure(entry__std__wait_to_27, 0);
  // 488: case type
  // 489:   READ_FROM:
  // 490:     no_longer_want_to_read_from value
  // 491:     !readers(value) undefined
  // 492:   WRITE_TO:
  // 493:     no_longer_want_to_write_to value
  // 494:     !writers(value) undefined
  // 495:   TERMINATED:
  // 496:     !terminators(value) undefined
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
static void cont__std__wait_to_29(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 497: !timeout undefined
  var._timeout = get__undefined();
  // 498: !timeout_exceeded undefined
  var._timeout_exceeded = get__undefined();
  // 499: -> event
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* event */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__par_1(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // tasks: 0
  frame->slots[0] /* tasks */ = from_arguments(0, argument_count-0);
  // 507: append &waiting_tasks tasks
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._waiting_tasks;
  arguments->slots[1] = frame->slots[0] /* tasks */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__std__par_2;
}
static void cont__std__par_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._waiting_tasks = arguments->slots[0];
  // 508: process_events
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
}

static int already_run_phase_2 = false;

EXPORT void phase_2__basic__event(void) {
  if (already_run_phase_2) return;
  already_run_phase_2 = true;
  set_module("basic__event");
  number__0 = from_uint32(0U);
  number__1 = from_uint32(1U);
  unique__std__WRITE_TO = register_unique_item("std__WRITE_TO");
  unique__std__READ_FROM = register_unique_item("std__READ_FROM");
  define_polymorphic_function_with_setter("std", "file_descriptor_of", get__std__file_descriptor_of, &poly_idx__std__file_descriptor_of, &var.std__file_descriptor_of);
  unique__std__TERMINATED = register_unique_item("std__TERMINATED");
  define_polymorphic_function_with_setter("std", "pid_of", get__std__pid_of, &poly_idx__std__pid_of, &var.std__pid_of);
  define_polymorphic_function_with_setter("std", "status_of", get__std__status_of, &poly_idx__std__status_of, &var.std__status_of);
  unique__std__TIMEOUT = register_unique_item("std__TIMEOUT");
  unique__std__SCREEN_SIZE_CHANGE = register_unique_item("std__SCREEN_SIZE_CHANGE");
  define_polymorphic_function_with_setter("std", "width_of", get__std__width_of, &poly_idx__std__width_of, &var.std__width_of);
  define_polymorphic_function_with_setter("std", "height_of", get__std__height_of, &poly_idx__std__height_of, &var.std__height_of);
  unique__std__KEY_PRESS = register_unique_item("std__KEY_PRESS");
  define_polymorphic_function_with_setter("std", "key_code_of", get__std__key_code_of, &poly_idx__std__key_code_of, &var.std__key_code_of);
  unique__std__MOUSE_CLICK = register_unique_item("std__MOUSE_CLICK");
  define_polymorphic_function_with_setter("std", "target_of", get__std__target_of, &poly_idx__std__target_of, &var.std__target_of);
  unique__std__PASTE = register_unique_item("std__PASTE");
  unique__std__MESSAGE = register_unique_item("std__MESSAGE");
  func__std__want_to_write_to_1 = create_function(entry__std__want_to_write_to_1, 1);
  func__std__no_longer_want_to_write_to_1 = create_function(entry__std__no_longer_want_to_write_to_1, 1);
  func__std__want_to_read_from_1 = create_function(entry__std__want_to_read_from_1, 1);
  func__std__no_longer_want_to_read_from_1 = create_function(entry__std__no_longer_want_to_read_from_1, 1);
  func__std__wanting_to_write_to_1 = create_function(entry__std__wanting_to_write_to_1, 1);
  func__std__wanting_to_read_from_1 = create_function(entry__std__wanting_to_read_from_1, 1);
  func__std__wait_to_read_from_1 = create_function(entry__std__wait_to_read_from_1, 1);
  func__std__wait_to_write_to_1 = create_function(entry__std__wait_to_write_to_1, 1);
  func__std__wait_for_termination_1 = create_function(entry__std__wait_for_termination_1, 1);
  func__std__discard_1 = create_function(entry__std__discard_1, 1);
  func__std__create_event_1 = create_function(entry__std__create_event_1, 1);
  func__get_low_level_events_18 = create_function(entry__get_low_level_events_18, 0);
  func__get_low_level_events_17 = create_function(entry__get_low_level_events_17, 0);
  func__get_low_level_events_27 = create_function(entry__get_low_level_events_27, 0);
  func__get_low_level_events_39 = create_function(entry__get_low_level_events_39, 1);
  func__get_low_level_events_43 = create_function(entry__get_low_level_events_43, 1);
  func__get_low_level_events_46 = create_function(entry__get_low_level_events_46, 0);
  func__get_low_level_events_1 = create_function(entry__get_low_level_events_1, 1);
  func__get_event_handler_1 = create_function(entry__get_event_handler_1, 1);
  string__66e3787d9d72e485 = from_latin_1_string("invalid continuation", 20);
  func__std__get_event_18 = create_function(entry__std__get_event_18, 0);
  func__std__get_event_1 = create_function(entry__std__get_event_1, 0);
  func__std__process_events_5 = create_function(entry__std__process_events_5, 0);
  func__std__process_events_2 = create_function(entry__std__process_events_2, 0);
  func__std__process_events_9 = create_function(entry__std__process_events_9, 0);
  func__std__process_events_1 = create_function(entry__std__process_events_1, 0);
  func__std__wait_to_18 = create_function(entry__std__wait_to_18, 1);
  func__std__wait_to_1 = create_function(entry__std__wait_to_1, -1);
  func__std__par_1 = create_function(entry__std__par_1, -1);
}

static int already_run_phase_3 = false;

EXPORT void phase_3__basic__event(void) {
  if (already_run_phase_3) return;
  already_run_phase_3 = true;
  set_module("basic__event");
  set_used_namespaces(used_namespaces);
  var.std__WRITE_TO = create_future();
  define_single_assign_static("std", "WRITE_TO", get__std__WRITE_TO, &var.std__WRITE_TO);
  var.std__READ_FROM = create_future();
  define_single_assign_static("std", "READ_FROM", get__std__READ_FROM, &var.std__READ_FROM);
  var.std__TERMINATED = create_future();
  define_single_assign_static("std", "TERMINATED", get__std__TERMINATED, &var.std__TERMINATED);
  var.std__TIMEOUT = create_future();
  define_single_assign_static("std", "TIMEOUT", get__std__TIMEOUT, &var.std__TIMEOUT);
  var.std__SCREEN_SIZE_CHANGE = create_future();
  define_single_assign_static("std", "SCREEN_SIZE_CHANGE", get__std__SCREEN_SIZE_CHANGE, &var.std__SCREEN_SIZE_CHANGE);
  var.std__KEY_PRESS = create_future();
  define_single_assign_static("std", "KEY_PRESS", get__std__KEY_PRESS, &var.std__KEY_PRESS);
  var.std__MOUSE_CLICK = create_future();
  define_single_assign_static("std", "MOUSE_CLICK", get__std__MOUSE_CLICK, &var.std__MOUSE_CLICK);
  var.std__PASTE = create_future();
  define_single_assign_static("std", "PASTE", get__std__PASTE, &var.std__PASTE);
  var.std__MESSAGE = create_future();
  define_single_assign_static("std", "MESSAGE", get__std__MESSAGE, &var.std__MESSAGE);
  var.types__event = create_future();
  define_single_assign_static("types", "event", get__types__event, &var.types__event);
  define_multi_assign_static("std", "events", get__std__events, set__std__events);
  var.std__want_to_write_to = create_future();
  define_single_assign_static("std", "want_to_write_to", get__std__want_to_write_to, &var.std__want_to_write_to);
  var.std__no_longer_want_to_write_to = create_future();
  define_single_assign_static("std", "no_longer_want_to_write_to", get__std__no_longer_want_to_write_to, &var.std__no_longer_want_to_write_to);
  var.std__want_to_read_from = create_future();
  define_single_assign_static("std", "want_to_read_from", get__std__want_to_read_from, &var.std__want_to_read_from);
  var.std__no_longer_want_to_read_from = create_future();
  define_single_assign_static("std", "no_longer_want_to_read_from", get__std__no_longer_want_to_read_from, &var.std__no_longer_want_to_read_from);
  var.std__wanting_to_write_to = create_future();
  define_single_assign_static("std", "wanting_to_write_to", get__std__wanting_to_write_to, &var.std__wanting_to_write_to);
  var.std__wanting_to_read_from = create_future();
  define_single_assign_static("std", "wanting_to_read_from", get__std__wanting_to_read_from, &var.std__wanting_to_read_from);
  var.std__wait_to_read_from = create_future();
  define_single_assign_static("std", "wait_to_read_from", get__std__wait_to_read_from, &var.std__wait_to_read_from);
  var.std__wait_to_write_to = create_future();
  define_single_assign_static("std", "wait_to_write_to", get__std__wait_to_write_to, &var.std__wait_to_write_to);
  var.std__wait_for_termination = create_future();
  define_single_assign_static("std", "wait_for_termination", get__std__wait_for_termination, &var.std__wait_for_termination);
  var.std__discard = create_future();
  define_single_assign_static("std", "discard", get__std__discard, &var.std__discard);
  var.std__create_event = create_future();
  define_single_assign_static("std", "create_event", get__std__create_event, &var.std__create_event);
  var.std__get_event = create_future();
  define_single_assign_static("std", "get_event", get__std__get_event, &var.std__get_event);
  var.std__process_events = create_future();
  define_single_assign_static("std", "process_events", get__std__process_events, &var.std__process_events);
  var.std__wait_to = create_future();
  define_single_assign_static("std", "wait_to", get__std__wait_to, &var.std__wait_to);
  var.std__par = create_future();
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
  initialize_future(var.std__WRITE_TO, unique__std__WRITE_TO);
  initialize_future(var.std__READ_FROM, unique__std__READ_FROM);
  assign_value(&var.std__file_descriptor_of, create_function(type__std__file_descriptor_of, -1));
  initialize_future(var.std__TERMINATED, unique__std__TERMINATED);
  assign_value(&var.std__pid_of, create_function(type__std__pid_of, -1));
  assign_value(&var.std__status_of, create_function(type__std__status_of, -1));
  initialize_future(var.std__TIMEOUT, unique__std__TIMEOUT);
  initialize_future(var.std__SCREEN_SIZE_CHANGE, unique__std__SCREEN_SIZE_CHANGE);
  assign_value(&var.std__width_of, create_function(type__std__width_of, -1));
  assign_value(&var.std__height_of, create_function(type__std__height_of, -1));
  initialize_future(var.std__KEY_PRESS, unique__std__KEY_PRESS);
  assign_value(&var.std__key_code_of, create_function(type__std__key_code_of, -1));
  initialize_future(var.std__MOUSE_CLICK, unique__std__MOUSE_CLICK);
  assign_value(&var.std__target_of, create_function(type__std__target_of, -1));
  initialize_future(var.std__PASTE, unique__std__PASTE);
  initialize_future(var.std__MESSAGE, unique__std__MESSAGE);
  initialize_future(var.types__event, get__types__object());
  initialize_future(var.std__want_to_write_to, func__std__want_to_write_to_1);
  initialize_future(var.std__no_longer_want_to_write_to, func__std__no_longer_want_to_write_to_1);
  initialize_future(var.std__want_to_read_from, func__std__want_to_read_from_1);
  initialize_future(var.std__no_longer_want_to_read_from, func__std__no_longer_want_to_read_from_1);
  initialize_future(var.std__wanting_to_write_to, func__std__wanting_to_write_to_1);
  initialize_future(var.std__wanting_to_read_from, func__std__wanting_to_read_from_1);
  initialize_future(var.std__wait_to_read_from, func__std__wait_to_read_from_1);
  initialize_future(var.std__wait_to_write_to, func__std__wait_to_write_to_1);
  initialize_future(var.std__wait_for_termination, func__std__wait_for_termination_1);
  initialize_future(var.std__discard, func__std__discard_1);
  initialize_future(var.std__create_event, func__std__create_event_1);
  assign_variable(&var._get_low_level_events, &func__get_low_level_events_1);
  assign_variable(&var._get_event_handler, &func__get_event_handler_1);
  initialize_future(var.std__get_event, func__std__get_event_1);
  initialize_future(var.std__process_events, func__std__process_events_1);
  initialize_future(var.std__wait_to, func__std__wait_to_1);
  initialize_future(var.std__par, func__std__par_1);
}

static int already_run_phase_6 = false;

EXPORT void phase_6__basic__event(void) {
  if (already_run_phase_6) return;
  already_run_phase_6 = true;
  register_collector(collect__basic__event);
}
