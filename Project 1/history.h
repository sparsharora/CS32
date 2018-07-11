//
//  history.hpp
//  P1
//
//  Created by Sparsh Arora on 1/12/16.
//  Copyright © 2016 Sparsh Arora. All rights reserved.
//
#include "globals.h"
#ifndef history_hpp
#define history_hpp

class History
{
public:
    History(int nRows, int nCols);
    bool record(int r, int c);
    void display() const;
private:
    int rows,cols;
    int hgrid[MAXROWS][MAXCOLS];
};


#endif /* history_hpp */
