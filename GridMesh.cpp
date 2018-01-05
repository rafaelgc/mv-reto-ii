/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GridMesh.cpp
 * Author: rafa
 * 
 * Created on January 5, 2018, 7:33 PM
 */

#include "GridMesh.hpp"
#include <cmath>

GridMesh::GridMesh(int width, int height, int* map) {
    this->map = map;
    this->width = width;
    this->height = height;
}

std::vector<GridNode> GridMesh::getAdjacents(const GridNode& node) const {
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

float GridMesh::cost(const GridNode& node1, const GridNode& node2) const {
    return (node1.getPosition().x == node2.getPosition().x || node1.getPosition().y == node2.getPosition().y) ? 10 : 14.1421356237;
}

float GridMesh::estimate(const GridNode& node1, const GridNode& node2) const {
    return sqrt((node1.getPosition().x - node2.getPosition().x) * 10 * (node1.getPosition().x - node2.getPosition().x) * 10 +
            (node1.getPosition().y - node2.getPosition().y) * 10 * (node1.getPosition().y - node2.getPosition().y) * 10);
}