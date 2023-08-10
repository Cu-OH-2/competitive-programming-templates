/*******************************************************************
* 时间复杂度：朴素O(N^2)/堆优化O(MlogM)
* 说明：
* 1.只适用于非负边权
* 2.稀疏图用堆优化，稠密图用朴素
* 3.注意处理图不连通的情况（dis==INFLL）
*******************************************************************/
const int N = 100005;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;

struct Edge {int to, v;};

vector<Edge> node[N];

struct Dijkstra
{
    struct NodeInfo
    {
        int id;
        ll d;
        bool operator < (const NodeInfo& p1) const
        {
            return d > p1.d;
        }
    };

    int sz;
    vector<int> vis;
    vector<ll> dis;

    Dijkstra(int x)
    {
        sz = x;
        vis.resize(sz + 1);
        dis.resize(sz + 1, INFLL);
    }

    void workO(int s)
    {
        priority_queue<NodeInfo> pq;
        dis[s] = 0;
        pq.push({ s,0 });
        while (pq.size())
        {
            int now = pq.top().id;
            pq.pop();
            if (vis[now] == 0)
            {
                vis[now] = 1; //被取出一定是最短路
                for (auto e : node[now])
                {
                    if (vis[e.to] == 0 && dis[e.to] > dis[now] + e.v)
                    {
                        dis[e.to] = dis[now] + e.v;
                        pq.push({ e.to,dis[e.to] });
                    }
                }
            }
        }
        return;
    }

    void workS(int s)
    {
        auto take = [&](int x)
        {
            vis[x] = 1;
            for (auto e : node[x])
            {
                dis[e.to] = min(dis[e.to], dis[x] + e.v);
            }
            return;
        };
        dis[s] = 0;
        take(s);
        for (int i = 1; i <= sz - 1; ++i)
        {
            ll mnn = INFLL;
            int id = 0;
            for (int j = 1; j <= sz; ++j)
            {
                if (vis[j] == 0 && dis[j] < mnn)
                {
                    mnn = dis[j];
                    id = j;
                }
            }
            if (mnn == INFLL) return;
            take(id);
        }
        return;
    }
};