#ifndef OBJECT_CODE_H

    #define OBJECT_CODE_H
    #include <string>

    using std::string;

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

        // Mutator.
        bool setName(const string);
        bool setBaseAddress(int);
        bool setLength(int);
        bool setStartAddress(int);

        // Method.
        void clear();

    private:
        // Variables.
        string name;
        int baseAddress;
        int length;
        int startAddress;
    };

#endif

