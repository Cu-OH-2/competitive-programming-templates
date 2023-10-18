/*******************************************************************
* 时间复杂度：建立O(n)/询问O(logn)/修改O(logn)
* 说明：
* 1.维护区间性质，要求性质能由子区间性质得到。
* 2.区间修改，区间查询。若仅单点修改则不需要标记。
* 3.使线段树维护不同性质只需要改变上方函数和默认值。
* 4.modify也要push。
*******************************************************************/
struct SegTree
{
    struct Node
    {
        int lef, rig;
        ll val, tag;
    };
    vector<Node> tree;

    const ll VDEF = 0;
    const ll TDEF = 0;

    inline void update(int src) //由子节点及其标记更新父节点
    {
        ll lw = tree[src << 1].rig - tree[src << 1].lef + 1;
        ll rw = tree[src << 1 | 1].rig - tree[src << 1 | 1].lef + 1;
        ll lv = tree[src << 1].val + tree[src << 1].tag * lw;
        ll rv = tree[src << 1 | 1].val + tree[src << 1 | 1].tag * rw;
        tree[src].val = merge(lv, rv);
        return;
    }
    inline void push(int src) //下传标记并消耗
    {
        if (tree[src].lef < tree[src].rig)
        {
            tree[src << 1].tag += tree[src].tag;
            tree[src << 1 | 1].tag += tree[src].tag;
        }
        ll wid = tree[src].rig - tree[src].lef + 1;
        tree[src].val += tree[src].tag * wid;
        tree[src].tag = TDEF;
        return;
    }
    inline void mark(int src, ll val) //更新标记
    {
        tree[src].tag += val;
        return;
    }
    inline ll merge(ll x, ll y) //合并两个查询结果
    {
        return x + y;
    }

    SegTree() {}
    SegTree(int x) { init(x); }
    void init(int x) { tree.resize(x * 4 + 1); }

    void build(int src, int lef, int rig, ll arr[])
    {
        tree[src] = { lef, rig, VDEF, TDEF };
        if (lef == rig) tree[src].val = arr[lef];
        else
        {
            int mid = lef + (rig - lef) / 2;
            build(src << 1, lef, mid, arr);
            build(src << 1 | 1, mid + 1, rig, arr);
            update(src);
        }
        return;
    }
    void build(int src, int lef, int rig)
    {
        tree[src] = { lef, rig, VDEF, TDEF };
        if (lef == rig) return;
        int mid = lef + (rig - lef) / 2;
        build(src << 1, lef, mid);
        build(src << 1 | 1, mid + 1, rig);
        update(src);
        return;
    }
    void assign(int src, int pos, ll val)
    {
        push(src);
        if (tree[src].lef == tree[src].rig)
        {
            tree[src].val = val;
            return;
        }
        if (pos <= tree[src << 1].rig) assign(src << 1, pos, val);
        else assign(src << 1 | 1, pos, val);
        update(src);
        return;
    }
    void modify(int src, int lef, int rig, ll val)
    {
        if (lef <= tree[src].lef && tree[src].rig <= rig)
        {
            mark(src, val);
            return;
        }
        push(src);
        if (lef <= tree[src << 1].rig) modify(src << 1, lef, rig, val);
        if (rig >= tree[src << 1 | 1].lef) modify(src << 1 | 1, lef, rig, val);
        update(src);
        return;
    }
    ll query(int src, int lef, int rig)
    {
        push(src);
        if (lef <= tree[src].lef && tree[src].rig <= rig) return tree[src].val;
        ll res = VDEF;
        if (lef <= tree[src << 1].rig) res = merge(res, query(src << 1, lef, rig));
        if (rig >= tree[src << 1 | 1].lef) res = merge(res, query(src << 1 | 1, lef, rig));
        return res;
    }
};