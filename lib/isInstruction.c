#include "cur.h"

inline bool isInstruction(char *src) {
  char *lnEnd;
  char *lnStart = src;

  lnEnd = strchr(src, '\n');
  if (!lnEnd) lnEnd = strchr(src, '\0');
  SKIPSPACES(lnStart);

  char *tokenStart = lnStart;
  char  oldLnEnd = *lnEnd;
  *lnEnd = '\0';
  char *tokenEnd = strchr(tokenStart, ' ');
  if (!tokenEnd) tokenEnd = lnEnd;

  // clang-format off
  if (tokenStart && tokenEnd) { // Sanity check
    if (*tokenStart != '.' 
        && (*tokenStart < '1' || *tokenStart > '9')
        && (*(tokenEnd - 1) != ':' || !hasc(tokenStart, tokenEnd, ':'))) { // Is an instruction
      *lnEnd = oldLnEnd;
      return true;
    }
  }
  // clang-format on

  *lnEnd = oldLnEnd;
  return false;
}
