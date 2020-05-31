#include "Directive.h"

/******************************
 *  Public members in class.  *
 ******************************/

Directive::Directive()
{
    clear();
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
     *********************************************************/

    if(isDirective(name))
    {
        if(name == "START" || name == "END")
        {
            if(Number::isInteger(value) && *Number::toInteger(value) >= 0)
            {
                this->value = *Number::toInteger(value);
                return true;
            }
            else
                return false;
        }
        else
        {
            if(Number::isInteger(value) && *Number::toInteger(value) > 0)
            {
                if(name == "BYTE")
                {
                    if(value[0] == 'C')
                    {
                        if(value[1] == '\'' && value[value.length()-1] == '\'')
                            value = value.substr(2, value.length()-3);
                        else
                            return false;

                        this->value = *Number::unsignedHexToDecimal(*Number::asciiToHex(value));
                    }
                    else if(value[0] == 'X')
                    {
                        if(value[1] == '\'' && value[value.length()-1] == '\'')
                            value = value.substr(2, value.length()-3);
                        else
                            return false;

                        this->value = *Number::unsignedHexToDecimal(value);
                    }
                    else if(Number::isInteger(value))
                        this->value = *Number::toInteger(value);
                    else
                        return false;
                }
                else if(name == "WORD")
                    this->value = *Number::toInteger(value);
                else  // RESB, RESW.
                    this->value = *Number::toInteger(value);

                return true;
            }
            else
                return false;
        }
    }
    else
        return false;
}

Directive::Directive(string name, string value)
{
    setName(name);
    setValue(value);
}

void Directive::clear()
{
    name = "";
    value = 0;
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

