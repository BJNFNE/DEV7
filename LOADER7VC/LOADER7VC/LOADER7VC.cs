using System.Diagnostics;
using System.Net.Sockets;
using System.Reflection;
string dir = AppDomain.CurrentDomain.BaseDirectory;


// Gets the FileVersion of LOADER7.EXE / Dev7VM.EXE.
    Console.WriteLine("Please insert here your Path to your LOADER7.EXE / Dev7VM.EXE (Without Quotes)");
    Console.WriteLine("\b");
    string EXEInput = Console.ReadLine();

    FileVersionInfo myFileVersionInfo = FileVersionInfo.GetVersionInfo(fileName: EXEInput);

    // Print the Description and the Version.
    string Description = "Description: " + myFileVersionInfo.FileDescription;
    string Version = "Version: " + myFileVersionInfo.FileVersion;
    Console.WriteLine("\b");
    Console.WriteLine(Description);
    Console.WriteLine(Version);

     // Print General Infos about LOADER7.EXE / Dev7VM.EXE
    Console.Write("\n");
    Console.WriteLine("General Infos");
    Console.WriteLine("\b");
    string OriginalFileName = "Original Filename: " + myFileVersionInfo.OriginalFilename;
    Console.WriteLine(OriginalFileName);

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
}
