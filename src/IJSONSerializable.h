#pragma once 

#include <novemberlib/utils/json.h>
using nlohmann::json;

class IJSONSerializable
{
public:
    virtual const json toJSON() const
    {
        return json();
    }
};