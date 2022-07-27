//
// Created by stein on 24/11/2021.
//

#include "ConcreteFactory.h"

/*
std::vector<Platform *> ConcreteFactory::getPlatforms() {
    const std::vector<PlatformLogic *> logicPlatorms = world->getPlatforms();
    std::vector<Platform *> platforms;
    for(auto it = logicPlatorms.begin(); it != logicPlatorms.end(); ++it){
        platforms.push_back(new Platform(*it));
    }
    return platforms;
}

Doodler *ConcreteFactory::getDoodler() {
    return new Doodler(world->getDoodleLogic());
}
 */
ConcreteFactory::ConcreteFactory(sf::RenderWindow* window) {
    this->window = window;
}
std::shared_ptr<DoodlerLogic> ConcreteFactory::createDoodler(World* world) {
    std::shared_ptr<DoodlerLogic> doodlerLogic(new DoodlerLogic(world));
    std::cout << "doodle logic created" << std::endl;
    new Doodler(doodlerLogic, window);
    return doodlerLogic;
}
std::shared_ptr<PlatformLogic> ConcreteFactory::createPlatform(double locationX, double locationY, World* world) {
    std::shared_ptr<PlatformLogic> platoformLogic(new PlatformLogic(locationX,locationY,world));
    new Platform(platoformLogic, window);
    return platoformLogic;
}
std::shared_ptr<HorizontalPlatformLogic> ConcreteFactory::createHorizontalPlatform(double locationX, double locationY,World *world) {
    std::shared_ptr<HorizontalPlatformLogic> platoformLogic(new HorizontalPlatformLogic(locationX,locationY,world));
    new Platform(platoformLogic, window);
    return platoformLogic;
}
std::shared_ptr<VerticalPlatformLogic> ConcreteFactory::createVerticalPlatform(double locationX, double locationY,World *world) {
    std::shared_ptr<VerticalPlatformLogic> platoformLogic(new VerticalPlatformLogic(locationX,locationY,world));
    new Platform(platoformLogic, window);
    return platoformLogic;
}
std::shared_ptr<TemporaryPlatformLogic> ConcreteFactory::createTemporaryPlatform(double locationX, double locationY,World *world) {
    std::shared_ptr<TemporaryPlatformLogic> platoformLogic(new TemporaryPlatformLogic(locationX,locationY,world));
    new Platform(platoformLogic, window);
    return platoformLogic;
}
