/*******************************************************************
* 时间复杂度: O(qlogn)
* 说明: 将dp转移方程表示为矩阵乘法，用线段树维护矩阵，实现带修改dp。
*******************************************************************/
//CF1814E
const int N = 200005;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;

struct SegTree
{
    struct Node
    {
        int lef, rig;
        array<array<ll, 2>, 2> mat;
    };
    vector<Node> tree;

    inline int ls(int src) { return src * 2; }
    inline int rs(int src) { return src * 2 + 1; }
    inline Node& ln(int src) { return tree[ls(src)]; }
    inline Node& rn(int src) { return tree[rs(src)]; }

    inline void update(int src)
    {
        for (int i = 0; i < 2; ++i)
        {
            for (int j = 0; j < 2; ++j)
            {
                auto v1 = ln(src).mat[i][1] + rn(src).mat[1][j];
                auto v2 = ln(src).mat[i][0] + rn(src).mat[1][j];
                auto v3 = ln(src).mat[i][1] + rn(src).mat[0][j];
                tree[src].mat[i][j] = min({ v1, v2, v3 });
            }
        }
        return;
    }

    inline void calc(int src, ll val)
    {
        tree[src].mat[1][1] = val;
        tree[src].mat[0][0] = 0;
        tree[src].mat[0][1] = tree[src].mat[1][0] = INFLL;
        return;
    }

    SegTree(int x) { tree.resize(x * 4 + 1); }

    void build(int src, int lef, int rig, ll arr[])
    {
        tree[src].lef = lef;
        tree[src].rig = rig;
        if (lef == rig)
        {
            calc(src, arr[lef]);
            return;
        }
        int mid = lef + rig >> 1;
        build(ls(src), lef, mid, arr);
        build(rs(src), mid + 1, rig, arr);
        update(src);
        return;
    }

    void modify(int src, int pos, ll val)
    {
        if (tree[src].lef == tree[src].rig)
        {
            calc(src, val);
            return;
        }
        int mid = tree[src].lef + tree[src].rig >> 1;
        if (pos <= mid) modify(ls(src), pos, val);
        else modify(rs(src), pos, val);
        update(src);
        return;
    }

    ll query() { return tree[1].mat[1][1] * 2; }
};

int n, q, k;
ll a[N], x;

void solve()
{
    cin >> n;
    for (int i = 1; i <= n - 1; ++i) cin >> a[i];
    SegTree sgt(n - 1);
    sgt.build(1, 1, n - 1, a);
    cin >> q;
    for (int i = 1; i <= q; ++i)
    {
        cin >> k >> x;
        sgt.modify(1, k, x);
        cout << sgt.query() << '\n';
    }
    return;
}