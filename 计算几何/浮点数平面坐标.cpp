/*******************************************************************
* 时间复杂度: ?
* 说明: 浮点数平面坐标相关操作
*******************************************************************/
using ld = long double;

constexpr ld INF = 1e100;
constexpr ld PI = acosl(-1);

struct P
{
    ld x, y;

    P(): x(0), y(0) {}
    P(ld x, ld y): x(x), y(y) {}

    P operator-(const P& rhs) const { return P(x - rhs.x, y - rhs.y); }
    P operator+(const P& rhs) const { return P(x + rhs.x, y + rhs.y); }
    ld operator*(const P& rhs) const { return x * rhs.x + y * rhs.y; }
    ld len() { return sqrtl(*this * *this); }
    void rotate(ld rad, const P& p = P(0, 0)) // counterclockwise
    {
        P rel(*this - p);
        *this = P(rel.x * cos(rad) - rel.y * sin(rad), rel.x * sin(rad) + rel.y * cos(rad)) + p;
        return;
    }
};

ld deg_to_rad(int x) { return x * PI / 180; }
ld sqr(ld x) { return x * x; }
ld dis(const P& p1, const P& p2) { return (p1 - p2).len(); }
ld cross(const P& p1, const P& p2) { return p1.x * p2.y - p2.x * p1.y; }
ld area(const P& p1, const P& p2, const P& p3) { return fabsl(cross(p2 - p1, p3 - p1)) / 2; }

ld closest(vector<P>& p) // P1429
{
    sort(p.begin(), p.end(), [](auto x, auto y) { return x.x < y.x; });
    function<ld(int, int)> work = [&](int lef, int rig)
    {
        if (lef == rig - 1) return INF;
        int mid = lef + (rig - lef) / 2;
        ld midx = p[mid].x;
        ld low = min(work(lef, mid), work(mid, rig));
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
            if (fabsl(p[i].x - midx) < low) v.push_back(p[i]);
        }
        for (int i = 1; i < v.size(); ++i)
        {
            for (int j = i - 1; j >= 0; --j)
            {
                if (v[i].y - v[j].y >= low) break;
                low = min(low, dis(v[i], v[j]));
            }
        }
        return low;
    };
    return work(0, p.size());
}
