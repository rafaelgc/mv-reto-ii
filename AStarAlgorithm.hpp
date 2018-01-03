/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AStarAlgorithm.hpp
 * Author: rafa
 *
 * Created on January 2, 2018, 8:15 PM
 */

#ifndef ASTARALGORITHM_HPP
#define ASTARALGORITHM_HPP

#include <vector>
#include <set>

template <class NodeType>
class DiscoveredNode {
    public:
    float g;
    float h;
    NodeType node, previousNode;
    bool initial;
    
    DiscoveredNode(const NodeType& node, float g = 0, float h = 0) :
        node(node), g(g), h(h) {
        initial = true;
    }
    
    DiscoveredNode(const NodeType& node, const NodeType& previousNode, float g = 0, float h = 0) :
        node(node), previousNode(previousNode) {
        this->g = g;
        this->h = h;
        initial = false;
    }
    
    DiscoveredNode(const DiscoveredNode& other) {
        node = other.node;
        previousNode = other.previousNode;
        g = other.g;
        h = other.h;
        initial = other.initial;
    }
    
    float f() const {
        return g + h;
    }
    
    inline bool operator==(const DiscoveredNode& other) const {
        return other.node == this->node;
    }
    
    //inline bool operator!=(const DiscoveredNode& other) const 
    
    /*inline bool operator<(const DiscoveredNode& other) const {
        if (other.node == node) {
            return false;
        }
        return f() < other.f();
    }*/
};

class INode {
public:
    //virtual bool operator==(const INode& other) const = 0;
};

template <class NodeType>
class IMesh {
public:
    virtual std::vector<NodeType> getAdjacents(const NodeType& node) const = 0;
    virtual float cost(const NodeType& node1, const NodeType& node2) const = 0;
    virtual float estimate(const NodeType &node1, const NodeType& node2) const = 0;
    virtual void test() const = 0;
};

template <class NodeType>
class AStarAlgorithm {
public:
    AStarAlgorithm(const IMesh<NodeType>& mesh);
    std::vector<NodeType> getPath(NodeType origin, NodeType destination);
    virtual ~AStarAlgorithm();
private:
    const IMesh<NodeType>& mesh;
    std::vector<DiscoveredNode<NodeType>> closedList;
    std::vector<DiscoveredNode<NodeType>> openList;
    
    DiscoveredNode<NodeType> popOpenList();
    void addOrUpdateOpenList(const NodeType& node, const NodeType& previous, float g, float h);
    
    bool isClosed(const NodeType& node);

};

#include "AStarAlgorithm.tpp"

#endif /* ASTARALGORITHM_HPP */

