//
//  arena.hpp
//  P1
//
//  Created by Sparsh Arora on 1/12/16.
//  Copyright © 2016 Sparsh Arora. All rights reserved.

class Player;
class Robot;
class History;
#include "globals.h"
#include "history.h"


#ifndef arena_hpp
#define arena_hpp


class Arena
{
public:
    // Constructor/destructor
    Arena(int nRows, int nCols);
    
    ~Arena();
    
    // Accessors
    int     rows() const;
    int     cols() const;
    Player* player() const;
    int     robotCount() const;
    int     nRobotsAt(int r, int c) const;
    bool    determineNewPosition(int& r, int& c, int dir) const;
    void    display() const;
    
    
    // Mutators
    bool   addRobot(int r, int c);
    bool   addPlayer(int r, int c);
    bool   attackRobotAt(int r, int c, int dir);
    bool   moveRobots();
    History& history();
    
private:
    int     m_rows;
    int     m_cols;
    Player* m_player;
    Robot*  m_robots[MAXROBOTS];
    History hist;
    int     m_nRobots;
};



#endif /* arena_hpp */
