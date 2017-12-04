//
// Created by Fitz on 2017/12/4.
//
#include<iostream>
#include<stack>
#include <cstdlib>
using namespace std;
#define Max 500
#define infite 0x3fffffff
class Map
{
public:
    int pointNum;
    int edge[Max][Max];

    void initMap(int p)
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

    void addEdge(int a,int b,int weight)
    {
        edge[a][b]=weight;
    }

};
Map newMap;
int year,n;
int newDevicePrice[Max];
int repareDevicePrice[Max];
int dis[Max];
int p[Max];
stack<int> trace;
bool s[Max];

int MinCost()
{
    int temp=infite;
    int w=2;
    for(int i=2;i<=n;i++)
    {
        if(!s[i]&&dis[i]<temp)
        {
            temp=dis[i];
            w=i;
        }
    }
    return w;
}

int main()
{
    int w,sum,temp;
    cout<<"请输入年份"<<endl;
    cin>>year;
    cout<<"请输入"<<year<<"年内每年的设备的价格"<<endl;
    for(int i=0;i<year;i++)
    {
        cin>>newDevicePrice[i];
    }
    cout<<"请输入"<<year<<"年内每年维修设备的价格"<<endl;
    for(int i=0;i<year;i++)
    {
        cin>>repareDevicePrice[i];
    }
    n=year;
    newMap.initMap(year);
    for(int i=1;i<=year;i++)
    {
        for(int j=i+1;j<=year;j++)
        {
            temp=0;
            for(int k=0;k<j-i;k++)
            {
                temp+=repareDevicePrice[k];
                if(k==year-i-1)
                    temp+=repareDevicePrice[k+1]<newDevicePrice[year-1]+repareDevicePrice[0]?repareDevicePrice[k+1]:newDevicePrice[year-1]+repareDevicePrice[0];
            }
            newMap.addEdge(i,j,newDevicePrice[i-1]+temp);
        }
    }
    for(int i=2;i<=n;i++)
    {
        dis[i]=newMap.edge[1][i];
        s[i]=false;
        p[i]=1;
    }
    dis[1]=0;
    s[1]=true;
    for(int i=1;i<=n-1;i++)
    {
        w=MinCost();
        s[w]=true;
        for(int v=2;v<=n;v++)
        {
            if(!s[v])
            {
                sum=dis[w]+newMap.edge[w][v];
                if(sum<dis[v])
                {
                    dis[v]=sum;
                    p[v]=w;
                }
            }
        }
    }
    int i=n;
    while(p[i]!=0)
    {
        i=p[i];
        trace.push(i);
    }
    while(!trace.empty())
    {
        cout<<"购进的年份是 "<<trace.top()<<endl;
        trace.pop();
    }
    cout<<"最少的经费是"<<dis[n]<<endl;
    return 0;
}
//5 11 11 12 12 13 5 6 8 11 18
//6 11 11 12 12 13 10 5 6 8 11 18 20
//8 11 11 12 12 13 10 13 14 5 6 8 11 18 20 21 12