/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BloodDrop.hpp
 * Author: rafa
 *
 * Created on January 6, 2018, 2:25 PM
 */

#ifndef BLOODDROP_HPP
#define BLOODDROP_HPP

#include "Particle.hpp"
#include <SFML/Graphics/CircleShape.hpp>

class BloodDrop : public Particle {
public:
    BloodDrop();
    BloodDrop(const zt::Vector2f& position, const zt::Vector2f& speed, float alphaFactor = 1000);
    virtual ~BloodDrop();
    
    void draw(sf::RenderTarget&, sf::RenderStates) const override;
    void advanceTime(float deltaTime) override;
    
    bool isRemovable() const;
private:
    sf::CircleShape circle;
    sf::Clock time;
    float rnd, alpha, alphaFactor;
};

#endif /* BLOODDROP_HPP */

