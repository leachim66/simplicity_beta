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
IMPORT NODE *get_dynamic_cell(int id);
IMPORT void set_dynamic_cell(int id, NODE *node);
IMPORT void define_dynamic_cell(int id, NODE *node);
IMPORT NODE *get_dynamic_slot(int id);
IMPORT void define_dynamic_slot(int id, NODE *node);
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
IMPORT NODE *undefined;
IMPORT void initialize_maybe_future(NODE *var, NODE *val);
IMPORT int result_count;
IMPORT void invalid_results_error(void);
IMPORT void initialize_future(NODE *var, NODE *val);
IMPORT NODE *collect_node(NODE *node);
IMPORT void register_module_info(MODULE_INFO *info);
IMPORT void define_polymorphic_function_with_setter(
  const char *namespace, const char *name, NODE_GETTER getter, int *id_p,
  NODE **var_p
);
IMPORT NODE *from_latin_1_string(const char *str, long len);
IMPORT void set_module(const char *name);
IMPORT void set_used_namespaces(const char **namespaces);
typedef void (*NODE_SETTER)(NODE *);
IMPORT void define_multi_assign_dynamic(
  const char *namespace, const char *name,
  NODE_GETTER getter, NODE_SETTER setter, NODE_SETTER definer,
  int *id_p
);
IMPORT void define_single_assign_dynamic(
  const char *namespace, const char *name,
  NODE_GETTER getter, NODE_SETTER definer,
  int *id_p
);
IMPORT NODE *create_future(void);
IMPORT void define_single_assign_static(
  const char *namespace, const char *name,
  NODE_GETTER getter, NODE **var_p
);
IMPORT void use_read_only(
  const char *namespace, const char *name,
  NODE_GETTER *getter, NODE_GETTER *get_value_or_future
);
IMPORT void assign_value(NODE **dest, NODE *val);
IMPORT NODE *create_function(FUNC func, int par_count);
IMPORT void maybe_initialize_future(NODE *var, NODE *val);
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
static NODE_GETTER get__list;
static NODE_GETTER get_value_or_future__list;
static NODE_GETTER get__undefined;
static NODE_GETTER get_value_or_future__undefined;
static struct {
  NODE *sim2c__line_no_of;
  NODE *sim2c__text_of;
  NODE *sim2c__source_of;
  NODE *sim2c__indents_of;
  NODE *sim2c__vtable_entries;
} var;
static const char *var_names[] = {
};
static int poly_idx__sim2c__line_no_of;
static void type__sim2c__line_no_of(void);
static NODE *get__sim2c__line_no_of(void) {
  return var.sim2c__line_no_of;
}
static int poly_idx__sim2c__text_of;
static void type__sim2c__text_of(void);
static NODE *get__sim2c__text_of(void) {
  return var.sim2c__text_of;
}
static int poly_idx__sim2c__source_of;
static void type__sim2c__source_of(void);
static NODE *get__sim2c__source_of(void) {
  return var.sim2c__source_of;
}
static int poly_idx__sim2c__indents_of;
static void type__sim2c__indents_of(void);
static NODE *get__sim2c__indents_of(void) {
  return var.sim2c__indents_of;
}
static int dyna_idx__sim2c__required_modules;
static NODE *get__sim2c__required_modules(void) {
  return get_dynamic_cell(dyna_idx__sim2c__required_modules);
}
static void set__sim2c__required_modules(NODE *node) {
  set_dynamic_cell(dyna_idx__sim2c__required_modules, node);
}
static void define__sim2c__required_modules(NODE *node) {
  define_dynamic_cell(dyna_idx__sim2c__required_modules, node);
}
static int dyna_idx__sim2c__used_namespaces;
static NODE *get__sim2c__used_namespaces(void) {
  return get_dynamic_cell(dyna_idx__sim2c__used_namespaces);
}
static void set__sim2c__used_namespaces(NODE *node) {
  set_dynamic_cell(dyna_idx__sim2c__used_namespaces, node);
}
static void define__sim2c__used_namespaces(NODE *node) {
  define_dynamic_cell(dyna_idx__sim2c__used_namespaces, node);
}
static int dyna_idx__sim2c__defined_namespaces;
static NODE *get__sim2c__defined_namespaces(void) {
  return get_dynamic_cell(dyna_idx__sim2c__defined_namespaces);
}
static void set__sim2c__defined_namespaces(NODE *node) {
  set_dynamic_cell(dyna_idx__sim2c__defined_namespaces, node);
}
static void define__sim2c__defined_namespaces(NODE *node) {
  define_dynamic_cell(dyna_idx__sim2c__defined_namespaces, node);
}
static int dyna_idx__sim2c__namespace_mappings;
static NODE *get__sim2c__namespace_mappings(void) {
  return get_dynamic_cell(dyna_idx__sim2c__namespace_mappings);
}
static void set__sim2c__namespace_mappings(NODE *node) {
  set_dynamic_cell(dyna_idx__sim2c__namespace_mappings, node);
}
static void define__sim2c__namespace_mappings(NODE *node) {
  define_dynamic_cell(dyna_idx__sim2c__namespace_mappings, node);
}
static int dyna_idx__sim2c__included_files;
static NODE *get__sim2c__included_files(void) {
  return get_dynamic_cell(dyna_idx__sim2c__included_files);
}
static void set__sim2c__included_files(NODE *node) {
  set_dynamic_cell(dyna_idx__sim2c__included_files, node);
}
static void define__sim2c__included_files(NODE *node) {
  define_dynamic_cell(dyna_idx__sim2c__included_files, node);
}
static int dyna_idx__sim2c__linked_libraries;
static NODE *get__sim2c__linked_libraries(void) {
  return get_dynamic_cell(dyna_idx__sim2c__linked_libraries);
}
static void set__sim2c__linked_libraries(NODE *node) {
  set_dynamic_cell(dyna_idx__sim2c__linked_libraries, node);
}
static void define__sim2c__linked_libraries(NODE *node) {
  define_dynamic_cell(dyna_idx__sim2c__linked_libraries, node);
}
static int dyna_idx__sim2c__dependent_data;
static NODE *get__sim2c__dependent_data(void) {
  return get_dynamic_cell(dyna_idx__sim2c__dependent_data);
}
static void set__sim2c__dependent_data(NODE *node) {
  set_dynamic_cell(dyna_idx__sim2c__dependent_data, node);
}
static void define__sim2c__dependent_data(NODE *node) {
  define_dynamic_cell(dyna_idx__sim2c__dependent_data, node);
}
static int dyna_idx__sim2c__enumeration_count;
static NODE *get__sim2c__enumeration_count(void) {
  return get_dynamic_cell(dyna_idx__sim2c__enumeration_count);
}
static void set__sim2c__enumeration_count(NODE *node) {
  set_dynamic_cell(dyna_idx__sim2c__enumeration_count, node);
}
static void define__sim2c__enumeration_count(NODE *node) {
  define_dynamic_cell(dyna_idx__sim2c__enumeration_count, node);
}
static int dyna_idx__sim2c__global_names;
static NODE *get__sim2c__global_names(void) {
  return get_dynamic_cell(dyna_idx__sim2c__global_names);
}
static void set__sim2c__global_names(NODE *node) {
  set_dynamic_cell(dyna_idx__sim2c__global_names, node);
}
static void define__sim2c__global_names(NODE *node) {
  define_dynamic_cell(dyna_idx__sim2c__global_names, node);
}
static int dyna_idx__sim2c__exported_names;
static NODE *get__sim2c__exported_names(void) {
  return get_dynamic_cell(dyna_idx__sim2c__exported_names);
}
static void set__sim2c__exported_names(NODE *node) {
  set_dynamic_cell(dyna_idx__sim2c__exported_names, node);
}
static void define__sim2c__exported_names(NODE *node) {
  define_dynamic_cell(dyna_idx__sim2c__exported_names, node);
}
static int dyna_idx__sim2c__needed_names;
static NODE *get__sim2c__needed_names(void) {
  return get_dynamic_cell(dyna_idx__sim2c__needed_names);
}
static void set__sim2c__needed_names(NODE *node) {
  set_dynamic_cell(dyna_idx__sim2c__needed_names, node);
}
static void define__sim2c__needed_names(NODE *node) {
  define_dynamic_cell(dyna_idx__sim2c__needed_names, node);
}
static int dyna_idx__sim2c__use_inline_c;
static NODE *get__sim2c__use_inline_c(void) {
  return get_dynamic_cell(dyna_idx__sim2c__use_inline_c);
}
static void set__sim2c__use_inline_c(NODE *node) {
  set_dynamic_cell(dyna_idx__sim2c__use_inline_c, node);
}
static void define__sim2c__use_inline_c(NODE *node) {
  define_dynamic_cell(dyna_idx__sim2c__use_inline_c, node);
}
static int dyna_idx__sim2c__defined_structs;
static NODE *get__sim2c__defined_structs(void) {
  return get_dynamic_cell(dyna_idx__sim2c__defined_structs);
}
static void set__sim2c__defined_structs(NODE *node) {
  set_dynamic_cell(dyna_idx__sim2c__defined_structs, node);
}
static void define__sim2c__defined_structs(NODE *node) {
  define_dynamic_cell(dyna_idx__sim2c__defined_structs, node);
}
static int dyna_idx__sim2c__defined_nodes;
static NODE *get__sim2c__defined_nodes(void) {
  return get_dynamic_cell(dyna_idx__sim2c__defined_nodes);
}
static void set__sim2c__defined_nodes(NODE *node) {
  set_dynamic_cell(dyna_idx__sim2c__defined_nodes, node);
}
static void define__sim2c__defined_nodes(NODE *node) {
  define_dynamic_cell(dyna_idx__sim2c__defined_nodes, node);
}
static int dyna_idx__sim2c__defined_functions;
static NODE *get__sim2c__defined_functions(void) {
  return get_dynamic_cell(dyna_idx__sim2c__defined_functions);
}
static void set__sim2c__defined_functions(NODE *node) {
  set_dynamic_cell(dyna_idx__sim2c__defined_functions, node);
}
static void define__sim2c__defined_functions(NODE *node) {
  define_dynamic_cell(dyna_idx__sim2c__defined_functions, node);
}
static int dyna_idx__sim2c__write_to_generated_collections;
static NODE *get__sim2c__write_to_generated_collections(void) {
  return get_dynamic_slot(dyna_idx__sim2c__write_to_generated_collections);
}
static void define__sim2c__write_to_generated_collections(NODE *node) {
  define_dynamic_slot(dyna_idx__sim2c__write_to_generated_collections, node);
}
static int dyna_idx__sim2c__write_to_delayed_statements;
static NODE *get__sim2c__write_to_delayed_statements(void) {
  return get_dynamic_slot(dyna_idx__sim2c__write_to_delayed_statements);
}
static void define__sim2c__write_to_delayed_statements(NODE *node) {
  define_dynamic_slot(dyna_idx__sim2c__write_to_delayed_statements, node);
}
static int dyna_idx__sim2c__use_identifier;
static NODE *get__sim2c__use_identifier(void) {
  return get_dynamic_slot(dyna_idx__sim2c__use_identifier);
}
static void define__sim2c__use_identifier(NODE *node) {
  define_dynamic_slot(dyna_idx__sim2c__use_identifier, node);
}
static int dyna_idx__sim2c__write_to_declarations;
static NODE *get__sim2c__write_to_declarations(void) {
  return get_dynamic_slot(dyna_idx__sim2c__write_to_declarations);
}
static void define__sim2c__write_to_declarations(NODE *node) {
  define_dynamic_slot(dyna_idx__sim2c__write_to_declarations, node);
}
static int dyna_idx__sim2c__write_to_top_level_variable_names;
static NODE *get__sim2c__write_to_top_level_variable_names(void) {
  return get_dynamic_slot(dyna_idx__sim2c__write_to_top_level_variable_names);
}
static void define__sim2c__write_to_top_level_variable_names(NODE *node) {
  define_dynamic_slot(dyna_idx__sim2c__write_to_top_level_variable_names, node);
}
static int dyna_idx__sim2c__write_to_top_level_variable_declarations;
static NODE *get__sim2c__write_to_top_level_variable_declarations(void) {
  return get_dynamic_slot(dyna_idx__sim2c__write_to_top_level_variable_declarations);
}
static void define__sim2c__write_to_top_level_variable_declarations(NODE *node) {
  define_dynamic_slot(dyna_idx__sim2c__write_to_top_level_variable_declarations, node);
}
static int dyna_idx__sim2c__write_to_global_variable_declarations;
static NODE *get__sim2c__write_to_global_variable_declarations(void) {
  return get_dynamic_slot(dyna_idx__sim2c__write_to_global_variable_declarations);
}
static void define__sim2c__write_to_global_variable_declarations(NODE *node) {
  define_dynamic_slot(dyna_idx__sim2c__write_to_global_variable_declarations, node);
}
static int dyna_idx__sim2c__write_to_continuation_table;
static NODE *get__sim2c__write_to_continuation_table(void) {
  return get_dynamic_slot(dyna_idx__sim2c__write_to_continuation_table);
}
static void define__sim2c__write_to_continuation_table(NODE *node) {
  define_dynamic_slot(dyna_idx__sim2c__write_to_continuation_table, node);
}
static int dyna_idx__sim2c__write_to_delayed_continuation_table;
static NODE *get__sim2c__write_to_delayed_continuation_table(void) {
  return get_dynamic_slot(dyna_idx__sim2c__write_to_delayed_continuation_table);
}
static void define__sim2c__write_to_delayed_continuation_table(NODE *node) {
  define_dynamic_slot(dyna_idx__sim2c__write_to_delayed_continuation_table, node);
}
static int dyna_idx__sim2c__write_to_functions;
static NODE *get__sim2c__write_to_functions(void) {
  return get_dynamic_slot(dyna_idx__sim2c__write_to_functions);
}
static void define__sim2c__write_to_functions(NODE *node) {
  define_dynamic_slot(dyna_idx__sim2c__write_to_functions, node);
}
static int dyna_idx__sim2c__write_to_phase_1;
static NODE *get__sim2c__write_to_phase_1(void) {
  return get_dynamic_slot(dyna_idx__sim2c__write_to_phase_1);
}
static void define__sim2c__write_to_phase_1(NODE *node) {
  define_dynamic_slot(dyna_idx__sim2c__write_to_phase_1, node);
}
static int dyna_idx__sim2c__write_to_phase_2;
static NODE *get__sim2c__write_to_phase_2(void) {
  return get_dynamic_slot(dyna_idx__sim2c__write_to_phase_2);
}
static void define__sim2c__write_to_phase_2(NODE *node) {
  define_dynamic_slot(dyna_idx__sim2c__write_to_phase_2, node);
}
static int dyna_idx__sim2c__write_to_phase_3;
static NODE *get__sim2c__write_to_phase_3(void) {
  return get_dynamic_slot(dyna_idx__sim2c__write_to_phase_3);
}
static void define__sim2c__write_to_phase_3(NODE *node) {
  define_dynamic_slot(dyna_idx__sim2c__write_to_phase_3, node);
}
static int dyna_idx__sim2c__write_to_phase_4;
static NODE *get__sim2c__write_to_phase_4(void) {
  return get_dynamic_slot(dyna_idx__sim2c__write_to_phase_4);
}
static void define__sim2c__write_to_phase_4(NODE *node) {
  define_dynamic_slot(dyna_idx__sim2c__write_to_phase_4, node);
}
static int dyna_idx__sim2c__write_to_phase_5;
static NODE *get__sim2c__write_to_phase_5(void) {
  return get_dynamic_slot(dyna_idx__sim2c__write_to_phase_5);
}
static void define__sim2c__write_to_phase_5(NODE *node) {
  define_dynamic_slot(dyna_idx__sim2c__write_to_phase_5, node);
}
static int dyna_idx__sim2c__write_to_phase_6;
static NODE *get__sim2c__write_to_phase_6(void) {
  return get_dynamic_slot(dyna_idx__sim2c__write_to_phase_6);
}
static void define__sim2c__write_to_phase_6(NODE *node) {
  define_dynamic_slot(dyna_idx__sim2c__write_to_phase_6, node);
}
static int dyna_idx__sim2c__use_literal;
static NODE *get__sim2c__use_literal(void) {
  return get_dynamic_slot(dyna_idx__sim2c__use_literal);
}
static void define__sim2c__use_literal(NODE *node) {
  define_dynamic_slot(dyna_idx__sim2c__use_literal, node);
}
static int dyna_idx__sim2c__module_name;
static NODE *get__sim2c__module_name(void) {
  return get_dynamic_slot(dyna_idx__sim2c__module_name);
}
static void define__sim2c__module_name(NODE *node) {
  define_dynamic_slot(dyna_idx__sim2c__module_name, node);
}
static int dyna_idx__sim2c__submodule_no;
static NODE *get__sim2c__submodule_no(void) {
  return get_dynamic_slot(dyna_idx__sim2c__submodule_no);
}
static void define__sim2c__submodule_no(NODE *node) {
  define_dynamic_slot(dyna_idx__sim2c__submodule_no, node);
}
static int dyna_idx__sim2c__index;
static NODE *get__sim2c__index(void) {
  return get_dynamic_cell(dyna_idx__sim2c__index);
}
static void set__sim2c__index(NODE *node) {
  set_dynamic_cell(dyna_idx__sim2c__index, node);
}
static void define__sim2c__index(NODE *node) {
  define_dynamic_cell(dyna_idx__sim2c__index, node);
}
static int dyna_idx__sim2c__definitions;
static NODE *get__sim2c__definitions(void) {
  return get_dynamic_cell(dyna_idx__sim2c__definitions);
}
static void set__sim2c__definitions(NODE *node) {
  set_dynamic_cell(dyna_idx__sim2c__definitions, node);
}
static void define__sim2c__definitions(NODE *node) {
  define_dynamic_cell(dyna_idx__sim2c__definitions, node);
}
static int dyna_idx__sim2c__statements;
static NODE *get__sim2c__statements(void) {
  return get_dynamic_cell(dyna_idx__sim2c__statements);
}
static void set__sim2c__statements(NODE *node) {
  set_dynamic_cell(dyna_idx__sim2c__statements, node);
}
static void define__sim2c__statements(NODE *node) {
  define_dynamic_cell(dyna_idx__sim2c__statements, node);
}
static int dyna_idx__sim2c__actions;
static NODE *get__sim2c__actions(void) {
  return get_dynamic_cell(dyna_idx__sim2c__actions);
}
static void set__sim2c__actions(NODE *node) {
  set_dynamic_cell(dyna_idx__sim2c__actions, node);
}
static void define__sim2c__actions(NODE *node) {
  define_dynamic_cell(dyna_idx__sim2c__actions, node);
}
static int dyna_idx__sim2c__temp_idx;
static NODE *get__sim2c__temp_idx(void) {
  return get_dynamic_cell(dyna_idx__sim2c__temp_idx);
}
static void set__sim2c__temp_idx(NODE *node) {
  set_dynamic_cell(dyna_idx__sim2c__temp_idx, node);
}
static void define__sim2c__temp_idx(NODE *node) {
  define_dynamic_cell(dyna_idx__sim2c__temp_idx, node);
}
static int dyna_idx__sim2c__current_fragment;
static NODE *get__sim2c__current_fragment(void) {
  return get_dynamic_slot(dyna_idx__sim2c__current_fragment);
}
static void define__sim2c__current_fragment(NODE *node) {
  define_dynamic_slot(dyna_idx__sim2c__current_fragment, node);
}
static int dyna_idx__sim2c__already_defined_names;
static NODE *get__sim2c__already_defined_names(void) {
  return get_dynamic_slot(dyna_idx__sim2c__already_defined_names);
}
static void define__sim2c__already_defined_names(NODE *node) {
  define_dynamic_slot(dyna_idx__sim2c__already_defined_names, node);
}
static int dyna_idx__sim2c__defined_names;
static NODE *get__sim2c__defined_names(void) {
  return get_dynamic_cell(dyna_idx__sim2c__defined_names);
}
static void set__sim2c__defined_names(NODE *node) {
  set_dynamic_cell(dyna_idx__sim2c__defined_names, node);
}
static void define__sim2c__defined_names(NODE *node) {
  define_dynamic_cell(dyna_idx__sim2c__defined_names, node);
}
static int dyna_idx__sim2c__used_names;
static NODE *get__sim2c__used_names(void) {
  return get_dynamic_cell(dyna_idx__sim2c__used_names);
}
static void set__sim2c__used_names(NODE *node) {
  set_dynamic_cell(dyna_idx__sim2c__used_names, node);
}
static void define__sim2c__used_names(NODE *node) {
  define_dynamic_cell(dyna_idx__sim2c__used_names, node);
}
static int dyna_idx__sim2c__assigned_names;
static NODE *get__sim2c__assigned_names(void) {
  return get_dynamic_cell(dyna_idx__sim2c__assigned_names);
}
static void set__sim2c__assigned_names(NODE *node) {
  set_dynamic_cell(dyna_idx__sim2c__assigned_names, node);
}
static void define__sim2c__assigned_names(NODE *node) {
  define_dynamic_cell(dyna_idx__sim2c__assigned_names, node);
}
static int dyna_idx__sim2c__current_continuation_info;
static NODE *get__sim2c__current_continuation_info(void) {
  return get_dynamic_cell(dyna_idx__sim2c__current_continuation_info);
}
static void set__sim2c__current_continuation_info(NODE *node) {
  set_dynamic_cell(dyna_idx__sim2c__current_continuation_info, node);
}
static void define__sim2c__current_continuation_info(NODE *node) {
  define_dynamic_cell(dyna_idx__sim2c__current_continuation_info, node);
}
static NODE *get__sim2c__vtable_entries(void) {
  return var.sim2c__vtable_entries;
}
static NODE *string__100_1;
static NODE *string__100_2;
static NODE *string__100_3;
static NODE *string__100_4;
static NODE *string__100_5;
static NODE *string__100_6;
static NODE *string__100_7;
static NODE *string__100_8;
static NODE *string__100_9;
static NODE *string__100_10;
static NODE *string__100_11;
static NODE *string__100_12;
static NODE *string__100_13;
static NODE *string__100_14;
static NODE *string__100_15;
static NODE *string__100_16;
static NODE *string__100_17;
static NODE *string__100_18;
static NODE *string__100_19;
static void cont__100_20(void);
void run__shared_variables(void);

static CONTINUATION_INFO continuation_info[] = {
  {type__sim2c__line_no_of, NULL, 31, 31, 2, 18},
  {type__sim2c__text_of, NULL, 32, 32, 2, 15},
  {type__sim2c__source_of, NULL, 33, 33, 2, 17},
  {type__sim2c__indents_of, NULL, 34, 34, 2, 18},
  {run__shared_variables, NULL, 108, 128, 1, 19},
  {cont__100_20, NULL, }
};

union NODE {
  struct {
    FUNC type;
    ATTRIBUTES *attributes;
  };
  CONTINUATION continuation;
  CLOSURE closure;
};
static void type__sim2c__line_no_of(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__sim2c__line_no_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__sim2c__line_no_of, attr);
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
static void type__sim2c__text_of(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__sim2c__text_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__sim2c__text_of, attr);
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
static void type__sim2c__source_of(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__sim2c__source_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__sim2c__source_of, attr);
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
static void type__sim2c__indents_of(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__sim2c__indents_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__sim2c__indents_of, attr);
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
  "sim2c",
  "node",
  NULL
};

static MODULE_INFO module_info = {
  NULL,
  "shared_variables",
  continuation_info,
  sizeof(continuation_info)/sizeof(CONTINUATION_INFO),
  (NODE **)&var,
  var_names,
  sizeof(var_names)/sizeof(const char *),
  used_namespaces,
  {DEBUG_FILENAME("shared_variables.sim")}
};

/******
C O D E
******/

static int already_run = false;

EXPORT void run__shared_variables(void) {
  if (already_run) {
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  already_run = true;
  allocate_initialized_frame_gc(0, 0);
  // 38: %%sim2c::required_modules undefined # a table
  set__sim2c__required_modules(get__undefined());
  // 39: %%sim2c::used_namespaces undefined # a set
  set__sim2c__used_namespaces(get__undefined());
  // 40: %%sim2c::defined_namespaces undefined # a set
  set__sim2c__defined_namespaces(get__undefined());
  // 41: %%sim2c::namespace_mappings undefined # a table
  set__sim2c__namespace_mappings(get__undefined());
  // 42: %%sim2c::included_files undefined # a set
  set__sim2c__included_files(get__undefined());
  // 43: %%sim2c::linked_libraries undefined # a set
  set__sim2c__linked_libraries(get__undefined());
  // 44: %%sim2c::dependent_data undefined # a set
  set__sim2c__dependent_data(get__undefined());
  // 48: %%sim2c::enumeration_count undefined # an integer
  set__sim2c__enumeration_count(get__undefined());
  // 52: %%sim2c::global_names undefined # module global names
  set__sim2c__global_names(get__undefined());
  // 53: %%sim2c::exported_names undefined # first index: name; second index: namespace
  set__sim2c__exported_names(get__undefined());
  // 54: %%sim2c::needed_names undefined # contains all symbols that are imported
  set__sim2c__needed_names(get__undefined());
  // 58: %%sim2c::use_inline_c undefined
  set__sim2c__use_inline_c(get__undefined());
  // 59: %%sim2c::defined_structs undefined
  set__sim2c__defined_structs(get__undefined());
  // 60: %%sim2c::defined_nodes undefined
  set__sim2c__defined_nodes(get__undefined());
  // 61: %%sim2c::defined_functions undefined
  set__sim2c__defined_functions(get__undefined());
  // 65: %sim2c::write_to_generated_collections undefined
  initialize_maybe_future(get__sim2c__write_to_generated_collections(), get__undefined());
  // 66: %sim2c::write_to_delayed_statements undefined
  initialize_maybe_future(get__sim2c__write_to_delayed_statements(), get__undefined());
  // 67: %sim2c::use_identifier undefined
  initialize_maybe_future(get__sim2c__use_identifier(), get__undefined());
  // 68: %sim2c::write_to_declarations undefined
  initialize_maybe_future(get__sim2c__write_to_declarations(), get__undefined());
  // 69: %sim2c::write_to_top_level_variable_names undefined
  initialize_maybe_future(get__sim2c__write_to_top_level_variable_names(), get__undefined());
  // 70: %sim2c::write_to_top_level_variable_declarations undefined
  initialize_maybe_future(get__sim2c__write_to_top_level_variable_declarations(), get__undefined());
  // 71: %sim2c::write_to_global_variable_declarations undefined
  initialize_maybe_future(get__sim2c__write_to_global_variable_declarations(), get__undefined());
  // 72: %sim2c::write_to_continuation_table undefined
  initialize_maybe_future(get__sim2c__write_to_continuation_table(), get__undefined());
  // 73: %sim2c::write_to_delayed_continuation_table undefined
  initialize_maybe_future(get__sim2c__write_to_delayed_continuation_table(), get__undefined());
  // 74: %sim2c::write_to_functions undefined
  initialize_maybe_future(get__sim2c__write_to_functions(), get__undefined());
  // 75: %sim2c::write_to_phase_1 undefined
  initialize_maybe_future(get__sim2c__write_to_phase_1(), get__undefined());
  // 76: %sim2c::write_to_phase_2 undefined
  initialize_maybe_future(get__sim2c__write_to_phase_2(), get__undefined());
  // 77: %sim2c::write_to_phase_3 undefined
  initialize_maybe_future(get__sim2c__write_to_phase_3(), get__undefined());
  // 78: %sim2c::write_to_phase_4 undefined
  initialize_maybe_future(get__sim2c__write_to_phase_4(), get__undefined());
  // 79: %sim2c::write_to_phase_5 undefined
  initialize_maybe_future(get__sim2c__write_to_phase_5(), get__undefined());
  // 80: %sim2c::write_to_phase_6 undefined
  initialize_maybe_future(get__sim2c__write_to_phase_6(), get__undefined());
  // 81: %sim2c::use_literal undefined
  initialize_maybe_future(get__sim2c__use_literal(), get__undefined());
  // 85: %sim2c::module_name undefined # the name of the current compilation unit
  initialize_maybe_future(get__sim2c__module_name(), get__undefined());
  // 86: %sim2c::submodule_no undefined
  initialize_maybe_future(get__sim2c__submodule_no(), get__undefined());
  // 88: %%sim2c::index undefined # used for enumerating expanded source code items
  set__sim2c__index(get__undefined());
  // 89: %%sim2c::definitions undefined # a list of key-value pairs
  set__sim2c__definitions(get__undefined());
  // 90: %%sim2c::statements undefined # a list of statements
  set__sim2c__statements(get__undefined());
  // 91: %%sim2c::actions undefined # a list of deferred actions (closures)
  set__sim2c__actions(get__undefined());
  // 92: %%sim2c::temp_idx undefined
  set__sim2c__temp_idx(get__undefined());
  // 94: %sim2c::current_fragment undefined # used for generating error messages
  initialize_maybe_future(get__sim2c__current_fragment(), get__undefined());
  // 95: %sim2c::already_defined_names undefined
  initialize_maybe_future(get__sim2c__already_defined_names(), get__undefined());
  // 97: %%sim2c::defined_names undefined # used for collecting defined symbols
  set__sim2c__defined_names(get__undefined());
  // 98: %%sim2c::used_names undefined # used for collecting usages of symbols
  set__sim2c__used_names(get__undefined());
  // 99: %%sim2c::assigned_names undefined
  set__sim2c__assigned_names(get__undefined());
  // 103: %%sim2c::current_continuation_info undefined
  set__sim2c__current_continuation_info(get__undefined());
  // 108: $sim2c::vtable_entries
  // 109:   list
  // 110:     "to_int8"
  // 111:     "to_int16"
  // 112:     "to_int32"
  // 113:     "to_int64"
  // 114:     "to_uint8"
  // 115:     "to_uint16"
  // 116:     "to_uint32"
  // 117:     "to_uint64"
  // ...
  argument_count = 19;
  arguments = node_p;
  arguments->slots[0] = string__100_1;
  arguments->slots[1] = string__100_2;
  arguments->slots[2] = string__100_3;
  arguments->slots[3] = string__100_4;
  arguments->slots[4] = string__100_5;
  arguments->slots[5] = string__100_6;
  arguments->slots[6] = string__100_7;
  arguments->slots[7] = string__100_8;
  arguments->slots[8] = string__100_9;
  arguments->slots[9] = string__100_10;
  arguments->slots[10] = string__100_11;
  arguments->slots[11] = string__100_12;
  arguments->slots[12] = string__100_13;
  arguments->slots[13] = string__100_14;
  arguments->slots[14] = string__100_15;
  arguments->slots[15] = string__100_16;
  arguments->slots[16] = string__100_17;
  arguments->slots[17] = string__100_18;
  arguments->slots[18] = string__100_19;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__100_20;
}
static void cont__100_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var.sim2c__vtable_entries, arguments->slots[0]);
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
EXPORT void collect__shared_variables(void) {
  var.sim2c__line_no_of = collect_node(var.sim2c__line_no_of);
  var.sim2c__text_of = collect_node(var.sim2c__text_of);
  var.sim2c__source_of = collect_node(var.sim2c__source_of);
  var.sim2c__indents_of = collect_node(var.sim2c__indents_of);
  var.sim2c__vtable_entries = collect_node(var.sim2c__vtable_entries);
  string__100_1 = collect_node(string__100_1);
  string__100_2 = collect_node(string__100_2);
  string__100_3 = collect_node(string__100_3);
  string__100_4 = collect_node(string__100_4);
  string__100_5 = collect_node(string__100_5);
  string__100_6 = collect_node(string__100_6);
  string__100_7 = collect_node(string__100_7);
  string__100_8 = collect_node(string__100_8);
  string__100_9 = collect_node(string__100_9);
  string__100_10 = collect_node(string__100_10);
  string__100_11 = collect_node(string__100_11);
  string__100_12 = collect_node(string__100_12);
  string__100_13 = collect_node(string__100_13);
  string__100_14 = collect_node(string__100_14);
  string__100_15 = collect_node(string__100_15);
  string__100_16 = collect_node(string__100_16);
  string__100_17 = collect_node(string__100_17);
  string__100_18 = collect_node(string__100_18);
  string__100_19 = collect_node(string__100_19);
}

static int already_run_phase_1 = false;

EXPORT void phase_1__shared_variables(void) {
  if (already_run_phase_1) return;
  already_run_phase_1 = true;
  register_module_info(&module_info);
  define_polymorphic_function_with_setter("sim2c", "line_no_of", get__sim2c__line_no_of, &poly_idx__sim2c__line_no_of, &var.sim2c__line_no_of);
  define_polymorphic_function_with_setter("sim2c", "text_of", get__sim2c__text_of, &poly_idx__sim2c__text_of, &var.sim2c__text_of);
  define_polymorphic_function_with_setter("sim2c", "source_of", get__sim2c__source_of, &poly_idx__sim2c__source_of, &var.sim2c__source_of);
  define_polymorphic_function_with_setter("sim2c", "indents_of", get__sim2c__indents_of, &poly_idx__sim2c__indents_of, &var.sim2c__indents_of);
}

static int already_run_phase_2 = false;

EXPORT void phase_2__shared_variables(void) {
  if (already_run_phase_2) return;
  already_run_phase_2 = true;
  string__100_1 = from_latin_1_string("to_int8", 7);
  string__100_2 = from_latin_1_string("to_int16", 8);
  string__100_3 = from_latin_1_string("to_int32", 8);
  string__100_4 = from_latin_1_string("to_int64", 8);
  string__100_5 = from_latin_1_string("to_uint8", 8);
  string__100_6 = from_latin_1_string("to_uint16", 9);
  string__100_7 = from_latin_1_string("to_uint32", 9);
  string__100_8 = from_latin_1_string("to_uint64", 9);
  string__100_9 = from_latin_1_string("to_uchar32", 10);
  string__100_10 = from_latin_1_string("to_bool", 7);
  string__100_11 = from_latin_1_string("to_int", 6);
  string__100_12 = from_latin_1_string("to_long", 7);
  string__100_13 = from_latin_1_string("to_double", 9);
  string__100_14 = from_latin_1_string("to_c_string", 11);
  string__100_15 = from_latin_1_string("to_octets", 9);
  string__100_16 = from_latin_1_string("get_item_of", 11);
  string__100_17 = from_latin_1_string("length_of", 9);
  string__100_18 = from_latin_1_string("unfold", 6);
  string__100_19 = from_latin_1_string("debug_string", 12);
}

static int already_run_phase_3 = false;

EXPORT void phase_3__shared_variables(void) {
  if (already_run_phase_3) return;
  already_run_phase_3 = true;
  set_module("shared_variables");
  set_used_namespaces(used_namespaces);
  define_multi_assign_dynamic("sim2c", "required_modules", get__sim2c__required_modules, set__sim2c__required_modules, define__sim2c__required_modules, &dyna_idx__sim2c__required_modules);
  define__sim2c__required_modules(undefined);
  define_multi_assign_dynamic("sim2c", "used_namespaces", get__sim2c__used_namespaces, set__sim2c__used_namespaces, define__sim2c__used_namespaces, &dyna_idx__sim2c__used_namespaces);
  define__sim2c__used_namespaces(undefined);
  define_multi_assign_dynamic("sim2c", "defined_namespaces", get__sim2c__defined_namespaces, set__sim2c__defined_namespaces, define__sim2c__defined_namespaces, &dyna_idx__sim2c__defined_namespaces);
  define__sim2c__defined_namespaces(undefined);
  define_multi_assign_dynamic("sim2c", "namespace_mappings", get__sim2c__namespace_mappings, set__sim2c__namespace_mappings, define__sim2c__namespace_mappings, &dyna_idx__sim2c__namespace_mappings);
  define__sim2c__namespace_mappings(undefined);
  define_multi_assign_dynamic("sim2c", "included_files", get__sim2c__included_files, set__sim2c__included_files, define__sim2c__included_files, &dyna_idx__sim2c__included_files);
  define__sim2c__included_files(undefined);
  define_multi_assign_dynamic("sim2c", "linked_libraries", get__sim2c__linked_libraries, set__sim2c__linked_libraries, define__sim2c__linked_libraries, &dyna_idx__sim2c__linked_libraries);
  define__sim2c__linked_libraries(undefined);
  define_multi_assign_dynamic("sim2c", "dependent_data", get__sim2c__dependent_data, set__sim2c__dependent_data, define__sim2c__dependent_data, &dyna_idx__sim2c__dependent_data);
  define__sim2c__dependent_data(undefined);
  define_multi_assign_dynamic("sim2c", "enumeration_count", get__sim2c__enumeration_count, set__sim2c__enumeration_count, define__sim2c__enumeration_count, &dyna_idx__sim2c__enumeration_count);
  define__sim2c__enumeration_count(undefined);
  define_multi_assign_dynamic("sim2c", "global_names", get__sim2c__global_names, set__sim2c__global_names, define__sim2c__global_names, &dyna_idx__sim2c__global_names);
  define__sim2c__global_names(undefined);
  define_multi_assign_dynamic("sim2c", "exported_names", get__sim2c__exported_names, set__sim2c__exported_names, define__sim2c__exported_names, &dyna_idx__sim2c__exported_names);
  define__sim2c__exported_names(undefined);
  define_multi_assign_dynamic("sim2c", "needed_names", get__sim2c__needed_names, set__sim2c__needed_names, define__sim2c__needed_names, &dyna_idx__sim2c__needed_names);
  define__sim2c__needed_names(undefined);
  define_multi_assign_dynamic("sim2c", "use_inline_c", get__sim2c__use_inline_c, set__sim2c__use_inline_c, define__sim2c__use_inline_c, &dyna_idx__sim2c__use_inline_c);
  define__sim2c__use_inline_c(undefined);
  define_multi_assign_dynamic("sim2c", "defined_structs", get__sim2c__defined_structs, set__sim2c__defined_structs, define__sim2c__defined_structs, &dyna_idx__sim2c__defined_structs);
  define__sim2c__defined_structs(undefined);
  define_multi_assign_dynamic("sim2c", "defined_nodes", get__sim2c__defined_nodes, set__sim2c__defined_nodes, define__sim2c__defined_nodes, &dyna_idx__sim2c__defined_nodes);
  define__sim2c__defined_nodes(undefined);
  define_multi_assign_dynamic("sim2c", "defined_functions", get__sim2c__defined_functions, set__sim2c__defined_functions, define__sim2c__defined_functions, &dyna_idx__sim2c__defined_functions);
  define__sim2c__defined_functions(undefined);
  define_single_assign_dynamic("sim2c", "write_to_generated_collections", get__sim2c__write_to_generated_collections, define__sim2c__write_to_generated_collections, &dyna_idx__sim2c__write_to_generated_collections);
  define__sim2c__write_to_generated_collections(create_future());
  define_single_assign_dynamic("sim2c", "write_to_delayed_statements", get__sim2c__write_to_delayed_statements, define__sim2c__write_to_delayed_statements, &dyna_idx__sim2c__write_to_delayed_statements);
  define__sim2c__write_to_delayed_statements(create_future());
  define_single_assign_dynamic("sim2c", "use_identifier", get__sim2c__use_identifier, define__sim2c__use_identifier, &dyna_idx__sim2c__use_identifier);
  define__sim2c__use_identifier(create_future());
  define_single_assign_dynamic("sim2c", "write_to_declarations", get__sim2c__write_to_declarations, define__sim2c__write_to_declarations, &dyna_idx__sim2c__write_to_declarations);
  define__sim2c__write_to_declarations(create_future());
  define_single_assign_dynamic("sim2c", "write_to_top_level_variable_names", get__sim2c__write_to_top_level_variable_names, define__sim2c__write_to_top_level_variable_names, &dyna_idx__sim2c__write_to_top_level_variable_names);
  define__sim2c__write_to_top_level_variable_names(create_future());
  define_single_assign_dynamic("sim2c", "write_to_top_level_variable_declarations", get__sim2c__write_to_top_level_variable_declarations, define__sim2c__write_to_top_level_variable_declarations, &dyna_idx__sim2c__write_to_top_level_variable_declarations);
  define__sim2c__write_to_top_level_variable_declarations(create_future());
  define_single_assign_dynamic("sim2c", "write_to_global_variable_declarations", get__sim2c__write_to_global_variable_declarations, define__sim2c__write_to_global_variable_declarations, &dyna_idx__sim2c__write_to_global_variable_declarations);
  define__sim2c__write_to_global_variable_declarations(create_future());
  define_single_assign_dynamic("sim2c", "write_to_continuation_table", get__sim2c__write_to_continuation_table, define__sim2c__write_to_continuation_table, &dyna_idx__sim2c__write_to_continuation_table);
  define__sim2c__write_to_continuation_table(create_future());
  define_single_assign_dynamic("sim2c", "write_to_delayed_continuation_table", get__sim2c__write_to_delayed_continuation_table, define__sim2c__write_to_delayed_continuation_table, &dyna_idx__sim2c__write_to_delayed_continuation_table);
  define__sim2c__write_to_delayed_continuation_table(create_future());
  define_single_assign_dynamic("sim2c", "write_to_functions", get__sim2c__write_to_functions, define__sim2c__write_to_functions, &dyna_idx__sim2c__write_to_functions);
  define__sim2c__write_to_functions(create_future());
  define_single_assign_dynamic("sim2c", "write_to_phase_1", get__sim2c__write_to_phase_1, define__sim2c__write_to_phase_1, &dyna_idx__sim2c__write_to_phase_1);
  define__sim2c__write_to_phase_1(create_future());
  define_single_assign_dynamic("sim2c", "write_to_phase_2", get__sim2c__write_to_phase_2, define__sim2c__write_to_phase_2, &dyna_idx__sim2c__write_to_phase_2);
  define__sim2c__write_to_phase_2(create_future());
  define_single_assign_dynamic("sim2c", "write_to_phase_3", get__sim2c__write_to_phase_3, define__sim2c__write_to_phase_3, &dyna_idx__sim2c__write_to_phase_3);
  define__sim2c__write_to_phase_3(create_future());
  define_single_assign_dynamic("sim2c", "write_to_phase_4", get__sim2c__write_to_phase_4, define__sim2c__write_to_phase_4, &dyna_idx__sim2c__write_to_phase_4);
  define__sim2c__write_to_phase_4(create_future());
  define_single_assign_dynamic("sim2c", "write_to_phase_5", get__sim2c__write_to_phase_5, define__sim2c__write_to_phase_5, &dyna_idx__sim2c__write_to_phase_5);
  define__sim2c__write_to_phase_5(create_future());
  define_single_assign_dynamic("sim2c", "write_to_phase_6", get__sim2c__write_to_phase_6, define__sim2c__write_to_phase_6, &dyna_idx__sim2c__write_to_phase_6);
  define__sim2c__write_to_phase_6(create_future());
  define_single_assign_dynamic("sim2c", "use_literal", get__sim2c__use_literal, define__sim2c__use_literal, &dyna_idx__sim2c__use_literal);
  define__sim2c__use_literal(create_future());
  define_single_assign_dynamic("sim2c", "module_name", get__sim2c__module_name, define__sim2c__module_name, &dyna_idx__sim2c__module_name);
  define__sim2c__module_name(create_future());
  define_single_assign_dynamic("sim2c", "submodule_no", get__sim2c__submodule_no, define__sim2c__submodule_no, &dyna_idx__sim2c__submodule_no);
  define__sim2c__submodule_no(create_future());
  define_multi_assign_dynamic("sim2c", "index", get__sim2c__index, set__sim2c__index, define__sim2c__index, &dyna_idx__sim2c__index);
  define__sim2c__index(undefined);
  define_multi_assign_dynamic("sim2c", "definitions", get__sim2c__definitions, set__sim2c__definitions, define__sim2c__definitions, &dyna_idx__sim2c__definitions);
  define__sim2c__definitions(undefined);
  define_multi_assign_dynamic("sim2c", "statements", get__sim2c__statements, set__sim2c__statements, define__sim2c__statements, &dyna_idx__sim2c__statements);
  define__sim2c__statements(undefined);
  define_multi_assign_dynamic("sim2c", "actions", get__sim2c__actions, set__sim2c__actions, define__sim2c__actions, &dyna_idx__sim2c__actions);
  define__sim2c__actions(undefined);
  define_multi_assign_dynamic("sim2c", "temp_idx", get__sim2c__temp_idx, set__sim2c__temp_idx, define__sim2c__temp_idx, &dyna_idx__sim2c__temp_idx);
  define__sim2c__temp_idx(undefined);
  define_single_assign_dynamic("sim2c", "current_fragment", get__sim2c__current_fragment, define__sim2c__current_fragment, &dyna_idx__sim2c__current_fragment);
  define__sim2c__current_fragment(create_future());
  define_single_assign_dynamic("sim2c", "already_defined_names", get__sim2c__already_defined_names, define__sim2c__already_defined_names, &dyna_idx__sim2c__already_defined_names);
  define__sim2c__already_defined_names(create_future());
  define_multi_assign_dynamic("sim2c", "defined_names", get__sim2c__defined_names, set__sim2c__defined_names, define__sim2c__defined_names, &dyna_idx__sim2c__defined_names);
  define__sim2c__defined_names(undefined);
  define_multi_assign_dynamic("sim2c", "used_names", get__sim2c__used_names, set__sim2c__used_names, define__sim2c__used_names, &dyna_idx__sim2c__used_names);
  define__sim2c__used_names(undefined);
  define_multi_assign_dynamic("sim2c", "assigned_names", get__sim2c__assigned_names, set__sim2c__assigned_names, define__sim2c__assigned_names, &dyna_idx__sim2c__assigned_names);
  define__sim2c__assigned_names(undefined);
  define_multi_assign_dynamic("sim2c", "current_continuation_info", get__sim2c__current_continuation_info, set__sim2c__current_continuation_info, define__sim2c__current_continuation_info, &dyna_idx__sim2c__current_continuation_info);
  define__sim2c__current_continuation_info(undefined);
  define_single_assign_static("sim2c", "vtable_entries", get__sim2c__vtable_entries, &var.sim2c__vtable_entries);
}

static int already_run_phase_4 = false;

EXPORT void phase_4__shared_variables(void) {
  if (already_run_phase_4) return;
  already_run_phase_4 = true;
  set_module("shared_variables");
  set_used_namespaces(used_namespaces);
  use_read_only(NULL, "list", &get__list, &get_value_or_future__list);
  use_read_only(NULL, "undefined", &get__undefined, &get_value_or_future__undefined);
}

static int already_run_phase_5 = false;

EXPORT void phase_5__shared_variables(void) {
  if (already_run_phase_5) return;
  already_run_phase_5 = true;
  assign_value(&var.sim2c__line_no_of, create_function(type__sim2c__line_no_of, -1));
  assign_value(&var.sim2c__text_of, create_function(type__sim2c__text_of, -1));
  assign_value(&var.sim2c__source_of, create_function(type__sim2c__source_of, -1));
  assign_value(&var.sim2c__indents_of, create_function(type__sim2c__indents_of, -1));
  maybe_initialize_future(get__sim2c__write_to_generated_collections(), get__undefined());
  maybe_initialize_future(get__sim2c__write_to_delayed_statements(), get__undefined());
  maybe_initialize_future(get__sim2c__use_identifier(), get__undefined());
  maybe_initialize_future(get__sim2c__write_to_declarations(), get__undefined());
  maybe_initialize_future(get__sim2c__write_to_top_level_variable_names(), get__undefined());
  maybe_initialize_future(get__sim2c__write_to_top_level_variable_declarations(), get__undefined());
  maybe_initialize_future(get__sim2c__write_to_global_variable_declarations(), get__undefined());
  maybe_initialize_future(get__sim2c__write_to_continuation_table(), get__undefined());
  maybe_initialize_future(get__sim2c__write_to_delayed_continuation_table(), get__undefined());
  maybe_initialize_future(get__sim2c__write_to_functions(), get__undefined());
  maybe_initialize_future(get__sim2c__write_to_phase_1(), get__undefined());
  maybe_initialize_future(get__sim2c__write_to_phase_2(), get__undefined());
  maybe_initialize_future(get__sim2c__write_to_phase_3(), get__undefined());
  maybe_initialize_future(get__sim2c__write_to_phase_4(), get__undefined());
  maybe_initialize_future(get__sim2c__write_to_phase_5(), get__undefined());
  maybe_initialize_future(get__sim2c__write_to_phase_6(), get__undefined());
  maybe_initialize_future(get__sim2c__use_literal(), get__undefined());
  maybe_initialize_future(get__sim2c__module_name(), get__undefined());
  maybe_initialize_future(get__sim2c__submodule_no(), get__undefined());
  maybe_initialize_future(get__sim2c__current_fragment(), get__undefined());
  maybe_initialize_future(get__sim2c__already_defined_names(), get__undefined());
}

static int already_run_phase_6 = false;

EXPORT void phase_6__shared_variables(void) {
  if (already_run_phase_6) return;
  already_run_phase_6 = true;
  register_collector(collect__shared_variables);
}
