//
// Created by stein on 18/11/2021.
//

#include "Entity.h"

Entity::Entity(EntityLogic& logicEntity1, sf::RenderWindow &window): EntityObserver(logicEntity1), window(window) {

}

TextureEntity::TextureEntity(EntityLogic& logicEntity, sf::RenderWindow &window, const char* texturePath): Entity(logicEntity, window) {
    entityGrahic = sf::Sprite();
    std::cout << texturePath << std::endl;
    if (!texture.loadFromFile(texturePath))
    {
        throw "Texturemap not found";
    }
    this->entityGrahic.setTextureRect(sf::IntRect(0, 0, logicEntity.getXSize(), logicEntity.getYSize()));
    entityGrahic.setTexture(texture);
    entityGrahic.setScale(1,1);
    std::pair<float, float> newLocation = logicEntity.getWorld().getCamera().coordinateToPixel(logicEntity.getLocation(), logicEntity);
    entityGrahic.setPosition(newLocation.first, newLocation.second);
}

void TextureEntity::update() {
    std::pair<float, float> newLocation = this->logicEntity.getWorld().getCamera().coordinateToPixel(this->logicEntity.getLocation(), this->logicEntity);
    entityGrahic.setPosition(newLocation.first, newLocation.second);
    if(this->logicEntity.darkTexture())
        entityGrahic.setColor(sf::Color(255,0,0));
    else{
        entityGrahic.setColor(sf::Color(255,255,255));
    }
    this->draw();
}

void TextureEntity::draw() {
    this->window.draw(this->entityGrahic);
}

Doodler::Doodler(DoodlerLogic& logicDoodle, sf::RenderWindow& window): TextureEntity(logicDoodle, window, "./src/textures/doodle.png") {
    std::cout << "doodle maken" << std::endl;
}

void Doodler::update() {
    std::pair<float, float> newLocation = this->logicEntity.getWorld().getCamera().coordinateToPixel(this->logicEntity.getLocation(), this->logicEntity);
    entityGrahic.setPosition(newLocation.first, newLocation.second);
    if(this->logicEntity.isFacingLeft()){
        this->entityGrahic.setTextureRect(sf::IntRect(55, 0, -55, 109));
    }
    else{
        this->entityGrahic.setTextureRect(sf::IntRect(0, 0, 55, 109));
    }
    if(this->logicEntity.getCustumTexture() != ""){
        texture.loadFromFile(this->logicEntity.getCustumTexture());
    }
    else{
        texture.loadFromFile("./src/textures/doodle.png");
    }
    if(this->logicEntity.darkTexture())
        entityGrahic.setColor(sf::Color(255,0,0));
    else{
        entityGrahic.setColor(sf::Color(255,255,255));
    }
    this->draw();
}

void Doodler::draw() {
    this->window.draw(this->entityGrahic);
}

Platform::Platform(PlatformLogic& logicEntity, sf::RenderWindow& window): Entity(logicEntity, window) {
    entityGrahic = new sf::RectangleShape();
    entityGrahic->setSize(sf::Vector2<float>(logicEntity.getXSize(),logicEntity.getYSize()));
    entityGrahic->setFillColor(sf::Color(logicEntity.getColor()));
    /*
    this->logicEntity = logicEntity;

    std::pair<float, float> newLocation = this->logicEntity->getWorld().getCamera().coordinateToPixel(this->logicEntity->getLocation(), this->logicEntity);
    entityGrahic->setPosition(newLocation.first, newLocation.second);*/
}

void Platform::update() {
    std::pair<float, float> newLocation = this->logicEntity.getWorld().getCamera().coordinateToPixel(this->logicEntity.getLocation(), this->logicEntity);
    entityGrahic->setPosition(newLocation.first, newLocation.second);
    this->draw();
}

void Platform::draw() {
    this->window.draw(*this->entityGrahic);
}

Spring::Spring(SpringLogic& logicSpring, sf::RenderWindow &window): TextureEntity(logicSpring, window, "./src/textures/spring.png") {
    std::cout << "spring created" << std::endl;
}

Jetpack::Jetpack(JetpackLogic& logicJetpack, sf::RenderWindow &window): TextureEntity(logicJetpack, window, "./src/textures/jetpack.png")  {
    std::cout << "jetpack created" << std::endl;
}

Spike::Spike(SpikeLogic& logicJetpack, sf::RenderWindow &window): TextureEntity(logicJetpack, window, "./src/textures/spike.png") {
    std::cout << "spike created" << std::endl;
}

AddHp::AddHp(AddHpLogic& logicJetpack, sf::RenderWindow &window): TextureEntity(logicJetpack, window, "./src/textures/addhp.png") {
    std::cout << "hp buble created" << std::endl;
}
void AddHp::update() {
    if(this->logicEntity.getCustumTexture() != ""){
        texture.loadFromFile(this->logicEntity.getCustumTexture());
    }
    else{
        texture.loadFromFile("./src/textures/addhp.png");
    }
    TextureEntity::update();
}

BGTile::BGTile(BGTileLogic& logicEntity, sf::RenderWindow &window): Entity(logicEntity, window) {
    std::cout << window.getSize().x << std::endl;
   // this->logicEntity = logicEntity;

}
void BGTile::update() {
    this->entityGrahic.clear();
    for(int i = 0; i < window.getSize().x; i += 20){
        this->entityGrahic.push_back(std::make_unique<sf::RectangleShape>());
        this->entityGrahic.back()->setSize(sf::Vector2<float>(1,window.getSize().y));
        this->entityGrahic.back()->setFillColor(sf::Color(227, 212, 168));
        this->entityGrahic.back()->setPosition(i, 0);
    }
    for(int i = 0; i < this->logicEntity.getHorizontalLines().size(); i++){
        this->entityGrahic.push_back(std::make_unique<sf::RectangleShape>());
        this->entityGrahic.back()->setSize(sf::Vector2<float>(window.getSize().x,1));
        this->entityGrahic.back()->setFillColor(sf::Color(227, 212, 168));
        this->entityGrahic.back()->setPosition(0, this->logicEntity.getWorld().getCamera().yCoordinateToPixel(this->logicEntity.getHorizontalLines()[i]));
    }
    this->draw();
}
void BGTile::draw() {
    for(int i = 0; i < this->entityGrahic.size(); i++){
        this->window.draw(*this->entityGrahic[i]);
    }
}

Enemy0::Enemy0(Enemy0Logic& enemyLogic, sf::RenderWindow &window): TextureEntity(enemyLogic, window, "./src/textures/monster0.png") {
    std::cout << "create monster" << std::endl;
}

Enemy1::Enemy1(Enemy1Logic& enemyLogic, sf::RenderWindow &window): TextureEntity(enemyLogic, window, "./src/textures/monster1.png") {
}


Label::Label(EntityLogic& logicEntity, sf::RenderWindow &window, int locationX, int locationY): Entity(logicEntity, window) {
    this->text.setFillColor(sf::Color(0,0,0));
    this->text.setPosition(locationX, locationY);

    if (!this->font.loadFromFile("./src/fonts/upheavtt.ttf"))
    {
        std::cout << "Error font not found" << std::endl;
    }
    this->text.setFont(font);
}

void Label::draw() {
    window.draw(text);
}

ScoreLabel::ScoreLabel(Score& logicEntity, sf::RenderWindow &window): Label(logicEntity, window, 10, 0) {
}

void ScoreLabel::update() {
    this->text.setString("Score:" + std::to_string(this->logicEntity.getCurrentScore()) + "\n" + "Hp:" + std::to_string(this->logicEntity.getCurrentHp()));
    this->draw();
}

Bullet::Bullet(BulletLogic& logicEntity, sf::RenderWindow &window): Entity(logicEntity, window) {
    entityGrahic = new sf::CircleShape();
    entityGrahic->setRadius(logicEntity.getXSize()/2.0);
    entityGrahic->setFillColor(sf::Color(255,255,255));
    /*this->logicEntity = logicEntity;

    std::pair<float, float> newLocation = this->logicEntity->getWorld().getCamera().coordinateToPixel(this->logicEntity->getLocation(), this->logicEntity);
    entityGrahic->setPosition(newLocation.first, newLocation.second);*/
}

void Bullet::update() {
    std::pair<float, float> newLocation = this->logicEntity.getWorld().getCamera().coordinateToPixel(this->logicEntity.getLocation(), this->logicEntity);
    entityGrahic->setPosition(newLocation.first, newLocation.second);
    this->draw();
}

void Bullet::draw() {
    this->window.draw(*this->entityGrahic);
}

StartScreen::StartScreen(StartScreenLogic& logicEntity, sf::RenderWindow &window): Entity(logicEntity, window) {
    if (!this->font.loadFromFile("./src/fonts/upheavtt.ttf"))
    {
        std::cout << "Error font not found" << std::endl;
    }

    this->title.setFillColor(sf::Color(0,0,0));
    this->title.setPosition(10, 140);
    this->title.setFont(font);
    this->title.setCharacterSize(50);

    this->instructions.setFillColor(sf::Color(0,0,0));
    this->instructions.setPosition(10, 200);
    this->instructions.setFont(font);
    this->instructions.setCharacterSize(20);

    this->hightScore.setFillColor(sf::Color(0,0,0));
    this->hightScore.setPosition(10, 240);
    this->hightScore.setFont(font);
    this->hightScore.setCharacterSize(27);
}

void StartScreen::update() {
    title.setString("DoodleJump");
    instructions.setString("Press Q, D or Z to start a new game");
    this->hightScore.setString("HIGHSCORE: " + std::to_string(this->logicEntity.getWorld().getScore().getHighScore()));
    this->draw();
}

void StartScreen::draw() {
    window.draw(title);
    window.draw(instructions);
    window.draw(hightScore);
}
