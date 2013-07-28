//http://acm.hdu.edu.cn/showproblem.php?pid=1166
//混在一起le，有zkw前缀的是zkw的
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int n,t,a[50010],c[50010],x,y,zkw[200010],m;
char cmd[10];
inline int lowbit(int x){
    return x&(-x);
    //return 1<<__builtin_ctz(x);
}
void change(int x,int val){
    while(x<=n){
        c[x]+=val;
        x+=lowbit(x);
    }
}
int sum(int x){
    int s=0;
    while(x>0){
        s+=c[x];
        x-=lowbit(x);
    }
    return s ;
}
inline void zkwAdd(int x,int val){
    for(zkw[x+=m]+=val,x>>=1;x;x>>=1)
        zkw[x] = zkw[x+x]+zkw[x+x+1];
}
int zkwQuery(int s,int t){
    int ans = 0;
    for(s=s-1+m,t=t+1+m;s^t^1;s>>=1,t>>=1){
        if(~s&1) ans +=zkw[s^1];
        if( t&1) ans +=zkw[t^1];
    }
    return ans;
}
int main()
{
    while(scanf("%d",&t)!=EOF){
        for(int cse=1;cse<=t;cse++){
            printf("Case %d:\n",cse);
            scanf("%d",&n);
            m=1;
            while(m<=n)m<<=1;
           // memset(c,0,sizeof(c));
            memset(zkw,0,sizeof(zkw));
            for(int i=1;i<=n;i++){
                //scanf("%d",&a[i]);
                //change(i,a[i]);
                scanf("%d",&zkw[m+i]);
            }
            for(int i=m-1;i>=1;i--)
                zkw[i] = zkw[i+i]+zkw[i+i+1];
            while(scanf("%s",cmd)!=EOF,cmd[0]!='E'){
                switch(cmd[0]){
                case 'A':
                    scanf("%d%d",&x,&y);
                    //change(x,y);
                    zkwAdd(x,y);
                    break;
                case 'S':
                    scanf("%d%d",&x,&y);
                    //change(x,-y);
                    zkwAdd(x,-y);
                    break;
                case 'Q':
                    scanf("%d%d",&x,&y);
                    //printf("%d\n",sum(y)-sum(x-1));
                   printf("%d\n",zkwQuery(x,y));
                   break;
                }
            }
        }
    }
    return 0;
}
