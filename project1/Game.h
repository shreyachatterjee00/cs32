//
//  Game.h
//  Project1
//
//  Created by Shreya Chatterjee on 4/3/19.
//  Copyright © 2019 Shreya Chatterjee. All rights reserved.
//

#ifndef Game_h
#define Game_h


class Arena;

class Game
{
public:
    // Constructor/destructor
    Game(int rows, int cols, int nZombies);
    ~Game();
    
    // Mutators
    void play();
    
    int decodeDirection(char dir); 
    
private:
    Arena* m_arena;
};

#endif /* Game_h */
