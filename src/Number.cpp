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

bool Number::isLowerAlpha(char ch)
{
    return (ch >= 'a' && ch <= 'z');
}

bool Number::isCapitalAlpha(char ch)
{
    return (ch >= 'A' && ch <= 'Z');
}

int* Number::toDigit(char ch)
{
    if(isDigit(ch))
        return new int(ch - '0');
    else
        return nullptr;
}

int* Number::toInteger(string str)
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
        for(int i=str.length()-1; i>=0; --i)
        {
            number *= 10;
            number += str[i] - '0';
        }

        // Return number type with sign.
        if(isNegative)
            return new int(-number);
        else
            return new int(number);
    }
    else
        return nullptr;
}

char* Number::toHexDigit(int number)
{
    if(number == 0)
        return new char('0');
    else if(number == 1)
        return new char('1');
    else if(number == 2)
        return new char('2');
    else if(number == 3)
        return new char('3');
    else if(number == 4)
        return new char('4');
    else if(number == 5)
        return new char('5');
    else if(number == 6)
        return new char('6');
    else if(number == 7)
        return new char('7');
    else if(number == 8)
        return new char('8');
    else if(number == 9)
        return new char('9');
    else if(number == 10)
        return new char('A');
    else if(number == 11)
        return new char('B');
    else if(number == 12)
        return new char('C');
    else if(number == 13)
        return new char('D');
    else if(number == 14)
        return new char('E');
    else if(number == 15)
        return new char('F');
    else
        return nullptr;
}

int* Number::unsignedHexToDecimal(string str)
{
    int number = 0;
    
    // Check each digit.
    for(int i=str.length()-1; i>=0; --i)
    {
        number *= 16;

        if(isDigit(str[i]))
            number += str[i] - '0';
        else if(isCapitalAlpha(str[i]))
            number += str[i] - 'A' + 10;
        else
            return nullptr;
    }

    return new int(number);
}

string* Number::decimalToHex(int dec, int digit)
{
    int kMaxValue = power(2, digit-1) - 1;
    int kMinValue = -power(2, digit-1);
    int remainder = 0;
    string hex = "";

    if(dec >= kMinValue && dec <= kMaxValue)
    {
        if(dec >= 0)
        {
            while(dec > 0)
            {
                remainder = dec % 16;
                dec /= 16;
                hex = to_string(*toHexDigit(remainder)) + hex;
            }

            if(hex.length() != digit)
            {
                for(int i=0, sizeI=digit-hex.length(); i<sizeI; ++i)
                    hex = "0" + hex;
            }
        }
        else
        {
            hex = *decimalToHex(-dec, digit);

            // Undone.
        }

        return new string(hex);
    }
    else  // Overflow.
        return nullptr;
}

string* Number::asciiToHex(string str)
{
    string hex = "";

    for(int i=0, sizeI=str.length(); i<sizeI; ++i)
    {
        if
        (
            (str[i] >= '0' && str[i] <= '9') ||
            (str[i] >= 'A' && str[i] <= 'F')
        )
        {
            hex += *decimalToHex(int(str[i]), 2);
        }
        else
            return nullptr;
    }

    return new string(hex);
}

int* Number::minNumberOfWord(int number)
{
    int count = 1;

    while(true)
    {
        if(number >= 0)
        {
            if(power(2, count*24 - 1) - 1 >= number)
                return new int(count);
        }
        else
        {
            if(power(2, count*24 - 1) >= -number)
                return new int(count);
        }
    }
}

