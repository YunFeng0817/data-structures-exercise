//
// Created by Fitz on 2017/11/4.
//

#include <iostream>
#include <cstdlib>
using namespace std;

typedef struct cellElement{
    cellElement *next;
    double data;
}cellElement;

class queue
{
public:
    cellElement *front,*rear;
    int length;
    queue()
    {
        length=0;
        front=new cellElement;
        front->next=NULL;
        rear=front;
    }

    void InQueue(double temp)
    {
        length++;
        rear->next=new cellElement;
        rear=rear->next;
        rear->next=NULL;
        rear->data=temp;
    }

    double OutQueue()
    {
        double tempD;
        if(Empty())
        {
            cout<<"栈已经为空"<<endl;
            exit(0);
        }
        else
        {
            length--;
            cellElement *temp,*temp1=NULL;
            temp=front->next->next;
            tempD=front->next->data;
            if(temp==NULL)
                front=rear;
            delete (front->next);
            front->next=temp;
            return tempD;
        }
    }

    bool Empty()
    {
        if(rear==front)
            return true;
        else
            return false;
    }

    double first()
    {
        return front->next->data;
    }
};

class stack
{
public:
    queue queue1,queue2;
    int length;

    stack()
    {
        length=0;
    }

    void push(double temp)
    {
        if(!queue1.Empty())
        {
            queue1.InQueue(temp);
            length++;
        }
        else if(!queue2.Empty())
        {
            queue2.InQueue(temp);
            length++;
        }
        else
        {
            queue1.InQueue(temp);
            length++;
        }
    }

    double pop()
    {
        if(!queue1.Empty())
        {
            int temp1=queue1.length;
            for(int i=0;i<temp1-1;i++)
            {
                queue2.InQueue(queue1.OutQueue());
            }
            length--;
            return queue1.OutQueue();
        }
        else if(!queue2.Empty())
        {
            int temp2=queue2.length;
            for(int i=0;i<temp2-1;i++)
            {
                queue1.InQueue(queue2.OutQueue());
            }
            length--;
            return queue2.OutQueue();
        }
        cout<<"栈已经为空"<<endl;
        exit(0);
    }

    double top()
    {
        if(!queue1.Empty())
        {
            double t;
            int temp1=queue1.length;
            for(int i=0;i<temp1-1;i++)
            {
                queue2.InQueue(queue1.OutQueue());
            }
            t=queue1.OutQueue();
            queue2.InQueue(t);
            return t;
        }
        else if(!queue2.Empty())
        {
            double t;
            int temp2=queue2.length;
            for(int i=0;i<temp2-1;i++)
            {
                queue1.InQueue(queue2.OutQueue());
            }
            t=queue2.OutQueue();
            queue1.InQueue(t);
            return t;
        }
        cout<<"栈已经为空"<<endl;
        exit(0);
    }
    bool Empty()
    {
        if(queue1.Empty()&&queue2.Empty())
            return true;
        return false;
    }
};

int main()
{
    double x;
    stack queue1;
    while(x!=0)
    {
        cin>>x;
        queue1.push(x);
    }
    while(!queue1.Empty())
    {
        cout<<"top:  "<<queue1.top()<<endl;
        cout<<"out:  "<<queue1.pop()<<endl;
    }
    return 0;
}
