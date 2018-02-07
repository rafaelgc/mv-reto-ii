/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   App.hpp
 * Author: rafa
 *
 * Created on January 2, 2018, 1:07 AM
 */

#ifndef APP_HPP
#define APP_HPP

#include <Zelta/Core/Application.hpp>

#include "GameScene.hpp"

class App : public zt::Application {
public:
    App(int argc, char** argv);
    virtual ~App();
private:
    GameScene gameScene;
};

#endif /* APP_HPP */

