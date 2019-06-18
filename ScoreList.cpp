//
//  ScoreList.cpp
//  Homework1
//
//  Created by Shreya Chatterjee on 4/11/19.
//  Copyright © 2019 Shreya Chatterjee. All rights reserved.
//

#include <stdio.h>
#include "ScoreList.h"
#include <iostream>
using namespace std;

//Create an empty ScoreList
ScoreList::ScoreList() : m_sequence() {
    
}

// If the score is valid (a value from 0 to 100) and the score list
// has room for it, add it to the score list and return true.
// Otherwise, leave the score list unchanged and return false.
bool ScoreList::add(unsigned long score) {
    bool flag;
    if (score <= 100) {
        int result = m_sequence.insert(score);
        if (result == -1) {
            flag = false;
        }
        else {
            flag = true;
        }
    }
    else {
        flag = false;
    }
    return flag;
}

// Remove one instance of the specified score from the score list.
// Return true if a score was removed; otherwise false.
bool ScoreList::remove(unsigned long score) {
    if (m_sequence.find(score) == -1) {
        return false;
    }
    else {
        int pos = m_sequence.find(score);
        m_sequence.erase(pos);
        return true;
    }
    
}

// Return the number of scores in the list.
int ScoreList::size() const {
    return m_sequence.size();
}

// Return the lowest score in the score list.  If the list is
// empty, return NO_SCORE.
unsigned long ScoreList::minimum() const {
    unsigned long minScore = 100;
    ItemType m_value = 0;
    if (m_sequence.empty() == true) {
        return NO_SCORE;
    }
    else {
        for (int i = 0; i < m_sequence.size(); i++) {
            m_sequence.get(i, m_value);
            if (m_value < minScore) {
                minScore = m_value;
            }
        }
        return minScore;
    }
}

// Return the highest score in the score list.  If the list is
// empty, return NO_SCORE.
unsigned long ScoreList::maximum() const {
    unsigned long maxScore = 0;
    ItemType m_value = 0;
    if (m_sequence.empty() == true) {
        return NO_SCORE;
    }
    else {
        for (int i = 0; i < m_sequence.size(); i++) {
            m_sequence.get(i, m_value);
            if (m_value > maxScore) {
                maxScore = m_value;
            }
            
        }
        return maxScore;
    }
}

