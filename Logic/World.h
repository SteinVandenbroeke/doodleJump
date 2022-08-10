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
    World(IWindow& window, AbstractFactory& factory);

    /***
     * Update all entity's in the world and connected reaction,
     * return's false when player dies
     */
    bool update();
    //Camera* getCamera();
    const Camera& getCamera() const;
    const Random& getRandom() const;
    Score& getScore();
    DoodlerLogic& getDoodle();
    std::shared_ptr<Stopwatch> getStopwatch();
    //const std::vector<PlatformLogic*>& getPlatforms() const;
    std::shared_ptr<BonusesLogic> createSpring(PlatformLogic& platform);
    std::shared_ptr<BonusesLogic> createJetPack(PlatformLogic& platform);
    std::shared_ptr<BonusesLogic> createSpike(PlatformLogic& platform);
    std::shared_ptr<BonusesLogic> createAddHp(PlatformLogic& platform);
    std::shared_ptr<Enemy0Logic> createEnemy0(PlatformLogic& platform);
    std::shared_ptr<Enemy1Logic> createEnemy1(PlatformLogic& platform);
    void createBullet(DoodlerLogic& doodlerLogic);
    void createBullet(EnemyLogic& enemyLogic);
    //DoodlerLogic* getDoodleLogic() const;
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
    Random* random;
    IWindow& window;
    AbstractFactory& factory;
    std::shared_ptr<Stopwatch> stopwatch = stopwatch->getInstance();
    bool continuShootBlock = false;
    bool started = false;

    void generatePlatforms();
    void removePlatforms();
    void updatePlatforms();

    void updateBullets();
    std::shared_ptr<PlatformLogic> getRandomPlatform(double platformXLocation, double platformYLocation);
};


#endif //TESTREPO_WORLD_H
