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
IMPORT NODE *undefined;
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
IMPORT NODE *create_function(FUNC func, int par_count);
IMPORT void set_module(const char *name);
IMPORT void set_used_namespaces(const char **namespaces);
IMPORT NODE *register_unique_item(const char *name);
IMPORT void assign_value(NODE **dest, NODE *val);
IMPORT void define_single_assign_static(
  const char *namespace, const char *name,
  NODE_GETTER getter, NODE **var_p
);
IMPORT void define_multi_assign_static(
  const char *namespace, const char *name,
  NODE_GETTER getter, NODE_SETTER setter
);
IMPORT NODE *from_latin_1_string(const char *str, long len);
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
static NODE_GETTER get__READ_FROM;
static NODE_GETTER get_value_or_future__READ_FROM;
static NODE_GETTER get__SCREEN_SIZE_CHANGE;
static NODE_GETTER get_value_or_future__SCREEN_SIZE_CHANGE;
static NODE_GETTER get__STDIN_FILENO;
static NODE_GETTER get_value_or_future__STDIN_FILENO;
static NODE_GETTER get__TERMINATE;
static NODE_GETTER get_value_or_future__TERMINATE;
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
static NODE_GETTER get__for_each_pair;
static NODE_GETTER get_value_or_future__for_each_pair;
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
  NODE *_get_low_level_events;
  NODE *_get_event_handler;
  NODE *_waiting_tasks;
  NODE *std__WRITE_TO;
  NODE *std__READ_FROM;
  NODE *std__file_descriptor_of;
  NODE *std__TERMINATE;
  NODE *std__pid_of;
  NODE *std__status_of;
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
  "get_low_level_events",
  "get_event_handler",
  "waiting_tasks"
};
static NODE *unique__1_1;
static NODE *get__std__WRITE_TO(void) {
  return var.std__WRITE_TO;
}
static NODE *unique__2_1;
static NODE *get__std__READ_FROM(void) {
  return var.std__READ_FROM;
}
static int poly_idx__std__file_descriptor_of;
static void type__std__file_descriptor_of(void);
static NODE *get__std__file_descriptor_of(void) {
  return var.std__file_descriptor_of;
}
static NODE *unique__4_1;
static NODE *get__std__TERMINATE(void) {
  return var.std__TERMINATE;
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
static NODE *unique__7_1;
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
static NODE *unique__10_1;
static NODE *get__std__KEY_PRESS(void) {
  return var.std__KEY_PRESS;
}
static int poly_idx__std__key_code_of;
static void type__std__key_code_of(void);
static NODE *get__std__key_code_of(void) {
  return var.std__key_code_of;
}
static NODE *unique__12_1;
static NODE *get__std__MOUSE_CLICK(void) {
  return var.std__MOUSE_CLICK;
}
static int poly_idx__std__target_of;
static void type__std__target_of(void);
static NODE *get__std__target_of(void) {
  return var.std__target_of;
}
static NODE *unique__14_1;
static NODE *get__std__PASTE(void) {
  return var.std__PASTE;
}
static NODE *unique__15_1;
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
static NODE *func__20_1;
static void entry__20_1(void);
static FRAME_INFO frame__20_1 = {1, {"fd"}};
static void cont__20_2(void);
static NODE *get__std__want_to_write_to(void) {
  return var.std__want_to_write_to;
}
static NODE *func__21_1;
static void entry__21_1(void);
static FRAME_INFO frame__21_1 = {1, {"fd"}};
static void cont__21_2(void);
static NODE *get__std__no_longer_want_to_write_to(void) {
  return var.std__no_longer_want_to_write_to;
}
static NODE *func__22_1;
static void entry__22_1(void);
static FRAME_INFO frame__22_1 = {1, {"fd"}};
static void cont__22_2(void);
static NODE *get__std__want_to_read_from(void) {
  return var.std__want_to_read_from;
}
static NODE *func__23_1;
static void entry__23_1(void);
static FRAME_INFO frame__23_1 = {1, {"fd"}};
static void cont__23_2(void);
static NODE *get__std__no_longer_want_to_read_from(void) {
  return var.std__no_longer_want_to_read_from;
}
static NODE *func__24_1;
static void entry__24_1(void);
static FRAME_INFO frame__24_1 = {1, {"fd"}};
static void cont__24_2(void);
static NODE *func__24_3;
static void entry__24_3(void);
static FRAME_INFO frame__24_3 = {1, {"fd"}};
static void cont__24_4(void);
static void cont__24_5(void);
static NODE *get__std__wanting_to_write_to(void) {
  return var.std__wanting_to_write_to;
}
static NODE *func__25_1;
static void entry__25_1(void);
static FRAME_INFO frame__25_1 = {1, {"fd"}};
static void cont__25_2(void);
static NODE *func__25_3;
static void entry__25_3(void);
static FRAME_INFO frame__25_3 = {1, {"fd"}};
static void cont__25_4(void);
static void cont__25_5(void);
static NODE *get__std__wanting_to_read_from(void) {
  return var.std__wanting_to_read_from;
}
static NODE *func__27_1;
static void entry__27_1(void);
static FRAME_INFO frame__27_1 = {2, {"fd", "continuation"}};
static void cont__27_2(void);
static void cont__27_3(void);
static void cont__27_4(void);
static NODE *get__std__wait_to_read_from(void) {
  return var.std__wait_to_read_from;
}
static NODE *func__29_1;
static void entry__29_1(void);
static FRAME_INFO frame__29_1 = {2, {"fd", "continuation"}};
static void cont__29_2(void);
static void cont__29_3(void);
static void cont__29_4(void);
static NODE *get__std__wait_to_write_to(void) {
  return var.std__wait_to_write_to;
}
static NODE *func__31_1;
static void entry__31_1(void);
static FRAME_INFO frame__31_1 = {2, {"pid", "continuation"}};
static void cont__31_2(void);
static void cont__31_3(void);
static NODE *get__std__wait_for_termination(void) {
  return var.std__wait_for_termination;
}
static NODE *func__32_1;
static void entry__32_1(void);
static FRAME_INFO frame__32_1 = {2, {"fd", "return"}};
static void cont__32_2(void);
static NODE *func__32_3;
static void entry__32_3(void);
static FRAME_INFO frame__32_3 = {3, {"fd", "new_events", "s"}};
static void cont__32_4(void);
static void cont__32_5(void);
static void cont__32_6(void);
static NODE *func__32_7;
static void entry__32_7(void);
static FRAME_INFO frame__32_7 = {5, {"idx", "event", "fd", "new_events", "s"}};
static void cont__32_8(void);
static void cont__32_9(void);
static NODE *func__32_10;
static void entry__32_10(void);
static FRAME_INFO frame__32_10 = {5, {"event", "fd", "new_events", "s", "idx"}};
static void cont__32_11(void);
static void cont__32_12(void);
static NODE *func__32_13;
static void entry__32_13(void);
static FRAME_INFO frame__32_13 = {3, {"new_events", "s", "idx"}};
static void cont__32_14(void);
static void cont__32_15(void);
static void cont__32_16(void);
static void cont__32_17(void);
static void cont__32_18(void);
static void cont__32_19(void);
static NODE *func__32_20;
static void entry__32_20(void);
static FRAME_INFO frame__32_20 = {2, {"new_events", "s"}};
static void cont__32_21(void);
static void cont__32_22(void);
static void cont__32_23(void);
static void cont__32_24(void);
static void cont__32_25(void);
static void cont__32_26(void);
static NODE *func__32_27;
static void entry__32_27(void);
static FRAME_INFO frame__32_27 = {1, {"return"}};
static void cont__32_28(void);
static NODE *get__std__discard(void) {
  return var.std__discard;
}
static NODE *func__33_1;
static void entry__33_1(void);
static FRAME_INFO frame__33_1 = {1, {"event"}};
static void cont__33_2(void);
static NODE *get__std__create_event(void) {
  return var.std__create_event;
}
static NODE *func__34_1;
static void entry__34_1(void);
static FRAME_INFO frame__34_1 = {9, {"for_readers_and_writers_only", "output_fds_list", "input_fds_list", "exception_fds_list", "child_changed_state", "window_changed_size", "ready_input_fds_list", "ready_output_fds_list", "ready_exception_fds_list"}};
static NODE *func__34_2;
static void entry__34_2(void);
static FRAME_INFO frame__34_2 = {2, {"output_fds_list", "input_fds_list"}};
static NODE *func__34_3;
static void entry__34_3(void);
static FRAME_INFO frame__34_3 = {3, {"output_fd", "continuation", "output_fds_list"}};
static void cont__34_4(void);
static void cont__34_5(void);
static NODE *func__34_6;
static void entry__34_6(void);
static FRAME_INFO frame__34_6 = {3, {"input_fd", "continuation", "input_fds_list"}};
static void cont__34_7(void);
static NODE *func__34_8;
static void entry__34_8(void);
static FRAME_INFO frame__34_8 = {2, {"output_fds_list", "input_fds_list"}};
static NODE *func__34_9;
static void entry__34_9(void);
static FRAME_INFO frame__34_9 = {2, {"output_fd", "output_fds_list"}};
static void cont__34_10(void);
static void cont__34_11(void);
static NODE *func__34_12;
static void entry__34_12(void);
static FRAME_INFO frame__34_12 = {2, {"input_fd", "input_fds_list"}};
static void cont__34_13(void);
static void cont__34_14(void);
static void cont__34_15(void);
static NODE *func__34_16;
static void entry__34_16(void);
static FRAME_INFO frame__34_16 = {8, {"child_changed_state", "window_changed_size", "ready_input_fds_list", "ready_output_fds_list", "ready_exception_fds_list", "ready_input_fds_set", "ready_output_fds_set", "ready_exception_fds_set"}};
static NODE *func__34_17;
static void entry__34_17(void);
static FRAME_INFO frame__34_17 = {0, {}};
static NODE *func__34_18;
static void entry__34_18(void);
static FRAME_INFO frame__34_18 = {1, {"break"}};
static NODE *func__34_19;
static void entry__34_19(void);
static FRAME_INFO frame__34_19 = {3, {"break", "status", "pid"}};
static void cont__34_20(void);
static void cont__34_21(void);
static void cont__34_22(void);
static void cont__34_23(void);
static void cont__34_24(void);
static void cont__34_25(void);
static void cont__34_26(void);
static NODE *func__34_27;
static void entry__34_27(void);
static FRAME_INFO frame__34_27 = {2, {"width", "height"}};
static void cont__34_28(void);
static void cont__34_29(void);
static NODE *func__34_30;
static void entry__34_30(void);
static FRAME_INFO frame__34_30 = {2, {"ready_input_fd", "ready_input_fds_set"}};
static void cont__34_31(void);
static void cont__34_32(void);
static NODE *func__34_33;
static void entry__34_33(void);
static FRAME_INFO frame__34_33 = {2, {"ready_output_fd", "ready_output_fds_set"}};
static void cont__34_34(void);
static void cont__34_35(void);
static NODE *func__34_36;
static void entry__34_36(void);
static FRAME_INFO frame__34_36 = {2, {"ready_exception_fd", "ready_exception_fds_set"}};
static void cont__34_37(void);
static void cont__34_38(void);
static NODE *func__34_39;
static void entry__34_39(void);
static FRAME_INFO frame__34_39 = {1, {"input_fd"}};
static void cont__34_40(void);
static NODE *func__34_41;
static void entry__34_41(void);
static FRAME_INFO frame__34_41 = {1, {"input_fd"}};
static void cont__34_42(void);
static NODE *func__34_43;
static void entry__34_43(void);
static FRAME_INFO frame__34_43 = {1, {"output_fd"}};
static void cont__34_44(void);
static NODE *func__34_45;
static void entry__34_45(void);
static FRAME_INFO frame__34_45 = {1, {"output_fd"}};
static NODE *func__35_1;
static void entry__35_1(void);
static FRAME_INFO frame__35_1 = {2, {"event", "return"}};
static void cont__35_2(void);
static NODE *func__35_3;
static void entry__35_3(void);
static FRAME_INFO frame__35_3 = {4, {"event", "return", "fd", "reader"}};
static void cont__35_4(void);
static void cont__35_5(void);
static void cont__35_6(void);
static NODE *func__35_7;
static void entry__35_7(void);
static FRAME_INFO frame__35_7 = {3, {"fd", "return", "reader"}};
static void cont__35_8(void);
static void cont__35_9(void);
static NODE *func__35_10;
static void entry__35_10(void);
static FRAME_INFO frame__35_10 = {4, {"event", "return", "fd", "writer"}};
static void cont__35_11(void);
static void cont__35_12(void);
static void cont__35_13(void);
static NODE *func__35_14;
static void entry__35_14(void);
static FRAME_INFO frame__35_14 = {3, {"fd", "return", "writer"}};
static void cont__35_15(void);
static void cont__35_16(void);
static NODE *func__35_17;
static void entry__35_17(void);
static FRAME_INFO frame__35_17 = {4, {"event", "return", "pid", "terminator"}};
static void cont__35_18(void);
static void cont__35_19(void);
static void cont__35_20(void);
static NODE *func__35_21;
static void entry__35_21(void);
static FRAME_INFO frame__35_21 = {3, {"pid", "return", "terminator"}};
static void cont__35_22(void);
static void cont__35_23(void);
static NODE *func__36_1;
static void entry__36_1(void);
static FRAME_INFO frame__36_1 = {1, {"return"}};
static NODE *func__36_2;
static void entry__36_2(void);
static FRAME_INFO frame__36_2 = {2, {"myself", "return"}};
static void cont__36_3(void);
static void cont__36_4(void);
static NODE *func__36_5;
static void entry__36_5(void);
static FRAME_INFO frame__36_5 = {4, {"myself", "return", "event", "handler"}};
static void cont__36_6(void);
static void cont__36_7(void);
static void cont__36_8(void);
static NODE *func__36_9;
static void entry__36_9(void);
static FRAME_INFO frame__36_9 = {3, {"myself", "handler", "event"}};
static void cont__36_10(void);
static void cont__36_11(void);
static void cont__36_12(void);
static NODE *func__36_13;
static void entry__36_13(void);
static FRAME_INFO frame__36_13 = {2, {"handler", "event"}};
static NODE *func__36_14;
static void entry__36_14(void);
static FRAME_INFO frame__36_14 = {1, {"handler"}};
static void cont__36_15(void);
static NODE *string__36_16;
static void cont__36_17(void);
static NODE *func__36_18;
static void entry__36_18(void);
static FRAME_INFO frame__36_18 = {0, {}};
static void cont__36_19(void);
static NODE *get__std__get_event(void) {
  return var.std__get_event;
}
static NODE *func__38_1;
static void entry__38_1(void);
static FRAME_INFO frame__38_1 = {1, {"i"}};
static NODE *func__38_2;
static void entry__38_2(void);
static FRAME_INFO frame__38_2 = {0, {}};
static void cont__38_3(void);
static void cont__38_4(void);
static NODE *func__38_5;
static void entry__38_5(void);
static FRAME_INFO frame__38_5 = {0, {}};
static void cont__38_6(void);
static void cont__38_7(void);
static void cont__38_8(void);
static NODE *func__38_9;
static void entry__38_9(void);
static FRAME_INFO frame__38_9 = {0, {}};
static void cont__38_10(void);
static void cont__38_11(void);
static void cont__38_12(void);
static NODE *func__38_13;
static void entry__38_13(void);
static FRAME_INFO frame__38_13 = {2, {"i", "n"}};
static void cont__38_14(void);
static NODE *func__38_15;
static void entry__38_15(void);
static FRAME_INFO frame__38_15 = {2, {"n", "i"}};
static void cont__38_16(void);
static void cont__38_17(void);
static NODE *func__38_18;
static void entry__38_18(void);
static FRAME_INFO frame__38_18 = {3, {"i", "event", "handler"}};
static void cont__38_19(void);
static void cont__38_20(void);
static void cont__38_21(void);
static NODE *func__38_22;
static void entry__38_22(void);
static FRAME_INFO frame__38_22 = {3, {"i", "handler", "event"}};
static void cont__38_23(void);
static void cont__38_24(void);
static void cont__38_25(void);
static NODE *func__38_26;
static void entry__38_26(void);
static FRAME_INFO frame__38_26 = {2, {"handler", "event"}};
static NODE *func__38_27;
static void entry__38_27(void);
static FRAME_INFO frame__38_27 = {1, {"handler"}};
static void cont__38_28(void);
static NODE *string__38_29;
static void cont__38_30(void);
static void cont__38_31(void);
static void cont__38_32(void);
static NODE *get__std__process_events(void) {
  return var.std__process_events;
}
static NODE *func__39_1;
static void entry__39_1(void);
static FRAME_INFO frame__39_1 = {2, {"args", "event"}};
static NODE *func__39_2;
static void entry__39_2(void);
static FRAME_INFO frame__39_2 = {2, {"continuation", "args"}};
static NODE *func__39_3;
static void entry__39_3(void);
static FRAME_INFO frame__39_3 = {3, {"type", "fd_or_pid", "continuation"}};
static NODE *func__39_4;
static void entry__39_4(void);
static FRAME_INFO frame__39_4 = {2, {"fd_or_pid", "continuation"}};
static void cont__39_5(void);
static void cont__39_6(void);
static NODE *func__39_7;
static void entry__39_7(void);
static FRAME_INFO frame__39_7 = {2, {"fd_or_pid", "continuation"}};
static void cont__39_8(void);
static void cont__39_9(void);
static NODE *func__39_10;
static void entry__39_10(void);
static FRAME_INFO frame__39_10 = {2, {"fd_or_pid", "continuation"}};
static void cont__39_11(void);
static void cont__39_12(void);
static void cont__39_13(void);
static void cont__39_14(void);
static NODE *func__39_15;
static void entry__39_15(void);
static FRAME_INFO frame__39_15 = {2, {"type", "fd_or_pid"}};
static NODE *func__39_16;
static void entry__39_16(void);
static FRAME_INFO frame__39_16 = {1, {"fd_or_pid"}};
static void cont__39_17(void);
static void cont__39_18(void);
static NODE *func__39_19;
static void entry__39_19(void);
static FRAME_INFO frame__39_19 = {1, {"fd_or_pid"}};
static void cont__39_20(void);
static void cont__39_21(void);
static NODE *func__39_22;
static void entry__39_22(void);
static FRAME_INFO frame__39_22 = {1, {"fd_or_pid"}};
static void cont__39_23(void);
static void cont__39_24(void);
static NODE *get__std__wait_to(void) {
  return var.std__wait_to;
}
static NODE *func__40_1;
static void entry__40_1(void);
static FRAME_INFO frame__40_1 = {1, {"tasks"}};
static void cont__40_2(void);
static NODE *get__std__par(void) {
  return var.std__par;
}
void run__basic__event(void);

static CONTINUATION_INFO continuation_info[] = {
  {type__std__file_descriptor_of, NULL, 26, 26, 2, 24},
  {type__std__pid_of, NULL, 30, 30, 2, 12},
  {type__std__status_of, NULL, 31, 31, 2, 15},
  {type__std__width_of, NULL, 35, 35, 2, 14},
  {type__std__height_of, NULL, 36, 36, 2, 15},
  {type__std__key_code_of, NULL, 40, 40, 2, 17},
  {type__std__target_of, NULL, 44, 44, 2, 15},
  {run__basic__event, NULL, 309, 309, 1, 26},
  {entry__20_1, NULL, 63, 63, 3, 24},
  {cont__20_2, &frame__20_1, 63, 63, 29, 29},
  {entry__21_1, NULL, 74, 74, 3, 24},
  {cont__21_2, &frame__21_1, 74, 74, 30, 30},
  {entry__22_1, NULL, 85, 85, 3, 23},
  {cont__22_2, &frame__22_1, 85, 85, 28, 28},
  {entry__23_1, NULL, 96, 96, 3, 23},
  {cont__23_2, &frame__23_1, 96, 96, 29, 29},
  {entry__24_3, NULL, 107, 107, 23, 43},
  {cont__24_4, &frame__24_3, 107, 107, 23, 43},
  {entry__24_1, NULL, 107, 107, 6, 18},
  {cont__24_2, &frame__24_1, 107, 107, 6, 43},
  {cont__24_5, &frame__24_1, 107, 107, 3, 43},
  {entry__25_3, NULL, 118, 118, 23, 42},
  {cont__25_4, &frame__25_3, 118, 118, 23, 42},
  {entry__25_1, NULL, 118, 118, 6, 18},
  {cont__25_2, &frame__25_1, 118, 118, 6, 42},
  {cont__25_5, &frame__25_1, 118, 118, 3, 42},
  {entry__27_1, NULL, 131, 131, 3, 22},
  {cont__27_2, &frame__27_1, 132, 132, 3, 14},
  {cont__27_3, &frame__27_1, 133, 133, 3, 45},
  {cont__27_4, &frame__27_1, 133, 133, 45, 45},
  {entry__29_1, NULL, 146, 146, 3, 21},
  {cont__29_2, &frame__29_1, 147, 147, 3, 14},
  {cont__29_3, &frame__29_1, 148, 148, 3, 45},
  {cont__29_4, &frame__29_1, 148, 148, 45, 45},
  {entry__31_1, NULL, 161, 161, 3, 19},
  {cont__31_2, &frame__31_1, 162, 162, 3, 45},
  {cont__31_3, &frame__31_1, 162, 162, 45, 45},
  {entry__32_13, NULL, 181, 181, 45, 49},
  {cont__32_14, &frame__32_13, 181, 181, 30, 50},
  {cont__32_15, &frame__32_13, 181, 181, 11, 50},
  {cont__32_16, &frame__32_13, 182, 182, 11, 18},
  {cont__32_17, &frame__32_13, 182, 182, 18, 18},
  {entry__32_10, NULL, 180, 180, 12, 36},
  {cont__32_11, &frame__32_10, 180, 180, 12, 42},
  {cont__32_12, &frame__32_10, 180, 182, 9, 18},
  {entry__32_7, NULL, 179, 179, 12, 25},
  {cont__32_8, &frame__32_7, 179, 179, 27, 45},
  {cont__32_9, &frame__32_7, 179, 182, 7, 19},
  {entry__32_20, NULL, 184, 184, 42, 42},
  {cont__32_21, &frame__32_20, 184, 184, 26, 43},
  {cont__32_22, &frame__32_20, 184, 184, 7, 43},
  {cont__32_23, &frame__32_20, 185, 185, 24, 24},
  {entry__32_3, NULL, 170, 170, 5, 34},
  {cont__32_4, &frame__32_3, 171, 171, 5, 33},
  {cont__32_5, &frame__32_3, 172, 172, 5, 12},
  {cont__32_6, &frame__32_3, 178, 182, 5, 20},
  {cont__32_18, &frame__32_3, 183, 183, 8, 12},
  {cont__32_19, &frame__32_3, 183, 185, 5, 24},
  {entry__32_27, NULL, 186, 186, 39, 54},
  {entry__32_1, NULL, 169, 169, 6, 18},
  {cont__32_2, &frame__32_1, 169, 185, 3, 25},
  {cont__32_24, &frame__32_1, 186, 186, 6, 31},
  {cont__32_25, &frame__32_1, 186, 186, 6, 36},
  {cont__32_26, &frame__32_1, 186, 186, 3, 54},
  {cont__32_28, &frame__32_1, 186, 186, 54, 54},
  {entry__33_1, NULL, 194, 194, 3, 20},
  {cont__33_2, &frame__33_1, 194, 194, 20, 20},
  {entry__34_3, NULL, 203, 203, 9, 39},
  {cont__34_4, &frame__34_3, 203, 203, 39, 39},
  {entry__34_6, NULL, 204, 204, 50, 78},
  {cont__34_7, &frame__34_6, 204, 204, 78, 78},
  {entry__34_2, NULL, 202, 203, 7, 39},
  {cont__34_5, &frame__34_2, 204, 204, 7, 78},
  {entry__34_9, NULL, 206, 206, 47, 77},
  {cont__34_10, &frame__34_9, 206, 206, 77, 77},
  {entry__34_12, NULL, 207, 207, 45, 73},
  {cont__34_13, &frame__34_12, 207, 207, 73, 73},
  {entry__34_8, NULL, 206, 206, 7, 77},
  {cont__34_11, &frame__34_8, 207, 207, 7, 73},
  {entry__34_19, NULL, 222, 222, 36, 36},
  {cont__34_20, &frame__34_19, 222, 222, 13, 41},
  {cont__34_21, &frame__34_19, 223, 223, 16, 23},
  {cont__34_22, &frame__34_19, 223, 223, 16, 23},
  {cont__34_23, &frame__34_19, 223, 223, 13, 29},
  {cont__34_24, &frame__34_19, 224, 225, 13, 76},
  {entry__34_18, NULL, 221, 225, 11, 77},
  {cont__34_25, &frame__34_18, 225, 225, 77, 77},
  {entry__34_17, NULL, 220, 225, 9, 78},
  {entry__34_27, NULL, 227, 227, 9, 53},
  {cont__34_28, &frame__34_27, 228, 232, 9, 30},
  {entry__34_30, NULL, 237, 237, 9, 44},
  {cont__34_31, &frame__34_30, 237, 237, 49, 49},
  {entry__34_33, NULL, 239, 239, 9, 46},
  {cont__34_34, &frame__34_33, 239, 239, 51, 51},
  {entry__34_36, NULL, 241, 241, 9, 52},
  {cont__34_37, &frame__34_36, 241, 241, 57, 57},
  {entry__34_41, NULL, 244, 245, 11, 73},
  {entry__34_39, NULL, 243, 243, 12, 37},
  {cont__34_40, &frame__34_39, 243, 245, 9, 74},
  {entry__34_45, NULL, 248, 249, 11, 73},
  {entry__34_43, NULL, 247, 247, 12, 39},
  {cont__34_44, &frame__34_43, 247, 249, 9, 74},
  {entry__34_16, NULL, 219, 225, 7, 79},
  {cont__34_26, &frame__34_16, 226, 232, 7, 31},
  {cont__34_29, &frame__34_16, 236, 237, 7, 49},
  {cont__34_32, &frame__34_16, 238, 239, 7, 51},
  {cont__34_35, &frame__34_16, 240, 241, 7, 57},
  {cont__34_38, &frame__34_16, 242, 245, 7, 75},
  {cont__34_42, &frame__34_16, 246, 249, 7, 75},
  {entry__34_1, NULL, 200, 207, 3, 74},
  {cont__34_14, &frame__34_1, 209, 217, 5, 23},
  {cont__34_15, &frame__34_1, 208, 249, 3, 77},
  {entry__35_7, NULL, 262, 262, 9, 38},
  {cont__35_8, &frame__35_7, 263, 263, 9, 20},
  {cont__35_9, &frame__35_7, 264, 264, 9, 21},
  {entry__35_3, NULL, 259, 259, 7, 35},
  {cont__35_4, &frame__35_3, 260, 260, 7, 25},
  {cont__35_5, &frame__35_3, 261, 261, 10, 26},
  {cont__35_6, &frame__35_3, 261, 264, 7, 21},
  {entry__35_14, NULL, 269, 269, 9, 37},
  {cont__35_15, &frame__35_14, 270, 270, 9, 20},
  {cont__35_16, &frame__35_14, 271, 271, 9, 21},
  {entry__35_10, NULL, 266, 266, 7, 35},
  {cont__35_11, &frame__35_10, 267, 267, 7, 25},
  {cont__35_12, &frame__35_10, 268, 268, 10, 26},
  {cont__35_13, &frame__35_10, 268, 271, 7, 21},
  {entry__35_21, NULL, 276, 276, 9, 25},
  {cont__35_22, &frame__35_21, 277, 277, 9, 25},
  {entry__35_17, NULL, 273, 273, 7, 24},
  {cont__35_18, &frame__35_17, 274, 274, 7, 34},
  {cont__35_19, &frame__35_17, 275, 275, 10, 30},
  {cont__35_20, &frame__35_17, 275, 277, 7, 25},
  {entry__35_1, NULL, 257, 257, 5, 18},
  {cont__35_2, &frame__35_1, 256, 277, 3, 27},
  {cont__35_23, &frame__35_1, 278, 278, 3, 14},
  {entry__36_13, NULL, 301, 301, 15, 27},
  {entry__36_14, NULL, 303, 303, 15, 21},
  {entry__36_9, NULL, 298, 298, 11, 35},
  {cont__36_10, &frame__36_9, 300, 300, 13, 39},
  {cont__36_11, &frame__36_9, 300, 300, 13, 44},
  {cont__36_12, &frame__36_9, 299, 303, 11, 22},
  {cont__36_15, &frame__36_9, 304, 304, 11, 38},
  {entry__36_5, NULL, 295, 295, 9, 27},
  {cont__36_6, &frame__36_5, 296, 296, 9, 41},
  {cont__36_7, &frame__36_5, 297, 297, 12, 29},
  {cont__36_8, &frame__36_5, 297, 304, 9, 38},
  {cont__36_17, &frame__36_5, 305, 305, 9, 20},
  {entry__36_18, NULL, 307, 307, 9, 34},
  {entry__36_2, NULL, 294, 294, 7, 23},
  {cont__36_3, &frame__36_2, 294, 294, 7, 27},
  {cont__36_4, &frame__36_2, 293, 307, 5, 35},
  {entry__36_1, NULL, 292, 307, 3, 36},
  {cont__36_19, &frame__36_1, 307, 307, 36, 36},
  {entry__38_5, NULL, 316, 316, 42, 60},
  {cont__38_6, &frame__38_5, 316, 316, 42, 60},
  {entry__38_2, NULL, 316, 316, 12, 35},
  {cont__38_3, &frame__38_2, 316, 316, 12, 39},
  {cont__38_4, &frame__38_2, 316, 316, 9, 60},
  {entry__38_9, NULL, 317, 317, 26, 41},
  {cont__38_10, &frame__38_9, 317, 317, 26, 41},
  {entry__38_26, NULL, 328, 328, 13, 25},
  {entry__38_27, NULL, 330, 330, 13, 19},
  {entry__38_22, NULL, 325, 325, 9, 27},
  {cont__38_23, &frame__38_22, 327, 327, 11, 37},
  {cont__38_24, &frame__38_22, 327, 327, 11, 42},
  {cont__38_25, &frame__38_22, 326, 330, 9, 20},
  {cont__38_28, &frame__38_22, 331, 331, 9, 36},
  {entry__38_18, NULL, 322, 322, 7, 22},
  {cont__38_19, &frame__38_18, 323, 323, 7, 39},
  {cont__38_20, &frame__38_18, 324, 324, 10, 27},
  {cont__38_21, &frame__38_18, 324, 331, 7, 36},
  {cont__38_30, &frame__38_18, 332, 332, 7, 12},
  {cont__38_31, &frame__38_18, 332, 332, 12, 12},
  {entry__38_15, NULL, 321, 321, 14, 19},
  {cont__38_16, &frame__38_15, 321, 321, 14, 19},
  {cont__38_17, &frame__38_15, 321, 332, 11, 12},
  {entry__38_13, NULL, 320, 320, 5, 24},
  {cont__38_14, &frame__38_13, 321, 332, 5, 12},
  {cont__38_32, &frame__38_13, 333, 333, 5, 29},
  {entry__38_1, NULL, 316, 316, 3, 60},
  {cont__38_7, &frame__38_1, 317, 317, 6, 21},
  {cont__38_8, &frame__38_1, 317, 317, 6, 41},
  {cont__38_11, &frame__38_1, 317, 317, 3, 51},
  {cont__38_12, &frame__38_1, 319, 333, 3, 29},
  {entry__39_4, NULL, 349, 349, 11, 37},
  {cont__39_5, &frame__39_4, 350, 350, 11, 29},
  {cont__39_6, &frame__39_4, 350, 350, 42, 42},
  {entry__39_7, NULL, 352, 352, 11, 36},
  {cont__39_8, &frame__39_7, 353, 353, 11, 29},
  {cont__39_9, &frame__39_7, 353, 353, 42, 42},
  {entry__39_10, NULL, 355, 355, 11, 33},
  {cont__39_11, &frame__39_10, 355, 355, 46, 46},
  {entry__39_3, NULL, 346, 355, 7, 47},
  {entry__39_2, NULL, 345, 355, 5, 48},
  {cont__39_12, &frame__39_2, 356, 356, 5, 47},
  {cont__39_13, &frame__39_2, 356, 356, 47, 47},
  {entry__39_16, NULL, 361, 361, 9, 45},
  {cont__39_17, &frame__39_16, 362, 362, 9, 27},
  {cont__39_18, &frame__39_16, 362, 362, 37, 37},
  {entry__39_19, NULL, 364, 364, 9, 44},
  {cont__39_20, &frame__39_19, 365, 365, 9, 27},
  {cont__39_21, &frame__39_19, 365, 365, 37, 37},
  {entry__39_22, NULL, 367, 367, 9, 31},
  {cont__39_23, &frame__39_22, 367, 367, 41, 41},
  {entry__39_15, NULL, 358, 367, 5, 42},
  {entry__39_1, NULL, 344, 356, 3, 47},
  {cont__39_14, &frame__39_1, 357, 367, 3, 43},
  {cont__39_24, &frame__39_1, 368, 368, 3, 10},
  {entry__40_1, NULL, 371, 371, 3, 29},
  {cont__40_2, &frame__40_1, 372, 372, 3, 16}
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
  // 49: $types::event types::object
  initialize_maybe_future(var.types__event, get__types__object());
  // 50: $$std::events empty_list
  var.std__events = get__empty_list();
  // 51: $$wanted_output_fds empty_set
  var._wanted_output_fds = get__empty_set();
  // 52: $$wanted_input_fds empty_set
  var._wanted_input_fds = get__empty_set();
  // 120: $$readers empty_key_order_table
  var._readers = get__empty_key_order_table();
  // 135: $$writers empty_key_order_table
  var._writers = get__empty_key_order_table();
  // 150: $$terminators empty_key_order_table
  var._terminators = get__empty_key_order_table();
  // 309: $$waiting_tasks empty_list
  var._waiting_tasks = get__empty_list();
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__20_1(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // fd: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 63: !wanted_output_fds(fd) true
  frame->slots[1] /* temp__1 */ = get__true();
  // 63: !wanted_output_fds(fd)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd */;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = var._wanted_output_fds;
  func = myself->type;
  frame->cont = cont__20_2;
}
static void cont__20_2(void) {
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
static void entry__21_1(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // fd: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 74: !wanted_output_fds(fd) false
  frame->slots[1] /* temp__1 */ = get__false();
  // 74: !wanted_output_fds(fd)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd */;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = var._wanted_output_fds;
  func = myself->type;
  frame->cont = cont__21_2;
}
static void cont__21_2(void) {
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
static void entry__22_1(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // fd: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 85: !wanted_input_fds(fd) true
  frame->slots[1] /* temp__1 */ = get__true();
  // 85: !wanted_input_fds(fd)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd */;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = var._wanted_input_fds;
  func = myself->type;
  frame->cont = cont__22_2;
}
static void cont__22_2(void) {
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
static void entry__23_1(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // fd: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 96: !wanted_input_fds(fd) false
  frame->slots[1] /* temp__1 */ = get__false();
  // 96: !wanted_input_fds(fd)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd */;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = var._wanted_input_fds;
  func = myself->type;
  frame->cont = cont__23_2;
}
static void cont__23_2(void) {
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
static void entry__24_1(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // fd: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 107: ... fd.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__24_2;
}
static void cont__24_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 107: ... wanted_output_fds(fd)
  frame->slots[3] /* temp__3 */ = create_closure(entry__24_3, 0);
  // 107: ... fd.is_defined && wanted_output_fds(fd)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__24_5;
}
static void entry__24_3(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // fd: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* fd */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 107: ... wanted_output_fds(fd)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd */;
  result_count = 1;
  myself = var._wanted_output_fds;
  func = myself->type;
  frame->cont = cont__24_4;
}
static void cont__24_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 107: ... wanted_output_fds(fd)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__24_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 107: -> fd.is_defined && wanted_output_fds(fd)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__25_1(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // fd: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 118: ... fd.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__25_2;
}
static void cont__25_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 118: ... wanted_input_fds(fd)
  frame->slots[3] /* temp__3 */ = create_closure(entry__25_3, 0);
  // 118: ... fd.is_defined && wanted_input_fds(fd)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__25_5;
}
static void entry__25_3(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // fd: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* fd */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 118: ... wanted_input_fds(fd)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd */;
  result_count = 1;
  myself = var._wanted_input_fds;
  func = myself->type;
  frame->cont = cont__25_4;
}
static void cont__25_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 118: ... wanted_input_fds(fd)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__25_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 118: -> fd.is_defined && wanted_input_fds(fd)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__27_1(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // fd: 0
  // continuation: 1
  frame->slots[1] /* continuation */ = create_continuation();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 131: want_to_read_from fd
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd */;
  result_count = 0;
  myself = get__want_to_read_from();
  func = myself->type;
  frame->cont = cont__27_2;
}
static void cont__27_2(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 132: !readers(fd) continuation
  frame->slots[2] /* temp__1 */ = frame->slots[1] /* continuation */;
  // 132: !readers(fd)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = var._readers;
  func = myself->type;
  frame->cont = cont__27_3;
}
static void cont__27_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._readers = arguments->slots[0];
  // 133: process_events # will never return directly
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = get__process_events();
  func = myself->type;
  frame->cont = cont__27_4;
}
static void cont__27_4(void) {
  myself = frame->slots[1] /* continuation */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__29_1(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // fd: 0
  // continuation: 1
  frame->slots[1] /* continuation */ = create_continuation();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 146: want_to_write_to fd
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd */;
  result_count = 0;
  myself = get__want_to_write_to();
  func = myself->type;
  frame->cont = cont__29_2;
}
static void cont__29_2(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 147: !writers(fd) continuation
  frame->slots[2] /* temp__1 */ = frame->slots[1] /* continuation */;
  // 147: !writers(fd)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = var._writers;
  func = myself->type;
  frame->cont = cont__29_3;
}
static void cont__29_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._writers = arguments->slots[0];
  // 148: process_events # will never return directly
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
static void entry__31_1(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // pid: 0
  // continuation: 1
  frame->slots[1] /* continuation */ = create_continuation();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 161: !terminators(pid) continuation
  frame->slots[2] /* temp__1 */ = frame->slots[1] /* continuation */;
  // 161: !terminators(pid)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* pid */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = var._terminators;
  func = myself->type;
  frame->cont = cont__31_2;
}
static void cont__31_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._terminators = arguments->slots[0];
  // 162: process_events # will never return directly
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = get__process_events();
  func = myself->type;
  frame->cont = cont__31_3;
}
static void cont__31_3(void) {
  myself = frame->slots[1] /* continuation */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__32_1(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // fd: 0
  // return: 1
  frame->slots[1] /* return */ = create_continuation();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 169: ... fd.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__32_2;
}
static void cont__32_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 169: ... :
  // 170:   no_longer_want_to_read_from fd
  // 171:   no_longer_want_to_write_to fd
  // 172:   close fd
  // 173:   
  // 174:   # remove all associated events
  // 175:   
  // 176:   $$new_events empty_list
  // 177:   $$s 1
  // 178:   for_each events: (idx event)
  // ...
  frame->slots[3] /* temp__2 */ = create_closure(entry__32_3, 0);
  // 169: if fd.is_defined:
  // 170:   no_longer_want_to_read_from fd
  // 171:   no_longer_want_to_write_to fd
  // 172:   close fd
  // 173:   
  // 174:   # remove all associated events
  // 175:   
  // 176:   $$new_events empty_list
  // 177:   $$s 1
  // 178:   for_each events: (idx event)
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__32_24;
}
static void entry__32_20(void) {
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
  // 184: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__32_21;
}
static void cont__32_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 184: ... range(events s -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__events();
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* s */;
  arguments->slots[2] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__32_22;
}
static void cont__32_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 184: append &new_events range(events s -1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* new_events */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__32_23;
}
static void cont__32_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* new_events */ = arguments->slots[0];
  // 185: !events new_events
  set__events(((CELL *)frame->slots[0])->contents /* new_events */);
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__32_3(void) {
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
  // 170: no_longer_want_to_read_from fd
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd */;
  result_count = 0;
  myself = get__no_longer_want_to_read_from();
  func = myself->type;
  frame->cont = cont__32_4;
}
static void cont__32_4(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 171: no_longer_want_to_write_to fd
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd */;
  result_count = 0;
  myself = get__no_longer_want_to_write_to();
  func = myself->type;
  frame->cont = cont__32_5;
}
static void cont__32_5(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 172: close fd
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd */;
  result_count = 0;
  myself = get__close();
  func = myself->type;
  frame->cont = cont__32_6;
}
static void cont__32_6(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 176: $$new_events empty_list
  ((CELL *)frame->slots[1])->contents /* new_events */ = get__empty_list();
  // 177: $$s 1
  ((CELL *)frame->slots[2])->contents /* s */ = number__1;
  // 178: ... : (idx event)
  // 179:   case type_of(event) WRITE_TO, READ_FROM:
  // 180:     if file_descriptor_of(event) == fd:
  // 181:       append &new_events range(events s idx-1)
  // 182:       !s idx+1
  frame->slots[3] /* temp__1 */ = create_closure(entry__32_7, 2);
  // 178: for_each events: (idx event)
  // 179:   case type_of(event) WRITE_TO, READ_FROM:
  // 180:     if file_descriptor_of(event) == fd:
  // 181:       append &new_events range(events s idx-1)
  // 182:       !s idx+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__events();
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__32_18;
}
static void entry__32_13(void) {
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
  // 181: ... idx-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* idx */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__32_14;
}
static void cont__32_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 181: ... range(events s idx-1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__events();
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* s */;
  arguments->slots[2] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__32_15;
}
static void cont__32_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 181: append &new_events range(events s idx-1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* new_events */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__32_16;
}
static void cont__32_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* new_events */ = arguments->slots[0];
  // 182: !s idx+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* idx */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__32_17;
}
static void cont__32_17(void) {
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
static void entry__32_10(void) {
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
  // 180: ... file_descriptor_of(event)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* event */;
  result_count = 1;
  myself = get__file_descriptor_of();
  func = myself->type;
  frame->cont = cont__32_11;
}
static void cont__32_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 180: ... file_descriptor_of(event) == fd
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[1] /* fd */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__32_12;
}
static void cont__32_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 180: ... :
  // 181:   append &new_events range(events s idx-1)
  // 182:   !s idx+1
  frame->slots[7] /* temp__3 */ = create_closure(entry__32_13, 0);
  // 180: if file_descriptor_of(event) == fd:
  // 181:   append &new_events range(events s idx-1)
  // 182:   !s idx+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__32_7(void) {
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
  // 179: ... type_of(event)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* event */;
  result_count = 1;
  myself = get__type_of();
  func = myself->type;
  frame->cont = cont__32_8;
}
static void cont__32_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 179: ... WRITE_TO, READ_FROM
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__WRITE_TO();
  arguments->slots[1] = get__READ_FROM();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__32_9;
}
static void cont__32_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 179: ... :
  // 180:   if file_descriptor_of(event) == fd:
  // 181:     append &new_events range(events s idx-1)
  // 182:     !s idx+1
  frame->slots[7] /* temp__3 */ = create_closure(entry__32_10, 0);
  // 179: case type_of(event) WRITE_TO, READ_FROM:
  // 180:   if file_descriptor_of(event) == fd:
  // 181:     append &new_events range(events s idx-1)
  // 182:     !s idx+1
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
static void cont__32_18(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 183: ... s > 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__1;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* s */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__32_19;
}
static void cont__32_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 183: ... :
  // 184:   append &new_events range(events s -1)
  // 185:   !events new_events
  frame->slots[4] /* temp__2 */ = create_closure(entry__32_20, 0);
  // 183: if s > 1:
  // 184:   append &new_events range(events s -1)
  // 185:   !events new_events
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__32_24(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 186: ... parameter_count_of(return)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* return */;
  result_count = 1;
  myself = get__parameter_count_of();
  func = myself->type;
  frame->cont = cont__32_25;
}
static void cont__32_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 186: ... parameter_count_of(return) == 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__32_26;
}
static void cont__32_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 186: ... : return undefined
  frame->slots[4] /* temp__3 */ = create_closure(entry__32_27, 0);
  // 186: if parameter_count_of(return) == 1: return undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__32_28;
}
static void entry__32_27(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 186: ... return undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__32_28(void) {
  myself = frame->slots[1] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__33_1(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // event: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 194: push &events event
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__events();
  arguments->slots[1] = frame->slots[0] /* event */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__33_2;
}
static void cont__33_2(void) {
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
static void entry__34_45(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // output_fd: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* output_fd */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 249: types::event(.type_of WRITE_TO .file_descriptor_of output_fd)
  {
    NODE *temp = clone_object_and_attributes(var.types__event);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__type_of, get__WRITE_TO());
    set_attribute_value(temp->attributes, poly_idx__file_descriptor_of, frame->slots[0] /* output_fd */);
    frame->slots[1] /* temp__1 */ = temp;

  }
  // 248: create_event
  // 249:   types::event(.type_of WRITE_TO .file_descriptor_of output_fd)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__create_event();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__34_43(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // output_fd: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 247: ... wanted_output_fds(output_fd)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* output_fd */;
  result_count = 1;
  myself = var._wanted_output_fds;
  func = myself->type;
  frame->cont = cont__34_44;
}
static void cont__34_44(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 247: ... :
  // 248:   create_event
  // 249:     types::event(.type_of WRITE_TO .file_descriptor_of output_fd)
  frame->slots[2] /* temp__2 */ = create_closure(entry__34_45, 0);
  // 247: if wanted_output_fds(output_fd):
  // 248:   create_event
  // 249:     types::event(.type_of WRITE_TO .file_descriptor_of output_fd)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__34_16(void) {
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
  // 219: if child_changed_state:
  // 220:   do: (-> break)
  // 221:     forever:
  // 222:       wait_pid $status $pid -1 true
  // 223:       if pid <= 0 break
  // 224:       create_event
  // 225:         types::event(.type_of TERMINATE .pid_of pid .status_of status)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* child_changed_state */;
  arguments->slots[1] = func__34_17;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__34_26;
}
static void entry__34_18(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // break: 0
  frame->slots[0] /* break */ = create_continuation();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 221: ... :
  // 222:   wait_pid $status $pid -1 true
  // 223:   if pid <= 0 break
  // 224:   create_event
  // 225:     types::event(.type_of TERMINATE .pid_of pid .status_of status)
  frame->slots[1] /* temp__1 */ = create_closure(entry__34_19, 0);
  // 221: forever:
  // 222:   wait_pid $status $pid -1 true
  // 223:   if pid <= 0 break
  // 224:   create_event
  // 225:     types::event(.type_of TERMINATE .pid_of pid .status_of status)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__forever();
  func = myself->type;
  frame->cont = cont__34_25;
}
static void entry__34_19(void) {
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
  // 222: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__34_20;
}
static void cont__34_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 222: wait_pid $status $pid -1 true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = get__true();
  result_count = 2;
  myself = get__wait_pid();
  func = myself->type;
  frame->cont = cont__34_21;
}
static void cont__34_21(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  frame->slots[5] /* temp__3 */ = arguments->slots[1];
  // 222: ... status
  initialize_future(frame->slots[1] /* status */, frame->slots[4] /* temp__2 */);
  // 222: ... pid
  initialize_future(frame->slots[2] /* pid */, frame->slots[5] /* temp__3 */);
  // 223: ... pid <= 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = frame->slots[2] /* pid */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__34_22;
}
static void cont__34_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 223: ... pid <= 0
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__34_23;
}
static void cont__34_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 223: if pid <= 0 break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[0] /* break */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__34_24;
}
static void cont__34_24(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 225: types::event(.type_of TERMINATE .pid_of pid .status_of status)
  {
    NODE *temp = clone_object_and_attributes(var.types__event);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__type_of, get__TERMINATE());
    set_attribute_value(temp->attributes, poly_idx__pid_of, frame->slots[2] /* pid */);
    set_attribute_value(temp->attributes, poly_idx__status_of, frame->slots[1] /* status */);
    frame->slots[3] /* temp__1 */ = temp;

  }
  // 224: create_event
  // 225:   types::event(.type_of TERMINATE .pid_of pid .status_of status)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__create_event();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__34_25(void) {
  myself = frame->slots[0] /* break */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__34_17(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 220: do: (-> break)
  // 221:   forever:
  // 222:     wait_pid $status $pid -1 true
  // 223:     if pid <= 0 break
  // 224:     create_event
  // 225:       types::event(.type_of TERMINATE .pid_of pid .status_of status)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__34_18;
  result_count = frame->caller_result_count;
  myself = get__do();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__34_26(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 226: if window_changed_size:
  // 227:   get_terminal_size STDIN_FILENO $width $height
  // 228:   create_event
  // 229:     types::event
  // 230:       .type_of SCREEN_SIZE_CHANGE
  // 231:       .width_of width
  // 232:       .height_of height
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* window_changed_size */;
  arguments->slots[1] = func__34_27;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__34_29;
}
static void entry__34_27(void) {
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
  // 227: get_terminal_size STDIN_FILENO $width $height
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__STDIN_FILENO();
  result_count = 2;
  myself = get__get_terminal_size();
  func = myself->type;
  frame->cont = cont__34_28;
}
static void cont__34_28(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  frame->slots[3] /* temp__2 */ = arguments->slots[1];
  // 227: ... width
  initialize_future(frame->slots[0] /* width */, frame->slots[2] /* temp__1 */);
  // 227: ... height
  initialize_future(frame->slots[1] /* height */, frame->slots[3] /* temp__2 */);
  // 229: types::event
  // 230:   .type_of SCREEN_SIZE_CHANGE
  // 231:   .width_of width
  // 232:   .height_of height
  {
    NODE *temp = clone_object_and_attributes(var.types__event);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__type_of, get__SCREEN_SIZE_CHANGE());
    set_attribute_value(temp->attributes, poly_idx__width_of, frame->slots[0] /* width */);
    set_attribute_value(temp->attributes, poly_idx__height_of, frame->slots[1] /* height */);
    frame->slots[2] /* temp__1 */ = temp;

  }
  // 228: create_event
  // 229:   types::event
  // 230:     .type_of SCREEN_SIZE_CHANGE
  // 231:     .width_of width
  // 232:     .height_of height
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__create_event();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__34_29(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 233: $$ready_input_fds_set empty_set
  ((CELL *)frame->slots[5])->contents /* ready_input_fds_set */ = get__empty_set();
  // 234: $$ready_output_fds_set empty_set
  ((CELL *)frame->slots[6])->contents /* ready_output_fds_set */ = get__empty_set();
  // 235: $$ready_exception_fds_set empty_set
  ((CELL *)frame->slots[7])->contents /* ready_exception_fds_set */ = get__empty_set();
  // 236: ... : (ready_input_fd)
  // 237:   !ready_input_fds_set(ready_input_fd) true
  frame->slots[8] /* temp__1 */ = create_closure(entry__34_30, 1);
  // 236: for_each ready_input_fds_list: (ready_input_fd)
  // 237:   !ready_input_fds_set(ready_input_fd) true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* ready_input_fds_list */;
  arguments->slots[1] = frame->slots[8] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__34_32;
}
static void entry__34_30(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // ready_input_fd: 0
  // ready_input_fds_set: 1
  frame->slots[1] = myself->closure.frame->slots[5]; /* ready_input_fds_set */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 237: !ready_input_fds_set(ready_input_fd) true
  frame->slots[2] /* temp__1 */ = get__true();
  // 237: !ready_input_fds_set(ready_input_fd)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* ready_input_fd */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[1])->contents /* ready_input_fds_set */;
  func = myself->type;
  frame->cont = cont__34_31;
}
static void cont__34_31(void) {
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
static void cont__34_32(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 238: ... : (ready_output_fd)
  // 239:   !ready_output_fds_set(ready_output_fd) true
  frame->slots[8] /* temp__1 */ = create_closure(entry__34_33, 1);
  // 238: for_each ready_output_fds_list: (ready_output_fd)
  // 239:   !ready_output_fds_set(ready_output_fd) true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* ready_output_fds_list */;
  arguments->slots[1] = frame->slots[8] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__34_35;
}
static void entry__34_33(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // ready_output_fd: 0
  // ready_output_fds_set: 1
  frame->slots[1] = myself->closure.frame->slots[6]; /* ready_output_fds_set */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 239: !ready_output_fds_set(ready_output_fd) true
  frame->slots[2] /* temp__1 */ = get__true();
  // 239: !ready_output_fds_set(ready_output_fd)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* ready_output_fd */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[1])->contents /* ready_output_fds_set */;
  func = myself->type;
  frame->cont = cont__34_34;
}
static void cont__34_34(void) {
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
static void cont__34_35(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 240: ... : (ready_exception_fd)
  // 241:   !ready_exception_fds_set(ready_exception_fd) true
  frame->slots[8] /* temp__1 */ = create_closure(entry__34_36, 1);
  // 240: for_each ready_exception_fds_list: (ready_exception_fd)
  // 241:   !ready_exception_fds_set(ready_exception_fd) true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* ready_exception_fds_list */;
  arguments->slots[1] = frame->slots[8] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__34_38;
}
static void entry__34_36(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // ready_exception_fd: 0
  // ready_exception_fds_set: 1
  frame->slots[1] = myself->closure.frame->slots[7]; /* ready_exception_fds_set */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 241: !ready_exception_fds_set(ready_exception_fd) true
  frame->slots[2] /* temp__1 */ = get__true();
  // 241: !ready_exception_fds_set(ready_exception_fd)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* ready_exception_fd */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[1])->contents /* ready_exception_fds_set */;
  func = myself->type;
  frame->cont = cont__34_37;
}
static void cont__34_37(void) {
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
static void cont__34_38(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 242: for_each ready_input_fds_set: (input_fd)
  // 243:   if wanted_input_fds(input_fd):
  // 244:     create_event
  // 245:       types::event(.type_of READ_FROM .file_descriptor_of input_fd)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[5])->contents /* ready_input_fds_set */;
  arguments->slots[1] = func__34_39;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__34_42;
}
static void entry__34_41(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // input_fd: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* input_fd */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 245: types::event(.type_of READ_FROM .file_descriptor_of input_fd)
  {
    NODE *temp = clone_object_and_attributes(var.types__event);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__type_of, get__READ_FROM());
    set_attribute_value(temp->attributes, poly_idx__file_descriptor_of, frame->slots[0] /* input_fd */);
    frame->slots[1] /* temp__1 */ = temp;

  }
  // 244: create_event
  // 245:   types::event(.type_of READ_FROM .file_descriptor_of input_fd)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__create_event();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__34_39(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // input_fd: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 243: ... wanted_input_fds(input_fd)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* input_fd */;
  result_count = 1;
  myself = var._wanted_input_fds;
  func = myself->type;
  frame->cont = cont__34_40;
}
static void cont__34_40(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 243: ... :
  // 244:   create_event
  // 245:     types::event(.type_of READ_FROM .file_descriptor_of input_fd)
  frame->slots[2] /* temp__2 */ = create_closure(entry__34_41, 0);
  // 243: if wanted_input_fds(input_fd):
  // 244:   create_event
  // 245:     types::event(.type_of READ_FROM .file_descriptor_of input_fd)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__34_42(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 246: for_each ready_output_fds_set: (output_fd)
  // 247:   if wanted_output_fds(output_fd):
  // 248:     create_event
  // 249:       types::event(.type_of WRITE_TO .file_descriptor_of output_fd)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[6])->contents /* ready_output_fds_set */;
  arguments->slots[1] = func__34_43;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__34_1(void) {
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
  // 197: $$output_fds_list empty_list
  ((CELL *)frame->slots[1])->contents /* output_fds_list */ = get__empty_list();
  // 198: $$input_fds_list empty_list
  ((CELL *)frame->slots[2])->contents /* input_fds_list */ = get__empty_list();
  // 199: $exception_fds_list empty_list
  initialize_maybe_future(frame->slots[3] /* exception_fds_list */, get__empty_list());
  // 201: ... :
  // 202:   for_each writers: (output_fd _continuation)
  // 203:     push &output_fds_list output_fd
  // 204:   for_each readers: (input_fd _continuation) push &input_fds_list input_fd
  frame->slots[9] /* temp__1 */ = create_closure(entry__34_2, 0);
  // 205: :
  // 206:   for_each wanted_output_fds: (output_fd) push &output_fds_list output_fd
  // 207:   for_each wanted_input_fds: (input_fd) push &input_fds_list input_fd
  frame->slots[10] /* temp__2 */ = create_closure(entry__34_8, 0);
  // 200: if
  // 201:   for_readers_and_writers_only:
  // 202:     for_each writers: (output_fd _continuation)
  // 203:       push &output_fds_list output_fd
  // 204:     for_each readers: (input_fd _continuation) push &input_fds_list input_fd
  // 205:   :
  // 206:     for_each wanted_output_fds: (output_fd) push &output_fds_list output_fd
  // 207:     for_each wanted_input_fds: (input_fd) push &input_fds_list input_fd
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* for_readers_and_writers_only */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  arguments->slots[2] = frame->slots[10] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__34_14;
}
static void entry__34_12(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // input_fd: 0
  // input_fds_list: 1
  frame->slots[1] = myself->closure.frame->slots[1]; /* input_fds_list */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 207: ... push &input_fds_list input_fd
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* input_fds_list */;
  arguments->slots[1] = frame->slots[0] /* input_fd */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__34_13;
}
static void cont__34_13(void) {
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
static void entry__34_6(void) {
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
  // 204: ... push &input_fds_list input_fd
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* input_fds_list */;
  arguments->slots[1] = frame->slots[0] /* input_fd */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__34_7;
}
static void cont__34_7(void) {
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
static void entry__34_2(void) {
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
  // 202: ... : (output_fd _continuation)
  // 203:   push &output_fds_list output_fd
  frame->slots[2] /* temp__1 */ = create_closure(entry__34_3, 2);
  // 202: for_each writers: (output_fd _continuation)
  // 203:   push &output_fds_list output_fd
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._writers;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__34_5;
}
static void entry__34_3(void) {
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
  // 203: push &output_fds_list output_fd
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* output_fds_list */;
  arguments->slots[1] = frame->slots[0] /* output_fd */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__34_4;
}
static void cont__34_4(void) {
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
static void cont__34_5(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 204: ... : (input_fd _continuation) push &input_fds_list input_fd
  frame->slots[2] /* temp__1 */ = create_closure(entry__34_6, 2);
  // 204: for_each readers: (input_fd _continuation) push &input_fds_list input_fd
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._readers;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__34_8(void) {
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
  // 206: ... : (output_fd) push &output_fds_list output_fd
  frame->slots[2] /* temp__1 */ = create_closure(entry__34_9, 1);
  // 206: for_each wanted_output_fds: (output_fd) push &output_fds_list output_fd
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._wanted_output_fds;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__34_11;
}
static void entry__34_9(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // output_fd: 0
  // output_fds_list: 1
  frame->slots[1] = myself->closure.frame->slots[0]; /* output_fds_list */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 206: ... push &output_fds_list output_fd
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* output_fds_list */;
  arguments->slots[1] = frame->slots[0] /* output_fd */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__34_10;
}
static void cont__34_10(void) {
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
static void cont__34_11(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 207: ... : (input_fd) push &input_fds_list input_fd
  frame->slots[2] /* temp__1 */ = create_closure(entry__34_12, 1);
  // 207: for_each wanted_input_fds: (input_fd) push &input_fds_list input_fd
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._wanted_input_fds;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__34_14(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 209: wait_for_io
  // 210:   $child_changed_state
  // 211:   $window_changed_size
  // 212:   $ready_input_fds_list
  // 213:   input_fds_list
  // 214:   $ready_output_fds_list
  // 215:   output_fds_list
  // 216:   $ready_exception_fds_list
  // 217:   exception_fds_list
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* input_fds_list */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* output_fds_list */;
  arguments->slots[2] = frame->slots[3] /* exception_fds_list */;
  result_count = 6;
  myself = get__wait_for_io();
  func = myself->type;
  frame->cont = cont__34_15;
}
static void cont__34_15(void) {
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
  // 210: ... child_changed_state
  initialize_future(frame->slots[4] /* child_changed_state */, frame->slots[10] /* temp__2 */);
  // 211: ... window_changed_size
  initialize_future(frame->slots[5] /* window_changed_size */, frame->slots[11] /* temp__3 */);
  // 212: ... ready_input_fds_list
  initialize_future(frame->slots[6] /* ready_input_fds_list */, frame->slots[12] /* temp__4 */);
  // 214: ... ready_output_fds_list
  initialize_future(frame->slots[7] /* ready_output_fds_list */, frame->slots[13] /* temp__5 */);
  // 216: ... ready_exception_fds_list
  initialize_future(frame->slots[8] /* ready_exception_fds_list */, frame->slots[14] /* temp__6 */);
  // 218: :
  // 219:   if child_changed_state:
  // 220:     do: (-> break)
  // 221:       forever:
  // 222:         wait_pid $status $pid -1 true
  // 223:         if pid <= 0 break
  // 224:         create_event
  // 225:           types::event(.type_of TERMINATE .pid_of pid .status_of status)
  // 226:   if window_changed_size:
  // 227:     get_terminal_size STDIN_FILENO $width $height
  // ...
  frame->slots[15] /* temp__7 */ = create_closure(entry__34_16, 0);
  // 208: if
  // 209:   wait_for_io
  // 210:     $child_changed_state
  // 211:     $window_changed_size
  // 212:     $ready_input_fds_list
  // 213:     input_fds_list
  // 214:     $ready_output_fds_list
  // 215:     output_fds_list
  // 216:     $ready_exception_fds_list
  // 217:     exception_fds_list
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  arguments->slots[1] = frame->slots[15] /* temp__7 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__35_1(void) {
  allocate_initialized_frame_gc(2, 6);
  // slot allocations:
  // event: 0
  // return: 1
  frame->slots[1] /* return */ = create_continuation();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 257: type_of(event)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* event */;
  result_count = 1;
  myself = get__type_of();
  func = myself->type;
  frame->cont = cont__35_2;
}
static void cont__35_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 258: ... :
  // 259:   $fd file_descriptor_of(event)
  // 260:   $reader readers(fd)
  // 261:   if reader.is_defined:
  // 262:     no_longer_want_to_read_from fd
  // 263:     !readers(fd) undefined
  // 264:     return reader
  frame->slots[3] /* temp__2 */ = create_closure(entry__35_3, 0);
  // 265: ... :
  // 266:   $fd file_descriptor_of(event)
  // 267:   $writer writers(fd)
  // 268:   if writer.is_defined:
  // 269:     no_longer_want_to_write_to fd
  // 270:     !writers(fd) undefined
  // 271:     return writer
  frame->slots[4] /* temp__3 */ = create_closure(entry__35_10, 0);
  // 272: ... :
  // 273:   $pid pid_of(event)
  // 274:   $terminator terminators(pid)
  // 275:   if terminator.is_defined:
  // 276:     !terminators(pid) undefined
  // 277:     return terminator
  frame->slots[5] /* temp__4 */ = create_closure(entry__35_17, 0);
  // 256: case
  // 257:   type_of(event)
  // 258:   READ_FROM:
  // 259:     $fd file_descriptor_of(event)
  // 260:     $reader readers(fd)
  // 261:     if reader.is_defined:
  // 262:       no_longer_want_to_read_from fd
  // 263:       !readers(fd) undefined
  // 264:       return reader
  // 265:   WRITE_TO:
  // ...
  argument_count = 7;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = get__READ_FROM();
  arguments->slots[2] = frame->slots[3] /* temp__2 */;
  arguments->slots[3] = get__WRITE_TO();
  arguments->slots[4] = frame->slots[4] /* temp__3 */;
  arguments->slots[5] = get__TERMINATE();
  arguments->slots[6] = frame->slots[5] /* temp__4 */;
  result_count = 0;
  myself = get__case();
  func = myself->type;
  frame->cont = cont__35_23;
}
static void entry__35_21(void) {
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
  // 276: !terminators(pid) undefined
  frame->slots[3] /* temp__1 */ = get__undefined();
  // 276: !terminators(pid)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* pid */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = var._terminators;
  func = myself->type;
  frame->cont = cont__35_22;
}
static void cont__35_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._terminators = arguments->slots[0];
  // 277: return terminator
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* terminator */;
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__35_14(void) {
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
  // 269: no_longer_want_to_write_to fd
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd */;
  result_count = 0;
  myself = get__no_longer_want_to_write_to();
  func = myself->type;
  frame->cont = cont__35_15;
}
static void cont__35_15(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 270: !writers(fd) undefined
  frame->slots[3] /* temp__1 */ = get__undefined();
  // 270: !writers(fd)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = var._writers;
  func = myself->type;
  frame->cont = cont__35_16;
}
static void cont__35_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._writers = arguments->slots[0];
  // 271: return writer
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* writer */;
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__35_7(void) {
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
  // 262: no_longer_want_to_read_from fd
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd */;
  result_count = 0;
  myself = get__no_longer_want_to_read_from();
  func = myself->type;
  frame->cont = cont__35_8;
}
static void cont__35_8(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 263: !readers(fd) undefined
  frame->slots[3] /* temp__1 */ = get__undefined();
  // 263: !readers(fd)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = var._readers;
  func = myself->type;
  frame->cont = cont__35_9;
}
static void cont__35_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._readers = arguments->slots[0];
  // 264: return reader
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* reader */;
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__35_3(void) {
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
  // 259: $fd file_descriptor_of(event)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* event */;
  result_count = 1;
  myself = get__file_descriptor_of();
  func = myself->type;
  frame->cont = cont__35_4;
}
static void cont__35_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* fd */, arguments->slots[0]);
  // 260: $reader readers(fd)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* fd */;
  result_count = 1;
  myself = var._readers;
  func = myself->type;
  frame->cont = cont__35_5;
}
static void cont__35_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* reader */, arguments->slots[0]);
  // 261: ... reader.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* reader */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__35_6;
}
static void cont__35_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 261: ... :
  // 262:   no_longer_want_to_read_from fd
  // 263:   !readers(fd) undefined
  // 264:   return reader
  frame->slots[5] /* temp__2 */ = create_closure(entry__35_7, 0);
  // 261: if reader.is_defined:
  // 262:   no_longer_want_to_read_from fd
  // 263:   !readers(fd) undefined
  // 264:   return reader
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__35_10(void) {
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
  // 266: $fd file_descriptor_of(event)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* event */;
  result_count = 1;
  myself = get__file_descriptor_of();
  func = myself->type;
  frame->cont = cont__35_11;
}
static void cont__35_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* fd */, arguments->slots[0]);
  // 267: $writer writers(fd)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* fd */;
  result_count = 1;
  myself = var._writers;
  func = myself->type;
  frame->cont = cont__35_12;
}
static void cont__35_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* writer */, arguments->slots[0]);
  // 268: ... writer.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* writer */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__35_13;
}
static void cont__35_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 268: ... :
  // 269:   no_longer_want_to_write_to fd
  // 270:   !writers(fd) undefined
  // 271:   return writer
  frame->slots[5] /* temp__2 */ = create_closure(entry__35_14, 0);
  // 268: if writer.is_defined:
  // 269:   no_longer_want_to_write_to fd
  // 270:   !writers(fd) undefined
  // 271:   return writer
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__35_17(void) {
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
  // 273: $pid pid_of(event)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* event */;
  result_count = 1;
  myself = get__pid_of();
  func = myself->type;
  frame->cont = cont__35_18;
}
static void cont__35_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* pid */, arguments->slots[0]);
  // 274: $terminator terminators(pid)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* pid */;
  result_count = 1;
  myself = var._terminators;
  func = myself->type;
  frame->cont = cont__35_19;
}
static void cont__35_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* terminator */, arguments->slots[0]);
  // 275: ... terminator.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* terminator */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__35_20;
}
static void cont__35_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 275: ... :
  // 276:   !terminators(pid) undefined
  // 277:   return terminator
  frame->slots[5] /* temp__2 */ = create_closure(entry__35_21, 0);
  // 275: if terminator.is_defined:
  // 276:   !terminators(pid) undefined
  // 277:   return terminator
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__35_23(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 278: -> undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  myself = frame->slots[1] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__36_1(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // return: 0
  frame->slots[0] /* return */ = create_continuation();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 292: ... : (myself^)
  // 293:   if
  // 294:     length_of(events) > 0:
  // 295:       $event get(&events)
  // 296:       $handler get_event_handler(event)
  // 297:       if handler.is_defined:
  // 298:         put &waiting_tasks myself
  // 299:         if
  // 300:           parameter_count_of(handler) == 1:
  // 301:             handler event
  // ...
  frame->slots[1] /* temp__1 */ = create_closure(entry__36_2, 0);
  // 292: forever: (myself^)
  // 293:   if
  // 294:     length_of(events) > 0:
  // 295:       $event get(&events)
  // 296:       $handler get_event_handler(event)
  // 297:       if handler.is_defined:
  // 298:         put &waiting_tasks myself
  // 299:         if
  // 300:           parameter_count_of(handler) == 1:
  // 301:             handler event
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__forever();
  func = myself->type;
  frame->cont = cont__36_19;
}
static void entry__36_5(void) {
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
  // 295: $event get(&events)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__events();
  result_count = 2;
  myself = get__get();
  func = myself->type;
  frame->cont = cont__36_6;
}
static void cont__36_6(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  set__events(arguments->slots[0]);
  frame->slots[4] /* temp__1 */ = arguments->slots[1];
  // 295: ... event
  initialize_future(frame->slots[2] /* event */, frame->slots[4] /* temp__1 */);
  // 296: $handler get_event_handler(event)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* event */;
  result_count = 1;
  myself = var._get_event_handler;
  func = myself->type;
  frame->cont = cont__36_7;
}
static void cont__36_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* handler */, arguments->slots[0]);
  // 297: ... handler.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* handler */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__36_8;
}
static void cont__36_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 297: ... :
  // 298:   put &waiting_tasks myself
  // 299:   if
  // 300:     parameter_count_of(handler) == 1:
  // 301:       handler event
  // 302:     :
  // 303:       handler
  // 304:   raise "invalid continuation"
  frame->slots[5] /* temp__2 */ = create_closure(entry__36_9, 0);
  // 297: if handler.is_defined:
  // 298:   put &waiting_tasks myself
  // 299:   if
  // 300:     parameter_count_of(handler) == 1:
  // 301:       handler event
  // 302:     :
  // 303:       handler
  // 304:   raise "invalid continuation"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__36_17;
}
static void entry__36_9(void) {
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
  // 298: put &waiting_tasks myself
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._waiting_tasks;
  arguments->slots[1] = frame->slots[0] /* myself */;
  result_count = 1;
  myself = get__put();
  func = myself->type;
  frame->cont = cont__36_10;
}
static void cont__36_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._waiting_tasks = arguments->slots[0];
  // 300: parameter_count_of(handler)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* handler */;
  result_count = 1;
  myself = get__parameter_count_of();
  func = myself->type;
  frame->cont = cont__36_11;
}
static void cont__36_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 300: parameter_count_of(handler) == 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = number__1;
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
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 300: ... :
  // 301:   handler event
  frame->slots[5] /* temp__3 */ = create_closure(entry__36_13, 0);
  // 302: :
  // 303:   handler
  frame->slots[6] /* temp__4 */ = create_closure(entry__36_14, 0);
  // 299: if
  // 300:   parameter_count_of(handler) == 1:
  // 301:     handler event
  // 302:   :
  // 303:     handler
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  arguments->slots[2] = frame->slots[6] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__36_15;
}
static void entry__36_13(void) {
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
  // 301: handler event
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* event */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* handler */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__36_14(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // handler: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* handler */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 303: handler
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* handler */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__36_15(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 304: raise "invalid continuation"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__36_16;
  result_count = frame->caller_result_count;
  myself = get__raise();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__36_17(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 305: return event
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* event */;
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__36_18(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 307: get_low_level_events false
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__false();
  result_count = frame->caller_result_count;
  myself = var._get_low_level_events;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__36_2(void) {
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
  // 294: length_of(events)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__events();
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__36_3;
}
static void cont__36_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 294: length_of(events) > 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__36_4;
}
static void cont__36_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 294: ... :
  // 295:   $event get(&events)
  // 296:   $handler get_event_handler(event)
  // 297:   if handler.is_defined:
  // 298:     put &waiting_tasks myself
  // 299:     if
  // 300:       parameter_count_of(handler) == 1:
  // 301:         handler event
  // 302:       :
  // 303:         handler
  // ...
  frame->slots[4] /* temp__3 */ = create_closure(entry__36_5, 0);
  // 293: if
  // 294:   length_of(events) > 0:
  // 295:     $event get(&events)
  // 296:     $handler get_event_handler(event)
  // 297:     if handler.is_defined:
  // 298:       put &waiting_tasks myself
  // 299:       if
  // 300:         parameter_count_of(handler) == 1:
  // 301:           handler event
  // 302:         :
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  arguments->slots[2] = func__36_18;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__36_19(void) {
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__38_13(void) {
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
  // 320: $n length_of(events)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__events();
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__38_14;
}
static void cont__38_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* n */, arguments->slots[0]);
  // 321: ... -> i <= n:
  // 322:   $event events(i)
  // 323:   $handler get_event_handler(event)
  // 324:   if handler.is_defined:
  // 325:     delete_at &events i
  // 326:     if
  // 327:       parameter_count_of(handler) == 1:
  // 328:         handler event
  // 329:       :
  // 330:         handler
  // ...
  frame->slots[2] /* temp__1 */ = create_closure(entry__38_15, 0);
  // 321: while -> i <= n:
  // 322:   $event events(i)
  // 323:   $handler get_event_handler(event)
  // 324:   if handler.is_defined:
  // 325:     delete_at &events i
  // 326:     if
  // 327:       parameter_count_of(handler) == 1:
  // 328:         handler event
  // 329:       :
  // 330:         handler
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__while();
  func = myself->type;
  frame->cont = cont__38_32;
}
static void entry__38_18(void) {
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
  // 322: $event events(i)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* i */;
  result_count = 1;
  myself = get__events();
  func = myself->type;
  frame->cont = cont__38_19;
}
static void cont__38_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* event */, arguments->slots[0]);
  // 323: $handler get_event_handler(event)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* event */;
  result_count = 1;
  myself = var._get_event_handler;
  func = myself->type;
  frame->cont = cont__38_20;
}
static void cont__38_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* handler */, arguments->slots[0]);
  // 324: ... handler.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* handler */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__38_21;
}
static void cont__38_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 324: ... :
  // 325:   delete_at &events i
  // 326:   if
  // 327:     parameter_count_of(handler) == 1:
  // 328:       handler event
  // 329:     :
  // 330:       handler
  // 331:   raise "invalid continuation"
  frame->slots[4] /* temp__2 */ = create_closure(entry__38_22, 0);
  // 324: if handler.is_defined:
  // 325:   delete_at &events i
  // 326:   if
  // 327:     parameter_count_of(handler) == 1:
  // 328:       handler event
  // 329:     :
  // 330:       handler
  // 331:   raise "invalid continuation"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__38_30;
}
static void entry__38_22(void) {
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
  // 325: delete_at &events i
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__events();
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* i */;
  result_count = 1;
  myself = get__delete_at();
  func = myself->type;
  frame->cont = cont__38_23;
}
static void cont__38_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__events(arguments->slots[0]);
  // 327: parameter_count_of(handler)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* handler */;
  result_count = 1;
  myself = get__parameter_count_of();
  func = myself->type;
  frame->cont = cont__38_24;
}
static void cont__38_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 327: parameter_count_of(handler) == 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__38_25;
}
static void cont__38_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 327: ... :
  // 328:   handler event
  frame->slots[5] /* temp__3 */ = create_closure(entry__38_26, 0);
  // 329: :
  // 330:   handler
  frame->slots[6] /* temp__4 */ = create_closure(entry__38_27, 0);
  // 326: if
  // 327:   parameter_count_of(handler) == 1:
  // 328:     handler event
  // 329:   :
  // 330:     handler
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  arguments->slots[2] = frame->slots[6] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__38_28;
}
static void entry__38_26(void) {
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
  // 328: handler event
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* event */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* handler */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__38_27(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // handler: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* handler */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 330: handler
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* handler */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__38_28(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 331: raise "invalid continuation"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__38_29;
  result_count = frame->caller_result_count;
  myself = get__raise();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__38_30(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 332: inc &i
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* i */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__38_31;
}
static void cont__38_31(void) {
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
static void entry__38_15(void) {
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
  // 321: ... i <= n
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* n */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* i */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__38_16;
}
static void cont__38_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 321: ... i <= n
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__38_17;
}
static void cont__38_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 321: ... :
  // 322:   $event events(i)
  // 323:   $handler get_event_handler(event)
  // 324:   if handler.is_defined:
  // 325:     delete_at &events i
  // 326:     if
  // 327:       parameter_count_of(handler) == 1:
  // 328:         handler event
  // 329:       :
  // 330:         handler
  // ...
  frame->slots[4] /* temp__3 */ = create_closure(entry__38_18, 0);
  // 321: ... -> i <= n:
  // 322:   $event events(i)
  // 323:   $handler get_event_handler(event)
  // 324:   if handler.is_defined:
  // 325:     delete_at &events i
  // 326:     if
  // 327:       parameter_count_of(handler) == 1:
  // 328:         handler event
  // 329:       :
  // 330:         handler
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__38_32(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 333: get_low_level_events true
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__true();
  result_count = frame->caller_result_count;
  myself = var._get_low_level_events;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__38_1(void) {
  allocate_initialized_frame_gc(0, 3);
  // slot allocations:
  // i: 0
  frame->slots[0] /* i */ = create_cell();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 316: while -> length_of(waiting_tasks) > 0: get(&waiting_tasks)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__38_2;
  result_count = 0;
  myself = get__while();
  func = myself->type;
  frame->cont = cont__38_7;
}
static void entry__38_5(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 316: ... get(&waiting_tasks)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._waiting_tasks;
  result_count = 2;
  myself = get__get();
  func = myself->type;
  frame->cont = cont__38_6;
}
static void cont__38_6(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  var._waiting_tasks = arguments->slots[0];
  frame->slots[0] /* temp__1 */ = arguments->slots[1];
  // 316: ... get(&waiting_tasks)
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* temp__1 */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__38_2(void) {
  allocate_initialized_frame_gc(0, 2);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 316: ... length_of(waiting_tasks)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._waiting_tasks;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__38_3;
}
static void cont__38_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 316: ... length_of(waiting_tasks) > 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__38_4;
}
static void cont__38_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 316: ... -> length_of(waiting_tasks) > 0: get(&waiting_tasks)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = func__38_5;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__38_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 317: ... readers.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._readers;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__38_8;
}
static void cont__38_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 317: ... readers.is_empty && writers.is_empty
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = func__38_9;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__38_11;
}
static void entry__38_9(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 317: ... writers.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._writers;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__38_10;
}
static void cont__38_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 317: ... writers.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__38_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 317: if readers.is_empty && writers.is_empty terminate
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = get__terminate();
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__38_12;
}
static void cont__38_12(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 318: $$i 1
  ((CELL *)frame->slots[0])->contents /* i */ = number__1;
  // 319: ... :
  // 320:   $n length_of(events)
  // 321:   while -> i <= n:
  // 322:     $event events(i)
  // 323:     $handler get_event_handler(event)
  // 324:     if handler.is_defined:
  // 325:       delete_at &events i
  // 326:       if
  // 327:         parameter_count_of(handler) == 1:
  // 328:           handler event
  // ...
  frame->slots[1] /* temp__1 */ = create_closure(entry__38_13, 0);
  // 319: forever:
  // 320:   $n length_of(events)
  // 321:   while -> i <= n:
  // 322:     $event events(i)
  // 323:     $handler get_event_handler(event)
  // 324:     if handler.is_defined:
  // 325:       delete_at &events i
  // 326:       if
  // 327:         parameter_count_of(handler) == 1:
  // 328:           handler event
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__forever();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__39_1(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // args: 0
  // event: 1
  frame->slots[1] /* event */ = create_future();
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 344: ... : (-> continuation)
  // 345:   for_each_pair args: (type fd_or_pid)
  // 346:     case
  // 347:       type
  // 348:       READ_FROM:
  // 349:         want_to_read_from fd_or_pid
  // 350:         !readers(fd_or_pid) continuation
  // 351:       WRITE_TO:
  // 352:         want_to_write_to fd_or_pid
  // 353:         !writers(fd_or_pid) continuation
  // ...
  frame->slots[2] /* temp__1 */ = create_closure(entry__39_2, 0);
  // 344: do $event: (-> continuation)
  // 345:   for_each_pair args: (type fd_or_pid)
  // 346:     case
  // 347:       type
  // 348:       READ_FROM:
  // 349:         want_to_read_from fd_or_pid
  // 350:         !readers(fd_or_pid) continuation
  // 351:       WRITE_TO:
  // 352:         want_to_write_to fd_or_pid
  // 353:         !writers(fd_or_pid) continuation
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__39_14;
}
static void entry__39_2(void) {
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
  // 345: ... : (type fd_or_pid)
  // 346:   case
  // 347:     type
  // 348:     READ_FROM:
  // 349:       want_to_read_from fd_or_pid
  // 350:       !readers(fd_or_pid) continuation
  // 351:     WRITE_TO:
  // 352:       want_to_write_to fd_or_pid
  // 353:       !writers(fd_or_pid) continuation
  // 354:     TERMINATE:
  // ...
  frame->slots[2] /* temp__1 */ = create_closure(entry__39_3, 2);
  // 345: for_each_pair args: (type fd_or_pid)
  // 346:   case
  // 347:     type
  // 348:     READ_FROM:
  // 349:       want_to_read_from fd_or_pid
  // 350:       !readers(fd_or_pid) continuation
  // 351:     WRITE_TO:
  // 352:       want_to_write_to fd_or_pid
  // 353:       !writers(fd_or_pid) continuation
  // 354:     TERMINATE:
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* args */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__for_each_pair();
  func = myself->type;
  frame->cont = cont__39_12;
}
static void entry__39_4(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // fd_or_pid: 0
  // continuation: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* fd_or_pid */
  frame->slots[1] = myself->closure.frame->slots[2]; /* continuation */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 349: want_to_read_from fd_or_pid
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd_or_pid */;
  result_count = 0;
  myself = get__want_to_read_from();
  func = myself->type;
  frame->cont = cont__39_5;
}
static void cont__39_5(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 350: !readers(fd_or_pid) continuation
  frame->slots[2] /* temp__1 */ = frame->slots[1] /* continuation */;
  // 350: !readers(fd_or_pid)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd_or_pid */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = var._readers;
  func = myself->type;
  frame->cont = cont__39_6;
}
static void cont__39_6(void) {
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
static void entry__39_7(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // fd_or_pid: 0
  // continuation: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* fd_or_pid */
  frame->slots[1] = myself->closure.frame->slots[2]; /* continuation */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 352: want_to_write_to fd_or_pid
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd_or_pid */;
  result_count = 0;
  myself = get__want_to_write_to();
  func = myself->type;
  frame->cont = cont__39_8;
}
static void cont__39_8(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 353: !writers(fd_or_pid) continuation
  frame->slots[2] /* temp__1 */ = frame->slots[1] /* continuation */;
  // 353: !writers(fd_or_pid)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd_or_pid */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = var._writers;
  func = myself->type;
  frame->cont = cont__39_9;
}
static void cont__39_9(void) {
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
static void entry__39_10(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // fd_or_pid: 0
  // continuation: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* fd_or_pid */
  frame->slots[1] = myself->closure.frame->slots[2]; /* continuation */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 355: !terminators(fd_or_pid) continuation
  frame->slots[2] /* temp__1 */ = frame->slots[1] /* continuation */;
  // 355: !terminators(fd_or_pid)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd_or_pid */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = var._terminators;
  func = myself->type;
  frame->cont = cont__39_11;
}
static void cont__39_11(void) {
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
static void entry__39_3(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // type: 0
  // fd_or_pid: 1
  // continuation: 2
  frame->slots[2] = myself->closure.frame->slots[0]; /* continuation */
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 348: ... :
  // 349:   want_to_read_from fd_or_pid
  // 350:   !readers(fd_or_pid) continuation
  frame->slots[3] /* temp__1 */ = create_closure(entry__39_4, 0);
  // 351: ... :
  // 352:   want_to_write_to fd_or_pid
  // 353:   !writers(fd_or_pid) continuation
  frame->slots[4] /* temp__2 */ = create_closure(entry__39_7, 0);
  // 354: ... :
  // 355:   !terminators(fd_or_pid) continuation
  frame->slots[5] /* temp__3 */ = create_closure(entry__39_10, 0);
  // 346: case
  // 347:   type
  // 348:   READ_FROM:
  // 349:     want_to_read_from fd_or_pid
  // 350:     !readers(fd_or_pid) continuation
  // 351:   WRITE_TO:
  // 352:     want_to_write_to fd_or_pid
  // 353:     !writers(fd_or_pid) continuation
  // 354:   TERMINATE:
  // 355:     !terminators(fd_or_pid) continuation
  argument_count = 7;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* type */;
  arguments->slots[1] = get__READ_FROM();
  arguments->slots[2] = frame->slots[3] /* temp__1 */;
  arguments->slots[3] = get__WRITE_TO();
  arguments->slots[4] = frame->slots[4] /* temp__2 */;
  arguments->slots[5] = get__TERMINATE();
  arguments->slots[6] = frame->slots[5] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__39_12(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 356: process_events # will never return directly
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = get__process_events();
  func = myself->type;
  frame->cont = cont__39_13;
}
static void cont__39_13(void) {
  myself = frame->slots[0] /* continuation */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__39_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* event */, arguments->slots[0]);
  // 357: for_each_pair args: (type fd_or_pid)
  // 358:   case
  // 359:     type
  // 360:     READ_FROM:
  // 361:       no_longer_want_to_read_from fd_or_pid
  // 362:       !readers(fd_or_pid) undefined
  // 363:     WRITE_TO:
  // 364:       no_longer_want_to_write_to fd_or_pid
  // 365:       !writers(fd_or_pid) undefined
  // 366:     TERMINATE:
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* args */;
  arguments->slots[1] = func__39_15;
  result_count = 0;
  myself = get__for_each_pair();
  func = myself->type;
  frame->cont = cont__39_24;
}
static void entry__39_16(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // fd_or_pid: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* fd_or_pid */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 361: no_longer_want_to_read_from fd_or_pid
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd_or_pid */;
  result_count = 0;
  myself = get__no_longer_want_to_read_from();
  func = myself->type;
  frame->cont = cont__39_17;
}
static void cont__39_17(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 362: !readers(fd_or_pid) undefined
  frame->slots[1] /* temp__1 */ = get__undefined();
  // 362: !readers(fd_or_pid)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd_or_pid */;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = var._readers;
  func = myself->type;
  frame->cont = cont__39_18;
}
static void cont__39_18(void) {
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
static void entry__39_19(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // fd_or_pid: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* fd_or_pid */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 364: no_longer_want_to_write_to fd_or_pid
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd_or_pid */;
  result_count = 0;
  myself = get__no_longer_want_to_write_to();
  func = myself->type;
  frame->cont = cont__39_20;
}
static void cont__39_20(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 365: !writers(fd_or_pid) undefined
  frame->slots[1] /* temp__1 */ = get__undefined();
  // 365: !writers(fd_or_pid)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd_or_pid */;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = var._writers;
  func = myself->type;
  frame->cont = cont__39_21;
}
static void cont__39_21(void) {
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
static void entry__39_22(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // fd_or_pid: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* fd_or_pid */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 367: !terminators(fd_or_pid) undefined
  frame->slots[1] /* temp__1 */ = get__undefined();
  // 367: !terminators(fd_or_pid)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd_or_pid */;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = var._terminators;
  func = myself->type;
  frame->cont = cont__39_23;
}
static void cont__39_23(void) {
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
static void entry__39_15(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // type: 0
  // fd_or_pid: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 360: ... :
  // 361:   no_longer_want_to_read_from fd_or_pid
  // 362:   !readers(fd_or_pid) undefined
  frame->slots[2] /* temp__1 */ = create_closure(entry__39_16, 0);
  // 363: ... :
  // 364:   no_longer_want_to_write_to fd_or_pid
  // 365:   !writers(fd_or_pid) undefined
  frame->slots[3] /* temp__2 */ = create_closure(entry__39_19, 0);
  // 366: ... :
  // 367:   !terminators(fd_or_pid) undefined
  frame->slots[4] /* temp__3 */ = create_closure(entry__39_22, 0);
  // 358: case
  // 359:   type
  // 360:   READ_FROM:
  // 361:     no_longer_want_to_read_from fd_or_pid
  // 362:     !readers(fd_or_pid) undefined
  // 363:   WRITE_TO:
  // 364:     no_longer_want_to_write_to fd_or_pid
  // 365:     !writers(fd_or_pid) undefined
  // 366:   TERMINATE:
  // 367:     !terminators(fd_or_pid) undefined
  argument_count = 7;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* type */;
  arguments->slots[1] = get__READ_FROM();
  arguments->slots[2] = frame->slots[2] /* temp__1 */;
  arguments->slots[3] = get__WRITE_TO();
  arguments->slots[4] = frame->slots[3] /* temp__2 */;
  arguments->slots[5] = get__TERMINATE();
  arguments->slots[6] = frame->slots[4] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__39_24(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 368: -> event
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* event */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__40_1(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // tasks: 0
  frame->slots[0] /* tasks */ = from_arguments(0, argument_count-0);
  // 371: append &waiting_tasks tasks
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._waiting_tasks;
  arguments->slots[1] = frame->slots[0] /* tasks */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__40_2;
}
static void cont__40_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._waiting_tasks = arguments->slots[0];
  // 372: process_events
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = get__process_events();
  func = myself->type;
  frame = frame->caller_frame;
}
EXPORT void collect__basic__event(void) {
  var.std__WRITE_TO = collect_node(var.std__WRITE_TO);
  unique__1_1 = collect_node(unique__1_1);
  var.std__READ_FROM = collect_node(var.std__READ_FROM);
  unique__2_1 = collect_node(unique__2_1);
  var.std__file_descriptor_of = collect_node(var.std__file_descriptor_of);
  var.std__TERMINATE = collect_node(var.std__TERMINATE);
  unique__4_1 = collect_node(unique__4_1);
  var.std__pid_of = collect_node(var.std__pid_of);
  var.std__status_of = collect_node(var.std__status_of);
  var.std__SCREEN_SIZE_CHANGE = collect_node(var.std__SCREEN_SIZE_CHANGE);
  unique__7_1 = collect_node(unique__7_1);
  var.std__width_of = collect_node(var.std__width_of);
  var.std__height_of = collect_node(var.std__height_of);
  var.std__KEY_PRESS = collect_node(var.std__KEY_PRESS);
  unique__10_1 = collect_node(unique__10_1);
  var.std__key_code_of = collect_node(var.std__key_code_of);
  var.std__MOUSE_CLICK = collect_node(var.std__MOUSE_CLICK);
  unique__12_1 = collect_node(unique__12_1);
  var.std__target_of = collect_node(var.std__target_of);
  var.std__PASTE = collect_node(var.std__PASTE);
  unique__14_1 = collect_node(unique__14_1);
  var.std__MESSAGE = collect_node(var.std__MESSAGE);
  unique__15_1 = collect_node(unique__15_1);
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
  var.std__discard = collect_node(var.std__discard);
  var.std__create_event = collect_node(var.std__create_event);
  var._get_low_level_events = collect_node(var._get_low_level_events);
  var._get_event_handler = collect_node(var._get_event_handler);
  var.std__get_event = collect_node(var.std__get_event);
  string__36_16 = collect_node(string__36_16);
  var._waiting_tasks = collect_node(var._waiting_tasks);
  var.std__process_events = collect_node(var.std__process_events);
  string__38_29 = collect_node(string__38_29);
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
  func__20_1 = create_function(entry__20_1, 1);
  func__21_1 = create_function(entry__21_1, 1);
  func__22_1 = create_function(entry__22_1, 1);
  func__23_1 = create_function(entry__23_1, 1);
  func__24_1 = create_function(entry__24_1, 1);
  func__25_1 = create_function(entry__25_1, 1);
  func__27_1 = create_function(entry__27_1, 1);
  func__29_1 = create_function(entry__29_1, 1);
  func__31_1 = create_function(entry__31_1, 1);
  func__32_1 = create_function(entry__32_1, 1);
  func__33_1 = create_function(entry__33_1, 1);
  func__34_18 = create_function(entry__34_18, 0);
  func__34_17 = create_function(entry__34_17, 0);
  func__34_27 = create_function(entry__34_27, 0);
  func__34_39 = create_function(entry__34_39, 1);
  func__34_43 = create_function(entry__34_43, 1);
  func__34_1 = create_function(entry__34_1, 1);
  func__35_1 = create_function(entry__35_1, 1);
  func__36_18 = create_function(entry__36_18, 0);
  func__36_1 = create_function(entry__36_1, 0);
  func__38_5 = create_function(entry__38_5, 0);
  func__38_2 = create_function(entry__38_2, 0);
  func__38_9 = create_function(entry__38_9, 0);
  func__38_1 = create_function(entry__38_1, 0);
  func__39_15 = create_function(entry__39_15, 2);
  func__39_1 = create_function(entry__39_1, -1);
  func__40_1 = create_function(entry__40_1, -1);
}

static int already_run_phase_3 = false;

EXPORT void phase_3__basic__event(void) {
  if (already_run_phase_3) return;
  already_run_phase_3 = true;
  set_module("basic__event");
  set_used_namespaces(used_namespaces);
  unique__1_1 = register_unique_item("std__WRITE_TO");
  assign_value(&var.std__WRITE_TO, unique__1_1);
  define_single_assign_static("std", "WRITE_TO", get__std__WRITE_TO, &var.std__WRITE_TO);
  unique__2_1 = register_unique_item("std__READ_FROM");
  assign_value(&var.std__READ_FROM, unique__2_1);
  define_single_assign_static("std", "READ_FROM", get__std__READ_FROM, &var.std__READ_FROM);
  unique__4_1 = register_unique_item("std__TERMINATE");
  assign_value(&var.std__TERMINATE, unique__4_1);
  define_single_assign_static("std", "TERMINATE", get__std__TERMINATE, &var.std__TERMINATE);
  unique__7_1 = register_unique_item("std__SCREEN_SIZE_CHANGE");
  assign_value(&var.std__SCREEN_SIZE_CHANGE, unique__7_1);
  define_single_assign_static("std", "SCREEN_SIZE_CHANGE", get__std__SCREEN_SIZE_CHANGE, &var.std__SCREEN_SIZE_CHANGE);
  unique__10_1 = register_unique_item("std__KEY_PRESS");
  assign_value(&var.std__KEY_PRESS, unique__10_1);
  define_single_assign_static("std", "KEY_PRESS", get__std__KEY_PRESS, &var.std__KEY_PRESS);
  unique__12_1 = register_unique_item("std__MOUSE_CLICK");
  assign_value(&var.std__MOUSE_CLICK, unique__12_1);
  define_single_assign_static("std", "MOUSE_CLICK", get__std__MOUSE_CLICK, &var.std__MOUSE_CLICK);
  unique__14_1 = register_unique_item("std__PASTE");
  assign_value(&var.std__PASTE, unique__14_1);
  define_single_assign_static("std", "PASTE", get__std__PASTE, &var.std__PASTE);
  unique__15_1 = register_unique_item("std__MESSAGE");
  assign_value(&var.std__MESSAGE, unique__15_1);
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
  string__36_16 = from_latin_1_string("invalid continuation", 20);
  define_single_assign_static("std", "get_event", get__std__get_event, &var.std__get_event);
  string__38_29 = from_latin_1_string("invalid continuation", 20);
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
  use_read_only(NULL, "TERMINATE", &get__TERMINATE, &get_value_or_future__TERMINATE);
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
  use_read_only(NULL, "for_each_pair", &get__for_each_pair, &get_value_or_future__for_each_pair);
  use_read_only(NULL, "forever", &get__forever, &get_value_or_future__forever);
  use_read_only(NULL, "get", &get__get, &get_value_or_future__get);
  use_read_only(NULL, "get_terminal_size", &get__get_terminal_size, &get_value_or_future__get_terminal_size);
  use_polymorphic_function(NULL, "height_of", &get__height_of, &poly_idx__height_of);
  use_read_only(NULL, "if", &get__if, &get_value_or_future__if);
  use_read_only(NULL, "inc", &get__inc, &get_value_or_future__inc);
  use_read_only(NULL, "is_defined", &get__is_defined, &get_value_or_future__is_defined);
  use_read_only(NULL, "is_empty", &get__is_empty, &get_value_or_future__is_empty);
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
  assign_value(&var.std__width_of, create_function(type__std__width_of, -1));
  assign_value(&var.std__height_of, create_function(type__std__height_of, -1));
  assign_value(&var.std__key_code_of, create_function(type__std__key_code_of, -1));
  assign_value(&var.std__target_of, create_function(type__std__target_of, -1));
  assign_value(&var.types__event, get__types__object());
  assign_variable(&var.std__want_to_write_to, &func__20_1);
  assign_variable(&var.std__no_longer_want_to_write_to, &func__21_1);
  assign_variable(&var.std__want_to_read_from, &func__22_1);
  assign_variable(&var.std__no_longer_want_to_read_from, &func__23_1);
  assign_variable(&var.std__wanting_to_write_to, &func__24_1);
  assign_variable(&var.std__wanting_to_read_from, &func__25_1);
  assign_variable(&var.std__wait_to_read_from, &func__27_1);
  assign_variable(&var.std__wait_to_write_to, &func__29_1);
  assign_variable(&var.std__wait_for_termination, &func__31_1);
  assign_variable(&var.std__discard, &func__32_1);
  assign_variable(&var.std__create_event, &func__33_1);
  assign_variable(&var._get_low_level_events, &func__34_1);
  assign_variable(&var._get_event_handler, &func__35_1);
  assign_variable(&var.std__get_event, &func__36_1);
  assign_variable(&var.std__process_events, &func__38_1);
  assign_variable(&var.std__wait_to, &func__39_1);
  assign_variable(&var.std__par, &func__40_1);
}

static int already_run_phase_6 = false;

EXPORT void phase_6__basic__event(void) {
  if (already_run_phase_6) return;
  already_run_phase_6 = true;
  register_collector(collect__basic__event);
}
