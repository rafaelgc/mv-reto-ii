/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Drop.cpp
 * Author: rafa
 * 
 * Created on January 6, 2018, 2:25 PM
 */

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Clock.hpp>
#include <cmath>

#include "Drop.hpp"
#include "GameScene.hpp"

Drop::Drop(GameScene& gameScene, const zt::Vector2f& position, const zt::Vector2f& speed, float angle, float alpha, bool calcIntersection) : Particle(position, speed) {
    rect.setFillColor(sf::Color(100, 100, 100, alpha));
    rect.setSize(sf::Vector2f(1, 5));
    rect.setPosition(position.toSfml());
    rect.setRotation(angle);
    
    target.setFillColor(sf::Color::Red);
    target.setSize(sf::Vector2f(2, 2));
    
    hasEnd = false;
    
    if (calcIntersection) {
    
        int left = std::max(0, gameScene.getVisibleArea().left) / gameScene.getSolidLayer().getTileSize().x;
        int right = std::min(gameScene.getSolidLayer().getSize().x, left + gameScene.getVisibleArea().width / gameScene.getSolidLayer().getTileSize().x);

        int top = std::max(0, gameScene.getVisibleArea().top) / gameScene.getSolidLayer().getTileSize().y;
        int bottom = std::min(gameScene.getSolidLayer().getSize().y, top + gameScene.getVisibleArea().height / gameScene.getSolidLayer().getTileSize().y);

        float minF;
        bool found = false;


        for (int y = top; y <= bottom; y++) {

            for (int x = left; x <= right; x++) {

                if (!gameScene.getSolidLayer().isEmpty(x, y)) {
                    std::tuple<bool, float, Tile::Side> res = gameScene.getSolidLayer().getTile(x, y).raycast(position.toSfml(), speed.toSfml());

                    if (std::get<0>(res) && (!found || std::get<1>(res) < minF)) {
                        minF = std::get<1>(res);
                        found = true;
                    }
                }

            }

        }

        if (found) {
            end = position.plus(speed.mult(minF));

            target.setPosition(end.getX(), end.getY());
            hasEnd = true;
        }
    
    }
}

Drop::~Drop() {
}

void Drop::draw(sf::RenderTarget& rt, sf::RenderStates rs) const {
    rt.draw(rect, rs);
    
    if (hasEnd) {
        rt.draw(target, rs);
    }
}

void Drop::advanceTime(float deltaTime) {
    Particle::advanceTime(deltaTime);
    rect.setPosition(position.toSfml());
}

bool Drop::isRemovable() const {
    
    if (hasEnd) {
        if (std::signbit(end.getX() - position.getX()) != std::signbit(speed.getX()) ||
                std::signbit(end.getY() - position.getY()) != std::signbit(speed.getY())) {
            return true;
        }
    }
    
    return position.getY() > 2000;
}