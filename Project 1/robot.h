//
//  robot.hpp
//  P1
//
//  Created by Sparsh Arora on 1/12/16.
//  Copyright © 2016 Sparsh Arora. All rights reserved.
//
class Arena;

#ifndef robot_hpp
#define robot_hpp

class Robot
{
public:
    // Constructor
    Robot(Arena* ap, int r, int c);
    
    // Accessors
    int  row() const;
    int  col() const;
    
    // Mutators
    void move();
    bool getAttacked(int dir);
    
private:
    Arena* m_arena;
    int    m_row;
    int    m_col;
    int    m_health;
};


#endif /* robot_hpp */

