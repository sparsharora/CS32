//
//  Map.cpp
//  P2
//
//  Created by Sparsh Arora on 1/19/16.
//  Copyright © 2016 Sparsh Arora. All rights reserved.
//

#include "Map.h"


Map::Map()
{
    n=0;
    
}

bool Map::empty() const
{ if(n==0)
    return true;
return false;
}

int Map::size() const
{ return n;
}


bool Map::insert(const KeyType& key, const ValueType& value)
{ int i;
    if(size()==DEFAULT_MAX_ITEMS)
        return false;
    
    for(i=0;i<n;i++)
        if(mem[i].Key==key)
            return false;
    
    mem[i].Key=key;
    mem[i].Value=value;
    n++;
    return true;
}

bool Map::update(const KeyType& key, const ValueType& value)
{      for(int i=0;i<size();i++)
    if(mem[i].Key==key)
    {   mem[i].Value=value;
        return true;
    }
    return false;
}

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value)
{int i;
    for(i=0;i<size();i++)
        if(mem[i].Key==key)
        {   mem[i].Value=value;
            return true;
        }
    
    if(size()==DEFAULT_MAX_ITEMS)
        return false;
    else
    {
        mem[i].Key=key;
        mem[i].Value=value;
        n++;
        return true;
    }
    return false;
}


bool Map::erase(const KeyType& key)
{
    for(int i=0;i<n;i++)
        if(mem[i].Key==key)
        {   for(;i<size();i++)
        {mem[i].Key=mem[i+1].Key;
            mem[i].Value=mem[i+1].Value;
        }
            n--;
        } return true;
    return false;
}

bool Map::contains(const KeyType& key) const
{
    for(int i=0;i<n;i++)
        if(mem[i].Key==key)
        {
            return true;
        }
    
    return false;
}

bool Map::get(const KeyType& key, ValueType& value) const
{
    for(int i=0;i<n;i++)
        if(mem[i].Key==key)
        {   value=mem[i].Value;
            return true;
        }
    return false;
}

bool Map::get(int i, KeyType& key, ValueType& value) const
{  if(i<0 || i>=n)
    return false;
    
    
    key=mem[i].Key;
    value=mem[i].Value;
    
    return true;
}

void Map::swap(Map& other)                       
{ ValueType t2; KeyType t1; int t=0,i=0;
    for(; i<this->n && i<other.n;i++)
    {   t2=this->mem[i].Value;
        this->mem[i].Value=other.mem[i].Value;
        other.mem[i].Value=t2;
        
        t1=this->mem[i].Key;
        this->mem[i].Key=other.mem[i].Key;
        other.mem[i].Key=t1;
    }
    
    
    if(i==this->n)
        while(i<other.n)
        {this->mem[i].Key=other.mem[i].Key;
        this->mem[i].Value=other.mem[i].Value;
            i++;
        }
    else if(i==other.n)
        while(i<this->n)
        {other.mem[i].Key=this->mem[i].Key;
        other.mem[i].Value=this->mem[i].Value;
            i++;
        }
    
    t=this->n;
    this->n=other.n;
    other.n=t;
}

