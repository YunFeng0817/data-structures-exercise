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
int p[Max];
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
    int count=1,pre,w,sum,main[Max],count1=0;
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
        main[count1]=count;
        count1++;
        newMap.addEdge(pre,count,newDevicePrice[year-i-1]+repareDevicePrice[0]);
    }
    count=1;
    for(int i=year-1;i>0;i--)
    {
        for(int j=0;j<i;j++)
        {
            if(main[j+year-i-1]!=n)
                newMap.addEdge(count,main[j+year-i-1],newDevicePrice[j+1]+repareDevicePrice[0]);
            else
                newMap.addEdge(count,main[j+year-i-1],repareDevicePrice[j+1]<newDevicePrice[j+1]+repareDevicePrice[0]?repareDevicePrice[j+1]:newDevicePrice[j+1]+repareDevicePrice[0]);
            count++;
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
//    for(int i=1;i<=n;i++)
//        cout<<p[i]<<endl;
    int i=n;
    while(p[i]!=0)
    {
        i=p[i];
        for(int j=0;j<count1;j++)
        {
            if(i==main[j])
                cout<<"购进的年份是 "<<j+2<<endl;
        }
    }
    cout<<"购进的年份是 "<<1<<endl;
    for(int j=0;j<count1;j++)
    {

            //cout<<main[j]<<endl;
    }
    cout<<endl;
    cout<<"最少的经费是"<<dis[n]+newDevicePrice[0]+repareDevicePrice[0]<<endl;
    return 0;
}
//5 11 11 12 12 13 5 6 8 11 18
//6 11 11 12 12 13 10 5 6 8 11 18 20