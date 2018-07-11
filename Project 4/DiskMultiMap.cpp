//
//  DiskMultiMap.cpp
//  temp
//
//  Created by Sparsh Arora on 3/10/16.
//  Copyright © 2016 Sparsh Arora. All rights reserved.
//

#include "DiskMultiMap.h"



using namespace std;

DiskMultiMap::DiskMultiMap()
{}

DiskMultiMap::~DiskMultiMap()
{
    close();
}


DiskMultiMap::Iterator::Iterator()
{
    m_valid=false;
}

DiskMultiMap::Iterator::Iterator(bool valid, BinaryFile::Offset place, DiskMultiMap* dmp)
{
    m_valid=valid;
    add=place;
    m_ptr=dmp;
    
    
}


bool DiskMultiMap::Iterator::isValid() const
{
    return m_valid;
}

DiskMultiMap::Iterator& DiskMultiMap::Iterator::operator++()
{
    node n;
    m_ptr->bf.read(n, add);
    string k;
    k=n.key;
   /*
    if(n.next!=0)
    {
        m_valid=false;
        return *this;
    
    }
    add=n.next;
    m_ptr->bf.read(n, n.next);
    return *this;
    */

    
    while(isValid())
    {
        if(n.next!=0)
        {
            add=n.next;
            m_ptr->bf.read(n, n.next);
        }
        else
        {
            m_valid=false;
        }
        if (m_valid && strcmp(n.key, k.c_str()) == 0) // if you find matching key
            return *this;
        
    }
    return *this;
    
}

MultiMapTuple DiskMultiMap::Iterator::operator*()
{
    MultiMapTuple mmt;
    if(!isValid())
        return mmt;
    node keep;
    m_ptr->bf.read(keep, add);
    
    mmt.key=keep.key;
    mmt.value=keep.value;
    mmt.context=keep.context;
    
    return mmt;
    
}

bool DiskMultiMap::createNew(const std::string& filename, unsigned int numBuckets)
{
    if(!bf.createNew(filename))
        return false;
    cerr<<"creating file"<<endl;
    h.num=numBuckets;
    h.firstdeleted=-1;
    BinaryFile::Offset off=0;
    FirstDeleted=0;
    
    bf.write(h, off);
    off+=sizeof(Header);
    cerr<<"offset after header: "<<off<<endl;
    
    StartTable=off;
    node empty;
    strcpy(empty.value, "");
    strcpy(empty.context, "");
    strcpy(empty.key, "");
    
    
    for(int i=0; i<numBuckets; i++)
    {
        
        BinaryFile::Offset insertAt= StartTable + (i*sizeof(node));
        
        
        empty.curr=insertAt;
        empty.next=0;
        
        bf.write(empty, insertAt);
        
    }
    cerr<<endl;
    bf.close();
    bf.openExisting(filename);
    return true;
}
bool DiskMultiMap::openExisting(const std::string& filename)
{
    if(bf.isOpen())
        bf.close();
    if(!bf.openExisting(filename))
        return false;
    BinaryFile::Offset it=0;
    Header newh;
    bf.read(newh, it);
    h=newh;
    it+=sizeof(Header);
    StartTable=it;
    return true;
    
}

void DiskMultiMap::close()
{
    if(bf.isOpen())
        bf.close();
}

bool DiskMultiMap::insert(const std::string& key, const std::string& value, const std::string& context)
{
    if(strlen(key.c_str())>=121 || strlen(value.c_str())>=121 || strlen(context.c_str())>=121 )
        return false;
    BinaryFile::Offset index=hash(key.c_str(), h.num);
    
    index+=StartTable;
    cerr<<"Index: "<<index<<endl;

    node temp;
    int test;
    if(!bf.read(test, index))
        return false;
    
    if(!bf.read(temp, index))
        return false;
    temp.curr=index;
    if(test!=0)
    {
        temp.next=0;
    }
    
    while(temp.next!=0)
    {
        temp.curr=temp.next;
        bf.read(temp, temp.next);
    }
    cerr<<"Located at: "<<temp.curr<<endl;
    
    if(FirstDeleted!=0)
    {
        node first;
        bf.read(first, FirstDeleted);
        FirstDeleted=first.next;
        
        temp.next = first.curr;
        node newnode;
        strcpy(newnode.key, key.c_str());
        strcpy(newnode.value, value.c_str());
        strcpy(newnode.context, context.c_str());
        
        newnode.curr = first.curr;
        newnode.next = 0;
        if(!bf.write(newnode, newnode.curr))
            return false;
        
    }
    else
    {
        node newnode;
        strcpy(newnode.key, key.c_str());
        strcpy(newnode.value, value.c_str());
        strcpy(newnode.context, context.c_str());
        newnode.curr=bf.fileLength();
        newnode.next=0;
        
        temp.next=newnode.curr;
        bf.write(temp, temp.curr);
        if(!bf.write(newnode, bf.fileLength()))
            return false;
        
        
    }
    
    return true;
    
    
    
}

DiskMultiMap::Iterator DiskMultiMap::search(const std::string& key)
{
    BinaryFile::Offset it=hash(key, h.num);
    it+=StartTable;
    node n;
    n.curr=it;
    bf.read(n, it);
    
    
    while(n.next!=0)
    {
        BinaryFile::Offset curr=n.next;
        n.curr=n.next;
        bf.read(n, n.next);
        
        if(strcmp(key.c_str(), n.key)==0)
        {
            Iterator itr(true, curr, this);
            return itr;
        }
    }
    
    Iterator itr;
    return itr;
    
}
int DiskMultiMap::erase(const std::string& key, const std::string& value, const std::string& context)
{
    int ctr=0;
    BinaryFile::Offset index;
    index=hash(key, h.num);
    index+=StartTable;
    node temp, front;
    bf.read(temp, index);
    temp.curr=index;
    bf.read(front, temp.next);
    while (front.curr!=0)
    {
        
        if(strcmp(front.key,key.c_str())==0  && strcmp(front.value, value.c_str())==0 && strcmp(front.context, context.c_str())==0)
        {
            
            temp.next=front.next;
            bf.write(temp, temp.curr);
            addToHDelete(front.curr);
            ctr++;
            
        }
   
        
        front.curr=front.next;
        bf.read(front, front.next);
    }
    
   
   
    return ctr;
}

