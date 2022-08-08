//
// Created by stein on 18/11/2021.
//

#include "EntityLogic.h"
#include "World.h"
#include <math.h>
#include "Observer.h"

int EntityLogic::getYLocation() const {
    return this->locationXY.second;
}

int EntityLogic::getXLocation() const {
    return this->locationXY.first;
}

const std::pair<float, float>& EntityLogic::getLocation() const {
    return this->locationXY;
}

EntityLogic::EntityLogic(World& world): world(world) {
    this->type = UndefinedLogicE;
}

int EntityLogic::getXSize() const {
    return this->sizeXY.first;
}

int EntityLogic::getYSize() const {
    return this->sizeXY.second;
}

void EntityLogic::setCollosionDoodle() {
    collisionDooldle = true;
}
EntityType EntityLogic::getEntityType() const {
    return this->type;
}
EntityLogic::EntityLogic(World& world, EntityType type): EntityLogic(world) {
    this->type = type;
}
World EntityLogic::getWorld() {
    return this->world;
}

void DoodlerLogic::moveLeft() {
    facingLeft = true;
    this->locationXY.first -= 3.f * world.getStopwatch()->getMovementMultiplier();
    if(this->locationXY.first + this->doodleWidth < 0){
        this->locationXY.first = world.getCamera().getScreenWidth() - 1;
    }
}

void DoodlerLogic::moveRight() {
    facingLeft = false;
    this->locationXY.first += 3.f * world.getStopwatch()->getMovementMultiplier();
    if(this->locationXY.first > world.getCamera().getScreenWidth()){
        this->locationXY.first = 1;
    }
}

void DoodlerLogic::update() {
    if(upValue > 0 && up){
        this->speed -= 0.1;
        upValue -= 1 * world.getStopwatch()->getMovementMultiplier();
    }
    else{
        upValue -= 1 * world.getStopwatch()->getMovementMultiplier();
        up = false;
    }

    this->locationXY.second += ((upValue*1.5)/(this->jumpHeight)) * world.getStopwatch()->getMovementMultiplier();
    updateObservers();
}

DoodlerLogic::DoodlerLogic(World& world): EntityLogic(world, DoodleLogicE) {
    this->locationXY.second = 100;
    this->locationXY.first = 0;

    this->sizeXY.second = doodleHeight;
    this->sizeXY.first = doodleWidth;
}

void DoodlerLogic::resetJump() {
    upValue = jumpHeight;
    up = true;
    this->resetCustumTexture();
}

bool DoodlerLogic::checkPlatformCollisions(std::vector<std::shared_ptr<PlatformLogic>> objects) {
    if(this->up){
        return false;
    }

    for(auto it = objects.begin(); it != objects.end(); it++){
        if(collisionsDetection(*this, *it)){
            (*it)->setCollosionDoodle();
            this->locationXY.second = (*it)->getYLocation() + (*it)->getYSize();
            std::cout << "jump reset" << std::endl;
            this->resetJump();
            return true;
        }
    }
    return false;
}

bool DoodlerLogic::checkBonusCollisions(std::vector<std::shared_ptr<BonusesLogic>> objects) {
    if(this->up){
        return false;
    }

    for(auto it = objects.begin(); it != objects.end(); it++){
        if(collisionsDetection(*this, *it)){
            (*it)->setCollosionDoodle();
            this->locationXY.second = (*it)->getYLocation() + (*it)->getYSize();
            return true;
        }
    }
    return false;
}

bool DoodlerLogic::isFacingLeft() {
    return this->facingLeft;
}
void DoodlerLogic::updateJumpHight(double jumpHight) {
    this->upValue = jumpHight;
    this->up = true;
}
void DoodlerLogic::setCustumTexture(std::string texturePath) {
    this->custumTexture = texturePath;
}
void DoodlerLogic::resetCustumTexture() {
    this->custumTexture = "";
}
std::string DoodlerLogic::getCustumTexture() {
    return this->custumTexture;
}

PlatformLogic::PlatformLogic(double locationX, double locationY, World& world): EntityLogic(world, PlatformLogicE) {
    this->locationXY.second = locationY;//y val
    this->locationXY.first = locationX;//x val;
    this->sizeXY.first = platformWidth;
    this->sizeXY.second = platformHeight;
    int i = this->world.getRandom().getInstance()->randomNumber(0,10);
    if(i == 5)
        this->bonus = world.createSpring(*this);
    else if(i == 1)
        this->bonus = world.createJetPack(*this);
}

double PlatformLogic::getMaxYLocation() const {
    return this->getYLocation();
}

double PlatformLogic::getMinYLocation() const {
    return this->getYLocation();
}
int PlatformLogic::getColor() const {
    return this->hexColor;
}
void PlatformLogic::setHexColor(int hexColor) {
    //TODO check string
    this->hexColor = hexColor;
}
void PlatformLogic::update() {
    if(this->bonus != nullptr){
        this->bonus->updateLocation(this->locationXY.first, this->locationXY.second);
        this->bonus->update();
        this->bonus->updateObservers();
    }
}

bool collisionsDetection(EntityLogic& entity1, std::shared_ptr<EntityLogic> entity2) {
    int entity1MinX = entity1.getXLocation();
    int entity1MaxX = entity1.getXLocation() + entity1.getXSize();

    int entity1MinY = entity1.getYLocation();
    int entity1MaxY = entity1.getYLocation() + entity1.getYSize();

    int entity2MinX = entity2->getXLocation();
    int entity2MaxX = entity2->getXLocation() + entity2->getXSize();

    int entity2MinY = entity2->getYLocation();
    int entity2MaxY = entity2->getYLocation() + entity2->getYSize();

    bool checkX = entity1MaxX >= entity2MinX && entity1MinX <= entity2MaxX;
    bool checkY = entity1MaxY >= entity2MinY && entity1MinY <= entity2MaxY;

    std::shared_ptr<Stopwatch> stopwatch = stopwatch->getInstance();
    if(entity1.getEntityType() == DoodleLogicE && entity2->getEntityType() == PlatformLogicE){
        checkY = abs(entity1MinY - entity2MaxY) <= stopwatch->getInstance()->getMovementMultiplier() * 1;
    }
    else if(entity2->getEntityType() == DoodleLogicE && entity1.getEntityType() == PlatformLogicE){
        checkY = abs(entity1MaxY - entity2MinY) <= stopwatch->getInstance()->getMovementMultiplier() * 1;
    }
    if(checkY && checkX){
        return true;
    }
    return false;
}

MovePlatformLogic::MovePlatformLogic(double locationX, double locationY, World& world, double frameAmount,
                                     std::function<double(double)> const movementXOverTime,
                                     std::function<double(double)> const movementYOverTime): PlatformLogic(locationX, locationY, world),
                                     movementXOverTime(movementXOverTime),
                                     movementYOverTime(movementYOverTime),
                                     timeLoop(frameAmount){
    double maxYLocation = 0;
    double minYLocation = std::numeric_limits<double>::max();
    for(int i = 0; i < frameAmount; ++i){
        maxYLocation = std::max(maxYLocation, movementYOverTime(frameAmount));
        minYLocation = std::min(minYLocation, movementYOverTime(frameAmount));
    }
    this->maxYLocation = maxYLocation;
    this->minYLocation = minYLocation;
}

void MovePlatformLogic::update() {
    this->locationXY.first += movementXOverTime(frameCounter) * world.getStopwatch()->getMovementMultiplier();
    this->locationXY.second += movementYOverTime(frameCounter) * world.getStopwatch()->getMovementMultiplier();
    frameCounter += 1.f * world.getStopwatch()->getMovementMultiplier();
    if(frameCounter >= timeLoop){
        frameCounter = 0;
    }
    PlatformLogic::update();
}

double MovePlatformLogic::getMaxYLocation() const {
    return maxYLocation;
}

double MovePlatformLogic::getMinYLocation() const {
    return minYLocation;
}

HorizontalPlatformLogic::HorizontalPlatformLogic(double locationX, double locationY, World& world) : MovePlatformLogic(
        locationX, locationY, world,200,
        (([](double t){ if(t <= 100){return 1; }else {return -1; }})),
        ([](double t){ return 0; })) {
    setHexColor(0x009799ff);
}

VerticalPlatformLogic::VerticalPlatformLogic(double locationX, double locationY, World& world) : MovePlatformLogic(
        locationX, locationY, world,200,
        ([](double t){ return 0; }),
        ([](double t){ if(t <= 100){return 1; }else {return -1; }})) {
    setHexColor(0xffee00ff);
}

void TemporaryPlatformLogic::update() {
    if(this->collisionDooldle){
        this->sizeXY = std::pair<float, float>(0,0);
        this->locationXY = std::pair<float, float>(0,0);
    }
    PlatformLogic::update();
}

TemporaryPlatformLogic::TemporaryPlatformLogic(double locationX, double locationY, World& world) : PlatformLogic(locationX, locationY, world) {
    setHexColor(0xffffffff);
}

VerticalRandomPlatformLogic::VerticalRandomPlatformLogic(double locationX, double locationY, World& world) : PlatformLogic(locationX, locationY, world) {
    setHexColor(0x808080);
}

void VerticalRandomPlatformLogic::update() {
    if(this->collisionDooldle){
        Random* random;
        int newYLocation = random->randomNumber(0, 200) - 100;
        this->locationXY.second = this->locationXY.second + (newYLocation);
        this->collisionDooldle = false;
    }
    PlatformLogic::update();
}

HorizontalRandomPlatformLogic::HorizontalRandomPlatformLogic(double locationX, double locationY, World& world) : PlatformLogic(locationX, locationY, world) {
    setHexColor(0x808090);
}

void HorizontalRandomPlatformLogic::update() {
    if(this->collisionDooldle){
        Random* random;
        int newXLocation = random->randomNumber(0, 200) - 100;
        this->locationXY.first = this->locationXY.first + (newXLocation);
        this->collisionDooldle = false;
    }
    PlatformLogic::update();
}

BonusesLogic::BonusesLogic(double locationX, double locationY, World& world): EntityLogic(world, SpringLogicE) {
    this->locationXY.second = locationY;//y val
    this->locationXY.first = locationX;//x val;
}
void BonusesLogic::updateLocation(double locationX, double locationY) {
    this->locationXY.first = locationX;
    this->locationXY.second = locationY;
}


SpringLogic::SpringLogic(double locationX, double locationY, World& world): BonusesLogic(locationX, locationY, world) {
    this->sizeXY.first = 40;
    this->sizeXY.second = 33;
}

void SpringLogic::update() {
    if(this->collisionDooldle){
        std::cout << "jump high!!!" << std::endl;
        this->getWorld().getDoodle().updateJumpHight(400);
        this->collisionDooldle = false;
    }
}
JetpackLogic::JetpackLogic(double locationX, double locationY, World& world) : BonusesLogic(locationX, locationY, world) {
    this->sizeXY.first = 52;
    this->sizeXY.second = 75;

}

void JetpackLogic::update() {
    if(this->collisionDooldle && this->getWorld().getDoodle().getYLocation() > this->getYLocation()){
        this->getWorld().getDoodle().updateJumpHight(1200);
        this->getWorld().getDoodle().setCustumTexture("./src/textures/doodleJetpack.png");
        this->collisionDooldle = false;
        std::cout << "jetpack collision" << std::endl;
    }
}

BGTileLogic::BGTileLogic(World &world1) : EntityLogic(world1) {
    std::cout << "test" << std::endl;
}
void BGTileLogic::update() {
    updateObservers();
}