//
// Created by Fitz on 2017/12/7.
//

#include "linkList.h"
linkList::linkList() {
    head=new cellElement;
    head->next= nullptr;
    size=0;
}

bool linkList::empty(){
    return !(bool)head->next;
}

template <typename Type>
bool linkList::insert(int place,Type d) {
    if(place>size+1)
        return false;
    cellElement *p,*pr=head,*temp;
    for(int i=0;i<place;i++)
    {
        pr=pr->next;
    }
    p=pr->next;
    temp=new cellElement;
    temp->data=d;
    temp->next=p;
    pr->next=temp;
    size++;
    return true;
}

template <typename Type>
Type linkList::inquire(int place) {
    if(empty()||place>size||place==0)
        return -1;
    cellElement *p=head;
    for(int i=0;i<place;i++)
    {
        p=p->next;
    }
    return p->data;
}

bool linkList::pop(int place) {
    if(empty()||place>size||place==0)
        return false;
    cellElement *p=head,*pr=head;
    for(int i=0;i<size;i++)
    {
        pr=p;
        p=p->next;
    }
    pr->next=p->next;
    delete(p);
    return true;
}

