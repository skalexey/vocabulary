@echo off

set executableName=vocabulary.exe
set destinationFolder=Release
set argCount=0
for %%x in (%*) do (
	set /A argCount+=1
	if "%%~x" == "debug" (
		echo --- 'debug' option passed. Use Debug build folder
		set destinationFolder=Debug
	)
)

set dir=%CD%
set buildDir=%CD%\Build-cmake-%destinationFolder%\Debug
set homeDir=%CD%

cd /D %QT_DIR%\msvc2019_64\bin\

call windeployqt.exe %buildDir%\%executableName% --qmldir %homeDir%
cd %dir%
echo All is done

