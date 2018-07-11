//
//  main.cpp
//  hw23
//
//  Created by Sparsh Arora on 2/1/16.
//  Copyright © 2016 Sparsh Arora. All rights reserved.
//
#include <cstring>
#include <iostream>
#include <queue>

using namespace std;


bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec);
// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise


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


bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
    queue<Coord> coordqueue;
    
    coordqueue.push(Coord(sr,sc));
    maze[sr][sc]='A';
    
    while (!coordqueue.empty())
    {
        Coord c=coordqueue.front();
        coordqueue.pop();
        if(c.r()==er && c.c()==ec)
            return true;
        if(maze[c.r()-1][c.c()]=='.' && maze[c.r()-1][c.c()]!='A')
        {
            coordqueue.push(Coord(c.r()-1, c.c()));
            maze[c.r()-1][c.c()]='A';
            
        }
        if(maze[c.r()][c.c()+1]=='.' && maze[c.r()][c.c()+1]!='A')
        {
            coordqueue.push(Coord(c.r(), c.c()+1));
            maze[c.r()][c.c()+1]='A';
            
        }
        if(maze[c.r()+1][c.c()]=='.' && maze[c.r()+1][c.c()]!='A')
        {
            coordqueue.push(Coord(c.r()+1, c.c()));
            maze[c.r()+1][c.c()]='A';
            
        }
        if(maze[c.r()][c.c()-1]=='.' && maze[c.r()][c.c()-1]!='A')
        {
            coordqueue.push(Coord(c.r(), c.c()-1));
            maze[c.r()][c.c()-1]='A';
            
        }
        
        
    }
    
    
    return false;
    
    
}

