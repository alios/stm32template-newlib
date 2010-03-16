#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>

#include "devices.h"
#include "console.h"
#include "irq.h"

extern int8_t _sheap;
extern int8_t _eheap;
static const int8_t* eheap_p = &_eheap;
static const int8_t* sheap_p = &_sheap;

static intptr_t heap_ptr;

const devoptab_t *devoptab_list[] = {
  &devoptab_console, /* stdin */
  &devoptab_console, /* stdout */
  &devoptab_console, /* stderr */
  NULL
};

long _write_r(struct _reent *ptr, int fd, const void *buf, int cnt)
{
  return devoptab_list[fd]->write_r(ptr, fd, buf, cnt);
}

long _read_r(struct _reent *r, int fd, char *ptr, int len )
{
  return devoptab_list[fd]->read_r(r, fd, ptr, len);
}

long _close_r(struct _reent *r, int fd)
{
  return devoptab_list[fd]->close_r(r, fd);
}

int _open_r (struct _reent *ptr, const char *file, int flags, int mode)
{
  int which_devoptab = 0;
  int fd = -1;
  
  /* search for "file" in dotab_list[].name */
  do {
    const devoptab_t* dev = devoptab_list[which_devoptab];
    
    if(dev == NULL)
      break;
    
    if(strcmp(dev->name, file ) == 0 ) 
      {
	fd = which_devoptab;
	break;
      }
  } while(devoptab_list[which_devoptab++]);

  /* if we found the requested file/device, invoke the device's open_r() */
  if(fd != -1) {
      devoptab_list[fd]->open_r(ptr, file, flags, mode);
  } else {    
    errno = ENODEV;
  }

  return fd;
}

int _stat_r (struct _reent *_r, const char *file, struct stat *pstat)
{
   pstat->st_mode = S_IFCHR;
   return 0;
}

int _fstat_r ( struct _reent *_r, int fd, struct stat *pstat)
{
   pstat->st_mode = S_IFCHR;
   return 0;
}

off_t _lseek_r( struct _reent *_r, int fd, off_t pos, int whence )
{
   return 0;
}

int _isatty( struct _reent *_r, int fd)
{
  errno = ENOTTY;
  return 0;
}

void *_sbrk(intptr_t incr)
{
  void* retval = 0;
  intptr_t newbrk = (intptr_t)((size_t)heap_ptr + (size_t)incr);

  if(newbrk >=  (intptr_t)eheap_p)
    {
      errno = ENOMEM;
      retval = (void *)-1;
    }
  else 
    {
      heap_ptr = newbrk;
    }

  return  retval;
}

void _init_crt1() 
{
  /* set the heap with 0xff */
  {
    const size_t heapsize = ((size_t)(eheap_p)) - ((size_t)sheap_p);
    memset(&_sheap, 0xff, heapsize);

    heap_ptr = (const intptr_t)sheap_p;
  }
}
