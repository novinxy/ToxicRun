#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

class IGameObject
{
public:
    virtual void update() = 0;
    virtual void setPosition(float x, float y) = 0;
    virtual sf::Sprite getBody() = 0;
};

class GameObject : public IGameObject
{
public:
    GameObject(b2World& world,
               float positionX,
               float positionY,
               sf::Texture& texture,
               float scale,
               b2BodyType type);
    void setPosition(float x, float y) override;
    void update() override;
    sf::Sprite getBody() override;

    sf::Sprite graphicBody;
    b2Body* physicalBody;
    b2PolygonShape shape;
};

#endif // GAMEOBJECT_HPP
