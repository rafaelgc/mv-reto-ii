/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AStar.cpp
 * Author: rafa
 * 
 * Created on January 2, 2018, 2:04 AM
 */

#include "AStar.hpp"

#include <iostream>
#include <cmath>
#include <chrono>
#include <SFML/System/Vector2.hpp>

AStar::AStar(int width, int height, int* map) {
    this->map = map;
    this->width = width;
    this->height = height;
}

AStar::~AStar() {
}

std::vector<sf::Vector2i> AStar::run(int originX, int originY, int targetX, int targetY) {
    openList.clear();
    closedList.clear();
    
    MDiscoveredNode origin(originX, originY, -1, -1, 0, estimate(originX, originY, targetX, targetY));
    
    openList.push_back(origin);
    
    bool success = false;
    
    int c1 = 0;
    
    while (!openList.empty()) {
        c1++;
        int index = smaller();
        
        MDiscoveredNode cf = openList[index];
        openList.erase(openList.begin() + index);
        
        closedList.push_back(cf);
        
        if (cf.x == targetX && cf.y == targetY) {
            success = true;
            break;
        }
        
        std::vector<sf::Vector2i> res = this->getAdjacent(cf.x, cf.y);
        
        for (auto adj : res) {
            if (!isClosed(adj.x, adj.y)) {
                float g = cf.g + cost(cf.x, cf.y, adj.x, adj.y);
                float h = estimate(adj.x, adj.y, targetX, targetY);

                addOrUpdateOpenList(adj.x, adj.y, cf.x, cf.y, g, h);
            }
        }
        
    }
    
    //std::cout << "Previous C1: " << c1 << std::endl;
    
    //std::cout << "Open: " << openList.size() << std::endl;
    //std::cout << "closed: " << closedList.size() << std::endl;
    
    std::vector<sf::Vector2i> path;
    if (success) {
        MDiscoveredNode& f = closedList.back();
        int sX = f.prevX;
        int sY = f.prevY;
        
        path.insert(path.begin(), sf::Vector2i(f.x, f.y));
        
        while (sX >= 0) {
            for (int i = 0; i < closedList.size(); i++) {
                if (closedList[i].x == sX && closedList[i].y == sY) {
                    sX = closedList[i].prevX;
                    sY = closedList[i].prevY;
                    path.insert(path.begin(), sf::Vector2i(closedList[i].x, closedList[i].y));
                    break;
                }
            }
        }
    }
    else {
        ////////////////throw std::exception();
    }
    
    return path;
}

bool AStar::isClosed(int x, int y) {
    for (MDiscoveredNode& f : closedList) {
        if (f.x == x && f.y == y) return true;
    }
    
    return false;
}

void AStar::addOrUpdateOpenList(int x, int y, int prevX, int prevY, float g, float h) {
    bool already = false;
    for (MDiscoveredNode& fr : openList) {
        if (fr.x == x && fr.y == y) {
            already = true;
            if (g < fr.g) {
                fr.prevX = prevX;
                fr.prevY = prevY;
                fr.g = g;
                //fr.h = fr.accumulatedCost + cost()
            }
            
            break;
        }
    }
    
    if (!already) {
        openList.push_back(MDiscoveredNode(x, y, prevX, prevY, g, h));
    }
    
}

int AStar::smaller() {
    int index = -1;
    float minF = 0;
    for (int i = 0; i < openList.size(); i++) {
        if (index == -1 || openList[i].f() < minF) {
            minF = openList[i].f();
            index = i;
        }
    }
    
    return index;
}

std::vector<sf::Vector2i> AStar::getAdjacent(int x, int y) {
    std::vector<sf::Vector2i> res;
    
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

            //if (isClosed(rx, ry)) continue;

            res.push_back(sf::Vector2i(rx, ry));

        }
    }
    
    return res;
}

float AStar::cost(int x, int y, int x2, int y2) {
    return (x == x2 || y == y2) ? 10 : 14;
}

float AStar::estimate(int x, int y, int x2, int y2) {
    return std::sqrt((x - x2) * 10 * (x - x2) * 10 + (y - y2) * 10 * (y - y2) * 10);
}
