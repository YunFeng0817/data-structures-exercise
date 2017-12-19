//
// Created by Fitz on 2017/12/17.
//
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include "linkList.h"
using namespace std;
#define Max 10000
#define bucketNum 50
#define madix 10
int num[Max];
int temp1[Max+1];
int temp2[Max+1];
linkList<int> bucket[bucketNum];
void bucketSort(int num[],int length)
{
    int flag;
    for(int i=0;i<length;i++)
    {
        if(bucket[num[i]>>1].size==0)
            bucket[num[i]>>1].insert(0,num[i]);
        else
        {
            flag=0;
            for(int j=1;j<=bucket[num[i]>>1].size;j++)
            {
                if(bucket[num[i]>>1].inquire(j)->data1>num[i])
                {
                    bucket[num[i]>>1].insert(j-1,num[i]);
                    flag=1;
                    break;
                }
            }
            if(flag==0)
                bucket[num[i]>>1].insert(bucket[num[i]>>1].size,num[i]);
        }
    }
    int count=0;
    for(int i=0;i<bucketNum;i++)
    {
        for(int j=1;j<=bucket[i].size;j++)
        {
            num[count]=bucket[i].inquire(j)->data1;
            bucket[i].pop(j);    //释放内存，防止内存泄漏
            count++;
        }
    }
}

void CountingSort(int *A,int *B,int *Order,int N,int K)
{
    int *C=new int[K+1];
    int i;
    memset(C,0,sizeof(int)*(K+1));
    for (i=1;i<=N;i++) //把A中的每个元素分配
        C[A[i]]++;
    for (i=2;i<=K;i++) //统计不大于i的元素的个数
        C[i]+=C[i-1];
    for (i=N;i>=1;i--)
    {
        B[C[A[i]]]=A[i]; //按照统计的位置，将值输出到B中，将顺序输出到Order中
        Order[C[A[i]]]=i;
        C[A[i]]--;
    }
}

void countSortEasy(int num[],int length,int maxNum)
{
    memset(temp1,0, sizeof(int)*(maxNum+1));
    for(int i=0;i<length;i++)
        temp1[num[i]]++;
    int c=0;
    for(int i=0;i<=maxNum;i++)
    {
        for(int j=0;j<temp1[i];j++)
        {
            num[c]=i;
            c++;
        }
    }
}

void countSortComplex(int num[],int length,int maxNum)
{
    memset(temp1,0, sizeof(int)*(maxNum+1));
    for(int i=0;i<length;i++)
        temp1[num[i]]++;
    for(int i=0;i<maxNum;i++)
    {
        temp1[i+1]=temp1[i]+temp1[i+1];
    }
    for(int i=length-1;i>=0;i--)
    {
        temp2[temp1[num[i]]-1]=num[i];
        temp1[num[i]]--;
    }
    for(int i=0;i<length;i++)
    {
        num[i]=temp2[i];
    }
}

void madixSort(int num[],int length)
{
    int max=num[0];
    for(int i=0;i<length-1;i++)
    {
        if(max<num[i+1])
            max=num[i+1];
    }
    int temp=1;
    memset(temp1,0, sizeof(int)*(max+1));
    while(max/temp)
    {
        for(int i=0;i<length;i++)
            temp1[(num[i]/temp)%madix]++;
        for(int i=0;i<madix;i++)
        {
            temp1[i+1]=temp1[i]+temp1[i+1];
        }
        for(int i=length-1;i>=0;i--)
        {
            temp2[temp1[(num[i]/temp)%madix]-1]=num[i];
            temp1[(num[i]/temp)%madix]--;
        }
        temp*=madix;
    }
}

int main()
{
    for(int i=0;i<Max;i++)
    {
        num[i]=Max-i;
    }
    double time;
    time=clock();
//    bucketSort(num,Max);
    time=clock()-time;
    cout<<"排序随机数的数据规模是"<<Max<<endl<<"用时为：\t";
    cout<<time<<endl;
    time=clock();
    countSortComplex(num,Max,Max);
    time=clock()-time;
    cout<<"排序随机数的数据规模是"<<Max<<endl<<"用时为：\t";
    cout<<time<<endl;
//    RadixSort(num,Max);
    for(int i=0;i<Max;i++)
        cout<<num[i]<<" ";
    cout<<endl;
    return 0;
}
