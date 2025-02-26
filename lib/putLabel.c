#include "cur.h"

void putLabel(struct line *ln) {
  if (ln->type == LLABEL) addnc(ln, ' ', 4); // Indentation

  char *postColon = findc(ln->srcStart, ln->srcEnd, ':') + 1;
  int   len = (int)(postColon - ln->srcStart);
  addstr(ln, ln->srcStart, len);

  if (postColon == ln->srcEnd) return; // Nothing after colon

  if (!ISBLANK(postColon)) { // Non-blank character after colon
    NextStart = postColon;
    return;
  }

  addc(ln, ' ');
  SKIPSPACES(postColon);
  len = (int)(ln->srcEnd - postColon);
  addstr(ln, postColon, len);
}