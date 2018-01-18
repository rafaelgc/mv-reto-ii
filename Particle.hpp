/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Particle.hpp
 * Author: rafa
 *
 * Created on January 6, 2018, 2:28 PM
 */

#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <Zelta/Core/Animatable.hpp>
#include <SFML/Graphics/Drawable.hpp>

#include <Zelta/Math/Vector2f.hpp>

class Particle : public sf::Drawable, public zt::Animatable{
public:
    Particle();
    Particle(const zt::Vector2f& position, const zt::Vector2f& speed);
    virtual ~Particle();
    
    virtual void draw(sf::RenderTarget&, sf::RenderStates) const = 0;
    virtual void advanceTime(float deltaTime) override;
    
    virtual void setPosition(const zt::Vector2f& position);
    virtual const zt::Vector2f& getPosition() const;
    
    virtual bool isRemovable() const = 0;
    
protected:
    zt::Vector2f position;
    zt::Vector2f speed;
};

#endif /* PARTICLE_HPP */

