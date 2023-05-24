using System;
using System.IO;
using System.Text;
Console.WriteLine("DecompOBC ver. 1.0");
Console.WriteLine("Made by CrystalBen");
Console.WriteLine("How to use?");
Console.WriteLine("type DecompOBC.exe then enter, type your OBC Script Path including your .obc File (without quotes), then it shows you the Text of the Script.");
Console.WriteLine("OBC Scripts (.obc) Files are also known as DEV7 object");
Console.WriteLine("\n");
Console.WriteLine("Write here the Path to the OBC File");

string OBC_OUTPUT = Console.ReadLine();


{
    Console.WriteLine("\n");
            // Output the Text of the OBC Script.
            Console.WriteLine(File.ReadAllText(@OBC_OUTPUT));



}
