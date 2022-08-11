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

enum EntityType { PlatformLogicE, DoodleLogicE, ItemLogicE, UndefinedLogicE, SpringLogicE, PlatmorLogicE };

class World;
class EntityObserver;
class PlatformLogic;
class EntityLogic: public Subject{
protected:
    bool collisionDooldle = false;
    EntityType type = UndefinedLogicE;
    EntityLogic(World& world);
    EntityLogic(World& world, EntityType type);
public:
    int getXSize() const;
    int getYSize() const;
    int getYLocation() const;
    int getXLocation() const;
    const std::pair<float, float>& getLocation() const;
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
    virtual bool darkTexture(){
        return false;
    }
    virtual std::vector<int> getHorizontalLines(){return std::vector<int>();}
    virtual int getCurrentScore(){return 0;}
    virtual int getCurrentHp() {return 0;}
    virtual int getHighScore() {return 0;}

protected:
    std::pair<float, float> locationXY;
    std::pair<float, float> sizeXY;

    World& world;
};

class PlatformItem: public EntityLogic{
protected:
    /***
     * Creates a new logic platform item (item on an platfrom) in a given world
     * @param locationX
     * @param locationY
     * @param world
     */
    PlatformItem(double locationX, double locationY, World& world);
public:
    /***
     * Function to update the logic location of the logic platform item
     * @param locationX
     * @param locationY
     */
    void updateLocation(double locationX, double locationY);

    /***
     * function to update the platform item (every type of platform item has his own update function)
     */
    void update() override = 0;
};

class EnemyLogic: public PlatformItem{
protected:
    bool previousCollisionDooldle = false;
    PlatformLogic& parentPlatform;
    double flashSec = 0;
    int hp;

    /***
     * Creates a logic enemy on an given platform (protected because it must be a specified enemy type)
     * @param platform
     */
    EnemyLogic(PlatformLogic& platform, World&);
public:
    /***
     * Function to update the enemy:
     * - will check collision with doodle in the world -> when hit decreases hp of doodle
     */
    void update() override;

    /***
     * Function that add points to the game, decreases hp or removes this enemy and let the enemy flash
     * @return
     */
    virtual bool hitByBullet();

    /***
     * Function to set flashSec (this are the sec to change the color of the enemy)
     * @param timeInSec
     */
    void makeDark(double timeInSec);

    /***
     * Function that returns True if flashSec are not passed
     * @return True/False
     */
    bool darkTexture() override;

    /***
     * Function that returns the x location from where the enemy returns his bullets
     * @return
     */
    virtual int getBulletLocationX();
};

class Enemy0Logic: public EnemyLogic{
public:
    /***
     * Creates a logic enemy of type 0 on an given platform
     * @param platform
     * @param world
     */
    Enemy0Logic(PlatformLogic& platform, World& world);
};

class Enemy1Logic: public EnemyLogic{
public:
    /***
     * Creates a logic enemy of type 1 on an given platform
     * @param platform
     * @param world
     */
    Enemy1Logic(PlatformLogic& platform, World& world);
};

class BonusesLogic: public PlatformItem{
protected:
    /***
     * Creates a logic bonus on an given location (protected because it must be a specified enemy type)
     * @param locationX
     * @param locationY
     */
    BonusesLogic(double locationX, double locationY, World&);
};

class SpringLogic: public BonusesLogic{
public:
    /***
     * Creates a logic spring on an given location on the given world
     * @param locationX
     * @param locationY
     */
    SpringLogic(double locationX, double locationY, World&);

    /***
     * checks if there is a collision with the doodle using the "collisionDooldle" varible
     * When there is updates the jump height of the doodle
     */
    void update() override;
};

class JetpackLogic: public BonusesLogic{
public:
    /***
     * Creates a logic jetpack on an given location on the given world
     * @param locationX
     * @param locationY
     */
    JetpackLogic(double locationX, double locationY, World&);

    /***
     * checks if there is a collision with the doodle using the "collisionDooldle" varible
     * When there is updates the jump height of the doodle and sets a custom texture in the "custumTexture" variable
     */
    void update() override;
};

class SpikeLogic: public BonusesLogic{
public:
    /***
     * Creates a logic spike on an given location on the given world
     * @param locationX
     * @param locationY
     */
    SpikeLogic(double locationX, double locationY, World&);

    /***
     * checks if there is a collision with the doodle using the "collisionDooldle" varible
     * When there is updates the hp of the doodle and resets the jump
     */
    void update() override;
};

class AddHpLogic: public BonusesLogic{
    std::string custumTexture = "";
    int hpPoints = 1;
public:
    /***
     * Creates a logic hp bubble on an given location on the given world
     * @param locationX
     * @param locationY
     */
    AddHpLogic(double locationX, double locationY, World&);

    /***
     * checks if there is a collision with the doodle using the "collisionDooldle" varible
     * - When there is updates the hp of the doodle and resets the jump
     * - updates the hp points of the bubble and updates the texture
     */
    void update() override;

    /***
     * Function to get the current changed texture, if not changed it's an empty string
     * @return
     */
    std::string getCustumTexture() override;
};

class BulletLogic: public EntityLogic{
private:
    bool reverseBullet = false;

    /***
     * Updates the location of the bullet (add a fixed speed in the direction specified ad creation)
     */
    void updateLocation();
public:
    /***
     * Create a logic bullet on a specified location an specified
     * @param locationX
     * @param locationY
     * @param world
     * @param reverseBullet (of true the bullet will go down instead of going up)
     */
    BulletLogic(double locationX, double locationY, World& world, bool reverseBullet = false);

    /***
     * checks if bullet collisions with enemies (if reverseBullet is false)
     * check if bullet collisions with doodle of the same world (if reverseBullet is true)
     * @param enemies vector of enemies
     * @return true by a collision otherwise false
     */
    bool checkEnemyCollisions(std::vector<std::shared_ptr<EnemyLogic>>& enemies);

    /***
     * updates the location of the bullet and than a call to all observers (representation of the bullet)
     */
    void update() override;
};

class PlatformLogic: public EntityLogic{
private:
    int hexColor = 0x229900ff;
    std::shared_ptr<PlatformItem> bonus = nullptr;
protected:
    /***
     * Set the color of the platform
     * @param hexColor 0x229900ff
     */
    void setHexColor(int hexColor);
public:
    /***
     * static information about the platform (can be used everywhere)
     */
    constexpr static const double platformHeight = 20;
    constexpr static const double platformWidth = 100;

    /***
     * Creates a default green platform on a specified location
     * @param locationX
     * @param locationY
     * @param world
     */
    PlatformLogic(double locationX, double locationY, World& world);

    /***
     * Gives the max y location of the platform (= platform height)
     * @return platform height
     */
    virtual double getMaxYLocation() const;

    /***
     * Gives the min y location of the platform (= platform height)
     * @return platform height
     */
    virtual double getMinYLocation() const;

    /***
     * Returns the color of the platform
     * @return
     */
    virtual int getColor() const;

    /***
     * update the PlatformItems on the platform and updates the representation of the platform and platform item
     */
    void update() override;

    /***
     * Removes platform item from platform
     */
    void removeItem();
};

class MovePlatformLogic: public PlatformLogic{
protected:
    const float timeLoop = 100;
    double frameCounter = 0;
    double maxYLocation = 0;
    double minYLocation = 0;
    std::function<double (double)> const movementXOverTime;
    std::function<double (double)> const movementYOverTime;

    /***
     * Creates a moving platform (up/down) (protected because it must be a specified moving platform)
     * @param locationX (start location)
     * @param locationY (start location)
     * @param frameAmount (amount of frames for movement)
     * @param movementXOverTime (function to move the x over with frameAmount)
     * @param movementYOverTime (function to move the y over with frameAmount)
     */
    MovePlatformLogic(double locationX, double locationY, World&, double frameAmount, std::function<double (double)> movementXOverTime, std::function<double (double)> movementYOverTime);
public:
    /***
     * updates the moving platform to the new location and updates the representation (observers)
     */
    void update() override;

    /***
     * returns the max location of the platform taking into account the animation
     * @return max location
     */
    double getMaxYLocation() const override;

    /***
     * returns the min location of the platform taking into account the animation
     * @return min location
     */
    double getMinYLocation() const override;
};

class HorizontalPlatformLogic: public MovePlatformLogic{
public:
    /***
     * Creates a horizontal moving platform
     * @param locationX start x location
     * @param locationY start y location
     */
    HorizontalPlatformLogic(double locationX, double locationY, World&);
};

class VerticalPlatformLogic: public MovePlatformLogic{
public:
    /***
     * Creates a vertical moving platform
     * @param locationX start x location
     * @param locationY start y location
     */
    VerticalPlatformLogic(double locationX, double locationY, World&);
};

class VerticalRandomPlatformLogic: public PlatformLogic{
public:
    /***
     * Creates a vertical random moving platform (jumps to a random location within the size of the VerticalPlatformLogic)
     * @param locationX start x location
     * @param locationY start y location
     */
    VerticalRandomPlatformLogic(double locationX, double locationY, World&);

    /***
     * updates the platform to the new location and calls update of the base class PlaformLogic
     */
    void update() override;
};

class HorizontalRandomPlatformLogic: public PlatformLogic{
public:
    /***
     * Creates a horizontal random moving platform (jumps to a random location within the size of the HorizontalRandomPlatformLogic)
     * @param locationX start x location
     * @param locationY start y location
     */
    HorizontalRandomPlatformLogic(double locationX, double locationY, World&);

    /***
     * updates the platform to the new location and calls update of the base class PlaformLogic
     */
    void update() override;
};

class TemporaryPlatformLogic: public PlatformLogic{
public:
    /***
     * Creates a platfrom when jumped on it will disappear
     * @param locationX
     * @param locationY
     * @param world
     */
    TemporaryPlatformLogic(double locationX, double locationY, World& world);

    /***
     * Check if the variable "collisionDooldle" and than moves platform to possition 0,0 and size 0,0 is true
     * and calls update of the base class PlaformLogic
     */
    void update() override;
};

class BGTileLogic: public EntityLogic{
private:
std::vector<int> horizontalLines;
public:
    /***
     * Creates the logics for the background grid layout
     * @param world
     */
    explicit BGTileLogic(World& world);

    /***
     * updates the horizontal lines and updates the observers
     */
    void update() override;

    /***
     * function that returns the horizontal lines
     * @return vector of the horizontal lines
     */
    std::vector<int> getHorizontalLines() override;
};

class StartScreenLogic: public EntityLogic{
public:
    /***
     * Function to create a startscreen
     * @param world
     */
    StartScreenLogic(World& world);

    /***
     * updates the observers (representation)
     */
    void update() override;
};

class DoodlerLogic: public EntityLogic{
protected:
    float upValue = jumpHeight;
    bool up = true;
    bool facingLeft = false;
    double speed = 3;
    std::string custumTexture = "";
    int hp = 3;
    double flashSec = 0;

    /***
     * Function to set flashSec (this are the sec to change the color of the enemy)
     * @param timeInSec
     */
    void makeDark(double timeInSec);
public:
    /***
     * static information about the logic doodle (can be used everywhere)
     */
    constexpr static const double jumpHeight = 200;
    constexpr static const double doodleHeight = 109;
    constexpr static const double doodleWidth = 55;

    /***
     * Function to create a doodle for a given world
     * @param world
     */
    explicit DoodlerLogic(World& world);

    /***
     * Moves the doodle left by a fixed amount
     */
    void moveLeft();

    /***
     * Moves the doodle right by a fixed amount
     */
    void moveRight();

    /***
     * Updates the hight of the doodle (jumps) and the observers (representation)
     */
    void update() override;

    /***
     * Function to reset the jump (does not work when doodle has no hp anymore and resets the custom texture)
     */
    void resetJump();

    /***
     * Changes the jump hight until the jump is reset, and updates the jump
     * @param jumpHight
     */
    void updateJumpHight(double jumpHight);

    /***
     * function to give doodle an other texture
     * @param texturePath
     */
    void setCustumTexture(std::string texturePath);

    /***
     * Function to get the current changed texture, if not changed it's an empty string
     * @return
     */
    std::string getCustumTexture() override;

    /***
     * Function that returns True if flashSec are not passed
     * @return True/False
     */
    bool darkTexture() override;

    /***
     * Resets the custum texture to default
     */
    void resetCustumTexture();

    /***
     * Boolean to get te facing side of the doodle
     * @return True (if left)
     */
    bool isFacingLeft() override;

    /***
     * Checks if logic doodle collisions with an platform and if doodle is going down
     * reset jump of logic doodle and returns true when collisions
     * @param vector of logic platforms
     * @return
     */
    bool checkPlatformCollisions(std::vector<std::shared_ptr<PlatformLogic>> objects);

    /***
     * Checks if logic doodle collisions with an bonus and if doodle is going down
     * returns true when collisions
     * @param vector of logic bonnuses
     * @return
     */
    bool checkBonusCollisions(std::vector<std::shared_ptr<BonusesLogic>> objects);

    /***
     * Checks if logic doodle collisions with an enemy
     * returns true when collisions
     * @param vector of logic enemies
     * @return
     */
    bool checkEnemyCollisions(std::vector<std::shared_ptr<EnemyLogic>> objects);

    /***
     * Function to change the current hp of the doodle
     * @param hp
     */
    void addHp(int hp = 1);

    /***
     * Function that:
     * - decreases the score of the game
     * - decreases the hp of the doodle
     * - set a flash
     */
    void hitByEnemy();

    /***
     * returns the x location from where bullets shot from the doodle start
     * @return x location
     */
    int getBulletLocationX();

    /***
     * returns the y location from where bullets shot from the doodle start
     * @return y location
     */
    int getBulletLocationY();

    /***
     * returns the current hp
     * @return
     */
    int getHp();
};

/***
 * function for collision detection between two logic entities
 * @param entity1
 * @param entity2
 * @return
 */
bool collisionsDetection(EntityLogic& entity1, EntityLogic& entity2);



#endif //TESTREPO_ENTITYMODEL_H
