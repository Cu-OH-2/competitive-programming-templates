/*******************************************************************
* 时间复杂度：O(N)
* 说明：
* 1.距离任一点最远的点一定是直径的一端
* 2.任一点距所有叶的最远距离对应的叶一定是直径端点
*******************************************************************/
const int N = 200005;

struct Edge { int to; ll v; };
vector<Edge> node[N];

pair<int, ll> farthest(int id, ll d, int pa)
{
    pair<int, ll> ret = { id,d };
    for (auto e : node[id])
    {
        pair<int, ll> res;
        if (e.to != pa) res = farthest(e.to, d + e.v, id);
        if (res.second > ret.second) ret = res;
    }
    return ret;
}

int n, m;

void solve()
{
    cin >> n >> m;
    int u, v;
    ll w;
    for (int i = 1; i <= m; ++i)
    {
        cin >> u >> v >> w;
        node[u].push_back({ v,w });
        node[v].push_back({ u,w });
    }
    int s = farthest(1, 0, -1).first;
    auto res = farthest(s, 0, -1);
    int t = res.first;
    ll d = res.second;
    return;
}