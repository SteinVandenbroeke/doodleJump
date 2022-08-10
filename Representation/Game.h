//
// Created by stein on 18/11/2021.
//

#ifndef TESTREPO_GAME_H
#define TESTREPO_GAME_H
#include "ConcreteFactory.h"
#include "Window.h"
#include <SFML/Graphics.hpp>

class Game {
public:
    Game(int width, int height);
    void gameLoop(Window &window, ConcreteFactory &factory);
};


#endif //TESTREPO_GAME_H
