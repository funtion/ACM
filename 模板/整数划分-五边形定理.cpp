//p(n) = p(n-1)+p(n-2)-p(n-5)-p(n-7)
//k(3k-1)/2,k(3k+1)/2

#include<iostream>
#define mx 100100
#define mod 1000000007
using namespace std;
int dp[mx]={1,1,2};
void init(){
    for(int i=3;i<mx;i++){
        for(int j=1;;j++){
            int t1 = (j*(3*j-1))/2;
            int t2 = (j*(3*j+1))/2;
            if(i<t1)
                break;
            else{
                if(j%2==0){
                    dp[i] = (dp[i]-dp[i-t1]+mod)%mod;
                }else{
                    dp[i] = (dp[i]+dp[i-t1])%mod;
                }
            }
            if(i<t2)
                break;
            else{
                if(j%2==0){
                    dp[i] = (dp[i]-dp[i-t2]+mod)%mod;
                }else{
                    dp[i] = (dp[i]+dp[i-t2])%mod;
                }
            }

        }
    }
}
int main(){
    ios::sync_with_stdio(false);
    init();
    int n,t;
    cin>>t;
    while(t--){
        cin>>n;
        cout<<dp[n]<<endl;
    }
}
