int count_coprime(int val,const vector<int>& fact) {
    // uses inclusion exclusion 
    // send unique PF here
    int cnt=0;
    int sz=fact.size();
    for(int i=1;i<(1<<sz);i++) {
        int div=1;
        int bits=0;
        for(int j=0;j<sz;j++) {
            if((i>>j)&1) {
                div*=fact[j];
                bits++;
            }
        }
        if(bits%2) cnt+=(val/div);
        else cnt-=(val/div);
    }
    return val-cnt; // it returns how many coprimes of n under [1,val].
}
