using System.Diagnostics;
using System.Net.Sockets;
using System.Reflection;
string dir = AppDomain.CurrentDomain.BaseDirectory;


Console.WriteLine("Welcome to LOADER7VC, This program shows you which version your LOADER7.EXE / Dev7VM.EXE is.");
Console.WriteLine("\n");
Console.WriteLine("LOADER7VC was designed for DEV7 Games.");
Console.WriteLine("\n");
Console.WriteLine("Copyright: BJNFNE (Benjamin Funke) & DerCodeDev (Samir Ademi)");
Console.WriteLine("\n");


{
    // Gets the FileVersion of LOADER7.EXE / Dev7VM.EXE.
    Console.WriteLine("Please insert here your Path to your LOADER7.EXE / Dev7VM.EXE");
    string UserInput = Console.ReadLine();

    FileVersionInfo myFileVersionInfo = FileVersionInfo.GetVersionInfo(fileName: UserInput);

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
