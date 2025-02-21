#include "cur.h"

void processln(struct line *ln) {
  char *lnStart = ln->srcStart;
  char *lnEnd = ln->srcEnd;
  char  oldlnEnd = *lnEnd;
  while (*(lnEnd - 1) == ' ' || *(lnEnd - 1) == '\t')
    lnEnd--; // Skip trailing spaces
  *lnEnd = '\0';

  char *tokenStart = lnStart;
  char *tokenEnd = lnStart;

  // Find space or tab
  while (tokenEnd < lnEnd && (*tokenEnd != ' ' && *tokenEnd != '\t'))
    tokenEnd++;
  if (*tokenEnd != ' ' && *tokenEnd != '\t') tokenEnd = lnEnd;

  if (tokenStart && tokenEnd) { // Sanity check
    if (*tokenStart == '.') {
      // Directive or label?
      if (*(tokenEnd - 1) == ':' || hasc(tokenStart, tokenEnd, ':')) { // label
        ln->indentation = 1;
        ln->type = LLABEL;
      } else { // directive
        ln->indentation = 0;
        ln->type = DIRECTIVE;
      }
    } else if (*(tokenEnd - 1) == ':' || hasc(tokenStart, tokenEnd, ':')) {
      // Numeric label or global label?
      if (*tokenStart >= '1' && *tokenStart <= '9') { // Numeric label
        ln->indentation = 1;
        ln->type = LLABEL;
      } else { // Global label
        ln->indentation = 0;
        ln->type = GLABEL;
      }
    } else { // Instruction
      ln->indentation = 1;
      ln->type = INSTRUCTION;
    }
  }
  int len;
  for (int i = 0; i < ln->indentation; i++) {
    addnc(ln, ' ', 4);
  }

  // Labels can either have a space or a new line after the colon
  if (ln->type == GLABEL || ln->type == LLABEL) {
    char *postColon = strchr(tokenStart, ':') + 1;
    if (postColon != lnEnd && (*postColon != ' ' && *postColon != '\n')) {
      len = (int)(postColon - tokenStart);
      addstr(ln, tokenStart, len);
      SKIPSPACES(postColon);
      *ln->srcEnd = oldlnEnd;
      ln->srcEnd = --postColon;
      return;
    }
  }

  if (tokenEnd == lnEnd) { // No operands
    len = (int)(lnEnd - lnStart);
    addstr(ln, lnStart, len);
    return;
  }

  len = (int)(tokenEnd - tokenStart);
  addstr(ln, tokenStart, len);
  tokenStart = tokenEnd;
  SKIPSPACES(tokenStart);

  if (ln->type == INSTRUCTION && AlignOff == 0) { // New block
    char *start = lnStart;
    char *end = lnEnd + 1;
    SKIPSPACES(end);

    if (*end == '\n' || *end == '\0') {
      *lnEnd = oldlnEnd;
      AlignOff = getAlignment(start, end);
      *lnEnd = '\0';
    } else {
      while ((end = strchr(end, '\n')) != NULL) {
        end++;
        SKIPSPACES(end);
        if (*end == '\n' || *end == '\0') {
          *lnEnd = oldlnEnd;
          AlignOff = getAlignment(start, end);
          *lnEnd = '\0';
          break;
        }
      }
      if (AlignOff == 0) {
        *lnEnd = oldlnEnd;
        end = strchr(start, '\0');
        AlignOff = getAlignment(start, end);
        *lnEnd = '\0';
      }
    }
  }

  int alignment = (ln->type == INSTRUCTION) ? AlignOff - len : 1;
  addnc(ln, ' ', alignment);

  if (ln->type == INSTRUCTION) { // Add a space after the comma ', '
    char *comma;
    while (comma = strchr(tokenStart, ',')) {
      len = (int)((++comma) - tokenStart);
      addstr(ln, tokenStart, len);
      addc(ln, ' ');
      SKIPSPACES(comma);
      tokenStart = comma;
    }
  }

  len = (int)(lnEnd - tokenStart);
  addstr(ln, tokenStart, len);
}
