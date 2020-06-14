#include "Number.h"

/******************************
 *  Public members in class.  *
 ******************************/

Number::Number()
{}

int Number::power(int x, int y)
{
    int ans = 1;

    for(int i=0; i<y; ++i)
        ans *= x;

    return ans;
}

bool Number::isDigit(char ch)
{
    return (ch >= '0' && ch <= '9');
}

bool Number::isInteger(string str)
{
    if(str[0] == '+' || str[0] == '-')
        str = str.substr(1, str.length()-1);

    for(int i=0, sizeI=str.length(); i<sizeI; ++i)
    {
        if(!isDigit(str[i]))
            return false;
    }

    return true;
}

bool Number::isPositiveInteger(string str)
{
    if(isInteger(str) && toInteger(str) > 0)
        return true;
    else
        return false;
}

bool Number::isNature(string str)
{
    if(isInteger(str) && toInteger(str) >= 0)
        return true;
    else
        return false;
}

bool Number::isLowerAlpha(char ch)
{
    return (ch >= 'a' && ch <= 'z');
}

bool Number::isCapitalAlpha(char ch)
{
    return (ch >= 'A' && ch <= 'Z');
}

bool Number::isHexDigit(char ch)
{
    if
    (
        (ch >= '0' && ch <= '9') ||
        (ch >= 'A' && ch <= 'F')
    )
        return true;
    else
        return false;
}

bool Number::isHex(string str)
{
    for(int i=0, sizeI=str.length(); i<sizeI; ++i)
    {
        if(!isHexDigit(str[i]))
            return false;
    }

    return true;
}

int Number::toDigit(char ch)
{
    if(isDigit(ch))
        return (ch - '0');
    else
        return 0;
}

int Number::toInteger(string str)
{
    if(isInteger(str))
    {
        int number = 0;
        bool isNegative = false;

        // Truncate sign.
        if(str[0] == '+' || str[0] == '-')
        {
            if(str[0] == '-')
                isNegative = true;

            str = str.substr(1, str.length()-1);
        }

        // Convert number type from string to integer.
        for(int i=0, sizeI=str.length(); i<sizeI; ++i)
        {
            number *= 10;
            number += str[i] - '0';
        }

        // Return number type with sign.
        if(isNegative)
            return -number;
        else
            return number;
    }
    else
        return 0;
}

char Number::toHexDigit(int number)
{
    if(number == 0)
        return '0';
    else if(number == 1)
        return '1';
    else if(number == 2)
        return '2';
    else if(number == 3)
        return '3';
    else if(number == 4)
        return '4';
    else if(number == 5)
        return '5';
    else if(number == 6)
        return '6';
    else if(number == 7)
        return '7';
    else if(number == 8)
        return '8';
    else if(number == 9)
        return '9';
    else if(number == 10)
        return 'A';
    else if(number == 11)
        return 'B';
    else if(number == 12)
        return 'C';
    else if(number == 13)
        return 'D';
    else if(number == 14)
        return 'E';
    else if(number == 15)
        return 'F';
    else
        return '\0';
}

int Number::unsignedHexToDecimal(string str)
{
    int number = 0;
    
    // Check each digit.
    for(int i=0, sizeI=str.length(); i<sizeI; ++i)
    {
        number *= 16;

        if(isDigit(str[i]))
            number += str[i] - '0';
        else if(isCapitalAlpha(str[i]))
            number += str[i] - 'A' + 10;
        else
            return 0;
    }

    return number;
}

string Number::decimalToHex(int dec, int digit)
{
    stringstream ss;
    string str;
    ss << std::hex << dec;
    str = toUpperHex(ss.str());

    if(str.length() == digit)
        return str;
    else if(str.length() > digit)
        return str.substr(str.length()-digit, digit);
    else
    {
        for(int i=0, sizeI=digit-str.length(); i<sizeI; ++i)
        {
            if(dec >= 0)
                str = "0" + str;
            else
                str = "F" + str;
        }

        return str;
    }
}

string Number::asciiToHex(string str)
{
    string hex = "";

    for(int i=0, sizeI=str.length(); i<sizeI; ++i)
    {
        if
        (
            (str[i] >= '0' && str[i] <= '9') ||
            (str[i] >= 'A' && str[i] <= 'Z') ||
            (str[i] >= 'a' && str[i] <= 'z')
        )
        {
            hex += decimalToHex(int(str[i]), 2);
        }
        else
            return "";
    }

    return hex;
}

int Number::minLengthOfByte(int number)
{
    int count = 1;
    int tmp = 0;

    while(true)
    {
        tmp = power(2, count*8 - 1);

        // Check overflow.
        if(tmp < 0)
            return 0;

        if(number >= 0)
        {
            if(tmp - 1 >= number)
                return count;
        }
        else
        {
            if(tmp >= -number)
                return count;
        }
    }
}

int Number::minLengthOfWord(int number)
{
    int count = 1;
    int tmp = 0;

    while(true)
    {
        tmp = power(2, count*24 - 1);

        // Check overflow.
        if(tmp < 0)
            return 0;

        if(number >= 0)
        {
            if(tmp - 1 >= number)
                return count;
        }
        else
        {
            if(tmp >= -number)
                return count;
        }
    }
}

string Number::toUpperHex(string hex)
{
    for(int i=0, sizeI=hex.length(); i<sizeI; ++i)
    {
        if(hex[i] >= 'a' && hex[i] <= 'z')
            hex[i] -= 32;
    }

    if(isHex(hex))
        return hex;
    else
        return "";
}

string Number::toLowerHex(string hex)
{
    if(toUpperHex(hex) == "")
        return "";

    for(int i=0, sizeI=hex.length(); i<sizeI; ++i)
    {
        if(hex[i] >= 'A' && hex[i] <= 'Z')
            hex[i] += 32;
    }

    return hex;
}

