//
// Created by Fitz on 2017/12/7.
//
#include <iostream>
#include "linkList.h"
using namespace std;

//此处这样写是因为c++ template的函数的具体实现一般需要和声明放在一起（即放在.h文件中），但是我想要分开写，只能添加这些字段
template class linkList<int>;
template class linkList<float>;
template class linkList<char>;
template class linkList<double>;

template <typename Type>
linkList<Type>::linkList() {
    head=new cellElement;
    head->next= nullptr;
    size=0;
}

template <typename Type>
bool linkList<Type>::empty(){
    return !(bool)head->next;
}

template <typename Type>
bool linkList<Type>::insert(int place,Type d) {
    if(place>size+1)
        return false;
    cellElement *p,*pr=head,*temp;
    for(int i=0;i<place;i++)
    {
        pr=pr->next;
    }
    p=pr->next;
    temp=new cellElement;
    temp->data1=d;
    temp->next=p;
    pr->next=temp;
    size++;
    return true;
}

template <typename Type>
typename linkList<Type>::cellElement *linkList<Type>::inquire(int place) {
    if(empty()||place>size||place==0)
        return nullptr;
    cellElement *p=head;
    for(int i=0;i<place;i++)
    {
        p=p->next;
    }
    return p;
}

template <typename Type>
bool linkList<Type>::insert(int place,Type d1,Type d2){
    if(place>size+1)
        return false;
    cellElement *p,*pr=head,*temp;
    for(int i=0;i<place;i++)
    {
        pr=pr->next;
    }
    p=pr->next;
    temp=new cellElement;
    temp->data1=d1;
    temp->data2=d2;
    temp->next=p;
    pr->next=temp;
    size++;
    return true;
}

template <typename Type>
bool linkList<Type>::pop(int place) {
    if(empty()||place>size||place==0)
        return false;
    cellElement *p=head,*pr=head;
    for(int i=0;i<place;i++)
    {
        pr=p;
        p=p->next;
    }
    pr->next=p->next;
    delete(p);
    size--;
    return true;
}
