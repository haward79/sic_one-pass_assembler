#include "Directive.h"

/******************************
 *  Public members in class.  *
 ******************************/

Directive::Directive()
{
    clear();
}

Directive::Directive(string name, string value)
{
    clear();
    this->name = setName(name);
    this->value = setValue(value);
}

bool Directive::setName(string name)
{
    if(isDirective(name))
    {
        this->name = name;
        return true;
    }
    else
        return false;
}

bool Directive::setValue(string value)
{
    /*********************************************************
     *  Set value for the specific directive named as name.  *
     *  Validation is applied to value.                      *
     *  Type is set according to the value.                  *
     *********************************************************/

    if(isDirective(name))
    {
        if(name == "START" || name == "END")
        {
            // Value is a hex.
            if(value.length() > 3 && value[0] == 'X' && value[1] == '\'' && value[value.length()-1] == '\'')
            {
                value = value.substr(2, value.length()-3);
                
                // Valid hex.
                if(Number::isHex(value))
                {
                    this->value = value;
                    type = hex;
                    return true;
                }
                // Invalid hex.
                else
                    return false;
            }
            // Value is a dec.
            else if(Number::isNature(value))
            {
                this->value = value;
                type = dec;
                return true;
            }
            // START : invalid value. END : symbol.
            else
            {
                // START : invalid value.
                if(name == "START")
                    return false;
                // END : symbol.
                else
                {
                    this->value = value;
                    type = symbol;
                    return true;
                }
            }
        }
        // BYTE, WORD, RESB, RESW.
        else
        {
            if(name == "BYTE")
            {
                // Value is a hex.
                if(value.length() > 3 && value[0] == 'X' && value[1] == '\'' && value[value.length()-1] == '\'')
                {
                    value = value.substr(2, value.length()-3);
                    
                    // Valid hex.
                    if(Number::isHex(value))
                    {
                        this->value = value;
                        type = hex;
                        return true;
                    }
                    // Invalid hex.
                    else
                        return false;
                }
                // Value is a dec.
                else if(Number::isInteger(value))
                {
                    this->value = value;
                    type = dec;
                    return true;
                }
                // Value is a ascii.
                else if(value.length() > 3 && value[0] == 'C' && value[1] == '\'' && value[value.length()-1] == '\'')
                {
                    value = value.substr(2, value.length()-3);

                    this->value = value;
                    type = ascii;
                    return true;
                }
                // Invalid value.
                else
                    return false;
            }
            else if(name == "WORD")
            {
                if(Number::isInteger(value))
                {
                    this->value = value;
                    type = dec;
                    return true;
                }
                else
                    return false;
            }
            // RESB, RESW.
            else
            {
                if(Number::isPositiveInteger(value))
                {
                    this->value = value;
                    type = dec;
                    return true;
                }
                else
                    return false;
            }
        }
    }
    else
        return false;
}

void Directive::clear()
{
    name = "";
    value = "";
    type = null;
}

bool Directive::isDirective(string name)
{
    /***********************************************************
     *  Return boolean indicates whether name is a directive.  *
     *  Directive is case sensitive.                           *
     ***********************************************************/

    if(name == "START" || name == "END" || name == "BYTE" || name == "WORD" || name == "RESB" || name == "RESW")
        return true;
    else
        return false;
}

