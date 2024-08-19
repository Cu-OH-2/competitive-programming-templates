const int N = 100005;
const int M = 40005;

ll n, m; // 种数、容积
ll v[N], w[N], k[N]; // 价值、体积、数量
ll dp[M]; // 使用i容积的最大价值

struct Node
{
    ll key, id;
};

void solve()
{
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> v[i] >> w[i] >> k[i];
    for (int i = 1; i <= n; ++i)
    {
        vector<deque<Node>> dq(w[i]);
        auto key = [&](int j) { return dp[j] - j / w[i] * v[i]; }; // dp[j]在比较基准下的指标
        auto join = [&](int j) // dp[j]入队
        {
            auto& q = dq[j % w[i]];
            while (q.size() && key(j) >= q.back().key) q.pop_back();
            q.push_back({ key(j),j });
            return;
        };
        for (int j = m; j >= max(0ll, m - k[i] * w[i]); --j) join(j);
        for (int j = m; j >= w[i]; --j)
        {
            auto& q = dq[j % w[i]];
            while (q.size() && q.front().id >= j) q.pop_front();
            if (j - k[i] * w[i] >= 0) join(j - k[i] * w[i]);
            dp[j] = max(dp[j], q.front().key + j / w[i] * v[i]);
        }
    }
    ll ans = 0;
    for (int i = 0; i <= m; ++i) ans = max(ans, dp[i]);
    cout << ans << '\n';
    return;
}