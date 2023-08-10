/*******************************************************************
* 时间复杂度：框架O(qlogm)
* 说明：
* 1.对多个需要二分解决的询问同时二分
* 2.二分对象为答案值域，但也将询问序列分到两个值域区间中
* 3.对于区间[l,r)的check不能到达O(q)/O(m)，应只考虑[l,r)中的值或询问
* 4.注意分到右半区间的询问目标值要削减
* 5.注意值域区间和询问区间的开闭
* 6.注意必要时对元素值去重
*******************************************************************/
const int N = 300005;

struct Fenwick { /*带时间戳树状数组*/ }fen;
struct Discret { /*离散化*/ }D;

struct Q
{
    int l, r, k, id;
}q[N];

int n, m;
pair<int, int> a[N];
int ans[N];

void bis(int lef, int rig, int ql, int qr)
{
    if (lef == rig - 1)
    {
        for (int i = ql; i < qr; ++i) ans[q[i].id] = lef;
        return;
    }
    int mid = lef + rig >> 1;
    for (int i = lef; i < mid; ++i)
    {
        fen.add(a[i].second, 1);
    }
    queue<Q> q1, q2;
    for (int i = ql; i < qr; ++i)
    {
        int cnt = fen.rsum(q[i].l, q[i].r);
        if (cnt < q[i].k) q2.push({ q[i].l,q[i].r,q[i].k - cnt,q[i].id });
        else q1.push(q[i]);
    }
    int qm = ql + q1.size();
    for (int i = ql; i < qr; ++i)
    {
        if (q1.size()) q[i] = q1.front(), q1.pop();
        else q[i] = q2.front(), q2.pop();
    }
    fen.clear();
    bis(lef, mid, ql, qm);
    bis(mid, rig, qm, qr);
    return;
}

void solve()
{
    cin >> n >> m;
    fen.init(n);
    for (int i = 1; i <= n; ++i)
    {
        cin >> a[i].first;
        a[i].second = i;
        D.insert(a[i].first);
    }
    D.work();
    for (int i = 1; i <= n; ++i) a[i].first = D[a[i].first];
    sort(a + 1, a + 1 + n);
    for (int i = 1; i <= m; ++i)
    {
        cin >> q[i].l >> q[i].r >> q[i].k;
        q[i].id = i;
    }
    bis(1, n + 1, 1, m + 1);
    for (int i = 1; i <= m; ++i) cout << D.v[ans[i] - 1] << '\n';
    return;
}