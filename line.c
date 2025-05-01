#include "line.h"
#include "edef.h"
#include "efunc.h"
#include "estruct.h"
#include "utf8.h"

#define BLOCK_SIZE 16 /* Line block chunk size. */

struct line *lalloc(int used) {
  struct line *lp;
  int size;

  size = (used + BLOCK_SIZE - 1) & ~(BLOCK_SIZE - 1);
  if (size == 0)       /* Assume that is an empty. */
    size = BLOCK_SIZE; /* Line is for type-in. */
  if ((lp = (struct line *)malloc(sizeof(struct line) + size)) == NULL) {
    mlwrite("(OUT OF MEMORY)");
    return NULL;
  }
  lp->l_size = size;
  lp->l_used = used;
  return lp;
}
