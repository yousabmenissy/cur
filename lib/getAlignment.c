#include "cur.h"

inline int getAlignment(char *start, char *end) {
  int   alignment = 0;
  char *lnStart = start;
  char *lnEnd;

  while ((lnEnd = findc(lnStart, end, '\n')) != NULL) {
    SKIPBLANKS(lnStart);

    // Skip comments
    if (*lnStart == '#' || strncmp(lnStart, "//", 2) == 0) {
      lnStart = lnEnd + 1;
      continue;
    } else if ((strncmp(lnStart, "/*", 2)) == 0) { // Multi-line comment
      char *endComment = strstr(lnStart, "*/");
      if (!endComment) endComment = strchr(lnStart, '\0'); // End of buffer
      lnStart = endComment + 2;
      continue;
    }

    if (isInstruction(lnStart)) {
      char *tokenStart = lnStart;
      char *tokenEnd = lnStart;
      while (tokenEnd < lnEnd && !ISSPACE(tokenEnd))
        tokenEnd++;

      // Skip instructions without operands
      if (!ISSPACE(tokenEnd)) {
        lnStart = ++lnEnd;
        continue;
      }

      if (tokenStart && tokenEnd) { // Sanity check
        int tokenLength = tokenEnd - tokenStart;
        if (tokenLength > alignment) alignment = tokenLength;
        lnStart = ++lnEnd;
        continue;
      }
    }
    
    lnStart = ++lnEnd;
  }

  return alignment + 2;
}