//
// Created by Fitz on 2017/12/4.
//

#ifndef SCORE_SYSTEM_MAP_H
#define SCORE_SYSTEM_MAP_H

class Map {
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

private:
    int dijkstra_MinCost();   //选取起始点到其他为访问过的点的距离最小的点
};


#endif //SCORE_SYSTEM_MAP_H
