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
queue<int> getPoint[2];
void searchRoad()
{
    if(mazeMap[1][1])
    {
        cout<<"迷宫无法进入"<<endl;
        exit(0);
    }
    visited[1][1]=true;
    getPoint[0].push(1);
    getPoint[1].push(1);
    while(!getPoint[0].empty())
    {
        cout<<getPoint[0].front()<<" "<<getPoint[1].front()<<endl;
        if(getPoint[0].front()==size&&getPoint[1].front()==size)
        {
            cout<<count<<endl;
            return;
        }
        for(int i=-1;i<=1;i++)
        {
            for(int j=-1;j<=1;j++)
            {
                if(!mazeMap[getPoint[0].front()+i][getPoint[1].front()+j]&&!visited[getPoint[0].front()+i][getPoint[1].front()+j])
                {
                    getPoint[0].push(getPoint[0].front()+i);
                    getPoint[1].push(getPoint[1].front()+j);
                    visited[getPoint[0].front()+i][getPoint[1].front()+j]=true;
                }
            }
        }
        getPoint[0].pop();
        getPoint[1].pop();
        count++;
    }
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