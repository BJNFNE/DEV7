#include <iostream>
using namespace std;
int main()
{
    char ch, inputOBC[20], outputOBC[20];
    FILE *robc, *wobc;
    cout<<"Developed by BJNFNE\n";
    cout<<"WIP - the decompiled Scripts can eventually display non printable Characters.\n";
    cout<<"Enter the Name of the OBC Script that should be decompiled: ";
    cin>>inputOBC;
    robc = fopen(inputOBC, "r"); // robc stands for ReadOBC &  wobc stands for WriteOBC
    if(robc == nullptr)
    {
        cout<<"\nOBC Script not found!\n";

        return 0;
    }
    cout<<"\nOBC Script was found!\n";
    cout<<"\nEnter here your output filename including extension (TXT): ";
    cin>>outputOBC;
    wobc = fopen(outputOBC, "w");
    if(wobc == nullptr)
    {
        cout<<"\nError Occurred, by creating the output file!\n";
        return 0;
    }
    ch = fgetc(robc);
    while(ch != EOF)
    {
        fputc(ch, wobc);
        ch = fgetc(robc);
    }
    cout<<"\nOBC Script is decompiled successfully.";
    fclose(robc);
    fclose(wobc);
    cout<<endl;
    return 0;
}