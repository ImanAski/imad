#include "edef.h"
#include "efunc.h"
#include "estruct.h"
#include "line.h"
#include "utf8.h"

/*
 * Move the cursor to the beginning of the line
 */
int gotobol(int f, int n) {
  curwp->w_doto = 0;
  return TRUE;
}

/*
 * Move the cursor to the end of the line
 */
int gotoeol(int f, int n) {
  curwp->w_doto = llength(curwp->w_dotp);
  return TRUE;
}

int gotobob(int f, int n) {
  curwp->w_dotp = lforw(curbp->b_linep);
  curwp->w_doto = 0;
  curwp->w_flag |= WFHARD;
  return TRUE;
}
