#include<iostream>
#include<cstdio>
using namespace std;
int main(){
	freopen("score.in","r",stdin);
	freopen("score.out","w",stdout);
	double a,b,c;
	cin>>a>>b>>c;
	double ans;
	ans=0.2*a+0.3*b+0.5*c;
	cout<<ans;
	return 0;
}
