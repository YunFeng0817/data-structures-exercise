//
// Created by Fitz on 2017/12/4.
//

#include "Map.h"
#include "linkList.h"
#define infite 0x3fffffff
void MapMatrix::initMap(int p)
{
    pointNum=p;
    for(int i=1;i<=pointNum;i++)
    {
        for(int j=1;j<=pointNum;j++)
        {
            edge[i][j]=infite;
        }
    }
}

void MapMatrix::addEdge(int a,int b,int weight)
{
    edge[a][b]=weight;
}

void MapMatrix::addEdge2(int a,int b,int weight)
{
    edge[a][b]=weight;
    edge[b][a]=weight;
}

void MapMatrix::dijkstra()
{
    int w,sum;
    for(int i=2;i<=pointNum;i++)
    {
        dis[i]=edge[1][i];
        s[i]=false;
        p[i]=1;
    }
    dis[1]=0;
    s[1]=true;
    for(int i=1;i<=pointNum-1;i++)
    {
        w=dijkstra_MinCost();
        s[w]=true;
        for(int v=2;v<=pointNum;v++)
        {
            if(!s[v])
            {
                sum=dis[w]+edge[w][v];
                if(sum<dis[v])
                {
                    dis[v]=sum;
                    p[v]=w;
                }
            }
        }
    }
}

int MapMatrix::dijkstra_MinCost()
{
    int temp=infite;
    int w=2;
    for(int i=2;i<=pointNum;i++)
    {
        if(!s[i]&&dis[i]<temp)
        {
            temp=dis[i];
            w=i;
        }
    }
    return w;
}

void MapVertex::initMap(int p){
    pointNum=p;
    for(int i=1;i<=pointNum;i++)
    {
        vertex[i]=-1;
    }
}

void MapVertex::addEdgeTableIn(int a, int b, int weight) {
    vertex[b]=weight;
    edgeNode[b].insert(0,a);
}

void MapVertex::addEdgeTableOut(int a, int b, int weight) {
    vertex[a]=weight;
    edgeNode[a].insert(0,b);
}

