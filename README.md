# DEV7
![DEV7 logo](/icons/DEV7_github_readme.png)

DEV7 is very well documented on the ScummVM Wiki see [here](https://wiki.scummvm.org/index.php?title=DEV7_Information) 

# Games that are using DEV7
1. Adibou 3
2. Adi 5
3. Adiboud'chou series
4. Adibou presente series
5. Le pays des pierres Magiques
6. Nathan Vacances series
7. English Fever series

# Tools (DEV7)
1. LOADER7VC checks which Version of DEV7 your LOADER7.EXE is.
2. OBCViewer shows the Text of the OBC Scripts for further analysis.
3. CTRKTextLoader loads the the Text of the CTRK files. (CTRK files are used for the rotation)
4. IMGIdentifier shows you which version your IMG is using.
5. IMGConverter converts Pictures to IMG file format, that then can be be used in Game.
6. ModelPathDumper dumps out of the EXO files the Path of the Models (Folders)
7. DEV7Launcher allows you to run Dev7VM.EXE or loader7.exe over an Launcher instead of the command.
8. BCD1Creator creates custom BCD1 files that can be used for Adibou 3's Applications.
9. OBCEditor allows you to modify the OBC Scripts.

# Tools (Reverse Engineering)
1. SecuROMDetector check if the executable uses SecuROM and displays the information about the SecuROM protection.
2. PKLiteDetector detects if the executable uses PKLite compression.
3. PetiteDetector detects if the executable uses Petite for the compression.
4. OBJDumper dumps all files with the extension .obj including Folderstructure into txt File for cleaner output.

# Rewritten original Software
- Rewritten original Software is to rewrite/decompile the programs as far as the where made back then.
1. LoaderMDO starts LOADER7.EXE, it was known as Adibou3.EXE / ADI5.EXE. for more Information see [here](https://github.com/BJNFNE/DEV7/blob/tools/LoaderMDO/LoaderMDO.cpp)
2. SYSTEM checks if the Disc is valid.
3. SYSTEM_RussianRelease this version of SYSTEM comes from the russian version of Adibou3 with slightly modifications to the original SYSTEM executable.

# Rewritten modern Software
- Rewritten modern Software ports the Software to newer Standards for modern platforms.
1. LoaderMDO was ported to modern Platform/Compiler to allow to use it under more modern platforms.