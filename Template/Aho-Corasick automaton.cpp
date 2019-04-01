#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <queue>

using namespace std;
struct Tree
{
    int fail;
    int vis[26];
    int end;
}AC[1000005];
int cnt = 0;
void build(string s)
{
    int l = s.length();
    int now = 0;
    for(int i = 0; i < l; i++)
    {
        if(AC[now].vis[s[i] - 'a'] == 0)
            AC[now].vis[s[i] - 'a'] = ++cnt;
        now = AC[now].vis[s[i] - 'a'];
    }
    AC[now].end += 1;
}
void get_fail()
{
    queue<int> Q;
    for(int i = 0; i < 26; i++)
    {
        if(AC[0].vis[i] != 0)
        {
            AC[AC[0].vis[i]].fail = 0;
            Q.push((AC[0].vis[i]));
        }
    }
    while(!Q.empty())
    {
        int u = Q.front();
        Q.pop();
        for(int i = 0; i < 26; i++)
        {
            if(AC[u].vis[i] != 0)
            {
                AC[AC[u].vis[i]].fail = AC[AC[u].fail].vis[i];
                Q.push(AC[u].vis[i]);
            }
            else AC[u].vis[i] = AC[AC[u].fail].vis[i];
        }
    }
}
int AC_query(string s)
{
    int l = s.length();
    int now = 0, ans = 0;
    for(int i = 0; i < l; i++)
    {
        now = AC[now].vis[s[i] - 'a'];
        for(int t = now; t && AC[t].end != -1; t = AC[t].fail)
        {
            ans += AC[t].end;
            AC[t].end = -1;
        }
    }
    return ans;
}
int main()
{
    int n; string s;
    cin >> n;
    for(int i = 1; i <= n; i++)
    {
        cin >> s;
        build(s);
    }
    AC[0].fail = 0;
    get_fail();
    cin >> s;
    cout << AC_query(s) << endl;
    return 0;
}