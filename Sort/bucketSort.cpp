//
// Created by Fitz on 2017/12/17.
//
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include "linkList.h"

using namespace std;
#define Max 60000000
#define bucketNum 5000000
#define madix 10
#define MaxRandom 10000000
int randomNum1[Max], randomNum2[Max], randomNum3[Max], randomNum4[Max];
int temp1[Max + 1];
int temp2[Max + 1];
linkList<int> bucket[bucketNum];

void bucketSort(int num[], int length) {
    int flag;
    for (int i = 0; i < length; i++) {
        if (bucket[num[i] >> 1].size == 0)
            bucket[num[i] >> 1].insert(0, num[i]);
        else {
            flag = 0;
            for (int j = 1; j <= bucket[num[i] >> 1].size; j++) {
                if (bucket[num[i] >> 1].inquire(j)->data1 > num[i]) {
                    bucket[num[i] >> 1].insert(j - 1, num[i]);
                    flag = 1;
                    break;
                }
            }
            if (flag == 0)
                bucket[num[i] >> 1].insert(bucket[num[i] >> 1].size, num[i]);
        }
    }
    int count = 0;
    for (int i = 0; i < bucketNum; i++) {
        for (int j = 1; j <= bucket[i].size; j++) {
            num[count] = bucket[i].inquire(j)->data1;
            bucket[i].pop(j);    //释放内存，防止内存泄漏
            count++;
        }
    }
}

void countSortEasy(int num[], int length, int maxNum) {
    memset(temp1, 0, sizeof(int) * (maxNum + 1));
    for (int i = 0; i < length; i++)
        temp1[num[i]]++;
    int c = 0;
    for (int i = 0; i <= maxNum; i++) {
        for (int j = 0; j < temp1[i]; j++) {
            num[c] = i;
            c++;
        }
    }
}

void countSortComplex(int num[], int length, int maxNum) {
    int better1, better2, better3;
    memset(temp1, 0, sizeof(int) * (maxNum + 1));
    for (int i = 0; i < length; i++)
        temp1[num[i]]++;
    int x;
    for (x = 0; x < length - 4; x += 3) {
        better1 = temp1[x] + temp1[x + 1];
        better2 = temp1[x] + (temp1[x + 1] + temp1[x + 2]);
        temp1[x + 1] = better1;
        better3 = better1 + (temp1[x + 2] + temp1[x + 3]);
        temp1[x + 2] = better2;
        temp1[x + 3] = better3;
    }
    for (; x < maxNum - 1; x++) {
        temp1[x + 1] = temp1[x] + temp1[x + 1];
    }
//    for(int i=0;i<maxNum-1;i++)
//    {
//        temp1[i+1]=temp1[i]+temp1[i+1];
//    }
    for (int i = length - 1; i >= 0; i--) {
        temp2[temp1[num[i]] - 1] = num[i];
        temp1[num[i]]--;
    }
    for (int i = 0; i < length; i++) {
        num[i] = temp2[i];
    }
}

void madixSort(int num[], int length, int max) {
//    int max=num[0];
//    for(int i=0;i<length-1;i++)
//    {
//        if(max<num[i+1])
//            max=num[i+1];
//    }
    int temp = 1;
    int stash;
    memset(temp1, 0, sizeof(int) * (max + 1));
    while (max / temp) {
        for (int i = 0; i < length; i++)
            temp1[(num[i] / temp) % madix]++;
        for (int i = 0; i < madix; i++) {
            temp1[i + 1] = temp1[i] + temp1[i + 1];
        }
        for (int i = length - 1; i >= 0; i--) {
            stash = (num[i] / temp) % madix;
            temp2[temp1[stash] - 1] = num[i];
            temp1[stash]--;
        }
        memset(temp1, 0, sizeof(int) * (max + 1));
        for (int i = 0; i < length; i++) {
            num[i] = temp2[i];
        }
        temp *= madix;
    }
}

int main() {
    int temp;
    for (int i = 0; i < Max; i++) {
        temp = rand() % MaxRandom;
        randomNum1[i] = temp;
        randomNum2[i] = temp;
        randomNum3[i] = temp;
        randomNum4[i] = temp;
    }
    cout << endl;
    double time;
    time = clock();
//    sort(randomNum1,&randomNum1[Num],greater<int>());  //从大到小排序
//    qsort(randomNum1,Max, sizeof(int),cmp);   //从小到大排序
    sort(randomNum1, &randomNum1[Max]);
    time = clock() - time;
    cout << "排序随机数的数据规模是" << Max << endl << "STL快排的用时为：\t";
    cout << time / 1000 << "s" << endl;
    time = clock();
    countSortComplex(randomNum2, Max, Max);
    time = clock() - time;
    cout << "计数排序（可用于基数排序，多占内存版本）的数据规模是" << Max << endl << "用时为：\t";
    cout << time / 1000 << "s" << endl;
    time = clock();
    countSortEasy(randomNum3, Max, Max);
    time = clock() - time;
    cout << "计数排序(省内存版本)的数据规模是" << Max << endl << "用时为：\t";
    cout << time / 1000 << "s" << endl;
    time = clock();
    madixSort(randomNum4, Max, Max);
    time = clock() - time;
    cout << "基数排序的数据规模是" << Max << endl << "用时为：\t";
    cout << time / 1000 << "s" << endl;
    for (int i = 0; i < Max; i++) {
        if (randomNum1[i] != randomNum2[i]) {
            cout << i << endl;
            cout << randomNum1[i] << "  " << randomNum2[i] << endl;
        }
        if (randomNum1[i] != randomNum3[i]) {
            cout << i << endl;
            cout << randomNum1[i] << "  " << randomNum2[i] << endl;
        }
        if (randomNum1[i] != randomNum4[i]) {
            cout << i << endl;
            cout << randomNum1[i] << "  " << randomNum2[i] << endl;
        }
    }
    return 0;
}
