  int n; cin>>n;
  int mx=0;
  vector<int> v(n+1);
  mi sum=0;
  for(int i=1;i<=n;i++) {
    cin>>v[i];
    mx=max(mx,v[i]);
    sum+=v[i];
  }
  vector<int>fre(mx+1,0);
  for(int i=1;i<=n;i++) fre[v[i]]++;
  vector<ll>mp(mx+1,0);
  for(int i=1;i<=mx;i++) {
    for(int j=i;j<=mx;j+=i) {
      ll k=j/i;
      mp[i]+=1LL*k*fre[j];
    }
  }
  mi ans=0;
  for(int i=1;i<=mx;i++) {
    mi term=mi(i)*mi(h[i])*mi(mp[i])*mi(mp[i]);
    ans+=term;
  }
  cout<<ans<<endl; // all pair lcm sum
  cout<<mi(ans-sum)<<endl; // exclude i=j
  mi inv=mi((MOD+1)/2);
  cout<<mi(mi(ans-sum)*inv)<<endl; // all pair lcm i<j
