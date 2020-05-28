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
IMPORT NODE *undefined;
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
IMPORT NODE *create_closure(FUNC type, int par_count);
IMPORT void initialize_future(NODE *var, NODE *val);
IMPORT void too_few_arguments_error(void);
IMPORT void too_many_arguments_error(void);
IMPORT void allocate_arguments(void);
IMPORT NODE *from_arguments(int first_idx, int count);
IMPORT NODE *create_continuation_with_exit(FUNC exit_func);
IMPORT void continuation_type_function(void);
IMPORT int debug_print_head(int *indent_p, char **buf_p, const char *format, ...);
IMPORT const char *indent_to_string(int indent);
IMPORT int print(char **buf_p, const char *format, ...);
IMPORT int debug_print(int indent, char *buf, const char *format, ...);
IMPORT void collect_static_attributes(ATTRIBUTES *attributes);
IMPORT void register_module_info(MODULE_INFO *info);
IMPORT void set_module(const char *name);
IMPORT NODE *from_uint32(uint32_t val);
IMPORT NODE *register_unique_item(const char *name);
IMPORT NODE *create_function(FUNC func, int par_count);
IMPORT NODE *from_latin_1_string(const char *str, long len);
IMPORT void set_used_namespaces(const char **namespaces);
IMPORT void assign_value(NODE **dest, NODE *val);
IMPORT NODE *create_future_with_prototype(NODE *prototype);
IMPORT void define_single_assign_static(
  const char *namespace, const char *name,
  NODE_GETTER getter, NODE **var_p
);
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
static NODE_GETTER get__Error;
static NODE_GETTER get_value_or_future__Error;
static NODE_GETTER get__empty_unordered_table;
static NODE_GETTER get_value_or_future__empty_unordered_table;
static NODE_GETTER get__equal_type_and_value;
static NODE_GETTER get_value_or_future__equal_type_and_value;
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
static NODE_GETTER get__parameter_count_of;
static NODE_GETTER get_value_or_future__parameter_count_of;
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
static NODE_GETTER get__std__or;
static NODE_GETTER get_value_or_future__std__or;
static NODE_GETTER get__std__value_of;
static NODE_GETTER get_value_or_future__std__value_of;
static NODE_GETTER get__types__generic_table;
static NODE_GETTER get_value_or_future__types__generic_table;
static NODE_GETTER get__undefined;
static NODE_GETTER get_value_or_future__undefined;
static int poly_idx__update_each;
static NODE_GETTER get__update_each;
static int poly_idx__update_each_downwards;
static NODE_GETTER get__update_each_downwards;
static int poly_idx__update_each_from_down_to;
static NODE_GETTER get__update_each_from_down_to;
static int poly_idx__update_each_from_to;
static NODE_GETTER get__update_each_from_to;
static struct {
  NODE *_NONE;
  NODE *_insert_item;
  NODE *_retrieve_item;
  NODE *_next_key_and_value;
  NODE *_previous_key_and_value;
  NODE *types__unordered_table;
  NODE *std__empty_unordered_table;
  NODE *std__unordered_table;
} var;
static const char *var_names[] = {
  "NONE",
  "insert_item",
  "retrieve_item",
  "next_key_and_value",
  "previous_key_and_value"
};
static NODE *unique__NONE;

typedef struct REFERRED_REVISION REFERRED_REVISION;
struct REFERRED_REVISION {
  REFERRED_REVISION *link;
  long rev_no;
};

typedef struct UNORDERED_TABLE_REVISION UNORDERED_TABLE_REVISION;
struct UNORDERED_TABLE_REVISION {
  UNORDERED_TABLE_REVISION *link;
  long rev_no; // the revision no. the value has been inserted or changed
  NODE *value;
};

typedef struct UNORDERED_TABLE_KEY_COLLISION UNORDERED_TABLE_KEY_COLLISION;
struct UNORDERED_TABLE_KEY_COLLISION {
  UNORDERED_TABLE_KEY_COLLISION *link;
  NODE *key; // this need not be the original key used to store the entry
             // but might be another but equal key
  UNORDERED_TABLE_REVISION *revisions;
};

typedef struct UNORDERED_TABLE_HASH_COLLISION UNORDERED_TABLE_HASH_COLLISION;
struct UNORDERED_TABLE_HASH_COLLISION {
  UNORDERED_TABLE_HASH_COLLISION *link;
  long hash; // the hash value of the entry's key
  UNORDERED_TABLE_KEY_COLLISION *key_collisions;
};

typedef struct UNORDERED_TABLE_DATA UNORDERED_TABLE_DATA;
struct UNORDERED_TABLE_DATA {
  long rev_no; // the newest revision stored within the table
  long size; // the total number of entries
  union {
    long used; // the total number of used entries
    REFERRED_REVISION *referrers; // used during the garbage collection
  };
  UNORDERED_TABLE_HASH_COLLISION **entries;
};

typedef struct {
  void *type;
  ATTRIBUTES *attributes;
  long rev_no;
  UNORDERED_TABLE_DATA *data;
} UNORDERED_TABLE;

static void collect_unordered_table_data_phase_3(
  void *old_data
);

static UNORDERED_TABLE_DATA *collect_unordered_table_data(
  UNORDERED_TABLE_DATA *data, long rev_no,
  REFERRED_REVISION *referred_revision
);

static void *collect_unordered_table(UNORDERED_TABLE *node);
static void entry__insert_item_1(void);
static NODE *func__insert_item_1;
static void entry__retrieve_item_1(void);
static NODE *func__retrieve_item_1;
static NODE *get__types__unordered_table(void) {
  return var.types__unordered_table;
}
static NODE *create__types__unordered_table(long rev_no, UNORDERED_TABLE_DATA *data);
static void entry__types__unordered_table__length_of_1(void);
static NODE *func__types__unordered_table__length_of_1;
static void entry__next_key_and_value_1(void);
static NODE *func__next_key_and_value_1;
static void entry__previous_key_and_value_1(void);
static NODE *func__previous_key_and_value_1;
static NODE *func__types__unordered_table__private__set_item_1;
static void entry__types__unordered_table__private__set_item_1(void);
static FRAME_INFO frame__types__unordered_table__private__set_item_1 = {6, {"self", "key", "value", "return", "h", "cmp_key"}};
static void cont__types__unordered_table__private__set_item_2(void);
static NODE *func__types__unordered_table__private__set_item_3;
static void entry__types__unordered_table__private__set_item_3(void);
static FRAME_INFO frame__types__unordered_table__private__set_item_3 = {1, {"key"}};
static void cont__types__unordered_table__private__set_item_4(void);
static void cont__types__unordered_table__private__set_item_5(void);
static NODE *func__types__unordered_table__private__set_item_6;
static void entry__types__unordered_table__private__set_item_6(void);
static FRAME_INFO frame__types__unordered_table__private__set_item_6 = {6, {"self", "h", "cmp_key", "key", "value", "return"}};
static void cont__types__unordered_table__private__set_item_7(void);
static void cont__types__unordered_table__private__set_item_8(void);
static NODE *func__types__unordered_table__private__set_item_9;
static void entry__types__unordered_table__private__set_item_9(void);
static FRAME_INFO frame__types__unordered_table__private__set_item_9 = {2, {"return", "self"}};
static void cont__types__unordered_table__private__set_item_10(void);
static void cont__types__unordered_table__private__set_item_11(void);
static NODE *func__types__unordered_table__private__set_item_12;
static void entry__types__unordered_table__private__set_item_12(void);
static FRAME_INFO frame__types__unordered_table__private__set_item_12 = {2, {"key", "cmp_key"}};
static void cont__types__unordered_table__private__set_item_13(void);
static NODE *func__types__unordered_table__private__get_item_1;
static void entry__types__unordered_table__private__get_item_1(void);
static FRAME_INFO frame__types__unordered_table__private__get_item_1 = {5, {"self", "key", "return", "h", "cmp_key"}};
static void cont__types__unordered_table__private__get_item_2(void);
static NODE *func__types__unordered_table__private__get_item_3;
static void entry__types__unordered_table__private__get_item_3(void);
static FRAME_INFO frame__types__unordered_table__private__get_item_3 = {6, {"self", "h", "cmp_key", "key", "return", "retrieved_value"}};
static void cont__types__unordered_table__private__get_item_4(void);
static void cont__types__unordered_table__private__get_item_5(void);
static NODE *func__types__unordered_table__private__get_item_6;
static void entry__types__unordered_table__private__get_item_6(void);
static FRAME_INFO frame__types__unordered_table__private__get_item_6 = {2, {"cmp_key", "key"}};
static void cont__types__unordered_table__private__get_item_7(void);
static void cont__types__unordered_table__private__get_item_8(void);
static NODE *func__types__unordered_table__private__get_item_9;
static void entry__types__unordered_table__private__get_item_9(void);
static FRAME_INFO frame__types__unordered_table__private__get_item_9 = {2, {"return", "retrieved_value"}};
static void cont__types__unordered_table__private__get_item_10(void);
static NODE *func__types__unordered_table_1;
static void entry__types__unordered_table_1(void);
static FRAME_INFO frame__types__unordered_table_1 = {3, {"key", "value", "myself"}};
static void cont__types__unordered_table_2(void);
static NODE *func__types__unordered_table_3;
static void entry__types__unordered_table_3(void);
static FRAME_INFO frame__types__unordered_table_3 = {2, {"myself", "key"}};
static NODE *func__types__unordered_table_4;
static void entry__types__unordered_table_4(void);
static FRAME_INFO frame__types__unordered_table_4 = {3, {"myself", "key", "value"}};
static NODE *string__16058a9f0bf11cc9;
static NODE *func__types__unordered_table__new_empty_collection_1;
static void entry__types__unordered_table__new_empty_collection_1(void);
static FRAME_INFO frame__types__unordered_table__new_empty_collection_1 = {1, {"self"}};
static NODE *get__std__empty_unordered_table(void) {
  return var.std__empty_unordered_table;
}
static NODE *func__std__unordered_table_1;
static void entry__std__unordered_table_1(void);
static FRAME_INFO frame__std__unordered_table_1 = {2, {"initializers", "tab"}};
static NODE *func__std__unordered_table_2;
static void entry__std__unordered_table_2(void);
static FRAME_INFO frame__std__unordered_table_2 = {2, {"initializer", "tab"}};
static void cont__std__unordered_table_3(void);
static void cont__std__unordered_table_4(void);
static void cont__std__unordered_table_5(void);
static void cont__std__unordered_table_6(void);
static NODE *get__std__unordered_table(void) {
  return var.std__unordered_table;
}
static NODE *func__types__unordered_table__for_each_1;
static void entry__types__unordered_table__for_each_1(void);
static FRAME_INFO frame__types__unordered_table__for_each_1 = {4, {"self", "body", "return", "key"}};
static NODE *func__types__unordered_table__for_each_2;
static void entry__types__unordered_table__for_each_2(void);
static FRAME_INFO frame__types__unordered_table__for_each_2 = {5, {"self", "key", "return", "body", "value"}};
static void cont__types__unordered_table__for_each_3(void);
static void cont__types__unordered_table__for_each_4(void);
static void cont__types__unordered_table__for_each_5(void);
static void cont__types__unordered_table__for_each_6(void);
static void cont__types__unordered_table__for_each_7(void);
static void cont__types__unordered_table__for_each_8(void);
static NODE *func__types__unordered_table__for_each_9;
static void entry__types__unordered_table__for_each_9(void);
static FRAME_INFO frame__types__unordered_table__for_each_9 = {3, {"body", "key", "value"}};
static NODE *func__types__unordered_table__for_each_10;
static void entry__types__unordered_table__for_each_10(void);
static FRAME_INFO frame__types__unordered_table__for_each_10 = {2, {"body", "value"}};
static void cont__types__unordered_table__for_each_11(void);
static NODE *func__types__unordered_table__for_each_from_to_1;
static void entry__types__unordered_table__for_each_from_to_1(void);
static FRAME_INFO frame__types__unordered_table__for_each_from_to_1 = {8, {"self", "first", "last", "body", "return", "key", "value", "h"}};
static void cont__types__unordered_table__for_each_from_to_2(void);
static void cont__types__unordered_table__for_each_from_to_3(void);
static void cont__types__unordered_table__for_each_from_to_4(void);
static NODE *func__types__unordered_table__for_each_from_to_5;
static void entry__types__unordered_table__for_each_from_to_5(void);
static FRAME_INFO frame__types__unordered_table__for_each_from_to_5 = {0, {}};
static NODE *string__2bdb69f58c8fd6ea;
static void cont__types__unordered_table__for_each_from_to_7(void);
static NODE *func__types__unordered_table__for_each_from_to_8;
static void entry__types__unordered_table__for_each_from_to_8(void);
static FRAME_INFO frame__types__unordered_table__for_each_from_to_8 = {6, {"body", "key", "value", "last", "return", "self"}};
static void cont__types__unordered_table__for_each_from_to_9(void);
static void cont__types__unordered_table__for_each_from_to_10(void);
static NODE *func__types__unordered_table__for_each_from_to_11;
static void entry__types__unordered_table__for_each_from_to_11(void);
static FRAME_INFO frame__types__unordered_table__for_each_from_to_11 = {3, {"body", "key", "value"}};
static NODE *func__types__unordered_table__for_each_from_to_12;
static void entry__types__unordered_table__for_each_from_to_12(void);
static FRAME_INFO frame__types__unordered_table__for_each_from_to_12 = {2, {"body", "value"}};
static void cont__types__unordered_table__for_each_from_to_13(void);
static void cont__types__unordered_table__for_each_from_to_14(void);
static void cont__types__unordered_table__for_each_from_to_15(void);
static void cont__types__unordered_table__for_each_from_to_16(void);
static void cont__types__unordered_table__for_each_from_to_17(void);
static void cont__types__unordered_table__for_each_from_to_18(void);
static void cont__types__unordered_table__for_each_from_to_19(void);
static NODE *func__types__unordered_table__for_each_downwards_1;
static void entry__types__unordered_table__for_each_downwards_1(void);
static FRAME_INFO frame__types__unordered_table__for_each_downwards_1 = {4, {"self", "body", "return", "key"}};
static NODE *func__types__unordered_table__for_each_downwards_2;
static void entry__types__unordered_table__for_each_downwards_2(void);
static FRAME_INFO frame__types__unordered_table__for_each_downwards_2 = {5, {"self", "key", "return", "body", "value"}};
static void cont__types__unordered_table__for_each_downwards_3(void);
static void cont__types__unordered_table__for_each_downwards_4(void);
static void cont__types__unordered_table__for_each_downwards_5(void);
static void cont__types__unordered_table__for_each_downwards_6(void);
static void cont__types__unordered_table__for_each_downwards_7(void);
static void cont__types__unordered_table__for_each_downwards_8(void);
static NODE *func__types__unordered_table__for_each_downwards_9;
static void entry__types__unordered_table__for_each_downwards_9(void);
static FRAME_INFO frame__types__unordered_table__for_each_downwards_9 = {3, {"body", "key", "value"}};
static NODE *func__types__unordered_table__for_each_downwards_10;
static void entry__types__unordered_table__for_each_downwards_10(void);
static FRAME_INFO frame__types__unordered_table__for_each_downwards_10 = {2, {"body", "value"}};
static void cont__types__unordered_table__for_each_downwards_11(void);
static NODE *func__types__unordered_table__for_each_from_down_to_1;
static void entry__types__unordered_table__for_each_from_down_to_1(void);
static FRAME_INFO frame__types__unordered_table__for_each_from_down_to_1 = {8, {"self", "last", "first", "body", "return", "key", "value", "h"}};
static void cont__types__unordered_table__for_each_from_down_to_2(void);
static void cont__types__unordered_table__for_each_from_down_to_3(void);
static void cont__types__unordered_table__for_each_from_down_to_4(void);
static NODE *func__types__unordered_table__for_each_from_down_to_5;
static void entry__types__unordered_table__for_each_from_down_to_5(void);
static FRAME_INFO frame__types__unordered_table__for_each_from_down_to_5 = {0, {}};
static void cont__types__unordered_table__for_each_from_down_to_6(void);
static NODE *func__types__unordered_table__for_each_from_down_to_7;
static void entry__types__unordered_table__for_each_from_down_to_7(void);
static FRAME_INFO frame__types__unordered_table__for_each_from_down_to_7 = {6, {"body", "key", "value", "first", "return", "self"}};
static void cont__types__unordered_table__for_each_from_down_to_8(void);
static void cont__types__unordered_table__for_each_from_down_to_9(void);
static NODE *func__types__unordered_table__for_each_from_down_to_10;
static void entry__types__unordered_table__for_each_from_down_to_10(void);
static FRAME_INFO frame__types__unordered_table__for_each_from_down_to_10 = {3, {"body", "key", "value"}};
static NODE *func__types__unordered_table__for_each_from_down_to_11;
static void entry__types__unordered_table__for_each_from_down_to_11(void);
static FRAME_INFO frame__types__unordered_table__for_each_from_down_to_11 = {2, {"body", "value"}};
static void cont__types__unordered_table__for_each_from_down_to_12(void);
static void cont__types__unordered_table__for_each_from_down_to_13(void);
static void cont__types__unordered_table__for_each_from_down_to_14(void);
static void cont__types__unordered_table__for_each_from_down_to_15(void);
static void cont__types__unordered_table__for_each_from_down_to_16(void);
static void cont__types__unordered_table__for_each_from_down_to_17(void);
static void cont__types__unordered_table__for_each_from_down_to_18(void);
static NODE *func__types__unordered_table__update_each_1;
static void entry__types__unordered_table__update_each_1(void);
static FRAME_INFO frame__types__unordered_table__update_each_1 = {4, {"self", "body", "return", "key"}};
static void exit__types__unordered_table__update_each_1(void);
static NODE *func__types__unordered_table__update_each_2;
static void entry__types__unordered_table__update_each_2(void);
static FRAME_INFO frame__types__unordered_table__update_each_2 = {5, {"self", "key", "return", "body", "value"}};
static void cont__types__unordered_table__update_each_3(void);
static void cont__types__unordered_table__update_each_4(void);
static void cont__types__unordered_table__update_each_5(void);
static void cont__types__unordered_table__update_each_6(void);
static void cont__types__unordered_table__update_each_7(void);
static void cont__types__unordered_table__update_each_8(void);
static void cont__types__unordered_table__update_each_9(void);
static NODE *func__types__unordered_table__update_each_from_to_1;
static void entry__types__unordered_table__update_each_from_to_1(void);
static FRAME_INFO frame__types__unordered_table__update_each_from_to_1 = {8, {"self", "first", "last", "body", "return", "key", "value", "h"}};
static void exit__types__unordered_table__update_each_from_to_1(void);
static void cont__types__unordered_table__update_each_from_to_2(void);
static void cont__types__unordered_table__update_each_from_to_3(void);
static void cont__types__unordered_table__update_each_from_to_4(void);
static NODE *func__types__unordered_table__update_each_from_to_5;
static void entry__types__unordered_table__update_each_from_to_5(void);
static FRAME_INFO frame__types__unordered_table__update_each_from_to_5 = {0, {}};
static void cont__types__unordered_table__update_each_from_to_6(void);
static NODE *func__types__unordered_table__update_each_from_to_7;
static void entry__types__unordered_table__update_each_from_to_7(void);
static FRAME_INFO frame__types__unordered_table__update_each_from_to_7 = {6, {"body", "key", "value", "self", "last", "return"}};
static void cont__types__unordered_table__update_each_from_to_8(void);
static void cont__types__unordered_table__update_each_from_to_9(void);
static void cont__types__unordered_table__update_each_from_to_10(void);
static void cont__types__unordered_table__update_each_from_to_11(void);
static void cont__types__unordered_table__update_each_from_to_12(void);
static void cont__types__unordered_table__update_each_from_to_13(void);
static void cont__types__unordered_table__update_each_from_to_14(void);
static void cont__types__unordered_table__update_each_from_to_15(void);
static NODE *func__types__unordered_table__update_each_downwards_1;
static void entry__types__unordered_table__update_each_downwards_1(void);
static FRAME_INFO frame__types__unordered_table__update_each_downwards_1 = {4, {"self", "body", "return", "key"}};
static void exit__types__unordered_table__update_each_downwards_1(void);
static NODE *func__types__unordered_table__update_each_downwards_2;
static void entry__types__unordered_table__update_each_downwards_2(void);
static FRAME_INFO frame__types__unordered_table__update_each_downwards_2 = {5, {"self", "key", "return", "body", "value"}};
static void cont__types__unordered_table__update_each_downwards_3(void);
static void cont__types__unordered_table__update_each_downwards_4(void);
static void cont__types__unordered_table__update_each_downwards_5(void);
static void cont__types__unordered_table__update_each_downwards_6(void);
static void cont__types__unordered_table__update_each_downwards_7(void);
static void cont__types__unordered_table__update_each_downwards_8(void);
static void cont__types__unordered_table__update_each_downwards_9(void);
static NODE *func__types__unordered_table__update_each_from_down_to_1;
static void entry__types__unordered_table__update_each_from_down_to_1(void);
static FRAME_INFO frame__types__unordered_table__update_each_from_down_to_1 = {8, {"self", "last", "first", "body", "return", "key", "value", "h"}};
static void exit__types__unordered_table__update_each_from_down_to_1(void);
static void cont__types__unordered_table__update_each_from_down_to_2(void);
static void cont__types__unordered_table__update_each_from_down_to_3(void);
static void cont__types__unordered_table__update_each_from_down_to_4(void);
static NODE *func__types__unordered_table__update_each_from_down_to_5;
static void entry__types__unordered_table__update_each_from_down_to_5(void);
static FRAME_INFO frame__types__unordered_table__update_each_from_down_to_5 = {0, {}};
static void cont__types__unordered_table__update_each_from_down_to_6(void);
static NODE *func__types__unordered_table__update_each_from_down_to_7;
static void entry__types__unordered_table__update_each_from_down_to_7(void);
static FRAME_INFO frame__types__unordered_table__update_each_from_down_to_7 = {6, {"body", "key", "value", "self", "first", "return"}};
static void cont__types__unordered_table__update_each_from_down_to_8(void);
static void cont__types__unordered_table__update_each_from_down_to_9(void);
static void cont__types__unordered_table__update_each_from_down_to_10(void);
static void cont__types__unordered_table__update_each_from_down_to_11(void);
static void cont__types__unordered_table__update_each_from_down_to_12(void);
static void cont__types__unordered_table__update_each_from_down_to_13(void);
static void cont__types__unordered_table__update_each_from_down_to_14(void);
static void cont__types__unordered_table__update_each_from_down_to_15(void);

static long func__types__unordered_table___debug_string(NODE *node, int indent, int max_depth, char *buf);
static void cont__66_1(void);
void run__basic__types__unordered_table(void);

static CONTINUATION_INFO continuation_info[] = {
  {run__basic__types__unordered_table, NULL, 1191, 1191, 1, 70},
  {cont__66_1, NULL, },
  {entry__insert_item_1, NULL, 305, 541, 3, 2},
  {entry__retrieve_item_1, NULL, 544, 617, 3, 2},
  {entry__types__unordered_table__length_of_1, NULL, 636, 672, 3, 2},
  {entry__next_key_and_value_1, NULL, 675, 742, 3, 2},
  {entry__previous_key_and_value_1, NULL, 745, 806, 3, 2},
  {entry__types__unordered_table__private__set_item_3, NULL, 817, 817, 37, 37},
  {entry__types__unordered_table__private__set_item_9, NULL, 832, 832, 25, 35},
  {entry__types__unordered_table__private__set_item_12, NULL, 834, 834, 72, 72},
  {entry__types__unordered_table__private__set_item_6, NULL, 831, 831, 5, 42},
  {cont__types__unordered_table__private__set_item_7, &frame__types__unordered_table__private__set_item_6, 832, 832, 8, 22},
  {cont__types__unordered_table__private__set_item_8, &frame__types__unordered_table__private__set_item_6, 832, 832, 5, 35},
  {cont__types__unordered_table__private__set_item_10, &frame__types__unordered_table__private__set_item_6, 833, 833, 8, 41},
  {cont__types__unordered_table__private__set_item_11, &frame__types__unordered_table__private__set_item_6, 833, 834, 5, 72},
  {entry__types__unordered_table__private__set_item_1, NULL, 817, 817, 6, 21},
  {cont__types__unordered_table__private__set_item_2, &frame__types__unordered_table__private__set_item_1, 817, 817, 3, 37},
  {cont__types__unordered_table__private__set_item_4, &frame__types__unordered_table__private__set_item_1, 818, 818, 3, 14},
  {cont__types__unordered_table__private__set_item_5, &frame__types__unordered_table__private__set_item_1, 830, 834, 3, 73},
  {cont__types__unordered_table__private__set_item_13, &frame__types__unordered_table__private__set_item_1, 834, 834, 73, 73},
  {entry__types__unordered_table__private__get_item_6, NULL, 861, 861, 27, 60},
  {cont__types__unordered_table__private__get_item_7, &frame__types__unordered_table__private__get_item_6, 861, 861, 27, 60},
  {entry__types__unordered_table__private__get_item_9, NULL, 862, 862, 7, 28},
  {entry__types__unordered_table__private__get_item_3, NULL, 856, 856, 5, 50},
  {cont__types__unordered_table__private__get_item_4, &frame__types__unordered_table__private__get_item_3, 861, 861, 8, 22},
  {cont__types__unordered_table__private__get_item_5, &frame__types__unordered_table__private__get_item_3, 861, 861, 8, 60},
  {cont__types__unordered_table__private__get_item_8, &frame__types__unordered_table__private__get_item_3, 861, 862, 5, 28},
  {entry__types__unordered_table__private__get_item_1, NULL, 844, 844, 3, 14},
  {cont__types__unordered_table__private__get_item_2, &frame__types__unordered_table__private__get_item_1, 855, 868, 3, 52},
  {cont__types__unordered_table__private__get_item_10, &frame__types__unordered_table__private__get_item_1, 868, 868, 52, 52},
  {entry__types__unordered_table_3, NULL, 886, 886, 7, 34},
  {entry__types__unordered_table_4, NULL, 888, 888, 7, 40},
  {entry__types__unordered_table_1, NULL, 885, 885, 5, 17},
  {cont__types__unordered_table_2, &frame__types__unordered_table_1, 884, 888, 3, 41},
  {entry__types__unordered_table__new_empty_collection_1, NULL, 900, 900, 3, 27},
  {entry__std__unordered_table_2, NULL, 921, 921, 5, 61},
  {cont__std__unordered_table_3, &frame__std__unordered_table_2, 921, 921, 10, 33},
  {cont__std__unordered_table_4, &frame__std__unordered_table_2, 921, 921, 5, 34},
  {cont__std__unordered_table_5, &frame__std__unordered_table_2, 921, 921, 61, 61},
  {entry__std__unordered_table_1, NULL, 920, 921, 3, 61},
  {cont__std__unordered_table_6, &frame__std__unordered_table_1, 922, 922, 3, 8},
  {entry__types__unordered_table__for_each_9, NULL, 943, 943, 9, 22},
  {entry__types__unordered_table__for_each_10, NULL, 945, 945, 9, 18},
  {entry__types__unordered_table__for_each_2, NULL, 939, 939, 29, 37},
  {cont__types__unordered_table__for_each_3, &frame__types__unordered_table__for_each_2, 939, 939, 5, 49},
  {cont__types__unordered_table__for_each_4, &frame__types__unordered_table__for_each_2, 940, 940, 8, 18},
  {cont__types__unordered_table__for_each_5, &frame__types__unordered_table__for_each_2, 940, 940, 5, 25},
  {cont__types__unordered_table__for_each_6, &frame__types__unordered_table__for_each_2, 942, 942, 7, 30},
  {cont__types__unordered_table__for_each_7, &frame__types__unordered_table__for_each_2, 942, 942, 7, 35},
  {cont__types__unordered_table__for_each_8, &frame__types__unordered_table__for_each_2, 941, 945, 5, 19},
  {entry__types__unordered_table__for_each_1, NULL, 938, 945, 3, 20},
  {cont__types__unordered_table__for_each_11, &frame__types__unordered_table__for_each_1, 945, 945, 20, 20},
  {entry__types__unordered_table__for_each_from_to_5, NULL, 965, 965, 19, 46},
  {entry__types__unordered_table__for_each_from_to_11, NULL, 969, 969, 9, 22},
  {entry__types__unordered_table__for_each_from_to_12, NULL, 971, 971, 9, 18},
  {entry__types__unordered_table__for_each_from_to_8, NULL, 968, 968, 7, 30},
  {cont__types__unordered_table__for_each_from_to_9, &frame__types__unordered_table__for_each_from_to_8, 968, 968, 7, 35},
  {cont__types__unordered_table__for_each_from_to_10, &frame__types__unordered_table__for_each_from_to_8, 967, 971, 5, 19},
  {cont__types__unordered_table__for_each_from_to_13, &frame__types__unordered_table__for_each_from_to_8, 972, 972, 8, 18},
  {cont__types__unordered_table__for_each_from_to_14, &frame__types__unordered_table__for_each_from_to_8, 972, 972, 5, 25},
  {cont__types__unordered_table__for_each_from_to_15, &frame__types__unordered_table__for_each_from_to_8, 973, 973, 29, 37},
  {cont__types__unordered_table__for_each_from_to_16, &frame__types__unordered_table__for_each_from_to_8, 973, 973, 5, 49},
  {cont__types__unordered_table__for_each_from_to_17, &frame__types__unordered_table__for_each_from_to_8, 974, 974, 8, 18},
  {cont__types__unordered_table__for_each_from_to_18, &frame__types__unordered_table__for_each_from_to_8, 974, 974, 5, 25},
  {entry__types__unordered_table__for_each_from_to_1, NULL, 963, 963, 3, 14},
  {cont__types__unordered_table__for_each_from_to_2, &frame__types__unordered_table__for_each_from_to_1, 964, 964, 3, 34},
  {cont__types__unordered_table__for_each_from_to_3, &frame__types__unordered_table__for_each_from_to_1, 965, 965, 6, 16},
  {cont__types__unordered_table__for_each_from_to_4, &frame__types__unordered_table__for_each_from_to_1, 965, 965, 3, 46},
  {cont__types__unordered_table__for_each_from_to_7, &frame__types__unordered_table__for_each_from_to_1, 966, 974, 3, 25},
  {cont__types__unordered_table__for_each_from_to_19, &frame__types__unordered_table__for_each_from_to_1, 974, 974, 25, 25},
  {entry__types__unordered_table__for_each_downwards_9, NULL, 995, 995, 9, 22},
  {entry__types__unordered_table__for_each_downwards_10, NULL, 997, 997, 9, 18},
  {entry__types__unordered_table__for_each_downwards_2, NULL, 991, 991, 33, 41},
  {cont__types__unordered_table__for_each_downwards_3, &frame__types__unordered_table__for_each_downwards_2, 991, 991, 5, 53},
  {cont__types__unordered_table__for_each_downwards_4, &frame__types__unordered_table__for_each_downwards_2, 992, 992, 8, 18},
  {cont__types__unordered_table__for_each_downwards_5, &frame__types__unordered_table__for_each_downwards_2, 992, 992, 5, 25},
  {cont__types__unordered_table__for_each_downwards_6, &frame__types__unordered_table__for_each_downwards_2, 994, 994, 7, 30},
  {cont__types__unordered_table__for_each_downwards_7, &frame__types__unordered_table__for_each_downwards_2, 994, 994, 7, 35},
  {cont__types__unordered_table__for_each_downwards_8, &frame__types__unordered_table__for_each_downwards_2, 993, 997, 5, 19},
  {entry__types__unordered_table__for_each_downwards_1, NULL, 990, 997, 3, 20},
  {cont__types__unordered_table__for_each_downwards_11, &frame__types__unordered_table__for_each_downwards_1, 997, 997, 20, 20},
  {entry__types__unordered_table__for_each_from_down_to_5, NULL, 1017, 1017, 19, 46},
  {entry__types__unordered_table__for_each_from_down_to_10, NULL, 1021, 1021, 9, 22},
  {entry__types__unordered_table__for_each_from_down_to_11, NULL, 1023, 1023, 9, 18},
  {entry__types__unordered_table__for_each_from_down_to_7, NULL, 1020, 1020, 7, 30},
  {cont__types__unordered_table__for_each_from_down_to_8, &frame__types__unordered_table__for_each_from_down_to_7, 1020, 1020, 7, 35},
  {cont__types__unordered_table__for_each_from_down_to_9, &frame__types__unordered_table__for_each_from_down_to_7, 1019, 1023, 5, 19},
  {cont__types__unordered_table__for_each_from_down_to_12, &frame__types__unordered_table__for_each_from_down_to_7, 1024, 1024, 8, 19},
  {cont__types__unordered_table__for_each_from_down_to_13, &frame__types__unordered_table__for_each_from_down_to_7, 1024, 1024, 5, 26},
  {cont__types__unordered_table__for_each_from_down_to_14, &frame__types__unordered_table__for_each_from_down_to_7, 1025, 1025, 33, 41},
  {cont__types__unordered_table__for_each_from_down_to_15, &frame__types__unordered_table__for_each_from_down_to_7, 1025, 1025, 5, 53},
  {cont__types__unordered_table__for_each_from_down_to_16, &frame__types__unordered_table__for_each_from_down_to_7, 1026, 1026, 8, 18},
  {cont__types__unordered_table__for_each_from_down_to_17, &frame__types__unordered_table__for_each_from_down_to_7, 1026, 1026, 5, 25},
  {entry__types__unordered_table__for_each_from_down_to_1, NULL, 1015, 1015, 3, 14},
  {cont__types__unordered_table__for_each_from_down_to_2, &frame__types__unordered_table__for_each_from_down_to_1, 1016, 1016, 3, 34},
  {cont__types__unordered_table__for_each_from_down_to_3, &frame__types__unordered_table__for_each_from_down_to_1, 1017, 1017, 6, 16},
  {cont__types__unordered_table__for_each_from_down_to_4, &frame__types__unordered_table__for_each_from_down_to_1, 1017, 1017, 3, 46},
  {cont__types__unordered_table__for_each_from_down_to_6, &frame__types__unordered_table__for_each_from_down_to_1, 1018, 1026, 3, 25},
  {cont__types__unordered_table__for_each_from_down_to_18, &frame__types__unordered_table__for_each_from_down_to_1, 1026, 1026, 25, 25},
  {entry__types__unordered_table__update_each_2, NULL, 1043, 1043, 29, 37},
  {cont__types__unordered_table__update_each_3, &frame__types__unordered_table__update_each_2, 1043, 1043, 5, 50},
  {cont__types__unordered_table__update_each_4, &frame__types__unordered_table__update_each_2, 1044, 1044, 8, 18},
  {cont__types__unordered_table__update_each_5, &frame__types__unordered_table__update_each_2, 1044, 1044, 5, 25},
  {cont__types__unordered_table__update_each_6, &frame__types__unordered_table__update_each_2, 1045, 1045, 5, 19},
  {cont__types__unordered_table__update_each_7, &frame__types__unordered_table__update_each_2, 1046, 1046, 5, 14},
  {cont__types__unordered_table__update_each_8, &frame__types__unordered_table__update_each_2, 1046, 1046, 20, 20},
  {entry__types__unordered_table__update_each_1, NULL, 1042, 1046, 3, 20},
  {cont__types__unordered_table__update_each_9, &frame__types__unordered_table__update_each_1, 1046, 1046, 20, 20},
  {entry__types__unordered_table__update_each_from_to_5, NULL, 1066, 1066, 19, 46},
  {entry__types__unordered_table__update_each_from_to_7, NULL, 1068, 1068, 5, 19},
  {cont__types__unordered_table__update_each_from_to_8, &frame__types__unordered_table__update_each_from_to_7, 1069, 1069, 5, 14},
  {cont__types__unordered_table__update_each_from_to_9, &frame__types__unordered_table__update_each_from_to_7, 1070, 1070, 8, 18},
  {cont__types__unordered_table__update_each_from_to_10, &frame__types__unordered_table__update_each_from_to_7, 1070, 1070, 5, 25},
  {cont__types__unordered_table__update_each_from_to_11, &frame__types__unordered_table__update_each_from_to_7, 1071, 1071, 29, 37},
  {cont__types__unordered_table__update_each_from_to_12, &frame__types__unordered_table__update_each_from_to_7, 1071, 1071, 5, 49},
  {cont__types__unordered_table__update_each_from_to_13, &frame__types__unordered_table__update_each_from_to_7, 1072, 1072, 8, 18},
  {cont__types__unordered_table__update_each_from_to_14, &frame__types__unordered_table__update_each_from_to_7, 1072, 1072, 5, 25},
  {entry__types__unordered_table__update_each_from_to_1, NULL, 1064, 1064, 3, 14},
  {cont__types__unordered_table__update_each_from_to_2, &frame__types__unordered_table__update_each_from_to_1, 1065, 1065, 3, 34},
  {cont__types__unordered_table__update_each_from_to_3, &frame__types__unordered_table__update_each_from_to_1, 1066, 1066, 6, 16},
  {cont__types__unordered_table__update_each_from_to_4, &frame__types__unordered_table__update_each_from_to_1, 1066, 1066, 3, 46},
  {cont__types__unordered_table__update_each_from_to_6, &frame__types__unordered_table__update_each_from_to_1, 1067, 1072, 3, 25},
  {cont__types__unordered_table__update_each_from_to_15, &frame__types__unordered_table__update_each_from_to_1, 1072, 1072, 25, 25},
  {entry__types__unordered_table__update_each_downwards_2, NULL, 1089, 1089, 33, 41},
  {cont__types__unordered_table__update_each_downwards_3, &frame__types__unordered_table__update_each_downwards_2, 1089, 1089, 5, 54},
  {cont__types__unordered_table__update_each_downwards_4, &frame__types__unordered_table__update_each_downwards_2, 1090, 1090, 8, 18},
  {cont__types__unordered_table__update_each_downwards_5, &frame__types__unordered_table__update_each_downwards_2, 1090, 1090, 5, 25},
  {cont__types__unordered_table__update_each_downwards_6, &frame__types__unordered_table__update_each_downwards_2, 1091, 1091, 5, 19},
  {cont__types__unordered_table__update_each_downwards_7, &frame__types__unordered_table__update_each_downwards_2, 1092, 1092, 5, 14},
  {cont__types__unordered_table__update_each_downwards_8, &frame__types__unordered_table__update_each_downwards_2, 1092, 1092, 20, 20},
  {entry__types__unordered_table__update_each_downwards_1, NULL, 1088, 1092, 3, 20},
  {cont__types__unordered_table__update_each_downwards_9, &frame__types__unordered_table__update_each_downwards_1, 1092, 1092, 20, 20},
  {entry__types__unordered_table__update_each_from_down_to_5, NULL, 1112, 1112, 19, 46},
  {entry__types__unordered_table__update_each_from_down_to_7, NULL, 1114, 1114, 5, 19},
  {cont__types__unordered_table__update_each_from_down_to_8, &frame__types__unordered_table__update_each_from_down_to_7, 1115, 1115, 5, 14},
  {cont__types__unordered_table__update_each_from_down_to_9, &frame__types__unordered_table__update_each_from_down_to_7, 1116, 1116, 8, 19},
  {cont__types__unordered_table__update_each_from_down_to_10, &frame__types__unordered_table__update_each_from_down_to_7, 1116, 1116, 5, 26},
  {cont__types__unordered_table__update_each_from_down_to_11, &frame__types__unordered_table__update_each_from_down_to_7, 1117, 1117, 33, 41},
  {cont__types__unordered_table__update_each_from_down_to_12, &frame__types__unordered_table__update_each_from_down_to_7, 1117, 1117, 5, 53},
  {cont__types__unordered_table__update_each_from_down_to_13, &frame__types__unordered_table__update_each_from_down_to_7, 1118, 1118, 8, 18},
  {cont__types__unordered_table__update_each_from_down_to_14, &frame__types__unordered_table__update_each_from_down_to_7, 1118, 1118, 5, 25},
  {entry__types__unordered_table__update_each_from_down_to_1, NULL, 1110, 1110, 3, 14},
  {cont__types__unordered_table__update_each_from_down_to_2, &frame__types__unordered_table__update_each_from_down_to_1, 1111, 1111, 3, 34},
  {cont__types__unordered_table__update_each_from_down_to_3, &frame__types__unordered_table__update_each_from_down_to_1, 1112, 1112, 6, 16},
  {cont__types__unordered_table__update_each_from_down_to_4, &frame__types__unordered_table__update_each_from_down_to_1, 1112, 1112, 3, 46},
  {cont__types__unordered_table__update_each_from_down_to_6, &frame__types__unordered_table__update_each_from_down_to_1, 1113, 1118, 3, 25},
  {cont__types__unordered_table__update_each_from_down_to_15, &frame__types__unordered_table__update_each_from_down_to_1, 1118, 1118, 25, 25}
};

union NODE {
  struct {
    FUNC type;
    ATTRIBUTES *attributes;
  };
  CONTINUATION continuation;
  CLOSURE closure;
  SIMPLE_NODE simple_node;
  UNORDERED_TABLE unordered_table;
};
static NODE *number__2;

static const char *used_namespaces[] = {
  "std",
  NULL
};

static MODULE_INFO module_info = {
  NULL,
  "basic__types__unordered_table",
  continuation_info,
  sizeof(continuation_info)/sizeof(CONTINUATION_INFO),
  (NODE **)&var,
  var_names,
  sizeof(var_names)/sizeof(const char *),
  used_namespaces,
  {DEBUG_FILENAME("basic/types/unordered_table.sim")}
};

/******
C O D E
******/

static int already_run = false;

EXPORT void run__basic__types__unordered_table(void) {
  if (already_run) {
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  already_run = true;
  allocate_initialized_frame_gc(0, 0);
  // 1191: register_collection_serializer "unordered_table" empty_unordered_table
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__16058a9f0bf11cc9;
  arguments->slots[1] = get__empty_unordered_table();
  result_count = 0;
  myself = get__register_collection_serializer();
  func = myself->type;
  frame->cont = cont__66_1;
}
static void cont__66_1(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}

static void collect_unordered_table_data_phase_3(
  void *old_data
) {
  //fprintf(stderr, "collect_unordered_table_data_phase_3 (%p)\n", old_data);
  UNORDERED_TABLE_DATA *data = DECODE_FROM_LENGTH(*(void **)old_data);
  /*REFERRED_REVISION *referrer = data->referrers;
  while (referrer) {
    fprintf(stderr, "rev_no: %ld\n", referrer->rev_no);
    referrer = referrer->link;
  }*/
  long size = data->size;
  long idx;
  //fprintf(stderr, "size: %ld\n", size);

  UNORDERED_TABLE_HASH_COLLISION **new_entries =
    allocate_and_clear(size*sizeof(UNORDERED_TABLE_HASH_COLLISION *));

  for (idx = 0; idx < size; ++idx) {
    UNORDERED_TABLE_HASH_COLLISION *hash_collision =
      data->entries[idx];

    if ((long)hash_collision & 1) {
      hash_collision = (void *)((long)hash_collision & -2);
      //fprintf(stderr, "idx: %ld\n", idx);
      //fprintf(stderr, "  %p\n", hash_collision);

      UNORDERED_TABLE_HASH_COLLISION **hash_collision_p = new_entries+idx;

      while (hash_collision) {
        UNORDERED_TABLE_KEY_COLLISION *key_collision =
          hash_collision->key_collisions;

        if ((long)key_collision & 1) {
          key_collision = (void *)((long)key_collision & -2);

          UNORDERED_TABLE_HASH_COLLISION *new_hash_collision =
            allocate(sizeof(UNORDERED_TABLE_HASH_COLLISION));

          new_hash_collision->link = NULL;
          new_hash_collision->hash = hash_collision->hash;
          new_hash_collision->key_collisions = NULL;

          *hash_collision_p = new_hash_collision;
          hash_collision_p = &new_hash_collision->link;

          //fprintf(stderr, "    %p\n", key_collision);

          UNORDERED_TABLE_KEY_COLLISION **key_collision_p =
            &new_hash_collision->key_collisions;

          while (key_collision) {
            if ((long)key_collision->key & 1) {
              UNORDERED_TABLE_KEY_COLLISION *new_key_collision =
                allocate(sizeof(UNORDERED_TABLE_KEY_COLLISION));

              new_key_collision->link = NULL;
              new_key_collision->key = (void *)((long)key_collision->key & -2);
              new_key_collision->revisions = NULL;

              *key_collision_p = new_key_collision;
              key_collision_p = &new_key_collision->link;

              UNORDERED_TABLE_REVISION **revision_p =
                &new_key_collision->revisions;

              UNORDERED_TABLE_REVISION *revision = key_collision->revisions;
              while (revision) {
                if ((long)revision->value & 1) {
                  //fprintf(stderr, "      rev_no: %ld\n", revision->rev_no);

                  UNORDERED_TABLE_REVISION *new_revision =
                    allocate(sizeof(UNORDERED_TABLE_REVISION));

                  new_revision->link = NULL;
                  new_revision->rev_no = revision->rev_no;
                  new_revision->value = (void *)((long)revision->value & -2);

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

static UNORDERED_TABLE_DATA *collect_unordered_table_data(
  UNORDERED_TABLE_DATA *data, long rev_no,
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
      UNORDERED_TABLE_DATA *new_data =
        allocate(sizeof(UNORDERED_TABLE_DATA));
      new_data->rev_no = data->rev_no;
      new_data->size = data->size;
      new_data->referrers = NULL;
      new_data->entries = data->entries;

      //fprintf(stderr, "register phase 2 collector\n");
      ((PHASE_2_COLLECTOR *)data)->collector = collect_unordered_table_data_phase_3;
      register_phase_3_collector(data);

      *(void **)data = ENCODE_TO_LENGTH(new_data);
      data = new_data;
    }

    referred_revision->link = data->referrers;
    referred_revision->rev_no = rev_no;
    data->referrers = referred_revision;

    // the key order within the hash collisions must not be changed

    UNORDERED_TABLE_HASH_COLLISION **entries = data->entries;
    long idx;
    long size = data->size;
    //fprintf(stderr, "mark used entries (%ld)\n", size);
    for (idx = 0; idx < size; ++idx) {
      UNORDERED_TABLE_HASH_COLLISION *hash_collision =
        (void *)((long)entries[idx] & -2);
      int hash_collisions_used = false;
      while (hash_collision) {
        UNORDERED_TABLE_KEY_COLLISION *key_collision =
          (void *)((long)hash_collision->key_collisions & -2);
        int key_collisions_used = false;
        while (key_collision) {
          UNORDERED_TABLE_REVISION *revision = key_collision->revisions;
          int revision_used = false;
          while (revision) {
            if (revision->rev_no <= rev_no) {
              //fprintf(stderr, "idx: %ld; rev_no: %ld (%ld)\n",
              //  idx, revision->rev_no, (long)revision->value & 1);
              if (!((long)revision->value & 1)) {
                revision->value =
                  (void *)((long)collect_node(revision->value) | 1);
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

static void *collect_unordered_table(UNORDERED_TABLE *node) {
  //fprintf(stderr, "collect unordered_table (%p)\n", node->data);
  UNORDERED_TABLE *new_node = allocate(sizeof(UNORDERED_TABLE));
  new_node->type = node->type;
  *(void **)node = ENCODE_ADDRESS(new_node);
  new_node->attributes = collect_attributes(node->attributes);
  new_node->rev_no = node->rev_no;
  new_node->data =
    collect_unordered_table_data(
      node->data, node->rev_no, (REFERRED_REVISION *)&node->rev_no);
  return new_node;
}
static void entry__insert_item_1(void) {
  if (argument_count != 5) {
    invalid_arguments_error();
    return;
  }

  UNORDERED_TABLE *myself = (UNORDERED_TABLE *)arguments->slots[0];
  uint32_t hash = to_uint32(arguments->slots[1]);
  NODE *cmp_key = arguments->slots[2]; // NONE or a key returned from a previous call
  NODE *key = arguments->slots[3];
  NODE *value = arguments->slots[4];

  long rev_no = myself->rev_no;
  UNORDERED_TABLE_DATA *data = myself->data;
  UNORDERED_TABLE_HASH_COLLISION **entries;
  long size;
  if (!data) { // we must allocate a data record
    size = 32; // the initial size for the table
    data = allocate(sizeof(UNORDERED_TABLE_DATA));
    // the empty table does *not* get a reference to the newly allocated data!
    data->rev_no = 0; // initial revision number is 0
    // no need to set <rev_no> - it must be 0
    data->size = size; // the maximum number of entries the table can hold without reallocation
    data->used = 0; // no entries are used yet
    data->entries = entries =
      allocate_and_clear(size*sizeof(UNORDERED_TABLE_HASH_COLLISION *));
  } else {
    size = data->size;
    entries = data->entries;
  }

  UNORDERED_TABLE_DATA *new_data = NULL;

  if (data->rev_no != rev_no) { // we must clone the table (data and entries)
    //fprintf(stderr, "clone (our rev_no: %ld; table's rev_no: %ld)\n", rev_no, data->rev_no);
    new_data = allocate(sizeof(UNORDERED_TABLE_DATA));
    new_data->rev_no = rev_no;
    new_data->size = size;
    new_data->used = data->used;
    new_data->entries =
      allocate(size*sizeof(UNORDERED_TABLE_HASH_COLLISION *));

    long idx;
    for (idx = 0; idx < size; ++idx) {
      //fprintf(stderr, "idx: %ld\n", idx);
      UNORDERED_TABLE_HASH_COLLISION *hash_collision = entries[idx];
      UNORDERED_TABLE_HASH_COLLISION *new_hash_collisions = NULL;
      UNORDERED_TABLE_HASH_COLLISION **new_hash_collisions_p =
        &new_hash_collisions;
      while (hash_collision) {
        UNORDERED_TABLE_KEY_COLLISION *key_collision =
          hash_collision->key_collisions;
        UNORDERED_TABLE_KEY_COLLISION *new_key_collisions = NULL;
        UNORDERED_TABLE_KEY_COLLISION **new_key_collisions_p =
          &new_key_collisions;
        while (key_collision) {
          UNORDERED_TABLE_REVISION *revision = key_collision->revisions;
          UNORDERED_TABLE_REVISION *new_revisions = NULL;
          UNORDERED_TABLE_REVISION **new_revision_p = &new_revisions;
          while (revision) {
            if (revision->rev_no <= rev_no) {
              UNORDERED_TABLE_REVISION *new_revision =
                allocate(sizeof(UNORDERED_TABLE_REVISION));
              new_revision->link = NULL;
              new_revision->rev_no = revision->rev_no;
              new_revision->value = revision->value;
              *new_revision_p = new_revision;
              new_revision_p = &new_revision->link;
            }
            revision = revision->link;
          }
          if (new_revisions) {
            UNORDERED_TABLE_KEY_COLLISION *new_key_collision =
              allocate(sizeof(UNORDERED_TABLE_KEY_COLLISION));
            new_key_collision->link = NULL;
            new_key_collision->key = key_collision->key;
            new_key_collision->revisions = new_revisions;
            *new_key_collisions_p = new_key_collision;
            new_key_collisions_p = &new_key_collision->link;
          }
          key_collision = key_collision->link;
        }
        if (new_key_collisions) {
          UNORDERED_TABLE_HASH_COLLISION *new_hash_collision =
            allocate(sizeof(UNORDERED_TABLE_HASH_COLLISION));
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

  UNORDERED_TABLE_HASH_COLLISION *hash_collision = entries[idx];
  while (hash_collision) {
    if (hash_collision->hash == hash) goto found_identical_hash;
    hash_collision = hash_collision->link;
  }
  //fprintf(stderr, "create new hash collision entry\n");
  hash_collision = allocate(sizeof(UNORDERED_TABLE_HASH_COLLISION));
  hash_collision->link = entries[idx];
  hash_collision->hash = hash;
  hash_collision->key_collisions = NULL;
  entries[idx] = hash_collision;

  found_identical_hash:;

  //fprintf(stderr, "key: %p\n", key);
  //fprintf(stderr, "cmp_key: %p\n", cmp_key);

  UNORDERED_TABLE_KEY_COLLISION *key_collision = hash_collision->key_collisions;

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
  key_collision = allocate(sizeof(UNORDERED_TABLE_KEY_COLLISION));
  key_collision->link = hash_collision->key_collisions;
  key_collision->key = key;
  key_collision->revisions = NULL;
  hash_collision->key_collisions = key_collision;

  insert_new_revision:;

  //fprintf(stderr, "create new revision entry\n");

  ++rev_no;

  UNORDERED_TABLE_REVISION *revision = allocate(sizeof(UNORDERED_TABLE_REVISION));
  revision->link = key_collision->revisions;
  revision->rev_no = rev_no;
  revision->value = value;
  key_collision->revisions = revision;

  data->rev_no = rev_no;

  update_myself:;

  NODE *new_table = create__types__unordered_table(rev_no, data);
  new_table->type = myself->type;
  new_table->attributes = myself->attributes;
  myself = (UNORDERED_TABLE *)new_table;

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
static void entry__retrieve_item_1(void) {
  if (argument_count != 3) {
    invalid_arguments_error();
    return;
  }

  UNORDERED_TABLE *myself = (UNORDERED_TABLE *)arguments->slots[0];
  uint32_t hash = to_uint32(arguments->slots[1]);
  NODE *cmp_key = arguments->slots[2];

  long rev_no = myself->rev_no;
  UNORDERED_TABLE_DATA *data = myself->data;

  NODE *key_node = var._NONE;
  NODE *value_node = undefined;
  if (!data) goto leave;

  long size = data->size;
  UNORDERED_TABLE_HASH_COLLISION **entries = data->entries;

  long idx = hash % size;
  //fprintf(stderr, "idx: %ld\n", idx);

  UNORDERED_TABLE_HASH_COLLISION *hash_collision = entries[idx];
  while (hash_collision) {
    if (hash_collision->hash == hash) goto found_identical_hash;
    hash_collision = hash_collision->link;
  }
  goto leave;

  found_identical_hash:;

  //fprintf(stderr, "found identical hash\n");
  UNORDERED_TABLE_KEY_COLLISION *key_collision = hash_collision->key_collisions;

  if (cmp_key == var._NONE) {
    if (key_collision) goto found_matching_key;
    goto leave;
  }

  while (key_collision) {
    if (key_collision->key == cmp_key) {
      if (key_collision->link) {
        // let the caller check the next key

        key_node = key_collision->link->key;
        value_node = key_collision->link->revisions->value;
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

  UNORDERED_TABLE_REVISION *revision = key_collision->revisions;
  while (revision && revision->rev_no > rev_no) {
    revision = revision->link;
  }

  if (revision) {
    value_node = key_collision->revisions->value;
  }

  leave:;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = key_node;
  arguments->slots[1] = value_node;
  {
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}

static VTABLE vtable__types__unordered_table = {
  sizeof(UNORDERED_TABLE),
  (COLLECTOR *)&collect_unordered_table,
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
  &func__types__unordered_table___debug_string
};

static ATTRIBUTES attributes__types__unordered_table = {
  &vtable__types__unordered_table,
  {
    &undefined_attributes_level_1, &undefined_attributes_level_2,
    &undefined_attributes_level_3, &undefined_attributes_level_4,
    &undefined_attributes_level_5, &undefined_attributes_level_6,
    &undefined_attributes_level_7
  }
};

static void type__types__unordered_table(void) {
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  {
    NODE *result__node = (NODE *)(create__types__unordered_table(0, NULL));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static NODE *create__types__unordered_table(long rev_no, UNORDERED_TABLE_DATA *data) {
  NODE *node = allocate(sizeof(UNORDERED_TABLE));
  node->type = type__types__unordered_table;
  node->attributes = &attributes__types__unordered_table;
  node->unordered_table.rev_no = rev_no;
  node->unordered_table.data = data;
  return node;
}
static void entry__types__unordered_table__length_of_1(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }

  UNORDERED_TABLE *myself = (UNORDERED_TABLE *)arguments->slots[0];

  long len = 0;

  UNORDERED_TABLE_DATA *data = myself->data;

  if (data) {
    long rev_no = data->rev_no;
    UNORDERED_TABLE_HASH_COLLISION **entries = data->entries;
    long size = data->size;
    long idx;
    for (idx = 0; idx < size; ++idx) {
      UNORDERED_TABLE_HASH_COLLISION *hash_collision = entries[idx];
      while (hash_collision) {
        UNORDERED_TABLE_KEY_COLLISION *key_collision =
          hash_collision->key_collisions;
        while (key_collision) {
          UNORDERED_TABLE_REVISION *revision = key_collision->revisions;
          while (revision) {
            if (revision->rev_no <= rev_no) {
            if (revision->value != undefined) ++len;
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
static void entry__next_key_and_value_1(void) {
  if (argument_count != 3) {
    invalid_arguments_error();
    return;
  }
  UNORDERED_TABLE *myself = (UNORDERED_TABLE *)arguments->slots[0];
  uint32_t hash = to_uint32(arguments->slots[1]);
  NODE *cmp_key = arguments->slots[2];

  NODE *key_node = var._NONE; // default: no more key and value found
  NODE *value_node = undefined;

  UNORDERED_TABLE_DATA *data = myself->data;
  if (data) {
    long rev_no = data->rev_no;
    UNORDERED_TABLE_HASH_COLLISION **entries = data->entries;
    long size = data->size;
    long idx;
    UNORDERED_TABLE_HASH_COLLISION *hash_collision;
    UNORDERED_TABLE_KEY_COLLISION *key_collision;
    UNORDERED_TABLE_REVISION *revision;
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
                if (revision->value == undefined) goto find_next;
                key_node = key_collision->key;
                value_node = revision->value;
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
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = key_node;
  arguments->slots[1] = value_node;
  {
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__previous_key_and_value_1(void) {
  if (argument_count != 3) {
    invalid_arguments_error();
    return;
  }
  UNORDERED_TABLE *myself = (UNORDERED_TABLE *)arguments->slots[0];
  uint32_t hash = to_uint32(arguments->slots[1]);
  NODE *cmp_key = arguments->slots[2];

  NODE *key_node = var._NONE; // default: no more key and value found
  NODE *value_node = undefined;

  UNORDERED_TABLE_DATA *data = myself->data;
  if (data) {
    long rev_no = data->rev_no;
    UNORDERED_TABLE_HASH_COLLISION **entries = data->entries;
    long size = data->size;
    long idx;
    UNORDERED_TABLE_HASH_COLLISION *hash_collision;
    UNORDERED_TABLE_KEY_COLLISION *key_collision;
    UNORDERED_TABLE_REVISION *revision;
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
              if (revision->value == undefined) goto skip;
              if (key_collision->key == cmp_key) {
                if (key_node != var._NONE) goto leave;
                cmp_key = var._NONE;
                goto find_previous;
              }
              key_node = key_collision->key;
              value_node = revision->value;
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
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = key_node;
  arguments->slots[1] = value_node;
  {
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__types__unordered_table__private__set_item_1(void) {
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
  // 817: ... key.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* key */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__types__unordered_table__private__set_item_2;
}
static void cont__types__unordered_table__private__set_item_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 817: ... : !key undefined
  frame->slots[7] /* temp__2 */ = create_closure(entry__types__unordered_table__private__set_item_3, 0);
  // 817: if key.is_undefined: !key undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__unordered_table__private__set_item_4;
}
static void entry__types__unordered_table__private__set_item_3(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // key: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* key */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 817: ... !key undefined
  ((CELL *)frame->slots[0])->contents /* key */ = get__undefined();
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__types__unordered_table__private__set_item_4(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 818: $h hash(key)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* key */;
  result_count = 1;
  myself = get__hash();
  func = myself->type;
  frame->cont = cont__types__unordered_table__private__set_item_5;
}
static void cont__types__unordered_table__private__set_item_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* h */, arguments->slots[0]);
  // 825: $$cmp_key NONE
  // 826:   #
  // 827:     start looking for possibly matching keys at the first key with
  // 828:     identical hash
  ((CELL *)frame->slots[5])->contents /* cmp_key */ = var._NONE;
  // 830: ... :
  // 831:   insert_item &self h &cmp_key key value
  // 832:   if cmp_key == NONE: return self
  // 833:   if cmp_key .equal_type_and_value. key:
  // 834:     !key cmp_key # force the use of the already stored (and equal) key
  frame->slots[6] /* temp__1 */ = create_closure(entry__types__unordered_table__private__set_item_6, 0);
  // 830: forever:
  // 831:   insert_item &self h &cmp_key key value
  // 832:   if cmp_key == NONE: return self
  // 833:   if cmp_key .equal_type_and_value. key:
  // 834:     !key cmp_key # force the use of the already stored (and equal) key
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__forever();
  func = myself->type;
  frame->cont = cont__types__unordered_table__private__set_item_13;
}
static void entry__types__unordered_table__private__set_item_12(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // key: 0
  // cmp_key: 1
  frame->slots[0] = myself->closure.frame->slots[3]; /* key */
  frame->slots[1] = myself->closure.frame->slots[2]; /* cmp_key */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 834: !key cmp_key # force the use of the already stored (and equal) key
  ((CELL *)frame->slots[0])->contents /* key */ = ((CELL *)frame->slots[1])->contents /* cmp_key */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__unordered_table__private__set_item_6(void) {
  allocate_initialized_frame_gc(6, 8);
  // slot allocations:
  // self: 0
  // h: 1
  // cmp_key: 2
  // key: 3
  // value: 4
  // return: 5
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  frame->slots[1] = myself->closure.frame->slots[4]; /* h */
  frame->slots[2] = myself->closure.frame->slots[5]; /* cmp_key */
  frame->slots[3] = myself->closure.frame->slots[1]; /* key */
  frame->slots[4] = myself->closure.frame->slots[2]; /* value */
  frame->slots[5] = myself->closure.frame->slots[3]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 831: insert_item &self h &cmp_key key value
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  arguments->slots[1] = frame->slots[1] /* h */;
  arguments->slots[2] = ((CELL *)frame->slots[2])->contents /* cmp_key */;
  arguments->slots[3] = ((CELL *)frame->slots[3])->contents /* key */;
  arguments->slots[4] = frame->slots[4] /* value */;
  result_count = 2;
  myself = var._insert_item;
  func = myself->type;
  frame->cont = cont__types__unordered_table__private__set_item_7;
}
static void cont__types__unordered_table__private__set_item_7(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* self */ = arguments->slots[0];
  ((CELL *)frame->slots[2])->contents /* cmp_key */ = arguments->slots[1];
  // 832: ... cmp_key == NONE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* cmp_key */;
  arguments->slots[1] = var._NONE;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__types__unordered_table__private__set_item_8;
}
static void cont__types__unordered_table__private__set_item_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 832: ... : return self
  frame->slots[7] /* temp__2 */ = create_closure(entry__types__unordered_table__private__set_item_9, 0);
  // 832: if cmp_key == NONE: return self
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__unordered_table__private__set_item_10;
}
static void entry__types__unordered_table__private__set_item_9(void) {
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
  // 832: ... return self
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* self */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__unordered_table__private__set_item_10(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 833: ... cmp_key .equal_type_and_value. key
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* cmp_key */;
  arguments->slots[1] = ((CELL *)frame->slots[3])->contents /* key */;
  result_count = 1;
  myself = get__equal_type_and_value();
  func = myself->type;
  frame->cont = cont__types__unordered_table__private__set_item_11;
}
static void cont__types__unordered_table__private__set_item_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 833: ... :
  // 834:   !key cmp_key # force the use of the already stored (and equal) key
  frame->slots[7] /* temp__2 */ = create_closure(entry__types__unordered_table__private__set_item_12, 0);
  // 833: if cmp_key .equal_type_and_value. key:
  // 834:   !key cmp_key # force the use of the already stored (and equal) key
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__unordered_table__private__set_item_13(void) {
  myself = frame->slots[3] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__types__unordered_table__private__get_item_1(void) {
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
  // 844: $h hash(key)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* key */;
  result_count = 1;
  myself = get__hash();
  func = myself->type;
  frame->cont = cont__types__unordered_table__private__get_item_2;
}
static void cont__types__unordered_table__private__get_item_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* h */, arguments->slots[0]);
  // 851: $$cmp_key NONE
  // 852:   #
  // 853:     start the search with the first key with a matching hash value
  ((CELL *)frame->slots[4])->contents /* cmp_key */ = var._NONE;
  // 855: ... :
  // 856:   retrieve_item self h &cmp_key $retrieved_value
  // 857:   
  // 858:   #ewriteln "___"
  // 859:   #edump `cmp_key `retrieved_value
  // 860:   
  // 861:   if cmp_key == NONE || cmp_key .equal_type_and_value. key:
  // 862:     return retrieved_value
  // 863:   
  // 864:   #
  // ...
  frame->slots[5] /* temp__1 */ = create_closure(entry__types__unordered_table__private__get_item_3, 0);
  // 855: forever:
  // 856:   retrieve_item self h &cmp_key $retrieved_value
  // 857:   
  // 858:   #ewriteln "___"
  // 859:   #edump `cmp_key `retrieved_value
  // 860:   
  // 861:   if cmp_key == NONE || cmp_key .equal_type_and_value. key:
  // 862:     return retrieved_value
  // 863:   
  // 864:   #
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__forever();
  func = myself->type;
  frame->cont = cont__types__unordered_table__private__get_item_10;
}
static void entry__types__unordered_table__private__get_item_9(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // return: 0
  // retrieved_value: 1
  frame->slots[0] = myself->closure.frame->slots[4]; /* return */
  frame->slots[1] = myself->closure.frame->slots[5]; /* retrieved_value */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 862: return retrieved_value
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* retrieved_value */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__unordered_table__private__get_item_3(void) {
  allocate_initialized_frame_gc(5, 10);
  // slot allocations:
  // self: 0
  // h: 1
  // cmp_key: 2
  // key: 3
  // return: 4
  // retrieved_value: 5
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  frame->slots[1] = myself->closure.frame->slots[3]; /* h */
  frame->slots[2] = myself->closure.frame->slots[4]; /* cmp_key */
  frame->slots[3] = myself->closure.frame->slots[1]; /* key */
  frame->slots[4] = myself->closure.frame->slots[2]; /* return */
  frame->slots[5] /* retrieved_value */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 856: retrieve_item self h &cmp_key $retrieved_value
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  arguments->slots[1] = frame->slots[1] /* h */;
  arguments->slots[2] = ((CELL *)frame->slots[2])->contents /* cmp_key */;
  result_count = 2;
  myself = var._retrieve_item;
  func = myself->type;
  frame->cont = cont__types__unordered_table__private__get_item_4;
}
static void cont__types__unordered_table__private__get_item_4(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* cmp_key */ = arguments->slots[0];
  initialize_future(frame->slots[5] /* retrieved_value */, arguments->slots[1]);
  // 861: ... cmp_key == NONE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* cmp_key */;
  arguments->slots[1] = var._NONE;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__types__unordered_table__private__get_item_5;
}
static void cont__types__unordered_table__private__get_item_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 861: ... cmp_key .equal_type_and_value. key
  frame->slots[8] /* temp__3 */ = create_closure(entry__types__unordered_table__private__get_item_6, 0);
  // 861: ... cmp_key == NONE || cmp_key .equal_type_and_value. key
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__2 */;
  arguments->slots[1] = frame->slots[8] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__types__unordered_table__private__get_item_8;
}
static void entry__types__unordered_table__private__get_item_6(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // cmp_key: 0
  // key: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* cmp_key */
  frame->slots[1] = myself->closure.frame->slots[3]; /* key */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 861: ... cmp_key .equal_type_and_value. key
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* cmp_key */;
  arguments->slots[1] = frame->slots[1] /* key */;
  result_count = 1;
  myself = get__equal_type_and_value();
  func = myself->type;
  frame->cont = cont__types__unordered_table__private__get_item_7;
}
static void cont__types__unordered_table__private__get_item_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 861: ... cmp_key .equal_type_and_value. key
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__types__unordered_table__private__get_item_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 861: ... :
  // 862:   return retrieved_value
  frame->slots[9] /* temp__4 */ = create_closure(entry__types__unordered_table__private__get_item_9, 0);
  // 861: if cmp_key == NONE || cmp_key .equal_type_and_value. key:
  // 862:   return retrieved_value
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[9] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__unordered_table__private__get_item_10(void) {
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__types__unordered_table_3(void) {
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
  // 886: private::get_item myself key
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* myself */;
  arguments->slots[1] = frame->slots[1] /* key */;
  result_count = frame->caller_result_count;
  myself = get__private__get_item();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__unordered_table_4(void) {
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
  // 888: private::set_item myself key value
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
static void entry__types__unordered_table_1(void) {
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
  // 885: NONE == value
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._NONE;
  arguments->slots[1] = frame->slots[1] /* value */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__types__unordered_table_2;
}
static void cont__types__unordered_table_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 885: ... :
  // 886:   private::get_item myself key
  frame->slots[4] /* temp__2 */ = create_closure(entry__types__unordered_table_3, 0);
  // 887: :
  // 888:   private::set_item myself key value
  frame->slots[5] /* temp__3 */ = create_closure(entry__types__unordered_table_4, 0);
  // 884: if
  // 885:   NONE == value:
  // 886:     private::get_item myself key
  // 887:   :
  // 888:     private::set_item myself key value
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
static void entry__types__unordered_table__new_empty_collection_1(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // self: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 900: -> types::unordered_table
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var.types__unordered_table;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__unordered_table_1(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // initializers: 0
  // tab: 1
  frame->slots[1] /* tab */ = create_cell();
  frame->slots[0] /* initializers */ = from_arguments(0, argument_count-0);
  // 919: $$tab types::unordered_table
  ((CELL *)frame->slots[1])->contents /* tab */ = var.types__unordered_table;
  // 920: ... : (initializer)
  // 921:   !tab(std::key_of(initializer)) std::value_of(initializer)
  frame->slots[2] /* temp__1 */ = create_closure(entry__std__unordered_table_2, 1);
  // 920: for_each initializers: (initializer)
  // 921:   !tab(std::key_of(initializer)) std::value_of(initializer)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* initializers */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__std__unordered_table_6;
}
static void entry__std__unordered_table_2(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // initializer: 0
  // tab: 1
  frame->slots[1] = myself->closure.frame->slots[1]; /* tab */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 921: !tab(std::key_of(initializer)) std::value_of(initializer)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* initializer */;
  result_count = 1;
  myself = get__std__value_of();
  func = myself->type;
  frame->cont = cont__std__unordered_table_3;
}
static void cont__std__unordered_table_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 921: ... std::key_of(initializer)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* initializer */;
  result_count = 1;
  myself = get__std__key_of();
  func = myself->type;
  frame->cont = cont__std__unordered_table_4;
}
static void cont__std__unordered_table_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 921: !tab(std::key_of(initializer))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[1])->contents /* tab */;
  func = myself->type;
  frame->cont = cont__std__unordered_table_5;
}
static void cont__std__unordered_table_5(void) {
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
static void cont__std__unordered_table_6(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 922: -> tab
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* tab */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__unordered_table__for_each_1(void) {
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
  // 937: $$key NONE
  ((CELL *)frame->slots[3])->contents /* key */ = var._NONE;
  // 938: ... :
  // 939:   next_key_and_value self hash(key) &key $value
  // 940:   if key == NONE return
  // 941:   if
  // 942:     parameter_count_of(body) == 2:
  // 943:       body key value
  // 944:     :
  // 945:       body value
  frame->slots[4] /* temp__1 */ = create_closure(entry__types__unordered_table__for_each_2, 0);
  // 938: forever:
  // 939:   next_key_and_value self hash(key) &key $value
  // 940:   if key == NONE return
  // 941:   if
  // 942:     parameter_count_of(body) == 2:
  // 943:       body key value
  // 944:     :
  // 945:       body value
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__forever();
  func = myself->type;
  frame->cont = cont__types__unordered_table__for_each_11;
}
static void entry__types__unordered_table__for_each_9(void) {
  allocate_initialized_frame_gc(3, 3);
  // slot allocations:
  // body: 0
  // key: 1
  // value: 2
  frame->slots[0] = myself->closure.frame->slots[3]; /* body */
  frame->slots[1] = myself->closure.frame->slots[1]; /* key */
  frame->slots[2] = myself->closure.frame->slots[4]; /* value */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 943: body key value
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* key */;
  arguments->slots[1] = frame->slots[2] /* value */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__unordered_table__for_each_10(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // body: 0
  // value: 1
  frame->slots[0] = myself->closure.frame->slots[3]; /* body */
  frame->slots[1] = myself->closure.frame->slots[4]; /* value */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 945: body value
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* value */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__unordered_table__for_each_2(void) {
  allocate_initialized_frame_gc(4, 9);
  // slot allocations:
  // self: 0
  // key: 1
  // return: 2
  // body: 3
  // value: 4
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  frame->slots[1] = myself->closure.frame->slots[3]; /* key */
  frame->slots[2] = myself->closure.frame->slots[2]; /* return */
  frame->slots[3] = myself->closure.frame->slots[1]; /* body */
  frame->slots[4] /* value */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 939: ... hash(key)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* key */;
  result_count = 1;
  myself = get__hash();
  func = myself->type;
  frame->cont = cont__types__unordered_table__for_each_3;
}
static void cont__types__unordered_table__for_each_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 939: next_key_and_value self hash(key) &key $value
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  arguments->slots[2] = ((CELL *)frame->slots[1])->contents /* key */;
  result_count = 2;
  myself = var._next_key_and_value;
  func = myself->type;
  frame->cont = cont__types__unordered_table__for_each_4;
}
static void cont__types__unordered_table__for_each_4(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* key */ = arguments->slots[0];
  initialize_future(frame->slots[4] /* value */, arguments->slots[1]);
  // 940: ... key == NONE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* key */;
  arguments->slots[1] = var._NONE;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__types__unordered_table__for_each_5;
}
static void cont__types__unordered_table__for_each_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 940: if key == NONE return
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* return */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__unordered_table__for_each_6;
}
static void cont__types__unordered_table__for_each_6(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 942: parameter_count_of(body)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* body */;
  result_count = 1;
  myself = get__parameter_count_of();
  func = myself->type;
  frame->cont = cont__types__unordered_table__for_each_7;
}
static void cont__types__unordered_table__for_each_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 942: parameter_count_of(body) == 2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__types__unordered_table__for_each_8;
}
static void cont__types__unordered_table__for_each_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 942: ... :
  // 943:   body key value
  frame->slots[7] /* temp__3 */ = create_closure(entry__types__unordered_table__for_each_9, 0);
  // 944: :
  // 945:   body value
  frame->slots[8] /* temp__4 */ = create_closure(entry__types__unordered_table__for_each_10, 0);
  // 941: if
  // 942:   parameter_count_of(body) == 2:
  // 943:     body key value
  // 944:   :
  // 945:     body value
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
static void cont__types__unordered_table__for_each_11(void) {
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__types__unordered_table__for_each_from_to_1(void) {
  allocate_initialized_frame_gc(5, 9);
  // slot allocations:
  // self: 0
  // first: 1
  // last: 2
  // body: 3
  // return: 4
  // key: 5
  // value: 6
  // h: 7
  frame->slots[4] /* return */ = create_continuation();
  frame->slots[5] /* key */ = create_cell();
  frame->slots[6] /* value */ = create_cell();
  frame->slots[7] /* h */ = create_future();
  if (argument_count != 4) {
    invalid_arguments_error();
    return;
  }
  // 961: $$key first
  ((CELL *)frame->slots[5])->contents /* key */ = frame->slots[1] /* first */;
  // 962: $$value undefined
  ((CELL *)frame->slots[6])->contents /* value */ = get__undefined();
  // 963: $h hash(key)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[5])->contents /* key */;
  result_count = 1;
  myself = get__hash();
  func = myself->type;
  frame->cont = cont__types__unordered_table__for_each_from_to_2;
}
static void cont__types__unordered_table__for_each_from_to_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[7] /* h */, arguments->slots[0]);
  // 964: retrieve_item self h &key !value
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  arguments->slots[1] = frame->slots[7] /* h */;
  arguments->slots[2] = ((CELL *)frame->slots[5])->contents /* key */;
  result_count = 2;
  myself = var._retrieve_item;
  func = myself->type;
  frame->cont = cont__types__unordered_table__for_each_from_to_3;
}
static void cont__types__unordered_table__for_each_from_to_3(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[5])->contents /* key */ = arguments->slots[0];
  ((CELL *)frame->slots[6])->contents /* value */ = arguments->slots[1];
  // 965: ... key == NONE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[5])->contents /* key */;
  arguments->slots[1] = var._NONE;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__types__unordered_table__for_each_from_to_4;
}
static void cont__types__unordered_table__for_each_from_to_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__1 */ = arguments->slots[0];
  // 965: if key == NONE: Error "Invalid index error!"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__1 */;
  arguments->slots[1] = func__types__unordered_table__for_each_from_to_5;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__unordered_table__for_each_from_to_7;
}
static void entry__types__unordered_table__for_each_from_to_5(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 965: ... Error "Invalid index error!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__2bdb69f58c8fd6ea;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__unordered_table__for_each_from_to_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 966: ... :
  // 967:   if
  // 968:     parameter_count_of(body) == 2:
  // 969:       body key value
  // 970:     :
  // 971:       body value
  // 972:   if key == last return
  // 973:   next_key_and_value self hash(key) &key !value
  // 974:   if key == NONE return
  frame->slots[8] /* temp__1 */ = create_closure(entry__types__unordered_table__for_each_from_to_8, 0);
  // 966: forever:
  // 967:   if
  // 968:     parameter_count_of(body) == 2:
  // 969:       body key value
  // 970:     :
  // 971:       body value
  // 972:   if key == last return
  // 973:   next_key_and_value self hash(key) &key !value
  // 974:   if key == NONE return
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__forever();
  func = myself->type;
  frame->cont = cont__types__unordered_table__for_each_from_to_19;
}
static void entry__types__unordered_table__for_each_from_to_8(void) {
  allocate_initialized_frame_gc(6, 10);
  // slot allocations:
  // body: 0
  // key: 1
  // value: 2
  // last: 3
  // return: 4
  // self: 5
  frame->slots[0] = myself->closure.frame->slots[3]; /* body */
  frame->slots[1] = myself->closure.frame->slots[5]; /* key */
  frame->slots[2] = myself->closure.frame->slots[6]; /* value */
  frame->slots[3] = myself->closure.frame->slots[2]; /* last */
  frame->slots[4] = myself->closure.frame->slots[4]; /* return */
  frame->slots[5] = myself->closure.frame->slots[0]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 968: parameter_count_of(body)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* body */;
  result_count = 1;
  myself = get__parameter_count_of();
  func = myself->type;
  frame->cont = cont__types__unordered_table__for_each_from_to_9;
}
static void cont__types__unordered_table__for_each_from_to_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 968: parameter_count_of(body) == 2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__2 */;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__types__unordered_table__for_each_from_to_10;
}
static void cont__types__unordered_table__for_each_from_to_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 968: ... :
  // 969:   body key value
  frame->slots[8] /* temp__3 */ = create_closure(entry__types__unordered_table__for_each_from_to_11, 0);
  // 970: :
  // 971:   body value
  frame->slots[9] /* temp__4 */ = create_closure(entry__types__unordered_table__for_each_from_to_12, 0);
  // 967: if
  // 968:   parameter_count_of(body) == 2:
  // 969:     body key value
  // 970:   :
  // 971:     body value
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__3 */;
  arguments->slots[2] = frame->slots[9] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__unordered_table__for_each_from_to_13;
}
static void entry__types__unordered_table__for_each_from_to_11(void) {
  allocate_initialized_frame_gc(3, 3);
  // slot allocations:
  // body: 0
  // key: 1
  // value: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* body */
  frame->slots[1] = myself->closure.frame->slots[1]; /* key */
  frame->slots[2] = myself->closure.frame->slots[2]; /* value */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 969: body key value
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* key */;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* value */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__unordered_table__for_each_from_to_12(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // body: 0
  // value: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* body */
  frame->slots[1] = myself->closure.frame->slots[2]; /* value */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 971: body value
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* value */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__unordered_table__for_each_from_to_13(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 972: ... key == last
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* key */;
  arguments->slots[1] = frame->slots[3] /* last */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__types__unordered_table__for_each_from_to_14;
}
static void cont__types__unordered_table__for_each_from_to_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 972: if key == last return
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* return */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__unordered_table__for_each_from_to_15;
}
static void cont__types__unordered_table__for_each_from_to_15(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 973: ... hash(key)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* key */;
  result_count = 1;
  myself = get__hash();
  func = myself->type;
  frame->cont = cont__types__unordered_table__for_each_from_to_16;
}
static void cont__types__unordered_table__for_each_from_to_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 973: next_key_and_value self hash(key) &key !value
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* self */;
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  arguments->slots[2] = ((CELL *)frame->slots[1])->contents /* key */;
  result_count = 2;
  myself = var._next_key_and_value;
  func = myself->type;
  frame->cont = cont__types__unordered_table__for_each_from_to_17;
}
static void cont__types__unordered_table__for_each_from_to_17(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* key */ = arguments->slots[0];
  ((CELL *)frame->slots[2])->contents /* value */ = arguments->slots[1];
  // 974: ... key == NONE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* key */;
  arguments->slots[1] = var._NONE;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__types__unordered_table__for_each_from_to_18;
}
static void cont__types__unordered_table__for_each_from_to_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 974: if key == NONE return
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* return */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__unordered_table__for_each_from_to_19(void) {
  myself = frame->slots[4] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__types__unordered_table__for_each_downwards_1(void) {
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
  // 989: $$key NONE
  ((CELL *)frame->slots[3])->contents /* key */ = var._NONE;
  // 990: ... :
  // 991:   previous_key_and_value self hash(key) &key $value
  // 992:   if key == NONE return
  // 993:   if
  // 994:     parameter_count_of(body) == 2:
  // 995:       body key value
  // 996:     :
  // 997:       body value
  frame->slots[4] /* temp__1 */ = create_closure(entry__types__unordered_table__for_each_downwards_2, 0);
  // 990: forever:
  // 991:   previous_key_and_value self hash(key) &key $value
  // 992:   if key == NONE return
  // 993:   if
  // 994:     parameter_count_of(body) == 2:
  // 995:       body key value
  // 996:     :
  // 997:       body value
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__forever();
  func = myself->type;
  frame->cont = cont__types__unordered_table__for_each_downwards_11;
}
static void entry__types__unordered_table__for_each_downwards_9(void) {
  allocate_initialized_frame_gc(3, 3);
  // slot allocations:
  // body: 0
  // key: 1
  // value: 2
  frame->slots[0] = myself->closure.frame->slots[3]; /* body */
  frame->slots[1] = myself->closure.frame->slots[1]; /* key */
  frame->slots[2] = myself->closure.frame->slots[4]; /* value */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 995: body key value
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* key */;
  arguments->slots[1] = frame->slots[2] /* value */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__unordered_table__for_each_downwards_10(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // body: 0
  // value: 1
  frame->slots[0] = myself->closure.frame->slots[3]; /* body */
  frame->slots[1] = myself->closure.frame->slots[4]; /* value */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 997: body value
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* value */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__unordered_table__for_each_downwards_2(void) {
  allocate_initialized_frame_gc(4, 9);
  // slot allocations:
  // self: 0
  // key: 1
  // return: 2
  // body: 3
  // value: 4
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  frame->slots[1] = myself->closure.frame->slots[3]; /* key */
  frame->slots[2] = myself->closure.frame->slots[2]; /* return */
  frame->slots[3] = myself->closure.frame->slots[1]; /* body */
  frame->slots[4] /* value */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 991: ... hash(key)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* key */;
  result_count = 1;
  myself = get__hash();
  func = myself->type;
  frame->cont = cont__types__unordered_table__for_each_downwards_3;
}
static void cont__types__unordered_table__for_each_downwards_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 991: previous_key_and_value self hash(key) &key $value
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  arguments->slots[2] = ((CELL *)frame->slots[1])->contents /* key */;
  result_count = 2;
  myself = var._previous_key_and_value;
  func = myself->type;
  frame->cont = cont__types__unordered_table__for_each_downwards_4;
}
static void cont__types__unordered_table__for_each_downwards_4(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* key */ = arguments->slots[0];
  initialize_future(frame->slots[4] /* value */, arguments->slots[1]);
  // 992: ... key == NONE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* key */;
  arguments->slots[1] = var._NONE;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__types__unordered_table__for_each_downwards_5;
}
static void cont__types__unordered_table__for_each_downwards_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 992: if key == NONE return
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* return */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__unordered_table__for_each_downwards_6;
}
static void cont__types__unordered_table__for_each_downwards_6(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 994: parameter_count_of(body)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* body */;
  result_count = 1;
  myself = get__parameter_count_of();
  func = myself->type;
  frame->cont = cont__types__unordered_table__for_each_downwards_7;
}
static void cont__types__unordered_table__for_each_downwards_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 994: parameter_count_of(body) == 2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__types__unordered_table__for_each_downwards_8;
}
static void cont__types__unordered_table__for_each_downwards_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 994: ... :
  // 995:   body key value
  frame->slots[7] /* temp__3 */ = create_closure(entry__types__unordered_table__for_each_downwards_9, 0);
  // 996: :
  // 997:   body value
  frame->slots[8] /* temp__4 */ = create_closure(entry__types__unordered_table__for_each_downwards_10, 0);
  // 993: if
  // 994:   parameter_count_of(body) == 2:
  // 995:     body key value
  // 996:   :
  // 997:     body value
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
static void cont__types__unordered_table__for_each_downwards_11(void) {
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__types__unordered_table__for_each_from_down_to_1(void) {
  allocate_initialized_frame_gc(5, 9);
  // slot allocations:
  // self: 0
  // last: 1
  // first: 2
  // body: 3
  // return: 4
  // key: 5
  // value: 6
  // h: 7
  frame->slots[4] /* return */ = create_continuation();
  frame->slots[5] /* key */ = create_cell();
  frame->slots[6] /* value */ = create_cell();
  frame->slots[7] /* h */ = create_future();
  if (argument_count != 4) {
    invalid_arguments_error();
    return;
  }
  // 1013: $$key last
  ((CELL *)frame->slots[5])->contents /* key */ = frame->slots[1] /* last */;
  // 1014: $$value undefined
  ((CELL *)frame->slots[6])->contents /* value */ = get__undefined();
  // 1015: $h hash(key)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[5])->contents /* key */;
  result_count = 1;
  myself = get__hash();
  func = myself->type;
  frame->cont = cont__types__unordered_table__for_each_from_down_to_2;
}
static void cont__types__unordered_table__for_each_from_down_to_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[7] /* h */, arguments->slots[0]);
  // 1016: retrieve_item self h &key !value
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  arguments->slots[1] = frame->slots[7] /* h */;
  arguments->slots[2] = ((CELL *)frame->slots[5])->contents /* key */;
  result_count = 2;
  myself = var._retrieve_item;
  func = myself->type;
  frame->cont = cont__types__unordered_table__for_each_from_down_to_3;
}
static void cont__types__unordered_table__for_each_from_down_to_3(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[5])->contents /* key */ = arguments->slots[0];
  ((CELL *)frame->slots[6])->contents /* value */ = arguments->slots[1];
  // 1017: ... key == NONE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[5])->contents /* key */;
  arguments->slots[1] = var._NONE;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__types__unordered_table__for_each_from_down_to_4;
}
static void cont__types__unordered_table__for_each_from_down_to_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__1 */ = arguments->slots[0];
  // 1017: if key == NONE: Error "Invalid index error!"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__1 */;
  arguments->slots[1] = func__types__unordered_table__for_each_from_down_to_5;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__unordered_table__for_each_from_down_to_6;
}
static void entry__types__unordered_table__for_each_from_down_to_5(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1017: ... Error "Invalid index error!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__2bdb69f58c8fd6ea;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__unordered_table__for_each_from_down_to_6(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1018: ... :
  // 1019:   if
  // 1020:     parameter_count_of(body) == 2:
  // 1021:       body key value
  // 1022:     :
  // 1023:       body value
  // 1024:   if key == first return
  // 1025:   previous_key_and_value self hash(key) &key !value
  // 1026:   if key == NONE return
  frame->slots[8] /* temp__1 */ = create_closure(entry__types__unordered_table__for_each_from_down_to_7, 0);
  // 1018: forever:
  // 1019:   if
  // 1020:     parameter_count_of(body) == 2:
  // 1021:       body key value
  // 1022:     :
  // 1023:       body value
  // 1024:   if key == first return
  // 1025:   previous_key_and_value self hash(key) &key !value
  // 1026:   if key == NONE return
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__forever();
  func = myself->type;
  frame->cont = cont__types__unordered_table__for_each_from_down_to_18;
}
static void entry__types__unordered_table__for_each_from_down_to_7(void) {
  allocate_initialized_frame_gc(6, 10);
  // slot allocations:
  // body: 0
  // key: 1
  // value: 2
  // first: 3
  // return: 4
  // self: 5
  frame->slots[0] = myself->closure.frame->slots[3]; /* body */
  frame->slots[1] = myself->closure.frame->slots[5]; /* key */
  frame->slots[2] = myself->closure.frame->slots[6]; /* value */
  frame->slots[3] = myself->closure.frame->slots[2]; /* first */
  frame->slots[4] = myself->closure.frame->slots[4]; /* return */
  frame->slots[5] = myself->closure.frame->slots[0]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1020: parameter_count_of(body)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* body */;
  result_count = 1;
  myself = get__parameter_count_of();
  func = myself->type;
  frame->cont = cont__types__unordered_table__for_each_from_down_to_8;
}
static void cont__types__unordered_table__for_each_from_down_to_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 1020: parameter_count_of(body) == 2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__2 */;
  arguments->slots[1] = number__2;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__types__unordered_table__for_each_from_down_to_9;
}
static void cont__types__unordered_table__for_each_from_down_to_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 1020: ... :
  // 1021:   body key value
  frame->slots[8] /* temp__3 */ = create_closure(entry__types__unordered_table__for_each_from_down_to_10, 0);
  // 1022: :
  // 1023:   body value
  frame->slots[9] /* temp__4 */ = create_closure(entry__types__unordered_table__for_each_from_down_to_11, 0);
  // 1019: if
  // 1020:   parameter_count_of(body) == 2:
  // 1021:     body key value
  // 1022:   :
  // 1023:     body value
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__3 */;
  arguments->slots[2] = frame->slots[9] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__unordered_table__for_each_from_down_to_12;
}
static void entry__types__unordered_table__for_each_from_down_to_10(void) {
  allocate_initialized_frame_gc(3, 3);
  // slot allocations:
  // body: 0
  // key: 1
  // value: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* body */
  frame->slots[1] = myself->closure.frame->slots[1]; /* key */
  frame->slots[2] = myself->closure.frame->slots[2]; /* value */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1021: body key value
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* key */;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* value */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__unordered_table__for_each_from_down_to_11(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // body: 0
  // value: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* body */
  frame->slots[1] = myself->closure.frame->slots[2]; /* value */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1023: body value
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* value */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__unordered_table__for_each_from_down_to_12(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1024: ... key == first
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* key */;
  arguments->slots[1] = frame->slots[3] /* first */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__types__unordered_table__for_each_from_down_to_13;
}
static void cont__types__unordered_table__for_each_from_down_to_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 1024: if key == first return
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* return */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__unordered_table__for_each_from_down_to_14;
}
static void cont__types__unordered_table__for_each_from_down_to_14(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1025: ... hash(key)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* key */;
  result_count = 1;
  myself = get__hash();
  func = myself->type;
  frame->cont = cont__types__unordered_table__for_each_from_down_to_15;
}
static void cont__types__unordered_table__for_each_from_down_to_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 1025: previous_key_and_value self hash(key) &key !value
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* self */;
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  arguments->slots[2] = ((CELL *)frame->slots[1])->contents /* key */;
  result_count = 2;
  myself = var._previous_key_and_value;
  func = myself->type;
  frame->cont = cont__types__unordered_table__for_each_from_down_to_16;
}
static void cont__types__unordered_table__for_each_from_down_to_16(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* key */ = arguments->slots[0];
  ((CELL *)frame->slots[2])->contents /* value */ = arguments->slots[1];
  // 1026: ... key == NONE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* key */;
  arguments->slots[1] = var._NONE;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__types__unordered_table__for_each_from_down_to_17;
}
static void cont__types__unordered_table__for_each_from_down_to_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 1026: if key == NONE return
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* return */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__unordered_table__for_each_from_down_to_18(void) {
  myself = frame->slots[4] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__types__unordered_table__update_each_1(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // self: 0
  // body: 1
  // return: 2
  // key: 3
  frame->slots[2] /* return */ = create_continuation_with_exit(exit__types__unordered_table__update_each_1);
  frame->slots[3] /* key */ = create_cell();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* self */ = create_cell_with_contents(arguments->slots[0]);
  // 1041: $$key NONE
  ((CELL *)frame->slots[3])->contents /* key */ = var._NONE;
  // 1042: ... :
  // 1043:   next_key_and_value self hash(key) &key $$value
  // 1044:   if key == NONE return
  // 1045:   body key &value
  // 1046:   !self(key) value
  frame->slots[4] /* temp__1 */ = create_closure(entry__types__unordered_table__update_each_2, 0);
  // 1042: forever:
  // 1043:   next_key_and_value self hash(key) &key $$value
  // 1044:   if key == NONE return
  // 1045:   body key &value
  // 1046:   !self(key) value
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count =
    frame->caller_result_count >= 1 ?
    frame->caller_result_count-1 : -1;
  myself = get__forever();
  func = myself->type;
  frame->cont = cont__types__unordered_table__update_each_9;
}
static void entry__types__unordered_table__update_each_2(void) {
  allocate_initialized_frame_gc(4, 6);
  // slot allocations:
  // self: 0
  // key: 1
  // return: 2
  // body: 3
  // value: 4
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  frame->slots[1] = myself->closure.frame->slots[3]; /* key */
  frame->slots[2] = myself->closure.frame->slots[2]; /* return */
  frame->slots[3] = myself->closure.frame->slots[1]; /* body */
  frame->slots[4] /* value */ = create_cell();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1043: ... hash(key)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* key */;
  result_count = 1;
  myself = get__hash();
  func = myself->type;
  frame->cont = cont__types__unordered_table__update_each_3;
}
static void cont__types__unordered_table__update_each_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 1043: next_key_and_value self hash(key) &key $$value
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  arguments->slots[2] = ((CELL *)frame->slots[1])->contents /* key */;
  result_count = 2;
  myself = var._next_key_and_value;
  func = myself->type;
  frame->cont = cont__types__unordered_table__update_each_4;
}
static void cont__types__unordered_table__update_each_4(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* key */ = arguments->slots[0];
  ((CELL *)frame->slots[4])->contents /* value */ = arguments->slots[1];
  // 1044: ... key == NONE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* key */;
  arguments->slots[1] = var._NONE;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__types__unordered_table__update_each_5;
}
static void cont__types__unordered_table__update_each_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 1044: if key == NONE return
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* return */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__unordered_table__update_each_6;
}
static void cont__types__unordered_table__update_each_6(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1045: body key &value
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* key */;
  arguments->slots[1] = ((CELL *)frame->slots[4])->contents /* value */;
  result_count = 1;
  myself = frame->slots[3] /* body */;
  func = myself->type;
  frame->cont = cont__types__unordered_table__update_each_7;
}
static void cont__types__unordered_table__update_each_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[4])->contents /* value */ = arguments->slots[0];
  // 1046: !self(key)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* key */;
  arguments->slots[1] = ((CELL *)frame->slots[4])->contents /* value */;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* self */;
  func = myself->type;
  frame->cont = cont__types__unordered_table__update_each_8;
}
static void cont__types__unordered_table__update_each_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* self */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__types__unordered_table__update_each_9(void) {
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void exit__types__unordered_table__update_each_1(void) {
  frame = ((CONTINUATION *)myself)->exit_frame;
  int i = argument_count;
  while (--i >= 0) {
    arguments->slots[i+1] = arguments->slots[i];
  }
  argument_count += 1;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  func = continuation_type_function;
}
static void entry__types__unordered_table__update_each_from_to_1(void) {
  allocate_initialized_frame_gc(5, 9);
  // slot allocations:
  // self: 0
  // first: 1
  // last: 2
  // body: 3
  // return: 4
  // key: 5
  // value: 6
  // h: 7
  frame->slots[4] /* return */ = create_continuation_with_exit(exit__types__unordered_table__update_each_from_to_1);
  frame->slots[5] /* key */ = create_cell();
  frame->slots[6] /* value */ = create_cell();
  frame->slots[7] /* h */ = create_future();
  if (argument_count != 4) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* self */ = create_cell_with_contents(arguments->slots[0]);
  // 1062: $$key first
  ((CELL *)frame->slots[5])->contents /* key */ = frame->slots[1] /* first */;
  // 1063: $$value undefined
  ((CELL *)frame->slots[6])->contents /* value */ = get__undefined();
  // 1064: $h hash(key)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[5])->contents /* key */;
  result_count = 1;
  myself = get__hash();
  func = myself->type;
  frame->cont = cont__types__unordered_table__update_each_from_to_2;
}
static void cont__types__unordered_table__update_each_from_to_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[7] /* h */, arguments->slots[0]);
  // 1065: retrieve_item self h &key !value
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  arguments->slots[1] = frame->slots[7] /* h */;
  arguments->slots[2] = ((CELL *)frame->slots[5])->contents /* key */;
  result_count = 2;
  myself = var._retrieve_item;
  func = myself->type;
  frame->cont = cont__types__unordered_table__update_each_from_to_3;
}
static void cont__types__unordered_table__update_each_from_to_3(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[5])->contents /* key */ = arguments->slots[0];
  ((CELL *)frame->slots[6])->contents /* value */ = arguments->slots[1];
  // 1066: ... key == NONE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[5])->contents /* key */;
  arguments->slots[1] = var._NONE;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__types__unordered_table__update_each_from_to_4;
}
static void cont__types__unordered_table__update_each_from_to_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__1 */ = arguments->slots[0];
  // 1066: if key == NONE: Error "Invalid index error!"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__1 */;
  arguments->slots[1] = func__types__unordered_table__update_each_from_to_5;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__unordered_table__update_each_from_to_6;
}
static void entry__types__unordered_table__update_each_from_to_5(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1066: ... Error "Invalid index error!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__2bdb69f58c8fd6ea;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__unordered_table__update_each_from_to_6(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1067: ... :
  // 1068:   body key &value
  // 1069:   !self(key) value
  // 1070:   if key == last return
  // 1071:   next_key_and_value self hash(key) &key !value
  // 1072:   if key == NONE return
  frame->slots[8] /* temp__1 */ = create_closure(entry__types__unordered_table__update_each_from_to_7, 0);
  // 1067: forever:
  // 1068:   body key &value
  // 1069:   !self(key) value
  // 1070:   if key == last return
  // 1071:   next_key_and_value self hash(key) &key !value
  // 1072:   if key == NONE return
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__1 */;
  result_count =
    frame->caller_result_count >= 1 ?
    frame->caller_result_count-1 : -1;
  myself = get__forever();
  func = myself->type;
  frame->cont = cont__types__unordered_table__update_each_from_to_15;
}
static void entry__types__unordered_table__update_each_from_to_7(void) {
  allocate_initialized_frame_gc(6, 7);
  // slot allocations:
  // body: 0
  // key: 1
  // value: 2
  // self: 3
  // last: 4
  // return: 5
  frame->slots[0] = myself->closure.frame->slots[3]; /* body */
  frame->slots[1] = myself->closure.frame->slots[5]; /* key */
  frame->slots[2] = myself->closure.frame->slots[6]; /* value */
  frame->slots[3] = myself->closure.frame->slots[0]; /* self */
  frame->slots[4] = myself->closure.frame->slots[2]; /* last */
  frame->slots[5] = myself->closure.frame->slots[4]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1068: body key &value
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* key */;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* value */;
  result_count = 1;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame->cont = cont__types__unordered_table__update_each_from_to_8;
}
static void cont__types__unordered_table__update_each_from_to_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* value */ = arguments->slots[0];
  // 1069: !self(key)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* key */;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* value */;
  result_count = 1;
  myself = ((CELL *)frame->slots[3])->contents /* self */;
  func = myself->type;
  frame->cont = cont__types__unordered_table__update_each_from_to_9;
}
static void cont__types__unordered_table__update_each_from_to_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* self */ = arguments->slots[0];
  // 1070: ... key == last
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* key */;
  arguments->slots[1] = frame->slots[4] /* last */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__types__unordered_table__update_each_from_to_10;
}
static void cont__types__unordered_table__update_each_from_to_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 1070: if key == last return
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* return */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__unordered_table__update_each_from_to_11;
}
static void cont__types__unordered_table__update_each_from_to_11(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1071: ... hash(key)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* key */;
  result_count = 1;
  myself = get__hash();
  func = myself->type;
  frame->cont = cont__types__unordered_table__update_each_from_to_12;
}
static void cont__types__unordered_table__update_each_from_to_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 1071: next_key_and_value self hash(key) &key !value
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* self */;
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  arguments->slots[2] = ((CELL *)frame->slots[1])->contents /* key */;
  result_count = 2;
  myself = var._next_key_and_value;
  func = myself->type;
  frame->cont = cont__types__unordered_table__update_each_from_to_13;
}
static void cont__types__unordered_table__update_each_from_to_13(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* key */ = arguments->slots[0];
  ((CELL *)frame->slots[2])->contents /* value */ = arguments->slots[1];
  // 1072: ... key == NONE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* key */;
  arguments->slots[1] = var._NONE;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__types__unordered_table__update_each_from_to_14;
}
static void cont__types__unordered_table__update_each_from_to_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 1072: if key == NONE return
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* return */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__unordered_table__update_each_from_to_15(void) {
  myself = frame->slots[4] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void exit__types__unordered_table__update_each_from_to_1(void) {
  frame = ((CONTINUATION *)myself)->exit_frame;
  int i = argument_count;
  while (--i >= 0) {
    arguments->slots[i+1] = arguments->slots[i];
  }
  argument_count += 1;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  func = continuation_type_function;
}
static void entry__types__unordered_table__update_each_downwards_1(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // self: 0
  // body: 1
  // return: 2
  // key: 3
  frame->slots[2] /* return */ = create_continuation_with_exit(exit__types__unordered_table__update_each_downwards_1);
  frame->slots[3] /* key */ = create_cell();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* self */ = create_cell_with_contents(arguments->slots[0]);
  // 1087: $$key NONE
  ((CELL *)frame->slots[3])->contents /* key */ = var._NONE;
  // 1088: ... :
  // 1089:   previous_key_and_value self hash(key) &key $$value
  // 1090:   if key == NONE return
  // 1091:   body key &value
  // 1092:   !self(key) value
  frame->slots[4] /* temp__1 */ = create_closure(entry__types__unordered_table__update_each_downwards_2, 0);
  // 1088: forever:
  // 1089:   previous_key_and_value self hash(key) &key $$value
  // 1090:   if key == NONE return
  // 1091:   body key &value
  // 1092:   !self(key) value
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count =
    frame->caller_result_count >= 1 ?
    frame->caller_result_count-1 : -1;
  myself = get__forever();
  func = myself->type;
  frame->cont = cont__types__unordered_table__update_each_downwards_9;
}
static void entry__types__unordered_table__update_each_downwards_2(void) {
  allocate_initialized_frame_gc(4, 6);
  // slot allocations:
  // self: 0
  // key: 1
  // return: 2
  // body: 3
  // value: 4
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  frame->slots[1] = myself->closure.frame->slots[3]; /* key */
  frame->slots[2] = myself->closure.frame->slots[2]; /* return */
  frame->slots[3] = myself->closure.frame->slots[1]; /* body */
  frame->slots[4] /* value */ = create_cell();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1089: ... hash(key)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* key */;
  result_count = 1;
  myself = get__hash();
  func = myself->type;
  frame->cont = cont__types__unordered_table__update_each_downwards_3;
}
static void cont__types__unordered_table__update_each_downwards_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 1089: previous_key_and_value self hash(key) &key $$value
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  arguments->slots[2] = ((CELL *)frame->slots[1])->contents /* key */;
  result_count = 2;
  myself = var._previous_key_and_value;
  func = myself->type;
  frame->cont = cont__types__unordered_table__update_each_downwards_4;
}
static void cont__types__unordered_table__update_each_downwards_4(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* key */ = arguments->slots[0];
  ((CELL *)frame->slots[4])->contents /* value */ = arguments->slots[1];
  // 1090: ... key == NONE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* key */;
  arguments->slots[1] = var._NONE;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__types__unordered_table__update_each_downwards_5;
}
static void cont__types__unordered_table__update_each_downwards_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 1090: if key == NONE return
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* return */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__unordered_table__update_each_downwards_6;
}
static void cont__types__unordered_table__update_each_downwards_6(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1091: body key &value
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* key */;
  arguments->slots[1] = ((CELL *)frame->slots[4])->contents /* value */;
  result_count = 1;
  myself = frame->slots[3] /* body */;
  func = myself->type;
  frame->cont = cont__types__unordered_table__update_each_downwards_7;
}
static void cont__types__unordered_table__update_each_downwards_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[4])->contents /* value */ = arguments->slots[0];
  // 1092: !self(key)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* key */;
  arguments->slots[1] = ((CELL *)frame->slots[4])->contents /* value */;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* self */;
  func = myself->type;
  frame->cont = cont__types__unordered_table__update_each_downwards_8;
}
static void cont__types__unordered_table__update_each_downwards_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* self */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__types__unordered_table__update_each_downwards_9(void) {
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void exit__types__unordered_table__update_each_downwards_1(void) {
  frame = ((CONTINUATION *)myself)->exit_frame;
  int i = argument_count;
  while (--i >= 0) {
    arguments->slots[i+1] = arguments->slots[i];
  }
  argument_count += 1;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  func = continuation_type_function;
}
static void entry__types__unordered_table__update_each_from_down_to_1(void) {
  allocate_initialized_frame_gc(5, 9);
  // slot allocations:
  // self: 0
  // last: 1
  // first: 2
  // body: 3
  // return: 4
  // key: 5
  // value: 6
  // h: 7
  frame->slots[4] /* return */ = create_continuation_with_exit(exit__types__unordered_table__update_each_from_down_to_1);
  frame->slots[5] /* key */ = create_cell();
  frame->slots[6] /* value */ = create_cell();
  frame->slots[7] /* h */ = create_future();
  if (argument_count != 4) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* self */ = create_cell_with_contents(arguments->slots[0]);
  // 1108: $$key last
  ((CELL *)frame->slots[5])->contents /* key */ = frame->slots[1] /* last */;
  // 1109: $$value undefined
  ((CELL *)frame->slots[6])->contents /* value */ = get__undefined();
  // 1110: $h hash(key)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[5])->contents /* key */;
  result_count = 1;
  myself = get__hash();
  func = myself->type;
  frame->cont = cont__types__unordered_table__update_each_from_down_to_2;
}
static void cont__types__unordered_table__update_each_from_down_to_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[7] /* h */, arguments->slots[0]);
  // 1111: retrieve_item self h &key !value
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  arguments->slots[1] = frame->slots[7] /* h */;
  arguments->slots[2] = ((CELL *)frame->slots[5])->contents /* key */;
  result_count = 2;
  myself = var._retrieve_item;
  func = myself->type;
  frame->cont = cont__types__unordered_table__update_each_from_down_to_3;
}
static void cont__types__unordered_table__update_each_from_down_to_3(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[5])->contents /* key */ = arguments->slots[0];
  ((CELL *)frame->slots[6])->contents /* value */ = arguments->slots[1];
  // 1112: ... key == NONE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[5])->contents /* key */;
  arguments->slots[1] = var._NONE;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__types__unordered_table__update_each_from_down_to_4;
}
static void cont__types__unordered_table__update_each_from_down_to_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__1 */ = arguments->slots[0];
  // 1112: if key == NONE: Error "Invalid index error!"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__1 */;
  arguments->slots[1] = func__types__unordered_table__update_each_from_down_to_5;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__unordered_table__update_each_from_down_to_6;
}
static void entry__types__unordered_table__update_each_from_down_to_5(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1112: ... Error "Invalid index error!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__2bdb69f58c8fd6ea;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__unordered_table__update_each_from_down_to_6(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1113: ... :
  // 1114:   body key &value
  // 1115:   !self(key) value
  // 1116:   if key == first return
  // 1117:   previous_key_and_value self hash(key) &key !value
  // 1118:   if key == NONE return
  frame->slots[8] /* temp__1 */ = create_closure(entry__types__unordered_table__update_each_from_down_to_7, 0);
  // 1113: forever:
  // 1114:   body key &value
  // 1115:   !self(key) value
  // 1116:   if key == first return
  // 1117:   previous_key_and_value self hash(key) &key !value
  // 1118:   if key == NONE return
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__1 */;
  result_count =
    frame->caller_result_count >= 1 ?
    frame->caller_result_count-1 : -1;
  myself = get__forever();
  func = myself->type;
  frame->cont = cont__types__unordered_table__update_each_from_down_to_15;
}
static void entry__types__unordered_table__update_each_from_down_to_7(void) {
  allocate_initialized_frame_gc(6, 7);
  // slot allocations:
  // body: 0
  // key: 1
  // value: 2
  // self: 3
  // first: 4
  // return: 5
  frame->slots[0] = myself->closure.frame->slots[3]; /* body */
  frame->slots[1] = myself->closure.frame->slots[5]; /* key */
  frame->slots[2] = myself->closure.frame->slots[6]; /* value */
  frame->slots[3] = myself->closure.frame->slots[0]; /* self */
  frame->slots[4] = myself->closure.frame->slots[2]; /* first */
  frame->slots[5] = myself->closure.frame->slots[4]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1114: body key &value
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* key */;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* value */;
  result_count = 1;
  myself = frame->slots[0] /* body */;
  func = myself->type;
  frame->cont = cont__types__unordered_table__update_each_from_down_to_8;
}
static void cont__types__unordered_table__update_each_from_down_to_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* value */ = arguments->slots[0];
  // 1115: !self(key)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* key */;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* value */;
  result_count = 1;
  myself = ((CELL *)frame->slots[3])->contents /* self */;
  func = myself->type;
  frame->cont = cont__types__unordered_table__update_each_from_down_to_9;
}
static void cont__types__unordered_table__update_each_from_down_to_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* self */ = arguments->slots[0];
  // 1116: ... key == first
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* key */;
  arguments->slots[1] = frame->slots[4] /* first */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__types__unordered_table__update_each_from_down_to_10;
}
static void cont__types__unordered_table__update_each_from_down_to_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 1116: if key == first return
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* return */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__unordered_table__update_each_from_down_to_11;
}
static void cont__types__unordered_table__update_each_from_down_to_11(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1117: ... hash(key)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* key */;
  result_count = 1;
  myself = get__hash();
  func = myself->type;
  frame->cont = cont__types__unordered_table__update_each_from_down_to_12;
}
static void cont__types__unordered_table__update_each_from_down_to_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 1117: previous_key_and_value self hash(key) &key !value
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* self */;
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  arguments->slots[2] = ((CELL *)frame->slots[1])->contents /* key */;
  result_count = 2;
  myself = var._previous_key_and_value;
  func = myself->type;
  frame->cont = cont__types__unordered_table__update_each_from_down_to_13;
}
static void cont__types__unordered_table__update_each_from_down_to_13(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* key */ = arguments->slots[0];
  ((CELL *)frame->slots[2])->contents /* value */ = arguments->slots[1];
  // 1118: ... key == NONE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* key */;
  arguments->slots[1] = var._NONE;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__types__unordered_table__update_each_from_down_to_14;
}
static void cont__types__unordered_table__update_each_from_down_to_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 1118: if key == NONE return
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* return */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__unordered_table__update_each_from_down_to_15(void) {
  myself = frame->slots[4] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void exit__types__unordered_table__update_each_from_down_to_1(void) {
  frame = ((CONTINUATION *)myself)->exit_frame;
  int i = argument_count;
  while (--i >= 0) {
    arguments->slots[i+1] = arguments->slots[i];
  }
  argument_count += 1;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  func = continuation_type_function;
}

static long func__types__unordered_table___debug_string(NODE *node, int indent, int max_depth, char *buf) {
  UNORDERED_TABLE *myself = (UNORDERED_TABLE *)node;

  long n;
  long count = 0;

  UNORDERED_TABLE_DATA *data = myself->data;

  if (data) {
    const char *contents_indent;
    const char *contents_indent_2;
    if (max_depth > 1) {
      n = debug_print_head(&indent, &buf, "unordered_table");
      contents_indent = indent_to_string(indent);
      contents_indent_2 = indent_to_string(indent+2);
    }

    long rev_no = data->rev_no;
    UNORDERED_TABLE_HASH_COLLISION **entries = data->entries;
    long size = data->size;
    long idx;
    for (idx = 0; idx < size; ++idx) {
      UNORDERED_TABLE_HASH_COLLISION *hash_collision = entries[idx];
      while (hash_collision) {
        UNORDERED_TABLE_KEY_COLLISION *key_collision =
          hash_collision->key_collisions;
        while (key_collision) {
          UNORDERED_TABLE_REVISION *revision = key_collision->revisions;
          while (revision) {
            if (revision->rev_no <= rev_no) {
              if (revision->value != undefined) {
                ++count;
                if (max_depth > 1) {
                  long len;
                  n += print(&buf, contents_indent);
                  n += print(&buf, "=\n");
                  n += print(&buf, contents_indent_2);
                  len = debug_string(key_collision->key, indent+2, max_depth-1, buf);
                  if (buf) buf += len;
                  n += len;
                  n += print(&buf, contents_indent_2);
                  len = debug_string(revision->value, indent+2, max_depth-1, buf);
                  if (buf) buf += len;
                  n += len;
                }
                break;
              }
              revision = revision->link;
            }
          }
          key_collision = key_collision->link;
        }
        hash_collision = hash_collision->link;
      }
    }
  } else {
    return debug_print(indent, buf, "empty_unordered_table");
  }

  if (max_depth > 1) {
    return n;
  } else {
    return
      debug_print(indent, buf, "<unordered_table with %ld entries>", count);
  }
}
EXPORT void collect__basic__types__unordered_table(void) {
  var._NONE = collect_node(var._NONE);
  var._insert_item = collect_node(var._insert_item);
  var._retrieve_item = collect_node(var._retrieve_item);
  var.types__unordered_table = collect_node(var.types__unordered_table);
  collect_static_attributes(&attributes__types__unordered_table);
  var._next_key_and_value = collect_node(var._next_key_and_value);
  var._previous_key_and_value = collect_node(var._previous_key_and_value);
  var.std__empty_unordered_table = collect_node(var.std__empty_unordered_table);
  var.std__unordered_table = collect_node(var.std__unordered_table);
}

static int already_run_phase_1 = false;

EXPORT void phase_1__basic__types__unordered_table(void) {
  if (already_run_phase_1) return;
  already_run_phase_1 = true;
  register_module_info(&module_info);
}

static int already_run_phase_2 = false;

EXPORT void phase_2__basic__types__unordered_table(void) {
  if (already_run_phase_2) return;
  already_run_phase_2 = true;
  set_module("basic__types__unordered_table");
  number__2 = from_uint32(2U);
  unique__NONE = register_unique_item("NONE");
  func__insert_item_1 = create_function(entry__insert_item_1, 5);
  func__retrieve_item_1 = create_function(entry__retrieve_item_1, 3);
  func__types__unordered_table__length_of_1 = create_function(entry__types__unordered_table__length_of_1, 1);
  func__next_key_and_value_1 = create_function(entry__next_key_and_value_1, 3);
  func__previous_key_and_value_1 = create_function(entry__previous_key_and_value_1, 3);
  func__types__unordered_table__private__set_item_1 = create_function(entry__types__unordered_table__private__set_item_1, 3);
  func__types__unordered_table__private__get_item_1 = create_function(entry__types__unordered_table__private__get_item_1, 2);
  string__16058a9f0bf11cc9 = from_latin_1_string("unordered_table", 15);
  func__types__unordered_table__new_empty_collection_1 = create_function(entry__types__unordered_table__new_empty_collection_1, 1);
  func__std__unordered_table_1 = create_function(entry__std__unordered_table_1, -1);
  func__types__unordered_table__for_each_1 = create_function(entry__types__unordered_table__for_each_1, 2);
  string__2bdb69f58c8fd6ea = from_latin_1_string("Invalid index error!", 20);
  func__types__unordered_table__for_each_from_to_5 = create_function(entry__types__unordered_table__for_each_from_to_5, 0);
  func__types__unordered_table__for_each_from_to_1 = create_function(entry__types__unordered_table__for_each_from_to_1, 4);
  func__types__unordered_table__for_each_downwards_1 = create_function(entry__types__unordered_table__for_each_downwards_1, 2);
  func__types__unordered_table__for_each_from_down_to_5 = create_function(entry__types__unordered_table__for_each_from_down_to_5, 0);
  func__types__unordered_table__for_each_from_down_to_1 = create_function(entry__types__unordered_table__for_each_from_down_to_1, 4);
  func__types__unordered_table__update_each_1 = create_function(entry__types__unordered_table__update_each_1, 2);
  func__types__unordered_table__update_each_from_to_5 = create_function(entry__types__unordered_table__update_each_from_to_5, 0);
  func__types__unordered_table__update_each_from_to_1 = create_function(entry__types__unordered_table__update_each_from_to_1, 4);
  func__types__unordered_table__update_each_downwards_1 = create_function(entry__types__unordered_table__update_each_downwards_1, 2);
  func__types__unordered_table__update_each_from_down_to_5 = create_function(entry__types__unordered_table__update_each_from_down_to_5, 0);
  func__types__unordered_table__update_each_from_down_to_1 = create_function(entry__types__unordered_table__update_each_from_down_to_1, 4);
}

static int already_run_phase_3 = false;

EXPORT void phase_3__basic__types__unordered_table(void) {
  if (already_run_phase_3) return;
  already_run_phase_3 = true;
  set_module("basic__types__unordered_table");
  set_used_namespaces(used_namespaces);
  assign_value(&var._NONE, unique__NONE);
  var.types__unordered_table = create_future_with_prototype(create__types__unordered_table(0, NULL));
  define_single_assign_static("types", "unordered_table", get__types__unordered_table, &var.types__unordered_table);
  var.std__empty_unordered_table = create_future();
  define_single_assign_static("std", "empty_unordered_table", get__std__empty_unordered_table, &var.std__empty_unordered_table);
  var.std__unordered_table = create_future();
  define_single_assign_static("std", "unordered_table", get__std__unordered_table, &var.std__unordered_table);
}

static int already_run_phase_4 = false;

EXPORT void phase_4__basic__types__unordered_table(void) {
  if (already_run_phase_4) return;
  already_run_phase_4 = true;
  set_module("basic__types__unordered_table");
  set_used_namespaces(used_namespaces);
  use_read_only(NULL, "Error", &get__Error, &get_value_or_future__Error);
  use_read_only(NULL, "empty_unordered_table", &get__empty_unordered_table, &get_value_or_future__empty_unordered_table);
  use_read_only(NULL, "equal_type_and_value", &get__equal_type_and_value, &get_value_or_future__equal_type_and_value);
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
  use_read_only(NULL, "parameter_count_of", &get__parameter_count_of, &get_value_or_future__parameter_count_of);
  use_polymorphic_function("private", "get_item", &get__private__get_item, &poly_idx__private__get_item);
  use_polymorphic_function("private", "set_item", &get__private__set_item, &poly_idx__private__set_item);
  use_read_only(NULL, "register_collection_serializer", &get__register_collection_serializer, &get_value_or_future__register_collection_serializer);
  use_polymorphic_function(NULL, "serialization_tag_of", &get__serialization_tag_of, &poly_idx__serialization_tag_of);
  use_read_only("std", "equal", &get__std__equal, &get_value_or_future__std__equal);
  use_read_only("std", "key_of", &get__std__key_of, &get_value_or_future__std__key_of);
  use_read_only("std", "or", &get__std__or, &get_value_or_future__std__or);
  use_read_only("std", "value_of", &get__std__value_of, &get_value_or_future__std__value_of);
  use_read_only("types", "generic_table", &get__types__generic_table, &get_value_or_future__types__generic_table);
  use_read_only(NULL, "undefined", &get__undefined, &get_value_or_future__undefined);
  use_polymorphic_function(NULL, "update_each", &get__update_each, &poly_idx__update_each);
  use_polymorphic_function(NULL, "update_each_downwards", &get__update_each_downwards, &poly_idx__update_each_downwards);
  use_polymorphic_function(NULL, "update_each_from_down_to", &get__update_each_from_down_to, &poly_idx__update_each_from_down_to);
  use_polymorphic_function(NULL, "update_each_from_to", &get__update_each_from_to, &poly_idx__update_each_from_to);
  define_method("types", "unordered_table", poly_idx__length_of, func__types__unordered_table__length_of_1);
  define_method("types", "unordered_table", poly_idx__private__set_item, func__types__unordered_table__private__set_item_1);
  define_method("types", "unordered_table", poly_idx__private__get_item, func__types__unordered_table__private__get_item_1);
  define_type_function("types", "unordered_table", entry__types__unordered_table_1, -1);
  define_attribute("types", "unordered_table", poly_idx__serialization_tag_of, string__16058a9f0bf11cc9);
  define_method("types", "unordered_table", poly_idx__new_empty_collection, func__types__unordered_table__new_empty_collection_1);
  define_method("types", "unordered_table", poly_idx__for_each, func__types__unordered_table__for_each_1);
  define_method("types", "unordered_table", poly_idx__for_each_from_to, func__types__unordered_table__for_each_from_to_1);
  define_method("types", "unordered_table", poly_idx__for_each_downwards, func__types__unordered_table__for_each_downwards_1);
  define_method("types", "unordered_table", poly_idx__for_each_from_down_to, func__types__unordered_table__for_each_from_down_to_1);
  define_method("types", "unordered_table", poly_idx__update_each, func__types__unordered_table__update_each_1);
  define_method("types", "unordered_table", poly_idx__update_each_from_to, func__types__unordered_table__update_each_from_to_1);
  define_method("types", "unordered_table", poly_idx__update_each_downwards, func__types__unordered_table__update_each_downwards_1);
  define_method("types", "unordered_table", poly_idx__update_each_from_down_to, func__types__unordered_table__update_each_from_down_to_1);
}

static int already_run_phase_5 = false;

EXPORT void phase_5__basic__types__unordered_table(void) {
  if (already_run_phase_5) return;
  already_run_phase_5 = true;
  assign_variable(&var._insert_item, &func__insert_item_1);
  assign_variable(&var._retrieve_item, &func__retrieve_item_1);
  assign_value(&var.types__unordered_table, get__types__generic_table());
  assign_variable(&var._next_key_and_value, &func__next_key_and_value_1);
  assign_variable(&var._previous_key_and_value, &func__previous_key_and_value_1);
  initialize_future(var.std__empty_unordered_table, var.types__unordered_table);
  initialize_future(var.std__unordered_table, func__std__unordered_table_1);
}

static int already_run_phase_6 = false;

EXPORT void phase_6__basic__types__unordered_table(void) {
  if (already_run_phase_6) return;
  already_run_phase_6 = true;
  register_collector(collect__basic__types__unordered_table);
}
