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

#include "Enemy.hpp"
#include "Vector2f.hpp"

Enemy::Enemy() {
    circle.setRadius(16);
    circle.setOrigin(16, 16);
    circle.setFillColor(sf::Color(30, 30, 30));
    
    rect.setSize(sf::Vector2f(4, 16));
    rect.setOrigin(2, 0);
    rect.setFillColor(sf::Color(100, 100, 100));
    
    finished = true;
    currentTarget = -1;
}

Enemy::~Enemy() {
}

void Enemy::draw(sf::RenderTarget& rt, sf::RenderStates rs) const {
    rt.draw(circle, rs);
    rt.draw(rect, rs);
}

void Enemy::advanceTime(float deltaTime) {
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
    
    circle.setPosition(position);
    rect.setPosition(position);
    circle.setRotation(angle);
    rect.setRotation(angle);
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
    
    angle = atan2(-deltaMovement.getX(), deltaMovement.getY()) * 57;
}

bool Enemy::arrivedCurrentTarget() {
    float dx = getPosition().x - (this->path[currentTarget].getPosition().x * tileSize.x + tileSize.x / 2);
    float dy = getPosition().y - (this->path[currentTarget].getPosition().y * tileSize.y + tileSize.y / 2);
    
    if (std::sqrt(dx * dx + dy * dy) < 10) {
        return true;
    }
    return false;
}