//
// Created by stein on 24/11/2021.
//

#ifndef DOODLE_JUMP_CONCRETEFACTORY_H
#define DOODLE_JUMP_CONCRETEFACTORY_H

#include <vector>
#include "../Logic/AbstractFactory.h"
#include "Entity.h"

class ConcreteFactory: public AbstractFactory{
private:
    sf::RenderWindow* window = nullptr;
public:
    //std::vector<Platform*> getPlatforms();
    //Doodler* getDoodler();
    ConcreteFactory(sf::RenderWindow* window);
    //World* getWorld();

    std::shared_ptr<DoodlerLogic> createDoodler(World* world) override;
    std::shared_ptr<PlatformLogic> createPlatform(double locationX, double locationY,World* world) override;
    std::shared_ptr<HorizontalPlatformLogic> createHorizontalPlatform(double locationX, double locationY,World* world) override;
    std::shared_ptr<VerticalPlatformLogic> createVerticalPlatform(double locationX, double locationY,World* world) override;
    std::shared_ptr<TemporaryPlatformLogic> createTemporaryPlatform(double locationX, double locationY,World* world) override;
};


#endif //DOODLE_JUMP_CONCRETEFACTORY_H
