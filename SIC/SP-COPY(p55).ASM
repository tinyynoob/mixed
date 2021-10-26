.
.  File; SP-COPY(p55).ASM
.  Date: (A) Creation - 2021/10/16     (B) Modified - 2021/10/19
.  Notes:
.  (1) This program is the same as the program in Figure 2.5 (pp. 55)
.  (2) This file is an example source program for SIC/XE Assembler
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
.  (B) Execute SIC/XE assembler
.
.0       1         2         3         4         5         6         7
.23456789012345678901234567890123456789012345678901234567890123456789012
.
COPY     START    1000              Copy file from INPUT to OUTPUT
FIRST    STL      RETADR            Save return address
         LDB     #LENGTH            Establish BASE register
         BASE     LENGTH
CLOOP   +JSUB     RDREC             Read input record
         LDA      LENGTH            Test for EOF (LENGTH = 0)
         COMP    #0
         JEQ      ENDFIL            Exit if EOF found/read
        +JSUB     WRREC             Write output record
         J        CLOOP             Loop
ENDFIL   LDA      EOF               Insert End-of-File marker
         STA      BUFFER
         LDA     #3                 Set LENGTH = 3
         STA      LENGTH
        +JSUB     WRREC             Write EOF to output file
         J       @RETADR            Return to caller
EOF      BYTE    C'EOF'
RETADR   RESW    1
LENGTH   RESW    1                  Length of record
BUFFER   RESB    4096               4096-BYTE Buffer area
.
.        SUBROUTINE TO READ RECORD INTO BUFFER
.
RDREC    CLEAR    X                 Clear loop counter
         CLEAR    A                 Clear A register to zero
         CLEAR    S                 Clear S register to zero
        +LDT     #4096
RLOOP    TD       INPUT             Test input device
         JEQ      RLOOP             Loop until device ready
         RD       INPUT             Read a character into register A
         COMPR    A,S               Test for End-of-Record (X'00')
         JEQ      EXIT              Exit loop if EOR encountered
         STCH     BUFFER,X          Store character in buffer
         TIXR     T                 Loop unless the max length
         JLT      RLOOP               has been reached
EXIT     STX      LENGTH            Save record length
         RSUB                       Return to caller
INPUT    BYTE     X'F1'             Code for the input device
MAXLEN   WORD     4096
.
.        SUBROUTINE TO WRITE RECORD FROM BUFFER
.
WRREC    CLEAR    X                 Clear loop counter
         LDT      LENGTH
WLOOP    TD       OUTPUT            Test output device
         JEQ      WLOOP             Loop until device ready
         LDCH     BUFFER,X          Get characteer from buffer
         WD       OUTPUT            Write a character
         TIXR     T                 Loop until all characters
         JLT      WLOOP               have been written
         RSUB                      Return to caller
OUTPUT   BYTE    X'05'             Code for the output device
         END     FIRST