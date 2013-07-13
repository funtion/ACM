#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define L(u) ( u << 1 )
#define R(u) ( u << 1 | 1 )
#define N 100005
#define inf (1<<31-1)

typedef int typev;
typedef pair<typev,int> pti;
/**
usage:  segtree::build(<root>,<l>,<r>) e.g. build(1,1,n); root=1; segment from 1 to n
        segtree::add(<root>,<l>,<r>,<val>) e.g add(1,3,5,-6); add -6 to nodes from <l> to <r>.
        segtree::getMin(<root>,<l>,<r>) e.g getMin(1,3,4); return a pair:first is maximal number,
                 second is it's position. Order by first ASC, second ASC default;
        segtree::getSum(<root>,<l>,<r>) e.g getSum(1,2,10); return sum of \sigma(node[2]..node[10])
*/
//#define SUM
#define MAX
struct item{
	int l, r;
	typev add;
	#ifdef SUM
	typev sumv;
	#endif
	#ifdef MAX
    pti maxv;   ///first:max_value, second:position
    #endif
};
struct segtree{
    item node[N*4];
    void build ( int u, int l, int r ){
        node[u].l = l, node[u].r = r;
        node[u].add = 0;
        #ifdef SUM
        node[u].sumv = 0;
        #endif
        //node[u].v = 0;
        if ( l == r ) {
            #ifdef MIN
            node[u].maxv.first = 0, node[u].maxv.second = r;
            #endif
            return;
        }
        int mid = ( l + r ) >> 1;
        build ( L(u), l, mid );
        build ( R(u), mid+1, r );
        #ifdef MIN
        node[u].maxv = max( node[L(u)].maxv, node[R(u)].maxv );
        #endif
    }
    inline void pushdown(int u){
        if (node[u].add==0) return ;
        #ifdef SUM
        node[u].sumv += node[u].add * ( node[u].r - node[u].l + 1 );
        #endif
        #ifdef MIN
        node[u].maxv.first += node[u].add;
        #endif
        if ( node[u].l!=node[u].r ){
            node[L(u)].add += node[u].add;
            node[R(u)].add += node[u].add;
        }
        node[u].add = 0;
    }
    inline void update(int u){
        pushdown(u);
        if ( node[u].l!=node[u].r ){
            pushdown(L(u)), pushdown(R(u));
            #ifdef MIN
            node[u].maxv = max( node[L(u)].maxv, node[R(u)].maxv );
            #endif
            #ifdef SUM
            node[u].sumv = node[L(u)].sumv + node[R(u)].sumv ;
            #endif
        }
    }
    void add ( int u, int l, int r, typev val ){
        if ( l == node[u].l && node[u].r == r ){
            node[u].add += val;
            return;
        }
        int mid = ( node[u].l + node[u].r ) >> 1;
        if ( r <= mid ) add ( L(u), l, r, val );
        else if ( l > mid ) add ( R(u), l, r, val );
        else{
            add ( L(u), l, mid, val );
            add ( R(u), mid+1, r, val );
        }
        update(u);  ///important
    }
    #ifdef SUM
    typev getSum(int u, int l, int r){
        update(u);
        if ( l == node[u].l && node[u].r == r ){ return node[u].sumv; }
        int mid = ( node[u].l + node[u].r ) >> 1;
        if ( r <= mid ) return getSum ( L(u), l, r );
        else if ( l > mid ) return getSum ( R(u), l, r );
        else{
            typev t1=getSum ( L(u), l, mid ),t2=getSum ( R(u), mid+1, r );
            return  t1 + t2;
        }
    }
    #endif
    #ifdef MAX
    pti getMax( int u, int l, int r ){
        update(u);  ///important
        if ( l == node[u].l && node[u].r == r ){ return node[u].maxv; }
        int mid = ( node[u].l + node[u].r ) >> 1;
        if ( r <= mid ) return getMax ( L(u), l, r );
        else if ( l > mid ) return getMax ( R(u), l, r );
        else{
            pti t1=getMax ( L(u), l, mid ),t2=getMax ( R(u), mid+1, r );
            return max( t1, t2 );
        }
    }
    #endif
};

segtree s;
