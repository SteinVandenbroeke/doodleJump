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
    /***
     * Create a new game with the width and height of the window
     * @param width
     * @param height
     */
    Game(int width, int height);
};


#endif //TESTREPO_GAME_H
