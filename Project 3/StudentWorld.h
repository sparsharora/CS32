#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include <string>
#include "Actor.h"
#include <cstdlib>
#include <vector>
#include <cmath>
#include <sstream>
#include <iomanip>
#include <random>
using namespace std;


// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
 
    
public:
    
	StudentWorld(std::string assetDir)
	 : GameWorld(assetDir)
	{
        prot=0;
	}
    
	virtual int init()
	{
        f= new FrackMan(this);
        
        
        for(int i=0; i < 64 ; i++)
            for(int j=0 ; j<60 ; j++)
            {
                if(i<34 && i>29 && j>3 && j<60)
                    d[i][j]=nullptr;
                else
                    d[i][j]=new Dirt(i,j, this);
            }
        for(int i=0; i < 64 ; i++)
            for(int j=60 ; j<64 ; j++)
                d[i][j]=nullptr;
        
        

        B = min((getLevel()/2) +2, 6);
        
        for(int l=0; l < B ; l++)
        {
            int x=randInt(0, 60);
            int y=randInt(20, 56);
           
            Boulder* b=new Boulder(x, y, this);
            
            if(isboulder(x, y)|| (x>26 && x<34)|| isActor6near(b))
            {
                
                delete b;
                B++;
                continue;
            }
            
            acts.push_back(b);
            
            for(int i=x; i<64 && i<x+4; i++)
                for(int j=y; j<60 && j<y+4; j++)
                {
                    delete d[i][j];
                    d[i][j]=nullptr;
                    
                }
        }

        
        OB = min(2+getLevel(), 20);
        for(int l=0; l < OB ; l++)
        {
            int x=randInt(0, 60);
            int y=randInt(20, 56);
            
            Barrel* b=new Barrel(x, y, this);
            
            if((x>26 && x<34)|| isActor6near(b))
            {
                
                delete b;
                OB++;
                continue;
            }
            
            acts.push_back(b);
            
        }
        
        nugget = max(5-getLevel()/2, 2);
        for(int l=0; l < nugget ; l++)
        {
            int x=randInt(0, 60);
            int y=randInt(0, 56);
            
            Gold* g=new Gold(x, y, this, 0);
            
            if((x>26 && x<34)|| isActor6near(g))
            {
                
                delete g;
                nugget++;
                continue;
            }
            
            acts.push_back(g);
            
        }

        Protester *q;
        int probabilityOfHardcore = min(90, getLevel() * 10 + 30);
        int rand= randInt(1, 100);


        if(rand<=probabilityOfHardcore)
            q= new HardCoreProtesters(IID_HARD_CORE_PROTESTER, this);
        else
            q= new RegularProtesters(IID_PROTESTER,this);
        
        acts.push_back(q);
    

        
        return GWSTATUS_CONTINUE_GAME;

    }

	virtual int move()
	{
      
        DisplayStat();
        
        f->doSomething();
        
        if(!f->isAlive())
        {
            f->setVisible(false);
            
            decLives();
            return GWSTATUS_PLAYER_DIED;
        }
        
        for(int i=0; i<acts.size(); i++) 
        {
            if(f->getBarrels()==0)
            {
                playSound(SOUND_FINISHED_LEVEL);
                return GWSTATUS_FINISHED_LEVEL;
            }
            
            if(acts[i]->isAlive())
                acts[i]->doSomething();
        }
  
        int G = getLevel() * 25 + 300;
        int randAdd = randInt(1, G);
        if (randAdd == G)
        {
            int randGoodie = randInt(1, 5);
            if (randGoodie == 1)
            {
                acts.push_back(new Sonar(0, 60, this));
            }
            else
            {
                start:
                int randX = randInt(0, 60);
                int randY = randInt(0, 60);
                
                
                for(int i=randX ; i<randX+4; i++)
                {
                    
                    for(int j=randY; j<randY+4 ; j++)
                    {
                       
                        if(d[i][j]!=nullptr)
                        {
                            goto start;
                        }
                        
                    }
                }
                
            
                acts.push_back(new WaterPool(randX, randY, this));

            }
        }
        
        
        Protester *p;
        int T = max(25, 200-getLevel());
        int P = min(15, 2 + getLevel() * 1.5);
        int probabilityOfHardcore = min(90, getLevel() * 10 + 30);
        
        prot++;
        
        if(prot==T && currProt()<P )
        {
            int rand1= randInt(1, 100);
            if(rand1<=probabilityOfHardcore)
                 p= new HardCoreProtesters(IID_HARD_CORE_PROTESTER, this);
            else
                 p= new RegularProtesters(IID_PROTESTER,this);
            
            acts.push_back(p);
            prot=0;

        }
        
        
        for(int i=0; acts.size()>0 &&  i<acts.size() ; i++)
        {
            if (acts[i]->getID()==IID_BOULDER && !acts[i]->isAlive())
            {
                acts[i]->setVisible(false);
                acts.erase(acts.begin()+i);
            }
        }
        
        for(int i=0; acts.size()>0 &&  i<acts.size() ; i++)
        {
            if (acts[i]->getID()==IID_BARREL && !acts[i]->isAlive())
            {
                acts[i]->setVisible(false);
                acts.erase(acts.begin()+i);
            }
        }
        
        for(int i=0; acts.size()>0 &&  i<acts.size() ; i++)
        {
            if (acts[i]->getID()==IID_SONAR && !acts[i]->isAlive())
            {
                acts[i]->setVisible(false);
                acts.erase(acts.begin()+i);
            }
        }
        
        for(int i=0; acts.size()>0 &&  i<acts.size() ; i++)
        {
            if (acts[i]->getID()==IID_GOLD && !acts[i]->isAlive())
            {
                acts[i]->setVisible(false);
                acts.erase(acts.begin()+i);
            }
        }
        
        for(int i=0; acts.size()>0 &&  i<acts.size() ; i++)
        {
            if (acts[i]->getID()==IID_WATER_POOL && !acts[i]->isAlive())
            {
                acts[i]->setVisible(false);
                acts.erase(acts.begin()+i);
            }
        }
        
        for(int i=0; acts.size()>0 &&  i<acts.size() ; i++)
        {
            if (acts[i]->getID()==IID_WATER_SPURT && !acts[i]->isAlive())
            {
                acts[i]->setVisible(false);
                acts.erase(acts.begin()+i);
            }
        }
        
        
        
        
            
        
        
        
        // This code is here merely to allow the game to build, run, and terminate after you hit enter a few times.
		  // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
		//decLives();
		return GWSTATUS_CONTINUE_GAME;
        
        
	}

	virtual void cleanUp()
	{
        delete f;
        
        
        for(int i=0; i<64 ; i++ )
            for(int j=0; j <60 ; j++)
                delete d[i][j];
        
        for(int i=0; i <acts.size(); i++)
            delete acts[i];
        acts.clear();
        
    }
    
   
    int currProt()
    {
        int ctr=0;
        for(int i=0; i < acts.size() ; i++)
        {
            if(acts[i]->getID()==IID_HARD_CORE_PROTESTER || acts[i]->getID()==IID_PROTESTER)
                ctr++;
        }
        
        return ctr;
    }
    
    int randInt(int min, int max)
    {
        if (max < min)
            swap(max, min);
        static random_device rd;
        static mt19937 generator(rd());
        uniform_int_distribution<> distro(min, max);
        return distro(generator);
    }
    
    void DisplayStat()
    {
        int score = getScore();
        int level = getLevel();
        int lives = getLives();
        int health = f->getHealth();
        int squirts = f->getWater();
        int gold = f->getGold();
        int sonar = f->getSonar();
        int barrelsLeft = f->getBarrels();
        string s = formatString(score, level, lives, health, squirts, gold, sonar, barrelsLeft);
        setGameStatText(s);
    }
    
    
    
    string formatString(int score, int level, int lives, int health, int squirts, int gold, int sonar, int barrels)
    {
        ostringstream oss;
        oss.fill('0');
        oss<<"  Scr: "<< setw(6) << score<<"  ";
         oss.fill(' ');
        oss<<"Lvl: "<<setw(2)<<level<<"  ";
         oss.fill(' ');
        oss<<"Lives: "<<setw(1)<<lives<<"  ";
         oss.fill(' ');
        oss<<"Hlth: "<<setw(3)<<health<<"%"<<"  ";
         oss.fill(' ');
        oss<<"Wtr: "<<setw(2)<<squirts<<"  ";
         oss.fill(' ');
        oss<<"Gld: "<<setw(2)<<gold<<"  ";
         oss.fill(' ');
        oss<<"Sonar: "<<setw(2)<<sonar<<"  ";
         oss.fill(' ');
        oss<<"Oil Left: "<<setw(2)<<barrels<<"  ";
        
        return oss.str();
        
    }
    
    void incPool(int x)
    {
        f->increaseWater(x);
    }
   
    void incN(int x)
    {
        f->increaseNugget(x);
    }
    void incS(int x)
    {
        f->incS(x);
    }
    
    void dirtremove(int x, int y)
    {
        if(d[x][y]!=nullptr)
            playSound(SOUND_DIG);
        
        delete d[x][y];
        d[x][y]=nullptr;
    }
    
    virtual ~StudentWorld()
    {
        delete f;
        
        for(int i=0; i<64 ; i++ )
            for(int j=0; j <60 ; j++)
                delete d[i][j];
    }
    
    int min(int x, int y)
    {
        if(x<y)
            return x;
        else
            return y;
    }
    int max(int x, int y)
    {
        if(x<y)
            return y;
        else
            return x;
    }
    
    void addActor(Actor* a)
    {
        acts.push_back(a);
    }
    
    bool isFacing(int x, int y, int n)
    {
        if(n==0)
            if(f->getX()<x)
                return true;
        if(n==1)
            if(f->getX()>x )
                return true;
        if(n==2)
            if( f->getY()>y)
                return true;
        if(n==3)
            if( f->getY()<y)
                return true;
        
        return false;
    }
    
    bool isdirtbelow(int x, int y)
    {
        for(int i=x; i<61 && y-1 >= 0 && i < x+4 ; i++ )
            if(d[i][y-1]!=nullptr)
                    return true;
        
        return false;
    }
    
    bool isboulder(int x, int y)
    {
        for(int i=0; acts.size()>0 &&  i<acts.size() ; i++)  
        {
            if(acts[i]->getX()==x && acts[i]->getY()==y && acts[i]->getID()==IID_BOULDER)
                return true;
        }
        return false;
    }
    
    
        bool isOverlapFrack(int x, int y)
    {
        if(acts.size()==0)
            return false;
        for(int i=0; i<acts.size() && acts[i]->getID()==IID_BOULDER ; i++)
        {
            if(pow(pow(acts[i]->getY() - y, 2) + pow(acts[i]->getX() - x, 2),0.5) <= 3)
                return true;
        }
        return false;
    }
    
    bool isActor6near(Actor* a)
    {
        if(acts.size()==0)
            return false;
        for(int i=0; i<acts.size() ; i++)
        {
            if(pow(pow(acts[i]->getY() - a->getY(), 2) + pow(acts[i]->getX() - a->getX(), 2), 0.5)<=6)
                return true;
        }
        return false;
    }
    
      

    
    bool isBoul3( int x, int y)
    {
        if(acts.size()==0)
            return false;
        for(int i=0; i<acts.size() && acts[i]->getID()==IID_BOULDER ; i++)
        {
            if(pow(pow(acts[i]->getY() - y, 2) + pow(acts[i]->getX() - x, 2), 0.5) <= 3)
                return true;
        }
        return false;
    }
    
    
    bool isActorNearFrackN(int x, int y, int n)
    {
        
        if(pow(pow(f->getY() - y, 2) + pow(f->getX() - x, 2), 0.5) <= n)
            return true;
        
        return false;
    }
    
    
    void revealR12( int x, int y)
    {
        if(acts.size()==0)
            return;
        for(int i=0; i<acts.size() ; i++)
        {
            if(pow(pow(acts[i]->getY() - y, 2) + pow(acts[i]->getX() - x, 2), 0.5) <= 12)
            {
                acts[i]->setVisible(true);
            }
        }
    
    }
    
    void reduceBarrel(int x, int y)
    {
        f->reduceB();
    }
    
    void deleteSq(int x, int y)
    {
        for(int i=0; i < acts.size(); i++)
            if(acts[i]->getX()==x && acts[i]->getY()==y && acts[i]->getID()==IID_WATER_SPURT)
                acts.erase(acts.begin()+i);
    }
    
       
    bool isDirtAround(int x, int y, int n)
    {
        if(n==1)                    
        {
            for(int i = y; i < y + 4; i++)
            {
                if(d[x][i]!=nullptr)
                    return false;
            }
        }
        
        if(n==2)
        {
            for(int i = x; i < x + 4; i++)
            {
                if(d[i][y]!=nullptr)
                    return false;
            }
        }
        
        
        
        
        return true;
    }
    
    bool isBoulderPath(int x, int y, int n)
    {
        
        for(int i=0; i < acts.size(); i++)
        {
            if(acts[i]->getID()==IID_BOULDER)
            {
                if(n==1)                        //n=1 means that direction is either left or right
                {
                    for(int j = y; j < y + 4; j++)
                    {
                        if(isBoulderAround(x, j, nullptr))
                            return false;
                    }
                }
                if(n==2)                    //n=2 means that direction is either up or down
                {
                    for(int j = x; j < x + 4; j++)
                    {
                        if(isBoulderAround(j, y, nullptr))
                            return false;
                    }
                }
            }
        }
        
        
        return true;
    }
    
    bool isBoulderAround(int x, int y, Actor* a)
    {
        int z = 0,v = 0;
        
        for(int i=0; i < acts.size() ; i++)
        {
            if(acts[i]==a)
                continue;
            
            if(acts[i]->getID()==IID_BOULDER)              {
                z=acts[i]->getX();
                v=acts[i]->getY();
            }
            
            
            for(int k = z; k < z + 4; k++)
                for(int l = v; l < v+4; l++)
                {
                    if(k==x && l==y)
                        return true;
                }
            
        }
        
        return false;
    }
    
    bool isDirtAt(int x, int y)
    {
            if(d[x][y]!=nullptr)
            {
                return true;
            }
        
        return false;
            
    }
    
    bool isFrackAboveDirt(int x, int y)
    {
        for(int i=x-3; i < x+4 ; i++)
        {
            if(f->getX()==i && f->getY()==y+4)
                return true;
        }
        
        return false;
    }
    
    void decHealth()
    {
        f->decHealth(20);
    }
    
    void killFrack()
    {
        f->setAlive(false);
    }
    
 

private:
    
    Dirt* d[64][64];
    FrackMan* f;
    vector<Actor*> acts;
    int B;
    int OB;
    int nugget;
    int prot;
};


#endif // STUDENTWORLD_H_
