#include <stdio.h>
#include <stdlib.h>

void *xmalloc(size_t size) {
  void *ret = malloc(size);
  if (!ret) {
    die("AAAAAAAAAAAhhhhhhh");
  }
  return ret;
}
