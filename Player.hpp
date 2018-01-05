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

#include "Vector2f.hpp"
#include "Actor.hpp"

class Trail {
public:
    sf::Clock clock;
    sf::Vector2f pos;
    bool visible;
    Trail() { visible = false; }
};

class Player : public Actor {
public:
    Player(sf::RenderWindow & renderWindow);
    virtual ~Player();
    
    void draw(sf::RenderTarget&, sf::RenderStates) const;
    void advanceTime(float deltaTime);
    void manageEvents(float deltaTime);
private:
    sf::CircleShape circle;
    sf::RectangleShape rect;
    
    bool lMouseBtnReleased;
    sf::Clock pressedTime;
    sf::Vector2i pressedPos;
    
    float speed;
    
    /// TELETRANSPORTE ///
    sf::RectangleShape movementRect;
    sf::CircleShape triangle;
    Vector2f originalPosition; // Posición del jugador al inicial el teletransporte.
    sf::Clock teleportingClock; //Se inicia al iniciar el teletransporte.
    float teleportSpeed; //Velocidad de teletransporte.
    float maxTeleport; //Máxima distancia de teletransporte.
    float teleportDistance; //Distancia a la que se teletransporta.
    Vector2f teleportVector; //Vector unitario con la dirección del telegransporte.
    bool teleporting;
    
    /// ESTELA DE TELETRANSPORTE ///
    std::vector<Trail> trails;
    int trailIndex;
    sf::Clock trailGenerationClock;
    float fadeTime;
    float trailGeneration;
    
    sf::RenderWindow& renderWindow;
};

#endif /* CHARACTER_HPP */

