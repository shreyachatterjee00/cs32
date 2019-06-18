//
//  testScoreList.cpp
//  Homework1
//
//  Created by Shreya Chatterjee on 4/11/19.
//  Copyright © 2019 Shreya Chatterjee. All rights reserved.
//

#include <stdio.h>
#include "ScoreList.h"
#include <iostream>
#include <cassert>
using namespace std;

int main() {
    ScoreList scoreList;
    assert(scoreList.maximum() == NO_SCORE);
    assert(scoreList.minimum() == NO_SCORE); //no scores for min or max yet
    
    scoreList.add(50);
    scoreList.add(100);
    scoreList.add(32);
    scoreList.add(44);
    scoreList.add(77);
    scoreList.add(32);
    
    assert(scoreList.add(-2) == false);
    
    //current score list is: 32, 32, 44, 50, 77, 100
        //size is 6
    
    assert(scoreList.size() == 6);
    
    assert(scoreList.remove(200) == false);
    
    scoreList.remove(32); //test if it removes only one instance of 32
    
    //current score list is: 32, 44, 50, 77, 100
        //size is 5
    
    assert(scoreList.size() == 5);
    
    assert(scoreList.minimum() == 32);
    assert(scoreList.maximum() == 100);
    
}
