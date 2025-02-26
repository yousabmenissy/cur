#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define ISBLANK(chrptr) (*chrptr == ' ' || *chrptr == '\t' || *chrptr == '\n')
#define ISSPACE(chrptr) (*chrptr == ' ' || *chrptr == '\t')

#define SKIPBLANKS(chrptr)                                                     \
  while (ISBLANK(chrptr)) chrptr++;

#define SKIPSPACES(chrptr)                                                     \
  while (ISSPACE(chrptr)) chrptr++;

#define DIRECTIVE   1
#define GLABEL      2
#define LLABEL      3
#define INSTRUCTION 4

// 32MBs. Enough for all handwritten assembly files and most disassembled files
#define BUFF_SIZE (32 * 1024 * 1024)

// Global variables are capitalized
extern char  SrcBuff[BUFF_SIZE];
extern char  DstBuff[BUFF_SIZE];
extern char *NextStart;
extern long  Count;
extern int   AlignOff;
extern bool  WFlag, VFlag;

struct line {
  char *srcStart;
  char *srcEnd;
  char *dst;
  char  type;
  char  alignment;
};

void  processln(struct line *ln);
int   getAlignment(char *start, char *end);
void  putSComment(struct line *ln);
void  putMComment(struct line *ln);
bool  isInstruction(char *src);
void  addc(struct line *ln, char chr);
void  addstr(struct line *ln, char *str, int len);
void  addnc(struct line *ln, char chr, int count);
bool  hasc(char *start, char *end, char chr);
char *findc(char *start, char *end, char chr);
void  fformat(char *path);
void  rformat(char *path);
void  putLabel(struct line *ln);
void  putDirective(struct line *ln);
void  putInstruction(struct line *ln);