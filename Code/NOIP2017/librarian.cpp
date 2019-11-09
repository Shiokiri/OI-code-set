#include<iostream>
#include<cstdio>
int bianma[1005],xuqiu[1005];
int changdu[1005];
using namespace std;
int chengfang(int a){
	int b=1;
	for(int i=1;i<=a;i++)
		b=b*10;
	return b;
}
int main(){
	freopen("librarian.in","r",stdin);
	freopen("librarian.out","w",stdout);
	int n,q,c;
	int ans=10000005;
	cin>>n>>q;
	for(int i=1;i<=n;i++) 
	  	scanf("%d",&bianma[i]);
	for(int i=1;i<=q;i++)
		scanf("%d%d",&changdu[i],&xuqiu[i]);
	for(int i=1;i<=q;i++){
		for(int j=1;j<=n;j++){
			c=chengfang(changdu[i]);
			if(bianma[j]%c==xuqiu[i]){
				if(bianma[j]<ans) ans=bianma[j];}
		}
		if(ans==10000005) printf("-1\n");
		else printf("%d\n",ans);
		ans=10000005;
	}
	return 0;
}
