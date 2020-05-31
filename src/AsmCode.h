#ifndef AsmCode_h

    #define AsmCode_h
    #include <iostream>
    #include <string>
    #include <vector>

    using std::cout;
    using std::string;
    using std::vector;

    class AsmCode
    {
    public:
        // Constructure.
        AsmCode();
        AsmCode(const string&);

        // Method.
        const string getSourceCode() const { return sourceCode; }
        const int getTokenLength() const { return tokens.size(); }
        const vector<string> getTokens() const { return tokens; }
        const string getToken(int) const;
        void clearSourceCode();
        void setSourceCode(const string&);

    private:
        // Variable.
        string sourceCode;
        vector<string> tokens;

        // Method.
        void splitTokens();
    };

#endif

