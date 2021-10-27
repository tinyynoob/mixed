@ECHO OFF
REM
IF NOT '%1' == ''     GOTO 000-ARGS
ECHO *
ECHO * %0 needs arguments!
ECHO * Please enter " %0 ? " for usage help.
ECHO * 
GOTO 999-EXIT
REM *---------------------------------------------*
:000-ARGS
REM
IF /I '%1' == '?'     GOTO 080-USAGE
IF /I '%1' == '-?'    GOTO 080-USAGE
IF /I '%1' == '/?'    GOTO 080-USAGE
IF /I '%1' == '-H'    GOTO 080-USAGE
IF /I '%1' == '/H'    GOTO 080-USAGE
IF /I '%1' == '-HELP' GOTO 080-USAGE
IF /I '%1' == '/HELP' GOTO 080-USAGE
IF /I '%1' == '-I'    GOTO 086-INFORMATION
IF /I '%1' == '/I'    GOTO 086-INFORMATION
REM
REM *---------------------------------------------*
:000-RESET
REM --- // Reset
SET ___ARG1=
SET ___V=
SET ___U=
SET ___K=
SET ___P=
SET ___T=
SET ___AFN1=

REM
REM --- // Processin Flag and Switche settings
:010-ALOOP
IF    '%1' == ''      GOTO 100-SETF
SET ___ARG1=%1
SET ___P=%___ARG1:~0,1%
SET ___T=%___ARG1:~1%
REM
IF NOT '%___P%' == '-'  GOTO 100-SETF
IF /I  '%___T%' == 'V'  SET ___V=Y
IF /I  '%___T%' == 'U'  SET ___U=Y
IF /I  '%___T%' == 'K'  SET ___K=Y
SHIFT /1
GOTO 010-ALOOP
REM
REM *---------------------------------------------*
:100-SETF
REM // Checking/Preparing source program file
IF  EXIST %1  GOTO 120-FILES
ECHO   //
ECHO   // ERROR: Source file [%___ARG1%] 
ECHO   //        appears non-existent.
GOTO 990-ERRS
REM
:120-FILES
SET ___AFN1=%~n1
SET ___AFN2=%~n2
SET ___AFN3=%~n3
IF   '%___AFN2%' == ''  SET ___AFN2=%___AFN1%
IF   '%___AFN3%' == ''  SET ___AFN3=%___AFN1%
ECHO * ___AFN1=%___AFN1%
ECHO * ___AFN2=%___AFN2%
ECHO * ___AFN3=%___AFN3%
REM
COPY /V /Y %1 SRCFILE > NULL
REM *---------------------------------------------*
:200-MAKF
REM
IF  /I NOT '%___V%' == 'Y'  GOTO 210-ASSEMB
ECHO *
ECHO * (%0) Status: Ready to assemble ...
ECHO *
:210-ASSEMB
SICASM-E
IF  /I NOT '%___V%' == 'Y'  GOTO 290-CONTINUE
ECHO *
ECHO * (%0) Status: Assembly process completed.
ECHO *
REM
:290-CONTINUE
REM *---------------------------------------------*
:300-COPYF
IF  /I NOT '%___V%' == 'Y'  GOTO 310-DOCOPY
ECHO *
ECHO * (%0) Status: Ready to copy files ...
ECHO *
:310-DOCOPY
IF EXIST OBJFILE  COPY /V /Y OBJFILE %___AFN2%.OBJ
IF EXIST LISFILE  COPY /V /Y LISFILE %___AFN3%.LST
IF EXIST INTFILE  COPY /V /Y OBJFILE %___AFN1%.INT
REM
REM *---------------------------------------------*
:700-CLEANUP
IF  /I NOT '%___V%' == 'Y'  GOTO 730-UMODE
ECHO *
ECHO * (%0) Status: Entering clean up phase...
ECHO *
REM
REM --- // UMODE takes the priority
:730-UMODE
IF  /I NOT '%___V%' == 'Y'  GOTO 740-GETUI
ECHO *
ECHO * (%0) Status: User interaction enabled?
ECHO *
REM
:740-GETUI
IF  /I NOT '%___U%' == 'Y'  GOTO 760-ACLEAN
IF  /I NOT '%___V%' == 'Y'  GOTO 750-UPROMPT
ECHO *
ECHO * (%0) Status: User interaction enabled...
ECHO *
REM
:750-UPROMPT
ECHO *
ECHO * (%0) The following files will be deleted:
ECHO *        SRCFILE
ECHO *        OBJFILE
ECHO *        LISFILE
ECHO *        INTFILE
ECHO *      Proceed/Continue?
ECHO *
ECHO *      Input: Y)es   = Yes, proceed.
ECHO *             N)o    = No, keep the files.
ECHO *             A)bort = Stop processing now!
ECHO *
:756-UINPUT
SET ___UI=
SET /P ___UI="Please enter your choice (Yes/No/Abort): "
IF  /I '%___UI%' == 'Y'  GOTO 770-RMFILES
IF  /I '%___UI%' == 'N'  GOTO 790-CONTINUE
IF  /I '%___UI%' == 'A'  GOTO 980-ABORT
GOTO 756-UINPUT
REM
:760-ACLEAN
IF  /I '%___K%' == 'Y'  GOTO 790-CONTINUE
REM
:770-RMFILES
IF  /I '%___V%' == 'Y'  ECHO * (%0) Status: Deleting working files ...
REM
IF  EXIST SRCFILE     DEL SRCFILE
IF  EXIST OBJFILE     DEL OBJFILE
IF  EXIST LISFILE     DEL LISFILE
IF  EXIST INTFILE     DEL INTFILE
REM
IF  /I '%___V%' == 'Y'  ECHO * (%0) Status: Working files deleted.
REM
REM *---------------------------------------------*
REM
:790-CONTINUE
GOTO 900-ENDING
REM
REM *=============================================*
:810-USAGE
ECHO *
ECHO * "%0" is the command file to run SIC assembler
ECHO * to assemble a source program.
ECHO *
ECHO * Usage:
ECHO *
ECHO *   %0 [-Flags] [Source] [Obj] [Listing]
ECHO *
ECHO *   Arguments:
ECHO *
ECHO *     -Flags : Flags/Switches declaration
ECHO *           -V : Enable Verbose mode
ECHO *           -U : Enable User interaction
ECHO *           -K : Keep temporary working files
ECHO *           -? : Display this help message
ECHO *           -H : Display this help message
ECHO *           -h : Display this help message
ECHO *           -I : Display information of %0
ECHO *           -i : Display information of %0
ECHO *
ECHO *     [Source]  - File name of source program
ECHO *     [Obj]     - File name of object program
ECHO *     [Listing] - File name of listing
ECHO *
REM *=============================================*
REM
GOTO 999-EXIT
REM 
:860-INFORMATION
ECHO *
ECHO **********************************************
ECHO *
ECHO * %0
ECHO * Author: J. Chen
ECHO * Last Modofication: 2021/10/19
ECHO *
ECHO **********************************************
REM
GOTO 999-EXIT
REM 
REM *---------------------------------------------*
:900-ENDING
ECHO *
ECHO * (%0) PROCESS COMPLETED.
ECHO *
ECHO * Press [Enter] key to exit processing ....
ECHO *
PAUSE
REM *---------------------------------------------*
REM
ECHO *
ECHO ***** /// END OF %0 /// **********************
ECHO .
GOTO 999-EXIT
REM
REM *---------------------------------------------*
:980-ABORT
ECHO *
ECHO * (%0) User abort! Precossing terminated.
ECHO *
GOTO 999-EXIT
REM *---------------------------------------------*
:990-ERRS
REM
ECHO   //
ECHO   // (%0) error found and cannot proceed.
ECHO   // Processing stops now. Please check and
ECHO   // correct errors before re-run.
ECHO   //      
REM
:999-EXIT
REM ****** // END OF THIS BATCH COMMAND FILE // ******