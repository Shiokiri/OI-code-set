#include <iostream>
#include <cstdio>

using namespace std;
typedef long long ll;
const int N = 3e6+5, P = 998244353, G = 3;
int n, Gi;
int r[N], len = 1, L;
ll x[N], y[N], z[N];
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
    if(op == -1) {
        int linv = ksm(len, P-2, P);
        for(int i = 0; i < len; i++) f[i] = f[i]*linv%P;
    }
}
void INV(int n, ll *f, ll *g)
{
    if(n == 1) {
        g[0] = ksm(f[0], P-2, P);
        return;
    }
    INV((n + 1) >> 1, f, g);
    len = 1, L = 0;
    while(len < (n << 1)) len <<= 1, L++;
    for(int i = 1; i < len; i++) r[i] = (r[i>>1]>>1)|((i&1)<<(L-1));
    for(int i = 0; i < n; i++) z[i] = f[i];
    for(int i = n; i < len; i++) z[i] = 0;
    NTT(z, 1); NTT(g, 1);
    for(int i = 0; i < len; i++) g[i] = g[i] * ((2 - z[i]*g[i]%P + P) % P) % P;
    NTT(g, -1);
    for(int i = n; i < len; i++) g[i] = 0;
}
int main()
{
    Gi = ksm(G, P - 2, P);
    scanf("%d", &n);
    for(int i = 0; i < n; i++) scanf("%lld", &x[i]), x[i] = (x[i]+P) % P;
    INV(n, x, y);
    for(int i = 0; i < n; i++) printf("%lld ", y[i]);
    return 0;
}
