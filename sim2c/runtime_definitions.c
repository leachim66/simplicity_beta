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
IMPORT void register_phase_2_collector(void *data);
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
static NODE *temp__1;
static NODE *temp__2;
static NODE *temp__3;
static NODE *temp__4;
static NODE *temp__5;
static NODE *temp__6;
static NODE *temp__7;
static NODE *temp__8;
static NODE *temp__9;
static NODE *temp__10;
static NODE *temp__11;
static NODE *temp__12;
static NODE *temp__13;
static NODE *temp__14;
static NODE *temp__15;
static NODE *temp__16;
static NODE *temp__17;
static NODE *temp__18;
static NODE *temp__19;
static NODE *temp__20;
static NODE *temp__21;
static NODE *temp__22;
static NODE *temp__23;
static NODE *temp__24;
static NODE *temp__25;
static NODE *temp__26;
static NODE *temp__27;
static NODE *temp__28;
static NODE *temp__29;
static NODE *temp__30;
static NODE *temp__31;
static NODE *temp__32;
static NODE *temp__33;
static NODE *temp__34;
static NODE *temp__35;
static NODE *temp__36;
static NODE *temp__37;
static NODE *temp__38;
static NODE *temp__39;
static NODE *temp__40;
static NODE *temp__41;
static NODE *temp__42;
static NODE *temp__43;
static NODE *temp__44;
static NODE *temp__45;
static NODE *temp__46;
static NODE *temp__47;
static NODE *temp__48;
static NODE *temp__49;
static NODE *temp__50;
static NODE *temp__51;
static NODE *temp__52;
static NODE *temp__53;
static NODE *temp__54;
static NODE *temp__55;
static NODE *temp__56;
static NODE *temp__57;
static NODE *temp__58;
static NODE *temp__59;
static NODE *temp__60;
static NODE *temp__61;
static NODE *temp__62;
static NODE *temp__63;
static NODE *temp__64;
static NODE *temp__65;
static NODE *temp__66;
static NODE *temp__67;
static NODE *temp__68;
static NODE *temp__69;
static NODE *temp__70;
static NODE *temp__71;
static NODE *temp__72;
static NODE *temp__73;
static NODE *temp__74;
static NODE *temp__75;
static NODE *temp__76;
static NODE *temp__77;
static NODE *temp__78;
static NODE *temp__79;
static NODE *temp__80;
static NODE *temp__81;
static NODE *temp__82;
static NODE *temp__83;
static NODE *temp__84;
static NODE *temp__85;
static NODE *temp__86;
static NODE *temp__87;
static NODE *temp__88;
static NODE *temp__89;
static NODE *temp__90;
static NODE *temp__91;
static NODE *temp__92;
static NODE *temp__93;
static NODE *temp__94;
static NODE *temp__95;
static NODE *temp__96;
static NODE *temp__97;
static NODE *temp__98;
static NODE *temp__99;
static NODE *temp__100;
static NODE *temp__101;
static NODE *temp__102;
static NODE *temp__103;
static NODE *temp__104;
static NODE *temp__105;
static NODE *temp__106;
static NODE *temp__107;
static NODE *temp__108;
static NODE *temp__109;
static NODE *temp__110;
static NODE *temp__111;
static NODE *temp__112;
static NODE *temp__113;
static NODE *temp__114;
static NODE *temp__115;
static NODE *temp__116;
static NODE *temp__117;
static NODE *temp__118;
static NODE *temp__119;
static NODE *temp__120;
static NODE *temp__121;
static NODE *temp__122;
static NODE *temp__123;
static NODE *temp__124;
static NODE *temp__125;
static NODE *temp__126;
static NODE *temp__127;
static NODE *temp__128;
static NODE *temp__129;
static NODE *temp__130;
static NODE *temp__131;
static NODE *temp__132;
static NODE *temp__133;
static NODE *temp__134;
static NODE *temp__135;
static NODE *temp__136;
static NODE *temp__137;
static NODE *temp__138;
static NODE *temp__139;
static NODE *temp__140;
static NODE *temp__141;
static NODE *temp__142;
static NODE *temp__143;
static NODE *temp__144;
static NODE *temp__145;
static NODE *temp__146;
static NODE *temp__147;
static NODE *temp__148;
static NODE *temp__149;
static NODE *temp__150;
static NODE *temp__151;
static NODE *temp__152;
static NODE *temp__153;
static NODE *temp__154;
static NODE *temp__155;
static NODE *temp__156;
static NODE *temp__157;
static NODE *temp__158;
static NODE *temp__159;
static NODE *temp__160;
static NODE *temp__161;
static NODE *temp__162;
static NODE *temp__163;
static NODE *temp__164;
static NODE *temp__165;
static NODE *temp__166;
static NODE *temp__167;
static NODE *temp__168;
static NODE *temp__169;
static NODE *temp__170;
static NODE *temp__171;
static NODE *temp__172;
static NODE *temp__173;
static NODE *temp__174;
static NODE *temp__175;
static NODE *temp__176;
static NODE *temp__177;
static NODE *temp__178;
static NODE *temp__179;
static NODE *temp__180;
static NODE *temp__181;
static NODE *temp__182;
static NODE *temp__183;
static NODE *temp__184;
static NODE *temp__185;
static NODE *temp__186;
static NODE *temp__187;
static NODE *temp__188;
static NODE *temp__189;
static NODE *temp__190;
static NODE *temp__191;
static NODE *temp__192;
static NODE *temp__193;
static NODE *temp__194;
static NODE *temp__195;
static NODE *temp__196;
static NODE *temp__197;
static NODE *temp__198;
static NODE *temp__199;
static NODE *temp__200;
static NODE *temp__201;
static NODE *temp__202;
static NODE *temp__203;
static NODE *temp__204;
static NODE *temp__205;
static NODE *temp__206;
static NODE *temp__207;
static NODE *temp__208;
static NODE *temp__209;
static NODE *temp__210;
static NODE *temp__211;
static NODE *temp__212;
static NODE *temp__213;
static NODE *temp__214;
static NODE *temp__215;
static NODE *temp__216;
static NODE *temp__217;
static NODE *temp__218;
static NODE *temp__219;
static NODE *temp__220;
static NODE *temp__221;
static NODE *temp__222;
static NODE *temp__223;
static NODE *temp__224;
static NODE *temp__225;
static NODE *temp__226;
static NODE *temp__227;
static NODE *temp__228;
static NODE *temp__229;
static NODE *temp__230;
static NODE *temp__231;
static NODE *temp__232;
static NODE *temp__233;
static NODE *temp__234;
static NODE *temp__235;
static NODE *temp__236;
static NODE *temp__237;
static NODE *temp__238;
static NODE *temp__239;
static NODE *temp__240;
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
static NODE *string__2_1;
static NODE *string__2_2;
static void cont__2_3(void);
static NODE *string__2_4;
static NODE *string__2_5;
static void cont__2_6(void);
static NODE *string__2_7;
static NODE *string__2_8;
static void cont__2_9(void);
static NODE *string__2_10;
static NODE *string__2_11;
static void cont__2_12(void);
static NODE *string__2_13;
static NODE *string__2_14;
static void cont__2_15(void);
static NODE *string__2_16;
static NODE *string__2_17;
static void cont__2_18(void);
static NODE *string__2_19;
static NODE *string__2_20;
static void cont__2_21(void);
static NODE *string__2_22;
static NODE *string__2_23;
static void cont__2_24(void);
static NODE *string__2_25;
static NODE *string__2_26;
static void cont__2_27(void);
static NODE *string__2_28;
static NODE *string__2_29;
static void cont__2_30(void);
static NODE *string__2_31;
static NODE *string__2_32;
static void cont__2_33(void);
static NODE *string__2_34;
static NODE *string__2_35;
static void cont__2_36(void);
static NODE *string__2_37;
static NODE *string__2_38;
static void cont__2_39(void);
static NODE *string__2_40;
static NODE *string__2_41;
static void cont__2_42(void);
static NODE *string__2_43;
static NODE *string__2_44;
static void cont__2_45(void);
static NODE *string__2_46;
static NODE *string__2_47;
static void cont__2_48(void);
static NODE *string__2_49;
static NODE *string__2_50;
static void cont__2_51(void);
static NODE *string__2_52;
static NODE *string__2_53;
static void cont__2_54(void);
static NODE *string__2_55;
static NODE *string__2_56;
static void cont__2_57(void);
static NODE *string__2_58;
static NODE *string__2_59;
static void cont__2_60(void);
static NODE *string__2_61;
static NODE *string__2_62;
static void cont__2_63(void);
static NODE *string__2_64;
static NODE *string__2_65;
static void cont__2_66(void);
static NODE *string__2_67;
static NODE *string__2_68;
static void cont__2_69(void);
static NODE *string__2_70;
static NODE *string__2_71;
static void cont__2_72(void);
static NODE *string__2_73;
static NODE *string__2_74;
static void cont__2_75(void);
static NODE *string__2_76;
static NODE *string__2_77;
static void cont__2_78(void);
static NODE *string__2_79;
static NODE *string__2_80;
static void cont__2_81(void);
static NODE *string__2_82;
static NODE *string__2_83;
static void cont__2_84(void);
static NODE *string__2_85;
static NODE *string__2_86;
static void cont__2_87(void);
static NODE *string__2_88;
static NODE *string__2_89;
static void cont__2_90(void);
static NODE *string__2_91;
static NODE *string__2_92;
static void cont__2_93(void);
static NODE *string__2_94;
static NODE *string__2_95;
static void cont__2_96(void);
static NODE *string__2_97;
static NODE *string__2_98;
static void cont__2_99(void);
static NODE *string__2_100;
static NODE *string__2_101;
static void cont__2_102(void);
static NODE *string__2_103;
static NODE *string__2_104;
static void cont__2_105(void);
static NODE *string__2_106;
static NODE *string__2_107;
static void cont__2_108(void);
static NODE *string__2_109;
static NODE *string__2_110;
static void cont__2_111(void);
static NODE *string__2_112;
static NODE *string__2_113;
static void cont__2_114(void);
static NODE *string__2_115;
static NODE *string__2_116;
static void cont__2_117(void);
static NODE *string__2_118;
static NODE *string__2_119;
static void cont__2_120(void);
static NODE *string__2_121;
static NODE *string__2_122;
static void cont__2_123(void);
static NODE *string__2_124;
static NODE *string__2_125;
static void cont__2_126(void);
static NODE *string__2_127;
static NODE *string__2_128;
static void cont__2_129(void);
static NODE *string__2_130;
static NODE *string__2_131;
static void cont__2_132(void);
static NODE *string__2_133;
static NODE *string__2_134;
static void cont__2_135(void);
static NODE *string__2_136;
static NODE *string__2_137;
static void cont__2_138(void);
static NODE *string__2_139;
static NODE *string__2_140;
static void cont__2_141(void);
static NODE *string__2_142;
static NODE *string__2_143;
static void cont__2_144(void);
static NODE *string__2_145;
static NODE *string__2_146;
static void cont__2_147(void);
static NODE *string__2_148;
static NODE *string__2_149;
static void cont__2_150(void);
static NODE *string__2_151;
static NODE *string__2_152;
static void cont__2_153(void);
static NODE *string__2_154;
static NODE *string__2_155;
static void cont__2_156(void);
static NODE *string__2_157;
static NODE *string__2_158;
static void cont__2_159(void);
static NODE *string__2_160;
static NODE *string__2_161;
static void cont__2_162(void);
static NODE *string__2_163;
static NODE *string__2_164;
static void cont__2_165(void);
static NODE *string__2_166;
static NODE *string__2_167;
static void cont__2_168(void);
static NODE *string__2_169;
static NODE *string__2_170;
static void cont__2_171(void);
static NODE *string__2_172;
static NODE *string__2_173;
static void cont__2_174(void);
static NODE *string__2_175;
static NODE *string__2_176;
static void cont__2_177(void);
static NODE *string__2_178;
static NODE *string__2_179;
static void cont__2_180(void);
static NODE *string__2_181;
static NODE *string__2_182;
static void cont__2_183(void);
static NODE *string__2_184;
static NODE *string__2_185;
static void cont__2_186(void);
static NODE *string__2_187;
static NODE *string__2_188;
static void cont__2_189(void);
static NODE *string__2_190;
static NODE *string__2_191;
static void cont__2_192(void);
static NODE *string__2_193;
static NODE *string__2_194;
static void cont__2_195(void);
static NODE *string__2_196;
static NODE *string__2_197;
static void cont__2_198(void);
static NODE *string__2_199;
static NODE *string__2_200;
static void cont__2_201(void);
static NODE *string__2_202;
static NODE *string__2_203;
static void cont__2_204(void);
static NODE *string__2_205;
static NODE *string__2_206;
static void cont__2_207(void);
static NODE *string__2_208;
static NODE *string__2_209;
static void cont__2_210(void);
static NODE *string__2_211;
static NODE *string__2_212;
static void cont__2_213(void);
static NODE *string__2_214;
static NODE *string__2_215;
static void cont__2_216(void);
static NODE *string__2_217;
static NODE *string__2_218;
static void cont__2_219(void);
static NODE *string__2_220;
static NODE *string__2_221;
static void cont__2_222(void);
static NODE *string__2_223;
static NODE *string__2_224;
static void cont__2_225(void);
static NODE *string__2_226;
static NODE *string__2_227;
static void cont__2_228(void);
static NODE *string__2_229;
static NODE *string__2_230;
static void cont__2_231(void);
static NODE *string__2_232;
static NODE *string__2_233;
static void cont__2_234(void);
static NODE *string__2_235;
static NODE *string__2_236;
static void cont__2_237(void);
static NODE *string__2_238;
static NODE *string__2_239;
static void cont__2_240(void);
static NODE *string__2_241;
static NODE *string__2_242;
static void cont__2_243(void);
static NODE *string__2_244;
static NODE *string__2_245;
static void cont__2_246(void);
static NODE *string__2_247;
static NODE *string__2_248;
static void cont__2_249(void);
static NODE *string__2_250;
static NODE *string__2_251;
static void cont__2_252(void);
static NODE *string__2_253;
static NODE *string__2_254;
static void cont__2_255(void);
static NODE *string__2_256;
static NODE *string__2_257;
static void cont__2_258(void);
static NODE *string__2_259;
static NODE *string__2_260;
static void cont__2_261(void);
static NODE *string__2_262;
static NODE *string__2_263;
static void cont__2_264(void);
static NODE *string__2_265;
static NODE *string__2_266;
static void cont__2_267(void);
static NODE *string__2_268;
static NODE *string__2_269;
static void cont__2_270(void);
static NODE *string__2_271;
static NODE *string__2_272;
static void cont__2_273(void);
static NODE *string__2_274;
static NODE *string__2_275;
static void cont__2_276(void);
static NODE *string__2_277;
static NODE *string__2_278;
static void cont__2_279(void);
static NODE *string__2_280;
static NODE *string__2_281;
static void cont__2_282(void);
static NODE *string__2_283;
static NODE *string__2_284;
static void cont__2_285(void);
static NODE *string__2_286;
static NODE *string__2_287;
static void cont__2_288(void);
static NODE *string__2_289;
static NODE *string__2_290;
static void cont__2_291(void);
static NODE *string__2_292;
static NODE *string__2_293;
static void cont__2_294(void);
static NODE *string__2_295;
static NODE *string__2_296;
static void cont__2_297(void);
static NODE *string__2_298;
static NODE *string__2_299;
static void cont__2_300(void);
static NODE *string__2_301;
static NODE *string__2_302;
static void cont__2_303(void);
static NODE *string__2_304;
static NODE *string__2_305;
static void cont__2_306(void);
static NODE *string__2_307;
static NODE *string__2_308;
static void cont__2_309(void);
static NODE *string__2_310;
static NODE *string__2_311;
static void cont__2_312(void);
static NODE *string__2_313;
static NODE *string__2_314;
static void cont__2_315(void);
static NODE *string__2_316;
static NODE *string__2_317;
static void cont__2_318(void);
static NODE *string__2_319;
static NODE *string__2_320;
static void cont__2_321(void);
static NODE *string__2_322;
static NODE *string__2_323;
static void cont__2_324(void);
static NODE *string__2_325;
static NODE *string__2_326;
static void cont__2_327(void);
static NODE *string__2_328;
static NODE *string__2_329;
static void cont__2_330(void);
static NODE *string__2_331;
static NODE *string__2_332;
static void cont__2_333(void);
static NODE *string__2_334;
static NODE *string__2_335;
static void cont__2_336(void);
static NODE *string__2_337;
static NODE *string__2_338;
static void cont__2_339(void);
static NODE *string__2_340;
static NODE *string__2_341;
static void cont__2_342(void);
static NODE *string__2_343;
static NODE *string__2_344;
static void cont__2_345(void);
static NODE *string__2_346;
static NODE *string__2_347;
static void cont__2_348(void);
static NODE *string__2_349;
static NODE *string__2_350;
static void cont__2_351(void);
static NODE *string__2_352;
static NODE *string__2_353;
static void cont__2_354(void);
static NODE *string__2_355;
static NODE *string__2_356;
static void cont__2_357(void);
static NODE *string__2_358;
static NODE *string__2_359;
static void cont__2_360(void);
static NODE *string__2_361;
static NODE *string__2_362;
static void cont__2_363(void);
static NODE *string__2_364;
static NODE *string__2_365;
static void cont__2_366(void);
static NODE *string__2_367;
static NODE *string__2_368;
static void cont__2_369(void);
static NODE *string__2_370;
static NODE *string__2_371;
static void cont__2_372(void);
static NODE *string__2_373;
static NODE *string__2_374;
static void cont__2_375(void);
static NODE *string__2_376;
static NODE *string__2_377;
static void cont__2_378(void);
static NODE *string__2_379;
static NODE *string__2_380;
static void cont__2_381(void);
static NODE *string__2_382;
static NODE *string__2_383;
static void cont__2_384(void);
static NODE *string__2_385;
static NODE *string__2_386;
static void cont__2_387(void);
static NODE *string__2_388;
static NODE *string__2_389;
static void cont__2_390(void);
static NODE *string__2_391;
static NODE *string__2_392;
static void cont__2_393(void);
static NODE *string__2_394;
static NODE *string__2_395;
static void cont__2_396(void);
static NODE *string__2_397;
static NODE *string__2_398;
static void cont__2_399(void);
static NODE *string__2_400;
static NODE *string__2_401;
static void cont__2_402(void);
static NODE *string__2_403;
static NODE *string__2_404;
static void cont__2_405(void);
static NODE *string__2_406;
static NODE *string__2_407;
static void cont__2_408(void);
static NODE *string__2_409;
static NODE *string__2_410;
static void cont__2_411(void);
static NODE *string__2_412;
static NODE *string__2_413;
static void cont__2_414(void);
static NODE *string__2_415;
static NODE *string__2_416;
static void cont__2_417(void);
static NODE *string__2_418;
static NODE *string__2_419;
static void cont__2_420(void);
static NODE *string__2_421;
static NODE *string__2_422;
static void cont__2_423(void);
static NODE *string__2_424;
static NODE *string__2_425;
static void cont__2_426(void);
static NODE *string__2_427;
static NODE *string__2_428;
static void cont__2_429(void);
static NODE *string__2_430;
static NODE *string__2_431;
static void cont__2_432(void);
static NODE *string__2_433;
static NODE *string__2_434;
static void cont__2_435(void);
static NODE *string__2_436;
static NODE *string__2_437;
static void cont__2_438(void);
static NODE *string__2_439;
static NODE *string__2_440;
static void cont__2_441(void);
static NODE *string__2_442;
static NODE *string__2_443;
static void cont__2_444(void);
static NODE *string__2_445;
static NODE *string__2_446;
static void cont__2_447(void);
static NODE *string__2_448;
static NODE *string__2_449;
static void cont__2_450(void);
static NODE *string__2_451;
static NODE *string__2_452;
static void cont__2_453(void);
static NODE *string__2_454;
static NODE *string__2_455;
static void cont__2_456(void);
static NODE *string__2_457;
static NODE *string__2_458;
static void cont__2_459(void);
static NODE *string__2_460;
static NODE *string__2_461;
static void cont__2_462(void);
static NODE *string__2_463;
static NODE *string__2_464;
static void cont__2_465(void);
static NODE *string__2_466;
static NODE *string__2_467;
static void cont__2_468(void);
static NODE *string__2_469;
static NODE *string__2_470;
static void cont__2_471(void);
static NODE *string__2_472;
static NODE *string__2_473;
static void cont__2_474(void);
static NODE *string__2_475;
static NODE *string__2_476;
static void cont__2_477(void);
static NODE *string__2_478;
static NODE *string__2_479;
static void cont__2_480(void);
static NODE *string__2_481;
static NODE *string__2_482;
static void cont__2_483(void);
static NODE *string__2_484;
static NODE *string__2_485;
static void cont__2_486(void);
static NODE *string__2_487;
static NODE *string__2_488;
static void cont__2_489(void);
static NODE *string__2_490;
static NODE *string__2_491;
static void cont__2_492(void);
static NODE *string__2_493;
static NODE *string__2_494;
static void cont__2_495(void);
static NODE *string__2_496;
static NODE *string__2_497;
static void cont__2_498(void);
static NODE *string__2_499;
static NODE *string__2_500;
static void cont__2_501(void);
static NODE *string__2_502;
static NODE *string__2_503;
static void cont__2_504(void);
static NODE *string__2_505;
static NODE *string__2_506;
static void cont__2_507(void);
static NODE *string__2_508;
static NODE *string__2_509;
static void cont__2_510(void);
static NODE *string__2_511;
static NODE *string__2_512;
static void cont__2_513(void);
static NODE *string__2_514;
static NODE *string__2_515;
static void cont__2_516(void);
static NODE *string__2_517;
static NODE *string__2_518;
static void cont__2_519(void);
static NODE *string__2_520;
static NODE *string__2_521;
static void cont__2_522(void);
static NODE *string__2_523;
static NODE *string__2_524;
static void cont__2_525(void);
static NODE *string__2_526;
static NODE *string__2_527;
static void cont__2_528(void);
static NODE *string__2_529;
static NODE *string__2_530;
static void cont__2_531(void);
static NODE *string__2_532;
static NODE *string__2_533;
static void cont__2_534(void);
static NODE *string__2_535;
static NODE *string__2_536;
static void cont__2_537(void);
static NODE *string__2_538;
static NODE *string__2_539;
static void cont__2_540(void);
static NODE *string__2_541;
static NODE *string__2_542;
static void cont__2_543(void);
static NODE *string__2_544;
static NODE *string__2_545;
static void cont__2_546(void);
static NODE *string__2_547;
static NODE *string__2_548;
static void cont__2_549(void);
static NODE *string__2_550;
static NODE *string__2_551;
static void cont__2_552(void);
static NODE *string__2_553;
static NODE *string__2_554;
static void cont__2_555(void);
static NODE *string__2_556;
static NODE *string__2_557;
static void cont__2_558(void);
static NODE *string__2_559;
static NODE *string__2_560;
static void cont__2_561(void);
static NODE *string__2_562;
static NODE *string__2_563;
static void cont__2_564(void);
static NODE *string__2_565;
static NODE *string__2_566;
static void cont__2_567(void);
static NODE *string__2_568;
static NODE *string__2_569;
static void cont__2_570(void);
static NODE *string__2_571;
static NODE *string__2_572;
static void cont__2_573(void);
static NODE *string__2_574;
static NODE *string__2_575;
static void cont__2_576(void);
static NODE *string__2_577;
static NODE *string__2_578;
static void cont__2_579(void);
static NODE *string__2_580;
static NODE *string__2_581;
static void cont__2_582(void);
static NODE *string__2_583;
static NODE *string__2_584;
static void cont__2_585(void);
static NODE *string__2_586;
static NODE *string__2_587;
static void cont__2_588(void);
static NODE *string__2_589;
static NODE *string__2_590;
static void cont__2_591(void);
static NODE *string__2_592;
static NODE *string__2_593;
static void cont__2_594(void);
static NODE *string__2_595;
static NODE *string__2_596;
static void cont__2_597(void);
static NODE *string__2_598;
static NODE *string__2_599;
static void cont__2_600(void);
static NODE *string__2_601;
static NODE *string__2_602;
static void cont__2_603(void);
static NODE *string__2_604;
static NODE *string__2_605;
static void cont__2_606(void);
static NODE *string__2_607;
static NODE *string__2_608;
static void cont__2_609(void);
static NODE *string__2_610;
static NODE *string__2_611;
static void cont__2_612(void);
static NODE *string__2_613;
static NODE *string__2_614;
static void cont__2_615(void);
static NODE *string__2_616;
static NODE *string__2_617;
static void cont__2_618(void);
static NODE *string__2_619;
static NODE *string__2_620;
static void cont__2_621(void);
static NODE *string__2_622;
static NODE *string__2_623;
static void cont__2_624(void);
static NODE *string__2_625;
static NODE *string__2_626;
static void cont__2_627(void);
static NODE *string__2_628;
static NODE *string__2_629;
static void cont__2_630(void);
static NODE *string__2_631;
static NODE *string__2_632;
static void cont__2_633(void);
static NODE *string__2_634;
static NODE *string__2_635;
static void cont__2_636(void);
static NODE *string__2_637;
static NODE *string__2_638;
static void cont__2_639(void);
static NODE *string__2_640;
static NODE *string__2_641;
static void cont__2_642(void);
static NODE *string__2_643;
static NODE *string__2_644;
static void cont__2_645(void);
static NODE *string__2_646;
static NODE *string__2_647;
static void cont__2_648(void);
static NODE *string__2_649;
static NODE *string__2_650;
static void cont__2_651(void);
static NODE *string__2_652;
static NODE *string__2_653;
static void cont__2_654(void);
static NODE *string__2_655;
static NODE *string__2_656;
static void cont__2_657(void);
static NODE *string__2_658;
static NODE *string__2_659;
static void cont__2_660(void);
static NODE *string__2_661;
static NODE *string__2_662;
static void cont__2_663(void);
static NODE *string__2_664;
static NODE *string__2_665;
static void cont__2_666(void);
static NODE *string__2_667;
static NODE *string__2_668;
static void cont__2_669(void);
static NODE *string__2_670;
static NODE *string__2_671;
static void cont__2_672(void);
static NODE *string__2_673;
static NODE *string__2_674;
static void cont__2_675(void);
static NODE *string__2_676;
static NODE *string__2_677;
static void cont__2_678(void);
static NODE *string__2_679;
static NODE *string__2_680;
static void cont__2_681(void);
static NODE *string__2_682;
static NODE *string__2_683;
static void cont__2_684(void);
static NODE *string__2_685;
static NODE *string__2_686;
static void cont__2_687(void);
static NODE *string__2_688;
static NODE *string__2_689;
static void cont__2_690(void);
static NODE *string__2_691;
static NODE *string__2_692;
static void cont__2_693(void);
static NODE *string__2_694;
static NODE *string__2_695;
static void cont__2_696(void);
static NODE *string__2_697;
static NODE *string__2_698;
static void cont__2_699(void);
static NODE *string__2_700;
static NODE *string__2_701;
static void cont__2_702(void);
static NODE *string__2_703;
static NODE *string__2_704;
static void cont__2_705(void);
static NODE *string__2_706;
static NODE *string__2_707;
static void cont__2_708(void);
static NODE *string__2_709;
static NODE *string__2_710;
static void cont__2_711(void);
static NODE *string__2_712;
static NODE *string__2_713;
static void cont__2_714(void);
static NODE *string__2_715;
static NODE *string__2_716;
static void cont__2_717(void);
static NODE *string__2_718;
static NODE *string__2_719;
static void cont__2_720(void);
static void cont__2_721(void);
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
  {cont__2_45, NULL, 72, 73, 5, 56},
  {cont__2_48, NULL, 74, 75, 5, 31},
  {cont__2_51, NULL, 76, 77, 5, 30},
  {cont__2_54, NULL, 78, 79, 5, 32},
  {cont__2_57, NULL, 80, 81, 5, 36},
  {cont__2_60, NULL, 82, 83, 5, 38},
  {cont__2_63, NULL, 84, 85, 5, 38},
  {cont__2_66, NULL, 86, 87, 5, 36},
  {cont__2_69, NULL, 88, 89, 5, 47},
  {cont__2_72, NULL, 90, 91, 5, 43},
  {cont__2_75, NULL, 92, 93, 5, 43},
  {cont__2_78, NULL, 94, 95, 5, 59},
  {cont__2_81, NULL, 96, 97, 5, 62},
  {cont__2_84, NULL, 98, 99, 5, 53},
  {cont__2_87, NULL, 100, 101, 5, 51},
  {cont__2_90, NULL, 102, 103, 5, 59},
  {cont__2_93, NULL, 104, 105, 5, 70},
  {cont__2_96, NULL, 106, 107, 5, 82},
  {cont__2_99, NULL, 108, 112, 5, 8},
  {cont__2_102, NULL, 113, 117, 5, 8},
  {cont__2_105, NULL, 118, 122, 5, 8},
  {cont__2_108, NULL, 123, 127, 5, 8},
  {cont__2_111, NULL, 128, 132, 5, 8},
  {cont__2_114, NULL, 133, 134, 5, 39},
  {cont__2_117, NULL, 135, 140, 5, 8},
  {cont__2_120, NULL, 141, 146, 5, 8},
  {cont__2_123, NULL, 147, 150, 5, 8},
  {cont__2_126, NULL, 151, 155, 5, 8},
  {cont__2_129, NULL, 156, 160, 5, 8},
  {cont__2_132, NULL, 161, 164, 5, 8},
  {cont__2_135, NULL, 165, 169, 5, 8},
  {cont__2_138, NULL, 170, 174, 5, 8},
  {cont__2_141, NULL, 175, 179, 5, 8},
  {cont__2_144, NULL, 180, 184, 5, 8},
  {cont__2_147, NULL, 185, 186, 5, 33},
  {cont__2_150, NULL, 187, 188, 5, 36},
  {cont__2_153, NULL, 189, 190, 5, 30},
  {cont__2_156, NULL, 191, 192, 5, 33},
  {cont__2_159, NULL, 193, 194, 5, 41},
  {cont__2_162, NULL, 195, 196, 5, 42},
  {cont__2_165, NULL, 197, 198, 5, 38},
  {cont__2_168, NULL, 199, 200, 5, 41},
  {cont__2_171, NULL, 201, 224, 5, 15},
  {cont__2_174, NULL, 225, 228, 5, 15},
  {cont__2_177, NULL, 229, 233, 5, 19},
  {cont__2_180, NULL, 234, 237, 5, 17},
  {cont__2_183, NULL, 238, 242, 5, 20},
  {cont__2_186, NULL, 243, 249, 5, 16},
  {cont__2_189, NULL, 250, 255, 5, 17},
  {cont__2_192, NULL, 256, 264, 5, 21},
  {cont__2_195, NULL, 265, 270, 5, 23},
  {cont__2_198, NULL, 271, 281, 5, 15},
  {cont__2_201, NULL, 282, 287, 5, 13},
  {cont__2_204, NULL, 288, 295, 5, 14},
  {cont__2_207, NULL, 296, 300, 5, 19},
  {cont__2_210, NULL, 301, 311, 5, 26},
  {cont__2_213, NULL, 312, 323, 5, 20},
  {cont__2_216, NULL, 324, 329, 5, 20},
  {cont__2_219, NULL, 330, 335, 5, 21},
  {cont__2_222, NULL, 336, 341, 5, 26},
  {cont__2_225, NULL, 342, 343, 5, 45},
  {cont__2_228, NULL, 344, 345, 5, 43},
  {cont__2_231, NULL, 346, 347, 5, 39},
  {cont__2_234, NULL, 348, 349, 5, 36},
  {cont__2_237, NULL, 350, 351, 5, 39},
  {cont__2_240, NULL, 352, 353, 5, 23},
  {cont__2_243, NULL, 354, 355, 5, 25},
  {cont__2_246, NULL, 356, 357, 5, 20},
  {cont__2_249, NULL, 358, 359, 5, 23},
  {cont__2_252, NULL, 360, 361, 5, 30},
  {cont__2_255, NULL, 362, 363, 5, 19},
  {cont__2_258, NULL, 364, 365, 5, 27},
  {cont__2_261, NULL, 366, 367, 5, 26},
  {cont__2_264, NULL, 368, 369, 5, 30},
  {cont__2_267, NULL, 370, 371, 5, 22},
  {cont__2_270, NULL, 372, 373, 5, 17},
  {cont__2_273, NULL, 374, 375, 5, 25},
  {cont__2_276, NULL, 376, 377, 5, 26},
  {cont__2_279, NULL, 378, 379, 5, 25},
  {cont__2_282, NULL, 380, 381, 5, 41},
  {cont__2_285, NULL, 382, 383, 5, 35},
  {cont__2_288, NULL, 384, 385, 5, 35},
  {cont__2_291, NULL, 386, 387, 5, 35},
  {cont__2_294, NULL, 388, 389, 5, 35},
  {cont__2_297, NULL, 390, 391, 5, 35},
  {cont__2_300, NULL, 392, 393, 5, 35},
  {cont__2_303, NULL, 394, 395, 5, 35},
  {cont__2_306, NULL, 396, 397, 5, 35},
  {cont__2_309, NULL, 398, 399, 5, 35},
  {cont__2_312, NULL, 400, 401, 5, 42},
  {cont__2_315, NULL, 402, 403, 5, 42},
  {cont__2_318, NULL, 404, 405, 5, 42},
  {cont__2_321, NULL, 406, 407, 5, 42},
  {cont__2_324, NULL, 408, 409, 5, 42},
  {cont__2_327, NULL, 410, 411, 5, 42},
  {cont__2_330, NULL, 412, 413, 5, 42},
  {cont__2_333, NULL, 414, 415, 5, 42},
  {cont__2_336, NULL, 416, 417, 5, 30},
  {cont__2_339, NULL, 418, 419, 5, 80},
  {cont__2_342, NULL, 420, 421, 5, 64},
  {cont__2_345, NULL, 422, 423, 5, 71},
  {cont__2_348, NULL, 424, 425, 5, 32},
  {cont__2_351, NULL, 426, 427, 5, 42},
  {cont__2_354, NULL, 428, 429, 5, 41},
  {cont__2_357, NULL, 430, 431, 5, 55},
  {cont__2_360, NULL, 432, 433, 5, 35},
  {cont__2_363, NULL, 434, 435, 5, 36},
  {cont__2_366, NULL, 436, 437, 5, 38},
  {cont__2_369, NULL, 438, 439, 5, 77},
  {cont__2_372, NULL, 440, 441, 5, 71},
  {cont__2_375, NULL, 442, 443, 5, 38},
  {cont__2_378, NULL, 444, 445, 5, 40},
  {cont__2_381, NULL, 446, 447, 5, 45},
  {cont__2_384, NULL, 448, 449, 5, 50},
  {cont__2_387, NULL, 450, 451, 5, 30},
  {cont__2_390, NULL, 452, 453, 5, 30},
  {cont__2_393, NULL, 454, 455, 5, 46},
  {cont__2_396, NULL, 456, 457, 5, 74},
  {cont__2_399, NULL, 458, 459, 5, 41},
  {cont__2_402, NULL, 460, 461, 5, 42},
  {cont__2_405, NULL, 462, 463, 5, 41},
  {cont__2_408, NULL, 464, 465, 5, 39},
  {cont__2_411, NULL, 466, 467, 5, 40},
  {cont__2_414, NULL, 468, 469, 5, 39},
  {cont__2_417, NULL, 470, 471, 5, 37},
  {cont__2_420, NULL, 472, 473, 5, 38},
  {cont__2_423, NULL, 474, 475, 5, 43},
  {cont__2_426, NULL, 476, 477, 5, 34},
  {cont__2_429, NULL, 478, 479, 5, 35},
  {cont__2_432, NULL, 480, 481, 5, 32},
  {cont__2_435, NULL, 482, 483, 5, 26},
  {cont__2_438, NULL, 484, 485, 5, 36},
  {cont__2_441, NULL, 486, 487, 5, 36},
  {cont__2_444, NULL, 488, 489, 5, 24},
  {cont__2_447, NULL, 490, 491, 5, 63},
  {cont__2_450, NULL, 492, 493, 5, 52},
  {cont__2_453, NULL, 494, 495, 5, 46},
  {cont__2_456, NULL, 496, 497, 5, 37},
  {cont__2_459, NULL, 498, 499, 5, 61},
  {cont__2_462, NULL, 500, 501, 5, 61},
  {cont__2_465, NULL, 502, 503, 5, 51},
  {cont__2_468, NULL, 504, 505, 5, 36},
  {cont__2_471, NULL, 506, 507, 5, 29},
  {cont__2_474, NULL, 508, 509, 5, 47},
  {cont__2_477, NULL, 510, 511, 5, 55},
  {cont__2_480, NULL, 512, 513, 5, 70},
  {cont__2_483, NULL, 514, 515, 5, 81},
  {cont__2_486, NULL, 516, 517, 5, 35},
  {cont__2_489, NULL, 518, 519, 5, 36},
  {cont__2_492, NULL, 520, 521, 5, 36},
  {cont__2_495, NULL, 522, 523, 5, 36},
  {cont__2_498, NULL, 524, 525, 5, 36},
  {cont__2_501, NULL, 526, 527, 5, 37},
  {cont__2_504, NULL, 528, 529, 5, 37},
  {cont__2_507, NULL, 530, 531, 5, 37},
  {cont__2_510, NULL, 532, 533, 5, 38},
  {cont__2_513, NULL, 534, 535, 5, 30},
  {cont__2_516, NULL, 536, 537, 5, 29},
  {cont__2_519, NULL, 538, 539, 5, 31},
  {cont__2_522, NULL, 540, 541, 5, 35},
  {cont__2_525, NULL, 542, 543, 5, 36},
  {cont__2_528, NULL, 544, 545, 5, 51},
  {cont__2_531, NULL, 546, 547, 5, 46},
  {cont__2_534, NULL, 548, 549, 5, 33},
  {cont__2_537, NULL, 550, 551, 5, 30},
  {cont__2_540, NULL, 552, 553, 5, 74},
  {cont__2_543, NULL, 554, 555, 5, 37},
  {cont__2_546, NULL, 556, 557, 5, 47},
  {cont__2_549, NULL, 558, 559, 5, 39},
  {cont__2_552, NULL, 560, 561, 5, 70},
  {cont__2_555, NULL, 562, 563, 5, 76},
  {cont__2_558, NULL, 564, 565, 5, 43},
  {cont__2_561, NULL, 566, 567, 5, 48},
  {cont__2_564, NULL, 568, 569, 5, 44},
  {cont__2_567, NULL, 570, 571, 5, 43},
  {cont__2_570, NULL, 572, 573, 5, 43},
  {cont__2_573, NULL, 574, 575, 5, 43},
  {cont__2_576, NULL, 576, 577, 5, 37},
  {cont__2_579, NULL, 578, 579, 5, 37},
  {cont__2_582, NULL, 580, 581, 5, 43},
  {cont__2_585, NULL, 582, 583, 5, 35},
  {cont__2_588, NULL, 584, 585, 5, 35},
  {cont__2_591, NULL, 586, 587, 5, 41},
  {cont__2_594, NULL, 588, 589, 5, 41},
  {cont__2_597, NULL, 590, 591, 5, 41},
  {cont__2_600, NULL, 592, 593, 5, 47},
  {cont__2_603, NULL, 594, 595, 5, 54},
  {cont__2_606, NULL, 596, 597, 5, 54},
  {cont__2_609, NULL, 598, 599, 5, 44},
  {cont__2_612, NULL, 600, 601, 5, 55},
  {cont__2_615, NULL, 602, 603, 5, 55},
  {cont__2_618, NULL, 604, 605, 5, 45},
  {cont__2_621, NULL, 606, 607, 5, 44},
  {cont__2_624, NULL, 608, 609, 5, 44},
  {cont__2_627, NULL, 610, 611, 5, 44},
  {cont__2_630, NULL, 612, 613, 5, 54},
  {cont__2_633, NULL, 614, 615, 5, 53},
  {cont__2_636, NULL, 616, 617, 5, 44},
  {cont__2_639, NULL, 618, 619, 5, 41},
  {cont__2_642, NULL, 620, 621, 5, 38},
  {cont__2_645, NULL, 622, 623, 5, 58},
  {cont__2_648, NULL, 624, 625, 5, 48},
  {cont__2_651, NULL, 626, 627, 5, 32},
  {cont__2_654, NULL, 628, 629, 5, 58},
  {cont__2_657, NULL, 630, 631, 5, 51},
  {cont__2_660, NULL, 632, 633, 5, 57},
  {cont__2_663, NULL, 634, 635, 5, 57},
  {cont__2_666, NULL, 636, 637, 5, 48},
  {cont__2_669, NULL, 638, 639, 5, 54},
  {cont__2_672, NULL, 640, 641, 5, 60},
  {cont__2_675, NULL, 642, 643, 5, 30},
  {cont__2_678, NULL, 644, 645, 5, 54},
  {cont__2_681, NULL, 646, 647, 5, 37},
  {cont__2_684, NULL, 648, 649, 5, 37},
  {cont__2_687, NULL, 650, 651, 5, 48},
  {cont__2_690, NULL, 652, 653, 5, 51},
  {cont__2_693, NULL, 654, 655, 5, 51},
  {cont__2_696, NULL, 656, 657, 5, 36},
  {cont__2_699, NULL, 658, 659, 5, 58},
  {cont__2_702, NULL, 660, 661, 5, 43},
  {cont__2_705, NULL, 662, 663, 5, 66},
  {cont__2_708, NULL, 664, 669, 5, 22},
  {cont__2_711, NULL, 670, 675, 5, 20},
  {cont__2_714, NULL, 676, 679, 5, 8},
  {cont__2_717, NULL, 680, 681, 5, 28},
  {cont__2_720, NULL, 22, 681, 1, 30},
  {cont__2_721, NULL, }
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
  allocate_initialized_frame_gc(0, 0);
  // 24: "ASM" = "
  // 25:   #if defined(__GNUC__) && !defined(__clang__) && defined(__x86_64)
  // 26:     #define ASM(x) asm(x)
  // 27:   #else
  // 28:     #define ASM(x)
  // 29:   #endif
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_1;
  arguments->slots[1] = string__2_2;
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
  temp__1 = arguments->slots[0];
  // 30: "REGISTER" = "
  // 31:   #if defined(__GNUC__) && !defined(__clang__) && defined(__x86_64)
  // 32:     #define REGISTER register
  // 33:   #else
  // 34:     #define REGISTER IMPORT
  // 35:   #endif
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_4;
  arguments->slots[1] = string__2_5;
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
  temp__2 = arguments->slots[0];
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
  arguments->slots[0] = string__2_7;
  arguments->slots[1] = string__2_8;
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
  temp__3 = arguments->slots[0];
  // 44: "ATTRIBUTE_ENTRY" = "
  // 45:   typedef struct ATTRIBUTE_ENTRY ATTRIBUTE_ENTRY;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_10;
  arguments->slots[1] = string__2_11;
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
  temp__4 = arguments->slots[0];
  // 46: "SYMBOL_ENTRY" = "
  // 47:   typedef struct SYMBOL_ENTRY SYMBOL_ENTRY;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_13;
  arguments->slots[1] = string__2_14;
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
  temp__5 = arguments->slots[0];
  // 48: "HASH_ENTRY" = "
  // 49:   typedef struct HASH_ENTRY HASH_ENTRY;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_16;
  arguments->slots[1] = string__2_17;
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
  temp__6 = arguments->slots[0];
  // 50: "C_FUNCTION" = "
  // 51:   typedef struct {
  // 52:     const char *name;
  // 53:     void **func;
  // 54:     const char *module_name;
  // 55:   } C_FUNCTION;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_19;
  arguments->slots[1] = string__2_20;
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
  temp__7 = arguments->slots[0];
  // 56: "runtime_major_version" = "
  // 57:   int runtime_major_version(void);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_22;
  arguments->slots[1] = string__2_23;
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
  temp__8 = arguments->slots[0];
  // 58: "runtime_minor_version" = "
  // 59:   int runtime_minor_version(void);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_25;
  arguments->slots[1] = string__2_26;
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
  temp__9 = arguments->slots[0];
  // 60: "runtime_revision" = "
  // 61:   int runtime_revision(void);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_28;
  arguments->slots[1] = string__2_29;
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
  temp__10 = arguments->slots[0];
  // 62: "polymorphic_function_count" = "
  // 63:   int polymorphic_function_count;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_31;
  arguments->slots[1] = string__2_32;
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
  temp__11 = arguments->slots[0];
  // 64: "polymorphic_function_with_setter_count" = "
  // 65:   int polymorphic_function_with_setter_count;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_34;
  arguments->slots[1] = string__2_35;
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
  temp__12 = arguments->slots[0];
  // 66: "polymorphic_function_names" = "
  // 67:   const char **polymorphic_function_names;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_37;
  arguments->slots[1] = string__2_38;
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
  temp__13 = arguments->slots[0];
  // 68: "set_module" = "
  // 69:   void set_module(const char *name);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_40;
  arguments->slots[1] = string__2_41;
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
  temp__14 = arguments->slots[0];
  // 70: "register_module_info" = "
  // 71:   void register_module_info(MODULE_INFO *info);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_43;
  arguments->slots[1] = string__2_44;
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
  temp__15 = arguments->slots[0];
  // 72: "set_used_namespaces" = "
  // 73:   void set_used_namespaces(const char **namespaces);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_46;
  arguments->slots[1] = string__2_47;
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
  temp__16 = arguments->slots[0];
  // 74: "from_bool" = "
  // 75:   NODE *from_bool(int val);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_49;
  arguments->slots[1] = string__2_50;
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
  temp__17 = arguments->slots[0];
  // 76: "from_int" = "
  // 77:   NODE *from_int(int val);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_52;
  arguments->slots[1] = string__2_53;
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
  temp__18 = arguments->slots[0];
  // 78: "from_long" = "
  // 79:   NODE *from_long(long val);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_55;
  arguments->slots[1] = string__2_56;
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
  temp__19 = arguments->slots[0];
  // 80: "from_int64" = "
  // 81:   NODE *from_int64(int64_t val);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_58;
  arguments->slots[1] = string__2_59;
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
  temp__20 = arguments->slots[0];
  // 82: "from_uint32" = "
  // 83:   NODE *from_uint32(uint32_t val);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_61;
  arguments->slots[1] = string__2_62;
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
  temp__21 = arguments->slots[0];
  // 84: "from_uint64" = "
  // 85:   NODE *from_uint64(uint64_t val);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_64;
  arguments->slots[1] = string__2_65;
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
  temp__22 = arguments->slots[0];
  // 86: "from_double" = "
  // 87:   NODE *from_double(double val);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_67;
  arguments->slots[1] = string__2_68;
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
  temp__23 = arguments->slots[0];
  // 88: "from_digit_string" = "
  // 89:   NODE *from_digit_string(const char *str);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_70;
  arguments->slots[1] = string__2_71;
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
  temp__24 = arguments->slots[0];
  // 90: "from_uchar32" = "
  // 91:   NODE *from_uchar32(unsigned int chr);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_73;
  arguments->slots[1] = string__2_74;
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
  temp__25 = arguments->slots[0];
  // 92: "from_c_string" = "
  // 93:   NODE *from_c_string(const char *str);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_76;
  arguments->slots[1] = string__2_77;
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
  temp__26 = arguments->slots[0];
  // 94: "from_latin_1_string" = "
  // 95:   NODE *from_latin_1_string(const char *str, long len);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_79;
  arguments->slots[1] = string__2_80;
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
  temp__27 = arguments->slots[0];
  // 96: "from_uint32_string" = "
  // 97:   NODE *from_uint32_string(const uint32_t *str, long len);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_82;
  arguments->slots[1] = string__2_83;
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
  temp__28 = arguments->slots[0];
  // 98: "from_arguments" = "
  // 99:   NODE *from_arguments(int first_idx, int count);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_85;
  arguments->slots[1] = string__2_86;
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
  temp__29 = arguments->slots[0];
  // 100: "register_unique_item" = "
  // 101:   NODE *register_unique_item(const char *name);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_88;
  arguments->slots[1] = string__2_89;
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
  temp__30 = arguments->slots[0];
  // 102: "define_c_function" = "
  // 103:   void define_c_function(const char *name, void *func);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_91;
  arguments->slots[1] = string__2_92;
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
  temp__31 = arguments->slots[0];
  // 104: "register_polymorphic_function" = "
  // 105:   void register_polymorphic_function(const char *name, int *id_p);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_94;
  arguments->slots[1] = string__2_95;
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
  temp__32 = arguments->slots[0];
  // 106: "register_polymorphic_function_with_setter" = "
  // 107:   void register_polymorphic_function_with_setter(const char *name, int *id_p);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_97;
  arguments->slots[1] = string__2_98;
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
  temp__33 = arguments->slots[0];
  // 108: "define_polymorphic_function" = "
  // 109:   void define_polymorphic_function(
  // 110:     const char *namespace, const char *name, NODE_GETTER getter, int *id_p,
  // 111:     NODE **var_p
  // 112:   );
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_100;
  arguments->slots[1] = string__2_101;
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
  temp__34 = arguments->slots[0];
  // 113: "define_polymorphic_function_with_setter" = "
  // 114:   void define_polymorphic_function_with_setter(
  // 115:     const char *namespace, const char *name, NODE_GETTER getter, int *id_p,
  // 116:     NODE **var_p
  // 117:   );
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_103;
  arguments->slots[1] = string__2_104;
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
  temp__35 = arguments->slots[0];
  // 118: "define_privileged_polymorphic_function" = "
  // 119:   void define_privileged_polymorphic_function(
  // 120:     const char *namespace, const char *name, NODE_GETTER getter, int id,
  // 121:     NODE **var_p
  // 122:   );
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_106;
  arguments->slots[1] = string__2_107;
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
  temp__36 = arguments->slots[0];
  // 123: "define_single_assign_static" = "
  // 124:   void define_single_assign_static(
  // 125:     const char *namespace, const char *name,
  // 126:     NODE_GETTER getter, NODE **var_p
  // 127:   );
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_109;
  arguments->slots[1] = string__2_110;
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
  temp__37 = arguments->slots[0];
  // 128: "define_multi_assign_static" = "
  // 129:   void define_multi_assign_static(
  // 130:     const char *namespace, const char *name,
  // 131:     NODE_GETTER getter, NODE_SETTER setter
  // 132:   );
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_112;
  arguments->slots[1] = string__2_113;
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
  temp__38 = arguments->slots[0];
  // 133: "register_dynamic" = "
  // 134:   void register_dynamic(int *id_p);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_115;
  arguments->slots[1] = string__2_116;
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
  temp__39 = arguments->slots[0];
  // 135: "define_single_assign_dynamic" = "
  // 136:   void define_single_assign_dynamic(
  // 137:     const char *namespace, const char *name,
  // 138:     NODE_GETTER getter, NODE_SETTER definer,
  // 139:     int *id_p
  // 140:   );
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_118;
  arguments->slots[1] = string__2_119;
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
  temp__40 = arguments->slots[0];
  // 141: "define_multi_assign_dynamic" = "
  // 142:   void define_multi_assign_dynamic(
  // 143:     const char *namespace, const char *name,
  // 144:     NODE_GETTER getter, NODE_SETTER setter, NODE_SETTER definer,
  // 145:     int *id_p
  // 146:   );
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_121;
  arguments->slots[1] = string__2_122;
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
  temp__41 = arguments->slots[0];
  // 147: "define_type_function" = "
  // 148:   void define_type_function(
  // 149:     const char *namespace, const char *name, FUNC type, int par_cnt
  // 150:   );
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_124;
  arguments->slots[1] = string__2_125;
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
  temp__42 = arguments->slots[0];
  // 151: "define_attribute" = "
  // 152:   void define_attribute(
  // 153:     const char *namespace, const char *name,
  // 154:     int id, NODE *attribute
  // 155:   );
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_127;
  arguments->slots[1] = string__2_128;
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
  temp__43 = arguments->slots[0];
  // 156: "define_method" = "
  // 157:   void define_method(
  // 158:     const char *namespace, const char *name,
  // 159:     int id, NODE *method
  // 160:   );
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_130;
  arguments->slots[1] = string__2_131;
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
  temp__44 = arguments->slots[0];
  // 161: "use_polymorphic_function" = "
  // 162:   void use_polymorphic_function(
  // 163:     const char *namespace, const char *name, NODE_GETTER *getter, int *id
  // 164:   );
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_133;
  arguments->slots[1] = string__2_134;
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
  temp__45 = arguments->slots[0];
  // 165: "use_read_only" = "
  // 166:   void use_read_only(
  // 167:     const char *namespace, const char *name,
  // 168:     NODE_GETTER *getter, NODE_GETTER *get_value_or_future
  // 169:   );
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_136;
  arguments->slots[1] = string__2_137;
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
  temp__46 = arguments->slots[0];
  // 170: "use_read_write" = "
  // 171:   void use_read_write(
  // 172:     const char *namespace, const char *name,
  // 173:     NODE_GETTER *getter, NODE_SETTER *setter
  // 174:   );
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_139;
  arguments->slots[1] = string__2_140;
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
  temp__47 = arguments->slots[0];
  // 175: "use_single_assign_dynamic" = "
  // 176:   void use_single_assign_dynamic(
  // 177:     const char *namespace, const char *name,
  // 178:     NODE_GETTER *getter, NODE_SETTER *definer
  // 179:   );
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_142;
  arguments->slots[1] = string__2_143;
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
  temp__48 = arguments->slots[0];
  // 180: "use_multi_assign_dynamic" = "
  // 181:   void use_multi_assign_dynamic(
  // 182:     const char *namespace, const char *name,
  // 183:     NODE_GETTER *getter, NODE_SETTER *setter, NODE_SETTER *definer
  // 184:   );
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_145;
  arguments->slots[1] = string__2_146;
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
  temp__49 = arguments->slots[0];
  // 185: "resolve_symbols" = "
  // 186:   void resolve_symbols(void);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_148;
  arguments->slots[1] = string__2_149;
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
  temp__50 = arguments->slots[0];
  // 187: "resolve_attributes" = "
  // 188:   void resolve_attributes(void);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_151;
  arguments->slots[1] = string__2_152;
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
  temp__51 = arguments->slots[0];
  // 189: "NODE" = "
  // 190:   typedef union NODE NODE;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_154;
  arguments->slots[1] = string__2_155;
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
  temp__52 = arguments->slots[0];
  // 191: "FUNC" = "
  // 192:   typedef void (*FUNC)(void);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_157;
  arguments->slots[1] = string__2_158;
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
  temp__53 = arguments->slots[0];
  // 193: "NODE_GETTER" = "
  // 194:   typedef NODE *(*NODE_GETTER)(void);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_160;
  arguments->slots[1] = string__2_161;
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
  temp__54 = arguments->slots[0];
  // 195: "NODE_SETTER" = "
  // 196:   typedef void (*NODE_SETTER)(NODE *);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_163;
  arguments->slots[1] = string__2_164;
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
  temp__55 = arguments->slots[0];
  // 197: "COLLECTOR" = "
  // 198:   typedef void *COLLECTOR(void *);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_166;
  arguments->slots[1] = string__2_167;
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
  temp__56 = arguments->slots[0];
  // 199: "DESTRUCTOR" = "
  // 200:   typedef void (*DESTRUCTOR)(void *);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_169;
  arguments->slots[1] = string__2_170;
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
  temp__57 = arguments->slots[0];
  // 201: "VTABLE" = "
  // 202:   typedef struct VTABLE {
  // 203:     size_t size;
  // 204:     COLLECTOR *collect;
  // 205:     int8_t (*to_int8)(NODE *);
  // 206:     int16_t (*to_int16)(NODE *);
  // 207:     int32_t (*to_int32)(NODE *);
  // 208:     int64_t (*to_int64)(NODE *);
  // 209:     uint8_t (*to_uint8)(NODE *);
  // 210:     uint16_t (*to_uint16)(NODE *);
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_172;
  arguments->slots[1] = string__2_173;
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
  temp__58 = arguments->slots[0];
  // 225: "OCTREE" = "
  // 226:   typedef struct OCTREE {
  // 227:     struct OCTREE *nodes[8];
  // 228:   } OCTREE;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_175;
  arguments->slots[1] = string__2_176;
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
  temp__59 = arguments->slots[0];
  // 229: "ATTRIBUTES" = "
  // 230:   typedef struct ATTRIBUTES {
  // 231:     struct VTABLE *vtable;
  // 232:     struct OCTREE *nodes[7];
  // 233:   } ATTRIBUTES;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_178;
  arguments->slots[1] = string__2_179;
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
  temp__60 = arguments->slots[0];
  // 234: "DYNAMICS" = "
  // 235:   typedef struct DYNAMICS {
  // 236:     struct OCTREE *nodes[8];
  // 237:   } DYNAMICS;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_181;
  arguments->slots[1] = string__2_182;
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
  temp__61 = arguments->slots[0];
  // 238: "SIMPLE_NODE" = "
  // 239:   typedef struct SIMPLE_NODE {
  // 240:     FUNC type;
  // 241:     struct ATTRIBUTES *attributes;
  // 242:   } SIMPLE_NODE;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_184;
  arguments->slots[1] = string__2_185;
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
  temp__62 = arguments->slots[0];
  // 243: "CLOSURE" = "
  // 244:   typedef struct CLOSURE {
  // 245:     FUNC type;
  // 246:     struct ATTRIBUTES *attributes;
  // 247:     int parameter_count;
  // 248:     struct FRAME *frame;
  // 249:   } CLOSURE;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_187;
  arguments->slots[1] = string__2_188;
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
  temp__63 = arguments->slots[0];
  // 250: "FUNCTION" = "
  // 251:   typedef struct FUNCTION {
  // 252:     FUNC type;
  // 253:     struct ATTRIBUTES *attributes;
  // 254:     int parameter_count;
  // 255:   } FUNCTION;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_190;
  arguments->slots[1] = string__2_191;
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
  temp__64 = arguments->slots[0];
  // 256: "CONTINUATION" = "
  // 257:   typedef struct CONTINUATION {
  // 258:     FUNC type;
  // 259:     struct ATTRIBUTES *attributes;
  // 260:     int result_count;
  // 261:     struct FRAME *frame;
  // 262:     struct DYNAMICS *dynamics;
  // 263:     struct FRAME *exit_frame; // used by exit-functions
  // 264:   } CONTINUATION;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_193;
  arguments->slots[1] = string__2_194;
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
  temp__65 = arguments->slots[0];
  // 265: "ATTRIBUTE_LIST" = "
  // 266:   typedef struct ATTRIBUTE_LIST {
  // 267:     struct ATTRIBUTE_LIST *link;
  // 268:     int idx;
  // 269:     void *attr;
  // 270:   } ATTRIBUTE_LIST;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_196;
  arguments->slots[1] = string__2_197;
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
  temp__66 = arguments->slots[0];
  // 271: "FUTURE" = "
  // 272:   typedef struct FUTURE {
  // 273:     FUNC type;
  // 274:     struct ATTRIBUTES *attributes;
  // 275:     NODE *link;
  // 276:     struct ATTRIBUTE_LIST *pending_attributes;
  // 277:     NODE *dependent_futures;
  // 278:     NODE *prototype;
  // 279:     long is_already_initialized;
  // 280:     NODE *pad_2;
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_199;
  arguments->slots[1] = string__2_200;
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
  temp__67 = arguments->slots[0];
  // 282: "CELL" = "
  // 283:   typedef struct CELL {
  // 284:     FUNC type;
  // 285:     struct ATTRIBUTES *attributes;
  // 286:     NODE *contents;
  // 287:   } CELL;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_202;
  arguments->slots[1] = string__2_203;
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
  temp__68 = arguments->slots[0];
  // 288: "FRAME" = "
  // 289:   typedef struct FRAME {
  // 290:     FUNC cont;
  // 291:     struct FRAME *caller_frame;
  // 292:     long caller_result_count;
  // 293:     long slot_count;
  // 294:     NODE *slots[0];
  // 295:   } FRAME;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_205;
  arguments->slots[1] = string__2_206;
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
  temp__69 = arguments->slots[0];
  // 296: "FRAME_INFO" = "
  // 297:   typedef struct FRAME_INFO {
  // 298:     int var_count;
  // 299:     const char *var_names[];
  // 300:   } FRAME_INFO;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_208;
  arguments->slots[1] = string__2_209;
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
  temp__70 = arguments->slots[0];
  // 301: "CONTINUATION_INFO" = "
  // 302:   typedef struct CONTINUATION_INFO {
  // 303:     FUNC continuation;
  // 304:     struct FRAME_INFO *frame_info;
  // 305:     uint16_t first_line;
  // 306:     uint16_t last_line;
  // 307:     uint8_t first_column;
  // 308:     uint8_t last_column;
  // 309:     uint8_t submodule_index;
  // 310:     uint8_t unused;
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_211;
  arguments->slots[1] = string__2_212;
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
  temp__71 = arguments->slots[0];
  // 312: "MODULE_INFO" = "
  // 313:   typedef struct MODULE_INFO {
  // 314:     struct MODULE_INFO *link;
  // 315:     const char *name;
  // 316:     struct CONTINUATION_INFO *continuation_info;
  // 317:     int continuation_count;
  // 318:     NODE **var_tab;
  // 319:     const char **var_names;
  // 320:     int top_level_count;
  // 321:     const char **used_namespaces;
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_214;
  arguments->slots[1] = string__2_215;
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
  temp__72 = arguments->slots[0];
  // 324: "EVENT__MODE" = "
  // 325:   typedef enum {
  // 326:     EM__NORMAL,
  // 327:     EM__RECORD,
  // 328:     EM__REPLAY
  // 329:   } EVENT__MODE;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_217;
  arguments->slots[1] = string__2_218;
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
  temp__73 = arguments->slots[0];
  // 330: "MEMORY_BLOCK" = "
  // 331:   typedef struct MEMORY_BLOCK {
  // 332:     struct MEMORY_BLOCK *link;
  // 333:     long mark;
  // 334:     DESTRUCTOR destructor;
  // 335:   } MEMORY_BLOCK;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_220;
  arguments->slots[1] = string__2_221;
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
  temp__74 = arguments->slots[0];
  // 336: "PHASE_2_COLLECTOR" = "
  // 337:   typedef struct PHASE_2_COLLECTOR {
  // 338:     void *dummy;
  // 339:     void *next_collector;
  // 340:     void (*collector)(void *data);
  // 341:   } PHASE_2_COLLECTOR;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_223;
  arguments->slots[1] = string__2_224;
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
  temp__75 = arguments->slots[0];
  // 342: "argument_count" = "
  // 343:   REGISTER int argument_count ASM("ebx");
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_226;
  arguments->slots[1] = string__2_227;
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
  temp__76 = arguments->slots[0];
  // 344: "arguments" = "
  // 345:   REGISTER FRAME *arguments ASM("r12");
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_229;
  arguments->slots[1] = string__2_230;
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
  temp__77 = arguments->slots[0];
  // 346: "myself" = "
  // 347:   REGISTER NODE *myself ASM("r13");
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_232;
  arguments->slots[1] = string__2_233;
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
  temp__78 = arguments->slots[0];
  // 348: "func" = "
  // 349:   REGISTER FUNC func ASM("r14");
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_235;
  arguments->slots[1] = string__2_236;
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
  temp__79 = arguments->slots[0];
  // 350: "frame" = "
  // 351:   REGISTER FRAME *frame ASM("r15");
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_238;
  arguments->slots[1] = string__2_239;
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
  temp__80 = arguments->slots[0];
  // 352: "result_count" = "
  // 353:   int result_count;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_241;
  arguments->slots[1] = string__2_242;
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
  temp__81 = arguments->slots[0];
  // 354: "dynamics" = "
  // 355:   DYNAMICS *dynamics;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_244;
  arguments->slots[1] = string__2_245;
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
  temp__82 = arguments->slots[0];
  // 356: "main_argc" = "
  // 357:   int main_argc;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_247;
  arguments->slots[1] = string__2_248;
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
  temp__83 = arguments->slots[0];
  // 358: "main_argv" = "
  // 359:   char **main_argv;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_250;
  arguments->slots[1] = string__2_251;
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
  temp__84 = arguments->slots[0];
  // 360: "event__mode" = "
  // 361:   EVENT__MODE event__mode;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_253;
  arguments->slots[1] = string__2_254;
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
  temp__85 = arguments->slots[0];
  // 362: "node_p" = "
  // 363:   void *node_p;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_256;
  arguments->slots[1] = string__2_257;
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
  temp__86 = arguments->slots[0];
  // 364: "update_start_p" = "
  // 365:   void *update_start_p;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_259;
  arguments->slots[1] = string__2_260;
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
  temp__87 = arguments->slots[0];
  // 366: "coll_node_buf" = "
  // 367:   void *coll_node_buf;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_262;
  arguments->slots[1] = string__2_263;
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
  temp__88 = arguments->slots[0];
  // 368: "coll_node_buf_end" = "
  // 369:   void *coll_node_buf_end;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_265;
  arguments->slots[1] = string__2_266;
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
  temp__89 = arguments->slots[0];
  // 370: "undefined" = "
  // 371:   NODE *undefined;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_268;
  arguments->slots[1] = string__2_269;
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
  temp__90 = arguments->slots[0];
  // 372: "zero" = "
  // 373:   NODE *zero;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_271;
  arguments->slots[1] = string__2_272;
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
  temp__91 = arguments->slots[0];
  // 374: "boolean_true" = "
  // 375:   NODE *boolean_true;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_274;
  arguments->slots[1] = string__2_275;
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
  temp__92 = arguments->slots[0];
  // 376: "boolean_false" = "
  // 377:   NODE *boolean_false;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_277;
  arguments->slots[1] = string__2_278;
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
  temp__93 = arguments->slots[0];
  // 378: "empty_string" = "
  // 379:   NODE *empty_string;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_280;
  arguments->slots[1] = string__2_281;
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
  temp__94 = arguments->slots[0];
  // 380: "raise_exception_getter" = "
  // 381:   NODE_GETTER raise_exception_getter;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_283;
  arguments->slots[1] = string__2_284;
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
  temp__95 = arguments->slots[0];
  // 382: "instruction_counter" = "
  // 383:   uint64_t instruction_counter;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_286;
  arguments->slots[1] = string__2_287;
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
  temp__96 = arguments->slots[0];
  // 384: "no_attributes_level_1" = "
  // 385:   OCTREE no_attributes_level_1;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_289;
  arguments->slots[1] = string__2_290;
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
  temp__97 = arguments->slots[0];
  // 386: "no_attributes_level_2" = "
  // 387:   OCTREE no_attributes_level_2;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_292;
  arguments->slots[1] = string__2_293;
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
  temp__98 = arguments->slots[0];
  // 388: "no_attributes_level_3" = "
  // 389:   OCTREE no_attributes_level_3;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_295;
  arguments->slots[1] = string__2_296;
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
  temp__99 = arguments->slots[0];
  // 390: "no_attributes_level_4" = "
  // 391:   OCTREE no_attributes_level_4;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_298;
  arguments->slots[1] = string__2_299;
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
  temp__100 = arguments->slots[0];
  // 392: "no_attributes_level_5" = "
  // 393:   OCTREE no_attributes_level_5;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_301;
  arguments->slots[1] = string__2_302;
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
  temp__101 = arguments->slots[0];
  // 394: "no_attributes_level_6" = "
  // 395:   OCTREE no_attributes_level_6;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_304;
  arguments->slots[1] = string__2_305;
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
  temp__102 = arguments->slots[0];
  // 396: "no_attributes_level_7" = "
  // 397:   OCTREE no_attributes_level_7;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_307;
  arguments->slots[1] = string__2_308;
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
  temp__103 = arguments->slots[0];
  // 398: "no_attributes_level_8" = "
  // 399:   OCTREE no_attributes_level_8;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_310;
  arguments->slots[1] = string__2_311;
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
  temp__104 = arguments->slots[0];
  // 400: "undefined_attributes_level_1" = "
  // 401:   OCTREE undefined_attributes_level_1;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_313;
  arguments->slots[1] = string__2_314;
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
  temp__105 = arguments->slots[0];
  // 402: "undefined_attributes_level_2" = "
  // 403:   OCTREE undefined_attributes_level_2;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_316;
  arguments->slots[1] = string__2_317;
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
  temp__106 = arguments->slots[0];
  // 404: "undefined_attributes_level_3" = "
  // 405:   OCTREE undefined_attributes_level_3;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_319;
  arguments->slots[1] = string__2_320;
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
  temp__107 = arguments->slots[0];
  // 406: "undefined_attributes_level_4" = "
  // 407:   OCTREE undefined_attributes_level_4;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_322;
  arguments->slots[1] = string__2_323;
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
  temp__108 = arguments->slots[0];
  // 408: "undefined_attributes_level_5" = "
  // 409:   OCTREE undefined_attributes_level_5;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_325;
  arguments->slots[1] = string__2_326;
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
  temp__109 = arguments->slots[0];
  // 410: "undefined_attributes_level_6" = "
  // 411:   OCTREE undefined_attributes_level_6;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_328;
  arguments->slots[1] = string__2_329;
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
  temp__110 = arguments->slots[0];
  // 412: "undefined_attributes_level_7" = "
  // 413:   OCTREE undefined_attributes_level_7;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_331;
  arguments->slots[1] = string__2_332;
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
  temp__111 = arguments->slots[0];
  // 414: "undefined_attributes_level_8" = "
  // 415:   OCTREE undefined_attributes_level_8;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_334;
  arguments->slots[1] = string__2_335;
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
  temp__112 = arguments->slots[0];
  // 416: "runtime_debug_level" = "
  // 417:   int runtime_debug_level;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_337;
  arguments->slots[1] = string__2_338;
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
  temp__113 = arguments->slots[0];
  // 418: "unrecoverable_error" = "
  // 419:   __attribute__ ((noreturn)) void unrecoverable_error(const char *msg, ...);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_340;
  arguments->slots[1] = string__2_341;
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
  temp__114 = arguments->slots[0];
  // 420: "out_of_memory_error" = "
  // 421:   __attribute__ ((noreturn)) void out_of_memory_error(void);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_343;
  arguments->slots[1] = string__2_344;
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
  temp__115 = arguments->slots[0];
  // 422: "invalid_continuation_error" = "
  // 423:   __attribute__ ((noreturn)) void invalid_continuation_error(void);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_346;
  arguments->slots[1] = string__2_347;
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
  temp__116 = arguments->slots[0];
  // 424: "allocate" = "
  // 425:   void *allocate(long size);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_349;
  arguments->slots[1] = string__2_350;
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
  temp__117 = arguments->slots[0];
  // 426: "allocate_and_clear" = "
  // 427:   void *allocate_and_clear(long size);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_352;
  arguments->slots[1] = string__2_353;
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
  temp__118 = arguments->slots[0];
  // 428: "allocate_memory" = "
  // 429:   void *allocate_memory(size_t size);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_355;
  arguments->slots[1] = string__2_356;
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
  temp__119 = arguments->slots[0];
  // 430: "reallocate_memory" = "
  // 431:   void *reallocate_memory(void * buf, size_t size);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_358;
  arguments->slots[1] = string__2_359;
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
  temp__120 = arguments->slots[0];
  // 432: "allocate_gc" = "
  // 433:   void *allocate_gc(long size);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_361;
  arguments->slots[1] = string__2_362;
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
  temp__121 = arguments->slots[0];
  // 434: "allocate_arguments" = "
  // 435:   void allocate_arguments(void);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_364;
  arguments->slots[1] = string__2_365;
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
  temp__122 = arguments->slots[0];
  // 436: "allocate_fixed" = "
  // 437:   void *allocate_fixed(long size);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_367;
  arguments->slots[1] = string__2_368;
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
  temp__123 = arguments->slots[0];
  // 438: "allocate_fixed_with_destructor" = "
  // 439:   void *allocate_fixed_with_destructor(long size, DESTRUCTOR destructor);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_370;
  arguments->slots[1] = string__2_371;
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
  temp__124 = arguments->slots[0];
  // 440: "allocate_initialized_frame_gc" = "
  // 441:   void allocate_initialized_frame_gc(int slot_idx, int slot_count);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_373;
  arguments->slots[1] = string__2_374;
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
  temp__125 = arguments->slots[0];
  // 442: "allocate_large" = "
  // 443:   void *allocate_large(long size);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_376;
  arguments->slots[1] = string__2_377;
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
  temp__126 = arguments->slots[0];
  // 444: "deallocate_memory" = "
  // 445:   void deallocate_memory(void *buf);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_379;
  arguments->slots[1] = string__2_380;
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
  temp__127 = arguments->slots[0];
  // 446: "copy" = "
  // 447:   void *copy(const void *buf, long size);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_382;
  arguments->slots[1] = string__2_383;
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
  temp__128 = arguments->slots[0];
  // 448: "register_phase_2_collector" = "
  // 449:   void register_phase_2_collector(void *data);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_385;
  arguments->slots[1] = string__2_386;
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
  temp__129 = arguments->slots[0];
  // 450: "child_changed_state" = "
  // 451:   int child_changed_state;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_388;
  arguments->slots[1] = string__2_389;
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
  temp__130 = arguments->slots[0];
  // 452: "window_changed_size" = "
  // 453:   int window_changed_size;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_391;
  arguments->slots[1] = string__2_392;
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
  temp__131 = arguments->slots[0];
  // 454: "from_printf" = "
  // 455:   NODE *from_printf(const char *msg, ...);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_394;
  arguments->slots[1] = string__2_395;
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
  temp__132 = arguments->slots[0];
  // 456: "runtime_error" = "
  // 457:   __attribute__ ((noreturn)) void runtime_error(const char *msg, ...);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_397;
  arguments->slots[1] = string__2_398;
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
  temp__133 = arguments->slots[0];
  // 458: "too_few_arguments_error" = "
  // 459:   void too_few_arguments_error(void);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_400;
  arguments->slots[1] = string__2_401;
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
  temp__134 = arguments->slots[0];
  // 460: "too_many_arguments_error" = "
  // 461:   void too_many_arguments_error(void);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_403;
  arguments->slots[1] = string__2_404;
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
  temp__135 = arguments->slots[0];
  // 462: "invalid_arguments_error" = "
  // 463:   void invalid_arguments_error(void);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_406;
  arguments->slots[1] = string__2_407;
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
  temp__136 = arguments->slots[0];
  // 464: "too_few_results_error" = "
  // 465:   void too_few_results_error(void);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_409;
  arguments->slots[1] = string__2_410;
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
  temp__137 = arguments->slots[0];
  // 466: "too_many_results_error" = "
  // 467:   void too_many_results_error(void);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_412;
  arguments->slots[1] = string__2_413;
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
  temp__138 = arguments->slots[0];
  // 468: "invalid_results_error" = "
  // 469:   void invalid_results_error(void);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_415;
  arguments->slots[1] = string__2_416;
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
  temp__139 = arguments->slots[0];
  // 470: "invalid_index_error" = "
  // 471:   void invalid_index_error(void);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_418;
  arguments->slots[1] = string__2_419;
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
  temp__140 = arguments->slots[0];
  // 472: "divide_by_zero_error" = "
  // 473:   void divide_by_zero_error(void);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_421;
  arguments->slots[1] = string__2_422;
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
  temp__141 = arguments->slots[0];
  // 474: "not_yet_implemented_error" = "
  // 475:   void not_yet_implemented_error(void);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_424;
  arguments->slots[1] = string__2_425;
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
  temp__142 = arguments->slots[0];
  // 476: "no_such_function" = "
  // 477:   void no_such_function(void);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_427;
  arguments->slots[1] = string__2_428;
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
  temp__143 = arguments->slots[0];
  // 478: "no_such_attribute" = "
  // 479:   void no_such_attribute(void);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_430;
  arguments->slots[1] = string__2_431;
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
  temp__144 = arguments->slots[0];
  // 480: "resource_error" = "
  // 481:   void resource_error(void);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_433;
  arguments->slots[1] = string__2_434;
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
  temp__145 = arguments->slots[0];
  // 482: "io_error" = "
  // 483:   void io_error(void);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_436;
  arguments->slots[1] = string__2_437;
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
  temp__146 = arguments->slots[0];
  // 484: "initialize_runtime" = "
  // 485:   void initialize_runtime(void);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_439;
  arguments->slots[1] = string__2_440;
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
  temp__147 = arguments->slots[0];
  // 486: "initialize_phase_3" = "
  // 487:   void initialize_phase_3(void);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_442;
  arguments->slots[1] = string__2_443;
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
  temp__148 = arguments->slots[0];
  // 488: "current_mark" = "
  // 489:   long current_mark;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_445;
  arguments->slots[1] = string__2_446;
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
  temp__149 = arguments->slots[0];
  // 490: "join_nodes" = "
  // 491:   void join_nodes(void *left_node_pp, void *right_node_pp);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_448;
  arguments->slots[1] = string__2_449;
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
  temp__150 = arguments->slots[0];
  // 492: "clone_object_and_attributes" = "
  // 493:   NODE *clone_object_and_attributes(NODE *node);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_451;
  arguments->slots[1] = string__2_452;
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
  temp__151 = arguments->slots[0];
  // 494: "register_collector" = "
  // 495:   void register_collector(FUNC collector);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_454;
  arguments->slots[1] = string__2_455;
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
  temp__152 = arguments->slots[0];
  // 496: "collect_node" = "
  // 497:   NODE *collect_node(NODE *node);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_457;
  arguments->slots[1] = string__2_458;
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
  temp__153 = arguments->slots[0];
  // 498: "collect_static_attributes" = "
  // 499:   void collect_static_attributes(ATTRIBUTES *attributes);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_460;
  arguments->slots[1] = string__2_461;
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
  temp__154 = arguments->slots[0];
  // 500: "collect_attributes" = "
  // 501:   ATTRIBUTES *collect_attributes(ATTRIBUTES *attributes);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_463;
  arguments->slots[1] = string__2_464;
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
  temp__155 = arguments->slots[0];
  // 502: "collect_simple_node" = "
  // 503:   void *collect_simple_node(SIMPLE_NODE *node);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_466;
  arguments->slots[1] = string__2_467;
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
  temp__156 = arguments->slots[0];
  // 504: "total_garbage_collections" = "
  // 505:   int total_garbage_collections;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_469;
  arguments->slots[1] = string__2_470;
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
  temp__157 = arguments->slots[0];
  // 506: "collect_garbage" = "
  // 507:   void collect_garbage();
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_472;
  arguments->slots[1] = string__2_473;
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
  temp__158 = arguments->slots[0];
  // 508: "indent_to_string" = "
  // 509:   const char *indent_to_string(int indent);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_475;
  arguments->slots[1] = string__2_476;
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
  temp__159 = arguments->slots[0];
  // 510: "print" = "
  // 511:   int print(char **buf_p, const char *format, ...);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_478;
  arguments->slots[1] = string__2_479;
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
  temp__160 = arguments->slots[0];
  // 512: "debug_print" = "
  // 513:   int debug_print(int indent, char *buf, const char *format, ...);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_481;
  arguments->slots[1] = string__2_482;
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
  temp__161 = arguments->slots[0];
  // 514: "debug_print_head" = "
  // 515:   int debug_print_head(int *indent_p, char **buf_p, const char *format, ...);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_484;
  arguments->slots[1] = string__2_485;
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
  temp__162 = arguments->slots[0];
  // 516: "to_int8" = "
  // 517:   uint32_t to_int8(NODE *node);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_487;
  arguments->slots[1] = string__2_488;
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
  temp__163 = arguments->slots[0];
  // 518: "to_int16" = "
  // 519:   uint64_t to_int16(NODE *node);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_490;
  arguments->slots[1] = string__2_491;
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
  temp__164 = arguments->slots[0];
  // 520: "to_int32" = "
  // 521:   uint32_t to_int32(NODE *node);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_493;
  arguments->slots[1] = string__2_494;
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
  temp__165 = arguments->slots[0];
  // 522: "to_int64" = "
  // 523:   uint64_t to_int64(NODE *node);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_496;
  arguments->slots[1] = string__2_497;
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
  temp__166 = arguments->slots[0];
  // 524: "to_uint8" = "
  // 525:   uint32_t to_uint8(NODE *node);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_499;
  arguments->slots[1] = string__2_500;
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
  temp__167 = arguments->slots[0];
  // 526: "to_uint16" = "
  // 527:   uint64_t to_uint16(NODE *node);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_502;
  arguments->slots[1] = string__2_503;
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
  temp__168 = arguments->slots[0];
  // 528: "to_uint32" = "
  // 529:   uint32_t to_uint32(NODE *node);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_505;
  arguments->slots[1] = string__2_506;
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
  temp__169 = arguments->slots[0];
  // 530: "to_uint64" = "
  // 531:   uint64_t to_uint64(NODE *node);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_508;
  arguments->slots[1] = string__2_509;
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
  temp__170 = arguments->slots[0];
  // 532: "to_uchar32" = "
  // 533:   uint32_t to_uchar32(NODE *node);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_511;
  arguments->slots[1] = string__2_512;
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
  temp__171 = arguments->slots[0];
  // 534: "to_bool" = "
  // 535:   int to_bool(NODE *node);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_514;
  arguments->slots[1] = string__2_515;
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
  temp__172 = arguments->slots[0];
  // 536: "to_int" = "
  // 537:   int to_int(NODE *node);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_517;
  arguments->slots[1] = string__2_518;
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
  temp__173 = arguments->slots[0];
  // 538: "to_long" = "
  // 539:   long to_long(NODE *node);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_520;
  arguments->slots[1] = string__2_521;
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
  temp__174 = arguments->slots[0];
  // 540: "to_double" = "
  // 541:   double to_double(NODE *node);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_523;
  arguments->slots[1] = string__2_524;
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
  temp__175 = arguments->slots[0];
  // 542: "to_c_string" = "
  // 543:   char *to_c_string(NODE *node);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_526;
  arguments->slots[1] = string__2_527;
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
  temp__176 = arguments->slots[0];
  // 544: "to_octets" = "
  // 545:   uint8_t *to_octets(NODE *node, long *size_p);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_529;
  arguments->slots[1] = string__2_530;
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
  temp__177 = arguments->slots[0];
  // 546: "get_item_of" = "
  // 547:   NODE *get_item_of(NODE *node, long idx);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_532;
  arguments->slots[1] = string__2_533;
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
  temp__178 = arguments->slots[0];
  // 548: "length_of" = "
  // 549:   long length_of(NODE *node);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_535;
  arguments->slots[1] = string__2_536;
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
  temp__179 = arguments->slots[0];
  // 550: "unfold" = "
  // 551:   void unfold(NODE *node);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_538;
  arguments->slots[1] = string__2_539;
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
  temp__180 = arguments->slots[0];
  // 552: "debug_string" = "
  // 553:   long debug_string(NODE *node, int indent, int max_depth, char *buf);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_541;
  arguments->slots[1] = string__2_542;
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
  temp__181 = arguments->slots[0];
  // 554: "optional_item" = "
  // 555:   void optional_item(NODE *item);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_544;
  arguments->slots[1] = string__2_545;
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
  temp__182 = arguments->slots[0];
  // 556: "get_attribute" = "
  // 557:   NODE *get_attribute(NODE *node, int idx);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_547;
  arguments->slots[1] = string__2_548;
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
  temp__183 = arguments->slots[0];
  // 558: "polymorph_dispatch" = "
  // 559:   void polymorph_dispatch(int idx);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_550;
  arguments->slots[1] = string__2_551;
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
  temp__184 = arguments->slots[0];
  // 560: "set_attribute" = "
  // 561:   void set_attribute(ATTRIBUTES *attributes, int idx, void *attr);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_553;
  arguments->slots[1] = string__2_554;
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
  temp__185 = arguments->slots[0];
  // 562: "set_attribute_value" = "
  // 563:   void set_attribute_value(ATTRIBUTES *attributes, int idx, void *attr);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_556;
  arguments->slots[1] = string__2_557;
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
  temp__186 = arguments->slots[0];
  // 564: "record__event" = "
  // 565:   void record__event(const char *name);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_559;
  arguments->slots[1] = string__2_560;
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
  temp__187 = arguments->slots[0];
  // 566: "successful__action" = "
  // 567:   void successful__action(const char *name);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_562;
  arguments->slots[1] = string__2_563;
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
  temp__188 = arguments->slots[0];
  // 568: "failed__action" = "
  // 569:   void failed__action(const char *name);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_565;
  arguments->slots[1] = string__2_566;
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
  temp__189 = arguments->slots[0];
  // 570: "replay__event" = "
  // 571:   void replay__event(const char *name);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_568;
  arguments->slots[1] = string__2_569;
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
  temp__190 = arguments->slots[0];
  // 572: "replay__action" = "
  // 573:   int replay__action(const char *name);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_571;
  arguments->slots[1] = string__2_572;
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
  temp__191 = arguments->slots[0];
  // 574: "report__event" = "
  // 575:   void report__event(const char *name);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_574;
  arguments->slots[1] = string__2_575;
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
  temp__192 = arguments->slots[0];
  // 576: "print__pointer" = "
  // 577:   void print__pointer(void *ptr);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_577;
  arguments->slots[1] = string__2_578;
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
  temp__193 = arguments->slots[0];
  // 578: "store__pointer" = "
  // 579:   void store__pointer(void *ptr);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_580;
  arguments->slots[1] = string__2_581;
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
  temp__194 = arguments->slots[0];
  // 580: "retrieve__pointer" = "
  // 581:   void retrieve__pointer(void **ptr_p);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_583;
  arguments->slots[1] = string__2_584;
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
  temp__195 = arguments->slots[0];
  // 582: "print__integer" = "
  // 583:   void print__integer(int val);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_586;
  arguments->slots[1] = string__2_587;
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
  temp__196 = arguments->slots[0];
  // 584: "store__integer" = "
  // 585:   void store__integer(int val);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_589;
  arguments->slots[1] = string__2_590;
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
  temp__197 = arguments->slots[0];
  // 586: "retrieve__integer" = "
  // 587:   void retrieve__integer(int *val_p);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_592;
  arguments->slots[1] = string__2_593;
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
  temp__198 = arguments->slots[0];
  // 588: "print__long_integer" = "
  // 589:   void print__long_integer(long val);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_595;
  arguments->slots[1] = string__2_596;
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
  temp__199 = arguments->slots[0];
  // 590: "store__long_integer" = "
  // 591:   void store__long_integer(long val);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_598;
  arguments->slots[1] = string__2_599;
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
  temp__200 = arguments->slots[0];
  // 592: "retrieve__long_integer" = "
  // 593:   void retrieve__long_integer(long *val_p);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_601;
  arguments->slots[1] = string__2_602;
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
  temp__201 = arguments->slots[0];
  // 594: "print__int_array" = "
  // 595:   void print__int_array(const int *buf, long len);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_604;
  arguments->slots[1] = string__2_605;
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
  temp__202 = arguments->slots[0];
  // 596: "store__int_array" = "
  // 597:   void store__int_array(const int *buf, long len);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_607;
  arguments->slots[1] = string__2_608;
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
  temp__203 = arguments->slots[0];
  // 598: "retrieve__int_array" = "
  // 599:   long retrieve__int_array(int **buf_p);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_610;
  arguments->slots[1] = string__2_611;
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
  temp__204 = arguments->slots[0];
  // 600: "print__memory" = "
  // 601:   void print__memory(const uint8_t *buf, long len);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_613;
  arguments->slots[1] = string__2_614;
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
  temp__205 = arguments->slots[0];
  // 602: "store__memory" = "
  // 603:   void store__memory(const uint8_t *buf, long len);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_616;
  arguments->slots[1] = string__2_617;
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
  temp__206 = arguments->slots[0];
  // 604: "retrieve__memory" = "
  // 605:   long retrieve__memory(uint8_t **buf_p);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_619;
  arguments->slots[1] = string__2_620;
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
  temp__207 = arguments->slots[0];
  // 606: "print__c_string" = "
  // 607:   void print__c_string(const char *buf);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_622;
  arguments->slots[1] = string__2_623;
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
  temp__208 = arguments->slots[0];
  // 608: "store__c_string" = "
  // 609:   void store__c_string(const char *buf);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_625;
  arguments->slots[1] = string__2_626;
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
  temp__209 = arguments->slots[0];
  // 610: "retrieve__c_string" = "
  // 611:   void retrieve__c_string(char **buf_p);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_628;
  arguments->slots[1] = string__2_629;
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
  temp__210 = arguments->slots[0];
  // 612: "create_function" = "
  // 613:   NODE *create_function(FUNC func, int par_count);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_631;
  arguments->slots[1] = string__2_632;
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
  temp__211 = arguments->slots[0];
  // 614: "create_closure" = "
  // 615:   NODE *create_closure(FUNC type, int par_count);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_634;
  arguments->slots[1] = string__2_635;
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
  temp__212 = arguments->slots[0];
  // 616: "continuation_type_function" = "
  // 617:   void continuation_type_function(void);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_637;
  arguments->slots[1] = string__2_638;
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
  temp__213 = arguments->slots[0];
  // 618: "continuation_trampoline" = "
  // 619:   void continuation_trampoline(void);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_640;
  arguments->slots[1] = string__2_641;
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
  temp__214 = arguments->slots[0];
  // 620: "create_continuation" = "
  // 621:   NODE *create_continuation(void);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_643;
  arguments->slots[1] = string__2_644;
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
  temp__215 = arguments->slots[0];
  // 622: "create_continuation_with_exit" = "
  // 623:   NODE *create_continuation_with_exit(FUNC exit_func);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_646;
  arguments->slots[1] = string__2_647;
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
  temp__216 = arguments->slots[0];
  // 624: "initialize_function_attributes" = "
  // 625:   void initialize_function_attributes(void);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_649;
  arguments->slots[1] = string__2_650;
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
  temp__217 = arguments->slots[0];
  // 626: "create_future" = "
  // 627:   NODE *create_future(void);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_652;
  arguments->slots[1] = string__2_653;
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
  temp__218 = arguments->slots[0];
  // 628: "create_future_with_prototype" = "
  // 629:   NODE *create_future_with_prototype(NODE *prototype);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_655;
  arguments->slots[1] = string__2_656;
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
  temp__219 = arguments->slots[0];
  // 630: "initialize_future" = "
  // 631:   void initialize_future(NODE *var, NODE *val);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_658;
  arguments->slots[1] = string__2_659;
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
  temp__220 = arguments->slots[0];
  // 632: "maybe_initialize_future" = "
  // 633:   void maybe_initialize_future(NODE *var, NODE *val);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_661;
  arguments->slots[1] = string__2_662;
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
  temp__221 = arguments->slots[0];
  // 634: "initialize_maybe_future" = "
  // 635:   void initialize_maybe_future(NODE *var, NODE *val);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_664;
  arguments->slots[1] = string__2_665;
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
  temp__222 = arguments->slots[0];
  // 636: "assign_value" = "
  // 637:   void assign_value(NODE **dest, NODE *val);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_667;
  arguments->slots[1] = string__2_668;
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
  temp__223 = arguments->slots[0];
  // 638: "assign_variable" = "
  // 639:   void assign_variable(NODE **dest, NODE **var_p);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_670;
  arguments->slots[1] = string__2_671;
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
  temp__224 = arguments->slots[0];
  // 640: "def_attribute" = "
  // 641:   void def_attribute(NODE **var_p, int idx, void *attr);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_673;
  arguments->slots[1] = string__2_674;
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
  temp__225 = arguments->slots[0];
  // 642: "create_cell" = "
  // 643:   NODE *create_cell(void);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_676;
  arguments->slots[1] = string__2_677;
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
  temp__226 = arguments->slots[0];
  // 644: "create_cell_with_contents" = "
  // 645:   NODE *create_cell_with_contents(NODE *contents);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_679;
  arguments->slots[1] = string__2_680;
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
  temp__227 = arguments->slots[0];
  // 646: "get_dynamic_slot" = "
  // 647:   NODE *get_dynamic_slot(int id);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_682;
  arguments->slots[1] = string__2_683;
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
  temp__228 = arguments->slots[0];
  // 648: "get_dynamic_cell" = "
  // 649:   NODE *get_dynamic_cell(int id);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_685;
  arguments->slots[1] = string__2_686;
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
  temp__229 = arguments->slots[0];
  // 650: "set_dynamic_cell" = "
  // 651:   void set_dynamic_cell(int id, NODE *node);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_688;
  arguments->slots[1] = string__2_689;
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
  temp__230 = arguments->slots[0];
  // 652: "define_dynamic_slot" = "
  // 653:   void define_dynamic_slot(int id, NODE *node);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_691;
  arguments->slots[1] = string__2_692;
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
  temp__231 = arguments->slots[0];
  // 654: "define_dynamic_cell" = "
  // 655:   void define_dynamic_cell(int id, NODE *node);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_694;
  arguments->slots[1] = string__2_695;
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
  temp__232 = arguments->slots[0];
  // 656: "terminate" = "
  // 657:   void terminate(int exit_code);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_697;
  arguments->slots[1] = string__2_698;
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
  temp__233 = arguments->slots[0];
  // 658: "execute" = "
  // 659:   __attribute__ ((noreturn)) void execute(FUNC entry);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_700;
  arguments->slots[1] = string__2_701;
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
  temp__234 = arguments->slots[0];
  // 660: "invoke_callback" = "
  // 661:   void invoke_callback(NODE *callback);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_703;
  arguments->slots[1] = string__2_704;
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
  temp__235 = arguments->slots[0];
  // 662: "COMPARE_FUNCTION" = "
  // 663:   typedef int (*COMPARE_FUNCTION)(const void *, const void *);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_706;
  arguments->slots[1] = string__2_707;
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
  temp__236 = arguments->slots[0];
  // 664: "DEBUG_COMMAND" = "
  // 665:   typedef enum {
  // 666:     SHOW_PROMPT,
  // 667:     LOG_LAST_INSTRUCTION,
  // 668:     GOTO_INSTRUCTION
  // 669:   } DEBUG_COMMAND;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_709;
  arguments->slots[1] = string__2_710;
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
  temp__237 = arguments->slots[0];
  // 670: "SHARED_DATA" = "
  // 671:   typedef struct {
  // 672:     DEBUG_COMMAND command;
  // 673:     uint64_t instruction_counter;
  // 674:     int depth;
  // 675:   } SHARED_DATA;
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_712;
  arguments->slots[1] = string__2_713;
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
  temp__238 = arguments->slots[0];
  // 676: "retrieve_continuation_info" = "
  // 677:   int retrieve_continuation_info(
  // 678:     FUNC func, const char **filename_p, CONTINUATION_INFO **info_p
  // 679:   );
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_715;
  arguments->slots[1] = string__2_716;
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
  temp__239 = arguments->slots[0];
  // 680: "crash_dump" = "
  // 681:   void crash_dump(void);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2_718;
  arguments->slots[1] = string__2_719;
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
  temp__240 = arguments->slots[0];
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
  argument_count = 240;
  arguments = node_p;
  arguments->slots[0] = temp__1;
  arguments->slots[1] = temp__2;
  arguments->slots[2] = temp__3;
  arguments->slots[3] = temp__4;
  arguments->slots[4] = temp__5;
  arguments->slots[5] = temp__6;
  arguments->slots[6] = temp__7;
  arguments->slots[7] = temp__8;
  arguments->slots[8] = temp__9;
  arguments->slots[9] = temp__10;
  arguments->slots[10] = temp__11;
  arguments->slots[11] = temp__12;
  arguments->slots[12] = temp__13;
  arguments->slots[13] = temp__14;
  arguments->slots[14] = temp__15;
  arguments->slots[15] = temp__16;
  arguments->slots[16] = temp__17;
  arguments->slots[17] = temp__18;
  arguments->slots[18] = temp__19;
  arguments->slots[19] = temp__20;
  arguments->slots[20] = temp__21;
  arguments->slots[21] = temp__22;
  arguments->slots[22] = temp__23;
  arguments->slots[23] = temp__24;
  arguments->slots[24] = temp__25;
  arguments->slots[25] = temp__26;
  arguments->slots[26] = temp__27;
  arguments->slots[27] = temp__28;
  arguments->slots[28] = temp__29;
  arguments->slots[29] = temp__30;
  arguments->slots[30] = temp__31;
  arguments->slots[31] = temp__32;
  arguments->slots[32] = temp__33;
  arguments->slots[33] = temp__34;
  arguments->slots[34] = temp__35;
  arguments->slots[35] = temp__36;
  arguments->slots[36] = temp__37;
  arguments->slots[37] = temp__38;
  arguments->slots[38] = temp__39;
  arguments->slots[39] = temp__40;
  arguments->slots[40] = temp__41;
  arguments->slots[41] = temp__42;
  arguments->slots[42] = temp__43;
  arguments->slots[43] = temp__44;
  arguments->slots[44] = temp__45;
  arguments->slots[45] = temp__46;
  arguments->slots[46] = temp__47;
  arguments->slots[47] = temp__48;
  arguments->slots[48] = temp__49;
  arguments->slots[49] = temp__50;
  arguments->slots[50] = temp__51;
  arguments->slots[51] = temp__52;
  arguments->slots[52] = temp__53;
  arguments->slots[53] = temp__54;
  arguments->slots[54] = temp__55;
  arguments->slots[55] = temp__56;
  arguments->slots[56] = temp__57;
  arguments->slots[57] = temp__58;
  arguments->slots[58] = temp__59;
  arguments->slots[59] = temp__60;
  arguments->slots[60] = temp__61;
  arguments->slots[61] = temp__62;
  arguments->slots[62] = temp__63;
  arguments->slots[63] = temp__64;
  arguments->slots[64] = temp__65;
  arguments->slots[65] = temp__66;
  arguments->slots[66] = temp__67;
  arguments->slots[67] = temp__68;
  arguments->slots[68] = temp__69;
  arguments->slots[69] = temp__70;
  arguments->slots[70] = temp__71;
  arguments->slots[71] = temp__72;
  arguments->slots[72] = temp__73;
  arguments->slots[73] = temp__74;
  arguments->slots[74] = temp__75;
  arguments->slots[75] = temp__76;
  arguments->slots[76] = temp__77;
  arguments->slots[77] = temp__78;
  arguments->slots[78] = temp__79;
  arguments->slots[79] = temp__80;
  arguments->slots[80] = temp__81;
  arguments->slots[81] = temp__82;
  arguments->slots[82] = temp__83;
  arguments->slots[83] = temp__84;
  arguments->slots[84] = temp__85;
  arguments->slots[85] = temp__86;
  arguments->slots[86] = temp__87;
  arguments->slots[87] = temp__88;
  arguments->slots[88] = temp__89;
  arguments->slots[89] = temp__90;
  arguments->slots[90] = temp__91;
  arguments->slots[91] = temp__92;
  arguments->slots[92] = temp__93;
  arguments->slots[93] = temp__94;
  arguments->slots[94] = temp__95;
  arguments->slots[95] = temp__96;
  arguments->slots[96] = temp__97;
  arguments->slots[97] = temp__98;
  arguments->slots[98] = temp__99;
  arguments->slots[99] = temp__100;
  arguments->slots[100] = temp__101;
  arguments->slots[101] = temp__102;
  arguments->slots[102] = temp__103;
  arguments->slots[103] = temp__104;
  arguments->slots[104] = temp__105;
  arguments->slots[105] = temp__106;
  arguments->slots[106] = temp__107;
  arguments->slots[107] = temp__108;
  arguments->slots[108] = temp__109;
  arguments->slots[109] = temp__110;
  arguments->slots[110] = temp__111;
  arguments->slots[111] = temp__112;
  arguments->slots[112] = temp__113;
  arguments->slots[113] = temp__114;
  arguments->slots[114] = temp__115;
  arguments->slots[115] = temp__116;
  arguments->slots[116] = temp__117;
  arguments->slots[117] = temp__118;
  arguments->slots[118] = temp__119;
  arguments->slots[119] = temp__120;
  arguments->slots[120] = temp__121;
  arguments->slots[121] = temp__122;
  arguments->slots[122] = temp__123;
  arguments->slots[123] = temp__124;
  arguments->slots[124] = temp__125;
  arguments->slots[125] = temp__126;
  arguments->slots[126] = temp__127;
  arguments->slots[127] = temp__128;
  arguments->slots[128] = temp__129;
  arguments->slots[129] = temp__130;
  arguments->slots[130] = temp__131;
  arguments->slots[131] = temp__132;
  arguments->slots[132] = temp__133;
  arguments->slots[133] = temp__134;
  arguments->slots[134] = temp__135;
  arguments->slots[135] = temp__136;
  arguments->slots[136] = temp__137;
  arguments->slots[137] = temp__138;
  arguments->slots[138] = temp__139;
  arguments->slots[139] = temp__140;
  arguments->slots[140] = temp__141;
  arguments->slots[141] = temp__142;
  arguments->slots[142] = temp__143;
  arguments->slots[143] = temp__144;
  arguments->slots[144] = temp__145;
  arguments->slots[145] = temp__146;
  arguments->slots[146] = temp__147;
  arguments->slots[147] = temp__148;
  arguments->slots[148] = temp__149;
  arguments->slots[149] = temp__150;
  arguments->slots[150] = temp__151;
  arguments->slots[151] = temp__152;
  arguments->slots[152] = temp__153;
  arguments->slots[153] = temp__154;
  arguments->slots[154] = temp__155;
  arguments->slots[155] = temp__156;
  arguments->slots[156] = temp__157;
  arguments->slots[157] = temp__158;
  arguments->slots[158] = temp__159;
  arguments->slots[159] = temp__160;
  arguments->slots[160] = temp__161;
  arguments->slots[161] = temp__162;
  arguments->slots[162] = temp__163;
  arguments->slots[163] = temp__164;
  arguments->slots[164] = temp__165;
  arguments->slots[165] = temp__166;
  arguments->slots[166] = temp__167;
  arguments->slots[167] = temp__168;
  arguments->slots[168] = temp__169;
  arguments->slots[169] = temp__170;
  arguments->slots[170] = temp__171;
  arguments->slots[171] = temp__172;
  arguments->slots[172] = temp__173;
  arguments->slots[173] = temp__174;
  arguments->slots[174] = temp__175;
  arguments->slots[175] = temp__176;
  arguments->slots[176] = temp__177;
  arguments->slots[177] = temp__178;
  arguments->slots[178] = temp__179;
  arguments->slots[179] = temp__180;
  arguments->slots[180] = temp__181;
  arguments->slots[181] = temp__182;
  arguments->slots[182] = temp__183;
  arguments->slots[183] = temp__184;
  arguments->slots[184] = temp__185;
  arguments->slots[185] = temp__186;
  arguments->slots[186] = temp__187;
  arguments->slots[187] = temp__188;
  arguments->slots[188] = temp__189;
  arguments->slots[189] = temp__190;
  arguments->slots[190] = temp__191;
  arguments->slots[191] = temp__192;
  arguments->slots[192] = temp__193;
  arguments->slots[193] = temp__194;
  arguments->slots[194] = temp__195;
  arguments->slots[195] = temp__196;
  arguments->slots[196] = temp__197;
  arguments->slots[197] = temp__198;
  arguments->slots[198] = temp__199;
  arguments->slots[199] = temp__200;
  arguments->slots[200] = temp__201;
  arguments->slots[201] = temp__202;
  arguments->slots[202] = temp__203;
  arguments->slots[203] = temp__204;
  arguments->slots[204] = temp__205;
  arguments->slots[205] = temp__206;
  arguments->slots[206] = temp__207;
  arguments->slots[207] = temp__208;
  arguments->slots[208] = temp__209;
  arguments->slots[209] = temp__210;
  arguments->slots[210] = temp__211;
  arguments->slots[211] = temp__212;
  arguments->slots[212] = temp__213;
  arguments->slots[213] = temp__214;
  arguments->slots[214] = temp__215;
  arguments->slots[215] = temp__216;
  arguments->slots[216] = temp__217;
  arguments->slots[217] = temp__218;
  arguments->slots[218] = temp__219;
  arguments->slots[219] = temp__220;
  arguments->slots[220] = temp__221;
  arguments->slots[221] = temp__222;
  arguments->slots[222] = temp__223;
  arguments->slots[223] = temp__224;
  arguments->slots[224] = temp__225;
  arguments->slots[225] = temp__226;
  arguments->slots[226] = temp__227;
  arguments->slots[227] = temp__228;
  arguments->slots[228] = temp__229;
  arguments->slots[229] = temp__230;
  arguments->slots[230] = temp__231;
  arguments->slots[231] = temp__232;
  arguments->slots[232] = temp__233;
  arguments->slots[233] = temp__234;
  arguments->slots[234] = temp__235;
  arguments->slots[235] = temp__236;
  arguments->slots[236] = temp__237;
  arguments->slots[237] = temp__238;
  arguments->slots[238] = temp__239;
  arguments->slots[239] = temp__240;
  result_count = 1;
  myself = get__table();
  func = myself->type;
  frame->cont = cont__2_721;
}
static void cont__2_721(void) {
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
  temp__1 = collect_node(temp__1);
  temp__2 = collect_node(temp__2);
  temp__3 = collect_node(temp__3);
  temp__4 = collect_node(temp__4);
  temp__5 = collect_node(temp__5);
  temp__6 = collect_node(temp__6);
  temp__7 = collect_node(temp__7);
  temp__8 = collect_node(temp__8);
  temp__9 = collect_node(temp__9);
  temp__10 = collect_node(temp__10);
  temp__11 = collect_node(temp__11);
  temp__12 = collect_node(temp__12);
  temp__13 = collect_node(temp__13);
  temp__14 = collect_node(temp__14);
  temp__15 = collect_node(temp__15);
  temp__16 = collect_node(temp__16);
  temp__17 = collect_node(temp__17);
  temp__18 = collect_node(temp__18);
  temp__19 = collect_node(temp__19);
  temp__20 = collect_node(temp__20);
  temp__21 = collect_node(temp__21);
  temp__22 = collect_node(temp__22);
  temp__23 = collect_node(temp__23);
  temp__24 = collect_node(temp__24);
  temp__25 = collect_node(temp__25);
  temp__26 = collect_node(temp__26);
  temp__27 = collect_node(temp__27);
  temp__28 = collect_node(temp__28);
  temp__29 = collect_node(temp__29);
  temp__30 = collect_node(temp__30);
  temp__31 = collect_node(temp__31);
  temp__32 = collect_node(temp__32);
  temp__33 = collect_node(temp__33);
  temp__34 = collect_node(temp__34);
  temp__35 = collect_node(temp__35);
  temp__36 = collect_node(temp__36);
  temp__37 = collect_node(temp__37);
  temp__38 = collect_node(temp__38);
  temp__39 = collect_node(temp__39);
  temp__40 = collect_node(temp__40);
  temp__41 = collect_node(temp__41);
  temp__42 = collect_node(temp__42);
  temp__43 = collect_node(temp__43);
  temp__44 = collect_node(temp__44);
  temp__45 = collect_node(temp__45);
  temp__46 = collect_node(temp__46);
  temp__47 = collect_node(temp__47);
  temp__48 = collect_node(temp__48);
  temp__49 = collect_node(temp__49);
  temp__50 = collect_node(temp__50);
  temp__51 = collect_node(temp__51);
  temp__52 = collect_node(temp__52);
  temp__53 = collect_node(temp__53);
  temp__54 = collect_node(temp__54);
  temp__55 = collect_node(temp__55);
  temp__56 = collect_node(temp__56);
  temp__57 = collect_node(temp__57);
  temp__58 = collect_node(temp__58);
  temp__59 = collect_node(temp__59);
  temp__60 = collect_node(temp__60);
  temp__61 = collect_node(temp__61);
  temp__62 = collect_node(temp__62);
  temp__63 = collect_node(temp__63);
  temp__64 = collect_node(temp__64);
  temp__65 = collect_node(temp__65);
  temp__66 = collect_node(temp__66);
  temp__67 = collect_node(temp__67);
  temp__68 = collect_node(temp__68);
  temp__69 = collect_node(temp__69);
  temp__70 = collect_node(temp__70);
  temp__71 = collect_node(temp__71);
  temp__72 = collect_node(temp__72);
  temp__73 = collect_node(temp__73);
  temp__74 = collect_node(temp__74);
  temp__75 = collect_node(temp__75);
  temp__76 = collect_node(temp__76);
  temp__77 = collect_node(temp__77);
  temp__78 = collect_node(temp__78);
  temp__79 = collect_node(temp__79);
  temp__80 = collect_node(temp__80);
  temp__81 = collect_node(temp__81);
  temp__82 = collect_node(temp__82);
  temp__83 = collect_node(temp__83);
  temp__84 = collect_node(temp__84);
  temp__85 = collect_node(temp__85);
  temp__86 = collect_node(temp__86);
  temp__87 = collect_node(temp__87);
  temp__88 = collect_node(temp__88);
  temp__89 = collect_node(temp__89);
  temp__90 = collect_node(temp__90);
  temp__91 = collect_node(temp__91);
  temp__92 = collect_node(temp__92);
  temp__93 = collect_node(temp__93);
  temp__94 = collect_node(temp__94);
  temp__95 = collect_node(temp__95);
  temp__96 = collect_node(temp__96);
  temp__97 = collect_node(temp__97);
  temp__98 = collect_node(temp__98);
  temp__99 = collect_node(temp__99);
  temp__100 = collect_node(temp__100);
  temp__101 = collect_node(temp__101);
  temp__102 = collect_node(temp__102);
  temp__103 = collect_node(temp__103);
  temp__104 = collect_node(temp__104);
  temp__105 = collect_node(temp__105);
  temp__106 = collect_node(temp__106);
  temp__107 = collect_node(temp__107);
  temp__108 = collect_node(temp__108);
  temp__109 = collect_node(temp__109);
  temp__110 = collect_node(temp__110);
  temp__111 = collect_node(temp__111);
  temp__112 = collect_node(temp__112);
  temp__113 = collect_node(temp__113);
  temp__114 = collect_node(temp__114);
  temp__115 = collect_node(temp__115);
  temp__116 = collect_node(temp__116);
  temp__117 = collect_node(temp__117);
  temp__118 = collect_node(temp__118);
  temp__119 = collect_node(temp__119);
  temp__120 = collect_node(temp__120);
  temp__121 = collect_node(temp__121);
  temp__122 = collect_node(temp__122);
  temp__123 = collect_node(temp__123);
  temp__124 = collect_node(temp__124);
  temp__125 = collect_node(temp__125);
  temp__126 = collect_node(temp__126);
  temp__127 = collect_node(temp__127);
  temp__128 = collect_node(temp__128);
  temp__129 = collect_node(temp__129);
  temp__130 = collect_node(temp__130);
  temp__131 = collect_node(temp__131);
  temp__132 = collect_node(temp__132);
  temp__133 = collect_node(temp__133);
  temp__134 = collect_node(temp__134);
  temp__135 = collect_node(temp__135);
  temp__136 = collect_node(temp__136);
  temp__137 = collect_node(temp__137);
  temp__138 = collect_node(temp__138);
  temp__139 = collect_node(temp__139);
  temp__140 = collect_node(temp__140);
  temp__141 = collect_node(temp__141);
  temp__142 = collect_node(temp__142);
  temp__143 = collect_node(temp__143);
  temp__144 = collect_node(temp__144);
  temp__145 = collect_node(temp__145);
  temp__146 = collect_node(temp__146);
  temp__147 = collect_node(temp__147);
  temp__148 = collect_node(temp__148);
  temp__149 = collect_node(temp__149);
  temp__150 = collect_node(temp__150);
  temp__151 = collect_node(temp__151);
  temp__152 = collect_node(temp__152);
  temp__153 = collect_node(temp__153);
  temp__154 = collect_node(temp__154);
  temp__155 = collect_node(temp__155);
  temp__156 = collect_node(temp__156);
  temp__157 = collect_node(temp__157);
  temp__158 = collect_node(temp__158);
  temp__159 = collect_node(temp__159);
  temp__160 = collect_node(temp__160);
  temp__161 = collect_node(temp__161);
  temp__162 = collect_node(temp__162);
  temp__163 = collect_node(temp__163);
  temp__164 = collect_node(temp__164);
  temp__165 = collect_node(temp__165);
  temp__166 = collect_node(temp__166);
  temp__167 = collect_node(temp__167);
  temp__168 = collect_node(temp__168);
  temp__169 = collect_node(temp__169);
  temp__170 = collect_node(temp__170);
  temp__171 = collect_node(temp__171);
  temp__172 = collect_node(temp__172);
  temp__173 = collect_node(temp__173);
  temp__174 = collect_node(temp__174);
  temp__175 = collect_node(temp__175);
  temp__176 = collect_node(temp__176);
  temp__177 = collect_node(temp__177);
  temp__178 = collect_node(temp__178);
  temp__179 = collect_node(temp__179);
  temp__180 = collect_node(temp__180);
  temp__181 = collect_node(temp__181);
  temp__182 = collect_node(temp__182);
  temp__183 = collect_node(temp__183);
  temp__184 = collect_node(temp__184);
  temp__185 = collect_node(temp__185);
  temp__186 = collect_node(temp__186);
  temp__187 = collect_node(temp__187);
  temp__188 = collect_node(temp__188);
  temp__189 = collect_node(temp__189);
  temp__190 = collect_node(temp__190);
  temp__191 = collect_node(temp__191);
  temp__192 = collect_node(temp__192);
  temp__193 = collect_node(temp__193);
  temp__194 = collect_node(temp__194);
  temp__195 = collect_node(temp__195);
  temp__196 = collect_node(temp__196);
  temp__197 = collect_node(temp__197);
  temp__198 = collect_node(temp__198);
  temp__199 = collect_node(temp__199);
  temp__200 = collect_node(temp__200);
  temp__201 = collect_node(temp__201);
  temp__202 = collect_node(temp__202);
  temp__203 = collect_node(temp__203);
  temp__204 = collect_node(temp__204);
  temp__205 = collect_node(temp__205);
  temp__206 = collect_node(temp__206);
  temp__207 = collect_node(temp__207);
  temp__208 = collect_node(temp__208);
  temp__209 = collect_node(temp__209);
  temp__210 = collect_node(temp__210);
  temp__211 = collect_node(temp__211);
  temp__212 = collect_node(temp__212);
  temp__213 = collect_node(temp__213);
  temp__214 = collect_node(temp__214);
  temp__215 = collect_node(temp__215);
  temp__216 = collect_node(temp__216);
  temp__217 = collect_node(temp__217);
  temp__218 = collect_node(temp__218);
  temp__219 = collect_node(temp__219);
  temp__220 = collect_node(temp__220);
  temp__221 = collect_node(temp__221);
  temp__222 = collect_node(temp__222);
  temp__223 = collect_node(temp__223);
  temp__224 = collect_node(temp__224);
  temp__225 = collect_node(temp__225);
  temp__226 = collect_node(temp__226);
  temp__227 = collect_node(temp__227);
  temp__228 = collect_node(temp__228);
  temp__229 = collect_node(temp__229);
  temp__230 = collect_node(temp__230);
  temp__231 = collect_node(temp__231);
  temp__232 = collect_node(temp__232);
  temp__233 = collect_node(temp__233);
  temp__234 = collect_node(temp__234);
  temp__235 = collect_node(temp__235);
  temp__236 = collect_node(temp__236);
  temp__237 = collect_node(temp__237);
  temp__238 = collect_node(temp__238);
  temp__239 = collect_node(temp__239);
  temp__240 = collect_node(temp__240);
  var.sim2c__runtime_symbols = collect_node(var.sim2c__runtime_symbols);
  string__2_1 = collect_node(string__2_1);
  string__2_2 = collect_node(string__2_2);
  string__2_4 = collect_node(string__2_4);
  string__2_5 = collect_node(string__2_5);
  string__2_7 = collect_node(string__2_7);
  string__2_8 = collect_node(string__2_8);
  string__2_10 = collect_node(string__2_10);
  string__2_11 = collect_node(string__2_11);
  string__2_13 = collect_node(string__2_13);
  string__2_14 = collect_node(string__2_14);
  string__2_16 = collect_node(string__2_16);
  string__2_17 = collect_node(string__2_17);
  string__2_19 = collect_node(string__2_19);
  string__2_20 = collect_node(string__2_20);
  string__2_22 = collect_node(string__2_22);
  string__2_23 = collect_node(string__2_23);
  string__2_25 = collect_node(string__2_25);
  string__2_26 = collect_node(string__2_26);
  string__2_28 = collect_node(string__2_28);
  string__2_29 = collect_node(string__2_29);
  string__2_31 = collect_node(string__2_31);
  string__2_32 = collect_node(string__2_32);
  string__2_34 = collect_node(string__2_34);
  string__2_35 = collect_node(string__2_35);
  string__2_37 = collect_node(string__2_37);
  string__2_38 = collect_node(string__2_38);
  string__2_40 = collect_node(string__2_40);
  string__2_41 = collect_node(string__2_41);
  string__2_43 = collect_node(string__2_43);
  string__2_44 = collect_node(string__2_44);
  string__2_46 = collect_node(string__2_46);
  string__2_47 = collect_node(string__2_47);
  string__2_49 = collect_node(string__2_49);
  string__2_50 = collect_node(string__2_50);
  string__2_52 = collect_node(string__2_52);
  string__2_53 = collect_node(string__2_53);
  string__2_55 = collect_node(string__2_55);
  string__2_56 = collect_node(string__2_56);
  string__2_58 = collect_node(string__2_58);
  string__2_59 = collect_node(string__2_59);
  string__2_61 = collect_node(string__2_61);
  string__2_62 = collect_node(string__2_62);
  string__2_64 = collect_node(string__2_64);
  string__2_65 = collect_node(string__2_65);
  string__2_67 = collect_node(string__2_67);
  string__2_68 = collect_node(string__2_68);
  string__2_70 = collect_node(string__2_70);
  string__2_71 = collect_node(string__2_71);
  string__2_73 = collect_node(string__2_73);
  string__2_74 = collect_node(string__2_74);
  string__2_76 = collect_node(string__2_76);
  string__2_77 = collect_node(string__2_77);
  string__2_79 = collect_node(string__2_79);
  string__2_80 = collect_node(string__2_80);
  string__2_82 = collect_node(string__2_82);
  string__2_83 = collect_node(string__2_83);
  string__2_85 = collect_node(string__2_85);
  string__2_86 = collect_node(string__2_86);
  string__2_88 = collect_node(string__2_88);
  string__2_89 = collect_node(string__2_89);
  string__2_91 = collect_node(string__2_91);
  string__2_92 = collect_node(string__2_92);
  string__2_94 = collect_node(string__2_94);
  string__2_95 = collect_node(string__2_95);
  string__2_97 = collect_node(string__2_97);
  string__2_98 = collect_node(string__2_98);
  string__2_100 = collect_node(string__2_100);
  string__2_101 = collect_node(string__2_101);
  string__2_103 = collect_node(string__2_103);
  string__2_104 = collect_node(string__2_104);
  string__2_106 = collect_node(string__2_106);
  string__2_107 = collect_node(string__2_107);
  string__2_109 = collect_node(string__2_109);
  string__2_110 = collect_node(string__2_110);
  string__2_112 = collect_node(string__2_112);
  string__2_113 = collect_node(string__2_113);
  string__2_115 = collect_node(string__2_115);
  string__2_116 = collect_node(string__2_116);
  string__2_118 = collect_node(string__2_118);
  string__2_119 = collect_node(string__2_119);
  string__2_121 = collect_node(string__2_121);
  string__2_122 = collect_node(string__2_122);
  string__2_124 = collect_node(string__2_124);
  string__2_125 = collect_node(string__2_125);
  string__2_127 = collect_node(string__2_127);
  string__2_128 = collect_node(string__2_128);
  string__2_130 = collect_node(string__2_130);
  string__2_131 = collect_node(string__2_131);
  string__2_133 = collect_node(string__2_133);
  string__2_134 = collect_node(string__2_134);
  string__2_136 = collect_node(string__2_136);
  string__2_137 = collect_node(string__2_137);
  string__2_139 = collect_node(string__2_139);
  string__2_140 = collect_node(string__2_140);
  string__2_142 = collect_node(string__2_142);
  string__2_143 = collect_node(string__2_143);
  string__2_145 = collect_node(string__2_145);
  string__2_146 = collect_node(string__2_146);
  string__2_148 = collect_node(string__2_148);
  string__2_149 = collect_node(string__2_149);
  string__2_151 = collect_node(string__2_151);
  string__2_152 = collect_node(string__2_152);
  string__2_154 = collect_node(string__2_154);
  string__2_155 = collect_node(string__2_155);
  string__2_157 = collect_node(string__2_157);
  string__2_158 = collect_node(string__2_158);
  string__2_160 = collect_node(string__2_160);
  string__2_161 = collect_node(string__2_161);
  string__2_163 = collect_node(string__2_163);
  string__2_164 = collect_node(string__2_164);
  string__2_166 = collect_node(string__2_166);
  string__2_167 = collect_node(string__2_167);
  string__2_169 = collect_node(string__2_169);
  string__2_170 = collect_node(string__2_170);
  string__2_172 = collect_node(string__2_172);
  string__2_173 = collect_node(string__2_173);
  string__2_175 = collect_node(string__2_175);
  string__2_176 = collect_node(string__2_176);
  string__2_178 = collect_node(string__2_178);
  string__2_179 = collect_node(string__2_179);
  string__2_181 = collect_node(string__2_181);
  string__2_182 = collect_node(string__2_182);
  string__2_184 = collect_node(string__2_184);
  string__2_185 = collect_node(string__2_185);
  string__2_187 = collect_node(string__2_187);
  string__2_188 = collect_node(string__2_188);
  string__2_190 = collect_node(string__2_190);
  string__2_191 = collect_node(string__2_191);
  string__2_193 = collect_node(string__2_193);
  string__2_194 = collect_node(string__2_194);
  string__2_196 = collect_node(string__2_196);
  string__2_197 = collect_node(string__2_197);
  string__2_199 = collect_node(string__2_199);
  string__2_200 = collect_node(string__2_200);
  string__2_202 = collect_node(string__2_202);
  string__2_203 = collect_node(string__2_203);
  string__2_205 = collect_node(string__2_205);
  string__2_206 = collect_node(string__2_206);
  string__2_208 = collect_node(string__2_208);
  string__2_209 = collect_node(string__2_209);
  string__2_211 = collect_node(string__2_211);
  string__2_212 = collect_node(string__2_212);
  string__2_214 = collect_node(string__2_214);
  string__2_215 = collect_node(string__2_215);
  string__2_217 = collect_node(string__2_217);
  string__2_218 = collect_node(string__2_218);
  string__2_220 = collect_node(string__2_220);
  string__2_221 = collect_node(string__2_221);
  string__2_223 = collect_node(string__2_223);
  string__2_224 = collect_node(string__2_224);
  string__2_226 = collect_node(string__2_226);
  string__2_227 = collect_node(string__2_227);
  string__2_229 = collect_node(string__2_229);
  string__2_230 = collect_node(string__2_230);
  string__2_232 = collect_node(string__2_232);
  string__2_233 = collect_node(string__2_233);
  string__2_235 = collect_node(string__2_235);
  string__2_236 = collect_node(string__2_236);
  string__2_238 = collect_node(string__2_238);
  string__2_239 = collect_node(string__2_239);
  string__2_241 = collect_node(string__2_241);
  string__2_242 = collect_node(string__2_242);
  string__2_244 = collect_node(string__2_244);
  string__2_245 = collect_node(string__2_245);
  string__2_247 = collect_node(string__2_247);
  string__2_248 = collect_node(string__2_248);
  string__2_250 = collect_node(string__2_250);
  string__2_251 = collect_node(string__2_251);
  string__2_253 = collect_node(string__2_253);
  string__2_254 = collect_node(string__2_254);
  string__2_256 = collect_node(string__2_256);
  string__2_257 = collect_node(string__2_257);
  string__2_259 = collect_node(string__2_259);
  string__2_260 = collect_node(string__2_260);
  string__2_262 = collect_node(string__2_262);
  string__2_263 = collect_node(string__2_263);
  string__2_265 = collect_node(string__2_265);
  string__2_266 = collect_node(string__2_266);
  string__2_268 = collect_node(string__2_268);
  string__2_269 = collect_node(string__2_269);
  string__2_271 = collect_node(string__2_271);
  string__2_272 = collect_node(string__2_272);
  string__2_274 = collect_node(string__2_274);
  string__2_275 = collect_node(string__2_275);
  string__2_277 = collect_node(string__2_277);
  string__2_278 = collect_node(string__2_278);
  string__2_280 = collect_node(string__2_280);
  string__2_281 = collect_node(string__2_281);
  string__2_283 = collect_node(string__2_283);
  string__2_284 = collect_node(string__2_284);
  string__2_286 = collect_node(string__2_286);
  string__2_287 = collect_node(string__2_287);
  string__2_289 = collect_node(string__2_289);
  string__2_290 = collect_node(string__2_290);
  string__2_292 = collect_node(string__2_292);
  string__2_293 = collect_node(string__2_293);
  string__2_295 = collect_node(string__2_295);
  string__2_296 = collect_node(string__2_296);
  string__2_298 = collect_node(string__2_298);
  string__2_299 = collect_node(string__2_299);
  string__2_301 = collect_node(string__2_301);
  string__2_302 = collect_node(string__2_302);
  string__2_304 = collect_node(string__2_304);
  string__2_305 = collect_node(string__2_305);
  string__2_307 = collect_node(string__2_307);
  string__2_308 = collect_node(string__2_308);
  string__2_310 = collect_node(string__2_310);
  string__2_311 = collect_node(string__2_311);
  string__2_313 = collect_node(string__2_313);
  string__2_314 = collect_node(string__2_314);
  string__2_316 = collect_node(string__2_316);
  string__2_317 = collect_node(string__2_317);
  string__2_319 = collect_node(string__2_319);
  string__2_320 = collect_node(string__2_320);
  string__2_322 = collect_node(string__2_322);
  string__2_323 = collect_node(string__2_323);
  string__2_325 = collect_node(string__2_325);
  string__2_326 = collect_node(string__2_326);
  string__2_328 = collect_node(string__2_328);
  string__2_329 = collect_node(string__2_329);
  string__2_331 = collect_node(string__2_331);
  string__2_332 = collect_node(string__2_332);
  string__2_334 = collect_node(string__2_334);
  string__2_335 = collect_node(string__2_335);
  string__2_337 = collect_node(string__2_337);
  string__2_338 = collect_node(string__2_338);
  string__2_340 = collect_node(string__2_340);
  string__2_341 = collect_node(string__2_341);
  string__2_343 = collect_node(string__2_343);
  string__2_344 = collect_node(string__2_344);
  string__2_346 = collect_node(string__2_346);
  string__2_347 = collect_node(string__2_347);
  string__2_349 = collect_node(string__2_349);
  string__2_350 = collect_node(string__2_350);
  string__2_352 = collect_node(string__2_352);
  string__2_353 = collect_node(string__2_353);
  string__2_355 = collect_node(string__2_355);
  string__2_356 = collect_node(string__2_356);
  string__2_358 = collect_node(string__2_358);
  string__2_359 = collect_node(string__2_359);
  string__2_361 = collect_node(string__2_361);
  string__2_362 = collect_node(string__2_362);
  string__2_364 = collect_node(string__2_364);
  string__2_365 = collect_node(string__2_365);
  string__2_367 = collect_node(string__2_367);
  string__2_368 = collect_node(string__2_368);
  string__2_370 = collect_node(string__2_370);
  string__2_371 = collect_node(string__2_371);
  string__2_373 = collect_node(string__2_373);
  string__2_374 = collect_node(string__2_374);
  string__2_376 = collect_node(string__2_376);
  string__2_377 = collect_node(string__2_377);
  string__2_379 = collect_node(string__2_379);
  string__2_380 = collect_node(string__2_380);
  string__2_382 = collect_node(string__2_382);
  string__2_383 = collect_node(string__2_383);
  string__2_385 = collect_node(string__2_385);
  string__2_386 = collect_node(string__2_386);
  string__2_388 = collect_node(string__2_388);
  string__2_389 = collect_node(string__2_389);
  string__2_391 = collect_node(string__2_391);
  string__2_392 = collect_node(string__2_392);
  string__2_394 = collect_node(string__2_394);
  string__2_395 = collect_node(string__2_395);
  string__2_397 = collect_node(string__2_397);
  string__2_398 = collect_node(string__2_398);
  string__2_400 = collect_node(string__2_400);
  string__2_401 = collect_node(string__2_401);
  string__2_403 = collect_node(string__2_403);
  string__2_404 = collect_node(string__2_404);
  string__2_406 = collect_node(string__2_406);
  string__2_407 = collect_node(string__2_407);
  string__2_409 = collect_node(string__2_409);
  string__2_410 = collect_node(string__2_410);
  string__2_412 = collect_node(string__2_412);
  string__2_413 = collect_node(string__2_413);
  string__2_415 = collect_node(string__2_415);
  string__2_416 = collect_node(string__2_416);
  string__2_418 = collect_node(string__2_418);
  string__2_419 = collect_node(string__2_419);
  string__2_421 = collect_node(string__2_421);
  string__2_422 = collect_node(string__2_422);
  string__2_424 = collect_node(string__2_424);
  string__2_425 = collect_node(string__2_425);
  string__2_427 = collect_node(string__2_427);
  string__2_428 = collect_node(string__2_428);
  string__2_430 = collect_node(string__2_430);
  string__2_431 = collect_node(string__2_431);
  string__2_433 = collect_node(string__2_433);
  string__2_434 = collect_node(string__2_434);
  string__2_436 = collect_node(string__2_436);
  string__2_437 = collect_node(string__2_437);
  string__2_439 = collect_node(string__2_439);
  string__2_440 = collect_node(string__2_440);
  string__2_442 = collect_node(string__2_442);
  string__2_443 = collect_node(string__2_443);
  string__2_445 = collect_node(string__2_445);
  string__2_446 = collect_node(string__2_446);
  string__2_448 = collect_node(string__2_448);
  string__2_449 = collect_node(string__2_449);
  string__2_451 = collect_node(string__2_451);
  string__2_452 = collect_node(string__2_452);
  string__2_454 = collect_node(string__2_454);
  string__2_455 = collect_node(string__2_455);
  string__2_457 = collect_node(string__2_457);
  string__2_458 = collect_node(string__2_458);
  string__2_460 = collect_node(string__2_460);
  string__2_461 = collect_node(string__2_461);
  string__2_463 = collect_node(string__2_463);
  string__2_464 = collect_node(string__2_464);
  string__2_466 = collect_node(string__2_466);
  string__2_467 = collect_node(string__2_467);
  string__2_469 = collect_node(string__2_469);
  string__2_470 = collect_node(string__2_470);
  string__2_472 = collect_node(string__2_472);
  string__2_473 = collect_node(string__2_473);
  string__2_475 = collect_node(string__2_475);
  string__2_476 = collect_node(string__2_476);
  string__2_478 = collect_node(string__2_478);
  string__2_479 = collect_node(string__2_479);
  string__2_481 = collect_node(string__2_481);
  string__2_482 = collect_node(string__2_482);
  string__2_484 = collect_node(string__2_484);
  string__2_485 = collect_node(string__2_485);
  string__2_487 = collect_node(string__2_487);
  string__2_488 = collect_node(string__2_488);
  string__2_490 = collect_node(string__2_490);
  string__2_491 = collect_node(string__2_491);
  string__2_493 = collect_node(string__2_493);
  string__2_494 = collect_node(string__2_494);
  string__2_496 = collect_node(string__2_496);
  string__2_497 = collect_node(string__2_497);
  string__2_499 = collect_node(string__2_499);
  string__2_500 = collect_node(string__2_500);
  string__2_502 = collect_node(string__2_502);
  string__2_503 = collect_node(string__2_503);
  string__2_505 = collect_node(string__2_505);
  string__2_506 = collect_node(string__2_506);
  string__2_508 = collect_node(string__2_508);
  string__2_509 = collect_node(string__2_509);
  string__2_511 = collect_node(string__2_511);
  string__2_512 = collect_node(string__2_512);
  string__2_514 = collect_node(string__2_514);
  string__2_515 = collect_node(string__2_515);
  string__2_517 = collect_node(string__2_517);
  string__2_518 = collect_node(string__2_518);
  string__2_520 = collect_node(string__2_520);
  string__2_521 = collect_node(string__2_521);
  string__2_523 = collect_node(string__2_523);
  string__2_524 = collect_node(string__2_524);
  string__2_526 = collect_node(string__2_526);
  string__2_527 = collect_node(string__2_527);
  string__2_529 = collect_node(string__2_529);
  string__2_530 = collect_node(string__2_530);
  string__2_532 = collect_node(string__2_532);
  string__2_533 = collect_node(string__2_533);
  string__2_535 = collect_node(string__2_535);
  string__2_536 = collect_node(string__2_536);
  string__2_538 = collect_node(string__2_538);
  string__2_539 = collect_node(string__2_539);
  string__2_541 = collect_node(string__2_541);
  string__2_542 = collect_node(string__2_542);
  string__2_544 = collect_node(string__2_544);
  string__2_545 = collect_node(string__2_545);
  string__2_547 = collect_node(string__2_547);
  string__2_548 = collect_node(string__2_548);
  string__2_550 = collect_node(string__2_550);
  string__2_551 = collect_node(string__2_551);
  string__2_553 = collect_node(string__2_553);
  string__2_554 = collect_node(string__2_554);
  string__2_556 = collect_node(string__2_556);
  string__2_557 = collect_node(string__2_557);
  string__2_559 = collect_node(string__2_559);
  string__2_560 = collect_node(string__2_560);
  string__2_562 = collect_node(string__2_562);
  string__2_563 = collect_node(string__2_563);
  string__2_565 = collect_node(string__2_565);
  string__2_566 = collect_node(string__2_566);
  string__2_568 = collect_node(string__2_568);
  string__2_569 = collect_node(string__2_569);
  string__2_571 = collect_node(string__2_571);
  string__2_572 = collect_node(string__2_572);
  string__2_574 = collect_node(string__2_574);
  string__2_575 = collect_node(string__2_575);
  string__2_577 = collect_node(string__2_577);
  string__2_578 = collect_node(string__2_578);
  string__2_580 = collect_node(string__2_580);
  string__2_581 = collect_node(string__2_581);
  string__2_583 = collect_node(string__2_583);
  string__2_584 = collect_node(string__2_584);
  string__2_586 = collect_node(string__2_586);
  string__2_587 = collect_node(string__2_587);
  string__2_589 = collect_node(string__2_589);
  string__2_590 = collect_node(string__2_590);
  string__2_592 = collect_node(string__2_592);
  string__2_593 = collect_node(string__2_593);
  string__2_595 = collect_node(string__2_595);
  string__2_596 = collect_node(string__2_596);
  string__2_598 = collect_node(string__2_598);
  string__2_599 = collect_node(string__2_599);
  string__2_601 = collect_node(string__2_601);
  string__2_602 = collect_node(string__2_602);
  string__2_604 = collect_node(string__2_604);
  string__2_605 = collect_node(string__2_605);
  string__2_607 = collect_node(string__2_607);
  string__2_608 = collect_node(string__2_608);
  string__2_610 = collect_node(string__2_610);
  string__2_611 = collect_node(string__2_611);
  string__2_613 = collect_node(string__2_613);
  string__2_614 = collect_node(string__2_614);
  string__2_616 = collect_node(string__2_616);
  string__2_617 = collect_node(string__2_617);
  string__2_619 = collect_node(string__2_619);
  string__2_620 = collect_node(string__2_620);
  string__2_622 = collect_node(string__2_622);
  string__2_623 = collect_node(string__2_623);
  string__2_625 = collect_node(string__2_625);
  string__2_626 = collect_node(string__2_626);
  string__2_628 = collect_node(string__2_628);
  string__2_629 = collect_node(string__2_629);
  string__2_631 = collect_node(string__2_631);
  string__2_632 = collect_node(string__2_632);
  string__2_634 = collect_node(string__2_634);
  string__2_635 = collect_node(string__2_635);
  string__2_637 = collect_node(string__2_637);
  string__2_638 = collect_node(string__2_638);
  string__2_640 = collect_node(string__2_640);
  string__2_641 = collect_node(string__2_641);
  string__2_643 = collect_node(string__2_643);
  string__2_644 = collect_node(string__2_644);
  string__2_646 = collect_node(string__2_646);
  string__2_647 = collect_node(string__2_647);
  string__2_649 = collect_node(string__2_649);
  string__2_650 = collect_node(string__2_650);
  string__2_652 = collect_node(string__2_652);
  string__2_653 = collect_node(string__2_653);
  string__2_655 = collect_node(string__2_655);
  string__2_656 = collect_node(string__2_656);
  string__2_658 = collect_node(string__2_658);
  string__2_659 = collect_node(string__2_659);
  string__2_661 = collect_node(string__2_661);
  string__2_662 = collect_node(string__2_662);
  string__2_664 = collect_node(string__2_664);
  string__2_665 = collect_node(string__2_665);
  string__2_667 = collect_node(string__2_667);
  string__2_668 = collect_node(string__2_668);
  string__2_670 = collect_node(string__2_670);
  string__2_671 = collect_node(string__2_671);
  string__2_673 = collect_node(string__2_673);
  string__2_674 = collect_node(string__2_674);
  string__2_676 = collect_node(string__2_676);
  string__2_677 = collect_node(string__2_677);
  string__2_679 = collect_node(string__2_679);
  string__2_680 = collect_node(string__2_680);
  string__2_682 = collect_node(string__2_682);
  string__2_683 = collect_node(string__2_683);
  string__2_685 = collect_node(string__2_685);
  string__2_686 = collect_node(string__2_686);
  string__2_688 = collect_node(string__2_688);
  string__2_689 = collect_node(string__2_689);
  string__2_691 = collect_node(string__2_691);
  string__2_692 = collect_node(string__2_692);
  string__2_694 = collect_node(string__2_694);
  string__2_695 = collect_node(string__2_695);
  string__2_697 = collect_node(string__2_697);
  string__2_698 = collect_node(string__2_698);
  string__2_700 = collect_node(string__2_700);
  string__2_701 = collect_node(string__2_701);
  string__2_703 = collect_node(string__2_703);
  string__2_704 = collect_node(string__2_704);
  string__2_706 = collect_node(string__2_706);
  string__2_707 = collect_node(string__2_707);
  string__2_709 = collect_node(string__2_709);
  string__2_710 = collect_node(string__2_710);
  string__2_712 = collect_node(string__2_712);
  string__2_713 = collect_node(string__2_713);
  string__2_715 = collect_node(string__2_715);
  string__2_716 = collect_node(string__2_716);
  string__2_718 = collect_node(string__2_718);
  string__2_719 = collect_node(string__2_719);
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
  set_used_namespaces(used_namespaces);
  define_single_assign_static("sim2c", "runtime_symbols", get__sim2c__runtime_symbols, &var.sim2c__runtime_symbols);
  string__2_1 = from_latin_1_string("ASM", 3);
  string__2_2 = from_latin_1_string("#if defined(__GNUC__) && !defined(__clang__) && defined(__x86_64)\012  #define ASM(x) asm(x)\012#else\012  #define ASM(x)\012#endif\012", 120);
  string__2_4 = from_latin_1_string("REGISTER", 8);
  string__2_5 = from_latin_1_string("#if defined(__GNUC__) && !defined(__clang__) && defined(__x86_64)\012  #define REGISTER register\012#else\012  #define REGISTER IMPORT\012#endif\012", 133);
  string__2_7 = from_latin_1_string("VAR_TYPE", 8);
  string__2_8 = from_latin_1_string("typedef enum {\012  VT_POLYMORPHIC,\012  VT_SINGLE_ASSIGN_STATIC,\012  VT_MULTI_ASSIGN_STATIC,\012  VT_SINGLE_ASSIGN_DYNAMIC,\012  VT_MULTI_ASSIGN_DYNAMIC,\012} VAR_TYPE;\012", 153);
  string__2_10 = from_latin_1_string("ATTRIBUTE_ENTRY", 15);
  string__2_11 = from_latin_1_string("typedef struct ATTRIBUTE_ENTRY ATTRIBUTE_ENTRY;\012", 48);
  string__2_13 = from_latin_1_string("SYMBOL_ENTRY", 12);
  string__2_14 = from_latin_1_string("typedef struct SYMBOL_ENTRY SYMBOL_ENTRY;\012", 42);
  string__2_16 = from_latin_1_string("HASH_ENTRY", 10);
  string__2_17 = from_latin_1_string("typedef struct HASH_ENTRY HASH_ENTRY;\012", 38);
  string__2_19 = from_latin_1_string("C_FUNCTION", 10);
  string__2_20 = from_latin_1_string("typedef struct {\012  const char *name;\012  void **func;\012  const char *module_name;\012} C_FUNCTION;\012", 93);
  string__2_22 = from_latin_1_string("runtime_major_version", 21);
  string__2_23 = from_latin_1_string("int runtime_major_version(void);\012", 33);
  string__2_25 = from_latin_1_string("runtime_minor_version", 21);
  string__2_26 = from_latin_1_string("int runtime_minor_version(void);\012", 33);
  string__2_28 = from_latin_1_string("runtime_revision", 16);
  string__2_29 = from_latin_1_string("int runtime_revision(void);\012", 28);
  string__2_31 = from_latin_1_string("polymorphic_function_count", 26);
  string__2_32 = from_latin_1_string("int polymorphic_function_count;\012", 32);
  string__2_34 = from_latin_1_string("polymorphic_function_with_setter_count", 38);
  string__2_35 = from_latin_1_string("int polymorphic_function_with_setter_count;\012", 44);
  string__2_37 = from_latin_1_string("polymorphic_function_names", 26);
  string__2_38 = from_latin_1_string("const char **polymorphic_function_names;\012", 41);
  string__2_40 = from_latin_1_string("set_module", 10);
  string__2_41 = from_latin_1_string("void set_module(const char *name);\012", 35);
  string__2_43 = from_latin_1_string("register_module_info", 20);
  string__2_44 = from_latin_1_string("void register_module_info(MODULE_INFO *info);\012", 46);
  string__2_46 = from_latin_1_string("set_used_namespaces", 19);
  string__2_47 = from_latin_1_string("void set_used_namespaces(const char **namespaces);\012", 51);
  string__2_49 = from_latin_1_string("from_bool", 9);
  string__2_50 = from_latin_1_string("NODE *from_bool(int val);\012", 26);
  string__2_52 = from_latin_1_string("from_int", 8);
  string__2_53 = from_latin_1_string("NODE *from_int(int val);\012", 25);
  string__2_55 = from_latin_1_string("from_long", 9);
  string__2_56 = from_latin_1_string("NODE *from_long(long val);\012", 27);
  string__2_58 = from_latin_1_string("from_int64", 10);
  string__2_59 = from_latin_1_string("NODE *from_int64(int64_t val);\012", 31);
  string__2_61 = from_latin_1_string("from_uint32", 11);
  string__2_62 = from_latin_1_string("NODE *from_uint32(uint32_t val);\012", 33);
  string__2_64 = from_latin_1_string("from_uint64", 11);
  string__2_65 = from_latin_1_string("NODE *from_uint64(uint64_t val);\012", 33);
  string__2_67 = from_latin_1_string("from_double", 11);
  string__2_68 = from_latin_1_string("NODE *from_double(double val);\012", 31);
  string__2_70 = from_latin_1_string("from_digit_string", 17);
  string__2_71 = from_latin_1_string("NODE *from_digit_string(const char *str);\012", 42);
  string__2_73 = from_latin_1_string("from_uchar32", 12);
  string__2_74 = from_latin_1_string("NODE *from_uchar32(unsigned int chr);\012", 38);
  string__2_76 = from_latin_1_string("from_c_string", 13);
  string__2_77 = from_latin_1_string("NODE *from_c_string(const char *str);\012", 38);
  string__2_79 = from_latin_1_string("from_latin_1_string", 19);
  string__2_80 = from_latin_1_string("NODE *from_latin_1_string(const char *str, long len);\012", 54);
  string__2_82 = from_latin_1_string("from_uint32_string", 18);
  string__2_83 = from_latin_1_string("NODE *from_uint32_string(const uint32_t *str, long len);\012", 57);
  string__2_85 = from_latin_1_string("from_arguments", 14);
  string__2_86 = from_latin_1_string("NODE *from_arguments(int first_idx, int count);\012", 48);
  string__2_88 = from_latin_1_string("register_unique_item", 20);
  string__2_89 = from_latin_1_string("NODE *register_unique_item(const char *name);\012", 46);
  string__2_91 = from_latin_1_string("define_c_function", 17);
  string__2_92 = from_latin_1_string("void define_c_function(const char *name, void *func);\012", 54);
  string__2_94 = from_latin_1_string("register_polymorphic_function", 29);
  string__2_95 = from_latin_1_string("void register_polymorphic_function(const char *name, int *id_p);\012", 65);
  string__2_97 = from_latin_1_string("register_polymorphic_function_with_setter", 41);
  string__2_98 = from_latin_1_string("void register_polymorphic_function_with_setter(const char *name, int *id_p);\012", 77);
  string__2_100 = from_latin_1_string("define_polymorphic_function", 27);
  string__2_101 = from_latin_1_string("void define_polymorphic_function(\012  const char *namespace, const char *name, NODE_GETTER getter, int *id_p,\012  NODE **var_p\012);\012", 126);
  string__2_103 = from_latin_1_string("define_polymorphic_function_with_setter", 39);
  string__2_104 = from_latin_1_string("void define_polymorphic_function_with_setter(\012  const char *namespace, const char *name, NODE_GETTER getter, int *id_p,\012  NODE **var_p\012);\012", 138);
  string__2_106 = from_latin_1_string("define_privileged_polymorphic_function", 38);
  string__2_107 = from_latin_1_string("void define_privileged_polymorphic_function(\012  const char *namespace, const char *name, NODE_GETTER getter, int id,\012  NODE **var_p\012);\012", 134);
  string__2_109 = from_latin_1_string("define_single_assign_static", 27);
  string__2_110 = from_latin_1_string("void define_single_assign_static(\012  const char *namespace, const char *name,\012  NODE_GETTER getter, NODE **var_p\012);\012", 115);
  string__2_112 = from_latin_1_string("define_multi_assign_static", 26);
  string__2_113 = from_latin_1_string("void define_multi_assign_static(\012  const char *namespace, const char *name,\012  NODE_GETTER getter, NODE_SETTER setter\012);\012", 120);
  string__2_115 = from_latin_1_string("register_dynamic", 16);
  string__2_116 = from_latin_1_string("void register_dynamic(int *id_p);\012", 34);
  string__2_118 = from_latin_1_string("define_single_assign_dynamic", 28);
  string__2_119 = from_latin_1_string("void define_single_assign_dynamic(\012  const char *namespace, const char *name,\012  NODE_GETTER getter, NODE_SETTER definer,\012  int *id_p\012);\012", 136);
  string__2_121 = from_latin_1_string("define_multi_assign_dynamic", 27);
  string__2_122 = from_latin_1_string("void define_multi_assign_dynamic(\012  const char *namespace, const char *name,\012  NODE_GETTER getter, NODE_SETTER setter, NODE_SETTER definer,\012  int *id_p\012);\012", 155);
  string__2_124 = from_latin_1_string("define_type_function", 20);
  string__2_125 = from_latin_1_string("void define_type_function(\012  const char *namespace, const char *name, FUNC type, int par_cnt\012);\012", 96);
  string__2_127 = from_latin_1_string("define_attribute", 16);
  string__2_128 = from_latin_1_string("void define_attribute(\012  const char *namespace, const char *name,\012  int id, NODE *attribute\012);\012", 95);
  string__2_130 = from_latin_1_string("define_method", 13);
  string__2_131 = from_latin_1_string("void define_method(\012  const char *namespace, const char *name,\012  int id, NODE *method\012);\012", 89);
  string__2_133 = from_latin_1_string("use_polymorphic_function", 24);
  string__2_134 = from_latin_1_string("void use_polymorphic_function(\012  const char *namespace, const char *name, NODE_GETTER *getter, int *id\012);\012", 106);
  string__2_136 = from_latin_1_string("use_read_only", 13);
  string__2_137 = from_latin_1_string("void use_read_only(\012  const char *namespace, const char *name,\012  NODE_GETTER *getter, NODE_GETTER *get_value_or_future\012);\012", 122);
  string__2_139 = from_latin_1_string("use_read_write", 14);
  string__2_140 = from_latin_1_string("void use_read_write(\012  const char *namespace, const char *name,\012  NODE_GETTER *getter, NODE_SETTER *setter\012);\012", 110);
  string__2_142 = from_latin_1_string("use_single_assign_dynamic", 25);
  string__2_143 = from_latin_1_string("void use_single_assign_dynamic(\012  const char *namespace, const char *name,\012  NODE_GETTER *getter, NODE_SETTER *definer\012);\012", 122);
  string__2_145 = from_latin_1_string("use_multi_assign_dynamic", 24);
  string__2_146 = from_latin_1_string("void use_multi_assign_dynamic(\012  const char *namespace, const char *name,\012  NODE_GETTER *getter, NODE_SETTER *setter, NODE_SETTER *definer\012);\012", 142);
  string__2_148 = from_latin_1_string("resolve_symbols", 15);
  string__2_149 = from_latin_1_string("void resolve_symbols(void);\012", 28);
  string__2_151 = from_latin_1_string("resolve_attributes", 18);
  string__2_152 = from_latin_1_string("void resolve_attributes(void);\012", 31);
  string__2_154 = from_latin_1_string("NODE", 4);
  string__2_155 = from_latin_1_string("typedef union NODE NODE;\012", 25);
  string__2_157 = from_latin_1_string("FUNC", 4);
  string__2_158 = from_latin_1_string("typedef void (*FUNC)(void);\012", 28);
  string__2_160 = from_latin_1_string("NODE_GETTER", 11);
  string__2_161 = from_latin_1_string("typedef NODE *(*NODE_GETTER)(void);\012", 36);
  string__2_163 = from_latin_1_string("NODE_SETTER", 11);
  string__2_164 = from_latin_1_string("typedef void (*NODE_SETTER)(NODE *);\012", 37);
  string__2_166 = from_latin_1_string("COLLECTOR", 9);
  string__2_167 = from_latin_1_string("typedef void *COLLECTOR(void *);\012", 33);
  string__2_169 = from_latin_1_string("DESTRUCTOR", 10);
  string__2_170 = from_latin_1_string("typedef void (*DESTRUCTOR)(void *);\012", 36);
  string__2_172 = from_latin_1_string("VTABLE", 6);
  string__2_173 = from_latin_1_string("typedef struct VTABLE {\012  size_t size;\012  COLLECTOR *collect;\012  int8_t (*to_int8)(NODE *);\012  int16_t (*to_int16)(NODE *);\012  int32_t (*to_int32)(NODE *);\012  int64_t (*to_int64)(NODE *);\012  uint8_t (*to_uint8)(NODE *);\012  uint16_t (*to_uint16)(NODE *);\012  uint32_t (*to_uint32)(NODE *);\012  uint64_t (*to_uint64)(NODE *);\012  uint32_t (*to_uchar32)(NODE *);\012  int (*to_bool)(NODE *);\012  int (*to_int)(NODE *);\012  long (*to_long)(NODE *);\012  double (*to_double)(NODE *);\012  char *(*to_c_string)(NODE *);\012  uint8_t *(*to_octets)(NODE *, long *size_p);\012  NODE *(*get_item_of)(NODE *, long idx);\012  long (*length_of)(NODE *);\012  void (*unfold)(NODE *);\012  long (*debug_string)(NODE *, int indent, int max_depth, char *buf);\012} VTABLE;\012", 712);
  string__2_175 = from_latin_1_string("OCTREE", 6);
  string__2_176 = from_latin_1_string("typedef struct OCTREE {\012  struct OCTREE *nodes[8];\012} OCTREE;\012", 61);
  string__2_178 = from_latin_1_string("ATTRIBUTES", 10);
  string__2_179 = from_latin_1_string("typedef struct ATTRIBUTES {\012  struct VTABLE *vtable;\012  struct OCTREE *nodes[7];\012} ATTRIBUTES;\012", 94);
  string__2_181 = from_latin_1_string("DYNAMICS", 8);
  string__2_182 = from_latin_1_string("typedef struct DYNAMICS {\012  struct OCTREE *nodes[8];\012} DYNAMICS;\012", 65);
  string__2_184 = from_latin_1_string("SIMPLE_NODE", 11);
  string__2_185 = from_latin_1_string("typedef struct SIMPLE_NODE {\012  FUNC type;\012  struct ATTRIBUTES *attributes;\012} SIMPLE_NODE;\012", 90);
  string__2_187 = from_latin_1_string("CLOSURE", 7);
  string__2_188 = from_latin_1_string("typedef struct CLOSURE {\012  FUNC type;\012  struct ATTRIBUTES *attributes;\012  int parameter_count;\012  struct FRAME *frame;\012} CLOSURE;\012", 128);
  string__2_190 = from_latin_1_string("FUNCTION", 8);
  string__2_191 = from_latin_1_string("typedef struct FUNCTION {\012  FUNC type;\012  struct ATTRIBUTES *attributes;\012  int parameter_count;\012} FUNCTION;\012", 107);
  string__2_193 = from_latin_1_string("CONTINUATION", 12);
  string__2_194 = from_latin_1_string("typedef struct CONTINUATION {\012  FUNC type;\012  struct ATTRIBUTES *attributes;\012  int result_count;\012  struct FRAME *frame;\012  struct DYNAMICS *dynamics;\012  struct FRAME *exit_frame; // used by exit-functions\012} CONTINUATION;\012", 218);
  string__2_196 = from_latin_1_string("ATTRIBUTE_LIST", 14);
  string__2_197 = from_latin_1_string("typedef struct ATTRIBUTE_LIST {\012  struct ATTRIBUTE_LIST *link;\012  int idx;\012  void *attr;\012} ATTRIBUTE_LIST;\012", 106);
  string__2_199 = from_latin_1_string("FUTURE", 6);
  string__2_200 = from_latin_1_string("typedef struct FUTURE {\012  FUNC type;\012  struct ATTRIBUTES *attributes;\012  NODE *link;\012  struct ATTRIBUTE_LIST *pending_attributes;\012  NODE *dependent_futures;\012  NODE *prototype;\012  long is_already_initialized;\012  NODE *pad_2;\012} FUTURE;\012", 231);
  string__2_202 = from_latin_1_string("CELL", 4);
  string__2_203 = from_latin_1_string("typedef struct CELL {\012  FUNC type;\012  struct ATTRIBUTES *attributes;\012  NODE *contents;\012} CELL;\012", 94);
  string__2_205 = from_latin_1_string("FRAME", 5);
  string__2_206 = from_latin_1_string("typedef struct FRAME {\012  FUNC cont;\012  struct FRAME *caller_frame;\012  long caller_result_count;\012  long slot_count;\012  NODE *slots[0];\012} FRAME;\012", 140);
  string__2_208 = from_latin_1_string("FRAME_INFO", 10);
  string__2_209 = from_latin_1_string("typedef struct FRAME_INFO {\012  int var_count;\012  const char *var_names[];\012} FRAME_INFO;\012", 86);
  string__2_211 = from_latin_1_string("CONTINUATION_INFO", 17);
  string__2_212 = from_latin_1_string("typedef struct CONTINUATION_INFO {\012  FUNC continuation;\012  struct FRAME_INFO *frame_info;\012  uint16_t first_line;\012  uint16_t last_line;\012  uint8_t first_column;\012  uint8_t last_column;\012  uint8_t submodule_index;\012  uint8_t unused;\012} CONTINUATION_INFO;\012", 247);
  string__2_214 = from_latin_1_string("MODULE_INFO", 11);
  string__2_215 = from_latin_1_string("typedef struct MODULE_INFO {\012  struct MODULE_INFO *link;\012  const char *name;\012  struct CONTINUATION_INFO *continuation_info;\012  int continuation_count;\012  NODE **var_tab;\012  const char **var_names;\012  int top_level_count;\012  const char **used_namespaces;\012  const char *filenames[];\012} MODULE_INFO;\012", 291);
  string__2_217 = from_latin_1_string("EVENT__MODE", 11);
  string__2_218 = from_latin_1_string("typedef enum {\012  EM__NORMAL,\012  EM__RECORD,\012  EM__REPLAY\012} EVENT__MODE;\012", 71);
  string__2_220 = from_latin_1_string("MEMORY_BLOCK", 12);
  string__2_221 = from_latin_1_string("typedef struct MEMORY_BLOCK {\012  struct MEMORY_BLOCK *link;\012  long mark;\012  DESTRUCTOR destructor;\012} MEMORY_BLOCK;\012", 113);
  string__2_223 = from_latin_1_string("PHASE_2_COLLECTOR", 17);
  string__2_224 = from_latin_1_string("typedef struct PHASE_2_COLLECTOR {\012  void *dummy;\012  void *next_collector;\012  void (*collector)(void *data);\012} PHASE_2_COLLECTOR;\012", 128);
  string__2_226 = from_latin_1_string("argument_count", 14);
  string__2_227 = from_latin_1_string("REGISTER int argument_count ASM(\042ebx\042);\012", 40);
  string__2_229 = from_latin_1_string("arguments", 9);
  string__2_230 = from_latin_1_string("REGISTER FRAME *arguments ASM(\042r12\042);\012", 38);
  string__2_232 = from_latin_1_string("myself", 6);
  string__2_233 = from_latin_1_string("REGISTER NODE *myself ASM(\042r13\042);\012", 34);
  string__2_235 = from_latin_1_string("func", 4);
  string__2_236 = from_latin_1_string("REGISTER FUNC func ASM(\042r14\042);\012", 31);
  string__2_238 = from_latin_1_string("frame", 5);
  string__2_239 = from_latin_1_string("REGISTER FRAME *frame ASM(\042r15\042);\012", 34);
  string__2_241 = from_latin_1_string("result_count", 12);
  string__2_242 = from_latin_1_string("int result_count;\012", 18);
  string__2_244 = from_latin_1_string("dynamics", 8);
  string__2_245 = from_latin_1_string("DYNAMICS *dynamics;\012", 20);
  string__2_247 = from_latin_1_string("main_argc", 9);
  string__2_248 = from_latin_1_string("int main_argc;\012", 15);
  string__2_250 = from_latin_1_string("main_argv", 9);
  string__2_251 = from_latin_1_string("char **main_argv;\012", 18);
  string__2_253 = from_latin_1_string("event__mode", 11);
  string__2_254 = from_latin_1_string("EVENT__MODE event__mode;\012", 25);
  string__2_256 = from_latin_1_string("node_p", 6);
  string__2_257 = from_latin_1_string("void *node_p;\012", 14);
  string__2_259 = from_latin_1_string("update_start_p", 14);
  string__2_260 = from_latin_1_string("void *update_start_p;\012", 22);
  string__2_262 = from_latin_1_string("coll_node_buf", 13);
  string__2_263 = from_latin_1_string("void *coll_node_buf;\012", 21);
  string__2_265 = from_latin_1_string("coll_node_buf_end", 17);
  string__2_266 = from_latin_1_string("void *coll_node_buf_end;\012", 25);
  string__2_268 = from_latin_1_string("undefined", 9);
  string__2_269 = from_latin_1_string("NODE *undefined;\012", 17);
  string__2_271 = from_latin_1_string("zero", 4);
  string__2_272 = from_latin_1_string("NODE *zero;\012", 12);
  string__2_274 = from_latin_1_string("boolean_true", 12);
  string__2_275 = from_latin_1_string("NODE *boolean_true;\012", 20);
  string__2_277 = from_latin_1_string("boolean_false", 13);
  string__2_278 = from_latin_1_string("NODE *boolean_false;\012", 21);
  string__2_280 = from_latin_1_string("empty_string", 12);
  string__2_281 = from_latin_1_string("NODE *empty_string;\012", 20);
  string__2_283 = from_latin_1_string("raise_exception_getter", 22);
  string__2_284 = from_latin_1_string("NODE_GETTER raise_exception_getter;\012", 36);
  string__2_286 = from_latin_1_string("instruction_counter", 19);
  string__2_287 = from_latin_1_string("uint64_t instruction_counter;\012", 30);
  string__2_289 = from_latin_1_string("no_attributes_level_1", 21);
  string__2_290 = from_latin_1_string("OCTREE no_attributes_level_1;\012", 30);
  string__2_292 = from_latin_1_string("no_attributes_level_2", 21);
  string__2_293 = from_latin_1_string("OCTREE no_attributes_level_2;\012", 30);
  string__2_295 = from_latin_1_string("no_attributes_level_3", 21);
  string__2_296 = from_latin_1_string("OCTREE no_attributes_level_3;\012", 30);
  string__2_298 = from_latin_1_string("no_attributes_level_4", 21);
  string__2_299 = from_latin_1_string("OCTREE no_attributes_level_4;\012", 30);
  string__2_301 = from_latin_1_string("no_attributes_level_5", 21);
  string__2_302 = from_latin_1_string("OCTREE no_attributes_level_5;\012", 30);
  string__2_304 = from_latin_1_string("no_attributes_level_6", 21);
  string__2_305 = from_latin_1_string("OCTREE no_attributes_level_6;\012", 30);
  string__2_307 = from_latin_1_string("no_attributes_level_7", 21);
  string__2_308 = from_latin_1_string("OCTREE no_attributes_level_7;\012", 30);
  string__2_310 = from_latin_1_string("no_attributes_level_8", 21);
  string__2_311 = from_latin_1_string("OCTREE no_attributes_level_8;\012", 30);
  string__2_313 = from_latin_1_string("undefined_attributes_level_1", 28);
  string__2_314 = from_latin_1_string("OCTREE undefined_attributes_level_1;\012", 37);
  string__2_316 = from_latin_1_string("undefined_attributes_level_2", 28);
  string__2_317 = from_latin_1_string("OCTREE undefined_attributes_level_2;\012", 37);
  string__2_319 = from_latin_1_string("undefined_attributes_level_3", 28);
  string__2_320 = from_latin_1_string("OCTREE undefined_attributes_level_3;\012", 37);
  string__2_322 = from_latin_1_string("undefined_attributes_level_4", 28);
  string__2_323 = from_latin_1_string("OCTREE undefined_attributes_level_4;\012", 37);
  string__2_325 = from_latin_1_string("undefined_attributes_level_5", 28);
  string__2_326 = from_latin_1_string("OCTREE undefined_attributes_level_5;\012", 37);
  string__2_328 = from_latin_1_string("undefined_attributes_level_6", 28);
  string__2_329 = from_latin_1_string("OCTREE undefined_attributes_level_6;\012", 37);
  string__2_331 = from_latin_1_string("undefined_attributes_level_7", 28);
  string__2_332 = from_latin_1_string("OCTREE undefined_attributes_level_7;\012", 37);
  string__2_334 = from_latin_1_string("undefined_attributes_level_8", 28);
  string__2_335 = from_latin_1_string("OCTREE undefined_attributes_level_8;\012", 37);
  string__2_337 = from_latin_1_string("runtime_debug_level", 19);
  string__2_338 = from_latin_1_string("int runtime_debug_level;\012", 25);
  string__2_340 = from_latin_1_string("unrecoverable_error", 19);
  string__2_341 = from_latin_1_string("__attribute__ ((noreturn)) void unrecoverable_error(const char *msg, ...);\012", 75);
  string__2_343 = from_latin_1_string("out_of_memory_error", 19);
  string__2_344 = from_latin_1_string("__attribute__ ((noreturn)) void out_of_memory_error(void);\012", 59);
  string__2_346 = from_latin_1_string("invalid_continuation_error", 26);
  string__2_347 = from_latin_1_string("__attribute__ ((noreturn)) void invalid_continuation_error(void);\012", 66);
  string__2_349 = from_latin_1_string("allocate", 8);
  string__2_350 = from_latin_1_string("void *allocate(long size);\012", 27);
  string__2_352 = from_latin_1_string("allocate_and_clear", 18);
  string__2_353 = from_latin_1_string("void *allocate_and_clear(long size);\012", 37);
  string__2_355 = from_latin_1_string("allocate_memory", 15);
  string__2_356 = from_latin_1_string("void *allocate_memory(size_t size);\012", 36);
  string__2_358 = from_latin_1_string("reallocate_memory", 17);
  string__2_359 = from_latin_1_string("void *reallocate_memory(void * buf, size_t size);\012", 50);
  string__2_361 = from_latin_1_string("allocate_gc", 11);
  string__2_362 = from_latin_1_string("void *allocate_gc(long size);\012", 30);
  string__2_364 = from_latin_1_string("allocate_arguments", 18);
  string__2_365 = from_latin_1_string("void allocate_arguments(void);\012", 31);
  string__2_367 = from_latin_1_string("allocate_fixed", 14);
  string__2_368 = from_latin_1_string("void *allocate_fixed(long size);\012", 33);
  string__2_370 = from_latin_1_string("allocate_fixed_with_destructor", 30);
  string__2_371 = from_latin_1_string("void *allocate_fixed_with_destructor(long size, DESTRUCTOR destructor);\012", 72);
  string__2_373 = from_latin_1_string("allocate_initialized_frame_gc", 29);
  string__2_374 = from_latin_1_string("void allocate_initialized_frame_gc(int slot_idx, int slot_count);\012", 66);
  string__2_376 = from_latin_1_string("allocate_large", 14);
  string__2_377 = from_latin_1_string("void *allocate_large(long size);\012", 33);
  string__2_379 = from_latin_1_string("deallocate_memory", 17);
  string__2_380 = from_latin_1_string("void deallocate_memory(void *buf);\012", 35);
  string__2_382 = from_latin_1_string("copy", 4);
  string__2_383 = from_latin_1_string("void *copy(const void *buf, long size);\012", 40);
  string__2_385 = from_latin_1_string("register_phase_2_collector", 26);
  string__2_386 = from_latin_1_string("void register_phase_2_collector(void *data);\012", 45);
  string__2_388 = from_latin_1_string("child_changed_state", 19);
  string__2_389 = from_latin_1_string("int child_changed_state;\012", 25);
  string__2_391 = from_latin_1_string("window_changed_size", 19);
  string__2_392 = from_latin_1_string("int window_changed_size;\012", 25);
  string__2_394 = from_latin_1_string("from_printf", 11);
  string__2_395 = from_latin_1_string("NODE *from_printf(const char *msg, ...);\012", 41);
  string__2_397 = from_latin_1_string("runtime_error", 13);
  string__2_398 = from_latin_1_string("__attribute__ ((noreturn)) void runtime_error(const char *msg, ...);\012", 69);
  string__2_400 = from_latin_1_string("too_few_arguments_error", 23);
  string__2_401 = from_latin_1_string("void too_few_arguments_error(void);\012", 36);
  string__2_403 = from_latin_1_string("too_many_arguments_error", 24);
  string__2_404 = from_latin_1_string("void too_many_arguments_error(void);\012", 37);
  string__2_406 = from_latin_1_string("invalid_arguments_error", 23);
  string__2_407 = from_latin_1_string("void invalid_arguments_error(void);\012", 36);
  string__2_409 = from_latin_1_string("too_few_results_error", 21);
  string__2_410 = from_latin_1_string("void too_few_results_error(void);\012", 34);
  string__2_412 = from_latin_1_string("too_many_results_error", 22);
  string__2_413 = from_latin_1_string("void too_many_results_error(void);\012", 35);
  string__2_415 = from_latin_1_string("invalid_results_error", 21);
  string__2_416 = from_latin_1_string("void invalid_results_error(void);\012", 34);
  string__2_418 = from_latin_1_string("invalid_index_error", 19);
  string__2_419 = from_latin_1_string("void invalid_index_error(void);\012", 32);
  string__2_421 = from_latin_1_string("divide_by_zero_error", 20);
  string__2_422 = from_latin_1_string("void divide_by_zero_error(void);\012", 33);
  string__2_424 = from_latin_1_string("not_yet_implemented_error", 25);
  string__2_425 = from_latin_1_string("void not_yet_implemented_error(void);\012", 38);
  string__2_427 = from_latin_1_string("no_such_function", 16);
  string__2_428 = from_latin_1_string("void no_such_function(void);\012", 29);
  string__2_430 = from_latin_1_string("no_such_attribute", 17);
  string__2_431 = from_latin_1_string("void no_such_attribute(void);\012", 30);
  string__2_433 = from_latin_1_string("resource_error", 14);
  string__2_434 = from_latin_1_string("void resource_error(void);\012", 27);
  string__2_436 = from_latin_1_string("io_error", 8);
  string__2_437 = from_latin_1_string("void io_error(void);\012", 21);
  string__2_439 = from_latin_1_string("initialize_runtime", 18);
  string__2_440 = from_latin_1_string("void initialize_runtime(void);\012", 31);
  string__2_442 = from_latin_1_string("initialize_phase_3", 18);
  string__2_443 = from_latin_1_string("void initialize_phase_3(void);\012", 31);
  string__2_445 = from_latin_1_string("current_mark", 12);
  string__2_446 = from_latin_1_string("long current_mark;\012", 19);
  string__2_448 = from_latin_1_string("join_nodes", 10);
  string__2_449 = from_latin_1_string("void join_nodes(void *left_node_pp, void *right_node_pp);\012", 58);
  string__2_451 = from_latin_1_string("clone_object_and_attributes", 27);
  string__2_452 = from_latin_1_string("NODE *clone_object_and_attributes(NODE *node);\012", 47);
  string__2_454 = from_latin_1_string("register_collector", 18);
  string__2_455 = from_latin_1_string("void register_collector(FUNC collector);\012", 41);
  string__2_457 = from_latin_1_string("collect_node", 12);
  string__2_458 = from_latin_1_string("NODE *collect_node(NODE *node);\012", 32);
  string__2_460 = from_latin_1_string("collect_static_attributes", 25);
  string__2_461 = from_latin_1_string("void collect_static_attributes(ATTRIBUTES *attributes);\012", 56);
  string__2_463 = from_latin_1_string("collect_attributes", 18);
  string__2_464 = from_latin_1_string("ATTRIBUTES *collect_attributes(ATTRIBUTES *attributes);\012", 56);
  string__2_466 = from_latin_1_string("collect_simple_node", 19);
  string__2_467 = from_latin_1_string("void *collect_simple_node(SIMPLE_NODE *node);\012", 46);
  string__2_469 = from_latin_1_string("total_garbage_collections", 25);
  string__2_470 = from_latin_1_string("int total_garbage_collections;\012", 31);
  string__2_472 = from_latin_1_string("collect_garbage", 15);
  string__2_473 = from_latin_1_string("void collect_garbage();\012", 24);
  string__2_475 = from_latin_1_string("indent_to_string", 16);
  string__2_476 = from_latin_1_string("const char *indent_to_string(int indent);\012", 42);
  string__2_478 = from_latin_1_string("print", 5);
  string__2_479 = from_latin_1_string("int print(char **buf_p, const char *format, ...);\012", 50);
  string__2_481 = from_latin_1_string("debug_print", 11);
  string__2_482 = from_latin_1_string("int debug_print(int indent, char *buf, const char *format, ...);\012", 65);
  string__2_484 = from_latin_1_string("debug_print_head", 16);
  string__2_485 = from_latin_1_string("int debug_print_head(int *indent_p, char **buf_p, const char *format, ...);\012", 76);
  string__2_487 = from_latin_1_string("to_int8", 7);
  string__2_488 = from_latin_1_string("uint32_t to_int8(NODE *node);\012", 30);
  string__2_490 = from_latin_1_string("to_int16", 8);
  string__2_491 = from_latin_1_string("uint64_t to_int16(NODE *node);\012", 31);
  string__2_493 = from_latin_1_string("to_int32", 8);
  string__2_494 = from_latin_1_string("uint32_t to_int32(NODE *node);\012", 31);
  string__2_496 = from_latin_1_string("to_int64", 8);
  string__2_497 = from_latin_1_string("uint64_t to_int64(NODE *node);\012", 31);
  string__2_499 = from_latin_1_string("to_uint8", 8);
  string__2_500 = from_latin_1_string("uint32_t to_uint8(NODE *node);\012", 31);
  string__2_502 = from_latin_1_string("to_uint16", 9);
  string__2_503 = from_latin_1_string("uint64_t to_uint16(NODE *node);\012", 32);
  string__2_505 = from_latin_1_string("to_uint32", 9);
  string__2_506 = from_latin_1_string("uint32_t to_uint32(NODE *node);\012", 32);
  string__2_508 = from_latin_1_string("to_uint64", 9);
  string__2_509 = from_latin_1_string("uint64_t to_uint64(NODE *node);\012", 32);
  string__2_511 = from_latin_1_string("to_uchar32", 10);
  string__2_512 = from_latin_1_string("uint32_t to_uchar32(NODE *node);\012", 33);
  string__2_514 = from_latin_1_string("to_bool", 7);
  string__2_515 = from_latin_1_string("int to_bool(NODE *node);\012", 25);
  string__2_517 = from_latin_1_string("to_int", 6);
  string__2_518 = from_latin_1_string("int to_int(NODE *node);\012", 24);
  string__2_520 = from_latin_1_string("to_long", 7);
  string__2_521 = from_latin_1_string("long to_long(NODE *node);\012", 26);
  string__2_523 = from_latin_1_string("to_double", 9);
  string__2_524 = from_latin_1_string("double to_double(NODE *node);\012", 30);
  string__2_526 = from_latin_1_string("to_c_string", 11);
  string__2_527 = from_latin_1_string("char *to_c_string(NODE *node);\012", 31);
  string__2_529 = from_latin_1_string("to_octets", 9);
  string__2_530 = from_latin_1_string("uint8_t *to_octets(NODE *node, long *size_p);\012", 46);
  string__2_532 = from_latin_1_string("get_item_of", 11);
  string__2_533 = from_latin_1_string("NODE *get_item_of(NODE *node, long idx);\012", 41);
  string__2_535 = from_latin_1_string("length_of", 9);
  string__2_536 = from_latin_1_string("long length_of(NODE *node);\012", 28);
  string__2_538 = from_latin_1_string("unfold", 6);
  string__2_539 = from_latin_1_string("void unfold(NODE *node);\012", 25);
  string__2_541 = from_latin_1_string("debug_string", 12);
  string__2_542 = from_latin_1_string("long debug_string(NODE *node, int indent, int max_depth, char *buf);\012", 69);
  string__2_544 = from_latin_1_string("optional_item", 13);
  string__2_545 = from_latin_1_string("void optional_item(NODE *item);\012", 32);
  string__2_547 = from_latin_1_string("get_attribute", 13);
  string__2_548 = from_latin_1_string("NODE *get_attribute(NODE *node, int idx);\012", 42);
  string__2_550 = from_latin_1_string("polymorph_dispatch", 18);
  string__2_551 = from_latin_1_string("void polymorph_dispatch(int idx);\012", 34);
  string__2_553 = from_latin_1_string("set_attribute", 13);
  string__2_554 = from_latin_1_string("void set_attribute(ATTRIBUTES *attributes, int idx, void *attr);\012", 65);
  string__2_556 = from_latin_1_string("set_attribute_value", 19);
  string__2_557 = from_latin_1_string("void set_attribute_value(ATTRIBUTES *attributes, int idx, void *attr);\012", 71);
  string__2_559 = from_latin_1_string("record__event", 13);
  string__2_560 = from_latin_1_string("void record__event(const char *name);\012", 38);
  string__2_562 = from_latin_1_string("successful__action", 18);
  string__2_563 = from_latin_1_string("void successful__action(const char *name);\012", 43);
  string__2_565 = from_latin_1_string("failed__action", 14);
  string__2_566 = from_latin_1_string("void failed__action(const char *name);\012", 39);
  string__2_568 = from_latin_1_string("replay__event", 13);
  string__2_569 = from_latin_1_string("void replay__event(const char *name);\012", 38);
  string__2_571 = from_latin_1_string("replay__action", 14);
  string__2_572 = from_latin_1_string("int replay__action(const char *name);\012", 38);
  string__2_574 = from_latin_1_string("report__event", 13);
  string__2_575 = from_latin_1_string("void report__event(const char *name);\012", 38);
  string__2_577 = from_latin_1_string("print__pointer", 14);
  string__2_578 = from_latin_1_string("void print__pointer(void *ptr);\012", 32);
  string__2_580 = from_latin_1_string("store__pointer", 14);
  string__2_581 = from_latin_1_string("void store__pointer(void *ptr);\012", 32);
  string__2_583 = from_latin_1_string("retrieve__pointer", 17);
  string__2_584 = from_latin_1_string("void retrieve__pointer(void **ptr_p);\012", 38);
  string__2_586 = from_latin_1_string("print__integer", 14);
  string__2_587 = from_latin_1_string("void print__integer(int val);\012", 30);
  string__2_589 = from_latin_1_string("store__integer", 14);
  string__2_590 = from_latin_1_string("void store__integer(int val);\012", 30);
  string__2_592 = from_latin_1_string("retrieve__integer", 17);
  string__2_593 = from_latin_1_string("void retrieve__integer(int *val_p);\012", 36);
  string__2_595 = from_latin_1_string("print__long_integer", 19);
  string__2_596 = from_latin_1_string("void print__long_integer(long val);\012", 36);
  string__2_598 = from_latin_1_string("store__long_integer", 19);
  string__2_599 = from_latin_1_string("void store__long_integer(long val);\012", 36);
  string__2_601 = from_latin_1_string("retrieve__long_integer", 22);
  string__2_602 = from_latin_1_string("void retrieve__long_integer(long *val_p);\012", 42);
  string__2_604 = from_latin_1_string("print__int_array", 16);
  string__2_605 = from_latin_1_string("void print__int_array(const int *buf, long len);\012", 49);
  string__2_607 = from_latin_1_string("store__int_array", 16);
  string__2_608 = from_latin_1_string("void store__int_array(const int *buf, long len);\012", 49);
  string__2_610 = from_latin_1_string("retrieve__int_array", 19);
  string__2_611 = from_latin_1_string("long retrieve__int_array(int **buf_p);\012", 39);
  string__2_613 = from_latin_1_string("print__memory", 13);
  string__2_614 = from_latin_1_string("void print__memory(const uint8_t *buf, long len);\012", 50);
  string__2_616 = from_latin_1_string("store__memory", 13);
  string__2_617 = from_latin_1_string("void store__memory(const uint8_t *buf, long len);\012", 50);
  string__2_619 = from_latin_1_string("retrieve__memory", 16);
  string__2_620 = from_latin_1_string("long retrieve__memory(uint8_t **buf_p);\012", 40);
  string__2_622 = from_latin_1_string("print__c_string", 15);
  string__2_623 = from_latin_1_string("void print__c_string(const char *buf);\012", 39);
  string__2_625 = from_latin_1_string("store__c_string", 15);
  string__2_626 = from_latin_1_string("void store__c_string(const char *buf);\012", 39);
  string__2_628 = from_latin_1_string("retrieve__c_string", 18);
  string__2_629 = from_latin_1_string("void retrieve__c_string(char **buf_p);\012", 39);
  string__2_631 = from_latin_1_string("create_function", 15);
  string__2_632 = from_latin_1_string("NODE *create_function(FUNC func, int par_count);\012", 49);
  string__2_634 = from_latin_1_string("create_closure", 14);
  string__2_635 = from_latin_1_string("NODE *create_closure(FUNC type, int par_count);\012", 48);
  string__2_637 = from_latin_1_string("continuation_type_function", 26);
  string__2_638 = from_latin_1_string("void continuation_type_function(void);\012", 39);
  string__2_640 = from_latin_1_string("continuation_trampoline", 23);
  string__2_641 = from_latin_1_string("void continuation_trampoline(void);\012", 36);
  string__2_643 = from_latin_1_string("create_continuation", 19);
  string__2_644 = from_latin_1_string("NODE *create_continuation(void);\012", 33);
  string__2_646 = from_latin_1_string("create_continuation_with_exit", 29);
  string__2_647 = from_latin_1_string("NODE *create_continuation_with_exit(FUNC exit_func);\012", 53);
  string__2_649 = from_latin_1_string("initialize_function_attributes", 30);
  string__2_650 = from_latin_1_string("void initialize_function_attributes(void);\012", 43);
  string__2_652 = from_latin_1_string("create_future", 13);
  string__2_653 = from_latin_1_string("NODE *create_future(void);\012", 27);
  string__2_655 = from_latin_1_string("create_future_with_prototype", 28);
  string__2_656 = from_latin_1_string("NODE *create_future_with_prototype(NODE *prototype);\012", 53);
  string__2_658 = from_latin_1_string("initialize_future", 17);
  string__2_659 = from_latin_1_string("void initialize_future(NODE *var, NODE *val);\012", 46);
  string__2_661 = from_latin_1_string("maybe_initialize_future", 23);
  string__2_662 = from_latin_1_string("void maybe_initialize_future(NODE *var, NODE *val);\012", 52);
  string__2_664 = from_latin_1_string("initialize_maybe_future", 23);
  string__2_665 = from_latin_1_string("void initialize_maybe_future(NODE *var, NODE *val);\012", 52);
  string__2_667 = from_latin_1_string("assign_value", 12);
  string__2_668 = from_latin_1_string("void assign_value(NODE **dest, NODE *val);\012", 43);
  string__2_670 = from_latin_1_string("assign_variable", 15);
  string__2_671 = from_latin_1_string("void assign_variable(NODE **dest, NODE **var_p);\012", 49);
  string__2_673 = from_latin_1_string("def_attribute", 13);
  string__2_674 = from_latin_1_string("void def_attribute(NODE **var_p, int idx, void *attr);\012", 55);
  string__2_676 = from_latin_1_string("create_cell", 11);
  string__2_677 = from_latin_1_string("NODE *create_cell(void);\012", 25);
  string__2_679 = from_latin_1_string("create_cell_with_contents", 25);
  string__2_680 = from_latin_1_string("NODE *create_cell_with_contents(NODE *contents);\012", 49);
  string__2_682 = from_latin_1_string("get_dynamic_slot", 16);
  string__2_683 = from_latin_1_string("NODE *get_dynamic_slot(int id);\012", 32);
  string__2_685 = from_latin_1_string("get_dynamic_cell", 16);
  string__2_686 = from_latin_1_string("NODE *get_dynamic_cell(int id);\012", 32);
  string__2_688 = from_latin_1_string("set_dynamic_cell", 16);
  string__2_689 = from_latin_1_string("void set_dynamic_cell(int id, NODE *node);\012", 43);
  string__2_691 = from_latin_1_string("define_dynamic_slot", 19);
  string__2_692 = from_latin_1_string("void define_dynamic_slot(int id, NODE *node);\012", 46);
  string__2_694 = from_latin_1_string("define_dynamic_cell", 19);
  string__2_695 = from_latin_1_string("void define_dynamic_cell(int id, NODE *node);\012", 46);
  string__2_697 = from_latin_1_string("terminate", 9);
  string__2_698 = from_latin_1_string("void terminate(int exit_code);\012", 31);
  string__2_700 = from_latin_1_string("execute", 7);
  string__2_701 = from_latin_1_string("__attribute__ ((noreturn)) void execute(FUNC entry);\012", 53);
  string__2_703 = from_latin_1_string("invoke_callback", 15);
  string__2_704 = from_latin_1_string("void invoke_callback(NODE *callback);\012", 38);
  string__2_706 = from_latin_1_string("COMPARE_FUNCTION", 16);
  string__2_707 = from_latin_1_string("typedef int (*COMPARE_FUNCTION)(const void *, const void *);\012", 61);
  string__2_709 = from_latin_1_string("DEBUG_COMMAND", 13);
  string__2_710 = from_latin_1_string("typedef enum {\012  SHOW_PROMPT,\012  LOG_LAST_INSTRUCTION,\012  GOTO_INSTRUCTION\012} DEBUG_COMMAND;\012", 90);
  string__2_712 = from_latin_1_string("SHARED_DATA", 11);
  string__2_713 = from_latin_1_string("typedef struct {\012  DEBUG_COMMAND command;\012  uint64_t instruction_counter;\012  int depth;\012} SHARED_DATA;\012", 102);
  string__2_715 = from_latin_1_string("retrieve_continuation_info", 26);
  string__2_716 = from_latin_1_string("int retrieve_continuation_info(\012  FUNC func, const char **filename_p, CONTINUATION_INFO **info_p\012);\012", 100);
  string__2_718 = from_latin_1_string("crash_dump", 10);
  string__2_719 = from_latin_1_string("void crash_dump(void);\012", 23);
}

static int already_run_phase_3 = false;

EXPORT void phase_3__runtime_definitions(void) {
  if (already_run_phase_3) return;
  already_run_phase_3 = true;
  set_module("runtime_definitions");
  set_used_namespaces(used_namespaces);
  use_read_only("std", "key_value_pair", &get__std__key_value_pair, &get_value_or_future__std__key_value_pair);
  use_read_only(NULL, "table", &get__table, &get_value_or_future__table);
}

static int already_run_phase_4 = false;

EXPORT void phase_4__runtime_definitions(void) {
  if (already_run_phase_4) return;
  already_run_phase_4 = true;
}

static int already_run_phase_5 = false;

EXPORT void phase_5__runtime_definitions(void) {
  if (already_run_phase_5) return;
  already_run_phase_5 = true;
  register_collector(collect__runtime_definitions);
}
