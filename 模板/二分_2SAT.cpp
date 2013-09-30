//hdu3622
#include<cstdio>
#include<cmath>
#include<cstring>
#define V 1000
#define E 2000000
/****io**/
namespace IO
{
template<class T> inline T RD(T &x)
{
    char c;
    for (c = getchar(); c < '-'; c = getchar());
    if (c == '-')
    {
        x = '0' - getchar();
        for (c = getchar(); '0' <= c && c <= '9'; c = getchar()) x = x * 10 + '0' - c;
    }
    else
    {
        x = c - '0';
        for (c = getchar(); '0' <= c && c <= '9'; c = getchar()) x = x * 10 + c - '0';
    }
    return x;
} inline int RD()
{
    int x;
    return RD(x);
}
} using namespace IO;
/****io**/
const double esp = 1e-8;
int n;
struct pt
{
    int x,y;
} a[300],b[300];
inline double dis(const pt& a,const pt&b)
{
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
double dis11[200][200],dis12[200][200],dis21[200][200],dis22[200][200];
/******************2-SAT*********************/
int top,cnt,index,ecnt;
bool instack[V];
int stack[V],id[V],dfn[V],low[V];
int head[V];
struct edge
{
    int s,t,next;
} e[E];
void addedge(int u,int v)
{
    e[ecnt].s=u;
    e[ecnt].t=v;
    e[ecnt].next=head[u];
    head[u]=ecnt++;
}
void tarjan(int u)
{
    int v;
    int tmp;
    dfn[u]=low[u]=++index;
    instack[u]=true;
    stack[++top]=u;
    for(int k=head[u]; k!=-1; k=e[k].next)
    {
        v=e[k].t;
        if(!dfn[v])
        {
            tarjan(v);
            if(low[v]<low[u])
            {
                low[u]=low[v];
            }
        }
        else if(instack[v] && dfn[v] < low[u])
        {
            low[u]=dfn[v];
        }
    }
    if(dfn[u]==low[u])
    {
        cnt++;
        do
        {
            tmp=stack[top--];
            instack[tmp]=false;
            id[tmp]=cnt;
        }
        while(tmp!=u);
    }
}
void solve()
{
    top = cnt = index = 0;
    memset(dfn,0,sizeof(dfn));
    for(int i=0; i<2*n; i++)
    {
        if(!dfn[i])
            tarjan(i);
    }
}
bool Two_Sat()
{
    solve();
    // for(int i=0;i<n*n;i++)
    //   printf("%d %d\n",i,id[i]);
    for(int i=0; i<n; i++)
    {
        if(id[i]==id[i+n])
        {
            return 0;
        }
    }
    return 1;
}
/******************2-SAT*********************/

bool rn(double r)
{
    ecnt = 0;
    memset(head,-1,sizeof(head));
    for(int i=0; i<n; i++)
    {
        for(int j=i+1; j<n; j++)
        {
            if(dis11[i][j]<r*2-esp)
            {
                addedge(i,j+n);
                addedge(j,i+n);
            }
            if(dis12[i][j]<r*2-esp)
            {
                addedge(i,j);
                addedge(j+n,i+n);
            }
            if(dis21[i][j]<r*2-esp)
            {
                addedge(i+n,j+n);
                addedge(j,i);
            }
            if(dis22[i][j]<r*2-esp)
            {
                addedge(i+n,j);
                addedge(j+n,i);
            }
        }
    }
    return Two_Sat();
}
int main()
{
    while(scanf("%d",&n)==1)
    {
        for(int i=0; i<n; i++)
        {
            scanf("%d%d%d%d",&a[i].x,&a[i].y,&b[i].x,&b[i].y);
            /*
            a[i].x =RD();
            a[i].y =RD();
            b[i].x =RD();
            b[i].y =RD();
            */
        }
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
            {
                dis11[i][j] = dis(a[i],a[j]);
                dis12[i][j] = dis(a[i],b[j]);
                dis21[i][j] = dis(b[i],a[j]);
                dis22[i][j] = dis(b[i],b[j]);
            }
        }

        double l=0,h=20000,mid,ans=0;
        while(h-l>=esp)
        {
            mid = (l+h)/2;
            if(rn(mid))
            {
                l = mid;
                ans = mid;
            }
            else
            {
                h = mid;
            }
            //printf("%.2lf,%.2lf\n",l,h);
        }

        printf("%.2lf\n",ans);
    }
}
