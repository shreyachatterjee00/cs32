//
//  maze.cpp
//  HW3
//
//  Created by Shreya Chatterjee on 5/8/19.
//  Copyright © 2019 Shreya Chatterjee. All rights reserved.
//
bool pathExists(char maze[][10], int sr, int sc, int er, int ec) {
    /*If the start location is equal to the ending location, then we've
     solved the maze, so return true.
     Mark the start location as visted.
     For each of the four directions,
     If the location one step in that direction (from the start
     location) is unvisited,
     then call pathExists starting from that location (and
     ending at the same ending location as in the
     current call).
     If that returned true,
     then return true.
     Return false.*/
    
    //if start location is equal to end location, solved maze, return true
    if (sr == er && sc == ec) {
        return true;
    }
    
    maze[sr][sc] = '!';
    
    //south
    
    if (maze[sr + 1][sc] == '.') {
        if ((pathExists(maze, sr + 1, sc, er, ec) == true)) {
            return true;
        }
    }
    
    //west
    
    if (maze[sr][sc - 1] == '.') {
        if ((pathExists(maze, sr, sc - 1, er, ec) == true)) {
            return true;
        }
    }
    
    //north
    
    if (maze[sr - 1][sc] == '.') {
        if ((pathExists(maze, sr - 1, sc, er, ec)) == true) {
            return true;
        }
    }
    
    //east
    
    if (maze[sr][sc + 1] == '.') {
        if ((pathExists(maze, sr, sc + 1, er, ec)) == true) {
            return true;
        }
    }
    
    return false;
}





