//
// Created by Fitz on 2017/11/4.
//

#include <iostream>
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
        rear->next=new cellElement;
        rear=rear->next;
        rear->next=NULL;
        rear->data=temp;
        cout<<rear->data<<endl;
    }

    double OutQueue()
    {
        double tempD;
        if(Empty())
        {
            cout<<"╤сапря©у"<<endl;
            exit(0);
        }
        cellElement *temp=front->next;
        front->next=temp->next;
        tempD=temp->data;
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

int main()
{
    queue a;
    double x=3.145;
    a.InQueue(x);
    cout<<a.OutQueue()<<endl;
    return 0;
}
