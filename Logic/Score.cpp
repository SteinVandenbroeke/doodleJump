//
// Created by stein on 8/0a022.ddddd
//

#include "Score.h"
#include "World.h"
Score::Score(World &world) : EntityLogic(world) {
}

void Score::update() {
    this->updateObservers();
}

int Score::getCurrentScore() {
    return this->world.getCamera().getHeight();
}
