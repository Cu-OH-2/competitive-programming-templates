const int N = 5005;
const int M = 200005;

struct Edge
{
    ll x, y, v;
    bool operator <(const Edge& e)
    {
        return v < e.v;
    }
};

Edge e[M];
int n, m;

ll kruskal()
{
    DSU dsu(n);
    ll ans = 0;
    sort(e + 1, e + 1 + m);
    for (int i = 1; i <= m; ++i)
    {
        if (dsu.find(e[i].x) != dsu.find(e[i].y))
        {
            ans += e[i].v;
            dsu.merge(e[i].x, e[i].y);
        }
    }
    return ans;
}