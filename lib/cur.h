#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define SKIPBLANKS(chrptr)                                                     \
  while (*chrptr == '\n' || *chrptr == ' ' || *chrptr == '\t') chrptr++;

#define SKIPSPACES(chrptr)                                                     \
  while (*chrptr == ' ' || *chrptr == '\t') chrptr++;

#define DIRECTIVE   1
#define GLABEL      2
#define LLABEL      3
#define INSTRUCTION 4

// 32MBs. Enough for all handwritten assembly files and most disassembled files
#define BUFF_SIZE (32 * 1024 * 1024)

// Global variables are capitalized
extern long Count;
extern int  AlignOff;
extern char SrcBuff[BUFF_SIZE];
extern char DstBuff[BUFF_SIZE];

struct line {
  char *srcStart;
  char *srcEnd;
  char *dst;
  char  indentation;
  char  type;
  char  alignment;
};

void format(char *src, int fsize, char *dstbuff);
void processln(struct line *ln);
int  getAlignment(char *start, char *end);
void putSComment(struct line *ln);
void putMComment(struct line *ln);
bool isInstruction(char *src);
void addc(struct line *ln, char chr);
void addstr(struct line *ln, char *str, int len);
void addnc(struct line *ln, char chr, int count);
bool hasc(char *start, char *end, char chr);