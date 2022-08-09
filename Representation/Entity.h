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
    Entity(std::shared_ptr<EntityLogic> logicEntity, sf::RenderWindow& window);
    virtual void draw() = 0;
};

class TextureEntity: public Entity{
protected:
    sf::Sprite entityGrahic;
    sf::Texture texture;
public:
    TextureEntity(std::shared_ptr<EntityLogic> logicEntity, sf::RenderWindow& window, const char* texture);
    void update() override;
    void draw() override;
};

class Doodler: public TextureEntity{
public:
    Doodler(std::shared_ptr<DoodlerLogic> logicEntity, sf::RenderWindow& window);
    void update() override;
    void draw() override;
};

class Enemy0: public TextureEntity {
public:
    Enemy0(std::shared_ptr<Enemy0Logic> logicEntity, sf::RenderWindow& window);
};

/*
class Enemy1: public TextureEntity {
public:
    Enemy1(std::shared_ptr<Enemy1Logic> logicEntity, sf::RenderWindow& window);
    void update() override;
    void draw() override;
};
*/

class Platform: public Entity{
    sf::RectangleShape* entityGrahic;
public:
    Platform(std::shared_ptr<PlatformLogic> logicEntity, sf::RenderWindow& window);//const .. const TODO
    void update() override;
    void draw() override;
};

class Spring: public TextureEntity{
public:
    Spring(std::shared_ptr<SpringLogic> logicSpring, sf::RenderWindow& window);
};

class Jetpack: public TextureEntity{
public:
    Jetpack(std::shared_ptr<JetpackLogic> logicJetpack, sf::RenderWindow& window);
};

class BGTile: public Entity{
protected:
    std::vector<std::unique_ptr<sf::RectangleShape>> entityGrahic;
public:
    BGTile(std::shared_ptr<BGTileLogic> logicEntity, sf::RenderWindow& window);
    void update() override;
    void draw() override;
};

class Label: public Entity{
private:
    sf::Font font;

protected:
    sf::Text text;

public:
    Label(std::shared_ptr<Score> logicEntity, sf::RenderWindow& window);
    void draw() override;
};

class ScoreLabel: public Label{
public:
    ScoreLabel(std::shared_ptr<Score> logicEntity, sf::RenderWindow& window);
    void update() override;
};

class HpLabel: public Label{
public:
    HpLabel(std::shared_ptr<Score> logicEntity, sf::RenderWindow& window);
    void update() override;
};

#endif //TESTREPO_ENTITY_H
