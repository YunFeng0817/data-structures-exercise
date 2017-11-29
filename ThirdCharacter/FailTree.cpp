//
// Created by Fitz on 2017/11/28.
//
#include <iostream>
#include<queue>
using namespace std;
#define Maxnum 100
#define infinite 0x7fffffff
int k;
queue<int> SortedNum[Maxnum];
int fail[Maxnum],sucess[Maxnum];

void establish()
{
    int temp1,temp2;
    for(int i=1;i<=k;i++)
    {
        fail[i+k-1]=i;
        sucess[i+k-1]=i;
    }
    for(int i=k-1;i>0;i--)
    {
        if(2*i<=k-1)
            temp1=SortedNum[sucess[2*i]].front();
        else
            temp1=SortedNum[fail[2*i]].front();
        if(2*i+1<=k-1)
            temp2=SortedNum[sucess[2*i+1]].front();
        else
            temp2=SortedNum[fail[2*i+1]].front();
        if(temp1<temp2)
        {
            sucess[i]=sucess[2*i];
            fail[i]=fail[2*i+1];

        }
        else
        {
            sucess[i]=sucess[2*i+1];
            fail[i]=fail[2*i];
        }
    }
}

//void modify(int specific)
//{
//    int i=specific+k-1;
//    int temp1,temp2;
//    while(i!=0)
//    {
//        if((i/2)%2==0)
//        {
//            temp1=SortedNum[sucess[i]].front();
//            temp2=SortedNum[sucess[i+1]].front();
//            if(temp1<temp2)
//            {
//                sucess[i]=
//            }
//        }
//    }
//}

int main()
{
    int count,temp;
    cout<<"请输入有多少组有序串"<<endl;
    cin>>k;
    cout<<"请输入每组有多少个数字"<<endl;
    cin>>count;
    for(int i=1;i<=k;i++)
    {
        for(int j=0;j<count;j++)
        {
            cin>>temp;
            SortedNum[i].push(temp);
        }
        SortedNum[i].push(infinite);

    }
    for(int i=1;i<=k*count;i++)
    {
        establish();
        cout<<SortedNum[sucess[1]].front()<<"\t";
        SortedNum[sucess[1]].pop();
    }
    return 0;
}
/*
8 3
10 15 16 9 20 38 20 20 30 6 15 25 8 15 20 9 11 16 90 100 110 17 18 20
5 2
17 21 05 44 10 12 29 32 15 56
 */
