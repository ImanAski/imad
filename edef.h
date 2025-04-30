
#ifndef EDEF_H_
#define EDEF_H_

#include <stdlib.h>
#include <string.h>

extern int fillcol;           /* fill column */
extern int gmode;             /* global editor mode */
extern int gflags;            /* global control flag */
extern int gfcolor;           /* global foreground color */
extern int gbcolor;           /* global background color */
extern int discmd;            /* display command flag         */
extern int vtrow;             /* Row location of SW cursor */
extern int vtcol;             /* Column location of SW cursor */
extern int ttrow;             /* Row location of HW cursor */
extern int ttcol;             /* Column location of HW cursor */
extern int lbound;            /* leftmost column of current line */
extern int eolexist;          /* does clear to EOL exist?     */
extern int mpresf;            /* Stuff in message line        */
extern struct buffer *bstore; /* buffer to save some shit prolly, who cares? */

extern struct window *curwp;  /* current window */
extern struct window *wheadp; /* head of list of windows */
extern struct buffer *curbp;  /* current buffer */
extern struct buffer *bheadp; /* head of list of buffers */
extern struct buffer *blistp; /* list of buffers */

extern int tabmask;
extern int seed;               /* random number seed */
extern int lastkey;            /* last key stroke */
extern char *fline;            /* dynamic return line */
extern int flen;               /* current length of line */
extern int resetflag;          /* meh? */
extern struct window *swindow; /* saved window pointer */

// Terminal Table
extern struct terminal term;
#endif // EDEF_H_
