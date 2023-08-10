/*******************************************************************
* 时间复杂度：n,m,t同级时O(n^(5/3))
* 说明：
*******************************************************************/
const int N = 150005;
const int M = 150005;

ll BLOCK;

struct Q
{
    ll l, r, id, t;
    bool operator<(const Q& rhs) const
    {
        // 左右端点都分块
        if (l / BLOCK == rhs.l / BLOCK)
        {
            if (r / BLOCK == rhs.r / BLOCK) return t < rhs.t;
            else return r / BLOCK < rhs.r / BLOCK;
        }
        else return l / BLOCK < rhs.l / BLOCK;
    }
} q[M];

struct C
{
    ll p, o, v;
} c[M];

ll n, m, a[N], ans[N];

void solve()
{
    cin >> n >> m;
    BLOCK = pow(n, 2.0 / 3);
    for (int i = 1; i <= n; ++i) cin >> a[i];
    ll mxx = *max_element(a + 1, a + 1 + n);

    // 离线处理询问
    char op;
    ll t = 0, ord = 0, u, v;
    for (int i = 1; i <= m; ++i)
    {
        cin >> op >> u >> v;
        if (op == 'R') c[++t] = { u, a[u], v }, a[u] = v;
        else ord++, q[ord] = { u, v, ord, t };
    }
    sort(q + 1, q + 1 + ord);

    // 计算首个询问答案
    vector<ll> cnt(mxx + 1);
    ll res = 0, l = q[1].l, r = q[1].r, nowt = t;
    auto del = [&](int p)
    {
        cnt[a[p]]--;
        if (cnt[a[p]] == 0) res--;
        return;
    };
    auto add = [&](int p)
    {
        cnt[a[p]]++;
        if (cnt[a[p]] == 1) res++;
        return;
    };
    auto chg = [&](int p, ll v)
    {
        if (p >= l && p <= r) del(p);
        a[p] = v;
        if (p >= l && p <= r) add(p);
        return;
    };
    while (nowt > q[1].t) a[c[nowt].p] = c[nowt].o, nowt--;
    for (int i = l; i <= r; ++i) add(i);
    ans[q[1].id] = res;

    // 开始转移
    for (int i = 2; i <= ord; ++i)
    {
        for (int j = q[i - 1].t + 1; j <= q[i].t; ++j) chg(c[j].p, c[j].v);
        for (int j = q[i - 1].t; j > q[i].t; --j) chg(c[j].p, c[j].o);
        while (r < q[i].r) add(++r);
        while (r > q[i].r) del(r--);
        while (l < q[i].l) del(l++);
        while (l > q[i].l) add(--l);
        ans[q[i].id] = res;
    }
    for (int i = 1; i <= ord; ++i) cout << ans[i] << '\n';
    return;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T = 1;
    // cin >> T;
    while (T--) solve();
    return 0;
}