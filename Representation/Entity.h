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
    Entity(EntityLogic& logicEntity, sf::RenderWindow& window);
public:
    virtual void draw() = 0;
};

class TextureEntity: public Entity{
protected:
    sf::Sprite entityGrahic;
    sf::Texture texture;
    TextureEntity(EntityLogic& logicEntity, sf::RenderWindow& window, const char* texture);
public:
    /***
     * Updates the location of the representative entity to the logic entity and calls the draw function
     */
    void update() override;

    /***
     * draw the doodle to the screen
     */
    void draw() override;
};

class Doodler: public TextureEntity{
public:
    /***
     * Creates a representative doodle item linked with the logic doodle with the observer
     * @param logicEntity
     * @param window
     */
    Doodler(DoodlerLogic& logicEntity, sf::RenderWindow& window);

    /***
     * Set location of representative doodle to the logic and calls the draw function
     */
    void update() override;

    /***
     * draw the doodle to the screen
     */
    void draw() override;
};

class Enemy0: public TextureEntity {
public:
    /***
     * Creates a representative enemy 0 item linked with the logic enemy 0 with the observer
     * @param logicEntity
     * @param window
     */
    Enemy0(Enemy0Logic& logicEntity, sf::RenderWindow& window);
};

class Enemy1: public TextureEntity {
public:
    /***
     * Creates a representative enemy 1 item linked with the logic enemy 1 with the observer
     * @param logicEntity
     * @param window
     */
    Enemy1(Enemy1Logic& logicEntity, sf::RenderWindow& window);
};

class Platform: public Entity{
    sf::RectangleShape* entityGrahic;
public:
    /***
     * Creates a representative platform  linked with a logic platform (any type) linked with the observer
     * @param logicEntity
     * @param window
     */
    Platform(PlatformLogic& logicEntity, sf::RenderWindow& window);

    /***
     * Set location of representative doodle to the logic and calls the draw function
     */
    void update() override;
    void draw() override;
};

class Spring: public TextureEntity{
public:
    /***
     * Creates a representative spring item linked to the logic spring with the observer
     * @param logicSpring
     * @param window
     */
    Spring(SpringLogic& logicSpring, sf::RenderWindow& window);
};

class Jetpack: public TextureEntity{
public:
    /***
     * Creates a representative jetpack item linked to the logic jetpack with the observer
     * @param logicJetpack
     * @param window
     */
    Jetpack(JetpackLogic& logicJetpack, sf::RenderWindow& window);
};

class Spike: public TextureEntity{
public:
    /***
     * Creates a representative spike item linked to the logic spike with the observer
     * @param logicJetpack
     * @param window
     */
    Spike(SpikeLogic& logicJetpack, sf::RenderWindow& window);
};

class AddHp: public TextureEntity{
public:
    /***
     * Creates a representative hp bubble item linked to the logic hp bubble with the observer
     * @param logicJetpack
     * @param window
     */
    AddHp(AddHpLogic& logicJetpack, sf::RenderWindow& window);
    void update() override;
};

class BGTile: public Entity{
protected:
    std::vector<std::unique_ptr<sf::RectangleShape>> entityGrahic;
public:
    /***
     * Creates a representative background linked to the logic background with the observer
     * @param logicEntity
     * @param window
     */
    BGTile(BGTileLogic& logicEntity, sf::RenderWindow& window);
    void update() override;
    void draw() override;
};

class Label: public Entity{
private:
    sf::Font font;

protected:
    sf::Text text;
    Label(EntityLogic& logicEntity, sf::RenderWindow& window, int locationX, int locationY);
public:
    /***
     * places the label on the window
     */
    void draw() override;
};

class ScoreLabel: public Label{
public:
    /***
     * Creates a representative score label linked to the score class with the observer
     * @param logicEntity
     * @param window
     */
    ScoreLabel(Score& logicEntity, sf::RenderWindow& window);

    /***
     * updates the labels to the current scores and calls the draw function
     */
    void update() override;
};

class Bullet: public Entity{
    sf::CircleShape* entityGrahic;
public:
    /***
     * Creates a representative bullet linked to the logic bullet with the observer
     * @param logicEntity
     * @param window
     */
    Bullet(BulletLogic& logicEntity, sf::RenderWindow& window);

    /***
     * Set location of representative bullet to the logic bullet and calls the draw function
     */
    void update() override;
    void draw() override;
};

class StartScreen: public Entity{
    sf::Font font;
    sf::Text title;
    sf::Text hightScore;
    sf::Text instructions;
public:
    /***
     * Creates the start screen with all labels
     * @param logicEntity
     * @param window
     */
    StartScreen(StartScreenLogic& logicEntity, sf::RenderWindow& window);

    /***
     * Set all labels to the correct values and calls the draw function
     */
    void update() override;
    void draw() override;
};

#endif //TESTREPO_ENTITY_H
