#include<stdio.h>
#include<time.h>

clock_t start,stop;
double duration;

int num[100001];

int main(void)
{
    /*Start the clock*/
    start=clock();

    /*Open the file*/
    FILE *fp1,*fp2;
    fp1=fopen("test.in","r");
    fp2=fopen("testA1.out","w");

    /*Main function*/
    int n,c,k;//flag=0 means we haven't found the pair,flag=1 means we have found the pair.
    fscanf(fp1,"%d",&n);
    for(int i=1;i<=n;i++)
        fscanf(fp1,"%d",&num[i]);
    fscanf(fp1,"%d",&k);
    for(int l=1;l<=k;l++)
    {
        int total=0,flag=0;
        fscanf(fp1,"%d",&c);
        for(int i=1;i<=n;i++)
            for(int j=i+1;j<=n;j++)//Enumerate all possible pairs
                if(num[i]+num[j]==c)//Check whether their sum is c
                {
                    flag=1;//We have found the answer
                    fprintf(fp2,"No.%6d : %6d + %6d = %6d\n",++total,num[i],num[j],c);
                }
        if(flag==0)//If there is no answer
            fprintf(fp2,"Cannot find the possible <a,b>!\n");
        fprintf(fp2,"\n");
    }

    /*Stop the clock*/
    stop=clock();
    duration = ((double)(stop-start))/CLOCKS_PER_SEC;
    fprintf(fp2,"The iteration is:%d\n",k);
    fprintf(fp2,"The ticks are:%lu\n",stop-start);
    fprintf(fp2,"The total time is:%.6lf(sec)\n",duration);
    fprintf(fp2,"The duration is:%.6lf(sec)\n",duration/k);

    /*Close the file*/
    fclose(fp1);
    fclose(fp2);

    return 0;
}