#ifndef GAME_OBJECTS_H
#define GAME_OBJECTS_H

#include "GameObject.hpp"
#include "ShadowObject.hpp"
#include "Player.hpp"
#include <SFML/Graphics.hpp>

class GameObjects
{
public:
    GameObjects() {objectList.reserve(40);}
    void update();
    void lower();
    void draw(sf::RenderWindow&);

    void loadTextures();
    void createWalls(b2World& world, sf::VideoMode videoMode);
    void createGround(b2World& world, sf::VideoMode videoMode);
    void createPlatform(b2World &world, ltbl::LightSystem &lightSystem, float positionX, float positionY);
    std::shared_ptr<Player> createPlayer(b2World& world, sf::VideoMode videoMode, ltbl::LightSystem& lightSystem);



private:
    std::vector<std::shared_ptr<IGameObject>> objectList;

    sf::Texture platformTexture;
    sf::Texture playerTexture;
    sf::Texture wallTexture;
};

#endif //GAME_OBJECTS_H
