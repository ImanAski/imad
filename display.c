#include "edef.h"
#include "efunc.h"
#include "estruct.h"
#include "line.h"
#include "utf8.h"
#include "wrapper.h"
#include <stdarg.h>
#include <unistd.h>

#if UNIX
#include <signal.h>
#endif
#ifdef SIGWINCH
#include <sys/ioctl.h>
/* for window size changes */
int chg_width, chg_height;
#endif

struct video {
  int v_flag;
#if COLOR
  int v_fcolor;  /* forground color */
  int v_bcolor;  /* background color */
  int v_rfcolor; /* requested foreground color */
  int v_rbcolor; /* request background color */
#endif           /* if COLOR */
  unicode_t v_text[1];
};

static struct video **vscreen;
#if MEMMAP == 0 || SCROLLCODE
static struct video **pscreen;
#endif
static void mlputi(int i, int r);
static void mlputli(long l, int r);
static void mlputf(int s);

static int displaying = TRUE;

void vtinit(void) {
  int i;
  struct video *vp;

  TTopen();
  TTkopen();
  TTrev(FALSE);
  vscreen = xmalloc(term.t_mrow * sizeof(struct video *));

#if MEMMAP
  pscreen = xmalloc(term.t_mrow * sizeof(struct video *));
#endif
  for (i = 0; i < term.t_mrow; ++i) {
    vp = xmalloc(sizeof(struct video) * term.t_mcol * 4);
    vp->v_flag = 0;
#if COLOR
    vp->v_rfcolor = 7;
    vp->v_rbcolor = 0;
#endif
    vscreen[i] = vp;
#if MEMMAP == 0 || SCROLLCODE
    vp = xmalloc(sizeof(struct video) + term.t_mcol * 4);
    vp->v_flag = 0;
    pscreen[i] = vp;
#endif
  }
}

void movecursor(int row, int col) {
  if (row != ttrow || col != ttcol) {
    ttrow = row;
    ttcol = col;
    TTmove(row, col);
  }
}

void mlerase(void) {
  int i;

  movecursor(term.t_nrow, 0);
  if (discmd == FALSE)
    return;

#if COLOR
  TTforg(7);
  TTbacg(0);
#endif
  if (eolexist == TRUE)
    TTeeol();
  else {
    for (i = 0; i < term.t_ncol - 1; i++)
      TTputc(' ');
    movecursor(term.t_nrow, 1); /* force the move! */
    movecursor(term.t_nrow, 0);
  }
  TTflush();
  mpresf = FALSE;
}

void mlwrite(const char *fmt, ...) {
  int c;
  va_list ap;

  if (discmd == FALSE) {
    movecursor(term.t_nrow, 0);
    return;
  }
#if COLOR
  /* set up the proper colors for the command line */
  TTforg(7);
  TTbacg(0);
#endif

  if (eolexist == FALSE) {
    mlerase();
    TTflush();
  }

  movecursor(term.t_nrow, 0);
  va_start(ap, fmt);
  while ((c = *fmt++) != 0) {
    if (c != '%') {
      TTputc(c);
      ++ttcol;
    } else {
      c = *fmt++;
      switch (c) {
      case 'd':
        mlputi(va_arg(ap, int), 10);
        break;

      case 'o':
        mlputi(va_arg(ap, int), 8);
        break;

      case 'x':
        mlputi(va_arg(ap, int), 16);
        break;

      case 'D':
        mlputli(va_arg(ap, long), 10);
        break;

      case 's':
        mlputs(va_arg(ap, char *));
        break;

      case 'f':
        mlputf(va_arg(ap, int));
        break;

      default:
        TTputc(c);
        ++ttcol;
      }
    }
  }
  va_end(ap);

  /* if we can, erase to the end of screen */
  if (eolexist == TRUE)
    TTeeol();
  TTflush();
  mpresf = TRUE;
}

static void mlputi(int i, int r) {
  int q;
  static char hexdigits[] = "0123456789ABCDEF";

  if (i < 0) {
    i = -i;
    TTputc('-');
  }

  q = i / r;

  if (q != 0)
    mlputi(q, r);

  TTputc(hexdigits[i % r]);
  ++ttcol;
}

void mlputs(char *s) {
  int c;

  while ((c = *s++) != 0) {
    TTputc(c);
    ++ttcol;
  }
}

static void mlputf(int s) {
  int i; /* integer portion of number */
  int f; /* fractional portion of number */

  /* break it up */
  i = s / 100;
  f = s % 100;

  /* send out the integer portion */
  mlputi(i, 10);
  TTputc('.');
  TTputc((f / 10) + '0');
  TTputc((f % 10) + '0');
  ttcol += 3;
}
