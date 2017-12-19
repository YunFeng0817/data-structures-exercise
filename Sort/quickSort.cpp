//
// Created by Fitz on 2017/12/16.
//
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#define Num 100000000
#define Max 30000000
#define Min 1
int randomNum1[Num],randomNum2[Num],temp;
using namespace std;
int findKey(int* num,int a,int b)
{
    int mid;
    mid=(a+b)>>1;
    if(num[mid]>num[b])
        swap(num[mid],num[b]);
    if(num[a]>num[mid])
        swap(num[a],num[mid]);
    if(num[mid]>num[b])
        swap(num[mid],num[b]);
    return mid;
}

void insertSort(int num[],int left,int right)
{
    int j,temp,k;
    for(int i=left+1;i<=right;i++)
    {
        temp=num[i];
        j=i;
        while(temp<=num[j]&&j>left)
        {
            j--;
        }
        k=i;
        while(k!=j+1)
        {
            num[k]=num[k-1];
            k--;
        }
        if(temp<num[j])
        {
            num[j+1]=num[j];
            num[j]=temp;
        }
        else
            num[j+1]=temp;
    }
}


void quickSort(int *num,int left,int right)
{
    int i,j,t,temp,l,r,lLen=0,rLen=0;
    if(left>=right)
        return;
    if(right-left<16)    // 当新区键的大小小于16时，改用插入排序的效率更高  经过多次测试，发现参数是16时用时最少
    {
        insertSort(num,left,right);
        return ;
    }
    int pivot=findKey(num,left,right);
    temp=num[pivot]; //temp中存的就是基准数
    i=left;
    j=right;
    l=left;
    r=right;
    while(i<j)
    {
        //顺序很重要，要先从右边开始找
        while(num[j]>=temp && i<j)
        {
            if(num[j]==temp&&j!=pivot)
            {
                if(pivot==r)
                    pivot=j;
                swap(num[j],num[r]);
                r--;
                rLen++;
            }
            j--;
        }
        //再找左边的
        while(num[i]<=temp && i<j)
        {
            if(num[i]==temp&&i!=pivot)
            {
                if(pivot==l)
                    pivot=i;
                swap(num[i],num[l]);
                l++;
                lLen++;
            }
            i++;
        }
        //交换两个数在数组中的位置
        if(i<j)
        {
            t=num[i];
            num[i]=num[j];
            num[j]=t;
        }
    }
//        最终将基准数归位
    if(pivot<=i||num[i]>num[pivot])
    {
        num[pivot]=num[i];
        num[i]=temp;
    }
    else if(i+1<=right)
    {
        num[pivot]=num[i+1];
        num[i+1]=temp;
        i++;
    }
    else
    {
        num[pivot]=num[i+1];
        num[i+1]=temp;
    }
    int x=1;
    if(lLen>0)
        l--;
    int a=lLen;
    while(a>0)
    {
        swap(num[l],num[i-x]);
        x++;
        l--;
        a--;
    }
    a=rLen;
    x=1;
    if(rLen>0)
        r++;
    while(a>0)
    {
        swap(num[r],num[i+x]);
        x++;
        r++;
        a--;
    }
    quickSort(num,i+1+rLen,right);
    quickSort(num,left,i-1-lLen);
}

int cmp( const void *a , const void *b)
{
    return *(int *)a - *(int *)b;
}

int main()
{
    for(int i=0;i<Num;i++)
    {
//        temp=Min+rand()%Max;
        temp=Max-i;
        randomNum1[i]=temp;
        randomNum2[i]=temp;
    }
    cout<<endl;
    double time;
    time=clock();
//    sort(randomNum1,&randomNum1[Num],greater<int>());  //从大到小排序
    qsort(randomNum1,Num, sizeof(int),cmp);   //从小到大排序
//    sort(randomNum1,&randomNum1[Num]);
    time=clock()-time;
    cout<<"排序随机数的数据规模是"<<Num<<endl<<"STL快排的用时为：\t";
    cout<<time<<endl;
    time=clock();
    quickSort(randomNum2,0,Num-1);  //自己的快排函数
    time=clock()-time;
    cout<<"排序随机数的数据规模是"<<Num<<endl<<"自己的快排的用时为：\t";
    cout<<time<<endl;
    for(int i=0;i<Num;i++)
    {
        if(randomNum1[i]!=randomNum2[i])
        {
            cout<<i<<endl;
            cout<<randomNum1[i]<<"  "<<randomNum2[i]<<endl;
        }
    }
    return 0;
}
