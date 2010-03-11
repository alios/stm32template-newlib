#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>

#include "irq.h"

#define BUFFERSIZE 0x100

extern void* _sheap;
extern void* _eheap;

static void* heap_ptr = &_sheap;

typedef struct ringbuffer {
  size_t read_i;
  size_t write_i;
  uint8_t buffer[BUFFERSIZE];
} ringbuffer_t;

typedef struct {
   const char *name;
   int (*open_r )( struct _reent *r, const char *path, int flags, int mode );
   int (*close_r )( struct _reent *r, int fd ); 
   long (*write_r ) ( struct _reent *r, int fd, const char *ptr, int len );
   long (*read_r )( struct _reent *r, int fd, char *ptr, int len );
} devoptab_t;


ringbuffer_t stdout_b; 

//const devoptab_t devoptab_console 


void _init_crt1() 
{
  /* set the heap with 0xff */
  {
    const ssize_t heapsize = ((ssize_t)(_eheap)) - ((ssize_t)_sheap);
    memset(&_sheap, 0xff, heapsize);
  }

  stdout_b.read_i = 0;
  stdout_b.write_i = 0;
}


void *_sbrk(intptr_t incr)
{
  void* retval = 0;
  disable_irqs();

  void* newbrk = (void *)((ssize_t)heap_ptr + (ssize_t)incr);


  if(newbrk >= _eheap)
    {
      errno = ENOMEM;
      retval = (void *)-1;
    }
  else 
    {
      heap_ptr = (void *)newbrk;
    }

  enable_irqs();
  return  retval;
}

