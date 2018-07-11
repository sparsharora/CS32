//
//  main.cpp
//  maze
//
//  Created by Sparsh Arora on 2/9/16.
//  Copyright © 2016 Sparsh Arora. All rights reserved.
//
#include <iostream>
#include <string.h>
using namespace std;



bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
    if(sr==er && sc==ec)
        return true;
    maze[sr][sc]='#';
    
    if(maze[sr-1][sc]=='.' && maze[sr-1][sc]!='A')
    {
        if(pathExists(maze, nRows, nCols, sr-1, sc, er, ec))
            return true;
    }
    if(maze[sr][sc+1]=='.' && maze[sr][sc+1]!='A')
    {
        if(pathExists(maze, nRows, nCols, sr, sc+1, er, ec))
            return true;
    }
    if(maze[sr+1][sc]=='.' && maze[sr+1][sc]!='A')
    {
        if(pathExists(maze, nRows, nCols, sr+1, sc, er, ec))
            return true;
    }
    if(maze[sr][sc-1]=='.' && maze[sr][sc-1]!='A')
    {
        if(pathExists(maze, nRows, nCols, sr, sc-1, er, ec))
            return true;
    }
    
    return false;
    
}