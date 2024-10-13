@echo off
setlocal
title SYSTEM Copy Utility v1.0

:: Define the source file
set SOURCE_FILE=SYSTEM.EXE

:: Prompt the user for the destination directory
set /p DEST_DIR="Enter the destination directory where SYSTEM.EXE should be copied: "

:: Ensure the destination directory exists
if not exist "%DEST_DIR%" (
    echo Destination directory does not exist.
    exit /b 1
)

:: Search for any case-insensitive variation of system.exe in the destination directory
for %%F in (SYSTEM.EXE system.exe System.exe) do (
    if exist "%DEST_DIR%\%%F" (
        set FILE_FOUND=%%F
    )
)

:: If a file is found, ask the user whether to replace it
if defined FILE_FOUND (
    echo %FILE_FOUND% already exists in this directory.
    set /p REPLACE="Do you want to replace it? (y/n): "

    if /i "%REPLACE%" neq "y" (
        echo Operation aborted.
        exit /b 0
    )
)

:: Proceed with copying the file
copy /Y "%SOURCE_FILE%" "%DEST_DIR%\SYSTEM.EXE" >nul

if %errorlevel% equ 0 (
    echo %SOURCE_FILE% copied successfully to %DEST_DIR%.
) else (
    echo Error copying %SOURCE_FILE% to %DEST_DIR%
    echo Please make sure you either run this Script with Admin Rights
    echo Or make sure its not an copy protected path
)
pause
endlocal
exit /b 0
