#include "edef.h"
#include "estruct.h"

int vtrow = 0;      /* Row location of SW cursor */
int vtcol = 0;      /* Column location of SW cursor */
int ttrow = BIGGUY; /* Row location of HW cursor */
int ttcol = BIGGUY; /* Column location of HW cursor */

int currow;            /* Cursor row                   */
int curcol;            /* Cursor column                */
int thisflag;          /* Flags, this command          */
int lastflag;          /* Flags, last command          */
int curgoal;           /* Goal for C-P, C-N            */
struct window *curwp;  /* Current window               */
struct buffer *curbp;  /* Current buffer               */
struct window *wheadp; /* Head of list of windows      */
struct buffer *bheadp; /* Head of list of buffers      */
struct buffer *blistp; /* Buffer for C-X C-B           */
