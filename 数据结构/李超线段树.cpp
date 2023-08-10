/*******************************************************************
* 时间复杂度：建立O(n)/修改O(log^2n)/查询O(logn)
* 说明：
* 1.谨慎使用，注意浮点数精度和结点初始化问题
* 2.标记永久化，整条链每一层的值都可能是答案
*******************************************************************/
const int N = 100005;
const double EPS = 1e-9;

struct Seg
{
    double k, b;
    int lef, rig;
    void init(int x0, int y0, int x1, int y1)
    {
        lef = x0, rig = x1;
        if (x0 == x1)
        {
            k = 0, b = max(y0, y1);
        }
        else
        {
            k = double(y1 - y0) / (x1 - x0);
            b = y0 - x0 * k;
        }
    }
    double at(int x) { return k * x + b; }
} seg[N];

struct LCSegTree
{
    struct Node
    {
        int lef, rig, id;
    };
    vector<Node> tree;

    LCSegTree(int x) { tree.resize(x * 4 + 1); }

    void build(int src, int lef, int rig)
    {
        tree[src] = { lef, rig, 0 };
        if (lef == rig) return;
        int mid = (lef + rig) / 2;
        build(src << 1, lef, mid);
        build(src << 1 | 1, mid + 1, rig);
        return;
    }

    void add(int src, int id)
    {
        if (seg[id].lef <= tree[src].lef && seg[id].rig >= tree[src].rig)
        {
            update(src, id);
            return;
        }
        if (seg[id].lef <= tree[src << 1].rig) add(src << 1, id);
        if (seg[id].rig >= tree[src << 1 | 1].lef) add(src << 1 | 1, id);
        return;
    }

    bool compare(int id1, int id2, int x)
    {
        if (id1 == 0) return 1;
        if (id2 == 0) return 0;
        double r1 = seg[id1].at(x);
        double r2 = seg[id2].at(x);
        if (fabs(r1 - r2) < EPS) return id2 < id1;
        else return r2 > r1 + EPS;
    }

    void update(int src, int id)
    {
        int mid = (tree[src].lef + tree[src].rig) / 2;
        if (compare(tree[src].id, id, mid)) swap(tree[src].id, id);
        if (tree[src].lef == tree[src].rig) return;
        if (compare(tree[src].id, id, tree[src].lef)) update(src << 1, id);
        if (compare(tree[src].id, id, tree[src].rig)) update(src << 1 | 1, id);
        return;
    }

    int query(int src, int x)
    {
        if (tree[src].lef == tree[src].rig) return tree[src].id;
        if (x <= tree[src << 1].rig)
        {
            int r = query(src << 1, x);
            if (compare(r, tree[src].id, x)) return tree[src].id;
            else return r;
        }
        else
        {
            int r = query(src << 1 | 1, x);
            if (compare(r, tree[src].id, x)) return tree[src].id;
            else return r;
        }
    }
};