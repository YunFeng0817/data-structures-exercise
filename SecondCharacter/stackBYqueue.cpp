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
            cout<<"队列已空"<<endl;
            exit(0);
        }
        length--;
        cellElement *temp=front->next;
        front->next=temp->next;
        tempD=temp->data;
        cout<<temp->data<<endl;
        //cout<<"Out"<<endl;
        delete(temp);
        if(front->next==NULL)
            front=rear;
        return tempD;
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
            //cout<<"pop1"<<endl;
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
            //cout<<"pop2"<<endl;
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
};

int main()
{
    double x=3.145;
    stack stack1;
    stack1.push(x);
    stack1.push(x-1);
    stack1.push(x-2);
    stack1.top();
    stack1.top();
    stack1.top();
//    cout<<stack1.top()<<endl;
//    cout<<stack1.top()<<endl;
//    cout<<stack1.top()<<endl;
//    cout<<stack1.top()<<endl;
//    cout<<stack1.top()<<endl;
    return 0;
}
