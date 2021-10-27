.
.  File; SP-HELLO.ASM
.  Date: (A) Creation - 2021/10/04     (B) Modified - 2021/10/05
.  Notes:
.  (1) This program is an example program of course System Programming
.  (2) This file is intended to be an example program for SIC Assembler
.  (3) The fixed format of each line:
.          COL. 1       - . (the entire line is comment)
.          COL. 1 ~ 8   - Label (optional)
.          COL. 9       - Blank
.          COL. 10 ~ 15 - Operation code mnemonic or assembler directive
.          COL. 16 ~ 17 - Blank
.          COL. 18 ~ 35 - Operand(s)
.          COL. 36 ~ 66 - Comment (optional)
.  Usage:
.  (A) Rename this file to SRCFILE
.  (B) Execute SIC assembler
.
.0       1         2         3         4         5         6         7
.23456789012345678901234567890123456789012345678901234567890123456789012
.
HELLO    START   1000              Hello, World! Program
PSTART   LDX     ZERO              Initialize index register
PUTCH    TD      OUTDEV            Output Device ready?
         JEQ     PUTCH
         LDCH    MSG,X             Load via index the next char
         WD      OUTDEV            Output/Display the character
         TIX     MSIZE             End of Message reached?
         JLT     PUTCH             Loop
         RSUB                      Program Return/Exit
.
ZERO     WORD    0                 Constant: 0
MSIZE    WORD    15                Size of the message
MSG      BYTE    C'Hello, world!'
         BYTE    X'0D0A'
OUTDEV   BYTE    X'05'
.
         END     PSTART
