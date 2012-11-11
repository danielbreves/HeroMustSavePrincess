//
//  Tile.h
//  HeroMustSavePrincess
//
//  Created by Daniel Breves on 7/11/12.
//  Copyright (c) 2012 Daniel Breves. All rights reserved.
//

#ifndef __HeroMustSavePrincess__Tile__
#define __HeroMustSavePrincess__Tile__

#include <iostream>
#include <SFML/Graphics.hpp>

class Tile
{
private:
	sf::Sprite baseSprite;
    
public:
	Tile(sf::Texture& image);
	~Tile();
    
    sf::IntRect GetRect();
	void Draw(int x, int y, sf::RenderWindow* rw);
};

#endif /* defined(__HeroMustSavePrincess__Tile__) */
