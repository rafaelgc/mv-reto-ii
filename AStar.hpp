/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AStar.hpp
 * Author: rafa
 *
 * Created on January 2, 2018, 2:04 AM
 */

#ifndef ASTAR_HPP
#define ASTAR_HPP

#include <vector>
#include <SFML/System/Vector2.hpp>
//Helper class
class MDiscoveredNode {
    public:
    float g;
    float h;
    int x, y;
    int prevX, prevY;
    MDiscoveredNode(int x, int y, int prevX, int prevY, float g = 0, float h = 0) {
        this->g = g;
        this->h = h;
        this->x = x;
        this->y = y;
        this->prevX = prevX;
        this->prevY = prevY;
    }
    
    float f() {
        return g + h;
    }
};

class AStar {
public:
    AStar(int width, int height, int* map);
    virtual ~AStar();
    
    std::vector<sf::Vector2i> run(int, int, int, int);
    
protected:
    int width, height;
    
    float estimate(int, int, int, int);
    float cost(int, int, int, int);
    int smaller();
    bool isClosed(int, int);
    void addOrUpdateOpenList(int x, int y, int prevX, int prevY, float g, float h);
    std::vector<sf::Vector2i> getAdjacent(int x, int y);
private:
    int *map;
    std::vector<MDiscoveredNode> closedList, openList;

};

#endif /* ASTAR_HPP */

