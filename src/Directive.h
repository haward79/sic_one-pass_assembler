#ifndef Directive_h

    #define Directive_h
    #include <string>
    #include "Number.h"

    using std::string;

    typedef enum {null, ascii, dec, hex, symbol} DirectiveType;

    class Directive
    {
    public:
        // Constructor.
        Directive();
        Directive(string, string);

        // Accessor.
        string getName() const { return name; }
        string getValue() const { return value; }
        DirectiveType getType() const { return type; }

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
        string value;
        DirectiveType type;
    };

#endif

