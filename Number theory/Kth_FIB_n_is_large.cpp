inline ll mul(ll a,ll b,ll mod) {
	return (__int128)a*b%mod;
}
struct Mat {
	ll m[2][2];
	Mat() {m[0][0]=m[0][1]=m[1][0]=m[1][1]=0;}
};
Mat matMul(Mat A,Mat B,ll mod) {
	Mat C;
	for(int i=0;i<2;i++) {
		for(int j=0;j<2;j++) {
			for(int k=0;k<2;k++) {
				C.m[i][j]=(C.m[i][j]+mul(A.m[i][k],B.m[k][j],mod))%mod;
			}
		}
	}
	return C;
}
Mat matPow(Mat A,ll p,ll mod) {
	Mat res; res.m[0][0]=res.m[1][1]=1;
	while(p) {
		if(p&1) res=matMul(res,A,mod);
		A=matMul(A,A,mod);
		p>>=1;
	}
	return res;
}
ll kth_string(ll a,ll b,string n,ll mod) {
	if(mod==1) return 0;
	Mat T;
	T.m[0][0]=1; T.m[0][1]=1;
	T.m[1][0]=1; T.m[1][1]=0;
	Mat res;
	res.m[0][0]=1; res.m[1][1]=1;
	
	for(char c:n) {
		int digit=c-'0';
		res=matPow(res,10,mod);
		res=matMul(res,matPow(T,digit,mod),mod);
	}
	return (mul(a,res.m[1][1],mod)+mul(b,res.m[1][0],mod))%mod;
}
ll kth(ll a,ll b,ll n,ll mod) {
    if(mod==1) return 0;
    if(n==0) return a%mod;
    if(n==1) return b%mod;

    Mat T;
    T.m[0][0]=1; T.m[0][1]=1;
    T.m[1][0]=1; T.m[1][1]=0;

    // Use binary exponentiation directly
    Mat res=matPow(T,n,mod);

    return (mul(a,res.m[1][1],mod) + mul(b,res.m[1][0],mod))%mod;
}
// this can cal nth fib for n is large or <=1e18
void GLITCH_() {
	string n; cin>>n;
	cout<<kth_string(0,1,n,1e8+7)<<endl;
}
