//
// Created by Fitz on 2017/12/16.
//
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#define Num 4000
#define Max 10000
#define Min 1

using namespace std;
int findKey(int* num,int a,int b)
{
    int m=num[a];
    for(int k=a+1;k<=b;k++)
    {
        if(num[k]>m)
            return k;
        else if(num[k]<m)
            return a;
    }
    return 0;
}

void swap(int *a,int *b)
{
    int temp;
    temp=*a;
    *a=*b;
    *b=temp;
}

void quickSort(int *num,int a,int b)
{
    int l=a,r=b,pivot;
    pivot=findKey(num,a,b);
    do{
        for(l;num[l]<num[pivot];l++);
        for(r;num[r]>=num[pivot];r--);
        if(l<r)
            swap(&num[l],&num[r]);
    }while(l<=r);
    if(pivot!=0)
    {
        quickSort(num,a,l-1);
        quickSort(num,l,b);
    }
}

int main()
{
    int randomNum1[Num],randomNum2[Num],temp;
    for(int i=0;i<Num;i++)
    {
        temp=Min+(int)Max*rand()/(RAND_MAX+1);
        randomNum1[i]=temp;
        randomNum2[i]=temp;
//        cout<<randomNum[i]<<"\t";
    }
    cout<<endl;
    double time;
    time=clock();
//    sort(randomNum1,&randomNum1[Num],greater<int>());  //从大到小排序
    sort(randomNum1,&randomNum1[Num]);   //从小到大排序
    time=clock()-time;
    cout<<"排序随机数的数据规模是"<<Num<<endl<<"STL快排的用时为：\t";
    cout<<time<<endl;
    time=clock();
    quickSort(randomNum2,0,Num-1);  //自己的快排函数
    time=clock()-time;
    cout<<"排序随机数的数据规模是"<<Num<<endl<<"自己的快排的用时为：\t";
    cout<<time<<endl;
    for(int i=0;i<Num;i++)
    {
//        cout<<randomNum2[i]<<"\t";
        if(randomNum1[i]!=randomNum2[i])
        {
            cout<<i<<endl;
            cout<<randomNum1[i]<<"  "<<randomNum2[i]<<endl;
        }
    }
    return 0;
}
