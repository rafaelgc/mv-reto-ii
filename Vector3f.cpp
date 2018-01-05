/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Vector3f.cpp
 * Author: rafa
 * 
 * Created on January 5, 2018, 12:14 PM
 */

#include "Vector3f.hpp"

Vector3f::Vector3f() { x = y = z = 0.f; }
Vector3f::Vector3f(float x, float y, float z) : x(x), y(y), z(z) { }

float Vector3f::getX() const { return x; }
float Vector3f::getY() const { return y; }
float Vector3f::getZ() const { return z; }
