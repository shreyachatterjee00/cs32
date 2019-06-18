#include "Sequence.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
   
    Sequence s;
    assert(s.empty() == true);
    s.insert(0, 1);
    s.insert(1, 2);
    s.insert(2, 3);
    s.insert(3, 4);
    s.insert(4, 5);
    s.insert(5, 6);
    
    //sequence currently is: 1, 2, 3, 4, 5, 6
    
    s.insert(2);
    s.insert(7);
    s.insert(5, 10);
    
    //sequence currently is: 1, 2, 2, 3, 4, 10, 5, 6, 7
    //size is 9
    
    assert (s.empty() == false);
    
    assert(s.find(1) == 0);
    assert(s.find(2) == 1);
    //assert(s.find(2) == 2); the find function finds the FIRST position with the value, so it will not find 2 at index 2
    assert(s.find(3) == 3);
    assert(s.find(4) == 4);
    assert(s.find(10) == 5);
    assert(s.find(5) == 6);
    assert(s.find(6) == 7);
    assert(s.find(7) == 8);
    
    assert(s.size() == 9);
    
    s.erase(5);
    s.erase(7);
    
    //sequence currently is: 1, 2, 2, 3, 4, 5, 6
    
    assert(s.remove(2) == 2);
    
    //sequence currently is: 1, 3, 4, 5, 6
    //size is 5
    
    assert(s.find(1) == 0);
    assert(s.find(3) == 1);
    assert(s.find(4) == 2);
    assert(s.find(5) == 3);
    assert(s.find(6) == 4);
    
    assert(s.size() == 5);
    
    s.set(0, 50);
    s.set(4, 100);
    
    //sequence currently is 50, 3, 4, 5, 100
    
    assert(s.find(50) == 0);
    assert(s.find(3) == 1);
    assert(s.find(4) == 2);
    assert(s.find(5) == 3);
    assert(s.find(100) == 4);
    
    Sequence s1;
    assert(s1.empty() == true);
    assert(s1.size() == 0);
    
    //attempt things that will return -1
    
    assert(s1.insert(300, 1) == -1);
    assert(s1.insert(-1, 1) == -1);
    assert(s1.find(1) == -1);
    
    
    s1.insert(0, 10);
    s1.insert(1, 20);
    s1.insert(2, 30);
    
    //s1 currently is 10, 20, 30
    
    assert(s1.find(10) == 0);
    assert(s1.find(20) == 1);
    assert(s1.find(30) == 2);
    
    //swaq sequences
    
    s1.swap(s);
    
    //s is currently 10, 20, 30
        //size is 3
    
    assert(s.find(10) == 0);
    assert(s.find(20) == 1);
    assert(s.find(30) == 2);
    assert(s.size() == 3);
    
    //s1 is currently 50, 3, 4, 5, 100
        //size is 5
    
    assert(s1.find(50) == 0);
    assert(s1.find(3) == 1);
    assert(s1.find(4) == 2);
    assert(s1.find(5) == 3);
    assert(s1.find(100) == 4);
    assert(s1.size() == 5);

}


