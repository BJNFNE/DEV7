@echo off
title Debug Mode Compile Script for SYSTEM
echo Welcome to the SYSTEM compilation script (Debug mode)!

REM Prompt the user to compile in debug mode
set /p compile_debug=Compile LoaderMDO in debug mode? (yes/no): 

REM Check the user input
if /i "%compile_debug%"=="yes" (
    echo Compiling SYSTEM in debug mode...
    REM Compile the source file
    cl.exe /Zi /EHsc /MDd /MT /c SYSTEM.cpp
    REM Link the object file
    link.exe /DEBUG /PDB:SYSTEM.pdb /MAP /SUBSYSTEM:WINDOWS /OUT:SYSTEM.EXE SYSTEM.obj user32.lib
) else if /i "%compile_debug%"=="no" (
    echo Exiting without compilation.
    exit
) else (
    echo Invalid input. Please enter "yes" or "no".
)

echo Compilation completed successfully.
pause
