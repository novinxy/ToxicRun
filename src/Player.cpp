#include "Player.hpp"
#include <iostream>

#define MAX_SPEED   1.5
#define FORCE       10
#define TORQUE      200

std::vector<sf::IntRect> drawings = {sf::IntRect(0,    0,   480,  440),
                                     sf::IntRect(480,  0,   480,  440),
                                     sf::IntRect(960,  0,   480, 440),
                                     sf::IntRect(1440, 0,   480, 440),
                                     sf::IntRect(0,    440, 480,  440),
                                     sf::IntRect(480,  440, 480,  440),
                                     sf::IntRect(960,  440, 480, 440),
                                     sf::IntRect(1440, 440, 480, 440)};

Player::Player(b2World& world, float positionX, float positionY, sf::Texture& texture, float scale)
{
    playerScale = scale;
    graphicBody.setTexture(texture);
    graphicBody.setTextureRect(drawings.at(drawingIndex));
    graphicBody.setOrigin( (float) graphicBody.getTextureRect().width / 2,
                           (float) graphicBody.getTextureRect().height / 2);

    graphicBody.setPosition(positionX, positionY);
    graphicBody.setScale(playerScale, playerScale);
    b2BodyDef body;
    body.position = b2Vec2(positionX / BOX2D_SCALE, positionY / BOX2D_SCALE);
    body.type = b2_dynamicBody;
    physicalBody = world.CreateBody(&body);
    b2PolygonShape shape;
    shape.SetAsBox(graphicBody.getTextureRect().width  * playerScale / (2 * BOX2D_SCALE),
                   graphicBody.getTextureRect().height * playerScale / (2 * BOX2D_SCALE));

    b2FixtureDef fixtureDef;
    fixtureDef.density = DENSITY;
    fixtureDef.friction = FRICTION;
    fixtureDef.shape = &shape;
    physicalBody->CreateFixture(&fixtureDef);
    physicalBody->SetUserData( (void*)1 );

    graphicBody.setRotation(physicalBody->GetAngle() * 180 / b2_pi);
    physicalBody->SetSleepingAllowed(true);

    b2PolygonShape polygonShape;
    polygonShape.SetAsBox(0.3, 0.3, b2Vec2(0, graphicBody.getTextureRect().height * playerScale / (2 * BOX2D_SCALE)), 0);

    //fixture definition
    b2FixtureDef myFixtureDef;
    myFixtureDef.shape = &polygonShape;
    myFixtureDef.density = 1;
    myFixtureDef.isSensor = true;

    //add main fixture
    physicalBody->CreateFixture(&myFixtureDef);

    b2Fixture* footSensorFixture = physicalBody->CreateFixture(&myFixtureDef);
    footSensorFixture->SetUserData( (void*)3 );

    b2MassData mass{18, physicalBody->GetLocalCenter(), physicalBody->GetInertia()};
    physicalBody->SetMassData(&mass);
    physicalBody->SetAngularDamping(2);
    physicalBody->SetSleepingAllowed(false);

}

void Player::moveLeft()
{
    if (clock.getElapsedTime().asSeconds() > 0.1f){
        animate();
        clock.restart();
    }
    graphicBody.setScale({-playerScale, playerScale});
    if (physicalBody->GetLinearVelocity().x > -MAX_SPEED)
        physicalBody->ApplyForce(b2Vec2(-FORCE, 0), physicalBody->GetWorldCenter(), true);
}

void Player::moveRight()
{
    if (clock.getElapsedTime().asSeconds() > 0.1f){
        animate();
        clock.restart();
    }
    graphicBody.setScale({playerScale, playerScale});
    if (physicalBody->GetLinearVelocity().x < MAX_SPEED)
        physicalBody->ApplyForce(b2Vec2(FORCE, 0), physicalBody->GetWorldCenter(), true);
}

void Player::jump()
{
    float impulse = -physicalBody->GetMass() * 5 / 20;
    physicalBody->ApplyLinearImpulse(b2Vec2(0, impulse), physicalBody->GetWorldCenter(), true);
}

void Player::update()
{
    if (physicalBody->GetAngle() > b2_pi / 6)
        physicalBody->ApplyTorque(-TORQUE, true);
    if (physicalBody->GetAngle() < -b2_pi / 6)
        physicalBody->ApplyTorque(TORQUE, true);

    GameObject::update();
}

void Player::animate()
{
    drawingIndex++;
    if (drawingIndex == 8) drawingIndex = 1;
    graphicBody.setTextureRect(drawings.at(drawingIndex));
}