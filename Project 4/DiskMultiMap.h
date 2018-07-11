//
//  DiskFile.cpp
//  temp
//
//  Created by Sparsh Arora on 3/7/16.
//  Copyright © 2016 Sparsh Arora. All rights reserved.
//

#ifndef DISKMULTIMAP_H_
#define DISKMULTIMAP_H_

#include <cstring>
#include <string>
#include "MultiMapTuple.h"
#include "BinaryFile.h"
#include <functional>




class DiskMultiMap
{
public:
    
    class Iterator
    {
    public:
        Iterator();
        Iterator(bool valid, BinaryFile::Offset place, DiskMultiMap* dmp);
        // You may add additional constructors
        bool isValid() const;
        Iterator& operator++();
        MultiMapTuple operator*();
        
    private:
        bool m_valid;
        BinaryFile::Offset add;
        DiskMultiMap* m_ptr;
        // Your private member declarations will go here
    };
    
    DiskMultiMap();
    ~DiskMultiMap();
    bool createNew(const std::string& filename, unsigned int numBuckets);
    bool openExisting(const std::string& filename);
    void close();
    bool insert(const std::string& key, const std::string& value, const std::string& context);
    Iterator search(const std::string& key);
    int erase(const std::string& key, const std::string& value, const std::string& context);
private:
   

    struct Header
    {
        int num;
        BinaryFile::Offset firstdeleted;
        
    }h;
    struct node
    {
        
        char value[121], context[121], key[121];
        BinaryFile::Offset curr;
        BinaryFile::Offset next;
        
    };
    
    int hash(const std::string &hashMe, int num)
    {
        
        std::hash<std::string> str_hash;                      // creates a string hasher! // now hash our string!
        unsigned int bucket = str_hash(hashMe) % num;
        return bucket;
    }
    
    void addToHDelete(BinaryFile::Offset add)
    {
        node temp;
        bf.read(temp, add);
        temp.next=FirstDeleted;
        FirstDeleted=temp.curr;
        bf.write(FirstDeleted, sizeof(int));
        
    }
    BinaryFile bf;

    BinaryFile::Offset StartTable;
    BinaryFile::Offset FirstDeleted;
    
    // Your private member declarations will go here
};

#endif // DISKMULTIMAP_H_