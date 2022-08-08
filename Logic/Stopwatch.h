//
// Created by stein on 18/11/2021.
//

#ifndef TESTREPO_STOPWATCH_H
#define TESTREPO_STOPWATCH_H
#include <chrono>
#include <iostream>
#include <memory>

class Stopwatch {
    static std::shared_ptr<Stopwatch> instance;
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

    void newFrame(){
        auto currentTime = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = currentTime-previousFrameTime;
        framesLoadTime = elapsed_seconds.count();
        //std::cout << std::to_string(1 / framesLoadTime) << std::endl;
        previousFrameTime = currentTime;
    }

    float getFrameLoadTime(){
        return framesLoadTime;
    }

    float getMovementMultiplier(){
        return this->framesLoadTime * framesLoadTimeMuliplier;
    }
};

#endif //TESTREPO_STOPWATCH_H
