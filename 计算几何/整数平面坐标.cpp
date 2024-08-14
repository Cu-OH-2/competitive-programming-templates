/*******************************************************************
* 时间复杂度: ?
* 说明: 整数平面坐标相关操作
*******************************************************************/
const ll INF = 1e18;

struct P
{
    ll x, y;

    P(): x(0), y(0) {}
    P(ll x, ll y): x(x), y(y) {}

    P operator-(const P& rhs) const { return P(x - rhs.x, y - rhs.y); }
    P operator+(const P& rhs) const { return P(x + rhs.x, y + rhs.y); }
    ll operator*(const P& rhs) const { return x * rhs.x + y * rhs.y; }
    ll len2() { return *this * *this; }
};

ll sqr(ll x) { return x * x; }
ll dis2(const P& p1, const P& p2) { return (p1 - p2).len2(); }
ll cross(const P& p1, const P& p2) { return p1.x * p2.y - p2.x * p1.y; }

ll closest(vector<P>& p)
{
    sort(p.begin(), p.end(), [](auto x, auto y) { return x.x < y.x; });
    function<ll(int, int)> work = [&](int lef, int rig)
    {
        if (lef == rig - 1) return INF;
        int mid = lef + (rig - lef) / 2;
        ll midx = p[mid].x;
        ll low = min(work(lef, mid), work(mid, rig));
        int lp = lef, rp = mid;
        vector<P> v;
        while (lp < mid || rp < rig)
        {
            if (lp < mid && (rp == rig || p[rp].y > p[lp].y)) v.push_back(p[lp++]);
            else v.push_back(p[rp++]);
        }
        for (int i = lef; i < rig; ++i) p[i] = v[i - lef];
        v.clear();
        for (int i = lef; i < rig; ++i)
        {
            if (sqr(abs(p[i].x - midx)) < low) v.push_back(p[i]);
        }
        for (int i = 1; i < v.size(); ++i)
        {
            for (int j = i - 1; j >= 0; --j)
            {
                if (sqr(v[i].y - v[j].y) >= low) break;
                low = min(low, dis2(v[i], v[j]));
            }
        }
        return low;
    };
    return work(0, p.size());
}

ll diameter(vector<P>& p) // counterclockwise
{
    int m = p.size(), k = 1;
    ll res = 0;
    for (int i = 0; i < m; ++i)
    {
        while (cross(p[(i + 1) % m] - p[i], p[k] - p[i]) <= cross(p[(i + 1) % m] - p[i], p[(k + 1) % m] - p[i]))
            k = (k + 1) % m;
        res = max(res, dis2(p[i], p[k]));
        res = max(res, dis2(p[(i + 1) % m], p[k]));
    }
    return res;
}

vector<P> convex(vector<P>& p) // least points
{
    int m = p.size();
    sort(p.begin(), p.end(),
         [](auto x, auto y)
         {
             if (x.x == y.x) return x.y < y.y;
             return x.x < y.x;
         });
    vector<P> res;
    vector<int> stk;
    auto top = [&](int x) { return stk[stk.size() - x]; };
    for (int i = 0; i < m; ++i)
    {
        while (stk.size() >= 2 && cross(p[top(1)] - p[top(2)], p[i] - p[top(1)]) <= 0) stk.pop_back();
        stk.push_back(i);
    }
    for (auto e : stk) res.push_back(p[e]);
    stk.clear();
    for (int i = m - 1; i >= 0; --i)
    {
        while (stk.size() >= 2 && cross(p[top(1)] - p[top(2)], p[i] - p[top(1)]) <= 0) stk.pop_back();
        stk.push_back(i);
    }
    for (int i = 1; i + 1 < stk.size(); ++i) res.push_back(p[stk[i]]);
    return res;
}