//
// Created by Fitz on 2017/12/7.
//
#include <iostream>
#include <fstream>
#include <cmath>
#include "Map.h"
using namespace std;

struct node{
    int x,y;
};

MapMatrix newMap;
int point;
node position[Max];
int main()
{
    double sum=0;
    double distance;
    ifstream file;
    file.open("position.dat");
    if(!file.is_open())
    {
        cout<<"无法打开文件"<<endl;
        exit(0);
    }
    file>>point;
    newMap.initMap(point);
    for(int i=1;i<=point;i++)
    {
        file>>position[i].x>>position[i].y;
    }
    for(int i=1;i<point;i++)
    {
        for(int j=i+1;j<=point;j++)
        {
            distance=sqrt((position[i].x-position[j].x)*(position[i].x-position[j].x)+(position[i].y-position[j].y)*(position[i].y-position[j].y));
            if(distance>=10&&distance<=1000)
            {
                newMap.addEdge2(i,j,distance);
            }
        }
    }
    newMap.prim();
    for(int i=1;i<=point;i++)
    {
        if(newMap.dis[i]==infinite)
        {
            cout<<"no"<<endl;
            exit(0);
        }
        sum+=newMap.dis[i];
    }
    cout<<sum*100<<endl;
    return 0;
}
