//
// Created by stein on 24/11/2021.
//

#ifndef DOODLE_JUMP_CONCRETEFACTORY_H
#define DOODLE_JUMP_CONCRETEFACTORY_H

#include <vector>
#include "../Logic/AbstractFactory.h"
#include "Entity.h"

/***
 * ConcreteFactory for creating logic entities liked to a representative entity
 */
class ConcreteFactory: public AbstractFactory{
private:
    sf::RenderWindow& window;
public:
    ConcreteFactory(sf::RenderWindow& window);

    std::shared_ptr<DoodlerLogic> createDoodler(World& world) override;
    std::shared_ptr<PlatformLogic> createPlatform(double locationX, double locationY,World& world) override;
    std::shared_ptr<HorizontalPlatformLogic> createHorizontalPlatform(double locationX, double locationY,World& world) override;
    std::shared_ptr<VerticalPlatformLogic> createVerticalPlatform(double locationX, double locationY,World& world) override;
    std::shared_ptr<TemporaryPlatformLogic> createTemporaryPlatform(double locationX, double locationY,World& world) override;
    std::shared_ptr<VerticalRandomPlatformLogic> createVerticalRandomPlatform(double locationX, double locationY,World& world) override;
    std::shared_ptr<HorizontalRandomPlatformLogic> createHorizontalRandomPlatform(double locationX, double locationY,World& world) override;
    std::shared_ptr<Enemy0Logic> createEnemy0(PlatformLogic& platform, World& world) override;
    std::shared_ptr<Enemy1Logic> createEnemy1(PlatformLogic& platform, World& world) override;
    std::shared_ptr<SpringLogic> createSpring(double locationX, double locationY,World& world) override;
    std::shared_ptr<JetpackLogic> createJetpack(double locationX, double locationY,World& world) override;
    std::shared_ptr<SpikeLogic> createSpike(double locationX, double locationY,World& world) override;
    std::shared_ptr<AddHpLogic> createAddHp(double locationX, double locationY,World& world) override;
    std::shared_ptr<BGTileLogic> createBGTile(World& world) override;
    std::shared_ptr<StartScreenLogic> createStartScreen(World& world) override;
    std::shared_ptr<Score> createScore(World& world) override;
    std::shared_ptr<BulletLogic> createBullet(double locationX, double locationY, World& world, bool reverseBullet = false) override;
};

#endif //DOODLE_JUMP_CONCRETEFACTORY_H
