/*******************************************************************
* 时间复杂度：O(nlogV)
* 说明：
* 1.扩展中国剩余定理，解模数不互质的线性同余方程组，可能无解
* 2.防止溢出采用O(logV)快速乘，不改变时间复杂度
*******************************************************************/
struct ExCRT
{
    vector<pair<ll, ll>> f;
    inline ll norm(ll x, ll mod) { return (x % mod + mod) % mod; }
    ll qmul(ll a, ll b, ll mod)
    {
        a = norm(a, mod);
        b = norm(b, mod);
        ll res = 0;
        while (b)
        {
            if (b & 1) res = (res + a) % mod;
            a = (a + a) % mod;
            b >>= 1;
        }
        return res;
    }
    ll exgcd(ll a, ll b, ll& x, ll& y)
    {
        if (b == 0)
        {
            x = 1, y = 0;
            return a;
        }
        ll d = exgcd(b, a % b, x, y);
        ll newx = y, newy = x - a / b * y;
        x = newx, y = newy;
        return d;
    }
    void insert(ll r, ll m)
    {
        f.push_back({ r, m });
        return;
    }
    pair<ll, ll> work()
    {
        ll x, y;
        while (f.size() >= 2)
        {
            pair<ll, ll> f1 = f.back();
            f.pop_back();
            pair<ll, ll> f2 = f.back();
            f.pop_back();

            // n % m1 = r1, n % m2 = r2
            // => n = x * m1 + r1 = y * m2 + r2
            // => x * m1 - y * m2 = r2 - r1
            ll g = exgcd(f1.second, f2.second, x, y);
            ll c = f2.first - f1.first;
            if (c % g) return { -1, -1 }; // 无解
            x = qmul(x, c / g, f2.second / g); // 输入可能为负，输出非负
            ll m = f1.second / g * f2.second; // m = lcm(m1, m2)
            ll r = (x * f1.second + f1.first) % m; // r = norm(x) * m1 + r1
            f.push_back({ r, m });
        }
        return f.front();
    }
};