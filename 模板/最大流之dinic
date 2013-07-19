/*
Program:POJ 1273 /
Dinic
Author:Comzyh
http://comzyh.tk/blog/archives/568/
*/
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#define min(x,y) ((x<y)?(x):(y))
using namespace std;
const int MAX=0x5fffffff;//
int tab[250][250];//邻接矩阵 
int dis[250];//距源点距离,分层图 
int q[2000],h,r;//BFS队列 ,首,尾 
int N,M,ANS;//N:点数;M,边数 
int BFS()
{
     int i,j;
     memset(dis,0xff,sizeof(dis));//以-1填充 
     dis[1]=0;
     h=0;r=1;
     q[1]=1;
     while (h<r)
     {
           j=q[++h];
           for (i=1;i<=N;i++)
               if (dis[i]<0 && tab[j][i]>0)
               {
                  dis[i]=dis[j]+1; 
                  q[++r]=i;
               }
     }
     if (dis[N]>0)
        return 1;
     else
        return 0;//汇点的DIS小于零,表明BFS不到汇点 
}
//Find代表一次增广,函数返回本次增广的流量,返回0表示无法增广 
int find(int x,int low)//Low是源点到现在最窄的(剩余流量最小)的边的剩余流量
{
    int i,a=0;
    if (x==N)return low;//是汇点 
    for (i=1;i<=N;i++)
    if (tab[x][i] >0 //联通 
     && dis[i]==dis[x]+1 //是分层图的下一层 
     &&(a=find(i,min(low,tab[x][i]))))//能到汇点(a <> 0) 
    {
       tab[x][i]-=a;
       tab[i][x]+=a;
       return a;
    }
    return 0;
 
}
int main()
{
    //freopen("ditch.in" ,"r",stdin );
    //freopen("ditch.out","w",stdout);
    int i,j,f,t,flow,tans;
    while (scanf("%d%d",&M,&N)!=EOF){
    memset(tab,0,sizeof(tab));
    for (i=1;i<=M;i++)
    {
        scanf("%d%d%d",&f,&t,&flow);
        tab[f][t]+=flow;
    }
    //
    ANS=0;
    while (BFS())//要不停地建立分层图,如果BFS不到汇点才结束 
    {
          while(tans=find(1,0x7fffffff))ANS+=tans;//一次BFS要不停地找增广路,直到找不到为止 
    }
    printf("%d\n",ANS);
    }
    system("pause");
}
