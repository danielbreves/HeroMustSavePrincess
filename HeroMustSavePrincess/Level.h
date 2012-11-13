//
//  Level.h
//  HeroMustSavePrincess
//
//  Created by Daniel Breves on 7/11/12.
//  Copyright (c) 2012 Daniel Breves. All rights reserved.
//

#ifndef __HeroMustSavePrincess__Level__
#define __HeroMustSavePrincess__Level__

#include <iostream>
#include <vector>
#include "../TmxParser/Tmx.h"
#include "SpriteManager.h"
#include "ImageManager.h"
//#include "Sprite.h"
#include "Camera.h"
#include "Tile.h"
using namespace std;

class Sprite;

class Level {
    SpriteManager spriteManager;
    ImageManager imageManager;
    
	//A 2D array of Tile pointers
	vector<vector<vector<Tile*>>> map;
    
    sf::Vector2i player;
    
    std::string filename;
    
	//Width and height of level (in tiles)
	int width, height, tileSize;
    
	void SetDimensions(int layers, int w, int h);
    
public:
    enum Status {INCOMPLETE, COMPLETE, LOST};
    
	Level(string file);
	~Level();
    
	void AddTile(int layer, int x, int y, Tile* tile);
	Tile* GetTile(unsigned int layer, unsigned int x, unsigned int y);
    
    void LoadMap();
    void LoadTilesets(Tmx::Map* map);
    void LoadObjects(Tmx::Map* map);
    
    void SetStatus(Status s) {status = s;}
    Status GetStatus() {return status;}
    sf::Vector2i GetPlayerPosition() {return player;}
    const vector<Sprite*>* GetSprites();
	const int GetWidth() const {return width;}
	const int GetHeight() const {return height;}
    const int GetTileSize() const {return tileSize;}
    
    void Update(Camera* camera);
    void Draw(sf::RenderWindow* rw, Camera* camera);
    
protected:
    Status status = INCOMPLETE;

};

#endif /* defined(__HeroMustSavePrincess__Level__) */
