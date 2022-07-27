//
// Created by stein on 31/12/2021.
//

#ifndef DOODLE_JUMP_IWINDOW_H
#define DOODLE_JUMP_IWINDOW_H


class IWindow {
public:
    virtual void clear() = 0;
    virtual void display() = 0;
    virtual void close() = 0;
    virtual char keyBoardPress() = 0;
    virtual int getWindowHeight() = 0;
    virtual int getWindowsWidth() = 0;
};


#endif//DOODLE_JUMP_IWINDOW_H
