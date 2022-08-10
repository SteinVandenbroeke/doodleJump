//
// Created by stein on 31/12/2021.
//

#ifndef DOODLE_JUMP_WINDOW_H
#define DOODLE_JUMP_WINDOW_H


#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "../Logic/IWindow.h"

class Window: public IWindow{
private:
    sf::RenderWindow& window;
    int height = 0;
    int width = 0;
public:
    Window(int width, int height, sf::RenderWindow&);
    void clear() override;
    void display() override;
    void close() override;
    void keyBoardPress(char* keyPresses) override;
    int getWindowHeight() override;
    int getWindowsWidth() override;
};


#endif//DOODLE_JUMP_WINDOW_H
