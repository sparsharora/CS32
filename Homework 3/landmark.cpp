//
//  main.cpp
//  hw3
//
//  Created by Sparsh Arora on 2/9/16.
//  Copyright © 2016 Sparsh Arora. All rights reserved.
//


//Your declarations and implementations would go here
class Landmark
{
public:
    Landmark(string name)
    {
        n=name;
    }
    virtual string icon() const=0;
    virtual string color() const
    {
        return "yellow";
    }
    string name() const
    {
        return n;
    }
    virtual ~Landmark()
    {
        cout<<n<<"."<<endl;
    }
    
private:
    string n;
};

class Restaurant: public Landmark
{
public:
    Restaurant(string name, int cap):Landmark(name)
    {
        if(cap<40)
            ir="small knife/fork";
        else
            ir="large knife/fork";
        
    }
    virtual string icon() const
    {
        return ir;
    }
    virtual ~Restaurant()
    {
        cout<<"Destroying the restaurant ";
    }
    
private:
    string ir;
    
};

class Hotel: public Landmark
{
public:
    Hotel(string name):Landmark(name){ih="bed";}
    virtual string icon() const
    {
        return ih;
    }
    virtual ~Hotel()
    {
        cout<<"Destroying the hotel ";
    }
private:

    string ih;
    
};

class Hospital: public Landmark
{
public:
    Hospital(string name): Landmark(name)
    {
        ihl="H";
        chl="blue";
    }
    virtual string icon() const
    {
        return ihl;
    }
    virtual string color() const
    {
        return chl;
    }
    virtual ~Hospital()
    {
        cout<<"Destroying the hospital ";
    }
private:
    
    string ihl;
    string chl;

};

