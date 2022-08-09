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
    DoodlerLogic& getDoodle();
    std::shared_ptr<Stopwatch> getStopwatch();
    //const std::vector<PlatformLogic*>& getPlatforms() const;
    std::shared_ptr<BonusesLogic> createSpring(PlatformLogic& platform);
    std::shared_ptr<BonusesLogic> createJetPack(PlatformLogic& platform);
    virtual std::shared_ptr<Enemy0Logic> createEnemy0(PlatformLogic& platform);
    //DoodlerLogic* getDoodleLogic() const;
private:
    std::shared_ptr<Score> score;
    std::shared_ptr<DoodlerLogic> doodler;
    std::shared_ptr<BGTileLogic> bgTile;
    std::vector<std::shared_ptr<PlatformLogic>> platforms;
    std::vector<std::shared_ptr<BonusesLogic>> bonussen;
    std::vector<std::shared_ptr<EnemyLogic>> enemies;
    Camera camera;
    Random* random;
    IWindow& window;
    AbstractFactory& factory;
    std::shared_ptr<Stopwatch> stopwatch = stopwatch->getInstance();

    void generatePlatforms();
    void removePlatforms();
    void updatePlatforms();
    std::shared_ptr<PlatformLogic> getRandomPlatform(double platformXLocation, double platformYLocation);
};


#endif //TESTREPO_WORLD_H
