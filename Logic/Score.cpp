//
// Created by stein on 8/0a022.ddddd
//

#include "Score.h"
#include "World.h"
#include <iostream>

Score::Score(World &world) : EntityLogic(world) {
    this->loadHighScore();
}

void Score::update() {
    this->updateObservers();
}

int Score::getCurrentScore() {
    return this->world.getCamera().getHeight() + this->extraScore;
}
int Score::getCurrentHp() {
    return this->world.getDoodle().getHp();
}
void Score::addScorePoints(int amount) {
    this->extraScore += amount;
}

void Score::loadHighScore() {
    std::ifstream scoreFile("highScore");
    if (scoreFile.is_open())
    {
        std::string score;
        getline (scoreFile,score);
        this->highScore = std::stoi(score);
        scoreFile.close();
    }
    else{
        this->highScore = 0;
    }
}
void Score::safeHighScore() {
    if(this->getCurrentScore() > this->highScore){
        std::cout << "new file" << std::endl;
        std::ofstream ScoreFile("highScore");
        ScoreFile << this->getCurrentScore();
        ScoreFile.close();
    }
}

Score::~Score() {
    std::cout << "score destructor" << std::endl;
    this->safeHighScore();
}
int Score::getHighScore() {
    return this->highScore;
}
