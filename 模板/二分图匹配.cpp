//http://poj.org/problem?id=3041
//临接表存边call init(), addedge()
#include <functional>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <numeric>
#include <cstring>
#include <cassert>
#include <cstdio>
#include <string>
#include <vector>
#include <bitset>
#include <queue>
#include <stack>
#include <cmath>
#include <ctime>
#include <list>
#include <set>
#include <map>

using namespace std;

#define DO(n) for ( int ____n ## __line__ = n; ____n ## __line__ -- ; )

#define ALL(A) A.begin(), A.end()
#define BSC(A, x) (lower_bound(ALL(A), x) - A.begin())
#define CTN(T, x) (T.find(x) != T.end())
#define SZ(A) int(A.size())
#define PB push_back
#define MP(A, B) make_pair(A, B)
#define fi first
#define se second

typedef long long LL;
typedef vector<int> VI;
typedef map<int, int> MII;
typedef pair<int, int> PII;
typedef pair<LL, LL> PLL;
const int V = 2e5+7;
const int E = 2e6+7;
using namespace std;
struct EDGE
{
    int u,v,w;
    EDGE *next;
    friend bool operator < ( const EDGE&a, const EDGE &b )
    {
        return (a.w < b.w);
    }
} e[E],*head[V];
int cnt;
void init()
{
    cnt=0;
    memset(head,0,sizeof(head));
}
inline void addedge(int u, int v, int c=0)
{
    e[cnt].u=u, e[cnt].v=v, e[cnt].w=c;
    e[cnt].next=head[u], head[u]=e+cnt++;
}

//result是匹配结果，maxmatch返回二分图最大匹配。
bool vis[V];
int result[V];
bool find(int a)
{
    for (EDGE *p=head[a]; p; p=p->next)
    {
        if (!vis[p->v])
        {
            vis[p->v]=true;
            if ( result[p->v]==-1 || find(result[p->v]) )
            {
                result[p->v]=a;
                return true;
            }
        }
    }
    return false;
}
int maxmatch(int n1, int n2=-1)
{
    memset(result,-1,sizeof(result));
    int i,ret=0;
    for (i=0; i<n1; i++)
    {
        if (n2==-1) memset(vis,0,sizeof(vis));
        else memset(vis,0,sizeof(bool)*n2);
        if (find(i)) ret++;
    }
    return ret;
}
PII a[V], b[V];
int main()
{
    int n,k,a,b;
    scanf("%d%d",&n,&k);
    init();
    while(k--)
    {
        scanf("%d%d",&a,&b);
        addedge(a,b);
    }
    printf("%d\n",maxmatch(n+1));//注意是n+1，看从0还是1开始
    return 0 ;
}
//////////////////////////////////////////////////////////////
//一个简化的////////////////////////////
//////////////////////
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define maxn 501
int match[maxn];
int map[maxn][maxn];
bool v[maxn];
int n,m;
bool dfs(int p)
{
    int i;
    for(i=1;i<=n;i++)
    {
        if(map[p][i]&&!v[i])
        {
            v[i]=1;
            if(match[i]==-1||dfs(match[i]))
            {
                match[i]=p;
                return 1;
            }
        }
    }
    return 0;
}
int Hungry()
{
    int i;
    int ans=0;
    for(i=1;i<=n;i++)
    {
        memset(v,0,sizeof(v));
        if(dfs(i))
            ans++;
    }
    return ans;
}
int main()
{
    int i,j,k;
    scanf("%d%d",&n,&k);
    for(m=1;m<=k;m++)
    {
        scanf("%d%d",&i,&j);
        map[i][j]=1;
    }
    memset(match,-1,sizeof(match));
    printf("%d\n",Hungry());
}
