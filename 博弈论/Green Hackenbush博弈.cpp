void dfs(int x, int fa)
{
    sg[x] = 0;
    for (auto e : node[x])
    {
        if (e == fa) continue;
        dfs(e, x);
        sg[x] ^= sg[e] + 1;
    }
    return;
}