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

class GameScene;

class Trail {
public:
    sf::Clock clock;
    sf::Vector2f pos;
    bool visible;
    Trail() { visible = false; }
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
    
    float speed;
    bool moving;
    
    /// DISPARO ///
    
    sf::Clock lastShoot, shootSpriteClock;
    bool shooting;
    sf::Sprite shootSprite;
    sf::Sound shotSound;
    
    /// ANIMACION ///
    int currentFrame, currentFeetFrame;
    sf::Clock animationClock, feetAnimationClock;
    std::vector<sf::Texture*>* currentAnimation;
    std::vector<sf::Texture*>* currentFeetAnimation;
    std::vector<sf::Texture*> rifleMovingTextures;
    std::vector<sf::Texture*> rifleShootingTextures;
    std::vector<sf::Texture*> idleTextures;
    std::vector<sf::Texture*> feetWalkingTextures;
    sf::Sprite playerSprite, feetSprite;
    sf::Sprite shadowPlayerSprite;
    
    /// TELETRANSPORTE ///
    sf::RectangleShape movementRect;
    sf::CircleShape triangle;
    zt::Vector2f originalPosition; // Posición del jugador al inicial el teletransporte.
    sf::Clock teleportingClock; //Se inicia al iniciar el teletransporte.
    float teleportSpeed; //Velocidad de teletransporte.
    float maxTeleport; //Máxima distancia de teletransporte.
    float teleportDistance; //Distancia a la que se teletransporta.
    zt::Vector2f teleportVector; //Vector unitario con la dirección del telegransporte.
    bool teleporting;
    
    /// ESTELA DE TELETRANSPORTE ///
    std::vector<Trail> trails;
    int trailIndex;
    sf::Clock trailGenerationClock;
    float fadeTime; // Tiempo ejn el que se desvanece cada parte de la estela.
    float trailGeneration;
    
    sf::RenderWindow& renderWindow;
    GameScene& gameScene;
    
};

#endif /* CHARACTER_HPP */

