// example of I from "SOLID"
// interface segragation

#pragma once

#include <vector>
#include <common.h>

class IModel
{
public:
    IModel() = default;
    virtual ~IModel() = default;

    virtual void jsonify() const = 0;
    virtual void serialize(ByteStream &) const = 0;
};

// add two more interface class

class IJsonifiable
{
public:
    virtual ~IJsonifiable() = default;
    virtual void jsonify() const = 0;
};

class ISerializable
{
public:
    virtual ~ISerializable() = default;
    virtual void serialize(ByteStream &) const = 0;
};

class IModel2 : public IJsonifiable, public ISerializable
{
public:
    virtual ~IModel2() = default;
};