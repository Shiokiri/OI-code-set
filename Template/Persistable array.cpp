#include <iostream>
#include <cstdio>

using namespace std;
const int N = 1e6;
const int _ = 22000005;
int n, m;
struct Segment_Tree {
#define mid ((l + r) >> 1)
	int root[N], T[_], L[_], R[_];
	int cnt;
	int build(int l, int r) {
		int p = ++cnt;
		if(l == r) {
			scanf("%d", &T[p]);
			return p;
		}
		L[p] = build(l, mid);
		R[p] = build(mid + 1, r);
		return p;
	}
	int update(int pre, int l, int r, int x, int k) {
		int p = ++cnt;
		if(l == r) {
			T[p] = k;
			return p;
		}
		L[p] = L[pre];
		R[p] = R[pre];
		if(x <= mid) L[p] = update(L[pre], l, mid, x, k);
		else R[p] = update(R[pre], mid + 1, r, x, k);
		return p;
	}
	int query(int p, int l, int r, int x) {
		if(l == r) return T[p];
		int ans = 0;
		if(x <= mid) ans = query(L[p], l, mid, x);
		else ans = query(R[p], mid + 1, r, x);
		return ans;
	}
#undef mid
}
int main() {
	scanf("%d%d", &n, &m);
	T.build(1, n);
	T.root[0] = 1;
	for(int i = 1, v, p, x, k; i <= m; i++) {
		scanf("%d%d%d", &v, &p, &x);
		if(p == 1) {
			scanf("%d", &k);
			T.root[i] = T.update(T.root[v], 1, n, x, k);
		} else if(p == 2) {
			T.root[i] = T.root[v];
			int ans = T.query(T.root[v], 1, n, x);
			printf("%d\n", ans);
		}
	}
	return 0;
}
