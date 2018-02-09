/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Tile.hpp
 * Author: rafa
 *
 * Created on January 24, 2018, 8:23 PM
 */

#ifndef TILE_HPP
#define TILE_HPP

#include <utility>
#include <SFML/System/Vector2.hpp>
#include <tuple>

class Tile : public sf::Transformable, public sf::Drawable {
protected:
    int type;
    float water;
    sf::Sprite tile;
    sf::RectangleShape waterRect;
    sf::Vector2f tileSize;
    
public:
    enum Side { TOP, LEFT, RIGHT, BOTTOM };
    
    Tile() {
        type = 0;
        waterRect.setFillColor(sf::Color(71, 113, 135, 150));
        water = 0.0f;
    }
    
    Tile(const sf::Vector2f& tileSize) : Tile() {
        this->tileSize = tileSize;
    }
    void setTileSize(const sf::Vector2f& tileSize) {
        this->tileSize = tileSize;
    };
    void setType(int type) { this->type = type; }
    int getType() { return type; }
    
    void updateWater() {
        waterRect.setSize(sf::Vector2f(tileSize.x, water * tileSize.y));
        waterRect.setPosition(0, tileSize.y * (1 - water));
    }
    
    void setWater(float water) {
        this->water = water;
        updateWater();
    }
    
    void fill(float incr) {
        this->water += incr;
        if (water > 1.f) { water = 1.f; }
        else if (water < 0.f) { water = 0.f; }
        
        updateWater();
    }
    
    float getWater() {
        return water;
    }
    
    void draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) const {
        renderStates.transform *= this->getTransform();
        
        renderTarget.draw(tile, renderStates);
        renderTarget.draw(waterRect, renderStates);
    }
    
    void setPosition(float x, float y) {
        sf::Transformable::setPosition(x, y);
        updateWater();
    }
    
    void setPosition(const sf::Vector2f& position) {
        sf::Transformable::setPosition(position.x, position.y);
        //updateWater();
    }
    
    void setTexture(const sf::Texture& texture, bool resetRect = false) {
        tile.setTexture(texture, resetRect);
        updateWater();
    }
    
    const sf::Vector2f& getSize() const {
        return tileSize;
        //return sf::Vector2f(64, 64);
    }
    
    zt::Vector2f getHorizontalVector() const {
        return zt::Vector2f(this->tileSize.x, 0);
    }
    
    zt::Vector2f getVerticalVector() const {
        return zt::Vector2f(0, this->tileSize.y);
    }
    
    zt::Vector2f getTopLeft() const {
        return zt::Vector2f(this->getPosition());
    }
    
    zt::Vector2f getTopRight() const {
        return zt::Vector2f(this->getPosition()).plus(getHorizontalVector());
    }
    
    zt::Vector2f getBottomLeft() const {
        return getTopLeft().plus(getVerticalVector());
    }
    
    zt::Vector2f getBottomRight() const {
        return getBottomLeft().plus(getHorizontalVector());
    }
    
    zt::Vector2f getSideVector(Side side) const {
        if (side == Side::TOP) return getHorizontalVector();
        if (side == Side::BOTTOM) return getHorizontalVector();
        if (side == Side::LEFT) return getVerticalVector();
        else getVerticalVector();
    }
    
    std::tuple<bool, float, Side> raycast(const sf::Vector2f& position, const zt::Vector2f& vector) {
        // TOP
        Side side;
        float minK;
        bool found = false;
        sf::Vector2f intersection;
        float k = getTopLeft().minus(zt::Vector2f(position)).cross(getHorizontalVector()).getZ() / vector.cross(getHorizontalVector()).getZ();
        float p = zt::Vector2f(position).minus(getTopLeft()).cross(vector).getZ() / getHorizontalVector().cross(vector).getZ();

        if (p >= 0 && p <= 1.f && k >= 0.f) {
            if (!found || k < minK) {
                minK = k;
                side = TOP;
                found = true;
            }
        }


        // BOTTOM
        k = getBottomLeft().minus(zt::Vector2f(position)).cross(getHorizontalVector()).getZ() / vector.cross(getHorizontalVector()).getZ();
        p = zt::Vector2f(position).minus(getBottomLeft()).cross(vector).getZ() / getHorizontalVector().cross(vector).getZ();

        if (p >= 0 && p <= 1.f && k >= 0.f) {
            if (!found || k < minK) {
                minK = k;
                side = BOTTOM;
                found = true;
            }
        }

        // LEFT
        k = getTopLeft().minus(zt::Vector2f(position)).cross(getVerticalVector()).getZ() / vector.cross(getVerticalVector()).getZ();
        p = zt::Vector2f(position).minus(getTopLeft()).cross(vector).getZ() / getVerticalVector().cross(vector).getZ();

        if (p >= 0 && p <= 1.f && k >= 0.f) {
            if (!found || k < minK) {
                minK = k;
                side = LEFT;
                found = true;
            }
        }

        // RIGHT
        k = getTopRight().minus(zt::Vector2f(position)).cross(getVerticalVector()).getZ() / vector.cross(getVerticalVector()).getZ();
        p = zt::Vector2f(position).minus(getTopRight()).cross(vector).getZ() / getVerticalVector().cross(vector).getZ();

        if (p >= 0 && p <= 1.f && k >= 0.f) {
            if (!found || k < minK) {
                minK = k;
                side = RIGHT;
                found = true;
            }
        }

        return std::make_tuple(found, minK, side);
    }
};

#endif /* TILE_HPP */

