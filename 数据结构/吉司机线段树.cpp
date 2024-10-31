const ll INF = 1e12;

struct SegTree // 维护区间和/最大值/次大值/最大值个数，支持区间取最小值
{
    struct Node
    {
        int lef, rig;
        ll fst, snd, cnt, sum, tag;
    };
    vector<Node> tree;
    SegTree(int x) { tree.resize(x * 4 + 1); }

    void update(int src)
    {
        tree[src].sum = tree[src << 1].sum + tree[src << 1 | 1].sum;
        if (tree[src << 1].fst == tree[src << 1 | 1].fst)
        {
            tree[src].fst = tree[src << 1].fst;
            tree[src].snd = max(tree[src << 1].snd, tree[src << 1 | 1].snd);
            tree[src].cnt = tree[src << 1].cnt + tree[src << 1 | 1].cnt;
        }
        else if (tree[src << 1].fst > tree[src << 1 | 1].fst)
        {
            tree[src].fst = tree[src << 1].fst;
            tree[src].snd = max(tree[src << 1].snd, tree[src << 1 | 1].fst);
            tree[src].cnt = tree[src << 1].cnt;
        }
        else
        {
            tree[src].fst = tree[src << 1 | 1].fst;
            tree[src].snd = max(tree[src << 1].fst, tree[src << 1 | 1].snd);
            tree[src].cnt = tree[src << 1 | 1].cnt;
        }
        return;
    }

    void work(int src, ll val)
    {
        if (val >= tree[src].fst) return;
        assert(val > tree[src].snd);
        tree[src].sum += (val - tree[src].fst) * tree[src].cnt;
        tree[src].fst = tree[src].tag = val;
        return;
    }

    void pushdown(int src)
    {
        if (tree[src].lef < tree[src].rig)
        {
            work(src << 1, tree[src].tag);
            work(src << 1 | 1, tree[src].tag);
        }
        tree[src].tag = INF;
        return;
    }

    void build(int src, int lef, int rig)
    {
        tree[src] = { lef, rig, INF, -INF, rig - lef + 1, (rig - lef + 1) * INF, INF };
        if (lef == rig) return;
        int mid = lef + (rig - lef) / 2;
        build(src << 1, lef, mid);
        build(src << 1 | 1, mid + 1, rig);
        update(src);
        return;
    }

    void modify(int src, int lef, int rig, ll val)
    {
        if (val >= tree[src].fst) return;
        if (lef <= tree[src].lef && rig >= tree[src].rig && val > tree[src].snd)
        {
            work(src, val);
            return;
        }
        pushdown(src);
        if (lef <= tree[src << 1].rig) modify(src << 1, lef, rig, val);
        if (rig >= tree[src << 1 | 1].lef) modify(src << 1 | 1, lef, rig, val);
        update(src);
        return;
    }

    ll query_sum(int src, int lef, int rig)
    {
        pushdown(src);
        if (lef <= tree[src].lef && rig >= tree[src].rig) return tree[src].sum;
        ll res = 0;
        if (lef <= tree[src << 1].rig) res += query_sum(src << 1, lef, rig);
        if (rig >= tree[src << 1 | 1].lef) res += query_sum(src << 1 | 1, lef, rig);
        return res;
    }
    ll query_max(int src, int lef, int rig)
    {
        pushdown(src);
        if (lef <= tree[src].lef && rig >= tree[src].rig) return tree[src].fst;
        ll res = -INF;
        if (lef <= tree[src << 1].rig) res = max(res, query_max(src << 1, lef, rig));
        if (rig >= tree[src << 1 | 1].lef) res = max(res, query_max(src << 1 | 1, lef, rig));
        return res;
    }
};

struct SegTree // 维护区间和/最小值/次小值/最小值个数，支持区间取最大值
{
    struct Node
    {
        int lef, rig;
        ll fst, snd, cnt, sum, tag;
    };
    vector<Node> tree;
    SegTree(int x) { tree.resize(x * 4 + 1); }

    void update(int src)
    {
        tree[src].sum = tree[src << 1].sum + tree[src << 1 | 1].sum;
        if (tree[src << 1].fst == tree[src << 1 | 1].fst)
        {
            tree[src].fst = tree[src << 1].fst;
            tree[src].snd = min(tree[src << 1].snd, tree[src << 1 | 1].snd);
            tree[src].cnt = tree[src << 1].cnt + tree[src << 1 | 1].cnt;
        }
        else if (tree[src << 1].fst < tree[src << 1 | 1].fst)
        {
            tree[src].fst = tree[src << 1].fst;
            tree[src].snd = min(tree[src << 1].snd, tree[src << 1 | 1].fst);
            tree[src].cnt = tree[src << 1].cnt;
        }
        else
        {
            tree[src].fst = tree[src << 1 | 1].fst;
            tree[src].snd = min(tree[src << 1].fst, tree[src << 1 | 1].snd);
            tree[src].cnt = tree[src << 1 | 1].cnt;
        }
        return;
    }

    void work(int src, ll val)
    {
        if (val <= tree[src].fst) return;
        assert(val < tree[src].snd);
        tree[src].sum += (val - tree[src].fst) * tree[src].cnt;
        tree[src].fst = tree[src].tag = val;
        return;
    }

    void pushdown(int src)
    {
        if (tree[src].lef < tree[src].rig)
        {
            work(src << 1, tree[src].tag);
            work(src << 1 | 1, tree[src].tag);
        }
        tree[src].tag = 0;
        return;
    }

    void build(int src, int lef, int rig)
    {
        tree[src] = { lef, rig, 0, INF, rig - lef + 1, 0, 0 };
        if (lef == rig) return;
        int mid = lef + (rig - lef) / 2;
        build(src << 1, lef, mid);
        build(src << 1 | 1, mid + 1, rig);
        update(src);
        return;
    }

    void modify(int src, int lef, int rig, ll val)
    {
        if (val <= tree[src].fst) return;
        if (lef <= tree[src].lef && rig >= tree[src].rig && val < tree[src].snd)
        {
            work(src, val);
            return;
        }
        pushdown(src);
        if (lef <= tree[src << 1].rig) modify(src << 1, lef, rig, val);
        if (rig >= tree[src << 1 | 1].lef) modify(src << 1 | 1, lef, rig, val);
        update(src);
        return;
    }

    ll query_sum(int src, int lef, int rig)
    {
        pushdown(src);
        if (lef <= tree[src].lef && rig >= tree[src].rig) return tree[src].sum;
        ll res = 0;
        if (lef <= tree[src << 1].rig) res += query_sum(src << 1, lef, rig);
        if (rig >= tree[src << 1 | 1].lef) res += query_sum(src << 1 | 1, lef, rig);
        return res;
    }
    ll query_min(int src, int lef, int rig)
    {
        pushdown(src);
        if (lef <= tree[src].lef && rig >= tree[src].rig) return tree[src].fst;
        ll res = INF;
        if (lef <= tree[src << 1].rig) res = min(res, query_min(src << 1, lef, rig));
        if (rig >= tree[src << 1 | 1].lef) res = min(res, query_min(src << 1 | 1, lef, rig));
        return res;
    }
};
