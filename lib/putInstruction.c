#include "cur.h"

void putInstruction(struct line *ln) {
  addnc(ln, ' ', 4); // Indentation

  int   len = 0;
  char *tokenEnd = ln->srcStart;
  while (tokenEnd < ln->srcEnd && !ISSPACE(tokenEnd)) tokenEnd++;

  if (!ISSPACE(tokenEnd)) { // No operands
    len = (int)(ln->srcEnd - ln->srcStart);
    addstr(ln, ln->srcStart, len);
    return;
  }

  len = (int)(tokenEnd - ln->srcStart);
  addstr(ln, ln->srcStart, len);
  SKIPSPACES(tokenEnd);

  if (!AlignOff) { // THIS IS NASTY!
    char *end = NextStart;
    SKIPSPACES(end);

    if (*end == '\n' || *end == '\0') {
      AlignOff = getAlignment(ln->srcStart, end);
    } else {
      while ((end = strchr(end, '\n')) != NULL) {
        end++;
        SKIPSPACES(end);
        if (*end == '\n' || *end == '\0') {
          AlignOff = getAlignment(ln->srcStart, end);
          break;
        }
      }
      if (AlignOff == 0) {
        end = strchr(ln->srcStart, '\0');
        AlignOff = getAlignment(ln->srcStart, end);
      }
    }
  }

  addnc(ln, ' ', AlignOff - len);
  char *comma;
  while ((comma = findc(tokenEnd, ln->srcEnd, ',')) != NULL) { // Space after the comma ', '
    len = (int)((++comma) - tokenEnd);
    addstr(ln, tokenEnd, len);
    addc(ln, ' ');
    SKIPSPACES(comma);
    tokenEnd = comma;
  }

  len = (int)(ln->srcEnd - tokenEnd);
  addstr(ln, tokenEnd, len);
}