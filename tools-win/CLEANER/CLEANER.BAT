REM CLEANER was made to remove the leftovers that UNINST.EXE are leave in the directory over.
@del "%s" > nul
@rd "%s" > nul
@deltree /y "%s" > nul
@rd /s /q "%s" > nul
@del /f /s /q "%s" > nul
