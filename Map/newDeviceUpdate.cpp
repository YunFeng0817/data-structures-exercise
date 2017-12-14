//
// Created by Fitz on 2017/12/4.
//
#include<iostream>
#include<stack>
#include"Map.h"
#include <cstdlib>
using namespace std;

MapMatrix newMap;   //用图的类实例化一个图的对象
int year,n;   //year 是总的年份
int newDevicePrice[Max];   //在某一年更新设备的花费
int repareDevicePrice[Max]; //在某一年维修设备的花费
stack<int> trace;   //将路径的信息倒序时需要用到的栈的数据结构


int main()
{
    int w,sum,temp;
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
    n=year;
    newMap.initMap(year);
    //这个三重循环主要用来为图录入边的信息
    for(int i=1;i<=year;i++)
    {
        //以第i年为边的一个起点，以第j年为中点
        for(int j=i+1;j<=year;j++)
        {
            temp=0;
            //这个循环 需要加上多年的维修费用
            for(int k=0;k<j-i;k++)
            {
                temp+=repareDevicePrice[k];
                //如果是计算到最后一年的花费，需要判断最后一年重新买新的设备合算还是维修合算，这样就可以减少一个节点
                if(k==year-i-1)
                    temp+=repareDevicePrice[k+1]<newDevicePrice[year-1]+repareDevicePrice[0]?repareDevicePrice[k+1]:newDevicePrice[year-1]+repareDevicePrice[0];
            }
            newMap.addEdge(i,j,newDevicePrice[i-1]+temp);   //在图的对象中添加该边的信息
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
        cout<<"购进的年份是 "<<trace.top()<<endl;
        trace.pop();
    }
    cout<<"最少的经费是"<<newMap.dis[n]<<endl;
    return 0;
}
//5 11 11 12 12 13 5 6 8 11 18
//6 11 11 12 12 13 10 5 6 8 11 18 20
//8 11 11 12 12 13 10 13 14 5 6 8 11 18 20 21 12