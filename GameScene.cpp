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

GameScene::GameScene(sf::RenderWindow * window) : mesh(WIDTH, HEIGHT, map[0]), pathfinding(mesh), pathfinding2(WIDTH, HEIGHT, map[0]), ESE::Scene("GameScene", window) {
    
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
    tiles[0].setFillColor(sf::Color(0, 200, 0));
    
    tiles[1].setSize(tileSize);
    tiles[1].setFillColor(sf::Color(100, 100, 0));
    
    tiles[2].setSize(tileSize);
    tiles[2].setFillColor(sf::Color(0, 150, 0));
    
    character.setRadius(tileSize.x / 2);
    character.setFillColor(sf::Color::White);
    character.setPosition(character.getRadius(), character.getRadius());
    character.setOrigin(character.getRadius(), character.getRadius());
    
    finished = true;
    
}

void GameScene::manageEvents(float deltaTime) {
    
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
        int cx = sf::Mouse::getPosition(*this->window).x / (tiles[0].getSize().x);
        int cy = sf::Mouse::getPosition(*this->window).y / (tiles[0].getSize().y);

        map[cy][cx] = 1;
    }
    
    while (this->window->pollEvent(this->events)) {
        this->checkIfWindowClosed();
        
        if (events.type == sf::Event::MouseButtonPressed)
        {
            if (events.mouseButton.button == sf::Mouse::Left) {
                int cx = events.mouseButton.x / (tiles[0].getSize().x);
                int cy = events.mouseButton.y / (tiles[0].getSize().y);
                
                //std::cout << "Running original..." << std::endl;
                
                float millis1 = 0;
                float millis2 = 0;
                for (int i = 0; i < 100; i++) {
                    auto begin = std::chrono::high_resolution_clock::now();
                    try {
                        pathfinding2.run(
                        character.getPosition().x / tiles[0].getSize().x, 
                        character.getPosition().y / tiles[0].getSize().y,
                        cx, cy);
                    } catch (std::exception e) {}
                    auto end = std::chrono::high_resolution_clock::now();

                    millis1 += std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count() / 1000000.f;

                    //std::cout << "Original: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count() / 1000000.f << " with " << success << std::endl;
                    //std::cout << "Running current..." << std::endl;
                    begin = std::chrono::high_resolution_clock::now();
                    try {
                    pathfinding.getPath(
                        GridNode(character.getPosition().x / tiles[0].getSize().x,
                            character.getPosition().y / tiles[0].getSize().y),
                        GridNode(cx, cy));
                    } catch (std::exception e) {}
                    end = std::chrono::high_resolution_clock::now();

                    millis2 += std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count() / 1000000.f;

                }
                std::cout << millis1 / 100 << " vs " << millis2 / 100 << " Diff> " << (millis2 / millis1) * 100 << std::endl;
                
                try {
                    characterPath = pathfinding.getPath(
                            GridNode(character.getPosition().x / tiles[0].getSize().x,
                                character.getPosition().y / tiles[0].getSize().y),
                            GridNode(cx, cy));
                
                    for (int i = 0; i < HEIGHT; i++) {
                        for (int j = 0; j < WIDTH; j++) {
                            if (map[i][j] == 2) map[i][j] = 0;
                        }
                    }
                    for (int i = 0; i < characterPath.size(); i++) {
                        map[characterPath[i].getPosition().y][characterPath[i].getPosition().x] = 2;
                    }

                    if (characterPath.size() > 1) {
                        currentTarget = 1;
                        finished = false;
                        calcMovement();
                    }
                }
                catch (std::exception e) {
                }
                
                
            }
            
        }
    }
}

void GameScene::logic(float deltaTime) {
    
    if (!finished) {
        //std::cout << "Xd " << mX << std::endl;
        character.move(deltaMovement.x * 100 * deltaTime, deltaMovement.y * 100 * deltaTime);
        
        if (arrivedCurrentTarget()) {
            currentTarget++;
            if (currentTarget >= characterPath.size()) {
                finished = true;
            }
            else {
                calcMovement();
            }
        }
    }
    
}

void GameScene::render() {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            tiles[map[y][x]].setPosition(x * tiles[map[y][x]].getSize().x, y * tiles[map[y][x]].getSize().y);
            this->draw(tiles[map[y][x]]);
        }
    }
    
    draw(character);
}

void GameScene::calcMovement() {
    deltaMovement.x = this->characterPath[currentTarget].getPosition().x * this->tileSize.x + this->tileSize.x / 2 - character.getPosition().x;
    deltaMovement.y = this->characterPath[currentTarget].getPosition().y * this->tileSize.y + this->tileSize.y / 2 - character.getPosition().y;
    
    float h = std::sqrt(deltaMovement.x * deltaMovement.x + deltaMovement.y * deltaMovement.y);
    
    deltaMovement /= h;
}

sf::Vector2i GameScene::getCharacterTilePosition() {
    return sf::Vector2i(character.getPosition().x / tileSize.x, character.getPosition().y / tileSize.y);
}

bool GameScene::arrivedCurrentTarget() {
    float dx = character.getPosition().x - (this->characterPath[currentTarget].getPosition().x * tileSize.x + tileSize.x / 2);
    float dy = character.getPosition().y - (this->characterPath[currentTarget].getPosition().y * tileSize.y + tileSize.y / 2);
    
    if (std::sqrt(dx * dx + dy * dy) < 10) {
        return true;
    }
    return false;
}