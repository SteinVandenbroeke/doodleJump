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
    this->startscreen = this->factory.createStartScreen(*this);
    std::cout << "create doodle ok" << std::endl;
    platforms.push_back(this->factory.createPlatform(10,10, *this));
}

bool World::update() {
    this->stopwatch->newFrame();
    double frameTime = 1/this->stopwatch->getFrameLoadTime();
    if(frameTime < 40 || frameTime > 65){
        std::cout << (1/this->stopwatch->getFrameLoadTime()) << std::endl;
    }
    this->updateBullets();
    this->bgTile->update();
    this->updatePlatforms();
    doodler->update();
    doodler->checkBonusCollisions(this->bonussen);
    doodler->checkPlatformCollisions(this->platforms);
    doodler->checkEnemyCollisions(this->enemies);
    this->score->update();

    char pressed[3] = {-1, -1, -1};
    window.keyBoardPress(pressed);

    //Check if world moves up
    if(pressed[0] == 'Q'){
        doodler->moveLeft();
    }
    if(pressed[1] == 'D'){
        doodler->moveRight();
    }
    if(pressed[2] == 'Z'){
        if(!continuShootBlock){
            this->createBullet(*doodler);
        }
        continuShootBlock = true;
    }
    else {
        continuShootBlock = false;
    }

    if(!started && (pressed[0] == 'Q' || pressed[1] == 'D' || pressed[2] == 'Z')){
        generatePlatforms();
        started = true;
        return true;
    }
    else if(!started){
        this->startscreen->update();
    }

    if(doodler->getYLocation() >= camera.getHeight() + camera.getScreenHeight() / 2){
        double heightDifference = abs((camera.getHeight() + camera.getScreenHeight()/2) - doodler->getYLocation());
        camera.addToHeight(heightDifference);
        this->generatePlatforms();
        this->removePlatforms();
    }
    else if(doodler->getYLocation() <= camera.getHeight()){
        started = false;
        return false;
    }
    return true;
}

void World::gameLoop() {
    bool playing = true;
    while (playing && window.isOpen())
    {
        this->window.clear();
        playing = this->update();
        this->window.display();
        this->window.checkForClose();
    }
}

void World::generatePlatforms() {
    std::shared_ptr<PlatformLogic> previusPlatform = platforms.back();
    while(previusPlatform->getYLocation() < camera.getHeight() + this->camera.getScreenHeight()){
        double platformXLocation = random->randomNumber(0,this->camera.getScreenWidth() - (PlatformLogic::platformWidth/2));
        double maxYPlatform = std::max(previusPlatform->getMaxYLocation(), (double)(previusPlatform->getYLocation())) + (DoodlerLogic::jumpHeight/1.1) - (PlatformLogic::platformHeight * 2);


        int minHeight = previusPlatform->getYLocation() + PlatformLogic::platformHeight + (this->getScore().getCurrentScore() / 500);
        if(minHeight >= maxYPlatform){
            minHeight = maxYPlatform - 1;
        }

        double platformYLocation = random->randomNumber( minHeight, maxYPlatform);
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

void World::updatePlatforms() {
    for(auto it = platforms.begin(); it != platforms.end(); ++it){
        (*it)->update();
    }
}

void World::updateBullets() {
    auto it = bullets.begin();
    while(it != bullets.end()){
        (*it)->update();
        if((*it)->checkEnemyCollisions(this->enemies) ||
            (*it)->getYLocation() > this->camera.getHeight() + this->camera.getScreenHeight() ||
            (*it)->getYLocation() < this->doodler->getYLocation()){
            bullets.erase(it);
        }
        else{
            ++it;
        }
    }

    it = reversebullets.begin();
    while(it != reversebullets.end()){
        (*it)->update();
        if((*it)->checkEnemyCollisions(this->enemies) ||
            (*it)->getYLocation() > this->camera.getHeight() + this->camera.getScreenHeight() ||
            (*it)->getYLocation() < this->doodler->getYLocation()){
            reversebullets.erase(it);
        }
        else{
            ++it;
        }
    }
}

std::shared_ptr<PlatformLogic> World::getRandomPlatform(double platformXLocation, double platformYLocation) {
    double score = this->getScore().getCurrentScore() + 1;
    int maxChange = 1000;
    int randomNumber = std::min(random->randomNumber(0, score), maxChange);
    if(randomNumber < 100){
        return this->factory.createPlatform(platformXLocation, platformYLocation, *this);
    }
    else {
        int randomNumber = random->randomNumber(0, 4);
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
    std::cout << "spring created" << std::endl;
    return spring;
}

std::shared_ptr<BonusesLogic> World::createJetPack(PlatformLogic &platform) {
    std::shared_ptr<BonusesLogic> jetpack = this->factory.createJetpack(platform.getXLocation(), platform.getYLocation(), *this);
    this->bonussen.push_back(jetpack);
    return jetpack;
}

std::shared_ptr<BonusesLogic> World::createSpike(PlatformLogic &platform) {
    std::shared_ptr<SpikeLogic> spike = this->factory.createSpike(platform.getXLocation(), platform.getYLocation(), *this);
    this->bonussen.push_back(spike);
    return spike;
}

std::shared_ptr<BonusesLogic> World::createAddHp(PlatformLogic &platform) {
    std::shared_ptr<AddHpLogic> hpBuble = this->factory.createAddHp(platform.getXLocation(), platform.getYLocation(), *this);
    this->bonussen.push_back(hpBuble);
    return hpBuble;
}


const Random &World::getRandom() const {
    return *random;
}

DoodlerLogic &World::getDoodle() {
    return *this->doodler;
}

std::shared_ptr<Enemy0Logic> World::createEnemy0(PlatformLogic &platform) {
    std::shared_ptr<Enemy0Logic> enemy = this->factory.createEnemy0(platform, *this);
    this->enemies.push_back(enemy);
    return enemy;
}

std::shared_ptr<Enemy1Logic> World::createEnemy1(PlatformLogic &platform) {
    std::shared_ptr<Enemy1Logic> enemy = this->factory.createEnemy1(platform, *this);
    this->enemies.push_back(enemy);
    return enemy;
}

void World::createBullet(DoodlerLogic &doodlerLogic) {
    this->bullets.push_back(this->factory.createBullet(doodlerLogic.getBulletLocationX(), doodlerLogic.getBulletLocationY(), *this, false));
}

void World::createBullet(EnemyLogic &enemyLogic) {
    this->reversebullets.push_back(this->factory.createBullet(enemyLogic.getBulletLocationX(), enemyLogic.getYLocation(), *this, true));
}

Score &World::getScore() {
    return *this->score;
}
