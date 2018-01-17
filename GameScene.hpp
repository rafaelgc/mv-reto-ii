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
#include <ESE/AI/Pathfinding.hpp>

#include <ESE/TileEngine/TilemapRenderer.hpp>
#include <ESE/TileEngine/TiledLoader/TiledLoader.hpp>

#include "Player.hpp"
#include "Spawn.hpp"
#include "Enemy.hpp"

#include "GridMesh.hpp"
#include "GridNode.hpp"
#include "Spawn.hpp"
#include "Task.hpp"
#include "TaskPool.hpp"

class Tile : public ESE::TileSprite {
protected:
    int type;
public:
    Tile() { type = 0; };
    void setType(int type) { this->type = type; }
    int getType() { return type; }
    
};

class GameScene : public ESE::Scene, public ESE::IMesh<GridNode>, public ESE::Tiled::TiledLoader, public Task {
public:
    GameScene(sf::RenderWindow& windwow);
    GameScene(const GameScene& orig);
    virtual ~GameScene();
    
    void setup();
    
    void manageEvents(float deltaTime);
    void logic(float deltaTime);
    void render();
    
    std::vector<Enemy*>& getEnemies();
    Player& getPlayer();
    
    sf::IntRect getWorldDimensions() const;
    sf::IntRect getVisibleArea() const;
    bool isValidPosition(const sf::Vector2f&) const;
    
    sf::Vector2f& getOrigin();
    
    ParticleManager& getParticleManager();
    
protected:
    void fixCamera();
    
    /// TASK PARA EJECUTAR EL PATHFINDING EN OTRO HILO ///
    bool work();
    
    /// MESH ///
    /// Hay que implementar estos métodos para poder ejecutar el
    /// algoritmo de búsqueda.
    std::vector<GridNode> getAdjacents(const GridNode& node) const;
    float cost(const GridNode& node1, const GridNode& node2) const;
    float estimate(const GridNode &node1, const GridNode& node2) const;
    
    /// TILEMAP LOADER ///
    void sizeLoaded(sf::Vector2u mapSize, const sf::Vector2u& tileSize);
    void layerLoaded(ESE::Tiled::Layer);
    void objectLayerLoaded(ESE::Tiled::ObjectLayer objectGroup);
    
private:
    // Punto central de la cámara. La clase Player se encarga de
    // mantenerla centrada en el jugador.
    sf::Vector2f origin;
    
    Player player;
    
    // Enemigos
    std::vector<Enemy*> enemies;
    Spawn sp;
    std::vector<Spawn> spawnPoints;
    
    ESE::Pathfinding<GridNode> pathfinding;
    sf::Clock pathfindingClock;
    TaskPool taskPool;
    
    ParticleManager particleManager;
    
    ESE::TilemapRenderer<Tile> tilemap;
    ESE::TilemapLayer<Tile>* buildingsLayer;
    sf::Texture tilesetTexture;
    ESE::Tileset tileset;
    
    sf::IntRect worldDimensions;
    sf::Vector2u tileSize;
    
    /// TILEMAP LOADER ///
    ESE::TilemapLayer<Tile> currentLayer;
    
};

#endif /* GAMESCENE_HPP */

