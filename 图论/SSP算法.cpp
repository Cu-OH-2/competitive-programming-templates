/*******************************************************************
* 时间复杂度：O(NMF)（伪多项式，与最大流有关）
* 说明：
* 1.求最小费用最大流
* 2.无法处理负环，需要提前排除
*******************************************************************/
const int N = 5005;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;

struct Edge
{
    int to; //终点
    int rev; //反向边对其起点的编号
    ll cap; //残量
    ll cost; //单位流量费用
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

struct SSP
{
    int sz;
    vector<ll> dis; //源点到i的最小单位流量费用
    vector<int> vis;
    vector<int> done; //每个点下一个要处理的邻接边
    queue<int> q;
    ll minc, maxf;

    SSP(int x)
    {
        sz = x;
        dis.resize(sz + 1);
        vis.resize(sz + 1);
        done.resize(sz + 1);
        minc = maxf = 0;
    }

    bool spfa(int s, int t) //寻找单位流量费用最小的增广路
    {
        vis.assign(sz + 1, 0);
        done.assign(sz + 1, 0);
        dis.assign(sz + 1, INFLL);
        dis[s] = 0;
        q.push(s);
        vis[s] = 1;
        while (q.size())
        {
            int now = q.front();
            q.pop();
            vis[now] = 0;
            for (auto e : node[now])
            {
                if (e.cap && dis[e.to] > dis[now] + e.cost) //还有残量且可松弛
                {
                    dis[e.to] = dis[now] + e.cost;
                    if (vis[e.to] == 0) q.push(e.to), vis[e.to] = 1;
                }
            }
        }
        return dis[t] != INFLL;
    }

    ll dfs(int x, int p, int t, ll flow) //沿增广路计算流量和费用
    {
        if (x == t || flow == 0) return flow; //找到汇点或断流
        vis[x] = 1; //防止零权环死循环
        ll rem = flow; //结点x当前剩余流量
        for (int i = done[x]; i < node[x].size() && rem; ++i)
        {
            done[x] = i; //前i-1条边已经搞定，不会再有增广路
            auto& e = node[x][i];
            if (e.to != p && vis[e.to] == 0 && e.cap && dis[e.to] == dis[x] + e.cost)
            {
                ll inflow = dfs(e.to, x, t, min(rem, e.cap)); //计算流向e.to的最大流量
                e.cap -= inflow; //更新残量
                node[e.to][e.rev].cap += inflow; //更新反向边
                rem -= inflow; //消耗流量
            }
        }
        vis[x] = 0; //出递归栈后可重新访问
        return flow - rem;
    }

    void work(int s, int t)
    {
        ll aug = 0;
        while (spfa(s, t))
        {
            while (aug = dfs(s, 0, t, INFLL))
            {
                maxf += aug;
                minc += dis[t] * aug;
            }
        }
        return;
    }
};