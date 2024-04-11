/*******************************************************************
* 时间复杂度: O(logm)
* 说明: 适用于有根树
*******************************************************************/
const int N = 500005;

vector<int> node[N];

struct LCA
{
    vector<int> d; //到根距离
    vector<vector<int>> st;

    void dfs(int x)
    {
        for (auto e : node[x])
        {
            if (e == st[x][0]) continue;
            d[e] = d[x] + 1;
            st[e][0] = x;
            dfs(e);    
        }
        return;
    }

    void build(int sz)
    {
        int lg = __lg(sz);
        for (int i = 1; i <= lg; ++i)
        {
            for (int j = 1; j <= sz; ++j)
            {
                if (d[j] >= (1 << i))
                {
                    st[j][i] = st[st[j][i - 1]][i - 1];
                }
            }
        }
        return;
    }

    LCA(int x, int root) 
    { 
        d.resize(x + 1);
        st.resize(x + 1, vector<int>(32));
        dfs(root);
        build(x); 
    }

    int query(int a, int b)
    {
        if (d[a] < d[b]) swap(a, b);
        int dif = d[a] - d[b];
        for (int i = 0; dif >> i; ++i)
        {
            if (dif >> i & 1) a = st[a][i];
        }
        if (a == b) return a;
        else
        {
            for (int i = 31; i >= 0; --i)
            {
                while (st[a][i] != st[b][i])
                {
                    a = st[a][i];
                    b = st[b][i];
                }
            }
            return st[a][0];
        }
    }
};