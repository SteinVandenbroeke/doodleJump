//
// Created by stein on 24/11/2021.
//

#ifndef DOODLE_JUMP_ABSTRACTFACTORY_H
#define DOODLE_JUMP_ABSTRACTFACTORY_H
#include "Score.h"
#include "World.h"

/***
 * AbstractFactory for creating logic entities liked to a representative entity
 */
class AbstractFactory {
public:
    virtual std::shared_ptr<DoodlerLogic> createDoodler(World& world) = 0;
    virtual std::shared_ptr<PlatformLogic> createPlatform(double locationX, double locationY,World& world) = 0;
    virtual std::shared_ptr<HorizontalPlatformLogic> createHorizontalPlatform(double locationX, double locationY,World& world) = 0;
    virtual std::shared_ptr<VerticalPlatformLogic> createVerticalPlatform(double locationX, double locationY,World& world) = 0;
    virtual std::shared_ptr<TemporaryPlatformLogic> createTemporaryPlatform(double locationX, double locationY,World& world) = 0;
    virtual std::shared_ptr<VerticalRandomPlatformLogic> createVerticalRandomPlatform(double locationX, double locationY,World& world) = 0;
    virtual std::shared_ptr<HorizontalRandomPlatformLogic> createHorizontalRandomPlatform(double locationX, double locationY,World& world) = 0;
    virtual std::shared_ptr<Enemy0Logic> createEnemy0(PlatformLogic& platform,World& world) = 0;
    virtual std::shared_ptr<Enemy1Logic> createEnemy1(PlatformLogic& platform, World& world) = 0;
    virtual std::shared_ptr<SpringLogic> createSpring(double locationX, double locationY,World& world) = 0;
    virtual std::shared_ptr<JetpackLogic> createJetpack(double locationX, double locationY,World& world) = 0;
    virtual std::shared_ptr<SpikeLogic> createSpike(double locationX, double locationY,World& world) = 0;
    virtual std::shared_ptr<AddHpLogic> createAddHp(double locationX, double locationY,World& world) = 0;
    virtual std::shared_ptr<BGTileLogic> createBGTile(World& world) = 0;
    virtual std::shared_ptr<StartScreenLogic> createStartScreen(World& world) = 0;
    virtual std::shared_ptr<Score> createScore(World& world) = 0;
    virtual std::shared_ptr<BulletLogic> createBullet(double locationX, double locationY, World& world, bool reverseBullet) = 0;
};
#endif //DOODLE_JUMP_ABSTRACTFACTORY_H
