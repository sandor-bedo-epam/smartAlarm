@echo OFF

echo Started: %date% %time%
echo.
echo Export VSCode's extension list to a list file near this sctipt!
echo.

set CUR_YYYY=20%date:~6,2%
set CUR_MM=%date:~0,2%
set CUR_DD=%date:~3,2%
set CUR_HH=%time:~0,2%
if %CUR_HH% lss 10 (set CUR_HH=0%time:~1,1%)
set CUR_MIN=%time:~3,2%

set SUBFILENAME=VSCode_ExtensionList_%CUR_YYYY%%CUR_MM%%CUR_DD%_%CUR_HH%%CUR_MIN%

CALL code --list-extensions >> ./%SUBFILENAME%.list
echo.
echo Completed: %date% %time%
echo.

PAUSE