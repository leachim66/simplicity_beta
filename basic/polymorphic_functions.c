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
IMPORT NODE *collect_node(NODE *node);
IMPORT void register_module_info(MODULE_INFO *info);
typedef NODE *(*NODE_GETTER)(void);
IMPORT void define_polymorphic_function(
  const char *namespace, const char *name, NODE_GETTER getter, int *id_p,
  NODE **var_p
);
IMPORT void define_privileged_polymorphic_function(
  const char *namespace, const char *name, NODE_GETTER getter, int id,
  NODE **var_p
);
IMPORT void define_polymorphic_function_with_setter(
  const char *namespace, const char *name, NODE_GETTER getter, int *id_p,
  NODE **var_p
);
IMPORT void set_module(const char *name);
IMPORT void set_used_namespaces(const char **namespaces);
IMPORT void assign_value(NODE **dest, NODE *val);
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
static struct {
  NODE *std__plus;
  NODE *std__minus;
  NODE *std__times;
  NODE *std__over;
  NODE *std__div;
  NODE *std__mod;
  NODE *std__negate;
  NODE *std__equal;
  NODE *std__equal_type_and_value;
  NODE *std__less;
  NODE *std__numerically_less;
  NODE *std__not;
  NODE *std__and;
  NODE *std__or;
  NODE *std__if;
  NODE *std__unless;
  NODE *std__shift_left;
  NODE *std__shift_right;
  NODE *std__bit_and;
  NODE *std__bit_or;
  NODE *std__bit_xor;
  NODE *std__parameter_count_of;
  NODE *std__is_defined;
  NODE *std__is_undefined;
  NODE *std__default_value;
  NODE *std__is_valid;
  NODE *std__to_string;
  NODE *std__to_list;
  NODE *std__serialize;
  NODE *std__serialization_tag_of;
  NODE *std__to_number;
  NODE *std__parse_number;
  NODE *std__to_integer;
  NODE *std__parse_integer;
  NODE *std__to_real;
  NODE *std__parse_real;
  NODE *std__to_lower_case;
  NODE *std__to_upper_case;
  NODE *std__to_title_case;
  NODE *std__is_empty;
  NODE *std__length_of;
  NODE *std__type_of;
  NODE *std__hash;
  NODE *std__push;
  NODE *std__pop;
  NODE *std__peek;
  NODE *std__drop;
  NODE *std__put;
  NODE *std__get;
  NODE *std__next;
  NODE *std__append;
  NODE *std__insert_before;
  NODE *std__insert_behind;
  NODE *std__first_index_of;
  NODE *std__last_index_of;
  NODE *std__delete_at;
  NODE *std__union;
  NODE *std__intersection;
  NODE *std__match_character;
  NODE *std__match_string;
  NODE *std__search_character;
  NODE *std__search_string;
  NODE *std__match;
  NODE *std__search;
  NODE *std__matches;
  NODE *std__contains;
  NODE *std__has_prefix;
  NODE *std__has_suffix;
  NODE *std__without_prefix;
  NODE *std__without_suffix;
  NODE *std__before;
  NODE *std__truncate_from;
  NODE *std__behind;
  NODE *std__truncate_until;
  NODE *std__from;
  NODE *std__truncate_before;
  NODE *std__until;
  NODE *std__truncate_behind;
  NODE *std__between;
  NODE *std__range;
  NODE *std__merge;
  NODE *std__sort;
  NODE *std__close;
  NODE *std__write_some_bytes_to;
  NODE *std__write_to;
  NODE *std__flush;
  NODE *std__read_some_bytes_from;
  NODE *std__read_from;
  NODE *std__key_of;
  NODE *std__value_of;
  NODE *std__keys_of;
  NODE *std__values_of;
  NODE *std__lower_bound_of;
  NODE *std__upper_bound_of;
  NODE *std__for_each_from_to;
  NODE *std__for_each_from_down_to;
  NODE *std__for_each;
  NODE *std__for_each_downwards;
  NODE *std__update_each_from_to;
  NODE *std__update_each_from_down_to;
  NODE *std__update_each;
  NODE *std__update_each_downwards;
  NODE *std__for_each_pair;
  NODE *std__new_empty_collection;
  NODE *std__filter;
  NODE *std__map;
  NODE *std__dup;
  NODE *std__interleave;
  NODE *std__stop;
  NODE *std__get_file_descriptors;
  NODE *std__handle_requests;
  NODE *std__select;
  NODE *std__delete;
  NODE *std__update;
  NODE *std__call_command;
} var;
static const char *var_names[] = {
};
static int poly_idx__std__plus;
static void type__std__plus(void);
static NODE *get__std__plus(void) {
  return var.std__plus;
}
static int poly_idx__std__minus;
static void type__std__minus(void);
static NODE *get__std__minus(void) {
  return var.std__minus;
}
static int poly_idx__std__times;
static void type__std__times(void);
static NODE *get__std__times(void) {
  return var.std__times;
}
static int poly_idx__std__over;
static void type__std__over(void);
static NODE *get__std__over(void) {
  return var.std__over;
}
static int poly_idx__std__div;
static void type__std__div(void);
static NODE *get__std__div(void) {
  return var.std__div;
}
static int poly_idx__std__mod;
static void type__std__mod(void);
static NODE *get__std__mod(void) {
  return var.std__mod;
}
static int poly_idx__std__negate;
static void type__std__negate(void);
static NODE *get__std__negate(void) {
  return var.std__negate;
}
static int poly_idx__std__equal = 2;
static void type__std__equal(void);
static NODE *get__std__equal(void) {
  return var.std__equal;
}
static int poly_idx__std__equal_type_and_value;
static void type__std__equal_type_and_value(void);
static NODE *get__std__equal_type_and_value(void) {
  return var.std__equal_type_and_value;
}
static int poly_idx__std__less = 3;
static void type__std__less(void);
static NODE *get__std__less(void) {
  return var.std__less;
}
static int poly_idx__std__numerically_less;
static void type__std__numerically_less(void);
static NODE *get__std__numerically_less(void) {
  return var.std__numerically_less;
}
static int poly_idx__std__not;
static void type__std__not(void);
static NODE *get__std__not(void) {
  return var.std__not;
}
static int poly_idx__std__and;
static void type__std__and(void);
static NODE *get__std__and(void) {
  return var.std__and;
}
static int poly_idx__std__or;
static void type__std__or(void);
static NODE *get__std__or(void) {
  return var.std__or;
}
static int poly_idx__std__if = 0;
static void type__std__if(void);
static NODE *get__std__if(void) {
  return var.std__if;
}
static int poly_idx__std__unless = 6;
static void type__std__unless(void);
static NODE *get__std__unless(void) {
  return var.std__unless;
}
static int poly_idx__std__shift_left;
static void type__std__shift_left(void);
static NODE *get__std__shift_left(void) {
  return var.std__shift_left;
}
static int poly_idx__std__shift_right;
static void type__std__shift_right(void);
static NODE *get__std__shift_right(void) {
  return var.std__shift_right;
}
static int poly_idx__std__bit_and;
static void type__std__bit_and(void);
static NODE *get__std__bit_and(void) {
  return var.std__bit_and;
}
static int poly_idx__std__bit_or;
static void type__std__bit_or(void);
static NODE *get__std__bit_or(void) {
  return var.std__bit_or;
}
static int poly_idx__std__bit_xor;
static void type__std__bit_xor(void);
static NODE *get__std__bit_xor(void) {
  return var.std__bit_xor;
}
static int poly_idx__std__parameter_count_of;
static void type__std__parameter_count_of(void);
static NODE *get__std__parameter_count_of(void) {
  return var.std__parameter_count_of;
}
static int poly_idx__std__is_defined = 1;
static void type__std__is_defined(void);
static NODE *get__std__is_defined(void) {
  return var.std__is_defined;
}
static int poly_idx__std__is_undefined;
static void type__std__is_undefined(void);
static NODE *get__std__is_undefined(void) {
  return var.std__is_undefined;
}
static int poly_idx__std__default_value;
static void type__std__default_value(void);
static NODE *get__std__default_value(void) {
  return var.std__default_value;
}
static int poly_idx__std__is_valid;
static void type__std__is_valid(void);
static NODE *get__std__is_valid(void) {
  return var.std__is_valid;
}
static int poly_idx__std__to_string;
static void type__std__to_string(void);
static NODE *get__std__to_string(void) {
  return var.std__to_string;
}
static int poly_idx__std__to_list;
static void type__std__to_list(void);
static NODE *get__std__to_list(void) {
  return var.std__to_list;
}
static int poly_idx__std__serialize;
static void type__std__serialize(void);
static NODE *get__std__serialize(void) {
  return var.std__serialize;
}
static int poly_idx__std__serialization_tag_of;
static void type__std__serialization_tag_of(void);
static NODE *get__std__serialization_tag_of(void) {
  return var.std__serialization_tag_of;
}
static int poly_idx__std__to_number;
static void type__std__to_number(void);
static NODE *get__std__to_number(void) {
  return var.std__to_number;
}
static int poly_idx__std__parse_number;
static void type__std__parse_number(void);
static NODE *get__std__parse_number(void) {
  return var.std__parse_number;
}
static int poly_idx__std__to_integer;
static void type__std__to_integer(void);
static NODE *get__std__to_integer(void) {
  return var.std__to_integer;
}
static int poly_idx__std__parse_integer;
static void type__std__parse_integer(void);
static NODE *get__std__parse_integer(void) {
  return var.std__parse_integer;
}
static int poly_idx__std__to_real;
static void type__std__to_real(void);
static NODE *get__std__to_real(void) {
  return var.std__to_real;
}
static int poly_idx__std__parse_real;
static void type__std__parse_real(void);
static NODE *get__std__parse_real(void) {
  return var.std__parse_real;
}
static int poly_idx__std__to_lower_case;
static void type__std__to_lower_case(void);
static NODE *get__std__to_lower_case(void) {
  return var.std__to_lower_case;
}
static int poly_idx__std__to_upper_case;
static void type__std__to_upper_case(void);
static NODE *get__std__to_upper_case(void) {
  return var.std__to_upper_case;
}
static int poly_idx__std__to_title_case;
static void type__std__to_title_case(void);
static NODE *get__std__to_title_case(void) {
  return var.std__to_title_case;
}
static int poly_idx__std__is_empty = 5;
static void type__std__is_empty(void);
static NODE *get__std__is_empty(void) {
  return var.std__is_empty;
}
static int poly_idx__std__length_of = 4;
static void type__std__length_of(void);
static NODE *get__std__length_of(void) {
  return var.std__length_of;
}
static int poly_idx__std__type_of;
static void type__std__type_of(void);
static NODE *get__std__type_of(void) {
  return var.std__type_of;
}
static int poly_idx__std__hash;
static void type__std__hash(void);
static NODE *get__std__hash(void) {
  return var.std__hash;
}
static int poly_idx__std__push;
static void type__std__push(void);
static NODE *get__std__push(void) {
  return var.std__push;
}
static int poly_idx__std__pop;
static void type__std__pop(void);
static NODE *get__std__pop(void) {
  return var.std__pop;
}
static int poly_idx__std__peek;
static void type__std__peek(void);
static NODE *get__std__peek(void) {
  return var.std__peek;
}
static int poly_idx__std__drop;
static void type__std__drop(void);
static NODE *get__std__drop(void) {
  return var.std__drop;
}
static int poly_idx__std__put;
static void type__std__put(void);
static NODE *get__std__put(void) {
  return var.std__put;
}
static int poly_idx__std__get;
static void type__std__get(void);
static NODE *get__std__get(void) {
  return var.std__get;
}
static int poly_idx__std__next;
static void type__std__next(void);
static NODE *get__std__next(void) {
  return var.std__next;
}
static int poly_idx__std__append;
static void type__std__append(void);
static NODE *get__std__append(void) {
  return var.std__append;
}
static int poly_idx__std__insert_before;
static void type__std__insert_before(void);
static NODE *get__std__insert_before(void) {
  return var.std__insert_before;
}
static int poly_idx__std__insert_behind;
static void type__std__insert_behind(void);
static NODE *get__std__insert_behind(void) {
  return var.std__insert_behind;
}
static int poly_idx__std__first_index_of;
static void type__std__first_index_of(void);
static NODE *get__std__first_index_of(void) {
  return var.std__first_index_of;
}
static int poly_idx__std__last_index_of;
static void type__std__last_index_of(void);
static NODE *get__std__last_index_of(void) {
  return var.std__last_index_of;
}
static int poly_idx__std__delete_at;
static void type__std__delete_at(void);
static NODE *get__std__delete_at(void) {
  return var.std__delete_at;
}
static int poly_idx__std__union;
static void type__std__union(void);
static NODE *get__std__union(void) {
  return var.std__union;
}
static int poly_idx__std__intersection;
static void type__std__intersection(void);
static NODE *get__std__intersection(void) {
  return var.std__intersection;
}
static int poly_idx__std__match_character;
static void type__std__match_character(void);
static NODE *get__std__match_character(void) {
  return var.std__match_character;
}
static int poly_idx__std__match_string;
static void type__std__match_string(void);
static NODE *get__std__match_string(void) {
  return var.std__match_string;
}
static int poly_idx__std__search_character;
static void type__std__search_character(void);
static NODE *get__std__search_character(void) {
  return var.std__search_character;
}
static int poly_idx__std__search_string;
static void type__std__search_string(void);
static NODE *get__std__search_string(void) {
  return var.std__search_string;
}
static int poly_idx__std__match;
static void type__std__match(void);
static NODE *get__std__match(void) {
  return var.std__match;
}
static int poly_idx__std__search;
static void type__std__search(void);
static NODE *get__std__search(void) {
  return var.std__search;
}
static int poly_idx__std__matches;
static void type__std__matches(void);
static NODE *get__std__matches(void) {
  return var.std__matches;
}
static int poly_idx__std__contains;
static void type__std__contains(void);
static NODE *get__std__contains(void) {
  return var.std__contains;
}
static int poly_idx__std__has_prefix;
static void type__std__has_prefix(void);
static NODE *get__std__has_prefix(void) {
  return var.std__has_prefix;
}
static int poly_idx__std__has_suffix;
static void type__std__has_suffix(void);
static NODE *get__std__has_suffix(void) {
  return var.std__has_suffix;
}
static int poly_idx__std__without_prefix;
static void type__std__without_prefix(void);
static NODE *get__std__without_prefix(void) {
  return var.std__without_prefix;
}
static int poly_idx__std__without_suffix;
static void type__std__without_suffix(void);
static NODE *get__std__without_suffix(void) {
  return var.std__without_suffix;
}
static int poly_idx__std__before;
static void type__std__before(void);
static NODE *get__std__before(void) {
  return var.std__before;
}
static int poly_idx__std__truncate_from;
static void type__std__truncate_from(void);
static NODE *get__std__truncate_from(void) {
  return var.std__truncate_from;
}
static int poly_idx__std__behind;
static void type__std__behind(void);
static NODE *get__std__behind(void) {
  return var.std__behind;
}
static int poly_idx__std__truncate_until;
static void type__std__truncate_until(void);
static NODE *get__std__truncate_until(void) {
  return var.std__truncate_until;
}
static int poly_idx__std__from;
static void type__std__from(void);
static NODE *get__std__from(void) {
  return var.std__from;
}
static int poly_idx__std__truncate_before;
static void type__std__truncate_before(void);
static NODE *get__std__truncate_before(void) {
  return var.std__truncate_before;
}
static int poly_idx__std__until;
static void type__std__until(void);
static NODE *get__std__until(void) {
  return var.std__until;
}
static int poly_idx__std__truncate_behind;
static void type__std__truncate_behind(void);
static NODE *get__std__truncate_behind(void) {
  return var.std__truncate_behind;
}
static int poly_idx__std__between;
static void type__std__between(void);
static NODE *get__std__between(void) {
  return var.std__between;
}
static int poly_idx__std__range;
static void type__std__range(void);
static NODE *get__std__range(void) {
  return var.std__range;
}
static int poly_idx__std__merge;
static void type__std__merge(void);
static NODE *get__std__merge(void) {
  return var.std__merge;
}
static int poly_idx__std__sort;
static void type__std__sort(void);
static NODE *get__std__sort(void) {
  return var.std__sort;
}
static int poly_idx__std__close;
static void type__std__close(void);
static NODE *get__std__close(void) {
  return var.std__close;
}
static int poly_idx__std__write_some_bytes_to;
static void type__std__write_some_bytes_to(void);
static NODE *get__std__write_some_bytes_to(void) {
  return var.std__write_some_bytes_to;
}
static int poly_idx__std__write_to;
static void type__std__write_to(void);
static NODE *get__std__write_to(void) {
  return var.std__write_to;
}
static int poly_idx__std__flush;
static void type__std__flush(void);
static NODE *get__std__flush(void) {
  return var.std__flush;
}
static int poly_idx__std__read_some_bytes_from;
static void type__std__read_some_bytes_from(void);
static NODE *get__std__read_some_bytes_from(void) {
  return var.std__read_some_bytes_from;
}
static int poly_idx__std__read_from;
static void type__std__read_from(void);
static NODE *get__std__read_from(void) {
  return var.std__read_from;
}
static int poly_idx__std__key_of;
static void type__std__key_of(void);
static NODE *get__std__key_of(void) {
  return var.std__key_of;
}
static int poly_idx__std__value_of;
static void type__std__value_of(void);
static NODE *get__std__value_of(void) {
  return var.std__value_of;
}
static int poly_idx__std__keys_of;
static void type__std__keys_of(void);
static NODE *get__std__keys_of(void) {
  return var.std__keys_of;
}
static int poly_idx__std__values_of;
static void type__std__values_of(void);
static NODE *get__std__values_of(void) {
  return var.std__values_of;
}
static int poly_idx__std__lower_bound_of;
static void type__std__lower_bound_of(void);
static NODE *get__std__lower_bound_of(void) {
  return var.std__lower_bound_of;
}
static int poly_idx__std__upper_bound_of;
static void type__std__upper_bound_of(void);
static NODE *get__std__upper_bound_of(void) {
  return var.std__upper_bound_of;
}
static int poly_idx__std__for_each_from_to;
static void type__std__for_each_from_to(void);
static NODE *get__std__for_each_from_to(void) {
  return var.std__for_each_from_to;
}
static int poly_idx__std__for_each_from_down_to;
static void type__std__for_each_from_down_to(void);
static NODE *get__std__for_each_from_down_to(void) {
  return var.std__for_each_from_down_to;
}
static int poly_idx__std__for_each;
static void type__std__for_each(void);
static NODE *get__std__for_each(void) {
  return var.std__for_each;
}
static int poly_idx__std__for_each_downwards;
static void type__std__for_each_downwards(void);
static NODE *get__std__for_each_downwards(void) {
  return var.std__for_each_downwards;
}
static int poly_idx__std__update_each_from_to;
static void type__std__update_each_from_to(void);
static NODE *get__std__update_each_from_to(void) {
  return var.std__update_each_from_to;
}
static int poly_idx__std__update_each_from_down_to;
static void type__std__update_each_from_down_to(void);
static NODE *get__std__update_each_from_down_to(void) {
  return var.std__update_each_from_down_to;
}
static int poly_idx__std__update_each;
static void type__std__update_each(void);
static NODE *get__std__update_each(void) {
  return var.std__update_each;
}
static int poly_idx__std__update_each_downwards;
static void type__std__update_each_downwards(void);
static NODE *get__std__update_each_downwards(void) {
  return var.std__update_each_downwards;
}
static int poly_idx__std__for_each_pair;
static void type__std__for_each_pair(void);
static NODE *get__std__for_each_pair(void) {
  return var.std__for_each_pair;
}
static int poly_idx__std__new_empty_collection;
static void type__std__new_empty_collection(void);
static NODE *get__std__new_empty_collection(void) {
  return var.std__new_empty_collection;
}
static int poly_idx__std__filter;
static void type__std__filter(void);
static NODE *get__std__filter(void) {
  return var.std__filter;
}
static int poly_idx__std__map;
static void type__std__map(void);
static NODE *get__std__map(void) {
  return var.std__map;
}
static int poly_idx__std__dup;
static void type__std__dup(void);
static NODE *get__std__dup(void) {
  return var.std__dup;
}
static int poly_idx__std__interleave;
static void type__std__interleave(void);
static NODE *get__std__interleave(void) {
  return var.std__interleave;
}
static int poly_idx__std__stop;
static void type__std__stop(void);
static NODE *get__std__stop(void) {
  return var.std__stop;
}
static int poly_idx__std__get_file_descriptors;
static void type__std__get_file_descriptors(void);
static NODE *get__std__get_file_descriptors(void) {
  return var.std__get_file_descriptors;
}
static int poly_idx__std__handle_requests;
static void type__std__handle_requests(void);
static NODE *get__std__handle_requests(void) {
  return var.std__handle_requests;
}
static int poly_idx__std__select;
static void type__std__select(void);
static NODE *get__std__select(void) {
  return var.std__select;
}
static int poly_idx__std__delete;
static void type__std__delete(void);
static NODE *get__std__delete(void) {
  return var.std__delete;
}
static int poly_idx__std__update;
static void type__std__update(void);
static NODE *get__std__update(void) {
  return var.std__update;
}
static int poly_idx__std__call_command;
static void type__std__call_command(void);
static NODE *get__std__call_command(void) {
  return var.std__call_command;
}
void run__basic__polymorphic_functions(void);

static CONTINUATION_INFO continuation_info[] = {
  {type__std__plus, NULL, 23, 23, 2, 10},
  {type__std__minus, NULL, 24, 24, 2, 11},
  {type__std__times, NULL, 25, 25, 2, 11},
  {type__std__over, NULL, 26, 26, 2, 10},
  {type__std__div, NULL, 27, 27, 2, 9},
  {type__std__mod, NULL, 28, 28, 2, 9},
  {type__std__negate, NULL, 29, 29, 2, 12},
  {type__std__equal, NULL, 30, 30, 2, 11},
  {type__std__equal_type_and_value, NULL, 31, 31, 2, 26},
  {type__std__less, NULL, 32, 32, 2, 10},
  {type__std__numerically_less, NULL, 34, 34, 2, 22},
  {type__std__not, NULL, 36, 36, 2, 9},
  {type__std__and, NULL, 37, 37, 2, 9},
  {type__std__or, NULL, 38, 38, 2, 8},
  {type__std__if, NULL, 39, 39, 2, 8},
  {type__std__unless, NULL, 40, 40, 2, 12},
  {type__std__shift_left, NULL, 41, 41, 2, 16},
  {type__std__shift_right, NULL, 42, 42, 2, 17},
  {type__std__bit_and, NULL, 43, 43, 2, 13},
  {type__std__bit_or, NULL, 44, 44, 2, 12},
  {type__std__bit_xor, NULL, 45, 45, 2, 13},
  {type__std__parameter_count_of, NULL, 46, 46, 2, 24},
  {type__std__is_defined, NULL, 47, 47, 2, 16},
  {type__std__is_undefined, NULL, 48, 48, 2, 18},
  {type__std__default_value, NULL, 49, 49, 2, 19},
  {type__std__is_valid, NULL, 50, 50, 2, 14},
  {type__std__to_string, NULL, 51, 51, 2, 15},
  {type__std__to_list, NULL, 52, 52, 2, 13},
  {type__std__serialize, NULL, 53, 53, 2, 15},
  {type__std__serialization_tag_of, NULL, 54, 54, 2, 26},
  {type__std__to_number, NULL, 55, 55, 2, 15},
  {type__std__parse_number, NULL, 56, 56, 2, 18},
  {type__std__to_integer, NULL, 57, 57, 2, 16},
  {type__std__parse_integer, NULL, 58, 58, 2, 19},
  {type__std__to_real, NULL, 59, 59, 2, 13},
  {type__std__parse_real, NULL, 60, 60, 2, 16},
  {type__std__to_lower_case, NULL, 61, 61, 2, 19},
  {type__std__to_upper_case, NULL, 62, 62, 2, 19},
  {type__std__to_title_case, NULL, 63, 63, 2, 19},
  {type__std__is_empty, NULL, 64, 64, 2, 14},
  {type__std__length_of, NULL, 65, 65, 2, 15},
  {type__std__type_of, NULL, 66, 66, 2, 13},
  {type__std__hash, NULL, 67, 67, 2, 10},
  {type__std__push, NULL, 68, 68, 2, 10},
  {type__std__pop, NULL, 69, 69, 2, 9},
  {type__std__peek, NULL, 70, 70, 2, 10},
  {type__std__drop, NULL, 71, 71, 2, 10},
  {type__std__put, NULL, 72, 72, 2, 9},
  {type__std__get, NULL, 73, 73, 2, 9},
  {type__std__next, NULL, 74, 74, 2, 10},
  {type__std__append, NULL, 75, 75, 2, 12},
  {type__std__insert_before, NULL, 76, 76, 2, 19},
  {type__std__insert_behind, NULL, 77, 77, 2, 19},
  {type__std__first_index_of, NULL, 78, 78, 2, 20},
  {type__std__last_index_of, NULL, 79, 79, 2, 19},
  {type__std__delete_at, NULL, 80, 80, 2, 15},
  {type__std__union, NULL, 81, 81, 2, 11},
  {type__std__intersection, NULL, 82, 82, 2, 18},
  {type__std__match_character, NULL, 83, 83, 2, 21},
  {type__std__match_string, NULL, 84, 84, 2, 18},
  {type__std__search_character, NULL, 85, 85, 2, 22},
  {type__std__search_string, NULL, 86, 86, 2, 19},
  {type__std__match, NULL, 87, 87, 2, 11},
  {type__std__search, NULL, 88, 88, 2, 12},
  {type__std__matches, NULL, 89, 89, 2, 13},
  {type__std__contains, NULL, 90, 90, 2, 14},
  {type__std__has_prefix, NULL, 91, 91, 2, 16},
  {type__std__has_suffix, NULL, 92, 92, 2, 16},
  {type__std__without_prefix, NULL, 93, 93, 2, 20},
  {type__std__without_suffix, NULL, 94, 94, 2, 20},
  {type__std__before, NULL, 95, 95, 2, 12},
  {type__std__truncate_from, NULL, 96, 96, 2, 19},
  {type__std__behind, NULL, 97, 97, 2, 12},
  {type__std__truncate_until, NULL, 98, 98, 2, 20},
  {type__std__from, NULL, 99, 99, 2, 10},
  {type__std__truncate_before, NULL, 100, 100, 2, 21},
  {type__std__until, NULL, 101, 101, 2, 11},
  {type__std__truncate_behind, NULL, 102, 102, 2, 21},
  {type__std__between, NULL, 103, 103, 2, 13},
  {type__std__range, NULL, 104, 104, 2, 11},
  {type__std__merge, NULL, 105, 105, 2, 11},
  {type__std__sort, NULL, 106, 106, 2, 10},
  {type__std__close, NULL, 107, 107, 2, 11},
  {type__std__write_some_bytes_to, NULL, 108, 108, 2, 25},
  {type__std__write_to, NULL, 109, 109, 2, 14},
  {type__std__flush, NULL, 110, 110, 2, 11},
  {type__std__read_some_bytes_from, NULL, 111, 111, 2, 26},
  {type__std__read_from, NULL, 112, 112, 2, 15},
  {type__std__key_of, NULL, 113, 113, 2, 12},
  {type__std__value_of, NULL, 114, 114, 2, 14},
  {type__std__keys_of, NULL, 115, 115, 2, 13},
  {type__std__values_of, NULL, 116, 116, 2, 15},
  {type__std__lower_bound_of, NULL, 117, 117, 2, 20},
  {type__std__upper_bound_of, NULL, 118, 118, 2, 20},
  {type__std__for_each_from_to, NULL, 119, 119, 2, 22},
  {type__std__for_each_from_down_to, NULL, 120, 120, 2, 27},
  {type__std__for_each, NULL, 121, 121, 2, 14},
  {type__std__for_each_downwards, NULL, 122, 122, 2, 24},
  {type__std__update_each_from_to, NULL, 123, 123, 2, 25},
  {type__std__update_each_from_down_to, NULL, 124, 124, 2, 30},
  {type__std__update_each, NULL, 125, 125, 2, 17},
  {type__std__update_each_downwards, NULL, 126, 126, 2, 27},
  {type__std__for_each_pair, NULL, 127, 127, 2, 19},
  {type__std__new_empty_collection, NULL, 128, 128, 2, 26},
  {type__std__filter, NULL, 129, 129, 2, 12},
  {type__std__map, NULL, 130, 130, 2, 9},
  {type__std__dup, NULL, 131, 131, 2, 9},
  {type__std__interleave, NULL, 132, 132, 2, 16},
  {type__std__stop, NULL, 133, 133, 2, 10},
  {type__std__get_file_descriptors, NULL, 134, 134, 2, 26},
  {type__std__handle_requests, NULL, 135, 135, 2, 21},
  {type__std__select, NULL, 136, 136, 2, 12},
  {type__std__delete, NULL, 137, 137, 2, 12},
  {type__std__update, NULL, 138, 138, 2, 12},
  {type__std__call_command, NULL, 139, 139, 2, 18},
  {run__basic__polymorphic_functions, NULL, }
};

union NODE {
  struct {
    FUNC type;
    ATTRIBUTES *attributes;
  };
  CONTINUATION continuation;
  CLOSURE closure;
};
static void type__std__plus(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__plus);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__plus, attr);
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
static void type__std__minus(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__minus);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__minus, attr);
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
static void type__std__times(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__times);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__times, attr);
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
static void type__std__over(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__over);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__over, attr);
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
static void type__std__div(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__div);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__div, attr);
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
static void type__std__mod(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__mod);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__mod, attr);
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
static void type__std__negate(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__negate);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__negate, attr);
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
static void type__std__equal(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__equal); // 2
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__equal, attr);
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
static void type__std__equal_type_and_value(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__equal_type_and_value);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__equal_type_and_value, attr);
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
static void type__std__less(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__less); // 3
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__less, attr);
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
static void type__std__numerically_less(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__numerically_less);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__numerically_less, attr);
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
static void type__std__not(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__not);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__not, attr);
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
static void type__std__and(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__and);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__and, attr);
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
static void type__std__or(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__or);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__or, attr);
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
static void type__std__if(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__if); // 0
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__if, attr);
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
static void type__std__unless(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__unless); // 6
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__unless, attr);
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
static void type__std__shift_left(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__shift_left);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__shift_left, attr);
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
static void type__std__shift_right(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__shift_right);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__shift_right, attr);
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
static void type__std__bit_and(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__bit_and);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__bit_and, attr);
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
static void type__std__bit_or(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__bit_or);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__bit_or, attr);
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
static void type__std__bit_xor(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__bit_xor);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__bit_xor, attr);
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
static void type__std__parameter_count_of(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__parameter_count_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__parameter_count_of, attr);
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
static void type__std__is_defined(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__is_defined); // 1
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__is_defined, attr);
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
static void type__std__is_undefined(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__is_undefined);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__is_undefined, attr);
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
static void type__std__default_value(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__default_value);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__default_value, attr);
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
static void type__std__is_valid(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__is_valid);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__is_valid, attr);
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
static void type__std__to_string(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__to_string);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__to_string, attr);
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
static void type__std__to_list(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__to_list);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__to_list, attr);
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
static void type__std__serialize(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__serialize);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__serialize, attr);
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
static void type__std__serialization_tag_of(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__serialization_tag_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__serialization_tag_of, attr);
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
static void type__std__to_number(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__to_number);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__to_number, attr);
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
static void type__std__parse_number(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__parse_number);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__parse_number, attr);
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
static void type__std__to_integer(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__to_integer);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__to_integer, attr);
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
static void type__std__parse_integer(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__parse_integer);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__parse_integer, attr);
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
static void type__std__to_real(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__to_real);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__to_real, attr);
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
static void type__std__parse_real(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__parse_real);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__parse_real, attr);
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
static void type__std__to_lower_case(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__to_lower_case);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__to_lower_case, attr);
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
static void type__std__to_upper_case(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__to_upper_case);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__to_upper_case, attr);
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
static void type__std__to_title_case(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__to_title_case);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__to_title_case, attr);
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
static void type__std__is_empty(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__is_empty); // 5
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__is_empty, attr);
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
static void type__std__length_of(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__length_of); // 4
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__length_of, attr);
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
static void type__std__type_of(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__type_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__type_of, attr);
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
static void type__std__hash(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__hash);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__hash, attr);
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
static void type__std__push(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__push);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__push, attr);
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
static void type__std__pop(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__pop);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__pop, attr);
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
static void type__std__peek(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__peek);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__peek, attr);
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
static void type__std__drop(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__drop);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__drop, attr);
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
static void type__std__put(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__put);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__put, attr);
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
static void type__std__get(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__get);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__get, attr);
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
static void type__std__next(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__next);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__next, attr);
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
static void type__std__append(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__append);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__append, attr);
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
static void type__std__insert_before(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__insert_before);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__insert_before, attr);
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
static void type__std__insert_behind(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__insert_behind);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__insert_behind, attr);
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
static void type__std__first_index_of(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__first_index_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__first_index_of, attr);
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
static void type__std__last_index_of(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__last_index_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__last_index_of, attr);
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
static void type__std__delete_at(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__delete_at);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__delete_at, attr);
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
static void type__std__union(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__union);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__union, attr);
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
static void type__std__intersection(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__intersection);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__intersection, attr);
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
static void type__std__match_character(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__match_character);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__match_character, attr);
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
static void type__std__match_string(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__match_string);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__match_string, attr);
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
static void type__std__search_character(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__search_character);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__search_character, attr);
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
static void type__std__search_string(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__search_string);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__search_string, attr);
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
static void type__std__match(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__match);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__match, attr);
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
static void type__std__search(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__search);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__search, attr);
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
static void type__std__matches(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__matches);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__matches, attr);
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
static void type__std__contains(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__contains);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__contains, attr);
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
static void type__std__has_prefix(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__has_prefix);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__has_prefix, attr);
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
static void type__std__has_suffix(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__has_suffix);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__has_suffix, attr);
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
static void type__std__without_prefix(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__without_prefix);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__without_prefix, attr);
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
static void type__std__without_suffix(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__without_suffix);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__without_suffix, attr);
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
static void type__std__before(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__before);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__before, attr);
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
static void type__std__truncate_from(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__truncate_from);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__truncate_from, attr);
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
static void type__std__behind(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__behind);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__behind, attr);
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
static void type__std__truncate_until(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__truncate_until);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__truncate_until, attr);
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
static void type__std__from(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__from);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__from, attr);
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
static void type__std__truncate_before(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__truncate_before);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__truncate_before, attr);
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
static void type__std__until(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__until);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__until, attr);
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
static void type__std__truncate_behind(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__truncate_behind);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__truncate_behind, attr);
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
static void type__std__between(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__between);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__between, attr);
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
static void type__std__range(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__range);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__range, attr);
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
static void type__std__merge(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__merge);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__merge, attr);
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
static void type__std__sort(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__sort);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__sort, attr);
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
static void type__std__close(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__close);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__close, attr);
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
static void type__std__write_some_bytes_to(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__write_some_bytes_to);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__write_some_bytes_to, attr);
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
static void type__std__write_to(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__write_to);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__write_to, attr);
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
static void type__std__flush(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__flush);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__flush, attr);
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
static void type__std__read_some_bytes_from(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__read_some_bytes_from);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__read_some_bytes_from, attr);
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
static void type__std__read_from(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__read_from);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__read_from, attr);
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
static void type__std__key_of(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__key_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__key_of, attr);
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
static void type__std__value_of(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__value_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__value_of, attr);
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
static void type__std__keys_of(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__keys_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__keys_of, attr);
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
static void type__std__values_of(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__values_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__values_of, attr);
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
static void type__std__lower_bound_of(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__lower_bound_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__lower_bound_of, attr);
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
static void type__std__upper_bound_of(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__upper_bound_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__upper_bound_of, attr);
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
static void type__std__for_each_from_to(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__for_each_from_to);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__for_each_from_to, attr);
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
static void type__std__for_each_from_down_to(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__for_each_from_down_to);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__for_each_from_down_to, attr);
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
static void type__std__for_each(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__for_each);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__for_each, attr);
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
static void type__std__for_each_downwards(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__for_each_downwards);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__for_each_downwards, attr);
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
static void type__std__update_each_from_to(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__update_each_from_to);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__update_each_from_to, attr);
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
static void type__std__update_each_from_down_to(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__update_each_from_down_to);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__update_each_from_down_to, attr);
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
static void type__std__update_each(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__update_each);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__update_each, attr);
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
static void type__std__update_each_downwards(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__update_each_downwards);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__update_each_downwards, attr);
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
static void type__std__for_each_pair(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__for_each_pair);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__for_each_pair, attr);
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
static void type__std__new_empty_collection(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__new_empty_collection);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__new_empty_collection, attr);
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
static void type__std__filter(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__filter);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__filter, attr);
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
static void type__std__map(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__map);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__map, attr);
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
static void type__std__dup(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__dup);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__dup, attr);
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
static void type__std__interleave(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__interleave);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__interleave, attr);
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
static void type__std__stop(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__stop);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__stop, attr);
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
static void type__std__get_file_descriptors(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__get_file_descriptors);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__get_file_descriptors, attr);
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
static void type__std__handle_requests(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__handle_requests);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__handle_requests, attr);
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
static void type__std__select(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__select);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__select, attr);
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
static void type__std__delete(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__delete);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__delete, attr);
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
static void type__std__update(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__update);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__update, attr);
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
static void type__std__call_command(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__call_command);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__call_command, attr);
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

static const char *used_namespaces[] = {
  "std",
  NULL
};

static MODULE_INFO module_info = {
  NULL,
  "basic__polymorphic_functions",
  continuation_info,
  sizeof(continuation_info)/sizeof(CONTINUATION_INFO),
  (NODE **)&var,
  var_names,
  sizeof(var_names)/sizeof(const char *),
  used_namespaces,
  {DEBUG_FILENAME("basic/polymorphic_functions.sim")}
};

/******
C O D E
******/

static int already_run = false;

EXPORT void run__basic__polymorphic_functions(void) {
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
EXPORT void collect__basic__polymorphic_functions(void) {
  var.std__plus = collect_node(var.std__plus);
  var.std__minus = collect_node(var.std__minus);
  var.std__times = collect_node(var.std__times);
  var.std__over = collect_node(var.std__over);
  var.std__div = collect_node(var.std__div);
  var.std__mod = collect_node(var.std__mod);
  var.std__negate = collect_node(var.std__negate);
  var.std__equal = collect_node(var.std__equal);
  var.std__equal_type_and_value = collect_node(var.std__equal_type_and_value);
  var.std__less = collect_node(var.std__less);
  var.std__numerically_less = collect_node(var.std__numerically_less);
  var.std__not = collect_node(var.std__not);
  var.std__and = collect_node(var.std__and);
  var.std__or = collect_node(var.std__or);
  var.std__if = collect_node(var.std__if);
  var.std__unless = collect_node(var.std__unless);
  var.std__shift_left = collect_node(var.std__shift_left);
  var.std__shift_right = collect_node(var.std__shift_right);
  var.std__bit_and = collect_node(var.std__bit_and);
  var.std__bit_or = collect_node(var.std__bit_or);
  var.std__bit_xor = collect_node(var.std__bit_xor);
  var.std__parameter_count_of = collect_node(var.std__parameter_count_of);
  var.std__is_defined = collect_node(var.std__is_defined);
  var.std__is_undefined = collect_node(var.std__is_undefined);
  var.std__default_value = collect_node(var.std__default_value);
  var.std__is_valid = collect_node(var.std__is_valid);
  var.std__to_string = collect_node(var.std__to_string);
  var.std__to_list = collect_node(var.std__to_list);
  var.std__serialize = collect_node(var.std__serialize);
  var.std__serialization_tag_of = collect_node(var.std__serialization_tag_of);
  var.std__to_number = collect_node(var.std__to_number);
  var.std__parse_number = collect_node(var.std__parse_number);
  var.std__to_integer = collect_node(var.std__to_integer);
  var.std__parse_integer = collect_node(var.std__parse_integer);
  var.std__to_real = collect_node(var.std__to_real);
  var.std__parse_real = collect_node(var.std__parse_real);
  var.std__to_lower_case = collect_node(var.std__to_lower_case);
  var.std__to_upper_case = collect_node(var.std__to_upper_case);
  var.std__to_title_case = collect_node(var.std__to_title_case);
  var.std__is_empty = collect_node(var.std__is_empty);
  var.std__length_of = collect_node(var.std__length_of);
  var.std__type_of = collect_node(var.std__type_of);
  var.std__hash = collect_node(var.std__hash);
  var.std__push = collect_node(var.std__push);
  var.std__pop = collect_node(var.std__pop);
  var.std__peek = collect_node(var.std__peek);
  var.std__drop = collect_node(var.std__drop);
  var.std__put = collect_node(var.std__put);
  var.std__get = collect_node(var.std__get);
  var.std__next = collect_node(var.std__next);
  var.std__append = collect_node(var.std__append);
  var.std__insert_before = collect_node(var.std__insert_before);
  var.std__insert_behind = collect_node(var.std__insert_behind);
  var.std__first_index_of = collect_node(var.std__first_index_of);
  var.std__last_index_of = collect_node(var.std__last_index_of);
  var.std__delete_at = collect_node(var.std__delete_at);
  var.std__union = collect_node(var.std__union);
  var.std__intersection = collect_node(var.std__intersection);
  var.std__match_character = collect_node(var.std__match_character);
  var.std__match_string = collect_node(var.std__match_string);
  var.std__search_character = collect_node(var.std__search_character);
  var.std__search_string = collect_node(var.std__search_string);
  var.std__match = collect_node(var.std__match);
  var.std__search = collect_node(var.std__search);
  var.std__matches = collect_node(var.std__matches);
  var.std__contains = collect_node(var.std__contains);
  var.std__has_prefix = collect_node(var.std__has_prefix);
  var.std__has_suffix = collect_node(var.std__has_suffix);
  var.std__without_prefix = collect_node(var.std__without_prefix);
  var.std__without_suffix = collect_node(var.std__without_suffix);
  var.std__before = collect_node(var.std__before);
  var.std__truncate_from = collect_node(var.std__truncate_from);
  var.std__behind = collect_node(var.std__behind);
  var.std__truncate_until = collect_node(var.std__truncate_until);
  var.std__from = collect_node(var.std__from);
  var.std__truncate_before = collect_node(var.std__truncate_before);
  var.std__until = collect_node(var.std__until);
  var.std__truncate_behind = collect_node(var.std__truncate_behind);
  var.std__between = collect_node(var.std__between);
  var.std__range = collect_node(var.std__range);
  var.std__merge = collect_node(var.std__merge);
  var.std__sort = collect_node(var.std__sort);
  var.std__close = collect_node(var.std__close);
  var.std__write_some_bytes_to = collect_node(var.std__write_some_bytes_to);
  var.std__write_to = collect_node(var.std__write_to);
  var.std__flush = collect_node(var.std__flush);
  var.std__read_some_bytes_from = collect_node(var.std__read_some_bytes_from);
  var.std__read_from = collect_node(var.std__read_from);
  var.std__key_of = collect_node(var.std__key_of);
  var.std__value_of = collect_node(var.std__value_of);
  var.std__keys_of = collect_node(var.std__keys_of);
  var.std__values_of = collect_node(var.std__values_of);
  var.std__lower_bound_of = collect_node(var.std__lower_bound_of);
  var.std__upper_bound_of = collect_node(var.std__upper_bound_of);
  var.std__for_each_from_to = collect_node(var.std__for_each_from_to);
  var.std__for_each_from_down_to = collect_node(var.std__for_each_from_down_to);
  var.std__for_each = collect_node(var.std__for_each);
  var.std__for_each_downwards = collect_node(var.std__for_each_downwards);
  var.std__update_each_from_to = collect_node(var.std__update_each_from_to);
  var.std__update_each_from_down_to = collect_node(var.std__update_each_from_down_to);
  var.std__update_each = collect_node(var.std__update_each);
  var.std__update_each_downwards = collect_node(var.std__update_each_downwards);
  var.std__for_each_pair = collect_node(var.std__for_each_pair);
  var.std__new_empty_collection = collect_node(var.std__new_empty_collection);
  var.std__filter = collect_node(var.std__filter);
  var.std__map = collect_node(var.std__map);
  var.std__dup = collect_node(var.std__dup);
  var.std__interleave = collect_node(var.std__interleave);
  var.std__stop = collect_node(var.std__stop);
  var.std__get_file_descriptors = collect_node(var.std__get_file_descriptors);
  var.std__handle_requests = collect_node(var.std__handle_requests);
  var.std__select = collect_node(var.std__select);
  var.std__delete = collect_node(var.std__delete);
  var.std__update = collect_node(var.std__update);
  var.std__call_command = collect_node(var.std__call_command);
}

static int already_run_phase_1 = false;

EXPORT void phase_1__basic__polymorphic_functions(void) {
  if (already_run_phase_1) return;
  already_run_phase_1 = true;
  register_module_info(&module_info);
  define_polymorphic_function("std", "plus", get__std__plus, &poly_idx__std__plus, &var.std__plus);
  define_polymorphic_function("std", "minus", get__std__minus, &poly_idx__std__minus, &var.std__minus);
  define_polymorphic_function("std", "times", get__std__times, &poly_idx__std__times, &var.std__times);
  define_polymorphic_function("std", "over", get__std__over, &poly_idx__std__over, &var.std__over);
  define_polymorphic_function("std", "div", get__std__div, &poly_idx__std__div, &var.std__div);
  define_polymorphic_function("std", "mod", get__std__mod, &poly_idx__std__mod, &var.std__mod);
  define_polymorphic_function("std", "negate", get__std__negate, &poly_idx__std__negate, &var.std__negate);
  define_privileged_polymorphic_function("std", "equal", get__std__equal, 2, &var.std__equal);
  define_polymorphic_function("std", "equal_type_and_value", get__std__equal_type_and_value, &poly_idx__std__equal_type_and_value, &var.std__equal_type_and_value);
  define_privileged_polymorphic_function("std", "less", get__std__less, 3, &var.std__less);
  define_polymorphic_function("std", "numerically_less", get__std__numerically_less, &poly_idx__std__numerically_less, &var.std__numerically_less);
  define_polymorphic_function("std", "not", get__std__not, &poly_idx__std__not, &var.std__not);
  define_polymorphic_function("std", "and", get__std__and, &poly_idx__std__and, &var.std__and);
  define_polymorphic_function("std", "or", get__std__or, &poly_idx__std__or, &var.std__or);
  define_privileged_polymorphic_function("std", "if", get__std__if, 0, &var.std__if);
  define_privileged_polymorphic_function("std", "unless", get__std__unless, 6, &var.std__unless);
  define_polymorphic_function("std", "shift_left", get__std__shift_left, &poly_idx__std__shift_left, &var.std__shift_left);
  define_polymorphic_function("std", "shift_right", get__std__shift_right, &poly_idx__std__shift_right, &var.std__shift_right);
  define_polymorphic_function("std", "bit_and", get__std__bit_and, &poly_idx__std__bit_and, &var.std__bit_and);
  define_polymorphic_function("std", "bit_or", get__std__bit_or, &poly_idx__std__bit_or, &var.std__bit_or);
  define_polymorphic_function("std", "bit_xor", get__std__bit_xor, &poly_idx__std__bit_xor, &var.std__bit_xor);
  define_polymorphic_function_with_setter("std", "parameter_count_of", get__std__parameter_count_of, &poly_idx__std__parameter_count_of, &var.std__parameter_count_of);
  define_privileged_polymorphic_function("std", "is_defined", get__std__is_defined, 1, &var.std__is_defined);
  define_polymorphic_function("std", "is_undefined", get__std__is_undefined, &poly_idx__std__is_undefined, &var.std__is_undefined);
  define_polymorphic_function("std", "default_value", get__std__default_value, &poly_idx__std__default_value, &var.std__default_value);
  define_polymorphic_function("std", "is_valid", get__std__is_valid, &poly_idx__std__is_valid, &var.std__is_valid);
  define_polymorphic_function("std", "to_string", get__std__to_string, &poly_idx__std__to_string, &var.std__to_string);
  define_polymorphic_function("std", "to_list", get__std__to_list, &poly_idx__std__to_list, &var.std__to_list);
  define_polymorphic_function("std", "serialize", get__std__serialize, &poly_idx__std__serialize, &var.std__serialize);
  define_polymorphic_function_with_setter("std", "serialization_tag_of", get__std__serialization_tag_of, &poly_idx__std__serialization_tag_of, &var.std__serialization_tag_of);
  define_polymorphic_function("std", "to_number", get__std__to_number, &poly_idx__std__to_number, &var.std__to_number);
  define_polymorphic_function("std", "parse_number", get__std__parse_number, &poly_idx__std__parse_number, &var.std__parse_number);
  define_polymorphic_function("std", "to_integer", get__std__to_integer, &poly_idx__std__to_integer, &var.std__to_integer);
  define_polymorphic_function("std", "parse_integer", get__std__parse_integer, &poly_idx__std__parse_integer, &var.std__parse_integer);
  define_polymorphic_function("std", "to_real", get__std__to_real, &poly_idx__std__to_real, &var.std__to_real);
  define_polymorphic_function("std", "parse_real", get__std__parse_real, &poly_idx__std__parse_real, &var.std__parse_real);
  define_polymorphic_function("std", "to_lower_case", get__std__to_lower_case, &poly_idx__std__to_lower_case, &var.std__to_lower_case);
  define_polymorphic_function("std", "to_upper_case", get__std__to_upper_case, &poly_idx__std__to_upper_case, &var.std__to_upper_case);
  define_polymorphic_function("std", "to_title_case", get__std__to_title_case, &poly_idx__std__to_title_case, &var.std__to_title_case);
  define_privileged_polymorphic_function("std", "is_empty", get__std__is_empty, 5, &var.std__is_empty);
  define_privileged_polymorphic_function("std", "length_of", get__std__length_of, 4, &var.std__length_of);
  define_polymorphic_function_with_setter("std", "type_of", get__std__type_of, &poly_idx__std__type_of, &var.std__type_of);
  define_polymorphic_function("std", "hash", get__std__hash, &poly_idx__std__hash, &var.std__hash);
  define_polymorphic_function("std", "push", get__std__push, &poly_idx__std__push, &var.std__push);
  define_polymorphic_function("std", "pop", get__std__pop, &poly_idx__std__pop, &var.std__pop);
  define_polymorphic_function("std", "peek", get__std__peek, &poly_idx__std__peek, &var.std__peek);
  define_polymorphic_function("std", "drop", get__std__drop, &poly_idx__std__drop, &var.std__drop);
  define_polymorphic_function("std", "put", get__std__put, &poly_idx__std__put, &var.std__put);
  define_polymorphic_function("std", "get", get__std__get, &poly_idx__std__get, &var.std__get);
  define_polymorphic_function("std", "next", get__std__next, &poly_idx__std__next, &var.std__next);
  define_polymorphic_function("std", "append", get__std__append, &poly_idx__std__append, &var.std__append);
  define_polymorphic_function("std", "insert_before", get__std__insert_before, &poly_idx__std__insert_before, &var.std__insert_before);
  define_polymorphic_function("std", "insert_behind", get__std__insert_behind, &poly_idx__std__insert_behind, &var.std__insert_behind);
  define_polymorphic_function_with_setter("std", "first_index_of", get__std__first_index_of, &poly_idx__std__first_index_of, &var.std__first_index_of);
  define_polymorphic_function_with_setter("std", "last_index_of", get__std__last_index_of, &poly_idx__std__last_index_of, &var.std__last_index_of);
  define_polymorphic_function("std", "delete_at", get__std__delete_at, &poly_idx__std__delete_at, &var.std__delete_at);
  define_polymorphic_function("std", "union", get__std__union, &poly_idx__std__union, &var.std__union);
  define_polymorphic_function("std", "intersection", get__std__intersection, &poly_idx__std__intersection, &var.std__intersection);
  define_polymorphic_function("std", "match_character", get__std__match_character, &poly_idx__std__match_character, &var.std__match_character);
  define_polymorphic_function("std", "match_string", get__std__match_string, &poly_idx__std__match_string, &var.std__match_string);
  define_polymorphic_function("std", "search_character", get__std__search_character, &poly_idx__std__search_character, &var.std__search_character);
  define_polymorphic_function("std", "search_string", get__std__search_string, &poly_idx__std__search_string, &var.std__search_string);
  define_polymorphic_function("std", "match", get__std__match, &poly_idx__std__match, &var.std__match);
  define_polymorphic_function("std", "search", get__std__search, &poly_idx__std__search, &var.std__search);
  define_polymorphic_function("std", "matches", get__std__matches, &poly_idx__std__matches, &var.std__matches);
  define_polymorphic_function("std", "contains", get__std__contains, &poly_idx__std__contains, &var.std__contains);
  define_polymorphic_function("std", "has_prefix", get__std__has_prefix, &poly_idx__std__has_prefix, &var.std__has_prefix);
  define_polymorphic_function("std", "has_suffix", get__std__has_suffix, &poly_idx__std__has_suffix, &var.std__has_suffix);
  define_polymorphic_function("std", "without_prefix", get__std__without_prefix, &poly_idx__std__without_prefix, &var.std__without_prefix);
  define_polymorphic_function("std", "without_suffix", get__std__without_suffix, &poly_idx__std__without_suffix, &var.std__without_suffix);
  define_polymorphic_function("std", "before", get__std__before, &poly_idx__std__before, &var.std__before);
  define_polymorphic_function("std", "truncate_from", get__std__truncate_from, &poly_idx__std__truncate_from, &var.std__truncate_from);
  define_polymorphic_function("std", "behind", get__std__behind, &poly_idx__std__behind, &var.std__behind);
  define_polymorphic_function("std", "truncate_until", get__std__truncate_until, &poly_idx__std__truncate_until, &var.std__truncate_until);
  define_polymorphic_function("std", "from", get__std__from, &poly_idx__std__from, &var.std__from);
  define_polymorphic_function("std", "truncate_before", get__std__truncate_before, &poly_idx__std__truncate_before, &var.std__truncate_before);
  define_polymorphic_function("std", "until", get__std__until, &poly_idx__std__until, &var.std__until);
  define_polymorphic_function("std", "truncate_behind", get__std__truncate_behind, &poly_idx__std__truncate_behind, &var.std__truncate_behind);
  define_polymorphic_function("std", "between", get__std__between, &poly_idx__std__between, &var.std__between);
  define_polymorphic_function("std", "range", get__std__range, &poly_idx__std__range, &var.std__range);
  define_polymorphic_function("std", "merge", get__std__merge, &poly_idx__std__merge, &var.std__merge);
  define_polymorphic_function("std", "sort", get__std__sort, &poly_idx__std__sort, &var.std__sort);
  define_polymorphic_function("std", "close", get__std__close, &poly_idx__std__close, &var.std__close);
  define_polymorphic_function("std", "write_some_bytes_to", get__std__write_some_bytes_to, &poly_idx__std__write_some_bytes_to, &var.std__write_some_bytes_to);
  define_polymorphic_function("std", "write_to", get__std__write_to, &poly_idx__std__write_to, &var.std__write_to);
  define_polymorphic_function("std", "flush", get__std__flush, &poly_idx__std__flush, &var.std__flush);
  define_polymorphic_function("std", "read_some_bytes_from", get__std__read_some_bytes_from, &poly_idx__std__read_some_bytes_from, &var.std__read_some_bytes_from);
  define_polymorphic_function("std", "read_from", get__std__read_from, &poly_idx__std__read_from, &var.std__read_from);
  define_polymorphic_function_with_setter("std", "key_of", get__std__key_of, &poly_idx__std__key_of, &var.std__key_of);
  define_polymorphic_function_with_setter("std", "value_of", get__std__value_of, &poly_idx__std__value_of, &var.std__value_of);
  define_polymorphic_function_with_setter("std", "keys_of", get__std__keys_of, &poly_idx__std__keys_of, &var.std__keys_of);
  define_polymorphic_function_with_setter("std", "values_of", get__std__values_of, &poly_idx__std__values_of, &var.std__values_of);
  define_polymorphic_function_with_setter("std", "lower_bound_of", get__std__lower_bound_of, &poly_idx__std__lower_bound_of, &var.std__lower_bound_of);
  define_polymorphic_function_with_setter("std", "upper_bound_of", get__std__upper_bound_of, &poly_idx__std__upper_bound_of, &var.std__upper_bound_of);
  define_polymorphic_function("std", "for_each_from_to", get__std__for_each_from_to, &poly_idx__std__for_each_from_to, &var.std__for_each_from_to);
  define_polymorphic_function("std", "for_each_from_down_to", get__std__for_each_from_down_to, &poly_idx__std__for_each_from_down_to, &var.std__for_each_from_down_to);
  define_polymorphic_function("std", "for_each", get__std__for_each, &poly_idx__std__for_each, &var.std__for_each);
  define_polymorphic_function("std", "for_each_downwards", get__std__for_each_downwards, &poly_idx__std__for_each_downwards, &var.std__for_each_downwards);
  define_polymorphic_function("std", "update_each_from_to", get__std__update_each_from_to, &poly_idx__std__update_each_from_to, &var.std__update_each_from_to);
  define_polymorphic_function("std", "update_each_from_down_to", get__std__update_each_from_down_to, &poly_idx__std__update_each_from_down_to, &var.std__update_each_from_down_to);
  define_polymorphic_function("std", "update_each", get__std__update_each, &poly_idx__std__update_each, &var.std__update_each);
  define_polymorphic_function("std", "update_each_downwards", get__std__update_each_downwards, &poly_idx__std__update_each_downwards, &var.std__update_each_downwards);
  define_polymorphic_function("std", "for_each_pair", get__std__for_each_pair, &poly_idx__std__for_each_pair, &var.std__for_each_pair);
  define_polymorphic_function("std", "new_empty_collection", get__std__new_empty_collection, &poly_idx__std__new_empty_collection, &var.std__new_empty_collection);
  define_polymorphic_function("std", "filter", get__std__filter, &poly_idx__std__filter, &var.std__filter);
  define_polymorphic_function("std", "map", get__std__map, &poly_idx__std__map, &var.std__map);
  define_polymorphic_function("std", "dup", get__std__dup, &poly_idx__std__dup, &var.std__dup);
  define_polymorphic_function("std", "interleave", get__std__interleave, &poly_idx__std__interleave, &var.std__interleave);
  define_polymorphic_function("std", "stop", get__std__stop, &poly_idx__std__stop, &var.std__stop);
  define_polymorphic_function("std", "get_file_descriptors", get__std__get_file_descriptors, &poly_idx__std__get_file_descriptors, &var.std__get_file_descriptors);
  define_polymorphic_function("std", "handle_requests", get__std__handle_requests, &poly_idx__std__handle_requests, &var.std__handle_requests);
  define_polymorphic_function("std", "select", get__std__select, &poly_idx__std__select, &var.std__select);
  define_polymorphic_function("std", "delete", get__std__delete, &poly_idx__std__delete, &var.std__delete);
  define_polymorphic_function("std", "update", get__std__update, &poly_idx__std__update, &var.std__update);
  define_polymorphic_function("std", "call_command", get__std__call_command, &poly_idx__std__call_command, &var.std__call_command);
}

static int already_run_phase_2 = false;

EXPORT void phase_2__basic__polymorphic_functions(void) {
  if (already_run_phase_2) return;
  already_run_phase_2 = true;
  set_module("basic__polymorphic_functions");
  set_used_namespaces(used_namespaces);
}

static int already_run_phase_3 = false;

EXPORT void phase_3__basic__polymorphic_functions(void) {
  if (already_run_phase_3) return;
  already_run_phase_3 = true;
  set_module("basic__polymorphic_functions");
  set_used_namespaces(used_namespaces);
}

static int already_run_phase_4 = false;

EXPORT void phase_4__basic__polymorphic_functions(void) {
  if (already_run_phase_4) return;
  already_run_phase_4 = true;
  assign_value(&var.std__plus, create_function(type__std__plus, -1));
  assign_value(&var.std__minus, create_function(type__std__minus, -1));
  assign_value(&var.std__times, create_function(type__std__times, -1));
  assign_value(&var.std__over, create_function(type__std__over, -1));
  assign_value(&var.std__div, create_function(type__std__div, -1));
  assign_value(&var.std__mod, create_function(type__std__mod, -1));
  assign_value(&var.std__negate, create_function(type__std__negate, -1));
  assign_value(&var.std__equal, create_function(type__std__equal, -1));
  assign_value(&var.std__equal_type_and_value, create_function(type__std__equal_type_and_value, -1));
  assign_value(&var.std__less, create_function(type__std__less, -1));
  assign_value(&var.std__numerically_less, create_function(type__std__numerically_less, -1));
  assign_value(&var.std__not, create_function(type__std__not, -1));
  assign_value(&var.std__and, create_function(type__std__and, -1));
  assign_value(&var.std__or, create_function(type__std__or, -1));
  assign_value(&var.std__if, create_function(type__std__if, -1));
  assign_value(&var.std__unless, create_function(type__std__unless, -1));
  assign_value(&var.std__shift_left, create_function(type__std__shift_left, -1));
  assign_value(&var.std__shift_right, create_function(type__std__shift_right, -1));
  assign_value(&var.std__bit_and, create_function(type__std__bit_and, -1));
  assign_value(&var.std__bit_or, create_function(type__std__bit_or, -1));
  assign_value(&var.std__bit_xor, create_function(type__std__bit_xor, -1));
  assign_value(&var.std__parameter_count_of, create_function(type__std__parameter_count_of, -1));
  assign_value(&var.std__is_defined, create_function(type__std__is_defined, -1));
  assign_value(&var.std__is_undefined, create_function(type__std__is_undefined, -1));
  assign_value(&var.std__default_value, create_function(type__std__default_value, -1));
  assign_value(&var.std__is_valid, create_function(type__std__is_valid, -1));
  assign_value(&var.std__to_string, create_function(type__std__to_string, -1));
  assign_value(&var.std__to_list, create_function(type__std__to_list, -1));
  assign_value(&var.std__serialize, create_function(type__std__serialize, -1));
  assign_value(&var.std__serialization_tag_of, create_function(type__std__serialization_tag_of, -1));
  assign_value(&var.std__to_number, create_function(type__std__to_number, -1));
  assign_value(&var.std__parse_number, create_function(type__std__parse_number, -1));
  assign_value(&var.std__to_integer, create_function(type__std__to_integer, -1));
  assign_value(&var.std__parse_integer, create_function(type__std__parse_integer, -1));
  assign_value(&var.std__to_real, create_function(type__std__to_real, -1));
  assign_value(&var.std__parse_real, create_function(type__std__parse_real, -1));
  assign_value(&var.std__to_lower_case, create_function(type__std__to_lower_case, -1));
  assign_value(&var.std__to_upper_case, create_function(type__std__to_upper_case, -1));
  assign_value(&var.std__to_title_case, create_function(type__std__to_title_case, -1));
  assign_value(&var.std__is_empty, create_function(type__std__is_empty, -1));
  assign_value(&var.std__length_of, create_function(type__std__length_of, -1));
  assign_value(&var.std__type_of, create_function(type__std__type_of, -1));
  assign_value(&var.std__hash, create_function(type__std__hash, -1));
  assign_value(&var.std__push, create_function(type__std__push, -1));
  assign_value(&var.std__pop, create_function(type__std__pop, -1));
  assign_value(&var.std__peek, create_function(type__std__peek, -1));
  assign_value(&var.std__drop, create_function(type__std__drop, -1));
  assign_value(&var.std__put, create_function(type__std__put, -1));
  assign_value(&var.std__get, create_function(type__std__get, -1));
  assign_value(&var.std__next, create_function(type__std__next, -1));
  assign_value(&var.std__append, create_function(type__std__append, -1));
  assign_value(&var.std__insert_before, create_function(type__std__insert_before, -1));
  assign_value(&var.std__insert_behind, create_function(type__std__insert_behind, -1));
  assign_value(&var.std__first_index_of, create_function(type__std__first_index_of, -1));
  assign_value(&var.std__last_index_of, create_function(type__std__last_index_of, -1));
  assign_value(&var.std__delete_at, create_function(type__std__delete_at, -1));
  assign_value(&var.std__union, create_function(type__std__union, -1));
  assign_value(&var.std__intersection, create_function(type__std__intersection, -1));
  assign_value(&var.std__match_character, create_function(type__std__match_character, -1));
  assign_value(&var.std__match_string, create_function(type__std__match_string, -1));
  assign_value(&var.std__search_character, create_function(type__std__search_character, -1));
  assign_value(&var.std__search_string, create_function(type__std__search_string, -1));
  assign_value(&var.std__match, create_function(type__std__match, -1));
  assign_value(&var.std__search, create_function(type__std__search, -1));
  assign_value(&var.std__matches, create_function(type__std__matches, -1));
  assign_value(&var.std__contains, create_function(type__std__contains, -1));
  assign_value(&var.std__has_prefix, create_function(type__std__has_prefix, -1));
  assign_value(&var.std__has_suffix, create_function(type__std__has_suffix, -1));
  assign_value(&var.std__without_prefix, create_function(type__std__without_prefix, -1));
  assign_value(&var.std__without_suffix, create_function(type__std__without_suffix, -1));
  assign_value(&var.std__before, create_function(type__std__before, -1));
  assign_value(&var.std__truncate_from, create_function(type__std__truncate_from, -1));
  assign_value(&var.std__behind, create_function(type__std__behind, -1));
  assign_value(&var.std__truncate_until, create_function(type__std__truncate_until, -1));
  assign_value(&var.std__from, create_function(type__std__from, -1));
  assign_value(&var.std__truncate_before, create_function(type__std__truncate_before, -1));
  assign_value(&var.std__until, create_function(type__std__until, -1));
  assign_value(&var.std__truncate_behind, create_function(type__std__truncate_behind, -1));
  assign_value(&var.std__between, create_function(type__std__between, -1));
  assign_value(&var.std__range, create_function(type__std__range, -1));
  assign_value(&var.std__merge, create_function(type__std__merge, -1));
  assign_value(&var.std__sort, create_function(type__std__sort, -1));
  assign_value(&var.std__close, create_function(type__std__close, -1));
  assign_value(&var.std__write_some_bytes_to, create_function(type__std__write_some_bytes_to, -1));
  assign_value(&var.std__write_to, create_function(type__std__write_to, -1));
  assign_value(&var.std__flush, create_function(type__std__flush, -1));
  assign_value(&var.std__read_some_bytes_from, create_function(type__std__read_some_bytes_from, -1));
  assign_value(&var.std__read_from, create_function(type__std__read_from, -1));
  assign_value(&var.std__key_of, create_function(type__std__key_of, -1));
  assign_value(&var.std__value_of, create_function(type__std__value_of, -1));
  assign_value(&var.std__keys_of, create_function(type__std__keys_of, -1));
  assign_value(&var.std__values_of, create_function(type__std__values_of, -1));
  assign_value(&var.std__lower_bound_of, create_function(type__std__lower_bound_of, -1));
  assign_value(&var.std__upper_bound_of, create_function(type__std__upper_bound_of, -1));
  assign_value(&var.std__for_each_from_to, create_function(type__std__for_each_from_to, -1));
  assign_value(&var.std__for_each_from_down_to, create_function(type__std__for_each_from_down_to, -1));
  assign_value(&var.std__for_each, create_function(type__std__for_each, -1));
  assign_value(&var.std__for_each_downwards, create_function(type__std__for_each_downwards, -1));
  assign_value(&var.std__update_each_from_to, create_function(type__std__update_each_from_to, -1));
  assign_value(&var.std__update_each_from_down_to, create_function(type__std__update_each_from_down_to, -1));
  assign_value(&var.std__update_each, create_function(type__std__update_each, -1));
  assign_value(&var.std__update_each_downwards, create_function(type__std__update_each_downwards, -1));
  assign_value(&var.std__for_each_pair, create_function(type__std__for_each_pair, -1));
  assign_value(&var.std__new_empty_collection, create_function(type__std__new_empty_collection, -1));
  assign_value(&var.std__filter, create_function(type__std__filter, -1));
  assign_value(&var.std__map, create_function(type__std__map, -1));
  assign_value(&var.std__dup, create_function(type__std__dup, -1));
  assign_value(&var.std__interleave, create_function(type__std__interleave, -1));
  assign_value(&var.std__stop, create_function(type__std__stop, -1));
  assign_value(&var.std__get_file_descriptors, create_function(type__std__get_file_descriptors, -1));
  assign_value(&var.std__handle_requests, create_function(type__std__handle_requests, -1));
  assign_value(&var.std__select, create_function(type__std__select, -1));
  assign_value(&var.std__delete, create_function(type__std__delete, -1));
  assign_value(&var.std__update, create_function(type__std__update, -1));
  assign_value(&var.std__call_command, create_function(type__std__call_command, -1));
}

static int already_run_phase_5 = false;

EXPORT void phase_5__basic__polymorphic_functions(void) {
  if (already_run_phase_5) return;
  already_run_phase_5 = true;
  register_collector(collect__basic__polymorphic_functions);
}
