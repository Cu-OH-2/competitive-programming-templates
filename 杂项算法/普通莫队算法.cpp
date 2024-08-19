const int N = 50005;
const int M = 50005;

ll n, m, k, a[N], BLOCK;
ll ans[M];

struct Q
{
    ll l, r, id;
    bool operator<(const Q& rhs) const
    {
        // 奇偶化排序优化常数
        int lb = l / BLOCK, rb = rhs.l / BLOCK;
        if (lb == rb)
        {
            if (r == rhs.r) return 0;
            else return (r < rhs.r) ^ (lb & 1);
        }
        else return lb < rb;
    }
} q[M];

void solve()
{
    cin >> n >> m >> k;
    BLOCK = n / sqrt(m); // 块大小
    for (int i = 1; i <= n; ++i) cin >> a[i];

    // 离线处理询问
    for (int i = 1; i <= m; ++i) q[i].id = i, cin >> q[i].l >> q[i].r;
    sort(q + 1, q + 1 + m);

    // 计算首个询问答案
    vector<int> cnt(k + 1);
    for (int i = q[1].l; i <= q[1].r; ++i) cnt[a[i]]++;
    ll res = 0;
    for (int i = 1; i <= k; ++i) res += cnt[i] * cnt[i];
    ans[q[1].id] = res;

    // 开始转移
    ll l = q[1].l, r = q[1].r;
    auto del = [&](int p)
    {
        res -= cnt[a[p]] * cnt[a[p]];
        cnt[a[p]]--;
        res += cnt[a[p]] * cnt[a[p]];
        return;
    };
    auto add = [&](int p)
    {
        res -= cnt[a[p]] * cnt[a[p]];
        cnt[a[p]]++;
        res += cnt[a[p]] * cnt[a[p]];
        return;
    };
    for (int i = 2; i <= m; ++i)
    {
        while (r < q[i].r) add(++r);
        while (r > q[i].r) del(r--);
        while (l < q[i].l) del(l++);
        while (l > q[i].l) add(--l);
        ans[q[i].id] = res;
    }
    for (int i = 1; i <= m; ++i) cout << ans[i] << '\n';
    return;
}