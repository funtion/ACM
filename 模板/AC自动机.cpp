#include <cstdio>
#include <algorithm>
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
int cnt;

struct AC_Automata {
    #define N 240005
    #define M 26
    int ch[N][M], sz;
    int val[N], last[N], f[N], cc[N];

    void clear() { sz = 1; memset(ch[0], 0, sizeof(ch[0])); }
    int idx(char c) { return c-'a'; }

    void insert(char s[], int v) {
        int u = 0;
        for (int i=0; s[i]; i++) {
            int c = idx(s[i]);
            if (!ch[u][c]) {
                memset(ch[sz], 0, sizeof(ch[sz]));
                val[sz] = cc[sz] = 0;
                ch[u][c] = sz++;
            }
            u = ch[u][c];
        }
        cc[u]++;
        val[u] = v;
    }
    void build() {
        queue<int> q;
        f[0] = 0;
        for (int c=0; c<M; c++) {
            int u = ch[0][c];
            if (u) { f[u] = 0, q.push(u); last[u] = 0; }
        }
        while (!q.empty()) {
            int r = q.front(); q.pop();
            for (int c=0; c<M; c++) {
                int u = ch[r][c];
                if (!u) { ch[r][c] = ch[f[r]][c]; continue; }
                q.push(u);
                int v = f[r];
                f[u] = ch[v][c];
                last[u] = val[f[u]] ? f[u] : last[f[u]];
            }
        }
    }
    void find(char *s) {
        int j = 0;
        for (int i=0; s[i]; i++) {
            int c = idx(s[i]);
            j = ch[j][c];
            //if (val[j]) print(j);
            //else if (last[j]) print(last[j]);
            if (cc[j]) print(j);
            else if (last[j]) print(last[j]);
        }
    }

    void print(int j) { //打印以结点j结尾的所有字符串
        if (j) {
            //printf("%d: %d\n", j, val[j]);
            cnt += cc[j];
            cc[j] = 0;
            print(last[j]);
        }
    }

} ac;
char s[55], text[1000006];

int main() {
    int n, T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        ac.clear();
        for (int i=1; i<=n; i++) {
            scanf(" %s", s); ac.insert(s, i);
        }
        ac.build();
        cnt = 0;
        scanf(" %s", text);
        ac.find(text);
        printf("%d\n", cnt);
    }
    return 0;

}
