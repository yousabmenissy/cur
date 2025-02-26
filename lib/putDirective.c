#include "cur.h"

void putDirective(struct line *ln) {
  char *tokenEnd = ln->srcStart;

  while (tokenEnd < ln->srcEnd && !ISSPACE(tokenEnd))
    tokenEnd++; // Find space or tab

  if (!ISSPACE(tokenEnd)) { // No operands
    int len = (int)(ln->srcEnd - ln->srcStart);
    addstr(ln, ln->srcStart, len);
    return;
  }

  int len = (int)(tokenEnd - ln->srcStart);
  addstr(ln, ln->srcStart, len);
  ln->srcStart = tokenEnd;
  SKIPSPACES(ln->srcStart);
  addc(ln, ' '); // Space after directive name

  len = (int)(ln->srcEnd - ln->srcStart);
  addstr(ln, ln->srcStart, len);
}