#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>

#include "devices.h"
#include "console.h"

#define BUFFERSIZE 0x100

typedef struct ringbuffer {
  size_t read_i;
  size_t write_i;
  uint8_t buffer[BUFFERSIZE];
} ringbuffer_t;

static int console_open_r(struct _reent *r, const char *path, int flags, int mode);
static int console_close_r(struct _reent *r, int fd);
static long console_write_r(struct _reent *r, int fd, const char *ptr, int len);
static long console_read_r(struct _reent *r, int fd, char *ptr, int len );


ringbuffer_t stdout_b; 


const devoptab_t devoptab_console = { "console", 
				      console_open_r, 
				      console_close_r,
				      console_write_r,
				      console_read_r };


static int console_open_r(struct _reent *r, const char *path, int flags, int mode)
{
  errno = ENXIO;
  return -1;
}

static int console_close_r(struct _reent *r, int fd)
{
  errno = EBADF;
  return -1;
} 

static long console_write_r(struct _reent *r, int fd, const char *ptr, int len)
{
  errno = EBADF;
  return -1;
}
 
static long console_read_r(struct _reent *r, int fd, char *ptr, int len )
{
  errno = EBADF;
  return -1;
}
