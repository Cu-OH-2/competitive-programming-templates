/*******************************************************************
* 时间复杂度：建立O(n)/询问O(logn)/修改O(logn)
* 说明：维护区间和，支持区间加减
*******************************************************************/
struct SegTree
{
    struct Node
    {
        int lef, rig;
        ll val, tag;
    };
    vector<Node> tree;

    SegTree() {}
    SegTree(int x) { tree.resize(x * 4 + 1); }

    // 由子节点及其标记更新父节点
    void update(int src)
    {
        ll lw = tree[src << 1].rig - tree[src << 1].lef + 1;
        ll rw = tree[src << 1 | 1].rig - tree[src << 1 | 1].lef + 1;
        ll lv = tree[src << 1].val + tree[src << 1].tag * lw;
        ll rv = tree[src << 1 | 1].val + tree[src << 1 | 1].tag * rw;
        tree[src].val = lv + rv;
        return;
    }

    // 下传标记并消耗
    void pushdown(int src)
    {
        if (tree[src].lef < tree[src].rig)
        {
            tree[src << 1].tag += tree[src].tag;
            tree[src << 1 | 1].tag += tree[src].tag;
        }
        ll wid = tree[src].rig - tree[src].lef + 1;
        tree[src].val += tree[src].tag * wid;
        tree[src].tag = 0;
        return;
    }

    /*
    void build(int src, int lef, int rig, ll arr[])
    {
        tree[src] = { lef, rig, arr[lef], 0 };
        if (lef == rig) return;
        int mid = lef + (rig - lef) / 2;
        build(src << 1, lef, mid, arr);
        build(src << 1 | 1, mid + 1, rig, arr);
        update(src);
        return;
    }
    */

    void build(int src, int lef, int rig)
    {
        tree[src] = { lef, rig, 0, 0 };
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
            tree[src].tag += val;
            return;
        }
        pushdown(src);
        if (lef <= tree[src << 1].rig) modify(src << 1, lef, rig, val);
        if (rig >= tree[src << 1 | 1].lef) modify(src << 1 | 1, lef, rig, val);
        update(src);
        return;
    }

    ll query(int src, int lef, int rig)
    {
        pushdown(src);
        if (lef <= tree[src].lef && tree[src].rig <= rig) return tree[src].val;
        ll res = 0;
        if (lef <= tree[src << 1].rig) res += query(src << 1, lef, rig);
        if (rig >= tree[src << 1 | 1].lef) res += query(src << 1 | 1, lef, rig);
        return res;
    }
};

/*******************************************************************
* 时间复杂度：建立O(n)/询问O(logn)/修改O(logn)
* 说明：维护区间和，支持单点修改
*******************************************************************/
struct SegTree
{
    struct Node
    {
        int lef, rig;
        int val;
    };
    vector<Node> tree;

    SegTree() {}
    SegTree(int x) { tree.resize(x * 4 + 1); }

    // 由子节点及其标记更新父节点
    void update(int src)
    {
        tree[src].val = tree[src << 1].val + tree[src << 1 | 1].val;
        return;
    }

    /*
    void build(int src, int lef, int rig, ll arr[])
    {
        tree[src] = { lef, rig, arr[i] };
        if (lef == rig) return;
        int mid = lef + (rig - lef) / 2;
        build(src << 1, lef, mid, arr);
        build(src << 1 | 1, mid + 1, rig, arr);
        update(src);
        return;
    }
    */

    void build(int src, int lef, int rig)
    {
        tree[src] = { lef, rig, 0 };
        if (lef == rig) return;
        int mid = lef + (rig - lef) / 2;
        build(src << 1, lef, mid);
        build(src << 1 | 1, mid + 1, rig);
        update(src);
        return;
    }

    void assign(int src, int pos, ll val)
    {
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

    ll query(int src, int lef, int rig)
    {
        if (lef <= tree[src].lef && tree[src].rig <= rig) return tree[src].val;
        ll res = 0;
        if (lef <= tree[src << 1].rig) res += query(src << 1, lef, rig);
        if (rig >= tree[src << 1 | 1].lef) res += query(src << 1 | 1, lef, rig);
        return res;
    }
};

/*******************************************************************
* 时间复杂度：建立O(n)/询问O(logn)/修改O(logn)
* 说明：维护最大值，支持区间加减/二分查询第一个大于等于x的数
*******************************************************************/
struct SegTree
{
    struct Node
    {
        int lef, rig;
        ll val, tag;
    };
    vector<Node> tree;

    SegTree() {}
    SegTree(int x) { tree.resize(x * 4 + 1); }

    // 由子节点及其标记更新父节点
    void update(int src)
    {
        ll lv = tree[src << 1].val + tree[src << 1].tag;
        ll rv = tree[src << 1 | 1].val + tree[src << 1 | 1].tag;
        tree[src].val = max(lv, rv);
        return;
    }

    // 下传标记并消耗
    void pushdown(int src)
    {
        if (tree[src].lef < tree[src].rig)
        {
            tree[src << 1].tag += tree[src].tag;
            tree[src << 1 | 1].tag += tree[src].tag;
        }
        tree[src].val += tree[src].tag;
        tree[src].tag = 0;
        return;
    }

    /*
    void build(int src, int lef, int rig, ll arr[])
    {
        tree[src] = { lef, rig, arr[lef], 0 };
        if (lef == rig) return;
        int mid = lef + (rig - lef) / 2;
        build(src << 1, lef, mid, arr);
        build(src << 1 | 1, mid + 1, rig, arr);
        update(src);
        return;
    }
    */

    void build(int src, int lef, int rig)
    {
        tree[src] = { lef, rig, 0, 0 };
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
            tree[src].tag += val;
            return;
        }
        pushdown(src);
        if (lef <= tree[src << 1].rig) modify(src << 1, lef, rig, val);
        if (rig >= tree[src << 1 | 1].lef) modify(src << 1 | 1, lef, rig, val);
        update(src);
        return;
    }

    ll query(int src, int lef, int rig)
    {
        pushdown(src);
        if (lef <= tree[src].lef && tree[src].rig <= rig) return tree[src].val;
        ll res = 0;
        if (lef <= tree[src << 1].rig) res = max(res, query(src << 1, lef, rig));
        if (rig >= tree[src << 1 | 1].lef) res = max(res, query(src << 1 | 1, lef, rig));
        return res;
    }

    int bis(int src, ll tar)
    {
        if(tree[src].val + tree[src].tag < tar) return tree[src].rig + 1;
        if(tree[src].lef == tree[src].rig) return tree[src].lef;
        if(tree[src << 1].val + tree[src << 1].tag >= tar) return bis(src << 1, tar);
        else return bis(src << 1 | 1, tar);
    }
};