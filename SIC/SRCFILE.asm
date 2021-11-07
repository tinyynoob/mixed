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
         LDA     ZERO              RESET ALL
	 LDX	 ZERO
         STA     ALPHA
         STA     BETA
         STA     TEMP
         STCH    DATA
READ	 JSUB    RLOOP		   
	 LDA     ALPHA		   IF NO DATA IN ALPHA, STORE TO ALPHA
	 COMP    ZERO
	 LDA 	 TEMP
	 JEQ	 SETALP
	 STA	 BETA		   OTHERWISE, STORE TO BETA
	 J	 EUCLID
RLOOP    TD      INDEV		   READ CHAR DATA AND TRANS TO INT
         JEQ     RLOOP
	 LDA	 ZERO
         RD      INDEV
	 STCH    CHAR
         COMP    SPACE
         JEQ     CCR		   IF THE NUMBER ENDS
	 LDA     TEMP		   TEMP=TEMP*10
	 MUL     TEN
	 STA     TEMP
	 LDA     ZERO
	 LDCH	 CHAR
	 SUB	 FOUEIG		   TRANS ASCII NUMBER SYMBOL TO NUMBER
	 ADD	 TEMP		   TEMP=TEMP+CURRENT DIGIT
         J       RLOOP
SETALP	 STA 	 ALPHA
	 J	 READ
EUCLID   LDA     ALPHA             EUCLIDEAN ALGORITHM
         COMP	 BETA              
         JSUB    CCSWAP            SWAP TO KEEP ALPHA>=BETA
         LDA     ALPHA
         DIV     BETA              (A)=ALPHA/BETA
         MUL     BETA              (A)=(A)*BETA
         STA     TEMP  		   COMPUTE REMAINDER BY ALPHA-(A)
         LDA     ALPHA
         SUB     TEMP
         COMP    ZERO      	   IF REMAINDER IS ZERO, EXIT EUCLID
         JEQ     CALENG
         STA     ALPHA		   OTHERWISE, UPDATE ALPHA AND LOOP
         J       EUCLID
CALENG	 LDA     BETA		   CALCULATE LENGTH
	 LDX	 ZERO
CLLOOP	 DIV	 TEN
	 TIX	 ZERO		   (X)++, NOT USING COMP OF X
	 COMP	 ZERO		   COMPARE (A) WITH 0
	 JEQ	 WLOOP		   EXIT CALENG IF TRUE
	 J	 CLLOOP
PREWRI	 STX	 TEMP		   PREPARE BEFORE WRITING
	 LDX	 ZERO
	 LDA	 ONE		   ALPHA=1
	 STA	 ALPHA		   ALPHA WILL BE USED AS DIVISOR
PWLOOP	 TIX	 TEMP
	 JEQ	 WLOOP
	 MUL	 TEN		   (A)=(A)*10
	 J	 PWLOOP
WLOOP    TD      OUTDEV		   OUTPUT THE ANSWER STORED IN BETA
         JEQ     WLOOP
	 LDA     BETA		   GET THE LEADER DIGIT OF BETA
	 DIV 	 ALPHA
	 STA	 TEMP
	 ADD	 FOREIG		   TRANS NUMBER TO ASCII SYMBOL
	 WD	 OUTDEV
	 LDA	 BETA		   REMOVE LEADER DIGIT OF BETA
	 SUB 	 TEMP
	 STA	 BETA
	 LDA	 ALPHA		   ALPHA=ALPHA/10
	 DIV	 TEN
	 COMP	 ZERO
	 JEQ	 CCR	 	   EXIT GCD
	 STA	 ALPHA
	 J 	 WLOOP
CCSWAP	 JLT	 SWAP		   IF ALPHA<BETA, SWAP
	 RSUB			   OTHERWISE, GO BACK
SWAP     STA     TEMP
         LDA     BETA
         STA     ALPHA     
         LDA     TEMP
         STA     BETA
         RSUB
CCR 	 RSUB			   CONDITIONAL RETURN

ZERO     WORD    0                 Constant: 0
ONE      WORD    1                 Constant: 1
TEN      WORD	 10
SPACE    WORD	 32
FOUEIG   WORD    48
ALPHA    RESW    1
BETA     RESW    1
TEMP     RESW    1
INDEV    BYTE    X'03'
OUTDEV   BYTE    X'05'
CHAR     RESB    1
         END     GCD
