//
//  testnewSequence.cpp
//  Homework1
//
//  Created by Shreya Chatterjee on 4/12/19.
//  Copyright © 2019 Shreya Chatterjee. All rights reserved.
//

#include <stdio.h>
#include "newSequence.h"
#include <iostream>
#include <cassert>
using namespace std;

int main() {
    Sequence a(1000);   // a can hold at most 1000 items
    Sequence b(5);      // b can hold at most 5 items
    Sequence c;         // c can hold at most DEFAULT_MAX_ITEMS items
    ItemType v = 40;        //some value of the appropriate type
    
    // No failures inserting 5 items into b
    for (int k = 0; k < 5; k++)
        assert(b.insert(v) != -1);
    
    //b.dump();
    
    // Failure if we try to insert a sixth item into b
    assert(b.insert(v) == -1);
    
    // When two Sequences' contents are swapped, their capacities are
    // swapped as well:
    a.swap(b);
    assert(a.insert(v) == -1  &&  b.insert(v) != -1);
    
    //my testing
    Sequence d(5);
    d.insert(1);
    d.insert(2);
    d.insert(3);
    d.insert(4);
    d.insert(5);
    
    assert(d.find(1) == 0);
    assert(d.find(2) == 1);
    assert(d.find(3) == 2);
    assert(d.find(4) == 3);
    assert(d.find(5) == 4);
    
    assert(d.insert(6) == -1);
    
    Sequence e (3);
    
    e.insert(10);
    e.insert(20);
    e.insert(30);
    
    d.swap(e);
    
    //d.dump();
    //e.dump();
    
    Sequence s(3);
    s.insert(5);
    s.insert(10);
    s.insert(15);
    
    Sequence t = s;     //should call copy constructor, t should be created w contents of s
    
    //t.dump();
    //s.dump();
    
    Sequence y(4);
    y.insert(1);
    y.insert(2);
    y.insert(3);
    y.insert(4);
    
    s = y;          //should call assignment operator, s should contain contents of y
    
    s.dump();
    y.dump();
    
}


