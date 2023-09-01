/*******************************************************************
* 时间复杂度: O(n)
* 说明: 
* 1.按照第一关键字顺序传入，按照第二关键字大小构建
* 2.第一关键字满足二叉搜索树性质，第二关键字满足小根堆性质
*******************************************************************/
const ll INFLL = 0x3f3f3f3f3f3f3f3f;

struct CarTree
{
    vector<pair<ll, ll>> v;
    vector<int> ls, rs;
    int sz;
    CarTree(): v(1, { -INFLL, -INFLL }), sz(0) {}
    void insert(ll a, ll b)
    {
        v.push_back({ a, b });
        sz++;
        return;
    }
    void build()
    {
        ls.resize(v.size());
        rs.resize(v.size());
        stack<int> stk;
        stk.push(0);
        for (int i = 1; i <= sz; ++i)
        {
            while (v[stk.top()].second > v[i].second) stk.pop();
            ls[i] = rs[stk.top()];
            rs[stk.top()] = i;
            stk.push(i);
        }
        return;
    }
};