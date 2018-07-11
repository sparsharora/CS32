//
//  main.cpp
//  P1
//
//  Created by Sparsh Arora on 1/12/16.
//  Copyright © 2016 Sparsh Arora. All rights reserved.
//
// robots.cpp


#include "robot.h"
#include "arena.h"
#include "globals.h"
#include "player.h"
#include "game.h"
#include <iostream>
#include <string>



int main()
{
    // Create a game
    // Use this instead to create a mini-game:   Game g(3, 4, 2);
    Game g(7, 8, 25);
    
    // Play the game
    g.play();
}
 
