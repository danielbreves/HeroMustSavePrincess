//
//  ImageManager.h
//  HeroMustSavePrincess
//
//  Created by Daniel Breves on 7/11/12.
//  Copyright (c) 2012 Daniel Breves. All rights reserved.
//

#ifndef __HeroMustSavePrincess__ImageManager__
#define __HeroMustSavePrincess__ImageManager__

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
using namespace std;

class ImageManager
{
private:
	vector<sf::Texture> imageList;
    map<int, int> imageIDs;
    
    int tileSize;
    
public:
	ImageManager();
	~ImageManager();
    
	void setTileSize(int tileSize) { this->tileSize = tileSize; }
    
	void AddImage(sf::Texture& image, int id);
	sf::Texture& GetImage(int id);
    
	//Loads tileset from xml format
	void LoadTileset(std::string filename);
};

#endif /* defined(__HeroMustSavePrincess__ImageManager__) */
