#include <iostream>
using namespace std;
int main()
{
    char ch, inputOBC[20], outputOBC[20];
    FILE *fs, *ft;
    cout<<"Developed by BJNFNE\n";
    cout<<"WIP - the decompiled Scripts can eventually display non printable Characters.\n";
    cout<<"Enter the Name of the OBC Script that should be decompiled: ";
    cin>>inputOBC;
    fs = fopen(inputOBC, "r");
    if(fs == NULL)
    {
        cout<<"\nOBC Script not found!\n";

        return 0;
    }
    cout<<"\nOBC Script was found!\n";
    cout<<"\nEnter here your output filename including extension (TXT): ";
    cin>>outputOBC;
    ft = fopen(outputOBC, "w");
    if(ft == NULL)
    {
        cout<<"\nError Occurred, by creating the output file!\n";
        return 0;
    }
    ch = fgetc(fs);
    while(ch != EOF)
    {
        fputc(ch, ft);
        ch = fgetc(fs);
    }
    cout<<"\nOBC Script is decompiled successfully.";
    fclose(fs);
    fclose(ft);
    cout<<endl;
    return 0;
}
