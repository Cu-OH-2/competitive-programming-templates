const int N = 100005;
const int M = 40005;

struct Item
{
    ll v, w; // 价值、体积
};

ll n, m; // 种数、容积
ll dp[M]; // 使用i容积的最大价值

void solve()
{
    cin >> n >> m;
    vector<Item> items;
    ll x, y, z;
    for (int i = 1; i <= n; ++i)
    {
        ll b = 1;
        cin >> x >> y >> z;
        while (z > b)
        {
            z -= b;
            items.push_back({ x * b, y * b });
            b <<= 1;
        }
        items.push_back({ x * z, y * z });
    }
    for (auto e : items)
    {
        for (int i = m; i >= e.w; --i)
        {
            dp[i] = max(dp[i], dp[i - e.w] + e.v);
        }
    }
    ll ans = 0;
    for (int i = 0; i <= m; ++i) ans = max(ans, dp[i]);
    cout << ans << '\n';
    return;
}