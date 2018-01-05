/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GridNode.hpp
 * Author: rafa
 *
 * Created on January 5, 2018, 7:37 PM
 */

#ifndef GRIDNODE_HPP
#define GRIDNODE_HPP

#include <SFML/System/Vector2.hpp>

class GridNode {
    sf::Vector2i pos;
public:
    GridNode();
    GridNode(int x, int y);
    GridNode(const sf::Vector2i& pos);
    const sf::Vector2i& getPosition() const;
    bool operator==(const GridNode& other) const;
};

#endif /* GRIDNODE_HPP */

