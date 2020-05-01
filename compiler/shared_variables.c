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
IMPORT void set_module(const char *name);
IMPORT void define_polymorphic_function_with_setter(
  const char *namespace, const char *name, NODE_GETTER getter, int *id_p,
  NODE **var_p
);
IMPORT NODE *from_latin_1_string(const char *str, long len);
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
static NODE_GETTER get__list;
static NODE_GETTER get_value_or_future__list;
static NODE_GETTER get__undefined;
static NODE_GETTER get_value_or_future__undefined;
static struct {
  NODE *compiler__line_no_of;
  NODE *compiler__text_of;
  NODE *compiler__source_of;
  NODE *compiler__indents_of;
  NODE *compiler__vtable_entries;
} var;
static const char *var_names[] = {
};
static int poly_idx__compiler__line_no_of;
static void type__compiler__line_no_of(void);
static NODE *get__compiler__line_no_of(void) {
  return var.compiler__line_no_of;
}
static int poly_idx__compiler__text_of;
static void type__compiler__text_of(void);
static NODE *get__compiler__text_of(void) {
  return var.compiler__text_of;
}
static int poly_idx__compiler__source_of;
static void type__compiler__source_of(void);
static NODE *get__compiler__source_of(void) {
  return var.compiler__source_of;
}
static int poly_idx__compiler__indents_of;
static void type__compiler__indents_of(void);
static NODE *get__compiler__indents_of(void) {
  return var.compiler__indents_of;
}
static int dyna_idx__compiler__required_modules;
static NODE *get__compiler__required_modules(void) {
  return get_dynamic_cell(dyna_idx__compiler__required_modules);
}
static void set__compiler__required_modules(NODE *node) {
  set_dynamic_cell(dyna_idx__compiler__required_modules, node);
}
static void define__compiler__required_modules(NODE *node) {
  define_dynamic_cell(dyna_idx__compiler__required_modules, node);
}
static int dyna_idx__compiler__used_namespaces;
static NODE *get__compiler__used_namespaces(void) {
  return get_dynamic_cell(dyna_idx__compiler__used_namespaces);
}
static void set__compiler__used_namespaces(NODE *node) {
  set_dynamic_cell(dyna_idx__compiler__used_namespaces, node);
}
static void define__compiler__used_namespaces(NODE *node) {
  define_dynamic_cell(dyna_idx__compiler__used_namespaces, node);
}
static int dyna_idx__compiler__defined_namespaces;
static NODE *get__compiler__defined_namespaces(void) {
  return get_dynamic_cell(dyna_idx__compiler__defined_namespaces);
}
static void set__compiler__defined_namespaces(NODE *node) {
  set_dynamic_cell(dyna_idx__compiler__defined_namespaces, node);
}
static void define__compiler__defined_namespaces(NODE *node) {
  define_dynamic_cell(dyna_idx__compiler__defined_namespaces, node);
}
static int dyna_idx__compiler__namespace_mappings;
static NODE *get__compiler__namespace_mappings(void) {
  return get_dynamic_cell(dyna_idx__compiler__namespace_mappings);
}
static void set__compiler__namespace_mappings(NODE *node) {
  set_dynamic_cell(dyna_idx__compiler__namespace_mappings, node);
}
static void define__compiler__namespace_mappings(NODE *node) {
  define_dynamic_cell(dyna_idx__compiler__namespace_mappings, node);
}
static int dyna_idx__compiler__included_files;
static NODE *get__compiler__included_files(void) {
  return get_dynamic_cell(dyna_idx__compiler__included_files);
}
static void set__compiler__included_files(NODE *node) {
  set_dynamic_cell(dyna_idx__compiler__included_files, node);
}
static void define__compiler__included_files(NODE *node) {
  define_dynamic_cell(dyna_idx__compiler__included_files, node);
}
static int dyna_idx__compiler__linked_libraries;
static NODE *get__compiler__linked_libraries(void) {
  return get_dynamic_cell(dyna_idx__compiler__linked_libraries);
}
static void set__compiler__linked_libraries(NODE *node) {
  set_dynamic_cell(dyna_idx__compiler__linked_libraries, node);
}
static void define__compiler__linked_libraries(NODE *node) {
  define_dynamic_cell(dyna_idx__compiler__linked_libraries, node);
}
static int dyna_idx__compiler__dependent_data;
static NODE *get__compiler__dependent_data(void) {
  return get_dynamic_cell(dyna_idx__compiler__dependent_data);
}
static void set__compiler__dependent_data(NODE *node) {
  set_dynamic_cell(dyna_idx__compiler__dependent_data, node);
}
static void define__compiler__dependent_data(NODE *node) {
  define_dynamic_cell(dyna_idx__compiler__dependent_data, node);
}
static int dyna_idx__compiler__enumeration_count;
static NODE *get__compiler__enumeration_count(void) {
  return get_dynamic_cell(dyna_idx__compiler__enumeration_count);
}
static void set__compiler__enumeration_count(NODE *node) {
  set_dynamic_cell(dyna_idx__compiler__enumeration_count, node);
}
static void define__compiler__enumeration_count(NODE *node) {
  define_dynamic_cell(dyna_idx__compiler__enumeration_count, node);
}
static int dyna_idx__compiler__global_names;
static NODE *get__compiler__global_names(void) {
  return get_dynamic_cell(dyna_idx__compiler__global_names);
}
static void set__compiler__global_names(NODE *node) {
  set_dynamic_cell(dyna_idx__compiler__global_names, node);
}
static void define__compiler__global_names(NODE *node) {
  define_dynamic_cell(dyna_idx__compiler__global_names, node);
}
static int dyna_idx__compiler__exported_names;
static NODE *get__compiler__exported_names(void) {
  return get_dynamic_cell(dyna_idx__compiler__exported_names);
}
static void set__compiler__exported_names(NODE *node) {
  set_dynamic_cell(dyna_idx__compiler__exported_names, node);
}
static void define__compiler__exported_names(NODE *node) {
  define_dynamic_cell(dyna_idx__compiler__exported_names, node);
}
static int dyna_idx__compiler__needed_names;
static NODE *get__compiler__needed_names(void) {
  return get_dynamic_cell(dyna_idx__compiler__needed_names);
}
static void set__compiler__needed_names(NODE *node) {
  set_dynamic_cell(dyna_idx__compiler__needed_names, node);
}
static void define__compiler__needed_names(NODE *node) {
  define_dynamic_cell(dyna_idx__compiler__needed_names, node);
}
static int dyna_idx__compiler__use_inline_c;
static NODE *get__compiler__use_inline_c(void) {
  return get_dynamic_cell(dyna_idx__compiler__use_inline_c);
}
static void set__compiler__use_inline_c(NODE *node) {
  set_dynamic_cell(dyna_idx__compiler__use_inline_c, node);
}
static void define__compiler__use_inline_c(NODE *node) {
  define_dynamic_cell(dyna_idx__compiler__use_inline_c, node);
}
static int dyna_idx__compiler__defined_structs;
static NODE *get__compiler__defined_structs(void) {
  return get_dynamic_cell(dyna_idx__compiler__defined_structs);
}
static void set__compiler__defined_structs(NODE *node) {
  set_dynamic_cell(dyna_idx__compiler__defined_structs, node);
}
static void define__compiler__defined_structs(NODE *node) {
  define_dynamic_cell(dyna_idx__compiler__defined_structs, node);
}
static int dyna_idx__compiler__defined_nodes;
static NODE *get__compiler__defined_nodes(void) {
  return get_dynamic_cell(dyna_idx__compiler__defined_nodes);
}
static void set__compiler__defined_nodes(NODE *node) {
  set_dynamic_cell(dyna_idx__compiler__defined_nodes, node);
}
static void define__compiler__defined_nodes(NODE *node) {
  define_dynamic_cell(dyna_idx__compiler__defined_nodes, node);
}
static int dyna_idx__compiler__defined_functions;
static NODE *get__compiler__defined_functions(void) {
  return get_dynamic_cell(dyna_idx__compiler__defined_functions);
}
static void set__compiler__defined_functions(NODE *node) {
  set_dynamic_cell(dyna_idx__compiler__defined_functions, node);
}
static void define__compiler__defined_functions(NODE *node) {
  define_dynamic_cell(dyna_idx__compiler__defined_functions, node);
}
static int dyna_idx__compiler__write_to_generated_collections;
static NODE *get__compiler__write_to_generated_collections(void) {
  return get_dynamic_slot(dyna_idx__compiler__write_to_generated_collections);
}
static void define__compiler__write_to_generated_collections(NODE *node) {
  define_dynamic_slot(dyna_idx__compiler__write_to_generated_collections, node);
}
static int dyna_idx__compiler__write_to_delayed_statements;
static NODE *get__compiler__write_to_delayed_statements(void) {
  return get_dynamic_slot(dyna_idx__compiler__write_to_delayed_statements);
}
static void define__compiler__write_to_delayed_statements(NODE *node) {
  define_dynamic_slot(dyna_idx__compiler__write_to_delayed_statements, node);
}
static int dyna_idx__compiler__use_identifier;
static NODE *get__compiler__use_identifier(void) {
  return get_dynamic_slot(dyna_idx__compiler__use_identifier);
}
static void define__compiler__use_identifier(NODE *node) {
  define_dynamic_slot(dyna_idx__compiler__use_identifier, node);
}
static int dyna_idx__compiler__write_to_declarations;
static NODE *get__compiler__write_to_declarations(void) {
  return get_dynamic_slot(dyna_idx__compiler__write_to_declarations);
}
static void define__compiler__write_to_declarations(NODE *node) {
  define_dynamic_slot(dyna_idx__compiler__write_to_declarations, node);
}
static int dyna_idx__compiler__write_to_top_level_variable_names;
static NODE *get__compiler__write_to_top_level_variable_names(void) {
  return get_dynamic_slot(dyna_idx__compiler__write_to_top_level_variable_names);
}
static void define__compiler__write_to_top_level_variable_names(NODE *node) {
  define_dynamic_slot(dyna_idx__compiler__write_to_top_level_variable_names, node);
}
static int dyna_idx__compiler__write_to_top_level_variable_declarations;
static NODE *get__compiler__write_to_top_level_variable_declarations(void) {
  return get_dynamic_slot(dyna_idx__compiler__write_to_top_level_variable_declarations);
}
static void define__compiler__write_to_top_level_variable_declarations(NODE *node) {
  define_dynamic_slot(dyna_idx__compiler__write_to_top_level_variable_declarations, node);
}
static int dyna_idx__compiler__write_to_global_variable_declarations;
static NODE *get__compiler__write_to_global_variable_declarations(void) {
  return get_dynamic_slot(dyna_idx__compiler__write_to_global_variable_declarations);
}
static void define__compiler__write_to_global_variable_declarations(NODE *node) {
  define_dynamic_slot(dyna_idx__compiler__write_to_global_variable_declarations, node);
}
static int dyna_idx__compiler__write_to_continuation_table;
static NODE *get__compiler__write_to_continuation_table(void) {
  return get_dynamic_slot(dyna_idx__compiler__write_to_continuation_table);
}
static void define__compiler__write_to_continuation_table(NODE *node) {
  define_dynamic_slot(dyna_idx__compiler__write_to_continuation_table, node);
}
static int dyna_idx__compiler__write_to_delayed_continuation_table;
static NODE *get__compiler__write_to_delayed_continuation_table(void) {
  return get_dynamic_slot(dyna_idx__compiler__write_to_delayed_continuation_table);
}
static void define__compiler__write_to_delayed_continuation_table(NODE *node) {
  define_dynamic_slot(dyna_idx__compiler__write_to_delayed_continuation_table, node);
}
static int dyna_idx__compiler__write_to_functions;
static NODE *get__compiler__write_to_functions(void) {
  return get_dynamic_slot(dyna_idx__compiler__write_to_functions);
}
static void define__compiler__write_to_functions(NODE *node) {
  define_dynamic_slot(dyna_idx__compiler__write_to_functions, node);
}
static int dyna_idx__compiler__write_to_phase_1;
static NODE *get__compiler__write_to_phase_1(void) {
  return get_dynamic_slot(dyna_idx__compiler__write_to_phase_1);
}
static void define__compiler__write_to_phase_1(NODE *node) {
  define_dynamic_slot(dyna_idx__compiler__write_to_phase_1, node);
}
static int dyna_idx__compiler__write_to_phase_2;
static NODE *get__compiler__write_to_phase_2(void) {
  return get_dynamic_slot(dyna_idx__compiler__write_to_phase_2);
}
static void define__compiler__write_to_phase_2(NODE *node) {
  define_dynamic_slot(dyna_idx__compiler__write_to_phase_2, node);
}
static int dyna_idx__compiler__write_to_phase_3;
static NODE *get__compiler__write_to_phase_3(void) {
  return get_dynamic_slot(dyna_idx__compiler__write_to_phase_3);
}
static void define__compiler__write_to_phase_3(NODE *node) {
  define_dynamic_slot(dyna_idx__compiler__write_to_phase_3, node);
}
static int dyna_idx__compiler__write_to_phase_4;
static NODE *get__compiler__write_to_phase_4(void) {
  return get_dynamic_slot(dyna_idx__compiler__write_to_phase_4);
}
static void define__compiler__write_to_phase_4(NODE *node) {
  define_dynamic_slot(dyna_idx__compiler__write_to_phase_4, node);
}
static int dyna_idx__compiler__write_to_phase_5;
static NODE *get__compiler__write_to_phase_5(void) {
  return get_dynamic_slot(dyna_idx__compiler__write_to_phase_5);
}
static void define__compiler__write_to_phase_5(NODE *node) {
  define_dynamic_slot(dyna_idx__compiler__write_to_phase_5, node);
}
static int dyna_idx__compiler__write_to_phase_6;
static NODE *get__compiler__write_to_phase_6(void) {
  return get_dynamic_slot(dyna_idx__compiler__write_to_phase_6);
}
static void define__compiler__write_to_phase_6(NODE *node) {
  define_dynamic_slot(dyna_idx__compiler__write_to_phase_6, node);
}
static int dyna_idx__compiler__use_literal;
static NODE *get__compiler__use_literal(void) {
  return get_dynamic_slot(dyna_idx__compiler__use_literal);
}
static void define__compiler__use_literal(NODE *node) {
  define_dynamic_slot(dyna_idx__compiler__use_literal, node);
}
static int dyna_idx__compiler__module_name;
static NODE *get__compiler__module_name(void) {
  return get_dynamic_slot(dyna_idx__compiler__module_name);
}
static void define__compiler__module_name(NODE *node) {
  define_dynamic_slot(dyna_idx__compiler__module_name, node);
}
static int dyna_idx__compiler__submodule_no;
static NODE *get__compiler__submodule_no(void) {
  return get_dynamic_slot(dyna_idx__compiler__submodule_no);
}
static void define__compiler__submodule_no(NODE *node) {
  define_dynamic_slot(dyna_idx__compiler__submodule_no, node);
}
static int dyna_idx__compiler__index;
static NODE *get__compiler__index(void) {
  return get_dynamic_cell(dyna_idx__compiler__index);
}
static void set__compiler__index(NODE *node) {
  set_dynamic_cell(dyna_idx__compiler__index, node);
}
static void define__compiler__index(NODE *node) {
  define_dynamic_cell(dyna_idx__compiler__index, node);
}
static int dyna_idx__compiler__definitions;
static NODE *get__compiler__definitions(void) {
  return get_dynamic_cell(dyna_idx__compiler__definitions);
}
static void set__compiler__definitions(NODE *node) {
  set_dynamic_cell(dyna_idx__compiler__definitions, node);
}
static void define__compiler__definitions(NODE *node) {
  define_dynamic_cell(dyna_idx__compiler__definitions, node);
}
static int dyna_idx__compiler__statements;
static NODE *get__compiler__statements(void) {
  return get_dynamic_cell(dyna_idx__compiler__statements);
}
static void set__compiler__statements(NODE *node) {
  set_dynamic_cell(dyna_idx__compiler__statements, node);
}
static void define__compiler__statements(NODE *node) {
  define_dynamic_cell(dyna_idx__compiler__statements, node);
}
static int dyna_idx__compiler__actions;
static NODE *get__compiler__actions(void) {
  return get_dynamic_cell(dyna_idx__compiler__actions);
}
static void set__compiler__actions(NODE *node) {
  set_dynamic_cell(dyna_idx__compiler__actions, node);
}
static void define__compiler__actions(NODE *node) {
  define_dynamic_cell(dyna_idx__compiler__actions, node);
}
static int dyna_idx__compiler__temp_idx;
static NODE *get__compiler__temp_idx(void) {
  return get_dynamic_cell(dyna_idx__compiler__temp_idx);
}
static void set__compiler__temp_idx(NODE *node) {
  set_dynamic_cell(dyna_idx__compiler__temp_idx, node);
}
static void define__compiler__temp_idx(NODE *node) {
  define_dynamic_cell(dyna_idx__compiler__temp_idx, node);
}
static int dyna_idx__compiler__current_fragment;
static NODE *get__compiler__current_fragment(void) {
  return get_dynamic_slot(dyna_idx__compiler__current_fragment);
}
static void define__compiler__current_fragment(NODE *node) {
  define_dynamic_slot(dyna_idx__compiler__current_fragment, node);
}
static int dyna_idx__compiler__already_defined_names;
static NODE *get__compiler__already_defined_names(void) {
  return get_dynamic_slot(dyna_idx__compiler__already_defined_names);
}
static void define__compiler__already_defined_names(NODE *node) {
  define_dynamic_slot(dyna_idx__compiler__already_defined_names, node);
}
static int dyna_idx__compiler__defined_names;
static NODE *get__compiler__defined_names(void) {
  return get_dynamic_cell(dyna_idx__compiler__defined_names);
}
static void set__compiler__defined_names(NODE *node) {
  set_dynamic_cell(dyna_idx__compiler__defined_names, node);
}
static void define__compiler__defined_names(NODE *node) {
  define_dynamic_cell(dyna_idx__compiler__defined_names, node);
}
static int dyna_idx__compiler__used_names;
static NODE *get__compiler__used_names(void) {
  return get_dynamic_cell(dyna_idx__compiler__used_names);
}
static void set__compiler__used_names(NODE *node) {
  set_dynamic_cell(dyna_idx__compiler__used_names, node);
}
static void define__compiler__used_names(NODE *node) {
  define_dynamic_cell(dyna_idx__compiler__used_names, node);
}
static int dyna_idx__compiler__assigned_names;
static NODE *get__compiler__assigned_names(void) {
  return get_dynamic_cell(dyna_idx__compiler__assigned_names);
}
static void set__compiler__assigned_names(NODE *node) {
  set_dynamic_cell(dyna_idx__compiler__assigned_names, node);
}
static void define__compiler__assigned_names(NODE *node) {
  define_dynamic_cell(dyna_idx__compiler__assigned_names, node);
}
static int dyna_idx__compiler__used_string_literals;
static NODE *get__compiler__used_string_literals(void) {
  return get_dynamic_cell(dyna_idx__compiler__used_string_literals);
}
static void set__compiler__used_string_literals(NODE *node) {
  set_dynamic_cell(dyna_idx__compiler__used_string_literals, node);
}
static void define__compiler__used_string_literals(NODE *node) {
  define_dynamic_cell(dyna_idx__compiler__used_string_literals, node);
}
static int dyna_idx__compiler__current_continuation_info;
static NODE *get__compiler__current_continuation_info(void) {
  return get_dynamic_cell(dyna_idx__compiler__current_continuation_info);
}
static void set__compiler__current_continuation_info(NODE *node) {
  set_dynamic_cell(dyna_idx__compiler__current_continuation_info, node);
}
static void define__compiler__current_continuation_info(NODE *node) {
  define_dynamic_cell(dyna_idx__compiler__current_continuation_info, node);
}
static int dyna_idx__compiler__string_literals;
static NODE *get__compiler__string_literals(void) {
  return get_dynamic_cell(dyna_idx__compiler__string_literals);
}
static void set__compiler__string_literals(NODE *node) {
  set_dynamic_cell(dyna_idx__compiler__string_literals, node);
}
static void define__compiler__string_literals(NODE *node) {
  define_dynamic_cell(dyna_idx__compiler__string_literals, node);
}
static NODE *get__compiler__vtable_entries(void) {
  return var.compiler__vtable_entries;
}
static NODE *string__a0540e55151930c2;
static NODE *string__72a8a8c9865d0296;
static NODE *string__72a8a8c9864d0292;
static NODE *string__72a8a8c986650294;
static NODE *string__7ca8ae498474c298;
static NODE *string__724c23a6148be573;
static NODE *string__724c23a6149be577;
static NODE *string__724c23a614b3e571;
static NODE *string__3730b49a2bb3f253;
static NODE *string__b6540e1515c13096;
static NODE *string__261f540a81caa2a3;
static NODE *string__aa540e1515c9309d;
static NODE *string__444c262e96638520;
static NODE *string__a4214b121078eb22;
static NODE *string__464c27eb16a34536;
static NODE *string__5af91691bb71fca7;
static NODE *string__7e88296f0e7a3463;
static NODE *string__541f558a01dab2b3;
static NODE *string__ee216a04cf7d466f;
static void cont__104_20(void);
void run__shared_variables(void);

static CONTINUATION_INFO continuation_info[] = {
  {type__compiler__line_no_of, NULL, 31, 31, 2, 21},
  {type__compiler__text_of, NULL, 32, 32, 2, 18},
  {type__compiler__source_of, NULL, 33, 33, 2, 20},
  {type__compiler__indents_of, NULL, 34, 34, 2, 21},
  {run__shared_variables, NULL, 114, 134, 1, 19},
  {cont__104_20, NULL, }
};

union NODE {
  struct {
    FUNC type;
    ATTRIBUTES *attributes;
  };
  CONTINUATION continuation;
  CLOSURE closure;
};
static void type__compiler__line_no_of(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__compiler__line_no_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__compiler__line_no_of, attr);
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
static void type__compiler__text_of(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__compiler__text_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__compiler__text_of, attr);
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
static void type__compiler__source_of(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__compiler__source_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__compiler__source_of, attr);
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
static void type__compiler__indents_of(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__compiler__indents_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__compiler__indents_of, attr);
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
  "compiler",
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
  // 38: %%compiler::required_modules undefined # a table
  set__compiler__required_modules(get__undefined());
  // 39: %%compiler::used_namespaces undefined # a set
  set__compiler__used_namespaces(get__undefined());
  // 40: %%compiler::defined_namespaces undefined # a set
  set__compiler__defined_namespaces(get__undefined());
  // 41: %%compiler::namespace_mappings undefined # a table
  set__compiler__namespace_mappings(get__undefined());
  // 42: %%compiler::included_files undefined # a set
  set__compiler__included_files(get__undefined());
  // 43: %%compiler::linked_libraries undefined # a set
  set__compiler__linked_libraries(get__undefined());
  // 44: %%compiler::dependent_data undefined # a set
  set__compiler__dependent_data(get__undefined());
  // 48: %%compiler::enumeration_count undefined # an integer
  set__compiler__enumeration_count(get__undefined());
  // 52: %%compiler::global_names undefined # module global names
  set__compiler__global_names(get__undefined());
  // 53: %%compiler::exported_names undefined # first index: name; second index: namespace
  set__compiler__exported_names(get__undefined());
  // 54: %%compiler::needed_names undefined # contains all symbols that are imported
  set__compiler__needed_names(get__undefined());
  // 58: %%compiler::use_inline_c undefined
  set__compiler__use_inline_c(get__undefined());
  // 59: %%compiler::defined_structs undefined
  set__compiler__defined_structs(get__undefined());
  // 60: %%compiler::defined_nodes undefined
  set__compiler__defined_nodes(get__undefined());
  // 61: %%compiler::defined_functions undefined
  set__compiler__defined_functions(get__undefined());
  // 65: %compiler::write_to_generated_collections undefined
  initialize_maybe_future(get__compiler__write_to_generated_collections(), get__undefined());
  // 66: %compiler::write_to_delayed_statements undefined
  initialize_maybe_future(get__compiler__write_to_delayed_statements(), get__undefined());
  // 67: %compiler::use_identifier undefined
  initialize_maybe_future(get__compiler__use_identifier(), get__undefined());
  // 68: %compiler::write_to_declarations undefined
  initialize_maybe_future(get__compiler__write_to_declarations(), get__undefined());
  // 69: %compiler::write_to_top_level_variable_names undefined
  initialize_maybe_future(get__compiler__write_to_top_level_variable_names(), get__undefined());
  // 70: %compiler::write_to_top_level_variable_declarations undefined
  initialize_maybe_future(get__compiler__write_to_top_level_variable_declarations(), get__undefined());
  // 71: %compiler::write_to_global_variable_declarations undefined
  initialize_maybe_future(get__compiler__write_to_global_variable_declarations(), get__undefined());
  // 72: %compiler::write_to_continuation_table undefined
  initialize_maybe_future(get__compiler__write_to_continuation_table(), get__undefined());
  // 73: %compiler::write_to_delayed_continuation_table undefined
  initialize_maybe_future(get__compiler__write_to_delayed_continuation_table(), get__undefined());
  // 74: %compiler::write_to_functions undefined
  initialize_maybe_future(get__compiler__write_to_functions(), get__undefined());
  // 75: %compiler::write_to_phase_1 undefined
  initialize_maybe_future(get__compiler__write_to_phase_1(), get__undefined());
  // 76: %compiler::write_to_phase_2 undefined
  initialize_maybe_future(get__compiler__write_to_phase_2(), get__undefined());
  // 77: %compiler::write_to_phase_3 undefined
  initialize_maybe_future(get__compiler__write_to_phase_3(), get__undefined());
  // 78: %compiler::write_to_phase_4 undefined
  initialize_maybe_future(get__compiler__write_to_phase_4(), get__undefined());
  // 79: %compiler::write_to_phase_5 undefined
  initialize_maybe_future(get__compiler__write_to_phase_5(), get__undefined());
  // 80: %compiler::write_to_phase_6 undefined
  initialize_maybe_future(get__compiler__write_to_phase_6(), get__undefined());
  // 81: %compiler::use_literal undefined
  initialize_maybe_future(get__compiler__use_literal(), get__undefined());
  // 85: %compiler::module_name undefined # the name of the current compilation unit
  initialize_maybe_future(get__compiler__module_name(), get__undefined());
  // 86: %compiler::submodule_no undefined
  initialize_maybe_future(get__compiler__submodule_no(), get__undefined());
  // 88: %%compiler::index undefined # used for enumerating expanded source code items
  set__compiler__index(get__undefined());
  // 89: %%compiler::definitions undefined # a list of key-value pairs
  set__compiler__definitions(get__undefined());
  // 90: %%compiler::statements undefined # a list of statements
  set__compiler__statements(get__undefined());
  // 91: %%compiler::actions undefined # a list of deferred actions (closures)
  set__compiler__actions(get__undefined());
  // 92: %%compiler::temp_idx undefined
  set__compiler__temp_idx(get__undefined());
  // 94: %compiler::current_fragment undefined # used for generating error messages
  initialize_maybe_future(get__compiler__current_fragment(), get__undefined());
  // 95: %compiler::already_defined_names undefined
  initialize_maybe_future(get__compiler__already_defined_names(), get__undefined());
  // 97: %%compiler::defined_names undefined # used for collecting defined symbols
  set__compiler__defined_names(get__undefined());
  // 98: %%compiler::used_names undefined # used for collecting usages of symbols
  set__compiler__used_names(get__undefined());
  // 99: %%compiler::assigned_names undefined
  set__compiler__assigned_names(get__undefined());
  // 103: %%compiler::used_string_literals undefined
  set__compiler__used_string_literals(get__undefined());
  // 105: %%compiler::current_continuation_info undefined
  set__compiler__current_continuation_info(get__undefined());
  // 108: %%compiler::string_literals undefined
  set__compiler__string_literals(get__undefined());
  // 114: $compiler::vtable_entries
  // 115:   list
  // 116:     "to_int8"
  // 117:     "to_int16"
  // 118:     "to_int32"
  // 119:     "to_int64"
  // 120:     "to_uint8"
  // 121:     "to_uint16"
  // 122:     "to_uint32"
  // 123:     "to_uint64"
  // ...
  argument_count = 19;
  arguments = node_p;
  arguments->slots[0] = string__a0540e55151930c2;
  arguments->slots[1] = string__72a8a8c9865d0296;
  arguments->slots[2] = string__72a8a8c9864d0292;
  arguments->slots[3] = string__72a8a8c986650294;
  arguments->slots[4] = string__7ca8ae498474c298;
  arguments->slots[5] = string__724c23a6148be573;
  arguments->slots[6] = string__724c23a6149be577;
  arguments->slots[7] = string__724c23a614b3e571;
  arguments->slots[8] = string__3730b49a2bb3f253;
  arguments->slots[9] = string__b6540e1515c13096;
  arguments->slots[10] = string__261f540a81caa2a3;
  arguments->slots[11] = string__aa540e1515c9309d;
  arguments->slots[12] = string__444c262e96638520;
  arguments->slots[13] = string__a4214b121078eb22;
  arguments->slots[14] = string__464c27eb16a34536;
  arguments->slots[15] = string__5af91691bb71fca7;
  arguments->slots[16] = string__7e88296f0e7a3463;
  arguments->slots[17] = string__541f558a01dab2b3;
  arguments->slots[18] = string__ee216a04cf7d466f;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__104_20;
}
static void cont__104_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var.compiler__vtable_entries, arguments->slots[0]);
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
EXPORT void collect__shared_variables(void) {
  var.compiler__line_no_of = collect_node(var.compiler__line_no_of);
  var.compiler__text_of = collect_node(var.compiler__text_of);
  var.compiler__source_of = collect_node(var.compiler__source_of);
  var.compiler__indents_of = collect_node(var.compiler__indents_of);
  var.compiler__vtable_entries = collect_node(var.compiler__vtable_entries);
}

static int already_run_phase_1 = false;

EXPORT void phase_1__shared_variables(void) {
  if (already_run_phase_1) return;
  already_run_phase_1 = true;
  register_module_info(&module_info);
}

static int already_run_phase_2 = false;

EXPORT void phase_2__shared_variables(void) {
  if (already_run_phase_2) return;
  already_run_phase_2 = true;
  set_module("shared_variables");
  define_polymorphic_function_with_setter("compiler", "line_no_of", get__compiler__line_no_of, &poly_idx__compiler__line_no_of, &var.compiler__line_no_of);
  define_polymorphic_function_with_setter("compiler", "text_of", get__compiler__text_of, &poly_idx__compiler__text_of, &var.compiler__text_of);
  define_polymorphic_function_with_setter("compiler", "source_of", get__compiler__source_of, &poly_idx__compiler__source_of, &var.compiler__source_of);
  define_polymorphic_function_with_setter("compiler", "indents_of", get__compiler__indents_of, &poly_idx__compiler__indents_of, &var.compiler__indents_of);
  string__a0540e55151930c2 = from_latin_1_string("to_int8", 7);
  string__72a8a8c9865d0296 = from_latin_1_string("to_int16", 8);
  string__72a8a8c9864d0292 = from_latin_1_string("to_int32", 8);
  string__72a8a8c986650294 = from_latin_1_string("to_int64", 8);
  string__7ca8ae498474c298 = from_latin_1_string("to_uint8", 8);
  string__724c23a6148be573 = from_latin_1_string("to_uint16", 9);
  string__724c23a6149be577 = from_latin_1_string("to_uint32", 9);
  string__724c23a614b3e571 = from_latin_1_string("to_uint64", 9);
  string__3730b49a2bb3f253 = from_latin_1_string("to_uchar32", 10);
  string__b6540e1515c13096 = from_latin_1_string("to_bool", 7);
  string__261f540a81caa2a3 = from_latin_1_string("to_int", 6);
  string__aa540e1515c9309d = from_latin_1_string("to_long", 7);
  string__444c262e96638520 = from_latin_1_string("to_double", 9);
  string__a4214b121078eb22 = from_latin_1_string("to_c_string", 11);
  string__464c27eb16a34536 = from_latin_1_string("to_octets", 9);
  string__5af91691bb71fca7 = from_latin_1_string("get_item_of", 11);
  string__7e88296f0e7a3463 = from_latin_1_string("length_of", 9);
  string__541f558a01dab2b3 = from_latin_1_string("unfold", 6);
  string__ee216a04cf7d466f = from_latin_1_string("debug_string", 12);
}

static int already_run_phase_3 = false;

EXPORT void phase_3__shared_variables(void) {
  if (already_run_phase_3) return;
  already_run_phase_3 = true;
  set_module("shared_variables");
  set_used_namespaces(used_namespaces);
  define_multi_assign_dynamic("compiler", "required_modules", get__compiler__required_modules, set__compiler__required_modules, define__compiler__required_modules, &dyna_idx__compiler__required_modules);
  define__compiler__required_modules(undefined);
  define_multi_assign_dynamic("compiler", "used_namespaces", get__compiler__used_namespaces, set__compiler__used_namespaces, define__compiler__used_namespaces, &dyna_idx__compiler__used_namespaces);
  define__compiler__used_namespaces(undefined);
  define_multi_assign_dynamic("compiler", "defined_namespaces", get__compiler__defined_namespaces, set__compiler__defined_namespaces, define__compiler__defined_namespaces, &dyna_idx__compiler__defined_namespaces);
  define__compiler__defined_namespaces(undefined);
  define_multi_assign_dynamic("compiler", "namespace_mappings", get__compiler__namespace_mappings, set__compiler__namespace_mappings, define__compiler__namespace_mappings, &dyna_idx__compiler__namespace_mappings);
  define__compiler__namespace_mappings(undefined);
  define_multi_assign_dynamic("compiler", "included_files", get__compiler__included_files, set__compiler__included_files, define__compiler__included_files, &dyna_idx__compiler__included_files);
  define__compiler__included_files(undefined);
  define_multi_assign_dynamic("compiler", "linked_libraries", get__compiler__linked_libraries, set__compiler__linked_libraries, define__compiler__linked_libraries, &dyna_idx__compiler__linked_libraries);
  define__compiler__linked_libraries(undefined);
  define_multi_assign_dynamic("compiler", "dependent_data", get__compiler__dependent_data, set__compiler__dependent_data, define__compiler__dependent_data, &dyna_idx__compiler__dependent_data);
  define__compiler__dependent_data(undefined);
  define_multi_assign_dynamic("compiler", "enumeration_count", get__compiler__enumeration_count, set__compiler__enumeration_count, define__compiler__enumeration_count, &dyna_idx__compiler__enumeration_count);
  define__compiler__enumeration_count(undefined);
  define_multi_assign_dynamic("compiler", "global_names", get__compiler__global_names, set__compiler__global_names, define__compiler__global_names, &dyna_idx__compiler__global_names);
  define__compiler__global_names(undefined);
  define_multi_assign_dynamic("compiler", "exported_names", get__compiler__exported_names, set__compiler__exported_names, define__compiler__exported_names, &dyna_idx__compiler__exported_names);
  define__compiler__exported_names(undefined);
  define_multi_assign_dynamic("compiler", "needed_names", get__compiler__needed_names, set__compiler__needed_names, define__compiler__needed_names, &dyna_idx__compiler__needed_names);
  define__compiler__needed_names(undefined);
  define_multi_assign_dynamic("compiler", "use_inline_c", get__compiler__use_inline_c, set__compiler__use_inline_c, define__compiler__use_inline_c, &dyna_idx__compiler__use_inline_c);
  define__compiler__use_inline_c(undefined);
  define_multi_assign_dynamic("compiler", "defined_structs", get__compiler__defined_structs, set__compiler__defined_structs, define__compiler__defined_structs, &dyna_idx__compiler__defined_structs);
  define__compiler__defined_structs(undefined);
  define_multi_assign_dynamic("compiler", "defined_nodes", get__compiler__defined_nodes, set__compiler__defined_nodes, define__compiler__defined_nodes, &dyna_idx__compiler__defined_nodes);
  define__compiler__defined_nodes(undefined);
  define_multi_assign_dynamic("compiler", "defined_functions", get__compiler__defined_functions, set__compiler__defined_functions, define__compiler__defined_functions, &dyna_idx__compiler__defined_functions);
  define__compiler__defined_functions(undefined);
  define_single_assign_dynamic("compiler", "write_to_generated_collections", get__compiler__write_to_generated_collections, define__compiler__write_to_generated_collections, &dyna_idx__compiler__write_to_generated_collections);
  define__compiler__write_to_generated_collections(create_future());
  define_single_assign_dynamic("compiler", "write_to_delayed_statements", get__compiler__write_to_delayed_statements, define__compiler__write_to_delayed_statements, &dyna_idx__compiler__write_to_delayed_statements);
  define__compiler__write_to_delayed_statements(create_future());
  define_single_assign_dynamic("compiler", "use_identifier", get__compiler__use_identifier, define__compiler__use_identifier, &dyna_idx__compiler__use_identifier);
  define__compiler__use_identifier(create_future());
  define_single_assign_dynamic("compiler", "write_to_declarations", get__compiler__write_to_declarations, define__compiler__write_to_declarations, &dyna_idx__compiler__write_to_declarations);
  define__compiler__write_to_declarations(create_future());
  define_single_assign_dynamic("compiler", "write_to_top_level_variable_names", get__compiler__write_to_top_level_variable_names, define__compiler__write_to_top_level_variable_names, &dyna_idx__compiler__write_to_top_level_variable_names);
  define__compiler__write_to_top_level_variable_names(create_future());
  define_single_assign_dynamic("compiler", "write_to_top_level_variable_declarations", get__compiler__write_to_top_level_variable_declarations, define__compiler__write_to_top_level_variable_declarations, &dyna_idx__compiler__write_to_top_level_variable_declarations);
  define__compiler__write_to_top_level_variable_declarations(create_future());
  define_single_assign_dynamic("compiler", "write_to_global_variable_declarations", get__compiler__write_to_global_variable_declarations, define__compiler__write_to_global_variable_declarations, &dyna_idx__compiler__write_to_global_variable_declarations);
  define__compiler__write_to_global_variable_declarations(create_future());
  define_single_assign_dynamic("compiler", "write_to_continuation_table", get__compiler__write_to_continuation_table, define__compiler__write_to_continuation_table, &dyna_idx__compiler__write_to_continuation_table);
  define__compiler__write_to_continuation_table(create_future());
  define_single_assign_dynamic("compiler", "write_to_delayed_continuation_table", get__compiler__write_to_delayed_continuation_table, define__compiler__write_to_delayed_continuation_table, &dyna_idx__compiler__write_to_delayed_continuation_table);
  define__compiler__write_to_delayed_continuation_table(create_future());
  define_single_assign_dynamic("compiler", "write_to_functions", get__compiler__write_to_functions, define__compiler__write_to_functions, &dyna_idx__compiler__write_to_functions);
  define__compiler__write_to_functions(create_future());
  define_single_assign_dynamic("compiler", "write_to_phase_1", get__compiler__write_to_phase_1, define__compiler__write_to_phase_1, &dyna_idx__compiler__write_to_phase_1);
  define__compiler__write_to_phase_1(create_future());
  define_single_assign_dynamic("compiler", "write_to_phase_2", get__compiler__write_to_phase_2, define__compiler__write_to_phase_2, &dyna_idx__compiler__write_to_phase_2);
  define__compiler__write_to_phase_2(create_future());
  define_single_assign_dynamic("compiler", "write_to_phase_3", get__compiler__write_to_phase_3, define__compiler__write_to_phase_3, &dyna_idx__compiler__write_to_phase_3);
  define__compiler__write_to_phase_3(create_future());
  define_single_assign_dynamic("compiler", "write_to_phase_4", get__compiler__write_to_phase_4, define__compiler__write_to_phase_4, &dyna_idx__compiler__write_to_phase_4);
  define__compiler__write_to_phase_4(create_future());
  define_single_assign_dynamic("compiler", "write_to_phase_5", get__compiler__write_to_phase_5, define__compiler__write_to_phase_5, &dyna_idx__compiler__write_to_phase_5);
  define__compiler__write_to_phase_5(create_future());
  define_single_assign_dynamic("compiler", "write_to_phase_6", get__compiler__write_to_phase_6, define__compiler__write_to_phase_6, &dyna_idx__compiler__write_to_phase_6);
  define__compiler__write_to_phase_6(create_future());
  define_single_assign_dynamic("compiler", "use_literal", get__compiler__use_literal, define__compiler__use_literal, &dyna_idx__compiler__use_literal);
  define__compiler__use_literal(create_future());
  define_single_assign_dynamic("compiler", "module_name", get__compiler__module_name, define__compiler__module_name, &dyna_idx__compiler__module_name);
  define__compiler__module_name(create_future());
  define_single_assign_dynamic("compiler", "submodule_no", get__compiler__submodule_no, define__compiler__submodule_no, &dyna_idx__compiler__submodule_no);
  define__compiler__submodule_no(create_future());
  define_multi_assign_dynamic("compiler", "index", get__compiler__index, set__compiler__index, define__compiler__index, &dyna_idx__compiler__index);
  define__compiler__index(undefined);
  define_multi_assign_dynamic("compiler", "definitions", get__compiler__definitions, set__compiler__definitions, define__compiler__definitions, &dyna_idx__compiler__definitions);
  define__compiler__definitions(undefined);
  define_multi_assign_dynamic("compiler", "statements", get__compiler__statements, set__compiler__statements, define__compiler__statements, &dyna_idx__compiler__statements);
  define__compiler__statements(undefined);
  define_multi_assign_dynamic("compiler", "actions", get__compiler__actions, set__compiler__actions, define__compiler__actions, &dyna_idx__compiler__actions);
  define__compiler__actions(undefined);
  define_multi_assign_dynamic("compiler", "temp_idx", get__compiler__temp_idx, set__compiler__temp_idx, define__compiler__temp_idx, &dyna_idx__compiler__temp_idx);
  define__compiler__temp_idx(undefined);
  define_single_assign_dynamic("compiler", "current_fragment", get__compiler__current_fragment, define__compiler__current_fragment, &dyna_idx__compiler__current_fragment);
  define__compiler__current_fragment(create_future());
  define_single_assign_dynamic("compiler", "already_defined_names", get__compiler__already_defined_names, define__compiler__already_defined_names, &dyna_idx__compiler__already_defined_names);
  define__compiler__already_defined_names(create_future());
  define_multi_assign_dynamic("compiler", "defined_names", get__compiler__defined_names, set__compiler__defined_names, define__compiler__defined_names, &dyna_idx__compiler__defined_names);
  define__compiler__defined_names(undefined);
  define_multi_assign_dynamic("compiler", "used_names", get__compiler__used_names, set__compiler__used_names, define__compiler__used_names, &dyna_idx__compiler__used_names);
  define__compiler__used_names(undefined);
  define_multi_assign_dynamic("compiler", "assigned_names", get__compiler__assigned_names, set__compiler__assigned_names, define__compiler__assigned_names, &dyna_idx__compiler__assigned_names);
  define__compiler__assigned_names(undefined);
  define_multi_assign_dynamic("compiler", "used_string_literals", get__compiler__used_string_literals, set__compiler__used_string_literals, define__compiler__used_string_literals, &dyna_idx__compiler__used_string_literals);
  define__compiler__used_string_literals(undefined);
  define_multi_assign_dynamic("compiler", "current_continuation_info", get__compiler__current_continuation_info, set__compiler__current_continuation_info, define__compiler__current_continuation_info, &dyna_idx__compiler__current_continuation_info);
  define__compiler__current_continuation_info(undefined);
  define_multi_assign_dynamic("compiler", "string_literals", get__compiler__string_literals, set__compiler__string_literals, define__compiler__string_literals, &dyna_idx__compiler__string_literals);
  define__compiler__string_literals(undefined);
  define_single_assign_static("compiler", "vtable_entries", get__compiler__vtable_entries, &var.compiler__vtable_entries);
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
  assign_value(&var.compiler__line_no_of, create_function(type__compiler__line_no_of, -1));
  assign_value(&var.compiler__text_of, create_function(type__compiler__text_of, -1));
  assign_value(&var.compiler__source_of, create_function(type__compiler__source_of, -1));
  assign_value(&var.compiler__indents_of, create_function(type__compiler__indents_of, -1));
  maybe_initialize_future(get__compiler__write_to_generated_collections(), get__undefined());
  maybe_initialize_future(get__compiler__write_to_delayed_statements(), get__undefined());
  maybe_initialize_future(get__compiler__use_identifier(), get__undefined());
  maybe_initialize_future(get__compiler__write_to_declarations(), get__undefined());
  maybe_initialize_future(get__compiler__write_to_top_level_variable_names(), get__undefined());
  maybe_initialize_future(get__compiler__write_to_top_level_variable_declarations(), get__undefined());
  maybe_initialize_future(get__compiler__write_to_global_variable_declarations(), get__undefined());
  maybe_initialize_future(get__compiler__write_to_continuation_table(), get__undefined());
  maybe_initialize_future(get__compiler__write_to_delayed_continuation_table(), get__undefined());
  maybe_initialize_future(get__compiler__write_to_functions(), get__undefined());
  maybe_initialize_future(get__compiler__write_to_phase_1(), get__undefined());
  maybe_initialize_future(get__compiler__write_to_phase_2(), get__undefined());
  maybe_initialize_future(get__compiler__write_to_phase_3(), get__undefined());
  maybe_initialize_future(get__compiler__write_to_phase_4(), get__undefined());
  maybe_initialize_future(get__compiler__write_to_phase_5(), get__undefined());
  maybe_initialize_future(get__compiler__write_to_phase_6(), get__undefined());
  maybe_initialize_future(get__compiler__use_literal(), get__undefined());
  maybe_initialize_future(get__compiler__module_name(), get__undefined());
  maybe_initialize_future(get__compiler__submodule_no(), get__undefined());
  maybe_initialize_future(get__compiler__current_fragment(), get__undefined());
  maybe_initialize_future(get__compiler__already_defined_names(), get__undefined());
}

static int already_run_phase_6 = false;

EXPORT void phase_6__shared_variables(void) {
  if (already_run_phase_6) return;
  already_run_phase_6 = true;
  register_collector(collect__shared_variables);
}
