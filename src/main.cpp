#include <iostream>
#include <string>
#include "AsmCode.h"
#include "Number.h"

using std::cout;
using std::string;

// Function prototype.
vector<string>& readArguments(int, char**);
AsmCode* readSourceCode(const string);
bool writeLc(const AsmCode*);
bool writeSymbolTable(const AsmCode*);
bool writeObjectCode(const AsmCode*);

int main(int countArg, char** args)
{
    /*********************
     *  Read arguments.  *
     *********************/

    vector<string>& arguments = readArguments(countArg, args);



    /************************************
     *  Split source code into tokens.  *
     ************************************/

    AsmCode* code = nullptr;

    // Read source code.
    code = readSourceCode(string(arguments[0]));

    if(code == nullptr)
        return 1;

    // Write lc to file.
    writeLc(code);

    // Write symbol table to file.
    writeSymbolTable(code);

    // Write object code to file.
    writeObjectCode(code);

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
        exit(1);
    }

    arguments.push_back(args[1]);

    if(countArg == 3)
    {
        if(args[2] != "-s" && args[2] != "-t" && args[2] != "-a")
        {
            cout << "Invalid argument : " << args[2] << "\n";
            exit(1);
        }

        arguments.push_back(args[2]);
    }

    return arguments;
}

AsmCode* readSourceCode(const string fileName)
{
    if(fileName == "")
    {
        cout << "  File name is empty !\n";
        cout << "  Parsing source code ... Failed\n\n";
        
        return nullptr;
    }

    AsmCode* code = new AsmCode;

    cout << "> Parsing source code ...\n";

    if(code->read(fileName))
    {
        cout << "  Parsing source code ... Done\n\n";
        return code;
    }
    else
    {
        cout << "  Parsing source code ... Failed\n\n";
        delete code;
        
        return nullptr;
    }
}

bool writeLc(const AsmCode* code)
{
    cout << "> Writing location counter values to file ...\n";
    
    if(code->writeLc())
    {
        cout << "  Writing location counter values to file ... Done\n\n";
        return true;
    }
    else
    {
        cout << "  Writing location counter values to file ... Failed\n\n";
        return false;
    }
}

bool writeSymbolTable(const AsmCode* code)
{
    cout << "> Writing symbol table to file ...\n";

    if(code->writeSymbolTable())
    {
        cout << "  Writing symbol table to file ... Done\n\n";
        return true;
    }
    else
    {
        cout << "  Writing symbol table to file ... Failed\n\n";
        return false;
    }
}

bool writeObjectCode(const AsmCode* code)
{
    cout << "> Writing object code to file ...\n";

    if(code->writeObjectCode())
    {
        cout << "  Writing object code to file ... Done\n\n";
        return true;
    }
    else
    {
        cout << "  Writing object code to file ... Failed\n\n";
        return false;
    }
}

