using ld = long double;

constexpr ld INF = 1e100;
constexpr ld PI = acosl(-1);
constexpr ld EPS = 1e-9;

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

P intersect(const P& p1, const P& p2, const P& p3, const P& p4) // 直线p1p2和p3p4的交点，需确保交点唯一存在
{
    ld s1 = cross(p2 - p1, p3 - p1);
    ld s2 = cross(p2 - p1, p4 - p1);
    return P((p3.x * s2 - p4.x * s1) / (s2 - s1), (p3.y * s2 - p4.y * s1) / (s2 - s1));
}

ld closest(vector<P>& p) // 最近点对，P1429
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

array<ld, 3> circle(const P& p1, const P& p2, const P& p3) // 三点定圆
{
    P a(2 * (p1.x - p2.x), 2 * (p1.x - p3.x));
    P b(2 * (p1.y - p2.y), 2 * (p1.y - p3.y));
    P c(p1 * p1 - p2 * p2, p1 * p1 - p3 * p3);
    P o(cross(c, b) / cross(a, b), cross(c, a) / cross(b, a));
    return { o.x, o.y, dis(o, p1) };
}

array<ld, 3> circle(vector<P>& p) // 最小圆覆盖
{
    shuffle(p.begin(), p.end(), mt19937(time(0)));
    int m = p.size();
    P c;
    ld r = 0;
    for (int i = 0; i < m; ++i)
    {
        if (dis(p[i], c) <= r + EPS) continue;
        c = p[i], r = 0;
        for (int j = 0; j < i; ++j)
        {
            if (dis(p[j], c) <= r + EPS) continue;
            c.x = (p[i].x + p[j].x) / 2;
            c.y = (p[i].y + p[j].y) / 2;
            r = dis(p[i], p[j]) / 2;
            for (int k = 0; k < j; ++k)
            {
                if (dis(p[k], c) < r + EPS) continue;
                auto cir = circle(p[i], p[j], p[k]);
                c.x = cir[0], c.y = cir[1], r = cir[2];
            }
        }
    }
    return { c.x, c.y, r };
}

array<P, 4> rectangle(vector<P>& p) // 最小矩形覆盖
{
    // convex & counterclockwise
    array<P, 4> res{};
    ld ans = INF;
    int m = p.size();
    int top = 1, lef = -1, rig = 1;
    for (int i = 0; i < m; ++i)
    {
        P bot = p[(i + 1) % m] - p[i];
        while (bot * (p[(rig + 1) % m] - p[i]) >= bot * (p[rig] - p[i])) rig = (rig + 1) % m;
        while (cross(p[(top + 1) % m] - p[i], bot) <= cross(p[top] - p[i], bot)) top = (top + 1) % m;
        if (lef == -1) lef = top;
        while (bot * (p[(lef + 1) % m] - p[i]) <= bot * (p[lef] - p[i])) lef = (lef + 1) % m;
        ld lb = (p[i] - p[lef]) * bot / bot.len(), rb = (p[rig] - p[i]) * bot / bot.len();
        ld base = lb + rb;
        ld high = cross(bot, p[top] - p[i]) / bot.len();
        ld area = base * high;
        if (area < ans)
        {
            ans = area;
            ld o = bot.len();
            bot.x /= o, bot.y /= o;
            res[0] = p[i] + P(-bot.x * lb, -bot.y * lb);
            res[1] = p[i] + P(bot.x * rb, bot.y * rb);
            P h(-bot.y * high, bot.x * high);
            res[2] = res[1] + h, res[3] = res[0] + h;
        }
    }
    return res;
}