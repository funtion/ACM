//http://blog.csdn.net/sdust_dc/article/details/9706357
//HDU 4635
#include <stdio.h>
#include <string.h>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;
#define LL long long
const int maxn=100010;
vector<int> G[maxn];
int n,m;
int pre[maxn],lowlink[maxn],sccno[maxn],dfs_clock,scc_cnt;
int in[maxn],out[maxn];
stack<int> S;

void dfs(int u){
    pre[u]=lowlink[u]=++dfs_clock;
    S.push(u);
    for(int i=0;i<G[u].size();i++)
    {
        int v=G[u][i];
        if(!pre[v]){
            dfs(v);
        lowlink[u]=min(lowlink[u],lowlink[v]);
        }
        else if(!sccno[v]){
            lowlink[u]=min(lowlink[u],pre[v]);
        }
    }
    if(lowlink[u]==pre[u])
    {
        scc_cnt++;
        for(;;){
            int x=S.top();S.pop();
            sccno[x]=scc_cnt;
            if(x==u)break;
        }
    }
}

void find_scc(int n){
    dfs_clock=scc_cnt=0;
    memset(sccno,0,sizeof(sccno));
    memset(pre,0,sizeof(pre));
    for(int i=0;i<n;i++)
        if(!pre[i])dfs(i);
}

int main()
{
    LL ct[100010];
    int T,x,y,cas=0;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        for(int i=0;i<n;i++)
            G[i].clear();
        for(int i=0;i<m;i++)
        {
            scanf("%d%d",&x,&y);
            G[x-1].push_back(y-1);
        }
        find_scc(n);
        printf("Case %d: ",++cas);
        if(scc_cnt==1)
        {
            printf("-1\n");
        }
        else
        {
            memset(ct,0,sizeof(ct));
            memset(in,0,sizeof(in));
            memset(out,0,sizeof(out));
            LL max=0;
            for(int i=0;i<n;i++)
            {
                ct[sccno[i]]++;
            }
            for(int i=0;i<n;i++)
            {
                for(int j=0;j<G[i].size();j++)
                {
                    if(sccno[i]!=sccno[G[i][j]])
                    {
                    out[sccno[i]]++;
                    in[sccno[G[i][j]]]++;
                    }
                }
            }
            for(int i=1;i<=scc_cnt;i++)
            {
                if(in[i]==0||out[i]==0)
                {
                   LL k=ct[i];
                   LL ans=k*(k-1)+(n-k)*(n-k-1)+k*(n-k)-m;
                   if(ans>max)max=ans;
                }
            }
            printf("%I64d\n",max);
        }
    }
    return 0;
}
