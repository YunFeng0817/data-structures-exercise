//
// Created by Fitz on 2017/12/16.
//
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#define Num 400000
#define Max 10000
#define Min 1

using namespace std;
void quickSort()
{

}

int main()
{
    int randomNum[Num];
    srand(unsigned(clock()));
    for(int i=0;i<Num;i++)
    {
        randomNum[i]=Min+(int)Max*rand()/(RAND_MAX+1);
    }
    double time;
    time=clock();
    sort(randomNum,&randomNum[Num],greater<int>());  //从大到小排序
    time=clock()-time;
    cout<<"排序随机数的数据规模是"<<Num<<endl<<"STL快排的用时为：\t";
    cout<<time/1000<<endl;
//    for(int i=0;i<Num;i++)
//    {
//        cout<<randomNum[i]<<endl;
//    }
    return 0;
}
