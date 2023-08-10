/*******************************************************************
* 时间复杂度：O(nlog^(d-1)n)
* 说明：
* 1.cdq注意事项详见[CDQ分治+数据结构=多维偏序]
* 2.n维偏序需要n-1层cdq
* 3.第i层cdq将整个区间按第i+1维归并排序，同时将第i维降为二进制，然后调用
    第i+1层cdq；第n-1层cdq递归将左右分别按第n维排序，再用双指针按照第n维
    大小归并，同时计算左部前n-2维全0元素对右部前n-2维全1元素的贡献
*******************************************************************/
const int N = 100005;

struct Elem
{
    ll a, b, c;
    ll cnt, id;
    bool xtag;
    bool operator!=(const Elem& e) const
    {
        return a != e.a || b != e.b || c != e.c;
    }
}e[N], ee[N], eee[N];

int n, k, ans[N], res[N];

bool bya(const Elem& e1, const Elem& e2)
{
    if (e1.a == e2.a && e1.b == e2.b) return e1.c < e2.c;
    else if (e1.a == e2.a) return e1.b < e2.b;
    else return e1.a < e2.a;
}

void cdq2(int lef, int rig)
{
    if (lef == rig - 1) return;
    int mid = lef + rig >> 1;
    cdq2(lef, mid);
    cdq2(mid, rig);
    int p1 = lef, p2 = mid, now = lef;
    int sum = 0;
    while (now < rig)
    {
        //左半部分xtag为0的可以贡献右半部分xtag为1的
        if (p2 == rig || p1 < mid && ee[p1].c <= ee[p2].c)
        {
            eee[now] = ee[p1++];
            sum += eee[now].cnt * (eee[now].xtag == 0);
        }
        else
        {
            eee[now] = ee[p2++];
            res[eee[now].id] += sum * (eee[now].xtag == 1);
        }
        now++;
    }
    for (int i = lef; i < rig; ++i) ee[i] = eee[i];
    return;
}

void cdq1(int lef, int rig)
{
    if (lef == rig - 1) return;
    int mid = lef + rig >> 1;
    cdq1(lef, mid);
    cdq1(mid, rig);
    int p1 = lef, p2 = mid, now = lef;
    while (now < rig)
    {
        if (p2 == rig || p1 < mid && e[p1].b <= e[p2].b)
        {
            ee[now] = e[p1++];
            ee[now].xtag = 0;
        }
        else
        {
            ee[now] = e[p2++];
            ee[now].xtag = 1;
        }
        now++;
    }
    for (int i = lef; i < rig; ++i) e[i] = ee[i];
    cdq2(lef, rig);
    return;
}

void solve()
{
    cin >> n >> k;
    vector<Elem> ori(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> ori[i].a >> ori[i].b >> ori[i].c;
        ori[i].cnt = 1;
    }
    sort(ori.begin(), ori.end(), bya);
    int cnt = 0;
    for (auto& x : ori)
    {
        if (cnt == 0 || e[cnt] != x) cnt++, e[cnt] = x, e[cnt].id = cnt;
        else e[cnt].cnt++;
    }
    cdq1(1, cnt + 1);
    for (int i = 1; i <= cnt; ++i)
    {
        res[e[i].id] += e[i].cnt - 1;
        ans[res[e[i].id]] += e[i].cnt;
    }
    for (int i = 0; i < n; ++i) cout << ans[i] << '\n';
    return;
}