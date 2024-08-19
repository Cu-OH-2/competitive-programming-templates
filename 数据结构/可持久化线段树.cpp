struct PerSegTree // 维护区间和，支持区间加减
{
    struct Node
    {
        int ls, rs;
        ll val, tag;
        Node(): ls(0), rs(0), val(0), tag(0) {}
    };
    vector<Node> tree;
    vector<int> root;
    int size;
    ll L, R;

    int _build(ll l, ll r, ll a[])
    {
        int now = size++;
        if (l == r) tree[now].val = a[l];
        else
        {
            ll m = l + (r - l) / 2;
            tree[now].ls = _build(l, m, a);
            tree[now].rs = _build(m + 1, r, a);
            tree[now].val = tree[tree[now].ls].val + tree[tree[now].rs].val;
        }
        return now;
    }
    void init(ll l, ll r, int cnt, ll a[]) // 建初始树
    {
        size = 0;
        L = l, R = r;
        tree.resize(cnt * 32 + 5);
        root.push_back(_build(L, R, a));
        return;
    }
    void init(ll l, ll r, int cnt) // 建一个空根
    {
        size = 1;
        L = l, R = r;
        tree.resize(cnt * 32 + 5);
        root.push_back(0);
        return;
    }
    void modify(int ver, ll lef, ll rig, ll val) { root.push_back(_modify(root[ver], L, R, lef, rig, val)); }
    int _modify(int src, ll l, ll r, ll lef, ll rig, ll val)
    {
        int now = size++;
        tree[now] = tree[src];
        if (lef <= l && r <= rig) tree[now].tag += val;
        else if (l <= rig && r >= lef)
        {
            tree[now].val += val * (min(rig, r) - max(lef, l) + 1);
            ll m = l + (r - l) / 2;
            if (lef <= m) tree[now].ls = _modify(tree[now].ls, l, m, lef, rig, val);
            if (rig > m) tree[now].rs = _modify(tree[now].rs, m + 1, r, lef, rig, val);
        }
        return now;
    }
    ll query(int ver, ll lef, ll rig) { return _query(root[ver], L, R, lef, rig, 0); }
    ll _query(int src, ll l, ll r, ll lef, ll rig, ll tag)
    {
        tag += tree[src].tag;
        if (lef <= l && r <= rig) return tree[src].val + (r - l + 1) * tag;
        else if (l <= rig && r >= lef)
        {
            int m = l + (r - l) / 2;
            ll res = 0;
            if (lef <= m) res += _query(tree[src].ls, l, m, lef, rig, tag);
            if (rig > m) res += _query(tree[src].rs, m + 1, r, lef, rig, tag);
            return res;
        }
        else return 0;
    }
    ll kth(ll lef, ll rig, int k) { return _kth(root[lef - 1], root[rig], L, R, k); }
    ll _kth(int osrc, int nsrc, ll l, ll r, int k)
    {
        if (l == r) return l;
        int nsum = tree[tree[nsrc].ls].val + tree[tree[nsrc].ls].tag;
        int osum = tree[tree[osrc].ls].val + tree[tree[osrc].ls].tag;
        int dif = nsum - osum;
        int m = l + (r - l) / 2;
        if (dif >= k) return _kth(tree[osrc].ls, tree[nsrc].ls, l, m, k);
        else return _kth(tree[osrc].rs, tree[nsrc].rs, m + 1, r, k - dif);
    }
};