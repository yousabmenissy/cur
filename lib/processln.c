#include "cur.h"

void processln(struct line *ln) {
  NextStart = ln->srcEnd + 1;
  char *tokenStart = ln->srcStart, *tokenEnd = ln->srcStart;
  while (ISSPACE((ln->srcEnd - 1))) ln->srcEnd--; // Skip trailing spaces

  // Find the first space or tab
  while (tokenEnd < ln->srcEnd && !ISSPACE(tokenEnd)) tokenEnd++;
  if (!ISSPACE(tokenEnd)) tokenEnd = ln->srcEnd; // No operands

  if (*tokenStart == '.') { // Directive or label?
    if (*(tokenEnd - 1) == ':' || hasc(tokenStart, tokenEnd, ':')) { // label
      if (ln->type == INSTRUCTION && (strncmp((ln->dst - 2), "\n\n", 2)) != 0)
        addc(ln, '\n');
      ln->type = LLABEL;
      putLabel(ln);
    } else { // directive
      ln->type = DIRECTIVE;
      putDirective(ln);
    }
  } else if (*(tokenEnd - 1) == ':' || hasc(tokenStart, tokenEnd, ':')) {
    if (*tokenStart >= '1' && *tokenStart <= '9') { // Numeric label
      if (ln->type == INSTRUCTION && (strncmp((ln->dst - 2), "\n\n", 2)) != 0)
        addc(ln, '\n');
      ln->type = LLABEL;
      putLabel(ln);
    } else { // Global label
      ln->type = GLABEL;
      putLabel(ln);
    }
  } else { // Instruction
    ln->type = INSTRUCTION;
    putInstruction(ln);
  }
  ln->srcStart = NextStart;
  return;
}