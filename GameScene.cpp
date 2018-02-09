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

GameScene::GameScene(sf::RenderWindow& window) : player(*this->window, *this), zt::Scene("GameScene", window) {
    /// CARGA DE RECURSOS ///
    zt::Textures::instance();
    zt::SoundBuffers::instance();
    zt::ResourceLoader::load("resources.res");
   
    this->loadFromFile("maps/default.tmx");

    /// La capa del mapa que contiene los tiles sólidos es
    /// importante tenerla a mano.
    solidLayer = &tilemap.getLayerByName(L"Solid");
    
    rainMovementVector.set(-200, 2000);
    rainMovementAngle = rainMovementVector.getAngle();
}

GameScene::~GameScene() {
}

void GameScene::setup() {
    
    player.setup();
    
    sf::Texture& bgTex = *zt::Textures::instance().getResource("background");
    backgroundDimensions = sf::FloatRect(0, 0, bgTex.getSize().x, bgTex.getSize().y);
    
    background.setTexture(bgTex);
    backgroundThunder.setTexture(*zt::Textures::instance().getResource("background_thunder"));
    
    grass.setTexture(*zt::Textures::instance().getResource("grass"));
    grass.setPosition(0, window->getSize().y - zt::Textures::instance().getResource("grass")->getSize().y);
    std::cout << window->getSize().y << " - " << zt::Textures::instance().getResource("grass")->getSize().y << std::endl;
    
    rainGenerationClock.restart();
    
    rainSound.setBuffer(*zt::SoundBuffers::instance().getResource("rain"));
    rainSound.setLoop(true);
    rainSound.play();
    
    thunderSound.setBuffer(*zt::SoundBuffers::instance().getResource("thunder"));
    thunderSound2.setBuffer(*zt::SoundBuffers::instance().getResource("thunder2"));
    
    nextThunderTime = 5 + rand() % 10;
    
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
    fixCamera();
    
    
    grass.setPosition(-(origin.x - window->getSize().x / 2) * ((float) (zt::Textures::instance().getResource("grass")->getSize().x - window->getSize().x) / (this->worldDimensions.width - window->getSize().x)),
                grass.getPosition().y);
    
    
    backgroundThunder.setColor(sf::Color(255, 255, 255, 255 * this->thunderAlpha(14 * thunderClock.getElapsedTime().asSeconds())));

    if (thunderClock.getElapsedTime().asSeconds() > nextThunderTime) {
        thunderClock.restart();
        
        if (rand() % 2 == 0) {
            thunderSound.play();
        }
        else {
            thunderSound2.play();
        }
        
        nextThunderTime = 5 + rand() % 10;
    }
    
    /*
     * He deshabilitado la simulación de fluidos.
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
                
                //if (fbigger(solidLayer->getTile(x, y).getWater(), 0.f) && y < mapSize.y - 1) continue;
            
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
    */
    
    /// GENERACION DE GOTAS ///
    if (rainGenerationClock.getElapsedTime().asMilliseconds() > 25) {
        for (int k = 0; k < 50; k++) {
            particleManager.addParticle(
                    new Drop(*this, zt::Vector2f(this->getVisibleArea().left + rand() % this->getVisibleArea().width, this->getVisibleArea().top - rand() % this->getVisibleArea().height), 
                    rainMovementVector, rainMovementAngle, 255, true));
        
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
    draw(backgroundThunder);
    
    sf::View view(origin, sf::Vector2f(window->getSize()));
    window->setView(view);
    
    tilemap.updateView(view);
    
    
    draw(player);
    
    draw(tilemap);
    
    draw(particleManager);
    
    window->setView(sf::View(sf::FloatRect(0, 0, window->getSize().x, window->getSize().y)));
    
    draw(grass);
    
    //draw(layout);
}

float GameScene::thunderAlpha(float time) {
    if (time < 3.1415f) {
        // Destello fuerte.
        return std::sin(time);
    }
    else if (time < 2.f * 3.1415f) {
        // Destello medio.
        return std::abs(std::sin(time) * 0.5f);
    }
    else if (time < 3.f * 3.1415f) {
        // Destello fuerte.
        return std::abs(std::sin(time));
    }
    else if (time < 4.f * 3.1415f) {
        // Destello flojo.
        return std::abs(std::sin(time) * 0.4f);
    }
    else {
        return 0.f;
    }
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
    else if (origin.x + window->getSize().x / 2 > tilemap.getSize().x * tileSize.x) {
        origin.x = tilemap.getSize().x * tileSize.x - window->getSize().x / 2;
    }
    
    if (origin.y - window->getSize().y / 2 < 0) {
        origin.y = window->getSize().y / 2;
    }
    else if (origin.y + window->getSize().y / 2 > tilemap.getSize().y * tileSize.y) {
        origin.y = tilemap.getSize().y * tileSize.y - window->getSize().y / 2;
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