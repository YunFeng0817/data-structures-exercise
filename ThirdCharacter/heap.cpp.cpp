//
// Created by Fitz on 2017/11/23.
//
#include <iostream>
#include <fstream>
#include <queue>
using namespace std;
int ID[100];
struct CellElement
{
    int pority;   //优先级
    int pocessID; //进程号
};

class heap
{
public:
    int size;
    int Maxlength;
    CellElement *Elements;
    heap(int length)
    {
        size=0;
        Maxlength=length;
        Elements=new CellElement[Maxlength];
    }

    bool empty()
    {
        if(size==0)
            return true;
        return false;
    }

    bool full()
    {
        return (size==Maxlength-1);
    }

    bool insert(int p,int ID)
    {
        int i=size+1;
        if(!full())
        {
            size++;
            while(i!=1&&p>Elements[i/2].pority)
            {
                Elements[i].pority=Elements[i/2].pority;
                Elements[i].pocessID=Elements[i/2].pocessID;
                i=i/2;
            }
            Elements[i].pocessID=ID;
            Elements[i].pority=p;
            return true;
        }
        return false;
    }

    int findID(int n)
    {
        for(int i=0;i<size;i++)
        {
            if(ID[i]==n)
                return i;
        }
        return -1;
    }

    CellElement top()
    {
        return Elements[1];
    }

    bool DeleteMax()
    {
        int i=1,max;
        CellElement last;
        if(!empty())
        {
            last=Elements[size];
            size--;
            while(2*i<=size)
            {
                if(2*i+1<=size)
                    max=Elements[2*i].pority>Elements[2*i+1].pority?Elements[2*i].pority:Elements[2*i+1].pority;
                else
                    max=Elements[2*i].pority;
                if(last.pority<=max)
                {
                    if(2*i+1>size||Elements[2*i].pority>Elements[2*i+1].pority||(Elements[2*i].pority==Elements[2*i+1].pority&&findID(Elements[2*i].pocessID)>findID(Elements[2*i+1].pocessID)))
                    {
                        cout<<"Elements[2*i].pority "<<Elements[2*i].pority<<" Elements[2*i+1].pority "<<Elements[2*i+1].pority<<endl;
                        Elements[i].pority=Elements[2*i].pority;
                        Elements[i].pocessID=Elements[2*i].pocessID;
                        i=2*i;
                    }
                    else
                    {
                        Elements[i].pority=Elements[2*i+1].pority;
                        Elements[i].pocessID=Elements[2*i+1].pocessID;
                        i=2*i+1;
                    }
                }
                else
                    break;
            }
            Elements[i].pority=last.pority;
            Elements[i].pocessID=last.pocessID;
        }
        return false;
    }

};

int main()
{
    heap system(100);
    fstream ReadFile;
    int a=0,b=0,count=0;
    ReadFile.open("C:\\Users\\29488\\Desktop\\task.dat",ios::in);
    if (!ReadFile.is_open())
    {
        cout << "Error opening file"<<endl;
        exit (1);
    }
    while(!ReadFile.eof())
    {
        ReadFile>>a>>b;
        ID[count]=a;
        count++;
        system.insert(b,a);  //先进程号后优先级
    }
    ReadFile.close();
    a=system.size;
    for(int i=1;i<=a;i++)
    {
//        cout<<system.Elements[i].pocessID<<"\t"<<system.Elements[i].pority<<endl;
        cout<<system.top().pocessID<<"\t"<<system.top().pority<<endl;
        system.DeleteMax();
    }
    return 0;
}
/*
10 0
20 1
15 2
14 3
13 4
 */
