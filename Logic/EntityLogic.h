//
// Created by stein on 18/11/2021.
//

#ifndef TESTREPO_ENTITYMODEL_H
#define TESTREPO_ENTITYMODEL_H
#include "Camera.h"
#include "Random.h"
#include "Stopwatch.h"
#include "vector"
#include <functional>
#include <utility>
#include "Subject.h"
#include <memory>

enum EntityType { PlatformLogicE, DoodleLogicE, ItemLogicE, UndefinedLogicE, SpringLogicE };

class World;
class EntityObserver;
class EntityLogic: public Subject{
protected:
    bool collisionDooldle = false;
    EntityType type = UndefinedLogicE;
public:
    int getXSize() const;
    int getYSize() const;
    int getYLocation() const;
    int getXLocation() const;
    const std::pair<float, float>& getLocation() const;
    EntityLogic(World& world);
    EntityLogic(World& world, EntityType type);
    void setCollosionDoodle();
    EntityType getEntityType() const;
    World getWorld();
    virtual void update() = 0;
    virtual bool isFacingLeft(){
            return false;
    };
    virtual std::string getCustumTexture(){
        return "";
    }
    virtual std::vector<int> getHorizontalLines(){return std::vector<int>();}
    virtual int getCurrentScore(){return 0;}


protected:
    std::pair<float, float> locationXY;
    std::pair<float, float> sizeXY;

    World& world;
};

class BonusesLogic: public EntityLogic{
public:
    BonusesLogic(double locationX, double locationY, World&);
    void updateLocation(double locationX, double locationY);
    //TODO
};

class SpringLogic: public BonusesLogic{
public:
    SpringLogic(double locationX, double locationY, World&);
    void update() override;
    //TODO
};

class JetpackLogic: public BonusesLogic{
public:
    JetpackLogic(double locationX, double locationY, World&);
    void update() override;
};

class PlatformLogic: public EntityLogic{
private:
    int hexColor = 0x229900ff;
    std::shared_ptr<BonusesLogic> bonus = nullptr;
protected:
    void setHexColor(int hexColor);
public:
   // PlatformLogic(double locationX, double locationY, Camera* camera);
    PlatformLogic(double locationX, double locationY, World& world);
    constexpr static const double platformHeight = 20;
    constexpr static const double platformWidth = 100;
    virtual double getMaxYLocation() const;
    virtual double getMinYLocation() const;
    virtual int getColor() const;
    void update() override;
};

class MovePlatformLogic: public PlatformLogic{
protected:
    const float timeLoop = 100;
    double frameCounter = 0;
    double maxYLocation = 0;
    double minYLocation = 0;
    std::function<double (double)> const movementXOverTime;
    std::function<double (double)> const movementYOverTime;
public:
    MovePlatformLogic(double locationX, double locationY, World&, double frameAmount, std::function<double (double)> movementXOverTime, std::function<double (double)> movementYOverTime);
    void update() override;
    double getMaxYLocation() const override;
    double getMinYLocation() const override;
};

class HorizontalPlatformLogic: public MovePlatformLogic{
public:
    HorizontalPlatformLogic(double locationX, double locationY, World&);
};

class VerticalPlatformLogic: public MovePlatformLogic{
public:
    VerticalPlatformLogic(double locationX, double locationY, World&);
};

class VerticalRandomPlatformLogic: public PlatformLogic{
public:
    VerticalRandomPlatformLogic(double locationX, double locationY, World&);
    void update() override;
};

class HorizontalRandomPlatformLogic: public PlatformLogic{
public:
    HorizontalRandomPlatformLogic(double locationX, double locationY, World&);
    void update() override;
};

class TemporaryPlatformLogic: public PlatformLogic{
public:
    TemporaryPlatformLogic(double locationX, double locationY, World&);
    void update() override;
};

class BGTileLogic: public EntityLogic{
private:
std::vector<int> horizontalLines;
public:
    explicit BGTileLogic(World& world);
    void update() override;
    std::vector<int> getHorizontalLines() override;
};

class DoodlerLogic: public EntityLogic{
protected:
    float upValue = jumpHeight;
    bool up = true;
    bool facingLeft = false;
    double speed = 3;
    std::string custumTexture = "";
public:
    explicit DoodlerLogic(World& world);
    void moveLeft();
    void moveRight();
    void update() override;
    void resetJump();
    void updateJumpHight(double jumpHight);
    void setCustumTexture(std::string texturePath);
    std::string getCustumTexture() override;
    void resetCustumTexture();
    bool isFacingLeft() override;
    bool checkPlatformCollisions(std::vector<std::shared_ptr<PlatformLogic>> objects);
    bool checkBonusCollisions(std::vector<std::shared_ptr<BonusesLogic>> objects);
    constexpr static const double jumpHeight = 200;
    constexpr static const double doodleHeight = 109;
    constexpr static const double doodleWidth = 55;
};

bool collisionsDetection(EntityLogic& entity1, std::shared_ptr<EntityLogic> entity2);



#endif //TESTREPO_ENTITYMODEL_H
