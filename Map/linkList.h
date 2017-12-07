//
// Created by Fitz on 2017/12/7.
//

#ifndef SCORE_SYSTEM_LINKLIST_H
#define SCORE_SYSTEM_LINKLIST_H

template <class Type>
class linkList {
    struct cellElement
    {
        cellElement *next;
        Type data;
    };

    cellElement* head;
    int size;  //链表的长度
    linkList();

    bool empty();  //判断链表是否为空

    bool insert(int place,Type d);  //往链表的指定位置插入元素

    Type inquire(int place);

    bool pop(int place);
};


#endif //SCORE_SYSTEM_LINKLIST_H
