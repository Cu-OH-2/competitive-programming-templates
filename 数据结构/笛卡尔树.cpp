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