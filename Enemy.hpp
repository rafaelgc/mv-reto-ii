/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Enemy.hpp
 * Author: rafa
 *
 * Created on January 5, 2018, 5:59 PM
 */

#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Actor.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "GridNode.hpp"
#include "Vector2f.hpp"

#include "ParticleManager.hpp"
#include "BloodDrop.hpp"

class Enemy : public Actor {
public:
    Enemy(ParticleManager & particleManager);
    virtual ~Enemy();
    
    void setup();
    
    void draw(sf::RenderTarget&, sf::RenderStates) const override;
    void advanceTime(float deltaTime) override;
    
    void setPath(std::vector<GridNode> path, sf::Vector2f tileSize);
    
    bool damage(float amount);
    bool giveShot(float damage, const Vector2f& sense);
    
    void setAngleTarget(float angle) {
        this->targetAngle = angle;
    }
    
private:
    sf::RectangleShape lifeBar;
    
    /// Para la sangre ///
    ParticleManager& particleManager;
    
    /// Movimiento ///
    int currentTarget;
    bool finished;
    std::vector<GridNode> path;
    sf::Vector2f tileSize;
    Vector2f deltaMovement;
    float angle, targetAngle;
    
    void calcMovement();
    bool arrivedCurrentTarget();
    
    float fixAngle(float angle);
    
    
    /// ANIMACION ///
    std::vector<sf::Texture*> walkingTextures;
    
    int animationFrame;
    sf::Sprite animation, shadowAnimation;
    sf::Clock animationClock;
};

#endif /* ENEMY_HPP */

