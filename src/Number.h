#ifndef Number_h

    #define Number_h
    #include <string>
    #include <sstream>

    using std::string;
    using std::to_string;
    using std::stringstream;

    class Number
    {
    public:
        // Constructor.
        Number();

        // Static method.
        static int power(int, int);
        static bool isDigit(char);
        static bool isInteger(string);
        static bool isPositiveInteger(string);
        static bool isNature(string);
        static bool isLowerAlpha(char);
        static bool isCapitalAlpha(char);
        static bool isHexDigit(char);
        static bool isHex(string);
        static int toDigit(char);
        static int toInteger(string);
        static char toHexDigit(int);
        static int unsignedHexToDecimal(string);
        static string decimalToHex(int, int);
        static string asciiToHex(string);
        static int minLengthOfByte(int);
        static int minLengthOfWord(int);
        static string toUpperHex(string);
        static string toLowerHex(string);
    };

#endif

