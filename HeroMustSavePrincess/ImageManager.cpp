//
//  ImageManager.cpp
//  HeroMustSavePrincess
//
//  Created by Daniel Breves on 7/11/12.
//  Copyright (c) 2012 Daniel Breves. All rights reserved.
//

#include <vector>
#include <string>
#include <fstream>
#include "ResourcePath.hpp"
#include "ImageManager.h"

ImageManager::ImageManager()
{
    
}

ImageManager::~ImageManager()
{
    
}

void ImageManager::AddImage(sf::Texture& image, int id)
{
	imageList.push_back(image);
}

sf::Texture& ImageManager::GetImage(int id)
{
	return imageList[id];
}