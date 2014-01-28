#define rep(i,n) for (int i = 0; i < (int)(n); i++)
#define foreach(it,v) for (__typeof((v).end()) it = (v).begin(); it != (v).end(); it++)
typedef pair <int, int> PII;
typedef long long ll;
const int MAXN = 100005;
int n, m, e;
int match1[MAXN], match2[MAXN];
int Q[MAXN], D1[MAXN], D2[MAXN];
vector <int> E[MAXN];

inline bool bfs() {
    int s = 0, t = 0, u, v;
    memset(D1, -1, sizeof(D1));
    memset(D2, -1, sizeof(D2));
    for (int i = 0; i < n; i++)
        if (match1[i] == -1)
            Q[t++] = i, D1[i] = 0;
    while (s != t)
        if ((u = Q[s++]) != n)
            for (int i = 0; i < (int)E[u].size(); i++)
                if (D2[v = E[u][i]] == -1) {
                    D2[v] = D1[u] + 1;
                    if (D1[match2[v]] == -1)
                        D1[Q[t++] = match2[v]] = D2[v] + 1;
                }
    return D1[n] != -1;
}

bool dfs(int u) {
    for (int i = 0, v; i < (int)E[u].size(); i++)
        if (D2[v = E[u][i]] == D1[u] + 1 && (D2[v] = -1) && (match2[v] == n || dfs(match2[v]))) {
            match1[u] = v;
            match2[v] = u;
            D1[u] = -1;
            return true;
        }
    D1[u] = -1;
    return false;
}

inline int hopcroft_karp() {
    memset(match1, -1, sizeof(match1));
    for (int i = 0; i < m; i++)
        match2[i] = n;
    int ret = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0, u; j < (int)E[i].size(); j++)
            if (match2[u = E[i][j]] == n) {
                match1[i] = u;
                match2[u] = i;
                ret++;
                break;
            }
    while (bfs())
        for (int i = 0; i < n; i++)
            if (match1[i] == -1 && dfs(i))
                ret++;
    return ret;
}
