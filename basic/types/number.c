/// link gmp
/// link m
#include <gmp.h>
#include <inttypes.h>
#include <math.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <runtime/platform.h>
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
REGISTER int argument_count ASM("ebx");
IMPORT void too_few_arguments_error(void);
REGISTER NODE *myself ASM("r13");
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
IMPORT void *allocate(long size);
IMPORT ATTRIBUTES *collect_attributes(ATTRIBUTES *attributes);
IMPORT void *copy(const void *buf, long size);
IMPORT void divide_by_zero_error(void);
IMPORT void not_yet_implemented_error(void);
IMPORT NODE *from_bool(int val);
IMPORT NODE *boolean_false;
IMPORT NODE *boolean_true;
IMPORT NODE *zero;
IMPORT NODE *from_uint32(uint32_t val);
IMPORT NODE *from_c_string(const char *str);
IMPORT int debug_print(int indent, char *buf, const char *format, ...);
IMPORT NODE *from_latin_1_string(const char *str, long len);
IMPORT int result_count;
IMPORT void invalid_results_error(void);
IMPORT NODE *create_continuation(void);
IMPORT NODE *create_cell(void);
IMPORT void too_many_arguments_error(void);
IMPORT NODE *create_cell_with_contents(NODE *contents);
IMPORT NODE *undefined;
typedef struct CELL {
  FUNC type;
  struct ATTRIBUTES *attributes;
  NODE *contents;
} CELL;
IMPORT NODE *create_closure(FUNC type, int par_count);
IMPORT NODE *empty_string;
IMPORT NODE *from_long(long val);
IMPORT NODE *collect_node(NODE *node);
IMPORT void collect_static_attributes(ATTRIBUTES *attributes);
IMPORT void register_module_info(MODULE_INFO *info);
IMPORT void define_c_function(const char *name, void *func);
IMPORT NODE *from_int(int val);
IMPORT NODE *from_int64(int64_t val);
IMPORT NODE *from_uint64(uint64_t val);
IMPORT NODE *from_digit_string(const char *str);
IMPORT NODE *from_double(double val);
IMPORT void set_module(const char *name);
IMPORT NODE *from_uchar32(unsigned int chr);
IMPORT void define_polymorphic_function(
  const char *namespace, const char *name, NODE_GETTER getter, int *id_p,
  NODE **var_p
);
IMPORT NODE *create_function(FUNC func, int par_count);
IMPORT void set_used_namespaces(const char **namespaces);
IMPORT NODE *create_future_with_prototype(NODE *prototype);
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
static int poly_idx__bit_and;
static NODE_GETTER get__bit_and;
static int poly_idx__bit_or;
static NODE_GETTER get__bit_or;
static int poly_idx__bit_xor;
static NODE_GETTER get__bit_xor;
static int poly_idx__ceil;
static NODE_GETTER get__ceil;
static int poly_idx__div;
static NODE_GETTER get__div;
static NODE_GETTER get__dup;
static NODE_GETTER get_value_or_future__dup;
static int poly_idx__equal;
static NODE_GETTER get__equal;
static int poly_idx__equal_type_and_value;
static NODE_GETTER get__equal_type_and_value;
static NODE_GETTER get__false;
static NODE_GETTER get_value_or_future__false;
static int poly_idx__floor;
static NODE_GETTER get__floor;
static int poly_idx__hash;
static NODE_GETTER get__hash;
static NODE_GETTER get__if;
static NODE_GETTER get_value_or_future__if;
static int poly_idx__is_a_number;
static NODE_GETTER get__is_a_number;
static int poly_idx__is_a_real;
static NODE_GETTER get__is_a_real;
static int poly_idx__is_an_integer;
static NODE_GETTER get__is_an_integer;
static NODE_GETTER get__is_defined;
static NODE_GETTER get_value_or_future__is_defined;
static int poly_idx__less;
static NODE_GETTER get__less;
static int poly_idx__ln;
static NODE_GETTER get__ln;
static int poly_idx__minus;
static NODE_GETTER get__minus;
static int poly_idx__mod;
static NODE_GETTER get__mod;
static int poly_idx__negate;
static NODE_GETTER get__negate;
static int poly_idx__over;
static NODE_GETTER get__over;
static NODE_GETTER get__pad_left;
static NODE_GETTER get_value_or_future__pad_left;
static int poly_idx__plus;
static NODE_GETTER get__plus;
static NODE_GETTER get__put;
static NODE_GETTER get_value_or_future__put;
static int poly_idx__round;
static NODE_GETTER get__round;
static int poly_idx__shift_left;
static NODE_GETTER get__shift_left;
static int poly_idx__shift_right;
static NODE_GETTER get__shift_right;
static NODE_GETTER get__std__bit_and;
static NODE_GETTER get_value_or_future__std__bit_and;
static NODE_GETTER get__std__equal;
static NODE_GETTER get_value_or_future__std__equal;
static NODE_GETTER get__std__less;
static NODE_GETTER get_value_or_future__std__less;
static NODE_GETTER get__std__minus;
static NODE_GETTER get_value_or_future__std__minus;
static NODE_GETTER get__std__not;
static NODE_GETTER get_value_or_future__std__not;
static NODE_GETTER get__std__plus;
static NODE_GETTER get_value_or_future__std__plus;
static NODE_GETTER get__std__shift_right;
static NODE_GETTER get_value_or_future__std__shift_right;
static int poly_idx__times;
static NODE_GETTER get__times;
static int poly_idx__to_integer;
static NODE_GETTER get__to_integer;
static int poly_idx__to_string;
static NODE_GETTER get__to_string;
static NODE_GETTER get__true;
static NODE_GETTER get_value_or_future__true;
static NODE_GETTER get__types__object;
static NODE_GETTER get_value_or_future__types__object;
static NODE_GETTER get__while;
static NODE_GETTER get_value_or_future__while;
static struct {
  NODE *std__integer_plus_me;
  NODE *std__integer_minus_me;
  NODE *std__integer_times_me;
  NODE *std__integer_over_me;
  NODE *std__real_plus_me;
  NODE *std__real_minus_me;
  NODE *std__real_times_me;
  NODE *std__real_over_me;
  NODE *std__is_a_number;
  NODE *std__is_an_integer;
  NODE *std__is_a_real;
  NODE *std__floor;
  NODE *std__ceil;
  NODE *std__round;
  NODE *std__ln;
  NODE *types__number;
  NODE *types__integer;
  NODE *types__positive_integer;
  NODE *std__zero;
  NODE *types__negative_integer;
  NODE *types__positive_large_integer;
  NODE *types__negative_large_integer;
  NODE *types__real;
  NODE *std__is_odd;
  NODE *std__is_even;
  NODE *std__bin;
  NODE *std__oct;
  NODE *std__hex;
} var;
static const char *var_names[] = {
};
static int poly_idx__std__integer_plus_me;
static void type__std__integer_plus_me(void);
static NODE *get__std__integer_plus_me(void) {
  return var.std__integer_plus_me;
}
static int poly_idx__std__integer_minus_me;
static void type__std__integer_minus_me(void);
static NODE *get__std__integer_minus_me(void) {
  return var.std__integer_minus_me;
}
static int poly_idx__std__integer_times_me;
static void type__std__integer_times_me(void);
static NODE *get__std__integer_times_me(void) {
  return var.std__integer_times_me;
}
static int poly_idx__std__integer_over_me;
static void type__std__integer_over_me(void);
static NODE *get__std__integer_over_me(void) {
  return var.std__integer_over_me;
}
static int poly_idx__std__real_plus_me;
static void type__std__real_plus_me(void);
static NODE *get__std__real_plus_me(void) {
  return var.std__real_plus_me;
}
static int poly_idx__std__real_minus_me;
static void type__std__real_minus_me(void);
static NODE *get__std__real_minus_me(void) {
  return var.std__real_minus_me;
}
static int poly_idx__std__real_times_me;
static void type__std__real_times_me(void);
static NODE *get__std__real_times_me(void) {
  return var.std__real_times_me;
}
static int poly_idx__std__real_over_me;
static void type__std__real_over_me(void);
static NODE *get__std__real_over_me(void) {
  return var.std__real_over_me;
}
static int poly_idx__std__is_a_number;
static void type__std__is_a_number(void);
static NODE *get__std__is_a_number(void) {
  return var.std__is_a_number;
}
static int poly_idx__std__is_an_integer;
static void type__std__is_an_integer(void);
static NODE *get__std__is_an_integer(void) {
  return var.std__is_an_integer;
}
static int poly_idx__std__is_a_real;
static void type__std__is_a_real(void);
static NODE *get__std__is_a_real(void) {
  return var.std__is_a_real;
}
static int poly_idx__std__floor;
static void type__std__floor(void);
static NODE *get__std__floor(void) {
  return var.std__floor;
}
static int poly_idx__std__ceil;
static void type__std__ceil(void);
static NODE *get__std__ceil(void) {
  return var.std__ceil;
}
static int poly_idx__std__round;
static void type__std__round(void);
static NODE *get__std__round(void) {
  return var.std__round;
}
static int poly_idx__std__ln;
static void type__std__ln(void);
static NODE *get__std__ln(void) {
  return var.std__ln;
}
static NODE *get__types__number(void) {
  return var.types__number;
}
static NODE *create__types__number();
static NODE *get__types__integer(void) {
  return var.types__integer;
}
static NODE *create__types__integer();

typedef struct {
  void *type;
  ATTRIBUTES *attributes;
  uint64_t value;
} INTEGER;

typedef struct LARGE_INTEGER_DATA LARGE_INTEGER_DATA;
struct LARGE_INTEGER_DATA {
  long size;
  mp_limb_t limbs[0];
};

static LARGE_INTEGER_DATA *collect_large_integer_data(LARGE_INTEGER_DATA *data);

typedef struct {
  void *type;
  ATTRIBUTES *attributes;
  LARGE_INTEGER_DATA *data;
} LARGE_INTEGER;

typedef struct {
  void *type;
  ATTRIBUTES *attributes;
  double value;
} REAL;

#define mpn_get_d __MPN(get_d)
extern double mpn_get_d(mp_srcptr up, mp_size_t size, mp_size_t sign, long exp);

#if GMP_LIMB_BITS == 32
  #define LIMBS_PER_INT64 2
  #define INTEGER_TO_LARGE_INTEGER(value, limbs, size) \
    size = ((value) >> 32 ? 2 : 1); \
    limbs = (mp_limb_t *)&(value);
#else
  #define LIMBS_PER_INT64 1
  #define INTEGER_TO_LARGE_INTEGER(value, limbs, size) \
    size = 1; \
    limbs = (mp_limb_t *)&(value);
#endif
static NODE *get__types__positive_integer(void) {
  return var.types__positive_integer;
}
extern NODE *create__types__positive_integer(uint64_t value);
static NODE *get__std__zero(void) {
  return var.std__zero;
}
static NODE *get__types__negative_integer(void) {
  return var.types__negative_integer;
}

static NODE *create__types__negative_integer(uint64_t value);
static NODE *get__types__positive_large_integer(void) {
  return var.types__positive_large_integer;
}
static NODE *create__types__positive_large_integer(LARGE_INTEGER_DATA *data);
static NODE *get__types__negative_large_integer(void) {
  return var.types__negative_large_integer;
}
static NODE *create__types__negative_large_integer(LARGE_INTEGER_DATA *data);
static NODE *get__types__real(void) {
  return var.types__real;
}
static NODE *create__types__real(double value);

static NODE *from_uint8(char value);

static int func__types__positive_integer___to_int(NODE *node);

static int func__types__negative_integer___to_int(NODE *node);

static uint8_t func__types__positive_integer___to_uint8(NODE *node);

static uint32_t func__types__positive_integer___to_uint32(NODE *node);

static uint64_t func__types__positive_integer___to_uint64(NODE *node);

static long func__types__positive_integer___to_long(NODE *node);

static long func__types__negative_integer___to_long(NODE *node);

static double func__types__positive_integer___to_double(NODE *node);

static double func__types__negative_integer___to_double(NODE *node);

static double func__types__positive_large_integer___to_double(NODE *node);

static double func__types__negative_large_integer___to_double(NODE *node);

static double func__types__real___to_double(NODE *node);
static void entry__types__positive_integer__negate_1(void);
static NODE *func__types__positive_integer__negate_1;
static void entry__types__negative_integer__negate_1(void);
static NODE *func__types__negative_integer__negate_1;
static void entry__types__positive_large_integer__negate_1(void);
static NODE *func__types__positive_large_integer__negate_1;
static void entry__types__negative_large_integer__negate_1(void);
static NODE *func__types__negative_large_integer__negate_1;
static void entry__types__real__negate_1(void);
static NODE *func__types__real__negate_1;

static NODE *positive_integer_sum(void);

static NODE *negative_integer_sum(void);

static NODE *integer_difference(uint64_t left_integer, uint64_t right_integer);
static void entry__types__positive_integer__plus_1(void);
static NODE *func__types__positive_integer__plus_1;
static void entry__types__positive_integer__minus_1(void);
static NODE *func__types__positive_integer__minus_1;
static void entry__types__negative_integer__plus_1(void);
static NODE *func__types__negative_integer__plus_1;
static void entry__types__negative_integer__minus_1(void);
static NODE *func__types__negative_integer__minus_1;

static NODE *large_integer_sum(
  mp_limb_t *left_limbs, long left_size,
  mp_limb_t *right_limbs, long right_size,
  int sign
);

static NODE *large_difference(
  mp_limb_t *left_limbs, long left_size,
  mp_limb_t *right_limbs, long right_size,
  int sign
);
static void entry__types__positive_large_integer__plus_1(void);
static NODE *func__types__positive_large_integer__plus_1;
static void entry__types__positive_large_integer__minus_1(void);
static NODE *func__types__positive_large_integer__minus_1;
static void entry__types__negative_large_integer__plus_1(void);
static NODE *func__types__negative_large_integer__plus_1;
static void entry__types__negative_large_integer__minus_1(void);
static NODE *func__types__negative_large_integer__minus_1;
static void entry__types__real__plus_1(void);
static NODE *func__types__real__plus_1;
static void entry__types__real__minus_1(void);
static NODE *func__types__real__minus_1;

static NODE *integer_product(int sign);
static void entry__types__positive_integer__times_1(void);
static NODE *func__types__positive_integer__times_1;
static void entry__types__negative_integer__times_1(void);
static NODE *func__types__negative_integer__times_1;

static NODE *large_integer_product(
  mp_limb_t *left_limbs, long left_size,
  mp_limb_t *right_limbs, long right_size,
  int sign
);
static void entry__types__positive_large_integer__times_1(void);
static NODE *func__types__positive_large_integer__times_1;
static void entry__types__negative_large_integer__times_1(void);
static NODE *func__types__negative_large_integer__times_1;
static void entry__types__real__times_1(void);
static NODE *func__types__real__times_1;

static NODE *integer_quotient(int sign);
static void entry__types__positive_integer__over_1(void);
static NODE *func__types__positive_integer__over_1;
static void entry__types__negative_integer__over_1(void);
static NODE *func__types__negative_integer__over_1;

static NODE *large_integer_quotient(
  mp_limb_t *left_limbs, long left_size,
  mp_limb_t *right_limbs, long right_size,
  int sign
);
static void entry__types__positive_large_integer__over_1(void);
static NODE *func__types__positive_large_integer__over_1;
static void entry__types__negative_large_integer__over_1(void);
static NODE *func__types__negative_large_integer__over_1;
static void entry__types__real__over_1(void);
static NODE *func__types__real__over_1;
static void entry__types__positive_integer__div_1(void);
static NODE *func__types__positive_integer__div_1;
static void entry__types__positive_integer__mod_1(void);
static NODE *func__types__positive_integer__mod_1;
static void entry__types__positive_integer__equal_1(void);
static NODE *func__types__positive_integer__equal_1;
static void entry__types__positive_integer__equal_type_and_value_1(void);
static NODE *func__types__positive_integer__equal_type_and_value_1;
static void entry__types__negative_integer__equal_1(void);
static NODE *func__types__negative_integer__equal_1;
static void entry__types__negative_integer__equal_type_and_value_1(void);
static NODE *func__types__negative_integer__equal_type_and_value_1;
static void entry__types__positive_large_integer__equal_1(void);
static NODE *func__types__positive_large_integer__equal_1;
static void entry__types__positive_large_integer__equal_type_and_value_1(void);
static NODE *func__types__positive_large_integer__equal_type_and_value_1;
static void entry__types__negative_large_integer__equal_1(void);
static NODE *func__types__negative_large_integer__equal_1;
static void entry__types__negative_large_integer__equal_type_and_value_1(void);
static NODE *func__types__negative_large_integer__equal_type_and_value_1;
static void entry__types__real__equal_1(void);
static NODE *func__types__real__equal_1;
static void entry__types__real__equal_type_and_value_1(void);
static NODE *func__types__real__equal_type_and_value_1;
static void entry__types__positive_integer__less_1(void);
static NODE *func__types__positive_integer__less_1;
static void entry__types__negative_integer__less_1(void);
static NODE *func__types__negative_integer__less_1;
static void entry__types__positive_large_integer__less_1(void);
static NODE *func__types__positive_large_integer__less_1;
static void entry__types__negative_large_integer__less_1(void);
static NODE *func__types__negative_large_integer__less_1;
static void entry__types__real__less_1(void);
static NODE *func__types__real__less_1;

static mp_limb_t lshift(
  mp_limb_t *rp, const mp_limb_t *src_ptr,
  mp_size_t src_size, unsigned long int count
);

static mp_limb_t rshift(
  mp_limb_t *rp, const mp_limb_t *src_ptr,
  mp_size_t src_size, unsigned long int count
);
static void entry__types__positive_integer__shift_left_1(void);
static NODE *func__types__positive_integer__shift_left_1;
static void entry__types__positive_large_integer__shift_left_1(void);
static NODE *func__types__positive_large_integer__shift_left_1;
static void entry__types__positive_integer__shift_right_1(void);
static NODE *func__types__positive_integer__shift_right_1;
static void entry__types__positive_large_integer__shift_right_1(void);
static NODE *func__types__positive_large_integer__shift_right_1;
static void entry__types__positive_integer__bit_or_1(void);
static NODE *func__types__positive_integer__bit_or_1;
static void entry__types__positive_integer__bit_and_1(void);
static NODE *func__types__positive_integer__bit_and_1;
static void entry__types__positive_integer__bit_xor_1(void);
static NODE *func__types__positive_integer__bit_xor_1;
static void entry__types__positive_integer__hash_1(void);
static NODE *func__types__positive_integer__hash_1;
static void entry__types__negative_integer__hash_1(void);
static NODE *func__types__negative_integer__hash_1;
static void entry__types__positive_integer__to_string_1(void);
static NODE *func__types__positive_integer__to_string_1;

static long func__types__positive_integer___debug_string(NODE *node, int indent, int max_depth, char *buf);
static void entry__types__negative_integer__to_string_1(void);
static NODE *func__types__negative_integer__to_string_1;

static long func__types__negative_integer___debug_string(NODE *node, int indent, int max_depth, char *buf);

static NODE *large_integer_to_string(int sign);
static void entry__types__positive_large_integer__to_string_1(void);
static NODE *func__types__positive_large_integer__to_string_1;

static long func__types__positive_large_integer___debug_string(NODE *node, int indent, int max_depth, char *buf);
static void entry__types__negative_large_integer__to_string_1(void);
static NODE *func__types__negative_large_integer__to_string_1;

static long func__types__negetive_large_integer___debug_string(NODE *node, int indent, int max_depth, char *buf);
static void entry__types__real__to_string_1(void);
static NODE *func__types__real__to_string_1;

static long func__types__real___debug_string(NODE *node, int indent, int max_depth, char *buf);
static NODE *func__std__is_odd_1;
static void entry__std__is_odd_1(void);
static FRAME_INFO frame__std__is_odd_1 = {1, {"n"}};
static void cont__std__is_odd_2(void);
static void cont__std__is_odd_3(void);
static NODE *get__std__is_odd(void) {
  return var.std__is_odd;
}
static NODE *func__std__is_even_1;
static void entry__std__is_even_1(void);
static FRAME_INFO frame__std__is_even_1 = {1, {"n"}};
static void cont__std__is_even_2(void);
static void cont__std__is_even_3(void);
static NODE *get__std__is_even(void) {
  return var.std__is_even;
}
static NODE *func__std__bin_1;
static void entry__std__bin_1(void);
static FRAME_INFO frame__std__bin_1 = {4, {"val", "size", "return", "str"}};
static void cont__std__bin_2(void);
static NODE *func__std__bin_3;
static void entry__std__bin_3(void);
static FRAME_INFO frame__std__bin_3 = {2, {"size", "return"}};
static void cont__std__bin_4(void);
static NODE *func__std__bin_5;
static void entry__std__bin_5(void);
static FRAME_INFO frame__std__bin_5 = {2, {"return", "size"}};
static NODE *string__578a5af303e9cd1;
static void cont__std__bin_7(void);
static NODE *func__std__bin_8;
static void entry__std__bin_8(void);
static FRAME_INFO frame__std__bin_8 = {1, {"return"}};
static void cont__std__bin_9(void);
static NODE *func__std__bin_10;
static void entry__std__bin_10(void);
static FRAME_INFO frame__std__bin_10 = {2, {"val", "str"}};
static void cont__std__bin_11(void);
static NODE *func__std__bin_12;
static void entry__std__bin_12(void);
static FRAME_INFO frame__std__bin_12 = {2, {"str", "val"}};
static void cont__std__bin_13(void);
static void cont__std__bin_14(void);
static void cont__std__bin_15(void);
static void cont__std__bin_16(void);
static void cont__std__bin_17(void);
static void cont__std__bin_18(void);
static NODE *func__std__bin_19;
static void entry__std__bin_19(void);
static FRAME_INFO frame__std__bin_19 = {3, {"return", "str", "size"}};
static void cont__std__bin_20(void);
static void cont__std__bin_21(void);
static NODE *get__std__bin(void) {
  return var.std__bin;
}
static NODE *func__std__oct_1;
static void entry__std__oct_1(void);
static FRAME_INFO frame__std__oct_1 = {4, {"val", "size", "return", "str"}};
static void cont__std__oct_2(void);
static NODE *func__std__oct_3;
static void entry__std__oct_3(void);
static FRAME_INFO frame__std__oct_3 = {2, {"size", "return"}};
static void cont__std__oct_4(void);
static NODE *func__std__oct_5;
static void entry__std__oct_5(void);
static FRAME_INFO frame__std__oct_5 = {2, {"return", "size"}};
static void cont__std__oct_6(void);
static NODE *func__std__oct_7;
static void entry__std__oct_7(void);
static FRAME_INFO frame__std__oct_7 = {1, {"return"}};
static void cont__std__oct_8(void);
static NODE *func__std__oct_9;
static void entry__std__oct_9(void);
static FRAME_INFO frame__std__oct_9 = {2, {"val", "str"}};
static void cont__std__oct_10(void);
static NODE *func__std__oct_11;
static void entry__std__oct_11(void);
static FRAME_INFO frame__std__oct_11 = {2, {"str", "val"}};
static void cont__std__oct_12(void);
static void cont__std__oct_13(void);
static void cont__std__oct_14(void);
static void cont__std__oct_15(void);
static void cont__std__oct_16(void);
static void cont__std__oct_17(void);
static NODE *func__std__oct_18;
static void entry__std__oct_18(void);
static FRAME_INFO frame__std__oct_18 = {3, {"return", "str", "size"}};
static void cont__std__oct_19(void);
static void cont__std__oct_20(void);
static NODE *get__std__oct(void) {
  return var.std__oct;
}
static NODE *func__std__hex_1;
static void entry__std__hex_1(void);
static FRAME_INFO frame__std__hex_1 = {4, {"val", "size", "return", "str"}};
static void cont__std__hex_2(void);
static NODE *func__std__hex_3;
static void entry__std__hex_3(void);
static FRAME_INFO frame__std__hex_3 = {2, {"size", "return"}};
static void cont__std__hex_4(void);
static NODE *func__std__hex_5;
static void entry__std__hex_5(void);
static FRAME_INFO frame__std__hex_5 = {2, {"return", "size"}};
static void cont__std__hex_6(void);
static NODE *func__std__hex_7;
static void entry__std__hex_7(void);
static FRAME_INFO frame__std__hex_7 = {1, {"return"}};
static void cont__std__hex_8(void);
static NODE *func__std__hex_9;
static void entry__std__hex_9(void);
static FRAME_INFO frame__std__hex_9 = {2, {"val", "str"}};
static void cont__std__hex_10(void);
static NODE *func__std__hex_11;
static void entry__std__hex_11(void);
static FRAME_INFO frame__std__hex_11 = {3, {"val", "str", "hex_digit"}};
static void cont__std__hex_12(void);
static void cont__std__hex_13(void);
static void cont__std__hex_14(void);
static NODE *func__std__hex_15;
static void entry__std__hex_15(void);
static FRAME_INFO frame__std__hex_15 = {1, {"hex_digit"}};
static void cont__std__hex_16(void);
static void cont__std__hex_17(void);
static NODE *func__std__hex_18;
static void entry__std__hex_18(void);
static FRAME_INFO frame__std__hex_18 = {1, {"hex_digit"}};
static void cont__std__hex_19(void);
static void cont__std__hex_20(void);
static void cont__std__hex_21(void);
static void cont__std__hex_22(void);
static void cont__std__hex_23(void);
static void cont__std__hex_24(void);
static NODE *func__std__hex_25;
static void entry__std__hex_25(void);
static FRAME_INFO frame__std__hex_25 = {3, {"return", "str", "size"}};
static void cont__std__hex_26(void);
static void cont__std__hex_27(void);
static NODE *get__std__hex(void) {
  return var.std__hex;
}
static NODE *func__types__integer__to_integer_1;
static void entry__types__integer__to_integer_1(void);
static FRAME_INFO frame__types__integer__to_integer_1 = {1, {"value"}};
static void entry__types__real__to_integer_1(void);
static NODE *func__types__real__to_integer_1;
static NODE *func__types__number__floor_1;
static void entry__types__number__floor_1(void);
static FRAME_INFO frame__types__number__floor_1 = {1, {"self"}};
static NODE *func__types__number__ceil_1;
static void entry__types__number__ceil_1(void);
static FRAME_INFO frame__types__number__ceil_1 = {1, {"self"}};
static NODE *func__types__number__round_1;
static void entry__types__number__round_1(void);
static FRAME_INFO frame__types__number__round_1 = {1, {"self"}};
static void entry__types__real__floor_1(void);
static NODE *func__types__real__floor_1;
static void entry__types__real__ceil_1(void);
static NODE *func__types__real__ceil_1;
static void entry__types__real__round_1(void);
static NODE *func__types__real__round_1;
static void entry__types__real__ln_1(void);
static NODE *func__types__real__ln_1;
void run__basic__types__number(void);

static CONTINUATION_INFO continuation_info[] = {
  {type__std__integer_plus_me, NULL, 48, 48, 2, 21},
  {type__std__integer_minus_me, NULL, 49, 49, 2, 22},
  {type__std__integer_times_me, NULL, 50, 50, 2, 22},
  {type__std__integer_over_me, NULL, 51, 51, 2, 21},
  {type__std__real_plus_me, NULL, 52, 52, 2, 18},
  {type__std__real_minus_me, NULL, 53, 53, 2, 19},
  {type__std__real_times_me, NULL, 54, 54, 2, 19},
  {type__std__real_over_me, NULL, 55, 55, 2, 18},
  {type__std__is_a_number, NULL, 56, 56, 2, 17},
  {type__std__is_an_integer, NULL, 57, 57, 2, 19},
  {type__std__is_a_real, NULL, 58, 58, 2, 15},
  {type__std__floor, NULL, 60, 60, 2, 11},
  {type__std__ceil, NULL, 68, 68, 2, 10},
  {type__std__round, NULL, 76, 76, 2, 11},
  {type__std__ln, NULL, 84, 84, 2, 8},
  {run__basic__types__number, NULL, },
  {entry__types__positive_integer__negate_1, NULL, 497, 502, 3, 2},
  {entry__types__negative_integer__negate_1, NULL, 507, 511, 3, 2},
  {entry__types__positive_large_integer__negate_1, NULL, 516, 520, 3, 2},
  {entry__types__negative_large_integer__negate_1, NULL, 525, 529, 3, 2},
  {entry__types__real__negate_1, NULL, 534, 537, 3, 2},
  {entry__types__positive_integer__plus_1, NULL, 597, 624, 3, 2},
  {entry__types__positive_integer__minus_1, NULL, 629, 656, 3, 2},
  {entry__types__negative_integer__plus_1, NULL, 661, 688, 3, 2},
  {entry__types__negative_integer__minus_1, NULL, 693, 720, 3, 2},
  {entry__types__positive_large_integer__plus_1, NULL, 796, 832, 3, 2},
  {entry__types__positive_large_integer__minus_1, NULL, 837, 873, 3, 2},
  {entry__types__negative_large_integer__plus_1, NULL, 878, 914, 3, 2},
  {entry__types__negative_large_integer__minus_1, NULL, 919, 955, 3, 2},
  {entry__types__real__plus_1, NULL, 960, 987, 3, 2},
  {entry__types__real__minus_1, NULL, 992, 1019, 3, 2},
  {entry__types__positive_integer__times_1, NULL, 1062, 1087, 3, 2},
  {entry__types__negative_integer__times_1, NULL, 1092, 1117, 3, 2},
  {entry__types__positive_large_integer__times_1, NULL, 1152, 1188, 3, 2},
  {entry__types__negative_large_integer__times_1, NULL, 1193, 1229, 3, 2},
  {entry__types__real__times_1, NULL, 1234, 1259, 3, 2},
  {entry__types__positive_integer__over_1, NULL, 1281, 1304, 3, 2},
  {entry__types__negative_integer__over_1, NULL, 1309, 1332, 3, 2},
  {entry__types__positive_large_integer__over_1, NULL, 1382, 1418, 3, 2},
  {entry__types__negative_large_integer__over_1, NULL, 1423, 1459, 3, 2},
  {entry__types__real__over_1, NULL, 1464, 1489, 3, 2},
  {entry__types__positive_integer__div_1, NULL, 1494, 1502, 3, 2},
  {entry__types__positive_integer__mod_1, NULL, 1507, 1515, 3, 2},
  {entry__types__positive_integer__equal_1, NULL, 1523, 1531, 3, 2},
  {entry__types__positive_integer__equal_type_and_value_1, NULL, 1539, 1545, 3, 2},
  {entry__types__negative_integer__equal_1, NULL, 1553, 1561, 3, 2},
  {entry__types__negative_integer__equal_type_and_value_1, NULL, 1569, 1575, 3, 2},
  {entry__types__positive_large_integer__equal_1, NULL, 1583, 1601, 3, 2},
  {entry__types__positive_large_integer__equal_type_and_value_1, NULL, 1609, 1622, 3, 2},
  {entry__types__negative_large_integer__equal_1, NULL, 1630, 1648, 3, 2},
  {entry__types__negative_large_integer__equal_type_and_value_1, NULL, 1656, 1669, 3, 2},
  {entry__types__real__equal_1, NULL, 1677, 1697, 3, 2},
  {entry__types__real__equal_type_and_value_1, NULL, 1705, 1711, 3, 2},
  {entry__types__positive_integer__less_1, NULL, 1716, 1732, 3, 2},
  {entry__types__negative_integer__less_1, NULL, 1737, 1753, 3, 2},
  {entry__types__positive_large_integer__less_1, NULL, 1758, 1783, 3, 2},
  {entry__types__negative_large_integer__less_1, NULL, 1788, 1813, 3, 2},
  {entry__types__real__less_1, NULL, 1818, 1838, 3, 2},
  {entry__types__positive_integer__shift_left_1, NULL, 1871, 1912, 3, 2},
  {entry__types__positive_large_integer__shift_left_1, NULL, 1919, 1942, 3, 2},
  {entry__types__positive_integer__shift_right_1, NULL, 1949, 1955, 3, 2},
  {entry__types__positive_large_integer__shift_right_1, NULL, 1962, 2000, 3, 2},
  {entry__types__positive_integer__bit_or_1, NULL, 2007, 2015, 3, 2},
  {entry__types__positive_integer__bit_and_1, NULL, 2022, 2030, 3, 2},
  {entry__types__positive_integer__bit_xor_1, NULL, 2037, 2045, 3, 2},
  {entry__types__positive_integer__hash_1, NULL, 2050, 2059, 3, 2},
  {entry__types__negative_integer__hash_1, NULL, 2064, 2073, 3, 2},
  {entry__types__positive_integer__to_string_1, NULL, 2078, 2083, 3, 2},
  {entry__types__negative_integer__to_string_1, NULL, 2096, 2101, 3, 2},
  {entry__types__positive_large_integer__to_string_1, NULL, 2142, 2145, 3, 2},
  {entry__types__negative_large_integer__to_string_1, NULL, 2158, 2161, 3, 2},
  {entry__types__real__to_string_1, NULL, 2174, 2179, 3, 2},
  {entry__std__is_odd_1, NULL, 2195, 2195, 6, 10},
  {cont__std__is_odd_2, &frame__std__is_odd_1, 2195, 2195, 6, 15},
  {cont__std__is_odd_3, &frame__std__is_odd_1, 2195, 2195, 3, 15},
  {entry__std__is_even_1, NULL, 2203, 2203, 6, 10},
  {cont__std__is_even_2, &frame__std__is_even_1, 2203, 2203, 6, 15},
  {cont__std__is_even_3, &frame__std__is_even_1, 2203, 2203, 3, 15},
  {entry__std__bin_5, NULL, 2223, 2223, 16, 28},
  {cont__std__bin_7, &frame__std__bin_5, 2223, 2223, 9, 28},
  {entry__std__bin_8, NULL, 2225, 2225, 9, 18},
  {entry__std__bin_3, NULL, 2222, 2222, 7, 21},
  {cont__std__bin_4, &frame__std__bin_3, 2221, 2225, 5, 19},
  {entry__std__bin_12, NULL, 2228, 2228, 19, 25},
  {cont__std__bin_13, &frame__std__bin_12, 2228, 2228, 14, 25},
  {cont__std__bin_14, &frame__std__bin_12, 2228, 2228, 5, 26},
  {cont__std__bin_15, &frame__std__bin_12, 2229, 2229, 5, 17},
  {cont__std__bin_16, &frame__std__bin_12, 2229, 2229, 17, 17},
  {entry__std__bin_10, NULL, 2227, 2227, 12, 18},
  {cont__std__bin_11, &frame__std__bin_10, 2227, 2229, 9, 17},
  {entry__std__bin_19, NULL, 2230, 2230, 30, 51},
  {cont__std__bin_20, &frame__std__bin_19, 2230, 2230, 23, 51},
  {entry__std__bin_1, NULL, 2220, 2220, 6, 13},
  {cont__std__bin_2, &frame__std__bin_1, 2220, 2225, 3, 20},
  {cont__std__bin_9, &frame__std__bin_1, 2227, 2229, 3, 17},
  {cont__std__bin_17, &frame__std__bin_1, 2230, 2230, 6, 20},
  {cont__std__bin_18, &frame__std__bin_1, 2230, 2230, 3, 51},
  {cont__std__bin_21, &frame__std__bin_1, 2231, 2231, 3, 8},
  {entry__std__oct_5, NULL, 2251, 2251, 16, 28},
  {cont__std__oct_6, &frame__std__oct_5, 2251, 2251, 9, 28},
  {entry__std__oct_7, NULL, 2253, 2253, 9, 18},
  {entry__std__oct_3, NULL, 2250, 2250, 7, 21},
  {cont__std__oct_4, &frame__std__oct_3, 2249, 2253, 5, 19},
  {entry__std__oct_11, NULL, 2256, 2256, 19, 28},
  {cont__std__oct_12, &frame__std__oct_11, 2256, 2256, 14, 28},
  {cont__std__oct_13, &frame__std__oct_11, 2256, 2256, 5, 29},
  {cont__std__oct_14, &frame__std__oct_11, 2257, 2257, 5, 17},
  {cont__std__oct_15, &frame__std__oct_11, 2257, 2257, 17, 17},
  {entry__std__oct_9, NULL, 2255, 2255, 12, 18},
  {cont__std__oct_10, &frame__std__oct_9, 2255, 2257, 9, 17},
  {entry__std__oct_18, NULL, 2258, 2258, 30, 51},
  {cont__std__oct_19, &frame__std__oct_18, 2258, 2258, 23, 51},
  {entry__std__oct_1, NULL, 2248, 2248, 6, 13},
  {cont__std__oct_2, &frame__std__oct_1, 2248, 2253, 3, 20},
  {cont__std__oct_8, &frame__std__oct_1, 2255, 2257, 3, 17},
  {cont__std__oct_16, &frame__std__oct_1, 2258, 2258, 6, 20},
  {cont__std__oct_17, &frame__std__oct_1, 2258, 2258, 3, 51},
  {cont__std__oct_20, &frame__std__oct_1, 2259, 2259, 3, 8},
  {entry__std__hex_5, NULL, 2279, 2279, 16, 28},
  {cont__std__hex_6, &frame__std__hex_5, 2279, 2279, 9, 28},
  {entry__std__hex_7, NULL, 2281, 2281, 9, 18},
  {entry__std__hex_3, NULL, 2278, 2278, 7, 21},
  {cont__std__hex_4, &frame__std__hex_3, 2277, 2281, 5, 19},
  {entry__std__hex_15, NULL, 2287, 2287, 20, 32},
  {cont__std__hex_16, &frame__std__hex_15, 2287, 2287, 9, 35},
  {cont__std__hex_17, &frame__std__hex_15, 2287, 2287, 35, 35},
  {entry__std__hex_18, NULL, 2289, 2289, 9, 32},
  {cont__std__hex_19, &frame__std__hex_18, 2289, 2289, 32, 32},
  {entry__std__hex_11, NULL, 2284, 2284, 5, 26},
  {cont__std__hex_12, &frame__std__hex_11, 2286, 2286, 7, 21},
  {cont__std__hex_13, &frame__std__hex_11, 2286, 2286, 7, 21},
  {cont__std__hex_14, &frame__std__hex_11, 2285, 2289, 5, 33},
  {cont__std__hex_20, &frame__std__hex_11, 2290, 2290, 5, 22},
  {cont__std__hex_21, &frame__std__hex_11, 2291, 2291, 5, 17},
  {cont__std__hex_22, &frame__std__hex_11, 2291, 2291, 17, 17},
  {entry__std__hex_9, NULL, 2283, 2283, 12, 18},
  {cont__std__hex_10, &frame__std__hex_9, 2283, 2291, 9, 17},
  {entry__std__hex_25, NULL, 2292, 2292, 30, 51},
  {cont__std__hex_26, &frame__std__hex_25, 2292, 2292, 23, 51},
  {entry__std__hex_1, NULL, 2276, 2276, 6, 13},
  {cont__std__hex_2, &frame__std__hex_1, 2276, 2281, 3, 20},
  {cont__std__hex_8, &frame__std__hex_1, 2283, 2291, 3, 17},
  {cont__std__hex_23, &frame__std__hex_1, 2292, 2292, 6, 20},
  {cont__std__hex_24, &frame__std__hex_1, 2292, 2292, 3, 51},
  {cont__std__hex_27, &frame__std__hex_1, 2293, 2293, 3, 8},
  {entry__types__integer__to_integer_1, NULL, 2301, 2301, 3, 10},
  {entry__types__real__to_integer_1, NULL, 2306, 2310, 3, 2},
  {entry__types__number__floor_1, NULL, 2318, 2318, 3, 9},
  {entry__types__number__ceil_1, NULL, 2326, 2326, 3, 9},
  {entry__types__number__round_1, NULL, 2334, 2334, 3, 9},
  {entry__types__real__floor_1, NULL, 2339, 2342, 3, 2},
  {entry__types__real__ceil_1, NULL, 2347, 2350, 3, 2},
  {entry__types__real__round_1, NULL, 2355, 2358, 3, 2},
  {entry__types__real__ln_1, NULL, 2363, 2366, 3, 2}
};

union NODE {
  struct {
    FUNC type;
    ATTRIBUTES *attributes;
  };
  CONTINUATION continuation;
  CLOSURE closure;
  LARGE_INTEGER large_integer;
  INTEGER integer;
  SIMPLE_NODE simple_node;
  REAL real;
};
static void type__std__integer_plus_me(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__std__integer_plus_me);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__integer_plus_me, attr);
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
static void type__std__integer_minus_me(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__std__integer_minus_me);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__integer_minus_me, attr);
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
static void type__std__integer_times_me(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__std__integer_times_me);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__integer_times_me, attr);
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
static void type__std__integer_over_me(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__std__integer_over_me);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__integer_over_me, attr);
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
static void type__std__real_plus_me(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__std__real_plus_me);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__real_plus_me, attr);
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
static void type__std__real_minus_me(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__std__real_minus_me);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__real_minus_me, attr);
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
static void type__std__real_times_me(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__std__real_times_me);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__real_times_me, attr);
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
static void type__std__real_over_me(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__std__real_over_me);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__real_over_me, attr);
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
static void type__std__is_a_number(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__std__is_a_number);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__is_a_number, attr);
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
static void type__std__is_an_integer(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__std__is_an_integer);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__is_an_integer, attr);
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
static void type__std__is_a_real(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__std__is_a_real);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__is_a_real, attr);
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
static void type__std__floor(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__std__floor);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__floor, attr);
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
static void type__std__ceil(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__std__ceil);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__ceil, attr);
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
static void type__std__round(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__std__round);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__round, attr);
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
static void type__std__ln(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__std__ln);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__ln, attr);
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
static NODE *number__3;
static NODE *character__48;
static NODE *number__4;
static NODE *number__0x0f;
static NODE *character__97;
static NODE *number__1;
static NODE *number__10;
static NODE *number__0x07;

static const char *used_namespaces[] = {
  "std",
  NULL
};

static MODULE_INFO module_info = {
  NULL,
  "basic__types__number",
  continuation_info,
  sizeof(continuation_info)/sizeof(CONTINUATION_INFO),
  (NODE **)&var,
  var_names,
  sizeof(var_names)/sizeof(const char *),
  used_namespaces,
  {DEBUG_FILENAME("basic/types/number.sim")}
};

/******
C O D E
******/

static int already_run = false;

EXPORT void run__basic__types__number(void) {
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

static VTABLE vtable__types__number = {
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
  (void *)no_such_function
};

static ATTRIBUTES attributes__types__number = {
  &vtable__types__number,
  {
    &undefined_attributes_level_1, &undefined_attributes_level_2,
    &undefined_attributes_level_3, &undefined_attributes_level_4,
    &undefined_attributes_level_5, &undefined_attributes_level_6,
    &undefined_attributes_level_7
  }
};

static void type__types__number(void) {
  {
    runtime_error("Attempt to call a numeric value as a function!");
  }
}
SIMPLE_NODE types__number__node =
  {
    type__types__number,
    &attributes__types__number
  };

static NODE *create__types__number() {
  return (NODE *)&types__number__node;
}

static VTABLE vtable__types__integer = {
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
  (void *)no_such_function
};

static ATTRIBUTES attributes__types__integer = {
  &vtable__types__integer,
  {
    &undefined_attributes_level_1, &undefined_attributes_level_2,
    &undefined_attributes_level_3, &undefined_attributes_level_4,
    &undefined_attributes_level_5, &undefined_attributes_level_6,
    &undefined_attributes_level_7
  }
};

static void type__types__integer(void) {
  {
    runtime_error("Attempt to call an integer value as a function!");
  }
}
SIMPLE_NODE types__integer__node =
  {
    type__types__integer,
    &attributes__types__integer
  };

static NODE *create__types__integer() {
  return (NODE *)&types__integer__node;
}
static void *collect_integer(INTEGER *node) {
  INTEGER *new_node = allocate(sizeof(INTEGER));
  new_node->type = node->type;
  *(void **)node = ENCODE_ADDRESS(new_node);
  new_node->attributes = collect_attributes(node->attributes);
  new_node->value = node->value;
  return new_node;
}

static LARGE_INTEGER_DATA *collect_large_integer_data(LARGE_INTEGER_DATA *data) {
  if (!IS_COLLECTED(data)) return data;
  void *new_location = *(void **)data;
  if (IS_AN_INVALID_LENGTH(new_location)) return DECODE_FROM_LENGTH(new_location);
  long size = data->size;
  LARGE_INTEGER_DATA *new_data =
    allocate(sizeof(LARGE_INTEGER_DATA)+size*sizeof(mp_limb_t));
  *(void **)data = ENCODE_TO_LENGTH(new_data);
  new_data->size = size;
  memcpy(new_data->limbs, data->limbs, size*sizeof(mp_limb_t));
  return new_data;
}
static void *collect_large_integer(LARGE_INTEGER *node) {
  LARGE_INTEGER *new_node = allocate(sizeof(LARGE_INTEGER));
  new_node->type = node->type;
  *(void **)node = ENCODE_ADDRESS(new_node);
  new_node->attributes = collect_attributes(node->attributes);
  new_node->data = collect_large_integer_data(node->data);
  return new_node;
}
static void *collect_real(REAL *node) {
  REAL *new_node = allocate(sizeof(REAL));
  new_node->type = node->type;
  *(void **)node = ENCODE_ADDRESS(new_node);
  new_node->attributes = collect_attributes(node->attributes);
  new_node->value = node->value;
  return new_node;
}

static VTABLE vtable__types__positive_integer = {
  sizeof(INTEGER),
  (COLLECTOR *)&collect_integer,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  &func__types__positive_integer___to_uint8,
  (void *)no_such_function,
  &func__types__positive_integer___to_uint32,
  &func__types__positive_integer___to_uint64,
  (void *)no_such_function,
  (void *)no_such_function,
  &func__types__positive_integer___to_int,
  &func__types__positive_integer___to_long,
  &func__types__positive_integer___to_double,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  &func__types__positive_integer___debug_string
};

static ATTRIBUTES attributes__types__positive_integer = {
  &vtable__types__positive_integer,
  {
    &undefined_attributes_level_1, &undefined_attributes_level_2,
    &undefined_attributes_level_3, &undefined_attributes_level_4,
    &undefined_attributes_level_5, &undefined_attributes_level_6,
    &undefined_attributes_level_7
  }
};

extern void type__types__positive_integer(void) {
  {
    runtime_error("Attempt to call an integer value as a function!");
  }
}
extern NODE *create__types__positive_integer(uint64_t value) {
  NODE *node = allocate(sizeof(INTEGER));
  node->type = type__types__positive_integer;
  node->attributes = &attributes__types__positive_integer;
  node->integer.value = value;
  return node;
}

static VTABLE vtable__types__negative_integer = {
  sizeof(INTEGER),
  (COLLECTOR *)&collect_integer,
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
  &func__types__negative_integer___to_int,
  &func__types__negative_integer___to_long,
  &func__types__negative_integer___to_double,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  &func__types__negative_integer___debug_string
};

static ATTRIBUTES attributes__types__negative_integer = {
  &vtable__types__negative_integer,
  {
    &undefined_attributes_level_1, &undefined_attributes_level_2,
    &undefined_attributes_level_3, &undefined_attributes_level_4,
    &undefined_attributes_level_5, &undefined_attributes_level_6,
    &undefined_attributes_level_7
  }
};

static void type__types__negative_integer(void) {
  {
    runtime_error("Attempt to call an integer value as a function!");
  }
}

static NODE *create__types__negative_integer(uint64_t value) {
  NODE *node = allocate(sizeof(INTEGER));
  if (value == 0) {
    node->type = type__types__positive_integer;
    node->attributes = &attributes__types__positive_integer;
  } else {
    node->type = type__types__negative_integer;
    node->attributes = &attributes__types__negative_integer;
  }
  node->integer.value = value;
  return node;
}

static VTABLE vtable__types__positive_large_integer = {
  sizeof(LARGE_INTEGER),
  (COLLECTOR *)&collect_large_integer,
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
  &func__types__positive_large_integer___to_double,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  &func__types__positive_large_integer___debug_string
};

static ATTRIBUTES attributes__types__positive_large_integer = {
  &vtable__types__positive_large_integer,
  {
    &undefined_attributes_level_1, &undefined_attributes_level_2,
    &undefined_attributes_level_3, &undefined_attributes_level_4,
    &undefined_attributes_level_5, &undefined_attributes_level_6,
    &undefined_attributes_level_7
  }
};

static void type__types__positive_large_integer(void) {
  {
    runtime_error("Attempt to call an integer value as a function!");
  }
}
static NODE *create__types__positive_large_integer(LARGE_INTEGER_DATA *data) {
  NODE *node = allocate(sizeof(LARGE_INTEGER));
  node->type = type__types__positive_large_integer;
  node->attributes = &attributes__types__positive_large_integer;
  node->large_integer.data = data;
  return node;
}

static VTABLE vtable__types__negative_large_integer = {
  sizeof(LARGE_INTEGER),
  (COLLECTOR *)&collect_large_integer,
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
  &func__types__negative_large_integer___to_double,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function
};

static ATTRIBUTES attributes__types__negative_large_integer = {
  &vtable__types__negative_large_integer,
  {
    &undefined_attributes_level_1, &undefined_attributes_level_2,
    &undefined_attributes_level_3, &undefined_attributes_level_4,
    &undefined_attributes_level_5, &undefined_attributes_level_6,
    &undefined_attributes_level_7
  }
};

static void type__types__negative_large_integer(void) {
  {
    runtime_error("Attempt to call an integer value as a function!");
  }
}
static NODE *create__types__negative_large_integer(LARGE_INTEGER_DATA *data) {
  NODE *node = allocate(sizeof(LARGE_INTEGER));
  node->type = type__types__negative_large_integer;
  node->attributes = &attributes__types__negative_large_integer;
  node->large_integer.data = data;
  return node;
}

static VTABLE vtable__types__real = {
  sizeof(REAL),
  (COLLECTOR *)&collect_real,
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
  &func__types__real___to_double,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  (void *)no_such_function,
  &func__types__real___debug_string
};

static ATTRIBUTES attributes__types__real = {
  &vtable__types__real,
  {
    &undefined_attributes_level_1, &undefined_attributes_level_2,
    &undefined_attributes_level_3, &undefined_attributes_level_4,
    &undefined_attributes_level_5, &undefined_attributes_level_6,
    &undefined_attributes_level_7
  }
};

static void type__types__real(void) {
  {
    runtime_error("Attempt to call a real value as a function!");
  }
}
static NODE *create__types__real(double value) {
  NODE *node = allocate(sizeof(REAL));
  node->type = type__types__real;
  node->attributes = &attributes__types__real;
  node->real.value = value;
  return node;
}

static NODE *from_uint8(char value) {
  return create__types__positive_integer(value);
}

NODE *runtime__from_uint32(uint32_t value) {
  return create__types__positive_integer(value);
}

NODE *runtime__from_int(int value) {
  if (value >= 0)
    return create__types__positive_integer(value);
  else
    return create__types__negative_integer(-value);
}

NODE *runtime__from_long(long value) {
  if (value >= 0)
    return create__types__positive_integer(value);
  else
    return create__types__negative_integer(-value);
}

NODE *runtime__from_int64(int64_t value) {
  if (value >= 0) {
    return create__types__positive_integer(value);
  } else {
    return create__types__negative_integer(-value);
  }
}

NODE *runtime__from_uint64(uint64_t value) {
  return create__types__positive_integer(value);
}

NODE *runtime__from_digit_string(const char *str) {
  long len = strlen(str);
  char *value = copy(str, ALLOCATION_SIZE(len));
  int i;
  for (i = 0; i < len; ++i) value[i] -= '0';
  LARGE_INTEGER_DATA *data =
    allocate(sizeof(LARGE_INTEGER_DATA)+ALLOCATION_SIZE(len >> 1));
  data->size = mpn_set_str(data->limbs, (unsigned char *)value, len, 10);
  return create__types__positive_large_integer(data);
}

NODE *runtime__from_double(double value) {
  return create__types__real(value);
}

static int func__types__positive_integer___to_int(NODE *node) {
  if (node->integer.value > INT_MAX) {
    {
  runtime_error("Conversion of integer value to \"int\" failed!");
}
  }
  return node->integer.value;
}

static int func__types__negative_integer___to_int(NODE *node) {
  if (node->integer.value > -(uint64_t)INT_MAX) {
    {
  runtime_error("Conversion of integer value to \"int\" failed!");
}
  }
  return -node->integer.value;
}

static uint8_t func__types__positive_integer___to_uint8(NODE *node) {
  if (node->integer.value > 0xff) {
    {
  runtime_error("Conversion of integer value to \"uint8\" failed!");
}
  }
  return node->integer.value;
}

static uint32_t func__types__positive_integer___to_uint32(NODE *node) {
  if (node->integer.value <= 0xffffffff) {
    return node->integer.value;
  } else {
    {
  runtime_error("Conversion of integer value to \"uint32\" failed!");
}
  }
}

static uint64_t func__types__positive_integer___to_uint64(NODE *node) {
  return node->integer.value;
}

static long func__types__positive_integer___to_long(NODE *node) {
  if (node->integer.value > LONG_MAX) {
    {
  runtime_error("Conversion of integer value to \"long\" failed!");
}
  }
  return node->integer.value;
}

static long func__types__negative_integer___to_long(NODE *node) {
  if (node->integer.value > -(uint64_t)LONG_MIN) {
    {
  runtime_error("Conversion of integer value to \"long\" failed!");
}
  }
  return -node->integer.value;
}

static double func__types__positive_integer___to_double(NODE *node) {
  return node->integer.value;
}

static double func__types__negative_integer___to_double(NODE *node) {
  return -node->integer.value;
}

static double func__types__positive_large_integer___to_double(NODE *node) {
  mp_limb_t *limbs = node->large_integer.data->limbs;
  long size = node->large_integer.data->size;
  return mpn_get_d(limbs, size, 1, 0);
}

static double func__types__negative_large_integer___to_double(NODE *node) {
  mp_limb_t *limbs = node->large_integer.data->limbs;
  long size = node->large_integer.data->size;
  return mpn_get_d(limbs, size, -1, 0);
}

static double func__types__real___to_double(NODE *node) {
  return node->real.value;
}
static void entry__types__positive_integer__negate_1(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  if (arguments->slots[0]->integer.value == 0) {
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  {
    NODE *result__node = (NODE *)(create__types__negative_integer(arguments->slots[0]->integer.value));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__types__negative_integer__negate_1(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  {
    NODE *result__node = (NODE *)(create__types__positive_integer(arguments->slots[0]->integer.value));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__types__positive_large_integer__negate_1(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  {
    NODE *result__node = (NODE *)(create__types__negative_large_integer(arguments->slots[0]->large_integer.data));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__types__negative_large_integer__negate_1(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  {
    NODE *result__node = (NODE *)(create__types__positive_large_integer(arguments->slots[0]->large_integer.data));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__types__real__negate_1(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  {
    NODE *result__node = (NODE *)(create__types__real(-arguments->slots[0]->real.value));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}

static NODE *positive_integer_sum(void) {
  uint64_t left_integer = arguments->slots[0]->integer.value;
  uint64_t right_integer = arguments->slots[1]->integer.value;
  uint64_t sum = left_integer+right_integer;
  if (sum >= left_integer) return create__types__positive_integer(sum);
  LARGE_INTEGER_DATA *result =
  #if LIMBS_PER_INT64 == 1
    allocate(sizeof(LARGE_INTEGER_DATA)+2*sizeof(mp_limb_t));
    result->size = 2;
  #else
    allocate(sizeof(LARGE_INTEGER_DATA)+3*sizeof(mp_limb_t));
    result->size = 3;
  #endif
  *(uint64_t *)result->limbs = sum;
  result->limbs[LIMBS_PER_INT64] = 1;
  return create__types__positive_large_integer(result);
}

static NODE *negative_integer_sum(void) {
  uint64_t left_integer = arguments->slots[0]->integer.value;
  uint64_t right_integer = arguments->slots[1]->integer.value;
  uint64_t sum = left_integer+right_integer;
  if (sum >= left_integer) return create__types__negative_integer(sum);
  LARGE_INTEGER_DATA *result =
  #if LIMBS_PER_INT64 == 1
    allocate(sizeof(LARGE_INTEGER_DATA)+2*sizeof(mp_limb_t));
    result->size = 2;
  #else
    allocate(sizeof(LARGE_INTEGER_DATA)+3*sizeof(mp_limb_t));
    result->size = 3;
  #endif
  *(uint64_t *)result->limbs = sum;
  result->limbs[LIMBS_PER_INT64] = 1;
  return create__types__negative_large_integer(result);
}

static NODE *integer_difference(uint64_t left_integer, uint64_t right_integer) {
  if (left_integer >= right_integer)
    return create__types__positive_integer(left_integer-right_integer);
  else
    return create__types__negative_integer(right_integer-left_integer);
}
static void entry__types__positive_integer__plus_1(void) {
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  long right_size;
  mp_limb_t *right_limbs;
  if ((arguments->slots[1])->type == type__types__positive_integer) {
    {
    NODE *result__node = (NODE *)(positive_integer_sum());
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__negative_integer) {
    {
    NODE *result__node = (NODE *)(integer_difference(
        arguments->slots[0]->integer.value, arguments->slots[1]->integer.value));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__real) {
    {
    NODE *result__node = (NODE *)(create__types__real(arguments->slots[0]->integer.value+arguments->slots[1]->real.value));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__positive_large_integer) {
    INTEGER_TO_LARGE_INTEGER(arguments->slots[0]->integer.value, right_limbs, right_size)
    {
    NODE *result__node = (NODE *)(large_integer_sum(
        arguments->slots[1]->large_integer.data->limbs, arguments->slots[1]->large_integer.data->size,
        right_limbs, right_size, 1));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__negative_large_integer) {
    INTEGER_TO_LARGE_INTEGER(arguments->slots[0]->integer.value, right_limbs, right_size)
    {
    NODE *result__node = (NODE *)(large_difference(
        arguments->slots[1]->large_integer.data->limbs, arguments->slots[1]->large_integer.data->size,
        right_limbs, right_size, -1));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  }
  {
    invalid_arguments_error();
  }
}
static void entry__types__positive_integer__minus_1(void) {
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  long right_size;
  mp_limb_t *right_limbs;
  if ((arguments->slots[1])->type == type__types__positive_integer) {
    {
    NODE *result__node = (NODE *)(integer_difference(
        arguments->slots[0]->integer.value, arguments->slots[1]->integer.value));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__negative_integer) {
    {
    NODE *result__node = (NODE *)(positive_integer_sum());
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__real) {
    {
    NODE *result__node = (NODE *)(create__types__real(arguments->slots[0]->integer.value-arguments->slots[1]->real.value));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__positive_large_integer) {
    INTEGER_TO_LARGE_INTEGER(arguments->slots[0]->integer.value, right_limbs, right_size)
    {
    NODE *result__node = (NODE *)(large_difference(
        arguments->slots[1]->large_integer.data->limbs, arguments->slots[1]->large_integer.data->size,
        right_limbs, right_size, -1));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__negative_large_integer) {
    INTEGER_TO_LARGE_INTEGER(arguments->slots[0]->integer.value, right_limbs, right_size)
    {
    NODE *result__node = (NODE *)(large_integer_sum(
        arguments->slots[1]->large_integer.data->limbs, arguments->slots[1]->large_integer.data->size,
        right_limbs, right_size, 1));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  }
  {
    invalid_arguments_error();
  }
}
static void entry__types__negative_integer__plus_1(void) {
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  long right_size;
  mp_limb_t *right_limbs;
  if ((arguments->slots[1])->type == type__types__positive_integer) {
    {
    NODE *result__node = (NODE *)(integer_difference(
        arguments->slots[1]->integer.value, arguments->slots[0]->integer.value));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__negative_integer) {
    {
    NODE *result__node = (NODE *)(negative_integer_sum());
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__real) {
    {
    NODE *result__node = (NODE *)(create__types__real(arguments->slots[1]->real.value-arguments->slots[0]->integer.value));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__positive_large_integer) {
    INTEGER_TO_LARGE_INTEGER(arguments->slots[0]->integer.value, right_limbs, right_size)
    {
    NODE *result__node = (NODE *)(large_difference(
        arguments->slots[1]->large_integer.data->limbs, arguments->slots[1]->large_integer.data->size,
        right_limbs, right_size, 1));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__negative_large_integer) {
    INTEGER_TO_LARGE_INTEGER(arguments->slots[0]->integer.value, right_limbs, right_size)
    {
    NODE *result__node = (NODE *)(large_integer_sum(
        arguments->slots[1]->large_integer.data->limbs, arguments->slots[1]->large_integer.data->size,
        right_limbs, right_size, -1));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  }
  {
    invalid_arguments_error();
  }
}
static void entry__types__negative_integer__minus_1(void) {
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  long right_size;
  mp_limb_t *right_limbs;
  if ((arguments->slots[1])->type == type__types__positive_integer) {
    {
    NODE *result__node = (NODE *)(negative_integer_sum());
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__negative_integer) {
    {
    NODE *result__node = (NODE *)(integer_difference(
        arguments->slots[1]->integer.value, arguments->slots[0]->integer.value));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__real) {
    {
    NODE *result__node = (NODE *)(create__types__real(-(arguments->slots[1]->real.value+arguments->slots[0]->integer.value)));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__positive_large_integer) {
    INTEGER_TO_LARGE_INTEGER(arguments->slots[0]->integer.value, right_limbs, right_size)
    {
    NODE *result__node = (NODE *)(large_integer_sum(
        arguments->slots[1]->large_integer.data->limbs, arguments->slots[1]->large_integer.data->size,
        right_limbs, right_size, -1));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__negative_large_integer) {
    INTEGER_TO_LARGE_INTEGER(arguments->slots[0]->integer.value, right_limbs, right_size)
    {
    NODE *result__node = (NODE *)(large_difference(
        arguments->slots[1]->large_integer.data->limbs, arguments->slots[1]->large_integer.data->size,
        right_limbs, right_size, 1));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  }
  {
    invalid_arguments_error();
  }
}

static NODE *large_integer_sum(
  mp_limb_t *left_limbs, long left_size,
  mp_limb_t *right_limbs, long right_size,
  int sign
) {
  if (right_size > left_size) {
    long tmp_size = left_size;
    left_size = right_size;
    right_size = tmp_size;
    mp_limb_t *tmp_limbs = left_limbs;
    left_limbs = right_limbs;
    right_limbs = tmp_limbs;
  }
  LARGE_INTEGER_DATA *result =
    allocate(sizeof(LARGE_INTEGER_DATA)+(left_size+1)*sizeof(mp_limb_t));
  if (
    mpn_add(result->limbs, left_limbs, left_size, right_limbs, right_size)
  ) result->limbs[left_size++] = 1;
  result->size = left_size;
  if (sign > 0)
    return create__types__positive_large_integer(result);
  else
    return create__types__negative_large_integer(result);
}

static NODE *large_difference(
  mp_limb_t *left_limbs, long left_size,
  mp_limb_t *right_limbs, long right_size,
  int sign
) {
  if (right_size > left_size) {
    long tmp_size = left_size;
    left_size = right_size;
    right_size = tmp_size;
    mp_limb_t *tmp_limbs = left_limbs;
    left_limbs = right_limbs;
    right_limbs = tmp_limbs;
    sign = -sign;
  }
  LARGE_INTEGER_DATA *result =
    allocate(sizeof(LARGE_INTEGER_DATA)+left_size*sizeof(mp_limb_t));
  if (
    mpn_sub(result->limbs, left_limbs, left_size, right_limbs, right_size)
  ) {
    mpn_sub(result->limbs, right_limbs, right_size, left_limbs, left_size);
    sign = -sign;
  }
  while (left_size > 0 && result->limbs[left_size-1] == 0) --left_size;
  if (left_size <= LIMBS_PER_INT64) {
    uint64_t left_integer = *(uint64_t *)result->limbs;
    if (sign > 0)
      return create__types__positive_integer(left_integer);
    else
      return create__types__negative_integer(left_integer);
  } else {
    result->size = left_size;
    if (sign > 0)
      return create__types__positive_large_integer(result);
    else
      return create__types__negative_large_integer(result);
  }
}
static void entry__types__positive_large_integer__plus_1(void) {
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  long right_size;
  mp_limb_t *right_limbs;
  if ((arguments->slots[1])->type == type__types__positive_large_integer) {
    {
    NODE *result__node = (NODE *)(large_integer_sum(
        arguments->slots[0]->large_integer.data->limbs, arguments->slots[0]->large_integer.data->size,
        arguments->slots[1]->large_integer.data->limbs, arguments->slots[1]->large_integer.data->size,
        1));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__positive_integer) {
    INTEGER_TO_LARGE_INTEGER(arguments->slots[1]->integer.value, right_limbs, right_size)
    {
    NODE *result__node = (NODE *)(large_integer_sum(
        arguments->slots[0]->large_integer.data->limbs, arguments->slots[0]->large_integer.data->size,
        right_limbs, right_size, 1));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__negative_integer) {
    INTEGER_TO_LARGE_INTEGER(arguments->slots[1]->integer.value, right_limbs, right_size)
    {
    NODE *result__node = (NODE *)(large_difference(
        arguments->slots[0]->large_integer.data->limbs, arguments->slots[0]->large_integer.data->size,
        right_limbs, right_size, 1));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__negative_large_integer) {
    {
    NODE *result__node = (NODE *)(large_difference(
        arguments->slots[0]->large_integer.data->limbs, arguments->slots[0]->large_integer.data->size,
        arguments->slots[1]->large_integer.data->limbs, arguments->slots[1]->large_integer.data->size,
        1));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__real) {
    mp_limb_t *left_limbs = arguments->slots[0]->large_integer.data->limbs;
    long left_size = arguments->slots[0]->large_integer.data->size;
    {
    NODE *result__node = (NODE *)(create__types__real(
        mpn_get_d(left_limbs, left_size, 1, 0)+arguments->slots[1]->real.value));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  }
  {
    invalid_arguments_error();
  }
}
static void entry__types__positive_large_integer__minus_1(void) {
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  long right_size;
  mp_limb_t *right_limbs;
  if ((arguments->slots[1])->type == type__types__positive_large_integer) {
    {
    NODE *result__node = (NODE *)(large_difference(
        arguments->slots[0]->large_integer.data->limbs, arguments->slots[0]->large_integer.data->size,
        arguments->slots[1]->large_integer.data->limbs, arguments->slots[1]->large_integer.data->size,
        1));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__positive_integer) {
    INTEGER_TO_LARGE_INTEGER(arguments->slots[1]->integer.value, right_limbs, right_size)
    {
    NODE *result__node = (NODE *)(large_difference(
        arguments->slots[0]->large_integer.data->limbs, arguments->slots[0]->large_integer.data->size,
        right_limbs, right_size, 1));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__negative_integer) {
    INTEGER_TO_LARGE_INTEGER(arguments->slots[1]->integer.value, right_limbs, right_size)
    {
    NODE *result__node = (NODE *)(large_integer_sum(
        arguments->slots[0]->large_integer.data->limbs, arguments->slots[0]->large_integer.data->size,
        right_limbs, right_size, 1));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__negative_large_integer) {
    {
    NODE *result__node = (NODE *)(large_integer_sum(
        arguments->slots[0]->large_integer.data->limbs, arguments->slots[0]->large_integer.data->size,
        arguments->slots[1]->large_integer.data->limbs, arguments->slots[1]->large_integer.data->size,
        1));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__real) {
    mp_limb_t *left_limbs = arguments->slots[0]->large_integer.data->limbs;
    long left_size = arguments->slots[0]->large_integer.data->size;
    {
    NODE *result__node = (NODE *)(create__types__real(
        mpn_get_d(left_limbs, left_size, 1, 0)-arguments->slots[1]->real.value));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  }
  {
    invalid_arguments_error();
  }
}
static void entry__types__negative_large_integer__plus_1(void) {
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  long right_size;
  mp_limb_t *right_limbs;
  if ((arguments->slots[1])->type == type__types__positive_large_integer) {
    {
    NODE *result__node = (NODE *)(large_difference(
        arguments->slots[0]->large_integer.data->limbs, arguments->slots[0]->large_integer.data->size,
        arguments->slots[1]->large_integer.data->limbs, arguments->slots[1]->large_integer.data->size,
        -1));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__positive_integer) {
    INTEGER_TO_LARGE_INTEGER(arguments->slots[1]->integer.value, right_limbs, right_size)
    {
    NODE *result__node = (NODE *)(large_difference(
        arguments->slots[0]->large_integer.data->limbs, arguments->slots[0]->large_integer.data->size,
        right_limbs, right_size, -1));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__negative_integer) {
    INTEGER_TO_LARGE_INTEGER(arguments->slots[1]->integer.value, right_limbs, right_size)
    {
    NODE *result__node = (NODE *)(large_integer_sum(
        arguments->slots[0]->large_integer.data->limbs, arguments->slots[0]->large_integer.data->size,
        right_limbs, right_size, -1));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__negative_large_integer) {
    {
    NODE *result__node = (NODE *)(large_integer_sum(
        arguments->slots[0]->large_integer.data->limbs, arguments->slots[0]->large_integer.data->size,
        arguments->slots[1]->large_integer.data->limbs, arguments->slots[1]->large_integer.data->size,
        -1));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__real) {
    mp_limb_t *left_limbs = arguments->slots[0]->large_integer.data->limbs;
    long left_size = arguments->slots[0]->large_integer.data->size;
    {
    NODE *result__node = (NODE *)(create__types__real(
        mpn_get_d(left_limbs, left_size, -1, 0)+arguments->slots[1]->real.value));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  }
  {
    invalid_arguments_error();
  }
}
static void entry__types__negative_large_integer__minus_1(void) {
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  long right_size;
  mp_limb_t *right_limbs;
  if ((arguments->slots[1])->type == type__types__positive_large_integer) {
    {
    NODE *result__node = (NODE *)(large_integer_sum(
        arguments->slots[0]->large_integer.data->limbs, arguments->slots[0]->large_integer.data->size,
        arguments->slots[1]->large_integer.data->limbs, arguments->slots[1]->large_integer.data->size,
        -1));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__positive_integer) {
    INTEGER_TO_LARGE_INTEGER(arguments->slots[1]->integer.value, right_limbs, right_size)
    {
    NODE *result__node = (NODE *)(large_integer_sum(
        arguments->slots[0]->large_integer.data->limbs, arguments->slots[0]->large_integer.data->size,
        right_limbs, right_size, -1));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__negative_integer) {
    INTEGER_TO_LARGE_INTEGER(arguments->slots[1]->integer.value, right_limbs, right_size)
    {
    NODE *result__node = (NODE *)(large_difference(
        arguments->slots[0]->large_integer.data->limbs, arguments->slots[0]->large_integer.data->size,
        right_limbs, right_size, -1));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__negative_large_integer) {
    {
    NODE *result__node = (NODE *)(large_difference(
        arguments->slots[0]->large_integer.data->limbs, arguments->slots[0]->large_integer.data->size,
        arguments->slots[1]->large_integer.data->limbs, arguments->slots[1]->large_integer.data->size,
        -1));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__real) {
    mp_limb_t *left_limbs = arguments->slots[0]->large_integer.data->limbs;
    long left_size = arguments->slots[0]->large_integer.data->size;
    {
    NODE *result__node = (NODE *)(create__types__real(
        mpn_get_d(left_limbs, left_size, -1, 0)-arguments->slots[1]->real.value));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  }
  {
    invalid_arguments_error();
  }
}
static void entry__types__real__plus_1(void) {
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  long right_size;
  mp_limb_t *right_limbs;
  if ((arguments->slots[1])->type == type__types__real) {
    {
    NODE *result__node = (NODE *)(create__types__real(arguments->slots[0]->real.value+arguments->slots[1]->real.value));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__positive_integer) {
    {
    NODE *result__node = (NODE *)(create__types__real(arguments->slots[0]->real.value+arguments->slots[1]->integer.value));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__negative_integer) {
    {
    NODE *result__node = (NODE *)(create__types__real(arguments->slots[0]->real.value-arguments->slots[1]->integer.value));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__positive_large_integer) {
    right_size = arguments->slots[1]->large_integer.data->size;
    right_limbs = arguments->slots[1]->large_integer.data->limbs;
    {
    NODE *result__node = (NODE *)(create__types__real(
        arguments->slots[0]->real.value+mpn_get_d(right_limbs, right_size, 1, 0)));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__negative_large_integer) {
    right_size = arguments->slots[1]->large_integer.data->size;
    right_limbs = arguments->slots[1]->large_integer.data->limbs;
    {
    NODE *result__node = (NODE *)(create__types__real(
        arguments->slots[0]->real.value+mpn_get_d(right_limbs, right_size, -1, 0)));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  }
  {
    invalid_arguments_error();
  }
}
static void entry__types__real__minus_1(void) {
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  long right_size;
  mp_limb_t *right_limbs;
  if ((arguments->slots[1])->type == type__types__real) {
    {
    NODE *result__node = (NODE *)(create__types__real(arguments->slots[0]->real.value-arguments->slots[1]->real.value));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__positive_integer) {
    {
    NODE *result__node = (NODE *)(create__types__real(arguments->slots[0]->real.value-arguments->slots[1]->integer.value));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__negative_integer) {
    {
    NODE *result__node = (NODE *)(create__types__real(arguments->slots[0]->real.value+arguments->slots[1]->integer.value));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__positive_large_integer) {
    right_size = arguments->slots[1]->large_integer.data->size;
    right_limbs = arguments->slots[1]->large_integer.data->limbs;
    {
    NODE *result__node = (NODE *)(create__types__real(
        arguments->slots[0]->real.value-mpn_get_d(right_limbs, right_size, 1, 0)));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__negative_large_integer) {
    right_size = arguments->slots[1]->large_integer.data->size;
    right_limbs = arguments->slots[1]->large_integer.data->limbs;
    {
    NODE *result__node = (NODE *)(create__types__real(
        arguments->slots[0]->real.value-mpn_get_d(right_limbs, right_size, -1, 0)));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  }
  {
    invalid_arguments_error();
  }
}

static NODE *integer_product(int sign) {
  uint64_t left_integer = arguments->slots[0]->integer.value;
  uint64_t right_integer = arguments->slots[1]->integer.value;
  if (right_integer > left_integer) {
    uint64_t tmp = left_integer;
    left_integer = right_integer;
    right_integer = tmp;
  }
  if (right_integer >> 32 == 0) {
    uint32_t right_low = right_integer;
    uint32_t left_low = left_integer;
    uint32_t left_high = left_integer >> 32;
    uint64_t product_high = (uint64_t)right_low*left_high;
    if (product_high >> 32 == 0) {
      product_high <<= 32;
      uint64_t product = (uint64_t)right_low*left_low + product_high;
      if (product >= product_high) {
        if (sign > 0)
          return create__types__positive_integer(product);
        else
          return create__types__negative_integer(product);
      }
    }
  }
  {
    mp_limb_t *left_limbs, *right_limbs;
    long left_size, right_size;
    INTEGER_TO_LARGE_INTEGER(left_integer, left_limbs, left_size)
    INTEGER_TO_LARGE_INTEGER(right_integer, right_limbs, right_size)
    return
      large_integer_product(left_limbs, left_size, right_limbs, right_size, sign);
  }
}
static void entry__types__positive_integer__times_1(void) {
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  long right_size;
  mp_limb_t *right_limbs;
  if ((arguments->slots[1])->type == type__types__positive_integer) {
    {
    NODE *result__node = (NODE *)(integer_product(1));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__negative_integer) {
    {
    NODE *result__node = (NODE *)(integer_product(-1));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__real) {
    {
    NODE *result__node = (NODE *)(create__types__real(arguments->slots[0]->integer.value*arguments->slots[1]->real.value));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__positive_large_integer) {
    INTEGER_TO_LARGE_INTEGER(arguments->slots[0]->integer.value, right_limbs, right_size)
    {
    NODE *result__node = (NODE *)(large_integer_product(
        arguments->slots[1]->large_integer.data->limbs, arguments->slots[1]->large_integer.data->size,
        right_limbs, right_size, 1));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__negative_large_integer) {
    INTEGER_TO_LARGE_INTEGER(arguments->slots[0]->integer.value, right_limbs, right_size)
    {
    NODE *result__node = (NODE *)(large_integer_product(
        arguments->slots[1]->large_integer.data->limbs, arguments->slots[1]->large_integer.data->size,
        right_limbs, right_size, -1));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  }
  {
    invalid_arguments_error();
  }
}
static void entry__types__negative_integer__times_1(void) {
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  long right_size;
  mp_limb_t *right_limbs;
  if ((arguments->slots[1])->type == type__types__positive_integer) {
    {
    NODE *result__node = (NODE *)(integer_product(-1));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__negative_integer) {
    {
    NODE *result__node = (NODE *)(integer_product(1));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__real) {
    {
    NODE *result__node = (NODE *)(create__types__real(-(arguments->slots[0]->integer.value*arguments->slots[1]->real.value)));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__positive_large_integer) {
    INTEGER_TO_LARGE_INTEGER(arguments->slots[0]->integer.value, right_limbs, right_size)
    {
    NODE *result__node = (NODE *)(large_integer_product(
        arguments->slots[1]->large_integer.data->limbs, arguments->slots[1]->large_integer.data->size,
        right_limbs, right_size, -1));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__negative_large_integer) {
    INTEGER_TO_LARGE_INTEGER(arguments->slots[0]->integer.value, right_limbs, right_size)
    {
    NODE *result__node = (NODE *)(large_integer_product(
        arguments->slots[1]->large_integer.data->limbs, arguments->slots[1]->large_integer.data->size,
        right_limbs, right_size, 1));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  }
  {
    invalid_arguments_error();
  }
}

static NODE *large_integer_product(
  mp_limb_t *left_limbs, long left_size,
  mp_limb_t *right_limbs, long right_size,
  int sign
) {
  if (right_size > left_size) {
    long tmp_size = left_size;
    left_size = right_size;
    right_size = tmp_size;
    mp_limb_t *tmp_limbs = left_limbs;
    left_limbs = right_limbs;
    right_limbs = tmp_limbs;
  }
  long result_size = left_size+right_size;
  LARGE_INTEGER_DATA *result =
    allocate(sizeof(LARGE_INTEGER_DATA)+result_size*sizeof(mp_limb_t));
  if (
    mpn_mul(result->limbs, left_limbs, left_size, right_limbs, right_size) == 0
  ) --result_size;
  result->size = result_size;
  if (sign > 0)
    return create__types__positive_large_integer(result);
  else
    return create__types__negative_large_integer(result);
}
static void entry__types__positive_large_integer__times_1(void) {
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  long right_size;
  mp_limb_t *right_limbs;
  if ((arguments->slots[1])->type == type__types__positive_large_integer) {
    {
    NODE *result__node = (NODE *)(large_integer_product(
        arguments->slots[0]->large_integer.data->limbs, arguments->slots[0]->large_integer.data->size,
        arguments->slots[1]->large_integer.data->limbs, arguments->slots[1]->large_integer.data->size,
        1));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__positive_integer) {
    INTEGER_TO_LARGE_INTEGER(arguments->slots[1]->integer.value, right_limbs, right_size)
    {
    NODE *result__node = (NODE *)(large_integer_product(
        arguments->slots[0]->large_integer.data->limbs, arguments->slots[0]->large_integer.data->size,
        right_limbs, right_size, 1));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__negative_integer) {
    INTEGER_TO_LARGE_INTEGER(arguments->slots[1]->integer.value, right_limbs, right_size)
    {
    NODE *result__node = (NODE *)(large_integer_product(
        arguments->slots[0]->large_integer.data->limbs, arguments->slots[0]->large_integer.data->size,
        right_limbs, right_size, -1));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__negative_large_integer) {
    {
    NODE *result__node = (NODE *)(large_integer_product(
        arguments->slots[0]->large_integer.data->limbs, arguments->slots[0]->large_integer.data->size,
        arguments->slots[1]->large_integer.data->limbs, arguments->slots[1]->large_integer.data->size,
        -1));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__real) {
    mp_limb_t *left_limbs = arguments->slots[0]->large_integer.data->limbs;
    long left_size = arguments->slots[0]->large_integer.data->size;
    {
    NODE *result__node = (NODE *)(create__types__real(
        mpn_get_d(left_limbs, left_size, 1, 0)*arguments->slots[1]->real.value));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  }
  {
    invalid_arguments_error();
  }
}
static void entry__types__negative_large_integer__times_1(void) {
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  long right_size;
  mp_limb_t *right_limbs;
  if ((arguments->slots[1])->type == type__types__positive_large_integer) {
    {
    NODE *result__node = (NODE *)(large_integer_product(
        arguments->slots[0]->large_integer.data->limbs, arguments->slots[0]->large_integer.data->size,
        arguments->slots[1]->large_integer.data->limbs, arguments->slots[1]->large_integer.data->size,
        -1));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__positive_integer) {
    INTEGER_TO_LARGE_INTEGER(arguments->slots[1]->integer.value, right_limbs, right_size)
    {
    NODE *result__node = (NODE *)(large_integer_product(
        arguments->slots[0]->large_integer.data->limbs, arguments->slots[0]->large_integer.data->size,
        right_limbs, right_size, -1));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__negative_integer) {
    INTEGER_TO_LARGE_INTEGER(arguments->slots[1]->integer.value, right_limbs, right_size)
    {
    NODE *result__node = (NODE *)(large_integer_product(
        arguments->slots[0]->large_integer.data->limbs, arguments->slots[0]->large_integer.data->size,
        right_limbs, right_size, 1));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__negative_large_integer) {
    {
    NODE *result__node = (NODE *)(large_integer_product(
        arguments->slots[0]->large_integer.data->limbs, arguments->slots[0]->large_integer.data->size,
        arguments->slots[1]->large_integer.data->limbs, arguments->slots[1]->large_integer.data->size,
        1));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__real) {
    mp_limb_t *left_limbs = arguments->slots[0]->large_integer.data->limbs;
    long left_size = arguments->slots[0]->large_integer.data->size;
    {
    NODE *result__node = (NODE *)(create__types__real(
        mpn_get_d(left_limbs, left_size, -1, 0)+arguments->slots[1]->real.value));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  }
  {
    invalid_arguments_error();
  }
}
static void entry__types__real__times_1(void) {
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  if ((arguments->slots[1])->type == type__types__real) {
    {
    NODE *result__node = (NODE *)(create__types__real(arguments->slots[0]->real.value*arguments->slots[1]->real.value));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__positive_integer) {
    {
    NODE *result__node = (NODE *)(create__types__real(arguments->slots[0]->real.value*arguments->slots[1]->integer.value));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__negative_integer) {
    {
    NODE *result__node = (NODE *)(create__types__real(-arguments->slots[0]->real.value*arguments->slots[1]->integer.value));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__positive_large_integer) {
    mp_limb_t *right_limbs = arguments->slots[1]->large_integer.data->limbs;
    long right_size = arguments->slots[1]->large_integer.data->size;
    {
    NODE *result__node = (NODE *)(create__types__real(
        arguments->slots[0]->real.value*mpn_get_d(right_limbs, right_size, 1, 0)));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__negative_large_integer) {
    mp_limb_t *right_limbs = arguments->slots[1]->large_integer.data->limbs;
    long right_size = arguments->slots[1]->large_integer.data->size;
    {
    NODE *result__node = (NODE *)(create__types__real(
        arguments->slots[0]->real.value*mpn_get_d(right_limbs, right_size, -1, 0)));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  }
  {
    invalid_arguments_error();
  }
}

static NODE *integer_quotient(int sign) {
  uint64_t left_integer = arguments->slots[0]->integer.value;
  uint64_t right_integer = arguments->slots[1]->integer.value;
  if (right_integer == 0LL) {
  divide_by_zero_error();
}
  int64_t quotient = left_integer/right_integer;
  if (quotient*right_integer == left_integer)
    if (sign > 0)
      return create__types__positive_integer(quotient);
    else
      return create__types__negative_integer(quotient);
  return create__types__real(sign*((double)left_integer/right_integer));
}
static void entry__types__positive_integer__over_1(void) {
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  int sign;
  if ((arguments->slots[1])->type == type__types__positive_integer) {
    {
    NODE *result__node = (NODE *)(integer_quotient(1));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__negative_integer) {
    {
    NODE *result__node = (NODE *)(integer_quotient(-1));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__real) {
    {
    NODE *result__node = (NODE *)(create__types__real(arguments->slots[0]->integer.value/arguments->slots[1]->real.value));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__positive_large_integer) {
    sign = 1;
    div_large_positive:;
    mp_limb_t *right_limbs = arguments->slots[1]->large_integer.data->limbs;
    long right_size = arguments->slots[1]->large_integer.data->size;
    {
    NODE *result__node = (NODE *)(create__types__real(
        arguments->slots[0]->integer.value/mpn_get_d(right_limbs, right_size, sign, 0)));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__negative_large_integer) {
    sign = -1;
    goto div_large_positive;
  }
  {
    invalid_arguments_error();
  }
}
static void entry__types__negative_integer__over_1(void) {
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  int sign;
  if ((arguments->slots[1])->type == type__types__positive_integer) {
    {
    NODE *result__node = (NODE *)(integer_quotient(-1));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__negative_integer) {
    {
    NODE *result__node = (NODE *)(integer_quotient(1));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__real) {
    {
    NODE *result__node = (NODE *)(create__types__real(-(arguments->slots[0]->integer.value/arguments->slots[1]->real.value)));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__positive_large_integer) {
    sign = -1;
    div_large_negative:;
    mp_limb_t *right_limbs = arguments->slots[1]->large_integer.data->limbs;
    long right_size = arguments->slots[1]->large_integer.data->size;
    {
    NODE *result__node = (NODE *)(create__types__real(
        arguments->slots[0]->integer.value/mpn_get_d(right_limbs, right_size, sign, 0)));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__negative_large_integer) {
    sign = 1;
    goto div_large_negative;
  }
  {
    invalid_arguments_error();
  }
}

static NODE *large_integer_quotient(
  mp_limb_t *left_limbs, long left_size,
  mp_limb_t *right_limbs, long right_size,
  int sign
) {
  if (
    right_size > left_size ||
    right_size == left_size && right_limbs[right_size-1] > left_limbs[left_size-1]
  ) {
    large_integer_inexact_division:
    return
      create__types__real(
        mpn_get_d(left_limbs, left_size, sign, 0) /
        mpn_get_d(right_limbs, right_size, 1, 0));
  }
  long quotient_size = left_size+1-right_size;
  LARGE_INTEGER_DATA *quotient =
    allocate(sizeof(LARGE_INTEGER_DATA)+quotient_size*sizeof(mp_limb_t));
  mp_limb_t *remainder = allocate(right_size*sizeof(mp_limb_t));
  mpn_tdiv_qr(
    quotient->limbs, remainder, 0,
    left_limbs, left_size, right_limbs, right_size);
  int i;
  for (i = 0; i < right_size; ++i) {
    if (remainder[i] != 0) goto large_integer_inexact_division;
  }
  if (quotient->limbs[quotient_size-1] == 0L) --quotient_size;
  if (quotient_size <= LIMBS_PER_INT64) {
    uint64_t left_integer = *(uint64_t *)quotient->limbs;
    if (sign > 0)
      return create__types__positive_integer(left_integer);
    else
      return create__types__negative_integer(left_integer);
  }
  quotient->size = quotient_size;
  if (sign > 0)
    return create__types__positive_large_integer(quotient);
  else
    return create__types__negative_large_integer(quotient);
}
static void entry__types__positive_large_integer__over_1(void) {
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  long right_size;
  mp_limb_t *right_limbs;
  if ((arguments->slots[1])->type == type__types__positive_large_integer) {
    {
    NODE *result__node = (NODE *)(large_integer_quotient(
        arguments->slots[0]->large_integer.data->limbs, arguments->slots[0]->large_integer.data->size,
        arguments->slots[1]->large_integer.data->limbs, arguments->slots[1]->large_integer.data->size,
        1));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__positive_integer) {
    INTEGER_TO_LARGE_INTEGER(arguments->slots[1]->integer.value, right_limbs, right_size)
    {
    NODE *result__node = (NODE *)(large_integer_quotient(
        arguments->slots[0]->large_integer.data->limbs, arguments->slots[0]->large_integer.data->size,
        right_limbs, right_size, 1));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__negative_integer) {
    INTEGER_TO_LARGE_INTEGER(arguments->slots[1]->integer.value, right_limbs, right_size)
    {
    NODE *result__node = (NODE *)(large_integer_quotient(
        arguments->slots[0]->large_integer.data->limbs, arguments->slots[0]->large_integer.data->size,
        right_limbs, right_size, -1));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__negative_large_integer) {
    {
    NODE *result__node = (NODE *)(large_integer_quotient(
        arguments->slots[0]->large_integer.data->limbs, arguments->slots[0]->large_integer.data->size,
        arguments->slots[1]->large_integer.data->limbs, arguments->slots[1]->large_integer.data->size,
        -1));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__real) {
    mp_limb_t *left_limbs = arguments->slots[0]->large_integer.data->limbs;
    long left_size = arguments->slots[0]->large_integer.data->size;
    {
    NODE *result__node = (NODE *)(create__types__real(
        mpn_get_d(left_limbs, left_size, 1, 0)/arguments->slots[1]->real.value));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  }
  {
    invalid_arguments_error();
  }
}
static void entry__types__negative_large_integer__over_1(void) {
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  long right_size;
  mp_limb_t *right_limbs;
  if ((arguments->slots[1])->type == type__types__positive_large_integer) {
    {
    NODE *result__node = (NODE *)(large_integer_quotient(
        arguments->slots[0]->large_integer.data->limbs, arguments->slots[0]->large_integer.data->size,
        arguments->slots[1]->large_integer.data->limbs, arguments->slots[1]->large_integer.data->size,
        -1));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__positive_integer) {
    INTEGER_TO_LARGE_INTEGER(arguments->slots[1]->integer.value, right_limbs, right_size)
    {
    NODE *result__node = (NODE *)(large_integer_quotient(
        arguments->slots[0]->large_integer.data->limbs, arguments->slots[0]->large_integer.data->size,
        right_limbs, right_size, -1));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__negative_integer) {
    INTEGER_TO_LARGE_INTEGER(arguments->slots[1]->integer.value, right_limbs, right_size)
    {
    NODE *result__node = (NODE *)(large_integer_quotient(
        arguments->slots[0]->large_integer.data->limbs, arguments->slots[0]->large_integer.data->size,
        right_limbs, right_size, 1));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__negative_large_integer) {
    {
    NODE *result__node = (NODE *)(large_integer_quotient(
        arguments->slots[0]->large_integer.data->limbs, arguments->slots[0]->large_integer.data->size,
        arguments->slots[1]->large_integer.data->limbs, arguments->slots[1]->large_integer.data->size,
        1));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__real) {
    mp_limb_t *left_limbs = arguments->slots[0]->large_integer.data->limbs;
    long left_size = arguments->slots[0]->large_integer.data->size;
    {
    NODE *result__node = (NODE *)(create__types__real(
        mpn_get_d(left_limbs, left_size, -1, 0)+arguments->slots[1]->real.value));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  }
  {
    invalid_arguments_error();
  }
}
static void entry__types__real__over_1(void) {
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  if ((arguments->slots[1])->type == type__types__real) {
    {
    NODE *result__node = (NODE *)(create__types__real(arguments->slots[0]->real.value/arguments->slots[1]->real.value));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__positive_integer) {
    {
    NODE *result__node = (NODE *)(create__types__real(arguments->slots[0]->real.value/arguments->slots[1]->integer.value));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__negative_integer) {
    {
    NODE *result__node = (NODE *)(create__types__real(-arguments->slots[0]->real.value/arguments->slots[1]->integer.value));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__positive_large_integer) {
    mp_limb_t *right_limbs = arguments->slots[1]->large_integer.data->limbs;
    long right_size = arguments->slots[1]->large_integer.data->size;
    {
    NODE *result__node = (NODE *)(create__types__real(
        arguments->slots[0]->real.value/mpn_get_d(right_limbs, right_size, 1, 0)));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__negative_large_integer) {
    mp_limb_t *right_limbs = arguments->slots[1]->large_integer.data->limbs;
    long right_size = arguments->slots[1]->large_integer.data->size;
    {
    NODE *result__node = (NODE *)(create__types__real(
        arguments->slots[0]->real.value/mpn_get_d(right_limbs, right_size, -1, 0)));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  }
  {
    invalid_arguments_error();
  }
}
static void entry__types__positive_integer__div_1(void) {
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  if ((arguments->slots[1])->type == type__types__positive_integer) {
    {
    NODE *result__node = (NODE *)(create__types__positive_integer(
        arguments->slots[0]->integer.value / arguments->slots[1]->integer.value));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  }
  {
    not_yet_implemented_error();
  }
}
static void entry__types__positive_integer__mod_1(void) {
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  if ((arguments->slots[1])->type == type__types__positive_integer) {
    {
    NODE *result__node = (NODE *)(create__types__positive_integer(
        arguments->slots[0]->integer.value % arguments->slots[1]->integer.value));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  }
  {
    not_yet_implemented_error();
  }
}
static void entry__types__positive_integer__equal_1(void) {
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  if ((arguments->slots[1])->type == type__types__positive_integer) {
    {
    NODE *result__node = (NODE *)(from_bool(arguments->slots[0]->integer.value == arguments->slots[1]->integer.value));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__real) {
    {
    NODE *result__node = (NODE *)(from_bool(arguments->slots[0]->integer.value == arguments->slots[1]->real.value));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  }
  {
    arguments = node_p;
    arguments->slots[0] = boolean_false;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__types__positive_integer__equal_type_and_value_1(void) {
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  if ((arguments->slots[1])->type == type__types__positive_integer) {
    {
    NODE *result__node = (NODE *)(from_bool(arguments->slots[0]->integer.value == arguments->slots[1]->integer.value));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  }
  {
    arguments = node_p;
    arguments->slots[0] = boolean_false;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__types__negative_integer__equal_1(void) {
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  if ((arguments->slots[1])->type == type__types__negative_integer) {
    {
    NODE *result__node = (NODE *)(from_bool(arguments->slots[0]->integer.value == arguments->slots[1]->integer.value));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__real) {
    {
    NODE *result__node = (NODE *)(from_bool(arguments->slots[0]->integer.value == -arguments->slots[1]->real.value));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  }
  {
    arguments = node_p;
    arguments->slots[0] = boolean_false;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__types__negative_integer__equal_type_and_value_1(void) {
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  if ((arguments->slots[1])->type == type__types__negative_integer) {
    {
    NODE *result__node = (NODE *)(from_bool(arguments->slots[0]->integer.value == arguments->slots[1]->integer.value));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  }
  {
    arguments = node_p;
    arguments->slots[0] = boolean_false;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__types__positive_large_integer__equal_1(void) {
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  long left_size, right_size;
  mp_limb_t *left_limbs, *right_limbs;
  if ((arguments->slots[1])->type == type__types__positive_large_integer) {
    left_size = arguments->slots[0]->large_integer.data->size;
    right_size = arguments->slots[1]->large_integer.data->size;
    if (left_size != right_size) {
    arguments = node_p;
    arguments->slots[0] = boolean_false;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
    left_limbs = arguments->slots[0]->large_integer.data->limbs;
    right_limbs = arguments->slots[1]->large_integer.data->limbs;
    {
    NODE *result__node = (NODE *)(from_bool(mpn_cmp(left_limbs, right_limbs, left_size) == 0));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__real) {
    left_limbs = arguments->slots[0]->large_integer.data->limbs;
    left_size = arguments->slots[0]->large_integer.data->size;
    {
    NODE *result__node = (NODE *)(from_bool(mpn_get_d(left_limbs, left_size, 1, 0) == arguments->slots[1]->real.value));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  }
  {
    arguments = node_p;
    arguments->slots[0] = boolean_false;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__types__positive_large_integer__equal_type_and_value_1(void) {
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  long left_size, right_size;
  mp_limb_t *left_limbs, *right_limbs;
  if ((arguments->slots[1])->type == type__types__positive_large_integer) {
    left_size = arguments->slots[0]->large_integer.data->size;
    right_size = arguments->slots[1]->large_integer.data->size;
    if (left_size != right_size) {
    arguments = node_p;
    arguments->slots[0] = boolean_false;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
    left_limbs = arguments->slots[0]->large_integer.data->limbs;
    right_limbs = arguments->slots[1]->large_integer.data->limbs;
    {
    NODE *result__node = (NODE *)(from_bool(mpn_cmp(left_limbs, right_limbs, left_size) == 0));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  }
  {
    arguments = node_p;
    arguments->slots[0] = boolean_false;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__types__negative_large_integer__equal_1(void) {
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  long left_size, right_size;
  mp_limb_t *left_limbs, *right_limbs;
  if ((arguments->slots[1])->type == type__types__negative_large_integer) {
    left_size = arguments->slots[0]->large_integer.data->size;
    right_size = arguments->slots[1]->large_integer.data->size;
    if (left_size != right_size) {
    arguments = node_p;
    arguments->slots[0] = boolean_false;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
    left_limbs = arguments->slots[0]->large_integer.data->limbs;
    right_limbs = arguments->slots[1]->large_integer.data->limbs;
    {
    NODE *result__node = (NODE *)(from_bool(mpn_cmp(left_limbs, right_limbs, left_size) == 0));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__real) {
    left_size = arguments->slots[0]->large_integer.data->size;
    left_limbs = arguments->slots[0]->large_integer.data->limbs;
    {
    NODE *result__node = (NODE *)(from_bool(mpn_get_d(left_limbs, left_size, -1, 0) == arguments->slots[1]->real.value));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  }
  {
    arguments = node_p;
    arguments->slots[0] = boolean_false;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__types__negative_large_integer__equal_type_and_value_1(void) {
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  long left_size, right_size;
  mp_limb_t *left_limbs, *right_limbs;
  if ((arguments->slots[1])->type == type__types__negative_large_integer) {
    left_size = arguments->slots[0]->large_integer.data->size;
    right_size = arguments->slots[1]->large_integer.data->size;
    if (left_size != right_size) {
    arguments = node_p;
    arguments->slots[0] = boolean_false;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
    left_limbs = arguments->slots[0]->large_integer.data->limbs;
    right_limbs = arguments->slots[1]->large_integer.data->limbs;
    {
    NODE *result__node = (NODE *)(from_bool(mpn_cmp(left_limbs, right_limbs, left_size) == 0));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  }
  {
    arguments = node_p;
    arguments->slots[0] = boolean_false;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__types__real__equal_1(void) {
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  if ((arguments->slots[1])->type == type__types__real) {
    {
    NODE *result__node = (NODE *)(from_bool(arguments->slots[0]->real.value == arguments->slots[1]->real.value));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__positive_integer) {
    {
    NODE *result__node = (NODE *)(from_bool(arguments->slots[0]->real.value == arguments->slots[1]->integer.value));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__negative_integer) {
    {
    NODE *result__node = (NODE *)(from_bool(-arguments->slots[0]->real.value == arguments->slots[1]->integer.value));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__positive_large_integer) {
    mp_limb_t *right_limbs = arguments->slots[1]->large_integer.data->limbs;
    long right_size = arguments->slots[1]->large_integer.data->size;
    {
    NODE *result__node = (NODE *)(from_bool(arguments->slots[0]->real.value == mpn_get_d(right_limbs, right_size, 1, 0)));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__negative_large_integer) {
    mp_limb_t *right_limbs = arguments->slots[1]->large_integer.data->limbs;
    long right_size = arguments->slots[1]->large_integer.data->size;
    {
    NODE *result__node = (NODE *)(from_bool(arguments->slots[0]->real.value == mpn_get_d(right_limbs, right_size, -1, 0)));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  }
  {
    arguments = node_p;
    arguments->slots[0] = boolean_false;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__types__real__equal_type_and_value_1(void) {
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  if ((arguments->slots[1])->type == type__types__real) {
    {
    NODE *result__node = (NODE *)(from_bool(arguments->slots[0]->real.value == arguments->slots[1]->real.value));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  }
  {
    arguments = node_p;
    arguments->slots[0] = boolean_false;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__types__positive_integer__less_1(void) {
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  if ((arguments->slots[1])->type == type__types__positive_integer) {
    {
    NODE *result__node = (NODE *)(from_bool(arguments->slots[0]->integer.value < arguments->slots[1]->integer.value));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__real) {
    {
    NODE *result__node = (NODE *)(from_bool(arguments->slots[0]->integer.value < arguments->slots[1]->real.value));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__positive_large_integer) {
    {
    arguments = node_p;
    arguments->slots[0] = boolean_true;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if (
    (arguments->slots[1])->type == type__types__negative_integer ||
    (arguments->slots[1])->type == type__types__negative_large_integer
  ) {
    {
    arguments = node_p;
    arguments->slots[0] = boolean_false;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  }
  {
    invalid_arguments_error();
  }
}
static void entry__types__negative_integer__less_1(void) {
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  if ((arguments->slots[1])->type == type__types__negative_integer) {
    {
    NODE *result__node = (NODE *)(from_bool(arguments->slots[0]->integer.value > arguments->slots[1]->integer.value));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__real) {
    {
    NODE *result__node = (NODE *)(from_bool(arguments->slots[0]->integer.value > -arguments->slots[1]->real.value));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if (
    (arguments->slots[1])->type == type__types__positive_integer ||
    (arguments->slots[1])->type == type__types__positive_large_integer
  ) {
    {
    arguments = node_p;
    arguments->slots[0] = boolean_true;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__negative_large_integer) {
    {
    arguments = node_p;
    arguments->slots[0] = boolean_false;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  }
  {
    invalid_arguments_error();
  }
}
static void entry__types__positive_large_integer__less_1(void) {
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  long left_size, right_size;
  mp_limb_t *left_limbs, *right_limbs;
  if ((arguments->slots[1])->type == type__types__positive_large_integer) {
    left_size = arguments->slots[0]->large_integer.data->size;
    right_size = arguments->slots[1]->large_integer.data->size;
    if (left_size < right_size) {
    arguments = node_p;
    arguments->slots[0] = boolean_true;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
    if (left_size > right_size) {
    arguments = node_p;
    arguments->slots[0] = boolean_false;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
    left_limbs = arguments->slots[0]->large_integer.data->limbs;
    right_limbs = arguments->slots[1]->large_integer.data->limbs;
    {
    NODE *result__node = (NODE *)(from_bool(mpn_cmp(left_limbs, right_limbs, left_size) < 0));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if (
    (arguments->slots[1])->type == type__types__positive_integer ||
    (arguments->slots[1])->type == type__types__negative_integer ||
    (arguments->slots[1])->type == type__types__negative_large_integer
  ) {
    {
    arguments = node_p;
    arguments->slots[0] = boolean_false;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__real) {
    left_limbs = arguments->slots[0]->large_integer.data->limbs;
    left_size = arguments->slots[0]->large_integer.data->size;
    {
    NODE *result__node = (NODE *)(from_bool(mpn_get_d(left_limbs, left_size, 1, 0) < arguments->slots[1]->real.value));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  }
  {
    invalid_arguments_error();
  }
}
static void entry__types__negative_large_integer__less_1(void) {
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  long left_size, right_size;
  mp_limb_t *left_limbs, *right_limbs;
  if ((arguments->slots[1])->type == type__types__negative_large_integer) {
    left_size = arguments->slots[0]->large_integer.data->size;
    right_size = arguments->slots[1]->large_integer.data->size;
    if (left_size > right_size) {
    arguments = node_p;
    arguments->slots[0] = boolean_true;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
    if (left_size < right_size) {
    arguments = node_p;
    arguments->slots[0] = boolean_false;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
    left_limbs = arguments->slots[0]->large_integer.data->limbs;
    right_limbs = arguments->slots[1]->large_integer.data->limbs;
    {
    NODE *result__node = (NODE *)(from_bool(mpn_cmp(left_limbs, right_limbs, left_size) > 0));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if (
    (arguments->slots[1])->type == type__types__positive_integer ||
    (arguments->slots[1])->type == type__types__negative_integer ||
    (arguments->slots[1])->type == type__types__positive_large_integer
  ) {
    {
    arguments = node_p;
    arguments->slots[0] = boolean_true;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__real) {
    left_limbs = arguments->slots[0]->large_integer.data->limbs;
    left_size = arguments->slots[0]->large_integer.data->size;
    {
    NODE *result__node = (NODE *)(from_bool(mpn_get_d(left_limbs, left_size, -1, 0) < arguments->slots[1]->real.value));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  }
  {
    invalid_arguments_error();
  }
}
static void entry__types__real__less_1(void) {
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  if ((arguments->slots[1])->type == type__types__real) {
    {
    NODE *result__node = (NODE *)(from_bool(arguments->slots[0]->real.value < arguments->slots[1]->real.value));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__positive_integer) {
    {
    NODE *result__node = (NODE *)(from_bool(arguments->slots[0]->real.value < arguments->slots[1]->integer.value));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__negative_integer) {
    {
    NODE *result__node = (NODE *)(from_bool(-arguments->slots[0]->real.value > arguments->slots[1]->integer.value));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__positive_large_integer) {
    mp_limb_t *right_limbs = arguments->slots[1]->large_integer.data->limbs;
    long right_size = arguments->slots[1]->large_integer.data->size;
    {
    NODE *result__node = (NODE *)(from_bool(arguments->slots[0]->real.value < mpn_get_d(right_limbs, right_size, 1, 0)));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if ((arguments->slots[1])->type == type__types__negative_large_integer) {
    mp_limb_t *right_limbs = arguments->slots[1]->large_integer.data->limbs;
    long right_size = arguments->slots[1]->large_integer.data->size;
    {
    NODE *result__node = (NODE *)(from_bool(arguments->slots[0]->real.value < mpn_get_d(right_limbs, right_size, -1, 0)));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  }
  {
    invalid_arguments_error();
  }
}

static mp_limb_t lshift(
  mp_limb_t *rp, const mp_limb_t *src_ptr,
  mp_size_t src_size, unsigned long int count
) {
  if (count != 0) return mpn_lshift(rp, src_ptr, src_size, count);
  memcpy(rp, src_ptr, src_size*sizeof(mp_limb_t));
  return 0;
}

static mp_limb_t rshift(
  mp_limb_t *rp, const mp_limb_t *src_ptr,
  mp_size_t src_size, unsigned long int count
) {
  if (count != 0) return mpn_rshift(rp, src_ptr, src_size, count);
  memcpy(rp, src_ptr, src_size*sizeof(mp_limb_t));
  return 0;
}
static void entry__types__positive_integer__shift_left_1(void) {
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  uint32_t shift = to_uint32(arguments->slots[1]);
  uint64_t value = arguments->slots[0]->integer.value;
  if (value == 0 || shift == 0) {
    NODE *result__node = (NODE *)(arguments->slots[0]);
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  if (value <= 0xffffffff && shift <= 32) {
    value <<= shift;
  } else if (shift < 64) {
    int n = shift;
    do {
      uint64_t old_value = value;
      value <<= 1;
      if (value < old_value) goto shift_overflow;
    } while (--n > 0);
  } else {
    shift_overflow:;
    int zero_limb_count = shift/GMP_LIMB_BITS;
    shift %= GMP_LIMB_BITS;
    long size = zero_limb_count+LIMBS_PER_INT64+1;
    LARGE_INTEGER_DATA *data =
      allocate(sizeof(LARGE_INTEGER_DATA)+size*sizeof(mp_limb_t));
    int i = 0;
    while (i < zero_limb_count) {
      data->limbs[i++] = 0;
    }
    value = arguments->slots[0]->integer.value;
    #if GMP_LIMB_BITS == 32
      data->limbs[i] = value & 0xffffffff;
      data->limbs[i+1] = value>>32;
      data->limbs[i+2] = lshift(data->limbs+i, data->limbs+i, 2, shift);
      while (data->limbs[size-1] == 0) {
        --size;
      }
    #else
      data->limbs[i] = value;
      data->limbs[i+1] = lshift(data->limbs+i, data->limbs+i, 1, shift);
    #endif
    data->size = size;
    {
    NODE *result__node = (NODE *)(create__types__positive_large_integer(data));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  }
  {
    NODE *result__node = (NODE *)(create__types__positive_integer(value));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__types__positive_large_integer__shift_left_1(void) {
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  uint32_t shift = to_uint32(arguments->slots[1]);
  if (shift == 0) {
    NODE *result__node = (NODE *)(arguments->slots[0]);
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  int zero_limb_count = shift/GMP_LIMB_BITS;
  shift %= GMP_LIMB_BITS;
  LARGE_INTEGER_DATA *data = arguments->slots[0]->large_integer.data;
  long size = data->size;
  long new_size = zero_limb_count+size+(shift == 0 ? 0 : 1);
  LARGE_INTEGER_DATA *new_data =
    allocate(sizeof(LARGE_INTEGER_DATA)+new_size*sizeof(mp_limb_t));
  int i = 0;
  while (i < zero_limb_count) {
    new_data->limbs[i++] = 0;
  }
  mp_limb_t overflow = lshift(new_data->limbs+i, data->limbs, size, shift);
  if (overflow != 0) {
    new_data->limbs[new_size-1] = overflow;
  } else if (shift != 0) {
    --new_size;
  }
  new_data->size = new_size;
  {
    NODE *result__node = (NODE *)(create__types__positive_large_integer(new_data));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__types__positive_integer__shift_right_1(void) {
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  uint32_t shift = to_uint32(arguments->slots[1]);
  if (shift >= 64) {
    arguments = node_p;
    arguments->slots[0] = zero;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  {
    NODE *result__node = (NODE *)(create__types__positive_integer(arguments->slots[0]->integer.value >> shift));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__types__positive_large_integer__shift_right_1(void) {
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  uint32_t shift = to_uint32(arguments->slots[1]);
  if (shift == 0) {
    NODE *result__node = (NODE *)(arguments->slots[0]);
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  int limb_count = shift/GMP_LIMB_BITS;
  shift %= GMP_LIMB_BITS;
  LARGE_INTEGER_DATA *data = arguments->slots[0]->large_integer.data;
  long size = data->size;
  long new_size = size-limb_count;
  if (new_size <= 0) {
    arguments = node_p;
    arguments->slots[0] = zero;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  if (new_size > LIMBS_PER_INT64) {
    LARGE_INTEGER_DATA *new_data =
      allocate(sizeof(LARGE_INTEGER_DATA)+new_size*sizeof(mp_limb_t));
    rshift(new_data->limbs, data->limbs+limb_count, new_size, shift);
    if (new_data->limbs[new_size-1] == 0) {
      --new_size;
    }
    if (new_size > LIMBS_PER_INT64) {
      new_data->size = new_size;
      {
    NODE *result__node = (NODE *)(create__types__positive_large_integer(new_data));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
    } else {
      uint64_t value = new_data->limbs[0];
      #if GMP_LIMB_BITS == 32
        if (new_size > 1) {
          value |= ((uint64_t)new_data->limbs[1])<<32;
        }
      #endif
      {
    NODE *result__node = (NODE *)(create__types__positive_integer(value));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
    }
  } else {
    uint64_t value = data->limbs[limb_count];
    #if GMP_LIMB_BITS == 32
      if (new_size > 1) {
        value |= ((uint64_t)data->limbs[limb_count+1])<<32;
      }
    #endif
    {
    NODE *result__node = (NODE *)(create__types__positive_integer(value>>shift));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  }
}
static void entry__types__positive_integer__bit_or_1(void) {
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  if ((arguments->slots[1])->type == type__types__positive_integer) {
    {
    NODE *result__node = (NODE *)(create__types__positive_integer(
        arguments->slots[0]->integer.value | arguments->slots[1]->integer.value));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  }
  {
    invalid_arguments_error();
  }
}
static void entry__types__positive_integer__bit_and_1(void) {
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  if ((arguments->slots[1])->type == type__types__positive_integer) {
    {
    NODE *result__node = (NODE *)(create__types__positive_integer(
        arguments->slots[0]->integer.value & arguments->slots[1]->integer.value));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  }
  {
    invalid_arguments_error();
  }
}
static void entry__types__positive_integer__bit_xor_1(void) {
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  if ((arguments->slots[1])->type == type__types__positive_integer) {
    {
    NODE *result__node = (NODE *)(create__types__positive_integer(
        arguments->slots[0]->integer.value ^ arguments->slots[1]->integer.value));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  }
  {
    invalid_arguments_error();
  }
}
static void entry__types__positive_integer__hash_1(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  uint32_t hash =
    (uint32_t)arguments->slots[0]->integer.value ^ (arguments->slots[0]->integer.value >> 32);
  hash *= 179234567;
  hash ^= hash >> 27 | hash << 5;
  //hash *= 257913241;
  //hash ^= hash >> 21 | hash << 11;
  {
    NODE *result__node = (NODE *)(from_uint32(hash));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__types__negative_integer__hash_1(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  uint32_t hash =
    (uint32_t)arguments->slots[0]->integer.value ^ (arguments->slots[0]->integer.value >> 32);
  hash *= 179234567;
  hash ^= hash >> 27 | hash << 5;
  //hash *= 326987239;
  //hash ^= hash >> 21 | hash << 11;
  {
    NODE *result__node = (NODE *)(from_uint32(hash));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__types__positive_integer__to_string_1(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  char buf[24];
  sprintf(buf, "%" PRIu64, arguments->slots[0]->integer.value);
  {
    NODE *result__node = (NODE *)(from_c_string(buf));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}

static long func__types__positive_integer___debug_string(NODE *node, int indent, int max_depth, char *buf) {
  return debug_print(indent, buf, "%" PRIu64, node->integer.value);
}
static void entry__types__negative_integer__to_string_1(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  char buf[24];
  sprintf(buf, "-%" PRIu64, arguments->slots[0]->integer.value);
  {
    NODE *result__node = (NODE *)(from_c_string(buf));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}

static long func__types__negative_integer___debug_string(NODE *node, int indent, int max_depth, char *buf) {
  return debug_print(indent, buf, "-%" PRIu64, node->integer.value);
}

static NODE *large_integer_to_string(int sign) {
  long size = arguments->slots[0]->large_integer.data->size;
  mp_limb_t *limbs =
    copy(arguments->slots[0]->large_integer.data->limbs, size*sizeof(mp_limb_t));
  /*if (size <= LIMBS_PER_INT64 || limbs[size-1] == 0) {
    {
  runtime_error("Invalid large integer!");
}
  }*/
  char *buf = allocate(ALLOCATION_SIZE(3*size*sizeof(mp_limb_t)))+1;
  size_t buf_size = mpn_get_str((unsigned char *)buf, 10, limbs, size);
  int i = 0;
  while (i < buf_size-1 && buf[i] == 0) ++i;
  buf += i;
  buf_size -= i;
  for (i = 0; i < buf_size; ++i) {
    buf[i] += '0';
  }
  if (sign < 0) {
    --buf;
    ++buf_size;
    *buf = '-';
  }
  return from_latin_1_string(buf, buf_size);
}
static void entry__types__positive_large_integer__to_string_1(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  {
    NODE *result__node = (NODE *)(large_integer_to_string(1));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}

static long func__types__positive_large_integer___debug_string(NODE *node, int indent, int max_depth, char *buf) {
  return debug_print(indent, buf, "<positive large integer>");
}
static void entry__types__negative_large_integer__to_string_1(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  {
    NODE *result__node = (NODE *)(large_integer_to_string(-1));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}

static long func__types__negetive_large_integer___debug_string(NODE *node, int indent, int max_depth, char *buf) {
  return debug_print(indent, buf, "<negative large integer>");
}
static void entry__types__real__to_string_1(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  char buf[24];
  sprintf(buf, "%.15g", arguments->slots[0]->real.value);
  {
    NODE *result__node = (NODE *)(from_c_string(buf));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}

static long func__types__real___debug_string(NODE *node, int indent, int max_depth, char *buf) {
  return debug_print(indent, buf, "%.15g", node->real.value);
}
static void entry__std__is_odd_1(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // n: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 2195: ... n & 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* n */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__bit_and();
  func = myself->type;
  frame->cont = cont__std__is_odd_2;
}
static void cont__std__is_odd_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 2195: ... n & 1 == 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__std__is_odd_3;
}
static void cont__std__is_odd_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 2195: -> n & 1 == 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__is_even_1(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // n: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 2203: ... n & 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* n */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__bit_and();
  func = myself->type;
  frame->cont = cont__std__is_even_2;
}
static void cont__std__is_even_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 2203: ... n & 1 == 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__std__is_even_3;
}
static void cont__std__is_even_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 2203: -> n & 1 == 0
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__bin_1(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // val: 0
  // size: 1
  // return: 2
  // str: 3
  frame->slots[2] /* return */ = create_continuation();
  frame->slots[3] /* str */ = create_cell();
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  if (argument_count > 2) {
    too_many_arguments_error();
    return;
  }
  frame->slots[0] /* val */ = create_cell_with_contents(arguments->slots[0]);
  switch(argument_count) {
    default: frame->slots[1] /* size */ = arguments->slots[1];
    case 1:;
  }
  switch(argument_count) {
    case 1: frame->slots[1] /* size */ = undefined;
  }
  // 2220: ... val == 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* val */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__std__bin_2;
}
static void cont__std__bin_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 2220: ... :
  // 2221:   if
  // 2222:     size.is_defined:
  // 2223:       return dup("0" size)
  // 2224:     :
  // 2225:       return "0"
  frame->slots[5] /* temp__2 */ = create_closure(entry__std__bin_3, 0);
  // 2220: if val == 0:
  // 2221:   if
  // 2222:     size.is_defined:
  // 2223:       return dup("0" size)
  // 2224:     :
  // 2225:       return "0"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__std__bin_9;
}
static void entry__std__bin_5(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // return: 0
  // size: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* return */
  frame->slots[1] = myself->closure.frame->slots[0]; /* size */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 2223: ... dup("0" size)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__578a5af303e9cd1;
  arguments->slots[1] = frame->slots[1] /* size */;
  result_count = 1;
  myself = get__dup();
  func = myself->type;
  frame->cont = cont__std__bin_7;
}
static void cont__std__bin_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 2223: return dup("0" size)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__bin_8(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 2225: return "0"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__578a5af303e9cd1;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__bin_3(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // size: 0
  // return: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* size */
  frame->slots[1] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 2222: size.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* size */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__std__bin_4;
}
static void cont__std__bin_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 2222: ... :
  // 2223:   return dup("0" size)
  frame->slots[3] /* temp__2 */ = create_closure(entry__std__bin_5, 0);
  // 2224: :
  // 2225:   return "0"
  frame->slots[4] /* temp__3 */ = create_closure(entry__std__bin_8, 0);
  // 2221: if
  // 2222:   size.is_defined:
  // 2223:     return dup("0" size)
  // 2224:   :
  // 2225:     return "0"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  arguments->slots[2] = frame->slots[4] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__std__bin_9(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 2226: $$str ""
  ((CELL *)frame->slots[3])->contents /* str */ = empty_string;
  // 2227: ... -> val > 0:
  // 2228:   put &str '0'+(val & 1)
  // 2229:   !val val >> 1
  frame->slots[4] /* temp__1 */ = create_closure(entry__std__bin_10, 0);
  // 2227: while -> val > 0:
  // 2228:   put &str '0'+(val & 1)
  // 2229:   !val val >> 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__while();
  func = myself->type;
  frame->cont = cont__std__bin_17;
}
static void entry__std__bin_12(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // str: 0
  // val: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* str */
  frame->slots[1] = myself->closure.frame->slots[0]; /* val */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 2228: ... val & 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* val */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__bit_and();
  func = myself->type;
  frame->cont = cont__std__bin_13;
}
static void cont__std__bin_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 2228: ... '0'+(val & 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__48;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__std__bin_14;
}
static void cont__std__bin_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 2228: put &str '0'+(val & 1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* str */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__put();
  func = myself->type;
  frame->cont = cont__std__bin_15;
}
static void cont__std__bin_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* str */ = arguments->slots[0];
  // 2229: !val val >> 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* val */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__shift_right();
  func = myself->type;
  frame->cont = cont__std__bin_16;
}
static void cont__std__bin_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* val */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__bin_10(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // val: 0
  // str: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* val */
  frame->slots[1] = myself->closure.frame->slots[3]; /* str */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 2227: ... val > 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* val */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__std__bin_11;
}
static void cont__std__bin_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 2227: ... :
  // 2228:   put &str '0'+(val & 1)
  // 2229:   !val val >> 1
  frame->slots[3] /* temp__2 */ = create_closure(entry__std__bin_12, 0);
  // 2227: ... -> val > 0:
  // 2228:   put &str '0'+(val & 1)
  // 2229:   !val val >> 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__std__bin_17(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 2230: ... size.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* size */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__std__bin_18;
}
static void cont__std__bin_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 2230: ... : return pad_left(str size "0")
  frame->slots[5] /* temp__2 */ = create_closure(entry__std__bin_19, 0);
  // 2230: if size.is_defined: return pad_left(str size "0")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__std__bin_21;
}
static void entry__std__bin_19(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // return: 0
  // str: 1
  // size: 2
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  frame->slots[1] = myself->closure.frame->slots[3]; /* str */
  frame->slots[2] = myself->closure.frame->slots[1]; /* size */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 2230: ... pad_left(str size "0")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* str */;
  arguments->slots[1] = frame->slots[2] /* size */;
  arguments->slots[2] = string__578a5af303e9cd1;
  result_count = 1;
  myself = get__pad_left();
  func = myself->type;
  frame->cont = cont__std__bin_20;
}
static void cont__std__bin_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 2230: ... return pad_left(str size "0")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__std__bin_21(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 2231: -> str
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* str */;
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__std__oct_1(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // val: 0
  // size: 1
  // return: 2
  // str: 3
  frame->slots[2] /* return */ = create_continuation();
  frame->slots[3] /* str */ = create_cell();
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  if (argument_count > 2) {
    too_many_arguments_error();
    return;
  }
  frame->slots[0] /* val */ = create_cell_with_contents(arguments->slots[0]);
  switch(argument_count) {
    default: frame->slots[1] /* size */ = arguments->slots[1];
    case 1:;
  }
  switch(argument_count) {
    case 1: frame->slots[1] /* size */ = undefined;
  }
  // 2248: ... val == 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* val */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__std__oct_2;
}
static void cont__std__oct_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 2248: ... :
  // 2249:   if
  // 2250:     size.is_defined:
  // 2251:       return dup("0" size)
  // 2252:     :
  // 2253:       return "0"
  frame->slots[5] /* temp__2 */ = create_closure(entry__std__oct_3, 0);
  // 2248: if val == 0:
  // 2249:   if
  // 2250:     size.is_defined:
  // 2251:       return dup("0" size)
  // 2252:     :
  // 2253:       return "0"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__std__oct_8;
}
static void entry__std__oct_5(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // return: 0
  // size: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* return */
  frame->slots[1] = myself->closure.frame->slots[0]; /* size */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 2251: ... dup("0" size)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__578a5af303e9cd1;
  arguments->slots[1] = frame->slots[1] /* size */;
  result_count = 1;
  myself = get__dup();
  func = myself->type;
  frame->cont = cont__std__oct_6;
}
static void cont__std__oct_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 2251: return dup("0" size)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__oct_7(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 2253: return "0"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__578a5af303e9cd1;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__oct_3(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // size: 0
  // return: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* size */
  frame->slots[1] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 2250: size.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* size */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__std__oct_4;
}
static void cont__std__oct_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 2250: ... :
  // 2251:   return dup("0" size)
  frame->slots[3] /* temp__2 */ = create_closure(entry__std__oct_5, 0);
  // 2252: :
  // 2253:   return "0"
  frame->slots[4] /* temp__3 */ = create_closure(entry__std__oct_7, 0);
  // 2249: if
  // 2250:   size.is_defined:
  // 2251:     return dup("0" size)
  // 2252:   :
  // 2253:     return "0"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  arguments->slots[2] = frame->slots[4] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__std__oct_8(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 2254: $$str ""
  ((CELL *)frame->slots[3])->contents /* str */ = empty_string;
  // 2255: ... -> val > 0:
  // 2256:   put &str '0'+(val & 0x07)
  // 2257:   !val val >> 3
  frame->slots[4] /* temp__1 */ = create_closure(entry__std__oct_9, 0);
  // 2255: while -> val > 0:
  // 2256:   put &str '0'+(val & 0x07)
  // 2257:   !val val >> 3
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__while();
  func = myself->type;
  frame->cont = cont__std__oct_16;
}
static void entry__std__oct_11(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // str: 0
  // val: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* str */
  frame->slots[1] = myself->closure.frame->slots[0]; /* val */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 2256: ... val & 0x07
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* val */;
  arguments->slots[1] = number__0x07;
  result_count = 1;
  myself = get__std__bit_and();
  func = myself->type;
  frame->cont = cont__std__oct_12;
}
static void cont__std__oct_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 2256: ... '0'+(val & 0x07
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__48;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__std__oct_13;
}
static void cont__std__oct_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 2256: put &str '0'+(val & 0x07)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* str */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__put();
  func = myself->type;
  frame->cont = cont__std__oct_14;
}
static void cont__std__oct_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* str */ = arguments->slots[0];
  // 2257: !val val >> 3
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* val */;
  arguments->slots[1] = number__3;
  result_count = 1;
  myself = get__std__shift_right();
  func = myself->type;
  frame->cont = cont__std__oct_15;
}
static void cont__std__oct_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* val */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__oct_9(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // val: 0
  // str: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* val */
  frame->slots[1] = myself->closure.frame->slots[3]; /* str */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 2255: ... val > 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* val */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__std__oct_10;
}
static void cont__std__oct_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 2255: ... :
  // 2256:   put &str '0'+(val & 0x07)
  // 2257:   !val val >> 3
  frame->slots[3] /* temp__2 */ = create_closure(entry__std__oct_11, 0);
  // 2255: ... -> val > 0:
  // 2256:   put &str '0'+(val & 0x07)
  // 2257:   !val val >> 3
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__std__oct_16(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 2258: ... size.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* size */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__std__oct_17;
}
static void cont__std__oct_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 2258: ... : return pad_left(str size "0")
  frame->slots[5] /* temp__2 */ = create_closure(entry__std__oct_18, 0);
  // 2258: if size.is_defined: return pad_left(str size "0")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__std__oct_20;
}
static void entry__std__oct_18(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // return: 0
  // str: 1
  // size: 2
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  frame->slots[1] = myself->closure.frame->slots[3]; /* str */
  frame->slots[2] = myself->closure.frame->slots[1]; /* size */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 2258: ... pad_left(str size "0")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* str */;
  arguments->slots[1] = frame->slots[2] /* size */;
  arguments->slots[2] = string__578a5af303e9cd1;
  result_count = 1;
  myself = get__pad_left();
  func = myself->type;
  frame->cont = cont__std__oct_19;
}
static void cont__std__oct_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 2258: ... return pad_left(str size "0")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__std__oct_20(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 2259: -> str
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* str */;
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__std__hex_1(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // val: 0
  // size: 1
  // return: 2
  // str: 3
  frame->slots[2] /* return */ = create_continuation();
  frame->slots[3] /* str */ = create_cell();
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  if (argument_count > 2) {
    too_many_arguments_error();
    return;
  }
  frame->slots[0] /* val */ = create_cell_with_contents(arguments->slots[0]);
  switch(argument_count) {
    default: frame->slots[1] /* size */ = arguments->slots[1];
    case 1:;
  }
  switch(argument_count) {
    case 1: frame->slots[1] /* size */ = undefined;
  }
  // 2276: ... val == 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* val */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__std__hex_2;
}
static void cont__std__hex_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 2276: ... :
  // 2277:   if
  // 2278:     size.is_defined:
  // 2279:       return dup("0" size)
  // 2280:     :
  // 2281:       return "0"
  frame->slots[5] /* temp__2 */ = create_closure(entry__std__hex_3, 0);
  // 2276: if val == 0:
  // 2277:   if
  // 2278:     size.is_defined:
  // 2279:       return dup("0" size)
  // 2280:     :
  // 2281:       return "0"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__std__hex_8;
}
static void entry__std__hex_5(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // return: 0
  // size: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* return */
  frame->slots[1] = myself->closure.frame->slots[0]; /* size */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 2279: ... dup("0" size)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__578a5af303e9cd1;
  arguments->slots[1] = frame->slots[1] /* size */;
  result_count = 1;
  myself = get__dup();
  func = myself->type;
  frame->cont = cont__std__hex_6;
}
static void cont__std__hex_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 2279: return dup("0" size)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__hex_7(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 2281: return "0"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__578a5af303e9cd1;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__hex_3(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // size: 0
  // return: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* size */
  frame->slots[1] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 2278: size.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* size */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__std__hex_4;
}
static void cont__std__hex_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 2278: ... :
  // 2279:   return dup("0" size)
  frame->slots[3] /* temp__2 */ = create_closure(entry__std__hex_5, 0);
  // 2280: :
  // 2281:   return "0"
  frame->slots[4] /* temp__3 */ = create_closure(entry__std__hex_7, 0);
  // 2277: if
  // 2278:   size.is_defined:
  // 2279:     return dup("0" size)
  // 2280:   :
  // 2281:     return "0"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  arguments->slots[2] = frame->slots[4] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__std__hex_8(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 2282: $$str ""
  ((CELL *)frame->slots[3])->contents /* str */ = empty_string;
  // 2283: ... -> val > 0:
  // 2284:   $$hex_digit val & 0x0f
  // 2285:   if
  // 2286:     hex_digit >= 10:
  // 2287:       !hex_digit 'a'+hex_digit-10
  // 2288:     :
  // 2289:       !hex_digit '0'+hex_digit
  // 2290:   put &str hex_digit
  // 2291:   !val val >> 4
  frame->slots[4] /* temp__1 */ = create_closure(entry__std__hex_9, 0);
  // 2283: while -> val > 0:
  // 2284:   $$hex_digit val & 0x0f
  // 2285:   if
  // 2286:     hex_digit >= 10:
  // 2287:       !hex_digit 'a'+hex_digit-10
  // 2288:     :
  // 2289:       !hex_digit '0'+hex_digit
  // 2290:   put &str hex_digit
  // 2291:   !val val >> 4
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__while();
  func = myself->type;
  frame->cont = cont__std__hex_23;
}
static void entry__std__hex_11(void) {
  allocate_initialized_frame_gc(2, 7);
  // slot allocations:
  // val: 0
  // str: 1
  // hex_digit: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* val */
  frame->slots[1] = myself->closure.frame->slots[1]; /* str */
  frame->slots[2] /* hex_digit */ = create_cell();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 2284: $$hex_digit val & 0x0f
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* val */;
  arguments->slots[1] = number__0x0f;
  result_count = 1;
  myself = get__std__bit_and();
  func = myself->type;
  frame->cont = cont__std__hex_12;
}
static void cont__std__hex_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* hex_digit */ = arguments->slots[0];
  // 2286: hex_digit >= 10
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* hex_digit */;
  arguments->slots[1] = number__10;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__std__hex_13;
}
static void cont__std__hex_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 2286: hex_digit >= 10
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__std__hex_14;
}
static void cont__std__hex_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 2286: ... :
  // 2287:   !hex_digit 'a'+hex_digit-10
  frame->slots[5] /* temp__3 */ = create_closure(entry__std__hex_15, 0);
  // 2288: :
  // 2289:   !hex_digit '0'+hex_digit
  frame->slots[6] /* temp__4 */ = create_closure(entry__std__hex_18, 0);
  // 2285: if
  // 2286:   hex_digit >= 10:
  // 2287:     !hex_digit 'a'+hex_digit-10
  // 2288:   :
  // 2289:     !hex_digit '0'+hex_digit
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  arguments->slots[2] = frame->slots[6] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__std__hex_20;
}
static void entry__std__hex_15(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // hex_digit: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* hex_digit */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 2287: ... 'a'+hex_digit
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__97;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* hex_digit */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__std__hex_16;
}
static void cont__std__hex_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 2287: !hex_digit 'a'+hex_digit-10
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = number__10;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__std__hex_17;
}
static void cont__std__hex_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* hex_digit */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__hex_18(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // hex_digit: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* hex_digit */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 2289: !hex_digit '0'+hex_digit
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__48;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* hex_digit */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__std__hex_19;
}
static void cont__std__hex_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* hex_digit */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__std__hex_20(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 2290: put &str hex_digit
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* str */;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* hex_digit */;
  result_count = 1;
  myself = get__put();
  func = myself->type;
  frame->cont = cont__std__hex_21;
}
static void cont__std__hex_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* str */ = arguments->slots[0];
  // 2291: !val val >> 4
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* val */;
  arguments->slots[1] = number__4;
  result_count = 1;
  myself = get__std__shift_right();
  func = myself->type;
  frame->cont = cont__std__hex_22;
}
static void cont__std__hex_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* val */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__hex_9(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // val: 0
  // str: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* val */
  frame->slots[1] = myself->closure.frame->slots[3]; /* str */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 2283: ... val > 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* val */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__std__hex_10;
}
static void cont__std__hex_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 2283: ... :
  // 2284:   $$hex_digit val & 0x0f
  // 2285:   if
  // 2286:     hex_digit >= 10:
  // 2287:       !hex_digit 'a'+hex_digit-10
  // 2288:     :
  // 2289:       !hex_digit '0'+hex_digit
  // 2290:   put &str hex_digit
  // 2291:   !val val >> 4
  frame->slots[3] /* temp__2 */ = create_closure(entry__std__hex_11, 0);
  // 2283: ... -> val > 0:
  // 2284:   $$hex_digit val & 0x0f
  // 2285:   if
  // 2286:     hex_digit >= 10:
  // 2287:       !hex_digit 'a'+hex_digit-10
  // 2288:     :
  // 2289:       !hex_digit '0'+hex_digit
  // 2290:   put &str hex_digit
  // 2291:   !val val >> 4
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__std__hex_23(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 2292: ... size.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* size */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__std__hex_24;
}
static void cont__std__hex_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 2292: ... : return pad_left(str size "0")
  frame->slots[5] /* temp__2 */ = create_closure(entry__std__hex_25, 0);
  // 2292: if size.is_defined: return pad_left(str size "0")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__std__hex_27;
}
static void entry__std__hex_25(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // return: 0
  // str: 1
  // size: 2
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  frame->slots[1] = myself->closure.frame->slots[3]; /* str */
  frame->slots[2] = myself->closure.frame->slots[1]; /* size */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 2292: ... pad_left(str size "0")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* str */;
  arguments->slots[1] = frame->slots[2] /* size */;
  arguments->slots[2] = string__578a5af303e9cd1;
  result_count = 1;
  myself = get__pad_left();
  func = myself->type;
  frame->cont = cont__std__hex_26;
}
static void cont__std__hex_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 2292: ... return pad_left(str size "0")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__std__hex_27(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 2293: -> str
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* str */;
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__types__integer__to_integer_1(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // value: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 2301: -> value
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* value */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__real__to_integer_1(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  long val = floor(arguments->slots[0]->real.value);
  {
    NODE *result__node = (NODE *)(from_long(val));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__types__number__floor_1(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // self: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 2318: -> self
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__number__ceil_1(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // self: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 2326: -> self
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__number__round_1(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // self: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 2334: -> self
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__real__floor_1(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  {
    NODE *result__node = (NODE *)(create__types__real(floor(arguments->slots[0]->real.value)));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__types__real__ceil_1(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  {
    NODE *result__node = (NODE *)(create__types__real(ceil(arguments->slots[0]->real.value)));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__types__real__round_1(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  {
    NODE *result__node = (NODE *)(create__types__real(round(arguments->slots[0]->real.value)));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__types__real__ln_1(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  {
    NODE *result__node = (NODE *)(create__types__real(log(arguments->slots[0]->real.value)));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
EXPORT void collect__basic__types__number(void) {
  var.std__integer_plus_me = collect_node(var.std__integer_plus_me);
  var.std__integer_minus_me = collect_node(var.std__integer_minus_me);
  var.std__integer_times_me = collect_node(var.std__integer_times_me);
  var.std__integer_over_me = collect_node(var.std__integer_over_me);
  var.std__real_plus_me = collect_node(var.std__real_plus_me);
  var.std__real_minus_me = collect_node(var.std__real_minus_me);
  var.std__real_times_me = collect_node(var.std__real_times_me);
  var.std__real_over_me = collect_node(var.std__real_over_me);
  var.std__is_a_number = collect_node(var.std__is_a_number);
  var.std__is_an_integer = collect_node(var.std__is_an_integer);
  var.std__is_a_real = collect_node(var.std__is_a_real);
  var.std__floor = collect_node(var.std__floor);
  var.std__ceil = collect_node(var.std__ceil);
  var.std__round = collect_node(var.std__round);
  var.std__ln = collect_node(var.std__ln);
  var.types__number = collect_node(var.types__number);
  collect_static_attributes(&attributes__types__number);
  var.types__integer = collect_node(var.types__integer);
  collect_static_attributes(&attributes__types__integer);
  var.types__positive_integer = collect_node(var.types__positive_integer);
  collect_static_attributes(&attributes__types__positive_integer);
  var.std__zero = collect_node(var.std__zero);
  var.types__negative_integer = collect_node(var.types__negative_integer);
  collect_static_attributes(&attributes__types__negative_integer);
  var.types__positive_large_integer = collect_node(var.types__positive_large_integer);
  collect_static_attributes(&attributes__types__positive_large_integer);
  var.types__negative_large_integer = collect_node(var.types__negative_large_integer);
  collect_static_attributes(&attributes__types__negative_large_integer);
  var.types__real = collect_node(var.types__real);
  collect_static_attributes(&attributes__types__real);
  var.std__is_odd = collect_node(var.std__is_odd);
  var.std__is_even = collect_node(var.std__is_even);
  var.std__bin = collect_node(var.std__bin);
  var.std__oct = collect_node(var.std__oct);
  var.std__hex = collect_node(var.std__hex);
}

static int already_run_phase_1 = false;

EXPORT void phase_1__basic__types__number(void) {
  if (already_run_phase_1) return;
  already_run_phase_1 = true;
  register_module_info(&module_info);
  define_c_function("from_uint32", runtime__from_uint32);
  define_c_function("from_int", runtime__from_int);
  define_c_function("from_long", runtime__from_long);
  define_c_function("from_int64", runtime__from_int64);
  define_c_function("from_uint64", runtime__from_uint64);
  define_c_function("from_digit_string", runtime__from_digit_string);
  define_c_function("from_double", runtime__from_double);
}

static int already_run_phase_2 = false;

EXPORT void phase_2__basic__types__number(void) {
  if (already_run_phase_2) return;
  already_run_phase_2 = true;
  set_module("basic__types__number");
  number__0 = from_uint32(0U);
  number__3 = from_uint32(3U);
  character__48 = from_uchar32(48);
  number__4 = from_uint32(4U);
  number__0x0f = from_uint32(15U);
  character__97 = from_uchar32(97);
  number__1 = from_uint32(1U);
  number__10 = from_uint32(10U);
  number__0x07 = from_uint32(7U);
  define_polymorphic_function("std", "integer_plus_me", get__std__integer_plus_me, &poly_idx__std__integer_plus_me, &var.std__integer_plus_me);
  define_polymorphic_function("std", "integer_minus_me", get__std__integer_minus_me, &poly_idx__std__integer_minus_me, &var.std__integer_minus_me);
  define_polymorphic_function("std", "integer_times_me", get__std__integer_times_me, &poly_idx__std__integer_times_me, &var.std__integer_times_me);
  define_polymorphic_function("std", "integer_over_me", get__std__integer_over_me, &poly_idx__std__integer_over_me, &var.std__integer_over_me);
  define_polymorphic_function("std", "real_plus_me", get__std__real_plus_me, &poly_idx__std__real_plus_me, &var.std__real_plus_me);
  define_polymorphic_function("std", "real_minus_me", get__std__real_minus_me, &poly_idx__std__real_minus_me, &var.std__real_minus_me);
  define_polymorphic_function("std", "real_times_me", get__std__real_times_me, &poly_idx__std__real_times_me, &var.std__real_times_me);
  define_polymorphic_function("std", "real_over_me", get__std__real_over_me, &poly_idx__std__real_over_me, &var.std__real_over_me);
  define_polymorphic_function("std", "is_a_number", get__std__is_a_number, &poly_idx__std__is_a_number, &var.std__is_a_number);
  define_polymorphic_function("std", "is_an_integer", get__std__is_an_integer, &poly_idx__std__is_an_integer, &var.std__is_an_integer);
  define_polymorphic_function("std", "is_a_real", get__std__is_a_real, &poly_idx__std__is_a_real, &var.std__is_a_real);
  define_polymorphic_function("std", "floor", get__std__floor, &poly_idx__std__floor, &var.std__floor);
  define_polymorphic_function("std", "ceil", get__std__ceil, &poly_idx__std__ceil, &var.std__ceil);
  define_polymorphic_function("std", "round", get__std__round, &poly_idx__std__round, &var.std__round);
  define_polymorphic_function("std", "ln", get__std__ln, &poly_idx__std__ln, &var.std__ln);
  func__types__positive_integer__negate_1 = create_function(entry__types__positive_integer__negate_1, 1);
  func__types__negative_integer__negate_1 = create_function(entry__types__negative_integer__negate_1, 1);
  func__types__positive_large_integer__negate_1 = create_function(entry__types__positive_large_integer__negate_1, 1);
  func__types__negative_large_integer__negate_1 = create_function(entry__types__negative_large_integer__negate_1, 1);
  func__types__real__negate_1 = create_function(entry__types__real__negate_1, 1);
  func__types__positive_integer__plus_1 = create_function(entry__types__positive_integer__plus_1, 2);
  func__types__positive_integer__minus_1 = create_function(entry__types__positive_integer__minus_1, 2);
  func__types__negative_integer__plus_1 = create_function(entry__types__negative_integer__plus_1, 2);
  func__types__negative_integer__minus_1 = create_function(entry__types__negative_integer__minus_1, 2);
  func__types__positive_large_integer__plus_1 = create_function(entry__types__positive_large_integer__plus_1, 2);
  func__types__positive_large_integer__minus_1 = create_function(entry__types__positive_large_integer__minus_1, 2);
  func__types__negative_large_integer__plus_1 = create_function(entry__types__negative_large_integer__plus_1, 2);
  func__types__negative_large_integer__minus_1 = create_function(entry__types__negative_large_integer__minus_1, 2);
  func__types__real__plus_1 = create_function(entry__types__real__plus_1, 2);
  func__types__real__minus_1 = create_function(entry__types__real__minus_1, 2);
  func__types__positive_integer__times_1 = create_function(entry__types__positive_integer__times_1, 2);
  func__types__negative_integer__times_1 = create_function(entry__types__negative_integer__times_1, 2);
  func__types__positive_large_integer__times_1 = create_function(entry__types__positive_large_integer__times_1, 2);
  func__types__negative_large_integer__times_1 = create_function(entry__types__negative_large_integer__times_1, 2);
  func__types__real__times_1 = create_function(entry__types__real__times_1, 2);
  func__types__positive_integer__over_1 = create_function(entry__types__positive_integer__over_1, 2);
  func__types__negative_integer__over_1 = create_function(entry__types__negative_integer__over_1, 2);
  func__types__positive_large_integer__over_1 = create_function(entry__types__positive_large_integer__over_1, 2);
  func__types__negative_large_integer__over_1 = create_function(entry__types__negative_large_integer__over_1, 2);
  func__types__real__over_1 = create_function(entry__types__real__over_1, 2);
  func__types__positive_integer__div_1 = create_function(entry__types__positive_integer__div_1, 2);
  func__types__positive_integer__mod_1 = create_function(entry__types__positive_integer__mod_1, 2);
  func__types__positive_integer__equal_1 = create_function(entry__types__positive_integer__equal_1, 2);
  func__types__positive_integer__equal_type_and_value_1 = create_function(entry__types__positive_integer__equal_type_and_value_1, 2);
  func__types__negative_integer__equal_1 = create_function(entry__types__negative_integer__equal_1, 2);
  func__types__negative_integer__equal_type_and_value_1 = create_function(entry__types__negative_integer__equal_type_and_value_1, 2);
  func__types__positive_large_integer__equal_1 = create_function(entry__types__positive_large_integer__equal_1, 2);
  func__types__positive_large_integer__equal_type_and_value_1 = create_function(entry__types__positive_large_integer__equal_type_and_value_1, 2);
  func__types__negative_large_integer__equal_1 = create_function(entry__types__negative_large_integer__equal_1, 2);
  func__types__negative_large_integer__equal_type_and_value_1 = create_function(entry__types__negative_large_integer__equal_type_and_value_1, 2);
  func__types__real__equal_1 = create_function(entry__types__real__equal_1, 2);
  func__types__real__equal_type_and_value_1 = create_function(entry__types__real__equal_type_and_value_1, 2);
  func__types__positive_integer__less_1 = create_function(entry__types__positive_integer__less_1, 2);
  func__types__negative_integer__less_1 = create_function(entry__types__negative_integer__less_1, 2);
  func__types__positive_large_integer__less_1 = create_function(entry__types__positive_large_integer__less_1, 2);
  func__types__negative_large_integer__less_1 = create_function(entry__types__negative_large_integer__less_1, 2);
  func__types__real__less_1 = create_function(entry__types__real__less_1, 2);
  func__types__positive_integer__shift_left_1 = create_function(entry__types__positive_integer__shift_left_1, 2);
  func__types__positive_large_integer__shift_left_1 = create_function(entry__types__positive_large_integer__shift_left_1, 2);
  func__types__positive_integer__shift_right_1 = create_function(entry__types__positive_integer__shift_right_1, 2);
  func__types__positive_large_integer__shift_right_1 = create_function(entry__types__positive_large_integer__shift_right_1, 2);
  func__types__positive_integer__bit_or_1 = create_function(entry__types__positive_integer__bit_or_1, 2);
  func__types__positive_integer__bit_and_1 = create_function(entry__types__positive_integer__bit_and_1, 2);
  func__types__positive_integer__bit_xor_1 = create_function(entry__types__positive_integer__bit_xor_1, 2);
  func__types__positive_integer__hash_1 = create_function(entry__types__positive_integer__hash_1, 1);
  func__types__negative_integer__hash_1 = create_function(entry__types__negative_integer__hash_1, 1);
  func__types__positive_integer__to_string_1 = create_function(entry__types__positive_integer__to_string_1, 1);
  func__types__negative_integer__to_string_1 = create_function(entry__types__negative_integer__to_string_1, 1);
  func__types__positive_large_integer__to_string_1 = create_function(entry__types__positive_large_integer__to_string_1, 1);
  func__types__negative_large_integer__to_string_1 = create_function(entry__types__negative_large_integer__to_string_1, 1);
  func__types__real__to_string_1 = create_function(entry__types__real__to_string_1, 1);
  func__std__is_odd_1 = create_function(entry__std__is_odd_1, 1);
  func__std__is_even_1 = create_function(entry__std__is_even_1, 1);
  string__578a5af303e9cd1 = from_latin_1_string("0", 1);
  func__std__bin_1 = create_function(entry__std__bin_1, -1);
  func__std__oct_1 = create_function(entry__std__oct_1, -1);
  func__std__hex_1 = create_function(entry__std__hex_1, -1);
  func__types__integer__to_integer_1 = create_function(entry__types__integer__to_integer_1, 1);
  func__types__real__to_integer_1 = create_function(entry__types__real__to_integer_1, 1);
  func__types__number__floor_1 = create_function(entry__types__number__floor_1, 1);
  func__types__number__ceil_1 = create_function(entry__types__number__ceil_1, 1);
  func__types__number__round_1 = create_function(entry__types__number__round_1, 1);
  func__types__real__floor_1 = create_function(entry__types__real__floor_1, 1);
  func__types__real__ceil_1 = create_function(entry__types__real__ceil_1, 1);
  func__types__real__round_1 = create_function(entry__types__real__round_1, 1);
  func__types__real__ln_1 = create_function(entry__types__real__ln_1, 1);
}

static int already_run_phase_3 = false;

EXPORT void phase_3__basic__types__number(void) {
  if (already_run_phase_3) return;
  already_run_phase_3 = true;
  set_module("basic__types__number");
  set_used_namespaces(used_namespaces);
  var.types__number = create_future_with_prototype(create__types__number());
  define_single_assign_static("types", "number", get__types__number, &var.types__number);
  var.types__integer = create_future_with_prototype(create__types__integer());
  define_single_assign_static("types", "integer", get__types__integer, &var.types__integer);
  var.types__positive_integer = create_future_with_prototype(create__types__positive_integer(1));
  define_single_assign_static("types", "positive_integer", get__types__positive_integer, &var.types__positive_integer);
  var.std__zero = create__types__positive_integer(0);
  define_single_assign_static("std", "zero", get__std__zero, &var.std__zero);
  var.types__negative_integer = create_future_with_prototype(create__types__negative_integer(1));
  define_single_assign_static("types", "negative_integer", get__types__negative_integer, &var.types__negative_integer);
  var.types__positive_large_integer = create_future_with_prototype(create__types__positive_large_integer(NULL));
  define_single_assign_static("types", "positive_large_integer", get__types__positive_large_integer, &var.types__positive_large_integer);
  var.types__negative_large_integer = create_future_with_prototype(create__types__negative_large_integer(NULL));
  define_single_assign_static("types", "negative_large_integer", get__types__negative_large_integer, &var.types__negative_large_integer);
  var.types__real = create_future_with_prototype(create__types__real(0.0));
  define_single_assign_static("types", "real", get__types__real, &var.types__real);
  define_single_assign_static("std", "is_odd", get__std__is_odd, &var.std__is_odd);
  define_single_assign_static("std", "is_even", get__std__is_even, &var.std__is_even);
  define_single_assign_static("std", "bin", get__std__bin, &var.std__bin);
  define_single_assign_static("std", "oct", get__std__oct, &var.std__oct);
  define_single_assign_static("std", "hex", get__std__hex, &var.std__hex);
}

static int already_run_phase_4 = false;

EXPORT void phase_4__basic__types__number(void) {
  if (already_run_phase_4) return;
  already_run_phase_4 = true;
  set_module("basic__types__number");
  set_used_namespaces(used_namespaces);
  use_polymorphic_function(NULL, "bit_and", &get__bit_and, &poly_idx__bit_and);
  use_polymorphic_function(NULL, "bit_or", &get__bit_or, &poly_idx__bit_or);
  use_polymorphic_function(NULL, "bit_xor", &get__bit_xor, &poly_idx__bit_xor);
  use_polymorphic_function(NULL, "ceil", &get__ceil, &poly_idx__ceil);
  use_polymorphic_function(NULL, "div", &get__div, &poly_idx__div);
  use_read_only(NULL, "dup", &get__dup, &get_value_or_future__dup);
  use_polymorphic_function(NULL, "equal", &get__equal, &poly_idx__equal);
  use_polymorphic_function(NULL, "equal_type_and_value", &get__equal_type_and_value, &poly_idx__equal_type_and_value);
  use_read_only(NULL, "false", &get__false, &get_value_or_future__false);
  use_polymorphic_function(NULL, "floor", &get__floor, &poly_idx__floor);
  use_polymorphic_function(NULL, "hash", &get__hash, &poly_idx__hash);
  use_read_only(NULL, "if", &get__if, &get_value_or_future__if);
  use_polymorphic_function(NULL, "is_a_number", &get__is_a_number, &poly_idx__is_a_number);
  use_polymorphic_function(NULL, "is_a_real", &get__is_a_real, &poly_idx__is_a_real);
  use_polymorphic_function(NULL, "is_an_integer", &get__is_an_integer, &poly_idx__is_an_integer);
  use_read_only(NULL, "is_defined", &get__is_defined, &get_value_or_future__is_defined);
  use_polymorphic_function(NULL, "less", &get__less, &poly_idx__less);
  use_polymorphic_function(NULL, "ln", &get__ln, &poly_idx__ln);
  use_polymorphic_function(NULL, "minus", &get__minus, &poly_idx__minus);
  use_polymorphic_function(NULL, "mod", &get__mod, &poly_idx__mod);
  use_polymorphic_function(NULL, "negate", &get__negate, &poly_idx__negate);
  use_polymorphic_function(NULL, "over", &get__over, &poly_idx__over);
  use_read_only(NULL, "pad_left", &get__pad_left, &get_value_or_future__pad_left);
  use_polymorphic_function(NULL, "plus", &get__plus, &poly_idx__plus);
  use_read_only(NULL, "put", &get__put, &get_value_or_future__put);
  use_polymorphic_function(NULL, "round", &get__round, &poly_idx__round);
  use_polymorphic_function(NULL, "shift_left", &get__shift_left, &poly_idx__shift_left);
  use_polymorphic_function(NULL, "shift_right", &get__shift_right, &poly_idx__shift_right);
  use_read_only("std", "bit_and", &get__std__bit_and, &get_value_or_future__std__bit_and);
  use_read_only("std", "equal", &get__std__equal, &get_value_or_future__std__equal);
  use_read_only("std", "less", &get__std__less, &get_value_or_future__std__less);
  use_read_only("std", "minus", &get__std__minus, &get_value_or_future__std__minus);
  use_read_only("std", "not", &get__std__not, &get_value_or_future__std__not);
  use_read_only("std", "plus", &get__std__plus, &get_value_or_future__std__plus);
  use_read_only("std", "shift_right", &get__std__shift_right, &get_value_or_future__std__shift_right);
  use_polymorphic_function(NULL, "times", &get__times, &poly_idx__times);
  use_polymorphic_function(NULL, "to_integer", &get__to_integer, &poly_idx__to_integer);
  use_polymorphic_function(NULL, "to_string", &get__to_string, &poly_idx__to_string);
  use_read_only(NULL, "true", &get__true, &get_value_or_future__true);
  use_read_only("types", "object", &get__types__object, &get_value_or_future__types__object);
  use_read_only(NULL, "while", &get__while, &get_value_or_future__while);
  define_attribute("types", "object", poly_idx__is_a_number, get__false());
  define_attribute("types", "number", poly_idx__is_a_number, get__true());
  define_attribute("types", "object", poly_idx__is_an_integer, get__false());
  define_attribute("types", "integer", poly_idx__is_an_integer, get__true());
  define_attribute("types", "object", poly_idx__is_a_real, get__false());
  define_attribute("types", "real", poly_idx__is_a_real, get__true());
  define_method("types", "positive_integer", poly_idx__negate, func__types__positive_integer__negate_1);
  define_method("types", "negative_integer", poly_idx__negate, func__types__negative_integer__negate_1);
  define_method("types", "positive_large_integer", poly_idx__negate, func__types__positive_large_integer__negate_1);
  define_method("types", "negative_large_integer", poly_idx__negate, func__types__negative_large_integer__negate_1);
  define_method("types", "real", poly_idx__negate, func__types__real__negate_1);
  define_method("types", "positive_integer", poly_idx__plus, func__types__positive_integer__plus_1);
  define_method("types", "positive_integer", poly_idx__minus, func__types__positive_integer__minus_1);
  define_method("types", "negative_integer", poly_idx__plus, func__types__negative_integer__plus_1);
  define_method("types", "negative_integer", poly_idx__minus, func__types__negative_integer__minus_1);
  define_method("types", "positive_large_integer", poly_idx__plus, func__types__positive_large_integer__plus_1);
  define_method("types", "positive_large_integer", poly_idx__minus, func__types__positive_large_integer__minus_1);
  define_method("types", "negative_large_integer", poly_idx__plus, func__types__negative_large_integer__plus_1);
  define_method("types", "negative_large_integer", poly_idx__minus, func__types__negative_large_integer__minus_1);
  define_method("types", "real", poly_idx__plus, func__types__real__plus_1);
  define_method("types", "real", poly_idx__minus, func__types__real__minus_1);
  define_method("types", "positive_integer", poly_idx__times, func__types__positive_integer__times_1);
  define_method("types", "negative_integer", poly_idx__times, func__types__negative_integer__times_1);
  define_method("types", "positive_large_integer", poly_idx__times, func__types__positive_large_integer__times_1);
  define_method("types", "negative_large_integer", poly_idx__times, func__types__negative_large_integer__times_1);
  define_method("types", "real", poly_idx__times, func__types__real__times_1);
  define_method("types", "positive_integer", poly_idx__over, func__types__positive_integer__over_1);
  define_method("types", "negative_integer", poly_idx__over, func__types__negative_integer__over_1);
  define_method("types", "positive_large_integer", poly_idx__over, func__types__positive_large_integer__over_1);
  define_method("types", "negative_large_integer", poly_idx__over, func__types__negative_large_integer__over_1);
  define_method("types", "real", poly_idx__over, func__types__real__over_1);
  define_method("types", "positive_integer", poly_idx__div, func__types__positive_integer__div_1);
  define_method("types", "positive_integer", poly_idx__mod, func__types__positive_integer__mod_1);
  define_method("types", "positive_integer", poly_idx__equal, func__types__positive_integer__equal_1);
  define_method("types", "positive_integer", poly_idx__equal_type_and_value, func__types__positive_integer__equal_type_and_value_1);
  define_method("types", "negative_integer", poly_idx__equal, func__types__negative_integer__equal_1);
  define_method("types", "negative_integer", poly_idx__equal_type_and_value, func__types__negative_integer__equal_type_and_value_1);
  define_method("types", "positive_large_integer", poly_idx__equal, func__types__positive_large_integer__equal_1);
  define_method("types", "positive_large_integer", poly_idx__equal_type_and_value, func__types__positive_large_integer__equal_type_and_value_1);
  define_method("types", "negative_large_integer", poly_idx__equal, func__types__negative_large_integer__equal_1);
  define_method("types", "negative_large_integer", poly_idx__equal_type_and_value, func__types__negative_large_integer__equal_type_and_value_1);
  define_method("types", "real", poly_idx__equal, func__types__real__equal_1);
  define_method("types", "real", poly_idx__equal_type_and_value, func__types__real__equal_type_and_value_1);
  define_method("types", "positive_integer", poly_idx__less, func__types__positive_integer__less_1);
  define_method("types", "negative_integer", poly_idx__less, func__types__negative_integer__less_1);
  define_method("types", "positive_large_integer", poly_idx__less, func__types__positive_large_integer__less_1);
  define_method("types", "negative_large_integer", poly_idx__less, func__types__negative_large_integer__less_1);
  define_method("types", "real", poly_idx__less, func__types__real__less_1);
  define_method("types", "positive_integer", poly_idx__shift_left, func__types__positive_integer__shift_left_1);
  define_method("types", "positive_large_integer", poly_idx__shift_left, func__types__positive_large_integer__shift_left_1);
  define_method("types", "positive_integer", poly_idx__shift_right, func__types__positive_integer__shift_right_1);
  define_method("types", "positive_large_integer", poly_idx__shift_right, func__types__positive_large_integer__shift_right_1);
  define_method("types", "positive_integer", poly_idx__bit_or, func__types__positive_integer__bit_or_1);
  define_method("types", "positive_integer", poly_idx__bit_and, func__types__positive_integer__bit_and_1);
  define_method("types", "positive_integer", poly_idx__bit_xor, func__types__positive_integer__bit_xor_1);
  define_method("types", "positive_integer", poly_idx__hash, func__types__positive_integer__hash_1);
  define_method("types", "negative_integer", poly_idx__hash, func__types__negative_integer__hash_1);
  define_method("types", "positive_integer", poly_idx__to_string, func__types__positive_integer__to_string_1);
  define_method("types", "negative_integer", poly_idx__to_string, func__types__negative_integer__to_string_1);
  define_method("types", "positive_large_integer", poly_idx__to_string, func__types__positive_large_integer__to_string_1);
  define_method("types", "negative_large_integer", poly_idx__to_string, func__types__negative_large_integer__to_string_1);
  define_method("types", "real", poly_idx__to_string, func__types__real__to_string_1);
  define_method("types", "integer", poly_idx__to_integer, func__types__integer__to_integer_1);
  define_method("types", "real", poly_idx__to_integer, func__types__real__to_integer_1);
  define_method("types", "number", poly_idx__floor, func__types__number__floor_1);
  define_method("types", "number", poly_idx__ceil, func__types__number__ceil_1);
  define_method("types", "number", poly_idx__round, func__types__number__round_1);
  define_method("types", "real", poly_idx__floor, func__types__real__floor_1);
  define_method("types", "real", poly_idx__ceil, func__types__real__ceil_1);
  define_method("types", "real", poly_idx__round, func__types__real__round_1);
  define_method("types", "real", poly_idx__ln, func__types__real__ln_1);
}

static int already_run_phase_5 = false;

EXPORT void phase_5__basic__types__number(void) {
  if (already_run_phase_5) return;
  already_run_phase_5 = true;
  assign_value(&var.std__integer_plus_me, create_function(type__std__integer_plus_me, -1));
  assign_value(&var.std__integer_minus_me, create_function(type__std__integer_minus_me, -1));
  assign_value(&var.std__integer_times_me, create_function(type__std__integer_times_me, -1));
  assign_value(&var.std__integer_over_me, create_function(type__std__integer_over_me, -1));
  assign_value(&var.std__real_plus_me, create_function(type__std__real_plus_me, -1));
  assign_value(&var.std__real_minus_me, create_function(type__std__real_minus_me, -1));
  assign_value(&var.std__real_times_me, create_function(type__std__real_times_me, -1));
  assign_value(&var.std__real_over_me, create_function(type__std__real_over_me, -1));
  assign_value(&var.std__is_a_number, create_function(type__std__is_a_number, -1));
  assign_value(&var.std__is_an_integer, create_function(type__std__is_an_integer, -1));
  assign_value(&var.std__is_a_real, create_function(type__std__is_a_real, -1));
  assign_value(&var.std__floor, create_function(type__std__floor, -1));
  assign_value(&var.std__ceil, create_function(type__std__ceil, -1));
  assign_value(&var.std__round, create_function(type__std__round, -1));
  assign_value(&var.std__ln, create_function(type__std__ln, -1));
  assign_value(&var.types__number, get__types__object());
  assign_variable(&var.types__integer, &var.types__number);
  assign_variable(&var.types__positive_integer, &var.types__integer);
  assign_variable(&var.types__negative_integer, &var.types__integer);
  assign_variable(&var.types__positive_large_integer, &var.types__integer);
  assign_variable(&var.types__negative_large_integer, &var.types__integer);
  assign_variable(&var.types__real, &var.types__number);
  assign_variable(&var.std__is_odd, &func__std__is_odd_1);
  assign_variable(&var.std__is_even, &func__std__is_even_1);
  assign_variable(&var.std__bin, &func__std__bin_1);
  assign_variable(&var.std__oct, &func__std__oct_1);
  assign_variable(&var.std__hex, &func__std__hex_1);
}

static int already_run_phase_6 = false;

EXPORT void phase_6__basic__types__number(void) {
  if (already_run_phase_6) return;
  already_run_phase_6 = true;
  register_collector(collect__basic__types__number);
}
