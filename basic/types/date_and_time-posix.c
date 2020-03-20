/// link rt
#include <errno.h>
#include <stdint.h>
#include <math.h>
#include <time.h>
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
IMPORT int debug_print(int indent, char *buf, const char *format, ...);
IMPORT NODE *undefined;
IMPORT NODE *from_int(int val);
IMPORT NODE *from_long(long val);
IMPORT NODE *from_double(double val);
IMPORT NODE *boolean_false;
IMPORT NODE *from_bool(int val);
IMPORT NODE *from_uint64(uint64_t val);
IMPORT NODE *create_future(void);
IMPORT int result_count;
IMPORT void invalid_results_error(void);
IMPORT void initialize_future(NODE *var, NODE *val);
IMPORT NODE *create_closure(FUNC type, int par_count);
IMPORT NODE *empty_string;
IMPORT NODE *collect_node(NODE *node);
IMPORT void collect_static_attributes(ATTRIBUTES *attributes);
IMPORT void register_module_info(MODULE_INFO *info);
IMPORT void define_polymorphic_function_with_setter(
  const char *namespace, const char *name, NODE_GETTER getter, int *id_p,
  NODE **var_p
);
IMPORT void set_module(const char *name);
IMPORT void set_used_namespaces(const char **namespaces);
IMPORT void define_single_assign_static(
  const char *namespace, const char *name,
  NODE_GETTER getter, NODE **var_p
);
IMPORT NODE *create_future_with_prototype(NODE *prototype);
IMPORT NODE *from_latin_1_string(const char *str, long len);
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
IMPORT void assign_value(NODE **dest, NODE *val);
IMPORT NODE *from_uint32(uint32_t val);
IMPORT NODE *from_uchar32(unsigned int chr);
IMPORT void assign_variable(NODE **dest, NODE **var_p);
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
static NODE_GETTER get__cond;
static NODE_GETTER get_value_or_future__cond;
static int poly_idx__day_of;
static NODE_GETTER get__day_of;
static int poly_idx__day_of_week_of;
static NODE_GETTER get__day_of_week_of;
static int poly_idx__equal;
static NODE_GETTER get__equal;
static NODE_GETTER get__floor;
static NODE_GETTER get_value_or_future__floor;
static int poly_idx__hour_of;
static NODE_GETTER get__hour_of;
static int poly_idx__less;
static NODE_GETTER get__less;
static int poly_idx__minus;
static NODE_GETTER get__minus;
static int poly_idx__minute_of;
static NODE_GETTER get__minute_of;
static int poly_idx__month_of;
static NODE_GETTER get__month_of;
static NODE_GETTER get__pad_left;
static NODE_GETTER get_value_or_future__pad_left;
static int poly_idx__plus;
static NODE_GETTER get__plus;
static int poly_idx__second_of;
static NODE_GETTER get__second_of;
static NODE_GETTER get__std__less;
static NODE_GETTER get_value_or_future__std__less;
static NODE_GETTER get__std__minus;
static NODE_GETTER get_value_or_future__std__minus;
static NODE_GETTER get__std__over;
static NODE_GETTER get_value_or_future__std__over;
static NODE_GETTER get__std__plus;
static NODE_GETTER get_value_or_future__std__plus;
static NODE_GETTER get__std__times;
static NODE_GETTER get_value_or_future__std__times;
static NODE_GETTER get__string;
static NODE_GETTER get_value_or_future__string;
static int poly_idx__time_shift_of;
static NODE_GETTER get__time_shift_of;
static int poly_idx__to_string;
static NODE_GETTER get__to_string;
static NODE_GETTER get__true;
static NODE_GETTER get_value_or_future__true;
static NODE_GETTER get__types__object;
static NODE_GETTER get_value_or_future__types__object;
static int poly_idx__year_of;
static NODE_GETTER get__year_of;
static struct {
  NODE *std__current_time;
  NODE *std__year_of;
  NODE *std__month_of;
  NODE *std__day_of;
  NODE *std__day_of_week_of;
  NODE *std__hour_of;
  NODE *std__minute_of;
  NODE *std__second_of;
  NODE *std__time_shift_of;
  NODE *types__date_and_time;
  NODE *std__from_unix_time;
  NODE *std__date_and_time;
  NODE *std__sleep;
} var;
static const char *var_names[] = {
};
static void entry__1_1(void);
static NODE *func__1_1;
static NODE *get__std__current_time(void) {
  return var.std__current_time;
}
static int poly_idx__std__year_of;
static void type__std__year_of(void);
static NODE *get__std__year_of(void) {
  return var.std__year_of;
}
static int poly_idx__std__month_of;
static void type__std__month_of(void);
static NODE *get__std__month_of(void) {
  return var.std__month_of;
}
static int poly_idx__std__day_of;
static void type__std__day_of(void);
static NODE *get__std__day_of(void) {
  return var.std__day_of;
}
static int poly_idx__std__day_of_week_of;
static void type__std__day_of_week_of(void);
static NODE *get__std__day_of_week_of(void) {
  return var.std__day_of_week_of;
}
static int poly_idx__std__hour_of;
static void type__std__hour_of(void);
static NODE *get__std__hour_of(void) {
  return var.std__hour_of;
}
static int poly_idx__std__minute_of;
static void type__std__minute_of(void);
static NODE *get__std__minute_of(void) {
  return var.std__minute_of;
}
static int poly_idx__std__second_of;
static void type__std__second_of(void);
static NODE *get__std__second_of(void) {
  return var.std__second_of;
}
static int poly_idx__std__time_shift_of;
static void type__std__time_shift_of(void);
static NODE *get__std__time_shift_of(void) {
  return var.std__time_shift_of;
}

typedef struct {
  void *type;
  ATTRIBUTES *attributes;
  int64_t seconds;
  int32_t nanoseconds;
} DATE_AND_TIME;
static NODE *get__types__date_and_time(void) {
  return var.types__date_and_time;
}
NODE *create__types__date_and_time(int64_t seconds, int32_t nanoseconds);

static long func__types__date_and_time___debug_string(NODE *node, int indent, int max_depth, char *buf);
static void entry__13_1(void);
static NODE *func__13_1;
static NODE *get__std__from_unix_time(void) {
  return var.std__from_unix_time;
}
static void entry__14_1(void);
static NODE *func__14_1;
static NODE *get__std__date_and_time(void) {
  return var.std__date_and_time;
}

static void year_month_day(NODE *node, int *year_p, int *month_p, int *day_p);
static void entry__16_1(void);
static NODE *func__16_1;
static void entry__17_1(void);
static NODE *func__17_1;
static void entry__18_1(void);
static NODE *func__18_1;
static void entry__19_1(void);
static NODE *func__19_1;
static void entry__20_1(void);
static NODE *func__20_1;
static void entry__21_1(void);
static NODE *func__21_1;
static void entry__22_1(void);
static NODE *func__22_1;
static void entry__23_1(void);
static NODE *func__23_1;
static void entry__24_1(void);
static NODE *func__24_1;
static void entry__25_1(void);
static NODE *func__25_1;
static void entry__26_1(void);
static NODE *func__26_1;
static void entry__27_1(void);
static NODE *func__27_1;
static NODE *func__28_1;
static void entry__28_1(void);
static FRAME_INFO frame__28_1 = {4, {"self", "ts", "t", "second"}};
static void cont__28_2(void);
static void cont__28_3(void);
static void cont__28_4(void);
static void cont__28_5(void);
static void cont__28_6(void);
static NODE *string__28_7;
static void cont__28_8(void);
static void cont__28_9(void);
static NODE *string__28_10;
static void cont__28_11(void);
static void cont__28_12(void);
static void cont__28_13(void);
static NODE *string__28_14;
static void cont__28_15(void);
static void cont__28_16(void);
static NODE *string__28_17;
static void cont__28_18(void);
static void cont__28_19(void);
static void cont__28_20(void);
static void cont__28_21(void);
static void cont__28_22(void);
static NODE *string__28_23;
static void cont__28_24(void);
static NODE *func__28_25;
static void entry__28_25(void);
static FRAME_INFO frame__28_25 = {1, {"ts"}};
static void cont__28_26(void);
static NODE *func__28_27;
static void entry__28_27(void);
static FRAME_INFO frame__28_27 = {1, {"ts"}};
static void cont__28_28(void);
static NODE *string__28_29;
static void cont__28_30(void);
static NODE *func__28_31;
static void entry__28_31(void);
static FRAME_INFO frame__28_31 = {1, {"ts"}};
static void cont__28_32(void);
static NODE *func__28_33;
static void entry__28_33(void);
static FRAME_INFO frame__28_33 = {1, {"ts"}};
static void cont__28_34(void);
static NODE *func__28_35;
static void entry__28_35(void);
static FRAME_INFO frame__28_35 = {0, {}};
static NODE *func__28_36;
static void entry__28_36(void);
static FRAME_INFO frame__28_36 = {0, {}};
static void cont__28_37(void);
static NODE *string__28_38;
static NODE *string__28_39;
static NODE *string__28_40;
static NODE *string__28_41;
static NODE *string__28_42;
static void cont__28_43(void);
static void entry__29_1(void);
static NODE *func__29_1;
static NODE *get__std__sleep(void) {
  return var.std__sleep;
}
void run__basic__types__date_and_time(void);

static CONTINUATION_INFO continuation_info[] = {
  {type__std__year_of, NULL, 28, 28, 2, 13, 1},
  {type__std__month_of, NULL, 29, 29, 2, 14, 1},
  {type__std__day_of, NULL, 30, 30, 2, 12, 1},
  {type__std__day_of_week_of, NULL, 31, 31, 2, 20, 1},
  {type__std__hour_of, NULL, 32, 32, 2, 13, 1},
  {type__std__minute_of, NULL, 33, 33, 2, 15, 1},
  {type__std__second_of, NULL, 34, 34, 2, 15, 1},
  {type__std__time_shift_of, NULL, 35, 35, 2, 19, 1},
  {run__basic__types__date_and_time, NULL, },
  {entry__1_1, NULL, 26, 32, 3, 2},
  {entry__13_1, NULL, 67, 72, 3, 2, 1},
  {entry__14_1, NULL, 75, 126, 3, 2, 1},
  {entry__16_1, NULL, 208, 213, 3, 2, 1},
  {entry__17_1, NULL, 216, 221, 3, 2, 1},
  {entry__18_1, NULL, 224, 229, 3, 2, 1},
  {entry__19_1, NULL, 232, 237, 3, 2, 1},
  {entry__20_1, NULL, 240, 244, 3, 2, 1},
  {entry__21_1, NULL, 247, 251, 3, 2, 1},
  {entry__22_1, NULL, 254, 260, 3, 2, 1},
  {entry__23_1, NULL, 263, 277, 3, 2, 1},
  {entry__24_1, NULL, 280, 301, 3, 2, 1},
  {entry__25_1, NULL, 304, 313, 3, 2, 1},
  {entry__26_1, NULL, 316, 326, 3, 2, 1},
  {entry__27_1, NULL, 329, 340, 3, 2, 1},
  {entry__28_27, NULL, 363, 363, 33, 39, 1},
  {cont__28_28, &frame__28_27, 363, 363, 22, 40, 1},
  {cont__28_30, &frame__28_27, 363, 363, 19, 40, 1},
  {entry__28_25, NULL, 363, 363, 12, 17, 1},
  {cont__28_26, &frame__28_25, 363, 363, 9, 40, 1},
  {entry__28_33, NULL, 364, 364, 22, 28, 1},
  {cont__28_34, &frame__28_33, 364, 364, 19, 28, 1},
  {entry__28_31, NULL, 364, 364, 12, 17, 1},
  {cont__28_32, &frame__28_31, 364, 364, 9, 28, 1},
  {entry__28_36, NULL, 365, 365, 17, 21, 1},
  {entry__28_35, NULL, 365, 365, 9, 21, 1},
  {entry__28_1, NULL, 343, 343, 3, 25, 1},
  {cont__28_2, &frame__28_1, 344, 344, 3, 12, 1},
  {cont__28_3, &frame__28_1, 345, 345, 3, 22, 1},
  {cont__28_4, &frame__28_1, 348, 348, 7, 16, 1},
  {cont__28_5, &frame__28_1, 350, 350, 16, 26, 1},
  {cont__28_6, &frame__28_1, 350, 350, 7, 33, 1},
  {cont__28_8, &frame__28_1, 352, 352, 16, 24, 1},
  {cont__28_9, &frame__28_1, 352, 352, 7, 31, 1},
  {cont__28_11, &frame__28_1, 354, 354, 7, 16, 1},
  {cont__28_12, &frame__28_1, 356, 356, 16, 27, 1},
  {cont__28_13, &frame__28_1, 356, 356, 7, 34, 1},
  {cont__28_15, &frame__28_1, 358, 358, 16, 28, 1},
  {cont__28_16, &frame__28_1, 358, 358, 7, 35, 1},
  {cont__28_18, &frame__28_1, 360, 360, 35, 47, 1},
  {cont__28_19, &frame__28_1, 360, 360, 28, 47, 1},
  {cont__28_20, &frame__28_1, 360, 360, 22, 47, 1},
  {cont__28_21, &frame__28_1, 360, 360, 16, 49, 1},
  {cont__28_22, &frame__28_1, 360, 360, 7, 56, 1},
  {cont__28_24, &frame__28_1, 362, 365, 7, 20, 1},
  {cont__28_37, &frame__28_1, 347, 365, 5, 21, 1},
  {cont__28_43, &frame__28_1, 346, 365, 3, 23, 1},
  {entry__29_1, NULL, 368, 378, 3, 2, 1}
};

union NODE {
  struct {
    FUNC type;
    ATTRIBUTES *attributes;
  };
  CONTINUATION continuation;
  CLOSURE closure;
  SIMPLE_NODE simple_node;
  DATE_AND_TIME date_and_time;
};
static void type__std__year_of(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__year_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__year_of, attr);
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
static void type__std__month_of(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__month_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__month_of, attr);
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
static void type__std__day_of(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__day_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__day_of, attr);
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
static void type__std__day_of_week_of(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__day_of_week_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__day_of_week_of, attr);
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
static void type__std__hour_of(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__hour_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__hour_of, attr);
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
static void type__std__minute_of(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__minute_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__minute_of, attr);
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
static void type__std__second_of(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__second_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__second_of, attr);
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
static void type__std__time_shift_of(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__time_shift_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__time_shift_of, attr);
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
static NODE *number__3600;
static NODE *number__0;
static NODE *number__1000;
static NODE *number__3;
static NODE *character__32;
static NODE *character__46;
static NODE *number__2;

static const char *used_namespaces[] = {
  "std",
  NULL
};

static MODULE_INFO module_info = {
  NULL,
  "basic__types__date_and_time",
  continuation_info,
  sizeof(continuation_info)/sizeof(CONTINUATION_INFO),
  (NODE **)&var,
  var_names,
  sizeof(var_names)/sizeof(const char *),
  used_namespaces,
  {DEBUG_FILENAME("basic/types/date_and_time-posix.sim"), DEBUG_FILENAME("basic/types/date_and_time-all-common.sim")}
};

/******
C O D E
******/

static int already_run = false;

EXPORT void run__basic__types__date_and_time(void) {
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
static void entry__1_1(void) {
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  struct timespec timespec;
  clock_gettime(CLOCK_REALTIME, &timespec);
  {
    NODE *result__node = (NODE *)(create__types__date_and_time(timespec.tv_sec, timespec.tv_nsec));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void *collect_date_and_time(DATE_AND_TIME *node) {
  DATE_AND_TIME *new_node = allocate(sizeof(DATE_AND_TIME));
  new_node->type = node->type;
  *(void **)node = ENCODE_ADDRESS(new_node);
  new_node->attributes = collect_attributes(node->attributes);
  new_node->seconds = node->seconds;
  new_node->nanoseconds = node->nanoseconds;
  return new_node;
}

static VTABLE vtable__types__date_and_time = {
  sizeof(DATE_AND_TIME),
  (COLLECTOR *)&collect_date_and_time,
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
  &func__types__date_and_time___debug_string
};

static ATTRIBUTES attributes__types__date_and_time = {
  &vtable__types__date_and_time,
  {
    &undefined_attributes_level_1, &undefined_attributes_level_2,
    &undefined_attributes_level_3, &undefined_attributes_level_4,
    &undefined_attributes_level_5, &undefined_attributes_level_6,
    &undefined_attributes_level_7
  }
};

void type__types__date_and_time(void) {
  {
    runtime_error("Attempt to call a date and time object as a function!");
  }
}
NODE *create__types__date_and_time(int64_t seconds, int32_t nanoseconds) {
  NODE *node = allocate(sizeof(DATE_AND_TIME));
  node->type = type__types__date_and_time;
  node->attributes = &attributes__types__date_and_time;
  node->date_and_time.seconds = seconds;
  node->date_and_time.nanoseconds = nanoseconds;
  return node;
}

static long func__types__date_and_time___debug_string(NODE *node, int indent, int max_depth, char *buf) {
  return debug_print(indent, buf, "<date and time %d.%09d>",
    node->date_and_time.seconds, node->date_and_time.nanoseconds);
}
static void entry__13_1(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  int64_t sec = to_int64(arguments->slots[0]);
  {
    NODE *result__node = (NODE *)(create__types__date_and_time(sec, 0));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__14_1(void) {
  if (argument_count != 6) {
    invalid_arguments_error();
    return;
  }
  int year = to_int(arguments->slots[0]);
  int month = to_int(arguments->slots[1]);
  int day = to_int(arguments->slots[2]);
  int hour = to_int(arguments->slots[3]);
  int minute = to_int(arguments->slots[4]);
  double second = to_double(arguments->slots[5]);
  int64_t seconds = floor(second);
  int32_t nanoseconds = 1000000000*(second-seconds);
  if (
    year < 1970 ||
    month < 1 || month > 12 ||
    day < 1 ||
    hour < 0 || hour > 23 ||
    minute < 0 || minute > 59 ||
    seconds < 0 || seconds > 59
  ) {
    arguments = node_p;
    arguments->slots[0] = undefined;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  int64_t days = 0;
  year -= 1970;
  if (year >= 2) {
    days += 730;
    year -= 2;
    days += 1461*(year/4);
    year %= 4;
    days += 365*year;
    if (year > 0) ++days;
  } else {
    if (year == 1971) days += 365;
    year += 2;
  }
  int m;
  for (m = 1; m <= 12; ++m) {
    int d;
    switch (m) {
      case 2:
        d = year == 0 ? 29 : 28;
        break;
      case 4: case 6: case 9: case 11:
        d = 30;
        break;
      default:
        d = 31;
    }
    if (month > m) days += d;
    if (month == m && day > d) {
    arguments = node_p;
    arguments->slots[0] = undefined;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  }
  days += day-1;
  seconds += 86400*(uint64_t)days+3600*hour+60*minute;
  {
    NODE *result__node = (NODE *)(create__types__date_and_time(seconds, nanoseconds));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}

static void year_month_day(NODE *node, int *year_p, int *month_p, int *day_p) {
  long days;
  int year, month, day, quads;
  int is_a_leap_year;
  days = arguments->slots[0]->date_and_time.seconds/86400;
  is_a_leap_year = false;
  if (days < 730) { // 1970, 1971
    year = days/365;
    days -= 365*year;
    year += 1970;
  } else { // 1972 and later
    days -= 730;
    quads = days/1461;
    days -= 1461*quads;
    year = 1972+4*quads;
    if (days >= 1096) {
      year += 3;
      days -= 1096;
    } else if (days >= 731) {
      year += 2;
      days -= 731;
    } else if (days >= 366) {
      ++year;
      days -= 366;
    } else {
      is_a_leap_year = true;
    }
  }
  month = 1;
  if (days < 31) goto done; // January
  days -= 31;
  ++month;
  if (is_a_leap_year) {
    if (days < 29) goto done; // February
    days -= 29;
  } else {
    if (days < 28) goto done; // February
    days -= 28;
  }
  ++month;
  if (days < 31) goto done; // March
  days -= 31;
  ++month;
  if (days < 30) goto done; // April
  days -= 30;
  ++month;
  if (days < 31) goto done; // May
  days -= 31;
  ++month;
  if (days < 30) goto done; // June
  days -= 30;
  ++month;
  if (days < 31) goto done; // July
  days -= 31;
  ++month;
  if (days < 31) goto done; // August
  days -= 31;
  ++month;
  if (days < 30) goto done; // September
  days -= 30;
  ++month;
  if (days < 31) goto done; // October
  days -= 31;
  ++month;
  if (days < 30) goto done; // November
  days -= 30;
  ++month; // December
  done:
  if (year_p) *year_p = year;
  if (month_p) *month_p = month;
  if (day_p) *day_p = days+1;
}
static void entry__16_1(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  int year;
  year_month_day(arguments->slots[0], &year, NULL, NULL);
  {
    NODE *result__node = (NODE *)(from_int(year));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__17_1(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  int month;
  year_month_day(arguments->slots[0], NULL, &month, NULL);
  {
    NODE *result__node = (NODE *)(from_int(month));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__18_1(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  int day;
  year_month_day(arguments->slots[0], NULL, NULL, &day);
  {
    NODE *result__node = (NODE *)(from_int(day));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__19_1(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  {
    NODE *result__node = (NODE *)(from_long(
      (3+arguments->slots[0]->date_and_time.seconds/86400)%7+1));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__20_1(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  int seconds = arguments->slots[0]->date_and_time.seconds%86400;
  {
    NODE *result__node = (NODE *)(from_int(seconds/3600));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__21_1(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  int seconds = arguments->slots[0]->date_and_time.seconds%3600;
  {
    NODE *result__node = (NODE *)(from_int(seconds/60));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__22_1(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  {
    NODE *result__node = (NODE *)(from_double(
      arguments->slots[0]->date_and_time.seconds%60+
      arguments->slots[0]->date_and_time.nanoseconds/1000000000.0));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__23_1(void) {
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  int64_t seconds = arguments->slots[0]->date_and_time.seconds;
  int32_t nanoseconds = arguments->slots[0]->date_and_time.nanoseconds;
  double delta = to_double(arguments->slots[1]);
  int64_t delta_seconds = round(delta);
  int32_t delta_nanoseconds = 1000000000*(delta-delta_seconds);
  seconds += delta_seconds;
  nanoseconds += delta_nanoseconds;
  if (nanoseconds >= 1000000000) {
    nanoseconds -= 1000000000;
    ++seconds;
  }
  {
    NODE *result__node = (NODE *)(create__types__date_and_time(seconds, nanoseconds));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  };
}
static void entry__24_1(void) {
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  int64_t seconds = arguments->slots[0]->date_and_time.seconds;
  int32_t nanoseconds = arguments->slots[0]->date_and_time.nanoseconds;
  if ((arguments->slots[1])->type == type__types__date_and_time) {
    int64_t seconds_2 = arguments->slots[1]->date_and_time.seconds;
    int32_t nanoseconds_2 = arguments->slots[1]->date_and_time.nanoseconds;
    {
    NODE *result__node = (NODE *)(from_double(
      seconds-seconds_2+(nanoseconds-nanoseconds_2)/1000000000.0));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else {
    double delta = to_double(arguments->slots[1]);
    int64_t delta_seconds = round(delta);
    int32_t delta_nanoseconds = 1000000000*(delta-delta_seconds);
    seconds -= delta_seconds;
    nanoseconds -= delta_nanoseconds;
    if (nanoseconds < 00) {
      nanoseconds += 1000000000;
      --seconds;
    }
    {
    NODE *result__node = (NODE *)(create__types__date_and_time(seconds, nanoseconds));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  };
  }
}
static void entry__25_1(void) {
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  NODE *left, *right;
  left = arguments->slots[0];
  right = arguments->slots[1];
  if ((arguments->slots[1])->type != type__types__date_and_time) {
    arguments = node_p;
    arguments->slots[0] = boolean_false;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  {
    NODE *result__node = (NODE *)(from_bool(left->date_and_time.seconds == right->date_and_time.seconds &&
    left->date_and_time.nanoseconds == right->date_and_time.nanoseconds));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__26_1(void) {
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  NODE *left, *right;
  left = arguments->slots[0];
  right = arguments->slots[1];
  if ((arguments->slots[1])->type != type__types__date_and_time) {
    invalid_arguments_error();
  }
  {
    NODE *result__node = (NODE *)(from_bool(left->date_and_time.seconds < right->date_and_time.seconds ||
    left->date_and_time.seconds == right->date_and_time.seconds &&
    left->date_and_time.nanoseconds < right->date_and_time.nanoseconds));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__27_1(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // This insane looking sequence of calls correctly computes the time shift!!!
  struct tm tm;
  time_t t1 = arguments->slots[0]->date_and_time.seconds;
  localtime_r(&t1, &tm);
  int isdst = tm.tm_isdst;
  gmtime_r(&t1, &tm);
  tm.tm_isdst = isdst;
  time_t t2 = mktime(&tm);
  {
    NODE *result__node = (NODE *)(from_uint64(t1-t2));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__28_1(void) {
  allocate_initialized_frame_gc(1, 23);
  // slot allocations:
  // self: 0
  // ts: 1
  // t: 2
  // second: 3
  frame->slots[1] /* ts */ = create_future();
  frame->slots[2] /* t */ = create_future();
  frame->slots[3] /* second */ = create_future();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 343: $ts time_shift_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__time_shift_of();
  func = myself->type;
  frame->cont = cont__28_2;
}
static void cont__28_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* ts */, arguments->slots[0]);
  // 344: $t self+ts
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  arguments->slots[1] = frame->slots[1] /* ts */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__28_3;
}
static void cont__28_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* t */, arguments->slots[0]);
  // 345: $second second_of(t)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* t */;
  result_count = 1;
  myself = get__second_of();
  func = myself->type;
  frame->cont = cont__28_4;
}
static void cont__28_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* second */, arguments->slots[0]);
  // 348: year_of(t)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* t */;
  result_count = 1;
  myself = get__year_of();
  func = myself->type;
  frame->cont = cont__28_5;
}
static void cont__28_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 350: ... month_of(t)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* t */;
  result_count = 1;
  myself = get__month_of();
  func = myself->type;
  frame->cont = cont__28_6;
}
static void cont__28_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__4 */ = arguments->slots[0];
  // 350: pad_left(month_of(t) 2 "0")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__4 */;
  arguments->slots[1] = number__2;
  arguments->slots[2] = string__28_7;
  result_count = 1;
  myself = get__pad_left();
  func = myself->type;
  frame->cont = cont__28_8;
}
static void cont__28_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 352: ... day_of(t)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* t */;
  result_count = 1;
  myself = get__day_of();
  func = myself->type;
  frame->cont = cont__28_9;
}
static void cont__28_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__6 */ = arguments->slots[0];
  // 352: pad_left(day_of(t) 2 "0")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__6 */;
  arguments->slots[1] = number__2;
  arguments->slots[2] = string__28_10;
  result_count = 1;
  myself = get__pad_left();
  func = myself->type;
  frame->cont = cont__28_11;
}
static void cont__28_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__5 */ = arguments->slots[0];
  // 354: hour_of(t)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* t */;
  result_count = 1;
  myself = get__hour_of();
  func = myself->type;
  frame->cont = cont__28_12;
}
static void cont__28_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__7 */ = arguments->slots[0];
  // 356: ... minute_of(t)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* t */;
  result_count = 1;
  myself = get__minute_of();
  func = myself->type;
  frame->cont = cont__28_13;
}
static void cont__28_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__9 */ = arguments->slots[0];
  // 356: pad_left(minute_of(t) 2 "0")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[12] /* temp__9 */;
  arguments->slots[1] = number__2;
  arguments->slots[2] = string__28_14;
  result_count = 1;
  myself = get__pad_left();
  func = myself->type;
  frame->cont = cont__28_15;
}
static void cont__28_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__8 */ = arguments->slots[0];
  // 358: ... floor(second)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* second */;
  result_count = 1;
  myself = get__floor();
  func = myself->type;
  frame->cont = cont__28_16;
}
static void cont__28_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[14] /* temp__11 */ = arguments->slots[0];
  // 358: pad_left(floor(second) 2 "0")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[14] /* temp__11 */;
  arguments->slots[1] = number__2;
  arguments->slots[2] = string__28_17;
  result_count = 1;
  myself = get__pad_left();
  func = myself->type;
  frame->cont = cont__28_18;
}
static void cont__28_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__10 */ = arguments->slots[0];
  // 360: ... floor(second)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* second */;
  result_count = 1;
  myself = get__floor();
  func = myself->type;
  frame->cont = cont__28_19;
}
static void cont__28_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[19] /* temp__16 */ = arguments->slots[0];
  // 360: ... second-floor(second)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* second */;
  arguments->slots[1] = frame->slots[19] /* temp__16 */;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__28_20;
}
static void cont__28_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[18] /* temp__15 */ = arguments->slots[0];
  // 360: ... 1000*(second-floor(second)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__1000;
  arguments->slots[1] = frame->slots[18] /* temp__15 */;
  result_count = 1;
  myself = get__std__times();
  func = myself->type;
  frame->cont = cont__28_21;
}
static void cont__28_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[17] /* temp__14 */ = arguments->slots[0];
  // 360: ... floor(1000*(second-floor(second)))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[17] /* temp__14 */;
  result_count = 1;
  myself = get__floor();
  func = myself->type;
  frame->cont = cont__28_22;
}
static void cont__28_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[16] /* temp__13 */ = arguments->slots[0];
  // 360: pad_left(floor(1000*(second-floor(second))) 3 "0")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[16] /* temp__13 */;
  arguments->slots[1] = number__3;
  arguments->slots[2] = string__28_23;
  result_count = 1;
  myself = get__pad_left();
  func = myself->type;
  frame->cont = cont__28_24;
}
static void cont__28_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[15] /* temp__12 */ = arguments->slots[0];
  // 363: -> ts > 0 -> string("+" ts/3600)
  frame->slots[21] /* temp__18 */ = create_closure(entry__28_25, 0);
  // 364: -> ts < 0 -> ts/3600
  frame->slots[22] /* temp__19 */ = create_closure(entry__28_31, 0);
  // 362: cond
  // 363:   -> ts > 0 -> string("+" ts/3600)
  // 364:   -> ts < 0 -> ts/3600
  // 365:   -> true -> ""
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[21] /* temp__18 */;
  arguments->slots[1] = frame->slots[22] /* temp__19 */;
  arguments->slots[2] = func__28_35;
  result_count = 1;
  myself = get__cond();
  func = myself->type;
  frame->cont = cont__28_37;
}
static void entry__28_36(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 365: ... -> ""
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = empty_string;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__28_33(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // ts: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* ts */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 364: ... ts/3600
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* ts */;
  arguments->slots[1] = number__3600;
  result_count = 1;
  myself = get__std__over();
  func = myself->type;
  frame->cont = cont__28_34;
}
static void cont__28_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 364: ... -> ts/3600
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__28_27(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // ts: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* ts */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 363: ... ts/3600
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* ts */;
  arguments->slots[1] = number__3600;
  result_count = 1;
  myself = get__std__over();
  func = myself->type;
  frame->cont = cont__28_28;
}
static void cont__28_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 363: ... string("+" ts/3600)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__28_29;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__28_30;
}
static void cont__28_30(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 363: ... -> string("+" ts/3600)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__28_25(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // ts: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* ts */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 363: ... ts > 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = frame->slots[0] /* ts */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__28_26;
}
static void cont__28_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 363: ... -> string("+" ts/3600)
  frame->slots[2] /* temp__2 */ = create_closure(entry__28_27, 0);
  // 363: -> ts > 0 -> string("+" ts/3600)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__28_31(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // ts: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* ts */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 364: ... ts < 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* ts */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__28_32;
}
static void cont__28_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 364: ... -> ts/3600
  frame->slots[2] /* temp__2 */ = create_closure(entry__28_33, 0);
  // 364: -> ts < 0 -> ts/3600
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__28_35(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 365: -> true -> ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__true();
  arguments->slots[1] = func__28_36;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__28_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[20] /* temp__17 */ = arguments->slots[0];
  // 347: string
  // 348:   year_of(t)
  // 349:   "-"
  // 350:   pad_left(month_of(t) 2 "0")
  // 351:   "-"
  // 352:   pad_left(day_of(t) 2 "0")
  // 353:   ' '
  // 354:   hour_of(t)
  // 355:   ":"
  // 356:   pad_left(minute_of(t) 2 "0")
  // ...
  argument_count = 15;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  arguments->slots[1] = string__28_38;
  arguments->slots[2] = frame->slots[6] /* temp__3 */;
  arguments->slots[3] = string__28_39;
  arguments->slots[4] = frame->slots[8] /* temp__5 */;
  arguments->slots[5] = character__32;
  arguments->slots[6] = frame->slots[10] /* temp__7 */;
  arguments->slots[7] = string__28_40;
  arguments->slots[8] = frame->slots[11] /* temp__8 */;
  arguments->slots[9] = string__28_41;
  arguments->slots[10] = frame->slots[13] /* temp__10 */;
  arguments->slots[11] = character__46;
  arguments->slots[12] = frame->slots[15] /* temp__12 */;
  arguments->slots[13] = string__28_42;
  arguments->slots[14] = frame->slots[20] /* temp__17 */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__28_43;
}
static void cont__28_43(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 346: ->
  // 347:   string
  // 348:     year_of(t)
  // 349:     "-"
  // 350:     pad_left(month_of(t) 2 "0")
  // 351:     "-"
  // 352:     pad_left(day_of(t) 2 "0")
  // 353:     ' '
  // 354:     hour_of(t)
  // 355:     ":"
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__29_1(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  double seconds = to_double(arguments->slots[0]);
  if (seconds > 0) {
    struct timespec req;
    req.tv_sec = seconds;
    req.tv_nsec = 1000000000*(seconds-req.tv_sec);
    while (nanosleep(&req, &req) == -1 && errno == EINTR);
  }
  {
    argument_count = 0;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
EXPORT void collect__basic__types__date_and_time(void) {
  var.std__current_time = collect_node(var.std__current_time);
  var.std__year_of = collect_node(var.std__year_of);
  var.std__month_of = collect_node(var.std__month_of);
  var.std__day_of = collect_node(var.std__day_of);
  var.std__day_of_week_of = collect_node(var.std__day_of_week_of);
  var.std__hour_of = collect_node(var.std__hour_of);
  var.std__minute_of = collect_node(var.std__minute_of);
  var.std__second_of = collect_node(var.std__second_of);
  var.std__time_shift_of = collect_node(var.std__time_shift_of);
  var.types__date_and_time = collect_node(var.types__date_and_time);
  collect_static_attributes(&attributes__types__date_and_time);
  var.std__from_unix_time = collect_node(var.std__from_unix_time);
  var.std__date_and_time = collect_node(var.std__date_and_time);
  string__28_7 = collect_node(string__28_7);
  string__28_10 = collect_node(string__28_10);
  string__28_14 = collect_node(string__28_14);
  string__28_17 = collect_node(string__28_17);
  string__28_23 = collect_node(string__28_23);
  string__28_29 = collect_node(string__28_29);
  func__28_36 = collect_node(func__28_36);
  func__28_35 = collect_node(func__28_35);
  string__28_38 = collect_node(string__28_38);
  string__28_39 = collect_node(string__28_39);
  string__28_40 = collect_node(string__28_40);
  string__28_41 = collect_node(string__28_41);
  string__28_42 = collect_node(string__28_42);
  func__28_1 = collect_node(func__28_1);
  var.std__sleep = collect_node(var.std__sleep);
  number__3600 = collect_node(number__3600);
  number__0 = collect_node(number__0);
  number__1000 = collect_node(number__1000);
  number__3 = collect_node(number__3);
  character__32 = collect_node(character__32);
  character__46 = collect_node(character__46);
  number__2 = collect_node(number__2);
}

static int already_run_phase_1 = false;

EXPORT void phase_1__basic__types__date_and_time(void) {
  if (already_run_phase_1) return;
  already_run_phase_1 = true;
  register_module_info(&module_info);
  define_polymorphic_function_with_setter("std", "year_of", get__std__year_of, &poly_idx__std__year_of, &var.std__year_of);
  define_polymorphic_function_with_setter("std", "month_of", get__std__month_of, &poly_idx__std__month_of, &var.std__month_of);
  define_polymorphic_function_with_setter("std", "day_of", get__std__day_of, &poly_idx__std__day_of, &var.std__day_of);
  define_polymorphic_function_with_setter("std", "day_of_week_of", get__std__day_of_week_of, &poly_idx__std__day_of_week_of, &var.std__day_of_week_of);
  define_polymorphic_function_with_setter("std", "hour_of", get__std__hour_of, &poly_idx__std__hour_of, &var.std__hour_of);
  define_polymorphic_function_with_setter("std", "minute_of", get__std__minute_of, &poly_idx__std__minute_of, &var.std__minute_of);
  define_polymorphic_function_with_setter("std", "second_of", get__std__second_of, &poly_idx__std__second_of, &var.std__second_of);
  define_polymorphic_function_with_setter("std", "time_shift_of", get__std__time_shift_of, &poly_idx__std__time_shift_of, &var.std__time_shift_of);
}

static int already_run_phase_2 = false;

EXPORT void phase_2__basic__types__date_and_time(void) {
  if (already_run_phase_2) return;
  already_run_phase_2 = true;
  set_module("basic__types__date_and_time");
  set_used_namespaces(used_namespaces);
  number__3600 = create_future();
  number__0 = create_future();
  number__1000 = create_future();
  number__3 = create_future();
  character__32 = create_future();
  character__46 = create_future();
  number__2 = create_future();
  func__1_1 = create_future();
  define_single_assign_static("std", "current_time", get__std__current_time, &var.std__current_time);
  var.types__date_and_time = create_future_with_prototype(create__types__date_and_time(0, 0));
  define_single_assign_static("types", "date_and_time", get__types__date_and_time, &var.types__date_and_time);
  func__13_1 = create_future();
  define_single_assign_static("std", "from_unix_time", get__std__from_unix_time, &var.std__from_unix_time);
  func__14_1 = create_future();
  define_single_assign_static("std", "date_and_time", get__std__date_and_time, &var.std__date_and_time);
  func__16_1 = create_future();
  func__17_1 = create_future();
  func__18_1 = create_future();
  func__19_1 = create_future();
  func__20_1 = create_future();
  func__21_1 = create_future();
  func__22_1 = create_future();
  func__23_1 = create_future();
  func__24_1 = create_future();
  func__25_1 = create_future();
  func__26_1 = create_future();
  func__27_1 = create_future();
  string__28_7 = from_latin_1_string("0", 1);
  string__28_10 = from_latin_1_string("0", 1);
  string__28_14 = from_latin_1_string("0", 1);
  string__28_17 = from_latin_1_string("0", 1);
  string__28_23 = from_latin_1_string("0", 1);
  string__28_29 = from_latin_1_string("+", 1);
  func__28_36 = create_future();
  func__28_35 = create_future();
  string__28_38 = from_latin_1_string("-", 1);
  string__28_39 = from_latin_1_string("-", 1);
  string__28_40 = from_latin_1_string(":", 1);
  string__28_41 = from_latin_1_string(":", 1);
  string__28_42 = from_latin_1_string(" GMT", 4);
  func__28_1 = create_future();
  func__29_1 = create_future();
  define_single_assign_static("std", "sleep", get__std__sleep, &var.std__sleep);
}

static int already_run_phase_3 = false;

EXPORT void phase_3__basic__types__date_and_time(void) {
  if (already_run_phase_3) return;
  already_run_phase_3 = true;
  set_module("basic__types__date_and_time");
  set_used_namespaces(used_namespaces);
  use_read_only(NULL, "cond", &get__cond, &get_value_or_future__cond);
  use_polymorphic_function(NULL, "day_of", &get__day_of, &poly_idx__day_of);
  use_polymorphic_function(NULL, "day_of_week_of", &get__day_of_week_of, &poly_idx__day_of_week_of);
  use_polymorphic_function(NULL, "equal", &get__equal, &poly_idx__equal);
  use_read_only(NULL, "floor", &get__floor, &get_value_or_future__floor);
  use_polymorphic_function(NULL, "hour_of", &get__hour_of, &poly_idx__hour_of);
  use_polymorphic_function(NULL, "less", &get__less, &poly_idx__less);
  use_polymorphic_function(NULL, "minus", &get__minus, &poly_idx__minus);
  use_polymorphic_function(NULL, "minute_of", &get__minute_of, &poly_idx__minute_of);
  use_polymorphic_function(NULL, "month_of", &get__month_of, &poly_idx__month_of);
  use_read_only(NULL, "pad_left", &get__pad_left, &get_value_or_future__pad_left);
  use_polymorphic_function(NULL, "plus", &get__plus, &poly_idx__plus);
  use_polymorphic_function(NULL, "second_of", &get__second_of, &poly_idx__second_of);
  use_read_only("std", "less", &get__std__less, &get_value_or_future__std__less);
  use_read_only("std", "minus", &get__std__minus, &get_value_or_future__std__minus);
  use_read_only("std", "over", &get__std__over, &get_value_or_future__std__over);
  use_read_only("std", "plus", &get__std__plus, &get_value_or_future__std__plus);
  use_read_only("std", "times", &get__std__times, &get_value_or_future__std__times);
  use_read_only(NULL, "string", &get__string, &get_value_or_future__string);
  use_polymorphic_function(NULL, "time_shift_of", &get__time_shift_of, &poly_idx__time_shift_of);
  use_polymorphic_function(NULL, "to_string", &get__to_string, &poly_idx__to_string);
  use_read_only(NULL, "true", &get__true, &get_value_or_future__true);
  use_read_only("types", "object", &get__types__object, &get_value_or_future__types__object);
  use_polymorphic_function(NULL, "year_of", &get__year_of, &poly_idx__year_of);
  define_method("types", "date_and_time", poly_idx__year_of, func__16_1);
  define_method("types", "date_and_time", poly_idx__month_of, func__17_1);
  define_method("types", "date_and_time", poly_idx__day_of, func__18_1);
  define_method("types", "date_and_time", poly_idx__day_of_week_of, func__19_1);
  define_method("types", "date_and_time", poly_idx__hour_of, func__20_1);
  define_method("types", "date_and_time", poly_idx__minute_of, func__21_1);
  define_method("types", "date_and_time", poly_idx__second_of, func__22_1);
  define_method("types", "date_and_time", poly_idx__plus, func__23_1);
  define_method("types", "date_and_time", poly_idx__minus, func__24_1);
  define_method("types", "date_and_time", poly_idx__equal, func__25_1);
  define_method("types", "date_and_time", poly_idx__less, func__26_1);
  define_method("types", "date_and_time", poly_idx__time_shift_of, func__27_1);
  define_method("types", "date_and_time", poly_idx__to_string, func__28_1);
}

static int already_run_phase_4 = false;

EXPORT void phase_4__basic__types__date_and_time(void) {
  if (already_run_phase_4) return;
  already_run_phase_4 = true;
  assign_value(&number__3600, from_uint32(3600U));
  assign_value(&number__0, from_uint32(0U));
  assign_value(&number__1000, from_uint32(1000U));
  assign_value(&number__3, from_uint32(3U));
  assign_value(&character__32, from_uchar32(32));
  assign_value(&character__46, from_uchar32(46));
  assign_value(&number__2, from_uint32(2U));
  assign_variable(&var.std__current_time, &func__1_1);
  assign_value(&var.std__year_of, create_function(type__std__year_of, -1));
  assign_value(&var.std__month_of, create_function(type__std__month_of, -1));
  assign_value(&var.std__day_of, create_function(type__std__day_of, -1));
  assign_value(&var.std__day_of_week_of, create_function(type__std__day_of_week_of, -1));
  assign_value(&var.std__hour_of, create_function(type__std__hour_of, -1));
  assign_value(&var.std__minute_of, create_function(type__std__minute_of, -1));
  assign_value(&var.std__second_of, create_function(type__std__second_of, -1));
  assign_value(&var.std__time_shift_of, create_function(type__std__time_shift_of, -1));
  assign_value(&var.types__date_and_time, get__types__object());
  assign_variable(&var.std__from_unix_time, &func__13_1);
  assign_variable(&var.std__date_and_time, &func__14_1);
  assign_variable(&var.std__sleep, &func__29_1);
}

static int already_run_phase_5 = false;

EXPORT void phase_5__basic__types__date_and_time(void) {
  if (already_run_phase_5) return;
  already_run_phase_5 = true;
  assign_value(&func__1_1, create_function(entry__1_1, 0));
  assign_value(&func__13_1, create_function(entry__13_1, 1));
  assign_value(&func__14_1, create_function(entry__14_1, 6));
  assign_value(&func__16_1, create_function(entry__16_1, 1));
  assign_value(&func__17_1, create_function(entry__17_1, 1));
  assign_value(&func__18_1, create_function(entry__18_1, 1));
  assign_value(&func__19_1, create_function(entry__19_1, 1));
  assign_value(&func__20_1, create_function(entry__20_1, 1));
  assign_value(&func__21_1, create_function(entry__21_1, 1));
  assign_value(&func__22_1, create_function(entry__22_1, 1));
  assign_value(&func__23_1, create_function(entry__23_1, 2));
  assign_value(&func__24_1, create_function(entry__24_1, 2));
  assign_value(&func__25_1, create_function(entry__25_1, 2));
  assign_value(&func__26_1, create_function(entry__26_1, 2));
  assign_value(&func__27_1, create_function(entry__27_1, 1));
  assign_value(&func__28_36, create_function(entry__28_36, 0));
  assign_value(&func__28_35, create_function(entry__28_35, 0));
  assign_value(&func__28_1, create_function(entry__28_1, 1));
  assign_value(&func__29_1, create_function(entry__29_1, 1));
  register_collector(collect__basic__types__date_and_time);
}
