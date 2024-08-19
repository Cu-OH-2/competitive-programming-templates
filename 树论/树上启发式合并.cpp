const int N = 100005;

vector<int> node[N];

int n;
ll a[N];

struct DsuOnTree
{
    struct State
    {
        vector<int> cnt;
        map<int, ll> mp;
        State() { init(); }
        void init() { cnt.resize(1e5 + 1); }
        void add(ll val)
        {
            if (cnt[val]) mp[cnt[val]] -= val;
            if (mp[cnt[val]] == 0) mp.erase(cnt[val]);
            cnt[val]++;
            mp[cnt[val]] += val;
            return;
        }
        void del(ll val)
        {
            mp[cnt[val]] -= val;
            if (mp[cnt[val]] == 0) mp.erase(cnt[val]);
            cnt[val]--;
            if (cnt[val]) mp[cnt[val]] += val;
            return;
        }
        ll ans() { return mp.rbegin()->second; }
    } state;
    vector<int> big; // 每个结点的重子
    vector<int> sz; // 每个子树的大小
    vector<ll> ans; // 每个子树的答案
    const int root = 1;

    DsuOnTree()
    {
        big.resize(n + 1);
        sz.resize(n + 1);
        ans.resize(n + 1);
    }
    void dfs0(int x, int p)
    {
        sz[x] = 1;
        for (auto e : node[x])
        {
            if (e == p) continue;
            dfs0(e, x);
            sz[x] += sz[e];
            if (sz[big[x]] < sz[e]) big[x] = e;
        }
        return;
    }
    void del(int x, int p) // 删除子树贡献
    {
        state.del(a[x]);
        for (auto e : node[x])
        {
            if (e == p) continue;
            del(e, x);
        }
        return;
    }
    void add(int x, int p) // 计算子树贡献
    {
        state.add(a[x]);
        for (auto e : node[x])
        {
            if (e == p) continue;
            add(e, x);
        }
        return;
    }
    void dfs(int x, int p, bool keep)
    {
        for (auto e : node[x]) // 计算轻子子树答案
        {
            if (e == big[x] || e == p) continue;
            dfs(e, x, 0);
        }
        if (big[x]) dfs(big[x], x, 1); // 计算重子子树答案和贡献
        for (auto e : node[x]) // 计算轻子子树贡献
        {
            if (e == big[x] || e == p) continue;
            add(e, x);
        }
        state.add(a[x]); // 计算自己贡献
        ans[x] = state.ans(); // 计算答案
        if (keep == 0) del(x, p); // 删除子树贡献
        return;
    }
    void work()
    {
        dfs0(root, 0);
        dfs(root, 0, 0);
        return;
    }
};

void solve()
{
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    int u, v;
    for (int i = 1; i <= n - 1; ++i)
    {
        cin >> u >> v;
        node[u].push_back(v);
        node[v].push_back(u);
    }
    DsuOnTree dot;
    dot.work();
    for (int i = 1; i <= n; ++i) cout << dot.ans[i] << ' ';
    cout << endl;
    return;
}