#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "GameObject.hpp"

class Player : public GameObject
{
public:
    Player(b2World& world, float x, float y, sf::Texture& texture, float scale = 0.2);
    void update() override;
    void moveLeft();
    void moveRight();
    void jump();

private:
    void animate();
    int drawingIndex = 0;
    sf::Clock clock;
    float playerScale;
};

#endif // PLAYER_HPP
