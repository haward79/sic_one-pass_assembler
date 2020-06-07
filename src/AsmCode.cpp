#include "AsmCode.h"

/*******************
 *  Not in class.  *
 *******************/

// Functions.
bool isSeperator(char ch)
{
    switch(ch)
    {
        // ch is a seperator.
        case ' ':
        case ',':
        case '\t':
            return true;

        // ch is NOT a seperator.
        default:
            return false;
    }
}

vector<string>* explode(const string& str)
{
    int startFlag = 0, endFlag = 0;
    int strLength = str.length();
    vector<string>* extract = new vector<string>;

    // Clear vector.
    extract->clear();

    // Extract string.
    while(endFlag < strLength)
    {
        for(int i=startFlag; i<strLength; ++i)
        {
            // Set end flag for sub-string.
            if(isSeperator(str[i]))
            {
                endFlag = i;
                break;
            }

            // Reach end of line.
            if(i == strLength - 1)
                endFlag = strLength;
        }

        // Store non-empty sub-string.
        if(endFlag != startFlag)
            extract->push_back(str.substr(startFlag, endFlag - startFlag));

        startFlag = ++endFlag;
    }

    return extract;
}

string getOpcodeStr(string mnemonic)
{
    /*********************************
     *  Return op code in hex.       *
     *  Mnemonic is case sensitive.  *
     *********************************/

    if(mnemonic == "ADD")
        return "18";
    else if(mnemonic == "AND")
        return "40";
    else if(mnemonic == "COMP")
        return "28";
    else if(mnemonic == "DIV")
        return "24";
    else if(mnemonic == "J")
        return "3C";
    else if(mnemonic == "JEQ")
        return "30";
    else if(mnemonic == "JGT")
        return "34";
    else if(mnemonic == "JLT")
        return "38";
    else if(mnemonic == "JSUB")
        return "48";
    else if(mnemonic == "LDA")
        return "00";
    else if(mnemonic == "LDCH")
        return "50";
    else if(mnemonic == "LDL")
        return "08";
    else if(mnemonic == "LDX")
        return "04";
    else if(mnemonic == "MUL")
        return "20";
    else if(mnemonic == "OR")
        return "44";
    else if(mnemonic == "RD")
        return "D8";
    else if(mnemonic == "RSUB")
        return "4C";
    else if(mnemonic == "STA")
        return "0C";
    else if(mnemonic == "STCH")
        return "54";
    else if(mnemonic == "STL")
        return "14";
    else if(mnemonic == "STSW")
        return "E8";
    else if(mnemonic == "STX")
        return "10";
    else if(mnemonic == "SUB")
        return "1C";
    else if(mnemonic == "TD")
        return "E0";
    else if(mnemonic == "TIX")
        return "2C";
    else if(mnemonic == "WD")
        return "DC";
    else
        return "";
}



/******************************
 *  Public members in class.  *
 ******************************/

// Constructure.
AsmCode::AsmCode()
{
    clearSourceCode();
}

// Destructor.
AsmCode::~AsmCode()
{
    for(int i=0, sizeI=lineBasedTokens.size(); i<sizeI; ++i)
    {
        if(lineBasedTokens[i] != nullptr)
        {
            delete lineBasedTokens[i];
            lineBasedTokens[i] = nullptr;
        }
    }

    lineBasedTokens.clear();
}

// Methods.
const string AsmCode::getToken(int index) const
{
    // Count index from the beginning of the vector.
    if(index >= 0 && index < tokens.size())
        return tokens[index];
    // Count index from the end of the vector.
    else if(index < 0 && -index <= tokens.size())
        return tokens[tokens.size() + index];
    // Invalid index is given.
    else
        return "";
}

const int AsmCode::getLineBasedTokenLineLength(int line) const
{
    if(line >= 0 && line < lineBasedTokens.size())
        return lineBasedTokens[line]->size();
    else
        return 0;
}

const string AsmCode::getLineBasedToken(int line, int index) const
{
    // Validate line number and index.
    if(line >= 0 && line < lineBasedTokens.size() && index >= 0 && index < lineBasedTokens[line]->size())
        return (*lineBasedTokens[line])[index];
    else
        return "";
}

const int AsmCode::getLc(int index) const
{
    if(index >= 0 && index < lc.size())
        return lc[index];
    else
        return 0;
}

void AsmCode::clearSourceCode()
{
    sourceCode.clear();
    lineBasedTokens.clear();
    tokens.clear();
    lc.clear();
    isWindowsFormat = false;
    codeLength = 0;
}

void AsmCode::setSourceCode(const vector<string>& src)
{
    sourceCode = src;
    splitTokens();
}

void AsmCode::read(const string& filePath)
{
    string tmp = "";
    ifstream& fin = *(new ifstream());

    // Open source code file.
    fin.open(filePath);

    // Failed.
    if(fin.fail())
    {
        cout << "Fatal error : failed to open file \"" << filePath << "\".\n";
        return ;
    }

    // Read source code from file.
    while(getline(fin, tmp))
    {
        // Truncate '\r' for windows system.
        if(isWindowsFormat)
            tmp = tmp.substr(0, tmp.length()-1);
        else if(tmp[tmp.length() - 1] == '\r')
        {
            isWindowsFormat = true;
            tmp = tmp.substr(0, tmp.length()-1);
        }

        // Store new line input.
        sourceCode.push_back(tmp);
    }

    // Close file stream.
    fin.close();
    delete &fin;

    splitTokens();
    generateLc();
}



/*******************************
 *  Private members in class.  *
 *******************************/

// Methods.
void AsmCode::splitTokens()
{
    vector<string>* tokensTmp = nullptr;

    // Fetch all tokens.
    for(int i=0, size=sourceCode.size(); i<size; ++i)
    {
        // Skip comment.
        if(sourceCode[i][0] == '.')
        {
            tokens.push_back(sourceCode[i]);

            lineBasedTokens.push_back(new vector<string>);
            lineBasedTokens[lineBasedTokens.size()-1]->push_back(sourceCode[i]);

            continue;
        }

        tokensTmp = explode(sourceCode[i]);

        if(tokensTmp->size() > 0)
            lineBasedTokens.push_back(new vector<string>);

        for(int j=0, sizeJ=tokensTmp->size(); j<sizeJ; ++j)
        {
            tokens.push_back((*tokensTmp)[j]);
            lineBasedTokens[lineBasedTokens.size()-1]->push_back((*tokensTmp)[j]);
        }

        delete tokensTmp;
        tokensTmp = nullptr;
    }
}

void AsmCode::generateLc()
{
    int lcTmp = -999999999;
    string opcode = "";
    bool directive = false;
    SymbolTable symbols;
    Directive directiveTmp;

    symbols.clear();

    for(int i=0, sizeI=getLineBasedTokenLength(); i<sizeI; ++i)
    {
        // This line is NOT a comment.
        if(lineBasedTokens[i]->at(0)[0] != '.')
        {
            opcode = getOpcodeStr(lineBasedTokens[i]->at(0));
            directive = Directive::isDirective(lineBasedTokens[i]->at(0));
            
            // First token is a instruction.
            if(opcode != "")
            {
                lc.push_back(lcTmp);
                lcTmp += 3;

                // Handle operands as value or symbol.
            }
            // First token is a directive : END.
            else if(directive)
            {
                if(lineBasedTokens[i]->at(0) == "END")
                {
                    if(lineBasedTokens[i]->size() == 2)
                    {
                        lc.push_back(lcTmp);
                        // Handle lineBasedTokens[i]->at(1) as value or symbol.
                    }
                    else
                    {
                        cout << "[Line " << (i+1) << "] Invalid directive : " << lineBasedTokens[i]->at(1) << ". END is expected.\n";
                        exit(0);
                    }
                }
                else
                {
                    cout << "[Line " << (i+1) << "] Invalid directive : " << lineBasedTokens[i]->at(1) << ". END is expected.\n";
                    exit(0);
                }
            }
            // First token is a symbol.
            else
            {
                // Add new symbol to symbol table.
                if(!symbols.isSymbolExists(lineBasedTokens[i]->at(0)))
                    symbols.addSymbol(lineBasedTokens[i]->at(0));
                // Duplicate name of symbol.
                else
                {
                    cout << "[Line " << (i+1) << "] Known symbol : " << lineBasedTokens[i]->at(0) << " at " << symbols.getAddress(lineBasedTokens[i]->at(0)) << ".\n";
                    exit(0);
                }

                // Set symbol address as the value of lc.
                symbols.setAddress(lineBasedTokens[i]->at(0), std::to_string(lcTmp));

                // Set lc for this line.
                lc.push_back(lcTmp);

                opcode = getOpcodeStr(lineBasedTokens[i]->at(1));
                directive = Directive::isDirective(lineBasedTokens[i]->at(1));

                // Second token is a instruction.
                if(opcode != "")
                {
                    // Handle instruction and operands as values or symbols.

                    lcTmp += 3;
                }
                // Second token is a directive.
                else if(directive)
                {
                    directiveTmp.setName(lineBasedTokens[i]->at(1));

                    // Three fields : symbol, directive, and value.
                    if(lineBasedTokens[i]->size() == 3)
                    {
                        if(directiveTmp.setValue(lineBasedTokens[i]->at(2)))
                        {
                            if(directiveTmp.getName() == "BYTE")
                            {
                                if(directiveTmp.getType() == DirectiveType::dec)
                                    lcTmp += Number::minLengthOfByte(Number::toInteger(directiveTmp.getValue())) * 3;
                                else if(directiveTmp.getType() == DirectiveType::hex)
                                    lcTmp += (directiveTmp.getValue().length() + 1) / 2;
                                else  // Ascii.
                                    lcTmp += directiveTmp.getValue().length();
                            }
                            else if(directiveTmp.getName() == "WORD")
                                lcTmp += Number::minLengthOfWord(Number::toInteger(directiveTmp.getValue())) * 3;
                            else if(directiveTmp.getName() == "RESB")
                                lcTmp += Number::toInteger(directiveTmp.getValue());
                            else if(directiveTmp.getName() == "RESW")
                                lcTmp += Number::toInteger(directiveTmp.getValue()) * 3;
                            else if(directiveTmp.getName() == "START")
                            {
                                if(lineBasedTokens[i]->size() == 3)
                                {
                                    if(Number::isHex(lineBasedTokens[i]->at(2)))
                                        lcTmp = Number::unsignedHexToDecimal(lineBasedTokens[i]->at(2));
                                    else
                                    {
                                        cout << "[Line " << (i+1) << "] Invalid value : " << lineBasedTokens[i]->at(2) << ". A nature number is expected\n";
                                        exit(0);
                                    }
                                }
                                else
                                {
                                    cout << "[Line " << (i+1) << "] Missing value after START.\n";
                                    exit(0);
                                }
                            }
                            else  // END.
                            {
                                cout << "[Line " << (i+1) << "] Syntax error : a phrase " << directiveTmp.getValue() << " before END.\n";
                                exit(0);
                            }
                        }
                        else
                        {
                            cout << "[Line " << (i+1) << "] Invalid value : " << lineBasedTokens[i]->at(2) << " followed by " << directiveTmp.getName() << ".\n";
                            exit(0);
                        }
                    }
                    // Too less fields.
                    else if(lineBasedTokens[i]->size() == 2)
                    {
                        cout << "[Line " << (i+1) << "] No phrase after " << lineBasedTokens[i]->at(1) << ".\n";
                        exit(0);
                    }
                    // Too many fields.
                    else
                    {
                        cout << "[Line " << (i+1) << "] Invalid value : " << lineBasedTokens[i]->at(3) << ". Too many value.\n";
                        exit(0);
                    }
                }
                // Second token is invalid.
                else
                {
                    cout << "[Line " << (i+1) << "] Invalid phrase : " << lineBasedTokens[i]->at(1) << ". An instruction or directive required.\n";
                    exit(0);
                }
            }
        }
        else
            lc.push_back(-1);
    }
}

