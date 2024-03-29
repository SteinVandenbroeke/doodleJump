//
// Created by stein on 31/12/2021.
//

#include "Window.h"
#include <SFML/Window/Event.hpp>

Window::Window(int width, int height, sf::RenderWindow& window): width(width), height(height), window(window){}

void Window::clear() {
    this->window.clear(sf::Color(255, 239, 196));
}
void Window::display() {
    this->window.display();
}

void Window::checkForClose() {
    sf::Event event;
    window.pollEvent(event);
    if (event.type == sf::Event::Closed)
        this->window.close();
}

void Window::keyBoardPress(char* keyPresses) {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
        keyPresses[0] = 'Q';
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        keyPresses[1] = 'D';
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){
        keyPresses[2] = 'Z';
    }
}

int Window::getWindowHeight() {
    return this->height;
}
int Window::getWindowsWidth() {
    return this->width;
}
bool Window::isOpen() {
    return this->window.isOpen();
}
