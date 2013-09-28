//automachine
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
/////////////fial/////////////
#include <iostream>
#include <string>
using namespace std;

int fail[1000005];

int kmp (const string& s1, const string& s2, int n) {
    fail[0] = 0;
    for (int i=1; i<=n; ++i) {
        int i1 = fail[i-1];
        while (i1!=0 && s1[i1] != s1[i-1]) i1 = fail[i1];

        if (s1[i1] == s1[i-1] && i!=1) fail[i] = i1+1;
        else fail[i] = i1;
    }
    //cout << s1 << endl;
    //for (int i=0; i!=n; ++i) cout << fail[i] << ' '; cout << endl;
    int j=0, k=0;
    while (j!=n) {
        if (s1[k] == s2[j]) {
            ++j; ++k;
        } else {
            while (s1[k] != s2[j] && k!=0) k = fail[k];
            if (s1[k] == s2[j]) ++k;
            ++j;
        }
    }
    return k;
}

int n;
int main()
{
    //cout << kmp("abcDabcEabcDabcF", "", 16);
    while (cin>>n)
    {
        for (int i=0; i!=n; ++i) {
            string s;
            cin >> s;
            string s1 = s.substr(0, s.length()/2);
            string s2 = s.substr(s.length() - s.length()/2, s.length()/2);
            //cout << s1 << '\t' << s2 << endl;

            cout << kmp(s1,s2,s1.length()) << endl;

        }
    }
}
////////////////////////////

