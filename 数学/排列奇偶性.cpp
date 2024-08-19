void solve()
{
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    int inv = n & 1;
    vector<bool> vis(n + 1);
    for (int i = 1; i <= n; ++i)
    {
        if (vis[i]) continue;
        int cur = i;
        while (!vis[cur])
        {
            vis[cur] = 1;
            cur = a[cur];
        }
        inv ^= 1;
    }
    return;
}