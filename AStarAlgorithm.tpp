/* 
 * File:   AStarAlgorithm.cpp
 * Author: rafa
 * 
 * Created on January 2, 2018, 8:15 PM
 */

#include "AStarAlgorithm.hpp"

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

        //int index = this->smallerNodeInOpenList();
        DiscoveredNode<NodeType> cf = popOpenList();
        
        
        //std::cout << "Start loop " << cf.node.getPosition().x << ", " << cf.node.getPosition().y << std::endl;
        /*DiscoveredNode<NodeType> cf = openList[index];
        openList.erase(openList.begin() + index);*/
        
        closedList.push_back(cf);
        
        //std::cout << "Openlist: " << openList.size() << "Closed list: " << closedList.size() << std::endl;
        
        if (cf == destination) {
            success = true;
            //std::cout << "Destination reached" << std::endl;
            break;
        }
        
        //std::vector<NodeType> res = mesh.getAdjacents(cf.node);
        std::vector<NodeType> adjs = mesh.getAdjacents(cf.node);
        
        //std::cout << "CURRENT NODE: " << cf.node.getPosition().x << ", " << cf.node.getPosition().y << std::endl;
        /*for (DiscoveredNode<NodeType>& f : closedList) {
            std::cout << "Closed list: " << f.node.getPosition().x << ", " << f.node.getPosition().y << std::endl;
        }
        for (DiscoveredNode<NodeType>& f : openList) {
            std::cout << "Open list: " << f.node.getPosition().x << ", " << f.node.getPosition().y << std::endl;
        }
        std::cout << "NUM. ADJACENTS: " << res.size() << std::endl;*/
        for (NodeType adj : adjs) {
            bool closed = isClosed(adj);
            //std::cout << "ADJACENT: " << adj.getPosition().x << ", " << adj.getPosition().y << " -> " << closed << std::endl;
            if (!closed) {
                float g = cf.g + mesh.cost(cf.node, adj);
                float h = mesh.estimate(adj, destination);
                
                this->addOrUpdateOpenList(adj, cf.node, g, h);
            }
        }
        
        /*std::cout << "N closed " << closedList.size() << std::endl;
        std::cout << "N open " << openList.size() << std::endl;*/
        
    }
    
    /*std::cout << "Open: " << openList.size() << std::endl;
    std::cout << "closed: " << closedList.size() << std::endl;*/
    
    //std::cout << "Current C1: " << c1 << std::endl;
    
    //std::cout << "About to reconstruct path..." << std::endl;
    
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
                    //std::cout << "Added to path " << closedList[i].node.getPosition().x << ", " << closedList[i].node.getPosition().y << std::endl;
                    break;
                }
            }
        }
    }
    else {
        //std::cout << "Exception..." << std::endl;
        throw std::exception();
    }
    
    //std::cout << "Finishing" << std::endl;
    
    return path;
}

template <class NodeType>
int AStarAlgorithm<NodeType>::smallerNodeInOpenList() {
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
    
    /*DiscoveredNode<NodeType> res(*openList.begin());
    openList.erase(openList.begin());*/
    return res;
}

template <class NodeType>
void AStarAlgorithm<NodeType>::addOrUpdateOpenList(const NodeType& node, const NodeType& previous, float g, float h) {
    //bool already = false;
    //std::cout << "About to add/update " << openList.size() << std::endl;
    
    /*if (openList.count(DiscoveredNode<NodeType>(node))) {
        auto d = openList.find(DiscoveredNode<NodeType>(node));
        DiscoveredNode<NodeType> dn(*d);
        
        if (g < (*d).g) {
            openList.erase(d);
            openList.insert(DiscoveredNode<NodeType>(dn.node, previous, g, dn.h));
        }
    }
    else {
        openList.insert(DiscoveredNode<NodeType>(node, previous, g, h));
    }*/
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
    
    for (DiscoveredNode<NodeType>& f : closedList) {
        if (f.node == node) {
            return true;
        }
    }
    return false;
}