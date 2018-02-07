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
#include "Zelta/Core/Textures.hpp"
#include "Zelta/Core/SoundBuffers.hpp"
#include "Zelta/Core/ResourceLoader.hpp"
#include "Drop.hpp"
#include <Zelta/Core/Textures.hpp>
#include <cmath>
#include <Zelta/TileEngine/TiledLoader/TiledLoader.hpp>

GameScene::GameScene(sf::RenderWindow& window) : pathfinding(*this), player(*this->window, *this), zt::Scene("GameScene", window) {
    /// CARGA DE RECURSOS ///
    zt::Textures::instance();
    zt::SoundBuffers::instance();
    zt::ResourceLoader::load("resources.res");
   
    
    this->loadFromFile("maps/default.tmx");

    /// La capa del mapa que contiene los edificios es
    /// importante tanto por las colisiones como para el
    /// algoritmo de búsqueda. Por eso se guarda.
    solidLayer = &tilemap.getLayerByName(L"Solid");
    
    rainMovementVector.set(-200, 2000);
    rainMovementAngle = rainMovementVector.getAngle();
    
    //std::cout << solidLayer->isEmpty(0, 0) << std::endl;
}

GameScene::~GameScene() {    
    taskPool.stop();
    
    taskPool.join();
}

void GameScene::setup() {
    
    player.setup();
    
    pathfindingClock.restart();
    
    sf::Texture& bgTex = *zt::Textures::instance().getResource("background");
    backgroundDimensions = sf::FloatRect(0, 0, bgTex.getSize().x, bgTex.getSize().y);
    
    
    background.setTexture(bgTex);
    std::cout << "Window H: " << window->getSize().y << " Tex: " << bgTex.getSize().y << std::endl;
    //std::cout << (float)window->getSize().y / bgTex.getSize().y << std::endl;
    //background.setScale((float)window->getSize().y / bgTex.getSize().y, (float)window->getSize().y / bgTex.getSize().y);
    
    taskPool.addTask(*this);
    
    rainGenerationClock.restart();
    
    //layout.setAvailableArea(sf::FloatRect(0, 0, 200, 200));
    //layout.add(textfield);
    
}

void GameScene::manageEvents(float deltaTime) {
   
    player.manageEvents(deltaTime);
    
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle)) {
        sf::Vector2f pos = window->mapPixelToCoords(sf::Vector2i(sf::Mouse::getPosition(*this->window).x, sf::Mouse::getPosition(*this->window).y));
        
        
        solidLayer->getTile(pos.x / tileSize.x, pos.y / tileSize.y).fill(0.1);
        
    }
    
    while (this->window->pollEvent(this->events)) {
        if (events.type == sf::Event::Closed) {
            zt::SceneManager::instance().deactivateAllScenes();
            
            
        }
    }
}

void GameScene::logic(float deltaTime) {
    player.advanceTime(deltaTime);
    /// La clase Player se encarga de centrar la cámara
    /// en el jugador. Si el jugador está en los límites del mapa la
    /// cámara podría quedar fuera de este, así que es necesario
    /// arreglar las coordenadas de esta.
    //fixCamera();

    if (waterPropagationClock.getElapsedTime().asSeconds() > 0.1) {
        float avg;
        for (int y = 0; y < mapSize.y; y++) {
            for (int x = 0; x < mapSize.x; x++) {
                
                /// EXPANSIÓN VERTICAL
                // Si el fluido puede moverse hacia la casilla de
                // debajo lo hará antes que expandirse lateralmente.
                
                bool downFree = y < mapSize.y - 1 && solidLayer->getTile(x, y + 1).getType() == 0
                    && solidLayer->getTile(x, y + 1).getWater() < 1.f;
                
                if (downFree) {
                    // El agua que cabe todavía en la casilla inferior.
                    float free = 1.f - solidLayer->getTile(x, y + 1).getWater();
                    
                    // El agua que finalmente se transfiere es el mínimo
                    // del agua que todavía cabe y la que hay en la
                    // casilla superior.
                    float trans = std::fmin(free,solidLayer->getTile(x, y).getWater());
                    
                    solidLayer->getTile(x, y + 1).fill(trans);
                    solidLayer->getTile(x, y).fill(-trans);
                    //continue;
                    
                }
                
                /*if (fbigger(solidLayer->getTile(x, y).getWater(), 0.f) && y < mapSize.y - 1) {
                    
                    continue;
                }*/
            
                /// EXPANSIÓN HORIZONTAL DEL FLUIDO
                // Básicamente hay que traspasar agua a las casillas
                // adyacentes que tengan menos agua.
                // La cantidad de agua que hay que mandar depende
                // de si tenemos que traspasar agua sólo a una de ellas
                // o a las dos.
                
                // Si hay que mandar agua sólo a una de ellas hay que
                // calcular la media de agua entre esas dos y mandar
                // lo que haga falta para que la otra casilla alcance
                // esa media.
                
                // Si hay que mendar agua a las dos casillas adyacentes
                // la media habrá que calcularla sobre las tres.
                
                bool leftFree = x > 0 && solidLayer->getTile(x - 1, y).getType() == 0 &&
                    fbigger(solidLayer->getTile(x, y).getWater(), solidLayer->getTile(x - 1, y).getWater());
                
                bool rightFree = x < (mapSize.x - 1) && solidLayer->getTile(x + 1, y).getType() == 0 &&
                    fbigger(solidLayer->getTile(x, y).getWater(), solidLayer->getTile(x + 1, y).getWater());
                
                //
                if (leftFree && rightFree) {
                    avg = (solidLayer->getTile(x, y).getWater() + solidLayer->getTile(x - 1, y).getWater() + solidLayer->getTile(x + 1, y).getWater()) / 3.f;
                    
                    solidLayer->getTile(x, y).setWater(avg);
                    solidLayer->getTile(x + 1, y).setWater(avg);
                    solidLayer->getTile(x - 1, y).setWater(avg);
                }
                else if (leftFree){
                    avg = (solidLayer->getTile(x, y).getWater() + solidLayer->getTile(x - 1, y).getWater()) / 2.f;
                    
                    solidLayer->getTile(x, y).setWater(avg);
                    solidLayer->getTile(x - 1, y).setWater(avg);
                    
                }
                else if (rightFree) {
                    avg = (solidLayer->getTile(x, y).getWater() + solidLayer->getTile(x + 1, y).getWater()) / 2.f;
                    
                    solidLayer->getTile(x, y).setWater(avg);
                    solidLayer->getTile(x + 1, y).setWater(avg);
                }
                
            }
        }
        
        waterPropagationClock.restart();
    }
    
    
    if (rainGenerationClock.getElapsedTime().asMilliseconds() > 50) {
        
        /*for (int k = 0; k < 25; k++) {
            particleManager.addParticle(
                    new Drop(*this, zt::Vector2f(this->getVisibleArea().left + rand() % this->getVisibleArea().width, this->getVisibleArea().top - rand() % this->getVisibleArea().height), 
                    rainMovementVector.mult(0.2), rainMovementAngle, 100, false));
        
        }*/
        
        for (int k = 0; k < 25; k++) {
            particleManager.addParticle(
                    new Drop(*this, zt::Vector2f(this->getVisibleArea().left + rand() % this->getVisibleArea().width, this->getVisibleArea().top - rand() % this->getVisibleArea().height), 
                    rainMovementVector, rainMovementAngle, 255, true));
            /*particleManager.addParticle(
                    new Drop(*this, zt::Vector2f(this->getVisibleArea().left + this->getVisibleArea().width, this->getVisibleArea().top), 
                    rainMovementVector, rainMovementAngle));*/
        
        }
        rainGenerationClock.restart();
    }
    
    particleManager.advanceTime(deltaTime);
    
    
    fps++;
    if (updateFPS.getElapsedTime().asSeconds() > 1) {
        //std::cout << fps << std::endl;
        fps = 0;
        updateFPS.restart();
    }
}

void GameScene::render() {
    window->setView(sf::View(backgroundDimensions));
    draw(background);
    
    sf::View view(origin, sf::Vector2f(window->getSize()));
    window->setView(view);
    
    tilemap.updateView(view);
    
    
    draw(player);
    
    draw(tilemap);
    
    draw(particleManager);
    
    window->setView(sf::View());
    //draw(layout);
}

bool GameScene::work() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    
    return false;
}

Player& GameScene::getPlayer() {
    return player;
}

zt::TilemapLayer<Tile>& GameScene::getSolidLayer() {
    return *solidLayer;
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

const sf::Vector2u& GameScene::getMapSize() const {
    return mapSize;
}

sf::IntRect GameScene::getVisibleArea() const {
    return sf::IntRect(sf::Vector2i(origin.x - window->getSize().x / 2, origin.y - window->getSize().y / 2),
                    sf::Vector2i (window->getSize()));
}

bool GameScene::isValidPosition(const sf::Vector2f& position) const {
    if (!worldDimensions.contains(position.x, position.y)) {
        return false;
    }
    
    if (solidLayer->getTile(position.x / tileSize.x, position.y / tileSize.y).getType() > 0) {
        return false;
    }
    
    return true;
}

Tile& GameScene::getTileAt(float x, float y) {
    return solidLayer->getTile(x / tileSize.x, y / tileSize.y);
}

sf::Vector2f& GameScene::getOrigin() {
    return origin;
}

ParticleManager& GameScene::getParticleManager() {
    return particleManager;
}

/// HELPER FLOAT ///

bool GameScene::fequal(float f1, float f2, float tolerance) {
    return std::fabs(f1 - f2) < tolerance;
}

bool GameScene::fbigger(float f1, float f2, float tolerance) {
    // Si son iguales...
    if (fequal(f1, f2, tolerance)) {
        return false;
    }
    
    return f1 > f2;
}

bool GameScene::flessEq(float f1, float f2, float tolerance) {
    return fequal(f1, f2, tolerance) || f1 < f2;
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
            if (solidLayer->getTile(rx,ry).getType() > 0) continue;
            
            // Un elemento en las casillas diagonales no será
            // adyacente si en las laterales hay algún obstáculo.
            if ((rx == x - 1 && ry == y - 1)) {
                if (solidLayer->getTile(rx, ry + 1).getType() > 0) continue;
                if (solidLayer->getTile(rx + 1, ry).getType() > 0) continue;
            }

            if ((rx == x + 1 && ry == y - 1)) {
                if (solidLayer->getTile(x, y - 1).getType() > 0) continue;
                if (solidLayer->getTile(x + 1, y).getType() > 0) continue;
            }

            if ((rx == x + 1 && ry == y + 1)) {
                if (solidLayer->getTile(x, y + 1).getType() > 0) continue;
                if (solidLayer->getTile(x + 1, y).getType() > 0) continue;
            }

            if ((rx == x - 1 && ry == y + 1)) {
                if (solidLayer->getTile(x, y + 1).getType() > 0) continue;
                if (solidLayer->getTile(x - 1, y).getType() > 0) continue;
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
    this->mapSize = mapSize;
    
    // El tileset debe estar cargado antes de añadir ningún tile.
    //tileset.create(*zt::Textures::instance().getResource("tileset"), tileSize);
    tileset.create(*zt::Textures::instance().getResource("tileset"), tileSize);
    
    worldDimensions.top = 0;
    worldDimensions.left = 0;
    worldDimensions.width = mapSize.x * tileSize.x;
    worldDimensions.height = mapSize.y * tileSize.y;
}
  
void GameScene::layerLoaded(zt::Tiled::Layer layer) {
    
    currentLayer = zt::TilemapLayer<Tile>();
    currentLayer.setName(layer.getName());
    currentLayer.setSize(tilemap.getSize());
    currentLayer.setTileSize(this->tileSize);
    
    for (int y = 0; y < layer.getHeight(); y++) {
        for (int x = 0; x < layer.getWidth(); x++) {
            zt::Tiled::Tile t = layer.at(x, y);
            if (t.getGID() > 0) {
                std::pair<int, Tile*> p = currentLayer.addTile(Tile(sf::Vector2f(tileSize)), sf::Vector2u(x, y));
            
                p.second->setTexture(tileset.getTextureForTile(t.getGID()));
            
                p.second->setType(t.getGID());
            }
        }
    }
    
    tilemap.addLayer(currentLayer);
}

void GameScene::objectLayerLoaded(zt::Tiled::ObjectLayer objectGroup) {
    if (objectGroup.getName() == L"Spawn") {
        
        for (int i = 0; i < objectGroup.size(); i++) {
            if (objectGroup[i].getName() == L"Player") {
                player.setPosition(sf::Vector2f(objectGroup[i].getX(), objectGroup[i].getY()));
            }
        }
        
    }
}