//
// Created by stein on 18/11/2021.
//

#include "Camera.h"
#include "EntityLogic.h"

Camera::Camera(int screenWidth, int screenHeight): screenHeight(screenHeight), screenWidth(screenWidth) {

}

std::pair<float, float> Camera::coordinateToPixel(const std::pair<float,float>& coordinate, const std::shared_ptr<EntityLogic> entity) const {
    return std::pair<float, float>(coordinate.first,
            (this->screenHeight - ((coordinate.second + entity->getYSize()) - this->height)));
}

void Camera::addToHeight(unsigned int height) {
    if(height < 0){
        //throw TODO
    }
    this->height += height;

}

int Camera::getScreenWidth() const {
    return this->screenWidth;
}

int Camera::getScreenHeight() const {
    return this->screenHeight;
}

int Camera::getHeight() const {
    return this->height;
}
