#include <stdio.h>
#include <malloc.h>

int main(void)
{
  int i = 1;
  char* cs = NULL;
  const size_t SIZE = 1024;

  for(;;) {
    if((cs = malloc(SIZE)) == NULL)
      {
	for(;;);
      }
    printf("hello world! this is iteration %d\n", i);
    snprintf(cs, SIZE, "hello buffer! this is iteration %d\n", i++);

    free(cs);
  }

}

