#ifndef OBJECT_CODE_H

    #define OBJECT_CODE_H
    #include <string>
    #include <vector>

    using std::string;
    using std::vector;

    class TextRecord
    {
    public:
        // Constructor.
        TextRecord();

        // Accessor.
        int getStartAddress() const { return startAddress; }
        int getLength() const { return length; }
        const string getRecord() const { return record; }

        // Mutator.
        bool setStartAddress(int);
        void appendRecord(const string);

        // Method.
        void clear();

    private:
        // Variables.
        int startAddress;
        int length;
        string record;
    };

    class ObjectCode
    {
    public:
        // Constructor.
        ObjectCode();

        // Accessor.
        const string getName() const { return name; }
        int getBaseAddress() const { return baseAddress; }
        int getLength() const { return length; }
        int getStartAddress() const { return startAddress; }
        int getTextRecordsLength() const { return textRecords.size(); }
        TextRecord* getTextRecord(int) const;

        // Mutator.
        bool setName(const string);
        bool setBaseAddress(int);
        bool setLength(int);
        bool setStartAddress(int);
        bool appendPartialToRecord(const string, int);
        void appendPartialToLastRecord(const string);
        void addRecord();

        // Method.
        void clear();

    private:
        // Variables.
        string name;
        int baseAddress;
        int length;
        int startAddress;
        vector<TextRecord*> textRecords;
    };

#endif

