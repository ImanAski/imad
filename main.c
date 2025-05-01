
#define maindef

#include "edef.h"
#include "efunc.h"
#include "estruct.h"
#include "version.h"
#include <stdio.h>

void usage(int status) {
  printf("Usage: %s filename\n", PROGRAM_NAME);
  printf(" or %s [options]\n\n", PROGRAM_NAME);

  exit(status);
}

int main(int argc, char **argv) {
  if (argc == 2) {
    if (strcmp(argv[1], "--help") == 0) {
      usage(EXIT_FAILURE);
    }
    if (strcmp(argv[1], "--usage") == 0) {
      version();
      exit(EXIT_SUCCESS);
    }
  }

  printf("hello\n\n");
  // Initalize the editor
  // vtinit();
  // edinit("main");
  // varinit();

  return EXIT_SUCCESS;
}

void edinit(char *bname) {
  struct buffer *bp;
  struct window *wp;

  bp = bfind(bname, TRUE, 0);
  blistp = bfind("*LIST*", TRUE, BFINVS);
  wp = (struct window *)malloc(sizeof(struct window));
  if (bp == NULL || wp == NULL || blistp == NULL) {
    exit(1);
  }

  curbp = bp;
  wheadp = wp;
  curwp = wp;
  wp->w_wndp = NULL;
  wp->w_bufp = bp;
  bp->b_nwnd = 1;

#if COLOR
  /* initalize colors to global defaults */
  wp->w_fcolor = gfcolor;
  wp->w_bcolor = gbcolor;
#endif /* if color */
  wp->w_ntrows = term.t_nrow - 1;
  wp->w_force = 0;
  wp->w_flag = WFMODE | WFHARD; /* Full. */
}
