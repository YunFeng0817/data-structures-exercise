//
// Created by Fitz on 2017/12/7.
//
#include <iostream>
#include <fstream>
#include "Map.h"
using namespace std;
#define Max 100
MapVertex newMap;

int point[Max];
int ve[Max];

int main()
{
    ifstream file;
    file.open("data.dat");  //这是存录入数据的文件
    if(!file.is_open())
    {
        cout<<"文件打开失败，请重新选择文件"<<endl;
        exit(0);
    }
    cout<<"请输入工序的数量"<<endl;
    int n,a,b,c;
    file>>n;
    newMap.initMap(n);
    cout<<"请输入每道工序的编号，紧前工序的编号，和该工序的所需时间"<<endl;
    while(!file.eof())
    {
        file>>a>>b>>c;
        if(a!=-1)
        {
            newMap.addEdgeTableIn(b,a,c);
            newMap.addEdgeTableOut(b,a,c);
        }
        point[b]=c;
    }
    for(int i=1;i<=n;i++)
    {
        ve[i]=0;
    }
    for(int i=1;i<=n;i++)
    {
        a=newMap.topoSort();
        for(int j=1;j<=newMap.edgeNodeOut[a].size;j++)
        {
            if(ve[newMap.edgeNodeOut[a].inquire(j)->data1]<ve[i]+point[a])
                ve[newMap.edgeNodeOut[a].inquire(j)->data1]=ve[i]+point[a];
        }
    }
    for(int i=1;i<=n;i++)
    {
        cout<<(char)(i+'A'-1)<<"工序最早在第"<<ve[i]<<"天开始"<<endl;
    }
    for(int i=1;i<=n;i++)
    {
        cout<<"完成"<<(char)(i+'A'-1)<<"工序需要的最短天数为"<<ve[i]+point[i]<<endl;
    }
    return 0;
}
