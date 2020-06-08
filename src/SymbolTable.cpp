#include "SymbolTable.h"

/******************************
 *  Public members in class.  *
 ******************************/

SymbolTable::SymbolTable()
{
    clear();
}

string SymbolTable::getAddress(string name) const
{
    int index = getNameIndex(name);

    if(index != -1)
        return address[index];
    else
        return "";
}

int SymbolTable::getReferenceSize(string name) const
{
    int index = getNameIndex(name);

    if(index != -1)
        return reference[index]->size();
    else
        return -1;
}

string SymbolTable::getReference(string name, int index) const
{
    int nameIndex = getNameIndex(name);

    if(nameIndex != -1)
    {
        if(index >= 0 && index < reference[nameIndex]->size())
            return reference[nameIndex]->at(index);
        else
            return "";
    }
    else
        return "";
}

bool SymbolTable::addSymbol(string name)
{
    if(isSymbolExists(name))
        return false;
    else
    {
        this->name.push_back(name);
        address.push_back("");
        reference.push_back(new vector<string>);
        reference[reference.size()-1]->clear();

        return true;
    }
}

bool SymbolTable::removeSymbol(string name)
{
    int index = getNameIndex(name);

    if(index != -1)
    {
        this->name.erase(this->name.begin() + index);
        address.erase(address.begin() + index);
        delete reference[index];
        reference.erase(reference.begin() + index);

        return true;
    }
    else
        return false;
}

bool SymbolTable::setAddress(string name, string address)
{
    int index = getNameIndex(name);

    if(index != -1)
    {
        this->address[index] = address;
        return true;
    }
    else
        return false;
}

bool SymbolTable::addReference(string name, string reference)
{
    int nameIndex = getNameIndex(name);

    if(nameIndex != -1)
    {
        // Check duplication.
        for(int i=0, sizeI=this->reference[nameIndex]->size(); i<sizeI; ++i)
        {
            if(this->reference[nameIndex]->at(i) == reference)
                return false;
        }

        this->reference[nameIndex]->push_back(reference);
        return true;
    }
    else
        return false;
}

bool SymbolTable::removeReference(string name, string reference)
{
    int nameIndex = getNameIndex(name);

    if(nameIndex != -1)
    {
        for(int i=0, sizeI=this->reference[nameIndex]->size(); i<sizeI; ++i)
        {
            if(this->reference[nameIndex]->at(i) == reference)
            {
                this->reference[nameIndex]->erase(this->reference[nameIndex]->begin() + i);

                // No reference remaining. Remove symbol.
                if(i == 0 && this->reference[nameIndex]->size() == 0)
                    removeSymbol(name);

                return true;
            }
        }

        return false;
    }
    else
        return false;
}

void SymbolTable::clear()
{
    for(int i=0, sizeI=name.size(); i<sizeI; ++i)
        removeSymbol(name[i]);
}

bool SymbolTable::isSymbolExists(string name) const
{
    for(int i=0, sizeI=this->name.size(); i<sizeI; ++i)
    {
        if(name == this->name[i])
            return true;
    }

    return false;
}

int SymbolTable::clearSymbolWithNoReference()
{
    int count = 0;

    for(int i=0, sizeI=name.size(); i<sizeI; ++i)
    {
        if(reference[i]->size() == 0)
        {
            removeSymbol(name[i]);
            ++count;
        }
    }

    return count;
}

string SymbolTable::getIndexName(int index) const
{
    if(index >=0 && index < name.size())
        return name[index];
    else
        return "";
}



/*******************************
 *  Private members in class.  *
 *******************************/

int SymbolTable::getNameIndex(string name) const
{
    for(int i=0, sizeI=this->name.size(); i<sizeI; ++i)
    {
        if(this->name[i] == name)
            return i;
    }

    return -1;
}

