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
    /***
     * Creates a new window of specified height
     * @param width
     * @param height
     */
    Window(int width, int height, sf::RenderWindow&);

    /***
     * Clears the window
     */
    void clear() override;

    /***
     * Display the items draw on the window
     */
    void display() override;

    /***
     * check if close button is pressed en close window
     */
    void checkForClose() override;

    /***
     * Functions to get te key presses
     * @param keyPresses
     */
    void keyBoardPress(char* keyPresses) override;

    /***
     * Returns the height of the window
     * @return window height
     */
    int getWindowHeight() override;

    /***
     * Returns the width of the window
     * @return window width
     */
    int getWindowsWidth() override;

    /***
     * Returns if the window is still open
     * @return window open
     */
    bool isOpen() override;
};


#endif//DOODLE_JUMP_WINDOW_H
