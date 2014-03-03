#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
 
template <class T> void checkmin(T &t,T x){if (x < t) t = x;}
template <class T> void checkmax(T &t,T x){if (x > t) t = x;}
#define foreach(it,v) for (__typeof((v).begin()) it = (v).begin();it != (v).end();it++)
const int N = 250005;
const int Mod = 2012;
 
struct Node {
	Node *ch[11], *fa;
	int val;
	int way;
	int sum;
	Node(): 
		val(0), fa(NULL), way(0), sum(0) { 
		memset(ch, 0, sizeof(ch));
	}
}pool[N * 2 + 5], *last, *root;
vector <Node *> vec[N];
 
namespace SAM {
	int cnt;
 
	void init() {
		if (cnt)
			for (int i = 0; i < cnt; i++)
				pool[i] = Node();
		cnt = 1;
		root = &pool[0];
		last = root;
	}
 
	void add(int c) {
		Node *p = last, *np = &pool[cnt++];
		last = np;
		np->val = p->val + 1;
		for  (; p && !p->ch[c]; p = p->fa)
			p->ch[c] = np;
		if (!p) {
			np->fa = root;
		} else {
			Node *q = p->ch[c];
			if (p->val + 1 == q->val) {
				 np->fa = q;
			} else {
				Node *nq = &pool[cnt++];
				*nq = *q;
				nq->val = p->val + 1;
				q->fa = nq;
				np->fa = nq;
				for (; p && p->ch[c] == q; p = p->fa)
					p->ch[c] = nq;
			}
		}
	}
}
 
bool cmp(int i, int j) {
	return pool[i].val < pool[j].val;
}
 
int n, m;
char S[N], buf[N];
 
void calc() {
	int ans = 0;
	vector <int> vec;
	for (int i = 0; i < SAM::cnt; i++) {
		vec.push_back(i);
		pool[i].way = pool[i].sum = 0;
	}
	sort(vec.begin(), vec.end(), cmp);
	root->way = 1;
	root->sum = 0;
	foreach (it, vec) {
		int i = *it;
		Node *p = &pool[i];
		for (int c = i == 0 ? 1 : 0; c < 10; c++) {
			if (p->ch[c]) {
				p->ch[c]->way += p->way;
				p->ch[c]->way %= Mod;
				p->ch[c]->sum += p->sum * 10 + p->way * c;
				p->ch[c]->sum %= Mod;
			}
		}
		ans += p->sum;
		ans %= Mod;
	}
	printf("%d\n", ans);
}
 
int main(){
	while (scanf("%d", &n) != EOF) {
		m = 0;
		SAM::init();
		for (int i = 0; i < n; i++) {
			scanf("%s", buf);
			int len = strlen(buf);
			for (int j = 0; j < len; j++) {
				SAM::add(buf[j] - '0');
			}
			SAM::add(10);
		}
		calc();
	}
}
////////////////////////////////////////////////////////////////////////////////////
struct SAM {
    struct {
        int len, f, ch[26];
        void init() {
            len = 0, f = -1;
            memset(ch, 0xff, sizeof (ch));
        }
    } e[N<<1];
    int idx, last;
    
    void init() {
        idx = last = 0;
        e[idx++].init();
    }
    int newnode() {
        e[idx].init();
        return idx++;
    }
    void add(int c) {
        int end = newnode();
        int tmp = last;
        e[end].len = e[last].len + 1;
        for (; tmp != -1 && e[tmp].ch[c] == -1; tmp = e[tmp].f) {
            e[tmp].ch[c] = end;
        }
        if (tmp == -1) e[end].f = 0;
        else {
            int nxt = e[tmp].ch[c];
            if (e[tmp].len + 1 == e[nxt].len) e[end].f = nxt;
            else {
                int np = newnode();
                e[np] = e[nxt];
                e[np].len = e[tmp].len + 1;
                e[nxt].f = e[end].f = np;
                for (; tmp != -1 && e[tmp].ch[c] == nxt; tmp = e[tmp].f) {
                    e[tmp].ch[c] = np;
                }
            }
        }
        last = end;
    }
};
