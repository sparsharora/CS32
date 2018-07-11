#include "Actor.h"
#include "StudentWorld.h"
#include <cmath>
#include <queue>

queue<GraphObject> explore;
// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp

Actor::Actor(int imageID, int startX, int startY, StudentWorld* m_studentworld, Direction dir , double size , unsigned int depth ):GraphObject( imageID,  startX,  startY,  dir ,  size , depth ), stud(m_studentworld)
{
        setVisible(true);
        alive=true;
    
}

Actor::~Actor()
{
    setVisible(false);
}

StudentWorld* Actor::getWorld()
{
    return stud;
}

bool Actor::isAlive() const
{
    if(alive)
        return true;
    else
        return false;
}

void Actor::setAlive(bool val)
{
    alive=val;
}

//============================================================================================


FrackMan::FrackMan(StudentWorld* m_world):Agent(IID_PLAYER, 30, 60, right, m_world)
{
    health=100;
    water=5;
    sonar=1;
    barrels=2;
    gold=0;
}

void FrackMan::increaseWater(int x)
{
    water+=5;
}

void FrackMan::increaseNugget(int x)
{
    gold+=1;
}

void FrackMan::decHealth(int x)
{
    health-=x;
}
void FrackMan::incS(int x)
{
    sonar+=2;
}

int FrackMan::getGold()
{
    
    return gold;
}
int FrackMan::getHealth()
{
    return health;
}

int FrackMan::getBarrels()
{
    return barrels;
}

int FrackMan::getSonar()
{
    if(sonar<0)
        sonar=0;
    return sonar;
}

int FrackMan::getWater()
{
    if(water<0)
        water=0;
    
    return water;
}

void FrackMan::reduceB()
{
    barrels--;
}

void FrackMan::doSomething()
{
    
    int ch;
    
    if (getWorld()->getKey(ch) == true)
    {
        // user hit a key this tick!
        switch (ch)
        {
           // case KEY_PRESS_ESCAPE:
                
            
            case KEY_PRESS_LEFT:
            { if(getX()>0)
                {
                    if(getDirection()!=left)
                        setDirection(left);
                    else if(getWorld()->isOverlapFrack(getX()-1, getY()))
                            {
                                
                            }
                    else
                    {   moveTo(getX()-1, getY());
                    
                        for(int i=getY(); i<60 && i<getY()+4;i++)
                            getWorld()->dirtremove(getX(),i);
                    }
                }

                else
                {   setDirection(left);
                    moveTo(getX(),getY());
                }
                break;
            }
            case KEY_PRESS_RIGHT:
            {
                if(getX()<60)
                {
                    if(getDirection()!=right)
                        setDirection(right);
                    else if(getWorld()->isOverlapFrack(getX()+1, getY()))
                    {
                        
                    }
                    else
                    {
                        moveTo(getX()+1, getY());
                    for(int i=getY();i<60 && i<getY()+4 ;i++)
                       getWorld()->dirtremove(getX()+3,i);
                        
                    }
                }
                else
                {   setDirection(right);
                    moveTo(getX(),getY());
                }
            }
                    break;
            case KEY_PRESS_UP:
            { if(getY()<60 )
                {   if(getDirection()!=up)
                    setDirection(up);
                else if(getWorld()->isOverlapFrack(getX(), getY()+1))
                {
                    
                }
                    else
                    {
                        moveTo(getX(), getY()+1);
                        for(int i=getX();(getY()+3)<60 && i<getX()+4 ;i++)
                            getWorld()->dirtremove(i,getY()+3);
                    }
               }
                else
                {   setDirection(up);
                    moveTo(getX(),getY());
                }
            }
                break;
            case KEY_PRESS_DOWN:
            {if(getY()>0)
                {   if(getDirection()!=down)
                    setDirection(down);
                else if(getWorld()->isOverlapFrack(getX(), getY()-1))
                {
                    
                }
                else
                {
                    moveTo(getX(), getY()-1);
                    for(int i=getX();getY()<60 && i<getX()+4 ;i++)
                       getWorld()->dirtremove(i,getY());
                    
                }
                }
                else
                {   setDirection(down);
                    moveTo(getX(),getY());
                }
            }
                break;
            case KEY_PRESS_SPACE:
            {
                
                if(water==0)
                    {
                        break;
                    }
                
                Squirt* s;

                
                if(getDirection()==left)
                    {
                        if(!getWorld()->isDirtAt(getX()-4, getY()) && !getWorld()->isBoul3(getX()-4, getY()))
                        {
                            s= new Squirt(getX()-4, getY(), getDirection(), getWorld());
                            getWorld()->addActor(s);
                        }
                    }
                else if(getDirection()==down)
                {
                    if(!getWorld()->isDirtAt(getX(), getY()-4) && !getWorld()->isBoul3(getX(), getY()-4))
                    {
                        s=new Squirt(getX(), getY()-4, getDirection(), getWorld());
                        getWorld()->addActor(s);
                    }
                }
                else if(getDirection()==right)
                {
                    if(!getWorld()->isDirtAt(getX()+4, getY()) && !getWorld()->isBoul3(getX()+4, getY()))
                    {
                        s=new Squirt(getX()+4, getY(), getDirection(), getWorld());
                        getWorld()->addActor(s);

                    }
                }
                else
                {
                    if(!getWorld()->isDirtAt(getX(), getY()+4) && !getWorld()->isBoul3(getX(), getY()+4))
                    {
                        s=new Squirt(getX(), getY()+4, getDirection(), getWorld());
                        getWorld()->addActor(s);
                        
                    }
                }
                
                water--;
                
                
             
            }
                break;
                
                case 'z':
                case 'Z':
                    if(sonar==0)
                        break;
                    else
                    {
                        getWorld()->revealR12(getX(), getY());
                        sonar--;
                    }
                break;
                
                case KEY_PRESS_ESCAPE:
                {
                    setAlive(false);
                }
                
            case KEY_PRESS_TAB:
            {
                if(getGold()>0)
                    Gold* g=new Gold(getX(), getY(), getWorld(),1);
                
                
            }

                // etc…
        }
        
        
    }
    
    
}

FrackMan::~FrackMan()
{
    
}


//============================================================================================

Dirt::Dirt(int x, int y, StudentWorld* m_world):Actor(IID_DIRT, x, y, m_world, right, 0.25, 3)
{}

Dirt::~Dirt()
{
    
}
void Dirt::doSomething()
{
    
}


//============================================================================================

// 3 squares ....

Boulder::Boulder(int x, int y, StudentWorld* m_world): Actor(IID_BOULDER, x, y, m_world, down, 1.0, 1)
{
    stab=0;
    h=1;
    ctr=0;
}

Boulder::~Boulder()
{
    
}

void Boulder::doSomething()
{
    if(!isAlive())
        return;
    
    if(ctr < 30)
    {
        if(!getWorld()->isdirtbelow(getX(), getY()))
        {
            stab=1;
            ctr++;
        }
    }
    
    if(ctr==30)
    {
        if(stab==1)
            getWorld()->playSound(SOUND_FALLING_ROCK);
        stab=2;
        if(!(getWorld()->isdirtbelow(getX(), getY()))  && !(getWorld()->isboulder(getX(), getY()-4))&& getY()>-1)   //check later
        {
            moveTo(getX(), getY()-1);
        }
        else
        {
            setAlive(false);
                    }
    }
    
    if(stab==2)
    {
        if(getWorld()->isActorNearFrackN(getX(), getY(), 3))
            getWorld()->killFrack();
    }
}

//============================================================================================

Squirt::Squirt(int x, int y, Direction dir, StudentWorld* m_world): Actor(IID_WATER_SPURT, x, y, m_world, dir, 1.0, 1 )
{
    dist=0;
    
}

void Squirt::doSomething()
{
    //PART 1 spec
   
    if(!isAlive())
    {
        setVisible(false);
    }
    
    if(dist==4)
    {
        setAlive(false);
    }
    else
    {
        switch(getDirection())
        {
            case left:
            {
                if(getWorld()->isDirtAround(getX() - 1 , getY(), 1) && (getWorld()->isBoulderPath(getX() -1, getY(), 1)))
                {moveTo(getX() -1, getY());
                    dist++;
                    return;}
                else
                    setAlive(false);
            }
                break;
                
            case right:
            {
                if(getWorld()->isDirtAround(getX() + 4 , getY(), 1) && (getWorld()->isBoulderPath(getX() + 4 , getY(), 1)))
                {moveTo(getX() + 1, getY());
                    dist++;
                    return;}
                else
                    setAlive(false);
                
            }
                break;
                
            case up:
            {
                if(getWorld()->isDirtAround(getX() , getY() + 4, 2) && getWorld()->isBoulderPath(getX() , getY() + 4, 2))
                {moveTo(getX(), getY() + 1);
                    dist++;
                    return;}
                else
                    setAlive(false);
                
                
            }
                break;
                
            case none:
                break;
                
            case down:
            {
                if(getWorld()->isDirtAround(getX() , getY() -1, 2) && getWorld()->isBoulderPath(getX() , getY() -1 , 2))
                {moveTo(getX() , getY() - 1);
                    dist++;
                    return;}
                else
                    setAlive(false);
            }
                break;
        }
        
        
    }
    
    
   
    
    
}



Squirt::~Squirt()
{
    
}


//============================================================================================


WaterPool::WaterPool(int x, int y, StudentWorld* world) : Activators(IID_WATER_POOL, x, y, world)
{
    setVisible(true);
    m_wait = 0;
    m_maxTime = getWorld()->max(100, 300 - 10*getWorld()->getLevel());
}
WaterPool::~WaterPool()
{
    //
}
void WaterPool::doSomething()
{
    //1
    if (!isAlive())
        return;
    
    if(getWorld()->isActorNearFrackN(getX(), getY(),3))
       {
           setAlive(false);
           setVisible(false);
            getWorld()->playSound(SOUND_GOT_GOODIE);
           getWorld()->incPool(5);
           getWorld()->increaseScore(100);
           
       }
    
    
    
    m_wait++;
    if (m_wait == m_maxTime)
    {
        setAlive(false);
        setVisible(false);
    }
    
}

//============================================================================================


Barrel::Barrel(int x, int y, StudentWorld* world): Activators(IID_BARREL, x, y, world)
{
    setVisible(false);
}

Barrel::~Barrel()
{
    
}

void Barrel::doSomething()
{
    if(!isAlive())
        return;
    else if(!isVisible() && getWorld()->isActorNearFrackN(getX(), getY(), 4))
        setVisible(true);
    else if(getWorld()->isActorNearFrackN(getX(), getY(), 3))
    {
        setAlive(false);
        setVisible(false);
        getWorld()->playSound(SOUND_FOUND_OIL);
        getWorld()->reduceBarrel(getX(),getY());
        getWorld()->increaseScore(1000);
    }
    
    
        
    
}

//============================================================================================


Sonar::Sonar(int x, int y, StudentWorld* world): Activators(IID_SONAR, x, y, world)
{
    ctr=0;
    max= getWorld()->max(100, 300 - 10*getWorld()->getLevel());
}

Sonar::~Sonar()
{
    
}

void Sonar::doSomething()
{
    ctr++;
 if(!isAlive())
     return;

    if(getWorld()->isActorNearFrackN(getX(),getY(),3))
    {
        setAlive(false);
        setVisible(false);
        getWorld()->playSound(SOUND_GOT_GOODIE);
        getWorld()->incS(2);
        getWorld()->increaseScore(75);
    }
    
    if(ctr==max)
    {
        setAlive(false);
        setVisible(false);
    }
        
}

//============================================================================================

Gold::Gold(int x, int y, StudentWorld* world, int a): Activators(IID_GOLD, x, y, world)
{
    if(a!=1)
        setVisible(false);
}

Gold::~Gold()
{
    
}

void Gold:: doSomething()
{
    if(!isAlive())
        return;
    else if(!isVisible() && getWorld()->isActorNearFrackN(getX(), getY(), 4))
            {
                setVisible(true);
                return;
            }
    else if(isVisible() && getWorld()->isActorNearFrackN(getX(), getY(),3))
    {
        setAlive(false);
        setVisible(false);
        getWorld()->playSound(SOUND_GOT_GOODIE);
        getWorld()->incN(2);
        getWorld()->increaseScore(10);
        
    }
        
    
    
}

//===============================================================================================

Activators::Activators(int ID, int x, int y, StudentWorld* world):Actor(ID, x, y, world, right, 1.0, 2)
{
    
}

Activators::~Activators()
{
    setVisible(false);
}

//===============================================================================================

Agent::Agent(int ID, int x, int y, Direction dir, StudentWorld* world):Actor(ID, x, y, world, dir, 1.0, 0)
{
    
}

Agent::~Agent()
{
    
}



//===============================================================================================

Protester::Protester(int ID, StudentWorld* world):Agent( ID, 60, 60, left, world)
{
    if(ID==IID_PROTESTER)
        hit=5;
    else
        hit=20;
    
    state=0;
}

Protester::~Protester()
{
    
}
int Protester::getState()
{
    return state;
}

int Protester::hitP()
{
    return hit;
}
//===============================================================================================

RegularProtesters::RegularProtesters( int ID, StudentWorld* world):Protester(ID, world)
{
     numSq = getWorld()->randInt(8, 60);
     ticksToWaitBetweenMoves = getWorld()->max(0, 3 - getWorld()->getLevel()/4);
    curr=0; scream=0;
}

RegularProtesters::~RegularProtesters()
{
    
}

void RegularProtesters::doSomething()
{
    
    int x;
    if(getDirection()==left)
         x=0;
    else if(getDirection()==right)
         x=1;
    else if(getDirection()==up)
         x=2;
    else
         x=3;
    
    
    if(!isAlive())
        return;
    
    curr++;
    
    if(curr==ticksToWaitBetweenMoves)
    {
        if(getX()>=0 )
        moveTo(getX()-1, getY());
        curr=0;
       
        if(getState()==1)
        {
            if(getX()==60 && getY()==60)
            {
                setAlive(false);
                setVisible(false);
            }
            else if(getWorld()->isActorNearFrackN(getX(), getY(), 4) && getWorld()->isFacing(getX(), getY(), x))
            {
                if(scream >= 15)
                {
                    getWorld()->playSound(SOUND_PROTESTER_YELL);
                    scream=0;
                    getWorld()->decHealth();
                }
                
            }
        }
    }
    
    
    
}

//===============================================================================================

HardCoreProtesters::HardCoreProtesters(int ID, StudentWorld* world):Protester(ID, world)
{
    ticksToWaitBetweenMoves = getWorld()->max(0, 3 - getWorld()->getLevel()/4);
    curr=0;
}

HardCoreProtesters::~HardCoreProtesters()
{
    
}

void HardCoreProtesters::doSomething()
{
    if(!isAlive())
        return;
    
    curr++;
    
    if(curr==ticksToWaitBetweenMoves)
    {
        if(getX()>=0 )
            moveTo(getX()-1, getY());
        curr=0;
        
    }
}