/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Character.cpp
 * Author: rafa
 * 
 * Created on January 5, 2018, 11:50 AM
 */

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/OpenGL.hpp>

#include "Player.hpp"
#include "Vector2f.hpp"

#include <iostream>

Player::Player(sf::RenderWindow& renderWindow) : renderWindow(renderWindow), triangle(10, 3) {
    speed = 150.f;
    teleportSpeed = 1550.f;
    maxTeleport = 400.f;
    teleportDistance = 0.f;
    
    circle.setRadius(16);
    circle.setOrigin(16, 16);
    
    rect.setSize(sf::Vector2f(4, 16));
    rect.setOrigin(2, 0);
    rect.setFillColor(sf::Color(100, 100, 100));
    
    lMouseBtnReleased = true;
    
    movementRect.setSize(sf::Vector2f(8, 100));
    movementRect.setOrigin(4, 0);
    
    triangle.setOrigin(10, 10);
    
    teleporting = false;
    
    fadeTime = 0.2;
    trailGeneration = 0.011;
    
    trailIndex = 0;
    for (int i = 0; i < 20; i++) {
        trails.push_back(Trail());
    }
}

Player::~Player() {
}

void Player::draw(sf::RenderTarget& rt, sf::RenderStates rs) const {
    sf::CircleShape trailCircle = circle;
    for (int i = 0; i < trailIndex; i++) {
        if (trails[i].visible) {
            float alpha = 100 * (1 - trails[i].clock.getElapsedTime().asSeconds() / fadeTime);
            
            trailCircle.setFillColor(sf::Color(255, 255, 255, alpha));
            trailCircle.setPosition(trails[i].pos);
            rt.draw(trailCircle, rs);
        }
    }
    
    rt.draw(circle, rs);
    rt.draw(rect, rs);
    
    if (!lMouseBtnReleased) {
        rt.draw(movementRect, rs);
        rt.draw(triangle), rs;
    }
    
}

void Player::advanceTime(float deltaTime) {
    circle.setPosition(position.x, position.y);
    rect.setPosition(position.x, position.y);
    
    if (teleporting) {
        float currDistance = teleportingClock.getElapsedTime().asSeconds() * teleportSpeed;
        float progress = currDistance / teleportDistance;
        if (progress <= 1) {
            Vector2f newPos = originalPosition.plus(teleportVector.mult(currDistance));
            this->position.x = newPos.getX();
            this->position.y = newPos.getY();
        }
        else {
            teleporting = false;
        }
        
        //// GENERACION DE LA ESTELA ////
        if (trailGenerationClock.getElapsedTime().asSeconds() > trailGeneration && trailIndex < trails.size()) {
            trails[trailIndex].visible = true;
            trails[trailIndex].pos.x = position.x;
            trails[trailIndex].pos.y = position.y;
            trails[trailIndex].clock.restart();
            trailIndex++;
            trailGenerationClock.restart();
            
        }
    }
    
    for (int i = 0; i < trailIndex; i++) {
        if (trails[i].clock.getElapsedTime().asSeconds() >= fadeTime) {
            trails[i].visible = false;
        }
    }
    
}

void Player::manageEvents(float deltaTime) {
    sf::Vector2i currMousePos = sf::Mouse::getPosition(renderWindow);
    Vector2f a(currMousePos.x, currMousePos.y);
    Vector2f b(position.x, position.y);

    //Para calcular el ángulo del ratón respecto al jugador.
    Vector2f m = a.minus(b);
    float angle = atan2(-m.getX(), m.getY()) * 57.29;
    
    circle.setRotation(angle);
    rect.setRotation(angle);
    
    if (!teleporting && lMouseBtnReleased) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            position.y -= speed * deltaTime;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            position.x -= speed * deltaTime;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            position.y += speed * deltaTime;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            position.x += speed * deltaTime;
        }
    }
    
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
        if (lMouseBtnReleased) {
            pressedPos = sf::Mouse::getPosition(renderWindow);
            
            Vector2f a(pressedPos.x, pressedPos.y);
            Vector2f b(position.x, position.y);
            
            teleportVector = a.minus(b).normalized();
            
            movementRect.setRotation(angle);
            triangle.setRotation(angle + 180);
            pressedTime.restart();
        }
        
        teleportDistance = teleportSpeed * pressedTime.getElapsedTime().asSeconds();
        if (teleportDistance > maxTeleport) {
            teleportDistance = 0;
            pressedTime.restart();
        }
        
        Vector2f a(pressedPos.x, pressedPos.y);
        Vector2f b(position.x, position.y);
        
        
        movementRect.setSize(sf::Vector2f(movementRect.getSize().x, teleportDistance));
        movementRect.setFillColor(sf::Color(255 * (teleportDistance / maxTeleport), 255 * (1 -(teleportDistance / maxTeleport)), 0));
        
        //Actualizar la posición en función de la del jugador.
        movementRect.setPosition(position);
        
        Vector2f v(position.x, position.y);
        v = v.plus(teleportVector.mult(teleportDistance));
        triangle.setPosition(v.getX(), v.getY());
        triangle.setFillColor(sf::Color(255 * (teleportDistance / maxTeleport), 255 * (1 -(teleportDistance / maxTeleport)), 0));
        
        lMouseBtnReleased = false;
    }
    else {
        if (!lMouseBtnReleased && !teleporting) {
            
            teleporting = true;
            teleportingClock.restart();
            
            trailIndex = 0;
            trailGenerationClock.restart();
            
            originalPosition.set(position.x, position.y);
        }
        lMouseBtnReleased = true;
    }
    
}