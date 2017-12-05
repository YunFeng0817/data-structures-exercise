//
// Created by Fitz on 2017/12/4.
//
#include<iostream>
#include<stack>
#include"Map.h"
#include <cstdlib>
using namespace std;
#define Max 500

Map newMap;
int year,n;
int newDevicePrice[Max];
int repareDevicePrice[Max];
stack<int> trace;


int main()
{
    int w,sum,temp;
    cout<<"���������"<<endl;
    cin>>year;
    cout<<"������"<<year<<"����ÿ����豸�ļ۸�"<<endl;
    for(int i=0;i<year;i++)
    {
        cin>>newDevicePrice[i];
    }
    cout<<"������"<<year<<"����ÿ��ά���豸�ļ۸�"<<endl;
    for(int i=0;i<year;i++)
    {
        cin>>repareDevicePrice[i];
    }
    n=year;
    newMap.initMap(year);
    for(int i=1;i<=year;i++)
    {
        for(int j=i+1;j<=year;j++)
        {
            temp=0;
            for(int k=0;k<j-i;k++)
            {
                temp+=repareDevicePrice[k];
                if(k==year-i-1)
                    temp+=repareDevicePrice[k+1]<newDevicePrice[year-1]+repareDevicePrice[0]?repareDevicePrice[k+1]:newDevicePrice[year-1]+repareDevicePrice[0];
            }
            newMap.addEdge(i,j,newDevicePrice[i-1]+temp);
        }
    }
    newMap.dijkstra();
    int i=n;
    while(newMap.p[i]!=0)
    {
        i=newMap.p[i];
        trace.push(i);
    }
    while(!trace.empty())
    {
        cout<<"����������� "<<trace.top()<<endl;
        trace.pop();
    }
    cout<<"���ٵľ�����"<<newMap.dis[n]<<endl;
    return 0;
}
//5 11 11 12 12 13 5 6 8 11 18
//6 11 11 12 12 13 10 5 6 8 11 18 20
//8 11 11 12 12 13 10 13 14 5 6 8 11 18 20 21 12