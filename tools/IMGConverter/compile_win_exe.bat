@echo off

title IMGConverter Compiler v1.0
echo Compile IMGConverter (Windows executable)
pyinstaller --onefile --distpath . IMGConverter.py
echo Press Enter to exit the Compiler
pause