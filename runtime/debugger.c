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

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <setjmp.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "common.h"
#include "linker.h"

#if defined(__GNUC__) && !defined(__clang__) && defined(__x86_64)
  register int argument_count asm("ebx");
  register FRAME *arguments asm("r12");
  register NODE *myself asm("r13");
  register FUNC func asm("r14");
  register FRAME *frame asm("r15");
#else
  extern int argument_count;
  extern FRAME *arguments;
  extern NODE *myself;
  extern FUNC func;
  extern FRAME *frame;
#endif

extern int argument_count_save;
extern FRAME *arguments_save;
extern NODE *myself_save;
extern FUNC func_save;
extern FRAME *frame_save;

#if !defined(MAP_ANONYMOUS) && defined(MAP_ANON)
  #define MAP_ANONYMOUS MAP_ANON
#endif

extern uint64_t instruction_counter;
extern jmp_buf main_loop_start;

extern long debug_string(NODE *node, int indent, int max_depth, char *buf);

static int is_identifier_start_character(char chr) {
  return chr >= 'a' && chr <= 'z' || chr >= 'A' && chr <= 'Z';
}

static int is_identifier_character(char chr) {
  return
    is_identifier_start_character(chr) ||
    chr == '_' || chr >= '0' && chr <= '9';
}

static char *parse_identifier(char **pp) {
  char *p = *pp;
  if (!is_identifier_start_character(*p)) return NULL;
  char *identifier = p++;
  while (is_identifier_character(*p)) ++p;
  *pp = p;
  return identifier;
}

static void list_global_symbol_names(void) {
  int i;
  for (i = 0; i < HASH_TABLE_SIZE; ++i) {
    HASH_ENTRY *hep = hash_table[i];
    while (hep) {
      SYMBOL_ENTRY *sep = hep->symbols;
      while (sep) {
	printf("%s::%s\n", sep->namespace, hep->name);
	sep = sep->link;
      }
      hep = hep->link;
    }
  }
}

extern MODULE_INFO *module_infos;
static int already_sorted;

static void list_module_names(void) {
  MODULE_INFO *module_info = module_infos;
  while (module_info) {
    printf("%s\n", module_info->name);
    module_info = module_info->link;
  }
}

typedef int (*COMPARE_FUNCTION)(const void *, const void *);

static int compare_continuation_infos(
  const CONTINUATION_INFO *left, const CONTINUATION_INFO *right
) {
  if (left->continuation < right->continuation)
    return -1;
  else if (left->continuation > right->continuation)
    return 1;
  else
    return 0;
}

EXPORT int retrieve_continuation_info(
  FUNC func, const char **filename_p, CONTINUATION_INFO **info_p
) {
  MODULE_INFO *module_info;
  if (!already_sorted) {
    module_info = module_infos;
    while (module_info) {
      qsort(
	module_info->continuation_info, module_info->continuation_count,
	sizeof(CONTINUATION_INFO), (COMPARE_FUNCTION)compare_continuation_infos);
      module_info = module_info->link;
    }
    already_sorted = true;
  }
  module_info = module_infos;
  while (module_info) {
    CONTINUATION_INFO *continuation_info = module_info->continuation_info;
    int count = module_info->continuation_count;
    if (count > 0) {
      int s = 0;
      int e = count;
      while (e-1 > s) {
	int i = (s+e)/2;
	if (func >= continuation_info[i].continuation)
	  s = i;
	else
	  e = i;
      }
      CONTINUATION_INFO *cip = &continuation_info[s];
      if (func == cip->continuation) {
	*filename_p = module_info->filenames[cip->submodule_index];
	*info_p = cip;
	return true;
      }
    }
    module_info = module_info->link;
  }
  return false;
}

static void dump_continuation(FUNC func) {
  const char *module_filename;
  CONTINUATION_INFO *info;
  if (retrieve_continuation_info(func, &module_filename, &info)) {
    printf(
      "%s: %d:%d-%d:%d\n",
      module_filename,
      info->first_line, info->first_column,
      info->last_line, info->last_column);
  } else {
    printf("%p\n", func);
  }
}

static void edump_continuation(const char *name, FUNC func) {
  const char *module_filename;
  CONTINUATION_INFO *info;
  if (retrieve_continuation_info(func, &module_filename, &info)) {
    fprintf(
      stderr, "%s: %s: %d:%d-%d:%d\n",
      name, module_filename,
      info->first_line, info->first_column,
      info->last_line, info->last_column);
  } else {
    fprintf(stderr, "%s: %p\n", name, func);
  }
}

EXPORT void crash_dump(void) {
  if (instruction_counter != 0) {
    fprintf(stderr, "instruction counter: %" PRIu64 "\n", instruction_counter);
  }
  edump_continuation("current function", func);
  edump_continuation("continuation", frame->cont);
  int n = 50;
  FRAME *trace = frame;
  while (--n >= 0 && trace) {
    edump_continuation("next", trace->cont);
    trace = trace->caller_frame;
  }
}

static void list_local_symbol_names(void) {
  const char *module_filename;
  CONTINUATION_INFO *info;
  if (retrieve_continuation_info(func, &module_filename, &info)) {
    FRAME_INFO *frame_info = info->frame_info;
    if (frame_info) {
      int i;
      for (i = 0; i < frame_info->var_count; ++i) {
	printf("%s\n", frame_info->var_names[i]);
      }
    }
  }
}

#ifdef __CYGWIN__
  extern FUNC invalid_continuation;
#else
  extern void invalid_continuation(void);
#endif

void print_contents(NODE *node) {
  if (node->type == NULL) { // it's a cell
    node = node->cell.contents;
  }
  long len = debug_string(node, 0, 1, NULL);
  char *buf = malloc(len+1); // obey terminating null-byte
  debug_string(node, 0, 1, buf);
  buf[len] = 0; // add terminating null-byte
  printf("%s", buf);
  free(buf);
}

int continuation_depth(void) {
  int depth = 1;
  FRAME *trace = frame;
  while (trace) {
    ++depth;
    trace = trace->caller_frame;
  }
  return depth;
}

extern void reset_log_file(void);

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

void debug(FUNC entry) {
  char cmd[320]; // add a 64-byte sentinel area
  SHARED_DATA *sd = mmap(
    NULL, sizeof(SHARED_DATA),
    PROT_READ|PROT_WRITE,
    MAP_ANONYMOUS|MAP_SHARED,
    0, 0);
  argument_count = 0;
  func = entry;
  while (true) {
    reset_log_file();
    int pid = fork();
    if (pid == 0) {
      switch (sd->command) {
	case GOTO_INSTRUCTION:
	  //printf("goto instruction %" PRId64 "\n", sd->instruction_counter);
	  if (setjmp(main_loop_start) != 0) {
	    argument_count = argument_count_save;
	    arguments = arguments_save;
	    myself = myself_save;
	    func = func_save;
	    frame = frame_save;
	  }
	  while (instruction_counter < sd->instruction_counter) {
	    func();
	    ++instruction_counter;
	  }
	  sd->command = SHOW_PROMPT;
	  break;
	case LOG_LAST_INSTRUCTION:
	  {
	    uint64_t last_instruction = 0;
	    if (setjmp(main_loop_start) != 0) {
	      argument_count = argument_count_save;
	      arguments = arguments_save;
	      myself = myself_save;
	      func = func_save;
	      frame = frame_save;
	    }
	    while (instruction_counter < sd->instruction_counter) {
	      func();
	      ++instruction_counter;
	      if (continuation_depth() <= sd->depth) {
		last_instruction = instruction_counter;
	      }
	    }
	    if (last_instruction < instruction_counter) {
	      sd->command = GOTO_INSTRUCTION;
	      sd->instruction_counter = last_instruction;
	      exit(47);
	    }
	  }
	  // fall through
	default:
	  sd->command = SHOW_PROMPT;
      }
      while (true) {
	print_prompt:
	printf("%" PRId64 ">", instruction_counter);
	fflush(stdout);
	int i = 0;
	while (true) {
	  char chr = getchar();
	  if (chr == '\n') break;
	  if (i < 256) cmd[i] = chr;
	  ++i;
	}
	if (i < 256) {
	  if (i > 0) {
	    cmd[i] = 0;
	    switch (cmd[0]) {
	      case 'a': // show arguments
		if (arguments) {
		  int i;
		  for (i = 0; i < argument_count; ++i) {
		    print_contents(arguments->slots[i]);
		  }
		}
		break;
	      case 'b': // set breakpoint
		break;
	      case 'B': // list breakpoints
		break;
	      case 'c': // continue forwards
		break;
	      case 'C': // continue backwards
		break;
	      case 'd': // delete breakpoint
		break;
	      case 'e': // exit forwards
		{
		  uint64_t n = 1;
		  if (i > 1) n = atoll(cmd+1);
		  while (n > 0) {
		    {
		      int depth = continuation_depth();
		      if (setjmp(main_loop_start) != 0) {
			argument_count = argument_count_save;
			arguments = arguments_save;
			myself = myself_save;
			func = func_save;
			frame = frame_save;
		      }
		      do {
			func();
			++instruction_counter;
		      } while (continuation_depth() >= depth);
		      --n;
		    }
		  }
		}
		break;
	      case 'E': // exit backwards
		if (instruction_counter > 0) {
		  sd->command = LOG_LAST_INSTRUCTION;
		  sd->instruction_counter = instruction_counter-1;
		  sd->depth = continuation_depth()-1;
		  exit(47);
		}
		printf("Error: Reached start of program!\n");
		break;
	      case 'f': // show current function
		dump_continuation(func);
		break;
	      case 'g': // list global variables
		list_global_symbol_names();
		break;
	      case 'j': // jump in time
		{
		  if (i > 1) {
		    uint64_t n = atoll(cmd+1);
		    if (n < instruction_counter) {
		      sd->command = GOTO_INSTRUCTION;
		      sd->instruction_counter = n;
		      exit(47);
		    }
		    if (setjmp(main_loop_start) != 0) {
		      argument_count = argument_count_save;
		      arguments = arguments_save;
		      myself = myself_save;
		      func = func_save;
		      frame = frame_save;
		    }
		    while (instruction_counter < n) {
		      func();
		      ++instruction_counter;
		    }
		  } else {
		    printf("Error: Missing argument!\n");
		  }
		}
		break;
	      case 'l': // list current local variables
		list_local_symbol_names();
		break;
	      case 'm': // list modules
		list_module_names();
		break;
	      case 'n': // next forwards
		{
		  uint64_t n = 1;
		  if (i > 1) n = atoll(cmd+1);
		  while (n > 0) {
		    {
		      int depth = continuation_depth();
		      if (setjmp(main_loop_start) != 0) {
			argument_count = argument_count_save;
			arguments = arguments_save;
			myself = myself_save;
			func = func_save;
			frame = frame_save;
		      }
		      do {
			func();
			++instruction_counter;
		      } while (continuation_depth() > depth);
		      --n;
		    }
		  }
		}
		break;
	      case 'N': // next backwards
		if (instruction_counter > 0) {
		  sd->command = LOG_LAST_INSTRUCTION;
		  sd->instruction_counter = instruction_counter-1;
		  sd->depth = continuation_depth();
		  exit(47);
		}
		printf("Error: Reached start of program!\n");
		break;
	      case 'p': // print
		{
		  char *p = cmd+1;
		  while (*p == ' ') ++p;
		  char *name = parse_identifier(&p);
		  if (name) {
		    if (p[0] == ':' && p[1] == ':') {
		      *p = 0;
		      p += 2;
		      char *namespace = name;
		      name = parse_identifier(&p);
		      if (*p) {
			printf("Error: Unexpected input at end of line!\n");
			goto print_prompt;
		      }
		      SYMBOL_ENTRY *obj = maybe_find_symbol(namespace, name);
		      if (obj) {
			NODE *node = obj->getter();
			if (node) {
			  print_contents(node);
			} else {
			  printf("<object not yet initialized>\n");
			}
		      } else {
			printf("Error: No such symbol!\n");
		      }
		      goto print_prompt;
		    } else {
		      while (--p > name) {
			if (*p == '_' && p[-1] == '_') {
			  p[-1] = 0;
			  ++p;
			  MODULE_INFO *module_info = module_infos;
			  while (module_info) {
			    if (strcmp(name, module_info->name) == 0) {
			      int i;
			      for (i = 0; i < module_info->top_level_count; ++i) {
				if (strcmp(p, module_info->var_names[i]) == 0) {
				  print_contents(module_info->var_tab[i]);
				  goto print_prompt;
				}
			      }
			      printf("Error: Invalid variable name!\n");
			      goto print_prompt;
			    }
			    module_info = module_info->link;
			  }
			  printf("Error: Invalid module name!\n");
			  goto print_prompt;
			}
		      }
		      const char *module_filename;
		      CONTINUATION_INFO *info;
		      if (retrieve_continuation_info(func, &module_filename, &info)) {
			FRAME_INFO *frame_info = info->frame_info;
			if (frame_info) {
			  int i;
			  for (i = 0; i < frame_info->var_count; ++i) {
			    if (strcmp(name, frame_info->var_names[i]) == 0) {
			      print_contents(frame->slots[i]);
			      goto print_prompt;
			    }
			  }
			}
		      }
		    }
		  }
		  printf("Error: Invalid variable name!\n");
		}
		break;
	      case 'q':
		exit(EXIT_SUCCESS);
	      case 's': // step forwards
		{
		  uint64_t n = 1;
		  if (i > 1) n = atoll(cmd+1);
		  if (setjmp(main_loop_start) != 0) {
		    argument_count = argument_count_save;
		    arguments = arguments_save;
		    myself = myself_save;
		    func = func_save;
		    frame = frame_save;
		  }
		  while (n > 0) {
		    func();
		    ++instruction_counter;
		    --n;
		  }
		}
		break;
	      case 'S': // step backwards
		if (instruction_counter > 0) {
		  sd->command = GOTO_INSTRUCTION;
		  sd->instruction_counter = instruction_counter-1;
		  exit(47);
		}
		printf("Error: Reached start of program!\n");
		break;
	      case 't': // dump continuation trace
		{
		  int n = 1;
		  if (i > 1) n = atoi(cmd+1);
		  dump_continuation(frame->cont);
		  FRAME *trace = frame;
		  while (--n > 0 && trace) {
		    dump_continuation(trace->cont);
		    trace = trace->caller_frame;
		  }
		}
		break;
	      case 'T': // print continuation trace depth
		printf("%d\n", continuation_depth());
		break;
	      case 'u': // list used namespaces
		{
		  char *p = cmd+1;
		  while (*p == ' ') ++p;
		  MODULE_INFO *module_info = module_infos;
		  while (module_info) {
		    if (strcmp(p, module_info->name) == 0) {
		      const char **namespaces = module_info->used_namespaces;
		      while (*namespaces) {
			printf("%s\n", *namespaces++);
		      }
		      goto print_prompt;
		    }
		    module_info = module_info->link;
		  }
		  printf("Error: Invalid module name!\n");
		}
		break;
	      case 'v': // list top-level variables
		{
		  char *p = cmd+1;
		  while (*p == ' ') ++p;
		  MODULE_INFO *module_info = module_infos;
		  while (module_info) {
		    if (strcmp(p, module_info->name) == 0) {
		      int i;
		      for (i = 0; i < module_info->top_level_count; ++i) {
			printf("%s\n", module_info->var_names[i]);
		      }
		      goto print_prompt;
		    }
		    module_info = module_info->link;
		  }
		  printf("Error: Invalid module name!\n");
		}
		break;
	      default:
		printf("Error: Unknown command!\n");
	    }
	  }
	} else {
	  printf("Error: Command line too long!\n");
	}
      }
    } else {
      int status;
      waitpid(pid, &status, 0);
      if (WEXITSTATUS(status) != 47) exit(status);
    }
  }
}
