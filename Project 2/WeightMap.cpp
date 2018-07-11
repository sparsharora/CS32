//
//  WeightMap.cpp
//  P2
//
//  Created by Sparsh Arora on 1/19/16.
//  Copyright © 2016 Sparsh Arora. All rights reserved.
//

#include "WeightMap.h"

WeightMap::WeightMap()
{  m=0;
}

bool WeightMap::enroll(std::string name, double startWeight)
{  if(!m1.contains(name) && m!=DEFAULT_MAX_ITEMS && startWeight>=0)
        {   m1.insert(name,startWeight);
            m++;
            return true;
        }
    return false;
}

double WeightMap::weight(std::string name) const
{ ValueType v;
    if(m1.get(name,v))
        return v;
    return -1;
}

bool WeightMap::adjustWeight(std::string name, double amt)
{ValueType v;
    if(!m1.contains(name) || (amt+weight(name))<0)
        return false;
    if(m1.get(name, v))
        { v+=amt;
            m1.update(name, v);
        }
    return true;
    
}

int WeightMap::size() const
{
    return m;
}

void WeightMap::print() const
{   ValueType v; KeyType k;
    
    for(int i=0;i<m;i++)
    {   m1.get(i,k,v);
        cout<<k<<" "<<v<<endl;
    }
}
