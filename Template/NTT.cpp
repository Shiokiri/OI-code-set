#include <iostream>
#include <cstdio>

using namespace std;
typedef long long ll;
const int N = 3000005;
const int P = 998244353, G = 3;
int n, m, Gi;
int r[N], len = 1, L;
ll f[N], g[N];
ll ksm(ll x, ll y, ll p) {
    ll ans = 1;
    while(y) {
        if(y & 1) ans = ans * x % p;
        x = x * x % p;
        y >>= 1;
    }
    return ans;
}
void NTT(ll *f, int op)
{
    for(int i = 0; i < len; i++) if(i < r[i]) swap(f[i], f[r[i]]);
    for(int mid = 1; mid < len; mid <<= 1) {
        ll W = ksm(op == 1 ? G : Gi, (P - 1) / (mid << 1), P);
        for(int j = 0; j < len; j += (mid << 1)) {
            ll w = 1;
            for(int k = 0; k < mid; k++, w = w * W % P) {
                int x = f[j+k], y = w * f[j+k+mid] % P;
                f[j+k] = (x + y) % P;
                f[j+k+mid] = (x - y + P) % P;
            }
        }
    }
}
int main()
{
    Gi = ksm(G, P - 2, P);
    scanf("%d%d", &n, &m);
    for(int i = 0; i <= n; i++) scanf("%lld", &f[i]), f[i]=(f[i]+P)%P;
    for(int i = 0; i <= m; i++) scanf("%lld", &g[i]), g[i]=(g[i]+P)%P;
    while(len <= n+m) len <<= 1, L++;
    for(int i = 0; i < len; i++) r[i] = (r[i>>1] >> 1) | ((i&1) << (L-1));
    NTT(f, 1); NTT(g, 1);
    for(int i = 0; i < len; i++) f[i] = f[i]*g[i]%P;
    NTT(f, -1);
    ll leninv = ksm(len, P - 2, P);
    for(int i = 0; i <= n+m; i++)
        printf("%d ", f[i] * leninv % P);
    return 0;
}
