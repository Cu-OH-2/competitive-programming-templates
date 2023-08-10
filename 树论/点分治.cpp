/*******************************************************************
* 时间复杂度：处理结点次数O(nlogn)
* 说明：用于树上路径计数问题：以重心为根分治子树，再计算经过重心的路径
*******************************************************************/
const int N = 100005;
const int D[3][2] = { -1, 0, 1, -1, 0, 1 };

int n, sz[N], maxd[N];
string s;
vector<int> node[N];
bool vis[N];
multiset<pair<int, int>> st;

void getRoot(int x, int fa, int sum, int& root)
{
    sz[x] = 1, maxd[x] = 0;
    for (auto e : node[x])
    {
        if (vis[e] || e == fa) continue;
        getRoot(e, x, sum, root);
        sz[x] += sz[e];
        maxd[x] = max(maxd[x], sz[e]);
    }
    maxd[x] = max(maxd[x], sum - sz[x]);
    if (maxd[x] < maxd[root]) root = x;
    return;
}

void dfs(int x, int fa, pair<int, int> p)
{
    p.first += D[s[x] - 'a'][0];
    p.second += D[s[x] - 'a'][1];
    st.insert(p);
    for (auto e : node[x])
    {
        if (vis[e] || e == fa) continue;
        dfs(e, x, p);
    }
    return;
}

ll work(int x)
{
    ll res = 0;
    multiset<pair<int, int>> ns;
    for (auto e : node[x])
    {
        if (vis[e]) continue;
        dfs(e, x, make_pair(0, 0));
        for (auto p : st)
        {
            pair<int, int> inv;
            inv.first = -(p.first + D[s[x] - 'a'][0]);
            inv.second = -(p.second + D[s[x] - 'a'][1]);
            if (inv == make_pair(0, 0)) res++;
            res += ns.count(inv);
        }
        for (auto p : st) ns.insert(p);
        st.clear();
    }
    return res;
}

ll divide(int x)
{
    ll res = 0;
    vis[x] = 1;
    res += work(x);
    for (auto e : node[x])
    {
        if (vis[e]) continue;
        int root = 0;
        getRoot(e, x, sz[e], root);
        res += divide(root);
    }
    return res;
}

void solve()
{
    cin >> n >> s;
    s = ' ' + s;
    for (int i = 1; i <= n - 1; ++i)
    {
        int u, v;
        cin >> u >> v;
        node[u].push_back(v);
        node[v].push_back(u);
    }
    maxd[0] = n + 1;
    int root = 0;
    getRoot(1, 0, n, root);
    cout << divide(root) << '\n';
    return;
}