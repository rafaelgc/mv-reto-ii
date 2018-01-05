/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GameScene.hpp
 * Author: rafa
 *
 * Created on January 2, 2018, 1:19 AM
 */

#ifndef GAMESCENE_HPP
#define GAMESCENE_HPP

#include <ESE/Core/Scene.hpp>
//#include "AStar.hpp"

#include "Player.hpp"
#include "Enemy.hpp"

#include "Pathfinding.hpp"
#include "GridMesh.hpp"
#include "GridNode.hpp"

class GameScene : public ESE::Scene {
public:
    GameScene(sf::RenderWindow *windwow);
    GameScene(const GameScene& orig);
    virtual ~GameScene();
    
    void setup();
    
    void manageEvents(float deltaTime);
    void logic(float deltaTime);
    void render();
    
private:
    static const int WIDTH = 20;
    static const int HEIGHT = 15;
    int map[HEIGHT][WIDTH];
    sf::Vector2f tileSize;
    
    sf::RectangleShape tiles[3];
    sf::CircleShape character;
    std::vector<GridNode> characterPath;
    
    Player player;
    std::vector<Enemy> enemies;
    GridMesh mesh;
    
    AStarAlgorithm<GridNode> pathfinding;
    sf::Clock pathfindingClock;
};

#endif /* GAMESCENE_HPP */
