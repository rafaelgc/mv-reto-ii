/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Vector2f.cpp
 * Author: rafa
 * 
 * Created on January 5, 2018, 12:14 PM
 */

#include "Vector2f.hpp"
#include <cmath>
#include <SFML/System/Vector2.hpp>

Vector2f::Vector2f() { x = y = 0.f; }
Vector2f::Vector2f(float x, float y) : x(x), y(y) { }
Vector2f::Vector2f(const sf::Vector2f& v) : x(v.x), y(v.y) {}

float Vector2f::getX() const { return x; }
float Vector2f::getY() const { return y; }

void Vector2f::setX(float x) {
    this->x = x;
}

void Vector2f::setY(float y) {
    this->y = y;
}

void Vector2f::set(float x, float y) {
    this->x = x; this->y = y;
}

float Vector2f::length() const {
    return std::sqrt(x * x + y * y);
}

void Vector2f::normalize() {
    float l = length();
    x /= l;
    y /= l;
}

Vector2f& Vector2f::add(const Vector2f& other) {
    x += other.x;
    y += other.y;
    
    return *this;
}

Vector2f& Vector2f::multiply(float num) {
    x *= num;
    y *= num;
    
    return *this;
}

Vector2f& Vector2f::multiply(float mx, float my) {
    x *= mx;
    y *= my;
    
    return *this;
}


Vector2f Vector2f::normalized() const {
    float l = length();
    return Vector2f(x / l, y / l);
}

Vector3f Vector2f::cross(const Vector2f& other) const {
    return Vector3f(0, 0, x * other.y - other.x * y);
}

float Vector2f::dot(const Vector2f& other) const {
    return x * other.x + y * other.y;
}

Vector2f Vector2f::plus(const Vector2f& other) const {
    return Vector2f(x + other.x, y + other.y);
}
Vector2f Vector2f::minus(const Vector2f& other) const {
    return Vector2f(x - other.x, y - other.y);
}

Vector2f Vector2f::mult(float s) const {
    return Vector2f(x * s, y * s);
}

Vector2f Vector2f::mult(float mx, float my) const {
    return Vector2f(x * mx, y * my);
}

Vector2f& Vector2f::rotate(float angle) {
    angle /= (180 / M_PI);
    float cx = x;
    x = cos(angle) * x - sin(angle) * y;
    y = sin(angle) * cx + cos(angle) * y;
    
    return *this;
}

Vector2f Vector2f::rotated(float angle) const {
    angle /= (180 / M_PI);
    
    return Vector2f(cos(angle) * x - sin(angle) * y, sin(angle) * x + cos(angle) * y);
}

sf::Vector2f Vector2f::toSfml() const {
    return sf::Vector2f(x, y);
}