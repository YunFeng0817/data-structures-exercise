//
// Created by Fitz on 2017/12/17.
//
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include "linkList.h"
using namespace std;
#define Max 100
int num[Max];
int count[10];
int tmp[10];
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

void countSort(int num[],int length,int maxNum)
{
    int temp[maxNum+1];
    memset(temp,0, sizeof(int)*length);
    for(int i=0;i<length;i++)
        temp[num[i]]++;
    int count=0;
    for(int i=0;i<=maxNum;i++)
    {
        for(int j=0;j<temp[i];j++)
        {
            num[count]=i;
            count++;
        }
    }
}

int maxbit(int data[],int n)
{
    int d=1;
    for(int i=0;i<n;i++)
    {
        int c=1;
        int p=data[i];
        while(p/10)
        {
            p=p/10;
            c++;
        }
        if(c>d)
            d=c;
    }
    return d;
}

void RadixSort(int data[],int n)
{
    int d=maxbit(data,n);
    int r=1;
    int rad[n];
    int c[10],count1;
    memset(c,0, sizeof(int)*10);
    for(int i=0;i<d;i++)
    {

        for(int i=0;i<10;i++)//装桶之前要先清桶
            count[i]=0;
        for(i=0;i<n;i++) //记录每个桶的记录数
        {
            int k=data[i]/r;
            int q=k%10;
            count[q]++;
        }
        for(i=1;i<10;i++)//计算位置
        {
            count[i]+=count[i-1];
        }
        for(int j=n-1;j>=0;j--)
        {
            int p=data[j]/r;
            int s=p%10;
            tmp[count[s]-1]=data[j];
            count[s]--;
        }
//        countSort(tmp,10,100);
        for(int k=0;k<n;k++)
        {
            num[i]=tmp[i];
            c[i]++;
        }
        r=r*10;
    }
//    r=0;
//    count1=0;
//    for(int i=0;i<10;i++)
//    {
//        for(int j=i;j<c[i];j++)
//        {
//            num[r]=rad[count1+j];
//            r++;
//        }
//        count1+=c[i];
//    }

}

int main()
{
    for(int i=0;i<Max;i++)
    {
        num[i]=i;
    }
    double time;
    time=clock();
    bucketSort(num,Max);
    time=clock()-time;
    cout<<"排序随机数的数据规模是"<<Max<<endl<<"用时为：\t";
    cout<<time<<endl;
    time=clock();
    countSort(num,Max,Max);
    time=clock()-time;
    cout<<"排序随机数的数据规模是"<<Max<<endl<<"用时为：\t";
    cout<<time<<endl;
//    RadixSort(num,Max);
    for(int i=0;i<Max;i++)
        cout<<num[i]<<" ";
    cout<<endl;
    return 0;
}
