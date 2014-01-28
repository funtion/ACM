//   O(N^3)
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
const int NMax=230;
int Next[NMax];
int spouse[NMax];
int belong[NMax];
int findb(int a){
	return belong[a]==a?a:belong[a]=findb(belong[a]);
}
void together(int a,int b){
	a=findb(a),b=findb(b);
	if (a!=b)belong[a]=b;
}
vector<int> E[NMax];
int N;
int Q[NMax],bot;
int mark[NMax];
int visited[NMax];
int findLCA(int x,int y){
	static int t=0;
	t++;
	while (1){
		if (x!=-1){
			x=findb(x);
			if (visited[x]==t)return x;
			visited[x]=t;
			if (spouse[x]!=-1)x=Next[spouse[x]];
			else x=-1;
		}
		swap(x,y);
	}
}
void goup(int a,int p){
	while (a!=p){
		int b=spouse[a],c=Next[b];
		if (findb(c)!=p)Next[c]=b;
		if (mark[b]==2)mark[Q[bot++]=b]=1;
		if (mark[c]==2)mark[Q[bot++]=c]=1;
		together(a,b);
		together(b,c);
		a=c;
	}
}
void findaugment(int s){
	for (int i=0;i<N;i++)Next[i]=-1,belong[i]=i,mark[i]=0,visited[i]=-1;
	Q[0]=s;bot=1;mark[s]=1;
	for (int head=0;spouse[s]==-1 && head<bot;head++){
		int x=Q[head];
		for (int i=0;i<(int)E[x].size();i++){
			int y=E[x][i];
			if (spouse[x]!=y && findb(x)!=findb(y) && mark[y]!=2){
				if (mark[y]==1){
					int p=findLCA(x,y);
					if (findb(x)!=p)Next[x]=y;
					if (findb(y)!=p)Next[y]=x;
					goup(x,p);
					goup(y,p);
				}else if (spouse[y]==-1){
					Next[y]=x;
					for (int j=y;j!=-1;){
						int k=Next[j];
						int l=spouse[k];
						spouse[j]=k;spouse[k]=j;
						j=l;
					}
					break;
				}else{
					Next[y]=x;
					mark[Q[bot++]=spouse[y]]=1;
					mark[y]=2;
				}
			}
		}
	}
}
int Map[NMax][NMax];
int main()
{
	scanf("%d",&N);
	int x,y;
	for (int i=0;i<N;i++)for (int j=0;j<N;j++)Map[i][j]=0;
	while (scanf("%d%d",&x,&y)!=EOF){
		x--;y--;
		if (x!=y && !Map[x][y]){
			Map[x][y]=Map[y][x]=1;
			E[x].push_back(y);
			E[y].push_back(x);
		}
	}
	for (int i=0;i<N;i++)spouse[i]=-1;
	for (int i=0;i<N;i++)if (spouse[i]==-1)
		findaugment(i);
	int ret=0;
	for (int i=0;i<N;i++)if (spouse[i]!=-1)ret++;
	printf("%d\n",ret);
	for (int i=0;i<N;i++)
		if (spouse[i]!=-1 && spouse[i]>i)
			printf("%d %d\n",i+1,spouse[i]+1);
	return 0;
}
