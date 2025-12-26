/**
 * Disjoint Set Union (DSU) with Path Compression and Union by Size.
 * * STORAGE STRATEGY (Vector 'p'):
 * - p[i] >= 0 : p[i] is the parent of i.
 * - p[i] < 0  : i is a root. -p[i] is the size of the set.
 * * TIME COMPLEXITY:
 * - O(alpha(N)) per operation (effectively constant).
 */

struct DSU {
	vector<int> p;
	int numsets;
	DSU(int N) {
		p.assign(N,-1);
		numsets=N;
	}
	int find_set(int i) {
		return (p[i]<0) ? i : p[i]=find_set(p[i]);
	}
	
	bool is_same_set(int i,int j) {
		return find_set(i)==find_set(j);
	}
	
	int size_of_set(int i) {
		return -p[find_set(i)];
	}
	
	void union_set(int i,int j) {
		i=find_set(i);
		j=find_set(j);
		if(i==j) return;
		
		if(abs(p[i])<abs(p[j])) swap(i,j);
		p[i]+=p[j];
		p[j]=i;
		numsets--;
	}
};
