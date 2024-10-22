@echo off
title Release Mode Compile Script for SYSTEM
echo Welcome to the SYSTEM compilation script (Release mode)!

REM Prompt the user to compile in release mode
set /p compile_release=Compile SYSTEM in release mode? (yes/no): 

REM Check the user input
if /i "%compile_release%"=="yes" (
    echo Compiling SYSTEM in release mode...
    REM Compile the source file
    cl.exe /O2 /EHsc /c /MT SYSTEM.cpp
    REM Link the object file
    link.exe /OUT:system.exe SYSTEM.obj user32.lib
) else if /i "%compile_release%"=="no" (
    echo Exiting without compilation.
    exit
) else (
    echo Invalid input. Please enter "yes" or "no".
)

echo Compilation completed successfully.
pause