/*******************************************************************
* 时间复杂度：O(nlogn)
* 说明：
* 1.解模数互质的线性同余方程组，一定有解
* 2.爆longlong时可能需要快速乘（模数过大也可能爆精度）
*******************************************************************/
struct CRT
{
    vector<pair<ll, ll>> f;
    inline ll norm(ll x, ll mod) { return (x % mod + mod) % mod; }
    ll qmul(ll a, ll b, ll mod)
    {
        //a = norm(a, mod);
        //b = norm(b, mod);
        ll res = a * b - (ll)((ld)a / mod * b + 1e-8) * mod;
        return norm(res, mod);
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
    ll inv(ll a, ll mod)
    {
        ll x, y;
        exgcd(a, mod, x, y);
        return norm(x, mod);
    }
    void insert(ll r, ll m)
    {
        f.push_back({ r, m });
        return;
    }
    ll work()
    {
        ll mul = 1, ans = 0;
        for (auto e : f) mul *= e.second;
        for (auto e : f)
        {
            ll m = mul / e.second;
            ll c = m * inv(m, e.second);
            ans += c * e.first;
        }
        return norm(ans, mul);
    }
};