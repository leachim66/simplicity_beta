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

#define HASH_TABLE_SIZE 8192

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

struct ATTRIBUTE_ENTRY {
  ATTRIBUTE_ENTRY *link;
  const char *module_name;
  int id;
  int par_cnt; // used for type functions
  union {
    FUNC type; // used for type functions
    NODE *value; // used for attributes and methods
  };
};

struct SYMBOL_ENTRY {
  SYMBOL_ENTRY *link;
  VAR_TYPE type;
  const char *namespace;
  const char *module_name;
  long id; // used for dynamic variables and polymorphic functions
  NODE **var_p; // used for single-assign static variables and polymorphic functions
  NODE_GETTER getter;
  union {
    NODE_SETTER setter; // used for read-write variables
    const char *source_namespace; // used for maybe-constants
  };
  union {
    NODE_SETTER definer; // used for dynamic variables
    const char *source_name; // used for maybe-constants
  };
  const char **used_namespaces; // used for maybe-constants
  SYMBOL_ENTRY *base; // used for single-assign static variables
  ATTRIBUTE_ENTRY *attributes; // used for single-assign static variables
};

struct HASH_ENTRY {
  struct HASH_ENTRY *link;
  const char *name;
  SYMBOL_ENTRY *symbols;
};

extern const char *current_module_name;

SYMBOL_ENTRY *maybe_find_symbol(const char *namespace, const char *name);
extern HASH_ENTRY *hash_table[HASH_TABLE_SIZE];

extern void *allocate_linktime(size_t size);
