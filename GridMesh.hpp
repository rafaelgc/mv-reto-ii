/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GridMesh.hpp
 * Author: rafa
 *
 * Created on January 5, 2018, 7:33 PM
 */

#ifndef GRIDMESH_HPP
#define GRIDMESH_HPP

#include <Zelta/AI/Pathfinding.hpp>
#include "GridNode.hpp"

class GridMesh : public zt::IMesh<GridNode> {
private:
    int *map, width, height;
public:
    GridMesh(int width, int height, int* map);
    
    std::vector<GridNode> getAdjacents(const GridNode& node) const override;
    
    float cost(const GridNode& node1, const GridNode& node2) const override;
    
    float estimate(const GridNode& node1, const GridNode& node2) const override;
};

#endif /* GRIDMESH_HPP */

