/*******************************************************************
* 时间复杂度：O(N+M)
* 说明：有向图强连通分量
*******************************************************************/
const int N = 10005;

vector<int> node[N];

struct Kosaraju
{
    int sz, index = 0;
    vector<int> vis, ord;
    vector<vector<int>> rev;
    vector<int> id; //强连通分量编号
    Kosaraju(int x)
    {
        sz = x;
        vis.resize(sz + 1);
        id.resize(sz + 1);
        rev.resize(sz + 1);
        ord.resize(1);
        for (int i = 1; i <= sz; ++i)
        {
            for (auto e : node[i])
            {
                rev[e].push_back(i);
            }
        }
        for (int i = 1; i <= sz; ++i) if (vis[i] == 0) dfs1(i);
        for (int i = sz; i >= 1; --i) if (id[ord[i]] == 0) index++, dfs2(ord[i]);
    }

    void dfs1(int x)
    {
        vis[x] = 1;
        for (auto e : node[x])
        {
            if (vis[e] == 0) dfs1(e);
        }
        ord.push_back(x);
        return;
    }

    void dfs2(int x)
    {
        id[x] = index;
        for (auto e : rev[x])
        {
            if (id[e] == 0) dfs2(e);
        }
        return;
    }
};