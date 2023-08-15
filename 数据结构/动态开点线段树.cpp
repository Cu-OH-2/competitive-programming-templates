/*******************************************************************
* 时间复杂度：询问O(logn)/修改O(logn)
* 说明：注意空间大小
*******************************************************************/
struct SegTree
{
    struct Node
    {
        int ls = 0, rs = 0;
        ll val = 0, tag = 0;
    };
    vector<Node> tree;
    int ord;
    SegTree(int x)
    {
        tree.resize(x * 64 + 1);
        ord = 1;
    }
    void push(int src, int lef, int rig)
    {
        if (lef < rig)
        {
            if (!tree[src].ls) tree[src].ls = ++ord;
            if (!tree[src].rs) tree[src].rs = ++ord;
            tree[tree[src].ls].tag += tree[src].tag;
            tree[tree[src].rs].tag += tree[src].tag;
        }
        tree[src].val += tree[src].tag * (rig - lef + 1);
        tree[src].tag = 0;
        return;
    }
    void modify(int src, int lef, int rig, int l, int r, ll val)
    {
        if (lef >= l && rig <= r)
        {
            tree[src].tag += val;
            return;
        }
        int mid = lef + (rig - lef) / 2;
        if (l <= mid)
        {
            if (!tree[src].ls) tree[src].ls = ++ord;
            modify(tree[src].ls, lef, mid, l, r, val);
        }
        if (r >= mid + 1)
        {
            if (!tree[src].rs) tree[src].rs = ++ord;
            modify(tree[src].rs, mid + 1, rig, l, r, val);
        }
        tree[src].val += (min(rig, r) - max(lef, l) + 1) * val;
        return;
    }
    ll query(int src, int lef, int rig, int l, int r)
    {
        push(src, lef, rig);
        if (lef >= l && rig <= r) return tree[src].val;
        ll res = 0;
        int mid = lef + (rig - lef) / 2;
        if (l <= mid)
        {
            if (!tree[src].ls) tree[src].ls = ++ord;
            res += query(tree[src].ls, lef, mid, l, r);
        }
        if (r >= mid + 1)
        {
            if (!tree[src].rs) tree[src].rs = ++ord;
            res += query(tree[src].rs, mid + 1, rig, l, r);
        }
        return res;
    }
};