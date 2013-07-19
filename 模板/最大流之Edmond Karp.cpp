

/**
 * Edmond Karp
 * Max Flow
 * by Tanky Woo @ www.wutianqi.com
 *http://www.wutianqi.com/?p=3107
 */

#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;
const int msize = 205;

int N, M;   // N--路径数, M--结点数
int r[msize][msize];  //
int pre[msize];  // 记录结点i的前向结点为pre[i]
bool vis[msize]; // 记录结点i是否已访问

// 用BFS来判断从结点s到t的路径上是否还有delta
// 即判断s,t之间是否还有增广路径，若有，返回1
bool BFS(int s, int t)
{
    queue<int> que;
    memset(pre, -1, sizeof(pre));
    memset(vis, false, sizeof(vis));

    pre[s] = s;
    vis[s] = true;
    que.push(s);

    int p;
    while(!que.empty())
    {
        p = que.front();
        que.pop();
        for(int i=1; i<=M; ++i)
        {
            if(r[p][i]>0 && !vis[i])
            {
                pre[i] = p;
                vis[i] = true;
                if(i == t)  // 存在增广路径
                    return true;
                que.push(i);
            }
        }
    }
    return false;
}

int EK(int s, int t)
{
    int maxflow = 0, d;
    while(BFS(s, t))
    {
        d= INT_MAX;
        // 若有增广路径，则找出最小的delta
        for(int i=t; i!=s; i=pre[i])
            d = min(d, r[pre[i]][i]);
        // 这里是反向边，看讲解
        for(int i=t; i!=s; i=pre[i])
        {
            r[pre[i]][i] -= d;
            r[i][pre[i]] += d;
        }
        maxflow += d;
    }
    return maxflow;
}

int main()
{
    while(cin >> N >> M)
    {
        memset(r, 0, sizeof(r));
        int s, e, c;
        for(int i=0; i<N; ++i)
        {
            cin >> s >> e >> c;
            r[s][e] += c;   // 有重边时则加上c
        }

        cout << EK(1, M) << endl;
    }
    return 0;
}
