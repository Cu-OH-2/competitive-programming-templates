int vis[M];
vector<int> node[N];
vector<int> stk;

void dfs(int x)
{
    for (auto e : node[x])
    {
        if (vis[e.second]) continue;
        vis[e.second] = 1;
        dfs(e.first);
    }
    stk.push_back(x);
}