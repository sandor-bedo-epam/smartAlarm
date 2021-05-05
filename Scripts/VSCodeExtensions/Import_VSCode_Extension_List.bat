@echo OFF

echo Started: %date% %time%

if "%1"=="" goto :ERROR
echo Input file is %1 & echo.
goto :OK


:ERROR
	echo echo. & Please correct the input parameter to install all necessary extensions for your VSCode
	goto END
	
:OK
	echo OK & echo.
	
	for /f "tokens=*" %%a in (%1) do (
		color 00
		echo %%a
		call code --install-extension %%a
		echo. 
	)
	
:END
	echo Completed: %date% %time%