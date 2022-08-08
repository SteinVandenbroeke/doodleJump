//
// Created by stein on 18/11/2021.
//

#include "Entity.h"

Entity::Entity(std::shared_ptr<EntityLogic> logicEntity, sf::RenderWindow &window): EntityObserver(logicEntity), window(window) {

}

TextureEntity::TextureEntity(std::shared_ptr<EntityLogic> logicEntity, sf::RenderWindow &window, const char* texturePath): Entity(logicEntity, window) {
    entityGrahic = sf::Sprite();
    std::cout << texturePath << std::endl;
    if (!texture.loadFromFile(texturePath))
    {
        throw "Texturemap not found";
    }
    entityGrahic.setTexture(texture);
    entityGrahic.setScale(1,1);
    //playerGrahic->setColor(sf::Color::Red);

    std::pair<float, float> newLocation = this->logicEntity->getWorld().getCamera().coordinateToPixel(this->logicEntity->getLocation(), this->logicEntity);
    entityGrahic.setPosition(newLocation.first, newLocation.second);
}
void TextureEntity::update() {
    std::pair<float, float> newLocation = this->logicEntity->getWorld().getCamera().coordinateToPixel(this->logicEntity->getLocation(), this->logicEntity);
    entityGrahic.setPosition(newLocation.first, newLocation.second);
    this->draw();
}

void TextureEntity::draw() {
    this->window.draw(this->entityGrahic);
}

Doodler::Doodler(std::shared_ptr<DoodlerLogic> logicDoodle, sf::RenderWindow& window): TextureEntity(logicDoodle, window, "./src/textures/doodle.png") {
    std::cout << "doodle maken" << std::endl;
}

void Doodler::update() {
    std::pair<float, float> newLocation = this->logicEntity->getWorld().getCamera().coordinateToPixel(this->logicEntity->getLocation(), this->logicEntity);
    entityGrahic.setPosition(newLocation.first, newLocation.second);
    if(this->logicEntity->isFacingLeft()){
        this->entityGrahic.setTextureRect(sf::IntRect(55, 0, -55, 109));
    }
    else{
        this->entityGrahic.setTextureRect(sf::IntRect(0, 0, 55, 109));
    }
    if(this->logicEntity->getCustumTexture() != ""){
        texture.loadFromFile(this->logicEntity->getCustumTexture());
    }
    else{
        texture.loadFromFile("./src/textures/doodle.png");
    }
    this->draw();
}

void Doodler::draw() {
    this->window.draw(this->entityGrahic);
}

Platform::Platform(std::shared_ptr<PlatformLogic> logicEntity, sf::RenderWindow& window): Entity(logicEntity, window) {
    entityGrahic = new sf::RectangleShape();
    entityGrahic->setSize(sf::Vector2<float>(logicEntity->getXSize(),logicEntity->getYSize()));
    entityGrahic->setFillColor(sf::Color(logicEntity->getColor()));
    this->logicEntity = logicEntity;

    std::pair<float, float> newLocation = this->logicEntity->getWorld().getCamera().coordinateToPixel(this->logicEntity->getLocation(), this->logicEntity);
    entityGrahic->setPosition(newLocation.first, newLocation.second);
}

void Platform::update() {
    std::pair<float, float> newLocation = this->logicEntity->getWorld().getCamera().coordinateToPixel(this->logicEntity->getLocation(), this->logicEntity);
    entityGrahic->setPosition(newLocation.first, newLocation.second);
    this->draw();
}

void Platform::draw() {
    this->window.draw(*this->entityGrahic);
}

Spring::Spring(std::shared_ptr<SpringLogic> logicSpring, sf::RenderWindow &window):  TextureEntity(logicSpring, window, "./src/textures/spring.png") {
    std::cout << "spring created" << std::endl;
}

Jetpack::Jetpack(std::shared_ptr<JetpackLogic> logicJetpack, sf::RenderWindow &window): TextureEntity(logicJetpack, window, "./src/textures/jetpack.png")  {
    std::cout << "jetpack created" << std::endl;
}
BGTile::BGTile(std::shared_ptr<BGTileLogic> logicEntity, sf::RenderWindow &window): Entity(logicEntity, window) {
    std::cout << window.getSize().x << std::endl;
    this->logicEntity = logicEntity;
    for(int i = 0; i < window.getSize().x; i += 10){
        this->entityGrahic.push_back(std::make_unique<sf::RectangleShape>());
        this->entityGrahic.back()->setSize(sf::Vector2<float>(5,window.getSize().y));
        this->entityGrahic.back()->setFillColor(sf::Color(255,255,255));
        this->entityGrahic.back()->setPosition(i, 0);
    }

}
void BGTile::update() {
    this->draw();
}
void BGTile::draw() {
    for(int i = 0; i < this->entityGrahic.size(); i++){
        std::cout << "draw line" << std::endl;
        this->window.draw(*this->entityGrahic[i]);
    }
}
