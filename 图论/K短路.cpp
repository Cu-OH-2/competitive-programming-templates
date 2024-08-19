const int N = 1005;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;

struct E
{
    ll to, v;
};

struct V
{
    ll id, d;
    bool operator<(const V& v) const { return d > v.d; }
};

int n, m, k;
vector<E> node[N];

struct Dijkstra
{
    int sz;
    vector<ll> d;
    vector<int> vis;
    priority_queue<V> pq;
    vector<vector<E>> rev;

    void rebuild()
    {
        for (int i = 1; i <= sz; ++i)
        {
            for (auto e : node[i])
            {
                rev[e.to].push_back({ i,e.v });
            }
        }
        return;
    }
    Dijkstra(int x, int s)
    {
        sz = x;
        d.resize(sz + 1, INFLL);
        vis.resize(sz + 1);
        rev.resize(sz + 1);
        rebuild();
        d[1] = 0;
        pq.push({ 1,0 });
        while (pq.size())
        {
            auto now = pq.top();
            pq.pop();
            if (vis[now.id]) continue;
            vis[now.id] = 1;
            for (auto e : rev[now.id])
            {
                if (vis[e.to] == 0 && d[e.to] > d[now.id] + e.v)
                {
                    d[e.to] = d[now.id] + e.v;
                    pq.push({ e.to, d[e.to] });
                }
            }
        }
    }
};

void solve()
{
    cin >> n >> m >> k;
    int u, v, w;
    for (int i = 1; i <= m; ++i)
    {
        cin >> u >> v >> w;
        node[u].push_back({ v,w });
    }
    Dijkstra dj(n, n);
    priority_queue<V> pq;
    vector<int> vis(n + 1);
    pq.push({ n,dj.d[n] });
    vector<ll> ans(k, -1);
    while (pq.size())
    {
        auto now = pq.top();
        pq.pop();
        if (now.id == 1 && vis[now.id] < k) ans[vis[now.id]] = now.d;
        vis[now.id]++;
        for (auto e : node[now.id])
        {
            if (vis[e.to] >= k) continue;
            pq.push({ e.to,now.d - dj.d[now.id] + e.v + dj.d[e.to] });
        }
    }
    for (int i = 0; i < k; ++i) cout << ans[i] << '\n';
    return;
}