
// buffer.c

// Lookup for a buffer by name
extern struct buffer *bfind(char *bname, int cflag, int bflag);

// main.c
extern void edinit(char *bname);

// eval.c
extern void varinit(void);

// basic.c
extern int gotobol(int f, int n);
extern int gotoeol(int f, int n);
extern int gotobob(int f, int n);

// display.c
extern void vtinit(void);
extern void movecursor(int row, int col);
extern void mlwrite(const char *fmt, ...);
extern void mlputs(char *s);
extern int makelist(int iflag);
