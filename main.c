#include "cur.h"

char  SrcBuff[BUFF_SIZE];
char  DstBuff[BUFF_SIZE];
char *NextStart;
long  Count = 0;
int   AlignOff = 0;
bool  WFlag = 0, VFlag = 0;

static inline void usage() {
  fputs("Usage: cur [options] file...\n"
        "Format assembly file. By default the formatted content is written to "
        "standard output.\n\n"
        "Options:\n"
        "-w    format file in place\n"
        "-v    print porcessed files names\n"
        "-h    show this message\n",
        stderr);
  exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
  if (argc == 1) usage();

  int opt;
  while ((opt = getopt(argc, argv, "wvhr:")) != -1) {
    switch (opt) {
    case 'w':
      WFlag = true;
      break;
    case 'v':
      VFlag = true;
      break;
    case 'h':
      usage();
    default:
      usage();
    }
  }

  for (int i = optind; i < argc; i++) {
    fformat(argv[i]);
  }

  return 0;
}
