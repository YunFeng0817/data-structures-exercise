#include <iostream>
//#include<string>
#include<cstdio>
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
    int max_num,max_index=0;
	double num[100];
	for(int i=0;i<100;i++)
	{
		num[i]=i*100+5000;
	}
	max_num = num[0];
	for(int i=1;i<100;i++)
	{
		if(num[i]>max_num)
		{
			max_num = num[i];
			max_index = i;
		}
	}
	cout<<"最大的数是"<<max_num<<endl<<"最大的数的位置是<"<<max_index<<endl;
	return 0;
}
