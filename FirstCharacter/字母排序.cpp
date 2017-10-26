#include <iostream>
//#include<string>
#include<cstdio>
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int trans(char a)
{
    if(a>='A'&&a<='Z')
        return a-'A';
    else if(a>='0'&&a<='9')
        return a-'0'+26;
    else
        return -1;
}

int main(int argc, char** argv) {
    char a[8][100]={"PAB","5C","PABC","CXY","CRSI","7","B899","B9"};
	int j,temp1;
	char temp2;
	for(int x=0;x<8;x++)
	{
		for(int i=0;a[x][i]!='\0';i++)
	    {
	        j=i;
	        int minim=trans(a[x][i]);
	        for(int k=i+1;a[x][k]!='\0';k++)
	        {
	            temp1=trans(a[x][k]);
	            if(temp1<minim)
	            {
	                j=k;
	                minim = temp1;
	            }
	        }
	        if(j!=i)
	        {
	            temp2 = a[x][i];
	            a[x][i] = a[x][j];
	            a[x][j] = temp2;
	        }
	    }
	    cout<<a[x]<<endl;
	}
	return 0;
}
