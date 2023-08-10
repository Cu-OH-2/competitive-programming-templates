/*******************************************************************
* 时间复杂度：O(n)
* 说明：求循环rotate得到的n种表示中字典序最小的一种
*******************************************************************/
const int N = 300005;

int n, a[N];

void solve()
{
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    auto norm = [](int x) { return (x - 1) % n + 1; };
    int p1 = 1, p2 = 2, len = 1;
    while (p1 <= n && p2 <= n & len <= n)
    {
        if (a[norm(p1 + len - 1)] == a[norm(p2 + len - 1)]) len++;
        else if (a[norm(p1 + len - 1)] < a[norm(p2 + len - 1)]) p2 += len, len = 1;
        else p1 += len, len = 1;
        if (p1 == p2) p1++;
    }
    int ans = min(p1, p2);
    return;
}