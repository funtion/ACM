//hdu 4691
#include <set>
#include <map>
#include <stack>
#include <cmath>
#include <queue>
#include <cstdio>
#include <string>
#include <vector>
#include <iomanip>
#include <cstring>
#include <iostream>
#include <algorithm>
#define Max 2505
#define FI first
#define SE second
#define ll __int64
#define PI acos(-1.0)
#define inf 0x3fffffff
#define LL(x) ( x << 1 )
#define bug puts("here")
#define PII pair<int,int>
#define RR(x) ( x << 1 | 1 )
#define mp(a,b) make_pair(a,b)
#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,s,t) for( int i = ( s ) ; i <= ( t ) ; ++ i )

using namespace std;

inline void RD(int &ret) {
    char c;
    int flag = 1 ;
    do {
        c = getchar();
        if(c == '-')flag = -1 ;
    } while(c < '0' || c > '9') ;
    ret = c - '0';
    while((c=getchar()) >= '0' && c <= '9')
        ret = ret * 10 + ( c - '0' );
    ret *= flag ;
}

inline void OT(int a) {
    if(a >= 10)OT(a / 10) ;
    putchar(a % 10 + '0') ;
}


#define N 1000005
/****后缀数组模版****/
#define F(x)((x)/3+((x)%3==1?0:tb)) //F(x)求出原字符串的suffix(x)在新的字符串中的起始位置
#define G(x)((x)<tb?(x)*3+1:((x)-tb)*3+2) //G(x)是计算新字符串的suffix(x)在原字符串中的位置，和F(x)为互逆运算
int wa[N],wb[N],wv[N],WS[N];
int sa[N*3] ;
int rank1[N],height[N];
int r[N*3];

int c0(int *r,int a,int b) {
    return r[a] == r[b] && r[a + 1] == r[b + 1] && r[a + 2] == r[b + 2];
}
int c12(int k,int *r,int a,int b) {
    if(k == 2)
        return r[a] < r[b] || ( r[a] == r[b] && c12(1 , r , a + 1 , b + 1) );
    else
        return r[a] < r[b] || ( r[a] == r[b] && wv[a + 1] < wv[b + 1] );
}
void sort(int *r,int *a,int *b,int n,int m) {
    int i;
    for(i = 0; i < n; i ++)
        wv[i] = r[a[i]];
    for(i = 0; i < m; i++)
        WS[i] = 0;
    for(i = 0; i < n; i++)
        WS[wv[i]] ++;
    for(i = 1; i < m; i++)
        WS[i] += WS[i-1];
    for(i=n-1; i>=0; i--)
        b[-- WS[wv[i]]] = a[i];
    return;
}

//注意点：为了方便下面的递归处理，r数组和sa数组的大小都要是3*n
void dc3(int *r,int *sa,int n,int m) { //rn数组保存的是递归处理的新字符串，san数组是新字符串的sa
    int i , j , *rn = r + n , *san = sa + n , ta = 0 ,tb = (n + 1) / 3 , tbc = 0 , p;
    r[n] = r[n+1] = 0;
    for(i = 0; i < n; i++) {
        if(i % 3 != 0)
            wa[tbc ++]=i; //tbc表示起始位置模3为1或2的后缀个数
    }
    sort(r + 2,wa,wb,tbc,m);
    sort(r + 1,wb,wa,tbc,m);
    sort(r,wa,wb,tbc,m);
    for(p = 1,rn[F(wb[0])] = 0,i = 1; i < tbc; i++)
        rn[F(wb[i])]=c0(r,wb[i - 1],wb[i])?p - 1 : p ++;
    if(p < tbc)
        dc3(rn,san,tbc,p);
    else {
        for(i = 0; i < tbc; i++)
            san[rn[i]]=i;
    }
//对所有起始位置模3等于0的后缀排序
    for(i = 0; i < tbc; i++) {
        if(san[i] < tb)
            wb[ta ++] = san[i] * 3;
    }
    if(n % 3 == 1)  //n%3==1，要特殊处理suffix(n-1)
        wb[ta ++] = n - 1;
    sort(r,wb,wa,ta,m);
    for(i = 0; i < tbc; i++)
        wv[wb[i] = G(san[i])] = i;
//合并所有后缀的排序结果，保存在sa数组中
    for(i = 0,j = 0,p = 0; i < ta && j < tbc; p ++)
        sa[p] = c12(wb[j] % 3,r,wa[i],wb[j]) ? wa[i ++] : wb[j ++];
    for(; i < ta; p++)
        sa[p] = wa[i++];
    for(; j < tbc; p++)
        sa[p] = wb[j++];
    return;
}

//height[i]=suffix(sa[i-1])和suffix(sa[i])的最长公共前缀，也就是排名相邻的两个后缀的最长公共前缀
void calheight(int *r,int *sa,int n) {
    int i , j , k = 0;
    for(i = 1; i <= n; i++)
        rank1[sa[i]] = i;
    for(i = 0; i < n; height[rank1[i++]] = k)
        for(k ? k -- : 0 , j = sa[rank1[i]-1]; r[i + k] == r[j + k]; k++);
}
int RMQ[N];
int mm[N];
int best[20][N];
void initRMQ(int n) {
    int i,j,a,b;
    for(mm[0] = -1,i = 1; i <= n; i++)
        mm[i] = ((i & (i - 1)) == 0)?mm[i - 1] + 1 : mm[i - 1];
    for(i = 1; i <= n; i++) best[0][i] = i;
    for(i = 1; i <= mm[n]; i++)
        for(j = 1; j <= n + 1 - (1 << i); j++) {
            a = best[i - 1][j];
            b = best[i - 1][j + (1 << (i - 1))];
            if(RMQ[a] < RMQ[b]) best[i][j] = a;
            else best[i][j] = b;
        }
    return;
}
int askRMQ(int a,int b) {
    int t;
    t = mm[b - a + 1];
    b -= (1 << t ) - 1;
    a = best[t][a];
    b = best[t][b];
    return RMQ[a] < RMQ[b] ? a : b;
}
int lcp(int a,int b) {
    int t;
    a = rank1[a];
    b = rank1[b];
    if(a > b) {
        t = a;
        a = b;
        b = t;
    }
    return(height[askRMQ(a + 1,b)]);
}
/*********************************************/


#define N 1000005
char a[N] ;
int n ;

int cal(int now){
    if(now == 0)return 1 ;
    int nn = 0 ;
    while(now){
        nn ++ ;
        now /= 10 ;
    }
    return nn ;
}
int main() {
    int ttt = 0 ;
    while(scanf("%s",a) != EOF ) {
        int l = strlen(a) ;
        for (int i = 0 ; i < l ; i ++ )r[i] = a[i] ;
        r[l] = 0 ;
        dc3(r , sa ,l + 1 , 200) ;
        calheight(r , sa , l) ;
        for (int i = 1 ; i <= l ; i ++ )RMQ[i] = height[i] ;
        initRMQ(l) ;
        RD(n) ;
        ll num1 = 0 ,num2 = 0 ;
        int x , y ;
        int prex = -1 , prey = -1 ;
        while(n -- ) {
            RD(x) ;
            RD(y) ;
            num1 += (y - x) + 1 ;
            if(prex == -1){
                num2 += (y - x) + 3 ;
                prex = x ;
                prey = y ;
                continue ;
            }
            int now = 0 ;
            if(x == prex){
                now = min(prey - prex , y - x) ;
            }
            else{
                now = lcp(prex , x) ;
                now = min(prey - prex , min(y - x , now) ) ;
            }
            prex = x ;
            prey = y ;
            int fk = now ;
            now = y - x - now ;
            if(now == 0){
                num2 += 2 + cal(fk) ;
            }else
            num2 += cal(fk) + now + 2 ;
        }
        printf("%I64d %I64d\n",num1 ,num2) ;
        ttt ++ ;
    }
    return 0 ;
}
