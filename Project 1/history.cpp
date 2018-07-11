//
//  history.cpp
//  P1
//
//  Created by Sparsh Arora on 1/12/16.
//  Copyright © 2016 Sparsh Arora. All rights reserved.
//

#include "history.h"
#include "arena.h"
#include<iostream>
using namespace std;

History::History(int nRows, int nCols)
{
    rows=nRows;
    cols=nCols;
    
    for(int i=0; i<rows; i++)
        for(int j=0;j<cols;j++)
            hgrid[i][j]=0;
}

bool History::record(int r, int c)
{
    if(r<1 || c<1 || r>rows || c>cols)
    return false;
    
    hgrid[r-1][c-1]++;
    
    return true;
    
}


void History :: display() const
{
    char x;
    clearScreen();
    for(int i=0;i<rows;i++)
    {  for(int j=0;j<cols;j++)
        { if(hgrid[i][j]==0)
                cout<<".";
            else
            {   x='A'-1+hgrid[i][j];
                cout<<x;
            }
            
        }
    cout<<endl;
     }
    cout<<endl;
}


