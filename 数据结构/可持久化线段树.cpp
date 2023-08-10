/*******************************************************************
* 时间复杂度：所有操作O(log(seglen))
* 说明：
* 1.建空根：可以不靠离散化维护大区间，但要谨慎考虑空间复杂度。
* 2.主席树维护区间值域上性质：用可持久化权值线段树维护值域，将序列元素逐
*   个插入，由前缀和性质，区间值域上性质蕴含在新树和旧树的差之中。
* 3.标记永久化：路过结点时标记不下放，也不通过子结点更新，而是直接改变其
*   值；向下搜索时记录累积标记值并在最后作用（因此assign()在维护最值时
*   无效）。
* 4.区间第k大也可以整体二分/划分树。
* 5.若维护区间超过int，记得把32换成64。
*******************************************************************/
struct PerSegTree
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
    void init(ll l, ll r, int cnt, ll a[]) //建初始树
    {
        size = 0;
        L = l, R = r;
        tree.resize(cnt * 32 + 5);
        root.push_back(_build(L, R, a));
        return;
    }
    void init(ll l, ll r, int cnt) //建一个空根
    {
        size = 1;
        L = l, R = r;
        tree.resize(cnt * 32 + 5);
        root.push_back(0);
        return;
    }
    void assign(int ver, ll pos, ll val) { root.push_back(_assign(root[ver], L, R, pos, val, 0)); }
    int _assign(int src, ll l, ll r, ll pos, ll val, ll tag)
    {
        int now = size++;
        tree[now] = tree[src];
        tag += tree[now].tag;
        if (l == r) tree[now].val = val - tag;
        else
        {
            ll m = l + (r - l) / 2;
            if (pos <= m) tree[now].ls = _assign(tree[now].ls, l, m, pos, val, tag);
            else tree[now].rs = _assign(tree[now].rs, m + 1, r, pos, val, tag);
        }
        return now;
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