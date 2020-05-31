#include <iostream>
#include <string>
#include "AsmCode.h"

using std::cout;
using std::string;

// Function prototype.
vector<string>& readArguments(int, char**);

int main(int countArg, char** args)
{
    /*********************
     *  Read arguments.  *
     *********************/

    vector<string>& arguments = readArguments(countArg, args);



    /************************************
     *  Split source code into tokens.  *
     ************************************/

    AsmCode* code = new AsmCode;

    // Read source code.
    code->read(string(arguments[0]) + ".asm");

    // Print line based source code.
    for(int i=0, sizeI=code->getLineBasedTokenLength(); i<sizeI; ++i)
    {
        cout << "[" << i << "]";
        
        for(int j=0, sizeJ=code->getLineBasedTokenLineLength(i); j<sizeJ; ++j)
            cout << " " << code->getLineBasedToken(i, j);

        cout << "\n";
    }

    return 0;
}



/**************************
 *  Function definition.  *
 **************************/

vector<string>& readArguments(int countArg, char** args)
{
    /*********************
     *  Read arguments.  *
     *********************/

    vector<string>& arguments = *(new vector<string>);
    
    if(countArg < 2 || countArg > 3)
    {
        cout << "Incorrect number of argument(s).\n";
        exit(0);
    }

    arguments.push_back(args[1]);

    if(countArg == 3)
    {
        if(args[2] != "-s" && args[2] != "-t" && args[2] != "-a")
        {
            cout << "Invalid argument : " << args[2] << "\n";
            exit(0);
        }

        arguments.push_back(args[2]);
    }

    return arguments;
}

