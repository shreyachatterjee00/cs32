//
//  History.h
//  Project1
//
//  Created by Shreya Chatterjee on 4/4/19.
//  Copyright © 2019 Shreya Chatterjee. All rights reserved.
//

#ifndef History_h
#define History_h

#include "globals.h"

class History
{
public:
    History(int nRows, int nCols);
    /*returns false if r and c are not within bounds, true otherwise*/
    bool record(int r, int c);
    void display() const;
    
private:
    char historyArena[MAXROWS][MAXCOLS];
    int m_row;
    int m_col;
};

#endif /* History_h */
