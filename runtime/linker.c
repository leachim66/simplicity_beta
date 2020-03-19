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

#define RUNTIME_MAJOR_VERSION 2
// denotes a runtime API change

#define RUNTIME_MINOR_VERSION 0
// denotes a runtime API extension

#define RUNTIME_REVISION 0
// denotes an internal change in the runtime library

#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "linker.h"

char *var_type[] = {
  "polymorphic function",
  "single assign static",
  "multi assign static",
  "single assign dynamic",
  "multi assign dynamic",
};

EXPORT int runtime_major_version(void) {
  return RUNTIME_MAJOR_VERSION;
}

EXPORT int runtime_minor_version(void) {
  return RUNTIME_MINOR_VERSION;
}

EXPORT int runtime_revision(void) {
  return RUNTIME_REVISION;
}

HASH_ENTRY *hash_table[HASH_TABLE_SIZE];

// reserve 8 IDs for privileged functions
EXPORT int polymorphic_function_count = 8;
  // is incremented in steps of 2
  // all even IDs are polymorphic functions without a setter
EXPORT int polymorphic_function_with_setter_count = 9;
  // is incremented in steps of 2
  // all odd IDs are polymorphic functions with a setter

int polymorphic_function_table_size = 0;
static int dyna_idx = 0;

EXPORT const char **polymorphic_function_names;

const char *current_module_name;

EXPORT void set_module(const char *name) {
  debug_info("set current module to \"%s\"\n", name);
  current_module_name = name;
}

MODULE_INFO *module_infos = NULL;

EXPORT void register_module_info(MODULE_INFO *info) {
  debug_info("register module \"%s\"\n", info->name);
  info->link = module_infos;
  module_infos = info;
  current_module_name = info->name;
}

static const char **current_namespaces;

EXPORT void set_used_namespaces(const char **namespaces) {
  current_namespaces = namespaces;
  if (show_debug_info) {
    fprintf(stderr, "set current namespaces:\n");
    while (*namespaces) fprintf(stderr, "  %s\n", *namespaces++);
  }
}

#define rol(val, shift) ((((unsigned)(val))<<(shift))|(((unsigned)(val))>>(32-(shift))))

__attribute__ ((noreturn)) void unrecoverable_error(const char *msg, ...);

void *allocate_linktime(size_t size) {
  void *p = malloc(size);
  if (!p) unrecoverable_error("OUT OF MEMORY WHILE LINKING!");
  return p;
}

static void *reallocate_linktime(void *buf, size_t size) {
  void *p = realloc(buf, size);
  if (!p) unrecoverable_error("OUT OF MEMORY WHILE LINKING!");
  return p;
}

static void free_all_linktime_memory() {
}

static SYMBOL_ENTRY *define_symbol(
  VAR_TYPE type, const char *namespace, const char *name
) {
  uint32_t h = 0;
  const char *p = name;
  while (*p) {
    h = rol(h, 5)^*p++;
  }
  h &= HASH_TABLE_SIZE-1;

  HASH_ENTRY *hep = hash_table[h];
  while (hep) {
    if (strcmp(hep->name, name) == 0) break;
    hep = hep->link;
  }
  SYMBOL_ENTRY *sep;
  if (hep) {
    sep = hep->symbols;
    while (sep) {
      if (strcmp(sep->namespace, namespace) == 0) {
	unrecoverable_error(
	  "The symbol \"%s::%s\" already defined in the module \"%s\" as a %s is "
	  "defined again in the module \"%s\" as a %s!",
	  namespace, name, sep->module_name, var_type[sep->type],
	  current_module_name, var_type[type]);
      }
      sep = sep->link;
    }
  } else {
    hep = allocate_linktime(sizeof(HASH_ENTRY));
    hep->link = hash_table[h];
    hep->name = name;
    hep->symbols = NULL;
    hash_table[h] = hep;
  }
  sep = allocate_linktime(sizeof(SYMBOL_ENTRY));
  sep->link = hep->symbols;
  sep->type = type;
  sep->namespace = namespace;
  sep->module_name = current_module_name;
  sep->base = NULL;
  sep->attributes = NULL;
  hep->symbols = sep;
  return sep;
}

static SYMBOL_ENTRY *find_symbol(const char *namespace, const char *name) {
  uint32_t h = 0;
  const char *p = name;
  while (*p) {
    h = rol(h, 5)^*p++;
  }
  h &= HASH_TABLE_SIZE-1;

  HASH_ENTRY *hep = hash_table[h];
  while (hep) {
    if (strcmp(hep->name, name) == 0) break;
    hep = hep->link;
  }
  if (namespace) {
    if (hep) {
      SYMBOL_ENTRY *sep = hep->symbols;
      while (sep) {
	if (strcmp(namespace, sep->namespace) == 0) return sep;
	sep = sep->link;
      }
    }
    unrecoverable_error(
      "The symbol \"%s::%s\" needed by the module \"%s\" is not defined!",
      namespace, name, current_module_name);
  } else {
    if (!hep) {
      unrecoverable_error(
	"The symbol \"%s\" needed by the module \"%s\" is not defined in any "
	"namespace!",
	name, current_module_name);
    }

    const char **namespaces;
    SYMBOL_ENTRY *sep = hep->symbols;
    SYMBOL_ENTRY *found_sep = NULL;
    do {
      namespaces = current_namespaces;
      while (*namespaces) {
	if (strcmp(sep->namespace, *namespaces++) == 0) {
	  if (found_sep) {
	    unrecoverable_error(
	      "The symbol \"%s\" needed by the module \"%s\" is defined in at "
	      "least two used namespaces(\"%s\" and \"%s\")!",
	      name, current_module_name, found_sep->namespace, sep->namespace);
	  }
	  found_sep = sep;
	  break;
	}
      };
      sep = sep->link;
    } while (sep);
    if (found_sep) return found_sep;

    fprintf(stderr,
      "The symbol \"%s\" needed by the module \"%s\" is not defined in any "
      "used namespace(",
      name, current_module_name);
    int something_printed = 0;
    namespaces = current_namespaces;
    while (*namespaces) {
      if (something_printed) {
	fprintf(stderr, ", ");
      }
      fprintf(stderr, "\"%s\"", *namespaces++);
      something_printed = 1;
    }
    fprintf(stderr, ")!\n");
    exit(EXIT_FAILURE);
  }
}

SYMBOL_ENTRY *maybe_find_symbol(const char *namespace, const char *name) {
  uint32_t h = 0;
  const char *p = name;
  while (*p) {
    h = rol(h, 5)^*p++;
  }
  h &= HASH_TABLE_SIZE-1;

  HASH_ENTRY *hep = hash_table[h];
  while (hep) {
    if (strcmp(hep->name, name) == 0) break;
    hep = hep->link;
  }
  if (hep) {
    SYMBOL_ENTRY *sep = hep->symbols;
    while (sep) {
      if (strcmp(namespace, sep->namespace) == 0) return sep;
      sep = sep->link;
    }
  }
  return NULL;
}

static void symbol_info(const char *msg, ...) {
  if (show_debug_info) {
    va_list args;
    va_start(args, msg);
    vfprintf(stderr, msg, args);
    fprintf(stderr, " in module \"%s\"\n", current_module_name);
    va_end(args);
  }
}

static void symbol_info_1(const char *msg, const char *namespace, const char *name) {
  if (show_debug_info) {
    if (namespace) {
      fprintf(stderr, "%s \"%s::%s\"", msg, namespace, name);
    } else {
      fprintf(stderr, "%s \"%s\"", msg, name);
    }
    fprintf(stderr, " in module \"%s\"\n", current_module_name);
  }
}

static void symbol_info_2(
  const char *msg_1, const char *namespace_1, const char *name_1,
  const char *msg_2, const char *name_2
) {
  if (show_debug_info) {
    if (namespace_1) {
      fprintf(stderr, "%s \"%s::%s", msg_1, namespace_1, name_1);
    } else {
      fprintf(stderr, "%s \"%s", msg_1, name_1);
    }
    fprintf(
      stderr, "%s%s\" in module \"%s\"\n",
      msg_2, name_2, current_module_name);
  }
}

void undefined_c_function(void) {
  unrecoverable_error("Attempt to call an undefined C-function!");
}

NODE *(*func__from_bool)(int val) = (void *)undefined_c_function;
EXPORT NODE *from_bool(int val) {
  return func__from_bool(val);
}

NODE *(*func__from_int)(int val) = (void *)undefined_c_function;
EXPORT NODE *from_int(int val) {
  return func__from_int(val);
}

NODE *(*func__from_long)(long val) = (void *)undefined_c_function;
EXPORT NODE *from_long(long val) {
  return func__from_long(val);
}

NODE *(*func__from_int64)(int64_t val) = (void *)undefined_c_function;
EXPORT NODE *from_int64(int64_t val) {
  return func__from_int64(val);
}

NODE *(*func__from_uint32)(uint32_t val) = (void *)undefined_c_function;
EXPORT NODE *from_uint32(uint32_t val) {
  return func__from_uint32(val);
}

NODE *(*func__from_uint64)(uint64_t val) = (void *)undefined_c_function;
EXPORT NODE *from_uint64(uint64_t val) {
  return func__from_uint64(val);
}

NODE *(*func__from_double)(double val) = (void *)undefined_c_function;
EXPORT NODE *from_double(double val) {
  return func__from_double(val);
}

NODE *(*func__from_digit_string)(const char *str) = (void *)undefined_c_function;
EXPORT NODE *from_digit_string(const char *str) {
  return func__from_digit_string(str);
}

NODE *(*func__from_uchar32)(unsigned int chr) = (void *)undefined_c_function;
EXPORT NODE *from_uchar32(unsigned int chr) {
  return func__from_uchar32(chr);
}

NODE *(*func__from_c_string)(const char *str) = (void *)undefined_c_function;
EXPORT NODE *from_c_string(const char *str) {
  return func__from_c_string(str);
}

NODE *(*func__from_latin_1_string)(const char *str, long len) = (void *)undefined_c_function;
EXPORT NODE *from_latin_1_string(const char *str, long len) {
  return func__from_latin_1_string(str, len);
}

NODE *(*func__from_uint32_string)(const uint32_t *str, long len) = (void *)undefined_c_function;
EXPORT NODE *from_uint32_string(const uint32_t *str, long len) {
  return func__from_uint32_string(str, len);
}

NODE *(*func__from_arguments)(int first_idx, int count) = (void *)undefined_c_function;
EXPORT NODE *from_arguments(int first_idx, int count) {
  return func__from_arguments(first_idx, count);
}

NODE *(*func__register_unique_item)(const char *name) = (void *)undefined_c_function;
EXPORT NODE *register_unique_item(const char *name) {
  return func__register_unique_item(name);
}

const char **unique_item_names;

typedef struct {
  const char *name;
  void **func;
  const char *module_name;
} C_FUNCTION;

C_FUNCTION c_functions[] = {
  {"from_bool", (void **)&func__from_bool},
  {"from_int", (void **)&func__from_int},
  {"from_long", (void **)&func__from_long},
  {"from_int64", (void **)&func__from_int64},
  {"from_uint32", (void **)&func__from_uint32},
  {"from_uint64", (void **)&func__from_uint64},
  {"from_double", (void **)&func__from_double},
  {"from_digit_string", (void **)&func__from_digit_string},
  {"from_uchar32", (void **)&func__from_uchar32},
  {"from_c_string", (void **)&func__from_c_string},
  {"from_latin_1_string", (void **)&func__from_latin_1_string},
  {"from_uint32_string", (void **)&func__from_uint32_string},
  {"from_arguments", (void **)&func__from_arguments},
  {"register_unique_item", (void **)&func__register_unique_item}
};

const int c_function_count = sizeof(c_functions) / sizeof(*c_functions);

EXPORT void define_c_function(const char *name, void *func) {
  symbol_info("define C-function");
  int i;
  for (i = 0; i < c_function_count; ++i) {
    if (strcmp(name, c_functions[i].name) == 0) {
      if (*c_functions[i].func != (void *)undefined_c_function) {
	unrecoverable_error(
	  "Attempt to redefine the C-function \"%s\" in module \"%s\" "
	  "(it was already defined in module \"%s\")!",
	  name, current_module_name, c_functions[i].module_name);
      }
      *c_functions[i].func = func;
      c_functions[i].module_name = current_module_name;
      return;
    }
  }
  unrecoverable_error(
    "Attempt to define the C-function \"%s\" in module \"%s\" "
    "but no such function is needed by the runtime!",
    name, current_module_name);
}

static const char *mangled_name(const char *namespace, const char *name) {
  if (!namespace) return name;
  char *buf =
    allocate_linktime(ALLOCATION_SIZE(strlen(namespace)+strlen(name)+3));
  sprintf(buf, "%s::%s", namespace, name);
  return buf;
}

int is_a_power_of_two(int n) {
  return ((n != 0) && !(n & (n - 1)));
}

static void do_register_polymorphic_function(const char *name, int id) {
  if (polymorphic_function_table_size == 0) {
    polymorphic_function_table_size = id+1;
    polymorphic_function_names =
      allocate_linktime(polymorphic_function_table_size*sizeof(const char *));
  } else if (id >= polymorphic_function_table_size) {
    polymorphic_function_table_size = 2*(id+1);
    polymorphic_function_names =
      reallocate_linktime(
	polymorphic_function_names,
	polymorphic_function_table_size*sizeof(const char *));
  }
  polymorphic_function_names[id] = name;
}

// by default this slot is set to a method that raises an error
EXPORT void register_polymorphic_function(const char *name, int *id_p) {
  symbol_info("register polymorphic function");
  int id = polymorphic_function_count;
  polymorphic_function_count += 2;
  do_register_polymorphic_function(name, id);
  *id_p = id;
}

// by default this slot is set to an attribute with the value <undefined>
// (this is done for all objects but the <undefined> object)
//
// in addition the polymorphic function acts as a setter if called with two
// arguments on an object that has not set this slot to a method
EXPORT void register_polymorphic_function_with_setter(const char *name, int *id_p) {
  symbol_info("register polymorphic function");
  int id = polymorphic_function_with_setter_count;
  polymorphic_function_with_setter_count += 2;
  do_register_polymorphic_function(name, id);
  *id_p = id;
}

// by default this slot is set to a method that raises an error
EXPORT void define_polymorphic_function(
  const char *namespace, const char *name, NODE_GETTER getter, int *id_p,
  NODE **var_p
) {
  symbol_info_1("define polymorphic function", namespace, name);
  SYMBOL_ENTRY *ep = define_symbol(VT_POLYMORPHIC, namespace, name);
  int id = polymorphic_function_count;
  polymorphic_function_count += 2;
  ep->getter = getter;
  ep->id = id;
  ep->var_p = var_p;
  do_register_polymorphic_function(mangled_name(namespace, name), id);
  *id_p = id;
}

// by default this slot is set to an attribute with the value <undefined>
// (this is done for all objects but the <undefined> object)
//
// in addition the polymorphic function acts as a setter if called with two
// arguments on an object that has not set this slot to a method
EXPORT void define_polymorphic_function_with_setter(
  const char *namespace, const char *name, NODE_GETTER getter, int *id_p,
  NODE **var_p
) {
  symbol_info_1("define polymorphic function with setter", namespace, name);
  SYMBOL_ENTRY *ep = define_symbol(VT_POLYMORPHIC, namespace, name);
  int id = polymorphic_function_with_setter_count;
  polymorphic_function_with_setter_count += 2;
  ep->getter = getter;
  ep->id = id;
  ep->var_p = var_p;
  do_register_polymorphic_function(mangled_name(namespace, name), id);
  *id_p = id;
}

EXPORT void define_privileged_polymorphic_function(
  const char *namespace, const char *name, NODE_GETTER getter, int id,
  NODE **var_p
) {
  symbol_info_1("define polymorphic function", namespace, name);
  SYMBOL_ENTRY *ep = define_symbol(VT_POLYMORPHIC, namespace, name);
  ep->getter = getter;
  ep->id = id;
  ep->var_p = var_p;
  do_register_polymorphic_function(mangled_name(namespace, name), id);
}

extern NODE *create_future(void);

EXPORT void define_single_assign_static(
  const char *namespace, const char *name,
  NODE_GETTER getter, NODE **var_p
) {
  symbol_info_1("define single assign static", namespace, name);
  SYMBOL_ENTRY *ep = define_symbol(VT_SINGLE_ASSIGN_STATIC, namespace, name);
  ep->var_p = var_p;
  ep->getter = getter;
  if (!*var_p) *var_p = create_future();
}

EXPORT void define_multi_assign_static(
  const char *namespace, const char *name,
  NODE_GETTER getter, NODE_SETTER setter
) {
  symbol_info_1("define multi assign static", namespace, name);
  SYMBOL_ENTRY *ep = define_symbol(VT_MULTI_ASSIGN_STATIC, namespace, name);
  ep->getter = getter;
  ep->setter = setter;
}

EXPORT void register_dynamic(int *id_p) {
  symbol_info("register dynamic");
  *id_p = dyna_idx++;
}

EXPORT void define_single_assign_dynamic(
  const char *namespace, const char *name,
  NODE_GETTER getter, NODE_SETTER definer,
  int *id_p
) {
  symbol_info_1("define single assign dynamic", namespace, name);
  SYMBOL_ENTRY *ep = define_symbol(VT_SINGLE_ASSIGN_DYNAMIC, namespace, name);
  ep->getter = getter;
  ep->definer = definer;
  *id_p = dyna_idx++;
}

EXPORT void define_multi_assign_dynamic(
  const char *namespace, const char *name,
  NODE_GETTER getter, NODE_SETTER setter, NODE_SETTER definer,
  int *id_p
) {
  symbol_info_1("define multi assign dynamic", namespace, name);
  SYMBOL_ENTRY *ep = define_symbol(VT_MULTI_ASSIGN_DYNAMIC, namespace, name);
  ep->getter = getter;
  ep->setter = setter;
  ep->definer = definer;
  *id_p = dyna_idx++;
}

EXPORT void define_type_function(
  const char *namespace, const char *name, FUNC type, int par_cnt
) {
  symbol_info_1("define type function", namespace, name);
  SYMBOL_ENTRY *obj = find_symbol(namespace, name);
  if (obj->type != VT_SINGLE_ASSIGN_STATIC) {
    unrecoverable_error(
      "Attempt to define a type function for the non-single-assign-static symbol "
      "\"%s::%s\"!", namespace, name);
  }
  ATTRIBUTE_ENTRY *attributes = obj->attributes;
  while (attributes) {
    if (attributes->id == -1) {
      unrecoverable_error(
	"Attempt to redefine the type function for \"%s::%s\"! "
	"in module \"%s\" (it was already defined in module \"%s\")!",
	namespace, name,
	current_module_name, attributes->module_name);
    }
    attributes = attributes->link;
  }
  attributes = allocate_linktime(sizeof(ATTRIBUTE_ENTRY));
  attributes->link = obj->attributes;
  attributes->module_name = current_module_name;
  attributes->id = -1;
  attributes->par_cnt = par_cnt;
  attributes->type = type;
  obj->attributes = attributes;
}

EXPORT void define_attribute(
  const char *namespace, const char *name,
  int id, NODE *attribute
) {
  symbol_info_2(
    "define attribute", namespace, name,
    ".", polymorphic_function_names[id]);
  SYMBOL_ENTRY *obj = find_symbol(namespace, name);
  if (obj->type != VT_SINGLE_ASSIGN_STATIC && obj->type != VT_POLYMORPHIC) {
    unrecoverable_error(
      "Attempt to define an attribute for the non-single-assign-static symbol "
      "\"%s::%s\"!", namespace, name);
  }
  ATTRIBUTE_ENTRY *attributes = obj->attributes;
  while (attributes) {
    if (attributes->id == id) {
      unrecoverable_error(
	"Attempt to redefine the attribute \"%s\" for \"%s::%s\"! "
	"in module \"%s\" (it was already defined in module \"%s\")!",
	polymorphic_function_names[id], namespace, name,
	current_module_name, attributes->module_name);
    }
    attributes = attributes->link;
  }
  attributes = allocate_linktime(sizeof(ATTRIBUTE_ENTRY));
  attributes->link = obj->attributes;
  attributes->module_name = current_module_name;
  attributes->id = id;
  attributes->value = MAKE_ATTRIBUTE_VALUE(attribute);
  obj->attributes = attributes;
}

EXPORT void define_method(
  const char *namespace, const char *name,
  int id, NODE *method
) {
  symbol_info_2(
    "define method", namespace, name,
    "/", polymorphic_function_names[id]);
  SYMBOL_ENTRY *obj = find_symbol(namespace, name);
  if (obj->type != VT_SINGLE_ASSIGN_STATIC && obj->type != VT_POLYMORPHIC) {
    unrecoverable_error(
      "Attempt to define a method for the non-single-assign-static symbol "
      "\"%s::%s\"!", namespace, name);
  }
  ATTRIBUTE_ENTRY *attributes = obj->attributes;
  while (attributes) {
    if (attributes->id == id) {
      unrecoverable_error(
	"Attempt to redefine the method (%d) \"%s\" for \"%s::%s\"! "
	"in module \"%s\" (it was already defined in module \"%s\")!",
	id, polymorphic_function_names[id], namespace, name,
	current_module_name, attributes->module_name);
    }
    attributes = attributes->link;
  }
  attributes = allocate_linktime(sizeof(ATTRIBUTE_ENTRY));
  attributes->link = obj->attributes;
  attributes->module_name = current_module_name;
  attributes->id = id;
  attributes->value = method;
  obj->attributes = attributes;
}

EXPORT void use_polymorphic_function(
  const char *namespace, const char *name, NODE_GETTER *getter, int *id
) {
  symbol_info_1("use polymorphic function", namespace, name);
  SYMBOL_ENTRY *ep = find_symbol(namespace, name);
  switch (ep->type) {
    case VT_POLYMORPHIC:
      *getter = ep->getter;
      *id = ep->id;
      return;
    default:
      unrecoverable_error(
	"The symbol \"%s::%s\", defined in the module \"%s\" is a %s and not a "
	"polymorphic function as needed by the module \"%s\"!",
	namespace, name, ep->module_name, var_type[ep->type],
	current_module_name);
  }
}

EXPORT void use_read_only(
  const char *namespace, const char *name,
  NODE_GETTER *getter, NODE_GETTER *get_value_or_future
) {
  symbol_info_1("use read-only", namespace, name);
  SYMBOL_ENTRY *ep = find_symbol(namespace, name);
  *getter = ep->getter;
  switch (ep->type) {
    case VT_MULTI_ASSIGN_STATIC:
    case VT_MULTI_ASSIGN_DYNAMIC:
      *get_value_or_future = create_future;
      break;
    default:
      *get_value_or_future = ep->getter;
  }
}

EXPORT void use_read_write(
  const char *namespace, const char *name,
  NODE_GETTER *getter, NODE_SETTER *setter
) {
  symbol_info_1("use read-write", namespace, name);
  SYMBOL_ENTRY *ep = find_symbol(namespace, name);
  switch (ep->type) {
    case VT_MULTI_ASSIGN_STATIC:
    case VT_MULTI_ASSIGN_DYNAMIC:
      *getter = ep->getter;
      *setter = ep->setter;
      return;
    default:
      unrecoverable_error(
	"The symbol \"%s::%s\", defined in the module \"%s\" is a %s and not "
	"writeable as needed by the module \"%s\"!",
	namespace, name, ep->module_name, var_type[ep->type],
	current_module_name);
  }
}

EXPORT void use_single_assign_dynamic(
  const char *namespace, const char *name,
  NODE_GETTER *getter, NODE_SETTER *definer
) {
  symbol_info_1("use single assign dynamic", namespace, name);
  SYMBOL_ENTRY *ep = find_symbol(namespace, name);
  switch (ep->type) {
    case VT_SINGLE_ASSIGN_DYNAMIC:
      *getter = ep->getter;
      *definer = ep->definer;
      return;
    default:
      unrecoverable_error(
	"The symbol \"%s::%s\", defined in the module \"%s\" is a %s and not "
	"a single assign dynamic as needed by the module \"%s\"!",
	namespace, name, ep->module_name, var_type[ep->type],
	current_module_name);
  }
}

EXPORT void use_multi_assign_dynamic(
  const char *namespace, const char *name,
  NODE_GETTER *getter, NODE_SETTER *setter, NODE_SETTER *definer
) {
  symbol_info_1("use multi assign dynamic", namespace, name);
  SYMBOL_ENTRY *ep = find_symbol(namespace, name);
  switch (ep->type) {
    case VT_MULTI_ASSIGN_DYNAMIC:
      *getter = ep->getter;
      *setter = ep->setter;
      *definer = ep->definer;
      return;
    default:
      unrecoverable_error(
	"The symbol \"%s::%s\", defined in the module \"%s\" is a %s and not "
	"a multi assign dynamic as needed by the module \"%s\"!",
	namespace, name, ep->module_name, var_type[ep->type],
	current_module_name);
  }
}

int par_count_id;

EXPORT void resolve_symbols(void) {
  debug_info("resolve symbols\n");
  set_module("_BUILTIN_");
  NODE_GETTER dummy;
  use_polymorphic_function("std", "parameter_count_of", &dummy, &par_count_id);
}

extern void *node_p;
extern void *update_start_p;
extern void def_attribute(NODE **var_p, int idx, void *attr);

extern void *allocate(long size);

EXPORT void resolve_attributes(void) {
  debug_info("resolve attributes\n");
  int i;
  for (i = 0; i < HASH_TABLE_SIZE; ++i) {
    HASH_ENTRY *hep = hash_table[i];
    while (hep) {
      SYMBOL_ENTRY *sep = hep->symbols;
      while (sep) {
	ATTRIBUTE_ENTRY *attributes = sep->attributes;
	if (attributes) {
	  debug_info("  %s::%s\n", sep->namespace, hep->name);
	  update_start_p = node_p;
	  do {
	    if (attributes->id == -1) {
	      debug_info("    <type function>\n");
	    } else {
	      debug_info(
		"    %s\n",
		polymorphic_function_names[attributes->id]);
	    }
	    def_attribute(sep->var_p, attributes->id, attributes->value);
	    attributes = attributes->link;
	  } while (attributes);
	}
	sep = sep->link;
      }
      hep = hep->link;
    }
  }
}
