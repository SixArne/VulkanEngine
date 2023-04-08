#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>

class Component
{
public:
    Component() = default;
    virtual ~Component() = default;
    virtual std::string GetName(){ return std::string("component");};
};

class Transform: public Component
{
public:
    Transform() = default;
    ~Transform() = default;
    virtual std::string GetName() override {return std::string("transform");};
};

#endif