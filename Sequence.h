//
//  Sequence.h
//  Project2
//
//  Created by Shreya Chatterjee on 4/16/19.
//  Copyright © 2019 Shreya Chatterjee. All rights reserved.
//

#ifndef Sequence_h
#define Sequence_h
#include <string>

using ItemType = std::string;

class Sequence {
    
    public:
        Sequence();
    
        //when a sequence is destroyed, the nodes in the list must be deallocated
        ~Sequence();
        //when a brand new Sequence is created as a copy of an existing Sequence, enough new nodes must be allocated to hold a duplicate of hte original list
        Sequence(const Sequence & other);
        //When an existing Sequence (the left-hand side) is assigned the value of another Sequence (the right-hand side), the result must be that the left-hand side object is a duplicate of the right-hand side object, with no memory leak of list nodes (i.e. no list node from the old value of the left-hand side should be still allocated yet inaccessible).
        Sequence & operator=(const Sequence & rhs);
        bool empty() const;
        int size() const;
        int insert(int pos, const ItemType& value);
        int insert(const ItemType& value);
        bool erase(int pos);
        int remove(const ItemType& value);
        bool get(int pos, ItemType& value) const;
        bool set(int pos, const ItemType& value);
        int find(const ItemType& value) const;
        void swap(Sequence& other);
        void dump() const;
    
    private:
    struct Node {
        ItemType m_value;
        Node * next;        //pointer to next Node
        Node * prev;        //pointer to previous Node
    };
    
    Node * head;            //pointer to first Node
    int m_size;
};


void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result);
int subsequence(const Sequence& seq1, const Sequence& seq2);

#endif

