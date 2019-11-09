#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;
int T,n,a[10005],Max,flag,Max2,sum;
int t[10005],canto[100005];
int b[10005],avis[10005],ans[100005];
int ed;
void dfs(int k) {
	if(k > n) {
		int res = 0;
		for(int i = 1; i <= n; i++)
			res += t[i] * a[i];
		canto[res] = 1;
		Max = max(Max, res);
		return;
	}
	for(int i = 0; i <= 10; i++) {
		t[k] = i; dfs(k+1);
	}
}
void dfs3(int k) {
	if(k > ed) {
		int res = 0;
		for(int i = 1; i <= ed; i++)
			res += t[i] * b[i];
		Max2 = max(Max2, res);
		ans[res] = 1;
		return;
	}
	for(int i = 0; i <= 10; i++) {
		t[k] = i; dfs3(k+1);
	}
}
void dfs2(int k)
{
	if(flag) return;
	if(k > ed)
	{
		memset(ans,0,sizeof(ans)); Max2 = 0;
		dfs3(1);
//		for(int i = 1; i <= 25; i++)
//			cout << ans[i] << " ";
//		cout << endl;
		int ttt = 1;
		int endi = min(Max,Max2);
		endi = min(endi, sum);
//		cout << endi << endl;
		for(int i = 1; i <= endi; i++)
			if(ans[i] != canto[i])
				ttt = 0;
//		for(int i = Max + 1; i <= sum; i++)
//			if(ans[i] == 0)
//				ttt = 0;
		if(ttt) flag = 1;
		return;
	}
	for(int i = 1; i <= n; i++)
		if(!avis[i])
	{
		if(flag) return;
		b[k] = a[i];
		avis[i] = 1;
		dfs2(k+1);
		avis[i] = 0;
	}
}
int main()
{
	freopen("money.in","r",stdin);
	freopen("money.out","w",stdout);
	scanf("%d", &T);
	while(T--)
	{
		Max = 0; sum = 0; 
		memset(canto, 0, sizeof(canto));
		scanf("%d", &n);
		for(int i = 1; i <= n; i++)
			scanf("%d", &a[i]), sum += a[i];
		dfs(1);
//		for(int i = 1; i <= 25; i++)
//			cout << canto[i] << " ";
//		for(int i = 1; i <= sum; i ++)
//			if(canto[i] == 0)
//		{
//			Max = i;
//		}
//		cout << endl;
//		cout << Max << endl;
		flag = 0;
		int isans = 1;
		for(int i = 1; i <= n; i++) {
			ed = i; dfs2(1);
			if(flag) {
				isans = 0;
				printf("%d\n", i);
				break;
			}
		}
		if(isans == 1) printf("%d\n", n);
	}
	return 0;
}
/*
2
4
3 19 10 6
5 11 29 13 19 17
*/
