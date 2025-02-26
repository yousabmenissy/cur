#include "cur.h"

inline void addstr(struct line *ln, char *str, int len) {
  memcpy(ln->dst, str, len);
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
  if (!start || !end || end < start) return NULL;
  return (memchr(start, chr, end - start) != NULL);
}

inline char *findc(char *start, char *end, char chr){
  if (!start || !end || end < start) return NULL;
  return memchr(start, chr, end - start);
}