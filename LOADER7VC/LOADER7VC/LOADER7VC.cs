using System.Diagnostics;
using System.Reflection;


Console.WriteLine("Welcome to LOADER7VC, This program shows you which version your LOADER7.EXE / Dev7VM.EXE is.");
Console.WriteLine("\n");
Console.WriteLine("LOADER7VC was designed for DEV7 Games.");
Console.WriteLine("\n");
Console.WriteLine("Copyright: CrystalBen (Benjamin Funke) & DerCodeDev (Samir Ademi)");
Console.WriteLine("\n");



{
    // Gets the FileVersion of LOADER7.EXE / Dev7VM.EXE.
    FileVersionInfo myFileVersionInfo = FileVersionInfo.GetVersionInfo(fileName: @"Insert here your Path to your EXE example: C:\coktel\Adibou3\LOADER7.exe");


    // Print the Description and the Version.
    String text = "Description: " + myFileVersionInfo.FileDescription + '\n' +
    "Version: " + myFileVersionInfo.FileVersion;
    Console.WriteLine(text);
        Console.WriteLine("\n");
        Console.WriteLine("Thanks for using LOADER7VC!");
    
    // This exits LOADER7VC
    
   Console.WriteLine("\nPress any key to exit LOADER7VC");

    Console.ReadKey();
}

