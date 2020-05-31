#ifndef Number_h

    #define Number_h
    #include <string>

    using std::string;
    using std::to_string;

    class Number
    {
    public:
        // Constructor.
        Number();

        // Static method.
        static int power(int, int);
        static bool isDigit(char);
        static bool isInteger(string);
        static bool isLowerAlpha(char);
        static bool isCapitalAlpha(char);
        static int* toDigit(char);
        static int* toInteger(string);
        static char* toHexDigit(int);
        static int* unsignedHexToDecimal(string);
        static string* decimalToHex(int, int);
        static string* asciiToHex(string);
        static int* minNumberOfWord(int);
    };

#endif

