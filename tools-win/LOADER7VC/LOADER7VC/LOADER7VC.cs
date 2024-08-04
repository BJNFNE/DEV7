using System;
using System.Diagnostics;
using System.IO;
using System.Security.Cryptography;
using System.Text;

class Program
{
    static void Main(string[] args)
    {
        string EXEInput = null;

        // Check if there is a command line argument
        if (args.Length > 0)
        {
            // Use the provided command line argument as the file path
            EXEInput = args[0];

            // Validate provided file path
            if (!ValidateFilePath(EXEInput))
            {
                Console.WriteLine("Only LOADER.EXE or Dev7VM.EXE.");
                Environment.Exit(1);
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
                Console.ReadLine();
                Environment.Exit(1);
            }
        }

        try
        {
            // Display file information
            DisplayFileInfo(EXEInput, interactive: true);
        }
        catch (Exception ex)
        {
            Console.WriteLine("An error occurred: " + ex.Message);
            Environment.Exit(1);
        }
    }

    static void DisplayFileInfo(string filePath, bool interactive)
    {
        // Calculate and display MD5 checksum
        string md5Sum = CalculateMD5(filePath);

        // Get file size
        long fileSize = new FileInfo(filePath).Length;

        FileVersionInfo myFileVersionInfo = FileVersionInfo.GetVersionInfo(filePath);
        string EXEFilename = Path.GetFileName(filePath);

        Console.WriteLine("\nInfos about " + EXEFilename + ":\n");

        PrintIfNoInfos("Original Filename", myFileVersionInfo.OriginalFilename);
        PrintIfNoInfos("Description", myFileVersionInfo.FileDescription);
        PrintIfNoInfos("Version", myFileVersionInfo.FileVersion);
        PrintIfNoInfos("Productname", myFileVersionInfo.ProductName);
        PrintIfNoInfos("Internalname", myFileVersionInfo.InternalName);
        PrintIfNoInfos("Copyright", myFileVersionInfo.LegalCopyright);
        PrintIfNoInfos("Language", myFileVersionInfo.Language); // Language of the executable is displayed in the Language that your system is set to.

        Console.WriteLine("MD5 Checksum: " + md5Sum);
        Console.WriteLine($"File Size: {fileSize} Bytes");

        // Read the content of the EXE file
        string exeContent = File.ReadAllText(filePath);

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

        // Wait for user input if running in interactive mode
        if (interactive)
        {
            Console.WriteLine("\nPress any key to exit LOADER7VC");
            Console.ReadKey();
        }
    }

    static bool ValidateFilePath(string filePath)
    {
        // Add additional validation if needed
        return filePath.EndsWith("LOADER7.EXE", StringComparison.OrdinalIgnoreCase) ||
               filePath.EndsWith("Dev7VM.EXE", StringComparison.OrdinalIgnoreCase);
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
