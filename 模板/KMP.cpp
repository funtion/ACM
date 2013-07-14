#include <iostream>
#include <cstring>
using namespace std;
char pat[11030];
int m[11030][50],fail[11030],len;
void KMP(){
    memset(fail,0,sizeof(fail));
    for(int i=0;i<=len;i++){//每一个前缀
        int mp = 0;
        for(int j=i;j>=1;j--){//前缀的后缀
            bool flag = true;
            for(int k=j;k<=i;k++){
                if(pat[k] != pat[k-j]){
                    flag = false;
                    break;
                }
            }
            if(flag){
                mp = i-j+1;
            }
        }
        fail[i+1] = mp;
    }
}
void build(){
    memset(m,0,sizeof(m));
    m[0][pat[0]-'a'] = 1;
    for(int i=1;i<=len;i++){
        memcpy(m[i],m[fail[i]],sizeof(m[i]));
        if(i!=len)
            m[i][pat[i]-'a'] = i+1;
    }
}
int main()
{
    while(cin>>pat,pat[0]!='0'){
        len =strlen(pat);
        KMP();
        build();
        for(int i=0;i<=len;i++){
            cout<<i;
            for(int j=0;j<26;j++){
                cout<<" "<<m[i][j];
            }
            cout<<endl;
        }
    }
    return 0;
}
