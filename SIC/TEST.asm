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
TEST     START   1000              Program
         LDA     ZERO
         LDCH    AAA
         STA     CHAR              
RLOOP    TD      INDEV             READ CHAR DATA AND TRANS TO INT
         JEQ     RLOOP
         LDA     ZERO
         RD      INDEV
         SUB     FOUEIG
         STCH    CHAR
         LDA     ONE
         ADD     ONE
         STA     ALPHA
         LDA     ZERO
         LDCH    CHAR
         MUL     ALPHA
         ADD     FOUEIG
         STCH    CHAR
WLOOP    TD      OUTDEV            OUTPUT THE ANSWER STORED IN BETA
         JEQ     WLOOP
         LDA     ZERO
         LDCH    CHAR
         WD      OUTDEV
         RSUB                      CONDITIONAL RETURN
ZERO     WORD    0                 Constant: 0
ONE      WORD    1                 Constant: 1
TEN      WORD    10
SPACE    WORD    32
FOUEIG   WORD    48
ALPHA    RESW    1
BETA     RESW    1
TEMP     RESW    1
INDEV    BYTE    X'F3'
OUTDEV   BYTE    X'05'
AAA      BYTE    C'A'
CHAR     RESB    1
         END     TEST
