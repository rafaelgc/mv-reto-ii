/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BloodDrop.hpp
 * Author: rafa
 *
 * Created on January 6, 2018, 2:25 PM
 */

#ifndef DROP_HPP
#define DROP_HPP

#include "Particle.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class GameScene;

class Drop : public Particle {
public:
    Drop();
    Drop(GameScene& gameScene, const zt::Vector2f& position, const zt::Vector2f& speed, float angle, float alpha = 255, bool calcIntersection = false);
    virtual ~Drop();
    
    void draw(sf::RenderTarget&, sf::RenderStates) const override;
    void advanceTime(float deltaTime) override;
    
    bool isRemovable() const;
private:
    sf::RectangleShape rect, target;
    bool hasEnd;
    zt::Vector2f end;
    
};

#endif /* BLOODDROP_HPP */

