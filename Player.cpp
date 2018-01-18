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
#include <cmath>

#include "Player.hpp"
#include <Zelta/Math/Vector2f.hpp>
#include "Zelta/Core/Textures.hpp"
#include "GameScene.hpp"
#include "Zelta/Core/SoundBuffers.hpp"

#include <iostream>
#include <SFML/Graphics/Sprite.hpp>

Player::Player(sf::RenderWindow& renderWindow, GameScene& gameScene) : renderWindow(renderWindow), gameScene(gameScene), triangle(10, 3) {
    
    speed = 150.f;
    teleportSpeed = 1500.f;
    maxTeleport = 400.f;
    teleportDistance = 0.f;
    
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

void Player::setup() {
    currentFrame = 0;
    currentFeetFrame = 0;
    
    for (int i = 0; i <= 19; i++) {
        idleTextures.push_back((zt::Textures::instance().getResource("survivor_rifle_idle_" + std::to_string(i))));
        rifleMovingTextures.push_back((zt::Textures::instance().getResource("survivor_rifle_move_" + std::to_string(i))));
        feetWalkingTextures.push_back((zt::Textures::instance().getResource("survivor_walk_" + std::to_string(i))));
    }
    
    for (int i = 0; i <= 2; i++) {
        rifleShootingTextures.push_back((zt::Textures::instance().getResource("survivor_shoot_rifle_" + std::to_string(i))));
    }
    
    currentAnimation = &idleTextures;
    currentFeetAnimation = &feetWalkingTextures;
       
    playerSprite.setTexture(*currentAnimation->at(currentFrame));
    playerSprite.setScale(0.4, 0.4);
    playerSprite.setOrigin(96, 119);
    
    shadowPlayerSprite = playerSprite;
    shadowPlayerSprite.setColor(sf::Color(0, 0, 0, 100));
    
    animationClock.restart();
    feetAnimationClock.restart();
    
    feetSprite.setTexture(*currentFeetAnimation->at(currentFeetFrame));
    feetSprite.setScale(0.4, 0.4);
    feetSprite.setOrigin(87, 62);
    
    moving = false;
    shooting = false;
    
    shootSprite.setTexture(*zt::Textures::instance().getResource("shoot_fire"));
    shootSprite.setOrigin(-750, 0);
    shootSprite.setScale(0.1, 0.1);
    
    shotSound.setBuffer(*zt::SoundBuffers::instance().getResource("shot"));
    shotSound.setVolume(10);
    lastShoot.restart();
}

void Player::draw(sf::RenderTarget& rt, sf::RenderStates rs) const {
    if (!lMouseBtnReleased) {
        rt.draw(movementRect, rs);
        rt.draw(triangle), rs;
    }
    
    rt.draw(shadowPlayerSprite, rs);
    
    sf::Sprite trailSprite = playerSprite;
    for (int i = 0; i < trailIndex; i++) {
        if (trails[i].visible) {
            float alpha = 100 * (1 - std::min(trails[i].clock.getElapsedTime().asSeconds() / fadeTime, 1.f));
            
            trailSprite.setColor(sf::Color(255, 255, 255, alpha));
            trailSprite.setPosition(trails[i].pos);
            rt.draw(trailSprite, rs);
        }
    }
    
    if (moving) {
        rt.draw(feetSprite, rs);
    }
    
    rt.draw(playerSprite, rs);
    
    if (shooting && shootSpriteClock.getElapsedTime().asSeconds() < 0.1) {
        rt.draw(shootSprite, rs);
    }
    
}

void Player::advanceTime(float deltaTime) {
    playerSprite.setPosition(position);
    shadowPlayerSprite.setPosition(position + sf::Vector2f(20, 20));
    
    feetSprite.setPosition(position);
    shootSprite.setPosition(position);
    
    if (shootSpriteClock.getElapsedTime().asSeconds() > 0.1) {
        shootSprite.setColor(sf::Color(255, 255, 255, 100 + rand() % 100));
        shootSpriteClock.restart();
    }
    
    if (animationClock.getElapsedTime().asSeconds() > (shooting ? 0.05 : 0.1)) {
        currentFrame++;
        
        if (currentFrame >= currentAnimation->size()) { currentFrame = 0; }
        
        playerSprite.setTexture(*currentAnimation->at(currentFrame));
        shadowPlayerSprite.setTexture(*currentAnimation->at(currentFrame));
        animationClock.restart();
    }
    
    if (feetAnimationClock.getElapsedTime().asSeconds() > 0.02) {
        currentFeetFrame++;
        if (currentFeetFrame == 20) { currentFeetFrame = 0; }
        feetSprite.setTexture(*currentFeetAnimation->at(currentFeetFrame));
        
        feetAnimationClock.restart();
    }
    
    if (teleporting) {
        float currDistance = teleportingClock.getElapsedTime().asSeconds() * teleportSpeed;
        float progress = currDistance / teleportDistance;
        if (progress <= 1) {
            zt::Vector2f newPos = originalPosition.plus(teleportVector.mult(currDistance));
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

void Player::manageEvents(float deltaTime) {\
    sf::Vector2f currMousePos = gameScene.getWindow().mapPixelToCoords(sf::Mouse::getPosition(renderWindow)); // Posición del ratón respecto al mundo.
    
    
    zt::Vector2f a(currMousePos.x, currMousePos.y);
    zt::Vector2f b(position.x, position.y);

    /// ROTACIÓN DEL JUGADOR ///
    lookAt = a.minus(b);
    float angle = std::atan2(-lookAt.getX(), lookAt.getY()) * 57.29;
    
    /// ACTUALIZACIÓN DE LA POSICION DE LA CAMARA ///
    this->gameScene.getOrigin().x = position.x + (currMousePos.x - position.x) / 4;
    this->gameScene.getOrigin().y = position.y + (currMousePos.y - position.y) / 4;
    
    /// APLICAR CAMBIOS A LOS SPRITES ///
    playerSprite.setRotation(angle + 90);
    shadowPlayerSprite.setRotation(angle + 90);
    
    feetSprite.setRotation(angle + 90);
    shootSprite.setRotation(angle + 90);
    
    moving = false;
    
    if (!teleporting && lMouseBtnReleased) {
        
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (lastShoot.getElapsedTime().asSeconds() > 0.1) {
                
                for (Enemy* enemy : gameScene.getEnemies()) {
                    zt::Vector2f playerEnemy(enemy->getPosition().x, enemy->getPosition().y);
                    playerEnemy = playerEnemy.minus(zt::Vector2f(position.x, position.y));

                    float projection = playerEnemy.dot(lookAt) / lookAt.length();

                    // Nota: sin calcular el valor absoluto de fabs()
                    // se dispara tanto de frente como de espaldas.
                    zt::Vector2f vProjection = lookAt.normalized().mult(fabs(projection));

                    float distance = zt::Vector2f(position.x, position.y).plus(vProjection).minus(zt::Vector2f(enemy->getPosition().x, enemy->getPosition().y)).length();

                    if (distance < 30) {
                        enemy->giveShot(20, lookAt);
                    }

                }
                lastShoot.restart();
                
                shotSound.play();
            }
            
            shooting = true;
        }
        else {
            shooting = false;
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            position.y -= speed * deltaTime;
            if (!gameScene.isValidPosition(sf::Vector2f(position))) {
                position.y += speed * deltaTime;
            }
            moving = true;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            position.x -= speed * deltaTime;
            if (!gameScene.isValidPosition(sf::Vector2f(position))) {
                position.x += speed * deltaTime;
            }
            moving = true;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            position.y += speed * deltaTime;
            if (!gameScene.isValidPosition(sf::Vector2f(position))) {
                position.y -= speed * deltaTime;
            }
            moving = true;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            position.x += speed * deltaTime;
            if (!gameScene.isValidPosition(sf::Vector2f(position))) {
                position.x -= speed * deltaTime;
            }
            moving = true;
        }
    }
    
    if (shooting) {
        currentAnimation = &rifleShootingTextures;
    }
    else if (moving) {
        currentAnimation = &rifleMovingTextures;
    }
    else {
        currentAnimation = &idleTextures;
    }
    
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
        if (lMouseBtnReleased) {
            pressedPos = this->gameScene.getWindow().mapPixelToCoords(sf::Mouse::getPosition(renderWindow));
            
            zt::Vector2f a(pressedPos.x, pressedPos.y);
            zt::Vector2f b(position.x, position.y);
            
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
        
        zt::Vector2f a(pressedPos.x, pressedPos.y);
        zt::Vector2f b(position.x, position.y);
        
        
        movementRect.setSize(sf::Vector2f(movementRect.getSize().x, teleportDistance));
        movementRect.setFillColor(sf::Color(255 * (teleportDistance / maxTeleport), 255 * (1 -(teleportDistance / maxTeleport)), 0));
        
        //Actualizar la posición en función de la del jugador.
        movementRect.setPosition(position);
        
        zt::Vector2f v(position.x, position.y);
        v = v.plus(teleportVector.mult(teleportDistance));
        triangle.setPosition(v.getX(), v.getY());
        triangle.setFillColor(sf::Color(255 * (teleportDistance / maxTeleport), 255 * (1 -(teleportDistance / maxTeleport)), 0));
        
        lMouseBtnReleased = false;
    }
    else {
        if (!lMouseBtnReleased && !teleporting) {
            //Comprobar que la posición de destino sea válida.
            if (gameScene.isValidPosition(position + teleportVector.mult(teleportDistance).toSfml())) {
                teleporting = true;
                teleportingClock.restart();

                trailIndex = 0;
                trailGenerationClock.restart();

                originalPosition.set(position.x, position.y);
            }
        }
        lMouseBtnReleased = true;
    }
    
}