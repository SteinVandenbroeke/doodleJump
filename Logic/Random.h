//
// Created by stein on 18/11/2021.
//

#ifndef TESTREPO_RANDOM_H
#define TESTREPO_RANDOM_H
#include <ctime>
#include <cstdlib>
#include <memory>

/***
 * singleton class for a random class for generating numbers between a min and max
 */
class Random {
    static std::shared_ptr<Random> instance;
    Random(){
        srand(time(0));
    }

    Random(Random&) = delete;
    void operator=(Random&) = delete;
public:
    static std::shared_ptr<Random> getInstance(){
        if(!instance){
            instance = std::shared_ptr<Random>(new Random());
        }
        return instance;
    }

    /***
     * generates a number between min and max (min and max included)
     * @param min
     * @param max
     * @return
     */
    int randomNumber(int min, int max){
        return rand()%(max-min + 1) + min;
    }
};
#endif //TESTREPO_RANDOM_H
