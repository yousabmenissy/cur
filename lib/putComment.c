#include "cur.h"

inline void putSComment(struct line *ln) {
  if (ln->type == INSTRUCTION || ln->type == LLABEL) addnc(ln, ' ', 4);

  addstr(ln, "# ", 2);
  ln->srcStart += 2;
  SKIPSPACES(ln->srcStart);

  int len = (int)(ln->srcEnd - ln->srcStart);
  addstr(ln, ln->srcStart, len);
  addc(ln, '\n');
  ln->srcStart = ++ln->srcEnd;
}

inline void putMComment(struct line *ln) {
  char *endComment = strstr(ln->srcStart, "*/");
  if (!endComment) endComment = strchr(ln->srcStart, '\0'); // End of buffer

  if (ISBLANK((endComment - 1))) memset(endComment, ' ', 2);
  while (ISBLANK((endComment - 1))) endComment--; // Skip trailing blank lines

  addstr(ln, "/*", 2);
  ln->srcStart += 2;
  addc(ln, '\n');
  SKIPBLANKS(ln->srcStart); // Skip starting blank lines

  while (ln->srcStart < endComment) { // Indent each line
    addnc(ln, ' ', 4);

    ln->srcEnd = strchr(ln->srcStart, '\n');
    if (!ln->srcEnd)
      ln->srcEnd = endComment;
    else
      ln->srcEnd++;
    if (ln->srcEnd > endComment) ln->srcEnd = endComment;

    int len = (int)(ln->srcEnd - ln->srcStart);
    addstr(ln, ln->srcStart, len);
    ln->srcStart += len;
    SKIPSPACES(ln->srcStart);
  }

  addc(ln, '\n');
  addstr(ln, "*/", 2);
  ln->srcStart = endComment + 2;
  
  SKIPSPACES(ln->srcStart);
  addc(ln, '\n');
}