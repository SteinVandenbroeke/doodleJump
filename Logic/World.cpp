//
// Created by stein on 18/11/2021.
//

#include "World.h"
#include "AbstractFactory.h"

World::World(IWindow& window, AbstractFactory& factory): window(window), factory(factory), camera(Camera(window.getWindowsWidth(), window.getWindowHeight())) {
    std::cout << "create doodle" << std::endl;
    this->doodler = this->factory.createDoodler(*this);
    this->bgTile = this->factory.createBGTile(*this);
    this->score = this->factory.createScore(*this);
    std::cout << "create doodle ok" << std::endl;
    platforms.push_back(this->factory.createPlatform(0,0, *this));
    generatePlatforms();
}

bool World::update() {
    this->stopwatch->newFrame();
    this->bgTile->update();
    this->updatePlatforms();
    doodler->update();
    doodler->checkBonusCollisions(this->bonussen);
    doodler->checkPlatformCollisions(this->platforms);
    this->score->update();

    //Check if world moves up
    if(window.keyBoardPress() == 'Q'){
        doodler->moveLeft();
    }
    if(window.keyBoardPress() == 'D'){
        doodler->moveRight();
    }
    if(doodler->getYLocation() >= camera.getHeight() + camera.getScreenHeight() / 2){
        double heightDifference = abs((camera.getHeight() + camera.getScreenHeight()/2) - doodler->getYLocation());
        camera.addToHeight(heightDifference);
        this->generatePlatforms();
        this->removePlatforms();
    }
    else if(doodler->getYLocation() <= camera.getHeight()){
        return false;
    }
    return true;
}

void World::generatePlatforms() {
    std::shared_ptr<PlatformLogic> previusPlatform = platforms.back();
    while(previusPlatform->getYLocation() < camera.getHeight() + this->camera.getScreenHeight()){
        double platformXLocation = random->randomNumber(0,this->camera.getScreenWidth() - (PlatformLogic::platformWidth/2));
        double maxYPlatform = (DoodlerLogic::jumpHeight/2) - (PlatformLogic::platformHeight * 2);
        double platformYLocation = random->randomNumber(previusPlatform->getYLocation() + PlatformLogic::platformHeight, maxYPlatform);

        std::shared_ptr<PlatformLogic> platform = getRandomPlatform(platformXLocation, platformYLocation);
        platforms.push_back(platform);
        previusPlatform = platform;
    }
}

void World::removePlatforms() {
    if((*platforms.begin())->getYLocation() <= camera.getHeight()){
        std::vector<std::shared_ptr<PlatformLogic>>::iterator endIterator = platforms.begin();
        int counter = 0;
        for(auto it = platforms.begin(); it != platforms.end(); ++it){
            if((*it)->getYLocation() <= camera.getHeight()){
                counter++;
                endIterator = it;
            }
            else{
                break;
            }
        }
        if(endIterator == platforms.begin())
            platforms.erase(platforms.begin());
        else
            platforms.erase(platforms.begin(), endIterator);
    }
}

/*
DoodlerLogic* World::getDoodleLogic() const {
    return this->doodler;
}
*/

/*
const std::vector<PlatformLogic *>& World::getPlatforms() const {
    return this->platforms;
}*/

void World::updatePlatforms() {
    for(auto it = platforms.begin(); it != platforms.end(); ++it){
        (*it)->update();
        (*it)->updateObservers();
    }
}

std::shared_ptr<PlatformLogic> World::getRandomPlatform(double platformXLocation, double platformYLocation) {
    double score = 200; //change!
    int maxChange = 1000;
    int randomNumber = std::min(random->randomNumber(0, score), maxChange);
    if(randomNumber < 100){
        return this->factory.createPlatform(platformXLocation, platformYLocation, *this);
    }
    else {
        std::cout << "Special platform"<<std::endl;
        int randomNumber = random->randomNumber(0, 5);//TODO
        switch (randomNumber) {
            case 0:
                return this->factory.createHorizontalPlatform(platformXLocation,platformYLocation, *this);
            case 1:
                return this->factory.createVerticalPlatform(platformXLocation,platformYLocation, *this);
            case 2:
                return this->factory.createTemporaryPlatform(platformXLocation,platformYLocation,*this);
            case 3:
                return this->factory.createVerticalRandomPlatform(platformXLocation,platformYLocation,*this);
            case 4:
                return this->factory.createHorizontalRandomPlatform(platformXLocation,platformYLocation,*this);
        }
        throw("error");
        return nullptr;
    }
}
const Camera& World::getCamera() const {
    return this->camera;
}
std::shared_ptr<Stopwatch> World::getStopwatch() {
    return this->stopwatch;
}
std::shared_ptr<BonusesLogic> World::createSpring(PlatformLogic &platform) {
    std::shared_ptr<BonusesLogic> spring = this->factory.createSpring(platform.getXLocation(), platform.getYLocation(), *this);
    this->bonussen.push_back(spring);
    return spring;
}

std::shared_ptr<BonusesLogic> World::createJetPack(PlatformLogic &platform) {
    std::shared_ptr<BonusesLogic> jetpack = this->factory.createJetpack(platform.getXLocation(), platform.getYLocation(), *this);
    this->bonussen.push_back(jetpack);
    return jetpack;
}

const Random &World::getRandom() const {
    return *random;
}

DoodlerLogic &World::getDoodle() {
    return *this->doodler;
}