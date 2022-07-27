//
// Created by stein on 29/12/2021.
//

#include "Observer.h"
#include "EntityLogic.h"

EntityObserver::EntityObserver(std::shared_ptr<EntityLogic> entityLogic): logicEntity(entityLogic) {
    this->logicEntity->addObserver(this);
}