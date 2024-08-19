const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const int N = 3005;

struct Edge
{
    int to; // 终点
    int rev; // 反向边对其起点的编号
    ll cap; // 残量
    Edge() {}
    Edge(int to, int rev, ll cap) :to(to), rev(rev), cap(cap) {}
};

vector<Edge> node[N];

void AddEdge(int from, int to, ll cap)
{
    int x = node[to].size();
    int y = node[from].size();
    node[from].push_back(Edge(to, x, cap));
    node[to].push_back(Edge(from, y, 0));
    return;
}

struct Dinic
{
    int sz;
    vector<int> dep; // 每个点所属层深度
    vector<int> done; // 每个点下一个要处理的邻接边
    queue<int> q;

    Dinic(int x)
    {
        sz = x;
        dep.resize(sz + 1);
        done.resize(sz + 1);
    }

    bool bfs(int s, int t) // 建立分层图
    {
        for (int i = 1; i <= sz; ++i) dep[i] = 0;
        q.push(s);
        dep[s] = 1;
        done[s] = 0;
        bool f = 0;
        while (q.size())
        {
            int now = q.front();
            q.pop();
            if (now == t) f = 1; // 到达终点说明存在增广路
            for (auto e : node[now])
            {
                if (e.cap && dep[e.to] == 0) // 还有残量且未访问过
                {
                    q.push(e.to);
                    done[e.to] = 0; // 有增广路，需要重新处理
                    dep[e.to] = dep[now] + 1;
                }
            }
        }
        return f;
    }

    ll dfs(int x, int t, ll flow) // 统计增广路总流量
    {
        if (x == t || flow == 0) return flow; // 找到汇点或断流
        ll rem = flow; // 结点x当前剩余流量
        for (int i = done[x]; i < node[x].size() && rem; ++i)
        {
            done[x] = i; // 前i-1条边已经搞定，不会再有增广路
            auto& e = node[x][i];
            if (e.cap && dep[e.to] == dep[x] + 1)// 还有残量且为下一层
            {
                ll inflow = dfs(e.to, t, min(rem, e.cap)); // 计算流向e.to的最大流量
                if (inflow == 0) dep[e.to] = 0; // e.to无法流入，本次增广不再考虑
                e.cap -= inflow; // 更新残量
                node[e.to][e.rev].cap += inflow; // 更新反向边
                rem -= inflow; // 消耗流量
            }
        }
        return flow - rem;
    }

    ll work(int s, int t)
    {
        ll aug = 0, ans = 0;
        while (bfs(s, t))
        {
            while (aug = dfs(s, t, INFLL)) ans += aug;
        }
        return ans;
    }
};