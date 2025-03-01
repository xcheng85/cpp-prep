// three ways to achieve dip

// way 1: inheritance
// way 2: concept of template, caller to satisfy concept

// stable layer

// <core/ioplugin.h>

class IOPlugin
{
public:
    virtual void load() = 0;
    virtual void unload() = 0;
};

// <core/scene.h>
// #include <ioplugin.h>
class Scene
{
};

// <ext/gltfb.h>
// #include <ioplugin.h>
class GLTFIO : public IOPlugin
{
public:
    virtual void load() {};
    virtual void unload() {};
};