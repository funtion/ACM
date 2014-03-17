#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#include <queue>
#include <set>
#include <map>
#include <cstring>
#include <functional>
#include <cmath>
typedef long long ll;
using namespace std;
ll n,m;
int a[200][200],b[200][200];
vector<int> pr;
int cp;
void init(){
    int h[10010];
    memset(h,0,sizeof(h));
    for(int i=2;i<=10000;i++){
        if(!h[i]){
            if(i>1000)
                pr.push_back(i);
            for(int j=i*2;j<=10000;j++)
                h[i] = true;
        }
    }
    cp = pr.size();
}
vector<ll> p,q;
ll pw(const ll x, const ll n, const ll mod){
    if(n==0)
        return 1;
    if(n==1)
        return x%mod;
    ll tmp = pw(x,n/2,mod);
    tmp = (tmp*tmp)%mod;
    if(n&1){
        tmp = (tmp*x)%mod;
    }
    return tmp;

}
ll gauss(const ll mod){
    //cout<<"mod="<<mod<<endl;
    ll ans = 1;
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            b[i][j] = a[i][j];
    for(int i=0;i<n;i++){
        ll mid = i;
        for(int j=i;j<n;j++){
            if(b[j][i] > b[mid][i])
                mid = j;
        }
        if(mid !=i){
            for(int j=i;j<n;j++){
                swap(b[i][j],b[mid][j]);
            }
            ans = (mod-ans)%mod;
        }

        if(b[i][i] == 0)
            return 0;
        ans=(ans*b[i][i])%mod;
        ll rev = pw(b[i][i],mod-2,mod);
        //cout<<"rev= "<<rev<<" "<<b[i][i]<<" "<<(rev*b[i][i])%mod<<endl;
        for(int j=i+1;j<n;j++){
            ll old = b[j][i];
            for(int k=i;k<n;k++){
                b[j][k] = (b[j][k] - (b[i][k]*rev*old)%mod+mod)%mod;
            }
        }

        // for(int i=0;i<n;i++){
        //     for(int j=0;j<n;j++){
        //      cout<<b[i][j]<<" ";
        //     }
        //     cout<<endl;
        // }
    }
    
    return ans;
}
ll chinese(){
    int sz = p.size();
    ll ans = 0;
    ll mi[200];
    for(int i=0;i<sz;i++){
        mi[i] = 1;
        for(int j=0;j<sz;j++)
            if(i!=j)
                mi[i]*=p[j];
    }
    for(int i=0;i<sz;i++){
        ll t = pw(mi[i],p[i]-2,p[i]);
        ans +=(q[i]*t*mi[i])%m;
        //cout<<q[i]<<" "<<mi[i]<<" "<<t<<endl;
    }
    return ans;

}
int main(){
    ios::sync_with_stdio(0);
    init();
    while(cin>>n>>m){
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                cin>>a[i][j];
        p.clear();
        q.clear();
        for(int i=0;i<cp;i++){
            if(m%pr[i] == 0){
                p.push_back(pr[i]);
                q.push_back(gauss(pr[i]));
            }
        }
        

        ll ans = chinese()%m;
        cout<<ans<<endl;
    }
}
