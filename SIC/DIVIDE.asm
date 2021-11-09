.  Notes:
.      The fixed format of each line:
.          COL. 1       - . (the entire line is comment)
.          COL. 1 ~ 8   - Label (optional)
.          COL. 9       - Blank
.          COL. 10 ~ 15 - Operation code mnemonic or assembler directive
.          COL. 16 ~ 17 - Blank
.          COL. 18 ~ 35 - Operand(s)
.          COL. 36 ~ 66 - Comment (optional)
.  Usage:
.  Notice that the XE version is applied.
.
.0       1         2         3         4         5         6         7
.23456789012345678901234567890123456789012345678901234567890123456789012
.
DIVIDE   START   1000              Program
.        .
         LDA     BETA
         RMO     A,T               (T)=BETA
         LDS     GAMMA
         DIVR    S,A               (A)=(A)/(S)
         STA     ALPHA
         MULR    S,A               (A)=(A)*(S)
         RMO     T,S               (S)=BETA
         SUBR    A,S               (S)=(S)-(A)
         STS     DELTA
         RSUB
ALPHA    RESW    1                 QUOTIENT
BETA     RESW    1                 DIVIDEND
DELTA    RESW    1                 REMAINDER
GAMMA    RESW    1                 DIVISOR
         END     DIVIDE
