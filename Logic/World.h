//
// Created by stein on 18/11/2021.
//

#ifndef TESTREPO_WORLD_H
#define TESTREPO_WORLD_H
#include "Camera.h"
#include "EntityLogic.h"
#include "IWindow.h"
#include "Score.h"
#include "math.h"
#include <vector>

class AbstractFactory;
class World {
public:
    /***
     * Create a new game world
     * @param window the window to render
     * @param factory the factory to generate entities
     */
    World(IWindow& window, AbstractFactory& factory);

    /***
     * Update all entity's in the world. and checks for collisions
     * Must run for every frame
     * return's false when player dies
     */
    bool update();

    /***
     * The game loop
     */
    void gameLoop();

    /***
     * Function that returns the Camera
     * @return Camera
     */
    const Camera& getCamera() const;

    /***
     * Function that returns the random used in this world
     * @return Random
     */
    const Random& getRandom() const;

    /***
     * Function that returns the score counter of this world
     * @return Score
     */
    Score& getScore();

    /***
     * Function that returns the doodle (player) of this world
     * @return Doodle
     */
    DoodlerLogic& getDoodle();

    /***
     * Function that returns the stopwatch used this world
     * @return stopwatch
     */
    std::shared_ptr<Stopwatch> getStopwatch();

    /***
     * Function that creates a new spring in this world on a given platform using the factory class
     * @param platform (to place on)
     * @return pointer to the created Spring
     */
    std::shared_ptr<BonusesLogic> createSpring(PlatformLogic& platform);

    /***
     * Function that creates a new jetpack in this world on a given platform using the factory class
     * @param platform (to place on)
     * @return pointer to the created jetpack
     */
    std::shared_ptr<BonusesLogic> createJetPack(PlatformLogic& platform);

    /***
     * Function that creates a new spike in this world on a given platform using the factory class
     * @param platform (to place on)
     * @return pointer to the created spike
     */
    std::shared_ptr<BonusesLogic> createSpike(PlatformLogic& platform);

    /***
     * Function that creates a new hpBuble in this world on a given platform using the factory class
     * @param platform (to place on)
     * @return pointer to the created AddHpLogic
     */
    std::shared_ptr<BonusesLogic> createAddHp(PlatformLogic& platform);

    /***
     * Function that creates a new enemy (type0) in this world on a given platform using the factory class
     * @param platform (to place on)
     * @return pointer to the created enemy
     */
    std::shared_ptr<Enemy0Logic> createEnemy0(PlatformLogic& platform);

    /***
     * Function that creates a new enemy (type 1) in this world on a given platform using the factory class
     * @param platform (to place on)
     * @return pointer to the created enemy
     */
    std::shared_ptr<Enemy1Logic> createEnemy1(PlatformLogic& platform);

    /***
     * Function that creates a bullet from a doodle
     * @param doodlerLogic the doodle that is shooting
     */
    void createBullet(DoodlerLogic& doodlerLogic);

    /***
     * Function that creates a bullet from a enemy
     * @param doodlerLogic the enemy that is shooting
     */
    void createBullet(EnemyLogic& enemyLogic);
private:
    std::shared_ptr<Score> score;
    std::shared_ptr<DoodlerLogic> doodler;
    std::shared_ptr<BGTileLogic> bgTile;
    std::shared_ptr<StartScreenLogic> startscreen;
    std::vector<std::shared_ptr<PlatformLogic>> platforms;
    std::vector<std::shared_ptr<BonusesLogic>> bonussen;
    std::vector<std::shared_ptr<EnemyLogic>> enemies;
    std::vector<std::shared_ptr<BulletLogic>> bullets;
    std::vector<std::shared_ptr<BulletLogic>> reversebullets;
    Camera camera;
    std::shared_ptr<Random> random = random->getInstance();
    IWindow& window;
    AbstractFactory& factory;
    std::shared_ptr<Stopwatch> stopwatch = stopwatch->getInstance();
    bool continuShootBlock = false;
    bool started = false;

    /***
     * Function that fills the world with platforms if there are places that can nog be reached
     */
    void generatePlatforms();

    /***
     * Function that removes platforms that reach the bottom of the screen
     */
    void removePlatforms();

    /***
     * Function that updates all platforms in the world
     */
    void updatePlatforms();

    /***
     * Function that generates a random (type) platform on a specified location using the factory class
     * @param platformXLocation
     * @param platformYLocation
     * @return the created platform
     */
    std::shared_ptr<PlatformLogic> getRandomPlatform(double platformXLocation, double platformYLocation);

    /***
     * Function that updates/removes all bullets in the world
     */
    void updateBullets();
};


#endif //TESTREPO_WORLD_H
