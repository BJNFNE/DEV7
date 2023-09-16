﻿using System;
using System.Diagnostics;
using System.IO;
using System.Text;

Console.Title = "DecompOBC 1.2.1 DEV Build";

Console.WriteLine("Made by BJNFNE\f");
Console.WriteLine("Enter here the Path to the OBC Script, after that obc_output.txt gets created that contains the decompiled code.");
Console.WriteLine("The Path to the OBC Scripts can also be inserted via Drag & Drop into the Decompiler. (without Quotes)\b");
Console.WriteLine("\b");
Console.WriteLine("WIP - the decompiled Scripts can eventually display non printable Characters");
Console.WriteLine("\b");

string OBC_OUTPUT = Console.ReadLine();

// Creates OBC Output File
FileStream obc_output_textfile = new FileStream("obc_output.txt", FileMode.Create);
var obc_decompiler = new StreamWriter(obc_output_textfile);
obc_decompiler.AutoFlush = true;
Console.SetOut(obc_decompiler);
Console.SetError(obc_decompiler);

{
    Console.WriteLine("\n");
    // Extracts the Text of the OBC Script.
    Console.WriteLine(File.ReadAllText(@OBC_OUTPUT));

}