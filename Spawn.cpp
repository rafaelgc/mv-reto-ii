/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Spawn.cpp
 * Author: rafa
 * 
 * Created on January 16, 2018, 3:30 AM
 */

#include "Spawn.hpp"
#include "Enemy.hpp"
#include "GameScene.hpp"

Spawn::Spawn(GameScene& gameScene) : gameScene(gameScene) {
}

Spawn::~Spawn() {
}

void Spawn::setPosition(const sf::Vector2f& position) {
    this->position = position;
}

const sf::Vector2f& Spawn::getPosition() const {
    return position;
}

void Spawn::advanceTime(float deltaTime) {
    if (spawnTime.getElapsedTime().asSeconds() > 10) {
        
        if (!gameScene.getVisibleArea().contains(sf::Vector2i(position))) {
            Enemy* e = new Enemy(gameScene.getParticleManager());
            e->setup();
            e->setPosition(position);
            gameScene.getEnemies().push_back(e);
        }
        
        spawnTime.restart();
    }
}