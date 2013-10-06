#include <cstdio>
#include <cstring>
#include <cstdlib>
#define INF 0x3f3f3f3f
#define MAX 1001
struct node
{
    int u, v, w;
} edge[MAX*MAX];
int n, x, y, z, es, k, tt;
int pre[MAX], in[MAX], id[MAX], vis[MAX];
int pnt[MAX][3];

void addedge( int u, int v, int w ) {  
        edge[es].u = u, edge[es].v = v, edge[es++].w = w;  
}  

int dirMst( int root, int vs )
{
    int ans = 0;
    while(1)
    {
        memset( in, INF, sizeof(in) );
        memset( id, -1, sizeof(id) );
        memset( vis, -1, sizeof(vis) );
        for ( int i = 0; i < es; ++i )
        {
            int u = edge[i].u, v = edge[i].v, w = edge[i].w;
            if ( w < in[v] && v != u ) pre[v] = u, in[v] = w;
        }//求最小入边集
        in[root] = 0, pre[root] = root;//为之后的遍历做准备，in【】用于存储最小边集
        for ( int i = 0; i < vs; ++i )
        {
            if ( in[i] == INF ) return -1;
            ans += in[i];
        }//此循环判断是否有孤立节点，同时计算当前最小权值和
        int idx = 0;//idx是用来给新的节点赋名称的（新序号）
        for ( int i = 0; i < vs; ++i )
            if ( vis[i] == -1 )
            {
                int u = i;
                while ( vis[u] == -1 ) vis[u] = i, u = pre[u];//将vis[u]赋值为i是为了做标记
                if ( vis[u] != i || u == root ) continue;//判断是否形成环
                for ( int t = pre[u]; t != u; t = pre[t] ) id[t] = idx;//给环上的点赋值一个统一的标号，形成一个新的点(id[i]用于存储i点的新标号）
                id[u] = idx++;
            }
        if ( idx == 0 ) break;//没有环，跳出循环
        for ( int i = 0; i < vs; i++ ) if ( id[i] == -1 ) id[i] = idx++;//在上一个循环给环赋予新的序号，这一步是给非环的点新的序号，保证新图中每个点有相应的标号
        for ( int i = 0; i < es; i++ )
        {
            edge[i].w -= in[edge[i].v];//把每个点的其他入边看做环的入边，将增值赋给环的入边，作为新图的这个新的点的该条入边的权值

            edge[i].u = id[edge[i].u];
            edge[i].v = id[edge[i].v];
        }//这个循环是修改旧图，把id中存储的映射到图中形成新图
        vs = idx;//这个很重要，要知道把环捏成一个点，那么图中点个数改变了，所以循环次数改变
        root = id[root];//给根新的标号
    }
    return ans;
}

int main()
{
    int ans = dirMst(0, n + 1);
    if ( ans == -1 ) printf("poor XiaoA\n");  
     else printf("%d\n", ans);  
    return 0;
    
}
////////////////////////////
#include<iostream>
#include<algorithm>
#include<string>
#include<math.h>
using namespace std;
const int N = 100+10;
const int M = 10000+10;
struct Point
{
    double x,y;
}p[N];
struct edge
{
    int u,v;
    double cost;
    edge(){}
    edge(int u,int v,double c):u(u),v(v),cost(c){}
}e[M];
int pre[N],hash1[N],vis[N];
double In[N];
inline double dist(Point& a,Point& b)
{
    return sqrt(double((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y)));
}
double Directed_MST(int root,int n,int m)
{
    double ret=0;
    while(true)
    {
        for(int i=0;i<n;i++)
            In[i]=INT_MAX;
        for(int i=0;i<m;i++)//找最小入边
        {
            int u=e[i].u;
            int v=e[i].v;
            if(e[i].cost<In[v] && u!=v){
                pre[v]=u;
                In[v]=e[i].cost;
            }
        }
        for(int i=0;i<n;i++)
        {
            if(i==root)
                continue;
            if(In[i]==INT_MAX)
                return -1;
        }
        int cntnode=0;
        memset(hash1,-1,sizeof(hash1));
        memset(vis,-1,sizeof(vis));
        In[root]=0;
        for(int i=0;i<n;i++)//找环
        {
            ret+=In[i];
            int v=i;
            while(vis[v]!=i && hash1[v]==-1 && v!=root)
            {
                vis[v]=i;
                v=pre[v];
            }
            if(v!=root && hash1[v]==-1)
            {
                for(int u=pre[v];u!=v;u=pre[u])
                    hash1[u]=cntnode;
                hash1[v]=cntnode++;
            }
        }
        if(cntnode==0)
            break;
        for(int i=0;i<n;i++)
            if(hash1[i]==-1)
                hash1[i]=cntnode++;
        for(int i=0;i<m;i++)//重标记
        {
            int v=e[i].v;
            e[i].u=hash1[e[i].u];
            e[i].v=hash1[e[i].v];
            if(e[i].u!=e[i].v)
                e[i].cost-=In[v];
        }
        n=cntnode;
        root=hash1[root];
    }
    return ret;
}
int main()
{
    int a,b;
    int n,m;
    while(scanf("%d %d",&n,&m)==2)
    {
        for(int i=0;i<n;i++)
            scanf("%lf %lf",&p[i].x,&p[i].y);
        int mm=0;
        for(int i=0;i<m;i++)
        {
            scanf("%d %d",&a,&b);
            if(a==b)continue;
            a--,b--;
            e[mm++]=edge(a,b,dist(p[a],p[b]));
        }
        double ans=Directed_MST(0,n,mm);
        if(ans==-1)
            puts("poor snoopy");
        else printf("%.2f\n",ans);
    }
    return 0;
}
