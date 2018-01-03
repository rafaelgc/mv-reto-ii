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

App::App() : gameScene(&this->window) {
    //getWindow().create();
    window.create(sf::VideoMode(800, 600), "Pathfinding");
    
    gameScene.setup();
    
    this->getSceneManager()->addScene(gameScene);
    this->getSceneManager()->activateSceneAndDeactivateTheRest("GameScene");
}

App::~App() {
}

