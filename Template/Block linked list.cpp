#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;
const int N = 100005, S = 405;
int n, m, w, sq, rebuild, cnt;
int a[N], in[N], c[S][N], s[S];
vector<int> v[S];

void Rebuild()
{
	cnt = 0;
	for(int i = 0; i <= w; i++) {
		for(int j = 0; j < s[i]; j++) a[++cnt] = v[i][j], c[i][a[cnt]] = 0;
		v[i].clear(); s[i] = 0;
	}
	for(int i = 1; i <= n; i++) {
		v[in[i]].push_back(a[i]);
		c[in[i]][a[i]]++; s[in[i]]++;
	}
	cnt = 0;
}
void update(int l, int r)
{
	vector<int>::iterator it;
	int e = 0, k = 0;
	while(e + s[k] < r) e += v[k++].size();
	e = r - e - 1;
	int x = v[k][e]; it = v[k].begin() + e; v[k].erase(it);
	c[k][x]--; s[k]--;
	e = 0, k = 0;
	while(e + s[k] < l) e += v[k++].size();
	e = l - e - 1; it = v[k].begin() + e; v[k].insert(it, x);
	c[k][x]++; s[k]++;
}
int query(int l, int r, int k)
{
	int e = 0, L = 0, R = 0, res = 0;
	while(e + s[L] < l) e += s[L++];
	int el = l - e - 1;
	e = 0;
	while(e + s[R] < r) e += s[R++];
	int er = r - e - 1;
	for(int i = L + 1; i < R; i++) res += c[i][k];
	if(L != R) {
		for(int i = el; i < s[L]; i++) res += (v[L][i] == k);
		for(int i = 0; i <= er; i++) res += (v[R][i] == k);
	}
	else for(int i = el; i <= er; i++) res += (v[L][i] == k);
	return res;
}
int main()
{
	scanf("%d", &n);
	sq = sqrt(n); w = n / sq;
	rebuild = 7 * sq;
	for(int i = 1; i <= n; i++) in[i] = i / sq, s[in[i]]++;
	for(int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		v[in[i]].push_back(a[i]);
		c[in[i]][a[i]]++;
	}
	scanf("%d", &m);
	int opt, l, r, k;
	while(m--)
	{
		cnt++;
		if(cnt > rebuild) Rebuild();
		scanf("%d", &opt);
		if(opt == 1) {
			scanf("%d%d", &l, &r);
			update(l, r);
		}
		else if(opt == 2) {
			scanf("%d%d%d", &l, &r, &k);
			printf("%d\n", query(l, r, k));
		}
	}
	return 0;
}