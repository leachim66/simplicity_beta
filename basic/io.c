#include <netdb.h>
#include <stddef.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <math.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
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
typedef struct FRAME_INFO {
  int var_count;
  const char *var_names[];
} FRAME_INFO;
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
IMPORT int child_changed_state;
IMPORT int window_changed_size;
IMPORT NODE *get_dynamic_slot(int id);
IMPORT void define_dynamic_slot(int id, NODE *node);
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
IMPORT int result_count;
IMPORT void invalid_results_error(void);
IMPORT void initialize_future(NODE *var, NODE *val);
IMPORT void allocate_arguments(void);
IMPORT NODE *create_cell(void);
IMPORT void too_few_arguments_error(void);
IMPORT NODE *from_arguments(int first_idx, int count);
typedef struct CELL {
  FUNC type;
  struct ATTRIBUTES *attributes;
  NODE *contents;
} CELL;
IMPORT NODE *empty_string;
IMPORT NODE *create_closure(FUNC type, int par_count);
IMPORT NODE *from_int(int val);
IMPORT NODE *from_c_string(const char *str);
IMPORT void *copy(const void *buf, long size);
IMPORT void *allocate(long size);
IMPORT ATTRIBUTES *collect_attributes(ATTRIBUTES *attributes);
IMPORT void no_such_function(void);
IMPORT OCTREE undefined_attributes_level_1;
IMPORT OCTREE undefined_attributes_level_2;
IMPORT OCTREE undefined_attributes_level_3;
IMPORT OCTREE undefined_attributes_level_4;
IMPORT OCTREE undefined_attributes_level_5;
IMPORT OCTREE undefined_attributes_level_6;
IMPORT OCTREE undefined_attributes_level_7;
IMPORT __attribute__ ((noreturn)) void runtime_error(const char *msg, ...);
IMPORT int debug_print(int indent, char *buf, const char *format, ...);
IMPORT NODE *from_long(long val);
IMPORT void deallocate_memory(void *buf);
IMPORT NODE *undefined;
IMPORT NODE *from_bool(int val);
IMPORT NODE *boolean_false;
IMPORT NODE *boolean_true;
IMPORT void too_many_arguments_error(void);
typedef enum {
  EM__NORMAL,
  EM__RECORD,
  EM__REPLAY
} EVENT__MODE;
IMPORT EVENT__MODE event__mode;
IMPORT void record__event(const char *name);
IMPORT void store__integer(int val);
IMPORT void replay__event(const char *name);
IMPORT void retrieve__integer(int *val_p);
IMPORT void report__event(const char *name);
IMPORT void print__integer(int val);
IMPORT void successful__action(const char *name);
IMPORT void failed__action(const char *name);
IMPORT int replay__action(const char *name);
IMPORT void *allocate_memory(size_t size);
IMPORT void store__memory(const uint8_t *buf, long len);
IMPORT long retrieve__memory(uint8_t **buf_p);
IMPORT NODE *from_latin_1_string(const char *str, long len);
IMPORT NODE *create_continuation(void);
IMPORT NODE *create_cell_with_contents(NODE *contents);
IMPORT NODE *create_future(void);
IMPORT void store__long_integer(long val);
IMPORT void retrieve__long_integer(long *val_p);
IMPORT void print__memory(const uint8_t *buf, long len);
IMPORT void store__int_array(const int *buf, long len);
IMPORT long retrieve__int_array(int **buf_p);
IMPORT NODE *zero;
IMPORT void too_few_results_error(void);
IMPORT void *reallocate_memory(void * buf, size_t size);
IMPORT void initialize_maybe_future(NODE *var, NODE *val);
IMPORT void set_attribute(ATTRIBUTES *attributes, int idx, void *attr);
IMPORT void *allocate_large(long size);
IMPORT NODE *collect_node(NODE *node);
IMPORT void collect_static_attributes(ATTRIBUTES *attributes);
IMPORT void register_module_info(MODULE_INFO *info);
IMPORT void define_polymorphic_function(
  const char *namespace, const char *name, NODE_GETTER getter, int *id_p,
  NODE **var_p
);
IMPORT void define_polymorphic_function_with_setter(
  const char *namespace, const char *name, NODE_GETTER getter, int *id_p,
  NODE **var_p
);
IMPORT NODE *from_uint32(uint32_t val);
IMPORT NODE *from_uchar32(unsigned int chr);
IMPORT NODE *create_function(FUNC func, int par_count);
IMPORT void set_module(const char *name);
IMPORT void set_used_namespaces(const char **namespaces);
IMPORT NODE *register_unique_item(const char *name);
IMPORT void assign_value(NODE **dest, NODE *val);
IMPORT void define_single_assign_static(
  const char *namespace, const char *name,
  NODE_GETTER getter, NODE **var_p
);
IMPORT NODE *create_future_with_prototype(NODE *prototype);
typedef void (*NODE_SETTER)(NODE *);
IMPORT void define_single_assign_dynamic(
  const char *namespace, const char *name,
  NODE_GETTER getter, NODE_SETTER definer,
  int *id_p
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
static NODE_GETTER get__EEXIST;
static NODE_GETTER get_value_or_future__EEXIST;
static NODE_GETTER get__Error;
static NODE_GETTER get_value_or_future__Error;
static NODE_GETTER get__MODE;
static NODE_GETTER get_value_or_future__MODE;
static NODE_GETTER get__PARENTS;
static NODE_GETTER get_value_or_future__PARENTS;
static NODE_GETTER get__SORT;
static NODE_GETTER get_value_or_future__SORT;
static NODE_GETTER get__STDERR_FILENO;
static NODE_GETTER get_value_or_future__STDERR_FILENO;
static NODE_GETTER get__STDIN_FILENO;
static NODE_GETTER get_value_or_future__STDIN_FILENO;
static NODE_GETTER get__STDOUT_FILENO;
static NODE_GETTER get_value_or_future__STDOUT_FILENO;
static int poly_idx__accept;
static NODE_GETTER get__accept;
static int poly_idx__access_time_of;
static NODE_GETTER get__access_time_of;
static NODE_GETTER get__append;
static NODE_GETTER get_value_or_future__append;
static NODE_GETTER get__atomic_write_to;
static NODE_GETTER get_value_or_future__atomic_write_to;
static NODE_GETTER get__before;
static NODE_GETTER get_value_or_future__before;
static int poly_idx__block_size_of;
static NODE_GETTER get__block_size_of;
static NODE_GETTER get__case;
static NODE_GETTER get_value_or_future__case;
static NODE_GETTER get__clib_mkdir;
static NODE_GETTER get_value_or_future__clib_mkdir;
static int poly_idx__close;
static NODE_GETTER get__close;
static int poly_idx__connect;
static NODE_GETTER get__connect;
static NODE_GETTER get__create_file;
static NODE_GETTER get_value_or_future__create_file;
static NODE_GETTER get__current_path;
static NODE_GETTER get_value_or_future__current_path;
static int poly_idx__device_of;
static NODE_GETTER get__device_of;
static NODE_GETTER get__do;
static NODE_GETTER get_value_or_future__do;
static int poly_idx__equal;
static NODE_GETTER get__equal;
static NODE_GETTER get__errno;
static NODE_GETTER get_value_or_future__errno;
static NODE_GETTER get__ewrite;
static NODE_GETTER get_value_or_future__ewrite;
static NODE_GETTER get__extern;
static NODE_GETTER get_value_or_future__extern;
static NODE_GETTER get__extract_options;
static NODE_GETTER get_value_or_future__extract_options;
static NODE_GETTER get__false;
static NODE_GETTER get_value_or_future__false;
static int poly_idx__file_type_of;
static NODE_GETTER get__file_type_of;
static int poly_idx__filename_of;
static NODE_GETTER get__filename_of;
static int poly_idx__flush;
static NODE_GETTER get__flush;
static NODE_GETTER get__for_each;
static NODE_GETTER get_value_or_future__for_each;
static NODE_GETTER get__forever;
static NODE_GETTER get_value_or_future__forever;
static NODE_GETTER get__fullname;
static NODE_GETTER get_value_or_future__fullname;
static int poly_idx__fullname_of;
static NODE_GETTER get__fullname_of;
static int poly_idx__get;
static NODE_GETTER get__get;
static NODE_GETTER get__get_network_address;
static NODE_GETTER get_value_or_future__get_network_address;
static int poly_idx__group_id_of;
static NODE_GETTER get__group_id_of;
static NODE_GETTER get__has_prefix;
static NODE_GETTER get_value_or_future__has_prefix;
static NODE_GETTER get__has_suffix;
static NODE_GETTER get_value_or_future__has_suffix;
static int poly_idx__hash;
static NODE_GETTER get__hash;
static NODE_GETTER get__if;
static NODE_GETTER get_value_or_future__if;
static int poly_idx__inode_of;
static NODE_GETTER get__inode_of;
static int poly_idx__is_a_directory;
static NODE_GETTER get__is_a_directory;
static int poly_idx__is_a_link;
static NODE_GETTER get__is_a_link;
static int poly_idx__is_a_regular_file;
static NODE_GETTER get__is_a_regular_file;
static NODE_GETTER get__is_defined;
static NODE_GETTER get_value_or_future__is_defined;
static NODE_GETTER get__key_of;
static NODE_GETTER get_value_or_future__key_of;
static NODE_GETTER get__length_of;
static NODE_GETTER get_value_or_future__length_of;
static int poly_idx__less;
static NODE_GETTER get__less;
static int poly_idx__link_count_of;
static NODE_GETTER get__link_count_of;
static NODE_GETTER get__list;
static NODE_GETTER get_value_or_future__list;
static int poly_idx__listen;
static NODE_GETTER get__listen;
static NODE_GETTER get__load_file;
static NODE_GETTER get_value_or_future__load_file;
static NODE_GETTER get__many;
static NODE_GETTER get_value_or_future__many;
static NODE_GETTER get__minus;
static NODE_GETTER get_value_or_future__minus;
static NODE_GETTER get__mkdir;
static NODE_GETTER get_value_or_future__mkdir;
static int poly_idx__mode_of;
static NODE_GETTER get__mode_of;
static int poly_idx__modification_time_of;
static NODE_GETTER get__modification_time_of;
static NODE_GETTER get__not_followed_by;
static NODE_GETTER get_value_or_future__not_followed_by;
static NODE_GETTER get__oct;
static NODE_GETTER get_value_or_future__oct;
static NODE_GETTER get__open_file_for_reading;
static NODE_GETTER get_value_or_future__open_file_for_reading;
static NODE_GETTER get__parameter_count_of;
static NODE_GETTER get_value_or_future__parameter_count_of;
static NODE_GETTER get__pass;
static NODE_GETTER get_value_or_future__pass;
static NODE_GETTER get__pathname_of;
static NODE_GETTER get_value_or_future__pathname_of;
static NODE_GETTER get__push;
static NODE_GETTER get_value_or_future__push;
static NODE_GETTER get__raise;
static NODE_GETTER get_value_or_future__raise;
static NODE_GETTER get__raise_error;
static NODE_GETTER get_value_or_future__raise_error;
static NODE_GETTER get__range;
static NODE_GETTER get_value_or_future__range;
static NODE_GETTER get__read;
static NODE_GETTER get_value_or_future__read;
static int poly_idx__read_from;
static NODE_GETTER get__read_from;
static int poly_idx__read_some_bytes_from;
static NODE_GETTER get__read_some_bytes_from;
static NODE_GETTER get__replace_all;
static NODE_GETTER get_value_or_future__replace_all;
static NODE_GETTER get__save_file;
static NODE_GETTER get_value_or_future__save_file;
static int poly_idx__sector_count_of;
static NODE_GETTER get__sector_count_of;
static int poly_idx__size_of;
static NODE_GETTER get__size_of;
static NODE_GETTER get__some;
static NODE_GETTER get_value_or_future__some;
static NODE_GETTER get__sort;
static NODE_GETTER get_value_or_future__sort;
static int poly_idx__status_change_time_of;
static NODE_GETTER get__status_change_time_of;
static NODE_GETTER get__std__and;
static NODE_GETTER get_value_or_future__std__and;
static NODE_GETTER get__std__bit_or;
static NODE_GETTER get_value_or_future__std__bit_or;
static NODE_GETTER get__std__equal;
static NODE_GETTER get_value_or_future__std__equal;
static NODE_GETTER get__std__key_value_pair;
static NODE_GETTER get_value_or_future__std__key_value_pair;
static NODE_GETTER get__std__less;
static NODE_GETTER get_value_or_future__std__less;
static NODE_GETTER get__std__negate;
static NODE_GETTER get_value_or_future__std__negate;
static NODE_GETTER get__std__not;
static NODE_GETTER get_value_or_future__std__not;
static NODE_GETTER get__std__or;
static NODE_GETTER get_value_or_future__std__or;
static NODE_GETTER get__std__plus;
static NODE_GETTER get_value_or_future__std__plus;
static NODE_GETTER get__std__sequence;
static NODE_GETTER get_value_or_future__std__sequence;
static NODE_GETTER get__std__string;
static NODE_GETTER get_value_or_future__std__string;
static NODE_GETTER get__std__true;
static NODE_GETTER get_value_or_future__std__true;
static NODE_GETTER get__string;
static NODE_GETTER get_value_or_future__string;
static NODE_GETTER get__to_string;
static NODE_GETTER get_value_or_future__to_string;
static NODE_GETTER get__to_utf8;
static NODE_GETTER get_value_or_future__to_utf8;
static NODE_GETTER get__true;
static NODE_GETTER get_value_or_future__true;
static NODE_GETTER get__types__object;
static NODE_GETTER get_value_or_future__types__object;
static NODE_GETTER get__types__string;
static NODE_GETTER get_value_or_future__types__string;
static NODE_GETTER get__undefined;
static NODE_GETTER get_value_or_future__undefined;
static NODE_GETTER get__unless;
static NODE_GETTER get_value_or_future__unless;
static int poly_idx__user_id_of;
static NODE_GETTER get__user_id_of;
static NODE_GETTER get__value_of;
static NODE_GETTER get_value_or_future__value_of;
static NODE_GETTER get__wait_to_read_from;
static NODE_GETTER get_value_or_future__wait_to_read_from;
static NODE_GETTER get__wait_to_write_to;
static NODE_GETTER get_value_or_future__wait_to_write_to;
static NODE_GETTER get__while;
static NODE_GETTER get_value_or_future__while;
static NODE_GETTER get__without_suffix;
static NODE_GETTER get_value_or_future__without_suffix;
static NODE_GETTER get__write;
static NODE_GETTER get_value_or_future__write;
static int poly_idx__write_some_bytes_to;
static NODE_GETTER get__write_some_bytes_to;
static int poly_idx__write_to;
static NODE_GETTER get__write_to;
static struct {
  NODE *_wget;
  NODE *_posix_open;
  NODE *_ioctl_value;
  NODE *_posix_unlink;
  NODE *_wait_for_io_ready;
  NODE *std__MODE;
  NODE *std__PARENTS;
  NODE *std__ioctl;
  NODE *std__get_terminal_size;
  NODE *std__device_of;
  NODE *std__inode_of;
  NODE *std__mode_of;
  NODE *std__link_count_of;
  NODE *std__user_id_of;
  NODE *std__group_id_of;
  NODE *std__size_of;
  NODE *std__block_size_of;
  NODE *std__sector_count_of;
  NODE *std__access_time_of;
  NODE *std__modification_time_of;
  NODE *std__status_change_time_of;
  NODE *std__creation_time_of;
  NODE *std__filename_of;
  NODE *std__file_type_of;
  NODE *std__pathname_of;
  NODE *std__fullname_of;
  NODE *std__is_a_directory;
  NODE *std__is_a_regular_file;
  NODE *std__is_a_link;
  NODE *std__listen;
  NODE *std__accept;
  NODE *std__connect;
  NODE *std__O_RDONLY;
  NODE *std__O_WRONLY;
  NODE *std__O_RDWR;
  NODE *std__O_CREAT;
  NODE *std__O_EXCL;
  NODE *std__O_NOCTTY;
  NODE *std__O_TRUNC;
  NODE *std__O_APPEND;
  NODE *std__O_NONBLOCK;
  NODE *std__O_ASYNC;
  NODE *std__UNKNOWN;
  NODE *std__FIFO;
  NODE *std__CHARACTER_DEVICE;
  NODE *std__DIRECTORY;
  NODE *std__BLOCK_DEVICE;
  NODE *std__REGULAR_FILE;
  NODE *std__LINK;
  NODE *std__SOCKET;
  NODE *std__EPERM;
  NODE *std__ENOENT;
  NODE *std__ESRCH;
  NODE *std__EINTR;
  NODE *std__EIO;
  NODE *std__ENXIO;
  NODE *std__E2BIG;
  NODE *std__ENOEXEC;
  NODE *std__EBADF;
  NODE *std__ECHILD;
  NODE *std__EAGAIN;
  NODE *std__ENOMEM;
  NODE *std__EACCES;
  NODE *std__EFAULT;
  NODE *std__ENOTBLK;
  NODE *std__EBUSY;
  NODE *std__EEXIST;
  NODE *std__EXDEV;
  NODE *std__ENODEV;
  NODE *std__ENOTDIR;
  NODE *std__EISDIR;
  NODE *std__EINVAL;
  NODE *std__ENFILE;
  NODE *std__EMFILE;
  NODE *std__ENOTTY;
  NODE *std__ETXTBSY;
  NODE *std__EFBIG;
  NODE *std__ENOSPC;
  NODE *std__ESPIPE;
  NODE *std__EROFS;
  NODE *std__EMLINK;
  NODE *std__EPIPE;
  NODE *std__EDOM;
  NODE *std__ERANGE;
  NODE *std__raise_error;
  NODE *std__check_error;
  NODE *std__errno;
  NODE *std__strerror;
  NODE *types__stat;
  NODE *std__stat;
  NODE *std__file_exists;
  NODE *types__file_descriptor;
  NODE *std__STDIN_FILENO;
  NODE *std__STDOUT_FILENO;
  NODE *std__STDERR_FILENO;
  NODE *std__create_file_descriptor;
  NODE *std__open_file_for_reading;
  NODE *std__open_file_for_writing;
  NODE *std__open_file_for_reading_and_writing;
  NODE *std__create_file;
  NODE *std__atomic_write_to;
  NODE *std__load_file;
  NODE *std__save_file;
  NODE *std__delete_file;
  NODE *std__get_pid;
  NODE *std__wait_pid;
  NODE *std__wait_for_io;
  NODE *std__current_path;
  NODE *std__chdir;
  NODE *std__change_directory;
  NODE *std__clib_mkdir;
  NODE *std__mkdir;
  NODE *std__create_directory;
  NODE *std__fullname;
  NODE *types__DIR;
  NODE *types__dirent;
  NODE *std__opendir;
  NODE *std__directory;
  NODE *types__addrinfo;
  NODE *std__get_network_addresses;
  NODE *std__get_network_address;
  NODE *std__writeln;
  NODE *std__ewriteln;
  NODE *std__readln;
  NODE *std__load;
  NODE *std__save;
} var;
static const char *var_names[] = {
  "wget",
  "posix_open",
  "ioctl_value",
  "posix_unlink",
  "wait_for_io_ready"
};
static NODE *unique__1_1;
static NODE *get__std__MODE(void) {
  return var.std__MODE;
}
static NODE *unique__2_1;
static NODE *get__std__PARENTS(void) {
  return var.std__PARENTS;
}
static int poly_idx__std__ioctl;
static void type__std__ioctl(void);
static NODE *get__std__ioctl(void) {
  return var.std__ioctl;
}
static int poly_idx__std__get_terminal_size;
static void type__std__get_terminal_size(void);
static NODE *get__std__get_terminal_size(void) {
  return var.std__get_terminal_size;
}
static int poly_idx__std__device_of;
static void type__std__device_of(void);
static NODE *get__std__device_of(void) {
  return var.std__device_of;
}
static int poly_idx__std__inode_of;
static void type__std__inode_of(void);
static NODE *get__std__inode_of(void) {
  return var.std__inode_of;
}
static int poly_idx__std__mode_of;
static void type__std__mode_of(void);
static NODE *get__std__mode_of(void) {
  return var.std__mode_of;
}
static int poly_idx__std__link_count_of;
static void type__std__link_count_of(void);
static NODE *get__std__link_count_of(void) {
  return var.std__link_count_of;
}
static int poly_idx__std__user_id_of;
static void type__std__user_id_of(void);
static NODE *get__std__user_id_of(void) {
  return var.std__user_id_of;
}
static int poly_idx__std__group_id_of;
static void type__std__group_id_of(void);
static NODE *get__std__group_id_of(void) {
  return var.std__group_id_of;
}
static int poly_idx__std__size_of;
static void type__std__size_of(void);
static NODE *get__std__size_of(void) {
  return var.std__size_of;
}
static int poly_idx__std__block_size_of;
static void type__std__block_size_of(void);
static NODE *get__std__block_size_of(void) {
  return var.std__block_size_of;
}
static int poly_idx__std__sector_count_of;
static void type__std__sector_count_of(void);
static NODE *get__std__sector_count_of(void) {
  return var.std__sector_count_of;
}
static int poly_idx__std__access_time_of;
static void type__std__access_time_of(void);
static NODE *get__std__access_time_of(void) {
  return var.std__access_time_of;
}
static int poly_idx__std__modification_time_of;
static void type__std__modification_time_of(void);
static NODE *get__std__modification_time_of(void) {
  return var.std__modification_time_of;
}
static int poly_idx__std__status_change_time_of;
static void type__std__status_change_time_of(void);
static NODE *get__std__status_change_time_of(void) {
  return var.std__status_change_time_of;
}
static int poly_idx__std__creation_time_of;
static void type__std__creation_time_of(void);
static NODE *get__std__creation_time_of(void) {
  return var.std__creation_time_of;
}
static int poly_idx__std__filename_of;
static void type__std__filename_of(void);
static NODE *get__std__filename_of(void) {
  return var.std__filename_of;
}
static int poly_idx__std__file_type_of;
static void type__std__file_type_of(void);
static NODE *get__std__file_type_of(void) {
  return var.std__file_type_of;
}
static int poly_idx__std__pathname_of;
static void type__std__pathname_of(void);
static NODE *get__std__pathname_of(void) {
  return var.std__pathname_of;
}
static int poly_idx__std__fullname_of;
static void type__std__fullname_of(void);
static NODE *get__std__fullname_of(void) {
  return var.std__fullname_of;
}
static int poly_idx__std__is_a_directory;
static void type__std__is_a_directory(void);
static NODE *get__std__is_a_directory(void) {
  return var.std__is_a_directory;
}
static int poly_idx__std__is_a_regular_file;
static void type__std__is_a_regular_file(void);
static NODE *get__std__is_a_regular_file(void) {
  return var.std__is_a_regular_file;
}
static int poly_idx__std__is_a_link;
static void type__std__is_a_link(void);
static NODE *get__std__is_a_link(void) {
  return var.std__is_a_link;
}
static int poly_idx__std__listen;
static void type__std__listen(void);
static NODE *get__std__listen(void) {
  return var.std__listen;
}
static int poly_idx__std__accept;
static void type__std__accept(void);
static NODE *get__std__accept(void) {
  return var.std__accept;
}
static int poly_idx__std__connect;
static void type__std__connect(void);
static NODE *get__std__connect(void) {
  return var.std__connect;
}
static NODE *get__std__O_RDONLY(void) {
  return var.std__O_RDONLY;
}
static NODE *get__std__O_WRONLY(void) {
  return var.std__O_WRONLY;
}
static NODE *get__std__O_RDWR(void) {
  return var.std__O_RDWR;
}
static NODE *get__std__O_CREAT(void) {
  return var.std__O_CREAT;
}
static NODE *get__std__O_EXCL(void) {
  return var.std__O_EXCL;
}
static NODE *get__std__O_NOCTTY(void) {
  return var.std__O_NOCTTY;
}
static NODE *get__std__O_TRUNC(void) {
  return var.std__O_TRUNC;
}
static NODE *get__std__O_APPEND(void) {
  return var.std__O_APPEND;
}
static NODE *get__std__O_NONBLOCK(void) {
  return var.std__O_NONBLOCK;
}
static NODE *get__std__O_ASYNC(void) {
  return var.std__O_ASYNC;
}
static NODE *get__std__UNKNOWN(void) {
  return var.std__UNKNOWN;
}
static NODE *get__std__FIFO(void) {
  return var.std__FIFO;
}
static NODE *get__std__CHARACTER_DEVICE(void) {
  return var.std__CHARACTER_DEVICE;
}
static NODE *get__std__DIRECTORY(void) {
  return var.std__DIRECTORY;
}
static NODE *get__std__BLOCK_DEVICE(void) {
  return var.std__BLOCK_DEVICE;
}
static NODE *get__std__REGULAR_FILE(void) {
  return var.std__REGULAR_FILE;
}
static NODE *get__std__LINK(void) {
  return var.std__LINK;
}
static NODE *get__std__SOCKET(void) {
  return var.std__SOCKET;
}
static NODE *get__std__EPERM(void) {
  return var.std__EPERM;
}
static NODE *get__std__ENOENT(void) {
  return var.std__ENOENT;
}
static NODE *get__std__ESRCH(void) {
  return var.std__ESRCH;
}
static NODE *get__std__EINTR(void) {
  return var.std__EINTR;
}
static NODE *get__std__EIO(void) {
  return var.std__EIO;
}
static NODE *get__std__ENXIO(void) {
  return var.std__ENXIO;
}
static NODE *get__std__E2BIG(void) {
  return var.std__E2BIG;
}
static NODE *get__std__ENOEXEC(void) {
  return var.std__ENOEXEC;
}
static NODE *get__std__EBADF(void) {
  return var.std__EBADF;
}
static NODE *get__std__ECHILD(void) {
  return var.std__ECHILD;
}
static NODE *get__std__EAGAIN(void) {
  return var.std__EAGAIN;
}
static NODE *get__std__ENOMEM(void) {
  return var.std__ENOMEM;
}
static NODE *get__std__EACCES(void) {
  return var.std__EACCES;
}
static NODE *get__std__EFAULT(void) {
  return var.std__EFAULT;
}
static NODE *get__std__ENOTBLK(void) {
  return var.std__ENOTBLK;
}
static NODE *get__std__EBUSY(void) {
  return var.std__EBUSY;
}
static NODE *get__std__EEXIST(void) {
  return var.std__EEXIST;
}
static NODE *get__std__EXDEV(void) {
  return var.std__EXDEV;
}
static NODE *get__std__ENODEV(void) {
  return var.std__ENODEV;
}
static NODE *get__std__ENOTDIR(void) {
  return var.std__ENOTDIR;
}
static NODE *get__std__EISDIR(void) {
  return var.std__EISDIR;
}
static NODE *get__std__EINVAL(void) {
  return var.std__EINVAL;
}
static NODE *get__std__ENFILE(void) {
  return var.std__ENFILE;
}
static NODE *get__std__EMFILE(void) {
  return var.std__EMFILE;
}
static NODE *get__std__ENOTTY(void) {
  return var.std__ENOTTY;
}
static NODE *get__std__ETXTBSY(void) {
  return var.std__ETXTBSY;
}
static NODE *get__std__EFBIG(void) {
  return var.std__EFBIG;
}
static NODE *get__std__ENOSPC(void) {
  return var.std__ENOSPC;
}
static NODE *get__std__ESPIPE(void) {
  return var.std__ESPIPE;
}
static NODE *get__std__EROFS(void) {
  return var.std__EROFS;
}
static NODE *get__std__EMLINK(void) {
  return var.std__EMLINK;
}
static NODE *get__std__EPIPE(void) {
  return var.std__EPIPE;
}
static NODE *get__std__EDOM(void) {
  return var.std__EDOM;
}
static NODE *get__std__ERANGE(void) {
  return var.std__ERANGE;
}
static NODE *func__81_1;
static void entry__81_1(void);
static FRAME_INFO frame__81_1 = {3, {"cmd", "args", "info"}};
static NODE *func__81_2;
static void entry__81_2(void);
static FRAME_INFO frame__81_2 = {2, {"arg", "info"}};
static void cont__81_3(void);
static void cont__81_4(void);
static NODE *string__81_5;
static NODE *string__81_6;
static void cont__81_7(void);
static void cont__81_8(void);
static void cont__81_9(void);
static void cont__81_10(void);
static void cont__81_11(void);
static NODE *string__81_12;
static NODE *string__81_13;
static void cont__81_14(void);
static NODE *get__std__raise_error(void) {
  return var.std__raise_error;
}
static NODE *func__82_1;
static void entry__82_1(void);
static FRAME_INFO frame__82_1 = {2, {"err", "args"}};
static void cont__82_2(void);
static NODE *get__std__check_error(void) {
  return var.std__check_error;
}
static void entry__83_1(void);
static NODE *func__83_1;
static NODE *get__std__errno(void) {
  return var.std__errno;
}
static void entry__84_1(void);
static NODE *func__84_1;
static NODE *get__std__strerror(void) {
  return var.std__strerror;
}

typedef struct STAT_BUFFER STAT_BUFFER;
struct STAT_BUFFER {
  void *new_location;
  struct stat stat;
};

static STAT_BUFFER *collect_stat_buffer(STAT_BUFFER *buf);

#if defined(__APPLE__) && defined(__MACH__)
  #define st_atim st_atimespec
  #define st_ctim st_ctimespec
  #define st_mtim st_mtimespec
#endif

typedef struct {
  void *type;
  ATTRIBUTES *attributes;
  STAT_BUFFER *buf;
} STAT;
static NODE *get__types__stat(void) {
  return var.types__stat;
}
static NODE *create__types__stat(STAT_BUFFER *buf);

static long func__types__stat___debug_string(NODE *node, int indent, int max_depth, char *buf);

extern NODE *create__types__date_and_time(int64_t seconds, int32_t nanoseconds);
static void entry__92_1(void);
static NODE *func__92_1;
static NODE *get__std__stat(void) {
  return var.std__stat;
}
static void entry__93_1(void);
static NODE *func__93_1;
static NODE *get__std__file_exists(void) {
  return var.std__file_exists;
}
static void entry__94_1(void);
static NODE *func__94_1;
static void entry__95_1(void);
static NODE *func__95_1;
static void entry__96_1(void);
static NODE *func__96_1;
static void entry__97_1(void);
static NODE *func__97_1;
static void entry__98_1(void);
static NODE *func__98_1;
static void entry__99_1(void);
static NODE *func__99_1;
static void entry__100_1(void);
static NODE *func__100_1;
static void entry__101_1(void);
static NODE *func__101_1;
static void entry__102_1(void);
static NODE *func__102_1;
static void entry__103_1(void);
static NODE *func__103_1;
static void entry__104_1(void);
static NODE *func__104_1;
static void entry__105_1(void);
static NODE *func__105_1;
static void entry__106_1(void);
static NODE *func__106_1;
static void entry__107_1(void);
static NODE *func__107_1;
static void entry__108_1(void);
static NODE *func__108_1;

typedef struct {
  void *type;
  ATTRIBUTES *attributes;
  int fd;
} FILE_DESCRIPTOR;
static NODE *get__types__file_descriptor(void) {
  return var.types__file_descriptor;
}
extern NODE *create__types__file_descriptor(int fd);

static long func__types__file_descriptor___debug_string(NODE *node, int indent, int max_depth, char *buf);
static NODE *get__std__STDIN_FILENO(void) {
  return var.std__STDIN_FILENO;
}
static NODE *get__std__STDOUT_FILENO(void) {
  return var.std__STDOUT_FILENO;
}
static NODE *get__std__STDERR_FILENO(void) {
  return var.std__STDERR_FILENO;
}
static void entry__115_1(void);
static NODE *func__115_1;
static NODE *get__std__create_file_descriptor(void) {
  return var.std__create_file_descriptor;
}
static void entry__116_1(void);
static NODE *func__116_1;
static void entry__117_1(void);
static NODE *func__117_1;
static void entry__118_1(void);
static NODE *func__118_1;
static void entry__119_1(void);
static NODE *func__119_1;
static NODE *func__120_1;
static void entry__120_1(void);
static FRAME_INFO frame__120_1 = {1, {"filename"}};
static NODE *get__std__open_file_for_reading(void) {
  return var.std__open_file_for_reading;
}
static NODE *func__121_1;
static void entry__121_1(void);
static FRAME_INFO frame__121_1 = {1, {"filename"}};
static NODE *get__std__open_file_for_writing(void) {
  return var.std__open_file_for_writing;
}
static NODE *func__122_1;
static void entry__122_1(void);
static FRAME_INFO frame__122_1 = {1, {"filename"}};
static NODE *get__std__open_file_for_reading_and_writing(void) {
  return var.std__open_file_for_reading_and_writing;
}
static NODE *func__123_1;
static void entry__123_1(void);
static FRAME_INFO frame__123_1 = {1, {"filename"}};
static void cont__123_2(void);
static void cont__123_3(void);
static NODE *get__std__create_file(void) {
  return var.std__create_file;
}
static void entry__124_1(void);
static NODE *func__124_1;
static void entry__125_1(void);
static NODE *func__125_1;
static NODE *func__126_1;
static void entry__126_1(void);
static FRAME_INFO frame__126_1 = {3, {"fd", "amount", "return"}};
static void cont__126_2(void);
static NODE *func__126_3;
static void entry__126_3(void);
static FRAME_INFO frame__126_3 = {4, {"amount", "fd", "return", "buf"}};
static NODE *func__126_4;
static void entry__126_4(void);
static FRAME_INFO frame__126_4 = {4, {"amount", "fd", "return", "buf"}};
static void cont__126_5(void);
static NODE *func__126_6;
static void entry__126_6(void);
static FRAME_INFO frame__126_6 = {6, {"fd", "amount", "return", "buf", "some_bytes", "len"}};
static void cont__126_7(void);
static void cont__126_8(void);
static void cont__126_9(void);
static void cont__126_10(void);
static NODE *func__126_11;
static void entry__126_11(void);
static FRAME_INFO frame__126_11 = {2, {"return", "buf"}};
static void cont__126_12(void);
static void cont__126_13(void);
static void cont__126_14(void);
static void cont__126_15(void);
static void cont__126_16(void);
static void cont__126_17(void);
static void cont__126_18(void);
static void entry__127_1(void);
static NODE *func__127_1;
static NODE *func__128_1;
static void entry__128_1(void);
static FRAME_INFO frame__128_1 = {4, {"fd", "args", "return", "data"}};
static void cont__128_2(void);
static NODE *func__128_3;
static void entry__128_3(void);
static FRAME_INFO frame__128_3 = {3, {"data", "fd", "return"}};
static void cont__128_4(void);
static void cont__128_5(void);
static NODE *func__128_6;
static void entry__128_6(void);
static FRAME_INFO frame__128_6 = {4, {"fd", "data", "return", "bytes_written"}};
static void cont__128_7(void);
static void cont__128_8(void);
static void cont__128_9(void);
static NODE *func__128_10;
static void entry__128_10(void);
static FRAME_INFO frame__128_10 = {1, {"return"}};
static void cont__128_11(void);
static void cont__128_12(void);
static NODE *func__128_13;
static void entry__128_13(void);
static FRAME_INFO frame__128_13 = {0, {}};
static NODE *string__128_14;
static void cont__128_15(void);
static void cont__128_16(void);
static void cont__128_17(void);
static void cont__128_18(void);
static void cont__128_19(void);
static void cont__128_20(void);
static void cont__128_21(void);
static void cont__128_22(void);
static NODE *func__128_23;
static void entry__128_23(void);
static FRAME_INFO frame__128_23 = {1, {"return"}};
static void cont__128_24(void);
static NODE *func__129_1;
static void entry__129_1(void);
static FRAME_INFO frame__129_1 = {4, {"fd", "args", "return", "data"}};
static void cont__129_2(void);
static NODE *func__129_3;
static void entry__129_3(void);
static FRAME_INFO frame__129_3 = {3, {"data", "fd", "return"}};
static void cont__129_4(void);
static void cont__129_5(void);
static NODE *func__129_6;
static void entry__129_6(void);
static FRAME_INFO frame__129_6 = {4, {"fd", "data", "return", "bytes_written"}};
static void cont__129_7(void);
static void cont__129_8(void);
static NODE *func__129_9;
static void entry__129_9(void);
static FRAME_INFO frame__129_9 = {1, {"return"}};
static void cont__129_10(void);
static void cont__129_11(void);
static NODE *func__129_12;
static void entry__129_12(void);
static FRAME_INFO frame__129_12 = {0, {}};
static void cont__129_13(void);
static void cont__129_14(void);
static void cont__129_15(void);
static void cont__129_16(void);
static void cont__129_17(void);
static void cont__129_18(void);
static void cont__129_19(void);
static void cont__129_20(void);
static NODE *func__129_21;
static void entry__129_21(void);
static FRAME_INFO frame__129_21 = {1, {"return"}};
static void cont__129_22(void);
static NODE *get__std__atomic_write_to(void) {
  return var.std__atomic_write_to;
}
static NODE *func__130_1;
static void entry__130_1(void);
static FRAME_INFO frame__130_1 = {2, {"filename", "fd"}};
static void cont__130_2(void);
static void cont__130_3(void);
static NODE *func__130_4;
static void entry__130_4(void);
static FRAME_INFO frame__130_4 = {2, {"fd", "buf"}};
static NODE *func__130_5;
static void entry__130_5(void);
static FRAME_INFO frame__130_5 = {3, {"break", "fd", "buf"}};
static NODE *func__130_6;
static void entry__130_6(void);
static FRAME_INFO frame__130_6 = {4, {"fd", "break", "buf", "some_bytes"}};
static void cont__130_7(void);
static void cont__130_8(void);
static void cont__130_9(void);
static void cont__130_10(void);
static void cont__130_11(void);
static void cont__130_12(void);
static void cont__130_13(void);
static void cont__130_14(void);
static NODE *func__130_15;
static void entry__130_15(void);
static FRAME_INFO frame__130_15 = {0, {}};
static NODE *get__std__load_file(void) {
  return var.std__load_file;
}
static NODE *func__131_1;
static void entry__131_1(void);
static FRAME_INFO frame__131_1 = {4, {"filename", "data", "return", "fd"}};
static void cont__131_2(void);
static void cont__131_3(void);
static NODE *func__131_4;
static void entry__131_4(void);
static FRAME_INFO frame__131_4 = {3, {"return", "fd", "data"}};
static void cont__131_5(void);
static void cont__131_6(void);
static NODE *func__131_7;
static void entry__131_7(void);
static FRAME_INFO frame__131_7 = {2, {"fd", "data"}};
static void cont__131_8(void);
static NODE *func__131_9;
static void entry__131_9(void);
static FRAME_INFO frame__131_9 = {3, {"return", "fd", "data"}};
static void cont__131_10(void);
static NODE *func__131_11;
static void entry__131_11(void);
static FRAME_INFO frame__131_11 = {1, {"fd"}};
static void cont__131_12(void);
static void cont__131_13(void);
static NODE *func__131_14;
static void entry__131_14(void);
static FRAME_INFO frame__131_14 = {2, {"return", "filename"}};
static void cont__131_15(void);
static void cont__131_16(void);
static NODE *func__131_17;
static void entry__131_17(void);
static FRAME_INFO frame__131_17 = {1, {"filename"}};
static NODE *string__131_18;
static NODE *string__131_19;
static void cont__131_20(void);
static void cont__131_21(void);
static void cont__131_22(void);
static NODE *get__std__save_file(void) {
  return var.std__save_file;
}
static void entry__132_1(void);
static NODE *func__132_1;
static void entry__133_1(void);
static NODE *func__133_1;
static NODE *func__134_1;
static void entry__134_1(void);
static FRAME_INFO frame__134_1 = {4, {"fd", "request", "value", "return"}};
static void cont__134_2(void);
static void cont__134_3(void);
static NODE *func__134_4;
static void entry__134_4(void);
static FRAME_INFO frame__134_4 = {3, {"fd", "request", "value"}};
static void cont__134_5(void);
static void cont__134_6(void);
static void cont__134_7(void);
static NODE *func__134_8;
static void entry__134_8(void);
static FRAME_INFO frame__134_8 = {0, {}};
static NODE *string__134_9;
static NODE *func__134_10;
static void entry__134_10(void);
static FRAME_INFO frame__134_10 = {4, {"return", "fd", "request", "value"}};
static void cont__134_11(void);
static void cont__134_12(void);
static void entry__135_1(void);
static NODE *func__135_1;
static void entry__136_1(void);
static NODE *func__136_1;
static NODE *func__137_1;
static void entry__137_1(void);
static FRAME_INFO frame__137_1 = {2, {"filename", "return"}};
static void cont__137_2(void);
static void cont__137_3(void);
static NODE *func__137_4;
static void entry__137_4(void);
static FRAME_INFO frame__137_4 = {1, {"filename"}};
static void cont__137_5(void);
static void cont__137_6(void);
static void cont__137_7(void);
static NODE *func__137_8;
static void entry__137_8(void);
static FRAME_INFO frame__137_8 = {1, {"filename"}};
static NODE *string__137_9;
static NODE *string__137_10;
static void cont__137_11(void);
static NODE *func__137_12;
static void entry__137_12(void);
static FRAME_INFO frame__137_12 = {2, {"return", "filename"}};
static void cont__137_13(void);
static void cont__137_14(void);
static void cont__137_15(void);
static NODE *get__std__delete_file(void) {
  return var.std__delete_file;
}
static void entry__138_1(void);
static NODE *func__138_1;
static void entry__139_1(void);
static NODE *func__139_1;
static NODE *get__std__get_pid(void) {
  return var.std__get_pid;
}
static void entry__140_1(void);
static NODE *func__140_1;
static NODE *get__std__wait_pid(void) {
  return var.std__wait_pid;
}
static NODE *func__141_1;
static void entry__141_1(void);
static FRAME_INFO frame__141_1 = {11, {"read_descriptors", "write_descriptors", "except_descriptors", "timeout", "success", "child_changed_state", "window_changed_size", "input_count", "output_count", "exception_count", "descriptors"}};
static void cont__141_2(void);
static void cont__141_3(void);
static void cont__141_4(void);
static void cont__141_5(void);
static void cont__141_6(void);
static void cont__141_7(void);
static void cont__141_8(void);
static void cont__141_9(void);
static void cont__141_10(void);
static NODE *get__std__wait_for_io(void) {
  return var.std__wait_for_io;
}
static void entry__142_1(void);
static NODE *func__142_1;
static NODE *get__std__current_path(void) {
  return var.std__current_path;
}
static void entry__143_1(void);
static NODE *func__143_1;
static NODE *get__std__chdir(void) {
  return var.std__chdir;
}
static NODE *func__144_1;
static void entry__144_1(void);
static FRAME_INFO frame__144_1 = {1, {"path"}};
static void cont__144_2(void);
static void cont__144_3(void);
static void cont__144_4(void);
static NODE *func__144_5;
static void entry__144_5(void);
static FRAME_INFO frame__144_5 = {1, {"path"}};
static NODE *string__144_6;
static NODE *string__144_7;
static void cont__144_8(void);
static NODE *get__std__change_directory(void) {
  return var.std__change_directory;
}
static void entry__145_1(void);
static NODE *func__145_1;
static NODE *get__std__clib_mkdir(void) {
  return var.std__clib_mkdir;
}
static NODE *func__146_1;
static void entry__146_1(void);
static FRAME_INFO frame__146_1 = {6, {"options", "path", "mode", "do_create_parent_folders", "fail", "create_parent_folders"}};
static NODE *func__146_2;
static void entry__146_2(void);
static FRAME_INFO frame__146_2 = {3, {"mode", "do_create_parent_folders", "path"}};
static void cont__146_3(void);
static NODE *string__146_4;
static void cont__146_5(void);
static NODE *string__146_6;
static void cont__146_7(void);
static NODE *string__146_8;
static void cont__146_9(void);
static NODE *string__146_10;
static void cont__146_11(void);
static NODE *string__146_12;
static NODE *func__146_13;
static void entry__146_13(void);
static FRAME_INFO frame__146_13 = {4, {"partial_path", "create_parent_folders", "mode", "fail"}};
static void cont__146_14(void);
static void cont__146_15(void);
static void cont__146_16(void);
static void cont__146_17(void);
static NODE *func__146_18;
static void entry__146_18(void);
static FRAME_INFO frame__146_18 = {4, {"create_parent_folders", "partial_path", "mode", "fail"}};
static void cont__146_19(void);
static void cont__146_20(void);
static void cont__146_21(void);
static NODE *func__146_22;
static void entry__146_22(void);
static FRAME_INFO frame__146_22 = {0, {}};
static void cont__146_23(void);
static void cont__146_24(void);
static void cont__146_25(void);
static void cont__146_26(void);
static void cont__146_27(void);
static void cont__146_28(void);
static void cont__146_29(void);
static void cont__146_30(void);
static NODE *func__146_31;
static void entry__146_31(void);
static FRAME_INFO frame__146_31 = {2, {"create_parent_folders", "path"}};
static void cont__146_32(void);
static void cont__146_33(void);
static void cont__146_34(void);
static NODE *func__146_35;
static void entry__146_35(void);
static FRAME_INFO frame__146_35 = {2, {"do_create_parent_folders", "fail"}};
static NODE *func__146_36;
static void entry__146_36(void);
static FRAME_INFO frame__146_36 = {0, {}};
static void cont__146_37(void);
static void cont__146_38(void);
static void cont__146_39(void);
static NODE *get__std__mkdir(void) {
  return var.std__mkdir;
}
static NODE *func__147_1;
static void entry__147_1(void);
static FRAME_INFO frame__147_1 = {2, {"path", "mode"}};
static void cont__147_2(void);
static void cont__147_3(void);
static void cont__147_4(void);
static NODE *func__147_5;
static void entry__147_5(void);
static FRAME_INFO frame__147_5 = {1, {"path"}};
static NODE *string__147_6;
static void cont__147_7(void);
static NODE *get__std__create_directory(void) {
  return var.std__create_directory;
}
static NODE *func__148_1;
static void entry__148_1(void);
static FRAME_INFO frame__148_1 = {1, {"pathname"}};
static void cont__148_2(void);
static NODE *func__148_3;
static void entry__148_3(void);
static FRAME_INFO frame__148_3 = {1, {"pathname"}};
static void cont__148_4(void);
static NODE *string__148_5;
static void cont__148_6(void);
static void cont__148_7(void);
static void cont__148_8(void);
static NODE *func__148_9;
static void entry__148_9(void);
static FRAME_INFO frame__148_9 = {1, {"pathname"}};
static void cont__148_10(void);
static void cont__148_11(void);
static NODE *string__148_12;
static void cont__148_13(void);
static void cont__148_14(void);
static void cont__148_15(void);
static NODE *string__148_16;
static void cont__148_17(void);
static void cont__148_18(void);
static NODE *func__148_19;
static void entry__148_19(void);
static FRAME_INFO frame__148_19 = {2, {"break", "pathname"}};
static NODE *func__148_20;
static void entry__148_20(void);
static FRAME_INFO frame__148_20 = {3, {"pathname", "break", "orig_pathname"}};
static void cont__148_21(void);
static void cont__148_22(void);
static NODE *string__148_23;
static void cont__148_24(void);
static void cont__148_25(void);
static void cont__148_26(void);
static void cont__148_27(void);
static void cont__148_28(void);
static void cont__148_29(void);
static void cont__148_30(void);
static NODE *func__148_31;
static void entry__148_31(void);
static FRAME_INFO frame__148_31 = {1, {"pathname"}};
static void cont__148_32(void);
static void cont__148_33(void);
static void cont__148_34(void);
static NODE *get__std__fullname(void) {
  return var.std__fullname;
}

typedef struct {
  void *type;
  ATTRIBUTES *attributes;
  DIR *dir;
} DIRECTORY_HANDLE;
static NODE *get__types__DIR(void) {
  return var.types__DIR;
}
static NODE *create__types__DIR(DIR *dir);

static long func__types__DIR___debug_string(NODE *node, int indent, int max_depth, char *buf);

typedef struct DIRENT_DATA DIRENT_DATA;
struct DIRENT_DATA {
  void *new_location;
  ino_t d_ino; // inode number
  unsigned char d_type; //type of file; not supported by all filesystem types
  char d_name[0]; // filename
};

static DIRENT_DATA *collect_dirent_data(DIRENT_DATA *buf);

typedef struct {
  void *type;
  ATTRIBUTES *attributes;
  DIRENT_DATA *dirent;
} DIRENT;
static NODE *get__types__dirent(void) {
  return var.types__dirent;
}
static NODE *create__types__dirent(DIRENT_DATA *dirent);

static long func__types__dirent___debug_string(NODE *node, int indent, int max_depth, char *buf);
static void entry__157_1(void);
static NODE *func__157_1;
static NODE *get__std__opendir(void) {
  return var.std__opendir;
}
static void entry__158_1(void);
static NODE *func__158_1;
static void entry__159_1(void);
static NODE *func__159_1;
static void entry__160_1(void);
static NODE *func__160_1;
static void entry__161_1(void);
static NODE *func__161_1;
static void entry__162_1(void);
static NODE *func__162_1;
static NODE *func__163_1;
static void entry__163_1(void);
static FRAME_INFO frame__163_1 = {1, {"self"}};
static void cont__163_2(void);
static void cont__163_3(void);
static void cont__163_4(void);
static NODE *func__164_1;
static void entry__164_1(void);
static FRAME_INFO frame__164_1 = {1, {"self"}};
static void cont__164_2(void);
static void cont__164_3(void);
static NODE *func__165_1;
static void entry__165_1(void);
static FRAME_INFO frame__165_1 = {1, {"self"}};
static void cont__165_2(void);
static void cont__165_3(void);
static NODE *func__166_1;
static void entry__166_1(void);
static FRAME_INFO frame__166_1 = {1, {"self"}};
static void cont__166_2(void);
static void cont__166_3(void);
static NODE *func__167_1;
static void entry__167_1(void);
static FRAME_INFO frame__167_1 = {5, {"options", "pathname", "do_sort", "entries", "dir"}};
static void cont__167_2(void);
static void cont__167_3(void);
static void cont__167_4(void);
static void cont__167_5(void);
static void cont__167_6(void);
static NODE *func__167_7;
static void entry__167_7(void);
static FRAME_INFO frame__167_7 = {3, {"break", "dir", "entries"}};
static NODE *func__167_8;
static void entry__167_8(void);
static FRAME_INFO frame__167_8 = {4, {"dir", "break", "entries", "entry"}};
static void cont__167_9(void);
static void cont__167_10(void);
static void cont__167_11(void);
static void cont__167_12(void);
static NODE *string__167_13;
static NODE *string__167_14;
static void cont__167_15(void);
static NODE *func__167_16;
static void entry__167_16(void);
static FRAME_INFO frame__167_16 = {2, {"entries", "entry"}};
static void cont__167_17(void);
static NODE *func__167_18;
static void entry__167_18(void);
static FRAME_INFO frame__167_18 = {0, {}};
static void cont__167_19(void);
static void cont__167_20(void);
static void cont__167_21(void);
static NODE *func__167_22;
static void entry__167_22(void);
static FRAME_INFO frame__167_22 = {1, {"entries"}};
static NODE *func__167_23;
static void entry__167_23(void);
static FRAME_INFO frame__167_23 = {2, {"left", "right"}};
static void cont__167_24(void);
static void cont__167_25(void);
static void cont__167_26(void);
static void cont__167_27(void);
static void cont__167_28(void);
static NODE *get__std__directory(void) {
  return var.std__directory;
}

typedef struct LIST_DATA LIST_DATA;
struct LIST_DATA {
  long size;
  long length;
  NODE **items;
};

extern NODE *create__types__list(long length, LIST_DATA *data);

typedef struct ADDRINFO_DATA ADDRINFO_DATA;
struct ADDRINFO_DATA {
  void *new_location;
  int family;
    // e.g. AF_INET or AF_INET6
  int type;
    // e.g. SOCK_STREAM or SOCK_DGRAM
  int protocol;
    // this is the same number which appears on the protocol field in the
    // IP header of a packet
  struct sockaddr sockaddr;
};

static ADDRINFO_DATA *collect_addrinfo_data(ADDRINFO_DATA *buf);

typedef struct {
  void *type;
  ATTRIBUTES *attributes;
  ADDRINFO_DATA *data;
} ADDRINFO;
static NODE *get__types__addrinfo(void) {
  return var.types__addrinfo;
}
static NODE *create__types__addrinfo(ADDRINFO_DATA *data);

static long func__types__addrinfo___debug_string(NODE *node, int indent, int max_depth, char *buf);
static void entry__175_1(void);
static NODE *func__175_1;
static NODE *get__std__get_network_addresses(void) {
  return var.std__get_network_addresses;
}
static void entry__176_1(void);
static NODE *func__176_1;
static NODE *get__std__get_network_address(void) {
  return var.std__get_network_address;
}
static void entry__177_1(void);
static NODE *func__177_1;
static NODE *func__178_1;
static void entry__178_1(void);
static FRAME_INFO frame__178_1 = {2, {"uri", "port"}};
static void cont__178_2(void);
static void entry__179_1(void);
static NODE *func__179_1;
static NODE *func__180_1;
static void entry__180_1(void);
static FRAME_INFO frame__180_1 = {2, {"uri", "port"}};
static void cont__180_2(void);
static void entry__181_1(void);
static NODE *func__181_1;
static int dyna_idx__std__write;
static NODE *get__std__write(void) {
  return get_dynamic_slot(dyna_idx__std__write);
}
static void define__std__write(NODE *node) {
  define_dynamic_slot(dyna_idx__std__write, node);
}
static NODE *func__182_1;
static void entry__182_1(void);
static FRAME_INFO frame__182_1 = {1, {"args"}};
static void cont__182_2(void);
static void cont__182_3(void);
static NODE *func__183_1;
static void entry__183_1(void);
static FRAME_INFO frame__183_1 = {1, {"args"}};
static NODE *get__std__writeln(void) {
  return var.std__writeln;
}
static int dyna_idx__std__ewrite;
static NODE *get__std__ewrite(void) {
  return get_dynamic_slot(dyna_idx__std__ewrite);
}
static void define__std__ewrite(NODE *node) {
  define_dynamic_slot(dyna_idx__std__ewrite, node);
}
static NODE *func__184_1;
static void entry__184_1(void);
static FRAME_INFO frame__184_1 = {1, {"args"}};
static void cont__184_2(void);
static void cont__184_3(void);
static NODE *func__185_1;
static void entry__185_1(void);
static FRAME_INFO frame__185_1 = {1, {"args"}};
static NODE *get__std__ewriteln(void) {
  return var.std__ewriteln;
}
static int dyna_idx__std__read;
static NODE *get__std__read(void) {
  return get_dynamic_slot(dyna_idx__std__read);
}
static void define__std__read(NODE *node) {
  define_dynamic_slot(dyna_idx__std__read, node);
}
static NODE *func__186_1;
static void entry__186_1(void);
static FRAME_INFO frame__186_1 = {1, {"n"}};
static NODE *func__187_1;
static void entry__187_1(void);
static FRAME_INFO frame__187_1 = {2, {"return", "buf"}};
static NODE *func__187_2;
static void entry__187_2(void);
static FRAME_INFO frame__187_2 = {3, {"return", "buf", "chr"}};
static void cont__187_3(void);
static void cont__187_4(void);
static NODE *func__187_5;
static void entry__187_5(void);
static FRAME_INFO frame__187_5 = {1, {"chr"}};
static void cont__187_6(void);
static void cont__187_7(void);
static NODE *func__187_8;
static void entry__187_8(void);
static FRAME_INFO frame__187_8 = {2, {"return", "buf"}};
static void cont__187_9(void);
static void cont__187_10(void);
static void cont__187_11(void);
static NODE *get__std__readln(void) {
  return var.std__readln;
}
static NODE *func__188_1;
static void entry__188_1(void);
static FRAME_INFO frame__188_1 = {1, {"filename"}};
static NODE *string__188_2;
static void cont__188_3(void);
static NODE *func__188_4;
static void entry__188_4(void);
static FRAME_INFO frame__188_4 = {2, {"filename", "buf"}};
static NODE *string__188_5;
static NODE *string__188_6;
static NODE *string__188_7;
static void cont__188_8(void);
static NODE *func__188_9;
static void entry__188_9(void);
static FRAME_INFO frame__188_9 = {1, {"buf"}};
static NODE *func__188_10;
static void entry__188_10(void);
static FRAME_INFO frame__188_10 = {1, {"filename"}};
static NODE *string__188_11;
static NODE *string__188_12;
static void cont__188_13(void);
static NODE *func__188_14;
static void entry__188_14(void);
static FRAME_INFO frame__188_14 = {1, {"filename"}};
static NODE *get__std__load(void) {
  return var.std__load;
}
static NODE *func__189_1;
static void entry__189_1(void);
static FRAME_INFO frame__189_1 = {4, {"options", "filename", "data", "do_create_directory"}};
static void cont__189_2(void);
static void cont__189_3(void);
static NODE *func__189_4;
static void entry__189_4(void);
static FRAME_INFO frame__189_4 = {2, {"filename", "path"}};
static void cont__189_5(void);
static void cont__189_6(void);
static void cont__189_7(void);
static void cont__189_8(void);
static NODE *func__189_9;
static void entry__189_9(void);
static FRAME_INFO frame__189_9 = {1, {"path"}};
static void cont__189_10(void);
static void cont__189_11(void);
static void cont__189_12(void);
static NODE *get__std__save(void) {
  return var.std__save;
}
static NODE *string__192_1;
static void cont__192_2(void);
void run__basic__io(void);

static CONTINUATION_INFO continuation_info[] = {
  {type__std__ioctl, NULL, 43, 43, 2, 11},
  {type__std__get_terminal_size, NULL, 44, 44, 2, 23},
  {type__std__device_of, NULL, 45, 45, 2, 15},
  {type__std__inode_of, NULL, 55, 55, 2, 14},
  {type__std__mode_of, NULL, 64, 64, 2, 13},
  {type__std__link_count_of, NULL, 76, 76, 2, 19},
  {type__std__user_id_of, NULL, 86, 86, 2, 16},
  {type__std__group_id_of, NULL, 95, 95, 2, 17},
  {type__std__size_of, NULL, 104, 104, 2, 13},
  {type__std__block_size_of, NULL, 113, 113, 2, 19},
  {type__std__sector_count_of, NULL, 127, 127, 2, 21},
  {type__std__access_time_of, NULL, 138, 138, 2, 20},
  {type__std__modification_time_of, NULL, 153, 153, 2, 26},
  {type__std__status_change_time_of, NULL, 165, 165, 2, 27},
  {type__std__creation_time_of, NULL, 178, 178, 2, 22},
  {type__std__filename_of, NULL, 192, 192, 2, 17},
  {type__std__file_type_of, NULL, 195, 195, 2, 18},
  {type__std__pathname_of, NULL, 196, 196, 2, 17},
  {type__std__fullname_of, NULL, 197, 197, 2, 17},
  {type__std__is_a_directory, NULL, 198, 198, 2, 20},
  {type__std__is_a_regular_file, NULL, 199, 199, 2, 23},
  {type__std__is_a_link, NULL, 200, 200, 2, 15},
  {type__std__listen, NULL, 201, 201, 2, 12},
  {type__std__accept, NULL, 202, 202, 2, 12},
  {type__std__connect, NULL, 203, 203, 2, 13},
  {run__basic__io, NULL, 41, 41, 1, 19},
  {cont__192_2, NULL, },
  {entry__81_2, NULL, 284, 284, 42, 52},
  {cont__81_3, &frame__81_2, 284, 284, 59, 71},
  {cont__81_4, &frame__81_2, 284, 284, 39, 77},
  {cont__81_7, &frame__81_2, 284, 284, 24, 77},
  {cont__81_8, &frame__81_2, 284, 284, 77, 77},
  {entry__81_1, NULL, 284, 284, 3, 77},
  {cont__81_9, &frame__81_1, 285, 285, 41, 52},
  {cont__81_10, &frame__81_1, 285, 285, 27, 53},
  {cont__81_11, &frame__81_1, 285, 285, 9, 67},
  {cont__81_14, &frame__81_1, 285, 285, 3, 67},
  {entry__82_1, NULL, 287, 287, 35, 41},
  {cont__82_2, &frame__82_1, 287, 287, 32, 59},
  {entry__83_1, NULL, 298, 301, 3, 2},
  {entry__84_1, NULL, 311, 314, 3, 2},
  {entry__92_1, NULL, 393, 402, 3, 2},
  {entry__93_1, NULL, 411, 418, 3, 2},
  {entry__94_1, NULL, 421, 424, 3, 2},
  {entry__95_1, NULL, 427, 430, 3, 2},
  {entry__96_1, NULL, 433, 437, 3, 2},
  {entry__97_1, NULL, 440, 444, 3, 2},
  {entry__98_1, NULL, 447, 451, 3, 2},
  {entry__99_1, NULL, 454, 458, 3, 2},
  {entry__100_1, NULL, 461, 465, 3, 2},
  {entry__101_1, NULL, 468, 472, 3, 2},
  {entry__102_1, NULL, 475, 479, 3, 2},
  {entry__103_1, NULL, 482, 489, 3, 2},
  {entry__104_1, NULL, 492, 499, 3, 2},
  {entry__105_1, NULL, 502, 509, 3, 2},
  {entry__106_1, NULL, 512, 516, 3, 2},
  {entry__107_1, NULL, 519, 523, 3, 2},
  {entry__108_1, NULL, 526, 530, 3, 2},
  {entry__115_1, NULL, 580, 583, 3, 2},
  {entry__116_1, NULL, 586, 592, 3, 2},
  {entry__117_1, NULL, 595, 601, 3, 2},
  {entry__118_1, NULL, 604, 607, 3, 2},
  {entry__119_1, NULL, 610, 632, 3, 2},
  {entry__120_1, NULL, 656, 656, 3, 35},
  {entry__121_1, NULL, 680, 680, 3, 35},
  {entry__122_1, NULL, 706, 706, 3, 33},
  {entry__123_1, NULL, 709, 709, 23, 49},
  {cont__123_2, &frame__123_1, 709, 709, 23, 63},
  {cont__123_3, &frame__123_1, 709, 709, 3, 63},
  {entry__124_1, NULL, 712, 735, 3, 2},
  {entry__125_1, NULL, 738, 755, 3, 2},
  {entry__126_11, NULL, 785, 785, 20, 29},
  {entry__126_6, NULL, 782, 782, 7, 26},
  {cont__126_7, &frame__126_6, 783, 783, 7, 48},
  {cont__126_8, &frame__126_6, 784, 784, 7, 32},
  {cont__126_9, &frame__126_6, 785, 785, 10, 17},
  {cont__126_10, &frame__126_6, 785, 785, 7, 29},
  {cont__126_12, &frame__126_6, 786, 786, 7, 28},
  {cont__126_13, &frame__126_6, 787, 787, 7, 23},
  {cont__126_14, &frame__126_6, 787, 787, 23, 23},
  {entry__126_4, NULL, 781, 781, 14, 23},
  {cont__126_5, &frame__126_4, 781, 787, 11, 23},
  {entry__126_3, NULL, 781, 787, 5, 23},
  {cont__126_15, &frame__126_3, 788, 788, 5, 14},
  {entry__126_1, NULL, 779, 779, 6, 22},
  {cont__126_2, &frame__126_1, 779, 788, 3, 14},
  {cont__126_16, &frame__126_1, 789, 789, 3, 22},
  {cont__126_17, &frame__126_1, 790, 790, 3, 50},
  {cont__126_18, &frame__126_1, 790, 790, 50, 50},
  {entry__127_1, NULL, 793, 811, 3, 2},
  {entry__128_13, NULL, 824, 824, 43, 74},
  {entry__128_10, NULL, 824, 824, 10, 35},
  {cont__128_11, &frame__128_10, 824, 824, 10, 40},
  {cont__128_12, &frame__128_10, 824, 824, 7, 74},
  {cont__128_15, &frame__128_10, 825, 825, 7, 18},
  {entry__128_6, NULL, 821, 821, 5, 23},
  {cont__128_7, &frame__128_6, 822, 822, 5, 46},
  {cont__128_8, &frame__128_6, 823, 823, 8, 24},
  {cont__128_9, &frame__128_6, 823, 825, 5, 18},
  {cont__128_16, &frame__128_6, 826, 826, 17, 31},
  {cont__128_17, &frame__128_6, 826, 826, 34, 34},
  {cont__128_18, &frame__128_6, 826, 826, 5, 34},
  {cont__128_19, &frame__128_6, 826, 826, 34, 34},
  {entry__128_3, NULL, 820, 820, 12, 26},
  {cont__128_4, &frame__128_3, 820, 820, 12, 30},
  {cont__128_5, &frame__128_3, 820, 826, 9, 34},
  {entry__128_23, NULL, 827, 827, 39, 49},
  {entry__128_1, NULL, 819, 819, 3, 22},
  {cont__128_2, &frame__128_1, 820, 826, 3, 34},
  {cont__128_20, &frame__128_1, 827, 827, 6, 31},
  {cont__128_21, &frame__128_1, 827, 827, 6, 36},
  {cont__128_22, &frame__128_1, 827, 827, 3, 49},
  {cont__128_24, &frame__128_1, 827, 827, 49, 49},
  {entry__129_12, NULL, 839, 839, 43, 74},
  {entry__129_9, NULL, 839, 839, 10, 35},
  {cont__129_10, &frame__129_9, 839, 839, 10, 40},
  {cont__129_11, &frame__129_9, 839, 839, 7, 74},
  {cont__129_13, &frame__129_9, 840, 840, 7, 18},
  {entry__129_6, NULL, 837, 837, 5, 46},
  {cont__129_7, &frame__129_6, 838, 838, 8, 24},
  {cont__129_8, &frame__129_6, 838, 840, 5, 18},
  {cont__129_14, &frame__129_6, 841, 841, 17, 31},
  {cont__129_15, &frame__129_6, 841, 841, 34, 34},
  {cont__129_16, &frame__129_6, 841, 841, 5, 34},
  {cont__129_17, &frame__129_6, 841, 841, 34, 34},
  {entry__129_3, NULL, 836, 836, 12, 26},
  {cont__129_4, &frame__129_3, 836, 836, 12, 30},
  {cont__129_5, &frame__129_3, 836, 841, 9, 34},
  {entry__129_21, NULL, 842, 842, 39, 49},
  {entry__129_1, NULL, 835, 835, 3, 22},
  {cont__129_2, &frame__129_1, 836, 841, 3, 34},
  {cont__129_18, &frame__129_1, 842, 842, 6, 31},
  {cont__129_19, &frame__129_1, 842, 842, 6, 36},
  {cont__129_20, &frame__129_1, 842, 842, 3, 49},
  {cont__129_22, &frame__129_1, 842, 842, 49, 49},
  {entry__130_6, NULL, 867, 867, 11, 34},
  {cont__130_7, &frame__130_6, 868, 868, 14, 34},
  {cont__130_8, &frame__130_6, 868, 868, 14, 39},
  {cont__130_9, &frame__130_6, 868, 868, 11, 45},
  {cont__130_10, &frame__130_6, 869, 869, 11, 32},
  {cont__130_11, &frame__130_6, 869, 869, 32, 32},
  {entry__130_5, NULL, 866, 869, 9, 32},
  {cont__130_12, &frame__130_5, 869, 869, 32, 32},
  {entry__130_4, NULL, 865, 869, 7, 33},
  {cont__130_13, &frame__130_4, 870, 870, 7, 14},
  {cont__130_14, &frame__130_4, 871, 871, 7, 12},
  {entry__130_15, NULL, 872, 872, 5, 16},
  {entry__130_1, NULL, 861, 861, 3, 36},
  {cont__130_2, &frame__130_1, 863, 863, 5, 17},
  {cont__130_3, &frame__130_1, 862, 872, 3, 16},
  {entry__131_7, NULL, 901, 901, 11, 26},
  {cont__131_8, &frame__131_7, 902, 902, 11, 18},
  {entry__131_11, NULL, 904, 904, 39, 47},
  {cont__131_12, &frame__131_11, 904, 904, 39, 47},
  {entry__131_9, NULL, 904, 904, 18, 34},
  {cont__131_10, &frame__131_9, 904, 904, 18, 47},
  {cont__131_13, &frame__131_9, 904, 904, 11, 47},
  {entry__131_4, NULL, 900, 900, 9, 34},
  {cont__131_5, &frame__131_4, 900, 900, 9, 39},
  {cont__131_6, &frame__131_4, 899, 904, 7, 48},
  {entry__131_17, NULL, 907, 908, 15, 49},
  {cont__131_20, &frame__131_17, 907, 908, 9, 49},
  {entry__131_14, NULL, 906, 906, 10, 35},
  {cont__131_15, &frame__131_14, 906, 906, 10, 40},
  {cont__131_16, &frame__131_14, 906, 908, 7, 50},
  {cont__131_21, &frame__131_14, 909, 909, 7, 18},
  {entry__131_1, NULL, 896, 896, 3, 26},
  {cont__131_2, &frame__131_1, 898, 898, 5, 17},
  {cont__131_3, &frame__131_1, 897, 909, 3, 19},
  {cont__131_22, &frame__131_1, 909, 909, 19, 19},
  {entry__132_1, NULL, 912, 927, 3, 2},
  {entry__133_1, NULL, 930, 942, 3, 2},
  {entry__134_8, NULL, 954, 955, 9, 23},
  {entry__134_4, NULL, 953, 953, 10, 38},
  {cont__134_5, &frame__134_4, 953, 953, 10, 43},
  {cont__134_6, &frame__134_4, 953, 953, 10, 43},
  {cont__134_7, &frame__134_4, 953, 955, 7, 24},
  {entry__134_10, NULL, 957, 957, 14, 42},
  {cont__134_11, &frame__134_10, 957, 957, 7, 42},
  {entry__134_1, NULL, 952, 952, 5, 30},
  {cont__134_2, &frame__134_1, 952, 952, 5, 35},
  {cont__134_3, &frame__134_1, 951, 957, 3, 43},
  {cont__134_12, &frame__134_1, 957, 957, 43, 43},
  {entry__135_1, NULL, 960, 981, 3, 2},
  {entry__136_1, NULL, 984, 995, 3, 2},
  {entry__137_8, NULL, 1005, 1006, 15, 51},
  {cont__137_11, &frame__137_8, 1005, 1006, 9, 51},
  {entry__137_4, NULL, 1004, 1004, 10, 31},
  {cont__137_5, &frame__137_4, 1004, 1004, 10, 36},
  {cont__137_6, &frame__137_4, 1004, 1004, 10, 36},
  {cont__137_7, &frame__137_4, 1004, 1006, 7, 52},
  {entry__137_12, NULL, 1008, 1008, 14, 35},
  {cont__137_13, &frame__137_12, 1008, 1008, 14, 40},
  {cont__137_14, &frame__137_12, 1008, 1008, 7, 40},
  {entry__137_1, NULL, 1003, 1003, 5, 30},
  {cont__137_2, &frame__137_1, 1003, 1003, 5, 35},
  {cont__137_3, &frame__137_1, 1002, 1008, 3, 41},
  {cont__137_15, &frame__137_1, 1008, 1008, 41, 41},
  {entry__138_1, NULL, 1011, 1171, 3, 2},
  {entry__139_1, NULL, 1174, 1177, 3, 2},
  {entry__140_1, NULL, 1185, 1197, 3, 2},
  {entry__141_1, NULL, 1201, 1212, 5, 19},
  {cont__141_2, &frame__141_1, 1216, 1216, 7, 38},
  {cont__141_3, &frame__141_1, 1217, 1217, 25, 37},
  {cont__141_4, &frame__141_1, 1217, 1217, 39, 62},
  {cont__141_5, &frame__141_1, 1217, 1217, 7, 63},
  {cont__141_6, &frame__141_1, 1218, 1218, 25, 48},
  {cont__141_7, &frame__141_1, 1218, 1218, 25, 50},
  {cont__141_8, &frame__141_1, 1218, 1218, 53, 53},
  {cont__141_9, &frame__141_1, 1218, 1218, 7, 54},
  {cont__141_10, &frame__141_1, 1213, 1219, 5, 13},
  {entry__142_1, NULL, 1222, 1240, 3, 2},
  {entry__143_1, NULL, 1243, 1254, 3, 2},
  {entry__144_5, NULL, 1258, 1259, 11, 60},
  {cont__144_8, &frame__144_5, 1258, 1259, 5, 60},
  {entry__144_1, NULL, 1257, 1257, 6, 21},
  {cont__144_2, &frame__144_1, 1257, 1257, 6, 26},
  {cont__144_3, &frame__144_1, 1257, 1257, 6, 26},
  {cont__144_4, &frame__144_1, 1257, 1259, 3, 61},
  {entry__145_1, NULL, 1262, 1274, 3, 2},
  {entry__146_2, NULL, 1287, 1287, 28, 36},
  {cont__146_3, &frame__146_2, 1287, 1287, 16, 37},
  {cont__146_5, &frame__146_2, 1287, 1287, 7, 37},
  {cont__146_7, &frame__146_2, 1288, 1288, 7, 42},
  {cont__146_9, &frame__146_2, 1289, 1289, 7, 19},
  {cont__146_11, &frame__146_2, 1285, 1289, 5, 19},
  {entry__146_22, NULL, 1295, 1295, 47, 53},
  {cont__146_23, &frame__146_22, 1295, 1295, 47, 63},
  {cont__146_24, &frame__146_22, 1295, 1295, 47, 63},
  {cont__146_25, &frame__146_22, 1295, 1295, 47, 63},
  {entry__146_18, NULL, 1294, 1294, 7, 40},
  {cont__146_19, &frame__146_18, 1295, 1295, 10, 38},
  {cont__146_20, &frame__146_18, 1295, 1295, 10, 42},
  {cont__146_21, &frame__146_18, 1295, 1295, 10, 63},
  {cont__146_26, &frame__146_18, 1295, 1295, 7, 68},
  {entry__146_13, NULL, 1292, 1292, 31, 31},
  {cont__146_14, &frame__146_13, 1292, 1292, 5, 31},
  {cont__146_15, &frame__146_13, 1293, 1293, 8, 25},
  {cont__146_16, &frame__146_13, 1293, 1293, 8, 25},
  {cont__146_17, &frame__146_13, 1293, 1295, 5, 68},
  {entry__146_31, NULL, 1298, 1298, 32, 57},
  {entry__146_36, NULL, 1300, 1300, 40, 46},
  {cont__146_37, &frame__146_36, 1300, 1300, 40, 56},
  {cont__146_38, &frame__146_36, 1300, 1300, 40, 56},
  {entry__146_35, NULL, 1300, 1300, 12, 56},
  {cont__146_39, &frame__146_35, 1300, 1300, 5, 61},
  {entry__146_1, NULL, 1279, 1279, 5, 16},
  {cont__146_27, &frame__146_1, 1281, 1281, 5, 19},
  {cont__146_28, &frame__146_1, 1277, 1282, 3, 29},
  {cont__146_29, &frame__146_1, 1297, 1297, 3, 26},
  {cont__146_30, &frame__146_1, 1298, 1298, 3, 57},
  {cont__146_32, &frame__146_1, 1299, 1299, 6, 26},
  {cont__146_33, &frame__146_1, 1299, 1299, 6, 30},
  {cont__146_34, &frame__146_1, 1299, 1300, 3, 61},
  {entry__147_5, NULL, 1308, 1309, 11, 49},
  {cont__147_7, &frame__147_5, 1308, 1309, 5, 49},
  {entry__147_1, NULL, 1307, 1307, 6, 26},
  {cont__147_2, &frame__147_1, 1307, 1307, 6, 31},
  {cont__147_3, &frame__147_1, 1307, 1307, 6, 31},
  {cont__147_4, &frame__147_1, 1307, 1309, 3, 50},
  {entry__148_3, NULL, 1313, 1313, 22, 35},
  {cont__148_4, &frame__148_3, 1313, 1313, 5, 49},
  {cont__148_6, &frame__148_3, 1313, 1313, 49, 49},
  {entry__148_9, NULL, 1314, 1314, 37, 54},
  {cont__148_10, &frame__148_9, 1314, 1314, 54, 54},
  {entry__148_20, NULL, 1320, 1320, 39, 58},
  {cont__148_21, &frame__148_20, 1320, 1320, 34, 59},
  {cont__148_22, &frame__148_20, 1320, 1320, 29, 71},
  {cont__148_24, &frame__148_20, 1320, 1320, 29, 77},
  {cont__148_25, &frame__148_20, 1320, 1320, 7, 77},
  {cont__148_26, &frame__148_20, 1321, 1321, 10, 34},
  {cont__148_27, &frame__148_20, 1321, 1321, 7, 40},
  {entry__148_19, NULL, 1318, 1321, 5, 40},
  {cont__148_28, &frame__148_19, 1321, 1321, 40, 40},
  {entry__148_31, NULL, 1322, 1322, 46, 46},
  {cont__148_32, &frame__148_31, 1322, 1322, 27, 46},
  {cont__148_33, &frame__148_31, 1322, 1322, 46, 46},
  {entry__148_1, NULL, 1312, 1312, 10, 34},
  {cont__148_2, &frame__148_1, 1312, 1313, 3, 49},
  {cont__148_7, &frame__148_1, 1314, 1314, 10, 34},
  {cont__148_8, &frame__148_1, 1314, 1314, 3, 54},
  {cont__148_11, &frame__148_1, 1315, 1315, 25, 34},
  {cont__148_13, &frame__148_1, 1315, 1315, 25, 40},
  {cont__148_14, &frame__148_1, 1315, 1315, 3, 40},
  {cont__148_15, &frame__148_1, 1316, 1316, 25, 35},
  {cont__148_17, &frame__148_1, 1316, 1316, 3, 35},
  {cont__148_18, &frame__148_1, 1317, 1321, 3, 41},
  {cont__148_29, &frame__148_1, 1322, 1322, 10, 24},
  {cont__148_30, &frame__148_1, 1322, 1322, 3, 46},
  {cont__148_34, &frame__148_1, 1323, 1323, 3, 13},
  {entry__157_1, NULL, 1404, 1416, 3, 2},
  {entry__158_1, NULL, 1419, 1430, 3, 2},
  {entry__159_1, NULL, 1433, 1452, 3, 2},
  {entry__160_1, NULL, 1455, 1459, 3, 2},
  {entry__161_1, NULL, 1462, 1466, 3, 2},
  {entry__162_1, NULL, 1469, 1473, 3, 2},
  {entry__163_1, NULL, 1476, 1476, 13, 29},
  {cont__163_2, &frame__163_1, 1476, 1476, 35, 51},
  {cont__163_3, &frame__163_1, 1476, 1476, 6, 52},
  {cont__163_4, &frame__163_1, 1476, 1476, 3, 52},
  {entry__164_1, NULL, 1478, 1478, 42, 59},
  {cont__164_2, &frame__164_1, 1478, 1478, 42, 77},
  {cont__164_3, &frame__164_1, 1478, 1478, 39, 77},
  {entry__165_1, NULL, 1481, 1481, 6, 23},
  {cont__165_2, &frame__165_1, 1481, 1481, 6, 44},
  {cont__165_3, &frame__165_1, 1481, 1481, 3, 44},
  {entry__166_1, NULL, 1483, 1483, 37, 54},
  {cont__166_2, &frame__166_1, 1483, 1483, 37, 67},
  {cont__166_3, &frame__166_1, 1483, 1483, 34, 67},
  {entry__167_16, NULL, 1498, 1498, 11, 29},
  {cont__167_17, &frame__167_16, 1498, 1498, 29, 29},
  {entry__167_18, NULL, 1496, 1496, 11, 14},
  {entry__167_8, NULL, 1491, 1491, 7, 21},
  {cont__167_9, &frame__167_8, 1492, 1492, 14, 29},
  {cont__167_10, &frame__167_8, 1492, 1492, 7, 35},
  {cont__167_11, &frame__167_8, 1494, 1494, 9, 26},
  {cont__167_12, &frame__167_8, 1495, 1495, 9, 17},
  {cont__167_15, &frame__167_8, 1493, 1498, 7, 30},
  {entry__167_7, NULL, 1490, 1498, 5, 31},
  {cont__167_19, &frame__167_7, 1498, 1498, 31, 31},
  {entry__167_23, NULL, 1501, 1501, 36, 52},
  {cont__167_24, &frame__167_23, 1501, 1501, 56, 73},
  {cont__167_25, &frame__167_23, 1501, 1501, 36, 73},
  {cont__167_26, &frame__167_23, 1501, 1501, 33, 73},
  {entry__167_22, NULL, 1501, 1501, 5, 73},
  {cont__167_27, &frame__167_22, 1501, 1501, 73, 73},
  {entry__167_1, NULL, 1486, 1486, 27, 38},
  {cont__167_2, &frame__167_1, 1486, 1486, 3, 47},
  {cont__167_3, &frame__167_1, 1487, 1487, 3, 18},
  {cont__167_4, &frame__167_1, 1488, 1488, 21, 38},
  {cont__167_5, &frame__167_1, 1488, 1488, 3, 39},
  {cont__167_6, &frame__167_1, 1489, 1498, 3, 32},
  {cont__167_20, &frame__167_1, 1499, 1499, 3, 11},
  {cont__167_21, &frame__167_1, 1500, 1501, 3, 73},
  {cont__167_28, &frame__167_1, 1502, 1502, 3, 12},
  {entry__175_1, NULL, 1594, 1632, 3, 2},
  {entry__176_1, NULL, 1635, 1662, 3, 2},
  {entry__177_1, NULL, 1665, 1678, 3, 2},
  {entry__178_1, NULL, 1680, 1680, 44, 67},
  {cont__178_2, &frame__178_1, 1680, 1680, 36, 72},
  {entry__179_1, NULL, 1683, 1705, 3, 2},
  {entry__180_1, NULL, 1707, 1707, 42, 65},
  {cont__180_2, &frame__180_1, 1707, 1707, 35, 70},
  {entry__181_1, NULL, 1710, 1719, 3, 2},
  {entry__182_1, NULL, 1721, 1721, 45, 57},
  {cont__182_2, &frame__182_1, 1721, 1721, 45, 65},
  {cont__182_3, &frame__182_1, 1721, 1721, 22, 65},
  {entry__183_1, NULL, 1723, 1723, 24, 41},
  {entry__184_1, NULL, 1725, 1725, 53, 65},
  {cont__184_2, &frame__184_1, 1725, 1725, 53, 73},
  {cont__184_3, &frame__184_1, 1725, 1725, 23, 73},
  {entry__185_1, NULL, 1727, 1727, 25, 43},
  {entry__186_1, NULL, 1729, 1729, 17, 40},
  {entry__187_5, NULL, 1735, 1735, 25, 33},
  {cont__187_6, &frame__187_5, 1735, 1735, 25, 33},
  {entry__187_8, NULL, 1735, 1735, 36, 45},
  {entry__187_2, NULL, 1734, 1734, 5, 15},
  {cont__187_3, &frame__187_2, 1735, 1735, 8, 20},
  {cont__187_4, &frame__187_2, 1735, 1735, 8, 33},
  {cont__187_7, &frame__187_2, 1735, 1735, 5, 45},
  {cont__187_9, &frame__187_2, 1736, 1736, 5, 19},
  {cont__187_10, &frame__187_2, 1736, 1736, 19, 19},
  {entry__187_1, NULL, 1733, 1736, 3, 19},
  {cont__187_11, &frame__187_1, 1736, 1736, 19, 19},
  {entry__188_9, NULL, 1741, 1741, 45, 50},
  {entry__188_10, NULL, 1742, 1743, 15, 43},
  {cont__188_13, &frame__188_10, 1742, 1743, 9, 43},
  {entry__188_4, NULL, 1741, 1741, 10, 42},
  {cont__188_8, &frame__188_4, 1741, 1743, 7, 44},
  {entry__188_14, NULL, 1745, 1745, 7, 24},
  {entry__188_1, NULL, 1740, 1740, 5, 35},
  {cont__188_3, &frame__188_1, 1739, 1745, 3, 25},
  {entry__189_9, NULL, 1751, 1751, 26, 34},
  {cont__189_10, &frame__189_9, 1751, 1751, 20, 39},
  {entry__189_4, NULL, 1750, 1750, 32, 32},
  {cont__189_5, &frame__189_4, 1750, 1750, 5, 33},
  {cont__189_6, &frame__189_4, 1751, 1751, 8, 17},
  {cont__189_7, &frame__189_4, 1751, 1751, 8, 17},
  {cont__189_8, &frame__189_4, 1751, 1751, 5, 39},
  {entry__189_1, NULL, 1748, 1748, 27, 41},
  {cont__189_2, &frame__189_1, 1748, 1748, 3, 62},
  {cont__189_3, &frame__189_1, 1749, 1751, 3, 39},
  {cont__189_11, &frame__189_1, 1752, 1752, 22, 35},
  {cont__189_12, &frame__189_1, 1752, 1752, 3, 35}
};

union NODE {
  struct {
    FUNC type;
    ATTRIBUTES *attributes;
  };
  CONTINUATION continuation;
  CLOSURE closure;
  DIRECTORY_HANDLE directory_handle;
  SIMPLE_NODE simple_node;
  FILE_DESCRIPTOR file_descriptor;
  ADDRINFO addrinfo;
  STAT stat;
  DIRENT dirent;
};
static void type__std__ioctl(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__ioctl);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__ioctl, attr);
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
static void type__std__get_terminal_size(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__get_terminal_size);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__get_terminal_size, attr);
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
static void type__std__device_of(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__device_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__device_of, attr);
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
static void type__std__inode_of(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__inode_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__inode_of, attr);
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
static void type__std__mode_of(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__mode_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__mode_of, attr);
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
static void type__std__link_count_of(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__link_count_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__link_count_of, attr);
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
static void type__std__user_id_of(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__user_id_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__user_id_of, attr);
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
static void type__std__group_id_of(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__group_id_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__group_id_of, attr);
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
static void type__std__size_of(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__size_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__size_of, attr);
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
static void type__std__block_size_of(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__block_size_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__block_size_of, attr);
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
static void type__std__sector_count_of(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__sector_count_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__sector_count_of, attr);
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
static void type__std__access_time_of(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__access_time_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__access_time_of, attr);
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
static void type__std__modification_time_of(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__modification_time_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__modification_time_of, attr);
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
static void type__std__status_change_time_of(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__status_change_time_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__status_change_time_of, attr);
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
static void type__std__creation_time_of(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__creation_time_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__creation_time_of, attr);
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
static void type__std__filename_of(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__filename_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__filename_of, attr);
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
static void type__std__file_type_of(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__file_type_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__file_type_of, attr);
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
static void type__std__pathname_of(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__pathname_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__pathname_of, attr);
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
static void type__std__fullname_of(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__fullname_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__fullname_of, attr);
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
static void type__std__is_a_directory(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__is_a_directory);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__is_a_directory, attr);
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
static void type__std__is_a_regular_file(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__is_a_regular_file);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__is_a_regular_file, attr);
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
static void type__std__is_a_link(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__is_a_link);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__is_a_link, attr);
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
static void type__std__listen(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__listen);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__listen, attr);
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
static void type__std__accept(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__accept);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__accept, attr);
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
static void type__std__connect(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__std__connect);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__std__connect, attr);
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
static NODE *number__6;
static NODE *number__0o4000;
static NODE *number__0o400;
static NODE *number__0o755;
static NODE *character__47;
static NODE *number__17;
static NODE *number__27;
static NODE *number__0o02;
static NODE *number__0o00;
static NODE *number__15;
static NODE *number__25;
static NODE *number__12;
static NODE *number__0;
static NODE *number__3;
static NODE *number__4;
static NODE *number__32;
static NODE *number__26;
static NODE *number__16;
static NODE *number__8;
static NODE *number__22;
static NODE *number__0o01;
static NODE *number__0o200;
static NODE *number__7;
static NODE *number__5;
static NODE *number__33;
static NODE *number__9;
static NODE *number__0o20000;
static NODE *number__11;
static NODE *number__21;
static NODE *number__13;
static NODE *number__31;
static NODE *number__23;
static NODE *number__0o1000;
static NODE *number__34;
static NODE *number__28;
static NODE *number__1;
static NODE *number__19;
static NODE *number__18;
static NODE *number__29;
static NODE *number__0o100;
static NODE *number__0x1000000;
static NODE *number__2;
static NODE *number__0o2000;
static NODE *number__20;
static NODE *number__10;
static NODE *number__30;
static NODE *number__24;
static NODE *number__14;

static const char *used_namespaces[] = {
  "std",
  NULL
};

static MODULE_INFO module_info = {
  NULL,
  "basic__io",
  continuation_info,
  sizeof(continuation_info)/sizeof(CONTINUATION_INFO),
  (NODE **)&var,
  var_names,
  sizeof(var_names)/sizeof(const char *),
  used_namespaces,
  {DEBUG_FILENAME("basic/io.sim")}
};

/******
C O D E
******/

static int already_run = false;

EXPORT void run__basic__io(void) {
  if (already_run) {
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  already_run = true;
  allocate_initialized_frame_gc(0, 0);
  // 41: extern $wget "wget"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__192_1;
  result_count = 1;
  myself = get__extern();
  func = myself->type;
  frame->cont = cont__192_2;
}
static void cont__192_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._wget, arguments->slots[0]);
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__81_1(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(2, 6);
  // slot allocations:
  // cmd: 0
  // args: 1
  // info: 2
  frame->slots[2] /* info */ = create_cell();
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  frame->slots[0] /* cmd */ = arguments->slots[0];
  frame->slots[1] /* args */ = from_arguments(1, argument_count-1);
  // 283: $$info ""
  ((CELL *)frame->slots[2])->contents /* info */ = empty_string;
  // 284: ... : (arg) write_to &info "@(key_of(arg)) = @(value_of(arg))@nl;"
  frame->slots[3] /* temp__1 */ = create_closure(entry__81_2, 1);
  // 284: for_each args: (arg) write_to &info "@(key_of(arg)) = @(value_of(arg))@nl;"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* args */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__81_9;
}
static void entry__81_2(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // arg: 0
  // info: 1
  frame->slots[1] = myself->closure.frame->slots[2]; /* info */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 284: ... key_of(arg)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* arg */;
  result_count = 1;
  myself = get__key_of();
  func = myself->type;
  frame->cont = cont__81_3;
}
static void cont__81_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 284: ... value_of(arg)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* arg */;
  result_count = 1;
  myself = get__value_of();
  func = myself->type;
  frame->cont = cont__81_4;
}
static void cont__81_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 284: ... "@(key_of(arg)) = @(value_of(arg))@nl;"
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = string__81_5;
  arguments->slots[2] = frame->slots[4] /* temp__3 */;
  arguments->slots[3] = string__81_6;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__81_7;
}
static void cont__81_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 284: ... write_to &info "@(key_of(arg)) = @(value_of(arg))@nl;"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* info */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__write_to();
  func = myself->type;
  frame->cont = cont__81_8;
}
static void cont__81_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* info */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__81_9(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 285: ... std::errno()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = var.std__errno;
  func = myself->type;
  frame->cont = cont__81_10;
}
static void cont__81_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 285: ... std::strerror(std::errno())
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = var.std__strerror;
  func = myself->type;
  frame->cont = cont__81_11;
}
static void cont__81_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 285: ... "@(cmd) failed: @(std::strerror(std::errno()))!@nl;@(info)"
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* cmd */;
  arguments->slots[1] = string__81_12;
  arguments->slots[2] = frame->slots[4] /* temp__2 */;
  arguments->slots[3] = string__81_13;
  arguments->slots[4] = ((CELL *)frame->slots[2])->contents /* info */;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__81_14;
}
static void cont__81_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 285: raise "@(cmd) failed: @(std::strerror(std::errno()))!@nl;@(info)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__raise();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__82_1(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // err: 0
  // args: 1
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  frame->slots[0] /* err */ = arguments->slots[0];
  frame->slots[1] /* args */ = from_arguments(1, argument_count-1);
  // 287: ... err < 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* err */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__82_2;
}
static void cont__82_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 287: ... if err < 0 raise_error args*
  argument_count = 0;
  arguments = node_p;
  arguments->slots[argument_count++] = frame->slots[2] /* temp__1 */;
  arguments->slots[argument_count++] = get__raise_error();
  unfold(frame->slots[1] /* args */);
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__83_1(void) {
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  {
    NODE *result__node = (NODE *)(from_int(errno));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  };
}
static void entry__84_1(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  {
    NODE *result__node = (NODE *)(from_c_string(strerror(to_int(arguments->slots[0]))));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}

static STAT_BUFFER *collect_stat_buffer(STAT_BUFFER *buf) {
  if (!IS_COLLECTED(buf)) return buf;
  void *new_location = buf->new_location;
  if (new_location) return new_location;
  STAT_BUFFER *new_buf = copy(buf, sizeof(STAT_BUFFER));
  new_buf->new_location = NULL;
  buf->new_location = new_buf;
  return new_buf;
}
static void *collect_stat(STAT *node) {
  STAT *new_node = allocate(sizeof(STAT));
  new_node->type = node->type;
  *(void **)node = ENCODE_ADDRESS(new_node);
  new_node->attributes = collect_attributes(node->attributes);
  new_node->buf = collect_stat_buffer(node->buf);
  return new_node;
}

static VTABLE vtable__types__stat = {
  sizeof(STAT),
  (COLLECTOR *)&collect_stat,
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
  &func__types__stat___debug_string
};

static ATTRIBUTES attributes__types__stat = {
  &vtable__types__stat,
  {
    &undefined_attributes_level_1, &undefined_attributes_level_2,
    &undefined_attributes_level_3, &undefined_attributes_level_4,
    &undefined_attributes_level_5, &undefined_attributes_level_6,
    &undefined_attributes_level_7
  }
};

static void type__types__stat(void) {
  {
    runtime_error("Attempt to call a file status object as a function!");
  }
}
static NODE *create__types__stat(STAT_BUFFER *buf) {
  NODE *node = allocate(sizeof(STAT));
  node->type = type__types__stat;
  node->attributes = &attributes__types__stat;
  node->stat.buf = buf;
  return node;
}

static long func__types__stat___debug_string(NODE *node, int indent, int max_depth, char *buf) {
  return debug_print(indent, buf, "<stat buffer - inode %ld>",
    from_long(node->stat.buf->stat.st_ino));
}
static void entry__92_1(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  char *filename = to_c_string(arguments->slots[0]);
  STAT_BUFFER *buf = allocate(sizeof(STAT_BUFFER));
  int err = stat(filename, &buf->stat);
  deallocate_memory(filename);
  if (err != 0) {
    arguments = node_p;
    arguments->slots[0] = undefined;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  buf->new_location = NULL;
  {
    NODE *result__node = (NODE *)(create__types__stat(buf));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__93_1(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  char *filename = to_c_string(arguments->slots[0]);
  struct stat buf;
  int err = stat(filename, &buf);
  deallocate_memory(filename);
  {
    NODE *result__node = (NODE *)(from_bool(err == 0));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__94_1(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  {
    NODE *result__node = (NODE *)(from_int(arguments->slots[0]->stat.buf->stat.st_dev));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__95_1(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  {
    NODE *result__node = (NODE *)(from_long(arguments->slots[0]->stat.buf->stat.st_ino));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__96_1(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }

  {
    NODE *result__node = (NODE *)(from_int(arguments->slots[0]->stat.buf->stat.st_mode));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__97_1(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }

  {
    NODE *result__node = (NODE *)(from_long(arguments->slots[0]->stat.buf->stat.st_nlink));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__98_1(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }

  {
    NODE *result__node = (NODE *)(from_int(arguments->slots[0]->stat.buf->stat.st_uid));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__99_1(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }

  {
    NODE *result__node = (NODE *)(from_int(arguments->slots[0]->stat.buf->stat.st_gid));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__100_1(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }

  {
    NODE *result__node = (NODE *)(from_long(arguments->slots[0]->stat.buf->stat.st_size));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__101_1(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }

  {
    NODE *result__node = (NODE *)(from_int(arguments->slots[0]->stat.buf->stat.st_blksize));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__102_1(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }

  {
    NODE *result__node = (NODE *)(from_long(arguments->slots[0]->stat.buf->stat.st_blocks));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__103_1(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }

  {
    NODE *result__node = (NODE *)(create__types__date_and_time(
      arguments->slots[0]->stat.buf->stat.st_atim.tv_sec,
      arguments->slots[0]->stat.buf->stat.st_atim.tv_nsec));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__104_1(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }

  {
    NODE *result__node = (NODE *)(create__types__date_and_time(
      arguments->slots[0]->stat.buf->stat.st_mtim.tv_sec,
      arguments->slots[0]->stat.buf->stat.st_mtim.tv_nsec));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__105_1(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }

  {
    NODE *result__node = (NODE *)(create__types__date_and_time(
      arguments->slots[0]->stat.buf->stat.st_ctim.tv_sec,
      arguments->slots[0]->stat.buf->stat.st_ctim.tv_nsec));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__106_1(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }

  {
    NODE *result__node = (NODE *)(from_bool(S_ISDIR(arguments->slots[0]->stat.buf->stat.st_mode)));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__107_1(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }

  {
    NODE *result__node = (NODE *)(from_bool(S_ISREG(arguments->slots[0]->stat.buf->stat.st_mode)));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__108_1(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }

  {
    NODE *result__node = (NODE *)(from_bool(S_ISLNK(arguments->slots[0]->stat.buf->stat.st_mode)));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void *collect_file_descriptor(FILE_DESCRIPTOR *node) {
  FILE_DESCRIPTOR *new_node = allocate(sizeof(FILE_DESCRIPTOR));
  new_node->type = node->type;
  *(void **)node = ENCODE_ADDRESS(new_node);
  new_node->attributes = collect_attributes(node->attributes);
  new_node->fd = node->fd;
  return new_node;
}

static VTABLE vtable__types__file_descriptor = {
  sizeof(FILE_DESCRIPTOR),
  (COLLECTOR *)&collect_file_descriptor,
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
  &func__types__file_descriptor___debug_string
};

static ATTRIBUTES attributes__types__file_descriptor = {
  &vtable__types__file_descriptor,
  {
    &undefined_attributes_level_1, &undefined_attributes_level_2,
    &undefined_attributes_level_3, &undefined_attributes_level_4,
    &undefined_attributes_level_5, &undefined_attributes_level_6,
    &undefined_attributes_level_7
  }
};

extern void type__types__file_descriptor(void) {
  {
    runtime_error("Attempt to call a file_descriptor as a function!");
  }
}
extern NODE *create__types__file_descriptor(int fd) {
  NODE *node = allocate(sizeof(FILE_DESCRIPTOR));
  node->type = type__types__file_descriptor;
  node->attributes = &attributes__types__file_descriptor;
  node->file_descriptor.fd = fd;
  return node;
}

static long func__types__file_descriptor___debug_string(NODE *node, int indent, int max_depth, char *buf) {
  return debug_print(indent, buf, "<file_descriptor %d>", node->file_descriptor.fd);
}
static void entry__115_1(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  {
    NODE *result__node = (NODE *)(create__types__file_descriptor(to_int(arguments->slots[0])));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__116_1(void) {
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  NODE *right = arguments->slots[1];
  if ((right)->type != type__types__file_descriptor) {
    arguments = node_p;
    arguments->slots[0] = boolean_false;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  {
    NODE *result__node = (NODE *)(from_bool(arguments->slots[0]->file_descriptor.fd == right->file_descriptor.fd));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__117_1(void) {
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  NODE *right = arguments->slots[1];
  if ((right)->type != type__types__file_descriptor) {
    arguments = node_p;
    arguments->slots[0] = boolean_true;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  {
    NODE *result__node = (NODE *)(from_bool(arguments->slots[0]->file_descriptor.fd < right->file_descriptor.fd));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__118_1(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  {
    NODE *result__node = (NODE *)(from_int(arguments->slots[0]->file_descriptor.fd+0xfdec));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__119_1(void) {
  if (argument_count < 2) {
    too_few_arguments_error();
    return;
  }
  if (argument_count > 3) {
    too_many_arguments_error();
    return;
  }
  int fd;
  int flags = to_int(arguments->slots[1]);
  mode_t mode = 0644;
  if (argument_count == 3) mode = to_uint32(arguments->slots[2]);
  if (event__mode != EM__REPLAY) {
    char *filename = to_c_string(arguments->slots[0]);
    do {
      fd = open(filename, flags, mode);
    } while (fd == -1 && errno == EINTR);
    deallocate_memory(filename);

    
    
    
    if (event__mode == EM__RECORD) {
      record__event("posix_open");
      store__integer(fd);
    }
  } else {
    replay__event("posix_open");
    retrieve__integer(&fd);
    report__event("posix_open");
    print__integer(fd);
    print__integer(flags);
    print__integer(mode);
  }
  if (fd == -1) {
    arguments = node_p;
    arguments->slots[0] = undefined;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  {
    NODE *result__node = (NODE *)(create__types__file_descriptor(fd));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__120_1(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // filename: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 656: posix_open filename std::O_RDONLY
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* filename */;
  arguments->slots[1] = var.std__O_RDONLY;
  result_count = frame->caller_result_count;
  myself = var._posix_open;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__121_1(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // filename: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 680: posix_open filename std::O_WRONLY
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* filename */;
  arguments->slots[1] = var.std__O_WRONLY;
  result_count = frame->caller_result_count;
  myself = var._posix_open;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__122_1(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // filename: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 706: posix_open filename std::O_RDWR
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* filename */;
  arguments->slots[1] = var.std__O_RDWR;
  result_count = frame->caller_result_count;
  myself = var._posix_open;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__123_1(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // filename: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 709: ... std::O_CREAT | std::O_TRUNC
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var.std__O_CREAT;
  arguments->slots[1] = var.std__O_TRUNC;
  result_count = 1;
  myself = get__std__bit_or();
  func = myself->type;
  frame->cont = cont__123_2;
}
static void cont__123_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 709: ... std::O_CREAT | std::O_TRUNC | std::O_RDWR
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = var.std__O_RDWR;
  result_count = 1;
  myself = get__std__bit_or();
  func = myself->type;
  frame->cont = cont__123_3;
}
static void cont__123_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 709: posix_open filename std::O_CREAT | std::O_TRUNC | std::O_RDWR
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* filename */;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = var._posix_open;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__124_1(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  int err;
  int fd = arguments->slots[0]->file_descriptor.fd;
  if (event__mode != EM__REPLAY) {
    do {
      struct stat statbuf;
      fstat(fd, &statbuf);
      if (S_ISSOCK(statbuf.st_mode)) {
        shutdown(fd, SHUT_RDWR);
      }
      err = close(fd);
    } while (err == -1 && errno == EINTR);

    
    if (event__mode == EM__RECORD) {
      if (err == 0) {
        successful__action("posix_close");
      } else {
        failed__action("posix_close");
        store__integer(err);
      }
      }
    } else {
      if (replay__action("posix_close")) {
        retrieve__integer(&err);
    } else {
        err = 0;
    }
      report__event("posix_close");
        print__integer(fd);
  }
  if (result_count == 0) {
    if (err != 0) {
    runtime_error("Failed to close file!");
  }
    {
    argument_count = 0;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  }
  {
    NODE *result__node = (NODE *)(from_bool(err == 0));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__125_1(void) {
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  int fd = arguments->slots[0]->file_descriptor.fd;
  long size = to_long(arguments->slots[1]);
  uint8_t *buf = allocate_memory(size);
  long bytes_read;
  if (event__mode != EM__REPLAY) {
    do {
      bytes_read = read(fd, buf, size);
    } while (bytes_read == -1 && errno == EINTR);
    if (event__mode == EM__RECORD) {
      record__event("read_some_bytes_from");
      store__memory(buf, bytes_read);
    }
  } else {
    replay__event("read_some_bytes_from");
    bytes_read = retrieve__memory((uint8_t **)&buf);
  }
  NODE *result = undefined;
  if (bytes_read >= 0) result = from_latin_1_string((const char *)buf, bytes_read);
  deallocate_memory(buf);
  {
    NODE *result__node = (NODE *)(result);
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__126_1(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // fd: 0
  // amount: 1
  // return: 2
  frame->slots[2] /* return */ = create_continuation();
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  if (argument_count > 2) {
    too_many_arguments_error();
    return;
  }
  switch(argument_count) {
    default: frame->slots[1] /* amount */ = create_cell_with_contents(arguments->slots[1]);
    case 1:;
  }
  switch(argument_count) {
    case 1: frame->slots[1] /* amount */ = create_cell_with_contents(undefined);
  }
  // 779: ... amount.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* amount */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__126_2;
}
static void cont__126_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 779: ... :
  // 780:   $$buf ""
  // 781:   while -> amount > 0:
  // 782:     wait_to_read_from fd
  // 783:     read_some_bytes_from $some_bytes fd amount
  // 784:     $len length_of(some_bytes)
  // 785:     if len == 0: return buf
  // 786:     append &buf some_bytes
  // 787:     minus &amount len
  // 788:   return buf
  frame->slots[4] /* temp__2 */ = create_closure(entry__126_3, 0);
  // 779: if amount.is_defined:
  // 780:   $$buf ""
  // 781:   while -> amount > 0:
  // 782:     wait_to_read_from fd
  // 783:     read_some_bytes_from $some_bytes fd amount
  // 784:     $len length_of(some_bytes)
  // 785:     if len == 0: return buf
  // 786:     append &buf some_bytes
  // 787:     minus &amount len
  // 788:   return buf
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__126_16;
}
static void entry__126_3(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // amount: 0
  // fd: 1
  // return: 2
  // buf: 3
  frame->slots[0] = myself->closure.frame->slots[1]; /* amount */
  frame->slots[1] = myself->closure.frame->slots[0]; /* fd */
  frame->slots[2] = myself->closure.frame->slots[2]; /* return */
  frame->slots[3] /* buf */ = create_cell();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 780: $$buf ""
  ((CELL *)frame->slots[3])->contents /* buf */ = empty_string;
  // 781: ... -> amount > 0:
  // 782:   wait_to_read_from fd
  // 783:   read_some_bytes_from $some_bytes fd amount
  // 784:   $len length_of(some_bytes)
  // 785:   if len == 0: return buf
  // 786:   append &buf some_bytes
  // 787:   minus &amount len
  frame->slots[4] /* temp__1 */ = create_closure(entry__126_4, 0);
  // 781: while -> amount > 0:
  // 782:   wait_to_read_from fd
  // 783:   read_some_bytes_from $some_bytes fd amount
  // 784:   $len length_of(some_bytes)
  // 785:   if len == 0: return buf
  // 786:   append &buf some_bytes
  // 787:   minus &amount len
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__while();
  func = myself->type;
  frame->cont = cont__126_15;
}
static void entry__126_6(void) {
  allocate_initialized_frame_gc(4, 8);
  // slot allocations:
  // fd: 0
  // amount: 1
  // return: 2
  // buf: 3
  // some_bytes: 4
  // len: 5
  frame->slots[0] = myself->closure.frame->slots[1]; /* fd */
  frame->slots[1] = myself->closure.frame->slots[0]; /* amount */
  frame->slots[2] = myself->closure.frame->slots[2]; /* return */
  frame->slots[3] = myself->closure.frame->slots[3]; /* buf */
  frame->slots[4] /* some_bytes */ = create_future();
  frame->slots[5] /* len */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 782: wait_to_read_from fd
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd */;
  result_count = 0;
  myself = get__wait_to_read_from();
  func = myself->type;
  frame->cont = cont__126_7;
}
static void cont__126_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 783: read_some_bytes_from $some_bytes fd amount
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* amount */;
  result_count = 1;
  myself = get__read_some_bytes_from();
  func = myself->type;
  frame->cont = cont__126_8;
}
static void cont__126_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* some_bytes */, arguments->slots[0]);
  // 784: $len length_of(some_bytes)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* some_bytes */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__126_9;
}
static void cont__126_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* len */, arguments->slots[0]);
  // 785: ... len == 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* len */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__126_10;
}
static void cont__126_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 785: ... : return buf
  frame->slots[7] /* temp__2 */ = create_closure(entry__126_11, 0);
  // 785: if len == 0: return buf
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__126_12;
}
static void entry__126_11(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // return: 0
  // buf: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  frame->slots[1] = myself->closure.frame->slots[3]; /* buf */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 785: ... return buf
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* buf */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__126_12(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 786: append &buf some_bytes
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* buf */;
  arguments->slots[1] = frame->slots[4] /* some_bytes */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__126_13;
}
static void cont__126_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* buf */ = arguments->slots[0];
  // 787: minus &amount len
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* amount */;
  arguments->slots[1] = frame->slots[5] /* len */;
  result_count = 1;
  myself = get__minus();
  func = myself->type;
  frame->cont = cont__126_14;
}
static void cont__126_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* amount */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__126_4(void) {
  allocate_initialized_frame_gc(4, 6);
  // slot allocations:
  // amount: 0
  // fd: 1
  // return: 2
  // buf: 3
  frame->slots[0] = myself->closure.frame->slots[0]; /* amount */
  frame->slots[1] = myself->closure.frame->slots[1]; /* fd */
  frame->slots[2] = myself->closure.frame->slots[2]; /* return */
  frame->slots[3] = myself->closure.frame->slots[3]; /* buf */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 781: ... amount > 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* amount */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__126_5;
}
static void cont__126_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 781: ... :
  // 782:   wait_to_read_from fd
  // 783:   read_some_bytes_from $some_bytes fd amount
  // 784:   $len length_of(some_bytes)
  // 785:   if len == 0: return buf
  // 786:   append &buf some_bytes
  // 787:   minus &amount len
  frame->slots[5] /* temp__2 */ = create_closure(entry__126_6, 0);
  // 781: ... -> amount > 0:
  // 782:   wait_to_read_from fd
  // 783:   read_some_bytes_from $some_bytes fd amount
  // 784:   $len length_of(some_bytes)
  // 785:   if len == 0: return buf
  // 786:   append &buf some_bytes
  // 787:   minus &amount len
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__126_15(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 788: return buf
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* buf */;
  result_count = frame->caller_result_count;
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__126_16(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 789: wait_to_read_from fd
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd */;
  result_count = 0;
  myself = get__wait_to_read_from();
  func = myself->type;
  frame->cont = cont__126_17;
}
static void cont__126_17(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 790: read_some_bytes_from fd 0x1000000 # 16 MiB limit
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd */;
  arguments->slots[1] = number__0x1000000;
  result_count = frame->caller_result_count;
  myself = get__read_some_bytes_from();
  func = myself->type;
  frame->cont = cont__126_18;
}
static void cont__126_18(void) {
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__127_1(void) {
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  int fd = arguments->slots[0]->file_descriptor.fd;
  long size;
  uint8_t *buf = to_octets(arguments->slots[1], &size);
  long bytes_written;
  if (event__mode != EM__REPLAY) {
    do {
      bytes_written = write(fd, buf, size);
    } while (bytes_written == -1 && errno == EINTR);

    
    
    if (event__mode == EM__RECORD) {
      if (bytes_written == size) {
        successful__action("write_some_bytes_to");
      } else {
        failed__action("write_some_bytes_to");
        store__long_integer(bytes_written);
      }
      }
    } else {
      if (replay__action("write_some_bytes_to")) {
        retrieve__long_integer(&bytes_written);
    } else {
        bytes_written = size;
    }
      report__event("write_some_bytes_to");
        print__integer(fd);
        print__memory(buf, bytes_written);
  }
  deallocate_memory(buf);
  {
    NODE *result__node = (NODE *)(from_long(bytes_written));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__128_1(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(3, 7);
  // slot allocations:
  // fd: 0
  // args: 1
  // return: 2
  // data: 3
  frame->slots[2] /* return */ = create_continuation();
  frame->slots[3] /* data */ = create_cell();
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  frame->slots[0] /* fd */ = arguments->slots[0];
  frame->slots[1] /* args */ = from_arguments(1, argument_count-1);
  // 819: $$data string(args*)
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[1] /* args */);
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__128_2;
}
static void cont__128_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* data */ = arguments->slots[0];
  // 820: ... -> length_of(data) > 0:
  // 821:   wait_to_write_to fd
  // 822:   write_some_bytes_to fd data $bytes_written
  // 823:   if bytes_written < 0:
  // 824:     if parameter_count_of(return) == 0: raise "Failed to write to file!"
  // 825:     return false
  // 826:   range &data bytes_written+1 -1
  frame->slots[4] /* temp__1 */ = create_closure(entry__128_3, 0);
  // 820: while -> length_of(data) > 0:
  // 821:   wait_to_write_to fd
  // 822:   write_some_bytes_to fd data $bytes_written
  // 823:   if bytes_written < 0:
  // 824:     if parameter_count_of(return) == 0: raise "Failed to write to file!"
  // 825:     return false
  // 826:   range &data bytes_written+1 -1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__while();
  func = myself->type;
  frame->cont = cont__128_20;
}
static void entry__128_6(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // fd: 0
  // data: 1
  // return: 2
  // bytes_written: 3
  frame->slots[0] = myself->closure.frame->slots[1]; /* fd */
  frame->slots[1] = myself->closure.frame->slots[0]; /* data */
  frame->slots[2] = myself->closure.frame->slots[2]; /* return */
  frame->slots[3] /* bytes_written */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 821: wait_to_write_to fd
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd */;
  result_count = 0;
  myself = get__wait_to_write_to();
  func = myself->type;
  frame->cont = cont__128_7;
}
static void cont__128_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 822: write_some_bytes_to fd data $bytes_written
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* data */;
  result_count = 1;
  myself = get__write_some_bytes_to();
  func = myself->type;
  frame->cont = cont__128_8;
}
static void cont__128_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* bytes_written */, arguments->slots[0]);
  // 823: ... bytes_written < 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* bytes_written */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__128_9;
}
static void cont__128_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 823: ... :
  // 824:   if parameter_count_of(return) == 0: raise "Failed to write to file!"
  // 825:   return false
  frame->slots[5] /* temp__2 */ = create_closure(entry__128_10, 0);
  // 823: if bytes_written < 0:
  // 824:   if parameter_count_of(return) == 0: raise "Failed to write to file!"
  // 825:   return false
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__128_16;
}
static void entry__128_10(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 824: ... parameter_count_of(return)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* return */;
  result_count = 1;
  myself = get__parameter_count_of();
  func = myself->type;
  frame->cont = cont__128_11;
}
static void cont__128_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 824: ... parameter_count_of(return) == 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__128_12;
}
static void cont__128_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 824: if parameter_count_of(return) == 0: raise "Failed to write to file!"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = func__128_13;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__128_15;
}
static void entry__128_13(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 824: ... raise "Failed to write to file!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__128_14;
  result_count = frame->caller_result_count;
  myself = get__raise();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__128_15(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 825: return false
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__false();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__128_16(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 826: ... bytes_written+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* bytes_written */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__128_17;
}
static void cont__128_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 826: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__128_18;
}
static void cont__128_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 826: range &data bytes_written+1 -1
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* data */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  arguments->slots[2] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__128_19;
}
static void cont__128_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* data */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__128_3(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // data: 0
  // fd: 1
  // return: 2
  frame->slots[0] = myself->closure.frame->slots[3]; /* data */
  frame->slots[1] = myself->closure.frame->slots[0]; /* fd */
  frame->slots[2] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 820: ... length_of(data)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* data */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__128_4;
}
static void cont__128_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 820: ... length_of(data) > 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__128_5;
}
static void cont__128_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 820: ... :
  // 821:   wait_to_write_to fd
  // 822:   write_some_bytes_to fd data $bytes_written
  // 823:   if bytes_written < 0:
  // 824:     if parameter_count_of(return) == 0: raise "Failed to write to file!"
  // 825:     return false
  // 826:   range &data bytes_written+1 -1
  frame->slots[5] /* temp__3 */ = create_closure(entry__128_6, 0);
  // 820: ... -> length_of(data) > 0:
  // 821:   wait_to_write_to fd
  // 822:   write_some_bytes_to fd data $bytes_written
  // 823:   if bytes_written < 0:
  // 824:     if parameter_count_of(return) == 0: raise "Failed to write to file!"
  // 825:     return false
  // 826:   range &data bytes_written+1 -1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__128_20(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 827: ... parameter_count_of(return)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* return */;
  result_count = 1;
  myself = get__parameter_count_of();
  func = myself->type;
  frame->cont = cont__128_21;
}
static void cont__128_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 827: ... parameter_count_of(return) == 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__128_22;
}
static void cont__128_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 827: ... : return true
  frame->slots[6] /* temp__3 */ = create_closure(entry__128_23, 0);
  // 827: if parameter_count_of(return) == 1: return true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__128_24;
}
static void entry__128_23(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 827: ... return true
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__true();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__128_24(void) {
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__129_1(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(3, 7);
  // slot allocations:
  // fd: 0
  // args: 1
  // return: 2
  // data: 3
  frame->slots[2] /* return */ = create_continuation();
  frame->slots[3] /* data */ = create_cell();
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  frame->slots[0] /* fd */ = arguments->slots[0];
  frame->slots[1] /* args */ = from_arguments(1, argument_count-1);
  // 835: $$data string(args*)
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[1] /* args */);
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__129_2;
}
static void cont__129_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* data */ = arguments->slots[0];
  // 836: ... -> length_of(data) > 0:
  // 837:   write_some_bytes_to fd data $bytes_written
  // 838:   if bytes_written < 0:
  // 839:     if parameter_count_of(return) == 0: raise "Failed to write to file!"
  // 840:     return false
  // 841:   range &data bytes_written+1 -1
  frame->slots[4] /* temp__1 */ = create_closure(entry__129_3, 0);
  // 836: while -> length_of(data) > 0:
  // 837:   write_some_bytes_to fd data $bytes_written
  // 838:   if bytes_written < 0:
  // 839:     if parameter_count_of(return) == 0: raise "Failed to write to file!"
  // 840:     return false
  // 841:   range &data bytes_written+1 -1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__while();
  func = myself->type;
  frame->cont = cont__129_18;
}
static void entry__129_6(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // fd: 0
  // data: 1
  // return: 2
  // bytes_written: 3
  frame->slots[0] = myself->closure.frame->slots[1]; /* fd */
  frame->slots[1] = myself->closure.frame->slots[0]; /* data */
  frame->slots[2] = myself->closure.frame->slots[2]; /* return */
  frame->slots[3] /* bytes_written */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 837: write_some_bytes_to fd data $bytes_written
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* data */;
  result_count = 1;
  myself = get__write_some_bytes_to();
  func = myself->type;
  frame->cont = cont__129_7;
}
static void cont__129_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* bytes_written */, arguments->slots[0]);
  // 838: ... bytes_written < 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* bytes_written */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__129_8;
}
static void cont__129_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 838: ... :
  // 839:   if parameter_count_of(return) == 0: raise "Failed to write to file!"
  // 840:   return false
  frame->slots[5] /* temp__2 */ = create_closure(entry__129_9, 0);
  // 838: if bytes_written < 0:
  // 839:   if parameter_count_of(return) == 0: raise "Failed to write to file!"
  // 840:   return false
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__129_14;
}
static void entry__129_9(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 839: ... parameter_count_of(return)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* return */;
  result_count = 1;
  myself = get__parameter_count_of();
  func = myself->type;
  frame->cont = cont__129_10;
}
static void cont__129_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 839: ... parameter_count_of(return) == 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__129_11;
}
static void cont__129_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 839: if parameter_count_of(return) == 0: raise "Failed to write to file!"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = func__129_12;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__129_13;
}
static void entry__129_12(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 839: ... raise "Failed to write to file!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__128_14;
  result_count = frame->caller_result_count;
  myself = get__raise();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__129_13(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 840: return false
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__false();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__129_14(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 841: ... bytes_written+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* bytes_written */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__129_15;
}
static void cont__129_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 841: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__129_16;
}
static void cont__129_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 841: range &data bytes_written+1 -1
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* data */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  arguments->slots[2] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__129_17;
}
static void cont__129_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* data */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__129_3(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // data: 0
  // fd: 1
  // return: 2
  frame->slots[0] = myself->closure.frame->slots[3]; /* data */
  frame->slots[1] = myself->closure.frame->slots[0]; /* fd */
  frame->slots[2] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 836: ... length_of(data)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* data */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__129_4;
}
static void cont__129_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 836: ... length_of(data) > 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__129_5;
}
static void cont__129_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 836: ... :
  // 837:   write_some_bytes_to fd data $bytes_written
  // 838:   if bytes_written < 0:
  // 839:     if parameter_count_of(return) == 0: raise "Failed to write to file!"
  // 840:     return false
  // 841:   range &data bytes_written+1 -1
  frame->slots[5] /* temp__3 */ = create_closure(entry__129_6, 0);
  // 836: ... -> length_of(data) > 0:
  // 837:   write_some_bytes_to fd data $bytes_written
  // 838:   if bytes_written < 0:
  // 839:     if parameter_count_of(return) == 0: raise "Failed to write to file!"
  // 840:     return false
  // 841:   range &data bytes_written+1 -1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__129_18(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 842: ... parameter_count_of(return)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* return */;
  result_count = 1;
  myself = get__parameter_count_of();
  func = myself->type;
  frame->cont = cont__129_19;
}
static void cont__129_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 842: ... parameter_count_of(return) == 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__129_20;
}
static void cont__129_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 842: ... : return true
  frame->slots[6] /* temp__3 */ = create_closure(entry__129_21, 0);
  // 842: if parameter_count_of(return) == 1: return true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__129_22;
}
static void entry__129_21(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 842: ... return true
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__true();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__129_22(void) {
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__130_4(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // fd: 0
  // buf: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* fd */
  frame->slots[1] /* buf */ = create_cell();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 864: $$buf ""
  ((CELL *)frame->slots[1])->contents /* buf */ = empty_string;
  // 865: ... : (-> break)
  // 866:   forever:
  // 867:     read_from fd $some_bytes
  // 868:     if length_of(some_bytes) == 0 break
  // 869:     append &buf some_bytes
  frame->slots[2] /* temp__1 */ = create_closure(entry__130_5, 0);
  // 865: do: (-> break)
  // 866:   forever:
  // 867:     read_from fd $some_bytes
  // 868:     if length_of(some_bytes) == 0 break
  // 869:     append &buf some_bytes
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__130_13;
}
static void entry__130_5(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // break: 0
  // fd: 1
  // buf: 2
  frame->slots[0] /* break */ = create_continuation();
  frame->slots[1] = myself->closure.frame->slots[0]; /* fd */
  frame->slots[2] = myself->closure.frame->slots[1]; /* buf */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 866: ... :
  // 867:   read_from fd $some_bytes
  // 868:   if length_of(some_bytes) == 0 break
  // 869:   append &buf some_bytes
  frame->slots[3] /* temp__1 */ = create_closure(entry__130_6, 0);
  // 866: forever:
  // 867:   read_from fd $some_bytes
  // 868:   if length_of(some_bytes) == 0 break
  // 869:   append &buf some_bytes
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__forever();
  func = myself->type;
  frame->cont = cont__130_12;
}
static void entry__130_6(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // fd: 0
  // break: 1
  // buf: 2
  // some_bytes: 3
  frame->slots[0] = myself->closure.frame->slots[1]; /* fd */
  frame->slots[1] = myself->closure.frame->slots[0]; /* break */
  frame->slots[2] = myself->closure.frame->slots[2]; /* buf */
  frame->slots[3] /* some_bytes */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 867: read_from fd $some_bytes
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd */;
  result_count = 1;
  myself = get__read_from();
  func = myself->type;
  frame->cont = cont__130_7;
}
static void cont__130_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* some_bytes */, arguments->slots[0]);
  // 868: ... length_of(some_bytes)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* some_bytes */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__130_8;
}
static void cont__130_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 868: ... length_of(some_bytes) == 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__130_9;
}
static void cont__130_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 868: if length_of(some_bytes) == 0 break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* break */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__130_10;
}
static void cont__130_10(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 869: append &buf some_bytes
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* buf */;
  arguments->slots[1] = frame->slots[3] /* some_bytes */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__130_11;
}
static void cont__130_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* buf */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__130_12(void) {
  myself = frame->slots[0] /* break */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__130_13(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 870: close fd
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd */;
  result_count = 0;
  myself = get__close();
  func = myself->type;
  frame->cont = cont__130_14;
}
static void cont__130_14(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 871: -> buf
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* buf */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__130_15(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 872: -> undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__130_1(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // filename: 0
  // fd: 1
  frame->slots[1] /* fd */ = create_future();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 861: open_file_for_reading $fd filename
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* filename */;
  result_count = 1;
  myself = get__open_file_for_reading();
  func = myself->type;
  frame->cont = cont__130_2;
}
static void cont__130_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* fd */, arguments->slots[0]);
  // 863: fd.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* fd */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__130_3;
}
static void cont__130_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 863: ... :
  // 864:   $$buf ""
  // 865:   do: (-> break)
  // 866:     forever:
  // 867:       read_from fd $some_bytes
  // 868:       if length_of(some_bytes) == 0 break
  // 869:       append &buf some_bytes
  // 870:   close fd
  // 871:   -> buf
  frame->slots[3] /* temp__2 */ = create_closure(entry__130_4, 0);
  // 862: if
  // 863:   fd.is_defined:
  // 864:     $$buf ""
  // 865:     do: (-> break)
  // 866:       forever:
  // 867:         read_from fd $some_bytes
  // 868:         if length_of(some_bytes) == 0 break
  // 869:         append &buf some_bytes
  // 870:     close fd
  // 871:     -> buf
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  arguments->slots[2] = func__130_15;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__131_1(void) {
  allocate_initialized_frame_gc(3, 7);
  // slot allocations:
  // filename: 0
  // data: 1
  // return: 2
  // fd: 3
  frame->slots[2] /* return */ = create_continuation();
  frame->slots[3] /* fd */ = create_future();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 896: create_file $fd filename
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* filename */;
  result_count = 1;
  myself = get__create_file();
  func = myself->type;
  frame->cont = cont__131_2;
}
static void cont__131_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* fd */, arguments->slots[0]);
  // 898: fd.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* fd */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__131_3;
}
static void cont__131_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 898: ... :
  // 899:   if
  // 900:     parameter_count_of(return) == 0:
  // 901:       write_to fd data
  // 902:       close fd
  // 903:     :
  // 904:       return write_to(fd data) && close(fd)
  frame->slots[5] /* temp__2 */ = create_closure(entry__131_4, 0);
  // 905: :
  // 906:   if parameter_count_of(return) == 0:
  // 907:     raise "
  // 908:       Failed to save file "@(filename)@quot;@
  // 909:   return false
  frame->slots[6] /* temp__3 */ = create_closure(entry__131_14, 0);
  // 897: if
  // 898:   fd.is_defined:
  // 899:     if
  // 900:       parameter_count_of(return) == 0:
  // 901:         write_to fd data
  // 902:         close fd
  // 903:       :
  // 904:         return write_to(fd data) && close(fd)
  // 905:   :
  // 906:     if parameter_count_of(return) == 0:
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  arguments->slots[2] = frame->slots[6] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__131_22;
}
static void entry__131_7(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // fd: 0
  // data: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* fd */
  frame->slots[1] = myself->closure.frame->slots[2]; /* data */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 901: write_to fd data
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd */;
  arguments->slots[1] = frame->slots[1] /* data */;
  result_count = 0;
  myself = get__write_to();
  func = myself->type;
  frame->cont = cont__131_8;
}
static void cont__131_8(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 902: close fd
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd */;
  result_count = frame->caller_result_count;
  myself = get__close();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__131_9(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // return: 0
  // fd: 1
  // data: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* return */
  frame->slots[1] = myself->closure.frame->slots[1]; /* fd */
  frame->slots[2] = myself->closure.frame->slots[2]; /* data */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 904: ... write_to(fd data)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* fd */;
  arguments->slots[1] = frame->slots[2] /* data */;
  result_count = 1;
  myself = get__write_to();
  func = myself->type;
  frame->cont = cont__131_10;
}
static void cont__131_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 904: ... close(fd)
  frame->slots[5] /* temp__3 */ = create_closure(entry__131_11, 0);
  // 904: ... write_to(fd data) && close(fd)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__131_13;
}
static void entry__131_11(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // fd: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* fd */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 904: ... close(fd)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd */;
  result_count = 1;
  myself = get__close();
  func = myself->type;
  frame->cont = cont__131_12;
}
static void cont__131_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 904: ... close(fd)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__131_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 904: return write_to(fd data) && close(fd)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__131_4(void) {
  allocate_initialized_frame_gc(3, 7);
  // slot allocations:
  // return: 0
  // fd: 1
  // data: 2
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  frame->slots[1] = myself->closure.frame->slots[3]; /* fd */
  frame->slots[2] = myself->closure.frame->slots[1]; /* data */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 900: parameter_count_of(return)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* return */;
  result_count = 1;
  myself = get__parameter_count_of();
  func = myself->type;
  frame->cont = cont__131_5;
}
static void cont__131_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 900: parameter_count_of(return) == 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__131_6;
}
static void cont__131_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 900: ... :
  // 901:   write_to fd data
  // 902:   close fd
  frame->slots[5] /* temp__3 */ = create_closure(entry__131_7, 0);
  // 903: :
  // 904:   return write_to(fd data) && close(fd)
  frame->slots[6] /* temp__4 */ = create_closure(entry__131_9, 0);
  // 899: if
  // 900:   parameter_count_of(return) == 0:
  // 901:     write_to fd data
  // 902:     close fd
  // 903:   :
  // 904:     return write_to(fd data) && close(fd)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  arguments->slots[2] = frame->slots[6] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__131_14(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // return: 0
  // filename: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  frame->slots[1] = myself->closure.frame->slots[0]; /* filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 906: ... parameter_count_of(return)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* return */;
  result_count = 1;
  myself = get__parameter_count_of();
  func = myself->type;
  frame->cont = cont__131_15;
}
static void cont__131_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 906: ... parameter_count_of(return) == 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__131_16;
}
static void cont__131_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 906: ... :
  // 907:   raise "
  // 908:     Failed to save file "@(filename)@quot;@
  frame->slots[4] /* temp__3 */ = create_closure(entry__131_17, 0);
  // 906: if parameter_count_of(return) == 0:
  // 907:   raise "
  // 908:     Failed to save file "@(filename)@quot;@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__131_21;
}
static void entry__131_17(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // filename: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 907: ... "
  // 908:   Failed to save file "@(filename)@quot;@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__131_18;
  arguments->slots[1] = frame->slots[0] /* filename */;
  arguments->slots[2] = string__131_19;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__131_20;
}
static void cont__131_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 907: raise "
  // 908:   Failed to save file "@(filename)@quot;@
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__raise();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__131_21(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 909: return false
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__false();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__131_22(void) {
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__132_1(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  int fd = arguments->slots[0]->file_descriptor.fd;
  if (result_count == 1) {
    int err;
    if (event__mode != EM__REPLAY) {
      err = fsync(fd);
      if (event__mode == EM__RECORD) {
        if (err == 0) {
        successful__action("flush");
      } else {
        failed__action("flush");
        store__integer(err);
      }
        }
    } else {
      if (replay__action("flush")) {
        retrieve__integer(&err);
    } else {
        err = 0;
    }
  }
    {
    NODE *result__node = (NODE *)(from_int(err));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else {
    fsync(fd);
    {
    argument_count = 0;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  }
}
static void entry__133_1(void) {
  if (argument_count != 3) {
    invalid_arguments_error();
    return;
  }
  int fd = arguments->slots[0]->file_descriptor.fd;
  long request = to_long(arguments->slots[1]);
  long value = to_long(arguments->slots[2]);
  int err;
  if (event__mode != EM__REPLAY) {
    err = ioctl(fd, request, value);
    if (event__mode == EM__RECORD) {
      if (err == 0) {
        successful__action("ioctl_value");
      } else {
        failed__action("ioctl_value");
        store__integer(err);
      }
      }
    } else {
      if (replay__action("ioctl_value")) {
        retrieve__integer(&err);
    } else {
        err = 0;
    }
  }
  {
    NODE *result__node = (NODE *)(from_int(err));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__134_1(void) {
  allocate_initialized_frame_gc(4, 8);
  // slot allocations:
  // fd: 0
  // request: 1
  // value: 2
  // return: 3
  frame->slots[3] /* return */ = create_continuation();
  if (argument_count < 2) {
    too_few_arguments_error();
    return;
  }
  if (argument_count > 3) {
    too_many_arguments_error();
    return;
  }
  switch(argument_count) {
    default: frame->slots[2] /* value */ = arguments->slots[2];
    case 2:;
  }
  switch(argument_count) {
    case 2: frame->slots[2] /* value */ = number__0;
  }
  // 952: parameter_count_of(return)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* return */;
  result_count = 1;
  myself = get__parameter_count_of();
  func = myself->type;
  frame->cont = cont__134_2;
}
static void cont__134_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 952: parameter_count_of(return) == 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__134_3;
}
static void cont__134_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 952: ... :
  // 953:   if ioctl_value(fd request value) != 0:
  // 954:     raise "
  // 955:       IOCTL failed!
  frame->slots[6] /* temp__3 */ = create_closure(entry__134_4, 0);
  // 956: :
  // 957:   return ioctl_value(fd request value)
  frame->slots[7] /* temp__4 */ = create_closure(entry__134_10, 0);
  // 951: if
  // 952:   parameter_count_of(return) == 0:
  // 953:     if ioctl_value(fd request value) != 0:
  // 954:       raise "
  // 955:         IOCTL failed!
  // 956:   :
  // 957:     return ioctl_value(fd request value)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  arguments->slots[2] = frame->slots[7] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__134_12;
}
static void entry__134_8(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 954: raise "
  // 955:   IOCTL failed!
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__134_9;
  result_count = frame->caller_result_count;
  myself = get__raise();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__134_4(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // fd: 0
  // request: 1
  // value: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* fd */
  frame->slots[1] = myself->closure.frame->slots[1]; /* request */
  frame->slots[2] = myself->closure.frame->slots[2]; /* value */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 953: ... ioctl_value(fd request value)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd */;
  arguments->slots[1] = frame->slots[1] /* request */;
  arguments->slots[2] = frame->slots[2] /* value */;
  result_count = 1;
  myself = var._ioctl_value;
  func = myself->type;
  frame->cont = cont__134_5;
}
static void cont__134_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 953: ... ioctl_value(fd request value) != 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__3 */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__134_6;
}
static void cont__134_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 953: ... ioctl_value(fd request value) != 0
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__134_7;
}
static void cont__134_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 953: if ioctl_value(fd request value) != 0:
  // 954:   raise "
  // 955:     IOCTL failed!
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = func__134_8;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__134_10(void) {
  allocate_initialized_frame_gc(4, 5);
  // slot allocations:
  // return: 0
  // fd: 1
  // request: 2
  // value: 3
  frame->slots[0] = myself->closure.frame->slots[3]; /* return */
  frame->slots[1] = myself->closure.frame->slots[0]; /* fd */
  frame->slots[2] = myself->closure.frame->slots[1]; /* request */
  frame->slots[3] = myself->closure.frame->slots[2]; /* value */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 957: ... ioctl_value(fd request value)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* fd */;
  arguments->slots[1] = frame->slots[2] /* request */;
  arguments->slots[2] = frame->slots[3] /* value */;
  result_count = 1;
  myself = var._ioctl_value;
  func = myself->type;
  frame->cont = cont__134_11;
}
static void cont__134_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 957: return ioctl_value(fd request value)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__134_12(void) {
  myself = frame->slots[3] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__135_1(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }

  int fd = arguments->slots[0]->file_descriptor.fd;
  int width, height;
  struct winsize winsize;

  if (event__mode != EM__REPLAY) {
    ioctl(fd, TIOCGWINSZ, &winsize);
    width = winsize.ws_col;
    height = winsize.ws_row;
    if (event__mode == EM__RECORD) {
      record__event("get_terminal_size");
      store__integer(width);
      store__integer(height);
    }
  } else {
    replay__event("get_terminal_size");
    retrieve__integer(&width);
    retrieve__integer(&height);
  }
  NODE *width_node = from_int(width);
  NODE *height_node = from_int(height);
  argument_count = 2;
  arguments = node_p;;
  arguments->slots[0] = width_node;
  arguments->slots[1] = height_node;
  {
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__136_1(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  char *filename = to_c_string(arguments->slots[0]);
  int err;
  if (event__mode != EM__REPLAY) {
    err = unlink(filename);
    if (event__mode == EM__RECORD) {
      if (err == 0) {
        successful__action("unlink");
      } else {
        failed__action("unlink");
        store__integer(err);
      }
      }
    } else {
      if (replay__action("unlink")) {
        retrieve__integer(&err);
    } else {
        err = 0;
    }
  }
  deallocate_memory(filename);
  {
    NODE *result__node = (NODE *)(from_int(err));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__137_1(void) {
  allocate_initialized_frame_gc(2, 6);
  // slot allocations:
  // filename: 0
  // return: 1
  frame->slots[1] /* return */ = create_continuation();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 1003: parameter_count_of(return)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* return */;
  result_count = 1;
  myself = get__parameter_count_of();
  func = myself->type;
  frame->cont = cont__137_2;
}
static void cont__137_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 1003: parameter_count_of(return) == 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__137_3;
}
static void cont__137_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 1003: ... :
  // 1004:   if posix_unlink(filename) != 0:
  // 1005:     raise "
  // 1006:       Failed to delete file "@(filename)@quot;!
  frame->slots[4] /* temp__3 */ = create_closure(entry__137_4, 0);
  // 1007: :
  // 1008:   return posix_unlink(filename) == 0
  frame->slots[5] /* temp__4 */ = create_closure(entry__137_12, 0);
  // 1002: if
  // 1003:   parameter_count_of(return) == 0:
  // 1004:     if posix_unlink(filename) != 0:
  // 1005:       raise "
  // 1006:         Failed to delete file "@(filename)@quot;!
  // 1007:   :
  // 1008:     return posix_unlink(filename) == 0
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  arguments->slots[2] = frame->slots[5] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__137_15;
}
static void entry__137_8(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // filename: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1005: ... "
  // 1006:   Failed to delete file "@(filename)@quot;!
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__137_9;
  arguments->slots[1] = frame->slots[0] /* filename */;
  arguments->slots[2] = string__137_10;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__137_11;
}
static void cont__137_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1005: raise "
  // 1006:   Failed to delete file "@(filename)@quot;!
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__raise();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__137_4(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // filename: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1004: ... posix_unlink(filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* filename */;
  result_count = 1;
  myself = var._posix_unlink;
  func = myself->type;
  frame->cont = cont__137_5;
}
static void cont__137_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 1004: ... posix_unlink(filename) != 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__137_6;
}
static void cont__137_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 1004: ... posix_unlink(filename) != 0
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__137_7;
}
static void cont__137_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1004: ... :
  // 1005:   raise "
  // 1006:     Failed to delete file "@(filename)@quot;!
  frame->slots[4] /* temp__4 */ = create_closure(entry__137_8, 0);
  // 1004: if posix_unlink(filename) != 0:
  // 1005:   raise "
  // 1006:     Failed to delete file "@(filename)@quot;!
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__137_12(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // return: 0
  // filename: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* return */
  frame->slots[1] = myself->closure.frame->slots[0]; /* filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1008: ... posix_unlink(filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* filename */;
  result_count = 1;
  myself = var._posix_unlink;
  func = myself->type;
  frame->cont = cont__137_13;
}
static void cont__137_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 1008: ... posix_unlink(filename) == 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__137_14;
}
static void cont__137_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 1008: return posix_unlink(filename) == 0
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__137_15(void) {
  myself = frame->slots[1] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__138_1(void) {
  if (argument_count != 4) {
    invalid_arguments_error();
    return;
  }
  NODE *read_descriptors = arguments->slots[0];
  NODE *write_descriptors = arguments->slots[1];
  NODE *except_descriptors = arguments->slots[2];
  double timeout = 0.0;
  struct timespec timeout_data;
  struct timespec *timeout_ptr = NULL;

  if ((arguments->slots[3])->type != (undefined)->type) {
    timeout = to_double(arguments->slots[3]);
    timeout_data.tv_sec = timeout;
    timeout_data.tv_nsec = 1000000000*(timeout-floor(timeout));
    timeout_ptr = &timeout_data;
  }
  retry:;
  int i, n;
  fd_set read_set, write_set, except_set;
  int last_fd = 0;
  FD_ZERO(&read_set);
  FD_ZERO(&write_set);
  FD_ZERO(&except_set);
  n = length_of(read_descriptors);
  for (i = 0; i < n; ++i) {
    NODE *descriptor = get_item_of(read_descriptors, i);
    if ((descriptor)->type != type__types__file_descriptor) {
    invalid_arguments_error();
  }
    int fd = descriptor->file_descriptor.fd;
    FD_SET(fd, &read_set);
    if (fd > last_fd) last_fd = fd;
  }
  n = length_of(write_descriptors);
  for (i = 0; i < n; ++i) {
    NODE *descriptor = get_item_of(write_descriptors, i);
    if ((descriptor)->type != type__types__file_descriptor) {
    invalid_arguments_error();
  }
    int fd = descriptor->file_descriptor.fd;
    FD_SET(fd, &write_set);
    if (fd > last_fd) last_fd = fd;
  }
  n = length_of(except_descriptors);
  for (i = 0; i < n; ++i) {
    NODE *descriptor = get_item_of(except_descriptors, i);
    if ((descriptor)->type != type__types__file_descriptor) {
    invalid_arguments_error();
  }
    int fd = descriptor->file_descriptor.fd;
    FD_SET(fd, &except_set);
    if (fd > last_fd) last_fd = fd;
  }
  int ret;
  int chld_changed_state = false;
  int win_changed_size = false;
  int read_count = 0;
  int write_count = 0;
  int except_count = 0;
  int descriptor_count = 0;
  int *descriptors = NULL;
  if (event__mode != EM__REPLAY) {
    sigset_t set;
    sigprocmask(SIG_BLOCK, NULL, &set);
    sigdelset(&set, SIGCHLD);
    sigdelset(&set, SIGWINCH);
    ret = pselect(last_fd+1, &read_set, &write_set, &except_set, timeout_ptr, &set);
    if (ret < 0 && errno == EINTR) {
      if (child_changed_state) {
        child_changed_state = false;
        chld_changed_state = true;
      } else if (window_changed_size) {
        window_changed_size = false;
        win_changed_size = true;
      } else {
        goto retry;
      }
    }
    if (ret > 0) { // success
      int fd;
      for (fd = 0; fd <= last_fd; ++fd) {
        if (FD_ISSET(fd, &read_set)) ++read_count;
        if (FD_ISSET(fd, &write_set)) ++write_count;
        if (FD_ISSET(fd, &except_set)) ++except_count;
      }
      descriptor_count = read_count+write_count+except_count;
      descriptors = allocate_memory(descriptor_count*sizeof(int));
      n = 0;
      if (read_count > 0) {
        for (fd = 0; fd <= last_fd; ++fd) {
          if (FD_ISSET(fd, &read_set)) {
            descriptors[n++] = fd;
          }
        }
      }
      if (write_count > 0) {
        for (fd = 0; fd <= last_fd; ++fd) {
          if (FD_ISSET(fd, &write_set)) {
            // set file descriptor to nonblocking
            int flags = fcntl(fd, F_GETFL, 0);
            if (flags == -1) flags = 0;
            fcntl(fd, F_SETFL, flags|O_NONBLOCK);
            descriptors[n++] = fd;
          }
        }
      }
      if (except_count > 0) {
        for (fd = 0; fd <= last_fd; ++fd) {
          if (FD_ISSET(fd, &except_set)) {
            descriptors[n++] = fd;
          }
        }
      }
    }
    if (event__mode == EM__RECORD) {
      record__event("wait_for_io");
      store__integer(ret);
      store__integer(chld_changed_state);
      store__integer(win_changed_size);
      store__integer(read_count);
      store__integer(write_count);
      store__integer(except_count);
      store__int_array(descriptors, descriptor_count);
    }
  } else {
    replay__event("wait_for_io");
    retrieve__integer(&ret);
    retrieve__integer(&chld_changed_state);
    retrieve__integer(&win_changed_size);
    retrieve__integer(&read_count);
    retrieve__integer(&write_count);
    retrieve__integer(&except_count);
    descriptor_count = retrieve__int_array((int **)&descriptors);
  }
  if (chld_changed_state || win_changed_size) {
    NODE *child_change_state_node = from_bool(chld_changed_state);
    NODE *window_changed_size_node = from_bool(win_changed_size);
    argument_count = 6;
  arguments = node_p;;
    arguments->slots[0] = boolean_true;
    arguments->slots[1] = child_change_state_node;
    arguments->slots[2] = window_changed_size_node;
    arguments->slots[3] = zero;
    arguments->slots[4] = zero;
    arguments->slots[5] = zero;
    {
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if (ret > 0) { // success
    int i;
    NODE *input_count = from_int(read_count);
    NODE *output_count = from_int(write_count);
    NODE *exception_count = from_int(except_count);
    NODE **descriptor_nodes = allocate(descriptor_count*sizeof(NODE *));
    for (i = 0; i < descriptor_count; ++i) {
      descriptor_nodes[i] = create__types__file_descriptor(descriptors[i]);
    }
    deallocate_memory(descriptors);
    argument_count = 6+descriptor_count;
  arguments = node_p;;
    arguments->slots[0] = boolean_true;
    arguments->slots[1] = boolean_false;
    arguments->slots[2] = boolean_false;
    arguments->slots[3] = input_count;
    arguments->slots[4] = output_count;
    arguments->slots[5] = exception_count;
    for (i = 0; i < descriptor_count; ++i) {
      arguments->slots[6+i] = descriptor_nodes[i];
    }
    {
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else if (ret == 0) { // timeout occured
    argument_count = 6;
  arguments = node_p;;
    arguments->slots[0] = boolean_false;
    arguments->slots[1] = boolean_false;
    arguments->slots[2] = boolean_false;
    arguments->slots[3] = zero;
    arguments->slots[4] = zero;
    arguments->slots[5] = zero;
    {
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else { // error
    {
    runtime_error("Unexpected I/O-error (%s) during select!", strerror(errno));
  }
  }
}
static void entry__139_1(void) {
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  {
    NODE *result__node = (NODE *)(from_int(getpid()));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__140_1(void) {
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  int pid = to_int(arguments->slots[0]);
  int no_hang = to_bool(arguments->slots[1]);
  int status;
  int ret = waitpid(pid, &status, no_hang ? WNOHANG : 0);
  NODE *child_status = from_int(WEXITSTATUS(status));
  NODE *child_pid = from_int(ret);
  argument_count = 2;
  arguments = node_p;;
  arguments->slots[0] = child_status;
  arguments->slots[1] = child_pid;
  {
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__141_1(void) {
  allocate_initialized_frame_gc(4, 19);
  // slot allocations:
  // read_descriptors: 0
  // write_descriptors: 1
  // except_descriptors: 2
  // timeout: 3
  // success: 4
  // child_changed_state: 5
  // window_changed_size: 6
  // input_count: 7
  // output_count: 8
  // exception_count: 9
  // descriptors: 10
  frame->slots[4] /* success */ = create_future();
  frame->slots[5] /* child_changed_state */ = create_future();
  frame->slots[6] /* window_changed_size */ = create_future();
  frame->slots[7] /* input_count */ = create_future();
  frame->slots[8] /* output_count */ = create_future();
  frame->slots[9] /* exception_count */ = create_future();
  frame->slots[10] /* descriptors */ = create_future();
  if (argument_count < 3) {
    too_few_arguments_error();
    return;
  }
  if (argument_count > 4) {
    too_many_arguments_error();
    return;
  }
  switch(argument_count) {
    default: frame->slots[3] /* timeout */ = arguments->slots[3];
    case 3:;
  }
  switch(argument_count) {
    case 3: frame->slots[3] /* timeout */ = undefined;
  }
  // 1201: wait_for_io_ready
  // 1202:   read_descriptors
  // 1203:   write_descriptors
  // 1204:   except_descriptors
  // 1205:   timeout
  // 1206:   $success
  // 1207:   $child_changed_state
  // 1208:   $window_changed_size
  // 1209:   $input_count
  // 1210:   $output_count
  // ...
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* read_descriptors */;
  arguments->slots[1] = frame->slots[1] /* write_descriptors */;
  arguments->slots[2] = frame->slots[2] /* except_descriptors */;
  arguments->slots[3] = frame->slots[3] /* timeout */;
  result_count = -1;
  myself = var._wait_for_io_ready;
  func = myself->type;
  frame->cont = cont__141_2;
}
static void cont__141_2(void) {
  if (argument_count < 6) {
    too_few_results_error();
    return;
  }
  allocate_arguments();
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  frame->slots[12] /* temp__2 */ = arguments->slots[1];
  frame->slots[13] /* temp__3 */ = arguments->slots[2];
  frame->slots[14] /* temp__4 */ = arguments->slots[3];
  frame->slots[15] /* temp__5 */ = arguments->slots[4];
  frame->slots[16] /* temp__6 */ = arguments->slots[5];
  frame->slots[17] /* temp__7 */ = from_arguments(6, argument_count-6);
  // 1206: ... success
  initialize_future(frame->slots[4] /* success */, frame->slots[11] /* temp__1 */);
  // 1207: ... child_changed_state
  initialize_future(frame->slots[5] /* child_changed_state */, frame->slots[12] /* temp__2 */);
  // 1208: ... window_changed_size
  initialize_future(frame->slots[6] /* window_changed_size */, frame->slots[13] /* temp__3 */);
  // 1209: ... input_count
  initialize_future(frame->slots[7] /* input_count */, frame->slots[14] /* temp__4 */);
  // 1210: ... output_count
  initialize_future(frame->slots[8] /* output_count */, frame->slots[15] /* temp__5 */);
  // 1211: ... _exception_count
  initialize_future(frame->slots[9] /* exception_count */, frame->slots[16] /* temp__6 */);
  // 1212: ... descriptors
  initialize_future(frame->slots[10] /* descriptors */, frame->slots[17] /* temp__7 */);
  // 1216: range(descriptors 1 input_count)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* descriptors */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[7] /* input_count */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__141_3;
}
static void cont__141_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 1217: ... input_count+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* input_count */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__141_4;
}
static void cont__141_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__3 */ = arguments->slots[0];
  // 1217: ... input_count+output_count
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* input_count */;
  arguments->slots[1] = frame->slots[8] /* output_count */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__141_5;
}
static void cont__141_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[14] /* temp__4 */ = arguments->slots[0];
  // 1217: range(descriptors input_count+1 input_count+output_count)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* descriptors */;
  arguments->slots[1] = frame->slots[13] /* temp__3 */;
  arguments->slots[2] = frame->slots[14] /* temp__4 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__141_6;
}
static void cont__141_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__2 */ = arguments->slots[0];
  // 1218: ... input_count+output_count
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* input_count */;
  arguments->slots[1] = frame->slots[8] /* output_count */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__141_7;
}
static void cont__141_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[17] /* temp__7 */ = arguments->slots[0];
  // 1218: ... input_count+output_count+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[17] /* temp__7 */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__141_8;
}
static void cont__141_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[16] /* temp__6 */ = arguments->slots[0];
  // 1218: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__141_9;
}
static void cont__141_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[18] /* temp__8 */ = arguments->slots[0];
  // 1218: range(descriptors input_count+output_count+1 -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* descriptors */;
  arguments->slots[1] = frame->slots[16] /* temp__6 */;
  arguments->slots[2] = frame->slots[18] /* temp__8 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__141_10;
}
static void cont__141_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[15] /* temp__5 */ = arguments->slots[0];
  // 1213: ->
  // 1214:   child_changed_state
  // 1215:   window_changed_size
  // 1216:   range(descriptors 1 input_count)
  // 1217:   range(descriptors input_count+1 input_count+output_count)
  // 1218:   range(descriptors input_count+output_count+1 -1)
  // 1219:   success
  argument_count = 6;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* child_changed_state */;
  arguments->slots[1] = frame->slots[6] /* window_changed_size */;
  arguments->slots[2] = frame->slots[11] /* temp__1 */;
  arguments->slots[3] = frame->slots[12] /* temp__2 */;
  arguments->slots[4] = frame->slots[15] /* temp__5 */;
  arguments->slots[5] = frame->slots[4] /* success */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__142_1(void) {
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  char *buf = NULL;
  char *ret;
  long size = 0x80;
  do {
    size += size;
    buf = reallocate_memory(buf, size);
    ret = getcwd(buf, size);
  } while (!ret && errno == ERANGE && size < 0x1000);
  NODE *result;
  if (ret) {
    result = from_c_string(buf);
  } else {
    result = undefined;
  }
  deallocate_memory(buf);
  {
    NODE *result__node = (NODE *)(result);
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__143_1(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  char *path = to_c_string(arguments->slots[0]);
  int err;
  if (event__mode != EM__REPLAY) {
    err = chdir(path);
    if (event__mode == EM__RECORD) {
      if (err == 0) {
        successful__action("chdir");
      } else {
        failed__action("chdir");
        store__integer(err);
      }
      }
    } else {
      if (replay__action("chdir")) {
        retrieve__integer(&err);
    } else {
        err = 0;
    }
  }
  deallocate_memory(path);
  {
    NODE *result__node = (NODE *)(from_int(err));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__144_5(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // path: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* path */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1258: ... "
  // 1259:   Failed to change current directory to "@(path)@quot;!@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__144_6;
  arguments->slots[1] = frame->slots[0] /* path */;
  arguments->slots[2] = string__144_7;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__144_8;
}
static void cont__144_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1258: Error "
  // 1259:   Failed to change current directory to "@(path)@quot;!@
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__144_1(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // path: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 1257: ... std::chdir(path)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* path */;
  result_count = 1;
  myself = var.std__chdir;
  func = myself->type;
  frame->cont = cont__144_2;
}
static void cont__144_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 1257: ... std::chdir(path) != 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__144_3;
}
static void cont__144_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 1257: ... std::chdir(path) != 0
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__144_4;
}
static void cont__144_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1257: ... :
  // 1258:   Error "
  // 1259:     Failed to change current directory to "@(path)@quot;!@
  frame->slots[4] /* temp__4 */ = create_closure(entry__144_5, 0);
  // 1257: if std::chdir(path) != 0:
  // 1258:   Error "
  // 1259:     Failed to change current directory to "@(path)@quot;!@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__145_1(void) {
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  char *path = to_c_string(arguments->slots[0]);
  int mode = to_int(arguments->slots[1]);
  int err;
  if (event__mode != EM__REPLAY) {
    err = mkdir(path, mode);
    if (event__mode == EM__RECORD) {
      if (err == 0) {
        successful__action("mkdir");
      } else {
        failed__action("mkdir");
        store__integer(err);
      }
      }
    } else {
      if (replay__action("mkdir")) {
        retrieve__integer(&err);
    } else {
        err = 0;
    }
  }
  deallocate_memory(path);
  {
    NODE *result__node = (NODE *)(from_int(err));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__146_35(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // do_create_parent_folders: 0
  // fail: 1
  frame->slots[0] = myself->closure.frame->slots[3]; /* do_create_parent_folders */
  frame->slots[1] = myself->closure.frame->slots[4]; /* fail */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1300: ... do_create_parent_folders && errno() == EEXIST
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* do_create_parent_folders */;
  arguments->slots[1] = func__146_36;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__146_39;
}
static void entry__146_36(void) {
  allocate_initialized_frame_gc(0, 2);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1300: ... errno()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__errno();
  func = myself->type;
  frame->cont = cont__146_37;
}
static void cont__146_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 1300: ... errno() == EEXIST
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  arguments->slots[1] = get__EEXIST();
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__146_38;
}
static void cont__146_38(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1300: ... errno() == EEXIST
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__146_39(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 1300: unless do_create_parent_folders && errno() == EEXIST fail
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* fail */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__146_1(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(2, 10);
  // slot allocations:
  // options: 0
  // path: 1
  // mode: 2
  // do_create_parent_folders: 3
  // fail: 4
  // create_parent_folders: 5
  frame->slots[4] /* fail */ = create_future();
  frame->slots[5] /* create_parent_folders */ = create_future();
  frame->slots[2] /* mode */ = create_future();
  frame->slots[3] /* do_create_parent_folders */ = create_future();
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  frame->slots[1] /* path */ = create_cell_with_contents(arguments->slots[argument_count-1]);
  frame->slots[0] /* options */ = from_arguments(0, argument_count-1);
  // 1284: ... :
  // 1285:   raise_error
  // 1286:     "mkdir"
  // 1287:     "MODE" = string("0o" oct(mode))
  // 1288:     "PARENTS" = do_create_parent_folders
  // 1289:     "path" = path
  frame->slots[6] /* temp__1 */ = create_closure(entry__146_2, 0);
  // 1284: $fail:
  // 1285:   raise_error
  // 1286:     "mkdir"
  // 1287:     "MODE" = string("0o" oct(mode))
  // 1288:     "PARENTS" = do_create_parent_folders
  // 1289:     "path" = path
  initialize_future(frame->slots[4] /* fail */, frame->slots[6] /* temp__1 */);
  // 1291: ... : ($partial_path)
  // 1292:   before &partial_path '/' -1
  // 1293:   if partial_path != "":
  // 1294:     create_parent_folders partial_path
  // 1295:     if clib_mkdir(partial_path mode) < 0 && errno() != EEXIST fail
  frame->slots[6] /* temp__1 */ = create_closure(entry__146_13, 1);
  // 1291: $create_parent_folders: ($partial_path)
  // 1292:   before &partial_path '/' -1
  // 1293:   if partial_path != "":
  // 1294:     create_parent_folders partial_path
  // 1295:     if clib_mkdir(partial_path mode) < 0 && errno() != EEXIST fail
  initialize_future(frame->slots[5] /* create_parent_folders */, frame->slots[6] /* temp__1 */);
  // 1279: MODE = 0o755
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__MODE();
  arguments->slots[1] = number__0o755;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__146_27;
}
static void entry__146_18(void) {
  allocate_initialized_frame_gc(4, 7);
  // slot allocations:
  // create_parent_folders: 0
  // partial_path: 1
  // mode: 2
  // fail: 3
  frame->slots[0] = myself->closure.frame->slots[1]; /* create_parent_folders */
  frame->slots[1] = myself->closure.frame->slots[0]; /* partial_path */
  frame->slots[2] = myself->closure.frame->slots[2]; /* mode */
  frame->slots[3] = myself->closure.frame->slots[3]; /* fail */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1294: create_parent_folders partial_path
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* partial_path */;
  result_count = 0;
  myself = frame->slots[0] /* create_parent_folders */;
  func = myself->type;
  frame->cont = cont__146_19;
}
static void cont__146_19(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1295: ... clib_mkdir(partial_path mode)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* partial_path */;
  arguments->slots[1] = frame->slots[2] /* mode */;
  result_count = 1;
  myself = get__clib_mkdir();
  func = myself->type;
  frame->cont = cont__146_20;
}
static void cont__146_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 1295: ... clib_mkdir(partial_path mode) < 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__3 */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__146_21;
}
static void cont__146_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 1295: ... clib_mkdir(partial_path mode) < 0 && errno() != EEXIST
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  arguments->slots[1] = func__146_22;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__146_26;
}
static void entry__146_22(void) {
  allocate_initialized_frame_gc(0, 3);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1295: ... errno()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__errno();
  func = myself->type;
  frame->cont = cont__146_23;
}
static void cont__146_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 1295: ... errno() != EEXIST
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__3 */;
  arguments->slots[1] = get__EEXIST();
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__146_24;
}
static void cont__146_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 1295: ... errno() != EEXIST
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__146_25;
}
static void cont__146_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1295: ... errno() != EEXIST
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__146_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 1295: if clib_mkdir(partial_path mode) < 0 && errno() != EEXIST fail
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* fail */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__146_2(void) {
  allocate_initialized_frame_gc(3, 8);
  // slot allocations:
  // mode: 0
  // do_create_parent_folders: 1
  // path: 2
  frame->slots[0] = myself->closure.frame->slots[2]; /* mode */
  frame->slots[1] = myself->closure.frame->slots[3]; /* do_create_parent_folders */
  frame->slots[2] = myself->closure.frame->slots[1]; /* path */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1287: ... oct(mode)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mode */;
  result_count = 1;
  myself = get__oct();
  func = myself->type;
  frame->cont = cont__146_3;
}
static void cont__146_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 1287: ... string("0o" oct(mode))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__146_4;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__146_5;
}
static void cont__146_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 1287: "MODE" = string("0o" oct(mode))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__146_6;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__146_7;
}
static void cont__146_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 1288: "PARENTS" = do_create_parent_folders
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__146_8;
  arguments->slots[1] = frame->slots[1] /* do_create_parent_folders */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__146_9;
}
static void cont__146_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__4 */ = arguments->slots[0];
  // 1289: "path" = path
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__146_10;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* path */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__146_11;
}
static void cont__146_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__5 */ = arguments->slots[0];
  // 1285: raise_error
  // 1286:   "mkdir"
  // 1287:   "MODE" = string("0o" oct(mode))
  // 1288:   "PARENTS" = do_create_parent_folders
  // 1289:   "path" = path
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = string__146_12;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  arguments->slots[2] = frame->slots[6] /* temp__4 */;
  arguments->slots[3] = frame->slots[7] /* temp__5 */;
  result_count = frame->caller_result_count;
  myself = get__raise_error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__146_13(void) {
  allocate_initialized_frame_gc(4, 7);
  // slot allocations:
  // partial_path: 0
  // create_parent_folders: 1
  // mode: 2
  // fail: 3
  frame->slots[1] = myself->closure.frame->slots[5]; /* create_parent_folders */
  frame->slots[2] = myself->closure.frame->slots[2]; /* mode */
  frame->slots[3] = myself->closure.frame->slots[4]; /* fail */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* partial_path */ = create_cell_with_contents(arguments->slots[0]);
  // 1292: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__146_14;
}
static void cont__146_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 1292: before &partial_path '/' -1
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* partial_path */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__before();
  func = myself->type;
  frame->cont = cont__146_15;
}
static void cont__146_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* partial_path */ = arguments->slots[0];
  // 1293: ... partial_path != ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* partial_path */;
  arguments->slots[1] = empty_string;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__146_16;
}
static void cont__146_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 1293: ... partial_path != ""
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__146_17;
}
static void cont__146_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 1293: ... :
  // 1294:   create_parent_folders partial_path
  // 1295:   if clib_mkdir(partial_path mode) < 0 && errno() != EEXIST fail
  frame->slots[6] /* temp__3 */ = create_closure(entry__146_18, 0);
  // 1293: if partial_path != "":
  // 1294:   create_parent_folders partial_path
  // 1295:   if clib_mkdir(partial_path mode) < 0 && errno() != EEXIST fail
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__146_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 1281: PARENTS = false
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__PARENTS();
  arguments->slots[1] = get__false();
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__146_28;
}
static void cont__146_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 1277: extract_options
  // 1278:   options
  // 1279:   MODE = 0o755
  // 1280:   $mode
  // 1281:   PARENTS = false
  // 1282:   $do_create_parent_folders
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* options */;
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  arguments->slots[2] = frame->slots[7] /* temp__2 */;
  result_count = 2;
  myself = get__extract_options();
  func = myself->type;
  frame->cont = cont__146_29;
}
static void cont__146_29(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__3 */ = arguments->slots[0];
  frame->slots[9] /* temp__4 */ = arguments->slots[1];
  // 1280: ... mode
  initialize_future(frame->slots[2] /* mode */, frame->slots[8] /* temp__3 */);
  // 1282: ... do_create_parent_folders
  initialize_future(frame->slots[3] /* do_create_parent_folders */, frame->slots[9] /* temp__4 */);
  // 1297: without_suffix &path '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* path */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__without_suffix();
  func = myself->type;
  frame->cont = cont__146_30;
}
static void cont__146_30(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* path */ = arguments->slots[0];
  // 1298: ... : create_parent_folders path
  frame->slots[6] /* temp__1 */ = create_closure(entry__146_31, 0);
  // 1298: if do_create_parent_folders: create_parent_folders path
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* do_create_parent_folders */;
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__146_32;
}
static void entry__146_31(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // create_parent_folders: 0
  // path: 1
  frame->slots[0] = myself->closure.frame->slots[5]; /* create_parent_folders */
  frame->slots[1] = myself->closure.frame->slots[1]; /* path */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1298: ... create_parent_folders path
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* path */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* create_parent_folders */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__146_32(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1299: ... clib_mkdir(path mode)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* path */;
  arguments->slots[1] = frame->slots[2] /* mode */;
  result_count = 1;
  myself = get__clib_mkdir();
  func = myself->type;
  frame->cont = cont__146_33;
}
static void cont__146_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 1299: ... clib_mkdir(path mode) < 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__2 */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__146_34;
}
static void cont__146_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 1299: ... :
  // 1300:   unless do_create_parent_folders && errno() == EEXIST fail
  frame->slots[8] /* temp__3 */ = create_closure(entry__146_35, 0);
  // 1299: if clib_mkdir(path mode) < 0:
  // 1300:   unless do_create_parent_folders && errno() == EEXIST fail
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__147_5(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // path: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* path */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1308: ... "
  // 1309:   Failed to create directory "@(path)@quot;!@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__147_6;
  arguments->slots[1] = frame->slots[0] /* path */;
  arguments->slots[2] = string__144_7;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__147_7;
}
static void cont__147_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1308: Error "
  // 1309:   Failed to create directory "@(path)@quot;!@
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__147_1(void) {
  allocate_initialized_frame_gc(2, 6);
  // slot allocations:
  // path: 0
  // mode: 1
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  if (argument_count > 2) {
    too_many_arguments_error();
    return;
  }
  switch(argument_count) {
    default: frame->slots[1] /* mode */ = arguments->slots[1];
    case 1:;
  }
  switch(argument_count) {
    case 1: frame->slots[1] /* mode */ = number__0o755;
  }
  // 1307: ... clib_mkdir(path mode)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* path */;
  arguments->slots[1] = frame->slots[1] /* mode */;
  result_count = 1;
  myself = get__clib_mkdir();
  func = myself->type;
  frame->cont = cont__147_2;
}
static void cont__147_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 1307: ... clib_mkdir(path mode) != 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__147_3;
}
static void cont__147_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 1307: ... clib_mkdir(path mode) != 0
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__147_4;
}
static void cont__147_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 1307: ... :
  // 1308:   Error "
  // 1309:     Failed to create directory "@(path)@quot;!@
  frame->slots[5] /* temp__4 */ = create_closure(entry__147_5, 0);
  // 1307: if clib_mkdir(path mode) != 0:
  // 1308:   Error "
  // 1309:     Failed to create directory "@(path)@quot;!@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__148_1(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // pathname: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* pathname */ = create_cell_with_contents(arguments->slots[0]);
  // 1312: ... pathname .has_prefix. '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* pathname */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__148_2;
}
static void cont__148_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1312: ... :
  // 1313:   !pathname string(current_path() "/" pathname)
  frame->slots[2] /* temp__2 */ = create_closure(entry__148_3, 0);
  // 1312: unless pathname .has_prefix. '/':
  // 1313:   !pathname string(current_path() "/" pathname)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__148_7;
}
static void entry__148_3(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // pathname: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* pathname */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1313: ... current_path()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__current_path();
  func = myself->type;
  frame->cont = cont__148_4;
}
static void cont__148_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1313: !pathname string(current_path() "/" pathname)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = string__148_5;
  arguments->slots[2] = ((CELL *)frame->slots[0])->contents /* pathname */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__148_6;
}
static void cont__148_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* pathname */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__148_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1314: ... pathname .has_suffix. '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* pathname */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__has_suffix();
  func = myself->type;
  frame->cont = cont__148_8;
}
static void cont__148_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1314: ... : push &pathname '/'
  frame->slots[2] /* temp__2 */ = create_closure(entry__148_9, 0);
  // 1314: unless pathname .has_suffix. '/': push &pathname '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__148_11;
}
static void entry__148_9(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // pathname: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* pathname */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1314: ... push &pathname '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* pathname */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__148_10;
}
static void cont__148_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* pathname */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__148_11(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1315: ... many("//")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__148_12;
  result_count = 1;
  myself = get__many();
  func = myself->type;
  frame->cont = cont__148_13;
}
static void cont__148_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 1315: ... many("//") = "/"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = string__148_5;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__148_14;
}
static void cont__148_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1315: replace_all &pathname many("//") = "/"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* pathname */;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__replace_all();
  func = myself->type;
  frame->cont = cont__148_15;
}
static void cont__148_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* pathname */ = arguments->slots[0];
  // 1316: ... "/./" = "/"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__148_16;
  arguments->slots[1] = string__148_5;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__148_17;
}
static void cont__148_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1316: replace_all &pathname "/./" = "/"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* pathname */;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__replace_all();
  func = myself->type;
  frame->cont = cont__148_18;
}
static void cont__148_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* pathname */ = arguments->slots[0];
  // 1317: ... : (-> break)
  // 1318:   forever:
  // 1319:     $orig_pathname pathname
  // 1320:     replace_all &pathname "/", some(not_followed_by('/')), '/', "../" = "/"
  // 1321:     if pathname == orig_pathname break
  frame->slots[1] /* temp__1 */ = create_closure(entry__148_19, 0);
  // 1317: do: (-> break)
  // 1318:   forever:
  // 1319:     $orig_pathname pathname
  // 1320:     replace_all &pathname "/", some(not_followed_by('/')), '/', "../" = "/"
  // 1321:     if pathname == orig_pathname break
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 0;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__148_29;
}
static void entry__148_19(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // break: 0
  // pathname: 1
  frame->slots[0] /* break */ = create_continuation();
  frame->slots[1] = myself->closure.frame->slots[0]; /* pathname */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1318: ... :
  // 1319:   $orig_pathname pathname
  // 1320:   replace_all &pathname "/", some(not_followed_by('/')), '/', "../" = "/"
  // 1321:   if pathname == orig_pathname break
  frame->slots[2] /* temp__1 */ = create_closure(entry__148_20, 0);
  // 1318: forever:
  // 1319:   $orig_pathname pathname
  // 1320:   replace_all &pathname "/", some(not_followed_by('/')), '/', "../" = "/"
  // 1321:   if pathname == orig_pathname break
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__forever();
  func = myself->type;
  frame->cont = cont__148_28;
}
static void entry__148_20(void) {
  allocate_initialized_frame_gc(2, 7);
  // slot allocations:
  // pathname: 0
  // break: 1
  // orig_pathname: 2
  frame->slots[0] = myself->closure.frame->slots[1]; /* pathname */
  frame->slots[1] = myself->closure.frame->slots[0]; /* break */
  // _define $orig_pathname pathname
  frame->slots[2] /* orig_pathname */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1319: $orig_pathname pathname
  initialize_maybe_future(frame->slots[2] /* orig_pathname */, ((CELL *)frame->slots[0])->contents /* pathname */);
  // 1320: ... not_followed_by('/')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__47;
  result_count = 1;
  myself = get__not_followed_by();
  func = myself->type;
  frame->cont = cont__148_21;
}
static void cont__148_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__4 */ = arguments->slots[0];
  // 1320: ... some(not_followed_by('/'))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__4 */;
  result_count = 1;
  myself = get__some();
  func = myself->type;
  frame->cont = cont__148_22;
}
static void cont__148_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 1320: ... "/", some(not_followed_by('/')), '/', "../"
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = string__148_5;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  arguments->slots[2] = character__47;
  arguments->slots[3] = string__148_23;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__148_24;
}
static void cont__148_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 1320: ... "/", some(not_followed_by('/')), '/', "../" = "/"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = string__148_5;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__148_25;
}
static void cont__148_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 1320: replace_all &pathname "/", some(not_followed_by('/')), '/', "../" = "/"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* pathname */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__replace_all();
  func = myself->type;
  frame->cont = cont__148_26;
}
static void cont__148_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* pathname */ = arguments->slots[0];
  // 1321: ... pathname == orig_pathname
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* pathname */;
  arguments->slots[1] = frame->slots[2] /* orig_pathname */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__148_27;
}
static void cont__148_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 1321: if pathname == orig_pathname break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* break */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__148_28(void) {
  myself = frame->slots[0] /* break */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__148_29(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1322: ... pathname == "/"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* pathname */;
  arguments->slots[1] = string__148_5;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__148_30;
}
static void cont__148_30(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1322: ... : range &pathname 1 -2
  frame->slots[2] /* temp__2 */ = create_closure(entry__148_31, 0);
  // 1322: unless pathname == "/": range &pathname 1 -2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__148_34;
}
static void entry__148_31(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // pathname: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* pathname */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1322: ... 2
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__148_32;
}
static void cont__148_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1322: ... range &pathname 1 -2
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* pathname */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__148_33;
}
static void cont__148_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* pathname */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__148_34(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1323: -> pathname
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* pathname */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void *collect_directory_handle(DIRECTORY_HANDLE *node) {
  DIRECTORY_HANDLE *new_node = allocate(sizeof(DIRECTORY_HANDLE));
  new_node->type = node->type;
  *(void **)node = ENCODE_ADDRESS(new_node);
  new_node->attributes = collect_attributes(node->attributes);
  new_node->dir = node->dir;
  return new_node;
}

static VTABLE vtable__types__DIR = {
  sizeof(DIRECTORY_HANDLE),
  (COLLECTOR *)&collect_directory_handle,
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
  &func__types__DIR___debug_string
};

static ATTRIBUTES attributes__types__DIR = {
  &vtable__types__DIR,
  {
    &undefined_attributes_level_1, &undefined_attributes_level_2,
    &undefined_attributes_level_3, &undefined_attributes_level_4,
    &undefined_attributes_level_5, &undefined_attributes_level_6,
    &undefined_attributes_level_7
  }
};

static void type__types__DIR(void) {
  {
    runtime_error("Attempt to call a DIR object as a function!");
  }
}
static NODE *create__types__DIR(DIR *dir) {
  NODE *node = allocate(sizeof(DIRECTORY_HANDLE));
  node->type = type__types__DIR;
  node->attributes = &attributes__types__DIR;
  node->directory_handle.dir = dir;
  return node;
}

static long func__types__DIR___debug_string(NODE *node, int indent, int max_depth, char *buf) {
  return debug_print(indent, buf, "<directory>");
}

static DIRENT_DATA *collect_dirent_data(DIRENT_DATA *buf) {
  if (!IS_COLLECTED(buf)) return buf;
  void *new_location = buf->new_location;
  if (new_location) return new_location;
  DIRENT_DATA *new_buf =
    copy(
      buf,
      ALLOCATION_SIZE(offsetof(DIRENT_DATA, d_name)+strlen(buf->d_name)+1));
  new_buf->new_location = NULL;
  buf->new_location = new_buf;
  return new_buf;
}
static void *collect_dirent(DIRENT *node) {
  DIRENT *new_node = allocate(sizeof(DIRENT));
  new_node->type = node->type;
  *(void **)node = ENCODE_ADDRESS(new_node);
  new_node->attributes = collect_attributes(node->attributes);
  new_node->dirent = collect_dirent_data(node->dirent);
  return new_node;
}

static VTABLE vtable__types__dirent = {
  sizeof(DIRENT),
  (COLLECTOR *)&collect_dirent,
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
  &func__types__dirent___debug_string
};

static ATTRIBUTES attributes__types__dirent = {
  &vtable__types__dirent,
  {
    &undefined_attributes_level_1, &undefined_attributes_level_2,
    &undefined_attributes_level_3, &undefined_attributes_level_4,
    &undefined_attributes_level_5, &undefined_attributes_level_6,
    &undefined_attributes_level_7
  }
};

static void type__types__dirent(void) {
  {
    runtime_error("Attempt to call a dirent object as a function!");
  }
}
static NODE *create__types__dirent(DIRENT_DATA *dirent) {
  NODE *node = allocate(sizeof(DIRENT));
  node->type = type__types__dirent;
  node->attributes = &attributes__types__dirent;
  node->dirent.dirent = dirent;
  return node;
}

static long func__types__dirent___debug_string(NODE *node, int indent, int max_depth, char *buf) {
  return debug_print(indent, buf, "<directory entry \"%s\">",
    node->dirent.dirent->d_name);
}
static void entry__157_1(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  NODE *pathname_node = arguments->slots[0];
  char *pathname = to_c_string(pathname_node);
  DIR *dir = opendir(pathname);
  if (!dir) {
    runtime_error("Failed to open directory \"%s\"!", pathname);
  }
  deallocate_memory(pathname);
  NODE *result = create__types__DIR(dir);
  result->attributes = copy(result->attributes, sizeof(ATTRIBUTES));
  update_start_p = node_p;
  set_attribute_value(result->attributes, poly_idx__std__pathname_of, pathname_node);
  {
    NODE *result__node = (NODE *)(result);
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__158_1(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  int err;
  do {
    err = closedir(arguments->slots[0]->directory_handle.dir);
  } while (err == -1 && errno == EINTR);
  if (result_count == 0) {
    if (err != 0) {
    runtime_error("Failed to close directory!");
  }
    {
    argument_count = 0;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  }
  {
    NODE *result__node = (NODE *)(from_int(err));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__159_1(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  NODE *dir_node = arguments->slots[0];
  struct dirent *dirent = readdir(dir_node->directory_handle.dir);
  if (!dirent) {
    arguments = node_p;
    arguments->slots[0] = undefined;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  DIRENT_DATA *data =
    allocate(
      ALLOCATION_SIZE(offsetof(DIRENT_DATA, d_name)+strlen(dirent->d_name)+1));
  data->new_location = NULL;
  data->d_ino = dirent->d_ino;
  data->d_type = dirent->d_type;
  strcpy(data->d_name, dirent->d_name);
  NODE *pathname_node = get_attribute(dir_node, poly_idx__std__pathname_of);
  NODE *result = create__types__dirent(data);
  result->attributes = copy(result->attributes, sizeof(ATTRIBUTES));
  update_start_p = node_p;
  set_attribute(
    result->attributes, poly_idx__std__pathname_of, pathname_node);
  {
    NODE *result__node = (NODE *)(result);
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__160_1(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }

  {
    NODE *result__node = (NODE *)(from_c_string(arguments->slots[0]->dirent.dirent->d_name));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__161_1(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }

  {
    NODE *result__node = (NODE *)(from_long(arguments->slots[0]->dirent.dirent->d_ino));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__162_1(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }

  {
    NODE *result__node = (NODE *)(from_int(arguments->slots[0]->dirent.dirent->d_type));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__163_1(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // self: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 1476: ... pathname_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__pathname_of();
  func = myself->type;
  frame->cont = cont__163_2;
}
static void cont__163_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 1476: ... filename_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__filename_of();
  func = myself->type;
  frame->cont = cont__163_3;
}
static void cont__163_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 1476: ... string(pathname_of(self) "/" filename_of(self))
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = string__148_5;
  arguments->slots[2] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__163_4;
}
static void cont__163_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1476: -> string(pathname_of(self) "/" filename_of(self))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__164_1(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // self: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 1478: ... file_type_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__file_type_of();
  func = myself->type;
  frame->cont = cont__164_2;
}
static void cont__164_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 1478: ... file_type_of(self) == std::DIRECTORY
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = var.std__DIRECTORY;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__164_3;
}
static void cont__164_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1478: ... -> file_type_of(self) == std::DIRECTORY
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__165_1(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // self: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 1481: ... file_type_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__file_type_of();
  func = myself->type;
  frame->cont = cont__165_2;
}
static void cont__165_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 1481: ... file_type_of(self) == std::REGULAR_FILE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = var.std__REGULAR_FILE;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__165_3;
}
static void cont__165_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1481: -> file_type_of(self) == std::REGULAR_FILE
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__166_1(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // self: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 1483: ... file_type_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__file_type_of();
  func = myself->type;
  frame->cont = cont__166_2;
}
static void cont__166_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 1483: ... file_type_of(self) == std::LINK
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = var.std__LINK;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__166_3;
}
static void cont__166_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1483: ... -> file_type_of(self) == std::LINK
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__167_1(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(2, 6);
  // slot allocations:
  // options: 0
  // pathname: 1
  // do_sort: 2
  // entries: 3
  // dir: 4
  frame->slots[2] /* do_sort */ = create_future();
  frame->slots[3] /* entries */ = create_cell();
  frame->slots[4] /* dir */ = create_future();
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  frame->slots[1] /* pathname */ = arguments->slots[argument_count-1];
  frame->slots[0] /* options */ = from_arguments(0, argument_count-1);
  // 1486: ... SORT = false
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__SORT();
  arguments->slots[1] = get__false();
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__167_2;
}
static void cont__167_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 1486: extract_options options SORT = false $do_sort
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* options */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 1;
  myself = get__extract_options();
  func = myself->type;
  frame->cont = cont__167_3;
}
static void cont__167_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* do_sort */, arguments->slots[0]);
  // 1487: $$entries list()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__167_4;
}
static void cont__167_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* entries */ = arguments->slots[0];
  // 1488: ... fullname(pathname)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* pathname */;
  result_count = 1;
  myself = get__fullname();
  func = myself->type;
  frame->cont = cont__167_5;
}
static void cont__167_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 1488: $dir std::opendir(fullname(pathname))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  result_count = 1;
  myself = var.std__opendir;
  func = myself->type;
  frame->cont = cont__167_6;
}
static void cont__167_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* dir */, arguments->slots[0]);
  // 1489: ... : (-> break)
  // 1490:   forever:
  // 1491:     $entry get(dir)
  // 1492:     unless entry.is_defined break
  // 1493:     case
  // 1494:       filename_of(entry)
  // 1495:       ".", "..":
  // 1496:         pass
  // 1497:       :
  // 1498:         push &entries entry
  frame->slots[5] /* temp__1 */ = create_closure(entry__167_7, 0);
  // 1489: do: (-> break)
  // 1490:   forever:
  // 1491:     $entry get(dir)
  // 1492:     unless entry.is_defined break
  // 1493:     case
  // 1494:       filename_of(entry)
  // 1495:       ".", "..":
  // 1496:         pass
  // 1497:       :
  // 1498:         push &entries entry
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  result_count = 0;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__167_20;
}
static void entry__167_7(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // break: 0
  // dir: 1
  // entries: 2
  frame->slots[0] /* break */ = create_continuation();
  frame->slots[1] = myself->closure.frame->slots[4]; /* dir */
  frame->slots[2] = myself->closure.frame->slots[3]; /* entries */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1490: ... :
  // 1491:   $entry get(dir)
  // 1492:   unless entry.is_defined break
  // 1493:   case
  // 1494:     filename_of(entry)
  // 1495:     ".", "..":
  // 1496:       pass
  // 1497:     :
  // 1498:       push &entries entry
  frame->slots[3] /* temp__1 */ = create_closure(entry__167_8, 0);
  // 1490: forever:
  // 1491:   $entry get(dir)
  // 1492:   unless entry.is_defined break
  // 1493:   case
  // 1494:     filename_of(entry)
  // 1495:     ".", "..":
  // 1496:       pass
  // 1497:     :
  // 1498:       push &entries entry
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__forever();
  func = myself->type;
  frame->cont = cont__167_19;
}
static void entry__167_16(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // entries: 0
  // entry: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* entries */
  frame->slots[1] = myself->closure.frame->slots[3]; /* entry */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1498: push &entries entry
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* entries */;
  arguments->slots[1] = frame->slots[1] /* entry */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__167_17;
}
static void cont__167_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* entries */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__167_18(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1496: pass
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = get__pass();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__167_8(void) {
  allocate_initialized_frame_gc(3, 7);
  // slot allocations:
  // dir: 0
  // break: 1
  // entries: 2
  // entry: 3
  frame->slots[0] = myself->closure.frame->slots[1]; /* dir */
  frame->slots[1] = myself->closure.frame->slots[0]; /* break */
  frame->slots[2] = myself->closure.frame->slots[2]; /* entries */
  frame->slots[3] /* entry */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1491: $entry get(dir)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* dir */;
  result_count = 1;
  myself = get__get();
  func = myself->type;
  frame->cont = cont__167_9;
}
static void cont__167_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* entry */, arguments->slots[0]);
  // 1492: ... entry.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* entry */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__167_10;
}
static void cont__167_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 1492: unless entry.is_defined break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* break */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__167_11;
}
static void cont__167_11(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1494: filename_of(entry)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* entry */;
  result_count = 1;
  myself = get__filename_of();
  func = myself->type;
  frame->cont = cont__167_12;
}
static void cont__167_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 1495: ".", ".."
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__167_13;
  arguments->slots[1] = string__167_14;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__167_15;
}
static void cont__167_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 1497: :
  // 1498:   push &entries entry
  frame->slots[6] /* temp__3 */ = create_closure(entry__167_16, 0);
  // 1493: case
  // 1494:   filename_of(entry)
  // 1495:   ".", "..":
  // 1496:     pass
  // 1497:   :
  // 1498:     push &entries entry
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  arguments->slots[2] = func__167_18;
  arguments->slots[3] = frame->slots[6] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__167_19(void) {
  myself = frame->slots[0] /* break */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__167_20(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1499: close dir
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* dir */;
  result_count = 0;
  myself = get__close();
  func = myself->type;
  frame->cont = cont__167_21;
}
static void cont__167_21(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1500: ... :
  // 1501:   sort &entries: (left right) -> filename_of(left) < filename_of(right)
  frame->slots[5] /* temp__1 */ = create_closure(entry__167_22, 0);
  // 1500: if do_sort:
  // 1501:   sort &entries: (left right) -> filename_of(left) < filename_of(right)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* do_sort */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__167_28;
}
static void entry__167_22(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // entries: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* entries */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1501: sort &entries: (left right) -> filename_of(left) < filename_of(right)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* entries */;
  arguments->slots[1] = func__167_23;
  result_count = 1;
  myself = get__sort();
  func = myself->type;
  frame->cont = cont__167_27;
}
static void entry__167_23(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // left: 0
  // right: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 1501: ... filename_of(left)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* left */;
  result_count = 1;
  myself = get__filename_of();
  func = myself->type;
  frame->cont = cont__167_24;
}
static void cont__167_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 1501: ... filename_of(right)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* right */;
  result_count = 1;
  myself = get__filename_of();
  func = myself->type;
  frame->cont = cont__167_25;
}
static void cont__167_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 1501: ... filename_of(left) < filename_of(right)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__167_26;
}
static void cont__167_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 1501: ... -> filename_of(left) < filename_of(right)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__167_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* entries */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__167_28(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1502: -> entries
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* entries */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}

static ADDRINFO_DATA *collect_addrinfo_data(ADDRINFO_DATA *buf) {
  if (!IS_COLLECTED(buf)) return buf;
  void *new_location = buf->new_location;
  if (new_location) return new_location;
  ADDRINFO_DATA *new_buf = copy(buf, sizeof(ADDRINFO_DATA));
  new_buf->new_location = NULL;
  buf->new_location = new_buf;
  return new_buf;
}
static void *collect_addrinfo(ADDRINFO *node) {
  ADDRINFO *new_node = allocate(sizeof(ADDRINFO));
  new_node->type = node->type;
  *(void **)node = ENCODE_ADDRESS(new_node);
  new_node->attributes = collect_attributes(node->attributes);
  new_node->data = collect_addrinfo_data(node->data);
  return new_node;
}

static VTABLE vtable__types__addrinfo = {
  sizeof(ADDRINFO),
  (COLLECTOR *)&collect_addrinfo,
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
  &func__types__addrinfo___debug_string
};

static ATTRIBUTES attributes__types__addrinfo = {
  &vtable__types__addrinfo,
  {
    &undefined_attributes_level_1, &undefined_attributes_level_2,
    &undefined_attributes_level_3, &undefined_attributes_level_4,
    &undefined_attributes_level_5, &undefined_attributes_level_6,
    &undefined_attributes_level_7
  }
};

static void type__types__addrinfo(void) {
  {
    runtime_error("Attempt to call an addrinfo object as a function!");
  }
}
static NODE *create__types__addrinfo(ADDRINFO_DATA *data) {
  NODE *node = allocate(sizeof(ADDRINFO));
  node->type = type__types__addrinfo;
  node->attributes = &attributes__types__addrinfo;
  node->addrinfo.data = data;
  return node;
}

static long func__types__addrinfo___debug_string(NODE *node, int indent, int max_depth, char *buf) {
  char description[64];
  ADDRINFO_DATA *data = node->addrinfo.data;
  void *ptr;
  switch (data->family) {
    case AF_INET:
      ptr = &((struct sockaddr_in *)&data->sockaddr)->sin_addr;
      break;
    case AF_INET6:
      ptr = &((struct sockaddr_in6 *)&data->sockaddr)->sin6_addr;
      break;
    default:
      ptr = NULL;
    }
  if (
    ptr &&
    inet_ntop(data->family, ptr, description, sizeof(description))
  ) {
    return debug_print(indent, buf, "<addrinfo %s>", description);
  } else {
    return debug_print(indent, buf, "<addrinfo>");
  }
}
static void entry__175_1(void) {
  // get all network addresses

  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  struct addrinfo *first;
  char *name = to_c_string(arguments->slots[0]);
  struct addrinfo hints;
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_flags = 0;
  hints.ai_family = AF_INET; // only IPv4
  hints.ai_socktype = SOCK_STREAM; // only TCP
  hints.ai_protocol = 0;
  getaddrinfo(name, NULL, &hints, &first);
  deallocate_memory(name);
  struct addrinfo *info = first;
  int len = 0;
  while (info) {
    ++len;
    info = info->ai_next;
  }
  LIST_DATA *list_data = allocate_large(sizeof(LIST_DATA)+len*sizeof(NODE *));
  list_data->size = len;
  list_data->length = len;
  list_data->items = (void *)(list_data+1);
  len = 0;
  info = first;
  while (info) {
    ADDRINFO_DATA *data = allocate(ALLOCATION_SIZE(sizeof(ADDRINFO_DATA)));
    data->family = info->ai_family;
    data->type = info->ai_socktype;
    data->protocol = info->ai_protocol;
    data->sockaddr = *info->ai_addr;
    list_data->items[len] = create__types__addrinfo(data);
    ++len;
    info = info->ai_next;
  }
  freeaddrinfo(first);
  {
    NODE *result__node = (NODE *)(create__types__list(len, list_data));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__176_1(void) {
  // get one network address

  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  struct addrinfo *first;
  char *name = to_c_string(arguments->slots[0]);
  struct addrinfo hints;
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_flags = 0;
  hints.ai_family = AF_INET; // only IPv4
  hints.ai_socktype = SOCK_STREAM; // only TCP
  hints.ai_protocol = 0;
  getaddrinfo(name, NULL, &hints, &first);
  deallocate_memory(name);
  NODE *node;
  if (first) {
    ADDRINFO_DATA *data = allocate(ALLOCATION_SIZE(sizeof(ADDRINFO_DATA)));
    data->family = first->ai_family;
    data->type = first->ai_socktype;
    data->protocol = first->ai_protocol;
    data->sockaddr = *first->ai_addr;
    node = create__types__addrinfo(data);
  } else {
    node = undefined;
  }
  freeaddrinfo(first);
  {
    NODE *result__node = (NODE *)(node);
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__177_1(void) {
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  ADDRINFO_DATA *data = arguments->slots[0]->addrinfo.data;
  int port = to_int(arguments->slots[1]);
  int sd = socket(data->family, data->type, data->protocol);
  if (sd == -1) {
    arguments = node_p;
    arguments->slots[0] = undefined;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  ((struct sockaddr_in *)&data->sockaddr)->sin_port = htons(port);
  if (connect(sd, &data->sockaddr, sizeof(data->sockaddr)) == 0) {
    {
    NODE *result__node = (NODE *)(create__types__file_descriptor(sd));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else {
    close(sd);
    {
    arguments = node_p;
    arguments->slots[0] = undefined;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  }
}
static void entry__178_1(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // uri: 0
  // port: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 1680: ... get_network_address(uri)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* uri */;
  result_count = 1;
  myself = get__get_network_address();
  func = myself->type;
  frame->cont = cont__178_2;
}
static void cont__178_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 1680: ... connect get_network_address(uri) port
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* port */;
  result_count = frame->caller_result_count;
  myself = get__connect();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__179_1(void) {
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  ADDRINFO_DATA *data = arguments->slots[0]->addrinfo.data;
  int port = to_int(arguments->slots[1]);
  int sd = socket(data->family, data->type, data->protocol);
  if (sd == -1) {
    arguments = node_p;
    arguments->slots[0] = undefined;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  int enable = 1;
  setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int));
  struct sockaddr_in sockaddr;
  memset(&sockaddr, 0, sizeof sockaddr);
  sockaddr.sin_family = data->family;
  sockaddr.sin_port = htons(port);
  sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  if (bind(sd, (struct sockaddr *)&sockaddr, sizeof(sockaddr)) == -1) {
    close(sd);
    {
    arguments = node_p;
    arguments->slots[0] = undefined;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  }
  if (listen(sd, 10) == -1) {
    close(sd);
    {
    arguments = node_p;
    arguments->slots[0] = undefined;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  }
  {
    NODE *result__node = (NODE *)(create__types__file_descriptor(sd));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__180_1(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // uri: 0
  // port: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 1707: ... get_network_address(uri)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* uri */;
  result_count = 1;
  myself = get__get_network_address();
  func = myself->type;
  frame->cont = cont__180_2;
}
static void cont__180_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 1707: ... listen get_network_address(uri) port
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* port */;
  result_count = frame->caller_result_count;
  myself = get__listen();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__181_1(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  int fd = arguments->slots[0]->file_descriptor.fd;
  int new_fd = accept(fd, NULL, NULL);
  if (new_fd == -1) {
    {
    arguments = node_p;
    arguments->slots[0] = undefined;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  } else {
    {
    NODE *result__node = (NODE *)(create__types__file_descriptor(new_fd));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  }
}
static void entry__182_1(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // args: 0
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 1721: ... string(args*)
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[0] /* args */);
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__182_2;
}
static void cont__182_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 1721: ... string(args*).to_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__to_utf8();
  func = myself->type;
  frame->cont = cont__182_3;
}
static void cont__182_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1721: ... write_to STDOUT_FILENO string(args*).to_utf8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__STDOUT_FILENO();
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write_to();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__183_1(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // args: 0
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 1723: ... write args* "@nl;"
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[0] /* args */);
  arguments->slots[argument_count++] = string__81_6;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__184_1(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // args: 0
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 1725: ... string(args*)
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[0] /* args */);
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__184_2;
}
static void cont__184_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 1725: ... string(args*).to_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__to_utf8();
  func = myself->type;
  frame->cont = cont__184_3;
}
static void cont__184_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1725: ... atomic_write_to STDERR_FILENO string(args*).to_utf8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__STDERR_FILENO();
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__atomic_write_to();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__185_1(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // args: 0
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 1727: ... ewrite args* "@nl;"
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[0] /* args */);
  arguments->slots[argument_count++] = string__81_6;
  result_count = frame->caller_result_count;
  myself = get__ewrite();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__186_1(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // n: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 1729: ... read_from STDIN_FILENO n
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__STDIN_FILENO();
  arguments->slots[1] = frame->slots[0] /* n */;
  result_count = frame->caller_result_count;
  myself = get__read_from();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__187_1(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // return: 0
  // buf: 1
  frame->slots[0] /* return */ = create_continuation();
  frame->slots[1] /* buf */ = create_cell();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1732: $$buf ""
  ((CELL *)frame->slots[1])->contents /* buf */ = empty_string;
  // 1733: ... :
  // 1734:   read $chr 1
  // 1735:   if chr == "@nl;" || chr == "": return buf
  // 1736:   append &buf chr
  frame->slots[2] /* temp__1 */ = create_closure(entry__187_2, 0);
  // 1733: forever:
  // 1734:   read $chr 1
  // 1735:   if chr == "@nl;" || chr == "": return buf
  // 1736:   append &buf chr
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__forever();
  func = myself->type;
  frame->cont = cont__187_11;
}
static void entry__187_2(void) {
  allocate_initialized_frame_gc(2, 7);
  // slot allocations:
  // return: 0
  // buf: 1
  // chr: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* return */
  frame->slots[1] = myself->closure.frame->slots[1]; /* buf */
  frame->slots[2] /* chr */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1734: read $chr 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__read();
  func = myself->type;
  frame->cont = cont__187_3;
}
static void cont__187_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* chr */, arguments->slots[0]);
  // 1735: ... chr == "@nl;"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* chr */;
  arguments->slots[1] = string__81_6;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__187_4;
}
static void cont__187_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 1735: ... chr == ""
  frame->slots[5] /* temp__3 */ = create_closure(entry__187_5, 0);
  // 1735: ... chr == "@nl;" || chr == ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__187_7;
}
static void entry__187_5(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1735: ... chr == ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  arguments->slots[1] = empty_string;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__187_6;
}
static void cont__187_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1735: ... chr == ""
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__187_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 1735: ... : return buf
  frame->slots[6] /* temp__4 */ = create_closure(entry__187_8, 0);
  // 1735: if chr == "@nl;" || chr == "": return buf
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__187_9;
}
static void entry__187_8(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // return: 0
  // buf: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* return */
  frame->slots[1] = myself->closure.frame->slots[1]; /* buf */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1735: ... return buf
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* buf */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__187_9(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1736: append &buf chr
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* buf */;
  arguments->slots[1] = frame->slots[2] /* chr */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__187_10;
}
static void cont__187_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* buf */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__187_11(void) {
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__188_9(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // buf: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* buf */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1741: ... -> buf
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* buf */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__188_10(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // filename: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1742: ... "
  // 1743:   Load error ("@(filename)@quot;)!@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__188_11;
  arguments->slots[1] = frame->slots[0] /* filename */;
  arguments->slots[2] = string__188_12;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__188_13;
}
static void cont__188_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1742: raise "
  // 1743:   Load error ("@(filename)@quot;)!@
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__raise();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__188_4(void) {
  allocate_initialized_frame_gc(1, 6);
  // slot allocations:
  // filename: 0
  // buf: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* filename */
  frame->slots[1] /* buf */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1741: ... wget($buf "-q" "-O" "-" filename)
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = string__188_5;
  arguments->slots[1] = string__188_6;
  arguments->slots[2] = string__188_7;
  arguments->slots[3] = frame->slots[0] /* filename */;
  result_count = 2;
  myself = var._wget;
  func = myself->type;
  frame->cont = cont__188_8;
}
static void cont__188_8(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  frame->slots[2] /* temp__1 */ = arguments->slots[1];
  // 1741: ... buf
  initialize_future(frame->slots[1] /* buf */, frame->slots[3] /* temp__2 */);
  // 1741: ... -> buf
  frame->slots[4] /* temp__3 */ = create_closure(entry__188_9, 0);
  // 1741: ... :
  // 1742:   raise "
  // 1743:     Load error ("@(filename)@quot;)!@
  frame->slots[5] /* temp__4 */ = create_closure(entry__188_10, 0);
  // 1741: if wget($buf "-q" "-O" "-" filename) (-> buf):
  // 1742:   raise "
  // 1743:     Load error ("@(filename)@quot;)!@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  arguments->slots[2] = frame->slots[5] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__188_14(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // filename: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1745: load_file filename
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* filename */;
  result_count = frame->caller_result_count;
  myself = get__load_file();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__188_1(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // filename: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 1740: filename .has_prefix. "http://"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* filename */;
  arguments->slots[1] = string__188_2;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__188_3;
}
static void cont__188_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1740: ... :
  // 1741:   if wget($buf "-q" "-O" "-" filename) (-> buf):
  // 1742:     raise "
  // 1743:       Load error ("@(filename)@quot;)!@
  frame->slots[2] /* temp__2 */ = create_closure(entry__188_4, 0);
  // 1744: :
  // 1745:   load_file filename
  frame->slots[3] /* temp__3 */ = create_closure(entry__188_14, 0);
  // 1739: if
  // 1740:   filename .has_prefix. "http://":
  // 1741:     if wget($buf "-q" "-O" "-" filename) (-> buf):
  // 1742:       raise "
  // 1743:         Load error ("@(filename)@quot;)!@
  // 1744:   :
  // 1745:     load_file filename
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  arguments->slots[2] = frame->slots[3] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__189_1(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // options: 0
  // filename: 1
  // data: 2
  // do_create_directory: 3
  frame->slots[3] /* do_create_directory */ = create_future();
  if (argument_count < 2) {
    too_few_arguments_error();
    return;
  }
  frame->slots[2] /* data */ = arguments->slots[argument_count-1];
  frame->slots[1] /* filename */ = arguments->slots[argument_count-2];
  frame->slots[0] /* options */ = from_arguments(0, argument_count-2);
  // 1748: ... PARENTS = false
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__PARENTS();
  arguments->slots[1] = get__false();
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__189_2;
}
static void cont__189_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 1748: extract_options options PARENTS = false $do_create_directory
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* options */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__extract_options();
  func = myself->type;
  frame->cont = cont__189_3;
}
static void cont__189_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* do_create_directory */, arguments->slots[0]);
  // 1749: ... :
  // 1750:   $path before(filename '/' -1)
  // 1751:   if path != "": mkdir --PARENTS path
  frame->slots[4] /* temp__1 */ = create_closure(entry__189_4, 0);
  // 1749: if do_create_directory:
  // 1750:   $path before(filename '/' -1)
  // 1751:   if path != "": mkdir --PARENTS path
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* do_create_directory */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__189_11;
}
static void entry__189_9(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // path: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* path */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1751: ... --PARENTS
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__PARENTS();
  arguments->slots[1] = get__std__true();
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__189_10;
}
static void cont__189_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1751: ... mkdir --PARENTS path
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[0] /* path */;
  result_count = frame->caller_result_count;
  myself = get__mkdir();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__189_4(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // filename: 0
  // path: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* filename */
  frame->slots[1] /* path */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1750: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__189_5;
}
static void cont__189_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 1750: $path before(filename '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* filename */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__before();
  func = myself->type;
  frame->cont = cont__189_6;
}
static void cont__189_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* path */, arguments->slots[0]);
  // 1751: ... path != ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* path */;
  arguments->slots[1] = empty_string;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__189_7;
}
static void cont__189_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 1751: ... path != ""
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__189_8;
}
static void cont__189_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 1751: ... : mkdir --PARENTS path
  frame->slots[4] /* temp__3 */ = create_closure(entry__189_9, 0);
  // 1751: if path != "": mkdir --PARENTS path
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__189_11(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1752: ... data.to_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* data */;
  result_count = 1;
  myself = get__to_string();
  func = myself->type;
  frame->cont = cont__189_12;
}
static void cont__189_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 1752: save_file filename data.to_string
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* filename */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__save_file();
  func = myself->type;
  frame = frame->caller_frame;
}
EXPORT void collect__basic__io(void) {
  var.std__MODE = collect_node(var.std__MODE);
  unique__1_1 = collect_node(unique__1_1);
  var.std__PARENTS = collect_node(var.std__PARENTS);
  unique__2_1 = collect_node(unique__2_1);
  var._wget = collect_node(var._wget);
  var.std__ioctl = collect_node(var.std__ioctl);
  var.std__get_terminal_size = collect_node(var.std__get_terminal_size);
  var.std__device_of = collect_node(var.std__device_of);
  var.std__inode_of = collect_node(var.std__inode_of);
  var.std__mode_of = collect_node(var.std__mode_of);
  var.std__link_count_of = collect_node(var.std__link_count_of);
  var.std__user_id_of = collect_node(var.std__user_id_of);
  var.std__group_id_of = collect_node(var.std__group_id_of);
  var.std__size_of = collect_node(var.std__size_of);
  var.std__block_size_of = collect_node(var.std__block_size_of);
  var.std__sector_count_of = collect_node(var.std__sector_count_of);
  var.std__access_time_of = collect_node(var.std__access_time_of);
  var.std__modification_time_of = collect_node(var.std__modification_time_of);
  var.std__status_change_time_of = collect_node(var.std__status_change_time_of);
  var.std__creation_time_of = collect_node(var.std__creation_time_of);
  var.std__filename_of = collect_node(var.std__filename_of);
  var.std__file_type_of = collect_node(var.std__file_type_of);
  var.std__pathname_of = collect_node(var.std__pathname_of);
  var.std__fullname_of = collect_node(var.std__fullname_of);
  var.std__is_a_directory = collect_node(var.std__is_a_directory);
  var.std__is_a_regular_file = collect_node(var.std__is_a_regular_file);
  var.std__is_a_link = collect_node(var.std__is_a_link);
  var.std__listen = collect_node(var.std__listen);
  var.std__accept = collect_node(var.std__accept);
  var.std__connect = collect_node(var.std__connect);
  var.std__O_RDONLY = collect_node(var.std__O_RDONLY);
  var.std__O_WRONLY = collect_node(var.std__O_WRONLY);
  var.std__O_RDWR = collect_node(var.std__O_RDWR);
  var.std__O_CREAT = collect_node(var.std__O_CREAT);
  var.std__O_EXCL = collect_node(var.std__O_EXCL);
  var.std__O_NOCTTY = collect_node(var.std__O_NOCTTY);
  var.std__O_TRUNC = collect_node(var.std__O_TRUNC);
  var.std__O_APPEND = collect_node(var.std__O_APPEND);
  var.std__O_NONBLOCK = collect_node(var.std__O_NONBLOCK);
  var.std__O_ASYNC = collect_node(var.std__O_ASYNC);
  var.std__UNKNOWN = collect_node(var.std__UNKNOWN);
  var.std__FIFO = collect_node(var.std__FIFO);
  var.std__CHARACTER_DEVICE = collect_node(var.std__CHARACTER_DEVICE);
  var.std__DIRECTORY = collect_node(var.std__DIRECTORY);
  var.std__BLOCK_DEVICE = collect_node(var.std__BLOCK_DEVICE);
  var.std__REGULAR_FILE = collect_node(var.std__REGULAR_FILE);
  var.std__LINK = collect_node(var.std__LINK);
  var.std__SOCKET = collect_node(var.std__SOCKET);
  var.std__EPERM = collect_node(var.std__EPERM);
  var.std__ENOENT = collect_node(var.std__ENOENT);
  var.std__ESRCH = collect_node(var.std__ESRCH);
  var.std__EINTR = collect_node(var.std__EINTR);
  var.std__EIO = collect_node(var.std__EIO);
  var.std__ENXIO = collect_node(var.std__ENXIO);
  var.std__E2BIG = collect_node(var.std__E2BIG);
  var.std__ENOEXEC = collect_node(var.std__ENOEXEC);
  var.std__EBADF = collect_node(var.std__EBADF);
  var.std__ECHILD = collect_node(var.std__ECHILD);
  var.std__EAGAIN = collect_node(var.std__EAGAIN);
  var.std__ENOMEM = collect_node(var.std__ENOMEM);
  var.std__EACCES = collect_node(var.std__EACCES);
  var.std__EFAULT = collect_node(var.std__EFAULT);
  var.std__ENOTBLK = collect_node(var.std__ENOTBLK);
  var.std__EBUSY = collect_node(var.std__EBUSY);
  var.std__EEXIST = collect_node(var.std__EEXIST);
  var.std__EXDEV = collect_node(var.std__EXDEV);
  var.std__ENODEV = collect_node(var.std__ENODEV);
  var.std__ENOTDIR = collect_node(var.std__ENOTDIR);
  var.std__EISDIR = collect_node(var.std__EISDIR);
  var.std__EINVAL = collect_node(var.std__EINVAL);
  var.std__ENFILE = collect_node(var.std__ENFILE);
  var.std__EMFILE = collect_node(var.std__EMFILE);
  var.std__ENOTTY = collect_node(var.std__ENOTTY);
  var.std__ETXTBSY = collect_node(var.std__ETXTBSY);
  var.std__EFBIG = collect_node(var.std__EFBIG);
  var.std__ENOSPC = collect_node(var.std__ENOSPC);
  var.std__ESPIPE = collect_node(var.std__ESPIPE);
  var.std__EROFS = collect_node(var.std__EROFS);
  var.std__EMLINK = collect_node(var.std__EMLINK);
  var.std__EPIPE = collect_node(var.std__EPIPE);
  var.std__EDOM = collect_node(var.std__EDOM);
  var.std__ERANGE = collect_node(var.std__ERANGE);
  var.std__raise_error = collect_node(var.std__raise_error);
  var.std__check_error = collect_node(var.std__check_error);
  var.std__errno = collect_node(var.std__errno);
  var.std__strerror = collect_node(var.std__strerror);
  var.types__stat = collect_node(var.types__stat);
  collect_static_attributes(&attributes__types__stat);
  var.std__stat = collect_node(var.std__stat);
  var.std__file_exists = collect_node(var.std__file_exists);
  var.types__file_descriptor = collect_node(var.types__file_descriptor);
  collect_static_attributes(&attributes__types__file_descriptor);
  var.std__STDIN_FILENO = collect_node(var.std__STDIN_FILENO);
  var.std__STDOUT_FILENO = collect_node(var.std__STDOUT_FILENO);
  var.std__STDERR_FILENO = collect_node(var.std__STDERR_FILENO);
  var.std__create_file_descriptor = collect_node(var.std__create_file_descriptor);
  var._posix_open = collect_node(var._posix_open);
  var.std__open_file_for_reading = collect_node(var.std__open_file_for_reading);
  var.std__open_file_for_writing = collect_node(var.std__open_file_for_writing);
  var.std__open_file_for_reading_and_writing = collect_node(var.std__open_file_for_reading_and_writing);
  var.std__create_file = collect_node(var.std__create_file);
  var.std__atomic_write_to = collect_node(var.std__atomic_write_to);
  var.std__load_file = collect_node(var.std__load_file);
  var.std__save_file = collect_node(var.std__save_file);
  var._ioctl_value = collect_node(var._ioctl_value);
  var._posix_unlink = collect_node(var._posix_unlink);
  var.std__delete_file = collect_node(var.std__delete_file);
  var._wait_for_io_ready = collect_node(var._wait_for_io_ready);
  var.std__get_pid = collect_node(var.std__get_pid);
  var.std__wait_pid = collect_node(var.std__wait_pid);
  var.std__wait_for_io = collect_node(var.std__wait_for_io);
  var.std__current_path = collect_node(var.std__current_path);
  var.std__chdir = collect_node(var.std__chdir);
  var.std__change_directory = collect_node(var.std__change_directory);
  var.std__clib_mkdir = collect_node(var.std__clib_mkdir);
  var.std__mkdir = collect_node(var.std__mkdir);
  var.std__create_directory = collect_node(var.std__create_directory);
  var.std__fullname = collect_node(var.std__fullname);
  var.types__DIR = collect_node(var.types__DIR);
  collect_static_attributes(&attributes__types__DIR);
  var.types__dirent = collect_node(var.types__dirent);
  collect_static_attributes(&attributes__types__dirent);
  var.std__opendir = collect_node(var.std__opendir);
  var.std__directory = collect_node(var.std__directory);
  var.types__addrinfo = collect_node(var.types__addrinfo);
  collect_static_attributes(&attributes__types__addrinfo);
  var.std__get_network_addresses = collect_node(var.std__get_network_addresses);
  var.std__get_network_address = collect_node(var.std__get_network_address);
  var.std__writeln = collect_node(var.std__writeln);
  var.std__ewriteln = collect_node(var.std__ewriteln);
  var.std__readln = collect_node(var.std__readln);
  var.std__load = collect_node(var.std__load);
  var.std__save = collect_node(var.std__save);
}

static int already_run_phase_1 = false;

EXPORT void phase_1__basic__io(void) {
  if (already_run_phase_1) return;
  already_run_phase_1 = true;
  register_module_info(&module_info);
  define_polymorphic_function("std", "ioctl", get__std__ioctl, &poly_idx__std__ioctl, &var.std__ioctl);
  define_polymorphic_function("std", "get_terminal_size", get__std__get_terminal_size, &poly_idx__std__get_terminal_size, &var.std__get_terminal_size);
  define_polymorphic_function_with_setter("std", "device_of", get__std__device_of, &poly_idx__std__device_of, &var.std__device_of);
  define_polymorphic_function_with_setter("std", "inode_of", get__std__inode_of, &poly_idx__std__inode_of, &var.std__inode_of);
  define_polymorphic_function_with_setter("std", "mode_of", get__std__mode_of, &poly_idx__std__mode_of, &var.std__mode_of);
  define_polymorphic_function_with_setter("std", "link_count_of", get__std__link_count_of, &poly_idx__std__link_count_of, &var.std__link_count_of);
  define_polymorphic_function_with_setter("std", "user_id_of", get__std__user_id_of, &poly_idx__std__user_id_of, &var.std__user_id_of);
  define_polymorphic_function_with_setter("std", "group_id_of", get__std__group_id_of, &poly_idx__std__group_id_of, &var.std__group_id_of);
  define_polymorphic_function_with_setter("std", "size_of", get__std__size_of, &poly_idx__std__size_of, &var.std__size_of);
  define_polymorphic_function_with_setter("std", "block_size_of", get__std__block_size_of, &poly_idx__std__block_size_of, &var.std__block_size_of);
  define_polymorphic_function_with_setter("std", "sector_count_of", get__std__sector_count_of, &poly_idx__std__sector_count_of, &var.std__sector_count_of);
  define_polymorphic_function_with_setter("std", "access_time_of", get__std__access_time_of, &poly_idx__std__access_time_of, &var.std__access_time_of);
  define_polymorphic_function_with_setter("std", "modification_time_of", get__std__modification_time_of, &poly_idx__std__modification_time_of, &var.std__modification_time_of);
  define_polymorphic_function_with_setter("std", "status_change_time_of", get__std__status_change_time_of, &poly_idx__std__status_change_time_of, &var.std__status_change_time_of);
  define_polymorphic_function_with_setter("std", "creation_time_of", get__std__creation_time_of, &poly_idx__std__creation_time_of, &var.std__creation_time_of);
  define_polymorphic_function_with_setter("std", "filename_of", get__std__filename_of, &poly_idx__std__filename_of, &var.std__filename_of);
  define_polymorphic_function_with_setter("std", "file_type_of", get__std__file_type_of, &poly_idx__std__file_type_of, &var.std__file_type_of);
  define_polymorphic_function_with_setter("std", "pathname_of", get__std__pathname_of, &poly_idx__std__pathname_of, &var.std__pathname_of);
  define_polymorphic_function_with_setter("std", "fullname_of", get__std__fullname_of, &poly_idx__std__fullname_of, &var.std__fullname_of);
  define_polymorphic_function("std", "is_a_directory", get__std__is_a_directory, &poly_idx__std__is_a_directory, &var.std__is_a_directory);
  define_polymorphic_function("std", "is_a_regular_file", get__std__is_a_regular_file, &poly_idx__std__is_a_regular_file, &var.std__is_a_regular_file);
  define_polymorphic_function("std", "is_a_link", get__std__is_a_link, &poly_idx__std__is_a_link, &var.std__is_a_link);
  define_polymorphic_function("std", "listen", get__std__listen, &poly_idx__std__listen, &var.std__listen);
  define_polymorphic_function("std", "accept", get__std__accept, &poly_idx__std__accept, &var.std__accept);
  define_polymorphic_function("std", "connect", get__std__connect, &poly_idx__std__connect, &var.std__connect);
}

static int already_run_phase_2 = false;

EXPORT void phase_2__basic__io(void) {
  if (already_run_phase_2) return;
  already_run_phase_2 = true;
  number__6 = from_uint32(6U);
  number__0o4000 = from_uint32(2048U);
  number__0o400 = from_uint32(256U);
  number__0o755 = from_uint32(493U);
  character__47 = from_uchar32(47);
  number__17 = from_uint32(17U);
  number__27 = from_uint32(27U);
  number__0o02 = from_uint32(2U);
  number__0o00 = from_uint32(0U);
  number__15 = from_uint32(15U);
  number__25 = from_uint32(25U);
  number__12 = from_uint32(12U);
  number__0 = from_uint32(0U);
  number__3 = from_uint32(3U);
  number__4 = from_uint32(4U);
  number__32 = from_uint32(32U);
  number__26 = from_uint32(26U);
  number__16 = from_uint32(16U);
  number__8 = from_uint32(8U);
  number__22 = from_uint32(22U);
  number__0o01 = from_uint32(1U);
  number__0o200 = from_uint32(128U);
  number__7 = from_uint32(7U);
  number__5 = from_uint32(5U);
  number__33 = from_uint32(33U);
  number__9 = from_uint32(9U);
  number__0o20000 = from_uint32(8192U);
  number__11 = from_uint32(11U);
  number__21 = from_uint32(21U);
  number__13 = from_uint32(13U);
  number__31 = from_uint32(31U);
  number__23 = from_uint32(23U);
  number__0o1000 = from_uint32(512U);
  number__34 = from_uint32(34U);
  number__28 = from_uint32(28U);
  number__1 = from_uint32(1U);
  number__19 = from_uint32(19U);
  number__18 = from_uint32(18U);
  number__29 = from_uint32(29U);
  number__0o100 = from_uint32(64U);
  number__0x1000000 = from_uint32(16777216U);
  number__2 = from_uint32(2U);
  number__0o2000 = from_uint32(1024U);
  number__20 = from_uint32(20U);
  number__10 = from_uint32(10U);
  number__30 = from_uint32(30U);
  number__24 = from_uint32(24U);
  number__14 = from_uint32(14U);
  string__81_5 = from_latin_1_string(" = ", 3);
  string__81_6 = from_latin_1_string("\012", 1);
  string__81_12 = from_latin_1_string(" failed: ", 9);
  string__81_13 = from_latin_1_string("!\012", 2);
  func__81_1 = create_function(entry__81_1, -1);
  func__82_1 = create_function(entry__82_1, -1);
  func__83_1 = create_function(entry__83_1, 0);
  func__84_1 = create_function(entry__84_1, 1);
  func__92_1 = create_function(entry__92_1, 1);
  func__93_1 = create_function(entry__93_1, 1);
  func__94_1 = create_function(entry__94_1, 1);
  func__95_1 = create_function(entry__95_1, 1);
  func__96_1 = create_function(entry__96_1, 1);
  func__97_1 = create_function(entry__97_1, 1);
  func__98_1 = create_function(entry__98_1, 1);
  func__99_1 = create_function(entry__99_1, 1);
  func__100_1 = create_function(entry__100_1, 1);
  func__101_1 = create_function(entry__101_1, 1);
  func__102_1 = create_function(entry__102_1, 1);
  func__103_1 = create_function(entry__103_1, 1);
  func__104_1 = create_function(entry__104_1, 1);
  func__105_1 = create_function(entry__105_1, 1);
  func__106_1 = create_function(entry__106_1, 1);
  func__107_1 = create_function(entry__107_1, 1);
  func__108_1 = create_function(entry__108_1, 1);
  func__115_1 = create_function(entry__115_1, 1);
  func__116_1 = create_function(entry__116_1, 2);
  func__117_1 = create_function(entry__117_1, 2);
  func__118_1 = create_function(entry__118_1, 1);
  func__119_1 = create_function(entry__119_1, -1);
  func__120_1 = create_function(entry__120_1, 1);
  func__121_1 = create_function(entry__121_1, 1);
  func__122_1 = create_function(entry__122_1, 1);
  func__123_1 = create_function(entry__123_1, 1);
  func__124_1 = create_function(entry__124_1, 1);
  func__125_1 = create_function(entry__125_1, 2);
  func__126_1 = create_function(entry__126_1, -1);
  func__127_1 = create_function(entry__127_1, 2);
  string__128_14 = from_latin_1_string("Failed to write to file!", 24);
  func__128_13 = create_function(entry__128_13, 0);
  func__128_1 = create_function(entry__128_1, -1);
  func__129_12 = create_function(entry__129_12, 0);
  func__129_1 = create_function(entry__129_1, -1);
  func__130_15 = create_function(entry__130_15, 0);
  func__130_1 = create_function(entry__130_1, 1);
  string__131_18 = from_latin_1_string("Failed to save file \042", 21);
  string__131_19 = from_latin_1_string("\042", 1);
  func__131_1 = create_function(entry__131_1, 2);
  func__132_1 = create_function(entry__132_1, 1);
  func__133_1 = create_function(entry__133_1, 3);
  string__134_9 = from_latin_1_string("IOCTL failed!\012", 14);
  func__134_8 = create_function(entry__134_8, 0);
  func__134_1 = create_function(entry__134_1, -1);
  func__135_1 = create_function(entry__135_1, 1);
  func__136_1 = create_function(entry__136_1, 1);
  string__137_9 = from_latin_1_string("Failed to delete file \042", 23);
  string__137_10 = from_latin_1_string("\042!\012", 3);
  func__137_1 = create_function(entry__137_1, 1);
  func__138_1 = create_function(entry__138_1, 4);
  func__139_1 = create_function(entry__139_1, 0);
  func__140_1 = create_function(entry__140_1, 2);
  func__141_1 = create_function(entry__141_1, -1);
  func__142_1 = create_function(entry__142_1, 0);
  func__143_1 = create_function(entry__143_1, 1);
  string__144_6 = from_latin_1_string("Failed to change current directory to \042", 39);
  string__144_7 = from_latin_1_string("\042!", 2);
  func__144_1 = create_function(entry__144_1, 1);
  func__145_1 = create_function(entry__145_1, 2);
  string__146_4 = from_latin_1_string("0o", 2);
  string__146_6 = from_latin_1_string("MODE", 4);
  string__146_8 = from_latin_1_string("PARENTS", 7);
  string__146_10 = from_latin_1_string("path", 4);
  string__146_12 = from_latin_1_string("mkdir", 5);
  func__146_22 = create_function(entry__146_22, 0);
  func__146_36 = create_function(entry__146_36, 0);
  func__146_1 = create_function(entry__146_1, -1);
  string__147_6 = from_latin_1_string("Failed to create directory \042", 28);
  func__147_1 = create_function(entry__147_1, -1);
  string__148_5 = from_latin_1_string("/", 1);
  string__148_12 = from_latin_1_string("//", 2);
  string__148_16 = from_latin_1_string("/./", 3);
  string__148_23 = from_latin_1_string("../", 3);
  func__148_1 = create_function(entry__148_1, 1);
  func__157_1 = create_function(entry__157_1, 1);
  func__158_1 = create_function(entry__158_1, 1);
  func__159_1 = create_function(entry__159_1, 1);
  func__160_1 = create_function(entry__160_1, 1);
  func__161_1 = create_function(entry__161_1, 1);
  func__162_1 = create_function(entry__162_1, 1);
  func__163_1 = create_function(entry__163_1, 1);
  func__164_1 = create_function(entry__164_1, 1);
  func__165_1 = create_function(entry__165_1, 1);
  func__166_1 = create_function(entry__166_1, 1);
  string__167_13 = from_latin_1_string(".", 1);
  string__167_14 = from_latin_1_string("..", 2);
  func__167_18 = create_function(entry__167_18, 0);
  func__167_23 = create_function(entry__167_23, 2);
  func__167_1 = create_function(entry__167_1, -1);
  func__175_1 = create_function(entry__175_1, -1);
  func__176_1 = create_function(entry__176_1, -1);
  func__177_1 = create_function(entry__177_1, 2);
  func__178_1 = create_function(entry__178_1, 2);
  func__179_1 = create_function(entry__179_1, 2);
  func__180_1 = create_function(entry__180_1, 2);
  func__181_1 = create_function(entry__181_1, 1);
  func__182_1 = create_function(entry__182_1, -1);
  func__183_1 = create_function(entry__183_1, -1);
  func__184_1 = create_function(entry__184_1, -1);
  func__185_1 = create_function(entry__185_1, -1);
  func__186_1 = create_function(entry__186_1, 1);
  func__187_1 = create_function(entry__187_1, 0);
  string__188_2 = from_latin_1_string("http://", 7);
  string__188_5 = from_latin_1_string("-q", 2);
  string__188_6 = from_latin_1_string("-O", 2);
  string__188_7 = from_latin_1_string("-", 1);
  string__188_11 = from_latin_1_string("Load error (\042", 13);
  string__188_12 = from_latin_1_string("\042)!", 3);
  func__188_1 = create_function(entry__188_1, 1);
  func__189_1 = create_function(entry__189_1, -1);
  string__192_1 = from_latin_1_string("wget", 4);
}

static int already_run_phase_3 = false;

EXPORT void phase_3__basic__io(void) {
  if (already_run_phase_3) return;
  already_run_phase_3 = true;
  set_module("basic__io");
  set_used_namespaces(used_namespaces);
  unique__1_1 = register_unique_item("std__MODE");
  assign_value(&var.std__MODE, unique__1_1);
  define_single_assign_static("std", "MODE", get__std__MODE, &var.std__MODE);
  unique__2_1 = register_unique_item("std__PARENTS");
  assign_value(&var.std__PARENTS, unique__2_1);
  define_single_assign_static("std", "PARENTS", get__std__PARENTS, &var.std__PARENTS);
  var._wget = create_future();
  define_single_assign_static("std", "O_RDONLY", get__std__O_RDONLY, &var.std__O_RDONLY);
  define_single_assign_static("std", "O_WRONLY", get__std__O_WRONLY, &var.std__O_WRONLY);
  define_single_assign_static("std", "O_RDWR", get__std__O_RDWR, &var.std__O_RDWR);
  define_single_assign_static("std", "O_CREAT", get__std__O_CREAT, &var.std__O_CREAT);
  define_single_assign_static("std", "O_EXCL", get__std__O_EXCL, &var.std__O_EXCL);
  define_single_assign_static("std", "O_NOCTTY", get__std__O_NOCTTY, &var.std__O_NOCTTY);
  define_single_assign_static("std", "O_TRUNC", get__std__O_TRUNC, &var.std__O_TRUNC);
  define_single_assign_static("std", "O_APPEND", get__std__O_APPEND, &var.std__O_APPEND);
  define_single_assign_static("std", "O_NONBLOCK", get__std__O_NONBLOCK, &var.std__O_NONBLOCK);
  define_single_assign_static("std", "O_ASYNC", get__std__O_ASYNC, &var.std__O_ASYNC);
  define_single_assign_static("std", "UNKNOWN", get__std__UNKNOWN, &var.std__UNKNOWN);
  define_single_assign_static("std", "FIFO", get__std__FIFO, &var.std__FIFO);
  define_single_assign_static("std", "CHARACTER_DEVICE", get__std__CHARACTER_DEVICE, &var.std__CHARACTER_DEVICE);
  define_single_assign_static("std", "DIRECTORY", get__std__DIRECTORY, &var.std__DIRECTORY);
  define_single_assign_static("std", "BLOCK_DEVICE", get__std__BLOCK_DEVICE, &var.std__BLOCK_DEVICE);
  define_single_assign_static("std", "REGULAR_FILE", get__std__REGULAR_FILE, &var.std__REGULAR_FILE);
  define_single_assign_static("std", "LINK", get__std__LINK, &var.std__LINK);
  define_single_assign_static("std", "SOCKET", get__std__SOCKET, &var.std__SOCKET);
  define_single_assign_static("std", "EPERM", get__std__EPERM, &var.std__EPERM);
  define_single_assign_static("std", "ENOENT", get__std__ENOENT, &var.std__ENOENT);
  define_single_assign_static("std", "ESRCH", get__std__ESRCH, &var.std__ESRCH);
  define_single_assign_static("std", "EINTR", get__std__EINTR, &var.std__EINTR);
  define_single_assign_static("std", "EIO", get__std__EIO, &var.std__EIO);
  define_single_assign_static("std", "ENXIO", get__std__ENXIO, &var.std__ENXIO);
  define_single_assign_static("std", "E2BIG", get__std__E2BIG, &var.std__E2BIG);
  define_single_assign_static("std", "ENOEXEC", get__std__ENOEXEC, &var.std__ENOEXEC);
  define_single_assign_static("std", "EBADF", get__std__EBADF, &var.std__EBADF);
  define_single_assign_static("std", "ECHILD", get__std__ECHILD, &var.std__ECHILD);
  define_single_assign_static("std", "EAGAIN", get__std__EAGAIN, &var.std__EAGAIN);
  define_single_assign_static("std", "ENOMEM", get__std__ENOMEM, &var.std__ENOMEM);
  define_single_assign_static("std", "EACCES", get__std__EACCES, &var.std__EACCES);
  define_single_assign_static("std", "EFAULT", get__std__EFAULT, &var.std__EFAULT);
  define_single_assign_static("std", "ENOTBLK", get__std__ENOTBLK, &var.std__ENOTBLK);
  define_single_assign_static("std", "EBUSY", get__std__EBUSY, &var.std__EBUSY);
  define_single_assign_static("std", "EEXIST", get__std__EEXIST, &var.std__EEXIST);
  define_single_assign_static("std", "EXDEV", get__std__EXDEV, &var.std__EXDEV);
  define_single_assign_static("std", "ENODEV", get__std__ENODEV, &var.std__ENODEV);
  define_single_assign_static("std", "ENOTDIR", get__std__ENOTDIR, &var.std__ENOTDIR);
  define_single_assign_static("std", "EISDIR", get__std__EISDIR, &var.std__EISDIR);
  define_single_assign_static("std", "EINVAL", get__std__EINVAL, &var.std__EINVAL);
  define_single_assign_static("std", "ENFILE", get__std__ENFILE, &var.std__ENFILE);
  define_single_assign_static("std", "EMFILE", get__std__EMFILE, &var.std__EMFILE);
  define_single_assign_static("std", "ENOTTY", get__std__ENOTTY, &var.std__ENOTTY);
  define_single_assign_static("std", "ETXTBSY", get__std__ETXTBSY, &var.std__ETXTBSY);
  define_single_assign_static("std", "EFBIG", get__std__EFBIG, &var.std__EFBIG);
  define_single_assign_static("std", "ENOSPC", get__std__ENOSPC, &var.std__ENOSPC);
  define_single_assign_static("std", "ESPIPE", get__std__ESPIPE, &var.std__ESPIPE);
  define_single_assign_static("std", "EROFS", get__std__EROFS, &var.std__EROFS);
  define_single_assign_static("std", "EMLINK", get__std__EMLINK, &var.std__EMLINK);
  define_single_assign_static("std", "EPIPE", get__std__EPIPE, &var.std__EPIPE);
  define_single_assign_static("std", "EDOM", get__std__EDOM, &var.std__EDOM);
  define_single_assign_static("std", "ERANGE", get__std__ERANGE, &var.std__ERANGE);
  define_single_assign_static("std", "raise_error", get__std__raise_error, &var.std__raise_error);
  define_single_assign_static("std", "check_error", get__std__check_error, &var.std__check_error);
  define_single_assign_static("std", "errno", get__std__errno, &var.std__errno);
  define_single_assign_static("std", "strerror", get__std__strerror, &var.std__strerror);
  var.types__stat = create_future_with_prototype(create__types__stat(NULL));
  define_single_assign_static("types", "stat", get__types__stat, &var.types__stat);
  define_single_assign_static("std", "stat", get__std__stat, &var.std__stat);
  define_single_assign_static("std", "file_exists", get__std__file_exists, &var.std__file_exists);
  var.types__file_descriptor = create_future_with_prototype(create__types__file_descriptor(-1));
  define_single_assign_static("types", "file_descriptor", get__types__file_descriptor, &var.types__file_descriptor);
  var.std__STDIN_FILENO = create__types__file_descriptor(STDIN_FILENO);
  define_single_assign_static("std", "STDIN_FILENO", get__std__STDIN_FILENO, &var.std__STDIN_FILENO);
  var.std__STDOUT_FILENO = create__types__file_descriptor(STDOUT_FILENO);
  define_single_assign_static("std", "STDOUT_FILENO", get__std__STDOUT_FILENO, &var.std__STDOUT_FILENO);
  var.std__STDERR_FILENO = create__types__file_descriptor(STDERR_FILENO);
  define_single_assign_static("std", "STDERR_FILENO", get__std__STDERR_FILENO, &var.std__STDERR_FILENO);
  define_single_assign_static("std", "create_file_descriptor", get__std__create_file_descriptor, &var.std__create_file_descriptor);
  define_single_assign_static("std", "open_file_for_reading", get__std__open_file_for_reading, &var.std__open_file_for_reading);
  define_single_assign_static("std", "open_file_for_writing", get__std__open_file_for_writing, &var.std__open_file_for_writing);
  define_single_assign_static("std", "open_file_for_reading_and_writing", get__std__open_file_for_reading_and_writing, &var.std__open_file_for_reading_and_writing);
  define_single_assign_static("std", "create_file", get__std__create_file, &var.std__create_file);
  define_single_assign_static("std", "atomic_write_to", get__std__atomic_write_to, &var.std__atomic_write_to);
  define_single_assign_static("std", "load_file", get__std__load_file, &var.std__load_file);
  define_single_assign_static("std", "save_file", get__std__save_file, &var.std__save_file);
  define_single_assign_static("std", "delete_file", get__std__delete_file, &var.std__delete_file);
  define_single_assign_static("std", "get_pid", get__std__get_pid, &var.std__get_pid);
  define_single_assign_static("std", "wait_pid", get__std__wait_pid, &var.std__wait_pid);
  define_single_assign_static("std", "wait_for_io", get__std__wait_for_io, &var.std__wait_for_io);
  define_single_assign_static("std", "current_path", get__std__current_path, &var.std__current_path);
  define_single_assign_static("std", "chdir", get__std__chdir, &var.std__chdir);
  define_single_assign_static("std", "change_directory", get__std__change_directory, &var.std__change_directory);
  define_single_assign_static("std", "clib_mkdir", get__std__clib_mkdir, &var.std__clib_mkdir);
  define_single_assign_static("std", "mkdir", get__std__mkdir, &var.std__mkdir);
  define_single_assign_static("std", "create_directory", get__std__create_directory, &var.std__create_directory);
  define_single_assign_static("std", "fullname", get__std__fullname, &var.std__fullname);
  var.types__DIR = create_future_with_prototype(create__types__DIR(NULL));
  define_single_assign_static("types", "DIR", get__types__DIR, &var.types__DIR);
  var.types__dirent = create_future_with_prototype(create__types__dirent(NULL));
  define_single_assign_static("types", "dirent", get__types__dirent, &var.types__dirent);
  define_single_assign_static("std", "opendir", get__std__opendir, &var.std__opendir);
  define_single_assign_static("std", "directory", get__std__directory, &var.std__directory);
  var.types__addrinfo = create_future_with_prototype(create__types__addrinfo(NULL));
  define_single_assign_static("types", "addrinfo", get__types__addrinfo, &var.types__addrinfo);
  define_single_assign_static("std", "get_network_addresses", get__std__get_network_addresses, &var.std__get_network_addresses);
  define_single_assign_static("std", "get_network_address", get__std__get_network_address, &var.std__get_network_address);
  define_single_assign_dynamic("std", "write", get__std__write, define__std__write, &dyna_idx__std__write);
  define_single_assign_static("std", "writeln", get__std__writeln, &var.std__writeln);
  define_single_assign_dynamic("std", "ewrite", get__std__ewrite, define__std__ewrite, &dyna_idx__std__ewrite);
  define_single_assign_static("std", "ewriteln", get__std__ewriteln, &var.std__ewriteln);
  define_single_assign_dynamic("std", "read", get__std__read, define__std__read, &dyna_idx__std__read);
  define_single_assign_static("std", "readln", get__std__readln, &var.std__readln);
  define_single_assign_static("std", "load", get__std__load, &var.std__load);
  define_single_assign_static("std", "save", get__std__save, &var.std__save);
}

static int already_run_phase_4 = false;

EXPORT void phase_4__basic__io(void) {
  if (already_run_phase_4) return;
  already_run_phase_4 = true;
  set_module("basic__io");
  set_used_namespaces(used_namespaces);
  use_read_only(NULL, "EEXIST", &get__EEXIST, &get_value_or_future__EEXIST);
  use_read_only(NULL, "Error", &get__Error, &get_value_or_future__Error);
  use_read_only(NULL, "MODE", &get__MODE, &get_value_or_future__MODE);
  use_read_only(NULL, "PARENTS", &get__PARENTS, &get_value_or_future__PARENTS);
  use_read_only(NULL, "SORT", &get__SORT, &get_value_or_future__SORT);
  use_read_only(NULL, "STDERR_FILENO", &get__STDERR_FILENO, &get_value_or_future__STDERR_FILENO);
  use_read_only(NULL, "STDIN_FILENO", &get__STDIN_FILENO, &get_value_or_future__STDIN_FILENO);
  use_read_only(NULL, "STDOUT_FILENO", &get__STDOUT_FILENO, &get_value_or_future__STDOUT_FILENO);
  use_polymorphic_function(NULL, "accept", &get__accept, &poly_idx__accept);
  use_polymorphic_function(NULL, "access_time_of", &get__access_time_of, &poly_idx__access_time_of);
  use_read_only(NULL, "append", &get__append, &get_value_or_future__append);
  use_read_only(NULL, "atomic_write_to", &get__atomic_write_to, &get_value_or_future__atomic_write_to);
  use_read_only(NULL, "before", &get__before, &get_value_or_future__before);
  use_polymorphic_function(NULL, "block_size_of", &get__block_size_of, &poly_idx__block_size_of);
  use_read_only(NULL, "case", &get__case, &get_value_or_future__case);
  use_read_only(NULL, "clib_mkdir", &get__clib_mkdir, &get_value_or_future__clib_mkdir);
  use_polymorphic_function(NULL, "close", &get__close, &poly_idx__close);
  use_polymorphic_function(NULL, "connect", &get__connect, &poly_idx__connect);
  use_read_only(NULL, "create_file", &get__create_file, &get_value_or_future__create_file);
  use_read_only(NULL, "current_path", &get__current_path, &get_value_or_future__current_path);
  use_polymorphic_function(NULL, "device_of", &get__device_of, &poly_idx__device_of);
  use_read_only(NULL, "do", &get__do, &get_value_or_future__do);
  use_polymorphic_function(NULL, "equal", &get__equal, &poly_idx__equal);
  use_read_only(NULL, "errno", &get__errno, &get_value_or_future__errno);
  use_read_only(NULL, "ewrite", &get__ewrite, &get_value_or_future__ewrite);
  use_read_only(NULL, "extern", &get__extern, &get_value_or_future__extern);
  use_read_only(NULL, "extract_options", &get__extract_options, &get_value_or_future__extract_options);
  use_read_only(NULL, "false", &get__false, &get_value_or_future__false);
  use_polymorphic_function(NULL, "file_type_of", &get__file_type_of, &poly_idx__file_type_of);
  use_polymorphic_function(NULL, "filename_of", &get__filename_of, &poly_idx__filename_of);
  use_polymorphic_function(NULL, "flush", &get__flush, &poly_idx__flush);
  use_read_only(NULL, "for_each", &get__for_each, &get_value_or_future__for_each);
  use_read_only(NULL, "forever", &get__forever, &get_value_or_future__forever);
  use_read_only(NULL, "fullname", &get__fullname, &get_value_or_future__fullname);
  use_polymorphic_function(NULL, "fullname_of", &get__fullname_of, &poly_idx__fullname_of);
  use_polymorphic_function(NULL, "get", &get__get, &poly_idx__get);
  use_read_only(NULL, "get_network_address", &get__get_network_address, &get_value_or_future__get_network_address);
  use_polymorphic_function(NULL, "group_id_of", &get__group_id_of, &poly_idx__group_id_of);
  use_read_only(NULL, "has_prefix", &get__has_prefix, &get_value_or_future__has_prefix);
  use_read_only(NULL, "has_suffix", &get__has_suffix, &get_value_or_future__has_suffix);
  use_polymorphic_function(NULL, "hash", &get__hash, &poly_idx__hash);
  use_read_only(NULL, "if", &get__if, &get_value_or_future__if);
  use_polymorphic_function(NULL, "inode_of", &get__inode_of, &poly_idx__inode_of);
  use_polymorphic_function(NULL, "is_a_directory", &get__is_a_directory, &poly_idx__is_a_directory);
  use_polymorphic_function(NULL, "is_a_link", &get__is_a_link, &poly_idx__is_a_link);
  use_polymorphic_function(NULL, "is_a_regular_file", &get__is_a_regular_file, &poly_idx__is_a_regular_file);
  use_read_only(NULL, "is_defined", &get__is_defined, &get_value_or_future__is_defined);
  use_read_only(NULL, "key_of", &get__key_of, &get_value_or_future__key_of);
  use_read_only(NULL, "length_of", &get__length_of, &get_value_or_future__length_of);
  use_polymorphic_function(NULL, "less", &get__less, &poly_idx__less);
  use_polymorphic_function(NULL, "link_count_of", &get__link_count_of, &poly_idx__link_count_of);
  use_read_only(NULL, "list", &get__list, &get_value_or_future__list);
  use_polymorphic_function(NULL, "listen", &get__listen, &poly_idx__listen);
  use_read_only(NULL, "load_file", &get__load_file, &get_value_or_future__load_file);
  use_read_only(NULL, "many", &get__many, &get_value_or_future__many);
  use_read_only(NULL, "minus", &get__minus, &get_value_or_future__minus);
  use_read_only(NULL, "mkdir", &get__mkdir, &get_value_or_future__mkdir);
  use_polymorphic_function(NULL, "mode_of", &get__mode_of, &poly_idx__mode_of);
  use_polymorphic_function(NULL, "modification_time_of", &get__modification_time_of, &poly_idx__modification_time_of);
  use_read_only(NULL, "not_followed_by", &get__not_followed_by, &get_value_or_future__not_followed_by);
  use_read_only(NULL, "oct", &get__oct, &get_value_or_future__oct);
  use_read_only(NULL, "open_file_for_reading", &get__open_file_for_reading, &get_value_or_future__open_file_for_reading);
  use_read_only(NULL, "parameter_count_of", &get__parameter_count_of, &get_value_or_future__parameter_count_of);
  use_read_only(NULL, "pass", &get__pass, &get_value_or_future__pass);
  use_read_only(NULL, "pathname_of", &get__pathname_of, &get_value_or_future__pathname_of);
  use_read_only(NULL, "push", &get__push, &get_value_or_future__push);
  use_read_only(NULL, "raise", &get__raise, &get_value_or_future__raise);
  use_read_only(NULL, "raise_error", &get__raise_error, &get_value_or_future__raise_error);
  use_read_only(NULL, "range", &get__range, &get_value_or_future__range);
  use_read_only(NULL, "read", &get__read, &get_value_or_future__read);
  use_polymorphic_function(NULL, "read_from", &get__read_from, &poly_idx__read_from);
  use_polymorphic_function(NULL, "read_some_bytes_from", &get__read_some_bytes_from, &poly_idx__read_some_bytes_from);
  use_read_only(NULL, "replace_all", &get__replace_all, &get_value_or_future__replace_all);
  use_read_only(NULL, "save_file", &get__save_file, &get_value_or_future__save_file);
  use_polymorphic_function(NULL, "sector_count_of", &get__sector_count_of, &poly_idx__sector_count_of);
  use_polymorphic_function(NULL, "size_of", &get__size_of, &poly_idx__size_of);
  use_read_only(NULL, "some", &get__some, &get_value_or_future__some);
  use_read_only(NULL, "sort", &get__sort, &get_value_or_future__sort);
  use_polymorphic_function(NULL, "status_change_time_of", &get__status_change_time_of, &poly_idx__status_change_time_of);
  use_read_only("std", "and", &get__std__and, &get_value_or_future__std__and);
  use_read_only("std", "bit_or", &get__std__bit_or, &get_value_or_future__std__bit_or);
  use_read_only("std", "equal", &get__std__equal, &get_value_or_future__std__equal);
  use_read_only("std", "key_value_pair", &get__std__key_value_pair, &get_value_or_future__std__key_value_pair);
  use_read_only("std", "less", &get__std__less, &get_value_or_future__std__less);
  use_read_only("std", "negate", &get__std__negate, &get_value_or_future__std__negate);
  use_read_only("std", "not", &get__std__not, &get_value_or_future__std__not);
  use_read_only("std", "or", &get__std__or, &get_value_or_future__std__or);
  use_read_only("std", "plus", &get__std__plus, &get_value_or_future__std__plus);
  use_read_only("std", "sequence", &get__std__sequence, &get_value_or_future__std__sequence);
  use_read_only("std", "string", &get__std__string, &get_value_or_future__std__string);
  use_read_only("std", "true", &get__std__true, &get_value_or_future__std__true);
  use_read_only(NULL, "string", &get__string, &get_value_or_future__string);
  use_read_only(NULL, "to_string", &get__to_string, &get_value_or_future__to_string);
  use_read_only(NULL, "to_utf8", &get__to_utf8, &get_value_or_future__to_utf8);
  use_read_only(NULL, "true", &get__true, &get_value_or_future__true);
  use_read_only("types", "object", &get__types__object, &get_value_or_future__types__object);
  use_read_only("types", "string", &get__types__string, &get_value_or_future__types__string);
  use_read_only(NULL, "undefined", &get__undefined, &get_value_or_future__undefined);
  use_read_only(NULL, "unless", &get__unless, &get_value_or_future__unless);
  use_polymorphic_function(NULL, "user_id_of", &get__user_id_of, &poly_idx__user_id_of);
  use_read_only(NULL, "value_of", &get__value_of, &get_value_or_future__value_of);
  use_read_only(NULL, "wait_to_read_from", &get__wait_to_read_from, &get_value_or_future__wait_to_read_from);
  use_read_only(NULL, "wait_to_write_to", &get__wait_to_write_to, &get_value_or_future__wait_to_write_to);
  use_read_only(NULL, "while", &get__while, &get_value_or_future__while);
  use_read_only(NULL, "without_suffix", &get__without_suffix, &get_value_or_future__without_suffix);
  use_read_only(NULL, "write", &get__write, &get_value_or_future__write);
  use_polymorphic_function(NULL, "write_some_bytes_to", &get__write_some_bytes_to, &poly_idx__write_some_bytes_to);
  use_polymorphic_function(NULL, "write_to", &get__write_to, &poly_idx__write_to);
  define_method("types", "stat", poly_idx__device_of, func__94_1);
  define_method("types", "stat", poly_idx__inode_of, func__95_1);
  define_method("types", "stat", poly_idx__mode_of, func__96_1);
  define_method("types", "stat", poly_idx__link_count_of, func__97_1);
  define_method("types", "stat", poly_idx__user_id_of, func__98_1);
  define_method("types", "stat", poly_idx__group_id_of, func__99_1);
  define_method("types", "stat", poly_idx__size_of, func__100_1);
  define_method("types", "stat", poly_idx__block_size_of, func__101_1);
  define_method("types", "stat", poly_idx__sector_count_of, func__102_1);
  define_method("types", "stat", poly_idx__access_time_of, func__103_1);
  define_method("types", "stat", poly_idx__modification_time_of, func__104_1);
  define_method("types", "stat", poly_idx__status_change_time_of, func__105_1);
  define_method("types", "stat", poly_idx__is_a_directory, func__106_1);
  define_method("types", "stat", poly_idx__is_a_regular_file, func__107_1);
  define_method("types", "stat", poly_idx__is_a_link, func__108_1);
  define_method("types", "file_descriptor", poly_idx__equal, func__116_1);
  define_method("types", "file_descriptor", poly_idx__less, func__117_1);
  define_method("types", "file_descriptor", poly_idx__hash, func__118_1);
  define_method("types", "file_descriptor", poly_idx__close, func__124_1);
  define_method("types", "file_descriptor", poly_idx__read_some_bytes_from, func__125_1);
  define_method("types", "file_descriptor", poly_idx__read_from, func__126_1);
  define_method("types", "file_descriptor", poly_idx__write_some_bytes_to, func__127_1);
  define_method("types", "file_descriptor", poly_idx__write_to, func__128_1);
  define_method("types", "file_descriptor", poly_idx__flush, func__132_1);
  define_method("types", "file_descriptor", poly_idx__std__ioctl, func__134_1);
  define_method("types", "file_descriptor", poly_idx__std__get_terminal_size, func__135_1);
  define_method("types", "DIR", poly_idx__close, func__158_1);
  define_method("types", "DIR", poly_idx__get, func__159_1);
  define_method("types", "dirent", poly_idx__filename_of, func__160_1);
  define_method("types", "dirent", poly_idx__inode_of, func__161_1);
  define_method("types", "dirent", poly_idx__file_type_of, func__162_1);
  define_method("types", "dirent", poly_idx__fullname_of, func__163_1);
  define_method("types", "dirent", poly_idx__is_a_directory, func__164_1);
  define_method("types", "dirent", poly_idx__is_a_regular_file, func__165_1);
  define_method("types", "dirent", poly_idx__is_a_link, func__166_1);
  define_method("types", "addrinfo", poly_idx__connect, func__177_1);
  define_method("types", "string", poly_idx__connect, func__178_1);
  define_method("types", "addrinfo", poly_idx__listen, func__179_1);
  define_method("types", "string", poly_idx__listen, func__180_1);
  define_method("types", "file_descriptor", poly_idx__accept, func__181_1);
}

static int already_run_phase_5 = false;

EXPORT void phase_5__basic__io(void) {
  if (already_run_phase_5) return;
  already_run_phase_5 = true;
  assign_value(&var.std__ioctl, create_function(type__std__ioctl, -1));
  assign_value(&var.std__get_terminal_size, create_function(type__std__get_terminal_size, -1));
  assign_value(&var.std__device_of, create_function(type__std__device_of, -1));
  assign_value(&var.std__inode_of, create_function(type__std__inode_of, -1));
  assign_value(&var.std__mode_of, create_function(type__std__mode_of, -1));
  assign_value(&var.std__link_count_of, create_function(type__std__link_count_of, -1));
  assign_value(&var.std__user_id_of, create_function(type__std__user_id_of, -1));
  assign_value(&var.std__group_id_of, create_function(type__std__group_id_of, -1));
  assign_value(&var.std__size_of, create_function(type__std__size_of, -1));
  assign_value(&var.std__block_size_of, create_function(type__std__block_size_of, -1));
  assign_value(&var.std__sector_count_of, create_function(type__std__sector_count_of, -1));
  assign_value(&var.std__access_time_of, create_function(type__std__access_time_of, -1));
  assign_value(&var.std__modification_time_of, create_function(type__std__modification_time_of, -1));
  assign_value(&var.std__status_change_time_of, create_function(type__std__status_change_time_of, -1));
  assign_value(&var.std__creation_time_of, create_function(type__std__creation_time_of, -1));
  assign_value(&var.std__filename_of, create_function(type__std__filename_of, -1));
  assign_value(&var.std__file_type_of, create_function(type__std__file_type_of, -1));
  assign_value(&var.std__pathname_of, create_function(type__std__pathname_of, -1));
  assign_value(&var.std__fullname_of, create_function(type__std__fullname_of, -1));
  assign_value(&var.std__is_a_directory, create_function(type__std__is_a_directory, -1));
  assign_value(&var.std__is_a_regular_file, create_function(type__std__is_a_regular_file, -1));
  assign_value(&var.std__is_a_link, create_function(type__std__is_a_link, -1));
  assign_value(&var.std__listen, create_function(type__std__listen, -1));
  assign_value(&var.std__accept, create_function(type__std__accept, -1));
  assign_value(&var.std__connect, create_function(type__std__connect, -1));
  assign_value(&var.std__O_RDONLY, number__0o00);
  assign_value(&var.std__O_WRONLY, number__0o01);
  assign_value(&var.std__O_RDWR, number__0o02);
  assign_value(&var.std__O_CREAT, number__0o100);
  assign_value(&var.std__O_EXCL, number__0o200);
  assign_value(&var.std__O_NOCTTY, number__0o400);
  assign_value(&var.std__O_TRUNC, number__0o1000);
  assign_value(&var.std__O_APPEND, number__0o2000);
  assign_value(&var.std__O_NONBLOCK, number__0o4000);
  assign_value(&var.std__O_ASYNC, number__0o20000);
  assign_value(&var.std__UNKNOWN, number__0);
  assign_value(&var.std__FIFO, number__1);
  assign_value(&var.std__CHARACTER_DEVICE, number__2);
  assign_value(&var.std__DIRECTORY, number__4);
  assign_value(&var.std__BLOCK_DEVICE, number__6);
  assign_value(&var.std__REGULAR_FILE, number__8);
  assign_value(&var.std__LINK, number__10);
  assign_value(&var.std__SOCKET, number__12);
  assign_value(&var.std__EPERM, number__1);
  assign_value(&var.std__ENOENT, number__2);
  assign_value(&var.std__ESRCH, number__3);
  assign_value(&var.std__EINTR, number__4);
  assign_value(&var.std__EIO, number__5);
  assign_value(&var.std__ENXIO, number__6);
  assign_value(&var.std__E2BIG, number__7);
  assign_value(&var.std__ENOEXEC, number__8);
  assign_value(&var.std__EBADF, number__9);
  assign_value(&var.std__ECHILD, number__10);
  assign_value(&var.std__EAGAIN, number__11);
  assign_value(&var.std__ENOMEM, number__12);
  assign_value(&var.std__EACCES, number__13);
  assign_value(&var.std__EFAULT, number__14);
  assign_value(&var.std__ENOTBLK, number__15);
  assign_value(&var.std__EBUSY, number__16);
  assign_value(&var.std__EEXIST, number__17);
  assign_value(&var.std__EXDEV, number__18);
  assign_value(&var.std__ENODEV, number__19);
  assign_value(&var.std__ENOTDIR, number__20);
  assign_value(&var.std__EISDIR, number__21);
  assign_value(&var.std__EINVAL, number__22);
  assign_value(&var.std__ENFILE, number__23);
  assign_value(&var.std__EMFILE, number__24);
  assign_value(&var.std__ENOTTY, number__25);
  assign_value(&var.std__ETXTBSY, number__26);
  assign_value(&var.std__EFBIG, number__27);
  assign_value(&var.std__ENOSPC, number__28);
  assign_value(&var.std__ESPIPE, number__29);
  assign_value(&var.std__EROFS, number__30);
  assign_value(&var.std__EMLINK, number__31);
  assign_value(&var.std__EPIPE, number__32);
  assign_value(&var.std__EDOM, number__33);
  assign_value(&var.std__ERANGE, number__34);
  assign_variable(&var.std__raise_error, &func__81_1);
  assign_variable(&var.std__check_error, &func__82_1);
  assign_variable(&var.std__errno, &func__83_1);
  assign_variable(&var.std__strerror, &func__84_1);
  assign_value(&var.types__stat, get__types__object());
  assign_variable(&var.std__stat, &func__92_1);
  assign_variable(&var.std__file_exists, &func__93_1);
  assign_value(&var.types__file_descriptor, get__types__object());
  assign_variable(&var.std__create_file_descriptor, &func__115_1);
  assign_variable(&var._posix_open, &func__119_1);
  assign_variable(&var.std__open_file_for_reading, &func__120_1);
  assign_variable(&var.std__open_file_for_writing, &func__121_1);
  assign_variable(&var.std__open_file_for_reading_and_writing, &func__122_1);
  assign_variable(&var.std__create_file, &func__123_1);
  assign_variable(&var.std__atomic_write_to, &func__129_1);
  assign_variable(&var.std__load_file, &func__130_1);
  assign_variable(&var.std__save_file, &func__131_1);
  assign_variable(&var._ioctl_value, &func__133_1);
  assign_variable(&var._posix_unlink, &func__136_1);
  assign_variable(&var.std__delete_file, &func__137_1);
  assign_variable(&var._wait_for_io_ready, &func__138_1);
  assign_variable(&var.std__get_pid, &func__139_1);
  assign_variable(&var.std__wait_pid, &func__140_1);
  assign_variable(&var.std__wait_for_io, &func__141_1);
  assign_variable(&var.std__current_path, &func__142_1);
  assign_variable(&var.std__chdir, &func__143_1);
  assign_variable(&var.std__change_directory, &func__144_1);
  assign_variable(&var.std__clib_mkdir, &func__145_1);
  assign_variable(&var.std__mkdir, &func__146_1);
  assign_variable(&var.std__create_directory, &func__147_1);
  assign_variable(&var.std__fullname, &func__148_1);
  assign_value(&var.types__DIR, get__types__object());
  assign_value(&var.types__dirent, get__types__object());
  assign_variable(&var.std__opendir, &func__157_1);
  assign_variable(&var.std__directory, &func__167_1);
  assign_value(&var.types__addrinfo, get__types__object());
  assign_variable(&var.std__get_network_addresses, &func__175_1);
  assign_variable(&var.std__get_network_address, &func__176_1);
  define__std__write(func__182_1);
  assign_variable(&var.std__writeln, &func__183_1);
  define__std__ewrite(func__184_1);
  assign_variable(&var.std__ewriteln, &func__185_1);
  define__std__read(func__186_1);
  assign_variable(&var.std__readln, &func__187_1);
  assign_variable(&var.std__load, &func__188_1);
  assign_variable(&var.std__save, &func__189_1);
}

static int already_run_phase_6 = false;

EXPORT void phase_6__basic__io(void) {
  if (already_run_phase_6) return;
  already_run_phase_6 = true;
  register_collector(collect__basic__io);
}
