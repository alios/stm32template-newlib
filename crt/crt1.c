#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>

#include "irq.h"

extern int8_t _sheap;
extern int8_t _eheap;
static const int8_t* eheap_p = &_eheap;
static const int8_t* sheap_p = &_sheap;
static intptr_t heap_ptr;

size_t heap_peak = 0x0;

long _write_r(struct _reent *_r, int fd, const void *buf, int cnt)
{
  _r->_errno = EBADF;
  return -1;
}

long _read_r(struct _reent *_r, int fd, char *ptr, int len )
{
  _r->_errno = EBADF;
  return -1;
}

off_t _lseek_r( struct _reent *_r, int fd, off_t pos, int whence )
{
   return 0;
}

int _isatty( struct _reent *_r, int fd)
{
  _r->_errno = ENOTTY;
  return 0;
}

int _fstat_r ( struct _reent *_r, int fd, struct stat *pstat)
{
   pstat->st_mode = S_IFCHR;
   return 0;
}

long _close_r(struct _reent *_r, int fd)
{
  _r->_errno = EBADF;
  return -1;
}

/*
int _open_r (struct _reent *_r, const char *file, int flags, int mode)
{ 
  _r->_errno = ENODEV;
  return -1;
}
*/


void *_sbrk_r(struct _reent *r, intptr_t incr)
{
  void* retval = 0;
  intptr_t newbrk = (intptr_t)((size_t)heap_ptr + (size_t)incr);

  if(newbrk >=  (intptr_t)eheap_p)
    {
      r->_errno = ENOMEM;
      retval = (void *)-1;
    }
  else 
    {
      const size_t new_size = ((size_t)newbrk) - ((size_t)sheap_p);
      heap_peak = (heap_peak < new_size) ? new_size : heap_peak;
      retval = (void*)heap_ptr;
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
