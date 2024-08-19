void solve()
{
    ll n, k;
    cin >> n >> k;
    ll ans = 0;
    for (ll lef = 1, rig; lef <= n; lef = rig + 1) // 分块
    {
        if (k >= lef) rig = min(n, k / (k / lef));
        else rig = n; // 该区间大于k（余数都为k）
        ll div = k / lef, len = rig - lef + 1;
        ans += k * len - div * (lef + rig) * len / 2;
    }
    cout << ans << '\n';
    return 0;
}