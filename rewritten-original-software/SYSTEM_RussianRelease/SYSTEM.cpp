/*
SYSTEM was developed to check if the Disc is valid or not.
It was mainly re-developed for Антошка3 Applications.
This version comes from the russian release and is slightly different from the original SYSTEM executable.

Requirements:
-  Compile under MSVC 6.0 build 8168 (Any newer build of MSVC6.0 work aswell but Coktel/Akella/MDO used back then used exactly this version of the Compiler.)

Compiling:
- build_release.bat: Run the batch script and confirm with yes to compile.

TODO:
- Implement the "strings" for the license.
- Include MSVCRT functions for heap (stdio.h)

Supported Games:
- ADI5 (Fully supported)
- Антошка3 (Fully supported)
- Adibou présenté (Fully supported)
- Adiboud'chou (Fully supported)

Not used SYSTEM.EXE Games:
- Adibou3 (Demo only)
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

- Антошка3
-- French:
-- Calcul 4-6 ans
-- Lecture 4-6 ans
-  L'île volante (4-7 ans)
-  L'orgue fantastique (4-7 ans)
-  Le royaume d'Hocus Pocus (4-7 ans)
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

WORKAROUND:
- Why some versions of Антошка3 don't accept the executable?
- For some Games you can leave the Environment CD/ISO mounted and mount the Application CD/ISO as an seperate drive.
- Some Games although needs to be mounted in the same Drive as the Environment so there you have to change the CD/ISO.

How does this works?
-- Антошка3
- Антошка3 checks when you want to enter an Application, if the Disc is valid over the B3_CDMANGER.OBC/B3_CHOOSEAPPLI.OBC script with the CheckCDPresent() with the comment "cd ok".
  Next after this the BCD1 file will be checked if it contains the required filename and content in the BCD1 file.
  If the Disc is valid, After this the required Game assets will be loaded with the OpenAppli()
  SYSTEM is only being executed when "cd ok" message is being printed.

Based on system.exe MD5: 2515cf4364dccf43f8002225dfa0d6fa Date: Nov 05 2005 (36KB)
*/

#include "stdafx.h"
#include <windows.h>
#include <stdio.h> // Used for MSVCRT
#include <stdlib.h>

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
  return atoi(lpCmdLine);
}
