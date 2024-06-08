@echo off
setlocal enabledelayedexpansion
title LoaderMDO Copy Utility v1.0

REM Get the current directory
set "currentDir=%~dp0"

REM Check if LoaderMDO.exe exists in the current directory
if not exist "%currentDir%LoaderMDO.exe" (
    echo LoaderMDO.exe not found in the current directory.
    goto end
)

echo LoaderMDO.exe found. Checking for DEV7 games...

REM Initialize a counter
set "counter=0"
set "drives=C D E F G H I J K L M N O P Q R S T U V W X Y Z"

REM Find all drives and search for directories containing Loader7.exe or Dev7VM.exe
for %%D in (%drives%) do (
    if exist %%D:\ (
        for /d %%F in (%%D:\coktel\*) do (
            if exist "%%F\Loader7.exe" (
                set /a counter+=1
                set "dir!counter!=%%F"
                echo !counter!: %%F
            ) else if exist "%%F\Dev7VM.exe" (
                set /a counter+=1
                set "dir!counter!=%%F"
                echo !counter!: %%F
            )
        )
    )
)

REM Check if any directories with Loader7.exe or Dev7VM.exe were found
if %counter%==0 (
    echo No directories were detected which are for DEV7 games.
    goto end
)

REM Prompt the user to select a directory
:input
set /p "choice=Enter the number of the directory where you want to copy LoaderMDO.exe: "

REM Validate the user's choice
if not defined dir%choice% (
    echo Invalid choice. Please enter a valid number.
    goto input
)

REM Set the destination directory
set "destination=!dir%choice%!"

REM Check if LoaderMDO.exe exists in the destination directory
if exist "%destination%\LoaderMDO.exe" (
    echo LoaderMDO.exe already exists in %destination%.
    set /p "overwrite=Do you want to overwrite it? (Y/N): "
    if /I not "!overwrite!"=="Y" (
        echo Copy operation cancelled.
        goto end
    )
)

REM Copy LoaderMDO.exe to the selected directory
echo Copying LoaderMDO.exe to %destination%
copy "%currentDir%LoaderMDO.exe" "%destination%\"

echo Copy process completed.

:end
endlocal
pause
