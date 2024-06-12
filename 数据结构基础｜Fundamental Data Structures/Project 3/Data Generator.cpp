#include<bits/stdc++.h>
using namespace std;
const int N=500,T=500,K=5,L=100;
bool visit[N+1][N+1];
int main(void){
	freopen("test.in","w",stdout);
	srand(time(0));
	int limit=N*(N-1)/2;
	int m=limit;
	int k=rand()%K+1;
	memset(visit,false,sizeof(visit));
	fprintf(stdout,"%d %d %d\n",N,m,k);
	for(int i=1;i<=m;i++){
		int c1=rand()%N,c2=rand()%N;
		while((c1==c2)||(visit[c1][c2])){
			c1=rand()%N;
			c2=rand()%N;
		}
		visit[c1][c2]=visit[c2][c1]=true;
		int len=rand()%L+1;
		fprintf(stdout,"%d %d %d\n",c1,c2,len);
	}
	memset(visit,false,sizeof(visit));
	fprintf(stdout,"%d\n",T);
	for(int i=1;i<=T;i++){
		int c1=rand()%N,c2=rand()%N;
		while((c1==c2)||(visit[c1][c2])){
			c1=rand()%N;
			c2=rand()%N;
		}
		visit[c1][c2]=visit[c2][c1]=true;
		fprintf(stdout,"%d %d\n",c1,c2);
	}
	fclose(stdout);
	return 0;
}
