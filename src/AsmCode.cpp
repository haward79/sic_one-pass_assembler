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
        case '\n':
        case '\t':
            return true;

        // ch is NOT a seperator.
        default:
            return false;
    }
}



/******************************
 *  Public members in class.  *
 ******************************/

// Constructure.
AsmCode::AsmCode()
{
    sourceCode = "";
    tokens.clear();
}

AsmCode::AsmCode(const string& sourceCode)
{
    this->sourceCode = sourceCode;
    splitTokens();
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

void AsmCode::clearSourceCode()
{
    sourceCode = "";
    tokens.clear();
}

void AsmCode::setSourceCode(const string& src)
{
    sourceCode = src;
    splitTokens();
}



/*******************************
 *  Private members in class.  *
 *******************************/

// Methods.
void AsmCode::splitTokens()
{
    int startFlag = 0;  // Point to start index of the token.
    int endFlag = 0;  // Point to next char to deal.
    int length = sourceCode.length();
    string token = "";

    // Fetch all tokens.
    while(startFlag < length)
    {
        // Truncate seperator.
        while(isSeperator(sourceCode[startFlag]))
        {
            ++startFlag;

            // Reach EOF.
            if(startFlag >= length)
                break;
        }

        // Extract a token.
        if(startFlag < length)
        {
            endFlag = startFlag + 1;

            // Move endFlag backward until seperator encountered.
            while(!isSeperator(sourceCode[endFlag]))
            {
                ++endFlag;

                // Reach EOF.
                if(endFlag >= length)
                    break;
            }

            // Store the token.
            tokens.push_back(sourceCode.substr(startFlag, endFlag - startFlag));

            // Print this new token.
            cout << "[" << (tokens.size() - 1) << "] " << getToken(-1) << "\n";

            // Move start flag to the start of new token.
            startFlag = endFlag;
        }
    }
}

