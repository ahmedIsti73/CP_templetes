// making DSU with union by rank or hight 
// this is O(logN) couse we didnt did path compression 

struct DSU {
	vector<int> rank,parent;
	DSU (int N) {
		rank.assign(N,0);
		parent.resize(N);
		iota(all(parent),0);
	}
	int find_parent(int i) {
		if(parent[i]==i) return i;
		return find_parent(parent[i]);	
	}
	void union_set(int i,int j) {
		i=find_parent(i);
		j=find_parent(j);
		if(i==j) return;
		if(rank[i]<rank[j]) swap(i,j);
		if(rank[i]==rank[j]) rank[i]++;
		parent[j]=i;
	}
};
