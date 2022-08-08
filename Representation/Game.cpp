//
// Created by stein on 18/11/2021.
//

#include <iostream>
#include "Game.h"
#include "../Logic/Stopwatch.h"
#include "../Logic/Random.h"
#include "../Logic/EntityLogic.h"
#include "../Logic/Camera.h"
#include "ConcreteFactory.h"
#include "Entity.h"
#include "Window.h"

std::shared_ptr<Stopwatch> Stopwatch::instance = 0;
std::shared_ptr<Random> Random::instance = 0;
Game::Game(int width, int height) {
    sf::RenderWindow renderWindow(sf::VideoMode(width, height), "Doodle jump");
    renderWindow.setFramerateLimit(120);
    Window window(width, height, renderWindow);
    ConcreteFactory factory(renderWindow);
    World world(window, factory);

    bool playing = true;
    while (playing)
    {
        window.clear();
        playing = world.update();
        window.display();
    }
}
