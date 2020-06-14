#include "AsmCode.h"

/******************************
 *  Public members in class.  *
 ******************************/

// Constructure.
AsmCode::AsmCode()
{
    fileName = "";
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
    symbols.clear();
    isWindowsFormat = false;
    objCode.clear();
}

void AsmCode::setSourceCode(const vector<string>& src)
{
    sourceCode = src;
    splitTokens();
}

bool AsmCode::read(const string& filePath)
{
    string tmp = "";
    ifstream& fin = *(new ifstream());

    // Open source code file.
    fin.open(filePath + ".asm");

    // Failed.
    if(fin.fail())
    {
        cout << "Fatal error : failed to open file \"" << filePath << ".asm\".\n";
        return false;
    }

    // Set filename.
    fileName = filePath;

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

    return true;
}

bool AsmCode::writeLc() const
{
    ofstream fout;

    // Open output file stream.
    fout.open(fileName + ".lst");

    // Failure.
    if(fout.fail())
        return false;
    // Success.
    else
    {
        // Write title.
        fout << "Loc.\tSource statement\n";
        fout << "=====\t==================================\n";

        // Write content.
        for(int i=0, sizeI=getLineBasedTokenLength(); i<sizeI; ++i)
        {
            if(getLc(i) >= 0)
                fout << Number::decimalToHex(getLc(i), 5).c_str() << "\t" << getSourceCode()[i].c_str() << "\n";
            else
            {
                if(getSourceCode()[i][0] == '.')
                    fout << "\t" << getSourceCode()[i].c_str() << "\n";
                else
                    fout << "     \t" << getSourceCode()[i].c_str() << "\n";
            }
        }

        // Close output file stream.
        fout.close();
    }
}

bool AsmCode::writeSymbolTable() const
{
    ofstream fout;
    string symbolName = "";

    // Open output file stream.
    fout.open(fileName + ".stb");

    // Failure.
    if(fout.fail())
        return false;
    // Success.
    else
    {
        // Write title.
        fout << "Symbol\tValue\n";
        fout << "======\t======\n";

        // Write content.
        for(int i=0, sizeI=symbols.getSize(); i<sizeI; ++i)
        {
            symbolName = symbols.getIndexName(i);

            fout << symbolName << "\t" << Number::decimalToHex(Number::toInteger(symbols.getAddress(symbolName)), 5) << "\n";
        }

        // Close output file stream.
        fout.close();
    }
}

bool AsmCode::writeObjectCode() const
{
    ofstream fout;

    fout.open(fileName + ".obj");

    if(fout.fail())
        return false;
    else
    {
        // Write head record.
        fout << "H" << objCode.getName() << Number::decimalToHex(objCode.getBaseAddress(), 6) << Number::decimalToHex(objCode.getLength(), 6) << "\n";
        
        // Write text record.
        for(int i=0, sizeI=objCode.getTextRecordsLength(); i<sizeI; ++i)
        {
            if(objCode.getTextRecord(i)->getLength() == 0)
                continue;

            fout << "T"
                 << Number::decimalToHex(objCode.getTextRecord(i)->getStartAddress(), 6)
                 << Number::decimalToHex(objCode.getTextRecord(i)->getLength(), 2)
                 << objCode.getTextRecord(i)->getRecord()
                 << "\n";
        }

        // Write end record.
        fout << "E" << Number::decimalToHex(objCode.getStartAddress(), 6) << "\n";

        fout.close();
    }
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
    string opcode = "", address = "";
    bool directive = false;
    Directive directiveTmp;

    for(int i=0, sizeI=getLineBasedTokenLength(); i<sizeI; ++i)
    {
        if(i == 10)
        {
            cout << "";
        }

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

                // Instruction is RSUB. (0 operand)
                if(lineBasedTokens[i]->at(0) == "RSUB")
                    objCode.appendPartialToLastRecord(opcode + "0000");
                // Instruction is NOT RSUB (2 operands in total for each instruction).
                else
                {
                    // Invalid number of operands.
                    if(lineBasedTokens[i]->size() > 3)
                    {
                        cout << "[Line " << (i+1) << "] Invalid number of operand(s) after instruction : " << lineBasedTokens[i]->at(0) << ".\n";
                        exit(0);
                    }
                    // 1 operands. 2 operands (indexed).
                    else
                    {
                        // Handle operands as a symbol : symbol exists.
                        if(symbols.isSymbolExists(lineBasedTokens[i]->at(1)))
                        {
                            // Get address of the symbol.
                            address = symbols.getAddress(lineBasedTokens[i]->at(1));

                            // Symbol not defined.  Stuff zeros and add current lc to reference list.
                            if(address == "")
                            {
                                // Not indexed.
                                if(lineBasedTokens[i]->size() == 2)
                                    objCode.appendPartialToLastRecord(opcode + "0000");
                                // Indexed.
                                else
                                {
                                    if(lineBasedTokens[i]->at(2) == "X")
                                        objCode.appendPartialToLastRecord(opcode + "8000");
                                    else
                                    {
                                        cout << "[Line " << (i+1) << "] Invalid offset : " << lineBasedTokens[i]->at(2) << ". X is expected.\n";
                                        exit(0);
                                    }
                                }

                                symbols.addReference(lineBasedTokens[i]->at(1), to_string(lc[lc.size()]));
                            }
                            // Symbol defined.
                            else
                            {
                                // Not indexed.
                                if(lineBasedTokens[i]->size() == 2)
                                    objCode.appendPartialToLastRecord(opcode + Number::decimalToHex(Number::toInteger(address), 4));
                                // Indexed.
                                else
                                {
                                    if(lineBasedTokens[i]->at(2) == "X")
                                        objCode.appendPartialToLastRecord(opcode + Number::decimalToHex(Number::toInteger(address)+32768, 4));
                                    else
                                    {
                                        cout << "[Line " << (i+1) << "] Invalid offset : " << lineBasedTokens[i]->at(2) << ". X is expected.\n";
                                        exit(0);
                                    }
                                }
                            }
                        }
                        // Handle operands as a symbol : symbol doesn't  exist.
                        else
                        {
                            // Add this symbol to symbol table.
                            symbols.addSymbol(lineBasedTokens[i]->at(1));

                            // Stuff zeros and add current lc to reference list.
                            objCode.appendPartialToLastRecord(opcode + "0000");
                            symbols.addReference(lineBasedTokens[i]->at(1), to_string(lc[lc.size()]));
                        }
                    }
                }
            }
            // First token is a directive : END.
            else if(directive)
            {
                if(lineBasedTokens[i]->at(0) == "END")
                {
                    if(lineBasedTokens[i]->size() == 2)
                    {
                        objCode.setLength(lcTmp - objCode.getBaseAddress());

                        lcTmp = -999999999;
                        lc.push_back(lcTmp);
                        
                        // Handle lineBasedTokens[i]->at(1) as value or symbol.
                        if(Number::isNature(lineBasedTokens[i]->at(1)))
                            objCode.setStartAddress(Number::toInteger(lineBasedTokens[i]->at(1)));
                        else if(symbols.getAddress(lineBasedTokens[i]->at(1)) != "")
                            objCode.setStartAddress(Number::toInteger(symbols.getAddress(lineBasedTokens[i]->at(1))));
                        else
                        {
                            cout << "[Line " << (i+1) << "] Invalid phrase : " << lineBasedTokens[i]->at(1) << ". Not a value or symbol.\n";
                            exit(0);
                        }
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
                if(symbols.getAddress(lineBasedTokens[i]->at(0)) != "")
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
                    // Instruction is RSUB. (0 operand)
                    if(lineBasedTokens[i]->at(1) == "RSUB")
                        objCode.appendPartialToLastRecord(opcode + "0000");
                    // Instruction is NOT RSUB (2 operands in total for each instruction).
                    else
                    {
                        // Invalid number of operands.
                        if(lineBasedTokens[i]->size() > 4)
                        {
                            cout << "[Line " << (i+1) << "] Invalid number of operand(s) after instruction : " << lineBasedTokens[i]->at(1) << ".\n";
                            exit(0);
                        }
                        // 1 operands. 2 operands (indexed).
                        else
                        {
                            // Handle operands as a symbol : symbol exists.
                            if(symbols.isSymbolExists(lineBasedTokens[i]->at(2)))
                            {
                                // Get address of the symbol.
                                address = symbols.getAddress(lineBasedTokens[i]->at(2));

                                // Symbol not defined.  Stuff zeros and add current lc to reference list.
                                if(address == "")
                                {
                                    // Not indexed.
                                    if(lineBasedTokens[i]->size() == 3)
                                        objCode.appendPartialToLastRecord(opcode + "0000");
                                    // Indexed.
                                    else
                                    {
                                        if(lineBasedTokens[i]->at(3) == "X")
                                            objCode.appendPartialToLastRecord(opcode + "8000");
                                        else
                                        {
                                            cout << "[Line " << (i+1) << "] Invalid offset : " << lineBasedTokens[i]->at(3) << ". X is expected.\n";
                                            exit(0);
                                        }
                                    }

                                    symbols.addReference(lineBasedTokens[i]->at(2), to_string(lc[lc.size()]));
                                }
                                // Symbol defined.
                                else
                                {
                                    // Not indexed.
                                    if(lineBasedTokens[i]->size() == 3)
                                        objCode.appendPartialToLastRecord(opcode + Number::decimalToHex(Number::toInteger(address), 4));
                                    // Indexed.
                                    else
                                    {
                                        if(lineBasedTokens[i]->at(3) == "X")
                                            objCode.appendPartialToLastRecord(opcode + Number::decimalToHex(Number::toInteger(address)+32768, 4));
                                        else
                                        {
                                            cout << "[Line " << (i+1) << "] Invalid offset : " << lineBasedTokens[i]->at(3) << ". X is expected.\n";
                                            exit(0);
                                        }
                                    }
                                }
                            }
                            // Handle operands as a symbol : symbol doesn't  exist.
                            else
                            {
                                // Add this symbol to symbol table.
                                symbols.addSymbol(lineBasedTokens[i]->at(2));

                                // Stuff zeros and add current lc to reference list.
                                objCode.appendPartialToLastRecord(opcode + "0000");
                                symbols.addReference(lineBasedTokens[i]->at(2), to_string(lc[lc.size()]));
                            }
                        }
                    }

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
                                {
                                    lcTmp += Number::minLengthOfByte(Number::toInteger(directiveTmp.getValue())) * 3;
                                    objCode.appendPartialToLastRecord(Number::decimalToHex(Number::toInteger(directiveTmp.getValue()), 6));
                                }
                                else if(directiveTmp.getType() == DirectiveType::hex)
                                {
                                    lcTmp += (directiveTmp.getValue().length() + 1) / 2;
                                    objCode.appendPartialToLastRecord(Number::decimalToHex(Number::unsignedHexToDecimal(directiveTmp.getValue()), 6));
                                }
                                else  // Ascii.
                                {
                                    lcTmp += directiveTmp.getValue().length();
                                    objCode.appendPartialToLastRecord(Number::asciiToHex(directiveTmp.getValue()));
                                }
                            }
                            else if(directiveTmp.getName() == "WORD")
                            {
                                lcTmp += Number::minLengthOfWord(Number::toInteger(directiveTmp.getValue())) * 3;
                                objCode.appendPartialToLastRecord(Number::decimalToHex(Number::toInteger(directiveTmp.getValue()), 6));
                            }
                            else if(directiveTmp.getName() == "RESB")
                            {
                                splitTextRecord(i-1, i, lcTmp);
                                lcTmp += Number::toInteger(directiveTmp.getValue());
                                splitTextRecord(i, i+1, lcTmp);
                            }
                            else if(directiveTmp.getName() == "RESW")
                            {
                                splitTextRecord(i-1, i, lcTmp);
                                lcTmp += Number::toInteger(directiveTmp.getValue()) * 3;
                                splitTextRecord(i, i+1, lcTmp);
                            }
                            else if(directiveTmp.getName() == "START")
                            {
                                if(lineBasedTokens[i]->size() == 3)
                                {
                                    if(!objCode.setName(lineBasedTokens[i]->at(0)))
                                        cout << "[Line " << (i+1) << "] Too long name of the program : " << lineBasedTokens[i]->at(2) << "\n";

                                    if(Number::isHex(lineBasedTokens[i]->at(2)))
                                    {
                                        lcTmp = Number::unsignedHexToDecimal(lineBasedTokens[i]->at(2));
                                        symbols.setAddress(lineBasedTokens[i]->at(0), to_string(lcTmp));
                                        objCode.setBaseAddress(lcTmp);
                                        
                                        objCode.addRecord();
                                        objCode.getTextRecord(-1)->setStartAddress(lcTmp);
                                    }
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

bool AsmCode::isSeperator(char ch)
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

vector<string>* AsmCode::explode(const string& str)
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

string AsmCode::getOpcodeStr(string mnemonic)
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

bool AsmCode::splitTextRecord(int index1, int index2, int lc)
{
    while(index2 >= 0 && index2 < lineBasedTokens.size() && lineBasedTokens[index2]->size() == 1 && lineBasedTokens[index2]->at(0)[0] == '.')
        ++index2;

    int difference = getTypeCode(index1) - getTypeCode(index2);

    if(difference == 2 || difference == -2)
    {
        objCode.addRecord();
        objCode.getTextRecord(-1)->setStartAddress(lc);
        return true;
    }
    else
        return false;
}

int AsmCode::getTypeCode(int index)
{
    /********************************
     *   0 : Error                  *
     *  -1 : RESB, RESW             *
     *   1 : BYTE, WORD, mnemonics  *
     ********************************/

    if(index >= 0 && index < lineBasedTokens.size())
    {
        if(lineBasedTokens[index]->size() == 1 && lineBasedTokens[index]->at(0) == "RSUB")
            return 1;
        else if(lineBasedTokens[index]->size() == 2)
        {
            if(lineBasedTokens[index]->at(1) == "RSUB")
                return 1;
            else if(getOpcodeStr(lineBasedTokens[index]->at(1)) != "")
                return 1;
            else
                return 0;
        }
        else if(lineBasedTokens[index]->size() == 3)
        {
            if(getOpcodeStr(lineBasedTokens[index]->at(1)) != "")
                return 1;
            else if(lineBasedTokens[index]->at(1) == "BYTE" || lineBasedTokens[index]->at(1) == "WORD")
                return 1;
            else if(lineBasedTokens[index]->at(1) == "RESB" || lineBasedTokens[index]->at(1) == "RESW")
                return -1;
            else
                return 0;
        }
        else if(lineBasedTokens[index]->size() == 4)
            return 1;
        else
            return 0;
    }
    else
        return 0;
}

