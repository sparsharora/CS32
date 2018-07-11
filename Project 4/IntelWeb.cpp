//
//  IntelWeb.cpp
//  temp
//
//  Created by Sparsh Arora on 3/9/16.
//  Copyright © 2016 Sparsh Arora. All rights reserved.
//

#include "IntelWeb.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

//=================HELPERS=======================

bool IsPresent(string str, set<string> s)
{
    if(s.count(str)>0)
    {
        return true;
    }
    return false;
}

bool operator==(InteractionTuple a, InteractionTuple b)
{
    if (a.to==b.to && a.from==b.from && a.context==b.context)
    {
        return true;
    }
    return false;
}

bool compareTup(InteractionTuple a, InteractionTuple b)
{
    if (a.context<b.context)
    {
        return true;
    }
    else if(a.context==b.context)
    {
        if(a.from<b.from)
        {
            return true;
        }
        else if(a.from==b.from)
        {
            if(a.to<b.to)
            {
                return true;
            }
        }
    }
    return false;
}


//==============================CLASS FUNCTIONs===========================


bool IntelWeb::createNew(const std::string& filePrefix, unsigned int maxDataItems)
{
    close();
    if(!map1.createNew(filePrefix + "_map1.dat", maxDataItems/0.75))
        return false;
    if(!map2.createNew(filePrefix + "_map2.dat", maxDataItems/0.75))
        return false;
    
    return true;
}

bool IntelWeb::openExisting(const std::string& filePrefix)
{
    close();
    if(!map1.openExisting(filePrefix + "_map1.dat"))
        return false;
    if(!map2.openExisting(filePrefix + "_map2.dat"))
        return false;
    
    return true;
}

void IntelWeb::close()
{
    map1.close();
    map2.close();
    
}

bool IntelWeb::ingest(const std::string& telemetryFile)
{
    ifstream tele(telemetryFile);
        if(!tele)
            return false;
    string sentence;
    char tester;
    
    while(getline(tele,sentence))
    {
        istringstream iss(sentence);
        string k, v, c;
        iss >> k >> v >> c;
        
        if(iss>>tester);
        
        if(!map1.insert(v, c, k))
            return false;
        if(!map2.insert(c, v, k))
            return false;
        
    }
    
    return true;
}



bool IntelWeb::purge(const std::string& entity)
{
    int ctr=0;
    
    DiskMultiMap::Iterator i1=map1.search(entity);
    DiskMultiMap::Iterator i2=map2.search(entity);
    
    while(i1.isValid())
    {
        MultiMapTuple mmt= *i1;
        ++i1;
        map1.erase(mmt.key, mmt.value, mmt.context);
        map2.erase(mmt.value, mmt.key, mmt.context);
        
        ctr++;
        
    }
    while(i2.isValid())
    {
        MultiMapTuple mmt= *i2;
        ++i2;
        map1.erase(mmt.key, mmt.value, mmt.context);
        map2.erase(mmt.value, mmt.key, mmt.context);
        
        ctr++;
        
    }
    
    return ctr>0;
}

unsigned int IntelWeb::crawl(const std::vector<std::string>& indicators, unsigned int minPrevalenceToBeGood, std::vector<std::string>& badEntitiesFound, std::vector<InteractionTuple>& badInteractions)
{
    int nmal=0;
    int count=0;
    badEntitiesFound.clear();
    InteractionTuple tuple;
    vector<string> N_indicators=indicators;
    DiskMultiMap::Iterator it, i1, i2;
    
    set<string> maliciousVal;
    set<string> prevb;
    
    
    for (int i=0; i<N_indicators.size(); i++)
       {
       
        it=map1.search(N_indicators[i]);
        
        if (it.isValid() && !IsPresent(N_indicators[i], maliciousVal))
        {
            nmal++;
            maliciousVal.insert(N_indicators[i]);
            badEntitiesFound.push_back(N_indicators[i]);
        }
        
        while(it.isValid())
        {
            MultiMapTuple m=*it;
            tuple.from=m.key;
            tuple.to=m.value;
            tuple.context=m.context;
            
            if (!IsPresent(tuple.to, maliciousVal))
               {
                   count=0;
                   i1=map2.search(tuple.to);
                   while (i1.isValid())
                   {
                        count++;
                        ++i1;
                   }
                i1=map1.search(tuple.to);
                
                while (i1.isValid())
                {
                    count++;
                    ++i1;
                }
                
                if (count<minPrevalenceToBeGood)
                {
                    prevb.insert(tuple.to);
                    nmal++;
                    maliciousVal.insert(tuple.to);
                    N_indicators.push_back(tuple.to);
                    badEntitiesFound.push_back(tuple.to);
                }
            }
            badInteractions.push_back(tuple);
            ++it;
        }
        
       
        i2=map2.search(N_indicators[i]);
        
        if (i2.isValid() && !IsPresent(N_indicators[i], maliciousVal))
            {
                nmal++;
                maliciousVal.insert(N_indicators[i]);
                badEntitiesFound.push_back(N_indicators[i]);
            }
        
        while (i2.isValid())
        {
            MultiMapTuple M=*i2;
            tuple.from=M.value;
            tuple.to=M.key;
            tuple.context=M.context;
            if (!IsPresent(tuple.from, maliciousVal))
            {
                count=0;
                i1=map2.search(tuple.from);
                while (i1.isValid())
                {
                    count++;
                    ++i1;
                }
                i1=map1.search(tuple.from);
                
                while (i1.isValid())
                {
                    count++;
                    ++i1;
                }
                
                if (count<minPrevalenceToBeGood)
                {
                    nmal++;
                    maliciousVal.insert(tuple.from);
                    N_indicators.push_back(tuple.from);
                    badEntitiesFound.push_back(tuple.from);
                }
                
            }
            badInteractions.push_back(tuple);
            ++i2;
        }
        
        
    }
    
    
    
    sort( badInteractions.begin(), badInteractions.end(), compareTup);
    sort(badEntitiesFound.begin(), badEntitiesFound.end());
    badInteractions.erase( unique( badInteractions.begin(), badInteractions.end() ), badInteractions.end() );
    
    
    return nmal;
}

IntelWeb::IntelWeb()
{
    
}

IntelWeb::~IntelWeb()
{
    close();
}
