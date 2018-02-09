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

Player::Player(sf::RenderWindow& renderWindow, GameScene& gameScene) : renderWindow(renderWindow), gameScene(gameScene) {
    
    speedMagnitude = 400.f;
    speed = sf::Vector2f(0, 0);
    gravity = sf::Vector2f(0, 4000);
    
    jumping = false;
    ropeThrowed = false;
    
    lMouseBtnReleased = true;
    
    fadeTime = 0.2;
    trailGeneration = 0.011;
    
    trailIndex = 0;
    for (int i = 0; i < 20; i++) {
        trails.push_back(Trail());
    }
    
    rope.setFillColor(sf::Color(40, 22, 14));
    rope.setOrigin(1.5, 0);
}

Player::~Player() {
}

void Player::setup() {
    currentFrame = 0;
    
    for (int i = 0; i <= 9; i++) {
        idleTextures.push_back((zt::Textures::instance().getResource("player_idle_" + std::to_string(i))));
        runningTextures.push_back((zt::Textures::instance().getResource("player_run_" + std::to_string(i))));
    }
    
    currentAnimation = &idleTextures;
       
    playerSprite.setTexture(*currentAnimation->at(currentFrame));
    playerSprite.setScale(0.2, 0.2);
    
    playerSprite.setOrigin((*currentAnimation)[0]->getSize().x / 2, (*currentAnimation)[0]->getSize().y);
    
    animationClock.restart();
    
    released = true;
    
    moving = false;
    
    ///////////////////////////////////////
    /// BORRAR XD
    text.setFillColor(sf::Color::Black);
    text.setString("Hola mundo");
    
    
    // Los sensores están situados a partir del origen del personaje que
    // son los pies (y horizontalmente centrado).
    
    // Sensor para los pies.
    sensors.push_back(Sensor(0, 0));
    
    // Sensor para la cabeza.
    //sensors.push_back(Sensor(0, *currentAnimation)[0]->getSize().y));
    
}

void Player::draw(sf::RenderTarget& rt, sf::RenderStates rs) const {
    sf::Sprite trailSprite = playerSprite;
    for (int i = 0; i < trailIndex; i++) {
        if (trails[i].visible) {
            float alpha = 100 * (1 - std::min(trails[i].clock.getElapsedTime().asSeconds() / fadeTime, 1.f));
            
            trailSprite.setColor(sf::Color(255, 255, 255, alpha));
            trailSprite.setPosition(trails[i].pos);
            rt.draw(trailSprite, rs);
        }
    }
    
    if (ropeThrowed) {
        rt.draw(rope, rs);
    }
    
    rt.draw(playerSprite, rs);
    
    
}

void Player::advanceTime(float deltaTime) {
    
    // El incremento de la x y la y se debe hacer por separado
    // para responder bien a la colisión.
    position.y += speed.y * deltaTime;
    if (!gameScene.isValidPosition(position)) {
        position.y -= speed.y * deltaTime;
        speed.y = 0.f;
        jumping = false;
    }
    
    position.x += speed.x * deltaTime;
    if (!gameScene.isValidPosition(position)) {
        position.x -= speed.x * deltaTime;
    }
    
    gameScene.getOrigin().x = position.x;
    gameScene.getOrigin().y = position.y;
    
    // La cuerda ya está enganchada a alguna superficie y el jugador
    // se está acercando hacia el objetivo.
    if (ropeThrowed) {
        rope.setPosition(position);
        rope.setSize(sf::Vector2f(rope.getSize().x, zt::Vector2f(position).minus(ropeTarget).length()));
                
        if (std::signbit(ropeTarget.getX() - position.x) != std::signbit(speed.x) ||
                std::signbit(ropeTarget.getY() - position.y) != std::signbit(speed.y)) {
            ropeThrowed = false;
            speed.x = 0;
            speed.y = 0;
        }
    }
    else {
        // Si se ha lanzado la cuerda la gravedad no afecta.
        speed += gravity * deltaTime;
    }
    
    
    playerSprite.setPosition(position);
    
    if (animationClock.getElapsedTime().asSeconds() > (0.03)) {
        currentFrame++;
        
        if (currentFrame >= currentAnimation->size()) { currentFrame = 0; }
        
        playerSprite.setTexture(*currentAnimation->at(currentFrame), true);
        animationClock.restart();
    }
    
    
    /*if (teleporting) {
        
        
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
    */
    
    for (int i = 0; i < trailIndex; i++) {
        if (trails[i].clock.getElapsedTime().asSeconds() >= fadeTime) {
            trails[i].visible = false;
        }
    }
    
}

void Player::manageEvents(float deltaTime) {
    sf::Vector2f currMousePos = gameScene.getWindow().mapPixelToCoords(sf::Mouse::getPosition(renderWindow)); // Posición del ratón respecto al mundo.
    
    
    zt::Vector2f a(currMousePos.x, currMousePos.y);
    zt::Vector2f b(position.x, position.y);

    /// ROTACIÓN DEL JUGADOR ///
    lookAt = a.minus(b);
    
    moving = false;

    if (!ropeThrowed) {
    
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            if (!jumping) {
                speed.y = -1200;
                jumping = true;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            speed.x = -speedMagnitude;
            playerSprite.setScale(-fabs(playerSprite.getScale().x), playerSprite.getScale().y);
            moving = true;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            speed.x = speedMagnitude;
            playerSprite.setScale(fabs(playerSprite.getScale().x), playerSprite.getScale().y);
            moving = true;
        }
        else {
            speed.x = 0;
        }
        
    }
    
    if (moving) {
        currentAnimation = &runningTextures;
    }
    else {
        currentAnimation = &idleTextures;
    }
    
    /* He deshabilitado el dash.
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (released) {
            released = false;

            zt::TilemapLayer<Tile> layer = gameScene.getSolidLayer();

            float minK;
            bool found = false;

            for (int y = 0; y < gameScene.getMapSize().y; y++) {
                for (int x = 0; x < gameScene.getMapSize().x; x++) {

                    Tile& t = layer.getTile(x, y);

                    if (t.getType() > 0) {


                        std::tuple<bool, float, Tile::Side> res = t.raycast(position, lookAt);

                        if (std::get<0>(res) && (!found || std::get<1>(res) < minK)) {
                            minK = std::get<1>(res);
                            found = true;
                        }


                    }
                }
            }

            if (found) {        
                
                //minK dice cuántas veces el vector lookAt hacen falta
                //para llegar a la intersección. lN = intersección.
                zt::Vector2f lN = lookAt.mult(minK);
                float len = lN.length();
                if (len > 50 && len < 400) {
                    ropeThrowed = true;


                    ropeTarget = zt::Vector2f(position).plus(lN);


                    rope.setSize(sf::Vector2f(3, lN.length()));
                    rope.setRotation(lookAt.getAngle());

                    speed = lN.normalized().mult(1600).toSfml();
                }
            }
        }
    }
    else {
        released = true;
    }
    */
    
    
}