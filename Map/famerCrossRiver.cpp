/*
 *思路是用一个四维的相量，每一维分别表示农夫，狼，羊，白菜，0表示未过河的状态，
1表示已经过河的状态，由此可以建立图的模型。最终求解的思路是从(0,0,0,0)到(1,1,1,1)
的一条通路。当然，中间有一些状态不存在，我在程序中直接忽略掉了。
 */
#include <iostream>
#include <stack>
#include <cstdlib>
#include "Map.h"
using namespace std;

MapMatrix newMap;
int index[11]={0,0,1,2,4,5,10,11,13,14,15};   //存储合理状态的点
void establish()
{
    newMap.initMap(10);
    newMap.addEdge2(1,6,1);
    newMap.addEdge2(2,7,1);
    newMap.addEdge2(2,8,1);
    newMap.addEdge2(3,6,1);
    newMap.addEdge2(3,7,1);
    newMap.addEdge2(3,9,1);
    newMap.addEdge2(4,8,1);
    newMap.addEdge2(4,9,1);
    newMap.addEdge2(5,8,1);
    newMap.addEdge2(5,10,1);
}

void coutRoad(int a,int b)
{
    if(((b&0x8)>>3))  //判断状态值的农夫状态那一位，由此判断农夫划船的方向
        cout<<"农夫划去对岸，";
    else
        cout<<"农夫从对岸划回来，";
    switch(((a^b)&7))   //判断前一种状态和后一种状态的区别，是哪种动物的状态发生了改变
    {
        case 0:
            cout<<"没有带东西"<<endl;
            break;
        case 1:
            cout<<"带着白菜"<<endl;
            break;
        case 2:
            cout<<"带着羊"<<endl;
            break;
        case 4:
            cout<<"带着狼"<<endl;
            break;
        default:
            cout<<"error"<<endl;
    }
}

int main()
{
    stack<int> trace;
    establish();
    newMap.dijkstra();
    int i=10,temp;
    trace.push(10);
    while(newMap.p[i])
    {
        i=newMap.p[i];
        trace.push(i);
    }
    cout<<endl;
    while(!trace.empty())
    {
        temp=trace.top();
        trace.pop();
        if(!trace.empty())
        {
            coutRoad(index[temp],index[trace.top()]);
        }
    }
    return 0;
}
