// ComponentRegisterMeta.h
#pragma once
#include "ComponentRegister.h"
#include "ComponentManager.h"
#include "ClassID.h"

class GameObject;

#define REGISTER_COMPONENT(TYPE)                                                    \
class TYPE;                                                                         \
namespace                                                                           \
{                                                                                   \
    struct TYPE##Register                                                           \
    {                                                                               \
        TYPE##Register()                                                            \
        {                                                                           \
            ComponentRegister::Register(                                            \
                #TYPE,                                                              \
                ClassID<TYPE>::GetID(),                                             \
                [](ComponentManager* manager, GameObject* obj)                      \
                {                                                                   \
                    manager->AddComponentPendingAwake<TYPE>(obj);                   \
                }                                                                   \
            );                                                                      \
        }                                                                           \
    };                                                                              \
                                                                                    \
    static TYPE##Register s_##TYPE##Register;                                       \
}