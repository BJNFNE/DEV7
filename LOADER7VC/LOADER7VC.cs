using System.Diagnostics;
using System.Reflection;


Console.WriteLine("Welcome to LOADER7VC, This program shows you which version your LOADER7.EXE / Dev7VM.EXE is.");
Console.WriteLine("");
Console.WriteLine("LOADER7VC was designed for Adibou 3 & Adi 5");
Console.WriteLine("");
Console.WriteLine("Copyright: CrystalBen (Benjamin Funke) & DerCodeDev (Samir Ademi)");
Console.WriteLine("");



{
    // Gets the FileVersion of LOADER7.EXE / Dev7VM.EXE.
    FileVersionInfo myFileVersionInfo = FileVersionInfo.GetVersionInfo(fileName: @"Insert here your Path to your EXE example: C:\coktel\Adibou3\LOADER7.exe");


    // Print the Description and the Version.
    String text = "Description: " + myFileVersionInfo.FileDescription + '\n' +
    "Version: " + myFileVersionInfo.FileVersion;
    Console.WriteLine(text);
    Console.WriteLine("Thanks for using LOADER7VC");
}