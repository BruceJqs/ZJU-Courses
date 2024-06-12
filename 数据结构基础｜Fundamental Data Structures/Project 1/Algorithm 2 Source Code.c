#include<stdio.h>
#include<time.h>

clock_t start,stop;
double duration;

int num[100001];

/*Quick_Sort Algorithm Code*/
void quick_sort(int l,int r)
{
    int i,j,mid,temp;
    i=l;j=r;mid=num[(l+r)/2];//Set num[(l+r)/2] as the standard.Numbers smaller go left and numbers bigger go right.
    do{//Distribute numbers in the left and right area
        while(num[i]<mid)//Numbers smaller remain in the left area
            i++;
        while(num[j]>mid)//Numbers bigger remain in the right area
            j--;
        if(i<=j)
        {
            temp=num[i];num[i]=num[j];num[j]=temp;//Swap num[i] and num[j]
            i++;j--;
        }
    }while(i<=j);//If i>j,then the distribution is over and correct.
    if(l<j)
        quick_sort(l,j);//Continue sorting the left area
    if(i<r)
        quick_sort(i,r);//Continue sorting the right area
}

/*Binary Search Algorithm Code*/
int binary_search(int l,int r,int target)
{
    while(l<=r)
    {
        int mid=(l+r)/2;
        if(target<num[mid])
            r=mid-1;//Search the left area of the array;
        else if(target>num[mid])
            l=mid+1;//Search the right area of the array;
        else//We found the target
            return 1;
    }
    return 0;//If l>r,then there's no target in the array
}

int main(void)
{
    /*Start the clock*/
    start=clock();

    /*Open the file*/
    FILE *fp1,*fp2;
    fp1=fopen("test.in","r");
    fp2=fopen("testA2.out","w");

    /*Main function*/
    int n,c,k;
    fscanf(fp1,"%d",&n);
    for(int i=1;i<=n;i++)
        fscanf(fp1,"%d",&num[i]);
    quick_sort(1,n);//Sort the numbers to operate binary search
    fscanf(fp1,"%d",&k);
    for(int l=1;l<=k;l++)
    {
        fscanf(fp1,"%d",&c);
        int flag=0,total=0;
        for(int i=1;i<=n;i++)
            if((num[i]<=(c-1)/2)&&binary_search(1,n,c-num[i]))//To avoid repetition,we enumerate numbers no bigger than (c-1)/2.
            {
                flag=1;//We have found the answer
                fprintf(fp2,"No.%6d : %6d + %6d = %6d\n",++total,num[i],c-num[i],c);
            }
        if(flag==0)//We haven't found the answer
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