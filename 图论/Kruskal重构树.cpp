/*******************************************************************
* 时间复杂度: 建立O(N)/查询O(logN)
* 说明: 
* 1.用于解决最小瓶颈路问题
* 2.考虑了初始图不连通的问题
* 3.注意n=1特殊情况（不用建树）
*******************************************************************/
const int N = 100005;

struct DSU
{
    vector<int> f;
    void init(int x)
    {
        f.resize(x + 1);
        for (int i = 1; i <= x; ++i) f[i] = i;
        return;
    }
    int find(int id) { return f[id] == id ? id : f[id] = find(f[id]); }
    void attach(int x, int y) //将fx连向fy，不按秩合并
    {
        int fx = find(x), fy = find(y);
        f[fx] = fy;
        return;
    }
};

struct LCA
{
    vector<int> d;
    vector<vector<int>> st;
    void dfs(int x, vector<vector<int>>& son)
    {
        for (auto e : son[x])
        {
            d[e] = d[x] + 1;
            st[e][0] = x;
            dfs(e, son);
        }
        return;
    }
    void build(int x)
    {
        int lg = int(log2(x));
        for (int i = 1; i <= lg; ++i)
        {
            for (int j = 1; j <= x; ++j)
            {
                if (d[j] >= (1 << i))
                {
                    st[j][i] = st[st[j][i - 1]][i - 1];
                }
            }
        }
        return;
    }
    void init(int x)
    {
        d.resize(x + 1);
        st.resize(x + 1, vector<int>(32));
        return;
    }
    int query(int x, int y)
    {
        if (d[x] < d[y]) swap(x, y);
        int dif = d[x] - d[y];
        for (int i = 0; dif >> i; ++i)
        {
            if (dif >> i & 1) x = st[x][i];
        }
        if (x == y) return x;
        for (int i = 31; i >= 0; --i)
        {
            while (st[x][i] != st[y][i])
            {
                x = st[x][i];
                y = st[y][i];
            }
        }
        return st[x][0];
    }
};

struct Edge
{
    ll x, y, v;
    bool operator<(const Edge& rhs) const { return v < rhs.v; }
} edg[N];

struct KrsRebTree
{
    int size; //当前结点数，最多为n*2-1
    vector<vector<int>> son; //子结点
    vector<ll> val; //点权
    LCA lca;
    DSU dsu;

    void build(int n, int m)
    {
        son.resize(n * 2);
        val.resize(n * 2);
        dsu.init(n * 2 - 1);
        size = n;
        sort(edg + 1, edg + 1 + m);
        for (int i = 1; i <= m && size < n * 2 - 1; ++i)
        {
            int fx = dsu.find(edg[i].x);
            int fy = dsu.find(edg[i].y);
            if (fx == fy) continue;
            size++;
            dsu.attach(fx, size);
            dsu.attach(fy, size);
            son[size].push_back(fx);
            son[size].push_back(fy);
            val[size] = edg[i].v;
        }
        lca.init(size);
        for (int i = n + 1; i <= size; ++i)
        {
            if (dsu.find(i) == i) lca.dfs(i, son); //对所有树的根dfs
        }
        lca.build(size);
        return;
    }
    ll query(int x, int y)
    {
        if (dsu.find(x) == dsu.find(y)) return val[lca.query(x, y)];
        else return -1;
    }
};