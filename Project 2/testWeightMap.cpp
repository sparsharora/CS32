//
//  testWeightMap.cpp
//  P2
//
//  Created by Sparsh Arora on 1/19/16.
//  Copyright © 2016 Sparsh Arora. All rights reserved.
//

#include "WeightMap.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    WeightMap m;  // maps strings to doubles
    
    ValueType v = 1234.5;
    assert(m.enroll("abc", v)  &&  v == 1234.5); // v unchanged by get failure
    assert(!m.enroll("gef", -10));
    assert(m.weight("xyz") == -1);
    m.weight("abc");
    assert(m.size() == 1);
    assert(!m.adjustWeight("abc", -10000));
    assert(m.adjustWeight("abc", 5000));
    assert(m.enroll("gef", 10));
    m.print();
    KeyType k = "hello";
    cout << "Passed all tests" << endl;
}
