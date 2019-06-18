//
//  History.cpp
//  Project1
//
//  Created by Shreya Chatterjee on 4/4/19.
//  Copyright © 2019 Shreya Chatterjee. All rights reserved.
//

#include <stdio.h>
#include "History.h"
#include <iostream>
using namespace std;

History::History(int nRows, int nCols) {
    m_row = nRows;
    m_col = nCols;
    
    nRows--;
    nCols--;
    
    for (int i = 0; i <= nRows; i++) {
        for (int j = 0; j <= nCols; j++) {
            historyArena[i][j] = '.';
        }
    }
}

bool History::record(int r, int c) {
    if (r > MAXROWS || c > MAXCOLS) {
        return false;
    }
    
    else {
        if (historyArena[r][c] == '.') {
            historyArena[r][c] = 'A';
        }
        else if (historyArena[r][c] == 'Y') {
            historyArena[r][c] = 'Z';
        }
        else {
            char value = historyArena[r][c];
            value = value + 1;
            historyArena[r][c] = value;
            
        }
        return true;
    }
}

void History::display() const {
    clearScreen();
    for (int i = 0; i < m_row; i++) {
        for (int j = 0; j < m_col; j++) {
            cout << historyArena[i][j];
        }
        
        cout << endl;
    }
    
    cout << endl;
}


