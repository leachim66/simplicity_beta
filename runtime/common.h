/*
  Copyright (C) 2015 by
  Dipl.-Ing. Michael Niederle

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU Library General Public License, version 2, or
  (at your option) under the terms of the GNU Lesser General Public License,
  version 3.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU Lesser (Library) General Public License for more details.

  For details of the GNU General Public License see the accompanying
  files LGPLv2.txt and LGLPv3.txt or
  http://www.gnu.org/licenses/lgpl-2.0.html
  http://www.gnu.org/licenses/lgpl-3.0.html
  or write to the
  Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
*/

// common defines

#define false 0
#define true 1

#define ALLOCATION_SIZE(size) (((size)+sizeof(void *)-1)&-sizeof(void *))

#define MAKE_ATTRIBUTE_VALUE(node) ((NODE *)(((uintptr_t)node)+1))
#define RETRIEVE_ATTRIBUTE_VALUE(node) ((NODE *)(((uintptr_t)node)-1))
#define CONTAINS_AN_ATTRIBUTE_VALUE(node) (((uintptr_t)node)&1)

#ifndef EXPORT
  #define EXPORT
#endif

// common basic types

typedef union NODE NODE;

typedef void (*FUNC)(void);
typedef NODE *(*NODE_GETTER)(void);
typedef void (*NODE_SETTER)(NODE *);
typedef void *COLLECTOR(void *);
typedef void (*DESTRUCTOR)(void *);

// common structs

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

typedef struct DYNAMICS {
  struct OCTREE *nodes[8];
} DYNAMICS;

typedef struct SIMPLE_NODE {
  FUNC type;
  struct ATTRIBUTES *attributes;
} SIMPLE_NODE;

typedef struct CLOSURE {
  FUNC type;
  struct ATTRIBUTES *attributes;
  int parameter_count;
  struct FRAME *frame;
} CLOSURE;

typedef struct FUNCTION {
  FUNC type;
  struct ATTRIBUTES *attributes;
  int parameter_count;
} FUNCTION;

typedef struct CONTINUATION {
  FUNC type;
  struct ATTRIBUTES *attributes;
  int result_count;
  struct FRAME *frame;
  struct DYNAMICS *dynamics;
  struct FRAME *exit_frame; // used by exit-functions
} CONTINUATION;

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

union NODE {
  struct {
    FUNC type;
    struct ATTRIBUTES *attributes;
  };
  struct FUNCTION function;
  struct CLOSURE closure;
  struct CONTINUATION continuation;
  struct FUTURE future;
  struct CELL cell;
};

typedef struct FRAME {
  FUNC cont;
  struct FRAME *caller_frame;
  long caller_result_count;
  long slot_count;
  NODE *slots[0];
} FRAME;

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

// common runtime_error messages

extern int show_debug_info;
extern void debug_info(const char *msg, ...);
extern void runtime_error(const char *msg, ...);
extern void out_of_memory_error(void) __attribute__ ((noreturn));
