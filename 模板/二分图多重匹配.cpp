 #include<iostream>
  #include<cstdio>
using namespace std;
 #define re(i,n) for(int i=0;i<n;i++)
  const int N = 100005;
  const int M = 11;
  int yM[M][N];
  int tem[M],num[M],chk[M];
  int G[N][M];
 int n,m;
 bool dfs(int u){
     re(v,m) if(G[u][v] && !chk[v]){
         chk[v] =1;
         if(tem[v] < num[v]){
             yM[v][tem[v]++] = u;
             return 1;
         }
         else re(i,tem[v])
             if(dfs(yM[v][i])){
                 yM[v][i] = u;
                 return 1;
             }
     }
     return 0;
 }
 int main(){
     while(~scanf("%d%d",&n,&m)){
         re(i,n) re(j,m) scanf("%d",&G[i][j]);
         re(i,m) scanf("%d",&num[i]);
         re(i,m) tem[i] = 0;
         int flag = 1;
         re(i,n) {
             re(j,m) chk[j] = 0;
             if(!dfs(i)) { flag = 0; break;}
         }
         puts(flag?"YES":"NO");
     }
 }
 
