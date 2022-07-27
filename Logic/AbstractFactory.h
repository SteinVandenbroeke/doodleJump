//
// Created by stein on 24/11/2021.
//

#ifndef DOODLE_JUMP_ABSTRACTFACTORY_H
#define DOODLE_JUMP_ABSTRACTFACTORY_H
#include "World.h"


class AbstractFactory {
public:
    //AbstractFactory(Camera* camera);

    virtual std::shared_ptr<DoodlerLogic> createDoodler(World* world) = 0;
    virtual std::shared_ptr<PlatformLogic> createPlatform(double locationX, double locationY,World* world) = 0;
    virtual std::shared_ptr<HorizontalPlatformLogic> createHorizontalPlatform(double locationX, double locationY,World* world) = 0;
    virtual std::shared_ptr<VerticalPlatformLogic> createVerticalPlatform(double locationX, double locationY,World* world) = 0;
    virtual std::shared_ptr<TemporaryPlatformLogic> createTemporaryPlatform(double locationX, double locationY,World* world) = 0;
};


#endif //DOODLE_JUMP_ABSTRACTFACTORY_H
