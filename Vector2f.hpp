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

class Vector2f {
    public:
    Vector2f();
    Vector2f(float x, float y);
    
    float getX() const;
    float getY() const;
    
    void setX(float x);
    void setY(float y);
    void set(float x, float y);
    
    float length() const;
    
    void normalize();
    Vector2f normalized() const;
    
    Vector3f cross(const Vector2f& other) const;
    
    float dot(const Vector2f& other) const;
    
    Vector2f plus(const Vector2f& other) const;
    Vector2f minus(const Vector2f& other) const;
    
    Vector2f mult(float s) const;
    
    private:
    float x, y;
};
#endif /* VECTOR2F_HPP */

