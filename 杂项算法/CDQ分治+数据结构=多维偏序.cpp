/*******************************************************************
* 时间复杂度：O(nlog^(d-1)n)
* 说明：
* 1.每降一维需要乘O(logn)时间
* 2.适用于高维偏序等小元素对大元素有贡献的问题
* 3.元素需要提前去重
* 4.注意小于等于和小于做法不同，如分治顺序与排序复原/mid的移动
* 5.贡献有顺序要求如dp时，先左再合并再右
* 6.有时需要离散化才能利用数据结构
*******************************************************************/
const int N = 100005;

struct Fenwick { /*带时间戳最大值树状数组*/ }fen;
struct Discret { /*离散化*/ }D;

struct Elem
{
    ll a, b, c;
    ll w, dp;
    bool operator!=(const Elem& e) const { return a != e.a || b != e.b || c != e.c; }
} e[N];

int n;

bool bya(const Elem& e1, const Elem& e2)
{
    if (e1.a == e2.a && e1.b == e2.b) return e1.c < e2.c;
    else if (e1.a == e2.a) return e1.b < e2.b;
    else return e1.a < e2.a;
}

bool byb(const Elem& e1, const Elem& e2)
{
    if (e1.b == e2.b) return e1.c < e2.c;
    else return e1.b < e2.b;
}

void cdq(int lef, int rig)
{
    if (e[lef].a == e[rig - 1].a) return;
    int mid = lef + (rig - lef) / 2;

    // 需要保证e[mid-1].a和e[mid].a不同
    if (e[lef].a == e[mid].a)
    {
        while (e[lef].a == e[mid].a) mid++;
    }
    else
    {
        while (e[mid - 1].a == e[mid].a) mid--;
    }

    // 解决左半
    cdq(lef, mid);

    // 解决合并
    sort(e + lef, e + mid, byb);
    sort(e + mid, e + rig, byb);
    int p1 = lef, p2 = mid;
    while (p2 < rig)
    {
        while (p1 < mid && e[p1].b < e[p2].b)
        {
            fen.add(D[e[p1].c], e[p1].dp);
            p1++;
        }
        e[p2].dp = max(e[p2].dp, e[p2].w + fen.pres(D[e[p2].c] - 1));
        p2++;
    }
    fen.clear();

    // 解决右半
    sort(e + mid, e + rig, bya); // 复原排序
    cdq(mid, rig);
    return;
}

void solve()
{
    cin >> n;
    vector<Elem> ori(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> ori[i].a >> ori[i].b >> ori[i].c >> ori[i].w;
        ori[i].dp = ori[i].w;
        D.insert(ori[i].c);
    }
    D.work();
    fen.init(D.v.size());
    sort(ori.begin(), ori.end(), bya);
    int cnt = 0;
    for (auto& x : ori)
    {
        if (cnt == 0 || e[cnt] != x) e[++cnt] = x;
        else e[cnt].dp = e[cnt].w = max(e[cnt].w, x.w);
    }
    cdq(1, cnt + 1);
    ll ans = 0;
    for (int i = 1; i <= cnt; ++i) ans = max(ans, e[i].dp);
    cout << ans << '\n';
    return;
}