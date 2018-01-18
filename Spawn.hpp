/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Spawn.hpp
 * Author: rafa
 *
 * Created on January 16, 2018, 3:30 AM
 */

#ifndef SPAWN_HPP
#define SPAWN_HPP

#include <SFML/System/Vector2.hpp>
#include <SFML/System/Clock.hpp>

#include <Zelta/Core/Animatable.hpp>

class GameScene;

class Spawn : zt::Animatable {
public:
    Spawn(GameScene& gameScene);
    virtual ~Spawn();
    
    void setPosition(const sf::Vector2f& position);
    const sf::Vector2f& getPosition() const;
    
    void advanceTime(float deltaTime);
private:
    sf::Vector2f position;
    sf::Clock spawnTime;
    GameScene& gameScene;
};

#endif /* SPAWN_HPP */

