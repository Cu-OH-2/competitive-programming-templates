const int N = 300005;

int n, a[N];

void solve()
{
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    auto nrm = [](int x) { return (x - 1) % n + 1; };
    int p1 = 1, p2 = 2, len = 1;
    while (p1 <= n && p2 <= n & len <= n)
    {
        if (a[nrm(p1 + len - 1)] == a[nrm(p2 + len - 1)]) len++;
        else if (a[nrm(p1 + len - 1)] < a[nrm(p2 + len - 1)]) p2 += len, len = 1;
        else p1 += len, len = 1;
        if (p1 == p2) p1++;
    }
    int ans = min(p1, p2);
    return;
}