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

    void push(double temp,bool ifINT)
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

    cellElement * top()
    {
        if(Empty())
            return NULL;
        else
            return (head->next);
    }

};

class queue
{
    stack stack1, stack2;

};

int main()
{

}

