//
// Created by stein on 8/08/2022.
//

#ifndef DOODLE_JUMP_SCORE_H
#define DOODLE_JUMP_SCORE_H


#include "EntityLogic.h"
#include "Subject.h"
class World;

class Score: public EntityLogic{
public:
    Score(World &world);
    void update() override;
    int getCurrentScore() override;
};


#endif//DOODLE_JUMP_SCORE_H
