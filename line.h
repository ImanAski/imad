#ifndef LINE_H_
#define LINE_H_

#include "utf8.h"

struct line {
  struct line *l_fp; /* link to the next line */
  struct line *l_bp; /* link to the previous line */
  int l_size;        /* allocated size */
  int l_used;        /* used size */
  char l_text[1];    /* bullshit */
};

#define lforw(lp) ((lp)->l_fp)
#define lback(lp) ((lp)->l_bp)
#define lgetc(lp, n) ((lp)->l_text[(n)] & 0xFF)
#define lputc(lp, n, c) ((lp)->l_text[(n)] = (c))
#define llength(lp) ((lp)->l_used)

extern void lfree(struct line *lp);
extern void lchange(int flag);
extern int insspace(int f, int n);
extern int linstr(char *instr);
extern int linsert(int n, int c);
extern int lowrite(int c);
extern int lover(char *ostr);
extern int lnewline(void);
extern int ldelete(long n, int kflag);
extern int ldelchar(long n, int kflag);
extern int lgetchar(unicode_t *);
extern char *getctext(void);
extern int putctext(char *iline);
extern int ldelnewline(void);
extern void kdelete(void);
extern int kinsert(int c);
extern int yank(int f, int n);
extern struct line *lalloc(int); /* Allocate a line. */
#endif
