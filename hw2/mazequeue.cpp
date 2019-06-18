//
//  mazequeue.cpp
//  Homework2
//
//  Created by Shreya Chatterjee on 4/28/19.
//  Copyright © 2019 Shreya Chatterjee. All rights reserved.
//

#include <stdio.h>

#include <iostream>
#include <queue>
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

bool pathExists(char maze[][10], int sr, int sc, int er, int ec) {
    queue<Coord> coordQueue;
    
    coordQueue.push(Coord(sr, sc));
    maze[sr][sc] = '*';
    
    while (coordQueue.empty() == false) {
        
        Coord frontCoord = coordQueue.front();
        int r = frontCoord.r();
        int c = frontCoord.c();
        coordQueue.pop();
        
        if (r == er && c == ec) {
            return true;
        }
        
        if (maze[r + 1][c] == '.') {        //south
            coordQueue.push(Coord(r + 1, c));
            maze[r + 1][c] = '*';
        }
        
        if (maze[r][c -1] == '.') {         //west
            coordQueue.push(Coord(r, c -1));
            maze[r][c - 1] = '*';
        }
        
        if (maze[r - 1][c] == '.') {        //north
            coordQueue.push(Coord(r -1, c));
            maze[r - 1][c] = '*';
        }
        
        if (maze[r][c + 1] == '.') {        //east
            coordQueue.push(Coord(r, c + 1));
            maze[r][c + 1] = '*';
        }
        
    }
    return false;
}
