/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GameScene.cpp
 * Author: rafa
 * 
 * Created on January 2, 2018, 1:19 AM
 */

#include "GameScene.hpp"
#include "Enemy.hpp"
#include "ESE/Core/Textures.hpp"
#include "ESE/Core/SoundBuffers.hpp"
#include <ESE/Core/Textures.hpp>

GameScene::GameScene(sf::RenderWindow * window) : mesh(WIDTH, HEIGHT, map[0]), pathfinding(mesh), player(*this->window, *this), /*pathfinding2(WIDTH, HEIGHT, map[0]), */ESE::Scene("GameScene", window) {
    
    ESE::Textures::instance().loadFromFile("shoot_fire", "images/shoot.png");
    
    ESE::Textures::instance().loadFromFile("survivor_idle_feet", "images/feet/idle/survivor-idle_0.png");
    for (int i = 0; i <= 19; i++) {
        ESE::Textures::instance().loadFromFile("survivor_rifle_idle_" + std::to_string(i) ,"images/rifle/idle/survivor-idle_rifle_" + std::to_string(i) + ".png");
        ESE::Textures::instance().loadFromFile("survivor_rifle_move_" + std::to_string(i) ,"images/rifle/move/survivor-move_rifle_" + std::to_string(i) + ".png");
        
        ESE::Textures::instance().loadFromFile("survivor_walk_" + std::to_string(i) ,"images/feet/run/survivor-run_" + std::to_string(i) + ".png");
    }
    
    for (int i = 0; i <= 2; i++) {
        ESE::Textures::instance().loadFromFile("survivor_shoot_rifle_" + std::to_string(i), "images/rifle/shoot/survivor-shoot_rifle_" + std::to_string(i) + ".png");
    }
    
    for (int i = 0; i <= 16; i++) {
        ESE::Textures::instance().loadFromFile("zombie_" + std::to_string(i), "images/zombie_walking/skeleton-move_" + std::to_string(i) + ".png");
    }
    
    ESE::SoundBuffers::instance().loadFromFile("shot", "sounds/ren.ogg");
    
    
}

GameScene::~GameScene() {
}

void GameScene::setup() {
    
    player.setup();
    
    tileSize = sf::Vector2f(window->getSize().x / WIDTH, window->getSize().y / HEIGHT);
    
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            map[y][x] = 0;
        }
    }
    
    tiles[0].setSize(tileSize);
    tiles[0].setFillColor(sf::Color(0, 120, 0));
    
    tiles[1].setSize(tileSize);
    tiles[1].setFillColor(sf::Color(100, 100, 0));
    
    tiles[2].setSize(tileSize);
    tiles[2].setFillColor(sf::Color(0, 150, 0));
    
    /*for (int i = 0; i < 1; i++) {
        Enemy enemy(particleManager);
        enemy.setPosition(sf::Vector2f(rand() % window->getSize().x, rand() % window->getSize().y));
        enemy.setup();
        
        enemies.push_back(enemy);
    }*/
    addRandomEnemy(0);
    
    
    pathfindingClock.restart();
    
}

void GameScene::manageEvents(float deltaTime) {
    
    player.manageEvents(deltaTime);
    
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle)) {
        int cx = sf::Mouse::getPosition(*this->window).x / (tiles[0].getSize().x);
        int cy = sf::Mouse::getPosition(*this->window).y / (tiles[0].getSize().y);

        map[cy][cx] = 1;
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)) {
        int cx = sf::Mouse::getPosition(*this->window).x / (tiles[0].getSize().x);
        int cy = sf::Mouse::getPosition(*this->window).y / (tiles[0].getSize().y);

        map[cy][cx] = 1;
    }
    
    while (this->window->pollEvent(this->events)) {
        this->checkIfWindowClosed();
    }
}

void GameScene::logic(float deltaTime) {
    player.advanceTime(deltaTime);
    
    if (enemiesSpawnClock.getElapsedTime().asSeconds() > 5) {
        addRandomEnemy();
        enemiesSpawnClock.restart();
    }
    
    for (auto &enemy : enemies) {
        enemy.advanceTime(deltaTime);
    }
    
    
    if (pathfindingClock.getElapsedTime().asSeconds() > 1) {
        
        try {
            for (auto &enemy : enemies) {
                std::vector<GridNode> path = 
                pathfinding.getPath(GridNode(enemy.getPosition().x / tileSize.x, enemy.getPosition().y / tileSize.y),
                    GridNode(player.getPosition().x / tileSize.x, player.getPosition().y / tileSize.y));
            
                enemy.setPath(path, tileSize);
            }
            
        } catch (std::exception e) {
            
        }
        
        pathfindingClock.restart();
    }
    
    particleManager.advanceTime(deltaTime);
   
}

void GameScene::render() {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            tiles[map[y][x]].setPosition(x * tiles[map[y][x]].getSize().x, y * tiles[map[y][x]].getSize().y);
            this->draw(tiles[map[y][x]]);
        }
    }
    
    for (auto &enemy : enemies) {
        draw(enemy);
    }
    
    draw(player);
    
    draw(particleManager);
}

std::vector<Enemy>& GameScene::getEnemies() {
    return enemies;
}

void GameScene::addRandomEnemy(int pside) {
    std::cout << pside << std::endl;
    int side = (pside != -1) ? 0 : rand() % 3;
    
    Enemy e(particleManager);
    e.setup();
    
    
    //Aparece arriba izda.
    if (side == 0) {
        std::cout << "Arriba izda" << std::endl;
        e.setPosition(sf::Vector2f(0, 0));
    }
    else if (side == 1) {
        //Arriba dcha.
        e.setPosition(sf::Vector2f(window->getSize().x, 0));
    }
    else if (side == 2) {
        //Abajo dcha.
        e.setPosition(sf::Vector2f(window->getSize().x, window->getSize().y));
    }
    else {
        //Abajo izda.
        e.setPosition(sf::Vector2f(0, window->getSize().y));
        std::cout << "Abajo izda" << std::endl;
    }
    
    enemies.push_back(e);
}