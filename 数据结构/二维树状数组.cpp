struct Fenwick2
{
    int sz;
    vector<vector<ll>> tree;

    inline int lowbit(int x) { return x & -x; }

    Fenwick2(int x)
    { 
        sz = x;
        tree.resize(sz + 1, vector<ll>(sz + 1));
    }

    void add(int x, int y, ll val)
    {
        for (int i = x; i <= sz; i += lowbit(i))
        {
            for (int j = y; j <= sz; j += lowbit(j))
            {
                tree[i][j] += val;
            }
        }
        return;
    }

    ll pre(int x, int y)
    {
        ll res = 0;
        for (int i = x; i >= 1; i -= lowbit(i))
        {
            for (int j = y; j >= 1; j -= lowbit(j))
            {
                res += tree[i][j];
            }
        }
        return res;
    }

    ll sum(int x1, int y1, int x2, int y2)
    {
        return pre(x2, y2) - pre(x1 - 1, y2) - pre(x2, y1 - 1) + pre(x1 - 1, y1 - 1);
    }
};