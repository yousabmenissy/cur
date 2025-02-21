#include "cur.h"

void format(char *src, int fsize, char *dstbuff) {
  static struct line ln;
  ln.srcStart = src;
  ln.dst = dstbuff;
  SKIPBLANKS(ln.srcStart);

  // Process the file one line on a time
  while ((ln.srcEnd = strchr(ln.srcStart, '\n')) != NULL) {
  start:
    SKIPSPACES(ln.srcStart);
    if (*ln.srcStart == '\n') {
      AlignOff = 0;

      addc(&ln, '\n');
      ln.srcStart = ++ln.srcEnd;

      SKIPBLANKS(ln.srcEnd);
      ln.srcStart = ln.srcEnd;
      continue;
    } else if (*ln.srcStart == '#' || (strncmp(ln.srcStart, "//", 2)) == 0) {
      putSComment(&ln);
      continue;
    } else if ((strncmp(ln.srcStart, "/*", 2)) == 0) { // Multi-line Comment
      putMComment(&ln);
      continue;
    }

    processln(&ln);
    addc(&ln, '\n');
    ln.srcStart = ++ln.srcEnd;
  }

  SKIPBLANKS(ln.srcStart);
  if (ln.srcStart < src + fsize
      && (ln.srcEnd = strchr(ln.srcStart, '\0')) != NULL) {
    goto start;
  }

  memset(&ln, 0, sizeof(ln)); // Clean up
}
