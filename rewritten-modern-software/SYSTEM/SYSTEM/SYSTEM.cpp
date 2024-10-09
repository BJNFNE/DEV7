/*
This is a port to the x64 Platform and newer C++. Code based on SYSTEM's rewritten code, which can be found in /rewritten-original-software/SYSTEM/SYSTEM.cpp
SYSTEM was developed to check if the Disc is valid or not.
This version is from 2000 that which one doesn't used SecuROM yet.
SecuROM was started to being used in later versions in SYSTEM.EXE.

Requirements:
-  Compile under MSVC 2022 or MinGW
-  Compatible with Windows 7 to Windows 11
-  Make sure to have Visual C++ Redistributable 2022 x64 installed.
Compiling:
- Can directly be compiled in MSVC: You can change between Release or Debug mode.
- To compile over g++/MinGW: you can run this command to compile: g++ -o SYSTEM.exe SYSTEM.cpp -luser32
- When you want to remove the debug symbols from the exe use the "strip SYSTEM.exe" (Without quotes) command (g++/MinGW only)

Supported Games:
- Adibou3 (Fully supported)
- ADI 5 (Fully supported)
- Adiboud'chou (Fully supported)
- Adibou présenté (Fully supported)

Unsupported Games (currently):
- English Fever (Here is it called SystemEx.exe instead of SYSTEM.EXE, it had also an own compiled Dev7VM.exe which the new SystemEx.exe reference)

Not used SYSTEM.EXE Games:
- Nathan Vacances
- Le Pays des Pierres Magiques

Supported Applications:
- ADI 5
-- French:
-- Mathématiques CE1
-- Français CE1
-- German:
-- Englisch Klasse 5
-- Deutsch Klasse 7+8

- Adibou3
-- French:
-- Calcul 4-6 ans
-- Lecture 4-6 ans
-- German:
-- Natur und Technik
-- Die rätselhafte Musikmaschine
-- Mathe & Deutsch 4-6 Jahre
-- Mathe & Deutsch 6-7 Jahre
-- Das Königreich Hocus Pocus (English 4-7 Jahre)
-- English:
-- The Mysterious Music Machine (Music 4-7 years)
-- Reading-Maths 5-6 years
-- Dutch:
-- Lezen 5-6 jaar
-- Rekenen 5-6 jaar
-- Russian:
-- Êîðîëåâñòâî Ôîêóñ-Ïîêóñ (Àíãëèéñêèé, 4-7 ëåò)
-- Çàáûòàÿ ñòðàíà (Íàóêè, 4-7 ëåò)
-- Ãîðîä Íåðàâåíñòâ (Ñ÷åò 5-6 ëåò)
-- Ñ÷åòíàÿ äîëèíà (Ñ÷åò 6-7 ëåò)
-- Çàãàäî÷íàÿ ìóçûêàëüíàÿ ìàøèíà (Ìóçûêà, 4-7 ëåò)

- Adibou présenté
-- French:
-- Adibou présenté Cuisine
-- Adibou présenté Dessin
-- Adibou présente la magie
-- English:
-- Adiboo presents Cooking
-- Adiboo presents Drawing

- Adiboud'chou
-- French:
-- Adiboud'chou à la campagne
-- Adiboud'chou dans la jungle et la savane
-- German:
-- Addy Buschu Eis & Schnee (Addy Mini version works aswell)
-- Addy Buschu Am Meer (Addy Mini version works aswell)
-- Addy Buschu Die Bunte Tierwelt (Addy Mini version works aswell)
-- Russian:
-- Â ãîñòÿõ ó Òèìîøêè
-- Spanish:
-- Adibú Chu-El Mar

FIRST_IDEA?:
- It turns out that the original release from 2000 of Adiboud'chou works
- Although the Re-Releases are modified which fails then to run the Game with the reimplemented executable.

WORKAROUND:
- Why some versions of ADI5 Adiboud'chou and Adibou3 don't accept the executable?
- For some Games you can leave the Environment CD/ISO mounted and mount the Application CD/ISO as an seperate drive.
- Some Games although needs to be mounted in the same Drive as the Environment so there you have to change the CD/ISO.

How does this works?
-- Adibou3
- Adibou3 checks when you want to enter an Application, if the Disc is valid over the B3_CDMANGER.OBC/B3_CHOOSEAPPLI.OBC script with the CheckCDPresent()
  Next after this the BCD1 file will be checked if it contains the required filename and content in the BCD1 file.
  If the Disc is valid, After this the required Game assets will be loaded with the OpenAppli()

-- Adibou presente
- Adibou presente games checks when you want to enter the Game, if the Disc is valid over the SFLOATBOOBAR.OBC script with the BOOT() function with
- the comment "Official CD found".

Based on system.exe MD5: d956cf751400520075cd5910673f5a1f Date: Jun 10 2000 (24KB)
Another system.exe is identical to this code, which is instead 280KB large in Filesize: MD5: 76c96b9be44359c9afba513db6c2c9b6 Date: 13. Jun 2000
*/

#include "pch.h"
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
