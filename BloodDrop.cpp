/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BloodDrop.cpp
 * Author: rafa
 * 
 * Created on January 6, 2018, 2:25 PM
 */

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Clock.hpp>

#include "BloodDrop.hpp"
#include "Vector2f.hpp"

BloodDrop::BloodDrop(const Vector2f& position, const Vector2f& speed) : Particle(position, speed) {
    time.restart();
    rnd = (rand() % 100) / 100.0;
    circle.setFillColor(sf::Color::Red);
    circle.setRadius(1);
    
    alpha = 255;
}

BloodDrop::~BloodDrop() {
}

void BloodDrop::draw(sf::RenderTarget& rt, sf::RenderStates rs) const {
    rt.draw(circle, rs);
}

void BloodDrop::advanceTime(float deltaTime) {
    Particle::advanceTime(deltaTime);
    
    circle.setFillColor(sf::Color(130, 0, 0, alpha));
    alpha -= deltaTime * 1000;
    if (alpha < 0) { alpha = 0; }
    
    circle.setPosition(position.toSfml());
}

bool BloodDrop::isRemovable() const {
    return alpha <= 0;
}