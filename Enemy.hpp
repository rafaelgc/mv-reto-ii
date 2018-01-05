/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Enemy.hpp
 * Author: rafa
 *
 * Created on January 5, 2018, 5:59 PM
 */

#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Actor.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "GridNode.hpp"
#include "Vector2f.hpp"

class Enemy : public Actor {
public:
    Enemy();
    virtual ~Enemy();
    
    void draw(sf::RenderTarget&, sf::RenderStates) const override;
    void advanceTime(float deltaTime) override;
    
    void setPath(std::vector<GridNode> path, sf::Vector2f tileSize);
private:
    sf::CircleShape circle;
    sf::RectangleShape rect, movementRect;
    
    //Movimiento
    int currentTarget;
    bool finished;
    std::vector<GridNode> path;
    sf::Vector2f tileSize;
    Vector2f deltaMovement;
    float angle;
    
    void calcMovement();
    bool arrivedCurrentTarget();
};

#endif /* ENEMY_HPP */

