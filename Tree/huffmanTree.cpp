//
// Created by Fitz on 2017/11/29.
//
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
#define codeNum 256
void getArticle();
void statistics();
int character[codeNum+1];
string Article;

struct CellElement
{
    int pority;   //编码节点的权重
    int pocessID; //编码的ID
};

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

class heapmin
{
public:
    int size;
    int Maxlength;
    CellElement *Elements;
    heapmin(int length)
    {
        size=0;
        Maxlength=length;
        Elements=new CellElement[Maxlength];
    }

    bool empty()
    {
        if(size==0)
            return true;
        return false;
    }

    bool full()
    {
        return (size==Maxlength-1);
    }

    bool insert(int p,int ID)
    {
        int i=size+1;
        if(!full())
        {
            size++;
            while(i!=1&&p<Elements[i/2].pority)
            {
                Elements[i].pority=Elements[i/2].pority;
                Elements[i].pocessID=Elements[i/2].pocessID;
                i=i/2;
            }
            Elements[i].pocessID=ID;
            Elements[i].pority=p;
            return true;
        }
        return false;
    }

    CellElement top()
    {
        return Elements[1];
    }

    bool DeleteMin()
    {
        int i=1,min;
        CellElement last;
        if(!empty())
        {
            last=Elements[size];
            size--;
            while(2*i<=size)
            {
                if(2*i+1<=size)
                    min=Elements[2*i].pority<Elements[2*i+1].pority?Elements[2*i].pority:Elements[2*i+1].pority;
                else
                    min=Elements[2*i].pority;
                if(last.pority>=min)
                {
                    if(2*i+1>size||Elements[2*i].pority<Elements[2*i+1].pority)
                    {
                        Elements[i]=Elements[2*i];
                        i=2*i;
                    }
                    else
                    {
                        Elements[i]=Elements[2*i+1];
                        i=2*i+1;
                    }
                }
                else
                    break;
            }
            Elements[i]=last;
        }
        return false;
    }
};

heapmin sortedNum(codeNum+1);

class huffmanTree
{
public:
    int * frequency,root;
    string codeRule[codeNum+1],temp,encodeResult,decodeResult;
    cellElement HT[2*codeNum-1];
    huffmanTree(int *temp)
    {
        frequency=temp;
        //初始化小根堆
        for(int i=0;i<codeNum;i++)
        {
            sortedNum.insert(frequency[i],i);
        }
    }

    void establishTree()
    {
        int sum;
        for(int i=codeNum,i<2*codeNum-1;i++)
        {
            sum=0;
            HT[i].lchild=sortedNum.top().pocessID;
            sum+=sortedNum.top().pority;
            sortedNum.DeleteMin();
            HT[i].rchild=sortedNum.top().pocessID;
            sum+=sortedNum.top().pority;
            sortedNum.DeleteMin();
            HT[i].weight=sum;
            sortedNum.insert(HT[i].weight,i);
        }
        root=sortedNum.top().pocessID;
    }

    //通过遍历哈夫曼树得到相应的编码规则
    void getCodeRule(int index)
    {
        if(index!=-1)
        {
            if(HT[index].lchild==-1&&HT[index].rchild==-1)
                codeRule[index]=temp;
            temp+='0';
            getCodeRule(HT[index].lchild);
            temp+='1';
            getCodeRule(HT[index].rchild);
            temp.pop_back();
        }
        else
        {
            temp.pop_back();
        }
    }

    void encode()
    {
        for(int i=0;i<Article.size();i++)
        {
            encodeResult+=codeRule[int(Article[i])];
        }
    }

    void decode(string * input)
    {
        int index=sortedNum.top().pocessID;
        for(int i=0;i<input->size();i++)
        {
            if(input[i]==0)
            {
                if(HT[index].lchild!=-1)
                    index=HT[index].lchild;
                else
                {
                    decodeResult+=char(index);
                    index=sortedNum.top().pocessID;
                }
            }
        }
    }

};

void getArticle()  //这是统计英语文章中字符出现频率的函数
{
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
    Article=article.str();
    englishArticle.close();
}

void statistics()
{
    for(int i=0;i<256;i++)
    {
        character[i]=0;
    }
    for(int i=0;i<Article.size();i++)
    {
        character[int(Article[i])]++;
    }
}

int main()
{
    getArticle();
    statistics();
    return 0;
}
