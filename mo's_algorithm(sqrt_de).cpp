#include<bits/stdc++.h>
using namespace std;
#define optimize()                 \
    ios_base ::sync_with_stdio(0); \
    cin.tie(0);                    \
    cout.tie(0);
#define ll long long int
#define endl '\n'
#define block 555
/////////////////////////////////////////
struct query{
    int i;
    int l;
    int r;
};
query Q[200001];
int arr[200001],ans[200001];
int fre[200001];
int cnt=0;
bool cmp(query a,query b){
    if(a.l/block != b.l/block)
    return a.l/block < b.l/block;

    return a.r < b.r;
}
void add(int pos){
    fre[arr[pos]]++;
    if(fre[arr[pos]]==1) 
    cnt++;
}
void remove(int pos){
    fre[arr[pos]]--;
    if(!fre[arr[pos]]) 
    cnt--;
}
int32_t main(){
    optimize();
    int n,q; cin>>n>>q;
    for(int i=0;i<n;i++) cin>>arr[i];
    for(int i=0;i<q;i++){
        cin>>Q[i].l>>Q[i].r;
        Q[i].i=i,Q[i].l--,Q[i].r--;
    }
    sort(Q,Q+q,cmp);
    int l=0,r=-1;
    for(int i=0;i<q;i++){
        int x=Q[i].l;
        int y=Q[i].r;
        while(l>x){
            l--, add(l);
        }
        while(r<y){
            r++,add(r);
        }
        while(l<x){
            remove(l),l++;
        }
        while(r>y){
            remove(r),r--;   
        }
        ans[Q[i].i]=cnt;
    }
    for(int i=0;i<q;i++) 
    cout<<ans[i]<<endl;
}
