#include "edef.h"
#include "efunc.h"
#include "estruct.h"
#include "line.h"
#include <stdlib.h>
#include <string.h>

struct buffer *bfind(char *bname, int cflag, int bflag) {
  struct buffer *bp;
  struct buffer *sp;
  struct line *lp;

  bp = bheadp;
  while (bp != NULL) {
    if (strcmp(bname, bp->b_bname) == 0) {
      return bp;
    }
    bp = bp->b_bufp;
  }
  if (cflag != FALSE) {
    if ((bp = (struct buffer *)malloc(sizeof(struct buffer))) == NULL) {
      return NULL;
      if ((lalloc(0)) == NULL) {
        return NULL;
      }
    }
  }
  return bp;
}
