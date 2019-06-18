//
//  Player.h
//  Project3
//
//  Created by Shreya Chatterjee on 5/13/19.
//  Copyright © 2019 Shreya Chatterjee. All rights reserved.
//

#ifndef Player_h
#define Player_h
#include "Side.h"
#include "Board.h"
#include <iostream>
class AlarmClock;

class Player {
    
public:

    /*Create a Player with the indicated name.*/
    Player(std::string name);

    /*Return the name of the player.*/
    std::string name() const;

    /*Return false if the player is a computer player. Return true if the player is human. Most kinds of players will be computer players.*/
    virtual bool isInteractive() const;

    /*Every concrete class derived from this class must implement this function so that if the player were to be playing side s and had to make a move given board b, the function returns the move the player would choose. If no move is possible, return −1.*/
    virtual int chooseMove(const Board& b, Side s) const = 0;

    /*Since this class is designed as a base class, it should have a virtual destructor.*/
    virtual ~Player();
    
private:
    std::string m_name;

};

class HumanPlayer : public Player {
public:
    HumanPlayer(std::string name);
    /*Return false if the player is a computer player. Return true if the player is human. Most kinds of players will be computer players.*/
    virtual bool isInteractive() const;
    
    /*Every concrete class derived from this class must implement this function so that if the player were to be playing side s and had to make a move given board b, the function returns the move the player would choose. If no move is possible, return −1.*/
    virtual int chooseMove(const Board& b, Side s) const;
};

class BadPlayer : public Player {
public:
    BadPlayer(std::string name);
    /*Return false if the player is a computer player. Return true if the player is human. Most kinds of players will be computer players.*/
    virtual bool isInteractive() const;
    
    /*Every concrete class derived from this class must implement this function so that if the player were to be playing side s and had to make a move given board b, the function returns the move the player would choose. If no move is possible, return −1.*/
    virtual int chooseMove(const Board& b, Side s) const;
};

class SmartPlayer : public Player {
public:
    SmartPlayer(std::string name);
    /*Return false if the player is a computer player. Return true if the player is human. Most kinds of players will be computer players.*/
    virtual bool isInteractive() const;
    
    /*Every concrete class derived from this class must implement this function so that if the player were to be playing side s and had to make a move given board b, the function returns the move the player would choose. If no move is possible, return −1.*/
    virtual int chooseMove(const Board& b, Side s) const;
private: 
    void findBestMove(const Board & copyBoard, Side s, int &bestHole, int &value, AlarmClock & alarm, int count) const;
};

#endif /* Player_h */
