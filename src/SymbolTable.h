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
        int getSize() const { return name.size(); }
        string getAddress(string) const;
        int getReferenceSize(string) const;
        string getReference(string, int) const;

        // Mutator.
        bool addSymbol(string);
        bool removeSymbol(string);
        bool setAddress(string, string);
        bool addReference(string, string);
        bool removeReference(string, string);

        // Method.
        void clear();
        bool isSymbolExists(string) const;
        int clearSymbolWithNoReference();

    private:
        // Variable.
        vector<string> name;
        vector<string> address;
        vector<vector<string>*> reference;

        // Method.
        int getNameIndex(string) const;
    };

#endif

