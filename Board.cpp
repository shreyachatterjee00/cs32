//
//  Board.cpp
//  Project3
//
//  Created by Shreya Chatterjee on 5/13/19.
//  Copyright © 2019 Shreya Chatterjee. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include "Board.h"
using namespace std;

/*Construct a Board with the indicated number of holes per side (not counting the pot) and inital number of beans per hole. If nHoles is not positive, act as if it were 1; if nInitialBeansPerHole is negative, act as if it were 0. */
Board::Board(int nHoles, int nInitialBeansPerHole) {
    if (nHoles < 0) {
        nHoles = 1;
    }
    
    if (nInitialBeansPerHole < 0) {
        nInitialBeansPerHole = 0;
    }
    
    m_numberHoles = nHoles;
    m_initialBeansPerHole = nInitialBeansPerHole;
    
    NorthHoles = new int [nHoles];
    NorthHoles[0] = 0;
    SouthHoles = new int [nHoles];
    SouthHoles[0] = 0;
    
    for (int i = 1; i < nHoles + 1; i++) {
        NorthHoles[i] = nInitialBeansPerHole;
        SouthHoles[i] = nInitialBeansPerHole;
    }
}

Board::Board(const Board & other) {
    m_numberHoles = other.m_numberHoles;
    m_initialBeansPerHole = other.m_initialBeansPerHole;
    
    NorthHoles = new int[m_numberHoles + 1];
    SouthHoles = new int[m_numberHoles + 1];
    
    for (int i = 0; i < m_numberHoles + 1; i++) {
        NorthHoles[i] = other.NorthHoles[i];
        SouthHoles[i] = other.SouthHoles[i];
    }
}

Board & Board::operator=(const Board & rhs) {
    if (this != &rhs) {
        delete [] NorthHoles;
        delete [] SouthHoles;
        
        m_numberHoles = rhs.m_numberHoles;
        m_initialBeansPerHole = rhs.m_initialBeansPerHole;
        
        NorthHoles = new int[m_numberHoles + 1];
        SouthHoles = new int[m_numberHoles + 1];
        
        for (int i = 0; i <= m_numberHoles; i++) {
            NorthHoles[i] = rhs.NorthHoles[i];
            SouthHoles[i] = rhs.SouthHoles[i];
        }
    }
    
    return * this;
}

Board::~Board() {
    delete [] NorthHoles;
    delete [] SouthHoles;
}

/*Return the number of holes on a side (not counting the pot). */
int Board::holes() const {
    return m_numberHoles;
}

/*Return the number of beans in the indicated hole or pot, or −1 if the hole number is invalid.*/
int Board::beans(Side s, int hole) const {
    if (hole < 0 || hole > m_numberHoles) {
        return -1;
    }
    
    int beans = 0;
    if (s == NORTH) {
        beans = NorthHoles[hole];
    }
        
    if (s == SOUTH) {
        beans = SouthHoles[hole];
    }
    
    return beans;
}

/* Return the total number of beans in all the holes on the indicated side, not counting the beans in the pot.*/
int Board::beansInPlay(Side s) const {
    int total = 0;
    if (s == NORTH) {
        for (int i = 1; i <= m_numberHoles; i++) {
            total += NorthHoles[i];
        }
    }
    
    if (s == SOUTH) {
        for (int i = 1; i <= m_numberHoles; i++) {
            total += SouthHoles[i];
        }
    }
    
    return total;
}

/*Return the total number of beans in the game, including any in the pots. */
int Board::totalBeans() const {
    int total = 0;
    for (int i = 0; i <= m_numberHoles; i++) {
        total = total + NorthHoles[i] + SouthHoles[i];
    }
    
    return total;
}

/*If the hole indicated by (s,hole) is empty or invalid or a pot, this function returns false without changing anything. Otherwise, it will return true after sowing the beans: the beans are removed from hole (s,hole) and sown counterclockwise, including s's pot if encountered, but skipping s's opponent's pot. The parameters endSide and endHole are set to the side and hole where the last bean was placed. (This function does not make captures or multiple turns; different Kalah variants have different rules about these issues, so dealing with them should not be the responsibility of the Board class.) */
bool Board::sow(Side s, int hole, Side& endSide, int& endHole) {
    if (hole < 1 || hole > m_numberHoles) {     //if hole is a pot or invalid
        return false;
    }
    if (s == NORTH && NorthHoles[hole] == 0) {  //if hole is empty
        return false;
    }
    if (s == SOUTH && SouthHoles[hole] == 0) {  //if hole is empty
        return false;
    }
    
    int numBeans = 0;
    int index = hole;
    int myEndIndex = 0;
    int otherEndIndex = 0;
    int myFirstIndex = 0;
    int otherFirstIndex = 0;
    int * iterator = nullptr;
    int * otherPot = nullptr;
    int * myPot = nullptr;
    int * otherFirst = nullptr;  //other starting point, comes right after my pot
    int * myFirst = nullptr;     //my starting point, comes right after other's pot
    int * myEnd = nullptr;       //hole immediately before my pot
    int * otherEnd = nullptr;    //hole immediately before other's pot
    string operation = " ";
    
    if (s == NORTH) {
        numBeans = NorthHoles[hole];
        NorthHoles[hole] = 0;
        iterator = &NorthHoles[hole - 1];
        otherPot = &SouthHoles[0];
        myPot = &NorthHoles[0];
        otherFirst = &SouthHoles[1];
        myFirst = &NorthHoles[m_numberHoles];
        myFirstIndex = m_numberHoles;
        otherFirstIndex = 1;
        myEnd = &NorthHoles[1];
        otherEnd = &SouthHoles[m_numberHoles];
        myEndIndex = 1;
        otherEndIndex = m_numberHoles;
        operation = "sub"; //counterclockwise, so hole numbering goes downwards
    }
    
    if (s == SOUTH) {
        numBeans = SouthHoles[hole];
        SouthHoles[hole] = 0;
        if (hole == m_numberHoles) {
            iterator = &SouthHoles[0];
        }
        else {
            iterator = &SouthHoles[hole + 1];
        }
        otherPot = &NorthHoles[0];
        myPot = &SouthHoles[0];
        otherFirst = &NorthHoles[m_numberHoles];
        myFirst = &SouthHoles[1];
        myFirstIndex = 1;
        otherFirstIndex = m_numberHoles;
        myEnd = &SouthHoles[m_numberHoles];
        otherEnd = &NorthHoles[1];
        myEndIndex = m_numberHoles;
        otherEndIndex = 1;
        operation = "add"; //hole numbering goes upwards
    }
        
    while (numBeans > 0) {
        
        //if at my pot, add one bean and continue to opposite first, indicate proper operation
        if (iterator == myPot) {
            *myPot += 1;
            numBeans--;
            iterator = otherFirst; //now goes to first hole on other side
            
            if (numBeans == 0) { //if beans are over, endHole is pot
                index = 0;
                endHole = index;
                break;
            }
            
            else {
                index = otherFirstIndex;
            }
                
            if (operation == "sub") {
                operation = "add";
                index--;            //to keep the index at the current hole, not one forward
            }
                
            else {
                operation = "sub";
                index++;        //to keep index at current hole, not one forward
            }
        }
        
        //if at opposite pot, continue to my first, indicate proper operation
        else if (iterator == otherPot) {
            iterator = myFirst; //now goes to first hole on my side
            
            index = myFirstIndex; //bean will not be dropped here, so index can just be moved
                
            if (operation == "sub") {
                operation = "add";
                index--;        //to keep index at current hole, not one forward
            }
                
            else {
                operation = "sub";
                index++;        //to keep index at current hole, not one forward
            }
        }
            
        //if at my end, continue to my pot
        else if (iterator == myEnd) {
            *myEnd += 1;
            numBeans--;
            iterator = myPot;
            index = myEndIndex;
        }
            
        //if at opposite's end, continue to opposite's pot
        else if (iterator == otherEnd) {
            *otherEnd += 1;
            numBeans--;
            iterator = otherPot;
            index = otherEndIndex;
        }
            
        //else, add a bean to the current hole
        else {
            *iterator += 1;
            numBeans--;
                
            //depending on what operation is, move iterator
            if (operation == "sub") {
                iterator--;
                index--;
            }
                
            if (operation == "add") {
                iterator++;
                index++;
            }
        }
        
        //update values of endSide and endHole
        
        if (operation == "add") {
            endSide = SOUTH;
        }
        
        else if (operation == "sub") {
            endSide = NORTH;
        }
        
        endHole = index;
    }
 
    return true;
}


/*If the indicated hole is invalid or a pot, return false without changing anything. Otherwise, move all the beans in hole (s,hole) into the pot belonging to potOwner and return true.*/
bool Board::moveToPot(Side s, int hole, Side potOwner) {
    if (hole < 1 || hole > m_numberHoles) {
        return false;
    }
    
    int beansToAdd = 0;
    if (s == NORTH) {
        beansToAdd = NorthHoles[hole];
        NorthHoles[hole] = 0;
        
        if (potOwner == NORTH) {
            NorthHoles[0] += beansToAdd;
        }
        if (potOwner == SOUTH) {
            SouthHoles[0] += beansToAdd;
        }
    }
    if (s == SOUTH) {
        beansToAdd = SouthHoles[hole];
        SouthHoles[hole] = 0;
        
        if (potOwner == NORTH) {
            NorthHoles[0] += beansToAdd;
        }
        if (potOwner == SOUTH) {
            SouthHoles[0] += beansToAdd;
        }
    }
    
    return true;
}

/*If the indicated hole is invalid or beans is negative, this function returns false without changing anything. Otherwise, it will return true after setting the number of beans in the indicated hole or pot to the value of the third parameter. (This may change what beansInPlay and totalBeans return if they are called later.) This function exists solely so that we and you can more easily test your program: None of your code that implements the member functions of any class is allowed to call this function directly or indirectly. (We'll show an example of its use below.)*/
bool Board::setBeans(Side s, int hole, int beans) {
    if (hole < 0 || hole > m_numberHoles || beans < 0) {
        return false;
    }
    if (s == NORTH) {
        NorthHoles[hole] = beans;
    }
    
    if (s == SOUTH) {
        SouthHoles[hole] = beans;
    }
    
    return true;
}

