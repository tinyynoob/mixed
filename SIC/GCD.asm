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
GCD      START   1000              Program
         STL     RETADR            STORE RETURN ADDRESS
         LDA     ZERO              RESET VARIABLES
         LDX     ZERO
         STA     ALPHA
         STA     BETA
         STA     TEMP
         STCH    CHAR
READ     JSUB    RLOOP             
         LDA     ALPHA             IF NO DATA IN ALPHA, STORE TO ALPHA
         COMP    ZERO
         LDA     TEMP
         JEQ     SETALP
         STA     BETA              OTHERWISE, STORE TO BETA
         J       EUCLID
RLOOP    TD      INDEV             READ INPUT, AND TRANS FROM CHAR TO INT, AND STORE TO TEMP
         JEQ     RLOOP
         LDA     ZERO
         RD      INDEV             READ INPUT TO CHAR
         STCH    CHAR
         COMP    SPACE             IF EQUAL TO　ASCII CODE OF SPACE
         JEQ     CCR               IF THE NUMBER ENDS, EXIT RLOOP
         LDA     TEMP              TEMP=TEMP*10
         MUL     TEN
         STA     TEMP
         LDA     ZERO
         LDCH    CHAR
         SUB     FOUEIG            TRANS ASCII NUMBER SYMBOL TO NUMBER
         ADD     TEMP              TEMP=TEMP+CURRENT DIGIT
         STA     TEMP
         J       RLOOP
SETALP   STA     ALPHA             STORE (A) TO ALPHA
         LDA     ZERO              RESET TEMP
         STA     TEMP              
         J       READ
EUCLID   LDA     ALPHA             EUCLIDEAN ALGORITHM
         COMP    BETA              
         JSUB    CCSWAP            SWAP TO KEEP ALPHA>=BETA
         LDA     ALPHA             (A)=ALPHA/BETA
         DIV     BETA              
         MUL     BETA              (A)=(A)*BETA
         STA     TEMP              STORE TO TEMP
         LDA     ALPHA             COMPUTE REMAINDER BY ALPHA-TEMP
         SUB     TEMP
         COMP    ZERO              IF REMAINDER IS ZERO, EXIT EUCLID
         JEQ     CALENG
         STA     ALPHA             OTHERWISE, UPDATE ALPHA AND LOOP
         J       EUCLID
CALENG   LDA     BETA              CALCULATE LENGTH OF BETA
         LDX     ZERO
CLLOOP   DIV     TEN
         TIX     ZERO              (X)++, NOT USING COMP OF X
         COMP    ZERO              COMPARE (A) WITH 0
         JEQ     PREWRI            EXIT CALENG IF TRUE
         J       CLLOOP
PREWRI   STX     TEMP              PREPARE BEFORE WRITING
         LDX     ZERO
         LDA     ONE               ALPHA=1
PWLOOP   STA     ALPHA             ALPHA WILL BE USED AS DIVISOR
         TIX     TEMP
         JEQ     WLOOP
         MUL     TEN               (A)=(A)*10
         J       PWLOOP
WLOOP    TD      OUTDEV            OUTPUT THE ANSWER STORED IN BETA
         JEQ     WLOOP
         LDA     BETA              GET THE LEADER DIGIT OF BETA
         DIV     ALPHA
         STA     TEMP              STORE THE DIGIT TO TEMP
         ADD     FOUEIG            TRANS THE DIGIT TO ASCII SYMBOL
         WD      OUTDEV            OUTPUT
         LDA     TEMP
         MUL     ALPHA
         STA     TEMP
         LDA     BETA              REMOVE LEADER DIGIT OF BETA
         SUB     TEMP
         STA     BETA
         LDA     ALPHA             ALPHA=ALPHA/10
         DIV     TEN
         COMP    ZERO
         JEQ     EXIT              EXIT GCD
         STA     ALPHA
         J       WLOOP
CCSWAP   JLT     SWAP              IF ALPHA<BETA, SWAP
         RSUB                      OTHERWISE, DO NOTHING AND GO BACK
SWAP     STA     TEMP
         LDA     BETA
         STA     ALPHA     
         LDA     TEMP
         STA     BETA
         RSUB
CCR      RSUB                      CONDITIONAL RETURN
EXIT     LDL     RETADR            EXIT GCD
         RSUB
ZERO     WORD    0                 Constant: 0
ONE      WORD    1                 Constant: 1
TEN      WORD    10
SPACE    WORD    32
FOUEIG   WORD    48
ALPHA    RESW    1
BETA     RESW    1
TEMP     RESW    1
RETADR   RESW    1
INDEV    BYTE    X'F3'
OUTDEV   BYTE    X'05'
CHAR     RESB    1
         END     GCD
