/*******************************************************************
* 时间复杂度: O(nsqrt(n))
* 说明: 莫队转移超过O(1)时，将所有转移离线并利用贡献可拆分性快速预处理
*******************************************************************/
const int B = 14;
const int N = 100005;

ll n, m, k;
ll a[N], BLOCK;

struct Q
{
    ll l, r, id, ans;
    bool operator<(const Q& rhs) const
    {
        int lb = l / BLOCK, rb = rhs.l / BLOCK;
        if (lb == rb)
        {
            if (r == rhs.r) return 0;
            else return (r < rhs.r) ^ (lb & 1);
        }
        else return lb < rb;
    }
} q[N];

void solve()
{
    cin >> n >> m >> k;
    BLOCK = sqrt(n);
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= m; ++i)
    {
        cin >> q[i].l >> q[i].r;
        q[i].id = i;
        q[i].ans = 0;
    }
    sort(q + 1, q + 1 + m);
    q[0].l = 1, q[0].r = 0, q[0].ans = 0;
    int lef = 1, rig = 0;
    array<vector<vector<int>>, 2> req{ vector<vector<int>>(n + 1), vector<vector<int>>(n + 1) };
    for (int i = 1; i <= m; ++i)
    {
        if (rig < q[i].r) req[0][lef].push_back(i), rig = q[i].r;
        if (lef > q[i].l) req[1][rig].push_back(i), lef = q[i].l;
        if (rig > q[i].r) req[0][lef].push_back(i), rig = q[i].r;
        if (lef < q[i].l) req[1][rig].push_back(i), lef = q[i].l;
    }
    vector<ll> tar;
    for (int i = 0; i < (1 << B); ++i)
    {
        if (__builtin_popcount(i) == k) tar.push_back(i);
    }
    vector<ll> cnt(1 << B), pre(n + 2), suf(n + 2);
    for (int i = 1; i <= n; ++i)
    {
        pre[i] = cnt[a[i]];
        for (auto e : req[0][i])
        {
            if (q[e - 1].r < q[e].r)
            {
                for (int j = q[e - 1].r + 1; j <= q[e].r; ++j) q[e].ans -= cnt[a[j]];
            }
            else
            {
                for (int j = q[e].r + 1; j <= q[e - 1].r; ++j) q[e].ans += cnt[a[j]];
            }
        }
        for (auto e : tar) cnt[a[i] ^ e]++;
    }
    fill(cnt.begin(), cnt.end(), 0ll);
    for (int i = n; i >= 1; --i)
    {
        suf[i] = cnt[a[i]];
        for (auto e : req[1][i])
        {
            if (q[e - 1].l > q[e].l)
            {
                for (int j = q[e - 1].l - 1; j >= q[e].l; --j) q[e].ans -= cnt[a[j]];
            }
            else
            {
                for (int j = q[e].l - 1; j >= q[e - 1].l; --j) q[e].ans += cnt[a[j]];
            }
        }
        for (auto e : tar) cnt[a[i] ^ e]++;
    }
    lef = 1, rig = 0;
    for (int i = 1; i <= m; ++i)
    {
        q[i].ans += q[i - 1].ans;
        while (rig < q[i].r) q[i].ans += pre[++rig];
        while (lef > q[i].l) q[i].ans += suf[--lef];
        while (rig > q[i].r) q[i].ans -= pre[rig--];
        while (lef < q[i].l) q[i].ans -= suf[lef++];
    }
    vector<ll> ans(m + 1);
    for (int i = 1; i <= m; ++i) ans[q[i].id] = q[i].ans;
    for (int i = 1; i <= m; ++i) cout << ans[i] << '\n';
    return;
}