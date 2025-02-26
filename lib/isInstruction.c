#include "cur.h"

inline bool isInstruction(char *src) {
  char *lnEnd;
  char *lnStart = src;

  lnEnd = strchr(src, '\n');
  if (!lnEnd) lnEnd = strchr(src, '\0');
  SKIPSPACES(lnStart);

  char *tokenStart = lnStart;
  char *tokenEnd = findc(tokenStart, lnEnd, ' ');
  if (!tokenEnd) tokenEnd = lnEnd;

  // clang-format off
  if (tokenStart && tokenEnd) { // Sanity check
    if (*tokenStart != '.' 
        && (*tokenStart < '1' || *tokenStart > '9')
        && (*(tokenEnd - 1) != ':' || !hasc(tokenStart, tokenEnd, ':'))) { // Is an instruction
      return true;
    }
  }
  return false;
}
