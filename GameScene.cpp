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

GameScene::GameScene(sf::RenderWindow * window) : mesh(WIDTH, HEIGHT, map[0]), pathfinding(mesh), player(*this->window), /*pathfinding2(WIDTH, HEIGHT, map[0]), */ESE::Scene("GameScene", window) {
    
}

GameScene::~GameScene() {
}

void GameScene::setup() {
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
    
    character.setRadius(tileSize.x / 2);
    character.setFillColor(sf::Color::White);
    character.setPosition(character.getRadius(), character.getRadius());
    character.setOrigin(character.getRadius(), character.getRadius());
    
    //enemy.setPosition(sf::Vector2f(200, 200));
    
    for (int i = 0; i < 2; i++) {
        Enemy enemy;
        enemy.setPosition(sf::Vector2f(rand() % window->getSize().x, rand() % window->getSize().y));
        
        enemies.push_back(enemy);
    }
    
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
    //draw(character);
}
