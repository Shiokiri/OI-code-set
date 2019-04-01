#include <iostream>
#include <cstdio>
#include <ctime>
#include <cstdlib>

using namespace std;
const int N = 100005;
class Fhq_Treap
{
    private:
        int ch[N][2]; //左/右儿子 
        int val[N]; //权值 
        int siz[N]; //子树大小 
        int pri[N]; //随机权值 
        int point, root; //结点个数 根  
        int x, y, z; //分裂树根 
        
        void update(int x)
        {
            siz[x] = siz[ch[x][0]] + siz[ch[x][1]] + 1;
        }
        int New(int v)
        {
            siz[++point] = 1;
            val[point] = v;
            pri[point] = rand();
            return point;
        }
        void split(int now, int k, int &x, int &y)
        {
            if(!now) x = y = 0;
            else
            {
                if(val[now] <= k)
                {
                    x = now;
                    split(ch[now][1], k, ch[now][1], y);
                }
                else
                {
                    y = now;
                    split(ch[now][0], k, x, ch[now][0]);
                }
                update(now);
            }
        }
        int merge(int x, int y)
        {
            if(!x || !y) return x + y;
            if(pri[x] < pri[y])
            {
                ch[x][1] = merge(ch[x][1], y);
                update(x);
                return x;
            }
            else
            {
                ch[y][0] = merge(x, ch[y][0]);
                update(y);
                return y;
            }
        }
        int Kth(int now, int k)
        {
            while(1)
            {
                if(k <= siz[ch[now][0]])
                    now = ch[now][0];
                else if(k == siz[ch[now][0]] + 1)
                    return now;
                else k -= siz[ch[now][0]] + 1, now = ch[now][1];
            }
        }
    public:
        void Insert(int v)
        {
            split(root, v, x, y);
            root = merge(merge(x, New(v)), y);
        }
        void Delete(int v)
        {
            split(root, v, x, z);
            split(x, v - 1, x, y);
            y = merge(ch[y][0], ch[y][1]);
            root = merge(merge(x, y), z);
        }
        int Rank(int v)
        {
            int ans = 0;
            split(root, v - 1, x, y);
            ans = siz[x] + 1;
            root = merge(x, y);
            return ans;
        }
        int Atrank(int v)
        {
            return val[Kth(root, v)];
        }
        int Pre(int v)
        {
            int ans = 0;
            split(root, v - 1, x, y);
            ans = val[Kth(x, siz[x])];
            root = merge(x, y);
            return ans;
        }
        int Next(int v)
        {
            int ans = 0;
            split(root, v, x, y);
            ans = val[Kth(y, 1)];
            root = merge(x, y);
            return ans;
        }
};
class Fhq_Treap treap;

int main()
{
    srand((unsigned)time(NULL));
    int n, opt, x;
    cin >> n;
    while(n--)
    {
        cin >> opt >> x;
        switch(opt)
        {
            case 1: treap.Insert(x); break;
            case 2: treap.Delete(x); break;
            case 3: cout << treap.Rank(x) << endl; break;
            case 4: cout << treap.Atrank(x) << endl; break;
            case 5: cout << treap.Pre(x) << endl; break;
            case 6: cout << treap.Next(x) << endl; break;
        }
    }
    return 0;
}