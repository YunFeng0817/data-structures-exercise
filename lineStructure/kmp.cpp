//
// Created by Fitz on 2018/1/6.
//

#include<iostream>

using namespace std;

void get_next(string pattern,int next[])
{
    int j=0,k=-1;
    next[0]=k;
    while(j<pattern.size())
    {
        if(k==-1||pattern[j]==pattern[k])
        {
            if(pattern[++j]==pattern[++k])
                next[j]=next[k];
            else
                next[j]=k;
        }
        else
            k=next[k];
    }
}

int main() {

    return 0;
}
