//
//  newMap.cpp
//  P2
//
//  Created by Sparsh Arora on 1/19/16.
//  Copyright © 2016 Sparsh Arora. All rights reserved.
//

//
//  Map.cpp
//  P2
//
//  Created by Sparsh Arora on 1/19/16.
//  Copyright © 2016 Sparsh Arora. All rights reserved.
//

#include "newMap.h"


Map::Map(int total)
{   ptr=new arr[total];
    n=0;
    t=total;
}

Map::Map()
{   ptr=new arr[DEFAULT_MAX_ITEMS];
    n=0;
    t=DEFAULT_MAX_ITEMS;
}
Map::~Map()
{delete [] ptr;
}

Map::Map(const Map &old)
{
    t = old.t;
    ptr = new arr[t];
    for (int i = 0; i < old.t; i++)
        ptr[i] = old.ptr[i];
    
}

Map& Map::operator=(const Map &src)
{
    if (&src == this)
        return (*this);
    delete [] ptr;
    this->n = src.n;
    t = src.t;
    ptr = new arr[t];
    for (int i = 0; i < n; i++)
        ptr[i] = src.ptr[i];
    return (*this);
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
    if(size()==t)
        return false;
    else
    for(i=0;i<n;i++)
        if(ptr[i].Key==key)
            return false;
    
    
    
    ptr[i].Key=key;
    ptr[i].Value=value;
    n++;
    return true;
     
}

bool Map::update(const KeyType& key, const ValueType& value)
{      for(int i=0;i<n;i++)
    if(ptr[i].Key==key)
    {   ptr[i].Value=value;
        return true;
    }
    return false;
}

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value)
{int i;
    for(i=0;i<n;i++)
        if(ptr[i].Key==key)
        {   ptr[i].Value=value;
            return true;
        }
    
    if(size()==t)
        return false;
    else
    {
        ptr[i].Key=key;
        ptr[i].Value=value;
        n++;
        return true;
    }
    return false;
}


bool Map::erase(const KeyType& key)
{
    for(int i=0;i<n;i++)
        if(ptr[i].Key==key)
        {   for(;i<size();i++)
        {ptr[i].Key=ptr[i+1].Key;
            ptr[i].Value=ptr[i+1].Value;
        }
            n--;
        } return true;
    return false;
}

bool Map::contains(const KeyType& key) const
{
    for(int i=0;i<n;i++)
        if(ptr[i].Key==key)
        {
            return true;
        }
    
    return false;
}

bool Map::get(const KeyType& key, ValueType& value) const
{
    for(int i=0;i<n;i++)
        if(ptr[i].Key==key)
        {   value=ptr[i].Value;
            return true;
        }
    return false;
}

bool Map::get(int i, KeyType& key, ValueType& value) const
{  if(i<0 || i>=n)
    return false;
    
    
    key=ptr[i].Key;
    value=ptr[i].Value;
    
    return true;
}

void Map::swap(Map& other)
{   
    
    Map temp(*this);
    this->operator=(other);
    other.operator=(temp);
    
}



