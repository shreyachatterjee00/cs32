//
//  main.cpp
//  Homework2
//
//  Created by Shreya Chatterjee on 4/26/19.
//  Copyright © 2019 Shreya Chatterjee. All rights reserved.
//

#include <iostream>
#include <stack>
using namespace std;


class Coord
{
public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};

// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise
bool pathExists(char maze[][10], int sr, int sc, int er, int ec) {
    
    stack<Coord> coordStack;
    
    //Push the starting coordinate (sr,sc) onto the coordinate stack and
    //update maze[sr][sc] to indicate that the algorithm has encountered
    //it (i.e., set maze[sr][sc] to have a value other than '.').
    
    coordStack.push(Coord(sr, sc));
    maze[sr][sc] = '*';
    
    //While the stack is not empty
    while (coordStack.empty() == false) {
        
    //{   Pop the top coordinate off the stack. This gives you the current
        //(r,c) location that your algorithm is exploring.
    
        Coord current = coordStack.top();
        int currentRow = current.r();
        int currentCol = current.c();
        coordStack.pop();
    
        //If the current (r,c) coordinate is equal to the ending coordinate,
        //then we've solved the maze so return true!
        
        if (currentRow == er && currentCol == ec) {
            return true;
        }
        
        //Check each place you can move from the current cell as follows:
        //If you can move SOUTH and haven't encountered that cell yet,
        //then push the coordinate (r+1,c) onto the stack and update
        //maze[r+1][c] to indicate the algorithm has encountered it.
        
        if (maze[currentRow + 1][currentCol] == '.') {
            coordStack.push(Coord(currentRow + 1, currentCol));
            maze[currentRow + 1][currentCol] = '*';
        }
        
        //If you can move WEST and haven't encountered that cell yet,
        //then push the coordinate (r,c-1) onto the stack and update
        //maze[r][c-1] to indicate the algorithm has encountered it.
        
        if (maze[currentRow][currentCol -1] == '.') {
            coordStack.push(Coord(currentRow, currentCol -1));
            maze[currentRow][currentCol -1] = '*';
        }
        
        //If you can move NORTH and haven't encountered that cell yet,
        //then push the coordinate (r-1,c) onto the stack and update
        //maze[r-1][c] to indicate the algorithm has encountered it.
        
        if (maze[currentRow - 1][currentCol] == '.') {
            coordStack.push(Coord(currentRow - 1, currentCol));
            maze[currentRow - 1][currentCol] = '*';
        }
        
        //If you can move EAST and haven't encountered that cell yet,
        //then push the coordinate (r,c+1) onto the stack and update
        //maze[r][c+1] to indicate the algorithm has encountered it.
        
        if (maze[currentRow][currentCol + 1] == '.') {
            coordStack.push(Coord(currentRow, currentCol + 1));
            maze[currentRow][currentCol + 1] = '*';
        }
    }
    //There was no solution, so return false
    return false;
}

