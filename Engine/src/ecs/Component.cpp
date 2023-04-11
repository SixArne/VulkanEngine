#include "Component.h"
#include "GameObject.h"

Component::Component(GameObject *pOwner)
    : m_pOwner(pOwner)
{
}

GameObject *Component::GetOwner() const
{
    return m_pOwner;
}
