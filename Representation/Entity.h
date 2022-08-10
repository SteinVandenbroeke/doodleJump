//
// Created by stein on 18/11/2021.
//

#ifndef TESTREPO_ENTITY_H
#define TESTREPO_ENTITY_H

#include "../Logic/EntityLogic.h"
#include "../Logic/Score.h"
#include "../Logic/World.h"
#include <SFML/Graphics.hpp>

class Entity: public EntityObserver{
protected:
    sf::RenderWindow& window;
public:
    Entity(EntityLogic& logicEntity, sf::RenderWindow& window);
    virtual void draw() = 0;
};

class TextureEntity: public Entity{
protected:
    sf::Sprite entityGrahic;
    sf::Texture texture;
public:
    TextureEntity(EntityLogic& logicEntity, sf::RenderWindow& window, const char* texture);
    void update() override;
    void draw() override;
};

class Doodler: public TextureEntity{
public:
    Doodler(DoodlerLogic& logicEntity, sf::RenderWindow& window);
    void update() override;
    void draw() override;
};

class Enemy0: public TextureEntity {
public:
    Enemy0(Enemy0Logic& logicEntity, sf::RenderWindow& window);
};

class Enemy1: public TextureEntity {
public:
    Enemy1(Enemy1Logic& logicEntity, sf::RenderWindow& window);
};

class Platform: public Entity{
    sf::RectangleShape* entityGrahic;
public:
    Platform(PlatformLogic& logicEntity, sf::RenderWindow& window);//const .. const TODO
    void update() override;
    void draw() override;
};

class Spring: public TextureEntity{
public:
    Spring(SpringLogic& logicSpring, sf::RenderWindow& window);
};

class Jetpack: public TextureEntity{
public:
    Jetpack(JetpackLogic& logicJetpack, sf::RenderWindow& window);
};

class Spike: public TextureEntity{
public:
    Spike(SpikeLogic& logicJetpack, sf::RenderWindow& window);
};

class AddHp: public TextureEntity{
public:
    AddHp(AddHpLogic& logicJetpack, sf::RenderWindow& window);
    void update() override;
};

class BGTile: public Entity{
protected:
    std::vector<std::unique_ptr<sf::RectangleShape>> entityGrahic;
public:
    BGTile(BGTileLogic& logicEntity, sf::RenderWindow& window);
    void update() override;
    void draw() override;
};

class Label: public Entity{
private:
    sf::Font font;

protected:
    sf::Text text;

public:
    Label(EntityLogic& logicEntity, sf::RenderWindow& window, int locationX, int locationY);
    void draw() override;
};

class ScoreLabel: public Label{
public:
    ScoreLabel(Score& logicEntity, sf::RenderWindow& window);
    void update() override;
};

class Bullet: public Entity{
    sf::CircleShape* entityGrahic;
public:
    Bullet(BulletLogic& logicEntity, sf::RenderWindow& window);
    void update() override;
    void draw() override;
};

class StartScreen: public Entity{
    sf::Font font;
    sf::Text title;
    sf::Text hightScore;
    sf::Text instructions;
public:
    StartScreen(StartScreenLogic& logicEntity, sf::RenderWindow& window);
    void update() override;
    void draw() override;
};

#endif //TESTREPO_ENTITY_H
