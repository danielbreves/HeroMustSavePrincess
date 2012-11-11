//
//  Tile.cpp
//  HeroMustSavePrincess
//
//  Created by Daniel Breves on 7/11/12.
//  Copyright (c) 2012 Daniel Breves. All rights reserved.
//

#include "Tile.h"

Tile::Tile(sf::Texture& image, bool walkable) {
	baseSprite.setTexture(image, true);
    this->walkable = walkable;
}

Tile::~Tile() {
    
}

sf::IntRect Tile::GetRect() {
    return (sf::IntRect)baseSprite.getGlobalBounds();
}

void Tile::Draw(int x, int y, sf::RenderWindow* rw) {
	baseSprite.setPosition(x, y);
	rw->draw(baseSprite);
}