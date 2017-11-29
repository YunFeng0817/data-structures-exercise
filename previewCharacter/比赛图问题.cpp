#include <iostream>
//#include<string>
#include<cstdio>
#include<cstdlib>
#include<string.h>
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
#define N 1000
bool e[N][N];
int count=1,n;;
int road[N];
int search(int pre);
int main(int argc, char** argv) {
    int tempa,tempb;
    cout<<"请输入选手的个数"<<endl;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            e[i][j]=0;
        }
    }
    for(int i=1;i<=n*(n-1)/2;i++)
    {
        cout<<"请输入两个选手的胜负（前面为胜者，后面为负者，每组两个数字）"<<endl;
        cin>>tempa>>tempb;
        e[tempa][tempb]=1;
    }
    for(int k=1;k<=n;k++)
    {
        count=1;
        memset(road,0,sizeof(int));
        if(search(k))
        {
            for(int i=1;i<=n;i++)
            {
                if(i<n)
                    cout<<road[i]<<"->";
                else
                    cout<<road[i]<<endl;
            }
        }
    }
    return 0;
}

int search(int pre)
{
    road[count]=pre;
    if(count==n)
        return 1;
    else
    {
        for(int i=1;i<=n;i++)
        {
            if(e[pre][i]==1)
            {
                int flag=0;
                for(int j=1;j<=count;j++)
                {
                    if(i==road[j])
                        flag=1;
                }
                //printf("flag:%d\n",flag);
                if(flag==0)
                {
                    //printf("road %d : %d\n",count,road[count]);
                    count++;
                    if(search(i))
                        return 1;
                    /*if(!search(i))
                        count--;
                        printf("count:%d\n",count);*/
                    /*else
                    {
                        return 0;
                    }*/
                }
            }
        }
        count--;
        return 0;
    }
}
/*   test 1
4
1 2
3 1
1 4
2 3
4 2
4 3

test2

5
4 5
4 3
4 2
4 1
5 3
5 2
5 1
2 3
2 1
3 1

test3
5
4 3
2 4
2 5
3 1
1 5
4 1
1 2
3 2
5 3
4 5

*/
