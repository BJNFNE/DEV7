using System;
using System.Diagnostics;
using System.IO;
using System.Security.Cryptography;
using System.Text;

// TODO:
// add interactive/noninteractive mode, if Program gets executed over an Command Line, then do not print "Press any Key to exit" but altough the Program gets executed via an Double-Click then print "Press any Key to exit"

class Program
{
    static void Main(string[] args)
    {
        string EXEInput;

        // Check if there is a command line argument
        if (args.Length > 0)
        {
            // Use the provided command line argument as the file path
            EXEInput = args[0];

            // Check if the provided file ends with "LOADER7.EXE" or "Dev7VM.EXE"
            if (!EXEInput.EndsWith("LOADER7.EXE", StringComparison.OrdinalIgnoreCase) &&
                !EXEInput.EndsWith("Dev7VM.EXE", StringComparison.OrdinalIgnoreCase))
            {
                Console.WriteLine("Please make sure you use the Tool on either LOADER7.EXE or Dev7VM.EXE!");
                return;
            }
        }
        else
        {
            // Check if LOADER7.EXE or Dev7VM.EXE exists in the current directory
            string loader7Path = Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "LOADER7.EXE");
            string dev7VMPath = Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "Dev7VM.EXE");

            if (File.Exists(loader7Path))
            {
                EXEInput = loader7Path;
            }
            else if (File.Exists(dev7VMPath))
            {
                EXEInput = dev7VMPath;
            }
            else
            {
                Console.WriteLine("LOADER7.EXE or Dev7VM.EXE not found in the current directory.");
                Console.WriteLine("Press enter to exit");
                Console.ReadKey();
                return;
            }
        }

        // Calculate and display MD5 checksum
        string md5Sum = CalculateMD5(EXEInput);

        // Get file size
        long fileSize = new FileInfo(EXEInput).Length;

        FileVersionInfo myFileVersionInfo = FileVersionInfo.GetVersionInfo(EXEInput);
        string EXEFilename = Path.GetFileName(EXEInput);

        Console.WriteLine("\nInfos about " + EXEFilename + ":\n");

        PrintIfNoInfos("Original Filename", myFileVersionInfo.OriginalFilename);
        PrintIfNoInfos("Description", myFileVersionInfo.FileDescription);
        PrintIfNoInfos("Version", myFileVersionInfo.FileVersion);
        PrintIfNoInfos("Productname", myFileVersionInfo.ProductName);
        PrintIfNoInfos("Internalname", myFileVersionInfo.InternalName);
        PrintIfNoInfos("Copyright", myFileVersionInfo.LegalCopyright);

        Console.WriteLine("MD5 Checksum: " + md5Sum);
        Console.WriteLine($"File Size: {fileSize} Bytes");

        // Read the content of the EXE file
        string exeContent = File.ReadAllText(EXEInput);

        // Find the index of "NB10" in the content
        int nb10Index = exeContent.IndexOf("NB10");

        // Check if "NB10" is found in the content
        if (nb10Index != -1)
        {
            // Print everything after "NB10" to display the PDB File Path
            string afterNB10 = exeContent.Substring(nb10Index + 4);
            string pdbFilePath = GetPrintableString(afterNB10);
            PrintIfNoInfos("PDB File", pdbFilePath);
        }
        else
        {
            Console.WriteLine("PDB File reference not found in " + EXEFilename);
        }

        Console.WriteLine("\nPress any key to exit LOADER7VC");
        Console.ReadKey();
    }

    static void PrintIfNoInfos(string label, string value)
    {
        if (!string.IsNullOrEmpty(value))
        {
            Console.WriteLine($"{label}: {value}");
        }
        else
        {
            Console.WriteLine($"{label}: Not available in LOADER7.EXE/Dev7VM.EXE.");
         }
       }

    static string CalculateMD5(string filePath)
    {
        using (var md5 = MD5.Create())
        {
            using (var stream = File.OpenRead(filePath))
            {
                byte[] hash = md5.ComputeHash(stream);
                return BitConverter.ToString(hash).Replace("-", "").ToLower();
            }
        }
    }

    static string GetPrintableString(string input)
    {
        // Remove non-printable characters from the input string
        StringBuilder printableString = new StringBuilder();

        foreach (char c in input)
        {
            if (Char.IsControl(c) && !Char.IsWhiteSpace(c))
            {
                // Skip non-printable characters
            }
            else
            {
                printableString.Append(c);
            }
        }

        return printableString.ToString();
    }
}
