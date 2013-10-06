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


int dist( int i, int j )
{
    return abs( pnt[i][0] - pnt[j][0] ) + abs( pnt[i][1] - pnt[j][1] ) + abs( pnt[i][2] - pnt[j][2] );
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
    return 0;
}

