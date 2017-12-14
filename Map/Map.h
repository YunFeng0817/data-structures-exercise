//
// Created by Fitz on 2017/12/4.
//

#ifndef SCORE_SYSTEM_MAP_H
#define SCORE_SYSTEM_MAP_H
#include "linkList.h"



class MapMatrix {
#define Max 501
#define infinite 0x3fffffff
public:
    int pointNum;  //图上点的个数
    double edge[Max][Max];   //图上边的长度
    bool s[Max];   //记录某个节点是否访问过
    double dis[Max],p[Max];   //dis[]记录从初始节点到其他各个节点的最短距离  p[]记录当前节点的前一个访问的节点
    void initMap(int p);   //将邻接矩阵初始化为全0
    void addEdge(int a ,int b , double weight);   //为图的类添加一条无向的边
    void addEdge2(int a ,int b , double weight);
    void dijkstra();   //dijkstra算法的具体实现
    bool prim();

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
