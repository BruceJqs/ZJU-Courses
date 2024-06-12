#include<stdio.h>
#include<vector>
#include<queue>
#include<string.h>
using namespace std;

struct node{//We use Chain Forward Star to store the graph information 
	int to,next,value;
}edge[125000];

struct node1{//Define a node to store distance to ind
	int ind,dist;
	bool operator < (const node1 &x) const{//Define the < operator of node1
		return x.dist<dist;
	}
};

std::priority_queue<node1> q;//We use heap to optimize dijkstra algorithm
vector<int> pre[501];//pre[i] stores previous vertex in the minimum path
vector<int> temp;//temp stores the temporary path

int head[501];//head[i] stores the index of the head edge starting from i
int dis[501];//dis[i] stores the minimum distance from staring point to i
int bucket[501];//bucket[i] stores the times of vertex i appearing in the minimum path
bool visit[501];//visit[i] stores whether we have calculated the minimum distance of the vertex i
int total,n,m,k,c1,c2,len,T,s,t;

void add(int u,int v,int w){//Add edges
	edge[++total].to=v;//The destination is v
	edge[total].value=w;//The weight of the edge is w
	edge[total].next=head[u];//The next edge is the old head edge
	head[u]=total;//The new head edge of u is the current edge
}

void dfs(int s,int t){
	if(s==t){//We have found one minimum path
		temp.push_back(t);
		for(int i=temp.size()-2;i>=1;i--)//For the vertex appearing in the path(s and t not included),plus 1
			bucket[temp[i]]++;
		temp.pop_back();//pop to find next minimum path
		return;
	}
	temp.push_back(t);//push the vertex in the path
	for(int i=0;i<pre[t].size();i++)
		dfs(s,pre[t][i]);//dfs previous vertex
	temp.pop_back();//pop to find next minimum path
}

int main(){
	freopen("test.in","r",stdin);
	freopen("test.out","w",stdout);
	/*Readin*/
	scanf("%d %d %d",&n,&m,&k);
	for(int i=1;i<=m;i++){
		scanf("%d %d %d",&c1,&c2,&len);
		add(c1,c2,len);//add edges
	}
	/*Operation*/
	scanf("%d",&T);
	for(int i=1;i<=T;i++){
		bool flag=false;//flag stores whether there is a transporation hub or not
		scanf("%d %d",&s,&t);
		/*Clear all the arrays*/
		memset(dis,0x7f,sizeof(dis));
		memset(visit,false,sizeof(visit));
		memset(bucket,0,sizeof(bucket));
		/*Dijkstra Algorithm*/
		dis[s]=0;q.push((node1){s,0});
		while(!q.empty()){
			node1 temp=q.top();//Get the minimum vertex to start loose operation
			q.pop();//Pop the vertex from the heap
			if(visit[temp.ind])//If the minimum distance of the vertex is calculated then continue
				continue;
			visit[temp.ind]=true;
			for(int j=head[temp.ind];j;j=edge[j].next){
				int des=edge[j].to;
				if(dis[des]>dis[temp.ind]+edge[j].value){//Loose operation
					dis[des]=dis[temp.ind]+edge[j].value;
					pre[des].clear();//The old path in pre is useless,so clear them and start storing new path again
					pre[des].push_back(temp.ind);
					if(!visit[des])
						q.push((node1){des,dis[des]});
				}
				else if(dis[des]==dis[temp.ind]+edge[j].value){//If there exists a path of same distance,we also store the previous vertex
					pre[des].push_back(temp.ind);
					if(!visit[des])
						q.push((node1){des,dis[des]});
				}
			}
		}
		/*Find the path and calculate the times of of vertex appearing in the minimum path*/
		dfs(s,t);
		for(int j=0;j<n;j++)
			if(bucket[j]>=k)//A transportation hub
			{
				if(flag==false)
					printf("%d",j);
				else
					printf(" %d",j);
				flag=true;
			}
		if(flag==false)
			printf("None\n");
		else
			printf("\n");
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
