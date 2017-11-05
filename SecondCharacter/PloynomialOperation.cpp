//
// Created by Fitz on 2017/11/5.
//
#include<iostream>
using namespace std;
typedef struct cellElement{
    cellElement *link;
    int coef,exp;
}cellElement;

cellElement * attach(int c,int e,cellElement *d)
{
    cellElement *p = new cellElement;
    d->link=p;
    p->link=NULL;
    p->coef=c;
    p->exp=e;
    return p;
}

cellElement * padd(cellElement *a,cellElement *b)
{
    cellElement *p,*q,*d,*c;
    c=new cellElement;
    d=c;
    int temp;
    p=a->link;
    q=a->link;
    while((!p->link==NULL)&&(!q->link==NULL))
    {
        if(p->exp==q->exp)
        {
            temp=p->coef+q->coef;
            if(temp)
            {
                d=attach(temp,p->exp,d);
            }
            p=p->link;
            q=q->link;
        }
        else if(p->exp>q->exp)
        {
            d=attach(p->coef,p->exp,d);
            p=p->link;
        }
        else
        {
            d=attach(q->coef,q->exp,d);
            q=q->link;
        }
    }
    while(p!=NULL)
    {
        d=attach(p->coef,p->exp,d);
        p=p->link;
    }
    while(q!=NULL)
    {
        d=attach(q->coef,q->exp,d);
        q=q->link;
    }
    d->link=NULL;
    p=c;
    c=c->link;
    delete(p);
    return c;
}

int main()
{

    return 0;
}