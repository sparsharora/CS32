//
//  main.cpp
//  hw25
//
//  Created by Sparsh Arora on 2/2/16.
//  Copyright © 2016 Sparsh Arora. All rights reserved.
//

#include "Map.h"
#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <cstdlib>
#include <cassert>
using namespace std;
bool preced(char a, char b);
bool isvalid(string in);


int evaluate(string infix, const Map& values, string& postfix, int& result)
{
    stack<char> op;
    
    if(!isvalid(infix))
        return 1;
 
   
    
    postfix="";
    while(!op.empty())
        op.pop();
    
    for(int i=0; i<infix.size() ; i++)
    {
        char ch=infix[i];
        switch(ch)
        {
            case ' ': break;
            case '(':
            {
                op.push('(');
                break;
            }
                
            case ')':
            {
                
                while(op.top()!='(')
                {
                    postfix+=op.top();
                    op.pop();
                }
                op.pop();
                break;
            }
                
            case '+':
            case '*':
            case '/':
            case '-':
            {
                while(!op.empty() && op.top()!='(' && preced(ch,op.top()))
                {
                    postfix+=op.top();
                    op.pop();
                }
                op.push(ch);
                break;
            }
            default:
            {
                postfix+=ch;
                break;
            }
        }
            
    }
    while(!op.empty())
    {

        postfix+=op.top();
        op.pop();
    }
    
    for(int i=0; i<infix.size() ; i++)
    {
        char m=infix[i];
        if(isalpha(m))
        {
            if(!values.contains(m))
                return 2;
        }
        
        
    }
    
    while(!op.empty())
        op.pop();
    
    for(int i=0;i<postfix.size();i++)
    {
        char h=postfix[i];
        ValueType val;
        
        if(isalpha(h))
        {
            values.get(h, val);
            op.push(val);
        }
        else
        {
            int v1=op.top();
            op.pop();
            int v2=op.top();
            op.pop();
            if(h=='+')
                op.push(v2+v1);
            else if(h=='*')
                op.push(v1*v2);
            else if (h=='-')
                op.push(v2-v1);
            else
                if(v1==0)
                    return 3;
                else
                    op.push(v2/v1);
            
        }

    }
    
    result=op.top();
    return 0;
    
}


bool preced(char a, char b)
{
    if((a=='*' && b=='*') || (a=='+' && b=='*') || (a=='-' && b=='*') || (a=='/' && b=='*'))
        return true;
    else if ((a=='/' && b=='/') ||(a=='+' && b=='/') ||(a=='-' && b=='/') )
        return true;
    else if ((a=='+' && b=='+') ||(a=='-' && b=='+') )
        return true;
    else
        return false;
}

bool isvalid(string in)
{
    int ctr1=0, ctr2=0, br=0;
    for(int i=0;i<in.size();i++)
    {
        if(isalpha(in[i])&&islower(in[i]))
        {
            ctr1++;
            continue;
        }
        else if(in[i]=='+'|| in[i]=='*'|| in[i]=='/'|| in[i]=='-')
        {
            ctr2++;
            continue;
        }
        else if(in[i]=='(')
        {
            br++;
            continue;
        }
        else if(in[i]==')')
        {
            br--;
            continue;
        }
        else if(in[i]==' ')
        {
            continue;
        }
        else
            return false;
    }
    int ctr=ctr1-ctr2;
    if(ctr==1 && br==0)
        return true;
    else
        return false;
}

