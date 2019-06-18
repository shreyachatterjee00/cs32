//
//  Game.cpp
//  Project3
//
//  Created by Shreya Chatterjee on 5/13/19.
//  Copyright © 2019 Shreya Chatterjee. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include "Game.h"
#include "Player.h"
using namespace std;

/*Construct a Game to be played with the indicated players on a copy of the board b. The player on the south side always moves first.*/
Game::Game(const Board& b, Player* south, Player* north)
    : m_board(b)
{
    southPlayer = south;
    northPlayer = north;
}


    
/*Display the game's board in a manner of your choosing, provided you show the names of the players and a reasonable representation of the state of the board.*/
void Game::display() const {
    //north players name
    cout << "  " << northPlayer->name() << endl;
    
    //north beans
    cout << "  ";
    for (int i = 1; i <= m_board.holes(); i++) {
        cout << m_board.beans(NORTH, i) << "  ";
    }
    cout << endl;
    
    //north pot
    cout << m_board.beans(NORTH, 0);
    
    //spacing between north and south pot
    for (int i = 1; i <= m_board.holes(); i++) {
        cout << "   ";
    }
    cout << " ";
    
    //south pot
    cout << m_board.beans(SOUTH, 0);
    cout << endl;
    
    //south beans
    cout << "  ";
    for (int i = 1; i <= m_board.holes(); i++) {
        cout << m_board.beans(SOUTH, i) << "  ";
    }
    cout << endl;
    
    //south players name
    cout << "   " << southPlayer->name() << endl;
    
}
    
/*If the game isn't over (i.e., more moves are possible), set over to false and do not change anything else. Otherwise, set over to true and hasWinner to true if the game has a winner, or false if it resulted in a tie. If hasWinner is set to false, leave winner unchanged; otherwise, set it to the winning side.*/
void Game::status(bool& over, bool& hasWinner, Side& winner) const {
    
    if (m_board.beansInPlay(NORTH) == 0 || m_board.beansInPlay(SOUTH) == 0) {
        over = true;
        
        int northPot = m_board.beans(NORTH, 0);
        int southPot = m_board.beans(SOUTH, 0);
        if (northPot > southPot) {
            hasWinner = true;
            winner = NORTH;
        }
        
        else if (southPot > northPot) {
            hasWinner = true;
            winner = SOUTH;
        }
        
        else if (southPot == northPot) {
            hasWinner = false;
        }
    }
    
    else {
        over = false;
    }
            
}
    
/*If the game is over, return false. Otherwise, make a complete move for the player whose turn it is (so that it becomes the other player's turn) and return true. "Complete" means that the player sows the seeds from a hole and takes any additional turns required or completes a capture. If the player gets an additional turn, you should display the board so someone looking at the screen can follow what's happening.*/
bool Game::move() {
    bool over, hasWinner;
    Side winner;
    bool cont = true;
    
    while (cont) {
        status(over, hasWinner, winner);
        
        Player * whoseTurn;
        Side endSide;
        int currentHole, endHole;
        
        if (turn == SOUTH) {
            whoseTurn = southPlayer;
        }
        
        else {
            whoseTurn = northPlayer;
        }
        
        //get hole the player wants to choose
        currentHole = whoseTurn->chooseMove(m_board, turn);
        if (whoseTurn->isInteractive() == false) {
            cout << whoseTurn->name() << " chooses hole " << currentHole << endl;
            cout << endl;
            cont = false;
        }
        
        if (currentHole == -1) {
            return false;
        }
        
        //sow from that hole
        m_board.sow(turn, currentHole, endSide, endHole);
        
        //extraneous circumstances
        
        //end in your pot: take another turn
        if (endHole == 0) {
            display();
            status(over, hasWinner, winner);
            if (over == false) {
                cout << whoseTurn->name() << " gets another turn." << endl;
                cout << endl;
                cont = true;
            }
            else {
                cont = false;
            }
        }
        
        //capture
        //find opposite hole
        Side oppositeSide;
        if (endSide == NORTH) {
            oppositeSide = SOUTH;
        }
        else {
            oppositeSide = NORTH;
        }
        
        if (endSide == turn && m_board.beans(endSide, endHole) == 1 && m_board.beans(oppositeSide, endHole) > 0) {
            m_board.moveToPot(endSide, endHole, endSide);
            m_board.moveToPot(oppositeSide, endHole, endSide);
            cont = false;
        }
        
        display();
        if (endHole != 0) {
        if (turn == SOUTH) {
            turn = NORTH;
        }
        else {
            turn = SOUTH;
        }
        }
        
        
        status(over, hasWinner, winner);
        if (over == true) {
            //sweep remaining beans on other side
                if (m_board.beansInPlay(SOUTH) != 0) {
                    for (int i = 0; i <= m_board.holes(); i++) {
                        m_board.moveToPot(SOUTH, i, SOUTH);
                    }
                    cout << "Sweeping remaining beans into " << southPlayer->name() << "'s pot." << endl;
                    cout << endl;
                }
            
                if (m_board.beansInPlay(NORTH) != 0) {
                    for (int i = 0; i <= m_board.holes(); i++) {
                        m_board.moveToPot(NORTH, i, NORTH);
                    }
                    cout << "Sweeping remaining beans into " << northPlayer->name() << "'s pot." << endl;
                    cout << endl;
                }
            return false;
        }
        
    }
   
    return true;
}
    
/*Play the game. Display the progress of the game in a manner of your choosing, provided that someone looking at the screen can follow what's happening. If neither player is interactive, then to keep the display from quickly scrolling through the whole game, it would be reasonable periodically to prompt the viewer to press ENTER to continue and not proceed until ENTER is pressed. (The ignore function for input streams is useful here.) Announce the winner at the end of the game. You can apportion to your liking the responsibility for displaying the board between this function and the move function. (Note: If when this function is called, South has no beans in play, so can't make the first move, sweep any beans on the North side into North's pot and act as if the game is thus over.)*/
void Game::play() {
    display();
    
    bool over, hasWinner;
    Side winner;
    status(over, hasWinner, winner);
    
    if (northPlayer->isInteractive() == false && southPlayer->isInteractive() == false) {
        while (!over) {
            move();
            cout << "Press ENTER to continue";
            cin.ignore(1000, '\n');
            status(over, hasWinner, winner);
        }
    }
    
    else {
        while (!over) {
            move();
            status(over, hasWinner, winner);
        }
    }
    
    if (over == true || move() == false) {
        
    //find winner after sweep
    status(over, hasWinner, winner);
    
    display(); //display final status
    
    if (over && !hasWinner) {
        cout << "The game resulted in a tie." << endl;
    }
    
    else if (hasWinner && winner == NORTH){
        cout << "The winner is " << northPlayer->name() << endl;
    }
    
    else if (hasWinner && winner == SOUTH) {
        cout << "The winner is " << southPlayer->name() << endl;
    }
    
}
    
}
    
/*Return the number of beans in the indicated hole or pot of the game's board, or −1 if the hole number is invalid. This function exists so that we and you can more easily test your program.*/
int Game::beans(Side s, int hole) const {
    if (hole < 0 || hole > m_board.holes()) {
        return -1;
    }
    
    else {
        return m_board.beans(s, hole);
    }
}
