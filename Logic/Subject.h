//
// Created by stein on 30/12/2021.
//

#ifndef DOODLE_JUMP_SUBJECT_H
#define DOODLE_JUMP_SUBJECT_H

#include "Observer.h"
#include <list>


class Subject {
private:
    std::list<Observer *> observerList;
public:
    void addObserver(Observer *observer) {
        std::cout << "added to observer list" << std::endl;
        observerList.push_back(observer);
    }
    void removeObserver(Observer *observer) {
        observerList.remove(observer);
    }

    void updateObservers() {
        for(auto it = observerList.begin(); it != observerList.end(); ++it){
            (*it)->update();
        }
    }
};


#endif//DOODLE_JUMP_SUBJECT_H
