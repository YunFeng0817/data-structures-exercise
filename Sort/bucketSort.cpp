//
// Created by Fitz on 2017/12/17.
//
#include <iostream>
#include "linkList.h"
using namespace std;
#define Max 100
int num[Max];

void bucketSort(int num[],int length)
{
    linkList<int> bucket[16];
    int flag;
    for(int i=0;i<length;i++)
    {
        if(bucket[num[i]/16].size==0)
            bucket[num[i]/16].insert(0,num[i]);
        else
        {
            flag=0;
            for(int j=1;j<=bucket[num[i]/16].size;j++)
            {
                if(bucket[num[i]/16].inquire(j)->data1>num[i])
                {
                    bucket[num[i]/16].insert(j-1,num[i]);
                    flag=1;
                    break;
                }
            }
            if(flag==0)
                bucket[num[i]/16].insert(bucket->size+1,num[i]);
        }
    }
    int count=0;
    for(int i=0;i<16;i++)
    {
        for(int j=1;j<=bucket[i].size;j++)
        {
            num[count]=bucket[i].inquire(j)->data1;
            count++;
        }
    }
}

int main()
{
    for(int i=0;i<Max;i++)
    {
        num[i]=Max-i;
    }
    bucketSort(num,Max);
    for(int i=0;i<Max;i++)
        cout<<num[i]<<" ";
    cout<<endl;
    return 0;
}
