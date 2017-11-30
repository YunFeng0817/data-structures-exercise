//
// Created by Fitz on 2017/11/29.
//
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
string getArticle();
void statistics(string getArticle);
int character[257];

class cellElement
{
public:
    int weight,lchild,rchild;
    cellElement()
    {
        weight=0;
        lchild=-1;
        rchild=-1;
    }
};

class huffmanTree
{
public:
    int frequency[257];
    string codeRule[257],temp,result;
};

string getArticle()  //这是统计英语文章中字符出现频率的函数
{
    string getArticle;
    for(int i=0;i<256;i++)
        character[i]=0;
    string filePath;
    char temp;
    cout<<"请输入要压缩处理的英文文章的路径"<<endl;
    cin>>filePath;
    ifstream englishArticle(filePath,ios::in);
    if(!englishArticle.is_open())
    {
        cout<<"打开文件失败,请输入有效路径"<<endl;
        exit(0);
    }
    stringstream article;
    article>>englishArticle.rdbuf();
    getArticle=article.str();
    englishArticle.close();
    return getArticle;
}

void statistics(string getArticle)
{
    for(int i=0;i<256;i++)
    {
        character[i]=0;
    }
    for(int i=0;i<getArticle.size();i++)
    {
        character[int(getArticle[i])]++;
    }
}

int main()
{
    statistics(getArticle());
    return 0;
}
