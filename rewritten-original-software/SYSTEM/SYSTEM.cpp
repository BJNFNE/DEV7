#include "stdafx.h"
#include <windows.h>
#include <string.h>
#include <stdlib.h>

// Define comparisonString to be 0
char comparisonString[] = "0";

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    int result;

    // Compare the command-line argument with the value stored in comparisonString
    result = strcmp(lpCmdLine, comparisonString);

    // If the command line argument doesn't match, return the integer version of lpCmdLine
    if (result != 0)
        return atoi(lpCmdLine);

    // If the strings match, return the result (which would be 0 from strcmp)
    return result;
}
