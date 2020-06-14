#include "ObjectCode.h"

/***********************************
 *  Public members in TextRecord.  *
 ***********************************/

// Constructor.
TextRecord::TextRecord()
{
    clear();
}

// Mutator.
bool TextRecord::setStartAddress(int startAddress)
{
    if(startAddress >= 0)
    {
        this->startAddress = startAddress;
        return true;
    }
    else
        return false;
}

void TextRecord::appendRecord(const string record)
{
    this->record += record;
    length += record.length() / 2;  // Unit : byte.
}

// Method.
void TextRecord::clear()
{
    startAddress = -1;
    length = 0;
    record = "";
}



/***********************************
 *  Public members in ObjectCode.  *
 ***********************************/

// Constructor.
ObjectCode::ObjectCode()
{
    clear();
}

// Accessor.
TextRecord* ObjectCode::getTextRecord(int index) const
{
    if(index >= 0 && index < textRecords.size())
        return textRecords[index];
    else if(-index >= 1 && -index <= textRecords.size())
        return textRecords[textRecords.size()+index];
    else
        return nullptr;
}

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

bool ObjectCode::appendPartialToRecord(const string partial, int index)
{
    if(index >= 0 && index < textRecords.size())
    {
        textRecords[index]->appendRecord(partial);
        return true;
    }
    else
        return false;
}

void ObjectCode::appendPartialToLastRecord(const string partial)
{
    // Record list is NOT empty.  Append partial to last record in the list.
    if(textRecords.size() > 0)
        textRecords[textRecords.size()-1]->appendRecord(partial);
    // Record list is empty.  Create a new record.
    else
    {
        addRecord();
        textRecords[0]->appendRecord(partial);
    }
}

void ObjectCode::addRecord()
{
    ++length;
    textRecords.push_back(new TextRecord);
}

// Methods.
void ObjectCode::clear()
{
    name = "";
    baseAddress = 0;
    length = 0;
    startAddress = 0;
    textRecords.clear();
}

