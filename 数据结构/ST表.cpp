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
        st.resize(sz + 1, vector<ll>(32));
    }
    void build(ll arr[])
    {
        for (int i = 1; i <= sz; ++i) st[i][0] = arr[i];
        int lg = __lg(sz);
        for (int i = 1; i <= lg; ++i)
        {
            for (int j = 1; j <= sz; ++j)
            {
                st[j][i] = st[j][i - 1];
                if (j + (1 << (i - 1)) <= sz)
                {
                    st[j][i] = max(st[j][i], st[j + (1 << (i - 1))][i - 1]);
                }
            }
        }
    }
    ll query(int lef, int rig)
    {
        int len = __lg(rig - lef + 1);
        return max(st[lef][len], st[rig - (1 << len) + 1][len]);
    }
};