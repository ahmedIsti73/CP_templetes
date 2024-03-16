#include<bits/stdc++.h>
using namespace std;
const int max_n=100005;
const int loG=18;
int a[max_n];
int m[max_n][loG];
int query(int l,int r){
    int length=r-l+1;
    int k=31-__builtin_clz(length);
    return min(m[l][k],m[r-(1<<k)+1][k]);
}
int32_t main(){
    int n; cin>>n;
    // read input
    for(int i=0;i<n;i++){
        cin>>a[i];
        m[i][0]=a[i];
    }
    // preprocessing 
    for(int k=1;k<loG;k++){
        for(int i=0;i+(1<<k)-1<n;i++){
            m[i][k]=min(m[i][k-1],m[i+(1<<(k-1))][k-1]);
        }
    }
    // ans query
    int q; cin>>q;
    while(q--){
        int l,r; cin>>l>>r;
        cout<<query(l,r)<<endl;
    }
}
