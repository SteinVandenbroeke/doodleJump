//
// Created by stein on 29/12/2021.
//

#include "Observer.h"
#include "EntityLogic.h"

EntityObserver::EntityObserver(EntityLogic& entityLogic): logicEntity(entityLogic) {
    this->logicEntity.addObserver(this);
}