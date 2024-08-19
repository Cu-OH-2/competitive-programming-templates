const int N = 5005;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;

struct Edge
{
    int to; // 终点
    int rev; // 反向边对其起点的编号
    ll cap; // 残量
    ll cost; // 单位流量费用
    Edge() {}
    Edge(int to, int rev, ll cap, ll cost) :to(to), rev(rev), cap(cap), cost(cost) {}
};

vector<Edge> node[N];

void addEdge(int from, int to, ll cap, ll cost)
{
    int x = node[to].size();
    int y = node[from].size();
    node[from].push_back(Edge(to, x, cap, cost));
    node[to].push_back(Edge(from, y, 0, -cost));
    return;
}

struct PrimalDual
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
    vector<ll> h; // 势能
    vector<int> vis;
    vector<int> done; // 每个点下一个要处理的邻接边
    vector<ll> dis;
    queue<int> q;
    priority_queue<NodeInfo> pq;
    ll minc, maxf;

    PrimalDual(int x)
    {
        sz = x;
        h.resize(sz + 1, INFLL);
        vis.resize(sz + 1);
        done.resize(sz + 1);
        dis.resize(sz + 1);
        minc = maxf = 0;
    }

    void spfa(int s) // 求初始势能
    {
        h[s] = 0;
        q.push(s);
        vis[s] = 1;
        while (q.size())
        {
            auto now = q.front();
            q.pop();
            vis[now] = 0;
            for (auto e : node[now])
            {
                if (e.cap && h[e.to] > h[now] + e.cost)
                {
                    h[e.to] = h[now] + e.cost;
                    if (vis[e.to] == 0) q.push(e.to), vis[e.to] = 1;
                }
            }
        }
        return;
    }

    bool dijkstra(int s, int t)
    {
        dis.assign(sz + 1, INFLL);
        vis.assign(sz + 1, 0);
        done.assign(sz + 1, 0);
        dis[s] = 0;
        pq.push({ s,0 });
        while (pq.size())
        {
            int now = pq.top().id;
            pq.pop();
            if (vis[now] == 0)
            {
                vis[now] = 1; // 被取出一定是最短路
                for (auto e : node[now])
                {
                    ll cost = e.cost + h[now] - h[e.to];
                    if (vis[e.to] == 0 && e.cap && dis[e.to] > dis[now] + cost)
                    {
                        dis[e.to] = dis[now] + cost;
                        pq.push({ e.to,dis[e.to] });
                    }
                }
            }
        }
        vis.assign(sz + 1, 0); // 还原vis
        return dis[t] != INFLL;
    }

    ll dfs(int x, int t, ll flow) // 沿增广路计算流量和费用
    {
        if (x == t || flow == 0) return flow; // 找到汇点或断流
        vis[x] = 1; // 防止零权环死循环
        ll rem = flow; // 结点x当前剩余流量
        for (int i = done[x]; i < node[x].size() && rem; ++i)
        {
            done[x] = i; // 前i-1条边已经搞定，不会再有增广路
            auto& e = node[x][i];
            if (vis[e.to] == 0 && e.cap && e.cost == h[e.to] - h[x]) // 势能差等于费用表明是最短路
            {
                ll inflow = dfs(e.to, t, min(rem, e.cap)); // 计算流向e.to的最大流量
                e.cap -= inflow; // 更新残量
                node[e.to][e.rev].cap += inflow; // 更新反向边
                rem -= inflow; // 消耗流量
            }
        }
        vis[x] = 0; // 出递归栈后可重新访问
        return flow - rem;
    }

    void work(int s, int t)
    {
        spfa(s);
        ll aug = 0;
        while (dijkstra(s, t))
        {
            for (int i = 1; i <= sz; ++i) h[i] += dis[i]; // 更新势能
            while (aug = dfs(s, t, INFLL))
            {
                maxf += aug;
                minc += aug * h[t];
            }
        }
        return;
    }
};