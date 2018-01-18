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

#include <Zelta/Core/Scene.hpp>
#include <Zelta/AI/Pathfinding.hpp>

#include <Zelta/TileEngine/TilemapRenderer.hpp>
#include <Zelta/TileEngine/TiledLoader/TiledLoader.hpp>

#include <Zelta/Concurrency/TaskPool.hpp>
#include <Zelta/Concurrency/Task.hpp>

#include "Player.hpp"
#include "Spawn.hpp"
#include "Enemy.hpp"

#include "GridMesh.hpp"
#include "GridNode.hpp"
#include "Spawn.hpp"

class Tile : public zt::TileSprite {
protected:
    int type;
public:
    Tile() { type = 0; };
    void setType(int type) { this->type = type; }
    int getType() { return type; }
    
};

class GameScene : public zt::Scene, public zt::IMesh<GridNode>, public zt::Tiled::TiledLoader, public zt::Task {
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
    void layerLoaded(zt::Tiled::Layer);
    void objectLayerLoaded(zt::Tiled::ObjectLayer objectGroup);
    
private:
    // Punto central de la cámara. La clase Player se encarga de
    // mantenerla centrada en el jugador.
    sf::Vector2f origin;
    
    Player player;
    
    // Enemigos
    std::vector<Enemy*> enemies;
    Spawn sp;
    std::vector<Spawn> spawnPoints;
    
    zt::Pathfinding<GridNode> pathfinding;
    sf::Clock pathfindingClock;
    zt::TaskPool taskPool;
    
    ParticleManager particleManager;
    
    zt::TilemapRenderer<Tile> tilemap;
    zt::TilemapLayer<Tile>* buildingsLayer;
    sf::Texture tilesetTexture;
    zt::Tileset tileset;
    
    sf::IntRect worldDimensions;
    sf::Vector2u tileSize;
    
    /// TILEMAP LOADER ///
    zt::TilemapLayer<Tile> currentLayer;
    
};

#endif /* GAMESCENE_HPP */

