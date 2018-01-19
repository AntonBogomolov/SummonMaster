#pragma once

class IDBSerializable
{
protected:
    virtual void loadFromDB(const unsigned int dbId) = 0;
    virtual void saveToDB() const = 0 ;
};