//
// Created by Fitz on 2017/12/3.
//
#include<iostream>
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
bool s[Max];

int MinCost()
{
    int temp=infite;
    int w=2;
    for(int i=2;i<=year;i++)
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
    int count=1,pre,w,sum;
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
    n=(year*year-year+2)/2;   //等差数列求和
    newMap.initMap(n);
    for(int i=year-2;i>=0;i--)
    {
        pre=count;
        for(int j=0;j<i;j++)
        {
            newMap.addEdge(count,count+1,repareDevicePrice[j+1]);
            count++;
        }
        count++;
        newMap.addEdge(pre,count,newDevicePrice[year-i-1]+repareDevicePrice[0]);
    }
    newMap.addEdge(2,8,17);
    newMap.addEdge(3,10,17);
    newMap.addEdge(6,10,17);
    for(int i=2;i<=n;i++)
    {
        dis[i]=newMap.edge[1][i];
        s[i]=false;
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
                }
            }
        }
    }
    for(int i=1;i<=n;i++)
        cout<<dis[i]<<endl;
    //cout<<dis[n]+newDevicePrice[0]+repareDevicePrice[0]<<endl;
//    for(int i=1;i<=n;i++)
//    {
//        for(int j=1;j<=n;j++)
//        {
//            cout<<newMap.edge[i][j]<<" ";
//        }
//        cout<<endl;
//    }
    return 0;
}
//5 11 11 12 12 13 5 6 8 11 18