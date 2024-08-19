const int N = 5005;
const int M = 200005;

const ll INFLL = 0x3f3f3f3f3f3f3f3f;

struct Edge {ll to, v;};

vector<Edge> node[N];
int n, m;

struct Prim
{
    int sz;
    vector<int> vis;
    vector<ll> dis;

    Prim(int x)
    {
        sz = x;
        vis.resize(sz + 1);
        dis.resize(sz + 1, INFLL);
    }

    ll work()
    {
        int now = 1;
        ll ans = 0;
        for (int i = 1; i <= sz - 1; ++i)
        {
            vis[now] = 1;
            for (auto e : node[now])
            {
                dis[e.to] = min(dis[e.to], e.v);
            }
            ll mnn = INFLL;
            for (int j = 1; j <= sz; ++j)
            {
                if (vis[j] == 0 && dis[j] < mnn)
                {
                    mnn = dis[j];
                    now = j;
                }
            }
            if (mnn == INFLL) return 0; // 不连通
            ans += mnn;
        }
        return ans;
    }
};