/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   App.cpp
 * Author: rafa
 * 
 * Created on January 2, 2018, 1:07 AM
 */

#include <SFML/Window/Window.hpp>

#include "App.hpp"

App::App(int argc, char** argv) : zt::Application(argc, argv), gameScene(this->window) {
    int width = 800;
    int height = 600;
    
    if (getArguments().size() == 3) {
        width = getArguments().get(1).toInt();
        height = getArguments().get(2).toInt();
    }
    
    window.create(sf::VideoMode(width,height), "mediavida-reto-ii");
    
    gameScene.setup();
    
    this->getSceneManager()->addScene(gameScene);
    this->getSceneManager()->switchTo("GameScene");
}

App::~App() {
}

