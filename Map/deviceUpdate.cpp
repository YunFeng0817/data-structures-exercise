//
// Created by Fitz on 2017/12/3.
//
#include<iostream>
#include <stack>
#include <cstdlib>
#include "Map.h"
using namespace std;
#define Max 500

Map newMap;
int year,n;
int newDevicePrice[Max];
int repareDevicePrice[Max];
stack<int> trace;

int main()
{
    int count=1,pre,w,sum,main[Max],count1=0;
    cout<<"请输入年份"<<endl;
    cin>>year;
    cout<<"请输入"<<year<<"年内每年的设备的价格"<<endl;
    for(int i=0;i<year;i++)
    {
        cin>>newDevicePrice[i];
    }
    cout<<"请输入"<<year<<"年内每年维修设备的价格"<<endl;
    for(int i=0;i<year;i++)
    {
        cin>>repareDevicePrice[i];
    }
    n=(year*year-year+2)/2;   //等差数列求和
    newMap.initMap(n);
    for(int i=year-2;i>=0;i--)
    {
        pre=count;
        for(int j=0;j<i;j++)
        {
            newMap.addEdge(count,count+1,repareDevicePrice[j+1]);
            count++;
        }
        count++;
        main[count1]=count;
        count1++;
        newMap.addEdge(pre,count,newDevicePrice[year-i-1]+repareDevicePrice[0]);
    }
    count=1;
    for(int i=year-1;i>0;i--)
    {
        for(int j=0;j<i;j++)
        {
            if(main[j+year-i-1]!=n)
                newMap.addEdge(count,main[j+year-i-1],newDevicePrice[j+1]+repareDevicePrice[0]);
            else
                newMap.addEdge(count,main[j+year-i-1],repareDevicePrice[j+1]<newDevicePrice[j+1]+repareDevicePrice[0]?repareDevicePrice[j+1]:newDevicePrice[j+1]+repareDevicePrice[0]);
            count++;
        }
    }
    newMap.dijkstra();
    int i=n;
    while(newMap.p[i]!=0)
    {
        i=newMap.p[i];
        for(int j=0;j<count1;j++)
        {
            if(i==main[j])
                trace.push(j+2);
        }
    }
    trace.push(1);
    while(!trace.empty())
    {
        cout<<"购进的年份是 "<<trace.top()<<endl;
        trace.pop();
    }
    cout<<endl;
    cout<<"最少的经费是"<<newMap.dis[n]+newDevicePrice[0]+repareDevicePrice[0]<<endl;
    return 0;
}
//5 11 11 12 12 13 5 6 8 11 18
//6 11 11 12 12 13 10 5 6 8 11 18 20