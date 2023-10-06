#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#pragma GCC optimization ("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
#define optimize()                 \
    ios_base ::sync_with_stdio(0); \
    cin.tie(0);                    \
    cout.tie(0);
void file(){
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
}
#define endl '\n'
#define ll long long int
#define mem(arr,x) memset(arr,x,sizeof arr)
//:::::::::::::::::::::::::::::::::::::::GlitcH::::::::::::::::::::::::::::::::
string s1,s2;
ll dp[4000][4000];
int32_t main()
{
    file();
    optimize();
    cin>>s1>>s2;
    ll x=s1.size(),y=s2.size();
    for(int i=1;i<=x;i++){
        for(int j=1;j<=y;j++){
            if(s1[i-1]==s2[j-1]) dp[i][j]=1+dp[i-1][j-1];
            else dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
        }
    }
    cout<<dp[x][y]<<endl;
} 
