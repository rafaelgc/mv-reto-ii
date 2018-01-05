/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Vector3f.hpp
 * Author: rafa
 *
 * Created on January 5, 2018, 12:14 PM
 */

#ifndef VECTOR3F_HPP
#define VECTOR3F_HPP

class Vector3f {
    public:
    Vector3f();
    Vector3f(float x, float y, float z);
    
    float getX() const;
    float getY() const;
    float getZ() const;
    
    private:
    float x, y, z;
};

#endif /* VECTOR3F_HPP */

