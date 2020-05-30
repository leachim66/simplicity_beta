#include <netdb.h>
#include <stddef.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <math.h>
#include <signal.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
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
REGISTER int argument_count ASM("ebx");
IMPORT void too_few_arguments_error(void);
REGISTER NODE *myself ASM("r13");
IMPORT NODE *get_attribute(NODE *node, int idx);
REGISTER FRAME *arguments ASM("r12");
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
IMPORT void set_module(const char *name);
IMPORT NODE *from_uint32(uint32_t val);
IMPORT NODE *from_uchar32(unsigned int chr);
IMPORT NODE *register_unique_item(const char *name);
IMPORT void define_polymorphic_function(
  const char *namespace, const char *name, NODE_GETTER getter, int *id_p,
  NODE **var_p
);
IMPORT void define_polymorphic_function_with_setter(
  const char *namespace, const char *name, NODE_GETTER getter, int *id_p,
  NODE **var_p
);
IMPORT NODE *create_function(FUNC func, int par_count);
IMPORT void set_used_namespaces(const char **namespaces);
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
IMPORT void assign_value(NODE **dest, NODE *val);
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
static NODE_GETTER get__ANY_CHARACTER;
static NODE_GETTER get_value_or_future__ANY_CHARACTER;
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
static NODE_GETTER get__open_file;
static NODE_GETTER get_value_or_future__open_file;
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
static int poly_idx__to_integer;
static NODE_GETTER get__to_integer;
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
  NODE *_file_description;
  NODE *_WriteError;
  NODE *_ioctl_value;
  NODE *_posix_unlink;
  NODE *_wait_for_io_ready;
  NODE *_clib_mkdir;
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
  NODE *std__open_file;
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
  "file_description",
  "WriteError",
  "ioctl_value",
  "posix_unlink",
  "wait_for_io_ready",
  "clib_mkdir"
};
static NODE *unique__std__MODE;
static NODE *get__std__MODE(void) {
  return var.std__MODE;
}
static NODE *unique__std__PARENTS;
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

extern NODE *create__types__positive_integer(uint64_t value);
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
static NODE *func__std__raise_error_1;
static void entry__std__raise_error_1(void);
static FRAME_INFO frame__std__raise_error_1 = {3, {"cmd", "args", "info"}};
static NODE *func__std__raise_error_2;
static void entry__std__raise_error_2(void);
static FRAME_INFO frame__std__raise_error_2 = {2, {"arg", "info"}};
static void cont__std__raise_error_3(void);
static void cont__std__raise_error_4(void);
static NODE *string__fa730415fc16bec;
static NODE *string__578a5af303e9ceb;
static void cont__std__raise_error_7(void);
static void cont__std__raise_error_8(void);
static void cont__std__raise_error_9(void);
static void cont__std__raise_error_10(void);
static void cont__std__raise_error_11(void);
static NODE *string__64b427a840d3b445;
static NODE *string__2d7981f4e6002bcf;
static void cont__std__raise_error_14(void);
static NODE *get__std__raise_error(void) {
  return var.std__raise_error;
}
static NODE *func__std__check_error_1;
static void entry__std__check_error_1(void);
static FRAME_INFO frame__std__check_error_1 = {2, {"err", "args"}};
static void cont__std__check_error_2(void);
static NODE *get__std__check_error(void) {
  return var.std__check_error;
}
static void entry__std__errno_1(void);
static NODE *func__std__errno_1;
static NODE *get__std__errno(void) {
  return var.std__errno;
}
static void entry__std__strerror_1(void);
static NODE *func__std__strerror_1;
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
static void entry__std__stat_1(void);
static NODE *func__std__stat_1;
static NODE *get__std__stat(void) {
  return var.std__stat;
}
static void entry__std__file_exists_1(void);
static NODE *func__std__file_exists_1;
static NODE *get__std__file_exists(void) {
  return var.std__file_exists;
}
static void entry__types__stat__device_of_1(void);
static NODE *func__types__stat__device_of_1;
static void entry__types__stat__inode_of_1(void);
static NODE *func__types__stat__inode_of_1;
static void entry__types__stat__mode_of_1(void);
static NODE *func__types__stat__mode_of_1;
static void entry__types__stat__link_count_of_1(void);
static NODE *func__types__stat__link_count_of_1;
static void entry__types__stat__user_id_of_1(void);
static NODE *func__types__stat__user_id_of_1;
static void entry__types__stat__group_id_of_1(void);
static NODE *func__types__stat__group_id_of_1;
static void entry__types__stat__size_of_1(void);
static NODE *func__types__stat__size_of_1;
static void entry__types__stat__block_size_of_1(void);
static NODE *func__types__stat__block_size_of_1;
static void entry__types__stat__sector_count_of_1(void);
static NODE *func__types__stat__sector_count_of_1;
static void entry__types__stat__access_time_of_1(void);
static NODE *func__types__stat__access_time_of_1;
static void entry__types__stat__modification_time_of_1(void);
static NODE *func__types__stat__modification_time_of_1;
static void entry__types__stat__status_change_time_of_1(void);
static NODE *func__types__stat__status_change_time_of_1;
static void entry__types__stat__is_a_directory_1(void);
static NODE *func__types__stat__is_a_directory_1;
static void entry__types__stat__is_a_regular_file_1(void);
static NODE *func__types__stat__is_a_regular_file_1;
static void entry__types__stat__is_a_link_1(void);
static NODE *func__types__stat__is_a_link_1;

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
static void entry__std__create_file_descriptor_1(void);
static NODE *func__std__create_file_descriptor_1;
static NODE *get__std__create_file_descriptor(void) {
  return var.std__create_file_descriptor;
}
static void entry__types__file_descriptor__to_integer_1(void);
static NODE *func__types__file_descriptor__to_integer_1;
static void entry__types__file_descriptor__equal_1(void);
static NODE *func__types__file_descriptor__equal_1;
static void entry__types__file_descriptor__less_1(void);
static NODE *func__types__file_descriptor__less_1;
static void entry__types__file_descriptor__hash_1(void);
static NODE *func__types__file_descriptor__hash_1;
static void entry__posix_open_1(void);
static NODE *func__posix_open_1;
static NODE *func__std__open_file_1;
static void entry__std__open_file_1(void);
static FRAME_INFO frame__std__open_file_1 = {3, {"filename", "mode", "fd"}};
static void cont__std__open_file_2(void);
static void cont__std__open_file_3(void);
static NODE *func__std__open_file_4;
static void entry__std__open_file_4(void);
static FRAME_INFO frame__std__open_file_4 = {2, {"fd", "filename"}};
static void cont__std__open_file_5(void);
static void cont__std__open_file_6(void);
static NODE *get__std__open_file(void) {
  return var.std__open_file;
}
static NODE *func__std__open_file_for_reading_1;
static void entry__std__open_file_for_reading_1(void);
static FRAME_INFO frame__std__open_file_for_reading_1 = {1, {"filename"}};
static NODE *get__std__open_file_for_reading(void) {
  return var.std__open_file_for_reading;
}
static NODE *func__std__open_file_for_writing_1;
static void entry__std__open_file_for_writing_1(void);
static FRAME_INFO frame__std__open_file_for_writing_1 = {1, {"filename"}};
static NODE *get__std__open_file_for_writing(void) {
  return var.std__open_file_for_writing;
}
static NODE *func__std__open_file_for_reading_and_writing_1;
static void entry__std__open_file_for_reading_and_writing_1(void);
static FRAME_INFO frame__std__open_file_for_reading_and_writing_1 = {1, {"filename"}};
static NODE *get__std__open_file_for_reading_and_writing(void) {
  return var.std__open_file_for_reading_and_writing;
}
static NODE *func__std__create_file_1;
static void entry__std__create_file_1(void);
static FRAME_INFO frame__std__create_file_1 = {1, {"filename"}};
static void cont__std__create_file_2(void);
static void cont__std__create_file_3(void);
static NODE *get__std__create_file(void) {
  return var.std__create_file;
}
static void entry__types__file_descriptor__close_1(void);
static NODE *func__types__file_descriptor__close_1;
static void entry__types__file_descriptor__read_some_bytes_from_1(void);
static NODE *func__types__file_descriptor__read_some_bytes_from_1;
static NODE *func__types__file_descriptor__read_from_1;
static void entry__types__file_descriptor__read_from_1(void);
static FRAME_INFO frame__types__file_descriptor__read_from_1 = {3, {"fd", "amount", "return"}};
static void cont__types__file_descriptor__read_from_2(void);
static NODE *func__types__file_descriptor__read_from_3;
static void entry__types__file_descriptor__read_from_3(void);
static FRAME_INFO frame__types__file_descriptor__read_from_3 = {4, {"amount", "fd", "return", "buf"}};
static NODE *func__types__file_descriptor__read_from_4;
static void entry__types__file_descriptor__read_from_4(void);
static FRAME_INFO frame__types__file_descriptor__read_from_4 = {4, {"amount", "fd", "return", "buf"}};
static void cont__types__file_descriptor__read_from_5(void);
static NODE *func__types__file_descriptor__read_from_6;
static void entry__types__file_descriptor__read_from_6(void);
static FRAME_INFO frame__types__file_descriptor__read_from_6 = {6, {"fd", "amount", "return", "buf", "some_bytes", "len"}};
static void cont__types__file_descriptor__read_from_7(void);
static void cont__types__file_descriptor__read_from_8(void);
static void cont__types__file_descriptor__read_from_9(void);
static void cont__types__file_descriptor__read_from_10(void);
static NODE *func__types__file_descriptor__read_from_11;
static void entry__types__file_descriptor__read_from_11(void);
static FRAME_INFO frame__types__file_descriptor__read_from_11 = {2, {"return", "buf"}};
static void cont__types__file_descriptor__read_from_12(void);
static void cont__types__file_descriptor__read_from_13(void);
static void cont__types__file_descriptor__read_from_14(void);
static void cont__types__file_descriptor__read_from_15(void);
static void cont__types__file_descriptor__read_from_16(void);
static void cont__types__file_descriptor__read_from_17(void);
static void cont__types__file_descriptor__read_from_18(void);
static void entry__types__file_descriptor__write_some_bytes_to_1(void);
static NODE *func__types__file_descriptor__write_some_bytes_to_1;
static NODE *func__file_description_1;
static void entry__file_description_1(void);
static FRAME_INFO frame__file_description_1 = {2, {"fd", "filename"}};
static void cont__file_description_2(void);
static void cont__file_description_3(void);
static NODE *func__file_description_4;
static void entry__file_description_4(void);
static FRAME_INFO frame__file_description_4 = {1, {"filename"}};
static NODE *string__578a5af303e9cc3;
static void cont__file_description_6(void);
static NODE *func__file_description_7;
static void entry__file_description_7(void);
static FRAME_INFO frame__file_description_7 = {2, {"fd", "num"}};
static void cont__file_description_8(void);
static NODE *func__file_description_9;
static void entry__file_description_9(void);
static FRAME_INFO frame__file_description_9 = {1, {"num"}};
static NODE *string__431630d095799867;
static NODE *string__578a5af303e9cdf;
static void cont__file_description_12(void);
static NODE *func__file_description_13;
static void entry__file_description_13(void);
static FRAME_INFO frame__file_description_13 = {0, {}};
static NODE *string__bb740f9b15cb80c4;
static NODE *func__file_description_15;
static void entry__file_description_15(void);
static FRAME_INFO frame__file_description_15 = {0, {}};
static NODE *string__70d8a89c0475db9e;
static NODE *func__file_description_17;
static void entry__file_description_17(void);
static FRAME_INFO frame__file_description_17 = {0, {}};
static NODE *string__64d8a95c0445db9e;
static NODE *func__WriteError_1;
static void entry__WriteError_1(void);
static FRAME_INFO frame__WriteError_1 = {1, {"fd"}};
static void cont__WriteError_2(void);
static NODE *string__8138f7c6e352b20e;
static void cont__WriteError_4(void);
static NODE *func__types__file_descriptor__write_to_1;
static void entry__types__file_descriptor__write_to_1(void);
static FRAME_INFO frame__types__file_descriptor__write_to_1 = {4, {"fd", "args", "return", "data"}};
static void cont__types__file_descriptor__write_to_2(void);
static NODE *func__types__file_descriptor__write_to_3;
static void entry__types__file_descriptor__write_to_3(void);
static FRAME_INFO frame__types__file_descriptor__write_to_3 = {3, {"data", "fd", "return"}};
static void cont__types__file_descriptor__write_to_4(void);
static void cont__types__file_descriptor__write_to_5(void);
static NODE *func__types__file_descriptor__write_to_6;
static void entry__types__file_descriptor__write_to_6(void);
static FRAME_INFO frame__types__file_descriptor__write_to_6 = {4, {"fd", "data", "return", "bytes_written"}};
static void cont__types__file_descriptor__write_to_7(void);
static void cont__types__file_descriptor__write_to_8(void);
static void cont__types__file_descriptor__write_to_9(void);
static NODE *func__types__file_descriptor__write_to_10;
static void entry__types__file_descriptor__write_to_10(void);
static FRAME_INFO frame__types__file_descriptor__write_to_10 = {2, {"return", "fd"}};
static void cont__types__file_descriptor__write_to_11(void);
static void cont__types__file_descriptor__write_to_12(void);
static NODE *func__types__file_descriptor__write_to_13;
static void entry__types__file_descriptor__write_to_13(void);
static FRAME_INFO frame__types__file_descriptor__write_to_13 = {1, {"fd"}};
static void cont__types__file_descriptor__write_to_14(void);
static void cont__types__file_descriptor__write_to_15(void);
static void cont__types__file_descriptor__write_to_16(void);
static void cont__types__file_descriptor__write_to_17(void);
static void cont__types__file_descriptor__write_to_18(void);
static void cont__types__file_descriptor__write_to_19(void);
static void cont__types__file_descriptor__write_to_20(void);
static void cont__types__file_descriptor__write_to_21(void);
static NODE *func__types__file_descriptor__write_to_22;
static void entry__types__file_descriptor__write_to_22(void);
static FRAME_INFO frame__types__file_descriptor__write_to_22 = {1, {"return"}};
static void cont__types__file_descriptor__write_to_23(void);
static NODE *func__std__atomic_write_to_1;
static void entry__std__atomic_write_to_1(void);
static FRAME_INFO frame__std__atomic_write_to_1 = {4, {"fd", "args", "return", "data"}};
static void cont__std__atomic_write_to_2(void);
static NODE *func__std__atomic_write_to_3;
static void entry__std__atomic_write_to_3(void);
static FRAME_INFO frame__std__atomic_write_to_3 = {3, {"data", "fd", "return"}};
static void cont__std__atomic_write_to_4(void);
static void cont__std__atomic_write_to_5(void);
static NODE *func__std__atomic_write_to_6;
static void entry__std__atomic_write_to_6(void);
static FRAME_INFO frame__std__atomic_write_to_6 = {4, {"fd", "data", "return", "bytes_written"}};
static void cont__std__atomic_write_to_7(void);
static void cont__std__atomic_write_to_8(void);
static NODE *func__std__atomic_write_to_9;
static void entry__std__atomic_write_to_9(void);
static FRAME_INFO frame__std__atomic_write_to_9 = {2, {"return", "fd"}};
static void cont__std__atomic_write_to_10(void);
static void cont__std__atomic_write_to_11(void);
static NODE *func__std__atomic_write_to_12;
static void entry__std__atomic_write_to_12(void);
static FRAME_INFO frame__std__atomic_write_to_12 = {1, {"fd"}};
static void cont__std__atomic_write_to_13(void);
static void cont__std__atomic_write_to_14(void);
static void cont__std__atomic_write_to_15(void);
static void cont__std__atomic_write_to_16(void);
static void cont__std__atomic_write_to_17(void);
static void cont__std__atomic_write_to_18(void);
static void cont__std__atomic_write_to_19(void);
static void cont__std__atomic_write_to_20(void);
static NODE *func__std__atomic_write_to_21;
static void entry__std__atomic_write_to_21(void);
static FRAME_INFO frame__std__atomic_write_to_21 = {1, {"return"}};
static void cont__std__atomic_write_to_22(void);
static NODE *get__std__atomic_write_to(void) {
  return var.std__atomic_write_to;
}
static NODE *func__std__load_file_1;
static void entry__std__load_file_1(void);
static FRAME_INFO frame__std__load_file_1 = {2, {"filename", "fd"}};
static void cont__std__load_file_2(void);
static void cont__std__load_file_3(void);
static NODE *func__std__load_file_4;
static void entry__std__load_file_4(void);
static FRAME_INFO frame__std__load_file_4 = {2, {"fd", "buf"}};
static NODE *func__std__load_file_5;
static void entry__std__load_file_5(void);
static FRAME_INFO frame__std__load_file_5 = {3, {"break", "fd", "buf"}};
static NODE *func__std__load_file_6;
static void entry__std__load_file_6(void);
static FRAME_INFO frame__std__load_file_6 = {4, {"fd", "break", "buf", "some_bytes"}};
static void cont__std__load_file_7(void);
static void cont__std__load_file_8(void);
static void cont__std__load_file_9(void);
static void cont__std__load_file_10(void);
static void cont__std__load_file_11(void);
static void cont__std__load_file_12(void);
static void cont__std__load_file_13(void);
static void cont__std__load_file_14(void);
static NODE *func__std__load_file_15;
static void entry__std__load_file_15(void);
static FRAME_INFO frame__std__load_file_15 = {0, {}};
static NODE *get__std__load_file(void) {
  return var.std__load_file;
}
static NODE *func__std__save_file_1;
static void entry__std__save_file_1(void);
static FRAME_INFO frame__std__save_file_1 = {4, {"filename", "data", "return", "fd"}};
static void cont__std__save_file_2(void);
static void cont__std__save_file_3(void);
static NODE *func__std__save_file_4;
static void entry__std__save_file_4(void);
static FRAME_INFO frame__std__save_file_4 = {3, {"return", "fd", "data"}};
static void cont__std__save_file_5(void);
static void cont__std__save_file_6(void);
static NODE *func__std__save_file_7;
static void entry__std__save_file_7(void);
static FRAME_INFO frame__std__save_file_7 = {2, {"fd", "data"}};
static void cont__std__save_file_8(void);
static NODE *func__std__save_file_9;
static void entry__std__save_file_9(void);
static FRAME_INFO frame__std__save_file_9 = {3, {"return", "fd", "data"}};
static void cont__std__save_file_10(void);
static NODE *func__std__save_file_11;
static void entry__std__save_file_11(void);
static FRAME_INFO frame__std__save_file_11 = {1, {"fd"}};
static void cont__std__save_file_12(void);
static void cont__std__save_file_13(void);
static NODE *func__std__save_file_14;
static void entry__std__save_file_14(void);
static FRAME_INFO frame__std__save_file_14 = {2, {"return", "filename"}};
static void cont__std__save_file_15(void);
static void cont__std__save_file_16(void);
static NODE *func__std__save_file_17;
static void entry__std__save_file_17(void);
static FRAME_INFO frame__std__save_file_17 = {1, {"filename"}};
static NODE *string__52b15fd51e05f634;
static void cont__std__save_file_19(void);
static void cont__std__save_file_20(void);
static void cont__std__save_file_21(void);
static NODE *get__std__save_file(void) {
  return var.std__save_file;
}
static void entry__types__file_descriptor__flush_1(void);
static NODE *func__types__file_descriptor__flush_1;
static void entry__ioctl_value_1(void);
static NODE *func__ioctl_value_1;
static NODE *func__types__file_descriptor__std__ioctl_1;
static void entry__types__file_descriptor__std__ioctl_1(void);
static FRAME_INFO frame__types__file_descriptor__std__ioctl_1 = {4, {"fd", "request", "value", "return"}};
static void cont__types__file_descriptor__std__ioctl_2(void);
static void cont__types__file_descriptor__std__ioctl_3(void);
static NODE *func__types__file_descriptor__std__ioctl_4;
static void entry__types__file_descriptor__std__ioctl_4(void);
static FRAME_INFO frame__types__file_descriptor__std__ioctl_4 = {3, {"fd", "request", "value"}};
static void cont__types__file_descriptor__std__ioctl_5(void);
static void cont__types__file_descriptor__std__ioctl_6(void);
static void cont__types__file_descriptor__std__ioctl_7(void);
static NODE *func__types__file_descriptor__std__ioctl_8;
static void entry__types__file_descriptor__std__ioctl_8(void);
static FRAME_INFO frame__types__file_descriptor__std__ioctl_8 = {0, {}};
static NODE *string__9f84c1967610d391;
static NODE *func__types__file_descriptor__std__ioctl_10;
static void entry__types__file_descriptor__std__ioctl_10(void);
static FRAME_INFO frame__types__file_descriptor__std__ioctl_10 = {4, {"return", "fd", "request", "value"}};
static void cont__types__file_descriptor__std__ioctl_11(void);
static void cont__types__file_descriptor__std__ioctl_12(void);
static void entry__types__file_descriptor__std__get_terminal_size_1(void);
static NODE *func__types__file_descriptor__std__get_terminal_size_1;
static void entry__posix_unlink_1(void);
static NODE *func__posix_unlink_1;
static NODE *func__std__delete_file_1;
static void entry__std__delete_file_1(void);
static FRAME_INFO frame__std__delete_file_1 = {2, {"filename", "return"}};
static void cont__std__delete_file_2(void);
static void cont__std__delete_file_3(void);
static NODE *func__std__delete_file_4;
static void entry__std__delete_file_4(void);
static FRAME_INFO frame__std__delete_file_4 = {1, {"filename"}};
static void cont__std__delete_file_5(void);
static void cont__std__delete_file_6(void);
static void cont__std__delete_file_7(void);
static NODE *func__std__delete_file_8;
static void entry__std__delete_file_8(void);
static FRAME_INFO frame__std__delete_file_8 = {1, {"filename"}};
static NODE *string__98599da1f95f3503;
static NODE *string__fa730c15f216bc6;
static void cont__std__delete_file_11(void);
static NODE *func__std__delete_file_12;
static void entry__std__delete_file_12(void);
static FRAME_INFO frame__std__delete_file_12 = {2, {"return", "filename"}};
static void cont__std__delete_file_13(void);
static void cont__std__delete_file_14(void);
static void cont__std__delete_file_15(void);
static NODE *get__std__delete_file(void) {
  return var.std__delete_file;
}
static void entry__wait_for_io_ready_1(void);
static NODE *func__wait_for_io_ready_1;
static void entry__std__get_pid_1(void);
static NODE *func__std__get_pid_1;
static NODE *get__std__get_pid(void) {
  return var.std__get_pid;
}
static void entry__std__wait_pid_1(void);
static NODE *func__std__wait_pid_1;
static NODE *get__std__wait_pid(void) {
  return var.std__wait_pid;
}
static NODE *func__std__wait_for_io_1;
static void entry__std__wait_for_io_1(void);
static FRAME_INFO frame__std__wait_for_io_1 = {11, {"read_descriptors", "write_descriptors", "except_descriptors", "timeout", "success", "child_changed_state", "window_changed_size", "input_count", "output_count", "exception_count", "descriptors"}};
static void cont__std__wait_for_io_2(void);
static void cont__std__wait_for_io_3(void);
static void cont__std__wait_for_io_4(void);
static void cont__std__wait_for_io_5(void);
static void cont__std__wait_for_io_6(void);
static void cont__std__wait_for_io_7(void);
static void cont__std__wait_for_io_8(void);
static void cont__std__wait_for_io_9(void);
static void cont__std__wait_for_io_10(void);
static NODE *get__std__wait_for_io(void) {
  return var.std__wait_for_io;
}
static void entry__std__current_path_1(void);
static NODE *func__std__current_path_1;
static NODE *get__std__current_path(void) {
  return var.std__current_path;
}
static void entry__std__chdir_1(void);
static NODE *func__std__chdir_1;
static NODE *get__std__chdir(void) {
  return var.std__chdir;
}
static NODE *func__std__change_directory_1;
static void entry__std__change_directory_1(void);
static FRAME_INFO frame__std__change_directory_1 = {1, {"path"}};
static void cont__std__change_directory_2(void);
static void cont__std__change_directory_3(void);
static void cont__std__change_directory_4(void);
static NODE *func__std__change_directory_5;
static void entry__std__change_directory_5(void);
static FRAME_INFO frame__std__change_directory_5 = {1, {"path"}};
static NODE *string__6e87e13bb5f5e5b7;
static NODE *string__2d7981f4e6182be4;
static void cont__std__change_directory_8(void);
static NODE *get__std__change_directory(void) {
  return var.std__change_directory;
}
static void entry__clib_mkdir_1(void);
static NODE *func__clib_mkdir_1;
static NODE *func__std__mkdir_1;
static void entry__std__mkdir_1(void);
static FRAME_INFO frame__std__mkdir_1 = {6, {"options", "path", "mode", "do_create_parent_folders", "fail", "create_parent_folders"}};
static NODE *func__std__mkdir_2;
static void entry__std__mkdir_2(void);
static FRAME_INFO frame__std__mkdir_2 = {3, {"mode", "do_create_parent_folders", "path"}};
static void cont__std__mkdir_3(void);
static NODE *string__2d7981f4e6882baa;
static void cont__std__mkdir_5(void);
static NODE *string__580ae28b5c407d7c;
static void cont__std__mkdir_7(void);
static NODE *string__f8c406421419e0a9;
static void cont__std__mkdir_9(void);
static NODE *string__220ae90b5dc07d51;
static void cont__std__mkdir_11(void);
static NODE *string__5c5aea03ea80c025;
static NODE *func__std__mkdir_13;
static void entry__std__mkdir_13(void);
static FRAME_INFO frame__std__mkdir_13 = {4, {"partial_path", "create_parent_folders", "mode", "fail"}};
static void cont__std__mkdir_14(void);
static void cont__std__mkdir_15(void);
static void cont__std__mkdir_16(void);
static void cont__std__mkdir_17(void);
static NODE *func__std__mkdir_18;
static void entry__std__mkdir_18(void);
static FRAME_INFO frame__std__mkdir_18 = {4, {"create_parent_folders", "partial_path", "mode", "fail"}};
static void cont__std__mkdir_19(void);
static void cont__std__mkdir_20(void);
static void cont__std__mkdir_21(void);
static NODE *func__std__mkdir_22;
static void entry__std__mkdir_22(void);
static FRAME_INFO frame__std__mkdir_22 = {0, {}};
static void cont__std__mkdir_23(void);
static void cont__std__mkdir_24(void);
static void cont__std__mkdir_25(void);
static void cont__std__mkdir_26(void);
static void cont__std__mkdir_27(void);
static void cont__std__mkdir_28(void);
static void cont__std__mkdir_29(void);
static void cont__std__mkdir_30(void);
static NODE *func__std__mkdir_31;
static void entry__std__mkdir_31(void);
static FRAME_INFO frame__std__mkdir_31 = {2, {"create_parent_folders", "path"}};
static void cont__std__mkdir_32(void);
static void cont__std__mkdir_33(void);
static void cont__std__mkdir_34(void);
static NODE *func__std__mkdir_35;
static void entry__std__mkdir_35(void);
static FRAME_INFO frame__std__mkdir_35 = {2, {"do_create_parent_folders", "fail"}};
static NODE *func__std__mkdir_36;
static void entry__std__mkdir_36(void);
static FRAME_INFO frame__std__mkdir_36 = {0, {}};
static void cont__std__mkdir_37(void);
static void cont__std__mkdir_38(void);
static void cont__std__mkdir_39(void);
static NODE *get__std__mkdir(void) {
  return var.std__mkdir;
}
static NODE *func__std__create_directory_1;
static void entry__std__create_directory_1(void);
static FRAME_INFO frame__std__create_directory_1 = {2, {"path", "mode"}};
static void cont__std__create_directory_2(void);
static void cont__std__create_directory_3(void);
static void cont__std__create_directory_4(void);
static NODE *func__std__create_directory_5;
static void entry__std__create_directory_5(void);
static FRAME_INFO frame__std__create_directory_5 = {1, {"path"}};
static NODE *string__99b484ebf32a2eca;
static void cont__std__create_directory_7(void);
static NODE *get__std__create_directory(void) {
  return var.std__create_directory;
}
static NODE *func__std__fullname_1;
static void entry__std__fullname_1(void);
static FRAME_INFO frame__std__fullname_1 = {1, {"pathname"}};
static void cont__std__fullname_2(void);
static NODE *func__std__fullname_3;
static void entry__std__fullname_3(void);
static FRAME_INFO frame__std__fullname_3 = {1, {"pathname"}};
static void cont__std__fullname_4(void);
static NODE *string__578a5af303e9cce;
static void cont__std__fullname_6(void);
static void cont__std__fullname_7(void);
static void cont__std__fullname_8(void);
static NODE *func__std__fullname_9;
static void entry__std__fullname_9(void);
static FRAME_INFO frame__std__fullname_9 = {1, {"pathname"}};
static void cont__std__fullname_10(void);
static void cont__std__fullname_11(void);
static NODE *string__2d7981f4e6702bea;
static void cont__std__fullname_13(void);
static void cont__std__fullname_14(void);
static void cont__std__fullname_15(void);
static NODE *string__fa733815f596be3;
static void cont__std__fullname_17(void);
static void cont__std__fullname_18(void);
static NODE *func__std__fullname_19;
static void entry__std__fullname_19(void);
static FRAME_INFO frame__std__fullname_19 = {2, {"break", "pathname"}};
static NODE *func__std__fullname_20;
static void entry__std__fullname_20(void);
static FRAME_INFO frame__std__fullname_20 = {3, {"pathname", "break", "orig_pathname"}};
static void cont__std__fullname_21(void);
static void cont__std__fullname_22(void);
static void cont__std__fullname_23(void);
static NODE *string__9c0afacb5f107d16;
static void cont__std__fullname_25(void);
static void cont__std__fullname_26(void);
static void cont__std__fullname_27(void);
static void cont__std__fullname_28(void);
static void cont__std__fullname_29(void);
static void cont__std__fullname_30(void);
static void cont__std__fullname_31(void);
static NODE *func__std__fullname_32;
static void entry__std__fullname_32(void);
static FRAME_INFO frame__std__fullname_32 = {1, {"pathname"}};
static void cont__std__fullname_33(void);
static void cont__std__fullname_34(void);
static void cont__std__fullname_35(void);
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
static void entry__std__opendir_1(void);
static NODE *func__std__opendir_1;
static NODE *get__std__opendir(void) {
  return var.std__opendir;
}
static void entry__types__DIR__close_1(void);
static NODE *func__types__DIR__close_1;
static void entry__types__DIR__get_1(void);
static NODE *func__types__DIR__get_1;
static void entry__types__dirent__filename_of_1(void);
static NODE *func__types__dirent__filename_of_1;
static void entry__types__dirent__inode_of_1(void);
static NODE *func__types__dirent__inode_of_1;
static void entry__types__dirent__file_type_of_1(void);
static NODE *func__types__dirent__file_type_of_1;
static NODE *func__types__dirent__fullname_of_1;
static void entry__types__dirent__fullname_of_1(void);
static FRAME_INFO frame__types__dirent__fullname_of_1 = {1, {"self"}};
static void cont__types__dirent__fullname_of_2(void);
static void cont__types__dirent__fullname_of_3(void);
static void cont__types__dirent__fullname_of_4(void);
static NODE *func__types__dirent__is_a_directory_1;
static void entry__types__dirent__is_a_directory_1(void);
static FRAME_INFO frame__types__dirent__is_a_directory_1 = {1, {"self"}};
static void cont__types__dirent__is_a_directory_2(void);
static void cont__types__dirent__is_a_directory_3(void);
static NODE *func__types__dirent__is_a_regular_file_1;
static void entry__types__dirent__is_a_regular_file_1(void);
static FRAME_INFO frame__types__dirent__is_a_regular_file_1 = {1, {"self"}};
static void cont__types__dirent__is_a_regular_file_2(void);
static void cont__types__dirent__is_a_regular_file_3(void);
static NODE *func__types__dirent__is_a_link_1;
static void entry__types__dirent__is_a_link_1(void);
static FRAME_INFO frame__types__dirent__is_a_link_1 = {1, {"self"}};
static void cont__types__dirent__is_a_link_2(void);
static void cont__types__dirent__is_a_link_3(void);
static NODE *func__std__directory_1;
static void entry__std__directory_1(void);
static FRAME_INFO frame__std__directory_1 = {5, {"options", "pathname", "do_sort", "entries", "dir"}};
static void cont__std__directory_2(void);
static void cont__std__directory_3(void);
static void cont__std__directory_4(void);
static void cont__std__directory_5(void);
static void cont__std__directory_6(void);
static NODE *func__std__directory_7;
static void entry__std__directory_7(void);
static FRAME_INFO frame__std__directory_7 = {3, {"break", "dir", "entries"}};
static NODE *func__std__directory_8;
static void entry__std__directory_8(void);
static FRAME_INFO frame__std__directory_8 = {4, {"dir", "break", "entries", "entry"}};
static void cont__std__directory_9(void);
static void cont__std__directory_10(void);
static void cont__std__directory_11(void);
static void cont__std__directory_12(void);
static NODE *string__578a5af303e9ccf;
static NODE *string__2d7981f4e6782beb;
static void cont__std__directory_15(void);
static NODE *func__std__directory_16;
static void entry__std__directory_16(void);
static FRAME_INFO frame__std__directory_16 = {2, {"entries", "entry"}};
static void cont__std__directory_17(void);
static NODE *func__std__directory_18;
static void entry__std__directory_18(void);
static FRAME_INFO frame__std__directory_18 = {0, {}};
static void cont__std__directory_19(void);
static void cont__std__directory_20(void);
static void cont__std__directory_21(void);
static NODE *func__std__directory_22;
static void entry__std__directory_22(void);
static FRAME_INFO frame__std__directory_22 = {1, {"entries"}};
static NODE *func__std__directory_23;
static void entry__std__directory_23(void);
static FRAME_INFO frame__std__directory_23 = {2, {"left", "right"}};
static void cont__std__directory_24(void);
static void cont__std__directory_25(void);
static void cont__std__directory_26(void);
static void cont__std__directory_27(void);
static void cont__std__directory_28(void);
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
static void entry__std__get_network_addresses_1(void);
static NODE *func__std__get_network_addresses_1;
static NODE *get__std__get_network_addresses(void) {
  return var.std__get_network_addresses;
}
static void entry__std__get_network_address_1(void);
static NODE *func__std__get_network_address_1;
static NODE *get__std__get_network_address(void) {
  return var.std__get_network_address;
}
static void entry__types__addrinfo__connect_1(void);
static NODE *func__types__addrinfo__connect_1;
static NODE *func__types__string__connect_1;
static void entry__types__string__connect_1(void);
static FRAME_INFO frame__types__string__connect_1 = {2, {"uri", "port"}};
static void cont__types__string__connect_2(void);
static void entry__types__addrinfo__listen_1(void);
static NODE *func__types__addrinfo__listen_1;
static NODE *func__types__string__listen_1;
static void entry__types__string__listen_1(void);
static FRAME_INFO frame__types__string__listen_1 = {2, {"uri", "port"}};
static void cont__types__string__listen_2(void);
static void entry__types__file_descriptor__accept_1(void);
static NODE *func__types__file_descriptor__accept_1;
static int dyna_idx__std__write;
static NODE *get__std__write(void) {
  return get_dynamic_slot(dyna_idx__std__write);
}
static void define__std__write(NODE *node) {
  define_dynamic_slot(dyna_idx__std__write, node);
}
static NODE *func__std__write_1;
static void entry__std__write_1(void);
static FRAME_INFO frame__std__write_1 = {1, {"args"}};
static void cont__std__write_2(void);
static void cont__std__write_3(void);
static NODE *func__std__writeln_1;
static void entry__std__writeln_1(void);
static FRAME_INFO frame__std__writeln_1 = {1, {"args"}};
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
static NODE *func__std__ewrite_1;
static void entry__std__ewrite_1(void);
static FRAME_INFO frame__std__ewrite_1 = {1, {"args"}};
static void cont__std__ewrite_2(void);
static void cont__std__ewrite_3(void);
static NODE *func__std__ewriteln_1;
static void entry__std__ewriteln_1(void);
static FRAME_INFO frame__std__ewriteln_1 = {1, {"args"}};
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
static NODE *func__std__read_1;
static void entry__std__read_1(void);
static FRAME_INFO frame__std__read_1 = {1, {"n"}};
static NODE *func__std__readln_1;
static void entry__std__readln_1(void);
static FRAME_INFO frame__std__readln_1 = {2, {"return", "buf"}};
static NODE *func__std__readln_2;
static void entry__std__readln_2(void);
static FRAME_INFO frame__std__readln_2 = {3, {"return", "buf", "chr"}};
static void cont__std__readln_3(void);
static void cont__std__readln_4(void);
static NODE *func__std__readln_5;
static void entry__std__readln_5(void);
static FRAME_INFO frame__std__readln_5 = {1, {"chr"}};
static void cont__std__readln_6(void);
static void cont__std__readln_7(void);
static NODE *func__std__readln_8;
static void entry__std__readln_8(void);
static FRAME_INFO frame__std__readln_8 = {2, {"return", "buf"}};
static void cont__std__readln_9(void);
static void cont__std__readln_10(void);
static void cont__std__readln_11(void);
static NODE *get__std__readln(void) {
  return var.std__readln;
}
static NODE *func__std__load_1;
static void entry__std__load_1(void);
static FRAME_INFO frame__std__load_1 = {1, {"filename"}};
static NODE *string__92241b5897c380d5;
static void cont__std__load_3(void);
static NODE *func__std__load_4;
static void entry__std__load_4(void);
static FRAME_INFO frame__std__load_4 = {2, {"filename", "buf"}};
static NODE *string__2d7981f4e6602bb4;
static NODE *string__2d7981f4e6602b8a;
static NODE *string__578a5af303e9ccc;
static void cont__std__load_8(void);
static NODE *func__std__load_9;
static void entry__std__load_9(void);
static FRAME_INFO frame__std__load_9 = {1, {"buf"}};
static NODE *func__std__load_10;
static void entry__std__load_10(void);
static FRAME_INFO frame__std__load_10 = {1, {"filename"}};
static NODE *string__a622e2e97612a669;
static NODE *string__fa730c15f616bed;
static void cont__std__load_13(void);
static NODE *func__std__load_14;
static void entry__std__load_14(void);
static FRAME_INFO frame__std__load_14 = {1, {"filename"}};
static NODE *get__std__load(void) {
  return var.std__load;
}
static NODE *func__std__save_1;
static void entry__std__save_1(void);
static FRAME_INFO frame__std__save_1 = {4, {"options", "filename", "data", "do_create_directory"}};
static void cont__std__save_2(void);
static void cont__std__save_3(void);
static NODE *func__std__save_4;
static void entry__std__save_4(void);
static FRAME_INFO frame__std__save_4 = {2, {"filename", "path"}};
static void cont__std__save_5(void);
static void cont__std__save_6(void);
static void cont__std__save_7(void);
static void cont__std__save_8(void);
static NODE *func__std__save_9;
static void entry__std__save_9(void);
static FRAME_INFO frame__std__save_9 = {1, {"path"}};
static void cont__std__save_10(void);
static void cont__std__save_11(void);
static void cont__std__save_12(void);
static NODE *get__std__save(void) {
  return var.std__save;
}
static NODE *string__2c0ae88b5d487d4d;
static void cont__196_2(void);
void run__basic__io(void);

static CONTINUATION_INFO continuation_info[] = {
  {type__std__ioctl, NULL, 45, 45, 2, 11},
  {type__std__get_terminal_size, NULL, 49, 49, 2, 23},
  {type__std__device_of, NULL, 55, 55, 2, 15},
  {type__std__inode_of, NULL, 66, 66, 2, 14},
  {type__std__mode_of, NULL, 76, 76, 2, 13},
  {type__std__link_count_of, NULL, 89, 89, 2, 19},
  {type__std__user_id_of, NULL, 100, 100, 2, 16},
  {type__std__group_id_of, NULL, 110, 110, 2, 17},
  {type__std__size_of, NULL, 120, 120, 2, 13},
  {type__std__block_size_of, NULL, 130, 130, 2, 19},
  {type__std__sector_count_of, NULL, 145, 145, 2, 21},
  {type__std__access_time_of, NULL, 157, 157, 2, 20},
  {type__std__modification_time_of, NULL, 173, 173, 2, 26},
  {type__std__status_change_time_of, NULL, 186, 186, 2, 27},
  {type__std__creation_time_of, NULL, 200, 200, 2, 22},
  {type__std__filename_of, NULL, 215, 215, 2, 17},
  {type__std__file_type_of, NULL, 219, 219, 2, 18},
  {type__std__pathname_of, NULL, 226, 226, 2, 17},
  {type__std__fullname_of, NULL, 230, 230, 2, 17},
  {type__std__is_a_directory, NULL, 234, 234, 2, 20},
  {type__std__is_a_regular_file, NULL, 238, 238, 2, 23},
  {type__std__is_a_link, NULL, 242, 242, 2, 15},
  {type__std__listen, NULL, 246, 246, 2, 12},
  {type__std__accept, NULL, 250, 250, 2, 12},
  {type__std__connect, NULL, 254, 254, 2, 13},
  {run__basic__io, NULL, 43, 43, 1, 19},
  {cont__196_2, NULL, },
  {entry__std__raise_error_2, NULL, 903, 903, 42, 52},
  {cont__std__raise_error_3, &frame__std__raise_error_2, 903, 903, 59, 71},
  {cont__std__raise_error_4, &frame__std__raise_error_2, 903, 903, 39, 77},
  {cont__std__raise_error_7, &frame__std__raise_error_2, 903, 903, 24, 77},
  {cont__std__raise_error_8, &frame__std__raise_error_2, 903, 903, 77, 77},
  {entry__std__raise_error_1, NULL, 903, 903, 3, 77},
  {cont__std__raise_error_9, &frame__std__raise_error_1, 904, 904, 41, 52},
  {cont__std__raise_error_10, &frame__std__raise_error_1, 904, 904, 27, 53},
  {cont__std__raise_error_11, &frame__std__raise_error_1, 904, 904, 9, 67},
  {cont__std__raise_error_14, &frame__std__raise_error_1, 904, 904, 3, 67},
  {entry__std__check_error_1, NULL, 917, 917, 6, 12},
  {cont__std__check_error_2, &frame__std__check_error_1, 917, 917, 3, 30},
  {entry__std__errno_1, NULL, 929, 932, 3, 2},
  {entry__std__strerror_1, NULL, 943, 946, 3, 2},
  {entry__std__stat_1, NULL, 1026, 1035, 3, 2},
  {entry__std__file_exists_1, NULL, 1047, 1054, 3, 2},
  {entry__types__stat__device_of_1, NULL, 1061, 1064, 3, 2},
  {entry__types__stat__inode_of_1, NULL, 1071, 1074, 3, 2},
  {entry__types__stat__mode_of_1, NULL, 1081, 1085, 3, 2},
  {entry__types__stat__link_count_of_1, NULL, 1092, 1096, 3, 2},
  {entry__types__stat__user_id_of_1, NULL, 1103, 1107, 3, 2},
  {entry__types__stat__group_id_of_1, NULL, 1114, 1118, 3, 2},
  {entry__types__stat__size_of_1, NULL, 1125, 1129, 3, 2},
  {entry__types__stat__block_size_of_1, NULL, 1136, 1140, 3, 2},
  {entry__types__stat__sector_count_of_1, NULL, 1147, 1151, 3, 2},
  {entry__types__stat__access_time_of_1, NULL, 1158, 1165, 3, 2},
  {entry__types__stat__modification_time_of_1, NULL, 1172, 1179, 3, 2},
  {entry__types__stat__status_change_time_of_1, NULL, 1186, 1193, 3, 2},
  {entry__types__stat__is_a_directory_1, NULL, 1200, 1204, 3, 2},
  {entry__types__stat__is_a_regular_file_1, NULL, 1211, 1215, 3, 2},
  {entry__types__stat__is_a_link_1, NULL, 1222, 1226, 3, 2},
  {entry__std__create_file_descriptor_1, NULL, 1291, 1294, 3, 2},
  {entry__types__file_descriptor__to_integer_1, NULL, 1301, 1304, 3, 2},
  {entry__types__file_descriptor__equal_1, NULL, 1309, 1315, 3, 2},
  {entry__types__file_descriptor__less_1, NULL, 1320, 1326, 3, 2},
  {entry__types__file_descriptor__hash_1, NULL, 1331, 1334, 3, 2},
  {entry__posix_open_1, NULL, 1337, 1360, 3, 2},
  {entry__std__open_file_4, NULL, 1373, 1373, 21, 54},
  {cont__std__open_file_5, &frame__std__open_file_4, 1373, 1373, 54, 54},
  {entry__std__open_file_1, NULL, 1372, 1372, 3, 31},
  {cont__std__open_file_2, &frame__std__open_file_1, 1373, 1373, 6, 18},
  {cont__std__open_file_3, &frame__std__open_file_1, 1373, 1373, 3, 54},
  {cont__std__open_file_6, &frame__std__open_file_1, 1374, 1374, 3, 7},
  {entry__std__open_file_for_reading_1, NULL, 1398, 1398, 3, 34},
  {entry__std__open_file_for_writing_1, NULL, 1422, 1422, 3, 34},
  {entry__std__open_file_for_reading_and_writing_1, NULL, 1448, 1448, 3, 32},
  {entry__std__create_file_1, NULL, 1468, 1468, 22, 48},
  {cont__std__create_file_2, &frame__std__create_file_1, 1468, 1468, 22, 62},
  {cont__std__create_file_3, &frame__std__create_file_1, 1468, 1468, 3, 62},
  {entry__types__file_descriptor__close_1, NULL, 1473, 1496, 3, 2},
  {entry__types__file_descriptor__read_some_bytes_from_1, NULL, 1506, 1523, 3, 2},
  {entry__types__file_descriptor__read_from_11, NULL, 1555, 1555, 20, 29},
  {entry__types__file_descriptor__read_from_6, NULL, 1552, 1552, 7, 26},
  {cont__types__file_descriptor__read_from_7, &frame__types__file_descriptor__read_from_6, 1553, 1553, 7, 48},
  {cont__types__file_descriptor__read_from_8, &frame__types__file_descriptor__read_from_6, 1554, 1554, 7, 32},
  {cont__types__file_descriptor__read_from_9, &frame__types__file_descriptor__read_from_6, 1555, 1555, 10, 17},
  {cont__types__file_descriptor__read_from_10, &frame__types__file_descriptor__read_from_6, 1555, 1555, 7, 29},
  {cont__types__file_descriptor__read_from_12, &frame__types__file_descriptor__read_from_6, 1556, 1556, 7, 28},
  {cont__types__file_descriptor__read_from_13, &frame__types__file_descriptor__read_from_6, 1557, 1557, 7, 23},
  {cont__types__file_descriptor__read_from_14, &frame__types__file_descriptor__read_from_6, 1557, 1557, 23, 23},
  {entry__types__file_descriptor__read_from_4, NULL, 1551, 1551, 14, 23},
  {cont__types__file_descriptor__read_from_5, &frame__types__file_descriptor__read_from_4, 1551, 1557, 11, 23},
  {entry__types__file_descriptor__read_from_3, NULL, 1551, 1557, 5, 23},
  {cont__types__file_descriptor__read_from_15, &frame__types__file_descriptor__read_from_3, 1558, 1558, 5, 14},
  {entry__types__file_descriptor__read_from_1, NULL, 1549, 1549, 6, 22},
  {cont__types__file_descriptor__read_from_2, &frame__types__file_descriptor__read_from_1, 1549, 1558, 3, 14},
  {cont__types__file_descriptor__read_from_16, &frame__types__file_descriptor__read_from_1, 1559, 1559, 3, 22},
  {cont__types__file_descriptor__read_from_17, &frame__types__file_descriptor__read_from_1, 1560, 1560, 3, 50},
  {cont__types__file_descriptor__read_from_18, &frame__types__file_descriptor__read_from_1, 1560, 1560, 50, 50},
  {entry__types__file_descriptor__write_some_bytes_to_1, NULL, 1570, 1588, 3, 2},
  {entry__file_description_4, NULL, 1594, 1594, 8, 32},
  {cont__file_description_6, &frame__file_description_4, 1594, 1594, 5, 32},
  {entry__file_description_9, NULL, 1604, 1604, 12, 37},
  {cont__file_description_12, &frame__file_description_9, 1604, 1604, 9, 37},
  {entry__file_description_13, NULL, 1599, 1599, 9, 20},
  {entry__file_description_15, NULL, 1601, 1601, 9, 21},
  {entry__file_description_17, NULL, 1603, 1603, 9, 21},
  {entry__file_description_7, NULL, 1596, 1596, 7, 24},
  {cont__file_description_8, &frame__file_description_7, 1597, 1604, 7, 37},
  {entry__file_description_1, NULL, 1591, 1591, 3, 27},
  {cont__file_description_2, &frame__file_description_1, 1593, 1593, 5, 23},
  {cont__file_description_3, &frame__file_description_1, 1592, 1604, 3, 39},
  {entry__WriteError_1, NULL, 1606, 1606, 50, 69},
  {cont__WriteError_2, &frame__WriteError_1, 1606, 1606, 31, 71},
  {cont__WriteError_4, &frame__WriteError_1, 1606, 1606, 19, 71},
  {entry__types__file_descriptor__write_to_13, NULL, 1626, 1626, 43, 55},
  {entry__types__file_descriptor__write_to_10, NULL, 1626, 1626, 10, 35},
  {cont__types__file_descriptor__write_to_11, &frame__types__file_descriptor__write_to_10, 1626, 1626, 10, 40},
  {cont__types__file_descriptor__write_to_12, &frame__types__file_descriptor__write_to_10, 1626, 1626, 7, 55},
  {cont__types__file_descriptor__write_to_14, &frame__types__file_descriptor__write_to_10, 1627, 1627, 7, 18},
  {entry__types__file_descriptor__write_to_6, NULL, 1623, 1623, 5, 23},
  {cont__types__file_descriptor__write_to_7, &frame__types__file_descriptor__write_to_6, 1624, 1624, 5, 46},
  {cont__types__file_descriptor__write_to_8, &frame__types__file_descriptor__write_to_6, 1625, 1625, 8, 24},
  {cont__types__file_descriptor__write_to_9, &frame__types__file_descriptor__write_to_6, 1625, 1627, 5, 18},
  {cont__types__file_descriptor__write_to_15, &frame__types__file_descriptor__write_to_6, 1628, 1628, 17, 31},
  {cont__types__file_descriptor__write_to_16, &frame__types__file_descriptor__write_to_6, 1628, 1628, 34, 34},
  {cont__types__file_descriptor__write_to_17, &frame__types__file_descriptor__write_to_6, 1628, 1628, 5, 34},
  {cont__types__file_descriptor__write_to_18, &frame__types__file_descriptor__write_to_6, 1628, 1628, 34, 34},
  {entry__types__file_descriptor__write_to_3, NULL, 1622, 1622, 12, 26},
  {cont__types__file_descriptor__write_to_4, &frame__types__file_descriptor__write_to_3, 1622, 1622, 12, 30},
  {cont__types__file_descriptor__write_to_5, &frame__types__file_descriptor__write_to_3, 1622, 1628, 9, 34},
  {entry__types__file_descriptor__write_to_22, NULL, 1629, 1629, 39, 49},
  {entry__types__file_descriptor__write_to_1, NULL, 1621, 1621, 3, 22},
  {cont__types__file_descriptor__write_to_2, &frame__types__file_descriptor__write_to_1, 1622, 1628, 3, 34},
  {cont__types__file_descriptor__write_to_19, &frame__types__file_descriptor__write_to_1, 1629, 1629, 6, 31},
  {cont__types__file_descriptor__write_to_20, &frame__types__file_descriptor__write_to_1, 1629, 1629, 6, 36},
  {cont__types__file_descriptor__write_to_21, &frame__types__file_descriptor__write_to_1, 1629, 1629, 3, 49},
  {cont__types__file_descriptor__write_to_23, &frame__types__file_descriptor__write_to_1, 1629, 1629, 49, 49},
  {entry__std__atomic_write_to_12, NULL, 1650, 1650, 43, 55},
  {entry__std__atomic_write_to_9, NULL, 1650, 1650, 10, 35},
  {cont__std__atomic_write_to_10, &frame__std__atomic_write_to_9, 1650, 1650, 10, 40},
  {cont__std__atomic_write_to_11, &frame__std__atomic_write_to_9, 1650, 1650, 7, 55},
  {cont__std__atomic_write_to_13, &frame__std__atomic_write_to_9, 1651, 1651, 7, 18},
  {entry__std__atomic_write_to_6, NULL, 1648, 1648, 5, 46},
  {cont__std__atomic_write_to_7, &frame__std__atomic_write_to_6, 1649, 1649, 8, 24},
  {cont__std__atomic_write_to_8, &frame__std__atomic_write_to_6, 1649, 1651, 5, 18},
  {cont__std__atomic_write_to_14, &frame__std__atomic_write_to_6, 1652, 1652, 17, 31},
  {cont__std__atomic_write_to_15, &frame__std__atomic_write_to_6, 1652, 1652, 34, 34},
  {cont__std__atomic_write_to_16, &frame__std__atomic_write_to_6, 1652, 1652, 5, 34},
  {cont__std__atomic_write_to_17, &frame__std__atomic_write_to_6, 1652, 1652, 34, 34},
  {entry__std__atomic_write_to_3, NULL, 1647, 1647, 12, 26},
  {cont__std__atomic_write_to_4, &frame__std__atomic_write_to_3, 1647, 1647, 12, 30},
  {cont__std__atomic_write_to_5, &frame__std__atomic_write_to_3, 1647, 1652, 9, 34},
  {entry__std__atomic_write_to_21, NULL, 1653, 1653, 39, 49},
  {entry__std__atomic_write_to_1, NULL, 1646, 1646, 3, 22},
  {cont__std__atomic_write_to_2, &frame__std__atomic_write_to_1, 1647, 1652, 3, 34},
  {cont__std__atomic_write_to_18, &frame__std__atomic_write_to_1, 1653, 1653, 6, 31},
  {cont__std__atomic_write_to_19, &frame__std__atomic_write_to_1, 1653, 1653, 6, 36},
  {cont__std__atomic_write_to_20, &frame__std__atomic_write_to_1, 1653, 1653, 3, 49},
  {cont__std__atomic_write_to_22, &frame__std__atomic_write_to_1, 1653, 1653, 49, 49},
  {entry__std__load_file_6, NULL, 1678, 1678, 11, 34},
  {cont__std__load_file_7, &frame__std__load_file_6, 1679, 1679, 14, 34},
  {cont__std__load_file_8, &frame__std__load_file_6, 1679, 1679, 14, 39},
  {cont__std__load_file_9, &frame__std__load_file_6, 1679, 1679, 11, 45},
  {cont__std__load_file_10, &frame__std__load_file_6, 1680, 1680, 11, 32},
  {cont__std__load_file_11, &frame__std__load_file_6, 1680, 1680, 32, 32},
  {entry__std__load_file_5, NULL, 1677, 1680, 9, 32},
  {cont__std__load_file_12, &frame__std__load_file_5, 1680, 1680, 32, 32},
  {entry__std__load_file_4, NULL, 1676, 1680, 7, 33},
  {cont__std__load_file_13, &frame__std__load_file_4, 1681, 1681, 7, 14},
  {cont__std__load_file_14, &frame__std__load_file_4, 1682, 1682, 7, 12},
  {entry__std__load_file_15, NULL, 1683, 1683, 5, 16},
  {entry__std__load_file_1, NULL, 1672, 1672, 3, 36},
  {cont__std__load_file_2, &frame__std__load_file_1, 1674, 1674, 5, 17},
  {cont__std__load_file_3, &frame__std__load_file_1, 1673, 1683, 3, 16},
  {entry__std__save_file_7, NULL, 1712, 1712, 11, 26},
  {cont__std__save_file_8, &frame__std__save_file_7, 1713, 1713, 11, 18},
  {entry__std__save_file_11, NULL, 1715, 1715, 39, 47},
  {cont__std__save_file_12, &frame__std__save_file_11, 1715, 1715, 39, 47},
  {entry__std__save_file_9, NULL, 1715, 1715, 18, 34},
  {cont__std__save_file_10, &frame__std__save_file_9, 1715, 1715, 18, 47},
  {cont__std__save_file_13, &frame__std__save_file_9, 1715, 1715, 11, 47},
  {entry__std__save_file_4, NULL, 1711, 1711, 9, 34},
  {cont__std__save_file_5, &frame__std__save_file_4, 1711, 1711, 9, 39},
  {cont__std__save_file_6, &frame__std__save_file_4, 1710, 1715, 7, 48},
  {entry__std__save_file_17, NULL, 1718, 1719, 15, 49},
  {cont__std__save_file_19, &frame__std__save_file_17, 1718, 1719, 9, 49},
  {entry__std__save_file_14, NULL, 1717, 1717, 10, 35},
  {cont__std__save_file_15, &frame__std__save_file_14, 1717, 1717, 10, 40},
  {cont__std__save_file_16, &frame__std__save_file_14, 1717, 1719, 7, 50},
  {cont__std__save_file_20, &frame__std__save_file_14, 1720, 1720, 7, 18},
  {entry__std__save_file_1, NULL, 1707, 1707, 3, 26},
  {cont__std__save_file_2, &frame__std__save_file_1, 1709, 1709, 5, 17},
  {cont__std__save_file_3, &frame__std__save_file_1, 1708, 1720, 3, 19},
  {cont__std__save_file_21, &frame__std__save_file_1, 1720, 1720, 19, 19},
  {entry__types__file_descriptor__flush_1, NULL, 1725, 1740, 3, 2},
  {entry__ioctl_value_1, NULL, 1743, 1755, 3, 2},
  {entry__types__file_descriptor__std__ioctl_8, NULL, 1769, 1770, 9, 23},
  {entry__types__file_descriptor__std__ioctl_4, NULL, 1768, 1768, 10, 38},
  {cont__types__file_descriptor__std__ioctl_5, &frame__types__file_descriptor__std__ioctl_4, 1768, 1768, 10, 43},
  {cont__types__file_descriptor__std__ioctl_6, &frame__types__file_descriptor__std__ioctl_4, 1768, 1768, 10, 43},
  {cont__types__file_descriptor__std__ioctl_7, &frame__types__file_descriptor__std__ioctl_4, 1768, 1770, 7, 24},
  {entry__types__file_descriptor__std__ioctl_10, NULL, 1772, 1772, 14, 42},
  {cont__types__file_descriptor__std__ioctl_11, &frame__types__file_descriptor__std__ioctl_10, 1772, 1772, 7, 42},
  {entry__types__file_descriptor__std__ioctl_1, NULL, 1767, 1767, 5, 30},
  {cont__types__file_descriptor__std__ioctl_2, &frame__types__file_descriptor__std__ioctl_1, 1767, 1767, 5, 35},
  {cont__types__file_descriptor__std__ioctl_3, &frame__types__file_descriptor__std__ioctl_1, 1766, 1772, 3, 43},
  {cont__types__file_descriptor__std__ioctl_12, &frame__types__file_descriptor__std__ioctl_1, 1772, 1772, 43, 43},
  {entry__types__file_descriptor__std__get_terminal_size_1, NULL, 1780, 1801, 3, 2},
  {entry__posix_unlink_1, NULL, 1804, 1815, 3, 2},
  {entry__std__delete_file_8, NULL, 1827, 1828, 15, 51},
  {cont__std__delete_file_11, &frame__std__delete_file_8, 1827, 1828, 9, 51},
  {entry__std__delete_file_4, NULL, 1826, 1826, 10, 31},
  {cont__std__delete_file_5, &frame__std__delete_file_4, 1826, 1826, 10, 36},
  {cont__std__delete_file_6, &frame__std__delete_file_4, 1826, 1826, 10, 36},
  {cont__std__delete_file_7, &frame__std__delete_file_4, 1826, 1828, 7, 52},
  {entry__std__delete_file_12, NULL, 1830, 1830, 14, 35},
  {cont__std__delete_file_13, &frame__std__delete_file_12, 1830, 1830, 14, 40},
  {cont__std__delete_file_14, &frame__std__delete_file_12, 1830, 1830, 7, 40},
  {entry__std__delete_file_1, NULL, 1825, 1825, 5, 30},
  {cont__std__delete_file_2, &frame__std__delete_file_1, 1825, 1825, 5, 35},
  {cont__std__delete_file_3, &frame__std__delete_file_1, 1824, 1830, 3, 41},
  {cont__std__delete_file_15, &frame__std__delete_file_1, 1830, 1830, 41, 41},
  {entry__wait_for_io_ready_1, NULL, 1833, 1994, 3, 2},
  {entry__std__get_pid_1, NULL, 1999, 2002, 3, 2},
  {entry__std__wait_pid_1, NULL, 2011, 2023, 3, 2},
  {entry__std__wait_for_io_1, NULL, 2034, 2045, 3, 17},
  {cont__std__wait_for_io_2, &frame__std__wait_for_io_1, 2049, 2049, 5, 36},
  {cont__std__wait_for_io_3, &frame__std__wait_for_io_1, 2050, 2050, 23, 35},
  {cont__std__wait_for_io_4, &frame__std__wait_for_io_1, 2050, 2050, 37, 60},
  {cont__std__wait_for_io_5, &frame__std__wait_for_io_1, 2050, 2050, 5, 61},
  {cont__std__wait_for_io_6, &frame__std__wait_for_io_1, 2051, 2051, 23, 46},
  {cont__std__wait_for_io_7, &frame__std__wait_for_io_1, 2051, 2051, 23, 48},
  {cont__std__wait_for_io_8, &frame__std__wait_for_io_1, 2051, 2051, 51, 51},
  {cont__std__wait_for_io_9, &frame__std__wait_for_io_1, 2051, 2051, 5, 52},
  {cont__std__wait_for_io_10, &frame__std__wait_for_io_1, 2046, 2052, 3, 11},
  {entry__std__current_path_1, NULL, 2057, 2075, 3, 2},
  {entry__std__chdir_1, NULL, 2082, 2093, 3, 2},
  {entry__std__change_directory_5, NULL, 2102, 2103, 11, 60},
  {cont__std__change_directory_8, &frame__std__change_directory_5, 2102, 2103, 5, 60},
  {entry__std__change_directory_1, NULL, 2101, 2101, 6, 21},
  {cont__std__change_directory_2, &frame__std__change_directory_1, 2101, 2101, 6, 26},
  {cont__std__change_directory_3, &frame__std__change_directory_1, 2101, 2101, 6, 26},
  {cont__std__change_directory_4, &frame__std__change_directory_1, 2101, 2103, 3, 61},
  {entry__clib_mkdir_1, NULL, 2106, 2118, 3, 2},
  {entry__std__mkdir_2, NULL, 2138, 2138, 28, 36},
  {cont__std__mkdir_3, &frame__std__mkdir_2, 2138, 2138, 16, 37},
  {cont__std__mkdir_5, &frame__std__mkdir_2, 2138, 2138, 7, 37},
  {cont__std__mkdir_7, &frame__std__mkdir_2, 2139, 2139, 7, 42},
  {cont__std__mkdir_9, &frame__std__mkdir_2, 2140, 2140, 7, 19},
  {cont__std__mkdir_11, &frame__std__mkdir_2, 2136, 2140, 5, 19},
  {entry__std__mkdir_22, NULL, 2146, 2146, 47, 53},
  {cont__std__mkdir_23, &frame__std__mkdir_22, 2146, 2146, 47, 63},
  {cont__std__mkdir_24, &frame__std__mkdir_22, 2146, 2146, 47, 63},
  {cont__std__mkdir_25, &frame__std__mkdir_22, 2146, 2146, 47, 63},
  {entry__std__mkdir_18, NULL, 2145, 2145, 7, 40},
  {cont__std__mkdir_19, &frame__std__mkdir_18, 2146, 2146, 10, 38},
  {cont__std__mkdir_20, &frame__std__mkdir_18, 2146, 2146, 10, 42},
  {cont__std__mkdir_21, &frame__std__mkdir_18, 2146, 2146, 10, 63},
  {cont__std__mkdir_26, &frame__std__mkdir_18, 2146, 2146, 7, 68},
  {entry__std__mkdir_13, NULL, 2143, 2143, 31, 31},
  {cont__std__mkdir_14, &frame__std__mkdir_13, 2143, 2143, 5, 31},
  {cont__std__mkdir_15, &frame__std__mkdir_13, 2144, 2144, 8, 25},
  {cont__std__mkdir_16, &frame__std__mkdir_13, 2144, 2144, 8, 25},
  {cont__std__mkdir_17, &frame__std__mkdir_13, 2144, 2146, 5, 68},
  {entry__std__mkdir_31, NULL, 2149, 2149, 32, 57},
  {entry__std__mkdir_36, NULL, 2151, 2151, 40, 46},
  {cont__std__mkdir_37, &frame__std__mkdir_36, 2151, 2151, 40, 56},
  {cont__std__mkdir_38, &frame__std__mkdir_36, 2151, 2151, 40, 56},
  {entry__std__mkdir_35, NULL, 2151, 2151, 12, 56},
  {cont__std__mkdir_39, &frame__std__mkdir_35, 2151, 2151, 5, 61},
  {entry__std__mkdir_1, NULL, 2130, 2130, 5, 16},
  {cont__std__mkdir_27, &frame__std__mkdir_1, 2132, 2132, 5, 19},
  {cont__std__mkdir_28, &frame__std__mkdir_1, 2129, 2133, 3, 29},
  {cont__std__mkdir_29, &frame__std__mkdir_1, 2148, 2148, 3, 26},
  {cont__std__mkdir_30, &frame__std__mkdir_1, 2149, 2149, 3, 57},
  {cont__std__mkdir_32, &frame__std__mkdir_1, 2150, 2150, 6, 26},
  {cont__std__mkdir_33, &frame__std__mkdir_1, 2150, 2150, 6, 30},
  {cont__std__mkdir_34, &frame__std__mkdir_1, 2150, 2151, 3, 61},
  {entry__std__create_directory_5, NULL, 2161, 2162, 11, 49},
  {cont__std__create_directory_7, &frame__std__create_directory_5, 2161, 2162, 5, 49},
  {entry__std__create_directory_1, NULL, 2160, 2160, 6, 26},
  {cont__std__create_directory_2, &frame__std__create_directory_1, 2160, 2160, 6, 31},
  {cont__std__create_directory_3, &frame__std__create_directory_1, 2160, 2160, 6, 31},
  {cont__std__create_directory_4, &frame__std__create_directory_1, 2160, 2162, 3, 50},
  {entry__std__fullname_3, NULL, 2171, 2171, 22, 35},
  {cont__std__fullname_4, &frame__std__fullname_3, 2171, 2171, 5, 49},
  {cont__std__fullname_6, &frame__std__fullname_3, 2171, 2171, 49, 49},
  {entry__std__fullname_9, NULL, 2172, 2172, 37, 54},
  {cont__std__fullname_10, &frame__std__fullname_9, 2172, 2172, 54, 54},
  {entry__std__fullname_20, NULL, 2180, 2180, 19, 38},
  {cont__std__fullname_21, &frame__std__fullname_20, 2180, 2180, 19, 53},
  {cont__std__fullname_22, &frame__std__fullname_20, 2180, 2180, 14, 54},
  {cont__std__fullname_23, &frame__std__fullname_20, 2180, 2180, 9, 62},
  {cont__std__fullname_25, &frame__std__fullname_20, 2180, 2180, 9, 68},
  {cont__std__fullname_26, &frame__std__fullname_20, 2178, 2180, 7, 68},
  {cont__std__fullname_27, &frame__std__fullname_20, 2181, 2181, 10, 34},
  {cont__std__fullname_28, &frame__std__fullname_20, 2181, 2181, 7, 40},
  {entry__std__fullname_19, NULL, 2176, 2181, 5, 40},
  {cont__std__fullname_29, &frame__std__fullname_19, 2181, 2181, 40, 40},
  {entry__std__fullname_32, NULL, 2182, 2182, 46, 46},
  {cont__std__fullname_33, &frame__std__fullname_32, 2182, 2182, 27, 46},
  {cont__std__fullname_34, &frame__std__fullname_32, 2182, 2182, 46, 46},
  {entry__std__fullname_1, NULL, 2170, 2170, 10, 34},
  {cont__std__fullname_2, &frame__std__fullname_1, 2170, 2171, 3, 49},
  {cont__std__fullname_7, &frame__std__fullname_1, 2172, 2172, 10, 34},
  {cont__std__fullname_8, &frame__std__fullname_1, 2172, 2172, 3, 54},
  {cont__std__fullname_11, &frame__std__fullname_1, 2173, 2173, 25, 34},
  {cont__std__fullname_13, &frame__std__fullname_1, 2173, 2173, 25, 40},
  {cont__std__fullname_14, &frame__std__fullname_1, 2173, 2173, 3, 40},
  {cont__std__fullname_15, &frame__std__fullname_1, 2174, 2174, 25, 35},
  {cont__std__fullname_17, &frame__std__fullname_1, 2174, 2174, 3, 35},
  {cont__std__fullname_18, &frame__std__fullname_1, 2175, 2181, 3, 41},
  {cont__std__fullname_30, &frame__std__fullname_1, 2182, 2182, 10, 24},
  {cont__std__fullname_31, &frame__std__fullname_1, 2182, 2182, 3, 46},
  {cont__std__fullname_35, &frame__std__fullname_1, 2183, 2183, 3, 13},
  {entry__std__opendir_1, NULL, 2270, 2282, 3, 2},
  {entry__types__DIR__close_1, NULL, 2287, 2298, 3, 2},
  {entry__types__DIR__get_1, NULL, 2303, 2322, 3, 2},
  {entry__types__dirent__filename_of_1, NULL, 2327, 2331, 3, 2},
  {entry__types__dirent__inode_of_1, NULL, 2336, 2340, 3, 2},
  {entry__types__dirent__file_type_of_1, NULL, 2345, 2349, 3, 2},
  {entry__types__dirent__fullname_of_1, NULL, 2357, 2357, 13, 29},
  {cont__types__dirent__fullname_of_2, &frame__types__dirent__fullname_of_1, 2357, 2357, 35, 51},
  {cont__types__dirent__fullname_of_3, &frame__types__dirent__fullname_of_1, 2357, 2357, 6, 52},
  {cont__types__dirent__fullname_of_4, &frame__types__dirent__fullname_of_1, 2357, 2357, 3, 52},
  {entry__types__dirent__is_a_directory_1, NULL, 2365, 2365, 6, 23},
  {cont__types__dirent__is_a_directory_2, &frame__types__dirent__is_a_directory_1, 2365, 2365, 6, 41},
  {cont__types__dirent__is_a_directory_3, &frame__types__dirent__is_a_directory_1, 2365, 2365, 3, 41},
  {entry__types__dirent__is_a_regular_file_1, NULL, 2373, 2373, 6, 23},
  {cont__types__dirent__is_a_regular_file_2, &frame__types__dirent__is_a_regular_file_1, 2373, 2373, 6, 44},
  {cont__types__dirent__is_a_regular_file_3, &frame__types__dirent__is_a_regular_file_1, 2373, 2373, 3, 44},
  {entry__types__dirent__is_a_link_1, NULL, 2381, 2381, 6, 23},
  {cont__types__dirent__is_a_link_2, &frame__types__dirent__is_a_link_1, 2381, 2381, 6, 36},
  {cont__types__dirent__is_a_link_3, &frame__types__dirent__is_a_link_1, 2381, 2381, 3, 36},
  {entry__std__directory_16, NULL, 2402, 2402, 11, 29},
  {cont__std__directory_17, &frame__std__directory_16, 2402, 2402, 29, 29},
  {entry__std__directory_18, NULL, 2400, 2400, 11, 14},
  {entry__std__directory_8, NULL, 2395, 2395, 7, 21},
  {cont__std__directory_9, &frame__std__directory_8, 2396, 2396, 14, 29},
  {cont__std__directory_10, &frame__std__directory_8, 2396, 2396, 7, 35},
  {cont__std__directory_11, &frame__std__directory_8, 2398, 2398, 9, 26},
  {cont__std__directory_12, &frame__std__directory_8, 2399, 2399, 9, 17},
  {cont__std__directory_15, &frame__std__directory_8, 2397, 2402, 7, 30},
  {entry__std__directory_7, NULL, 2394, 2402, 5, 31},
  {cont__std__directory_19, &frame__std__directory_7, 2402, 2402, 31, 31},
  {entry__std__directory_23, NULL, 2405, 2405, 36, 52},
  {cont__std__directory_24, &frame__std__directory_23, 2405, 2405, 56, 73},
  {cont__std__directory_25, &frame__std__directory_23, 2405, 2405, 36, 73},
  {cont__std__directory_26, &frame__std__directory_23, 2405, 2405, 33, 73},
  {entry__std__directory_22, NULL, 2405, 2405, 5, 73},
  {cont__std__directory_27, &frame__std__directory_22, 2405, 2405, 73, 73},
  {entry__std__directory_1, NULL, 2390, 2390, 27, 38},
  {cont__std__directory_2, &frame__std__directory_1, 2390, 2390, 3, 47},
  {cont__std__directory_3, &frame__std__directory_1, 2391, 2391, 3, 18},
  {cont__std__directory_4, &frame__std__directory_1, 2392, 2392, 21, 38},
  {cont__std__directory_5, &frame__std__directory_1, 2392, 2392, 3, 39},
  {cont__std__directory_6, &frame__std__directory_1, 2393, 2402, 3, 32},
  {cont__std__directory_20, &frame__std__directory_1, 2403, 2403, 3, 11},
  {cont__std__directory_21, &frame__std__directory_1, 2404, 2405, 3, 73},
  {cont__std__directory_28, &frame__std__directory_1, 2406, 2406, 3, 12},
  {entry__std__get_network_addresses_1, NULL, 2502, 2538, 3, 2},
  {entry__std__get_network_address_1, NULL, 2543, 2568, 3, 2},
  {entry__types__addrinfo__connect_1, NULL, 2573, 2586, 3, 2},
  {entry__types__string__connect_1, NULL, 2595, 2595, 11, 34},
  {cont__types__string__connect_2, &frame__types__string__connect_1, 2595, 2595, 3, 39},
  {entry__types__addrinfo__listen_1, NULL, 2600, 2622, 3, 2},
  {entry__types__string__listen_1, NULL, 2631, 2631, 10, 33},
  {cont__types__string__listen_2, &frame__types__string__listen_1, 2631, 2631, 3, 38},
  {entry__types__file_descriptor__accept_1, NULL, 2636, 2645, 3, 2},
  {entry__std__write_1, NULL, 2655, 2655, 26, 38},
  {cont__std__write_2, &frame__std__write_1, 2655, 2655, 26, 46},
  {cont__std__write_3, &frame__std__write_1, 2655, 2655, 3, 46},
  {entry__std__writeln_1, NULL, 2665, 2665, 3, 20},
  {entry__std__ewrite_1, NULL, 2676, 2676, 33, 45},
  {cont__std__ewrite_2, &frame__std__ewrite_1, 2676, 2676, 33, 53},
  {cont__std__ewrite_3, &frame__std__ewrite_1, 2676, 2676, 3, 53},
  {entry__std__ewriteln_1, NULL, 2685, 2685, 3, 21},
  {entry__std__read_1, NULL, 2693, 2693, 3, 26},
  {entry__std__readln_5, NULL, 2704, 2704, 25, 33},
  {cont__std__readln_6, &frame__std__readln_5, 2704, 2704, 25, 33},
  {entry__std__readln_8, NULL, 2704, 2704, 36, 45},
  {entry__std__readln_2, NULL, 2703, 2703, 5, 15},
  {cont__std__readln_3, &frame__std__readln_2, 2704, 2704, 8, 20},
  {cont__std__readln_4, &frame__std__readln_2, 2704, 2704, 8, 33},
  {cont__std__readln_7, &frame__std__readln_2, 2704, 2704, 5, 45},
  {cont__std__readln_9, &frame__std__readln_2, 2705, 2705, 5, 19},
  {cont__std__readln_10, &frame__std__readln_2, 2705, 2705, 19, 19},
  {entry__std__readln_1, NULL, 2702, 2705, 3, 19},
  {cont__std__readln_11, &frame__std__readln_1, 2705, 2705, 19, 19},
  {entry__std__load_9, NULL, 2717, 2717, 9, 14},
  {entry__std__load_10, NULL, 2719, 2720, 17, 45},
  {cont__std__load_13, &frame__std__load_10, 2719, 2720, 11, 45},
  {entry__std__load_4, NULL, 2716, 2716, 9, 41},
  {cont__std__load_8, &frame__std__load_4, 2715, 2720, 7, 47},
  {entry__std__load_14, NULL, 2722, 2722, 7, 24},
  {entry__std__load_1, NULL, 2714, 2714, 5, 35},
  {cont__std__load_3, &frame__std__load_1, 2713, 2722, 3, 25},
  {entry__std__save_9, NULL, 2735, 2735, 26, 34},
  {cont__std__save_10, &frame__std__save_9, 2735, 2735, 20, 39},
  {entry__std__save_4, NULL, 2734, 2734, 32, 32},
  {cont__std__save_5, &frame__std__save_4, 2734, 2734, 5, 33},
  {cont__std__save_6, &frame__std__save_4, 2735, 2735, 8, 17},
  {cont__std__save_7, &frame__std__save_4, 2735, 2735, 8, 17},
  {cont__std__save_8, &frame__std__save_4, 2735, 2735, 5, 39},
  {entry__std__save_1, NULL, 2732, 2732, 27, 41},
  {cont__std__save_2, &frame__std__save_1, 2732, 2732, 3, 62},
  {cont__std__save_3, &frame__std__save_1, 2733, 2735, 3, 39},
  {cont__std__save_11, &frame__std__save_1, 2736, 2736, 22, 35},
  {cont__std__save_12, &frame__std__save_1, 2736, 2736, 3, 35}
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
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
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
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
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
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
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
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
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
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
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
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
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
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
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
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
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
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
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
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
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
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
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
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
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
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
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
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
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
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
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
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
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
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
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
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
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
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
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
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
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
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
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
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
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
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
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
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
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
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
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
static NODE *number__0o755;
static NODE *character__47;
static NODE *number__0;
static NODE *number__1;
static NODE *number__2;
static NODE *number__0x1000000;

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
  // 43: extern $wget "wget"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__2c0ae88b5d487d4d;
  result_count = 1;
  myself = get__extern();
  func = myself->type;
  frame->cont = cont__196_2;
}
static void cont__196_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._wget, arguments->slots[0]);
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__raise_error_1(void) {
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
  // 902: $$info ""
  ((CELL *)frame->slots[2])->contents /* info */ = empty_string;
  // 903: ... : (arg) write_to &info "@(key_of(arg)) = @(value_of(arg))@nl;"
  frame->slots[3] /* temp__1 */ = create_closure(entry__std__raise_error_2, 1);
  // 903: for_each args: (arg) write_to &info "@(key_of(arg)) = @(value_of(arg))@nl;"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* args */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__std__raise_error_9;
}
static void entry__std__raise_error_2(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // arg: 0
  // info: 1
  frame->slots[1] = myself->closure.frame->slots[2]; /* info */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 903: ... key_of(arg)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* arg */;
  result_count = 1;
  myself = get__key_of();
  func = myself->type;
  frame->cont = cont__std__raise_error_3;
}
static void cont__std__raise_error_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 903: ... value_of(arg)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* arg */;
  result_count = 1;
  myself = get__value_of();
  func = myself->type;
  frame->cont = cont__std__raise_error_4;
}
static void cont__std__raise_error_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 903: ... "@(key_of(arg)) = @(value_of(arg))@nl;"
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = string__fa730415fc16bec;
  arguments->slots[2] = frame->slots[4] /* temp__3 */;
  arguments->slots[3] = string__578a5af303e9ceb;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__std__raise_error_7;
}
static void cont__std__raise_error_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 903: ... write_to &info "@(key_of(arg)) = @(value_of(arg))@nl;"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* info */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__write_to();
  func = myself->type;
  frame->cont = cont__std__raise_error_8;
}
static void cont__std__raise_error_8(void) {
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
static void cont__std__raise_error_9(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 904: ... std::errno()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = var.std__errno;
  func = myself->type;
  frame->cont = cont__std__raise_error_10;
}
static void cont__std__raise_error_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 904: ... std::strerror(std::errno())
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = var.std__strerror;
  func = myself->type;
  frame->cont = cont__std__raise_error_11;
}
static void cont__std__raise_error_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 904: ... "@(cmd) failed: @(std::strerror(std::errno()))!@nl;@(info)"
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* cmd */;
  arguments->slots[1] = string__64b427a840d3b445;
  arguments->slots[2] = frame->slots[4] /* temp__2 */;
  arguments->slots[3] = string__2d7981f4e6002bcf;
  arguments->slots[4] = ((CELL *)frame->slots[2])->contents /* info */;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__std__raise_error_14;
}
static void cont__std__raise_error_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 904: raise "@(cmd) failed: @(std::strerror(std::errno()))!@nl;@(info)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__raise();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__check_error_1(void) {
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
  // 917: ... err < 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* err */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__std__check_error_2;
}
static void cont__std__check_error_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 917: if err < 0 raise_error args*
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
static void entry__std__errno_1(void) {
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
static void entry__std__strerror_1(void) {
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
static void entry__std__stat_1(void) {
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
static void entry__std__file_exists_1(void) {
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
static void entry__types__stat__device_of_1(void) {
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
static void entry__types__stat__inode_of_1(void) {
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
static void entry__types__stat__mode_of_1(void) {
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
static void entry__types__stat__link_count_of_1(void) {
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
static void entry__types__stat__user_id_of_1(void) {
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
static void entry__types__stat__group_id_of_1(void) {
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
static void entry__types__stat__size_of_1(void) {
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
static void entry__types__stat__block_size_of_1(void) {
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
static void entry__types__stat__sector_count_of_1(void) {
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
static void entry__types__stat__access_time_of_1(void) {
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
static void entry__types__stat__modification_time_of_1(void) {
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
static void entry__types__stat__status_change_time_of_1(void) {
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
static void entry__types__stat__is_a_directory_1(void) {
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
static void entry__types__stat__is_a_regular_file_1(void) {
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
static void entry__types__stat__is_a_link_1(void) {
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
static void entry__std__create_file_descriptor_1(void) {
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
static void entry__types__file_descriptor__to_integer_1(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  {
    NODE *result__node = (NODE *)(from_int(arguments->slots[0]->file_descriptor.fd));
    arguments = node_p;
    arguments->slots[0] = result__node;
    argument_count = 1;
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
}
static void entry__types__file_descriptor__equal_1(void) {
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
static void entry__types__file_descriptor__less_1(void) {
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
static void entry__types__file_descriptor__hash_1(void) {
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
static void entry__posix_open_1(void) {
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
  flags |= O_CLOEXEC;
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
static void entry__std__open_file_1(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // filename: 0
  // mode: 1
  // fd: 2
  frame->slots[2] /* fd */ = create_cell();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 1372: posix_open $$fd filename mode
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* filename */;
  arguments->slots[1] = frame->slots[1] /* mode */;
  result_count = 1;
  myself = var._posix_open;
  func = myself->type;
  frame->cont = cont__std__open_file_2;
}
static void cont__std__open_file_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* fd */ = arguments->slots[0];
  // 1373: ... fd.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* fd */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__std__open_file_3;
}
static void cont__std__open_file_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 1373: ... : !fd.filename_of fullname(filename)
  frame->slots[4] /* temp__2 */ = create_closure(entry__std__open_file_4, 0);
  // 1373: if fd.is_defined: !fd.filename_of fullname(filename)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__std__open_file_6;
}
static void entry__std__open_file_4(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // fd: 0
  // filename: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* fd */
  frame->slots[1] = myself->closure.frame->slots[0]; /* filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1373: ... !fd.filename_of fullname(filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* filename */;
  result_count = 1;
  myself = get__fullname();
  func = myself->type;
  frame->cont = cont__std__open_file_5;
}
static void cont__std__open_file_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 1373: ... !fd.filename_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* fd */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__filename_of, frame->slots[2] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* fd */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__std__open_file_6(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1374: -> fd
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* fd */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__open_file_for_reading_1(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // filename: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 1398: open_file filename std::O_RDONLY
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* filename */;
  arguments->slots[1] = var.std__O_RDONLY;
  result_count = frame->caller_result_count;
  myself = get__open_file();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__open_file_for_writing_1(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // filename: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 1422: open_file filename std::O_WRONLY
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* filename */;
  arguments->slots[1] = var.std__O_WRONLY;
  result_count = frame->caller_result_count;
  myself = get__open_file();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__open_file_for_reading_and_writing_1(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // filename: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 1448: open_file filename std::O_RDWR
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* filename */;
  arguments->slots[1] = var.std__O_RDWR;
  result_count = frame->caller_result_count;
  myself = get__open_file();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__create_file_1(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // filename: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 1468: ... std::O_CREAT | std::O_TRUNC
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var.std__O_CREAT;
  arguments->slots[1] = var.std__O_TRUNC;
  result_count = 1;
  myself = get__std__bit_or();
  func = myself->type;
  frame->cont = cont__std__create_file_2;
}
static void cont__std__create_file_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 1468: ... std::O_CREAT | std::O_TRUNC | std::O_RDWR
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = var.std__O_RDWR;
  result_count = 1;
  myself = get__std__bit_or();
  func = myself->type;
  frame->cont = cont__std__create_file_3;
}
static void cont__std__create_file_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1468: open_file filename std::O_CREAT | std::O_TRUNC | std::O_RDWR
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* filename */;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__open_file();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__file_descriptor__close_1(void) {
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  int err;
  int fd = arguments->slots[0]->file_descriptor.fd;
  if (event__mode != EM__REPLAY) {
    struct stat statbuf;
    fstat(fd, &statbuf);
    if (S_ISSOCK(statbuf.st_mode)) {
      shutdown(fd, SHUT_RDWR); // fail silent
    }
    do {
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
static void entry__types__file_descriptor__read_some_bytes_from_1(void) {
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
static void entry__types__file_descriptor__read_from_1(void) {
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
  // 1549: ... amount.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* amount */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__types__file_descriptor__read_from_2;
}
static void cont__types__file_descriptor__read_from_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 1549: ... :
  // 1550:   $$buf ""
  // 1551:   while -> amount > 0:
  // 1552:     wait_to_read_from fd
  // 1553:     read_some_bytes_from $some_bytes fd amount
  // 1554:     $len length_of(some_bytes)
  // 1555:     if len == 0: return buf
  // 1556:     append &buf some_bytes
  // 1557:     minus &amount len
  // 1558:   return buf
  frame->slots[4] /* temp__2 */ = create_closure(entry__types__file_descriptor__read_from_3, 0);
  // 1549: if amount.is_defined:
  // 1550:   $$buf ""
  // 1551:   while -> amount > 0:
  // 1552:     wait_to_read_from fd
  // 1553:     read_some_bytes_from $some_bytes fd amount
  // 1554:     $len length_of(some_bytes)
  // 1555:     if len == 0: return buf
  // 1556:     append &buf some_bytes
  // 1557:     minus &amount len
  // 1558:   return buf
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__file_descriptor__read_from_16;
}
static void entry__types__file_descriptor__read_from_3(void) {
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
  // 1550: $$buf ""
  ((CELL *)frame->slots[3])->contents /* buf */ = empty_string;
  // 1551: ... -> amount > 0:
  // 1552:   wait_to_read_from fd
  // 1553:   read_some_bytes_from $some_bytes fd amount
  // 1554:   $len length_of(some_bytes)
  // 1555:   if len == 0: return buf
  // 1556:   append &buf some_bytes
  // 1557:   minus &amount len
  frame->slots[4] /* temp__1 */ = create_closure(entry__types__file_descriptor__read_from_4, 0);
  // 1551: while -> amount > 0:
  // 1552:   wait_to_read_from fd
  // 1553:   read_some_bytes_from $some_bytes fd amount
  // 1554:   $len length_of(some_bytes)
  // 1555:   if len == 0: return buf
  // 1556:   append &buf some_bytes
  // 1557:   minus &amount len
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__while();
  func = myself->type;
  frame->cont = cont__types__file_descriptor__read_from_15;
}
static void entry__types__file_descriptor__read_from_6(void) {
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
  // 1552: wait_to_read_from fd
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd */;
  result_count = 0;
  myself = get__wait_to_read_from();
  func = myself->type;
  frame->cont = cont__types__file_descriptor__read_from_7;
}
static void cont__types__file_descriptor__read_from_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1553: read_some_bytes_from $some_bytes fd amount
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* amount */;
  result_count = 1;
  myself = get__read_some_bytes_from();
  func = myself->type;
  frame->cont = cont__types__file_descriptor__read_from_8;
}
static void cont__types__file_descriptor__read_from_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* some_bytes */, arguments->slots[0]);
  // 1554: $len length_of(some_bytes)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* some_bytes */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__types__file_descriptor__read_from_9;
}
static void cont__types__file_descriptor__read_from_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* len */, arguments->slots[0]);
  // 1555: ... len == 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* len */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__types__file_descriptor__read_from_10;
}
static void cont__types__file_descriptor__read_from_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 1555: ... : return buf
  frame->slots[7] /* temp__2 */ = create_closure(entry__types__file_descriptor__read_from_11, 0);
  // 1555: if len == 0: return buf
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__file_descriptor__read_from_12;
}
static void entry__types__file_descriptor__read_from_11(void) {
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
  // 1555: ... return buf
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* buf */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__file_descriptor__read_from_12(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1556: append &buf some_bytes
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* buf */;
  arguments->slots[1] = frame->slots[4] /* some_bytes */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__types__file_descriptor__read_from_13;
}
static void cont__types__file_descriptor__read_from_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* buf */ = arguments->slots[0];
  // 1557: minus &amount len
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* amount */;
  arguments->slots[1] = frame->slots[5] /* len */;
  result_count = 1;
  myself = get__minus();
  func = myself->type;
  frame->cont = cont__types__file_descriptor__read_from_14;
}
static void cont__types__file_descriptor__read_from_14(void) {
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
static void entry__types__file_descriptor__read_from_4(void) {
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
  // 1551: ... amount > 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* amount */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__types__file_descriptor__read_from_5;
}
static void cont__types__file_descriptor__read_from_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 1551: ... :
  // 1552:   wait_to_read_from fd
  // 1553:   read_some_bytes_from $some_bytes fd amount
  // 1554:   $len length_of(some_bytes)
  // 1555:   if len == 0: return buf
  // 1556:   append &buf some_bytes
  // 1557:   minus &amount len
  frame->slots[5] /* temp__2 */ = create_closure(entry__types__file_descriptor__read_from_6, 0);
  // 1551: ... -> amount > 0:
  // 1552:   wait_to_read_from fd
  // 1553:   read_some_bytes_from $some_bytes fd amount
  // 1554:   $len length_of(some_bytes)
  // 1555:   if len == 0: return buf
  // 1556:   append &buf some_bytes
  // 1557:   minus &amount len
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__types__file_descriptor__read_from_15(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1558: return buf
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* buf */;
  result_count = frame->caller_result_count;
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__file_descriptor__read_from_16(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1559: wait_to_read_from fd
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd */;
  result_count = 0;
  myself = get__wait_to_read_from();
  func = myself->type;
  frame->cont = cont__types__file_descriptor__read_from_17;
}
static void cont__types__file_descriptor__read_from_17(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1560: read_some_bytes_from fd 0x1000000 # 16 MiB limit
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd */;
  arguments->slots[1] = number__0x1000000;
  result_count = frame->caller_result_count;
  myself = get__read_some_bytes_from();
  func = myself->type;
  frame->cont = cont__types__file_descriptor__read_from_18;
}
static void cont__types__file_descriptor__read_from_18(void) {
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__types__file_descriptor__write_some_bytes_to_1(void) {
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
static void entry__file_description_9(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // num: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* num */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1604: ... "<file descriptor @(num)>"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__431630d095799867;
  arguments->slots[1] = frame->slots[0] /* num */;
  arguments->slots[2] = string__578a5af303e9cdf;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__file_description_12;
}
static void cont__file_description_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1604: -> "<file descriptor @(num)>"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__file_description_13(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1599: -> "<stdin>"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__bb740f9b15cb80c4;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__file_description_15(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1601: -> "<stdout>"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__70d8a89c0475db9e;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__file_description_17(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1603: -> "<stderr>"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__64d8a95c0445db9e;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__file_description_4(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // filename: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1594: ... "@quot;@(filename)@quot;"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__578a5af303e9cc3;
  arguments->slots[1] = frame->slots[0] /* filename */;
  arguments->slots[2] = string__578a5af303e9cc3;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__file_description_6;
}
static void cont__file_description_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1594: -> "@quot;@(filename)@quot;"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__file_description_7(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // fd: 0
  // num: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* fd */
  frame->slots[1] /* num */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1596: $num fd.to_integer
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd */;
  result_count = 1;
  myself = get__to_integer();
  func = myself->type;
  frame->cont = cont__file_description_8;
}
static void cont__file_description_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* num */, arguments->slots[0]);
  // 1604: -> "<file descriptor @(num)>"
  frame->slots[2] /* temp__1 */ = create_closure(entry__file_description_9, 0);
  // 1597: case num
  // 1598:   0
  // 1599:   -> "<stdin>"
  // 1600:   1
  // 1601:   -> "<stdout>"
  // 1602:   2
  // 1603:   -> "<stderr>"
  // 1604:   -> "<file descriptor @(num)>"
  argument_count = 8;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* num */;
  arguments->slots[1] = number__0;
  arguments->slots[2] = func__file_description_13;
  arguments->slots[3] = number__1;
  arguments->slots[4] = func__file_description_15;
  arguments->slots[5] = number__2;
  arguments->slots[6] = func__file_description_17;
  arguments->slots[7] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__file_description_1(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // fd: 0
  // filename: 1
  frame->slots[1] /* filename */ = create_future();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 1591: $filename filename_of(fd)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd */;
  result_count = 1;
  myself = get__filename_of();
  func = myself->type;
  frame->cont = cont__file_description_2;
}
static void cont__file_description_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* filename */, arguments->slots[0]);
  // 1593: filename.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* filename */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__file_description_3;
}
static void cont__file_description_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 1594: -> "@quot;@(filename)@quot;"
  frame->slots[3] /* temp__2 */ = create_closure(entry__file_description_4, 0);
  // 1595: :
  // 1596:   $num fd.to_integer
  // 1597:   case num
  // 1598:     0
  // 1599:     -> "<stdin>"
  // 1600:     1
  // 1601:     -> "<stdout>"
  // 1602:     2
  // 1603:     -> "<stderr>"
  // 1604:     -> "<file descriptor @(num)>"
  frame->slots[4] /* temp__3 */ = create_closure(entry__file_description_7, 0);
  // 1592: if
  // 1593:   filename.is_defined
  // 1594:   -> "@quot;@(filename)@quot;"
  // 1595:   :
  // 1596:     $num fd.to_integer
  // 1597:     case num
  // 1598:       0
  // 1599:       -> "<stdin>"
  // 1600:       1
  // 1601:       -> "<stdout>"
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  arguments->slots[2] = frame->slots[4] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__WriteError_1(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // fd: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 1606: ... file_description(fd)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd */;
  result_count = 1;
  myself = var._file_description;
  func = myself->type;
  frame->cont = cont__WriteError_2;
}
static void cont__WriteError_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 1606: ... "Writing to file @(file_description(fd))"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__8138f7c6e352b20e;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__WriteError_4;
}
static void cont__WriteError_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1606: ... raise_error "Writing to file @(file_description(fd))"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__raise_error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__file_descriptor__write_to_1(void) {
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
  // 1621: $$data string(args*)
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[1] /* args */);
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__types__file_descriptor__write_to_2;
}
static void cont__types__file_descriptor__write_to_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* data */ = arguments->slots[0];
  // 1622: ... -> length_of(data) > 0:
  // 1623:   wait_to_write_to fd
  // 1624:   write_some_bytes_to fd data $bytes_written
  // 1625:   if bytes_written < 0:
  // 1626:     if parameter_count_of(return) == 0: WriteError fd
  // 1627:     return false
  // 1628:   range &data bytes_written+1 -1
  frame->slots[4] /* temp__1 */ = create_closure(entry__types__file_descriptor__write_to_3, 0);
  // 1622: while -> length_of(data) > 0:
  // 1623:   wait_to_write_to fd
  // 1624:   write_some_bytes_to fd data $bytes_written
  // 1625:   if bytes_written < 0:
  // 1626:     if parameter_count_of(return) == 0: WriteError fd
  // 1627:     return false
  // 1628:   range &data bytes_written+1 -1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__while();
  func = myself->type;
  frame->cont = cont__types__file_descriptor__write_to_19;
}
static void entry__types__file_descriptor__write_to_6(void) {
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
  // 1623: wait_to_write_to fd
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd */;
  result_count = 0;
  myself = get__wait_to_write_to();
  func = myself->type;
  frame->cont = cont__types__file_descriptor__write_to_7;
}
static void cont__types__file_descriptor__write_to_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1624: write_some_bytes_to fd data $bytes_written
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* data */;
  result_count = 1;
  myself = get__write_some_bytes_to();
  func = myself->type;
  frame->cont = cont__types__file_descriptor__write_to_8;
}
static void cont__types__file_descriptor__write_to_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* bytes_written */, arguments->slots[0]);
  // 1625: ... bytes_written < 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* bytes_written */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__types__file_descriptor__write_to_9;
}
static void cont__types__file_descriptor__write_to_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 1625: ... :
  // 1626:   if parameter_count_of(return) == 0: WriteError fd
  // 1627:   return false
  frame->slots[5] /* temp__2 */ = create_closure(entry__types__file_descriptor__write_to_10, 0);
  // 1625: if bytes_written < 0:
  // 1626:   if parameter_count_of(return) == 0: WriteError fd
  // 1627:   return false
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__file_descriptor__write_to_15;
}
static void entry__types__file_descriptor__write_to_10(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // return: 0
  // fd: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  frame->slots[1] = myself->closure.frame->slots[0]; /* fd */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1626: ... parameter_count_of(return)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* return */;
  result_count = 1;
  myself = get__parameter_count_of();
  func = myself->type;
  frame->cont = cont__types__file_descriptor__write_to_11;
}
static void cont__types__file_descriptor__write_to_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 1626: ... parameter_count_of(return) == 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__types__file_descriptor__write_to_12;
}
static void cont__types__file_descriptor__write_to_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 1626: ... : WriteError fd
  frame->slots[4] /* temp__3 */ = create_closure(entry__types__file_descriptor__write_to_13, 0);
  // 1626: if parameter_count_of(return) == 0: WriteError fd
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__file_descriptor__write_to_14;
}
static void entry__types__file_descriptor__write_to_13(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // fd: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* fd */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1626: ... WriteError fd
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd */;
  result_count = frame->caller_result_count;
  myself = var._WriteError;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__file_descriptor__write_to_14(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1627: return false
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__false();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__file_descriptor__write_to_15(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1628: ... bytes_written+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* bytes_written */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__types__file_descriptor__write_to_16;
}
static void cont__types__file_descriptor__write_to_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 1628: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__types__file_descriptor__write_to_17;
}
static void cont__types__file_descriptor__write_to_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 1628: range &data bytes_written+1 -1
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* data */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  arguments->slots[2] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__types__file_descriptor__write_to_18;
}
static void cont__types__file_descriptor__write_to_18(void) {
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
static void entry__types__file_descriptor__write_to_3(void) {
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
  // 1622: ... length_of(data)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* data */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__types__file_descriptor__write_to_4;
}
static void cont__types__file_descriptor__write_to_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 1622: ... length_of(data) > 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__types__file_descriptor__write_to_5;
}
static void cont__types__file_descriptor__write_to_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 1622: ... :
  // 1623:   wait_to_write_to fd
  // 1624:   write_some_bytes_to fd data $bytes_written
  // 1625:   if bytes_written < 0:
  // 1626:     if parameter_count_of(return) == 0: WriteError fd
  // 1627:     return false
  // 1628:   range &data bytes_written+1 -1
  frame->slots[5] /* temp__3 */ = create_closure(entry__types__file_descriptor__write_to_6, 0);
  // 1622: ... -> length_of(data) > 0:
  // 1623:   wait_to_write_to fd
  // 1624:   write_some_bytes_to fd data $bytes_written
  // 1625:   if bytes_written < 0:
  // 1626:     if parameter_count_of(return) == 0: WriteError fd
  // 1627:     return false
  // 1628:   range &data bytes_written+1 -1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__types__file_descriptor__write_to_19(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1629: ... parameter_count_of(return)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* return */;
  result_count = 1;
  myself = get__parameter_count_of();
  func = myself->type;
  frame->cont = cont__types__file_descriptor__write_to_20;
}
static void cont__types__file_descriptor__write_to_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 1629: ... parameter_count_of(return) == 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__types__file_descriptor__write_to_21;
}
static void cont__types__file_descriptor__write_to_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 1629: ... : return true
  frame->slots[6] /* temp__3 */ = create_closure(entry__types__file_descriptor__write_to_22, 0);
  // 1629: if parameter_count_of(return) == 1: return true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__file_descriptor__write_to_23;
}
static void entry__types__file_descriptor__write_to_22(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1629: ... return true
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__true();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__file_descriptor__write_to_23(void) {
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__std__atomic_write_to_1(void) {
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
  // 1646: $$data string(args*)
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[1] /* args */);
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__std__atomic_write_to_2;
}
static void cont__std__atomic_write_to_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* data */ = arguments->slots[0];
  // 1647: ... -> length_of(data) > 0:
  // 1648:   write_some_bytes_to fd data $bytes_written
  // 1649:   if bytes_written < 0:
  // 1650:     if parameter_count_of(return) == 0: WriteError fd
  // 1651:     return false
  // 1652:   range &data bytes_written+1 -1
  frame->slots[4] /* temp__1 */ = create_closure(entry__std__atomic_write_to_3, 0);
  // 1647: while -> length_of(data) > 0:
  // 1648:   write_some_bytes_to fd data $bytes_written
  // 1649:   if bytes_written < 0:
  // 1650:     if parameter_count_of(return) == 0: WriteError fd
  // 1651:     return false
  // 1652:   range &data bytes_written+1 -1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__while();
  func = myself->type;
  frame->cont = cont__std__atomic_write_to_18;
}
static void entry__std__atomic_write_to_6(void) {
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
  // 1648: write_some_bytes_to fd data $bytes_written
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* data */;
  result_count = 1;
  myself = get__write_some_bytes_to();
  func = myself->type;
  frame->cont = cont__std__atomic_write_to_7;
}
static void cont__std__atomic_write_to_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* bytes_written */, arguments->slots[0]);
  // 1649: ... bytes_written < 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* bytes_written */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__std__atomic_write_to_8;
}
static void cont__std__atomic_write_to_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 1649: ... :
  // 1650:   if parameter_count_of(return) == 0: WriteError fd
  // 1651:   return false
  frame->slots[5] /* temp__2 */ = create_closure(entry__std__atomic_write_to_9, 0);
  // 1649: if bytes_written < 0:
  // 1650:   if parameter_count_of(return) == 0: WriteError fd
  // 1651:   return false
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__std__atomic_write_to_14;
}
static void entry__std__atomic_write_to_9(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // return: 0
  // fd: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  frame->slots[1] = myself->closure.frame->slots[0]; /* fd */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1650: ... parameter_count_of(return)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* return */;
  result_count = 1;
  myself = get__parameter_count_of();
  func = myself->type;
  frame->cont = cont__std__atomic_write_to_10;
}
static void cont__std__atomic_write_to_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 1650: ... parameter_count_of(return) == 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__std__atomic_write_to_11;
}
static void cont__std__atomic_write_to_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 1650: ... : WriteError fd
  frame->slots[4] /* temp__3 */ = create_closure(entry__std__atomic_write_to_12, 0);
  // 1650: if parameter_count_of(return) == 0: WriteError fd
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__std__atomic_write_to_13;
}
static void entry__std__atomic_write_to_12(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // fd: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* fd */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1650: ... WriteError fd
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd */;
  result_count = frame->caller_result_count;
  myself = var._WriteError;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__std__atomic_write_to_13(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1651: return false
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__false();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__std__atomic_write_to_14(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1652: ... bytes_written+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* bytes_written */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__std__atomic_write_to_15;
}
static void cont__std__atomic_write_to_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 1652: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__std__atomic_write_to_16;
}
static void cont__std__atomic_write_to_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 1652: range &data bytes_written+1 -1
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* data */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  arguments->slots[2] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__std__atomic_write_to_17;
}
static void cont__std__atomic_write_to_17(void) {
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
static void entry__std__atomic_write_to_3(void) {
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
  // 1647: ... length_of(data)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* data */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__std__atomic_write_to_4;
}
static void cont__std__atomic_write_to_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 1647: ... length_of(data) > 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__0;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__std__atomic_write_to_5;
}
static void cont__std__atomic_write_to_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 1647: ... :
  // 1648:   write_some_bytes_to fd data $bytes_written
  // 1649:   if bytes_written < 0:
  // 1650:     if parameter_count_of(return) == 0: WriteError fd
  // 1651:     return false
  // 1652:   range &data bytes_written+1 -1
  frame->slots[5] /* temp__3 */ = create_closure(entry__std__atomic_write_to_6, 0);
  // 1647: ... -> length_of(data) > 0:
  // 1648:   write_some_bytes_to fd data $bytes_written
  // 1649:   if bytes_written < 0:
  // 1650:     if parameter_count_of(return) == 0: WriteError fd
  // 1651:     return false
  // 1652:   range &data bytes_written+1 -1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__std__atomic_write_to_18(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1653: ... parameter_count_of(return)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* return */;
  result_count = 1;
  myself = get__parameter_count_of();
  func = myself->type;
  frame->cont = cont__std__atomic_write_to_19;
}
static void cont__std__atomic_write_to_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 1653: ... parameter_count_of(return) == 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__std__atomic_write_to_20;
}
static void cont__std__atomic_write_to_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 1653: ... : return true
  frame->slots[6] /* temp__3 */ = create_closure(entry__std__atomic_write_to_21, 0);
  // 1653: if parameter_count_of(return) == 1: return true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__std__atomic_write_to_22;
}
static void entry__std__atomic_write_to_21(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1653: ... return true
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__true();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__std__atomic_write_to_22(void) {
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__std__load_file_4(void) {
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
  // 1675: $$buf ""
  ((CELL *)frame->slots[1])->contents /* buf */ = empty_string;
  // 1676: ... : (-> break)
  // 1677:   forever:
  // 1678:     read_from fd $some_bytes
  // 1679:     if length_of(some_bytes) == 0 break
  // 1680:     append &buf some_bytes
  frame->slots[2] /* temp__1 */ = create_closure(entry__std__load_file_5, 0);
  // 1676: do: (-> break)
  // 1677:   forever:
  // 1678:     read_from fd $some_bytes
  // 1679:     if length_of(some_bytes) == 0 break
  // 1680:     append &buf some_bytes
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__std__load_file_13;
}
static void entry__std__load_file_5(void) {
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
  // 1677: ... :
  // 1678:   read_from fd $some_bytes
  // 1679:   if length_of(some_bytes) == 0 break
  // 1680:   append &buf some_bytes
  frame->slots[3] /* temp__1 */ = create_closure(entry__std__load_file_6, 0);
  // 1677: forever:
  // 1678:   read_from fd $some_bytes
  // 1679:   if length_of(some_bytes) == 0 break
  // 1680:   append &buf some_bytes
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__forever();
  func = myself->type;
  frame->cont = cont__std__load_file_12;
}
static void entry__std__load_file_6(void) {
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
  // 1678: read_from fd $some_bytes
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd */;
  result_count = 1;
  myself = get__read_from();
  func = myself->type;
  frame->cont = cont__std__load_file_7;
}
static void cont__std__load_file_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* some_bytes */, arguments->slots[0]);
  // 1679: ... length_of(some_bytes)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* some_bytes */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__std__load_file_8;
}
static void cont__std__load_file_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 1679: ... length_of(some_bytes) == 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__std__load_file_9;
}
static void cont__std__load_file_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 1679: if length_of(some_bytes) == 0 break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* break */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__std__load_file_10;
}
static void cont__std__load_file_10(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1680: append &buf some_bytes
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* buf */;
  arguments->slots[1] = frame->slots[3] /* some_bytes */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__std__load_file_11;
}
static void cont__std__load_file_11(void) {
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
static void cont__std__load_file_12(void) {
  myself = frame->slots[0] /* break */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__std__load_file_13(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1681: close fd
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd */;
  result_count = 0;
  myself = get__close();
  func = myself->type;
  frame->cont = cont__std__load_file_14;
}
static void cont__std__load_file_14(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1682: -> buf
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* buf */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__load_file_15(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1683: -> undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__load_file_1(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // filename: 0
  // fd: 1
  frame->slots[1] /* fd */ = create_future();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 1672: open_file_for_reading $fd filename
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* filename */;
  result_count = 1;
  myself = get__open_file_for_reading();
  func = myself->type;
  frame->cont = cont__std__load_file_2;
}
static void cont__std__load_file_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* fd */, arguments->slots[0]);
  // 1674: fd.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* fd */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__std__load_file_3;
}
static void cont__std__load_file_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 1674: ... :
  // 1675:   $$buf ""
  // 1676:   do: (-> break)
  // 1677:     forever:
  // 1678:       read_from fd $some_bytes
  // 1679:       if length_of(some_bytes) == 0 break
  // 1680:       append &buf some_bytes
  // 1681:   close fd
  // 1682:   -> buf
  frame->slots[3] /* temp__2 */ = create_closure(entry__std__load_file_4, 0);
  // 1673: if
  // 1674:   fd.is_defined:
  // 1675:     $$buf ""
  // 1676:     do: (-> break)
  // 1677:       forever:
  // 1678:         read_from fd $some_bytes
  // 1679:         if length_of(some_bytes) == 0 break
  // 1680:         append &buf some_bytes
  // 1681:     close fd
  // 1682:     -> buf
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  arguments->slots[2] = func__std__load_file_15;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__save_file_1(void) {
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
  // 1707: create_file $fd filename
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* filename */;
  result_count = 1;
  myself = get__create_file();
  func = myself->type;
  frame->cont = cont__std__save_file_2;
}
static void cont__std__save_file_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* fd */, arguments->slots[0]);
  // 1709: fd.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* fd */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__std__save_file_3;
}
static void cont__std__save_file_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 1709: ... :
  // 1710:   if
  // 1711:     parameter_count_of(return) == 0:
  // 1712:       write_to fd data
  // 1713:       close fd
  // 1714:     :
  // 1715:       return write_to(fd data) && close(fd)
  frame->slots[5] /* temp__2 */ = create_closure(entry__std__save_file_4, 0);
  // 1716: :
  // 1717:   if parameter_count_of(return) == 0:
  // 1718:     raise "
  // 1719:       Failed to save file "@(filename)@quot;@
  // 1720:   return false
  frame->slots[6] /* temp__3 */ = create_closure(entry__std__save_file_14, 0);
  // 1708: if
  // 1709:   fd.is_defined:
  // 1710:     if
  // 1711:       parameter_count_of(return) == 0:
  // 1712:         write_to fd data
  // 1713:         close fd
  // 1714:       :
  // 1715:         return write_to(fd data) && close(fd)
  // 1716:   :
  // 1717:     if parameter_count_of(return) == 0:
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  arguments->slots[2] = frame->slots[6] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__std__save_file_21;
}
static void entry__std__save_file_7(void) {
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
  // 1712: write_to fd data
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd */;
  arguments->slots[1] = frame->slots[1] /* data */;
  result_count = 0;
  myself = get__write_to();
  func = myself->type;
  frame->cont = cont__std__save_file_8;
}
static void cont__std__save_file_8(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1713: close fd
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd */;
  result_count = frame->caller_result_count;
  myself = get__close();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__save_file_9(void) {
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
  // 1715: ... write_to(fd data)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* fd */;
  arguments->slots[1] = frame->slots[2] /* data */;
  result_count = 1;
  myself = get__write_to();
  func = myself->type;
  frame->cont = cont__std__save_file_10;
}
static void cont__std__save_file_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 1715: ... close(fd)
  frame->slots[5] /* temp__3 */ = create_closure(entry__std__save_file_11, 0);
  // 1715: ... write_to(fd data) && close(fd)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__std__save_file_13;
}
static void entry__std__save_file_11(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // fd: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* fd */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1715: ... close(fd)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd */;
  result_count = 1;
  myself = get__close();
  func = myself->type;
  frame->cont = cont__std__save_file_12;
}
static void cont__std__save_file_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1715: ... close(fd)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__std__save_file_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 1715: return write_to(fd data) && close(fd)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__save_file_4(void) {
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
  // 1711: parameter_count_of(return)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* return */;
  result_count = 1;
  myself = get__parameter_count_of();
  func = myself->type;
  frame->cont = cont__std__save_file_5;
}
static void cont__std__save_file_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 1711: parameter_count_of(return) == 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__std__save_file_6;
}
static void cont__std__save_file_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 1711: ... :
  // 1712:   write_to fd data
  // 1713:   close fd
  frame->slots[5] /* temp__3 */ = create_closure(entry__std__save_file_7, 0);
  // 1714: :
  // 1715:   return write_to(fd data) && close(fd)
  frame->slots[6] /* temp__4 */ = create_closure(entry__std__save_file_9, 0);
  // 1710: if
  // 1711:   parameter_count_of(return) == 0:
  // 1712:     write_to fd data
  // 1713:     close fd
  // 1714:   :
  // 1715:     return write_to(fd data) && close(fd)
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
static void entry__std__save_file_14(void) {
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
  // 1717: ... parameter_count_of(return)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* return */;
  result_count = 1;
  myself = get__parameter_count_of();
  func = myself->type;
  frame->cont = cont__std__save_file_15;
}
static void cont__std__save_file_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 1717: ... parameter_count_of(return) == 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__std__save_file_16;
}
static void cont__std__save_file_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 1717: ... :
  // 1718:   raise "
  // 1719:     Failed to save file "@(filename)@quot;@
  frame->slots[4] /* temp__3 */ = create_closure(entry__std__save_file_17, 0);
  // 1717: if parameter_count_of(return) == 0:
  // 1718:   raise "
  // 1719:     Failed to save file "@(filename)@quot;@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__std__save_file_20;
}
static void entry__std__save_file_17(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // filename: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1718: ... "
  // 1719:   Failed to save file "@(filename)@quot;@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__52b15fd51e05f634;
  arguments->slots[1] = frame->slots[0] /* filename */;
  arguments->slots[2] = string__578a5af303e9cc3;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__std__save_file_19;
}
static void cont__std__save_file_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1718: raise "
  // 1719:   Failed to save file "@(filename)@quot;@
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__raise();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__std__save_file_20(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1720: return false
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__false();
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__std__save_file_21(void) {
  myself = frame->slots[2] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__types__file_descriptor__flush_1(void) {
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
static void entry__ioctl_value_1(void) {
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
static void entry__types__file_descriptor__std__ioctl_1(void) {
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
  // 1767: parameter_count_of(return)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* return */;
  result_count = 1;
  myself = get__parameter_count_of();
  func = myself->type;
  frame->cont = cont__types__file_descriptor__std__ioctl_2;
}
static void cont__types__file_descriptor__std__ioctl_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 1767: parameter_count_of(return) == 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__types__file_descriptor__std__ioctl_3;
}
static void cont__types__file_descriptor__std__ioctl_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 1767: ... :
  // 1768:   if ioctl_value(fd request value) != 0:
  // 1769:     raise "
  // 1770:       IOCTL failed!
  frame->slots[6] /* temp__3 */ = create_closure(entry__types__file_descriptor__std__ioctl_4, 0);
  // 1771: :
  // 1772:   return ioctl_value(fd request value)
  frame->slots[7] /* temp__4 */ = create_closure(entry__types__file_descriptor__std__ioctl_10, 0);
  // 1766: if
  // 1767:   parameter_count_of(return) == 0:
  // 1768:     if ioctl_value(fd request value) != 0:
  // 1769:       raise "
  // 1770:         IOCTL failed!
  // 1771:   :
  // 1772:     return ioctl_value(fd request value)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  arguments->slots[2] = frame->slots[7] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__types__file_descriptor__std__ioctl_12;
}
static void entry__types__file_descriptor__std__ioctl_8(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1769: raise "
  // 1770:   IOCTL failed!
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__9f84c1967610d391;
  result_count = frame->caller_result_count;
  myself = get__raise();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__file_descriptor__std__ioctl_4(void) {
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
  // 1768: ... ioctl_value(fd request value)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fd */;
  arguments->slots[1] = frame->slots[1] /* request */;
  arguments->slots[2] = frame->slots[2] /* value */;
  result_count = 1;
  myself = var._ioctl_value;
  func = myself->type;
  frame->cont = cont__types__file_descriptor__std__ioctl_5;
}
static void cont__types__file_descriptor__std__ioctl_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 1768: ... ioctl_value(fd request value) != 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__3 */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__types__file_descriptor__std__ioctl_6;
}
static void cont__types__file_descriptor__std__ioctl_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 1768: ... ioctl_value(fd request value) != 0
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__types__file_descriptor__std__ioctl_7;
}
static void cont__types__file_descriptor__std__ioctl_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 1768: if ioctl_value(fd request value) != 0:
  // 1769:   raise "
  // 1770:     IOCTL failed!
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = func__types__file_descriptor__std__ioctl_8;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__file_descriptor__std__ioctl_10(void) {
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
  // 1772: ... ioctl_value(fd request value)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* fd */;
  arguments->slots[1] = frame->slots[2] /* request */;
  arguments->slots[2] = frame->slots[3] /* value */;
  result_count = 1;
  myself = var._ioctl_value;
  func = myself->type;
  frame->cont = cont__types__file_descriptor__std__ioctl_11;
}
static void cont__types__file_descriptor__std__ioctl_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 1772: return ioctl_value(fd request value)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__types__file_descriptor__std__ioctl_12(void) {
  myself = frame->slots[3] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__types__file_descriptor__std__get_terminal_size_1(void) {
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
static void entry__posix_unlink_1(void) {
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
static void entry__std__delete_file_1(void) {
  allocate_initialized_frame_gc(2, 6);
  // slot allocations:
  // filename: 0
  // return: 1
  frame->slots[1] /* return */ = create_continuation();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 1825: parameter_count_of(return)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* return */;
  result_count = 1;
  myself = get__parameter_count_of();
  func = myself->type;
  frame->cont = cont__std__delete_file_2;
}
static void cont__std__delete_file_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 1825: parameter_count_of(return) == 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__std__delete_file_3;
}
static void cont__std__delete_file_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 1825: ... :
  // 1826:   if posix_unlink(filename) != 0:
  // 1827:     raise "
  // 1828:       Failed to delete file "@(filename)@quot;!
  frame->slots[4] /* temp__3 */ = create_closure(entry__std__delete_file_4, 0);
  // 1829: :
  // 1830:   return posix_unlink(filename) == 0
  frame->slots[5] /* temp__4 */ = create_closure(entry__std__delete_file_12, 0);
  // 1824: if
  // 1825:   parameter_count_of(return) == 0:
  // 1826:     if posix_unlink(filename) != 0:
  // 1827:       raise "
  // 1828:         Failed to delete file "@(filename)@quot;!
  // 1829:   :
  // 1830:     return posix_unlink(filename) == 0
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  arguments->slots[2] = frame->slots[5] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__std__delete_file_15;
}
static void entry__std__delete_file_8(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // filename: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1827: ... "
  // 1828:   Failed to delete file "@(filename)@quot;!
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__98599da1f95f3503;
  arguments->slots[1] = frame->slots[0] /* filename */;
  arguments->slots[2] = string__fa730c15f216bc6;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__std__delete_file_11;
}
static void cont__std__delete_file_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1827: raise "
  // 1828:   Failed to delete file "@(filename)@quot;!
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__raise();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__delete_file_4(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // filename: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1826: ... posix_unlink(filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* filename */;
  result_count = 1;
  myself = var._posix_unlink;
  func = myself->type;
  frame->cont = cont__std__delete_file_5;
}
static void cont__std__delete_file_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 1826: ... posix_unlink(filename) != 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__std__delete_file_6;
}
static void cont__std__delete_file_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 1826: ... posix_unlink(filename) != 0
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__std__delete_file_7;
}
static void cont__std__delete_file_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 1826: ... :
  // 1827:   raise "
  // 1828:     Failed to delete file "@(filename)@quot;!
  frame->slots[4] /* temp__4 */ = create_closure(entry__std__delete_file_8, 0);
  // 1826: if posix_unlink(filename) != 0:
  // 1827:   raise "
  // 1828:     Failed to delete file "@(filename)@quot;!
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__delete_file_12(void) {
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
  // 1830: ... posix_unlink(filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* filename */;
  result_count = 1;
  myself = var._posix_unlink;
  func = myself->type;
  frame->cont = cont__std__delete_file_13;
}
static void cont__std__delete_file_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 1830: ... posix_unlink(filename) == 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__std__delete_file_14;
}
static void cont__std__delete_file_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 1830: return posix_unlink(filename) == 0
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__std__delete_file_15(void) {
  myself = frame->slots[1] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__wait_for_io_ready_1(void) {
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
    if (timeout < 0.0) timeout = 0.0;
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
static void entry__std__get_pid_1(void) {
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
static void entry__std__wait_pid_1(void) {
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
static void entry__std__wait_for_io_1(void) {
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
  // 2034: wait_for_io_ready
  // 2035:   read_descriptors
  // 2036:   write_descriptors
  // 2037:   except_descriptors
  // 2038:   timeout
  // 2039:   $success
  // 2040:   $child_changed_state
  // 2041:   $window_changed_size
  // 2042:   $input_count
  // 2043:   $output_count
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
  frame->cont = cont__std__wait_for_io_2;
}
static void cont__std__wait_for_io_2(void) {
  if (argument_count < 6) {
    too_few_results_error();
    return;
  }
  allocate_arguments();
  initialize_future(frame->slots[4] /* success */, arguments->slots[0]);
  initialize_future(frame->slots[5] /* child_changed_state */, arguments->slots[1]);
  initialize_future(frame->slots[6] /* window_changed_size */, arguments->slots[2]);
  initialize_future(frame->slots[7] /* input_count */, arguments->slots[3]);
  initialize_future(frame->slots[8] /* output_count */, arguments->slots[4]);
  initialize_future(frame->slots[9] /* exception_count */, arguments->slots[5]);
  initialize_future(frame->slots[10] /* descriptors */, from_arguments(6, argument_count-6));
  // 2049: range(descriptors 1 input_count)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* descriptors */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[7] /* input_count */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__std__wait_for_io_3;
}
static void cont__std__wait_for_io_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 2050: ... input_count+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* input_count */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__std__wait_for_io_4;
}
static void cont__std__wait_for_io_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__3 */ = arguments->slots[0];
  // 2050: ... input_count+output_count
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* input_count */;
  arguments->slots[1] = frame->slots[8] /* output_count */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__std__wait_for_io_5;
}
static void cont__std__wait_for_io_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[14] /* temp__4 */ = arguments->slots[0];
  // 2050: range(descriptors input_count+1 input_count+output_count)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* descriptors */;
  arguments->slots[1] = frame->slots[13] /* temp__3 */;
  arguments->slots[2] = frame->slots[14] /* temp__4 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__std__wait_for_io_6;
}
static void cont__std__wait_for_io_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__2 */ = arguments->slots[0];
  // 2051: ... input_count+output_count
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* input_count */;
  arguments->slots[1] = frame->slots[8] /* output_count */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__std__wait_for_io_7;
}
static void cont__std__wait_for_io_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[17] /* temp__7 */ = arguments->slots[0];
  // 2051: ... input_count+output_count+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[17] /* temp__7 */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__std__wait_for_io_8;
}
static void cont__std__wait_for_io_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[16] /* temp__6 */ = arguments->slots[0];
  // 2051: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__std__wait_for_io_9;
}
static void cont__std__wait_for_io_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[18] /* temp__8 */ = arguments->slots[0];
  // 2051: range(descriptors input_count+output_count+1 -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* descriptors */;
  arguments->slots[1] = frame->slots[16] /* temp__6 */;
  arguments->slots[2] = frame->slots[18] /* temp__8 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__std__wait_for_io_10;
}
static void cont__std__wait_for_io_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[15] /* temp__5 */ = arguments->slots[0];
  // 2046: ->
  // 2047:   child_changed_state
  // 2048:   window_changed_size
  // 2049:   range(descriptors 1 input_count)
  // 2050:   range(descriptors input_count+1 input_count+output_count)
  // 2051:   range(descriptors input_count+output_count+1 -1)
  // 2052:   success
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
static void entry__std__current_path_1(void) {
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
static void entry__std__chdir_1(void) {
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
static void entry__std__change_directory_5(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // path: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* path */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 2102: ... "
  // 2103:   Failed to change current directory to "@(path)@quot;!@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__6e87e13bb5f5e5b7;
  arguments->slots[1] = frame->slots[0] /* path */;
  arguments->slots[2] = string__2d7981f4e6182be4;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__std__change_directory_8;
}
static void cont__std__change_directory_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 2102: Error "
  // 2103:   Failed to change current directory to "@(path)@quot;!@
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__change_directory_1(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // path: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 2101: ... std::chdir(path)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* path */;
  result_count = 1;
  myself = var.std__chdir;
  func = myself->type;
  frame->cont = cont__std__change_directory_2;
}
static void cont__std__change_directory_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 2101: ... std::chdir(path) != 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__std__change_directory_3;
}
static void cont__std__change_directory_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 2101: ... std::chdir(path) != 0
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__std__change_directory_4;
}
static void cont__std__change_directory_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 2101: ... :
  // 2102:   Error "
  // 2103:     Failed to change current directory to "@(path)@quot;!@
  frame->slots[4] /* temp__4 */ = create_closure(entry__std__change_directory_5, 0);
  // 2101: if std::chdir(path) != 0:
  // 2102:   Error "
  // 2103:     Failed to change current directory to "@(path)@quot;!@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__clib_mkdir_1(void) {
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
static void entry__std__mkdir_35(void) {
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
  // 2151: ... do_create_parent_folders && errno() == EEXIST
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* do_create_parent_folders */;
  arguments->slots[1] = func__std__mkdir_36;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__std__mkdir_39;
}
static void entry__std__mkdir_36(void) {
  allocate_initialized_frame_gc(0, 2);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 2151: ... errno()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__errno();
  func = myself->type;
  frame->cont = cont__std__mkdir_37;
}
static void cont__std__mkdir_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 2151: ... errno() == EEXIST
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  arguments->slots[1] = get__EEXIST();
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__std__mkdir_38;
}
static void cont__std__mkdir_38(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 2151: ... errno() == EEXIST
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__std__mkdir_39(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 2151: unless do_create_parent_folders && errno() == EEXIST fail
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* fail */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__mkdir_1(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(2, 9);
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
  // 2135: ... :
  // 2136:   raise_error
  // 2137:     "mkdir"
  // 2138:     "MODE" = string("0o" oct(mode))
  // 2139:     "PARENTS" = do_create_parent_folders
  // 2140:     "path" = path
  frame->slots[6] /* temp__1 */ = create_closure(entry__std__mkdir_2, 0);
  // 2135: $fail:
  // 2136:   raise_error
  // 2137:     "mkdir"
  // 2138:     "MODE" = string("0o" oct(mode))
  // 2139:     "PARENTS" = do_create_parent_folders
  // 2140:     "path" = path
  initialize_future(frame->slots[4] /* fail */, frame->slots[6] /* temp__1 */);
  // 2142: ... : ($partial_path)
  // 2143:   before &partial_path '/' -1
  // 2144:   if partial_path != "":
  // 2145:     create_parent_folders partial_path
  // 2146:     if clib_mkdir(partial_path mode) < 0 && errno() != EEXIST fail
  frame->slots[6] /* temp__1 */ = create_closure(entry__std__mkdir_13, 1);
  // 2142: $create_parent_folders: ($partial_path)
  // 2143:   before &partial_path '/' -1
  // 2144:   if partial_path != "":
  // 2145:     create_parent_folders partial_path
  // 2146:     if clib_mkdir(partial_path mode) < 0 && errno() != EEXIST fail
  initialize_future(frame->slots[5] /* create_parent_folders */, frame->slots[6] /* temp__1 */);
  // 2130: MODE = 0o755
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__MODE();
  arguments->slots[1] = number__0o755;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__std__mkdir_27;
}
static void entry__std__mkdir_18(void) {
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
  // 2145: create_parent_folders partial_path
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* partial_path */;
  result_count = 0;
  myself = frame->slots[0] /* create_parent_folders */;
  func = myself->type;
  frame->cont = cont__std__mkdir_19;
}
static void cont__std__mkdir_19(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 2146: ... clib_mkdir(partial_path mode)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* partial_path */;
  arguments->slots[1] = frame->slots[2] /* mode */;
  result_count = 1;
  myself = var._clib_mkdir;
  func = myself->type;
  frame->cont = cont__std__mkdir_20;
}
static void cont__std__mkdir_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 2146: ... clib_mkdir(partial_path mode) < 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__3 */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__std__mkdir_21;
}
static void cont__std__mkdir_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 2146: ... clib_mkdir(partial_path mode) < 0 && errno() != EEXIST
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  arguments->slots[1] = func__std__mkdir_22;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__std__mkdir_26;
}
static void entry__std__mkdir_22(void) {
  allocate_initialized_frame_gc(0, 3);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 2146: ... errno()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__errno();
  func = myself->type;
  frame->cont = cont__std__mkdir_23;
}
static void cont__std__mkdir_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 2146: ... errno() != EEXIST
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__3 */;
  arguments->slots[1] = get__EEXIST();
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__std__mkdir_24;
}
static void cont__std__mkdir_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 2146: ... errno() != EEXIST
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__std__mkdir_25;
}
static void cont__std__mkdir_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 2146: ... errno() != EEXIST
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__std__mkdir_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 2146: if clib_mkdir(partial_path mode) < 0 && errno() != EEXIST fail
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* fail */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__mkdir_2(void) {
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
  // 2138: ... oct(mode)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mode */;
  result_count = 1;
  myself = get__oct();
  func = myself->type;
  frame->cont = cont__std__mkdir_3;
}
static void cont__std__mkdir_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 2138: ... string("0o" oct(mode))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e6882baa;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__std__mkdir_5;
}
static void cont__std__mkdir_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 2138: "MODE" = string("0o" oct(mode))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__580ae28b5c407d7c;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__std__mkdir_7;
}
static void cont__std__mkdir_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 2139: "PARENTS" = do_create_parent_folders
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__f8c406421419e0a9;
  arguments->slots[1] = frame->slots[1] /* do_create_parent_folders */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__std__mkdir_9;
}
static void cont__std__mkdir_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__4 */ = arguments->slots[0];
  // 2140: "path" = path
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__220ae90b5dc07d51;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* path */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__std__mkdir_11;
}
static void cont__std__mkdir_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__5 */ = arguments->slots[0];
  // 2136: raise_error
  // 2137:   "mkdir"
  // 2138:   "MODE" = string("0o" oct(mode))
  // 2139:   "PARENTS" = do_create_parent_folders
  // 2140:   "path" = path
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = string__5c5aea03ea80c025;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  arguments->slots[2] = frame->slots[6] /* temp__4 */;
  arguments->slots[3] = frame->slots[7] /* temp__5 */;
  result_count = frame->caller_result_count;
  myself = get__raise_error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__mkdir_13(void) {
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
  // 2143: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__std__mkdir_14;
}
static void cont__std__mkdir_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 2143: before &partial_path '/' -1
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* partial_path */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__before();
  func = myself->type;
  frame->cont = cont__std__mkdir_15;
}
static void cont__std__mkdir_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* partial_path */ = arguments->slots[0];
  // 2144: ... partial_path != ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* partial_path */;
  arguments->slots[1] = empty_string;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__std__mkdir_16;
}
static void cont__std__mkdir_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 2144: ... partial_path != ""
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__std__mkdir_17;
}
static void cont__std__mkdir_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 2144: ... :
  // 2145:   create_parent_folders partial_path
  // 2146:   if clib_mkdir(partial_path mode) < 0 && errno() != EEXIST fail
  frame->slots[6] /* temp__3 */ = create_closure(entry__std__mkdir_18, 0);
  // 2144: if partial_path != "":
  // 2145:   create_parent_folders partial_path
  // 2146:   if clib_mkdir(partial_path mode) < 0 && errno() != EEXIST fail
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__std__mkdir_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 2132: PARENTS = false
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__PARENTS();
  arguments->slots[1] = get__false();
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__std__mkdir_28;
}
static void cont__std__mkdir_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 2129: extract_options options
  // 2130:   MODE = 0o755
  // 2131:   $mode
  // 2132:   PARENTS = false
  // 2133:   $do_create_parent_folders
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* options */;
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  arguments->slots[2] = frame->slots[7] /* temp__2 */;
  result_count = 2;
  myself = get__extract_options();
  func = myself->type;
  frame->cont = cont__std__mkdir_29;
}
static void cont__std__mkdir_29(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* mode */, arguments->slots[0]);
  initialize_future(frame->slots[3] /* do_create_parent_folders */, arguments->slots[1]);
  // 2148: without_suffix &path '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* path */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__without_suffix();
  func = myself->type;
  frame->cont = cont__std__mkdir_30;
}
static void cont__std__mkdir_30(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* path */ = arguments->slots[0];
  // 2149: ... : create_parent_folders path
  frame->slots[6] /* temp__1 */ = create_closure(entry__std__mkdir_31, 0);
  // 2149: if do_create_parent_folders: create_parent_folders path
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* do_create_parent_folders */;
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__std__mkdir_32;
}
static void entry__std__mkdir_31(void) {
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
  // 2149: ... create_parent_folders path
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* path */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* create_parent_folders */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__std__mkdir_32(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 2150: ... clib_mkdir(path mode)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* path */;
  arguments->slots[1] = frame->slots[2] /* mode */;
  result_count = 1;
  myself = var._clib_mkdir;
  func = myself->type;
  frame->cont = cont__std__mkdir_33;
}
static void cont__std__mkdir_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 2150: ... clib_mkdir(path mode) < 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__2 */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__std__mkdir_34;
}
static void cont__std__mkdir_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 2150: ... :
  // 2151:   unless do_create_parent_folders && errno() == EEXIST fail
  frame->slots[8] /* temp__3 */ = create_closure(entry__std__mkdir_35, 0);
  // 2150: if clib_mkdir(path mode) < 0:
  // 2151:   unless do_create_parent_folders && errno() == EEXIST fail
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__create_directory_5(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // path: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* path */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 2161: ... "
  // 2162:   Failed to create directory "@(path)@quot;!@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__99b484ebf32a2eca;
  arguments->slots[1] = frame->slots[0] /* path */;
  arguments->slots[2] = string__2d7981f4e6182be4;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__std__create_directory_7;
}
static void cont__std__create_directory_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 2161: Error "
  // 2162:   Failed to create directory "@(path)@quot;!@
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__create_directory_1(void) {
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
  // 2160: ... clib_mkdir(path mode)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* path */;
  arguments->slots[1] = frame->slots[1] /* mode */;
  result_count = 1;
  myself = var._clib_mkdir;
  func = myself->type;
  frame->cont = cont__std__create_directory_2;
}
static void cont__std__create_directory_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 2160: ... clib_mkdir(path mode) != 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__std__create_directory_3;
}
static void cont__std__create_directory_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 2160: ... clib_mkdir(path mode) != 0
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__std__create_directory_4;
}
static void cont__std__create_directory_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 2160: ... :
  // 2161:   Error "
  // 2162:     Failed to create directory "@(path)@quot;!@
  frame->slots[5] /* temp__4 */ = create_closure(entry__std__create_directory_5, 0);
  // 2160: if clib_mkdir(path mode) != 0:
  // 2161:   Error "
  // 2162:     Failed to create directory "@(path)@quot;!@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__fullname_1(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // pathname: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* pathname */ = create_cell_with_contents(arguments->slots[0]);
  // 2170: ... pathname .has_prefix. '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* pathname */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__std__fullname_2;
}
static void cont__std__fullname_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 2170: ... :
  // 2171:   !pathname string(current_path() "/" pathname)
  frame->slots[2] /* temp__2 */ = create_closure(entry__std__fullname_3, 0);
  // 2170: unless pathname .has_prefix. '/':
  // 2171:   !pathname string(current_path() "/" pathname)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__std__fullname_7;
}
static void entry__std__fullname_3(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // pathname: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* pathname */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 2171: ... current_path()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__current_path();
  func = myself->type;
  frame->cont = cont__std__fullname_4;
}
static void cont__std__fullname_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 2171: !pathname string(current_path() "/" pathname)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = string__578a5af303e9cce;
  arguments->slots[2] = ((CELL *)frame->slots[0])->contents /* pathname */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__std__fullname_6;
}
static void cont__std__fullname_6(void) {
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
static void cont__std__fullname_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 2172: ... pathname .has_suffix. '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* pathname */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__has_suffix();
  func = myself->type;
  frame->cont = cont__std__fullname_8;
}
static void cont__std__fullname_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 2172: ... : push &pathname '/'
  frame->slots[2] /* temp__2 */ = create_closure(entry__std__fullname_9, 0);
  // 2172: unless pathname .has_suffix. '/': push &pathname '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__std__fullname_11;
}
static void entry__std__fullname_9(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // pathname: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* pathname */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 2172: ... push &pathname '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* pathname */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__std__fullname_10;
}
static void cont__std__fullname_10(void) {
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
static void cont__std__fullname_11(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 2173: ... many("//")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e6702bea;
  result_count = 1;
  myself = get__many();
  func = myself->type;
  frame->cont = cont__std__fullname_13;
}
static void cont__std__fullname_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 2173: ... many("//") = "/"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = string__578a5af303e9cce;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__std__fullname_14;
}
static void cont__std__fullname_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 2173: replace_all &pathname many("//") = "/"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* pathname */;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__replace_all();
  func = myself->type;
  frame->cont = cont__std__fullname_15;
}
static void cont__std__fullname_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* pathname */ = arguments->slots[0];
  // 2174: ... "/./" = "/"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__fa733815f596be3;
  arguments->slots[1] = string__578a5af303e9cce;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__std__fullname_17;
}
static void cont__std__fullname_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 2174: replace_all &pathname "/./" = "/"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* pathname */;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__replace_all();
  func = myself->type;
  frame->cont = cont__std__fullname_18;
}
static void cont__std__fullname_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* pathname */ = arguments->slots[0];
  // 2175: ... : (-> break)
  // 2176:   forever:
  // 2177:     $orig_pathname pathname
  // 2178:     replace_all
  // 2179:       &pathname
  // 2180:       '/', many(not_followed_by('/'), ANY_CHARACTER), "/../" = "/"
  // 2181:     if pathname == orig_pathname break
  frame->slots[1] /* temp__1 */ = create_closure(entry__std__fullname_19, 0);
  // 2175: do: (-> break)
  // 2176:   forever:
  // 2177:     $orig_pathname pathname
  // 2178:     replace_all
  // 2179:       &pathname
  // 2180:       '/', many(not_followed_by('/'), ANY_CHARACTER), "/../" = "/"
  // 2181:     if pathname == orig_pathname break
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 0;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__std__fullname_30;
}
static void entry__std__fullname_19(void) {
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
  // 2176: ... :
  // 2177:   $orig_pathname pathname
  // 2178:   replace_all
  // 2179:     &pathname
  // 2180:     '/', many(not_followed_by('/'), ANY_CHARACTER), "/../" = "/"
  // 2181:   if pathname == orig_pathname break
  frame->slots[2] /* temp__1 */ = create_closure(entry__std__fullname_20, 0);
  // 2176: forever:
  // 2177:   $orig_pathname pathname
  // 2178:   replace_all
  // 2179:     &pathname
  // 2180:     '/', many(not_followed_by('/'), ANY_CHARACTER), "/../" = "/"
  // 2181:   if pathname == orig_pathname break
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__forever();
  func = myself->type;
  frame->cont = cont__std__fullname_29;
}
static void entry__std__fullname_20(void) {
  allocate_initialized_frame_gc(2, 8);
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
  // 2177: $orig_pathname pathname
  initialize_maybe_future(frame->slots[2] /* orig_pathname */, ((CELL *)frame->slots[0])->contents /* pathname */);
  // 2180: ... not_followed_by('/')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__47;
  result_count = 1;
  myself = get__not_followed_by();
  func = myself->type;
  frame->cont = cont__std__fullname_21;
}
static void cont__std__fullname_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__5 */ = arguments->slots[0];
  // 2180: ... not_followed_by('/'), ANY_CHARACTER
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__5 */;
  arguments->slots[1] = get__ANY_CHARACTER();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__std__fullname_22;
}
static void cont__std__fullname_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__4 */ = arguments->slots[0];
  // 2180: ... many(not_followed_by('/'), ANY_CHARACTER)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__4 */;
  result_count = 1;
  myself = get__many();
  func = myself->type;
  frame->cont = cont__std__fullname_23;
}
static void cont__std__fullname_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 2180: '/', many(not_followed_by('/'), ANY_CHARACTER), "/../"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = character__47;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  arguments->slots[2] = string__9c0afacb5f107d16;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__std__fullname_25;
}
static void cont__std__fullname_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 2180: '/', many(not_followed_by('/'), ANY_CHARACTER), "/../" = "/"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = string__578a5af303e9cce;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__std__fullname_26;
}
static void cont__std__fullname_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 2178: replace_all
  // 2179:   &pathname
  // 2180:   '/', many(not_followed_by('/'), ANY_CHARACTER), "/../" = "/"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* pathname */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__replace_all();
  func = myself->type;
  frame->cont = cont__std__fullname_27;
}
static void cont__std__fullname_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* pathname */ = arguments->slots[0];
  // 2181: ... pathname == orig_pathname
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* pathname */;
  arguments->slots[1] = frame->slots[2] /* orig_pathname */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__std__fullname_28;
}
static void cont__std__fullname_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 2181: if pathname == orig_pathname break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* break */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__std__fullname_29(void) {
  myself = frame->slots[0] /* break */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__std__fullname_30(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 2182: ... pathname == "/"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* pathname */;
  arguments->slots[1] = string__578a5af303e9cce;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__std__fullname_31;
}
static void cont__std__fullname_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 2182: ... : range &pathname 1 -2
  frame->slots[2] /* temp__2 */ = create_closure(entry__std__fullname_32, 0);
  // 2182: unless pathname == "/": range &pathname 1 -2
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__std__fullname_35;
}
static void entry__std__fullname_32(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // pathname: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* pathname */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 2182: ... 2
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__std__fullname_33;
}
static void cont__std__fullname_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 2182: ... range &pathname 1 -2
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* pathname */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__std__fullname_34;
}
static void cont__std__fullname_34(void) {
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
static void cont__std__fullname_35(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 2183: -> pathname
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
static void entry__std__opendir_1(void) {
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
static void entry__types__DIR__close_1(void) {
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
static void entry__types__DIR__get_1(void) {
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
static void entry__types__dirent__filename_of_1(void) {
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
static void entry__types__dirent__inode_of_1(void) {
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
static void entry__types__dirent__file_type_of_1(void) {
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
static void entry__types__dirent__fullname_of_1(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // self: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 2357: ... pathname_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__pathname_of();
  func = myself->type;
  frame->cont = cont__types__dirent__fullname_of_2;
}
static void cont__types__dirent__fullname_of_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 2357: ... filename_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__filename_of();
  func = myself->type;
  frame->cont = cont__types__dirent__fullname_of_3;
}
static void cont__types__dirent__fullname_of_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 2357: ... string(pathname_of(self) "/" filename_of(self))
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = string__578a5af303e9cce;
  arguments->slots[2] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__types__dirent__fullname_of_4;
}
static void cont__types__dirent__fullname_of_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 2357: -> string(pathname_of(self) "/" filename_of(self))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__dirent__is_a_directory_1(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // self: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 2365: ... file_type_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__file_type_of();
  func = myself->type;
  frame->cont = cont__types__dirent__is_a_directory_2;
}
static void cont__types__dirent__is_a_directory_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 2365: ... file_type_of(self) == std::DIRECTORY
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = var.std__DIRECTORY;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__types__dirent__is_a_directory_3;
}
static void cont__types__dirent__is_a_directory_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 2365: -> file_type_of(self) == std::DIRECTORY
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__dirent__is_a_regular_file_1(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // self: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 2373: ... file_type_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__file_type_of();
  func = myself->type;
  frame->cont = cont__types__dirent__is_a_regular_file_2;
}
static void cont__types__dirent__is_a_regular_file_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 2373: ... file_type_of(self) == std::REGULAR_FILE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = var.std__REGULAR_FILE;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__types__dirent__is_a_regular_file_3;
}
static void cont__types__dirent__is_a_regular_file_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 2373: -> file_type_of(self) == std::REGULAR_FILE
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__types__dirent__is_a_link_1(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // self: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 2381: ... file_type_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* self */;
  result_count = 1;
  myself = get__file_type_of();
  func = myself->type;
  frame->cont = cont__types__dirent__is_a_link_2;
}
static void cont__types__dirent__is_a_link_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 2381: ... file_type_of(self) == std::LINK
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = var.std__LINK;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__types__dirent__is_a_link_3;
}
static void cont__types__dirent__is_a_link_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 2381: -> file_type_of(self) == std::LINK
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__directory_1(void) {
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
  // 2390: ... SORT = false
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__SORT();
  arguments->slots[1] = get__false();
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__std__directory_2;
}
static void cont__std__directory_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 2390: extract_options options SORT = false $do_sort
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* options */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 1;
  myself = get__extract_options();
  func = myself->type;
  frame->cont = cont__std__directory_3;
}
static void cont__std__directory_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* do_sort */, arguments->slots[0]);
  // 2391: $$entries list()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__std__directory_4;
}
static void cont__std__directory_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* entries */ = arguments->slots[0];
  // 2392: ... fullname(pathname)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* pathname */;
  result_count = 1;
  myself = get__fullname();
  func = myself->type;
  frame->cont = cont__std__directory_5;
}
static void cont__std__directory_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 2392: $dir std::opendir(fullname(pathname))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  result_count = 1;
  myself = var.std__opendir;
  func = myself->type;
  frame->cont = cont__std__directory_6;
}
static void cont__std__directory_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* dir */, arguments->slots[0]);
  // 2393: ... : (-> break)
  // 2394:   forever:
  // 2395:     $entry get(dir)
  // 2396:     unless entry.is_defined break
  // 2397:     case
  // 2398:       filename_of(entry)
  // 2399:       ".", "..":
  // 2400:         pass
  // 2401:       :
  // 2402:         push &entries entry
  frame->slots[5] /* temp__1 */ = create_closure(entry__std__directory_7, 0);
  // 2393: do: (-> break)
  // 2394:   forever:
  // 2395:     $entry get(dir)
  // 2396:     unless entry.is_defined break
  // 2397:     case
  // 2398:       filename_of(entry)
  // 2399:       ".", "..":
  // 2400:         pass
  // 2401:       :
  // 2402:         push &entries entry
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  result_count = 0;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__std__directory_20;
}
static void entry__std__directory_7(void) {
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
  // 2394: ... :
  // 2395:   $entry get(dir)
  // 2396:   unless entry.is_defined break
  // 2397:   case
  // 2398:     filename_of(entry)
  // 2399:     ".", "..":
  // 2400:       pass
  // 2401:     :
  // 2402:       push &entries entry
  frame->slots[3] /* temp__1 */ = create_closure(entry__std__directory_8, 0);
  // 2394: forever:
  // 2395:   $entry get(dir)
  // 2396:   unless entry.is_defined break
  // 2397:   case
  // 2398:     filename_of(entry)
  // 2399:     ".", "..":
  // 2400:       pass
  // 2401:     :
  // 2402:       push &entries entry
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__forever();
  func = myself->type;
  frame->cont = cont__std__directory_19;
}
static void entry__std__directory_16(void) {
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
  // 2402: push &entries entry
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* entries */;
  arguments->slots[1] = frame->slots[1] /* entry */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__std__directory_17;
}
static void cont__std__directory_17(void) {
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
static void entry__std__directory_18(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 2400: pass
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = get__pass();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__directory_8(void) {
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
  // 2395: $entry get(dir)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* dir */;
  result_count = 1;
  myself = get__get();
  func = myself->type;
  frame->cont = cont__std__directory_9;
}
static void cont__std__directory_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* entry */, arguments->slots[0]);
  // 2396: ... entry.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* entry */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__std__directory_10;
}
static void cont__std__directory_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 2396: unless entry.is_defined break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* break */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__std__directory_11;
}
static void cont__std__directory_11(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 2398: filename_of(entry)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* entry */;
  result_count = 1;
  myself = get__filename_of();
  func = myself->type;
  frame->cont = cont__std__directory_12;
}
static void cont__std__directory_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 2399: ".", ".."
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__578a5af303e9ccf;
  arguments->slots[1] = string__2d7981f4e6782beb;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__std__directory_15;
}
static void cont__std__directory_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 2401: :
  // 2402:   push &entries entry
  frame->slots[6] /* temp__3 */ = create_closure(entry__std__directory_16, 0);
  // 2397: case
  // 2398:   filename_of(entry)
  // 2399:   ".", "..":
  // 2400:     pass
  // 2401:   :
  // 2402:     push &entries entry
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  arguments->slots[2] = func__std__directory_18;
  arguments->slots[3] = frame->slots[6] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__std__directory_19(void) {
  myself = frame->slots[0] /* break */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__std__directory_20(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 2403: close dir
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* dir */;
  result_count = 0;
  myself = get__close();
  func = myself->type;
  frame->cont = cont__std__directory_21;
}
static void cont__std__directory_21(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 2404: ... :
  // 2405:   sort &entries: (left right) -> filename_of(left) < filename_of(right)
  frame->slots[5] /* temp__1 */ = create_closure(entry__std__directory_22, 0);
  // 2404: if do_sort:
  // 2405:   sort &entries: (left right) -> filename_of(left) < filename_of(right)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* do_sort */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__std__directory_28;
}
static void entry__std__directory_22(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // entries: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* entries */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 2405: sort &entries: (left right) -> filename_of(left) < filename_of(right)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* entries */;
  arguments->slots[1] = func__std__directory_23;
  result_count = 1;
  myself = get__sort();
  func = myself->type;
  frame->cont = cont__std__directory_27;
}
static void entry__std__directory_23(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // left: 0
  // right: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 2405: ... filename_of(left)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* left */;
  result_count = 1;
  myself = get__filename_of();
  func = myself->type;
  frame->cont = cont__std__directory_24;
}
static void cont__std__directory_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 2405: ... filename_of(right)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* right */;
  result_count = 1;
  myself = get__filename_of();
  func = myself->type;
  frame->cont = cont__std__directory_25;
}
static void cont__std__directory_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 2405: ... filename_of(left) < filename_of(right)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__std__directory_26;
}
static void cont__std__directory_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 2405: ... -> filename_of(left) < filename_of(right)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__std__directory_27(void) {
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
static void cont__std__directory_28(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 2406: -> entries
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
static void entry__std__get_network_addresses_1(void) {
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
static void entry__std__get_network_address_1(void) {
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
static void entry__types__addrinfo__connect_1(void) {
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
static void entry__types__string__connect_1(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // uri: 0
  // port: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 2595: ... get_network_address(uri)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* uri */;
  result_count = 1;
  myself = get__get_network_address();
  func = myself->type;
  frame->cont = cont__types__string__connect_2;
}
static void cont__types__string__connect_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 2595: connect get_network_address(uri) port
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* port */;
  result_count = frame->caller_result_count;
  myself = get__connect();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__addrinfo__listen_1(void) {
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
static void entry__types__string__listen_1(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // uri: 0
  // port: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 2631: ... get_network_address(uri)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* uri */;
  result_count = 1;
  myself = get__get_network_address();
  func = myself->type;
  frame->cont = cont__types__string__listen_2;
}
static void cont__types__string__listen_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 2631: listen get_network_address(uri) port
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* port */;
  result_count = frame->caller_result_count;
  myself = get__listen();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__types__file_descriptor__accept_1(void) {
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
static void entry__std__write_1(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // args: 0
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 2655: ... string(args*)
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[0] /* args */);
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__std__write_2;
}
static void cont__std__write_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 2655: ... string(args*).to_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__to_utf8();
  func = myself->type;
  frame->cont = cont__std__write_3;
}
static void cont__std__write_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 2655: write_to STDOUT_FILENO string(args*).to_utf8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__STDOUT_FILENO();
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__write_to();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__writeln_1(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // args: 0
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 2665: write args* "@nl;"
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[0] /* args */);
  arguments->slots[argument_count++] = string__578a5af303e9ceb;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__ewrite_1(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // args: 0
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 2676: ... string(args*)
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[0] /* args */);
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__std__ewrite_2;
}
static void cont__std__ewrite_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 2676: ... string(args*).to_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__to_utf8();
  func = myself->type;
  frame->cont = cont__std__ewrite_3;
}
static void cont__std__ewrite_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 2676: atomic_write_to STDERR_FILENO string(args*).to_utf8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__STDERR_FILENO();
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__atomic_write_to();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__ewriteln_1(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // args: 0
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 2685: ewrite args* "@nl;"
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[0] /* args */);
  arguments->slots[argument_count++] = string__578a5af303e9ceb;
  result_count = frame->caller_result_count;
  myself = get__ewrite();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__read_1(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // n: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 2693: read_from STDIN_FILENO n
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__STDIN_FILENO();
  arguments->slots[1] = frame->slots[0] /* n */;
  result_count = frame->caller_result_count;
  myself = get__read_from();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__readln_1(void) {
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
  // 2701: $$buf ""
  ((CELL *)frame->slots[1])->contents /* buf */ = empty_string;
  // 2702: ... :
  // 2703:   read $chr 1
  // 2704:   if chr == "@nl;" || chr == "": return buf
  // 2705:   append &buf chr
  frame->slots[2] /* temp__1 */ = create_closure(entry__std__readln_2, 0);
  // 2702: forever:
  // 2703:   read $chr 1
  // 2704:   if chr == "@nl;" || chr == "": return buf
  // 2705:   append &buf chr
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__forever();
  func = myself->type;
  frame->cont = cont__std__readln_11;
}
static void entry__std__readln_2(void) {
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
  // 2703: read $chr 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__read();
  func = myself->type;
  frame->cont = cont__std__readln_3;
}
static void cont__std__readln_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* chr */, arguments->slots[0]);
  // 2704: ... chr == "@nl;"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* chr */;
  arguments->slots[1] = string__578a5af303e9ceb;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__std__readln_4;
}
static void cont__std__readln_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 2704: ... chr == ""
  frame->slots[5] /* temp__3 */ = create_closure(entry__std__readln_5, 0);
  // 2704: ... chr == "@nl;" || chr == ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__std__readln_7;
}
static void entry__std__readln_5(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // chr: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* chr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 2704: ... chr == ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* chr */;
  arguments->slots[1] = empty_string;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__std__readln_6;
}
static void cont__std__readln_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 2704: ... chr == ""
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__std__readln_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 2704: ... : return buf
  frame->slots[6] /* temp__4 */ = create_closure(entry__std__readln_8, 0);
  // 2704: if chr == "@nl;" || chr == "": return buf
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__std__readln_9;
}
static void entry__std__readln_8(void) {
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
  // 2704: ... return buf
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* buf */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__std__readln_9(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 2705: append &buf chr
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* buf */;
  arguments->slots[1] = frame->slots[2] /* chr */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__std__readln_10;
}
static void cont__std__readln_10(void) {
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
static void cont__std__readln_11(void) {
  myself = frame->slots[0] /* return */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__std__load_9(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // buf: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* buf */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 2717: -> buf
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* buf */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__std__load_10(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // filename: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 2719: ... "
  // 2720:   Load error ("@(filename)@quot;)!@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__a622e2e97612a669;
  arguments->slots[1] = frame->slots[0] /* filename */;
  arguments->slots[2] = string__fa730c15f616bed;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__std__load_13;
}
static void cont__std__load_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 2719: raise "
  // 2720:   Load error ("@(filename)@quot;)!@
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__raise();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__load_4(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // filename: 0
  // buf: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* filename */
  frame->slots[1] /* buf */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 2716: wget($buf "-q" "-O" "-" filename)
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e6602bb4;
  arguments->slots[1] = string__2d7981f4e6602b8a;
  arguments->slots[2] = string__578a5af303e9ccc;
  arguments->slots[3] = frame->slots[0] /* filename */;
  result_count = 2;
  myself = var._wget;
  func = myself->type;
  frame->cont = cont__std__load_8;
}
static void cont__std__load_8(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* buf */, arguments->slots[0]);
  frame->slots[2] /* temp__1 */ = arguments->slots[1];
  // 2717: -> buf
  frame->slots[3] /* temp__2 */ = create_closure(entry__std__load_9, 0);
  // 2718: :
  // 2719:   raise "
  // 2720:     Load error ("@(filename)@quot;)!@
  frame->slots[4] /* temp__3 */ = create_closure(entry__std__load_10, 0);
  // 2715: if
  // 2716:   wget($buf "-q" "-O" "-" filename)
  // 2717:   -> buf
  // 2718:   :
  // 2719:     raise "
  // 2720:       Load error ("@(filename)@quot;)!@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  arguments->slots[2] = frame->slots[4] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__load_14(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // filename: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 2722: load_file filename
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* filename */;
  result_count = frame->caller_result_count;
  myself = get__load_file();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__load_1(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // filename: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 2714: filename .has_prefix. "http://"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* filename */;
  arguments->slots[1] = string__92241b5897c380d5;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__std__load_3;
}
static void cont__std__load_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 2714: ... :
  // 2715:   if
  // 2716:     wget($buf "-q" "-O" "-" filename)
  // 2717:     -> buf
  // 2718:     :
  // 2719:       raise "
  // 2720:         Load error ("@(filename)@quot;)!@
  frame->slots[2] /* temp__2 */ = create_closure(entry__std__load_4, 0);
  // 2721: :
  // 2722:   load_file filename
  frame->slots[3] /* temp__3 */ = create_closure(entry__std__load_14, 0);
  // 2713: if
  // 2714:   filename .has_prefix. "http://":
  // 2715:     if
  // 2716:       wget($buf "-q" "-O" "-" filename)
  // 2717:       -> buf
  // 2718:       :
  // 2719:         raise "
  // 2720:           Load error ("@(filename)@quot;)!@
  // 2721:   :
  // 2722:     load_file filename
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
static void entry__std__save_1(void) {
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
  // 2732: ... PARENTS = false
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__PARENTS();
  arguments->slots[1] = get__false();
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__std__save_2;
}
static void cont__std__save_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 2732: extract_options options PARENTS = false $do_create_directory
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* options */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__extract_options();
  func = myself->type;
  frame->cont = cont__std__save_3;
}
static void cont__std__save_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* do_create_directory */, arguments->slots[0]);
  // 2733: ... :
  // 2734:   $path before(filename '/' -1)
  // 2735:   if path != "": mkdir --PARENTS path
  frame->slots[4] /* temp__1 */ = create_closure(entry__std__save_4, 0);
  // 2733: if do_create_directory:
  // 2734:   $path before(filename '/' -1)
  // 2735:   if path != "": mkdir --PARENTS path
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* do_create_directory */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__std__save_11;
}
static void entry__std__save_9(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // path: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* path */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 2735: ... --PARENTS
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__PARENTS();
  arguments->slots[1] = get__std__true();
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__std__save_10;
}
static void cont__std__save_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 2735: ... mkdir --PARENTS path
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[0] /* path */;
  result_count = frame->caller_result_count;
  myself = get__mkdir();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__std__save_4(void) {
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
  // 2734: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__std__save_5;
}
static void cont__std__save_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 2734: $path before(filename '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* filename */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__before();
  func = myself->type;
  frame->cont = cont__std__save_6;
}
static void cont__std__save_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* path */, arguments->slots[0]);
  // 2735: ... path != ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* path */;
  arguments->slots[1] = empty_string;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__std__save_7;
}
static void cont__std__save_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 2735: ... path != ""
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__std__save_8;
}
static void cont__std__save_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 2735: ... : mkdir --PARENTS path
  frame->slots[4] /* temp__3 */ = create_closure(entry__std__save_9, 0);
  // 2735: if path != "": mkdir --PARENTS path
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__std__save_11(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 2736: ... data.to_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* data */;
  result_count = 1;
  myself = get__to_string();
  func = myself->type;
  frame->cont = cont__std__save_12;
}
static void cont__std__save_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 2736: save_file filename data.to_string
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
  var.std__PARENTS = collect_node(var.std__PARENTS);
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
  var.std__open_file = collect_node(var.std__open_file);
  var.std__open_file_for_reading = collect_node(var.std__open_file_for_reading);
  var.std__open_file_for_writing = collect_node(var.std__open_file_for_writing);
  var.std__open_file_for_reading_and_writing = collect_node(var.std__open_file_for_reading_and_writing);
  var.std__create_file = collect_node(var.std__create_file);
  var._file_description = collect_node(var._file_description);
  var._WriteError = collect_node(var._WriteError);
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
  var._clib_mkdir = collect_node(var._clib_mkdir);
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
}

static int already_run_phase_2 = false;

EXPORT void phase_2__basic__io(void) {
  if (already_run_phase_2) return;
  already_run_phase_2 = true;
  set_module("basic__io");
  number__0o755 = from_uint32(493U);
  character__47 = from_uchar32(47);
  number__0 = from_uint32(0U);
  number__1 = from_uint32(1U);
  number__2 = from_uint32(2U);
  number__0x1000000 = from_uint32(16777216U);
  unique__std__MODE = register_unique_item("std__MODE");
  unique__std__PARENTS = register_unique_item("std__PARENTS");
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
  string__fa730415fc16bec = from_latin_1_string(" = ", 3);
  string__578a5af303e9ceb = from_latin_1_string("\012", 1);
  string__64b427a840d3b445 = from_latin_1_string(" failed: ", 9);
  string__2d7981f4e6002bcf = from_latin_1_string("!\012", 2);
  func__std__raise_error_1 = create_function(entry__std__raise_error_1, -1);
  func__std__check_error_1 = create_function(entry__std__check_error_1, -1);
  func__std__errno_1 = create_function(entry__std__errno_1, 0);
  func__std__strerror_1 = create_function(entry__std__strerror_1, 1);
  func__std__stat_1 = create_function(entry__std__stat_1, 1);
  func__std__file_exists_1 = create_function(entry__std__file_exists_1, 1);
  func__types__stat__device_of_1 = create_function(entry__types__stat__device_of_1, 1);
  func__types__stat__inode_of_1 = create_function(entry__types__stat__inode_of_1, 1);
  func__types__stat__mode_of_1 = create_function(entry__types__stat__mode_of_1, 1);
  func__types__stat__link_count_of_1 = create_function(entry__types__stat__link_count_of_1, 1);
  func__types__stat__user_id_of_1 = create_function(entry__types__stat__user_id_of_1, 1);
  func__types__stat__group_id_of_1 = create_function(entry__types__stat__group_id_of_1, 1);
  func__types__stat__size_of_1 = create_function(entry__types__stat__size_of_1, 1);
  func__types__stat__block_size_of_1 = create_function(entry__types__stat__block_size_of_1, 1);
  func__types__stat__sector_count_of_1 = create_function(entry__types__stat__sector_count_of_1, 1);
  func__types__stat__access_time_of_1 = create_function(entry__types__stat__access_time_of_1, 1);
  func__types__stat__modification_time_of_1 = create_function(entry__types__stat__modification_time_of_1, 1);
  func__types__stat__status_change_time_of_1 = create_function(entry__types__stat__status_change_time_of_1, 1);
  func__types__stat__is_a_directory_1 = create_function(entry__types__stat__is_a_directory_1, 1);
  func__types__stat__is_a_regular_file_1 = create_function(entry__types__stat__is_a_regular_file_1, 1);
  func__types__stat__is_a_link_1 = create_function(entry__types__stat__is_a_link_1, 1);
  func__std__create_file_descriptor_1 = create_function(entry__std__create_file_descriptor_1, 1);
  func__types__file_descriptor__to_integer_1 = create_function(entry__types__file_descriptor__to_integer_1, 1);
  func__types__file_descriptor__equal_1 = create_function(entry__types__file_descriptor__equal_1, 2);
  func__types__file_descriptor__less_1 = create_function(entry__types__file_descriptor__less_1, 2);
  func__types__file_descriptor__hash_1 = create_function(entry__types__file_descriptor__hash_1, 1);
  func__posix_open_1 = create_function(entry__posix_open_1, -1);
  func__std__open_file_1 = create_function(entry__std__open_file_1, 2);
  func__std__open_file_for_reading_1 = create_function(entry__std__open_file_for_reading_1, 1);
  func__std__open_file_for_writing_1 = create_function(entry__std__open_file_for_writing_1, 1);
  func__std__open_file_for_reading_and_writing_1 = create_function(entry__std__open_file_for_reading_and_writing_1, 1);
  func__std__create_file_1 = create_function(entry__std__create_file_1, 1);
  func__types__file_descriptor__close_1 = create_function(entry__types__file_descriptor__close_1, 1);
  func__types__file_descriptor__read_some_bytes_from_1 = create_function(entry__types__file_descriptor__read_some_bytes_from_1, 2);
  func__types__file_descriptor__read_from_1 = create_function(entry__types__file_descriptor__read_from_1, -1);
  func__types__file_descriptor__write_some_bytes_to_1 = create_function(entry__types__file_descriptor__write_some_bytes_to_1, 2);
  string__578a5af303e9cc3 = from_latin_1_string("\042", 1);
  string__431630d095799867 = from_latin_1_string("<file descriptor ", 17);
  string__578a5af303e9cdf = from_latin_1_string(">", 1);
  string__bb740f9b15cb80c4 = from_latin_1_string("<stdin>", 7);
  func__file_description_13 = create_function(entry__file_description_13, 0);
  string__70d8a89c0475db9e = from_latin_1_string("<stdout>", 8);
  func__file_description_15 = create_function(entry__file_description_15, 0);
  string__64d8a95c0445db9e = from_latin_1_string("<stderr>", 8);
  func__file_description_17 = create_function(entry__file_description_17, 0);
  func__file_description_1 = create_function(entry__file_description_1, 1);
  string__8138f7c6e352b20e = from_latin_1_string("Writing to file ", 16);
  func__WriteError_1 = create_function(entry__WriteError_1, 1);
  func__types__file_descriptor__write_to_1 = create_function(entry__types__file_descriptor__write_to_1, -1);
  func__std__atomic_write_to_1 = create_function(entry__std__atomic_write_to_1, -1);
  func__std__load_file_15 = create_function(entry__std__load_file_15, 0);
  func__std__load_file_1 = create_function(entry__std__load_file_1, 1);
  string__52b15fd51e05f634 = from_latin_1_string("Failed to save file \042", 21);
  func__std__save_file_1 = create_function(entry__std__save_file_1, 2);
  func__types__file_descriptor__flush_1 = create_function(entry__types__file_descriptor__flush_1, 1);
  func__ioctl_value_1 = create_function(entry__ioctl_value_1, 3);
  string__9f84c1967610d391 = from_latin_1_string("IOCTL failed!\012", 14);
  func__types__file_descriptor__std__ioctl_8 = create_function(entry__types__file_descriptor__std__ioctl_8, 0);
  func__types__file_descriptor__std__ioctl_1 = create_function(entry__types__file_descriptor__std__ioctl_1, -1);
  func__types__file_descriptor__std__get_terminal_size_1 = create_function(entry__types__file_descriptor__std__get_terminal_size_1, 1);
  func__posix_unlink_1 = create_function(entry__posix_unlink_1, 1);
  string__98599da1f95f3503 = from_latin_1_string("Failed to delete file \042", 23);
  string__fa730c15f216bc6 = from_latin_1_string("\042!\012", 3);
  func__std__delete_file_1 = create_function(entry__std__delete_file_1, 1);
  func__wait_for_io_ready_1 = create_function(entry__wait_for_io_ready_1, 4);
  func__std__get_pid_1 = create_function(entry__std__get_pid_1, 0);
  func__std__wait_pid_1 = create_function(entry__std__wait_pid_1, 2);
  func__std__wait_for_io_1 = create_function(entry__std__wait_for_io_1, -1);
  func__std__current_path_1 = create_function(entry__std__current_path_1, 0);
  func__std__chdir_1 = create_function(entry__std__chdir_1, 1);
  string__6e87e13bb5f5e5b7 = from_latin_1_string("Failed to change current directory to \042", 39);
  string__2d7981f4e6182be4 = from_latin_1_string("\042!", 2);
  func__std__change_directory_1 = create_function(entry__std__change_directory_1, 1);
  func__clib_mkdir_1 = create_function(entry__clib_mkdir_1, 2);
  string__2d7981f4e6882baa = from_latin_1_string("0o", 2);
  string__580ae28b5c407d7c = from_latin_1_string("MODE", 4);
  string__f8c406421419e0a9 = from_latin_1_string("PARENTS", 7);
  string__220ae90b5dc07d51 = from_latin_1_string("path", 4);
  string__5c5aea03ea80c025 = from_latin_1_string("mkdir", 5);
  func__std__mkdir_22 = create_function(entry__std__mkdir_22, 0);
  func__std__mkdir_36 = create_function(entry__std__mkdir_36, 0);
  func__std__mkdir_1 = create_function(entry__std__mkdir_1, -1);
  string__99b484ebf32a2eca = from_latin_1_string("Failed to create directory \042", 28);
  func__std__create_directory_1 = create_function(entry__std__create_directory_1, -1);
  string__578a5af303e9cce = from_latin_1_string("/", 1);
  string__2d7981f4e6702bea = from_latin_1_string("//", 2);
  string__fa733815f596be3 = from_latin_1_string("/./", 3);
  string__9c0afacb5f107d16 = from_latin_1_string("/../", 4);
  func__std__fullname_1 = create_function(entry__std__fullname_1, 1);
  func__std__opendir_1 = create_function(entry__std__opendir_1, 1);
  func__types__DIR__close_1 = create_function(entry__types__DIR__close_1, 1);
  func__types__DIR__get_1 = create_function(entry__types__DIR__get_1, 1);
  func__types__dirent__filename_of_1 = create_function(entry__types__dirent__filename_of_1, 1);
  func__types__dirent__inode_of_1 = create_function(entry__types__dirent__inode_of_1, 1);
  func__types__dirent__file_type_of_1 = create_function(entry__types__dirent__file_type_of_1, 1);
  func__types__dirent__fullname_of_1 = create_function(entry__types__dirent__fullname_of_1, 1);
  func__types__dirent__is_a_directory_1 = create_function(entry__types__dirent__is_a_directory_1, 1);
  func__types__dirent__is_a_regular_file_1 = create_function(entry__types__dirent__is_a_regular_file_1, 1);
  func__types__dirent__is_a_link_1 = create_function(entry__types__dirent__is_a_link_1, 1);
  string__578a5af303e9ccf = from_latin_1_string(".", 1);
  string__2d7981f4e6782beb = from_latin_1_string("..", 2);
  func__std__directory_18 = create_function(entry__std__directory_18, 0);
  func__std__directory_23 = create_function(entry__std__directory_23, 2);
  func__std__directory_1 = create_function(entry__std__directory_1, -1);
  func__std__get_network_addresses_1 = create_function(entry__std__get_network_addresses_1, 1);
  func__std__get_network_address_1 = create_function(entry__std__get_network_address_1, 1);
  func__types__addrinfo__connect_1 = create_function(entry__types__addrinfo__connect_1, 2);
  func__types__string__connect_1 = create_function(entry__types__string__connect_1, 2);
  func__types__addrinfo__listen_1 = create_function(entry__types__addrinfo__listen_1, 2);
  func__types__string__listen_1 = create_function(entry__types__string__listen_1, 2);
  func__types__file_descriptor__accept_1 = create_function(entry__types__file_descriptor__accept_1, 1);
  func__std__write_1 = create_function(entry__std__write_1, -1);
  func__std__writeln_1 = create_function(entry__std__writeln_1, -1);
  func__std__ewrite_1 = create_function(entry__std__ewrite_1, -1);
  func__std__ewriteln_1 = create_function(entry__std__ewriteln_1, -1);
  func__std__read_1 = create_function(entry__std__read_1, 1);
  func__std__readln_1 = create_function(entry__std__readln_1, 0);
  string__92241b5897c380d5 = from_latin_1_string("http://", 7);
  string__2d7981f4e6602bb4 = from_latin_1_string("-q", 2);
  string__2d7981f4e6602b8a = from_latin_1_string("-O", 2);
  string__578a5af303e9ccc = from_latin_1_string("-", 1);
  string__a622e2e97612a669 = from_latin_1_string("Load error (\042", 13);
  string__fa730c15f616bed = from_latin_1_string("\042)!", 3);
  func__std__load_1 = create_function(entry__std__load_1, 1);
  func__std__save_1 = create_function(entry__std__save_1, -1);
  string__2c0ae88b5d487d4d = from_latin_1_string("wget", 4);
}

static int already_run_phase_3 = false;

EXPORT void phase_3__basic__io(void) {
  if (already_run_phase_3) return;
  already_run_phase_3 = true;
  set_module("basic__io");
  set_used_namespaces(used_namespaces);
  var.std__MODE = create_future();
  define_single_assign_static("std", "MODE", get__std__MODE, &var.std__MODE);
  var.std__PARENTS = create_future();
  define_single_assign_static("std", "PARENTS", get__std__PARENTS, &var.std__PARENTS);
  var._wget = create_future();
  var.std__O_RDONLY = create__types__positive_integer(O_RDONLY);
  define_single_assign_static("std", "O_RDONLY", get__std__O_RDONLY, &var.std__O_RDONLY);
  var.std__O_WRONLY = create__types__positive_integer(O_WRONLY);
  define_single_assign_static("std", "O_WRONLY", get__std__O_WRONLY, &var.std__O_WRONLY);
  var.std__O_RDWR = create__types__positive_integer(O_RDWR);
  define_single_assign_static("std", "O_RDWR", get__std__O_RDWR, &var.std__O_RDWR);
  var.std__O_CREAT = create__types__positive_integer(O_CREAT);
  define_single_assign_static("std", "O_CREAT", get__std__O_CREAT, &var.std__O_CREAT);
  var.std__O_EXCL = create__types__positive_integer(O_EXCL);
  define_single_assign_static("std", "O_EXCL", get__std__O_EXCL, &var.std__O_EXCL);
  var.std__O_NOCTTY = create__types__positive_integer(O_NOCTTY);
  define_single_assign_static("std", "O_NOCTTY", get__std__O_NOCTTY, &var.std__O_NOCTTY);
  var.std__O_TRUNC = create__types__positive_integer(O_TRUNC);
  define_single_assign_static("std", "O_TRUNC", get__std__O_TRUNC, &var.std__O_TRUNC);
  var.std__O_APPEND = create__types__positive_integer(O_APPEND);
  define_single_assign_static("std", "O_APPEND", get__std__O_APPEND, &var.std__O_APPEND);
  var.std__O_NONBLOCK = create__types__positive_integer(O_NONBLOCK);
  define_single_assign_static("std", "O_NONBLOCK", get__std__O_NONBLOCK, &var.std__O_NONBLOCK);
  var.std__UNKNOWN = create__types__positive_integer(DT_UNKNOWN);
  define_single_assign_static("std", "UNKNOWN", get__std__UNKNOWN, &var.std__UNKNOWN);
  var.std__FIFO = create__types__positive_integer(DT_FIFO);
  define_single_assign_static("std", "FIFO", get__std__FIFO, &var.std__FIFO);
  var.std__CHARACTER_DEVICE = create__types__positive_integer(DT_CHR);
  define_single_assign_static("std", "CHARACTER_DEVICE", get__std__CHARACTER_DEVICE, &var.std__CHARACTER_DEVICE);
  var.std__DIRECTORY = create__types__positive_integer(DT_DIR);
  define_single_assign_static("std", "DIRECTORY", get__std__DIRECTORY, &var.std__DIRECTORY);
  var.std__BLOCK_DEVICE = create__types__positive_integer(DT_BLK);
  define_single_assign_static("std", "BLOCK_DEVICE", get__std__BLOCK_DEVICE, &var.std__BLOCK_DEVICE);
  var.std__REGULAR_FILE = create__types__positive_integer(DT_REG);
  define_single_assign_static("std", "REGULAR_FILE", get__std__REGULAR_FILE, &var.std__REGULAR_FILE);
  var.std__LINK = create__types__positive_integer(DT_LNK);
  define_single_assign_static("std", "LINK", get__std__LINK, &var.std__LINK);
  var.std__SOCKET = create__types__positive_integer(DT_SOCK);
  define_single_assign_static("std", "SOCKET", get__std__SOCKET, &var.std__SOCKET);
  var.std__EPERM = create__types__positive_integer(EPERM);
  define_single_assign_static("std", "EPERM", get__std__EPERM, &var.std__EPERM);
  var.std__ENOENT = create__types__positive_integer(ENOENT);
  define_single_assign_static("std", "ENOENT", get__std__ENOENT, &var.std__ENOENT);
  var.std__ESRCH = create__types__positive_integer(ESRCH);
  define_single_assign_static("std", "ESRCH", get__std__ESRCH, &var.std__ESRCH);
  var.std__EINTR = create__types__positive_integer(EINTR);
  define_single_assign_static("std", "EINTR", get__std__EINTR, &var.std__EINTR);
  var.std__EIO = create__types__positive_integer(EIO);
  define_single_assign_static("std", "EIO", get__std__EIO, &var.std__EIO);
  var.std__ENXIO = create__types__positive_integer(ENXIO);
  define_single_assign_static("std", "ENXIO", get__std__ENXIO, &var.std__ENXIO);
  var.std__E2BIG = create__types__positive_integer(E2BIG);
  define_single_assign_static("std", "E2BIG", get__std__E2BIG, &var.std__E2BIG);
  var.std__ENOEXEC = create__types__positive_integer(ENOEXEC);
  define_single_assign_static("std", "ENOEXEC", get__std__ENOEXEC, &var.std__ENOEXEC);
  var.std__EBADF = create__types__positive_integer(EBADF);
  define_single_assign_static("std", "EBADF", get__std__EBADF, &var.std__EBADF);
  var.std__ECHILD = create__types__positive_integer(ECHILD);
  define_single_assign_static("std", "ECHILD", get__std__ECHILD, &var.std__ECHILD);
  var.std__EAGAIN = create__types__positive_integer(EAGAIN);
  define_single_assign_static("std", "EAGAIN", get__std__EAGAIN, &var.std__EAGAIN);
  var.std__ENOMEM = create__types__positive_integer(ENOMEM);
  define_single_assign_static("std", "ENOMEM", get__std__ENOMEM, &var.std__ENOMEM);
  var.std__EACCES = create__types__positive_integer(EACCES);
  define_single_assign_static("std", "EACCES", get__std__EACCES, &var.std__EACCES);
  var.std__EFAULT = create__types__positive_integer(EFAULT);
  define_single_assign_static("std", "EFAULT", get__std__EFAULT, &var.std__EFAULT);
  var.std__ENOTBLK = create__types__positive_integer(ENOTBLK);
  define_single_assign_static("std", "ENOTBLK", get__std__ENOTBLK, &var.std__ENOTBLK);
  var.std__EBUSY = create__types__positive_integer(EBUSY);
  define_single_assign_static("std", "EBUSY", get__std__EBUSY, &var.std__EBUSY);
  var.std__EEXIST = create__types__positive_integer(EEXIST);
  define_single_assign_static("std", "EEXIST", get__std__EEXIST, &var.std__EEXIST);
  var.std__EXDEV = create__types__positive_integer(EXDEV);
  define_single_assign_static("std", "EXDEV", get__std__EXDEV, &var.std__EXDEV);
  var.std__ENODEV = create__types__positive_integer(ENODEV);
  define_single_assign_static("std", "ENODEV", get__std__ENODEV, &var.std__ENODEV);
  var.std__ENOTDIR = create__types__positive_integer(ENOTDIR);
  define_single_assign_static("std", "ENOTDIR", get__std__ENOTDIR, &var.std__ENOTDIR);
  var.std__EISDIR = create__types__positive_integer(EISDIR);
  define_single_assign_static("std", "EISDIR", get__std__EISDIR, &var.std__EISDIR);
  var.std__EINVAL = create__types__positive_integer(EINVAL);
  define_single_assign_static("std", "EINVAL", get__std__EINVAL, &var.std__EINVAL);
  var.std__ENFILE = create__types__positive_integer(ENFILE);
  define_single_assign_static("std", "ENFILE", get__std__ENFILE, &var.std__ENFILE);
  var.std__EMFILE = create__types__positive_integer(EMFILE);
  define_single_assign_static("std", "EMFILE", get__std__EMFILE, &var.std__EMFILE);
  var.std__ENOTTY = create__types__positive_integer(ENOTTY);
  define_single_assign_static("std", "ENOTTY", get__std__ENOTTY, &var.std__ENOTTY);
  var.std__ETXTBSY = create__types__positive_integer(ETXTBSY);
  define_single_assign_static("std", "ETXTBSY", get__std__ETXTBSY, &var.std__ETXTBSY);
  var.std__EFBIG = create__types__positive_integer(EFBIG);
  define_single_assign_static("std", "EFBIG", get__std__EFBIG, &var.std__EFBIG);
  var.std__ENOSPC = create__types__positive_integer(ENOSPC);
  define_single_assign_static("std", "ENOSPC", get__std__ENOSPC, &var.std__ENOSPC);
  var.std__ESPIPE = create__types__positive_integer(ESPIPE);
  define_single_assign_static("std", "ESPIPE", get__std__ESPIPE, &var.std__ESPIPE);
  var.std__EROFS = create__types__positive_integer(EROFS);
  define_single_assign_static("std", "EROFS", get__std__EROFS, &var.std__EROFS);
  var.std__EMLINK = create__types__positive_integer(EMLINK);
  define_single_assign_static("std", "EMLINK", get__std__EMLINK, &var.std__EMLINK);
  var.std__EPIPE = create__types__positive_integer(EPIPE);
  define_single_assign_static("std", "EPIPE", get__std__EPIPE, &var.std__EPIPE);
  var.std__EDOM = create__types__positive_integer(EDOM);
  define_single_assign_static("std", "EDOM", get__std__EDOM, &var.std__EDOM);
  var.std__ERANGE = create__types__positive_integer(ERANGE);
  define_single_assign_static("std", "ERANGE", get__std__ERANGE, &var.std__ERANGE);
  var.std__raise_error = create_future();
  define_single_assign_static("std", "raise_error", get__std__raise_error, &var.std__raise_error);
  var.std__check_error = create_future();
  define_single_assign_static("std", "check_error", get__std__check_error, &var.std__check_error);
  var.std__errno = create_future();
  define_single_assign_static("std", "errno", get__std__errno, &var.std__errno);
  var.std__strerror = create_future();
  define_single_assign_static("std", "strerror", get__std__strerror, &var.std__strerror);
  var.types__stat = create_future_with_prototype(create__types__stat(NULL));
  define_single_assign_static("types", "stat", get__types__stat, &var.types__stat);
  var.std__stat = create_future();
  define_single_assign_static("std", "stat", get__std__stat, &var.std__stat);
  var.std__file_exists = create_future();
  define_single_assign_static("std", "file_exists", get__std__file_exists, &var.std__file_exists);
  var.types__file_descriptor = create_future_with_prototype(create__types__file_descriptor(-1));
  define_single_assign_static("types", "file_descriptor", get__types__file_descriptor, &var.types__file_descriptor);
  var.std__STDIN_FILENO = create__types__file_descriptor(STDIN_FILENO);
  define_single_assign_static("std", "STDIN_FILENO", get__std__STDIN_FILENO, &var.std__STDIN_FILENO);
  var.std__STDOUT_FILENO = create__types__file_descriptor(STDOUT_FILENO);
  define_single_assign_static("std", "STDOUT_FILENO", get__std__STDOUT_FILENO, &var.std__STDOUT_FILENO);
  var.std__STDERR_FILENO = create__types__file_descriptor(STDERR_FILENO);
  define_single_assign_static("std", "STDERR_FILENO", get__std__STDERR_FILENO, &var.std__STDERR_FILENO);
  var.std__create_file_descriptor = create_future();
  define_single_assign_static("std", "create_file_descriptor", get__std__create_file_descriptor, &var.std__create_file_descriptor);
  var.std__open_file = create_future();
  define_single_assign_static("std", "open_file", get__std__open_file, &var.std__open_file);
  var.std__open_file_for_reading = create_future();
  define_single_assign_static("std", "open_file_for_reading", get__std__open_file_for_reading, &var.std__open_file_for_reading);
  var.std__open_file_for_writing = create_future();
  define_single_assign_static("std", "open_file_for_writing", get__std__open_file_for_writing, &var.std__open_file_for_writing);
  var.std__open_file_for_reading_and_writing = create_future();
  define_single_assign_static("std", "open_file_for_reading_and_writing", get__std__open_file_for_reading_and_writing, &var.std__open_file_for_reading_and_writing);
  var.std__create_file = create_future();
  define_single_assign_static("std", "create_file", get__std__create_file, &var.std__create_file);
  var.std__atomic_write_to = create_future();
  define_single_assign_static("std", "atomic_write_to", get__std__atomic_write_to, &var.std__atomic_write_to);
  var.std__load_file = create_future();
  define_single_assign_static("std", "load_file", get__std__load_file, &var.std__load_file);
  var.std__save_file = create_future();
  define_single_assign_static("std", "save_file", get__std__save_file, &var.std__save_file);
  var.std__delete_file = create_future();
  define_single_assign_static("std", "delete_file", get__std__delete_file, &var.std__delete_file);
  var.std__get_pid = create_future();
  define_single_assign_static("std", "get_pid", get__std__get_pid, &var.std__get_pid);
  var.std__wait_pid = create_future();
  define_single_assign_static("std", "wait_pid", get__std__wait_pid, &var.std__wait_pid);
  var.std__wait_for_io = create_future();
  define_single_assign_static("std", "wait_for_io", get__std__wait_for_io, &var.std__wait_for_io);
  var.std__current_path = create_future();
  define_single_assign_static("std", "current_path", get__std__current_path, &var.std__current_path);
  var.std__chdir = create_future();
  define_single_assign_static("std", "chdir", get__std__chdir, &var.std__chdir);
  var.std__change_directory = create_future();
  define_single_assign_static("std", "change_directory", get__std__change_directory, &var.std__change_directory);
  var.std__mkdir = create_future();
  define_single_assign_static("std", "mkdir", get__std__mkdir, &var.std__mkdir);
  var.std__create_directory = create_future();
  define_single_assign_static("std", "create_directory", get__std__create_directory, &var.std__create_directory);
  var.std__fullname = create_future();
  define_single_assign_static("std", "fullname", get__std__fullname, &var.std__fullname);
  var.types__DIR = create_future_with_prototype(create__types__DIR(NULL));
  define_single_assign_static("types", "DIR", get__types__DIR, &var.types__DIR);
  var.types__dirent = create_future_with_prototype(create__types__dirent(NULL));
  define_single_assign_static("types", "dirent", get__types__dirent, &var.types__dirent);
  var.std__opendir = create_future();
  define_single_assign_static("std", "opendir", get__std__opendir, &var.std__opendir);
  var.std__directory = create_future();
  define_single_assign_static("std", "directory", get__std__directory, &var.std__directory);
  var.types__addrinfo = create_future_with_prototype(create__types__addrinfo(NULL));
  define_single_assign_static("types", "addrinfo", get__types__addrinfo, &var.types__addrinfo);
  var.std__get_network_addresses = create_future();
  define_single_assign_static("std", "get_network_addresses", get__std__get_network_addresses, &var.std__get_network_addresses);
  var.std__get_network_address = create_future();
  define_single_assign_static("std", "get_network_address", get__std__get_network_address, &var.std__get_network_address);
  define_single_assign_dynamic("std", "write", get__std__write, define__std__write, &dyna_idx__std__write);
  var.std__writeln = create_future();
  define_single_assign_static("std", "writeln", get__std__writeln, &var.std__writeln);
  define_single_assign_dynamic("std", "ewrite", get__std__ewrite, define__std__ewrite, &dyna_idx__std__ewrite);
  var.std__ewriteln = create_future();
  define_single_assign_static("std", "ewriteln", get__std__ewriteln, &var.std__ewriteln);
  define_single_assign_dynamic("std", "read", get__std__read, define__std__read, &dyna_idx__std__read);
  var.std__readln = create_future();
  define_single_assign_static("std", "readln", get__std__readln, &var.std__readln);
  var.std__load = create_future();
  define_single_assign_static("std", "load", get__std__load, &var.std__load);
  var.std__save = create_future();
  define_single_assign_static("std", "save", get__std__save, &var.std__save);
}

static int already_run_phase_4 = false;

EXPORT void phase_4__basic__io(void) {
  if (already_run_phase_4) return;
  already_run_phase_4 = true;
  set_module("basic__io");
  set_used_namespaces(used_namespaces);
  use_read_only(NULL, "ANY_CHARACTER", &get__ANY_CHARACTER, &get_value_or_future__ANY_CHARACTER);
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
  use_read_only(NULL, "open_file", &get__open_file, &get_value_or_future__open_file);
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
  use_polymorphic_function(NULL, "to_integer", &get__to_integer, &poly_idx__to_integer);
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
  define_method("types", "stat", poly_idx__device_of, func__types__stat__device_of_1);
  define_method("types", "stat", poly_idx__inode_of, func__types__stat__inode_of_1);
  define_method("types", "stat", poly_idx__mode_of, func__types__stat__mode_of_1);
  define_method("types", "stat", poly_idx__link_count_of, func__types__stat__link_count_of_1);
  define_method("types", "stat", poly_idx__user_id_of, func__types__stat__user_id_of_1);
  define_method("types", "stat", poly_idx__group_id_of, func__types__stat__group_id_of_1);
  define_method("types", "stat", poly_idx__size_of, func__types__stat__size_of_1);
  define_method("types", "stat", poly_idx__block_size_of, func__types__stat__block_size_of_1);
  define_method("types", "stat", poly_idx__sector_count_of, func__types__stat__sector_count_of_1);
  define_method("types", "stat", poly_idx__access_time_of, func__types__stat__access_time_of_1);
  define_method("types", "stat", poly_idx__modification_time_of, func__types__stat__modification_time_of_1);
  define_method("types", "stat", poly_idx__status_change_time_of, func__types__stat__status_change_time_of_1);
  define_method("types", "stat", poly_idx__is_a_directory, func__types__stat__is_a_directory_1);
  define_method("types", "stat", poly_idx__is_a_regular_file, func__types__stat__is_a_regular_file_1);
  define_method("types", "stat", poly_idx__is_a_link, func__types__stat__is_a_link_1);
  define_method("types", "file_descriptor", poly_idx__to_integer, func__types__file_descriptor__to_integer_1);
  define_method("types", "file_descriptor", poly_idx__equal, func__types__file_descriptor__equal_1);
  define_method("types", "file_descriptor", poly_idx__less, func__types__file_descriptor__less_1);
  define_method("types", "file_descriptor", poly_idx__hash, func__types__file_descriptor__hash_1);
  define_method("types", "file_descriptor", poly_idx__close, func__types__file_descriptor__close_1);
  define_method("types", "file_descriptor", poly_idx__read_some_bytes_from, func__types__file_descriptor__read_some_bytes_from_1);
  define_method("types", "file_descriptor", poly_idx__read_from, func__types__file_descriptor__read_from_1);
  define_method("types", "file_descriptor", poly_idx__write_some_bytes_to, func__types__file_descriptor__write_some_bytes_to_1);
  define_method("types", "file_descriptor", poly_idx__write_to, func__types__file_descriptor__write_to_1);
  define_method("types", "file_descriptor", poly_idx__flush, func__types__file_descriptor__flush_1);
  define_method("types", "file_descriptor", poly_idx__std__ioctl, func__types__file_descriptor__std__ioctl_1);
  define_method("types", "file_descriptor", poly_idx__std__get_terminal_size, func__types__file_descriptor__std__get_terminal_size_1);
  define_method("types", "DIR", poly_idx__close, func__types__DIR__close_1);
  define_method("types", "DIR", poly_idx__get, func__types__DIR__get_1);
  define_method("types", "dirent", poly_idx__filename_of, func__types__dirent__filename_of_1);
  define_method("types", "dirent", poly_idx__inode_of, func__types__dirent__inode_of_1);
  define_method("types", "dirent", poly_idx__file_type_of, func__types__dirent__file_type_of_1);
  define_method("types", "dirent", poly_idx__fullname_of, func__types__dirent__fullname_of_1);
  define_method("types", "dirent", poly_idx__is_a_directory, func__types__dirent__is_a_directory_1);
  define_method("types", "dirent", poly_idx__is_a_regular_file, func__types__dirent__is_a_regular_file_1);
  define_method("types", "dirent", poly_idx__is_a_link, func__types__dirent__is_a_link_1);
  define_method("types", "addrinfo", poly_idx__connect, func__types__addrinfo__connect_1);
  define_method("types", "string", poly_idx__connect, func__types__string__connect_1);
  define_method("types", "addrinfo", poly_idx__listen, func__types__addrinfo__listen_1);
  define_method("types", "string", poly_idx__listen, func__types__string__listen_1);
  define_method("types", "file_descriptor", poly_idx__accept, func__types__file_descriptor__accept_1);
}

static int already_run_phase_5 = false;

EXPORT void phase_5__basic__io(void) {
  if (already_run_phase_5) return;
  already_run_phase_5 = true;
  initialize_future(var.std__MODE, unique__std__MODE);
  initialize_future(var.std__PARENTS, unique__std__PARENTS);
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
  initialize_future(var.std__raise_error, func__std__raise_error_1);
  initialize_future(var.std__check_error, func__std__check_error_1);
  initialize_future(var.std__errno, func__std__errno_1);
  initialize_future(var.std__strerror, func__std__strerror_1);
  assign_value(&var.types__stat, get__types__object());
  initialize_future(var.std__stat, func__std__stat_1);
  initialize_future(var.std__file_exists, func__std__file_exists_1);
  assign_value(&var.types__file_descriptor, get__types__object());
  initialize_future(var.std__create_file_descriptor, func__std__create_file_descriptor_1);
  assign_variable(&var._posix_open, &func__posix_open_1);
  initialize_future(var.std__open_file, func__std__open_file_1);
  initialize_future(var.std__open_file_for_reading, func__std__open_file_for_reading_1);
  initialize_future(var.std__open_file_for_writing, func__std__open_file_for_writing_1);
  initialize_future(var.std__open_file_for_reading_and_writing, func__std__open_file_for_reading_and_writing_1);
  initialize_future(var.std__create_file, func__std__create_file_1);
  assign_variable(&var._file_description, &func__file_description_1);
  assign_variable(&var._WriteError, &func__WriteError_1);
  initialize_future(var.std__atomic_write_to, func__std__atomic_write_to_1);
  initialize_future(var.std__load_file, func__std__load_file_1);
  initialize_future(var.std__save_file, func__std__save_file_1);
  assign_variable(&var._ioctl_value, &func__ioctl_value_1);
  assign_variable(&var._posix_unlink, &func__posix_unlink_1);
  initialize_future(var.std__delete_file, func__std__delete_file_1);
  assign_variable(&var._wait_for_io_ready, &func__wait_for_io_ready_1);
  initialize_future(var.std__get_pid, func__std__get_pid_1);
  initialize_future(var.std__wait_pid, func__std__wait_pid_1);
  initialize_future(var.std__wait_for_io, func__std__wait_for_io_1);
  initialize_future(var.std__current_path, func__std__current_path_1);
  initialize_future(var.std__chdir, func__std__chdir_1);
  initialize_future(var.std__change_directory, func__std__change_directory_1);
  assign_variable(&var._clib_mkdir, &func__clib_mkdir_1);
  initialize_future(var.std__mkdir, func__std__mkdir_1);
  initialize_future(var.std__create_directory, func__std__create_directory_1);
  initialize_future(var.std__fullname, func__std__fullname_1);
  assign_value(&var.types__DIR, get__types__object());
  assign_value(&var.types__dirent, get__types__object());
  initialize_future(var.std__opendir, func__std__opendir_1);
  initialize_future(var.std__directory, func__std__directory_1);
  assign_value(&var.types__addrinfo, get__types__object());
  initialize_future(var.std__get_network_addresses, func__std__get_network_addresses_1);
  initialize_future(var.std__get_network_address, func__std__get_network_address_1);
  define__std__write(func__std__write_1);
  initialize_future(var.std__writeln, func__std__writeln_1);
  define__std__ewrite(func__std__ewrite_1);
  initialize_future(var.std__ewriteln, func__std__ewriteln_1);
  define__std__read(func__std__read_1);
  initialize_future(var.std__readln, func__std__readln_1);
  initialize_future(var.std__load, func__std__load_1);
  initialize_future(var.std__save, func__std__save_1);
}

static int already_run_phase_6 = false;

EXPORT void phase_6__basic__io(void) {
  if (already_run_phase_6) return;
  already_run_phase_6 = true;
  register_collector(collect__basic__io);
}
