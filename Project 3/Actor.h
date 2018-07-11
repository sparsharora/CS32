#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

class StudentWorld;

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class Actor: public GraphObject
{
public:
    Actor(int imageID, int startX, int startY, StudentWorld* m_student, Direction dir = right, double size = 1.0, unsigned int depth = 0);
    StudentWorld* getWorld();
    
    virtual void doSomething()=0;
    virtual ~Actor();
    bool isAlive() const;
    void setAlive(bool val);
    
private:
    StudentWorld *stud;
    bool alive;
    
};

class Activators: public Actor
{
public:
    Activators(int ID, int x, int y, StudentWorld* world);
    virtual void doSomething()=0;
    virtual ~Activators();
    
    
};

class Agent: public Actor
{
public:
    Agent(int ID, int x, int y, Direction dir, StudentWorld* world);
    virtual void doSomething()=0;
    virtual ~Agent();
    
};


class Protester: public Agent
{
public:
    Protester(int ID, StudentWorld* world);
    virtual void doSomething()=0;
    virtual ~Protester();
    int hitP();
    int getState();
private:
    int hit, state;
    //state=0 if not leave =1 if leave
    
};

class RegularProtesters: public Protester
{
public:
    RegularProtesters(int ID, StudentWorld* world);
    virtual void doSomething();
    virtual ~RegularProtesters();
private:
    
    int numSq;
    int ticksToWaitBetweenMoves;
    int curr, scream;
    
};

class HardCoreProtesters: public Protester
{
public:
    HardCoreProtesters(int ID, StudentWorld* world);
    virtual void doSomething();
    virtual ~HardCoreProtesters();
private:
    int curr,  ticksToWaitBetweenMoves;
    
};

class FrackMan: public Agent
{
public:
    FrackMan(StudentWorld* m_world);
    int getHealth();
    int getWater();
    int getSonar();
    int getBarrels();
    int getGold();
    void increaseWater(int x);
    void reduceB();
    void incS(int x);
    void increaseNugget(int x);
    void decHealth(int x);
    
    virtual void doSomething();
    virtual ~FrackMan();
private:
    int health;
    int sonar;
    int water;
    int barrels;
    int gold;
   
};

class Dirt: public Actor
{
public:
    Dirt(int x, int y, StudentWorld* m_world);
    virtual void doSomething();
    virtual ~Dirt();
    
};

class Boulder: public Actor
{
public:
    Boulder(int x, int y, StudentWorld* m_world);
    virtual void doSomething();
    virtual ~Boulder();
private:
    int stab;//stab=0 , wait=1, fall=2
    int h;
    int ctr;

};

class Squirt: public Actor
{
public:
    Squirt(int x, int y, Direction dir, StudentWorld* m_world);
    virtual void doSomething();
    virtual ~Squirt();
private:
    int dist;
    
    
};

class WaterPool : public Activators
{
public:
    WaterPool(int startX, int startY, StudentWorld* world);
    virtual ~WaterPool();
    virtual void doSomething();
    
private:
    
    int m_wait;
    int m_maxTime;
};

class Barrel: public Activators
{
public:
    Barrel(int x, int y, StudentWorld* world);
    virtual ~Barrel();
    virtual void doSomething();
private:
};

class Sonar: public Activators
{
public:
    Sonar(int x, int y, StudentWorld* world);
    virtual ~Sonar();
    virtual void doSomething();
    
private:
    int ctr; int max;
};

class Gold: public Activators
{
public:
    Gold(int x, int y, StudentWorld* world, int a);
    virtual ~Gold();
    void virtual doSomething();
private:
    
};



#endif // ACTOR_H_
