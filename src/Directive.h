#ifndef Directive_h

    #define Directive_h
    #include <string>
    #include "Number.h"

    using std::string;

    class Directive
    {
    public:
        // Constructor.
        Directive();
        Directive(string, string);

        // Accessor.
        string getName() const { return name; }
        int getValue() const { return value; }

        // Mutator.
        bool setName(string);
        bool setValue(string);

        // Method.
        void clear();

        // Static method.
        static bool isDirective(string);

    private:
        // Variable.
        string name;
        int value;
    };

#endif

