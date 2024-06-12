#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define MAXN 10000//Change the parameter here.

const int MAXM=5,MAXV=MAXN*10;//Change the parameter here.

int num[MAXN];

int search(int l,int r,int target)
{
    for(int i=l;i<=r;i++)
        if(num[i]==target)
            return 1;
    return 0;
}

int main(void)
{
    srand((unsigned int)time(NULL));
    FILE *fp;
    fp=fopen("test.in","w");
    fprintf(fp,"%d\n",MAXN);
    int maxnum=-0x7f;
    for(int i=1;i<=MAXN;i++)
    {
        int x=rand();
        while((x<=0)||(x>MAXV)||(search(1,i-1,x)))
            x=rand();
        if(x>maxnum)
            maxnum=x;
        fprintf(fp,"%d ",x);
        num[i]=x;
    }
    fprintf(fp,"\n");
    fprintf(fp,"%d\n",MAXM);
    for(int i=1;i<=MAXM;i++)
    {
        int x=rand();
        while((x<=0)||(x>maxnum))
            x=rand();
        fprintf(fp,"%d\n",x);
    }
    fclose(fp);
    return 0;
}