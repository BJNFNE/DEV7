@echo off
title Installation script for DEV7 repository deps
REM Run this Script as Administrator! 

REM Winget installation commands (ID's of the Program were used here)
winget install Python.Python.3.12 REM must be 3.12
winget install Kitware.CMake
winget install LLVM.LLVM

