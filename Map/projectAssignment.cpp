//
// Created by Fitz on 2017/12/7.
//
#include <iostream>
#include"linkList.h"
using namespace std;



int main()
{
    linkList<int> test;
    test.insert(0,7);
    test.insert(test.size,6);
    test.insert(1,5);
    test.insert(0,4);
    test.pop(2);
    for(int i=1;i<=test.size;i++)
        cout<<test.inquire(i)<<endl;
    return 0;
}
