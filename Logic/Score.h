//
// Created by stein on 8/08/2022.
//

#ifndef DOODLE_JUMP_SCORE_H
#define DOODLE_JUMP_SCORE_H


#include "EntityLogic.h"
#include "Subject.h"
#include <fstream>
class World;

class Score: public EntityLogic{
private:
    int extraScore = 0;
    int highScore = -1;
    void loadHighScore();
    void safeHighScore();
public:
    Score(World &world);
    ~Score();
    void update() override;
    int getCurrentScore() override;
    int getCurrentHp() override;
    void addScorePoints(int amount);
    int getHighScore() override;
};


#endif//DOODLE_JUMP_SCORE_H
