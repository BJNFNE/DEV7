using System;
using System.Diagnostics;
using System.IO;
using System.Text;

Console.Title = "CTRKTextLoader 1.0";

Console.WriteLine("Made by BJNFNE");
Console.WriteLine("\f");
Console.WriteLine("Enter here the Path to the CTRK file, after that ctrk_text.txt gets created that contains the text of the CTRK file.");
Console.WriteLine("\b");

string CTRK_TEXT = Console.ReadLine();

// creates CTRK text File
FileStream ctrk_textfile = new FileStream("ctrk_text.txt", FileMode.Create);
var ctrk_textloader = new StreamWriter(ctrk_textfile);
ctrk_textloader.AutoFlush = true;
Console.SetOut(ctrk_textloader);
Console.SetError(ctrk_textloader);

{
    Console.WriteLine("\n");
    // Shows the Text of CTRK.
    Console.WriteLine(File.ReadAllText(CTRK_TEXT));

}