/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Vector2f.hpp
 * Author: rafa
 *
 * Created on January 5, 2018, 12:14 PM
 */

#ifndef VECTOR2F_HPP
#define VECTOR2F_HPP

#include "Vector3f.hpp"
#include <SFML/System/Vector2.hpp>

class Vector2f {
    public:
    Vector2f();
    Vector2f(float x, float y);
    Vector2f(const sf::Vector2f& v);
    
    float getX() const;
    float getY() const;
    
    float length() const;
    
    /// MODIFICADORES ///
    void setX(float x);
    void setY(float y);
    void set(float x, float y);
    
    void normalize();
    
    Vector2f& add(const Vector2f& other);
    Vector2f& multiply(float num);
    Vector2f& multiply(float x, float y);
    
    Vector2f& rotate(float angle);
    
    /// NO MODIFICADORES ///
    Vector2f normalized() const;
    
    Vector3f cross(const Vector2f& other) const;
    
    float dot(const Vector2f& other) const;
    
    Vector2f plus(const Vector2f& other) const;
    Vector2f minus(const Vector2f& other) const;
    
    Vector2f mult(float s) const;
    Vector2f mult(float x, float y) const;
    
    Vector2f rotated(float angle) const;
    
    sf::Vector2f toSfml() const;
    
    private:
    float x, y;
};
#endif /* VECTOR2F_HPP */

