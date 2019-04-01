#include <iostream>
#include <cstdio>

using namespace std;
const int MAXL = 100005;
const int inf = 0x7fffffff;
class node
{
    public:
        int v, father;
        int ch[2];
        int sum;
        int recy;
};
class Splay
{
    #define root e[0].ch[1]
    private:
        class node e[MAXL];
        int n, points;
        void update(int x)
        {
            e[x].sum = e[e[x].ch[0]].sum + e[e[x].ch[1]].sum + e[x].recy;
        }
        int identify(int x)
        {
            return e[e[x].father].ch[0] == x ? 0 : 1;
        }
        void connect(int x, int f, int son)
        {
            e[x].father = f;
            e[f].ch[son] = x;
        }
        void rotate(int x)
        {
            int y = e[x].father;
            int mroot = e[y].father;
            int mrootson = identify(y);
            int yson = identify(x);
            int B = e[x].ch[yson ^ 1]; 
            connect(B, y, yson);
            connect(y, x, yson ^ 1);
            connect(x, mroot, mrootson);
            update(y); update(x);
        }
        void splay(int at, int to)
        {
            to = e[to].father;
            while(e[at].father != to)
            {
                int up = e[at].father;
                if(e[up].father == to) rotate(at);
                else if(identify(up) == identify(at))
                {
                    rotate(up);
                    rotate(at);
                }
                else
                {
                    rotate(at);
                    rotate(at);
                }
            }
        }
        int crepoint(int v, int father)
        {
            n++;
            e[n].v = v;
            e[n].father = father;
            e[n].sum = e[n].recy = 1;
            return n;
        }
        void destroy(int x)
        {
            e[x].v = e[x].ch[0] = e[x].ch[1] = e[x].sum = e[x].father = e[x].recy = 0;
            if(x == n) n--;
        }
        int insert(int v)
        {
            points++;
            if(n == 0)
            {
                root = 1;
                crepoint(v, 0);
            }
            else
            {
                int now = root;
                while(true)
                {
                    e[now].sum++;
                    if(v == e[now].v)
                    {
                        e[now].recy ++;
                        return now;
                    }
                    int next = v < e[now].v ? 0 : 1;
                    if(!e[now].ch[next])
                    {
                        crepoint(v, now);
                        e[now].ch[next] = n;
                        return n;
                    }
                    now = e[now].ch[next];
                }
            }
            return 0;
        }
    public:
        Splay()
        {
            push(-inf); push(inf);
        }
        int getroot()
        { 
            return root;
        }
        int find(int v)
        {
            int now = root;
            while(true)
            {
                if(e[now].v == v)
                {
                    splay(now, root);
                    return now;
                }
                int next = v < e[now].v ? 0 : 1;
                if(!e[now].ch[next]) return false;
                now = e[now].ch[next];
            }
        }
        void push(int v)
        {
            int add = insert(v);
            splay(add, root);
        }
        void pop(int v)
        {
            int deal = find(v);
            if(!deal) return;
            points--;
            if(e[deal].recy > 1)
            {
                e[deal].recy --;
                e[deal].sum --;
                return;
            }
            if(!e[deal].ch[0])
            {
                root = e[deal].ch[1];
                e[root].father = 0;
            }
            else
            {
                int left = e[deal].ch[0];
                while(e[left].ch[1]) left = e[left].ch[1];
                splay(left, e[deal].ch[0]);
                int right = e[deal].ch[1];
                connect(right, left, 1);
                connect(left, 0, 1);
                update(left);
            }
            destroy(deal);
        }
        int rank(int v)
        {
            int ans = 0, now = root;
            while(true)
            {
                if(e[now].v == v) {
                    ans = ans + e[e[now].ch[0]].sum + 1;
                    break;
                }
                if(now == 0) {
                    ans = 0;
                    break;
                }
                if(v < e[now].v) now = e[now].ch[0];
                else
                {
                    ans = ans + e[e[now].ch[0]].sum + e[now].recy;
                    now = e[now].ch[1];
                }
            }
            if(now) splay(now, root);
            return ans;
        }
        int atrank(int x)
        {
            if(x > points) return -inf;
            int now = root;
            while(true)
            {
                int minused = e[now].sum - e[e[now].ch[1]].sum;
                if(x > e[e[now].ch[0]].sum && x <= minused) break;
                if(x < minused) now = e[now].ch[0];
                else {
                    x = x - minused;
                    now = e[now].ch[1];
                }
            }
            splay(now, root);
            return e[now].v;
        }
        int upper(int v)
        {
            int now = root, res = inf;
            while(now)
            {
                if(e[now].v > v && e[now].v < res) res = e[now].v;
                if(v < e[now].v) now = e[now].ch[0];
                else now = e[now].ch[1];
            }
            return res;
        }
        int lower(int v)
        {
            int now = root, res = -inf;
            while(now)
            {
                if(e[now].v < v && e[now].v > res) res = e[now].v;
                if(v > e[now].v) now = e[now].ch[1];
                else now = e[now].ch[0];
            }
            return res;
        }
    #undef root
};
class Splay sp;

int main()
{
    int n, opt, x;
    cin >> n;
    while(n--)
    {
        cin >> opt >> x;
        if(opt == 1) sp.push(x);
        else if(opt == 2) sp.pop(x);
        else if(opt == 3) printf("%d\n", sp.rank(x) - 1);
        else if(opt == 4) printf("%d\n", sp.atrank(x + 1));
        else if(opt == 5) printf("%d\n", sp.lower(x));
        else if(opt == 6) printf("%d\n", sp.upper(x));
    }
    return 0;
}