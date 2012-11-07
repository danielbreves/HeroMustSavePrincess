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
    
public:
	ImageManager();
	~ImageManager();
    
	void AddImage(sf::Texture& image);
	sf::Texture& GetImage(int index);
};

#endif /* defined(__HeroMustSavePrincess__ImageManager__) */
