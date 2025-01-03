const int N = 100005;

vector<int> node[N];

struct HLD
{
    vector<int> pa, dep, sz, hson;
    vector<int> top, dfn, rnk;
    int ord = 0;

    HLD(int x, int root)
    {
        pa.resize(x + 1);
        dep.resize(x + 1);
        sz.resize(x + 1);
        hson.resize(x + 1);
        top.resize(x + 1);
        dfn.resize(x + 1);
        rnk.resize(x + 1);
        build(root);
        decom(root);
    }

    void build(int x)
    {
        sz[x] = 1;
        int mxsz = 0;
        for (auto e : node[x])
        {
            if (e != pa[x])
            {
                pa[e] = x;
                dep[e] = dep[x] + 1;
                build(e);
                sz[x] += sz[e];
                if (sz[e] > mxsz)
                {
                    mxsz = sz[e];
                    hson[x] = e;
                }
            }
        }
        return;
    }

    void decom(int x)
    {
        top[x] = x;
        dfn[x] = ++ord;
        rnk[ord] = x;
        if (hson[pa[x]] == x) top[x] = top[pa[x]];
        if (hson[x]) decom(hson[x]);
        for (auto e : node[x]) 
        {
            if (e != pa[x] && e != hson[x]) decom(e);
        }
        return;
    }

    int lcm(int u, int v)
    {
        while (top[u] != top[v])
        {
            if (dep[u] < dep[v]) v = pa[top[v]];
            else u = pa[top[u]];
        }
        if (dep[u] < dep[v]) return u;
        else return v;
    }
};

struct LCD
{
    vector<int> pa, dep, h, hson;
    vector<int> top, dfn, rnk;
    int ord = 0;
 
    LCD(int x, int root)
    {
        pa.resize(x + 1);
        dep.resize(x + 1);
        h.resize(x + 1);
        hson.resize(x + 1);
        top.resize(x + 1);
        dfn.resize(x + 1);
        rnk.resize(x + 1);
        build(root);
        decom(root);
    }
 
    void build(int x)
    {
        h[x] = 1;
        int mxh = 0;
        for (auto e : node[x])
        {
            if (e == pa[x]) continue;
            pa[e] = x;
            dep[e] = dep[x] + 1;
            build(e);
            h[x] = max(h[x], h[e] + 1);
            if (h[e] > mxh)
            {
                mxh = h[e];
                hson[x] = e;
            }
        }
        return;
    }
 
    void decom(int x)
    {
        top[x] = x;
        dfn[x] = ++ord;
        rnk[ord] = x;
        if (hson[pa[x]] == x) top[x] = top[pa[x]];
        if (hson[x]) decom(hson[x]);
        for (auto e : node[x])
        {
            if (e == pa[x] || e == hson[x]) continue;
            decom(e);
        }
        return;
    }
};