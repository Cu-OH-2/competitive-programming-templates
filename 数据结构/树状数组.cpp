struct Fenwick // 普通树状数组
{
    int sz;
    vector<ll> tree;

    int lowbit(int x) { return x & -x; }

    Fenwick() {}
    Fenwick(int x) { init(x); }
    void init(int x)
    {
        sz = x;
        tree.resize(sz + 1);
    }
    void add(int dst, ll v)
    {
        while (dst <= sz)
        {
            tree[dst] += v;
            dst += lowbit(dst);
        }
        return;
    }
    ll pre(int dst)
    {
        ll res = 0;
        while (dst)
        {
            res += tree[dst];
            dst -= lowbit(dst);
        }
        return res;
    }
    ll rsum(int lef, int rig) { return pre(rig) - pre(lef - 1); }
    void build(ll arr[])
    {
        for (int i = 1; i <= sz; ++i)
        {
            tree[i] += arr[i];
            int j = i + lowbit(i);
            if (j <= sz) tree[j] += tree[i];
        }
        return;
    }
};


struct Fenwick // 时间戳优化，可O(1)清空
{
    int sz;
    vector<ll> tree;
    vector<int> tag;
    int now;

    int lowbit(int x) { return x & -x; }

    Fenwick(int x) 
    { 
        sz = x;
        tree.resize(sz + 1);
        tag.resize(sz + 1);
        now = 0;
    }
    void clear()
    {
        now++;
        return;
    }
    void add(int dst, ll v)
    {
        while (dst <= sz)
        {
            if (tag[dst] != now) tree[dst] = 0;
            tree[dst] += v;
            tag[dst] = now;
            dst += lowbit(dst);
        }
        return;
    }
    ll pre(int dst)
    {
        ll res = 0;
        while (dst)
        {
            if (tag[dst] == now) res += tree[dst];
            dst -= lowbit(dst);
        }
        return res;
    }
    ll rsum(int lef, int rig) { return pre(rig) - pre(lef - 1); }
    void build(ll arr[])
    {
        for (int i = 1; i <= sz; ++i)
        {
            tree[i] += arr[i];
            int j = i + lowbit(i);
            if (j <= sz) tree[j] += tree[i];
        }
        return;
    }
};