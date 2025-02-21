#include "cur.h"

inline void addstr(struct line *ln, char *str, int len) {
  strncpy(ln->dst, str, len);
  ln->dst += len;
  Count += len;
}

inline void addc(struct line *ln, char chr) {
  *ln->dst = chr;
  ln->dst++;
  Count++;
}

inline void addnc(struct line *ln, char chr, int count) {
  memset(ln->dst, ' ', count);
  ln->dst += count;
  Count += count;
}

inline bool hasc(char *start, char *end, char chr) {
  char *token = start;
  while (token < end && *token != chr) token++;
  if (*token == chr) return true;
  return false;
}