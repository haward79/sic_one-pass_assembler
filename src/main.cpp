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
    cout << "> Parsing source code ...\n";
    code->read(string(arguments[0]) + ".asm");
    cout << "  Parsing source code ... Done\n\n";

    // Write lc to file.
    cout << "> Writing location counter values to file ...\n";
    
    if(code->writeLc(arguments[0] + ".lst"))
        cout << "  Writing location counter values to file ... Done\n\n";
    else
        cout << "  Writing location counter values to file ... Failed\n\n";

    // Write symbol table to file.
    cout << "> Writing symbol table to file ...\n";

    if(code->writeSymbolTable(arguments[0] + ".stb"))
        cout << "  Writing symbol table to file ... Done\n\n";
    else
        cout << "  Writing symbol table to file ... Failed\n\n";

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

