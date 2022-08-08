//
// Created by stein on 18/11/2021.
//

#ifndef TESTREPO_CAMERA_H
#define TESTREPO_CAMERA_H
#include "Stopwatch.h"
#include <memory>

class EntityLogic;
class Camera {
    int height = 0;
    std::shared_ptr<Stopwatch> stopwatch = stopwatch->getInstance();
    int screenHeight = 0;
    int screenWidth = 0;
public:
    Camera(int screenWidth, int screenHeight);
    std::pair<float, float> coordinateToPixel(const std::pair<float,float>& coordinate, const std::shared_ptr<EntityLogic> entity) const;
    float yCoordinateToPixel(float y) const;
    void addToHeight(unsigned int height);
    int getScreenWidth() const;
    int getScreenHeight() const;
    int getHeight() const;
};


#endif //TESTREPO_CAMERA_H
