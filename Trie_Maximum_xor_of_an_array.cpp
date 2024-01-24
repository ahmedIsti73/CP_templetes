#include <bits/stdc++.h>
using namespace std;
#define ll long long int
class trieNode
{
public:
    trieNode *zero;
    trieNode *one;
};
class xor_trie{
public:
    void insert(trieNode *root, ll n){
        trieNode *cur = root;
        for (int i = 31; i >= 0; i--){
            if ((n & (1LL << i))){
                if (cur->one == NULL){
                    cur->one = new trieNode();
                }
                cur = cur->one;
            }
            else{
                if (cur->zero == NULL)
                {
                    cur->zero = new trieNode();
                }
                cur = cur->zero;
            }
        }
    }
    ll findMaxXor(trieNode *root, ll n){
        trieNode *cur = root;
        ll ans = 0;
        for (int i = 31; i >= 0; i--){
            if ((n & (1LL << i))){
                if (cur->zero != NULL){
                    ans += (1LL << i);
                    cur = cur->zero;
                }
                else
                    cur = cur->one;
            }
            else{
                if (cur->one != NULL){
                    ans += (1LL << i);
                    cur = cur->one;
                }
                else
                    cur = cur->zero;
            }
        }
        return ans;
    }
    ll maxXor(vector<ll> &v, ll n){
        trieNode *root = new trieNode();
        ll ans = 0;
        for (int i = 0; i < n; i++){
            insert(root, v[i]);
        }
        for (int i = 0; i < n; i++){
            ans = max(ans, findMaxXor(root, v[i]));
        }
        return ans;
    }
};
int32_t main(){
    ll n;
    cin >> n;
    vector<ll> v(n);
    for (ll i = 0; i < n; i++)
        cin >> v[i];
    xor_trie t;
    cout << t.maxXor(v, n - 1) << endl;
}
