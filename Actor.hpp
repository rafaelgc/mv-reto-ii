/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Actor.hpp
 * Author: rafa
 *
 * Created on January 5, 2018, 6:08 PM
 */

#ifndef ACTOR_HPP
#define ACTOR_HPP

#include <ESE/Core/Animatable.hpp>
#include <SFML/Graphics/Drawable.hpp>

class Actor : public sf::Drawable, public ESE::Animatable {
public:
    Actor();
    virtual ~Actor();
    
    virtual void draw(sf::RenderTarget&, sf::RenderStates) const override = 0;
    virtual void advanceTime(float deltaTime) override = 0;
    
    void setPosition(const sf::Vector2f&);
    const sf::Vector2f getPosition() const;
    
    bool damage(float amount);
    bool isAlive() const;
    
protected:
    sf::Vector2f position;
    float life;
};

#endif /* ACTOR_HPP */

