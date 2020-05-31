#ifndef SymbolTable_h

    #define SymbolTable_h
    #include <string>
    #include <vector>

    using std::string;
    using std::vector;

    class SymbolTable
    {
    public:
        // Constructor.
        SymbolTable();

        // Accessor.
        int getAddress(string) const;
        vector<int>* getReferences(string name) const;

        // Mutator.
        bool addSymbol(string);
        bool removeSymbol(string);
        bool setAddress(string, int);
        bool addReference(string, int);
        bool removeReference(string, int);

        // Method.
        void clear();
        bool isNameExists(string) const;
        int clearSymbolWithEmptyReference();

    private:
        // Variable.
        vector<string> name;
        vector<int> address;
        vector<vector<int>*> reference;

        // Method.
        int getNameIndex(string) const;
    };

#endif

