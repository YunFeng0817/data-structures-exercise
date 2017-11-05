//
// Created by Fitz on 2017/11/4.
//
#include <iostream>
using namespace std;

//这个类是基本的由指针构成的栈结构

typedef struct cellElement{
    cellElement *next;
    double data;
}cellElement;

class stack
{
public:
    cellElement *head=new cellElement;
    int length=0;

    stack(){
        length=0;
        head->next=NULL;
    }

    void push(double temp)
    {
        cellElement *cell = new cellElement;
        if(length==0)
        {
            head->next=cell;
            cell->next=NULL;
        }
        else{
            cell->next=head->next;
            head->next=cell;
        }
        cell->data = temp;
        length++;
        return;
    }

    double pop() //在调用pop()前要判断是否为空
    {
        if(Empty())
        {
            cout<<"栈已经为空"<<endl;
            exit(0);
        }
        double x;
        cellElement *temp = head->next;
        head->next = temp->next;
        x = temp->data;
        delete(temp);
        length--;
        return x;
    }

    bool Empty()
    {
        if(head->next==NULL)
            return true;
        else
            return false;
    }

    double top()
    {
        return head->next->data;
    }

};

class queue
{
public:
    stack stack1, stack2;
    int length;

    queue()
    {
        length=0;
    }

    bool Empty()
    {
        if(!stack1.Empty())
        {
            int temp=stack1.length;
            for (int i = 0; i < temp; i++)
            {
                stack2.push(stack1.pop());
            }
        }
        if(stack2.Empty())
            return true;
        return false;
    }

    void InQueue(double temp)
    {
        stack1.push(temp);
        length++;
    }

    double OutQueue()
    {
        if(Empty())
        {
            cout<<"队列已空"<<endl;
            exit(0);
        }
        else
        {
            if(stack2.Empty()&&!stack1.Empty())
            {
                int temp=stack1.length;
                for (int i = 0; i < temp; i++)
                {
                    stack2.push(stack1.pop());
                }
            }
            length--;
            return stack2.pop();
        }
    }

    double first()
    {
        if(!stack2.Empty())
        {
            return stack2.top();
        }
        if(!stack1.Empty())
        {
            int temp=stack1.length;
            for (int i = 0; i < temp; i++)
            {
                stack2.push(stack1.pop());
            }
        }
        else
        {
            cout<<"队列已空"<<endl;
            exit(0);
        }
    }
};

int main()
{
//    queue a;
//    a.InQueue(3.12334);
//    a.InQueue(43554);
//    a.InQueue(1);
//    int temp=a.length;
//    for(int i=0;i<temp;i++)
//        cout<<a.first()<<endl;
//    return 0;

    double x;
    queue a;
    while(x!=0)
    {
        cin>>x;
        a.InQueue(x);
    }
    while(!a.Empty())
    {
        cout<<"first:  "<<a.first()<<endl;
        cout<<"out:  "<<a.OutQueue()<<endl;
    }
    return 0;
}

