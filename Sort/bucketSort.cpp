//
// Created by Fitz on 2017/12/17.
//
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include "linkList.h"
using namespace std;
#define Max 100
#define BUCKET_NUM 100000
#define BUCKET_SIZE 1000
int array_1[BUCKET_NUM*BUCKET_SIZE], array_2[BUCKET_NUM*BUCKET_SIZE], array_3[BUCKET_NUM*BUCKET_SIZE];
int count[10];
int tmp[10];


typedef struct b
{
    int key;
    int count;
    struct b *next;
} bucket_t;

typedef struct
{
    int a, b;
} data_t;

typedef struct b1
{
    data_t data;
    int count;
    struct b1 *next;
} bucket1_t;

bucket_t *new_bucket(int key)
{
    bucket_t *ptr = (bucket_t *)malloc(sizeof(bucket_t));
    memset(ptr, 0, sizeof(bucket_t));
    ptr->key = key;
    return ptr;
}

void free_bucket(bucket_t *first)
{
    bucket_t *ptr = first;
    while(ptr)
    {
        first = ptr;
        ptr = ptr->next;
        free(first);
    }
}

void bucketSort(int array[],int length)
{
    int i, j = 0, pos;
    bucket_t *ptr, *last;
    bucket_t *buckets[BUCKET_NUM] = {NULL};
    for(i = 0; i < length; i++)
    {
        pos = (array[i] - (array[i] % BUCKET_SIZE))/BUCKET_SIZE;
        if(buckets[pos])
        {
            ptr = buckets[pos];
            last = ptr;
            while(ptr && ptr->key < array[i])
            {
                last = ptr;
                ptr = ptr->next;
            }
            if(ptr && ptr->key == array[i])
                ptr->count++;
            else
            {
                ptr = new_bucket(array[i]);
                ptr->next = last->next;
                last->next = ptr;
            }
        }
        else
            buckets[pos] = new_bucket(array[i]);
    }

    for(i = 0; i < BUCKET_NUM; i++)
    {
        ptr = buckets[i];
        while(ptr)
        {
            while(ptr->count >= 0)
            {
                array[j] = ptr->key;
                j++; ptr->count--;
            }
            ptr = ptr->next;
        }
        free_bucket(buckets[i]);
    }
}

void countSort(int array[],int length)
{
    int i, j=0;
    int count[BUCKET_SIZE*BUCKET_NUM] = {0};
    for(i = 0; i < length; i++)
        count[array[i]]++;

    for(i = 0; i < BUCKET_NUM*BUCKET_SIZE; i++)
    {
        while(count[i])
        {
            array[j] = i;
            count[i]--; j++;
        }
    }
}

int main()
{
    for(int i = 0; i < BUCKET_NUM*BUCKET_SIZE; i++)
    {
        array_1[i] = rand() % BUCKET_NUM*BUCKET_SIZE;
    }
    double time;
    time=clock();
    bucketSort(array_1,BUCKET_NUM*BUCKET_SIZE);
    time=clock()-time;
    cout<<"排序随机数的数据规模是"<<Max<<endl<<"用时为：\t";
    cout<<time<<endl;
    time=clock();
    countSort(array_1,BUCKET_NUM*BUCKET_SIZE);
    time=clock()-time;
    cout<<"排序随机数的数据规模是"<<Max<<endl<<"用时为：\t";
    cout<<time<<endl;
//    RadixSort(num,Max);
//    for(int i=0;i<Max;i++)
//        cout<<num[i]<<" ";
//    cout<<endl;
    return 0;
}
