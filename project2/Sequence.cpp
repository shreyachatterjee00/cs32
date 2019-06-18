//
//  Sequence.cpp
//  Project2
//
//  Created by Shreya Chatterjee on 4/16/19.
//  Copyright © 2019 Shreya Chatterjee. All rights reserved.
//

#include <stdio.h>
#include "Sequence.h"
#include <iostream>
using namespace std;

Sequence::Sequence() {
    //constructs empty sequence
    head = nullptr;
    m_size = 0;
}

Sequence::~Sequence() { //destructor
    Node * p;
    p = head;                   //p starts at the beginning
    while (p != nullptr) {
        Node * q = p->next;     //node q is the next value of p
        delete p;
        p = q;                  //p takes on value of the next node
        
    }
}

Sequence::Sequence(const Sequence & other) {
    this->m_size = other.m_size;
    
    head = nullptr;
    
    Node * p;                   //other's head
    
    Node * newNode = new Node;     //establish head node
    newNode->m_value = other.head->m_value;
    newNode->next = nullptr;
    newNode->prev = nullptr;
    head = newNode;
    
    Node * a = this->head;      //this obj's head
   
    for (p = other.head->next; p != nullptr; p = p->next) {   //loop for original sequence, start from one                                                            after head because head already has a node
        Node * newNode = new Node;
        newNode->m_value = p->m_value;                        //make values of nodes equal
        newNode->prev = a;                                    //a is the node before the current one
        newNode->next = nullptr;
        a->next = newNode;                                   //make a's pointer point to the current node
        a = newNode;
    }
    
}

Sequence& Sequence::operator=(const Sequence& rhs) {
    if (this != &rhs) {
        Sequence temp (rhs);
        swap(temp);
    }
    return * this;
}

bool Sequence::empty() const {  //returns true if empty, false if not
    if (m_size != 0) {
        return false;
    }
    else {
        return true;
    }
}

int Sequence::size() const {    //return size of list
    return m_size;
}

bool Sequence::get(int pos, ItemType& value) const {    //changes value to the value at parameter pos
    if (pos >= 0 && pos < size()) {
        Node * p;
        p = head;
        for (int i = 0; i < pos; i++) {
            if (p != nullptr) {
                p = p->next;
            }
        }
        
        if (p != nullptr) {
            value = p->m_value;
            return true;
        }
        
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

bool Sequence::set(int pos, const ItemType& value) {    //set item at pos to value, return false if can't be done
    if (pos >= 0 && pos < size()) {
        Node * p;
        p = head;
        for (int i = 0; i < pos; i++) { //traverse list
            if (p != nullptr) {
                p = p->next;
            }
        }
        
        if (p != nullptr) {
            p->m_value = value;
            return true;
        }
        
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

int Sequence::insert(int pos, const ItemType &value) {
    if (pos >= 0 && pos <= size()) {
        if (head != nullptr) {              //list is not empty
            //insert at beginning
            if (pos == 0) {
                Node * newNode = new Node;
                newNode->m_value = value;
                newNode->next = head;
                newNode->prev = nullptr;
                head->prev = newNode;
                head = newNode;
                m_size++;
                return pos;
            }
            //insert at end
            else if (pos == size()){
                Node * p = head;
                for (p = head; p->next != nullptr; p = p->next) {
                }
                Node * newNode = new Node;
                newNode->m_value = value;
                newNode->next = nullptr;
                newNode->prev = p;
                p->next = newNode;
                m_size++;
                return pos;
            }
            //insert at middle
            else {
                Node * p = head;
                for (int i = 0; i < pos - 1; i++) {
                    p = p->next;
                }
                Node * newNode = new Node;
                newNode->m_value = value;
                newNode->next = p->next;
                newNode->prev = p;
                p->next = newNode;
                newNode->next->prev = newNode;
                m_size++;
                return pos;
            }
        }
        else {  //head is null, empty list, inserting at beginning
            Node * newNode = new Node;
            newNode->m_value = value;
            newNode->next = nullptr;
            newNode->prev = nullptr;
            head = newNode;
            m_size++;
            return 0;
        }
    }
    else {
        return -1;
    }
}

int Sequence::insert(const ItemType& value) {
    Node * p = head;
    int pos = 0;
    int counter = 0;
    for (int i = 0; i < size(); i++) {  //loop through to find value

        if (p != nullptr) {
            if (value <= p->m_value) {  //found value
                pos = i;
                break;
            }
        }
        if (counter != size() -1) {
            p = p->next;
        }
        counter++;
    }

    if (counter == size()) {
        pos = size();
    }
    
insert(pos, value);
return pos;
}

bool Sequence::erase(int pos) {
    if (pos >= 0 && pos < size()) {
        
        if (pos == 0) {             //deleting first item
            Node * deadNode = head;
            head = deadNode->next;
            delete deadNode;
            m_size--;
            return true;
        }
        
        else if (pos + 1 == size()) {   //deleting last item
            Node * p = head;
            //traverse to last node
            for (p = head; p->next != nullptr; p = p->next) {
            }
            p->prev->next = nullptr;
            delete p;
            m_size--;
            return true;
            
        }
        else {                          //deleting some item in the middle
            Node * p = head;
            for (int i = 0; i < pos; i++) {
                p = p->next;            //p points to pointer we want to delete
            }
            p->prev->next = p->next;
            p->next->prev = p->prev;
            delete p;
            m_size--;
            return true;
        }
    }
    else {
        return false;
    }
}


int Sequence::remove(const ItemType& value) {
    Node * p = head;
    int counter = 0;
    for (int i = 0; i < size(); i++) {  //find index of value to delete
        if (p->m_value == value) {
            erase(i);
            i--;
            counter++;
        }
        p = p->next;
    }
    return counter;
}

int Sequence::find(const ItemType& value) const { //find first index where value exists
    Node * p;
    int counter = 0;
    for (p = head; p != nullptr; p = p->next) {
        if (p->m_value == value) {
            break;
        }
        counter++;
    }
    if (p != nullptr) {
        return counter;
    }
    else {
        return -1;
    }
}

void Sequence::swap(Sequence& other) {
    //swap sizes
    int tempSize = this->m_size;
    this->m_size = other.m_size;
    other.m_size = tempSize;
    
    //swap head pointers
    Node * tempHead = this->head;
    this->head = other.head;
    other.head = tempHead;
}

void Sequence::dump() const {
    for (Node * p = head; p != nullptr; p = p->next) {        //create a new Node variable that can be used to go through list
        cerr << p->m_value << endl;
    }
}

//NON MEMBER FUNCTIONS

void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result) {
    
    //check if any of the sequences are empty
    if (seq1.empty() == true && seq2.empty() != true) {
        result = seq2;
    }
    else if (seq2.empty() == true && seq1.empty() != true) {
        result = seq1;
    }
    else if (seq1.empty() == true && seq2.empty() == true) {    //if both sequences are empty, result should be empty
        for (int i = (result.size() - 1); i >= 0; i--) {       //clear result so we can put stuff in it
            result.erase(i);
        }
    }
    
    //both sequences have stuff in them
    else {
        Sequence temp;                      //in case of aliasing
        
        if (result.empty() == false) {
            temp = result;
        }
        
        for (int i = (temp.size() - 1); i >= 0; i--) {       //clear result so we can put stuff in it
            temp.erase(i);
        }
        
        int difference = 0;
        difference = seq1.size() - seq2.size();
        if (difference < 0) {
            difference = difference * -1;
        }
        
        int iterations = 0;                 //figure out how many times to iterate the for loop, depending on size of                                       sequences
        if (seq1.size() == seq2.size()) {
            iterations = seq1.size() + seq2.size(); //iterate enough times to put all items of each in the seq
        }
        else {
            iterations = seq1.size() + seq2.size() + (difference * 2);
            //add items in both sequences
            //difference in items between sequences multiplied by 2 b/c the for loop depends on whether i is even or odd
            //without multiplying difference by 2, this code will not update result if i is even or odd
            //both if statements below will never be satisfied: either i is not even/odd, or the sequence counter is not less than the size
        }
        
        ItemType seq1val;
        ItemType seq2val;
        
        int seq1counter = 0;            //keeps track of the number of elements in seq1
        int seq2counter = 0;            //keeps track of the number of elements in seq2
        int generalCounter = 0;         //keeps track of the number of elements in result
        
        for (int i = 0; i < iterations; i++) {
            if (i % 2 == 0 || i == 0) {             //if i is even, input a member from seq1
                if (seq1counter < seq1.size()) {    //AND if there are still items left in seq 1
                    seq1.get(seq1counter, seq1val);
                    temp.insert(generalCounter, seq1val);
                    seq1counter++;
                    generalCounter++;
                }
            }
            
            else if (i % 2 == 1) {                  //if i is odd, input a member from seq 2
                if (seq2counter < seq2.size()) {    //AND if there are still items left in seq 2
                    seq2.get(seq2counter, seq2val);
                    temp.insert(generalCounter, seq2val);
                    seq2counter++;
                    generalCounter++;
                }
            }
        }
        result = temp;
    }
    
}

int subsequence(const Sequence& seq1, const Sequence& seq2) {
    //loop through seq 1
    //if get at 0 = get at 0 for both
    //check if the rest of seq2 is found here
    //if yes then return that position
    //if not then keep looping
    ItemType seq1val;
    ItemType seq2headVal;
    ItemType seq2val;
    
    int m_return = -1;
    
    seq2.get(0, seq2headVal);
    for (int i = 0; i < seq1.size(); i++) {
        seq1.get(i, seq1val);
        
        if (seq1val == seq2headVal) {
            int counter = 0;
            
            for (int j = 0; j < seq2.size(); j++) {
                seq1.get((i+j), seq1val);
                seq2.get(j, seq2val);
                
                if (seq1val == seq2val) {
                    counter++;
                }
                
                if (counter == seq2.size()) {
                    m_return = i;
                }
            }
        }
        
    }
    return m_return;
}
