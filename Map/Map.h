//
// Created by Fitz on 2017/12/4.
//

#ifndef SCORE_SYSTEM_MAP_H
#define SCORE_SYSTEM_MAP_H
#include "linkList.h"
class MapMatrix {
#define Max 501
public:
    int pointNum;
    int edge[Max][Max];
    bool s[Max];
    int dis[Max],p[Max];
    void initMap(int p);
    void addEdge(int a ,int b ,int weight);
    void addEdge2(int a ,int b ,int weight);
    void dijkstra();
    void prim();

private:
    int dijkstra_MinCost();   //选取起始点到其他为访问过的点的距离最小的点
};

class MapVertex{
public:
    int pointNum;
    char vertex[Max];  //这里存储邻接表的顶点
    linkList<int> edgeNodeIn[Max];
    linkList<int> edgeNodeOut[Max];
    bool visited[Max];
    void initMap(int p);
    void addEdgeTableIn(int a,int b,int weight);
    void addEdgeTableOut(int a,int b,int weight);
    void addEdgeTableIn(int a,int b,int weight,char name);
    void addEdgeTableOut(int a,int b,int weight,char name);
    int topoSort();
};


#endif //SCORE_SYSTEM_MAP_H
