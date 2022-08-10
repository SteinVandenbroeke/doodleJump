//
// Created by stein on 24/11/2021.
//

#include "ConcreteFactory.h"

ConcreteFactory::ConcreteFactory(sf::RenderWindow& window): window(window) {
}

std::shared_ptr<DoodlerLogic> ConcreteFactory::createDoodler(World& world) {
    std::shared_ptr<DoodlerLogic> doodlerLogic = std::make_shared<DoodlerLogic>(world);
    std::cout << "doodle logic created" << std::endl;
    new Doodler(*doodlerLogic, window);
    return doodlerLogic;
}

std::shared_ptr<PlatformLogic> ConcreteFactory::createPlatform(double locationX, double locationY,World& world) {
    std::shared_ptr<PlatformLogic> platoformLogic = std::make_shared<PlatformLogic>(locationX,locationY,world);
    new Platform(*platoformLogic, window);
    return platoformLogic;
}

std::shared_ptr<HorizontalPlatformLogic> ConcreteFactory::createHorizontalPlatform(double locationX, double locationY,World& world) {
    std::shared_ptr<HorizontalPlatformLogic> platoformLogic = std::make_shared<HorizontalPlatformLogic>(locationX,locationY,world);
    new Platform(*platoformLogic, window);
    return platoformLogic;
}
std::shared_ptr<VerticalPlatformLogic> ConcreteFactory::createVerticalPlatform(double locationX, double locationY,World& world) {
    std::shared_ptr<VerticalPlatformLogic> platoformLogic = std::make_shared<VerticalPlatformLogic>(locationX,locationY,world);
    new Platform(*platoformLogic, window);
    return platoformLogic;
}
std::shared_ptr<TemporaryPlatformLogic> ConcreteFactory::createTemporaryPlatform(double locationX, double locationY,World& world) {
    std::shared_ptr<TemporaryPlatformLogic> platoformLogic = std::make_shared<TemporaryPlatformLogic>(locationX,locationY,world);
    new Platform(*platoformLogic, window);
    return platoformLogic;
}
std::shared_ptr<VerticalRandomPlatformLogic> ConcreteFactory::createVerticalRandomPlatform(double locationX, double locationY,World& world) {
    std::shared_ptr<VerticalRandomPlatformLogic> platoformLogic = std::make_shared<VerticalRandomPlatformLogic>(locationX,locationY,world);
    new Platform(*platoformLogic, window);
    return platoformLogic;
}

std::shared_ptr<HorizontalRandomPlatformLogic> ConcreteFactory::createHorizontalRandomPlatform(double locationX, double locationY,World& world) {
    std::shared_ptr<HorizontalRandomPlatformLogic> platoformLogic = std::make_shared<HorizontalRandomPlatformLogic>(locationX,locationY,world);
    new Platform(*platoformLogic, window);
    return platoformLogic;
}

std::shared_ptr<SpringLogic> ConcreteFactory::createSpring(double locationX, double locationY, World &world) {
    std::shared_ptr<SpringLogic> springLogic = std::make_shared<SpringLogic>(locationX,locationY,world);
    new Spring(*springLogic, window);
    return springLogic;
}

std::shared_ptr<JetpackLogic> ConcreteFactory::createJetpack(double locationX, double locationY, World &world) {
    std::shared_ptr<JetpackLogic> jetpackLogic = std::make_shared<JetpackLogic>(locationX,locationY,world);
    new Jetpack(*jetpackLogic, window);
    return jetpackLogic;
}

std::shared_ptr<SpikeLogic> ConcreteFactory::createSpike(double locationX, double locationY, World &world) {
    std::shared_ptr<SpikeLogic> spike = std::make_shared<SpikeLogic>(locationX,locationY,world);
    new Spike(*spike, window);
    return spike;
}

std::shared_ptr<AddHpLogic> ConcreteFactory::createAddHp(double locationX, double locationY, World &world) {
    std::shared_ptr<AddHpLogic> addHp = std::make_shared<AddHpLogic>(locationX,locationY,world);
    new AddHp(*addHp, window);
    return addHp;
}

std::shared_ptr<BGTileLogic> ConcreteFactory::createBGTile(World &world) {
    std::shared_ptr<BGTileLogic> bgTileLogic = std::make_shared<BGTileLogic>(world);
    new BGTile(*bgTileLogic, window);
    return bgTileLogic;
}
std::shared_ptr<Score> ConcreteFactory::createScore(World &world) {
    std::shared_ptr<Score> score = std::make_shared<Score>(world);
    new ScoreLabel(*score, window);
    return score;
}
std::shared_ptr<Enemy0Logic> ConcreteFactory::createEnemy0(PlatformLogic& platform, World &world) {
    std::shared_ptr<Enemy0Logic> enemie0 = std::make_shared<Enemy0Logic>(platform,world);
    new Enemy0(*enemie0, window);
    return enemie0;
}
std::shared_ptr<Enemy1Logic> ConcreteFactory::createEnemy1(PlatformLogic &platform, World &world) {
    std::shared_ptr<Enemy1Logic> enemie1 = std::make_shared<Enemy1Logic>(platform,world);
    new Enemy1(*enemie1, window);
    return enemie1;
}
std::shared_ptr<BulletLogic> ConcreteFactory::createBullet(double locationX, double locationY, World &world, bool reverseBullet) {
    std::shared_ptr<BulletLogic> bullet = std::make_shared<BulletLogic>(locationX,locationY,world, reverseBullet);
    new Bullet(*bullet, window);
    return bullet;
}

std::shared_ptr<StartScreenLogic> ConcreteFactory::createStartScreen(World &world) {
    std::shared_ptr<StartScreenLogic> startScreen = std::make_shared<StartScreenLogic>(world);
    new StartScreen(*startScreen, window);
    return startScreen;
}
