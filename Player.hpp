/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Character.hpp
 * Author: rafa
 *
 * Created on January 5, 2018, 11:50 AM
 */

#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <Zelta/Math/Vector2f.hpp>
#include "Actor.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

class GameScene;

class Trail {
public:
    sf::Clock clock;
    sf::Vector2f pos;
    bool visible;
    Trail() { visible = false; }
};

class Sensor {
public:
    Sensor() : x(0), y(0), on(false) { }
    Sensor(float x, float y) : x(x), y(y) {}
    
    void setX(float x) { this->x = x; }
    void setY(float y) { this->y = y; }
    float getX() const { return x; }
    float getY() const { return y; }
    bool isOn() const { return on; }
    void setOn(bool on) { this->on = on; }
    
private:
    float x, y;
    bool on;
};

class Player : public Actor {
public:
    Player(sf::RenderWindow & renderWindow, GameScene& gameScene);
    virtual ~Player();
    
    void setup();
    
    void draw(sf::RenderTarget&, sf::RenderStates) const;
    void advanceTime(float deltaTime);
    void manageEvents(float deltaTime);
private:
    
    bool lMouseBtnReleased;
    sf::Clock pressedTime;
    sf::Vector2f pressedPos;
    
    zt::Vector2f lookAt;
    
    float speedMagnitude;
    bool jumping;
    bool flipped;
    bool moving;
    bool released;
    
    /// FISICA
    sf::Vector2f gravity;
    sf::Vector2f speed;
    std::vector<Sensor> sensors;
    
    /// ANIMACION ///
    int currentFrame;
    sf::Clock animationClock;
    std::vector<sf::Texture*>* currentAnimation;
    std::vector<sf::Texture*> idleTextures;
    std::vector<sf::Texture*> runningTextures;
    sf::Sprite playerSprite;
    
    /// CUERDA ///
    sf::RectangleShape rope;
    bool ropeThrowed;
    sf::Vector2f ropeMovementVector;
    zt::Vector2f ropeTarget;
    
    
    /// ESTELA DE TELETRANSPORTE ///
    std::vector<Trail> trails;
    int trailIndex;
    sf::Clock trailGenerationClock;
    float fadeTime; // Tiempo ejn el que se desvanece cada parte de la estela.
    float trailGeneration;
    
    sf::RenderWindow& renderWindow;
    GameScene& gameScene;
    
    sf::Text text;
    
};

#endif /* CHARACTER_HPP */

