const int N = 1505;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;

struct Edge {ll to, v;};

vector<Edge> node[N];

struct BellmanFord
{
    int sz;
    vector<ll> dis;

    BellmanFord(int x)
    {
        sz = x;
        dis.resize(sz + 1, INFLL);
    }
    
    void work(int s)
    {
        dis[s] = 0;
        for (int i = 1; i <= sz - 1; ++i)
        {
            for (int j = 1; j <= sz; ++j)
            {
                for (auto e : node[j])
                {
                    dis[e.to] = min(dis[e.to], dis[j] + e.v);
                }
            }
        }
        return;
    }

    bool negCir()
    {
        for (int i = 1; i <= sz; ++i)
        {
            for (auto e : node[i])
            {
                if (dis[e.to] > dis[i] + e.v) return 1;
            }
        }
        return 0;
    }
};