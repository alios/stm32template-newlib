#ifndef __DEVICES_H__
#define __DEVICES_H__

typedef struct {
   const char *name;
   int (*open_r )( struct _reent *r, const char *path, int flags, int mode );
   int (*close_r )( struct _reent *r, int fd ); 
   long (*write_r ) ( struct _reent *r, int fd, const char *ptr, int len );
   long (*read_r )( struct _reent *r, int fd, char *ptr, int len );
} devoptab_t;

#endif /* __DEVICES_H__ */
