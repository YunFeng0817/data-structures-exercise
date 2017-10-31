//
// Created by Fitz on 2017/10/31.
//

#include <iostream>
using namespace std;

string operation = "+-*/()";

typedef union charOrInt{
    int num;
    char op;
}charOrInt;


typedef struct cellElement{
    cellElement *next;
    charOrInt data;
}cellElement;

//这个类是基本的由指针构成的栈结构
class stack
{
public:
    cellElement *head=new cellElement;
    int length=0;

    stack(){
        length=0;
        head->next=NULL;
    }

    void push(charOrInt temp)
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

    charOrInt pop() //在调用pop()前要判断是否为空
    {
        charOrInt x;
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

    charOrInt * top()
    {
        if(Empty())
            return NULL;
        else
            return &(head->next->data);
    }

};

//这个类是用于将中缀表达式转化为后缀表达式
class mid2tail:stack
{
    stack max;
    stack OpChar;

    void push(char temp)
    {
        charOrInt x;
        x.op = temp;
        OpChar.push(x);
        if(max.Empty())
            max.push(x);
        else if(operation.find((*max.top()).op)<operation.find(x.op))
            max.push(x);
        else;
    }

    char pop()
    {
        char x;
        charOrInt temp;
        temp=OpChar.pop();
        x=temp.op;
        if(operation.find((*max.top()).op)==operation.find(temp.op))
            max.pop();
        return x;
    }
};


int main()
{
    return 0;
}