/*******************************************************************
* 时间复杂度：O(n+m)
* 说明：对点双中的任意三点a,b,c，一定存在a->b->c的简单路径
*******************************************************************/
int n, m;
vector<int> node[N];

struct RSTree
{
    int sz, ord, cnt;
    stack<int> stk;
    vector<int> dfn, low, tag;
    vector<vector<int>> g;
    RSTree(int x)
    {
        cnt = x; // 方点编号
        sz = x; // 点数
        ord = 0; // 时间戳
        dfn.resize(sz + 1); // dfs序
        low.resize(sz + 1); // 能到达的最小dfn
        g.resize(sz * 2 + 1); // 圆方树
    }
    void dfs(int x, int fa)
    {
        stk.push(x);
        dfn[x] = low[x] = ++ord;
        for (auto e : node[x])
        {
            if (dfn[e] == 0) // 未访问过
            {
                dfs(e, x);
                low[x] = min(low[x], low[e]);
                if (low[e] >= dfn[x])
                {
                    cnt++;
                    while (stk.top() != e)
                    {
                        g[cnt].push_back(stk.top());
                        g[stk.top()].push_back(cnt);
                        stk.pop();
                    }
                    g[cnt].push_back(stk.top());
                    g[stk.top()].push_back(cnt);
                    stk.pop();
                    g[cnt].push_back(x);
                    g[x].push_back(cnt);
                }
            }
            else if (e != fa) // 祖先
            {
                low[x] = min(low[x], dfn[e]);
            }
        }
        return;
    }
    void work()
    {
        for (int i = 1; i <= sz; ++i)
        {
            if (dfn[i]) continue;
            while (stk.size()) stk.pop();
            dfs(i, 0);
        }
        return;
    }
};