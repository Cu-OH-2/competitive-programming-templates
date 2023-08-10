/*******************************************************************
* 时间复杂度：O(N^3)
* 说明：
* 1.求任意两点间最短路
* 2.最短路计数
*******************************************************************/
const int N = 105;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;

int n, m;
ll dis[N][N], cnt[N][N];

void floyd()
{
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            for (int k = 1; k <= n; ++k)
            {
                if (dis[j][k] > dis[j][i] + dis[i][k])
                {
                    dis[j][k] = dis[j][i] + dis[i][k];
                    cnt[j][k] = cnt[j][i] * cnt[i][k];
                }
                else if (dis[j][k] == dis[j][i] + dis[i][k])
                {
                    cnt[j][k] += cnt[j][i] * cnt[i][k];
                }
            }
        }
    }
    return;
}

void solve()
{
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            dis[i][j] = INFLL;
        }
    }
    ll u, v, w;
    for (int i = 1; i <= m; ++i)
    {
        cin >> u >> v >> w;
        dis[u][v] = dis[v][u] = w;
        cnt[u][v] = cnt[v][u] = 1;
    }
    floyd();
    return;
}