#include "efunc.h"
#include "evar.h"

#define MAXVARS 255

static struct user_variable uv[MAXVARS + 1];

void varinit(void) {
  int i;
  for (i = 0; i < MAXVARS; i++) {
    uv[i].u_name[0] = 0;
  }
}
