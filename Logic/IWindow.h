//
// Created by stein on 31/12/2021.
//

#ifndef DOODLE_JUMP_IWINDOW_H
#define DOODLE_JUMP_IWINDOW_H

/***
 * Abstract function for controlling and receiving information from the window (representation)
 */
class IWindow {
public:
    virtual void clear() = 0;
    virtual void display() = 0;
    virtual void checkForClose() = 0;
    virtual void keyBoardPress(char* keyPresses) = 0;
    virtual int getWindowHeight() = 0;
    virtual int getWindowsWidth() = 0;
    virtual bool isOpen() = 0;
};


#endif//DOODLE_JUMP_IWINDOW_H
