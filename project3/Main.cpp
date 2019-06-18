//
//  main.cpp
//  Project3
//
//  Created by Shreya Chatterjee on 5/13/19.
//  Copyright © 2019 Shreya Chatterjee. All rights reserved.
//
#include "Game.h"
#include "Player.h"
#include "Board.h"
#include "Side.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    HumanPlayer hp("shreya");
    SmartPlayer bp("smart");
    
    Board b(6, 4);
    Game g(b, &bp, &hp);
    
    g.play();
}

  
