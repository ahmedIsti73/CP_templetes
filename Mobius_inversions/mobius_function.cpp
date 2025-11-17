const int MX=1000001;
vector<int> mu(MX);
vector<int> phi(MX);
vector<int> spf(MX);
vector<ll> h(MX,0); // for LCM
vector<int> primes;
void mobius_sieve(){
  mu[1]=1; h[1]=1;
  for(int i=2;i<MX;i++){
    if(!spf[i]){
        spf[i]=i;
        mu[i]=-1;
        phi[i]=i-1;
        h[i]=(1-i+MOD);
        primes.PB(i);
    }
    for(int p:primes){
        if(1LL*i*p>=MX) break;
        spf[i*p]=p;
        if(!(i%p)){
          h[i*p]=h[i];
          phi[i*p]=phi[i]*p;
          mu[i*p]=0;
          break;
        }else {
          mu[i*p]=-mu[i];
          phi[i*p]=phi[i]*(p-1);
          h[i*p]=(h[i]*h[p])%MOD;
        }
    }
  }
}
