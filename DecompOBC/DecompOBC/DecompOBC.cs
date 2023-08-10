using System;
using System.Diagnostics;
using System.IO;
using System.Text;
using System.Text.RegularExpressions;
using static System.Net.Mime.MediaTypeNames;

Console.WriteLine("DecompOBC ver. 1.2");
Console.WriteLine("Made by BJNFNE");
Console.WriteLine("\n");
Console.WriteLine("Write here the Path to the OBC File, after that a obc_output.txt gets created that contains the decompiled code.");

// only allows ".obc"
string myFilePath = @".obc";
string ext = Path.GetExtension(myFilePath);
string OBC_OUTPUT = Console.ReadLine();

// Creates OBC Output File
FileStream filestream = new FileStream("obc_output.txt", FileMode.Create);
var streamwriter = new StreamWriter(filestream);
streamwriter.AutoFlush = true;
Console.SetOut(streamwriter);
Console.SetError(streamwriter);

{
    Console.WriteLine("\n");
    // Extracts the Text of the OBC Script.
    Console.WriteLine(File.ReadAllText(@OBC_OUTPUT));

}
