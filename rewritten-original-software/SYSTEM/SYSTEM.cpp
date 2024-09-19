/*
SYSTEM was developed to check if the Disc is valid or not.
This version is from 2000 that which one doesn't used SecuROM yet.
SecuROM was started to being used in 2001/2002 in SYSTEM.EXE.

Requirements:
-  Compile under MSVC 6.0 build 8168 (Any newer build of MSVC6.0 work aswell but Coktel/MDO used back then used exactly this version of the Compiler.)

Compiling:
- build_release.bat: Run the batch script and confirm with yes to compile.

Supported Games:
- Adibou3 (partially)
- Adiboud'chou (partially)

Supported Applications:
- Adibou3
-- German:
-- Natur und Technik
-- Die rätselhafte Musikmaschine
-- Mathe & Deutsch 4-6 Jahre
-- Mathe & Deutsch 6-7 Jahre
-- Das Königreich Hocus Pocus (English 4-7 Jahre)
-- Dutch:
-- Lezen 5-6 jaar

- Adiboud'chou
-- French:
-- Adiboud'chou à la campagne
-- Spanish:
-- Adibú Chu-El Mar

TODO:
- Find out why some versions of ADI5 Adiboud'chou and Adibou3 don't accept the executable.
FIRST_IDEA?:
- It turns out that the original release from 2000 of Adiboud'chou works
- Although the Re-Releases are modified which fails then to run the Game with the reimplemented executable.

Based on system.exe MD5: d956cf751400520075cd5910673f5a1f Date: Jun 10 2000
*/

#include "stdafx.h"
#include <windows.h>
#include <string.h>
#include <stdlib.h>

// Define comparisonString to be 0
char comparisonString[] = "0";

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    int result;

    // Compare the command-line argument with the value stored in comparisonString
    result = strcmp(lpCmdLine, comparisonString);

    // If the command line argument doesn't match, return the integer version of lpCmdLine
    if (result != 0)
        return atoi(lpCmdLine);

    // If the strings match, return the result (which would be 0 from strcmp)
    return result;
}
