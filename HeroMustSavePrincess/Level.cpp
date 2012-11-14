//
//  Level.cpp
//  HeroMustSavePrincess
//
//  Created by Daniel Breves on 7/11/12.
//  Copyright (c) 2012 Daniel Breves. All rights reserved.
//

#include "Level.h"
#include "Princess.h"
#include "Player.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "ResourcePath.hpp"

Level::Level(std::string file) {
    filename = file;
}

Level::~Level() {
    vector<vector<vector<Tile*>>>::iterator l;
    vector<vector<Tile*>>::iterator y;
    vector<Tile*>::iterator x;
    
    for (l = map.begin(); l != map.end(); l++) {
        for (y = (*l).begin(); y != (*l).end(); y++) {
            for (x = (*y).begin(); x != (*y).end(); x++) {
                delete (*x);
            }
        }
    }
    map.clear();
}

void Level::SetDimensions(int layers, int w, int h)
{
    width = w;
	height = h;
    
	//w rows
	map.resize(layers);
    
	//Each row has h columns of null Tile pointers
    for (int l = 0; l < layers; l++) {
        map[l].resize(w);
        for (int i = 0; i < w; i++) {
            map[l].at(i).resize(h, 0);
        }
    }
}

void Level::AddTile(int layer, int x, int y, Tile* tile) {
	map[layer][x][y] = tile;
}

Tile* Level::GetTile(unsigned int layer, unsigned int x, unsigned int y) {
    if (layer >= map.capacity()) return 0;
    else if (x >= map[layer].capacity()) return 0;
    else if (y >= map[layer][x].capacity()) return 0;
    else return map[layer][x][y];
}

void Level::LoadMap() {
    Tmx::Map *map = new Tmx::Map();
	map->ParseFile(filename);
    
    if (map->HasError()) {
		printf("error code: %d\n", map->GetErrorCode());
		printf("error text: %s\n", map->GetErrorText().c_str());
        
		exit(map->GetErrorCode());
	}
            
    LoadTiles(map);
    
    LoadObjects(map);
}

void Level::LoadTiles(Tmx::Map* map) {
    sf::Image img;
    tileSize = map->GetTileWidth();
    int layers = map->GetNumLayers();
    SetDimensions(layers, map->GetWidth(), map->GetHeight());
    
    // Iterate through the tilesets.
	for (int i = 0; i < map->GetNumTilesets(); ++i) {
		// Get a tileset.
		const Tmx::Tileset *tileset = map->GetTileset(i);
        
        //Get the image file we're parsing and load it
		img.loadFromFile(resourcePath() + tileset->GetImage()->GetSource());
        
        int rows = tileset->GetImage()->GetWidth() / tileSize;
        int cols = tileset->GetImage()->GetHeight() / tileSize;
        
        for (int y = 0, i = 0; y < cols; ++y) {
            for (int x = 0; x < rows; ++i, ++x) {
                //Copy the right tile image from tileset
                sf::Texture tileImage;
                tileImage.create(tileSize, tileSize);
                tileImage.loadFromImage(img, sf::IntRect(x * tileSize, y * tileSize, tileSize, tileSize));
                
                //Add the image to our tileset
                this->tileset[i] = tileImage;
            }
        }
	}
        
    for (int i = 0; i < layers; ++i) {
        const Tmx::Layer *layer = map->GetLayer(i);
                
        for (int y = 0; y < layer->GetHeight(); ++y) {
            for (int x = 0; x < layer->GetWidth(); ++x) {
                //Get all the attributes
                int id = layer->GetTileId(x, y);
                
                if (id) {
                    Tile* newTile = new Tile(this->tileset[id]);
                    AddTile(i, x, y, newTile);
                }
            }
        }
    }
}

void Level::LoadObjects(Tmx::Map* map) {
    // Iterate through all of the object groups.
    sf::Texture* badguy = new sf::Texture;
    badguy->loadFromFile(resourcePath() + "badguy.png");
    
    sf::Texture* princess = new sf::Texture;
    princess->loadFromFile(resourcePath() + "princess.png");
    
	for (int i = 0; i < map->GetNumObjectGroups(); ++i) {
		// Get an object group.
		const Tmx::ObjectGroup *objectGroup = map->GetObjectGroup(i);
        
		// Iterate through all objects in the object group.
		for (int j = 0; j < objectGroup->GetNumObjects(); ++j) {
			// Get an object.
			const Tmx::Object *object = objectGroup->GetObject(j);
            
            if (object->GetName() == "player") {
                player = sf::Vector2i(object->GetX(), object->GetY());
            }
            else if (object->GetName() == "princess") {
                sf::Vector2i position = sf::Vector2i(object->GetX(), object->GetY());
                
                spriteManager.AddSprite(new Princess(*princess, position, object->GetWidth(), object->GetHeight()));
            }
            else {
                Tmx::PropertySet properties = object->GetProperties();
                
                int speed = properties.GetNumericProperty("speed");
                Sprite::ActionType action = static_cast<Sprite::ActionType>(properties.GetNumericProperty("action"));
                
                sf::Vector2i position = sf::Vector2i(object->GetX(), object->GetY());
                spriteManager.AddSprite(new Sprite(*badguy, position, action, object->GetWidth(), object->GetHeight(), speed));
            }
		}
	}
}

const vector<Sprite*>* Level::GetSprites() {
    return spriteManager.GetSprites();
}

void Level::Update(Camera* camera, Player* player) {
    spriteManager.CheckCollisions(player, this);
    spriteManager.Update(camera, this);
}

void Level::Draw(sf::RenderWindow* rw, Camera* camera) {    
	//Camera offsets
	int camOffsetX, camOffsetY;
    
	Tile* tile;
    
	//Get the tile bounds we need to draw and Camera bounds
	sf::IntRect bounds = camera->GetTileBounds(tileSize);
    
	//Figure out how much to offset each tile
	camOffsetX = camera->GetTileOffset(tileSize).x;
	camOffsetY = camera->GetTileOffset(tileSize).y;
    
    int layers = (int)map.size();
    
	//Loop through and draw each tile
    for (int i = 0; i < layers; i++) {
        for (int y = 0, tileY = bounds.top; y < bounds.height; y++, tileY++) {
            for (int x = 0, tileX = bounds.left; x < bounds.width; x++, tileX++) {
                //Get the tile we're drawing
                tile = GetTile(i, tileX, tileY);
                
                if (tile) {
                    tile->Draw((x * tileSize) - camOffsetX, (y * tileSize) - camOffsetY, rw);
                }
            }
        }
    }
    
    spriteManager.Draw(rw, camera);
}