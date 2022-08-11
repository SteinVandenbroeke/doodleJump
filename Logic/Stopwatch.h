//
// Created by stein on 18/11/2021.
//

#ifndef TESTREPO_STOPWATCH_H
#define TESTREPO_STOPWATCH_H
#include <chrono>
#include <iostream>
#include <memory>

/***
 * Stopwatch singleton
 */
class Stopwatch {
    static std::shared_ptr<Stopwatch> instance;

    /***
     * Creates a stopwatch item and set the time to the current time
     */
    Stopwatch(){
        previousFrameTime = std::chrono::steady_clock::now();
        framesLoadTime = 0;
    }

    Stopwatch(Stopwatch&) = delete;
    void operator=(Stopwatch&) = delete;

    std::chrono::time_point<std::chrono::steady_clock> previousFrameTime;
    float framesLoadTime;
    const float framesLoadTimeMuliplier = 200.f;
public:
    static std::shared_ptr<Stopwatch> getInstance(){
        if(!instance){
            instance = std::shared_ptr<Stopwatch>(new Stopwatch());
        }
        return instance;
    }

    /***
     * Must be called for every game loop
     */
    void newFrame(){
        auto currentTime = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = currentTime-previousFrameTime;
        framesLoadTime = elapsed_seconds.count();
        //std::cout << std::to_string(1 / framesLoadTime) << std::endl;
        previousFrameTime = currentTime;
    }

    /***
     * Function that returns the loadtime for 1 frame
     * @return
     */
    float getFrameLoadTime(){
        return framesLoadTime;
    }

    /***
     * Function that returns the movement multiplier (for every movement calculation)
     * @return
     */
    float getMovementMultiplier(){
        return this->framesLoadTime * framesLoadTimeMuliplier;
    }
};

#endif //TESTREPO_STOPWATCH_H
