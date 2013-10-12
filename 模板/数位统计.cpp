///7k+
int dfs(int i, int s, bool e) {
    if (i==-1) return s==target_s;
    if (!e && ~f[i][s]) return f[i][s];
    int res = 0;
    int u = e?num[i]:9;
    for (int d = first?1:0; d <= u; ++d)
        res += dfs(i-1, new_s(s, d), e&&d==u);
    return e?res:f[i][s]=res;
}
//f为记忆化数组；

//i为当前处理串的第i位（权重表示法，也即后面剩下i+1位待填数）；

//s为之前数字的状态（如果要求后面的数满足什么状态，也可以再记一个目标状态t之类，for的时候枚举下t）；

//e表示之前的数是否是上界的前缀（即后面的数能否任意填）。

//for循环枚举数字时，要注意是否能枚举0，以及0对于状态的影响，有的题目前导0和中间的0是等价的，但有的不是，对于后者可以在dfs时再加一个状态变量z，表示前面是否全部是前导0，也可以看是否是首位，然后外面统计时候枚举一下位数。It depends.
///////////
//http://blog.csdn.net/dgq8211/article/details/9301135
//hdu 3652

#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

int dp[10][13][2][2],digit[10];

int dfs(int len,int remain,bool mask,bool state,bool fp)
{
    if(!len)
        return remain == 0 && mask ? 1 : 0;
    if(!fp && dp[len][remain][mask][state] != -1)
        return dp[len][remain][mask][state];
    int ret = 0 , fpmax = fp ? digit[len] : 9;
    for(int i=0;i<=fpmax;i++){
        ret += dfs(len-1,(remain * 10 + i) % 13,mask || state && i == 3,i == 1,fp && i == fpmax);
    }
    if(!fp)
        dp[len][remain][mask][state] = ret;
    return ret;
}

int f(int n)
{
    int len = 0;
    while(n)
    {
        digit[++len] = n % 10;
        n /= 10;
    }
    return dfs(len,0,0,0,true);
}

int main()
{
    memset(dp,-1,sizeof(dp));
    int n;
    while(~scanf("%d",&n))
    {
        printf("%d\n",f(n));
    }
    return 0;
}
