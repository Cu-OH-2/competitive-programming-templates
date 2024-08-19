const int MOD = 1e9 + 7;

ll qpow(ll a, ll p)
{
    ll res = 1;
    while (p)
    {
        if (p & 1) res = res * a % MOD;
        a = a * a % MOD;
        p >>= 1;
    }
    return res;
}

ll inv(ll x) { return qpow(x, MOD - 2); }

struct Square
{
    int n;
    vector<vector<ll>> a;
    Square(int n): n(n) { a.resize(n, vector<ll>(n)); }

    void unit()
    {
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                a[i][j] = (i == j);
            }
        }
        return;
    }

    bool inverse()
    {
        Square rig(n);
        rig.unit();
        for (int i = 0; i < n; ++i)
        {
            // 找到第i列最大值所在行
            ll tar = i;
            for (int j = i + 1; j < n; ++j)
            {
                if (abs(a[j][i]) > abs(a[tar][i])) tar = j;
            }
            // 与第i行交换
            if (tar != i)
            {
                for (int j = 0; j < n; ++j)
                {
                    swap(a[i][j], a[tar][j]);
                    swap(rig.a[i][j], rig.a[tar][j]);
                }
            }
            // 不可逆
            if (a[i][i] == 0) return 0;
            // 消去
            ll iv = inv(a[i][i]);
            for (int j = 0; j < n; ++j)
            {
                if (i == j) continue;
                ll t = a[j][i] * iv % MOD;
                for (int k = i; k < n; ++k)
                {
                    a[j][k] += MOD - a[i][k] * t % MOD;
                    a[j][k] %= MOD;
                }
                for (int k = 0; k < n; ++k)
                {
                    rig.a[j][k] += MOD - rig.a[i][k] * t % MOD;
                    rig.a[j][k] %= MOD;
                }
            }
            // 归一
            for (int j = 0; j < n; ++j)
            {
                a[i][j] *= iv;
                a[i][j] %= MOD;
                rig.a[i][j] *= iv;
                rig.a[i][j] %= MOD;
            }
        }
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                a[i][j] = rig.a[i][j];
            }
        }
        return 1;
    }
};