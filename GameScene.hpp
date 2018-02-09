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

#include <Zelta/TileEngine/Tileset.hpp>
#include <Zelta/TileEngine/TilemapRenderer.hpp>
#include <Zelta/TileEngine/TiledLoader/TiledLoader.hpp>

#include <Zelta/Concurrency/TaskPool.hpp>
#include <Zelta/Concurrency/Task.hpp>

#include "Player.hpp"

#include "GridMesh.hpp"
#include "GridNode.hpp"
#include "ParticleManager.hpp"
#include "Tile.hpp"

class GameScene : public zt::Scene, public zt::Tiled::TiledLoader {
public:
    GameScene(sf::RenderWindow& windwow);
    GameScene(const GameScene& orig);
    virtual ~GameScene();
    
    void setup();
    
    void manageEvents(float deltaTime);
    void logic(float deltaTime);
    void render();
    
    Player& getPlayer();
    
    zt::TilemapLayer<Tile>& getSolidLayer();
    
    sf::IntRect getWorldDimensions() const;
    const sf::Vector2u& getMapSize() const;
    sf::IntRect getVisibleArea() const;
    bool isValidPosition(const sf::Vector2f&) const;
    Tile& getTileAt(float x, float y);
    Tile& getTileAtT(unsigned int x, unsigned int y);
    
    sf::Vector2f& getOrigin();
    
    ParticleManager& getParticleManager();
    
protected:
    void fixCamera();
    
    /// EFECTRO TRUENO ///
    float thunderAlpha(float time);
    
    
    /// HELPER FLOAT ///
    // Cálculos del agua.
    bool fequal(float f1, float f2, float tolerance = 0.0001f);
    bool fbigger(float f1, float f2, float tolerance = 0.0001f);
    bool flessEq(float f1, float f2, float tolerance = 0.0001f);
    
    /// TILEMAP LOADER ///
    void sizeLoaded(sf::Vector2u mapSize, const sf::Vector2u& tileSize);
    void layerLoaded(zt::Tiled::Layer);
    void objectLayerLoaded(zt::Tiled::ObjectLayer objectGroup);
    
    /// UI ///
    //zt::ui::VBox layout;
    //zt::ui::TextField textfield;
private:
    // Punto central de la cámara. La clase Player se encarga de
    // mantenerla centrada en el jugador.
    sf::Vector2f origin;
    
    Player player;
    
    sf::Sprite background, grass;
    
    ParticleManager particleManager;
    
    zt::TilemapRenderer<Tile> tilemap;
    zt::TilemapLayer<Tile>* solidLayer;
    sf::Texture tilesetTexture;
    zt::Tileset tileset;
    
    sf::IntRect worldDimensions;
    sf::Vector2u tileSize, mapSize;
    
    sf::Clock waterPropagationClock;
    
    sf::FloatRect backgroundDimensions;
    
    /// LLUVIA ///
    sf::Clock rainGenerationClock;
    float rainMovementAngle;
    zt::Vector2f rainMovementVector;
    sf::Sound rainSound;
    
    /// EFECTRO TRUENO ///
    sf::Sprite backgroundThunder;
    int nextThunderTime;
    sf::Clock thunderClock;
    sf::Sound thunderSound, thunderSound2;
    
    /// FPS ///
    sf::Clock updateFPS;
    int fps;
    
    /// TILEMAP LOADER ///
    zt::TilemapLayer<Tile> currentLayer;
    
};

#endif /* GAMESCENE_HPP */

