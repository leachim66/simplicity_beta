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
REGISTER FUNC func ASM("r14");
REGISTER FRAME *frame ASM("r15");
IMPORT void allocate_initialized_frame_gc(int slot_idx, int slot_count);
REGISTER int argument_count ASM("ebx");
REGISTER FRAME *arguments ASM("r12");
IMPORT void *node_p;
IMPORT int result_count;
IMPORT void invalid_results_error(void);
IMPORT void *allocate_and_clear(long size);
IMPORT void *allocate(long size);
typedef struct PHASE_2_COLLECTOR {
  void *dummy;
  void *next_collector;
  void (*collector)(void *data);
} PHASE_2_COLLECTOR;
IMPORT void register_phase_3_collector(void *data);
IMPORT NODE *collect_node(NODE *node);
IMPORT ATTRIBUTES *collect_attributes(ATTRIBUTES *attributes);
IMPORT void invalid_arguments_error(void);
IMPORT void no_such_function(void);
IMPORT OCTREE undefined_attributes_level_1;
IMPORT OCTREE undefined_attributes_level_2;
IMPORT OCTREE undefined_attributes_level_3;
IMPORT OCTREE undefined_attributes_level_4;
IMPORT OCTREE undefined_attributes_level_5;
IMPORT OCTREE undefined_attributes_level_6;
IMPORT OCTREE undefined_attributes_level_7;
IMPORT NODE *from_long(long val);
IMPORT void invalid_index_error(void);
IMPORT NODE *create_continuation(void);
IMPORT NODE *create_future(void);
IMPORT NODE *create_cell(void);
IMPORT NODE *create_cell_with_contents(NODE *contents);
typedef struct CELL {
  FUNC type;
  struct ATTRIBUTES *attributes;
  NODE *contents;
} CELL;
IMPORT NODE *undefined;
IMPORT NODE *create_closure(FUNC type, int par_count);
IMPORT void initialize_future(NODE *var, NODE *val);
IMPORT void too_few_arguments_error(void);
IMPORT void too_many_arguments_error(void);
IMPORT void allocate_arguments(void);
IMPORT NODE *from_arguments(int first_idx, int count);
IMPORT void collect_static_attributes(ATTRIBUTES *attributes);
IMPORT void register_module_info(MODULE_INFO *info);
IMPORT NODE *create_function(FUNC func, int par_count);
IMPORT void set_module(const char *name);
IMPORT void set_used_namespaces(const char **namespaces);
IMPORT NODE *register_unique_item(const char *name);
IMPORT void assign_value(NODE **dest, NODE *val);
IMPORT NODE *create_future_with_prototype(NODE *prototype);
IMPORT void define_single_assign_static(
  const char *namespace, const char *name,
  NODE_GETTER getter, NODE **var_p
);
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
IMPORT void define_type_function(
  const char *namespace, const char *name, FUNC type, int par_cnt
);
IMPORT void define_attribute(
  const char *namespace, const char *name,
  int id, NODE *attribute
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
static NODE_GETTER get__Error;
static NODE_GETTER get_value_or_future__Error;
static NODE_GETTER get__empty_unordered_set;
static NODE_GETTER get_value_or_future__empty_unordered_set;
static NODE_GETTER get__equal_type_and_value;
static NODE_GETTER get_value_or_future__equal_type_and_value;
static NODE_GETTER get__false;
static NODE_GETTER get_value_or_future__false;
static int poly_idx__for_each;
static NODE_GETTER get__for_each;
static int poly_idx__for_each_downwards;
static NODE_GETTER get__for_each_downwards;
static int poly_idx__for_each_from_down_to;
static NODE_GETTER get__for_each_from_down_to;
static int poly_idx__for_each_from_to;
static NODE_GETTER get__for_each_from_to;
static NODE_GETTER get__forever;
static NODE_GETTER get_value_or_future__forever;
static NODE_GETTER get__hash;
static NODE_GETTER get_value_or_future__hash;
static NODE_GETTER get__if;
static NODE_GETTER get_value_or_future__if;
static NODE_GETTER get__is_undefined;
static NODE_GETTER get_value_or_future__is_undefined;
static int poly_idx__length_of;
static NODE_GETTER get__length_of;
static int poly_idx__new_empty_collection;
static NODE_GETTER get__new_empty_collection;
static int poly_idx__private__get_item;
static NODE_GETTER get__private__get_item;
static int poly_idx__private__set_item;
static NODE_GETTER get__private__set_item;
static NODE_GETTER get__register_collection_serializer;
static NODE_GETTER get_value_or_future__register_collection_serializer;
static int poly_idx__serialization_tag_of;
static NODE_GETTER get__serialization_tag_of;
static NODE_GETTER get__std__equal;
static NODE_GETTER get_value_or_future__std__equal;
static NODE_GETTER get__std__key_of;
static NODE_GETTER get_value_or_future__std__key_of;
static NODE_GETTER get__std__value_of;
static NODE_GETTER get_value_or_future__std__value_of;
static NODE_GETTER get__true;
static NODE_GETTER get_value_or_future__true;
static NODE_GETTER get__types__generic_set;
static NODE_GETTER get_value_or_future__types__generic_set;
static NODE_GETTER get__undefined;
static NODE_GETTER get_value_or_future__undefined;
static struct {
  NODE *_NONE;
  NODE *_insert_item;
  NODE *_retrieve_item;
  NODE *_next_key;
  NODE *_previous_key;
  NODE *types__unordered_set;
  NODE *std__empty_unordered_set;
  NODE *std__unordered_set;
} var;
static const char *var_names[] = {
  "NONE",
  "insert_item",
  "retrieve_item",
  "next_key",
  "previous_key"
};
static NODE *unique__1_1;

typedef struct REFERRED_REVISION REFERRED_REVISION;
struct REFERRED_REVISION {
  REFERRED_REVISION *link;
  long rev_no;
};

typedef struct UNORDERED_SET_REVISION UNORDERED_SET_REVISION;
struct UNORDERED_SET_REVISION {
  UNORDERED_SET_REVISION *link;
  long rev_no; // the revision no. the value has been inserted or changed
  int value; // "false" must be stored to override "true" in older revisions
};

typedef struct UNORDERED_SET_KEY_COLLISION UNORDERED_SET_KEY_COLLISION;
struct UNORDERED_SET_KEY_COLLISION {
  UNORDERED_SET_KEY_COLLISION *link;
  NODE *key; // this need not be the original key used to store the entry
             // but might be another but equal key
  UNORDERED_SET_REVISION *revisions;
};

typedef struct UNORDERED_SET_HASH_COLLISION UNORDERED_SET_HASH_COLLISION;
struct UNORDERED_SET_HASH_COLLISION {
  UNORDERED_SET_HASH_COLLISION *link;
  long hash; // the hash value of the entry's key
  UNORDERED_SET_KEY_COLLISION *key_collisions;
};

typedef struct UNORDERED_SET_DATA UNORDERED_SET_DATA;
struct UNORDERED_SET_DATA {
  long rev_no; // the newest revision stored within the set
  long size; // the total number of entries
  union {
    long used; // the total number of used entries
    REFERRED_REVISION *referrers; // used during the garbage collection
  };
  UNORDERED_SET_HASH_COLLISION **entries;
};

typedef struct {
  void *type;
  ATTRIBUTES *attributes;
  long rev_no;
  UNORDERED_SET_DATA *data;
} UNORDERED_SET;

static void collect_unordered_set_data_phase_3(
  void *old_data
);

static UNORDERED_SET_DATA *collect_unordered_set_data(
  UNORDERED_SET_DATA *data, long rev_no,
  REFERRED_REVISION *referred_revision
);

static void *collect_unordered_set(UNORDERED_SET *node);
static void entry__11_1(void);
static NODE *func__11_1;
static void entry__12_1(void);
static NODE *func__12_1;
static NODE *get__types__unordered_set(void) {
  return var.types__unordered_set;
}
static NODE *create__types__unordered_set(long rev_no, UNORDERED_SET_DATA *data);
static void entry__14_1(void);
static NODE *func__14_1;
static void entry__15_1(void);
static NODE *func__15_1;
static void entry__16_1(void);
static NODE *func__16_1;
static NODE *func__17_1;
static void entry__17_1(void);
static FRAME_INFO frame__17_1 = {6, {"self", "key", "value", "return", "h", "cmp_key"}};
static void cont__17_2(void);
static NODE *func__17_3;
static void entry__17_3(void);
static FRAME_INFO frame__17_3 = {1, {"key"}};
static void cont__17_4(void);
static void cont__17_5(void);
static NODE *func__17_6;
static void entry__17_6(void);
static FRAME_INFO frame__17_6 = {6, {"self", "cmp_key", "h", "key", "value", "return"}};
static void cont__17_7(void);
static void cont__17_8(void);
static NODE *func__17_9;
static void entry__17_9(void);
static FRAME_INFO frame__17_9 = {2, {"return", "self"}};
static void cont__17_10(void);
static void cont__17_11(void);
static NODE *func__17_12;
static void entry__17_12(void);
static FRAME_INFO frame__17_12 = {2, {"key", "cmp_key"}};
static void cont__17_13(void);
static NODE *func__18_1;
static void entry__18_1(void);
static FRAME_INFO frame__18_1 = {5, {"self", "key", "return", "h", "cmp_key"}};
static void cont__18_2(void);
static NODE *func__18_3;
static void entry__18_3(void);
static FRAME_INFO frame__18_3 = {5, {"cmp_key", "self", "h", "return", "key"}};
static void cont__18_4(void);
static void cont__18_5(void);
static NODE *func__18_6;
static void entry__18_6(void);
static FRAME_INFO frame__18_6 = {1, {"return"}};
static void cont__18_7(void);
static void cont__18_8(void);
static NODE *func__18_9;
static void entry__18_9(void);
static FRAME_INFO frame__18_9 = {1, {"return"}};
static void cont__18_10(void);
static NODE *func__19_1;
static void entry__19_1(void);
static FRAME_INFO frame__19_1 = {3, {"key", "value", "myself"}};
static void cont__19_2(void);
static NODE *func__19_3;
static void entry__19_3(void);
static FRAME_INFO frame__19_3 = {2, {"myself", "key"}};
static NODE *func__19_4;
static void entry__19_4(void);
static FRAME_INFO frame__19_4 = {3, {"myself", "key", "value"}};
static NODE *string__20_1;
static NODE *func__21_1;
static void entry__21_1(void);
static FRAME_INFO frame__21_1 = {1, {"self"}};
static NODE *get__std__empty_unordered_set(void) {
  return var.std__empty_unordered_set;
}
static NODE *func__23_1;
static void entry__23_1(void);
static FRAME_INFO frame__23_1 = {2, {"initializers", "tab"}};
static NODE *func__23_2;
static void entry__23_2(void);
static FRAME_INFO frame__23_2 = {2, {"initializer", "tab"}};
static void cont__23_3(void);
static void cont__23_4(void);
static void cont__23_5(void);
static void cont__23_6(void);
static NODE *get__std__unordered_set(void) {
  return var.std__unordered_set;
}
static NODE *func__24_1;
static void entry__24_1(void);
static FRAME_INFO frame__24_1 = {4, {"self", "body", "return", "key"}};
static NODE *func__24_2;
static void entry__24_2(void);
static FRAME_INFO frame__24_2 = {4, {"key", "self", "return", "body"}};
static void cont__24_3(void);
static void cont__24_4(void);
static void cont__24_5(void);
static void cont__24_6(void);
static void cont__24_7(void);
static NODE *func__25_1;
static void entry__25_1(void);
static FRAME_INFO frame__25_1 = {7, {"self", "first", "last", "body", "return", "key", "h"}};
static void cont__25_2(void);
static void cont__25_3(void);
static void cont__25_4(void);
static NODE *func__25_5;
static void entry__25_5(void);
static FRAME_INFO frame__25_5 = {0, {}};
static NODE *string__25_6;
static void cont__25_7(void);
static NODE *func__25_8;
static void entry__25_8(void);
static FRAME_INFO frame__25_8 = {5, {"body", "key", "last", "return", "self"}};
static void cont__25_9(void);
static void cont__25_10(void);
static void cont__25_11(void);
static void cont__25_12(void);
static void cont__25_13(void);
static void cont__25_14(void);
static void cont__25_15(void);
static NODE *func__26_1;
static void entry__26_1(void);
static FRAME_INFO frame__26_1 = {4, {"self", "body", "return", "key"}};
static NODE *func__26_2;
static void entry__26_2(void);
static FRAME_INFO frame__26_2 = {4, {"key", "self", "return", "body"}};
static void cont__26_3(void);
static void cont__26_4(void);
static void cont__26_5(void);
static void cont__26_6(void);
static void cont__26_7(void);
static NODE *func__27_1;
static void entry__27_1(void);
static FRAME_INFO frame__27_1 = {7, {"self", "last", "first", "body", "return", "key", "h"}};
static void cont__27_2(void);
static void cont__27_3(void);
static void cont__27_4(void);
static NODE *func__27_5;
static void entry__27_5(void);
static FRAME_INFO frame__27_5 = {0, {}};
static NODE *string__27_6;
static void cont__27_7(void);
static NODE *func__27_8;
static void entry__27_8(void);
static FRAME_INFO frame__27_8 = {5, {"body", "key", "first", "return", "self"}};
static void cont__27_9(void);
static void cont__27_10(void);
static void cont__27_11(void);
static void cont__27_12(void);
static void cont__27_13(void);
static void cont__27_14(void);
static void cont__27_15(void);
static NODE *string__56_1;
static void cont__56_2(void);
void run__basic__types__unordered_set(void);

static CONTINUATION_INFO continuation_info[] = {
  {run__basic__types__unordered_set, NULL, 956, 956, 1, 66},
  {cont__56_2, NULL, },
  {entry__11_1, NULL, 301, 537, 3, 2},
  {entry__12_1, NULL, 540, 613, 3, 2},
  {entry__14_1, NULL, 630, 666, 3, 2},
  {entry__15_1, NULL, 669, 731, 3, 2},
  {entry__16_1, NULL, 734, 790, 3, 2},
  {entry__17_3, NULL, 799, 799, 37, 37},
  {entry__17_9, NULL, 813, 813, 25, 35},
  {entry__17_12, NULL, 815, 815, 72, 72},
  {entry__17_6, NULL, 812, 812, 5, 42},
  {cont__17_7, &frame__17_6, 813, 813, 8, 22},
  {cont__17_8, &frame__17_6, 813, 813, 5, 35},
  {cont__17_10, &frame__17_6, 814, 814, 8, 41},
  {cont__17_11, &frame__17_6, 814, 815, 5, 72},
  {entry__17_1, NULL, 799, 799, 6, 21},
  {cont__17_2, &frame__17_1, 799, 799, 3, 37},
  {cont__17_4, &frame__17_1, 800, 800, 3, 14},
  {cont__17_5, &frame__17_1, 811, 815, 3, 73},
  {cont__17_13, &frame__17_1, 815, 815, 73, 73},
  {entry__18_6, NULL, 839, 839, 25, 36},
  {entry__18_9, NULL, 840, 840, 44, 54},
  {entry__18_3, NULL, 834, 834, 5, 33},
  {cont__18_4, &frame__18_3, 839, 839, 8, 22},
  {cont__18_5, &frame__18_3, 839, 839, 5, 36},
  {cont__18_7, &frame__18_3, 840, 840, 8, 41},
  {cont__18_8, &frame__18_3, 840, 840, 5, 54},
  {entry__18_1, NULL, 823, 823, 3, 14},
  {cont__18_2, &frame__18_1, 833, 846, 3, 52},
  {cont__18_10, &frame__18_1, 846, 846, 52, 52},
  {entry__19_3, NULL, 862, 862, 7, 34},
  {entry__19_4, NULL, 864, 864, 7, 40},
  {entry__19_1, NULL, 861, 861, 5, 17},
  {cont__19_2, &frame__19_1, 860, 864, 3, 41},
  {entry__21_1, NULL, 868, 868, 53, 75},
  {entry__23_2, NULL, 875, 875, 5, 61},
  {cont__23_3, &frame__23_2, 875, 875, 10, 33},
  {cont__23_4, &frame__23_2, 875, 875, 5, 34},
  {cont__23_5, &frame__23_2, 875, 875, 61, 61},
  {entry__23_1, NULL, 874, 875, 3, 61},
  {cont__23_6, &frame__23_1, 876, 876, 3, 8},
  {entry__24_2, NULL, 891, 891, 19, 27},
  {cont__24_3, &frame__24_2, 891, 891, 5, 32},
  {cont__24_4, &frame__24_2, 892, 892, 8, 18},
  {cont__24_5, &frame__24_2, 892, 892, 5, 25},
  {cont__24_6, &frame__24_2, 893, 893, 5, 12},
  {entry__24_1, NULL, 890, 893, 3, 12},
  {cont__24_7, &frame__24_1, 893, 893, 12, 12},
  {entry__25_5, NULL, 910, 910, 19, 46},
  {entry__25_8, NULL, 912, 912, 5, 12},
  {cont__25_9, &frame__25_8, 913, 913, 8, 18},
  {cont__25_10, &frame__25_8, 913, 913, 5, 25},
  {cont__25_11, &frame__25_8, 914, 914, 19, 27},
  {cont__25_12, &frame__25_8, 914, 914, 5, 32},
  {cont__25_13, &frame__25_8, 915, 915, 8, 18},
  {cont__25_14, &frame__25_8, 915, 915, 5, 25},
  {entry__25_1, NULL, 908, 908, 3, 14},
  {cont__25_2, &frame__25_1, 909, 909, 3, 27},
  {cont__25_3, &frame__25_1, 910, 910, 6, 16},
  {cont__25_4, &frame__25_1, 910, 910, 3, 46},
  {cont__25_7, &frame__25_1, 911, 915, 3, 25},
  {cont__25_15, &frame__25_1, 915, 915, 25, 25},
  {entry__26_2, NULL, 930, 930, 23, 31},
  {cont__26_3, &frame__26_2, 930, 930, 5, 36},
  {cont__26_4, &frame__26_2, 931, 931, 8, 18},
  {cont__26_5, &frame__26_2, 931, 931, 5, 25},
  {cont__26_6, &frame__26_2, 932, 932, 5, 12},
  {entry__26_1, NULL, 929, 932, 3, 12},
  {cont__26_7, &frame__26_1, 932, 932, 12, 12},
  {entry__27_5, NULL, 949, 949, 19, 46},
  {entry__27_8, NULL, 951, 951, 5, 12},
  {cont__27_9, &frame__27_8, 952, 952, 8, 19},
  {cont__27_10, &frame__27_8, 952, 952, 5, 26},
  {cont__27_11, &frame__27_8, 953, 953, 23, 31},
  {cont__27_12, &frame__27_8, 953, 953, 5, 36},
  {cont__27_13, &frame__27_8, 954, 954, 8, 18},
  {cont__27_14, &frame__27_8, 954, 954, 5, 25},
  {entry__27_1, NULL, 947, 947, 3, 14},
  {cont__27_2, &frame__27_1, 948, 948, 3, 27},
  {cont__27_3, &frame__27_1, 949, 949, 6, 16},
  {cont__27_4, &frame__27_1, 949, 949, 3, 46},
  {cont__27_7, &frame__27_1, 950, 954, 3, 25},
  {cont__27_15, &frame__27_1, 954, 954, 25, 25}
};

union NODE {
  struct {
    FUNC type;
    ATTRIBUTES *attributes;
  };
  CONTINUATION continuation;
  CLOSURE closure;
  SIMPLE_NODE simple_node;
  UNORDERED_SET unordered_set;
};

static const char *used_namespaces[] = {
  "std",
  NULL
};

static MODULE_INFO module_info = {
  NULL,
  "basic__types__unordered_set",
  continuation_info,
  sizeof(continuation_info)/sizeof(CONTINUATION_INFO),
  (NODE **)&var,
  var_names,
  sizeof(var_names)/sizeof(const char *),
  used_namespaces,
  {DEBUG_FILENAME("basic/types/unordered_set.sim")}
};

/******
C O D E
******/

static int already_run = false;

EXPORT void run__basic__types__unordered_set(void) {
  if (already_run) {
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  already_run = true;
  allocate_initialized_frame_gc(0, 0);
  // 956: register_collection_serializer "unordered_set" empty_unordered_set
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__56_1;
  arguments->slots[1] = get__empty_unordered_set();
  result_count = 0;
  myself = get__register_collection_serializer();
  func = myself->type;
  frame->cont = cont__56_2;
}
static void cont__56_2(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}

static void collect_unordered_set_data_phase_3(
  void *old_data
) {
  //fprintf(stderr, "collect_unordered_set_data_phase_3 (%p)\n", old_data);
  UNORDERED_SET_DATA *data = DECODE_FROM_LENGTH(*(void **)old_data);
  /*REFERRED_REVISION *referrer = data->referrers;
  while (referrer) {
    fprintf(stderr, "rev_no: %ld\n", referrer->rev_no);
    referrer = referrer->link;
  }*/
  long size = data->size;
  long idx;
  //fprintf(stderr, "size: %ld\n", size);

  UNORDERED_SET_HASH_COLLISION **new_entries =
    allocate_and_clear(size*sizeof(UNORDERED_SET_HASH_COLLISION *));

  for (idx = 0; idx < size; ++idx) {
    UNORDERED_SET_HASH_COLLISION *hash_collision =
      data->entries[idx];

    if ((long)hash_collision & 1) {
      hash_collision = (void *)((long)hash_collision & -2);
      //fprintf(stderr, "idx: %ld\n", idx);
      //fprintf(stderr, "  %p\n", hash_collision);

      UNORDERED_SET_HASH_COLLISION **hash_collision_p = new_entries+idx;

      while (hash_collision) {
        UNORDERED_SET_KEY_COLLISION *key_collision =
          hash_collision->key_collisions;

        if ((long)key_collision & 1) {
          key_collision = (void *)((long)key_collision & -2);

          UNORDERED_SET_HASH_COLLISION *new_hash_collision =
            allocate(sizeof(UNORDERED_SET_HASH_COLLISION));

          new_hash_collision->link = NULL;
          new_hash_collision->hash = hash_collision->hash;
          new_hash_collision->key_collisions = NULL;

          *hash_collision_p = new_hash_collision;
          hash_collision_p = &new_hash_collision->link;

          //fprintf(stderr, "    %p\n", key_collision);

          UNORDERED_SET_KEY_COLLISION **key_collision_p =
            &new_hash_collision->key_collisions;

          while (key_collision) {
            if ((long)key_collision->key & 1) {
              UNORDERED_SET_KEY_COLLISION *new_key_collision =
                allocate(sizeof(UNORDERED_SET_KEY_COLLISION));

              new_key_collision->link = NULL;
              new_key_collision->key = (void *)((long)key_collision->key & -2);
              new_key_collision->revisions = NULL;

              *key_collision_p = new_key_collision;
              key_collision_p = &new_key_collision->link;

              UNORDERED_SET_REVISION **revision_p =
                &new_key_collision->revisions;

              UNORDERED_SET_REVISION *revision = key_collision->revisions;
              while (revision) {
                if (revision->value & 2) { // is marked?
                  //fprintf(stderr, "      rev_no: %ld\n", revision->rev_no);

                  UNORDERED_SET_REVISION *new_revision =
                    allocate(sizeof(UNORDERED_SET_REVISION));

                  new_revision->link = NULL;
                  new_revision->rev_no = revision->rev_no;
                  new_revision->value = revision->value & 1; // remove mark

                  *revision_p = new_revision;
                  revision_p = &new_revision->link;
                }
                revision = revision->link;
              }
            }
            key_collision = key_collision->link;
          }
        }
        hash_collision = hash_collision->link;
      }
    }
  }
  data->entries = new_entries;
  //fprintf(stderr, "collection phase 2 done (%p)\n", old_data);
}

static UNORDERED_SET_DATA *collect_unordered_set_data(
  UNORDERED_SET_DATA *data, long rev_no,
  REFERRED_REVISION *referred_revision
) {
  if (IS_COLLECTED(data)) {
    void *new_location = *(void **)data;

    //fprintf(stderr, "GC-%ld\n", rev_no);

    if (IS_AN_INVALID_LENGTH(new_location)) {
      data = DECODE_FROM_LENGTH(new_location);

      // don't mark twice
      REFERRED_REVISION *referrer = data->referrers;
      while (referrer) {
        if (referrer->rev_no == rev_no) return data;
        referrer = referrer->link;
      }
    } else {
      UNORDERED_SET_DATA *new_data =
        allocate(sizeof(UNORDERED_SET_DATA));
      new_data->rev_no = data->rev_no;
      new_data->size = data->size;
      new_data->referrers = NULL;
      new_data->entries = data->entries;

      //fprintf(stderr, "register phase 2 collector\n");
      ((PHASE_2_COLLECTOR *)data)->collector = collect_unordered_set_data_phase_3;
      register_phase_3_collector(data);

      *(void **)data = ENCODE_TO_LENGTH(new_data);
      data = new_data;
    }

    referred_revision->link = data->referrers;
    referred_revision->rev_no = rev_no;
    data->referrers = referred_revision;

    // the key order within the hash collisions must not be changed

    UNORDERED_SET_HASH_COLLISION **entries = data->entries;
    long idx;
    long size = data->size;
    //fprintf(stderr, "mark used entries (%ld)\n", size);
    for (idx = 0; idx < size; ++idx) {
      UNORDERED_SET_HASH_COLLISION *hash_collision =
        (void *)((long)entries[idx] & -2);
      int hash_collisions_used = false;
      while (hash_collision) {
        UNORDERED_SET_KEY_COLLISION *key_collision =
          (void *)((long)hash_collision->key_collisions & -2);
        int key_collisions_used = false;
        while (key_collision) {
          UNORDERED_SET_REVISION *revision = key_collision->revisions;
          int revision_used = false;
          while (revision) {
            if (revision->rev_no <= rev_no) {
              if (!(revision->value & 2)) { // is not marked?
                revision->value |= 2; // mark it!
                revision_used = true;
              }
              break;
            }
            revision = revision->link;
          }
          if (revision_used) {
            key_collision->key =
              (void *)((long)collect_node(key_collision->key) | 1);
            key_collisions_used = true;
          }
          key_collision = key_collision->link;
        }
        if (key_collisions_used) {
          hash_collision->key_collisions =
            (void *)((long)hash_collision->key_collisions | 1);
          hash_collisions_used = true;
        }
        hash_collision = hash_collision->link;
      }
      if (hash_collisions_used) {
        entries[idx] = (void *)((long)entries[idx] | 1);
      }
    }
    //fprintf(stderr, "marked used entries\n");
  } /*else if (data) {
    fprintf(stderr, "data: %p\n", data);
    fprintf(stderr, "???\n");
    exit(1);
  }*/
  return data;
}

static void *collect_unordered_set(UNORDERED_SET *node) {
  //fprintf(stderr, "collect unordered_set (%p)\n", node->data);
  UNORDERED_SET *new_node = allocate(sizeof(UNORDERED_SET));
  new_node->type = node->type;
  *(void **)node = ENCODE_ADDRESS(new_node);
  new_node->attributes = collect_attributes(node->attributes);
  new_node->rev_no = node->rev_no;
  new_node->data =
    collect_unordered_set_data(
      node->data, node->rev_no, (REFERRED_REVISION *)&node->rev_no);
  return new_node;
}
static void entry__11_1(void) {
  if (argument_count != 5) {
    invalid_arguments_error();
    return;
  }

  UNORDERED_SET *myself = (UNORDERED_SET *)arguments->slots[0];
  uint32_t hash = to_uint32(arguments->slots[1]);
  NODE *cmp_key = arguments->slots[2]; // NONE or a key returned from a previous call
  NODE *key = arguments->slots[3];
  int value = to_bool(arguments->slots[4]);

  long rev_no = myself->rev_no;
  UNORDERED_SET_DATA *data = myself->data;
  UNORDERED_SET_HASH_COLLISION **entries;
  long size;
  if (!data) { // we must allocate a data record
    size = 32; // the initial size for the set
    data = allocate(sizeof(UNORDERED_SET_DATA));
    // the empty set does *not* get a reference to the newly allocated data!
    data->rev_no = 0; // initial revision number is 0
    // no need to set <rev_no> - it must be 0
    data->size = size; // the maximum number of entries the set can hold without reallocation
    data->used = 0; // no entries are used yet
    data->entries = entries =
      allocate_and_clear(size*sizeof(UNORDERED_SET_HASH_COLLISION *));
  } else {
    size = data->size;
    entries = data->entries;
  }

  UNORDERED_SET_DATA *new_data = NULL;

  if (data->rev_no != rev_no) { // we must clone the set (data and entries)
    //fprintf(stderr, "clone (our rev_no: %ld; set's rev_no: %ld)\n", rev_no, data->rev_no);
    new_data = allocate(sizeof(UNORDERED_SET_DATA));
    new_data->rev_no = rev_no;
    new_data->size = size;
    new_data->used = data->used;
    new_data->entries =
      allocate(size*sizeof(UNORDERED_SET_HASH_COLLISION *));

    long idx;
    for (idx = 0; idx < size; ++idx) {
      //fprintf(stderr, "idx: %ld\n", idx);
      UNORDERED_SET_HASH_COLLISION *hash_collision = entries[idx];
      UNORDERED_SET_HASH_COLLISION *new_hash_collisions = NULL;
      UNORDERED_SET_HASH_COLLISION **new_hash_collisions_p =
        &new_hash_collisions;
      while (hash_collision) {
        UNORDERED_SET_KEY_COLLISION *key_collision =
          hash_collision->key_collisions;
        UNORDERED_SET_KEY_COLLISION *new_key_collisions = NULL;
        UNORDERED_SET_KEY_COLLISION **new_key_collisions_p =
          &new_key_collisions;
        while (key_collision) {
          UNORDERED_SET_REVISION *revision = key_collision->revisions;
          UNORDERED_SET_REVISION *new_revisions = NULL;
          UNORDERED_SET_REVISION **new_revision_p = &new_revisions;
          while (revision) {
            if (revision->rev_no <= rev_no) {
              UNORDERED_SET_REVISION *new_revision =
                allocate(sizeof(UNORDERED_SET_REVISION));
              new_revision->link = NULL;
              new_revision->rev_no = revision->rev_no;
              new_revision->value = revision->value;
              *new_revision_p = new_revision;
              new_revision_p = &new_revision->link;
            }
            revision = revision->link;
          }
          if (new_revisions) {
            UNORDERED_SET_KEY_COLLISION *new_key_collision =
              allocate(sizeof(UNORDERED_SET_KEY_COLLISION));
            new_key_collision->link = NULL;
            new_key_collision->key = key_collision->key;
            new_key_collision->revisions = new_revisions;
            *new_key_collisions_p = new_key_collision;
            new_key_collisions_p = &new_key_collision->link;
          }
          key_collision = key_collision->link;
        }
        if (new_key_collisions) {
          UNORDERED_SET_HASH_COLLISION *new_hash_collision =
            allocate(sizeof(UNORDERED_SET_HASH_COLLISION));
          new_hash_collision->link = NULL;
          new_hash_collision->hash = hash_collision->hash;
          new_hash_collision->key_collisions = new_key_collisions;
          *new_hash_collisions_p = new_hash_collision;
          new_hash_collisions_p = &new_hash_collision->link;
        }
        hash_collision = hash_collision->link;
      }
      new_data->entries[idx] = new_hash_collisions;
    }

    data = new_data;
    entries = new_data->entries;
  }

  NODE *key_node = var._NONE; // default: item has been inserted

  long idx = hash % size;
  //fprintf(stderr, "insert into slot %ld\n", idx);

  UNORDERED_SET_HASH_COLLISION *hash_collision = entries[idx];
  while (hash_collision) {
    if (hash_collision->hash == hash) goto found_identical_hash;
    hash_collision = hash_collision->link;
  }
  //fprintf(stderr, "create new hash collision entry\n");
  hash_collision = allocate(sizeof(UNORDERED_SET_HASH_COLLISION));
  hash_collision->link = entries[idx];
  hash_collision->hash = hash;
  hash_collision->key_collisions = NULL;
  entries[idx] = hash_collision;

  found_identical_hash:;

  //fprintf(stderr, "key: %p\n", key);
  //fprintf(stderr, "cmp_key: %p\n", cmp_key);

  UNORDERED_SET_KEY_COLLISION *key_collision = hash_collision->key_collisions;

  if (cmp_key == key) {
    // the caller has already checked the cmp_key and forces the insert

    //fprintf(stderr, "force insert\n");
    while (key_collision) {
      if (key_collision->key == key) goto insert_new_revision;
      key_collision = key_collision->link;
    }

    // fall through
    // the key is no longer present - must be removed by a garbage collection
    // so insert a new key collision entry
  } else if (cmp_key == var._NONE) {
    // first call to attempt to insert the new key and value

    while (key_collision) {
      if (key_collision->key == key) goto insert_new_revision;

      // we found a nonidentical key with the same 32-bit hash value
      // this key might be another key-value (with the same hash) or (probably)
      // another object for the same key-value
      // we delegate the decision to the caller unless we find an identical key

      if (cmp_key == var._NONE) {
        // let's store this key for later check by the caller

        cmp_key = key_collision->key;
      }

      key_collision = key_collision->link;
    }

    if (cmp_key != var._NONE) {
      // let the caller check this key

      //fprintf(stderr, "let the caller check this key\n");
      key_node = cmp_key;
      if (new_data) goto update_myself;
      goto leave;
    }

    // fall through - insert a new key_collision entry
  } else {
    // look for the cmp_key

    //fprintf(stderr, "look for another key\n");
    while (key_collision) {
      //fprintf(stderr, "key_collision->key: %p\n", key_collision->key);
      if (key_collision->key == cmp_key) {
        if (key_collision->link) {
          // let the caller check the next key

          key_node = key_collision->link->key;
          if (new_data) goto update_myself; // can this ever occur?
          goto leave;
        } else {
          // it's a unique new key

          goto insert_new_key;
        }
      }
      key_collision = key_collision->link;
    }

    // the cmp_key has been removed (by a garbage collection) ...

    key_collision = hash_collision->key_collisions;
    if (key_collision) {
      // ... so we have to start probing keys again

      key_node = key_collision->key;
      if (new_data) goto update_myself; // can this ever occur?
      goto leave;
    }

    // fall through - there are no more rivaling keys

  }

  insert_new_key:

  //fprintf(stderr, "create new key collision entry\n");
  key_collision = allocate(sizeof(UNORDERED_SET_KEY_COLLISION));
  key_collision->link = hash_collision->key_collisions;
  key_collision->key = key;
  key_collision->revisions = NULL;
  hash_collision->key_collisions = key_collision;

  insert_new_revision:;

  //fprintf(stderr, "create new revision entry\n");

  ++rev_no;

  UNORDERED_SET_REVISION *revision = allocate(sizeof(UNORDERED_SET_REVISION));
  revision->link = key_collision->revisions;
  revision->rev_no = rev_no;
  revision->value = value;
  key_collision->revisions = revision;

  data->rev_no = rev_no;

  update_myself:;

  NODE *new_set = create__types__unordered_set(rev_no, data);
  new_set->type = myself->type;
  new_set->attributes = myself->attributes;
  myself = (UNORDERED_SET *)new_set;

  leave:;

  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = (NODE *)myself;
  arguments->slots[1] = key_node;
  {
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__12_1(void) {
  if (argument_count != 3) {
    invalid_arguments_error();
    return;
  }

  UNORDERED_SET *myself = (UNORDERED_SET *)arguments->slots[0];
  uint32_t hash = to_uint32(arguments->slots[1]);
  NODE *cmp_key = arguments->slots[2];

  long rev_no = myself->rev_no;
  UNORDERED_SET_DATA *data = myself->data;

  NODE *key_node = var._NONE;
  int value = false;
  if (!data) goto leave;

  long size = data->size;
  UNORDERED_SET_HASH_COLLISION **entries = data->entries;

  long idx = hash % size;
  //fprintf(stderr, "idx: %ld\n", idx);

  UNORDERED_SET_HASH_COLLISION *hash_collision = entries[idx];
  while (hash_collision) {
    if (hash_collision->hash == hash) goto found_identical_hash;
    hash_collision = hash_collision->link;
  }
  goto leave;

  found_identical_hash:;

  //fprintf(stderr, "found identical hash\n");
  UNORDERED_SET_KEY_COLLISION *key_collision = hash_collision->key_collisions;

  if (cmp_key == var._NONE) {
    if (key_collision) goto found_matching_key;
    goto leave;
  }

  while (key_collision) {
    if (key_collision->key == cmp_key) {
      if (key_collision->link) {
        // let the caller check the next key

        key_node = key_collision->link->key;
        value = key_collision->link->revisions->value;
      }
      goto leave;
    }
    key_collision = key_collision->link;
  }

  // the cmp_key has been removed (by a garbage collection) ...
  // so let's start again

  key_collision = hash_collision->key_collisions;

  found_matching_key:;
  //fprintf(stderr, "found matching key\n");
  key_node = key_collision->key;

  UNORDERED_SET_REVISION *revision = key_collision->revisions;
  while (revision && revision->rev_no > rev_no) {
    revision = revision->link;
  }

  if (revision) {
    value = key_collision->revisions->value;
  }

  leave:;
  if (!value) {
    key_node = var._NONE;
  }
  {
    NODE *result__node = (NODE *)(key_node);
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}

static VTABLE vtable__types__unordered_set = {
  sizeof(UNORDERED_SET),
  (COLLECTOR *)&collect_unordered_set,
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

static ATTRIBUTES attributes__types__unordered_set = {
  &vtable__types__unordered_set,
  {
    &undefined_attributes_level_1, &undefined_attributes_level_2,
    &undefined_attributes_level_3, &undefined_attributes_level_4,
    &undefined_attributes_level_5, &undefined_attributes_level_6,
    &undefined_attributes_level_7
  }
};

static void type__types__unordered_set(void) {
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  {
    NODE *result__node = (NODE *)(create__types__unordered_set(0, NULL));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static NODE *create__types__unordered_set(long rev_no, UNORDERED_SET_DATA *data) {
  NODE *node = allocate(sizeof(UNORDERED_SET));
  node->type = type__types__unordered_set;
  node->attributes = &attributes__types__unordered_set;
  node->unordered_set.rev_no = rev_no;
  node->unordered_set.data = data;
  return node;
}
static void entry__14_1(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }

  UNORDERED_SET *myself = (UNORDERED_SET *)arguments->slots[0];

  long len = 0;

  UNORDERED_SET_DATA *data = myself->data;

  if (data) {
    long rev_no = data->rev_no;
    UNORDERED_SET_HASH_COLLISION **entries = data->entries;
    long size = data->size;
    long idx;
    for (idx = 0; idx < size; ++idx) {
      UNORDERED_SET_HASH_COLLISION *hash_collision = entries[idx];
      while (hash_collision) {
        UNORDERED_SET_KEY_COLLISION *key_collision =
          hash_collision->key_collisions;
        while (key_collision) {
          UNORDERED_SET_REVISION *revision = key_collision->revisions;
          while (revision) {
            if (revision->rev_no <= rev_no) {
            if (revision->value) ++len;
              break;
            }
            revision = revision->link;
          }
          key_collision = key_collision->link;
        }
        hash_collision = hash_collision->link;
      }
    }
  }

  {
    NODE *result__node = (NODE *)(from_long(len));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__15_1(void) {
  if (argument_count != 3) {
    invalid_arguments_error();
    return;
  }
  UNORDERED_SET *myself = (UNORDERED_SET *)arguments->slots[0];
  uint32_t hash = to_uint32(arguments->slots[1]);
  NODE *cmp_key = arguments->slots[2];

  NODE *key_node = var._NONE; // default: no more key and value found

  UNORDERED_SET_DATA *data = myself->data;
  if (data) {
    long rev_no = data->rev_no;
    UNORDERED_SET_HASH_COLLISION **entries = data->entries;
    long size = data->size;
    long idx;
    UNORDERED_SET_HASH_COLLISION *hash_collision;
    UNORDERED_SET_KEY_COLLISION *key_collision;
    UNORDERED_SET_REVISION *revision;
    if (cmp_key == var._NONE) {
      // find first key
      for (idx = 0; idx < size; ++idx) {
        hash_collision = entries[idx];
        while (hash_collision) {
          key_collision = hash_collision->key_collisions;
          while (key_collision) {
            revision = key_collision->revisions;
            while (revision) {
              if (revision->rev_no <= rev_no) {
                if (!revision->value) goto find_next;
                key_node = key_collision->key;
                goto leave;
              }
              revision = revision->link;
            }
            find_next:
            key_collision = key_collision->link;
          }
          hash_collision = hash_collision->link;
        }
      }
    } else {
      // find key
      idx = hash % size;

      hash_collision = entries[idx];
      while (hash_collision) {
        if (hash_collision->hash == hash) {
          key_collision = hash_collision->key_collisions;
          while (key_collision) {
            if (key_collision->key == cmp_key) {
              goto find_next;
            }
            key_collision = key_collision->link;
          }
        }
        hash_collision = hash_collision->link;
      }
      {
    invalid_index_error();
  }
    }
  }

  leave:;
  {
    NODE *result__node = (NODE *)(key_node);
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__16_1(void) {
  if (argument_count != 3) {
    invalid_arguments_error();
    return;
  }
  UNORDERED_SET *myself = (UNORDERED_SET *)arguments->slots[0];
  uint32_t hash = to_uint32(arguments->slots[1]);
  NODE *cmp_key = arguments->slots[2];

  NODE *key_node = var._NONE; // default: no more key and value found

  UNORDERED_SET_DATA *data = myself->data;
  if (data) {
    long rev_no = data->rev_no;
    UNORDERED_SET_HASH_COLLISION **entries = data->entries;
    long size = data->size;
    long idx;
    UNORDERED_SET_HASH_COLLISION *hash_collision;
    UNORDERED_SET_KEY_COLLISION *key_collision;
    UNORDERED_SET_REVISION *revision;
    if (cmp_key == var._NONE) {
      // find last key
      idx = size-1;
    } else {
      // find key
      idx = hash % size;
    }
    while (idx >= 0) {
      hash_collision = entries[idx];
      while (hash_collision) {
        key_collision = hash_collision->key_collisions;
        while (key_collision) {
          revision = key_collision->revisions;
          while (revision) {
            if (revision->rev_no <= rev_no) {
              if (!revision->value) goto skip;
              if (key_collision->key == cmp_key) {
                if (key_node != var._NONE) goto leave;
                cmp_key = var._NONE;
                goto find_previous;
              }
              key_node = key_collision->key;
              break;
            }
            revision = revision->link;
          }
          skip:
          key_collision = key_collision->link;
        }
        hash_collision = hash_collision->link;
      }
      if (key_node != var._NONE) goto leave;
      find_previous:
      --idx;
    }
  }

  leave:;
  {
    NODE *result__node = (NODE *)(key_node);
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__17_1(void) {
  allocate_initialized_frame_gc(4, 8);
  // slot allocations:
  // self: 0
  // key: 1
  // value: 2
  // return: 3
  // h: 4
  // cmp_key: 5
  frame->slots[3] /* return */ = create_continuation();
  frame->slots[4] /* h */ = create_future();
  frame->slots[5] /* cmp_key */ = create_cell();
  if (argument_count != 3) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* self */ = create_cell_with_contents(arguments->slots[0]);
  frame->slots[1] /* key */ = create_cell_with_contents(arguments->slots[1]);
  // 799: ... key.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* key */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__17_2;
}
static void cont__17_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 799: ... : !key undefined
  frame->slots[7] /* temp__2 */ = create_closure(entry__17_3, 0);
  // 799: if key.is_undefined: !key undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__17_4;
}
static void entry__17_3(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // key: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* key */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 799: ... !key undefined
  ((CELL *)frame->slots[0])->contents /* key */ = get__undefined();
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__17_4(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 800: $h hash(key)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* key */;
  result_count = 1;
  myself = get__hash();
  func = myself->type;
  frame->cont = cont__17_5;
}
static void cont__17_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* h */, arguments->slots[0]);
  // 807: $$cmp_key NONE
  ((CELL *)frame->slots[5])->contents /* cmp_key */ = var._NONE;
  // 811: ... :
  // 812:   insert_item &self h &cmp_key key value
  // 813:   if cmp_key == NONE: return self
  // 814:   if cmp_key .equal_type_and_value. key:
  // 815:     !key cmp_key # force the use of the already stored (and equal) key
  frame->slots[6] /* temp__1 */ = create_closure(entry__17_6, 0);
  // 811: forever:
  // 812:   insert_item &self h &cmp_key key value
  // 813:   if cmp_key == NONE: return self
  // 814:   if cmp_key .equal_type_and_value. key:
  // 815:     !key cmp_key # force the use of the already stored (and equal) key
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__forever();
  func = myself->type;
  frame->cont = cont__17_13;
}
static void entry__17_12(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // key: 0
  // cmp_key: 1
  frame->slots[0] = myself->closure.frame->slots[3]; /* key */
  frame->slots[1] = myself->closure.frame->slots[1]; /* cmp_key */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 815: !key cmp_key # force the use of the already stored (and equal) key
  ((CELL *)frame->slots[0])->contents /* key */ = ((CELL *)frame->slots[1])->contents /* cmp_key */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__17_6(void) {
  allocate_initialized_frame_gc(6, 8);
  // slot allocations:
  // self: 0
  // cmp_key: 1
  // h: 2
  // key: 3
  // value: 4
  // return: 5
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  frame->slots[1] = myself->closure.frame->slots[5]; /* cmp_key */
  frame->slots[2] = myself->closure.frame->slots[4]; /* h */
  frame->slots[3] = myself->closure.frame->slots[1]; /* key */
  frame->slots[4] = myself->closure.frame->slots[2]; /* value */
  frame->slots[5] = myself->closure.frame->slots[3]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 812: insert_item &self h &cmp_key key value
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  arguments->slots[1] = frame->slots[2] /* h */;
  arguments->slots[2] = ((CELL *)frame->slots[1])->contents /* cmp_key */;
  arguments->slots[3] = ((CELL *)frame->slots[3])->contents /* key */;
  arguments->slots[4] = frame->slots[4] /* value */;
  result_count = 2;
  myself = var._insert_item;
  func = myself->type;
  frame->cont = cont__17_7;
}
static void cont__17_7(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* self */ = arguments->slots[0];
  ((CELL *)frame->slots[1])->contents /* cmp_key */ = arguments->slots[1];
  // 813: ... cmp_key == NONE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* cmp_key */;
  arguments->slots[1] = var._NONE;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__17_8;
}
static void cont__17_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 813: ... : return self
  frame->slots[7] /* temp__2 */ = create_closure(entry__17_9, 0);
  // 813: if cmp_key == NONE: return self
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__17_10;
}
static void entry__17_9(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // return: 0
  // self: 1
  frame->slots[0] = myself->closure.frame->slots[5]; /* return */
  frame->slots[1] = myself->closure.frame->slots[0]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 813: ... return self
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* self */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__17_10(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 814: ... cmp_key .equal_type_and_value. key
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* cmp_key */;
  arguments->slots[1] = ((CELL *)frame->slots[3])->contents /* key */;
  result_count = 1;
  myself = get__equal_type_and_value();
  func = myself->type;
  frame->cont = cont__17_11;
}
static void cont__17_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 814: ... :
  // 815:   !key cmp_key # force the use of the already stored (and equal) key
  frame->slots[7] /* temp__2 */ = create_closure(entry__17_12, 0);
  // 814: if cmp_key .equal_type_and_value. key:
  // 815:   !key cmp_key # force the use of the already stored (and equal) key
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__17_13(void) {
  myself = frame->slots[3] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__18_1(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // self: 0
  // key: 1
  // return: 2
  // h: 3
  // cmp_key: 4
  frame->slots[2] /* return */ = create_continuation();
  frame->slots[3] /* h */ = create_future();
  frame->slots[4] /* cmp_key */ = create_cell();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 823: $h hash(key)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* key */;
  result_count = 1;
  myself = get__hash();
  func = myself->type;
  frame->cont = cont__18_2;
}
static void cont__18_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* h */, arguments->slots[0]);
  // 830: $$cmp_key NONE
  ((CELL *)frame->slots[4])->contents /* cmp_key */ = var._NONE;
  // 833: ... :
  // 834:   retrieve_item self h &cmp_key
  // 835:   
  // 836:   #ewriteln "___"
  // 837:   #edump `cmp_key
  // 838:   
  // 839:   if cmp_key == NONE: return false
  // 840:   if cmp_key .equal_type_and_value. key: return true
  // 841:   
  // 842:   #
  // ...
  frame->slots[5] /* temp__1 */ = create_closure(entry__18_3, 0);
  // 833: forever:
  // 834:   retrieve_item self h &cmp_key
  // 835:   
  // 836:   #ewriteln "___"
  // 837:   #edump `cmp_key
  // 838:   
  // 839:   if cmp_key == NONE: return false
  // 840:   if cmp_key .equal_type_and_value. key: return true
  // 841:   
  // 842:   #
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__forever();
  func = myself->type;
  frame->cont = cont__18_10;
}
static void entry__18_9(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 840: ... return true
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__true();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__18_3(void) {
  allocate_initialized_frame_gc(5, 7);
  // slot allocations:
  // cmp_key: 0
  // self: 1
  // h: 2
  // return: 3
  // key: 4
  frame->slots[0] = myself->closure.frame->slots[4]; /* cmp_key */
  frame->slots[1] = myself->closure.frame->slots[0]; /* self */
  frame->slots[2] = myself->closure.frame->slots[3]; /* h */
  frame->slots[3] = myself->closure.frame->slots[2]; /* return */
  frame->slots[4] = myself->closure.frame->slots[1]; /* key */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 834: retrieve_item self h &cmp_key
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* self */;
  arguments->slots[1] = frame->slots[2] /* h */;
  arguments->slots[2] = ((CELL *)frame->slots[0])->contents /* cmp_key */;
  result_count = 1;
  myself = var._retrieve_item;
  func = myself->type;
  frame->cont = cont__18_4;
}
static void cont__18_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* cmp_key */ = arguments->slots[0];
  // 839: ... cmp_key == NONE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* cmp_key */;
  arguments->slots[1] = var._NONE;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__18_5;
}
static void cont__18_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 839: ... : return false
  frame->slots[6] /* temp__2 */ = create_closure(entry__18_6, 0);
  // 839: if cmp_key == NONE: return false
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__18_7;
}
static void entry__18_6(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 839: ... return false
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__false();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__18_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 840: ... cmp_key .equal_type_and_value. key
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* cmp_key */;
  arguments->slots[1] = frame->slots[4] /* key */;
  result_count = 1;
  myself = get__equal_type_and_value();
  func = myself->type;
  frame->cont = cont__18_8;
}
static void cont__18_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 840: ... : return true
  frame->slots[6] /* temp__2 */ = create_closure(entry__18_9, 0);
  // 840: if cmp_key .equal_type_and_value. key: return true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__18_10(void) {
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__19_3(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // myself: 0
  // key: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* myself */
  frame->slots[1] = myself->closure.frame->slots[0]; /* key */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 862: private::get_item myself key
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* myself */;
  arguments->slots[1] = frame->slots[1] /* key */;
  result_count = frame->caller_result_count;
  myself = get__private__get_item();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__19_4(void) {
  allocate_initialized_frame_gc(3, 3);
  // slot allocations:
  // myself: 0
  // key: 1
  // value: 2
  frame->slots[0] = myself->closure.frame->slots[2]; /* myself */
  frame->slots[1] = myself->closure.frame->slots[0]; /* key */
  frame->slots[2] = myself->closure.frame->slots[1]; /* value */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 864: private::set_item myself key value
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* myself */;
  arguments->slots[1] = frame->slots[1] /* key */;
  arguments->slots[2] = frame->slots[2] /* value */;
  result_count = frame->caller_result_count;
  myself = get__private__set_item();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__19_1(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // key: 0
  // value: 1
  // myself: 2
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  if (argument_count > 2) {
    too_many_arguments_error();
    return;
  }
  switch(argument_count) {
    default: frame->slots[1] /* value */ = arguments->slots[1];
    case 1:;
  }
  switch(argument_count) {
    case 1: frame->slots[1] /* value */ = var._NONE;
  }
  frame->slots[2] /* myself */ = myself;
  // 861: NONE == value
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._NONE;
  arguments->slots[1] = frame->slots[1] /* value */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__19_2;
}
static void cont__19_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 861: ... :
  // 862:   private::get_item myself key
  frame->slots[4] /* temp__2 */ = create_closure(entry__19_3, 0);
  // 863: :
  // 864:   private::set_item myself key value
  frame->slots[5] /* temp__3 */ = create_closure(entry__19_4, 0);
  // 860: if
  // 861:   NONE == value:
  // 862:     private::get_item myself key
  // 863:   :
  // 864:     private::set_item myself key value
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  arguments->slots[2] = frame->slots[5] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__21_1(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // self: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 868: ... -> types::unordered_set
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var.types__unordered_set;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__23_1(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // initializers: 0
  // tab: 1
  frame->slots[1] /* tab */ = create_cell();
  frame->slots[0] /* initializers */ = from_arguments(0, argument_count-0);
  // 873: $$tab types::unordered_set
  ((CELL *)frame->slots[1])->contents /* tab */ = var.types__unordered_set;
  // 874: ... : (initializer)
  // 875:   !tab(std::key_of(initializer)) std::value_of(initializer)
  frame->slots[2] /* temp__1 */ = create_closure(entry__23_2, 1);
  // 874: for_each initializers: (initializer)
  // 875:   !tab(std::key_of(initializer)) std::value_of(initializer)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* initializers */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__23_6;
}
static void entry__23_2(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // initializer: 0
  // tab: 1
  frame->slots[1] = myself->closure.frame->slots[1]; /* tab */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 875: !tab(std::key_of(initializer)) std::value_of(initializer)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* initializer */;
  result_count = 1;
  myself = get__std__value_of();
  func = myself->type;
  frame->cont = cont__23_3;
}
static void cont__23_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 875: ... std::key_of(initializer)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* initializer */;
  result_count = 1;
  myself = get__std__key_of();
  func = myself->type;
  frame->cont = cont__23_4;
}
static void cont__23_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 875: !tab(std::key_of(initializer))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[1])->contents /* tab */;
  func = myself->type;
  frame->cont = cont__23_5;
}
static void cont__23_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* tab */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__23_6(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 876: -> tab
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* tab */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__24_1(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // self: 0
  // body: 1
  // return: 2
  // key: 3
  frame->slots[2] /* return */ = create_continuation();
  frame->slots[3] /* key */ = create_cell();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 889: $$key NONE
  ((CELL *)frame->slots[3])->contents /* key */ = var._NONE;
  // 890: ... :
  // 891:   next_key self hash(key) &key
  // 892:   if key == NONE return
  // 893:   body key
  frame->slots[4] /* temp__1 */ = create_closure(entry__24_2, 0);
  // 890: forever:
  // 891:   next_key self hash(key) &key
  // 892:   if key == NONE return
  // 893:   body key
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__forever();
  func = myself->type;
  frame->cont = cont__24_7;
}
static void entry__24_2(void) {
  allocate_initialized_frame_gc(4, 5);
  // slot allocations:
  // key: 0
  // self: 1
  // return: 2
  // body: 3
  frame->slots[0] = myself->closure.frame->slots[3]; /* key */
  frame->slots[1] = myself->closure.frame->slots[0]; /* self */
  frame->slots[2] = myself->closure.frame->slots[2]; /* return */
  frame->slots[3] = myself->closure.frame->slots[1]; /* body */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 891: ... hash(key)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* key */;
  result_count = 1;
  myself = get__hash();
  func = myself->type;
  frame->cont = cont__24_3;
}
static void cont__24_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 891: next_key self hash(key) &key
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* self */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  arguments->slots[2] = ((CELL *)frame->slots[0])->contents /* key */;
  result_count = 1;
  myself = var._next_key;
  func = myself->type;
  frame->cont = cont__24_4;
}
static void cont__24_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* key */ = arguments->slots[0];
  // 892: ... key == NONE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* key */;
  arguments->slots[1] = var._NONE;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__24_5;
}
static void cont__24_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 892: if key == NONE return
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* return */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__24_6;
}
static void cont__24_6(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 893: body key
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* key */;
  result_count = frame->caller_result_count;
  myself = frame->slots[3] /* body */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__24_7(void) {
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__25_1(void) {
  allocate_initialized_frame_gc(5, 8);
  // slot allocations:
  // self: 0
  // first: 1
  // last: 2
  // body: 3
  // return: 4
  // key: 5
  // h: 6
  frame->slots[4] /* return */ = create_continuation();
  frame->slots[5] /* key */ = create_cell();
  frame->slots[6] /* h */ = create_future();
  if (argument_count != 4) {
    invalid_arguments_error();
    return;
  }
  // 907: $$key first
  ((CELL *)frame->slots[5])->contents /* key */ = frame->slots[1] /* first */;
  // 908: $h hash(key)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[5])->contents /* key */;
  result_count = 1;
  myself = get__hash();
  func = myself->type;
  frame->cont = cont__25_2;
}
static void cont__25_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* h */, arguments->slots[0]);
  // 909: retrieve_item self h &key
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  arguments->slots[1] = frame->slots[6] /* h */;
  arguments->slots[2] = ((CELL *)frame->slots[5])->contents /* key */;
  result_count = 1;
  myself = var._retrieve_item;
  func = myself->type;
  frame->cont = cont__25_3;
}
static void cont__25_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[5])->contents /* key */ = arguments->slots[0];
  // 910: ... key == NONE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[5])->contents /* key */;
  arguments->slots[1] = var._NONE;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__25_4;
}
static void cont__25_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 910: if key == NONE: Error "Invalid index error!"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = func__25_5;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__25_7;
}
static void entry__25_5(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 910: ... Error "Invalid index error!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__25_6;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__25_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 911: ... :
  // 912:   body key
  // 913:   if key == last return
  // 914:   next_key self hash(key) &key
  // 915:   if key == NONE return
  frame->slots[7] /* temp__1 */ = create_closure(entry__25_8, 0);
  // 911: forever:
  // 912:   body key
  // 913:   if key == last return
  // 914:   next_key self hash(key) &key
  // 915:   if key == NONE return
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__forever();
  func = myself->type;
  frame->cont = cont__25_15;
}
static void entry__25_8(void) {
  allocate_initialized_frame_gc(5, 6);
  // slot allocations:
  // body: 0
  // key: 1
  // last: 2
  // return: 3
  // self: 4
  frame->slots[0] = myself->closure.frame->slots[3]; /* body */
  frame->slots[1] = myself->closure.frame->slots[5]; /* key */
  frame->slots[2] = myself->closure.frame->slots[2]; /* last */
  frame->slots[3] = myself->closure.frame->slots[4]; /* return */
  frame->slots[4] = myself->closure.frame->slots[0]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 912: body key
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* key */;
  result_count = 0;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame->cont = cont__25_9;
}
static void cont__25_9(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 913: ... key == last
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* key */;
  arguments->slots[1] = frame->slots[2] /* last */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__25_10;
}
static void cont__25_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 913: if key == last return
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* return */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__25_11;
}
static void cont__25_11(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 914: ... hash(key)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* key */;
  result_count = 1;
  myself = get__hash();
  func = myself->type;
  frame->cont = cont__25_12;
}
static void cont__25_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 914: next_key self hash(key) &key
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* self */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  arguments->slots[2] = ((CELL *)frame->slots[1])->contents /* key */;
  result_count = 1;
  myself = var._next_key;
  func = myself->type;
  frame->cont = cont__25_13;
}
static void cont__25_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* key */ = arguments->slots[0];
  // 915: ... key == NONE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* key */;
  arguments->slots[1] = var._NONE;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__25_14;
}
static void cont__25_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 915: if key == NONE return
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* return */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__25_15(void) {
  myself = frame->slots[4] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__26_1(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // self: 0
  // body: 1
  // return: 2
  // key: 3
  frame->slots[2] /* return */ = create_continuation();
  frame->slots[3] /* key */ = create_cell();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 928: $$key NONE
  ((CELL *)frame->slots[3])->contents /* key */ = var._NONE;
  // 929: ... :
  // 930:   previous_key self hash(key) &key
  // 931:   if key == NONE return
  // 932:   body key
  frame->slots[4] /* temp__1 */ = create_closure(entry__26_2, 0);
  // 929: forever:
  // 930:   previous_key self hash(key) &key
  // 931:   if key == NONE return
  // 932:   body key
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__forever();
  func = myself->type;
  frame->cont = cont__26_7;
}
static void entry__26_2(void) {
  allocate_initialized_frame_gc(4, 5);
  // slot allocations:
  // key: 0
  // self: 1
  // return: 2
  // body: 3
  frame->slots[0] = myself->closure.frame->slots[3]; /* key */
  frame->slots[1] = myself->closure.frame->slots[0]; /* self */
  frame->slots[2] = myself->closure.frame->slots[2]; /* return */
  frame->slots[3] = myself->closure.frame->slots[1]; /* body */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 930: ... hash(key)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* key */;
  result_count = 1;
  myself = get__hash();
  func = myself->type;
  frame->cont = cont__26_3;
}
static void cont__26_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 930: previous_key self hash(key) &key
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* self */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  arguments->slots[2] = ((CELL *)frame->slots[0])->contents /* key */;
  result_count = 1;
  myself = var._previous_key;
  func = myself->type;
  frame->cont = cont__26_4;
}
static void cont__26_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* key */ = arguments->slots[0];
  // 931: ... key == NONE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* key */;
  arguments->slots[1] = var._NONE;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__26_5;
}
static void cont__26_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 931: if key == NONE return
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* return */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__26_6;
}
static void cont__26_6(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 932: body key
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* key */;
  result_count = frame->caller_result_count;
  myself = frame->slots[3] /* body */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__26_7(void) {
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__27_1(void) {
  allocate_initialized_frame_gc(5, 8);
  // slot allocations:
  // self: 0
  // last: 1
  // first: 2
  // body: 3
  // return: 4
  // key: 5
  // h: 6
  frame->slots[4] /* return */ = create_continuation();
  frame->slots[5] /* key */ = create_cell();
  frame->slots[6] /* h */ = create_future();
  if (argument_count != 4) {
    invalid_arguments_error();
    return;
  }
  // 946: $$key last
  ((CELL *)frame->slots[5])->contents /* key */ = frame->slots[1] /* last */;
  // 947: $h hash(key)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[5])->contents /* key */;
  result_count = 1;
  myself = get__hash();
  func = myself->type;
  frame->cont = cont__27_2;
}
static void cont__27_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* h */, arguments->slots[0]);
  // 948: retrieve_item self h &key
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  arguments->slots[1] = frame->slots[6] /* h */;
  arguments->slots[2] = ((CELL *)frame->slots[5])->contents /* key */;
  result_count = 1;
  myself = var._retrieve_item;
  func = myself->type;
  frame->cont = cont__27_3;
}
static void cont__27_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[5])->contents /* key */ = arguments->slots[0];
  // 949: ... key == NONE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[5])->contents /* key */;
  arguments->slots[1] = var._NONE;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__27_4;
}
static void cont__27_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 949: if key == NONE: Error "Invalid index error!"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = func__27_5;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__27_7;
}
static void entry__27_5(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 949: ... Error "Invalid index error!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__27_6;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__27_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 950: ... :
  // 951:   body key
  // 952:   if key == first return
  // 953:   previous_key self hash(key) &key
  // 954:   if key == NONE return
  frame->slots[7] /* temp__1 */ = create_closure(entry__27_8, 0);
  // 950: forever:
  // 951:   body key
  // 952:   if key == first return
  // 953:   previous_key self hash(key) &key
  // 954:   if key == NONE return
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__forever();
  func = myself->type;
  frame->cont = cont__27_15;
}
static void entry__27_8(void) {
  allocate_initialized_frame_gc(5, 6);
  // slot allocations:
  // body: 0
  // key: 1
  // first: 2
  // return: 3
  // self: 4
  frame->slots[0] = myself->closure.frame->slots[3]; /* body */
  frame->slots[1] = myself->closure.frame->slots[5]; /* key */
  frame->slots[2] = myself->closure.frame->slots[2]; /* first */
  frame->slots[3] = myself->closure.frame->slots[4]; /* return */
  frame->slots[4] = myself->closure.frame->slots[0]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 951: body key
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* key */;
  result_count = 0;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame->cont = cont__27_9;
}
static void cont__27_9(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 952: ... key == first
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* key */;
  arguments->slots[1] = frame->slots[2] /* first */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__27_10;
}
static void cont__27_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 952: if key == first return
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* return */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__27_11;
}
static void cont__27_11(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 953: ... hash(key)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* key */;
  result_count = 1;
  myself = get__hash();
  func = myself->type;
  frame->cont = cont__27_12;
}
static void cont__27_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 953: previous_key self hash(key) &key
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* self */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  arguments->slots[2] = ((CELL *)frame->slots[1])->contents /* key */;
  result_count = 1;
  myself = var._previous_key;
  func = myself->type;
  frame->cont = cont__27_13;
}
static void cont__27_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* key */ = arguments->slots[0];
  // 954: ... key == NONE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* key */;
  arguments->slots[1] = var._NONE;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__27_14;
}
static void cont__27_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 954: if key == NONE return
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* return */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__27_15(void) {
  myself = frame->slots[4] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
EXPORT void collect__basic__types__unordered_set(void) {
  var._NONE = collect_node(var._NONE);
  unique__1_1 = collect_node(unique__1_1);
  var._insert_item = collect_node(var._insert_item);
  var._retrieve_item = collect_node(var._retrieve_item);
  var.types__unordered_set = collect_node(var.types__unordered_set);
  collect_static_attributes(&attributes__types__unordered_set);
  var._next_key = collect_node(var._next_key);
  var._previous_key = collect_node(var._previous_key);
  string__20_1 = collect_node(string__20_1);
  var.std__empty_unordered_set = collect_node(var.std__empty_unordered_set);
  var.std__unordered_set = collect_node(var.std__unordered_set);
  string__25_6 = collect_node(string__25_6);
  string__27_6 = collect_node(string__27_6);
  string__56_1 = collect_node(string__56_1);
}

static int already_run_phase_1 = false;

EXPORT void phase_1__basic__types__unordered_set(void) {
  if (already_run_phase_1) return;
  already_run_phase_1 = true;
  register_module_info(&module_info);
}

static int already_run_phase_2 = false;

EXPORT void phase_2__basic__types__unordered_set(void) {
  if (already_run_phase_2) return;
  already_run_phase_2 = true;
  func__17_1 = create_function(entry__17_1, 3);
  func__18_1 = create_function(entry__18_1, 2);
  func__21_1 = create_function(entry__21_1, 1);
  func__23_1 = create_function(entry__23_1, -1);
  func__24_1 = create_function(entry__24_1, 2);
  func__25_5 = create_function(entry__25_5, 0);
  func__25_1 = create_function(entry__25_1, 4);
  func__26_1 = create_function(entry__26_1, 2);
  func__27_5 = create_function(entry__27_5, 0);
  func__27_1 = create_function(entry__27_1, 4);
}

static int already_run_phase_3 = false;

EXPORT void phase_3__basic__types__unordered_set(void) {
  if (already_run_phase_3) return;
  already_run_phase_3 = true;
  set_module("basic__types__unordered_set");
  set_used_namespaces(used_namespaces);
  unique__1_1 = register_unique_item("NONE");
  assign_value(&var._NONE, unique__1_1);
  func__11_1 = create_future();
  func__12_1 = create_future();
  var.types__unordered_set = create_future_with_prototype(create__types__unordered_set(0, NULL));
  define_single_assign_static("types", "unordered_set", get__types__unordered_set, &var.types__unordered_set);
  func__14_1 = create_future();
  func__15_1 = create_future();
  func__16_1 = create_future();
  string__20_1 = from_latin_1_string("unordered_set", 13);
  define_single_assign_static("std", "empty_unordered_set", get__std__empty_unordered_set, &var.std__empty_unordered_set);
  define_single_assign_static("std", "unordered_set", get__std__unordered_set, &var.std__unordered_set);
  string__25_6 = from_latin_1_string("Invalid index error!", 20);
  string__27_6 = from_latin_1_string("Invalid index error!", 20);
  string__56_1 = from_latin_1_string("unordered_set", 13);
}

static int already_run_phase_4 = false;

EXPORT void phase_4__basic__types__unordered_set(void) {
  if (already_run_phase_4) return;
  already_run_phase_4 = true;
  set_module("basic__types__unordered_set");
  set_used_namespaces(used_namespaces);
  use_read_only(NULL, "Error", &get__Error, &get_value_or_future__Error);
  use_read_only(NULL, "empty_unordered_set", &get__empty_unordered_set, &get_value_or_future__empty_unordered_set);
  use_read_only(NULL, "equal_type_and_value", &get__equal_type_and_value, &get_value_or_future__equal_type_and_value);
  use_read_only(NULL, "false", &get__false, &get_value_or_future__false);
  use_polymorphic_function(NULL, "for_each", &get__for_each, &poly_idx__for_each);
  use_polymorphic_function(NULL, "for_each_downwards", &get__for_each_downwards, &poly_idx__for_each_downwards);
  use_polymorphic_function(NULL, "for_each_from_down_to", &get__for_each_from_down_to, &poly_idx__for_each_from_down_to);
  use_polymorphic_function(NULL, "for_each_from_to", &get__for_each_from_to, &poly_idx__for_each_from_to);
  use_read_only(NULL, "forever", &get__forever, &get_value_or_future__forever);
  use_read_only(NULL, "hash", &get__hash, &get_value_or_future__hash);
  use_read_only(NULL, "if", &get__if, &get_value_or_future__if);
  use_read_only(NULL, "is_undefined", &get__is_undefined, &get_value_or_future__is_undefined);
  use_polymorphic_function(NULL, "length_of", &get__length_of, &poly_idx__length_of);
  use_polymorphic_function(NULL, "new_empty_collection", &get__new_empty_collection, &poly_idx__new_empty_collection);
  use_polymorphic_function("private", "get_item", &get__private__get_item, &poly_idx__private__get_item);
  use_polymorphic_function("private", "set_item", &get__private__set_item, &poly_idx__private__set_item);
  use_read_only(NULL, "register_collection_serializer", &get__register_collection_serializer, &get_value_or_future__register_collection_serializer);
  use_polymorphic_function(NULL, "serialization_tag_of", &get__serialization_tag_of, &poly_idx__serialization_tag_of);
  use_read_only("std", "equal", &get__std__equal, &get_value_or_future__std__equal);
  use_read_only("std", "key_of", &get__std__key_of, &get_value_or_future__std__key_of);
  use_read_only("std", "value_of", &get__std__value_of, &get_value_or_future__std__value_of);
  use_read_only(NULL, "true", &get__true, &get_value_or_future__true);
  use_read_only("types", "generic_set", &get__types__generic_set, &get_value_or_future__types__generic_set);
  use_read_only(NULL, "undefined", &get__undefined, &get_value_or_future__undefined);
  define_method("types", "unordered_set", poly_idx__length_of, func__14_1);
  define_method("types", "unordered_set", poly_idx__private__set_item, func__17_1);
  define_method("types", "unordered_set", poly_idx__private__get_item, func__18_1);
  define_type_function("types", "unordered_set", entry__19_1, -1);
  define_attribute("types", "unordered_set", poly_idx__serialization_tag_of, string__20_1);
  define_method("types", "unordered_set", poly_idx__new_empty_collection, func__21_1);
  define_method("types", "unordered_set", poly_idx__for_each, func__24_1);
  define_method("types", "unordered_set", poly_idx__for_each_from_to, func__25_1);
  define_method("types", "unordered_set", poly_idx__for_each_downwards, func__26_1);
  define_method("types", "unordered_set", poly_idx__for_each_from_down_to, func__27_1);
}

static int already_run_phase_5 = false;

EXPORT void phase_5__basic__types__unordered_set(void) {
  if (already_run_phase_5) return;
  already_run_phase_5 = true;
  assign_variable(&var._insert_item, &func__11_1);
  assign_variable(&var._retrieve_item, &func__12_1);
  assign_value(&var.types__unordered_set, get__types__generic_set());
  assign_variable(&var._next_key, &func__15_1);
  assign_variable(&var._previous_key, &func__16_1);
  assign_variable(&var.std__empty_unordered_set, &var.types__unordered_set);
  assign_variable(&var.std__unordered_set, &func__23_1);
}

static int already_run_phase_6 = false;

EXPORT void phase_6__basic__types__unordered_set(void) {
  if (already_run_phase_6) return;
  already_run_phase_6 = true;
  assign_value(&func__11_1, create_function(entry__11_1, 5));
  assign_value(&func__12_1, create_function(entry__12_1, 3));
  assign_value(&func__14_1, create_function(entry__14_1, 1));
  assign_value(&func__15_1, create_function(entry__15_1, 3));
  assign_value(&func__16_1, create_function(entry__16_1, 3));
  register_collector(collect__basic__types__unordered_set);
}
