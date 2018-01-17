/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GameScene.cpp
 * Author: rafa
 * 
 * Created on January 2, 2018, 1:19 AM
 */

#include "GameScene.hpp"
#include "Enemy.hpp"
#include "ESE/Core/Textures.hpp"
#include "ESE/Core/SoundBuffers.hpp"
#include "ESE/Core/ResourceLoader.hpp"
#include <ESE/Core/Textures.hpp>
#include <cmath>
#include <ESE/TileEngine/TiledLoader/TiledLoader.hpp>

GameScene::GameScene(sf::RenderWindow& window) : pathfinding(*this), player(*this->window, *this), ESE::Scene("GameScene", window), sp(*this) {
    /// CARGA DE RECURSOS ///
    std::cout << "previo" << std::endl;
    ESE::ResourceLoader::load("resources.res");
    std::cout << "post" << std::endl;
    
    ESE::Textures::instance().loadFromFile("shoot_fire", "images/shoot.png");
    
    ESE::Textures::instance().loadFromFile("survivor_idle_feet", "images/feet/idle/survivor-idle_0.png");
    for (int i = 0; i <= 19; i++) {
        ESE::Textures::instance().loadFromFile("survivor_rifle_idle_" + std::to_string(i) ,"images/rifle/idle/survivor-idle_rifle_" + std::to_string(i) + ".png");
        ESE::Textures::instance().loadFromFile("survivor_rifle_move_" + std::to_string(i) ,"images/rifle/move/survivor-move_rifle_" + std::to_string(i) + ".png");
        
        ESE::Textures::instance().loadFromFile("survivor_walk_" + std::to_string(i) ,"images/feet/run/survivor-run_" + std::to_string(i) + ".png");
    }
    
    for (int i = 0; i <= 2; i++) {
        ESE::Textures::instance().loadFromFile("survivor_shoot_rifle_" + std::to_string(i), "images/rifle/shoot/survivor-shoot_rifle_" + std::to_string(i) + ".png");
    }
    
    for (int i = 0; i <= 16; i++) {
        ESE::Textures::instance().loadFromFile("zombie_" + std::to_string(i), "images/zombie_walking/skeleton-move_" + std::to_string(i) + ".png");
    }
    
    ESE::SoundBuffers::instance().loadFromFile("shot", "sounds/ren.ogg");
    
    
    this->loadFromFile("maps/default.tmx");

    /// La capa del mapa que contiene los edificios es
    /// importante tanto por las colisiones como para el
    /// algoritmo de búsqueda. Por eso se guarda.
    buildingsLayer = &tilemap.getLayerByName(L"Building");
    
}

GameScene::~GameScene() {
    for (Enemy* e : enemies) {
        delete e;
    }
}

void GameScene::setup() {
    
    player.setup();
    
    pathfindingClock.restart();
    
}

void GameScene::manageEvents(float deltaTime) {
   
    player.manageEvents(deltaTime);
    
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle)) {
        sf::Vector2f pos = window->mapPixelToCoords(sf::Vector2i(sf::Mouse::getPosition(*this->window).x, sf::Mouse::getPosition(*this->window).y));
        
        buildingsLayer->addTile(14, sf::Vector2u(pos.x / tileSize.x, pos.y / tileSize.y)).second->setType(14);

    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)) {
        /*int cx = sf::Mouse::getPosition(*this->window).x / (tiles[0].getSize().x);
        int cy = sf::Mouse::getPosition(*this->window).y / (tiles[0].getSize().y);

        map[cy][cx] = 1;*/
    }
    
    while (this->window->pollEvent(this->events)) {
        this->checkIfWindowClosed();
    }
}

void GameScene::logic(float deltaTime) {
    player.advanceTime(deltaTime);
    /// La clase Player se encarga de centrar la cámara
    /// en el jugador. Si el jugador está en los límites del mapa la
    /// cámara podría quedar fuera de este, así que es necesario
    /// arreglar las coordenadas de esta.
    fixCamera();
    
    /// La gestión de los enemigos se delega a estos.
    /// Si se detecta que uno ha muerto se elimina del vector.
    for (auto it = enemies.begin(); it != enemies.end();) {

        (*it)->advanceTime(deltaTime);
        
        if (!(*it)->isAlive()) {
            delete *it;
            enemies.erase(it);
        }
        else {
            ++it;
        }
    }
    
    /// El algoritmo de búsqueda se ejecuta periódicamente
    /// para asegurar que los zombies si dirijan a una posición
    /// actualizada del enemigo.
    if (pathfindingClock.getElapsedTime().asSeconds() > 1) {
        for (auto &enemy : enemies) {
            try {
                std::vector<GridNode> path = 
                pathfinding.getPath(GridNode(enemy->getPosition().x / 32, enemy->getPosition().y / 32),
                    GridNode(player.getPosition().x / 32, player.getPosition().y / 32));

                enemy->setPath(path, sf::Vector2f(32, 32));

            } catch (std::exception e) {
                //El objetivo es inalcanzable.
                enemy->setPath(std::vector<GridNode>(), sf::Vector2f(32, 32));
            }
        }
        
        pathfindingClock.restart();
    }
    
    /// Puntos de aparición de los enemigos
    for (auto& spawn : this->spawnPoints) {
        spawn.advanceTime(deltaTime);
    }
    
    particleManager.advanceTime(deltaTime);
    
    
   
}

void GameScene::render() {
    sf::View view(origin, sf::Vector2f(window->getSize()));
    window->setView(view);
    
    tilemap.updateView(view);
    
    draw(tilemap);
    
    for (auto &enemy : enemies) {
        draw(*enemy);
    }
    
    draw(player);
    
    draw(particleManager);
}

std::vector<Enemy*>& GameScene::getEnemies() {
    return enemies;
}

Player& GameScene::getPlayer() {
    return player;
}

void GameScene::fixCamera() {
    if (origin.x - window->getSize().x / 2 < 0) {
        origin.x = window->getSize().x / 2;
    }
    else if (origin.x + window->getSize().x / 2 > tilemap.getSize().x * 32) {
        origin.x = tilemap.getSize().x * 32 - window->getSize().x / 2;
    }
    
    if (origin.y - window->getSize().y / 2 < 0) {
        origin.y = window->getSize().y / 2;
    }
    else if (origin.y + window->getSize().y / 2 > tilemap.getSize().y * 32) {
        origin.y = tilemap.getSize().y * 32 - window->getSize().y / 2;
    }
}

sf::IntRect GameScene::getWorldDimensions() const {
    return worldDimensions;
}

sf::IntRect GameScene::getVisibleArea() const {
    return sf::IntRect(sf::Vector2i(origin.x - window->getSize().x / 2, origin.y - window->getSize().y / 2),
                    sf::Vector2i (window->getSize()));
}

bool GameScene::isValidPosition(const sf::Vector2f& position) const {
    if (!worldDimensions.contains(position.x, position.y)) {
        return false;
    }
    
    if (buildingsLayer->getTile(position.x / tileSize.x, position.y / tileSize.y).getType() > 0) {
        return false;
    }
    
    return true;
}

sf::Vector2f& GameScene::getOrigin() {
    return origin;
}

ParticleManager& GameScene::getParticleManager() {
    return particleManager;
}

/// MESH ///

std::vector<GridNode> GameScene::getAdjacents(const GridNode& node) const {
    std::vector<GridNode> res;
    int x = node.getPosition().x;
    int y = node.getPosition().y;

    for (int rx = x - 1; rx <= x + 1; rx++) {
        for (int ry = y - 1; ry <= y + 1; ry++) {

            if (rx < 0 || ry < 0 || rx >= tilemap.getSize().x || ry >= tilemap.getSize().y) continue;
            // Una casilla no es adyacente a si misma:
            if (rx == x && ry == y) continue;
            // Si es sólido no es adyacente:
            if (buildingsLayer->getTile(rx,ry).getType() > 0) continue;
            
            // Un elemento en las casillas diagonales no será
            // adyacente si en las laterales hay algún obstáculo.
            if ((rx == x - 1 && ry == y - 1)) {
                if (buildingsLayer->getTile(rx, ry + 1).getType() > 0) continue;
                if (buildingsLayer->getTile(rx + 1, ry).getType() > 0) continue;
            }

            if ((rx == x + 1 && ry == y - 1)) {
                if (buildingsLayer->getTile(x, y - 1).getType() > 0) continue;
                if (buildingsLayer->getTile(x + 1, y).getType() > 0) continue;
            }

            if ((rx == x + 1 && ry == y + 1)) {
                if (buildingsLayer->getTile(x, y + 1).getType() > 0) continue;
                if (buildingsLayer->getTile(x + 1, y).getType() > 0) continue;
            }

            if ((rx == x - 1 && ry == y + 1)) {
                if (buildingsLayer->getTile(x, y + 1).getType() > 0) continue;
                if (buildingsLayer->getTile(x - 1, y).getType() > 0) continue;
            }
            
            res.push_back(GridNode(rx, ry));
        }
    }

    return res;
}

float GameScene::cost(const GridNode& node1, const GridNode& node2) const {
    return (node1.getPosition().x == node2.getPosition().x || node1.getPosition().y == node2.getPosition().y) ? 10 : 14.1421356237;
}

float GameScene::estimate(const GridNode &node1, const GridNode& node2) const {
    return std::sqrt((node1.getPosition().x - node2.getPosition().x) * 10 * (node1.getPosition().x - node2.getPosition().x) * 10 +
            (node1.getPosition().y - node2.getPosition().y) * 10 * (node1.getPosition().y - node2.getPosition().y) * 10);
}

/// TILEMAP LOADER ///

void GameScene::sizeLoaded(sf::Vector2u mapSize, const sf::Vector2u& tileSize) {
    tilemap.setSize(mapSize);
    this->tileSize = tileSize;
    
    // El tileset debe estar cargado antes de añadir ningún tile.
    tilesetTexture.loadFromFile("maps/template8x6.png");
    tileset.create(tilesetTexture, tileSize);
    
    tilemap.setTileset(tileset);
    
    
    worldDimensions.top = 0;
    worldDimensions.left = 0;
    worldDimensions.width = mapSize.x * tileSize.x;
    worldDimensions.height = mapSize.y * tileSize.y;
}
  
void GameScene::layerLoaded(ESE::Tiled::Layer layer) {
    
    currentLayer = ESE::TilemapLayer<Tile>(tileset);
    currentLayer.setName(layer.getName());
    currentLayer.setSize(tilemap.getSize());
    
    for (int y = 0; y < layer.getHeight(); y++) {
        for (int x = 0; x < layer.getWidth(); x++) {
            ESE::Tiled::Tile t = layer.at(x, y);
            if (t.getGID() > 0) {
                std::pair<int, Tile*> p = currentLayer.addTile(t.getGID(), sf::Vector2u(x, y));
                p.second->setType(t.getGID());
            }
        }
    }
    
    tilemap.addLayer(currentLayer);
}

void GameScene::objectLayerLoaded(ESE::Tiled::ObjectLayer objectGroup) {
    if (objectGroup.getName() == L"Spawns") {
        for (int i = 0; i < objectGroup.size(); i++) {
            
            Spawn s(*this);
            s.setPosition(sf::Vector2f(objectGroup[i].getX(), objectGroup[i].getY()));
            
            spawnPoints.push_back(s);
            
        }
    }
}