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
    std::shared_ptr<EntityLogic> logicEntity;
public:
    EntityObserver(std::shared_ptr<EntityLogic> entityLogic);
};


#endif//DOODLE_JUMP_OBSERVER_H
