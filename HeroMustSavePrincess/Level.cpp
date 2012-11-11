//
//  Level.cpp
//  HeroMustSavePrincess
//
//  Created by Daniel Breves on 7/11/12.
//  Copyright (c) 2012 Daniel Breves. All rights reserved.
//

#include "Level.h"
#include "ResourcePath.hpp"

Level::Level()
{
    
}

Level::~Level()
{
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
    this->w = w;
	this->h = h;
    
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

void Level::AddTile(int layer, int x, int y, Tile* tile)
{
	map[layer][x][y] = tile;
}

Tile* Level::GetTile(unsigned int layer, unsigned int x, unsigned int y)
{
    if (layer >= map.capacity()) return 0;
    else if (x >= map[layer].capacity()) return 0;
    else if (y >= map[layer][x].capacity()) return 0;
    else return map[layer][x][y];
}

void Level::LoadMap(std::string filename, ImageManager& imageManager) {
    Tmx::Map *map = new Tmx::Map();
	map->ParseFile(filename);
    
    if (map->HasError()) {
		printf("error code: %d\n", map->GetErrorCode());
		printf("error text: %s\n", map->GetErrorText().c_str());
        
		exit(map->GetErrorCode());
	}
            
    LoadTilesets(map, imageManager);
}

void Level::LoadTilesets(Tmx::Map* map, ImageManager& imageManager) {
    sf::Image img;
    tileSize = map->GetTileWidth();
    
    // Iterate through the tilesets.
	for (int i = 0; i < map->GetNumTilesets(); ++i) {
		// Get a tileset.
		const Tmx::Tileset *tileset = map->GetTileset(i);
        
        //Get the image file we're parsing and load it
		img.loadFromFile(resourcePath() + tileset->GetImage()->GetSource());
        
        int rows = tileset->GetImage()->GetWidth() / tileSize;
        int cols = tileset->GetImage()->GetHeight() / tileSize;
        
        for (int y = 0, i = 1; y < cols; ++y) {
            for (int x = 0; x < rows; ++i, ++x) {
                //Copy the right tile image from tileset
                sf::Texture tileImage;
                tileImage.create(tileSize, tileSize);
                tileImage.loadFromImage(img, sf::IntRect(x * tileSize, y * tileSize, tileSize, tileSize));
                
                //Add the image to our image list
                imageManager.AddImage(tileImage, i);
            }
        }
	}
    
    int layers = map->GetNumLayers();    
    SetDimensions(layers, map->GetWidth(), map->GetHeight());
        
    for (int i = 0; i < layers; ++i) {
        const Tmx::Layer *layer = map->GetLayer(i);
        
        bool walkable = layer->GetProperties().GetNumericProperty("walkable");
        
        for (int y = 0; y < layer->GetHeight(); ++y) {
            for (int x = 0; x < layer->GetWidth(); ++x) {
                //Get all the attributes
                int id = layer->GetTileId(x, y);
                
                if (id) {
                    if (!walkable) {
                        printf("x: %d, y: %d, is not walkable\n", x, y);
                    }
                    
                    Tile* newTile = new Tile(imageManager.GetImage(id), walkable);
                    AddTile(i, x, y, newTile);
                }
            }
        }
    }
}