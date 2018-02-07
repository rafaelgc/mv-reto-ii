/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ParticleManager.cpp
 * Author: rafa
 * 
 * Created on January 6, 2018, 2:38 PM
 */

#include <vector>
#include <SFML/System/Clock.hpp>

#include "ParticleManager.hpp"
#include "Particle.hpp"

ParticleManager::ParticleManager() {
    removeInterval.restart();
}

ParticleManager::~ParticleManager() {
    for (Particle* p : particles) {
        delete p;
    }
    
    particles.clear();
}

void ParticleManager::addParticle(Particle* particle) {
    particles.push_back(particle);
}

void ParticleManager::draw(sf::RenderTarget& rt, sf::RenderStates rs) const {
    for (auto it = particles.begin(); it != particles.end(); it++) {
        (*it)->draw(rt, rs);
    }
}

void ParticleManager::advanceTime(float deltaTime) {
    
    for (auto it = particles.begin(); it != particles.end(); it++) {
        (*it)->advanceTime(deltaTime);
        
    }
    
    //if (removeInterval.getElapsedTime().asSeconds() > 0.1) {
        for (auto it = particles.begin(); it != particles.end();) {
            if ((*it)->isRemovable()) {
                particles.erase(it);
            }
            else {
                ++it;
            }
        }
        
        //removeInterval.restart();
    //}
}