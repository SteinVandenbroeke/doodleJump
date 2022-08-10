//
// Created by stein on 29/12/2021.
//

#ifndef DOODLE_JUMP_OBSERVER_H
#define DOODLE_JUMP_OBSERVER_H
#include "iostream"
#include <memory>
class EntityLogic;

class Observer {
public:
    virtual void update() = 0;
};

class EntityObserver: Observer{
protected:
    EntityLogic& logicEntity;
public:
    EntityObserver(EntityLogic& entityLogic);
};


#endif//DOODLE_JUMP_OBSERVER_H
