//
// Created by stein on 31/12/2021.
//

#include "Window.h"

Window::Window(int width, int height, sf::RenderWindow* window): width(width), height(height) {
    this->window = window;
}
void Window::clear() {
    this->window->clear();
}
void Window::display() {
    this->window->display();
}
void Window::close() {
    this->window->close();
}

char Window::keyBoardPress() {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
        return 'Q';
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        return 'D';
    }
    return -1;
}
int Window::getWindowHeight() {
    return this->height;
}
int Window::getWindowsWidth() {
    return this->width;
}
