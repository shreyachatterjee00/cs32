//
//  Player.cpp
//  Project3
//
//  Created by Shreya Chatterjee on 5/13/19.
//  Copyright © 2019 Shreya Chatterjee. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include "Player.h"
#include <string>
using namespace std;

//==========================================================================
// AlarmClock ac(numMilliseconds);  // Set an alarm clock that will time out
//                                  // after the indicated number of ms
// if (ac.timedOut())  // Will be false until the alarm clock times out; after
//                     // that, always returns true.
//==========================================================================

#include <chrono>
#include <future>
#include <atomic>

class AlarmClock
{
public:
    AlarmClock(int ms)
    {
        m_timedOut = false;
        m_isRunning = true;
        m_alarmClockFuture = std::async([=]() {
            for (int k = 0; k < ms  &&  m_isRunning; k++)
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            if (m_isRunning)
                m_timedOut = true;
        });
    }
    
    ~AlarmClock()
    {
        m_isRunning = false;
        m_alarmClockFuture.get();
    }
    
    bool timedOut() const
    {
        return m_timedOut;
    }
    
    AlarmClock(const AlarmClock&) = delete;
    AlarmClock& operator=(const AlarmClock&) = delete;
private:
    std::atomic<bool> m_isRunning;
    std::atomic<bool> m_timedOut;
    std::future<void> m_alarmClockFuture;
};
    
/*Create a Player with the indicated name.*/
Player::Player(string name) {
    m_name = name;
}
    
/*Return the name of the player.*/
string Player::name() const {
    return m_name;
}
    
/*Return false if the player is a computer player. Return true if the player is human. Most kinds of players will be computer players.*/
bool Player::isInteractive() const {
    return false;
}
    
/*Since this class is designed as a base class, it should have a virtual destructor.*/
Player::~Player() {
    
}

 /////////////////////////////////////////////////////////////////////////////////////////////////////

HumanPlayer::HumanPlayer (string name)
: Player (name)
{
    
}

/*Return false if the player is a computer player. Return true if the player is human. Most kinds of players will be computer players.*/
bool HumanPlayer::isInteractive() const {
    return true;
}
    
/*Every concrete class derived from this class must implement this function so that if the player were to be playing side s and had to make a move given board b, the function returns the move the player would choose. If no move is possible, return −1.*/
int HumanPlayer::chooseMove(const Board& b, Side s) const {
    if (b.beansInPlay(s) == 0) {
        return -1;
    }
    
    int holeInput;
    cout << "Select a hole, " << name() << ": ";
    cout << endl;
    cin >> holeInput;
    
    while (holeInput < 1 || holeInput > b.holes()) {
        cout << "The hole number must be from 1 to " << b.holes() << "." << endl;
        cout << "Select a hole, " << name() << ": ";
        cout << endl;
        cin >> holeInput;
    }
    
    while (b.beans(s, holeInput) == 0) {
        cout << "There are no beans in that hole." << endl;
        cout << "Select a hole, " << name() << ": ";
        cout << endl;
        cin >> holeInput;
    }
    
    return holeInput;
}

///////////////////////////////////////////////////////////////////////////////////////////

BadPlayer::BadPlayer (string name)
: Player (name)
{
    
}
/*Return false if the player is a computer player. Return true if the player is human. Most kinds of players will be computer players.*/
bool BadPlayer::isInteractive() const {
    return false;
}
    
/*Every concrete class derived from this class must implement this function so that if the player were to be playing side s and had to make a move given board b, the function returns the move the player would choose. If no move is possible, return −1.*/
int BadPlayer::chooseMove(const Board& b, Side s) const {
    
    if (b.beansInPlay(s) == 0) {
        return -1;
    }
    
    //find first hole in array that has beans, traversing array upwards, regardless of proximity to pot
    
    for (int i = 1; i <= b.holes(); i++) {
        if (b.beans(s, i) != 0) {
            return i;
        }
    }
    
    return -1;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
SmartPlayer::SmartPlayer (string name)
: Player (name)
{
    
}
/*Return false if the player is a computer player. Return true if the player is human. Most kinds of players will be computer players.*/
bool SmartPlayer::isInteractive() const {
    return false;
}
    
/*Every concrete class derived from this class must implement this function so that if the player were to be playing side s and had to make a move given board b, the function returns the move the player would choose. If no move is possible, return −1.*/
int SmartPlayer::chooseMove(const Board& b, Side s) const {
    Board board = b;
    
    
    if (b.beansInPlay(s) == 0) {
        return -1;
    }
    
    int bestHole;
    int value;
    int count = 5; //depth
    
    AlarmClock a(4800);
    findBestMove(b, s, bestHole, value, a, count);
    
   if (bestHole >= 1 && bestHole <= board.holes() && board.beans(s, bestHole) > 0) {
        return bestHole;
    }
    
    else {
        for (int i = 1; i <= board.holes(); i++) {
            if (board.beans(s, i) != 0) {
                return i;
            }
        }
        
        return -1;
    }
}


void SmartPlayer::findBestMove(const Board & board, Side s, int &bestHole, int &value, AlarmClock & alarm, int count) const {
    
    Side opp;
    if (s == NORTH) {
        opp = SOUTH;
    }
    else {
        opp = NORTH;
    }
    //if no move for player exists (i.e., game is over)
    //bestHole = -1
    //value = value of this position
    //return
    if (board.beansInPlay(NORTH) == 0 || board.beansInPlay(SOUTH) == 0) {
        bestHole = -1;
        int northBeans = board.beansInPlay(NORTH) + board.beans(NORTH, 0);
        int southBeans = board.beansInPlay(SOUTH) + board.beans(SOUTH, 0);
        
        
        /*for (int i = 1; i <= board.holes(); i++) {
            //move beans to pot, both sides, but only one should have beans in the holes
            board.moveToPot(NORTH, i, NORTH);
            board.moveToPot(SOUTH, i, SOUTH);
        }*/
        
        //if north is winner, change values
        if (northBeans > southBeans) {
            value = -100000;
        }
        
        //if south is winner, change values
        else if (southBeans > northBeans) {
            value = 100000;
        }
        
        else if (southBeans == northBeans) {
            value = 0;
        }
        return;
    }
    
    //if the criterion says we should not search below this node
    //bestHole = -1
    //value = value of this position
    //return
    if (alarm.timedOut() || count == 0) {
        bestHole = -1;
        //evaluation function: the number of beans in our pot - number of beans in the other pot
        value = board.beans(SOUTH, 0) - board.beans(NORTH, 0);
        return;
    }
    
    //for every hole h the player can choose
    //"make" the move h
    //chooseMove(opponent, h2, v2)
    //"unmake" the move
    
    Side eS;
    int eH;
    int h2 = 0, v2 = 0;
    
    bool first = true;
    
    for (int h = 1; h <= board.holes(); h++) {
        
        if (first == true) {
            v2 = value;
            bestHole = h;
            first = false;
        }
        
        Board copyBoard = board;
        //if the hole has beans
        if (board.beans(s, h) > 0) {
            //Board copyBoard = board;
            
            //sow 
            copyBoard.sow(s, h, eS, eH);
            
            //if move ends in your pot, go again
            if (eS == s && eH == 0) {
                count --;
                findBestMove(copyBoard, s, h2, v2, alarm, count);
            }
            
            //capture
            if (eS == s && copyBoard.beans(s, eH) == 1 && copyBoard.beans(opp, eH) > 0) {
                copyBoard.moveToPot(s, eH, s);
                copyBoard.moveToPot(opp, eH, s);
            }
            
            count --;
            findBestMove(copyBoard, opp, h2, v2, alarm, count); //check next moves
            
            //if v2 is better for the player than best seen so far,
            //bestHole = h
            //value = v2
            //return
            
            if (s == SOUTH) {
                if (v2 > value) {
                    value = v2;
                    bestHole = h;
                }
            }
            
            if (s == NORTH) {
                if (v2 < value) {
                    value = v2;
                    bestHole = h;
                }
            }
        }
    }
    
    return;
}
