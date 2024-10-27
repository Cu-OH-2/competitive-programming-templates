void solve()
{
    ll n;
    cin >> n;
    for (ll lef = 1, rig; lef <= n; lef = rig + 1)
    {
        rig = n / (n / lef);
    }
    for (ll lef = 1, rig; lef <= n; lef = rig + 1)
    {
        ll ud = (n + lef - 1) / lef;
        if (ud == 1) rig = n;
        else rig = (n - 1) / ((n + lef - 1) / lef - 1) + 1;
    }
    return;
}