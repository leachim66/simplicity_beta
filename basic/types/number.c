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
IMPORT void too_few_arguments_error(void);
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
IMPORT void define_polymorphic_function(
  const char *namespace, const char *name, NODE_GETTER getter, int *id_p,
  NODE **var_p
);
IMPORT void define_c_function(const char *name, void *func);
IMPORT NODE *from_int(int val);
IMPORT NODE *from_int64(int64_t val);
IMPORT NODE *from_uint64(uint64_t val);
IMPORT NODE *from_digit_string(const char *str);
IMPORT NODE *from_double(double val);
IMPORT NODE *from_uchar32(unsigned int chr);
IMPORT NODE *create_function(FUNC func, int par_count);
IMPORT void set_module(const char *name);
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
static NODE *create__types__positive_integer(uint64_t value);
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
static void entry__58_1_types__positive_integer_negate(void);
static NODE *func__58_1_types__positive_integer_negate;
static void entry__59_1_types__negative_integer_negate(void);
static NODE *func__59_1_types__negative_integer_negate;
static void entry__60_1_types__positive_large_integer_negate(void);
static NODE *func__60_1_types__positive_large_integer_negate;
static void entry__61_1_types__negative_large_integer_negate(void);
static NODE *func__61_1_types__negative_large_integer_negate;
static void entry__62_1_types__real_negate(void);
static NODE *func__62_1_types__real_negate;

static NODE *positive_integer_sum(void);

static NODE *negative_integer_sum(void);

static NODE *integer_difference(uint64_t left_integer, uint64_t right_integer);
static void entry__66_1_types__positive_integer_plus(void);
static NODE *func__66_1_types__positive_integer_plus;
static void entry__67_1_types__positive_integer_minus(void);
static NODE *func__67_1_types__positive_integer_minus;
static void entry__68_1_types__negative_integer_plus(void);
static NODE *func__68_1_types__negative_integer_plus;
static void entry__69_1_types__negative_integer_minus(void);
static NODE *func__69_1_types__negative_integer_minus;

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
static void entry__72_1_types__positive_large_integer_plus(void);
static NODE *func__72_1_types__positive_large_integer_plus;
static void entry__73_1_types__positive_large_integer_minus(void);
static NODE *func__73_1_types__positive_large_integer_minus;
static void entry__74_1_types__negative_large_integer_plus(void);
static NODE *func__74_1_types__negative_large_integer_plus;
static void entry__75_1_types__negative_large_integer_minus(void);
static NODE *func__75_1_types__negative_large_integer_minus;
static void entry__76_1_types__real_plus(void);
static NODE *func__76_1_types__real_plus;
static void entry__77_1_types__real_minus(void);
static NODE *func__77_1_types__real_minus;

static NODE *integer_product(int sign);
static void entry__79_1_types__positive_integer_times(void);
static NODE *func__79_1_types__positive_integer_times;
static void entry__80_1_types__negative_integer_times(void);
static NODE *func__80_1_types__negative_integer_times;

static NODE *large_integer_product(
  mp_limb_t *left_limbs, long left_size,
  mp_limb_t *right_limbs, long right_size,
  int sign
);
static void entry__82_1_types__positive_large_integer_times(void);
static NODE *func__82_1_types__positive_large_integer_times;
static void entry__83_1_types__negative_large_integer_times(void);
static NODE *func__83_1_types__negative_large_integer_times;
static void entry__84_1_types__real_times(void);
static NODE *func__84_1_types__real_times;

static NODE *integer_quotient(int sign);
static void entry__86_1_types__positive_integer_over(void);
static NODE *func__86_1_types__positive_integer_over;
static void entry__87_1_types__negative_integer_over(void);
static NODE *func__87_1_types__negative_integer_over;

static NODE *large_integer_quotient(
  mp_limb_t *left_limbs, long left_size,
  mp_limb_t *right_limbs, long right_size,
  int sign
);
static void entry__89_1_types__positive_large_integer_over(void);
static NODE *func__89_1_types__positive_large_integer_over;
static void entry__90_1_types__negative_large_integer_over(void);
static NODE *func__90_1_types__negative_large_integer_over;
static void entry__91_1_types__real_over(void);
static NODE *func__91_1_types__real_over;
static void entry__92_1_types__positive_integer_div(void);
static NODE *func__92_1_types__positive_integer_div;
static void entry__93_1_types__positive_integer_mod(void);
static NODE *func__93_1_types__positive_integer_mod;
static void entry__94_1_types__positive_integer_equal(void);
static NODE *func__94_1_types__positive_integer_equal;
static void entry__95_1_types__positive_integer_equal_type_and_value(void);
static NODE *func__95_1_types__positive_integer_equal_type_and_value;
static void entry__96_1_types__negative_integer_equal(void);
static NODE *func__96_1_types__negative_integer_equal;
static void entry__97_1_types__negative_integer_equal_type_and_value(void);
static NODE *func__97_1_types__negative_integer_equal_type_and_value;
static void entry__98_1_types__positive_large_integer_equal(void);
static NODE *func__98_1_types__positive_large_integer_equal;
static void entry__99_1_types__positive_large_integer_equal_type_and_value(void);
static NODE *func__99_1_types__positive_large_integer_equal_type_and_value;
static void entry__100_1_types__negative_large_integer_equal(void);
static NODE *func__100_1_types__negative_large_integer_equal;
static void entry__101_1_types__negative_large_integer_equal_type_and_value(void);
static NODE *func__101_1_types__negative_large_integer_equal_type_and_value;
static void entry__102_1_types__real_equal(void);
static NODE *func__102_1_types__real_equal;
static void entry__103_1_types__real_equal_type_and_value(void);
static NODE *func__103_1_types__real_equal_type_and_value;
static void entry__104_1_types__positive_integer_less(void);
static NODE *func__104_1_types__positive_integer_less;
static void entry__105_1_types__negative_integer_less(void);
static NODE *func__105_1_types__negative_integer_less;
static void entry__106_1_types__positive_large_integer_less(void);
static NODE *func__106_1_types__positive_large_integer_less;
static void entry__107_1_types__negative_large_integer_less(void);
static NODE *func__107_1_types__negative_large_integer_less;
static void entry__108_1_types__real_less(void);
static NODE *func__108_1_types__real_less;

static mp_limb_t lshift(
  mp_limb_t *rp, const mp_limb_t *src_ptr,
  mp_size_t src_size, unsigned long int count
);

static mp_limb_t rshift(
  mp_limb_t *rp, const mp_limb_t *src_ptr,
  mp_size_t src_size, unsigned long int count
);
static void entry__111_1_types__positive_integer_shift_left(void);
static NODE *func__111_1_types__positive_integer_shift_left;
static void entry__112_1_types__positive_large_integer_shift_left(void);
static NODE *func__112_1_types__positive_large_integer_shift_left;
static void entry__113_1_types__positive_integer_shift_right(void);
static NODE *func__113_1_types__positive_integer_shift_right;
static void entry__114_1_types__positive_large_integer_shift_right(void);
static NODE *func__114_1_types__positive_large_integer_shift_right;
static void entry__115_1_types__positive_integer_bit_or(void);
static NODE *func__115_1_types__positive_integer_bit_or;
static void entry__116_1_types__positive_integer_bit_and(void);
static NODE *func__116_1_types__positive_integer_bit_and;
static void entry__117_1_types__positive_integer_bit_xor(void);
static NODE *func__117_1_types__positive_integer_bit_xor;
static void entry__118_1_types__positive_integer_hash(void);
static NODE *func__118_1_types__positive_integer_hash;
static void entry__119_1_types__negative_integer_hash(void);
static NODE *func__119_1_types__negative_integer_hash;
static void entry__120_1_types__positive_integer_to_string(void);
static NODE *func__120_1_types__positive_integer_to_string;

static long func__types__positive_integer___debug_string(NODE *node, int indent, int max_depth, char *buf);
static void entry__122_1_types__negative_integer_to_string(void);
static NODE *func__122_1_types__negative_integer_to_string;

static long func__types__negative_integer___debug_string(NODE *node, int indent, int max_depth, char *buf);

static NODE *large_integer_to_string(int sign);
static void entry__125_1_types__positive_large_integer_to_string(void);
static NODE *func__125_1_types__positive_large_integer_to_string;

static long func__types__positive_large_integer___debug_string(NODE *node, int indent, int max_depth, char *buf);
static void entry__127_1_types__negative_large_integer_to_string(void);
static NODE *func__127_1_types__negative_large_integer_to_string;

static long func__types__negetive_large_integer___debug_string(NODE *node, int indent, int max_depth, char *buf);
static void entry__129_1_types__real_to_string(void);
static NODE *func__129_1_types__real_to_string;

static long func__types__real___debug_string(NODE *node, int indent, int max_depth, char *buf);
static NODE *func__131_1_std__is_odd;
static void entry__131_1_std__is_odd(void);
static FRAME_INFO frame__131_1_std__is_odd = {1, {"n"}};
static void cont__131_2(void);
static void cont__131_3(void);
static NODE *get__std__is_odd(void) {
  return var.std__is_odd;
}
static NODE *func__132_1_std__is_even;
static void entry__132_1_std__is_even(void);
static FRAME_INFO frame__132_1_std__is_even = {1, {"n"}};
static void cont__132_2(void);
static void cont__132_3(void);
static NODE *get__std__is_even(void) {
  return var.std__is_even;
}
static NODE *func__133_1_std__bin;
static void entry__133_1_std__bin(void);
static FRAME_INFO frame__133_1_std__bin = {4, {"val", "size", "return", "str"}};
static void cont__133_2(void);
static NODE *func__133_3;
static void entry__133_3(void);
static FRAME_INFO frame__133_3 = {2, {"size", "return"}};
static void cont__133_4(void);
static NODE *func__133_5;
static void entry__133_5(void);
static FRAME_INFO frame__133_5 = {2, {"return", "size"}};
static NODE *string__133_6;
static void cont__133_7(void);
static NODE *func__133_8;
static void entry__133_8(void);
static FRAME_INFO frame__133_8 = {1, {"return"}};
static void cont__133_9(void);
static NODE *func__133_10;
static void entry__133_10(void);
static FRAME_INFO frame__133_10 = {2, {"val", "str"}};
static void cont__133_11(void);
static NODE *func__133_12;
static void entry__133_12(void);
static FRAME_INFO frame__133_12 = {2, {"str", "val"}};
static void cont__133_13(void);
static void cont__133_14(void);
static void cont__133_15(void);
static void cont__133_16(void);
static void cont__133_17(void);
static void cont__133_18(void);
static NODE *func__133_19;
static void entry__133_19(void);
static FRAME_INFO frame__133_19 = {3, {"return", "str", "size"}};
static void cont__133_20(void);
static void cont__133_21(void);
static NODE *get__std__bin(void) {
  return var.std__bin;
}
static NODE *func__134_1_std__oct;
static void entry__134_1_std__oct(void);
static FRAME_INFO frame__134_1_std__oct = {4, {"val", "size", "return", "str"}};
static void cont__134_2(void);
static NODE *func__134_3;
static void entry__134_3(void);
static FRAME_INFO frame__134_3 = {2, {"size", "return"}};
static void cont__134_4(void);
static NODE *func__134_5;
static void entry__134_5(void);
static FRAME_INFO frame__134_5 = {2, {"return", "size"}};
static void cont__134_6(void);
static NODE *func__134_7;
static void entry__134_7(void);
static FRAME_INFO frame__134_7 = {1, {"return"}};
static void cont__134_8(void);
static NODE *func__134_9;
static void entry__134_9(void);
static FRAME_INFO frame__134_9 = {2, {"val", "str"}};
static void cont__134_10(void);
static NODE *func__134_11;
static void entry__134_11(void);
static FRAME_INFO frame__134_11 = {2, {"str", "val"}};
static void cont__134_12(void);
static void cont__134_13(void);
static void cont__134_14(void);
static void cont__134_15(void);
static void cont__134_16(void);
static void cont__134_17(void);
static NODE *func__134_18;
static void entry__134_18(void);
static FRAME_INFO frame__134_18 = {3, {"return", "str", "size"}};
static void cont__134_19(void);
static void cont__134_20(void);
static NODE *get__std__oct(void) {
  return var.std__oct;
}
static NODE *func__135_1_std__hex;
static void entry__135_1_std__hex(void);
static FRAME_INFO frame__135_1_std__hex = {4, {"val", "size", "return", "str"}};
static void cont__135_2(void);
static NODE *func__135_3;
static void entry__135_3(void);
static FRAME_INFO frame__135_3 = {2, {"size", "return"}};
static void cont__135_4(void);
static NODE *func__135_5;
static void entry__135_5(void);
static FRAME_INFO frame__135_5 = {2, {"return", "size"}};
static void cont__135_6(void);
static NODE *func__135_7;
static void entry__135_7(void);
static FRAME_INFO frame__135_7 = {1, {"return"}};
static void cont__135_8(void);
static NODE *func__135_9;
static void entry__135_9(void);
static FRAME_INFO frame__135_9 = {2, {"val", "str"}};
static void cont__135_10(void);
static NODE *func__135_11;
static void entry__135_11(void);
static FRAME_INFO frame__135_11 = {3, {"val", "str", "hex_digit"}};
static void cont__135_12(void);
static void cont__135_13(void);
static void cont__135_14(void);
static NODE *func__135_15;
static void entry__135_15(void);
static FRAME_INFO frame__135_15 = {1, {"hex_digit"}};
static void cont__135_16(void);
static void cont__135_17(void);
static NODE *func__135_18;
static void entry__135_18(void);
static FRAME_INFO frame__135_18 = {1, {"hex_digit"}};
static void cont__135_19(void);
static void cont__135_20(void);
static void cont__135_21(void);
static void cont__135_22(void);
static void cont__135_23(void);
static void cont__135_24(void);
static NODE *func__135_25;
static void entry__135_25(void);
static FRAME_INFO frame__135_25 = {3, {"return", "str", "size"}};
static void cont__135_26(void);
static void cont__135_27(void);
static NODE *get__std__hex(void) {
  return var.std__hex;
}
static NODE *func__136_1_types__integer_to_integer;
static void entry__136_1_types__integer_to_integer(void);
static FRAME_INFO frame__136_1_types__integer_to_integer = {1, {"value"}};
static void entry__137_1_types__real_to_integer(void);
static NODE *func__137_1_types__real_to_integer;
static NODE *func__138_1_types__number_floor;
static void entry__138_1_types__number_floor(void);
static FRAME_INFO frame__138_1_types__number_floor = {1, {"self"}};
static NODE *func__139_1_types__number_ceil;
static void entry__139_1_types__number_ceil(void);
static FRAME_INFO frame__139_1_types__number_ceil = {1, {"self"}};
static NODE *func__140_1_types__number_round;
static void entry__140_1_types__number_round(void);
static FRAME_INFO frame__140_1_types__number_round = {1, {"self"}};
static void entry__141_1_types__real_floor(void);
static NODE *func__141_1_types__real_floor;
static void entry__142_1_types__real_ceil(void);
static NODE *func__142_1_types__real_ceil;
static void entry__143_1_types__real_round(void);
static NODE *func__143_1_types__real_round;
static void entry__144_1_types__real_ln(void);
static NODE *func__144_1_types__real_ln;
void run__basic__types__number(void);

static CONTINUATION_INFO continuation_info[] = {
  {type__std__integer_plus_me, NULL, 35, 35, 2, 21},
  {type__std__integer_minus_me, NULL, 36, 36, 2, 22},
  {type__std__integer_times_me, NULL, 37, 37, 2, 22},
  {type__std__integer_over_me, NULL, 38, 38, 2, 21},
  {type__std__real_plus_me, NULL, 39, 39, 2, 18},
  {type__std__real_minus_me, NULL, 40, 40, 2, 19},
  {type__std__real_times_me, NULL, 41, 41, 2, 19},
  {type__std__real_over_me, NULL, 42, 42, 2, 18},
  {type__std__is_a_number, NULL, 43, 43, 2, 17},
  {type__std__is_an_integer, NULL, 44, 44, 2, 19},
  {type__std__is_a_real, NULL, 45, 45, 2, 15},
  {type__std__floor, NULL, 46, 46, 2, 11},
  {type__std__ceil, NULL, 47, 47, 2, 10},
  {type__std__round, NULL, 48, 48, 2, 11},
  {type__std__ln, NULL, 49, 49, 2, 8},
  {run__basic__types__number, NULL, },
  {entry__58_1_types__positive_integer_negate, NULL, 430, 434, 3, 2},
  {entry__59_1_types__negative_integer_negate, NULL, 437, 442, 3, 2},
  {entry__60_1_types__positive_large_integer_negate, NULL, 445, 449, 3, 2},
  {entry__61_1_types__negative_large_integer_negate, NULL, 452, 456, 3, 2},
  {entry__62_1_types__real_negate, NULL, 459, 462, 3, 2},
  {entry__66_1_types__positive_integer_plus, NULL, 520, 547, 3, 2},
  {entry__67_1_types__positive_integer_minus, NULL, 550, 577, 3, 2},
  {entry__68_1_types__negative_integer_plus, NULL, 580, 607, 3, 2},
  {entry__69_1_types__negative_integer_minus, NULL, 610, 637, 3, 2},
  {entry__72_1_types__positive_large_integer_plus, NULL, 711, 747, 3, 2},
  {entry__73_1_types__positive_large_integer_minus, NULL, 750, 786, 3, 2},
  {entry__74_1_types__negative_large_integer_plus, NULL, 789, 825, 3, 2},
  {entry__75_1_types__negative_large_integer_minus, NULL, 828, 864, 3, 2},
  {entry__76_1_types__real_plus, NULL, 867, 894, 3, 2},
  {entry__77_1_types__real_minus, NULL, 897, 924, 3, 2},
  {entry__79_1_types__positive_integer_times, NULL, 965, 990, 3, 2},
  {entry__80_1_types__negative_integer_times, NULL, 993, 1018, 3, 2},
  {entry__82_1_types__positive_large_integer_times, NULL, 1051, 1087, 3, 2},
  {entry__83_1_types__negative_large_integer_times, NULL, 1090, 1126, 3, 2},
  {entry__84_1_types__real_times, NULL, 1129, 1154, 3, 2},
  {entry__86_1_types__positive_integer_over, NULL, 1174, 1197, 3, 2},
  {entry__87_1_types__negative_integer_over, NULL, 1200, 1223, 3, 2},
  {entry__89_1_types__positive_large_integer_over, NULL, 1271, 1307, 3, 2},
  {entry__90_1_types__negative_large_integer_over, NULL, 1310, 1346, 3, 2},
  {entry__91_1_types__real_over, NULL, 1349, 1374, 3, 2},
  {entry__92_1_types__positive_integer_div, NULL, 1377, 1385, 3, 2},
  {entry__93_1_types__positive_integer_mod, NULL, 1388, 1396, 3, 2},
  {entry__94_1_types__positive_integer_equal, NULL, 1399, 1407, 3, 2},
  {entry__95_1_types__positive_integer_equal_type_and_value, NULL, 1410, 1416, 3, 2},
  {entry__96_1_types__negative_integer_equal, NULL, 1419, 1427, 3, 2},
  {entry__97_1_types__negative_integer_equal_type_and_value, NULL, 1430, 1436, 3, 2},
  {entry__98_1_types__positive_large_integer_equal, NULL, 1439, 1457, 3, 2},
  {entry__99_1_types__positive_large_integer_equal_type_and_value, NULL, 1460, 1473, 3, 2},
  {entry__100_1_types__negative_large_integer_equal, NULL, 1476, 1494, 3, 2},
  {entry__101_1_types__negative_large_integer_equal_type_and_value, NULL, 1497, 1510, 3, 2},
  {entry__102_1_types__real_equal, NULL, 1513, 1533, 3, 2},
  {entry__103_1_types__real_equal_type_and_value, NULL, 1536, 1542, 3, 2},
  {entry__104_1_types__positive_integer_less, NULL, 1545, 1561, 3, 2},
  {entry__105_1_types__negative_integer_less, NULL, 1564, 1580, 3, 2},
  {entry__106_1_types__positive_large_integer_less, NULL, 1583, 1608, 3, 2},
  {entry__107_1_types__negative_large_integer_less, NULL, 1611, 1636, 3, 2},
  {entry__108_1_types__real_less, NULL, 1639, 1659, 3, 2},
  {entry__111_1_types__positive_integer_shift_left, NULL, 1688, 1729, 3, 2},
  {entry__112_1_types__positive_large_integer_shift_left, NULL, 1732, 1755, 3, 2},
  {entry__113_1_types__positive_integer_shift_right, NULL, 1758, 1764, 3, 2},
  {entry__114_1_types__positive_large_integer_shift_right, NULL, 1767, 1805, 3, 2},
  {entry__115_1_types__positive_integer_bit_or, NULL, 1808, 1816, 3, 2},
  {entry__116_1_types__positive_integer_bit_and, NULL, 1819, 1827, 3, 2},
  {entry__117_1_types__positive_integer_bit_xor, NULL, 1830, 1838, 3, 2},
  {entry__118_1_types__positive_integer_hash, NULL, 1841, 1850, 3, 2},
  {entry__119_1_types__negative_integer_hash, NULL, 1853, 1862, 3, 2},
  {entry__120_1_types__positive_integer_to_string, NULL, 1865, 1870, 3, 2},
  {entry__122_1_types__negative_integer_to_string, NULL, 1881, 1886, 3, 2},
  {entry__125_1_types__positive_large_integer_to_string, NULL, 1925, 1928, 3, 2},
  {entry__127_1_types__negative_large_integer_to_string, NULL, 1939, 1942, 3, 2},
  {entry__129_1_types__real_to_string, NULL, 1953, 1958, 3, 2},
  {entry__131_1_std__is_odd, NULL, 1968, 1968, 22, 26},
  {cont__131_2, &frame__131_1_std__is_odd, 1968, 1968, 22, 31},
  {cont__131_3, &frame__131_1_std__is_odd, 1968, 1968, 19, 31},
  {entry__132_1_std__is_even, NULL, 1970, 1970, 23, 27},
  {cont__132_2, &frame__132_1_std__is_even, 1970, 1970, 23, 32},
  {cont__132_3, &frame__132_1_std__is_even, 1970, 1970, 20, 32},
  {entry__133_5, NULL, 1981, 1981, 16, 28},
  {cont__133_7, &frame__133_5, 1981, 1981, 9, 28},
  {entry__133_8, NULL, 1983, 1983, 9, 18},
  {entry__133_3, NULL, 1980, 1980, 7, 21},
  {cont__133_4, &frame__133_3, 1979, 1983, 5, 19},
  {entry__133_12, NULL, 1986, 1986, 19, 25},
  {cont__133_13, &frame__133_12, 1986, 1986, 14, 25},
  {cont__133_14, &frame__133_12, 1986, 1986, 5, 26},
  {cont__133_15, &frame__133_12, 1987, 1987, 5, 17},
  {cont__133_16, &frame__133_12, 1987, 1987, 17, 17},
  {entry__133_10, NULL, 1985, 1985, 12, 18},
  {cont__133_11, &frame__133_10, 1985, 1987, 9, 17},
  {entry__133_19, NULL, 1988, 1988, 30, 51},
  {cont__133_20, &frame__133_19, 1988, 1988, 23, 51},
  {entry__133_1_std__bin, NULL, 1978, 1978, 6, 13},
  {cont__133_2, &frame__133_1_std__bin, 1978, 1983, 3, 20},
  {cont__133_9, &frame__133_1_std__bin, 1985, 1987, 3, 17},
  {cont__133_17, &frame__133_1_std__bin, 1988, 1988, 6, 20},
  {cont__133_18, &frame__133_1_std__bin, 1988, 1988, 3, 51},
  {cont__133_21, &frame__133_1_std__bin, 1989, 1989, 3, 8},
  {entry__134_5, NULL, 2000, 2000, 16, 28},
  {cont__134_6, &frame__134_5, 2000, 2000, 9, 28},
  {entry__134_7, NULL, 2002, 2002, 9, 18},
  {entry__134_3, NULL, 1999, 1999, 7, 21},
  {cont__134_4, &frame__134_3, 1998, 2002, 5, 19},
  {entry__134_11, NULL, 2005, 2005, 19, 28},
  {cont__134_12, &frame__134_11, 2005, 2005, 14, 28},
  {cont__134_13, &frame__134_11, 2005, 2005, 5, 29},
  {cont__134_14, &frame__134_11, 2006, 2006, 5, 17},
  {cont__134_15, &frame__134_11, 2006, 2006, 17, 17},
  {entry__134_9, NULL, 2004, 2004, 12, 18},
  {cont__134_10, &frame__134_9, 2004, 2006, 9, 17},
  {entry__134_18, NULL, 2007, 2007, 30, 51},
  {cont__134_19, &frame__134_18, 2007, 2007, 23, 51},
  {entry__134_1_std__oct, NULL, 1997, 1997, 6, 13},
  {cont__134_2, &frame__134_1_std__oct, 1997, 2002, 3, 20},
  {cont__134_8, &frame__134_1_std__oct, 2004, 2006, 3, 17},
  {cont__134_16, &frame__134_1_std__oct, 2007, 2007, 6, 20},
  {cont__134_17, &frame__134_1_std__oct, 2007, 2007, 3, 51},
  {cont__134_20, &frame__134_1_std__oct, 2008, 2008, 3, 8},
  {entry__135_5, NULL, 2019, 2019, 16, 28},
  {cont__135_6, &frame__135_5, 2019, 2019, 9, 28},
  {entry__135_7, NULL, 2021, 2021, 9, 18},
  {entry__135_3, NULL, 2018, 2018, 7, 21},
  {cont__135_4, &frame__135_3, 2017, 2021, 5, 19},
  {entry__135_15, NULL, 2027, 2027, 20, 32},
  {cont__135_16, &frame__135_15, 2027, 2027, 9, 35},
  {cont__135_17, &frame__135_15, 2027, 2027, 35, 35},
  {entry__135_18, NULL, 2029, 2029, 9, 32},
  {cont__135_19, &frame__135_18, 2029, 2029, 32, 32},
  {entry__135_11, NULL, 2024, 2024, 5, 26},
  {cont__135_12, &frame__135_11, 2026, 2026, 7, 21},
  {cont__135_13, &frame__135_11, 2026, 2026, 7, 21},
  {cont__135_14, &frame__135_11, 2025, 2029, 5, 33},
  {cont__135_20, &frame__135_11, 2030, 2030, 5, 22},
  {cont__135_21, &frame__135_11, 2031, 2031, 5, 17},
  {cont__135_22, &frame__135_11, 2031, 2031, 17, 17},
  {entry__135_9, NULL, 2023, 2023, 12, 18},
  {cont__135_10, &frame__135_9, 2023, 2031, 9, 17},
  {entry__135_25, NULL, 2032, 2032, 30, 51},
  {cont__135_26, &frame__135_25, 2032, 2032, 23, 51},
  {entry__135_1_std__hex, NULL, 2016, 2016, 6, 13},
  {cont__135_2, &frame__135_1_std__hex, 2016, 2021, 3, 20},
  {cont__135_8, &frame__135_1_std__hex, 2023, 2031, 3, 17},
  {cont__135_23, &frame__135_1_std__hex, 2032, 2032, 6, 20},
  {cont__135_24, &frame__135_1_std__hex, 2032, 2032, 3, 51},
  {cont__135_27, &frame__135_1_std__hex, 2033, 2033, 3, 8},
  {entry__136_1_types__integer_to_integer, NULL, 2035, 2035, 37, 44},
  {entry__137_1_types__real_to_integer, NULL, 2038, 2042, 3, 2},
  {entry__138_1_types__number_floor, NULL, 2044, 2044, 30, 36},
  {entry__139_1_types__number_ceil, NULL, 2046, 2046, 29, 35},
  {entry__140_1_types__number_round, NULL, 2048, 2048, 30, 36},
  {entry__141_1_types__real_floor, NULL, 2051, 2054, 3, 2},
  {entry__142_1_types__real_ceil, NULL, 2057, 2060, 3, 2},
  {entry__143_1_types__real_round, NULL, 2063, 2066, 3, 2},
  {entry__144_1_types__real_ln, NULL, 2069, 2072, 3, 2}
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

static void type__types__positive_integer(void) {
  {
    runtime_error("Attempt to call an integer value as a function!");
  }
}
static NODE *create__types__positive_integer(uint64_t value) {
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
static void entry__58_1_types__positive_integer_negate(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
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
static void entry__59_1_types__negative_integer_negate(void) {
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
    NODE *result__node = (NODE *)(create__types__positive_integer(arguments->slots[0]->integer.value));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__60_1_types__positive_large_integer_negate(void) {
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
static void entry__61_1_types__negative_large_integer_negate(void) {
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
static void entry__62_1_types__real_negate(void) {
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
static void entry__66_1_types__positive_integer_plus(void) {
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
static void entry__67_1_types__positive_integer_minus(void) {
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
static void entry__68_1_types__negative_integer_plus(void) {
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
static void entry__69_1_types__negative_integer_minus(void) {
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
static void entry__72_1_types__positive_large_integer_plus(void) {
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
static void entry__73_1_types__positive_large_integer_minus(void) {
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
static void entry__74_1_types__negative_large_integer_plus(void) {
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
static void entry__75_1_types__negative_large_integer_minus(void) {
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
static void entry__76_1_types__real_plus(void) {
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
static void entry__77_1_types__real_minus(void) {
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
static void entry__79_1_types__positive_integer_times(void) {
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
static void entry__80_1_types__negative_integer_times(void) {
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
static void entry__82_1_types__positive_large_integer_times(void) {
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
static void entry__83_1_types__negative_large_integer_times(void) {
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
static void entry__84_1_types__real_times(void) {
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
static void entry__86_1_types__positive_integer_over(void) {
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
static void entry__87_1_types__negative_integer_over(void) {
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
static void entry__89_1_types__positive_large_integer_over(void) {
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
static void entry__90_1_types__negative_large_integer_over(void) {
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
static void entry__91_1_types__real_over(void) {
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
static void entry__92_1_types__positive_integer_div(void) {
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
static void entry__93_1_types__positive_integer_mod(void) {
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
static void entry__94_1_types__positive_integer_equal(void) {
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
static void entry__95_1_types__positive_integer_equal_type_and_value(void) {
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
static void entry__96_1_types__negative_integer_equal(void) {
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
static void entry__97_1_types__negative_integer_equal_type_and_value(void) {
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
static void entry__98_1_types__positive_large_integer_equal(void) {
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
static void entry__99_1_types__positive_large_integer_equal_type_and_value(void) {
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
static void entry__100_1_types__negative_large_integer_equal(void) {
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
static void entry__101_1_types__negative_large_integer_equal_type_and_value(void) {
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
static void entry__102_1_types__real_equal(void) {
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
static void entry__103_1_types__real_equal_type_and_value(void) {
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
static void entry__104_1_types__positive_integer_less(void) {
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
static void entry__105_1_types__negative_integer_less(void) {
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
static void entry__106_1_types__positive_large_integer_less(void) {
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
static void entry__107_1_types__negative_large_integer_less(void) {
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
static void entry__108_1_types__real_less(void) {
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
static void entry__111_1_types__positive_integer_shift_left(void) {
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
static void entry__112_1_types__positive_large_integer_shift_left(void) {
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
static void entry__113_1_types__positive_integer_shift_right(void) {
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
static void entry__114_1_types__positive_large_integer_shift_right(void) {
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
static void entry__115_1_types__positive_integer_bit_or(void) {
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
static void entry__116_1_types__positive_integer_bit_and(void) {
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
static void entry__117_1_types__positive_integer_bit_xor(void) {
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
static void entry__118_1_types__positive_integer_hash(void) {
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
static void entry__119_1_types__negative_integer_hash(void) {
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
static void entry__120_1_types__positive_integer_to_string(void) {
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
static void entry__122_1_types__negative_integer_to_string(void) {
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
static void entry__125_1_types__positive_large_integer_to_string(void) {
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
static void entry__127_1_types__negative_large_integer_to_string(void) {
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
static void entry__129_1_types__real_to_string(void) {
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
static void entry__131_1_std__is_odd(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // n: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 1968: ... n & 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* n */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__bit_and();
  func = myself->type;
  frame->cont = cont__131_2;
}
static void cont__131_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 1968: ... n & 1 == 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__131_3;
}
static void cont__131_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1968: ... -> n & 1 == 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__132_1_std__is_even(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // n: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 1970: ... n & 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* n */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__bit_and();
  func = myself->type;
  frame->cont = cont__132_2;
}
static void cont__132_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 1970: ... n & 1 == 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__132_3;
}
static void cont__132_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1970: ... -> n & 1 == 0
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__133_1_std__bin(void) {
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
  // 1978: ... val == 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* val */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__133_2;
}
static void cont__133_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 1978: ... :
  // 1979:   if
  // 1980:     size.is_defined:
  // 1981:       return dup("0" size)
  // 1982:     :
  // 1983:       return "0"
  frame->slots[5] /* temp__2 */ = create_closure(entry__133_3, 0);
  // 1978: if val == 0:
  // 1979:   if
  // 1980:     size.is_defined:
  // 1981:       return dup("0" size)
  // 1982:     :
  // 1983:       return "0"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__133_9;
}
static void entry__133_5(void) {
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
  // 1981: ... dup("0" size)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__133_6;
  arguments->slots[1] = frame->slots[1] /* size */;
  result_count = 1;
  myself = get__dup();
  func = myself->type;
  frame->cont = cont__133_7;
}
static void cont__133_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 1981: return dup("0" size)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__133_8(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1983: return "0"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__133_6;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__133_3(void) {
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
  // 1980: size.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* size */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__133_4;
}
static void cont__133_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 1980: ... :
  // 1981:   return dup("0" size)
  frame->slots[3] /* temp__2 */ = create_closure(entry__133_5, 0);
  // 1982: :
  // 1983:   return "0"
  frame->slots[4] /* temp__3 */ = create_closure(entry__133_8, 0);
  // 1979: if
  // 1980:   size.is_defined:
  // 1981:     return dup("0" size)
  // 1982:   :
  // 1983:     return "0"
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
static void cont__133_9(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1984: $$str ""
  ((CELL *)frame->slots[3])->contents /* str */ = empty_string;
  // 1985: ... -> val > 0:
  // 1986:   put &str '0'+(val & 1)
  // 1987:   !val val >> 1
  frame->slots[4] /* temp__1 */ = create_closure(entry__133_10, 0);
  // 1985: while -> val > 0:
  // 1986:   put &str '0'+(val & 1)
  // 1987:   !val val >> 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__while();
  func = myself->type;
  frame->cont = cont__133_17;
}
static void entry__133_12(void) {
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
  // 1986: ... val & 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* val */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__bit_and();
  func = myself->type;
  frame->cont = cont__133_13;
}
static void cont__133_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 1986: ... '0'+(val & 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__48;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__133_14;
}
static void cont__133_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 1986: put &str '0'+(val & 1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* str */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__put();
  func = myself->type;
  frame->cont = cont__133_15;
}
static void cont__133_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* str */ = arguments->slots[0];
  // 1987: !val val >> 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* val */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__shift_right();
  func = myself->type;
  frame->cont = cont__133_16;
}
static void cont__133_16(void) {
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
static void entry__133_10(void) {
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
  // 1985: ... val > 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* val */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__133_11;
}
static void cont__133_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 1985: ... :
  // 1986:   put &str '0'+(val & 1)
  // 1987:   !val val >> 1
  frame->slots[3] /* temp__2 */ = create_closure(entry__133_12, 0);
  // 1985: ... -> val > 0:
  // 1986:   put &str '0'+(val & 1)
  // 1987:   !val val >> 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__133_17(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1988: ... size.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* size */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__133_18;
}
static void cont__133_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 1988: ... : return pad_left(str size "0")
  frame->slots[5] /* temp__2 */ = create_closure(entry__133_19, 0);
  // 1988: if size.is_defined: return pad_left(str size "0")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__133_21;
}
static void entry__133_19(void) {
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
  // 1988: ... pad_left(str size "0")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* str */;
  arguments->slots[1] = frame->slots[2] /* size */;
  arguments->slots[2] = string__133_6;
  result_count = 1;
  myself = get__pad_left();
  func = myself->type;
  frame->cont = cont__133_20;
}
static void cont__133_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 1988: ... return pad_left(str size "0")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__133_21(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1989: -> str
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* str */;
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__134_1_std__oct(void) {
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
  // 1997: ... val == 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* val */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__134_2;
}
static void cont__134_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 1997: ... :
  // 1998:   if
  // 1999:     size.is_defined:
  // 2000:       return dup("0" size)
  // 2001:     :
  // 2002:       return "0"
  frame->slots[5] /* temp__2 */ = create_closure(entry__134_3, 0);
  // 1997: if val == 0:
  // 1998:   if
  // 1999:     size.is_defined:
  // 2000:       return dup("0" size)
  // 2001:     :
  // 2002:       return "0"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__134_8;
}
static void entry__134_5(void) {
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
  // 2000: ... dup("0" size)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__133_6;
  arguments->slots[1] = frame->slots[1] /* size */;
  result_count = 1;
  myself = get__dup();
  func = myself->type;
  frame->cont = cont__134_6;
}
static void cont__134_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 2000: return dup("0" size)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__134_7(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 2002: return "0"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__133_6;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__134_3(void) {
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
  // 1999: size.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* size */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__134_4;
}
static void cont__134_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 1999: ... :
  // 2000:   return dup("0" size)
  frame->slots[3] /* temp__2 */ = create_closure(entry__134_5, 0);
  // 2001: :
  // 2002:   return "0"
  frame->slots[4] /* temp__3 */ = create_closure(entry__134_7, 0);
  // 1998: if
  // 1999:   size.is_defined:
  // 2000:     return dup("0" size)
  // 2001:   :
  // 2002:     return "0"
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
static void cont__134_8(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 2003: $$str ""
  ((CELL *)frame->slots[3])->contents /* str */ = empty_string;
  // 2004: ... -> val > 0:
  // 2005:   put &str '0'+(val & 0x07)
  // 2006:   !val val >> 3
  frame->slots[4] /* temp__1 */ = create_closure(entry__134_9, 0);
  // 2004: while -> val > 0:
  // 2005:   put &str '0'+(val & 0x07)
  // 2006:   !val val >> 3
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__while();
  func = myself->type;
  frame->cont = cont__134_16;
}
static void entry__134_11(void) {
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
  // 2005: ... val & 0x07
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* val */;
  arguments->slots[1] = number__0x07;
  result_count = 1;
  myself = get__std__bit_and();
  func = myself->type;
  frame->cont = cont__134_12;
}
static void cont__134_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 2005: ... '0'+(val & 0x07
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__48;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__134_13;
}
static void cont__134_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 2005: put &str '0'+(val & 0x07)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* str */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__put();
  func = myself->type;
  frame->cont = cont__134_14;
}
static void cont__134_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* str */ = arguments->slots[0];
  // 2006: !val val >> 3
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* val */;
  arguments->slots[1] = number__3;
  result_count = 1;
  myself = get__std__shift_right();
  func = myself->type;
  frame->cont = cont__134_15;
}
static void cont__134_15(void) {
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
static void entry__134_9(void) {
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
  // 2004: ... val > 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* val */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__134_10;
}
static void cont__134_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 2004: ... :
  // 2005:   put &str '0'+(val & 0x07)
  // 2006:   !val val >> 3
  frame->slots[3] /* temp__2 */ = create_closure(entry__134_11, 0);
  // 2004: ... -> val > 0:
  // 2005:   put &str '0'+(val & 0x07)
  // 2006:   !val val >> 3
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__134_16(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 2007: ... size.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* size */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__134_17;
}
static void cont__134_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 2007: ... : return pad_left(str size "0")
  frame->slots[5] /* temp__2 */ = create_closure(entry__134_18, 0);
  // 2007: if size.is_defined: return pad_left(str size "0")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__134_20;
}
static void entry__134_18(void) {
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
  // 2007: ... pad_left(str size "0")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* str */;
  arguments->slots[1] = frame->slots[2] /* size */;
  arguments->slots[2] = string__133_6;
  result_count = 1;
  myself = get__pad_left();
  func = myself->type;
  frame->cont = cont__134_19;
}
static void cont__134_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 2007: ... return pad_left(str size "0")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__134_20(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 2008: -> str
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* str */;
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__135_1_std__hex(void) {
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
  // 2016: ... val == 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* val */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__135_2;
}
static void cont__135_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 2016: ... :
  // 2017:   if
  // 2018:     size.is_defined:
  // 2019:       return dup("0" size)
  // 2020:     :
  // 2021:       return "0"
  frame->slots[5] /* temp__2 */ = create_closure(entry__135_3, 0);
  // 2016: if val == 0:
  // 2017:   if
  // 2018:     size.is_defined:
  // 2019:       return dup("0" size)
  // 2020:     :
  // 2021:       return "0"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__135_8;
}
static void entry__135_5(void) {
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
  // 2019: ... dup("0" size)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__133_6;
  arguments->slots[1] = frame->slots[1] /* size */;
  result_count = 1;
  myself = get__dup();
  func = myself->type;
  frame->cont = cont__135_6;
}
static void cont__135_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 2019: return dup("0" size)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__135_7(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 2021: return "0"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__133_6;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__135_3(void) {
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
  // 2018: size.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* size */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__135_4;
}
static void cont__135_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 2018: ... :
  // 2019:   return dup("0" size)
  frame->slots[3] /* temp__2 */ = create_closure(entry__135_5, 0);
  // 2020: :
  // 2021:   return "0"
  frame->slots[4] /* temp__3 */ = create_closure(entry__135_7, 0);
  // 2017: if
  // 2018:   size.is_defined:
  // 2019:     return dup("0" size)
  // 2020:   :
  // 2021:     return "0"
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
static void cont__135_8(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 2022: $$str ""
  ((CELL *)frame->slots[3])->contents /* str */ = empty_string;
  // 2023: ... -> val > 0:
  // 2024:   $$hex_digit val & 0x0f
  // 2025:   if
  // 2026:     hex_digit >= 10:
  // 2027:       !hex_digit 'a'+hex_digit-10
  // 2028:     :
  // 2029:       !hex_digit '0'+hex_digit
  // 2030:   put &str hex_digit
  // 2031:   !val val >> 4
  frame->slots[4] /* temp__1 */ = create_closure(entry__135_9, 0);
  // 2023: while -> val > 0:
  // 2024:   $$hex_digit val & 0x0f
  // 2025:   if
  // 2026:     hex_digit >= 10:
  // 2027:       !hex_digit 'a'+hex_digit-10
  // 2028:     :
  // 2029:       !hex_digit '0'+hex_digit
  // 2030:   put &str hex_digit
  // 2031:   !val val >> 4
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__while();
  func = myself->type;
  frame->cont = cont__135_23;
}
static void entry__135_11(void) {
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
  // 2024: $$hex_digit val & 0x0f
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* val */;
  arguments->slots[1] = number__0x0f;
  result_count = 1;
  myself = get__std__bit_and();
  func = myself->type;
  frame->cont = cont__135_12;
}
static void cont__135_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* hex_digit */ = arguments->slots[0];
  // 2026: hex_digit >= 10
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* hex_digit */;
  arguments->slots[1] = number__10;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__135_13;
}
static void cont__135_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 2026: hex_digit >= 10
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__135_14;
}
static void cont__135_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 2026: ... :
  // 2027:   !hex_digit 'a'+hex_digit-10
  frame->slots[5] /* temp__3 */ = create_closure(entry__135_15, 0);
  // 2028: :
  // 2029:   !hex_digit '0'+hex_digit
  frame->slots[6] /* temp__4 */ = create_closure(entry__135_18, 0);
  // 2025: if
  // 2026:   hex_digit >= 10:
  // 2027:     !hex_digit 'a'+hex_digit-10
  // 2028:   :
  // 2029:     !hex_digit '0'+hex_digit
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  arguments->slots[2] = frame->slots[6] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__135_20;
}
static void entry__135_15(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // hex_digit: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* hex_digit */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 2027: ... 'a'+hex_digit
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__97;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* hex_digit */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__135_16;
}
static void cont__135_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 2027: !hex_digit 'a'+hex_digit-10
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = number__10;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__135_17;
}
static void cont__135_17(void) {
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
static void entry__135_18(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // hex_digit: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* hex_digit */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 2029: !hex_digit '0'+hex_digit
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__48;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* hex_digit */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__135_19;
}
static void cont__135_19(void) {
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
static void cont__135_20(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 2030: put &str hex_digit
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* str */;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* hex_digit */;
  result_count = 1;
  myself = get__put();
  func = myself->type;
  frame->cont = cont__135_21;
}
static void cont__135_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* str */ = arguments->slots[0];
  // 2031: !val val >> 4
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* val */;
  arguments->slots[1] = number__4;
  result_count = 1;
  myself = get__std__shift_right();
  func = myself->type;
  frame->cont = cont__135_22;
}
static void cont__135_22(void) {
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
static void entry__135_9(void) {
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
  // 2023: ... val > 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* val */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__135_10;
}
static void cont__135_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 2023: ... :
  // 2024:   $$hex_digit val & 0x0f
  // 2025:   if
  // 2026:     hex_digit >= 10:
  // 2027:       !hex_digit 'a'+hex_digit-10
  // 2028:     :
  // 2029:       !hex_digit '0'+hex_digit
  // 2030:   put &str hex_digit
  // 2031:   !val val >> 4
  frame->slots[3] /* temp__2 */ = create_closure(entry__135_11, 0);
  // 2023: ... -> val > 0:
  // 2024:   $$hex_digit val & 0x0f
  // 2025:   if
  // 2026:     hex_digit >= 10:
  // 2027:       !hex_digit 'a'+hex_digit-10
  // 2028:     :
  // 2029:       !hex_digit '0'+hex_digit
  // 2030:   put &str hex_digit
  // 2031:   !val val >> 4
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__135_23(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 2032: ... size.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* size */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__135_24;
}
static void cont__135_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 2032: ... : return pad_left(str size "0")
  frame->slots[5] /* temp__2 */ = create_closure(entry__135_25, 0);
  // 2032: if size.is_defined: return pad_left(str size "0")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__135_27;
}
static void entry__135_25(void) {
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
  // 2032: ... pad_left(str size "0")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* str */;
  arguments->slots[1] = frame->slots[2] /* size */;
  arguments->slots[2] = string__133_6;
  result_count = 1;
  myself = get__pad_left();
  func = myself->type;
  frame->cont = cont__135_26;
}
static void cont__135_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 2032: ... return pad_left(str size "0")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__135_27(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 2033: -> str
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* str */;
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__136_1_types__integer_to_integer(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // value: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 2035: ... -> value
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* value */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__137_1_types__real_to_integer(void) {
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
static void entry__138_1_types__number_floor(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // self: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 2044: ... -> self
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__139_1_types__number_ceil(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // self: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 2046: ... -> self
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__140_1_types__number_round(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // self: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 2048: ... -> self
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__141_1_types__real_floor(void) {
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
static void entry__142_1_types__real_ceil(void) {
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
static void entry__143_1_types__real_round(void) {
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
static void entry__144_1_types__real_ln(void) {
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
  number__0 = from_uint32(0U);
  number__3 = from_uint32(3U);
  character__48 = from_uchar32(48);
  number__4 = from_uint32(4U);
  number__0x0f = from_uint32(15U);
  character__97 = from_uchar32(97);
  number__1 = from_uint32(1U);
  number__10 = from_uint32(10U);
  number__0x07 = from_uint32(7U);
  func__58_1_types__positive_integer_negate = create_function(entry__58_1_types__positive_integer_negate, 1);
  func__59_1_types__negative_integer_negate = create_function(entry__59_1_types__negative_integer_negate, 1);
  func__60_1_types__positive_large_integer_negate = create_function(entry__60_1_types__positive_large_integer_negate, 1);
  func__61_1_types__negative_large_integer_negate = create_function(entry__61_1_types__negative_large_integer_negate, 1);
  func__62_1_types__real_negate = create_function(entry__62_1_types__real_negate, 1);
  func__66_1_types__positive_integer_plus = create_function(entry__66_1_types__positive_integer_plus, 2);
  func__67_1_types__positive_integer_minus = create_function(entry__67_1_types__positive_integer_minus, 2);
  func__68_1_types__negative_integer_plus = create_function(entry__68_1_types__negative_integer_plus, 2);
  func__69_1_types__negative_integer_minus = create_function(entry__69_1_types__negative_integer_minus, 2);
  func__72_1_types__positive_large_integer_plus = create_function(entry__72_1_types__positive_large_integer_plus, 2);
  func__73_1_types__positive_large_integer_minus = create_function(entry__73_1_types__positive_large_integer_minus, 2);
  func__74_1_types__negative_large_integer_plus = create_function(entry__74_1_types__negative_large_integer_plus, 2);
  func__75_1_types__negative_large_integer_minus = create_function(entry__75_1_types__negative_large_integer_minus, 2);
  func__76_1_types__real_plus = create_function(entry__76_1_types__real_plus, 2);
  func__77_1_types__real_minus = create_function(entry__77_1_types__real_minus, 2);
  func__79_1_types__positive_integer_times = create_function(entry__79_1_types__positive_integer_times, 2);
  func__80_1_types__negative_integer_times = create_function(entry__80_1_types__negative_integer_times, 2);
  func__82_1_types__positive_large_integer_times = create_function(entry__82_1_types__positive_large_integer_times, 2);
  func__83_1_types__negative_large_integer_times = create_function(entry__83_1_types__negative_large_integer_times, 2);
  func__84_1_types__real_times = create_function(entry__84_1_types__real_times, 2);
  func__86_1_types__positive_integer_over = create_function(entry__86_1_types__positive_integer_over, 2);
  func__87_1_types__negative_integer_over = create_function(entry__87_1_types__negative_integer_over, 2);
  func__89_1_types__positive_large_integer_over = create_function(entry__89_1_types__positive_large_integer_over, 2);
  func__90_1_types__negative_large_integer_over = create_function(entry__90_1_types__negative_large_integer_over, 2);
  func__91_1_types__real_over = create_function(entry__91_1_types__real_over, 2);
  func__92_1_types__positive_integer_div = create_function(entry__92_1_types__positive_integer_div, 2);
  func__93_1_types__positive_integer_mod = create_function(entry__93_1_types__positive_integer_mod, 2);
  func__94_1_types__positive_integer_equal = create_function(entry__94_1_types__positive_integer_equal, 2);
  func__95_1_types__positive_integer_equal_type_and_value = create_function(entry__95_1_types__positive_integer_equal_type_and_value, 2);
  func__96_1_types__negative_integer_equal = create_function(entry__96_1_types__negative_integer_equal, 2);
  func__97_1_types__negative_integer_equal_type_and_value = create_function(entry__97_1_types__negative_integer_equal_type_and_value, 2);
  func__98_1_types__positive_large_integer_equal = create_function(entry__98_1_types__positive_large_integer_equal, 2);
  func__99_1_types__positive_large_integer_equal_type_and_value = create_function(entry__99_1_types__positive_large_integer_equal_type_and_value, 2);
  func__100_1_types__negative_large_integer_equal = create_function(entry__100_1_types__negative_large_integer_equal, 2);
  func__101_1_types__negative_large_integer_equal_type_and_value = create_function(entry__101_1_types__negative_large_integer_equal_type_and_value, 2);
  func__102_1_types__real_equal = create_function(entry__102_1_types__real_equal, 2);
  func__103_1_types__real_equal_type_and_value = create_function(entry__103_1_types__real_equal_type_and_value, 2);
  func__104_1_types__positive_integer_less = create_function(entry__104_1_types__positive_integer_less, 2);
  func__105_1_types__negative_integer_less = create_function(entry__105_1_types__negative_integer_less, 2);
  func__106_1_types__positive_large_integer_less = create_function(entry__106_1_types__positive_large_integer_less, 2);
  func__107_1_types__negative_large_integer_less = create_function(entry__107_1_types__negative_large_integer_less, 2);
  func__108_1_types__real_less = create_function(entry__108_1_types__real_less, 2);
  func__111_1_types__positive_integer_shift_left = create_function(entry__111_1_types__positive_integer_shift_left, 2);
  func__112_1_types__positive_large_integer_shift_left = create_function(entry__112_1_types__positive_large_integer_shift_left, 2);
  func__113_1_types__positive_integer_shift_right = create_function(entry__113_1_types__positive_integer_shift_right, 2);
  func__114_1_types__positive_large_integer_shift_right = create_function(entry__114_1_types__positive_large_integer_shift_right, 2);
  func__115_1_types__positive_integer_bit_or = create_function(entry__115_1_types__positive_integer_bit_or, 2);
  func__116_1_types__positive_integer_bit_and = create_function(entry__116_1_types__positive_integer_bit_and, 2);
  func__117_1_types__positive_integer_bit_xor = create_function(entry__117_1_types__positive_integer_bit_xor, 2);
  func__118_1_types__positive_integer_hash = create_function(entry__118_1_types__positive_integer_hash, 1);
  func__119_1_types__negative_integer_hash = create_function(entry__119_1_types__negative_integer_hash, 1);
  func__120_1_types__positive_integer_to_string = create_function(entry__120_1_types__positive_integer_to_string, 1);
  func__122_1_types__negative_integer_to_string = create_function(entry__122_1_types__negative_integer_to_string, 1);
  func__125_1_types__positive_large_integer_to_string = create_function(entry__125_1_types__positive_large_integer_to_string, 1);
  func__127_1_types__negative_large_integer_to_string = create_function(entry__127_1_types__negative_large_integer_to_string, 1);
  func__129_1_types__real_to_string = create_function(entry__129_1_types__real_to_string, 1);
  func__131_1_std__is_odd = create_function(entry__131_1_std__is_odd, 1);
  func__132_1_std__is_even = create_function(entry__132_1_std__is_even, 1);
  string__133_6 = from_latin_1_string("0", 1);
  func__133_1_std__bin = create_function(entry__133_1_std__bin, -1);
  func__134_1_std__oct = create_function(entry__134_1_std__oct, -1);
  func__135_1_std__hex = create_function(entry__135_1_std__hex, -1);
  func__136_1_types__integer_to_integer = create_function(entry__136_1_types__integer_to_integer, 1);
  func__137_1_types__real_to_integer = create_function(entry__137_1_types__real_to_integer, 1);
  func__138_1_types__number_floor = create_function(entry__138_1_types__number_floor, 1);
  func__139_1_types__number_ceil = create_function(entry__139_1_types__number_ceil, 1);
  func__140_1_types__number_round = create_function(entry__140_1_types__number_round, 1);
  func__141_1_types__real_floor = create_function(entry__141_1_types__real_floor, 1);
  func__142_1_types__real_ceil = create_function(entry__142_1_types__real_ceil, 1);
  func__143_1_types__real_round = create_function(entry__143_1_types__real_round, 1);
  func__144_1_types__real_ln = create_function(entry__144_1_types__real_ln, 1);
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
  define_method("types", "positive_integer", poly_idx__negate, func__58_1_types__positive_integer_negate);
  define_method("types", "negative_integer", poly_idx__negate, func__59_1_types__negative_integer_negate);
  define_method("types", "positive_large_integer", poly_idx__negate, func__60_1_types__positive_large_integer_negate);
  define_method("types", "negative_large_integer", poly_idx__negate, func__61_1_types__negative_large_integer_negate);
  define_method("types", "real", poly_idx__negate, func__62_1_types__real_negate);
  define_method("types", "positive_integer", poly_idx__plus, func__66_1_types__positive_integer_plus);
  define_method("types", "positive_integer", poly_idx__minus, func__67_1_types__positive_integer_minus);
  define_method("types", "negative_integer", poly_idx__plus, func__68_1_types__negative_integer_plus);
  define_method("types", "negative_integer", poly_idx__minus, func__69_1_types__negative_integer_minus);
  define_method("types", "positive_large_integer", poly_idx__plus, func__72_1_types__positive_large_integer_plus);
  define_method("types", "positive_large_integer", poly_idx__minus, func__73_1_types__positive_large_integer_minus);
  define_method("types", "negative_large_integer", poly_idx__plus, func__74_1_types__negative_large_integer_plus);
  define_method("types", "negative_large_integer", poly_idx__minus, func__75_1_types__negative_large_integer_minus);
  define_method("types", "real", poly_idx__plus, func__76_1_types__real_plus);
  define_method("types", "real", poly_idx__minus, func__77_1_types__real_minus);
  define_method("types", "positive_integer", poly_idx__times, func__79_1_types__positive_integer_times);
  define_method("types", "negative_integer", poly_idx__times, func__80_1_types__negative_integer_times);
  define_method("types", "positive_large_integer", poly_idx__times, func__82_1_types__positive_large_integer_times);
  define_method("types", "negative_large_integer", poly_idx__times, func__83_1_types__negative_large_integer_times);
  define_method("types", "real", poly_idx__times, func__84_1_types__real_times);
  define_method("types", "positive_integer", poly_idx__over, func__86_1_types__positive_integer_over);
  define_method("types", "negative_integer", poly_idx__over, func__87_1_types__negative_integer_over);
  define_method("types", "positive_large_integer", poly_idx__over, func__89_1_types__positive_large_integer_over);
  define_method("types", "negative_large_integer", poly_idx__over, func__90_1_types__negative_large_integer_over);
  define_method("types", "real", poly_idx__over, func__91_1_types__real_over);
  define_method("types", "positive_integer", poly_idx__div, func__92_1_types__positive_integer_div);
  define_method("types", "positive_integer", poly_idx__mod, func__93_1_types__positive_integer_mod);
  define_method("types", "positive_integer", poly_idx__equal, func__94_1_types__positive_integer_equal);
  define_method("types", "positive_integer", poly_idx__equal_type_and_value, func__95_1_types__positive_integer_equal_type_and_value);
  define_method("types", "negative_integer", poly_idx__equal, func__96_1_types__negative_integer_equal);
  define_method("types", "negative_integer", poly_idx__equal_type_and_value, func__97_1_types__negative_integer_equal_type_and_value);
  define_method("types", "positive_large_integer", poly_idx__equal, func__98_1_types__positive_large_integer_equal);
  define_method("types", "positive_large_integer", poly_idx__equal_type_and_value, func__99_1_types__positive_large_integer_equal_type_and_value);
  define_method("types", "negative_large_integer", poly_idx__equal, func__100_1_types__negative_large_integer_equal);
  define_method("types", "negative_large_integer", poly_idx__equal_type_and_value, func__101_1_types__negative_large_integer_equal_type_and_value);
  define_method("types", "real", poly_idx__equal, func__102_1_types__real_equal);
  define_method("types", "real", poly_idx__equal_type_and_value, func__103_1_types__real_equal_type_and_value);
  define_method("types", "positive_integer", poly_idx__less, func__104_1_types__positive_integer_less);
  define_method("types", "negative_integer", poly_idx__less, func__105_1_types__negative_integer_less);
  define_method("types", "positive_large_integer", poly_idx__less, func__106_1_types__positive_large_integer_less);
  define_method("types", "negative_large_integer", poly_idx__less, func__107_1_types__negative_large_integer_less);
  define_method("types", "real", poly_idx__less, func__108_1_types__real_less);
  define_method("types", "positive_integer", poly_idx__shift_left, func__111_1_types__positive_integer_shift_left);
  define_method("types", "positive_large_integer", poly_idx__shift_left, func__112_1_types__positive_large_integer_shift_left);
  define_method("types", "positive_integer", poly_idx__shift_right, func__113_1_types__positive_integer_shift_right);
  define_method("types", "positive_large_integer", poly_idx__shift_right, func__114_1_types__positive_large_integer_shift_right);
  define_method("types", "positive_integer", poly_idx__bit_or, func__115_1_types__positive_integer_bit_or);
  define_method("types", "positive_integer", poly_idx__bit_and, func__116_1_types__positive_integer_bit_and);
  define_method("types", "positive_integer", poly_idx__bit_xor, func__117_1_types__positive_integer_bit_xor);
  define_method("types", "positive_integer", poly_idx__hash, func__118_1_types__positive_integer_hash);
  define_method("types", "negative_integer", poly_idx__hash, func__119_1_types__negative_integer_hash);
  define_method("types", "positive_integer", poly_idx__to_string, func__120_1_types__positive_integer_to_string);
  define_method("types", "negative_integer", poly_idx__to_string, func__122_1_types__negative_integer_to_string);
  define_method("types", "positive_large_integer", poly_idx__to_string, func__125_1_types__positive_large_integer_to_string);
  define_method("types", "negative_large_integer", poly_idx__to_string, func__127_1_types__negative_large_integer_to_string);
  define_method("types", "real", poly_idx__to_string, func__129_1_types__real_to_string);
  define_method("types", "integer", poly_idx__to_integer, func__136_1_types__integer_to_integer);
  define_method("types", "real", poly_idx__to_integer, func__137_1_types__real_to_integer);
  define_method("types", "number", poly_idx__floor, func__138_1_types__number_floor);
  define_method("types", "number", poly_idx__ceil, func__139_1_types__number_ceil);
  define_method("types", "number", poly_idx__round, func__140_1_types__number_round);
  define_method("types", "real", poly_idx__floor, func__141_1_types__real_floor);
  define_method("types", "real", poly_idx__ceil, func__142_1_types__real_ceil);
  define_method("types", "real", poly_idx__round, func__143_1_types__real_round);
  define_method("types", "real", poly_idx__ln, func__144_1_types__real_ln);
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
  assign_variable(&var.std__is_odd, &func__131_1_std__is_odd);
  assign_variable(&var.std__is_even, &func__132_1_std__is_even);
  assign_variable(&var.std__bin, &func__133_1_std__bin);
  assign_variable(&var.std__oct, &func__134_1_std__oct);
  assign_variable(&var.std__hex, &func__135_1_std__hex);
}

static int already_run_phase_6 = false;

EXPORT void phase_6__basic__types__number(void) {
  if (already_run_phase_6) return;
  already_run_phase_6 = true;
  register_collector(collect__basic__types__number);
}
