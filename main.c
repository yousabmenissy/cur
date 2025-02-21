#include "cur.h"

long Count = 0;
int  AlignOff = 0;
bool WFlag = false;
char SrcBuff[BUFF_SIZE];
char DstBuff[BUFF_SIZE];

void usage() {
  fputs("Usage: cur [-w] file...\n"
        "Format assembly file. By default the formatted content is written to "
        "standard output.\n\n"
        "Options:\n"
        "-w    format file in place\n"
        "-h    show this message\n",
        stderr);
  exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
  if (argc == 1) usage();

  int opt;
  while ((opt = getopt(argc, argv, "wh")) != -1) {
    switch (opt) {
    case 'w':
      WFlag = true;
      break;
    case 'h':
      usage();
    default:
      usage();
    }
  }

  for (int i = optind; i < argc; i++) {
    FILE *fd = fopen(argv[i], WFlag ? "r+" : "r");
    if (fd == NULL) {
      fprintf(stderr, "cur: could not open file '%s'\n", argv[i]);
      continue;
    }

    fseek(fd, 0, SEEK_END);
    long fsize = ftell(fd);
    if (fsize > BUFF_SIZE) { // Such a big boy!
      fprintf(stderr, "cur: '%s' is too big to format\n", argv[i]);
      continue;
    }
    rewind(fd);
    int nread = fread(SrcBuff, 1, fsize, fd);
    if (nread != fsize) {
      fprintf(stderr, "cur: could not read file '%s'\n", argv[i]);
      continue;
    }

    format(SrcBuff, fsize, DstBuff); // Show time!
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

  return 0;
}
