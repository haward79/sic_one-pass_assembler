#include "SymbolTable.h"

/******************************
 *  Public members in class.  *
 ******************************/

SymbolTable::SymbolTable()
{
    clear();
}

int SymbolTable::getAddress(string name) const
{
    int index = getNameIndex(name);

    if(index != -1)
        return address[index];
    else
        return -1;
}

vector<int>* SymbolTable::getReferences(string name) const
{
    int index = getNameIndex(name);

    if(index != -1)
        return new vector<int>(*reference[index]);
    else
        return nullptr;
}

bool SymbolTable::addSymbol(string name)
{
    if(isNameExists(name))
        return false;
    else
    {
        this->name.push_back(name);
        address.push_back(-1);
        reference.push_back(new vector<int>);
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

bool SymbolTable::setAddress(string name, int address)
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

bool SymbolTable::addReference(string name, int reference)
{
    if(isNameExists(name))
    {
        this->reference[getNameIndex(name)]->push_back(reference);
        return true;
    }
    else
        return false;
}

bool SymbolTable::removeReference(string name, int reference)
{
    int index = getNameIndex(name);

    if(index != -1)
    {
        for(int i=0, sizeI=this->reference[index]->size(); i<sizeI; ++i)
        {
            if(this->reference[index]->at(i) == reference)
            {
                this->reference[index]->erase(this->reference[index]->begin() + i);
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
    name.clear();
    address.clear();
    reference.clear();
}

bool SymbolTable::isNameExists(string name) const
{
    for(int i=0, sizeI=this->name.size(); i<sizeI; ++i)
    {
        if(name == this->name[i])
            return true;
    }

    return false;
}

int SymbolTable::clearSymbolWithEmptyReference()
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

