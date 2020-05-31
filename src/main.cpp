#include <iostream>
#include <fstream>
#include <string>
#include "AsmCode.h"

using std::cin;
using std::cout;
using std::ifstream;
using std::ofstream;
using std::string;

int main(int countArg, char** args)
{
    bool isWindows = false;

    /*********************
     *  Read arguments.  *
     *********************/

    // Print number of arguments and each argument.
    cout << "\n==== Argument List ====\n";
    cout << "Total : " << countArg << " arguments.\n";

    for(int i=0; i<countArg; ++i)
        cout << "Argument[" << i << "] : " << args[i] << "\n";

    if(countArg < 2 || countArg > 3)
    {
        cout << "Incorrect number of argument(s).\n";
        exit(0);
    }



    /***********************
     *  Read source code.  *
     ***********************/

    int countLines = 0, countComments = 0;
    string tmp = "", sourceCode = "";
    ifstream& fin = *(new ifstream());

    cout << "\n==== Read source code from file ====\n";

    // Open source code file.
    fin.open(string(args[1]) + ".asm");

    // Failed.
    if(fin.fail())
    {
        cout << "Fatal error : failed to open file \"" << args[1] << ".asm\".\n";
        exit(1);
    }

    // Read source code from file.
    while(getline(fin, tmp))
    {
        // Truncate '\r' for windows system.
        if(isWindows)
            tmp = tmp.substr(0, tmp.length()-1);
        else if(tmp[tmp.length() - 1] == '\r')
        {
            isWindows = true;
            tmp = tmp.substr(0, tmp.length()-1);
        }

        // Store new line input.
        if(tmp[0] != '.')
        {
            sourceCode += tmp + "\n";
            ++countLines;
        }
        // New line is a comment. This line should be ignored.
        else
        {
            cout << "comment[" << countComments << "] is ignored : " << tmp.substr(1, tmp.size()-1) << "\n";
            ++countComments;
        }
    }

    // Close file stream.
    fin.close();

    // Print info of source code.
    cout << "\nSource code / Comment : " << countLines << " / " << countComments << " line(s) read.\n\n";

    if(isWindows)
        cout << "The input file (source code) is written on Windows.\nThe output file(s) will use \\r\\n for a new line.\n";
    else
        cout << "The input file (source code) is written on Linux or Mac.\nThe output file(s) will use \\n for a new line.\n";



    /************************************
     *  Split source code into tokens.  *
     ************************************/

    AsmCode* code = new AsmCode;

    cout << "\n==== Split source code into tokens ====\n";

    // Add source code to class and split source code string into tokens.
    code->setSourceCode(sourceCode);

    // Print number of tokens.
    cout << code->getTokenLength() << " token(s) found.\n";

    return 0;
}

