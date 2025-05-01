

#define MAX_COL 500
#define MAX_ROW 500

/* Internal constants */

#define NFILEN 256  /* # of bytes, file name */
#define NBUFN 16    /* # of bytes, buffer name */
#define BIGGUY 1000 /* just a big guy of number :) */
#define KBLOCK 250  /* sizeof kill buffer chunks */

#define CONTROL 0x1000000
#define META 0x2000000

#ifdef FALSE
#undef FALSE
#endif // FALSE

#ifdef TRUE
#undef TRUE
#endif // TRUE

#define FALSE 0
#define TRUE 1
#define ABORT 2
#define FAILED 3

#define STOP 0
#define START 1
#define RECORD 2

#ifndef AUTOCONF

/*   Special keyboard definitions            */

#define VT220 0 /* Use keypad escapes P.K.      */
#define VT100 0 /* Handle VT100 style keypad.   */

/*	Terminal Output definitions		*/

#define ANSI 0    /* ANSI escape sequences        */
#define VMSVT 0   /* various VMS terminal entries */
#define VT52 0    /* VT52 terminal (Zenith).      */
#define TERMCAP 0 /* Use TERMCAP                  */
#define IBMPC 1   /* IBM-PC CGA/MONO/EGA driver   */

#else

#define VT220 (UNIX | VMS)
#define VT100 0

#define ANSI 0
#define VMSVT VMS
#define VT52 0
#define TERMCAP UNIX
#define IBMPC MSDOS

#endif // AUTOCONF

#if IBMPC
#define MEMMAP 1
#else
#define MEMMAP 0
#endif

#ifndef AUTOCONF

#define COLOR 1
#define FILOCK 1

#else

#define COLOR MSDOS
#ifdef SVR4
#define FILOCK 1
#else
#define FILOCK BSD
#endif

#endif // AUTOCONF

#define ISRCH 1
#define SCROLLCODE 1

#if CLEAN
#define exit(a) cexit(a)
#endif // CLEAN

struct window {
  struct window *w_wndp; /* Next window                  */
  struct buffer *w_bufp; /* Buffer displayed in window   */
  struct line *w_linep;  /* Top line in the window       */
  struct line *w_dotp;   /* Line containing "."          */
  struct line *w_markp;  /* Line containing "mark"       */
  int w_doto;            /* Byte offset for "."          */
  int w_marko;           /* Byte offset for "mark"       */
  int w_toprow;          /* Origin 0 top row of window   */
  int w_ntrows;          /* # of rows of text in window  */
  char w_force;          /* If NZ, forcing row.          */
  char w_flag;           /* Flags.                       */
#if COLOR
  char w_fcolor; /* current forground color      */
  char w_bcolor; /* current background color     */
#endif
};

#define WFFORCE 0x01 /* Window needs forced reframe  */
#define WFMOVE 0x02  /* Movement from line to line   */
#define WFEDIT 0x04  /* Editing within a line        */
#define WFHARD 0x08  /* Better to a full display     */
#define WFMODE 0x10  /* Update mode line.            */
#define WFCOLR 0x20  /* Needs a color change         */

struct terminal {
  short t_mrow;             /* max number of rows allowable */
  short t_nrow;             /* current number of rows used  */
  short t_mcol;             /* max Number of columns.       */
  short t_ncol;             /* current Number of columns.   */
  short t_margin;           /* min margin for extended lines */
  short t_scrsiz;           /* size of scroll region "      */
  int t_pause;              /* # times thru update to pause */
  void (*t_open)(void);     /* Open terminal at the start.  */
  void (*t_close)(void);    /* Close terminal at end.       */
  void (*t_kopen)(void);    /* Open keyboard                */
  void (*t_kclose)(void);   /* close keyboard               */
  int (*t_getchar)(void);   /* Get character from keyboard. */
  int (*t_putchar)(int);    /* Put character to display.    */
  void (*t_flush)(void);    /* Flush output buffers.        */
  void (*t_move)(int, int); /* Move the cursor, origin 0.   */
  void (*t_eeol)(void);     /* Erase to end of line.        */
  void (*t_eeop)(void);     /* Erase to end of page.        */
  void (*t_beep)(void);     /* Beep.                        */
  void (*t_rev)(int);       /* set reverse video state      */
  int (*t_rez)(char *);     /* change screen resolution     */
#if COLOR
  int (*t_setfor)();  /* set forground color          */
  int (*t_setback)(); /* set background color         */
#endif
#if SCROLLCODE
  void (*t_scroll)(int, int, int); /* scroll a region of the screen */
#endif
};

#define TTopen (*term.t_open)
#define TTclose (*term.t_close)
#define TTkopen (*term.t_kopen)
#define TTmove (*term.t_move)
#define TTgetc (*term.t_getchar)
#define TTputc (*term.t_putchar)
#define TTrev (*term.t_rev)
#define TTrez (*term.t_rez)
#define TTeeol (*term.t_eeol)
#define TTeeop (*term.t_eeop)
#define TTbeep (*term.t_beep)
#define TTflush (*term.t_flush)
#if COLOR
#define TTforg (*term.t_setfor)
#define TTbacg (*term.t_setback)
#endif

struct buffer {
  struct buffer *b_bufp; /* Link to next struct buffer   */
  struct line *b_dotp;   /* Link to "." struct line structure   */
  struct line *b_markp;  /* The same as the above two,   */
  struct line *b_linep;  /* Link to the header struct line      */
  int b_doto;            /* Offset of "." in above struct line  */
  int b_marko;           /* but for the "mark"           */
  int b_mode;            /* editor mode of this buffer   */
  char b_active;         /* window activated flag        */
  char b_nwnd;           /* Count of windows on buffer   */
  char b_flag;           /* Flags                        */
  char b_fname[NFILEN];  /* File name                    */
  char b_bname[NBUFN];   /* Buffer name                  */
};

#define BFINVS 0x01  /* Internal invisible buffer */
#define BFCHG 0x01   /* Changed since last write */
#define BFTRUNC 0x04 /* buffer was truncated when read */

struct kill {
  struct kill *d_next;  /* link to the next chunk of killed text*/
  char d_chunk[KBLOCK]; /* chunk of deleted text */
};

#if ISRCH

#define CMDBUFLEN 256

#define IS_ABORT 0x07
#define IS_QUIT 0x1B

#endif // ISRCH
