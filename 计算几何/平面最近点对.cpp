/*******************************************************************
* 时间复杂度: O(nlogn)
* 说明: P1429（浮点数），分治/归并排序
*******************************************************************/
const int N = 400005;
const double INF = 1e100;

double sqr(double x) { return x * x; }

struct Point
{
    double x, y;
    double dis(const Point& rhs) { return sqrt(sqr(x - rhs.x) + sqr(y - rhs.y)); }
    bool operator<(const Point& rhs) { return x < rhs.x; }
} p[N];

double work(int lef, int rig)
{
    if (lef == rig - 1) return INF;
    int mid = lef + (rig - lef) / 2;
    double midx = p[mid].x;
    double low = min(work(lef, mid), work(mid, rig));
    int lp = lef, rp = mid;
    vector<Point> v;
    while (lp < mid || rp < rig)
    {
        if (lp < mid && (rp == rig || p[rp].y > p[lp].y)) v.push_back(p[lp++]);
        else v.push_back(p[rp++]);
    }
    for (int i = lef; i < rig; ++i) p[i] = v[i - lef];
    v.clear();
    for (int i = lef; i < rig; ++i)
    {
        if (fabs(p[i].x - midx) < low) v.push_back(p[i]);
    }
    for (int i = 1; i < v.size(); ++i)
    {
        for (int j = i - 1; j >= 0; --j)
        {
            if (v[i].y - v[j].y >= low) break;
            low = min(low, v[i].dis(v[j]));
        }
    }
    return low;
}

void solve()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> p[i].x >> p[i].y;
    sort(p + 1, p + 1 + n);
    cout << fixed << setprecision(4) << work(1, n + 1) << '\n';
    return;
}

/*******************************************************************
* 时间复杂度: O(nlogn)
* 说明: P7883（整数），分治/归并排序，需要注意距离和距离的平方
*******************************************************************/
const int N = 400005;
const ll INF = 0x3f3f3f3f3f3f3f3f;

ll sqr(ll x) { return x * x; }

struct Point
{
    ll x, y;
    ll dd(const Point& rhs) { return sqr(x - rhs.x) + sqr(y - rhs.y); }
    bool operator<(const Point& rhs) { return x < rhs.x; }
} p[N];

ll work(int lef, int rig)
{
    if (lef == rig - 1) return INF;
    int mid = lef + (rig - lef) / 2;
    ll midx = p[mid].x;
    ll low = min(work(lef, mid), work(mid, rig));
    int lp = lef, rp = mid;
    vector<Point> v;
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
            low = min(low, v[i].dd(v[j]));
        }
    }
    return low;
}

void solve()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> p[i].x >> p[i].y;
    sort(p + 1, p + 1 + n);
    cout << work(1, n + 1) << '\n';
    return;
}