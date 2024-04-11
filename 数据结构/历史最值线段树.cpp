/*******************************************************************
* 时间复杂度：询问O(logn)/修改O(logn)
* 说明：
* 1. 维护区间历史最值，支持区间加减
* 2. 上方标记一定新于下方标记，因此下传可以整体施加
*******************************************************************/
struct SegTree
{
    struct Node
    {
        int lef, rig;
        ll mval; //历史最值
        ll tag, mtag; //当前修改标签、tag生命周期内最值
    };
    vector<Node> tree;
    inline ll merge(ll x, ll y) { return min(x, y); } //最大还是最小
    inline void affect(ll& x, ll y) { x = merge(x, y); } //取最值
    inline void update(int src) //由子节点及其标记更新父节点
    {
        ll lv = tree[src << 1].mval + merge(tree[src << 1].mtag, 0);
        ll rv = tree[src << 1 | 1].mval + merge(tree[src << 1 | 1].mtag, 0);
        tree[src].mval = merge(lv, rv);
        return;
    }
    inline void push(int src) //下传标记并消耗
    {
        if (tree[src].lef < tree[src].rig)
        {
            affect(tree[src << 1].mtag, tree[src << 1].tag + tree[src].mtag);
            affect(tree[src << 1 | 1].mtag, tree[src << 1 | 1].tag + tree[src].mtag);
            tree[src << 1].tag += tree[src].tag;
            tree[src << 1 | 1].tag += tree[src].tag;
        }
        tree[src].mval += merge(tree[src].mtag, 0);
        tree[src].mtag = tree[src].tag = 0;
        return;
    }
    inline void mark(int src, ll val) //更新标记
    {
        tree[src].tag += val;
        affect(tree[src].mtag, tree[src].tag);
        return;
    }

    SegTree() {}
    SegTree(int x) { init(x); }
    void init(int x) { tree.resize(x * 4 + 1); }

    void build(int src, int lef, int rig)
    {
        tree[src] = { lef, rig, 0, 0, 0 };
        if (lef == rig) return;
        int mid = lef + (rig - lef) / 2;
        build(src << 1, lef, mid);
        build(src << 1 | 1, mid + 1, rig);
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
        if (lef <= tree[src].lef && tree[src].rig <= rig) return tree[src].mval;
        ll res = 0;
        if (lef <= tree[src << 1].rig) res = merge(res, query(src << 1, lef, rig));
        if (rig >= tree[src << 1 | 1].lef) res = merge(res, query(src << 1 | 1, lef, rig));
        return res;
    }
};