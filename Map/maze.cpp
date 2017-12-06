//
// Created by Fitz on 2017/12/6.
//
#include <cstdlib>
#include <iostream>
#include <queue>
using namespace std;
#define Max 100
int size,count=0;
bool mazeMap[Max][Max];
bool visited[Max][Max];
struct point{
    int x,y,next,pre;
};
queue<point> getPoint;
point trace[Max];
bool searchRoad()
{
    point temp;
    if(mazeMap[1][1])
    {
        cout<<"迷宫无法进入"<<endl;
        exit(0);
    }
    visited[1][1]=true;
    temp.x=1;
    temp.y=1;
    temp.next=count;
    getPoint.push(temp);
    trace[count].x=1;
    trace[count].y=1;
    trace[count].pre=-1;
    count++;
    while(!getPoint.empty())
    {
        if(getPoint.front().x==size&&getPoint.front().y==size)
        {
            return true;
        }
        for(int i=-1;i<=1;i++)
        {
            for(int j=-1;j<=1;j++)
            {
                if(!mazeMap[getPoint.front().x+i][getPoint.front().y+j]&&!visited[getPoint.front().x+i][getPoint.front().y+j])
                {
                    trace[count].x=getPoint.front().x+i;
                    trace[count].y=getPoint.front().y+j;
                    trace[count].pre=getPoint.front().next;
                    count++;
                    temp.x=getPoint.front().x+i;
                    temp.y=getPoint.front().y+j;
                    temp.next=count-1;
                    getPoint.push(temp);
                    visited[getPoint.front().x+i][getPoint.front().y+j]=true;
                }
            }
        }
        getPoint.pop();
    }
    return false;
}

void getRoad(int a)
{
    if(trace[a].pre!=-1)
    {
        getRoad(trace[a].pre);
    }
    cout<<"( "<<trace[a].x<<" , "<<trace[a].y<<" )"<<endl;
}

int main()
{
    cout<<"请输入迷宫边的大小"<<endl;
    cin>>size;
    cout<<"请依次输入迷宫的每个点的数据"<<endl;
    for(int i=0;i<=size+1;i++)  //录入迷宫的点的信息
    {
        for(int j=0;j<=size+1;j++)
        {
            if(i==0||i==size+1)
                mazeMap[i][j]=true;
            else if(j==0||j==size+1)
                mazeMap[i][j]=true;
            else
                cin>>mazeMap[i][j];
        }
    }
    searchRoad();
    getRoad(count-1);
    return 0;
}
/*
5
0 1 0 1 1
0 1 0 1 1
0 0 0 1 1
1 0 1 1 0
0 1 0 0 0
 */