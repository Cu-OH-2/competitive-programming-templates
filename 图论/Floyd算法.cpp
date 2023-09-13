/*******************************************************************
* 时间复杂度：O(N^3)
* 说明：多源最短路、最短路计数、最小环计数
*******************************************************************/
const int N = 505;
const int MOD = 998244353;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;

int n, m;
ll cnt[N][N]; // 最短路条数
ll dis[N][N]; // 最短路长度
ll edg[N][N]; // 边长

void solve()
{
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            if (i == j) dis[i][j] = 0;
            else dis[i][j] = INFLL;
            cnt[i][j] = 0;
            edg[i][j] = 0;
        }
    }
    for (int i = 1; i <= m; ++i)
    {
        int u, v, w;
        cin >> u >> v >> w;
        dis[u][v] = edg[u][v] = w;
        cnt[u][v] = 1;
    }
    map<ll, ll> ans;
    for (int k = 1; k <= n; ++k)
    {
        // 用指向最大编号点的边作为一个环的代表
        for (int i = 1; i < k; ++i)
        {
            if (edg[i][k] && cnt[k][i])
            {
                ans[edg[i][k] + dis[k][i]] += cnt[k][i];
                ans[edg[i][k] + dis[k][i]] %= MOD;
            }
        }
        // 最短路计数
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= n; ++j)
            {
                if (dis[i][k] + dis[k][j] < dis[i][j])
                {
                    dis[i][j] = dis[i][k] + dis[k][j];
                    cnt[i][j] = cnt[i][k] * cnt[k][j] % MOD;
                }
                else if (dis[i][j] == dis[i][k] + dis[k][j])
                {
                    cnt[i][j] += cnt[i][k] * cnt[k][j] % MOD;
                    cnt[i][j] %= MOD;
                }
            }
        }
    }
    if (ans.empty()) cout << "-1 -1\n";
    else cout << ans.begin()->first << ' ' << ans.begin()->second << '\n';
    return;
}