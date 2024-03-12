@echo off
echo Cleaning up LoaderMDO project directory...

rem Change the current directory to the script's directory
cd %~dp0

rem Function to prompt for deletion confirmation
:confirm_delete
set /P choice=Do you want to delete these files? (y/n): 
if /I "%choice%"=="y" goto :delete_files
if /I "%choice%"=="n" goto :cleanup_complete
echo Invalid choice. Please enter y for Yes or n for No.
goto :confirm_delete

:delete_files
rem Remove object files
echo Removing object files...
del /s /q *.obj 2>nul

rem Remove Debug directory
rd /s /q Debug 2>nul

rem Remove Release directory
rd /s /q Release 2>nul

rem Remove temporary files
echo Removing temporary files...
del /s /q *.pch 2>nul
del /s /q *.plg 2>nul
del /s /q *.ncb 2>nul
del /s /q *.opt 2>nul
del /s /q *.ilk 2>nul
del /s /q *.pdb 2>nul
del /s /q *.aps 2>nul
del /s /q *.sbr 2>nul
del /s /q *.idb 2>nul
del /s /q *.html 2>nul

rem Remove executables
echo Removing executables...
del /s /q *.exe 2>nul

echo Cleanup complete.
pause
exit

:cleanup_complete
echo Cleanup aborted.
pause
exit
