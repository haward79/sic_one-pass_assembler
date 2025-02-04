#ifndef AsmCode_h

    #define AsmCode_h
    #include <stdio.h>
    #include <iostream>
    #include <string>
    #include <vector>
    #include <fstream>
    #include "SymbolTable.h"
    #include "Directive.h"
    #include "ObjectCode.h"

    using std::cout;
    using std::string;
    using std::vector;
    using std::ifstream;
    using std::ofstream;

    class AsmCode
    {
    public:
        // Constructure.
        AsmCode();
        
        // Destructor.
        ~AsmCode();

        // Method.
        const string getFileName() const { return fileName; }
        const vector<string> getSourceCode() const { return sourceCode; }
        const int getTokenLength() const { return tokens.size(); }
        const vector<string> getTokens() const { return tokens; }
        const string getToken(int) const;
        const int getLineBasedTokenLength() const { return lineBasedTokens.size(); }
        const int getLineBasedTokenLineLength(int) const;
        const string getLineBasedToken(int, int) const;
        const int getLc(int) const;
        const bool getIsWindowsFormat() const { return isWindowsFormat; }
        void clearSourceCode();
        void setSourceCode(const vector<string>&);
        bool read(const string&);
        bool writeLc() const;
        bool writeSymbolTable() const;
        bool writeObjectCode() const;

    private:
        // Variable.
        string fileName;
        vector<string> sourceCode;
        vector<vector<string>*> lineBasedTokens;
        vector<string> tokens;
        vector<int> lc;
        SymbolTable symbols;
        bool isWindowsFormat;
        ObjectCode objCode;

        // Method.
        void splitTokens();
        void generateLc();
        bool isSeperator(char);
        vector<string>* explode(const string&);
        string getOpcodeStr(string);
        bool splitTextRecord(int, int, int);
        int getTypeCode(int);
    };

#endif

