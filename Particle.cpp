/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Particle.cpp
 * Author: rafa
 * 
 * Created on January 6, 2018, 2:28 PM
 */

#include "Particle.hpp"

Particle::Particle() {
}

Particle::Particle(const zt::Vector2f& position, const zt::Vector2f& speed) {
    this->position = position;
    this->speed = speed;
}

Particle::~Particle() {
}

void Particle::advanceTime(float deltaTime) {
    position.add(speed.mult(deltaTime));
}

void Particle::setPosition(const zt::Vector2f& position) {
    this->position = position;
}

const zt::Vector2f& Particle::getPosition() const {
    return this->position;
}