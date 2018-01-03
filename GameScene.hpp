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
#include "AStar.hpp"

#include "AStarAlgorithm.hpp"

class GridNode {
    sf::Vector2i pos;
public:
    GridNode() { }
    GridNode(int x, int y) { pos = sf::Vector2i(x, y); }
    GridNode(const sf::Vector2i& pos) : pos(pos) { }
    const sf::Vector2i& getPosition() const { return pos; }
    
    bool operator==(const GridNode& other) const {
        return pos.x == other.getPosition().x && pos.y == other.getPosition().y;
    }
};

class Mesh : public IMesh<GridNode> {
private:
    int *map, width, height;
public:
    Mesh(int width, int height, int* map) {
        this->map = map;
        this->width = width;
        this->height = height;
    }
    
    void test() const override {
        std::cout << "Hola" << std::endl;
    }
    
    std::vector<GridNode> getAdjacents(const GridNode& node) const {
        std::vector<GridNode> res;
        int x = node.getPosition().x;
        int y = node.getPosition().y;
        
        for (int rx = x - 1; rx <= x + 1; rx++) {
            for (int ry = y - 1; ry <= y + 1; ry++) {

                if (rx < 0 || ry < 0 || rx >= width || ry >= height) continue;
                if (rx == x && ry == y) continue;
                if (map[ry * width + rx] == 1) continue;

                // Un elemento en las casillas diagonales no será
                // adyacente si en las laterales hay algún obstáculo.
                

                if ((rx == x - 1 && ry == y - 1)) {
                    if (map[(ry + 1) * width + rx] == 1) continue;
                    if (map[ry * width + (rx + 1)] == 1) continue;
                }

                if ((rx == x + 1 && ry == y - 1)) {
                    if (map[(y - 1) * width + x] == 1) continue;
                    if (map[y * width + (x + 1)] == 1) continue;
                }

                if ((rx == x + 1 && ry == y + 1)) {
                    if (map[(y + 1) * width + x] == 1) continue;
                    if (map[y * width + (x + 1)] == 1) continue;
                }

                if ((rx == x - 1 && ry == y + 1)) {
                    if (map[(y + 1) * width + x] == 1) continue;
                    if (map[y * width + (x - 1)] == 1) continue;
                }
                
                res.push_back(GridNode(rx, ry));
            }
        }

        return res;
    }
    
    float cost(const GridNode& node1, const GridNode& node2) const {
        return (node1.getPosition().x == node2.getPosition().x || node1.getPosition().y == node2.getPosition().y) ? 10 : 14;
    }
    
    float estimate(const GridNode& node1, const GridNode& node2) const override {
        return ((node1.getPosition().x - node2.getPosition().x) * 10 * (node1.getPosition().x - node2.getPosition().x) * 10 +
                (node1.getPosition().y - node2.getPosition().y) * 10 * (node1.getPosition().y - node2.getPosition().y) * 10);
    }
};

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
    
    
    bool finished;
    int currentTarget;
    sf::Vector2f deltaMovement;
    
    void calcMovement();
    sf::Vector2i getCharacterTilePosition();
    bool arrivedCurrentTarget();
    
    Mesh mesh;
    AStarAlgorithm<GridNode> pathfinding;
    AStar pathfinding2;
};

#endif /* GAMESCENE_HPP */

