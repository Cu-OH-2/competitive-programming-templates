/*******************************************************************
* 时间复杂度：O(N+M)
* 说明：求强连通分量，也可求缩点后新图
*******************************************************************/
const int N = 10005;

int n, m;
int a[N]; //旧图点权
vector<int> node[N];

struct Tarjan
{
    int sz, cnt, ord;
    stack<int> stk;
    vector<vector<int>> g; //新图
    vector<int> dfn, low, id, val;
    Tarjan(int x)
    {
        sz = x; //点数
        cnt = 0; //强连通分量个数
        ord = 0; //时间戳
        dfn.resize(sz + 1); //dfs序
        low.resize(sz + 1); //能到达的最小dfn
        id.resize(sz + 1); //对应的强连通分量编号
        val.resize(sz + 1); //新图点权
    }
    void dfs(int x)
    {
        stk.push(x);
        dfn[x] = low[x] = ++ord;
        for (auto e : node[x])
        {
            if (dfn[e] == 0) //未访问
            {
                dfs(e);
                low[x] = min(low[x], low[e]);
            }
            else if (id[e] == 0) //在栈中
            {
                low[x] = min(low[x], low[e]);
            }
        }
        if (dfn[x] == low[x]) //x为强连通分量的根
        {
            cnt++;
            while (dfn[stk.top()] != low[stk.top()]) //强连通分量中只有根dfn=low
            {
                val[cnt] += a[stk.top()];
                id[stk.top()] = cnt;
                stk.pop();
            }
            val[cnt] += a[stk.top()];
            id[stk.top()] = cnt;
            stk.pop();
        }
        return;
    }
    void shrink()
    {
        for (int i = 1; i <= sz; ++i)
        {
            if (id[i] == 0) dfs(i);
        }
        return;
    }
    void rebuild()
    {
        for (int i = 1; i <= sz; ++i)
        {
            for (auto e : node[i])
            {
                if (id[i] != id[e]) g[id[i]].push_back(id[e]);
            }
        }
        return;
    }
};