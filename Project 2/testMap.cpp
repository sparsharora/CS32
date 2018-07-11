//
//  main.cpp
//  P2
//
//  Created by Sparsh Arora on 1/19/16.
//  Copyright © 2016 Sparsh Arora. All rights reserved.
//

#include "Map.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    Map m1;
    m1.insert("Fred", 2.956);
    m1.insert("Spe", 3.8);
    m1.insert("YOO", 2.45);
    Map m2;
    m2.insert("Ethel", 3.538);
    m2.insert("Lucy", 2.956);
    m1.swap(m2);
    assert(m1.size() == 2  &&  m1.contains("Ethel")  &&  m1.contains("Lucy")  &&
           m2.size() == 3  &&  m2.contains("Fred") && m2.contains("Spe")&&  m2.contains("YOO"));

    cout << "Passed all tests" << endl;
}
