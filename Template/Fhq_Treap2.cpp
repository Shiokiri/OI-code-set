#include <iostream>
#include <cstdio>
#include <cmath>
#include <ctime>
#include <cstdlib>

using namespace std;
const int N = 100005;
const int inf = 0x7fffffff;
int n, m;
class Fhq_Treap
{
    private:
        int ch[N][2]; //左/右儿子 
        int val[N]; //权值 
        int siz[N]; //子树大小 
        int pri[N]; //随机权值
        int root; // 根  
        int point; //结点个数 
        int x, y, z; //分裂树根 
        int f[N]; //tag
        
        void update(int x)
        {
            siz[x] = siz[ch[x][0]] + siz[ch[x][1]] + 1;
        }
        void pushdown(int x)
        {
            swap(ch[x][0], ch[x][1]);
            if(ch[x][0]) f[ch[x][0]] ^= 1;
            if(ch[x][1]) f[ch[x][1]] ^= 1;
            f[x] = 0;
        }
        
        int New(int v)
        {
            siz[++point] = 1;
            val[point] = v;
            pri[point] = rand();
            return point;
        }
        void split(int i, int k, int &x, int &y)
        {
            if(!i) { x = y = 0; return; }
            if(f[i]) pushdown(i);
            if(siz[ch[i][0]] < k)
            {
                x = i;
                split(ch[i][1], k - siz[ch[i][0]] - 1, ch[i][1], y);
            }
            else
            {
                y = i;
                split(ch[i][0], k, x, ch[i][0]);
            }
            update(i);
        }
        int merge(int x, int y)
        {
            if(!x || !y) return x + y;
            if(pri[x] < pri[y])
            {
                if(f[x]) pushdown(x);
                ch[x][1] = merge(ch[x][1], y);
                update(x);
                return x;
            }
            else
            {
                if(f[y]) pushdown(y);
                ch[y][0] = merge(x, ch[y][0]);
                update(y);
                return y;
            }
        }
        void Print(int i)
        {
            if(!i) return;
            if(f[i]) pushdown(i);
            Print(ch[i][0]);
            printf("%d ", val[i]);
            Print(ch[i][1]);
        }
    public:
        void solve()
        {
            for(int i = 1; i <= n; i++)
                root = merge(root, New(i));
            for(int i = 1, l, r; i <= m; i++)
            {
                cin >> l >> r;
                split(root, l - 1, x, y);
                split(y, r - l + 1, y, z);
                f[y] ^= 1;
                root = merge(x, merge(y, z));
            }
            Print(root);
        }
};
class Fhq_Treap treap;

int main()
{
    cin >> n >> m;
    treap.solve();
    return 0;
}