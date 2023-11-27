/*******************************************************************
* 时间复杂度：O(n+m)
* 说明：
* 1.求有向图强连通分量+缩点
* 2.求无向图点双连通分量和割点
* 3.求无向图边双连通分量和割边
*******************************************************************/
struct SCC
{
    int sz, cnt, ord;
    stack<int> stk;
    vector<int> dfn, low, id;
    vector<vector<int>> g; // 新图
    SCC(int x)
    {
        sz = x; // 点数
        cnt = 0; // 连通分量个数
        ord = 0; // 时间戳
        dfn.resize(sz + 1); // dfs序
        low.resize(sz + 1); // 能到达的最小dfn
        id.resize(sz + 1); // 连通分量编号
    }
    void dfs(int x)
    {
        stk.push(x);
        dfn[x] = low[x] = ++ord;
        for (auto e : node[x])
        {
            if (dfn[e] == 0) // 未访问过
            {
                dfs(e);
                low[x] = min(low[x], low[e]);
            }
            else if (id[e] == 0) // 在栈中
            {
                low[x] = min(low[x], dfn[e]);
            }
        }
        if (dfn[x] == low[x]) // x为强连通分量的根
        {
            cnt++;
            while (stk.top() != x)
            {
                id[stk.top()] = cnt;
                stk.pop();
            }
            id[stk.top()] = cnt;
            stk.pop();
        }
        return;
    }
    void shrink()
    {
        for (int i = 1; i <= sz; ++i)
        {
            if (id[i] == 0) dfs(i);
        }
        return;
    }
    void rebuild()
    {
        g.resize(cnt + 1);
        for (int i = 1; i <= sz; ++i)
        {
            for (auto e : node[i])
            {
                if (id[i] != id[e]) g[id[i]].push_back(id[e]);
            }
        }
        return;
    }
};

struct VBCC
{
    int sz, ord;
    stack<int> stk;
    vector<int> dfn, low, tag;
    vector<vector<int>> bcc;
    VBCC(int x)
    {
        sz = x; // 点数
        ord = 0; // 时间戳
        dfn.resize(sz + 1); // dfs序
        low.resize(sz + 1); // 能到达的最小dfn
        tag.resize(sz + 1); // 是否割点
    }
    void dfs(int x, int fa)
    {
        stk.push(x);
        dfn[x] = low[x] = ++ord;
        int son = 0;
        for (auto e : node[x])
        {
            if (dfn[e] == 0) // 未访问过
            {
                son++;
                dfs(e, x);
                low[x] = min(low[x], low[e]);
                if (low[e] >= dfn[x]) // x可能是割点
                {
                    if (fa) tag[x] = 1; // 不是dfs的根，则为割点
                    bcc.emplace_back();
                    while (stk.top() != e)
                    {
                        bcc.back().push_back(stk.top());
                        stk.pop();
                    }
                    bcc.back().push_back(stk.top());
                    stk.pop();
                    bcc.back().push_back(x);
                }
            }
            else if (e != fa) // 祖先
            {
                low[x] = min(low[x], dfn[e]);
            }
        }
        if (fa == 0 && son >= 2) tag[x] = 1; // 特判dfs根是否为割点
        if (fa == 0 && son == 0) bcc.emplace_back(1, x); // 特判dfs根是否单独为一个分量
        return;
    }
    void work()
    {
        for (int i = 1; i <= sz; ++i)
        {
            if (dfn[i]) continue;
            while (stk.size()) stk.pop();
            dfs(i, 0);
        }
        return;
    }
};

struct EBCC
{
    int sz, ord;
    vector<int> dfn, low, tag, vis;
    vector<vector<int>> bcc;
    EBCC(int x, int y)
    {
        sz = x; // 点数
        ord = 0; // 时间戳
        dfn.resize(sz + 1); // dfs序
        low.resize(sz + 1); // 能到达的最小dfn
        vis.resize(sz + 1); // 是否已加入连通分量
        tag.resize(y + 1); // 是否割边
    }
    void dfs0(int x, int fa)
    {
        dfn[x] = low[x] = ++ord;
        for (auto e : node[x])
        {
            if (dfn[e.to] == 0) // 未访问过
            {
                dfs0(e.to, x);
                low[x] = min(low[x], low[e.to]);
                if (low[e.to] > dfn[x]) tag[e.id] = 1; // 是割边
            }
            else if (e.to != fa) // 祖先
            {
                low[x] = min(low[x], dfn[e.to]);
            }
        }
        return;
    }
    void dfs(int x)
    {
        bcc.back().push_back(x);
        vis[x] = 1;
        for (auto e : node[x])
        {
            if (vis[e.to]) continue;
            if (tag[e.id]) continue;
            dfs(e.to);
        }
        return;
    }
    void work()
    {
        for (int i = 1; i <= sz; ++i)
        {
            if (dfn[i]) continue;
            dfs0(i, 0);
        }
        for (int i = 1; i <= sz; ++i)
        {
            if (vis[i]) continue;
            bcc.emplace_back();
            dfs(i);
        }
        return;
    }
};