//
// Created by Fitz on 2017/11/23.
//
#include <iostream>
#include <fstream>
#include <queue>
using namespace std;
struct CellElement
{
    int pority;   //优先级
    int pocessID; //进程号
};

class heapmax
{
public:
    int size;
    int Maxlength,length;
    int *ID;
    CellElement *Elements;
    heapmax(int length)
    {
        size=0;
        Maxlength=length;
        Elements=new CellElement[Maxlength];
        ID=(int *)malloc(Maxlength*sizeof(int));
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
            length=size;
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
        for(int i=0;i<length;i++)
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
                    if(2*i+1>size||Elements[2*i].pority>Elements[2*i+1].pority)
                    {
                        Elements[i]=Elements[2*i];
                        i=2*i;
                    }
                    else
                    {
                        Elements[i]=Elements[2*i+1];
                        i=2*i+1;
                    }
                }
                else
                    break;
            }
            Elements[i]=last;
        }
        return false;
    }

};

class heapmin
{
public:
    int size;
    int Maxlength;
    CellElement *Elements;
    heapmin(int length)
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
            while(i!=1&&p<Elements[i/2].pority)
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

    CellElement top()
    {
        return Elements[1];
    }

    bool DeleteMin()
    {
        int i=1,min;
        CellElement last;
        if(!empty())
        {
            last=Elements[size];
            size--;
            while(2*i<=size)
            {
                if(2*i+1<=size)
                    min=Elements[2*i].pority<Elements[2*i+1].pority?Elements[2*i].pority:Elements[2*i+1].pority;
                else
                    min=Elements[2*i].pority;
                if(last.pority>=min)
                {
                    if(2*i+1>size||Elements[2*i].pority<Elements[2*i+1].pority)
                    {
                        Elements[i]=Elements[2*i];
                        i=2*i;
                    }
                    else
                    {
                        Elements[i]=Elements[2*i+1];
                        i=2*i+1;
                    }
                }
                else
                    break;
            }
            Elements[i]=last;
        }
        return false;
    }
};

int main()
{
    heapmin temp(100);
    queue<CellElement> buffer; //用于处理相同优先级的问题
    heapmax system(100);
    fstream ReadFile;
    string filepath;
    int a=0,b=0,count=0;
    cout<<">>>请输入进程信息文件task.dat的有效路径"<<endl;
    cin>>filepath;
    ReadFile.open(filepath.c_str(),ios::in);
    if (!ReadFile.is_open())
    {
        cout << "Error opening file"<<endl;
        exit (1);
    }
    cout<<"开始读取文件……"<<endl;
    while(!ReadFile.eof())
    {
        ReadFile>>a>>b;
        system.ID[count]=a;
        count++;
        system.insert(b,a);  //先进程号后优先级
    }
    ReadFile.close();
    cout<<"读取文件完成"<<endl;
    a=system.size;
    cout<<"开始输出进程的执行顺序:"<<endl;
    for(int i=1;i<=a+1;i++)
    {
        if((!buffer.empty()&&system.top().pority<buffer.back().pority)||i==a+1)
        {
            count=buffer.front().pority;
            while(!buffer.empty())
            {
                temp.insert(system.findID(buffer.front().pocessID),buffer.front().pocessID);
                buffer.pop();
            }
            b=temp.size;
            for(int j=1;j<=b;j++)
            {
                cout<<temp.top().pocessID<<"\t"<<count<<endl;
                temp.DeleteMin();
            }
        }
        buffer.push(system.top());
        system.DeleteMax();
    }
    return 0;
}
/*
 * C:\Users\29488\Desktop\task.dat
10 0
20 1
15 2
14 3
13 4
 */
