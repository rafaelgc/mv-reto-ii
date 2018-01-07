/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Actor.cpp
 * Author: rafa
 * 
 * Created on January 5, 2018, 6:08 PM
 */

#include "Actor.hpp"

Actor::Actor() {
    life = 100;
}

Actor::~Actor() {
}

void Actor::setPosition(const sf::Vector2f& pos) {
    position = pos;
}

const sf::Vector2f Actor::getPosition() const {
    return position;
}

bool Actor::damage(float amount) {
    life -= amount;
    if (life <= 0) { life = 0; return true; }
    
    return false;
}

bool Actor::isAlive() const {
    return life > 0;
}