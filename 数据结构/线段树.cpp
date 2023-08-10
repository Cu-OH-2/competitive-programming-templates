/*******************************************************************
* 时间复杂度：建立O(n)/询问O(logn)/修改O(logn)
* 说明：
* 1.维护区间性质，要求性质能由子区间性质得到。
* 2.区间修改，区间查询。若仅单点修改则不需要标记。
* 3.使线段树维护不同性质只需要改变上方5个函数和两个默认值。
* 4.动态开点线段树：在结点中记录ls和rs，而不记录lef和rig。修改时遇到不
*   存在的结点要创建，查询时遇到不存在的结点要跳过。
*******************************************************************/
struct SegTree
{
    struct Node
    {
        int lef, rig;
        ll v, tag;
    };
    vector<Node> tree;

    inline int ls(int src) { return src * 2; }
    inline int rs(int src) { return src * 2 + 1; }
    inline Node& ln(int src) { return tree[ls(src)]; }
    inline Node& rn(int src) { return tree[rs(src)]; }
    
    const ll VDEF = 0;
    const ll TDEF = 0;

    inline void update(int src) //由子节点及其标记更新父节点
    {
        ll lw = tree[ls(src)].rig - tree[ls(src)].lef + 1;
        ll rw = tree[rs(src)].rig - tree[rs(src)].lef + 1;
        ll lv = ln(src).v + ln(src).tag * lw;
        ll rv = rn(src).v + rn(src).tag * rw;
        tree[src].v = merge(lv, rv);
        return;
    }
    inline void act(int src) //消耗标记使其发挥作用
    {
        ll wid = tree[src].rig - tree[src].lef + 1;
        tree[src].v += tree[src].tag * wid;
        tree[src].tag = TDEF;
        return;
    }
    inline void push(int src) //将标记传给子节点
    {
        if (tree[src].lef < tree[src].rig)
        {
            ln(src).tag += tree[src].tag;
            rn(src).tag += tree[src].tag;
        }
        act(src);
        return;
    }
    inline void mark(int src, ll val) //更新标记
    {
        tree[src].tag += val;
        return;
    }
    inline ll merge(ll x, ll y) //合并两个子节点查询结果
    {
        return x + y;
    }

    SegTree() {}
    SegTree(int x) { init(x); }
    void init(int x) { tree.resize(x * 4 + 1); }

    void build(int src, int lef, int rig, ll arr[])
    {
        tree[src] = { lef,rig,VDEF,TDEF };
        if (lef == rig) tree[src].v = arr[lef];
        else
        {
            int mid = lef + (rig - lef) / 2;
            build(ls(src), lef, mid, arr);
            build(rs(src), mid + 1, rig, arr);
            update(src);
        }
        return;
    }
    void build(int src, int lef, int rig)
    {
        tree[src] = { lef,rig,VDEF,TDEF };
        if (lef == rig) return;
        int mid = lef + (rig - lef) / 2;
        build(ls(src), lef, mid);
        build(rs(src), mid + 1, rig);
        update(src);
        return;
    }
    void assign(int src, int p, ll val)
    {
        if (tree[src].lef <= p && tree[src].rig >= p)
        {
            push(src);
            if (tree[src].lef == tree[src].rig) tree[src].v = val;
            else
            {
                assign(ls(src), p, val);
                assign(rs(src), p, val);
                update(src);
            }
        }
        return;
    }
    void modify(int src, int lef, int rig, ll val)
    {
        if (lef <= tree[src].lef && tree[src].rig <= rig) mark(src, val);
        else if (tree[src].lef <= rig && tree[src].rig >= lef)
        {
            push(src);
            modify(ls(src), lef, rig, val);
            modify(rs(src), lef, rig, val);
            update(src);
        }
        return;
    }
    ll query(int src, int lef, int rig)
    {
        push(src);
        if (lef <= tree[src].lef && tree[src].rig <= rig) return tree[src].v;
        else if (tree[src].lef <= rig && tree[src].rig >= lef)
        {
            ll lr = query(ls(src), lef, rig);
            ll rr = query(rs(src), lef, rig);
            return merge(lr, rr);
        }
        else return VDEF;
    }
};