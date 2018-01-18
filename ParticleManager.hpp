/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ParticleManager.hpp
 * Author: rafa
 *
 * Created on January 6, 2018, 2:38 PM
 */

#ifndef PARTICLEMANAGER_HPP
#define PARTICLEMANAGER_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <Zelta/Core/Animatable.hpp>
#include <SFML/System/Clock.hpp>

#include "Particle.hpp"

class ParticleManager : public sf::Drawable, public zt::Animatable {
public:
    ParticleManager();
    virtual ~ParticleManager();
    
    void addParticle(Particle* particle);
    void draw(sf::RenderTarget&, sf::RenderStates) const;
    void advanceTime(float deltaTime);
private:
    std::vector<Particle*> particles;
    sf::Clock removeInterval;
};

#endif /* PARTICLEMANAGER_HPP */

