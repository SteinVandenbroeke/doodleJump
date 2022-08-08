//
// Created by stein on 18/11/2021.
//

#ifndef TESTREPO_WORLD_H
#define TESTREPO_WORLD_H
#include "EntityLogic.h"
#include <vector>
#include "Camera.h"
#include "math.h"
#include "IWindow.h"

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
    //DoodlerLogic* getDoodleLogic() const;
private:
    std::shared_ptr<DoodlerLogic> doodler;
    std::shared_ptr<BGTileLogic> bgTile;
    std::vector<std::shared_ptr<PlatformLogic>> platforms;
    std::vector<std::shared_ptr<BonusesLogic>> bonussen;
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
