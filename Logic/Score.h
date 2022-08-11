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
    /***
     * Create a score entity for a given world
     * @param world
     */
    Score(World &world);

    /***
     * deconstruct score and safe to file if higher than the curren high score
     */
    ~Score();

    /***
     * updates all obsevers (representation)
     */
    void update() override;

    /***
     * returns the current score of the player
     * @return
     */
    int getCurrentScore() override;

    /***
     * returns the current hp of the doodle
     * @return
     */
    int getCurrentHp() override;

    /***
     * add an amount to the current score
     * @param amount
     */
    void addScorePoints(int amount);

    /***
     * returns the all time high score
     * @return
     */
    int getHighScore() override;
};


#endif//DOODLE_JUMP_SCORE_H
