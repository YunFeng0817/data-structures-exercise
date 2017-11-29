//coding=utf-8
// Created by Fitz on 2017/10/27.
//
#include <iostream>
#include <fstream>
using namespace std;
typedef struct cellElement{
    cellElement *next;
    string name;
    string brand;   //表示品牌
    int id,price ,amount;
}cellElement;

class chain{

public:
    cellElement *head;
    cellElement *previous = head;
    string FilePath="";

    chain(){
        head->next=NULL;
    }

    void insert(int id,string n,string b,int price,int a)
    {
        if(head->next==NULL){
            cellElement *p = new cellElement;
            head->next = p;
            p->id=id;
            p->next=NULL;
            p->name=n;
            p->brand=b;
            p->price=price;
            p->amount=a;
            //此处未判断传入的参数是否为空
        }

        else{
            cellElement *pr=head;
            cellElement *p=pr->next;
            while(p!=NULL)
            {
                if(p->price>=price)
                {
                    cellElement *temp = new cellElement;
                    temp->id=id;
                    temp->name=n;
                    temp->brand=b;
                    temp->price=price;
                    temp->amount=a;
                    temp->next = pr->next;
                    pr->next = temp;
                    return ;
                }
                pr=p;
                p=p->next;
            }
            cellElement *temp = new cellElement;
            temp->id=id;
            temp->next=NULL;
            temp->name=n;
            temp->brand=b;
            temp->price=price;
            temp->amount=a;
            pr->next=temp;
        }
    }

    cellElement* loate(int id){
        if(head->next==NULL){
            return NULL;   //此处注意意外情况
        }
        else{
            previous = head;
            cellElement *p = previous->next;
            while (p!=NULL){
                if(p->id==id)
                {
                    return p;
                }
                previous = p;
                p=p->next;
            }
            return NULL;
        }
    }

    void Delete(int id){
        cellElement *temp = this->loate(id);
        if(temp==NULL){
            return;
        }
        else{
            cellElement *p;
            p = previous->next;//previous->next;
            if(p->next==NULL){
                previous->next=NULL;
            }
            else{
                previous->next=p->next;
            }
            delete(p);
        }
    }

    void AddAmount(int id,int AddAmount){
        cellElement *p = this->loate(id);
        if(p==NULL){
            if(AddAmount<0) {
                cout<<"该物品没有库存了，无法提货！"<<endl;
                return;
            }
            string a,b;
            int price;
            cout<<"数据库没有此商品，请补充该商品的信息"<<endl<<"请输入该商品的名称："<<endl;
            cin>>a;
            cout<<"请输入该商品的品牌："<<endl;
            cin>>b;
            cout<<"请输入该商品的价格："<<endl;
            cin>>price;
            cout<<"请输入该商品的库存数量："<<endl;
            cin>>AddAmount;
            this->insert(id,a,b,price,AddAmount);
            return ;
        }
        if(p->amount+AddAmount<0){
            cout<<"库存不足，无法提出如此多的货物！"<<endl;
            return;
        }
        p->amount+=AddAmount;
        cout<<"数据更新成功！"<<endl;
        return;
    }

    void modify(int id,string name,string brand,int price,int amount){
        this->Delete(id);
        this->insert(id,name,brand,price,amount);
        return;
    }

    void empty()
    {
        this->InputFile();
        ofstream DataFile;
        DataFile.open(FilePath);
        cellElement *temp=head;
        cellElement *p = head->next;
        while(p->next!=NULL){
            temp = p->next;
            DataFile<<p->id<<" "<<p->name<<" "<<p->brand<<" "<<p->price<<" "<<p->amount<<endl;
            delete(p);
            p = temp;
        }
        DataFile<<p->id<<" "<<p->name<<" "<<p->brand<<" "<<p->price<<" "<<p->amount;
        delete(p);
        return;
    }

    void display(){
        cellElement *p = head->next;
        if(head!=NULL)
        {
            cout<<"该家电的ID\t该家电的名称\t该家电的品牌是\t该家电的价格是\t该家电的库存数量是\t"<<endl;
        }
        while(p!=NULL){
            cout<<p->id<<"\t\t"<<p->name<<"\t\t"<<p->brand<<"\t\t"<<p->price<<"\t\t"<<p->amount<<endl;
            p=p->next;
        }
    }

    void ReadFromFile(){
        int price,amount,id,i=0;
        string name,brand;
        InputFile();
        ifstream DataFile;
        DataFile.open(FilePath);
        while (true){
            DataFile>>id>>name>>brand>>price>>amount;
            insert(id,name,brand,price,amount);
            if(DataFile.eof()!=0)
                break;
        }
        DataFile.close();
    }

private:
    void InputFile()
    {
        if(FilePath==""){
            cout<<"请输入文件的路径：（包括文件的名称）"<<endl;
            cin>>FilePath;
        }
    }
};

int InitMenu(){
    int choice=0;
    while(choice<=0||choice>=3){
        cout<<"######欢迎来到家电管理系统######"<<endl;
        cout<<"请选择系统的启动方式："<<endl;
        cout<<">>>1.自己录入数据，并存档"<<endl;
        cout<<">>>2.从已有的文件读取数据"<<endl;
        cout<<"请输入你的选择：(1 或 2)"<<endl;
        cin>>choice;
    }
    return choice;
}

void menu(int *choice){
    cout<<"######菜单######"<<endl;
    cout<<">>>1.进货"<<endl;
    cout<<">>>2.取货"<<endl;
    cout<<">>>3.查询某个商品的信息"<<endl;
    cout<<">>>4.输出所有商品的信息"<<endl;
    cout<<">>>5.修改某种商品的信息"<<endl;
    cout<<">>>6.增加某种商品的信息"<<endl;
    cout<<">>>7.结束营业（数据将保存到指定文件）"<<endl;
    cin>>*choice;
}

void solveChoice(int *choice,chain *Shop){
    int id,price,amount,Add;
    string name,brand;
    cellElement *p=NULL;
    switch(*choice){
        case 1:
            cout<<"请输入你进货的家电ID："<<endl;
            cin>>id;
            cout<<"请输入进货的数量："<<endl;
            cin>>Add;
            Shop->AddAmount(id,Add);
            break;
        case 2:
            cout<<"请输入你取货的家电ID："<<endl;
            cin>>id;
            cout<<"请输入你取货的数量："<<endl;
            cin>>Add;
            Shop->AddAmount(id,-Add);
            break;
        case 3:
            cout<<"请输入你想查询的家电ID："<<endl;
            cin>>id;
            p= Shop->loate(id);
            if(p==NULL){
                cout<<"该ID没有商品与之对应"<<endl;
                break;
            }
            cout<<"该商品的名称是\t"<<p->name<<"\t该商品的品牌是\t"<<p->brand<<"\t该商品的单价是\t"<<p->price<<"\t该商品的数量是\t"<<p->amount<<endl;
            break;
        case 4:
            Shop->display();
            break;
        case 5:
            cout<<"请输入你的想修改的id"<<endl;
            cin>>id;
            cout<<"请输入你修改后的信息："<<endl;
            cout<<"请在一行内依次输入: 名称，品牌，单价，库存量        (waring:如果不按照顺序输入，可能会导致程序崩溃，数据丢失)"<<endl;
            cin>>name>>brand>>price>>amount;
            Shop->modify(id,name,brand,price,amount);
            break;
        case 6:
            cout<<"请在一行内依次输入:  商品ID，名称，品牌，单价，库存量        (waring:如果不按照顺序输入，可能会导致程序崩溃，数据丢失)"<<endl;
            cin>>id>>name>>brand>>price>>amount;
            p = Shop->loate(id);
            cout<<1<<endl;
            while(p!=NULL){
                cout<<"该ID已经存在了，请重新输入一个ID值";
                cin>>id;
                p = Shop->loate(id);
            }
            cout<<1<<endl;
            Shop->insert(id,name,brand,price,amount);
            cout<<"添加成功!"<<endl;
            break;
        case 7:
            Shop->empty();
            *choice = 0;
            break;
        default:
            *choice=1;
    }
    return;
}

int main()
{
    chain Shop;
    int InitChoice;
    char flag;
    InitChoice = InitMenu();
    if(InitChoice==1)
    {
        string name,brand;
        int price,amount,id=0;
        flag='y';
        while(flag=='y'||flag=='Y'){
            cout<<"请在一行内依次输入:  商品名称，品牌，单价，库存量        (waring:如果不按照顺序输入，可能会导致程序崩溃，数据丢失)"<<endl;
            cin>>name>>brand>>price>>amount;
            Shop.insert(id,name,brand,price,amount);
            id++;
            cout<<"您是否还想继续输入？输入y(Y)或n(N)"<<endl;
            cin>>flag;
        }
    }
    else{
        Shop.ReadFromFile();
    }
    int choice=1;
    while(choice!=0){
        menu(&choice);
        solveChoice(&choice,&Shop);
    }
    cout<<"系统安全关闭，欢迎您再次使用~"<<endl;
    return 0;
}