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
#include <map>
#include "../TmxParser/Tmx.h"
#include "SpriteManager.h"
#include "Camera.h"
#include "Tile.h"
using namespace std;

class Sprite;
class Player;

class Level {
    SpriteManager spriteManager;
    map<int, sf::Texture> tileset;
    
	vector<vector<vector<Tile*>>> map;
    sf::Vector2i player;
    std::string filename;
	int width, height, tileSize;
    
	void SetDimensions(int layers, int w, int h);
    void LoadTilesets(Tmx::Map* map);
    void LoadTiles(Tmx::Map* map, int layers);
    void LoadObjects(Tmx::Map* map);
    
public:
    enum Status {INCOMPLETE, COMPLETE, LOST};
    
	Level(string file);
	~Level();
    
    void LoadMap();
    
    void SetStatus(Status s) {status = s;}
    Status GetStatus() {return status;}
    sf::Vector2i GetPlayerPosition() {return player;}
    const vector<Sprite*>* GetSprites();
    Tile* GetTile(unsigned int layer, unsigned int x, unsigned int y);
	const int GetWidth() const {return width;}
	const int GetHeight() const {return height;}
    const int GetTileSize() const {return tileSize;}
    
    void Update(Camera* camera, Player* player);
    void Draw(sf::RenderWindow* rw, Camera* camera);
    
protected:
    Status status = INCOMPLETE;
};

#endif /* defined(__HeroMustSavePrincess__Level__) */
