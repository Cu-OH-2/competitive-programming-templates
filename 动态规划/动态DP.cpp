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

    void update(int src)
    {
        for (int i = 0; i < 2; ++i)
        {
            for (int j = 0; j < 2; ++j)
            {
                auto v1 = tree[src << 1].mat[i][1] + tree[src << 1 | 1].mat[1][j];
                auto v2 = tree[src << 1].mat[i][0] + tree[src << 1 | 1].mat[1][j];
                auto v3 = tree[src << 1].mat[i][1] + tree[src << 1 | 1].mat[0][j];
                tree[src].mat[i][j] = min({ v1, v2, v3 });
            }
        }
        return;
    }

    void settle(int src, ll val)
    {
        tree[src].mat[1][1] = val;
        tree[src].mat[0][0] = 0;
        tree[src].mat[0][1] = tree[src].mat[1][0] = INFLL;
    }

    SegTree(int x) { tree.resize(x * 4 + 1); }

    void build(int src, int lef, int rig, ll arr[])
    {
        tree[src].lef = lef;
        tree[src].rig = rig;
        if (lef == rig)
        {
            settle(src, arr[lef]);
            return;
        }
        int mid = lef + (rig - lef) / 2;
        build(src << 1, lef, mid, arr);
        build(src << 1 | 1, mid + 1, rig, arr);
        update(src);
        return;
    }

    void modify(int src, int pos, ll val)
    {
        if (tree[src].lef == tree[src].rig)
        {
            settle(src, val);
            return;
        }
        int mid = tree[src].lef + (tree[src].rig - tree[src].lef) / 2;
        if (pos <= mid) modify(src << 1, pos, val);
        else modify(src << 1 | 1, pos, val);
        update(src);
        return;
    }

    ll query() { return tree[1].mat[1][1] * 2; }
};

int n, q, k;
ll a[N], x;

void solve() // CF1814E
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