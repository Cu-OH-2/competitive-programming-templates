/*******************************************************************
* 时间复杂度: 建表O(nlogn)/查询O(1)
* 说明: 可重复贡献问题[f(r,r)=r]的静态区间查询，一般是最值/gcd
*******************************************************************/
struct ST
{
    int sz;
    vector<vector<ll>> st;

    ST(int x) { init(x); }
    void init(int x)
    {
        sz = x;
        st.resize(32, vector<ll>(sz + 1));
    }
    void build(ll arr[])
    {
        for (int i = 1; i <= sz; ++i) st[0][i] = arr[i];
        int lg = __lg(sz);
        for (int i = 1; i <= lg; ++i)
        {
            for (int j = 1; j <= sz; ++j)
            {
                st[i][j] = st[i - 1][j];
                if (j + (1 << (i - 1)) <= sz)
                {
                    st[i][j] = max(st[i][j], st[i - 1][j + (1 << (i - 1))]);
                }
            }
        }
    }
    ll query(int lef, int rig)
    {
        int len = __lg(rig - lef + 1);
        return max(st[len][lef], st[len][rig - (1 << len) + 1]);
    }
};