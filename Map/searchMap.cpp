//
// Created by Fitz on 2017/12/2.
//
#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;
#define maxNum 30

class map{
public:
    int pointNum,edgeNum;
    int point[maxNum],edge[maxNum][maxNum];
    map(int p,int e)
    {
        pointNum=p;
        edgeNum=e;
        for(int i=0;i<p;i++)
        {
            for(int j=0;j<p;j++)
            {
                edge[i][j]=0;
            }
        }
    }

    map(){}

    void addEdge(int a,int b,int weight)
    {
        edge[a][b]=weight;
        edge[b][a]=weight;
    }

};

//实例一个图的对象
map newMap;
int visited[maxNum];

//通过文件读入图的信息并建立图
void readFile()
{
    ifstream fileReader;
    string filePath;
    int p,e,a,b,w;
    cout<<"请输入存储图信息的文件位置"<<"tips:格式：顶点个数，边的个数，顶点编号1，顶点编号2，边的权重"endl;
    cin>>filePath;
    fileReader.open(filePath.c_str());
    fileReader>>p>>e;
    newMap.map(p,e);
    for(int i=0;i<e;i++)
    {
        fileReader>>a>>b>>w;
        newMap.addEdge(a,b,w);
    }
    fileReader.close();
}

void deepSearchRecursive()
{

}

int main()
{
    readFile();
    return 0;
}
