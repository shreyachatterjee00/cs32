//
//  newSequence.cpp
//  Homework1
//
//  Created by Shreya Chatterjee on 4/12/19.
//  Copyright © 2019 Shreya Chatterjee. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include "newSequence.h"
using namespace std;

Sequence::Sequence(int size) {
    maxSize = size;
    m_size = 0;
    array = new ItemType [size];
}

Sequence::Sequence(const Sequence & other) {
    m_size = other.m_size;
    maxSize = other.maxSize;
    array = new ItemType [maxSize];
    for (int i = 0; i < m_size; i++) {
        *(array + i) = *(other.array + i);
    }
}

Sequence & Sequence::operator=(const Sequence &rhs) {
    if (this != &rhs) {
        Sequence temp(rhs);
        swap(temp);
    }
    return * this;
}



bool Sequence::empty() const {
    if (m_size == 0) {
        return true;
    }
    else {
        return false;
    }
}

int Sequence::size() const {
    return m_size;
}

// Insert value into the sequence so that it becomes the item at
// position pos.  The original item at position pos and those that
// follow it end up at positions one higher than they were at before.
// Return pos if 0 <= pos <= size() and the value could be
// inserted.  (It might not be, if the sequence has a fixed capacity,
// e.g., because it's implemented using a fixed-size array.)  Otherwise,
// leave the sequence unchanged and return -1.  Notice that
// if pos is equal to size(), the value is inserted at the end.
 int Sequence::insert(int pos, const ItemType& value) {
 
 if (pos >= 0 && pos <= size() && size() != DEFAULT_MAX_ITEMS) {
 m_size++;
 for (int i = size() -1; i > pos; i--) {
 array[i] = array[i-1];
 }
 array[pos] = value;
 return pos;
 }
 else {
 return -1;
 }
 }

// Let p be the smallest integer such that value <= the item at
// position p in the sequence; if no such item exists (i.e.,
// value > all items in the sequence), let p be size().  Insert
// value into the sequence so that it becomes the item at position
// p.  The original item at position p and those that follow it end
// up at positions one higher than before.  Return p if the value
// was actually inserted.  Return -1 if the value was not inserted
// (perhaps because the sequence has a fixed capacity and is full).
int Sequence::insert(const ItemType& value) {
    if (m_size < maxSize) {
        int p = size();
        if (size() == DEFAULT_MAX_ITEMS) {
            return -1;
        }
        else {
            for (int i = 0; i < size(); i++) {
                if (value <= array[i]) {
                    p = i;
                    break;
                }
            }
            insert(p, value);
            return p;
        }
        return p;
    }
    else {
        return -1;
    }
}

// If 0 <= pos < size(), remove the item at position pos from
// the sequence (so that all items that followed that item end up at
// positions one lower than they were at before), and return true.
// Otherwise, leave the sequence unchanged and return false.
 bool Sequence::erase(int pos) {
 if (0 <= pos && pos < size()) {
 for (int i = pos; i < size(); i++) {
 array[i] = array[i+1];
 }
 m_size--;
 return true;
 }
 
 else {
 return false;
 }
 }


// Erase all items from the sequence that == value.  Return the
// number of items removed (which will be 0 if no item == value).
int Sequence::remove(const ItemType& value) {
    int counter = 0;
    for (int i = 0; i < size(); i++) {
        if (array[i] == value) {
            erase(i);
            counter++;
            i--;
        }
    }
    return counter;
}

// If 0 <= pos < size(), copy into value the item at position pos
// of the sequence and return true.  Otherwise, leave value unchanged
// and return false.
bool Sequence::get(int pos, ItemType& value) const {
    if (0 <= pos && pos < size()) {
        value = array[pos];
        return true;
    }
    else {
        return false;
    }
}

// If 0 <= pos < size(), replace the item at position pos in the
// sequence with value and return true.  Otherwise, leave the sequence
// unchanged and return false.
bool Sequence::set(int pos, const ItemType& value) {
    if (0 <= pos && pos < size()) {
        array[pos] = value;
        return true;
    }
    else {
        return false;
    }
}

// Let p be the smallest integer such that value == the item at
// position p in the sequence; if no such item exists, let p be -1.
// Return p.
int Sequence::find(const ItemType& value) const {
    int p = -1;
    for (int i = 0; i < size(); i++) {
        if (array[i] == value) {
            p = i;
            break;
        }
    }
    return p;
}

// Exchange the contents of this sequence with the other one.
void Sequence::swap(Sequence& other) {
    
    ItemType * tempPtr;
    int tempSize;
    int tempMax;
    
    tempPtr = array;
    tempSize = m_size;
    tempMax = maxSize;
    
    array = other.array;
    m_size = other.m_size;
    maxSize = other.maxSize;
    
    other.array = tempPtr;
    other.m_size = tempSize;
    other.maxSize = tempMax;
    
}

void Sequence::dump() const {
    cerr << "size of array is: " << size() << endl;
    for (int i = 0; i < this->size(); i++) {
        cerr << i << ": " << * (array + i) << endl;
    }
}

Sequence::~Sequence() {
    delete [] array;
}



