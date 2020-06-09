#include "ObjectCode.h"

/******************************
 *  Public members in class.  *
 ******************************/

// Constructor.
ObjectCode::ObjectCode()
{
    clear();
}

/*******************************
 *  Private members in class.  *
 *******************************/

// Mutator.
bool ObjectCode::setName(const string name)
{
    if(name.length() <= 6)
    {
        this->name = name;

        // Append space(s) to satisfy 6 chars length.
        if(name.length() < 6)
        {
            for(int i=0, sizeI=6-name.length(); i<sizeI; ++i)
                this->name += " ";
        }

        return true;
    }
    else
    {
        this->name = name.substr(0, 6);
        return false;
    }
}

bool ObjectCode::setBaseAddress(int baseAddress)
{
    if(baseAddress >= 0)
    {
        this->baseAddress = baseAddress;
        return true;
    }
    else
        return false;
}

bool ObjectCode::setLength(int length)
{
    if(length > 0)
    {
        this->length = length;
        return true;
    }
    else
        return false;
}

bool ObjectCode::setStartAddress(int startAddress)
{
    if(startAddress >= 0 && startAddress >= baseAddress)
    {
        this->startAddress = startAddress;
        return true;
    }
    else
        return false;
}

// Methods.
void ObjectCode::clear()
{
    name = "";
    baseAddress = 0;
    length = 0;
    startAddress = 0;
}

