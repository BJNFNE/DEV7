using System.Diagnostics;
using System.IO;
using System.Net.Sockets;
using System.Reflection;
string dir = AppDomain.CurrentDomain.BaseDirectory;

Console.WriteLine("Welcome to LOADER7VC ver 1.4, This program shows you which version your LOADER7.EXE / Dev7VM.EXE is.\f");
Console.WriteLine("LOADER7VC was designed for DEV7 Games.\n");
Console.WriteLine("Developed by: BJNFNE\n");

// Gets the FileVersion of LOADER7.EXE / Dev7VM.EXE.
Console.WriteLine("Please insert here your Path to your LOADER7.EXE / Dev7VM.EXE (without Quotes)");
Console.WriteLine("\f");
string EXEInput = Console.ReadLine();

FileVersionInfo myFileVersionInfo = FileVersionInfo.GetVersionInfo(fileName: EXEInput);

// Print General Infos about LOADER7.EXE / Dev7VM.EXE
Console.Write("\n");
Console.WriteLine("General Infos: \n");
string OriginalFileName = "Original Filename: " + myFileVersionInfo.OriginalFilename;
Console.WriteLine(OriginalFileName);

string Description = "Description: " + myFileVersionInfo.FileDescription;
Console.WriteLine(Description);

string Version = "Version: " + myFileVersionInfo.FileVersion;
Console.WriteLine(Version);

string ProductName = "Productname: " + myFileVersionInfo.ProductName;
Console.WriteLine(ProductName);

string InternalName = "Internalname: " + myFileVersionInfo.InternalName;
Console.WriteLine(InternalName);

string Copyright = "Copyright: " + myFileVersionInfo.LegalCopyright;
Console.WriteLine(Copyright);

// executes Thank message
Console.WriteLine("\b");
Console.WriteLine("Thanks for using LOADER7VC!");

// This exits LOADER7VC

Console.WriteLine("\nPress any key to exit LOADER7VC");

Console.ReadKey();