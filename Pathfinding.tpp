/* 
 * File:   AStarAlgorithm.cpp
 * Author: rafa
 * 
 * Created on January 2, 2018, 8:15 PM
 */

#include "Pathfinding.hpp"

#include <chrono>

//#include "AStarAlgorithm.hpp"

template <class NodeType>
AStarAlgorithm<NodeType>::AStarAlgorithm(const IMesh<NodeType>& mesh) : mesh(mesh){
}

template <class NodeType>
AStarAlgorithm<NodeType>::~AStarAlgorithm() {
}

template <class NodeType>
std::vector<NodeType> AStarAlgorithm<NodeType>::getPath(NodeType originNode, NodeType destination) {
    openList.clear();
    closedList.clear();
    
    DiscoveredNode<NodeType> origin(originNode, 0, mesh.estimate(originNode, destination));
    openList.push_back(origin);
    
    bool success = false;
    
    int c1 = 0;
    
    while (!openList.empty()) {
        c1++;

        DiscoveredNode<NodeType> cf = popOpenList();
        
        closedList.push_back(cf);
        
        if (cf == destination) {
            success = true;
            break;
        }
        
        std::vector<NodeType> adjs = mesh.getAdjacents(cf.node);

        for (NodeType adj : adjs) {
            bool closed = isClosed(adj);
            
            if (!closed) {
                float g = cf.g + mesh.cost(cf.node, adj);
                float h = mesh.estimate(adj, destination);
                
                this->addOrUpdateOpenList(adj, cf.node, g, h);
            }
        }
        
    }
    
    std::vector<NodeType> path;
    if (success) {
        //std::cout << "Reconstructing..." << std::endl;
        
        DiscoveredNode<NodeType>& f = closedList.back();
                
        NodeType nt = f.previousNode;
        
        path.insert(path.begin(), f.node);
        
        bool initial = f.initial;
        
        while (!initial) {
            for (int i = 0; i < closedList.size(); i++) {
                if (closedList[i].node == nt) {
                    initial = closedList[i].initial;
                    nt = closedList[i].previousNode;
                    path.insert(path.begin(), closedList[i].node);
                    break;
                }
            }
        }
    }
    else {
        throw std::exception();
    }
    
    
    return path;
}

template <class NodeType>
DiscoveredNode<NodeType> AStarAlgorithm<NodeType>::popOpenList() {
    //openList no debe estar vacia.
    int index = -1;
    float minF = 0;
    for (int i = 0; i < openList.size(); i++) {
        if (index == -1 || openList[i].f() < minF) {
            minF = openList[i].f();
            index = i;
        }
    }
    
    DiscoveredNode<NodeType> res = openList[index];
    openList.erase(openList.begin() + index);
    
    return res;
}

template <class NodeType>
void AStarAlgorithm<NodeType>::addOrUpdateOpenList(const NodeType& node, const NodeType& previous, float g, float h) {
    bool already = false;
    for (DiscoveredNode<NodeType>& fr : openList) {
        if (fr.node == node) {
            already = true;
            if (g < fr.g) {
                fr.previousNode = previous;
                fr.g = g;
            }
            
            break;
        }
    }
    
    if (!already) {
        openList.push_back(DiscoveredNode<NodeType>(node, previous, g, h));
    }
    
    
    
}

template <class NodeType>
bool AStarAlgorithm<NodeType>::isClosed(const NodeType& node) {
    
    for (const DiscoveredNode<NodeType>& f : closedList) {
        if (f.node == node) {
            return true;
        }
    }
    return false;
}