/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Enemy.cpp
 * Author: rafa
 * 
 * Created on January 5, 2018, 5:59 PM
 */

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <random>
#include <SFML/Graphics/Sprite.hpp>
#include <ESE/Core/Textures.hpp>

#include "Enemy.hpp"
#include "Vector2f.hpp"
#include "ESE/Core/ResourceManager.hpp"

Enemy::Enemy(ParticleManager& particleManager) : particleManager(particleManager) {
    finished = true;
    currentTarget = -1;
    
    lifeBar.setSize(sf::Vector2f(50, 3));
    lifeBar.setFillColor(sf::Color::Red);
}

Enemy::~Enemy() {
}

void Enemy::setup() {
    for (int i = 0; i <= 16; i++) {
        walkingTextures.push_back(ESE::Textures::instance().getResource("zombie_" + std::to_string(i)));
    }
    
    animationFrame = 0;
    animation.setTexture(*walkingTextures[animationFrame]);
    
    animation.scale(0.35, 0.35);
    animation.setOrigin(107, 169);
}

void Enemy::draw(sf::RenderTarget& rt, sf::RenderStates rs) const {
    if (!isAlive()) return;
    rt.draw(animation, rs);
    rt.draw(lifeBar, rs);
}

void Enemy::advanceTime(float deltaTime) {
    /// GESTION DEL MOVIMIENTO ///
    if (!finished) {
        position.x += deltaMovement.getX() * 100 * deltaTime;
        position.y += deltaMovement.getY() * 100 * deltaTime;
        
        if (arrivedCurrentTarget()) {
            currentTarget++;
            if (currentTarget >= path.size()) {
                finished = true;
            }
            else {
                calcMovement();
            }
        }
    }
    
    /// ACTUALIZACION DE LA ANIMACION ///
    if (animationClock.getElapsedTime().asSeconds() > 0.1) {
        animationFrame++;
        if (animationFrame >= walkingTextures.size()) { animationFrame = 0; }
        animation.setTexture(*walkingTextures[animationFrame]);
        
        animationClock.restart();
    }
    
    /// ACTUALIZACION DE LA POSICION Y ROTACION ///
    if (fabs(angle - targetAngle) > 2) {
        angle = fixAngle(angle);
        targetAngle = fixAngle(targetAngle);

        if(angle < targetAngle) {
            if(abs(angle - targetAngle) < 180) {
                angle += 180 * deltaTime;
            }
            else {
                angle -= 180 * deltaTime;
            }
        }

        else {
            if(abs(angle - targetAngle) < 180) {
                angle -= 180 * deltaTime;
            }
            else {
                angle += 180 * deltaTime;
            }
        }
           
        animation.setRotation(angle + 90);
    }
    
    animation.setPosition(position);
    lifeBar.setPosition(position);
    
}

float Enemy::fixAngle(float angle) {
    if (angle < 0) { return angle + 360; }
    if (angle > 360) { return ((int)angle % 360); }
    return angle;
}

void Enemy::setPath(std::vector<GridNode> path, sf::Vector2f tileSize) {
    this->path = path;
    this->tileSize = tileSize;
    
    if (path.size() > 1) {
        currentTarget = 1;
        finished = false;
        calcMovement();
    }
}

void Enemy::calcMovement() {
    deltaMovement.setX(this->path[currentTarget].getPosition().x * this->tileSize.x + this->tileSize.x / 2 - getPosition().x);
    deltaMovement.setY(this->path[currentTarget].getPosition().y * this->tileSize.y + this->tileSize.y / 2 - getPosition().y);
    deltaMovement.normalize();
    
    targetAngle = atan2(-deltaMovement.getX(), deltaMovement.getY()) * (180 / M_PI);
}

bool Enemy::arrivedCurrentTarget() {
    float dx = getPosition().x - (this->path[currentTarget].getPosition().x * tileSize.x + tileSize.x / 2);
    float dy = getPosition().y - (this->path[currentTarget].getPosition().y * tileSize.y + tileSize.y / 2);
    
    if (std::sqrt(dx * dx + dy * dy) < 10) {
        return true;
    }
    return false;
}

bool Enemy::damage(float amount) {
    bool r = Actor::damage(amount);
    
    lifeBar.setSize(sf::Vector2f(life / 100 * 50, lifeBar.getSize().y));
    
    
    return r;
}

bool Enemy::giveShot(float d, const Vector2f& sense) {
    bool r = damage(d);
    
    std::default_random_engine generator;
    std::normal_distribution<float> distribution(45.0,5.0);
    
    for (int i = 0; i < 50; i++) {
        float rotation = distribution(generator);
        Vector2f senseN = sense.normalized().mult(500 + rand() % 300);
        particleManager.addParticle(
            new BloodDrop(
                    Vector2f(position), 
                    senseN.rotated(rotation - 45)
            )
        );
    }
    
    return r;
}