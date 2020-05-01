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
REGISTER FRAME *frame ASM("r15");
IMPORT void allocate_initialized_frame_gc(int slot_idx, int slot_count);
REGISTER int argument_count ASM("ebx");
REGISTER FRAME *arguments ASM("r12");
IMPORT void *node_p;
IMPORT int result_count;
REGISTER NODE *myself ASM("r13");
IMPORT void invalid_results_error(void);
typedef enum {
  VT_POLYMORPHIC,
  VT_SINGLE_ASSIGN_STATIC,
  VT_MULTI_ASSIGN_STATIC,
  VT_SINGLE_ASSIGN_DYNAMIC,
  VT_MULTI_ASSIGN_DYNAMIC,
} VAR_TYPE;
typedef struct ATTRIBUTE_ENTRY ATTRIBUTE_ENTRY;
typedef struct SYMBOL_ENTRY SYMBOL_ENTRY;
typedef struct HASH_ENTRY HASH_ENTRY;
typedef struct {
  const char *name;
  void **func;
  const char *module_name;
} C_FUNCTION;
IMPORT int runtime_major_version(void);
IMPORT int runtime_minor_version(void);
IMPORT int runtime_revision(void);
IMPORT int polymorphic_function_count;
IMPORT int polymorphic_function_with_setter_count;
IMPORT const char **polymorphic_function_names;
IMPORT void set_module(const char *name);
IMPORT void register_module_info(MODULE_INFO *info);
IMPORT void define_namespace(const char *namespace);
IMPORT void set_used_namespaces(const char **namespaces);
IMPORT NODE *from_bool(int val);
IMPORT NODE *from_int(int val);
IMPORT NODE *from_long(long val);
IMPORT NODE *from_int64(int64_t val);
IMPORT NODE *from_uint32(uint32_t val);
IMPORT NODE *from_uint64(uint64_t val);
IMPORT NODE *from_double(double val);
IMPORT NODE *from_digit_string(const char *str);
IMPORT NODE *from_uchar32(unsigned int chr);
IMPORT NODE *from_c_string(const char *str);
IMPORT NODE *from_latin_1_string(const char *str, long len);
IMPORT NODE *from_uint32_string(const uint32_t *str, long len);
IMPORT NODE *from_arguments(int first_idx, int count);
IMPORT NODE *register_unique_item(const char *name);
IMPORT void define_c_function(const char *name, void *func);
IMPORT void register_polymorphic_function(const char *name, int *id_p);
IMPORT void register_polymorphic_function_with_setter(const char *name, int *id_p);
IMPORT void define_polymorphic_function(
  const char *namespace, const char *name, NODE_GETTER getter, int *id_p,
  NODE **var_p
);
IMPORT void define_polymorphic_function_with_setter(
  const char *namespace, const char *name, NODE_GETTER getter, int *id_p,
  NODE **var_p
);
IMPORT void define_privileged_polymorphic_function(
  const char *namespace, const char *name, NODE_GETTER getter, int id,
  NODE **var_p
);
IMPORT void define_single_assign_static(
  const char *namespace, const char *name,
  NODE_GETTER getter, NODE **var_p
);
typedef void (*NODE_SETTER)(NODE *);
IMPORT void define_multi_assign_static(
  const char *namespace, const char *name,
  NODE_GETTER getter, NODE_SETTER setter
);
IMPORT void register_dynamic(int *id_p);
IMPORT void define_single_assign_dynamic(
  const char *namespace, const char *name,
  NODE_GETTER getter, NODE_SETTER definer,
  int *id_p
);
IMPORT void define_multi_assign_dynamic(
  const char *namespace, const char *name,
  NODE_GETTER getter, NODE_SETTER setter, NODE_SETTER definer,
  int *id_p
);
IMPORT void define_type_function(
  const char *namespace, const char *name, FUNC type, int par_cnt
);
IMPORT void define_attribute(
  const char *namespace, const char *name,
  int id, NODE *attribute
);
IMPORT void define_method(
  const char *namespace, const char *name,
  int id, NODE *method
);
IMPORT void use_polymorphic_function(
  const char *namespace, const char *name, NODE_GETTER *getter, int *id
);
IMPORT void use_read_only(
  const char *namespace, const char *name,
  NODE_GETTER *getter, NODE_GETTER *get_value_or_future
);
IMPORT void use_read_write(
  const char *namespace, const char *name,
  NODE_GETTER *getter, NODE_SETTER *setter
);
IMPORT void use_single_assign_dynamic(
  const char *namespace, const char *name,
  NODE_GETTER *getter, NODE_SETTER *definer
);
IMPORT void use_multi_assign_dynamic(
  const char *namespace, const char *name,
  NODE_GETTER *getter, NODE_SETTER *setter, NODE_SETTER *definer
);
IMPORT void resolve_symbols(void);
IMPORT void resolve_attributes(void);
typedef struct SIMPLE_NODE {
  FUNC type;
  struct ATTRIBUTES *attributes;
} SIMPLE_NODE;
typedef struct FUNCTION {
  FUNC type;
  struct ATTRIBUTES *attributes;
  int parameter_count;
} FUNCTION;
IMPORT DYNAMICS *dynamics;
typedef struct ATTRIBUTE_LIST {
  struct ATTRIBUTE_LIST *link;
  int idx;
  void *attr;
} ATTRIBUTE_LIST;
typedef struct FUTURE {
  FUNC type;
  struct ATTRIBUTES *attributes;
  NODE *link;
  struct ATTRIBUTE_LIST *pending_attributes;
  NODE *dependent_futures;
  NODE *prototype;
  long is_already_initialized;
  NODE *pad_2;
} FUTURE;
typedef struct CELL {
  FUNC type;
  struct ATTRIBUTES *attributes;
  NODE *contents;
} CELL;
typedef enum {
  EM__NORMAL,
  EM__RECORD,
  EM__REPLAY
} EVENT__MODE;
typedef struct PHASE_2_COLLECTOR {
  void *dummy;
  void *next_collector;
  void (*collector)(void *data);
} PHASE_2_COLLECTOR;
IMPORT int main_argc;
IMPORT char **main_argv;
IMPORT EVENT__MODE event__mode;
IMPORT void *update_start_p;
IMPORT NODE *undefined;
IMPORT NODE *zero;
IMPORT NODE *boolean_true;
IMPORT NODE *boolean_false;
IMPORT NODE *empty_string;
IMPORT NODE_GETTER raise_exception_getter;
IMPORT uint64_t instruction_counter;
IMPORT OCTREE no_attributes_level_1;
IMPORT OCTREE no_attributes_level_2;
IMPORT OCTREE no_attributes_level_3;
IMPORT OCTREE no_attributes_level_4;
IMPORT OCTREE no_attributes_level_5;
IMPORT OCTREE no_attributes_level_6;
IMPORT OCTREE no_attributes_level_7;
IMPORT OCTREE no_attributes_level_8;
IMPORT OCTREE undefined_attributes_level_1;
IMPORT OCTREE undefined_attributes_level_2;
IMPORT OCTREE undefined_attributes_level_3;
IMPORT OCTREE undefined_attributes_level_4;
IMPORT OCTREE undefined_attributes_level_5;
IMPORT OCTREE undefined_attributes_level_6;
IMPORT OCTREE undefined_attributes_level_7;
IMPORT OCTREE undefined_attributes_level_8;
IMPORT int runtime_debug_level;
IMPORT __attribute__ ((noreturn)) void unrecoverable_error(const char *msg, ...);
IMPORT __attribute__ ((noreturn)) void out_of_memory_error(void);
IMPORT __attribute__ ((noreturn)) void invalid_continuation_error(void);
IMPORT void *allocate(long size);
IMPORT void *allocate_and_clear(long size);
IMPORT void *allocate_memory(size_t size);
IMPORT void *reallocate_memory(void * buf, size_t size);
IMPORT void *allocate_gc(long size);
IMPORT void allocate_arguments(void);
IMPORT void *allocate_fixed(long size);
IMPORT void *allocate_fixed_with_destructor(long size, DESTRUCTOR destructor);
IMPORT void *allocate_large(long size);
IMPORT void deallocate_memory(void *buf);
IMPORT void *copy(const void *buf, long size);
IMPORT void register_phase_3_collector(void *data);
IMPORT int child_changed_state;
IMPORT int window_changed_size;
IMPORT NODE *from_printf(const char *msg, ...);
IMPORT __attribute__ ((noreturn)) void runtime_error(const char *msg, ...);
IMPORT void too_few_arguments_error(void);
IMPORT void too_many_arguments_error(void);
IMPORT void invalid_arguments_error(void);
IMPORT void too_few_results_error(void);
IMPORT void too_many_results_error(void);
IMPORT void invalid_index_error(void);
IMPORT void divide_by_zero_error(void);
IMPORT void not_yet_implemented_error(void);
IMPORT void no_such_function(void);
IMPORT void no_such_attribute(void);
IMPORT void resource_error(void);
IMPORT void io_error(void);
IMPORT void initialize_runtime(void);
IMPORT void initialize_phase_3(void);
IMPORT void initialize_phase_4(void);
IMPORT void join_nodes(void *left_node_pp, void *right_node_pp);
IMPORT NODE *clone_object_and_attributes(NODE *node);
IMPORT void register_collector(FUNC collector);
IMPORT NODE *collect_node(NODE *node);
IMPORT void collect_static_attributes(ATTRIBUTES *attributes);
IMPORT ATTRIBUTES *collect_attributes(ATTRIBUTES *attributes);
IMPORT void *collect_simple_node(SIMPLE_NODE *node);
IMPORT int total_garbage_collections;
IMPORT void collect_garbage();
IMPORT const char *indent_to_string(int indent);
IMPORT int print(char **buf_p, const char *format, ...);
IMPORT int debug_print(int indent, char *buf, const char *format, ...);
IMPORT int debug_print_head(int *indent_p, char **buf_p, const char *format, ...);
IMPORT void optional_item(NODE *item);
IMPORT NODE *get_attribute(NODE *node, int idx);
IMPORT void polymorph_dispatch(int idx);
IMPORT void set_attribute(ATTRIBUTES *attributes, int idx, void *attr);
IMPORT void set_attribute_value(ATTRIBUTES *attributes, int idx, void *attr);
IMPORT void record__event(const char *name);
IMPORT void successful__action(const char *name);
IMPORT void failed__action(const char *name);
IMPORT void replay__event(const char *name);
IMPORT int replay__action(const char *name);
IMPORT void report__event(const char *name);
IMPORT void print__pointer(void *ptr);
IMPORT void store__pointer(void *ptr);
IMPORT void retrieve__pointer(void **ptr_p);
IMPORT void print__integer(int val);
IMPORT void store__integer(int val);
IMPORT void retrieve__integer(int *val_p);
IMPORT void print__long_integer(long val);
IMPORT void store__long_integer(long val);
IMPORT void retrieve__long_integer(long *val_p);
IMPORT void print__int_array(const int *buf, long len);
IMPORT void store__int_array(const int *buf, long len);
IMPORT long retrieve__int_array(int **buf_p);
IMPORT void print__memory(const uint8_t *buf, long len);
IMPORT void store__memory(const uint8_t *buf, long len);
IMPORT long retrieve__memory(uint8_t **buf_p);
IMPORT void print__c_string(const char *buf);
IMPORT void store__c_string(const char *buf);
IMPORT void retrieve__c_string(char **buf_p);
IMPORT NODE *create_function(FUNC func, int par_count);
IMPORT NODE *create_closure(FUNC type, int par_count);
IMPORT void continuation_type_function(void);
IMPORT void continuation_trampoline(void);
IMPORT NODE *create_continuation(void);
IMPORT NODE *create_continuation_with_exit(FUNC exit_func);
IMPORT void initialize_function_attributes(void);
IMPORT NODE *create_future(void);
IMPORT NODE *create_future_with_prototype(NODE *prototype);
IMPORT void initialize_future(NODE *var, NODE *val);
IMPORT void maybe_initialize_future(NODE *var, NODE *val);
IMPORT void initialize_maybe_future(NODE *var, NODE *val);
IMPORT void assign_value(NODE **dest, NODE *val);
IMPORT void assign_variable(NODE **dest, NODE **var_p);
IMPORT void def_attribute(NODE **var_p, int idx, void *attr);
IMPORT NODE *create_cell(void);
IMPORT NODE *create_cell_with_contents(NODE *contents);
IMPORT NODE *get_dynamic_slot(int id);
IMPORT NODE *get_dynamic_cell(int id);
IMPORT void set_dynamic_cell(int id, NODE *node);
IMPORT void define_dynamic_slot(int id, NODE *node);
IMPORT void define_dynamic_cell(int id, NODE *node);
IMPORT void terminate(int exit_code);
IMPORT __attribute__ ((noreturn)) void execute(FUNC entry);
IMPORT void invoke_callback(NODE *callback);
typedef int (*COMPARE_FUNCTION)(const void *, const void *);
typedef enum {
  SHOW_PROMPT,
  LOG_LAST_INSTRUCTION,
  GOTO_INSTRUCTION
} DEBUG_COMMAND;
typedef struct {
  DEBUG_COMMAND command;
  uint64_t instruction_counter;
  int depth;
} SHARED_DATA;
IMPORT int retrieve_continuation_info(
  FUNC func, const char **filename_p, CONTINUATION_INFO **info_p
);
IMPORT void crash_dump(void);


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
static NODE_GETTER get__std__key_value_pair;
static NODE_GETTER get_value_or_future__std__key_value_pair;
static NODE_GETTER get__table;
static NODE_GETTER get_value_or_future__table;
static struct {
  NODE *sim2c__runtime_symbols;
} var;
static const char *var_names[] = {
};
static NODE *get__sim2c__runtime_symbols(void) {
  return var.sim2c__runtime_symbols;
}
static NODE *string__fa728015cb16b81;
static NODE *string__8edd415ac72451d0;
static void cont__2_3(void);
static NODE *string__800a0c585ff0632;
static NODE *string__5c95584625416db4;
static void cont__2_6(void);
static NODE *string__610a38f055666a5;
static NODE *string__3e779bba71ff6e96;
static void cont__2_9(void);
static NODE *string__1580bcaf2d42dade;
static NODE *string__56c3d0662f712784;
static void cont__2_12(void);
static NODE *string__966c1d52f9f0535e;
static NODE *string__9f2336b788df6407;
static void cont__2_15(void);
static NODE *string__69c55d0406b923b8;
static NODE *string__fc5ea67cb9ff6239;
static void cont__2_18(void);
static NODE *string__5db1024c9851410f;
static NODE *string__a1dd1a49069005db;
static void cont__2_21(void);
static NODE *string__786504f5b93f55fd;
static NODE *string__86acba43b7c3c22a;
static void cont__2_24(void);
static NODE *string__786504f5b92f55fc;
static NODE *string__86acaa43b6c3c22a;
static void cont__2_27(void);
static NODE *string__7690e6a93c025e80;
static NODE *string__f62e6c6074331b2f;
static void cont__2_30(void);
static NODE *string__a8d3ab331eb668e7;
static NODE *string__bdeaeb384def5a1;
static void cont__2_33(void);
static NODE *string__77b931a5baaa8bfc;
static NODE *string__b46169d78bdd1cff;
static void cont__2_36(void);
static NODE *string__b4d3ad331eeeb8e0;
static NODE *string__301d5357b968136a;
static void cont__2_39(void);
static NODE *string__3d988d5d234b8764;
static NODE *string__1a135fbcb802cc05;
static void cont__2_42(void);
static NODE *string__dc6342966f81738c;
static NODE *string__6777bcdceff69976;
static void cont__2_45(void);
static NODE *string__74b135724d6dbce9;
static NODE *string__3ef83756322d0f8;
static void cont__2_48(void);
static NODE *string__51af6105266784c5;
static NODE *string__6e38e34fa7ce2068;
static void cont__2_51(void);
static NODE *string__6a8c256a04788689;
static NODE *string__3e6f7d71ebbc1fd7;
static void cont__2_54(void);
static NODE *string__10dcaf9184a54094;
static NODE *string__9d29beb6e8094e17;
static void cont__2_57(void);
static NODE *string__768c256a04708682;
static NODE *string__205751daa5312b90;
static void cont__2_60(void);
static NODE *string__29502504369be455;
static NODE *string__2e6aba362d00a1da;
static void cont__2_63(void);
static NODE *string__1c21a45122913ab3;
static NODE *string__91b47fced47c61e2;
static void cont__2_66(void);
static NODE *string__1c21a45122b93ab5;
static NODE *string__d1b24fced47c61cb;
static void cont__2_69(void);
static NODE *string__2a21a1d9a0695ae4;
static NODE *string__cebc109d1e7797e2;
static void cont__2_72(void);
static NODE *string__f7822ff0f11c2c3;
static NODE *string__290e2a52fea6fc66;
static void cont__2_75(void);
static NODE *string__88904ccd590813f;
static NODE *string__b475c09adc8d6659;
static void cont__2_78(void);
static NODE *string__2696ba098b1916ef;
static NODE *string__7be49ac3d7efe7a6;
static void cont__2_81(void);
static NODE *string__f8dc63c35d5f67e4;
static NODE *string__bb39174a4b655c1c;
static void cont__2_84(void);
static NODE *string__6148905dd1501604;
static NODE *string__c2bd832925dd7b1c;
static void cont__2_87(void);
static NODE *string__c81c58c835e0c166;
static NODE *string__f28c00dfeab5a4f5;
static void cont__2_90(void);
static NODE *string__dc074c1662997308;
static NODE *string__ecd63bf007719c5e;
static void cont__2_93(void);
static NODE *string__81d201e3591a9487;
static NODE *string__bd156810a3b87b39;
static void cont__2_96(void);
static NODE *string__34c427046666a791;
static NODE *string__1852e8fc677301ab;
static void cont__2_99(void);
static NODE *string__4f152c2abbd22d29;
static NODE *string__b2c113b0186c2dd1;
static void cont__2_102(void);
static NODE *string__caafa59fe636a9de;
static NODE *string__e4d263547623cea0;
static void cont__2_105(void);
static NODE *string__4a15c8d55d6a0491;
static NODE *string__21c0f79678df3c50;
static void cont__2_108(void);
static NODE *string__2d9e9f5fd5d9523e;
static NODE *string__6445dfc09129e2bc;
static void cont__2_111(void);
static NODE *string__7699f5c17fb1f0c5;
static NODE *string__bd51ec8ac074a909;
static void cont__2_114(void);
static NODE *string__9d2186757f44a3c;
static NODE *string__d8100904e5447128;
static void cont__2_117(void);
static NODE *string__1614e67e91066b2b;
static NODE *string__da679ac2fd23801b;
static void cont__2_120(void);
static NODE *string__8457fc89067b44ac;
static NODE *string__8d9a40a45ca1f46;
static void cont__2_123(void);
static NODE *string__e966bea4d1b0bef3;
static NODE *string__4203ade7496d3cba;
static void cont__2_126(void);
static NODE *string__bb073f307486f5e2;
static NODE *string__d8ae744927741c5e;
static void cont__2_129(void);
static NODE *string__50d53079c2d41e49;
static NODE *string__d699aac52d63a802;
static void cont__2_132(void);
static NODE *string__6a969a66ba3e062e;
static NODE *string__3ca1e27da11d6a79;
static void cont__2_135(void);
static NODE *string__f22e4ba252bb0402;
static NODE *string__cd13cee030a4034b;
static void cont__2_138(void);
static NODE *string__9c6f2af22609a633;
static NODE *string__b5cfa062437d6535;
static void cont__2_141(void);
static NODE *string__6f91310d31f5631c;
static NODE *string__5ca1f7a22b3232c2;
static void cont__2_144(void);
static NODE *string__f5ba58e4689a80a3;
static NODE *string__d107ad9b7b630943;
static void cont__2_147(void);
static NODE *string__d1e75099653d132f;
static NODE *string__1eb9413f2d2e180c;
static void cont__2_150(void);
static NODE *string__15d9100c1cca979d;
static NODE *string__bd4383921548788;
static void cont__2_153(void);
static NODE *string__366b3f231611767c;
static NODE *string__cf523af04f93c1a2;
static void cont__2_156(void);
static NODE *string__5e0ae28b5c407d7c;
static NODE *string__8f20b7aa2b348ba;
static void cont__2_159(void);
static NODE *string__4e0ae40b5c107d7a;
static NODE *string__5ad1f0da53fa6a79;
static void cont__2_162(void);
static NODE *string__682044480a23ffd9;
static NODE *string__c6ec8dca53a5a1af;
static void cont__2_165(void);
static NODE *string__682044420a23ffd9;
static NODE *string__b8b9c6a2212e34c0;
static void cont__2_168(void);
static NODE *string__28002bbaa0792117;
static NODE *string__9ae348be480e8e0;
static void cont__2_171(void);
static NODE *string__73b53d02825023b3;
static NODE *string__b20c4a77a3ac08a2;
static void cont__2_174(void);
static NODE *string__1a1f5edb80d91292;
static NODE *string__c4d379f2bb5c3e41;
static void cont__2_177(void);
static NODE *string__301f5ad700906292;
static NODE *string__8106f1378366edc;
static void cont__2_180(void);
static NODE *string__5fad150f13015352;
static NODE *string__86e05501f2bf69ee;
static void cont__2_183(void);
static NODE *string__3470a78105cf84f3;
static NODE *string__5dec1a1e2d91f421;
static void cont__2_186(void);
static NODE *string__1c6c7289032a5d69;
static NODE *string__1dd5fa7b31b5023d;
static void cont__2_189(void);
static NODE *string__d4880084942830bf;
static NODE *string__6fd6eaaa0ae0aa48;
static void cont__2_192(void);
static NODE *string__640a78105afa4ae;
static NODE *string__4e857cd3f4048898;
static void cont__2_195(void);
static NODE *string__22640217ef38138c;
static NODE *string__aca6b18f1d890a7a;
static void cont__2_198(void);
static NODE *string__4950e37017ade5ae;
static NODE *string__196c75ae6866989e;
static void cont__2_201(void);
static NODE *string__301f5b1380290292;
static NODE *string__998dcabeeeee256c;
static void cont__2_204(void);
static NODE *string__440ae00b5c007d75;
static NODE *string__552dc13bf9788e15;
static void cont__2_207(void);
static NODE *string__2e5ae343eba27012;
static NODE *string__18822595562573af;
static void cont__2_210(void);
static NODE *string__67d12b89151881ee;
static NODE *string__97eba66a53ce2418;
static void cont__2_213(void);
static NODE *string__659c1a461307f144;
static NODE *string__aff0e1bffd69d09e;
static void cont__2_216(void);
static NODE *string__926c42c90a3a5dc4;
static NODE *string__35dcdd757d8ff36a;
static void cont__2_219(void);
static NODE *string__9a0c8a840b2a5eac;
static NODE *string__699ad5fe935c0c;
static void cont__2_222(void);
static NODE *string__92381b92f44420eb;
static NODE *string__ad6cb4d361a97110;
static void cont__2_225(void);
static NODE *string__b203ec07e46c6d80;
static NODE *string__8f7c86910d6d0ec0;
static void cont__2_228(void);
static NODE *string__dfd1ce1d312022e7;
static NODE *string__70bef8fa01ea78c4;
static void cont__2_231(void);
static NODE *string__64ac252603a3a696;
static NODE *string__501ffc7c0e5fce8d;
static void cont__2_234(void);
static NODE *string__7e1f570601dbc2b1;
static NODE *string__7ed5b7453a0b28eb;
static void cont__2_237(void);
static NODE *string__e0aec0b5d107d5a;
static NODE *string__226dfcc2010b42bb;
static void cont__2_240(void);
static NODE *string__6e5aeb43eaa07032;
static NODE *string__2cf4a351abcf4415;
static void cont__2_243(void);
static NODE *string__d48de512cf50371c;
static NODE *string__8f245610f4cd3fb7;
static void cont__2_246(void);
static NODE *string__74f0af9104cd80d3;
static NODE *string__1b7f73c5bf94e5d0;
static void cont__2_249(void);
static NODE *string__6c94222b8f3884e6;
static NODE *string__5ae9ab7012ed0dc4;
static void cont__2_252(void);
static NODE *string__6c94222b8f3884f3;
static NODE *string__b4d23a65497e01c1;
static void cont__2_255(void);
static NODE *string__da8d82842a2a5a84;
static NODE *string__ab557f0a5c48499b;
static void cont__2_258(void);
static NODE *string__501f57078042a2a7;
static NODE *string__f43fa690fc94429d;
static void cont__2_261(void);
static NODE *string__efcd0668b0ae04c6;
static NODE *string__6f7ba838857d0d29;
static void cont__2_264(void);
static NODE *string__2729ba62a63415a9;
static NODE *string__411ed56d73ccbf77;
static void cont__2_267(void);
static NODE *string__25a63323422a9216;
static NODE *string__3156ce0eca29841b;
static void cont__2_270(void);
static NODE *string__bc56b0920bfa074e;
static NODE *string__6c603b3047444a74;
static void cont__2_273(void);
static NODE *string__d50939ffa304eba1;
static NODE *string__dfb31d464579b6cc;
static void cont__2_276(void);
static NODE *string__7ca0252e172b1501;
static NODE *string__35b46e45a024cc89;
static void cont__2_279(void);
static NODE *string__360ae80b5df07d56;
static NODE *string__6ff45b807d805ee8;
static void cont__2_282(void);
static NODE *string__62d904ca56abf62f;
static NODE *string__a7036984828ad991;
static void cont__2_285(void);
static NODE *string__52b31fb1ca36ad;
static NODE *string__606c03df4d04a811;
static void cont__2_288(void);
static NODE *string__ee21fa04ce7f45ad;
static NODE *string__922f8927bcb56a37;
static void cont__2_291(void);
static NODE *string__9a7719701e463c3d;
static NODE *string__4dfebf8ce2b979fc;
static void cont__2_294(void);
static NODE *string__ccb06cae4fc7ced1;
static NODE *string__f51775fad4122113;
static void cont__2_297(void);
static NODE *string__f10614695d7490c;
static NODE *string__ae72e78740405523;
static void cont__2_300(void);
static NODE *string__f10614695d7490f;
static NODE *string__ae72e74740405523;
static void cont__2_303(void);
static NODE *string__f10614695d7490e;
static NODE *string__ae72e70740405523;
static void cont__2_306(void);
static NODE *string__f10614695d74909;
static NODE *string__ae72e6c740405523;
static void cont__2_309(void);
static NODE *string__f10614695d74908;
static NODE *string__ae72e68740405523;
static void cont__2_312(void);
static NODE *string__f10614695d7490b;
static NODE *string__ae72e64740405523;
static void cont__2_315(void);
static NODE *string__f10614695d7490a;
static NODE *string__ae72e60740405523;
static void cont__2_318(void);
static NODE *string__f10614695d74905;
static NODE *string__ae72e5c740405523;
static void cont__2_321(void);
static NODE *string__a96d37e5269efcea;
static NODE *string__d3abaa3aea9568d8;
static void cont__2_324(void);
static NODE *string__a96d37e5269efce9;
static NODE *string__d3abaafaea9568d8;
static void cont__2_327(void);
static NODE *string__a96d37e5269efce8;
static NODE *string__d3abaabaea9568d8;
static void cont__2_330(void);
static NODE *string__a96d37e5269efcef;
static NODE *string__d3abab7aea9568d8;
static void cont__2_333(void);
static NODE *string__a96d37e5269efcee;
static NODE *string__d3abab3aea9568d8;
static void cont__2_336(void);
static NODE *string__a96d37e5269efced;
static NODE *string__d3ababfaea9568d8;
static void cont__2_339(void);
static NODE *string__a96d37e5269efcec;
static NODE *string__d3ababbaea9568d8;
static void cont__2_342(void);
static NODE *string__a96d37e5269efce3;
static NODE *string__d3aba87aea9568d8;
static void cont__2_345(void);
static NODE *string__96bd3c5645503754;
static NODE *string__313ff19f63187450;
static void cont__2_348(void);
static NODE *string__39a91c6464b48cb7;
static NODE *string__51cfd78644d80c92;
static void cont__2_351(void);
static NODE *string__fd5f7ef32f24bfaa;
static NODE *string__fec3a524701ff247;
static void cont__2_354(void);
static NODE *string__761587227d4825b9;
static NODE *string__6d343fd95f2f86f5;
static void cont__2_357(void);
static NODE *string__68a4ad9004756065;
static NODE *string__828961258c78d260;
static void cont__2_360(void);
static NODE *string__83bbca0be31365ab;
static NODE *string__b0f237f00b697e93;
static void cont__2_363(void);
static NODE *string__cfe9a9f60d3a5cd4;
static NODE *string__998fb2a1fe8a0c3e;
static void cont__2_366(void);
static NODE *string__b1ec1042f2e6e8ff;
static NODE *string__e4edebbe4882d6ef;
static void cont__2_369(void);
static NODE *string__cad15e9b2330eaa3;
static NODE *string__d95df4cca4d2c6fd;
static void cont__2_372(void);
static NODE *string__91b7c8dee3bb862a;
static NODE *string__32a7900019341d55;
static void cont__2_375(void);
static NODE *string__5395bcbd356e71b1;
static NODE *string__e0605de396839adc;
static void cont__2_378(void);
static NODE *string__42e269e73a13b76b;
static NODE *string__69dfa40f6a365db;
static void cont__2_381(void);
static NODE *string__1b77e1575779efa5;
static NODE *string__6757b2e2474a0b22;
static void cont__2_384(void);
static NODE *string__4395be3d357ed1b0;
static NODE *string__e0e85de2d683928c;
static void cont__2_387(void);
static NODE *string__b1fa1042f2e6e8ff;
static NODE *string__b16ca6def7b3553c;
static void cont__2_390(void);
static NODE *string__40aea8b5de07d40;
static NODE *string__e97bf72e3ea776ca;
static void cont__2_393(void);
static NODE *string__b23dc2be453fb4c;
static NODE *string__68644448021229ea;
static void cont__2_396(void);
static NODE *string__edb661f544f7f1b4;
static NODE *string__58ce4981a1cf1c90;
static void cont__2_399(void);
static NODE *string__b7b51829c8931dfe;
static NODE *string__41f55b1721116bb3;
static void cont__2_402(void);
static NODE *string__1221a2d3a0a88ae7;
static NODE *string__906cbeff26b5017a;
static void cont__2_405(void);
static NODE *string__667e759fbd1e073a;
static NODE *string__4f98ca907370d4fd;
static void cont__2_408(void);
static NODE *string__ac42fe8001c0cf7b;
static NODE *string__90e4557368bcc70c;
static void cont__2_411(void);
static NODE *string__fe16467ca0045e4f;
static NODE *string__4b24985949e64aa0;
static void cont__2_414(void);
static NODE *string__3c5182f403404f1a;
static NODE *string__e4e6d5f3092cd470;
static void cont__2_417(void);
static NODE *string__5a7ee7d9a77669df;
static NODE *string__3e34445dbde01d92;
static void cont__2_420(void);
static NODE *string__a8f9f59d763f3b3c;
static NODE *string__96b12e6b0e8f1ea6;
static void cont__2_423(void);
static NODE *string__8a74e5d82136242e;
static NODE *string__3fb204104c301790;
static void cont__2_426(void);
static NODE *string__fad96544e5c0b191;
static NODE *string__82b0591fec9d608e;
static void cont__2_429(void);
static NODE *string__776fc0898d8697f5;
static NODE *string__de9a692913a186a6;
static void cont__2_432(void);
static NODE *string__76bf0e1274169131;
static NODE *string__682822d0ffcfd8e0;
static void cont__2_435(void);
static NODE *string__e0508ed6bc3a9403;
static NODE *string__d9addc1ddea8b503;
static void cont__2_438(void);
static NODE *string__60dde75c27ced2c1;
static NODE *string__f20d2016c4807ea2;
static void cont__2_441(void);
static NODE *string__6c150ead26004347;
static NODE *string__9d8c53f6d9a9a7b7;
static void cont__2_444(void);
static NODE *string__4aa8a94984adc172;
static NODE *string__162c20703a78c3ff;
static void cont__2_447(void);
static NODE *string__b6e0e11e4743dfdf;
static NODE *string__f2036859ec134a7c;
static void cont__2_450(void);
static NODE *string__b8e8e210c6d32f89;
static NODE *string__fc82f8a9ba1d427f;
static void cont__2_453(void);
static NODE *string__b8e8e210c6d32f8e;
static NODE *string__fc82f8a9bd1d427f;
static void cont__2_456(void);
static NODE *string__d0e5e8074891f627;
static NODE *string__3f5d3a0d2c7bc3c7;
static void cont__2_459(void);
static NODE *string__2b5c4104290394d2;
static NODE *string__5104e1e70e2bbd29;
static void cont__2_462(void);
static NODE *string__41c85713242372c5;
static NODE *string__e51baebf46ac8640;
static void cont__2_465(void);
static NODE *string__5592cf0301411d16;
static NODE *string__dee304be4126ea7;
static void cont__2_468(void);
static NODE *string__56d11b875621f62f;
static NODE *string__caea8b2ff976ddc3;
static void cont__2_471(void);
static NODE *string__34fd7b2a54432a1f;
static NODE *string__2f060df2bab9ebec;
static void cont__2_474(void);
static NODE *string__32e13e70f6337af4;
static NODE *string__8a205606fdc9fcee;
static void cont__2_477(void);
static NODE *string__47935b184e1b3728;
static NODE *string__337f24e44c027fbc;
static void cont__2_480(void);
static NODE *string__9520754d88a4dfe0;
static NODE *string__ae1a6ceddb2e6555;
static void cont__2_483(void);
static NODE *string__5089ba700d952389;
static NODE *string__728beb96de734cfe;
static void cont__2_486(void);
static NODE *string__317937b8f705e12f;
static NODE *string__726eb8f70f88c9b;
static void cont__2_489(void);
static NODE *string__6e5ae943eab91023;
static NODE *string__1248a4b5a2020125;
static void cont__2_492(void);
static NODE *string__a4c11b042d78a9f5;
static NODE *string__b17e1477ca7d8644;
static void cont__2_495(void);
static NODE *string__c6bc4dbad16d7de6;
static NODE *string__9852c4e0e14b8181;
static void cont__2_498(void);
static NODE *string__a0540e55151930c2;
static NODE *string__8b67b34a14524350;
static void cont__2_501(void);
static NODE *string__72a8a8c9865d0296;
static NODE *string__7156ce06811a3bb7;
static void cont__2_504(void);
static NODE *string__72a8a8c9864d0292;
static NODE *string__71578e06f11a2bb7;
static void cont__2_507(void);
static NODE *string__72a8a8c986650294;
static NODE *string__7156ce06611a33b7;
static void cont__2_510(void);
static NODE *string__7ca8ae498474c298;
static NODE *string__714d8e0e161a038f;
static void cont__2_513(void);
static NODE *string__724c23a6148be573;
static NODE *string__9b761c44b7e5eaec;
static void cont__2_516(void);
static NODE *string__724c23a6149be577;
static NODE *string__9b779c44f7e5fae6;
static void cont__2_519(void);
static NODE *string__724c23a614b3e571;
static NODE *string__9b761c4457e5e2ec;
static void cont__2_522(void);
static NODE *string__3730b49a2bb3f253;
static NODE *string__96187ba7d2aab9e;
static void cont__2_525(void);
static NODE *string__b6540e1515c13096;
static NODE *string__eab0567a680d7e49;
static void cont__2_528(void);
static NODE *string__261f540a81caa2a3;
static NODE *string__4ed36036cf5d9072;
static void cont__2_531(void);
static NODE *string__aa540e1515c9309d;
static NODE *string__eb940de21eba7011;
static void cont__2_534(void);
static NODE *string__444c262e96638520;
static NODE *string__348e2dcbe014e084;
static void cont__2_537(void);
static NODE *string__a4214b121078eb22;
static NODE *string__2a2e177196a0d458;
static void cont__2_540(void);
static NODE *string__464c27eb16a34536;
static NODE *string__21cd69a400bae74a;
static void cont__2_543(void);
static NODE *string__5af91691bb71fca7;
static NODE *string__f5570b383c3fc00;
static void cont__2_546(void);
static NODE *string__7e88296f0e7a3463;
static NODE *string__310f62774c0e0007;
static void cont__2_549(void);
static NODE *string__541f558a01dab2b3;
static NODE *string__aa90620e046f416c;
static void cont__2_552(void);
static NODE *string__ee216a04cf7d466f;
static NODE *string__b1d91f87cca0e731;
static void cont__2_555(void);
static NODE *string__d06e9dd63b47a743;
static NODE *string__7a5cedaec36476fb;
static void cont__2_558(void);
static NODE *string__c63b2d1935e6c40b;
static NODE *string__679ea7d4aa3dc62e;
static void cont__2_561(void);
static NODE *string__de8d76bddd0e0c7c;
static NODE *string__33b3c02b144305e5;
static void cont__2_564(void);
static NODE *string__c63b2c5935e6c40b;
static NODE *string__461472315ebaff5f;
static void cont__2_567(void);
static NODE *string__d22f03c332cbb7fe;
static NODE *string__14bb178f7122cfd7;
static void cont__2_570(void);
static NODE *string__2e96a85fa636061f;
static NODE *string__dab898fd6ccb94af;
static void cont__2_573(void);
static NODE *string__704f98350e6d5307;
static NODE *string__cb62ccbfd0ebcc01;
static void cont__2_576(void);
static NODE *string__aafd8832303424db;
static NODE *string__d0c86ff26de9d846;
static void cont__2_579(void);
static NODE *string__ee96b05fb53605bb;
static NODE *string__96b8997d6dfb9495;
static void cont__2_582(void);
static NODE *string__a0fda8722d0624db;
static NODE *string__c4688fdba679a3d7;
static void cont__2_585(void);
static NODE *string__ee96a85fa636041b;
static NODE *string__96b898fd6ccb948f;
static void cont__2_588(void);
static NODE *string__154106450b6484c7;
static NODE *string__48ac73a2bb0fdab2;
static void cont__2_591(void);
static NODE *string__14c18e250b6884c0;
static NODE *string__4b2cb3e68b0fdcb2;
static void cont__2_594(void);
static NODE *string__f85036d3d94a7bb1;
static NODE *string__1e649a8a52a00dac;
static void cont__2_597(void);
static NODE *string__32502858b6554c7;
static NODE *string__ba7ab002426e2e85;
static void cont__2_600(void);
static NODE *string__2a58ae58b6954c0;
static NODE *string__aabab01a42602d84;
static void cont__2_603(void);
static NODE *string__ee343213594babb1;
static NODE *string__fc70de4897612997;
static void cont__2_606(void);
static NODE *string__4f8263ad80b7c630;
static NODE *string__ac28eb4056636d1;
static void cont__2_609(void);
static NODE *string__4f8463ae00778200;
static NODE *string__6c6cdb4050636e9;
static void cont__2_612(void);
static NODE *string__26951c16f63f5e7b;
static NODE *string__8aa183bf30fdb669;
static void cont__2_615(void);
static NODE *string__f75531ddca48c11b;
static NODE *string__1061572abef9f5fc;
static void cont__2_618(void);
static NODE *string__f455301daa6ad91b;
static NODE *string__c67550b3ef9c5fc;
static void cont__2_621(void);
static NODE *string__7ceaec668e04e4af;
static NODE *string__f527cb3955e59def;
static void cont__2_624(void);
static NODE *string__9896a2e6a0f80170;
static NODE *string__b813d7b89495bd97;
static void cont__2_627(void);
static NODE *string__189642d6b1f40171;
static NODE *string__a91fd7b914955da7;
static void cont__2_630(void);
static NODE *string__47787f4486eadb35;
static NODE *string__71f6bf6cf0c52b77;
static void cont__2_633(void);
static NODE *string__3ee8582926d9080f;
static NODE *string__b566653efe8d5564;
static void cont__2_636(void);
static NODE *string__7de8584926e1040b;
static NODE *string__c57e6db8fe8d9564;
static void cont__2_639(void);
static NODE *string__ba5ec95edd6e6086;
static NODE *string__44e19d077543310d;
static void cont__2_642(void);
static NODE *string__324188e7a6ce34a6;
static NODE *string__cc612f10fbde1147;
static void cont__2_645(void);
static NODE *string__e68d0604b1c4e4d3;
static NODE *string__4e66b585b29bac7b;
static void cont__2_648(void);
static NODE *string__527f2a0eb4d2ad39;
static NODE *string__36dea3e52fa97601;
static void cont__2_651(void);
static NODE *string__db8268c5e3e3998;
static NODE *string__9cbbab858b1d3dd4;
static void cont__2_654(void);
static NODE *string__70926021f73890ec;
static NODE *string__6f29cd9643b48e9f;
static void cont__2_657(void);
static NODE *string__d7f67e3c0983d96f;
static NODE *string__312f4f711c0187b4;
static void cont__2_660(void);
static NODE *string__5df6e86d7cfc4b00;
static NODE *string__83170f4ed8417cf9;
static void cont__2_663(void);
static NODE *string__aa96dd5320f9062f;
static NODE *string__2524b8f70c096216;
static void cont__2_666(void);
static NODE *string__b621c02f863d5995;
static NODE *string__795f344f2e5fec15;
static void cont__2_669(void);
static NODE *string__4ff756961cfbc8e0;
static NODE *string__8ac552a1731f393c;
static void cont__2_672(void);
static NODE *string__83ece5deb5c6ec9d;
static NODE *string__b7c1a4c735435200;
static void cont__2_675(void);
static NODE *string__cb694aae4ed9216f;
static NODE *string__326ed43c2a8ea048;
static void cont__2_678(void);
static NODE *string__48e5e352d3af6668;
static NODE *string__f906962f4ff7a2cb;
static void cont__2_681(void);
static NODE *string__d891d349a6c69ea9;
static NODE *string__9d199eb4b8234323;
static void cont__2_684(void);
static NODE *string__463b2d2935e6c40f;
static NODE *string__c561b7f4ab9de03e;
static void cont__2_687(void);
static NODE *string__468da0192a6a5b6c;
static NODE *string__ca7b95abeb676984;
static void cont__2_690(void);
static NODE *string__d2bf386ef518fd14;
static NODE *string__9711b14735cfde06;
static void cont__2_693(void);
static NODE *string__7ba0bd51221b7d7f;
static NODE *string__4607d5e4ffb66756;
static void cont__2_696(void);
static NODE *string__5ba0bf1122037d67;
static NODE *string__4e07d574ffb06750;
static void cont__2_699(void);
static NODE *string__5ba0bf13a2037d67;
static NODE *string__e46df6740b141708;
static void cont__2_702(void);
static NODE *string__fe8d616be3f518cb;
static NODE *string__f248fe4622d2f5cc;
static void cont__2_705(void);
static NODE *string__de8d632be3ed18d3;
static NODE *string__f228fe26a2d2fccc;
static void cont__2_708(void);
static NODE *string__72f826ea16a3e460;
static NODE *string__43fa56dbd271ef60;
static void cont__2_711(void);
static NODE *string__b410089e951a909f;
static NODE *string__5637a81453ba364;
static void cont__2_714(void);
static NODE *string__d0118bd6a6b2ec04;
static NODE *string__736892f443d8da54;
static void cont__2_717(void);
static NODE *string__e9d1ecf31d50102f;
static NODE *string__29bf848cc7ceebf2;
static void cont__2_720(void);
static NODE *string__18e7723792748147;
static NODE *string__b1b21feb47ad3535;
static void cont__2_723(void);
static NODE *string__84879098faa5d2d;
static NODE *string__45b0ac293d6efdfa;
static void cont__2_726(void);
static NODE *string__8edd0c0616b76781;
static NODE *string__5745a2890b84b4b9;
static void cont__2_729(void);
static NODE *string__3d280d5fb44085d1;
static NODE *string__ed53ddd7ccc24cb5;
static void cont__2_732(void);
static void cont__2_733(void);
void run__runtime_definitions(void);

static CONTINUATION_INFO continuation_info[] = {
  {run__runtime_definitions, NULL, 24, 29, 5, 12},
  {cont__2_3, NULL, 30, 35, 5, 12},
  {cont__2_6, NULL, 36, 43, 5, 17},
  {cont__2_9, NULL, 44, 45, 5, 53},
  {cont__2_12, NULL, 46, 47, 5, 47},
  {cont__2_15, NULL, 48, 49, 5, 43},
  {cont__2_18, NULL, 50, 55, 5, 19},
  {cont__2_21, NULL, 56, 57, 5, 38},
  {cont__2_24, NULL, 58, 59, 5, 38},
  {cont__2_27, NULL, 60, 61, 5, 33},
  {cont__2_30, NULL, 62, 63, 5, 37},
  {cont__2_33, NULL, 64, 65, 5, 49},
  {cont__2_36, NULL, 66, 67, 5, 46},
  {cont__2_39, NULL, 68, 69, 5, 40},
  {cont__2_42, NULL, 70, 71, 5, 51},
  {cont__2_45, NULL, 72, 73, 5, 51},
  {cont__2_48, NULL, 74, 75, 5, 56},
  {cont__2_51, NULL, 76, 77, 5, 31},
  {cont__2_54, NULL, 78, 79, 5, 30},
  {cont__2_57, NULL, 80, 81, 5, 32},
  {cont__2_60, NULL, 82, 83, 5, 36},
  {cont__2_63, NULL, 84, 85, 5, 38},
  {cont__2_66, NULL, 86, 87, 5, 38},
  {cont__2_69, NULL, 88, 89, 5, 36},
  {cont__2_72, NULL, 90, 91, 5, 47},
  {cont__2_75, NULL, 92, 93, 5, 43},
  {cont__2_78, NULL, 94, 95, 5, 43},
  {cont__2_81, NULL, 96, 97, 5, 59},
  {cont__2_84, NULL, 98, 99, 5, 62},
  {cont__2_87, NULL, 100, 101, 5, 53},
  {cont__2_90, NULL, 102, 103, 5, 51},
  {cont__2_93, NULL, 104, 105, 5, 59},
  {cont__2_96, NULL, 106, 107, 5, 70},
  {cont__2_99, NULL, 108, 109, 5, 82},
  {cont__2_102, NULL, 110, 114, 5, 8},
  {cont__2_105, NULL, 115, 119, 5, 8},
  {cont__2_108, NULL, 120, 124, 5, 8},
  {cont__2_111, NULL, 125, 129, 5, 8},
  {cont__2_114, NULL, 130, 134, 5, 8},
  {cont__2_117, NULL, 135, 136, 5, 39},
  {cont__2_120, NULL, 137, 142, 5, 8},
  {cont__2_123, NULL, 143, 148, 5, 8},
  {cont__2_126, NULL, 149, 152, 5, 8},
  {cont__2_129, NULL, 153, 157, 5, 8},
  {cont__2_132, NULL, 158, 162, 5, 8},
  {cont__2_135, NULL, 163, 166, 5, 8},
  {cont__2_138, NULL, 167, 171, 5, 8},
  {cont__2_141, NULL, 172, 176, 5, 8},
  {cont__2_144, NULL, 177, 181, 5, 8},
  {cont__2_147, NULL, 182, 186, 5, 8},
  {cont__2_150, NULL, 187, 188, 5, 33},
  {cont__2_153, NULL, 189, 190, 5, 36},
  {cont__2_156, NULL, 191, 192, 5, 30},
  {cont__2_159, NULL, 193, 194, 5, 33},
  {cont__2_162, NULL, 195, 196, 5, 41},
  {cont__2_165, NULL, 197, 198, 5, 42},
  {cont__2_168, NULL, 199, 200, 5, 38},
  {cont__2_171, NULL, 201, 202, 5, 41},
  {cont__2_174, NULL, 203, 226, 5, 15},
  {cont__2_177, NULL, 227, 230, 5, 15},
  {cont__2_180, NULL, 231, 235, 5, 19},
  {cont__2_183, NULL, 236, 239, 5, 17},
  {cont__2_186, NULL, 240, 244, 5, 20},
  {cont__2_189, NULL, 245, 251, 5, 16},
  {cont__2_192, NULL, 252, 257, 5, 17},
  {cont__2_195, NULL, 258, 266, 5, 21},
  {cont__2_198, NULL, 267, 272, 5, 23},
  {cont__2_201, NULL, 273, 283, 5, 15},
  {cont__2_204, NULL, 284, 289, 5, 13},
  {cont__2_207, NULL, 290, 297, 5, 14},
  {cont__2_210, NULL, 298, 302, 5, 19},
  {cont__2_213, NULL, 303, 313, 5, 26},
  {cont__2_216, NULL, 314, 325, 5, 20},
  {cont__2_219, NULL, 326, 331, 5, 20},
  {cont__2_222, NULL, 332, 337, 5, 21},
  {cont__2_225, NULL, 338, 343, 5, 26},
  {cont__2_228, NULL, 344, 345, 5, 45},
  {cont__2_231, NULL, 346, 347, 5, 43},
  {cont__2_234, NULL, 348, 349, 5, 39},
  {cont__2_237, NULL, 350, 351, 5, 36},
  {cont__2_240, NULL, 352, 353, 5, 39},
  {cont__2_243, NULL, 354, 355, 5, 23},
  {cont__2_246, NULL, 356, 357, 5, 25},
  {cont__2_249, NULL, 358, 359, 5, 20},
  {cont__2_252, NULL, 360, 361, 5, 23},
  {cont__2_255, NULL, 362, 363, 5, 30},
  {cont__2_258, NULL, 364, 365, 5, 19},
  {cont__2_261, NULL, 366, 367, 5, 27},
  {cont__2_264, NULL, 368, 369, 5, 28},
  {cont__2_267, NULL, 370, 371, 5, 32},
  {cont__2_270, NULL, 372, 373, 5, 26},
  {cont__2_273, NULL, 374, 375, 5, 30},
  {cont__2_276, NULL, 376, 377, 5, 22},
  {cont__2_279, NULL, 378, 379, 5, 17},
  {cont__2_282, NULL, 380, 381, 5, 25},
  {cont__2_285, NULL, 382, 383, 5, 26},
  {cont__2_288, NULL, 384, 385, 5, 25},
  {cont__2_291, NULL, 386, 387, 5, 41},
  {cont__2_294, NULL, 388, 389, 5, 35},
  {cont__2_297, NULL, 390, 391, 5, 35},
  {cont__2_300, NULL, 392, 393, 5, 35},
  {cont__2_303, NULL, 394, 395, 5, 35},
  {cont__2_306, NULL, 396, 397, 5, 35},
  {cont__2_309, NULL, 398, 399, 5, 35},
  {cont__2_312, NULL, 400, 401, 5, 35},
  {cont__2_315, NULL, 402, 403, 5, 35},
  {cont__2_318, NULL, 404, 405, 5, 35},
  {cont__2_321, NULL, 406, 407, 5, 42},
  {cont__2_324, NULL, 408, 409, 5, 42},
  {cont__2_327, NULL, 410, 411, 5, 42},
  {cont__2_330, NULL, 412, 413, 5, 42},
  {cont__2_333, NULL, 414, 415, 5, 42},
  {cont__2_336, NULL, 416, 417, 5, 42},
  {cont__2_339, NULL, 418, 419, 5, 42},
  {cont__2_342, NULL, 420, 421, 5, 42},
  {cont__2_345, NULL, 422, 423, 5, 30},
  {cont__2_348, NULL, 424, 425, 5, 80},
  {cont__2_351, NULL, 426, 427, 5, 64},
  {cont__2_354, NULL, 428, 429, 5, 71},
  {cont__2_357, NULL, 430, 431, 5, 32},
  {cont__2_360, NULL, 432, 433, 5, 42},
  {cont__2_363, NULL, 434, 435, 5, 41},
  {cont__2_366, NULL, 436, 437, 5, 55},
  {cont__2_369, NULL, 438, 439, 5, 35},
  {cont__2_372, NULL, 440, 441, 5, 36},
  {cont__2_375, NULL, 442, 443, 5, 38},
  {cont__2_378, NULL, 444, 445, 5, 77},
  {cont__2_381, NULL, 446, 447, 5, 71},
  {cont__2_384, NULL, 448, 449, 5, 38},
  {cont__2_387, NULL, 450, 451, 5, 40},
  {cont__2_390, NULL, 452, 453, 5, 45},
  {cont__2_393, NULL, 454, 455, 5, 50},
  {cont__2_396, NULL, 456, 457, 5, 30},
  {cont__2_399, NULL, 458, 459, 5, 30},
  {cont__2_402, NULL, 460, 461, 5, 46},
  {cont__2_405, NULL, 462, 463, 5, 74},
  {cont__2_408, NULL, 464, 465, 5, 41},
  {cont__2_411, NULL, 466, 467, 5, 42},
  {cont__2_414, NULL, 468, 469, 5, 41},
  {cont__2_417, NULL, 470, 471, 5, 39},
  {cont__2_420, NULL, 472, 473, 5, 40},
  {cont__2_423, NULL, 474, 475, 5, 39},
  {cont__2_426, NULL, 476, 477, 5, 37},
  {cont__2_429, NULL, 478, 479, 5, 38},
  {cont__2_432, NULL, 480, 481, 5, 43},
  {cont__2_435, NULL, 482, 483, 5, 34},
  {cont__2_438, NULL, 484, 485, 5, 35},
  {cont__2_441, NULL, 486, 487, 5, 32},
  {cont__2_444, NULL, 488, 489, 5, 26},
  {cont__2_447, NULL, 490, 491, 5, 36},
  {cont__2_450, NULL, 492, 493, 5, 36},
  {cont__2_453, NULL, 494, 495, 5, 36},
  {cont__2_456, NULL, 496, 497, 5, 24},
  {cont__2_459, NULL, 498, 499, 5, 63},
  {cont__2_462, NULL, 500, 501, 5, 52},
  {cont__2_465, NULL, 502, 503, 5, 46},
  {cont__2_468, NULL, 504, 505, 5, 37},
  {cont__2_471, NULL, 506, 507, 5, 61},
  {cont__2_474, NULL, 508, 509, 5, 61},
  {cont__2_477, NULL, 510, 511, 5, 51},
  {cont__2_480, NULL, 512, 513, 5, 36},
  {cont__2_483, NULL, 514, 515, 5, 29},
  {cont__2_486, NULL, 516, 517, 5, 47},
  {cont__2_489, NULL, 518, 519, 5, 55},
  {cont__2_492, NULL, 520, 521, 5, 70},
  {cont__2_495, NULL, 522, 523, 5, 81},
  {cont__2_498, NULL, 524, 525, 5, 35},
  {cont__2_501, NULL, 526, 527, 5, 36},
  {cont__2_504, NULL, 528, 529, 5, 36},
  {cont__2_507, NULL, 530, 531, 5, 36},
  {cont__2_510, NULL, 532, 533, 5, 36},
  {cont__2_513, NULL, 534, 535, 5, 37},
  {cont__2_516, NULL, 536, 537, 5, 37},
  {cont__2_519, NULL, 538, 539, 5, 37},
  {cont__2_522, NULL, 540, 541, 5, 38},
  {cont__2_525, NULL, 542, 543, 5, 30},
  {cont__2_528, NULL, 544, 545, 5, 29},
  {cont__2_531, NULL, 546, 547, 5, 31},
  {cont__2_534, NULL, 548, 549, 5, 35},
  {cont__2_537, NULL, 550, 551, 5, 36},
  {cont__2_540, NULL, 552, 553, 5, 51},
  {cont__2_543, NULL, 554, 555, 5, 46},
  {cont__2_546, NULL, 556, 557, 5, 33},
  {cont__2_549, NULL, 558, 559, 5, 30},
  {cont__2_552, NULL, 560, 561, 5, 74},
  {cont__2_555, NULL, 562, 563, 5, 37},
  {cont__2_558, NULL, 564, 565, 5, 47},
  {cont__2_561, NULL, 566, 567, 5, 39},
  {cont__2_564, NULL, 568, 569, 5, 70},
  {cont__2_567, NULL, 570, 571, 5, 76},
  {cont__2_570, NULL, 572, 573, 5, 43},
  {cont__2_573, NULL, 574, 575, 5, 48},
  {cont__2_576, NULL, 576, 577, 5, 44},
  {cont__2_579, NULL, 578, 579, 5, 43},
  {cont__2_582, NULL, 580, 581, 5, 43},
  {cont__2_585, NULL, 582, 583, 5, 43},
  {cont__2_588, NULL, 584, 585, 5, 37},
  {cont__2_591, NULL, 586, 587, 5, 37},
  {cont__2_594, NULL, 588, 589, 5, 43},
  {cont__2_597, NULL, 590, 591, 5, 35},
  {cont__2_600, NULL, 592, 593, 5, 35},
  {cont__2_603, NULL, 594, 595, 5, 41},
  {cont__2_606, NULL, 596, 597, 5, 41},
  {cont__2_609, NULL, 598, 599, 5, 41},
  {cont__2_612, NULL, 600, 601, 5, 47},
  {cont__2_615, NULL, 602, 603, 5, 54},
  {cont__2_618, NULL, 604, 605, 5, 54},
  {cont__2_621, NULL, 606, 607, 5, 44},
  {cont__2_624, NULL, 608, 609, 5, 55},
  {cont__2_627, NULL, 610, 611, 5, 55},
  {cont__2_630, NULL, 612, 613, 5, 45},
  {cont__2_633, NULL, 614, 615, 5, 44},
  {cont__2_636, NULL, 616, 617, 5, 44},
  {cont__2_639, NULL, 618, 619, 5, 44},
  {cont__2_642, NULL, 620, 621, 5, 54},
  {cont__2_645, NULL, 622, 623, 5, 53},
  {cont__2_648, NULL, 624, 625, 5, 44},
  {cont__2_651, NULL, 626, 627, 5, 41},
  {cont__2_654, NULL, 628, 629, 5, 38},
  {cont__2_657, NULL, 630, 631, 5, 58},
  {cont__2_660, NULL, 632, 633, 5, 48},
  {cont__2_663, NULL, 634, 635, 5, 32},
  {cont__2_666, NULL, 636, 637, 5, 58},
  {cont__2_669, NULL, 638, 639, 5, 51},
  {cont__2_672, NULL, 640, 641, 5, 57},
  {cont__2_675, NULL, 642, 643, 5, 57},
  {cont__2_678, NULL, 644, 645, 5, 48},
  {cont__2_681, NULL, 646, 647, 5, 54},
  {cont__2_684, NULL, 648, 649, 5, 60},
  {cont__2_687, NULL, 650, 651, 5, 30},
  {cont__2_690, NULL, 652, 653, 5, 54},
  {cont__2_693, NULL, 654, 655, 5, 37},
  {cont__2_696, NULL, 656, 657, 5, 37},
  {cont__2_699, NULL, 658, 659, 5, 48},
  {cont__2_702, NULL, 660, 661, 5, 51},
  {cont__2_705, NULL, 662, 663, 5, 51},
  {cont__2_708, NULL, 664, 665, 5, 36},
  {cont__2_711, NULL, 666, 667, 5, 58},
  {cont__2_714, NULL, 668, 669, 5, 43},
  {cont__2_717, NULL, 670, 671, 5, 66},
  {cont__2_720, NULL, 672, 677, 5, 22},
  {cont__2_723, NULL, 678, 683, 5, 20},
  {cont__2_726, NULL, 684, 687, 5, 8},
  {cont__2_729, NULL, 688, 689, 5, 28},
  {cont__2_732, NULL, 22, 689, 1, 30},
  {cont__2_733, NULL, }
};

union NODE {
  struct {
    FUNC type;
    ATTRIBUTES *attributes;
  };
  CONTINUATION continuation;
  CLOSURE closure;
};

static const char *used_namespaces[] = {
  "std",
  NULL
};

static MODULE_INFO module_info = {
  NULL,
  "runtime_definitions",
  continuation_info,
  sizeof(continuation_info)/sizeof(CONTINUATION_INFO),
  (NODE **)&var,
  var_names,
  sizeof(var_names)/sizeof(const char *),
  used_namespaces,
  {DEBUG_FILENAME("runtime_definitions.sim")}
};

/******
C O D E
******/

static int already_run = false;

EXPORT void run__runtime_definitions(void) {
  if (already_run) {
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  already_run = true;
  allocate_initialized_frame_gc(0, 244);
  // 24: "ASM" = "
  // 25:   #if defined(__GNUC__) && !defined(__clang__) && defined(__x86_64)
  // 26:     #define ASM(x) asm(x)
  // 27:   #else
  // 28:     #define ASM(x)
  // 29:   #endif
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__fa728015cb16b81;
  arguments->slots[1] = string__8edd415ac72451d0;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_3;
}
static void cont__2_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 30: "REGISTER" = "
  // 31:   #if defined(__GNUC__) && !defined(__clang__) && defined(__x86_64)
  // 32:     #define REGISTER register
  // 33:   #else
  // 34:     #define REGISTER IMPORT
  // 35:   #endif
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__800a0c585ff0632;
  arguments->slots[1] = string__5c95584625416db4;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_6;
}
static void cont__2_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 36: "VAR_TYPE" = "
  // 37:   typedef enum {
  // 38:     VT_POLYMORPHIC,
  // 39:     VT_SINGLE_ASSIGN_STATIC,
  // 40:     VT_MULTI_ASSIGN_STATIC,
  // 41:     VT_SINGLE_ASSIGN_DYNAMIC,
  // 42:     VT_MULTI_ASSIGN_DYNAMIC,
  // 43:   } VAR_TYPE;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__610a38f055666a5;
  arguments->slots[1] = string__3e779bba71ff6e96;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_9;
}
static void cont__2_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 44: "ATTRIBUTE_ENTRY" = "
  // 45:   typedef struct ATTRIBUTE_ENTRY ATTRIBUTE_ENTRY;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__1580bcaf2d42dade;
  arguments->slots[1] = string__56c3d0662f712784;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_12;
}
static void cont__2_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 46: "SYMBOL_ENTRY" = "
  // 47:   typedef struct SYMBOL_ENTRY SYMBOL_ENTRY;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__966c1d52f9f0535e;
  arguments->slots[1] = string__9f2336b788df6407;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_15;
}
static void cont__2_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__5 */ = arguments->slots[0];
  // 48: "HASH_ENTRY" = "
  // 49:   typedef struct HASH_ENTRY HASH_ENTRY;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__69c55d0406b923b8;
  arguments->slots[1] = string__fc5ea67cb9ff6239;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_18;
}
static void cont__2_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__6 */ = arguments->slots[0];
  // 50: "C_FUNCTION" = "
  // 51:   typedef struct {
  // 52:     const char *name;
  // 53:     void **func;
  // 54:     const char *module_name;
  // 55:   } C_FUNCTION;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__5db1024c9851410f;
  arguments->slots[1] = string__a1dd1a49069005db;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_21;
}
static void cont__2_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__7 */ = arguments->slots[0];
  // 56: "runtime_major_version" = "
  // 57:   int runtime_major_version(void);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__786504f5b93f55fd;
  arguments->slots[1] = string__86acba43b7c3c22a;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_24;
}
static void cont__2_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__8 */ = arguments->slots[0];
  // 58: "runtime_minor_version" = "
  // 59:   int runtime_minor_version(void);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__786504f5b92f55fc;
  arguments->slots[1] = string__86acaa43b6c3c22a;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_27;
}
static void cont__2_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__9 */ = arguments->slots[0];
  // 60: "runtime_revision" = "
  // 61:   int runtime_revision(void);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__7690e6a93c025e80;
  arguments->slots[1] = string__f62e6c6074331b2f;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_30;
}
static void cont__2_30(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__10 */ = arguments->slots[0];
  // 62: "polymorphic_function_count" = "
  // 63:   int polymorphic_function_count;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__a8d3ab331eb668e7;
  arguments->slots[1] = string__bdeaeb384def5a1;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_33;
}
static void cont__2_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__11 */ = arguments->slots[0];
  // 64: "polymorphic_function_with_setter_count" = "
  // 65:   int polymorphic_function_with_setter_count;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__77b931a5baaa8bfc;
  arguments->slots[1] = string__b46169d78bdd1cff;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_36;
}
static void cont__2_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__12 */ = arguments->slots[0];
  // 66: "polymorphic_function_names" = "
  // 67:   const char **polymorphic_function_names;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__b4d3ad331eeeb8e0;
  arguments->slots[1] = string__301d5357b968136a;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_39;
}
static void cont__2_39(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__13 */ = arguments->slots[0];
  // 68: "set_module" = "
  // 69:   void set_module(const char *name);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__3d988d5d234b8764;
  arguments->slots[1] = string__1a135fbcb802cc05;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_42;
}
static void cont__2_42(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__14 */ = arguments->slots[0];
  // 70: "register_module_info" = "
  // 71:   void register_module_info(MODULE_INFO *info);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__dc6342966f81738c;
  arguments->slots[1] = string__6777bcdceff69976;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_45;
}
static void cont__2_45(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[14] /* temp__15 */ = arguments->slots[0];
  // 72: "define_namespace" = "
  // 73:   void define_namespace(const char *namespace);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__74b135724d6dbce9;
  arguments->slots[1] = string__3ef83756322d0f8;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_48;
}
static void cont__2_48(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[15] /* temp__16 */ = arguments->slots[0];
  // 74: "set_used_namespaces" = "
  // 75:   void set_used_namespaces(const char **namespaces);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__51af6105266784c5;
  arguments->slots[1] = string__6e38e34fa7ce2068;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_51;
}
static void cont__2_51(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[16] /* temp__17 */ = arguments->slots[0];
  // 76: "from_bool" = "
  // 77:   NODE *from_bool(int val);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__6a8c256a04788689;
  arguments->slots[1] = string__3e6f7d71ebbc1fd7;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_54;
}
static void cont__2_54(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[17] /* temp__18 */ = arguments->slots[0];
  // 78: "from_int" = "
  // 79:   NODE *from_int(int val);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__10dcaf9184a54094;
  arguments->slots[1] = string__9d29beb6e8094e17;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_57;
}
static void cont__2_57(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[18] /* temp__19 */ = arguments->slots[0];
  // 80: "from_long" = "
  // 81:   NODE *from_long(long val);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__768c256a04708682;
  arguments->slots[1] = string__205751daa5312b90;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_60;
}
static void cont__2_60(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[19] /* temp__20 */ = arguments->slots[0];
  // 82: "from_int64" = "
  // 83:   NODE *from_int64(int64_t val);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__29502504369be455;
  arguments->slots[1] = string__2e6aba362d00a1da;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_63;
}
static void cont__2_63(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[20] /* temp__21 */ = arguments->slots[0];
  // 84: "from_uint32" = "
  // 85:   NODE *from_uint32(uint32_t val);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__1c21a45122913ab3;
  arguments->slots[1] = string__91b47fced47c61e2;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_66;
}
static void cont__2_66(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[21] /* temp__22 */ = arguments->slots[0];
  // 86: "from_uint64" = "
  // 87:   NODE *from_uint64(uint64_t val);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__1c21a45122b93ab5;
  arguments->slots[1] = string__d1b24fced47c61cb;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_69;
}
static void cont__2_69(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[22] /* temp__23 */ = arguments->slots[0];
  // 88: "from_double" = "
  // 89:   NODE *from_double(double val);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2a21a1d9a0695ae4;
  arguments->slots[1] = string__cebc109d1e7797e2;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_72;
}
static void cont__2_72(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[23] /* temp__24 */ = arguments->slots[0];
  // 90: "from_digit_string" = "
  // 91:   NODE *from_digit_string(const char *str);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__f7822ff0f11c2c3;
  arguments->slots[1] = string__290e2a52fea6fc66;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_75;
}
static void cont__2_75(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[24] /* temp__25 */ = arguments->slots[0];
  // 92: "from_uchar32" = "
  // 93:   NODE *from_uchar32(unsigned int chr);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__88904ccd590813f;
  arguments->slots[1] = string__b475c09adc8d6659;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_78;
}
static void cont__2_78(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[25] /* temp__26 */ = arguments->slots[0];
  // 94: "from_c_string" = "
  // 95:   NODE *from_c_string(const char *str);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2696ba098b1916ef;
  arguments->slots[1] = string__7be49ac3d7efe7a6;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_81;
}
static void cont__2_81(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[26] /* temp__27 */ = arguments->slots[0];
  // 96: "from_latin_1_string" = "
  // 97:   NODE *from_latin_1_string(const char *str, long len);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__f8dc63c35d5f67e4;
  arguments->slots[1] = string__bb39174a4b655c1c;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_84;
}
static void cont__2_84(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[27] /* temp__28 */ = arguments->slots[0];
  // 98: "from_uint32_string" = "
  // 99:   NODE *from_uint32_string(const uint32_t *str, long len);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__6148905dd1501604;
  arguments->slots[1] = string__c2bd832925dd7b1c;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_87;
}
static void cont__2_87(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[28] /* temp__29 */ = arguments->slots[0];
  // 100: "from_arguments" = "
  // 101:   NODE *from_arguments(int first_idx, int count);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__c81c58c835e0c166;
  arguments->slots[1] = string__f28c00dfeab5a4f5;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_90;
}
static void cont__2_90(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[29] /* temp__30 */ = arguments->slots[0];
  // 102: "register_unique_item" = "
  // 103:   NODE *register_unique_item(const char *name);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__dc074c1662997308;
  arguments->slots[1] = string__ecd63bf007719c5e;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_93;
}
static void cont__2_93(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[30] /* temp__31 */ = arguments->slots[0];
  // 104: "define_c_function" = "
  // 105:   void define_c_function(const char *name, void *func);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__81d201e3591a9487;
  arguments->slots[1] = string__bd156810a3b87b39;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_96;
}
static void cont__2_96(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[31] /* temp__32 */ = arguments->slots[0];
  // 106: "register_polymorphic_function" = "
  // 107:   void register_polymorphic_function(const char *name, int *id_p);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__34c427046666a791;
  arguments->slots[1] = string__1852e8fc677301ab;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_99;
}
static void cont__2_99(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[32] /* temp__33 */ = arguments->slots[0];
  // 108: "register_polymorphic_function_with_setter" = "
  // 109:   void register_polymorphic_function_with_setter(const char *name, int *id_p);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__4f152c2abbd22d29;
  arguments->slots[1] = string__b2c113b0186c2dd1;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_102;
}
static void cont__2_102(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[33] /* temp__34 */ = arguments->slots[0];
  // 110: "define_polymorphic_function" = "
  // 111:   void define_polymorphic_function(
  // 112:     const char *namespace, const char *name, NODE_GETTER getter, int *id_p,
  // 113:     NODE **var_p
  // 114:   );
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__caafa59fe636a9de;
  arguments->slots[1] = string__e4d263547623cea0;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_105;
}
static void cont__2_105(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[34] /* temp__35 */ = arguments->slots[0];
  // 115: "define_polymorphic_function_with_setter" = "
  // 116:   void define_polymorphic_function_with_setter(
  // 117:     const char *namespace, const char *name, NODE_GETTER getter, int *id_p,
  // 118:     NODE **var_p
  // 119:   );
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__4a15c8d55d6a0491;
  arguments->slots[1] = string__21c0f79678df3c50;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_108;
}
static void cont__2_108(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[35] /* temp__36 */ = arguments->slots[0];
  // 120: "define_privileged_polymorphic_function" = "
  // 121:   void define_privileged_polymorphic_function(
  // 122:     const char *namespace, const char *name, NODE_GETTER getter, int id,
  // 123:     NODE **var_p
  // 124:   );
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2d9e9f5fd5d9523e;
  arguments->slots[1] = string__6445dfc09129e2bc;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_111;
}
static void cont__2_111(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[36] /* temp__37 */ = arguments->slots[0];
  // 125: "define_single_assign_static" = "
  // 126:   void define_single_assign_static(
  // 127:     const char *namespace, const char *name,
  // 128:     NODE_GETTER getter, NODE **var_p
  // 129:   );
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__7699f5c17fb1f0c5;
  arguments->slots[1] = string__bd51ec8ac074a909;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_114;
}
static void cont__2_114(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[37] /* temp__38 */ = arguments->slots[0];
  // 130: "define_multi_assign_static" = "
  // 131:   void define_multi_assign_static(
  // 132:     const char *namespace, const char *name,
  // 133:     NODE_GETTER getter, NODE_SETTER setter
  // 134:   );
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__9d2186757f44a3c;
  arguments->slots[1] = string__d8100904e5447128;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_117;
}
static void cont__2_117(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[38] /* temp__39 */ = arguments->slots[0];
  // 135: "register_dynamic" = "
  // 136:   void register_dynamic(int *id_p);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__1614e67e91066b2b;
  arguments->slots[1] = string__da679ac2fd23801b;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_120;
}
static void cont__2_120(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[39] /* temp__40 */ = arguments->slots[0];
  // 137: "define_single_assign_dynamic" = "
  // 138:   void define_single_assign_dynamic(
  // 139:     const char *namespace, const char *name,
  // 140:     NODE_GETTER getter, NODE_SETTER definer,
  // 141:     int *id_p
  // 142:   );
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__8457fc89067b44ac;
  arguments->slots[1] = string__8d9a40a45ca1f46;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_123;
}
static void cont__2_123(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[40] /* temp__41 */ = arguments->slots[0];
  // 143: "define_multi_assign_dynamic" = "
  // 144:   void define_multi_assign_dynamic(
  // 145:     const char *namespace, const char *name,
  // 146:     NODE_GETTER getter, NODE_SETTER setter, NODE_SETTER definer,
  // 147:     int *id_p
  // 148:   );
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__e966bea4d1b0bef3;
  arguments->slots[1] = string__4203ade7496d3cba;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_126;
}
static void cont__2_126(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[41] /* temp__42 */ = arguments->slots[0];
  // 149: "define_type_function" = "
  // 150:   void define_type_function(
  // 151:     const char *namespace, const char *name, FUNC type, int par_cnt
  // 152:   );
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__bb073f307486f5e2;
  arguments->slots[1] = string__d8ae744927741c5e;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_129;
}
static void cont__2_129(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[42] /* temp__43 */ = arguments->slots[0];
  // 153: "define_attribute" = "
  // 154:   void define_attribute(
  // 155:     const char *namespace, const char *name,
  // 156:     int id, NODE *attribute
  // 157:   );
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__50d53079c2d41e49;
  arguments->slots[1] = string__d699aac52d63a802;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_132;
}
static void cont__2_132(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[43] /* temp__44 */ = arguments->slots[0];
  // 158: "define_method" = "
  // 159:   void define_method(
  // 160:     const char *namespace, const char *name,
  // 161:     int id, NODE *method
  // 162:   );
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__6a969a66ba3e062e;
  arguments->slots[1] = string__3ca1e27da11d6a79;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_135;
}
static void cont__2_135(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[44] /* temp__45 */ = arguments->slots[0];
  // 163: "use_polymorphic_function" = "
  // 164:   void use_polymorphic_function(
  // 165:     const char *namespace, const char *name, NODE_GETTER *getter, int *id
  // 166:   );
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__f22e4ba252bb0402;
  arguments->slots[1] = string__cd13cee030a4034b;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_138;
}
static void cont__2_138(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[45] /* temp__46 */ = arguments->slots[0];
  // 167: "use_read_only" = "
  // 168:   void use_read_only(
  // 169:     const char *namespace, const char *name,
  // 170:     NODE_GETTER *getter, NODE_GETTER *get_value_or_future
  // 171:   );
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__9c6f2af22609a633;
  arguments->slots[1] = string__b5cfa062437d6535;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_141;
}
static void cont__2_141(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[46] /* temp__47 */ = arguments->slots[0];
  // 172: "use_read_write" = "
  // 173:   void use_read_write(
  // 174:     const char *namespace, const char *name,
  // 175:     NODE_GETTER *getter, NODE_SETTER *setter
  // 176:   );
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__6f91310d31f5631c;
  arguments->slots[1] = string__5ca1f7a22b3232c2;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_144;
}
static void cont__2_144(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[47] /* temp__48 */ = arguments->slots[0];
  // 177: "use_single_assign_dynamic" = "
  // 178:   void use_single_assign_dynamic(
  // 179:     const char *namespace, const char *name,
  // 180:     NODE_GETTER *getter, NODE_SETTER *definer
  // 181:   );
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__f5ba58e4689a80a3;
  arguments->slots[1] = string__d107ad9b7b630943;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_147;
}
static void cont__2_147(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[48] /* temp__49 */ = arguments->slots[0];
  // 182: "use_multi_assign_dynamic" = "
  // 183:   void use_multi_assign_dynamic(
  // 184:     const char *namespace, const char *name,
  // 185:     NODE_GETTER *getter, NODE_SETTER *setter, NODE_SETTER *definer
  // 186:   );
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__d1e75099653d132f;
  arguments->slots[1] = string__1eb9413f2d2e180c;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_150;
}
static void cont__2_150(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[49] /* temp__50 */ = arguments->slots[0];
  // 187: "resolve_symbols" = "
  // 188:   void resolve_symbols(void);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__15d9100c1cca979d;
  arguments->slots[1] = string__bd4383921548788;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_153;
}
static void cont__2_153(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[50] /* temp__51 */ = arguments->slots[0];
  // 189: "resolve_attributes" = "
  // 190:   void resolve_attributes(void);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__366b3f231611767c;
  arguments->slots[1] = string__cf523af04f93c1a2;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_156;
}
static void cont__2_156(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[51] /* temp__52 */ = arguments->slots[0];
  // 191: "NODE" = "
  // 192:   typedef union NODE NODE;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__5e0ae28b5c407d7c;
  arguments->slots[1] = string__8f20b7aa2b348ba;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_159;
}
static void cont__2_159(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[52] /* temp__53 */ = arguments->slots[0];
  // 193: "FUNC" = "
  // 194:   typedef void (*FUNC)(void);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__4e0ae40b5c107d7a;
  arguments->slots[1] = string__5ad1f0da53fa6a79;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_162;
}
static void cont__2_162(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[53] /* temp__54 */ = arguments->slots[0];
  // 195: "NODE_GETTER" = "
  // 196:   typedef NODE *(*NODE_GETTER)(void);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__682044480a23ffd9;
  arguments->slots[1] = string__c6ec8dca53a5a1af;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_165;
}
static void cont__2_165(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[54] /* temp__55 */ = arguments->slots[0];
  // 197: "NODE_SETTER" = "
  // 198:   typedef void (*NODE_SETTER)(NODE *);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__682044420a23ffd9;
  arguments->slots[1] = string__b8b9c6a2212e34c0;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_168;
}
static void cont__2_168(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[55] /* temp__56 */ = arguments->slots[0];
  // 199: "COLLECTOR" = "
  // 200:   typedef void *COLLECTOR(void *);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__28002bbaa0792117;
  arguments->slots[1] = string__9ae348be480e8e0;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_171;
}
static void cont__2_171(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[56] /* temp__57 */ = arguments->slots[0];
  // 201: "DESTRUCTOR" = "
  // 202:   typedef void (*DESTRUCTOR)(void *);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__73b53d02825023b3;
  arguments->slots[1] = string__b20c4a77a3ac08a2;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_174;
}
static void cont__2_174(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[57] /* temp__58 */ = arguments->slots[0];
  // 203: "VTABLE" = "
  // 204:   typedef struct VTABLE {
  // 205:     size_t size;
  // 206:     COLLECTOR *collect;
  // 207:     int8_t (*to_int8)(NODE *);
  // 208:     int16_t (*to_int16)(NODE *);
  // 209:     int32_t (*to_int32)(NODE *);
  // 210:     int64_t (*to_int64)(NODE *);
  // 211:     uint8_t (*to_uint8)(NODE *);
  // 212:     uint16_t (*to_uint16)(NODE *);
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__1a1f5edb80d91292;
  arguments->slots[1] = string__c4d379f2bb5c3e41;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_177;
}
static void cont__2_177(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[58] /* temp__59 */ = arguments->slots[0];
  // 227: "OCTREE" = "
  // 228:   typedef struct OCTREE {
  // 229:     struct OCTREE *nodes[8];
  // 230:   } OCTREE;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__301f5ad700906292;
  arguments->slots[1] = string__8106f1378366edc;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_180;
}
static void cont__2_180(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[59] /* temp__60 */ = arguments->slots[0];
  // 231: "ATTRIBUTES" = "
  // 232:   typedef struct ATTRIBUTES {
  // 233:     struct VTABLE *vtable;
  // 234:     struct OCTREE *nodes[7];
  // 235:   } ATTRIBUTES;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__5fad150f13015352;
  arguments->slots[1] = string__86e05501f2bf69ee;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_183;
}
static void cont__2_183(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[60] /* temp__61 */ = arguments->slots[0];
  // 236: "DYNAMICS" = "
  // 237:   typedef struct DYNAMICS {
  // 238:     struct OCTREE *nodes[8];
  // 239:   } DYNAMICS;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__3470a78105cf84f3;
  arguments->slots[1] = string__5dec1a1e2d91f421;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_186;
}
static void cont__2_186(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[61] /* temp__62 */ = arguments->slots[0];
  // 240: "SIMPLE_NODE" = "
  // 241:   typedef struct SIMPLE_NODE {
  // 242:     FUNC type;
  // 243:     struct ATTRIBUTES *attributes;
  // 244:   } SIMPLE_NODE;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__1c6c7289032a5d69;
  arguments->slots[1] = string__1dd5fa7b31b5023d;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_189;
}
static void cont__2_189(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[62] /* temp__63 */ = arguments->slots[0];
  // 245: "CLOSURE" = "
  // 246:   typedef struct CLOSURE {
  // 247:     FUNC type;
  // 248:     struct ATTRIBUTES *attributes;
  // 249:     int parameter_count;
  // 250:     struct FRAME *frame;
  // 251:   } CLOSURE;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__d4880084942830bf;
  arguments->slots[1] = string__6fd6eaaa0ae0aa48;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_192;
}
static void cont__2_192(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[63] /* temp__64 */ = arguments->slots[0];
  // 252: "FUNCTION" = "
  // 253:   typedef struct FUNCTION {
  // 254:     FUNC type;
  // 255:     struct ATTRIBUTES *attributes;
  // 256:     int parameter_count;
  // 257:   } FUNCTION;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__640a78105afa4ae;
  arguments->slots[1] = string__4e857cd3f4048898;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_195;
}
static void cont__2_195(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[64] /* temp__65 */ = arguments->slots[0];
  // 258: "CONTINUATION" = "
  // 259:   typedef struct CONTINUATION {
  // 260:     FUNC type;
  // 261:     struct ATTRIBUTES *attributes;
  // 262:     int result_count;
  // 263:     struct FRAME *frame;
  // 264:     struct DYNAMICS *dynamics;
  // 265:     struct FRAME *exit_frame; // used by exit-functions
  // 266:   } CONTINUATION;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__22640217ef38138c;
  arguments->slots[1] = string__aca6b18f1d890a7a;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_198;
}
static void cont__2_198(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[65] /* temp__66 */ = arguments->slots[0];
  // 267: "ATTRIBUTE_LIST" = "
  // 268:   typedef struct ATTRIBUTE_LIST {
  // 269:     struct ATTRIBUTE_LIST *link;
  // 270:     int idx;
  // 271:     void *attr;
  // 272:   } ATTRIBUTE_LIST;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__4950e37017ade5ae;
  arguments->slots[1] = string__196c75ae6866989e;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_201;
}
static void cont__2_201(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[66] /* temp__67 */ = arguments->slots[0];
  // 273: "FUTURE" = "
  // 274:   typedef struct FUTURE {
  // 275:     FUNC type;
  // 276:     struct ATTRIBUTES *attributes;
  // 277:     NODE *link;
  // 278:     struct ATTRIBUTE_LIST *pending_attributes;
  // 279:     NODE *dependent_futures;
  // 280:     NODE *prototype;
  // 281:     long is_already_initialized;
  // 282:     NODE *pad_2;
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__301f5b1380290292;
  arguments->slots[1] = string__998dcabeeeee256c;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_204;
}
static void cont__2_204(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[67] /* temp__68 */ = arguments->slots[0];
  // 284: "CELL" = "
  // 285:   typedef struct CELL {
  // 286:     FUNC type;
  // 287:     struct ATTRIBUTES *attributes;
  // 288:     NODE *contents;
  // 289:   } CELL;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__440ae00b5c007d75;
  arguments->slots[1] = string__552dc13bf9788e15;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_207;
}
static void cont__2_207(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[68] /* temp__69 */ = arguments->slots[0];
  // 290: "FRAME" = "
  // 291:   typedef struct FRAME {
  // 292:     FUNC cont;
  // 293:     struct FRAME *caller_frame;
  // 294:     long caller_result_count;
  // 295:     long slot_count;
  // 296:     NODE *slots[0];
  // 297:   } FRAME;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2e5ae343eba27012;
  arguments->slots[1] = string__18822595562573af;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_210;
}
static void cont__2_210(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[69] /* temp__70 */ = arguments->slots[0];
  // 298: "FRAME_INFO" = "
  // 299:   typedef struct FRAME_INFO {
  // 300:     int var_count;
  // 301:     const char *var_names[];
  // 302:   } FRAME_INFO;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__67d12b89151881ee;
  arguments->slots[1] = string__97eba66a53ce2418;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_213;
}
static void cont__2_213(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[70] /* temp__71 */ = arguments->slots[0];
  // 303: "CONTINUATION_INFO" = "
  // 304:   typedef struct CONTINUATION_INFO {
  // 305:     FUNC continuation;
  // 306:     struct FRAME_INFO *frame_info;
  // 307:     uint16_t first_line;
  // 308:     uint16_t last_line;
  // 309:     uint8_t first_column;
  // 310:     uint8_t last_column;
  // 311:     uint8_t submodule_index;
  // 312:     uint8_t unused;
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__659c1a461307f144;
  arguments->slots[1] = string__aff0e1bffd69d09e;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_216;
}
static void cont__2_216(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[71] /* temp__72 */ = arguments->slots[0];
  // 314: "MODULE_INFO" = "
  // 315:   typedef struct MODULE_INFO {
  // 316:     struct MODULE_INFO *link;
  // 317:     const char *name;
  // 318:     struct CONTINUATION_INFO *continuation_info;
  // 319:     int continuation_count;
  // 320:     NODE **var_tab;
  // 321:     const char **var_names;
  // 322:     int top_level_count;
  // 323:     const char **used_namespaces;
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__926c42c90a3a5dc4;
  arguments->slots[1] = string__35dcdd757d8ff36a;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_219;
}
static void cont__2_219(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[72] /* temp__73 */ = arguments->slots[0];
  // 326: "EVENT__MODE" = "
  // 327:   typedef enum {
  // 328:     EM__NORMAL,
  // 329:     EM__RECORD,
  // 330:     EM__REPLAY
  // 331:   } EVENT__MODE;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__9a0c8a840b2a5eac;
  arguments->slots[1] = string__699ad5fe935c0c;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_222;
}
static void cont__2_222(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[73] /* temp__74 */ = arguments->slots[0];
  // 332: "MEMORY_BLOCK" = "
  // 333:   typedef struct MEMORY_BLOCK {
  // 334:     struct MEMORY_BLOCK *link;
  // 335:     long mark;
  // 336:     DESTRUCTOR destructor;
  // 337:   } MEMORY_BLOCK;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__92381b92f44420eb;
  arguments->slots[1] = string__ad6cb4d361a97110;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_225;
}
static void cont__2_225(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[74] /* temp__75 */ = arguments->slots[0];
  // 338: "PHASE_2_COLLECTOR" = "
  // 339:   typedef struct PHASE_2_COLLECTOR {
  // 340:     void *dummy;
  // 341:     void *next_collector;
  // 342:     void (*collector)(void *data);
  // 343:   } PHASE_2_COLLECTOR;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__b203ec07e46c6d80;
  arguments->slots[1] = string__8f7c86910d6d0ec0;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_228;
}
static void cont__2_228(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[75] /* temp__76 */ = arguments->slots[0];
  // 344: "argument_count" = "
  // 345:   REGISTER int argument_count ASM("ebx");
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__dfd1ce1d312022e7;
  arguments->slots[1] = string__70bef8fa01ea78c4;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_231;
}
static void cont__2_231(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[76] /* temp__77 */ = arguments->slots[0];
  // 346: "arguments" = "
  // 347:   REGISTER FRAME *arguments ASM("r12");
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__64ac252603a3a696;
  arguments->slots[1] = string__501ffc7c0e5fce8d;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_234;
}
static void cont__2_234(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[77] /* temp__78 */ = arguments->slots[0];
  // 348: "myself" = "
  // 349:   REGISTER NODE *myself ASM("r13");
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__7e1f570601dbc2b1;
  arguments->slots[1] = string__7ed5b7453a0b28eb;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_237;
}
static void cont__2_237(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[78] /* temp__79 */ = arguments->slots[0];
  // 350: "func" = "
  // 351:   REGISTER FUNC func ASM("r14");
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__e0aec0b5d107d5a;
  arguments->slots[1] = string__226dfcc2010b42bb;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_240;
}
static void cont__2_240(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[79] /* temp__80 */ = arguments->slots[0];
  // 352: "frame" = "
  // 353:   REGISTER FRAME *frame ASM("r15");
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__6e5aeb43eaa07032;
  arguments->slots[1] = string__2cf4a351abcf4415;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_243;
}
static void cont__2_243(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[80] /* temp__81 */ = arguments->slots[0];
  // 354: "result_count" = "
  // 355:   int result_count;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__d48de512cf50371c;
  arguments->slots[1] = string__8f245610f4cd3fb7;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_246;
}
static void cont__2_246(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[81] /* temp__82 */ = arguments->slots[0];
  // 356: "dynamics" = "
  // 357:   DYNAMICS *dynamics;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__74f0af9104cd80d3;
  arguments->slots[1] = string__1b7f73c5bf94e5d0;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_249;
}
static void cont__2_249(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[82] /* temp__83 */ = arguments->slots[0];
  // 358: "main_argc" = "
  // 359:   int main_argc;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__6c94222b8f3884e6;
  arguments->slots[1] = string__5ae9ab7012ed0dc4;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_252;
}
static void cont__2_252(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[83] /* temp__84 */ = arguments->slots[0];
  // 360: "main_argv" = "
  // 361:   char **main_argv;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__6c94222b8f3884f3;
  arguments->slots[1] = string__b4d23a65497e01c1;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_255;
}
static void cont__2_255(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[84] /* temp__85 */ = arguments->slots[0];
  // 362: "event__mode" = "
  // 363:   EVENT__MODE event__mode;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__da8d82842a2a5a84;
  arguments->slots[1] = string__ab557f0a5c48499b;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_258;
}
static void cont__2_258(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[85] /* temp__86 */ = arguments->slots[0];
  // 364: "node_p" = "
  // 365:   void *node_p;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__501f57078042a2a7;
  arguments->slots[1] = string__f43fa690fc94429d;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_261;
}
static void cont__2_261(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[86] /* temp__87 */ = arguments->slots[0];
  // 366: "update_start_p" = "
  // 367:   void *update_start_p;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__efcd0668b0ae04c6;
  arguments->slots[1] = string__6f7ba838857d0d29;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_264;
}
static void cont__2_264(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[87] /* temp__88 */ = arguments->slots[0];
  // 368: "static_node_buf" = "
  // 369:   void *static_node_buf;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2729ba62a63415a9;
  arguments->slots[1] = string__411ed56d73ccbf77;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_267;
}
static void cont__2_267(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[88] /* temp__89 */ = arguments->slots[0];
  // 370: "static_node_buf_end" = "
  // 371:   void *static_node_buf_end;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__25a63323422a9216;
  arguments->slots[1] = string__3156ce0eca29841b;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_270;
}
static void cont__2_270(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[89] /* temp__90 */ = arguments->slots[0];
  // 372: "coll_node_buf" = "
  // 373:   void *coll_node_buf;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__bc56b0920bfa074e;
  arguments->slots[1] = string__6c603b3047444a74;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_273;
}
static void cont__2_273(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[90] /* temp__91 */ = arguments->slots[0];
  // 374: "coll_node_buf_end" = "
  // 375:   void *coll_node_buf_end;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__d50939ffa304eba1;
  arguments->slots[1] = string__dfb31d464579b6cc;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_276;
}
static void cont__2_276(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[91] /* temp__92 */ = arguments->slots[0];
  // 376: "undefined" = "
  // 377:   NODE *undefined;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__7ca0252e172b1501;
  arguments->slots[1] = string__35b46e45a024cc89;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_279;
}
static void cont__2_279(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[92] /* temp__93 */ = arguments->slots[0];
  // 378: "zero" = "
  // 379:   NODE *zero;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__360ae80b5df07d56;
  arguments->slots[1] = string__6ff45b807d805ee8;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_282;
}
static void cont__2_282(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[93] /* temp__94 */ = arguments->slots[0];
  // 380: "boolean_true" = "
  // 381:   NODE *boolean_true;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__62d904ca56abf62f;
  arguments->slots[1] = string__a7036984828ad991;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_285;
}
static void cont__2_285(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[94] /* temp__95 */ = arguments->slots[0];
  // 382: "boolean_false" = "
  // 383:   NODE *boolean_false;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__52b31fb1ca36ad;
  arguments->slots[1] = string__606c03df4d04a811;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_288;
}
static void cont__2_288(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[95] /* temp__96 */ = arguments->slots[0];
  // 384: "empty_string" = "
  // 385:   NODE *empty_string;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__ee21fa04ce7f45ad;
  arguments->slots[1] = string__922f8927bcb56a37;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_291;
}
static void cont__2_291(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[96] /* temp__97 */ = arguments->slots[0];
  // 386: "raise_exception_getter" = "
  // 387:   NODE_GETTER raise_exception_getter;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__9a7719701e463c3d;
  arguments->slots[1] = string__4dfebf8ce2b979fc;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_294;
}
static void cont__2_294(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[97] /* temp__98 */ = arguments->slots[0];
  // 388: "instruction_counter" = "
  // 389:   uint64_t instruction_counter;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__ccb06cae4fc7ced1;
  arguments->slots[1] = string__f51775fad4122113;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_297;
}
static void cont__2_297(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[98] /* temp__99 */ = arguments->slots[0];
  // 390: "no_attributes_level_1" = "
  // 391:   OCTREE no_attributes_level_1;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__f10614695d7490c;
  arguments->slots[1] = string__ae72e78740405523;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_300;
}
static void cont__2_300(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[99] /* temp__100 */ = arguments->slots[0];
  // 392: "no_attributes_level_2" = "
  // 393:   OCTREE no_attributes_level_2;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__f10614695d7490f;
  arguments->slots[1] = string__ae72e74740405523;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_303;
}
static void cont__2_303(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[100] /* temp__101 */ = arguments->slots[0];
  // 394: "no_attributes_level_3" = "
  // 395:   OCTREE no_attributes_level_3;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__f10614695d7490e;
  arguments->slots[1] = string__ae72e70740405523;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_306;
}
static void cont__2_306(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[101] /* temp__102 */ = arguments->slots[0];
  // 396: "no_attributes_level_4" = "
  // 397:   OCTREE no_attributes_level_4;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__f10614695d74909;
  arguments->slots[1] = string__ae72e6c740405523;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_309;
}
static void cont__2_309(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[102] /* temp__103 */ = arguments->slots[0];
  // 398: "no_attributes_level_5" = "
  // 399:   OCTREE no_attributes_level_5;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__f10614695d74908;
  arguments->slots[1] = string__ae72e68740405523;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_312;
}
static void cont__2_312(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[103] /* temp__104 */ = arguments->slots[0];
  // 400: "no_attributes_level_6" = "
  // 401:   OCTREE no_attributes_level_6;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__f10614695d7490b;
  arguments->slots[1] = string__ae72e64740405523;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_315;
}
static void cont__2_315(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[104] /* temp__105 */ = arguments->slots[0];
  // 402: "no_attributes_level_7" = "
  // 403:   OCTREE no_attributes_level_7;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__f10614695d7490a;
  arguments->slots[1] = string__ae72e60740405523;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_318;
}
static void cont__2_318(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[105] /* temp__106 */ = arguments->slots[0];
  // 404: "no_attributes_level_8" = "
  // 405:   OCTREE no_attributes_level_8;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__f10614695d74905;
  arguments->slots[1] = string__ae72e5c740405523;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_321;
}
static void cont__2_321(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[106] /* temp__107 */ = arguments->slots[0];
  // 406: "undefined_attributes_level_1" = "
  // 407:   OCTREE undefined_attributes_level_1;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__a96d37e5269efcea;
  arguments->slots[1] = string__d3abaa3aea9568d8;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_324;
}
static void cont__2_324(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[107] /* temp__108 */ = arguments->slots[0];
  // 408: "undefined_attributes_level_2" = "
  // 409:   OCTREE undefined_attributes_level_2;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__a96d37e5269efce9;
  arguments->slots[1] = string__d3abaafaea9568d8;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_327;
}
static void cont__2_327(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[108] /* temp__109 */ = arguments->slots[0];
  // 410: "undefined_attributes_level_3" = "
  // 411:   OCTREE undefined_attributes_level_3;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__a96d37e5269efce8;
  arguments->slots[1] = string__d3abaabaea9568d8;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_330;
}
static void cont__2_330(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[109] /* temp__110 */ = arguments->slots[0];
  // 412: "undefined_attributes_level_4" = "
  // 413:   OCTREE undefined_attributes_level_4;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__a96d37e5269efcef;
  arguments->slots[1] = string__d3abab7aea9568d8;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_333;
}
static void cont__2_333(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[110] /* temp__111 */ = arguments->slots[0];
  // 414: "undefined_attributes_level_5" = "
  // 415:   OCTREE undefined_attributes_level_5;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__a96d37e5269efcee;
  arguments->slots[1] = string__d3abab3aea9568d8;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_336;
}
static void cont__2_336(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[111] /* temp__112 */ = arguments->slots[0];
  // 416: "undefined_attributes_level_6" = "
  // 417:   OCTREE undefined_attributes_level_6;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__a96d37e5269efced;
  arguments->slots[1] = string__d3ababfaea9568d8;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_339;
}
static void cont__2_339(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[112] /* temp__113 */ = arguments->slots[0];
  // 418: "undefined_attributes_level_7" = "
  // 419:   OCTREE undefined_attributes_level_7;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__a96d37e5269efcec;
  arguments->slots[1] = string__d3ababbaea9568d8;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_342;
}
static void cont__2_342(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[113] /* temp__114 */ = arguments->slots[0];
  // 420: "undefined_attributes_level_8" = "
  // 421:   OCTREE undefined_attributes_level_8;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__a96d37e5269efce3;
  arguments->slots[1] = string__d3aba87aea9568d8;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_345;
}
static void cont__2_345(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[114] /* temp__115 */ = arguments->slots[0];
  // 422: "runtime_debug_level" = "
  // 423:   int runtime_debug_level;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__96bd3c5645503754;
  arguments->slots[1] = string__313ff19f63187450;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_348;
}
static void cont__2_348(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[115] /* temp__116 */ = arguments->slots[0];
  // 424: "unrecoverable_error" = "
  // 425:   __attribute__ ((noreturn)) void unrecoverable_error(const char *msg, ...);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__39a91c6464b48cb7;
  arguments->slots[1] = string__51cfd78644d80c92;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_351;
}
static void cont__2_351(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[116] /* temp__117 */ = arguments->slots[0];
  // 426: "out_of_memory_error" = "
  // 427:   __attribute__ ((noreturn)) void out_of_memory_error(void);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__fd5f7ef32f24bfaa;
  arguments->slots[1] = string__fec3a524701ff247;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_354;
}
static void cont__2_354(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[117] /* temp__118 */ = arguments->slots[0];
  // 428: "invalid_continuation_error" = "
  // 429:   __attribute__ ((noreturn)) void invalid_continuation_error(void);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__761587227d4825b9;
  arguments->slots[1] = string__6d343fd95f2f86f5;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_357;
}
static void cont__2_357(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[118] /* temp__119 */ = arguments->slots[0];
  // 430: "allocate" = "
  // 431:   void *allocate(long size);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__68a4ad9004756065;
  arguments->slots[1] = string__828961258c78d260;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_360;
}
static void cont__2_360(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[119] /* temp__120 */ = arguments->slots[0];
  // 432: "allocate_and_clear" = "
  // 433:   void *allocate_and_clear(long size);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__83bbca0be31365ab;
  arguments->slots[1] = string__b0f237f00b697e93;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_363;
}
static void cont__2_363(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[120] /* temp__121 */ = arguments->slots[0];
  // 434: "allocate_memory" = "
  // 435:   void *allocate_memory(size_t size);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__cfe9a9f60d3a5cd4;
  arguments->slots[1] = string__998fb2a1fe8a0c3e;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_366;
}
static void cont__2_366(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[121] /* temp__122 */ = arguments->slots[0];
  // 436: "reallocate_memory" = "
  // 437:   void *reallocate_memory(void * buf, size_t size);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__b1ec1042f2e6e8ff;
  arguments->slots[1] = string__e4edebbe4882d6ef;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_369;
}
static void cont__2_369(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[122] /* temp__123 */ = arguments->slots[0];
  // 438: "allocate_gc" = "
  // 439:   void *allocate_gc(long size);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__cad15e9b2330eaa3;
  arguments->slots[1] = string__d95df4cca4d2c6fd;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_372;
}
static void cont__2_372(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[123] /* temp__124 */ = arguments->slots[0];
  // 440: "allocate_arguments" = "
  // 441:   void allocate_arguments(void);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__91b7c8dee3bb862a;
  arguments->slots[1] = string__32a7900019341d55;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_375;
}
static void cont__2_375(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[124] /* temp__125 */ = arguments->slots[0];
  // 442: "allocate_fixed" = "
  // 443:   void *allocate_fixed(long size);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__5395bcbd356e71b1;
  arguments->slots[1] = string__e0605de396839adc;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_378;
}
static void cont__2_378(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[125] /* temp__126 */ = arguments->slots[0];
  // 444: "allocate_fixed_with_destructor" = "
  // 445:   void *allocate_fixed_with_destructor(long size, DESTRUCTOR destructor);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__42e269e73a13b76b;
  arguments->slots[1] = string__69dfa40f6a365db;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_381;
}
static void cont__2_381(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[126] /* temp__127 */ = arguments->slots[0];
  // 446: "allocate_initialized_frame_gc" = "
  // 447:   void allocate_initialized_frame_gc(int slot_idx, int slot_count);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__1b77e1575779efa5;
  arguments->slots[1] = string__6757b2e2474a0b22;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_384;
}
static void cont__2_384(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[127] /* temp__128 */ = arguments->slots[0];
  // 448: "allocate_large" = "
  // 449:   void *allocate_large(long size);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__4395be3d357ed1b0;
  arguments->slots[1] = string__e0e85de2d683928c;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_387;
}
static void cont__2_387(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[128] /* temp__129 */ = arguments->slots[0];
  // 450: "deallocate_memory" = "
  // 451:   void deallocate_memory(void *buf);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__b1fa1042f2e6e8ff;
  arguments->slots[1] = string__b16ca6def7b3553c;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_390;
}
static void cont__2_390(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[129] /* temp__130 */ = arguments->slots[0];
  // 452: "copy" = "
  // 453:   void *copy(const void *buf, long size);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__40aea8b5de07d40;
  arguments->slots[1] = string__e97bf72e3ea776ca;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_393;
}
static void cont__2_393(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[130] /* temp__131 */ = arguments->slots[0];
  // 454: "register_phase_3_collector" = "
  // 455:   void register_phase_3_collector(void *data);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__b23dc2be453fb4c;
  arguments->slots[1] = string__68644448021229ea;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_396;
}
static void cont__2_396(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[131] /* temp__132 */ = arguments->slots[0];
  // 456: "child_changed_state" = "
  // 457:   int child_changed_state;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__edb661f544f7f1b4;
  arguments->slots[1] = string__58ce4981a1cf1c90;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_399;
}
static void cont__2_399(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[132] /* temp__133 */ = arguments->slots[0];
  // 458: "window_changed_size" = "
  // 459:   int window_changed_size;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__b7b51829c8931dfe;
  arguments->slots[1] = string__41f55b1721116bb3;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_402;
}
static void cont__2_402(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[133] /* temp__134 */ = arguments->slots[0];
  // 460: "from_printf" = "
  // 461:   NODE *from_printf(const char *msg, ...);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__1221a2d3a0a88ae7;
  arguments->slots[1] = string__906cbeff26b5017a;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_405;
}
static void cont__2_405(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[134] /* temp__135 */ = arguments->slots[0];
  // 462: "runtime_error" = "
  // 463:   __attribute__ ((noreturn)) void runtime_error(const char *msg, ...);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__667e759fbd1e073a;
  arguments->slots[1] = string__4f98ca907370d4fd;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_408;
}
static void cont__2_408(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[135] /* temp__136 */ = arguments->slots[0];
  // 464: "too_few_arguments_error" = "
  // 465:   void too_few_arguments_error(void);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__ac42fe8001c0cf7b;
  arguments->slots[1] = string__90e4557368bcc70c;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_411;
}
static void cont__2_411(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[136] /* temp__137 */ = arguments->slots[0];
  // 466: "too_many_arguments_error" = "
  // 467:   void too_many_arguments_error(void);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__fe16467ca0045e4f;
  arguments->slots[1] = string__4b24985949e64aa0;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_414;
}
static void cont__2_414(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[137] /* temp__138 */ = arguments->slots[0];
  // 468: "invalid_arguments_error" = "
  // 469:   void invalid_arguments_error(void);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__3c5182f403404f1a;
  arguments->slots[1] = string__e4e6d5f3092cd470;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_417;
}
static void cont__2_417(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[138] /* temp__139 */ = arguments->slots[0];
  // 470: "too_few_results_error" = "
  // 471:   void too_few_results_error(void);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__5a7ee7d9a77669df;
  arguments->slots[1] = string__3e34445dbde01d92;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_420;
}
static void cont__2_420(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[139] /* temp__140 */ = arguments->slots[0];
  // 472: "too_many_results_error" = "
  // 473:   void too_many_results_error(void);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__a8f9f59d763f3b3c;
  arguments->slots[1] = string__96b12e6b0e8f1ea6;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_423;
}
static void cont__2_423(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[140] /* temp__141 */ = arguments->slots[0];
  // 474: "invalid_results_error" = "
  // 475:   void invalid_results_error(void);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__8a74e5d82136242e;
  arguments->slots[1] = string__3fb204104c301790;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_426;
}
static void cont__2_426(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[141] /* temp__142 */ = arguments->slots[0];
  // 476: "invalid_index_error" = "
  // 477:   void invalid_index_error(void);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__fad96544e5c0b191;
  arguments->slots[1] = string__82b0591fec9d608e;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_429;
}
static void cont__2_429(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[142] /* temp__143 */ = arguments->slots[0];
  // 478: "divide_by_zero_error" = "
  // 479:   void divide_by_zero_error(void);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__776fc0898d8697f5;
  arguments->slots[1] = string__de9a692913a186a6;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_432;
}
static void cont__2_432(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[143] /* temp__144 */ = arguments->slots[0];
  // 480: "not_yet_implemented_error" = "
  // 481:   void not_yet_implemented_error(void);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__76bf0e1274169131;
  arguments->slots[1] = string__682822d0ffcfd8e0;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_435;
}
static void cont__2_435(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[144] /* temp__145 */ = arguments->slots[0];
  // 482: "no_such_function" = "
  // 483:   void no_such_function(void);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__e0508ed6bc3a9403;
  arguments->slots[1] = string__d9addc1ddea8b503;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_438;
}
static void cont__2_438(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[145] /* temp__146 */ = arguments->slots[0];
  // 484: "no_such_attribute" = "
  // 485:   void no_such_attribute(void);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__60dde75c27ced2c1;
  arguments->slots[1] = string__f20d2016c4807ea2;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_441;
}
static void cont__2_441(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[146] /* temp__147 */ = arguments->slots[0];
  // 486: "resource_error" = "
  // 487:   void resource_error(void);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__6c150ead26004347;
  arguments->slots[1] = string__9d8c53f6d9a9a7b7;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_444;
}
static void cont__2_444(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[147] /* temp__148 */ = arguments->slots[0];
  // 488: "io_error" = "
  // 489:   void io_error(void);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__4aa8a94984adc172;
  arguments->slots[1] = string__162c20703a78c3ff;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_447;
}
static void cont__2_447(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[148] /* temp__149 */ = arguments->slots[0];
  // 490: "initialize_runtime" = "
  // 491:   void initialize_runtime(void);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__b6e0e11e4743dfdf;
  arguments->slots[1] = string__f2036859ec134a7c;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_450;
}
static void cont__2_450(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[149] /* temp__150 */ = arguments->slots[0];
  // 492: "initialize_phase_3" = "
  // 493:   void initialize_phase_3(void);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__b8e8e210c6d32f89;
  arguments->slots[1] = string__fc82f8a9ba1d427f;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_453;
}
static void cont__2_453(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[150] /* temp__151 */ = arguments->slots[0];
  // 494: "initialize_phase_4" = "
  // 495:   void initialize_phase_4(void);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__b8e8e210c6d32f8e;
  arguments->slots[1] = string__fc82f8a9bd1d427f;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_456;
}
static void cont__2_456(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[151] /* temp__152 */ = arguments->slots[0];
  // 496: "current_mark" = "
  // 497:   long current_mark;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__d0e5e8074891f627;
  arguments->slots[1] = string__3f5d3a0d2c7bc3c7;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_459;
}
static void cont__2_459(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[152] /* temp__153 */ = arguments->slots[0];
  // 498: "join_nodes" = "
  // 499:   void join_nodes(void *left_node_pp, void *right_node_pp);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2b5c4104290394d2;
  arguments->slots[1] = string__5104e1e70e2bbd29;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_462;
}
static void cont__2_462(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[153] /* temp__154 */ = arguments->slots[0];
  // 500: "clone_object_and_attributes" = "
  // 501:   NODE *clone_object_and_attributes(NODE *node);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__41c85713242372c5;
  arguments->slots[1] = string__e51baebf46ac8640;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_465;
}
static void cont__2_465(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[154] /* temp__155 */ = arguments->slots[0];
  // 502: "register_collector" = "
  // 503:   void register_collector(FUNC collector);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__5592cf0301411d16;
  arguments->slots[1] = string__dee304be4126ea7;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_468;
}
static void cont__2_468(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[155] /* temp__156 */ = arguments->slots[0];
  // 504: "collect_node" = "
  // 505:   NODE *collect_node(NODE *node);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__56d11b875621f62f;
  arguments->slots[1] = string__caea8b2ff976ddc3;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_471;
}
static void cont__2_471(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[156] /* temp__157 */ = arguments->slots[0];
  // 506: "collect_static_attributes" = "
  // 507:   void collect_static_attributes(ATTRIBUTES *attributes);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__34fd7b2a54432a1f;
  arguments->slots[1] = string__2f060df2bab9ebec;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_474;
}
static void cont__2_474(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[157] /* temp__158 */ = arguments->slots[0];
  // 508: "collect_attributes" = "
  // 509:   ATTRIBUTES *collect_attributes(ATTRIBUTES *attributes);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__32e13e70f6337af4;
  arguments->slots[1] = string__8a205606fdc9fcee;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_477;
}
static void cont__2_477(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[158] /* temp__159 */ = arguments->slots[0];
  // 510: "collect_simple_node" = "
  // 511:   void *collect_simple_node(SIMPLE_NODE *node);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__47935b184e1b3728;
  arguments->slots[1] = string__337f24e44c027fbc;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_480;
}
static void cont__2_480(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[159] /* temp__160 */ = arguments->slots[0];
  // 512: "total_garbage_collections" = "
  // 513:   int total_garbage_collections;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__9520754d88a4dfe0;
  arguments->slots[1] = string__ae1a6ceddb2e6555;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_483;
}
static void cont__2_483(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[160] /* temp__161 */ = arguments->slots[0];
  // 514: "collect_garbage" = "
  // 515:   void collect_garbage();
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__5089ba700d952389;
  arguments->slots[1] = string__728beb96de734cfe;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_486;
}
static void cont__2_486(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[161] /* temp__162 */ = arguments->slots[0];
  // 516: "indent_to_string" = "
  // 517:   const char *indent_to_string(int indent);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__317937b8f705e12f;
  arguments->slots[1] = string__726eb8f70f88c9b;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_489;
}
static void cont__2_489(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[162] /* temp__163 */ = arguments->slots[0];
  // 518: "print" = "
  // 519:   int print(char **buf_p, const char *format, ...);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__6e5ae943eab91023;
  arguments->slots[1] = string__1248a4b5a2020125;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_492;
}
static void cont__2_492(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[163] /* temp__164 */ = arguments->slots[0];
  // 520: "debug_print" = "
  // 521:   int debug_print(int indent, char *buf, const char *format, ...);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__a4c11b042d78a9f5;
  arguments->slots[1] = string__b17e1477ca7d8644;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_495;
}
static void cont__2_495(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[164] /* temp__165 */ = arguments->slots[0];
  // 522: "debug_print_head" = "
  // 523:   int debug_print_head(int *indent_p, char **buf_p, const char *format, ...);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__c6bc4dbad16d7de6;
  arguments->slots[1] = string__9852c4e0e14b8181;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_498;
}
static void cont__2_498(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[165] /* temp__166 */ = arguments->slots[0];
  // 524: "to_int8" = "
  // 525:   uint32_t to_int8(NODE *node);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__a0540e55151930c2;
  arguments->slots[1] = string__8b67b34a14524350;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_501;
}
static void cont__2_501(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[166] /* temp__167 */ = arguments->slots[0];
  // 526: "to_int16" = "
  // 527:   uint64_t to_int16(NODE *node);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__72a8a8c9865d0296;
  arguments->slots[1] = string__7156ce06811a3bb7;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_504;
}
static void cont__2_504(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[167] /* temp__168 */ = arguments->slots[0];
  // 528: "to_int32" = "
  // 529:   uint32_t to_int32(NODE *node);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__72a8a8c9864d0292;
  arguments->slots[1] = string__71578e06f11a2bb7;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_507;
}
static void cont__2_507(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[168] /* temp__169 */ = arguments->slots[0];
  // 530: "to_int64" = "
  // 531:   uint64_t to_int64(NODE *node);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__72a8a8c986650294;
  arguments->slots[1] = string__7156ce06611a33b7;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_510;
}
static void cont__2_510(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[169] /* temp__170 */ = arguments->slots[0];
  // 532: "to_uint8" = "
  // 533:   uint32_t to_uint8(NODE *node);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__7ca8ae498474c298;
  arguments->slots[1] = string__714d8e0e161a038f;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_513;
}
static void cont__2_513(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[170] /* temp__171 */ = arguments->slots[0];
  // 534: "to_uint16" = "
  // 535:   uint64_t to_uint16(NODE *node);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__724c23a6148be573;
  arguments->slots[1] = string__9b761c44b7e5eaec;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_516;
}
static void cont__2_516(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[171] /* temp__172 */ = arguments->slots[0];
  // 536: "to_uint32" = "
  // 537:   uint32_t to_uint32(NODE *node);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__724c23a6149be577;
  arguments->slots[1] = string__9b779c44f7e5fae6;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_519;
}
static void cont__2_519(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[172] /* temp__173 */ = arguments->slots[0];
  // 538: "to_uint64" = "
  // 539:   uint64_t to_uint64(NODE *node);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__724c23a614b3e571;
  arguments->slots[1] = string__9b761c4457e5e2ec;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_522;
}
static void cont__2_522(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[173] /* temp__174 */ = arguments->slots[0];
  // 540: "to_uchar32" = "
  // 541:   uint32_t to_uchar32(NODE *node);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__3730b49a2bb3f253;
  arguments->slots[1] = string__96187ba7d2aab9e;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_525;
}
static void cont__2_525(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[174] /* temp__175 */ = arguments->slots[0];
  // 542: "to_bool" = "
  // 543:   int to_bool(NODE *node);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__b6540e1515c13096;
  arguments->slots[1] = string__eab0567a680d7e49;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_528;
}
static void cont__2_528(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[175] /* temp__176 */ = arguments->slots[0];
  // 544: "to_int" = "
  // 545:   int to_int(NODE *node);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__261f540a81caa2a3;
  arguments->slots[1] = string__4ed36036cf5d9072;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_531;
}
static void cont__2_531(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[176] /* temp__177 */ = arguments->slots[0];
  // 546: "to_long" = "
  // 547:   long to_long(NODE *node);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__aa540e1515c9309d;
  arguments->slots[1] = string__eb940de21eba7011;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_534;
}
static void cont__2_534(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[177] /* temp__178 */ = arguments->slots[0];
  // 548: "to_double" = "
  // 549:   double to_double(NODE *node);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__444c262e96638520;
  arguments->slots[1] = string__348e2dcbe014e084;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_537;
}
static void cont__2_537(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[178] /* temp__179 */ = arguments->slots[0];
  // 550: "to_c_string" = "
  // 551:   char *to_c_string(NODE *node);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__a4214b121078eb22;
  arguments->slots[1] = string__2a2e177196a0d458;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_540;
}
static void cont__2_540(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[179] /* temp__180 */ = arguments->slots[0];
  // 552: "to_octets" = "
  // 553:   uint8_t *to_octets(NODE *node, long *size_p);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__464c27eb16a34536;
  arguments->slots[1] = string__21cd69a400bae74a;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_543;
}
static void cont__2_543(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[180] /* temp__181 */ = arguments->slots[0];
  // 554: "get_item_of" = "
  // 555:   NODE *get_item_of(NODE *node, long idx);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__5af91691bb71fca7;
  arguments->slots[1] = string__f5570b383c3fc00;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_546;
}
static void cont__2_546(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[181] /* temp__182 */ = arguments->slots[0];
  // 556: "length_of" = "
  // 557:   long length_of(NODE *node);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__7e88296f0e7a3463;
  arguments->slots[1] = string__310f62774c0e0007;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_549;
}
static void cont__2_549(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[182] /* temp__183 */ = arguments->slots[0];
  // 558: "unfold" = "
  // 559:   void unfold(NODE *node);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__541f558a01dab2b3;
  arguments->slots[1] = string__aa90620e046f416c;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_552;
}
static void cont__2_552(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[183] /* temp__184 */ = arguments->slots[0];
  // 560: "debug_string" = "
  // 561:   long debug_string(NODE *node, int indent, int max_depth, char *buf);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__ee216a04cf7d466f;
  arguments->slots[1] = string__b1d91f87cca0e731;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_555;
}
static void cont__2_555(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[184] /* temp__185 */ = arguments->slots[0];
  // 562: "optional_item" = "
  // 563:   void optional_item(NODE *item);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__d06e9dd63b47a743;
  arguments->slots[1] = string__7a5cedaec36476fb;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_558;
}
static void cont__2_558(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[185] /* temp__186 */ = arguments->slots[0];
  // 564: "get_attribute" = "
  // 565:   NODE *get_attribute(NODE *node, int idx);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__c63b2d1935e6c40b;
  arguments->slots[1] = string__679ea7d4aa3dc62e;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_561;
}
static void cont__2_561(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[186] /* temp__187 */ = arguments->slots[0];
  // 566: "polymorph_dispatch" = "
  // 567:   void polymorph_dispatch(int idx);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__de8d76bddd0e0c7c;
  arguments->slots[1] = string__33b3c02b144305e5;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_564;
}
static void cont__2_564(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[187] /* temp__188 */ = arguments->slots[0];
  // 568: "set_attribute" = "
  // 569:   void set_attribute(ATTRIBUTES *attributes, int idx, void *attr);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__c63b2c5935e6c40b;
  arguments->slots[1] = string__461472315ebaff5f;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_567;
}
static void cont__2_567(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[188] /* temp__189 */ = arguments->slots[0];
  // 570: "set_attribute_value" = "
  // 571:   void set_attribute_value(ATTRIBUTES *attributes, int idx, void *attr);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__d22f03c332cbb7fe;
  arguments->slots[1] = string__14bb178f7122cfd7;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_570;
}
static void cont__2_570(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[189] /* temp__190 */ = arguments->slots[0];
  // 572: "record__event" = "
  // 573:   void record__event(const char *name);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2e96a85fa636061f;
  arguments->slots[1] = string__dab898fd6ccb94af;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_573;
}
static void cont__2_573(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[190] /* temp__191 */ = arguments->slots[0];
  // 574: "successful__action" = "
  // 575:   void successful__action(const char *name);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__704f98350e6d5307;
  arguments->slots[1] = string__cb62ccbfd0ebcc01;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_576;
}
static void cont__2_576(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[191] /* temp__192 */ = arguments->slots[0];
  // 576: "failed__action" = "
  // 577:   void failed__action(const char *name);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__aafd8832303424db;
  arguments->slots[1] = string__d0c86ff26de9d846;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_579;
}
static void cont__2_579(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[192] /* temp__193 */ = arguments->slots[0];
  // 578: "replay__event" = "
  // 579:   void replay__event(const char *name);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__ee96b05fb53605bb;
  arguments->slots[1] = string__96b8997d6dfb9495;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_582;
}
static void cont__2_582(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[193] /* temp__194 */ = arguments->slots[0];
  // 580: "replay__action" = "
  // 581:   int replay__action(const char *name);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__a0fda8722d0624db;
  arguments->slots[1] = string__c4688fdba679a3d7;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_585;
}
static void cont__2_585(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[194] /* temp__195 */ = arguments->slots[0];
  // 582: "report__event" = "
  // 583:   void report__event(const char *name);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__ee96a85fa636041b;
  arguments->slots[1] = string__96b898fd6ccb948f;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_588;
}
static void cont__2_588(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[195] /* temp__196 */ = arguments->slots[0];
  // 584: "print__pointer" = "
  // 585:   void print__pointer(void *ptr);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__154106450b6484c7;
  arguments->slots[1] = string__48ac73a2bb0fdab2;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_591;
}
static void cont__2_591(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[196] /* temp__197 */ = arguments->slots[0];
  // 586: "store__pointer" = "
  // 587:   void store__pointer(void *ptr);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__14c18e250b6884c0;
  arguments->slots[1] = string__4b2cb3e68b0fdcb2;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_594;
}
static void cont__2_594(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[197] /* temp__198 */ = arguments->slots[0];
  // 588: "retrieve__pointer" = "
  // 589:   void retrieve__pointer(void **ptr_p);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__f85036d3d94a7bb1;
  arguments->slots[1] = string__1e649a8a52a00dac;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_597;
}
static void cont__2_597(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[198] /* temp__199 */ = arguments->slots[0];
  // 590: "print__integer" = "
  // 591:   void print__integer(int val);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__32502858b6554c7;
  arguments->slots[1] = string__ba7ab002426e2e85;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_600;
}
static void cont__2_600(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[199] /* temp__200 */ = arguments->slots[0];
  // 592: "store__integer" = "
  // 593:   void store__integer(int val);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2a58ae58b6954c0;
  arguments->slots[1] = string__aabab01a42602d84;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_603;
}
static void cont__2_603(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[200] /* temp__201 */ = arguments->slots[0];
  // 594: "retrieve__integer" = "
  // 595:   void retrieve__integer(int *val_p);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__ee343213594babb1;
  arguments->slots[1] = string__fc70de4897612997;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_606;
}
static void cont__2_606(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[201] /* temp__202 */ = arguments->slots[0];
  // 596: "print__long_integer" = "
  // 597:   void print__long_integer(long val);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__4f8263ad80b7c630;
  arguments->slots[1] = string__ac28eb4056636d1;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_609;
}
static void cont__2_609(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[202] /* temp__203 */ = arguments->slots[0];
  // 598: "store__long_integer" = "
  // 599:   void store__long_integer(long val);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__4f8463ae00778200;
  arguments->slots[1] = string__6c6cdb4050636e9;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_612;
}
static void cont__2_612(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[203] /* temp__204 */ = arguments->slots[0];
  // 600: "retrieve__long_integer" = "
  // 601:   void retrieve__long_integer(long *val_p);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__26951c16f63f5e7b;
  arguments->slots[1] = string__8aa183bf30fdb669;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_615;
}
static void cont__2_615(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[204] /* temp__205 */ = arguments->slots[0];
  // 602: "print__int_array" = "
  // 603:   void print__int_array(const int *buf, long len);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__f75531ddca48c11b;
  arguments->slots[1] = string__1061572abef9f5fc;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_618;
}
static void cont__2_618(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[205] /* temp__206 */ = arguments->slots[0];
  // 604: "store__int_array" = "
  // 605:   void store__int_array(const int *buf, long len);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__f455301daa6ad91b;
  arguments->slots[1] = string__c67550b3ef9c5fc;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_621;
}
static void cont__2_621(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[206] /* temp__207 */ = arguments->slots[0];
  // 606: "retrieve__int_array" = "
  // 607:   long retrieve__int_array(int **buf_p);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__7ceaec668e04e4af;
  arguments->slots[1] = string__f527cb3955e59def;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_624;
}
static void cont__2_624(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[207] /* temp__208 */ = arguments->slots[0];
  // 608: "print__memory" = "
  // 609:   void print__memory(const uint8_t *buf, long len);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__9896a2e6a0f80170;
  arguments->slots[1] = string__b813d7b89495bd97;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_627;
}
static void cont__2_627(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[208] /* temp__209 */ = arguments->slots[0];
  // 610: "store__memory" = "
  // 611:   void store__memory(const uint8_t *buf, long len);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__189642d6b1f40171;
  arguments->slots[1] = string__a91fd7b914955da7;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_630;
}
static void cont__2_630(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[209] /* temp__210 */ = arguments->slots[0];
  // 612: "retrieve__memory" = "
  // 613:   long retrieve__memory(uint8_t **buf_p);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__47787f4486eadb35;
  arguments->slots[1] = string__71f6bf6cf0c52b77;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_633;
}
static void cont__2_633(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[210] /* temp__211 */ = arguments->slots[0];
  // 614: "print__c_string" = "
  // 615:   void print__c_string(const char *buf);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__3ee8582926d9080f;
  arguments->slots[1] = string__b566653efe8d5564;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_636;
}
static void cont__2_636(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[211] /* temp__212 */ = arguments->slots[0];
  // 616: "store__c_string" = "
  // 617:   void store__c_string(const char *buf);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__7de8584926e1040b;
  arguments->slots[1] = string__c57e6db8fe8d9564;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_639;
}
static void cont__2_639(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[212] /* temp__213 */ = arguments->slots[0];
  // 618: "retrieve__c_string" = "
  // 619:   void retrieve__c_string(char **buf_p);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__ba5ec95edd6e6086;
  arguments->slots[1] = string__44e19d077543310d;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_642;
}
static void cont__2_642(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[213] /* temp__214 */ = arguments->slots[0];
  // 620: "create_function" = "
  // 621:   NODE *create_function(FUNC func, int par_count);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__324188e7a6ce34a6;
  arguments->slots[1] = string__cc612f10fbde1147;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_645;
}
static void cont__2_645(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[214] /* temp__215 */ = arguments->slots[0];
  // 622: "create_closure" = "
  // 623:   NODE *create_closure(FUNC type, int par_count);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__e68d0604b1c4e4d3;
  arguments->slots[1] = string__4e66b585b29bac7b;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_648;
}
static void cont__2_648(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[215] /* temp__216 */ = arguments->slots[0];
  // 624: "continuation_type_function" = "
  // 625:   void continuation_type_function(void);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__527f2a0eb4d2ad39;
  arguments->slots[1] = string__36dea3e52fa97601;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_651;
}
static void cont__2_651(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[216] /* temp__217 */ = arguments->slots[0];
  // 626: "continuation_trampoline" = "
  // 627:   void continuation_trampoline(void);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__db8268c5e3e3998;
  arguments->slots[1] = string__9cbbab858b1d3dd4;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_654;
}
static void cont__2_654(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[217] /* temp__218 */ = arguments->slots[0];
  // 628: "create_continuation" = "
  // 629:   NODE *create_continuation(void);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__70926021f73890ec;
  arguments->slots[1] = string__6f29cd9643b48e9f;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_657;
}
static void cont__2_657(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[218] /* temp__219 */ = arguments->slots[0];
  // 630: "create_continuation_with_exit" = "
  // 631:   NODE *create_continuation_with_exit(FUNC exit_func);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__d7f67e3c0983d96f;
  arguments->slots[1] = string__312f4f711c0187b4;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_660;
}
static void cont__2_660(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[219] /* temp__220 */ = arguments->slots[0];
  // 632: "initialize_function_attributes" = "
  // 633:   void initialize_function_attributes(void);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__5df6e86d7cfc4b00;
  arguments->slots[1] = string__83170f4ed8417cf9;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_663;
}
static void cont__2_663(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[220] /* temp__221 */ = arguments->slots[0];
  // 634: "create_future" = "
  // 635:   NODE *create_future(void);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__aa96dd5320f9062f;
  arguments->slots[1] = string__2524b8f70c096216;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_666;
}
static void cont__2_666(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[221] /* temp__222 */ = arguments->slots[0];
  // 636: "create_future_with_prototype" = "
  // 637:   NODE *create_future_with_prototype(NODE *prototype);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__b621c02f863d5995;
  arguments->slots[1] = string__795f344f2e5fec15;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_669;
}
static void cont__2_669(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[222] /* temp__223 */ = arguments->slots[0];
  // 638: "initialize_future" = "
  // 639:   void initialize_future(NODE *var, NODE *val);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__4ff756961cfbc8e0;
  arguments->slots[1] = string__8ac552a1731f393c;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_672;
}
static void cont__2_672(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[223] /* temp__224 */ = arguments->slots[0];
  // 640: "maybe_initialize_future" = "
  // 641:   void maybe_initialize_future(NODE *var, NODE *val);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__83ece5deb5c6ec9d;
  arguments->slots[1] = string__b7c1a4c735435200;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_675;
}
static void cont__2_675(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[224] /* temp__225 */ = arguments->slots[0];
  // 642: "initialize_maybe_future" = "
  // 643:   void initialize_maybe_future(NODE *var, NODE *val);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__cb694aae4ed9216f;
  arguments->slots[1] = string__326ed43c2a8ea048;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_678;
}
static void cont__2_678(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[225] /* temp__226 */ = arguments->slots[0];
  // 644: "assign_value" = "
  // 645:   void assign_value(NODE **dest, NODE *val);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__48e5e352d3af6668;
  arguments->slots[1] = string__f906962f4ff7a2cb;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_681;
}
static void cont__2_681(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[226] /* temp__227 */ = arguments->slots[0];
  // 646: "assign_variable" = "
  // 647:   void assign_variable(NODE **dest, NODE **var_p);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__d891d349a6c69ea9;
  arguments->slots[1] = string__9d199eb4b8234323;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_684;
}
static void cont__2_684(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[227] /* temp__228 */ = arguments->slots[0];
  // 648: "def_attribute" = "
  // 649:   void def_attribute(NODE **var_p, int idx, void *attr);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__463b2d2935e6c40f;
  arguments->slots[1] = string__c561b7f4ab9de03e;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_687;
}
static void cont__2_687(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[228] /* temp__229 */ = arguments->slots[0];
  // 650: "create_cell" = "
  // 651:   NODE *create_cell(void);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__468da0192a6a5b6c;
  arguments->slots[1] = string__ca7b95abeb676984;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_690;
}
static void cont__2_690(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[229] /* temp__230 */ = arguments->slots[0];
  // 652: "create_cell_with_contents" = "
  // 653:   NODE *create_cell_with_contents(NODE *contents);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__d2bf386ef518fd14;
  arguments->slots[1] = string__9711b14735cfde06;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_693;
}
static void cont__2_693(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[230] /* temp__231 */ = arguments->slots[0];
  // 654: "get_dynamic_slot" = "
  // 655:   NODE *get_dynamic_slot(int id);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__7ba0bd51221b7d7f;
  arguments->slots[1] = string__4607d5e4ffb66756;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_696;
}
static void cont__2_696(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[231] /* temp__232 */ = arguments->slots[0];
  // 656: "get_dynamic_cell" = "
  // 657:   NODE *get_dynamic_cell(int id);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__5ba0bf1122037d67;
  arguments->slots[1] = string__4e07d574ffb06750;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_699;
}
static void cont__2_699(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[232] /* temp__233 */ = arguments->slots[0];
  // 658: "set_dynamic_cell" = "
  // 659:   void set_dynamic_cell(int id, NODE *node);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__5ba0bf13a2037d67;
  arguments->slots[1] = string__e46df6740b141708;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_702;
}
static void cont__2_702(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[233] /* temp__234 */ = arguments->slots[0];
  // 660: "define_dynamic_slot" = "
  // 661:   void define_dynamic_slot(int id, NODE *node);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__fe8d616be3f518cb;
  arguments->slots[1] = string__f248fe4622d2f5cc;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_705;
}
static void cont__2_705(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[234] /* temp__235 */ = arguments->slots[0];
  // 662: "define_dynamic_cell" = "
  // 663:   void define_dynamic_cell(int id, NODE *node);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__de8d632be3ed18d3;
  arguments->slots[1] = string__f228fe26a2d2fccc;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_708;
}
static void cont__2_708(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[235] /* temp__236 */ = arguments->slots[0];
  // 664: "terminate" = "
  // 665:   void terminate(int exit_code);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__72f826ea16a3e460;
  arguments->slots[1] = string__43fa56dbd271ef60;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_711;
}
static void cont__2_711(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[236] /* temp__237 */ = arguments->slots[0];
  // 666: "execute" = "
  // 667:   __attribute__ ((noreturn)) void execute(FUNC entry);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__b410089e951a909f;
  arguments->slots[1] = string__5637a81453ba364;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_714;
}
static void cont__2_714(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[237] /* temp__238 */ = arguments->slots[0];
  // 668: "invoke_callback" = "
  // 669:   void invoke_callback(NODE *callback);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__d0118bd6a6b2ec04;
  arguments->slots[1] = string__736892f443d8da54;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_717;
}
static void cont__2_717(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[238] /* temp__239 */ = arguments->slots[0];
  // 670: "COMPARE_FUNCTION" = "
  // 671:   typedef int (*COMPARE_FUNCTION)(const void *, const void *);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__e9d1ecf31d50102f;
  arguments->slots[1] = string__29bf848cc7ceebf2;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_720;
}
static void cont__2_720(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[239] /* temp__240 */ = arguments->slots[0];
  // 672: "DEBUG_COMMAND" = "
  // 673:   typedef enum {
  // 674:     SHOW_PROMPT,
  // 675:     LOG_LAST_INSTRUCTION,
  // 676:     GOTO_INSTRUCTION
  // 677:   } DEBUG_COMMAND;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__18e7723792748147;
  arguments->slots[1] = string__b1b21feb47ad3535;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_723;
}
static void cont__2_723(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[240] /* temp__241 */ = arguments->slots[0];
  // 678: "SHARED_DATA" = "
  // 679:   typedef struct {
  // 680:     DEBUG_COMMAND command;
  // 681:     uint64_t instruction_counter;
  // 682:     int depth;
  // 683:   } SHARED_DATA;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__84879098faa5d2d;
  arguments->slots[1] = string__45b0ac293d6efdfa;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_726;
}
static void cont__2_726(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[241] /* temp__242 */ = arguments->slots[0];
  // 684: "retrieve_continuation_info" = "
  // 685:   int retrieve_continuation_info(
  // 686:     FUNC func, const char **filename_p, CONTINUATION_INFO **info_p
  // 687:   );
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__8edd0c0616b76781;
  arguments->slots[1] = string__5745a2890b84b4b9;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_729;
}
static void cont__2_729(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[242] /* temp__243 */ = arguments->slots[0];
  // 688: "crash_dump" = "
  // 689:   void crash_dump(void);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__3d280d5fb44085d1;
  arguments->slots[1] = string__ed53ddd7ccc24cb5;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__2_732;
}
static void cont__2_732(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[243] /* temp__244 */ = arguments->slots[0];
  // 22: $sim2c::runtime_symbols
  // 23:   table
  // 24:     "ASM" = "
  // 25:       #if defined(__GNUC__) && !defined(__clang__) && defined(__x86_64)
  // 26:         #define ASM(x) asm(x)
  // 27:       #else
  // 28:         #define ASM(x)
  // 29:       #endif
  // 30:     "REGISTER" = "
  // 31:       #if defined(__GNUC__) && !defined(__clang__) && defined(__x86_64)
  // ...
  argument_count = 244;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* temp__2 */;
  arguments->slots[2] = frame->slots[2] /* temp__3 */;
  arguments->slots[3] = frame->slots[3] /* temp__4 */;
  arguments->slots[4] = frame->slots[4] /* temp__5 */;
  arguments->slots[5] = frame->slots[5] /* temp__6 */;
  arguments->slots[6] = frame->slots[6] /* temp__7 */;
  arguments->slots[7] = frame->slots[7] /* temp__8 */;
  arguments->slots[8] = frame->slots[8] /* temp__9 */;
  arguments->slots[9] = frame->slots[9] /* temp__10 */;
  arguments->slots[10] = frame->slots[10] /* temp__11 */;
  arguments->slots[11] = frame->slots[11] /* temp__12 */;
  arguments->slots[12] = frame->slots[12] /* temp__13 */;
  arguments->slots[13] = frame->slots[13] /* temp__14 */;
  arguments->slots[14] = frame->slots[14] /* temp__15 */;
  arguments->slots[15] = frame->slots[15] /* temp__16 */;
  arguments->slots[16] = frame->slots[16] /* temp__17 */;
  arguments->slots[17] = frame->slots[17] /* temp__18 */;
  arguments->slots[18] = frame->slots[18] /* temp__19 */;
  arguments->slots[19] = frame->slots[19] /* temp__20 */;
  arguments->slots[20] = frame->slots[20] /* temp__21 */;
  arguments->slots[21] = frame->slots[21] /* temp__22 */;
  arguments->slots[22] = frame->slots[22] /* temp__23 */;
  arguments->slots[23] = frame->slots[23] /* temp__24 */;
  arguments->slots[24] = frame->slots[24] /* temp__25 */;
  arguments->slots[25] = frame->slots[25] /* temp__26 */;
  arguments->slots[26] = frame->slots[26] /* temp__27 */;
  arguments->slots[27] = frame->slots[27] /* temp__28 */;
  arguments->slots[28] = frame->slots[28] /* temp__29 */;
  arguments->slots[29] = frame->slots[29] /* temp__30 */;
  arguments->slots[30] = frame->slots[30] /* temp__31 */;
  arguments->slots[31] = frame->slots[31] /* temp__32 */;
  arguments->slots[32] = frame->slots[32] /* temp__33 */;
  arguments->slots[33] = frame->slots[33] /* temp__34 */;
  arguments->slots[34] = frame->slots[34] /* temp__35 */;
  arguments->slots[35] = frame->slots[35] /* temp__36 */;
  arguments->slots[36] = frame->slots[36] /* temp__37 */;
  arguments->slots[37] = frame->slots[37] /* temp__38 */;
  arguments->slots[38] = frame->slots[38] /* temp__39 */;
  arguments->slots[39] = frame->slots[39] /* temp__40 */;
  arguments->slots[40] = frame->slots[40] /* temp__41 */;
  arguments->slots[41] = frame->slots[41] /* temp__42 */;
  arguments->slots[42] = frame->slots[42] /* temp__43 */;
  arguments->slots[43] = frame->slots[43] /* temp__44 */;
  arguments->slots[44] = frame->slots[44] /* temp__45 */;
  arguments->slots[45] = frame->slots[45] /* temp__46 */;
  arguments->slots[46] = frame->slots[46] /* temp__47 */;
  arguments->slots[47] = frame->slots[47] /* temp__48 */;
  arguments->slots[48] = frame->slots[48] /* temp__49 */;
  arguments->slots[49] = frame->slots[49] /* temp__50 */;
  arguments->slots[50] = frame->slots[50] /* temp__51 */;
  arguments->slots[51] = frame->slots[51] /* temp__52 */;
  arguments->slots[52] = frame->slots[52] /* temp__53 */;
  arguments->slots[53] = frame->slots[53] /* temp__54 */;
  arguments->slots[54] = frame->slots[54] /* temp__55 */;
  arguments->slots[55] = frame->slots[55] /* temp__56 */;
  arguments->slots[56] = frame->slots[56] /* temp__57 */;
  arguments->slots[57] = frame->slots[57] /* temp__58 */;
  arguments->slots[58] = frame->slots[58] /* temp__59 */;
  arguments->slots[59] = frame->slots[59] /* temp__60 */;
  arguments->slots[60] = frame->slots[60] /* temp__61 */;
  arguments->slots[61] = frame->slots[61] /* temp__62 */;
  arguments->slots[62] = frame->slots[62] /* temp__63 */;
  arguments->slots[63] = frame->slots[63] /* temp__64 */;
  arguments->slots[64] = frame->slots[64] /* temp__65 */;
  arguments->slots[65] = frame->slots[65] /* temp__66 */;
  arguments->slots[66] = frame->slots[66] /* temp__67 */;
  arguments->slots[67] = frame->slots[67] /* temp__68 */;
  arguments->slots[68] = frame->slots[68] /* temp__69 */;
  arguments->slots[69] = frame->slots[69] /* temp__70 */;
  arguments->slots[70] = frame->slots[70] /* temp__71 */;
  arguments->slots[71] = frame->slots[71] /* temp__72 */;
  arguments->slots[72] = frame->slots[72] /* temp__73 */;
  arguments->slots[73] = frame->slots[73] /* temp__74 */;
  arguments->slots[74] = frame->slots[74] /* temp__75 */;
  arguments->slots[75] = frame->slots[75] /* temp__76 */;
  arguments->slots[76] = frame->slots[76] /* temp__77 */;
  arguments->slots[77] = frame->slots[77] /* temp__78 */;
  arguments->slots[78] = frame->slots[78] /* temp__79 */;
  arguments->slots[79] = frame->slots[79] /* temp__80 */;
  arguments->slots[80] = frame->slots[80] /* temp__81 */;
  arguments->slots[81] = frame->slots[81] /* temp__82 */;
  arguments->slots[82] = frame->slots[82] /* temp__83 */;
  arguments->slots[83] = frame->slots[83] /* temp__84 */;
  arguments->slots[84] = frame->slots[84] /* temp__85 */;
  arguments->slots[85] = frame->slots[85] /* temp__86 */;
  arguments->slots[86] = frame->slots[86] /* temp__87 */;
  arguments->slots[87] = frame->slots[87] /* temp__88 */;
  arguments->slots[88] = frame->slots[88] /* temp__89 */;
  arguments->slots[89] = frame->slots[89] /* temp__90 */;
  arguments->slots[90] = frame->slots[90] /* temp__91 */;
  arguments->slots[91] = frame->slots[91] /* temp__92 */;
  arguments->slots[92] = frame->slots[92] /* temp__93 */;
  arguments->slots[93] = frame->slots[93] /* temp__94 */;
  arguments->slots[94] = frame->slots[94] /* temp__95 */;
  arguments->slots[95] = frame->slots[95] /* temp__96 */;
  arguments->slots[96] = frame->slots[96] /* temp__97 */;
  arguments->slots[97] = frame->slots[97] /* temp__98 */;
  arguments->slots[98] = frame->slots[98] /* temp__99 */;
  arguments->slots[99] = frame->slots[99] /* temp__100 */;
  arguments->slots[100] = frame->slots[100] /* temp__101 */;
  arguments->slots[101] = frame->slots[101] /* temp__102 */;
  arguments->slots[102] = frame->slots[102] /* temp__103 */;
  arguments->slots[103] = frame->slots[103] /* temp__104 */;
  arguments->slots[104] = frame->slots[104] /* temp__105 */;
  arguments->slots[105] = frame->slots[105] /* temp__106 */;
  arguments->slots[106] = frame->slots[106] /* temp__107 */;
  arguments->slots[107] = frame->slots[107] /* temp__108 */;
  arguments->slots[108] = frame->slots[108] /* temp__109 */;
  arguments->slots[109] = frame->slots[109] /* temp__110 */;
  arguments->slots[110] = frame->slots[110] /* temp__111 */;
  arguments->slots[111] = frame->slots[111] /* temp__112 */;
  arguments->slots[112] = frame->slots[112] /* temp__113 */;
  arguments->slots[113] = frame->slots[113] /* temp__114 */;
  arguments->slots[114] = frame->slots[114] /* temp__115 */;
  arguments->slots[115] = frame->slots[115] /* temp__116 */;
  arguments->slots[116] = frame->slots[116] /* temp__117 */;
  arguments->slots[117] = frame->slots[117] /* temp__118 */;
  arguments->slots[118] = frame->slots[118] /* temp__119 */;
  arguments->slots[119] = frame->slots[119] /* temp__120 */;
  arguments->slots[120] = frame->slots[120] /* temp__121 */;
  arguments->slots[121] = frame->slots[121] /* temp__122 */;
  arguments->slots[122] = frame->slots[122] /* temp__123 */;
  arguments->slots[123] = frame->slots[123] /* temp__124 */;
  arguments->slots[124] = frame->slots[124] /* temp__125 */;
  arguments->slots[125] = frame->slots[125] /* temp__126 */;
  arguments->slots[126] = frame->slots[126] /* temp__127 */;
  arguments->slots[127] = frame->slots[127] /* temp__128 */;
  arguments->slots[128] = frame->slots[128] /* temp__129 */;
  arguments->slots[129] = frame->slots[129] /* temp__130 */;
  arguments->slots[130] = frame->slots[130] /* temp__131 */;
  arguments->slots[131] = frame->slots[131] /* temp__132 */;
  arguments->slots[132] = frame->slots[132] /* temp__133 */;
  arguments->slots[133] = frame->slots[133] /* temp__134 */;
  arguments->slots[134] = frame->slots[134] /* temp__135 */;
  arguments->slots[135] = frame->slots[135] /* temp__136 */;
  arguments->slots[136] = frame->slots[136] /* temp__137 */;
  arguments->slots[137] = frame->slots[137] /* temp__138 */;
  arguments->slots[138] = frame->slots[138] /* temp__139 */;
  arguments->slots[139] = frame->slots[139] /* temp__140 */;
  arguments->slots[140] = frame->slots[140] /* temp__141 */;
  arguments->slots[141] = frame->slots[141] /* temp__142 */;
  arguments->slots[142] = frame->slots[142] /* temp__143 */;
  arguments->slots[143] = frame->slots[143] /* temp__144 */;
  arguments->slots[144] = frame->slots[144] /* temp__145 */;
  arguments->slots[145] = frame->slots[145] /* temp__146 */;
  arguments->slots[146] = frame->slots[146] /* temp__147 */;
  arguments->slots[147] = frame->slots[147] /* temp__148 */;
  arguments->slots[148] = frame->slots[148] /* temp__149 */;
  arguments->slots[149] = frame->slots[149] /* temp__150 */;
  arguments->slots[150] = frame->slots[150] /* temp__151 */;
  arguments->slots[151] = frame->slots[151] /* temp__152 */;
  arguments->slots[152] = frame->slots[152] /* temp__153 */;
  arguments->slots[153] = frame->slots[153] /* temp__154 */;
  arguments->slots[154] = frame->slots[154] /* temp__155 */;
  arguments->slots[155] = frame->slots[155] /* temp__156 */;
  arguments->slots[156] = frame->slots[156] /* temp__157 */;
  arguments->slots[157] = frame->slots[157] /* temp__158 */;
  arguments->slots[158] = frame->slots[158] /* temp__159 */;
  arguments->slots[159] = frame->slots[159] /* temp__160 */;
  arguments->slots[160] = frame->slots[160] /* temp__161 */;
  arguments->slots[161] = frame->slots[161] /* temp__162 */;
  arguments->slots[162] = frame->slots[162] /* temp__163 */;
  arguments->slots[163] = frame->slots[163] /* temp__164 */;
  arguments->slots[164] = frame->slots[164] /* temp__165 */;
  arguments->slots[165] = frame->slots[165] /* temp__166 */;
  arguments->slots[166] = frame->slots[166] /* temp__167 */;
  arguments->slots[167] = frame->slots[167] /* temp__168 */;
  arguments->slots[168] = frame->slots[168] /* temp__169 */;
  arguments->slots[169] = frame->slots[169] /* temp__170 */;
  arguments->slots[170] = frame->slots[170] /* temp__171 */;
  arguments->slots[171] = frame->slots[171] /* temp__172 */;
  arguments->slots[172] = frame->slots[172] /* temp__173 */;
  arguments->slots[173] = frame->slots[173] /* temp__174 */;
  arguments->slots[174] = frame->slots[174] /* temp__175 */;
  arguments->slots[175] = frame->slots[175] /* temp__176 */;
  arguments->slots[176] = frame->slots[176] /* temp__177 */;
  arguments->slots[177] = frame->slots[177] /* temp__178 */;
  arguments->slots[178] = frame->slots[178] /* temp__179 */;
  arguments->slots[179] = frame->slots[179] /* temp__180 */;
  arguments->slots[180] = frame->slots[180] /* temp__181 */;
  arguments->slots[181] = frame->slots[181] /* temp__182 */;
  arguments->slots[182] = frame->slots[182] /* temp__183 */;
  arguments->slots[183] = frame->slots[183] /* temp__184 */;
  arguments->slots[184] = frame->slots[184] /* temp__185 */;
  arguments->slots[185] = frame->slots[185] /* temp__186 */;
  arguments->slots[186] = frame->slots[186] /* temp__187 */;
  arguments->slots[187] = frame->slots[187] /* temp__188 */;
  arguments->slots[188] = frame->slots[188] /* temp__189 */;
  arguments->slots[189] = frame->slots[189] /* temp__190 */;
  arguments->slots[190] = frame->slots[190] /* temp__191 */;
  arguments->slots[191] = frame->slots[191] /* temp__192 */;
  arguments->slots[192] = frame->slots[192] /* temp__193 */;
  arguments->slots[193] = frame->slots[193] /* temp__194 */;
  arguments->slots[194] = frame->slots[194] /* temp__195 */;
  arguments->slots[195] = frame->slots[195] /* temp__196 */;
  arguments->slots[196] = frame->slots[196] /* temp__197 */;
  arguments->slots[197] = frame->slots[197] /* temp__198 */;
  arguments->slots[198] = frame->slots[198] /* temp__199 */;
  arguments->slots[199] = frame->slots[199] /* temp__200 */;
  arguments->slots[200] = frame->slots[200] /* temp__201 */;
  arguments->slots[201] = frame->slots[201] /* temp__202 */;
  arguments->slots[202] = frame->slots[202] /* temp__203 */;
  arguments->slots[203] = frame->slots[203] /* temp__204 */;
  arguments->slots[204] = frame->slots[204] /* temp__205 */;
  arguments->slots[205] = frame->slots[205] /* temp__206 */;
  arguments->slots[206] = frame->slots[206] /* temp__207 */;
  arguments->slots[207] = frame->slots[207] /* temp__208 */;
  arguments->slots[208] = frame->slots[208] /* temp__209 */;
  arguments->slots[209] = frame->slots[209] /* temp__210 */;
  arguments->slots[210] = frame->slots[210] /* temp__211 */;
  arguments->slots[211] = frame->slots[211] /* temp__212 */;
  arguments->slots[212] = frame->slots[212] /* temp__213 */;
  arguments->slots[213] = frame->slots[213] /* temp__214 */;
  arguments->slots[214] = frame->slots[214] /* temp__215 */;
  arguments->slots[215] = frame->slots[215] /* temp__216 */;
  arguments->slots[216] = frame->slots[216] /* temp__217 */;
  arguments->slots[217] = frame->slots[217] /* temp__218 */;
  arguments->slots[218] = frame->slots[218] /* temp__219 */;
  arguments->slots[219] = frame->slots[219] /* temp__220 */;
  arguments->slots[220] = frame->slots[220] /* temp__221 */;
  arguments->slots[221] = frame->slots[221] /* temp__222 */;
  arguments->slots[222] = frame->slots[222] /* temp__223 */;
  arguments->slots[223] = frame->slots[223] /* temp__224 */;
  arguments->slots[224] = frame->slots[224] /* temp__225 */;
  arguments->slots[225] = frame->slots[225] /* temp__226 */;
  arguments->slots[226] = frame->slots[226] /* temp__227 */;
  arguments->slots[227] = frame->slots[227] /* temp__228 */;
  arguments->slots[228] = frame->slots[228] /* temp__229 */;
  arguments->slots[229] = frame->slots[229] /* temp__230 */;
  arguments->slots[230] = frame->slots[230] /* temp__231 */;
  arguments->slots[231] = frame->slots[231] /* temp__232 */;
  arguments->slots[232] = frame->slots[232] /* temp__233 */;
  arguments->slots[233] = frame->slots[233] /* temp__234 */;
  arguments->slots[234] = frame->slots[234] /* temp__235 */;
  arguments->slots[235] = frame->slots[235] /* temp__236 */;
  arguments->slots[236] = frame->slots[236] /* temp__237 */;
  arguments->slots[237] = frame->slots[237] /* temp__238 */;
  arguments->slots[238] = frame->slots[238] /* temp__239 */;
  arguments->slots[239] = frame->slots[239] /* temp__240 */;
  arguments->slots[240] = frame->slots[240] /* temp__241 */;
  arguments->slots[241] = frame->slots[241] /* temp__242 */;
  arguments->slots[242] = frame->slots[242] /* temp__243 */;
  arguments->slots[243] = frame->slots[243] /* temp__244 */;
  result_count = 1;
  myself = get__table();
  func = myself->type;
  frame->cont = cont__2_733;
}
static void cont__2_733(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var.sim2c__runtime_symbols, arguments->slots[0]);
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
EXPORT void collect__runtime_definitions(void) {
  var.sim2c__runtime_symbols = collect_node(var.sim2c__runtime_symbols);
}

static int already_run_phase_1 = false;

EXPORT void phase_1__runtime_definitions(void) {
  if (already_run_phase_1) return;
  already_run_phase_1 = true;
  register_module_info(&module_info);
}

static int already_run_phase_2 = false;

EXPORT void phase_2__runtime_definitions(void) {
  if (already_run_phase_2) return;
  already_run_phase_2 = true;
  set_module("runtime_definitions");
  string__fa728015cb16b81 = from_latin_1_string("ASM", 3);
  string__8edd415ac72451d0 = from_latin_1_string(
    "#if defined(__GNUC__) && !defined(__clang__) && defined(__x86_64)\n"
    "  #define ASM(x) asm(x)\n"
    "#else\n"
    "  #define ASM(x)\n"
    "#endif\n",
    120);
  string__800a0c585ff0632 = from_latin_1_string("REGISTER", 8);
  string__5c95584625416db4 = from_latin_1_string(
    "#if defined(__GNUC__) && !defined(__clang__) && defined(__x86_64)\n"
    "  #define REGISTER register\n"
    "#else\n"
    "  #define REGISTER IMPORT\n"
    "#endif\n",
    133);
  string__610a38f055666a5 = from_latin_1_string("VAR_TYPE", 8);
  string__3e779bba71ff6e96 = from_latin_1_string(
    "typedef enum {\n"
    "  VT_POLYMORPHIC,\n"
    "  VT_SINGLE_ASSIGN_STATIC,\n"
    "  VT_MULTI_ASSIGN_STATIC,\n"
    "  VT_SINGLE_ASSIGN_DYNAMIC,\n"
    "  VT_MULTI_ASSIGN_DYNAMIC,\n"
    "} VAR_TYPE;\n",
    153);
  string__1580bcaf2d42dade = from_latin_1_string("ATTRIBUTE_ENTRY", 15);
  string__56c3d0662f712784 = from_latin_1_string("typedef struct ATTRIBUTE_ENTRY ATTRIBUTE_ENTRY;\012", 48);
  string__966c1d52f9f0535e = from_latin_1_string("SYMBOL_ENTRY", 12);
  string__9f2336b788df6407 = from_latin_1_string("typedef struct SYMBOL_ENTRY SYMBOL_ENTRY;\012", 42);
  string__69c55d0406b923b8 = from_latin_1_string("HASH_ENTRY", 10);
  string__fc5ea67cb9ff6239 = from_latin_1_string("typedef struct HASH_ENTRY HASH_ENTRY;\012", 38);
  string__5db1024c9851410f = from_latin_1_string("C_FUNCTION", 10);
  string__a1dd1a49069005db = from_latin_1_string(
    "typedef struct {\n"
    "  const char *name;\n"
    "  void **func;\n"
    "  const char *module_name;\n"
    "} C_FUNCTION;\n",
    93);
  string__786504f5b93f55fd = from_latin_1_string("runtime_major_version", 21);
  string__86acba43b7c3c22a = from_latin_1_string("int runtime_major_version(void);\012", 33);
  string__786504f5b92f55fc = from_latin_1_string("runtime_minor_version", 21);
  string__86acaa43b6c3c22a = from_latin_1_string("int runtime_minor_version(void);\012", 33);
  string__7690e6a93c025e80 = from_latin_1_string("runtime_revision", 16);
  string__f62e6c6074331b2f = from_latin_1_string("int runtime_revision(void);\012", 28);
  string__a8d3ab331eb668e7 = from_latin_1_string("polymorphic_function_count", 26);
  string__bdeaeb384def5a1 = from_latin_1_string("int polymorphic_function_count;\012", 32);
  string__77b931a5baaa8bfc = from_latin_1_string("polymorphic_function_with_setter_count", 38);
  string__b46169d78bdd1cff = from_latin_1_string("int polymorphic_function_with_setter_count;\012", 44);
  string__b4d3ad331eeeb8e0 = from_latin_1_string("polymorphic_function_names", 26);
  string__301d5357b968136a = from_latin_1_string("const char **polymorphic_function_names;\012", 41);
  string__3d988d5d234b8764 = from_latin_1_string("set_module", 10);
  string__1a135fbcb802cc05 = from_latin_1_string("void set_module(const char *name);\012", 35);
  string__dc6342966f81738c = from_latin_1_string("register_module_info", 20);
  string__6777bcdceff69976 = from_latin_1_string("void register_module_info(MODULE_INFO *info);\012", 46);
  string__74b135724d6dbce9 = from_latin_1_string("define_namespace", 16);
  string__3ef83756322d0f8 = from_latin_1_string("void define_namespace(const char *namespace);\012", 46);
  string__51af6105266784c5 = from_latin_1_string("set_used_namespaces", 19);
  string__6e38e34fa7ce2068 = from_latin_1_string("void set_used_namespaces(const char **namespaces);\012", 51);
  string__6a8c256a04788689 = from_latin_1_string("from_bool", 9);
  string__3e6f7d71ebbc1fd7 = from_latin_1_string("NODE *from_bool(int val);\012", 26);
  string__10dcaf9184a54094 = from_latin_1_string("from_int", 8);
  string__9d29beb6e8094e17 = from_latin_1_string("NODE *from_int(int val);\012", 25);
  string__768c256a04708682 = from_latin_1_string("from_long", 9);
  string__205751daa5312b90 = from_latin_1_string("NODE *from_long(long val);\012", 27);
  string__29502504369be455 = from_latin_1_string("from_int64", 10);
  string__2e6aba362d00a1da = from_latin_1_string("NODE *from_int64(int64_t val);\012", 31);
  string__1c21a45122913ab3 = from_latin_1_string("from_uint32", 11);
  string__91b47fced47c61e2 = from_latin_1_string("NODE *from_uint32(uint32_t val);\012", 33);
  string__1c21a45122b93ab5 = from_latin_1_string("from_uint64", 11);
  string__d1b24fced47c61cb = from_latin_1_string("NODE *from_uint64(uint64_t val);\012", 33);
  string__2a21a1d9a0695ae4 = from_latin_1_string("from_double", 11);
  string__cebc109d1e7797e2 = from_latin_1_string("NODE *from_double(double val);\012", 31);
  string__f7822ff0f11c2c3 = from_latin_1_string("from_digit_string", 17);
  string__290e2a52fea6fc66 = from_latin_1_string("NODE *from_digit_string(const char *str);\012", 42);
  string__88904ccd590813f = from_latin_1_string("from_uchar32", 12);
  string__b475c09adc8d6659 = from_latin_1_string("NODE *from_uchar32(unsigned int chr);\012", 38);
  string__2696ba098b1916ef = from_latin_1_string("from_c_string", 13);
  string__7be49ac3d7efe7a6 = from_latin_1_string("NODE *from_c_string(const char *str);\012", 38);
  string__f8dc63c35d5f67e4 = from_latin_1_string("from_latin_1_string", 19);
  string__bb39174a4b655c1c = from_latin_1_string("NODE *from_latin_1_string(const char *str, long len);\012", 54);
  string__6148905dd1501604 = from_latin_1_string("from_uint32_string", 18);
  string__c2bd832925dd7b1c = from_latin_1_string("NODE *from_uint32_string(const uint32_t *str, long len);\012", 57);
  string__c81c58c835e0c166 = from_latin_1_string("from_arguments", 14);
  string__f28c00dfeab5a4f5 = from_latin_1_string("NODE *from_arguments(int first_idx, int count);\012", 48);
  string__dc074c1662997308 = from_latin_1_string("register_unique_item", 20);
  string__ecd63bf007719c5e = from_latin_1_string("NODE *register_unique_item(const char *name);\012", 46);
  string__81d201e3591a9487 = from_latin_1_string("define_c_function", 17);
  string__bd156810a3b87b39 = from_latin_1_string("void define_c_function(const char *name, void *func);\012", 54);
  string__34c427046666a791 = from_latin_1_string("register_polymorphic_function", 29);
  string__1852e8fc677301ab = from_latin_1_string("void register_polymorphic_function(const char *name, int *id_p);\012", 65);
  string__4f152c2abbd22d29 = from_latin_1_string("register_polymorphic_function_with_setter", 41);
  string__b2c113b0186c2dd1 = from_latin_1_string("void register_polymorphic_function_with_setter(const char *name, int *id_p);\012", 77);
  string__caafa59fe636a9de = from_latin_1_string("define_polymorphic_function", 27);
  string__e4d263547623cea0 = from_latin_1_string(
    "void define_polymorphic_function(\n"
    "  const char *namespace, const char *name, NODE_GETTER getter, int *id_p,\n"
    "  NODE **var_p\n"
    ");\n",
    126);
  string__4a15c8d55d6a0491 = from_latin_1_string("define_polymorphic_function_with_setter", 39);
  string__21c0f79678df3c50 = from_latin_1_string(
    "void define_polymorphic_function_with_setter(\n"
    "  const char *namespace, const char *name, NODE_GETTER getter, int *id_p,\n"
    "  NODE **var_p\n"
    ");\n",
    138);
  string__2d9e9f5fd5d9523e = from_latin_1_string("define_privileged_polymorphic_function", 38);
  string__6445dfc09129e2bc = from_latin_1_string(
    "void define_privileged_polymorphic_function(\n"
    "  const char *namespace, const char *name, NODE_GETTER getter, int id,\n"
    "  NODE **var_p\n"
    ");\n",
    134);
  string__7699f5c17fb1f0c5 = from_latin_1_string("define_single_assign_static", 27);
  string__bd51ec8ac074a909 = from_latin_1_string(
    "void define_single_assign_static(\n"
    "  const char *namespace, const char *name,\n"
    "  NODE_GETTER getter, NODE **var_p\n"
    ");\n",
    115);
  string__9d2186757f44a3c = from_latin_1_string("define_multi_assign_static", 26);
  string__d8100904e5447128 = from_latin_1_string(
    "void define_multi_assign_static(\n"
    "  const char *namespace, const char *name,\n"
    "  NODE_GETTER getter, NODE_SETTER setter\n"
    ");\n",
    120);
  string__1614e67e91066b2b = from_latin_1_string("register_dynamic", 16);
  string__da679ac2fd23801b = from_latin_1_string("void register_dynamic(int *id_p);\012", 34);
  string__8457fc89067b44ac = from_latin_1_string("define_single_assign_dynamic", 28);
  string__8d9a40a45ca1f46 = from_latin_1_string(
    "void define_single_assign_dynamic(\n"
    "  const char *namespace, const char *name,\n"
    "  NODE_GETTER getter, NODE_SETTER definer,\n"
    "  int *id_p\n"
    ");\n",
    136);
  string__e966bea4d1b0bef3 = from_latin_1_string("define_multi_assign_dynamic", 27);
  string__4203ade7496d3cba = from_latin_1_string(
    "void define_multi_assign_dynamic(\n"
    "  const char *namespace, const char *name,\n"
    "  NODE_GETTER getter, NODE_SETTER setter, NODE_SETTER definer,\n"
    "  int *id_p\n"
    ");\n",
    155);
  string__bb073f307486f5e2 = from_latin_1_string("define_type_function", 20);
  string__d8ae744927741c5e = from_latin_1_string(
    "void define_type_function(\n"
    "  const char *namespace, const char *name, FUNC type, int par_cnt\n"
    ");\n",
    96);
  string__50d53079c2d41e49 = from_latin_1_string("define_attribute", 16);
  string__d699aac52d63a802 = from_latin_1_string(
    "void define_attribute(\n"
    "  const char *namespace, const char *name,\n"
    "  int id, NODE *attribute\n"
    ");\n",
    95);
  string__6a969a66ba3e062e = from_latin_1_string("define_method", 13);
  string__3ca1e27da11d6a79 = from_latin_1_string(
    "void define_method(\n"
    "  const char *namespace, const char *name,\n"
    "  int id, NODE *method\n"
    ");\n",
    89);
  string__f22e4ba252bb0402 = from_latin_1_string("use_polymorphic_function", 24);
  string__cd13cee030a4034b = from_latin_1_string(
    "void use_polymorphic_function(\n"
    "  const char *namespace, const char *name, NODE_GETTER *getter, int *id\n"
    ");\n",
    106);
  string__9c6f2af22609a633 = from_latin_1_string("use_read_only", 13);
  string__b5cfa062437d6535 = from_latin_1_string(
    "void use_read_only(\n"
    "  const char *namespace, const char *name,\n"
    "  NODE_GETTER *getter, NODE_GETTER *get_value_or_future\n"
    ");\n",
    122);
  string__6f91310d31f5631c = from_latin_1_string("use_read_write", 14);
  string__5ca1f7a22b3232c2 = from_latin_1_string(
    "void use_read_write(\n"
    "  const char *namespace, const char *name,\n"
    "  NODE_GETTER *getter, NODE_SETTER *setter\n"
    ");\n",
    110);
  string__f5ba58e4689a80a3 = from_latin_1_string("use_single_assign_dynamic", 25);
  string__d107ad9b7b630943 = from_latin_1_string(
    "void use_single_assign_dynamic(\n"
    "  const char *namespace, const char *name,\n"
    "  NODE_GETTER *getter, NODE_SETTER *definer\n"
    ");\n",
    122);
  string__d1e75099653d132f = from_latin_1_string("use_multi_assign_dynamic", 24);
  string__1eb9413f2d2e180c = from_latin_1_string(
    "void use_multi_assign_dynamic(\n"
    "  const char *namespace, const char *name,\n"
    "  NODE_GETTER *getter, NODE_SETTER *setter, NODE_SETTER *definer\n"
    ");\n",
    142);
  string__15d9100c1cca979d = from_latin_1_string("resolve_symbols", 15);
  string__bd4383921548788 = from_latin_1_string("void resolve_symbols(void);\012", 28);
  string__366b3f231611767c = from_latin_1_string("resolve_attributes", 18);
  string__cf523af04f93c1a2 = from_latin_1_string("void resolve_attributes(void);\012", 31);
  string__5e0ae28b5c407d7c = from_latin_1_string("NODE", 4);
  string__8f20b7aa2b348ba = from_latin_1_string("typedef union NODE NODE;\012", 25);
  string__4e0ae40b5c107d7a = from_latin_1_string("FUNC", 4);
  string__5ad1f0da53fa6a79 = from_latin_1_string("typedef void (*FUNC)(void);\012", 28);
  string__682044480a23ffd9 = from_latin_1_string("NODE_GETTER", 11);
  string__c6ec8dca53a5a1af = from_latin_1_string("typedef NODE *(*NODE_GETTER)(void);\012", 36);
  string__682044420a23ffd9 = from_latin_1_string("NODE_SETTER", 11);
  string__b8b9c6a2212e34c0 = from_latin_1_string("typedef void (*NODE_SETTER)(NODE *);\012", 37);
  string__28002bbaa0792117 = from_latin_1_string("COLLECTOR", 9);
  string__9ae348be480e8e0 = from_latin_1_string("typedef void *COLLECTOR(void *);\012", 33);
  string__73b53d02825023b3 = from_latin_1_string("DESTRUCTOR", 10);
  string__b20c4a77a3ac08a2 = from_latin_1_string("typedef void (*DESTRUCTOR)(void *);\012", 36);
  string__1a1f5edb80d91292 = from_latin_1_string("VTABLE", 6);
  string__c4d379f2bb5c3e41 = from_latin_1_string(
    "typedef struct VTABLE {\n"
    "  size_t size;\n"
    "  COLLECTOR *collect;\n"
    "  int8_t (*to_int8)(NODE *);\n"
    "  int16_t (*to_int16)(NODE *);\n"
    "  int32_t (*to_int32)(NODE *);\n"
    "  int64_t (*to_int64)(NODE *);\n"
    "  uint8_t (*to_uint8)(NODE *);\n"
    "  uint16_t (*to_uint16)(NODE *);\n"
    "  uint32_t (*to_uint32)(NODE *);\n"
    "  uint64_t (*to_uint64)(NODE *);\n"
    "  uint32_t (*to_uchar32)(NODE *);\n"
    "  int (*to_bool)(NODE *);\n"
    "  int (*to_int)(NODE *);\n"
    "  long (*to_long)(NODE *);\n"
    "  double (*to_double)(NODE *);\n"
    "  char *(*to_c_string)(NODE *);\n"
    "  uint8_t *(*to_octets)(NODE *, long *size_p);\n"
    "  NODE *(*get_item_of)(NODE *, long idx);\n"
    "  long (*length_of)(NODE *);\n"
    "  void (*unfold)(NODE *);\n"
    "  long (*debug_string)(NODE *, int indent, int max_depth, char *buf);\n"
    "} VTABLE;\n",
    712);
  string__301f5ad700906292 = from_latin_1_string("OCTREE", 6);
  string__8106f1378366edc = from_latin_1_string(
    "typedef struct OCTREE {\n"
    "  struct OCTREE *nodes[8];\n"
    "} OCTREE;\n",
    61);
  string__5fad150f13015352 = from_latin_1_string("ATTRIBUTES", 10);
  string__86e05501f2bf69ee = from_latin_1_string(
    "typedef struct ATTRIBUTES {\n"
    "  struct VTABLE *vtable;\n"
    "  struct OCTREE *nodes[7];\n"
    "} ATTRIBUTES;\n",
    94);
  string__3470a78105cf84f3 = from_latin_1_string("DYNAMICS", 8);
  string__5dec1a1e2d91f421 = from_latin_1_string(
    "typedef struct DYNAMICS {\n"
    "  struct OCTREE *nodes[8];\n"
    "} DYNAMICS;\n",
    65);
  string__1c6c7289032a5d69 = from_latin_1_string("SIMPLE_NODE", 11);
  string__1dd5fa7b31b5023d = from_latin_1_string(
    "typedef struct SIMPLE_NODE {\n"
    "  FUNC type;\n"
    "  struct ATTRIBUTES *attributes;\n"
    "} SIMPLE_NODE;\n",
    90);
  string__d4880084942830bf = from_latin_1_string("CLOSURE", 7);
  string__6fd6eaaa0ae0aa48 = from_latin_1_string(
    "typedef struct CLOSURE {\n"
    "  FUNC type;\n"
    "  struct ATTRIBUTES *attributes;\n"
    "  int parameter_count;\n"
    "  struct FRAME *frame;\n"
    "} CLOSURE;\n",
    128);
  string__640a78105afa4ae = from_latin_1_string("FUNCTION", 8);
  string__4e857cd3f4048898 = from_latin_1_string(
    "typedef struct FUNCTION {\n"
    "  FUNC type;\n"
    "  struct ATTRIBUTES *attributes;\n"
    "  int parameter_count;\n"
    "} FUNCTION;\n",
    107);
  string__22640217ef38138c = from_latin_1_string("CONTINUATION", 12);
  string__aca6b18f1d890a7a = from_latin_1_string(
    "typedef struct CONTINUATION {\n"
    "  FUNC type;\n"
    "  struct ATTRIBUTES *attributes;\n"
    "  int result_count;\n"
    "  struct FRAME *frame;\n"
    "  struct DYNAMICS *dynamics;\n"
    "  struct FRAME *exit_frame; // used by exit-functions\n"
    "} CONTINUATION;\n",
    218);
  string__4950e37017ade5ae = from_latin_1_string("ATTRIBUTE_LIST", 14);
  string__196c75ae6866989e = from_latin_1_string(
    "typedef struct ATTRIBUTE_LIST {\n"
    "  struct ATTRIBUTE_LIST *link;\n"
    "  int idx;\n"
    "  void *attr;\n"
    "} ATTRIBUTE_LIST;\n",
    106);
  string__301f5b1380290292 = from_latin_1_string("FUTURE", 6);
  string__998dcabeeeee256c = from_latin_1_string(
    "typedef struct FUTURE {\n"
    "  FUNC type;\n"
    "  struct ATTRIBUTES *attributes;\n"
    "  NODE *link;\n"
    "  struct ATTRIBUTE_LIST *pending_attributes;\n"
    "  NODE *dependent_futures;\n"
    "  NODE *prototype;\n"
    "  long is_already_initialized;\n"
    "  NODE *pad_2;\n"
    "} FUTURE;\n",
    231);
  string__440ae00b5c007d75 = from_latin_1_string("CELL", 4);
  string__552dc13bf9788e15 = from_latin_1_string(
    "typedef struct CELL {\n"
    "  FUNC type;\n"
    "  struct ATTRIBUTES *attributes;\n"
    "  NODE *contents;\n"
    "} CELL;\n",
    94);
  string__2e5ae343eba27012 = from_latin_1_string("FRAME", 5);
  string__18822595562573af = from_latin_1_string(
    "typedef struct FRAME {\n"
    "  FUNC cont;\n"
    "  struct FRAME *caller_frame;\n"
    "  long caller_result_count;\n"
    "  long slot_count;\n"
    "  NODE *slots[0];\n"
    "} FRAME;\n",
    140);
  string__67d12b89151881ee = from_latin_1_string("FRAME_INFO", 10);
  string__97eba66a53ce2418 = from_latin_1_string(
    "typedef struct FRAME_INFO {\n"
    "  int var_count;\n"
    "  const char *var_names[];\n"
    "} FRAME_INFO;\n",
    86);
  string__659c1a461307f144 = from_latin_1_string("CONTINUATION_INFO", 17);
  string__aff0e1bffd69d09e = from_latin_1_string(
    "typedef struct CONTINUATION_INFO {\n"
    "  FUNC continuation;\n"
    "  struct FRAME_INFO *frame_info;\n"
    "  uint16_t first_line;\n"
    "  uint16_t last_line;\n"
    "  uint8_t first_column;\n"
    "  uint8_t last_column;\n"
    "  uint8_t submodule_index;\n"
    "  uint8_t unused;\n"
    "} CONTINUATION_INFO;\n",
    247);
  string__926c42c90a3a5dc4 = from_latin_1_string("MODULE_INFO", 11);
  string__35dcdd757d8ff36a = from_latin_1_string(
    "typedef struct MODULE_INFO {\n"
    "  struct MODULE_INFO *link;\n"
    "  const char *name;\n"
    "  struct CONTINUATION_INFO *continuation_info;\n"
    "  int continuation_count;\n"
    "  NODE **var_tab;\n"
    "  const char **var_names;\n"
    "  int top_level_count;\n"
    "  const char **used_namespaces;\n"
    "  const char *filenames[];\n"
    "} MODULE_INFO;\n",
    291);
  string__9a0c8a840b2a5eac = from_latin_1_string("EVENT__MODE", 11);
  string__699ad5fe935c0c = from_latin_1_string(
    "typedef enum {\n"
    "  EM__NORMAL,\n"
    "  EM__RECORD,\n"
    "  EM__REPLAY\n"
    "} EVENT__MODE;\n",
    71);
  string__92381b92f44420eb = from_latin_1_string("MEMORY_BLOCK", 12);
  string__ad6cb4d361a97110 = from_latin_1_string(
    "typedef struct MEMORY_BLOCK {\n"
    "  struct MEMORY_BLOCK *link;\n"
    "  long mark;\n"
    "  DESTRUCTOR destructor;\n"
    "} MEMORY_BLOCK;\n",
    113);
  string__b203ec07e46c6d80 = from_latin_1_string("PHASE_2_COLLECTOR", 17);
  string__8f7c86910d6d0ec0 = from_latin_1_string(
    "typedef struct PHASE_2_COLLECTOR {\n"
    "  void *dummy;\n"
    "  void *next_collector;\n"
    "  void (*collector)(void *data);\n"
    "} PHASE_2_COLLECTOR;\n",
    128);
  string__dfd1ce1d312022e7 = from_latin_1_string("argument_count", 14);
  string__70bef8fa01ea78c4 = from_latin_1_string("REGISTER int argument_count ASM(\042ebx\042);\012", 40);
  string__64ac252603a3a696 = from_latin_1_string("arguments", 9);
  string__501ffc7c0e5fce8d = from_latin_1_string("REGISTER FRAME *arguments ASM(\042r12\042);\012", 38);
  string__7e1f570601dbc2b1 = from_latin_1_string("myself", 6);
  string__7ed5b7453a0b28eb = from_latin_1_string("REGISTER NODE *myself ASM(\042r13\042);\012", 34);
  string__e0aec0b5d107d5a = from_latin_1_string("func", 4);
  string__226dfcc2010b42bb = from_latin_1_string("REGISTER FUNC func ASM(\042r14\042);\012", 31);
  string__6e5aeb43eaa07032 = from_latin_1_string("frame", 5);
  string__2cf4a351abcf4415 = from_latin_1_string("REGISTER FRAME *frame ASM(\042r15\042);\012", 34);
  string__d48de512cf50371c = from_latin_1_string("result_count", 12);
  string__8f245610f4cd3fb7 = from_latin_1_string("int result_count;\012", 18);
  string__74f0af9104cd80d3 = from_latin_1_string("dynamics", 8);
  string__1b7f73c5bf94e5d0 = from_latin_1_string("DYNAMICS *dynamics;\012", 20);
  string__6c94222b8f3884e6 = from_latin_1_string("main_argc", 9);
  string__5ae9ab7012ed0dc4 = from_latin_1_string("int main_argc;\012", 15);
  string__6c94222b8f3884f3 = from_latin_1_string("main_argv", 9);
  string__b4d23a65497e01c1 = from_latin_1_string("char **main_argv;\012", 18);
  string__da8d82842a2a5a84 = from_latin_1_string("event__mode", 11);
  string__ab557f0a5c48499b = from_latin_1_string("EVENT__MODE event__mode;\012", 25);
  string__501f57078042a2a7 = from_latin_1_string("node_p", 6);
  string__f43fa690fc94429d = from_latin_1_string("void *node_p;\012", 14);
  string__efcd0668b0ae04c6 = from_latin_1_string("update_start_p", 14);
  string__6f7ba838857d0d29 = from_latin_1_string("void *update_start_p;\012", 22);
  string__2729ba62a63415a9 = from_latin_1_string("static_node_buf", 15);
  string__411ed56d73ccbf77 = from_latin_1_string("void *static_node_buf;\012", 23);
  string__25a63323422a9216 = from_latin_1_string("static_node_buf_end", 19);
  string__3156ce0eca29841b = from_latin_1_string("void *static_node_buf_end;\012", 27);
  string__bc56b0920bfa074e = from_latin_1_string("coll_node_buf", 13);
  string__6c603b3047444a74 = from_latin_1_string("void *coll_node_buf;\012", 21);
  string__d50939ffa304eba1 = from_latin_1_string("coll_node_buf_end", 17);
  string__dfb31d464579b6cc = from_latin_1_string("void *coll_node_buf_end;\012", 25);
  string__7ca0252e172b1501 = from_latin_1_string("undefined", 9);
  string__35b46e45a024cc89 = from_latin_1_string("NODE *undefined;\012", 17);
  string__360ae80b5df07d56 = from_latin_1_string("zero", 4);
  string__6ff45b807d805ee8 = from_latin_1_string("NODE *zero;\012", 12);
  string__62d904ca56abf62f = from_latin_1_string("boolean_true", 12);
  string__a7036984828ad991 = from_latin_1_string("NODE *boolean_true;\012", 20);
  string__52b31fb1ca36ad = from_latin_1_string("boolean_false", 13);
  string__606c03df4d04a811 = from_latin_1_string("NODE *boolean_false;\012", 21);
  string__ee21fa04ce7f45ad = from_latin_1_string("empty_string", 12);
  string__922f8927bcb56a37 = from_latin_1_string("NODE *empty_string;\012", 20);
  string__9a7719701e463c3d = from_latin_1_string("raise_exception_getter", 22);
  string__4dfebf8ce2b979fc = from_latin_1_string("NODE_GETTER raise_exception_getter;\012", 36);
  string__ccb06cae4fc7ced1 = from_latin_1_string("instruction_counter", 19);
  string__f51775fad4122113 = from_latin_1_string("uint64_t instruction_counter;\012", 30);
  string__f10614695d7490c = from_latin_1_string("no_attributes_level_1", 21);
  string__ae72e78740405523 = from_latin_1_string("OCTREE no_attributes_level_1;\012", 30);
  string__f10614695d7490f = from_latin_1_string("no_attributes_level_2", 21);
  string__ae72e74740405523 = from_latin_1_string("OCTREE no_attributes_level_2;\012", 30);
  string__f10614695d7490e = from_latin_1_string("no_attributes_level_3", 21);
  string__ae72e70740405523 = from_latin_1_string("OCTREE no_attributes_level_3;\012", 30);
  string__f10614695d74909 = from_latin_1_string("no_attributes_level_4", 21);
  string__ae72e6c740405523 = from_latin_1_string("OCTREE no_attributes_level_4;\012", 30);
  string__f10614695d74908 = from_latin_1_string("no_attributes_level_5", 21);
  string__ae72e68740405523 = from_latin_1_string("OCTREE no_attributes_level_5;\012", 30);
  string__f10614695d7490b = from_latin_1_string("no_attributes_level_6", 21);
  string__ae72e64740405523 = from_latin_1_string("OCTREE no_attributes_level_6;\012", 30);
  string__f10614695d7490a = from_latin_1_string("no_attributes_level_7", 21);
  string__ae72e60740405523 = from_latin_1_string("OCTREE no_attributes_level_7;\012", 30);
  string__f10614695d74905 = from_latin_1_string("no_attributes_level_8", 21);
  string__ae72e5c740405523 = from_latin_1_string("OCTREE no_attributes_level_8;\012", 30);
  string__a96d37e5269efcea = from_latin_1_string("undefined_attributes_level_1", 28);
  string__d3abaa3aea9568d8 = from_latin_1_string("OCTREE undefined_attributes_level_1;\012", 37);
  string__a96d37e5269efce9 = from_latin_1_string("undefined_attributes_level_2", 28);
  string__d3abaafaea9568d8 = from_latin_1_string("OCTREE undefined_attributes_level_2;\012", 37);
  string__a96d37e5269efce8 = from_latin_1_string("undefined_attributes_level_3", 28);
  string__d3abaabaea9568d8 = from_latin_1_string("OCTREE undefined_attributes_level_3;\012", 37);
  string__a96d37e5269efcef = from_latin_1_string("undefined_attributes_level_4", 28);
  string__d3abab7aea9568d8 = from_latin_1_string("OCTREE undefined_attributes_level_4;\012", 37);
  string__a96d37e5269efcee = from_latin_1_string("undefined_attributes_level_5", 28);
  string__d3abab3aea9568d8 = from_latin_1_string("OCTREE undefined_attributes_level_5;\012", 37);
  string__a96d37e5269efced = from_latin_1_string("undefined_attributes_level_6", 28);
  string__d3ababfaea9568d8 = from_latin_1_string("OCTREE undefined_attributes_level_6;\012", 37);
  string__a96d37e5269efcec = from_latin_1_string("undefined_attributes_level_7", 28);
  string__d3ababbaea9568d8 = from_latin_1_string("OCTREE undefined_attributes_level_7;\012", 37);
  string__a96d37e5269efce3 = from_latin_1_string("undefined_attributes_level_8", 28);
  string__d3aba87aea9568d8 = from_latin_1_string("OCTREE undefined_attributes_level_8;\012", 37);
  string__96bd3c5645503754 = from_latin_1_string("runtime_debug_level", 19);
  string__313ff19f63187450 = from_latin_1_string("int runtime_debug_level;\012", 25);
  string__39a91c6464b48cb7 = from_latin_1_string("unrecoverable_error", 19);
  string__51cfd78644d80c92 = from_latin_1_string("__attribute__ ((noreturn)) void unrecoverable_error(const char *msg, ...);\012", 75);
  string__fd5f7ef32f24bfaa = from_latin_1_string("out_of_memory_error", 19);
  string__fec3a524701ff247 = from_latin_1_string("__attribute__ ((noreturn)) void out_of_memory_error(void);\012", 59);
  string__761587227d4825b9 = from_latin_1_string("invalid_continuation_error", 26);
  string__6d343fd95f2f86f5 = from_latin_1_string("__attribute__ ((noreturn)) void invalid_continuation_error(void);\012", 66);
  string__68a4ad9004756065 = from_latin_1_string("allocate", 8);
  string__828961258c78d260 = from_latin_1_string("void *allocate(long size);\012", 27);
  string__83bbca0be31365ab = from_latin_1_string("allocate_and_clear", 18);
  string__b0f237f00b697e93 = from_latin_1_string("void *allocate_and_clear(long size);\012", 37);
  string__cfe9a9f60d3a5cd4 = from_latin_1_string("allocate_memory", 15);
  string__998fb2a1fe8a0c3e = from_latin_1_string("void *allocate_memory(size_t size);\012", 36);
  string__b1ec1042f2e6e8ff = from_latin_1_string("reallocate_memory", 17);
  string__e4edebbe4882d6ef = from_latin_1_string("void *reallocate_memory(void * buf, size_t size);\012", 50);
  string__cad15e9b2330eaa3 = from_latin_1_string("allocate_gc", 11);
  string__d95df4cca4d2c6fd = from_latin_1_string("void *allocate_gc(long size);\012", 30);
  string__91b7c8dee3bb862a = from_latin_1_string("allocate_arguments", 18);
  string__32a7900019341d55 = from_latin_1_string("void allocate_arguments(void);\012", 31);
  string__5395bcbd356e71b1 = from_latin_1_string("allocate_fixed", 14);
  string__e0605de396839adc = from_latin_1_string("void *allocate_fixed(long size);\012", 33);
  string__42e269e73a13b76b = from_latin_1_string("allocate_fixed_with_destructor", 30);
  string__69dfa40f6a365db = from_latin_1_string("void *allocate_fixed_with_destructor(long size, DESTRUCTOR destructor);\012", 72);
  string__1b77e1575779efa5 = from_latin_1_string("allocate_initialized_frame_gc", 29);
  string__6757b2e2474a0b22 = from_latin_1_string("void allocate_initialized_frame_gc(int slot_idx, int slot_count);\012", 66);
  string__4395be3d357ed1b0 = from_latin_1_string("allocate_large", 14);
  string__e0e85de2d683928c = from_latin_1_string("void *allocate_large(long size);\012", 33);
  string__b1fa1042f2e6e8ff = from_latin_1_string("deallocate_memory", 17);
  string__b16ca6def7b3553c = from_latin_1_string("void deallocate_memory(void *buf);\012", 35);
  string__40aea8b5de07d40 = from_latin_1_string("copy", 4);
  string__e97bf72e3ea776ca = from_latin_1_string("void *copy(const void *buf, long size);\012", 40);
  string__b23dc2be453fb4c = from_latin_1_string("register_phase_3_collector", 26);
  string__68644448021229ea = from_latin_1_string("void register_phase_3_collector(void *data);\012", 45);
  string__edb661f544f7f1b4 = from_latin_1_string("child_changed_state", 19);
  string__58ce4981a1cf1c90 = from_latin_1_string("int child_changed_state;\012", 25);
  string__b7b51829c8931dfe = from_latin_1_string("window_changed_size", 19);
  string__41f55b1721116bb3 = from_latin_1_string("int window_changed_size;\012", 25);
  string__1221a2d3a0a88ae7 = from_latin_1_string("from_printf", 11);
  string__906cbeff26b5017a = from_latin_1_string("NODE *from_printf(const char *msg, ...);\012", 41);
  string__667e759fbd1e073a = from_latin_1_string("runtime_error", 13);
  string__4f98ca907370d4fd = from_latin_1_string("__attribute__ ((noreturn)) void runtime_error(const char *msg, ...);\012", 69);
  string__ac42fe8001c0cf7b = from_latin_1_string("too_few_arguments_error", 23);
  string__90e4557368bcc70c = from_latin_1_string("void too_few_arguments_error(void);\012", 36);
  string__fe16467ca0045e4f = from_latin_1_string("too_many_arguments_error", 24);
  string__4b24985949e64aa0 = from_latin_1_string("void too_many_arguments_error(void);\012", 37);
  string__3c5182f403404f1a = from_latin_1_string("invalid_arguments_error", 23);
  string__e4e6d5f3092cd470 = from_latin_1_string("void invalid_arguments_error(void);\012", 36);
  string__5a7ee7d9a77669df = from_latin_1_string("too_few_results_error", 21);
  string__3e34445dbde01d92 = from_latin_1_string("void too_few_results_error(void);\012", 34);
  string__a8f9f59d763f3b3c = from_latin_1_string("too_many_results_error", 22);
  string__96b12e6b0e8f1ea6 = from_latin_1_string("void too_many_results_error(void);\012", 35);
  string__8a74e5d82136242e = from_latin_1_string("invalid_results_error", 21);
  string__3fb204104c301790 = from_latin_1_string("void invalid_results_error(void);\012", 34);
  string__fad96544e5c0b191 = from_latin_1_string("invalid_index_error", 19);
  string__82b0591fec9d608e = from_latin_1_string("void invalid_index_error(void);\012", 32);
  string__776fc0898d8697f5 = from_latin_1_string("divide_by_zero_error", 20);
  string__de9a692913a186a6 = from_latin_1_string("void divide_by_zero_error(void);\012", 33);
  string__76bf0e1274169131 = from_latin_1_string("not_yet_implemented_error", 25);
  string__682822d0ffcfd8e0 = from_latin_1_string("void not_yet_implemented_error(void);\012", 38);
  string__e0508ed6bc3a9403 = from_latin_1_string("no_such_function", 16);
  string__d9addc1ddea8b503 = from_latin_1_string("void no_such_function(void);\012", 29);
  string__60dde75c27ced2c1 = from_latin_1_string("no_such_attribute", 17);
  string__f20d2016c4807ea2 = from_latin_1_string("void no_such_attribute(void);\012", 30);
  string__6c150ead26004347 = from_latin_1_string("resource_error", 14);
  string__9d8c53f6d9a9a7b7 = from_latin_1_string("void resource_error(void);\012", 27);
  string__4aa8a94984adc172 = from_latin_1_string("io_error", 8);
  string__162c20703a78c3ff = from_latin_1_string("void io_error(void);\012", 21);
  string__b6e0e11e4743dfdf = from_latin_1_string("initialize_runtime", 18);
  string__f2036859ec134a7c = from_latin_1_string("void initialize_runtime(void);\012", 31);
  string__b8e8e210c6d32f89 = from_latin_1_string("initialize_phase_3", 18);
  string__fc82f8a9ba1d427f = from_latin_1_string("void initialize_phase_3(void);\012", 31);
  string__b8e8e210c6d32f8e = from_latin_1_string("initialize_phase_4", 18);
  string__fc82f8a9bd1d427f = from_latin_1_string("void initialize_phase_4(void);\012", 31);
  string__d0e5e8074891f627 = from_latin_1_string("current_mark", 12);
  string__3f5d3a0d2c7bc3c7 = from_latin_1_string("long current_mark;\012", 19);
  string__2b5c4104290394d2 = from_latin_1_string("join_nodes", 10);
  string__5104e1e70e2bbd29 = from_latin_1_string("void join_nodes(void *left_node_pp, void *right_node_pp);\012", 58);
  string__41c85713242372c5 = from_latin_1_string("clone_object_and_attributes", 27);
  string__e51baebf46ac8640 = from_latin_1_string("NODE *clone_object_and_attributes(NODE *node);\012", 47);
  string__5592cf0301411d16 = from_latin_1_string("register_collector", 18);
  string__dee304be4126ea7 = from_latin_1_string("void register_collector(FUNC collector);\012", 41);
  string__56d11b875621f62f = from_latin_1_string("collect_node", 12);
  string__caea8b2ff976ddc3 = from_latin_1_string("NODE *collect_node(NODE *node);\012", 32);
  string__34fd7b2a54432a1f = from_latin_1_string("collect_static_attributes", 25);
  string__2f060df2bab9ebec = from_latin_1_string("void collect_static_attributes(ATTRIBUTES *attributes);\012", 56);
  string__32e13e70f6337af4 = from_latin_1_string("collect_attributes", 18);
  string__8a205606fdc9fcee = from_latin_1_string("ATTRIBUTES *collect_attributes(ATTRIBUTES *attributes);\012", 56);
  string__47935b184e1b3728 = from_latin_1_string("collect_simple_node", 19);
  string__337f24e44c027fbc = from_latin_1_string("void *collect_simple_node(SIMPLE_NODE *node);\012", 46);
  string__9520754d88a4dfe0 = from_latin_1_string("total_garbage_collections", 25);
  string__ae1a6ceddb2e6555 = from_latin_1_string("int total_garbage_collections;\012", 31);
  string__5089ba700d952389 = from_latin_1_string("collect_garbage", 15);
  string__728beb96de734cfe = from_latin_1_string("void collect_garbage();\012", 24);
  string__317937b8f705e12f = from_latin_1_string("indent_to_string", 16);
  string__726eb8f70f88c9b = from_latin_1_string("const char *indent_to_string(int indent);\012", 42);
  string__6e5ae943eab91023 = from_latin_1_string("print", 5);
  string__1248a4b5a2020125 = from_latin_1_string("int print(char **buf_p, const char *format, ...);\012", 50);
  string__a4c11b042d78a9f5 = from_latin_1_string("debug_print", 11);
  string__b17e1477ca7d8644 = from_latin_1_string("int debug_print(int indent, char *buf, const char *format, ...);\012", 65);
  string__c6bc4dbad16d7de6 = from_latin_1_string("debug_print_head", 16);
  string__9852c4e0e14b8181 = from_latin_1_string("int debug_print_head(int *indent_p, char **buf_p, const char *format, ...);\012", 76);
  string__a0540e55151930c2 = from_latin_1_string("to_int8", 7);
  string__8b67b34a14524350 = from_latin_1_string("uint32_t to_int8(NODE *node);\012", 30);
  string__72a8a8c9865d0296 = from_latin_1_string("to_int16", 8);
  string__7156ce06811a3bb7 = from_latin_1_string("uint64_t to_int16(NODE *node);\012", 31);
  string__72a8a8c9864d0292 = from_latin_1_string("to_int32", 8);
  string__71578e06f11a2bb7 = from_latin_1_string("uint32_t to_int32(NODE *node);\012", 31);
  string__72a8a8c986650294 = from_latin_1_string("to_int64", 8);
  string__7156ce06611a33b7 = from_latin_1_string("uint64_t to_int64(NODE *node);\012", 31);
  string__7ca8ae498474c298 = from_latin_1_string("to_uint8", 8);
  string__714d8e0e161a038f = from_latin_1_string("uint32_t to_uint8(NODE *node);\012", 31);
  string__724c23a6148be573 = from_latin_1_string("to_uint16", 9);
  string__9b761c44b7e5eaec = from_latin_1_string("uint64_t to_uint16(NODE *node);\012", 32);
  string__724c23a6149be577 = from_latin_1_string("to_uint32", 9);
  string__9b779c44f7e5fae6 = from_latin_1_string("uint32_t to_uint32(NODE *node);\012", 32);
  string__724c23a614b3e571 = from_latin_1_string("to_uint64", 9);
  string__9b761c4457e5e2ec = from_latin_1_string("uint64_t to_uint64(NODE *node);\012", 32);
  string__3730b49a2bb3f253 = from_latin_1_string("to_uchar32", 10);
  string__96187ba7d2aab9e = from_latin_1_string("uint32_t to_uchar32(NODE *node);\012", 33);
  string__b6540e1515c13096 = from_latin_1_string("to_bool", 7);
  string__eab0567a680d7e49 = from_latin_1_string("int to_bool(NODE *node);\012", 25);
  string__261f540a81caa2a3 = from_latin_1_string("to_int", 6);
  string__4ed36036cf5d9072 = from_latin_1_string("int to_int(NODE *node);\012", 24);
  string__aa540e1515c9309d = from_latin_1_string("to_long", 7);
  string__eb940de21eba7011 = from_latin_1_string("long to_long(NODE *node);\012", 26);
  string__444c262e96638520 = from_latin_1_string("to_double", 9);
  string__348e2dcbe014e084 = from_latin_1_string("double to_double(NODE *node);\012", 30);
  string__a4214b121078eb22 = from_latin_1_string("to_c_string", 11);
  string__2a2e177196a0d458 = from_latin_1_string("char *to_c_string(NODE *node);\012", 31);
  string__464c27eb16a34536 = from_latin_1_string("to_octets", 9);
  string__21cd69a400bae74a = from_latin_1_string("uint8_t *to_octets(NODE *node, long *size_p);\012", 46);
  string__5af91691bb71fca7 = from_latin_1_string("get_item_of", 11);
  string__f5570b383c3fc00 = from_latin_1_string("NODE *get_item_of(NODE *node, long idx);\012", 41);
  string__7e88296f0e7a3463 = from_latin_1_string("length_of", 9);
  string__310f62774c0e0007 = from_latin_1_string("long length_of(NODE *node);\012", 28);
  string__541f558a01dab2b3 = from_latin_1_string("unfold", 6);
  string__aa90620e046f416c = from_latin_1_string("void unfold(NODE *node);\012", 25);
  string__ee216a04cf7d466f = from_latin_1_string("debug_string", 12);
  string__b1d91f87cca0e731 = from_latin_1_string("long debug_string(NODE *node, int indent, int max_depth, char *buf);\012", 69);
  string__d06e9dd63b47a743 = from_latin_1_string("optional_item", 13);
  string__7a5cedaec36476fb = from_latin_1_string("void optional_item(NODE *item);\012", 32);
  string__c63b2d1935e6c40b = from_latin_1_string("get_attribute", 13);
  string__679ea7d4aa3dc62e = from_latin_1_string("NODE *get_attribute(NODE *node, int idx);\012", 42);
  string__de8d76bddd0e0c7c = from_latin_1_string("polymorph_dispatch", 18);
  string__33b3c02b144305e5 = from_latin_1_string("void polymorph_dispatch(int idx);\012", 34);
  string__c63b2c5935e6c40b = from_latin_1_string("set_attribute", 13);
  string__461472315ebaff5f = from_latin_1_string("void set_attribute(ATTRIBUTES *attributes, int idx, void *attr);\012", 65);
  string__d22f03c332cbb7fe = from_latin_1_string("set_attribute_value", 19);
  string__14bb178f7122cfd7 = from_latin_1_string("void set_attribute_value(ATTRIBUTES *attributes, int idx, void *attr);\012", 71);
  string__2e96a85fa636061f = from_latin_1_string("record__event", 13);
  string__dab898fd6ccb94af = from_latin_1_string("void record__event(const char *name);\012", 38);
  string__704f98350e6d5307 = from_latin_1_string("successful__action", 18);
  string__cb62ccbfd0ebcc01 = from_latin_1_string("void successful__action(const char *name);\012", 43);
  string__aafd8832303424db = from_latin_1_string("failed__action", 14);
  string__d0c86ff26de9d846 = from_latin_1_string("void failed__action(const char *name);\012", 39);
  string__ee96b05fb53605bb = from_latin_1_string("replay__event", 13);
  string__96b8997d6dfb9495 = from_latin_1_string("void replay__event(const char *name);\012", 38);
  string__a0fda8722d0624db = from_latin_1_string("replay__action", 14);
  string__c4688fdba679a3d7 = from_latin_1_string("int replay__action(const char *name);\012", 38);
  string__ee96a85fa636041b = from_latin_1_string("report__event", 13);
  string__96b898fd6ccb948f = from_latin_1_string("void report__event(const char *name);\012", 38);
  string__154106450b6484c7 = from_latin_1_string("print__pointer", 14);
  string__48ac73a2bb0fdab2 = from_latin_1_string("void print__pointer(void *ptr);\012", 32);
  string__14c18e250b6884c0 = from_latin_1_string("store__pointer", 14);
  string__4b2cb3e68b0fdcb2 = from_latin_1_string("void store__pointer(void *ptr);\012", 32);
  string__f85036d3d94a7bb1 = from_latin_1_string("retrieve__pointer", 17);
  string__1e649a8a52a00dac = from_latin_1_string("void retrieve__pointer(void **ptr_p);\012", 38);
  string__32502858b6554c7 = from_latin_1_string("print__integer", 14);
  string__ba7ab002426e2e85 = from_latin_1_string("void print__integer(int val);\012", 30);
  string__2a58ae58b6954c0 = from_latin_1_string("store__integer", 14);
  string__aabab01a42602d84 = from_latin_1_string("void store__integer(int val);\012", 30);
  string__ee343213594babb1 = from_latin_1_string("retrieve__integer", 17);
  string__fc70de4897612997 = from_latin_1_string("void retrieve__integer(int *val_p);\012", 36);
  string__4f8263ad80b7c630 = from_latin_1_string("print__long_integer", 19);
  string__ac28eb4056636d1 = from_latin_1_string("void print__long_integer(long val);\012", 36);
  string__4f8463ae00778200 = from_latin_1_string("store__long_integer", 19);
  string__6c6cdb4050636e9 = from_latin_1_string("void store__long_integer(long val);\012", 36);
  string__26951c16f63f5e7b = from_latin_1_string("retrieve__long_integer", 22);
  string__8aa183bf30fdb669 = from_latin_1_string("void retrieve__long_integer(long *val_p);\012", 42);
  string__f75531ddca48c11b = from_latin_1_string("print__int_array", 16);
  string__1061572abef9f5fc = from_latin_1_string("void print__int_array(const int *buf, long len);\012", 49);
  string__f455301daa6ad91b = from_latin_1_string("store__int_array", 16);
  string__c67550b3ef9c5fc = from_latin_1_string("void store__int_array(const int *buf, long len);\012", 49);
  string__7ceaec668e04e4af = from_latin_1_string("retrieve__int_array", 19);
  string__f527cb3955e59def = from_latin_1_string("long retrieve__int_array(int **buf_p);\012", 39);
  string__9896a2e6a0f80170 = from_latin_1_string("print__memory", 13);
  string__b813d7b89495bd97 = from_latin_1_string("void print__memory(const uint8_t *buf, long len);\012", 50);
  string__189642d6b1f40171 = from_latin_1_string("store__memory", 13);
  string__a91fd7b914955da7 = from_latin_1_string("void store__memory(const uint8_t *buf, long len);\012", 50);
  string__47787f4486eadb35 = from_latin_1_string("retrieve__memory", 16);
  string__71f6bf6cf0c52b77 = from_latin_1_string("long retrieve__memory(uint8_t **buf_p);\012", 40);
  string__3ee8582926d9080f = from_latin_1_string("print__c_string", 15);
  string__b566653efe8d5564 = from_latin_1_string("void print__c_string(const char *buf);\012", 39);
  string__7de8584926e1040b = from_latin_1_string("store__c_string", 15);
  string__c57e6db8fe8d9564 = from_latin_1_string("void store__c_string(const char *buf);\012", 39);
  string__ba5ec95edd6e6086 = from_latin_1_string("retrieve__c_string", 18);
  string__44e19d077543310d = from_latin_1_string("void retrieve__c_string(char **buf_p);\012", 39);
  string__324188e7a6ce34a6 = from_latin_1_string("create_function", 15);
  string__cc612f10fbde1147 = from_latin_1_string("NODE *create_function(FUNC func, int par_count);\012", 49);
  string__e68d0604b1c4e4d3 = from_latin_1_string("create_closure", 14);
  string__4e66b585b29bac7b = from_latin_1_string("NODE *create_closure(FUNC type, int par_count);\012", 48);
  string__527f2a0eb4d2ad39 = from_latin_1_string("continuation_type_function", 26);
  string__36dea3e52fa97601 = from_latin_1_string("void continuation_type_function(void);\012", 39);
  string__db8268c5e3e3998 = from_latin_1_string("continuation_trampoline", 23);
  string__9cbbab858b1d3dd4 = from_latin_1_string("void continuation_trampoline(void);\012", 36);
  string__70926021f73890ec = from_latin_1_string("create_continuation", 19);
  string__6f29cd9643b48e9f = from_latin_1_string("NODE *create_continuation(void);\012", 33);
  string__d7f67e3c0983d96f = from_latin_1_string("create_continuation_with_exit", 29);
  string__312f4f711c0187b4 = from_latin_1_string("NODE *create_continuation_with_exit(FUNC exit_func);\012", 53);
  string__5df6e86d7cfc4b00 = from_latin_1_string("initialize_function_attributes", 30);
  string__83170f4ed8417cf9 = from_latin_1_string("void initialize_function_attributes(void);\012", 43);
  string__aa96dd5320f9062f = from_latin_1_string("create_future", 13);
  string__2524b8f70c096216 = from_latin_1_string("NODE *create_future(void);\012", 27);
  string__b621c02f863d5995 = from_latin_1_string("create_future_with_prototype", 28);
  string__795f344f2e5fec15 = from_latin_1_string("NODE *create_future_with_prototype(NODE *prototype);\012", 53);
  string__4ff756961cfbc8e0 = from_latin_1_string("initialize_future", 17);
  string__8ac552a1731f393c = from_latin_1_string("void initialize_future(NODE *var, NODE *val);\012", 46);
  string__83ece5deb5c6ec9d = from_latin_1_string("maybe_initialize_future", 23);
  string__b7c1a4c735435200 = from_latin_1_string("void maybe_initialize_future(NODE *var, NODE *val);\012", 52);
  string__cb694aae4ed9216f = from_latin_1_string("initialize_maybe_future", 23);
  string__326ed43c2a8ea048 = from_latin_1_string("void initialize_maybe_future(NODE *var, NODE *val);\012", 52);
  string__48e5e352d3af6668 = from_latin_1_string("assign_value", 12);
  string__f906962f4ff7a2cb = from_latin_1_string("void assign_value(NODE **dest, NODE *val);\012", 43);
  string__d891d349a6c69ea9 = from_latin_1_string("assign_variable", 15);
  string__9d199eb4b8234323 = from_latin_1_string("void assign_variable(NODE **dest, NODE **var_p);\012", 49);
  string__463b2d2935e6c40f = from_latin_1_string("def_attribute", 13);
  string__c561b7f4ab9de03e = from_latin_1_string("void def_attribute(NODE **var_p, int idx, void *attr);\012", 55);
  string__468da0192a6a5b6c = from_latin_1_string("create_cell", 11);
  string__ca7b95abeb676984 = from_latin_1_string("NODE *create_cell(void);\012", 25);
  string__d2bf386ef518fd14 = from_latin_1_string("create_cell_with_contents", 25);
  string__9711b14735cfde06 = from_latin_1_string("NODE *create_cell_with_contents(NODE *contents);\012", 49);
  string__7ba0bd51221b7d7f = from_latin_1_string("get_dynamic_slot", 16);
  string__4607d5e4ffb66756 = from_latin_1_string("NODE *get_dynamic_slot(int id);\012", 32);
  string__5ba0bf1122037d67 = from_latin_1_string("get_dynamic_cell", 16);
  string__4e07d574ffb06750 = from_latin_1_string("NODE *get_dynamic_cell(int id);\012", 32);
  string__5ba0bf13a2037d67 = from_latin_1_string("set_dynamic_cell", 16);
  string__e46df6740b141708 = from_latin_1_string("void set_dynamic_cell(int id, NODE *node);\012", 43);
  string__fe8d616be3f518cb = from_latin_1_string("define_dynamic_slot", 19);
  string__f248fe4622d2f5cc = from_latin_1_string("void define_dynamic_slot(int id, NODE *node);\012", 46);
  string__de8d632be3ed18d3 = from_latin_1_string("define_dynamic_cell", 19);
  string__f228fe26a2d2fccc = from_latin_1_string("void define_dynamic_cell(int id, NODE *node);\012", 46);
  string__72f826ea16a3e460 = from_latin_1_string("terminate", 9);
  string__43fa56dbd271ef60 = from_latin_1_string("void terminate(int exit_code);\012", 31);
  string__b410089e951a909f = from_latin_1_string("execute", 7);
  string__5637a81453ba364 = from_latin_1_string("__attribute__ ((noreturn)) void execute(FUNC entry);\012", 53);
  string__d0118bd6a6b2ec04 = from_latin_1_string("invoke_callback", 15);
  string__736892f443d8da54 = from_latin_1_string("void invoke_callback(NODE *callback);\012", 38);
  string__e9d1ecf31d50102f = from_latin_1_string("COMPARE_FUNCTION", 16);
  string__29bf848cc7ceebf2 = from_latin_1_string("typedef int (*COMPARE_FUNCTION)(const void *, const void *);\012", 61);
  string__18e7723792748147 = from_latin_1_string("DEBUG_COMMAND", 13);
  string__b1b21feb47ad3535 = from_latin_1_string(
    "typedef enum {\n"
    "  SHOW_PROMPT,\n"
    "  LOG_LAST_INSTRUCTION,\n"
    "  GOTO_INSTRUCTION\n"
    "} DEBUG_COMMAND;\n",
    90);
  string__84879098faa5d2d = from_latin_1_string("SHARED_DATA", 11);
  string__45b0ac293d6efdfa = from_latin_1_string(
    "typedef struct {\n"
    "  DEBUG_COMMAND command;\n"
    "  uint64_t instruction_counter;\n"
    "  int depth;\n"
    "} SHARED_DATA;\n",
    102);
  string__8edd0c0616b76781 = from_latin_1_string("retrieve_continuation_info", 26);
  string__5745a2890b84b4b9 = from_latin_1_string(
    "int retrieve_continuation_info(\n"
    "  FUNC func, const char **filename_p, CONTINUATION_INFO **info_p\n"
    ");\n",
    100);
  string__3d280d5fb44085d1 = from_latin_1_string("crash_dump", 10);
  string__ed53ddd7ccc24cb5 = from_latin_1_string("void crash_dump(void);\012", 23);
}

static int already_run_phase_3 = false;

EXPORT void phase_3__runtime_definitions(void) {
  if (already_run_phase_3) return;
  already_run_phase_3 = true;
  set_module("runtime_definitions");
  set_used_namespaces(used_namespaces);
  define_single_assign_static("sim2c", "runtime_symbols", get__sim2c__runtime_symbols, &var.sim2c__runtime_symbols);
}

static int already_run_phase_4 = false;

EXPORT void phase_4__runtime_definitions(void) {
  if (already_run_phase_4) return;
  already_run_phase_4 = true;
  set_module("runtime_definitions");
  set_used_namespaces(used_namespaces);
  use_read_only("std", "key_value_pair", &get__std__key_value_pair, &get_value_or_future__std__key_value_pair);
  use_read_only(NULL, "table", &get__table, &get_value_or_future__table);
}

static int already_run_phase_5 = false;

EXPORT void phase_5__runtime_definitions(void) {
  if (already_run_phase_5) return;
  already_run_phase_5 = true;
}

static int already_run_phase_6 = false;

EXPORT void phase_6__runtime_definitions(void) {
  if (already_run_phase_6) return;
  already_run_phase_6 = true;
  register_collector(collect__runtime_definitions);
}
