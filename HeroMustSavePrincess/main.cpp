//
//  main.cpp
//  HeroMustSavePrincess
//
//  Created by Daniel Breves on 7/11/12.
//  Copyright (c) 2012 Daniel Breves. All rights reserved.
//

#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"
#include "Engine.h"

int main (int argc, const char * argv[])
{
	Engine* engine = new Engine();
    
	try {
		engine->Go();
	} catch (char* e) {
        printf("%s", e);
        return EXIT_FAILURE;
	}

    return EXIT_SUCCESS;
}
