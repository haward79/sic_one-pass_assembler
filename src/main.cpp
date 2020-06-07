#include <stdio.h>
#include <iostream>
#include <string>
#include "AsmCode.h"
#include "Number.h"

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

    // Print lc.
    for(int i=0, sizeI=code->getLineBasedTokenLength(); i<sizeI; ++i)
    {
        if(code->getLc(i) >= 0)
            printf("[%2d]  %s  %4d\t%s\n", i, Number::decimalToHex(code->getLc(i), 5).c_str(), code->getLc(i), code->getSourceCode()[i].c_str());
        else
            printf("[%2d]  %s  %s\t%s\n", i, "     ", "    ", code->getSourceCode()[i].c_str());
    }

    cout << "\n";

    // Release object.
    delete code;

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

