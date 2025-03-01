// design of open-close principle

#pragma once
#include <common.h>
#include <typeinfo>
#include <cassert>
#include <iostream>
#include <memory>

namespace OCP
{
    class IModel
    {
    public:
        virtual ~IModel() = default;
        virtual void serialize(ByteStream &) const = 0;
    };

    enum ModelType : int
    {
        GLTF,
        ASSIMP,
        // Obj
    };

    class Gltf : public IModel
    {
    public:
        Gltf()
            : _type{ModelType::GLTF}
        {
        }
        virtual ~Gltf() = default;
        // Gltf coupled with all other models
        // if ModelType changes, it will re-compile,
        // how to avoid, strategy pattern
        virtual void serialize(ByteStream &) const
        {
        }

    private:
        ModelType _type;
    };

    class Assimp : public IModel
    {
    public:
        virtual ~Assimp() = default;
        virtual void serialize(ByteStream &) const
        {
        }
    };

    // version adhere to OCP
    class IModelOCP
    {
    public:
        virtual ~IModelOCP() = default;
        virtual void serialize(ByteStream &) const = 0;
    };

    class Serialization
    {
    public:
        Serialization() = default;
        void operator()(const IModelOCP *model)
        {
            std::cout << typeid(model).name() << std::endl;
        }
    };

    class AssimpOCP : public IModelOCP
    {
    public:
        AssimpOCP() = delete;
        AssimpOCP(std::shared_ptr<Serialization> serializer)
            : _serializer(serializer)
        {
        }

        virtual ~AssimpOCP() = default;
        virtual void serialize(ByteStream &) const
        {
            _serializer->operator()(this);
        }

    private:
        std::shared_ptr<Serialization> _serializer;
    };

    // Open-close principle for compile-time
    // template specialization is the tech behind it
    // template specialization for swap template function
    void swap(IModelOCP &a, IModelOCP &b)
    {
        std::cout << "swap customization for IModelOCP" << std::endl;
    }

    // extension without breaking close
    void swap(AssimpOCP &a, AssimpOCP &b)
    {
        std::cout << "swap customization for AssimpOCP" << std::endl;
    }

    template<typename T>
    void testSwap(T& v1, T& v2) {
        using std::swap; // 
        // if T is 
        // ADL
        swap(v1, v2); 
    }
};