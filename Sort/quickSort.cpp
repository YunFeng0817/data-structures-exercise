//
// Created by Fitz on 2017/12/16.
//
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#define Num 10000000
#define Max 10000
#define Min 1
int randomNum1[Num],randomNum2[Num],temp;
using namespace std;
int findKey(int* num,int a,int b)
{
    int mid;
    mid=(a+b)>>1;
    if(num[mid]>num[b])
        swap(num[mid],num[b]);
    if(num[a]>num[mid])
        swap(num[a],num[mid]);
    return a;
}

void quickSort(int *num,int left,int right)
{
    int i,j,t,temp;
    if(left>right)
        return;
    int pivot=findKey(num,left,right);
    temp=num[left]; //temp中存的就是基准数
    i=left;
    j=right;
    while(i!=j)
    {
        //顺序很重要，要先从右边开始找
        while(num[j]>=temp && i<j)
            j--;
        //再找右边的
        while(num[i]<=temp && i<j)
            i++;
        //交换两个数在数组中的位置
        if(i<j)
        {
            t=num[i];
            num[i]=num[j];
            num[j]=t;
        }
    }
    //最终将基准数归位
    num[left]=num[i];
    num[i]=temp;


    quickSort(num,left,i-1);
    quickSort(num,i+1,right);
}

int main()
{
    for(int i=0;i<Num;i++)
    {
        temp=Min+rand()%Max;
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
