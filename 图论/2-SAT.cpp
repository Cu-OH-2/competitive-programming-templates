const int N = 2000005;

vector<int> node[N];

struct Tarjan
{
    int sz, cnt, ord;
    stack<int> stk;
    vector<vector<int>> g; // 新图
    vector<int> dfn, low, id, val;
    Tarjan(int x)
    {
        sz = x; // 点数
        cnt = 0; // 强连通分量个数
        ord = 0; // 时间戳
        dfn.resize(sz + 1); // dfs序
        low.resize(sz + 1); // 能到达的最小dfn
        id.resize(sz + 1); // 对应的强连通分量编号
        val.resize(sz + 1); // 新图点权
    }
    void dfs(int x)
    {
        stk.push(x);
        dfn[x] = low[x] = ++ord;
        for (auto e : node[x])
        {
            if (dfn[e] == 0)
            {
                dfs(e);
                low[x] = min(low[x], low[e]);
            }
            else if (id[e] == 0)
            {
                low[x] = min(low[x], low[e]);
            }
        }
        if (dfn[x] == low[x]) // x为强连通分量的根
        {
            cnt++;
            while (dfn[stk.top()] != low[stk.top()])
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

struct TwoSat
{
    int sz;
    vector<int> res;
    inline int negate(int x)
    {
        if (x > sz) return x - sz;
        else return x + sz;
    }
    TwoSat(int x)
    {
        sz = x;
        res.resize(sz + 1);
    }
    bool work()
    {
        Tarjan tj(sz * 2);
        tj.shrink();
        for (int i = 1; i <= sz; ++i)
        {
            if (tj.id[i] == tj.id[negate(i)]) return 0;
        }
        for (int i = 1; i <= sz; ++i)
        {
            res[i] = tj.id[i] < tj.id[negate(i)];
        }
        return 1;
    }
};

void solve() // P4782
{
    ll n, m;
    cin >> n >> m;
    for (int i = 1; i <= m; ++i)
    {
        bool a, b;
        ll x, y;
        cin >> x >> a >> y >> b;
        node[x + a * n].push_back(y + (!b) * n);
        node[y + b * n].push_back(x + (!a) * n);
    }
    TwoSat ts(n);
    if (!ts.work()) cout << "IMPOSSIBLE\n";
    else
    {
        cout << "POSSIBLE\n";
        for (int i = 1; i <= n; ++i) cout << ts.res[i] << ' ';
    }
    return;
}