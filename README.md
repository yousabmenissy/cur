# cur
An opinionated autoformatter for the GNU assembler, `as`.

cur is the result of my long-brewing frustration with the complete lack of open source GAS autoformatters.

## Table of Contents
- [Installation](#installation)
  - [Unix/Linux](#unixlinux)
  - [Windows](#windows)
- [Usage](#usage)
- [Formatting Rules](#formatting-rules)
  - [Blank characters](#blank-characters)
  - [Directives](#directives)
  - [Global labels](#global-labels)
  - [Local labels](#local-labels)
  - [Signle line comments](#signle-line-comments)
  - [Multi line comments](#multi-line-comments)
  - [Instructions](#instructions)
- [Example](#example)
    - [Before](#before)
    - [After](#after)
- [License](#license)


## Installation

### Unix/Linux
```sh
git clone https://github.com/yousabmenissy/cur.git
cd cur
sudo make install
```

### Windows
If gcc is not installed, install it first via MinGW or TDM-GCC. you can check with:
```sh
gcc --version
```
Press Win + S and type cmd, Right-click Command Prompt and select Run as administrator.

run these commands:
```sh
git clone https://github.com/yousabmenissy/cur.git
cd cur
gcc main.c lib/*.c -o cur.exe -Ilib -O3
if not exist "C:\Program Files\cur" mkdir "C:\Program Files\cur"
move cur.exe "C:\Program Files\cur"
powershell -Command "[System.Environment]::SetEnvironmentVariable('Path', $env:Path + ';C:\Program Files\cur', 'Machine')"
```
## Usage
To format all .s files in the current directory:
```sh
cur *.s
```

or to include all .s files in subdirectories:
```sh
cur **/*.s
```

By default cur will use standard output. To format files in place use the -w flag:
```sh
cur *.s -w
```

## Formatting rules

### Blank characters
The characters '\n', '\t' and '\s' are treated as blanks.
- blanks at the start of the line are ignored.
- tabs and spaces before the end of the line are ignored.
- multible lines of blank characters are all replaced with a single '\n' character.
- cur will make sure the last character in the file is a new line, '\n'.

### Directives
Expressions that start with '.', does not end with ':' are treated as directives.
- they are always at indentaion level 0.
- their operands are aligned by 1 space.

### Global labels
Expressions that does not start with '.', does not compose of a signle digit, and end with ':' are treated as global labels.
- they are always at indentaion level 0.
- cur will allow either a space, '\s', or a new line, '\n', to follow the ':'.
- if ':' is not followed by either a space or a new line, cur will inject a new line after the colon and treats the rest as a different line
- tabs are not allowed after the ':'

### Local labels
Expressions that start with '.', or compose of a signle digit, and end with ':' are treated as local labels.
- they are always at indentaion level 1.
- they are always followed by a new line.

### Signle line comments
lines that start with '#' or '//' are treated as single line comments.
- they follow the indentaion of the previous line
- if '//' is used, cur will replace with '#' followed by 1 space.
- blank lines at the start of the comment are ignored.
- comments that come after other expressions are not formated

### Multi line comments
lines that start with /* are treated as multi-line comment untill */ or end of the file is reached.
- blank lines are not allowed.
- the /* and */ are set on their own line with no indentaion.
- everything inside the comment is always at indentation level 1.

### Instructions 
lines that is not recognized as directives, labels, or comments are treated as instructions.
- they are always at indentaion level 1.
- their operands are aligned with 2 spaces after the longest instruction in the block.
- each block has it's own alignment.
- a block start at the first instruction and end at the next blank line
- instruction without operands are not cosidered when finding the alignment
- a space is injected after each ',' in the operands list.
- macro calls are treated exactly like instructions.

## Example

#### Before
```as
 .section .text


        .global basename
 .type basename, @function
    basename: # basename(path)
    movq %rdi, %rsi
    xor %rax,    %rax

//      find the '/'
    .LPBN0:lodsb
    cmpb $'/',%al
    cmove    %rsi,%rdi


    cmpq $0,        %rax
    jne .LPBN0
    movq      %rdi,%rax

ret
/*## Altered Registers ##
- rdi
 - rsi*/
```
#### After
```as
.section .text

.global basename
.type basename, @function
basename: # basename(path)
    movq  %rdi, %rsi
    xor   %rax, %rax

    # find the '/'
    .LPBN0:
    lodsb
    cmpb   $'/', %al
    cmove  %rsi, %rdi

    cmpq  $0, %rax
    jne   .LPBN0
    movq  %rdi, %rax

    ret
/*
    ## Altered Registers ##
    - rdi
    - rsi
*/

```
## License
Copyright (c) 2025-present Yousab Menissy

Licensed under MIT License. See the [LICENSE](LICENSE) file for details.