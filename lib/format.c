#include "cur.h"

// Format the source code
static inline void format(char *src, int fsize, char *dstbuff) {
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
  }

  SKIPBLANKS(ln.srcStart);
  if (ln.srcStart < src + fsize
      && (ln.srcEnd = strchr(ln.srcStart, '\0')) != NULL) {
    goto start;
  }

  memset(&ln, 0, sizeof(ln)); // Clean up
}

// Process and format a file
void fformat(char *path) {
  FILE *fd = fopen(path, WFlag ? "r+" : "r");
  if (fd == NULL) {
    fprintf(stderr, "cur: could not open file '%s'\n", path);
    return;
  }

  fseek(fd, 0, SEEK_END);
  long fsize = ftell(fd);
  if (fsize > BUFF_SIZE) {
    fprintf(stderr, "cur: '%s' is too big to format\n", path);
    return;
  }

  rewind(fd);
  int nread = fread(SrcBuff, 1, fsize, fd);
  if (nread != fsize) {
    fprintf(stderr, "cur: could not read file '%s'\n", path);
    return;
  }

  format(SrcBuff, fsize, DstBuff); // Show time!
  if (VFlag) printf("cur: formatted '%s'\n", path);

  if (WFlag) {
    fseek(fd, 0, SEEK_SET);
    ftruncate(fileno(fd), 0);
    fwrite(DstBuff, 1, Count, fd);
  } else {
    fwrite(DstBuff, 1, Count, stdout);
  }

  // Clean up
  memset(SrcBuff, 0, fsize);
  memset(DstBuff, 0, Count);
  Count = 0;
  AlignOff = 0;
  fclose(fd);
}