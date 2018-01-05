/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GridNode.cpp
 * Author: rafa
 * 
 * Created on January 5, 2018, 7:37 PM
 */

#include "GridNode.hpp"

GridNode::GridNode() { }
GridNode::GridNode(int x, int y) { pos = sf::Vector2i(x, y); }
GridNode::GridNode(const sf::Vector2i& pos) : pos(pos) { }
const sf::Vector2i& GridNode::getPosition() const { return pos; }

bool GridNode::operator==(const GridNode& other) const {
    return pos.x == other.getPosition().x && pos.y == other.getPosition().y;
}