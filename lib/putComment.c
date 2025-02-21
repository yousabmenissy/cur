#include "cur.h"

inline void putSComment(struct line *ln) {
  for (int i = 0; i < ln->indentation; i++) {
    addnc(ln, ' ', 4);
  }

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
  if (!endComment) endComment = strstr(ln->srcStart, "\0");

  addstr(ln, "/*", 2);
  ln->srcStart += 2;
  addc(ln, '\n');

  while (ln->srcStart < endComment) { // Indent each line
    SKIPBLANKS(ln->srcStart);
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
  SKIPBLANKS(ln->srcStart);

  if (*(ln->srcEnd - 1) != '\n') addc(ln, '\n');
  addstr(ln, "*/", 2);
  ln->srcStart = endComment + 2;
  SKIPSPACES(ln->srcStart);
  if (*ln->srcStart == '\n') {
    addc(ln, '\n');
    ln->srcStart++;
  } else
    addc(ln, '\n');
}