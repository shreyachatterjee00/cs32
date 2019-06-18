//
//  linear.cpp
//  HW3
//
//  Created by Shreya Chatterjee on 5/7/19.
//  Copyright © 2019 Shreya Chatterjee. All rights reserved.
//

// Return false if the somePredicate function returns false for at
// least one of the array elements; return true otherwise.
bool allTrue(const string a[], int n)
{
    if (n <= 0) {
        return true;
    }
    
    bool predicate = somePredicate(a[n - 1]);
    
    return (predicate && allTrue(a, n - 1));
}

// Return the number of elements in the array for which the
// somePredicate function returns false.
int countFalse(const string a[], int n)
{
    if (n <= 0) {
        return 0;
    }
    
    if (somePredicate(a[n - 1]) == false) {
        return 1 + (countFalse(a, n - 1));
    }
    else {
        return (countFalse(a, n -1));
    }
}

// Return the subscript of the first element in the array for which
// the somePredicate function returns false.  If there is no such
// element, return -1.
int firstFalse(const string a[], int n)
{
    if (n <= 0) {
        return -1;
    }
        
    if (somePredicate(a[0]) == false) {
        return 0;
    }
    
    
    if (firstFalse(a + 1, n - 1) == -1) {
        return -1;
    }
    
    else {
        return 1 + firstFalse(a + 1, n - 1);
    }
}

// Return the subscript of the least string in the array (i.e.,
// return the smallest subscript m such that a[m] <= a[k] for all
// k from 0 to n-1).  If the function is told to examine no
// elements, return -1.
int indexOfLeast(const string a[], int n)
{
    if (n < 0) {
        return -1;
    }
    
    if (n == 0) {
        return 0;
    }
        
        int index = indexOfLeast(a, n - 1);
        
        if (a[index] <= a[n - 1]) {
            return indexOfLeast(a, n - 1);
        }
        
        else {
            return n - 1;
        }
    
}



// If all n2 elements of a2 appear in the n1 element array a1, in
// the same order (though not necessarily consecutively), then
// return true; otherwise (i.e., if the array a1 does not include
// a2 as a not-necessarily-contiguous subsequence), return false.
// (Of course, if a2 is empty (i.e., n2 is 0), return true.)
// For example, if a1 is the 7 element array
//    "stan" "kyle" "cartman" "kenny" "kyle" "cartman" "butters"
// then the function should return true if a2 is
//    "kyle" "kenny" "butters"
// or
//    "kyle" "cartman" "cartman"
// and it should return false if a2 is
//    "kyle" "butters" "kenny"
// or
//    "stan" "kenny" "kenny"
bool includes(const string a1[], int n1, const string a2[], int n2) {
    if (n2 == 0) {
        return true;
    }
    
    if (n2 > n1) {
        return false;
    }
    
    if (a1[n1 - 1] == a2 [n2 - 1]) {
        //top elements are equal, keep going to see if other elements are as well
        return includes(a1, n1 - 1, a2, n2 - 1);
    }
    
    else {  //elements are not equal, keep going through a1
        return includes(a1, n1 - 1, a2, n2);
    }
}
